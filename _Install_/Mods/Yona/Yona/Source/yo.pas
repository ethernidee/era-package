unit Yo;
{
DESCRIPTION:  Yona project
AUTHOR:       Alexander Shostak (aka Berserker aka EtherniDee aka BerSoft)
}

(***)  interface  (***)
uses
  SysUtils, Math,
  Utils, StrLib, Ini,
  Era, Lib;

const
  (* Pathes and names *)
  MOD_DIR             = 'Yona';
  SETTINGS_FILE_PATH  = MOD_DIR + '\settings.ini';
  LANG_FILE_PATH      = MOD_DIR + '\lang.ini';

  (* Settings *)
  DEBUG_OPT                     = 'Debug';
  NEW_CREATURE_ABILITIES_OPT    = 'NewCreatureAbilities';
  DEBUG_STACK_TO_STACK_DMG_OPT  = 'DebugStackToStackDamage';

  (* Balance configurations *)
  MAX_SHOOT_DISTANCE                = 19;
  ANTICAVALRY_DAMAGE_MULTIPLIER     = 200;
  INGAME_CAVALRY_BONUS_PER_CELL     = 5;
  ADDITIONAL_CAVALRY_BONUS_PER_CELL = 15;
  TOTAL_CAVALRY_BONUS_PER_CELL      =
    INGAME_CAVALRY_BONUS_PER_CELL +
    ADDITIONAL_CAVALRY_BONUS_PER_CELL;
  
  DEFENSIVE_BLOCK_DAMAGE_MULTIPLIER = 50;
  AIMED_SHOT_MULTIPLIER             = 300;
  HAMMER_CRUSH_BONUS                = 33;
  HAMMER_CRUSH_THRESHOLD            = 10; // damage of 10% of total enemy hp
  
  (* Colors *)
  SPECIAL_ABILITY_COLOR = GOLD_COLOR;

  (* Creature abilities assigment *)
  ANTI_CAVALRY_USERS    = [PIKEMAN, HALBERDIER];
  CAVALRY_USERS         = [CAVALIER, CHAMPION];
  DEFENSIVE_BLOCK_USERS = [SWORDSMAN, CRUSADER];
  DISTANT_ATTACK_USERS  = [ORC, ORC_CHIEFTAIN];
  AIMED_SHOT_USERS      = [ARCHER, MARKSMAN];
  HAMMER_CRUSH_USERS    = [DWARF, BATTLE_DWARF];
  
  (* Mouse click position *)
  PLACE_BATTLEGROUND  = 10;
  
  (* Hints *)
  HINT_DELIM  = '  ';
  
  (* Network *)
  TRIGGER_NET = 89999;
  

type
  TEvent  =
  (
    EVENT_ENTER_SPECIAL_MODE,
    EVENT_HINT,
    EVENT_CLICK,
    EVENT_LEAVE_SPECIAL_MODE
  );
  TEventHandler = procedure (Event: TEvent);
  
  TStackInfo  = class
    IsValidInfo:  boolean;
    
    // AIMED SHOT
    AimRound: integer;
    AimPos:   integer;

    // HAMMER CRUSH
    HammerStrikes: integer; // number of received hammer strikes
    
    procedure MakeValid;
  end; // .CLASS TStackInfo
  
  TNetEvents = (EVENT_AIMED_SHOT);

  TBg0 = record
    Stack:     integer;
    StackType: integer;
    StackNum:  integer;
    Action:    integer;
  end; // .record TBg0
  
  TRegenPhase = record
    Stack: integer;
  end; // .record TRegenPhase

  TBa = record
    
  end; // .record TBa

var
  (* Settings *)
  DebugOpt:                 boolean;
  NewCreatureAbilitiesOpt:  boolean;
  DebugStackToStackDmgOpt:  boolean;
  
  // Stack special abilities mode
  SpecialMode:  boolean = FALSE;
  
  // Event handler for special mode
  EventHandler: TEventHandler = nil;
  
  // Stack activating event
  EventStack: integer;
  
  // Generated starting from damage calculation event
  AbilityHint: string;
  
  // Full battle hint
  BattleHint: string;
  
  // General string builder
  {O} StrBuilder: StrLib.TStrBuilder;
  
  // Extra information for battle stacks
  {O} StacksInfo: array [FIRST_BATTLE_STACK..LAST_BATTLE_STACK] of TStackInfo;
  
  (* OnStackToStackPhysicalDamage *)
  DmgCalcAttacker: integer;
  DmgCalcDefender: integer;

  (* !?CM *)
  MousePos:       integer;
  MouseFlags:     integer;
  MouseType:      integer;
  MousePlace:     integer;
  MouseStack:     integer;
  MouseDeadStack: integer;
  
  (* !?BR *)
  BattleRound:  integer;

  (* !?BG0 *)
  ActingStack:           integer;
  ActingStackType:       integer;
  BattleAction:          integer;
  BattleActionDestStack: integer;

  Ba: TBa;
  Bg0: TBg0;
  RegenPhase: TRegenPhase;


(***) implementation (***)


function GetOpt (const OptName: string): boolean;
const
  MAX_VALUE_LENGTH  = 1024;
  
var
  Buf:  string;

begin
  SetLength(Buf, MAX_VALUE_LENGTH);
  
  if Ini.ReadStrFromIni(OptName, '', SETTINGS_FILE_PATH, Buf) then begin
    result := Buf = '1';
  end // .if
  else begin
    result := false;
  end; // .else
end; // .function GetOptValue

function tr
(
  const Key:          string;
  const FilePath:     string = LANG_FILE_PATH;
  const SectionName:  string = ''
): string;

begin
  result  :=  Key;
  Ini.ReadStrFromIni(Key, SectionName, FilePath, result);
end; // .function tr

procedure Erm (Cmds: string);
var
  CmdArr: TArrayOfStr;
  i:      integer;

begin
  CmdArr := StrLib.Explode(Cmds, ';');

  for i := 0 to high(CmdArr) do begin
    CmdArr[i] := Trim(CmdArr[i]);

    if CmdArr[i] <> '' then begin
      CmdArr[i] := CmdArr[i] + ';';
      ExecErmCmd(pchar(CmdArr[i]));
    end; // .if
  end; // .for
end; // .procedure Erm

procedure FireNet (Args: array of integer);
var
  i:  integer;

begin
  Game.FireRemoteErmEvent(TRIGGER_NET, Args);
  Era.v[1]  :=  TRIGGER_NET;
  
  for i := 1 to Math.Min(Length(Args), 16) do begin
    Era.y[i]  :=  Args[i - 1];
  end; // .for
  
  Era.ExecErmCmd('FUv1:Py1/y2/y3/y4/y5/y6/y7/y8/y9/y10/y11/y12/y13/y14/y15/y16;');
end; // .procedure FireNet

function FormatDamage (MinDamage, MaxDamage, MinKilled, MaxKilled, FatalityNum: integer): string;
const
  MAX_NUMKILLED_FRACT_DISPLAY_VALUE = 20;
  
  FRACT_SEPARATOR = '.';
  
  DEF_COLOR   = '';
  MARK_COLOR  = 'Chartreuse';

var
  Color:  string;
  
  procedure WriteStr (const Str: string);
  begin
    if Color <> '' then begin
      StrBuilder.Append('{~');
      StrBuilder.Append(Color);
      StrBuilder.Append('}');
    end; // .if
    
    StrBuilder.Append(Str);
    
    if Color <> '' then begin
      StrBuilder.Append('{~}');
    end; // .if
  end; // .procedure Write
  
  procedure WriteInt (Value: integer);
  begin
    WriteStr(IntToStr(Value));
  end; // .procedure WriteInt
  
  procedure WriteMarkedInt (Value, MarkLimit: integer);
  begin
    if Value >= MarkLimit then begin
      Color :=  MARK_COLOR;
    end; // .if
    
    WriteInt(Value);
    Color :=  DEF_COLOR;
  end; // .procedure WriteMarkedInt
  
  procedure WriteHumanInt (Value, OrientOnValue: integer);
  const
    THOUSAND_CHAR = 'k';
  
  var
    HighPart: integer;
    LowPart:  integer;
    
  begin
    if OrientOnValue < 1000 then begin
      WriteInt(Value);
    end // .if
    else begin
      if OrientOnValue < 10000 then begin
        HighPart  :=  ROUND(Value / 100);
        LowPart   :=  HighPart mod 10;
        HighPart  :=  HighPart div 10;
        WriteInt(HighPart);
        
        if LowPart <> 0 then begin
          WriteStr(FRACT_SEPARATOR);
          WriteInt(LowPart);
        end; // .if
      end // .if
      else begin
        WriteInt(ROUND(Value / 1000));
      end; // .else
      
      WriteStr(THOUSAND_CHAR);
    end; // .else
  end; // .procedure WriteHumanInt

var
  SumKilled:  integer;
  AvgKilled:  integer;
  
begin
  StrBuilder.Clear;
  Color :=  DEF_COLOR;
  
  SumKilled :=  MinKilled + MaxKilled;
  AvgKilled :=  SumKilled div 2;
  
  WriteMarkedInt(AvgKilled, FatalityNum);
  
  if (SumKilled < MAX_NUMKILLED_FRACT_DISPLAY_VALUE) and ODD(SumKilled) then begin
    if AvgKilled >= FatalityNum then begin
      Color :=  MARK_COLOR;
    end; // .if
    
    WriteStr(FRACT_SEPARATOR + '5');
    Color :=  DEF_COLOR;
  end; // .if
  
  WriteStr('  (');
  
  if MinKilled <> MaxKilled then begin
    WriteMarkedInt(MinKilled, FatalityNum);
    WriteStr('-');
    WriteMarkedInt(MaxKilled, FatalityNum);
    WriteStr(', ');
  end; // .if
  
  if MinDamage <> MaxDamage then begin
    WriteHumanInt(MinDamage, MaxDamage);
    WriteStr('-');
  end; // .if
  
  WriteHumanInt(MaxDamage, MaxDamage);
  WriteStr(')');
  
  result  :=  StrBuilder.BuildStr;
end; // .function FormatDamage

function IsCavalry (MonType: integer): boolean;
begin
  result  :=  MonType in 
  [
    CAVALIER,     CHAMPION,
    CENTAUR,      CENTAUR_CAPTAIN,
    UNICORN,      WAR_UNICORN,
    BLACK_KNIGHT, DREAD_KNIGHT,
    NOMAD,        SYLVAN_CENTAUR,
    NIGHTMARE,    HELL_STEED
  ];
end; // .function IsCavalry

procedure TStackInfo.MakeValid;
var
  i: integer;

begin
  if not Self.IsValidInfo then begin
    Self.IsValidInfo   := TRUE;
    Self.AimRound      := NO_ROUND;
    Self.AimPos        := INVALID_POS;
    Self.HammerStrikes := 0;
  end; // .if
end; // .procedure TStackInfo.MakeValid

procedure UpdateStacksInfo;
var
  i: integer;
   
begin
  for i := Low(StacksInfo) to High(StacksInfo) do begin
    if StacksInfo[i].IsValidInfo then begin
      StacksInfo[i].IsValidInfo := (Stacks(i, STACK_TYPE).v <> NO_STACK) and (Stacks(i, STACK_NUM).v > 0);
    end;
    
    if not StacksInfo[i].IsValidInfo then begin
      StacksInfo[i].MakeValid;
    end;
  end; // .for
end; // .procedure UpdateStacksInfo

procedure OnBattleRound (Event: Era.PEvent); stdcall;
begin
  BattleRound :=  Era.v[997];
  UpdateStacksInfo;
end; // .procedure OnBattleRound

procedure OnStackToStackDamage (Event: Era.PEvent); stdcall;
const
  (* Event arguments *)
  ARG_ATTACKER_STACK        = 0;
  ARG_DEFENDER_STACK        = 1;
  ARG_FINAL_DAMAGE_CONST    = 2;
  ARG_FINAL_DAMAGE          = 3;
  ARG_BASIC_DAMAGE          = 4;
  ARG_DAMAGE_BONUS          = 5;
  ARG_IS_DISTANT_ATTACK     = 6;
  ARG_DISTANCE              = 7;
  ARG_IS_THEORETICAL_ATTACK = 8;

var
  (* Event arguments *)
  Attacker:             integer;
  Defender:             integer;
  FinalDamage:          integer;
  BasicDamage:          integer;
  DamageBonus:          integer;
  IsDistantAttack:      boolean;
  Distance:             integer;
  IsTheoreticalAttack:  boolean;
  
  (* Derived event arguments
     Resulting damage is
      (BasicDamage + DamageBonus) * (1 + DamagePercentBonus / 100) * DamageMultiplier
  *)
  
  IngameDamageMultiplier: double;
  DamageMultiplier:       double;
  DamagePercentBonus:     double;
  
  AttackerType: integer;
  DefenderType: integer;
  
  AttackerPos:  integer;
  DefenderPos:  integer;
  
  TempInt:  integer;
  
begin
  Attacker  :=  Era.EventParams[ARG_ATTACKER_STACK];
  Defender  :=  Era.EventParams[ARG_DEFENDER_STACK];
  
  FinalDamage         :=  Era.EventParams[ARG_FINAL_DAMAGE];
  BasicDamage         :=  Era.EventParams[ARG_BASIC_DAMAGE];
  DamageBonus         :=  0;
  IsDistantAttack     :=  Era.EventParams[ARG_IS_DISTANT_ATTACK] = 1;
  Distance            :=  Era.EventParams[ARG_DISTANCE];
  IsTheoreticalAttack :=  Era.EventParams[ARG_IS_THEORETICAL_ATTACK] = 1;
  
  IngameDamageMultiplier  :=  FinalDamage / (BasicDamage + Era.EventParams[ARG_DAMAGE_BONUS]);
  DamageMultiplier        :=  IngameDamageMultiplier;
  DamagePercentBonus      :=  Era.EventParams[ARG_DAMAGE_BONUS] * (100 / BasicDamage);
   
  (* Full initial damage diagnostics *)
  if DebugStackToStackDmgOpt then begin
    Writeln;
    Write('A[', Attacker, '] ');
    Write('D[', Defender, '] ');
    Write
    (
      'DM = (',
      BasicDamage, ' + ', (DamagePercentBonus):1:1, '% (', Era.EventParams[ARG_DAMAGE_BONUS],
      ') * ', DamageMultiplier:3:2, ' = ',
      FinalDamage, ';  '
    );
    Write('ID[', IsDistantAttack, '] ');
    Write
    (
      'DI[', Distance, ': ', Stacks(Attacker, STACK_POS).v,
      '-', Stacks(Defender, STACK_POS).v, '] '
    );
    Write('TH[', IsTheoreticalAttack, '];');
    Writeln;
  end; // .if

  AbilityHint  :=  '';
  
  if Defender <> NO_STACK then begin
    (* Fixing distance for shooters *)
    if IsDistantAttack and (Distance = 0) then begin
      Distance  :=  CalculateDistance
      (
        Stacks(Attacker, STACK_POS).v,
        Stacks(Defender, STACK_POS).v
      );
      Era.EventParams[ARG_DISTANCE] :=  Distance;
    end; // .if
    
    AttackerType  :=  Stacks(Attacker, STACK_TYPE).v;
    DefenderType  :=  Stacks(Defender, STACK_TYPE).v;
    
    AttackerPos  :=  Stacks(Attacker, STACK_POS).v;
    DefenderPos  :=  Stacks(Defender, STACK_POS).v;
    
    if NewCreatureAbilitiesOpt then begin
      // ANTI-CAVALRY - X times more damage to cavalry, ignores cavalry bonus
      if (AttackerType in ANTI_CAVALRY_USERS) and IsCavalry(DefenderType)
      then begin
        DamageMultiplier  :=  DamageMultiplier * (ANTICAVALRY_DAMAGE_MULTIPLIER / 100);
        AbilityHint       :=  AbilityHint + HINT_DELIM + ColorizeText(StrLib.BuildStr
        (
          tr('ANTICAVALRY_BONUS'),
          ['Multiplier', IntToStr(ANTICAVALRY_DAMAGE_MULTIPLIER)],
          TEMPLATE_CHAR
        ), SPECIAL_ABILITY_COLOR);
      end; // .if
      
      
      // CAVALRY - X% damage bonus per cell
      if
        (AttackerType in CAVALRY_USERS) and
        ((Stacks(Defender, STACK_FLAGS).v and FLAG_FLIER) = 0)
      then begin
        // Remove cavalry bonus for non-heroes3 anti-cavalry units
        if
          not (DefenderType in [PIKEMAN, HALBERDIER]) and
          (DefenderType in ANTI_CAVALRY_USERS)
        then begin
          DamagePercentBonus  :=  Math.Max
          (
            DamagePercentBonus - INGAME_CAVALRY_BONUS_PER_CELL * Distance,
            0
          );
        end; // .if
        
        if not (DefenderType in ANTI_CAVALRY_USERS) then begin
          DamagePercentBonus  :=  DamagePercentBonus + Distance * ADDITIONAL_CAVALRY_BONUS_PER_CELL;
          AbilityHint         :=  AbilityHint + HINT_DELIM + ColorizeText(StrLib.BuildStr
          (
            tr('CAVALRY_BONUS'),
            [
              'Damage',
              IntToStr(TOTAL_CAVALRY_BONUS_PER_CELL * Distance)
            ],
            Lib.TEMPLATE_CHAR
          ), SPECIAL_ABILITY_COLOR);
        end; // .if
      end; // .if
      
      
      // DEFENSIVE BLOCK - receive only X% of physical damage in defense state
      if
        (DefenderType in DEFENSIVE_BLOCK_USERS) and
        ((Stacks(Defender, STACK_FLAGS).v and FLAG_DEFENSE) <> 0)
      then begin 
        DamageMultiplier  :=  DamageMultiplier * DEFENSIVE_BLOCK_DAMAGE_MULTIPLIER / 100;
        AbilityHint       :=  AbilityHint + HINT_DELIM + ColorizeText(StrLib.BuildStr
        (
          tr('DEFENSIVE_BLOCK_BONUS'),
          ['Multiplier', IntToStr(DEFENSIVE_BLOCK_DAMAGE_MULTIPLIER)],
          Lib.TEMPLATE_CHAR
        ), SPECIAL_ABILITY_COLOR);
      end; // .if
      
      
      // DISTANCE DEPENDANT ATTACK - Damage * ((MAX_DIST - Min(MAX_DIST, Distance)) ^ 2)%
      if (AttackerType in DISTANT_ATTACK_USERS) and (IsDistantAttack) then begin
        TempInt     :=  (MAX_SHOOT_DISTANCE - Math.Min(MAX_SHOOT_DISTANCE, Distance));
        TempInt     :=  TempInt * TempInt;
        AbilityHint :=  AbilityHint + HINT_DELIM + ColorizeText(StrLib.BuildStr
        (
          tr('DISTANCE_DEPENDANT_ATTACK_BONUS'),
          [
            'Modifier', IntToStr(TempInt)
          ],
          Lib.TEMPLATE_CHAR
        ), SPECIAL_ABILITY_COLOR);
        
        DamageMultiplier  :=  DamageMultiplier * TempInt / 100;
      end; // .if
    end; // .if
    
    // AIMED SHOT - increased damage for particular hex
    if
      (AttackerType in AIMED_SHOT_USERS)                    and
      IsDistantAttack                                       and
      (StacksInfo[Attacker].IsValidInfo)                    and
      (StacksInfo[Attacker].AimPos <> INVALID_POS)          and
      ((BattleRound - StacksInfo[Attacker].AimRound) <= 1)  and
      (
        (StacksInfo[Attacker].AimPos = DefenderPos) or
        (
          ((Stacks(Defender, STACK_FLAGS).v and FLAG_TWO_HEXED) <> 0) and
          (StacksInfo[Attacker].AimPos = (DefenderPos + 1 - Stacks(Defender, STACK_SIDE).v * 2))
        )
      )
    then begin
      AbilityHint :=  AbilityHint + HINT_DELIM + ColorizeText(StrLib.BuildStr
      (
        tr('AIMED_SHOT_BONUS'),
        [
          'Multiplier', IntToStr(AIMED_SHOT_MULTIPLIER)
        ],
        Lib.TEMPLATE_CHAR
      ), SPECIAL_ABILITY_COLOR);
    
      DamageMultiplier  :=  DamageMultiplier * (AIMED_SHOT_MULTIPLIER / 100);
    end; // .if

    // HAMMER CRUSH - increase damage for accumulated number of hammer strikes
    if (AttackerType in HAMMER_CRUSH_USERS) and
       (StacksInfo[Defender].HammerStrikes > 0)
    then begin
      TempInt          := HAMMER_CRUSH_BONUS * StacksInfo[Defender].HammerStrikes + 100;
      DamageMultiplier := DamageMultiplier * (TempInt / 100);
      AbilityHint      := AbilityHint + HINT_DELIM + ColorizeText(StrLib.BuildStr
      (
        tr('HUMMER_CRUSH_BONUS'),
        [
          'Multiplier', IntToStr(TempInt)
        ],
        Lib.TEMPLATE_CHAR
      ), SPECIAL_ABILITY_COLOR);
    end; // .if
    
    (* Calculating new damage *)
    Era.EventParams[ARG_FINAL_DAMAGE] :=  Math.Max(1, TRUNC
    (
      (BasicDamage * (1 + DamagePercentBonus / 100) + DamageBonus) * DamageMultiplier
    ));

    (* Save event participants and final calculated damage. Check saved values in !?MF1 to
       determine attacker and if it's a counter attack *)
    if IsTheoreticalAttack then begin
      DmgCalcAttacker := -1;
      DmgCalcDefender := -1;
    end else begin
      DmgCalcAttacker := Attacker;
      DmgCalcDefender := Defender;
    end; // .else
    
    (* Full post damage diagnostics *)
    if DebugStackToStackDmgOpt then begin
      Writeln;
      Write('A[', Attacker, '] ');
      Write('D[', Defender, '] ');
      Write
      (
        'DM = (',
        BasicDamage, ' + ', (DamagePercentBonus):1:1, '% (',
        (BasicDamage * DamagePercentBonus / 100):1:0, ') + ', DamageBonus,
        ') * ', DamageMultiplier:3:2, ' = ',
        Era.EventParams[ARG_FINAL_DAMAGE], ';  '
      );
      Write('ID[', IsDistantAttack, '] ');
      Write
      (
        'DI[', Distance, ': ', Stacks(Attacker, STACK_POS).v,
        '-', Stacks(Defender, STACK_POS).v, '] '
      );
      Write('TH[', IsTheoreticalAttack, ']; @@');
      Writeln;
    end; // .if
  end; // .if
end; // .procedure OnStackToStackDamage

procedure OnBattleMouseHint (Event: Era.PEvent); stdcall;
const
  ARG_ATTACKER_STACK  = 0;
  ARG_DEFENDER_STACK  = 1;
  ARG_MIN_DAMAGE      = 2;
  ARG_MAX_DAMAGE      = 3;

var
  (* Events arguments *)
  Attacker: integer;
  Defender: integer;
  
  MinDamage:  integer;
  MaxDamage:  integer;
  
  IsDamageHint: boolean;
  
  TargetNum:    integer;
  TargetHP:     integer;
  TargetLostHP: integer;
  
  Distance: integer;
  
  AttackerType: integer;
  DefenderType: integer;
  
  AttackerPos:  integer;
  DstPos:       integer;
  
  TempInt:  integer;
  
begin
  if not Game.CursorLocked or SpecialMode then begin
    Attacker  :=  Era.EventParams[ARG_ATTACKER_STACK];
    Defender  :=  Era.EventParams[ARG_DEFENDER_STACK];
    
    MinDamage :=  Era.EventParams[ARG_MIN_DAMAGE];
    MaxDamage :=  Era.EventParams[ARG_MAX_DAMAGE];
    
    IsDamageHint  :=  (Attacker <> NO_STACK) and (Defender <> NO_STACK) and (MinDamage <> -1);
    BattleHint    :=  '';
    
    Era.ExecErmCmd('MM:D?y1;');
    DstPos  :=  Era.y[1];

    if IsDamageHint then begin   
      TargetNum     :=  Stacks(Defender, STACK_NUM).v;
      TargetHP      :=  Stacks(Defender, STACK_HP).v;
      TargetLostHP  :=  Stacks(Defender, STACK_LOSTHP).v;
  
      BattleHint  :=  FormatDamage
      (
        MinDamage,
        MaxDamage,
        CalcNumKilled(MinDamage, TargetLostHP, TargetHP),
        CalcNumKilled(MaxDamage, TargetLostHP, TargetHP),
        TargetNum
      );
      
      AttackerType  :=  Stacks(Attacker, STACK_TYPE).v;
      DefenderType  :=  Stacks(Defender, STACK_TYPE).v;

      BattleHint  :=  BattleHint + AbilityHint;

      // AIMED SHOT - show special cursor when mouse is over enemy
      if
        (AttackerType in AIMED_SHOT_USERS)                    and
        (StacksInfo[Attacker].IsValidInfo)                    and
        (StacksInfo[Attacker].AimPos <> INVALID_POS)          and
        ((BattleRound - StacksInfo[Attacker].AimRound) <= 1)  and
        (StacksInfo[Attacker].AimPos = DstPos)
      then begin
        RedirectFile('cradvntr.def', 'cursarch.def');
        Game.SetCursor(1, 3);
        RedirectFile('cradvntr.def', '');
      end; // .if
    end // .if
    else begin // Pieceful hint
      Attacker      :=  GetActiveStack;
      AttackerType  :=  Stacks(Attacker, STACK_TYPE).v;
      
      (* For battle cells *)
      if Math.InRange(DstPos, FIRST_BATTLEFIELD_POS, LAST_BATTLEFIELD_POS) then begin
        Era.y[1]  :=  DstPos;
        Era.ExecErmCmd('BU:Ey1/?y2;');
        Defender  :=  Era.y[2];

        AttackerPos :=  Stacks(Attacker, STACK_POS).v;
        Distance    :=  CalculateDistance(AttackerPos, DstPos);
        
        // Find shortest distance for 2-hexed creatures
        if (Stacks(Attacker, STACK_FLAGS).v and FLAG_TWO_HEXED) <> 0 then begin
          Distance  :=  Math.Min
          (
            Distance,
            CalculateDistance(AttackerPos + 1 - Stacks(Attacker, STACK_SIDE).v * 2, DstPos)
          );
        end; // .if
        
        BattleHint  :=  StrLib.BuildStr
        (
          tr('DISTANCE_HINT'),
          ['Distance',  IntToStr(Distance)],
          TEMPLATE_CHAR
        );
        
        if NewCreatureAbilitiesOpt then begin
          // CAVALRY passive distance bonus hint
          if AttackerType in CAVALRY_USERS then begin
            BattleHint :=  BattleHint + '.' + HINT_DELIM + ColorizeText(StrLib.BuildStr
            (
              tr('CAVALRY_BONUS'),
              [
                'Damage',
                IntToStr(TOTAL_CAVALRY_BONUS_PER_CELL * Distance)
              ],
              TEMPLATE_CHAR
            ), SPECIAL_ABILITY_COLOR);
          end; // .if
          
          // DISTANCE DEPENDANT ATTACK - passive bonus hint
          if AttackerType in DISTANT_ATTACK_USERS then begin     
            TempInt :=  (MAX_SHOOT_DISTANCE - Math.Min(MAX_SHOOT_DISTANCE, Distance));
            TempInt :=  TempInt * TempInt;
          
            BattleHint := BattleHint + '.' + HINT_DELIM + ColorizeText(StrLib.BuildStr
            (
              tr('DISTANCE_DEPENDANT_ATTACK_BONUS'),
              [
                'Modifier', IntToStr(TempInt)
              ],
              TEMPLATE_CHAR
            ), SPECIAL_ABILITY_COLOR);
          end; // .if
          
          // AIMED SHOT - increased damage for particular hex
          if
            (AttackerType in AIMED_SHOT_USERS)                    and
            (StacksInfo[Attacker].IsValidInfo)                    and
            (StacksInfo[Attacker].AimPos <> INVALID_POS)          and
            ((BattleRound - StacksInfo[Attacker].AimRound) <= 1)  and
            (StacksInfo[Attacker].AimPos = DstPos)
          then begin
            BattleHint :=  BattleHint + HINT_DELIM + ColorizeText(StrLib.BuildStr
            (
              tr('AIMED_SHOT_BONUS'),
              [
                'Multiplier', IntToStr(AIMED_SHOT_MULTIPLIER)
              ],
              Lib.TEMPLATE_CHAR
            ), SPECIAL_ABILITY_COLOR);
          end; // .if
        end; // .if
      end; // .if
    end; // .else
    
    if SpecialMode then begin
      EventStack  :=  Attacker;
      EventHandler(EVENT_HINT);
    end; // .if
    
    if BattleHint <> '' then begin
      SetBattleHint(BattleHint);
    end; // .elseIF
  end; // .if
end; // .procedure OnBattleMouseHint

procedure AimedShotHandler (Event: TEvent);
begin
  case Event of 
    EVENT_ENTER_SPECIAL_MODE:
      begin
        RedirectFile('cradvntr.def', 'cursarch.def');
        Game.SetLockedCursor(1, 15);
        RedirectFile('cradvntr.def', '');
      end;
    EVENT_HINT:
      begin
        if BattleHint <> '' then begin
          BattleHint  :=  BattleHint + HINT_DELIM;
        end; // .if
        
        BattleHint  :=  BattleHint + ColorizeText(tr('AIMED_SHOT_HINT'), SPECIAL_ABILITY_COLOR);
      end;
    EVENT_CLICK:
      begin
        Era.ExecErmCmd('VRz1:S^bow.wav^;');
        Era.ExecErmCmd('SN:Pz1;');
        FireNet([ORD(EVENT_AIMED_SHOT), EventStack, BattleRound, MousePos]);
        Game.UnlockCursor;
        Game.SetCursor(CURSOR_NORMAL, CURSOR_NORMAL_NORMAL);
        SpecialMode :=  FALSE;
        Combat(COMBAT_ACTION).v :=  SKIP_ACTION;
      end;
    EVENT_LEAVE_SPECIAL_MODE:
      begin
        Game.UnlockCursor;
        Game.SetCursor(CURSOR_NORMAL, CURSOR_NORMAL_NORMAL);
        SpecialMode :=  FALSE;
      end;
  end; // .SWITCH Event
end; // .procedure AimedShotHandler

procedure OnKeyPressed (Event: Era.PEvent); stdcall;
const
  ARG_KEYCODE           = 0;
  ARG_BLOCKDEFREACTION  = 1;

  SPECIAL_KEY = KEY_ESC;

var
  KeyCode:          integer;
  BlockDefReaction: LONGBOOL;
  DlgId:            integer;

  ActiveStack:    integer;
  ActiveSide:     integer;
  ActiveHero:     integer;
  ActiveOwner:    integer;
  IsHuman:        boolean;
  IsLocalPlayer:  boolean;

  StackType:  integer;

  KeysAreAllowed:  boolean;
  
  procedure EnterSpecialMode (Handler: TEventHandler);
  begin
    SpecialMode       :=  TRUE;
    EventHandler      :=  Handler;
    BlockDefReaction  :=  TRUE;
    EventStack        :=  ActiveStack;
    Game.BlockThisEventForERM(Event);
    EventHandler(EVENT_ENTER_SPECIAL_MODE);
  end; // .procedure EnterSpecialMode
  
begin
  KeyCode           :=  Era.EventParams[ARG_KEYCODE];
  BlockDefReaction  :=  LONGBOOL(Era.EventParams[ARG_BLOCKDEFREACTION]);

  DlgId           :=  Game.GetDlgId;
  KeysAreAllowed  :=  FALSE;
  ActiveStack     :=  GetActiveStack;

  (* Is event allowed? *)
  if (DlgId = BATTLE_DLG) and not IsTacticPhase then begin
    ActiveSide  :=  Combat(COMBAT_SIDE).v;

    Era.y[1]    :=  ActiveSide;
    Era.ExecErmCmd('BHy1:N?y2;');
    ActiveHero  :=  Era.y[2];

    Era.ExecErmCmd('BA:O?y1/?y2;');
    ActiveOwner :=  Era.y[1 + ActiveSide];

    if Combat(COMBAT_ACTION).v = NO_ACTION then begin
      Era.y[1]      :=  ActiveOwner;
      Era.ExecErmCmd('OW:Iy1/?y2 Gy1/?y3;');
      IsHuman       :=  Era.y[2] = 0;
      IsLocalPlayer :=  Era.y[3] = 1;

      KeysAreAllowed :=  IsHuman and IsLocalPlayer and not IsAutoBattle;
    end; // .if
  end; // .if

  if (DlgId = BATTLE_DLG) and KeysAreAllowed then begin
    if SpecialMode then begin
      if KeyCode = SPECIAL_KEY then begin
        SpecialMode :=  FALSE;
        EventHandler(EVENT_LEAVE_SPECIAL_MODE);
      end; // .if

      KeyCode           :=  NO_KEY;
      BlockDefReaction  :=  TRUE;
      Game.BlockThisEventForERM(Event);
    end // .if
    else if KeyCode = SPECIAL_KEY then begin
      UpdateStacksInfo;
      StackType :=  Stacks(ActiveStack, STACK_TYPE).v;

      // AIMED SHOT - spend a turn to aim at hex and shoot at it more effectively the next run
      if StackType in AIMED_SHOT_USERS then begin
        EnterSpecialMode(AimedShotHandler);
      end; // .if
    end; // .elseIF
  end; // .if
  
  Era.EventParams[ARG_KEYCODE]          :=  KeyCode;
  Era.EventParams[ARG_BLOCKDEFREACTION] :=  integer(BlockDefReaction);
end; // .procedure OnKeyPressed

procedure OnBattleScreenMouseClick (Event: Era.PEvent); stdcall;
begin
  Era.ExecErmCmd('CM:D?y1 F?y2 S?y3 I?y4;');
  MousePos    :=  Era.y[1];
  MouseFlags  :=  Era.y[2];
  MouseType   :=  Era.y[3];
  MousePlace  :=  Era.y[4];
  
  if
    (MousePlace in [0..1]) and (MousePos in [FIRST_BATTLEFIELD_POS..LAST_BATTLEFIELD_POS])
  then begin
    MousePlace      :=  PLACE_BATTLEGROUND;
    Era.y[1]        :=  MousePos;
    Era.ExecErmCmd('BU:Ey1/?y2 Dy1/?y3;');
    MouseStack      :=  Era.y[2];
    MouseDeadStack  :=  Era.y[3];
    
    if MouseDeadStack = -2 then begin
      MouseDeadStack  :=  NO_STACK;
    end; // .if
  end; // .if
  
  if SpecialMode then begin
    {!} Assert(@EventHandler <> nil);
    Game.BlockThisEventForERM(Event);
    Game.ClickIsBlocked :=  TRUE;
    EventStack          :=  GetActiveStack;
    UpdateStacksInfo;
    
    if (MouseFlags and RMB) <> 0 then begin
      EventHandler(EVENT_LEAVE_SPECIAL_MODE);
    end // .if
    else if (MousePlace = PLACE_BATTLEGROUND) and (MouseType = LMB_PUSH) then begin
      EventHandler(EVENT_CLICK);
    end; // .elseIF
  end; // .if
end; // .procedure OnBattleScreenMouseClick

//procedure OnBeforeBattleUniversal (Event: Era.PEvent); stdcall;
//begin
//  Erm('BA:O?y1/?y2 H0/?y3 H1/?y4; OW:Iy1/?y5 Iy2/?y6');
//  Ba.Owners[0] := Era.y[1];
//  Ba.Owners[1] := Era.y[2];
//  Ba.Heroes[0] := Era.y[3];
//  Ba.Heroes[1] := Era.y[4];
//  Ba.AI[0]     := Era.y[5];
//  Ba.AI[1]     := Era.y[6];
//end; // .procedure OnBeforeBattleUniversal

procedure OnBeforeBattleAction (Event: Era.PEvent); stdcall;
begin
  Era.ExecErmCmd('BG:N?y1 A?y2 E?y3;');
  ActingStack           := Era.y[1];
  BattleAction          := Era.y[2];
  BattleActionDestStack := Era.y[3];
  Era.ExecErmCmd('BMy1:T?y4;');
  ActingStackType       := Era.y[4];

  UpdateStacksInfo;
end; // .procedure OnBeforeBattleAction

procedure OnAfterBattleAction (Event: Era.PEvent); stdcall;
begin
  {// HAMMER CRUSH
  if (BattleAction = Lib.ACTION_MELEE_ATTACK) and
     (ActingStackType IN HAMMER_CRUSH_USERS)
  then begin
    Era.y[1] := ActingStack;
    Era.ExecErmCmd('BMy1:N?y2;');

    if Era.y[2] > 0 then begin
      if StacksInfo[ActingStack].LastTarget = BattleActionDestStack then begin
        inc(StacksInfo[ActingStack].LastTargetNumSerialStrikes);
      end else begin
        StacksInfo[ActingStack].LastTarget                 := BattleActionDestStack;
        StacksInfo[ActingStack].LastTargetNumSerialStrikes := 1;
      end; // .else
    end; // .if
  end; // .if}

  UpdateStacksInfo;
end; // .procedure OnAfterBattleAction

procedure OnBattleRegeneratePhase (Event: Era.PEvent); stdcall;
begin
  RegenPhase.Stack := Era.EventParams[0];

  if not IsTacticPhase and not IsAutoBattle then begin
    
  end; // .if
end; // .procedure OnBattleRegeneratePhase

procedure OnMonsterPhysicalDamage (Event: Era.PEvent); stdcall;
var
  Attacker:        integer;
  AttackerType:    integer;
  Defender:        integer;
  Damage:          integer;
  DefenderTotalHp: integer;

begin
  ExecErmCmd('MF:N?y1 F?y2;');
  Defender := Era.y[1];
  Damage   := Era.y[2];

  if (Defender = DmgCalcDefender) and (DmgCalcAttacker <> NO_MON_TYPE) then begin
    Era.y[99] := DmgCalcAttacker;
    ExecErmCmd('BMy99:T?y98;');
    Attacker     := DmgCalcAttacker;
    AttackerType := Era.y[98];

    // HAMMER CRUSH
    if (AttackerType in HAMMER_CRUSH_USERS) and
       (StacksInfo[Defender].IsValidInfo)
    then begin
      ExecErmCmd('BMy1:N?y3 H?y4 L?y5;');
      DefenderTotalHp := Era.y[3] * Era.y[4] - Era.y[5];

      if (DefenderTotalHp div Damage <= HAMMER_CRUSH_THRESHOLD) then begin
        Inc(StacksInfo[Defender].HammerStrikes);
      end; // .if
    end; // .if
  end; // .if

  // Real damage calculation and damage receive trigger must be sequentional
  DmgCalcAttacker := NO_MON_TYPE;
  DmgCalcDefender := NO_MON_TYPE;
end; // .procedure OnMonsterPhysicalDamage

procedure OnBeforeBattleUniversal (Event: Era.PEvent); stdcall;
var
  i:  integer;
   
begin
  for i := Low(StacksInfo) to High(StacksInfo) do begin
    StacksInfo[i].IsValidInfo := FALSE;
  end; // .for
end; // .procedure OnBeforeBattleUniversal

procedure OnNet (Event: Era.PEvent); stdcall;
begin
  // Switch event
  case Era.x[1] of 
    ORD(EVENT_AIMED_SHOT):
      begin
        EventStack  :=  Era.x[2];
        BattleRound :=  Era.x[3];
        MousePos    :=  Era.x[4];
        // --- //
        StacksInfo[EventStack].MakeValid;
        StacksInfo[EventStack].AimRound := BattleRound;
        StacksInfo[EventStack].AimPos   := MousePos;
        WriteBattleLog(StrLib.BuildStr(
          tr('AIMED_SHOT_ACTION_LOG'),
          [
            'Num',  IntToStr(Stacks(EventStack, STACK_NUM).v),
            'Name', Game.MonInfos[Stacks(EventStack, STACK_TYPE).v].Name[NAME_PLURAL]
          ],
          TEMPLATE_CHAR
        ));
      end;
  end; // .switch Network event
end; // .procedure OnNet

procedure InitStacksInfo;
var
  i:  integer;
   
begin
  for i := Low(StacksInfo) to High(StacksInfo) do begin
    StacksInfo[i] :=  TStackInfo.Create;
  end; // .for
end; // .procedure InitStacksInfo

begin
  StrBuilder  :=  StrLib.TStrBuilder.Create;
  InitStacksInfo;

  (* Read options *)
  DebugOpt                :=  GetOpt(DEBUG_OPT);
  NewCreatureAbilitiesOpt :=  GetOpt(NEW_CREATURE_ABILITIES_OPT);
  
  if DebugOpt then begin
    DebugStackToStackDmgOpt :=  GetOpt(DEBUG_STACK_TO_STACK_DMG_OPT);
    Game.CreateConsole('Yona debug console');
  end; // .if
  
  (* Register handlers *)
  Era.RegisterHandler(OnStackToStackDamage,     'OnStackToStackDamage');
  Era.RegisterHandler(OnBattleMouseHint,        'OnBattleMouseHint');
  Era.RegisterHandler(OnKeyPressed,             'OnKeyPressed');
  Era.RegisterHandler(OnBattleScreenMouseClick, 'OnBattleScreenMouseClick');
  Era.RegisterHandler(OnBeforeBattleUniversal,  'OnBeforeBattleUniversal');
  Era.RegisterHandler(OnBeforeBattleAction,     'OnBeforeBattleAction');
  Era.RegisterHandler(OnAfterBattleAction,      'OnAfterBattleAction');
  Era.RegisterHandler(OnBattleRegeneratePhase,  'OnBattleRegeneratePhase');
  Era.RegisterHandler(OnMonsterPhysicalDamage,  'OnMonsterPhysicalDamage');
  Era.RegisterHandler(OnBattleRound,            'OnBattleRound');
  Era.RegisterHandler(OnBeforeBattleUniversal,  'OnBeforeBattleUniversal');
  Era.RegisterHandler(OnNet, pchar('OnTrigger ' + IntToStr(TRIGGER_NET)));
end.

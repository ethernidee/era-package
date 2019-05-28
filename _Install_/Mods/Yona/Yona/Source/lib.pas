UNIT Lib;
{
DESCRIPTION:  Library of game functions and ERM equivalents
AUTHOR:       Alexander Shostak (aka Berserker aka EtherniDee aka BerSoft)
}

(***)  INTERFACE  (***)
USES
  Windows, SysUtils, Math,
  Utils, StrLib, ConsoleAPI, DlgMes,
  Era;

TYPE
  (*  Functions  *)
  TSetCursorProc  = PROCEDURE (CursorSubType, CursorType: INTEGER); CDECL;
  TSendDataProc   = PROCEDURE (EventId: INTEGER; Data: PINTEGER; NumInts: INTEGER); CDECL;
  TRandFunc       = FUNCTION (aMin, aMax: INTEGER): INTEGER; CDECL;

CONST
  (*  Functions  *)
  SendData: TSendDataProc = Ptr($76863A);
  Rand:     TRandFunc     = Ptr($710509);
  
  (*  Sounds/Music  *)
  MAX_SOUND_VOLUME  = 9;
  MAX_MUSIC_VOLUME  = 9;
  
  (*  Creatures  *)
  NO_MON_TYPE     = -1;
  MIN_MON         = 0;
  PIKEMAN         = 0;
  HALBERDIER      = 1;
  ARCHER          = 2;
  MARKSMAN        = 3;
  SWORDSMAN       = 6;
  CRUSADER        = 7;
  CAVALIER        = 10;
  CHAMPION        = 11;
  CENTAUR         = 14;
  CENTAUR_CAPTAIN = 15;
  DWARF           = 16;
  BATTLE_DWARF    = 17;
  UNICORN         = 24;
  WAR_UNICORN     = 25;
  BLACK_KNIGHT    = 66;
  DREAD_KNIGHT    = 67;
  ORC             = 88;
  ORC_CHIEFTAIN   = 89;
  PEASANT         = 139;
  NOMAD           = 142;
  NIGHTMARE       = 172;
  SYLVAN_CENTAUR  = 192;
  HELL_STEED      = 195;
  MAX_MON         = 196;

  (*  Creature flags  *)
  FLAG_TWO_HEXED  = 1;
  FLAG_FLIER      = 2;
  FLAG_SHOOTER    = 4;
  FLAG_DEFENSE    = 134217728;

  (*  Keys  *)
  NO_KEY        = 0;
  KEY_ESC       = 27;
  KEY_F3        = 114;
  KEY_F4        = 115;
  KEY_BACKSPACE = 8;
  KEY_DELETE    = 46;

  (*  Artifacts  *)
  ART_ELVEN_BOW = 60;

  (*  Cursors  *)
  CURSOR_NORMAL = 0;
  CURSOR_BATTLE = 2;
  CURSOR_MAGIC  = 3;
  CURSOR_ART    = 4;
  
  (*  Cursors.Normal  *)
  CURSOR_NORMAL_NORMAL  = 0;
  
  (*  Cursors.Battle  *)
  CURSOR_BATTLE_NA  = 0;
  
  (*  Dialog Ids  *)
  ADVMAP_DLG      = $402AE0;
  BATTLE_DLG      = $4723E0;
  HERO_SCREEN_DLG = $4E1790;
  
  (*  Dialog Commands  *)
  DLG_CMD_SET_CAPTION       = 3;
  DLG_CMD_SET_PCX_FILENAME  = 11;

  (*  Dialog Items  *)
  ALL_DLG_ITEMS = -1;
  
  (*  Dialog Actions  *)
  ACTION_LMB_PRESSED  = 12;
  ACTION_LMB_RELEASED = 13;
  ACTION_RMB          = 14;
  
  (*  InputStrEx  *)
  ADD_ESC_BTN = TRUE;

  (*  Heroes  *)
  FIRST_HERO  = 0;
  LAST_HERO   = 155;
  NO_HERO     = -1;
  CURR_HERO   = -1;
  
  (*  Spells  *)
  SPELL_TELEPORT  = 63;
  
  (*  Colors  *)
  GOLD_COLOR  = '0FFFE794';
  RED_COLOR   = '0F2223E';
  
  TEMPLATE_CHAR = '~';
  
  (*  Battle stacks  *)
  FIRST_BATTLE_STACK  = 0;
  LAST_BATTLE_STACK   = 41;
  NO_STACK            = -1;
  
  (*  Battle actions  *)
  NO_ACTION           = 0;
  ACTION_MELEE_ATTACK = 6;
  SKIP_ACTION         = 12;
  
  (*  Battlefield parameters  *)
  NUM_BATTLE_STACKS     = LAST_BATTLE_STACK - FIRST_BATTLE_STACK + 1;
  NUMSTACKS_PER_SIDE    = NUM_BATTLE_STACKS DIV 2;
  BATTLEFIELD_LINE_SIZE = 17;
  INVALID_POS           = -1;
  FIRST_BATTLEFIELD_POS = 0;
  LAST_BATTLEFIELD_POS  = 186;
  
  (*  Battle rounds  *)
  TACTIC_ROUND  = -1;
  NO_ROUND      = LOW(INTEGER);
  
  (*  Mouse  *)
  LMB         = 0;
  SHIFT_FLAG  = 1;
  CTRL_FLAG   = 4;
  ALT_FLAG    = 32;
  RMB         = 512;
  LMB_PUSH    = 12;
  LMB_RELEASE = 13;
  
  (*  Mouse clicks  *)
  HERO_SCREEN_MIN_MON = 68;
  HERO_SCREEN_MAX_MON = 74;
  HERO_SCREEN_OK      = 30720;
  
  (*  Monster slots  *)
  MIN_MON_SLOT = 0;
  MAX_MON_SLOT = 6;
  
  (*  Towns  *)
  MIN_TOWN    = 0;
  TOWN_CASTLE = 0;
  MAX_TOWN    = 8;
  MAX_AB_TOWN = 7;
  
  (*  Msg result  *)
  MSG_RES_OK        = 0;
  MSG_RES_CANCEL    = 2;
  MSG_RES_LEFTPIC   = 0;
  MSG_RES_RIGHTPIC  = 1;
  
  (*  Dialog Pictures Types and Subtypes  *)
  NO_PIC_TYPE = -1;
  
  //  LOW LEVEL  //
  
  (*  MonInfo  *)
  MONINFO_BASE_ADDR     = $7D0C90;
  MONINFO_STRUCT_SIZE   = 116;
  MONINFO_SINGULAR_NAME = $14;
  
  (*  Combat Manager  *)
  COMBAT_BASE_ADDR        = $699420;
  COMBAT_STACKS           = 21708;
  COMBAT_ACTION           = $3C;
  COMBAT_SPELL            = $40;
  COMBAT_POS1             = $44;
  COMBAT_POS2             = $48;
  COMBAT_CURR_SIDE        = $132B8; // 0..1
  COMBAT_SIDE_STACK       = $132BC; // 0..20
  COMBAT_SIDE             = $132C0;
  COMBAT_IS_TACTIC_PHASE  = $13D68;
  COMBAT_IS_AUTOBATTLE    = $132C4;
  
  (*  Hero Window Manager  *)
  HERO_WND_MAN_PTR  = $6992D0;
  
  (*  BattleMon  *)
  STACK_STRUCT_SIZE = 1352;
  STACK_TYPE        = $34;
  STACK_POS         = $38;
  STACK_POS_SHIFT   = $44;
  STACK_NUM         = $4C;
  STACK_LOSTHP      = $58;
  STACK_FLAGS       = $84;
  STACK_HP          = $C0;
  STACK_SIDE        = $F4;
  
  (*  THero  *)
  CURR_HERO_PTR = $27F9970;
  HERO_ID       = $1E;


TYPE
  PValue  = ^TValue;
  TValue  = PACKED RECORD
    CASE BYTE OF
      0:  (v:   INTEGER);
      1:  (p:   POINTER);
      2:  (pc:  PCHAR);
  END; // .RECORD TValue

  TMesType  =
  (
    MES_MES         = 1,
    MES_QUESTION    = 2,
    MES_RMB_HINT    = 4,
    MES_CHOOSE      = 7,
    MES_MAY_CHOOSE  = 10
  );
  
  TNameType = (NAME_SINGULAR, NAME_PLURAL, NAME_DESC);

  TMonInfo  = CLASS
    PROTECTED
      fMonInd:  INTEGER;
      fAddr:    POINTER;
      fName:    ARRAY [TNameType] OF STRING;
      
      FUNCTION  GetOrigName (NameType: TNameType): STRING;
      FUNCTION  GetName (NameType: TNameType): STRING;
      PROCEDURE SetName (NameType: TNameType; CONST NewName: STRING);
      FUNCTION  GetNameZVar (NameType: TNameType): INTEGER;
      PROCEDURE SetNameZVar (NameType: TNameType; NewZVarInd: INTEGER);
      
    PUBLIC
      CONSTRUCTOR Create (MonInd: INTEGER);
      
      PROPERTY MonInd:  INTEGER READ fMonInd;
      PROPERTY Addr:    POINTER READ fAddr;
      PROPERTY OrigName[NameType: TNameType]: STRING READ GetOrigName;
      PROPERTY Name[NameType: TNameType]: STRING READ GetName WRITE SetName;
      PROPERTY NameZVar[NameType: TNameType]: INTEGER READ GetNameZVar WRITE SetNameZVar;
  END; // .CLASS TMonInfo

  TGame = CLASS
    PROTECTED
      {On}  fConsole:       ConsoleAPI.TConsole;
            fMonInfos:      ARRAY [0..HIGH(BYTE)] OF {n} TMonInfo;
            fPauseOnError:  BOOLEAN;
      
    
      {Monsters}
      FUNCTION  GetMonInfo (MonInd: INTEGER): {U} TMonInfo;
      
      {Cursors}
      FUNCTION  GetCursorLocked:  BOOLEAN;
      PROCEDURE SetCursorLocked (NewCursorLocked: BOOLEAN);
      
      {Dialogs}
      PROCEDURE SetClickIsBlocked (Value: BOOLEAN);
      FUNCTION  GetClickIsBlocked: BOOLEAN;
      
      {Sound/Music}
      FUNCTION  GetSoundVolume: INTEGER;
      PROCEDURE SetSoundVolume (NewSoundVolume: INTEGER);
      FUNCTION  GetMusicVolume: INTEGER;
      PROCEDURE SetMusicVolume (NewMusicVolume: INTEGER);
  
    PUBLIC
      {Cursors}
      PROCEDURE SetCursor (CursorType, CursorSubType: INTEGER);
      PROCEDURE LockCursor;
      PROCEDURE UnlockCursor;
      PROCEDURE SetLockedCursor (CursorType, CursorSubType: INTEGER);
      
      {Events}
      PROCEDURE BlockThisEventForERM (Event: Era.PEvent);
      
      {TCP/IP}
      (*  Up to 16 arguments  *)
      PROCEDURE FireRemoteErmEvent (EventId: INTEGER; Args: ARRAY OF INTEGER);
      
      {Sound/Music}
      PROCEDURE RestoreSoundVolume;
      PROCEDURE RestoreMusicVolume;

      {Dialogs}
      PROCEDURE PrintChatMsg (CONST Msg: STRING);
      PROCEDURE SilentChatMsg (CONST Msg: STRING);
      FUNCTION  GetDlgId: INTEGER;
      FUNCTION  GetRootDlgId: INTEGER;
      
      {Debug}
      PROCEDURE CreateConsole (CONST Title: STRING);
      PROCEDURE PrintError (CONST Error: STRING);
      
      //  PROPERTIES  //
      
      {Monsters}
      PROPERTY MonInfos[Index: INTEGER]:  {U} TMonInfo READ GetMonInfo;
      
      {Cursors}
      PROPERTY CursorLocked:  BOOLEAN READ GetCursorLocked WRITE SetCursorLocked;
      
      {Dialogs}
      PROPERTY DlgId:           INTEGER READ GetDlgId;
      PROPERTY RootDlgId:       INTEGER READ GetRootDlgId;
      PROPERTY ClickIsBlocked:  BOOLEAN READ GetClickIsBlocked WRITE SetClickIsBlocked;
      
      {Sound/Music}
      PROPERTY SoundVolume: INTEGER READ GetSoundVolume WRITE SetSoundVolume;
      PROPERTY MusicVolume: INTEGER READ GetMusicVolume WRITE SetMusicVolume;
      
      {Debug}
      PROPERTY Console:       {U} ConsoleAPI.TConsole READ fConsole;
      PROPERTY PauseOnError:  BOOLEAN READ fPauseOnError WRITE fPauseOnError;
  END; // .CLASS TGame
  
  TMonStack = RECORD
    MonType:    INTEGER;
    MonNum:     INTEGER;
    MonExp:     INTEGER;
    NumArts:    INTEGER;
    ArtType:    INTEGER;
    ArtSubtype: INTEGER;
    
    PROCEDURE Init
    (
      MonType:    INTEGER = NO_MON_TYPE;
      MonNum:     INTEGER = 0;
      MonExp:     INTEGER = 0;
      NumArts:    INTEGER = 0;
      ArtType:    INTEGER = 0;
      ArtSubtype: INTEGER = 0
    );
  END; // .RECORD TMonStack

  
VAR
{O} Game:     TGame;
    hThisDll: INTEGER;

{Low level}
PROCEDURE SetPcharValue (What: PCHAR; CONST Value: STRING; BufSize: INTEGER);
FUNCTION  GetVal (BaseAddr: POINTER; Offset: INTEGER): PValue; OVERLOAD;
FUNCTION  GetVal (BaseAddr, Offset: INTEGER): PValue; OVERLOAD;
// Offset in Combat Manager
FUNCTION  Combat (Offset: INTEGER): PValue;
FUNCTION  GetActiveStack: INTEGER;
FUNCTION  Stacks (Stack, Offset: INTEGER): PValue;
FUNCTION  MonAttr (MonId, Offset: INTEGER): PValue;
FUNCTION  CurrHero (Ofs: INTEGER): PValue;

{Colorful text}
FUNCTION  ColorizeText (CONST Str, Color: STRING): STRING; 

{Savegames}
PROCEDURE SaveInt (Value: INTEGER; CONST Section: STRING);
PROCEDURE SaveStr (CONST Str, Section: STRING);
FUNCTION  LoadInt (CONST Section: STRING): INTEGER;
FUNCTION  LoadStr (Section: STRING): STRING;

{Dialogs}
FUNCTION  Msg
(
  CONST Mes:          STRING;
        MesType:      TMesType  = MES_MES;
        Pic1Type:     INTEGER   = NO_PIC_TYPE;
        Pic1SubType:  INTEGER   = 0;
        Pic2Type:     INTEGER   = NO_PIC_TYPE;
        Pic2SubType:  INTEGER   = 0;
        Pic3Type:     INTEGER   = NO_PIC_TYPE;
        Pic3SubType:  INTEGER   = 0
): INTEGER;

PROCEDURE ParseDlg (CONST DlgFileName: STRING; DlgId: INTEGER);
FUNCTION  GetErmDlgById (DlgId: INTEGER): {n} POINTER;
PROCEDURE SendDlgCmdEx (Cmd, Param, Elem: INTEGER; Dlg: POINTER);
PROCEDURE SendDlgCmd (Cmd, Param, Elem, DlgId: INTEGER);
PROCEDURE SendDlgStrCmd (Cmd: INTEGER; CONST Param: STRING; Elem, DlgId: INTEGER);
PROCEDURE ShowDlg (DlgId: INTEGER);
PROCEDURE CloseDlg;
PROCEDURE UpdateDlgItemEx (ItemId: INTEGER; Dlg: POINTER);
PROCEDURE UpdateDlgItem (ItemId, DlgId: INTEGER);
PROCEDURE SetDlgItemHintEx (ItemId: INTEGER; CONST StaticHint: STRING; Dlg: POINTER);
PROCEDURE SetDlgItemHint (ItemId: INTEGER; CONST StaticHint: STRING; DlgId: INTEGER);

FUNCTION  InputStr (CONST Caption: STRING): STRING;
FUNCTION  InputStrEx (CONST Caption: STRING; AddEscBtn: BOOLEAN; OUT Aborted: BOOLEAN): STRING;
FUNCTION  DoInputNum
(
  CONST Caption:  STRING;
        Min:      INTEGER = LOW(INTEGER);
        Max:      INTEGER = HIGH(INTEGER)
): INTEGER;

{Battle}
FUNCTION  IsTacticPhase: BOOLEAN;
FUNCTION  IsAutoBattle: BOOLEAN;
PROCEDURE UpdateShadow;
FUNCTION  CalculateDistance (SrcPos, DstPos: INTEGER): INTEGER;
FUNCTION  CalcNumKilled (Damage, LostHP, UnitHP: INTEGER): INTEGER;
PROCEDURE SetBattleHint (CONST Hint: STRING);
PROCEDURE WriteBattleLog (CONST Str: STRING);

{Hero}
PROCEDURE GetHeroStack (SlotN, HeroId: INTEGER; OUT MonStack: TMonStack);
PROCEDURE SetHeroStack (SlotN, HeroId: INTEGER; CONST MonStack: TMonStack);

{Texts}
// Deletes #13 from string
FUNCTION  ToH3Text (CONST Txt: STRING): STRING;


(***) IMPLEMENTATION (***)


CONST
  (*  Variables  *)
  IsCursorLocked:   PLONGBOOL = Ptr($840E10);
  MusicVolume:      PINTEGER  = Ptr($6987B0);
  SoundVolume:      PINTEGER  = Ptr($6987B4);
  LastMusicVolume:  PINTEGER  = Ptr($6987B8);
  LastSoundVolume:  PINTEGER  = Ptr($6987BC);
  DefClickReaction: PLONGBOOL = Ptr($A4AAFC);
  
  (*  Functions  *)
  SetCursor:  TSetCursorProc  = Ptr($716D9A);


PROCEDURE AssertHandler (CONST Mes, FileName: STRING; LineNumber: INTEGER; Address: POINTER);
BEGIN
  DlgMes.MsgError(StrLib.BuildStr(
    'Assert violation in file "~FileName~" on line ~Line~.'#13#10'Error at address ~Address~.',
    [
      'FileName', FileName,
      'Line',     SysUtils.IntToStr(LineNumber),
      'Address',  SysUtils.Format('%x', [INTEGER(Address)])
    ],
    TEMPLATE_CHAR
  ));
  
  RAISE Exception.Create('Assert Violation');
END; // .PROCEDURE AssertHandler
  
FUNCTION GetVal (BaseAddr: POINTER; Offset: INTEGER): PValue; OVERLOAD;
BEGIN
  RESULT  :=  Utils.PtrOfs(BaseAddr, Offset);
END; // .FUNCTION GetVal

FUNCTION GetVal (BaseAddr, Offset: INTEGER): PValue; OVERLOAD;
BEGIN
  RESULT  :=  Utils.PtrOfs(Ptr(BaseAddr), Offset);
END; // .FUNCTION GetVal

PROCEDURE SetPcharValue (What: PCHAR; CONST Value: STRING; BufSize: INTEGER);
VAR
  NumBytesToCopy: INTEGER;
   
BEGIN
  {!} ASSERT(What <> NIL);
  {!} ASSERT(BufSize > 0);
  NumBytesToCopy  :=  Math.Min(LENGTH(Value), BufSize - 1);
  
  IF NumBytesToCopy > 0 THEN BEGIN
    Utils.CopyMem(LENGTH(Value), PCHAR(Value), What);
  END; // .IF
  
  Utils.PCharByte(Utils.PtrOfs(What, NumBytesToCopy))^  :=  #0;
END; // .PROCEDURE SetPcharValue

PROCEDURE SaveStr (CONST Str, Section: STRING);
VAR
  StrLen: INTEGER;
   
BEGIN
  StrLen  :=  LENGTH(Str);
  Era.WriteSavegameSection(SIZEOF(StrLen), @StrLen, PCHAR(Section));
  
  IF StrLen > 0 THEN BEGIN
    Era.WriteSavegameSection(StrLen, PCHAR(Str), PCHAR(Section));
  END; // .IF
END; // .PROCEDURE SaveStr

PROCEDURE SaveInt (Value: INTEGER; CONST Section: STRING);
BEGIN
  Era.WriteSavegameSection(SIZEOF(Value), @Value, PCHAR(Section));
END; // .PROCEDURE SaveInt

FUNCTION LoadStr (Section: STRING): STRING;
VAR
  StrLen: INTEGER;
   
BEGIN
  StrLen  :=  0;
  Era.ReadSavegameSection(SIZEOF(StrLen), @StrLen, PCHAR(Section));
  SetLength(RESULT, StrLen);
  
  IF StrLen > 0 THEN BEGIN
    Era.ReadSavegameSection(StrLen, POINTER(RESULT), PCHAR(Section));
  END; // .IF
END; // .FUNCTION LoadStr

FUNCTION LoadInt (CONST Section: STRING): INTEGER;
BEGIN
  RESULT  :=  0;
  Era.ReadSavegameSection(SIZEOF(RESULT), @RESULT, PCHAR(Section));
END; // .FUNCTION LoadInt

FUNCTION CurrHero (Ofs: INTEGER): PValue;
BEGIN
  RESULT  :=  Utils.PtrOfs(PPOINTER(CURR_HERO_PTR)^, Ofs);
END; // .FUNCTION CurrHero

FUNCTION Combat (Offset: INTEGER): PValue;
BEGIN
  {!} ASSERT(Offset >= 0);
  RESULT  :=  GetVal(PINTEGER(COMBAT_BASE_ADDR)^, Offset);
END; // .FUNCTION Combat

FUNCTION GetActiveStack: INTEGER;
BEGIN
  RESULT  :=  Combat(COMBAT_CURR_SIDE).v * NUMSTACKS_PER_SIDE + Combat(COMBAT_SIDE_STACK).v;
END; // .FUNCTION GetActiveStack

FUNCTION Stacks (Stack, Offset: INTEGER): PValue;
BEGIN
  {!} ASSERT(Math.InRange(Stack, FIRST_BATTLE_STACK, LAST_BATTLE_STACK));
  {!} ASSERT(Offset >= 0);
  RESULT  :=  GetVal(Combat(COMBAT_STACKS), STACK_STRUCT_SIZE * Stack + Offset);
END; // .FUNCTION Stacks

FUNCTION MonAttr (MonId, Offset: INTEGER): PValue;
BEGIN
  RESULT  :=  Utils.PtrOfs(Era.GetRealAddr(Ptr($7D0C90)), MonId * 116 + Offset);
END; // .FUNCTION MonAttr

FUNCTION ColorizeText (CONST Str, Color: STRING): STRING;
BEGIN
  RESULT  :=  '{~' + Color + '}' + Str + '{~}';
END; // .FUNCTION ColorizeText

PROCEDURE PrintChatMsg (Msg: PCHAR); ASSEMBLER;
ASM
  PUSH Msg
  PUSH $69D800
  MOV EAX, $553C40
  CALL EAX
  ADD ESP, $8
END; // .PROCEDURE PrintChatMsg

FUNCTION Msg
(
  CONST Mes:          STRING;
        MesType:      TMesType  = MES_MES;
        Pic1Type:     INTEGER   = NO_PIC_TYPE;
        Pic1SubType:  INTEGER   = 0;
        Pic2Type:     INTEGER   = NO_PIC_TYPE;
        Pic2SubType:  INTEGER   = 0;
        Pic3Type:     INTEGER   = NO_PIC_TYPE;
        Pic3SubType:  INTEGER   = 0
): INTEGER;

VAR
  MesStr:     PCHAR;
  MesTypeInt: INTEGER;
  Res:        INTEGER;
  
BEGIN
  MesStr      :=  PCHAR(Mes);
  MesTypeInt  :=  ORD(MesType);

  ASM
    MOV ECX, MesStr
    PUSH Pic3SubType
    PUSH Pic3Type
    PUSH -1
    PUSH -1
    PUSH Pic2SubType
    PUSH Pic2Type
    PUSH Pic1SubType
    PUSH Pic1Type
    PUSH -1
    PUSH -1 
    MOV EAX, $4F6C00
    MOV EDX, MesTypeInt
    CALL EAX
    MOV EAX, [HERO_WND_MAN_PTR]
    MOV EAX, [EAX + $38]
    MOV Res, EAX
  END; // .ASM
  
  RESULT  :=  MSG_RES_OK;
  
  IF MesType = MES_QUESTION THEN BEGIN
    IF Res = 30726 THEN BEGIN
      RESULT  :=  MSG_RES_CANCEL;
    END // .IF
  END // .IF
  ELSE IF MesType IN [MES_CHOOSE, MES_MAY_CHOOSE] THEN BEGIN
    CASE Res OF 
      30729:  RESULT  :=  MSG_RES_LEFTPIC;
      30730:  RESULT  :=  MSG_RES_RIGHTPIC;
    ELSE
      RESULT  :=  MSG_RES_CANCEL;
    END; // .SWITCH Res
  END; // .ELSEIF
END; // .FUNCTION Msg

PROCEDURE ParseDlg (CONST DlgFileName: STRING; DlgId: INTEGER);
BEGIN
  Era.y[1]  :=  DlgId;
  SetPcharValue(@Era.z[1], DlgFileName, SIZEOF(Era.z[1]));
  Era.ExecErmCmd('DLy1:Nz1;');
END; // .PROCEDURE ParseDlg

FUNCTION GetErmDlgById (DlgId: INTEGER): {n} POINTER; ASSEMBLER;
ASM
  PUSH DlgId
  MOV EAX, $729AD3
  CALL EAX
  ADD ESP, 4
END; // .FUNCTION GetErmDlgById

PROCEDURE SendDlgCmdEx (Cmd, Param, Elem: INTEGER; Dlg: POINTER);
BEGIN
  {!} ASSERT(Dlg <> NIL);
  ASM
    MOV ECX, Dlg
    PUSH Param
    PUSH Elem
    PUSH Cmd
    MOV EAX, $729992
    CALL EAX
  END; // .ASM
END; // .PROCEDURE SendDlgCmdEx

PROCEDURE SendDlgCmd (Cmd, Param, Elem, DlgId: INTEGER);
BEGIN
  SendDlgCmdEx(Cmd, Param, Elem, GetErmDlgById(DlgId));
END; // .PROCEDURE SendDlgCmd

PROCEDURE SendDlgStrCmd (Cmd: INTEGER; CONST Param: STRING; Elem, DlgId: INTEGER);
BEGIN
  SendDlgCmd(Cmd, INTEGER(PCHAR(Param)), Elem, DlgId);
END; // .PROCEDURE SendDlgStrCmd

PROCEDURE ShowDlg (DlgId: INTEGER);
BEGIN
  Era.y[1]  :=  DlgId;
  Era.ExecErmCmd('DLy1:S?y2;');
END; // .PROCEDURE ShowDlg

PROCEDURE CloseDlg;
BEGIN
  Era.ExecErmCmd('DL:C1;');
END; // .PROCEDURE CloseDlg

PROCEDURE UpdateDlgItemEx (ItemId: INTEGER; Dlg: POINTER);
BEGIN
  {!} ASSERT(Dlg <> NIL);
  ASM
    MOV ECX, Dlg
    PUSH ItemId
    MOV EAX, $7299FD
    CALL EAX
  END; // .ASM
END; // .PROCEDURE UpdateDlgItemEx

PROCEDURE UpdateDlgItem (ItemId, DlgId: INTEGER);
BEGIN
  UpdateDlgItemEx(ItemId, GetErmDlgById(DlgId));
END; // .PROCEDURE UpdateDlgItem

PROCEDURE SetDlgItemHintEx (ItemId: INTEGER; CONST StaticHint: STRING; Dlg: POINTER);
VAR
  Hint: PCHAR;

BEGIN
  {!} ASSERT(Dlg <> NIL);
  Hint  :=  PCHAR(StaticHint);
  
  ASM
    PUSH Hint
    PUSH ItemId
    MOV ECX, Dlg
    MOV EAX, $7297CF
    CALL EAX
  END; // .ASM
END; // .PROCEDURE SetDlgItemHintEx

PROCEDURE SetDlgItemHint (ItemId: INTEGER; CONST StaticHint: STRING; DlgId: INTEGER);
BEGIN
  SetDlgItemHintEx(ItemId, StaticHint, GetErmDlgById(DlgId));
END; // .PROCEDURE SetDlgItemHint

FUNCTION InputStrEx (CONST Caption: STRING; AddEscBtn: BOOLEAN; OUT Aborted: BOOLEAN): STRING;
BEGIN
  SetPcharValue(@Era.z[1], Caption, SIZEOF(Era.z[1]));
  Era.y[1]  :=  INTEGER(AddEscBtn);
  SetPcharValue(@Era.z[2], '', SIZEOF(Era.z[1]));
  Era.ExecErmCmd(PCHAR('IF:D99/2/1/2/2/2/2/2/2/2/2/2/2/2/2/2 F99/2/2/2/2/y1 E1/99;'));
  Aborted :=  AddEscBtn AND (Era.v[1] = -1);
  RESULT  :=  PCHAR(@Era.z[1]);
END; // .FUNCTION InputStrEx

FUNCTION InputStr (CONST Caption: STRING): STRING;
VAR
  Aborted:  BOOLEAN;

BEGIN
  RESULT  :=  InputStrEx(Caption, NOT ADD_ESC_BTN, Aborted);
END; // .FUNCTION InputStr

FUNCTION DoInputNum
(
  CONST Caption:  STRING;
        Min:      INTEGER = LOW(INTEGER);
        Max:      INTEGER = HIGH(INTEGER)
): INTEGER;

VAR
  ValidNum: BOOLEAN;
  Input:    STRING;

BEGIN
  ValidNum  :=  FALSE;

  WHILE NOT ValidNum DO BEGIN
    Input     :=  InputStr(Caption);
    ValidNum  :=  SysUtils.TryStrToInt(Input, RESULT) AND Math.InRange(RESULT, Min, Max);
  END; // .WHILE
END; // .FUNCTION DoInputNum

FUNCTION IsTacticPhase: BOOLEAN;
BEGIN
  RESULT  :=  Combat(COMBAT_IS_TACTIC_PHASE).v = 1;
END; // .FUNCTION IsTacticPhase

FUNCTION IsAutoBattle: BOOLEAN;
BEGIN
  RESULT  :=  Combat(COMBAT_IS_AUTOBATTLE).v = 1;
END; // .FUNCTION IsAutoBattle

PROCEDURE UpdateShadow; ASSEMBLER;
ASM
  MOV ECX, [$699420]
  PUSH 1
  PUSH 0
  MOV EAX, $4934B0
  CALL EAX
END; // .PROCEDURE UpdateShadow

FUNCTION CalculateDistance (SrcPos, DstPos: INTEGER): INTEGER;
VAR
  DistanceX:  INTEGER;
  DistanceY:  INTEGER;
  x1, x2:     INTEGER;
  y1, y2:     INTEGER;

BEGIN
  x1  :=  SrcPos MOD BATTLEFIELD_LINE_SIZE;
  y1  :=  SrcPos DIV BATTLEFIELD_LINE_SIZE;
  x2  :=  DstPos MOD BATTLEFIELD_LINE_SIZE;
  y2  :=  DstPos DIV BATTLEFIELD_LINE_SIZE;

  DistanceY :=  ABS(y1 - y2);
  DistanceX :=  ABS(x1 * 2 - (y1 AND 1) - x2 * 2 + (y2 AND 1)) - DistanceY;
  
  RESULT  :=  (DistanceY * 2 + Math.Max(DistanceX, 0)) DIV 2;
END; // .FUNCTION CalculateDistance

FUNCTION CalcNumKilled (Damage, LostHP, UnitHP: INTEGER): INTEGER;
VAR
  LastUnitHPLeft: INTEGER;

BEGIN
  RESULT  :=  0;
  
  LastUnitHPLeft  :=  UnitHP - LostHP;
  IF Damage >= LastUnitHPLeft THEN BEGIN
    INC(RESULT);
    Damage  :=  Damage - LastUnitHPLeft;
  END; // .IF
  
  RESULT  :=  RESULT + Damage DIV UnitHP;
END; // .FUNCTION CalcNumKilled

PROCEDURE SetBattleHint (CONST Hint: STRING);
BEGIN
  SetPcharValue(@Era.z[1], Hint, SIZEOF(Era.z[1]));
  Era.ExecErmCmd('MM:Mz1;');
END; // .PROCEDURE SetBattleHint

PROCEDURE WriteBattleLog (CONST Str: STRING);
BEGIN
  SetPcharValue(@Era.z[1], Str, SIZEOF(Era.z[1]));
  Era.ExecErmCmd('MM:Sz1;');
END; // .PROCEDURE WriteBattleLog

PROCEDURE GetHeroStack (SlotN, HeroId: INTEGER; OUT MonStack: TMonStack);
BEGIN
  Era.y[1]  :=  HeroId;
  Era.y[2]  :=  SlotN;
  Era.ExecErmCmd('HEy1:C0/y2/?y3/?y4/?y5;');
  Era.ExecErmCmd('EXy1/y2:R?y6/?y7/?y8/?y9;');
  MonStack.Init(Era.y[3], Era.y[4], Era.y[5], Era.y[6] + Era.y[9], Era.y[7], Era.y[8]);
END; // .PROCEDURE GetHeroStack

PROCEDURE SetHeroStack (SlotN, HeroId: INTEGER; CONST MonStack: TMonStack);
BEGIN
  Era.y[1]  :=  HeroId;
  Era.y[2]  :=  SlotN;
  Era.y[3]  :=  MonStack.MonType;
  Era.y[4]  :=  MonStack.MonNum;
  Era.y[5]  :=  MonStack.MonExp;
  Era.y[6]  :=  INTEGER(MonStack.NumArts > 0);
  Era.y[7]  :=  MonStack.ArtType;
  Era.y[8]  :=  MonStack.ArtSubtype;
  Era.y[9]  :=  MonStack.NumArts - Era.y[6];
  Era.ExecErmCmd('HEy1:C0/y2/y3/y4/y5;');
  Era.ExecErmCmd('EXy1/y2:Ry6/y7/y8/y9;');
END; // .PROCEDURE SetHeroStack

FUNCTION ToH3Text (CONST Txt: STRING): STRING;
BEGIN
  RESULT  :=  SysUtils.StringReplace(Txt, #13, '', [SysUtils.rfReplaceAll]);
END; // .FUNCTION ToH3Text

CONSTRUCTOR TMonInfo.Create (MonInd: INTEGER);
BEGIN
  {!} ASSERT(Math.InRange(MonInd, 0, HIGH(BYTE)));
  Self.fMonInd  :=  MonInd;
  Self.fAddr    :=  GetVal(Era.GetRealAddr(Ptr(MONINFO_BASE_ADDR)), MonInd * MONINFO_STRUCT_SIZE);
END; // .CONSTRUCTOR TMonInfo.Create 

FUNCTION TMonInfo.GetOrigName (NameType: TNameType): STRING;
BEGIN
  CASE NameType OF 
    NAME_SINGULAR:  RESULT  :=  PCHAR(Utils.PtrOfs(Era.GetRealAddr(Ptr($A498A8)), Self.MonInd * 4)); 
    NAME_PLURAL:    RESULT  :=  PCHAR(Utils.PtrOfs(Era.GetRealAddr(Ptr($A48128)), Self.MonInd * 4)); 
    NAME_DESC:      RESULT  :=  PCHAR(Utils.PtrOfs(Era.GetRealAddr(Ptr($A88E78)), Self.MonInd * 4)); 
  END; // .SWITCH NameType
END; // .FUNCTION TMonInfo.GetOrigName

FUNCTION TMonInfo.GetName (NameType: TNameType): STRING;
BEGIN
  RESULT  :=  GetVal(Self.fAddr, MONINFO_SINGULAR_NAME + ORD(NameType) * 4).pc;
END; // .FUNCTION TMonInfo.GetName

PROCEDURE TMonInfo.SetName (NameType: TNameType; CONST NewName: STRING);
BEGIN
  Self.fName[NameType]  :=  NewName;
  GetVal(Self.fAddr, MONINFO_SINGULAR_NAME + ORD(NameType) * 4).pc  :=  PCHAR(NewName);
  
  CASE NameType OF 
    NAME_SINGULAR:  GetVal(Era.GetRealAddr(Ptr($7C8240)), Self.MonInd * 4).pc  :=  PCHAR(NewName);
    NAME_PLURAL:    GetVal(Era.GetRealAddr(Ptr($7B6650)), Self.MonInd * 4).pc  :=  PCHAR(NewName);
    NAME_DESC:      GetVal(Era.GetRealAddr(Ptr($7C4018)), Self.MonInd * 4).pc  :=  PCHAR(NewName);
  END; // .SWITCH NameType
END; // .PROCEDURE TMonInfo.SetName

FUNCTION TMonInfo.GetNameZVar (NameType: TNameType): INTEGER;
BEGIN
  RESULT  :=  GetVal(Era.GetRealAddr(Ptr($A48440)), Self.MonInd * 12 + ORD(NameType) * 4).v;
END; // .FUNCTION TMonInfo.GetNameZVar

PROCEDURE TMonInfo.SetNameZVar (NameType: TNameType; NewZVarInd: INTEGER);
BEGIN
  {!} ASSERT(Math.InRange(NewZVarInd, LOW(Era.TErmZVars), HIGH(Era.TErmZVars)));
  GetVal(Era.GetRealAddr(Ptr($A48440)), Self.MonInd * 12 + ORD(NameType) * 4).v :=  NewZVarInd;
END; // .PROCEDURE TMonInfo.SetNameZVar

FUNCTION TGame.GetCursorLocked: BOOLEAN;
BEGIN
  RESULT  :=  IsCursorLocked^;
END; // .FUNCTION GetCursorLocked

PROCEDURE TGame.SetCursorLocked (NewCursorLocked: BOOLEAN);
BEGIN
  IsCursorLocked^ :=  NewCursorLocked;
END; // .PROCEDURE TGame.SetCursorLocked

PROCEDURE TGame.LockCursor;
BEGIN
  Self.CursorLocked :=  TRUE;
END; // .PROCEDURE TGame.LockCursor

PROCEDURE TGame.UnlockCursor;
BEGIN
  Self.CursorLocked :=  FALSE;
END; // .PROCEDURE TGame.UnlockCursor

PROCEDURE TGame.SetCursor (CursorType, CursorSubType: INTEGER);
BEGIN
  Lib.SetCursor(CursorSubType, CursorType);
END; // .PROCEDURE TGame.SetCursor

PROCEDURE TGame.SetLockedCursor (CursorType, CursorSubType: INTEGER);
BEGIN
  Self.UnlockCursor;
  Self.SetCursor(CursorType, CursorSubType);
  Self.LockCursor;
END; // .PROCEDURE TGame.SetLockedCursor

PROCEDURE TGame.BlockThisEventForERM (Event: Era.PEvent);
BEGIN
  PLONGBOOL(Event.Data)^  :=  TRUE;
END; // .PROCEDURE TGame.BlockThisEventForERM

PROCEDURE TGame.FireRemoteErmEvent (EventId: INTEGER; Args: ARRAY OF INTEGER);
BEGIN
  {!} ASSERT(LENGTH(Args) <= 16);
  IF LENGTH(Args) = 0 THEN BEGIN
    SendData(EventId, NIL, 0);
  END // .IF
  ELSE BEGIN
    SendData(EventId, @Args[0], LENGTH(Args));
  END; // .ELSE
END; // .PROCEDURE TGame.FireRemoteErmEvent

FUNCTION TGame.GetMonInfo (MonInd: INTEGER): {U} TMonInfo;
BEGIN
  {!} ASSERT(Math.InRange(MonInd, 0, HIGH(Self.fMonInfos)));
  RESULT  :=  Self.fMonInfos[MonInd];
  
  IF RESULT = NIL THEN BEGIN
    Self.fMonInfos[MonInd]  :=  TMonInfo.Create(MonInd);
    RESULT                  :=  Self.fMonInfos[MonInd];
  END; // .IF
END; // .FUNCTION TGame.GetMonInfo

FUNCTION TGame.GetSoundVolume: INTEGER;
BEGIN
  RESULT  :=  Lib.SoundVolume^;
END; // .FUNCTION TGame.GetSoundVolume

PROCEDURE TGame.SetSoundVolume (NewSoundVolume: INTEGER);
BEGIN
  {!} ASSERT(Math.InRange(NewSoundVolume, 0, MAX_SOUND_VOLUME));
  Lib.LastSoundVolume^  :=  Self.SoundVolume;
  Lib.SoundVolume^      :=  NewSoundVolume;
END; // .PROCEDURE TGame.SetSoundVolume

FUNCTION TGame.GetMusicVolume: INTEGER;
BEGIN
  RESULT  :=  Lib.MusicVolume^;
END; // .FUNCTION TGame.GetSoundVolume

PROCEDURE TGame.SetMusicVolume (NewMusicVolume: INTEGER);
BEGIN
  {!} ASSERT(Math.InRange(NewMusicVolume, 0, MAX_MUSIC_VOLUME));
  Lib.LastMusicVolume^  :=  Self.MusicVolume;
  Lib.MusicVolume^      :=  NewMusicVolume;
END; // .PROCEDURE TGame.SetMusicVolume

PROCEDURE TGame.RestoreSoundVolume;
BEGIN
  Self.SoundVolume  :=  LastSoundVolume^;
END; // .PROCEDURE TGame.RestoreSoundVolume

PROCEDURE TGame.RestoreMusicVolume;
BEGIN
  Self.MusicVolume  :=  LastMusicVolume^;
END; // .PROCEDURE TGame.RestoreMusicVolume

PROCEDURE TGame.PrintChatMsg (CONST Msg: STRING);
BEGIN
  Lib.PrintChatMsg(PCHAR(Msg));
END; // .PROCEDURE TGame.PrintChatMsg

PROCEDURE TGame.SilentChatMsg (CONST Msg: STRING);
BEGIN
  Self.SoundVolume  :=  0;
  Self.PrintChatMsg(Msg);
  Self.RestoreSoundVolume;
END; // .PROCEDURE TGame.SilentChatMsg

FUNCTION TGame.GetDlgId: INTEGER;
VAR
  GameState:  Era.TGameState;

BEGIN
  Era.GetGameState(GameState);
  RESULT  :=  GameState.CurrentDlgId;
END; // .FUNCTION TGame.GetDlgId

FUNCTION TGame.GetRootDlgId: INTEGER;
VAR
  GameState:  Era.TGameState;

BEGIN
  Era.GetGameState(GameState);
  RESULT  :=  GameState.RootDlgId;
END; // .FUNCTION TGame.GetRootDlgId

FUNCTION TGame.GetClickIsBlocked: BOOLEAN;
BEGIN
  RESULT  :=  NOT DefClickReaction^;
END; // .FUNCTION TGame.GetClickIsBlocked

PROCEDURE TGame.SetClickIsBlocked (Value: BOOLEAN);
BEGIN
  DefClickReaction^ :=  NOT Value;
END; // .PROCEDURE TGame.SetClickIsBlocked

PROCEDURE TGame.CreateConsole (CONST Title: STRING);
BEGIN
  SysUtils.FreeAndNil(Self.fConsole);
  Self.fConsole :=  ConsoleAPI.TConsole.Create(Title, 100, 50, 100, 1000);
END; // .PROCEDURE TGame.CreateConsole

PROCEDURE TGame.PrintError (CONST Error: STRING);
BEGIN
  IF Self.fConsole <> NIL THEN BEGIN
    WriteLn(Error + #13#10);
    
    IF Self.fPauseOnError THEN BEGIN
      Self.fConsole.ReadKey;
    END; // .IF
  END; // .IF
END; // .PROCEDURE TGame.PrintError

PROCEDURE TMonStack.Init
(
  MonType:    INTEGER = NO_MON_TYPE;
  MonNum:     INTEGER = 0;
  MonExp:     INTEGER = 0;
  NumArts:    INTEGER = 0;
  ArtType:    INTEGER = 0;
  ArtSubtype: INTEGER = 0
);

BEGIN
  Self.MonType    :=  MonType;
  Self.MonNum     :=  MonNum;
  Self.MonExp     :=  MonExp;
  Self.NumArts    :=  NumArts;
  Self.ArtType    :=  ArtType;
  Self.ArtSubtype :=  ArtSubtype;
END; // .PROCEDURE TMonStack.Init

BEGIN
  (* System *)
  AssertErrorProc           :=  AssertHandler;
  SysUtils.DecimalSeparator :=  '.';
  hThisDll                  :=  SysInit.hInstance;

  Game  :=  TGame.Create;
END.

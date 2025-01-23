library Erm_Hooker;

uses
  SysUtils,

  DataLib,
  DlgMes,
  Files,
  FilesEx,
  Lists,
  StrLib,
  Utils,

  Era in '..\..\Era\Era.pas';

{$R *.RES}

var
(* Map of hook address => THookData *)
{O} Hooks: {O} TObjDict {OF THookData};

const
  MIN_HOOK_SIZE        = 5;
  MAX_HOOK_SIZE        = 16;
  DEBUG_DIR            = 'Debug\Era';
  DEBUG_ERM_HOOKS_PATH = 'Debug\Era\erm hooks.txt';
  VERSION_STR          = '{Erm Hooker} v3.1.0';

  ALL_HANDLERS = 0;

type
  THookData = class;

  PBridgeCode = ^TBridgeCode;
  TBridgeCode = packed record
    PopEax:         byte;
    PushConst32:    byte;
    HookDataPtr:    pointer;
    PushEax:        byte;
    MovEaxConst32:  byte;
    HookHandler:    pointer;
    JmpEax:         word;
    Padding:        array [1..2] of byte;

    procedure Init ({U} HookData: THookData; aHookHandler: pointer);
  end; // .record TBridgeCode

  THookData = class
    {O} Handlers:     Lists.TList {OF ErmFunc: INTEGER};
    {O} BridgeCode:   PBridgeCode;
    {O} AppliedPatch: pointer; {needs RollbackAppliedPatch for deallocation}
    {U} Addr:         pointer;
        PatchSize:    integer;

    constructor Create;
    destructor  Destroy; override;
  end;

constructor THookData.Create;
begin
  Self.Handlers := Lists.NewSimpleList();
end;

destructor THookData.Destroy;
begin
  Handlers.Free();
  FreeMem(BridgeCode); BridgeCode := nil;
end;

procedure TBridgeCode.Init ({U} HookData: THookData; aHookHandler: pointer);
begin
  {!} Assert(aHookHandler <> nil);
  PopEax        := $58;
  PushConst32   := $68;
  HookDataPtr   := pointer(HookData);
  PushEax       := $50;
  MovEaxConst32 := $B8;
  HookHandler   := aHookHandler;
  JmpEax        := $E0FF;
end;

function CanUnsetHook (HookData: THookData): boolean;
begin
  {!} Assert(HookData <> nil);
  result := not Era.IsPatchOverwritten(HookData.AppliedPatch);
end;

procedure DoUnsetHook (HookData: THookData);
begin
  {!} Assert(HookData <> nil);
  Era.RollbackAppliedPatch(HookData.AppliedPatch);
  Hooks.DeleteItem(HookData.Addr);
end;

function OnErmCustomHook ({U} HookData: THookData; Context: PHookContext): longbool; stdcall;
var
  ArgXVars: Era.PErmXVars;
  i:        integer;

begin
  ArgXVars := Era.GetArgXVars;
  result   := true;
  i        := 0;

  while i < HookData.Handlers.Count do begin
    ArgXVars[1] := integer(Context);
    ArgXVars[2] := integer(ord(true));
    Era.FireErmEvent(integer(HookData.Handlers[i]));
    result      := Era.GetRetXVars()[2] <> 0;

    if not result then begin
      break;
    end;

    inc(i);
  end;
end;

function SetHook (Addr: pointer; ErmHandlerFunc: integer): longbool; stdcall;
var
{U}  HookData:       THookData;
{Un} OldHook:        THookData;
     IsHookConflict: longbool;
     NumHandlers:    integer;
     i:              integer;

begin
  {!} Assert(Addr <> nil);
  HookData := Hooks[Addr];
  OldHook  := nil;
  // * * * * * //
  result := false;

  if HookData = nil then begin
    HookData            := THookData.Create;
    HookData.Addr       := Addr;
    HookData.BridgeCode := New(PBridgeCode);
    HookData.BridgeCode.Init(HookData, @OnErmCustomHook);

    Era.Hook(Addr, pointer(HookData.BridgeCode), @HookData.AppliedPatch);

    HookData.PatchSize := Era.GetAppliedPatchSize(HookData.AppliedPatch);
    IsHookConflict     := false;

    for i := 1 to MAX_HOOK_SIZE - 1 do begin
      OldHook := Hooks[Utils.PtrOfs(Addr, -i)];

      if (OldHook <> nil) and (cardinal(OldHook.Addr) + cardinal(OldHook.PatchSize) > cardinal(Addr)) then begin
        IsHookConflict := true;
        break;
      end;
    end;

    if not IsHookConflict then begin
      for i := 1 to HookData.PatchSize - 1 do begin
        OldHook := Hooks[Utils.PtrOfs(Addr, i)];

        if OldHook <> nil then begin
          IsHookConflict := true;
          break;
        end;
      end;
    end;

    if IsHookConflict then begin
      Era.RollbackAppliedPatch(HookData.AppliedPatch);
      SysUtils.FreeAndNil(HookData);
      Era.ShowMessage(pchar(SysUtils.Format('ErmHooker: cannot set hook at %x, because it will overwrite another ERM hook at %x', [integer(Addr), integer(OldHook.Addr)])));
      exit;
    end;

    Hooks[Addr] := HookData;
  end; // .if

  i           := 0;
  NumHandlers := HookData.Handlers.Count;

  while (i < NumHandlers) and (integer(HookData.Handlers[i]) <> ErmHandlerFunc) do begin
    inc(i);
  end;

  result := i >= NumHandlers;

  if result then begin
    HookData.Handlers.Add(pointer(ErmHandlerFunc));
  end;
end; // .function SetHook

function UnsetHook (Addr: pointer; ErmHandlerFunc: integer): longbool; stdcall;
var
{U} HookData:    THookData;
    NumHandlers: integer;
    i:           integer;

begin
  {!} Assert(Addr <> nil);
  HookData := THookData(Hooks[Addr]);
  // * * * * * //
  result := HookData <> nil;

  if result then begin
    if ErmHandlerFunc = ALL_HANDLERS then begin
      HookData.Handlers.Clear();
    end else begin
      i           := 0;
      NumHandlers := HookData.Handlers.Count;

      while (i < NumHandlers) and (integer(HookData.Handlers[i]) <> ErmHandlerFunc) do begin
        inc(i);
      end;

      result := i < NumHandlers;

      if result then begin
        HookData.Handlers.Delete(i);
      end;
    end; // .else

    if (HookData.Handlers.Count = 0) and CanUnsetHook(HookData) then begin
      DoUnsetHook(HookData);
    end;
  end; // .if
end; // .function UnsetHook

procedure PrintHooks; stdcall;
var
{O} HooksAddrs:  DataLib.TList;
{O} TriggerName: pchar;
{U} HookData:    THookData;
    LineStr:     string;
    Addr:        pointer;
    i, j:        integer;

begin
  HooksAddrs  := GetObjDictKeys(Hooks);
  HookData    := nil;
  TriggerName := nil;
  // * * * * * //
  Files.ForcePath(DEBUG_DIR); // For manual call not in debug event
  HooksAddrs.Sort;

  with FilesEx.WriteFormattedOutput(DEBUG_ERM_HOOKS_PATH) do begin
    Line('> Format: [Address] (Hook size) => [ERM Function], [ERM Function...]');
    EmptyLine;

    for i := 0 to HooksAddrs.Count - 1 do begin
      Addr     := HooksAddrs[i];
      HookData := THookData(Hooks[Addr]);
      LineStr  := SysUtils.Format('%s (%d) => ', [IntToHex(integer(Addr), 8), HookData.PatchSize]);

      for j := 0 to HookData.Handlers.Count - 1 do begin
        if j > 0 then begin
          LineStr := LineStr + ', ';
        end;

        TriggerName := Era.GetTriggerReadableName(integer(HookData.Handlers[j]));
        LineStr     := LineStr + TriggerName;
        Era.MemFree(TriggerName); TriggerName := nil;
      end;

      Line(LineStr);
    end; // .for
  end; // .with
  // * * * * * //
  SysUtils.FreeAndNil(HooksAddrs);
  Era.MemFree(TriggerName);
end; // .procedure PrintHooks

procedure OnResetHooks (Event: PEvent); stdcall;
var
{U} HookData: THookData;

begin
  HookData := nil;
  // * * * * * //
  with IterateObjDict(Hooks) do begin
    while IterNext do begin
      HookData := THookData(IterValue);
      HookData.Handlers.Clear();

      if CanUnsetHook(HookData) then begin
        DoUnsetHook(HookData);
      end;
    end;
  end;
end;

procedure OnReportVersion (Event: PEvent); stdcall;
begin
  Era.ReportPluginVersion(VERSION_STR);
end;

procedure OnGenerateDebugInfo (Event: PEvent); stdcall;
begin
  PrintHooks;
end;

procedure AssertHandler (const Mes, FileName: string; LineNumber: integer; Address: pointer);
var
  CrashMes: string;

begin
  CrashMes := StrLib.BuildStr
  (
    'Assert violation in file "~FileName~" on line ~Line~.'#13#10'Error at address: $~Address~.'#13#10'Message: "~Message~"',
    [
      'FileName', FileName,
      'Line',     SysUtils.IntToStr(LineNumber),
      'Address',  SysUtils.Format('%x', [integer(Address)]),
      'Message',  Mes
    ],
    '~'
  );

  DlgMes.MsgError(CrashMes);

  // Better callstack
  pinteger(0)^ := 0;
end;

exports
  SetHook    name 'SetHook',
  UnsetHook  name 'UnsetHook',
  PrintHooks name 'PrintHooks';

begin
  System.AssertErrorProc := AssertHandler;
  Hooks                  := DataLib.NewObjDict(OWNS_ITEMS);

  RegisterHandler(OnResetHooks,        'OnBeforeErmInstructions');
  RegisterHandler(OnResetHooks,        'OnSavegameRead');
  RegisterHandler(OnResetHooks,        'OnGameLeave');
  RegisterHandler(OnGenerateDebugInfo, 'OnGenerateDebugInfo');
  RegisterHandler(OnReportVersion,     'OnReportVersion');
end.

unit YoDescs;
{
DESCRIPTION:  Assignes descriptions to creatures
AUTHOR:       Alexander Shostak (aka Berserker aka EtherniDee aka BerSoft)
}

(***)  interface  (***)
uses
  SysUtils, Math,
  Lexer, TextScan, StrLib, Files,
  Era, Lib, Yo;
  
const
  (* Pathes and names *)
  CREATURE_DESCRIPTIONS_FILEPATH = Yo.MOD_DIR + '\creature descriptions.txt';

  
(***) implementation (***)


var
{U} Game:   Lib.TGame;
    Descs:  array [0..High(byte)] of string;

    
function LoadCreatureDescriptions: boolean;
var
{O} Scanner:  TextScan.TTextScanner;
    FileContents: string;
    Lexem:        Lexer.TLexem;
    LastLineN:    integer;
    LastLinePos:  integer;
    IsError:        boolean;
    
  procedure MarkError (const Err: string);
  begin
    if not IsError then begin
      IsError :=  TRUE;
      Game.PrintError(StrLib.BuildStr
      (
        'ERROR/Yona: File: ~FileName~, Line: ~Line~, Pos: ~Pos~.'#13#10'~Msg~',
        [
          'FileName', CREATURE_DESCRIPTIONS_FILEPATH,
          'Line',     SysUtils.IntToStr(LastLineN),
          'Pos',      SysUtils.IntToStr(LastLinePos),
          'Msg',      Err
        ],
        Lib.TEMPLATE_CHAR
      ));
    end; // .if
  end; // .procedure MarkError
  
  function ReadLexem: boolean;
  begin
    LastLineN   :=  Scanner.LineN;
    LastLinePos :=  Scanner.Pos - Scanner.LineStartPos;
    
    while Lexer.ReadLexem(Lexem, Scanner) and (Lexem.LexType = Lexer.LEX_COMMENT) do begin
      LastLineN   :=  Scanner.LineN;
      LastLinePos :=  Scanner.Pos - Scanner.LineStartPos;
    end; // .while
  
    result  :=  Lexem.LexType <> Lexer.LEX_ERROR;
    
    if not result then begin
      MarkError(Lexem.Error);
    end; // .if
  end; // .function ReadLexem
  
  function EnsureSym (Sym: Lexer.TLexType; const SymName: string): boolean;
  begin
    result  :=  Lexem.LexType = Sym;
      
    if not result then begin
      MarkError(SymName + ' expected');
    end; // .if
  end; // .function EnsureSym
  
  function ParseSemicolon: boolean;
  begin
    EnsureSym(Lexer.LEX_SEMICOLON, '";"');
    
    if IsError then begin
      IsError :=  FALSE;
    end // .if
    else begin
      ReadLexem;
    end; // .else
  
    result  :=  TRUE;
  end; // .function ParseSemicolon
  
  function ParseMonInd (out Value: integer): boolean;
  begin
    result  :=  EnsureSym(Lexer.LEX_INTEGER, 'Integer');
    
    if result then begin
      result  :=  Math.InRange(Lexem.IntVal, 0, High(byte));
    
      if result then begin
        Value :=  Lexem.IntVal;
      end // .if
      else begin
        MarkError('Invalid creature index');
      end; // .else
      
      ReadLexem;
    end; // .if
  end; // .function ParseMonInd
  
  function ParseString (out Value: string): boolean;
  begin
    result  :=  EnsureSym(Lexer.LEX_STRING, 'String');
    
    if result then begin
      Value   :=  SysUtils.StringReplace(Lexem.StrVal, #13#10, #10, [SysUtils.rfReplaceAll]);
      ReadLexem;
    end; // .if
  end; // .function ParseString
  
  function ParseDescription: boolean;
  var
    MonInd:   integer;
    MonDesc:  string;
  
  begin
    result  :=
      ParseMonInd(MonInd)                 and
      EnsureSym(Lexer.LEX_EQUALS, '"="')  and
      ReadLexem                           and
      ParseString(MonDesc)                and
      ParseSemicolon;
    
    if result then begin
      if MonDesc = '' then begin
        Descs[MonInd] :=  #0;
      end // .if
      else begin
        Descs[MonInd] :=  MonDesc;
      end; // .else
    end; // .if
  end; // .function HandleDescription
  
  function Recover: boolean;
  begin
    if IsError then begin
      while (Lexem.LexType <> Lexer.LEX_NO_ITEM) and IsError do begin
        while not (Lexem.LexType in [Lexer.LEX_NO_ITEM, Lexer.LEX_SEMICOLON]) do begin
          ReadLexem;
        end; // .while
        
        IsError :=  Lexem.LexType <> Lexer.LEX_SEMICOLON;
        ReadLexem;
      end; // .while
    end; // .if
  
    result  :=  not IsError;
  end; // .function Recover
  
  procedure ParseDescriptions;
  begin
    while Recover and (Lexem.LexType <> Lexer.LEX_NO_ITEM) do begin
      ParseDescription;
    end; // .while
  end; // .procedure ParseDescriptions

begin
  Scanner :=  TextScan.TTextScanner.Create;
  // * * * * * //
  result  :=  Files.ReadFileContents(CREATURE_DESCRIPTIONS_FILEPATH, FileContents);
  
  if not result then begin
    Game.PrintError
    (
      'ERROR/Yona: Cannot load file: "' + CREATURE_DESCRIPTIONS_FILEPATH + '"'
    );
  end // .if
  else begin
    Scanner.Connect(FileContents, #10);
    IsError :=  FALSE;
    ReadLexem;
    
    if Lexem.LexType <> Lexer.LEX_NO_ITEM then begin
      ParseDescriptions;
    end; // .if
  end; // .else
  // * * * * * //
  SysUtils.FreeAndNil(Scanner);
end; // .function LoadCreatureDescriptions

procedure OnGameStartOrLoad (Event: Era.PEvent); stdcall;
var
  i:  integer;

begin
  for i := 0 to High(Descs) do begin
    if (Descs[i] <> '') and (Game.MonInfos[i].NameZVar[Lib.NAME_DESC] = 0) then begin
      Game.MonInfos[i].Name[Lib.NAME_DESC] :=  Descs[i];
    end; // .if
  end; // .for
end; // .procedure OnGameStartOrLoad

begin
  Game  :=  Lib.Game;
  LoadCreatureDescriptions;
  
  Era.RegisterHandler(OnGameStartOrLoad,  'OnBeforeErmInstructions');
  Era.RegisterHandler(OnGameStartOrLoad,  'OnAfterLoadGame');
end.

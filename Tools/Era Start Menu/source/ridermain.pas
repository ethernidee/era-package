UNIT RiderMain;

INTERFACE

USES
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, Ini, AssocArrays, Utils, StrLib, ShellAPI;

TYPE
  TMain = class (TForm)
    Btn0: TBitBtn;
    Btn2: TBitBtn;
    Btn1: TBitBtn;
    Btn3: TBitBtn;
    Btn4: TBitBtn;
    Btn5: TBitBtn;
    Btn6: TBitBtn;
    Btn7: TBitBtn;
    Btn8: TBitBtn;
    Btn9: TBitBtn;
    Btn10: TBitBtn;
    Btn11: TBitBtn;
    Btn12: TBitBtn;
    Btn13: TBitBtn;
    Btn14: TBitBtn;
    Btn15: TBitBtn;
    BtnForward: TBitBtn;
    BtnBack: TBitBtn;
    procedure FormKeyPress(Sender: TObject; var Key: Char);
    procedure BtnClick(Sender: TObject);
    procedure BtnForwardClick(Sender: TObject);
    procedure BtnBackClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }
  public
    PROCEDURE ShowGroup (GroupInd: INTEGER);
  end;

CONST
  SETTINGS_PATH   = 'settings.ini';
  GROUPS_SECTION  = 'groups';
  GROUP_SECTION   = 'group';
  
  MAX_NUM_GROUPS      = 16;
  NUM_ITEMS_PER_GROUP = 16;
  
  DEFAULT_BUTTON_PATH = #0#0;
  

TYPE
  TItem = RECORD
    IsEmpty:  BOOLEAN;
    Caption:  STRING;
    RunPath:  STRING;
    ImgPath:  STRING;
  END; // .RECORD TItem
  
  TItemGroup  = RECORD
    Caption:  STRING;
    IsEmpty:  BOOLEAN;
    Items:    ARRAY [0..NUM_ITEMS_PER_GROUP - 1] OF TItem;
  END; // .RECORD TItemGroup
  
  
VAR
{O} Icons:    AssocArrays.TAssocArray {OF TBitmap};
    Main:     TMain;
    Groups:   ARRAY [0..MAX_NUM_GROUPS - 1] OF TItemGroup;
{U} BtnArr:   ARRAY [0..NUM_ITEMS_PER_GROUP - 1] OF Buttons.TBitBtn;
    CurrPage: INTEGER;


IMPLEMENTATION


{$R *.dfm}

PROCEDURE LoadSettings;
VAR
{U} Image:  Graphics.TBitmap;
    i:      INTEGER;
    y:      INTEGER;

  PROCEDURE LoadGroupCaption (GroupInd: INTEGER; OUT Res: STRING);
  BEGIN
    IF
      NOT Ini.ReadStrFromIni
      (
        SysUtils.IntToStr(GroupInd),
        GROUPS_SECTION,
        SETTINGS_PATH,
        Res
      )
    THEN BEGIN
      Res :=  '';
    END // .IF
  END; // .PROCEDURE LoadGroupCaption
  
  PROCEDURE LoadItem (ItemInd, GroupInd: INTEGER; OUT Item: TItem);
  VAR
    ItemStr:    STRING;
    ItemTokens: Utils.TArrayOfString;
     
  BEGIN
    Item.Caption  :=  '';
    Item.RunPath  :=  '';
    Item.ImgPath  :=  '';
    Item.IsEmpty  :=  NOT Ini.ReadStrFromIni
    (
      SysUtils.IntToStr(ItemInd),
      GROUP_SECTION + ' ' + SysUtils.IntToStr(GroupInd),
      SETTINGS_PATH,
      ItemStr
    );
  
    IF NOT Item.IsEmpty THEN BEGIN
      ItemTokens  :=  StrLib.Explode(ItemStr, '|');
      
      IF LENGTH(ItemTokens) > 0 THEN BEGIN
        Item.RunPath  :=  SysUtils.Trim(ItemTokens[0]);
      END; // .IF
      
      IF LENGTH(ItemTokens) > 1 THEN BEGIN
        Item.Caption  :=  SysUtils.Trim(ItemTokens[1]);
      END // .IF
      ELSE BEGIN
        Item.Caption  :=  SysUtils.ExtractFileName(Item.RunPath);
      END; // .ELSE
      
      IF LENGTH(ItemTokens) > 2 THEN BEGIN
        Item.ImgPath  :=  SysUtils.Trim(ItemTokens[2]);
      END; // .IF
    END; // .IF
  END; // .PROCEDURE LoadItem

BEGIN
  Image :=  NIL;
  // * * * * * // 
  FOR y := 0 TO HIGH(Groups) DO BEGIN
    LoadGroupCaption(y, Groups[y].Caption);
    Groups[y].IsEmpty :=  TRUE;
    
    FOR i := 0 TO HIGH(Groups[y].Items) DO BEGIN
      LoadItem(i, y, Groups[y].Items[i]);
      
      IF NOT Groups[y].Items[i].IsEmpty THEN BEGIN
        Groups[y].IsEmpty :=  FALSE;
      END; // .IF
      
      IF Groups[y].Items[i].ImgPath <> '' THEN BEGIN
        IF NOT Icons.GetExistingValue(Groups[y].Items[i].ImgPath, POINTER(Image)) THEN BEGIN
          Image :=  Graphics.TBitmap.Create;
          
          TRY
            Image.LoadFromFile(Groups[y].Items[i].ImgPath);
          EXCEPT
            Groups[y].Items[i].ImgPath  :=  DEFAULT_BUTTON_PATH;
          END; // .TRY
          
          IF Groups[y].Items[i].ImgPath <> DEFAULT_BUTTON_PATH THEN BEGIN
            Icons[Groups[y].Items[i].ImgPath] :=  Image; Image  :=  NIL;
          END // .IF
          ELSE BEGIN
            SysUtils.FreeAndNil(Image);
          END; // .ELSE
        END // .IF
        ELSE BEGIN
          Image :=  NIL;
        END; // .ELSE
      END // .IF
      ELSE BEGIN
        Groups[y].Items[i].ImgPath  :=  DEFAULT_BUTTON_PATH;
      END; // .ELSE
    END; // .FOR
  END; // .FOR
END; // .PROCEDURE LoadSettings

PROCEDURE TMain.ShowGroup (GroupInd: INTEGER);
VAR
{U} Image:  Graphics.TBitmap;
    i:      INTEGER;

BEGIN
  Image :=  NIL;
  // * * * * * //
  FOR i := 0 TO HIGH(Groups[GroupInd].Items) DO BEGIN
    BtnArr[i].Glyph   :=  Graphics.TBitmap(Icons[Groups[GroupInd].Items[i].ImgPath]);
    BtnArr[i].Caption :=  Groups[GroupInd].Items[i].Caption;
  END; // .FOR
  
  Self.Caption            :=
    Groups[GroupInd].Caption + '  [' + SysUtils.IntToStr(GroupInd) +
    '/' + SysUtils.IntToStr(MAX_NUM_GROUPS - 1) + ']';
  Self.BtnBack.Enabled    :=  CurrPage > 0;
  Self.BtnForward.Enabled :=  CurrPage < (MAX_NUM_GROUPS - 1);
END; // .PROCEDURE TMain.ShowGroup

PROCEDURE TMain.BtnClick (Sender: TObject);
VAR
  AppPath:        STRING;
  AppParams:      STRING;
  AppDir:         STRING;
  RunPathTokens:  Utils.TArrayOfString;
  ItemInd:        INTEGER;

BEGIN
  ItemInd :=  0;
  
  WHILE BtnArr[ItemInd] <> Sender DO BEGIN
    INC(ItemInd);
  END; // .WHILE
  
  IF Groups[CurrPage].Items[ItemInd].RunPath <> '' THEN BEGIN
    RunPathTokens :=  StrLib.ExplodeEx
    (
      Groups[CurrPage].Items[ItemInd].RunPath,
      '?',
      NOT StrLib.INCLUDE_DELIM,
      StrLib.LIMIT_TOKENS,
      2
    );
    
    AppPath :=  SysUtils.ExpandFileName(SysUtils.Trim(RunPathTokens[0]));
    
    IF LENGTH(RunPathTokens) > 1 THEN BEGIN
      AppParams :=  SysUtils.Trim(RunPathTokens[1]);
    END // .IF
    ELSE BEGIN
      AppParams :=  '';
    END; // .ELSE
    
    AppDir  :=  SysUtils.ExtractFileDir(AppPath);
    
    ShellAPI.ShellExecute
    (
      0,
      NIL,
      PCHAR(AppPath),
      PCHAR(AppParams),
      PCHAR(AppDir),
      Windows.SW_SHOW
    )
  END; // .IF
END; // .PROCEDURE TMain.BtnClick

PROCEDURE TMain.BtnBackClick (Sender: TObject);
BEGIN
  DEC(CurrPage);
  Self.ShowGroup(CurrPage);
END; // .PROCEDURE TMain.BtnBackClick

PROCEDURE TMain.BtnForwardClick (Sender: TObject);
BEGIN
  INC(CurrPage);
  Self.ShowGroup(CurrPage);
END; // .PROCEDURE TMain.BtnForwardClick

PROCEDURE TMain.FormKeyPress (Sender: TObject; var Key: Char);
BEGIN
  IF Key = #27 THEN BEGIN
    Self.Close;
  END; // .IF
END; // .PROCEDURE TMain.FormKeyPress

PROCEDURE TMain.FormShow (Sender: TObject);
VAR
{U} DefImage: Graphics.TBitmap;

BEGIN
  DefImage  :=  Graphics.TBitmap.Create;
  // * * * * * //
  BtnArr[0]   :=  Self.Btn0;
  BtnArr[1]   :=  Self.Btn1;
  BtnArr[2]   :=  Self.Btn2;
  BtnArr[3]   :=  Self.Btn3;
  BtnArr[4]   :=  Self.Btn4;
  BtnArr[5]   :=  Self.Btn5;
  BtnArr[6]   :=  Self.Btn6;
  BtnArr[7]   :=  Self.Btn7;
  BtnArr[8]   :=  Self.Btn8;
  BtnArr[9]   :=  Self.Btn9;
  BtnArr[10]  :=  Self.Btn10;
  BtnArr[11]  :=  Self.Btn11;
  BtnArr[12]  :=  Self.Btn12;
  BtnArr[13]  :=  Self.Btn13;
  BtnArr[14]  :=  Self.Btn14;
  BtnArr[15]  :=  Self.Btn15;
  
  DefImage.Assign(BtnArr[0].Glyph);
  Icons[DEFAULT_BUTTON_PATH]  :=  DefImage; DefImage  :=  NIL;

  LoadSettings;
  Self.KeyPreview :=  TRUE;
  CurrPage        :=  0;
  Self.ShowGroup(CurrPage);
END; // .PROCEDURE TMain.FormShow

BEGIN
  Icons :=  AssocArrays.NewStrictAssocArr(Graphics.TBitmap);
END.

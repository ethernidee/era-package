////////////////////////////////////////////////////////////////////////////////////
// (HD 3.0) HoMM3 GUI (Window Manager, Dialogs, Control Elements (DlgItems) )
// Author: Alexander Barinov (aka baratorch, aka Bara) e-mail: baratorch@yandex.ru
// Thanks: ZVS, GrayFace
////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "HoMM3_Base.h"
#include "HoMM3_Res.h"

// char myString[1024];


// _EventMsg_::type values
#define MT_MOUSEBUTTON 512   // нажата любая кнопка мыши
#define MT_KEYDOWN  1        // нажата клавиша
#define MT_KEYUP  2          // отпущена клавиша
#define MT_MOUSEOVER 4       // ведение мыши
#define MT_LBUTTONOUTSIDE 8  // лкм за пределами диалога
#define MT_RBUTTONOUTSIDE 32 // пкм за пределами диалога
#define MT_EXIT 512          // отмена
// #define WM_MOUSEWHEEL  522  // скролл колесом

// MT_MOUSEBUTTON _EventMsg_::subtype values
#define MST_EXIT 10          // отмена
#define MST_LBUTTONDOWN 12
#define MST_RBUTTONDOWN 14
#define MST_LBUTTONCLICK 13

// _EventMsg_::flags 
#define MF_SHIFT 1
#define MF_CTRL 4
#define MF_ALT 32


// _Dlg_::flags 
#define DF_NOTSCREEN 0x01
#define DF_SCREENSHOT 0x02
#define DF_SHADOW  0x10
// my _Dlg_::flags 
#define DF_HD           0x04
#define DF_SIMPLEFRAME  0x08
#define DF_GRAYFRAME    0x20
#define DF_FSSHADOW     0x40
#define DF_XORSCREEN    0x80
#define DF_NOTSHOW      0x100
#define DF_INVISIBLE    0x200

// _DlgItem_::flags
#define DIF_TRANSPARENT 0x0001
#define DIF_PCX   0x0800
#define DIF_DEF   0x0010
#define DIF_BUTTON  0x0002
#define DIF_TEXT  0x0008 // read only

#define DIID_OK_FRAME     30625
#define DIID_CANCEL_FRAME  30626
#define DIID_OK     30725
#define DIID_CANCEL 30726

#define DLG_X_CENTER -1
#define DLG_Y_CENTER -1

namespace Fonts
{
  _cstr_ const TINY    = ((_cstr_)0x660CB4); // "tiny.fnt"
  _cstr_ const SMALL   = ((_cstr_)0x65F2F8); // "smalfont.fnt"
  _cstr_ const MEDIUM  = ((_cstr_)0x65F2EC); // "MedFont.fnt"
  _cstr_ const BIG     = ((_cstr_)0x660B24); // "bigfont.fnt"
  _cstr_ const VERDANA = ((_cstr_)0x6700B4); // "Verd10B.fnt"
} // namespace Text

namespace DlgDefNames
{
    _cstr_ const ARTIFACT_DEF     = ((_cstr_)0x660214);  // "artifact.def" 44x44
    _cstr_ const ARTS_ICON        = ((_cstr_)0x683178);  // AltArt.def 64x32
    _cstr_ const CREATURE_SMALL   = ((_cstr_)0x660180);  // "CPRSMALL.def" 32x32
    _cstr_ const DIBOXBACK        = ((_cstr_)0x66025C);  // "diboxback.pcx" 256x256
    _cstr_ const DLGBOX           = ((_cstr_)0x66024C);  // "dialogbox.def" 64x64
    _cstr_ const HERO_CADRE       = ((_cstr_)0x65F3DC);  // hpsyyy.pcx 48x32
    _cstr_ const PSKILL_42        = ((_cstr_)0x679D9C);  // "PSKIL42.def" 42x42
    _cstr_ const RESOURCE_DEF     = ((_cstr_)0x660224);  // "resource.def" 32x32
    _cstr_ const RESOURCE_82      = ((_cstr_)0x660114);  // "resour82.def" 82x93
    _cstr_ const SPELLS_DEF       = ((_cstr_)0x660208);  // "spells.def"78x65
    _cstr_ const SPELL_SMALL      = ((_cstr_)0x6700A4);  // "spellint.def" 48x36
    _cstr_ const SSKILL_44        = ((_cstr_)0x6601D0);  // "Secskill.def" 44x44
    _cstr_ const UN44_DEF         = ((_cstr_)0x679D90);  // "un44.def"44x44
    _cstr_ const OVBUTN3          = ((_cstr_)0x6817C4);  // "OvButn3.def" 108x16
    _cstr_ const LARGE_HERO_CADRE = ((_cstr_)0x68C45C);  // TPTavSel.pcx 62x68 ~decal by -2
    _cstr_ const CREATURE_LARGE   = ((_cstr_)0x6700C0);  // TwCrPort.def 58x64
    _cstr_ const CANCEL_BUTTON    = ((_cstr_)0x660B04);  // iCancel.def 64x30
    _cstr_ const CAST_SPELL       = ((_cstr_)0x66FFD4);  // icm005.def 48x36
    _cstr_ const MORALE_42        = ((_cstr_)0x68C6DC);  // IMRL42.def 42x38
    _cstr_ const LUCK_42          = ((_cstr_)0x68C6D0);  // ILCK42.def 42x38
    _cstr_ const CREST58          = ((_cstr_)0x6601FC);  // CREST58.def 58x64
    _cstr_ const TOWN_SMALL       = ((_cstr_)0x65F318);  // itpa.def 48x32
    _cstr_ const NO_VISION        = ((_cstr_)0x6885A0);  // SYSOPB8.def 46x32
    _cstr_ const ADVENTURE_CURSOR = ((_cstr_)0x68164C);  // cradvntr.def 40x40
    _cstr_ const ALT_ART          = ((_cstr_)0x683178);  // AltArt.def 64x32
    _cstr_ const ON_OFF_CHECKBOX  = ((_cstr_)0x6700F0);  // sysopchk.def 32x24
    _cstr_ const OKAY_DEF         = ((_cstr_)0x670160);  // iOkay.def 64x30
    _cstr_ const OKAY32_DEF       = ((_cstr_)0x682374);  // iOkay32.def 66x32
    _cstr_ const OKAY6432_DEF     = ((_cstr_)0x65F470);  // iOk6432.def 64x32
    _cstr_ const BOX_64_30_PCX    = ((_cstr_)0x67016C);  // Box64x30.pcx
    _cstr_ const BOX_66_32_PCX    = ((_cstr_)0x682380);  // Box66x32.pcx
    _cstr_ const CANCEL_DEF       = ((_cstr_)0x660B04);  // "iCancel.def" 64x30
    _cstr_ const VIEW_CREATURE    = ((_cstr_)0x660134);  // iViewCr.def
    _cstr_ const VIEW_MAGNIFIER   = ((_cstr_)0x68C734);  // VWMag1.def 60x32
    _cstr_ const iSAVE_DEF        = "ISAVE.DEF";         // iSave.def 64x32
    _cstr_ const BOX_64_32_PCX    = ((_cstr_)0x68C640);  // Box64x32.pcx
    _cstr_ const GAME_TYPE_DEF    = ((_cstr_)0x683568);  // 32x24
    _cstr_ const ICM005_DEF       = ((_cstr_)0x66FFD4);  // 48x36
    _cstr_ const ALTART_DEF       = ((_cstr_)0x683178);  // 64x32
    _cstr_ const VWSYMBOL_DEF     = ((_cstr_)0x68C740);  // 32x32
    _cstr_ const CHECKBOX_DEF     = "checkbox.def";      
    _cstr_ const RADIOBTN_DEF     = "radiobttn.def";     
}

//enum DlgTextAlignment
//{
//    HLeft        = 0,
//    HCenter      = 1,
//    HRight       = 2,
//    VTop         = 0,
//    VCenter      = 4,
//    VBottom      = 8,
//    BottomLeft   = HLeft   | VBottom,
//    BottomCenter = HCenter | VBottom,
//    BottomRight  = HRight  | VBottom,
//    MiddleLeft   = HLeft   | VCenter,
//    MiddleCenter = HCenter | VCenter,
//    MiddleRight  = HRight  | VCenter,
//    TopLeft      = HLeft   | VTop,
//    TopMiddle    = HCenter | VTop,
//    TopRight     = HRight  | VTop
//};

//enum DlgTextColor
//{
//    PRIMARY     = 1,
//    HEADING     = 7,
//    CHAT        = 15,
//
//    SILVER      = 0x00,
//    REGULAR     = 0x01,
//    HIGHLIGHT   = 0x02,
//    GOLD        = 0x03,
//    WHITE       = 0x04,
//    REGULARY    = 0x07,
//    GREEN       = 0x0D,
//    LIGHT_GREEN = 0x0E,
//    DARK_GREEN  = 0x0F,
//    BLACK       = 0x17,
//    BLUE        = 0x18,
//    CYAN        = 0x1A,
//    RED         = 0x1B,
//    PURPLE      = 0x1C,
//    YELLOW      = 0x1D,
//    GRAY        = 0x36,
//    RED2        = 0x37,
//    BLUE2       = 0x38,
//    TAN         = 0x39,
//    DARK_GREEN2 = 0x3A,
//    ORANGE      = 0x3B,
//    PURPLE2     = 0x3C,
//    DARK_CYAN   = 0x3D,
//    PINK        = 0x3E,
//    GRAY2       = 0x3F,
//    YELLOW2     = 0x57,
//    DARK_YELLOW = 0x58,
//    TAN2        = 0x59,
//    TAN3        = 0x5A,
//    TAN4        = 0x5B,
//    TAN5        = 0x5C,
//    CYAN2       = 0x67,
//    CYAN3       = 0x68,
//    CYAN4       = 0x69,
//    CYAN5       = 0x6A
//};

// просто объявление функцции для удобства вызова
inline _bool_ b_MsgBox(char* text, int style);

NOALIGN struct _DlgMsg_ : public _Struct_
{
 _dword_ type;
 _int_ subtype;
 _int_ item_id;
 _dword_ flags;
 _dword_ x_abs;
 _dword_ y_abs;
 _dword_ new_param ;
 _dword_ flags_2;

  _DlgMsg_* Set(_dword_ type = 0, _int_ subtype = 0, _int_ item_id = 0, _dword_ flags = 0, _dword_ x_abs = 0, _dword_ y_abs = 0, _dword_ new_param = 0, _dword_ flags_2 = 0)
  {
    this->type = type;
    this->subtype = subtype;
    this->item_id = item_id;
    this->flags = flags;
    this->x_abs = x_abs;
    this->y_abs = y_abs;
    this->new_param = new_param;
    this->flags_2 = flags_2;
    return this;
  }
};
typedef _DlgMsg_ _EventMsg_;


////////////////////////////////////////////////////////////////////////////

// * размер 38h (56 dec)
NOALIGN struct _Manager_ : _Struct_
{
// protected:
  struct {
    _dword_ managerConstructor; // 0x44D200
    _dword_ managerDestructor;
    _dword_ managerUpdate;
    // goes on
  } *h3ManagerVTable;

  _Manager_ *previus;   // parent
  _Manager_ *next;      // child
  _int32_ id;
  _int32_ priority;
  char name[28];    // 0x14
  _int32_ nameEnd;  // 0x30
  _int32_ isActive; // 0x34
  // public:
  void SetPreviousManager(_Struct_ *prevMgr) { previus = (_Manager_*)prevMgr; }
  void SetNextManager(_Struct_ *nextMgr) { next = (_Manager_*)nextMgr; }
  _Manager_* ActivateManager() { return CALL_1(_Manager_*, __thiscall, 0x4B0BA0, this); }

  void SetManagers(void *mgr1, void *mgr2)
  {
    previus = (_Manager_ *)mgr1;
    next = (_Manager_ *)mgr2;
  }
  void ShowInfo() // корректно размер пока не показывает
  {
    //sprintf(H3Text, "{Manager}\n\n name: %s\n size: %d", &this->name, sizeof(_Manager_) );
    //b_MsgBox(H3Text, 5);
  };
};


////////////////////////////////////////////////////////////////////////////
// struct _Manager_;
NOALIGN struct _WndMgr_ : _Struct_
// NOALIGN struct _WndMgr_ : public _Struct_
{
  // _byte_  field_0[56];
  _Manager_ mgr;
  _dword_ result_dlg_item_id; // 0x38
  _dword_ f_3C;   // 0x3C
  _Pcx16_* screen_pcx16;   // 0x40 
  _dword_ f_44;   // 0x44
  _dword_ f_48;   // 0x48 

 _Pcx16_* backup_screen_pcx16; // +4Ch; Сохранённое старое изображение для плавного изменения его в новое (исчезание ресурсов при взятии и пр.)
  
 _Dlg_*  dlg_first; // 0x50
 _Dlg_*  dlg_last;  // 0x54

 _Dlg_*  field_58;
 _Dlg_*  field_5C;

 //normal
 inline void ShowRightMouseClickDlg(_Dlg_* dlg) {CALL_2(void, __thiscall, 0x603000, this, dlg);}
 inline void RemoveDialog(_Dlg_* dlg) {CALL_2(void, __thiscall, 0x602A60, this, dlg);}
 inline void RedrawScreenRect(_int_ x, _int_ y, _int_ width, _int_ height) {CALL_5(void, __thiscall, 0x603190, this, x, y, width, height);}
 
 
 // Создание нового сохранённого экрана (в backup_screen_pcx16), старый автоматически уничтожается.
 inline void MakeBackupScreen(_int_ X_Pos, _int_ Y_Pos, _int_ Width, _int_ Height)
 {
   CALL_5(void, __thiscall, 0x603280, this, X_Pos, Y_Pos, Width, Height);
 }
 
 
 // Плавное изменение области экрана (из backup_screen_pcx16 в screen_pcx16).
 inline void SmoothImageChange(_int_ X_Pos, _int_ Y_Pos, _int_ Width, _int_ Height, _int_ FrameTime)
 {
   CALL_6(void, __thiscall, 0x603380, this, X_Pos, Y_Pos, Width, Height, FrameTime);
 }

 // 
 inline _int32_ ProcessDialog(_dword_ dlg, _dword_ fncallback, _int32_ fadeIn)
 {
  return CALL_4(_int32_, __thiscall, 0x602AE0, this, dlg, fncallback, fadeIn);
 }

};


////////////////////////////////////////////////////////////////////////////
NOALIGN struct _Dlg_ : public _Struct_ 
{
 _ptr_*  v_table;
 _dword_  z_order;
 _Dlg_*  next_dlg;
 _Dlg_*  last_dlg;
 _dword_  flags;
 _dword_  state;
 _dword_  x;
 _dword_  y;
 _dword_  width;
 _dword_  height;
 _DlgItem_* first_item;
 _DlgItem_* last_item;

 _ptr_  items_list;       // +48
 _ptr_  items_first;      // +52
 _ptr_  items_last;       // +56
 _ptr_  items_mem_end;    // +60

 _dword_  focused_item_id;
 _Pcx16_* screenshot_pcx16;

 //
 _int32_ deactivatesCount;
 _ptr_ field_4C;
 _ptr_ field_50;

 _ptr_ field_54;
 _ptr_ field_58;
 _ptr_ field_5C;

 ///
 _ptr_ field_60;

 _dword_ field_64;
 _dword_ field_68;

//VIRTUAL/////////////////////////////////////////////////////////////////////////
 inline _Dlg_* Destroy(_bool_ delete_) {return CALL_2(_Dlg_*, __thiscall, this->v_table[0], this, delete_);}
 inline void  Show(_int_ z_order, _bool_ redraw_screen) {CALL_3(void, __thiscall, this->v_table[1], this, z_order, redraw_screen);}
 inline void  Hide(_bool_ redraw_screen) {CALL_2(void, __thiscall, this->v_table[2], this, redraw_screen);}
 inline void  Redraw(_bool_ redraw_screen, _dword_ item_id_start, _dword_ item_id_end) {CALL_4(void, __thiscall, this->v_table[5], this, redraw_screen, item_id_start, item_id_end);}
 inline void  Run(_dword_ a2) { CALL_2(void, __thiscall, this->v_table[6], this, a2);}
 inline _int_ Close(_EventMsg_* msg) {return CALL_2(_int_, __thiscall, this->v_table[14], this, msg); }
 inline int  RMC_Show() {return CALL_1(int, __thiscall, 0x5F4B90, this);}

//NORMAL//////////////////////////////////////////////////////////////////////////
 inline _DlgItem_* GetItem(_int_ id) {return CALL_2(_DlgItem_*, __thiscall, 0x5FF5B0, this, id);}
 inline _DlgItem_* FindItem(_int_ x, _int_ y) {return CALL_3(_DlgItem_*, __thiscall, 0x5FF9A0, this, x, y);}
 inline _int_  FindItemID(_int_ x, _int_ y) {return CALL_3(_int_, __thiscall, 0x5FF970, this, x, y);}
 
 inline _dword_  AttachItem(_DlgItem_* item, int z_order) {return CALL_3(_dword_, __thiscall, 0x5FF270, this, item, z_order);}
 inline _dword_  DetachItem(_DlgItem_* item) {return CALL_2(_dword_, __thiscall, 0x5FF320, this, item);}
 inline void   SetFocuseToItem(_int_ item_id) { CALL_2(void, __thiscall, 0x5FFA50, this, item_id); }
 
 inline _int_  SendItemCommand(_int_ cmd_type, _int_ cmd_subtype, _int_ item_id, _dword_ param)
  {return CALL_5(_int_, __thiscall, 0x5FF400,this,cmd_type,cmd_subtype,item_id,param);}

 inline _int_ DefProc(_EventMsg_* msg) {return CALL_2(_int_, __thiscall, 0x41B120, this, msg);}

//MY//////////////////////////////////////////////////////////////////////////////
 inline void Redraw(_bool_ redraw_screen) {Redraw(redraw_screen, -65535, 65535);}
 inline void Redraw() {Redraw(1, -65535, 65535);}
 inline void Run() { Run(0);}

 inline void AddItemToOwnArrayList(_DlgItem_* item) {CALL_4(void, __thiscall, 0x5FE2D0, &this->items_list, this->items_last, 1, &item);}
 inline _dword_ AttachItem(_DlgItem_* item) {return CALL_3(_dword_, __thiscall, 0x5FF270, this, item, -1);}
 inline void AddItem(_DlgItem_* item) {AddItemToOwnArrayList(item); AttachItem(item);}

 void SetItemsArrayListLength(int items_count);
 void AddItemByZOrder(_DlgItem_* item, int z_order);
 ////void DetachItem(_DlgItem_* item);
 void RemoveItem(_DlgItem_* item);
 void SetItemZOrder(_DlgItem_* item, int z_order);

 inline void SetRect(int x, int y, int width, int height) {this->x = x; this->y = y; this->width = width; this->height = height;}
 inline void SetPos(int x, int y) {this->x = x; this->y = y;}
 inline void SetSize(int width, int height) {this->width = width; this->height = height;}

 inline void Send_MouseMsg(_dword_ type = 0, _int_ subtype = 0, _int_ item_id = 0, _dword_ flags = 0, _dword_ x_abs = 0, _dword_ y_abs = 0, _dword_ new_param = 0, _dword_ flags_2 = 0)
 {
    _DlgMsg_ m; 
    CALL_2(void, __thiscall, 0x5FF3A0, this, m.Set(type, subtype, item_id, flags, x_abs, y_abs, new_param, flags_2) );
 }
};
////////////////////////////////////////////////////////////////////////////


#define b_DlgStaticPcx8_Create(x, y, width, height, id, pcx8_name, flags) \
 CALL_8(_DlgStaticPcx8_*, __thiscall, 0x44FFA0, o_New(sizeof(_DlgStaticPcx8_)), x, y, width, height, id, pcx8_name, flags)

#define b_DlgStaticText_Create(x, y, width, height, text, font_name, text_color, id, align, bkcolor, flags_notused) \
 CALL_12(_DlgStaticText_*, __thiscall, 0x5BC6A0, o_New(sizeof(_DlgStaticText_)), x, y, width, height, text, font_name, text_color, id, align, bkcolor, flags_notused)

#define b_DlgStaticTextPcx8ed_Create(x, y, width, height, text, font_name, bkground_pcx8, text_color, id, align, flags_notused) \
 CALL_12(_DlgStaticTextPcx8ed_*, __thiscall, 0x5BCB70, o_New(sizeof(_DlgStaticTextPcx8ed_)), x, y, width, height, text, font_name, bkground_pcx8, text_color, id, align, flags_notused)

#define b_DlgTextEdit_Create(x, y, width, height, max_len, text, font_name, text_color,  align, bkground_pcx8, bkcolor_notused, id, flags_notused, has_border, border_width, border_height) \
 CALL_17(_DlgTextEdit_*, __thiscall, 0x5BACD0, o_New(sizeof(_DlgTextEdit_)), x, y, width, height, max_len, text, font_name, text_color,  align, bkground_pcx8, bkcolor_notused, id, flags_notused, has_border, border_width, border_height)

#define b_DlgTextButton_Create(x, y, width, height, id, def_name, caption_text, font_name,  def_frame_ix, def_frame_press_ix, close_dlg, hotkey, flags, caption_color) \
 CALL_15(_DlgTextButton_*, __thiscall, 0x456730, o_New(sizeof(_DlgTextButton_)), x, y, width, height, id, def_name, caption_text, font_name,  def_frame_ix, def_frame_press_ix, close_dlg, hotkey, flags, caption_color)

#define b_DlgCallbackButton_Create(x, y, width, height, id, def_name, callback, def_frame_ix, def_frame_press_ix) \
 CALL_10(_DlgCallbackButton_*, __thiscall, 0x456A10, o_New(sizeof(_DlgCallbackButton_)), x, y, width, height, id, def_name, callback, def_frame_ix, def_frame_press_ix)

#define b_DlgButton_Create(x, y, width, height, id, def_name, def_frame_ix, def_frame_press_ix, close_dlg, hotkey, flags) \
 CALL_12(_DlgButton_*, __thiscall, 0x455bd0, o_New(sizeof(_DlgButton_)), x, y, width, height, id, def_name, def_frame_ix, def_frame_press_ix, close_dlg, hotkey, flags)

#define b_DlgStaticPcx16_Create(x, y, width, height, id, pcx16_name, flags) \
 CALL_8(_DlgStaticPcx16_*, __thiscall, 0x450340, o_New(0x52), x, y, width, height, id, pcx16_name, flags)

#define b_DlgEmptyStatic_Create(x, y, width, height, id, flags) \
 CALL_7(_DlgItem_*, __thiscall, 0x44FBE0, o_New(0x48), x, y, width, height, id, flags)

#define b_DlgStaticDef_Create(x, y, width, height, id, def_name, def_frame_ix, def_frame_press_ix, mirrored, close_dlg, flags) \
 CALL_12(_DlgStaticDef_*, __thiscall, 0x4EA800, o_New(0x48), x, y, width, height, id, def_name, def_frame_ix, def_frame_press_ix, mirrored, close_dlg, flags)

#define b_DlgScrollableText_Create(text, x, y, width, height, font_name, text_color, is_blue) \
 CALL_9(_DlgScrollableText_*, __thiscall, 0x5BA360, o_New(sizeof(_DlgScrollableText_)),text,x,y,width,height,font_name,text_color,is_blue)

#define b_DlgScroll_Create(x, y, width, height, id, ticks_count, callback, is_blue, a10, a11) \
 CALL_11(_DlgScroll_*, __thiscall, 0x5963C0, o_New(sizeof(_DlgScroll_)),x, y, width, height, id, ticks_count, callback, is_blue, a10, a11)

////////////////////////////////////////////////////////////////////////////
NOALIGN struct _DlgItem_
{
 _ptr_*  v_table;       // +0
 _Dlg_*  parent;        // +4
 _DlgItem_* prev_item;  // +8
 _DlgItem_* next_item;  // +12
 _word_  id;            // +16
 _word_  z_order;       // +18
 _word_  flags;         // +20
 _word_  state;         // +22
 _int16_  x;            // +24
 _int16_  y;            // +26
 _word_  width;         // +28
 _word_  height;        // +30
 _char_*  short_tip_text; // +32 shown in status bar
 _char_*  full_tip_text;  // +36 shown in RMC Message Box
 // _byte_  field_28[4];
 _dword_  field_28;   // +40
 _dword_  field_2C;   // +44

 //virtual
 inline _DlgItem_* Destroy(_bool_ delete_this)  {return CALL_2(_DlgItem_*, __thiscall, this->v_table[0], this, delete_this);}
 inline void   Draw()       {CALL_1(void, __thiscall, this->v_table[4], this);}
 inline _dword_  Proc(_DlgMsg_* msg)    {return CALL_2(_dword_, __thiscall, this->v_table[2], this, msg);}
 inline _dword_  SetEnabled(_bool_ enabled)  {return CALL_2(_dword_, __thiscall, this->v_table[9], this, enabled);}
 inline void   SetFocus()      { CALL_1(void, __thiscall, this->v_table[10], this); }
 inline void   RemoveFocus()     { CALL_1(void, __thiscall, this->v_table[11], this); }

 // normal
 inline _dword_  SendCommand(_int_ new_param, _dword_ subtype) 
  {return CALL_3(_dword_, __thiscall, 0x5FED80, this, new_param, subtype);}

 // my 
 inline void  Show()  {SendCommand(5, 6);}
 inline void  Show_ButStayEnable()  {SendCommand(5, 4);}
 inline void  Hide()  {SendCommand(6, 6);}
 inline void  Hide_ButStayEnable()  {SendCommand(6, 4);}
 void RedrawScreen(); 
 inline void SetRect(int x, int y, int width, int height) {this->x = x; this->y = y; this->width = width; this->height = height;}
 inline void SetPos(int x, int y) {this->x = x; this->y = y;}
 inline void SetSize(int width, int height) {this->width = width; this->height = height;}
 static inline  _DlgItem_* Create(int x, int y, int width, int height, int id, _dword_ flags)
  {return b_DlgEmptyStatic_Create(x, y, width, height, id, flags);}
};
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
NOALIGN struct _DlgScroll_ : public _DlgItem_
{
 _Def_ *  def;
 _Pcx8_ * pcx;

 _dword_  tick_value;
 _int_  tick;
 _dword_  btn_position;
 _dword_  size_free;
 _dword_  ticks_count;
 _dword_  size_max;
 _dword_  a10;
 _dword_  btn_size2;
 _word_  some_x;
 _word_  some_y;
 _dword_  a11;
 _dword_  field_60;
 _ptr_  callback;

  inline int DrawScroll() { return CALL_1(int, __thiscall, this->v_table[4], this); }
  inline void SetTicksCount(int count) { CALL_2(void, __thiscall, this->v_table[13], this, count); }
  inline void SetValue(int value) { CALL_2(void, __thiscall, this->v_table[14], this, value); }  
  inline int SetTicksCountNew(int count) { return CALL_2(int, __thiscall, this->v_table[15], this, count); }
  // inline void SetWTF() { CALL_1(void, __thiscall, this->v_table[16], this); }
  inline int ClickUp() { return CALL_6(int, __thiscall, 0x596520, this, 1, 2, 0, 4, 72);}
  inline int ClickDown() { return CALL_6(int, __thiscall, 0x596520, this, 0, 3, 0, 4, 80);}

  // igrik: клик вверх по ползунку без анимации нажатия кнопки скролла
  inline int MooveUP() { 
      *(_byte_*)0x59672E = 0xEB; 
      int result = CALL_6(int, __thiscall, 0x596520, this, 1, 2, 0, 4, 72);
      *(_byte_*)0x59672E = 0x7F;
      return result;
  }

  // igrik: клик вниз по ползунку без анимации нажатия кнопки скролла
  inline int MooveDown() { 
      *(_byte_*)0x59672E = 0xEB; 
      int result = CALL_6(int, __thiscall, 0x596520, this, 0, 3, 0, 4, 80);
      *(_byte_*)0x59672E = 0x7F;
      return result;
  }

// my 
 static inline _DlgScroll_* Create(int x, int y, int width, int height, int id, int ticks_count, _ptr_ callback, _bool_ is_blue, _dword_ a10, _dword_ a11)
  {return b_DlgScroll_Create(x, y, width, height, id, ticks_count, callback, is_blue, a10, a11);}
};
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
NOALIGN struct _DlgStaticPcx8_ : public _DlgItem_
{
 _Pcx8_* pcx8;
 void Colorize(_int_ player_id) {CALL_2(void, __thiscall, 0x4501D0, this, player_id);}

// my 
 static inline _DlgStaticPcx8_* Create(int x, int y, int width, int height, int id, char* pcx8_name)
  {return b_DlgStaticPcx8_Create(x, y, width, height, id, pcx8_name, DIF_PCX);}
 static inline _DlgStaticPcx8_* Create(int x, int y, int id, char* pcx8_name)
 {
  _DlgStaticPcx8_* item = b_DlgStaticPcx8_Create(x, y, 0, 0, id, pcx8_name, DIF_PCX);
  if (item)
   if (item->pcx8)
   {
    item->width = item->pcx8->width;
    item->height = item->pcx8->height;
   }
  return item;
 }

};
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
NOALIGN struct _DlgStaticText_ : public _DlgItem_
{
 _char_* text_len;
 _char_* text;
 _char_* text_mem_end;
 _dword_ field_3C;
 _ptr_ font;
 _dword_ color;
 _dword_ back_color;
 _dword_ align;

// virtual
 void SetText(char* text) { CALL_2(void, __thiscall, this->v_table[13], this, text); }

// my 
 static inline _DlgStaticText_* Create(int x, int y, int width, int height, char* text, char* font_name, _dword_ text_color, int id, _dword_ align, int bkcolor)
  {return b_DlgStaticText_Create(x, y, width, height, text, font_name, text_color, id, align, bkcolor, 0);}
};
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
NOALIGN struct _DlgStaticTextPcx8ed_: public _DlgStaticText_
{
 _Pcx8_* pcx8;

// my 
 static inline _DlgStaticTextPcx8ed_* Create(int x, int y, int width, int height, char* text, char* font_name, char* bkground_pcx8_name, _dword_ text_color, int id, _dword_ text_align)
  {return b_DlgStaticTextPcx8ed_Create(x, y, width, height, text, font_name, bkground_pcx8_name, text_color, id, text_align, 0);}
 static inline _DlgStaticTextPcx8ed_* Create(int x, int y, char* text, char* font_name, char* bkground_pcx8_name, _dword_ text_color, int id, _dword_ text_align)
 {
  _DlgStaticTextPcx8ed_* item = b_DlgStaticTextPcx8ed_Create(x, y, 0, 0, text, font_name, bkground_pcx8_name, text_color, id, text_align, 0);
  if (item)
   if (item->pcx8)
   {
    item->width = item->pcx8->width;
    item->height = item->pcx8->height;
   }
  return item;
 }
};
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
NOALIGN struct _DlgTextEdit_ : public _DlgStaticTextPcx8ed_
{
 _Pcx16_* pcx16;
 _word_ caret_pos;
 _word_ max_len;

 _word_ field_width;
 _word_ field_height;
 _word_ field_x;
 _word_ field_y;

 _word_ field_64;
 _word_ field_66;
 _word_ field_68;
 _word_ field_6A;
 _byte_ field_6C;

 _bool8_ focused;

 _bool8_ redraw_actions;
 _byte_ field_6F;

// _DlgChatTextEdit_:
///////////////////////////////
 // _byte_ field_70;
 _byte_ enteringText; // +0x70
 _byte_ field_71[3];
///////////////////////////////

//virtual 
 inline int SetEditText(char* text) {return CALL_2(int, __thiscall, this->v_table[13], this, text);}
 inline void SetFocused(_bool8_ value) {CALL_2(void, __thiscall, this->v_table[14], this, value);}

// my 
 static inline _DlgTextEdit_* Create(int x, int y, int width, int height, int max_len, char* text, char* font_name, _dword_ text_color, _dword_ text_align, char* bkground_pcx8_name, int id, _bool_ has_border, int border_width, int border_height)
 {
  //////if ( (has_border) && (bkground_pcx8_name) )
  //////{
  ////// width += 2*border_width;
  ////// height += 2*border_height;
  //////}
  _DlgTextEdit_* it = b_DlgTextEdit_Create(x, y, width, height, max_len, text, font_name, text_color,  text_align, bkground_pcx8_name, 0, id, 0, has_border << 2, border_width, border_height);
  it->redraw_actions = TRUE;
  return it;
 }

};
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
NOALIGN struct _DlgStaticDef_ : public _DlgItem_
{
 _Def_* def; // 0x30
 _dword_ def_frame_index;
 _dword_ press_def_frame_index;
 _dword_ mirrored;
 _dword_ field_40;
 _word_ close_dlg;
 _word_ field_46;

 // igrik
 inline int SetFrame(signed int frame)
 { return CALL_2(int, __thiscall, 0x4EB0D0, this, frame); }
// my 
 static inline _DlgStaticDef_* Create(int x, int y, int width, int height, int id, char* def_name, int def_frame_ix, int mirrored, _bool_ close_dlg)
  {return b_DlgStaticDef_Create(x, y, width, height, id, def_name, def_frame_ix, 0, mirrored, close_dlg, DIF_DEF);}
 static inline _DlgStaticDef_* Create(int x, int y, int id, char* def_name, int def_frame_ix, int mirrored, _bool_ close_dlg)
 {
   _DlgStaticDef_* item = b_DlgStaticDef_Create(x, y, 0, 0, id, def_name, def_frame_ix, 0, mirrored, close_dlg, DIF_DEF);
   if (item)
   if (item->def)
   {
    item->width = item->def->width;
    item->height = item->def->height;
   }
   return item;
 }
};
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
NOALIGN struct _DlgStaticPcx16_ : public _DlgItem_
{
 _Pcx16_* pcx16;
 _dword_ field_34[7];
 _word_ field_50;

 static inline _DlgStaticPcx16_* Create(int x, int y, int width, int height, int id, char* pcx16_name, _dword_ flags)
  {return b_DlgStaticPcx16_Create(x, y, width, height, id, pcx16_name, flags);}
};
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
NOALIGN struct _DlgButton_ : public _DlgStaticDef_
{
 _ptr_ hotkeys_struct;
 _ptr_ hotkeys_start;
 _ptr_ hotkeys_end;
 _ptr_ hotkeys_mem_end;
 _ptr_ caption_struct;
 _ptr_ caption;
 _ptr_ caption_end;
 _ptr_ caption_mem_end;

 inline int ProcessMsg(_EventMsg_* msg)
 { return CALL_2(int, __thiscall, 0x455E70, this, msg); }

// my 
 static inline _DlgButton_* Create(int x, int y, int width, int height, int id, char* def_name, int def_frame_ix, int def_frame_press_ix, _bool_ close_dlg, int hotkey, _dword_ flags)
  {return b_DlgButton_Create(x, y, width, height, id, def_name, def_frame_ix, def_frame_press_ix, close_dlg, hotkey, flags);}
 static inline _DlgButton_* Create(int x, int y, int id, char* def_name, int def_frame_ix, int def_frame_press_ix, _bool_ close_dlg, int hotkey)
 {
  _DlgButton_* item = b_DlgButton_Create(x, y, 0, 0, id, def_name, def_frame_ix, def_frame_press_ix, close_dlg, hotkey, DIF_BUTTON);

   if (item)
   if (item->def)
   {
    item->width = item->def->width;
    item->height = item->def->height;
   }
   return item;
 }
 inline int SetHotKey(int hotkey)
  { return CALL_4(int, __thiscall, 0x404230, &this->hotkeys_struct, this->hotkeys_end, 1, &hotkey); }
};
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
NOALIGN struct _DlgTextButton_ : public _DlgButton_
{
 _ptr_ caption_font;
 _dword_ caption_color;

// my 
 static inline _DlgTextButton_* Create(int x, int y, int width, int height, int id, char* def_name, char* caption_text, char* font_name, int def_frame_ix, int def_frame_press_ix, _bool_ close_dlg, int hotkey, _dword_ flags, int caption_color)
  {return b_DlgTextButton_Create(x, y, width, height, id, def_name, caption_text, font_name,  def_frame_ix, def_frame_press_ix, close_dlg, hotkey, flags, caption_color);}
static inline _DlgTextButton_* Create(int x, int y, int id, char* def_name, char* caption_text, char* font_name, int def_frame_ix, int def_frame_press_ix, _bool_ close_dlg, int hotkey, int caption_color)
 {
  _DlgTextButton_* item = b_DlgTextButton_Create(x, y, 0, 0, id, def_name, caption_text, font_name,  def_frame_ix, def_frame_press_ix, close_dlg, hotkey, DIF_BUTTON, caption_color);

  if (item)
   if (item->def)
   {
    item->width = item->def->width;
    item->height = item->def->height;
   }
  return item;
 }
};
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
NOALIGN struct _DlgCallbackButton_ : public _DlgButton_
{
 _ptr_ callback;

// my 
 static inline _DlgCallbackButton_* Create(int x, int y, int width, int height, int id, char* def_name, _ptr_ callback, int def_frame_ix, int def_frame_press_ix)
  {return b_DlgCallbackButton_Create(x, y, width, height, id, def_name, callback, def_frame_ix, def_frame_press_ix);}
 static inline _DlgCallbackButton_* Create(int x, int y, int id, char* def_name, _ptr_ callback, int def_frame_ix, int def_frame_press_ix)
 {
  _DlgCallbackButton_* item = b_DlgCallbackButton_Create(x, y, 0, 0, id, def_name, callback, def_frame_ix, def_frame_press_ix);
  if (item)
   if (item->def)
   {
    item->width = item->def->width;
    item->height = item->def->height;
   }
  return item;
 }
};
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
NOALIGN struct _DlgScrollableText_ : public _DlgItem_
{
 _ptr_ font;
 _int_ lines_count; 
 _dword_ field_38[3];
 _ptr_ items_list;
 _ptr_ items_first;
 _ptr_ items_last;
 _ptr_ items_mem_end;
 _DlgScroll_* scroll_bar;
 _dword_ field_58;

// my 
 static inline _DlgScrollableText_* Create(char* text, int x, int y, int width, int height, char* font_name, _dword_ text_color, _bool_ is_blue)
  {return b_DlgScrollableText_Create(text, x, y, width, height, font_name, text_color, is_blue);}

};
////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// b_MsgBox style
#define MBX_OK   1
#define MBX_OKCANCEL 2
#define MBX_RMC   4

enum MsgBoxStyle : _int32_
{
    OK          = 1,
    OK_CANCEL   = 2,
    RMC         = 4,
    OKEY        = 5, // не имеeт функции CallBack (короче ускоренная)
    CANCEL      = 6, // не имеeт функции CallBack (короче ускоренная)
    TAKE        = 7,
    OPTION      = 10,
};

enum MsgBoxItemIDs : _int32_
{
    // кнопки MsgBox (типы 1, 2)
    ID_OK_1     = 30722,
    ID_OK_2     = 30725,
    ID_CANCEL_2 = 30726,
    // кнопки MsgBox (типы 7, 10)
    ID_OK_10     = 30720,
    ID_CANCEL_10 = 30721,
    // элементы MsgBox (типы 7, 10)
    ITEM_0    = 30729,
    ITEM_1    = 30730,
    ITEM_2    = 30731,
    ITEM_3    = 30732,
    ITEM_4    = 30733,
    ITEM_5    = 30734,
    ITEM_6    = 30735,
    ITEM_7    = 30736,
};

// #define o_TimeClick (*(_int_*)0x6977D4)
#define b_MsgBox_Style_id (*(_int_*)0x699570)
#define b_MsgBox_Result_id (*(_int_*)0x699424)

inline _bool_ o_MsgBox(char* text, int style = MBX_OK, int x = -1, int y = -1, int i1_type = -1, int i1_stype = 0, int i2_type = -1, int i2_stype = 0, int unknown = -1, int time = 0, int i3_type = -1, int i3_stype = 0)
{
  o_WndMgr->result_dlg_item_id = -1;
  CALL_12(void, __fastcall, 0x4F6C00, text, style, x, y, i1_type, i1_stype, i2_type, i2_stype, unknown, time, i3_type, i3_stype);
  return (o_WndMgr->result_dlg_item_id);
}

inline _bool_ b_MsgBox(char* text)
{
 CALL_12(void, __fastcall, 0x4F6C00, text, 5, -1, -1, -1, 0, -1, 0, -1, 0, -1, 0);
 return (o_WndMgr->result_dlg_item_id == DIID_OK);
}

inline _bool_ b_MsgBox(char* text, int style)
{
 CALL_12(void, __fastcall, 0x4F6C00, text, style, -1, -1, -1, 0, -1, 0, -1, 0, -1, 0);
 return (o_WndMgr->result_dlg_item_id == DIID_OK);
}

inline _bool_ b_MsgBoxD(char* text, int style, int def_id, int def_frame)
{
 CALL_12(void, __fastcall, 0x4F6C00, text, style, -1, -1, def_id, def_frame, -1, 0, -1, 0, -1, 0);
 return (o_WndMgr->result_dlg_item_id == DIID_OK);
}

inline _bool_ b_MsgBoxC(char* text, int style, int x, int y)
{
 CALL_12(void, __fastcall, 0x4F6C00, text, style, x, y, -1, 0, -1, 0, -1, 0, -1, 0);
 return (o_WndMgr->result_dlg_item_id == DIID_OK);
}
// 0x65F4D4 тут дефы


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

//MY///////////////////////////////////////////////////////////////////////////////////

NOALIGN struct _DlgStdBackground_
{
 static _DlgStaticPcx16_* Create(int x, int y, int width, int height, int id, _bool_ have_bottombar, int player_id /*color*/);
 static inline _DlgStaticPcx16_* Create(_Dlg_* dlg, int id, _bool_ have_bottombar, int player_id /*color*/)
  {return Create(0, 0, dlg->width, dlg->height, id, have_bottombar, player_id);}
};

NOALIGN struct _DlgBlueBackground_
{
 static _DlgStaticPcx16_* Create(int x, int y, int width, int height, int id);
};

//MY///////////////////////////////////////////////////////////////////////////////////
class _CustomDlg_;

typedef int (__stdcall *_func_CustomDlgProc)(_CustomDlg_* dlg, _EventMsg_* msg);

class _CustomDlg_ : public _Dlg_
{
public:
   _func_CustomDlgProc dlg_proc;
   _dword_ custom_data[3];
   static _ptr_ v_table_funcs[15];
   static int __fastcall DlgProcBridge(_CustomDlg_* this_, _dword_ not_used, _EventMsg_* msg);

 
public:
 static _CustomDlg_* Create(int x, int y, int width, int height, _dword_ flags, _func_CustomDlgProc dlg_proc);
};

_Pcx8_* CreateSimpleFrame(int width, int height);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// ниже идут функции by [igrik] ////////////////////////////////////////////////////////

// создание подложки (заднего фона) под новые диалоговые окна (под цвет текущего игрока)
inline void DlgStdBackground_Create(_Dlg_* dlg, int color) 
{
  CALL_5 (int, __thiscall, 0x48FA80, dlg, dlg->x, dlg->y, dlg->width, dlg->height);

  for (_dword_ i = dlg->field_4C; i <= dlg->field_50; ++i)
  {
    CALL_5 (int, __thiscall, 0x5FF400, dlg, 512, 13, i, /* o_GameMgr->GetMeID()*/ color);  
  }
}

#define o_Pal_Blue 0
#define o_Pal_Black 2
#define o_Pal_Pink 4
#define o_Pal_Green 32
#define o_Pal_BlackBlue 36
#define o_Pal_Purpe 38
#define o_Pal_Red 43
#define o_Pal_Grey 47
#define o_Pal_Y 118

#define ON 1
#define OFF 0

inline void b_YellowFrame_Create(_Dlg_* dlg, int x, int y, int width, int height, int id, int show, int color) {
  dlg->AddItem(CALL_8 (_DlgItem_*, __thiscall, 0x44FE00, o_New(56), x, y, width, height, id, *(int*)(*(int*)0x6AAD18 + color), 1024)); 
  if (show) { 
    dlg->GetItem(id)->SendCommand(5, 4);
  } else dlg->GetItem(id)->SendCommand(6, 4);
}


// замена цвета item->Field<int>(0x30) 
NOALIGN struct _DlgColorFrame_ : public _DlgItem_
{
  _int_ color; // +48
  _int_ field_34; // +52

 inline void SetColor(int color) {this->color = *(int*)(*(int*)0x6AAD18 + color);}
};

////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
NOALIGN struct _ScrollItems_
{
  int step;
  int text_hight;
  int item_id_start;
  int item_id_end;
  int item_id_show_start;
  int item_id_show_end; 
  int not_redraw; 
};


////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
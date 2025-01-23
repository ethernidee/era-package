////////////////////////////////////////////////////////////////////////////////////
// (HD 3.0) Some global HoMM3 functions and variables
// Author: Alexander Barinov (aka baratorch, aka Bara) e-mail: baratorch@yandex.ru
// Thanks: ZVS, GrayFace
////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Base.h"

// res
struct _BinTree_;
struct _BinTreeItem_;
struct _Palette16_;
struct _Palette24_;
struct _Pcx8_;
struct _Pcx16_;
struct _DefFrame_;
struct _DefGroup_;
struct _Def_;
struct _TXT_;
// GUI
struct _DlgMsg_;
struct _Manager_;
struct _WndMgr_;
struct _Dlg_;
struct _DlgItem_;
struct _DlgStaticPcx8_;
struct _DlgScroll_;
struct _DlgStaticText_;
struct _DlgTextEdit_;
struct _DlgStaticDef_;
struct _DlgStaticText_;
struct _DlgTextEdit_;
struct _DlgStaticDef_;
struct _DlgStaticPcx16_;
struct _DlgButton_;
struct _DlgTextButton_;
struct _DlgCallbackButton_;
struct _DlgScrollableText_;

#define o_New(size) CALL_1(_ptr_, __cdecl, 0x617492, size)
#define o_Delete(ptr) CALL_1(void, __cdecl, 0x60B0F0, ptr)


#define o_PauseVideo() CALL_0(void, __cdecl, 0x597AA0)
#define o_ContinueVideo() CALL_0(void, __cdecl, 0x597B50)

#define o_GetIngameCursorPos(px, py) CALL_2(void, __stdcall, 0x50D700, px, py);


#define o_WndMgr (*(_WndMgr_**)0x6992D0)
#define o_GameMgrPalette16 (*(_Palette16_**)0x6AAD18)
#define o_PlayersPalette16 (*(_Palette16_**)0x6AAD10)
#define o_PlayersPalette24 (*(_Palette24_**)0x6AAD14)

#define o_BinTreeHead (*(_BinTree_*)0x69E560)

#define o_GENRLTXT_TXT (*(_TXT_**)0x6A5DC4)
#define o_ADVEVENT_TXT (*(_TXT_**)0x696A68)
#define o_ARTEVENT_TXT (*(_TXT_**)0x696CC0)
#define o_PLCOLORS_TXT (*(_TXT_**)0x6A7584)
#define o_TCOMMAND_TXT (*(_TXT_**)0x6A62F8)
#define o_RESTYPES_TXT (*(_TXT_**)0x6A5390)
#define o_NPC_TXT (*(_TXT_**)0x2860724)
// ..............

#define o_Tiny_Fnt  (*(_Fnt_**)0x698A54)
#define o_Smalfont_Fnt (*(_Fnt_**)0x698A58)
#define o_Medfont_Fnt (*(_Fnt_**)0x698A5C)
#define o_Bigfont_Fnt (*(_Fnt_**)0x698A60)
#define o_Calli10R_Fnt (*(_Fnt_**)0x698A64)


#define p_GameMgr (*(_ptr_*)0x699538)
#define o_GameMgrMgr_GetMeID() CALL_1(_int_, __thiscall, 0x4CE6E0, p_GameMgr)



// ����� ���������� ��������� �����.
#define RandSeed *(_dword_*)(CALL_0(_ptr_, __cdecl, 0x61D8C3) + 20)

// ��������� ����� ���������� ��������� �����.
#define SetRandSeed(Seed) CALL_1(void, __cdecl, 0x61841F, Seed)

// ��������� ������.
#define o_MemAlloc(Size) CALL_1(_ptr_, __cdecl, 0x617492, Size)

// ������������ ������.
#define o_MemFree(lpMem) CALL_1(void, __cdecl, 0x60B0F0, lpMem)



// ��������� �� ������ ������� ���� � ������.
#define LIST_SIZE_ERROR_MESSAGE "Cannot do \"%s\" operation with type of size: %d"

// ������� ��������� �� ������ ������� ���� � ������.
#define LIST_SIZE_ERROR_SHORT_MESSAGE "List type size error"


#define _H3Str_ _HStr_
NOALIGN struct _HStr_ : public _Struct_
{
  _byte_ init;
  _byte_ _u[3];
  _char_* c_str;
  _int_ length;
  _int_ size;

  inline void   Destruct(_bool_ delete_)  { CALL_2(void, __thiscall, 0x404130, this, delete_); }
  inline _HStr_*  CopyObject(_HStr_* target, int a3, int a4)  { return CALL_4(_HStr_*, __thiscall, 0x404810, this, target, a3, a4); }
  inline _bool8_  RemoveAndSetExpandSize(int newSize, _byte_ a3)  { return CALL_3(_bool8_, __thiscall, 0x404A40, this, newSize+1, a3); }
  inline _int_  SetLength(int length)  { return CALL_2(_int_, __thiscall, 0x404A20, this, length+1); }


  inline _HStr_*  Set(char* str, int len)   { return CALL_3(_HStr_*, __thiscall, 0x404180, this, str, len); }
  inline _HStr_*  Set(char* str)        { return Set(str, strlen(str)); }
  _HStr_()
  {
    _byte_ v = 1;
    init = v;
    c_str = NULL;
    length = 0;
    size = 0;
  }
};

// ��������� ��������� ������.
#define _H3Vector_ _List_
#pragma pack(push, 1)
template <typename _type_> struct _List_
{
public:
  // ��� ������ �������������-������� ������ ��� ��������� ���� ���������� �������� �� �������������������� ����������.
  _byte_ Creation; // +0h;
  // ��������� ������������, �� ������������.
  _byte_ Dummy_f1[3]; // +1h;
  // ����� ������ ������ ������.
  _type_* Data; // +4h;
  // ����� ����� ������.
  _type_* EndData; // +8h;
  // ����� ���������� �� ������ ������.
  _ptr_ EndMem; // +Ch;
  
  
  
  
  
  
  
  
  
  
  
  
  // built-in
  
  
  // ��������� ���������� ��������� � ������.
  // �������� ��� ����� �������� � 4.
  inline _int_ GetItemsCount()
  {
    // ��� ������� ������� ���� - ���� �������.
    switch (sizeof(_type_))
    {
      case 4:
        return CALL_1(_int_, __thiscall, 0x54D2B0, this);
        
      // ���� ������ �� �������� �� ��� ���� �������, ���������� ������.
      default:
        ShowVA(LIST_SIZE_ERROR_MESSAGE, "GetItemsCount", sizeof(_type_));
        throw LIST_SIZE_ERROR_SHORT_MESSAGE;
    }
  }

  // ��������� ���������� ��������� � ������.
  // �������� ��� ����� �������� � 64.
  inline _int_ GetItemsCount_Size64()
  {
    // ��� ������� ������� ���� - ���� �������.
    switch (sizeof(_type_))
    {
      case 64:
        return CALL_1(_int_, __thiscall, 0x4CF3D0, this);
        
      // ���� ������ �� �������� �� ��� ���� �������, ���������� ������.
      default:
        ShowVA(LIST_SIZE_ERROR_MESSAGE, "GetItemsCount", sizeof(_type_));
        throw LIST_SIZE_ERROR_SHORT_MESSAGE;
    }
  }
  
  
  
  
  
  
  // ���������� ��������� � ������ �� �������.
  // �������� ��� ����� �������� � 4.
  // DestAddr - ����� �����, ������� � �������� ����� ���� ����� ��������, ������ ������� � ����� ����� ����� ��������.
  // Count - ���������� ����������� ���������.
  // SourceAddr - �����, ������� � �������� ����� ������� ����� ��������.
  inline void InsertRange(_type_* DestAddr, _int_ Count, _type_* SourceAddr)
  {
    // ��� ������� ������� ���� - ���� �������.
     switch (sizeof(_type_))
    {
      case 4:
        CALL_4(void, __thiscall, 0x4230D0, this, DestAddr, Count, SourceAddr);
        break;
        
      // ���� ������ �� �������� �� ��� ���� �������, ���������� ������.
      default:
        ShowVA(LIST_SIZE_ERROR_MESSAGE, "InsertRange", sizeof(_type_));
        throw LIST_SIZE_ERROR_SHORT_MESSAGE;
    }
  }
  

  // ���������� ��������� � ������ �� �������.
  // �������� ��� ����� �������� � 64.
  // 4D0870
  
  
  
  
  
  // �������� ���������� �������� � ��������������� ���������
  // ���� �������� � ����� ��������� � ������ ���, ������ �������� �� �����.
  // �������� ��� ����� �������� � 4.
  inline void DeleteLastValue(_type_ Value)
  {
    // ��� ������� ������� ���� - ���� �������.
    switch (sizeof(_type_))
    {
      case 4:
        CALL_2(void, __fastcall, 0x43E720, this, Value);
        break;
        
      // ���� ������ �� �������� �� ��� ���� �������, ���������� ������.
      default:
        ShowVA(LIST_SIZE_ERROR_MESSAGE, "DeleteLastValue", sizeof(_type_));
        throw LIST_SIZE_ERROR_SHORT_MESSAGE;
    }
  }
  
  
  // �������� �������� �� ��� ������ (�� ��������� ����� ������ ����� ������ ���� ���������� � ���� ������� �������� � ������).
  // �������� ��� ����� �������� � 4.
  inline void DeleteEntry(_type_* Addr)
  {
    // ��� ������� ������� ���� - ���� �������.
    switch (sizeof(_type_))
    {
      case 4:
        CALL_2(void, __thiscall, 0x54CDC0, this, Addr);
        break;
        
      // ���� ������ �� �������� �� ��� ���� �������, ���������� ������.
      default:
        ShowVA(LIST_SIZE_ERROR_MESSAGE, "DeleteEntry", sizeof(_type_));
        throw LIST_SIZE_ERROR_SHORT_MESSAGE;
    }
  }
  
  
  // �������� ��������� � ��������� ��������� (������ - �������, ����� - �� �������).
  // �������� ��� ����� �������� � 4.
  inline void DeleteRange(_type_* FirstAddr, _type_* EndAddr)
  {
    // ��� ������� ������� ���� - ���� �������.
    switch (sizeof(_type_))
    {
      case 4:
        CALL_3(void, __thiscall, 0x4D4E90, this, FirstAddr, EndAddr);
        break;
        
      // ���� ������ �� �������� �� ��� ���� �������, ���������� ������.
      default:
        ShowVA(LIST_SIZE_ERROR_MESSAGE, "DeleteRange", sizeof(_type_));
        throw LIST_SIZE_ERROR_SHORT_MESSAGE;
    }
  }
  
  
  // �������� ���� ��������� �� ������.
  // �������� ��� ����� �������� � 4.
  inline void DeleteAll()
  {
    // ��� ������� ������� ���� - ���� �������.
    switch (sizeof(_type_))
    {
      case 4:
        CALL_1(void, __thiscall, 0x448A40, this);
        break;
        
      // ���� ������ �� �������� �� ��� ���� �������, ���������� ������.
      default:
        ShowVA(LIST_SIZE_ERROR_MESSAGE, "DeleteAll", sizeof(_type_));
        throw LIST_SIZE_ERROR_SHORT_MESSAGE;
    }
  }
  
  
  
  
  
  
  
  
  
  
  
  
  // user
  
  
  
  
  // ����������� ������.
  inline _List_()
  {
    this->Data = 0;
    this->Creation = 0;
    this->EndData = 0;
    this->EndMem = 0;
  }
  
  
  // ���������� ������.
  inline ~_List_()
  {
    o_MemFree(this->Data);
    this->Data = 0;
    this->EndData = 0;
    this->EndMem = 0;
  }
  
  
  
  
  
  // �������� ������� �������� � ������.
  inline _bool_ HasValue(_type_ Value)
  {
    // �������� �� ���� ��������� ������.
    for (_int_ i = 0; i < this->GetItemsCount(); i++)
    {
      // ���� ����� ������ �������� - ���������� ���������.
      if ((*this)[i] == Value) return TRUE;
    }
    
    // ������ �������� �� �������.
    return FALSE;
  }
  
  
  
  
  
  // �������� ������ �� �������.
  // �������������� ������������� ������� - � ���� ������ ������� ����� ������� � ����� ������.
  // �������� �� ������������ ������� �����������.
  inline _type_& operator[](_int_ index)
  {
    // ��� �������������� ������� ������ ��� ������.
    if (index >= 0)
    {
      return (this->Data)[index];
    }
    // ��� �������������� ������� ���� � ����� ������.
    else
    {
      return *(_type_*)(this->EndData + index);
    }
  }
  
  
  
  
  
  
  // ���������� �������� � ����� ������ �� ��������.
  inline void Append(_type_ Item)
  {
    // ��������� ���� ������� � ����� ������.
    this->InsertRange(this->EndData, 1, &Item);
  }
  
  
  
  
  // ������� �������� �� ������� � ����������� ��������� ��������.
  // �������������� ������������� ������� - � ���� ������ ������� ����� ������� � ����� ������.
  // ��� ������ ��� ���������� ����� ����� ��������� ������� ������.
  // ��� ������������ ������� ������ �� ��������� ���������, � ��������� ����� �����.
  inline _type_ Pop(_int_ index = -1)
  {
    // ���������� ��� �������� ���������.
    _type_ res = (*this)[index];
    
    // ������� ��������������� �������.
    this->DeleteEntry(&((*this)[index]));
    
    // ��������� �������� �������.
    return res;
  }
  
  
};
#pragma pack(pop)

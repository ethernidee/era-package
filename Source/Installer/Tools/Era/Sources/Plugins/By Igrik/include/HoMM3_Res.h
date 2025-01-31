// /////////////////////////////////////////////////////////////////////////////////
// (HD 3.0) HoMM3 Resources (PCXes, DEFs, Palettes, Fonts, TXTes)
// Author: Alexander Barinov (aka baratorch, aka Bara) e-mail: baratorch@yandex.ru
// Thanks: ZVS, GrayFace
////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "HoMM3_Base.h"

#define RGB565_fromR8G8B8(r, g, b) \
 (_word_)( (((int)(r) >> 3) << 11) | (((int)(g) >> 2) << 5) | (((int)(b)) >> 3) )

struct _ColorRGB888_;
struct _Pcx_;

NOALIGN struct _BinTreeItem_ // size = 28
{
 _ptr_* v_table; // + 0
 _char_ name[12]; // + 4
 _dword_ name_end; // + 16
 _dword_ type; // + 20
 _int_ ref_count; // + 24
 
 
 // Удалить ссылку на объект и, если она последняя, уничтотжить его.
 void DerefOrDestruct()
 {
   CALL_1(void, __thiscall, this->v_table[1], this);
 }

};

NOALIGN struct _BinTree_
{
 _BinTree_* left;
 _BinTree_* parent;
 _BinTree_* right;
 _char_ name[12];
 _dword_ name_end;
 _BinTreeItem_* item;
 _dword_ field_20;

 // my
 inline _BinTreeItem_* FindItem(char* name)
 {
  if (name)
  {
   _BinTree_* search_result = CALL_2(_BinTree_*, __thiscall, 0x55EE00, this, name);
   if ((search_result == this->parent) || (_strcmpi(name, search_result->name) < 0))
    return NULL;
   return search_result->item;
  }
  else
   return NULL;
 }

 inline void AddItem(_BinTreeItem_* item, char* name)
 {
  _ptr_ buf[2];
  char named_item_block[20]; 
  MemCopy(named_item_block, name, 12);
  *(_dword_*)(named_item_block + 12) = 0;
  *(_BinTreeItem_**)(named_item_block + 16) = item;
  CALL_3(void, __thiscall, 0x55DDF0, this, buf, named_item_block);
 }
};




NOALIGN struct _Wav_ : public _BinTreeItem_ // size = 52
{
 _dword_ PlayingIndex; // + 28 = 0 при загрузке; индекс среди проигрывающихся звуков
 _ptr_ data; // + 32 - указатель на загруженное содержимое wav-файла
 _dword_ data_size; // + 36 размер данных (размер wav-файла)
 _dword_ field_28; // + 40 = 0 при загрузке // после инициализации звуков монстров = 3 
 _dword_ field_2C; // + 44 = 127 при загрузке // после инициализации звуков монстров = 64
 _bool32_ no_loop; // + 48 = 1 при загрузке // после инициализации звуков монстров = 0 у звука move монстра и = 1 у остальных звуков монстра 
};



// Проигрывающийся звук.
NOALIGN struct _Sample_ // size = 8
{
  _Wav_* Wav; // +0h; Звук
  _dword_ PlayingInd; // +4h; Индекс среди проигрывающихся звуков
};



// Загрузка звука по имени.
_Wav_* __fastcall LoadWav(_cstr_ Name);





NOALIGN struct _Palette16_ : public _BinTreeItem_
{
 _word_ colors[256]; // + 28

 //my
 void Colorize(int player_id) {CALL_2(void, __fastcall, 0x6003E0, this->colors, player_id);}
};

NOALIGN struct _ColorRGB888_
{
 _byte_ r;
 _byte_ g;
 _byte_ b;
};

NOALIGN struct _Palette24_ : public _BinTreeItem_
{
 _ColorRGB888_ colors[256]; // + 28
};

NOALIGN struct _Pcx_ : public _BinTreeItem_
{
 _dword_ buf_size; // + 28
 _dword_ pic_size;
 _dword_ width;
 _dword_ height;
 _dword_ scanline_size;
 _ptr_ buffer;
};


NOALIGN struct _DefFrame_ : public _BinTreeItem_
{
 _dword_  frm_size; // +1Ch
 _dword_  buf_size; // +20h
 _dword_  compression_type; // +24h
 _dword_  def_width; // +28h
 _dword_  def_height; // +2Ch
 _dword_  frame_width; // +30h
 _dword_  frame_height; // +34h
 _dword_  frame_left; // +38h
 _dword_  frame_top; // +3Ch
 _dword_  unknown_40; // +40h
 _ptr_  buffer; // +2Ch

 // my
 _dword_ DrawInterfaceToPcx16(_Pcx_* dst_pcx16, _int_ dst_x, _int_ dst_y, _Palette16_* palette16)
 {
  return CALL_14(_dword_, __thiscall, 0x47BE90, this, 0, 0, def_width, def_height, dst_pcx16->buffer, dst_x, dst_y, dst_pcx16->width, dst_pcx16->height, dst_pcx16->scanline_size, palette16, 0, 1);
 }
};

NOALIGN struct _DefGroup_
{
 _dword_  frames_count; 
 _dword_  frames_size;
 _DefFrame_** frames;

};

#define o_LoadDef(name) CALL_1(_Def_*, __fastcall, 0x55C9C0, name)

NOALIGN struct _Def_ : public _BinTreeItem_
{
 _DefGroup_** groups; // + 28
 _Palette16_* palette16; //  + 32
 _Palette24_* palette24; //  + 36
 _dword_   groups_count; //  + 40
 _ptr_   active_groups; //  + 44
 _dword_   width; //  + 48
 _dword_   height; //  + 52

 //normal
 // Загрузка def`а по имени.
 static inline _Def_* Load(char* def_name) {return o_LoadDef(def_name);}
 
 
 // Отрисовка def`а с полупрозрачностью. При включении полупрозрачности ихображение полностью становится полупрозрачным.
 // Используется для отрисовки анимаций в бою.
 inline void Draw_Transparent(_int_ Group, _int_ Frame, _int_ Img_Def_X, _int_ Img_Def_Y, _int_ Img_Width, _int_ Img_Height, _dword_ PcxBuffer,
                      _int_ Dest_X, _int_ Dest_Y, _int_ Dest_Width, _int_ Dest_Height,
                      _dword_ ScanlineSize, _bool_ Reflected, _bool_ IsTransparent)
 {
   CALL_15(void, __thiscall, 0x47BA90, this, Group, Frame, Img_Def_X, Img_Def_Y, Img_Width, Img_Height, PcxBuffer,
                                       Dest_X, Dest_Y, Dest_Width, Dest_Height,
                                       ScanlineSize, Reflected, IsTransparent);
 }
 
 
 // Отрисовка def`а с пользовательским спеццветом, заменяющимся на указанный.
 // Используется для стеков в бою (рамка вокруг стоящего стека).
 inline void Draw_SpecColorReplace(_int_ Group, _int_ Frame, _int_ Img_Def_X, _int_ Img_Def_Y, _int_ Img_Width, _int_ Img_Height, _dword_ PcxBuffer,
                      _int_ Dest_X, _int_ Dest_Y, _int_ Dest_Width, _int_ Dest_Height,
                      _dword_ ScanlineSize, _bool_ Reflected, _int_ SpecColor)
 {
   CALL_15(void, __thiscall, 0x47B680, this, Group, Frame, Img_Def_X, Img_Def_Y, Img_Width, Img_Height, PcxBuffer,
                                       Dest_X, Dest_Y, Dest_Width, Dest_Height,
                                       ScanlineSize, Reflected, SpecColor);
 }
 
 // Отрисовка def`а (та, что используется для отрисовки снарядов в бою (возможна без использования спеццветов)).
 inline void BBULL_Draw(_int_ Group, _int_ Frame, _int_ Img_Def_X, _int_ Img_Def_Y, _int_ Img_Width, _int_ Img_Height, _dword_ PcxBuffer,
                      _int_ Dest_X, _int_ Dest_Y, _int_ Dest_Width, _int_ Dest_Height,
                      _dword_ ScanlineSize, _bool_ Reflected, _bool_ UseSpecColors)
 {
   CALL_15(void, __thiscall, 0x47B610, this, Group, Frame, Img_Def_X, Img_Def_Y, Img_Width, Img_Height, PcxBuffer,
                                       Dest_X, Dest_Y, Dest_Width, Dest_Height,
                                       ScanlineSize, Reflected, UseSpecColors);
 }
 
 
 
 
 ////my
 //static _Def_* LoadFromFile(char file_name);
};

// text alignment flags
#define ALIGN_H_LEFT 0
#define ALIGN_H_CENTER 1
#define ALIGN_H_RIGHT 2
#define ALIGN_V_TOP  0
#define ALIGN_V_CENTER 4
#define ALIGN_V_BOTTOM 8

NOALIGN struct _Fnt_:  public _BinTreeItem_
{
 NOALIGN struct _CharSize_
 {
  int width;
  int left;
  int right;
 };

  _byte_  first;          /*28 first character in font              */
  _byte_  last;           /*29 last character in font           */
  _byte_  depth;          /*30 depth of font (1=monochrome mask only    */
                  /* otherwise mask is an additional plane)   */
  _int8_  xspace;         /*31 X spacing (normally 1)           */
  _int8_  yspace;         /*32 Y spacing (distance between text lines)      */
  _byte_  height;         /*33 Height of all characters in this font    */
  
  _byte_ unknown[26];
  
  _CharSize_ char_sizes[256];

 // normal
 inline static _Fnt_* Load(char* filename) { return CALL_1(_Fnt_*, __fastcall, 0x55BD10, filename); }
 inline void DrawTextToPcx16(_char_* text, _Pcx16_* pcx16, _int_ x, _int_ y, _int_ width, _int_ height, _byte_ color, _dword_ align, _int_ a10)
  {CALL_10(void, __thiscall, 0x4B51F0, this, text, pcx16, x,y,width,height, color, align, a10);}

 // my 
 _int_ GetLineWidth(char* text);
 // inline _int_ GetLineWidth(char* text) { return CALL_2(_int_, __thiscall, 0x4B5680, this, text); }

  inline _int_ GetMax_WordWidth(const char* string) {
    return CALL_2(_int_, __thiscall, 0x4B5770, this, string);
  }

  inline _int_ GetMax_LineWidth(const char* string) {
    return CALL_2(_int_, __thiscall, 0x4B56F0, this, string);
  }

  inline _int_ GetLinesCountInText(const char* string, int width) {
    return CALL_3(_int_, __thiscall, 0x4B5580, this, string, width);
  }
 
};

// #define o_LoadTXT(name) CALL_1(_TXT_*, __fastcall, 0x55C2B0, name)
#define o_LoadTXT(name) CALL_1(_TXT_*, __fastcall, 0x55BFE0, name)
NOALIGN struct _TXT_ : public _BinTreeItem_
{
 inline static _TXT_* Load(char* filename) {return o_LoadTXT(filename);}
 inline char* GetString(int index) { return *(char **)(*(_ptr_*)((_ptr_)(this) + 32) + (_dword_)(index -1)*4);}
};


#define o_LoadPcx8(name) CALL_1(_Pcx8_*, __fastcall, 0x55AA10, name)

NOALIGN struct _Pcx8_ : public _Pcx_
{
 _Palette16_ palette16;
 _Palette24_ palette24;

 //normal
 static inline _Pcx8_* Load(_char_* pcx_name) { return o_LoadPcx8(pcx_name); }
 inline void DrawToPcx16(int src_x, int src_y, int width, int height, _Pcx16_* dst_pcx16, int dst_x, int dst_y, _bool_ transparent)
  {CALL_9(void, __thiscall, 0x44FA80, this, src_x, src_y, width, height, dst_pcx16, dst_x, dst_y, transparent);}

 //my
 static _Pcx8_* CreateNew(char* name, int width, int height);
 static _Pcx8_* CreateFromBMP(char* name, char* file_name);
 static void Delete(_Pcx8_* pcx8);

 void SetPaletteFrom(_Pcx8_* pcx8);
 void DrawPcx8(_Pcx8_* pcx8, int x, int y);
 void DrawPcx8(_Pcx8_* pcx8, int x, int y, int width, int height);
 void Fill(_byte_ color_index);
 void FillRect(_byte_ color_index, int x, int y, int width, int height);


};

#define o_LoadPcx16(name) CALL_1(_Pcx16_*, __fastcall, 0x55B1E0, name)
#define o_DoLoadPcx16(name) CALL_1(_Pcx16_*, __thiscall, 0x55AE50, name)
NOALIGN struct _Pcx16_ : public _Pcx_
{
 _byte_ have_ddsurface_buffer;


 //normal
 inline void DrawSurface16(int src_x, int src_y, int src_w, int src_h, int surface_buffer, int dst_x, int dst_y, int surface_w, int surface_h, int surface_scanline, int transparent_color)
 {
   CALL_12(void, __thiscall, 0x44DF80, this, src_x, src_y, src_w, src_h, surface_buffer, dst_x, dst_y, surface_w, surface_h, surface_scanline, transparent_color);
 }
 
 inline void DrawShadowRect(int x, int y, int width, int height)
 {
   CALL_5(void, __thiscall, 0x44E2C0, this, x, y, width, height);
 }
 
 
 // Копирование изображения в данное.
 inline void CopySurface16(int surface_buffer, int src_x, int src_y, int surface_w, int surface_h, int surface_scanline)
 {
   CALL_7(void, __thiscall, 0x44E0C0, this, surface_buffer, src_x, src_y, surface_w, surface_h, surface_scanline);
 }
 
 
 
 
 // my
 static _Pcx16_* CreateNew(char* name, int width, int height);
 static void Delete(_Pcx16_* pcx16);

 static _Pcx16_* CreateFromBMP(char* name, char* file_name);

 void FillRect(_word_ color, int x, int y, int w, int h);
 void DrawPcx16(_Pcx16_* src_pcx16, int x, int y, int width, int height);
 void DrawPcx16(_Pcx16_* src_pcx16, int src_x, int src_y, int width, int height, int dst_x, int dst_y);
 void DrawPcx16(_Pcx16_* src_pcx16, int x, int y);
 void DrawPcx16Resized(_Pcx16_* src_pcx16, int src_width, int src_height, int dst_x, int dst_y, int dst_width, int dst_height);
 void DrawPcx8(_Pcx8_* src_pcx8, int src_x, int src_y, int width, int height, int dst_x, int dst_y);
};



// Границы перерисовки.
NOALIGN struct _RedrawBorders_
{
  _int_ Left; // Левая
  _int_ High; // Верхняя
  _int_ Right; // Правая
  _int_ Low; // Нижняя
};

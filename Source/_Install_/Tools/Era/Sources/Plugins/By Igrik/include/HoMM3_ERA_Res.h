#pragma once

#include "homm3.h"

char* GetShortFileName_Y(char* filename)
  {
    char* str_f = filename;
    char* str_r = NULL;

    if (filename)
    {
      for (int i = strlen(str_f) - 1; i >= 0; i--)
        if (str_f[i] == '\\')
        {
          str_r = str_f + i + 1;
          break;
        }

      if (!str_r) str_r = str_f;
    }

    return str_r;
  }

// загружать картинку так _Pcx8_* o_Pic = o_LoadBMP8_LongName("Длинный путь к картинке");
_Pcx8_* o_LoadBMP8_LongName(char* pathTo_File){
  if (!pathTo_File) return NULL;
  char* name = GetShortFileName_Y(pathTo_File);
  _Pcx8_* result = _Pcx8_::CreateFromBMP(name, pathTo_File);
  if (result){
    o_BinTreeHead.AddItem(result, name);
    result->ref_count++;  
  } 
  return result;
}

// функция загрузки bmp 1/2/4/8/16/24/32 бита или png или jpeg = с любым размером _pcx16_ © Berserker
_Pcx16_* LoadPcx16_ERA(char* pathTo_File, int width, int height){
  if (!pathTo_File) return NULL;

    void* f = NULL;
    _Pcx16_* result = NULL;
    char* name = GetShortFileName_Y(pathTo_File);
    HMODULE o_ERA = LoadLibraryA("era.dll");
    if (o_ERA){
      f = GetProcAddress(o_ERA, "LoadImageAsPcx16"); 
      result = CALL_4 (_Pcx16_*, __stdcall, f, pathTo_File, name, width, height); // LoadImageAsPcx16(путь, имя(можно пустое), ширина, высота)
      FreeLibrary(o_ERA);
      //_endthread(); 
    }
    return result;
}


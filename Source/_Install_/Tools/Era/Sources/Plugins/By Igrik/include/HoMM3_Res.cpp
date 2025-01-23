// /////////////////////////////////////////////////////////////////////////////////
// (HD 3.0) HoMM3 Resources (PCXes, DEFs, Palettes, Fonts, TXTes)
// Author: Alexander Barinov (aka baratorch, aka Bara) e-mail: baratorch@yandex.ru
// Thanks: ZVS, GrayFace
////////////////////////////////////////////////////////////////////////////////////


#include"HoMM3_Res.h"

#ifdef UNICODE
 #undef UNICODE
#endif

#define WIN32_LEAN_AND_MEAN 
#define BIT_MODE *(_byte_*)0x5FA22B

#include <windows.h>
#include <string.h>




// Загрузка звука по имени.
_Wav_* __fastcall LoadWav(_cstr_ Name)
{
  return CALL_1(_Wav_*, __fastcall, 0x55C930, Name);
}



//_Def_* _Def_::LoadFromFile(char filename)
//{
//
//}


_int_ _Fnt_::GetLineWidth(char* text)
{
 int r = 0;
 int len = strlen(text);
 for (int i = 0; i < len; i++)
 {
  if ((text[i] != '{') && (text[i] != '}'))
  {
   r += char_sizes[text[i]].left;
   r += char_sizes[text[i]].width;
   r += char_sizes[text[i]].right;
  }
 }
 return r;
}

_Pcx16_* _Pcx16_::CreateNew(char* n, int w, int h)
{
if ((w <= 0) || (h <= 0))
  return NULL;

_Pcx16_ *pcx16 = (_Pcx16_ *)o_New(56);
if (pcx16 == NULL) return NULL;

pcx16->v_table = (_ptr_*)0x63B9C8;
pcx16->ref_count = 0;
MemCopy(pcx16->name, n, 12);
pcx16->width = w;
pcx16->height = h;

if (BIT_MODE * 8 == 32)
     pcx16->scanline_size = ((((w * 32) + 31) & ~31) >> 3);
else
    pcx16->scanline_size = ((((w * 16) + 31) & ~31) >> 3);

pcx16->buf_size = pcx16->pic_size = pcx16->scanline_size*h;
pcx16->have_ddsurface_buffer = 0;
pcx16->buffer = o_New(pcx16->buf_size);
if (pcx16->buffer == NULL)
{
  o_Delete((_ptr_)pcx16);
  return NULL;
}

return pcx16;
}

void _Pcx16_::Delete(_Pcx16_* p)
{
 if (!p->have_ddsurface_buffer)
  o_Delete(p->buffer);
 o_Delete((_ptr_)p);
}
_Pcx16_* _Pcx16_::CreateFromBMP(char* name, char* filename)
{
 DWORD fr;
 HANDLE hFile = INVALID_HANDLE_VALUE;
 BITMAPFILEHEADER bfh;
 BITMAPINFO bmi;
 _Pcx16_* pcx;

 hFile = CreateFile(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
 if (hFile == INVALID_HANDLE_VALUE) return NULL;

 if (ReadFile(hFile, &bfh, sizeof(BITMAPFILEHEADER), &fr, NULL))
  if (bfh.bfType == 0x4d42)
   if (ReadFile(hFile, &bmi, sizeof(BITMAPINFO),&fr,NULL))
   {
    if (bmi.bmiHeader.biCompression == BI_RGB)
    {
     if (bmi.bmiHeader.biBitCount == 24)
     {
      pcx = CreateNew(name, bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight);
      if (pcx == NULL)
      {
       CloseHandle(hFile);
       return NULL;
      }
      SetFilePointer(hFile, bfh.bfOffBits, NULL, FILE_BEGIN);
      int scanline24 = ((((pcx->width * 24) + 31) & ~31) >> 3);
      BYTE* p_bits24 = (BYTE*)o_New(scanline24 * pcx->height);
      if (p_bits24 == NULL)
      {
       CloseHandle(hFile);
       Delete(pcx);
       return NULL;
      }
      if (!ReadFile(hFile, p_bits24, scanline24*pcx->height ,&fr, NULL))
      {
       o_Delete(p_bits24);
       CloseHandle(hFile);
       Delete(pcx);
       return NULL;
      }
      int r, g, b;
      _word_* pcx16_pixel = (_word_*)(pcx->buffer);
      BYTE* pcx24_pixel = (BYTE*)p_bits24;
      int x, y;
      y = 0;
      while (y < pcx->height)
      {
       x = 0;
       while(x < pcx->width)
       {
        r = ((int)(pcx24_pixel[(pcx->height - y - 1)*scanline24 + x*3 + 2]));
        g = ((int)(pcx24_pixel[(pcx->height - y - 1)*scanline24 + x*3 + 1]));
        b = ((int)(pcx24_pixel[(pcx->height - y - 1)*scanline24 + x*3 + 0]));
        pcx16_pixel[y * pcx->width + x] = RGB565_fromR8G8B8(r,g,b);

        x++;
       }
       y++;
      }
      o_Delete(p_bits24);
      CloseHandle(hFile);
      return pcx;
     }
    }
   }
 CloseHandle(hFile);
 return NULL;
}

void _Pcx16_::DrawPcx16(_Pcx16_ *src_pcx, int dst_x, int dst_y, int src_w, int src_h)
{
         int src_x = max(0, -dst_x);
            int src_y = max(0, -dst_y);
            dst_x = max(0, dst_x);
            dst_y = max(0, dst_y);
            src_w = min(width - dst_x, src_w - src_x);
            src_h = min(height - dst_y, src_h - src_y);
   _word_* src_pixel_bits = (_word_*)(src_pcx->buffer);
   _word_* dst_pixel_bits = (_word_*)buffer;

            for (int y = 0; y < src_h; y++)
                for (int x = 0; x < src_w; x++)
                        dst_pixel_bits[dst_x + x + (dst_y + y) * (scanline_size >> 1)] = src_pixel_bits[src_x + x + (src_y + y) * (src_pcx->scanline_size >> 1)];
}

void _Pcx16_::DrawPcx16(_Pcx16_ *src_pcx, int dst_x, int dst_y)
{
         int src_x = max(0, -dst_x);
            int src_y = max(0, -dst_y);
            dst_x = max(0, dst_x);
            dst_y = max(0, dst_y);
            int src_w = min(width - dst_x, src_pcx->width - src_x);
            int src_h = min(height - dst_y, src_pcx->height - src_y);
   _word_* src_pixel_bits = (_word_*)(src_pcx->buffer);
   _word_* dst_pixel_bits = (_word_*)buffer;

            for (int y = 0; y < src_h; y++)
                for (int x = 0; x < src_w; x++)
                        dst_pixel_bits[dst_x + x + (dst_y + y) * (scanline_size >> 1)] = src_pixel_bits[src_x + x + (src_y + y) * (src_pcx->scanline_size >> 1)];
}

void _Pcx16_::DrawPcx16(_Pcx16_* src_pcx, int src_x, int src_y, int src_w, int src_h, int dst_x, int dst_y)
{
         src_x = max(src_x, -dst_x);
            src_y = max(src_y, -dst_y);
            dst_x = max(0, dst_x);
            dst_y = max(0, dst_y);
   src_w = min(src_w, min(width - dst_x, src_pcx->width - src_x));
   src_h = min(src_h, min(height - dst_y, src_pcx->height - src_y));
   _word_* src_pixel_bits = (_word_*)(src_pcx->buffer);
   _word_* dst_pixel_bits = (_word_*)buffer;

            for (int y = 0; y < src_h; y++)
                for (int x = 0; x < src_w; x++)
                        dst_pixel_bits[dst_x + x + (dst_y + y) * (scanline_size >> 1)] = src_pixel_bits[src_x + x + (src_y + y) * (src_pcx->scanline_size >> 1)];
}

void _Pcx16_::DrawPcx16Resized(_Pcx16_ *src_pcx, int s_w, int s_h, int d_x, int d_y, int d_w, int d_h)
{
    d_x = max(0, d_x);
    d_y = max(0, d_y);
    int src_w = min(s_w, src_pcx->width);
    int src_h = min(s_h, src_pcx->height);
 _word_* src_bits0 = (_word_*)(src_pcx->buffer);
 _word_* dst_bits0 = (_word_*)buffer;
 int src_scan = src_pcx->scanline_size >> 1;
 int dst_scan = scanline_size >> 1;

 int src_x;
 int src_y;
 int dst_y;
 int dst_x;

 for (dst_y = 0; dst_y < d_h; dst_y++)
  for (dst_x = 0; dst_x < d_w; dst_x++)
  {
   src_x = dst_x * src_w / d_w;
   src_y = dst_y * src_h / d_h;
   dst_bits0[d_x+dst_x+dst_scan*(d_y+dst_y)] = src_bits0[src_x+src_scan*src_y];
  }
}

void _Pcx16_::DrawPcx8(_Pcx8_* src_pcx, int src_x, int src_y, int src_w, int src_h, int dst_x, int dst_y)
{
         src_x = max(src_x, -dst_x);
            src_y = max(src_y, -dst_y);
            dst_x = max(0, dst_x);
            dst_y = max(0, dst_y);
            src_w = min(width - dst_x, src_w - src_x);
            src_h = min(height - dst_y, src_h - src_y);
   _byte_* src_pixel_bits = (_byte_*)(src_pcx->buffer);
   _word_* dst_pixel_bits = (_word_*)buffer;
   _byte_ src_i;

            for (int y = 0; y < src_h; y++)
                for (int x = 0; x < src_w; x++)
    {
     src_i = src_pixel_bits[src_x + x + (src_y + y) * src_pcx->scanline_size];
     if (src_i == 0) continue;
     dst_pixel_bits[dst_x + x + (dst_y + y) * (scanline_size >> 1)] = src_pcx->palette16.colors[src_i];
    }
}

void _Pcx16_::FillRect(_word_ color, int x, int y, int w, int h)
{
    if ((x < 0) || (y < 0) || ((x + w) > width) || ((y + h) > height))
        return;

 _ptr_ p_pixel = buffer + x*2 + y * scanline_size;
 int s = scanline_size - w * 2;

 for (int y_ = 0; y_ < h; y_++)
 {
  for (int x_ = 0; x_ < w; x_++)
  {
   *(_word_*)p_pixel = color;
   p_pixel += 2;
  }
  p_pixel += s;
 }
  
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void _Pcx8_::Delete(_Pcx8_* pcx8)
{
 o_Delete(pcx8->buffer);
 o_Delete((_ptr_)pcx8);
}

_Pcx8_* _Pcx8_::CreateNew(char* n, int w, int h)
{
 _Pcx8_ *pcx;

 if ((w <= 0) || (h <= 0))
  return NULL;

 pcx = (_Pcx8_ *)o_New(1388);
 if (pcx == NULL) return NULL;
 MemZero(pcx, 1388);

 pcx->v_table = (_ptr_*)0x63BA14;

 pcx->ref_count = 0;
 MemCopy(pcx->name, n, 12);
 pcx->width = w;
 pcx->height = h;
 pcx->scanline_size = ((((w * 8) + 31) & ~31) / 8);
 pcx->buf_size = pcx->pic_size = pcx->scanline_size * h;
 pcx->buffer = o_New(pcx->buf_size);
 if (pcx->buffer == NULL)
 {
  o_Delete(pcx);
  return NULL;
 }
 pcx->palette16.v_table = (_ptr_*)0x640378;
 pcx->palette16.name[0] = 0;
 pcx->palette16.ref_count = -1;

 pcx->palette24.v_table = (_ptr_*)0x640384;
 pcx->palette24.name[0] = 0;
 pcx->palette24.ref_count = -1;
 
 return pcx;
}

_Pcx8_* _Pcx8_::CreateFromBMP(char* name, char* filename)
{
 DWORD fr;
 HANDLE hFile = INVALID_HANDLE_VALUE;
 BITMAPFILEHEADER bfh;
 BITMAPINFO bmi;
 RGBQUAD palette32[256];
 _Pcx8_* pcx;

 hFile = CreateFile((LPTSTR)filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
 if (hFile == INVALID_HANDLE_VALUE) return NULL;

 if (ReadFile(hFile, &bfh, sizeof(BITMAPFILEHEADER), &fr, NULL))
  if (bfh.bfType == 0x4d42)
   if (ReadFile(hFile, &bmi, sizeof(BITMAPINFO),&fr,NULL))
   {
    if (bmi.bmiHeader.biCompression == BI_RGB)
    {
     if (bmi.bmiHeader.biBitCount == 8)
     {
      pcx = CreateNew(name, bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight);
      if (pcx == NULL)
      {
       CloseHandle(hFile);
       return NULL;
      }

      SetFilePointer(hFile, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER), NULL, FILE_BEGIN);
      if (!ReadFile(hFile, (LPVOID)palette32, 256*4 ,&fr, NULL))
      {
       CloseHandle(hFile);
       Delete(pcx);
       return NULL;
      }

      for (int i = 0; i < 256; i++)
      {
       pcx->palette24.colors[i].r = palette32[i].rgbRed;
       pcx->palette24.colors[i].g = palette32[i].rgbGreen;
       pcx->palette24.colors[i].b = palette32[i].rgbBlue;

       pcx->palette16.colors[i] = RGB565_fromR8G8B8(palette32[i].rgbRed, 
        palette32[i].rgbGreen, 
        palette32[i].rgbBlue);
      }


      LPVOID p_scanline;
      for (int y = 0; y < pcx->height; y++)
      {
       SetFilePointer(hFile, bfh.bfOffBits + pcx->scanline_size * y, NULL, FILE_BEGIN);
       p_scanline = (LPVOID)(pcx->buffer + pcx->scanline_size * (pcx->height - y - 1));
       if (!ReadFile(hFile, p_scanline, pcx->scanline_size ,&fr, NULL))
       {
        CloseHandle(hFile);
        Delete(pcx);
        return NULL;
       }
      }
      CloseHandle(hFile);
      return pcx;
     }
    }
   }
 CloseHandle(hFile);
 return NULL;
}


void _Pcx8_::SetPaletteFrom(_Pcx8_ *pcx)
{
 MemCopy(this->palette16.colors, pcx->palette16.colors, 256 * sizeof(_word_));
 MemCopy(this->palette24.colors, pcx->palette24.colors, 256 * sizeof(_ColorRGB888_));
}

void _Pcx8_::DrawPcx8(_Pcx8_ *src_pcx, int dst_x, int dst_y)
{
   if ((dst_x >= width)||(dst_y >= height)) return;
         int src_x = max(0, -dst_x);
            int src_y = max(0, -dst_y);
            dst_x = max(0, dst_x);
            dst_y = max(0, dst_y);
            int src_w = min(width - dst_x, src_pcx->width - src_x);
            int src_h = min(height - dst_y, src_pcx->height - src_y);
   if ((src_w <= 0)||(src_h <= 0)) return;
   _byte_* src_pixel_bits = (_byte_*)(src_pcx->buffer);
   _byte_* dst_pixel_bits = (_byte_*)buffer;

            for (int y = 0; y < src_h; y++)
                for (int x = 0; x < src_w; x++)
                {
                    if (src_pixel_bits[src_x + x + (src_y + y) * src_pcx->scanline_size] != 0x00)
                        dst_pixel_bits[dst_x + x + (dst_y + y) * scanline_size] = src_pixel_bits[src_x + x + (src_y + y) * src_pcx->scanline_size];
                }

}

void _Pcx8_::DrawPcx8(_Pcx8_ *src_pcx, int dst_x, int dst_y, int src_w, int src_h)
{
         int src_x = max(0, -dst_x);
            int src_y = max(0, -dst_y);
            dst_x = max(0, dst_x);
            dst_y = max(0, dst_y);
            src_w = min(width - dst_x, src_w - src_x);
            src_h = min(height - dst_y, src_h - src_y);
   _byte_* src_pixel_bits = (_byte_*)(src_pcx->buffer);
   _byte_* dst_pixel_bits = (_byte_*)buffer;

            for (int y = 0; y < src_h; y++)
                for (int x = 0; x < src_w; x++)
                {
                    if (src_pixel_bits[src_x + x + (src_y + y) * src_pcx->scanline_size] != 0x00)
                        dst_pixel_bits[dst_x + x + (dst_y + y) * scanline_size] = src_pixel_bits[src_x + x + (src_y + y) * src_pcx->scanline_size];
                }

}


void _Pcx8_::Fill(_byte_ color_index)
{
 int size = scanline_size * height;
 _byte_* p_pixel = (_byte_*)buffer;
    for (int i = 0; i < size; i++)
  *(p_pixel++) = color_index;
}

void _Pcx8_::FillRect(_byte_ color_index, int x, int y, int w, int h)
{
    if ((x < 0) || (y < 0) || ((x + w) > width) || ((y + h) > height))
        return;

 _byte_* p_pixel = (_byte_*)buffer;

 for (int y_ = y + h - 1; y_ >= y; y_--)
        for (int x_ = x + w - 1; x_ >= x; x_--)
            p_pixel[x_ + y_ * scanline_size] = color_index;

}



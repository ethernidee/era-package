// /////////////////////////////////////////////////////////////////////////////////
// Some HD 3.0 and HotA base stuff
////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef UNICODE
 #undef UNICODE
#endif

#ifdef WIN32_LEAN_AND_MEAN 
 #undef WIN32_LEAN_AND_MEAN
#endif

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <string>
#include <new>
using std::string;

//typedef unsigned __int8  _byte_;
//typedef unsigned __int16 _word_;
//typedef unsigned __int32 _dword_;
//typedef signed __int8  _char_;
//typedef signed __int8  _int8_;
//typedef signed __int16  _int16_;
//typedef signed __int32  _int_;
//typedef _dword_    _ptr_;
//typedef float    _float_;
//typedef _int_    _bool_;

// ����� ����������� ����.
#define _byte_ unsigned __int8
// ����� ����������� �����.
#define _word_ unsigned __int16
// ����� ����������� ������� �����.
#define _dword_ unsigned __int32
// ����� ����������� ����������� �����.
#define _qword_ unsigned __int64

// ������.
#define _char_ char

// ����� �������� ����.
#define _int8_ signed __int8
// ����� �������� �����.
#define _int16_ signed __int16
// ����� �������� ������� �����.
#define _int32_ signed __int32
// ����� �������� ����������� �����.
#define _int64_ signed __int64

// ������������ ������� �����.
#define _float_ float

// ���������� ����.
#define _bool8_ _char_
// ���������� ������� �����.
#define _bool32_ _int32_

// ���������� (������� �����).
#define _bool_ _bool32_

// ����� (�������� ������� �����).
#define _int_ _int32_
#define INT_MAX 2147483647

// ��������� (C-�����).
#define _cstr_ _char_*

// ��������� (����������� ������� �����).
//#define _ptr_ _dword_
typedef _dword_ _ptr_;


#define LODWORD(x)  (*((_dword_*)&(x)))
#define HIDWORD(x)  (*((_dword_*)&(x)+1))

// ���� ��������� ������
// char h3Text[1024];
// #define H3Text  (char*)h3Text

// ������ ������� �� �������.
// ������ 3 ���������:
// ��� ������������� ��������, ���������� ������ � ��������� �� ������� (� ����� ����, ���� ������������� �������������).

// ��� ����������.
#define CALL_0(return_type, call_type, address) \
 ((return_type (call_type *)(void))address)()

// � 1 ����������.
#define CALL_1(return_type, call_type, address, a1) \
 ((return_type (call_type *)(_dword_))(address))((_dword_)(a1))

// � 2 �����������.
#define CALL_2(return_type, call_type, address, a1, a2) \
 ((return_type (call_type *)(_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2))

// � 3 �����������.
#define CALL_3(return_type, call_type, address, a1, a2, a3) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3))

// � 4 �����������.
#define CALL_4(return_type, call_type, address, a1, a2, a3, a4) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4))

// � 5 �����������.
#define CALL_5(return_type, call_type, address, a1, a2, a3, a4, a5) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5))

// � 6 �����������.
#define CALL_6(return_type, call_type, address, a1, a2, a3, a4, a5, a6) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6))

// � 7 �����������.
#define CALL_7(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7))

// � 8 �����������.
#define CALL_8(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8))

// � 9 �����������.
#define CALL_9(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9))

// � 10 �����������.
#define CALL_10(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10))

// � 11 �����������.
#define CALL_11(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11))

// � 12 �����������.
#define CALL_12(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12))

// � 13 �����������.
#define CALL_13(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13))

// � 14 �����������.
#define CALL_14(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14))

// � 15 �����������.
#define CALL_15(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14),(_dword_)(a15))

// � 16 �����������.
#define CALL_16(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14),(_dword_)(a15),(_dword_)(a16))

// � 17 �����������.
#define CALL_17(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14),(_dword_)(a15),(_dword_)(a16),(_dword_)(a17))

// __cdecl � ���������� ����������� ����������.
#define CALL_VA(return_type, adress, a1, ...) \
 ((return_type (__cdecl *)(_dword_, ...))(adress))((_dword_)(a1), __VA_ARGS__)

// ����������� � ���������� ��������� this ������� __thiscall (��������� ��������������� ����� �������).
#define SET_THIS(this_var) {__asm mov this_var, ecx}

// ��� ������������ - ��� ������������.
#define NOALIGN __declspec(align(1))

// �������� ���������� ���������.
#define BREAKPOINT __asm{__asm int 3}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ��������� ����������� ����������, ���� �� ���.

// ������ ���������.
#ifndef NULL
 #define NULL 0
#endif
// ������.
#ifndef TRUE
 #define TRUE 1
#endif
// ����.
#ifndef FALSE
 #define FALSE 0
#endif
// �������� �� ���� ��������.
#ifndef max
 #define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif
// ������� �� ���� ��������.
#ifndef min
 #define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

// ������.
#define Abs(value) ( ((value) > 0) ? (value) : -(value) )

// �������������� ����������.
#define Round(value) ((_int_)((double)(value) + 0.5))
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ����������� ������ � �������������� ����������� �����.
#define MemCopy(dst, src, size) memcpy((void*)(dst), (void*)(src), (size_t)(size))
// ���������� ������ � �������������� ����������� �����.
#define MemSet(ptr, value, size) memset((void*)(ptr), (char)(value), (size_t)(size))
// ��������� ������ � �������������� ����������� �����.
#define MemZero(ptr, size) MemSet(ptr, 0, size)

// ��������� ������ � ��������������� � ������������ ����������� ����.
#define MemAlloc(size) ((_ptr_)malloc((size_t)(size)))
// ������������� ������ � ��������������� ����.
#define MemFree(ptr) free((void*)(ptr))
// ������������� ������ � ��������������� � ������������ ����������� ����.
#define MemRealloc(ptr, size) ((_ptr_)realloc((void*)(ptr), (size_t)(size)))

// ��������� ������� ���������� ������ � ��������������� �����.
#define MemGetSize(ptr) ((_dword_)_msize((void*)(ptr)))

// �������� ������� ����� �� ������.
#define IntAt(address) (*(_int_*)(address))
// ������� ����� �� ������.
#define DwordAt(address) (*(_dword_*)(address))
// ���� �� ������.
#define ByteAt(address) (*(_byte_*)(address))
// ����� �� ������.
#define WordAt(address) (*(_word_*)(address))
// C-������ �� ������.
#define CStrAt(address) (*(_cstr_*)(address))
// ��������� �� ������.
#define PtrAt(address) (*(_ptr_*)(address))

// ���������� ������������ ������� ����� �� ������.
#define SetFloatAt(address, value) (*(_float_*)(address) = (_float_)(value))
// ���������� ������� ����� �� ������.
#define SetDwordAt(address, value) (*(_dword_*)(address) = (_dword_)(value))
// ���������� ����� �� ������.
#define SetWordAt(address, value) (*(_word_*)(address) = (_word_)(value))
// ���������� ���� �� ������.
#define SetByteAt(address, value) (*(_byte_*)(address) = (_byte_)(value))
// ���������� ������.
#define SetJmpAt(address, to_address) do{*(_byte_*)(address) = 0xE9; *(_int_*)(address + 1) = (_int_)(to_address) -  (_int_)(address) - 5; break;}while(true)

// ������ �� ��������� �������.
_bool_ IsKeyPressed(int nVirtKey);

// ��������� ����� ����� �� ���� � ����.
char* GetShortFileName(char* filename);
// �������� ������������ ����� �����.
_bool_ IsFileNameValid(char* name);

// �������� ������������� ����� �� �����.
//inline _bool_ FileExists(char* filename)
//{
//  return (GetFileAttributes(filename) != INVALID_FILE_ATTRIBUTES)
//}
#define FileExists(file_name) (GetFileAttributes((char*)(file_name)) != INVALID_FILE_ATTRIBUTES)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ���� ������, �� ������� �� ������� �������� ���� ����� ������������� ����������� ������ ������ ��� �������.
#define MIN_ARRAY_MEMBLOCK_SIZE 64

// ���� ��������� ������� ����������/������ - ������������ ������ ������.
#define soFromBeginning FILE_BEGIN
// ���� ��������� ������� ����������/������ - ������������ ������� �������.
#define soFromCurrent FILE_CURRENT
// ���� ��������� ������� ����������/������ - ������������ ����� ������.
#define soFromEnd  FILE_END

// ������� ��������� ������.
class TStream
{
public:
 // ����������.
 virtual void Free() = 0;
 // ������ �� ������ (������� ���������� ������).
 virtual _bool_ Read(void* dst, _dword_ size) = 0;
 // ������ � �����, ������� ���������� ������.
 virtual _bool_ Write(void* src, _dword_ size) = 0;
 // ��������� ������� ����������/������ � ������.
 virtual _int_ Seek(_int_ offset, _int_ origin) = 0;
 // �������� ������ ������ ������.
 virtual _int_ Size() = 0;
 
 // ������-������� ������ �������� ������ ���� ������ �� ������.
 template<typename DataType> _bool_ Read(const DataType& value)
 {
  return Read((void*)&value, sizeof(DataType));
 }
 // ������-������� ������ �������� ������ ���� ������ � �����.
 template<typename DataType> _bool_ Write(const DataType& value)
 {
  return Write((void*)&value, sizeof(DataType));
 }
};


// ����� � ������.
class TMemoryStream : public TStream
{
public:
 // ���������� ������ � ������.
 virtual void Free();
 // ������ �� ������ � ������ (������� ���������� ������).
 virtual _bool_ Read(void* dst, _dword_ size);
 // ������ � ����� � ������ � �������������� ����������� ��� ������ (�������), ������� ���������� ������.
 virtual _bool_ Write(void* src, _dword_ size);
 // ��������� ������� ����������/������ � ������ (������� -1 ��� �������� ��������� - ��������).
 virtual _int_ Seek(_int_ offset, _int_ origin);
 // �������� ������ ������ ������ � ������.
 virtual _int_ Size();

 // ��������� �� ������ ������.
 _ptr_ memory;
 // ������� ������� ������/���������� ������.
 _int_ position;
 // ������ ������ ������.
 _int_ size;
 // ����������� ������� ������ � ������.
 static TMemoryStream* Create();
 // ����������� ������ � ������.
 static TMemoryStream* Create(_dword_ size);
 // �������� ������� ���������� ������� ������.
 void SetSize(_dword_ size);
 // �������� ��������� �� ������ ������.
 void* Memory()
 {
  return (void*)this->memory;
 }
};


// ���� ������������ ��������� ������ - ������� ����.
#define fmCreate   0xFFFF
// ���� ������������ ��������� ������ - ������� ���� ��� ������.
#define fmOpenRead       0x0000
// ���� ������������ ��������� ������ - ������� ���� ��� ������.
#define fmOpenWrite      0x0001
// ���� ������������ ��������� ������ - ������� ���� ��� ������ � ������.
#define fmOpenReadWrite  0x0002


// �������� �����.
class TFileStream : public TStream
{
protected:
 // ���� ��� ������/������ ������.
 HANDLE h_file;

public:
 // ���������� ��������� ������.
 virtual void Free();
 // ������ �� ��������� ������ (������� ���������� ������).
 virtual _bool_ Read(void* dst, _dword_ size);
 // ������ � �������� ����� (������� ���������� ������).
 virtual _bool_ Write(void* src, _dword_ size);
 // ����������� ������� ����������/������ � �������� ������.
 virtual _int_ Seek(_int_ offset, _int_ origin);
 //  ��������� ������� ��������� ������.
 virtual _int_ Size();

 // ����������� ��������� ������.
 static TFileStream* Create(_cstr_ file_name, _word_ mode);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// ������������ ����� ������ ��������� ��� ����������� ���������� �������.
#define MAX_MSGVA_LENGTH 256

// ����� ���������.
#define ShowMessage(msg) MessageBoxA(NULL, (LPCSTR)(msg), (LPCSTR)"", MB_OK)

// ����� ��������� � ������������ �������.
inline void ShowVA(const char *pFormat, ... )
{
 // ������ ����������.
 va_list Args;
 va_start(Args, pFormat);
 // ������������� ������.
 char Buffer[MAX_MSGVA_LENGTH];
 // ���������� ������������� ������ � �����������.
 vsprintf(Buffer, pFormat, Args);
 va_end(Args);
 // ������� ���������.
 ShowMessage(Buffer);
}


// �������������� ������ � �������� 32-������ �����.
inline _int_ StrToInt(_cstr_ str)
{
 //int n = 0;
 //char* digits =  "0123456789";
 //BOOL char_is_not_digit = TRUE;

 //for (int i = 0; i < strlen(str); i++)
 //{
 // for (int d = 0; d < 10; d++)
 // {
 //  if (str[i] == digits[d])
 //  {
 //   n = n * 10 + d;
 //   char_is_not_digit = FALSE;
 //   break;
 //  }
 // }
 // if (char_is_not_digit) break;
 //}
 //return n;
 // �����.
 _int_ result;
 sscanf(str, "%d", &result);
 return result;
}

// �������� �� ��������� ������ ������ �������� �� ������.
inline _bool_ IsDelimiter(_cstr_ Delimiters, _cstr_ S, _int_ Index)
{
 // �������� �� ���� �������� �� ������.
 for (int i = strlen(Delimiters); i >= 0; i--)
 {
  if (Delimiters[i] == S[Index])
   return TRUE;
 }
 return FALSE;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ������ ������������� ������� ��� ������ ���� ���������.
template <typename ElementType> class TArray
{
public:
 // ������.
 ElementType* data;
 // ���������� ��������� �������.
 int length;
 // ������ ���������� �������� ������.
 int data_size;

 // �����������.
 TArray()
 {
  this->data = NULL;
  this->length = 0;
  this->data_size = 0;
 }

 //  ����������.
 ~TArray()
 {
  // ����������� ������� �������� ������.
  MemFree(this->data);
 }

 // ��������� ���������� ��������� �������.
 _int_ Length()
 {
  return this->length;
 }

 // ��������� ���������� ��������� �������.
 void SetLength(_int_ new_len)
 {
  // ���� ����� ������� �� ����� 0...
  if (new_len) 
  {
   // ����������� ������, �����������, ����� �������� new_len ���������.
   int need_min_size = new_len * sizeof(ElementType);
   // ������������ ������, ������ MIN_ARRAY_MEMBLOCK_SIZE.
   int new_size = ( need_min_size / MIN_ARRAY_MEMBLOCK_SIZE + ((need_min_size % MIN_ARRAY_MEMBLOCK_SIZE) != 0) ) * MIN_ARRAY_MEMBLOCK_SIZE;
   if (new_size != this->data_size)
   {
    // �������� ����� ������ � �������� ���� ������.
    //this->data = (ElementType*)MemRealloc(this->data, new_size);
    ElementType* new_data = (ElementType*)MemAlloc(new_size);
    MemCopy(new_data, data, min(data_size, new_size));
    MemFree(data);
    data = new_data;

    // ��������� ������������� ���������� ������ ������.
    if (new_size > this->data_size)
     MemZero((_ptr_)this->data + this->data_size, new_size - this->data_size);
    this->data_size = new_size;
   }
   // ������������� ����� �����.
   this->length = new_len;
  }
  // ���� ����� ����� ����� 0, ����������� ������ �������.
  else
  {
   MemFree(this->data);
   this->data = NULL;
   this->data_size = 0;
   this->length = 0;
  }
 }

 // ������ �������� �� �������.
 ElementType& operator[](int index)
 {
  // ������ ������������� ��������� �� ������� ���������.
  index = min(length - 1, max(0, index)); // if < 0 then =0, if > last then =last 
  return data[index];
 }

 // ���������� ������ �������� � ����� �������.
 void Add(const ElementType& value)
 {
  // ����������� ������ �������.
  SetLength(this->length + 1);
  // �������� ����� ������� � �����.
  MemCopy(&(this->data[this->length - 1]), &value, sizeof(ElementType)); 
 }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ������ � ������ (����������� �� ������������� ������� ��������).
class TString: public TArray<_char_>
{
protected:
 // ������, �������� ��������� ��������.
 static TString op_result;

public:
 // �����������.
 TString(const _cstr_ cstr);
 // ������ ������.
 TString();
 // ����������.
 //~TString();

 // �������������� ������ � C-�����.
 _char_* c_str()
 {
  return this->data;
 }

 // ��������� ����� ������.
 void SetLength(int new_len);
 // ���������� ������� � ������.
 void Add(const _char_ &chr);
 
 // ������������� � ������ � ������.
 TString& operator=(TString& r_str);
 // ������������� � C-������.
 TString& operator=(const _cstr_ r_str);
 // ������������� � �������.
 TString& operator=(_char_ r_chr);
 
 // ���������� ������ � ������.
 TString& operator+=(TString& r_str);
 // ���������� C-������.
 TString& operator+=(const _cstr_ r_str);
 // ���������� �������.
 TString& operator+=(_char_ r_chr);

 // �������� �� ������� � ������..
 friend TString& operator+(TString &l_tstr, TString &r_tstr);
 // �������� � C-�������.
 friend TString& operator+(TString &l_tstr, _cstr_ r_cstr);
 // ������ �������� � C-�������.
 friend TString& operator+(_cstr_ l_cstr, TString &r_tstr);
 // �������� � ��������.
 friend TString& operator+(TString &l_tstr, _char_ r_chr);
 // ������ �������� � ��������.
 friend TString& operator+(_char_ l_chr, TString &r_tstr);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



NOALIGN struct _Struct_
{
    template <typename _type_>
    inline _type_ & Field(int offset) {return *(_type_*)((_ptr_)this + offset);}
    
    template <typename _type_>
    inline _type_ * PField(int offset) {return (_type_*)((_ptr_)this + offset);}
    
    inline _ptr_    Offset(int offset)    {return ((_ptr_)this + offset);}
};



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// �������� �������.
template<typename _type_> void MakeArray(_type_** array_off, _int_ count)
{
  // ���� ������ ��� ��������, ����������� ���.
  if (*array_off)
  {
    // ��������������� �������.
    for (_int_ i = 0; i < count; i++)
    {
      ((*array_off)[i]).~_type_();
    }
    
    MemFree(*array_off);
  }
  
  // �������� ������ ��� ����� ������.
  if (count)
  {
    *array_off = (_type_*)MemAlloc(sizeof(_type_)*count);
    
    // �������������� �������.
    for (_int_ i = 0; i < count; i++)
    {
      new(&((*array_off)[i])) _type_();
    }
  
  }
  else
  {
    *array_off = NULL;
  }
}


struct _BitField_
{
	_dword_ bf;

	// * returns whether bit at position is set or not
	// * position can exceed the scope of bitfield, meaning greater than 32 bits
	bool GetState(_int_ position)
	{
		_int_ index = position >> 5;
		_int_ pos = position & 0x1F;
		_int_ value = 1 << pos;
		return ((&bf)[index]) & value;
	}
	// * sets bit at position to one or off
	// * position can exceed the scope of bitfield, meaning greater than 32 bits
	void SetState(_int_ position, bool state)
	{
		_int_ index = position >> 5;
		_int_ pos = position & 0x1F;
		_int_ value = 1 << pos;
		if (state)
			((&bf)[index]) |= value;
		else
			((&bf)[index]) &= ~value;
	}
};



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/* #include "..\patcher_x86_commented.hpp"
extern Patcher* _P;
extern PatcherInstance* _PI;

// ��������� ���������� HD.
extern FARPROC HdCommon_Get;
#define HDC_Get(name, default_value) HdCommon_Get?CALL_2(_dword_,__stdcall,HdCommon_Get,name,default_value):default_value

// ��������� ���������� HD.
extern FARPROC HdCommon_Set;
#define HDC_Set(name, value) HdCommon_Set?CALL_2(_bool_,__stdcall,HdCommon_Set,name,value):FALSE */



#define strempty(string) do{string[0] = 0;}while(false)



#define va_cstr(pFormat, ...) Base::va_cstr(pFormat, __VA_ARGS__)

#define _L(ru, en) (Base::SystemLanguageIsRussian() ? (ru) : (en))


#define _LW(ru, en) (Base::SystemLanguageIsRussian()  ? (L##ru) : (L##en))
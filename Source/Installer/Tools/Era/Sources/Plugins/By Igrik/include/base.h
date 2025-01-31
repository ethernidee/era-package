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

// Целый беззнаковый байт.
#define _byte_ unsigned __int8
// Целое беззнаковое слово.
#define _word_ unsigned __int16
// Целое беззнаковое двойное слово.
#define _dword_ unsigned __int32
// Целое беззнаковое учетверённое слово.
#define _qword_ unsigned __int64

// Символ.
#define _char_ char

// Целый знаковый байт.
#define _int8_ signed __int8
// Целое знаковое слово.
#define _int16_ signed __int16
// Целое знаковое двойное слово.
#define _int32_ signed __int32
// Целое знаковое учетверённое слово.
#define _int64_ signed __int64

// Вещественное двойное слово.
#define _float_ float

// Логический байт.
#define _bool8_ _char_
// Логическое двойное слово.
#define _bool32_ _int32_

// Логический (двойное слово).
#define _bool_ _bool32_

// Целый (знаковое двойное слово).
#define _int_ _int32_
#define INT_MAX 2147483647

// Строковый (C-стиль).
#define _cstr_ _char_*

// Указатель (беззнаковое двойное слово).
//#define _ptr_ _dword_
typedef _dword_ _ptr_;


#define LODWORD(x)  (*((_dword_*)&(x)))
#define HIDWORD(x)  (*((_dword_*)&(x)+1))

// Свой текстовый буффер
// char h3Text[1024];
// #define H3Text  (char*)h3Text

// Вызовы функций по адресам.
// Первые 3 параметра:
// Тип возвращаемого значения, соглашение вызова и указатель на функцию (в любом типе, явно преобразуется автоматически).

// Без аргументов.
#define CALL_0(return_type, call_type, address) \
 ((return_type (call_type *)(void))address)()

// С 1 аргументом.
#define CALL_1(return_type, call_type, address, a1) \
 ((return_type (call_type *)(_dword_))(address))((_dword_)(a1))

// С 2 аргументами.
#define CALL_2(return_type, call_type, address, a1, a2) \
 ((return_type (call_type *)(_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2))

// С 3 аргументами.
#define CALL_3(return_type, call_type, address, a1, a2, a3) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3))

// С 4 аргументами.
#define CALL_4(return_type, call_type, address, a1, a2, a3, a4) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4))

// С 5 аргументами.
#define CALL_5(return_type, call_type, address, a1, a2, a3, a4, a5) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5))

// С 6 аргументами.
#define CALL_6(return_type, call_type, address, a1, a2, a3, a4, a5, a6) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6))

// С 7 аргументами.
#define CALL_7(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7))

// С 8 аргументами.
#define CALL_8(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8))

// С 9 аргументами.
#define CALL_9(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9))

// С 10 аргументами.
#define CALL_10(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10))

// С 11 аргументами.
#define CALL_11(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11))

// С 12 аргументами.
#define CALL_12(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12))

// С 13 аргументами.
#define CALL_13(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13))

// С 14 аргументами.
#define CALL_14(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14))

// С 15 аргументами.
#define CALL_15(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14),(_dword_)(a15))

// С 16 аргументами.
#define CALL_16(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14),(_dword_)(a15),(_dword_)(a16))

// С 17 аргументами.
#define CALL_17(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14),(_dword_)(a15),(_dword_)(a16),(_dword_)(a17))

// __cdecl с переменным количеством аргументов.
#define CALL_VA(return_type, adress, a1, ...) \
 ((return_type (__cdecl *)(_dword_, ...))(adress))((_dword_)(a1), __VA_ARGS__)

// Перемещение в переменную параметра this функции __thiscall (выполнять непосредственно перед вызовом).
#define SET_THIS(this_var) {__asm mov this_var, ecx}

// Тип выравнивания - без выравнивания.
#define NOALIGN __declspec(align(1))

// Передача управления отладчику.
#define BREAKPOINT __asm{__asm int 3}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Объявляем стандартные объявления, если их нет.

// Пустая константа.
#ifndef NULL
 #define NULL 0
#endif
// Истина.
#ifndef TRUE
 #define TRUE 1
#endif
// Ложь.
#ifndef FALSE
 #define FALSE 0
#endif
// Максимум из двух значений.
#ifndef max
 #define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif
// Минимум ищ двух значений.
#ifndef min
 #define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

// Модуль.
#define Abs(value) ( ((value) > 0) ? (value) : -(value) )

// Математическое округление.
#define Round(value) ((_int_)((double)(value) + 0.5))
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Копирование памяти с автоматическим приведением типов.
#define MemCopy(dst, src, size) memcpy((void*)(dst), (void*)(src), (size_t)(size))
// Заполнение памяти с автоматическим приведением типов.
#define MemSet(ptr, value, size) memset((void*)(ptr), (char)(value), (size_t)(size))
// Обнуление памяти с автоматическим приведением типов.
#define MemZero(ptr, size) MemSet(ptr, 0, size)

// Выделение памяти с автоприведением и возвращением встроенного типа.
#define MemAlloc(size) ((_ptr_)malloc((size_t)(size)))
// Освобоождение памяти с автоприведением типа.
#define MemFree(ptr) free((void*)(ptr))
// Перевыделение памяти с автоприведением и возвращением встроенного типа.
#define MemRealloc(ptr, size) ((_ptr_)realloc((void*)(ptr), (size_t)(size)))

// Получение размера выделенной памяти с автоприведением типов.
#define MemGetSize(ptr) ((_dword_)_msize((void*)(ptr)))

// Знаковое двойное слово по адресу.
#define IntAt(address) (*(_int_*)(address))
// Двойное слово по адресу.
#define DwordAt(address) (*(_dword_*)(address))
// Байт по адресу.
#define ByteAt(address) (*(_byte_*)(address))
// Слово по адресу.
#define WordAt(address) (*(_word_*)(address))
// C-строка по адресу.
#define CStrAt(address) (*(_cstr_*)(address))
// Указатель по адресу.
#define PtrAt(address) (*(_ptr_*)(address))

// Установить вещественное двойное слово по адресу.
#define SetFloatAt(address, value) (*(_float_*)(address) = (_float_)(value))
// Установить двойное слово по адресу.
#define SetDwordAt(address, value) (*(_dword_*)(address) = (_dword_)(value))
// Установить слово по адресу.
#define SetWordAt(address, value) (*(_word_*)(address) = (_word_)(value))
// Установить байт по адресу.
#define SetByteAt(address, value) (*(_byte_*)(address) = (_byte_)(value))
// Установить прыжок.
#define SetJmpAt(address, to_address) do{*(_byte_*)(address) = 0xE9; *(_int_*)(address + 1) = (_int_)(to_address) -  (_int_)(address) - 5; break;}while(true)

// Нажата ли указанная клавиша.
_bool_ IsKeyPressed(int nVirtKey);

// Получение имени файла из пути к нему.
char* GetShortFileName(char* filename);
// Проверка допустимости имени файла.
_bool_ IsFileNameValid(char* name);

// Проверка существования файла по имени.
//inline _bool_ FileExists(char* filename)
//{
//  return (GetFileAttributes(filename) != INVALID_FILE_ATTRIBUTES)
//}
#define FileExists(file_name) (GetFileAttributes((char*)(file_name)) != INVALID_FILE_ATTRIBUTES)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Блок памяти, на кратный по размеру которому блок может автоматически расширяться память потока или массива.
#define MIN_ARRAY_MEMBLOCK_SIZE 64

// Флаг изменения позиции считывания/записи - относительно начала потока.
#define soFromBeginning FILE_BEGIN
// Флаг изменения позиции считывания/записи - относительно текущей позиции.
#define soFromCurrent FILE_CURRENT
// Флаг изменения позиции считывания/записи - относительно конца потока.
#define soFromEnd  FILE_END

// Базовый интерфейс потока.
class TStream
{
public:
 // Деструктор.
 virtual void Free() = 0;
 // Чтение из потока (возврат успешности чтения).
 virtual _bool_ Read(void* dst, _dword_ size) = 0;
 // Запись в поток, возврат успешности записи.
 virtual _bool_ Write(void* src, _dword_ size) = 0;
 // Установка позиции считывания/записи в потоке.
 virtual _int_ Seek(_int_ offset, _int_ origin) = 0;
 // Получить размер памяти потока.
 virtual _int_ Size() = 0;
 
 // Шаблон-функция чтения элемента любого типа данных из потока.
 template<typename DataType> _bool_ Read(const DataType& value)
 {
  return Read((void*)&value, sizeof(DataType));
 }
 // Шаблон-функция записи элемента любого типа данных в поток.
 template<typename DataType> _bool_ Write(const DataType& value)
 {
  return Write((void*)&value, sizeof(DataType));
 }
};


// Поток в памяти.
class TMemoryStream : public TStream
{
public:
 // Деструктор потока в памяти.
 virtual void Free();
 // Чтение из потока в памяти (возврат успешности чтения).
 virtual _bool_ Read(void* dst, _dword_ size);
 // Запись в поток в памяти с автоматическим расширением его памяти (блоками), возврат успешности записи.
 virtual _bool_ Write(void* src, _dword_ size);
 // Установка позиции считывания/записи в потоке (возврат -1 при неверном параметре - смещении).
 virtual _int_ Seek(_int_ offset, _int_ origin);
 // Получить размер памяти потока в памяти.
 virtual _int_ Size();

 // Указатель на память потока.
 _ptr_ memory;
 // Позиция курсора записи/считывания потока.
 _int_ position;
 // Размер памяти потока.
 _int_ size;
 // Конструктор пустого потока в памяти.
 static TMemoryStream* Create();
 // Конструктор потока в памяти.
 static TMemoryStream* Create(_dword_ size);
 // Именение размера занимаемой потоком памяти.
 void SetSize(_dword_ size);
 // Получить указатель на память потока.
 void* Memory()
 {
  return (void*)this->memory;
 }
};


// Флаг конструктора файлового потока - создать файл.
#define fmCreate   0xFFFF
// Флаг конструктора файлового потока - открыть файл для чтения.
#define fmOpenRead       0x0000
// Флаг конструктора файлового потока - открыть файл для записи.
#define fmOpenWrite      0x0001
// Флаг конструктора файлового потока - открыть файл для чтения и записи.
#define fmOpenReadWrite  0x0002


// Файловый поток.
class TFileStream : public TStream
{
protected:
 // Файл для чтения/записи потока.
 HANDLE h_file;

public:
 // Деструктор файлового потока.
 virtual void Free();
 // Чтение из файлового потока (возврат успешности чтения).
 virtual _bool_ Read(void* dst, _dword_ size);
 // Запись в файловый поток (возврат успешности записи).
 virtual _bool_ Write(void* src, _dword_ size);
 // Перемещение позиции считывания/записи в файловом потоке.
 virtual _int_ Seek(_int_ offset, _int_ origin);
 //  Получение размера файлового потока.
 virtual _int_ Size();

 // Конструктор файлового потока.
 static TFileStream* Create(_cstr_ file_name, _word_ mode);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Максимальная длина строки сообщения при подстановке параметров формата.
#define MAX_MSGVA_LENGTH 256

// Показ сообщения.
#define ShowMessage(msg) MessageBoxA(NULL, (LPCSTR)(msg), (LPCSTR)"", MB_OK)

// Показ сообщения с парамметрами формата.
inline void ShowVA(const char *pFormat, ... )
{
 // Список параметров.
 va_list Args;
 va_start(Args, pFormat);
 // Окончательная строка.
 char Buffer[MAX_MSGVA_LENGTH];
 // Записываем окончательную строку с параметрами.
 vsprintf(Buffer, pFormat, Args);
 va_end(Args);
 // Выводим сообщение.
 ShowMessage(Buffer);
}


// Преобразование строки в знаковое 32-битное число.
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
 // Число.
 _int_ result;
 sscanf(str, "%d", &result);
 return result;
}

// Является ли указанный символ строки символом из набора.
inline _bool_ IsDelimiter(_cstr_ Delimiters, _cstr_ S, _int_ Index)
{
 // Проходии по всем символам из набора.
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

// Шаблон динамического массива для любого типа элементов.
template <typename ElementType> class TArray
{
public:
 // Данные.
 ElementType* data;
 // Количество элементов массива.
 int length;
 // Размер занимаемой массивом памяти.
 int data_size;

 // Конструктор.
 TArray()
 {
  this->data = NULL;
  this->length = 0;
  this->data_size = 0;
 }

 //  Деструктор.
 ~TArray()
 {
  // Освобождаем занятую массивом память.
  MemFree(this->data);
 }

 // Получение количества элементов массива.
 _int_ Length()
 {
  return this->length;
 }

 // Установка количества элементов массива.
 void SetLength(_int_ new_len)
 {
  // Если длина массива не равна 0...
  if (new_len) 
  {
   // Минимальная память, достаточная, чтобы вместить new_len элементов.
   int need_min_size = new_len * sizeof(ElementType);
   // Довыделяемая память, кратна MIN_ARRAY_MEMBLOCK_SIZE.
   int new_size = ( need_min_size / MIN_ARRAY_MEMBLOCK_SIZE + ((need_min_size % MIN_ARRAY_MEMBLOCK_SIZE) != 0) ) * MIN_ARRAY_MEMBLOCK_SIZE;
   if (new_size != this->data_size)
   {
    // Выделяем новую память и копируем туда данные.
    //this->data = (ElementType*)MemRealloc(this->data, new_size);
    ElementType* new_data = (ElementType*)MemAlloc(new_size);
    MemCopy(new_data, data, min(data_size, new_size));
    MemFree(data);
    data = new_data;

    // Заполняем дополнительно выделенную память нулями.
    if (new_size > this->data_size)
     MemZero((_ptr_)this->data + this->data_size, new_size - this->data_size);
    this->data_size = new_size;
   }
   // Устанавливаем новую длину.
   this->length = new_len;
  }
  // Если новая длина равна 0, освобождаем память массива.
  else
  {
   MemFree(this->data);
   this->data = NULL;
   this->data_size = 0;
   this->length = 0;
  }
 }

 // Взятие элемента по индексу.
 ElementType& operator[](int index)
 {
  // Индекс автоматически ужимается до нужного диапазона.
  index = min(length - 1, max(0, index)); // if < 0 then =0, if > last then =last 
  return data[index];
 }

 // Добавление нового элемента в конец массива.
 void Add(const ElementType& value)
 {
  // Увеличиваем размер массива.
  SetLength(this->length + 1);
  // Копируем новый элемент в конец.
  MemCopy(&(this->data[this->length - 1]), &value, sizeof(ElementType)); 
 }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Строка с длиной (наследуется от динамического массива символов).
class TString: public TArray<_char_>
{
protected:
 // Строка, хранящая результат операции.
 static TString op_result;

public:
 // Конструктор.
 TString(const _cstr_ cstr);
 // Пустая строка.
 TString();
 // Деструктор.
 //~TString();

 // Преобразование строки к C-стилю.
 _char_* c_str()
 {
  return this->data;
 }

 // Установка длины строки.
 void SetLength(int new_len);
 // Добавление символа к строке.
 void Add(const _char_ &chr);
 
 // Приравнивание к строке с длиной.
 TString& operator=(TString& r_str);
 // Приравнивание к C-строке.
 TString& operator=(const _cstr_ r_str);
 // Приравнивание к символу.
 TString& operator=(_char_ r_chr);
 
 // Добавление строки с длиной.
 TString& operator+=(TString& r_str);
 // Добавление C-строки.
 TString& operator+=(const _cstr_ r_str);
 // Добавление символа.
 TString& operator+=(_char_ r_chr);

 // Сложение со строкой с длиной..
 friend TString& operator+(TString &l_tstr, TString &r_tstr);
 // Сложение с C-строкой.
 friend TString& operator+(TString &l_tstr, _cstr_ r_cstr);
 // Правое сложение с C-строкой.
 friend TString& operator+(_cstr_ l_cstr, TString &r_tstr);
 // Сложение с символом.
 friend TString& operator+(TString &l_tstr, _char_ r_chr);
 // Правое сложение с символом.
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



// Создание массива.
template<typename _type_> void MakeArray(_type_** array_off, _int_ count)
{
  // Если массив уже заполнен, освобождаем его.
  if (*array_off)
  {
    // Денициализируем объекты.
    for (_int_ i = 0; i < count; i++)
    {
      ((*array_off)[i]).~_type_();
    }
    
    MemFree(*array_off);
  }
  
  // Выделяем память под новый массив.
  if (count)
  {
    *array_off = (_type_*)MemAlloc(sizeof(_type_)*count);
    
    // Инициализируем объекты.
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

// Получение параметров HD.
extern FARPROC HdCommon_Get;
#define HDC_Get(name, default_value) HdCommon_Get?CALL_2(_dword_,__stdcall,HdCommon_Get,name,default_value):default_value

// Установка параметров HD.
extern FARPROC HdCommon_Set;
#define HDC_Set(name, value) HdCommon_Set?CALL_2(_bool_,__stdcall,HdCommon_Set,name,value):FALSE */



#define strempty(string) do{string[0] = 0;}while(false)



#define va_cstr(pFormat, ...) Base::va_cstr(pFormat, __VA_ARGS__)

#define _L(ru, en) (Base::SystemLanguageIsRussian() ? (ru) : (en))


#define _LW(ru, en) (Base::SystemLanguageIsRussian()  ? (L##ru) : (L##en))
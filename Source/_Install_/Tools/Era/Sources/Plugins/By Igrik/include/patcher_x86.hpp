////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����������� patcher_x86.dll 
// ���������������� ��������(���������)
// ��������� �����: ������� ��������� (baratorch), e-mail: baratorch@yandex.ru
// ����� ���������� �������������� ����� (LoHook) ������� �������������� � Berserker (�� ERA)
////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ������ 4.3.1

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ��������.
//
// ! ���������� �������������:
//  - ������� ��������������� ���������������� 
//    ����������� ��� ��������� ������ � �����
//    � ��� ������� ���������.
//  - �������������� �����������: ������������ ���� ������� � �������
//    ���������� ��� � ���������� ��������� ������� jmp � call c 
//    ������������� ����������
// ! ���������� ���������
//  - ������������� ��� ������� ��� � ������� �����.
//  - ������������� ��������������� ����, ������� ������������ ������� �
//    � ������� ���� �� ����, �� �������� � ��������� ����������,
//    �����, � �������� � ������������ ���.
//  - ������������� ��������������� ���� ���� �� ������
//    �� �������� � �������� ��� ���� ���������������� �����
//    ������������� ������ ����������
//  - ������������� �������������� ���� � ��������������� �������� �
//    ��������� ����������, �����, ��������� ���� � ������ �������� � ���
//  - �������� ����� ���� � ���, ������������� � ������� ���� ����������.
//  - ������ ������������ �� ������������ ���, ������������ ����������
//  - ������ ����� ��� (������������ ����������) ��������� ������������ ����/���
//  - �������� ������ ������ �� ���� ������/�����, ������������� �� ������ ����� 
//    � ������� ���� ����������
//  - ����� � ������ ���������� ������������� ����� �� ������ �����
//    (������������ ��� ����������) 1) �������� ���� ����� ��������� ���:
//        - ��������������� �����/���� ������� ������� �� ���� �����
//        - ��������������� �����/���� ������������� ���� ������� �� ���������
//        - ��������������� ����� ������ ����� � ��������
//    � ��� �� 2) ����� ����������� ���������� ���� (����� �������) ���� ������ 
//    � ����� ������������� � ������� ���� ���������� � ���������� ������ �������.
////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����������.
//
// �� ��������� � patcher_x86.dll ����������� ���������, ����� �������� ���,
// ���������� � ��� �� ����� ������� ���� patcher_x86.ini c ������������
// �������: Logging = 1 (Logging = 0 - ��������� ����������� �����)
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ������� �������������.
//
// 1) ������ ��� ������ 1 ��� ������� ������� GetPatcher(), �������� ���������
//  ��������: Patcher* _P = GetPatcher();
// 2) ����� � ������� ������ Pather::CreateInstance ����� �������  
// ��������� Pat�herInstance �� ����� ���������� ������
//  ��������: Pat�herInstance* _PI = _P->CreateInstance("MyMod");
// 3)  ����� ������������ ������ ������� Pat�her � Pat�herInstance
// ��������������� ��� ������ � ������� � ������
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#define _byte_ unsigned __int8
#define _word_ unsigned __int16
#define _dword_ unsigned __int32


//������� CALL_? ��������� �������� ������������ ������� �� ������������� ������
//������������ � ��� ����� ��� ������ �������
//���������� � ������� HiHook::GetDefaultFunc � HiHook::GetOriginalFunc
#define CALL_0(return_type, call_type, address) \
 ((return_type (call_type *)(void))address)()
#define CALL_1(return_type, call_type, address, a1) \
 ((return_type (call_type *)(_dword_))(address))((_dword_)(a1))
#define CALL_2(return_type, call_type, address, a1, a2) \
 ((return_type (call_type *)(_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2))
#define CALL_3(return_type, call_type, address, a1, a2, a3) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3))
#define CALL_4(return_type, call_type, address, a1, a2, a3, a4) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4))
#define CALL_5(return_type, call_type, address, a1, a2, a3, a4, a5) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5))
#define CALL_6(return_type, call_type, address, a1, a2, a3, a4, a5, a6) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6))
#define CALL_7(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7))
#define CALL_8(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8))
#define CALL_9(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9))
#define CALL_10(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10))
#define CALL_11(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11))
#define CALL_12(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12))
#define CALL_13(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13))
#define CALL_14(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14))
#define CALL_15(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14),(_dword_)(a15))
#define CALL_16(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14),(_dword_)(a15),(_dword_)(a16))
#define CALL_17(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17) \
 ((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14),(_dword_)(a15),(_dword_)(a16),(_dword_)(a17))

#define CALL_VA(return_type, adress, a1, ...) \
 ((return_type (__cdecl *)(_dword_, ...))(adress))((_dword_)(a1), __VA_ARGS__)


// _bool_ - 4-� �������� ���������� ���, ��� BOOL � Win32 API
// ���� ����� ���������, ����� �������� �� BOOL ��� ������������ bool ��������
#define _bool_ __int32

#define NULL 0

// ��� ������ � ����� ���������� ���������� ���� �����,
// ���� ��� ������� ��-�������, ������ �������� _ptr_ �� ����� ������ ���, void* ��� int ��������
typedef _dword_ _ptr_;



// �� ���� ���������� � ����������� ���������� ������ ���� ������������ - 4 �����
#pragma pack(push, 4)


//��� "����������", ������������ ��� ������������ �������� Patcher::VarInit � Patcher::VarFind ��������.
class Variable
{
public:
	// ���������� �������� '����������' (���������������� ���������)
	virtual _dword_ __stdcall GetValue() = 0;
	// ������������� �������� '����������' (���������������� ���������)
	virtual void __stdcall SetValue(_dword_ value) = 0;
	// ���������� ��������� �� �������� (��������� � �������� ����� ��������� �����������������)
	virtual _dword_* __stdcall GetPValue() = 0;
};

// ��� '������� ������', ������ - 32 ���� 
// ������������ � HookContext
struct FlagsRegister
{
	_dword_ CF			: 1; //0
	_dword_ reserved_1	: 1; //1
	_dword_ PF			: 1; //2
	_dword_ reserved_3	: 1; //3
	_dword_ AF			: 1; //4
	_dword_ reserved_5	: 1; //5
	_dword_ ZF			: 1; //6
	_dword_ SF			: 1; //7
	_dword_ TF			: 1; //8
	_dword_ IF			: 1; //9
	_dword_ DF			: 1; //10
	_dword_ OF			: 1; //11
	_dword_ IOPL		: 2; //12-13
	_dword_ NT			: 1; //14
	_dword_ reserved_15	: 1; //15
	_dword_ RF			: 1; //16
	_dword_ VM			: 1; //17
	_dword_ AC			: 1; //18
	_dword_ VIF			: 1; //19
	_dword_ VIP			: 1; //20
	_dword_ ID			: 1; //21
	_dword_ reserved_22	: 1; //22
	_dword_ reserved_23	: 1; //23
	_dword_ reserved_24	: 1; //24
	_dword_ reserved_25	: 1; //25
	_dword_ reserved_26	: 1; //26
	_dword_ reserved_27	: 1; //27
	_dword_ reserved_28	: 1; //28
	_dword_ reserved_29	: 1; //29
	_dword_ reserved_30	: 1; //30
	_dword_ reserved_31	: 1; //31
};

// ��������� HookContext
// ������������ � �������� ����������� �� LoHook ����
struct HookContext
{
 int eax; //������� EAX, ������/���������
 int ecx; //������� ECX, ������/���������
 int edx; //������� EDX, ������/���������
 int ebx; //������� EBX, ������/���������
 int esp; //������� ESP, ������/���������
 int ebp; //������� EBP, ������/���������
 int esi; //������� ESI, ������/���������
 int edi; //������� EDI, ������/���������

 _ptr_ return_address; //����� ��������, ������/���������

 FlagsRegister flags; //������� ������, ������/���������
 // ��� ������ ���������������� �� �������������� ������� ���� (����. delphi)
 // flags ����� ���� ��������� ��� _dword_ ����.


 // ������� Push ����� ����������� �������� ������� ���������� PUSH ��� ��������� LoHook ����
 // ��� ������������� � ���������� ���� �������������� � ������� WriteLoHook ��� CreateLoHook
 // ������ ������ ������� ����� ���� �������� � ���� � ������� ���� ������� ��������� 128 �������.
 // ��� ������������� � ���������� ���� �������������� � ������� WriteLoHookEx ��� CreateLoHookEx
 // ���� ������ ��������������� ����������� ��� ������ WriteLoHookEx ��� CreateLoHookEx.
 inline void Push(int v)
 {
	 esp -= 4;
	 *(int*)(esp) = v;
 }

 // ������� Pop ����� ����������� �������� ������� ���������� POP ��� ��������� LoHook ����
 inline int Pop()
 {
	 int r = *(int*)(esp);
	 esp += 4;
	 return r;
 }
};



// �������� ������������ �������� ������������� �� LoHook ����
#define EXEC_DEFAULT 1
#define NO_EXEC_DEFAULT 0
#define SKIP_DEFAULT 0


// �������� ������������� Patch::GetType()
#define PATCH_  0
#define LOHOOK_ 1
#define HIHOOK_ 2


// �������� ������������ PatcherInstance::Write() � PatcherInstance::CreatePatch()
#define DATA_ 0
#define CODE_ 1


// ����������� ����� Patch
// ������� ��������� ����� �
// ������� ������� ������ PatcherInstance
class Patch
{
public:
 // ���������� ����� �� �������� ��������������� ����
 virtual _ptr_ __stdcall GetAddress() = 0; 

 // ���������� ������ �����
 virtual _dword_ __stdcall GetSize() = 0; 

 // ���������� ���������� ��� ���������� PatcherInstance, � ������� �������� ��� ������ ����
 virtual char* __stdcall GetOwner() = 0;

 // ���������� ��� �����
 // ��� �� ���� ������ PATCH_
 // ��� LoHook ������ LOHOOK_
 // ��� HiHook ������ HIHOOK_
 virtual int  __stdcall GetType() = 0;

 // ���������� true, ���� ���� �������� � false, ���� ���.
 virtual _bool_ __stdcall IsApplied() = 0;

 // ��������� ���� 
 // ���������� >= 0 , ���� ����/��� ���������� �������
 // (������������ �������� �������� ���������� ������� ����� � ������������������
 // ������, ����������� �� ����������� ������� ������, ��� ������ �����, 
 // ��� ������� ��� �������� ����)
 // ���������� -2, ���� ���� ��� ��������
 // ��������� ���������� ������ ��������������� ������� � ���
 virtual _bool_ __stdcall Apply() = 0;

    // ApplyInsert ��������� ���� � ��������� ����������� ������ �
 // ������������������ ������, ����������� �� ����� ������.
 // ������������ �������� ���������� �������������� � Patch::Apply
 // ������� ApplyInsert ����� ���������� �������� ��������, ������������ 
 // �������� Undo, ����� ��������� ���� � �� �� �����, �� ������� ��� ��� �� ���������.
 virtual _bool_ __stdcall ApplyInsert(int zorder) = 0;

 /////////////////////////////////////////////////////////////////////////////////////////////////////
 // ����� Undo
 // �������� ����(���) (� ������ ���� ���� �������� ��������� - ��������������� �������� ���)
 // ���������� ����� >= 0, ���� ����(���) ��� ������� ������� 
 // (������������ �������� �������� ������� ����� � ������������������
 // ������, ����������� �� ������� ������, ��� ������ �����, 
 // ��� ������� ��� �������� ����)
 // ���������� -2, ���� ���� � ��� ��� ��� ������� (�� ��� ��������)
 // ��������� ���������� ������ ��������������� ������� � ���
 virtual _bool_ __stdcall Undo() = 0;


 /////////////////////////////////////////////////////////////////////////////////////////////////////
 // ����� Destroy
 // ����������
 // �������� � ������������ ���������� ����/���
 // ���������� ������ 1 (��� ������������� � ����� ������� �������� ����������)
 // ��������� ����������� ��������������� ������� � ���
 virtual _bool_ __stdcall Destroy() = 0;

 /////////////////////////////////////////////////////////////////////////////////////////////////////
 // ����� GetAppliedBefore
 // ���������� ���� ����������� ����� ������
 // ���������� NULL ���� ������ ���� �������� ������
 virtual Patch* __stdcall GetAppliedBefore() = 0;

 /////////////////////////////////////////////////////////////////////////////////////////////////////
 // ����� GetAppliedAfter
 // ���������� ���� ����������� ����� �������
 // ���������� NULL ���� ������ ���� �������� ���������
 virtual Patch* __stdcall GetAppliedAfter() = 0;

};


// ����������� ����� LoHook (����������� �� Patch, �.�. �� ���� ���-��� �������� ������)
// ������� ��������� ����� �
// ������� ������� ������ PatcherInstance
class LoHook : public Patch
{
};


typedef int(__stdcall *_LoHookFunc_)(LoHook*, HookContext*);


// �������� ������������ ��� �������� hooktype � PatcherInstance::WriteHiHook � PatcherInstance::CreateHiHook
#define CALL_ 0
#define SPLICE_ 1
#define FUNCPTR_ 2

// �������� ������������ ��� �������� subtype � PatcherInstance::WriteHiHook � PatcherInstance::CreateHiHook
#define DIRECT_  0
#define EXTENDED_ 1
#define SAFE_  2

// �������� ������������ ��� �������� calltype � PatcherInstance::WriteHiHook � PatcherInstance::CreateHiHook
#define ANY_  0
#define STDCALL_ 0
#define THISCALL_ 1
#define FASTCALL_ 2 
#define CDECL_  3
#define FASTCALL_1 1 

// ����������� ����� HiHook (����������� �� Patch, �.�. �� ���� ���-��� �������� ������)
// ������� ��������� ����� � ������� ������� ������ PatcherInstance
class HiHook : public Patch
{
public:
 // ���������� ��������� �� ������� (�� ���� � ������� � ������ SPLICE_),
 // ���������� �����
 // ��������! ������� ������� ��� �� ������������ ����, ����� ��������
 // ������������ (�� �������) ��������.
 virtual _ptr_ __stdcall GetDefaultFunc() = 0;

 // ���������� ��������� �� ������������ ������� (�� ���� � ������� � ������ SPLICE_),
 // ���������� �����(������) �� ������� ������
 // (�.�. ���������� GetDefaultFunc() ��� ������� ������������ ���� �� ������� ������)
 // ��������! ������� ������� ��� �� ������������ ����, ����� ��������
 // ������������ (�� �������) ��������.
 virtual _ptr_ __stdcall GetOriginalFunc() = 0;

 // ���������� ����� �������� � ������������ ���
 // ����� ������������ ������ ���-�������
 // SPLICE_ EXTENDED_ ��� SAFE_ ����, ����� ������ ������ ��� ���� �������
 // ��� SPLICE_ DIRECT_ ���� ������� ���������� ������ 0 (�.�. ��� DIRECT_ ���� ����������� ������ ����� �������� ����� ��� - ���)
 virtual _ptr_ __stdcall GetReturnAddress() = 0;


 //# ver 2.1
 // ������������� �������� ���������������� ������ ����
 virtual void __stdcall SetUserData(_dword_ data) = 0;
 // ���������� �������� ���������������� ������ ����
 // ���� �� ������ �������������, �� ����� 0
 virtual _dword_ __stdcall GetUserData() = 0;
};


// ����������� ����� PatcherInstance
// �������/�������� ��������� ����� � ������� ������� CreateInstance � GetInstance ������ Patcher
// ��������������� ��������� ���������/������������� ����� � ���� � ���,
// �������� �� � ������ ���� ������/�����, ��������� ����������� patcher_x86.dll
class PatcherInstance
{
public:
 ////////////////////////////////////////////////////////////
 // ����� WriteByte
 // ����� ����������� ����� �� ������ address
 // (������� � ��������� DATA_ ����)
 // ���������� ��������� �� ����
 virtual Patch* __stdcall WriteByte(_ptr_ address, int value) = 0;
 
 ////////////////////////////////////////////////////////////
 // ����� WriteWord
 // ����� ������������ ����� �� ������ address
 // (������� � ��������� DATA_ ����)
 // ���������� ��������� �� ����
 virtual Patch* __stdcall WriteWord(_ptr_ address, int value) = 0;
 
 ////////////////////////////////////////////////////////////
 // ����� WriteDword
 // ����� ��������������� ����� �� ������ address
 // (������� � ��������� DATA_ ����)
 // ���������� ��������� �� ����
 virtual Patch* __stdcall WriteDword(_ptr_ address, int value) = 0;
 
 ////////////////////////////////////////////////////////////
 // ����� WriteJmp
 // ����� jmp to ����� �� ������ address
 // (������� � ��������� CODE_ ����)
 // ���������� ��������� �� ����
 // ���� ��������� ����� ���������� �������,
 // �.�. ������ ����� >= 5, ������� ����������� NOP'���. 
 virtual Patch* __stdcall WriteJmp(_ptr_ address, _ptr_ to) = 0;
 
 ////////////////////////////////////////////////////////////
 // ����� WriteHexPatch
 // ����� �� ������ address ������������������ ����,
 // ������������ hex_str
 // (������� � ��������� DATA_ ����)
 // ���������� ��������� �� ����
 // hex_str - ��-������ ����� ��������� ����������������� �����
 // 0123456789ABCDEF (������ ������� �������!) ��������� ������� 
 // ��� ������ ������� hex_str ������������(������������)
 // ������ ������������ � �������� ��������� ����� ������
 // ������������� � ������� Binary copy � OllyDbg
 /* ������:
   pi->WriteHexPatch(0x57b521, "6A 01  6A 00");
 */
 virtual Patch* __stdcall WriteHexPatch(_ptr_ address, char* hex_str) = 0;
 
 ////////////////////////////////////////////////////////////
 // ����� WriteCodePatchVA
 // � ������������ ���� ���������� ������ �� ��������������,
 // �������� (����) �������� ������-�������� WriteCodePatch
 virtual Patch* __stdcall WriteCodePatchVA(_ptr_ address, char* format, _dword_* va_args) = 0;
 
 ////////////////////////////////////////////////////////////
 // ����� WriteLoHook
 // ������� �� ������ address �������������� ��� (CODE_ ����) � ��������� ���
 // ���������� ��������� �� ���
 // func - ������� ���������� ��� ������������ ����
 // ������ ����� ��� int __stdcall func(LoHook* h, HookContext* c);
 // � HookContext* c ���������� ��� ������/��������� 
 // �������� ���������� � ����� ��������
 // ���� func ���������� EXEC_DEFAULT, �� 
 // ����� ���������� func ����������� �������� ����� ���.
 // ���� - SKIP_DEFAULT - �������� ��� �� �����������
 //
 // ��������! 
 // ������ ������, ������� ����� ���� �������� � ���� ���������
 // � ������� ������������� c->esp � �->Push, ��������� 128 �������.
 // ���� ��������� ���� ����������� ����������� ����� WriteLoHookEx ��� CreateLoHookEx.
 virtual LoHook* __stdcall WriteLoHook(_ptr_ address, _LoHookFunc_ func) = 0;
 
 ////////////////////////////////////////////////////////////
 // ����� WriteHiHook
 // ������� �� ������ address ��������������� ��� � ��������� ���
 // ���������� ��������� �� ���
 //
 // new_func - ������� ���������� ������������
 //
 // hooktype - ��� ����:
 //  CALL_ -  ��� �� ����� ������� �� ������ address
 //     �������������� ������ E8 � FF 15, � ��������� ������� ��� �� ���������������
 //     � � ��� ������� ���������� �� ���� ������
 //  SPLICE_ - ��� ��������������� �� ���� ������� �� ������ address
 //  FUNCPTR_ - ��� �� ������� � ��������� (����������� �����, � �������� ��� ����� � �������� �������)
 //
 // subtype - ������ ����:
 //  DIRECT_ - new_func ����� ��� �� ��� ��� �
 //     ������������ ���������� �������
 //     ����������: ������ __thiscall f(this) 
 //        ����� ������������ __fastcal f(this_)
 //        ������ __thiscall f(this, ...)  ����� ������������ 
 //        __fastcall f(this_, no_used_edx, ...) 
 //  EXTENDED_ - ������� new_func ������ �������� ���������� ����������
 //     ��������� �� ��������� HiHook �, � ������ 
 //     ���������� �������� �-�� __thiscall � __fastcall
 //     ����������� ��������� ���������� ��������� ������� 
 // ����� ������� ������� new_func ������ ����� ���
 // ? __stdcall new_func(HiHook* hook, ?) ��� ? ? orig(?)
 //
 // ��������! EXTENDED_ FASTCALL_ ������������ ������ ������� � 2-�� � ����� �����������
 // ��� __fastcall c 1 ���������� ����������� EXTENDED_ FASTCALL_1 / EXTENDED_ THISCALL_
 //
 //   SAFE_ - �� �� ����� ��� � EXTENDED_, ������ ����� ������� (�� ����� ������) GetDefaultFunc() �����������������
 //    �������� ��������� ���������� EAX, ECX (���� �� FASTCALL_ � �� THISCALL_),
 //    EDX (���� �� FASTCALL_), EBX, ESI, EDI, ������ �� ������ ������ ���������� �������
 //
 //  � ����������� ����������� ������� ������� ������������ EXTENDED_
 //  �� DIRECT_ ����������� ������� ��-�� �������� ����� � ����� ���������� �������
 //
 // calltype - ���������� � ������ ������������ ���������� �-��:
 //  STDCALL_
 //  THISCALL_
 //  FASTCALL_
 //  CDECL_
 // ���������� ����� ��������� ���������� ��� ���� ����� EXTENDED_ ��� ���������
 // �������� ���� � ����� ���������� �������
 //
 // CALL_, SPLICE_ ��� �������� CODE_ ������
 // FUNCPTR_ ��� �������� DATA_ ������
 //
 virtual HiHook* __stdcall WriteHiHook(_ptr_ address, int hooktype, int subtype, int calltype, void* new_func) = 0;

 ///////////////////////////////////////////////////////////////////
 // ������ Create...
 // ������� ����/��� ��� �� ��� � ��������������� ������ Write...,
 // �� �� ��������� ���
 // ���������� ��������� �� ����/���
 virtual Patch* __stdcall CreateBytePatch(_ptr_ address, int value) = 0;
 virtual Patch* __stdcall CreateWordPatch(_ptr_ address, int value) = 0;
 virtual Patch* __stdcall CreateDwordPatch(_ptr_ address, int value) = 0;
 virtual Patch* __stdcall CreateJmpPatch(_ptr_ address, _ptr_ to) = 0;
 virtual Patch* __stdcall CreateHexPatch(_ptr_ address, char* hex_str) = 0;
 virtual Patch* __stdcall CreateCodePatchVA(_ptr_ address, char* format, _dword_* va_args) = 0;
 virtual LoHook* __stdcall CreateLoHook(_ptr_ address, void* func) = 0;
 virtual HiHook* __stdcall CreateHiHook(_ptr_ address, int hooktype, int subtype, int calltype, void* new_func) = 0;
 
 ////////////////////////////////////////////////////////////
 // ����� ApplyAll
 // ��������� ��� �����/����, ��������� ���� ����������� PatcherInstance
 // ������ ���������� 1 (��� ������������� � ����� ������� �������� ����������)
 // (��. Patch::Apply)
 virtual _bool_ __stdcall ApplyAll() = 0;

 ////////////////////////////////////////////////////////////
 // ����� UndoAll
 // �������� ��� �����/����, ��������� ���� ����������� PatcherInstance
 // �.�. ��� ������� �� ������/����� �������� ����� Undo
 // ������ ���������� 1 (��� ������������� � ����� ������� �������� ����������)
 // (��. Patch::Undo)
 virtual _bool_ __stdcall UndoAll() = 0;

 ////////////////////////////////////////////////////////////
 // ����� DestroyAll
 // �������� � ������������ ���������� ��� �����/����, ��������� ���� ����������� PatcherInstance
 // �.�. ��� ������� �� ������/����� �������� ����� Destroy
 // ������ ���������� 1 (��� ������������� � ����� ������� �������� ����������)
 // (��. Patch::Destroy)
 virtual _bool_ __stdcall DestroyAll() = 0;

 // � ������������ ���� ���������� ������ �� ��������������,
 // �������� (����) �������� ������-�������� WriteDataPatch
 virtual Patch* __stdcall WriteDataPatchVA(_ptr_ address, char* format, _dword_* va_args);
 // � ������������ ���� ���������� ������ �� ��������������,
 // �������� (����) �������� ������-�������� WriteDataPatch
 virtual Patch* __stdcall CreateDataPatchVA(_ptr_ address, char* format, _dword_* va_args);


 // ����� GetLastPatchAt
 // ���������� NULL, ���� � ����������� ������ address �� ��� �������� �� ���� ����/���,
 // ��������� ������ ����������� PatcherInstance
 // ����� ���������� ��������� ���������� ����/��� � ����������� ������ address,
 // ��������� ������ ����������� PatcherInstance
 virtual Patch* __stdcall GetLastPatchAt(_ptr_ address) = 0;

 // ����� UndoAllAt
 // �������� ����� ����������� ������ ����������� PatcherInstance
 // � ����������� ������ address 
 // ������ ���������� 1 (��� ������������� � ����� ������� �������� ����������)
 // (��. Patch::Undo)
 virtual _bool_ __stdcall UndoAllAt(_ptr_ address) = 0;

 // ����� GetFirstPatchAt
 // ���������� NULL, ���� � ����������� ������ address �� ��� �������� �� ���� ����/���,
 // ��������� ������ ����������� PatcherInstance
 // ����� ���������� ������ ���������� ����/��� � ����������� ������ address,
 // ��������� ������ ����������� PatcherInstance
 virtual Patch* __stdcall GetFirstPatchAt(_ptr_ address) = 0;


 ////////////////////////////////////////////////////////////
 // ����� Write
 // ����� �� ������ address ������/��� �� ������ �� ������ data �������� size ���� 
 // ���� is_code == 1, �� ��������� � ������� CODE_ ����, ���� 0 - DATA_ ����.
 // ���������� ��������� �� ����
 virtual Patch* __stdcall Write(_ptr_ address, _ptr_ data, _dword_ size, _bool_ is_code = 0) = 0;
 ///////////////////////////////////////////////////////////////////
 // ����� CreatePatch
 // ������ ���� ��� �� ��� � ����� Write,
 // �� �� ��������� ���
 // ���������� ��������� �� ����
 virtual Patch* __stdcall CreatePatch(_ptr_ address, _ptr_ data, _dword_ size, _bool_ is_code = 0) = 0;


 //## ver 2.1
  ////////////////////////////////////////////////////////////
 // ����� WriteLoHookEx
 // ���������� ������ WriteLoHook, �� ����� �������������� ��������
 // stack_delta - ������ ������ ������� ����� ��������� � ���� ���������
 // ��������� HookContext::esp � HookContext::Push ������ func.
 //
 // ���������� ��������� �� LoHook ���
 virtual LoHook* __stdcall WriteLoHookEx(_ptr_ address, void* func, _dword_ stack_delta) = 0;
 // ����� CreateLoHookEx
 // ������� ��� ��� �� ��� � WriteLoHookEx,
 // �� �� ��������� ���.
 // ���������� ��������� �� LoHook ���
 virtual LoHook* __stdcall CreateLoHookEx(_ptr_ address, void* func, _dword_ stack_delta) = 0;


 // � ������������ ���� ���������� ������ �� ��������������,
 // �������� (����) �������� ������-�������� WriteHexHook
 virtual LoHook* __stdcall WriteHexHookVA(_ptr_ address, _bool_ exec_default, char* hex_str, _dword_* va_args) = 0;
 // � ������������ ���� ���������� ������ �� ��������������,
 // �������� (����) �������� ������-�������� CreateHexHook
 virtual LoHook* __stdcall CreateHexHookVA(_ptr_ address, _bool_ exec_default, char* hex_str, _dword_* va_args) = 0;



 // ����� BlockAt ������������� ���� �� ������������ ����� (������ �� ���������� ����� � �� �� �����������)
 // ��� ������� ���������� PatcherInstance
 // ����� ���� ������ ��������� PatcherInstance �� ����� ��������� 
 // ����� �� ����� ������
 virtual void __stdcall BlockAt(_ptr_ address) = 0;

 //## ver 2.6

 // ����� BlockAllExceptVA ������������� ���� �� ��� ������ ����� ��������� � va_args
 // ��� �� ��� � ����� BlockAt ��������� ����������� �������� � �� �������������
 // ��� ������� ���������� PatcherInstance
 // ����� ���� ������ ��������� PatcherInstance �� ����� ��������� 
 // ����� �� ���� ������� ����� ���������.
 // ������ ������� � va_args ������ ������������� 0 (�����)
 virtual void __stdcall BlockAllExceptVA(_dword_ *va_args) = 0;


 //## ver 4.0
 // � ������������ ���� ���������� ������ �� ��������������,
 // �������� (����) �������� ������-�������� WriteAsmPatch
 virtual Patch* __stdcall WriteAsmPatchVA(_ptr_ address, _dword_* va_args) = 0;

 // � ������������ ���� ���������� ������ �� ��������������,
 // �������� (����) �������� ������-�������� CreateAsmPatch
 virtual Patch* __stdcall CreateAsmPatchVA(_ptr_ address, _dword_* va_args) = 0;

 // � ������������ ���� ���������� ������ �� ��������������,
 // �������� (����) �������� ������-�������� WriteAsmHook
 virtual LoHook* __stdcall WriteAsmHookVA(_ptr_ address, _dword_* va_args) = 0;

 // � ������������ ���� ���������� ������ �� ��������������,
 // �������� (����) �������� ������-�������� CreateAsmHook
 virtual LoHook* __stdcall CreateAsmHookVA(_ptr_ address, _dword_* va_args) = 0;


 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // WriteAsmPatch ����� ���� �� ������ address
 // ��������e� ��������� �� ����
 // ��������� ... - ��� ������, ���������� ��� �� ����������
 // ������������ ��� ����������, �������������� OllyDbg 1.04 (������ �� MMX � amd 3DNow! ������������)
 // ��������! � ������� �� OllyDbg, ����� ����� �� ������� �������� 0x ��� ��������� h �������� ��� ������������!
 // ������� �� ��������� ������ ���������������� ����� ����
 // � ����� ������ ����� ���� ��������� ����������, ����������� �������� ';'
 // ��� �� ���������� ����� ��������� �����;
 // ���������� ����� - label_name: (��� �����, ���������),
 // ������������� label_name (��� ��� ���������);
 // ������������ ����� ����� ����� - 39 ��������, ��� ����� ��������� �����, �����, ������� '_' � '.';
 // ��� ����� ��������� ���������������� times (����� �������� ���������� ��� ��������� ����������)
 // ��������, ����������� "times 3 nop" ����� ��� 90 90 90
 // ��� ����� ��������� ���������������� _ExecCopy <�����>, <������> (����� ��� �� ������ �� ������ <�����> �������� <������>)
 // ��� ����� ��������� ���������������� db <�����>, dw <�����>, dd <����� ��� �����>.
 // ������ ����� ��������� ������-������� %d. � ���� ������ �� ������� ������ ��������� ��������������� ���������� ��������������� ����� (��������/�����������/������/...)
 // ��������! ��������� ���������� (�������) ������ ����������� ���� 0 (NULL)!
 // ����������� ������: WriteAsmPatch(0x112233, "begin: call %d", MyFunc, "jmp begin", "jne dword [%d]", 0xAABBCC, 0);
 inline Patch* WriteAsmPatch(_ptr_ address, ...)
 {
	 return WriteAsmPatchVA(address, (_dword_*)((_ptr_)&address + 4));
 }
 ////////////////////////////////////////////////////////////
 // ����� CreateAsmPatch
 // ������� ���� ��� �� ��� � ����� WriteCodePatch,
 // �� �� ��������� ���
 // ��������e� ��������� �� ����
 inline Patch* CreateAsmPatch(_ptr_ address, ...)
 {
	 return CreateAsmPatchVA(address, (_dword_*)((_ptr_)&address + 4));
 }

 ////////////////////////////////////////////////////////////
 // WriteAsmHook ����� �� ������ address ����������� ���
 // � ������ LoHook ��� ������ ��������������� �������.
 // ���� ���� ������� ����� � ������ CreateHexHook ��� WriteHexHook
 // ����� �� ������� ��� ������� ���� � ������� WriteAsmPatch (��. WriteAsmPatch)
 // � ������� ������ WriteAsmPatch ����� ��� ����� ��������� (� ����� �� ���������) ������������� _ExecDefault,
 // ������� ��������� �������� ����� ���
 // ��������! � ���� �� ����� ���� ������ ����� ������������� _ExecDefault
 // ���������� ��������� �� LoHook ���
 // ��������! ��������� ���������� (�������) ������ ����������� ���� 0 (NULL)!
 // ����������� ������: WriteAsmHook(0x112233, "cmp eax, 0; jne SkipDefault; _ExecDefault; jmp End; SkipDefault: mov ecx, 2; End: retn", 0);
 inline LoHook* WriteAsmHook(_ptr_ address, ...)
 {
	 return WriteAsmHookVA(address, (_dword_*)((_ptr_)&address + 4));
 }

 ////////////////////////////////////////////////////////////
 // ����� CreateAsmHook
 // ������� ��� ��� �� ��� � WriteAsmHook,
 // �� �� ��������� ���.
 // ���������� ��������� �� LoHook ���
 inline LoHook* CreateAsmHook(_ptr_ address, ...)
 {
	 return CreateAsmHookVA(address, (_dword_*)((_ptr_)&address + 4));
 }



//WriteHexHook ����� �� ������ address ����� ����������� ���
//� ������ LoHook ��� ������ ��������������� �������.
//���� ���� ������� ����� � ������ CreateHexHook ��� WriteHexHook
//����� �� ������� ��� ������� ���� � ������� WriteCodePatch (��. WriteCodePatch)
//
//exec_default - ��������� �� �������� ����� ��� ����� ���������� ���� ����
//���������� ��������� �� LoHook ���
 inline LoHook* WriteHexHook(_ptr_ address, _bool_ exec_default, char* format, ...)
 {
  return WriteHexHookVA(address, exec_default, format, (_dword_*)((_ptr_)&format + 4));
 }
 // ����� CreateHexHook
 // ������� ��� ��� �� ��� � WriteHexHook,
 // �� �� ��������� ���.
 // ���������� ��������� �� LoHook ���
 inline LoHook* CreateHexHook(_ptr_ address, _bool_ exec_default, char* format, ...)
 {
  return CreateHexHookVA(address, exec_default, format, (_dword_*)((_ptr_)&format + 4));
 }


 ////////////////////////////////////////////////////////////
 // ����� WriteCodePatch
 // ����� �� ������ address ������������������ ����,
 // ������������ format � ...
 // (������� � ��������� CODE_ ����)
 // ���������� ��������� �� ����
 // format - ��-������ ����� ��������� ����������������� �����
 // 0123456789ABCDEF (������ ������� �������!),
 // � ��� �� ����������� ������-������� (������ �������!):
 // %b - (byte) ����� ������������ ����� �� ...
 // %w - (word) ����� ������������ ����� �� ...
 // %d - (dword) ����� ��������������� ����� �� ...
 // %j - ����� jmp �� ����� �� ...
 // %� - ����� �all ...
 // %m - �������� ��� �� ������ ... �������� ... (�.�. ������ 2 ��������� �� ...)
 //      ����������� ���������� ����������� MemCopyCodeEx (��. ��������)
 // %% - ����� ������ � ������-��������� �� ... 
 // %o - (offset) �������� �� ������ �� ��������� �������� ������� �
 //      Complex ����,  ������������ ������ Complex ����.
 // %n - ����� nop ������, ����������� ������ ...                                  \
 // #0: - #9: -������������� ����� (�� 0 �� 9) � ������� ����� ������� � ������� #0 - #9                              \
 // #0 -  #9  -����� ������������ ����� ����� ������� EB, 70 - 7F, E8, E9, 0F80 - 0F8F
 //      ��������������� �����; ����� ������ ������� ������ �� �����
 // ~b - ����� �� ... ���������� ����� � ����� ������������� �������� �� ����
 //      �������� � 1 ���� (������������ ��� ������� EB, 70 - 7F)
 // ~d - ����� �� ... ���������� ����� � ����� ������������� �������� �� ����
 //      �������� � 4 ����� (������������ ��� ������� E8, E9, 0F 80 - 0F 8F)
 // %. - ������ �� ������ ( ��� � ����� ������ �� ����������� ���� ������ ����� % ) 
 // ����������� ������:
 // Patch* p = pi->WriteCodePatch(address,
 //  "#0: %%",
 //  "B9 %d %%", this,     // mov ecx, this  // 
 //  "BA %d %%", this->context,   // mov edx, context  // 
 //  "%c %%", func,      // call func  // 
 //  "83 F8 01 %%",      // cmp eax, 1
 //  "0F 85 #7 %%",       // jne long to label 7 (if func returns 0)
 //  "83 F8 02 %%",      // cmp eax, 2
 //  "0F 85 ~d %%", 0x445544,   // jne long to 0x445544 (if func returns 0)
 //  "EB #0 %%",       // jmp short to label 0
 //  "%m %%", address2, size,   // exec  code copy from address2
 //  "#7: FF 25 %d %.", &return_address); // jmp [&return_address]
 inline Patch* WriteCodePatch(_ptr_ address, char* format, ...)
 {
  return WriteCodePatchVA(address, format, (_dword_*)((_ptr_)&format + 4));
 }
 
 ////////////////////////////////////////////////////////////
 // ����� CreateCodePatch
 // ������� ���� ��� �� ��� � ����� WriteCodePatch,
 // �� �� ��������� ���
 // ��������e� ��������� �� ����
 inline Patch* CreateCodePatch(_ptr_ address, char* format, ...)
 {
  return CreateCodePatchVA(address, format, (_dword_*)((_ptr_)&format + 4));
 }


 ////////////////////////////////////////////////////////////
 // ����� WriteDataPatch
 // ����� �� ������ address ������������������ ����,
 // ������������ format � ...
 // (������� � ��������� DATA_ ����)
 // ���������� ��������� �� ����
 // format - ��-������ ����� ��������� ����������������� �����
 // 0123456789ABCDEF (������ ������� �������!),
 // � ��� �� ����������� ������-������� (������ �������!):
 // %b - (byte) ����� ������������ ����� �� ...
 // %w - (word) ����� ������������ ����� �� ...
 // %d - (dword) ����� ��������������� ����� �� ...
 // %m - �������� ������ �� ������ ... �������� ... (�.�. ������ 2 ��������� �� ...)
 // %% - ����� ������ � ������-��������� �� ... 
 // %o - (offset) �������� �� ������ �� ��������� �������� ������� �
 //      Complex ����,  ������������ ������ Complex ����.
 // %. - ������ �� ������ ( ��� � ����� ������ �� ����������� ���� ������ ����� % ) 
 // ����������� ������:
 // Patch* p = pi->WriteDataPatch(address,
 //  "FF FF FF %d %%", var, 
 //  "%m %%", address2, size, 
 //  "AE %.");
 inline Patch* WriteDataPatch(_ptr_ address, char* format, ...)
 {
  return WriteDataPatchVA(address, format, (_dword_*)((_ptr_)&format + 4));
 }
 
 ////////////////////////////////////////////////////////////
 // ����� CreateDataPatch
 // ������� ���� ��� �� ��� � ����� WriteDataPatch,
 // �� �� ��������� ���
 // ��������e� ��������� �� ����
 inline Patch* CreateDataPatch(_ptr_ address, char* format, ...)
 {
  return CreateDataPatchVA(address, format, (_dword_*)((_ptr_)&format + 4));
 }
 
 inline Patch* __stdcall WriteDword(_ptr_ address, const char* value)
 {
  return WriteDword(address, (int)value);
 }

};

// ����� Patcher
class Patcher
{
public:
 // �������� ������:

 ///////////////////////////////////////////////////
 // ����� CreateInstance
 // ������� ��������� ������ PatcherInstance, ������� 
 // ��������������� ��������� ��������� ����� � ���� �
 // ���������� ��������� �� ���� ���������.
 // owner - ���������� ��� ���������� PatcherInstance
 // ����� ���������� NULL, ���� ��������� � ������ owner ��� ������
 // ���� owner == NULL ��� owner == "" �� 
 // ��������� PatcherInstance ����� ������ � ������ ������ ��
 // �������� ���� ������� �������.
 virtual PatcherInstance* __stdcall CreateInstance(char* owner) = 0;
 
 ///////////////////////////////////////////////////
 // ����� GetInstance
 // ���������� ��������� �� ��������� PatcherInstance
 // � ������ owner.
 // ����� ���������� NULL � ������, ���� 
 // ��������� � ������ owner �� ���������� (�� ��� ������)
 // � �������� ��������� ����� ���������� ��� ������.
 // ������������ ��� :
 // - �������� ������� �� ��������� ���, ������������ patcher_x86.dll
 // - ��������� ������� �� ���� ������ � ����� ���������� ����,
 //   ������������� patcher_x86.dll
 virtual PatcherInstance*  __stdcall GetInstance(char* owner) = 0;
 
 ///////////////////////////////////////////////////
 // ����� GetLastPatchAt
 // ���������� NULL, ���� � ����������� ������ address �� ��� �������� �� ���� ����/���
 // ����� ���������� ��������� ���������� ����/��� � ����������� ������ address
 // ��������������� �������� �� ���� ������ � �������� ����������� 
 // ��������� ���� ����� � Patch::GetAppliedBefore
 virtual Patch* __stdcall GetLastPatchAt(_ptr_ address);
 
 ///////////////////////////////////////////////////
 // ����� UndoAllAt
 // �������� ��� �����/���� � ����������� ������ address
 // ������ ���������� 1 (��� ������������� � ����� ������� �������� ����������)
 virtual Patch* __stdcall UndoAllAt(_ptr_ address);
 
 ///////////////////////////////////////////////////
 // ����� SaveDump
 // ��������� � ���� � ������ file_name
 // - ���������� � ����� ���� ����������� PatcherInstance
 // - ���������� ���� ����������� ������/�����
 // - ������ ���� ����������� ������ � ����� � �� �������� ���������, ���������, ���������� ������������ ����������, �������������� (������� PatcherInstance)
 virtual void __stdcall SaveDump(char* file_name) = 0;
 
 ///////////////////////////////////////////////////
 // ����� SaveLog
 // ��������� � ���� � ������ file_name ��� 
 // ���� ����������� ��������� � ���� ����� 0 �������.
 // �������� ����������� ����� ������ � ���������� ����������
 // ��������� ���� patcher_x86.ini c c���������: Logging = 1
 virtual void __stdcall SaveLog(char* file_name) = 0;
 
 ///////////////////////////////////////////////////
 // ����� GetMaxPatchSize
 // ���������� patcher_x86.dll ����������� ��������� �����������
 // �� ������������ ������ �����,
 // ����� - ����� ������ � ������� ������ GetMaxPatchSize
 // (�� ������ ������ ��� 262144 ����, �.�. ������� :) )
 virtual int __stdcall GetMaxPatchSize() = 0;
 
 // �������������� ������:

 ///////////////////////////////////////////////////
 // ����� WriteComplexDataVA
 // � ������������ ���� ���������� ������ �� ��������������,
 // �������� (����) �������� ������-�������� WriteComplexString
 virtual int __stdcall WriteComplexDataVA(_ptr_ address, char* format, _dword_* args) = 0;
 
 ///////////////////////////////////////////////////
 // ����� GetOpcodeLength
 // �.�. ������������ ���� �������
 // ���������� ����� � ������ ������ �� ������ p_opcode
 // ���������� 0, ���� ����� ����������
 virtual int __stdcall GetOpcodeLength(_ptr_ p_opcode) = 0;
 
 ///////////////////////////////////////////////////
 // ����� MemCopyCode
 // �������� ��� �� ������ �� ������ src � ������ �� ������ dst
 // MemCopyCode �������� ������ ����� ���������� ������� �������� >= size. ������ �����������!
 // ���������� ������ �������������� ����.
 // ���������� ��������� �� �������� ����������� ������ ���,
 // ��� ��������� �������� ������ E8 (call), E9 (jmp long), 0F80 - 0F8F (j** long)
 // c ������������� ���������� �� ������ � ��� ������, ���� ���������� 
 // ���������� �� ������� ����������� ������.
 // 
 virtual int __stdcall MemCopyCode(_ptr_ dst, _ptr_ src, _dword_ size) = 0;
 
 ///////////////////////////////////////////////////
 // ����� GetFirstPatchAt
 // ���������� NULL, ���� � ����������� ������ address �� ��� �������� �� ���� ����/���
 // ����� ���������� ������ ���������� ����/��� � ����������� ������ address
 // ��������������� �������� �� ���� ������ � �������� ����������� 
 // ��������� ���� ����� � Patch::GetAppliedAfter
 virtual Patch* __stdcall GetFirstPatchAt(_ptr_ address);
 
 ///////////////////////////////////////////////////
 // ����� MemCopyCodeEx
 // �������� ��� �� ������ �� ������ src � ������ �� ������ dst
 // ���������� ������ �������������� ����.
 // ���������� �� MemCopyCode ���,
 // ��� ��������� �������� ������ EB (jmp short), 70 - 7F (j** short)
 // c ������������� ���������� �� ������ � ��� ������, ���� ���������� 
 // ���������� �� ������� ����������� ������ (� ���� ������ ��� ���������� ��
 // ��������������� E9 (jmp long), 0F80 - 0F8F (j** long) ������.
 // ��������! ��-�� ����� ������ �������������� ���� ����� ��������� ����������� 
 // ������ �����������.
 virtual int __stdcall MemCopyCodeEx(_ptr_ dst, _ptr_ src, _dword_ size) = 0;
 
 
 // ver 2.3
 // ����� VarInit
 // �������������� "����������" c ������ name � ������������� �������� "����������" ������ value
 // ���� "����������" � ����� ������ ��� ����������, �� ������ ������������� �� �������� ������ value
 // ���������� ��������� �� "����������" � ������ ������ � NULL � ��������� ������
 virtual Variable* __stdcall VarInit(char* name, _dword_ value) = 0;
 // ����� VarFind
 // ���������� ��������� �� "����������" � ������ name, ���� ����� ���� �����������������
 // ���� ���, ���������� NULL
 virtual Variable* __stdcall VarFind(char* name) = 0;


 // ver 2.6
 // ����� PreCreateInstance
 // ������� ������������� ��������� PatcherInstance � ��������� ������.
 // PatcherInstance ��������� ����� ������� �� ����� ��������� �����.
 // ���� ������������� ��������� ������������ ��� ���������� ������� PatcherInstance::BlockAt � PatcherInstance::BlockAllExceptVA
 // ����� ����� ���� ������������� ������ �� ���� ��� ������ PatcherInstance ����� ���������� ������ � ������� CreateInstance
 virtual PatcherInstance* __stdcall PreCreateInstance(char* name) = 0;


 // ver 4.1
 // �������� � ����������...
 virtual int __stdcall WriteAsmCodeVA(_ptr_ address, _dword_* args) = 0;
 virtual _ptr_ __stdcall CreateCodeBlockVA(_dword_* args) = 0;

 
 // ����� VarGetValue ���������� �������� "����������" c ������ name
 // ���� "����������" � ����� ������ �� ���� �����������������, ���������� default_value
 template<typename ValueType>
 inline ValueType VarGetValue(char* name, ValueType default_value)
 {
	 if (sizeof(ValueType) > 4) return default_value;
	 Variable* v = VarFind(name);
	 if (v == NULL) return default_value;
	 return (ValueType)v->GetValue();
 }

 // ����� VarValue ���������� ������ �� �������� "����������" c ������ name
 // ���� "����������" � ����� ������ �� ���� �����������������, �������������� �� � ������������� �������� ������ 0
 // ��������, ��������� � �������� ���������� �� ������ �����������������
 template<typename ValueType>
 inline ValueType& VarValue(char* name)
 {
	 if (sizeof(ValueType) > 4) __asm{__asm int 3};
	 
	 Variable* v = VarFind(name);
	 if (v == NULL) v = VarInit(name, 0);
	 
	 if (v == NULL) __asm{__asm int 3};
	 
	 return (ValueType&)*v->GetPValue();
 }



 ////////////////////////////////////////////////////////////////////
 // ����� WriteComplexData
 // �������� ����� ������� �����������  
 // ������ WriteComplexDataVA
 // ���� ����� ��������� ����� � �� � ����������, �.�. ��� ��� 
 // ���������� � �� � �����
 // ���������� ������ ����� ��� �� ��� � � PatcherInstance::WriteCodePatch
 // (��. �������� ����� ������)
 // �� ���� ����� ����� �� ������ address, ������������������ ����,
 // ������������ ����������� format � ...,
 // ��! �� ������� ��������� ������ Patch, �� ����� ����������� (�.�. �� �������� �������� ������, �������� ������ � ������ �� ������� ���� � �.�.)
 // ��������!
 // ����������� ���� ����� ������ ��� ������������� �������� ������
 // ����, �.�. ������ ���� ������� ������ � ���� ������, 
 // � � ��� �������������� ��������� ������ � �������
 // PatcherInstance::WriteCodePatch
 //
 inline _ptr_ WriteComplexData(_ptr_ address, char* format, ...)
 {
  return WriteComplexDataVA(address, format, (_dword_*)((_ptr_)&format + 4));
 }



inline HiHook* GetFirstHiHookAt(_ptr_ address)
{
	Patch* p = GetFirstPatchAt(address);
	while (true)
	{
		if (p == 0) return 0;
		if (p->GetType() == HIHOOK_) return (HiHook*)p;
		p = p->GetAppliedAfter();
	}
}

inline HiHook* GetLastHiHookAt(_ptr_ address)
{
	Patch* p = GetLastPatchAt(address);
	while (true)
	{
		if (p == 0) return 0;
		if (p->GetType() == HIHOOK_) return (HiHook*)p;
		p = p->GetAppliedBefore();
	}
}


};





// ��������������� ������������ ������ �������� � �������
#pragma pack(pop)

//////////////////////////////////////////////////////////////////

//������� GetPatcher
//��������� ���������� �, � ������� ������ ������������ �������������� 
//������� _GetPatcherX86@0, ���������� ��������� �� ������ Patcher,
//����������� �������� �������� ���� ���������� ���������� patcher_x86.dll
//���������� NULL ��� �������
//������� �������� 1 ���, ��� �������� �� �� �����������
#include <windows.h>
inline Patcher* GetPatcher()
{
static int calls_count = 0;
 if (calls_count > 0) return NULL;
 calls_count++;
 HMODULE pl = LoadLibraryA("patcher_x86.dll");
 if (pl)
 {
  FARPROC f = GetProcAddress(pl, "_GetPatcherX86@0");
  if (f) return CALL_0(Patcher*, __stdcall, f);
 }
 return NULL;
}

#ifndef _LHF_
// * predefined macro for LoHook functions
// * LoHook *h and HookContext *c are pre-defined
// * e.g. _LHF_(MyFunction) {}
#define _LHF_(func) int __stdcall func(LoHook *h, HookContext *c)
#endif
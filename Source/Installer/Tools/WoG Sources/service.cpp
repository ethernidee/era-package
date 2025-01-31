#include <windows.h>
#include <direct.h>
#include <stdio.h>

#include "structs.h"
#include "common.h"
#include "txtfile.h"
//#include "classes.h"
#include "herospec.h"
#include "service.h"
#include "b1.h"
#define __FILENUM__ 3
//#include"WinNT.h"
#define SILENCE 4

int    TerminateFlag=0;
static TxtFile CustomTxt;
static int  YesCustomCMD;
static char CustomTxtName[1024];
char StartUpFolder[_MAX_PATH];

static Dword RetVal;
//HINSTANCE LoadLibrary(
//  LPCTSTR lpLibFileName   // address of filename of executable module
//);
//If the function succeeds, the return value is a handle to the module.
//If the function fails, the return value is NULL.
//To get extended error information, call GetLastError. 
Dword Service_LoadLibrary(char *DLLName)
{
  __asm{
    mov  eax,DLLName
    push eax
    mov  eax,0x63A1FC
    mov  eax,[eax]
    call eax
    mov  DDummy,eax
  }
  return DDummy;
}

//FARPROC GetProcAddress(
//  HMODULE hModule,    // handle to DLL module
//  LPCSTR lpProcName   // name of function
//);
//If the function succeeds, the return value is the address of the DLL's exported function.
//If the function fails, the return value is NULL. 
//To get extended error information, call GetLastError.
Dword Service_GetProcAddress(Dword Handle,char *FunName)
{
  __asm{
    mov  eax,Handle
    mov  ecx,FunName
    push ecx
    push eax
    mov  eax,0x63A22C
    mov  eax,[eax]
    call eax
    mov  DDummy,eax
  }
  return DDummy;
}

//BOOL FreeLibrary(
//  HMODULE hLibModule   // handle to loaded library module
//);
//If the function succeeds, the return value is nonzero.
//If the function fails, the return value is zero.
//To get extended error information, call GetLastError.
//------ kernel32
Dword po_FreeLibrary;
int Service_FreeLibrary(Dword Handle)
{
  #include "templ.h"
  __asm{
    mov  eax,Handle
    push eax
    mov  eax,po_FreeLibrary
    mov  eax,[eax]
    call eax
    mov  IDummy,eax
  }
  RETURN(IDummy)
}

//LONG GetWindowLong(
//  HWND hWnd,  // handle of window
//  int nIndex  // offset of value to retrieve
//);
//If the function succeeds, the return value is the requested 32-bit value.
//If the function fails, the return value is zero. To get extended error information, callGetLastError.

//HWND GetForegroundWindow(VOID)
//The return value is a handle to the foreground window.
//Dword WoGForegroundWindow=0;
int Service_GetForegroundWindow(void){
  #include "templ.h"
  __asm{
    mov   eax,0x699650
    mov   eax,[eax]
    mov   DDummy,eax
  }
  RETURN(DDummy)
//  return WoGForegroundWindow;
}
/*
static void Service_GetForegroundWindowExt(void)
{
  STARTN(__FILENUM__*1000000+__LINE__)
  __asm{
    mov  eax,0x63A2F8
    mov  eax,[eax]
    call eax
    mov  WoGForegroundWindow,eax
  }
  RETURNV
}
*/
//The timeGetTime function retrieves the system time, in milliseconds.
//The system time is the time elapsed since Windows was started.
//DWORD timeGetTime(VOID);
Dword Service_timeGetTime(void)
{
  #include "templ.h"
  __asm{
    mov  eax,0x63A354
    mov  eax,[eax]
    call eax
    mov  DDummy,eax
  }
  RETURN(DDummy)
}

//int DialogBox(
//  HINSTANCE hInstance,  // handle to application instance
//  LPCTSTR lpTemplate,   // identifies dialog box template
//  HWND hWndParent,      // handle to owner window
//  DLGPROC lpDialogFunc  // pointer to dialog box procedure
//);
//If the function succeeds, the return value is the nResult parameter in the call to the EndDialog function used to terminate the dialog box.
//If the function fails, the return value is �1. To get extended error information, callGetLastError.
Dword po_DialogBox;
int Service_DialogBox(int hInstance,void *lpTemplate,int hWndParent,void (*lpDialogFunc))
{
  #include "templ.h"
  __asm{
    pusha
    mov  eax,hInstance
    mov  ebx,lpTemplate
    mov  ecx,hWndParent
    mov  edx,lpDialogFunc
    push 0
    push edx
    push ecx
    push ebx
    push eax
    mov  eax,0x63A2BC
    mov  eax,[eax]
    call eax
    mov  RetVal,eax
    popa
  }
  RETURN(RetVal)
}

//DWORD GetFileAttributes(
//  LPCTSTR lpFileName   // pointer to the name of a file or directory
//);
int Service_GetFileAttributes(char *FileName)
{
  #include "templ.h"
  __asm{
    mov  eax,FileName
    push eax
    mov  eax,0x63A0C0
    mov  eax,[eax]
    call eax
    mov  IDummy,eax
  }
  RETURN(IDummy)
}
/////////////////////////////////////////////
static Dword po_SetErrMode=0;
static Dword po_SetExcFilt;
static Dword po_GetCurProc;
static Dword po_ReadProcMem;
int Service_SetExcFilter(Dword NewHandler)
{
  #include "templ.h"
  __asm{
    mov   eax,NewHandler
    push  eax
    mov   eax,po_SetExcFilt
//    mov   eax,[eax]
    call  eax
  }
  RETURN(0)
}
Dword Service_GetCurProc(void)
{
  #include "templ.h"
  __asm{
    mov   eax,po_GetCurProc
    call  eax
    mov   DDummy,eax
  }
  RETURN(DDummy)
}
char Service_ReadProcMem(Dword /*Handle*/,void *Addr,Byte *Buf,int ZSize,Dword *SizeRead)
{
  HANDLE Handle=GetCurrentProcess();
  IDummy=ReadProcessMemory(Handle,Addr,Buf,ZSize,SizeRead);
/*
  __asm{
    push  Handle
    push  Addr
    push  Buf
    push  ZSize
    push  SizeRead
    mov   eax,po_ReadProcMem
    call  eax
    mov   CDummy,al  
  }
*/
  if(IDummy==0){ // cannot read
    *SizeRead=0;
    return 0;
  }
//  for(int i=0;i<Size;i++){ Buf[i]=((Byte *)Addr)[i]; }
//  *SizeRead=Size;
  return 1;
}
//////////////////////////
#define SIZE_OF_80387_REGISTERS      80
/*
typedef struct _FLOATING_SAVE_AREA {
    Dword   ControlWord;
    Dword   StatusWord;
    Dword   TagWord;
    Dword   ErrorOffset;
    Dword   ErrorSelector;
    Dword   DataOffset;
    Dword   DataSelector;
    Byte    RegisterArea[SIZE_OF_80387_REGISTERS];
    Dword   Cr0NpxState;
} FLOATING_SAVE_AREA;

typedef struct _CONTEXT {
    // The flags values within this flag control the contents of a CONTEXT record.
    // If the context record is used as an input parameter, then
    // for each portion of the context record controlled by a flag
    // whose value is set, it is assumed that that portion of the
    // context record contains valid context. If the context record
    // is being used to modify a threads context, then only that
    // portion of the threads context will be modified.
    // If the context record is used as an IN OUT parameter to capture
    // the context of a thread, then only those portions of the thread's
    // context corresponding to set flags will be returned.
    // The context record is never used as an OUT only parameter.
    Dword ContextFlags;
    // This section is specified/returned if CONTEXT_DEBUG_REGISTERS is
    // set in ContextFlags.  Note that CONTEXT_DEBUG_REGISTERS is NOT
    // included in CONTEXT_FULL.
    Dword   Dr0;
    Dword   Dr1;
    Dword   Dr2;
    Dword   Dr3;
    Dword   Dr6;
    Dword   Dr7;
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_FLOATING_POINT.
    FLOATING_SAVE_AREA FloatSave;
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_SEGMENTS.
    Dword   SegGs;
    Dword   SegFs;
    Dword   SegEs;
    Dword   SegDs;
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_INTEGER.
    Dword   Edi;
    Dword   Esi;
    Dword   Ebx;
    Dword   Edx;
    Dword   Ecx;
    Dword   Eax;
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_CONTROL.
    Dword   Ebp;
    Dword   Eip;
    Dword   SegCs;              // MUST BE SANITIZED
    Dword   EFlags;             // MUST BE SANITIZED
    Dword   Esp;
    Dword   SegSs;
} CONTEXT;

typedef struct _EXCEPTION_RECORD { // exr
    Dword ExceptionCode;
    Dword ExceptionFlags;
    struct _EXCEPTION_RECORD *ExceptionRecord;
    void *ExceptionAddress;
    Dword NumberParameters;
    Dword ExceptionInformation[15];
} EXCEPTION_RECORD;
typedef struct _EXCEPTION_POINTERS { // exp
    EXCEPTION_RECORD *ExceptionRecord;
    CONTEXT          *ContextRecord;
} EXCEPTION_POINTERS;
*/
PEr GEr;
void PEr::Del(void){
  __asm pusha
    for(int i=49;i>=0;i--){ if(GEr.Descr[i]!=0){ GEr.Descr[i]=0; GEr.Text[i]=0; goto _done; }}
_done:
  __asm popa
}
_ZPrintf_ PEr::Frmt;
char PEr::GlbBuf[2][30000];

//EXCEPTION_CONTINUE_EXECUTION (�1)
//EXCEPTION_CONTINUE_SEARCH (0)
//EXCEPTION_EXECUTE_HANDLER (1)
int CommonDialog(char *Mess);
static _ZPrintf_ Frmt;
static char Buf[30000];
static Byte Mem[1000];
static char *ParseContext(int par,CONTEXT *Cnt){
/*
  Zsprintf2(&Frmt,"\n\nRegister Context:\n\n",0,0);
  StrCopy(Buf,29999,Frmt.Str);
  Zsprintf2(&Frmt,"%s\n\nEAX = {0x%08X}, ",(Dword)Buf,Cnt->Eax); StrCopy(Buf,29999,Frmt.Str);
  Zsprintf2(&Frmt,"%s\nEBX = {0x%08X}, ",(Dword)Buf,Cnt->Ebx);   StrCopy(Buf,29999,Frmt.Str);
  Zsprintf2(&Frmt,"%s\nECX = {0x%08X}, ",(Dword)Buf,Cnt->Ecx);   StrCopy(Buf,29999,Frmt.Str);
  Zsprintf2(&Frmt,"%s\nEDX = {0x%08X}, ",(Dword)Buf,Cnt->Edx);   StrCopy(Buf,29999,Frmt.Str);
  Zsprintf2(&Frmt,"%s\nESI = {0x%08X}, ",(Dword)Buf,Cnt->Esi);   StrCopy(Buf,29999,Frmt.Str);
  Zsprintf2(&Frmt,"%s\nEDI = {0x%08X}, ",(Dword)Buf,Cnt->Edi);   StrCopy(Buf,29999,Frmt.Str);
  Zsprintf2(&Frmt,"%s\nEBP = {0x%08X}, ",(Dword)Buf,Cnt->Ebp);   StrCopy(Buf,29999,Frmt.Str);
  Zsprintf2(&Frmt,"%s\nESP = {0x%08X}, ",(Dword)Buf,Cnt->Esp);   StrCopy(Buf,29999,Frmt.Str);
  Zsprintf2(&Frmt,"%s\nEIP = {0x%08X}, ",(Dword)Buf,Cnt->Eip);   StrCopy(Buf,29999,Frmt.Str);
*/
  sprintf(Buf,"\n\nRegister Context:\n\n"
          "\nEAX = 0x%08X\nEBX = 0x%08X\nECX = 0x%08X\nEDX = 0x%08X"
          "\nESI = 0x%08X\nEDI = 0x%08X\nEBP = 0x%08X\nESP = 0x%08X",
          Cnt->Eax,Cnt->Ebx,Cnt->Ecx,Cnt->Edx,Cnt->Esi,Cnt->Edi,Cnt->Ebp,Cnt->Esp);
  if(par==1) return Buf;
  if(Cnt->Esp!=0 && Cnt->Esp!=0xFFFFFFFF){
    Dword sz=0;
    if(Service_ReadProcMem(Service_GetCurProc(),(void *)Cnt->Esp,Mem,1000,&sz)){ // read
//      Zsprintf2(&Frmt,"%s\n\nStack Frame:\n\n",(Dword)Buf,0); StrCopy(Buf,29999,Frmt.Str);
      sprintf(&Buf[StrLen(Buf)],"\n\nStack Frame:\n\n");
      for(Dword i=0;i<sz/4;i++){
        int s=StrLen(Buf);
        sprintf(&Buf[s],"0x%08X : 0x%08X\n",Cnt->Esp+i*4,*(int *)&Mem[i*4]);
/*
        int s=StrLen(Buf);
        Itoa(Cnt->Esp+i*4,&Buf[s],16);
        s=StrLen(Buf);
        Buf[s]=':'; Buf[s+1]=0;
        s=StrLen(Buf);
        Itoa(*(int *)&Mem[i*4],&Buf[s],16);
        s=StrLen(Buf);
        Buf[s]='\n'; Buf[s+1]=0;
*/
      }
    }
  }
  return Buf;
}
long MyExcHandler(EXCEPTION_POINTERS *Reason)
{
  char fl=0,*po;
  Dword Par=0;
  switch(Reason->ExceptionRecord->ExceptionCode){
    case 0xC0000005L:
      if(Reason->ExceptionRecord->ExceptionInformation[0]){ // writing
        po="Access Violation. Attempt to {write} the inaccessible data at";
      }else{ // reading
        po="Access Violation. Attempt to {read} the inaccessible data at";
      }
      Par=Reason->ExceptionRecord->ExceptionInformation[1];
//      if(Par==1) goto _Term;
      fl=1;
      break;
    case 0xC000008CL: //EXCEPTION_ARRAY_BOUNDS_EXCEEDED
      po="Attempt to access an array element that is out of bounds.";
      break;
    case 0x80000003L: //EXCEPTION_BREAKPOINT
      po="A breakpoint was encountered.";
      break;
    case 0x80000002L: //EXCEPTION_DATATYPE_MISALIGNMENT
      po="Data access misalignment.";
      break;
    case 0xC000008DL: //EXCEPTION_FLT_DENORMAL_OPERAND
      po="One of the operands in a floating-point operation is denormal.";
      break;
    case 0xC000008EL: //EXCEPTION_FLT_DIVIDE_BY_ZERO
      po="Attempt to divide a floating-point value by a floating-point divisor of zero.";
      break;
    case 0xC000008FL: //EXCEPTION_FLT_INEXACT_RESULT
      po="The result of a floating-point operation cannot be represented exactly as a decimal fraction.";
      break;
    case 0xC0000090L: //EXCEPTION_FLT_INVALID_OPERATION
      po="Unhandled floating-point exception.";
      break;
    case 0xC0000091L: //EXCEPTION_FLT_OVERFLOW
      po="The exponent of a floating-point operation is greater than the magnitude allowed by the corresponding type.";
      break;
    case 0xC0000092L: //EXCEPTION_FLT_STACK_CHECK
      po="The stack overflowed or underflowed as the result of a floating-point operation.";
      break;
    case 0xC0000093L: //EXCEPTION_FLT_UNDERFLOW
      po="The exponent of a floating-point operation is less than the magnitude allowed by the corresponding type.";
      break;
    case 0xC000001DL: //EXCEPTION_ILLEGAL_INSTRUCTION
      po="Attempt to execute an invalid instruction.";
      break;
    case 0xC0000006L: //EXCEPTION_IN_PAGE_ERROR
      po="Attempt to access a page that was not present, and the system was unable to load the page.";
      break;
    case 0xC0000094L: //EXCEPTION_INT_DIVIDE_BY_ZERO
      po="Attempt to divide an integer value by an integer divisor of zero.";
      break;
    case 0xC0000095L: //EXCEPTION_INT_OVERFLOW
      po="Arithmetic overflow.";
      break;
//    case 0xC0000026L: //EXCEPTION_INVALID_DISPOSITION
//      po="";
//      break;
//    case 0xC0000025L: //EXCEPTION_NONCONTINUABLE_EXCEPTION
//      po="";
//      break;
    case 0xC0000096L: //EXCEPTION_PRIV_INSTRUCTION
      po="Attempt to execute a privilaged instruction.";
      break;
//    case 0x80000004L: //EXCEPTION_SINGLE_STEP
//      po="";
//      break;
    case 0xC00000FDL: //EXCEPTION_STACK_OVERFLOW
      po="The thread used up its stack.";
      break;
    default:
      po="Unhandled Exception.";
  }
  GEr.Show(po,Reason->ExceptionRecord->ExceptionAddress,fl,Par,ParseContext(Par,Reason->ContextRecord));
//  GEr.Clear();
//  po="Program will be terminated.";
//_Term:
  __asm{
    mov   ecx,0
    mov   eax,0x4F3D20
    call  eax
  }
//  Service_SetExcFilter((Dword)0);
  return 1;
}
//////////////////////////////////////////////
Dword HKernel32,HUser32;

int StartDLLService(void)
{
  #include "templ.h"
  Dword hdll,pfun;
  hdll=Service_LoadLibrary("kernel32.dll"); if(hdll==0) RETURN(-1)
  HKernel32=hdll;
  pfun=Service_GetProcAddress(hdll,"FreeLibrary"); if(pfun==0) RETURN(-1)
  po_FreeLibrary=pfun;
  pfun=Service_GetProcAddress(hdll,"SetUnhandledExceptionFilter"); if(pfun==0) RETURN(-1)
  po_SetExcFilt=pfun;
  pfun=Service_GetProcAddress(hdll,"GetCurrentProcess"); if(pfun==0) RETURN(-1)
  po_GetCurProc=pfun;
  pfun=Service_GetProcAddress(hdll,"ReadProcessMemory"); if(pfun==0) RETURN(-1)
  po_ReadProcMem=pfun;
  pfun=Service_GetProcAddress(hdll,"SetErrorMode"); if(pfun==0) RETURN(-1)
  po_SetErrMode=pfun;
  Service_SetExcFilter((Dword)MyExcHandler);
/*
  hdll=Service_LoadLibrary("user32.dll"); if(hdll==0) return -1;
  HUser32=hdll;
  pfun=Service_GetProcAddress(hdll,"DialogBox"); if(pfun==0) return -1;
  po_DialogBox=pfun;
*/
  RETURN(0)
}

int StopDLLService(void)
{
  #include "templ.h"
  if(Service_FreeLibrary(HKernel32)==0) RETURN(-1)
//  if(Service_FreeLibrary(HUser32)==0) return -1;
  RETURN(0)
}

///////////////////////////////////////////////////////

//static int (*ChooseCastle_c)(int ParentWindow,char *Message,char *ResDir,
//     char *Button,char *Clear,char *Item1,char *Item2,char *Item3,char *Item4,
//     char *Item5,char *Item6,char *Item7,char *Item8,char *Item9,int Playsnd);
static int (*ChooseCastle_c)(int ParentWindow,char *ResDir,int Playsnd);
//static int (*CommonDialog_c)(int ParentWindow,char *Message,char *ResDir,
//     char *Button,char *Clear,int Playsnd);
static int (*CommonDialog_c)(int ParentWindow,char *Message,char *ResDir,int Playsnd);
//static int (*CustomReq_c)(int ParentWindow,_Sphinx *Sphinx,char *ResDir,int Playsnd);
static int (*CustomReq1_c)(int ParentWindow,_Sphinx1 *Sphinx,char *ResDir,int Playsnd);
static void (*CustomPic_c)(int ParentWindow,_Intro *Intro, char *ResDir,int Playsnd);
static int (*Curse_c)(int ParentWindow,_CurseShow *CurseShow,char *ResDir,int Playsnd);
static void (*MultiCheck_c)(int ParentWindow,_CheckBoxes *StartUpSetUp,char *ResDir,int Playsnd);
static int (*Diplom_c)(int ParentWindow,_Diplomacy *Diplomacy,char*,int);
static int (*NPCInfo_c)(int ParentWindow,_DlgNPC *DlgNPC,char *,int);
static int (*Radio2_c)(int ParentWindow,_PopUpRadioButtons *PopUpRadioButtons,char *,int);
static void (*WoGSetup_c)(int ParentWindow,_DlgSetup *,char *,int);
static int (*SaveSetupState_c)(char *Name,void *Buf,int Len);
static int (*LoadSetupState_c)(char *Name,void *Buf,int Len);
// 3.58
static int (*ChooseFile_c)(int ParentWindow,_ChooseFile* ChooseFile,char *ResDir,int Playsnd);
static int (*ChooseIcon_c)(int ParentWindow,_IconList *,char *ResDir,int Playsnd);
static int (*WoGMessage_c)(int ParentWindow,char **,char *ResDir,int Playsnd);
static int (*ReadIntFromINI_c)(char *FileName,char *SectionName,char *ParameterName,int *Value,int DefValue);
static int (*ReadStrFromINI_c)(char *FileName,char *SectionName,char *ParameterName,char *Value,int ValueLen,char * DefValue);
static int (*WriteIntToINI_c)(char *FileName,char *SectionName,char *ParameterName,int Value);
static int (*WriteStrToINI_c)(char *FileName,char *SectionName,char *ParameterName,char *Value);
static int (*ShowUpgradeDlg_c)(int ParentWindow,_MonsterInfo *,char *ResDir,int Playsnd);
static int (*CommonPicDlg_c)(int ParentWindow,char *Message,char *Pic,char *ResDir,int Playsnd);
static void (*RegGlobalTerminate_c)(int *TermunateFlag);
///////////////////////////////////////////////////////
static void BeforeDialog(void)
{
  #include "templ.h"
  __asm{
  // �������� ���������� ����
    mov  ecx,0x6992B0
    mov  ecx,[ecx]
//  push 1
//  mov  eax,0x50D7B0
//  call eax
    mov  eax,0x50D740
    call eax
// ������� ������� ����  
    push 1
    mov  eax,0x63A314
    mov  eax,[eax]
    call eax
  }
  RETURNV
}

void AfterDialog(void)
{  
  #include "templ.h"
  __asm{
  // �������� ������� ����
    push 0
    mov  eax,0x63A314
    mov  eax,[eax]
    call eax
  // ������� ���������� ����
    mov  ecx,0x6992B0
    mov  ecx,[ecx]
    push 0
    mov  eax,0x50D7B0
    call eax
  // ����������� ������  
//    mov   eax,0x4F8640
//    call  eax
    mov   ecx,0x699530
    mov   ecx,[ecx]
    mov   eax,0x4EC640
    call  eax
  }
  RETURNV
}


int CommonDialog(char *Mess)
{
  #include "templ.h"
//  return CommonDialog_c(Service_GetForegroundWindow(),
//    Mess,".\\Data\\ZVS\\LIB1.RES","Ok","Cansel",1);
  int ret=CommonDialog_c(Service_GetForegroundWindow(),Mess,".\\Data\\ZVS\\LIB1.RES",EffectVolume()>SILENCE);
  SetFocus((HWND)Service_GetForegroundWindow());
  RETURN(ret)
}

int ChooseCastle(void)
{
  #include "templ.h"
  int ret;
  BeforeDialog();
//  ret=ChooseCastle_c(Service_GetForegroundWindow(),
//    "Choose a Town type to restore.",
//    ".\\Data\\ZVS\\LIB1.RES","Ok","Cansel",
//    "Castle","Rampart","Tower","Inferno","Necropolis",
//    "Dungeon","Stronghold","Fortress","Conflux",1);
  ret=ChooseCastle_c(Service_GetForegroundWindow(),
    ".\\Data\\ZVS\\LIB1.RES",EffectVolume()>SILENCE);
  SetFocus((HWND)Service_GetForegroundWindow());
  AfterDialog();
  RETURN(ret)
}
/////////////////////////////////////
///  ���������������� ���������
static char LCT_s1[]="..\\MAPS\\";
static char *Types[]={" ","MESSAGE","REQUEST","HERO",0};
static char *SubTypes[]={" ","PIC","EXT",0};
static char *Apply[]={" ","APPLY",0};
static char **AllNames[]={
  Types,SubTypes,Apply,0
};
// Message: Std,Extended,Picture
// Request: Std,Extended
// Hero: Picture
// Location
// Timer
// Instruction
// Command
/*
  Comment 
************** Request / Message
  Type
  SubType
  Item on the Map
  Location X / Number
  Location Y
  Location L
  Header
  Message 1
  Message 2
  Message 3
  Message 4
  Picture 1
  Picture 2
  Picture 3
  Picture 4
  Button 1
  Button 2
  Button 3
  Button 4
  Action Type
  Action SubType
  Action Number
*************** Actions
  Type
  SubType
  Number
  ...
*/
#define CUSTOMDATANUM 1000
static struct _CustomData1_{
  int   Type; // 0 - �� ������
  int   SType;
  int   Num;
  char  HasCansel;
  char _u[3];
//  int   x,y,l;
//  int   AType; // ��������
//  int   ASType;
//  int   ANum;
  int   Number[4];
  char *Text[4];
  char *Pic[4];
  char *Hint[4];
  char *Button[4];
  char *HintButton[4];
  
} CustomData[CUSTOMDATANUM];
/*
static struct _CDChar_{
  TxtFile *CD_File;
  char     CD_Name[128];
} CDChar[1000];

int FindCDChar(char *filename)
{
  int i;
  for(i=0;i<1000;i++){
    if(CDChar[i].CD_File==0) continue;
    if(StrCmp(CDChar[i].CD_Name,filename)) return i;
  }
  return -1;
}

void AddCDChar(char *filename,_CustomData_ *po)
{
  int i;
  for(i=0;i<1000;i++){
    if(CDChar[i].CD_Str!=0) continue;
    StrCopy(CDChar[i].CD_Name,127,filename);
    CDChar[i].CD_Str=po;
  }
  Error();
}
*/
int FindFreeCData(void)
{
  #include "templ.h"
  int i;
  for(i=0;i<CUSTOMDATANUM;i++){
    if(CustomData[i].Type==0) RETURN(i)
  }
  RETURN(-1)
}

int FindCData(int Num)
{
  #include "templ.h"
  int i;
  for(i=0;i<CUSTOMDATANUM;i++){
    if(CustomData[i].Type==0) continue;
    if(CustomData[i].Num==Num) RETURN(i)
  }
  RETURN(-1)
}

int FindItem(char ***File,int Section,char *Item)
{
  #include "templ.h"
  int   i;
  char *str;
  
  for(i=0;;i++){
    str=File[Section][i];
    if(str==0) RETURN(-1) // �� �����
    if(StrCmp(str,Item)){ // �����
      RETURN(i)
    }
  }
}

char *HasText(char *str)
{
  #include "templ.h"
  int  i;
  char c;

  if(str==0) RETURN(0)
  for(i=0;;i++){
    c=str[i];
    if(c==0) RETURN(0)
    if(c==' ') continue;
    if(c==13) continue;
    if(c==10) continue;
    if(c==9) continue;
    RETURN(str)
  }
}

int LoadCustomTxt(int NEWload,int Apply)
{
  #include "templ.h"
  int   i,j,Ct,Cst,Ind,Num,App;
  char *MapName;
  _CustomData1_ *CD;
  char  TxtName[1024];
  char  Item[128];
  
  if(NEWload){ 
    YesCustomCMD=0;
  }else{
    if(YesCustomCMD==0) RETURN(1)
  }
//asm int 3
  for(i=0;i<HERNUM;i++){
    HeroSpecCus[i].Used=0; // �������
    for(j=0;j<24;j++){
      HeroSpecCus[i].HPSName[j]=0;
      HeroSpecCus[i].HPLName[j]=0;
    }
    HeroSpecCus[i].HPSLoaded=0;
    HeroSpecCus[i].HPLLoaded=0;
  }  
  for(i=0;i<CUSTOMDATANUM;i++) CustomData[i].Type=0;
  // �������� �� WoG
  __asm{
    mov  eax,BASE
    mov  eax,[eax]
    add  eax,0x1F86C
    mov  eax,[eax]
    mov  DDummy,eax
  }
  if(DDummy!=SOGMAPTYPE) RETURN(1)
  if(NEWload){
     __asm{
      mov   eax,BASE
      mov   eax,[eax]
      add   eax,0x1F6D9
      mov   MapName,eax
    }
    StrCanc(TxtName,1023,LCT_s1,MapName);
    i=StrLen(TxtName);
    for(;i>0;i--) if(TxtName[i]=='.') break;
    i++; TxtName[i++]='C'; TxtName[i++]='M'; TxtName[i]='D';
    if(LoadFile16k(&TxtName[3],"rb")==0) RETURN(1) // �� ����� ��������� TXT - ���� ���
//    if(Apply) Message("Custom Settings found",1);
/*
  CDChInd=FindCDChar(MapName)
  if(CDChInd!=-1){ // �����!
  }
*/  
    if(CustomTxt.fl!=0) UnloadTXT(&CustomTxt);
    if(LoadTXT(TxtName,&CustomTxt)){ 
      if(WoGType){ Message("��������� ��������� ���������������� ���������.",1); }
      else{ Message("Cannot load Custom Settings.",1); }
      RETURN(1) // ���-�� �� ���
    }
    YesCustomCMD=1;
    for(i=0;i<1024;i++) CustomTxtName[i]=TxtName[i];
  }else{
    for(i=0;i<1024;i++) TxtName[i]=CustomTxtName[i];
    YesCustomCMD=0;
    if(LoadTXT(TxtName,&CustomTxt)){
      if(WoGType){ Message("��������� ��������� ���������������� ���������.",1); }
      else{ Message("Cannot load Custom Settings.",1); }
      RETURN(1) // ���-�� �� ���
    }
    YesCustomCMD=1;
  }
  // ���� �������
  for(i=1;i<CustomTxt.sn;i++){
    StrCopy(Item,128,ITxt(i,1,&CustomTxt));
    ToUpper(Item); CutWord(Item);
    Ct=FindItem(AllNames,0,Item);
    if(Ct==-1) continue; // �� ����� - ����������
    Ind=FindFreeCData();
    if(Ind==-1){
      Message("Too many custom defined items.",1);
      RETURN(0)
    }
    CD=&CustomData[Ind];
    StrCopy(Item,128,ITxt(i,2,&CustomTxt));
    ToUpper(Item); CutWord(Item);
    Cst=FindItem(AllNames,1,Item);
    Num=a2i(ITxt(i,3,&CustomTxt));
    StrCopy(Item,128,ITxt(i,4,&CustomTxt));
    App=FindItem(AllNames,2,Item);
    CD->SType=Cst;
    CD->Num=Num;
    switch(Ct){ // ��� �������
      case 1: // Message
      case 2: // Request
        CD->Type=Ct;
        switch(Cst){
          case 2: // EXT
            CD->Text[0]=ITxt(i,5,&CustomTxt);
            CD->Text[1]=HasText(ITxt(i,6,&CustomTxt));
            CD->Text[2]=HasText(ITxt(i,7,&CustomTxt));
//            CD->Text[3]=ITxt(i,7,&CustomTxt);
            CD->Pic[0]=HasText(ITxt(i,8,&CustomTxt));
            CD->Pic[1]=HasText(ITxt(i,9,&CustomTxt));
            CD->Pic[2]=HasText(ITxt(i,10,&CustomTxt));
            CD->Pic[3]=HasText(ITxt(i,11,&CustomTxt));
            CD->Hint[0]=HasText(ITxt(i,12,&CustomTxt));
            CD->Hint[1]=HasText(ITxt(i,13,&CustomTxt));
            CD->Hint[2]=HasText(ITxt(i,14,&CustomTxt));
            CD->Hint[3]=HasText(ITxt(i,15,&CustomTxt));
            CD->Button[0]=HasText(ITxt(i,16,&CustomTxt));
            CD->Button[1]=HasText(ITxt(i,17,&CustomTxt));
            CD->Button[2]=HasText(ITxt(i,18,&CustomTxt));
            CD->Button[3]=HasText(ITxt(i,19,&CustomTxt));
            CD->HintButton[0]=CD->Button[0];
            CD->HintButton[1]=CD->Button[1];
            CD->HintButton[2]=CD->Button[2];
            CD->HintButton[3]=CD->Button[3];
            CD->HasCansel=1;
            CD->Type=Ct;
            if(NEWload&&Apply){
              if(App==1){ CustomReq(CD->Num,1,0); }
            }  
            break;
          case 1: // PIC
            CD->Pic[0]=HasText(ITxt(i,5,&CustomTxt)); // ���� � �������� �� MAPS
            CD->Number[0]=a2i(ITxt(i,6,&CustomTxt));  // 1-���������
            CD->HasCansel=0;
            CD->Type=Ct;
            if(NEWload&&Apply){
              if(App==1){ CustomPic(CD->Num,1); }
            }
            break;  
        }    
        break;
      case 3: // HERO
        if(Cst==1){ // PIC
          CD->Number[0]=a2i(ITxt(i,5,&CustomTxt)); // ����� �����
          CD->Text[0]=ITxt(i,6,&CustomTxt);        // ������� �������
          CD->Text[1]=ITxt(i,7,&CustomTxt);        // ��������� �������
          CD->HasCansel=0;
          CD->Type=Ct;
          if(NEWload){
            if(App==1){
//            SetHeroPic(CD->Number[0],CD->Text[0],CD->Text[1],0);
              CustomHPic(CD->Num,-1,1);
            }
          }
        }
        break;
      default: continue; // ���� �� ���������� - ����������
    }
  }
//CustomReq(0);
  RETURN(1)
}

int AddExtCMDPic(int Num,char *pic,int Repiter)
{
  #include "templ.h"
  int   Ind,IsNew;
  _CustomData1_ *CD;

  IsNew=0;
  Ind=FindCData(Num);
  if(Ind==-1){
    IsNew=1;
    Ind=FindFreeCData();
    if(Ind==-1){ Error(); RETURN(0) }
  }
  CD=&CustomData[Ind];
  if(IsNew){
    CD->Type=2;  // Request 
    CD->SType=1; // PIC
    CD->Num=Num;
  }
  CD->Pic[0]=HasText(pic);
  CD->Number[0]=Repiter;
  RETURN(1)
}

int AddExtCMDRequest(int Num
    ,char *txt1,char *txt2,char *txt3
    ,char *pic1,char *pic2,char *pic3,char *pic4
    ,char *pch1,char *pch2,char *pch3,char *pch4
    ,char *but1,char *but2,char *but3,char *but4
    ,char *bth1,char *bth2,char *bth3,char *bth4
    ,char HasEscape)
{
  #include "templ.h"
  int   Ind,IsNew;
  _CustomData1_ *CD;

  IsNew=0;
  Ind=FindCData(Num);
  if(Ind==-1){
    IsNew=1;
    Ind=FindFreeCData();
    if(Ind==-1){ Error(); RETURN(0) }
  }  
  CD=&CustomData[Ind];
  if(IsNew){
    CD->Type=2;  // Request 
    CD->SType=2; // EXT
    CD->Num=Num;
  }  
  if(((IsNew==0)&&(txt1!=0))||(IsNew==1)) CD->Text[0]=txt1;
  if(((IsNew==0)&&(txt2!=0))||(IsNew==1)) CD->Text[1]=HasText(txt2);
  if(((IsNew==0)&&(txt3!=0))||(IsNew==1)) CD->Text[2]=HasText(txt3);
//  CD->Text[3]=ITxt(i,7,&CustomTxt);
  if(((IsNew==0)&&(pic1!=0))||(IsNew==1)) CD->Pic[0]=HasText(pic1);
  if(((IsNew==0)&&(pic2!=0))||(IsNew==1)) CD->Pic[1]=HasText(pic2);
  if(((IsNew==0)&&(pic3!=0))||(IsNew==1)) CD->Pic[2]=HasText(pic3);
  if(((IsNew==0)&&(pic4!=0))||(IsNew==1)) CD->Pic[3]=HasText(pic4);
  if(((IsNew==0)&&(pch1!=0))||(IsNew==1)) CD->Hint[0]=HasText(pch1);
  if(((IsNew==0)&&(pch2!=0))||(IsNew==1)) CD->Hint[1]=HasText(pch2);
  if(((IsNew==0)&&(pch3!=0))||(IsNew==1)) CD->Hint[2]=HasText(pch3);
  if(((IsNew==0)&&(pch4!=0))||(IsNew==1)) CD->Hint[3]=HasText(pch4);
  if(((IsNew==0)&&(but1!=0))||(IsNew==1)) CD->Button[0]=HasText(but1);
  if(((IsNew==0)&&(but2!=0))||(IsNew==1)) CD->Button[1]=HasText(but2);
  if(((IsNew==0)&&(but3!=0))||(IsNew==1)) CD->Button[2]=HasText(but3);
  if(((IsNew==0)&&(but4!=0))||(IsNew==1)) CD->Button[3]=HasText(but4);
  if(((IsNew==0)&&(bth1!=0))||(IsNew==1)) CD->HintButton[0]=HasText(bth1);
  if(((IsNew==0)&&(bth2!=0))||(IsNew==1)) CD->HintButton[1]=HasText(bth2);
  if(((IsNew==0)&&(bth3!=0))||(IsNew==1)) CD->HintButton[2]=HasText(bth3);
  if(((IsNew==0)&&(bth4!=0))||(IsNew==1)) CD->HintButton[3]=HasText(bth4);
  if(HasEscape!=-1){
    CD->HasCansel=HasEscape;
  }else if(IsNew){
    CD->HasCansel=1;
  }
  RETURN(1)
}

void CustomHPic(int Num,int Hn,int startup)
{
  #include "templ.h"
  int Ind;
  _CustomData1_ *CD;
  char Buf[2][1024];

  Ind=FindCData(Num);
  if(Ind==-1){ Error(); RETURNV }
  CD=&CustomData[Ind];
  if(CD->Type==0){ // �����������
    Message("Oops, undefined customizable dialogue.",1);
    RETURNV
  }
  StrCanc(Buf[0],14,"..\\MAPS\\",CD->Text[0]);
  StrCanc(Buf[1],14,"..\\MAPS\\",CD->Text[1]);

  if(Hn==-1) Hn=CD->Number[0];
  if(startup)    SetHeroPic(Hn,Buf[0],Buf[1],0);
  else        ChangeHeroPic(Hn,Buf[0],Buf[1]);
  RETURNV
}

char  path0[]=".\\MAPS\\";
char  path1[]=".\\MAPS\\";
static char Answer[1024];
int CustomReq(int Num,int startup,char **answ)
{
  #include "templ.h"
  int Ind,ret;
  _CustomData1_ *CD;
  _Sphinx1 Sphinx;
  char *path;
  char  Buf[4][128];

  Ind=FindCData(Num);
  if(Ind==-1){ Error(); RETURN(0) }
  CD=&CustomData[Ind];
  if(CD->Type==0){ // �����������
    Message("Oops, undefined customizable dialogue.",1);
    RETURN(0)
  }
  BeforeDialog();
  if(startup) path=path0; else path=path1;
  Sphinx.SelItm=-1;
  Sphinx.Text1=CD->Text[0];
  Sphinx.Text2=CD->Text[1];
  Sphinx.Text3=CD->Text[2];
  Answer[0]=5; Answer[1]=0;
  Sphinx.Text4=Answer; //CD->Text[3];
  if(CD->Pic[0]!=0){ 
    StrCanc(Buf[0],128,path,CD->Pic[0]);
    Sphinx.Pic1Path=Buf[0];
  }else{
    Sphinx.Pic1Path=0;
  }  
  if(CD->Pic[1]!=0){
    StrCanc(Buf[1],128,path,CD->Pic[1]);
    Sphinx.Pic2Path=Buf[1];
  }else{
    Sphinx.Pic2Path=0;
  }  
  if(CD->Pic[2]!=0){
    StrCanc(Buf[2],128,path,CD->Pic[2]);
    Sphinx.Pic3Path=Buf[2];
  }else{
    Sphinx.Pic3Path=0;
  }  
  if(CD->Pic[3]!=0){
    StrCanc(Buf[3],128,path,CD->Pic[3]);
    Sphinx.Pic4Path=Buf[3];
  }else{
    Sphinx.Pic4Path=0;
  }  
  Sphinx.Pic1Hint=CD->Hint[0];
  Sphinx.Pic2Hint=CD->Hint[1];
  Sphinx.Pic3Hint=CD->Hint[2];
  Sphinx.Pic4Hint=CD->Hint[3];
  Sphinx.Chk1Text=CD->Button[0];
  Sphinx.Chk2Text=CD->Button[1];
  Sphinx.Chk3Text=CD->Button[2];
  Sphinx.Chk4Text=CD->Button[3];
  Sphinx.Chk1Hint=CD->HintButton[0];
  Sphinx.Chk2Hint=CD->HintButton[1];
  Sphinx.Chk3Hint=CD->HintButton[2];
  Sphinx.Chk4Hint=CD->HintButton[3];
  Sphinx.ShowCancel=CD->HasCansel;
  CustomReq1_c(Service_GetForegroundWindow(),&Sphinx,".\\Data\\ZVS\\LIB1.RES",EffectVolume()>SILENCE);
  SetFocus((HWND)Service_GetForegroundWindow());
  if(answ!=0){
    StrCopy(Answer,512,Sphinx.Text4);
//    if(a2i(Answer)==9999) Answer[0]=0;
    if(Answer[0]==5) Answer[0]=0;
    *answ=Answer;
  }
  ret=Sphinx.SelItm;
  AfterDialog();
  RETURN(ret)
}

int QuickDialog(_Sphinx1 *Sphinx){
  #include "templ.h"
  BeforeDialog();
  int ret=CustomReq1_c(Service_GetForegroundWindow(),Sphinx,".\\Data\\ZVS\\LIB1.RES",EffectVolume()>SILENCE);
  SetFocus((HWND)Service_GetForegroundWindow());
  AfterDialog();
  // -1 - press Esc, 1= press Ok
  RETURN(ret)
}

TxtFile TXTSphinx;
int LoadSphinxTXT(void)
{
  #include "templ.h"
  if(LoadTXT("ZSphinx0.TXT",&TXTSphinx)) RETURN(-1) // �� ����� ��������� TXT
  RETURN(0)
}
int CheckAnswer(char *ans, char *cor)
{
  #include "templ.h"
//asm int 3
  ToUpper(ans); ToUpper(cor);
  RETURN(StrCmpExt(cor,ans))
}

int SphinxReq(int Num)
{
  #include "templ.h"
  _Sphinx1 Sphinx;

  BeforeDialog();
  Sphinx.SelItm=-1;
  Sphinx.Text1=ITxt(Num,0,&TXTSphinx);
  Sphinx.Text2=ITxt(122,0,&Strings);
  Sphinx.Text3=0;
  Answer[0]=0;
//  Sphinx.Text4=Answer; //CD->Text[3];
  Answer[0]='9'; Answer[1]='9'; Answer[2]='9'; Answer[3]='9'; Answer[4]=0;
  Sphinx.Text4=Answer; //CD->Text[3];
  Sphinx.Pic1Path=0;
  Sphinx.Pic2Path=0;
  Sphinx.Pic3Path=0;
  Sphinx.Pic4Path=0;
  Sphinx.Pic1Hint=0;
  Sphinx.Pic2Hint=0;
  Sphinx.Pic3Hint=0;
  Sphinx.Pic4Hint=0;
  Sphinx.Chk1Text=0;
  Sphinx.Chk2Text=0;
  Sphinx.Chk3Text=0;
  Sphinx.Chk4Text=0;
  Sphinx.Chk1Hint=0;
  Sphinx.Chk2Hint=0;
  Sphinx.Chk3Hint=0;
  Sphinx.Chk4Hint=0;
  Sphinx.ShowCancel=0;
  CustomReq1_c(Service_GetForegroundWindow(),&Sphinx,".\\Data\\ZVS\\LIB1.RES",EffectVolume()>SILENCE);
  SetFocus((HWND)Service_GetForegroundWindow());

  StrCopy(Answer,512,Sphinx.Text4); 
  if(a2i(Answer)==9999) Answer[0]=0;
  AfterDialog();
  if(CheckAnswer(Answer,ITxt(Num,1,&TXTSphinx))) RETURN(1)
  else RETURN(0)
}
int MultiCheckReq( char*TxtH,int state,char *txt[12],int chRAD)
{
  #include "templ.h"
  long i,j,v,n,ind[12];
  int Sstate[12];
  char /**txt[12],*/*Stxt[12];
  _CheckBoxes StartUpSetUp;

  BeforeDialog();
  for(i=n=0;i<12;i++) if(HasText(txt[i])) ind[n++]=i;
  StartUpSetUp.Number=n;
  for(i=0;i<n;i++) Stxt[i]=txt[ind[i]];
  StartUpSetUp.Text=Stxt;
  for(i=0;i<n;i++){
    for(j=0,v=1;j<ind[i];j++) v*=2;
    if(state&v) Sstate[i]=1; else Sstate[i]=0;
  }
  StartUpSetUp.OnlyOne=(char)chRAD;
  StartUpSetUp.Caption=TxtH;
  StartUpSetUp.State=Sstate;
//  StartUpSetUp.IFPath=0;
  MultiCheck_c(Service_GetForegroundWindow(),&StartUpSetUp,".\\Data\\ZVS\\LIB1.RES",EffectVolume()>SILENCE);
  SetFocus((HWND)Service_GetForegroundWindow());
//asm int 3
  for(i=0,state=0;i<n;i++){ 
    for(j=0,v=1;j<ind[i];j++) v*=2;
    if(Sstate[i]) state+=v;
  }  
  AfterDialog();
  RETURN(state)
}

void MultiCheckReqInt(_CheckBoxes *StartUpSetUp){
  #include "templ.h"
  MultiCheck_c(Service_GetForegroundWindow(),StartUpSetUp,".\\Data\\ZVS\\LIB1.RES",EffectVolume()>SILENCE);
  SetFocus((HWND)Service_GetForegroundWindow());
  RETURNV
}

void CustomPic(int Num,int startup)
{
  #include "templ.h"
  int Ind;
  _CustomData1_ *CD;
  _Intro Intro;
  char *path;
  char  Buf[1024];

  Ind=FindCData(Num);
  if(Ind==-1){ Error(); RETURNV }
  CD=&CustomData[Ind];
  if(CD->Type==0){ // �����������
    Message("Oops, undefined customizable dialogue.",1);
    RETURNV
  }
  BeforeDialog();
  if(startup) path=path0; else path=path1;
  StrCanc(Buf,128,path,CD->Pic[0]);
  Intro.AVIBMPPath=Buf;
  Intro.Cicling=(char)CD->Number[0];
  CustomPic_c(Service_GetForegroundWindow(),&Intro,".\\Data\\ZVS\\LIB1.RES",EffectVolume()>SILENCE);
  SetFocus((HWND)Service_GetForegroundWindow());

  AfterDialog();
  RETURNV
}

static char *Mess1[10]={"��������� 1","����� 1","����� 2","����� 3","","","","","",""};
static char *Mess2[10]={"��������� 2","����� 1","����� 2","","","","","","",""};
static char *Mess3[10]={"��������� 3","����� 1","����� 2","","","","","","",""};
static char *Mess4[10]={"��������� 4","����� 1","����� 2","","","","","","",""};
static char *Mess5[10]={"��������� 5","����� 1","����� 2","","","","","","",""};
static char *Mess6[10]={"��������� 6","����� 1","����� 2","","","","","","",""};
static char *Mess7[10]={"��������� 7","����� 1","����� 2","","","","","","",""};
static char *Mess8[10]={"��������� 8","����� 1","����� 2","","","","","","",""};
static char *Mess9[10]={"��������� 9","����� 1","����� 2","","","","","","",""};
// � ��� �� ���� � ���������

//  ������ �������� ���������� �� ���������.
static char **MessAll[]={
  Mess1,Mess2,Mess3,Mess4,Mess5,Mess6,Mess7,Mess8,Mess9,
// ���� ��������� ����������
  0  // ��������� ����� ������
};
static _Diplomacy DP={
// char GamerAvailable[8]; // �� 8-�� ������� 1-����, 0-��� ������ (� ������� ���������� ������)
 {1,1,1,1,1,1,1,1},
// long GamerIndex;        // ����� ������
 0,
// char GamerEnable[8][2]; // 0-������� � ������ ��������, 1-�����
 {{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{1,0}},
// char GamerSent[8][2];   // 0, ���� ������� � ������ �� ���������� � 1, ���� ����������
 {{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1},{0,1}},
 // ������ ������ ������ 0-����� ��������, 1-����� �� ����������.
 // GamerEnable[8][2] � GamerSent[8][2] ������� ���. ���� GamerEnable[i][j]
 // ����, �� �������� "�������" ������ ���� ��������, �.�. � ���� ���� ���
 // ����������, � ���� �� ����, �� ���������. �� �� ������ ����������
 // �������� � GamerSent[i][j], ���� ��� ����������. � ����� ������ ������� ���
 // �������� ��  GamerSent[i][j] � ������ � GamerEnable[8][2].
// long DipLevel[8][8];    // ������� 8 �� 8, ��� ������ [i][j]
 {{50,50,50,50,50,50,50,50},{50,50,50,50,50,50,50,50},{50,50,50,50,50,50,50,50},{50,50,50,50,50,50,50,50},
  {50,50,50,50,50,50,50,50},{50,50,50,50,50,50,50,50},{50,50,50,50,50,50,50,50},{50,50,50,50,50,50,50,50}},
                         // ������ ������� ��������� (0-100) i � j (��������� j � i ����� ���� ������)
                         // � ���� ������� �������� ���������� � ��������� �� ���� �
// long ShowLevels[7];     // ������� ���������, �� ���� ��������  ������������ ������ ������ � (0-100) - �������� ��� ����
 {31,51,31,51,51,51,71},
// long Resources[8][7];   // ������� ����
 {{50,50,50,50,50,50,50000},
  {50,50,50,50,50,50,50000},
  {50,50,50,50,50,50,50000},
  {50,50,50,50,50,50,50000},
  {50,50,50,50,50,50,50000},
  {50,50,50,50,50,50,50000},
  {50,50,50,50,50,50,50000},
  {50,50,50,50,50,50,50000}},
// long ResSent[7][8][8];     // ���������� ������� �� ���� � (i/j/k, i - ���������� �������, j- �� ������, k - � ������)
 {{{0}}},
// long ResvMessage[8][8]; // �������� � �� ������. ��������� (���.,-1-���)
 {{-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1}},
// long ReplMessage[8][8]; // ��������� � ����� (������ ������, -1-���)
 {{-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1}},
// long SentMessage[8][8]; // ����� ��������� (������ �����., -1-���)
 {{-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1}},
// char ***Messages;        // ��� ��������� � ������ (��. ����)
  MessAll
};

int PrepareDP(int Gamer)
{
  #include "templ.h"
  int i,j,k;
  for(i=0;i<8;i++) if(DoesExist(i)) DP.GamerAvailable[i]=1; else DP.GamerAvailable[i]=0;
  DP.GamerIndex=Gamer;
  for(i=0;i<8;i++){
    DP.GamerEnable[i][0]=(char)~DP.GamerSent[i][0];
    DP.GamerEnable[i][1]=(char)~DP.GamerSent[i][1];
  }
  for(i=0;i<8;i++) for(j=0;j<7;j++) DP.Resources[i][j]=GetRes(i,j);
  for(i=0;i<7;i++) for(j=0;j<8;j++) for(k=0;k<8;k++) DP.ResSent[i][j][k]=0;
  for(i=0;i<8;i++) DP.GamerEnable[i][0]=0; DP.GamerEnable[i][1]=0;
  for(i=0;i<8;i++) if(DP.ResvMessage[Gamer][i]!=-1) DP.GamerEnable[Gamer][1]=1;
  for(i=0;i<8;i++) if(DP.SentMessage[Gamer][i]!=-1) DP.GamerEnable[Gamer][0]=0;

  RETURN(0)
}

int ShowDiplom(int Gamer)
{
  #include "templ.h"
  int ret;
  BeforeDialog();
  PrepareDP(Gamer);
  ret=Diplom_c(Service_GetForegroundWindow(),&DP,".\\Data\\ZVS\\LIB1.RES",EffectVolume()>SILENCE);
  SetFocus((HWND)Service_GetForegroundWindow());
  AfterDialog();
  RETURN(ret)
}

int ShowCurse(_CurseShow *CurseShow)
{
  #include "templ.h"
  int ret;
  BeforeDialog();
  ret=Curse_c(Service_GetForegroundWindow(),CurseShow,".\\Data\\ZVS\\LIB1.RES",EffectVolume()>SILENCE);
  SetFocus((HWND)Service_GetForegroundWindow());
  AfterDialog();
  RETURN(ret)
}

int ShowNPC(_DlgNPC *DlgNPC)
{
  #include "templ.h"
  int ret;
  BeforeDialog();
  ret=NPCInfo_c(Service_GetForegroundWindow(),DlgNPC,".\\Data\\ZVS\\LIB1.RES",EffectVolume()>SILENCE);
  SetFocus((HWND)Service_GetForegroundWindow());
  AfterDialog();
  RETURN(ret)
}

void ShowWoGSetup(_DlgSetup *DlgSetup)
{
  #include "templ.h"
  Dword ParWin=Service_GetForegroundWindow();
  BeforeDialog();
  if(ParWin!=0){
    WoGSetup_c(ParWin,DlgSetup,".\\Data\\ZVS\\LIB1.RES",EffectVolume()>SILENCE);
    SetFocus((HWND)Service_GetForegroundWindow());
  }
  AfterDialog();
  RETURNV
}

int ShowRadio(_PopUpRadioButtons *PopUpRadioButtons)
{
  #include "templ.h"
  int ret;
  BeforeDialog();
  ret=Radio2_c(Service_GetForegroundWindow(),PopUpRadioButtons,".\\Data\\ZVS\\LIB1.RES",EffectVolume()>SILENCE);
  SetFocus((HWND)Service_GetForegroundWindow());
  AfterDialog();
  RETURN(ret)
}

int SaveSetupState(char *Name,void *Buf,int Len)
{
  #include "templ.h"
  int ret=SaveSetupState_c(Name,Buf,Len);
  RETURN(ret)
}
int LoadSetupState(char *Name,void *Buf,int Len)
{
  #include "templ.h"
  int ret=LoadSetupState_c(Name,Buf,Len);
  RETURN(ret)
}

// 3.58
int ChooseFileDlg(_ChooseFile* ChooseFile, char *Default)
{
  #include "templ.h"
  int ret;
  if(ChooseFile_c==0){
    StrCopy(ChooseFile->Buf,StrLen(Default)+1,Default);
    RETURN(0)
  }
  BeforeDialog();
  ret=ChooseFile_c(Service_GetForegroundWindow(),ChooseFile,".\\Data\\ZVS\\LIB1.RES",EffectVolume()>SILENCE);
  SetFocus((HWND)Service_GetForegroundWindow());
  AfterDialog();
  RETURN(ret)
}

int ChooseIconDlg(_IconList * IconList){
  #include "templ.h"
  int ret;
  if(ChooseIcon_c==0){
    Message("Option not implemented in ZvsLib1.dll",1);
    RETURN(-1)
  }
  BeforeDialog();
  ret=ChooseIcon_c(Service_GetForegroundWindow(),IconList,".\\Data\\ZVS\\LIB1.RES",EffectVolume()>SILENCE);
  SetFocus((HWND)Service_GetForegroundWindow());
  AfterDialog();
  RETURN(ret)
}

int ReadIntINI(int *Value,int DefValue,char *Parameter,char *Section,char *File){
  #include "templ.h"
  int ret;
  if(ReadIntFromINI_c==0){
    Message("Option not implemented in ZvsLib1.dll",1);
    *Value=DefValue;
    RETURN(-1)
  }
  ret=ReadIntFromINI_c(File,Section,Parameter,Value,DefValue);
  RETURN(ret)
}
int ReadStrINI(char *Value,int Len,char *DefValue,char *Parameter,char *Section,char *File){
  #include "templ.h"
  int ret;
  if(ReadStrFromINI_c==0){
    Message("Option not implemented in ZvsLib1.dll",1);
    StrCopy(Value,Len,DefValue);
    RETURN(-1)
  }
  ret=ReadStrFromINI_c(File,Section,Parameter,Value,Len,DefValue);
  RETURN(ret)
}
int WriteIntINI(int Value,char *Parameter,char *Section,char *File){
  #include "templ.h"
  int ret;
  if(WriteIntToINI_c==0){
    Message("Option not implemented in ZvsLib1.dll",1);
    RETURN(-1)
  }
  ret=WriteIntToINI_c(File,Section,Parameter,Value);
  RETURN(ret)
}
int WriteStrINI(char *Value,char *Parameter,char *Section,char *File){
  #include "templ.h"
  int ret;
  if(WriteStrToINI_c==0){
    Message("Option not implemented in ZvsLib1.dll",1);
    RETURN(-1)
  }
  ret=WriteStrToINI_c(File,Section,Parameter,Value);
  RETURN(ret)
}

int ShowUpgradeDlg(_MonsterInfo *MonInfo){
  #include "templ.h"
  int ret;
  if(ShowUpgradeDlg_c==0){
    Message("Option not implemented in ZvsLib1.dll",1);
    RETURN(-1)
  }
  BeforeDialog();
  ret=ShowUpgradeDlg_c(Service_GetForegroundWindow(),MonInfo,".\\Data\\ZVS\\LIB1.RES",EffectVolume()>SILENCE);
  SetFocus((HWND)Service_GetForegroundWindow());
  AfterDialog();
  RETURN(ret)
}

static char *WoGMessages[10];
int WoGMessage(char *Msg1,char *Msg2,char *Msg3,char *Msg4,char *Msg5){
  #include "templ.h"
  int ret;
  BeforeDialog();
  if(WoGMessage_c==0){
    ret=CommonDialog(Msg1);
  }else{
    WoGMessages[0]=Msg1;
    WoGMessages[1]=Msg2;
    WoGMessages[2]=Msg3;
    WoGMessages[3]=Msg4;
    WoGMessages[4]=Msg5;
    WoGMessages[5]=0;
    ret=WoGMessage_c(Service_GetForegroundWindow(),WoGMessages,".\\Data\\ZVS\\LIB1.RES",EffectVolume()>SILENCE);
    SetFocus((HWND)Service_GetForegroundWindow());
  }
  AfterDialog();
  RETURN(ret)
}

void PicDlg(char *Msg,char *Pic){
  #include "templ.h"
  char *pic=Pic;
  if(pic==0) pic="NONE";
  BeforeDialog();
  if(CommonPicDlg_c==0){
    CommonDialog(Msg);
  }else{
    CommonPicDlg_c(Service_GetForegroundWindow(),Msg,pic,".\\Data\\ZVS\\LIB1.RES",EffectVolume()>SILENCE);
    SetFocus((HWND)Service_GetForegroundWindow());
  }
  AfterDialog();
  RETURNV
}
void PicDlg_Int(char *Msg,char *Pic){
  #include "templ.h"
  char *pic=Pic;
  if(pic==0) pic="NONE";
  if(CommonPicDlg_c==0){
    CommonDialog(Msg);
  }else{
    CommonPicDlg_c(Service_GetForegroundWindow(),Msg,pic,".\\Data\\ZVS\\LIB1.RES",EffectVolume()>SILENCE);
    SetFocus((HWND)Service_GetForegroundWindow());
  }
  RETURNV
}

static char FullPath[_MAX_PATH+1];
char *GetFolder(int Mod)
{
  #include "templ.h"
  strcpy(FullPath,StartUpFolder);
  switch(Mod){
    case 1: // in DATA
      strncat(FullPath,"DATA\\",_MAX_PATH);
      break;
    case 2: // in MAPS
      strncat(FullPath,"MAPS\\",_MAX_PATH);
      break;
    case 3: // in Random Maps
      strncat(FullPath,"RANDOM_MAPS\\",_MAX_PATH);
      break;
    case 4: // in GAMES
      strncat(FullPath,"GAMES\\",_MAX_PATH);
      break;
    case 5: // in Script folder
      strncat(FullPath,"DATA\\S\\",_MAX_PATH);
      break;
    case 6: // in Resource folder
      strncat(FullPath,"DATA\\P\\",_MAX_PATH);
      break;
    case 7: // in LIB folder
      strncat(FullPath,"DATA\\ZVS\\LIB1.RES\\",_MAX_PATH);
      break;
    case 8: // in Campaign res folder
      strncat(FullPath,"DATA\\ZVS\\CMP.RES\\",_MAX_PATH);
      break;
    case 9: // in ERM Help
      strncat(FullPath,"ERM_HELP\\",_MAX_PATH);
      break;
    default: //Heroes home
      break;
  }
  RETURN(FullPath)
}
int DoesFileExist(char *FName,int Mod)
{
/*
  strcpy(FullPath,StartUpFolder);
  switch(Mod){
    case 1: // in DATA
      strncat(FullPath,"DATA\\",_MAX_PATH);
      break;
    case 2: // in MAPS
      strncat(FullPath,"MAPS\\",_MAX_PATH);
      break;
    case 3: // in Random Maps
      strncat(FullPath,"RANDOM_MAPS\\",_MAX_PATH);
      break;
    case 4: // in GAMES
      strncat(FullPath,"GAMES\\",_MAX_PATH);
      break;
    case 5: // in Script folder
      strncat(FullPath,"DATA\\S\\",_MAX_PATH);
      break;
    case 6: // in Resource folder
      strncat(FullPath,"DATA\\P\\",_MAX_PATH);
      break;
    case 7: // in LIB folder
      strncat(FullPath,"DATA\\ZVS\\LIB1.RES\\",_MAX_PATH);
      break;
    case 8: // in Campaign res folder
      strncat(FullPath,"DATA\\ZVS\\CMP.RES\\",_MAX_PATH);
      break;
    case 9: // in ERM Help
      strncat(FullPath,"ERM_HELP\\",_MAX_PATH);
      break;
    default: //Heroes home
      break;
  }
*/
  #include "templ.h"
  if(Mod==10){ // absolute folder
    FullPath[0]=0;
  }else{
    GetFolder(Mod);
  }
  strncat(FullPath,FName,_MAX_PATH);
  if(GetFileAttributes(FullPath)==0xFFFFFFFF) RETURN(0)
  RETURN(1)
}

static int (*p_TestDlg)(int ParentWindow);
void TestDlg(void)
{
//  BeforeDialog();
//  p_TestDlg(Service_GetForegroundWindow());
//  AfterDialog();
}

///////////////////////
int LoadZVSDialogs(void)
{
  Word fcw;
  __asm fstcw fcw;
  Dword hdll=Service_LoadLibrary("zvslib1.dll"); if(hdll==0) -1;
//  if(Service_FreeLibrary(hdll)==0) return -1;
  Dword pfun=Service_GetProcAddress(hdll,"_InvokeDialogue02"); if(pfun==0) return -1;
  *(Dword *)&ChooseCastle_c=pfun;
  pfun=Service_GetProcAddress(hdll,"_InvokeDialogue01"); if(pfun==0) return -1;
  *(Dword *)&CommonDialog_c=pfun;
// �������� ���������
//  pfun=Service_GetProcAddress(hdll,"_InvokeDialogue05");
//  if(pfun==0){ // return -1;
//    Error();
//  }else{ (Dword)CustomReq_c=pfun; }
  pfun=Service_GetProcAddress(hdll,"_InvokeDialogue051");
  if(pfun==0){ // return -1;
    Error();
  }else{ *(Dword *)&CustomReq1_c=pfun; }
  pfun=Service_GetProcAddress(hdll,"_InvokeDialogue06");
  if(pfun==0){ // return -1;
    Error();
  }else{ *(Dword *)&Curse_c=pfun; }
  pfun=Service_GetProcAddress(hdll,"_InvokeDialogue07");
  if(pfun==0){ // return -1;
    Error();
  }else{ *(Dword *)&CustomPic_c=pfun; }
  pfun=Service_GetProcAddress(hdll,"_InvokeDialogue08");
  if(pfun==0){ // return -1;
    Error();
  }else{ *(Dword *)&MultiCheck_c=pfun; }
  pfun=Service_GetProcAddress(hdll,"_InvokeDialogue04");
  if(pfun==0){ // return -1;
    Error();
  }else{ *(Dword *)&Diplom_c=pfun; }
  pfun=Service_GetProcAddress(hdll,"_InvokeDialogue09");
  if(pfun==0){ // return -1;
    Error();
  }else{ *(Dword *)&NPCInfo_c=pfun; }
  pfun=Service_GetProcAddress(hdll,"_InvokeDialogue10");
  if(pfun==0){ // return -1;
    Error();
  }else{ *(Dword *)&Radio2_c=pfun; }
  pfun=Service_GetProcAddress(hdll,"_InvokeSetupDialogue");
  if(pfun==0){ // return -1;
    Error();
  }else{ *(Dword *)&WoGSetup_c=pfun; }
  pfun=Service_GetProcAddress(hdll,"_SaveSetupState");
  if(pfun==0){ // return -1;
    Error();
  }else{ *(Dword *)&SaveSetupState_c=pfun; }
  pfun=Service_GetProcAddress(hdll,"_LoadSetupState");
  if(pfun==0){ // return -1;
    Error();
  }else{ *(Dword *)&LoadSetupState_c=pfun; }
// 3.58
  pfun=Service_GetProcAddress(hdll,"_InvokeDialogue11");
  if(pfun==0){ // return -1;
//    Error();
    *(Dword *)&ChooseFile_c=0;
  }else{ *(Dword *)&ChooseFile_c=pfun; }
  pfun=Service_GetProcAddress(hdll,"_InvokeDialogue12");
  if(pfun==0){ // return -1;
//    Error();
    *(Dword *)&ChooseIcon_c=0;
  }else{ *(Dword *)&ChooseIcon_c=pfun; }
  pfun=Service_GetProcAddress(hdll,"_InvokeWOGMessageBox");
  if(pfun==0){ // return -1;
//    Error();
    *(Dword *)&WoGMessage_c=0;
  }else{ *(Dword *)&WoGMessage_c=pfun; }
  pfun=Service_GetProcAddress(hdll,"_ReadIntFromINI");
  if(pfun==0){ // return -1;
//    Error();
    *(Dword *)&ReadIntFromINI_c=0;
  }else{ *(Dword *)&ReadIntFromINI_c=pfun; }
  pfun=Service_GetProcAddress(hdll,"_ReadStrFromINI");
  if(pfun==0){ // return -1;
//    Error();
    *(Dword *)&ReadStrFromINI_c=0;
  }else{ *(Dword *)&ReadStrFromINI_c=pfun; }
  pfun=Service_GetProcAddress(hdll,"_WriteIntToINI");
  if(pfun==0){ // return -1;
//    Error();
    *(Dword *)&WriteIntToINI_c=0;
  }else{ *(Dword *)&WriteIntToINI_c=pfun; }
  pfun=Service_GetProcAddress(hdll,"_WriteStrToINI");
  if(pfun==0){ // return -1;
//    Error();
    *(Dword *)&WriteStrToINI_c=0;
  }else{ *(Dword *)&WriteStrToINI_c=pfun; }
  pfun=Service_GetProcAddress(hdll,"_InvokeDialogue15");
  if(pfun==0){ // return -1;
//    Error();
    *(Dword *)&ShowUpgradeDlg_c=0;
  }else{ *(Dword *)&ShowUpgradeDlg_c=pfun; }
  pfun=Service_GetProcAddress(hdll,"_InvokeDialogue01a");
  if(pfun==0){ // return -1;
    Error();
  }else{ *(Dword *)&CommonPicDlg_c=pfun; }
  pfun=Service_GetProcAddress(hdll,"_RegGlobalTerminate");
  if(pfun==0){ // return -1;
    Error();
  }else{ *(Dword *)&RegGlobalTerminate_c=pfun; }

  fcw=0x023F;
  __asm fldcw fcw;
 /* Get the current working directory: */
  if(_getcwd(StartUpFolder, _MAX_PATH ) == NULL){
    strcpy(StartUpFolder,".");
  }
  strcat(StartUpFolder,"\\");
  RegGlobalTerminate_c(&TerminateFlag);
///////////////////////////////
/*
  hdll=Service_LoadLibrary("project1.dll"); 
  if(hdll==0){
    Error();
  }
  pfun=Service_GetProcAddress(hdll,"@SayHello$qpv");
  if(pfun==0){ // return -1;
    Error();
  }else{ *(Dword *)&p_TestDlg=pfun; }
*/
///////////////////  
  
  return 0;
}

extern "C" int  _heap_init(int mtflag);
extern "C" int  _mtinit(void);
extern "C" void _ioinit(void);
extern "C" void _cinit(void);
extern "C" unsigned int _osver;
extern "C" unsigned int _winminor;
extern "C" unsigned int _winmajor;
extern "C" unsigned int _winver;
extern "C" unsigned int _osplatform;

  OSVERSIONINFOA posvi;      
int MyGetVersionExA(OSVERSIONINFOA *lpVersionInfo);
#define VER_PLATFORM_WIN32_NT 2

void InitCRT(void){
  // Get the full Win32 version
//  _osver = GetVersion();
//  _winminor = (_osver >> 8) & 0x00FF ;
//  _winmajor = _osver & 0x00FF ;
//  _winver = (_winmajor << 8) + _winminor;
//  _osver = (_osver >> 16) & 0x00FFFF ;
        /*
         * Dynamically allocate the OSVERSIONINFOA buffer, so we avoid
         * triggering the /GS buffer overrun detection.  That can't be
         * used here, since the guard cookie isn't available until we
         * initialize it from here!
         */

        /*
         * Get the full Win32 version
         */
        posvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
        (void)GetVersionExA(&posvi);

        _osplatform = posvi.dwPlatformId;
        _winmajor = posvi.dwMajorVersion;
        _winminor = posvi.dwMinorVersion;

        /*
         * The somewhat bizarre calculations of _osver and _winver are
         * required for backward compatibility (used to use GetVersion)
         */
        _osver = (posvi.dwBuildNumber) & 0x07fff;
        if ( _osplatform != VER_PLATFORM_WIN32_NT )
            _osver |= 0x08000;
        _winver = (_winmajor << 8) + _winminor;

        /*
         * Determine if this is a managed application
         */
//        managedapp = check_managed_app();

#ifdef _MT
  _heap_init(1);               /* initialize heap */
#else  /* _MT */
  _heap_init(0);               /* initialize heap */
#endif  /* _MT */
#ifdef _MT
  _mtinit();                    /* initialize multi-thread */
#endif  /* _MT */
  _ioinit();                      /* initialize lowio */

  _cinit();                       /* do C data initialize */
 
}

////////////////////////////////////////
int SaveCustom(void)
{
  #include "templ.h"
  if(Saver("LCUS",4)) RETURN(1)
  if(Saver(&YesCustomCMD,sizeof(YesCustomCMD))) RETURN(1)
  if(Saver(CustomTxtName,sizeof(CustomTxtName))) RETURN(1)
  RETURN(0)
}

int LoadCustom(int /*ver*/)
{
  #include "templ.h"
  char buf[4]; if(Loader(buf,4)) RETURN(1)
  if(buf[0]!='L'||buf[1]!='C'||buf[2]!='U'||buf[3]!='S')
      {MError("LoadCustom cannot start loading"); RETURN(1) }
  if(Loader(&YesCustomCMD,sizeof(YesCustomCMD))) RETURN(1)
  if(Loader(CustomTxtName,sizeof(CustomTxtName))) RETURN(1)
  LoadCustomTxt(0,0);
  RETURN(0)
}

extern "C"{ 
__declspec( naked ) void Exiter(void){
  __asm{
//    mov  eax,ebx
    sub  eax,ebx
//    inc  eax
    mov  [eax],eax
  }
  //_exit();
//  ExitProcess(0);
//  TerminateProcess();
/*
  __asm{
//int 3
    push -1
    mov  eax,fs:[0x18]
    mov  eax,[eax+0x20]
    push eax
    mov  eax,0xE0
    mov  edx,esp
    int  0x2E
    ret  8
  }
*/
}

}
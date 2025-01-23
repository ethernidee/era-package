#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "txtfile.h"
#include "service.h"
#include "casdem.h"
#include "common.h"
#include "monsters.h"
#include "erm.h"
#include "b1.h"
#include "crexpo.h"
#define __FILENUM__ 4

_Date_    *CurDate;
int   IDummy;
Dword DDummy;
char  CDummy;
Byte  BDummy;
Byte *BPDummy;
char *CPDummy;
int  *IPDummy;

static char *FileList[]={
  "undefined", //0
  "erm",       //1
  "herospec",  //2
  "service",   //3
  "common",    //4
  "casdem",    //5
  "monsters",  //6
  "womo",      //7
  "b1",        //8
  "anim",      //9
  "sound",     //10
  "ai",        //11
  "npc",       //12
  "Setup",     //13
  "String",    //14
  "CrExpo",    //15
  "Arts",      //16
  "txtfile",   //17
  "timer",     //18 3.59+
  0
};

__declspec( naked ) void GoExitW(void){
  //_exit();
  __asm lea ecx,Exiter+7234
  __asm sub ecx,8000
  __asm sub ecx,7234-8000
  __asm jmp ecx;
}

void *Alloc(int zsize)
{ 
#include "templ.h"
void *po;
  __asm{
    mov    eax,zsize
    push   eax
    mov    eax,0x617492
    call   eax
    add    esp,4
    mov    po,eax
  }
  if(po==0){ MError("Cannot allocate memory."); }
  RETURN(po);
}

void Free(void *po)
{
#include "templ.h"
  if(po==0) RETURNV;
  __asm{
    mov    edx,po
    push   edx
    mov    eax,0x60B0F0
    call   eax
    add    esp,4
  }
  RETURNV;
}

int MesMan(_AMes_ *mp,char *mes,int zsize)
{
#include "templ.h"
  int i;
  char *d,*s,*c,bt;
  if(mes==0){ // ����������
    __asm{
      mov    ebx,mp
      sub    ebx,4  // ������� �� ���������, ������� �����
      push   1
      mov    ecx,ebx
      mov    eax,0x404130 // ����������
      call   eax
    }
    RETURN(0);
  }
  s=mes; c=0;
  if(zsize==0){
    if(mes[0]==STRCH){
      i=0;
      do{ bt=mes[++i]; if(bt==0){ MError("\"MesMan\"-unexpected end of message."); RETURN(0); }
      }while(bt!=STRCH);
      c=&mes[i];
      *c=0;
      zsize=i;
      s=&mes[1];
    }else{
      zsize=StrLen(mes)+1;
    }
  }
  __asm{
    mov    esi,zsize
    mov    ebx,mp
    sub    ebx,4  // ������� �� ���������, ������� �����
    mov    eax,[ebx+0xC] // m->a
    cmp    eax,0x1F
    ja     m1
    cmp    eax,esi // ��� �������
    jnb    m2
  }
m1: // ������ ����� > 1F
  __asm{
    push   1
    mov    ecx,ebx
    mov    eax,0x404130 // ����������
    call   eax
    push   esi
    mov    ecx,ebx
    mov    eax,0x404B80 // ��������
    call   eax
  }
m2: // ����� ����������
  d=mp->m.s;
  for(i=0;i<zsize;i++){
    bt=d[i]=s[i];
    if(bt==0) break;
  }
  mp->m.l=i;
  if(c!=0){ *c=STRCH; RETURN(c-mes); }
  else RETURN(i);
}
int M_MDisabled;
int M_MDisabledNext;
int Message(char *zmes,int n,int showtime)
/*
  1-���������
  2-������ 
  4-���� �� ������ �����
  7-������� �������
 10-����� � ������� � ����������
*/
{
#include "templ.h"
  __asm{
    mov  ecx,zmes
    push 0         // SType 3 : 0 
    push -1        // Type 3  : -1
    push showtime  //0
    push -1        // Par ???
    push 0         // SType 2
    push -1        // Type 2
    push 0         // SType 1
    push -1        // Type 1
    push -1        // y
    push -1        // x
    mov eax,0x4f6C00
    mov edx,n
    call eax
  }
  __asm{
    mov eax,0x6992D0
    mov ecx,[eax]
    mov eax,[ecx+0x38]
    mov IDummy,eax    
  }  
  RETURN(IDummy);
}

static Dword C4ME_EBPval;
__declspec( naked ) void Check4MessageEnable(void)
{
  _EBP(C4ME_EBPval);
  __asm pusha
    GLB_DisableMouse=0;
    if(M_MDisabled){
    __asm{
      mov    eax,M_MDisabledNext
      mov    M_MDisabled,eax
      popa
      mov    eax,C4ME_EBPval
//      mov    eax,[eax]

      mov    esp,eax
      pop    ebp
      ret    0x28
    }
  }
  __asm popa
  __asm mov eax,fs:[0]
  __asm ret
}
static int i2a_eax;
int a2i(char *val)
{
#include "templ.h"
  __asm{
    mov    eax,val
    push   eax
    mov    eax,0x6184D9
    call   eax
    add    esp,4
    mov    i2a_eax,eax
  }
  RETURN(i2a_eax);
}

int i2a(int val,char *str)
{
#include "templ.h"
  int i=0,k,d;
  char ch,ds[16];

  if(val<0){ val=-val; str[i]='-'; i++; }
  for(k=0;k<10;k++){
    d=val%10;
    ds[9-k]=(char)d;
    val/=10;
  }
  for(k=0;k<10;k++){ if(ds[k]!=0) goto l_nz; }
  // ��� ����
  k=9; // ����� ���� �����
l_nz:
  for(;k<10;k++,i++){
      ch=ds[k];
      str[i]=(char)(ch+'0');
  }
  RETURN(i);
}

int f2a(float val,char *str)
{
  #include "templ.h"
  int i=0,k,d,vali;
  char ch,ds[32];

  if(val<0){ val=-val; str[i]='-'; i++; }
  vali=(int)(val*1000.0+0.5);
  for(k=0;k<20;k++){
    d=vali%10;
    ds[19-k]=(char)d;
    vali/=10;
  }
  for(k=0;k<16;k++){ if(ds[k]!=0) goto l_nz; }
  // ��� ����
  k=16; // ����� ���� ����� ����� �������
l_nz:
  for(;k<20;k++,i++){
      ch=ds[k];
      if(k==17){
        str[i++]=(char)('.');
      }
      str[i]=(char)(ch+'0');
  }
  RETURN(i);
}

int a2a(char *src,char *str)
{
  #include "templ.h"
  int  i;
  char ch;

  for(i=0;;i++){
    ch=src[i];
    if(ch==0) break; // 0 �� ��������
    str[i]=src[i];
  }
  RETURN(i);
}
_PlayerSetup_ *GetPlayerSetup(int owner)
{
  #include "templ.h"
  _PlayerSetup_ *zret;
  int shifter=owner*0x168+0x20AD0;
  __asm{
    mov    eax,BASE
    mov    eax,[eax]
    add    eax,shifter
    mov    zret,eax
  }
  RETURN((_PlayerSetup_ *)zret);
}

int *GetResPo(int Player,int Nres)
{
  #include "templ.h"
  if((Nres<0)||(Nres>6)) RETURN(0);
  int zret;
  if(Player==-1){
    __asm mov    eax,0x69CCF4
    __asm mov    eax,[eax]
    _EAX(Player);
  }
  __asm{
    mov    esi,Nres
    mov    eax,Player
    mov    edi,BASE
    mov    edi,[edi]
    lea    edx,[eax+4*eax]
    lea    edx,[edx+8*edx]
    lea    edx,[esi+2*edx]
    lea    edx,[edi+4*edx+0x20B6C]
//    mov    eax,dword ptr [edx]
    mov    zret,edx
  }
  RETURN((int *)zret);
}

int GetRes(int Player,int Nres)
{
  #include "templ.h"
  int  val;
  int *po;
  po=GetResPo(Player,Nres);
  if(po==0) RETURN(-1);
  val=*po;
  RETURN(val);
}

int CheckRes(int Player,int Nres,int Vres)
{
  #include "templ.h"
  int val;
  val=GetRes(Player,Nres);
  if(val==-1) RETURN(-1);
  if((val+Vres)<0) RETURN(1); // �� �������
  RETURN(0);
}

void AddRes(int Player,int Nres,int Vres)
{
  #include "templ.h"
  int *rp;
  int  val;

  rp=GetResPo(Player,Nres);
  if(rp==0) RETURNV
  val=*rp;
  val+=Vres;
  if(val<0) val=0;  // �� �������
  *rp=val;
  RedrawRes();
  RETURNV
}

void SetRes(int Player,int Nres,int Vres)
{
  #include "templ.h"
  int *rp;
  
  rp=GetResPo(Player,Nres);
  if(rp==0) RETURNV
  *rp=Vres;
  RedrawRes();
  RETURNV
}

int Request0(char *mes,int showtime)
{
  #include "templ.h"
  Message(mes,2,showtime);
  __asm{
    mov eax,0x6992D0
    mov ecx,[eax]
    cmp dword ptr [ecx+0x38],0x00007805 
    jne l_not
  }  
  RETURN(1)
l_not:
  RETURN(0)
}

int Request(char *mes,int l,int showtime)
{
  #include "templ.h"
  mes[l]=0;
  RETURN(Request0(mes,showtime))
}

int RequestPic(char *mes,int ZType,int Btype,int mode,int showtime)
{
  #include "templ.h"
  __asm{
    push   0
    push  -1
    push   showtime
    push  -1
    push   0
    push  -1
    push   Btype
    mov    eax,ZType
    push   eax
    push  -1
    push  -1 // TIME TO SHOW in ms !!! -1=forever
    mov    ecx,mes
    mov    edx,mode
    mov    eax,0x4F6C00
    call   eax
  }
  if(mode!=2) RETURN(0)
  __asm{
    mov eax,0x6992D0
    mov ecx,[eax]
    cmp dword ptr [ecx+0x38],0x00007805 
    jne l_not
  }  
  RETURN(1)
l_not:
  RETURN(0)
}

int Request2Pic(char *mes,int T1,int B1,int T2,int B2,int mode,int showtime)
{
/*
  1-���������
  2-������ 
  4-���� �� ������ �����
  7-������� �������
  10 - ������� ������� (0x7809,0x980A)� ��(-)/���(0x7801)
*/
  #include "templ.h"
  Dword zret;
  __asm{
    push   0
    push  -1
    push   showtime
    push  -1
    push   B2
    push   T2
    push   B1
    push   T1
    push  -1
    push  -1
    mov    ecx,mes
    mov    edx,mode
    mov    eax,0x4F6C00
    call   eax
  }
  if((mode!=2)&&(mode!=7)&&(mode!=10)) RETURN(0)
  __asm{
//    cmp    eax,00007805
//    cmp    eax,00007809
    mov eax,0x6992D0
    mov ecx,[eax]
    mov eax,[ecx+0x38]
  }
  _EAX(zret);
  if(mode==2){ // yes/no
    if(zret==0x7805) RETURN(1) // yes
    RETURN(0)                 // no
  }
  if(mode==10){ // choose and Yes/No
    if(zret==0x7809) RETURN(1) // left
    if(zret==0x780A) RETURN(2) // right
    RETURN(0) // esc
  }
  if(zret==0x7809) RETURN(1) // ������ �����
//  if(ret==0x780A) return 0; // ����. ����� (������)
  RETURN(0)
}

int Request3Pic(char *mes,int T1,int B1,int T2,int B2,int T3,int B3,int mode,int showtime)
{
/*
  1-���������
  2-������
  4-���� �� ������ �����
  7-������� �������
  10 - ������� ������� (0x7809,0x980A,????)� ��(-)/���(0x7801)
*/
  #include "templ.h"
  Dword zret;
  __asm{
    push   B3
    push   T3
    push   showtime
    push  -1
    push   B2
    push   T2
    push   B1
    push   T1
    push  -1
    push  -1 // TIME TO SHOW in ms !!! -1=forever
    mov    ecx,mes
    mov    edx,mode
    mov    eax,0x4F6C00
    call   eax
  }
  if((mode!=2)&&(mode!=7)&&(mode!=10)) RETURN(0)
  __asm{
//    cmp    eax,00007805
//    cmp    eax,00007809
    mov eax,0x6992D0
    mov ecx,[eax]
    mov eax,[ecx+0x38]
  }
  _EAX(zret);
  if(mode==2){ // yes/no
    if(zret==0x7805) RETURN(1) // yes
    RETURN(0)                 // no
  }
  if(mode==10){ // choose and Yes/No
    if(zret==0x7809) RETURN(1) // left
    if(zret==0x780A) RETURN(2) // right
    RETURN(0) // esc
  }
  if(zret==0x7809) RETURN(1) // ������ �����
//  if(ret==0x780A) return 0; // ����. ����� (������)
  RETURN(0)
}

int GetCurDate(void){
  #include "templ.h"
  _Date_ *p=CurDate;
  RETURN(((p->Month-1)*4+p->Week-1)*7+p->Day)
}

void SetCurDate(int Month,int Week,int Day){
  #include "templ.h"
  _Date_ *p=CurDate;
  p->Month=(Word)Month; // 1...
  p->Week=(Word)Week;   // 1...
  p->Day=(Word)Day;     // 1...
  RETURNV
}

void Copy(Byte *src,Byte *dst,int sz)
{
  #include "templ.h"
  int i;
// 3.58
//  if(src==0) return;
//  if(dst==0){
  if(dst==0) RETURNV
  if(src==0){
    for(i=0;i<sz;i++) *dst++=0;
  }else{
    for(i=0;i<sz;i++) *dst++=*src++;
  }
  RETURNV
}

int Random(int ZLow,int ZHigh)
{
  #include "templ.h"
  __asm{
    mov    ecx,ZLow
    mov    edx,ZHigh
    mov    eax,0x50C7C0
    call   eax
    mov    IDummy,eax
  }
  RETURN(IDummy)
}

int Abs(int v)
{
  if(v<0) v=-v;
  return v;
}

///////////////////////////////////////
// String functions
int StrCmp(char *src,char *dst)
{
  #include "templ.h"
  if((src==0)||(dst==0)) RETURN(0)
  if((*src==0)&&(*dst!=0)) RETURN(0)
  while(*src!=0){
    if(*src++!=*dst++) RETURN(0)
  }
  RETURN(1)
}
int StrNCmp(Byte *src,Byte *dst,int len)
{
  #include "templ.h"
  for(int i=0;i<len;i++){
    if(src[i]!=dst[i]) RETURN(0)
  }
  RETURN(1)
}

int StrSkipLead(char *str,int start)
{
  #include "templ.h"
  int i;
  if(str==0) RETURN(-1)
  for(i=start;;i++){
    switch(str[i]){
      case  ' ':
      case 0x0D:
      case 0x0A:
      case 0x09: continue;
      case 0:    RETURN(-1)
      default:   break;
    }
    RETURN(i)
  }
}
int StrSkipTrailer(char *str,int start)
{
  #include "templ.h"
  int i;
  if(str==0) RETURN(-1)
  for(i=start;i>=0;i--){
    switch(str[i]){
      case  ' ':
      case 0x0D:
      case 0x0A:
      case 0x09:
      case 0:    continue;
      default:   break;
    }
    RETURN(i)
  }
  RETURN(0)
}
int StrWordEnd(char *str,int start)
{
  #include "templ.h"
  int i;
  if(str==0) RETURN(-1)
  for(i=start;;i++){
    switch(str[i]){
      case  ' ':
      case 0x0D:
      case 0x0A:
      case 0x09:
      case 0:
        RETURN(i)
      default: continue;
    }
  }
}
int StrCmpExt(char *src,char *dst)
{
  #include "templ.h"
  int i,ie,j,je,cs,cd;
  if((src==0)||(dst==0)) RETURN(0)
  if((*src==0)&&(*dst!=0)) RETURN(0)
  i=ie=j=je=0;
  while(1){
    i=StrSkipLead(src,i);
    j=StrSkipLead(dst,j);
    if((i==-1)&&(j!=-1)) RETURN(0) // �������� ��������, � �������� ���
    if((j==-1)&&(i!=-1)) RETURN(0) // �������� ��������, � �������� ���
    if((i==-1)&&(j==-1)) RETURN(1) // ����� �� �����
    ie=StrWordEnd(src,i);
    je=StrWordEnd(dst,j);
    if((je-j)!=(ie-i)) RETURN(0) // ����� ������ �����
    for(;i<ie;i++,j++){
      cs=src[i]; cd=dst[j];
      if((cs>='a')&&(cs<='z')) cs-=(char)('a'-'A');
      if((cd>='a')&&(cd<='z')) cd-=(char)('a'-'A');
      if(cs!=cd) RETURN(0) // ������� ������
    }
  }
}

static char S2[1000],D2[1000];
int Serch4Substring(char *S,char *D)
{
  #include "templ.h"
  int i,i2,j,j2;
  StrCopy(S2,999,S); S2[999]=0;
  StrCopy(D2,999,D); D2[999]=0;
  ToUpper(S2);
  ToUpper(D2);
  i=StrSkipLead(S2,0);
  j=StrSkipLead(D2,0);
  if((i==-1)&&(j!=-1)) RETURN(0) // �������� ��������, � �������� ���
  if((j==-1)&&(i!=-1)) RETURN(0) // �������� ��������, � �������� ���
  if((i==-1)&&(j==-1)) RETURN(0) // ����� �� �����
  j2=StrSkipTrailer(D2,998);
  if(j2<=j) RETURN(0) // ��� ������ ������
  D2[j2+1]=0;
  for(i2=i;((S2[i2]!=0)&&(i2<998));i2++){
    if(StrCmp(&D2[j],&S2[i2])) RETURN(1)
  }
  RETURN(0)
}

int StrLen(char *src)
{
  #include "templ.h"
  int i=0;
  while(src[i]!=0) i++;
  RETURN(i)
}  

void StrCopy(char *dst,int len,char *src)
{
  #include "templ.h"
  char c;
  int  i=0;
  if(src==0){
    dst[0]=0;
    RETURNV
  }
  while(i<len){
    c=src[i]; dst[i]=c; i++;
    if(c==0) break;
  }
  dst[len-1]=0;
  RETURNV
}

void StrCanc(char *dst,int len,char *s1,char *s2)
{
  #include "templ.h"
  char c;
  int  i=0,j=0;
  while(i<len){
    c=s1[i]; dst[i]=c; 
    if(c==0) break;
    i++;
  }
  while(i<len){
    c=s2[j]; dst[i]=c; 
    if(c==0) break;
    i++; j++;
  }
  dst[len-1]=0;
  RETURNV
}

void ToUpper(char *str)
{
  #include "templ.h"
  char c;
  for(int i=0;;i++){
    c=str[i];
    if(c==0) break;
    if((c>='a')&&(c<='z')){
      c-=(char)('a'-'A');
      str[i]=c;
    }
    if((c>='�')&&(c<='�')){
      c-=(char)('�'-'�');
      str[i]=c;
    }
  }
  RETURNV
}

void HexToUpper(char *str)
{
  #include "templ.h"
  char c;
  for(int i=0;;i++){
    c=str[i];
    if(c==0) break;
    if((c>='a')&&(c<='x')){
      c-=(char)('a'-'A');
      str[i]=c;
    }
  }
  RETURNV
}

void ToLower(char *str)
{
  #include "templ.h"
  char c;
  for(int i=0;;i++){
    c=str[i];
    if(c==0) break;
    if((c>='A')&&(c<='Z')){
      c+=(char)('a'-'A');
      str[i]=c;
    }
    if((c>='�')&&(c<='�')){
      c+=(char)('�'-'�');
      str[i]=c;
    }
  }
  RETURNV
}

void CutWord(char *str)
{
  #include "templ.h"
  int  i;
  char c;
  
  for(i=0;;i++){
    c=str[i];
    switch(c){
      case ' ':
      case 0x0A:
      case 0x0D:
      case 0x09:
        str[i]=0;
        RETURNV
      case 0:
        RETURNV
    }
  }
//  RETURNV
}

void SetMem(void *Mem,int Sz,Byte Val){
  #include "templ.h"
  Byte *p=(Byte *)Mem;
  if(p==0){
    MError("SetMem: Null pointer.");
    RETURNV
  }
  for(int i=0;i<Sz;i++) p[i]=Val;
  RETURNV
}
/////////////////////////////
int LoadFile16k(char *name,char *mode)
{
  #include "templ.h"
  __asm{
    mov   edx,mode
    mov   ecx,name
    mov   eax,0x6067E0
    call  eax
    mov   IDummy,eax
  }
  RETURN(IDummy)
}

/////////////////////////////
int CurrentUser(void)
{
  #include "templ.h"
  __asm mov  eax,0x69CCF4
  __asm mov  eax,[eax]
  __asm mov  IDummy,eax
  RETURN(IDummy)
}

int QuickBattle(void)
{
  #include "templ.h"
  __asm mov  eax,0x6987CC
  __asm mov  eax,[eax]
  __asm mov  IDummy,eax
  RETURN(IDummy)
}
void SetQuickBattle(int value)
{
  #include "templ.h"
  __asm mov  eax,value
  __asm mov  edx,0x6987CC
  __asm mov  [edx],eax
  RETURNV
}

void MakeLine(int x1,int y1,int x2,int y2,int l,void (*fun)(int x,int y,int l))
{
  #include "templ.h"
  int dx,dy,i,j,t,fl,fl2,e;

  if((x1==x2)&&(y1==y2)) RETURNV
  dx=abs(x2-x1); 
  dy=abs(y2-y1); 
  if(dy>dx){ fl=1; t=dx; dx=dy; dy=t; t=x1; x1=y1; y1=t; t=x2; x2=y2; y2=t;} else fl=0;
  if(x1>x2){/*t=x1;*/ x1=x2; /*x2=t;*/ t=y1; y1=y2; y2=t;}
  if(y1>y2) fl2=-1; else fl2=1;
  if(fl) fun(y1,x1,l); else fun(x1,y1,l);
  for(i=0,j=0,e=dx;i<=dx;i++){
    e-=dy*2;
    if(e<0){e+=dx*2; j+=fl2;}
    if(fl) fun(y1+j,x1+i,l); else fun(x1+i,y1+j,l);
  }
  RETURNV
}

_MapItem_ *GetMapItem(int x,int y,int l)
{
  #include "templ.h"
  int MapSize;
  _MapItem_  *MIp0,*MIp;
  __asm{
    mov   ecx,BASE
    mov   ecx,[ecx]
    mov   eax,[ecx+0x1FC40]
    mov   MIp0,eax
    mov   eax,[ecx+0x1FC44]
    mov   MapSize,eax
  }
  if(x<0) x=0; if(x>=MapSize) x=MapSize-1;
  if(y<0) y=0; if(y>=MapSize) y=MapSize-1;
  if(l<0) l=0; if(l>1) l=1;
  MIp=&MIp0[x+(y+l*MapSize)*MapSize];
  RETURN(MIp)
}

_MapItem_ *GetMapItem2(Dword MixPos)
{
  #include "templ.h"
  int x,y,l;
  MixedPos(&x,&y,&l,MixPos);
  RETURN(GetMapItem(x,y,l))
}

int GetMapItemModif(_MapItem_ *mp)
{
  #include "templ.h"
  __asm{
    mov    ecx,mp
    mov    eax,0x4FD470
    call   eax
    mov    IDummy,eax
  }
  RETURN(IDummy)
}

_MapItem_ *GetMapItem0(void)
{
  #include "templ.h"
  _MapItem_  *MIp0;
  __asm{
    mov   ecx,BASE
    mov   ecx,[ecx]
    mov   eax,[ecx+0x1FC40]
    mov   MIp0,eax
  }
  RETURN(MIp0)
}

int GetMapSize(void)
{
  #include "templ.h"
  int MapSize;
  __asm{
    mov   ecx,BASE
    mov   ecx,[ecx]
    mov   eax,[ecx+0x1FC44]
    mov   MapSize,eax
  }
  RETURN(MapSize)
}

int GetMapLevels(void)
{
  #include "templ.h"
  char MapLevels;
  __asm{
    mov   ecx,BASE
    mov   ecx,[ecx]
    mov   al,[ecx+0x1FC48]
    mov   MapLevels,al
  }
  RETURN(MapLevels)
}

Byte *LoadPCX(char *PCXName)
{
  #include "templ.h"
  __asm{
    mov  ecx,PCXName
    mov  eax,0x55AA10
    call eax
    mov  BPDummy,eax
  }
  RETURN(BPDummy)
}

int EmptyPlace(_MapItem_ *mp)
{
  #include "templ.h"
  Dword Dwr;
  Byte  Hi,Lo;
// �������� �� ����������� ����������
  __asm{
    mov    esi,mp        // esi -> ������ �� �����
    mov    ax,[esi+0x0C] // ??
    mov    Lo,al
    mov    Hi,ah
  }
// �������� ���������
  if(Hi & 0x10) goto l_exit;  // ���-�� ���� (������ ������/�����)
  if(!(Lo & 0x40)) goto l_exit;
  __asm{
    mov    esi,mp
    mov    eax,[esi+0x04]
    and    eax,0xFF
    mov    Dwr,eax
  }
  if(Dwr==0x08) goto l_exit; // ����
  if(Dwr==0x09) goto l_exit; // ��� �����������
  __asm{
    mov    esi,mp
    mov    eax,[esi+0x1E]
    mov    Dwr,eax
  }
  if(Dwr==0x1A) goto l_exit; // LE 
  RETURN(1) // ������ ������
l_exit:
  RETURN(0)
}

int EmptyPlaceWater(_MapItem_ *mp)
{
  #include "templ.h"
  Dword Dwr;
  Byte  Hi,Lo;
// �������� �� ����������� ����������
  __asm{
    mov    esi,mp        // esi -> ������ �� �����
    mov    ax,[esi+0x0C] // ??
    mov    Lo,al
    mov    Hi,ah
  }
// �������� ���������
  if(Hi & 0x10) goto l_exit;
  if(!(Lo & 0x40)) goto l_exit;
  __asm{
    mov    esi,mp
    mov    eax,[esi+0x04]
    and    eax,0xFF
    mov    Dwr,eax
  }
  if(Dwr!=0x08) goto l_exit; // �� ����
  __asm{
    mov    esi,mp
    mov    eax,[esi+0x1E]
    mov    Dwr,eax
  }
  if(Dwr==0x1A) goto l_exit;
  RETURN(1) // ������ ������
l_exit:
  RETURN(0)
}

int EmptyPlaceAny(_MapItem_ *mp)
{
  #include "templ.h"
  Dword Dwr;
  Byte  Hi,Lo;
// �������� �� ����������� ����������
  __asm{
    mov    esi,mp        // esi -> ������ �� �����
    mov    ax,[esi+0x0C] // ??
    mov    Lo,al
    mov    Hi,ah
  }
// �������� ���������
  if(Hi & 0x10) goto l_exit;
  if(!(Lo & 0x40)) goto l_exit;
  __asm{
    mov    esi,mp
    mov    eax,[esi+0x04]
    and    eax,0xFF
    mov    Dwr,eax
  }
  if(Dwr==0x09) goto l_exit; // ��� �����������
  __asm{
    mov    esi,mp
    mov    eax,[esi+0x1E]
    mov    Dwr,eax
  }
  if(Dwr==0x1A) goto l_exit;
  RETURN(1) // ������ ������
l_exit:
  RETURN(0)
}

int EmptyPlace2(_MapItem_ *mp)
{
  #include "templ.h"
  if(EmptyPlace(mp)==0) RETURN(0)
//  if(mp->Attrib&0x01) return 0;
  RETURN(1)
}

void Hero2Town(Dword TownManager)
{
  #include "templ.h"
  __asm{
    mov    ecx,TownManager
    mov    eax,0x5D5550
    call   eax
  }
  RETURNV
}

void Town2Hero(Dword TownManager)
{
  #include "templ.h"
  __asm{
    mov    ecx,TownManager
    mov    eax,0x5D5620
    call   eax
  }
  RETURNV
}

void Town2Hero0(_CastleSetup_ *CStr)
{
  #include "templ.h"
  __asm{
    mov    ecx,CStr
    mov    eax,0x5BE790
    call   eax
  }
  RETURNV
}

_Hero_ *GetHeroStr(int n)
{
  #include "templ.h"
  _Hero_ *hp,*chp;
  if((n<0)||(n>=HERNUM)) RETURN(0)
  __asm{
    mov  eax,BASE
    mov  eax,[eax]
    add  eax,0x21620
    mov  hp,eax
  }
  chp=&hp[n];
  RETURN(chp)
}

_Hero_ *FindHeroNum(int x,int y,int l)
{
  #include "templ.h"
  int i;
  _Hero_ *hp;
  for(i=0;i<HERNUM;i++){
    hp=GetHeroStr(i);
    if(hp->x!=x) continue;
    if(hp->y!=y) continue;
    if(hp->l!=l) continue;
    RETURN(hp)
  }
  RETURN(0)
}

void KillHero(int Number)
{ // 4E1C29
  #include "templ.h"
  _Hero_ *chp;
  if(Number>=HERNUM) RETURNV;
  chp=GetHeroStr(Number);
  __asm{
    mov    ecx,chp
    push   0
    push   1
    mov    eax,0x4DA130
    call   eax
  }
  RETURNV
}


static char CrTrWoGName[]="ZCrTrait.txt";
//static char CrTrSoDName[]="CrTraits.txt";
static char CrTrSoDName[]="ZCrTrait.txt";
char LoadCrTraits(int wog)
{
  #include "templ.h"
  char *name,dummy;
  if(wog) name=CrTrWoGName;
  else    name=CrTrSoDName;
  StrCopy((char *)0x675514,15,name);
  __asm{
    mov   eax,0x47ABC0
    call  eax
    mov   dummy,al
  }
  RETURN(dummy)
}

int IsAI(int gamer)
{
  #include "templ.h"
  char r,*hspo;

  if((gamer<0)||(gamer>7)) RETURN(1)
  __asm{
    mov  eax,BASE
    mov  eax,[eax]
    add  eax,0x20AD0
    mov  hspo,eax
  }
  r=hspo[0x168*gamer+0xE2];
  if(r==0) RETURN(1) else RETURN(0)
//  4BAA40
//  mov    al,[ecx+000000E2]
//  test   al,al
//  je     H32.004BAA57 (004BAA57)
//  mov    al,[ecx+000000E1]
//  test   al,al
//  je     H32.004BAA57 (004BAA57)
//  mov    al,01
//  ret
//  xor    al,al
//  ret
}
// ��������� �� ����������� ����� � 0x588600
int IsThis(int gamer)
{
  #include "templ.h"
  char r,*hspo;

  if((gamer<0)||(gamer>7)) RETURN(0)
  __asm{
    mov  eax,BASE
    mov  eax,[eax]
    add  eax,0x20AD0
    mov  hspo,eax
  }
  r=hspo[0x168*gamer+0xE1];
  RETURN(r)
}
int HasAnyAtThisPC(void){
  #include "templ.h"
  for(int i=0;i<8;i++) if(IsThis(i)) RETURN(1);
  RETURN(0)
}
// ���������� ���������� ������������� ������, ���� ����
int CurrentUserSecond(void)
{
  #include "templ.h"
  __asm{
    mov    ecx,BASE
    mov    ecx,[ecx]
    mov    eax,0x4CE6E0
    call   eax
    mov    IDummy,eax
  }
  RETURN(IDummy)
}

void SetAI(int gamer,int AI_gm)
{
  #include "templ.h"
  char *hspo;
  
  if((gamer<0)||(gamer>7)) RETURNV
  __asm{
    mov  eax,BASE
    mov  eax,[eax]
    add  eax,0x20AD0
    mov  hspo,eax
  }
  if(AI_gm){
    hspo[0x168*gamer+0xE2]=0;
  }else{
    hspo[0x168*gamer+0xE2]=1;
  }  
  RETURNV
}

void ThisIs(int gamer,int ThisGamer)
{
  #include "templ.h"
  char *hspo;

  if((gamer<0)||(gamer>7)) RETURNV
  __asm{
    mov  eax,BASE
    mov  eax,[eax]
    add  eax,0x20AD0
    mov  hspo,eax
  }
  if(ThisGamer){
    hspo[0x168*gamer+0xE1]=1;
  }else{
    hspo[0x168*gamer+0xE1]=0;
  }
  RETURNV
}

int GetTeam(int gamer)
{
  #include "templ.h"
  char *tpo;
  if((gamer<0)||(gamer>7)) RETURN(-1)
  __asm{
    mov  eax,BASE
    mov  eax,[eax]
    add  eax,0x1F879
    mov  tpo,eax
  }
  RETURN(tpo[gamer])
}

void SetTeam(int gamer,char team)
{
  #include "templ.h"
  char *tpo;
  if((gamer<0)||(gamer>7)) RETURNV
  __asm{
    mov  eax,BASE
    mov  eax,[eax]
    add  eax,0x1F879
    mov  tpo,eax
  }
  tpo[gamer]=team;
  RETURNV
}
  
int IsTeam(int gamer1, int gamer2)
{
  #include "templ.h"
  int t1,t2;
  if((gamer1<0)||(gamer1>7)) RETURN(0)
  if((gamer2<0)||(gamer2>7)) RETURN(0)
  t1=GetTeam(gamer1);
  t2=GetTeam(gamer2);
  if((t1==-1)||(t2==-1)) RETURN(0)
  if(t1==t2) RETURN(1) else RETURN(0)
}

_CastleSetup_ *GetCastleBase(void)
{
  #include "templ.h"
  _CastleSetup_ *zret;
  __asm{
    mov  eax,BASE
    mov  eax,[eax]
    add  eax,0x21614
    mov  eax,[eax]
    mov  zret,eax
  }
  RETURN(zret)
}

int GetCastleNum(void)
{
  #include "templ.h"
  _CastleSetup_ *strt,*end;
  __asm{
    mov  eax,BASE
    mov  ecx,[eax]
    add  ecx,0x21614
    mov  eax,[ecx]
    mov  strt,eax
    mov  eax,[ecx+4]
    mov  end,eax
  }
  RETURN(end-strt)
}

_CastleSetup_ *FindCastle(int x,int y,int l)
{
  #include "templ.h"
  int   i,cn;
  _CastleSetup_ *cst;

  cst=GetCastleBase();
  cn=GetCastleNum();
  for(i=0;i<cn;i++,cst++){
    if(cst->x!=x) continue;
    if(cst->y!=y) continue;
    if(cst->l!=l) continue;
    RETURN(cst)
  }
  RETURN(0)
}

int IsCastleSetup(_CastleSetup_ *cs)
{
  #include "templ.h"
  int   i,cn;
  _CastleSetup_ *cst;

  cst=GetCastleBase();
  cn=GetCastleNum();
  for(i=0;i<cn;i++,cst++){
    if(cst==cs) RETURN(1) // �����
  }
  RETURN(0) // ���
}

_Dwelling_ *GetDwellingBase(void)
{
  #include "templ.h"
  _Dwelling_ *zret;
  __asm{
    mov  eax,BASE
    mov  eax,[eax]
    add  eax,0x4E39C
    mov  eax,[eax]
    mov  zret,eax
  }
  RETURN(zret)
}

int GetDwellingNums(void)
{
  #include "templ.h"
  _Dwelling_ *strt,*end;
  __asm{
    mov  eax,BASE
    mov  ecx,[eax]
    add  ecx,0x4E39C
    mov  eax,[ecx]
    mov  strt,eax
    mov  eax,[ecx+4]
    mov  end,eax
  }
  RETURN(end-strt);
}

_Dwelling_ *FindDwelling(int x,int y,int l)
{
  #include "templ.h"
  int         i,cn;
  _Dwelling_ *dwst;

  dwst=GetDwellingBase();
  cn=GetDwellingNums();
  for(i=0;i<cn;i++,dwst++){
    if(dwst->x!=x) continue;
    if(dwst->y!=y) continue;
    if(dwst->l!=l) continue;
    RETURN(dwst)
  }
  RETURN(0)
}

Dword PosMixed(int x,int y,int l)
{
  #include "templ.h"
  Dword p;
  p=(((Dword)y)<<16)+(Dword)x;
  if(l) p+=0x04000000;
  RETURN(p)
}  

void Map2Coord(_MapItem_ *Mi,int *x,int *y,int *l)
{
  #include "templ.h"
  int        size,n;
  _MapItem_ *Mi0;

  Mi0=GetMapItem0();
  size=GetMapSize();
  n=Mi-Mi0;
  *l=n/(size*size);
  n=n%(size*size);
  *y=n/size;
  *x=n%size;
  RETURNV
}

void MixedPos(int *x,int *y,int *l,Dword pos)
{
  #include "templ.h"
  if(pos>=0x04000000) *l=1; else *l=0;
  *x=pos&0x000003FF;
  *y=(pos>>16)&0x03FF;
  RETURNV
}  


void HideHero(_Hero_ *Hp)
{
//    Hr->Hidden=1;
  #include "templ.h"
  __asm{
    mov    ecx,Hp
    mov    eax,0x4D7950
    call   eax
  } 
  RETURNV
}  

void ShowHero(_Hero_ *Hp)
{
  #include "templ.h"
  __asm{
    mov    ecx,Hp
    mov    eax,[ecx+0x1A]
    push   eax    // ������ - �����
    push   0x22   // ��� - �����
    mov    eax,0x4D7840
    call   eax
  } 
  RETURNV
}  

void JumpHero(_Hero_ *Hp,int nx,int ny,int nl,int flag)
{
  #include "templ.h"
  int   Owner,CurUser;
  Dword po,pm/*,hspo,oruspo*/;
  Owner=Hp->Owner;
  CurUser=CurrentUser();
  if(flag==2){ // 3.57m2 ������ ������ ����������
    Hp->x=(Word)nx;
    Hp->y=(Word)ny;
    Hp->l=(Word)nl;
    RETURNV
  }
  if((Owner!=CurUser)&&(flag==0)){
    HideHero(Hp);
    Hp->x=(Word)nx;
    Hp->y=(Word)ny;
    Hp->l=(Word)nl;
    ShowHero(Hp);
    RETURNV
  }
  if(flag==3){ // 3.58 - ������� ��� �����
//    HideHero(Hp);
    Hp->x=(Word)nx;
    Hp->y=(Word)ny;
    Hp->l=(Word)nl;
//    ShowHero(Hp);
    RETURNV
  }
  po=0x67775C;
  pm=PosMixed(nx,ny,nl);
  __asm{
    mov   ecx,0x6992B8
    mov   ecx,[ecx]
    mov   edx,po
    mov   ebx,Hp
    mov   eax,pm
    push  0
    push  1
    push  0
    push  edx
    push  eax
    push  ebx
    mov   eax,0x41DAB0
    call  eax
  }
  RETURNV
}

int Zsprintf2(_ZPrintf_ *ZFStr,char *Format,Dword a1,Dword a2)
{
  #include "templ.h"
  __asm{
    mov   edx,a2
    mov   ecx,a1
    mov   ebx,Format
    mov   eax,ZFStr
    push  edx
    push  ecx
    push  ebx
    push  eax
    mov   eax,0x50C7F0
    call  eax
    add   esp,0x10
    mov   IDummy,eax
  }
  RETURN(IDummy)
// 001A2225: mov    eax,000691260
// 001A222A: mov    ecx,[edi][0000000CC]
// 001A2230: lea    edx,[ebp][-0078]
// 001A2233: sub    esi,ecx
// 001A2235: push   esi
// 001A2236: push   eax
// 001A2237: push   0006884A0
// 001A223C: push   edx
// 001A223D: call   00010C7F0   ---------- (2)
// 001A2242: add    esp,010
// 001A2245: mov    eax,[eax][00004]
// 001A2248: mov    d,[ebp][-0004],000000003
// 001A224F: test   eax,eax
// 001A2251: jne    0001A2258   ---------- (3)
}
int Zsprintf3(_ZPrintf_ *ZFStr,char *Format,Dword a1,Dword a2,Dword a3)
{
  #include "templ.h"
  __asm{
    mov   edx,a2
    mov   ecx,a1
    mov   ebx,Format
    mov   eax,ZFStr
    push  a3
    push  edx
    push  ecx
    push  ebx
    push  eax
    mov   eax,0x50C7F0
    call  eax
    add   esp,0x14
    mov   IDummy,eax
  }
  RETURN(IDummy)
}
//static char Trm_buf[1000];
/*
#ifdef RELEASE
void Terminate(char *Mes)
{
  if(Mes==0){
    StrCopy(Trm_buf,1000,"Initialization failed.");
  }else{
    StrCanc(Trm_buf,1000,"Initialization failed.\nThe reason is : ",Mes);
  }
  __asm{
    lea   ecx,Trm_buf
    mov   eax,0x4F3D20
    call  eax
  }
}
#else
*/
_ZPrintf_ TermStruct;
void Terminate(char *File,int Line)
{
  #include "templ.h"
  char *string;
  if(File==0){
    if(WoGType){ Zsprintf2(&TermStruct,"������. ������� �� �������.",0,0); }
    else{ Zsprintf2(&TermStruct,"Fault. No reason.",0,0); }
  }else{
//    if(Line==0){ // File -> ������ �����
//      if(WoGType){ Zsprintf(&TermStruct,"������. \n\t���: %s",(Dword)File); }
//      else{ Zsprintf2(&TermStruct,"Fault. \n\tFile: %s\n\tLine : %i",(Dword)File,(Dword)Line); }
//    }else{
      if(WoGType){ Zsprintf2(&TermStruct,"������. \n\t����: %s\n\t������ : %i",(Dword)File,(Dword)Line); }
      else{ Zsprintf2(&TermStruct,"Fault. \n\tFile: %s\n\tLine : %i",(Dword)File,(Dword)Line); }
//    }
  }
  string=TermStruct.Str;
  STOP
  __asm{
    mov   ecx,string
    mov   eax,0x4F3D20
    call  eax
  }
}

void _Error(int File,int Line)
{
  #include "templ.h"
  if(File==0){
    if(WoGType){ Zsprintf2(&TermStruct,"������ ���������� ERM. ������� �� �������.",0,0); }
    else{ Zsprintf2(&TermStruct,"ERM syntax Error. No reason.",0,0); }
  }else{
    if(WoGType){ Zsprintf2(&TermStruct,"������ ���������� ERM. \n\t����: %s\n\t������ : %i",(Dword)FileList[File],(Dword)Line); }
    else{ Zsprintf2(&TermStruct,"ERM syntax Error. \n\tFile: %s\n\tLine : %i",(Dword)FileList[File],(Dword)Line); }
  }
  Message(TermStruct.Str,1);
  RETURNV
}
char *ErrStringPo=0;
static char ME_Buf[2000];
void _MError(int File,int Line,char *Txt)
{
  #include "templ.h"
  PL_ERMError=1;
  if(PL_ERMErrDis) RETURNV
  if(Txt==0){
    _Error(File,Line);
  }else{
    if(WoGType){ Zsprintf3(&TermStruct,"������ ���������� ERM.\n\t����: %s\n\t������: %i\n\t�������:\n\t%s\n\n��������� ���� ERM ���������� � WOGERMLOG.TXT (����. ���������)?",(Dword)FileList[File],(Dword)Line,(Dword)Txt); }
    else{ Zsprintf3(&TermStruct,"ERM syntax Error.\n\tFile: %s\n\tLine: %i\n\tReason:\n\t%s\n\nSave all ERM vars to WOGERMLOG.TXT (may take time)?",(Dword)FileList[File],(Dword)Line,(Dword)Txt); }
  }
  if(Request0(TermStruct.Str)){
    if(ErrStringPo!=0){ // 3.58
      DumpERMVars(TermStruct.Str,ErrStringPo); 
    }else{
      DumpERMVars(TermStruct.Str,0); 
    }
  }
  if(ErrStringPo!=0){
    for(int i=0;i<200;i++){
      ME_Buf[i]=ErrStringPo[i]; 
      if(ME_Buf[i]==0) break;
    }
    ME_Buf[199]=0;
    Message(ME_Buf,1);
  }
  RETURNV
}
void _TError(int File,int Line,char *Txt)
{
  #include "templ.h"
  if(Txt==0){
    sprintf(ME_Buf,"Error. \n\tFile: %s\n\tLine : %i",(Dword)FileList[File],(Dword)Line);
  }else{
    if(WoGType){ sprintf(ME_Buf,"������.\n\t����: %s\n\t������: %i\n\t�������:\n\t%s",(Dword)FileList[File],(Dword)Line,(Dword)Txt); }
    else{ sprintf(ME_Buf,"Error.\n\tFile: %s\n\tLine: %i\n\tReason:\n\t%s",(Dword)FileList[File],(Dword)Line,(Dword)Txt); }
  }
  Message(ME_Buf,1);
  RETURNV
}
void DumpMessage(char *txt,int offset){
  #include "templ.h"
  strncpy(ME_Buf,&txt[offset],1999);
  Message(ME_Buf,1);
  RETURNV
}
//#endif

/////////////////////////////////////////
// ��������� ����� �����������
void HideArea(int X,int Y,int Level,int Owner,int Radius)
{
  #include "templ.h"
  __asm{
    mov    eax,X
    mov    ebx,Y
    mov    ecx,Level
    mov    edx,Owner
    push   Radius       // ������ ����������
    push   edx          // ����� �������(�����)
    push   ecx          // level
    push   ebx          // y
    push   eax          // x
    mov    ecx,BASE
    mov    ecx,[ecx]
    mov    eax,0x49D040
    call   eax
// open area around all heroes and towns
    mov    ecx,BASE
    mov    ecx,[ecx]
    mov    eax,0x4C7910
    call   eax
  }  
  RETURNV
}
// �������� ����� �����������
static int SA_Radius;
void ShowArea(int X,int Y,int Level,int Owner,int Radius)
{
  #include "templ.h"
  SA_Radius=Radius;
  __asm{
    mov    eax,X
    mov    ebx,Y
    mov    ecx,Level
    mov    edx,Owner
    push   0
    push   SA_Radius       // ������ ���������
    push   edx          // ����� �������(�����)
    push   ecx          // level
    push   ebx          // y
    push   eax          // x
    mov    ecx,BASE
    mov    ecx,[ecx]
    mov    eax,0x49CDD0
    call   eax
  }  
  RETURNV
}    
// esi -> Hero
// eax = ������ ���������
//00480967 0FBF4E04       movsx  ecx,word ptr [esi+04] // Level
//0048096B 0FBF5602       movsx  edx,word ptr [esi+02] // exY
//0048096F 50             push   eax                   // radius of visability
//00480970 0FBE4622       movsx  eax,byte ptr [esi+22] // Owner (color)
//00480974 50             push   eax                   
//00480975 51             push   ecx
//00480976 8B4DE8         mov    ecx,[ebp-18]
//00480979 0FBF06         movsx  eax,word ptr [esi]
//0048097C 03D1           add    edx,ecx
//0048097E 8B0D38956900   mov    ecx,[00699538]
//00480984 52             push   edx
//00480985 8B55DC         mov    edx,[ebp-24]
//00480988 03C2           add    eax,edx
//0048098A 50             push   eax
//0048098B E840C40100     call   HEROES3.0049CDD0

_HeroInfo_ *GetHIBase(void)
{
  #include "templ.h"
  _HeroInfo_ *zret;
  __asm{ 
    mov eax,0x67DCE8
    mov eax,[eax] 
    mov zret,eax
  } 
  RETURN(zret)
}

Byte *GamerStruc(int hn)
{
  #include "templ.h"
  if(hn==-1){ 
    __asm mov eax,0x69CCFC 
    __asm mov eax,[eax]
    __asm mov BPDummy,eax
    RETURN(BPDummy)
  }  
  if((hn<0)||(hn>7)){ MError("\"GamerStruc\"-wrong player number."); RETURN(0) }
  __asm{
    mov    eax,hn
    lea    eax,[eax+4*eax]
    lea    edx,[eax+8*eax]
    mov    eax,0x699538
    mov    eax,[eax]
    lea    eax,[eax+8*edx+0x20AD0]
    mov    BPDummy,eax
  }
  RETURN(BPDummy)
}

void RedrawMap(void)
{
  #include "templ.h"
  __asm{
    mov    ecx,0x6992B8
    mov    ecx,[ecx]
// �������������� ����� advanture
// ecx -> advManager
    mov    ecx,[ecx+0x44]
// ��������, ���� ����
    or     ecx,ecx
    je     l_not
   push   ecx
    push   1
    push   1
    push   0xFFFFFFFF
    mov    eax,0x4032E0
    call   eax
   pop    ecx
    push   1
    push   1
    push   0xFFFFFFFF
    mov    eax,0x403420
    call   eax
// �������������� ������ ������ ���� �����
    mov    ecx,0x6992B8
    mov    ecx,[ecx]
//    mov    ecx, -> advManager
    push   1
    push   1
    push   1
    mov    eax,0x415D40
    call   eax
  }
l_not:;  
  RETURNV
}

void RedrawRes(void)
{
  #include "templ.h"
  __asm{
    mov    ecx,0x6992B8
    mov    ecx,[ecx]
    mov    ecx,[ecx+0x44]
    push   1
    push   1
    mov    eax,0x403F00
    call   eax
  }
  RETURNV
}

void RedrawTown(void)
{
  #include "templ.h"
  __asm{
//    mov   eax,0x5F4B90
/*
    mov   ecx,0x6992D0
    mov   ecx,[ecx]
    push  0x258
    push  0x320
    push  0
    push  0
    mov   eax,0x603190
    call  eax
*/
    mov   esi,0x69954C
    mov   esi,[esi]
    // redraw small towns icons
    mov   ecx,[esi+0x118]
    mov   eax,0x5C5EA0
    call  eax
    // redraw
    mov   ecx,esi
    mov   eax,0x5D5810
    call  eax
  }
  RETURNV
}

static Dword TS_HintStr[10];
void ShowTSHint(char *txt)
{
  #include "templ.h"
  TS_HintStr[6]=(Dword)txt;
  TS_HintStr[3]=0;
  TS_HintStr[4]=0;
  TS_HintStr[5]=0;
  TS_HintStr[7]=0;
  TS_HintStr[0]=0x200;
  TS_HintStr[1]=3;
  TS_HintStr[2]=0x97;
  __asm{
    mov    ebx,0x69954C
    mov    ebx,[ebx]
    lea    edx,TS_HintStr//[ebp-20]
    mov    ecx,[ebx+0x118]
    push   edx
    mov    eax,0x5FF3A0
    call   eax
    mov    ebx,[ebx+0x118]
    push   0x97
    push   0x97
    push   0
    mov    eax,[ebx]
    mov    ecx,ebx
    call   [eax+0x14]
    mov    ecx,0x6992D0
    mov    ecx,[ecx]
    push   0x13
    push   0x2DE
    push   0x22B
    push   0x7
    mov    eax,0x603190
    call   eax
  }
  RETURNV
}

// [BASE+4E38C] -> ������ 0x40, ����� = ��������� � _Position_
_Mine_ *GetMineStr(int Num)
{
  #include "templ.h"
  int     mn;
  _Mine_ *mp0,*mp1;

  __asm{
    mov   ecx,BASE
    mov   ecx,[ecx]
    add   ecx,0x4E38C
    mov   eax,[ecx]
    mov   mp0,eax
    mov   eax,[ecx+4]
    mov   mp1,eax
  }
  mn=mp1-mp0;
  if((Num<0)||(Num>=mn)){ MError("\"GetMineStr\"-cannot find mine (internal)"); RETURN(0) }
  RETURN(&mp0[Num])
}

void AddExp(_Hero_ *hp/*int hn,int exp*/)
{
  #include "templ.h"
  __asm{
  // ������� ���������� ����
    mov  ecx,0x6992B0
    mov  ecx,[ecx]
    push 0
    mov  eax,0x50D7B0
    call eax
  }  
  __asm{
    mov   ecx,hp
    mov   eax,0x4DA990  
    call  eax
  }
  RETURNV
}

void _PlaceObject(int x,int y,int l,int ztype,int subtype,int ter,Dword SetUpWord)
{
  #include "templ.h"
  __asm{
// ��� �����
    mov    ebx,0x4C95DF
    mov    eax,ter
    mov    [ebx],al
// ���� �-�
    mov    ecx,subtype   // ������
    mov    edx,l         // l
    mov    eax,y         // y
    mov    ebx,x         // x
    mov    esi,ztype      // ���
    push   SetUpWord
    push   ecx    // subtype
    push   esi    // type
    push   edx    // l
    push   eax    // y
    push   ebx    // x
    mov    ecx,BASE
    mov    ecx,[ecx] // [BASE]
    mov    eax,0x4C9550
    call   eax
// ����������� ��� �����
    mov    ebx,0x4C95DF
    mov    al,0xFF
    mov    [ebx],al
  }
  RETURNV
}

Dword PlaceObject(int x,int y,int l,int type,int subtype,int t2,int st2,int ter)
{
  #include "templ.h"
  Dword setup,dws;
  int x2,y2,ex,ey,dx,dy,Flag;
  if((type!=t2)||(subtype!=st2)) Flag=1; else Flag=0;
  switch(type){ // ���������� ���������
//    case 69: // ��������� ������
//      type=Random(65,68); break;
    case 76: // ��������� ������
      type=79; // ����� ������
      subtype=Random(0,6); 
      if(Flag) break;
      t2=type; st2=subtype;
      break;
    default: break;  
  }
  setup=AddStrObject(x,y,l,type,subtype,t2,st2,ter);
  if(Flag){
    int MapSize;
    __asm{
      mov   ecx,BASE
      mov   ecx,[ecx]
      mov   eax,[ecx+0x1FC44]
      mov   MapSize,eax
    }
    FindEnterShift(t2,st2,&dx,&dy);
    ex=x-dx; ey=y-dy;
    _MapItem_ *mp=GetMapItem(ex,ey,l);
    dws=mp->SetUp;
    for(dy=0;dy<6;dy++){
      for(dx=0;dx<6;dx++){
        x2=x-dx; y2=y-dy;
        if(x2<0) continue;
        if(x2>=MapSize) continue;
        if(y2<0) continue;
        if(y2>=MapSize) continue;
        mp=GetMapItem(x2,y2,l);
        if(mp->OType!=(Word)t2) continue;
        if(mp->OSType!=(Word)st2) continue;
        if(mp->SetUp!=dws) continue;
        mp->OType=(Word)type;
        mp->OSType=(Word)subtype;
      }
    }
  }
  RETURN(setup)
}

void DelObject(int x,int y,int l)
{
  #include "templ.h"
  Dword PosMixed;
  _MapItem_ *MIp;

  MIp=GetMapItem(x,y,l);
  PosMixed=((Dword)y<<16)+(Dword)x;
  if(l) PosMixed+=0x04000000;
  __asm{
    mov    ecx,0x6992B8
    mov    ecx,[ecx]     // -> AdvManager
    mov    ebx,PosMixed
    mov    eax,MIp
    push   1
    push   ebx
    push   eax
    mov    eax,0x4AA820
    call   eax
  }
  RETURNV
}
void DelFirstObjectPic(int x,int y,int l)
{
  #include "templ.h"
  _MapItem_ *MIp=GetMapItem(x,y,l);
  if(MIp->Draw==0) RETURNV // ��� ������
  if(MIp->Draw==MIp->DrawEnd) RETURNV // ��� ������
  for(ODraw *dp=MIp->Draw;dp<MIp->DrawEnd-1;dp++){ 
    dp->LType=dp[1].LType;
    dp->Code=dp[1].Code;
  }  
  --MIp->DrawEnd;
  RETURNV
}

void FixStr(char *String)
{
  #include "templ.h"
  __asm{
    mov    ecx,String
    test   ecx,ecx
    je     l_ex
    mov    al,[ecx-1]
    test   al,al
    je     l_ex
    cmp    al,0xFF
    je     l_ex
    dec    al
    mov    [ecx-1],al
  }
l_ex:;    
  RETURNV
}

int FindEnterShift(int t,int st,int *dx,int *dy,int silence/*=0*/)
{
  #include "templ.h"
  int i,j,k,num;
  Dword tb;
  _Types_ *tps,*tpe,*tp;
  *dx=*dy=0;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x1FB74
    mov    eax,[ebx]
    mov    tps,eax
    mov    eax,[ebx+4]
    mov    tpe,eax
  }
  num=tpe-tps;
  for(i=0;i<num;i++){
    tp=&tps[i];
    if(tp->type!=t) continue;
    if(tp->subtype!=st) continue;
// +0x14 - 6 ���� ����� ���������
// +0x24 - 6 ���� ����� ����
    for(k=0;k<6;k++){
      for(j=0;j<8;j++){
        tb=0x80>>j;
        if(tp->EnterMask[5-k]&tb){
          *dx=j; *dy=k; RETURN(1)
        }
      }
    }
//    MError("\"FindEnterShift\"-cannot find entrance shift."); return; // �� ����� ����
    *dx=*dy=0; RETURN(1)
  }
  *dx=*dy=0;
  if(silence==0) MError("\"FindEnterShift\"-cannot find type of object."); 
  RETURN(0) // ��� ������ ����
}

_ArtRes_ *GetArtResBase(void)
{
  #include "templ.h"
  _ArtRes_ *zret;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x1FBA4 // -> ����.�����.���/���
    mov    eax,[ebx]
    mov    zret,eax
  }
  RETURN(zret)
}
int GetArtResNum(void)
{
  #include "templ.h"
  _ArtRes_ *ars,*are;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x1FBA4 // -> ����.�����.���/���
    mov    eax,[ebx]
    mov    ars,eax
    mov    eax,[ebx+4]
    mov    are,eax
  }
  if(ars==0) RETURN(0)
  RETURN(are-ars)
}
_Dwelling_ *GetSwellingBase(void)
{
  #include "templ.h"
  _Dwelling_ *zret;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x4E39C // -> ����.�����
    mov    eax,[ebx]
    mov    zret,eax
  }
  RETURN(zret)
}
int GetDwellingNum(void)
{
  #include "templ.h"
  _Dwelling_ *ars,*are;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x4E39C // -> ����.�����
    mov    eax,[ebx]
    mov    ars,eax
    mov    eax,[ebx+4]
    mov    are,eax
  }
  if(ars==0) RETURN(0)
  RETURN(are-ars)
}

_CrBankMap_ *GetCrBankBase(void)
{
  #include "templ.h"
  _CrBankMap_ *zret;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x4E3DC // -> ����.�����
    mov    eax,[ebx]
    mov    zret,eax
  }
  RETURN(zret)
}
int GetCrBankNum(void)
{
  #include "templ.h"
  _CrBankMap_ *ars,*are;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x4E3DC // -> ����.�����
    mov    eax,[ebx]
    mov    ars,eax
    mov    eax,[ebx+4]
    mov    are,eax
  }
  if(ars==0) RETURN(0)
  RETURN(are-ars)
}

_Mine_ *GetMineBase(void)
{
  #include "templ.h"
  _Mine_ *zret;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x4E38C // -> ����.�����
    mov    eax,[ebx]
    mov    zret,eax
  }
  RETURN(zret)
}
int GetMineNum(void)
{
  #include "templ.h"
  _Mine_ *ars,*are;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x4E38C // -> ����.�����
    mov    eax,[ebx]
    mov    ars,eax
    mov    eax,[ebx+4]
    mov    are,eax
  }
  if(ars==0) RETURN(0)
  RETURN(are-ars)
}
_Horn_ *GetHornBase(void)
{
  #include "templ.h"
  _Horn_ *zret;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x4E3AC // -> ����.�����
    mov    eax,[ebx]
    mov    zret,eax
  }
  RETURN(zret)
}
int GetHornNum(void)
{
  #include "templ.h"
  _Horn_ *ars,*are;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x4E3AC // -> ����.�����
    mov    eax,[ebx]
    mov    ars,eax
    mov    eax,[ebx+4]
    mov    are,eax
  }
  if(ars==0) RETURN(0)
  RETURN(are-ars)
}
_Monster_ *GetMonsterBase(void)
{
  #include "templ.h"
  _Monster_ *zret;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x1FBB4 // -> ����.�����
    mov    eax,[ebx]
    mov    zret,eax
  }
  RETURN(zret)
}
int GetMonsterNum(void)
{
  #include "templ.h"
  _Monster_ *ars,*are;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x1FBB4 // -> ����.�����
    mov    eax,[ebx]
    mov    ars,eax
    mov    eax,[ebx+4]
    mov    are,eax
  }
  if(ars==0) RETURN(0)
  RETURN(are-ars)
}
_Sign_ *GetSignBase(void)
{
  #include "templ.h"
  _Sign_ *zret;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x4E37C // -> ����.�����
    mov    eax,[ebx]
    mov    zret,eax
  }
  RETURN(zret)
}
int GetSignNum(void)
{
  #include "templ.h"
  _Sign_ *ars,*are;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x4E37C // -> ����.�����
    mov    eax,[ebx]
    mov    ars,eax
    mov    eax,[ebx+4]
    mov    are,eax
  }
  if(ars==0) RETURN(0)
  RETURN(are-ars)
}
_Univer_ *GetUniverBase(void)
{
  #include "templ.h"
  _Univer_ *zret;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x4E3CC // -> ����.�����
    mov    eax,[ebx]
    mov    zret,eax
  }
  RETURN(zret)
}
int GetUniverNum(void)
{
  #include "templ.h"
  _Univer_ *ars,*are;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x4E3CC // -> ����.�����
    mov    eax,[ebx]
    mov    ars,eax
    mov    eax,[ebx+4]
    mov    are,eax
  }
  if(ars==0) RETURN(0)
  RETURN(are-ars)
}

_Event_ *GetEventBase(void)
{
  #include "templ.h"
  _Event_ *zret;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x1FBC4 // -> ����.�����
    mov    eax,[ebx]
    mov    zret,eax
  }
  RETURN(zret)
}
int GetEventNum(void)
{
  #include "templ.h"
  _Event_ *ars,*are;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x1FBC4 // -> ����.�����
    mov    eax,[ebx]
    mov    ars,eax
    mov    eax,[ebx+4]
    mov    are,eax
  }
  if(ars==0) RETURN(0)
  RETURN(are-ars)
}
void CoorectMonsterRadius(void)
{
// 4C8EF4 ���-�� �� ������� �����, �� �������� - ������������� ���������� ������ ��������
  #include "templ.h"
  __asm{
    push   edi
    mov    edi,BASE
    mov    edi,[edi]
    mov    ecx,edi
    mov    eax,0x4CA0D0
    call   eax
/*
    push   2
    mov    ecx,edi
    mov    eax,0x4C9190
    call   eax
    push   2
    mov    ecx,edi
    mov    [edi+0x1F664],eax
    mov    eax,0x4C9190
    call   eax
    push   2
    mov    ecx,edi
    mov    [edi+0x1F668],eax
    mov    eax,0x4C9190
    call   eax
    push   4
    mov    ecx,edi
    mov    [edi+0x1F66C],eax
    mov    eax,0x4C9190
    call   eax
    push   4
    mov    ecx,edi
    mov    [edi+0x1F670],eax
    mov    eax,0x4C9190
    call   eax
    push   4
    mov    ecx,edi
    mov    [edi+0x1F674],eax
    mov    eax,0x4C9190
    call   eax
    push   8
    mov    ecx,edi
    mov    [edi+0x1F678],eax
    mov    eax,0x4C9190
    call   eax
    mov    [edi+0x1F67C],eax
*/
    mov    ecx,0x6992B8
    mov    ecx,[ecx]
    push   0
    mov    eax,0x40F7D0
    call   eax
    pop    edi
  }
  RETURNV
}

static _Mine_     AO_mn;
static _ArtRes_   AO_ar; static _CRes_ AOC_ar;
static _Dwelling_ AO_dw;
static _Horn_     AO_hr;
static _Monster_  AO_mo; static _CMonster_ AOC_mo;
static _Sign_     AO_sn;
Dword AddStrObject(int x,int y,int l,int t,int st,int t2, int st2,int ter)
{
//  _MapItem_ *mp;
  #include "templ.h"
  Dword stpword;
  int i,ind,dx,dy;
  switch(t){
    case 17: // ������ ��������
    case 20: // ������ ��������
     {
      __asm{
        lea    ecx,AO_dw
        mov    eax,0x4B8250 // ��������� ����������
        call   eax
      }
      AO_dw.Type=(Byte)t;
      AO_dw.SType=(Byte)st;
      AO_dw.x=(Byte)x; AO_dw.y=(Byte)y; AO_dw.l=(Byte)l;
      __asm{
        push   -1 // Owner
        lea    ecx,AO_dw
        mov    eax,0x4B8560 // ��������� ��� �������
        call   eax  
      }
//__asm int 3

      _Dwelling_ *dwp,*dwpo,*dwp0;
      ind=-1;
/*
      if(FindEnterShift(t2,st2,&dx,&dy,1)==1){ // this type was placed somewhere on the map
        AO_dw.x=(Byte)(x-dx);
        AO_dw.y=(Byte)(y-dy); //AO_dw.l=(Byte)l;
        dwp=GetDwellingBase();
        dwpo=FindDwelling(AO_dw.x,AO_dw.y,l);
        if((dwpo!=0) && (dwp!=0)){ // there was a dwelling at this location already
          memcpy(dwpo,&AO_dw,sizeof(_Dwelling_));
          ind=dwpo-dwp;
        }
      }
      if(ind==-1){
        __asm{ // add new
          mov    eax,BASE
          mov    eax,[eax]
          lea    edx,AO_dw
          push   edx
          push   1
          lea    ecx,[eax+0x4E398]
          mov    eax,[eax+0x4E3A0]
          push   eax
          mov    eax,0x509440
          call   eax
        }
        ind=GetDwellingNum()-1;
      }
      dwp=GetDwellingBase();
      if(ind==-1){ Error(); RETURN((Dword)-1) }
      stpword=(Dword)ind;
      _PlaceObject(x,y,l,t2,st2,ter,stpword);
      FindEnterShift(t2,st2,&dx,&dy);
      dwp=&dwp[ind];
      dwp->x=(Byte)(x-dx);
      dwp->y=(Byte)(y-dy); //AO_dw.l=(Byte)l;
      RETURN(stpword)
*/
//__asm int 3
      __asm{ // add new
        mov    eax,BASE
        mov    eax,[eax]
        lea    edx,AO_dw
        push   edx
        push   1
        lea    ecx,[eax+0x4E398]
        mov    eax,[eax+0x4E3A0]
        push   eax
        mov    eax,0x509440
        call   eax
      }
      ind=GetDwellingNum()-1; // last added
      if(ind==-1){ Error(); RETURN((Dword)-1) }
      stpword=(Dword)ind;
      _PlaceObject(x,y,l,t2,st2,ter,stpword);
      FindEnterShift(t2,st2,&dx,&dy);
      dwp=GetDwellingBase();
      dwp=&dwp[ind];
      dwp->x=(Byte)(x-dx);
      dwp->y=(Byte)(y-dy); //AO_dw.l=(Byte)l;

      AO_dw.x=(Byte)(x-dx);
      AO_dw.y=(Byte)(y-dy); //AO_dw.l=(Byte)l;
      dwp0=GetDwellingBase();
      dwpo=FindDwelling(AO_dw.x,AO_dw.y,l);
      if(ind!=(dwpo-dwp0)){ // there was a dwelling at the same place - try to fill it
        dwpo->x=0;
        dwpo->y=0;
        dwpo->l=0;
/*
        memcpy(dwpo,dwp,sizeof(_Dwelling_));
        int szofstr=sizeof(_Dwelling_);
        __asm{ // remove the latest dwelling from the list
          mov    edx,BASE
          mov    edx,[edx]
          mov    eax,[edx+0x04E3A0]
          sub    eax,szofstr
          mov    [edx+0x04E3A0],eax
        }
        stpword=dwpo-dwp0;
        _MapItem_ *mp=GetMapItem(AO_dw.x,AO_dw.y,l);
        mp->SetUp=stpword;
*/
      }
      RETURN(stpword)
     }
//    case 69,65,66,67,68: // ���� ���
    case 79: // ������ 
    case  5: // ���
    case 93: // ������ � ������������
     {
      MesMan(&AO_ar.Mes,"No message",0);
      for(i=0;i<7;i++){ AO_ar.Gt[i]=-1; AO_ar.Gn[i]=0; }
      __asm{
        mov    edi,BASE
        mov    edi,[edi]
        add    edi,0x1FBA0 // -> ����.�����.���/���
        mov    edx,[edi+8]
        lea    ecx,AO_ar
        push   ecx
        push   1
        push   edx
        mov    ecx,edi
        mov    eax,0x507020
        call   eax
      }
      MesMan(&AO_ar.Mes,0,0);
      _ArtRes_ *arp=GetArtResBase();
      ind=GetArtResNum()-1;
      if(ind==-1){ Error(); RETURN((Dword)-1) }
      arp=&arp[ind];
      MesMan(&arp->Mes,0,0);
//      FixStr(arp->Mes.m.s);
      if(t==79) AOC_ar.Value=5; // ������
      if(t==93){ // ������
        if(st<0){ Error(); RETURN((Dword)-1) }
        AOC_ar.Value=(Word)st; 
        if((t==t2)&&(st==st2)){ /*st=*/st2=0; }
 //       else st=0;
      }  
      AOC_ar.SetUpNum=(Word)ind;
      AOC_ar.HasSetUp=1;
      stpword=*(Dword *)&AOC_ar;
      _PlaceObject(x,y,l,t2,st2,ter,stpword);
      RETURN(stpword)
     } 
    case 53: // �����
    case 42: // ����
     {
      if((t==53)&&(st==7)) break;
      if(t==53) AO_mn.Owner=-1;
      if(t==42){ AO_mn.Owner=(Byte)st; 
        if((t==t2)&&(st==st2)){ st=st2=0; }
        else st=0;
      }
      for(i=0;i<7;i++){ AO_mn.GType[i]=-1; AO_mn.GNumb[i]=0; }
      if(t==53){ AO_mn.ResNum=(char)st; }
      if(t==42){ AO_mn.ResNum=100; }
      AO_mn._u1[0]=0; AO_mn._u1[1]=0;
      AO_mn.xe=(Byte)x; 
      AO_mn.ye=(Byte)y; 
      AO_mn.le=(Byte)l;
      AO_mn._u2=0;
      __asm{
        mov    ecx,0x699538
        mov    ecx,[ecx]
        add    ecx,0x4E388
        lea    edx,AO_mn
        push   edx
        mov    eax,[ecx+8]
        push   1
        push   eax
        mov    eax,0x4D0870
        call   eax
      }
      _Mine_ *mnp=GetMineBase();
      ind=GetMineNum()-1;
      if(ind==-1){ Error(); RETURN((Dword)-1) }
      stpword=(Dword)ind;
      _PlaceObject(x,y,l,t2,st2,ter,stpword);
      FindEnterShift(t2,st2,&dx,&dy);
      mnp=&mnp[ind];
      mnp->xe=(Byte)(x-dx); 
      mnp->ye=(Byte)(y-dy);
      RETURN(stpword)
     } 
    case 113: // 0x71 - ������ ������
     {
      if((st<0)||(st>=28)){ Error(); RETURN((Dword)-1) }
      _CWHat_ wh; *(Dword *)&wh=0;
      wh.SSkill=st;
      if((t==t2)&&(st==st2)){ /*st=*/st2=0; }
 //     else st=0;
      stpword=*(Dword *)&wh;
      _PlaceObject(x,y,l,t2,st2,ter,stpword);
      RETURN(stpword)
     } 
    case 87: // - �����
     {
      if((st<-1)||(st>=8)){ Error(); RETURN((Dword)-1) }
      _CShipyard_ sh;
      sh.Owner=(Word)st; 
      sh.xs=(Word)(x+1);
      sh.ys=(Word)(y+1);
      sh._u3=0xFF;
      stpword=*(Dword *)&sh;
      if((t==t2)&&(st==st2)){ /*st=*/st2=0; }
//      else st=0;
      _PlaceObject(x,y,l,t2,st2,ter,stpword);
      RETURN(stpword)
     } 
    case 33:  // H ��������
    case 219: // V ��������
     {
      AO_hr.Owner=-1; // �����
//      AO_hr._u1[0]=AO_hr._u1[1]=AO_hr._u1[2]=-1;
      AO_hr.NotRem=1; // ��������������
      AO_hr.ex=(Byte)x; AO_hr.ey=(Byte)y;
      for(i=0;i<7;i++){ AO_hr.GType[i]=-1; AO_hr.GNumb[i]=0; }
      AO_hr.el=0;  //????
      __asm{
        mov    edx,BASE
        mov    edx,[edx]
        lea    eax,AO_hr
        lea    ecx,[edx+0x4E3A8]
        push   eax
        push   1
        mov    edx,[ecx+8]
        push   edx
        mov    eax,0x4D0870
        call   eax
      }
      _Horn_ *dwp=GetHornBase();
      ind=GetHornNum()-1;
      if(ind==-1){ Error(); RETURN((Dword)-1) }
      stpword=(Dword)ind;
      _PlaceObject(x,y,l,t2,st2,ter,stpword);
      FindEnterShift(t2,st2,&dx,&dy);
      dwp=&dwp[ind];
      dwp->ex=(Byte)(x-dx);
      dwp->ey=(Byte)(y-dy);
//      if(t==219){
//        mp=GetMapItem(x-dx,y-dy,l);
//        mp->OType=33; // for Vertical Garrison
//      }
      RETURN(stpword)
     }
    case 36: // ������
      __asm{
        mov    edx,BASE
        mov    edx,[edx]
        mov    ecx,x
        mov    [edx+0x1F690],cx
        mov    ecx,y
        mov    [edx+0x1F692],cx
        mov    ecx,l
        mov    [edx+0x1F694],cl
        xor    cl,cl // ???
        mov    [edx+0x1F695],cl
        mov    cl,1 // ���� ������
        mov    [edx+0x1F696],cl
      }
      RETURN(0)
    case 54: // ������
     {
      MesMan(&AO_mo.Mes,"No message",0);
      for(i=0;i<7;i++) AO_mo.Res[i]=0;
      AO_mo.Artefact=-1;
      __asm{
        mov    edi,BASE
        mov    edi,[edi]
        add    edi,0x1FBB0 // -> ����.�����
        mov    edx,[edi+8]
        lea    ecx,AO_mo
        push   ecx
        push   1
        push   edx
        mov    ecx,edi
        mov    eax,0x507410
        call   eax
      }
      MesMan(&AO_mo.Mes,0,0);
      _Monster_ *arp=GetMonsterBase();
      ind=GetMonsterNum()-1;
      if(ind==-1){ Error(); RETURN((Dword)-1) }
      arp=&arp[ind];
      MesMan(&arp->Mes,0,0);
//      FixStr(arp->Mes.m.s);
      AOC_mo.Number=5;
      AOC_mo.Agression=0x0A; 
      AOC_mo.NoMore=0;
      AOC_mo.NoRun=1;
      AOC_mo.SetUpInd=(Word)ind;
      AOC_mo.HasSetUp=1;
      stpword=*(Dword *)&AOC_mo;
      _PlaceObject(x,y,l,t2,st2,ter,stpword);
      CoorectMonsterRadius();
      RETURN(stpword)
     } 
    case 59: // �������
    case 91: // ����
     {
      MesMan(&AO_sn.Mes,"No message",0);
      AO_sn.HasMess=1;
      __asm{

        mov    ecx,BASE
        mov    ecx,[ecx]
        lea    edx,AO_sn
        add    ecx,0x4E378
        push   edx
        push   1
        mov    eax,[ecx+8]
        push   eax
        mov    eax,0x4D04C0
        call   eax
      }
      MesMan(&AO_sn.Mes,0,0);
      _Sign_ *arp=GetSignBase();
      ind=GetSignNum()-1;
      if(ind==-1){ Error(); RETURN((Dword)-1) }
      arp=&arp[ind];
      MesMan(&arp->Mes,0,0);
      arp->HasMess=0;
      stpword=(Dword)ind;
      _PlaceObject(x,y,l,t2,st2,ter,stpword);
      RETURN(stpword)
     } 
//    case 43: // ������� ���� - �� ����
//    case 44: // ������� ����� - �� �������� ???
    case 45: // ������� ��� �������
      {
       Dword mixpos=PosMixed(x,y,l);
       Dword *po;
       int subt=st;
       if(t==45){
         __asm{
           mov    ebx,BASE
           mov    ebx,[ebx]
           mov    eax,subt
           shl    eax,4
           mov    edx,[eax+ebx+0x4E680]
           lea    ecx,[eax+ebx+0x4E67C]
           test   edx,edx
           jne    l_m1
           xor    eax,eax
           jmp    l_m2
         }
       }else{  
         __asm{
           mov    ebx,BASE
           mov    ebx,[ebx]
           mov    eax,subt
           shl    eax,4
           mov    edx,[eax+ebx+0x4E700]
           lea    ecx,[eax+ebx+0x4E6FC]
           test   edx,edx
           jne    l_m1
           xor    eax,eax
           jmp    l_m2
         }  
       }
l_m1:
       __asm{       
         mov    eax,[ecx+8]
         sub    eax,edx
         sar    eax,2
       }
l_m2:         
       __asm{
         mov    ind,eax
         mov    po,ecx
         mov    edx,[ecx+8]
         lea    eax,mixpos
         push   eax
         push   1
         push   edx
         mov    eax,0x5FE2D0
         call   eax
       }  
       stpword=(Dword)ind;
       _PlaceObject(x,y,l,t2,st2,ter,stpword);
       po=(Dword *)po[1];
       po=&po[ind];
       FindEnterShift(t2,st2,&dx,&dy);
       *po=PosMixed(x-dx,y-dy,l);
       RETURN(stpword)
     }
    case 0x68: // �����������
      {
        _MapItem_ *mp;
        stpword=(Dword)-1;
        _PlaceObject(x,y,l,t2,st2,ter,stpword);
        FindEnterShift(t2,st2,&dx,&dy);
        mp=GetMapItem(x-dx,y-dy,l);
        __asm{
          mov    esi,mp
          mov    ecx,BASE
          mov    ecx,[ecx]
          push   esi
          mov    eax,0x4C03B0
          call   eax
        }  
        RETURN(mp->SetUp)
      }
    case 98: // �����
      {
        _CastleSetup_ *csp;
        _CastleSetup_ TCs;
        _CastlePreSetup_ Cps;
        Cps.Id=0; Cps.Owner=-1; Cps._u9=0; Cps._u10=1; Cps._u7=0;
        for(i=0;i<7;i++){ Cps.GuardsT[i]=-1; Cps.GuardsN[i]=0; }
        Cps._u6=0; Cps._u1=0; Cps._u8=0;
        for(i=0;i<12;i++){ Cps._u2[i]=0; Cps._u3[i]=0; Cps._u4[i]=0; }
        Cps.SType=st;
        __asm{
          mov    ecx,BASE
          mov    ecx,[ecx]
          mov    edx,[ecx+0x9C]
          add    ecx,0x94
          lea    eax,Cps
          push   eax
          push   1
          push   edx
          mov    eax,0x509080
          call   eax
//          mov    ecx,BASE
//          mov    ecx,[ecx]
//          mov    eax,0x4CA730
//          call   eax
// ��������� ��������� ���. �����
//:004CA791 8D8D68FEFFFF   lea    ecx,[ebp-00000198] -> ����� �� 0x168
//:004CA797 E8E43A0F00     call   H3.005BE280
          lea    ecx,TCs
          mov    eax,0x5BE280
          call   eax
//:004CA7D5 8DB710160200   lea    esi,[edi+00021610] BASE+
//:004CA825 8B4608         mov    eax,[esi+08]
//:004CA82A51             push   ecx -> ���. ��������� �����
//:004CA82B 53             push   ebx = ���������� ����������
//:004CA82C 50             push   eax -> ��. �� ��, ��� ����
//:004CA82D 8BCE           mov    ecx,esi -> �� �� ������. ���������
//:004CA82F E8CC580000     call   H3.004D0100
          mov    esi,BASE
          mov    esi,[esi]
          lea    esi,[esi+0x21610]
          mov    eax,[esi+8]
          lea    ecx,TCs
          push   ecx 
          push   1
          push   eax 
          mov    ecx,esi
          mov    eax,0x4D0100
          call   eax
        }  
// ��������� ���������� � �.�.
//:004CAA70 8BCB           mov    ecx,ebx -> ������ �����
//:004CAA72 52             push   edx     -> ������ �����. �����
//:004CAA73E8F85F0F00     call   H3.005C0A70
        ind=GetCastleNum()-1;
        stpword=ind;
        _PlaceObject(x,y,l,t2,st2,ter,stpword);
        FindEnterShift(t2,st2,&dx,&dy);
//        mp=GetMapItem(x-dx,y-dy,l);
//        mp->SetUp=ind;
        csp=GetCastleBase();
        csp=&csp[ind];
        csp->Number=(Byte)ind;
        csp->Type=(Byte)st;
        csp->x=(Byte)(x-dx); csp->y=(Byte)(y-dy); csp->l=(Byte)l;
        __asm{
          mov    ecx,csp
          lea    edx,Cps
          push   edx
          mov    eax,0x5C0A70
          call   eax
        }
//        PrepareCastle(cs);
        RETURN(ind)
      }
    case 16: // �����
      {
        int x1,y1,st1;
        _MapItem_ *mp;
        stpword=(Dword)-1;
        Byte  CrB_Buf[0x200];
//        Dword *CrB_BufD=CrB_Buf;
        _PlaceObject(x,y,l,t2,st2,ter,stpword);
        FindEnterShift(t2,st2,&dx,&dy);
        x1=x-dx; y1=y-dy; st1=st;
        mp=GetMapItem(x1,y1,l);
        __asm{
//int 3        
//          mov    ecx,mp
//          mov    eax,[ecx] //����������� �����
          mov    eax,stpword
          and    eax,0xFFFFE01F
//          mov    [ecx],eax
          mov    stpword,eax

          mov    ebx,BASE
          mov    ebx,[ebx]
          mov    eax,[ebx+0x4E3DC]
//          mov    ecx,edi
          lea    edi,[ebx+0x4E3D8]
          test   eax,eax
          je     no_one
          mov    edx,[edi+8]
          sub    edx,eax
          mov    eax,0x4BDA12F7
          imul   edx
          sar    edx,5
          mov    eax,edx
          shr    eax,0x1F
          add    edx,eax
          mov    eax,edx //����� ��� �����������
        }
no_one:
      __asm{
          and    eax,0xFFF
          mov    ecx,stpword
          and    ecx,0xFC001FFF
          shl    eax,0xD
          or     eax,ecx
//          mov    [esi],eax �����. �����
          mov    stpword,eax
          lea    ecx,CrB_Buf
          mov    eax,0x44A750
          call   eax // ���� ������
          mov    cl,2 //[ebp-11] ???
          xor    eax,eax
          mov    CrB_Buf[0x5C],cl
          mov    dword ptr [CrB_Buf+0x60],eax
          mov    dword ptr [CrB_Buf+0x64],eax
          mov    dword ptr [CrB_Buf+0x68],eax
//          movsx  edx,word ptr [esi+22] ��� CrBank (������)
          mov    edx,st1
          lea    ecx,CrB_Buf
//  mov    [ebp-04],eax
          mov    eax,0x47A6C0
          call   eax // ��������� �����. ����.
          mov    eax,[edi+8] //����� CrBank
          lea    edx,CrB_Buf
          push   edx
          push   1
          push   eax
          mov    ecx,edi
          mov    eax,0x4D22B0
          call   eax // ���������
          lea    ecx,[CrB_Buf+0x5C]
//  mov    dword ptr [ebp-04],FFFFFFFF ????
          mov    eax,0x5BC5E0
          call   eax // ???
        }
        mp->SetUp=stpword;
        RETURN(mp->SetUp)
      }
    case 8: // �����
      {
        int x1,y1,st1;
        _MapItem_ *mp;
        stpword=(Dword)-1;
        _PlaceObject(x,y,l,t2,st2,ter,stpword);
        FindEnterShift(t2,st2,&dx,&dy);
        x1=x-dx; y1=y-dy; st1=st;
        mp=GetMapItem(x1,y1,l);
        __asm{
          mov    ecx,l
          mov    edx,y1
          mov    eax,x1
          push   st1
          push   1
          push  -1
          push   ecx
          push   edx
          push   eax
          mov    ecx,BASE
          mov    ecx,[ecx]
          mov    eax,0x4BAF10
          call   eax
        }
        RETURN(mp->SetUp)
      }
    case 26: // LE
      {
        _EventPos_ *ep;
        _Event_    Evnt;
        _MapItem_ *mp;
        mp=GetMapItem(x,y,l);
        ep=(_EventPos_ *)mp;
        for(i=0;i<sizeof(_Event_);i++) ((Byte *)&Evnt)[i]=0;
        for(i=0;i<7;i++){ Evnt.Guard.Ct[i]=-1; Evnt.Mon.Ct[i]=-1; }
        __asm{
          mov    ecx,BASE
          mov    ecx,[ecx]
          lea    ebx,[ecx+0x1FBC0]
          mov    eax,[ebx+8]
          lea    ecx,Evnt
          push   ecx
          push   1
          push   eax
          mov    ecx,ebx
          mov    eax,0x5077F0
          call   eax
        }
        ind=GetEventNum()-1;
        if(ind>=1024){ MError("AddStrObject:\nToo many LE (>1024)"); RETURN(0) }
        mp->SetUp=0x03FC00;
        ep->Number=(Word)ind;
        _PlaceObject(x,y,l,t2,st2,ter,mp->SetUp);
        RETURN(mp->SetUp)
      }
    default: 
    break;
  }
  stpword=0; // ������� ���������
  _PlaceObject(x,y,l,t2,st2,ter,stpword);
  RETURN(0)
}

void SetMonMagic(Byte *MonStr,int Spell,int ZLength,int Level,_Hero_ *Hp)    
{
  #include "templ.h"
  __asm{
    mov   ecx,MonStr
    mov   edx,Spell
    mov   ebx,Level
    mov   eax,ZLength
    push  Hp
    push  ebx
    push  eax
    push  edx
    mov   eax,0x444610
    call  eax
  }
  RETURNV
}

int SetMonMassMagic(Byte *Mon,int Spell,int Level)
{
  #include "templ.h"
  if(*((int *)&Mon[0x4C])<=0) RETURN(-1);
  int side=*((int *)&Mon[0xF4]);
  if(*((int *)&Mon[0x288])){ side=!side; }
  __asm{
    mov    ecx,0x699420
    mov    ecx,[ecx]
    push   1
    push   1
    push   Mon  // -> DMon
    push   side  // Side
    push   Spell // Spell Index
    mov    eax,0x5A8950
    call   eax
    test   al, al
    jz     lCannot
    mov    edi,Mon
    mov    ecx, [edi+0x38]     // Dest position
    push   3
    push   Level //3 - level of creature
    push  -1
    push   1
    push   ecx
    mov    ecx, 0x699420
    mov    ecx,[ecx]
    push   Spell // Spell Index
    mov    eax,0x5A0140
    call   eax
  }
  RETURN(Spell)
lCannot:
  RETURN(-1)
}

static char  CSBuffer[2048];
int DoBattle(
  int    *Mn, // -> ����� �������� (dw)
  _Hero_ *Hp, // -> �����
  int     Mt, // = ��� ��������
  Dword   PosMixed // ������� ��������
)
{
  #include "templ.h"
  // 3.58 fix
  int oldCAI=G2B_CompleteAI,Dummy;
  G2B_CompleteAI=1;
  do{
    if(Hp==0) break;
    if(Hp->Owner<0) break;
    if(Hp->Owner>7) break;
    if(IsAI(Hp->Owner)==0) G2B_CompleteAI=0; // human
  }while(0);

  if(QuickBattle()){
    __asm{
//      mov ebx,0x5C7603; mov eax,0x90909090; mov [ebx],eax;
//      mov [ebx+4],eax; mov [ebx+8],ax; mov [ebx+10],al;
    }
  }
  __asm{
//    mov ebx,0x4AE5DB; mov eax,0x90909090; mov [ebx],eax;
//    mov [ebx+4],eax; mov [ebx+8],al; mov [ebx+9],eax;
//    mov ebx,0x4AC5FD; mov [ebx],eax; mov [ebx+4],eax;
//    mov [ebx+8],ax; mov [ebx+10],al; mov [ebx+11],eax;
//    mov ebx,0x4AE3A4; mov ax,0x4CEB; mov [ebx],ax;
///////    lea    eax,Mn // -> ����� �������� (dw)
    mov    eax,Mn
    mov    ebx,Hp // -> �����
    mov    edi,Mt // = ��� ��������
    mov    edx,PosMixed // ������� ��������
    lea    ecx,CSBuffer // -> ����� �� ~20h ����
    push   0
    push   0
    push   -1
    push   0
    push   0
    push   -1
    push   edx  // ������� �� �����
    push   ecx  // �� �� ������ �� �����
    push   eax  // �� �� ����� ��������
    push   edi   // = ��� ��������
    push   ebx
    mov    ecx,0x6992B8 // [BASE]+ 109700h
    mov    ecx,[ecx]
    mov    eax,0x04AC270 
    call   eax
    mov    ecx,eax
//    mov ebx,0x4AE5DB; mov eax,0x006A016A; mov [ebx],eax;
//    mov eax,0xCE8B006A; mov [ebx+4],eax; mov al,0xE8;
//    mov [ebx+8],al; mov eax,0xFFF68F58; mov [ebx+9],eax;
//    mov ebx,0x4AC5FD; mov eax,0x006A016A; mov [ebx],eax;
//    mov eax,0x0189006A; mov [ebx+4],eax; mov ax,0xCB8B;
//    mov [ebx+8],ax; mov al,0xE8; mov [ebx+10],al;
//    mov eax,0xFFF6AF34; mov [ebx+11],eax; mov ebx,0x4AE3A4;
//    mov ax,0x758B; mov [ebx],ax;
  }
  if(QuickBattle()){
    __asm{
//      mov ebx,0x5C7603; mov eax,0x046A016A; mov [ebx],eax;
//      mov eax,0x02E8016A; mov [ebx+4],eax; mov ax,0x03BC;
//      mov [ebx+8],ax; xor al,al; mov [ebx+10],al;
    }
  }
//  if(_ECX==0) Mn=*Mnp=0; // �� �����
  // 3.58 fix
  G2B_CompleteAI=oldCAI;
  _ECX(Dummy)
  RETURN(Dummy)
}

_Dwelling_ *FindDwellStr(_MapItem_ *Mi)
{
  #include "templ.h"
  int        x,y,l,size,n;
  _Dwelling_ *dwst;
  _MapItem_  *Mi0;

  Mi0=GetMapItem0();
  size=GetMapSize();
  n=Mi-Mi0;
  l=n/(size*size);
  n=n%(size*size);
  y=n/size;
  x=n%size;
  dwst=FindDwelling(x,y,l);
  RETURN(dwst)
}

int HeroHasArt(_Hero_ *hp,int ANum)
{
  #include "templ.h"
  if(hp==0) RETURN(0)
  for(int i=0;i<19;i++){ if(hp->IArt[i][0]==ANum) RETURN(1) } RETURN(0)
}  

int CheckForCreature(_Hero_ *hp,int type)
{
  #include "templ.h"
  for(int i=0;i<7;i++){
    if(hp->Ct[i]==type) RETURN(1) // ������ ������
  }
  RETURN(0)
}

// get name of artefact
char *GetArtName(int number)
{
  #include "templ.h"
  char *zret;
  __asm{
    mov    eax,0x660B68
    mov    eax,[eax]
    mov    edx,number
    shl    edx,5
    mov    eax,[edx+eax]
    mov    zret,eax
  }
  RETURN(zret)
}  
// get name of spell
char *GetSpellName(int number)
{
  #include "templ.h"
  char *zret;
  __asm{
    mov    edx,0x687FA8
    mov    edx,[edx]
    mov    eax,number
    mov    ecx,eax
    shl    ecx,4
    add    ecx,eax
    mov    eax,[edx+8*ecx+0x10]
    mov    zret,eax
  }
  RETURN(zret)
}  
//  ��� �������� � ������������ ������
char *GetBuildName(int town,int build)
{
  #include "templ.h"
  char *zret;
  if(town>=24) town-=24;
  __asm{
    mov    ecx,town    //???  = ����� ���� ������ + 24 (0x16)
//  sub    ecx,00000016
    mov    edx,build   //???  = ������ ��������
    mov    eax,0x460CC0
    call   eax         // = eax -> ��� ��������� � ������
    mov    zret,eax; 
  }
  RETURN(zret)
}  
/*
static int  *GEB_po,GEB_town,GEB_build,GEB_ind;
static char *GEB_ret;
char *_GetErmBuildingName(void){
  asm pusha
  GEB_town=_ECX;
  GEB_build=_EDX;
  if(GEB_build>=0x1E){ // dwellings
    GEB_po=(int *)0x6A6298; GEB_ind=(GEB_town*14+GEB_build); GEB_ret=(char *)GEB_po[GEB_ind];
  }else if(GEB_build>=0x11){
    GEB_po=(int *)0x6A53F8; GEB_ind=(GEB_town*11+GEB_build); GEB_ret=(char *)GEB_po[GEB_ind];
  }else if(GEB_build==0x0F){
    GEB_po=(int *)0x6A5464; GEB_ind=GEB_town*11; GEB_ret=(char *)GEB_po[GEB_ind];
  }else{
    GEB_po=(int *)0x6A654C; GEB_ind=GEB_build; GEB_ret=(char *)GEB_po[GEB_ind];
  }
  asm popa
  asm mov eax,GEB_ret
  return (char *)_EAX;
}
*/
/*
cmp    edx,0x11
jge    M1
cmp    edx,0x0F
jne    M2
lea    eax,[ecx][ecx]*4
lea    ecx,[ecx][eax]*2
mov    eax,[0x6A5464][ecx]*4
retn
M2:
mov    eax,[0x6A654C][edx]*4
retn
M1:
cmp    edx,0x1E
jge    M3
lea    eax,[ecx][ecx]*4
add    edx,ecx
lea    ecx,[edx][eax]*2
mov    eax,[0x6A53F8][ecx]*4
retn
M3:
lea    eax,[0][ecx]*8
sub    eax,ecx
lea    ecx,[edx][eax]*2
mov    eax,[0x6A6298][ecx]*4
retn
*/

// �������� �������
char *GetMonName(int number,int oneMORE)
{
  #include "templ.h"
  char *zret;
  int shifter;
  if(oneMORE) shifter=4; else shifter=0;
  __asm{
    mov    ecx,number //??? = ��� �������
    lea    edx,[8*ecx] 
    sub    edx,ecx
    lea    ecx,[ecx+4*edx]
    mov    edx,0x6747B0
    mov    edx,[edx]
    add    edx,shifter
    mov    eax,[edx+4*ecx+0x14] //-> �������� ������� �� �����
//  mov    ecx,[edx+4*ecx+18] -> �������� ������� �� �����
    mov    zret,eax
  }
  RETURN(zret)
}  

int TimeRandom(int Low, int High)
{
  #include "templ.h"
  if(High<=Low) RETURN(Low)
  int del=High-Low+1;
  Dword ctime=Service_timeGetTime();
  int ret=((int)((ctime/100)&0x7FFFFFFF))%del+Low;
  RETURN(ret)
}

// ��������� �����
char *GetSSkillName(int number)
{
  #include "templ.h"
  char *zret;
  __asm{
    mov    ecx,0x67DCF0
    mov    ecx,[ecx]
    mov    eax,number
    inc    eax
//    mov    edx,eax
//    shr    edx,0x1F
//    add    eax,edx
    shl    eax,4
    mov    eax,[eax+ecx-0x10]
    mov    zret,eax
  }
  RETURN(zret)
}  
//////////////////////////////
static int LeftCr[2][7];
//static char CrBuffer[1024];
void CrChangeDialog(_Hero_ *hp,int Mt0,int Mn0,int Mt1,int Mn1,int Mt2,int Mn2,
int Mt3,int Mn3,int Mt4,int Mn4,int Mt5,int Mn5,int Mt6,int Mn6)
{
  #include "templ.h"
  LeftCr[0][0]=Mt0; 
  LeftCr[1][0]=Mn0; 
  LeftCr[0][1]=Mt1; 
  LeftCr[1][1]=Mn1; 
  LeftCr[0][2]=Mt2; 
  LeftCr[1][2]=Mn2; 
  LeftCr[0][3]=Mt3; 
  LeftCr[1][3]=Mn3; 
  LeftCr[0][4]=Mt4; 
  LeftCr[1][4]=Mn4; 
  LeftCr[0][5]=Mt5; 
  LeftCr[1][5]=Mn5; 
  LeftCr[0][6]=Mt6; 
  LeftCr[1][6]=Mn6; 
  __asm{
    mov    ecx,hp
    lea    edx,LeftCr
    push   1
    mov    eax,0x5D16B0
    call   eax
  } 
  RETURNV
}

void SetKeyMaster(int owner,int key,int val)
{
  #include "templ.h"
  int i,j;
  Byte vb;
  __asm{
    mov   eax,0x699538
    mov   eax,[eax]
    add   eax,key
    add   eax,0x4E364
    mov   al,[eax]
    mov   vb,al
  }
  for(i=0,j=1;i<8;i++,j<<=1){ if(i==owner) break; }
  if(val) vb|=(Byte)j; else vb&=(Byte)~j;
  __asm{
    mov   eax,0x699538
    mov   eax,[eax]
    add   eax,key
    add   eax,0x4E364
    mov   bl,vb
    mov   [eax],bl
  }
  RETURNV
}
int GetKeyMaster(int owner,int key)
{
  #include "templ.h"
  int i,j;
  Byte vb;
  __asm{
    mov   eax,0x699538
    mov   eax,[eax]
    add   eax,key
    add   eax,0x4E364
    mov   al,[eax]
    mov   vb,al
  }
  for(i=0,j=1;i<8;i++,j<<=1){ if(i==owner) break; }
  if((vb&j)) RETURN(1) else RETURN(0)
}

static int SC_Type,SC_Num,SC_Pos,SC_Side,SC_Slot,SC_Redraw,SC_Flags;
static Byte *SC_MStruct;
Byte *SammonCreatureEx(int type,int num,int pos,int side,int slot,int redraw,int Flags)
{
  #include "templ.h"
  SC_Type=type; // ��� ��������
  SC_Num=num; // ����� �������
  SC_Pos=pos; // ������� �� ����
  SC_Side=side; // ������� ������ (0,1)
  SC_Slot=slot; // ���� � ����� �����
  SC_Redraw=redraw; // ��������������
  SC_Flags=Flags; // ����� ���������� ��������
  __asm{
//005A775B 8B83F4000000   mov    eax,[ebx+000000F4] ebx -> ������������ ������
    mov    ecx,0x699420
    mov    ecx,[ecx]
    push   SC_Redraw
    push   SC_Flags
    push   SC_Pos     //edx  = ���������� ������ ����
    push   SC_Num     //ecx  = ����������
    push   SC_Type    //00000030 = ����� �������
    push   SC_Side    //eax = ����� ������ (0,1)
//005A776D 8BCF           mov    ecx,edi -> ������ ��������
    mov    eax,0x479A30
    call   eax
//005A776F E8BC22EDFF     call   H3WOG.00479A30
    mov    edx,eax
    mov    SC_MStruct,eax  //-> ��. �� ������ �������
    or     edx,edx
    je     l_notset
    mov    eax,SC_Slot     //[ebp+0C] = ����� ����� � ����� �����
//005A7779 8BCF           mov    ecx,edi
    mov    [edx+0x5C],eax
////    mov    ecx,0x699420
////    mov    ecx,[ecx]
////    mov    eax,0x493290
////    call   eax
//005A777E E80DBBEEFF     call   H3WOG.00493290
  }
  CrExpBon::ClearCrExpBonBFStartStat(MonIndex(SC_MStruct));
l_notset:
  RETURN(SC_MStruct)
}
Byte *SammonCreature(int type,int num,int pos,int side,int slot,int redraw){
  #include "templ.h"
  RETURN(SammonCreatureEx(type,num,pos,side,slot,redraw,0));
}

Byte *SammonCreatureIfPossible(int type,int num,int pos,int side,int slot,int redraw,int Flags){
  #include "templ.h"
  char *bh=(char *)GetHexStr(pos); if(bh==0) RETURN(0)
  if(bh[0x10]&0x3F) RETURN(0) // �����������
  RETURN(SammonCreatureEx(type,num,pos,side,slot,redraw,Flags));
}
int ArtDisabled(int art)
{
  #include "templ.h"
  char *en;
  if((art<0)||(art>=ARTNUM)){ MError("\"ArtDisabled\" wrong Artifact number."); RETURN(0) }
  __asm{
    mov  eax,BASE
    mov  eax,[eax]
    add  eax,0x4E2B4
    mov  en,eax
  }
  if(en[art]!=0) RETURN(1) // ��� ��������
  RETURN(0)
}

void ArtDisabledSet(int art,int disab)
{
  #include "templ.h"
  char *en;
  if((art<0)||(art>=ARTNUM)){ MError("\"ArtDisabbledSet\" wrong Artifact number."); RETURNV }
  __asm{ 
    mov  eax,BASE
    mov  eax,[eax]
    add  eax,0x4E2B4
    mov  en,eax
  }
  en[art]=(char)disab;
  RETURNV
}

_ArtSetUp_ *GetArtBase(void)
{
  #include "templ.h"
  _ArtSetUp_ *zret;
  __asm{
    mov   eax,0x660B68
    mov   eax,[eax]
    mov   zret,eax
  }
  RETURN(zret)
}

static int  FOH_HerNum;
static Byte FOH_Buffer[0x400];

void FortOnHill(int hero)
{
  #include "templ.h"
  __asm{
    mov    eax,0x69CCFC
    mov    eax,[eax]
    or     eax,eax
    je     lexit
    mov    edx,[eax+4]
    mov    FOH_HerNum,edx
    mov    edx,hero
    mov    [eax+4],edx

    mov    ecx,0x06992B0
    mov    ecx,[ecx]
    push   1
    push   0
    mov    eax,0x50CEA0
    call   eax
    mov    ecx,0x6992B0
    mov    ecx,[ecx]
    push   1
    mov    eax,0x50D7B0
    call   eax
    lea    ecx,FOH_Buffer
    mov    eax,0x4E76B0
    call   eax
    push   -1
    push   -1
    lea    ecx,FOH_Buffer
//mov    dword ptr [ebp-04],00000001
    mov    eax,0x5FF800
    call   eax
    lea    ecx,FOH_Buffer
    mov    eax,0x4E7F50
    call   eax
    lea    ecx,FOH_Buffer
//mov    dword ptr [ebp-04],FFFFFFFF
    mov    eax,0x4E7ED0
    call   eax

    mov    eax,0x69CCFC
    mov    eax,[eax]
    mov    edx,FOH_HerNum
    mov    [eax+4],edx
  }
lexit:;
  RETURNV
}

int *MonInTownBase(int Town){ 
  #include "templ.h"
  RETURN((int *)(0x6747B4+Town*14*4))
}

Byte  AGE_Buf[0x100];
Dword AGE_ebp_4;
Dword AGE_retval;
int AddGlbEvent(void)
{
  #include "templ.h"
  __asm{
    pusha
    mov    eax,-1
    mov    AGE_retval,eax
    mov    al,0 //[ebp+0B] ��� ���������
    xor    ebx,ebx
    push   ebx
    lea    ecx,AGE_Buf
    mov    [ecx],al
    mov    esi,BASE
    mov    esi,[esi]
    add    esi,0x1FB70
    mov    eax,0x404130 // ��������� ������.
    call   eax
    mov    edi,[esi+0x84]
    add    esi,0x80
    cmp    edi,ebx
    mov    AGE_ebp_4,ebx
    jne    l_m1
    xor    edx,edx
    jmp    l_m2
  }
l_m1:
  __asm{
    mov    ecx,[esi+0x08]
    mov    eax,0x4EC4EC4F
    sub    ecx,edi
    imul   ecx
    sar    edx,4
    mov    ecx,edx
    shr    ecx,0x1F
    add    edx,ecx
  }
l_m2:
  __asm{
//    mov    ecx,[ebp-10]
//    cmp    edx,ecx
    cmp    edi,ebx
    jne    l_m3
    xor    edx,edx
    jmp    l_m4
  }
l_m3:
  __asm{
    mov    edx,[esi+8]
    mov    eax,0x4EC4EC4F
    sub    edx,edi
    imul   edx
    sar    edx,4
    mov    eax,edx
    shr    eax,0x1F
    add    edx,eax
  }
l_m4:
  __asm{
    mov    eax,[esi+8]
    lea    edi,AGE_Buf
//     sub    ecx,edx
    mov    ecx,1 // ��������� ����
    push   edi
    push   ecx
    push   eax
    mov    ecx,esi
    mov    eax,0x5084C0  // ��������� ����
    call   eax
//...
    xor    edi,edi
    mov    eax,[esi+4]
    test   eax,eax
    je     l_m5
    mov    ecx,[esi+8]
    sub    ecx,eax
    mov    eax,0x4EC4EC4F
    imul   ecx
    sar    edx,4
    mov    ecx,edx
    shr    ecx,0x1F
    add    edx,ecx
    cmp    edi,edx
    jnb    l_m5
    dec    edx
    mov    AGE_retval,edx
  }
l_m5:
  __asm{
    popa
  }
  RETURN(AGE_retval)
}

int DoesExist(int Player)
{
  #include "templ.h"
  __asm{
    mov   eax,BASE
    mov   eax,[eax]
    add   eax,0x1F636
    add   eax,Player
    mov   al,[eax]
    mov   CDummy,al
  }
  if(CDummy==0) RETURN(1) else RETURN(0)
}

_Position_ *GetPositionBase(void)
{
  #include "templ.h"
  _Position_ *zret;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x1FB84 // -> ����
    mov    eax,[ebx]
    mov    zret,eax
  }
  RETURN(zret)
}
int GetPositionNum(void)
{
  #include "templ.h"
  _Position_ *ars,*are;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x1FB84 // -> ����
    mov    eax,[ebx]
    mov    ars,eax
    mov    eax,[ebx+4]
    mov    are,eax
  }
  if(ars==0) RETURN(0)
  RETURN(are-ars)
}

_CastleSetup_ *GetTownBase(void)
{
  #include "templ.h"
  _CastleSetup_ *zret;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x21614 // -> ����
    mov    eax,[ebx]
    mov    zret,eax
  }
  RETURN(zret)
}
int GetTownNum(void)
{
  #include "templ.h"
  _CastleSetup_ *ars,*are;
  __asm{
    mov    ebx,BASE
    mov    ebx,[ebx]
    add    ebx,0x21614 // -> ����
    mov    eax,[ebx]
    mov    ars,eax
    mov    eax,[ebx+4]
    mov    are,eax
  }
  if(ars==0) RETURN(0)
  RETURN(are-ars)
}

void ShowThis(int x,int y,char level,int delay)
{
//   0x698A48 dd -> ����� ��������� (dw*l*dY*dX) l 0x4BD63D
//   0x6992B8 dd -> advManager
// ��������� � �������
// esi->AdvManager
  #include "templ.h"
 __asm{
   mov    ebx,x
   mov    edi,y
   mov    esi,0x6992B8
   mov    esi,[esi]
  mov    edx,[esi+0xE4]
  push   1
  push   0
  mov    ecx,esi
  mov    eax,0x4175E0
  call   eax
   mov    ax,[esi+0xE4]
   lea    ecx,[ebx-9] //ecx=x-9
   xor    ecx,eax
   lea    edx,[edi-8] //edx=y-8
   and    ecx,0x3FF
   xor    ecx,eax
   mov    ax,[esi+0xE6]
   xor    edx,eax
   mov    [esi+0xE4],cx
   and    edx,0x3FF
   mov    ecx,esi
   xor    edx,eax
   mov    al,level // al=level
   and    eax,0xF
   and    dh,0xC3
   shl    eax,0xA
   or     edx,eax
   mov    [esi+0xE6],dx
   push   0
   mov    eax,0x40F7D0
   call   eax
   push   0
   push   0
   push   0
   push   1
   push   1
   mov    ecx,esi
   mov    eax,0x4136F0
   call   eax
   push   0
   push   0
   mov    ecx,esi
   mov    eax,0x40F1D0
   call   eax
   mov    eax,0x4F8970
   call   eax // �������� ����� (���������)
   mov    ecx,eax
   add    ecx,delay  //00007D0 �������� ����� 2-� ������
   mov    eax,0x4F8980
   call   eax // ��������� �� ����� �������
  push   0
  mov    ecx,esi
  mov    eax,0x40F7D0
  call   eax
  push   0
  push   0
  mov    ecx,esi
  mov    eax,0x40F1D0
  call   eax
 }
  RETURNV
}
///////////////////////
/////////////////////////////
static char *WO_Str;
int WeekOf(void)
{
  #include "templ.h"
  int ret=Random(0,14);
  switch(NextWeekOf){
    case 1: // �������� ������ �����
      __asm{
        mov   eax,0x4C846C
        mov   dword ptr [eax],5
        mov   eax,0x4C848A
        mov   dword ptr [eax],2
      }
      break;
    case 0:  // ��� ������
      __asm{
        mov   eax,0x4C846C
        mov   dword ptr [eax],4
        mov   eax,0x4C848A
        mov   dword ptr [eax],1
      }
      break;
    default: Error(); break;
  }
  if(NextWeekMess){ // ��������� ��������� � ����������
    if((NextWeekMess<1)||(NextWeekMess>500)){
      Error();
    }else{
// 3.57f formating
//      _EDX=(Dword)&ERMString[NextWeekMess-1];
      WO_Str=ERMString[NextWeekMess-1];
      WO_Str=ERM2String2(33,WO_Str);
      __asm{
        mov   edx,WO_Str
        mov   eax,0x4CCA5B
        mov   [eax],edx
      }
    }
  }else{
    __asm{
      mov   eax,0x4CCA5B
      mov   [eax],0x697428
    }
  }
  RETURN(ret)
}

int MonthOf(void)
{
  #include "templ.h"
  int ret=Random(0,10);
  switch(NextMonthOf){
    case 3: // ����
      ret=10;
      __asm{
        mov   eax,0x4C8C51
        mov   word ptr [eax],0x9090
      }
      break;
    case 2: // *2 �������
      ret=6;
      break;
    case 1: // ������
      ret=2;
      break;
    case 0:  // ��� ������
      __asm{
        mov   eax,0x4C8C51
        mov   word ptr [eax],0x7528
      }
      break;
    default: Error(); break;
  }
  RETURN(ret)
} 
int MonthOf2(void)
{
  #include "templ.h"
  int retval=Random(0,12);
  switch(NextMonthOf){
    case 2: // *2 �������
      __asm{
        mov   eax,0x4C8C6D
        mov   dword ptr [eax],0
        lea   eax,NextMonthOfMonster
        mov   retval,eax
      }
      break;
    default:  // ��� ������
      __asm{
        mov   eax,0x4C8C6D
        mov   dword ptr [eax],0x63E678
      }
      break;
  }
  RETURN(retval)
} 

char *GetHOTableBase(void)
{
  #include "templ.h"
  __asm{
    mov    eax, BASE
    mov    eax,[eax]
    add    eax,0x04DF18
    mov    CPDummy,eax
  }
  RETURN(CPDummy)
}

int *GetHHTableBase(void)
{
  #include "templ.h"
  __asm{
    mov    eax, BASE
    mov    eax,[eax]
    add    eax,0x04DFB4
    mov    IPDummy,eax
  }
  RETURN(IPDummy)
}

int IsPlayerKilled(int Player,int val)
{
  #include "templ.h"
  char *ps;
  __asm{
    mov    eax, BASE
    mov    eax,[eax]
    add    eax,0x01F636
    mov    ps,eax
  }
  if(val!=-1) ps[Player]=(char)val;
  RETURN(ps[Player])
}

static Dword PO_cmp;
static Byte  PO_buf[0x60];
// +0  -38
// +4  -34
// +8  -30
// +9  -2F
// +A  -2E
// +C  -2C
// +10 -28
// +14 -24
int PlaceObstacle(int object,int position)
{
  #include "templ.h"
  Dword odesc=object*20+0x63C7C8;
  __asm{
// edi = 63C7C8+4*5*�����(0...0x5A)
    mov    edi,odesc
    mov    ecx,[edi+0x10]   // -> ��� def � ����.
    mov    eax,0x55C9C0 // ��������
    call   eax
    mov    esi,0x699420
    mov    esi,[esi]
    mov    PO_cmp,esi
    mov    ecx,[esi+0x13D60] // esi-> CombatManager
    mov    dword ptr [PO_buf+0],eax //[ebp-38],eax // ->����. def
    mov    ebx,position      // = �������
    or     eax,0xFFFFFFFF
    mov    byte ptr [PO_buf+9],al//[ebp-2F],al
    mov    dword ptr [PO_buf+0x14],eax//[ebp-24],eax
    add    esi,0x13D58
    lea    eax,dword ptr [PO_buf+0]//[ebp-38]
    push   eax
    mov    dword ptr [PO_buf+4],edi//[ebp-34],edi
    push   1
    xor    edi,edi
    push   ecx
    mov    ecx,esi
    mov    byte ptr [PO_buf+8],bl//[ebp-30],bl
    mov    byte ptr [PO_buf+0xA],1//byte ptr [ebp-2E],01
    mov    dword ptr [PO_buf+0xC],edi//[ebp-2C],edi
    mov    dword ptr [PO_buf+0x10],edi//[ebp-28],edi
    mov    eax,0x46AA60
    call   eax
    mov    eax,[esi+4]
    cmp    eax,edi
    jne    l_c1
    xor    edx,edx
    jmp    l_c2
  }
l_c1:
  __asm{
    mov    esi,[esi+8]
    sub    esi,eax
    mov    eax,0x2AAAAAAB
    imul   esi
    sar    edx,2
    mov    eax,edx
    shr    eax,0x1F
    add    edx,eax
  }
l_c2:
  __asm{
    push   2
    dec    edx
    push   ebx
    lea    ecx,[PO_buf]
    push   edx
    push   ecx
    mov    ecx,PO_cmp
    mov    eax,0x466590
    call   eax
//    mov    edx,[ebp-44]
//    push   edx
//    mov    eax,0x60B0F0
//    call   eax
//    add    esp,4
  }
  RETURN(1)
}

void HitMonster(Byte *mon, int damage)
{
  #include "templ.h"
  __asm{
    mov    ecx,mon // ->������ ��� ������
    mov    eax,damage
    push   eax     // =���������� ����� �������
    mov    eax,0x443DB0
    call   eax
  }
  RETURNV
}

void RedrawBF(void)
{
  #include "templ.h"
  __asm{
    mov    ecx,0x699420 //-> CombatManager
    mov    ecx,[ecx]
    push   0
    push   -1
    mov    eax,0x468570
    call   eax
  }
  RETURNV
}

static int CS_Spell,CS_heroMONSTER,CS_Pos,CS_HSkill,CS_MSkill;
void CastSpell(int Spell,int heroMONSTER,int Pos,int HSkill,int MSkill)
{
  #include "templ.h"
  CS_Spell=Spell;
  CS_heroMONSTER=heroMONSTER;
  CS_Pos=Pos;
  CS_HSkill=HSkill;
  CS_MSkill=MSkill;
  __asm{
    push   CS_HSkill // ������ - ���������� �������
    push   CS_MSkill
    push   -1
    push   CS_heroMONSTER // Hero=0, Monster=1, Artifact=2
    push   CS_Pos // may be -1
    push   CS_Spell
    mov    ecx,0x699420 //-> CombatManager
    mov    ecx,[ecx]
    mov    eax,0x5A0140
    call   eax
  }
  RETURNV
}

Byte *GetHexStr(int Pos)
{
  #include "templ.h"
  if((Pos<0)||(Pos>0xBA)) RETURN(0)
  __asm{
    mov    eax,Pos
    lea    ecx,[8*eax]
    sub    ecx,eax
    shl    ecx,4
    mov    eax,0x699420 //-> CombatManager
    mov    eax,[eax]
    lea    eax,[ecx+eax]
    add    eax,0x1C4
    mov    BPDummy,eax
  }
  RETURN(BPDummy)
}

static int MS2B_x,MS2B_y;
static Dword MS2B_div,MS2B_val;
int MapSmPos(_MouseStr_ *MouseStr,Dword *rMixPos)
{
  #include "templ.h"
  int x,y,l;
  *rMixPos=0;
  if(MouseStr->Item==1){
    __asm{
      mov    eax,0x6783CC
      mov    eax,[eax]
      cmp    eax,0x24
      je     l_24
      cmp    eax,0x48
      je     l_48
      cmp    eax,0x6C
      je     l_6C
// XL
      mov    MS2B_div,0x3F800000
      jmp    l_all
    }
l_6C: //L
    __asm{
      mov    MS2B_div,0x3FAAA993
      jmp    l_all
    }
l_48: //M
    __asm{
      mov    MS2B_div,0x40000000
      jmp    l_all
    }
l_24: //S
    __asm{
      mov    MS2B_div,0x40800000
    }
l_all:
    __asm{
      mov    ebx,0x6992B8
      mov    ebx,[ebx]
      mov    edx,[ebx+0x44] // ebx->advManager
      mov    eax,[edx+0x4C]
      movsx  eax,word ptr [eax+0x1A] // left border of map
      mov    edi,MouseStr
      mov    ecx,[edi+0x14] // edi->mouse structure
      sub    ecx,eax
      mov    MS2B_val,ecx
      fild   MS2B_val 
      fstp   MS2B_val 
      fld    MS2B_val 
      fdiv   dword ptr MS2B_div 
      mov    eax,0x617F94
      call   eax
      mov    MS2B_y,eax // y
      mov    edx,[ebx+0x44] // ebx->advManager
      mov    eax,[edx+0x4C]
      movsx  edx,word ptr [eax+0x18]
      mov    eax,MouseStr // ->mouse structure
      mov    ecx,[eax+0x10] // x or
      sub    ecx,edx
      mov    MS2B_val,ecx
      fild   MS2B_val
      fstp   MS2B_val
      fld    MS2B_val
      fdiv   dword ptr MS2B_div
      mov    eax,0x617F94
      call   eax
      mov    MS2B_x,eax
      mov    eax,[ebx+0xE4]
      mov    MS2B_val,eax
    }
    MixedPos(&x,&y,&l,MS2B_val);
    *rMixPos=PosMixed(MS2B_x,MS2B_y,l);
    RETURN(1)
  }else if((MouseStr->Item==37)||(MouseStr->Item==0)){
    __asm{
      mov    eax,0x6992B8
      mov    eax,[eax]
      mov    eax,[eax+0xE8]
      mov    MS2B_val,eax
      lea    ecx,MS2B_val
      mov    eax,0x4B1090
      call   eax
      test   al,al        // = 1 - Ok
      je     l_out
    }
    *rMixPos=MS2B_val;
    RETURN(1)
l_out:
    RETURN(0)
  }else{
    RETURN(0)
  }
}

int GetVisability(int x,int y,int l)
{
  #include "templ.h"
  int   msz;
  Word *vmp;
  __asm{
    mov    eax,0x698A48
    mov    eax,[eax]
    mov    vmp,eax
    mov    eax,0x6783CC
    mov    eax,[eax]
    mov    msz,eax
  }
  RETURN(vmp[x+y*msz+l*msz*msz])
}
void SetVisability(int x,int y,int l,int v)
{
  #include "templ.h"
  int   msz;
  Word *vmp;
  __asm{
    mov    eax,0x698A48
    mov    eax,[eax]
    mov    vmp,eax
    mov    eax,0x6783CC
    mov    eax,[eax]
    mov    msz,eax
  }
  vmp[x+y*msz+l*msz*msz]=(Word)v;
  RETURNV
}

int IsStartUp(void)
{
  #include "templ.h"
  __asm{
    mov     eax,0x698450
    mov     eax,[eax]
    mov     IDummy,eax
  }
  RETURN(IDummy)
}

int Int(float f){
  #include "templ.h"
  int i=(int)f;
  if((float)i>f) i--;
  RETURN(i)
}

int RemoveCreature(int *Mt,int *Mn,int *Mn1,int *Mn2,int pers) // pers �������� �� 100
{
  #include "templ.h"
  int i,j,n,n0,v,mt[7],mn[7],ms[7];

  for(i=0;i<7;i++){ mt[i]=Mt[i]; mn[i]=Mn[i]; ms[i]=1; Mn1[i]=0; Mn2[i]=0; }
  for(i=1;i<7;i++) for(j=0;j<i;j++) if(mt[i]==mt[j]){ ms[j]++; mn[j]+=mn[i]; mt[i]=-1; }
  for(i=0;i<7;i++){
    if(mt[i]==-1) continue;
    n=(mn[i]*pers)/100; n0=mn[i]-n;
    for(j=0;j<7;j++){
      if(Mt[j]!=mt[i]) continue;
      Mn1[j]=Mn[j];
      if(n==0) continue;
      if(ms[i]==1){
        Mn1[j]=Mn[j]-n; break;
      }else{
        v=Int((float)(Mn[j]*n0/mn[i])); if(v<0) v=0;
        Mn1[j]=v; n-=(Mn[j]-Mn1[j]); ms[i]--;
      }
    }
  }
  for(i=0;i<7;i++){ Mn2[i]=Mn[i]-Mn1[i]; if(Mn2[i]<0) Mn2[i]=0; }
  for(i=0;i<7;i++){ if(Mn[i]!=Mn1[i]) RETURN(1) }
  RETURN(0)
}

void AddCreature(int *Mt,int *Mn,int *Mt1,int *Mn1)
{
  #include "templ.h"
  int i,j;

  for(i=0;i<7;i++){
    if(Mt[i]==-1) continue;
    for(j=0;j<7;j++){
      if(Mt[i]==Mt1[j]){ Mn[i]+=Mn1[j]; Mt1[j]=-1; }
    }
  }
  for(i=0;i<7;i++){
    if(Mt1[i]==-1) continue;
    for(j=0;j<7;j++){
      if(Mt[j]==Mt1[i]){ Mn[j]+=Mn1[i]; Mt1[i]=-1; }
      else if(Mt[j]==-1){ Mt[j]=Mt1[i]; Mn[j]=Mn1[j]; Mt1[i]=-1; }
    }
  }
  RETURNV
}

void RedrawHeroScreen(_Hero_ *hp)
{
  #include "templ.h"
  __asm{
    mov    eax,hp
    mov    ecx,0x698B70
    mov    [ecx],eax
    mov    ecx,0x698AC8
    mov    ecx,[ecx]
    mov    eax,0x4E1CC0
    call   eax
    mov    ecx,0x698AC8
    mov    ecx,[ecx]
    mov    edx,[ecx]
    push   0x0000FFFF
    push   0xFFFF0001
    push   1
    call   [edx+0x14]
  }
  RETURNV
}

int GetObel(int Player,int Index){
  #include "templ.h"
  int   st;
  Byte mask,*op;
  __asm{
    mov    eax,BASE
    mov    eax,[eax]
    add    eax,0x4E3E9
    mov    op,eax
  }
  if(Player==-1) Player=CurrentUser();
  if((Player<0)||(Player>7)){ MError("\"GetObel\" wrong Player index (0...7)"); RETURN(0) }
  mask=(Byte)(1<<Player);
  if((Index<0)||(Index>47)){ MError("\"GetObel\" wrong Obelisk index (0...47)"); RETURN(0) }
  st=op[Index];
  if(st&mask) RETURN(1)
  RETURN(0)
}

void SetObel(int Player,int Index,int State)
{
  #include "templ.h"
  int i;
  Byte mask,*stp,*op;
  __asm{
    mov    eax,BASE
    mov    eax,[eax]
    add    eax,0x4E3E9
    mov    op,eax
  }
  if(Player==-2){ // ����
    if(Index==-1){ // ���
      for(i=0;i<48;i++){ if(State) op[i]=1; else op[i]=0; }
      RETURNV
    }
    if((Index<0)||(Index>47)){ MError("\"SetObel\" wrong Obelisk index (0...47)"); RETURNV }
    stp=&op[Index];
    if(State) *stp=1; else *stp=0;
    RETURNV
  }
  if(Player==-1) Player=CurrentUser();
  if((Player<0)||(Player>7)){ MError("\"SetObel\" wrong Player index (0...7)"); RETURNV }
  mask=(Byte)(1<<Player);
  if(Index==-1){ // ���
    for(i=0;i<48;i++){ if(State) op[i]|=mask; else op[i]&=Byte(~mask); }
    RETURNV
  }
  if((Index<0)||(Index>47)){ MError("\"SetObel\" wrong Obelisk index (0...47)"); RETURNV }
  stp=&op[Index];
  if(State) *stp|=mask; else *stp&=Byte(~mask);
  RETURNV
}

char *SpellDisBase(void)
{
  #include "templ.h"
  __asm{
    mov     eax,BASE
    mov     eax,[eax]
    add     eax,0x4A
    mov     CPDummy,eax
  }
  RETURN(CPDummy)
}

// �������� �������� �����
void AddMon2Hero(_Hero_ *hp,int t,int n,int HUM_ai)
{
  #include "templ.h"
  _MonArr_ *ma=(_MonArr_ *)&hp->Ct[0];
  __asm{
    mov    ecx,ma
    mov    edx,hp
    mov    esi,n
    mov    edi,t
    push   -1
    push   esi
    push   edi
    mov    eax,0x44A9B0
    call   eax
    mov    DDummy,eax
  }
  if(DDummy) RETURNV // ��������
  if(HUM_ai){
    __asm{
      mov    ecx,hp
      mov    edx,t
      mov    eax,n
      push   eax
      mov    eax,0x5D15D0
      call   eax
    }
  }else{
    __asm{
      mov    ecx,hp
      mov    edx,t
      mov    eax,n
      push   eax
      mov    eax,0x52C140
      call   eax
    }  
  }
  RETURNV
}

int GetCurHero(void)
{
  #include "templ.h"
  int pl=CurrentUser();
  if((pl<0)||(pl>7)) RETURN(-1)
  __asm{
    mov    eax,pl
    mov    edx,BASE
    mov    edx,[edx]
    lea    eax,[eax+4*eax]
    lea    eax,[eax+8*eax]
    mov    eax,[edx+8*eax+0x20AD4]
    mov    IDummy,eax
  }
  RETURN(IDummy)
}

// 3.58
static int EA_Buf[5]; // ���. ������ 2 ������ ��������
void EquipArtifact(_Hero_ *hp,int ArtNum,int ArtSNum)
{
  #include "templ.h"
  EA_Buf[0]=ArtNum;
  EA_Buf[1]=ArtSNum;
  __asm{
    mov   ecx,hp
    lea   eax,EA_Buf
    push  1
    push  1
    push  eax
    mov   eax,0x4E32E0
    call  eax
  }
  RETURNV
}

void CastAdvSpell(int Spell)
{
  #include "templ.h"
  __asm{
    mov    ecx,0x69CCFC // cur player
    mov    ecx,[ecx]
    mov    ecx,[ecx+4] // cur hero
    cmp    ecx,0xFFFFFFFF
    je     lexit
    mov    eax,ecx
    shl    eax,6
    add    eax,ecx
    lea    edx,[eax+8*eax]
    mov    eax,0x699538
    mov    eax,[eax]
    lea    esi,[eax+2*edx+0x21620]
    mov    ecx,esi
    mov    eax,0x4E5130
    call   eax
    mov    edx,0x6992D0 //-> heroWindowManager
    mov    edx,[edx]
    mov    edi,0x6992B8 //-> advManager
    mov    edi,[edi]
    mov    ecx,edi
    mov    eax,Spell //= ����� �����
    push   eax
    mov    eax,0x41C610
    call   eax
    push   1
    push   1
    push   1
    mov    ecx,edi
    mov    eax,0x415D40
    call   eax
  }
lexit:;
  RETURNV
}

void ChooseAdvSpell(void)
{
  #include "templ.h"
  __asm{
  // ������� ���������� ����
    mov  ecx,0x6992B0
    mov  ecx,[ecx]
    push 0
    mov  eax,0x50D7B0
    call eax

    mov    ecx,0x6992B8 //-> advManager
    mov    ecx,[ecx]
    mov    eax,0x41C470
    call   eax
  }
  RETURNV
}

Dword GetExpo(int Lvl){
  #include "templ.h"
  Dword Ebp10,Ebp14[2];
  if(Lvl<=0) RETURN(0)
  __asm{
//    mov    ecx,0x699538
//    mov    ecx,[ecx]
//    mov    al,[ecx+0x1F877] // limit in levels
//    test   al,al
//    jbe   _NoLimit
    mov    eax,Lvl
    and    eax,0xFF
    mov    ebx,eax
    cmp    ebx,0xC
    jg     Lvl12pp
    movsx  eax,word ptr [2*ebx+0x679C86]
    mov    DDummy,eax
  }
  RETURN(DDummy)
Lvl12pp:
  __asm{
    movsx  esi,word ptr DS:[0x679C9E]
    movsx  edx,word ptr DS:[0x679C9C]
    mov    eax,esi
    sub    eax,edx
    mov    Ebp10,eax
    fild   dword ptr Ebp10
    fstp   qword ptr Ebp14
    fld    qword ptr Ebp14
    fmul   qword ptr DS:[0x63AC20]
    mov    eax,0x617F94
    call   eax
    add    esi,eax
    cmp    ebx,0xD
    mov    Ebp10,eax
    jle    Lvl12mm
    add    ebx,0xFFFFFFF3
  }
l_Next:
  __asm{
    fild   dword ptr Ebp10
    fstp   qword ptr Ebp14
    fld    qword ptr Ebp14
    fmul   qword ptr DS:[0x63AC20]
    mov    eax,0x617F94
    call   eax
    add    esi,eax
    dec    ebx
    mov    Ebp10,eax
    jne    l_Next
  }
Lvl12mm:  
  __asm mov DDummy,eax
  RETURN(DDummy)
}

int GetLimitLvl(void)
{
  #include "templ.h"
  __asm{
    mov    ecx,0x699538
    mov    ecx,[ecx]
    xor    eax,eax
    mov    al,[ecx+0x1F877] // limit in levels
    mov    IDummy,eax
  }
  RETURN(IDummy)
}

void SetLimitLvl(int NewLvl)
{
  #include "templ.h"
  __asm{
    mov    ecx,0x699538
    mov    ecx,[ecx]
    mov    eax,NewLvl
    mov    [ecx+0x1F877],al // limit in levels
  }
  RETURNV
}
//////////////////////
int MusicVolume(void)
{
  #include "templ.h"
  __asm{
    mov  eax,0x6987B0
    mov  eax,[eax]
    mov    IDummy,eax
  }
  RETURN(IDummy)
}

int EffectVolume(void)
{
  #include "templ.h"
  __asm{
    mov  eax,0x6987B4
    mov  eax,[eax]
    mov    IDummy,eax
  }
  RETURN(IDummy)
}

int GameLevel(void)
{
  #include "templ.h"
  __asm{
    mov  eax,0x6834A4
    mov  eax,[eax]
    mov    IDummy,eax
  }
  RETURN(IDummy)
}
void SetGameLevel(int Val)
{
  #include "templ.h"
  __asm{
    mov  edx,Val
    mov  eax,0x6834A4
    mov  [eax],edx
  }
  RETURNV
}

// all should be the same size
void SplitPath(char *all,char *path,char *name)
{
  #include "templ.h"
  char drive[_MAX_DRIVE];
  char dir[MAX_PATH];
  char fname[MAX_PATH];
  char ext[MAX_PATH];
//void _splitpath( const char *path, char *drive, char *dir, char *fname, char *ext );
//void _makepath( char *path, const char *drive, const char *dir, const char *fname, const char *ext );

  _splitpath(all,drive,dir,fname,ext);
  _makepath(path,drive,dir,0,0);
  _makepath(name,0,0,fname,ext);
  RETURNV
}

void MakePath(char *all,char *path,char *name)
{
  #include "templ.h"
  _makepath(all,0,path,name,0);
  RETURNV
}

static char StrTokDelimit[]=" ,.\t\n\a";
char *Strtok(char *strToken){
  #include "templ.h"
  RETURN( strtok(strToken,StrTokDelimit))
}

char *Strerror( int errnum ){
  #include "templ.h"
  RETURN(strerror(errnum))
}

void Itoa(int val,char *str,int Base){
  #include "templ.h"
  itoa(val,str,Base);
  HexToUpper(str);
  RETURNV
}

int Atoi(char *str){
  #include "templ.h"
  RETURN( atoi(str) )
}

float Atof(char *StrVal){
  #include "templ.h"
  float v;
  double (*pf)(char *);
  *((Dword *)&pf)=0x619366;
/*
  __asm{
    mov   eax,StrVal
    push  eax
    mov   eax,0x619366
    call  eax
    add   esp,4
  }
*/
  v=(float)pf(StrVal);  
  RETURN( v/*atof(str)*/ )
}

int GetDelay(void){
  #include "templ.h"
  __asm{
    mov  eax,0x526C9E
    mov  eax,[eax]
    mov  IDummy,eax
  }
  RETURN(IDummy)
}
void SetDelay(int Value){
  #include "templ.h"
  __asm{
    mov  eax,Value
    mov  ecx,0x526C9E
    mov  [ecx],eax
    mov  ecx,0x526CEE
    mov  [ecx],eax
  }
  RETURNV
}

int GetAutoSave(void){
  #include "templ.h"
  __asm{
    mov  eax,0x6987C0
    mov  eax,[eax]
    mov  IDummy,eax
  }
  RETURN(IDummy)
}
void SetAutoSave(int Value){
  #include "templ.h"
  __asm{
    mov  eax,Value
    mov  ecx,0x6987C0
    mov  [ecx],eax
  }
  RETURNV
}

//static int D8D_Ar[9][2];
// dd object type
// dw object index
// dw object subindex
static Dword D8D_Struct[4];//={1,(Dword)&D8D_Ar[0][0],(Dword)&D8D_Ar[8][0],(Dword)&D8D_Ar[8][0]};
void Display8Dialog(char *TextPo,int (*Ar)[2])
{
//  D8D_Ar[0][0]=Ar[0];   D8D_Ar[0][1]=N1;
//  D8D_Ar[1][0]=Ar[0];   D8D_Ar[1][1]=N2;
//  D8D_Ar[2][0]=Ar[0];   D8D_Ar[2][1]=N3;
//  D8D_Ar[3][0]=Ar[0];   D8D_Ar[3][1]=N4;
//  D8D_Ar[4][0]=Ar[0];   D8D_Ar[4][1]=N5;
//  D8D_Ar[5][0]=Ar[0];   D8D_Ar[5][1]=N6;
//  D8D_Ar[6][0]=Ar[0];   D8D_Ar[6][1]=N7;
//  D8D_Ar[7][0]=Ar[0];   D8D_Ar[7][1]=N8;
  #include "templ.h"
  D8D_Struct[0]=1;
  D8D_Struct[1]=(Dword)&Ar[0][0];
  D8D_Struct[2]=(Dword)&Ar[8][0];
  D8D_Struct[3]=(Dword)&Ar[8][0];
  __asm{
    mov   ecx,TextPo
    lea   edx,D8D_Struct
    push  15000  // 0,15000
    push  -1
    push  -1
    mov   eax,0x4F7D20
    call  eax
  }
  RETURNV
}

_Mine_ *FindMine(int x,int y,int l)
{
  #include "templ.h"
  int   i,cn;
  _Mine_ *cst;

  cst=GetMineBase();
  cn=GetMineNum();
  for(i=0;i<cn;i++,cst++){
    if(cst->xe!=x) continue;
    if(cst->ye!=y) continue;
    if(cst->le!=l) continue;
    RETURN(cst)
  }
  RETURN(0)
}

_Horn_ *FindHorn(int x,int y,int l)
{
  #include "templ.h"
  int   i,cn;
  _Horn_ *cst;

  cst=GetHornBase();
  cn=GetHornNum();
  for(i=0;i<cn;i++,cst++){
    if(cst->ex!=x) continue;
    if(cst->ey!=y) continue;
    if(cst->el!=l) continue;
    RETURN(cst)
  }
  RETURN(0)
}

// ��������� ��������� ������ � eax (2,4,8,0x10)
//:004C1C11 8B0D38956900   mov    ecx,[00699538]
//:004C1C17 50             push   eax
//:004C1C18 E873750000     call   H3.004C9190
int GenArt(int lvl){
  #include "templ.h"
  __asm{
    mov    eax, lvl
    push   eax
    mov    ecx,0x699538
    mov    ecx,[ecx]
    mov    eax,0x4C9190
    call   eax
    mov    IDummy,eax
  }
  RETURN(IDummy)
}

int GetMerchArt(int Numb)
{
  #include "templ.h"
  if(Numb<0 || Numb>6) RETURN(-1)
  int shiftval=0x1F664+Numb*4;
  __asm{
    mov    ecx,BASE
    mov    ecx,[ecx]
    add    ecx,shiftval
    mov    eax,[ecx]
    mov    IDummy,eax
  }
  RETURN(IDummy)
}

void SetMerchArt(int Numb,int Art)
{
  #include "templ.h"
  if(Numb<0 || Numb>6) RETURNV
  int shiftval=0x1F664+Numb*4;
  __asm{
    mov    ecx,BASE
    mov    ecx,[ecx]
    add    ecx,shiftval
    mov    eax,Art
    mov    [ecx],eax
  }
  RETURNV
}

/*
int UpgradeAvail(int Type){
  int Vret=-1;
  if((Type>=0)&&(Type<MONNUM)){
    if(MonsterUpgradeTable[Type]==-2) Vret=0;
    if(MonsterUpgradeTable[Type]>=0)  Vret=1;
  }
  if(Vret==-1){
    asm{
      mov    ecx,Type
      mov    eax,0x47AA50
      call   eax
      mov    Vret,eax
    }
  }
  return Vret;
}

int UpgradeTo(int Type){
  if(UpgradeAvail(Type)==0) return -1;
  int Vret=-1;
  if((Type>=0)&&(Type<MONNUM)){
    if(MonsterUpgradeTable[Type]==-2) return -1;
    else Vret=MonsterUpgradeTable[Type];
  }
  if(Vret==-1){
    asm{
      mov    ecx,Type
      mov    eax,0x47AAD0
      call   eax
      mov    Vret,eax
    }
  }
  return Vret;
}
*/

int WinerIs(void)
{
  #include "templ.h"
  Byte *batman;
  __asm{
    mov   eax,0x699420
    mov   eax,[eax]
    mov   batman,eax
  }
  if(batman==0) RETURN(-1)
  int ret=*(int *)&batman[0x13D48];
  if(ret<0) ret=-1;
  if(ret>1) ret=-1;
  RETURN(ret)
}

int MonIndex(Byte *Mon)
{
  #include "templ.h"
  int j;
  Byte *BatMan;
  __asm{
    mov   eax,0x699420
    mov   eax,[eax]
    mov   BatMan,eax
  }
  for(j=0;j<(21*2);j++){
    // 3.58 Tower skip
//    if(j==20) continue; // 3.58
//    if(j==41) continue; // 3.58
    if(&BatMan[0x54CC+0x548*j]==Mon) break;
  }
  if(j==42) j=0; // not found????
  RETURN(j)
}

Byte *MonPos(int Index)
{
  #include "templ.h"
  if(Index<0 || Index>41) RETURN(0)
  Byte *BatMan;
  __asm{
    mov   eax,0x699420
    mov   eax,[eax]
    mov   BatMan,eax
  }
  RETURN(&BatMan[0x54CC+0x548*Index])
}

Byte *MonPos2(int Side,int SideIndex)
{
  #include "templ.h"
  int index=Side*21+SideIndex;
  RETURN(MonPos(index))
}

void SetMouseCursor(int FType, int SType)
{
  #include "templ.h"
  __asm{
    mov    ecx,0x6992B0
    mov    ecx,[ecx]
    push   SType
    push   FType
    mov    eax,0x50CEA0
    call   eax
  }
  RETURNV
}

void ZHideCursor(void)
{
  #include "templ.h"
  __asm{
    mov  ecx,0x6992B0
    mov  ecx,[ecx]
    mov  eax,0x50D740
    call eax
  }
  RETURNV
}

void ZShowCursor(void)
{
  #include "templ.h"
  __asm{
    mov  ecx,0x6992B0
    mov  ecx,[ecx]
    push 0
    mov  eax,0x50D7B0
    call eax
  }
  RETURNV
}

int GLB_DisableMouse=0;
__declspec( naked ) void DisableMouse(void)
{ // 50CEA5
  __asm{
    mov   eax,GLB_DisableMouse
    or    eax,eax
    je    l_Enabled

    mov    esp,ebp
    pop    ebp
    ret    8
  }
l_Enabled:
  __asm{
    mov   eax,fs:[0]
    ret
  }
}

void DelayIt(int MSec)
{
  #include "templ.h"
  __asm{
    mov    eax,0x4F8970
    call   eax // �������� ����� (���������)
    mov    ecx,eax
    add    ecx,MSec  //00007D0 �������� ����� 2-� ������
    mov    eax,0x4F8980
    call   eax // ��������� �� ����� �������
  }
  RETURNV
}

void SetActiveStack(int Val)
{
  #include "templ.h"
  __asm{
    mov   eax,0x697788
    mov   edx,Val
    mov   [eax],edx
    mov   edi,0x698AC8
    mov   edi,[edi]
    mov   ecx,edi
    mov   eax,0x4E1CC0
    call  eax
    mov   eax,[edi]
    push  0x0000FFFF
    push  0xFFFF0001
    push  1
    mov   ecx,edi
    call  [eax+0x14]
  }
  RETURNV
}

// ���������� ����� �������� ��� ������������� �����������
int BuildTownStruct(_CastleSetup_ *TownPo,int Str2Build)
{
  #include "templ.h"
  int retval=0;
  __asm{
    mov  ecx,TownPo
    mov  eax,Str2Build
    push 1
    push 1
    push eax
    mov  eax,0x5BF1E0
    call eax
    mov  retval,eax
  }
  RETURN(retval)
}
/*
static Dword *CAS_Ar[4];
static Dword PAS_Ar[100];
void ApplyArtSet(Dword *DstAr)
{
  if(DstAr==0) return;
  CAS_Ar[0]=(Dword *)1;
  CAS_Ar[1]=PAS_Ar;
  for(int i=0;i<100;i++){
    if(PAS_Ar[i]==0xFFFFFFFF) break;
  }
  CAS_Ar[2]=&PAS_Ar[i];
  CAS_Ar[3]=CAS_Ar[2];
  __asm{
    lea   eax,CAS_Ar
    mov   ecx,DstAr
    push  eax
    mov   eax,0x4D44B0
    call  eax
  }
}

void Add2ArtSet(int Ind,int Ar,int Subtype)
{
  if(Ind<0 || Ind>=100) return;
  if(Ar==-1) PAS_Ar[Ind]=0xFFFFFFFF;
  else{
    PAS_Ar[Ind]=Ar&0x0000FFFF;
    PAS_Ar[Ind]|=((Subtype&0x0000FFFF)<<16);
  }
}

int GetArtSetNum(Dword *ArtSet)
{
  if(ArtSet==0) return 0;
  return((ArtSet[2]-ArtSet[1])/4);
}

void GetArtInd(Dword *ArtSet,int Ind,int *Art,int *Subtype)
{
  *Art=-1; *Subtype=-1;
  if(ArtSet==0) return;
  if(Ind<0) return;
  if(Ind>=GetArtSetNum(ArtSet)) return;
  Dword *po=(Dword *)ArtSet[1];
  *Art=po[Ind]&0x00000FFFF;
  *Subtype=(po[Ind]&0xFFFF0000)>>16;
}

void SetArtInd(Dword *ArtSet,int Ind,int Art,int Subtype)
{
  if(ArtSet==0) return;
  if(Ind<0) return;
  if(Ind>=GetArtSetNum(ArtSet)) return;
  Dword *po=(Dword *)ArtSet[1];
  po[Ind]=Art&0x00000FFFF|((Subtype&0x0000FFFF)<<16);
}

int CopyArtSet(Dword *ArtSet)
{
  int num=GetArtSetNum(ArtSet);
  int Art,Subtype;
  for(int i=0;i<num;i++){
    GetArtInd(ArtSet,i,&Art,&Subtype);
    Add2ArtSet(i,Art,Subtype);
  }
  Add2ArtSet(num,-1,-1);
  return num;
}
*/

int DoPhysicalDamage(Byte *Mon,int Damage)
{
  #include "templ.h"
  __asm{
    mov   ecx,Mon
    push  Damage
    mov   eax,0x443DB0
    call  eax
    mov   IDummy,eax
  }
  RETURN(IDummy)
}

static _CArtSetup_ BUC_Str;
void CleanUpCombo(int CInd)
{
  #include "templ.h"
  int i;
  for(i=0;i<ARTNUM;i++){
    if(ArtTable[i].PartOfSuperN==CInd) ArtTable[i].PartOfSuperN=-1;
    if(ArtTable[i].SuperN==CInd) ArtTable[i].SuperN=-1;
  }
  CArtSetup[CInd].Index=0;
  RETURNV
}
int BuildUpCombo(int CNum,int CInd,int ArtNums,int *Arts)
{
  #include "templ.h"
  int i;
  // Check
  if(CInd<0 || CInd>=32) RETURN(0)
  if(CNum<0 || CNum>=ARTNUM) RETURN(0)
  if(ArtNums<1 || ArtNums>14) RETURN(0)
  for(i=0;i<ArtNums;i++){
    if(Arts[i]<0 || Arts[i]>=160) RETURN(0)
  }
  // Clean up previous if it is there
  CleanUpCombo(CInd);
  // if SNum==0 just remove previous Combo
  if(CNum==0) RETURN(0)
  // bild up bits for Combo
  __asm{
    mov   eax,Arts
    push  dword ptr [eax+13*4]
    push  dword ptr [eax+12*4]
    push  dword ptr [eax+11*4]
    push  dword ptr [eax+10*4]
    push  dword ptr [eax+ 9*4]
    push  dword ptr [eax+ 8*4]
    push  dword ptr [eax+ 7*4]
    push  dword ptr [eax+ 6*4]
    push  dword ptr [eax+ 5*4]
    push  dword ptr [eax+ 4*4]
    push  dword ptr [eax+ 3*4]
    push  dword ptr [eax+ 2*4]
    push  dword ptr [eax+ 1*4]
    push  dword ptr [eax+ 0*4]
    push  ArtNums
    lea   eax,BUC_Str.ArtNums
    push  eax
    mov   eax,0x44C500
    call  eax
    add   esp,16*4
  }
  BUC_Str.Index=CNum;
  CArtSetup[CInd]=BUC_Str;
  // set up combo nums
  ArtTable[CNum].SuperN=CInd;
  for(i=0;i<ArtNums;i++){
    ArtTable[Arts[i]].PartOfSuperN=CInd;
  }
  RETURN(1);
}

void SummonCreatures3(int MType,int MNum,int Level)
{
  #include "templ.h"
  __asm{
    mov   eax,MType
    mov   ecx,MNum
    push  Level // 0,1=MNum*2, 2=*3, 3=*4
    push  ecx
    push  eax
    push  0x42
    mov   ecx,0x699420
    mov   ecx,[ecx]
    mov   eax,0x5A7390
    call  eax
  }
  RETURNV
}

Word *GetVisabilityPosByXYL(int x,int y,int l)
{
  #include "templ.h"
  __asm{
    mov   eax,l
    push  eax
    mov   edx,y
    mov   ecx,x
    mov   eax,0x4F8070
    call  eax
    mov   DDummy,eax
  }
  RETURN((Word *)DDummy)
}

void MPHoldONTime(void)
{
  __asm{
    mov   ecx,0x69D680
    mov   eax,0x558170
    call  eax
  }
}
void MPContinueTime(void)
{
  __asm{
    mov   ecx,0x69D680
    mov   eax,0x558190
    call  eax
  }
}

void AdjustAllIfPassDwell(int DwNum,int NewOwner)
{
  #include "templ.h"
  __asm{
    mov    ecx,BASE
    mov    ecx,[ecx]
    push   NewOwner
    push   DwNum
    mov    eax,0x4C6470
    call   eax
  }
  RETURNV
}

// 3.59

char MarkedAsChiter(void){
  char *po=(char *)0x69779C;
  return *po;
}

Dword getTime(void){
  #include "templ.h"
  Dword (*p)(void); *(Dword *)&p=0x4F8970;
  RETURN(p());
}
char IsThisGamer2(void *PlStruct){
  #include "templ.h"
  char (__fastcall *p)(void *PlStruct); *(Dword *)&p=0x4BAA40;
  RETURN(p(PlStruct));
}

int ChooseCrToAnimDlg(void){
  #include "templ.h"
  int ind;
  while(1){
    ind=Random(150,MONNUM-1); // show only WoG creatures
//    if(ind==54) continue;
//    if(ind==55) continue;
//    if(ind==122) continue;
//    if(ind==124) continue;
//    if(ind==126) continue;
//    if(ind==128) continue;
//    if(ind==145) continue;
//    if(ind==146) continue;
//    if(ind==147) continue;
//    if(ind==148) continue;
//    if(ind==149) continue;
    if(ind==153) continue;
    break;
  }
  RETURN(ind);
}

__declspec( naked ) void GoExitS(void){
  //_exit();
  __asm lea edx,Exiter+943156
  __asm sub edx,67567
  __asm sub edx,943156-67567
  __asm jmp edx;
}

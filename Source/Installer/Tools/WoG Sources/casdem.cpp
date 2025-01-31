#include <memory.h>
#include "structs.h"
#include "common.h"
#include "txtfile.h"
#include "service.h"
#include "anim.h"
#include "erm.h"
#include "b1.h"
#include "npc.h"
#include "casdem.h"
#define __FILENUM__ 5

//char ttt[]="Title";
//char www[]="Message";
struct _BuildMask_ AllEnBuildings[TOWNNUM];
struct _BuildMask_ BuildDepends[TOWNNUM][44];
struct _BuildMask_ BuildExclusions[TOWNNUM][44];
Byte TownStructOnScreen[TOWNNUM][18];
Byte TownStructOnScreenNum[TOWNNUM];

int b1[200]={100,100,105,105},b2[200]={0,0,0x14,0x18};
static TxtFile TFile;

// Castles
#define CASTLESNUM 100
// 3.59 reduce
//#define CASTLESNUM 48
struct _CastleState_{
  int    State; //0 - Ok, 1,2,3,... -1 - broken
  int    Date;
  int    Cost;
  int    Destroyed; // ����� ��� ��������
  int    DestroyedBy; // ��� ��� ��������
  int    Ghost;
  short  TCenter,TSide; // ����� ������� �����
  short  TLastOwner;
//  Byte   Creat[7][2];
} CastleState[CASTLESNUM];

char *CastleDefs[7][9]={
  {"AVCcasz0.def","AVCramz0.def","AVCtowz0.def","AVCinfz0.def","AVCnecz0.def","AVCdunz0.def","AVCstrz0.def","AVCforz0.def","AVChforz.def"},
  {"AVCcasx0.def","AVCramx0.def","AVCtowx0.def","AVCinfx0.def","AVCnecx0.def","AVCdunx0.def","AVCstrx0.def","AVCforx0.def","AVChforx.def"},
  {"AVCcast0.def","AVCramp0.def","AVCtowr0.def","AVCinft0.def","AVCnecr0.def","AVCdung0.def","AVCstro0.def","AVCftrt0.def","AVChfor0.def"},

  {"AVCcast1.def","AVCramp1.def","AVCtowr1.def","AVCinfr1.def","AVCnecr1.def","AVCdung1.def","AVCstrn1.def","AVCfort1.def","AVCconf1.def"},
  {"AVCcast2.def","AVCramp2.def","AVCtowr2.def","AVCinfr2.def","AVCnecr2.def","AVCdung2.def","AVCstrn2.def","AVCfort2.def","AVCconf2.def"},
  {"AVCcast3.def","AVCramp3.def","AVCtowr3.def","AVCinfr3.def","AVCnecr3.def","AVCdung3.def","AVCstrn3.def","AVCfort3.def","AVCconf3.def"},
  {"AVCcast4.def","AVCramp4.def","AVCtowr4.def","AVCinfr4.def","AVCnecr4.def","AVCdung4.def","AVCstrn4.def","AVCfort4.def","AVCconf4.def"}
};

struct _BattlePlace_{
  int x;
  int y;
  int l;
  int abs; // =0 -�������. ������������ ����� =1 -����������
} BattlePlace_back[14],BattlePlace[14]={
  {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},
  {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}
};

int MonInTownsBack[9*7*2], MonInTownsBack_Saved=0;

int DemPerDay_back,DemPerDay=3; // ������� � ����
int DemNextCost_back[100],DemNextCost[100]={0,500,1000,0}; // ���� ����������
int Mov2Lost_back,Mov2Lost=0x100; // ������ ����� ��� �����
//int Army2Dem_back[48][100][2],Army2Dem[48][100][2]; // ���. ����� ��� ���������� ��������
int GrailDemontage;

int CSMTran[4][9]={
  {3,2,2,1,1,1,1,1,1},
  {3+7,2+7,2+7,1+7,1+7,1+7,1+7,1+7,1+7},
  {0,5,0,3,0,0,0,0,0},
  {0,5+7,0,3+7,0,0,0,0,0}
};
Dword CommonBuildingsMask[2][2]={{0xC403FBFF,0x00000FFF},  // AND ����� ��� ����
                                 {0x03EC0040,0x00000000}}; // OR
Dword UniqBuildingsMask[9][2]={{0xC46FFBEF,0x00000FFF},
                               {0xC76FFBBF,0x00000FFF},
                               {0xC4EFFBBF,0x00000FFF},
                               {0xC7EDFBBF,0x00000FFF},
                               {0xC46FFBFF,0x00000FFF},
                               {0xC4EFFBBF,0x00000FFF},
                               {0xC4EFFBA7,0x00000FFF},
                               {0xC46FFBE7,0x00000FFF},
                               {0xC42FFBFF,0x00000FFF}};
struct _CSCheck_{
  Byte Mon;         // ��� �������� ��� �����
  Byte Bits2Build;  // ����� ���������� ����� ������� ���� ������ ...
  Byte Byte2Build;  // ... � ���� �����
  struct {
    Byte  Depend[6];
    int   Cost2Break;
    int   MinHeroExp;
    int   MinArmyPow;
    short Bonus[6];
  } Town[9];  
} CSCheck_back[44],CSCheck[44]={
//  0x00,0x00,0xC0,0x03,0x7E,0x0F // All creature 
//  0x00,0x00,0x00,0xC0,0xFF,0x0F // All creature (old)
//  0x80,0x03,0x00,0xC0,0xFF,0x0F // + Forts
//  0x9F,0x03,0x00,0xC0,0xFF,0x0F // + Mag
//  0x9F,0x03,0x00,0xC4,0xFF,0x0F // + Gral
//  0x9F,0x3F,0x00,0xC4,0xFF,0x0F // + All
  {0},{0,0x01,0},{0,0x02,0},{0,0x04,0},{0,0x08,0}, // 4 ( 5)
  {0},{0},{0}, // 7 ( 8)
  {0,0x80,0},{0,0x01,1}, // 9 (..)
  {0}, //10 (11)
  {0,0x04,1},{0,0x08,1},{0,0x10,1}, //13 ()
  {0},{0},{0},{0}, //17 (30)
  {100},{101}, //19 (30)
  {0},{0},{0},{0}, //23 (30)
  {102},{103}, //25 (30)
  {0}, //26 ( 0)
  {0},{0},{0}, //29 (30)
  {1},{2},{3},{4},{5},{6},{7},      //36 (43)
  {8},{9},{10},{11},{12},{13},{14}  //43 (-)
};
struct _CSCheckERM_{
  Byte Bits2Build;  // ����� ���������� ����� ������� ���� ������ ...
  Byte Byte2Build;  // ... � ���� �����
} CSCheckERM[44]={
//  0x00,0x00,0xC0,0x03,0x7E,0x0F // All creature 
//  0x00,0x00,0x00,0xC0,0xFF,0x0F // All creature (old)
//  0x80,0x03,0x00,0xC0,0xFF,0x0F // + Forts
//  0x9F,0x03,0x00,0xC0,0xFF,0x0F // + Mag
//  0x9F,0x03,0x00,0xC4,0xFF,0x0F // + Gral
//  0x9F,0x3F,0x00,0xC4,0xFF,0x0F // + All
  {0},{0x01,0},{0x02,0},{0x04,0},{0x08,0}, // 4 ( 5)
  {0},{0},{0}, // 7 ( 8)
  {0x80,0},{0x01,1}, // 9 (..)
  {0}, //10 (11)
  {0x04,1},{0x08,1},{0x10,1}, //13 ()
  {0},{0},{0},{0}, //17 (30)
  {0},{0}, //19 (30)
  {0},{0},{0},{0}, //23 (30)
  {0},{0}, //25 (30)
  {0}, //26 ( 0)
  {0},{0},{0}, //29 (30)
  {0},{0},{0},{0},{0},{0},{0},      //36 (43)
  {0x40,3},{0x80,3},{0x01,4},{0x02,4},{0x04,4},{0x08,4},{0x10,4}  //43 (-)
};
int CSCostNext=0;
//int CSValues[48][4][2];
//int CS2Crash[48];
int CSMonst[7*2]; // ��������� ����� ������� 7 �������

// ������ �������� 8-�� ������
#define DWELLMAPNUM 1000
static struct _DwellMapInfo_{
  char  Owner; // 0...8 - ������, -1=�� ���, 
  short x,y;
  char  l;
  Byte  SType;  // ������, 0 - �� �����
  short GotDay; // ����, ����� ��� �������� ���� ��������
  Word  Mon2Town; // ��������������� � ������ ������ ������, ������������ ��� �����
} DwellMapInfo[DWELLMAPNUM];

Dword CSval;
Dword CCval;
static char  CSBuffer[2048];

void PrepareCastle(_CastleSetup_ *CStructure)
{
#include "templ.h"
//  STARTN(__FILENUM__*1000000+__LINE__) //  START("PrepareCastle")
  int CType=CStructure->Type;
  Dword Mask;
  for(int i=0;i<2;i++){
    Mask=CStructure->BMask[i];
    Mask&=CommonBuildingsMask[0][i];
    Mask|=CommonBuildingsMask[1][i];
    Mask&=UniqBuildingsMask[CType][i];
    CStructure->BMask[i]=Mask;
  }  
  RETURNV
}

int GetCastleNumber(_CastleSetup_ *CStructure)
{
#include "templ.h"
//  STARTN(__FILENUM__*1000000+__LINE__) //  START("GetCastleNumber")
  int Cnum;
  Cnum=CStructure->Number;
  if(Cnum>(CASTLESNUM-1)){
    Message(ITxt(29,0,&Strings),1);
    RETURN(-1)
  } 
  RETURN(Cnum)
}  

_CastleSetup_ *FindCastleStr(_MapItem_ *Mi)
{
  #include "templ.h"
  int        x,y,l,size,n;
  _CastleSetup_ *cst;
  _MapItem_ *Mi0;

  Mi0=GetMapItem0();
  size=GetMapSize();
  n=Mi-Mi0;
  l=n/(size*size);
  n=n%(size*size);
  y=n/size;
  x=n%size;
  cst=FindCastle(x,y,l);
  RETURN(cst)
}

void static MakeCheck(int item,int town,char *depend)
{
  #include "templ.h"
  int  i,j,k;
  Byte b;
  
  if((item<0)||(item>43)){ Message("CD: Item to check is out of range.",1); }
  for(j=0;j<6;j++) CSCheck[item].Town[town].Depend[j]=0;
  for(i=0;i<44;i++){
    j=i/8; // ������
    k=i%8; // ����� ����
    b=(Byte)((depend[i]-'0')<<k);
    CSCheck[item].Town[town].Depend[j]|=b;
  }  
  RETURNV
}

void CastleCheck(int flag)
{
  #include "templ.h"
  switch(flag){
    case  1: CCval=(Dword)CastleDefs[3]; break;
    case  2: CCval=(Dword)CastleDefs[4]; break;
    case  3: CCval=(Dword)CastleDefs[5]; break;

    case -1: CCval=(Dword)CastleDefs[6]; break;
  }
  if(flag!=0){
    __asm mov eax,CCval
    __asm mov ecx,0x4C97C1+3
    __asm mov [ecx],eax
    __asm mov ax,0x9090
    __asm mov ecx,0x4C97B5
    __asm mov word ptr [ecx],ax
  }else{
    __asm mov eax,0x677A54
    __asm mov ecx,0x4C97C1+3
    __asm mov [ecx],eax
    __asm mov ax,0x1374
    __asm mov ecx,0x4C97B5
    __asm mov word ptr [ecx],ax
  }
  RETURNV
}

void __stdcall CastleServiceRedraw(Dword,Dword)
{
  Byte *Castle;
  int tn;
  _CastleState_ *csp;

  __asm pusha
  #include "templ.h"
//  Castle=(Byte *)_ECX;
  _ECX(Castle)
  tn=Castle[0];
  csp=&CastleState[tn];
  CastleCheck(csp->State);
  STOP
  OriginalCallPointer=Callers[9].forig;
  __asm popa
  __asm push   0
  __asm push   0x0D
  __asm call dword ptr [OriginalCallPointer]
}

void CastleSkipDemolition(void)
{
  #include "templ.h"
  int    Cnum;
  Dword  Pointer;
  _CastleSetup_ *CStructure;
  _CastleState_ *csp;
  
  _EDX(Pointer)
  if(WoG==0) RETURNV
  __asm{
    mov   ebx,Pointer
    mov   ecx,[ebx+0x38]
    mov   CStructure,ecx
  }
  if((Cnum=GetCastleNumber(CStructure))<0) RETURNV
  
  csp=&CastleState[Cnum];
  csp->State=0; // ������� ����������
  csp->Ghost=0; // ������� ����������
  RETURNV
}

void SetBonRes(short *Bonus)
{
  #include "templ.h"
  int i,n,r,v,f;
  r=-1; v=0;
  for(i=n=f=0;i<6;i++){
    if(Bonus[i]!=0){
      ++n;
      if(n==2){
        if(f){ // �� ������ ���
          Request2Pic(ITxt(15,0,&Strings),r,v,i,Bonus[i],1);
          AddRes(-1,r,v); AddRes(-1,i,Bonus[i]);
        }else{
          Request2Pic(ITxt(12,0,&Strings),r,v,i,Bonus[i],1);
          AddRes(-1,r,v); AddRes(-1,i,Bonus[i]);
          f=1;
        }
        r=-1;
      }else{
        r=i; v=Bonus[i];
      }  
    }
  }
  if(r!=-1){
    if(f){ // �� ������ ���
      Request2Pic(ITxt(15,0,&Strings),r,v,-1,0,1);
      AddRes(-1,r,v);
    }else{
      Request2Pic(ITxt(12,0,&Strings),r,v,-1,0,1);
      AddRes(-1,r,v);
    }
  }
  RETURNV
}

void CastleCheckDemolition(void)
{
  int    i,j,t,flag,Btype,Date,Rebuild,CType,CNewType,Mn,MCt,Mt,VHero,LCost,LCost2;
  int    Cnum,tval,GrailDemFlag;
  Dword  ZPointer,PosMixed,Mask,Dummy;
  _CastleSetup_ *CStructure;
  Byte  *Building,*Bonus;
  Word  *Monst,*Mnp;
  Byte   Zb;
  _CastleState_ *csp;
  _Hero_ *Hp0,*Hp;
  char  *tstr,ch;
  _MapItem_  *MIp;
  int    ex,ey,el;
  
  _EAX(flag);
  _EBX(ZPointer);
  _EDI(Btype);
  #include "templ.h"
  CSval=0;
  if(WoG==0) RETURNV
  if(PL_NoTownDem) RETURNV
  if(IsThis(CurrentUser())==0){  // �� ��� �����
    RETURNV
  }
  // 3.58f fix - disable demolition in allied town
  __asm{
    mov   ebx,ZPointer
    mov   ecx,[ebx+0x38]
    mov   CStructure,ecx
  }
  if(CStructure->Owner!=CurrentUser()) RETURNV // not our town
  if((Btype<0)||(Btype>48)) RETURNV
  __asm{
    mov   edx,Btype
    mov   ebx,ZPointer
    mov   ecx,[ebx+0x38]
//    mov   CStructure,ecx
    push  1
    push  1
    mov   eax,0x5D2E40
    call  eax
  }
  _EAX(tstr);
  if((Cnum=GetCastleNumber(CStructure))<0) RETURNV

  Rebuild=0;
  csp=&CastleState[Cnum];
  Date=GetCurDate();
  CType=CStructure->Type;
  CNewType=CType;
  VHero=CStructure->VHero;
  Building=CStructure->Built;
  Bonus=CStructure->Bonus;
  Mn=csp->Ghost;
  __asm{ 
    mov  eax,BASE
    mov  eax,[eax]
    add  eax,0x21620
    mov  Hp0,eax
  }
  if(VHero==-1) Hp=0;
  else Hp=&Hp0[VHero];
  if(flag!=1){ // ����� ����
    if(Btype!=16) RETURNV // �� �������
    if(csp->State!=-1) RETURNV // �� ���������
    if(VHero==-1) RETURNV // ����� � ������ ���
    if(Mn!=0){ // ����. ����
      if((Date-csp->Destroyed)>=GHOSTDAYS){ // � ����� ������
        __asm{
          lea    eax,Mn // -> ����� �������� (dw)
          mov    ebx,Hp // -> �����
          add    ebx,0x91 // -> ����� ��� ����� � ����� (ebx->�����)
          mov    edi,GHOSTTYPE
          lea    ecx,CSBuffer // -> ����� �� ~20h ����
// ��������� ������ ��� �����
          push   0
          push   -1
// ������ ������ ��� �����
          push   0
          push   -1
// ������ ������ ��� �����
          push   0
          push   -1
// ������ ������ ��� �����
          push   eax // -> ����������
          push   edi // = ��� ��������
          push   0
          push   ebx
          mov    eax,0x0551750
          call   eax
          lea    ecx,CSBuffer // -> ����� �� ~20h ����
          push   ecx
          mov    ecx,0x699550 //???
          mov    ecx,[ecx]
          mov    eax,0x04B0770
          call   eax
        }
        CastleCheck(-1); // ������� ������� ���
        if(Mn!=csp->Ghost){ // ���� ������������ �����
          for(i=0;i<6;i++){
            Building[i]=0;
            Bonus[i]=0;
          }
          __asm{
            mov    ecx,ZPointer
            push   16 //Btype
            mov    eax,0x5D6E80
            call   eax
          }  
        }
        csp->Ghost=Mn;
      }else{ // ��� ������ �������
        Message(ITxt(4,0,&Strings),1);
      }  
    }else{ // ����. ���
      Message(ITxt(7,0,&Strings),1);
    }
    CSval=0x5D4617;
    RETURNV
  }

  if((Btype==16)&&((Building[1]&0x3C)==0)){
// ��������� �������, ������ ��� ��� - ��� ��� � ������������
    if(csp->Ghost){ // ���� ����������
      if((Date-csp->Destroyed)>=GHOSTDAYS){ // 6 ���� ������ - ����� ��������
        RequestPic(ITxt(3,0,&Strings),0x15,GHOSTTYPE,1);
        CSval=0x5D4617;
        RETURNV
      }else{ // ��� �� �����
        Message(ITxt(4,0,&Strings),1);
        CSval=0x5D4617;
        RETURNV
      }
    }else{ // ��� - ����� ���������������
      if(RequestPic(ITxt(5,0,&Strings),CType+0x16,10,2)==0){
        CSval=0x5D4617;
        RETURNV
      }
      if(Hp!=0){
        // � ������ ���� ����� - ����� ������� ���.
        // �������� �� ���������
        CNewType=CType;
        if((HSpecTable[Hp->Number].Spec==HSUPERSPEC)&&(HSpecTable[Hp->Number].Spec1==HSPEC_ANYTOWN)){
          CNewType=ChooseCastle();
        }else{
          i=Hp->Spec/2;
          if(CType!=i){ // ���� ���� ������� �����������
            if(Request2Pic(ITxt(14,0,&Strings),CType+0x16,10,0x16+i,10,7)==0){
               // ������ ���
               CNewType=i;
            }
          }
        }
        if(CNewType!=CType){
          for(i=0;i<2;i++){
//            Mask=*((Dword *)&CStructure[0x160+i*4]);
            Mask=CStructure->BMask[i];
            Mask&=CommonBuildingsMask[0][i];
            Mask|=CommonBuildingsMask[1][i];
            Mask&=UniqBuildingsMask[CNewType][i];
//            *((Dword *)&CStructure[0x160+i*4])=Mask;
            CStructure->BMask[i]=Mask;
          }
        }
      }
      Rebuild=1;
      CastleCheck(0); // ������� ���������� ���
    }
  }
  // ��������� ����������� ���������� ������� �������� (�� ��������� ��������)
  if(Rebuild==0){
    for(i=0;i<6;i++){
      if(CSCheck[Btype].Town[CType].Depend[i]&Building[i]){
        RETURNV
      }
    }

// ...

    for(i=0;i<512;i++){
      ch=tstr[i];
      if(ch==0) break;
      CSBuffer[i]=ch;
    }
    for(j=0;i<1024;i++,j++){
      ch=ITxt(1,0,&Strings)[j];
      if(ch==0) break;
      CSBuffer[i]=ch;
    }
    for(j=0;i<1024;i++,j++){
      ch=ITxt(2,0,&Strings)[j];
      if(ch==0) break;
      CSBuffer[i]=ch;
    }
  }else{
    for(i=0;i<512;i++){
      ch=ITxt(6,0,&Strings)[i];
      if(ch==0) break;
      CSBuffer[i]=ch;
    }
  }
  CSBuffer[i]=0;
  if(RequestPic(CSBuffer,CStructure->Type+0x16,Btype,2)==0){
/*
    // ����� ��� �������� ��� ���� �� ������ ������
    if(CSCheck[Btype][0]==0) CSval=0x5D4617;
    // ����� � ����� �� ������ ������
    RETURNV
*/
    // ���� ������� ����� ���� �� ������ ������ ��� ����
    CSval=0x5D4617;
    RETURNV
  }

  if(csp->Date!=Date){ csp->Cost=0; }
  if(Hp==0){
    Message(ITxt(17,0,&Strings),1);
    CSval=0x5D4617;
    RETURNV
  }
  if(csp->Cost>=DemPerDay){ // ������� ����� ��� ��������� � ���� ����
    Message(ITxt(16,0,&Strings),1);
    CSval=0x5D4617;
    RETURNV
  }
// �������� ����� �����
  if(Hp->Exp<(Dword)CSCheck[Btype].Town[CType].MinHeroExp){
    Message(ITxt(30,0,&Strings),1);
    CSval=0x5D4617;
    RETURNV
  }
// �������� �������� �����
  tval=0;
  for(j=0;j<7;j++){
    if(Hp->Ct[j]==-1) continue;
    if(Hp->Cn[j]==-1) continue;
    tval+=(MonTable[Hp->Ct[j]].HitPoints*Hp->Cn[j]);
  }
  if(tval<CSCheck[Btype].Town[CType].MinArmyPow){
    Message(ITxt(19,0,&Strings),1);
    CSval=0x5D4617;
    RETURNV
  }
// ��������� �� ������
  GrailDemFlag=0;
  if(Btype==26){
    if(Request2Pic(ITxt(31,0,&Strings),6,GrailDemontage,8,2,2)){
      // ����� �������������
      LCost2=DemNextCost[csp->Cost]+GrailDemontage;
      for(i=0;i<64;i++){
        if(Hp->OArt[i][0]==0xFFFFFFFF){
          GrailDemFlag=1;
          break;
        }
      }
      if(GrailDemFlag==0){
        Message(ITxt(32,0,&Strings),1);
        CSval=0x5D4617;
        RETURNV
      }
      if(CheckRes(-1,6,-LCost2)){
        // �� ������� ��������
        RequestPic(ITxt(10,0,&Strings),6,LCost2,1); // �� �������
        CSval=0x5D4617;
        RETURNV
      }else{
        if(RequestPic(ITxt(9,0,&Strings),6,LCost2,2)==0){
          // �� ����� - �� ����
          CSval=0x5D4617;
          RETURNV
        }
        AddRes(-1,6,-LCost2);
        LCost2=0;
        for(i=0;i<64;i++){
          if(Hp->OArt[i][0]==0xFFFFFFFF){
            Hp->OArt[i][0]=2; Hp->OArt[i][1]=-1;
            Hp->OANum=(Byte)(Hp->OANum+1);
//            GrailDemFlag=1;
            break;
          }
        }
      }
    }else{ // ������� �� �����
      LCost2=DemNextCost[csp->Cost]+CSCheck[Btype].Town[CType].Cost2Break;
      GrailDemFlag=0;
    }
  }else{
    LCost2=DemNextCost[csp->Cost]+CSCheck[Btype].Town[CType].Cost2Break;
  }
//  Monst=((Word *)&CStructure[0x16]);
  Monst=(Word *)CStructure->Monsters;
  i=CSCheck[Btype].Mon;
//  d=(Btype-0x1E); // ��� �������� ��� ��������� ���� �������
  if(i>=100){ // ��� ������� ������� �� ���� ������
    i-=100;
    i=CSMTran[i][CType];
  }
  if(i!=0){ // ����� ���� ������� - ������ �����
    MCt=i-1;
    Mnp=&Monst[MCt];
    Mn=Monst[MCt];
    // ������� ��� �������
    i=(MCt+CType*14)*4;
    __asm{
      mov   eax,i
      add   eax,0x6747B4
      mov   eax,[eax]
    }
    _EAX(Mt);
    if(Mn!=0){
      LCost=Mn*CSMonst[MCt];
      if(CheckRes(-1,6,-LCost)){
        // �� ������� ��������
        Request2Pic(ITxt(10,0,&Strings),6,LCost,0x15,Mt+(Mn<<16),1); // �� �������
      }else{
        if(Request2Pic(ITxt(8,0,&Strings),6,LCost,0x15,Mt+(Mn<<16),(int)2)==0){
          // ������� �� �����
        }else{
          // ����� �������� ������ � �����
          AddRes(-1,6,-LCost);
          Mn=*Mnp=0; // ������� ��������
        }
      }
      if((Hp!=0)&&(Mn!=0)){
        // ���� ���� ����� � �����
        if(RequestPic(ITxt(11,0,&Strings),0x15,Mt+(Mn<<16),2)==1){
          // ����� ������ ���� �����
          if(Hp->Movement<Mov2Lost){ // ���� ��������� �������� � �����
            Message(ITxt(18,0,&Strings),1);
            CSval=0x5D4617;
            RETURNV
          }
          Hp->Movement-=Mov2Lost; if(Hp->Movement<0) Hp->Movement=0;
          // ��������� ���������� �������� �� �����
          if(BattlePlace[MCt].abs){ // ���������� ����������
            PosMixed=((Dword)BattlePlace[MCt].y<<16)+(Dword)BattlePlace[MCt].x;
            if(BattlePlace[MCt].l) PosMixed+=0x04000000;
          }else{ // ������������ �����
            PosMixed=((CStructure->y+(Dword)BattlePlace[MCt].y)<<16)+CStructure->x+(Dword)BattlePlace[MCt].x;
            if(CStructure->l+BattlePlace[MCt].l) PosMixed+=0x04000000;
          }
          if(QuickBattle()){
            __asm{
             mov    ebx,0x5C7603
             mov    eax,0x90909090
             mov    [ebx],eax
             mov    [ebx+4],eax
             mov    [ebx+8],ax
             mov    [ebx+10],al
            }
          }
          __asm{
           mov    ebx,0x4AE5DB
           mov    eax,0x90909090
           mov    [ebx],eax
           mov    [ebx+4],eax
           mov    [ebx+8],al
           mov    [ebx+9],eax
           mov    ebx,0x4AC5FD
           mov    [ebx],eax
           mov    [ebx+4],eax
           mov    [ebx+8],ax
           mov    [ebx+10],al
           mov    [ebx+11],eax
           mov    ebx,0x4AE3A4
           mov    ax,0x4CEB
           mov    [ebx],ax
            lea    eax,Mn // -> ����� �������� (dw)
            mov    ebx,Hp // -> �����
            mov    edi,Mt
            mov    edx,PosMixed // ������� �����
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
//            mov    ecx,0x1A00020
            mov    ecx,0x6992B8 // [BASE]+ 109700h
            mov    ecx,[ecx]
            mov    eax,0x04AC270
            call   eax
            mov    ecx,eax
           mov    ebx,0x4AE5DB
           mov    eax,0x006A016A
           mov    [ebx],eax
           mov    eax,0xCE8B006A
           mov    [ebx+4],eax
           mov    al,0xE8
           mov    [ebx+8],al
           mov    eax,0xFFF68F58
           mov    [ebx+9],eax
           mov    ebx,0x4AC5FD
           mov    eax,0x006A016A
           mov    [ebx],eax
           mov    eax,0x0189006A
           mov    [ebx+4],eax
           mov    ax,0xCB8B
           mov    [ebx+8],ax
           mov    al,0xE8
           mov    [ebx+10],al
           mov    eax,0xFFF6AF34
           mov    [ebx+11],eax
           mov    ebx,0x4AE3A4
           mov    ax,0x758B
           mov    [ebx],ax
          }
          if(QuickBattle()){
            __asm{
             mov    ebx,0x5C7603
             mov    eax,0x046A016A
             mov    [ebx],eax
             mov    eax,0x02E8016A
             mov    [ebx+4],eax
             mov    ax,0x03BC
             mov    [ebx+8],ax
             xor    al,al
             mov    [ebx+10],al
            }
          }
          _ECX(Dummy);
          if(Dummy==0) Mn=*Mnp=0;
          else{
            Message(ITxt(13,0,&Strings),1);
          }
        }
      }
    }
  }
  if(Mn!=0){
    CSval=0x5D4617;
    RETURNV
  }
  if(LCost2!=0){
    // ���� ��������� �� ��������� ����������
    if(CheckRes(-1,6,-LCost2)){
      // �� ������� ��������
      RequestPic(ITxt(10,0,&Strings),6,LCost2,1); // �� �������
      CSval=0x5D4617;
      RETURNV
    }else{
      if(RequestPic(ITxt(9,0,&Strings),6,LCost2,2)==0){
        // �� ����� - �� ����
        CSval=0x5D4617;
        RETURNV
      }
      AddRes(-1,6,-LCost2);
    }
  }

// ...
  i=Btype/8; j=Btype%8;
  Zb=(Byte)(1<<j);
  Building[i]&=(Byte)~Zb;
  Bonus[i]&=(Byte)~Zb;
  Zb=CSCheck[Btype].Bits2Build;
  i=CSCheck[Btype].Byte2Build;
  if(Zb!=0){
    Building[i]|=(Byte)Zb;
    Bonus[i]|=(Byte)Zb;
//    Building[i]&=(Byte)~b;
//    Bonus[i]&=(Byte)~b;
  }
  if(Btype<5){ // ��������� ���������� �������
    CStructure->MagLevel=(Byte)Btype; // �������� ������� �������
    for(i=Btype;i<5;i++)
      CStructure->MagicHild[i]=0; // �������� ����� ���, ��� ����
  }

  Zb=(Byte)(Building[1]&0x3C);
  Building[1]&=(Byte)~0x3C;
  Bonus[1]&=(Byte)~0x3C;
  if(Zb&0x04) Zb=10;
  else if(Zb&0x08) Zb=11;
  else if(Zb&0x10) Zb=12;
  else if(Zb&0x20) Zb=13;
  else Zb=0;

  if(Rebuild==0){
    if(Zb==0){ // ��� ���������
      t=-1;
      csp->Destroyed=Date;
      csp->Ghost=GHOSTNUM;
      csp->DestroyedBy=CurrentUser();
    }else t=csp->State;
    switch(t){
      case  0: t= 1; break;
      case  1: t= 2; break;
      case -1: t=-1; break;
      case  2:
      default: t= 3; break;
    }
    CastleCheck(t);
    csp->State=t;
    csp->Date=Date;
    csp->Cost+=1; // ���� ���������� ����� ������
  }else{ // ���������������
    csp->Ghost=0;
    csp->State=0;
    Zb=10; // �������� ������
    for(i=0;i<6;i++){
      Building[i]=0;
      Bonus[i]=0;
    }
    CStructure->Type=(Byte)CNewType;
    ex=CStructure->x; ey=CStructure->y; el=CStructure->l;
    MIp=GetMapItem(ex,ey,el);
    MIp->OSType=(Word)CNewType;
  }
  if(Zb==0){
    Zb=16; // ���. ������ �������.
    for(i=0;i<6;i++){
      Building[i]=0;
      Bonus[i]=0;
    }
  }
//  _EAX=b;
  __asm{
    xor    eax,eax
    mov    al,Zb
    mov    ecx,ZPointer
    push   eax//Btype
    mov    eax,0x5D6E80
    call   eax
  }
  CastleCheck(0);
  // ���� �� �����?
  if(GrailDemFlag==0){ // ������ ������������
    SetBonRes(CSCheck[Btype].Town[CType].Bonus);
  }
  CSval=0x5D4617;
  RETURNV
}

void CastleExit(Dword/* Manager*/)
{
  #include "templ.h"
  _CastleState_ *csp;
  _MapItem_  *MIp0,*MIp;
  int    Cnum,MapSize,ex,ey,el,Date;
  _CastleSetup_ *Castle, *End;
  int   i,Num,ShowMess,cu,DisableEnter;
//  int   hn;
//  _Hero_ *chp;
  
  ShowMess=1;
  cu=CurrentUser();
  __asm{
    mov   ecx,BASE
    mov   ecx,[ecx]
    mov   eax,[ecx+0x021614]
    mov   Castle,eax
    mov   eax,[ecx+0x021618]
    mov   End,eax
    mov   eax,[ecx+0x1FC40]
    mov   MIp0,eax
    mov   eax,[ecx+0x1FC44]
    mov   MapSize,eax
  }
  Num=End-Castle;
  for(i=0;i<Num;i++,Castle++){
    DisableEnter=0;
    ex=Castle->x; ey=Castle->y; el=Castle->l;
    if((Cnum=GetCastleNumber(Castle))<0) RETURNV
    csp=&CastleState[Cnum];
    Date=GetCurDate();
//    if(csp->DestroyedBy!=cu) continue;
    if(Castle->Owner!=cu) continue;
    if(csp->State==-1){
      // � ������� ����� � ������
      if((Date-csp->Destroyed)>=GHOSTDAYS){
        if(ShowMess){
          Message(ITxt(23,0,&Strings),1);
          ShowMess=0;
        } 
      }else{
        DisableEnter=1;
        if(ShowMess){
          Message(ITxt(22,0,&Strings),1);
          ShowMess=0;
        } 
      }
/*
      // �������� �� ����� �� ����� �� ����� ������.
      hn=*(int *)&Castle[0x10];
      if(hn!=-1){ // ���� ����� �������
        chp=GetHeroStr(hn);
        // ���������� ��� ���������
        if(ey<MapSize-1){ // ���� ���� ������
          // ���� ��������� ������ �����
          MIp=&MIp0[ex+((ey+1)+el*MapSize)*MapSize]; // �����
          if(EmptyPlace(MIp)){ // �� ������
            // ������
            chp->y++; *(int *)&Castle[0x10]=-1;
            goto _ok;
          }
          if(ex>0){
            MIp=&MIp0[(ex-1)+((ey+1)+el*MapSize)*MapSize]; // ����� � �����
            if(EmptyPlace(MIp)){ // �� ������
              // ������
              chp->y++; chp->x--; *(int *)&Castle[0x10]=-1;
              goto _ok;
            }
          }
          if(ex<MapSize-1){
            MIp=&MIp0[(ex+1)+((ey+1)+el*MapSize)*MapSize]; // ����� � ������
            if(EmptyPlace(MIp)){ // �� ������
              // ������
              chp->y++; chp->x++; *(int *)&Castle[0x10]=-1;
              goto _ok;
            }
          }
        }
        KillHero(hn);
        // �� ����� - ��������� ��� �������� ������
        j=*(int *)&Castle[0x0C];
        if(j!=-1){ // ���� ����� ������
//          Town2Hero(Manager); 
//          KillHero(j);
          // ������� �����
          KillHero(hn);
//          *(int *)&Castle[0x10]=-1;
        }else{
          // ���������� ������
// ���� ���������, �.�. ����� ����� ��������������� �����
          Hero2Town(Manager); 
//            *(int *)&Castle[0x0C]=hn;
//            *(int *)&Castle[0x10]=-1;
//            chp->Visible=0;
        }
      }
*/
//_ok:
      // ��������, ���� ���-��
      if(Castle->Owner!=-1){
        __asm{
          mov   eax,0x5BE6D0
          mov   ecx,Castle
          call  eax
        }
      }  
      if(DisableEnter){
        // �������� �������� �� ������
        MIp=&MIp0[ex+(ey+el*MapSize)*MapSize];
        MIp->Attrib|=0x01;
      }  
    }
  }
  RETURNV
}

__declspec( naked ) void CastleService(void)
{
  __asm pusha
//  asm mov CSval,ebx
//  asm mov CSbuild,edi
  __asm mov eax,[ebp+8]
  CastleCheckDemolition();
  __asm mov ecx,0x6AAA50
  __asm mov dword ptr [ecx],-1
  __asm mov eax,CSval
  __asm or  eax,eax
  __asm je  l_cont
  __asm popa
  __asm pop eax
  __asm jmp dword ptr [CSval]
l_cont:
  __asm popa
  __asm ret
}

void CastleService2(void)
{
  __asm pusha
//  edx - ��������� �� �������� (+38 -> �����)
//  ecx - ����������� ������
  CastleSkipDemolition();
  __asm popa
  __asm mov [edx+0x1B8],ecx
}

int ERM_CasDem(char Cmd,int Num,_ToDo_*,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i]) //  STARTC("Process !!CD",&Mp->m.s[Mp->i])
  int k;
  
  if(WoG==0) RETURN(0) // ������ ��������� ����� �� � WoG
  switch(Cmd){
    case 'P': // ������� �������� ����� �������� � ���������
      if(Num<5) RETURN(0) // #M/$x/$y/$l/#R
      k=Mp->n[0];  // ����� �������
      if((k<0)||(k>13)) RETURN(0)
      BattlePlace[k].x=BattlePlace[k].x*Mp->f[1]+Mp->n[1]; // x
      BattlePlace[k].y=BattlePlace[k].y*Mp->f[2]+Mp->n[2]; // y
      BattlePlace[k].l=BattlePlace[k].l*Mp->f[3]+Mp->n[3]; // l
      BattlePlace[k].abs=BattlePlace[k].abs*Mp->f[4]+Mp->n[4]; // r
      break;
    case 'D': // D$ ���-�� ����. � ����
      DemPerDay=DemPerDay*Mp->f[0]+Mp->n[0]; // ������� � ����
      if(DemPerDay<0) DemPerDay=0;
      break;
    case 'M': // M$ ������ �������� �����  
      Mov2Lost=Mov2Lost*Mp->f[0]+Mp->n[0]; // ������� � ����
      if(Mov2Lost<0) Mov2Lost=0;
      break;
    case 'N': // N#1/$2 ���� ���� ����������  
      if(Num<2) RETURN(0)
      k=Mp->n[0];
      if((k<0)||(k>99)) RETURN(0)
      DemNextCost[k]=DemNextCost[k]*Mp->f[1]+Mp->n[1]; // ���� ����������
      if(DemNextCost[k]<0) DemNextCost[k]=0;
      break;
    case 'E': // Etown_type/build_type/exp_val ���� ����� ��� ����������
      if(Num<3){ Error(); RETURN(0) }
      if((Mp->n[0]<0)||(Mp->n[0]>8)){ Error(); RETURN(0) }
      if((Mp->n[1]<0)||(Mp->n[1]>43)){ Error(); RETURN(0) }
      Apply(&CSCheck[Mp->n[1]].Town[Mp->n[0]].MinHeroExp,4,Mp,2);
      break;
    case 'A': // Atown_type/build_type/army_hp ���� ����� ����� ��� ����������
      if(Num<3){ Error(); RETURN(0) }
      if((Mp->n[0]<0)||(Mp->n[0]>8)){ Error(); RETURN(0) }
      if((Mp->n[1]<0)||(Mp->n[1]>43)){ Error(); RETURN(0) }
      Apply(&CSCheck[Mp->n[1]].Town[Mp->n[0]].MinArmyPow,4,Mp,2);
      break;
    // 3.59
    case 'B':{
      // B0/town/struct/ENdis - global enanle/disable structure
      // B1/town/struct/$/$ - build dependence
      // B2/town/struct/#/#/#... - build dependence
      // B3/town/struct/$/$ - exclusion dependence
      // B4/town/struct/#/#/#... - exclusion dependence
      if(Num<4){ MError("\"!!CD:B\"-wrong syntax"); RETURN(0) }
      int cs; if(Apply(&cs,4,Mp,0)){ MError("\"!!CD:B\"- cannot get case"); RETURN(0) }
      int tp; if(Apply(&tp,4,Mp,1)){ MError("\"!!CD:B\"- cannot get town type"); RETURN(0) }
      if(tp<0 || tp>=TOWNNUM){ MError("\"!!CD:B\"- incorrect town type"); RETURN(0) }
      int st; if(Apply(&st,4,Mp,2)){ MError("\"!!CD:B\"- cannot get structure"); RETURN(0) }
      if(st<0 || st>=44){ MError("\"!!CD:B\"- incorrect structure type"); RETURN(0) }
      int i,fl,val/*,val2*/;
      _BuildMask_ *Masks; *(Dword *)&Masks=0x66CD98;
      _BuildMask_  var;
      switch(cs){
        case 0:
          val=0;
          if(AllEnBuildings[tp].Lo & Masks[st].Lo) val=1;
          if(AllEnBuildings[tp].Hi & Masks[st].Hi) val=1;
          if(Apply(&val,4,Mp,3)) break; // check/get
          if(val){ // enable
            AllEnBuildings[tp].Lo |= Masks[st].Lo;
            AllEnBuildings[tp].Hi |= Masks[st].Hi;
          }else{ // disable
            AllEnBuildings[tp].Lo &= ~Masks[st].Lo;
            AllEnBuildings[tp].Hi &= ~Masks[st].Hi;
          }
          break;
        case 1:
          if(Num<5){ MError("\"!!CD:B1\"-wrong syntax"); RETURN(0) }
          var=BuildDepends[tp][st];
//          val =BuildDepends[tp][st].Lo;
//          val2=BuildDepends[tp][st].Hi;
          fl=0;
          if(Apply(&var.Lo,4,Mp,3)) fl=1; // check/get
          if(Apply(&var.Hi,4,Mp,4)) fl=1; // check/get
//          if(Apply(&val ,4,Mp,3)) fl=1; // check/get
//          if(Apply(&val2,4,Mp,4)) fl=1; // check/get
          if(fl) break;
          BuildDepends[tp][st]=var;
//          BuildDepends[tp][st].Lo=val;
//          BuildDepends[tp][st].Hi=val2;
          break;
        case 2:
          var.Lo=0; var.Hi=0;
          for(i=0;i<Num-3;i++){
            if(Apply(&val,4,Mp,i+3)){ MError("\"!!CD:B2\"- get/check syntax not supported"); RETURN(0) }
//            if(val==-1) break;
            if(val<0 || val>=44){ MError("\"!!CD:B2\"- incorrect structure type"); RETURN(0) }
            var.Lo |= Masks[val].Lo; var.Lo |= BuildDepends[tp][val].Lo;
            var.Hi |= Masks[val].Hi; var.Hi |= BuildDepends[tp][val].Hi;
          }
          BuildDepends[tp][st]=var;
          break;
        case 3:
          if(Num<5){ MError("\"!!CD:B3\"-wrong syntax"); RETURN(0) }
          var =BuildExclusions[tp][st];
          fl=0;
          if(Apply(&var.Lo,4,Mp,3)) fl=1; // check/get
          if(Apply(&var.Hi,4,Mp,4)) fl=1; // check/get
          if(fl) break;
          BuildExclusions[tp][st]=var;
          break;
        case 4:
          var.Lo=0; var.Hi=0;
          for(i=0;i<Num-3;i++){
            if(Apply(&val,4,Mp,i+3)){ MError("\"!!CD:B4\"- get/check syntax not supported"); RETURN(0) }
//            if(val==-1) break;
            if(val<0 || val>=44){ MError("\"!!CD:B4\"- incorrect structure type"); RETURN(0) }
            var.Lo |= Masks[val].Lo; var.Lo |= BuildExclusions[tp][val].Lo;
            var.Hi |= Masks[val].Hi; var.Hi |= BuildExclusions[tp][val].Hi;
          }
          BuildExclusions[tp][st]=var;
          break;
        default: MError("\"!!CD:B\"-incorrect command type."); RETURN(0)
      }
      break;}
    default: MError("\"!!CD\"-incorrect command."); RETURN(0)
  }
  RETURN(1)
}

void DaylyCastle(int User)
{
  #include "templ.h"
  _CastleSetup_ *Castle, *End;
  int   i,Num,Cnum,DoIt;
  _CastleState_ *csp;
  _MapItem_  *MIp0,*MIp;
  int    MapSize,ex,ey,el,Date;

  __asm{
    mov   ecx,BASE
    mov   ecx,[ecx]
    mov   eax,[ecx+0x021614]
    mov   Castle,eax
    mov   eax,[ecx+0x021618]
    mov   End,eax
  }
  Num=End-Castle;
  Date=GetCurDate();
  for(i=0;i<Num;i++,Castle++){
    DoIt=0;
    if((Cnum=GetCastleNumber(Castle))<0) RETURNV
    csp=&CastleState[Cnum];
    ex=Castle->x; ey=Castle->y; el=Castle->l;
    if(csp->State==-1){ // ��������
      DoIt=-1; // ��������� ����
      if(csp->DestroyedBy==User){ // ���� ���� ����� �����
        if((Date-csp->Destroyed)>=GHOSTDAYS){ // 6 ���� ������ - ����� ��������
          DoIt=1;
        }
      }else{
        if((Date-csp->Destroyed)>GHOSTDAYS){ // �� ��������� ����
          DoIt=1;
        }
      }
      // ��������� ��� � ��.
//      if(((Date-csp->Destroyed-1)%10)==0){ // ��������� �� ���� ����. � ������ 10 ����
        ProvokeAnimation(ex-2,ey-2,el,5,3,1,OAM_AUTO);
//      }
    }
    if(DoIt!=0){
      __asm{
        mov   ecx,BASE
        mov   ecx,[ecx]
        mov   eax,[ecx+0x1FC40]
        mov   MIp0,eax
        mov   eax,[ecx+0x1FC44]
        mov   MapSize,eax
      }
      MIp=&MIp0[ex+(ey+el*MapSize)*MapSize];
      if(DoIt==1){
        MIp->Attrib&=0xFE;  // ���������
      }else{
        MIp->Attrib|=0x01;  // ���������
      }
      // ��������, ���� ���-��
      if(Castle->Owner!=-1){
//        AIStartBuilding(-1); // ����������� �����
        // �������� �����
        if(Castle->IHero!=-1){ // ������ ���� �����.
          if(Castle->VHero==-1){ // � � ������ ���
            Town2Hero0(Castle);
          }
        }
        __asm{
          mov   eax,0x5BE6D0
          mov   ecx,Castle
          call  eax
        }
      }
    }
  }
  if((Date%7)==1){ // ������ ������
    // "�������" �������� �������� 8-�� ������
    for(i=0;i<DWELLMAPNUM;i++){
      if(DwellMapInfo[i].Owner!=User) continue; // ������
      DwellMapInfo[i].Mon2Town=1;
    }
  }
  RETURNV
}

// ��������� ���������� �����.
void NextTowerState(_CastleSetup_ *Castle)
{
  #include "templ.h"
  int   Cnum;
  _CastleState_ *csp;
  int    Owner;
  if((Cnum=GetCastleNumber(Castle))<0) RETURNV
  csp=&CastleState[Cnum];
  Owner=Castle->Owner;
  if((Owner==-1)||((Owner!=csp->TLastOwner)&&(csp->TLastOwner!=-2))){
    csp->TCenter=csp->TSide=0;
  }else{
    if(Castle->Built[1]&0x02){ // ��������� 3
      csp->TCenter+=(short)5;
      csp->TSide+=(short)3;
    }else if(Castle->Built[1]&0x02){ // ��������� 1
      csp->TCenter+=(short)5;
    }else{ // ������ ���
      csp->TCenter=csp->TSide=0;
    }
  }
  csp->TLastOwner=(short)Owner;
  RETURNV
}

void SetTowerBunus(_CastleSetup_ *Castle,Byte *MonStr)
{
  #include "templ.h"
  if(PL_TowerStd) RETURNV // ����������� ��������� �����
  _CastleState_ *csp;
  int Cnum,Bonus;
//RETURNV  
  if((Cnum=GetCastleNumber(Castle))<0) RETURNV
  csp=&CastleState[Cnum];
  int mnum=*(int *)&MonStr[0x60]; // ��������� ���������� ��������
  if(mnum==5) Bonus=csp->TCenter; else Bonus=csp->TSide; 
  *(int *)&MonStr[0x4C]+=Bonus;
  RETURNV
}
// network support
struct _TransTownState_{
  int  TInd;
  int  TCenter,TSide; // ����� �����
} TransTownState;
void SendCastleState(int cnum,int *len,Byte **buf){
  #include "templ.h"
  *len=sizeof(_TransTownState_);
  *buf=(Byte *)&TransTownState;
  TransTownState.TInd=-1; // incorrect data
//  if((Cnum=GetCastleNumber(castle))<0) RETURNV 
  if((cnum<0)||(cnum>=CASTLESNUM)) RETURNV
  _CastleState_ *csp=&CastleState[cnum];
  TransTownState.TInd=cnum;
  TransTownState.TCenter=csp->TCenter;
  TransTownState.TSide=csp->TSide;
  RETURNV
}
void ReceiveCastleState(int len,Byte *buf){
  if(len!=sizeof(TransTownState)){ TError("Wrong length of sent CastleState"); RETURNV }
  memcpy(&TransTownState,buf,sizeof(TransTownState));
  int Cnum=TransTownState.TInd;
  if(Cnum<0) RETURNV // no data was sent
  _CastleState_ *csp=&CastleState[Cnum];
  csp->TCenter=TransTownState.TCenter;
  csp->TSide=TransTownState.TSide;
  RETURNV
}

void CastleTowers(void)
{
  #include "templ.h"
  _CastleSetup_ *Castle, *End;
  int   i,Num;
//  _CastleState_ *csp;
  int    Date;

  if(PL_TowerStd) RETURNV // ����������� ��������� �����
  Date=GetCurDate();
  if(((Date%7)!=1)||(Date==1)) RETURNV // �� ������ ������
  __asm{
    mov   ecx,BASE
    mov   ecx,[ecx]
    mov   eax,[ecx+0x021614]
    mov   Castle,eax
    mov   eax,[ecx+0x021618]
    mov   End,eax
  }
  Num=End-Castle;
  for(i=0;i<Num;i++,Castle++){
    NextTowerState(Castle);
  }  
  RETURNV
}

// �������� �� ���������� AI ������� ��������� 5C119B
// �������� �� ���������� AI ������� ���������� �������� 5BF7E4
int AIStartBuilding(int BType)
{
  _CastleSetup_ *CStructure; _ECX(CStructure);
  #include "templ.h"
  Byte   *Building,*Bonus;
  int     Cnum,ct,nct;
  _CastleState_ *csp;
  int     VHero,IHero,Mn,i;
  _Hero_ *Hp0,*Hp;
  int     ex,ey,el;
  _MapItem_  *MIp;
  Dword   Mask;
  
  if(BType==10) RETURN(1) // ��������� ������
// ��� ����������� �������������
//  if(BType==-1) BType=10;
  if((Cnum=GetCastleNumber(CStructure))<0) RETURN(0)
  csp=&CastleState[Cnum];
  if(csp->State>0){ // ���� ��������� ����������
    csp->State=0;
    RETURN(0)
  }
  if(csp->State!=-1) RETURN(0) // �� ���������
  VHero=CStructure->VHero;
  IHero=CStructure->IHero;
  Building=CStructure->Built;
  Bonus=CStructure->Bonus;
  if((Building[1]&0x3C)!=0) RETURN(0)
// �������� ������
//  Building[1]|=0x04;
//  Bonus[1]|=0x04;
  __asm{
    mov  eax,BASE
    mov  eax,[eax]
    add  eax,0x21620
    mov  Hp0,eax
  }
  if(VHero==-1){ 
    if(IHero==-1) Hp=0;
    else Hp=&Hp0[IHero]; 
  }else Hp=&Hp0[VHero];
  Mn=csp->Ghost;
  if(Mn!=0){ // ����. ����
    if(Hp!=0){
      for(i=0;i<7;i++){
        if(Hp->Ct[i]==-1){
          Hp->Ct[i]=GHOSTTYPE;
          Hp->Cn[i]=Mn;
          break;
        }
      }
    }
  }
  csp->Ghost=0;
  csp->State=0;
//  b=10; // �������� ������
  ct=CStructure->Type;
  if(Hp!=0) nct=Hp->Spec/2; else nct=ct;
// ����� ������ ���� �������� �� �������
  if(ct!=nct){
    CStructure->Type=(Byte)(nct); // ������ ��� ������
    Building[2]&=0xFE;
    Bonus[2]&=0xFE;
    ex=CStructure->x; ey=CStructure->y; el=CStructure->l;
    MIp=GetMapItem(ex,ey,el);
    MIp->OSType=(Word)(nct);
    for(i=0;i<2;i++){
      Mask=CStructure->BMask[i];
      Mask&=CommonBuildingsMask[0][i];
      Mask|=CommonBuildingsMask[1][i];
      Mask&=UniqBuildingsMask[nct][i];
      CStructure->BMask[i]=Mask;
    }
  }  
// �������� ������
  __asm{
    push   10
    mov    ecx,CStructure
    mov    eax,0x5BF7C0
    call   eax
  }  
  RETURN(0)
}

int zret;

void __stdcall AIBuild(Dword BType)
{
  __asm pusha
  zret=AIStartBuilding(BType);
  OriginalCallPointer=Callers[11].forig;
  __asm popa;
  __asm push  edi
  __asm call dword ptr [OriginalCallPointer]
  if(zret) __asm  mov eax,zret
}

int Enter2Castle(int GM_ai,_MapItem_ *Mi,_Hero_ *Hr,Dword /*avd.Manager*/)
{
  #include "templ.h"
  int   Cnum,Date;
  _CastleSetup_ *CStr;
  _CastleState_ *csp;

  // �������� �� �����
  // ���� �� ��������� �� ����, �� ���� �� �������
  if((CStr=FindCastleStr(Mi))==0) RETURN(-1) // �� ����� ����� - ������ �� ��
  if((Cnum=GetCastleNumber(CStr))<0) RETURN(1)
  csp=&CastleState[Cnum];
  if(csp->State!=-1){ // ��  ��������
//    CStr[1]=(Byte)Hr->Owner; // ������-�� �������� ����� � �����
    goto l_Exit;
  }
  Date=GetCurDate();
  if(csp->DestroyedBy==Hr->Owner){ // ���� ���� ����� �����
    if((Date-csp->Destroyed)>=GHOSTDAYS) goto l_Exit; // 6 ���� ������
  }else{
    if((Date-csp->Destroyed)>GHOSTDAYS) goto l_Exit; // �� ��������� ����
  }
  // ������ ���� �������
  if(GM_ai) Message(ITxt(33,0,&Strings),1);
  RETURN(1)
l_Exit:
  NPC2Castle(GM_ai,Hr,CStr);
  RETURN(0)
}

// �������� ����� �� ����� ����� (�������)
// ��� ���� �� ����������� �������������� ����� � �����.
// esi -> �����
// edx -> �����
//:004AAD4A 6A01           push   00000001
//:004AAD4C 6A00           push   00000000
//:004AAD4E 8BCF           mov    ecx,edi
//:004AAD50 8945F8         mov    [ebp-08],eax
//:004AAD53 E888C8F6FF     call   H3.004175E0
Dword MTD_Ecx;
void __stdcall MakeTownDefender(Dword v2,Dword v1)
{
  __asm{
    mov   MTD_Ecx,ecx
    mov   al,[edx+0x22] // ������ �����
    mov   dl,[esi+1]    // ������ ������
  }
  __asm mov BDummy,dl
  if(BDummy!=0xFF) goto lOk; // ���� ���� ������
//  if(_AL==_DL) goto Ok;  // ���� ���� ������
  __asm{
    mov   eax,[esi+0xE0]      // -1 ��� =-1, ���� ������ ���
    add   eax,[esi+0xE0+0x04] // -2
    add   eax,[esi+0xE0+0x08] // -3
    add   eax,[esi+0xE0+0x0C] // -4
    add   eax,[esi+0xE0+0x10] // -5
    add   eax,[esi+0xE0+0x14] // -6
    add   eax,[esi+0xE0+0x18] // -7
  }
  _EAX(DDummy); if((int)DDummy!=-7) return;
  __asm{
    mov   eax,[esi+0x0C]      // ���� �� ���������� �����
  }
  _EAX(DDummy); if((int)DDummy!=-1) return;
lOk:
  __asm{
    mov   eax,v1
    mov   ebx,v2
    mov   ecx,MTD_Ecx
    push  v1
    push  v2
    mov   eax,0x4175E0
    call  eax
  }
}

//////////////////////////////
// ������ �������� 8-�� ������
//#define DWELLMAPNUM 1000
int FindDwellInfo(_Dwelling_ *dw)
{
  #include "templ.h"
  int i;
  for(i=0;i<DWELLMAPNUM;i++){
    if(DwellMapInfo[i].SType==0) continue; // ������
    if(DwellMapInfo[i].x!=dw->x) continue;
    if(DwellMapInfo[i].y!=dw->y) continue;
    if(DwellMapInfo[i].l!=dw->l) continue;
    RETURN(i)
  }
  RETURN(-1)
}

int AddDwellInfo(_Dwelling_ *dw)
{
  #include "templ.h"
  int i;
  i=FindDwellInfo(dw);
  if(i==-1){
    for(i=0;i<DWELLMAPNUM;i++){
      if(DwellMapInfo[i].SType==0) goto l_found; // ������
    }
    RETURN(-1)
  }
l_found:
  DwellMapInfo[i].Owner=dw->Owner;
  DwellMapInfo[i].x=dw->x;
  DwellMapInfo[i].y=dw->y;
  DwellMapInfo[i].l=dw->l;
  DwellMapInfo[i].SType=dw->SType;
  RETURN(i)
}

int IsFirstDay(_Dwelling_ *dw)
{
  #include "templ.h"
  int ind;
  int Day=GetCurDate();
  ind=FindDwellInfo(dw);
  if(ind==-1) RETURN(0) // ������ ���
  if((Day-DwellMapInfo[ind].GotDay)==0) RETURN(1)
  RETURN(0)
}
// ���� �������� ��� ������
static int E2D_GuardType[9][2][7];
/*
={
 {{3,1,11,150,5,7,9},{48,96,3,1,24,12,6}},
 {{19,23,25,151,21,17,15},{24,6,3,1,12,48,96}},
 {{29,33,31,152,37,39,35},{96,24,48,1,6,3,12}},
 {{45,47,53,153,51,49,43},{48,24,3,1,6,12,96}},
 {{65,59,67,154,63,61,57},{6,48,3,1,12,24,96}},
 {{75,71,79,155,81,73,77},{24,96,6,1,3,48,12}},
 {{89,85,91,156,93,87,95},{24,96,12,1,6,48,3}},
 {{101,103,109,157,107,105,99},{48,24,3,1,6,12,96}},
 {{123,119,129,158,121,125,127},{24,96,6,1,3,48,12}}
};
*/
int Enter2Dwelling(int GM_ai,_MapItem_ *Mi,_Hero_ *Hr,Dword /*avd.Manager*/,Dword *Object)
{
  #include "templ.h"
  int st,ind,i;
  _Dwelling_ *dw;
  _DwellMapInfo_ *di;
  // �������� �� ����� �������
//  if((CStr=FindCastleStr(Mi))==0) return -1; // �� ����� �� - ������ �� ���
  if(PL_ExtDwellStd==1) RETURN(-1)
  if(Mi->OType!=17) RETURN(-1) // �� dwelling
  st=Mi->OSType;
  if((st<80)||(st>88)) RETURN(-1) // �� ���
//asm int 3
  dw=FindDwellStr(Mi);
  if(dw==0) RETURN(-1) // �� ����� ������ ������ - ������ ?
  *Object=(Dword)dw;   // ������ ��.
  ind=AddDwellInfo(dw);    // �������, ���� ��� �� ����
  if(ind==-1) RETURN(-1) // ������ �� ���� - ������ ���� �� ������
  di=&DwellMapInfo[ind];
  if(dw->Owner==Hr->Owner){ //  ������ ������
//asm int 3
    if(IsFirstDay(dw)){ // � ���� ���� � �������� - ����� ������
      if(dw->Num2Hire[0]==0){ // ������ ��� ��������
        if(GM_ai){
          RequestPic(ITxt(43,0,&Strings),0x15,150-80+st,1); // ��� �������
          RETURN(1)
        }
      }else RETURN(0) // ����� ��� ���� ����� �������
    }else{ // ����� ������, ������ ������ � ��������������� �����
      if(di->Mon2Town/*Num2Hire[0]*/==0){ // ���, ��������� � �������
        if(GM_ai){
          RequestPic(ITxt(44,0,&Strings),0x15,150-80+st,1); // ��� �������
        }else RETURN(0) // ����� AI �������� - � �� �� ��� ����������
      }else{ // �� ����� - �������
        if(GM_ai){
          RequestPic(ITxt(41,0,&Strings),0x15,150-80+st,1); // ��� �������
        }else RETURN(0) // ����� AI �������� - � �� �� ��� ����������
//        return 0; // ��������� ���� �������� � �����
      }  
      RETURN(1) // ������ ��� ����� ������
    }
  }else{ // ���� ������
    // ���������� ��� ��������
    for(i=0;i<7;i++){
      dw->GType[i]=E2D_GuardType[st-80][0][i];
      dw->GNum[i]=E2D_GuardType[st-80][1][i];
    }
    // � ����� ������ ���������
    dw->Num2Hire[0]=1;
    RETURN(0) // ����� ��� ���� ����� �������
  } 
  RETURN(0)
}

void EnterOutOfDwelling(int GM_ai,Dword Object)
{
  #include "templ.h"
  int ind,i;
  _Dwelling_ *dw=(_Dwelling_ *)Object;
  int Day=GetCurDate();
  _DwellMapInfo_ *di;
  
  if(dw==0) RETURNV // ������-�� ����������
  ind=FindDwellInfo(dw);
  if(ind==-1) RETURNV // ������ �� ���� - ������ ���� �� ������
  di=&DwellMapInfo[ind];
  if(di->Owner!=dw->Owner){ // ������ �������� - ��������
    di->Owner=dw->Owner;   // ������������
    di->GotDay=(short)Day;
    di->Mon2Town=0; // ��������� ������ �� ���� ������
    if(dw->Num2Hire[0]!=0){ // �� �����
      if(GM_ai){
        RequestPic(ITxt(42,0,&Strings),0x15,150-80+dw->SType,1); // ��� �������
      }
    }
    // ������� ����
    for(i=0;i<8;i++){
      ShowArea(dw->x,dw->y,dw->l,i,1);
    }
  }
  RETURNV
}

//////////////////////////
// ���� �������� 8-�� ������ � �������
static struct C2H_HireBufStr{
  Byte  _u1[0x50];
  int    DefCrType;
  Word  *DefCrNum; //-> ����� ��� ����� (������ ����� ��� ���������� �����)
  int    DefCrInd; // 0,1,2,3
  int    CrType[4];
  Word  *CrNum[4];
} *C2H_HireBufPo;
//Byte  *C2H_CrMan;
static Byte  *C2H_TownMan;
static Byte  *C2H_Town;
static int PC2H_MonTrans[][2]={
  {150,13},{151,27},{152,41},{153,55},{154,69},{155,83},{156,97},{157,111},{158,131}, // 8 level
  {-1,-1} // ���������
};
void ProcessC2H(void)
{
  #include "templ.h"
  int   i,StInd,mon,mtl,mth;
  int   Owner,SInd,DwNum;
//  int   num;
  
  if(WoG==0) RETURNV
  C2H_Town=(*(Byte **)&C2H_TownMan[0x38]);
//....
//  tp=C2H_HireBufPo->CrNum[0]; // ���-�� 0
  mth=C2H_HireBufPo->CrType[0];
  mtl=C2H_HireBufPo->CrType[1];
  if(mth==-1) RETURNV // ��� ������ ����� �������� ������ (����������)
  else if(mtl==-1) StInd=1;
  else StInd=2;
  if(StInd==1) RETURNV // ��� ��������  
  for(i=0;;i++){
    if(PC2H_MonTrans[i][0]==-1) break; // ���������
    if(PC2H_MonTrans[i][1]==mth){ mon=PC2H_MonTrans[i][0]; SInd=i; goto l_found; }
  }
  RETURNV
l_found:
  // ��������� �� ���������� �������� 8-�� ������ � ������
  Owner=C2H_Town[1];
  DwNum=-1;
  for(i=0;i<DWELLMAPNUM;i++){
    if(DwellMapInfo[i].Owner!=Owner) continue; // �� ���
    if(DwellMapInfo[i].SType!=(SInd+80)) continue; // �� ���
    if(DwellMapInfo[i].Mon2Town==0) continue; // ���
    // �����
    DwNum=i;
    break;
  }
  if(DwNum==-1) RETURNV // ��� ������ - 

//  mon=C2H_Town[4]+150;
//  num=1;
  C2H_HireBufPo->CrType[StInd]=mon;   // ��� 3
  C2H_HireBufPo->CrNum[StInd]=&DwellMapInfo[DwNum].Mon2Town;   // ���-�� 3
//  C2H_HireBufPo->CrType[StInd+1]=1; // ��� 4
//  C2H_HireBufPo->CrNum[StInd+1]=tp; // ���-�� 4
  C2H_HireBufPo->CrType[StInd+1]=-1; // ��� 4
  C2H_HireBufPo->CrNum[StInd+1]=0; // ���-�� 4
  RETURNV
}

void __stdcall Creature2Hire(Dword)
{
  __asm pusha
  _EAX(C2H_HireBufPo);
  _EBX(C2H_TownMan);
  ProcessC2H();
  OriginalCallPointer=Callers[7].forig;
  __asm popa;
  __asm push C2H_HireBufPo
  __asm call dword ptr [OriginalCallPointer]
}

///// ERM
int ERM_Castle(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i]) //  STARTC("Process !!CA",&Mp->m.s[Mp->i])
  int  i,j,tp,*stp,hn;
  Byte b,*msk;
  Dword MixPos;
  _MapItem_ *mip=0;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  _CastleSetup_ *dp=GetCastleBase(); if(dp==0){ MError("\"!!CA\"-no Castles defined for a map.."); RETURN(0) }
//  _CastleState_ *csp;
  switch(sp->ParSet){
    case 2: // ����/�����
      i=GetVarVal(&sp->Par[0]);
      if(i!=0){ MError("\"CA#/#\"-first parameter out of range (0)."); RETURN(0) }
      i=GetVarVal(&sp->Par[1]);
      if((i<0)||(i>=GetCastleNum())){ MError("\"CA$\"-cannot find castle (out of range)."); RETURN(0) }
      dp=&dp[i];
      break;
    case 1: // ������� indirect (-1=�������)
      i=GetVarVal(&sp->Par[0]);
      if(i==-1){ // �������
        __asm  mov   eax,0x69954C // -> TownManager
        __asm  mov   eax,[eax]
        __asm  mov   eax,[eax+0x38]
        __asm  mov   dp,eax
        break;
      }
    case 3: // �������
      MixPos=GetDinMixPos(sp);
      mip=GetMapItem2(MixPos);
      stp=(int *)mip;
      tp=CheckPlace4Hero(mip,(Dword **)&stp);
      if(tp!=98){ MError("\"!!CA\"-not a Castle."); RETURN(0) }
      if(*stp>=GetCastleNum()){ MError("\"!!CA\"-Castle number out of array."); RETURN(0) }
      dp=&dp[*stp];
      break;
    default: // ???
      MError("\"CA???\"-incorrect syntax.");
      RETURN(0)
  }
  switch(Cmd){
    case 'H': //H1/$ ���� ������� H0/$ ����� � ���������
      if(Num!=2){ MError("\"!!CA:H\"-wrong syntax"); RETURN(0) }
      switch(Mp->n[0]){
        case 0:
          hn=dp->IHero; if(Apply(&hn,4,Mp,1)) break;
          if(hn==dp->IHero) break;
          dp->IHero=hn;
          if(hn==-1) break;
          if((hn<0)||(hn>=HERNUM)){ MError("\"!!CA:H\"-wrong hero number"); RETURN(0) }
          GetHeroStr(hn)->x=dp->x;
          GetHeroStr(hn)->y=dp->y;
          GetHeroStr(hn)->l=dp->l;
          GetHeroStr(hn)->Visible=0;
          break;
        case 1:
          hn=dp->VHero; if(Apply(&hn,4,Mp,1)) break;
          if(hn==dp->VHero) break;
          dp->VHero=hn;
          if(hn==-1) break;
          if((hn<0)||(hn>=HERNUM)){ MError("\"!!CA:H\"-wrong hero number"); RETURN(0) }
          GetHeroStr(hn)->x=dp->x;
          GetHeroStr(hn)->y=dp->y;
          GetHeroStr(hn)->l=dp->l;
          GetHeroStr(hn)->Visible=1;
          break;
        default: MError("\"!!CA:H\"-wrong first parameter (0,1)"); RETURN(0)
      }
      break;
    case 'U': // U$ ����� �����
      Apply(&dp->Number,1,Mp,0);
      break;
    case 'I': // I$ ����������� ����� �� �����
      Apply(&i,4,Mp,0);
//      csp=&CastleState[dp->Number];
      if(i<-1) i=-1;
      if(i>3)  i=3;
//      csp->State=i;
      mip=GetMapItem(dp->x,dp->y,dp->l);
//005BF4838B0D38956900   mov    ecx,[00699538]
//005BF489 33C0           xor    eax,eax
//005BF48B 8A4607         mov    al,[esi+07]
//005BF48E 33D2           xor    edx,edx
//005BF490 8BB944FC0100   mov    edi,[ecx+0001FC44]
//005BF496 8A5606         mov    dl,[esi+06]
//005BF499 0FAFC7         imul   eax,edi
//005BF49C 03C2           add    eax,edx
//005BF49E 33D2           xor    edx,edx
//005BF4A0 0FAFC7         imul   eax,edi
//005BF4A3 8A5605         mov    dl,[esi+05]
//005BF4A6 03C2           add    eax,edx
//005BF4A8 8D14C0         lea    edx,[eax+8*eax]
//005BF4AB 8D0450         lea    eax,[eax+2*edx]
//005BF4AE 8B9140FC0100   mov    edx,[ecx+0001FC40]
//005BF4B4 8D0442         lea    eax,[edx+2*eax]
//005BF4B7 50             push   eax
//005BF4B8 E893A1F0FF     call   H3WOG.004C9650
      CastleCheck(i);
      __asm{
        mov    ecx,BASE
        mov    ecx,[ecx]
        mov    eax,mip
        push   eax
        mov    eax,0x4C9650
        call   eax
      }
      break;
    case 'N': // N^text^ , M$, M-1 ��������
      if(NewMesMan(Mp,&dp->Name,0)){ MError("\"!!CA:N\"-Cannot set a Castle Name."); RETURN(0) }
      break;
    case 'P': // P$/$/$ ������� �����
      Apply(&dp->x,-1,Mp,0); // unsigned 3.58 bug fix
      Apply(&dp->y,-1,Mp,1); // unsigned 3.58 bug fix
      Apply(&dp->l,1,Mp,2);
      break;
    case 'O': // O$, O-1 ������
      // ��������, ���� ���-��
      if(Mp->VarI[0].Check==0){ // �������������
        int _owner,_number;
        _owner=Mp->n[0];
        _number=dp->Number;
        __asm{
          mov    ecx,_number
          mov    eax,_owner
          push   0
          push   0
          push   eax
          push   ecx
          mov    ecx,BASE
          mov    ecx,[ecx]
          mov    eax,0x4C5EA0
          call   eax
        }
      }
      Apply(&dp->Owner,1,Mp,0);
      break;
    case 'T': // Ttype
      if(Apply(&dp->Type,1,Mp,0)) break;
      mip->OSType=(Word)dp->Type;
      CastleCheck(0);
      break;
//    case 'V': // V$, V-1 ������� ?
//      Apply(&dp->Tavern,1,Mp,0);
//      break;
    case 'R': // R$, (0,1,2???) 3.58 ����������� ������� � ���� ���� 
      Apply(&dp->BuiltThisTurn,1,Mp,0);
      break;
    case 'G': // ��� �������
      switch(Num){
        case 1: // G$ ������� ��� �������
          Apply(&dp->MagLevel,1,Mp,0);
          break;
        case 2: // G$/$ ���-�� ���� �� ������� ������� ��� �������
          if((Mp->n[0]<0)||(Mp->n[0]>4)){ MError("\"!!CA:G\"-A level of Magic Guild out of range (0...4)."); RETURN(0) }
          Apply(&dp->MagicHild[Mp->n[0]],1,Mp,1);
          break;
        case 3: // G$/$/$ ����������
          if((Mp->n[0]<0)||(Mp->n[0]>4)){ Error(); RETURN(0) }
          if((Mp->n[1]<0)||(Mp->n[1]>5)){ Error(); RETURN(0) }
          Apply(&dp->Spels[Mp->n[0]][Mp->n[1]],4,Mp,2);
          break;
        default: MError("\"!!CA:G\"-incorrect command type (1...3)."); RETURN(0)
      }
      break;
    case 'M': // �������
      if(Num!=4){ Error(); RETURN(0) }
      switch(Mp->n[0]){
        case 1: // M1/pos/$/$ ���� �������� � ��� ?
          if((Mp->n[1]<0)||(Mp->n[1]>6)){ MError("\"!!CA:M\"-position out of range (0...6)."); RETURN(0) }
          Apply(&dp->Monsters[0][Mp->n[1]],2,Mp,2);
          Apply(&dp->Monsters[1][Mp->n[1]],2,Mp,3);
          break;
        case 2: // M2/pos/$/$ ������ ����� ��� � ���-��
          if((Mp->n[1]<0)||(Mp->n[1]>6)){ MError("\"!!CA:M\"-position out of range (0...6)."); RETURN(0) }
          Apply(&dp->GuardsT[Mp->n[1]],4,Mp,2);
          Apply(&dp->GuardsN[Mp->n[1]],4,Mp,3);
          break;
        case 3: // M3/pos/$/$ ������ ����� ��� � ���-��
          if((Mp->n[1]<0)||(Mp->n[1]>6)){ MError("\"!!CA:M\"-position out of range."); RETURN(0) }
          Apply(&dp->GuardsT0[Mp->n[1]],4,Mp,2);
          Apply(&dp->GuardsN0[Mp->n[1]],4,Mp,3);
          break;
        default: Error(); RETURN(0)
      }
      break;
    case 'B': // ������
      if(Num!=2){ MError("\"!!CA:B\"-wrong syntax."); RETURN(0) }
      if((Mp->n[1]<0)||(Mp->n[1]>43)){ MError("\"!!CA:B\"-wrong building number (0...43)."); RETURN(0) }
      i=Mp->n[1]/8; j=Mp->n[1]%8;
      b=(Byte)(1<<j);
      switch(Mp->n[0]){
        case 1: // B1/$ ���������
          dp->Built[i]|=(Byte)b;
          dp->Bonus[i]|=(Byte)b;
          break;
        case 2: // B2/$ ���������
          dp->Built[i]&=(Byte)~b;
          dp->Bonus[i]&=(Byte)~b;
          b=CSCheckERM[Mp->n[1]].Bits2Build;
          i=CSCheckERM[Mp->n[1]].Byte2Build;
          if(b!=0){
            dp->Built[i]|=(Byte)b;
            dp->Bonus[i]|=(Byte)b;
          }
          break;
        case 3: // B3/$ ���������
          if(dp->Built[i]&(Byte)b) ERMFlags[0]=1; else ERMFlags[0]=0;
          break;
        case 4: // B4/$ ��������� �������
          msk=(Byte *)dp->BMask;
          msk[i]|=(Byte)b;
          break;
        case 5: // B5/$ ��������� �������
          msk=(Byte *)dp->BMask;
          msk[i]&=(Byte)~b;
          break;
        case 6: // B6/$ 3.58 ��������� �������� ������
          i=dp->BuiltThisTurn;
          dp->BuiltThisTurn=0;
          BuildTownStruct(dp,Mp->n[1]);
          dp->BuiltThisTurn=i;
          break;
        default: MError("\"!!CA:B\"-incorrect command type (1...5)."); RETURN(0)
      }
      break;
    default: MError("\"!!CA\"-incorrect command."); RETURN(0)
   }
//  }
  RETURN(1)
}

////////////////////////////////////
int SaveCasDem(void)
{
  #include "templ.h"
  if(Saver("LCDM",4)) RETURN(1)
  if(Saver(CastleState,sizeof(CastleState))) RETURN(1)
  if(Saver(CSCheck,sizeof(CSCheck))) RETURN(1)
  if(Saver(BattlePlace,sizeof(BattlePlace))) RETURN(1)
  if(Saver(&DemPerDay,sizeof(DemPerDay))) RETURN(1)
  if(Saver(DemNextCost,sizeof(DemNextCost))) RETURN(1)
  if(Saver(&Mov2Lost,sizeof(Mov2Lost))) RETURN(1)
  // Dwellings
  if(Saver(DwellMapInfo,sizeof(DwellMapInfo))) RETURN(1)
  if(Saver(MonInTownBase(0),sizeof(MonInTownsBack))) RETURN(1)
  RETURN(0)
}

int LoadCasDem(int /*ver*/)
{
  #include "templ.h"
  char buf[4]; if(Loader(buf,4)) RETURN(1)
  if(buf[0]!='L'||buf[1]!='C'||buf[2]!='D'||buf[3]!='M')
      {MError("LoadCusDem cannot start loading"); RETURN(1)}
  if(Loader(CastleState,sizeof(CastleState))) RETURN(1)
  if(Loader(CSCheck,sizeof(CSCheck))) RETURN(1)
  if(Loader(BattlePlace,sizeof(BattlePlace))) RETURN(1)
  if(Loader(&DemPerDay,sizeof(DemPerDay))) RETURN(1)
  if(Loader(DemNextCost,sizeof(DemNextCost))) RETURN(1)
  if(Loader(&Mov2Lost,sizeof(Mov2Lost))) RETURN(1)
  // Dwellings
  if(Loader(DwellMapInfo,sizeof(DwellMapInfo))) RETURN(1)
  if(Loader(MonInTownBase(0),sizeof(MonInTownsBack))) RETURN(1)
  RETURN(0)
}

int LoadTXTCasDem(void) // ��������� ������
{
  #include "templ.h"
  int i,j,t;

  // ������� �� ���������� �������� � ������
  if(LoadTXT("ZTBUILD.TXT",&TFile)) RETURN(1) 
  for(t=0;t<9;t++){
    for(i=0;i<44;i++){
      for(j=0;j<6;j++){
        CSCheck[i].Town[t].Bonus[j]=(short)a2i(ITxt(t*45+i+2,j+1,&TFile));
      }
      CSCheck[i].Town[t].Cost2Break=a2i(ITxt(t*45+i+2,9,&TFile));
      MakeCheck(i,t,                    ITxt(t*45+i+2,10,&TFile));
      CSCheck[i].Town[t].MinHeroExp=a2i(ITxt(t*45+i+2,11,&TFile));
      CSCheck[i].Town[t].MinArmyPow=a2i(ITxt(t*45+i+2,12,&TFile));
    }
  }
  UnloadTXT(&TFile);
  Copy((Byte *)CSCheck,(Byte *)CSCheck_back,sizeof(CSCheck));
  // ������� �� ����� ����� � ���������
  if(LoadTXT("ZTBATLE.TXT",&TFile)) RETURN(1) // �� ����� ��������� TXT
  for(i=0;i<14;i++){ 
    BattlePlace[i].x=a2i(ITxt(i+2,1,&TFile));
    BattlePlace[i].y=a2i(ITxt(i+2,2,&TFile));
    BattlePlace[i].l=a2i(ITxt(i+2,3,&TFile));
    BattlePlace[i].abs=a2i(ITxt(i+2,4,&TFile));
    CSMonst[i]=a2i(ITxt(i+2,5,&TFile));
  }
  UnloadTXT(&TFile);
  Copy((Byte *)BattlePlace,(Byte *)BattlePlace_back,sizeof(BattlePlace));

  // ����� ���������
  if(LoadTXT("ZTCOMMN.TXT",&TFile)) RETURN(1) // �� ����� ��������� TXT
  DemPerDay=a2i(ITxt(1,1,&TFile)); // ������� � ����
  DemPerDay_back=DemPerDay;
  for(i=0;i<DemPerDay;i++){
    DemNextCost[i]=a2i(ITxt(2,i+1,&TFile)); // ���� ����������
  }
  Copy((Byte *)DemNextCost,(Byte *)DemNextCost_back,sizeof(DemNextCost));
  Mov2Lost=a2i(ITxt(3,1,&TFile)); // ������ ����� ��� �����
  Mov2Lost_back=Mov2Lost;
  GrailDemontage=a2i(ITxt(4,1,&TFile)); // �������� ������
  UnloadTXT(&TFile);
  // ��������
  if(LoadTXT("ZDWELL8.TXT",&TFile)) RETURN(1) 
  for(t=0;t<9;t++){
    for(i=0;i<2;i++){
      for(j=0;j<7;j++){
        E2D_GuardType[t][i][j]=a2i(ITxt(t*2+i+1,j+1,&TFile));
      }
    }
  }
  UnloadTXT(&TFile);
//...
 RETURN(0)
}

static int RD_MonVsTown[9]={150,151,152,153,154,155,156,157,158};
void ResetDwellings(void)
{
  #include "templ.h"
  int i,j,k,cn,t,ind;
  _Dwelling_ *dw;
  _DwellMapInfo_ *di;

  for(i=0;i<DWELLMAPNUM;i++){
    DwellMapInfo[i].SType=0;
  }
  if(PL_ExtDwellStd==1) RETURNV
  dw=GetDwellingBase();
  cn=GetDwellingNums();
  for(i=0;i<cn;i++,dw++){
    if(dw->Owner==-1) continue; // �����
    t=dw->Mon2Hire[0];
    if(t==-1) continue;
    for(k=0;k<9;k++){
      if(t==RD_MonVsTown[k]){ // �����-�� �� �������� 8-�� ������
        ind=AddDwellInfo(dw);    // �������, ���� ��� �� ����
        if(ind==-1) RETURNV // ������ �� ���� - ������ ���� �� ������
        di=&DwellMapInfo[ind];
        di->GotDay=0;
        di->Mon2Town=1; // ��������� � ���� ������
        // ������� ����
        for(j=0;j<8;j++){
          ShowArea(dw->x,dw->y,dw->l,j,1);
        }
        break;
      }
    }
  }
  RETURNV
}

void ResetCastles(void)
{
  #include "templ.h"
  int i;
  for(i=0;i<CASTLESNUM;i++){
    CastleState[i].State=0;
    CastleState[i].Date=0;
    CastleState[i].Cost=0;
    CastleState[i].Destroyed=0;
    CastleState[i].Ghost=0;
    CastleState[i].TCenter=0;
    CastleState[i].TSide=0;
    CastleState[i].TLastOwner=-2;
  }
  CastleCheck(0);
  if(MonInTownsBack_Saved==0){
    Copy((Byte *)0x6747B4,(Byte *)MonInTownsBack,sizeof(MonInTownsBack));
    MonInTownsBack_Saved=1;
  }
  Copy((Byte *)MonInTownsBack,(Byte *)0x6747B4,sizeof(MonInTownsBack));
// ZVS 21.02.02
  ResetDwellings();
  RETURNV
}

void InitCastles(void)
{
  #include "templ.h"
  ResetCastles();
  Copy((Byte *)BattlePlace_back,(Byte *)BattlePlace,sizeof(BattlePlace));
  DemPerDay=DemPerDay_back;
  Copy((Byte *)DemNextCost_back,(Byte *)DemNextCost,sizeof(DemNextCost));
  Mov2Lost=Mov2Lost_back;
  Copy((Byte *)CSCheck_back,(Byte *)CSCheck,sizeof(CSCheck));
  RETURNV
}

// ���� ���������� � ��������� ��������� ��� ����� �����
//struct _CSCheck_{
//  Byte Mon;         // ��� �������� ��� �����
//  Byte Bits2Build;  // ����� ���������� ����� ������� ���� ������ ...
//  Byte Byte2Build;  // ... � ���� �����
//  struct {
//    Byte  Depend[6];
//    int   Cost2Break;
//    int   MinHeroExp;
//    int   MinArmyPow;
//    short Bonus[6];
//  } Town[9];  
//} CSCheck[44];

void __stdcall SoDFix_SpaceInAlliedTown(int par1,int par2,int par3)
{
  Byte *TownMan; _ECX(TownMan);
  _CastleSetup_ *csp=(_CastleSetup_ *)*(Dword *)&TownMan[0x38];
  int hv;
  hv=csp->VHero;
  if(csp->Owner!=CurrentUser()) return; // not a town owner
  if(GetHeroStr(hv)->Owner!=csp->Owner) return;
  __asm{
    mov   ecx,TownMan
    push  par3
    push  par2
    push  par1
    mov   eax,0x5D5010
    call  eax
  }

}
// 3.58f
__declspec( naked ) void FixWrongTownListInfo(void)
{
  __asm{
    pusha
    mov   ecx,0x699538
    mov   ecx,[ecx]
    mov   eax,0x4CE670
    call  eax
    mov   DDummy,eax
    popa
    mov   eax,DDummy
    ret
  }
}

// 3.59
void ResetNewTownStruct(void){
  #include "templ.h"
  // all new things here
  struct _BuildMask_ (*or_AllEnBuildings)[TOWNNUM];      *(Dword *)&or_AllEnBuildings=0x697740;
  struct _BuildMask_ (*or_BuildDepends)[TOWNNUM][44];    *(Dword *)&or_BuildDepends=0x6977E8;
  struct _BuildMask_ (*or_BuildExclusions)[TOWNNUM][44]; *(Dword *)&or_BuildExclusions=0x6A8C20;
  int i;
  for(i=0;i<TOWNNUM_0;i++){
     AllEnBuildings[i]=(*or_AllEnBuildings)[i];
  }
//  for(i=0;i<TOWNNUM_0;i++){
//     BuildDepends[i]=(*or_BuildDepends)[i];
//  }
  memcpy(BuildDepends,*or_BuildDepends,sizeof(_BuildMask_)*TOWNNUM_0*44);
  memcpy(BuildExclusions,*or_BuildExclusions,sizeof(_BuildMask_)*TOWNNUM_0*44);
  memcpy(TownStructOnScreen,(void *)0x66CF98,TOWNNUM_0*18);
  memcpy(TownStructOnScreenNum,(void *)0x66D03C,TOWNNUM_0);

  // clean up for testing
//  SetMem(*or_AllEnBuildings,sizeof(_BuildMask_)*TOWNNUM_0,0);
//  SetMem(*or_BuildDepends,sizeof(_BuildMask_)*TOWNNUM_0*44,0);
//  SetMem(*or_BuildExclusions,sizeof(_BuildMask_)*TOWNNUM_0*44,0);
  RETURNV
}
void AdjustNewTownStructures(void){
  #include "templ.h"
  void (*fp)(void); *(Dword *)&fp=0x4EB810;
  fp();
//  ResetNewTownStruct();
  RETURNV
}
int SaveNewTown(void)
{
  #include "templ.h"
  if(Saver("NTWN",4)) RETURN(1)
  if(Saver(AllEnBuildings,sizeof(AllEnBuildings))) RETURN(1)
  if(Saver(BuildDepends,sizeof(BuildDepends))) RETURN(1)
  if(Saver(BuildExclusions,sizeof(BuildExclusions))) RETURN(1)
  RETURN(0)
}

int LoadNewTown(int ver)
{
  #include "templ.h"
  ResetNewTownStruct();
  if(ver < 18) RETURN(0)
  char buf[4]; if(Loader(buf,4)) RETURN(1)
  if(buf[0]!='N'||buf[1]!='T'||buf[2]!='W'||buf[3]!='N')
    {MError("LoadNewTown cannot start loading"); RETURN(1)}
  if(Loader(AllEnBuildings,sizeof(AllEnBuildings))) RETURN(1)
  if(Loader(BuildDepends,sizeof(BuildDepends))) RETURN(1)
  if(Loader(BuildExclusions,sizeof(BuildExclusions))) RETURN(1)
  RETURN(0)
}


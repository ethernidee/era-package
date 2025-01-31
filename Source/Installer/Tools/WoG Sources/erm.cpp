#include <stddef.h>
#include <stdio.h>
#include "structs.h"
#include "common.h"
#include "txtfile.h"
#include "b1.h"
#include "casdem.h"
#include "service.h"
#include "herospec.h"
#include "monsters.h"
#include "anim.h"
#include "womo.h"
#include "sound.h"
#include "npc.h"
#include "erm.h"
#include "ai.h"
#include "CrExpo.h"
#include "wogsetup.h"
#include "timer.h"
#define __FILENUM__ 1
#include "string.h"
#include "stdlib.h"
#include "animdlg.h"
#include "lod.h"
#include "dlg.h"
#include "spell.h"
#include "lod.h"
#include "prot.h"

_PostERM_ *PostERM;
_Cmd_     *Heap;
Dword      HeapSize=0;
// _Date_    *CurDate;
_Main_    *Main;
////Word CurrentScope=0;
////_Scope_ *FirstERMScope=0;
////_Scope_ *ERMScope=0;
struct _ERMScript_{
  int   Used;  // 2-�� ������������ � �����/1-��������/0-no
//  char  FileName[63]; // ��� �����
  int   Size; // ������ � ������ ������������ �����
} ERMScript[SCRIPTSNUM];
char *ERMBody[SCRIPTSNUM];
int        ERMEnabled=0;
int        ERM_RetVal=0;
int        ERM_PosX=0,ERM_PosY=0,ERM_PosL=0;
int        ERM_GM_ai=-1;   // ��� ������� ������
//int        ERM_This=-1;    // ��� ���, ��� ����� ���������?
_Hero_    *ERM_HeroStr=0;  // �����, ���������� ������
//int        PL_ExtDwellStd=0; // 1-����������� �������� 8-�� ������
//int        PL_TowerStd=0; // 1-����������� ���������� �����
//int        PL_MLeaveStd=0; // 1-����������� ���������� ��������
//int        PL_NoNPC=0; // 1-������ NPC
int   PL_NPCOptionWasSet=0;
int   PL_CustomOptionWasSet=0; // 3.58
int   PL_DisableWogifyWasSet=0; // 3.58
int   PL_ExpoWasSet=0; // 3.58
int   WoGSpecMap=0; // ����� random_... ��� wogify_...
int   PL_WoGOptions[2][PL_WONUM]; // ��� �����
// �� ����� ���� ������������ � 1 �� 20 ���
int   ERMVar[20];           char ERMVarMacro[20][8];
char  ERMVarUsed[20];
char  ERMFlags[1000];       char ERMFlagsMacro[1000][8];
char  ERMFlagsUsed[1000];
int   ERMVar2[10000];       char ERMVar2Macro[10000][8];
char  ERMVar2Used[10000];
int   ERMW=0;
int   ERMVarH[HERNUM][200]; char ERMVarHMacro[HERNUM][200][8];
char  ERMVarHUsed[200];
char  ERMString[1000][512];  char ERMStringMacro[1000][8];
char  ERMStringUsed[1000];
char  ERMLString[10][512];
char  ERMFunUsed[30000];
char  ERMTimerUsed[100];
int   ERMVarUsedStore=0; //������ �� ���� ������������� ����������
int   ERMVarCheck4DblStore=0; // ��������� �� ������������
int   NextMessShowTime=0; // show time for the next message (self reset, not saved)
Word  GlobalCurrentScope=0; // 3.59 current trigger scope
struct _Square_{
  unsigned Hero    :8; // ��������� ���������� �����
  signed   Owner   :4; // ������
  unsigned Number  :4; // ���������������� ����� 0...15
  unsigned NumberT :8; // 0...255
  unsigned NumberS :8; // 0...255
} Square[144][144][2];
struct _Square2_{
  short S[4];
  long  L[2];
} Square2[144][144][2];

int NextWeekOf=0;   // ������ ����-��
int NextWeekMess=0; // ���������
int NextMonthOf=0;  // ��� ������
int NextMonthOfMonster=0; // ������ *2
int LoadVersion4Scripts=0;
int AI_Delay=0x1000;
int AutoSaveFlag=1;
char Load2Path[MAX_PATH]; // 3.58 alternate path for loading scripts
struct _Timer_{
  Word FirstDay;
  Word LastDay;
  Word Period;
  Word Owners; // ��������
} ERMTimer[100];
// �� ���� ����������
int   ERMVarX[16];
int   ERMVarY[100],ERMVarYT[100];
float ERMVarF[100],ERMVarFT[100];

int EnableMithrill=0;
int EnableChest[20]={0,0,0,0,0};
int MithrillVal[8]={0,0,0,0,0,0,0,0};

int MonsterUpgradeTable[MONNUM];

struct _ArtNames_{
  int NameVar; // ����� z ���������� (0-������������)
  int DescVar;
} ArtNames[ARTNUM];
int ArtSetUpBackStored=0;
_ArtSetUp_ ArtSetUpBack[ARTNUM];

int HTableBackStored=0;
_HeroInfo_ HTableBack[HERNUM+8];

struct _SSAllNames_{
// 0-���, 1-���.����, 2- �����.����, 3-����.����
  int Var[4];   // ����� z ���������� (0-������������)
} SSAllNames[SSNUM];
int SSNameBackStored=0;
_SSName_ SSNameBack[SSNUM];
int SSDescBackStored=0;
_SSDesc_ SSDescBack[SSNUM];
int SSNameDescBackStored=0;
_SSNameDesc_ SSNameDescBack[SSNUM];

struct _MonNames_{
// 0-��� ����, 1-��� �����, 2-�������������
  int Var[3];   // ����� z ���������� (0-������������)
} MonNames[MONNUM];
int MonNameBackStored=0;
_MNameS_  MonTable2Back[MONNUM];
_MNameP_  MonTable3Back[MONNUM];
_MNameSp_ MonTable4Back[MONNUM];

struct _HSpecNames_{
  int PicNum; // ����� �������� ������������� +1
// 0-��������, 1-�������, 2-��������
  int Var[3];   // ����� z ���������� (0-������������)
} HSpecNames[HERNUM];
int HSpecBackStored=0;
_HeroSpec_ HSpecBack[HERNUM];

char ArtSkill[0x2D][4]={
  {3,3,3,6},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{2,0,0,0},
  {3,0,0,0},{4,0,0,0},{5,0,0,0},{6,0,0,0},{12,-3,0,0},{0,2,0,0},{0,3,0,0},{0,4,0,0},
  {0,5,0,0},{0,6,0,0},{-3,12,0,0},{0,0,0,1},{0,0,0,2},{0,0,0,3},{0,0,0,4},{0,0,0,5},
  {0,0,-2,10},{0,0,1,0},{0,0,2,0},{0,0,3,0},{0,0,4,0},{0,0,5,0},{0,0,10,-2},{1,1,1,1},
  {2,2,2,2},{3,3,3,3},{4,4,4,4},{5,5,5,5},{6,6,6,6},{1,1,0,0},{2,2,0,0},{3,3,0,0},
  {4,4,0,0},{0,0,1,1},{0,0,2,2},{0,0,3,3},{0,0,4,4}
};
Byte Ar0 [11][2]={{0x23,0x13},{0x19,0x15},{0x13,0x14},{0x10,0x16},{0x0D,0x17},
 {0x0A,0x7B},{0x07,0x18},{0x05,0x2C},{0x03,0x7C},{0x01,0x24},{0,0}};
Byte Ar1 [10][2]={{0x19,0x44},{0x13,0x3A},{0x0F,0x63},{0x0C,0x6D},{0x09,0x2A},
 {0x07,0x53},{0x05,0x37},{0x03,0x4E},{0x01,0x48},{0,0}};
Byte Ar2 [18][2]={{0x2C,0x66},{0x29,0x42},{0x26,0x39},{0x23,0x65},{0x20,0x68},
 {0x1D,0x6C},{0x1A,0x69},{0x17,0x6A},{0x14,0x67},{0x11,0x64},
 {0x0E,0x6B},{0x0B,0x36},{0x08,0x61},{0x06,0x47},{0x04,0x4C},
 {0x02,0x2B},{0x01,0x21},{0,0}};
Byte Ar3 [10][2]={{0x21,0x07},{0x1B,0x09},{0x15,0x08},{0x11,0x0A},{0x0D,0x0B},
 {0x09,0x0C},{0x06,0x26},{0x03,0x23},{0x01,0x80},{0,0}};
Byte Ar4 [ 9][2]={{0x1F,0x0D},{0x19,0x0F},{0x12,0x0E},{0x0E,0x10},{0x0A,0x11},
 {0x06,0x12},{0x03,0x27},{0x01,0x22},{0,0}};
Byte Ar5 [ 9][2]={{0x11,0x19},{0x0C,0x1B},{0x09,0x1A},{0x07,0x1C},{0x05,0x1D},
 {0x03,0x1E},{0x02,0x28},{0x01,0x1F},{0,0}};
Byte Ar67[11][2]={{0x1B,0x43},{0x15,0x46},{0x11,0x71},{0x0E,0x6E},{0x0B,0x45},
 {0x08,0x4D},{0x06,0x2D},{0x04,0x25},{0x02,0x5F},{0x01,0x5E},{0,0}};
Byte Ar8 [ 7][2]={{0x11,0x3B},{0x0C,0x62},{0x09,0x29},{0x06,0x38},{0x03,0x20},
 {0x01,0x5A},{0,0}};
Byte ArC [28][2]={{0x57,0x72},{0x53,0x73},{0x4F,0x74},{0x4B,0x75},{0x47,0x70},
 {0x43,0x5D},{0x3F,0x5C},{0x3B,0x5B},{0x37,0x4F},{0x33,0x50},
 {0x2F,0x51},{0x2B,0x52},{0x27,0x3C},{0x24,0x3D},{0x21,0x3E},
 {0x1E,0x6F},{0x1B,0x60},{0x18,0x49},{0x15,0x4A},{0x12,0x4B},
 {0x0F,0x7D},{0x0C,0x7E},{0x09,0x56},{0x07,0x57},{0x05,0x58},
 {0x03,0x59},{0x01,0x7F},{0,0}};

Byte ArtSlots[]={
// �����,+�����,+������,+����,+������, ������� ����� ...
  0x81,21,21,21,21, 0,2,4,5,7,
  0x82,0,0,0,0,     2,7,
  0x83,0,0,0,0,     6,6,
  0x84,3,3,2,2,     0,3,4,
  0x85,0,0,0,0,     8,8,8,8,
  0x86,16,16,16,16, 0,1,2,3,4,6,6,7,
  0x87,9,9,8,8,     0,4,5,
  0x88,0,0,0,0,     2,
  0x89,0,0,0,0,     8,8,
  0x8A,0,0,0,0,     8,8,
  0x8B,0,0,0,0,     1,2,
  0x8C,0,0,0,0,     1,6,6,
  0x99 // ���������
};
static char ME_Buf2[500000];


void DumpERMVars(char *Text,char *Text2)
{
  // 3.58
  #include "templ.h"
  int hout;
  ME_Buf2[0]=0;
  sprintf(&ME_Buf2[strlen(ME_Buf2)],"-----------------------\n%s\n-----------------------\n",Text);
  if(Text2!=0){
    sprintf(&ME_Buf2[strlen(ME_Buf2)],"-----Context-----\n%.200s.....\n-----------------\n",Text2);
  }
  sprintf(&ME_Buf2[strlen(ME_Buf2)],"COMMON VARS\n");
  sprintf(&ME_Buf2[strlen(ME_Buf2)],"f=%i\ng=%i\nh=%i\ni=%i\nj=%i\nk=%i\nl=%i\nm=%i\nn=%i\no=%i\np=%i\nq=%i\nr=%i\ns=%i\nt=%i\n",
    ERMVar[0],ERMVar[1],ERMVar[2],ERMVar[3],ERMVar[4],
    ERMVar[5],ERMVar[6],ERMVar[7],ERMVar[8],ERMVar[9],
    ERMVar[10],ERMVar[11],ERMVar[12],ERMVar[13],ERMVar[14]);
  int i,j;
  sprintf(&ME_Buf2[strlen(ME_Buf2)],"Common flags (1...1000)\n");
  for(i=0;i<1000;i++){ 
    if(ERMFlags[i]==0) continue;
    sprintf(&ME_Buf2[strlen(ME_Buf2)],"flag%i=%i\n",i+1,ERMFlags[i]); 
  }
  sprintf(&ME_Buf2[strlen(ME_Buf2)],"Common v vars (v1...v10000)\n",i);
  for(i=0;i<10000;i++){ 
    if(ERMVar2[i]==0) continue;
    sprintf(&ME_Buf2[strlen(ME_Buf2)],"v%i=%i\n",i+1,ERMVar2[i]); 
  }
  sprintf(&ME_Buf2[strlen(ME_Buf2)],"Hero's vars (w1...w200)\n",i);
  for(i=0;i<HERNUM;i++){
    hout=0;
    for(j=0;j<200;j++){ 
      if(ERMVarH[i][j]==0) continue;
      if(hout==0){ sprintf(&ME_Buf2[strlen(ME_Buf2)],"Hero#=%i\n",i); hout=1; }
      sprintf(&ME_Buf2[strlen(ME_Buf2)],"w%i=%i\n",j+1,ERMVarH[i][j]); 
    }
  }
  sprintf(&ME_Buf2[strlen(ME_Buf2)],"\nTRIGGER BASED VARS\n");
  sprintf(&ME_Buf2[strlen(ME_Buf2)],"Trigger y vars (y-1...y-100)\n");
  for(i=0;i<100;i++){ 
    if(ERMVarYT[i]==0) continue;
    sprintf(&ME_Buf2[strlen(ME_Buf2)],"y-%i=\"%i\"\n",i+1,ERMVarYT[i]); 
  }
  sprintf(&ME_Buf2[strlen(ME_Buf2)],"Trigger e vars (e-1...e-100)\n");
  for(i=0;i<100;i++){ 
    if(ERMVarFT[i]==0.0) continue;
    sprintf(&ME_Buf2[strlen(ME_Buf2)],"e-%i=\"%f\"\n",i+1,ERMVarFT[i]); 
  }

  sprintf(&ME_Buf2[strlen(ME_Buf2)],"\nFUNCTION BASED VARS\n");
  sprintf(&ME_Buf2[strlen(ME_Buf2)],"Parameters x vars (x1...x16)\n");
  for(i=0;i<16;i++){ 
    if(ERMVarX[i]==0) continue;
    sprintf(&ME_Buf2[strlen(ME_Buf2)],"x%i=\"%i\"\n",i+1,ERMVarX[i]); 
  }
  sprintf(&ME_Buf2[strlen(ME_Buf2)],"Local y vars (y1...y100)\n");
  for(i=0;i<100;i++){ 
    if(ERMVarY[i]==0) continue;
    sprintf(&ME_Buf2[strlen(ME_Buf2)],"y%i=\"%i\"\n",i+1,ERMVarY[i]); 
  }
  sprintf(&ME_Buf2[strlen(ME_Buf2)],"Local e vars (e1...e100)\n");
  for(i=0;i<100;i++){ 
    if(ERMVarF[i]==0.0) continue;
    sprintf(&ME_Buf2[strlen(ME_Buf2)],"e%i=\"%f\"\n",i+1,ERMVarF[i]); 
  }
  sprintf(&ME_Buf2[strlen(ME_Buf2)],"\nSTRING VARS\n");
  sprintf(&ME_Buf2[strlen(ME_Buf2)],"Common z vars (z1...z1000)\n");
  for(i=0;i<1000;i++){ 
    if(ERMString[i][0]==0) continue;
    sprintf(&ME_Buf2[strlen(ME_Buf2)],"z%i=\"%s\"\n",i+1,ERMString[i]); 
  }
  sprintf(&ME_Buf2[strlen(ME_Buf2)],"Local z vars (z-1...z-10)\n");
  for(i=0;i<10;i++){ 
    if(ERMLString[i][0]==0) continue;
    sprintf(&ME_Buf2[strlen(ME_Buf2)],"z-%i=\"%s\"\n",i+1,ERMLString[i]); 
  }
  SaveSetupState("WOGERMLOG.TXT",ME_Buf2,StrLen(ME_Buf2));
  RETURNV
}

Byte  HeapArray[PERMSIZE];
Byte  HeapArray2[HEAPSIZE];

int Apply(void *dp,char size,Mes *mp,char ind);
int NewMesMan(Mes *ms,_AMes_ *ap,int ind);
char *ERM2String(char *mes,int zstr,int *len);
int ApplyString(Mes *Mp,int ind,_AMes_ *amp);
void DelObjPos(Dword MixPos);
void ClearScriptFile(void);
void ResetCustomSettings(char *FName);
///////////////////////////
//void FUCall(int n);

static int YesERMFile;
static int ERMFile2Process;
static TxtFile ErmTxt;
static char ErmTxtName[1024];
static char LCT_s1[]="..\\MAPS\\";

static TxtFile ErmTXTScript;
static char LCT_s2[]="..\\DATA\\S\\";

char *GetERMtext(Mes *Mp,int ind,int staticonly){
  #include "templ.h"
  char *ret="";
  int vv;
  if(Mp->VarI[ind].Num!=0){ // ����������
    Apply(&vv,4,Mp,ind);
    if(staticonly){
      if(vv<1){ MError("\"Generic\"-wrong z var index (1...1000+)."); RETURN(ret) }
      if(vv>1000)   ret=StringSet::GetText(vv);
      else if(vv>0) ret=ERMString[vv-1];
    }else{
      if((vv<-10)||(vv==0)){ MError("\"Generic\"-wrong z var index (-10...-1,1...1000+)."); RETURN(ret) }
      if(vv>1000)   ret=ERM2String(StringSet::GetText(vv),1,0);
      else if(vv>0) ret=ERM2String(ERMString[vv-1],1,0);
      else          ret=ERM2String(ERMLString[-vv-1],1,0);
    }
  }else{           // �������� ��� �����
    if(staticonly){
      MError("\"!!DL:H\"-cannot use direct ERM text (z vars only)"); RETURN(ret)
    }else{
      ret=ERM2String(&Mp->m.s[Mp->i],0,&vv);
      Mp->i+=vv;
    }
  }
  RETURN(ret);
}

int CountERMScripts(void)
{
  #include "templ.h"
  int i,num;
  for(i=num=0;i<SCRIPTSNUM;i++){
    if(ERMScript[i].Used) num++;
  }
  RETURN(num)
}
int GetERMScripts(int ind)
{
  #include "templ.h"
  int i,num;
  for(i=num=0;i<SCRIPTSNUM;i++){
    if(ERMScript[i].Used){ if(num++==ind) RETURN(i) }
  }
  if(WoGType){ Message("�� ����� ERM ������.",1); }
  else{ Message("Cannot find ERM script.",1); }
  RETURN(0)
}


static char *ScriptNames[4]={"alibrary","awogify","script%03i","custom\\wcustom%02i"};

static char ScriptNameBuf[256];
char *GetScriptName(int ind){
  char *name;
  switch(ind){
    case 0: name=ScriptNames[0]; break;
    case 1: name=ScriptNames[1]; break;
    default:
      if(ind<1002){ // script
        sprintf(ScriptNameBuf,ScriptNames[2],ind-2);
        name=ScriptNameBuf;
      }else{ // custom
        sprintf(ScriptNameBuf,ScriptNames[3],ind-1002);
        name=ScriptNameBuf;
      }
  }
  return name;
}

static int _LoadERMScript(int Number,char *name,char *path)
{
  #include "templ.h"
  char  TxtName[1024];

  sprintf(TxtName,"%s%s.erm",path,name);
  if(Service_GetFileAttributes(&TxtName[3])==-1) RETURN(-1) // ��� ������ �����
  if(ErmTXTScript.fl!=0) UnloadTXT(&ErmTXTScript);
  if(Number==0){
    if(WoG==0){ // �� WoG
      if(WoGType){ Message("��� ��� ����� �� WoG, �� �� ����� WoG�����������.",1); }
      else{ Message("Since the map is not a WoG type, it will not be WoGified.",1); }
      RETURN(1)
    }
  }
  if(LoadTXT(TxtName,&ErmTXTScript)){
    if(WoGType){ Message("�� ��������� ������.",1); }
    else{ Message("Cannot load ERM file.",1); }
    RETURN(1) // ���-�� �� ���
  }
//   for(i=0;i<63;i++) ERMScript[Number].FileName[i]=TxtName[i];
  ERMScript[Number].Used=1;
  ERMScript[Number].Size=StrLen(ErmTXTScript.fl->Start[0]->Start[0]);
  if(ERMScript[Number].Size<=0){
    if(WoGType){ Message("������ ����� ERM ������� ����������.",1); }
    else{ Message("Size of ERM script file is negative or zero.",1); }
    ERMScript[Number].Used=0;
    RETURN(1)
  }
  ERMBody[Number]=(char *)Alloc(ERMScript[Number].Size);
  StrCopy(ERMBody[Number],ERMScript[Number].Size,ErmTXTScript.fl->Start[0]->Start[0]);
  RETURN(0)
}

static int _LoadERTScript(/*int Number,*/char *name,char *path)
{
  #include "templ.h"
  int   i,l;
  char *txt;
  char  TxtName[1024];

  sprintf(TxtName,"%s%s.ert",path,name);
  // loading strings now
//  TxtName[StrLen(TxtName)-1]='T';
  if(Service_GetFileAttributes(&TxtName[3])==-1) RETURN(-1) // ��� ������ �����
  if(ErmTXTScript.fl!=0) UnloadTXT(&ErmTXTScript);
  if(LoadTXT(TxtName,&ErmTXTScript)){
    if(WoGType){ Message("�� ��������� ���� ����� ��� �������.",1); }
    else{ Message("Cannot load Strings for ERM file.",1); }
    RETURN(1) // ���-�� �� ���
  }
  for(i=0;i<ErmTXTScript.sn;i++){
    if(a2i(ITxt(i,0,&ErmTXTScript))==0) continue;
    l=StrLen(ITxt(i,1,&ErmTXTScript));
    txt=(char *)Alloc(l+1);
    StrCopy(txt,l+1,ITxt(i,1,&ErmTXTScript));
    if(StringSet::Add(a2i(ITxt(i,0,&ErmTXTScript)),txt)) RETURN(1)
  }
  RETURN(0)
}

int LoadERMScript(int Number)
{
  #include "templ.h"
  int   ret;

//  ReadStrINI(Load2Path,MAX_PATH-1,"","Alternate_Script_Location","WoGification");
  char *name=GetScriptName(Number);
  ReadIntINI(&ret,0,name,"WoGification");
  if(ret!=0) RETURN(0) // do not load this script 

  ERMScript[Number].Used=0;
  ret=-1;
  if(Load2Path[0]!=0){ // ���� �������������� ����
    ret=_LoadERMScript(Number,name,Load2Path);
  }
  if(ret==-1){ // ��� ��� ����� (��� ����)
    ret=_LoadERMScript(Number,name,LCT_s2);
  }
  if(ret==-1) RETURN(0) // ��� ������ ����� ������
  if(ret==1) RETURN(1) // ������ ���������
  ret=-1;
  if(Load2Path[0]!=0){ // ���� �������������� ����
    ret=_LoadERTScript(/*Number,*/name,Load2Path);
  }
  if(ret==-1){ // ��� ��� ����� (��� ����)
    ret=_LoadERTScript(/*Number,*/name,LCT_s2);
  }
  if(ret==-1) RETURN(0) // ��� ������ ����� ������
  if(ret==1) RETURN(1) // ������ ���������
  RETURN(0)
}
/*
int FixedMapName(void)
{
  char *MapName;
  char  TxtName[1024];
  asm{
    mov   eax,BASE
    mov   eax,[eax]
    add   eax,0x1F6D9
    mov   MapName,eax
  }
  StrCopy(TxtName,1023,MapName);
  ToUpper(TxtName);
  if(StrCmp("ZUTORIAL",TxtName)) return 1;
  if(StrCmp("Z_-~-_",TxtName)) return 1;
  if(StrCmp("B_-~-_",TxtName)) return 1;
  if(StrCmp("G_-~-_",TxtName)) return 1;
  if(StrCmp("WOG_CAMP",TxtName)) return 1;
  if(StrCmp("CAVE OF GERFREX",TxtName)) return 1;
  return 0;
}
*/
int LoadERMTXT(int NEWload)
{
  #include "templ.h"
  int   i;
  char *MapName;
  char  TxtName[1024];

  if(NEWload){
    YesERMFile=0;
    ERMFile2Process=0;
//    ClearScriptFile();
//    for(i=0;i<SCRIPTSNUM;i++) LoadERMScript(i);
  }else{
    if(YesERMFile==0) RETURN(0)
  }
  if(NEWload){
    __asm{
      mov   eax,BASE
      mov   eax,[eax]
      add   eax,0x1F6D9
      mov   MapName,eax
    }
    StrCopy(TxtName,1023,MapName);
    ToUpper(TxtName);
    ClearScriptFile();
// 3.57f fix for WoGifiing wogify_... maps
    WoGSpecMap=0;
    if((TxtName[0]=='R'&&TxtName[1]=='A'&&TxtName[2]=='N'&&TxtName[3]=='D'&&
        TxtName[4]=='O'&&TxtName[5]=='M'&&TxtName[6]=='_'&&TxtName[7]=='M'&&
        TxtName[8]=='A'&&TxtName[9]=='P')||
       (TxtName[0]=='W'&&TxtName[1]=='O'&&TxtName[2]=='G'&&TxtName[3]=='I'&&
        TxtName[4]=='F'&&TxtName[5]=='Y'&&TxtName[6]=='_')) WoGSpecMap=1;
    if(WoGSpecMap||(PL_ApplyWoG>0)){
      ReadStrINI(Load2Path,MAX_PATH-1,"","Alternate_Script_Location","WoGification");
      for(i=0;i<SCRIPTSNUM;i++) if(LoadERMScript(i)) break;
    }
/*
    if((TxtName[0]=='R'&&TxtName[1]=='A'&&TxtName[2]=='N'&&TxtName[3]=='D'&&
        TxtName[4]=='O'&&TxtName[5]=='M'&&TxtName[6]=='_'&&TxtName[7]=='M'&&
        TxtName[8]=='A'&&TxtName[9]=='P')||
       (TxtName[0]=='W'&&TxtName[1]=='O'&&TxtName[2]=='G'&&TxtName[3]=='I'&&
        TxtName[4]=='F'&&TxtName[5]=='Y'&&TxtName[6]=='_')||
        (PL_ApplyWoG>0))
    {
      for(i=0;i<SCRIPTSNUM;i++) if(LoadERMScript(i)) break;
    }
*/
    StrCanc(TxtName,1023,LCT_s1,MapName);
    i=StrLen(TxtName);
    for(;i>0;i--) if(TxtName[i]=='.') break;
    i++; TxtName[i++]='E'; TxtName[i++]='R'; TxtName[i]='M';
    if(LoadFile16k(&TxtName[3],"rb")==0) RETURN(0) // �� ����� ��������� TXT - ���� ���
    if(ErmTxt.fl!=0) UnloadTXT(&ErmTxt);
    if(LoadTXT(TxtName,&ErmTxt)){
      if(WoGType){ Message("�� ��������� ERM ����.",1); }
      else{ Message("Cannot load ERM file.",1); }
      RETURN(1) // ���-�� �� ���
    }
    YesERMFile=1;
    ERMFile2Process=1;
    for(i=0;i<1024;i++) ErmTxtName[i]=TxtName[i];
  }else{
    for(i=0;i<1024;i++) TxtName[i]=ErmTxtName[i];
    YesERMFile=0;
    if(LoadTXT(TxtName,&ErmTxt)){
      if(WoGType){ Message("�� ��������� ERM ����.",1); }
      else{ Message("Cannot load ERM file.",1); }
      RETURN(1) // ���-�� �� ���
    }
    YesERMFile=1;
    ERMFile2Process=1;
  }
  RETURN(0)
}

static int TriggerBreak=0;
static int YVarInsideFunction=1; // default is OFF to check
int ERM_Function(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int i,j,v;
  int   _lYVarInsideFunction;
  int   OldX[16];
  int   OldY[100];
  float OldF[100];
  char OldString[10][512];
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
//  VarNum *vnp=(VarNum *)&sp->Pointer;
  switch(Cmd){
    case 'P': // ������� �������
      for(i=0;i<16;i++) { OldX[i]=ERMVarX[i]; }
      for(i=0;i<100;i++){ OldY[i]=ERMVarY[i]; }
      for(i=0;i<100;i++){ OldF[i]=ERMVarF[i]; }
      for(i=0;i<10;i++) for(j=0;j<512;j++) { OldString[i][j]=ERMLString[i][j]; }
      for(i=0;i<Num;i++){ ERMVarX[i]=Mp->n[i]; }
      for(i=0;i<100;i++){ ERMVarY[i]=0; }
      for(i=0;i<100;i++){ ERMVarF[i]=0; }
      v=GetVarVal(&sp->Par[0]);
      _lYVarInsideFunction=YVarInsideFunction;
      YVarInsideFunction=1;
      FUCall(v);
      YVarInsideFunction=_lYVarInsideFunction;
      // 3.58 return values
      // first restore y vars (and others)
      for(i=0;i<100;i++){ ERMVarY[i]=OldY[i]; }
      for(i=0;i<100;i++){ ERMVarF[i]=OldF[i]; }
      for(i=0;i<10;i++) for(j=0;j<512;j++) { ERMLString[i][j]=OldString[i][j]; }
      // now if used ?y, it will be stored correctly
      for(i=0;i<Num;i++){
        if(Mp->VarI[i].Check!=1) continue; // �� ?
        Apply(&ERMVarX[i],4,Mp,(char)i);
      }
      for(i=0;i<16;i++) { ERMVarX[i]=OldX[i]; }
      break;
    case 'D': // 3.58 distant call
      int vars[16];
      for(i=0;i<Num;i++){ vars[i]=Mp->n[i]; }
      SendCustomRequest(GetVarVal(&sp->Par[0]),vars,Num);
      break;
    case 'E': // �������� �������
      TriggerBreak=1;
      break;
    case 'C': // 3.58f check wrong Y var usege outside of trigger
      YVarInsideFunction=Mp->n[0];
      break;
    default: MError("\"!!FU\" - wrong command"); RETURN(0)
  }
  RETURN(1)
}
// call from a network
int Call_Function(int ind,int *var,int num){
  #include "templ.h"
  int i,j;
  int   _lYVarInsideFunction;
  int   OldX[16];
  int   OldY[100];
  float OldF[100];
  char OldString[10][512];
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  for(i=0;i<16;i++) { OldX[i]=ERMVarX[i]; }
  for(i=0;i<100;i++){ OldY[i]=ERMVarY[i]; }
  for(i=0;i<100;i++){ OldF[i]=ERMVarF[i]; }
  for(i=0;i<10;i++) for(j=0;j<512;j++) { OldString[i][j]=ERMLString[i][j]; }
  for(i=0;i<num;i++){ ERMVarX[i]=var[i]; }
  for(i=0;i<100;i++){ ERMVarY[i]=0; }
  for(i=0;i<100;i++){ ERMVarF[i]=0; }
  _lYVarInsideFunction=YVarInsideFunction;
  YVarInsideFunction=1;
  FUCall(ind);
  YVarInsideFunction=_lYVarInsideFunction;
  for(i=0;i<100;i++){ ERMVarY[i]=OldY[i]; }
  for(i=0;i<100;i++){ ERMVarF[i]=OldF[i]; }
  for(i=0;i<10;i++) for(j=0;j<512;j++) { ERMLString[i][j]=OldString[i][j]; }
  for(i=0;i<16;i++) { ERMVarX[i]=OldX[i]; }
  RETURN(1)
}

/*
struct Cycle{
  int From  : 11; //+-1024
  int To    : 11; //+-1024
  int Step  : 10; //+-512
};
*/
int ReParseVal(VarNum *vn)
{
  #include "templ.h"
  int vi=vn->Num;
  if(vn->IType!=0){// ���� ���� ��������������
    switch(vn->IType){
      case 2: vi=ERMVar[vn->Num-1]; break; // f...t
      case 3: vi=ERMVar2[vn->Num-1]; break; // v
      case 4: vi=ERMVarH[ERMW][vn->Num-1]; break; // w
      case 5: vi=ERMVarX[vn->Num-1]; break; // x
      case 6:
        if(vi<0) vi=ERMVarYT[-vn->Num-1]; // y
        else vi=ERMVarY[vn->Num-1]; 
      break; // y
////                    case 8: // a
////                      if(CheckScope()){ *n=0; goto _over; }
////                      *n=ERMScope->Var[vi-1];
////                      break;
      default: MError("\"ReParseVal\"-wrong indexing var type (f...t,v,w,x,y)."); RETURN(0)
    }
  }
  switch(vn->Type){
    case 3: vi=ERMVar2[vi-1]; break; // v
    case 4: vi=ERMVarH[ERMW][vi-1]; break; // w
    case 5: vi=ERMVarX[vi-1]; break; // x
    case 6:
      if(vi<0) vi=ERMVarYT[-vi-1];
      else     vi=ERMVarY[vi-1];
      break; // y
    case 7: vi=vi; break; // z
    case 8:
      if(vi<0)  vi=(int)ERMVarFT[-vi-1];
      else      vi=(int)ERMVarF[vi-1];
      break; // e
////                  case 8: // a
////                    if(CheckScope()){ *n=0; goto _over; }
////                    *n=ERMScope->Var[vi-1];
////                    break;
////                  case 9: // b
////                    if(CheckScope()){ *n=0; goto _over; }
////                    *n=-vi;
////                    break;
//                  default: MError("\"GetNum\"-wrong var type (v,w,x,y,z)."); goto _over;
  }
  RETURN(vi)
}

int ERM_Do(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int i,v,from,to,step;
//  Cycle *cp=(Cycle *)&sp->Pointer[1];
  int   _lYVarInsideFunction;
  int   OldX[16];
  int   OldY[100];
  float OldF[100];
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  switch(Cmd){
    case 'P': // ������� �������
//      from=cp->From;
//      to=cp->To;
//      step=cp->Step;
      from=GetVarVal(&sp->Par[1]);
      to=GetVarVal(&sp->Par[2]);
      step=GetVarVal(&sp->Par[3]);
      for(i=0;i<16;i++) { OldX[i]=ERMVarX[i]; }
      for(i=0;i<100;i++){ OldY[i]=ERMVarY[i]; }
      for(i=0;i<100;i++){ OldF[i]=ERMVarF[i]; }
      for(i=0;i<Num;i++){ ERMVarX[i]=Mp->n[i]; }
      for(i=0;i<100;i++){ ERMVarY[i]=0; }
      for(i=0;i<100;i++){ ERMVarF[i]=0; }
      for(ERMVarX[15]=from;ERMVarX[15]<=to;ERMVarX[15]+=step){
//      ERMVarX[15]=j; // �������� ����������
        // 3.58 return values
        for(i=0;i<Num;i++){
          if(Mp->VarI[i].Check!=1) continue; // �� ?
          ERMVarX[i]=Mp->n[i];
        }
        for(i=0;i<Num;i++){
          if(Mp->VarI[i].Check!=2) continue; // �� =
//          Mp->VarI[i].Check=0;
//          Apply(&ERMVarX[i],4,Mp,(char)i);
//          Mp->VarI[i].Check=2;
          ERMVarX[i]=ReParseVal(&Mp->VarI[i]);
        }
        v=GetVarVal(&sp->Par[0]);
        _lYVarInsideFunction=YVarInsideFunction;
        YVarInsideFunction=1;
        FUCall(v);
        YVarInsideFunction=_lYVarInsideFunction;
        for(i=0;i<Num;i++){
          if(Mp->VarI[i].Check!=1) continue; // �� ?
          Apply(&ERMVarX[i],4,Mp,(char)i);
        }
      }
      for(i=0;i<100;i++){ ERMVarY[i]=OldY[i]; }
      for(i=0;i<100;i++){ ERMVarF[i]=OldF[i]; }
      // we need to repeat because we restored many of them a line above
      for(i=0;i<Num;i++){
        if(Mp->VarI[i].Check!=1) continue; // �� ?
        Apply(&ERMVarX[i],4,Mp,(char)i);
      }
      for(i=0;i<16;i++) { ERMVarX[i]=OldX[i]; }
      break;
    default: MError("\"!!DO\" - wrong command"); RETURN(0)
  }
  RETURN(1)
}

int GetVarValIndex(VarNum *vnp)
{
  #include "templ.h"
  int vi;
  vi=vnp->Num;
  switch(vnp->IType){
    case 0: break;
    case 2: // f...t
      if((vi<1)||(vi>15)){ MError("Var is out of set (f...t) as index in GetVar."); RETURN(0) }
      vi=ERMVar[vi-1];
      break;
    case 3: // v1...1000
      if((vi<1)||(vi>10000)){ MError("Var is out of set (v1...v10000) as index in GetVar."); RETURN(0) }
      vi=ERMVar2[vi-1];
      break;
    case 4: // w1...100
      if((vi<1)||(vi>200)){ MError("Var is out of set (w1...w200) as index in GetVar."); RETURN(0) }
      vi=ERMVarH[ERMW][vi-1];
      break;
    case 5: // x1...16
      if((vi<1)||(vi>16)){ MError("Var is out of set (x1...x16) as index in GetVar."); RETURN(0) }
      vi=ERMVarX[vi-1];
      break;
    case 6: // y1...100
      if((vi>100)||(vi==0)||(vi<-100)){ MError("Var is out of set (y-100...y-1,y1...y100) as index in GetVarValIndex."); RETURN(0) }
      if(vi<0) vi=ERMVarYT[-vi-1];
      else     vi=ERMVarY[vi-1];
      break;
    default: MError("Incorrect index in GetVar."); RETURN(0)
  }
  RETURN(vi)
}

int GetVarVal(VarNum *vnp)
{
  #include "templ.h"
  int vi;
  vi=vnp->Num;
  switch(vnp->IType){
    case 0: break;
    case 2: // f...t
      if((vi<1)||(vi>15)){ MError("Var is out of set (f...t) as index in GetVar."); RETURN(0) }
      vi=ERMVar[vi-1];
      break;
    case 3: // v1...1000
      if((vi<1)||(vi>10000)){ MError("Var is out of set (v1...v10000) as index in GetVar."); RETURN(0) }
      vi=ERMVar2[vi-1];
      break;
    case 4: // w1...100
      if((vi<1)||(vi>200)){ MError("Var is out of set (w1...w200) as index in GetVar."); RETURN(0) }
      vi=ERMVarH[ERMW][vi-1];
      break;
    case 5: // x1...16
      if((vi<1)||(vi>16)){ MError("Var is out of set (x1...x16) as index in GetVar."); RETURN(0) }
      vi=ERMVarX[vi-1];
      break;
    case 6: // y1...100
//      if((vi<1)||(vi>100)){ MError("Var is out of set (y1...y100) as index in GetVar."); RETURN(0) }
//      vi=ERMVarY[vi-1];
      if((vi>100)||(vi==0)||(vi<-100)){ MError("Var is out of set (y-100...y-1,y1...y100) as index in GetVarVal."); RETURN(0) }
      if(vi<0) vi=ERMVarYT[-vi-1];
      else     vi=ERMVarY[vi-1];
      break;
////    case 8: // a1...1000
////      if((vi<1)||(vi>1000)){ MError("Var is out of set (a1...v1000) as index in GetVar."); return 0; }
////      if(CheckScope()) return 0;
////      vi=ERMScope->Var[vi-1];
////      break;
    default: MError("Incorrect index in GetVar."); RETURN(0)
  }
  switch(vnp->Type){
    case 0: // �����
      break;
    case 2: // f...t
      if((vi<1)||(vi>15)){ MError("Var is out of set (f...t) in GetVar."); RETURN(0) }
      vi=ERMVar[vi-1];
      break;
    case 3: // v1...1000
      if((vi<1)||(vi>10000)){ MError("Var is out of set (v1...v10000) in GetVar."); RETURN(0) }
      vi=ERMVar2[vi-1];
      break;
    case 4: // w1...100
      if((vi<1)||(vi>200)){ MError("Var is out of set (w1...w200) in GetVar."); RETURN(0) }
      vi=ERMVarH[ERMW][vi-1];
      break;
    case 5: // x1...16
      if((vi<1)||(vi>16)){ MError("Var is out of set (x1...x16) in GetVar."); RETURN(0) }
      vi=ERMVarX[vi-1];
      break;
    case 6: // y1...100
//      if((vi<1)||(vi>100)){ MError("Var is out of set (y1...y100) in GetVar."); RETURN(0) }
//      vi=ERMVarY[vi-1];
      if((vi>100)||(vi==0)||(vi<-100)){ MError("Var is out of set (y-100...y-1,y1...y100) as index in GetVarVal."); RETURN(0) }
      if(vi<0) vi=ERMVarYT[-vi-1];
      else     vi=ERMVarY[vi-1];
      break;
    case 7: // z1...500
      if((vi<-10)||(vi==0)||(vi>1000)){ MError("Var is out of set (z-10...z-1,z1...z1000) in GetVar."); RETURN(0) }
      // ���������� ��� ������
      break;
    case 8: // e1...100
//      if((vi<1)||(vi>100)){ MError("Var is out of set (e1...e100) as index in GetVar."); RETURN(0) }
//      vi=ERMVarF[vi-1];
      if((vi<-100)||(vi==0)||(vi>100)){ MError("Var is out of set (e-100...e-1,e1...e100)."); RETURN(0) }
      if(vi<0) vi=(int)ERMVarFT[-vi-1];
      else     vi=(int)ERMVarF[vi-1];
      break;
////    case 8: // a1...1000
////      if((vi<1)||(vi>1000)){ MError("Var is out of set (a1...a1000) in GetVar."); return 0; }
////      if(CheckScope()) return 0;
////      vi=ERMScope->Var[vi-1];
////      break;
////    case 9: // b1...500
////      if((vi<1)||(vi>500)){ MError("Var is out of set (b1...b500) in GetVar."); return 0; }
////      vi=-vi;
////      // ���������� - ��� ������
////      break;
    default: MError("Incorrect Var in GetVar."); RETURN(0)
  }
  RETURN(vi)
}
int SetVarVal(VarNum *vnp,int Val)
{
  #include "templ.h"
  char *txt;
  int vi;
  vi=vnp->Num;
  switch(vnp->IType){
    case 0: break;
    case 2: // f...t
      if((vi<1)||(vi>15)){ MError("Var is out of set (f...t) as index in SetVar."); RETURN(-1) }
      vi=ERMVar[vi-1];
      break;
    case 3: // v1...1000
      if((vi<1)||(vi>10000)){ MError("Var is out of set (v1...v10000) as index in SetVar."); RETURN(0) }
      vi=ERMVar2[vi-1];
      break;
    case 4: // w1...100
      if((vi<1)||(vi>200)){ MError("Var is out of set (w1...w200) as index in SetVar."); RETURN(0) }
      vi=ERMVarH[ERMW][vi-1];
      break;
    case 5: // x1...16
      if((vi<1)||(vi>16)){ MError("Var is out of set (x1...x16) as index in SetVar."); RETURN(0) }
      vi=ERMVarX[vi-1];
      break;
    case 6: // y1...100
//      if((vi<1)||(vi>100)){ MError("Var is out of set (y1...y100) as index in SetVar."); RETURN(0) }
//      vi=ERMVarY[vi-1];
      if((vi>100)||(vi==0)||(vi<-100)){ MError("Var is out of set (y-100...y-1,y1...y100) as index in SetVarVal."); RETURN(0) }
      if(vi<0) vi=ERMVarYT[-vi-1];
      else     vi=ERMVarY[vi-1];
      break;
////    case 8: // a1...1000
////      if((vi<1)||(vi>1000)){ MError("Var is out of set (a1...v1000) as index in GetVar."); return 0; }
////      if(CheckScope()) return 0;
////      vi=ERMScope->Var[vi-1];
////      break;
    default: MError("Incorrect Var as index in SetVar."); RETURN(0)
  }
  switch(vnp->Type){
    case 2: // f...t
      if((vi<1)||(vi>15)){ MError("Var is out of set (f...t) in SetVar."); RETURN(-1) }
      ERMVar[vi-1]=Val;
      break;
    case 3: // v1...1000
      if((vi<1)||(vi>10000)){ MError("Var is out of set (v1...v10000) in SetVar."); RETURN(-1) }
      ERMVar2[vi-1]=Val;
      break;
    case 4: // w1...100
      if((vi<1)||(vi>200)){ MError("Var is out of set (w1...w200) in SetVar."); RETURN(0) }
      ERMVarH[ERMW][vi-1]=Val;
      break;
    case 5: // x1...16
      if((vi<1)||(vi>16)){ MError("Var is out of set (x1...x16) in SetVar."); RETURN(0) }
      ERMVarX[vi-1]=Val;
      break;
    case 6: // y1...100
//      if((vi<1)||(vi>100)){ MError("Var is out of set (y1...y100) in SetVar."); RETURN(0) }
//      ERMVarY[vi-1]=Val;
      if((vi>100)||(vi==0)||(vi<-100)){ MError("Var is out of set (y-100...y-1,y1...y100) as index in SetVarVal."); RETURN(0) }
      if(vi<0) ERMVarYT[-vi-1]=Val;
      else{ if(YVarInsideFunction==0) GEr.WrongYVarUsage();  ERMVarY[vi-1]=Val; }
      break;
    case 7: // z1...500
      if((vi<-10)||(vi==0)||(vi>1000)){ MError("Var is out of set (z-10...z-1,z1...z1000) as destination in SetVar."); RETURN(0) }
      if((Val<-10)||(Val==0)){ MError("Var z is out of set (-10...-1,1...1000) as source in SetVar."); RETURN(0) }
//      if(Val>1000) txt=StringSet::GetText(Val);//ERM2String(StringSet::GetText(val),1,0);
      if(Val>1000) txt=ERM2String(StringSet::GetText(Val),1,0);
      else if(Val<0) txt=ERMLString[-Val-1];
      else txt=ERMString[Val-1];
      if(vi>0) StrCopy(ERMString[vi-1],512,txt);
      else     StrCopy(ERMLString[-vi-1],512,txt);
      break;
    case 8: // e1...100
//      if((vi<1)||(vi>100)){ MError("Var is out of set (e1...e100) as index in SetVar."); RETURN(0) }
//      ERMVarF[vi-1]=Val;
      if((vi<-100)||(vi==0)||(vi>100)){ MError("Var is out of set (e-100...e-1,e1...e100)."); RETURN(0) }
      if(vi<0) ERMVarFT[-vi-1]=(float)Val;
      else     ERMVarF[vi-1]=(float)Val;
      break;
////      if((Val<-500)||(Val>500)){ MError("Var z or b is out of set (1...500) as source in SetVar."); return 0; }
////      if(Val<0){ // b
////        if(CheckScope()) return 0;
////        StrCopy(ERMString[vi-1],512,ERMScope->String[-Val-1]);
////      }else{ // z
////        StrCopy(ERMString[vi-1],512,ERMString[Val-1]);
////      }
////      break;
////    case 8: // a1...1000
////      if((vi<1)||(vi>1000)){ MError("Var is out of set (a1...a1000) in SetVar."); return -1; }
////      if(CheckScope()) return 0;
////      ERMScope->Var[vi-1]=Val;
////      break;
////    case 9: // b1...500
////      if((vi<1)||(vi>500)){ MError("Var is out of set (b1...z500) as destination in SetVar."); return 0; }
////      if((Val<-500)||(Val>500)){ MError("Var z or b is out of set (1...500) as source in SetVar."); return 0; }
////      if(Val<0){ // b
////        if(CheckScope()) return 0;
////        StrCopy(ERMScope->String[vi-1],512,ERMScope->String[-Val-1]);
////      }else{ // z
////        StrCopy(ERMScope->String[vi-1],512,ERMString[Val-1]);
////      }
////      break;
    case 0: // �����
    default: MError("Incorrect Var SetVar."); RETURN(-1)
  }
  RETURN(0)
}

float GetVarValF(VarNum *vnp)
{
  #include "templ.h"
  int   vi;
  float vf;
  vi=vnp->Num;
  switch(vnp->IType){
    case 0: break;
    case 2: // f...t
      if((vi<1)||(vi>15)){ MError("Var is out of set (f...t) as index in GetVar."); RETURN(0) }
      vi=ERMVar[vi-1];
      break;
    case 3: // v1...1000
      if((vi<1)||(vi>10000)){ MError("Var is out of set (v1...v10000) as index in GetVar."); RETURN(0) }
      vi=ERMVar2[vi-1];
      break;
    case 4: // w1...100
      if((vi<1)||(vi>200)){ MError("Var is out of set (w1...w200) as index in GetVar."); RETURN(0) }
      vi=ERMVarH[ERMW][vi-1];
      break;
    case 5: // x1...16
      if((vi<1)||(vi>16)){ MError("Var is out of set (x1...x16) as index in GetVar."); RETURN(0) }
      vi=ERMVarX[vi-1];
      break;
    case 6: // y1...100
//      if((vi<1)||(vi>100)){ MError("Var is out of set (y1...y100) as index in GetVar."); RETURN(0) }
//      vi=ERMVarY[vi-1];
      if((vi>100)||(vi==0)||(vi<-100)){ MError("Var is out of set (y-100...y-1,y1...y100) as index in GetVarValF."); RETURN(0) }
      if(vi<0) vi=ERMVarYT[-vi-1];
      else     vi=ERMVarY[vi-1];
      break;
////    case 8: // a1...1000
////      if((vi<1)||(vi>1000)){ MError("Var is out of set (a1...v1000) as index in GetVar."); return 0; }
////      if(CheckScope()) return 0;
////      vi=ERMScope->Var[vi-1];
////      break;
    default: MError("Incorrect index in GetVar."); RETURN(0)
  }
  vf=(float)vnp->Num;
  switch(vnp->Type){
    case 0: // �����
      break;
    case 2: // f...t
      if((vi<1)||(vi>15)){ MError("Var is out of set (f...t) in GetVar."); RETURN(0) }
      vf=(float)ERMVar[vi-1];
      break;
    case 3: // v1...1000
      if((vi<1)||(vi>10000)){ MError("Var is out of set (v1...v10000) in GetVar."); RETURN(0) }
      vf=(float)ERMVar2[vi-1];
      break;
    case 4: // w1...100
      if((vi<1)||(vi>200)){ MError("Var is out of set (w1...w200) in GetVar."); RETURN(0) }
      vf=(float)ERMVarH[ERMW][vi-1];
      break;
    case 5: // x1...16
      if((vi<1)||(vi>16)){ MError("Var is out of set (x1...x16) in GetVar."); RETURN(0) }
      vf=(float)ERMVarX[vi-1];
      break;
    case 6: // y1...100
//      if((vi<1)||(vi>100)){ MError("Var is out of set (y1...y100) in GetVar."); RETURN(0) }
//      vf=ERMVarY[vi-1];
      if((vi>100)||(vi==0)||(vi<-100)){ MError("Var is out of set (y-100...y-1,y1...y100) as index in GetVarValF."); RETURN(0) }
      if(vi<0) vf=(float)ERMVarYT[-vi-1];
      else     vf=(float)ERMVarY[vi-1];
      break;
    case 7: // z1...500
      if((vi<-10)||(vi==0)||(vi>1000)){ MError("Var is out of set (z-10...z-1,z1...z1000) in GetVar."); RETURN(0) }
      vf=(float)vi;
      // ���������� ��� ������
      break;
    case 8: // e1...100
//      if((vi<1)||(vi>100)){ MError("Var is out of set (e1...e100) as index in GetVar."); RETURN(0) }
//      vf=ERMVarF[vi-1];
      if((vi<-100)||(vi==0)||(vi>100)){ MError("Var is out of set (e-100...e-1,e1...e100)."); RETURN(0) }
      if(vi<0) vf=ERMVarFT[-vi-1];
      else     vf=ERMVarF[vi-1];
      break;
////    case 8: // a1...1000
////      if((vi<1)||(vi>1000)){ MError("Var is out of set (a1...a1000) in GetVar."); return 0; }
////      if(CheckScope()) return 0;
////      vi=ERMScope->Var[vi-1];
////      break;
////    case 9: // b1...500
////      if((vi<1)||(vi>500)){ MError("Var is out of set (b1...b500) in GetVar."); return 0; }
////      vi=-vi;
////      // ���������� - ��� ������
////      break;
    default: MError("Incorrect Var in GetVar."); RETURN(0)
  }
  RETURN(vf)
}
int SetVarValF(VarNum *vnp,float Val)
{
  #include "templ.h"
  int vi,ValI=(int)Val;
  vi=vnp->Num;
  switch(vnp->IType){
    case 0: break;
    case 2: // f...t
      if((vi<1)||(vi>15)){ MError("Var is out of set (f...t) as index in SetVar."); RETURN(-1) }
      vi=ERMVar[vi-1];
      break;
    case 3: // v1...1000
      if((vi<1)||(vi>10000)){ MError("Var is out of set (v1...v10000) as index in SetVar."); RETURN(0) }
      vi=ERMVar2[vi-1];
      break;
    case 4: // w1...100
      if((vi<1)||(vi>200)){ MError("Var is out of set (w1...w200) as index in SetVar."); RETURN(0) }
      vi=ERMVarH[ERMW][vi-1];
      break;
    case 5: // x1...16
      if((vi<1)||(vi>16)){ MError("Var is out of set (x1...x16) as index in SetVar."); RETURN(0) }
      vi=ERMVarX[vi-1];
      break;
    case 6: // y1...100
//      if((vi<1)||(vi>100)){ MError("Var is out of set (y1...y100) as index in SetVar."); RETURN(0) }
//      vi=ERMVarY[vi-1];
      if((vi>100)||(vi==0)||(vi<-100)){ MError("Var is out of set (y-100...y-1,y1...y100) as index in SetVarValF."); RETURN(0) }
      if(vi<0) vi=ERMVarYT[-vi-1];
      else     vi=ERMVarY[vi-1];
      break;
////    case 8: // a1...1000
////      if((vi<1)||(vi>1000)){ MError("Var is out of set (a1...v1000) as index in GetVar."); return 0; }
////      if(CheckScope()) return 0;
////      vi=ERMScope->Var[vi-1];
////      break;
    default: MError("Incorrect Var as index in SetVar."); RETURN(0)
  }
  switch(vnp->Type){
    case 2: // f...t
      if((vi<1)||(vi>15)){ MError("Var is out of set (f...t) in SetVar."); RETURN(-1) }
      ERMVar[vi-1]=ValI;
      break;
    case 3: // v1...1000
      if((vi<1)||(vi>10000)){ MError("Var is out of set (v1...v10000) in SetVar."); RETURN(-1) }
      ERMVar2[vi-1]=ValI;
      break;
    case 4: // w1...100
      if((vi<1)||(vi>200)){ MError("Var is out of set (w1...w200) in SetVar."); RETURN(0) }
      ERMVarH[ERMW][vi-1]=ValI;
      break;
    case 5: // x1...16
      if((vi<1)||(vi>16)){ MError("Var is out of set (x1...x16) in SetVar."); RETURN(0) }
      ERMVarX[vi-1]=ValI;
      break;
    case 6: // y1...100
//      if((vi<1)||(vi>100)){ MError("Var is out of set (y1...y100) in SetVar."); RETURN(0) }
//      ERMVarY[vi-1]=ValI;
      if((vi>100)||(vi==0)||(vi<-100)){ MError("Var is out of set (y-100...y-1,y1...y100) as index in SetVarValF."); RETURN(0) }
      if(vi<0) ERMVarYT[-vi-1]=ValI;
      else{ if(YVarInsideFunction==0) GEr.WrongYVarUsage(); ERMVarY[vi-1]=ValI; }
      break;
    case 7: // z1...500
      if((vi<-10)||(vi==0)||(vi>1000)){ MError("Var is out of set (z-10...z-1,z1...z1000) as destination in SetVar."); RETURN(0) }
      if((ValI<-10)||(ValI==0)||(ValI>1000)){ MError("Var z is out of set (-10...-1,1...1000) as source in SetVar."); RETURN(0) }
      if(vi>0){
        if(ValI>0) StrCopy(ERMString[vi-1],512,ERMString[ValI-1]);
        else      StrCopy(ERMString[vi-1],512,ERMLString[-ValI-1]);
      }else{
        if(Val>0) StrCopy(ERMLString[-vi-1],512,ERMString[ValI-1]);
        else      StrCopy(ERMLString[-vi-1],512,ERMLString[-ValI-1]);
      }
      break;
    case 8: // e1...100
//      if((vi<1)||(vi>100)){ MError("Var is out of set (e1...e100) as index in SetVar."); RETURN(0) }
//      ERMVarF[vi-1]=Val;
      if((vi<-100)||(vi==0)||(vi>100)){ MError("Var is out of set (e-100...e-1,e1...e100)."); RETURN(0) }
      if(vi<0) ERMVarFT[-vi-1]=Val;
      else     ERMVarF[vi-1]=Val;
      break;
    case 0: // �����
    default: MError("Incorrect Var SetVar."); RETURN(-1)
  }
  RETURN(0)
}
////////////////////////////////////
// �������� �� ����
static int SW_Set;
void StepWater(int x,int y,int l)
{
  #include "templ.h"
  _MapItem_ *MIp;
  MIp=GetMapItem(x,y,l);
  if(SW_Set){
    MIp->Land=4; // ������
    PlaceObject(x,y,l,208,1,208,1,-1);
  }else{
//    DelObject(x,y,l); // �� �������� - ������ ���, ��� �� ���� ������
    DelFirstObjectPic(x,y,l);
    MIp->Land=8; // ����
  }
  RETURNV
}

void PathOverWater(int x1,int y1,int x2,int y2,int l)
{
  #include "templ.h"
  MakeLine(x1,y1,x2,y2,l,StepWater);
  RETURNV
}
////////////////////////////////////
int CheckPlace4Hero(_MapItem_ *mip,Dword **stp)
{
  #include "templ.h"
  int tp=mip->OType;
  if(tp==0x22){ // ����� ����� �� �������
    int v=*(int *)mip;
    _Hero_ *hp=GetHeroStr(v);
    tp=hp->PlOType;
    if(stp!=0) *stp=&hp->PlSetUp;
  }
  RETURN(tp)
}

int IsObjectType(_MapItem_ *mip,int t,int st)
{
  #include "templ.h"
  int stp=mip->OSType,tp=mip->OType;
  Byte at=mip->Attrib;
  if(tp==0x22){ // ����� ����� �� �������
    int v=*(int *)mip;
    _Hero_ *hp=GetHeroStr(v);
    tp=hp->PlOType;
//    stp=hp->PlOSType;
//    at=(Byte)(hp->Pl0Cflag>>8);
  }
  if(tp==t){
    if(at&0x10){
      if(st==-1){ RETURN(1) }
      else{ if(stp==st){ RETURN(1) } }
    }else{ // 3.58f Pleced Events fix
      if(tp==26){ // local event
        if(st==-1){ RETURN(1) }
        else{ if(stp==st){ RETURN(1) } }
      }
    }
  }
  RETURN(0)
}
int CalcObjects(int t,int st)
{
  #include "templ.h"
  int x,y,l,n,v,v2;
  _MapItem_ *mp;
  n=0; v=GetMapSize(); v2=GetMapLevels();
  for(l=0;l<=v2;l++){
    for(y=0;y<v;y++){
      for(x=0;x<v;x++){
        mp=GetMapItem(x,y,l);
        if(IsObjectType(mp,t,st)) ++n;
/*
        if(mp->OType==t){
          if(mp->Attrib&0x10){
            if(st==-1){ ++n; }
            else{ if(mp->OSType==st){ ++n; } }
          }
        }
*/
      }
    }
  }
  RETURN(n)
}
int FindObjects(int t,int st,int i,int *xv,int *yv,int *lv)
{
  #include "templ.h"
  int x,y,l,n,m,v,v2;
  _MapItem_ *mp/*,*mp0*/;
  m=CalcObjects(t,st);
  if(m==0) RETURN(-1)
  v=GetMapSize(); v2=GetMapLevels();
  n=0;
//  mp0=GetMapItem(0,0,0); // 3.58f 
  for(l=0;l<=v2;l++){
    for(y=0;y<v;y++){
      for(x=0;x<v;x++){
        mp=GetMapItem(x,y,l);
//        mp=&mp0[x+(y+l*v)*v];
        if(IsObjectType(mp,t,st)==0) continue;
/*
        if(mp->OType==t){
          if(mp->Attrib&0x10){
            if(st==-1){ ++n; }
            else{ if(mp->OSType==st){ ++n; } }
          }
        }
*/
        ++n;
        if(n>m) RETURN(-1)
        if(n==i){
          *xv=x; *yv=y; *lv=l;
          RETURN(0)
        }
      }
    }
  }
  RETURN(-1)
}
int FindNextObjects(int t,int st,int *xv,int *yv,int *lv,int direction)
{
  #include "templ.h"
  int x,y,l/*,m*/,v,v2,fl=0;
  _MapItem_ *mp,*mp0;
//  m=CalcObjects(t,st);
//  if(m==0) RETURN(-1)
  v=GetMapSize(); v2=GetMapLevels();
  mp0=GetMapItem(0,0,0); // 3.58f
  int sx,sy,sl;
  if(*xv==-1){ sx=0; sy=0; sl=0; } // serch from start
  else if(*xv==-2){ sx=v-1; sy=v-1; sl=v2; } // search from end
  else { 
    sx=*xv; sy=*yv; sl=*lv; 
    if(direction==-2) --sx; else ++sx;
  }
  
  if(direction==-2){ //backward
    for(l=v2;l>=0;l--){
      for(y=v-1;y>=0;y--){
        for(x=v-1;x>=0;x--){
          if(fl==0){
            x=sx; y=sy;l=sl;
            if(x<0){ --y; x=v-1; }
            if(y<0){ --l; y=v-1; }
            if(l<0){ RETURN(-1) }
            fl=1;
          }
          mp=&mp0[x+(y+l*v)*v];
          if(IsObjectType(mp,t,st)==0) continue;
          *xv=x; *yv=y; *lv=l;
          RETURN(0)
        }
      }
    }
  }else{ // forward
    for(l=0;l<=v2;l++){
      for(y=0;y<v;y++){
        for(x=0;x<v;x++){
          if(fl==0){
            x=sx; y=sy;l=sl;
            if(x>=v){ ++y; x=0; }
            if(y>=v){ ++l; y=0; }
            if(l>v2){ RETURN(-1) }
            fl=1;
          }
          mp=&mp0[x+(y+l*v)*v];
          if(IsObjectType(mp,t,st)==0) continue;
          *xv=x; *yv=y; *lv=l;
          RETURN(0)
        }
      }
    }
  }
  RETURN(-1)
}

void ClearVarUsedList(void)
{
  #include "templ.h"
  int i;
  for(i=0;i<20;i++)    ERMVarUsed[i]=0;
  for(i=0;i<10000;i++) ERMVar2Used[i]=0;
  for(i=0;i<200;i++)   ERMVarHUsed[i]=0;
  for(i=0;i<1000;i++)  ERMStringUsed[i]=0;
  for(i=0;i<1000;i++)  ERMFlagsUsed[i]=0;
  for(i=0;i<30000;i++) ERMFunUsed[i]=0;
  for(i=0;i<100;i++)   ERMTimerUsed[i]=0;
  RETURNV
}
void StartVarUsed(void){ ERMVarUsedStore=1; }
void StopVarUsed(void){ ERMVarUsedStore=0; }

void StartDblVarUsed(void){ ERMVarCheck4DblStore=1; }
void StopDblVarUsed(void){ ERMVarCheck4DblStore=0; }

char VarUsedLog[300000]; // 300 kb
void WriteVarUsed(void)
{
  #include "templ.h"
  int i,len;
  char *cp=VarUsedLog;
  char buf[128];

  StrCopy(cp,64,"Common rules for cross-reverence:\r\n - used in both parts [*].\r\n"); cp+=63;
  StrCopy(cp,109,"Common rules for Flags, v,w,z vars:\r\n - used as parameter [p];\r\n - in & section [&];\r\n - in | section [|].\r\n"); cp+=108;
  StrCopy(cp,55,"Single letter variables used in the left part [f...t]:"); cp+=54;
  *cp++=0x0D; *cp++=0x0A;
  for(i=0;i<20;i++){
    if(ERMVarUsed[i]==0) continue;
    *cp++=(char)('f'+i); *cp++=' ';
    if(ERMVarUsed[i]&1) *cp++='p';
    if(ERMVarUsed[i]&2) *cp++='&';
    if(ERMVarUsed[i]&4) *cp++='|';
    if(ERMVarUsed[i]&0x40){ *cp++=' '; *cp++='*'; }
    *cp++=0x0D; *cp++=0x0A;
  }
  StrCopy(cp,40,"Flags used in the left part [1...1000]:"); cp+=39;
  *cp++=0x0D; *cp++=0x0A;
  for(i=0;i<1000;i++){
    if(ERMFlagsUsed[i]==0) continue;
    len=i2a(i+1,buf); buf[len]=0;
    StrCopy(cp,len+1,buf); cp+=len; *cp++=' ';
    if(ERMFlagsUsed[i]&1) *cp++='p';
    if(ERMFlagsUsed[i]&2) *cp++='&';
    if(ERMFlagsUsed[i]&4) *cp++='|';
    if(ERMFlagsUsed[i]&0x40){ *cp++=' '; *cp++='*'; }
    *cp++=0x0D; *cp++=0x0A;
  }
  StrCopy(cp,44,"v vars used in the left part [v1...v10000]:"); cp+=43;
  *cp++=0x0D; *cp++=0x0A;
  for(i=0;i<10000;i++){
    if(ERMVar2Used[i]==0) continue;
    *cp++='v';
    len=i2a(i+1,buf); buf[len]=0;
    StrCopy(cp,len+1,buf); cp+=len; *cp++=' ';
    if(ERMVar2Used[i]&1) *cp++='p';
    if(ERMVar2Used[i]&2) *cp++='&';
    if(ERMVar2Used[i]&4) *cp++='|';
    if(ERMVar2Used[i]&0x40){ *cp++=' '; *cp++='*'; }
    *cp++=0x0D; *cp++=0x0A;
  }
  StrCopy(cp,42,"w vars used in the left part [w1...w200]:"); cp+=41;
  *cp++=0x0D; *cp++=0x0A;
  for(i=0;i<200;i++){                                 
    if(ERMVarHUsed[i]==0) continue;
    *cp++='w';
    len=i2a(i+1,buf); buf[len]=0;
    StrCopy(cp,len+1,buf); cp+=len; *cp++=' ';
    if(ERMVarHUsed[i]&1) *cp++='p';
    if(ERMVarHUsed[i]&2) *cp++='&';
    if(ERMVarHUsed[i]&4) *cp++='|';
    if(ERMVarHUsed[i]&0x40){ *cp++=' '; *cp++='*'; }
    *cp++=0x0D; *cp++=0x0A;
  }
  StrCopy(cp,43,"z vars used in the left part [z1...z1000]:"); cp+=42;
  *cp++=0x0D; *cp++=0x0A;
  for(i=0;i<1000;i++){
    if(ERMStringUsed[i]==0) continue;
    *cp++='z';
    len=i2a(i+1,buf); buf[len]=0;
    StrCopy(cp,len+1,buf); cp+=len; *cp++=' ';
    if(ERMStringUsed[i]&1) *cp++='p';
    if(ERMStringUsed[i]&2) *cp++='&';
    if(ERMStringUsed[i]&4) *cp++='|';
    if(ERMStringUsed[i]&0x40){ *cp++=' '; *cp++='*'; }
    *cp++=0x0D; *cp++=0x0A;
  }
  StrCopy(cp,66,"Timers triggers [t] and receivers/instructions [r] [TM1...TM100]:"); cp+=65;
  *cp++=0x0D; *cp++=0x0A;
  for(i=0;i<100;i++){
    if(ERMTimerUsed[i]==0) continue;
    *cp++='T'; *cp++='M';
    len=i2a(i+1,buf); buf[len]=0;
    StrCopy(cp,len+1,buf); cp+=len; *cp++=' ';
    if(ERMTimerUsed[i]&1) *cp++='t';
    if(ERMTimerUsed[i]&2) *cp++='r';
    if(ERMTimerUsed[i]&0x40){ *cp++=' '; *cp++='*'; }
    *cp++=0x0D; *cp++=0x0A;
  }
  StrCopy(cp,81,"Functions triggers [t] and receivers/instructions [r,d] [FU(DO)1...FU(DO)30000]:"); cp+=80;
  *cp++=0x0D; *cp++=0x0A;
  for(i=0;i<30000;i++){
    if(ERMFunUsed[i]==0) continue;
    *cp++='F'; *cp++='U';
    len=i2a(i+1,buf); buf[len]=0;
    StrCopy(cp,len+1,buf); cp+=len; *cp++=' ';
    if(ERMFunUsed[i]&1) *cp++='t';
    if(ERMFunUsed[i]&2) *cp++='r';
    if(ERMFunUsed[i]&4) *cp++='d';
    if(ERMFunUsed[i]&0x40){ *cp++=' '; *cp++='*'; }
    *cp++=0x0D; *cp++=0x0A;
  }
  if(SaveSetupState("ERMVarsUsed.LOG",VarUsedLog,StrLen(VarUsedLog))){
    Message(/*ITxt(125,1,&WoGTexts)*/"Cannot write LOG file",1);
  }
  RETURNV
}
int LogERMVarNumParse(VarNum *vn,char w,int flag=ERMVarCheck4DblStore)
{
  #include "templ.h"
  int j;
  switch(vn->IType){ // indexed
      case 0: //=���,
        switch(vn->Type){ // ��� �����
          case 0: //=�����,
            break;
          case 1: //=����,
            j=vn->Num;
            if((j<1)||(j>1000)){ Message("Cannot LOG index of flag",1); RETURN(1) }
            if(flag) if(ERMFlagsUsed[j-1]!=0) ERMFlagsUsed[j-1]|=0x40;
            ERMFlagsUsed[j-1]|=w;
            break;
          case 2: //=f...t,
            j=vn->Num;
            if((j<1)||(j>20)){ Message("Cannot LOG index of f...t var",1); RETURN(1) }
            if(flag) if(ERMVarUsed[j-1]!=0) ERMVarUsed[j-1]|=0x40;
            ERMVarUsed[j-1]|=w;
            break;
          case 3: //=v1...10000,
            j=vn->Num;
            if((j<1)||(j>10000)){ Message("Cannot LOG index of v var",1); RETURN(1) }
            if(flag) if(ERMVar2Used[j-1]!=0) ERMVar2Used[j-1]|=0x40;
            ERMVar2Used[j-1]|=w;
            break;
          case 4: //=w1...100,
            j=vn->Num;
            if((j<1)||(j>200)){ Message("Cannot LOG index of w var",1); RETURN(1) }
            if(flag) if(ERMVarHUsed[j-1]!=0) ERMVarHUsed[j-1]|=0x40;
            ERMVarHUsed[j-1]|=w;
            break;
          case 5: //=x1...100,
            break;
          case 6: //=y1...100
            break;
          case 7: //=z1...500
            j=vn->Num;
            if(j>1000) break;
            if((j<-10)||(j>1000)){ Message("Cannot LOG index of z var",1); RETURN(1) }
            if(j<1) break;
            if(flag) if(ERMStringUsed[j-1]!=0) ERMStringUsed[j-1]|=0x40;
            ERMStringUsed[j-1]|=w;
            break;
        }
        break;
      case 1: //=����,
        j=vn->Num;
        if((j<1)||(j>1000)){ Message("Cannot LOG index of flag [indexed???]",1); RETURN(1) }
        if(flag) if(ERMFlagsUsed[j-1]!=0) ERMFlagsUsed[j-1]|=0x40;
        ERMFlagsUsed[j-1]|=w;
        break;
      case 2: //=f...t,
        j=vn->Num;
        if((j<1)||(j>20)){ Message("Cannot LOG index of f...t var [indirected]",1); RETURN(1) }
        if(flag) if(ERMVarUsed[j-1]!=0) ERMVarUsed[j-1]|=0x40;
        ERMVarUsed[j-1]|=w;
        break;
      case 3: //=v1...1000,
        j=vn->Num;
        if((j<1)||(j>10000)){ Message("Cannot LOG index of v var [indirected]",1); RETURN(1) }
        if(flag) if(ERMVar2Used[j-1]!=0) ERMVar2Used[j-1]|=0x40;
        ERMVar2Used[j-1]|=w;
        break;
      case 4: //=w1...100,
        j=vn->Num;
        if((j<1)||(j>200)){ Message("Cannot LOG index of w var [indirected]",1); RETURN(1) }
        if(flag) if(ERMVarHUsed[j-1]!=0) ERMVarHUsed[j-1]|=0x40;
        ERMVarHUsed[j-1]|=w;
        break;
      case 5: //=x1...100,
        break;
      case 6: //=y1...100
        break;
    }
  RETURN(0)
}
void LogERMVarUsed(_ToDo_ *dp,char *Line)
{
  #include "templ.h"
  int i;
  for(i=0;i<dp->ParSet;i++){
    if(LogERMVarNumParse(&dp->Par[i],1)) Message(Line,1);
  }
  for(i=0;i<16;i++){
    if(LogERMVarNumParse(&dp->Efl[0][i][0],2)) Message(Line,1); // & left
    if(LogERMVarNumParse(&dp->Efl[0][i][1],2)) Message(Line,1); // & right
    if(LogERMVarNumParse(&dp->Efl[1][i][0],4)) Message(Line,1); // | left
    if(LogERMVarNumParse(&dp->Efl[1][i][1],4)) Message(Line,1); // | right
  }
  RETURNV
}
void LogTriggerConditions(_Cmd_ *cp,char *Line)
{
  #include "templ.h"
  int i;
  for(i=0;i<16;i++){
    if(LogERMVarNumParse(&cp->Efl[0][i][0],2)) Message(Line,1); // & left
    if(LogERMVarNumParse(&cp->Efl[0][i][1],2)) Message(Line,1); // & right
    if(LogERMVarNumParse(&cp->Efl[1][i][0],4)) Message(Line,1); // | left
    if(LogERMVarNumParse(&cp->Efl[1][i][1],4)) Message(Line,1); // | right
  }
  RETURNV
}
void LogERMFunctionTrigger(int fn,char *Line,int flag=ERMVarCheck4DblStore) // 1...30000
{
  #include "templ.h"
  if((fn<1)||(fn>30000)){
    Message("Cannot LOG index of function [trigger]",1);
    Message(Line,1);
    RETURNV
  }
  if(flag) if(ERMFunUsed[fn-1]!=0) ERMFunUsed[fn-1]|=0x40;
  ERMFunUsed[fn-1]|=1; // trigger
  RETURNV
}
void LogERMTimerTrigger(int tn,char *Line,int flag=ERMVarCheck4DblStore) // 1...100
{
  #include "templ.h"
  if((tn<1)||(tn>100)){
    Message("Cannot LOG index of timer [trigger]",1);
    Message(Line,1);
    RETURNV
  }
  if(flag) if(ERMTimerUsed[tn-1]!=0) ERMTimerUsed[tn-1]|=0x40;
  ERMTimerUsed[tn-1]|=1; // trigger
  RETURNV
}
void LogERMAnyReceiver(Word Id,VarNum Par,char * /*Line*/,int flag=ERMVarCheck4DblStore) // any trigger switched
{
  #include "templ.h"
  int ind;
//  ind=GetVarVal(&Par);
  switch(Par.IType){ // indexed
    case 0: //=���,
      switch(Par.Type){ // ��� �����
        case 0: //=�����,
          ind=Par.Num;
          break;
        default:
          ind=-1;
          break;
      }
      break;
    default:
      ind=-1;
      break;
  }
  switch(Id){
    case 'UF':// VC 'FU':
      if((ind<1)||(ind>30000)){
//        MError("Function receiver or instruction cannot be logged (variable value is not defined yet).");
//        Message(Line,1);
//        ������ ���������
        break;
      }
      if(flag) if(ERMFunUsed[ind-1]!=0) ERMFunUsed[ind-1]|=0x40;
      ERMFunUsed[ind-1]|=2; // receiver or instruction
      break;
    case 'OD':// VC 'DO':
      if((ind<1)||(ind>30000)){
//        MError("Cycle receiver or instruction cannot be logged (variable value is not defined yet).");
//        Message(Line,1);
//        ������ ���������
        break;
      }
      if(flag) if(ERMFunUsed[ind-1]!=0) ERMFunUsed[ind-1]|=0x40;
      ERMFunUsed[ind-1]|=4; // receiver or instruction
      break;
    case 'MT':// VC 'TM':
      if((ind<1)||(ind>100)){
//        MError("Timer receiver or instruction cannot be logged (variable value is not defined yet).");
//        Message(Line,1);
//        ������ ���������
        break;
      }
      if(flag) if(ERMTimerUsed[ind-1]!=0) ERMTimerUsed[ind-1]|=0x40;
      ERMTimerUsed[ind-1]|=2; // receiver or instruction
      break;
  }
  RETURNV
}
int ERM_VarControl(char Cmd,int /*Num*/,_ToDo_*,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  switch(Cmd){
    case 'C': // �������� ������
      ClearVarUsedList();
      break;
    case 'B': // ������ �������� ����������
      StartVarUsed();
      break;
    case 'E': // ������������� ���� ����������
      StopVarUsed();
      break;
    case 'Y': // ��������� �� �����������
      StartDblVarUsed();
      break;
    case 'N': // ��������� �� �����������
      StopDblVarUsed();
      break;
    case 'W': // �������� ���� � ����
      WriteVarUsed();
      break;
    default:
      MError("\"!!VC:\"-wrong command.");
      RETURN(0)
  }
  RETURN(1)
}

static char UN_Buf[32];
int ERM_Universal(char Cmd,int Num,_ToDo_*,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int x,y,l,t,st,srf,t2,st2,v,v2,zi,redraw;
  int *mt,MType,MSType;
  char *str,*str2,*str3;
  _MapItem_ *mp;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  switch(Cmd){
    case 'W': // ��������� ���� �� ����
      if(Num<5){ MError("\"!!UN:W\"-insufficient parameters."); RETURN(0) } // #x1/#y1/#x2/#y2/#l
      if(Num==6) SW_Set=Mp->n[5]; else SW_Set=1;
      PathOverWater(Mp->n[0],Mp->n[1],Mp->n[2],Mp->n[3],Mp->n[4]);
      RedrawMap();
      break;
    case 'D': // ������� ��������� ������ ���������� �� ����
      if(Num<3){ MError("\"!!UN:D\"-insufficient parameters."); RETURN(0) } // #x/#y/#l
      if(Num==4) SW_Set=Mp->n[3]; else SW_Set=1;
      StepWater(Mp->n[0],Mp->n[1],Mp->n[2]);
      RedrawMap();
      break;
    case 'S': // ������� �����������
      if(Num<5){ MError("\"!!UN:S\"-insufficient parameters."); RETURN(0) } // #x/#y/#l/#o/#r
      ShowArea(Mp->n[0],Mp->n[1],Mp->n[2],Mp->n[3],Mp->n[4]);
      break;
    case 'H': // ������� �����������
      if(Num<5){ MError("\"!!UN:H\"-insufficient parameters."); RETURN(0) } // #x/#y/#l/#o/#r
      HideArea(Mp->n[0],Mp->n[1],Mp->n[2],Mp->n[3],Mp->n[4]);
      break;
    case 'R': // ���������� ������
      switch(Mp->n[0]){
        case 1: RedrawMap(); break;
        case 2: RedrawRes(); break;
        case 3:
          if(Num<2){ MError("\"!!UN:R3\"-insufficient parameters."); RETURN(0) } // #x/#y/#l/#o/#r
          v=Mp->n[1];
          if((v<-1)||(v>=HERNUM)){ MError("\"!!UN:R3\"-wrong hero number."); RETURN(0) } // #x/#y/#l/#o/#r
          if(v==-1) RedrawHeroScreen(ERM_HeroStr);
          else RedrawHeroScreen(GetHeroStr(v));
          break;
        case 4: RedrawTown(); break;
        case 5: // ���������� ��� �������
          if(Num<3){ MError("\"!!UN:R5\"-insufficient parameters."); RETURN(0) } // #x/#y/#l/#o/#r
          if(Apply(&MType,4,Mp,1)) break;
          if(Apply(&MSType,4,Mp,2)) break;
          SetMouseCursor(MSType,MType);
          break;
        case 6:
          if(Num<2){ MError("\"!!UN:R6\"-insufficient parameters."); RETURN(0) } // #x/#y/#l/#o/#r
          if(Apply(&MType,4,Mp,1)) break;
          DelayIt(MType); // delay for MType msec
          break;
        case 7: // enable/disable show/hide cursor
          if(Num<2){ MError("\"!!UN:R7\"-insufficient parameters."); RETURN(0) } // #x/#y/#l/#o/#r
          if(Apply(&MType,4,Mp,1)) break;
          if(MType){ // hide
            ZHideCursor();
          }else{
            ZShowCursor();
          }
          if(Num>2) Apply(&GLB_DisableMouse,4,Mp,2);
          break;        
        default: MError("\"!!UN:R\"-wrong parameter."); RETURN(0)
      }
      break;
    case 'E': // ��������� �� ����������� ����������
      if(Num<3){ MError("\"!!UN:E\"-insufficient parameters."); RETURN(0) } // #x/#y/#l
      mp=GetMapItem(Mp->n[0],Mp->n[1],Mp->n[2]);
      if(mp==0){ MError("\"!!UN:E\"-wrong map position."); RETURN(0) }
      if(EmptyPlace2(mp)==0){ //������
        ERMFlags[0]=1;
      }else{
        ERMFlags[0]=0;
      }
      break;
    case 'I': // Ix/y/l/t/s,Ix/y/l/t/s/ter, Ix/y/l/t/s/t2/st2/ter - ��������� ������
      redraw=1;
      if(Num<5){ MError("\"!!UN:I\"-insufficient parameters."); RETURN(0) }
      x=Mp->n[0]; y=Mp->n[1]; l=Mp->n[2];
      t=Mp->n[3]; st=Mp->n[4];
      if(Num==5){ srf=-1; }
      if(Num==6){ srf=Mp->n[5]; if((srf<-1)||(srf>8)){ MError("\"!!UN:I\"-wrong surface type (-1...8)                                ."); RETURN(0) }}
      t2=t; st2=st;
      if(Num>6){ t2=Mp->n[5]; st2=Mp->n[6]; }
      if(Num==7){ srf=-1; }
      if(Num>7) { srf=Mp->n[7]; if((srf<-1)||(srf>8)){ MError("\"!!UN:I\"-wrong surface type (-1...8)."); RETURN(0) }}
      if(Num==9)  redraw=Mp->n[8];
      PlaceObject(x,y,l,t,st,t2,st2,srf);
      if(redraw) RedrawMap();
      break;
    case 'O': // Ox/y/l(t/redr) ������� ������
      redraw=1;
      if(Num<3){ MError("\"!!UN:O\"-insufficient parameters."); RETURN(0) }
      if(Num>3) t=Mp->n[3]; else t=0;
      if(Num==5) redraw=Mp->n[4];
      DelObject(Mp->n[0],Mp->n[1],Mp->n[2]);
      if(t!=0) DelObjPos(PosMixed(Mp->n[0],Mp->n[1],Mp->n[2]));
      if(redraw) RedrawMap();
      break;
    case 'F': // Fx/y/l/dx/dy ������� ���
      if(Num!=5){ MError("\"!!UN:F\"-insufficient parameters."); RETURN(0) }
      ProvokeAnimation(Mp->n[0],Mp->n[1],Mp->n[2],Mp->n[3],Mp->n[4],1,OAM_AUTO);
      break;
    case 'K': // K#/$ ���������� ������...
      if(Num<2){ MError("\"!!UN:K\"-insufficient parameters."); RETURN(0) }
      switch(Mp->n[0]){
        case 1: // K1/$ 1-��� ������ ������, 0-������
          Apply(&NextWeekOf,4,Mp,1);
          break;
        case 2: // K2/$ ����� ������ ��� ������ (1...500)
          Apply(&NextWeekMess,4,Mp,1);
          break;
        default: MError("\"!!UN:I\"-wrong first parameter."); RETURN(0)
      }
      break;
    case 'M': // M#/$ ���������� �����...
      switch(Mp->n[0]){
        case 0: // M0 ����� ��� ������
          NextMonthOf=0;
          break;
        case 1: // M1 ����� ������
          NextMonthOf=1;
          break;
        case 2: // M2/$ - ����� �������*2
          if(Num<2){ MError("\"!!UN:M\"-insufficient parameters."); RETURN(0) }
          NextMonthOf=2;
          Apply(&NextMonthOfMonster,4,Mp,1);
          break;
        case 3: // M3 ����� ����
          NextMonthOf=3;
          break;
//        case 4: // M4/$1/$2 - ��� �������*2 � ������� $1
//          if(Num<3){ Error(); return 0; }
//          if((Mp->n[1]<0)||(Mp->n[1]>11)){ Error(); return 0; }
//          Apply(&NewMonthMonTypes[Mp->n[1]],1,Mp,2);
//          break;
        default: MError("\"!!UN:M\"-wrong first parameter."); RETURN(0)
      }
      break;
    case 'N': // N#/z/subtype/...
      if(Num<3){ MError("\"!!UN:N\"-insufficient parameters."); RETURN(0) }
      zi=0; Apply(&zi,4,Mp,1);
      if((zi<-10)||(zi==0)||(zi>1000)){ MError("\"!!UN:N\"-z var index out of range (-10...-1,1...1000)."); RETURN(0) }
      v=-1; Apply(&v,4,Mp,2);
      if(v<0){ MError("\"!!UN:N\"-incorrect type of object (<0)."); RETURN(0) }
      if(zi>0) str=ERMString[zi-1];
      else     str=ERMLString[-zi-1];
////      if(zi<0){ // b
////        if(CheckScope()) return 0;
////        str=ERMScope->String[-zi-1];
////      }else{ // z
////        str=ERMString[zi-1];
////      }
      switch(Mp->n[0]){
        case 0: // N0/z/st get name of artefact
          StrCopy(str,512,GetArtName(v));
          break;
        case 1: // N1/z/st get name of spell
          StrCopy(str,512,GetSpellName(v));
          break;
        case 2: // N2/z/st/sst  //  ��� �������� � ������������ ������
          if(Num<4){ MError("\"!!UN:N\"-insufficient parameters."); RETURN(0) }
           v2=-1; Apply(&v2,4,Mp,3);
          if(v2<0){ MError("\"!!UN:N\"-incorrect additioal type of object (<0)."); RETURN(0) }
          StrCopy(str,512,GetBuildName(v,v2));
          break;
        case 3: // N3/z/st/sP  //  ��� �������(��)
          if(Num<4){ MError("\"!!UN:N\"-insufficient parameters."); RETURN(0) }
           v2=-1; Apply(&v2,4,Mp,3);
          if(v2<0){ MError("\"!!UN:N\"-incorrect additioal type of object (<0)."); RETURN(0) }
          StrCopy(str,512,GetMonName(v,v2));
          break;
        case 4: // N4/z/st get name of secondary skill
          StrCopy(str,512,GetSSkillName(v));
          break;
        case 5: // N5/z/optind save a value to INI file
          if(Num<3){ MError("\"!!UN:N5\"-insufficient parameters."); RETURN(0) }
          if(Num>3){
            zi=0; Apply(&zi,4,Mp,3);
            if((zi<-10)||(zi==0)||(zi>1000)){ MError("\"!!UN:N5\"-z var index out of range (-10...-1,1...1000)."); RETURN(0) }
            if(zi>0) str2=ERMString[zi-1];
            else     str2=ERMLString[-zi-1];
          }else str2="Common";
          if(Num>4){
            zi=0; Apply(&zi,4,Mp,4);
            if((zi<-10)||(zi==0)||(zi>1000)){ MError("\"!!UN:N5\"-z var index out of range (-10...-1,1...1000)."); RETURN(0) }
            if(zi>0) str3=ERMString[zi-1];
            else     str3=ERMLString[-zi-1];
          }else str3=".\\WoG.ini";
          WriteStrINI(str,itoa(v,UN_Buf,10),str2,str3);
          break;
        case 6: // N5/z/optind read a value to INI file
          if(Num<3){ MError("\"!!UN:N6\"-insufficient parameters."); RETURN(0) }
          if(Num>3){
            zi=0; Apply(&zi,4,Mp,3);
            if((zi<-10)||(zi==0)||(zi>1000)){ MError("\"!!UN:N6\"-z var index out of range (-10...-1,1...1000)."); RETURN(0) }
            if(zi>0) str2=ERMString[zi-1];
            else     str2=ERMLString[-zi-1];
          }else str2="Common";
          if(Num>4){
            zi=0; Apply(&zi,4,Mp,4);
            if((zi<-10)||(zi==0)||(zi>1000)){ MError("\"!!UN:N5\"-z var index out of range (-10...-1,1...1000)."); RETURN(0) }
            if(zi>0) str3=ERMString[zi-1];
            else     str3=ERMLString[-zi-1];
          }else str3=".\\WoG.ini";
          ReadStrINI(str,512-1,str,itoa(v,UN_Buf,10),str2,str3);
          break;
        default: MError("\"!!UN:N\"-wrong first parameter."); RETURN(0)
      }
      break;
    case 'C': // Cadr/syze/data �����. ������
      if(Num!=3){ MError("\"!!UN:C\"-insufficient parameters."); RETURN(0) }
//      Apply((void *)Mp->n[0],(char)Mp->n[1],Mp,2);
      if(Apply(&v ,4,Mp,0)){ MError("\"!!UN:C\"-get or check syntax is not acceptable."); RETURN(0) }
      if(Apply(&v2,4,Mp,1)){ MError("\"!!UN:C\"-get or check syntax is not acceptable."); RETURN(0) }
      __asm{ 
        mov eax,v 
        mov eax,[eax]
        mov t,eax
      }
      if(Apply(&t,(char)v2,Mp,2)) break;
      switch(v2){
        case 1: __asm{ 
          mov edx,v
          mov eax,t 
          mov [edx], al 
                } 
          break;
        case 2: __asm{ 
          mov edx,v 
          mov eax,t 
          mov [edx], ax 
                } 
          break;
        case 4: __asm{ 
          mov edx,v 
          mov eax,t 
          mov [edx],eax 
                } 
          break;
        default: MError("\"!!UN:C\"-wrong syntax."); RETURN(0)
      }
      break;
    case 'X': // X?x/?l - �������� ������� �����
      if(Num!=2){ MError("\"!!UN:X\"-insufficient parameters."); RETURN(0) }
      if(Mp->VarI[0].Check==0){ MError("\"!!UN:X\"-try to set X(Y)."); RETURN(0) }
      if(Mp->VarI[1].Check==0){ MError("\"!!UN:X\"-try to set L."); RETURN(0) }
      v=GetMapSize();
      v2=GetMapLevels();
      Apply(&v,4,Mp,0);
      Apply(&v2,4,Mp,1);
      break;
    case 'V': // V?wog/?erm - �������� ������ WoG � ERM
      if(Num<2){ MError("\"!!UN:V\"-insufficient parameters."); RETURN(0) }
      if(Mp->VarI[0].Check==0){ MError("\"!!UN:V\"-try to set WoG version."); RETURN(0) }
      if(Mp->VarI[1].Check==0){ MError("\"!!UN:V\"-try to set ERM version."); RETURN(0) }
      v=WOG_VERSION;
      v2=ERM_VERSION;
      Apply(&v,4,Mp,0);
      Apply(&v2,4,Mp,1);
      if(Num>2){
//        if(Num<5){ MError("\"!!UN:V\"-insufficient parameters."); RETURN(0) }
        if(Mp->VarI[2].Check==0){ MError("\"!!UN:V\"-try to set parameter."); RETURN(0) }
        if(Mp->VarI[3].Check==0){ MError("\"!!UN:V\"-try to set parameter."); RETURN(0) }
        if(Mp->VarI[4].Check==0){ MError("\"!!UN:V\"-try to set parameter."); RETURN(0) }
        __asm{ 
          mov eax,0x6992C4 
          mov eax,[eax] 
          mov v,eax 
        }
        Apply(&v,4,Mp,2);
        __asm{ 
          mov eax,0x69959C
          mov eax,[eax]; 
          mov v,eax; 
        }
        Apply(&v,4,Mp,3);
        __asm{ 
          mov eax,0x698A40; 
          mov eax,[eax]; 
          mov v,eax; 
        }
        Apply(&v,4,Mp,4);
        if(Num>5){
          if(Num<7){ MError("\"!!UN:V\"-insufficient parameters."); RETURN(0) }
          __asm{ 
            mov eax,0x698A84; 
            mov eax,[eax]; 
            mov v,eax; 
          }
          Apply(&v,4,Mp,5);
          v=0;
          __asm{
            xor eax,eax
            mov edx,BASE;
            mov edx,[edx]
            mov al,[edx+0x1F69C];
            mov v,eax;
          }
          Apply(&v,4,Mp,6);
        }
      }
      break;
    case 'A': // Cart/var �������� ��� (0) ��� ��� (1)
      if(Num<2){ MError("\"!!UN:A\"-insufficient parameters."); RETURN(0) }
      if(Num==2){
        v=ArtDisabled(Mp->n[0]);
        if(Apply(&v,4,Mp,1)==0){
          ArtDisabledSet(Mp->n[0],v);
        }
        break;
      }else if(Num==3){
        _ArtSetUp_ *artsetup;
        v2=-1; Apply(&v2,4,Mp,0);
        if((v2<0)||(v2>=ARTNUM)){ MError("\"!!UN:A\"-wrong artifact number (internal)."); RETURN(0) }
        artsetup=&GetArtBase()[v2];
        v=0; Apply(&v,4,Mp,1);
        switch(v){
          case 1: // cost
            v=artsetup->Cost; Apply(&v,4,Mp,2); artsetup->Cost=(Dword)v;
            break;
          case 2: // position
            v=artsetup->Position; Apply(&v,4,Mp,2); artsetup->Position=v;
            break;
          case 3: // type
            v=artsetup->Type; Apply(&v,4,Mp,2); artsetup->Type=v;
            break;
          case 4: // SuperNumber
            v=artsetup->SuperN; Apply(&v,4,Mp,2); artsetup->SuperN=v;
            break;
          case 5: // Part of Super
            v=artsetup->PartOfSuperN; Apply(&v,4,Mp,2); artsetup->PartOfSuperN=v;
            break;
          case 7: // Disable;
            v=artsetup->Disable; Apply(&v,4,Mp,2); artsetup->Disable=(Byte)v;
            break;
          case 8: // NewSpell;
            v=artsetup->NewSpell; Apply(&v,4,Mp,2); artsetup->NewSpell=(Byte)v;
            break;
          case 9: // Name 2 z
            v=ArtNames[v2].NameVar; if(Apply(&v,4,Mp,2)) break; ArtNames[v2].NameVar=v;
            if(v!=0){
              if((v<1)||(v>1000)){ MError("\"UN:A\"-wrong z var index (1...1000)."); RETURN(0) }
              artsetup->Name=ERMString[v-1];
            }else{ artsetup->Name=ArtSetUpBack[v2].Name; }
            break;
          case 10: // Descr 2 z
            v=ArtNames[v2].DescVar; if(Apply(&v,4,Mp,2)) break; ArtNames[v2].DescVar=v;
            if(v!=0){
              if((v<1)||(v>1000)){ MError("\"UN:A\"-wrong z var index (1...1000)."); RETURN(0) }
              artsetup->Description=ERMString[v-1];
            }else{ artsetup->Description=ArtSetUpBack[v2].Description; }
            break;
          default: //0
            MError("\"UN:A\"-wrong syntax (A$/$/$)."); RETURN(0)
        }
        break;
      }else if(Num>=4){
        int Arts[14];
        int CInd=-1; Apply(&CInd,4,Mp,0);
        if((CInd<0)||(CInd>=32)){ MError("\"!!UN:A\"-wrong combo artifact index."); RETURN(0) }
        int CNum=CArtSetup[CInd].Index; if(Apply(&CNum,4,Mp,1)) break;
        if((CNum<0)||(CNum>=ARTNUM)){ MError("\"!!UN:A\"-wrong combo artifact number."); RETURN(0) }
        for(int i=2;i<Num;i++){ Arts[i-2]=-1; Apply(&Arts[i-2],4,Mp,i); }
        ERMFlags[0]=BuildUpCombo(CNum,CInd,Num-2,Arts);
      }
      break;
    case 'U': // Utype/subtype/?N  ��� Utype/subtype/i/varnumber
      if(Num<2){ MError("\"!!UN:U\"-insufficient parameters."); RETURN(0) }
      if((Apply(&t,4,Mp,0))||(Apply(&st,4,Mp,1))){ MError("\"!!UN:U\"-cannot check or get Type and Subtype."); RETURN(0) }
      if(Num==3){
        srf=CalcObjects(t,st);
        if(Apply(&srf,4,Mp,2)==0){ MError("\"!!UN:U\"-cannot set number of objects."); RETURN(0) }
      }else{
        if(Apply(&srf,4,Mp,2)){ MError("\"!!UN:U\"-cannot get or check number of object."); RETURN(0) }
        if(srf==0){ MError("\"!!UN:U\"-wrong object number (0). Must be>0, -1 or -2"); RETURN(0) }
        if(Apply(&v,4,Mp,3)){ MError("\"!!UN:U\"-cannot get or check number of V variable."); RETURN(0) }
        if((v<1)||(v>9998)){ MError("\"!!UN:U\"-wrong V var number (1...9998)."); RETURN(0) }
//        if(srf==-1){
        if(srf<0){
          x=ERMVar2[v-1];
          y=ERMVar2[v];
          l=ERMVar2[v+1];
          if(FindNextObjects(t,st,&x,&y,&l,srf)){ MError("\"!!UN:U\"-cannot find more objects."); RETURN(0) }
        }else{
          if(FindObjects(t,st,srf,&x,&y,&l)){ MError("\"!!UN:U\"-cannot get object coordinates."); RETURN(0) }
        }
        ERMVar2[v-1]=x;
        ERMVar2[v]=y;
        ERMVar2[v+1]=l;
      }
      break;
    case 'T': // Ttown/dwel/upgr/montype - ��� �������� ��� �����
      if(Num<4){ MError("\"!!UN:T\"-insufficient parameters."); RETURN(0) }
      t=-1; Apply(&t,4,Mp,0); if((t<0)||(t>8)){ MError("\"!!UN:T\"-wrong town number(0...8)."); RETURN(0) }
      mt=MonInTownBase(t);
      st=-1; Apply(&st,4,Mp,1); if((st<0)||(st>6)){ MError("\"!!UN:T\"-wrong dwelling number(0...6)."); RETURN(0) }
      t2=-1; Apply(&t2,4,Mp,2); if((t2<0)||(t2>1)){ MError("\"!!UN:T\"-wrong upgrade(0,1)."); RETURN(0) }
      v=mt[t2*7+st];
      if(Apply(&v,4,Mp,3)) break;
      if((v<0)||(v>=MONNUM)){ MError("\"!!UN:T\"-wrong monster type."); RETURN(0) }
      mt[t2*7+st]=v;
      break;
    case 'L': // ����������� � �������
      if(Num==4){ ShowThis(Mp->n[0],Mp->n[1],(char)Mp->n[2],Mp->n[3]); }
      else if(Num==3){
        if((Mp->n[0]>=0)&&(Mp->n[1]>=0)){
          t=GetObel(Mp->n[0],Mp->n[1]);
        }else t=0;
        if(Apply(&t,4,Mp,2)) break;
        SetObel(Mp->n[0],Mp->n[1],t);
      }else{ MError("\"!!UN:L\"-insufficient parameters."); RETURN(0) }// #x/#y/#l/#d
      break;
    case 'P': // ��������� ���������
      if(Num<2){
        Apply(&PL_ExtDwellStd,4,Mp,0);
        break;
      }
      switch(Mp->n[0]){
        case 0: // ������� ��������
          if(Apply(&PL_ExtDwellStd,4,Mp,1)) break; // 0
//          Apply(&PL_WoGOptions[1][0],4,Mp,1);
          break;
        case 1: // ���������� �����
          if(Apply(&PL_TowerStd,4,Mp,1)) break; // 1
//          Apply(&PL_WoGOptions[1][1],4,Mp,1);
          break;
        case 2: // ���������� ��������
          if(Apply(&PL_MLeaveStd,4,Mp,1)) break; // 2
//          Apply(&PL_WoGOptions[1][2],4,Mp,1);
          break;
        case 3: // NPC
          PL_NPCOptionWasSet=1;
          if(Apply(&PL_NoNPC,4,Mp,1)) break; // ��������� // 3
          if(PL_NoNPC) DisableNPC(-1); else EnableNPC(-1,!PL_NPC2Hire);
//          Apply(&PL_WoGOptions[1][3],4,Mp,1);
          break;
        case 4: // ���������� ������
          if(Apply(&PL_NoTownDem,4,Mp,1)) break;  // 4
//          Apply(&PL_WoGOptions[1][4],4,Mp,1);
          break;
        default: //MError("\"!!UN:P\"-wrong first parameter."); return 0;
          if((Mp->n[0]<0)||(Mp->n[0]>=PL_WONUM)){ MError("\"!!UN:P\"-wrong first parameter."); RETURN(0) }
          if(Mp->n[0]==5) PL_DisableWogifyWasSet=1;
          if(Mp->n[0]==900) PL_ExpoWasSet=1;
          if(Apply(&PL_WoGOptions[0][Mp->n[0]],4,Mp,1)) break;
//          Apply(&PL_WoGOptions[1][Mp->n[0]],4,Mp,1);
          break;
      }
      break;
    case 'B': // B#/$ ��������� �������� � �������
      if(Num<2){ MError("\"!!UN:B\"-insufficient parameters."); RETURN(0) }
      switch(Mp->n[0]){
        case 0: // ������
          Apply(&EnableMithrill,4,Mp,1);
          break;
        default: // ������ 1..., ����� 7...10 
          if((Mp->n[0]<0)||(Mp->n[0]>19)){ MError("\"!!UN:B\"-wrong first parameter."); RETURN(0) }
          Apply(&EnableChest[Mp->n[0]],4,Mp,1);
          break;
      }
      break;
    case 'Q': // Q# ��������� (0) ��� �������� (1)
      if(Num>1){ // 3.58
        if(Mp->n[0]){ // ��������
          __asm{
            mov   ecx,1
            mov   eax,0x4F3370
            call  eax
          }
        }else{ // ���������
          __asm{
            mov   ecx,2
            mov   eax,0x4F3370
            call  eax
          }
        }
      }else{
        if(Mp->n[0]){ // ��������
          __asm{
            mov    eax,0x697308
            mov    dword ptr [eax],1
            mov    eax,0x699560
            mov    dword ptr [eax],1
          }
        }else{ // ���������
          __asm{
            mov    eax,0x697308
            mov    dword ptr [eax],1
            mov    eax,0x699560
            mov    dword ptr [eax],0
          }
        }
      }
      break;
    case 'G': // G#/#/#/$ �����
      if(Num<4){ MError("\"!!UN:G\"-insufficient parameters."); RETURN(0) }
      switch(Mp->n[0]){
        case 0:  // ��������� ������ 0/�����_�����/���_������/zvar
          t=Mp->n[1];  if((t<0)||(t>28)){ MError("\"!!UN:G\"-wrong secondary skill number (0...27)."); RETURN(0) }
          t2=Mp->n[2]; if((t2<0)||(t2>3)){ MError("\"!!UN:G\"-wrong secondary skill text type number (0...3)."); RETURN(0) }
          v=SSAllNames[t].Var[t2];
          if(Apply(&v,4,Mp,3)) break;
          SSAllNames[t].Var[t2]=v;
          if(v!=0){
            if((v<1)||(v>1000)){ MError("\"UN:G\"-wrong z var index (1...1000)."); RETURN(0) }
            switch(t2){
              case 0:
                SSNAME[t].Name=ERMString[v-1];
                SSNAMEDESC[t].Name[t2]=ERMString[v-1];
                break;
              default:
                SSDESC[t].Name[t2-1]=ERMString[v-1];
                SSNAMEDESC[t].Name[t2]=ERMString[v-1];
                break;
            }
          }else{
            switch(t2){
              case 0:
                SSNAME[t].Name=SSNameBack[t].Name;
                SSNAMEDESC[t].Name[t2]=SSNameDescBack[t].Name[t2];
                break;
              default:
                SSDESC[t].Name[t2-1]=SSDescBack[t].Name[t2-1];
                SSNAMEDESC[t].Name[t2]=SSNameDescBack[t].Name[t2];
                break;
            }
          }
          break;
        case 1:  // ������� 1/�����_�������/���_������/zvar
          t=Mp->n[1];  if((t<0)||(t>=MONNUM)){ MError("\"!!UN:G\"-wrong monster number."); RETURN(0) }
          t2=Mp->n[2]; if((t2<0)||(t2>2)){ MError("\"!!UN:G\"-wrong monster text type number (0...2)."); RETURN(0) }
          v=MonNames[t].Var[t2];
          if(Apply(&v,4,Mp,3)) break;
          MonNames[t].Var[t2]=v;
          if(v!=0){
            if((v<1)||(v>1000)){ MError("\"UN:G\"-wrong z var index (1...1000)."); RETURN(0) }
            switch(t2){
              case 0: // single
                MonTable [t].NameS=ERMString[v-1];
                MonTable2[t].NameS=ERMString[v-1];
                break;
              case 1: // plural
                MonTable [t].NameP=ERMString[v-1];
                MonTable3[t].NameP=ERMString[v-1];
                break;
              case 2: // spec
                MonTable [t].Spec=ERMString[v-1];
                MonTable4[t].Spec=ERMString[v-1];
                break;
            }
          }else{
            switch(t2){
              case 0: // single
                MonTable [t].NameS=MonTable2Back[t].NameS;
                MonTable2[t].NameS=MonTable2Back[t].NameS;
                break;
              case 1: // plural
                MonTable [t].NameP=MonTable3Back[t].NameP;
                MonTable3[t].NameP=MonTable3Back[t].NameP;
                break;
              case 2: // spec
                MonTable [t].Spec=MonTable4Back[t].Spec;
                MonTable4[t].Spec=MonTable4Back[t].Spec;
                break;
            }
          }
          break;
        case 2:  // ����.������ 2/�����_�����/���_������(3-��������)/zvar(����� �������� ����+1)
          t=Mp->n[1];  if((t<0)||(t>=HERNUM)){ MError("\"!!UN:G\"-wrong hero number."); RETURN(0) }
          t2=Mp->n[2]; if((t2<0)||(t2>3)){ MError("\"!!UN:G\"-wrong herospec text type number (0...3)."); RETURN(0) }
          if(t2==3){ // ��������
            v=HSpecNames[t].PicNum-1;
            if(Apply(&v,4,Mp,3)) break;
            HSpecNames[t].PicNum=v+1;
            break;
          }
          v=HSpecNames[t].Var[t2];
          if(Apply(&v,4,Mp,3)) break;
          HSpecNames[t].Var[t2]=v;
          if(v!=0){
            if((v<1)||(v>1000)){ MError("\"UN:G\"-wrong z var index (1...1000)."); RETURN(0) }
            switch(t2){
              case 0: // short
                HSpecTable[t].SpShort=ERMString[v-1];
                break;
              case 1: // full
                HSpecTable[t].SpFull=ERMString[v-1];
                break;
              case 2: // descr
                HSpecTable[t].SpDescr=ERMString[v-1];
            }
          }else{
            switch(t2){
              case 0: // short
                HSpecTable[t].SpShort=HSpecBack[t].SpShort;
                break;
              case 1: // full
                HSpecTable[t].SpFull=HSpecBack[t].SpFull;
                break;
              case 2: // descr
                HSpecTable[t].SpDescr=HSpecBack[t].SpDescr;
                break;
            }
          }
          break;
        default: MError("\"!!UN:G\"-wrong first parameter."); RETURN(0)
      }
      break;
    case 'J': // J#/#/$ ������
      switch(Mp->n[0]){
        case 0: // ����������� �������
          if(Num<3){ MError("\"!!UN:J\"-insufficient parameters."); RETURN(0) }
          t=Mp->n[1];  if((t<0)||(t>=0x46)){ MError("\"!!UN:J\"-wrong spell number (0...69)."); RETURN(0) }
          v=SpellDisBase()[t];
          if(Apply(&v,4,Mp,2)) break;
          SpellDisBase()[t]=(char)v;
          break;
        case 1: // ����������� ������ ����� ������
          if(Num<3){ MError("\"!!UN:J\"-insufficient parameters."); RETURN(0) }
          v=GetLimitLvl();
          if(Apply(&v,4,Mp,1)){ // check,get
          }else{ // set
            SetLimitLvl(v);
          }
          v=(int)GetExpo(v);
          Apply(&v,4,Mp,2);
          break;
        case 2: // ��������� ����
          if(Num<2){ MError("\"!!UN:J\"-insufficient parameters."); RETURN(0) }
          v=GameLevel();
          if(Apply(&v,4,Mp,1)) break; // check,get
          SetGameLevel(v);
          break;
        case 3: // J3/^text^ or J3/# �������� ���������������� �����
          { char *d;
            if(Num!=2){ MError("\"!!UN:J3\"-wrong number of parameters."); RETURN(0) }
            if(Mp->n[1]!=0){ // �������� - z var
              if(Apply(&v,4,Mp,1)) break;
              if((v<-10)||(v==0)){ MError("\"!!UN:J3\"- z var out of range (-10...-1,1...1000)."); RETURN(0) }
              if(v>1000)    d=StringSet::GetText(v);
              else if(v>0)  d=ERMString[v-1];
              else          d=ERMLString[-v-1];
              d=ERM2String2(1,d);
            }else{ // �������� - ^�����^
              d=ERM2String(&Mp->m.s[Mp->i],0,&v);
              Mp->i+=v;
            }
            ResetCustomSettings(d);
            break;
          }
        case 4: // 3.58 set the AI thinking delay
          if(Num<2){ MError("\"!!UN:J4\"-insufficient parameters."); RETURN(0) }
          v=GetDelay();
          if(Apply(&v,4,Mp,1)) break; // check,get
          AI_Delay=v;
          SetDelay(v);
          break;
        case 5: // 3.58 set auto save flag
          if(Num<2){ MError("\"!!UN:J5\"-insufficient parameters."); RETURN(0) }
          v=GetAutoSave();
          if(Apply(&v,4,Mp,1)) break; // check,get
          AutoSaveFlag=v;
          SetAutoSave(v);
          break;
        case 6: // J6/#/$; 3.58 get a random artifact
          if(Num<3){ MError("\"!!UN:J6\"-insufficient parameters."); RETURN(0) }
          if(Apply(&v,4,Mp,1)){ MError("\"!!UN:J6\"-cannot check art level."); RETURN(0) }
          v=GenArt(v);
          Apply(&v,4,Mp,2);
          break;
        case 7: // J7/#/$; 3.58 get/set Merchant artifact
          if(Num<3){ MError("\"!!UN:J7\"-insufficient parameters."); RETURN(0) }
          if(Apply(&v,4,Mp,1)){ MError("\"!!UN:J7\"-cannot check art slot."); RETURN(0) }
          v2=GetMerchArt(v);
          if(Apply(&v2,4,Mp,2)) break;
          SetMerchArt(v,v2);
          break;
        case 8: // J8/#(modifier)/#(z var) or J8/#/^text^ set flag 1 - if file exists
          { char *d;
            if(Num!=3){ MError("\"!!UN:J8\"-wrong number of parameters."); RETURN(0) }
            if(Apply(&t,4,Mp,1)) break;
            if(Mp->n[2]!=0){ // �������� - z var
              if(Apply(&v,4,Mp,2)) break;
              if((v<-10)||(v==0)){ MError("\"!!UN:J8\"- z var out of range (-10...-1,1...1000)."); RETURN(0) }
              if(v>1000)    d=StringSet::GetText(v);
              else if(v>0)  d=ERMString[v-1];
              else          d=ERMLString[-v-1];
              d=ERM2String2(1,d);
            }else{ // �������� - ^�����^
              d=ERM2String(&Mp->m.s[Mp->i],0,&v);
              Mp->i+=v;
            }
            ERMFlags[0]=DoesFileExist(d,t);
            break;
          }
        case 9: // J9/#(modifier)/#(z var) - get path to z var
          { char *d;
            if(Num!=3){ MError("\"!!UN:J9\"-wrong number of parameters."); RETURN(0) }
            if(Apply(&t,4,Mp,1)) break;
            if(Mp->n[2]!=0){ // �������� - z var
              if(Apply(&v,4,Mp,2)) break;
              if((v<-10)||(v>1000)){ MError("\"!!UN:J9\"- z var out of range (-10...-1,1...1000)."); RETURN(0) }
              else if(v>0)  d=ERMString[v-1];
              else          d=ERMLString[-v-1];
            }else{ // �������� - ^�����^
              MError("\"!!UN:J9\"- must be z var."); 
              RETURN(0)
            }
            strncpy(d,GetFolder(t),511);
            break;
          }
        case 10: // J10 - write variable dump
          DumpERMVars("SCRIPT BASED LOGGING (by UN:J10 command)",0);
          break;
        case 11: // 3.59 J11/$ - ��������� ��������� ������� ���� � �������� � �����
          Apply(&MonInfoDlgPopUpSetting,4,Mp,1);
          break;
        case 12:
          { char *d;
            char *MapName="";
            __asm{
              mov   eax,BASE
              mov   eax,[eax]
              add   eax,0x1F6D9
              mov   MapName,eax
            }
            if(Mp->n[1]!=0){ // �������� - z var
              if(Apply(&v,4,Mp,1)) break;
              if((v<-10)||(v>1000)){ MError("\"!!UN:J12\"- z var out of range (-10...-1,1...1000)."); RETURN(0) }
              else if(v>0)  d=ERMString[v-1];
              else          d=ERMLString[-v-1];
            }else{ // �������� - ^�����^
              MError("\"!!UN:J12\"- must be z var."); 
              RETURN(0)
            }
            strncpy(d,MapName,511);
          }
          break;
        default: MError("\"!!UN:J\"-wrong first parameter."); RETURN(0)
      }
      break;
    default:
      MError("\"!!UN:\"-wrong command.");
      RETURN(0)
  }
  RETURN(1)
}

//static char FM_buf[8];
static char FM_buf[10];
char *FindMacro(Mes *mp,int Set)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&mp->m.s[mp->i])
  int  e,s,i,j;
  char ch,cch;

  if(Set) cch='@'; else cch='$';
  for(;mp->i<mp->m.l;mp->i++){
    ch=mp->m.s[mp->i];
    if(ch==' ') continue;
    if(ch== 9 ) continue;
    if(ch!=cch) RETURN(0)
    break;
  }
  for(s=mp->i,e=mp->i+1;e<mp->m.l;e++){
    ch=mp->m.s[e];
    if(ch==0){ MError("Macro was not found."); RETURN(0) }
    if(ch==cch){
      for(i=0,j=s+1;((i<8)&&(j<e));i++,j++) FM_buf[i]=mp->m.s[j];
      for(;i<10;i++) FM_buf[i]=0;
      mp->i=e+1;
      RETURN(FM_buf)
    }
  }
  RETURN(0)
}
char *FindMacro2(char *str,int Set, int *shift)
{
  STARTNC(__FILENUM__*1000000+__LINE__,str)
  int  i,j;
  char ch,cch;

  if(Set) cch='@'; else cch='$';
  for(i=0;;i++){
    ch=str[i];
    if(ch== 0 ){ MError("Macro was not found."); RETURN(0) }
    if(ch==' ') continue;
    if(ch== 9 ) continue;
    if(ch!=cch) RETURN(0)
    break;
  }
  i+=1;
  for(j=0;;i++,j++){
    ch=str[i];
    if(ch==0){ MError("Macro was not found."); RETURN(0) }
    if(ch==cch){
      *shift=i+1;
      for(;j<10;j++) FM_buf[j]=0;
      RETURN(FM_buf)
    }
    if(j>8){ MError("Macro is too long (>8 chars)."); *shift=i+1; RETURN(0) }
    FM_buf[j]=ch;
  }
//  RETURN(0)
//  return 0;
}

int CheckMacro(char *src, char *dst){
  STARTNC(__FILENUM__*1000000+__LINE__,src)
  for(int i=0;i<8;i++) if(dst[i]!=src[i]) RETURN(1)
  RETURN(0)
}

static VarNum GM_vn;
VarNum *GetMacro(char *macro)
{
  STARTNC(__FILENUM__*1000000+__LINE__,macro)
  int i;
  if(macro==0) RETURN(0)
  for(i=1;i<=15;i++){
    if(ERMVarMacro[i-1][0]==0) continue;
    if(CheckMacro(macro,ERMVarMacro[i-1])) continue;
    GM_vn.Type=2; GM_vn.Check=0; GM_vn.Num=i;
    RETURN(&GM_vn)
  }
  for(i=1;i<=10000;i++){
    if(ERMVar2Macro[i-1][0]==0) continue;
    if(CheckMacro(macro,ERMVar2Macro[i-1])) continue;
    GM_vn.Type=3; GM_vn.Check=0; GM_vn.Num=i;
    RETURN(&GM_vn)
  }
  for(i=1;i<=1000;i++){
    if(ERMFlagsMacro[i-1][0]==0) continue;
    if(CheckMacro(macro,ERMFlagsMacro[i-1])) continue;
    GM_vn.Type=0; GM_vn.Check=0; GM_vn.Num=i;
    RETURN(&GM_vn)
  }
  for(i=1;i<=1000;i++){
    if(ERMStringMacro[i-1][0]==0) continue;
    if(CheckMacro(macro,ERMStringMacro[i-1])) continue;
    GM_vn.Type=7; GM_vn.Check=0; GM_vn.Num=i;
    RETURN(&GM_vn)
  }
  //...
  RETURN(0)
}

void SetMacro(char *src, char *dst){
  STARTNC(__FILENUM__*1000000+__LINE__,src)
  for(int i=0;i<8;i++) dst[i]=src[i];
  RETURNV
}
////////////////////
int ERM_Macro(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int  vi;
  char *str;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  if(Num!=1){ MError("\"!!MC:?\"-insufficient parameters."); RETURN(0) }
  VarNum *vnp=&sp->Par[0];
  VarNum *vnp2=&sp->Par[1];
//  if(*(Dword * )vnp2==0) vi=vnp->Num;
  if(vnp2->Num==0 && vnp2->Type==0 && vnp2->IType==0 && vnp2->Check==0) vi=vnp->Num;
  else vi=GetVarVal(vnp2);
  str=FindMacro(Mp,1);
  if(str==0){ MError("Macro defined incorrectly."); RETURN(0) }
  switch(Cmd){
    case 'S': // ����������
      switch(vnp->Type){
        case 0: // ����� - ���� ����
          if((vi<1)||(vi>1000)){ MError("\"!!MC:S\"-flag is out of set (1...1000)."); RETURN(0) }
          SetMacro(str,ERMFlagsMacro[vi-1]);
          break;
        case 2: // f...t
          if((vi<1)||(vi>15)){ MError("\"!!MC:S\"-var is out of set (f...t)."); RETURN(0) }
          SetMacro(str,ERMVarMacro[vi-1]);
          break;
        case 3: // v1...1000
          if((vi<1)||(vi>10000)){ MError("\"!!MC:S\"-var is out of set (v1...v10000)."); RETURN(0) }
          SetMacro(str,ERMVar2Macro[vi-1]);
          break;
        case 4: // w1...100
          if((vi<1)||(vi>200)){ MError("\"!!MC:S\"-var is out of set (w1...w200)."); RETURN(0) }
          SetMacro(str,ERMVarHMacro[ERMW][vi-1]);
          break;
//        case 5: // v1...1000
//        case 6: // v1...1000
        case 7: // z1...500
          if((vi<1)||(vi>1000)){ MError("\"!!MC:S\"-var is out of set (z1...z1000)."); RETURN(0) }
          SetMacro(str,ERMStringMacro[vi-1]);
          break;
        default: MError("\"!!MC:S\"-Wrong var type."); RETURN(0)
      }
      break;
    default: MError("\"!!MC:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}

int ERM_Variable(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  char fl,*txt;
  int  vv,vv2,i,ind;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  VarNum *vnp=&sp->Par[0];
  switch(Cmd){
    case 'S': // ����������
      if(Num!=1){ MError("\"!!VR\"-wrong number of parameters."); RETURN(0) }
      if(vnp->Type==7){  // ������
        if(Mp->n[0]!=0){ // �������� ���� � ������
          vv=GetVarVal(vnp);
          if(Apply(&vv,4,Mp,0)) break;
          SetVarVal(vnp,vv);
        }else{           // �������� ��� �����
          ind=GetVarVal(vnp);
          if((ind<-10)||(ind==0)||(ind>1000)){ MError("\"!!VR:S\"-var is out of set (z-10...-1,1...z1000)."); RETURN(0) }
          if(ind>0) StrCopy(ERMString[ind-1],512,ERM2String(&Mp->m.s[Mp->i],0,&vv));
          else      StrCopy(ERMLString[-ind-1],512,ERM2String(&Mp->m.s[Mp->i],0,&vv));
          Mp->i+=vv;
        }
////      }else if(vnp->Type==9){  // ������
////        if(CheckScope()) break;
////        if(Mp->n[0]!=0){ // �������� ���� � ������
////          vv=GetVarVal(vnp);
////          if(Apply(&vv,4,Mp,0)) break;
////          SetVarVal(vnp,vv);
////        }else{           // �������� ��� �����
////          StrCopy(ERMScope->String[GetVarVal(vnp)-1],512,ERM2String(&Mp->m.s[Mp->i],0,&vv));
////          Mp->i+=vv;
////        }
      }else if(vnp->Type==8){  // floating
        if(Mp->VarI[0].Check!=0){ MError("\"!!VR:S\"-you cannot use get or check syntax for float variable."); RETURN(0) }
        float vf=GetVarValF(&Mp->VarI[0]);
        SetVarValF(vnp,vf);
      }else{
        vv=GetVarVal(vnp);
        if(Apply(&vv,4,Mp,0)) break;
        SetVarVal(vnp,vv);
      }
      break;
    case 'R': // ���������� ���� ���������
      if(Num>2){ MError("\"!!VR\"-wrong number of parameters."); RETURN(0) }
      if(Num==1){
        Apply(&vv,4,Mp,0);
        vv=GetVarVal(vnp)+Random(0,vv);
        SetVarVal(vnp,vv);
      }else{
        Apply(&vv,4,Mp,1);
        __asm{
          mov   ecx,vv;
          mov   eax,0x50C7B0
          call  eax // set random seed
        }
      }
      break;
    case 'T': // ���� ��������� �� �������
      if(Num!=1){ MError("\"!!VR\"-wrong number of parameters."); RETURN(0) }
      Apply(&vv,4,Mp,0);
      vv=GetVarVal(vnp)+TimeRandom(0,vv);
      SetVarVal(vnp,vv);
      break;
    case '+': // ��������
      if(Num!=1){ MError("\"!!VR\"-wrong number of parameters."); RETURN(0) }
      if(vnp->Type==7){  // ������
        if(Mp->n[0]!=0){ // ��������� ���� � ������
          vv=GetVarVal(vnp);
          if(Apply(&vv,4,Mp,0)) break;
          ind=GetVarVal(vnp);
          if((ind<-10)||(ind==0)||(ind>1000)){ MError("\"!!VR:+\"-var is out of set (z-10...-1,1...z1000)."); RETURN(0) }
          if((vv<-10)||(vv==0)){ MError("\"!!VR:+\"-var is out of set (z-10...-1,1...z1000)."); RETURN(0) }
//          if(vv>1000) txt=StringSet::GetText(vv);
//        3.58 ERTification fix
          if(vv>1000) txt=ERM2String(StringSet::GetText(vv),1,0);
          else if(vv>0) txt=ERMString[vv-1];
          else txt=ERMLString[-vv-1];
          if(ind>0){
            StrCanc(ERMString[ind-1],512,ERMString[ind-1],txt);
          }else{
            StrCanc(ERMLString[-ind-1],512,ERMLString[-ind-1],txt);
          }
        }else{           // ��������� ��� �����
          ind=GetVarVal(vnp);
          if((ind<-10)||(ind==0)||(ind>1000)){ MError("\"!!VR:+\"-var is out of set (z-10...-1,1...z1000)."); RETURN(0) }
          if(ind>0) StrCanc(ERMString[ind-1],512,ERMString[ind-1],ERM2String(&Mp->m.s[Mp->i],0,&vv));
          else      StrCanc(ERMLString[-ind-1],512,ERMLString[-ind-1],ERM2String(&Mp->m.s[Mp->i],0,&vv));
          Mp->i+=vv;
        }
////      }else if(vnp->Type==9){  // ������
////        if(CheckScope()) break;
////        if(Mp->n[0]!=0){ // ��������� ���� � ������
////          vv=GetVarVal(vnp);
////          if(Apply(&vv,4,Mp,0)) break;
////          StrCanc(ERMScope->String[GetVarVal(vnp)-1],512,ERMScope->String[GetVarVal(vnp)-1],ERMScope->String[vv-1]);
////        }else{           // ��������� ��� �����
////          StrCanc(ERMScope->String[GetVarVal(vnp)-1],512,ERMScope->String[GetVarVal(vnp)-1],ERM2String(&Mp->m.s[Mp->i],0,&vv));
////          Mp->i+=vv;
////        }
      }else if(vnp->Type==8){  // floating
        float vf=GetVarValF(&Mp->VarI[0]);
        vf=GetVarValF(vnp)+vf;
        SetVarValF(vnp,vf);
      }else{
        Apply(&vv,4,Mp,0);
        vv=GetVarVal(vnp)+vv;
        SetVarVal(vnp,vv);
      }
      break;
    case '-': // �������
      if(Num!=1){ MError("\"!!VR\"-wrong number of parameters."); RETURN(0) }
      if(vnp->Type==8){  // floating
        float vf=GetVarValF(&Mp->VarI[0]);
        vf=GetVarValF(vnp)-vf;
        SetVarValF(vnp,vf);
        break;
      }
      Apply(&vv,4,Mp,0);
      vv=GetVarVal(vnp)-vv;
      SetVarVal(vnp,vv);
//      ERMVar[vi-1]-=vv;
      break;
    case '*': // ��������
      if(Num!=1){ MError("\"!!VR\"-wrong number of parameters."); RETURN(0) }
      if(vnp->Type==8){  // floating
        float vf=GetVarValF(&Mp->VarI[0]);
        vf=GetVarValF(vnp)*vf;
        SetVarValF(vnp,vf);
        break;
      }
      Apply(&vv,4,Mp,0);
      vv=GetVarVal(vnp)*vv;
      SetVarVal(vnp,vv);
//      ERMVar[vi-1]*=vv;
      break;
    case ':': // ������
      if(Num!=1){ MError("\"!!VR\"-wrong number of parameters."); RETURN(0) }
      if(vnp->Type==8){  // floating
        float vf=GetVarValF(&Mp->VarI[0]);
        if(vf==0.0){ Message("Sorry. Division by zero :-)",1); RETURN(0) }
        vf=GetVarValF(vnp)/vf;
        SetVarValF(vnp,vf);
        break;
      }
      Apply(&vv,4,Mp,0);
      if(vv==0){ Message("Sorry. Division by zero :-)",1); RETURN(0) }
      vv=GetVarVal(vnp)/vv;
      SetVarVal(vnp,vv);
//      ERMVar[vi-1]/=vv;
      break;
    case '%': // ������� �� �������
      if(Num!=1){ MError("\"!!VR\"-wrong number of parameters."); RETURN(0) }
      Apply(&vv,4,Mp,0);
      if(vv==0){ Message("Sorry. Division by zero :-)",1); RETURN(0) }
      vv=GetVarVal(vnp)%vv;
      SetVarVal(vnp,vv);
//      ERMVar[vi-1]%=vv;
      break;
    case '&': // ����� �
      if(Num!=1){ MError("\"!!VR\"-wrong number of parameters."); RETURN(0) }
      Apply(&vv,4,Mp,0);
      vv=(Dword)GetVarVal(vnp)&*(Dword *)&vv;
      SetVarVal(vnp,vv);
//      *(Dword *)(&ERMVar[vi-1])&=*(Dword *)&vv;
      break;
    case '|': // ����� ���
      if(Num!=1){ MError("\"!!VR\"-wrong number of parameters."); RETURN(0) }
      Apply(&vv,4,Mp,0);
      vv=(Dword)GetVarVal(vnp)|*(Dword *)&vv;
      SetVarVal(vnp,vv);
//      *(Dword *)(&ERMVar[vi-1])|=*(Dword *)&vv;
      break;
    case '^': // ����� ����. ���
      Message("WARNING!\n The \'!!VR:^$\' command should be changed to \'!!VR:X$\' command.",1);
    case 'X': // ����� ����. ���
      if(Num!=1){ MError("\"!!VR\"-wrong number of parameters."); RETURN(0) }
      if(Apply(&vv,4,Mp,0)) break;
      vv=(Dword)GetVarVal(vnp)^*(Dword *)&vv;
      SetVarVal(vnp,vv);
//      *(Dword *)(&ERMVar[vi-1])^=*(Dword *)&vv;
      break;
    case 'H': // H# ��������� ������ �� ���������� ������ �� ���� #
      if(Num!=1){ MError("\"!!VR\"-wrong number of parameters."); RETURN(0) }
      if(vnp->Type==7){  // ������
        if((Mp->n[0]<1)||(Mp->n[0]>1000)){ MError("\"!!VR:H\"-flag number out of range (1...1000)."); RETURN(0) }
        ind=GetVarVal(vnp);
        if((ind<-10)||(ind==0)||(ind>1000)){ MError("\"!!VR:H\"-var is out of set (z-10...-1,1...z1000)."); RETURN(0) }
        if(ind>0) if(HasText(ERMString[ind-1])==0) fl=0; else fl=1;
        else      if(HasText(ERMLString[-ind-1])==0) fl=0; else fl=1;
        ERMFlags[Mp->n[0]-1]=fl;
////      }else if(vnp->Type==9){  // ������
////        if(CheckScope()) return 0;
////        if((Mp->n[0]<1)||(Mp->n[0]>1000)){ MError("\"!!VR:H\"-flag number out of range (1...1000)."); return 0; }
////        if(HasText(ERMScope->String[GetVarVal(vnp)-1])==0) fl=0; else fl=1;
////        ERMFlags[Mp->n[0]-1]=fl;
      }else{
        MError("\"!!VR:H\"-not a string variable (z#).");
      }
      break;
    case 'C': // C$/$/$/$/$.... ����������
      if(vnp->Type==3){
        ind=GetVarValIndex(vnp);
//        ind=vnp->Num;
        if((ind<1)||((ind+Num)>10000)){ MError("\"!!VR:C\"-v index out of range (1...10000)."); RETURN(0) }
        for(i=0;i<Num;i++){ Apply(&ERMVar2[ind-1+i],4,Mp,(char)i); }
      }else{ MError("\"!!VR:�\"-not a v type variable."); RETURN(0) }
      break;
    case 'U': // search for
     { char *s,*d;
      if(Num!=1){ MError("\"!!VR\"-wrong number of parameters."); RETURN(0) }
      if(vnp->Type==7){  // ������
        ind=GetVarVal(vnp);
        if((ind<-10)||(ind==0)){ MError("\"!!VR:U\"- z var out of range (-10...-1,1...)."); RETURN(0) }
        if(ind>1000)   s=StringSet::GetText(ind);
        else if(ind>0) s=ERMString[ind-1];
        else           s=ERMLString[-ind-1];
        if(Mp->n[0]!=0){ // �������� - z var
          if(Apply(&vv,4,Mp,0)) break;
          if((vv<-10)||(vv==0)){ MError("\"!!SN:S\"- z var out of range (-10...-1,1...)."); RETURN(0) }
          if(vv>1000)    d=StringSet::GetText(vv);
          else if(vv>0)  d=ERMString[vv-1];
          else           d=ERMLString[-vv-1];
          d=ERM2String2(1,d);
        }else{ // �������� - ^�����^
          d=ERM2String(&Mp->m.s[Mp->i],0,&vv);
          Mp->i+=vv;
        }
        ERMFlags[0]=(char)Serch4Substring(s,d);
      }else{
        MError("\"!!VR:U\"-not Z var."); RETURN(0)
      }
      break;
     }
    case 'M': // 3.58 string process
     { char *s,*d;
      if(vnp->Type!=7){  // �� ������
        MError("\"!!VR:M\"-not Z var."); RETURN(0)
      }
      if(Num<2){ MError("\"!!VR:M\"-wrong number of parameters."); RETURN(0) }
      ind=GetVarVal(vnp);
      if((ind<-10)||(ind==0)||(ind>1000)){ MError("\"!!VR:M\"- z var out of range (-10...-1,1...1000)."); RETURN(0) }
      if(ind>0) d=ERMString[ind-1];
      else      d=ERMLString[-ind-1];
      switch(Mp->n[0]){
        case 1: // ����� ��������� �� z2 � #3 ������� #4
          if(Num<4){ MError("\"!!VR:M1\"-wrong number of parameters."); RETURN(0) }
          if(Apply(&vv,4,Mp,1)) break; // z var source
          if((vv<-10)||(vv==0)){ MError("\"!!VR:M1\"- z var (parameter) out of range (-10...-1,1...1000)."); RETURN(0) }
          if(vv>1000)    s=StringSet::GetText(vv);
          else if(vv>0)  s=ERMString[vv-1];
          else           s=ERMLString[-vv-1];
          vv=0;  if(Apply(&vv,4,Mp,2)) break; // start
          vv2=0; if(Apply(&vv2,4,Mp,3)) break; // len
          if(vv>511) vv=511;
          if((vv2+vv)>511) vv2=511-vv;
          for(i=0;i<vv2;i++) d[i]=s[vv+i];
          d[vv2]=0;
          break;
        case 2: // ����� ����� ����� #3 �� z2
         {
          char *tmp,buf[512];
          if(Num<3){ MError("\"!!VR:M2\"-wrong number of parameters."); RETURN(0) }
          if(Apply(&vv,4,Mp,1)) break; // z var source
          if((vv<-10)||(vv==0)){ MError("\"!!VR:M2\"- z var (parameter) out of range (-10...-1,1...1000)."); RETURN(0) }
          if(vv>1000)    s=StringSet::GetText(vv);
          else if(vv>0)  s=ERMString[vv-1];
          else           s=ERMLString[-vv-1];
          StrCopy(buf,512,s);
          tmp=buf;
          vv=0; if(Apply(&vv,4,Mp,2)) break; // token
          d[0]=0;
          for(i=0;i<=vv;i++){
            s=Strtok(tmp);
            if(s==0) break; // no more tokens
            tmp=0;
          }
          StrCopy(d,512,s);
          break;
         }
        case 3: // ������������� ����� �� #2 �� ��������� #3 � ������
          if(Num<2){ MError("\"!!VR:M3\"-wrong number of parameters."); RETURN(0) }
          vv=0; Apply(&vv,4,Mp,1);
          i=10;
          if(Num>2) Apply(&i,4,Mp,2);
          Itoa(vv,d,i);
          break;
        case 4: // VRxxx:M4/$ ��������� ����� ������ � ��������
          if(Num<2){ MError("\"!!VR:M4\"-wrong number of parameters."); RETURN(0) }
          vv=strlen(d); Apply(&vv,4,Mp,1);
          break;
        case 5: // VRxxx:M5/$ ������ �������� ������ � ������
          if(Num<2){ MError("\"!!VR:M5\"-wrong number of parameters."); RETURN(0) }
          vv=StrSkipLead(d,0); Apply(&vv,4,Mp,1);
          break;
        case 6: // VRxxx:M6/$ ��������� �������� ������ � ������
          if(Num<2){ MError("\"!!VR:M6\"-wrong number of parameters."); RETURN(0) }
          vv=StrSkipTrailer(d,strlen(d)); Apply(&vv,4,Mp,1);
          break;
        default:
          MError("\"!!VR:M\"-wrong first parameter."); RETURN(0)
      }
      break;
     }
    case 'V': // 3.58 ����������
     {
      float vf;
      char *s;
      if(Num!=1){ MError("\"!!VR\"-wrong number of parameters."); RETURN(0) }
      if(Apply(&vv,4,Mp,0)) break; // z var source
      if((vv<-10)||(vv==0)){ MError("\"!!VR:V\"- z var (parameter) out of range (-10...-1,1...)."); RETURN(0) }
      if(vv>1000)    s=StringSet::GetText(vv);
      else if(vv>0)  s=ERMString[vv-1];
      else           s=ERMLString[-vv-1];
      switch(vnp->Type){
        case 8:  // floating
//          MError("\"!!VR:V\"-floating point not supported yet.");
//          RETURN(0)
          vf=Atof(s); SetVarValF(vnp,vf);
          break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6: // all integer
          vv=Atoi(s); SetVarVal(vnp,vv);
          break;
        default:
          MError("\"!!VR:V\"-wrong type of var (fl or int only)."); RETURN(0)
      }
      break;
     }
    default:
      MError("\"!!VR:\"-wrong command.");
      RETURN(0)
  }
  RETURN(1)
}

int ERM_Timer(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int  ti,vv;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  VarNum *vnp=&sp->Par[0];
  switch(Cmd){
    case 'S': // ���������� Sfirst/last/period/owner
      if(Num<4){ MError("\"!!TM:S\"-insufficient parameters."); RETURN(0) }
      ti=GetVarVal(vnp);
      if((ti<1)||(ti>100)){ MError("\"!!TM:S\"-timer number is out of range (1...100)."); RETURN(0) }
      vv=ERMTimer[ti-1].FirstDay; Apply(&vv,4,Mp,0); ERMTimer[ti-1].FirstDay=(Word)vv;
      vv=ERMTimer[ti-1].LastDay;  Apply(&vv,4,Mp,1); ERMTimer[ti-1].LastDay=(Word)vv;
      vv=ERMTimer[ti-1].Period;   Apply(&vv,4,Mp,2); ERMTimer[ti-1].Period=(Word)vv;
      vv=ERMTimer[ti-1].Owners;   Apply(&vv,4,Mp,3); ERMTimer[ti-1].Owners=(Word)vv;
      break;
    case 'E': // ��������� ������ Eowner
      if(Num!=1){ MError("\"!!TM:E\"-insufficient parameters."); RETURN(0) }
      ti=GetVarVal(vnp);
      if((ti<1)||(ti>100)){ MError("\"!!TM:E\"-timer number is out of range (1...100)."); RETURN(0) }
      ERMTimer[ti-1].Owners|=(Word)(1<<Mp->n[0]);
      break;
    case 'D': // ��������� ������ Downer
      if(Num!=1){ MError("\"!!TM:D\"-insufficient parameters."); RETURN(0) }
      ti=GetVarVal(vnp);
      if((ti<1)||(ti>100)){ MError("\"!!TM:S\"-timer index is out of range (1...100)."); RETURN(0) }
      ERMTimer[ti-1].Owners&=(Word)~(1<<Mp->n[0]);
      break;
    default:
      MError("\"!!TM:\"-wrong command.");
      RETURN(0)
  }
  RETURN(1)
}

#define ERMOBJECTS 1000
static struct _ERM_Object_{
  char  Used;        // 1-����, 0-��������
  Word  HintVar;     // ���������� ��������� 0-���,1...
  char  Disabled[8]; // 1-dis 0-en �� �������
  char  AMessage[8][2]; // =1-���������, ���� ���������
// 0x00000000 - �������
// 0x1tttssss - ��� �������
// 0x200pttss - ���������� �������
// 0x4w - ���������� w
// 0x8v - ���������� v
////// 0x6a - ��������
  Dword PosMix;      // ��������� ������� �� �����
} ERM_Object[ERMOBJECTS];

_ERM_Object_ *FindObj(Dword MixPos)
{
  #include "templ.h"
  int i;

  for(i=0;i<ERMOBJECTS;i++){
    if(ERM_Object[i].Used==0) continue;
    if(ERM_Object[i].PosMix==MixPos) RETURN(&ERM_Object[i])
  }
  RETURN(0)
}

_ERM_Object_ *FindObjExt(_MapItem_ *Mp,int x,int y,int l)
{
  #include "templ.h"
  int wnum,wval,vnum,vval;
  int i,c,ind;
  _Square_ *sqp;
  int alltype=((Mp->OType&0xFF)<<8)+(Mp->OSType&0xFF);
  _ERM_Object_ *op;
  for(c=0;c<2;c++){
    if(c==1) alltype=((Mp->OType&0xFF)<<8)+0xFF; // ��� ���� ��������
    for(i=0;i<ERMOBJECTS;i++){
      op=&ERM_Object[i];
      if(op->Used==0) continue;
      switch(op->PosMix&0xF0000000){
        case 0: break;
        case 0x20000000: // position->number (0...15)
          if(alltype!=(int)(op->PosMix&0x0000FFFF)) continue; // ������
          sqp=&Square[x][y][l];
          if(sqp->Number==((op->PosMix&0x000F0000)>>16)) RETURN(op)
          break;
        case 0x40000000: // w (0...99) = (0...32)
          if(alltype!=(int)(op->PosMix&0x0000FFFF)) continue; // ������
          wnum=(op->PosMix&0x007F0000)>>16;
          if(wnum>99){ MError("Hint W variable out of range (>100)"); RETURN(0)}
          wval=(op->PosMix&0x0F800000)>>23;
//          asm{ mov eax,0x698B70; mov eax,[eax]; }
//          hp=(_Hero_ *)_EAX;
//          if(hp==0) continue;
//          if(ERMVarH[hp->Number][wnum]==wval) return op;
          ind=CurrentUser()*0x168;
          __asm{
            mov   eax,0x699538
            mov   eax,[eax]
            add   eax,0x20AD4
            add   eax,ind
            mov   eax,[eax]
            mov   ind,eax
          }
          if(ind==-1) continue; // ��� ��������� �����
          if(ERMVarH[ind][wnum]==wval) RETURN(op)
          break;
        case 0x80000000: // v  (1...1000) = (0...3)
          if(alltype!=(int)(op->PosMix&0x0000FFFF)) continue; // ������
          vnum=(op->PosMix&0x03FF0000)>>16;
          if(vnum>9999){ MError("Hint V variable out of range (>10000)"); RETURN(0)}
          vval=(op->PosMix&0x0C000000)>>26;
          if(ERMVar2[vnum]==vval) RETURN(op)
          break;
        case 0x10000000: // ������ �� ����/�������
          if(alltype!=(int)(op->PosMix&0x0000FFFF)) continue; // ������
          RETURN(op)
      }
    }
  }
  RETURN(0)
}
/*
_ERM_Object_ *FindObjExtArt(int artnum)
{
  int i;
  _ERM_Object_ *op;
  for(i=0;i<ERMOBJECTS;i++){
    op=&ERM_Object[i];
    if(op->Used==0) continue;
    switch(op->PosMix&0xF0000000){
      case 0x60000000: // ��������
        if(artnum!=(op->PosMix&0x0000FFFF)) continue; // ������
        return op;
    }
  }
  return 0;
}
*/
_ERM_Object_ *AddObj(Dword MixPos)
{
  #include "templ.h"
  int i,j;
  _ERM_Object_ *obj;

  obj=FindObj(MixPos);
  if(obj!=0) RETURN(obj)
  for(i=0;i<ERMOBJECTS;i++){
    if(ERM_Object[i].Used!=0) continue;
    for(j=0;j<8;j++) ERM_Object[i].Disabled[j]=0;
    ERM_Object[i].PosMix=MixPos;
    ERM_Object[i].Used=1;
    RETURN(&ERM_Object[i])
  }
  MError("Cannot add more objects.");
  RETURN(0)
}

void DelObj(_ERM_Object_ *obj)
{
  #include "templ.h"
  int j;

  if(obj==0) RETURNV
  obj->Used=0;
  obj->HintVar=0;
  for(j=0;j<8;j++){
    obj->Disabled[j]=0;
    obj->AMessage[j][0]=0;
    obj->AMessage[j][1]=0;
  }
  obj->PosMix=0;
  RETURNV
}

void DelObjPos(Dword MixPos)
{
  #include "templ.h"
  DelObj(FindObj(MixPos));
  RETURNV
}
/*
Dword GetDinMixPos(_ToDo_ *sp)
{
  Dword MixPos;
  int x,y,l,ind;
  if(sp->Pointer2==1){
    VarNum *vnp=(VarNum *)&sp->Pointer;
    ind=GetVarVal(vnp);
    if((ind<1)||(ind>(1000-2))){ MError("Index of var for Dinamic position is out of range (1...998)."); return 0; }
    x=ERMVar2[ind-1];
    y=ERMVar2[ind];
    l=ERMVar2[ind+1];
    MixPos=PosMixed(x,y,l);
  }else{
    MixPos=sp->Pointer;
  }
  return MixPos;
}
*/
Dword GetDinMixPos(_ToDo_ *sp)
{
  #include "templ.h"
  Dword MixPos;
  int x,y,l,ind;
  switch(sp->ParSet){
    case 1: // ��������� ������
//      VarNum *vnp=&sp->Par[0];
      ind=GetVarVal(&sp->Par[0]);
      if((ind<1)||(ind>(10000-2))){ MError("Index of var for Dinamic position is out of range (1...9998)."); RETURN(0) }
      x=ERMVar2[ind-1]; y=ERMVar2[ind]; l=ERMVar2[ind+1];
      MixPos=PosMixed(x,y,l);
      break;
    case 3: // x/y/l
      x=GetVarVal(&sp->Par[0]);
      y=GetVarVal(&sp->Par[1]);
      l=GetVarVal(&sp->Par[2]);
      MixPos=PosMixed(x,y,l);
      break;
    default: // t/st
      MError("Not realized yet."); RETURN(0)
/*
    VarNum *vnp=(VarNum *)&sp->Par[0];
    ind=GetVarVal(vnp);
    MixPos=ind<<16;
    vnp=(VarNum *)&sp->Par[1];
    ind=GetVarVal(vnp);
    MixPos+=ind&0xFFFF;
*/
    }
  RETURN(MixPos)
}

int ERM_HintType(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  _ERM_Object_ *obj;
  Dword alltype;
  int ind,val,z;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  VarNum *vnp=&sp->Par[0];
  int type=GetVarVal(vnp);
  type&=0xFF;
  vnp=&sp->Par[1];
  int subtype=GetVarVal(vnp);
  if(subtype==-1) subtype=0xFF;
  subtype&=0xFF;
  switch(Cmd){
    case 'T': // Tz (z=0-delete)
//      if(Num<1){ MError("\"!!HT:T\"-insufficient parameters."); return 0; }
      alltype=(type<<8)+subtype+0x10000000;
      obj=AddObj(alltype);
      if(obj==0){ MError("Cannot add more objects"); RETURN(0) }
      Apply(&z,4,Mp,0);
      if((z<0)||(z>32000)){ MError("\"!!HT:T\"-wrong Z var index (0,1...32000)."); RETURN(0) }
      if(z==0) DelObj(obj);
      else obj->HintVar=(Word)z;
      break;
    case 'P': // Pval/z (z=0-delete) position->number (0...15)
      if(Num<2){ MError("\"!!HT:P\"-insufficient parameters."); RETURN(0) }
      if(Apply(&val,4,Mp,0)) RETURN(0)
      if((val<0)||(val>15)){ MError("\"!!HT:P\"-Number value out of range (0...15)."); RETURN(0) }
      alltype=(type<<8)+subtype+0x20000000+((val&0x0F)<<16);
      obj=AddObj(alltype);
      if(obj==0){ MError("Cannot add more objects"); RETURN(0) }
      Apply(&z,4,Mp,1);
      if((z<0)||(z>32000)){ MError("\"!!HT:P\"-wrong Z var index (0,1...32000)."); RETURN(0) }
      if(z==0) DelObj(obj);
      else obj->HintVar=(Word)z;
      break;
    case 'W': // Wind/val/z (z=0-delete) w (0...99) = (0...32)
      if(Num<3){ MError("\"!!HT:W\"-insufficient parameters."); RETURN(0) }
      if(Apply(&ind,4,Mp,0)) RETURN(0)
      if((ind<1)||(ind>100)){ MError("\"!!HT:W\"- W index value out of range (1...100)."); RETURN(0) }
      if(Apply(&val,4,Mp,1)) RETURN(0)
      if((val<0)||(val>32)){ MError("\"!!HT:W\"- W value out of range (0...32)."); RETURN(0) }
      alltype=(type<<8)+subtype+0x40000000+(((ind-1)&0x7F)<<16)+((val&0x1F)<<23);
      obj=AddObj(alltype);
      if(obj==0){ MError("Cannot add more objects"); RETURN(0) }
      Apply(&z,4,Mp,2);
      if((z<0)||(z>32000)){ MError("\"!!HT:W\"-wrong Z var index (0,1...32000)."); RETURN(0) }
      if(z==0) DelObj(obj);
      else obj->HintVar=(Word)z;
      break;
    case 'V': // Vind/val/z (z=0-delete) v  (1...1000) = (0...3)
      if(Num<3){ MError("\"!!HT:V\"-insufficient parameters."); RETURN(0) }
      if(Apply(&ind,4,Mp,0)) RETURN(0)
      if((ind<1)||(ind>1000)){ MError("\"!!HT:V\"- V index value out of range (1...1000)."); RETURN(0) }
      if(Apply(&val,4,Mp,1)) RETURN(0)
      if((val<0)||(val>3)){ MError("\"!!HT:V\"- V value out of range (0...3)."); RETURN(0) }
      alltype=(type<<8)+subtype+((((ind-1)&0x3FF)<<16)&0x3FF0000)+(((val&0x3)<<26)&0x0C000000);
      alltype|=0x80000000;
      obj=AddObj(alltype);
      if(obj==0){ MError("Cannot add more objects"); RETURN(0) }
      Apply(&z,4,Mp,2);
      if((z<0)||(z>32000)){ MError("\"!!HT:V\"-wrong Z var index (0,1...32000)."); RETURN(0) }
      if(z==0) DelObj(obj);
      else obj->HintVar=(Word)z;
      break;
    default:
      MError("\"!!HT:\"-wrong command.");
      RETURN(0)
  }
  RETURN(1)
}

int ERM_SetObject(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  char en,fl;
  int  i,owner;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  _ERM_Object_ *obj=0;

  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  switch(Cmd){
    case 'T': // T$ ���
      Apply(&mip->OType,2,Mp,0);
      break;
    case 'U': // U$ ������
      Apply(&mip->OSType,2,Mp,0);
      break;
    case 'C': // C$ ���.�����
      Apply(&mip->SetUp,4,Mp,0);
      break;
    default:
//      obj=AddObj(MixPos); if(obj==0) RETURN(0)
      en=0;
      switch(Cmd){
        case 'M': // Mowner/auto/next
          if(Num<3){ MError("\"!!OB:M\"-insufficient parameters."); RETURN(0) }
          owner=Mp->n[0];
          if((owner<-1)||(owner>7)){ MError("\"!!OB:M\"-owner out of range (-1...7)."); RETURN(0) }
          char ames[8][2]; SetMem(ames,sizeof(ames),0);
          fl=0;
          if(owner==-1){ // ��� ����
            for(i=0;i<8;i++){
              if(Apply(&ames[i][0],1,Mp,1)) fl=1;
              if(Apply(&ames[i][1],1,Mp,2)) fl=1;
            }
            if(fl) break;
            // 3.59 fix we are her only if not check syntax
            obj=AddObj(MixPos); if(obj==0) RETURN(0)
            for(i=0;i<8;i++){
              obj->AMessage[i][0]=ames[i][0];
              obj->AMessage[i][1]=ames[i][1];
            }
          }else{ // for a player
            if(Apply(&ames[owner][0],1,Mp,1)) fl=1;
            if(Apply(&ames[owner][1],1,Mp,2)) fl=1;
            if(fl) break;
            // 3.59 fix we are her only if not check syntax
            obj=AddObj(MixPos); if(obj==0) RETURN(0)
            obj->AMessage[owner][0]=ames[owner][0];
            obj->AMessage[owner][1]=ames[owner][1];
          }
          break;
        case 'D': // D# ���������
          en=1;
        case 'E': // E# ���������
          if(Num!=1){ MError("\"!!OB:E\" or \"!!OB:D\"-insufficient parameters."); RETURN(0) }
          owner=Mp->n[0];
          if(owner==-1) owner=CurrentUser();
          if((owner<0)||(owner>7)){ MError("\"!!OB:E\" or \"!!OB:D\"-owner out of range (-1...7)."); RETURN(0) }
          obj=AddObj(MixPos); if(obj==0) RETURN(0)
          obj->Disabled[owner]=en;
          break;
        case 'S': // S ��������� ����
          en=1;
        case 'R': // R ��������� ����
//          if(Num!=1){ Error(); return 0; }
          obj=AddObj(MixPos); if(obj==0) RETURN(0)
          for(i=0;i<8;i++) obj->Disabled[i]=en;
          break;
        case 'H':{ // H$ ���������� ���������
          short hintvar=0;
          obj=FindObj(MixPos); 
          if(obj!=0){ // there is an object
            hintvar=obj->HintVar;
          }
          if(Apply(&hintvar,2,Mp,0)) break;
//          Apply(&obj->HintVar,2,Mp,0);
          // 3.59 fix we are her only if not check syntax
          obj=AddObj(MixPos); if(obj==0) RETURN(0)
          obj->HintVar=hintvar;
          break;}
        case 'B': // B ������� ���������
          DelObjPos(MixPos);
//          DelObj(obj);
          break;
        default:
          MError("\"!!OB:\"-wrong command.");
          RETURN(0)
      }
  }
  RETURN(1)
}
////////////////////////
static struct _ERM_Hero_{
  Word  HintVar;     // ���������� ��������� 0-���,1...
  char  Disabled[8]; // 1-dis 0-en �� �������
} ERM_Hero[HERNUM];

int ERM_SetHero(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  char en;
  int  i,owner;
  int  ind=GetVarVal(&sp->Par[0]);

  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  if((ind<0)||(ind>=HERNUM)){ MError("\"!!HO:\"-number of hero out of range."); RETURN(0) }
  en=0;
  switch(Cmd){
    case 'D': // D# ���������
      en=1;
    case 'E': // E# ���������
      if(Num!=1){ MError("\"!!HO:D\" or \"!!HO:E\"-insufficient parameters."); RETURN(0) }
      owner=Mp->n[0];
      if(owner==-1) owner=CurrentUser();
      if((owner<0)||(owner>7)){ MError("\"!!HO:D\" or \"!!HO:E\"-owner out of range (-1...7)."); RETURN(0) }
      ERM_Hero[ind].Disabled[owner]=en;
      break;
    case 'S': // S ��������� ����
      en=1;
    case 'R': // R ��������� ����
      for(i=0;i<8;i++) ERM_Hero[ind].Disabled[i]=en;
      break;
    case 'H': // H$ ���������� ���������
      Apply(&ERM_Hero[ind].HintVar,2,Mp,0);
      break;
    default:
      MError("\"!!HO:\"-wrong command.");
      RETURN(0)
  }
  RETURN(1)
}
////////////////////////
int ERM_Owner(char Cmd,int Num,_ToDo_* /*sp*/,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int   i,j,owner,res,val,ind,act;
  _Hero_ *hp;
  _PlayerSetup_ *ps;
  char *pho=GetHOTableBase();
  Byte *str,vb;

  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  switch(Cmd){
    case 'R': // R#1/#2/$3 ������� #1(0...7,-1-�������)
      if(Num<3) { MError("\"!!OW:R\"-insufficient parameters."); RETURN(0) }
      owner=Mp->n[0]; res=Mp->n[1];
      if(owner==-1) owner=CurrentUser();
      if((owner<0)||(owner>7)){ MError("\"!!OW:R\"-owner out of range (-1...7)."); RETURN(0) }
      if(res==7){ // Mithrill
        val=MithrillVal[owner]; Apply(&val,4,Mp,2); MithrillVal[owner]=val;
      }else{
        val=GetRes(owner,res); if(val==-1){ MError("\"!!OW:R\"-resourse out of range."); RETURN(0) }
        if(Apply(&val,4,Mp,2)) break;
        SetRes(owner,res,val);
      }
      break;
    case 'D': // D#1/#2 ������� #1(0...7,-1-�������,-2-����)
              //  #2 = 0...127,-1 -��������
      if(Num<2) { MError("\"!!OW:D\"-insufficient parameters."); RETURN(0) }
      owner=Mp->n[0];
      vb=(Byte)Mp->n[1];
      if(owner==-2){ //��� ����
        //004F356B C60307 mov  byte ptr [ebx],07
        __asm{
          mov  ecx,0x4F356D
          mov  al,vb
          mov  [ecx],al
        }
      }else{ //���������
        str=GamerStruc(owner);
        str[0x3D]=vb;
      }
      break;
    case 'I': // Iowner/AIgm(/Killed) - AI ��� �������
      if(Num<2) { MError("\"!!OW:I\"-insufficient parameters."); RETURN(0) }
      owner=Mp->n[0];
      if(owner==-1) owner=CurrentUser();
      if((owner<0)||(owner>7)){ MError("\"!!OW:I\"-owner out of range (-1...7)."); RETURN(0) }
      val=IsAI(owner);
      Apply(&val,4,Mp,1);
      SetAI(owner,val);
      if(Num>2){
        val=IsPlayerKilled(owner,-1);
        if(Apply(&val,4,Mp,2)) break;
        IsPlayerKilled(owner,val);
      }
      break;
    case 'G': // Gowner/this - ������� ����� - ���, ��� �� �������� ��� ���
      if(Num!=2) { MError("\"!!OW:G\"-insufficient parameters."); RETURN(0) }
      owner=Mp->n[0];
      if(owner==-1) owner=CurrentUser();
      if((owner<0)||(owner>7)){ MError("\"!!OW:G\"-owner out of range (-1...7)."); RETURN(0) }
      val=IsThis(owner); Apply(&val,4,Mp,1); ThisIs(owner,val);
      break;
    case 'T': // Towner/team - �������
      if(Num!=2) { MError("\"!!OW:T\"-insufficient parameters."); RETURN(0) }
      owner=Mp->n[0];
      if(owner==-1) owner=CurrentUser();
      if((owner<0)||(owner>7)){ MError("\"!!OW:T\"-owner out of range (-1...7)."); RETURN(0) }
      val=GetTeam(owner); Apply(&val,4,Mp,1); SetTeam(owner,(char)val);
      break;
    case 'H': // Howner/ind - ��������� � ��������� ������ ������
      if(Num<2){ MError("\"!!OW:H\"-insufficient parameters."); RETURN(0) }
      owner=Mp->n[0];
      ind=Mp->n[1];
      if(owner==-1) owner=CurrentUser();
      if((owner<0)||(owner>7)){ MError("\"!!OW:H\"-owner out of range (-1...7)."); RETURN(0) }
      if((ind<1)||(ind>10000)){ MError("\"!!OW:H\"-var index out of range (1...10000)."); RETURN(0) }
      if(Num==3){
        j=Mp->n[2];
        if(j<0){ MError("\"!!OW:H\"-third parameter below zero."); RETURN(0) }
        if(j==0){
          for(i=val=0;i<HERNUM;i++){
            hp=GetHeroStr(i); if(hp->Owner!=owner) continue;
            ++val;
          }
          ERMVar2[ind-1]=val;
        }else{
          for(i=val=0;i<HERNUM;i++){
            hp=GetHeroStr(i); if(hp->Owner!=owner) continue;
            ++val;
            if(val==j){ ERMVar2[ind-1]=i; break; }
          }
        }
      }else{
        for(i=val=0,j=ind+1;i<HERNUM;i++){
          hp=GetHeroStr(i);
          if(hp->Owner!=owner) continue;
          if(j>10000){ MError("\"!!OW:H\"-var index goes out of range (1...10000)."); RETURN(0) }
          ERMVar2[j-1]=i; ++j;
          ++val;
        }
        ERMVar2[ind-1]=val;
      }
      break;
    case 'C': // C?owner - ������� �����
      if(Num!=1) { MError("\"!!OW:C\"-wrong parameters number."); RETURN(0) }
      val=CurrentUser();
      Apply(&val,4,Mp,0);
      break;
    case 'K': // Kowner/keymaster/state - ��������� �����������
      if(Num<3){ MError("\"!!OW:K\"-wrong parameters number."); RETURN(0) }
      if(Apply(&owner,4,Mp,0)){ MError("\"!!OW:K\"-cannot get or check owner."); RETURN(0) }
      if(owner==-1) owner=CurrentUser();
      if((owner<0)||(owner>7)){ MError("\"!!OW:K\"-owner out of range (-1...7)."); RETURN(0) }
      if(Apply(&ind,4,Mp,1)){ MError("\"!!OW:K\"-cannot get or check keymaster number."); RETURN(0) }
      if((ind<0)||(ind>7)){ MError("\"!!OW:K\"-keymaster out of range (-1...7)."); RETURN(0) }
      val=GetKeyMaster(owner,ind); Apply(&val,4,Mp,2); SetKeyMaster(owner,ind,val);
      break;
    case 'O': // Oowner/number/#1/#2/#3/#4/#5/#6/#7/#8
      if(Apply(&owner,4,Mp,0)){ MError("\"!!OW:O\"-cannot get or check owner."); RETURN(0) }
      if(owner==-1) owner=CurrentUser();
      if((owner<0)||(owner>7)){ MError("\"!!OW:O\"-owner out of range (-1...7)."); RETURN(0) }
      ps=GetPlayerSetup(owner);
      if(ps==0){ MError("\"!!OW:O\"-cannot get PlayerSetup structure."); RETURN(0) }
      if(Num==4){ // O#owner/#action/#hero_ind_to be/#dummy first
        if(Apply(&act,4,Mp,1)) break; // action
        if(Apply(&ind,4,Mp,2)) break; // index
        __asm{
          mov    eax,0x6992B8
          mov    eax,[eax]
          mov    eax,[eax+0x44]
          mov    eax,[eax+0x64]
          add    ind,eax
        }
        if(ind>=ps->HasHeroes) break;
        if(ind<0) break;
        switch(act){
          case 1: // to first
            val=ps->Heroes[ind];
            for(i=ind+1;i<ps->HasHeroes;i++){ // delete
              ps->Heroes[i-1]=ps->Heroes[i];
            }
            for(i=ps->HasHeroes-1;i>0;i--){ // add
              ps->Heroes[i]=ps->Heroes[i-1];
            }
            ps->Heroes[0]=val;
            break;
          case 2: // one slot up
            if(ind<1) break;
            val=ps->Heroes[ind];
            ps->Heroes[ind]=ps->Heroes[ind-1];
            ps->Heroes[ind-1]=val;
            break;
          case 3: // one slot down
            if(ind>=(ps->HasHeroes-1)) break;
            val=ps->Heroes[ind];
            ps->Heroes[ind]=ps->Heroes[ind+1];
            ps->Heroes[ind+1]=val;
            break;
        }
        break;
      }else if(Num==3){ // O#owner/#ind/?h
        if(Apply(&ind,4,Mp,1)) break; // index
        __asm{
          mov    eax,0x6992B8
          mov    eax,[eax]
          mov    eax,[eax+0x44]
          mov    eax,[eax+0x64]
          add    ind,eax
        }
//        ind+=ps->TopHeroInd;
        if(ind>=ps->HasHeroes) val=-1; // no
        else{
          val=ps->Heroes[ind];
        }
        Apply(&val,4,Mp,2); 
        break;
      }else if(Num<10) { MError("\"!!OW:O\"-insufficient parameters."); RETURN(0) }
      Apply(&ps->HasHeroes,1,Mp,1);
      for(i=0;i<8;i++){
        Apply(&ps->Heroes[i],4,Mp,(char)(i+2));
      }
      break;
    case 'V': // Vowner/heroleft/heroright to hire in a tavern
      if(Num!=3) { MError("\"!!OW:V\"-insufficient parameters."); RETURN(0) }
      owner=Mp->n[0];
      if(owner==-1) owner=CurrentUser();
      if((owner<0)||(owner>7)){ MError("\"!!OW:V\"-owner out of range (-1...7)."); RETURN(0) }
      ps=GetPlayerSetup(owner);
      i=ps->THeroL; j=ps->THeroR;
      if(i!=-1) pho[i]=-1; if(j!=-1) pho[j]=-1;
      Apply(&i,4,Mp,1); Apply(&j,4,Mp,2);
      if(i!=-1) pho[i]=0x40; if(j!=-1) pho[j]=0x40;
      ps->THeroL=i; ps->THeroR=j;
      break;
    case 'A': // A#/$ (0...N,-1) Hero number
      if(Num<2) { MError("\"!!OW:A\"-insufficient parameters."); RETURN(0) }
      if(Apply(&owner,4,Mp,0)){ MError("\"!!OW:A\"-cannot get or check owner."); RETURN(0) }
      if(owner==-1) owner=CurrentUser();
      if((owner<0)||(owner>7)){ MError("\"!!OW:A\"-owner out of range (-1...7)."); RETURN(0) }
      ps=GetPlayerSetup(owner);
      if(ps==0){ MError("\"!!OW:A\"-cannot get PlayerSetup structure."); RETURN(0) }
      Apply(&ps->CurHero,4,Mp,1);
      break;
    case 'N': // N#/$ (0...N,-1) Town number
      if(Apply(&owner,4,Mp,0)){ MError("\"!!OW:N\"-cannot get or check owner."); RETURN(0) }
      if(owner==-1) owner=CurrentUser();
      if((owner<0)||(owner>7)){ MError("\"!!OW:N\"-owner out of range (-1...7)."); RETURN(0) }
      ps=GetPlayerSetup(owner);
      if(ps==0){ MError("\"!!OW:N\"-cannot get PlayerSetup structure."); RETURN(0) }
      if(Num==4){ // N#owner/#action/#town_ind_to be first/dummy
        if(Apply(&act,4,Mp,1)) break; // action
        if(Apply(&ind,4,Mp,2)) break; // index
        __asm{
          mov    eax,0x6992B8
          mov    eax,[eax]
          mov    eax,[eax+0x44]
          mov    eax,[eax+0x68]
          add    ind,eax
        }
        if(ind>=ps->HasTowns) break;
        if(ind<0) break;
        switch(act){
          case 1: // to first
            val=ps->Towns[ind];
            for(i=ind+1;i<ps->HasTowns;i++){ // delete
              ps->Towns[i-1]=ps->Towns[i];
            }
            for(i=ps->HasTowns-1;i>0;i--){ // add
              ps->Towns[i]=ps->Towns[i-1];
            }
            ps->Towns[0]=val;
            break;
          case 2: // one slot up
            if(ind<1) break;
            val=ps->Towns[ind];
            ps->Towns[ind]=ps->Towns[ind-1];
            ps->Towns[ind-1]=val;
            break;
          case 3: // one slot down
            if(ind>=(ps->HasTowns-1)) break;
            val=ps->Towns[ind];
            ps->Towns[ind]=ps->Towns[ind+1];
            ps->Towns[ind+1]=val;
            break;
        }
        break;
      }else if(Num==3){ // N#owner/#ind/?t
        if(Apply(&ind,4,Mp,1)) break; // index
        __asm{
          mov    eax,0x6992B8
          mov    eax,[eax]
          mov    eax,[eax+0x44]
          mov    eax,[eax+0x68]
          add    ind,eax
        }
//        ind+=ps->TopTownInd;
        if(ind>=ps->HasTowns) val=-1; // no
        else{
          val=ps->Towns[ind];
        }
        Apply(&val,4,Mp,2);
        break;
      }else if(Num<2) { MError("\"!!OW:N\"-insufficient parameters."); RETURN(0) }
      Apply(&ps->CurTown,1,Mp,1);
      break;
    case 'W': // W#/$(/$) Town number by position and full towns number
      if(Num<2) { MError("\"!!OW:W\"-insufficient parameters."); RETURN(0) }
      if(Apply(&owner,4,Mp,0)){ MError("\"!!OW:W\"-cannot get or check owner."); RETURN(0) }
      if(owner==-1) owner=CurrentUser();
      if((owner<0)||(owner>7)){ MError("\"!!OW:W\"-owner out of range (-1...7)."); RETURN(0) }
      ps=GetPlayerSetup(owner);
      if(ps==0){ MError("\"!!OW:W\"-cannot get PlayerSetup structure."); RETURN(0) }
      if(Num==2){ // ������ ���������� �������
        Apply(&ps->HasTowns,1,Mp,1);
      }else{ // >2 ����� ����������� ������ (�� �������)
        if(Apply(&i,4,Mp,1)){ MError("\"!!OW:W\"-cannot get or check town list number."); RETURN(0) }
        if((i<0)||(i>=48)){ MError("\"!!OW:W\"-town list number out of range (0...47)."); RETURN(0) }
        Apply(&ps->Towns[i],1,Mp,2);
      }
      break;
    case 'S': // S#/#
      if(Apply(&ind,4,Mp,0)) break;
      switch(ind){
        case 1: // S1/#spell - �������� ����� �� ����� ��� ��� �����
          if(Apply(&val,4,Mp,1)) break;
          CastAdvSpell(val);
          break;
        case 2: // S2/X - ����� ����� �� ����� ��� �������� �����
          ChooseAdvSpell();
          break;
      }
      break;
    default:
      MError("\"!!OW\"-wrong command.");
      RETURN(0)
  }
  RETURN(1)
}

int ERM_Mine(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int  owner;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  _CMine_ *msp=(_CMine_ *)mip;
  _Mine_  *mp;

  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  int tp=CheckPlace4Hero(mip,(Dword **)&msp);
  if((tp!=53)&&(tp!=42)){ MError("\"!!MN:\"-not a mine."); RETURN(0) }
  mp=GetMineStr(msp->Num);
  if(mp==0){ MError("\"!!MN:\"-mine is not found in internal structures."); RETURN(0) }
  switch(Cmd){
    case 'O': // O$ Owner O$/1 no redraw
      if(Mp->VarI[0].Check==0){ // ���������
        owner=Mp->n[0]; if(owner==-2) owner=CurrentUser();
        if((owner<-1)||(owner>7)){ MError("\"!!MN:O\"-Owner out of range (-1...7)."); RETURN(0) }
        Mp->n[0]=owner;
      }
      Apply(&mp->Owner,1,Mp,0);
      if(Num<2) RedrawMap();
      break;
    case 'R': // R$ Resource type R$/1
      if(Mp->VarI[0].Check==0){ // ���������
        if(((Mp->n[0]<0)||(Mp->n[0]>6))&&(Mp->n[0]!=100)){ MError("\"!!MN:R\"-Resource type out of range (0...6,100)."); RETURN(0) }
      }
      Apply(&mp->ResNum,1,Mp,0);
      if(Num<2) RedrawMap();
      break;
    case 'M': // M#/$/$ Monsters
      if(Num<3){ MError("\"!!MN:M\"-wrong syntax."); RETURN(0) }
      if((Mp->n[0]<0)||(Mp->n[0]>7)){ MError("\"!!MN:M\"-wrong slot number (0...7)."); RETURN(0) }
      Apply(&mp->GType[Mp->n[0]],4,Mp,1);
      Apply(&mp->GNumb[Mp->n[0]],4,Mp,2);
      break;
    default:
      MError("\"!!MN:\"-wrong command.");
      RETURN(0)
  }
  RETURN(1)
}
int ERM_SetScoolar(char Cmd,int/* Num*/,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int v;
  Dword MixPos=GetDinMixPos(sp);
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  _MapItem_ *mip=GetMapItem2(MixPos);
  _CSchoolar_ *stp=(_CSchoolar_ *)mip;
  if(mip->OType!=0x51/*)||(mip->OType!=0x22)*/){ MError("\"!!SC:\"-not a schoolar."); RETURN(0) }
  switch(Cmd){
    case 'T': // T# - ��� 1,2,3 (3)
      v=stp->Type; Apply(&v,4,Mp,0); stp->Type=(Word)v; break;
    case 'P': // P# - ����. ������ (3)
      v=stp->PSkill; Apply(&v,4,Mp,0); stp->PSkill=(Word)v; break;
    case 'S': // S# - ����. ������ (7)
      v=stp->SSkill; Apply(&v,4,Mp,0); stp->SSkill=(Word)v; break;
    case 'L': // L# - ���������� (11)
      v=stp->Spell;  Apply(&v,4,Mp,0); stp->Spell=(Word)v;  break;
    default: MError("\"!!SC:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_SetChest(char Cmd,int/* Num*/,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int v;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  _CChest_ *stp=(_CChest_ *)mip;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  if(mip->OType!=101){ MError("\"!!CH:\"-not a chest."); RETURN(0) }
  switch(Cmd){
    case 'S': // S# ��������=1 ��� ������=0
      v=stp->HasArt; Apply(&v,4,Mp,0); stp->HasArt=(Word)v; break;
    case 'A': // A# ����� ���.
      v=stp->ArtNum; Apply(&v,4,Mp,0); stp->ArtNum=(Word)v; break;
    case 'B': // B# ���-�� ������
      v=stp->Bonus; Apply(&v,4,Mp,0);  stp->Bonus=(Word)v; break;
    default: MError("\"!!CH:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_SetWTomb(char Cmd,int/* Num*/,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int v;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  _CWTomb_ *stp=(_CWTomb_ *)mip;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  int tp=CheckPlace4Hero(mip,(Dword **)&stp);
  if(tp!=0x6C){ MError("\"!!WT:\"-not a warrior tomb."); RETURN(0) }
  switch(Cmd){
    case 'A': // A# ����� ���. (10)
      v=stp->ArtNum; Apply(&v,4,Mp,0); stp->ArtNum=(Word)v; break;
    case 'S': // S# ���. ����=1 ��� ���=0 (1)
      v=stp->HasArt; if(Apply(&v,4,Mp,0)) break; stp->HasArt=(Word)v; stp->Whom=0; break;
    default: MError("\"!!WT:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_SetKTree(char Cmd,int/* Num*/,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int v;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  _CKTree_ *stp=(_CKTree_ *)mip;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  int tp=CheckPlace4Hero(mip,(Dword **)&stp);
  if(tp!=0x66){ MError("\"!!KT:\"-not a knowledge tree."); RETURN(0) }
  switch(Cmd){
    case 'S': // S# 0,1,2 (2)
      v=stp->Type; if(Apply(&v,4,Mp,0)) break; stp->Type=(Word)v; stp->Whom=0; break;
    case 'N': // N# ����� (5)
      v=stp->Number; Apply(&v,4,Mp,0); stp->Number=(Word)v; break;
    default: MError("\"!!KT:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_SetFire(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int v;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  _CFire_ *stp=(_CFire_ *)mip;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  if(mip->OType!=0xC){ MError("\"!!FR:\"-not a campfire."); RETURN(0) }
  switch(Cmd){
    case 'B': // B#1/#2 (4)(>5)
      if(Num<2){ MError("\"!!FR:B\"-wrong syntax."); RETURN(0) }
      v=stp->ResType; Apply(&v,4,Mp,0); stp->ResType=(Word)v;
      v=stp->ResVal;  Apply(&v,4,Mp,1); stp->ResVal=(Word)v;
      break;
    default: MError("\"!!FR:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_SetLean(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int v;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  _CLean_ *stp=(_CLean_ *)mip;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  int tp=CheckPlace4Hero(mip,(Dword **)&stp);
  if(tp!=0x27){ MError("\"!!LN:\"-not a lean."); RETURN(0) }
  switch(Cmd){
    case 'B': // B#1/#2 (4)(4)
      if(Num<2){ MError("\"!!LN:B\"-wrong syntax."); RETURN(0) }
      v=stp->ResType; Apply(&v,4,Mp,0); stp->ResType=(Word)v;
      v=stp->ResVal;  Apply(&v,4,Mp,1); stp->ResVal=(Word)v;
      break;
    case 'N': // N# ����� (5)
      v=stp->Number;  Apply(&v,4,Mp,0); stp->Number=(Word)v; break;
    default: MError("\"!!LN:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_SetStone(char Cmd,int/* Num*/,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int v;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  _CLStone_ *stp=(_CLStone_ *)mip;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  int tp=CheckPlace4Hero(mip,(Dword **)&stp);
  if(tp!=0x64){ MError("\"!!ST:\"-not a stone."); RETURN(0) }
  switch(Cmd){
    case 'N': // N# ����� ����� (5)
      v=stp->Number; Apply(&v,4,Mp,0); stp->Number=(Word)v; break;
    default: MError("\"!!ST:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_SetWagon(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int v;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  _CWagon_ *stp=(_CWagon_ *)mip;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  int tp=CheckPlace4Hero(mip,(Dword **)&stp);
  if(tp!=0x69){ MError("\"!!WG:\"-not a wagon."); RETURN(0) }
  switch(Cmd){
    case 'S': // S - ���� ���-��=1 ��� ��� ������=0 (1)
      v=stp->HasBon; if(Apply(&v,4,Mp,0)) break; stp->HasBon=(Word)v; stp->Whom=0; break;
    case 'B': // B - ���.=1 ��� ������=0 (1)
      v=stp->HasArt; Apply(&v,4,Mp,0); stp->HasArt=(Word)v; break;
    case 'A': // A#1 (10)
      v=stp->ArtNum; Apply(&v,4,Mp,0); stp->ArtNum=(Word)v; break;
    case 'R': // R#1/#2 (4)(5)
      if(Num<2){ MError("\"!!WG:R\"-wrong syntax."); RETURN(0) }
      v=stp->ResType; Apply(&v,4,Mp,0); stp->ResType=(Word)v;
      v=stp->ResVal;  Apply(&v,4,Mp,1); stp->ResVal=(Word)v;
      break;
    default: MError("\"!!WG:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_Pyramid(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int  v;
  Word b;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  _CPyram_  *stp=(_CPyram_ *)mip;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  int tp=CheckPlace4Hero(mip,(Dword **)&stp);
  if(tp!=0x3F){ MError("\"!!PM:\"-not a Pyramid or New Object."); RETURN(0) }
  switch(Cmd){
    case 'V': // V - ����������=1 ��� ��������=0
      v=stp->Visited; Apply(&v,4,Mp,0); stp->Visited=(Word)v; break;
    case 'P': // P#/$ - ��� ��������
      if(Num<2){ MError("\"!!PM:P\"-wrong syntax."); RETURN(0) }
      if((Mp->n[0]<0)||(Mp->n[0]>7)){ MError("\"!!PM:P\"-wrong player number (0...7)."); RETURN(0) }
      b=(Word)(1<<Mp->n[0]);
      if(b&stp->Whom) v=1; else v=0;
      if(Apply(&v,4,Mp,1)) break;
      if(v) stp->Whom|=b; else stp->Whom&=(Word)(~b);
      break;
    case 'S': // S$ ����������
      v=stp->Spell; Apply(&v,4,Mp,0); stp->Spell=(Word)v; break;
    default: MError("\"!!PM:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_SetSkelet(char Cmd,int/*Num*/,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int  v;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  _CSkelet_ *stp=(_CSkelet_ *)mip;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  int tp=CheckPlace4Hero(mip,(Dword **)&stp);
  if(tp!=0x16){ MError("\"!!SK:\"-not a skeleton."); RETURN(0) }
  switch(Cmd){
    case 'A': // A# �������� (10)
      v=stp->ArtNum; Apply(&v,4,Mp,0); stp->ArtNum=(Word)v; break;
    case 'N': // N# ���������� ����� (5)
      v=stp->Number; Apply(&v,4,Mp,0); stp->Number=(Word)v; break;
    case 'S': // S# ���� ���.=1 ��� ���=0 (1)
      v=stp->HasArt; Apply(&v,4,Mp,0); stp->HasArt=(Word)v; break;
    default: MError("\"!!SK:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_SetSpring(char Cmd,int/* Num*/,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int  v;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  _CMSpring_ *stp=(_CMSpring_ *)mip;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  int tp=CheckPlace4Hero(mip,(Dword **)&stp);
  if(tp!=0x30){ MError("\"!!SP:\"-not a spring."); RETURN(0) }
// ��������� 2-� �������� ������
  switch(Cmd){
    case 'S': // S# �������=1 ��� ���=0
      v=stp->Power; Apply(&v,4,Mp,0); stp->Power=(Word)v; break;
    case 'N': // N# ���������� ����� (5)
      v=stp->Number; Apply(&v,4,Mp,0); stp->Number=(Word)v; break;
    default: MError("\"!!SP:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_SetWMill(char Cmd,int/* Num*/,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int  v;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  _CWMill_ *stp=(_CWMill_ *)mip;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  int tp=CheckPlace4Hero(mip,(Dword **)&stp);
  if(tp!=0x6D){ MError("\"!!WM:\"-not a water weel."); RETURN(0) }
  switch(Cmd){
    case 'B': // B# ���-�� ������ (5)
      v=stp->Bonus; if(Apply(&v,4,Mp,0)) break; stp->Bonus=(Word)v; stp->Whom=0; break;
    default: MError("\"!!WM:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_SetSwan(char Cmd,int/* Num*/,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int  v;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  _CSSwan_ *stp=(_CSSwan_ *)mip;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  int tp=CheckPlace4Hero(mip,(Dword **)&stp);
  if(tp!=0x0E){ MError("\"!!SW:\"-not a swan pond."); RETURN(0) }
  switch(Cmd){
    case 'B': // B# ���-�� ����� 1...3 (4)
      v=stp->BonLuck; if(Apply(&v,4,Mp,0)) break; stp->BonLuck=(Word)v; stp->Whom=0; break;
    case 'N': // N# ���������� ����� (5)
      v=stp->Number; Apply(&v,4,Mp,0); stp->Number=(Word)v; break;
    default: MError("\"!!SW:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_SetMonolit(char Cmd,int/* Num*/,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int  v;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  _CMonol_ *stp=(_CMonol_ *)mip;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  int tp=CheckPlace4Hero(mip,(Dword **)&stp);
  if(tp!=0x39){ MError("\"!!MT:\"-not a monolith."); RETURN(0) }
  switch(Cmd){
    case 'N': // N# ���������� ����� (5)
      v=stp->Number; Apply(&v,4,Mp,0); stp->Number=(Word)v; break;
    default: MError("\"!!MT:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_SetGarden(char Cmd,int/* Num*/,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int  v;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  _CMGarden_ *stp=(_CMGarden_ *)mip;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  int tp=CheckPlace4Hero(mip,(Dword **)&stp);
  if(tp!=0x37){ MError("\"!!GD:\"-not a garden."); RETURN(0) }
  switch(Cmd){
    case 'B': // B# ��� ������ (4) [������ = 5]
      v=stp->ResType; Apply(&v,4,Mp,0); stp->ResType=(Word)v; break;
    case 'T': // T# ������=1 ��� ������=0 (1)
      v=stp->HasRes; Apply(&v,4,Mp,0); stp->HasRes=(Word)v; break;
    case 'N': // N# ���������� ����� (5)
      v=stp->Number; Apply(&v,4,Mp,0); stp->Number=(Word)v; break;
    default: MError("\"!!GD:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_SetMill(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int  v;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  _CMill_ *stp=(_CMill_ *)mip;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  int tp=CheckPlace4Hero(mip,(Dword **)&stp);
  if(tp!=0x70){ MError("\"!!ML:\"-not a mill."); RETURN(0) }
  switch(Cmd){
    case 'B': // B#/# ��� ������    (4)(4)
      if(Num<2){ MError("\"!!ML:B\"-wrong syntax."); RETURN(0) }
      v=stp->ResType; Apply(&v,4,Mp,0); stp->ResType=(Word)v;
      v=stp->ResVal; Apply(&v,4,Mp,1); stp->ResVal=(Word)v;
      break;
    default: MError("\"!!ML:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_SetDwelling(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int  i;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  int *stp=(int *)mip;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  int tp=CheckPlace4Hero(mip,(Dword **)&stp);
  if((tp!=17)&&(tp!=20)){ MError("\"!!DW:\"-not a Dwelling."); RETURN(0) }
  if((*stp<0)||(*stp>=GetDwellingNum())){ MError("\"!!DW\"-incorrect internal Dwelling number."); RETURN(0) }
  _Dwelling_ *dp=GetDwellingBase(); if(dp==0){ MError("\"!!DW:\"-Dwelling is not found in internal structures."); RETURN(0) }
  dp=&dp[*stp];
  switch(Cmd){
    case 'M': // M#1(0...3)/$2type/$3num ������ ��� �����
      if(Num<3){ MError("\"!!DW:M\"-wrong syntax."); RETURN(0) }
      i=Mp->n[0]; if((i<0)||(i>3)){ MError("\"!!DW:M\"-wrong monster slot (0...3)."); RETURN(0) }
      Apply(&dp->Mon2Hire[i],4,Mp,1);
      Apply(&dp->Num2Hire[i],2,Mp,2);
      break;
    case 'G': // M#1(0...7)/$2type/$3num ������ ��� ������
      if(Num<3){ MError("\"!!DW:G\"-wrong syntax."); RETURN(0) }
      i=Mp->n[0]; if((i<0)||(i>7)){ MError("\"!!DW:G\"-wrong monster slot (0...7)."); RETURN(0) }
      Apply(&dp->GType[i],4,Mp,1);
      Apply(&dp->GNum[i],4,Mp,2);
      break;
    case 'O': // O$ ������ (-1=�����)
      if(Num<2){
        Apply(&dp->Owner,1,Mp,0);
      }else{
        if(Num!=2){ MError("\"!!DW:O\"-wrong syntax."); RETURN(0) }
        i=dp->Owner; if(Apply(&i,1,Mp,0)) break;
        AdjustAllIfPassDwell(*stp,i);
//        if(Apply(&dp->Owner,1,Mp,0)) break;
      }
      break;
    default: MError("\"!!DW:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_SetCrBank(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int  i,ind,val,ar,retfl;
//  if(ERMVar2[0]==25 && ERMVar2[1]==20 && ERMVar2[2]==1){
//    __asm int 3
//  }
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  _CCrBank_ *stp=(_CCrBank_ *)mip;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  int tp=CheckPlace4Hero(mip,(Dword **)&stp);
  if(tp!=16 && tp!=25 && tp!=24 && tp!=84 && tp!=85){ MError("\"!!CB:\"-not a CrBank."); RETURN(0) }
  ind=stp->Ind;
  if((ind<0)||(ind>=GetCrBankNum())){ MError("\"!!CB\"-incorrect internal CrBank number."); RETURN(0) }
  _CrBankMap_ *dp=GetCrBankBase(); if(dp==0){ MError("\"!!CB:\"-Dwelling is not found in internal structures."); RETURN(0) }
  dp=&dp[ind];
  switch(Cmd){
    case 'M': // M$1type/$2num ������ ��� �����
      if(Num<2){ MError("\"!!CB:M\"-wrong syntax."); RETURN(0) }
      // 3.58f fix incorrect settings
//      Apply(&dp->BMonsterType,4,Mp,0);
//      Apply(&dp->BMonsterNum,1,Mp,1);
      val=dp->BMonsterType; Apply(&val,4,Mp,0); if(val<0) val=0; if(val>=MONNUM) val=MONNUM-1; dp->BMonsterType=val;
      val=dp->BMonsterNum;  Apply(&val,1,Mp,1); if(val<0) val=0; if(val>127) val=127; dp->BMonsterNum=val;
      break;
    case 'G': // M#1(0...7)/$2type/$3num ������ ��� ������
      if(Num<3){ MError("\"!!CB:G\"-wrong syntax."); RETURN(0) }
      i=Mp->n[0]; if((i<0)||(i>7)){ MError("\"!!CB:G\"-wrong monster slot (0...7)."); RETURN(0) }
      Apply(&dp->DMonsterType[i],4,Mp,1);
      Apply(&dp->DMonsterNum[i],4,Mp,2);
      break;
    case 'R': // R#1(0...7)/$2num ��������� �����
      if(Num<2){ MError("\"!!CB:R\"-wrong syntax."); RETURN(0) }
      i=Mp->n[0]; if((i<0)||(i>7)){ MError("\"!!CB:R\"-wrong resource index (0...7)."); RETURN(0) }
      Apply(&dp->Res[i],4,Mp,1);
      break;
    case 'A': // A#ind/...
      i=Mp->n[0]; if((i<1)||(i>5)){ MError("\"!!CB:A\"-wrong subcommand (1...5)."); RETURN(0) }
      switch(i){
        case 1: // A1/?var - number of arts
          if(Num<2){ MError("\"!!CB:A1\"-wrong syntax."); RETURN(0) }
          val=dp->Arts.GetNum();
          Apply(&val,4,Mp,1);
          break;
        case 2: // A2/#/$ - get/set art and subart at position #
          if(Num<3){ MError("\"!!CB:A2\"-wrong syntax."); RETURN(0) }
          retfl=0;
          if(Apply(&val,4,Mp,1)) break;
          ar=dp->Arts.Get(val);
          if(Apply(&ar,4,Mp,2)) retfl=1;
          if(retfl) break;
          dp->Arts.Set(val,ar);
          break;
        case 3: // A3/$ - add artifact
          if(Num<2){ MError("\"!!CB:A3\"-wrong syntax."); RETURN(0) }
          if(Apply(&val,4,Mp,1)) break;
          dp->Arts.Add(val);
          break;
        case 4: // A4/$ - del art
          if(Num<2){ MError("\"!!CB:A4\"-wrong syntax."); RETURN(0) }
          if(Apply(&val,4,Mp,1)) break;
          dp->Arts.Del(val);
          break;
        default:
          MError("\"!!CB:A\"-wrong syntax."); RETURN(0) 
      }
      break;
    case 'T': // T$ ���� ��� (1) ��� ��� (0)
      i=stp->Taken;
      if(Apply(&i,4,Mp,0)) break;
      if(i) stp->Taken=1; else stp->Taken=0;
      break;
    case 'V': // V$ ������� ������� (1) ��� ��� (0) [������� �����]
      i=stp->Whom;
      if(Apply(&i,4,Mp,0)) break;
      stp->Whom=i;
      break;
    default: MError("\"!!CB:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_SetWHat(char Cmd,int/* Num*/,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int  v;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  _CWHat_ *stp=(_CWHat_ *)mip;
  if(WoG==0) RETURN(0)// �������������� ������ � WoG
  int tp=CheckPlace4Hero(mip,(Dword **)&stp);
  if(tp!=113){ MError("\"!!WH:\"-not a witch hut."); RETURN(0) }
  switch(Cmd){
    case 'S': // S$ ����.�����
//      if((Mp->n[0]<0)||(Mp->n[0]>=28)){ MError("\"!!WH:S\"-wrong skill index (0...27)."); return 0; }
      v=stp->SSkill; Apply(&v,4,Mp,0); stp->SSkill=v;
      break;
    default: MError("\"!!WH:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_Shipyard(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int  v;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  _CShipyard_ *stp=(_CShipyard_ *)mip;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  int tp=CheckPlace4Hero(mip,(Dword **)&stp);
  if(tp!=87){ MError("\"!!SY:\"-not a shipyard."); RETURN(0) }
  switch(Cmd){
    case 'O': // O$ ������
//      if((Mp->n[0]<-1)||(Mp->n[0]>7)){ MError("\"!!SY:O\"-wrong owner (-1...7)."); return 0; }
      v=stp->Owner; Apply(&v,4,Mp,0); stp->Owner=(Word)v;
      break;
    case 'P': // P$/$ ������� ��� �����
      if(Num<2){ MError("\"!!SY:P\"-wrong syntax."); RETURN(0) }
      v=stp->xs; Apply(&v,4,Mp,0); stp->xs=(Word)v;
      v=stp->ys; Apply(&v,4,Mp,1); stp->ys=(Word)v;
      break;
    default: MError("\"!!SY:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_Garrison(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int  i,v;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  int *stp=(int *)mip;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  int tp=CheckPlace4Hero(mip,(Dword **)&stp);
  if(tp!=33){ MError("\"!!GR:\"-not a garrison."); RETURN(0) }
  if((*stp<0)||(*stp>=GetHornNum())){ MError("\"!!GR\"-wrong internal Garrison index."); RETURN(0) }
  _Horn_ *dp=GetHornBase(); if(dp==0){ MError("\"!!GR:\"-Garrison is not found in internal structures."); RETURN(0) }
  dp=&dp[*stp];
  switch(Cmd){
    case 'O': // O$ ������
//      if((Mp->n[0]<-1)||(Mp->n[0]>7)){ MError("\"!!GR:O\"-wrong owner (-1...7)."); return 0; }
      Apply(&dp->Owner,1,Mp,0);
      break;
    case 'G': // M#1(0...6)/$2type/$3num ������ ��� ������
      if(Num<3){ MError("\"!!GR:G\"-wrong syntax."); RETURN(0) }
      i=Mp->n[0]; if((i<0)||(i>=7)){ MError("\"!!GR:G\"-wrong slot number (0...6)."); RETURN(0) }
      Apply(&dp->GType[i],4,Mp,1);
      Apply(&dp->GNumb[i],4,Mp,2);
      break;
    case 'F': // F$ ������ ��������
      v=dp->NotRem; Apply(&v,4,Mp,0); dp->NotRem=(char)v;
      break;
//    case 'N': // 3.58 N$ ����� ��������� � ������ - ������ ��������
//      v=*stp; Apply(&v,4,Mp,0);
//      break;
    default: MError("\"!!GR:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_Shrine(char Cmd,int/* Num*/,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int  v;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  _CShrine_ *stp=(_CShrine_ *)mip;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  int tp=CheckPlace4Hero(mip,(Dword **)&stp);
  if((tp!=88)&&(tp!=89)&&(tp!=90)){ MError("\"!!SR:\"-not a shrine."); RETURN(0) }
  switch(Cmd){
    case 'S': // S$ ����������
      v=stp->Spell; Apply(&v,4,Mp,0); stp->Spell=(Word)v; break;
    default: MError("\"!!SR:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_Sign(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  int *stp=(int *)mip;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  int tp=CheckPlace4Hero(mip,(Dword **)&stp);
  if((tp!=59)&&(tp!=91)){ MError("\"!!SG:\"-not a sign or bottle."); RETURN(0) }
  if((*stp<0)||(*stp>=GetSignNum())){ MError("\"!!SG:\"-wrong internal sign or bottle index."); RETURN(0) }
  _Sign_ *dp=GetSignBase(); if(dp==0){ MError("\"!!SG:\"-Sign or Bottle is not found in internal structures."); RETURN(0) }
  dp=&dp[*stp];
  switch(Cmd){
    case 'M': // M^text^ , M1/$
      if(Num==2){ // � ����������
        if(Mp->n[0]==1){
          if(Mp->n[1]==-1){ // M1/-1
            MesMan(&dp->Mes,0,0);
            dp->HasMess=0;
          }else{ // M1/$
            ApplyString(Mp,1,&dp->Mes);
          }
        }else{ MError("\"!!SG:M\"-wrong syntax."); RETURN(0) }
      }else{
        if(NewMesMan(Mp,&dp->Mes,0)){ MError("\"!!SG:M\"-cannot set message."); RETURN(0) }
        if(dp->Mes.m.s!=0) dp->HasMess=1; // ���� ���������
        else dp->HasMess=0; // ��� ���������
      }
      break;
    default: MError("\"!!SG:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_Univer(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int i;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  _CUniver_ *stp=(_CUniver_ *)mip;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  int tp=CheckPlace4Hero(mip,(Dword **)&stp);
  if(tp!=104){ MError("\"!!UR:\"-not a univercity."); RETURN(0) }
  if((int)stp->Num>=GetUniverNum()){ MError("\"!!UR:\"-wrong internal univercity index."); RETURN(0) }
  _Univer_ *dp=GetUniverBase(); if(dp==0){ MError("\"!!UR:\"-University is not found in internal structures."); RETURN(0) }
  dp=&dp[stp->Num];
  switch(Cmd){
    case 'S': // S$/$/$/$
      if(Num!=4){ MError("\"!!UR:S\"-wrong syntax."); RETURN(0) }
      for(i=0;i<4;i++){ Apply(&dp->SSkill[i],4,Mp,(char)i); }
      break;
    default: MError("\"!!UR:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}

int ERM_Terrain(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int v,x,y,l;
  Dword MixPos=GetDinMixPos(sp);
  _MapItem_ *mip=GetMapItem2(MixPos);
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  switch(Cmd){
    case 'G': //G?var - �������� �����. ����������� 3.58
      v=GetMapItemModif(mip);
      Apply(&v,4,Mp,0);
      break;
    case 'T': // Tl/lt/r/rt/d/dt/m/mt - ��� ���
      if(Num!=8){ MError("\"!!TR:T\"-wrong syntax."); RETURN(0) }
      Apply(&mip->Land,1,Mp,0);
      Apply(&mip->LType,1,Mp,1);
      Apply(&mip->River,1,Mp,2);
      Apply(&mip->RType,1,Mp,3);
      Apply(&mip->Road,1,Mp,4);
      Apply(&mip->RType,1,Mp,5);
      Apply(&mip->Mirror,1,Mp,6);
      Apply(&mip->Attrib,1,Mp,7);
      break;
    case 'P': // P$ - ������������
      if(Num!=1){ MError("\"!!TR:P\"-wrong syntax."); RETURN(0) }
      if(mip->Attrib&0x01) v=0; else v=1;
      if(Apply(&v,4,Mp,0)) break;
      if(v==0) mip->Attrib|=0x01;
      else     mip->Attrib&=~(0x01);
      break;
    case 'E': // E$ - ����
      if(Num!=1){ MError("\"!!TR:E\"-wrong syntax."); RETURN(0) }
      if(mip->Attrib&0x10) v=0; else v=1;
      if(Apply(&v,4,Mp,0)) break;
      if(v==0) mip->Attrib|=0x10;
      else     mip->Attrib&=~(0x10);
      break;
    case 'V': // V$ - ���������
      MixedPos(&x,&y,&l,MixPos);
      v=GetVisability(x,y,l);
      if(Apply(&v,4,Mp,0)) break;
      SetVisability(x,y,l,v);
      break;
    default: MError("\"!!TR\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
int ERM_Position(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int  i,j,k,sz,lv,v,x,y,l,num;
  Dword w;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  Dword MixPos=GetDinMixPos(sp);
  MixedPos(&x,&y,&l,MixPos);
  sz=GetMapSize(); lv=GetMapLevels();
  if((x<0)||(x>=sz)){ MError("\"!!PO\"-wrong position (x)."); RETURN(0) }
  if((y<0)||(y>=sz)){ MError("\"!!PO\"-wrong position (y)."); RETURN(0) }
  if((l<0)||(l>lv)) { MError("\"!!PO\"-wrong position (l)."); RETURN(0) }
  _Square_ *sqp=&Square[x][y][l];
  _Square2_ *sqp2=&Square2[x][y][l];
  switch(Cmd){
    case 'H': // H$ ����� 0...255
      if(Num!=1){ MError("\"!!PO:H\"-wrong syntax."); RETURN(0) }
      w=sqp->Hero; Apply(&w,4,Mp,0); sqp->Hero=(Word)w;
      break;
    case 'O': // O$ ������ -8...7
      if(Num!=1){ MError("\"!!PO:O\"-wrong syntax."); RETURN(0) }
      v=sqp->Owner; Apply(&v,4,Mp,0); sqp->Owner=v;
      break;
    case 'N': // N$ ����� 0...15
      if(Num!=1){ MError("\"!!PO:N\"-wrong syntax."); RETURN(0) }
      w=sqp->Number; Apply(&w,4,Mp,0); sqp->Number=(Word)w;
      break;
    case 'T': // T$ ����� 0...255 ���
      if(Num!=1){ MError("\"!!PO:T\"-wrong syntax."); RETURN(0) }
      w=sqp->NumberT; Apply(&w,4,Mp,0); sqp->NumberT=(Word)w;
      break;
    case 'S': // S$ ����� 0...255 ������
      if(Num!=1){ MError("\"!!PO:S\"-wrong syntax."); RETURN(0) }
      w=sqp->NumberS; Apply(&w,4,Mp,0); sqp->NumberS=(Word)w;
      break;
    case 'C': // Ct/st/h/o/n (-1 - no matter)
      if(Num!=5){ MError("\"!!PO:C\"-wrong syntax."); RETURN(0) }
      num=0;
      for(i=0;i<sz;i++){
        for(j=0;j<sz;j++){
          for(k=0;k<=lv;k++){
            sqp=&Square[i][j][k];
            if(Mp->n[0]!=-1){ if((int)sqp->NumberT!=Mp->n[0]) continue; }
            if(Mp->n[1]!=-1){ if((int)sqp->NumberS!=Mp->n[1]) continue; }
            if(Mp->n[2]!=-1){ if((int)sqp->Hero!=Mp->n[2]) continue; }
            if(Mp->n[3]!=-1){ if((int)sqp->Owner!=Mp->n[3]) continue; }
            if(Mp->n[4]!=-1){ if((int)sqp->Number!=Mp->n[4]) continue; }
            ++num;
          }
        }
      }
      ERMVar2[0]=num;
      break;
    case 'V': // V#/$ ����� short -32000...32000
      if(Num!=2){ MError("\"!!PO:V\"-wrong syntax."); RETURN(0) }
      if(Apply(&i,4,Mp,0)){ MError("\"!!PO:V\"-you cannot use get or check syntax for the first argument."); RETURN(0) }
      if((i<0)||(i>3)){ MError("\"!!PO:V\"-wrong index (0...3)."); RETURN(0) }
      v=sqp2->S[i]; Apply(&v,4,Mp,1); sqp2->S[i]=(short)v;
      break;
    case 'B': // B#/$ ����� long -4g...4g
      if(Num!=2){ MError("\"!!PO:B\"-wrong syntax."); RETURN(0) }
      if(Apply(&i,4,Mp,0)){ MError("\"!!PO:B\"-you cannot use get or check syntax for the first argument."); RETURN(0) }
      if((i<0)||(i>1)){ MError("\"!!PO:B\"-wrong index (0...1)."); RETURN(0) }
      v=sqp2->L[i]; Apply(&v,4,Mp,1); sqp2->L[i]=v;
      break;
    default: MError("\"!!PO:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}

#define QWESTLOGNUM 1000
struct _QuestLog_{
  int  num; //0-free
  int  z;
  int  hero;
  int  owner;
}QuestLog[QWESTLOGNUM];

_QuestLog_ *FindQuest(int num,int hero,int owner)
{
  #include "templ.h"
  int i;
  for(i=0;i<QWESTLOGNUM;i++){
    if(QuestLog[i].num!=num) continue;
    if(QuestLog[i].hero!=hero) continue;
    if(QuestLog[i].owner!=owner) continue;
    RETURN(&QuestLog[i])
  }
  RETURN(0)
}

_QuestLog_ *AddQuest(int num,int hero,int owner)
{
  #include "templ.h"
  int i;
  for(i=0;i<QWESTLOGNUM;i++){
    if(QuestLog[i].num!=0) continue;
    QuestLog[i].num=num;
    QuestLog[i].hero=hero;
    QuestLog[i].owner=owner;
    RETURN(&QuestLog[i])
  }
  RETURN(0)
}

void DelQuest(_QuestLog_ *qlp)
{
  #include "templ.h"
  qlp->num=0;
  qlp->hero=0;
  qlp->owner=0;
  qlp->z=0;
  RETURNV
}
_QuestLog_ *GetQuest(int hero,int owner,int *ind)
{
  #include "templ.h"
  int i;
  for(i=*ind;i<QWESTLOGNUM;i++){
    if(QuestLog[i].num==0) continue;
    if((QuestLog[i].hero!=hero)&&(QuestLog[i].hero!=-2)) continue;
    if((QuestLog[i].owner!=owner)&&(QuestLog[i].owner!=-2)) continue;
    *ind=i+1;
    RETURN(&QuestLog[i])
  }
  RETURN(0)
}

int ERM_Qwest(char Cmd,int Num,_ToDo_* /*sp*/,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int num,zvar,hero,owner;
  _QuestLog_ *qlp;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  switch(Cmd){
    case 'A': // Anum/hero/owner/zvar;
      if(Num!=4){ MError("\"!!QW:A\"-wrong syntax."); RETURN(0) }
      if(Apply(&num,4,Mp,0)) { MError("\"!!QW:A\"-cannot get or check num."); RETURN(0) }
      if(Apply(&hero,4,Mp,1)) { MError("\"!!QW:A\"-cannot get or check hero number."); RETURN(0) }
      if(Apply(&owner,4,Mp,2)) { MError("\"!!QW:A\"-cannot get or check owner."); RETURN(0) }
      if(num<1){ MError("\"!!QW:A\"-Qwest number is incorrect (>0)."); RETURN(0) }
      if((hero<-2)||(hero>=HERNUM)){ MError("\"!!QW:A\"-hero number is incorrect."); RETURN(0) }
      if(hero==-1){
        hero=ERM_HeroStr->Number;
        if((hero<0)||(hero>=HERNUM)){ MError("\"!!QW:A\"-no current hero."); RETURN(0) }
      }
      if((owner<-2)||(owner>7)){ MError("\"!!QW:A\"-owner is incorrect (<-2 or >7)."); RETURN(0) }
      if(owner==-1) owner=CurrentUser();
      qlp=FindQuest(num,hero,owner);
      if(qlp==0) qlp=AddQuest(num,hero,owner);
      if(qlp==0){ MError("\"!!QW:A\"-cannot add one more quest."); RETURN(0) }
      zvar=qlp->z; Apply(&zvar,4,Mp,3); qlp->z=zvar;
      if(zvar==-1) DelQuest(qlp);
      break;
    default: MError("\"!!QW\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}

int ERM_StackExperience(char Cmd,int Num,_ToDo_*sp,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int x,y,l,v,m,n,fl,hind,art,opt;
  int Type,Slot,MType=-1,MNum=0;
  CRLOC Crloc;
  CrExpo *Cr,*Cr2,CrV;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
//  ERMFlags[0]=0;
  // should set Type,Crloc,Slot
  switch(sp->ParSet){
//    case 1: // ������ ����� � ��������� �����
//      Ind=GetVarVal(&sp->Par[0]);
//      if(CrExpoSet::FindType(Ind,&Type,&Crloc,&Slot)==0){ MError("\"!!EX\"- incorrect index"); RETURN(0) }
//      break;
    case 2: // �����/����
      hind=GetVarVal(&sp->Par[0]);
      if(hind<-1 || hind>=HERNUM){ MError("\"!!EX\"- incorrect hero index"); RETURN(0) }
      if(hind==-1){
        if(ERM_HeroStr==0){ MError("\"!!EX\"- default hero is not available here"); RETURN(0) }
        else hind=ERM_HeroStr->Number;
      }
      Slot=GetVarVal(&sp->Par[1]);
      if(Slot<0 || Slot>=7){ MError("\"!!EX\"- incorrect index"); RETURN(0) }
      Type=CE_HERO; Crloc=MAKEHS(hind,Slot);
      MType=GetHeroStr(hind)->Ct[Slot];
      MNum =GetHeroStr(hind)->Cn[Slot];
//      Ind=CrExpoSet::FindIt(Type,Crloc);
//      if(Ind<0){ MError("\"!!EX\"- incorrect index"); RETURN(0) }
      break;
    case 4: // something at x/y/l/n(/type)
    case 5: 
      if(sp->ParSet==5){
        Type=GetVarVal(&sp->Par[4]);
        switch(Type){
          case 1:  Type=CE_HERO; break;
          case 2:  Type=CE_TOWN; break;
          case 3:  Type=CE_MINE; break;
          case 4:  Type=CE_HORN; break;
          default: Type=-1;
        }
      }else{
        Type=-1; // undefined
      }
      x=GetVarVal(&sp->Par[0]);
      y=GetVarVal(&sp->Par[1]);
      l=GetVarVal(&sp->Par[2]);
      Slot=GetVarVal(&sp->Par[3]);
      if(Slot<0 || Slot>=7){ ERMFlags[0]=1; RETURN(0) }
      if(CrExpoSet::FindType(x,y,l,Slot,&Type,&Crloc,&MType,&MNum)==0){ MError("\"!!EX\"- cannot find object at location"); RETURN(0) }
      break;
    case 0:
    case 1: // ������ ����� � ��������� �����
    case 3: // type/index/slot
      MError("\"!!EX\"-unsupported syntax."); RETURN(0)
  }
  Cr=CrExpoSet::Find(Type,Crloc);
  // Cr may be 0 !!!!
  if(Cr==0){
    Cr2=CrExpoSet::FindEmpty();
    if(Cr2==0){ MError("\"!!EX\"-no more room in experience story."); RETURN(0) }
    CrV.Clear();
    CrV.SetN(Type,Crloc,MType,MNum,0);
  }else{
    Cr2=Cr;
    CrV=*Cr;
  }
  switch(Cmd){
    case 'E': // Experience
      v=CrV.Expo; if(Apply(&v,4,Mp,0)) break;
      CrV.Expo=v; *Cr2=CrV;
      break;
    case 'N': // Number of creatures
      v=CrV.Num;  if(Apply(&v,4,Mp,0)) break;
      CrV.Num=v; *Cr2=CrV;
      break;
    case 'T': // Monster Type
      v=CrV.Fl.MType; if(Apply(&v,4,Mp,0)) break;
      CrV.Fl.MType=(Word)v; *Cr2=CrV;
      break;
//    case 'O': // Owner Type
//      if(Cr==0) v=0; else v=Cr->Fl.Type;
//      if(Apply(&v,4,Mp,0)) break;
//      if(Cr==0){ Cr=Cr2; Cr->SetN(Type,Crloc,0,0,0); }
//      Cr->Fl.Type=v;
//      break;
    case 'A': // all info: MType/MNum/Expo
      if(Num<3){ MError("\"!!EX:A\"-wrong syntax."); RETURN(0) }
      m=CrV.Fl.MType; n=CrV.Num; v=CrV.Expo;
      fl=0;
      if(Apply(&m,4,Mp,0)) ++fl;
      if(Apply(&n,4,Mp,1)) ++fl;
      if(Apply(&v,4,Mp,2)) ++fl;
      if(fl==3) break;
//      if(m==-1){ // �� ����� ��� - ����� ������ ��� ���� ��� �����, ���� �� ��� ���
      CrV.Fl.MType=(Word)m;
      CrV.Num=n;
      CrV.Expo=v;
      *Cr2=CrV;
      break;
    case 'R': // art/subart
      if(Num<2){ MError("\"!!EX:R\"-wrong syntax."); RETURN(0) }
      if(Num==4){ // new syntax - has/art/subart/copies
        int h,a,s,c,fl;
        h=CrV.HasArt();
        a=CrV.GetArt();
        s=CrV.GetSubArt();
        c=CrV.ArtCopy();
        fl=4;
        if(Apply(&h,4,Mp,0)) --fl;
        if(Apply(&a,4,Mp,1)) --fl;
        if(Apply(&s,4,Mp,2)) --fl;
        if(Apply(&c,4,Mp,3)) --fl;
        if(fl==0) break;
        CrV.SetArtAll(h,a,s,c);
        *Cr2=CrV;
        break;
      }
      if(CrV.HasArt()){ art=CrV.GetArt(); opt=CrV.GetSubArt(); }
      else{ art=-1; opt=0; }
      fl=0;
      if(Apply(&art,4,Mp,0)) fl=1;
      if(Apply(&opt,4,Mp,1)) fl=1;
      if(fl) break;
      if(art==-1){ // no art
        CrV.DelArt();
      }else{
        CrV.SetArt(art,opt);
      }
      *Cr2=CrV;
      break;
    case 'C': // combine with other stack
      {
        int nomes=0,lt,lhind,lx,ly,ll,lslot,ltype,lmtype,lmnum;
        CRLOC lcrloc;
//  CrExpo *Cr,*Cr2,CrV;
        if(Apply(&lt,4,Mp,0)) break;
        ERMVar2[0]=0;
        switch(lt){
          case 0: // 0/�����/����(/nomes)
           if(Num<3){ MError("\"!!EX:C\"-wrong syntax."); RETURN(0) }
           if(Apply(&lhind,4,Mp,1)) RETURN(1)
           if(lhind<-1 || lhind>=HERNUM){ MError("\"!!EX:C\"- incorrect hero index"); RETURN(0) }
           if(lhind==-1){
              if(ERM_HeroStr==0){ MError("\"!!EX:C\"- default hero is not available here"); RETURN(0) }
              else lhind=ERM_HeroStr->Number;
           } 
           if(Apply(&lslot,4,Mp,2)) RETURN(1)
           ltype=CE_HERO; lcrloc=MAKEHS(lhind,lslot);
           if(CrExpoSet::Find(Type,Crloc)==0){
             // not found - nothing to do
//             RETURN(1)
             lmtype=MType; lmnum=0; // undefoned!!!
           }
           lmtype=GetHeroStr(lhind)->Ct[lslot];
           lmnum =GetHeroStr(lhind)->Cn[lslot];
           if(Num>3) Apply(&nomes,4,Mp,3);
           if(lmtype!=MType){ 
             ERMVar2[0]=-1;
             if(nomes){ 
               RETURN(1)
             }else{
               MError("\"!!EX:C\"- stacks have a different creatures"); RETURN(0) 
             }
           }
           break;
         case 1: // hero at 1/x/y/l/n(/nomes)
         case 2: // town at 2/x/y/l/n(/nomes)
         case 3: // mine at 3/x/y/l/n(/nomes)
         case 4: // garn at 4/x/y/l/n(/nomes)
           if(Num<5){ MError("\"!!EX:C\"-wrong syntax."); RETURN(0) }
           if(Apply(&lx,4,Mp,1)) RETURN(1)
           if(Apply(&ly,4,Mp,2)) RETURN(1)
           if(Apply(&ll,4,Mp,3)) RETURN(1)
           if(Apply(&lslot,4,Mp,4)) RETURN(1)
           if(lslot<0 || lslot>=7){ MError("\"!!EX:C\"- incorrect slot index"); RETURN(0) }
           switch(lt){
             case 1:  ltype=CE_HERO; break;
             case 2:  ltype=CE_TOWN; break;
             case 3:  ltype=CE_MINE; break;
             case 4:  ltype=CE_HORN; break;
             default: ltype=-1;
           }
           if(CrExpoSet::FindType(lx,ly,ll,lslot,&ltype,&lcrloc,&lmtype,&lmnum)==0){  
             // not found - nothing to do
//             RETURN(1)
             lmtype=MType; lmnum=0; // undefoned!!!
           }
           if(Num>5) Apply(&nomes,4,Mp,5);
           if(lmtype!=MType){ 
             ERMVar2[0]=-1;
             if(nomes){ 
               RETURN(1)
             }else{
               MError("\"!!EX:C\"- stacks have a different creatures"); RETURN(0) 
             }
           }
           break;
         default:
           MError("\"!!EX:C\"-unsupported syntax."); RETURN(0)
        }
        // add this stack to main
        ERMVar2[0]=CrExpoSet::HCombReal(ltype,Type,lcrloc,Crloc,lmtype,MType,lmnum,MNum);
      }
      break;
    default: MError("\"!!EX\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}

int ERM_HeroGainLevel(char Cmd,int Num,_ToDo_*sp,Mes *Mp);
int ERM_MouseClick(char Cmd,int Num,_ToDo_*sp,Mes *Mp);
int ERM_MouseMove(char Cmd,int Num,_ToDo_* /*sp*/,Mes *Mp);

///////////////////////////////////////////////
/// ERM ERM ERM
///////////////////////////////////////////////
struct _ERM_Addition_{
  Word   Id;
  int  (*Fun)(char,int,_ToDo_ *,Mes *);
  int    Type;
} ERM_Addition[]={
  {'DC',ERM_CasDem,0},
  {'AM',ERM_MonAtr,0},
  {'NU',ERM_Universal,0},
  {'RV',ERM_Variable,1}, // ����������� ���������� VRi
  {'MT',ERM_Timer,1},    // ����������� ���������� TMi
  {'BO',ERM_SetObject,2},   // 2-x/y/l � MixedPos
  {'WO',ERM_Owner,0},
  {'NM',ERM_Mine,2},
  {'CS',ERM_SetScoolar,2},   // 2-x/y/l � MixedPos
  {'HC',ERM_SetChest,2},     // 2-x/y/l � MixedPos
  {'TW',ERM_SetWTomb,2},     // 2-x/y/l � MixedPos
  {'TK',ERM_SetKTree,2},     // 2-x/y/l � MixedPos
  {'RF',ERM_SetFire,2},      // 2-x/y/l � MixedPos
  {'NL',ERM_SetLean,2},      // 2-x/y/l � MixedPos
  {'TS',ERM_SetStone,2},     // 2-x/y/l � MixedPos
  {'GW',ERM_SetWagon,2},     // 2-x/y/l � MixedPos
  {'KS',ERM_SetSkelet,2},    // 2-x/y/l � MixedPos
  {'PS',ERM_SetSpring,2},    // 2-x/y/l � MixedPos
  {'MW',ERM_SetWMill,2},     // 2-x/y/l � MixedPos
  {'WS',ERM_SetSwan,2},      // 2-x/y/l � MixedPos
  {'TM',ERM_SetMonolit,2},   // 2-x/y/l � MixedPos
  {'DG',ERM_SetGarden,2},    // 2-x/y/l � MixedPos
  {'LM',ERM_SetMill,2},      // 2-x/y/l � MixedPos
  {'WD',ERM_SetDwelling,2},  // 2-x/y/l � MixedPos
  {'HW',ERM_SetWHat,2},      // 2-x/y/l � MixedPos
  {'YS',ERM_Shipyard,2},     // 2-x/y/l � MixedPos
  {'RG',ERM_Garrison,2},     // 2-x/y/l � MixedPos
  {'RS',ERM_Shrine,2},       // 2-x/y/l � MixedPos
  {'GS',ERM_Sign,2},         // 2-x/y/l � MixedPos
  {'RU',ERM_Univer,2},       // 2-x/y/l � MixedPos
  {'CM',ERM_Macro,1},        // ����������� ���������� VRi
  {'UF',ERM_Function,3},     // ����������� �������� M.n[0]
  {'OD',ERM_Do,4},           // �������� M.n[0], ���� M.n[1],M.n[2],M.n[3]
  {'AC',ERM_Castle,2},       // 2-x/y/l � MixedPos
  {'RT',ERM_Terrain,2},      // 2-x/y/l � MixedPos
  {'OH',ERM_SetHero,3},      // ����������� �������� M.n[0]
  {'OP',ERM_Position,2},     // 2-x/y/l � MixedPos
  {'AB',ERM_Battle,0},
  {'FB',ERM_BattleField,0},
  {'MB',ERM_BRound,1},
//  {(Word)'BM',ERM_BMonster,0},
  {'HB',ERM_BHero,1},
  {'UB',ERM_BUniversal,0},
  {'GB',ERM_MAction,0},
  {'WQ',ERM_Qwest,0},
  {'LH',ERM_HeroGainLevel,0},
  {'TH',ERM_HintType,5},      // ��� ���������� v1/v2
  {'MP',ERM_Pyramid,2},       // 2-x/y/l � MixedPos
  {'WM',ERM_WMon,1},          // ����������� ���������� MWi
  {'MC',ERM_MouseClick,0},
  {'MM',ERM_MouseMove,0},
  {'PM',ERM_MP3,0},
  {'IA',ERM_AIRun,0},
  {'OC',ERM_NPC,1},
  {'CV',ERM_VarControl,0},
// 3.58
  {'NS',ERM_Sound,0},
  {'RM',ERM_MonRes,0},
  {'FM',ERM_MonFeature,0},
  {'XE',ERM_StackExperience,2},
  {'AE',ERM_AICrExp,2},
  {'BC',ERM_SetCrBank,2},  // 2-x/y/l � MixedPos
  {'PI',ERM_NetworkService,3},      // ����������� �������� M.n[0]
// 3.59
  {'LT',ERM_TL,0}, 
  {'LD',ERM_Dlg,1},          // ����������� ���������� VRi
  {'SS',ERM_Spell,1}, 
  {'DL',ERM_LODs,0}, 
  {'fi',0,0},
  {'le',0,0},
  {'ne',0,0},

  {0,0}
};

//////////////////////////////////

int SkipNumbers(char *str)
{
  STARTNC(__FILENUM__*1000000+__LINE__,str)
  int i;
  for(i=0;;i++){
    if((str[i]=='+')||(str[i]=='-')) continue;
    break;
  }
  for(;;i++){
    if((str[i]>='0')&&(str[i]<='9')) continue;
    RETURN(i)
  }
}

static char ERMMesBuf[5][10000];
char *_Message2ERM(char *str)
{
  STARTNC(__FILENUM__*1000000+__LINE__,str)
  int  i,j,k,l,v;
  char ch,*s,*stro;
  VarNum *vnt;
  _Date_ *p=CurDate;

 for(l=0;l<5;l++){
  if(l>0) str=ERMMesBuf[l-1];
  stro=ERMMesBuf[l];
  for(i=j=0;j<9999;i++,j++){
    ch=str[i];
    switch(ch){
      case '%':
        ch=str[++i];
        switch(ch){
          case '$':
            vnt=GetMacro(FindMacro2(&str[i],0,&k));
            i+=k-1;
            if(vnt==0){ MError("\"String 2ERM\"-wrong macro $...$."); break; }
            if(vnt->Type==7){
              j+=a2a(ERMString[vnt->Num-1],&/*ERMMesBuf*/stro[j])-1;
              break;
////            }else if(vnt->Type==9){
////              if(CheckScope()) break;
////              j+=a2a(ERMScope->String[vnt->Num-1],&ERMMesBuf[j])-1;
////              break;
            }else{
              switch(vnt->Type){
                case 0: v=ERMFlags[vnt->Num-1]; break; // flags
                case 2: v=ERMVar[vnt->Num-1]; break; // f...t
                case 3: v=ERMVar2[vnt->Num-1]; break; // v
                case 4: v=ERMVarH[ERMW][vnt->Num-1]; break; // w
                case 5: v=ERMVarX[vnt->Num-1]; break; // x
                case 6:
                  if(vnt->Num<0) v=ERMVarYT[-vnt->Num-1];
                  else                v=ERMVarY[vnt->Num-1];
                  break; // y
//                case 8: v=ERMVarF[vnt->Num-1]; break; // e
              }
              j+=i2a(v,&/*ERMMesBuf*/stro[j])-1;
            }
            break;
          case '%': /*ERMMesBuf*/stro[j]='%'; break;
          case 'V': // V# or Vf...t
            ch=str[++i];
            if((ch>='f')&&(ch<='t')){ // ����������
              j+=i2a(ERMVar[ch-'e'-1],&/*ERMMesBuf*/stro[j])-1;
            }else{
              v=a2i(&str[i]); i+=SkipNumbers(&str[i])-1;
              if((v>=1)&&(v<=10000)){ // ����������
                j+=i2a(ERMVar2[v-1],&/*ERMMesBuf*/stro[j])-1;
              }else{ MError("\"String 2ERM\"-wrong %V# number (1...10000)."); }
            }
            break;
          case 'W': // W#
            ++i;
            v=a2i(&str[i]); i+=SkipNumbers(&str[i])-1;
            if((v>=1)&&(v<=200)){ // w#
              j+=i2a(ERMVarH[ERMW][v-1],&/*ERMMesBuf*/stro[j])-1;
            }else{ MError("\"String 2ERM\"-wrong %W# number (1...200)."); }
            break;
          case 'X': // X#
            ++i;
            v=a2i(&str[i]); i+=SkipNumbers(&str[i])-1;
            if((v>=1)&&(v<=16)){ // x#
              j+=i2a(ERMVarX[v-1],&/*ERMMesBuf*/stro[j])-1;
            }else{ MError("\"String 2ERM\"-wrong %X# number (1...16)."); }
            break;
          case 'Y': // Y#
            ++i;
            v=a2i(&str[i]); i+=SkipNumbers(&str[i])-1;
            if((v>=1)&&(v<=100)){ // y#
              j+=i2a(ERMVarY[v-1],&/*ERMMesBuf*/stro[j])-1;
            }else if((v<=-1)&&(v>=-100)){ // y#
              j+=i2a(ERMVarYT[-v-1],&/*ERMMesBuf*/stro[j])-1;
            }else{ MError("\"String 2ERM\"-wrong %Y# number (-100...-1,1...100)."); }
            break;
          case 'E': // E#
            ++i;
            v=a2i(&str[i]); i+=SkipNumbers(&str[i])-1;
            if((v>=1)&&(v<=100)){ // e#
              j+=f2a(ERMVarF[v-1],&/*ERMMesBuf*/stro[j])-1;
            }else if((v<=-1)&&(v>=-100)){ // e-#
              j+=f2a(ERMVarFT[-v-1],&/*ERMMesBuf*/stro[j])-1;
            }else{ MError("\"String 2ERM\"-wrong %E# number (-100...-1,1...100)."); }
            break;
          case 'Z': // Z#
            ++i;
            v=a2i(&str[i]); i+=SkipNumbers(&str[i])-1;
            if((v<-10)||(v==0)){ MError("\"String 2ERM\"-wrong %Z# number (-10...-1,1...1000)."); }
            if(v>1000)   j+=a2a(StringSet::GetText(v),&/*ERMMesBuf*/stro[j])-1;
            else if(v>0) j+=a2a(ERMString[v-1],&/*ERMMesBuf*/stro[j])-1;
            else         j+=a2a(ERMLString[-v-1],&/*ERMMesBuf*/stro[j])-1;
            break;
////          case 'B': // B#
////            ++i;
////            if(CheckScope()) break;
////            v=a2i(&str[i]); i+=SkipNumbers(&str[i])-1;
////            if((v>=1)&&(v<=500)){ // z#
////              j+=a2a(ERMScope->String[v-1],&ERMMesBuf[j])-1;
////            }else{ MError("\"String 2ERM\"-wrong %B# number (1...500)."); }
////            break;
////          case 'A': // A#
////            ++i;
////            if(CheckScope()) break;
////            v=a2i(&str[i]); i+=SkipNumbers(&str[i])-1;
////            if((v>=1)&&(v<=1000)){ // x#
////                j+=i2a(ERMVar2[v-1],&ERMMesBuf[j])-1;
////              }else{ MError("\"String 2ERM\"-wrong %A# number (1...1000)."); }
////            break;
          case 'F': // F# �����
            ++i;
            v=a2i(&str[i]); i+=SkipNumbers(&str[i])-1;
            if((v>=1)&&(v<=1000)){ // z#
              j+=i2a(ERMFlags[v-1],&/*ERMMesBuf*/stro[j])-1;
            }else{ MError("\"String 2ERM\"-wrong %F# number (1...1000)."); }
            break;
          case 'D': // Dd or Dw or Dm or Da
            ch=str[++i];
            switch(ch){
              case 'd': j+=i2a(p->Day,&/*ERMMesBuf*/stro[j])-1; break;
              case 'w': j+=i2a(p->Week,&/*ERMMesBuf*/stro[j])-1; break;
              case 'm': j+=i2a(p->Month,&/*ERMMesBuf*/stro[j])-1; break;
              case 'a': j+=i2a(GetCurDate(),&/*ERMMesBuf*/stro[j])-1; break;
              default : MError("\"String 2ERM\"-wrong %D$ syntax.");
            }
            break;
          case 'G': // G# or Gc
            ch=str[++i];
            if(ch=='c') v=CurrentUser();
//            else{ v=a2i(&str[i]); i+=SkipNumbers(&str[i]); }
//            if((v<0)||(v>7)){ Error(); break; }
            else{ MError("\"String 2ERM\"-wrong %G# syntax."); break; }
            s=ITxt(62+v,0,&Strings);
            while((ch=*s++)!=0) /*ERMMesBuf*/stro[j++]=ch;
            --j;
            break;
          default:
//            MError("\"String 2ERM\"-wrong %$ syntax."); return str;
              /*ERMMesBuf*/stro[j++]='%'; /*ERMMesBuf*/stro[j]=ch;
              break;
        }
        break;
      case   0:
        /*ERMMesBuf*/stro[j]=0; goto _ok;
      default :
        /*ERMMesBuf*/stro[j]=ch;
    }
  }
_ok:
  /*ERMMesBuf*/stro[9999]=0;
 }
 RETURN(ERMMesBuf[4])
}

void Mess(Mes *m)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&m->m.s[m->i])
//  DATAIT;
//  Message("{ERM} Command has wrong syntax. Skipped.",1);
  Message(ITxt(24,0,&Strings),1);
  m->m.s[m->m.l]=0;
  Message(m->m.s,1);
  ++m->i;
  RETURNV
}

//static char NoERMString[]="*** ERM String Error ***";
char *ERM2String(char *mes,int zstr,int *len)
{
  STARTNC(__FILENUM__*1000000+__LINE__,mes)
  int i,j,fl;

  ERMMesBuf[0][0]=0;
  if(len!=0) *len=0;
  if(zstr){
    _Message2ERM(mes);
  }else{
    for(fl=i=j=0;i<10000;i++){
      if(mes[i]==STRCH){
        if(fl==1){
          mes[i]=0;
          _Message2ERM(&mes[j]);
          mes[i]=STRCH;
          *len=i+1;
          break;
        }else{
          j=i+1;
          fl=1;
        }
      }
    }
  }
  RETURN(ERMMesBuf[4])
}

int ApplyString(Mes *Mp,int ind,_AMes_ *amp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int sind;
  if(Mp->VarI[ind].Check==1){ // ?
    sind=GetVarVal(&Mp->VarI[ind]);
    if((sind<-10)||(sind==0)||(sind>1000)){ MError("\"ApplyString\"-wrong z (destination) index (-10...-1,1...1000)."); RETURN(0) }
    if(sind>0) StrCopy(ERMString[sind-1],512,amp->m.s);
    else       StrCopy(ERMLString[-sind-1],512,amp->m.s);
////    if((sind<-500)||(sind>500)){ MError("\"ApplyString\"-wrong z or b var (destination) index (1...500)."); return 0; }
////    if(sind<0){ // b
////      if(CheckScope()) return 0;
////      StrCopy(ERMScope->String[-sind-1],512,amp->m.s);
////    }else{ // z
////      StrCopy(ERMString[sind-1],512,amp->m.s);
////    }
    RETURN(1)
  }else{
    sind=Mp->n[ind];
////
    if((sind<-10)||(sind==0)){ MError("\"ApplyString\"-wrong z (sourse) index (-10...-1,1...1000)."); RETURN(0) }
    if(sind>1000)   MesMan(amp,ERM2String(StringSet::GetText(sind),1,0),0);
    else if(sind>0) MesMan(amp,ERM2String(ERMString[sind-1],1,0),0);
    else            MesMan(amp,ERM2String(ERMLString[-sind-1],1,0),0);
////    if((sind<-500)||(sind>500)){ MError("\"ApplyString\"-wrong z or b var (sourse) index (1...500)."); return 0; }
////    if(sind<0){ // b
////      if(CheckScope()) return 0;
////      MesMan(amp,ERM2String(ERMScope->String[-sind-1],1,0),0);
////    }else{ // z
////      MesMan(amp,ERM2String(ERMString[sind-1],1,0),0);
////    }
    RETURN(0)
  }
}

int PrepareArtTable(void){ return 0; }

Dword InitEnters(void)
{
  #include "templ.h"
  PostERM=(struct _PostERM_ *)HeapArray;
  PostERM->f=PERMSIZE;
  Heap=(struct _Cmd_ *)HeapArray2;
  HeapSize=HEAPSIZE;
  RETURN(0)
}

//////////// Put all functions here

int SkipUntil(Mes *ms)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&ms->m.s[ms->i])
  char *s=ms->m.s; long  l=ms->m.l; long  i=ms->i; char  c=ms->c[0];
  int fl=0;
  char ch;
  if(c==1){ // �� ������� �������
    while(i<l){
      c=s[i];
      switch(c){
        case ' ':
        case 0x0A:
        case 0x0D:
        case 0x09: break;
//        case '"' : fl!=fl; break;
        default: ms->i=i; RETURN(0)
      }
      ++i;
    }
  }else{
    while(i<l){
      ch=s[i];
//      if(ch==STRCH){ fl!=fl;}
      // VC
      if(ch==STRCH){ fl=!fl;}
      else{
        if(fl==0){
          if(ch==c){ ms->i=i+1; RETURN(0)}// ��������� ���������
        }
      }
      ++i;
    }
  }
  RETURN(-1)
}

// skip all chars (comment part)
int SkipUntil2(Mes *ms)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&ms->m.s[ms->i])
  char *s=ms->m.s; long  l=ms->m.l; long  i=ms->i; char  c=ms->c[0];
  char ch;
  while(i<l){
    ch=s[i];
    if(ch==c){ ms->i=i+1; RETURN(0)}// ��������� ���������
    ++i;
  }
  RETURN(-1)
}

int CheckMine(Mes *ms)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&ms->m.s[ms->i])
  Dword *d;
  ms->i=0;ms->c[0]=1;
  if(SkipUntil(ms)) RETURN(0)
  d=(Dword *)&ms->m.s[ms->i];
  if(*d==0x4553565A){ ms->i+=4; RETURN(1)}
  RETURN(0)
}
/////////////////////////////////
int GetSubNum(Mes *ms,int ind)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&ms->m.s[ms->i])
  char *s=ms->m.s; long l=ms->m.l; long i=ms->i;
  char c=ms->c[ind]; int *n=&ms->n[ind]; //char *df=&ms->f[ind];
  char ch,sign=0,day=0;
  *n=0;

//  *df=0;
  if(c==1){
    do{
      ch=s[i];
      switch(ch){
        case ' ': if(sign==0){i++; continue;}else goto _over;
//        case 'd': if(sign==0){*df=1; ++i; continue;}else goto _ok;
        case 'c': if(day==0) {day=1; ++i; continue;}else goto _ok;
        case '-': if(sign==0){sign=-1; ++i; continue;}else goto _ok;
        case '+': if(sign==0){sign=1; ++i; continue;}else goto _ok;
        default:
          if((ch<'0')||(ch>'9')) goto _ok;
          if(sign==0) sign=1;
           if(day==0) day=-1;
          *n*=10; *n+=(int)ch-'0';
          ++i;
          break;
      }
    }while(1);
  }else{
    while(((ch=s[i])!=c)&&(i<l)){
      switch(ch){
        case ' ': ++i; continue;
//        case 'd': if(sign==0){*df=1; ++i; continue;}else return -1;
        case 'c': if(day==0) { day=1; ++i; continue;}else RETURN(-1)
        case '-': if(sign==0){ sign=-1; ++i; continue;}else RETURN(-1)
        case '+': if(sign==0){ sign=1; ++i; continue;}else RETURN(-1)
        default:
          if((ch<'0')||(ch>'9')) RETURN(-1)
          if(sign==0) sign=1;
          if(day==0) day=-1;
          *n*=10; *n+=(int)ch-'0';
          ++i;
          break;
      }
    }
    ms->i=i+1; // ��������� ������������� ������
    goto _ok2;
  }
_ok:
  ms->i=i;
_ok2:
  *n*=sign;
  if(day==1) *n+=GetCurDate();
  RETURN(0)
_over: // ��������� ����������� �������
  while(s[i]==' ') ++i;
  goto _ok;
}

void VNCopy(VarNum *src,VarNum *dst)
{
  #include "templ.h"
  if(src==0){ MError("\"VNCopy\"-internal error (source=0). Possible reason is wrong macro syntax."); RETURNV }
  if(dst==0){ MError("\"VNCopy\"-internal error (destination=0). Possible reason is wrong macro syntax."); RETURNV }
//  dst->SetNum(src->GetNum());
  *dst=*src;
//  dst->Num=src->Num;
//  dst->Type=src->Type;
//  dst->IType=src->IType;
//  dst->Check=src->Check;
  RETURNV
}
int GetCmpCode(char cn)
{
  #include "templ.h"
  switch(cn){
    case 0: RETURN(0)
    case 1: RETURN(5) // <
    case 2: RETURN(2) // =
    case 3: RETURN(7) // <=
    case 4: RETURN(4) // >
    case 5: RETURN(3) // <>
    case 6: RETURN(6) // >=
    case 7:
    default: MError("\"GetCmpCode\"-type of comparison is incorrect."); RETURN(0)
  }
}

int GetNum(Mes *ms,int ind, int immed)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&ms->m.s[ms->i])
  char   *s=ms->m.s; long l=ms->m.l; long i=ms->i;
  char    c=ms->c[ind]; int *n=&ms->n[ind]; char *df=&ms->f[ind];
  char    cn;
  VarNum *mvi=&ms->VarI[ind],*vnt;
  char    ch,set,vf,ivf/*,*macro*/;
  int     vi;

  *n=0; *df=0; cn=0;
  mvi->Num=0; mvi->Type=0; mvi->IType=0; mvi->Check=0;
  vf=ivf=0; set=0;
  do{
    ch=s[i];
    switch(ch){
      case    0: goto _ok;
      case  'd': *df=1; ++i; continue;
      case  '<': cn|=1; ++i; continue;
      case  '=': cn|=2; ++i; continue;
      case  '>': cn|=4; ++i; continue;
      case  '?': set=1; ++i; continue;
      case  'v':  if(vf!=0) ivf=3; else vf=3; ++i; continue;
      case  'w':  if(vf!=0) ivf=4; else vf=4; ++i; continue;
      case  'x':  if(vf!=0) ivf=5; else vf=5; ++i; continue;
      case  'y':  if(vf!=0) ivf=6; else vf=6; ++i; continue;
      case  'z':  if(vf!=0) ivf=7; else vf=7; ++i; continue;
      case  'e':  if(vf!=0) ivf=8; else vf=8; ++i; continue;
////      case  'a':  if(vf!=0) ivf=8; else vf=8; ++i; continue;
////      case  'b':  if(vf!=0) ivf=9; else vf=9; ++i; continue;
      case  ' ':
//      case  '[':
//      case  ']':
      case 0x0D:
      case 0x0A:
      case 0x09: ++i; continue;
      case  '$': // �����
        ms->i=i;
        vnt=GetMacro(FindMacro(ms,0));
        i=ms->i;
        VNCopy(vnt,mvi);
        if(set){
          if(cn!=0){ MError("\"GetNum\"-cannot set macro here."); goto _over; }
          mvi->Check=1; //?
          goto _ok;
        }else{
          switch(mvi->Type){
            case 0: *n=ERMFlags[mvi->Num-1]; break; // flags
            case 2: *n=ERMVar[mvi->Num-1]; break; // f...t
            case 3: *n=ERMVar2[mvi->Num-1]; break; // v
            case 4: *n=ERMVarH[ERMW][mvi->Num-1]; break; // w
            case 5: *n=ERMVarX[mvi->Num-1]; break; // x
            case 6: // y
              if(mvi->Num<0) *n=ERMVarYT[-mvi->Num-1];
              else                *n=ERMVarY[mvi->Num-1];
              break;
////            case 8: // a
////              if(CheckScope()){ *n=0; goto _over; }
////              *n=ERMScope->Var[mvi->Num-1];
////              break;
//            default: MError("\"GetNum\"-wrong indexing var type (f...t,v,w,x,y)."); goto _over;
          }
          mvi->Check=(Word)GetCmpCode(cn);
          goto _ok;
        }
      default:
        if((ch>='f')&&(ch<='t')){ // ����������
          vi=ch-'e'; ++i;
          mvi->Num=vi;
          if(vf!=0){
            ivf=2;
            mvi->Type=vf;
            mvi->IType=2;
          }else{
            vf=2;
            mvi->Type=2;  // f...t
          }
          if(set){ // ���������
            if(cn!=0){ MError("\"GetNum\"-cannot set and check both (?f...t var)."); goto _over; }
            mvi->Check=1; //?
//            if(ivf!=0){ Error(); goto _over; }
            goto _ok;
          }else{   // ������ � ������������
            if(immed){
              if(mvi->IType!=0){// ���� ���� ��������������
                *n=ERMVar[vi-1];
                vi=*n;
              }
              switch(vf){
                case 2: *n=ERMVar[vi-1]; break; // f...t
                case 3: *n=ERMVar2[vi-1]; break; // v
                case 4: *n=ERMVarH[ERMW][vi-1]; break; // w
                case 5: *n=ERMVarX[vi-1]; break; // x
                case 6:
                  if(vi<0) *n=ERMVarYT[-vi-1];
                  else     *n=ERMVarY[vi-1];
                  break; // y
                case 7: *n=vi; break; // z
                case 8:
                  if(vi<0) *n=(int)ERMVarFT[-vi-1];
                  else     *n=(int)ERMVarF[vi-1];
                  break; // e
////                case 8: // a
////                  if(CheckScope()){ *n=0; goto _over; }
////                  *n=ERMScope->Var[vi-1];
////                  break;
////                case 9: // b
////                  if(CheckScope()){ *n=0; goto _over; }
////                  *n=-vi;
////                  break;
//                default: MError("\"GetNum\"-wrong var type (f...t,v,w,x,y,z)."); goto _over;
              }
            }
            mvi->Check=(Word)GetCmpCode(cn);
            goto _ok;
          }
        }else{
          ms->i=i;
          if(GetSubNum(ms,ind)){ MError("\"GetNum\"-cannot parse a number."); goto _over; }
          i=ms->i;
          if(vf){
            vi=*n;
//            if((vi<-10)||(vi>10000)){ MError("\"GetNum\"-wrong variable index (-10...10000)."); goto _over; }
            ////////////// mvi->Num=(Word)vi;
            if(vi<VN_MINVAL || vi>VN_MAXVAL){
              MError("\"GetNum\"-wrong variable value (-1048575...1048575)."); goto _over;
            }
            mvi->Num=vi;
            mvi->Type=vf;
            mvi->IType=ivf;
            if(set){
              if(cn!=0){ MError("\"GetNum\"-cannot set and check both."); goto _over; }
              mvi->Check=1; //?
              goto _ok;
            }else{
              if(immed){
                if(ivf!=0){// ���� ���� ��������������
                  switch(ivf){
                    case 2: *n=ERMVar[vi-1]; break; // f...t
                    case 3: *n=ERMVar2[vi-1]; break; // v
                    case 4: *n=ERMVarH[ERMW][vi-1]; break; // w
                    case 5: *n=ERMVarX[vi-1]; break; // x
                    case 6:
                      if(vi<0) *n=ERMVarYT[-vi-1]; // y
                      else     *n=ERMVarY[vi-1];
                      break; // y
////                    case 8: // a
////                      if(CheckScope()){ *n=0; goto _over; }
////                      *n=ERMScope->Var[vi-1];
////                      break;
                    default: MError("\"GetNum\"-wrong indexing var type (f...t,v,w,x,y)."); goto _over;
                  }
                }
                vi=*n;
//                if((vi<-10)||(vi>10000)){ MError("\"GetNum\"-wrong index (-10...10000)."); goto _over; }
                switch(vf){
                  case 3: *n=ERMVar2[vi-1]; break; // v
                  case 4: *n=ERMVarH[ERMW][vi-1]; break; // w
                  case 5: *n=ERMVarX[vi-1]; break; // x
                  case 6:
                    if(vi<0) *n=ERMVarYT[-vi-1];
                    else     *n=ERMVarY[vi-1];
                    break; // y
                  case 7: *n=vi; break; // z
                  case 8:
                    if(vi<0)  *n=(int)ERMVarFT[-vi-1];
                    else      *n=(int)ERMVarF[vi-1];
                    break; // e
////                  case 8: // a
////                    if(CheckScope()){ *n=0; goto _over; }
////                    *n=ERMScope->Var[vi-1];
////                    break;
////                  case 9: // b
////                    if(CheckScope()){ *n=0; goto _over; }
////                    *n=-vi;
////                    break;
//                  default: MError("\"GetNum\"-wrong var type (v,w,x,y,z)."); goto _over;
                }
              }
              mvi->Check=(Word)GetCmpCode(cn);
              goto _ok;
            }
          }else{
            if(*n<VN_MINVAL || *n>VN_MAXVAL){
              MError("\"GetNum\"-wrong constant value (-1048575...1048575)."); goto _over;
            }
            mvi->Num=*n;
            mvi->Type=0;
            mvi->IType=0;
            mvi->Check=(Word)GetCmpCode(cn);
            if(set){ MError("\"GetNum\"-cannot get flag."); goto _over;} // ������ ���� ����������
          }
          goto _ok;
        }
    }
_ok:
    if(c==1) goto _ok3;
    if(ch==0){ MError("\"GetNum\"-unexpected end of line."); goto _over; }
    if((ch!=c)&&(i<l)) continue;
    ms->i=i+1; // ��������� ������������� ������
    goto _ok2;
  }while(1);
_ok3:
  ms->i=i;
_ok2:
  RETURN(0)
_over: // ��������� ����������� �������
  while(s[i]==' ') ++i;
  goto _ok;
}

int GetFlags(Mes *m)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&m->m.s[m->i])
  Mes  M;
  int  i,ind;

  M.m.s=m->m.s;
  M.m.l=m->m.l;
  M.i=m->i;
  for(i=0;i<16;i++){
    SetMem(&m->Efl[0][i][0],sizeof(VarNum),0);
    SetMem(&m->Efl[0][i][1],sizeof(VarNum),0);
    SetMem(&m->Efl[1][i][0],sizeof(VarNum),0);
    SetMem(&m->Efl[1][i][1],sizeof(VarNum),0);
//    *(long *)&m->Efl[0][i][0]=0; // �� ����������
//    *(long *)&m->Efl[0][i][1]=0; // �� ����������
//    *(long *)&m->Efl[1][i][0]=0; // �� ����������
//    *(long *)&m->Efl[1][i][1]=0; // �� ����������
/*
    m->Efl[0][i][0].Type=0; // �� ����������
    m->Efl[0][i][0].IType=0; // �� ����������
    m->Efl[0][i][1].Check=0; // �� ����������
    m->Efl[1][i][0].Type=0; // �� ����������
    m->Efl[1][i][0].IType=0; // �� ����������
    m->Efl[1][i][1].Check=0; // �� ����������
*/
  }
  if(M.m.s[M.i]=='&'){
    ++M.i;
    for(i=0;i<16;i++){
      M.n[i]=0; M.c[i]=1;
      if(GetNum(&M,i,0)) RETURN(-1)
      if(M.VarI[i].Check!=0){ MError("\"GetFlags\"-cannot get or campare first argument in \"&...\" part."); RETURN(-1) }
      if(M.VarI[i].Type!=0){ // ��������� �� ����������
        if(M.VarI[i].Num==0){ MError("\"GetFlags\"-wrong var index or syntax in \"&...\" part."); RETURN(-1) }
        VNCopy(&M.VarI[i],&m->Efl[0][i][0]);
        if(GetNum(&M,i,0)){ MError("\"GetFlags\"-cannot get number in \"&...\" part."); RETURN(-1) }
        if(M.VarI[i].Check<2){ MError("\"GetFlags\"-cannot set or get second argument in \"&...\" part (only check)."); RETURN(-1) }
        if(M.VarI[i].Type==0){  // ���������� � ������
          M.VarI[i].Num=M.n[i]; // �������� ���
        }
        VNCopy(&M.VarI[i],&m->Efl[0][i][1]);
      }else{
        ind=M.n[i];
        if(ind<0){
          ind=-ind;
          M.VarI[i].Check=3;
        }else{
          M.VarI[i].Check=2;
        }
        if((ind<1)||(ind>1000)){ MError("\"GetFlags\"-wrong index of flag in \"&...\" part."); RETURN(-1) }
        M.VarI[i].Num=ind;
        M.VarI[i].Type=1; // ����
        M.VarI[i].IType=0;
        VNCopy(&M.VarI[i],&m->Efl[0][i][0]);
      }
      if(M.m.s[M.i]==SLCH) ++M.i;
      else break;
    }
    m->i=M.i;
  }
  if(M.m.s[M.i]=='|'){
    ++M.i;
    for(i=0;i<16;i++){
      M.n[i]=0; M.c[i]=1;
      if(GetNum(&M,i,0)) RETURN(-1)
      if(M.VarI[i].Check!=0){ MError("\"GetFlags\"-cannot get or campare first argument in \"|...\" part."); RETURN(-1) }
      if(M.VarI[i].Type!=0){ // ��������� �� ����������
        if(M.VarI[i].Num==0){ MError("\"GetFlags\"-wrong var index or syntax in \"|...\" part."); RETURN(-1) }
        VNCopy(&M.VarI[i],&m->Efl[1][i][0]);
        if(GetNum(&M,i,0)){ MError("\"GetFlags\"-cannot get number in \"|...\" part."); RETURN(-1) }
        if(M.VarI[i].Check<2){ MError("\"GetFlags\"-cannot set or get second argument in \"|...\" part (only check)."); RETURN(-1) }
        if(M.VarI[i].Type==0){  // ���������� � ������
          M.VarI[i].Num=M.n[i]; // �������� ���
        }
        VNCopy(&M.VarI[i],&m->Efl[1][i][1]);
      }else{
        ind=M.n[i];
        if(ind<0){
          ind=-ind;
          M.VarI[i].Check=3;
        }else{
          M.VarI[i].Check=2;
        }
        if((ind<1)||(ind>1000)){ MError("\"GetFlags\"-wrong index of flag in \"|...\" part."); RETURN(-1) }
        M.VarI[i].Num=ind;
        M.VarI[i].Type=1; // ����
        M.VarI[i].IType=0;
        VNCopy(&M.VarI[i],&m->Efl[1][i][0]);
      }
      if(M.m.s[M.i]==SLCH) ++M.i;
      else break;
    }
    m->i=M.i;
  }
  RETURN(0)
}
//#undef MError

int GetNumAutoSelf(Mes *ms,int fl,int immed)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&ms->m.s[ms->i])
  int  i;
  char che;
//  ms->efl=ms->dfl=0;
  che=ms->c[0];
  for(i=0;i<16;i++){
    ms->n[i]=0; ms->c[i]=1;
    if(GetNum(ms,i,immed)) RETURN(0)
    if(ms->m.s[ms->i]==SLCH) ++ms->i;
    else{
      if(fl){ if(GetFlags(ms)) RETURN(-2) }
      if(che!=1){ if(ms->m.s[ms->i]==che) ++ms->i; }
      RETURN(i+1)
    }
  }
  RETURN(i)
}

int GetNumAuto(Mes *ms)  { return GetNumAutoSelf(ms,0,1); }
int GetNumAutoFl(Mes *ms){ return GetNumAutoSelf(ms,1,0); }

int GetSpecNum(Mes *ms)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&ms->m.s[ms->i])
  char *s=ms->m.s; long l=ms->m.l; long i=ms->i;
  int *n=&ms->n[0];

  char ch;
  *n=0;
  do{
    if(i>l) RETURN(-1)
    ch=s[i];
    if((ch<1)||(ch>0x0F)){ ms->i=i; RETURN(0)}
    if(ch!=0x0F){
      if(ch==0x0B) ch=0;
      *n*=10; *n+=(int)ch;
    }
    ++i;
  }while(1);
}
void PutSpecNum(Mes *ms,int len)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&ms->m.s[ms->i])
  char *s=ms->m.s; long l=ms->m.l; int n=ms->n[0];

  int k,j,d;
  char ch,ds[10];

  for(k=0;k<10;k++){
    d=n%10;
    ds[9-k]=(char)d;
    n/=10;
  }
  for(k=0;k<10;k++){ if(ds[k]!=0) break; }
  for(j=0;k<10;k++,j++){
      ch=ds[k]; if(ch==0) ch=0x0B;
      s[j]=ch;
  }
  for(;j<len;j++) s[j]=0x0F;
  ms->i=l;
  RETURNV
}

int MakeSpec(_Mes_ *m,int nn)
{
  #include "templ.h"
  int lind;
  Mes M;
  M.m.s=m->s; M.m.l=m->l; M.i=0;

  if(M.m.s[0]<0x0F){ // ����������� �������
    if(GetSpecNum(&M)) RETURN(0)
    if(M.n[0]!=nn) RETURN(0) // �� ���
    RETURN(1);
  }else{
    M.c[0]=1;
    if(GetNum(&M,0,1)) RETURN(0)
    if(M.n[0]!=nn) RETURN(0) // �� ���
    lind=M.i; M.i=0;
    PutSpecNum(&M,lind);
    RETURN(1)
  }
}

//////////////////////////////////////////////////////////////
#define SPECSKILL 353
static FHSI_0[SSNUM]={300,0,23,302,295,3,297,304,41,299,294,13,69,4,145,292,305,296,301,303,293,298,102,16,26,62,20,8};
static FHSI_C[MONNUM]={
/*  0*/  158,159, 1,160, 2,161, 5,162, 12,163, 7,164, 165,166,
/* 14*/  167,168, 17,169, 21,170, 31,171, 19,172, 22,173, 174,175,
/* 28*/  176,177, 32,178, 34,179, 44,180, 33,181, 37,182, 183,184,
/* 42*/  51,185, 53,186, 48,187, 50,188, 55,189, 49,190, 155,191,
/* 56*/  71,192, 64,193, 67,194, 65,195, 66,196, 68,197, 198,199,
/* 70*/  87,200, 80,201, 83,202, 203,204, 82,205, 86,206, 207,208,
/* 84*/  100,209, 103,210, 98,211, 101,212, 99,213, 96,214, 215,149,
/* 98*/  113,216, 114,217, 116,220, 117,218, 112,219, 119,221, 222,223,
/*112*/  226,129,130,131,234,235,
/*118*/  224,225, 128,231,SPECSKILL,228,SPECSKILL,230,SPECSKILL,227,SPECSKILL,229, 232,233,
/*132*/  236,237,238,239,147,148,240,241,
/*140*/  242,243,244,245,246,247,6,248,249,356,
/*150*/  250,251,252,253,254,255,256,257,258,
/*159*/  259,
/*160*/  260,261,262,263,
/*164*/  264,265,266,267,
/*168*/  268,269,270,271,272,273,
/*174*/  274,275,276,277,278,279,280,281,282,
/*183*/  274,275,276,277,278,279,280,281,282,
/*192*/  283,284,285,286,355
};
static FHSI_R[10]={287,38,288,60,94,111,15,/*Mithril*/290,/*wood+ore*/289,/*all other res*/291};
static FHSI_S[80]={
/* 0*/  342,348,318,354,312,309,314,350,311,325,
/*10*/  326,339,323,136,321,138,30,315,324,45,
/*20*/  11,57/*Fireball*/,63/*Inferno*/,73,72,313,330,329,307,336,
/*30*/  306,334,351,320,319,344,316,25,88,76,
/*40*/  341,9,333,338,108,10,77,141,14,346,
/*50*/  328,29,340,46,327,24,335,317,310,332,
/*60*/  40,345,331,349,347,343,337,322,352,308,
/*70*/  0,0,0,0,0,0,0,0,0,0
};
static FHSI_5[1]={144};
static FHSI_7[1]={151};
static FHSI_8[2]={156,157};
int FindHeroSpecIcon(int Hn)
{
  #include "templ.h"
  Dword *dsp=(Dword *)&HSpecTable[Hn];
//  if(Hn==79) RETURN(FHSI_8[0]+1); // Nagash
//  if(Hn==91) RETURN(FHSI_8[1]+1); // Jeddit
  switch(dsp[0]){
    case 0: // 0/$ ���� �� ��������� ������.
      if(dsp[1]<0 || dsp[1]>=SSNUM) RETURN(SPECSKILL+1)
      RETURN(FHSI_0[dsp[1]]+1)
    case 1: // 1/$ ���� �� ���������
      if(dsp[1]<0 || dsp[1]>=MONNUM) RETURN(SPECSKILL+1)
      RETURN(FHSI_C[dsp[1]]+1)
    case 2: // 2/$ ���� �� ��������
      if(dsp[1]<0 || dsp[1]>=10) RETURN(SPECSKILL+1)
      RETURN(FHSI_R[dsp[1]]+1)
    case 3: // 3/$ ���� �� ����������
      if(dsp[1]<0 || dsp[1]>=80) RETURN(SPECSKILL+1)
      RETURN(FHSI_S[dsp[1]]+1)
    case 4: // 4/$/$at/$df/$damage ���� �� ������ ���������
      if(dsp[1]<0 || dsp[1]>=MONNUM) RETURN(SPECSKILL+1)
      RETURN(FHSI_C[dsp[1]]+1)
    case 5: // 5/$ ���� �� �������� � ��?
      if(dsp[1]<2 || dsp[1]>=3) RETURN(SPECSKILL+1)
      RETURN(FHSI_5[dsp[1]-2]+1)
    case 6: // 6/$1/$2/$3 ���� �� ��������
      if(dsp[6]<0 || dsp[6]>=MONNUM) RETURN(SPECSKILL+1)
      RETURN(FHSI_C[dsp[6]]+1)
    case 7: // 7/$a/$d ���� �� �������� (7/???/at/df/damage)
      RETURN(FHSI_7[0]+1)
    case 8: // 8/$ ����� ����.
      if(dsp[1]<1 || dsp[1]>=3 ) RETURN(SPECSKILL+1)
      RETURN(FHSI_8[dsp[1]-1]+1)
    case -1: // Adrienne - expert Fire Magic
      RETURN(145+1)
    default:
      break;
  }
  RETURN(SPECSKILL+1)
}

int MakeHeroSpec(int Hn,Mes *M,int Num)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&M->m.s[M->i])
//  Dword *dsp=(Dword *)(0x678420+0x28*Hn);
  Dword *dsp=(Dword *)&HSpecTable[Hn];
  if(Num<2) RETURN(-1)
  if((M->n[0]<0)||(M->n[0]>8)) RETURN(-1)
  dsp[0]=M->n[0]; dsp[1]=dsp[1]*M->f[1]+M->n[1];
//              if(M.n[0]==0){ // 0/$ ���� �� ��������� ������.
//              }else if(M.n[0]==1){ // 1/$ ���� �� ���������
//              }else if(M.n[0]==2){ // 2/$ ���� �� ��������
//              }else if(M.n[0]==3){ // 3/$ ���� �� ����������
  if(M->n[0]==4){ // 4/$/$a/$d/$h ���� �� ������ ���������
    if(Num<5) RETURN(-1)
    dsp[2]=dsp[2]*M->f[2]+M->n[2]; dsp[3]=dsp[3]*M->f[3]+M->n[3]; dsp[4]=dsp[4]*M->f[4]+M->n[4];
  }else if(M->n[0]==5){ // 5/$ ���� �� �������� � ��?
  }else if(M->n[0]==6){ // 6/$1/$2/$3 ���� �� ��������
    if(Num<4) RETURN(-1)
    dsp[5]=dsp[5]*M->f[2]+M->n[2]; dsp[6]=dsp[6]*M->f[3]+M->n[3];
  }else if(M->n[0]==7){ // 7/$a/$d ���� �� ��������
    dsp[2]=dsp[2]*M->f[2]+M->n[2];
  }else if(M->n[0]==8){ // 8/$ ����� ����.
  }
  RETURN(0)
}

long SetMes(_Mes_ *mt,_Mes_ *mf,long sf)
{
  #include "templ.h"
  long i=sf,i1,lt,lf;
  char ch,*to,*from;
  to=mt->s;  lt=mt->l;
  if(mf!=0){ from=mf->s; lf=mf->l; }else{ from=0; lf=0; }
  for(i1=0;i1<lt;i1++){
    if(to[i1]>=0x0F) goto _ok0; // �������� ����������� ����������
  }
  RETURN(-1)
_ok0:
  if(from==0) goto _ok2;
  if(sf==0){ // ����� ������� ��������� - ����������� �� �����
    for(i=0;i<lf;i++){
      if(from[i]>=0x0F) goto _ok1; // �������� ����������� ����������
    }
    RETURN(-1)
  }else{
    while((i<lf)){ ++i; if(from[i-1]==STRCH) goto _ok1;}
    RETURN(-1)
  }
_ok1:
  for(;i<lf;i++){
    ch=from[i];
    if((sf!=0)&&(ch==STRCH)) goto _ok2;
    to[i1++]=ch;
    if(i1==lt) goto _ok3; // ��� ��� ������ ���������
  }
//  return -1;
_ok2:
  for(;i1<lt;i1++) to[i1]=0x0F; // ���������� ��������� �������
_ok3:
  RETURN(i+1)
}

int MesManOld(Mes *ms,_Mes_ *p)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&ms->m.s[ms->i])
  _Mes_  m,*mp;
  struct _Main_     *MS;
  struct _GlbEvent_ *GEp0,*GEp1,*GEp;
  int     i,n=ms->n[0];

  switch(n){
    case -1:
      if(SetMes(p,0,0)==-1) RETURN(-1) else RETURN(0)
    case  0:
      m.s=ERM2String(&ms->m.s[ms->i],0,&i);
      m.l=StrLen(m.s); //
      if(SetMes(p,&m,0)==-1) RETURN(-1)
      ms->i+=i;
      RETURN(0)
    default:
      MS=Main;
      GEp0=MS->GEp0;  //  GEp0=(_GlbEvent_ *)  *(Dword *)(Esi_+0x84);
      GEp1=MS->GEp1;  //  GEp1=(_GlbEvent_ *)  *(Dword *)(Esi_+0x88);
      for(GEp=GEp0;GEp<GEp1;GEp++){
        mp=&GEp->Mes.m;
        if(MakeSpec(&GEp->Mes.m,n)){
          if(SetMes(p,mp,0)==-1) RETURN(-1) else RETURN(0)
        }
      }
      RETURN(-1)
  }
}

int NewMesMan(Mes *ms,_AMes_ *ap,int ind)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&ms->m.s[ms->i])
  _Mes_  *mp;
  struct _Main_     *MS;
  struct _GlbEvent_ *GEp0,*GEp1,*GEp;
  int     i;

  switch(ms->n[ind]){
    case -1: MesMan(ap,0,0); RETURN(0)
    case  0:
      if((ms->VarI[ind].Type==7)||(ms->VarI[ind].Type==9)){
        ApplyString(ms,ind,ap);
      }else{
        MesMan(ap,ERM2String(&ms->m.s[ms->i],0,&i),0);
        ms->i+=i;
      }
      RETURN(0)
    default:
      if((ms->VarI[ind].Type==7)||(ms->VarI[ind].Type==9)){
        ApplyString(ms,ind,ap);
        RETURN(0)
      }else{
        MS=Main;
        GEp0=MS->GEp0;  //  GEp0=(_GlbEvent_ *)  *(Dword *)(Esi_+0x84);
        GEp1=MS->GEp1;  //  GEp1=(_GlbEvent_ *)  *(Dword *)(Esi_+0x88);
        for(GEp=GEp0;GEp<GEp1;GEp++){
          mp=&GEp->Mes.m;
          if(MakeSpec(&GEp->Mes.m,ms->n[ind])){
            MesMan(ap,mp->s,0); RETURN(0)
          }
        }
      }
      RETURN(-1)
  }
}

int AddCommand(_ToDo_ *sp,int b,int e)
{
  #include "templ.h"
  _PostERM_   *PERM;
  int   i,l;
  char *s,*s1;

  PERM=PostERM;
  l=PERM->l;
  s=&PERM->s[l];
  if(PERM->p==0){ // ��� �� ����� ��������������
    *s++='!'; *s++='@'; // ������� ������������
    *s++='Z'; *s++='V'; *s++='S'; *s++='E';
    PERM->p=l+2;
    l+=6;
  }
  *s++='!'; *s++='#'; l+=2;
  s1=sp->Self.s;
  for(i=0;i<sp->Self.l;i++) *s++=*s1++;
  l+=i;
  s1=sp->Com.s;
  for(i=b;i<e;i++) *s++=s1[i];
  *s++=';'; l+=e-b+1;
  *s=0;
  if(l>PERM->f) RETURN(1)
  PERM->l=l;
  PERM->owner->l=l;
  RETURN(0)
}

int ProcessDisable(_ToDo_ *sp,int z)
{
  #include "templ.h"
  _Cmd_  *cp;
  _ToDo_ *td;
  int     i;
  Dword   event,object;
  Byte    pr,cur;

  if((z<0)||(z>7)){MError("Z command fas a wrong parameter (Z4...Z7)."); RETURN(1) }
  if((z>=0)&&(z<=3)){MError("Z0...Z3 command is obsolete and are not supported anymore."); RETURN(1) }
  object=sp->Pointer;
  cp=Heap;
  while(cp->Event!=0){
    if(z>3){ // ���������
      if(cp->Event&0x20000000){ // LE
        event=cp->Event&0x0FFFFFFF;
//        object=sp->Pointer2;
      }else{                    // NO
        event=cp->Event;
//        object=sp->Pointer;
      }
      if(event==object){ // ! �����
//        if(sp->Pointer2!=0){MError("!!LE:Z command is obsolete and works only with LEx/y/l trigger/receiver.\n For new style LE$ you should use conditional execution."); goto l_exit; }
        pr=cp->DisabledPrev;
        cp->DisabledPrev=cp->Disabled;
        switch(z){
          case  7: cur=pr; break;
          case  6: cur=!pr; break;
          case  5: cur=1; break;
          default: cur=0; break;
        }
        cp->Disabled=cur;
      }
    }else{ // ��������
      for(i=0;i<cp->Num;i++){
        td=&cp->ToDo[i];
        if(td->Pointer==object){ // ! �����
          pr=td->DisabledPrev;
          td->DisabledPrev=td->Disabled;
          switch(z){
            case  3: cur=pr; break;
            case  2: cur=!pr; break;
            case  1: cur=1; break;
            default: cur=0; break;
          }
          td->Disabled=cur;
        }
      }
    }
    if(cp->Next==0) break;
    cp=cp->Next;
  }
  RETURN(0)
}

int CheckFlags(VarNum (*Efl)[16][2])
{
  #include "templ.h"
  int i,j,vi,tp,itp,n,n2,fl,zind,zind2,evar=0;
  float v1,v2;
  char *txt1,*txt2;
  if((Efl[0][0][0].Type==0)&&(Efl[1][0][0].Type==0)) RETURN(0)
  for(j=0;j<2;j++){
    for(i=0;i<16;i++){
      zind=zind2=0;
      vi=Efl[j][i][0].Num;
      tp=Efl[j][i][0].Type;
      itp=Efl[j][i][0].IType;
      if(tp==0) continue; // �� �����
      switch(itp){
        case 0: break;
        case 2: vi=ERMVar[vi-1]; break; // f...t
        case 3: vi=ERMVar2[vi-1]; break; // v
        case 4: vi=ERMVarH[ERMW][vi-1]; break; // w
        case 5: vi=ERMVarX[vi-1]; break; // x
        case 6:
          if(vi<0) vi=ERMVarYT[-vi-1];
          else     vi=ERMVarY[vi-1];
          break; // y
////        case 8: // a
////          if(CheckScope()) return 0;
////          vi=ERMScope->Var[vi-1];
////          break;
        default: MError("\"CheckFlags\"-wrong indexing var in first argument of \"&|...\" part (f...t,v,w,x,y)."); RETURN(1)
      }
      switch(tp){
        case 1: // ����
          if(Efl[j][i][0].Check==3){ // ������ ���� �������
            if(j==0){ if(ERMFlags[vi-1]==1) goto ToOr; /*return 1;*/ }
            else{     if(ERMFlags[vi-1]==0) RETURN(0) }
          }else{ // ������ ���� ����������
            if(j==0){ if(ERMFlags[vi-1]==0) goto ToOr; /*return 1;*/ }
            else{     if(ERMFlags[vi-1]==1) RETURN(0) }
          }
          continue; // � ���������� ��������
        case 2: // f...t
          n=ERMVar[vi-1];
          break;
        case 3: // v1...1000
          n=ERMVar2[vi-1];
          break;
        case 4: // w1...100
          n=ERMVarH[ERMW][vi-1];
          break;
        case 5: // x1...16
          n=ERMVarX[vi-1];
          break;
        case 6: // y1...100
          if(vi<0) n=ERMVarYT[-vi-1];
          else     n=ERMVarY[vi-1];
          break;
        case 7: // z1...500
          zind=vi; n=zind;
          break;
        case 8: // e1...100
          evar=1;
          v1=ERMVarF[vi-1];
          n=(int)v1;
          break;
////        case 8: // a1...1000
////          if(CheckScope()) return 1;
////          n=ERMScope->Var[vi-1];
////          break;
////        case 9: // b1...500
////          if(CheckScope()) return 1;
////          zind=-vi; n=zind;
////          break;
        default: MError("\"CheckFlags\"-wrong var index in first argument of \"&|...\" part (1...[1000])."); RETURN(1)
      }
      vi=Efl[j][i][1].Num;
      switch(Efl[j][i][1].IType){
        case 0: break;
        case 2: vi=ERMVar[vi-1]; break; // f...t
        case 3: vi=ERMVar2[vi-1]; break; // v
        case 4: vi=ERMVarH[ERMW][vi-1]; break; // w
        case 5: vi=ERMVarX[vi-1]; break; // x
        case 6:
          if(vi<0) vi=ERMVarYT[-vi-1];
          else     vi=ERMVarY[vi-1];
          break; // y
////        case 8: // a
////          if(CheckScope()) return 0;
////          vi=ERMScope->Var[vi-1];
////          break;
        default: MError("\"CheckFlags\"-wrong var in first argument of \"&|...\" part (f...t,v,w,x,y)."); RETURN(1)
      }
      switch(Efl[j][i][1].Type){
        case 0: // �����
          n2=vi;
          break;
        case 2: // f...t
          n2=ERMVar[vi-1];
          break;
        case 3: // v1...1000
          n2=ERMVar2[vi-1];
          break;
        case 4: // w1...100
          n2=ERMVarH[ERMW][vi-1];
          break;
        case 5: // x1...16
          n2=ERMVarX[vi-1];
          break;
        case 6: // y1...100
          if(vi<0) n2=ERMVarYT[-vi-1];
          else     n2=ERMVarY[vi-1];
          break;
        case 7: // z1...500
          zind2=vi; n2=zind;
          break;
        case 8: // e1...100
          evar+=2;
          v2=ERMVarF[vi-1];
          n2=(int)v2;
          break;
////        case 8: // a1...1000
////          if(CheckScope()) return 1;
////          n2=ERMScope->Var[vi-1];
////          break;
////        case 9: // b1...500
////          if(CheckScope()) return 1;
////          zind2=-vi; n2=zind;
////          break;
        default: MError("\"CheckFlags\"-wrong var in second argument of \"&|...\" part (#,f...t,v,w,x,y)."); RETURN(1)
      }
      fl=0;
      if((zind!=0)&&(zind2!=0)){ // ���������� ��������� ����������
        if((zind<-10)||(zind==0)||(zind2<-10)||(zind2==0)){
          MError("\"CheckFlags\"-wrong z var index in \"&|...\" part.");
          RETURN(1)
        }
        if(zind>1000) txt1=StringSet::GetText(zind);
        else if(zind>0) txt1=ERMString[zind-1];
        else txt1=ERMLString[-zind-1];
        if(zind2>1000) txt2=StringSet::GetText(zind2);
        else if(zind2>0) txt2=ERMString[zind2-1];
        else txt2=ERMLString[-zind2-1];
        fl=StrCmpExt(txt1,txt2);
////        if(zind<0){
////          if(zind2<0){
////            fl=StrCmpExt(ERMScope->String[-zind-1],ERMScope->String[-zind2-1]);
////          }else{
////            fl=StrCmpExt(ERMScope->String[-zind-1],ERMString[zind2-1]);
////          }
////        }else{
////          if(zind2<0){
////            fl=StrCmpExt(ERMString[zind-1],ERMScope->String[-zind2-1]);
////          }else{
////            fl=StrCmpExt(ERMString[zind-1],ERMString[zind2-1]);
////          }
////        }
        switch(Efl[j][i][1].Check){
          case 2: // =
            break;
          case 3: // <>,>< (!=)
            if(fl) fl=0; else fl=1;
            break;
          default: MError("\"CheckFlags\"-Z vars may be compared for = or <> only in \"&|...\" part (<,=,<=,=<,>,<>,><,>=,=>)."); RETURN(1)
        }
      }else{
        if(evar==3){ // both e-vars
          switch(Efl[j][i][1].Check){
            case 5: // <
              if(v1<v2) fl=1;
              break;
            case 2: // =
              if(v1==v2) fl=1;
              break;
            case 7: // <=,=<
              if(v1<=v2) fl=1;
              break;
            case 4: // >
              if(v1>v2) fl=1;
              break;
            case 3: // <>,>< (!=)
              if(v1!=v2) fl=1;
              break;
            case 6: // >=,=>
              if(v1>=v2) fl=1;
              break;
            default: MError("\"CheckFlags\"-wrong comparison type in \"&|...\" part (<,=,<=,=<,>,<>,><,>=,=>)."); break;
          }
        }else{
          switch(Efl[j][i][1].Check){
            case 5: // <
              if(n<n2) fl=1;
              break;
            case 2: // =
              if(n==n2) fl=1;
              break;
            case 7: // <=,=<
              if(n<=n2) fl=1;
              break;
            case 4: // >
              if(n>n2) fl=1;
              break;
            case 3: // <>,>< (!=)
              if(n!=n2) fl=1;
              break;
            case 6: // >=,=>
              if(n>=n2) fl=1;
              break;
            default: MError("\"CheckFlags\"-wrong comparison type in \"&|...\" part (<,=,<=,=<,>,<>,><,>=,=>)."); break;
          }
        }
      }
      if(j==0){ if(fl==0) goto ToOr; /*return 1;*/ }  // & all must be
      else{     if(fl==1) RETURN(0) }
    }
    if(j==0){
      if(Efl[0][0][0].Type!=0) RETURN(0) // ���� ���� & ����� � ��� ������� ������
    }
ToOr:; // AND �� ������
  }
  RETURN(1) // � OR �� ����
}

void PutVal(void *dp,char size,Mes *mp,char ind)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&mp->m.s[mp->i])
  int   *dip;
  short *dsp;
  char  *dcp;
  unsigned int   *duip;
  unsigned short *dusp;
  unsigned char  *ducp;
  switch(size){
    //3.58 unsigned support
    case -4:
      duip=(unsigned int *)dp;
      *duip=(*duip)*mp->f[ind]+mp->n[ind];
      break;
    case -2:
      dusp=(unsigned short *)dp;
      *dusp=(unsigned short)((*dusp)*mp->f[ind]+mp->n[ind]);
      break;
    case -1:
      ducp=(unsigned char *)dp;
      *ducp=(unsigned char)((*ducp)*mp->f[ind]+mp->n[ind]);
      break;
    //
    case 4:
      dip=(int *)dp;
      *dip=(*dip)*mp->f[ind]+mp->n[ind];
      break;
    case 2:
      dsp=(short *)dp;
      *dsp=(short)((*dsp)*mp->f[ind]+mp->n[ind]);
      break;
    default: // 1
      dcp=(char *)dp;
      *dcp=(char)((*dcp)*mp->f[ind]+mp->n[ind]);
      break;
  }
  RETURNV
}

int GetVal(void *dp,char size)
{
  #include "templ.h"
  int    v;
  switch(size){
    //3.58 unsigned support
    case -4: v=*((unsigned int *)dp);   break;
    case -2: v=*((unsigned short *)dp); break;
    case -1: v=*((unsigned char *)dp);  break;
    //
    case 4:  v=*((int *)dp);   break;
    case 2:  v=*((short *)dp); break;
    default: v=*((char *)dp);  break;
  }
  RETURN(v)
}

int Apply(void *dp,char size,Mes *mp,char ind)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&mp->m.s[mp->i])
  int v,vf,ivf,p,fl,ret,vi,chk;
  ret=0;
  chk=mp->VarI[ind].Check;
  if(chk!=0){
    ret=1; // ���� �������
    v=GetVal(dp,size);
    p=mp->n[ind];
    fl=0;
    vf=mp->VarI[ind].Type;
    ivf=mp->VarI[ind].IType;
    if(vf!=0){ // ����������
      vi=mp->VarI[ind].Num;
      if(vi==0){ MError("\"Apply\"-wrong var index (1...[10000])."); RETURN(-1) }
      if(chk==1){ // ���������
        switch(ivf){
          case 0: break;
          case 2: vi=ERMVar[vi-1]; break; // f...t
          case 3: vi=ERMVar2[vi-1]; break; // v
          case 4: vi=ERMVarH[ERMW][vi-1]; break; // w
          case 5: vi=ERMVarX[vi-1]; break; // x
          case 6:
            if(vi<0) vi=ERMVarYT[-vi-1];
            else     vi=ERMVarY[vi-1];
            break; // y
////          case 8: // a
////            if(CheckScope()) return -1;
////            vi=ERMScope->Var[vi-1];
////            break;
          default: MError("\"Apply\"-wrong indexing var type in \"?$$$\" (1...[10000])."); RETURN(-1)
        }
        switch(vf){
          case 2: ERMVar[vi-1]=v; break; // f...t
          case 3: ERMVar2[vi-1]=v; break; // v
          case 4: ERMVarH[ERMW][vi-1]=v; break; // w
          case 5: ERMVarX[vi-1]=v; break; // x
          case 6:
            if(vi<0) ERMVarYT[-vi-1]=v;
            else{ if(YVarInsideFunction==0) GEr.WrongYVarUsage(); ERMVarY[vi-1]=v; }
            break; // y
          case 8:
            if(vi<0)  ERMVarFT[-vi-1]=(float)v;
            else      ERMVarF[vi-1]=(float)v;
            break; // e
          case 7: //3.58 z vars
            PutVal(dp,size,mp,ind);
            break;
////          case 8: // a
////            if(CheckScope()) return -1;
////            ERMScope->Var[vi-1]=v;
////            break;
          default: MError("\"Apply\"-wrong var type (f...t,v,w,x,y,e)."); RETURN(-1)
        }
        RETURN(1) // ���� �������
      }
    }
    switch(chk){
      case 1: // <
        if(v<p) fl=1;
        break;
      case 2: // =
        if(v==p) fl=1;
        break;
      case 3: // <=,=<
        if(v<=p) fl=1;
        break;
      case 4: // >
        if(v>p) fl=1;
        break;
      case 5: // <>,>< (!=)
        if(v!=p) fl=1;
        break;
      case 6:
      case 7: // >=,=>
        if(v>=p) fl=1;
        break;
    }
    ERMFlags[0]=(char)fl;
  }else{
    PutVal(dp,size,mp,ind);
  }
  RETURN(ret)
}
//
static char ERMExtDBuf[40][1000];
// [0...32] - �������
// 33 - WeekOfText
char *ERM2String2(int ind,char *mes){
  STARTNC(__FILENUM__*1000000+__LINE__,mes)
  ERMExtDBuf[0][0]=0;
  if((ind<0)||(ind>39)){ MError("\"ERM2String2\"-wrong index (internal)"); RETURN(ERMExtDBuf[0]) }
  _Message2ERM(mes);
  for(int i=0;i<1000;i++) ERMExtDBuf[ind][i]=ERMMesBuf[4][i];
  ERMExtDBuf[ind][999]=0;
  RETURN(ERMExtDBuf[ind])
}

static int IF_N_Ar[9][2];

//////////////////////////////////////////////////////////////
void ProcessCmd(_ToDo_ *sp,int /*FirstPart*/,int PostInstr)
{
  #include "templ.h"
  Word  Id=sp->Type;   // ��� ������� ���������
  Mes   M;
  int   Ind,Num,ns2,i,j,k,Start,cfl;
  int   x,y,l,val;
  char  Cmd;
//  _Main_     *MS;
  _MapItem_  /* *MIp0,*/*MIp;
  _CMonster_ *mp/*, *mp0*/;

//  MS=Main;
//  MIp0=MS->MIp0;   // ����� ��������� ��������
//  MapSize=MS->MapSize; // dx=dy

  M.m.s=sp->Com.s;   // ������ ������-������� � �������� (����� - ;)
    GEr.LastERM(sp->Self.s); // 3.58
  M.m.l=sp->Com.l;    // ����� ������-�������
  M.i=0;
// disable to process
  do{
    Start=Ind=M.i;
    ErrStringPo=&M.m.s[Ind]; // 3.57f extended error log
    Cmd=M.m.s[M.i++];
    M.c[0]=1;
    if((Num=GetNumAuto(&M))==0) goto l_exit;
//    if(CheckFlags(M.efl,M.dfl)) continue;
    if(Cmd=='Z'){
      if(Num!=1) goto l_exit;
      if(ProcessDisable(sp,M.n[0])) goto l_exit;
      if(PostInstr==0){ // �� ����������� ��������������
        if(AddCommand(sp,Start,M.i)) goto l_exit;
      }
      continue;
    }
//    if(sp->Disabled) continue;
    if(sp->Disabled) RETURNV
    switch(Id){
      case 0x4547: // GE
        {
          struct _GlbEvent_ *p=(struct _GlbEvent_ *)sp->Pointer;
          if(Cmd=='M'){ // M# ��� ������������
            if(Num==2){ // � ����������
              if(M.n[0]==1){
                if(M.n[1]==-1){ // M1/-1
                  MesMan(&p->Mes,0,0);
                }else{ // M1/$
                  ApplyString(&M,1,&p->Mes);
                }
              }else{ MError("\"GE:M\"-wrong syntax (M1/$)"); goto l_exit; }
            }else{ // ������ �����
               if(MesManOld(&M,&p->Mes.m)){ MError("\"GE:M\"-cannot set message (M$)"); goto l_exit; }
            }
            break;
          }else if(Cmd=='F'){ // F$ ���� ������� ��������� (� 1-��)
            Apply(&p->FirstDate,2,&M,0);
          }else if(Cmd=='R'){ // R$ ������������� ���������
            Apply(&p->Repeater,2,&M,0);
          }else if(Cmd=='B'){ // B#1/$2 �������
            if(Num<2) goto l_exit;
            if((M.n[0]<0)||(M.n[0]>6)) goto l_exit;
            Apply(&p->Res[M.n[0]],4,&M,1);
          }else if(Cmd=='E'){ // E$ ��������� ������� ������
            if(M.f[0]) p->Colors|=(Byte)(M.n[0]&0x0FF);
            else p->Colors=(Byte)(M.n[0]&0x0FF);
          }else if(Cmd=='N'){ // N$ ��������� ������� ������
              M.n[0]=~M.n[0];
              if(M.f[0]) p->Colors&=(Byte)(M.n[0]&0x0FF);
              else p->Colors=(Byte)(M.n[0]&0x0FF);
          }else if(Cmd=='H'){ // H# ��������� ��������
            Apply(&p->HEnable,1,&M,0);
          }else if(Cmd=='Q'){ // H# ��������� ��������
            Apply(&p->AIEnable,1,&M,0);
          }else if(Cmd=='D'){ // D#1/#2
            if(Num<2){ MError("\"GE:D\"-wrong syntax (D$/$)"); goto l_exit; }
            if((M.n[0]<0)||(M.n[0]>7)){ MError("\"GE:D\"-wrong owner (0...7)"); goto l_exit; }
            if(M.n[1]){ // ���������
              p->Colors&=(Byte)~((Byte)(((Byte)1)<<M.n[0]));
            }else{ // ���������
              p->Colors|=(Byte)(((Byte)1)<<M.n[0]);
            }
          }else if(Cmd==' '){ // ������� ����� ����
          }else{
            Mess(&M);
          }
        }
        break;
      case 0x454C: // LE
        {
          struct _Event_ *p=0;
          Dword MixPos=GetDinMixPos(sp);
          _MapItem_ *mi=GetMapItem2(MixPos);
          _EventPos_ *pos=(_EventPos_ *)mi;
          int tp=CheckPlace4Hero(mi,(Dword **)&pos);
          ERMFlags[995]=0;
//          if(tp!=0x1A){ ERMFlags[998]=1; break; }
          if(tp==6){} // Pandora's Box
          else if(tp!=0x1A){ ERMFlags[1]=1; break; }
          __asm{
            mov    eax,BASE
            mov    eax,[eax]
            add    eax,0x1FBC4 // ->events
            mov    eax,[eax]
            mov    p,eax
          }
          if(p==0){ MError("\"LE\"-cannot find event."); goto l_exit; }
          p=&p[pos->Number];
          if(p==0){ MError("\"LE\"-cannot find event."); goto l_exit; }
          if(Cmd=='M'){
            if(Num==2){ // � ����������
              if(M.n[0]==1){
                if(M.n[1]==-1){ // M1/-1
                  MesMan(&p->Mes,0,0);
                }else{ // M1/$
                  ApplyString(&M,1,&p->Mes);
                }
              }else{ MError("\"LE:M\"-wrong syntax (M1/$)."); goto l_exit; }
            }else{// ������ �����
              if(NewMesMan(&M,&p->Mes,0)){ MError("\"LE:M\"-cannot set message (M$)."); goto l_exit; }
            }
          }else if(Cmd=='G'){ // G#1/$2/$3 �������� � ��� #1 ��� #2(-1 ���) ���-�� #3
            if(Num<3) goto l_exit;
            if((M.n[0]<0)||(M.n[0]>6)) goto l_exit;
            Apply(&p->Guard.Ct[M.n[0]],4,&M,1);
            Apply(&p->Guard.Cn[M.n[0]],4,&M,2);
          }else if(Cmd=='X'){
//            if(M.n[0]!=0) p->fl_G=1; else p->fl_G=0;
             val=p->fl_G&0xFF; // 3.58
             if(Apply(&val,4,&M,0)==0){ // set syntax
                if(val) p->fl_G=1; else p->fl_G=0;
             }
          }else if(Cmd=='E'){ // E$ ����
            Apply(&p->Exp,4,&M,0);
          }else if(Cmd=='P'){ // P$ ����� ����������
            Apply(&p->SpPow,4,&M,0);
          }else if(Cmd=='O'){ // O$ ������
            Apply(&p->Moral,1,&M,0);
          }else if(Cmd=='U'){ // U$ �����
            Apply(&p->Luck,1,&M,0);
          }else if(Cmd=='R'){ // R#1/$2 �������
            if(Num<2) goto l_exit;
            if((M.n[0]<0)||(M.n[0]>7)) goto l_exit;
            if(M.n[0]==7) Apply(&(((short *)p->Res)[1]),2,&M,1);
            else if(M.n[0]==0) Apply(&p->Res[0],2,&M,1);
            else Apply(&p->Res[M.n[0]],4,&M,1);
          }else if(Cmd=='F'){ // F$1/$2/$3/$4 ��������� ������
            if(Num<4) goto l_exit;
            Apply(&p->First[0],1,&M,0);
            Apply(&p->First[1],1,&M,1);
            Apply(&p->First[2],1,&M,2);
            Apply(&p->First[3],1,&M,3);
          }else if(Cmd=='N'){ // N#1/$2/$3 �������� � ���� ���� ������� ���1 �����2 ������3
            if(Num==1){ // 3.58
              val=(long)p->SecondE-(long)p->Second;
              val/=8;
              Apply(&val,4,&M,0);
            }else if(Num<3){ goto l_exit;
            }else{
              if((M.n[0]<0)||(p->Second[M.n[0]]>p->SecondE[0])) goto l_exit;
              Apply(&p->Second[M.n[0]][0],4,&M,1);
              Apply(&p->Second[M.n[0]][1],4,&M,2);
            }
          }else if(Cmd=='A'){ // A#1/$2 �������� � ���� ��� ���1 ���2
            if(Num==1){ // 3.58
//              val=(long)p->ArtifE-(long)p->Artif;
//              val/=4;
              val=p->Arts.GetNum();
              Apply(&val,4,&M,0);
            }else if(Num<2){ goto l_exit;
            }else{
//              if((M.n[0]<0)||(&p->Artif[M.n[0]]>p->ArtifE)) goto l_exit;
//              Apply(&p->Artif[M.n[0]],4,&M,1);
              do{
                if(Apply(&val,4,&M,0)) break;
                int ar=p->Arts.Get(val);
                if(Apply(&ar,4,&M,1)) break;
                p->Arts.Set(val,ar);
              }while(0);
            }
          }else if(Cmd=='B'){ // 3.58 alternative for A
            int ar;
            int st=M.n[0]; if((st<1)||(st>5)){ MError("\"!!LE:B\"-wrong subcommand (1...5)."); goto l_exit; }
            switch(st){
              case 1: // A1/?var - number of arts
                if(Num<2){ MError("\"!!LE:B1\"-wrong syntax."); goto l_exit; }
                val=p->Arts.GetNum();
                Apply(&val,4,&M,1);
                break;
              case 2: // A2/#/$ - get/set art and subart at position #
                if(Num<3){ MError("\"!!LE:B2\"-wrong syntax."); goto l_exit; }
                if(Apply(&val,4,&M,1)) break;
                ar=p->Arts.Get(val);
                if(Apply(&ar,4,&M,2)) break;
                p->Arts.Set(val,ar);
                break;
              case 3: // A3/$ - add artifact
                if(Num<2){ MError("\"!!LE:B3\"-wrong syntax."); goto l_exit; }
                if(Apply(&val,4,&M,1)) break;
                p->Arts.Add(val);
                break;
              case 4: // A4/$ - del art
                if(Num<2){ MError("\"!!LE:B4\"-wrong syntax."); goto l_exit; }
                if(Apply(&val,4,&M,1)) break;
                p->Arts.Del(val);
                break;
              default:
                MError("\"!!LE:B\"-wrong syntax."); goto l_exit; 
            }
          }else if(Cmd=='S'){ // S#1/$2 �������� � ���� ���� ���1 ����2
            if(Num==1){ // 3.58
              val=(long)p->SpellE-(long)p->Spell;
              val/=4;
              Apply(&val,4,&M,0);
            }else if(Num<2){ goto l_exit;
            }else{
              if((M.n[0]<0)||(&p->Spell[M.n[0]]>p->SpellE)) goto l_exit;
              Apply(&p->Spell[M.n[0]],4,&M,1);
            }
          }else if(Cmd=='C'){ // C#1/$2/$3 ��������
            if(Num<3) goto l_exit;
            if((M.n[0]<0)||(M.n[0]>6)) goto l_exit;
            Apply(&p->Mon.Ct[M.n[0]],4,&M,1);
            Apply(&p->Mon.Cn[M.n[0]],4,&M,2);
          }else if(Cmd=='D'){ // D#1/#2
            if(Num<2){ MError("\"LE:D\"-wrong syntax (D$/$)."); goto l_exit; }
            if((M.n[0]<0)||(M.n[0]>7)){ MError("\"LE:D\"-wrong owner (0...7)."); goto l_exit; }
            if(M.n[1]){ // ���������
              pos->Enabled4&=(Word)~((Word)(1<<M.n[0]));
            }else{ // ���������
              pos->Enabled4|=(Word)(1<<M.n[0]);
            }
          }else if(Cmd=='I'){ // I#
            pos->AIEnable=(Word)M.n[0];
          }else if(Cmd=='L'){ // L#
            pos->OneVisit=(Word)M.n[0];
          }else if(Cmd==' '){
          }else{
            Mess(&M);
          }
        }
        break;
      case 0x4543: // CE
        {
          struct _CastleEvent_ *p=(struct _CastleEvent_ *)sp->Pointer;
          if(Cmd=='M'){
          // M^text^ , M1/$
            if(Num==2){ // � ����������
              if(M.n[0]==1){
                if(M.n[1]==-1){ // M1/-1
                  MesMan(&p->Mes,0,0);
                }else{ // M1/$
                  ApplyString(&M,1,&p->Mes);
                }
              }else{ MError("\"CE:M\"-wrong syntax (M1/$)."); goto l_exit; }
            }else{// ������ �����
               if(MesManOld(&M,&p->Mes.m)){ MError("\"CE:M\"-cannot set message (M$)."); goto l_exit; }
            }
          }else if(Cmd=='F'){ // F$ ���� ������� ��������� (� 1-��)
            Apply(&p->FirstDate,2,&M,0);
          }else if(Cmd=='R'){ // R$ ������������� ���������
            Apply(&p->Repeater,2,&M,0);
          }else if(Cmd=='B'){ // B#1/$2 �������
            if(Num<2) goto l_exit;
            if((M.n[0]<0)||(M.n[0]>6)) goto l_exit;
            Apply(&p->Res[M.n[0]],4,&M,1);
          }else if(Cmd=='E'){ // E$ ��������� ������� ������
            if(M.f[0]) p->Colors|=(Byte)(M.n[0]&0x0FF);
            else p->Colors=(Byte)(M.n[0]&0x0FF);
          }else if(Cmd=='N'){ // N$ ��������� ������� ������
            M.n[0]=~M.n[0];
            if(M.f[0]) p->Colors&=(Byte)(M.n[0]&0x0FF);
            else p->Colors=(Byte)(M.n[0]&0x0FF);
          }else if(Cmd=='H'){ // H# ��������� ��������
            Apply(&p->HEnable,1,&M,0);
          }else if(Cmd=='Q'){ // H# ��������� ��������
            Apply(&p->AIEnable,1,&M,0);
          }else if(Cmd=='C'){ // C#1/$2 ��������
            if(Num<2) goto l_exit;
            if((M.n[0]<0)||(M.n[0]>6)) goto l_exit;
            Apply(&p->Cr[M.n[0]],2,&M,1);
          }else if(Cmd=='U'){ // U# ������� ������ #-����� ����-������
            if((M.n[0]<0)||(M.n[0]>47)) goto l_exit;
            ns2=M.n[0]/8; p->BuildIt[ns2]|=(Byte)(1<<(M.n[0]%8));
          }else if(Cmd=='D'){ // D# �� ������� ������ #-����� ����-������
            if((M.n[0]<0)||(M.n[0]>47)) goto l_exit;
            ns2=M.n[0]/8; p->BuildIt[ns2]&=(Byte)~(1<<(M.n[0]%8));
          }else if(Cmd==' '){
          }else{
            Mess(&M);
          }
        }
        break;
      case 0x4F4D: // MO
        {
          int mn,v;
          struct _Monster_  *p=0;
          Dword MixPos=GetDinMixPos(sp);
          MIp=GetMapItem2(MixPos);
          mp=(_CMonster_ *)MIp;
          if((p==0)&&(mp->HasSetUp)){ // ����������� - ������
            mn=mp->SetUpInd;
            if(mn>GetMonsterNum()){ MError("\"MO\"-cannot find monster by num (internal)."); goto l_exit; }
            p=GetMonsterBase(); if(p==0){ MError("\"MO\"-cannot find monster base(internal)."); goto l_exit; }
            p=&p[mn];
          }
          if(Cmd=='G'){ // G$ ����������
            v=mp->Number; if(Apply(&v,4,&M,0)) break; mp->Number=(Word)v;
          }else if(Cmd=='O'){ // O# �� ������
            v=mp->NoMore; if(Apply(&v,4,&M,0)) break; mp->NoMore=(Word)v;
          }else if(Cmd=='U'){ // U# �� �������
            v=mp->NoRun; if(Apply(&v,4,&M,0)) break; mp->NoRun=(Word)v;
          }else if(Cmd=='R'){ // R# ��������
            if(Num>1){ // ����� ����� 3.57m
              v=mp->Agression; if(v==0x1C) v=0;
              if(Apply(&v,4,&M,0)) break;
              mp->Agression=(Word)v;
              if(v==0) mp->Agression=0x1C;
            }else{
              if(mp->Agression==0x0A) v=1; else v=0;
              if(Apply(&v,4,&M,0)) break;
              if(v) mp->Agression=0x0A; else mp->Agression=0x1C;
            }
          }else{
            if(Cmd=='M'){
              if(p==0){ MError("\"MO:M\"-monster has no setup."); goto l_exit; }
              if(NewMesMan(&M,&p->Mes,0)) goto l_exit;
              p->Set=1; // ��������� �����
            }else if(Cmd=='B'){ // R#1/$2 �������
              if(p==0){ MError("\"MO:M\"-monster has no setup."); goto l_exit; }
              if(Num<2){ MError("\"MO:B\"-wrong syntax (R$/$)."); goto l_exit; }
              if((M.n[0]<0)||(M.n[0]>6)){ MError("\"MO:B\"-incorrect resource (0...7)."); goto l_exit; }
              Apply(&p->Res[M.n[0]],4,&M,1);
              p->Set=1; // ��������� �����
            }else if(Cmd=='A'){ // ��������
              if(p==0){ MError("\"MO:A\"-monster has no setup."); goto l_exit; }
              Apply(&p->Artefact,4,&M,0);
              p->Set=1; // ��������� �����
//            }else if(Cmd=='W'){ // ��������
//              MakeWoMoPos(MIp,M.n[0]);
            }else if(Cmd==' '){
            }else{
              Mess(&M);
            }
          }
        }
        break;
      case 0x5241: // AR
        {
          _ArtRes_  *p=0/*(_ArtRes_ *)sp->Pointer*/;
           Dword MixPos=GetDinMixPos(sp);
          _MapItem_ *mp;
          _CRes_    *vp;
//          _ArtSetUp_ *artsetup;
          int v/*,vi*/;
          mp=GetMapItem2(MixPos);
          if((mp->OType!=79)&&(mp->OType!=5)&&(mp->OType!=93)){ MError("\"AR\"-not an artefact or resource."); goto l_exit; } // ��� �������
          vp=(_CRes_ *)mp;
          if(vp->HasSetUp){
            v=vp->SetUpNum;
            if(v>=GetArtResNum()){ MError("\"AR\"-cannot find artefact or resource (internal)."); goto l_exit; }
            p=GetArtResBase();
            if(p!=0) p=&p[v];
          }
          if(Cmd=='V'){//V$ ���������� �������
            v=vp->Value; if(Apply(&v,4,&M,0)) break; vp->Value=(Word)v;
            break;
          }
          if(p!=0){
            if(Cmd=='M'){
              if(MixPos==0){ if(MesManOld(&M,&p->Mes.m)) goto l_exit; }
              else{ // M^text^ , M1/$
                if(Num==2){ // � ����������
                  if(M.n[0]==1){
                    if(M.n[1]==-1){ // M1/-1
                      MesMan(&p->Mes,0,0);
                    }else{ // M1/$
                      ApplyString(&M,1,&p->Mes);
                    }
                  }else{ MError("\"AR:M\"-wrong syntax (M1/$)."); goto l_exit; }
                }else{
                  if(NewMesMan(&M,&p->Mes,0)){ MError("\"AR:M\"-cannot set message (M$)."); goto l_exit; }
                }
              }
            }else if(Cmd=='G'){ // G#1/$2/$3 �������� � ��� #1 ��� #2(-1 ���) ���-�� #3
              if(Num<3) goto l_exit;
              if((M.n[0]<0)||(M.n[0]>6)) goto l_exit;
              Apply(&p->Gt[M.n[0]],4,&M,1);
              Apply(&p->Gn[M.n[0]],4,&M,2);
            }else if(Cmd=='X'){
              if(M.n[0]!=0) p->fl_G=1; else p->fl_G=0;
            }else if(Cmd==' '){
            }else{ MError("\"AR\"-wrong command."); Mess(&M); }
            break;
          }
          MError("\"AR\"-cannot find artefact or resource (syntax error).");
          goto l_exit;
        }
      case 0x4548: // HE$ HE$/$/$
        { //ABCDEF HI KLMNOP RSTUVWXY
          int n;
          struct _Hero_  *p;
          switch(sp->ParSet){
            case 1: // �����
              n=GetVarVal(&sp->Par[0]);
              if(n==-1) p=ERM_HeroStr;
              else if(n==-10) p=G2B_HrA;
              else if(n==-20) p=G2B_HrD;
              else p=GetHeroStr(n);
              if(p==0){ MError("\"HE$\"-cannot find hero (out of range)."); goto l_exit; }
              break;
            case 3: // �������
              MixedPos(&x,&y,&l,GetDinMixPos(sp));
              p=FindHeroNum(x,y,l);
              if(p==0){ MError("\"HE$/$/$\"-cannot find hero at position."); goto l_exit; }
              break;
            default: // ???
              MError("\"HE???\"-incorrect syntax.");
              goto l_exit;
          }
          if(Cmd=='O'){ // O$(/#) ������� �������
            _PlayerSetup_ *ps;
            char *pho=GetHOTableBase();
            if(M.VarI[0].Check==0){ // �������������
              if((M.n[0]<-1)||(M.n[0]>7)){ MError("\"HE:O\"-owner out of range (-1...7)."); goto l_exit; }
              if(Num>1){ // 3.58 change an owner without check
                Apply(&p->Owner,1,&M,0); break;
              }
              if(M.n[0]!=-1){
                ps=GetPlayerSetup(M.n[0]); if(ps==0){ MError("\"!!HE:O\"-cannot get PlayerSetup structure."); goto l_exit; }
                if(ps->HasHeroes>=8){ break;} // ������ ������ ��������
              }
              if(p->Owner!=-1){
                ps=GetPlayerSetup(p->Owner); if(ps==0){ MError("\"!!HE:O\"-cannot get PlayerSetup structure."); goto l_exit; }
                for(i=0;i<8;i++){ if(ps->Heroes[i]==p->Number) goto Ok_11; }
                MError("\"!!HE:O\"-cannot find hero (internal)."); goto l_exit;
Ok_11:
                ++i; for(;i<8;i++){ ps->Heroes[i-1]=ps->Heroes[i]; }
                ps->Heroes[7]=-1;
                ps->HasHeroes-=(char)1;
                if(ps->CurHero==p->Number){
                  if(ps->HasHeroes>0) ps->CurHero=ps->Heroes[0]; else ps->CurHero=-1;
                }
              }
              if(M.n[0]!=-1){
                ps=GetPlayerSetup(M.n[0]); if(ps==0){ MError("\"!!HE:O\"-cannot get PlayerSetup structure."); goto l_exit; }
                ps->Heroes[ps->HasHeroes]=p->Number;
                ps->HasHeroes+=(char)1;
              }
              pho[p->Number]=(char)M.n[0];
              Apply(&p->Owner,1,&M,0);
            }else{
              Apply(&p->Owner,1,&M,0);
            }
          }else if(Cmd=='P'){ // P$1/P$2/$3[/flag] ����������� � �������
            if(Num<3) goto l_exit;
            cfl=0;
            if(M.VarI[0].Check){ cfl=1; Apply(&p->x,2,&M,0); }
            if(M.VarI[1].Check){ cfl=1; Apply(&p->y,2,&M,1); }
            if(M.VarI[2].Check){ cfl=1; Apply(&p->l,2,&M,2); }
            if(cfl==0){
              if(Num==4) cfl=M.n[3]; else cfl=0;
              JumpHero(p,p->x*M.f[0]+M.n[0],(p->y*M.f[1]+M.n[1]),(p->l*M.f[2]+M.n[2]),cfl);
            }
          }else if(Cmd=='I'){ // I$ ���� ����������
            Apply(&p->SpPoints,2,&M,0);
            if(Num<2) RedrawMap();
          }else if(Cmd=='X'){ // �������������
            if(Num<7){
              if(MakeHeroSpec(p->Number,&M,Num)) goto l_exit;
            }else{
              _HeroSpec_ *dsp=&HSpecTable[p->Number];
              int p0,p1,p2,p3,p4,p5,p6;
              p0=dsp->Spec; p1=dsp->Spec1; p2=dsp->Spec2; p3=dsp->Spec3; p4=dsp->Spec4; p5=dsp->Spec5; p6=dsp->Spec6;
              Apply(&p0,4,&M,0);
              Apply(&p1,4,&M,1);
              Apply(&p2,4,&M,2);
              Apply(&p3,4,&M,3);
              Apply(&p4,4,&M,4);
              Apply(&p5,4,&M,5);
              Apply(&p6,4,&M,6);
              dsp->Spec=p0; dsp->Spec1=p1; dsp->Spec2=p2; dsp->Spec3=p3; dsp->Spec4=p4; dsp->Spec5=p5; dsp->Spec6=p6;
            }
// ������� � 3.57m ������������ ������������� � ���� ������
//            if(PostInstr==0){ // �� ����������� ���������� � ������.
//              if(AddCommand(sp,Start,M.i)) goto l_exit;
//            }
          }else if(Cmd=='U'){ // U$1/$2/$3 ������� ����� � �������� ������� ����
            if(Num<3) goto l_exit;
            Apply(&p->x0,1,&M,0);
            Apply(&p->y0,1,&M,1);
            Apply(&p->Run,1,&M,2);
          }else if(Cmd=='C'){ // C ����������� �������
            if(Num<4) goto l_exit;
            if(Num==14){
              CrChangeDialog(p,M.n[0],M.n[1],M.n[2],M.n[3],M.n[4],M.n[5],M.n[6],M.n[7],
                               M.n[8],M.n[9],M.n[10],M.n[11],M.n[12],M.n[13]);
            }else{
              int check=0,Exp=0,Mod=0,OldNum;
              if(Num>5) Apply(&Mod,4,&M,5);
              if(M.n[0]==0){ // C0/#2/$3/$4{/$5{/$6}} ����������� ������� �� �������
                {
                  if((M.n[1]<0)||(M.n[1]>7)) goto l_exit;
                  if(M.f[2]==0){
                    // 3.59 fix -1 only if a constant
                    if((M.n[2]==-1)&&(M.VarI[2].Type==0)){ // �������
                      p->Ct[M.n[1]]=p->Ct[M.n[1]]&0xFFFFFFFE +1;
                    // 3.59 fix -2 only if a constant
                    }else if((M.n[2]==-2)&&(M.VarI[2].Type==0)){ // �������
                      p->Ct[M.n[1]]=p->Ct[M.n[1]]&0xFFFFFFFE;
                    }else{
                      if(Apply(&p->Ct[M.n[1]],4,&M,2)) check=1;
                    }
                  }
                  OldNum=p->Cn[M.n[1]];
                  if(Apply(&p->Cn[M.n[1]],4,&M,3)) check=1;
                  if(p->Cn[M.n[1]]<=0){ p->Ct[M.n[1]]=-1; p->Cn[M.n[1]]=0; }
                  // 3.58 cr experience
                  if(Num>4){
//                    Exp=CrExpoSet::GetExp(CE_HERO,MAKEHS(p->Number,M.n[1]));
                    // 3.59 - return exp or exp level (M>=10)
                    Exp=CrExpoSet::GetExpM(CE_HERO,MAKEHS(p->Number,M.n[1]),Mod);
                    if(Apply(&Exp,4,&M,4)) check=1;
                  }
                  if(check==0){
                    CrExpoSet::Modify(5,CE_HERO,MAKEHS(p->Number,M.n[1]),Exp,Mod,p->Ct[M.n[1]],OldNum,p->Cn[M.n[1]]);
                  }
                }
              }else if(M.n[0]==1){ // C1/#2/$3/$4{/$5} ����������� ������� �� ����
                {
                  for(i=0;i<7;i++){
                    if(p->Ct[i]==M.n[1]){
                      if(Apply(&p->Ct[i],4,&M,2)) check=1;
                      OldNum=p->Cn[i];
                      if(Apply(&p->Cn[i],4,&M,3)) check=1;
                      if(p->Cn[i]==0) p->Ct[i]=-1;
                      // 3.58 cr experience
                      if(Num>4){
                        Exp=CrExpoSet::GetExp(CE_HERO,MAKEHS(p->Number,i));
                        if(Apply(&Exp,4,&M,4)) check=1;
                      }
                      if(check==0){
                        CrExpoSet::Modify(5,CE_HERO,MAKEHS(p->Number,i),Exp,Mod,p->Ct[i],OldNum,p->Cn[i]);
                      }
                    }
                  }
                }
              }else if(M.n[0]==2){ // C2/���/�����/H_ai{/$5} �������� �������
                AddMon2Hero(p,M.n[1],M.n[2],M.n[3]);
                // 3.58 cr experience
                if(Num>4){
                  if(Apply(&Exp,4,&M,4)) check=1;
                }
                if(check==0){
                  CrExpoSet::Modify(6,CE_HERO,MAKEHS(p->Number,0),Exp,Mod,M.n[1],0,M.n[2],(_MonArr_ *)&p->Ct[0]);
                }
              }
            }
          }else if(Cmd=='S'){ // S#1/$2 ��������� �����
            if(Num==3){ // �����/����/1
              int sind=0,skill=0;
              if(Apply(&sind,4,&M,0)){ // ?/#
                if(Apply(&skill,4,&M,1)){ // ?/? - wrong
                  MError("\"HE:S?/?/1\"- is a wrong syntax."); goto l_exit;
                }
                if((skill<0)||(skill>27)){ MError("\"HE:S?/#/1\"- skill number is out of range (0...27)."); goto l_exit; }
                sind=p->SShow[skill];
                Apply(&sind,4,&M,0);
              }else{ // #/? or #/#
                if((sind<0)||(sind>8)){ MError("\"HE:S#/#/1\"- skill show index is out of range (0...8)."); goto l_exit; }
                skill=-1;
                if(Apply(&skill,4,&M,1)){ // #/?
                  for(i=0;i<28;i++){
                    if(p->SShow[i]==sind){
                      skill=i;
                      Apply(&skill,4,&M,1);
                      break;
                    }
                  }
                }else{ // #/#
                  if((skill<0)||(skill>27)){ MError("\"HE:S#/#/1\"- skill number is out of range (0...27)."); goto l_exit; }
                  for(i=0;i<28;i++){
                    if(p->SShow[i]==sind) p->SShow[i]=0;
                  }
                  p->SShow[skill]=(Byte)sind;
                }
              }
            }else if(Num==1){
              Apply(&p->SSNum,4,&M,0);
            }else if(Num==2){
              if((M.n[0]<0)||(M.n[0]>27)) goto l_exit;
              if(Apply(&p->SSkill[M.n[0]],1,&M,1)) goto _ok101;
              if(p->SSkill[M.n[0]]==0){ // �������
                if(p->SShow[M.n[0]]!=0){ // ��� ����
                  if(p->SShow[M.n[0]]!=p->SSNum){
                    for(i=0;i<28;i++) if(p->SShow[i]==p->SSNum){
                      p->SShow[i]=p->SShow[M.n[0]];
                      goto _ok1;
                    }
                    goto l_exit;
_ok1:;
                  }
                  p->SShow[M.n[0]]=0;
                  --p->SSNum;
                }else{ // ��� ���
                }
              }else{
                if(p->SShow[M.n[0]]!=0){ // ��� ����
                }else{
                  if(p->SSNum<8){ // ����� ��� ��������
                    ++p->SSNum;
                    p->SShow[M.n[0]]=(Byte)p->SSNum;
                  }else{ // ��� �����
                  }
                }
              }
            }else goto l_exit;
_ok101:;
          }else if(Cmd=='A'){ // A#1
            if(Num>1){ // ���� �������
              int aflag,anum,art=0,arts=-1;
              if(M.VarI[1].Check==0){
                // check only if used SET syntax
                art=M.n[1]; arts=-1;
                if(art<0){ MError("\"HE:A\"-wrong artifact number."); goto l_exit; }
                if(art==1000) art=0;
                if(art>1000){ arts=art-1001; art=1; }
              }
              switch(M.n[0]){
                case 1: // A1/art/pos - ��������� ���
//                  if((M.n[2]<0)||(M.n[2]>18)){ MError("\"HE:A1\"-wrong slot number."); goto l_exit; }
                  if((M.n[2]<0)||(M.n[2]>82)){ MError("\"HE:A1\"-wrong slot number."); goto l_exit; }
                  if(M.VarI[1].Check!=0){ // �������� �� �������
                    if(M.n[2]>18){ // 3.58 backpack
                      art=p->OArt[M.n[2]-19][0];
                      if(art==0) art=1000;
                      if(art==1) art=p->OArt[M.n[2]-19][1]+1001;
                      Apply(&art,4,&M,1);
                      break;
                    }else{
                      art=p->IArt[M.n[2]][0];
                      if(art==0) art=1000;
                      if(art==1) art=p->IArt[M.n[2]][1]+1001;
                      Apply(&art,4,&M,1);
                      break;
                    }
                  }
                  // ����������
                  if(M.n[2]>18){ // 3.58 backpack
                    if(p->OArt[M.n[2]-19][0]==-1){ // ��������
                      p->OArt[M.n[2]-19][0]=art;
                      p->OArt[M.n[2]-19][1]=arts;
                      ERMFlags[0]=1;
                    }else ERMFlags[0]=0; // ���������, ��� �� �������
                  }else{
                    if(p->IArt[M.n[2]][0]==-1){ // ��������
                      p->IArt[M.n[2]][0]=art;
                      p->IArt[M.n[2]][1]=arts;
                      if(((art>0)&&(art<=0x2C))||(art==0x80)){
                        if(art==0x80) k=0; else k=art;
                        for(j=0;j<4;j++){
                          p->PSkill[j]+=(char)ArtSkill[k][j];
                        }
                      }
                      ERMFlags[0]=1;
                    }else ERMFlags[0]=0; // ���������, ��� �� �������
                  }
                  break;
                case 2: // A2/art/num/act - ��������� ���
                  aflag=anum=0;
                  for(i=0;i<19;i++){
                    if((p->IArt[i][0]==art)&&(p->IArt[i][1]==arts)){
                      ++aflag; ++anum;
                    }
                  }
                  for(i=0;i<64;i++){
                    if((p->OArt[i][0]==art)&&(p->OArt[i][1]==arts)){ ++anum; }
                  }
                  Apply(&anum,4,&M,2);
                  Apply(&aflag,4,&M,3);
                  break;
                case 3: // A3/art/num/act - ������ ���
                  anum=0;  Apply(&anum,4,&M,2);
                  aflag=0; Apply(&aflag,4,&M,3);
                  if(aflag==0){ // ������� � ������ ������� �� �������
                    for(i=0;i<64;i++){
                      if((p->OArt[i][0]==art)&&(p->OArt[i][1]==arts)){
                        if(anum==0) break;
                        p->OArt[i][0]=p->OArt[i][1]=-1;
                        --anum;
                      }
                    }
                  }
                  for(i=0;i<19;i++){
                    if((p->IArt[i][0]==art)&&(p->IArt[i][1]==arts)){
                      if(anum==0) break;
                      p->IArt[i][0]=p->IArt[i][1]=-1;
                      --anum;
                      if(M.n[0]>0x80){ // ���������
                        for(j=0;;j++){ // ������� �������
                          if(ArtSlots[j]==M.n[0]){
                            for(k=0,j=j+1;k<4;k++){
                              p->PSkill[k]-=(char)ArtSlots[j+k];
                            }
                            for(j=j+4;;j++){
                              k=ArtSlots[j];
                              if(k>0x80) break; // ����� �� �����
                              p->LockedSlot[k]=(Byte)(p->LockedSlot[k]-1);
                            }
                          }
                          if(ArtSlots[j]==0x99) break; // ���
                        }
                      }
                    }
                  }
                  if(aflag){ // ������� �� ������ ������� ������
                    for(i=0;i<64;i++){
                      if((p->OArt[i][0]==art)&&(p->OArt[i][1]==arts)){
                        if(anum==0) break;
                        p->OArt[i][0]=p->OArt[i][1]=-1;
                        --anum;
                      }
                    }
                  }
                  break;
                case 4: // A4/art - ��������� ��� (����� �������)
                  EquipArtifact(p,art,arts);
                  break;
                default: MError("\"HE:A\"-wrong syntax."); goto l_exit;
              }
            }else{
              int art,arts;
              if(M.n[0]>=0){
                art=M.n[0]; arts=-1;
                if(art==1000) art=0;
                if(art>1000){ arts=art-1001; art=1; }
                if(M.VarI[0].Check!=0){ // �������� �� �������
                  if(M.VarI[0].Check!=2){ MError("\"HE:A\"-wrong syntax (second argument)."); goto l_exit; } // ����� ������ ����������
                  ERMFlags[0]=0;
                  for(i=0;i<19;i++){
                    if((p->IArt[i][0]==art)&&(p->IArt[i][1]==arts)){
                      ERMFlags[0]=1;
                      goto _ok103;
                    }
                  }
                  for(i=0;i<64;i++){
                    if((p->OArt[i][0]==art)&&(p->OArt[i][1]==arts)){
                      ERMFlags[0]=1;
                      goto _ok103;
                    }
                  }
                }else{// �������� � ������
                  for(i=0;i<64;i++){
                    if(p->OArt[i][0]==-1){
                      p->OArt[i][0]=art;
                      p->OArt[i][1]=arts;
                      p->OANum=(Byte)(p->OANum+1);
                      break;
                    }
                  }
                }
              }else{ // ������
                art=-M.n[0]; arts=-1;
                if(art==1000) art=0;
                // ��� ��������� ������� ���������� - ������� ��� ������ � ����
                if(art==1){ arts=-2; }
                if(art>1000){ arts=art-1001; art=1; }
                for(i=0;i<19;i++){
                  if((p->IArt[i][0]==art)&&((p->IArt[i][1]==arts)||(arts==-2))){
                    p->IArt[i][0]=p->IArt[i][1]=-1;
                    if(art>0x80){ // ���������
                      for(j=0;;j++){ // ������� �������
                        if(ArtSlots[j]==art){
                          for(k=0,j=j+1;k<4;k++){
                            p->PSkill[k]-=(char)ArtSlots[j+k];
                          }
                          for(j=j+4;;j++){
                            k=ArtSlots[j];
                            if(k>0x80) break; // ����� �� �����
                            p->LockedSlot[k]=(Byte)(p->LockedSlot[k]-1);
                          }
                        }
                        if(ArtSlots[j]==0x99) break; // ���
                      }
                    }
                    // ����� ������ ��������� ���. ��� ������� ����������
                    if(((art>0)&&(art<=0x2C))||(art==0x80)){
                      if(art==0x80) k=0; else k=art;
                      for(j=0;j<4;j++){
                        p->PSkill[j]-=ArtSkill[k][j];
                      }
                    }
                  }
                }
                for(i=0;i<64;i++){
                  if((p->OArt[i][0]==art)&&((p->OArt[i][1]==arts)||(arts==-2))){
                    p->OArt[i][0]=p->OArt[i][1]=-1;
                    p->OANum=(Byte)(p->OANum-1);
                  }
                }
              }
            }
_ok103:;
          }else if(Cmd=='M'){ // M#1/$2 ����������
            char  fl;
            if(Num<2){ MError("\"HE:M\"-wrong syntax."); goto l_exit; }
            if(M.VarI[0].Check!=0){ // �������� �� �������
              if(M.VarI[0].Check!=2){ MError("\"HE:M\"-wrong syntax (second argument)."); goto l_exit; } // ����� ������ ����������
              if(p->Spell[M.n[0]]==0) fl=0; else fl=1;
              ERMFlags[0]=fl;
            }else{
              if((M.n[0]<0)||(M.n[0]>69)) goto l_exit;
//              p->LSpell[M.n[0]]=(Byte)(p->LSpell[M.n[0]]*M.f[1]+M.n[1]);
              if(Apply(&p->LSpell[M.n[0]],1,&M,1)) break;
              if(p->LSpell[M.n[0]]==0){ // �������
                p->Spell[M.n[0]]=0;
              }else{
                p->Spell[M.n[0]]=1;
              }
            }
          }else if(Cmd=='F'){ // F$1/$2/$3/$4 ��������� ������
            if(Num<4){ MError("\"HE:F\"-wrong syntax."); goto l_exit; }
            if(Num==4){
              int redrfl=0;
              if(Apply(&p->PSkill[0],1,&M,0)) redrfl=1;
              if(Apply(&p->PSkill[1],1,&M,1)) redrfl=1;
              if(Apply(&p->PSkill[2],1,&M,2)) redrfl=1;
              if(Apply(&p->PSkill[3],1,&M,3)) redrfl=1;
              if(redrfl) RedrawMap();
            }else if(Num==5){ // F$1/$2/$3/$4/1 ������ ��������� ������
              int art,ps[4];
              ps[0]=p->PSkill[0]; ps[1]=p->PSkill[1]; ps[2]=p->PSkill[2]; ps[3]=p->PSkill[3];
              switch(M.n[4]){
                case 1:
                  for(i=0;i<19;i++){
                    art=p->IArt[i][0];
                    if(art==-1) continue;
                    if(art>0x80){ // ���������
                      for(j=0;;j++){ // ������� �������
                        if(ArtSlots[j]==art){
                          for(k=0,j=j+1;k<4;k++){
                            ps[k]-=(char)ArtSlots[j+k];
                          }
                          for(j=j+4;;j++){
                            k=ArtSlots[j];
                            if(k>0x80) break; // ����� �� �����
                          }
                        }
                        if(ArtSlots[j]==0x99) break; // ���
                      }
                    }
                    // ����� ������ ��������� ���. ��� ������� ����������
                    if(((art>0)&&(art<=0x2C))||(art==0x80)){
                      if(art==0x80) k=0; else k=art;
                      for(j=0;j<4;j++){
                        ps[j]-=ArtSkill[k][j];
                      }
                    }
                  }
                  Apply(&ps[0],4,&M,0);
                  Apply(&ps[1],4,&M,1);
                  Apply(&ps[2],4,&M,2);
                  Apply(&ps[3],4,&M,3);
                  break;
                default:
                  MError("\"HE:F\"-wrong syntax."); goto l_exit;
              }
            }else{ MError("\"HE:F\"-wrong syntax."); goto l_exit; }
          }else if(Cmd=='N'){ // N# ����� ������ ���������
            int v=p->Number;
            Apply(&v,4,&M,0); // ����� ������ ���������
          }else if(Cmd=='L'){ // L#^Name.pcx^
            if((M.n[0]<0)||(M.n[0]>5)){ MError("\"HE:L\"-wrong syntax."); goto l_exit; }
            if(M.n[0]==3){ // �������� ����
              ChangeHeroPic(p->Number,0,0);
              RedrawMap();
            }else if(M.n[0]==4){
              ChangeHeroPicN(p->Number,M.n[1]);
              RedrawMap();
            }else if(M.n[0]==0){ // ���������� ��� � ������� ��������
              if(Num<2){ MError("\"HE:L0\"-wrong syntax."); goto l_exit; }
              CustomHPic(M.n[1],p->Number,0);
              RedrawMap();
            }else if(M.n[0]==5){ // ���������� ��� � ��������� ���������� (0-�� ���.)
              if(Num<3){ MError("\"HE:L5\"-wrong syntax."); goto l_exit; }
              if(M.n[1]<-10){ MError("\"HE:L5\"-wrong z var index (-10...-1,(0),1...1000)."); goto l_exit; }
              if(M.n[2]<-10){ MError("\"HE:L5\"-wrong z var index (-10...-1,(0),1...1000)."); goto l_exit; }
              char *s1=0,*s2=0;
              if(M.n[1]!=0){
                if(M.n[1]>1000)   s1=StringSet::GetText(M.n[1]);
                else if(M.n[1]>0) s1=ERMString[M.n[1]-1];
                else              s1=ERMLString[-M.n[1]-1];
              }
              if(M.n[2]!=0){
                if(M.n[2]>1000)   s2=StringSet::GetText(M.n[2]);
                else if(M.n[2]>0) s2=ERMString[M.n[2]-1];
                else              s2=ERMLString[-M.n[2]-1];
              }
              ChangeHeroPic(p->Number,s1,s2);
              RedrawMap();
            }else{
              for(int fl=j=0,i=M.i;i<M.m.l;i++){
                if(M.m.s[i]==STRCH){
                  if(fl==1){
                    M.m.s[i]=0;
                    if(M.n[0]==1) // S
                      ChangeHeroPic(p->Number,0,&M.m.s[j]);
                    else // L
                      ChangeHeroPic(p->Number,&M.m.s[j],0);
                    RedrawMap();
                    M.m.s[i]=STRCH;
                    ERMFlags[M.n[0]-1]=(char)fl;
                    M.i=i+1;
                    break;
                  }else{
                    j=i+1;
                    fl=1;
                  }
                }
              }
            }
          }else if(Cmd=='W'){ // W$1 ������ �����������
            Apply(&p->Movement,4,&M,0);
            if(Num<2) RedrawMap();
          }else if(Cmd=='G'){ // 3.58 G$1 ������ ����������� ���������
            Apply(&p->Movement0,4,&M,0);
//            if(Num<2) RedrawMap();
          }else if(Cmd=='K'){ // K ����� �����
            KillHero(p->Number);
            if(Num<2) RedrawMap();
          }else if(Cmd=='E'){ // E$(/$?level) �������� �����
            int retflag=0;
            if(Num>1){ Apply(&p->ExpLevel,2,&M,1); retflag=1; }
            if(Apply(&p->Exp,4,&M,0)) retflag=1;
            if(retflag) break; // if check first or second
            AddExp(p);
            if(Num<3) RedrawMap();
          }else if(Cmd=='V'){
           {
            Dword mask;
            int v;
            if((M.n[0]<0)||(M.n[0]>=10)){ MError("\"HE:V\"-wrong object type index (0...10)."); goto l_exit; }
            if(Num==2){       // V#/# ������������ ��������
              Apply(&p->Visited[M.n[0]],4,&M,1);
            }else if(Num==3){ // V#/#/# ������������ ��������
              if((M.n[1]<0)||(M.n[1]>=32)){ MError("\"HE:V\"-wrong object index (0...32)."); goto l_exit; }
              mask=1;
              for(i=0;i<M.n[1];i++) mask<<=1;
              if(p->Visited[M.n[0]]&mask) v=1; else v=0;
              if(Apply(&v,4,&M,2)) break;
              if(v) p->Visited[M.n[0]]|=mask; // ���������
              else  p->Visited[M.n[0]]&=~mask;
            }
           }
          }else if(Cmd=='B'){ // ��� ��� ���� ��� �����
            if(Num<2){ MError("\"HE:B\"-wrong syntax."); goto l_exit; }
            switch(M.n[0]){
              case 0: // B0/$ - ���
                if(M.VarI[1].Check==1){ // ?
                  int sind=GetVarVal(&M.VarI[1]);
                  if((sind<-10)||(sind==0)||(sind>1000)){ MError("\"HE:B0\"-wrong z var index (-10...-1,1...1000)."); goto l_exit; }
                  if(sind>0){ StrCopy(ERMString[sind-1],13,p->Name); ERMString[sind-1][13]=0; }
                  else      { StrCopy(ERMLString[-sind-1],13,p->Name); ERMLString[-sind-1][13]=0; }
                }else{
                  if((M.n[1]<-10)||(M.n[1]==0)){ MError("\"HE:B1\"-wrong z var index (-10...-1,1...1000)."); goto l_exit; }
                  if(M.n[1]>1000)   StrCopy(p->Name,13,StringSet::GetText(M.n[1]));
                  else if(M.n[1]>0) StrCopy(p->Name,13,ERMString[M.n[1]-1]);
                  else              StrCopy(p->Name,13,ERMLString[-M.n[1]-1]);
                }
                break;
              case 1: // B1/$ - ����
                ApplyString(&M,1,&p->Bibl);
                if(M.VarI[1].Check==0) p->fl_B=1;
                break;
              case 2: // B2/$ - �����
                Apply(&p->Spec,4,&M,1);
                break;
              case 3: // B3/$ - �������� ������������� ����
                if(M.VarI[1].Check==1){ // ?
                  int sind=GetVarVal(&M.VarI[1]);
                  if((sind<-10)||(sind==0)||(sind>1000)){ MError("\"HE:B3\"-wrong z var index (-10...-1,1...1000)."); goto l_exit; }
                  if(sind>0){ StrCopy(ERMString[sind-1],511,HBiosTable[p->Number].HBios); ERMString[sind-1][511]=0; }
                  else      { StrCopy(ERMLString[-sind-1],511,HBiosTable[p->Number].HBios); ERMLString[-sind-1][511]=0; }
                }else{
                  MError("\"HE:B3\"-cannot use set syntax."); goto l_exit;
                }
                break;
              default:
                MError("\"HE:B\"-wrong syntax."); goto l_exit;
            }
          }else if(Cmd=='R'){ //
            int v,en,posred; char *pho=GetHOTableBase(); int *phh=GetHHTableBase();
            if(Num<2){ MError("\"HE:R\"-wrong syntax."); goto l_exit; }
            posred=1;
            switch(M.n[0]){
              case 0: // R0/$ - ������
                if(Apply(&p->DMorale1,1,&M,1)) posred=0;
                break;
              case 1: // R1/$ - �����
                if(Apply(&p->DLuck,1,&M,1)) posred=0;
                break;
              case 2: // R2/$ - ���
                if(Apply(&p->Sex,1,&M,1)) posred=0;
                break;
              case 3:
                if(Num<3){ // R3/$ - ��������(1)/��������(0)
                  en=0xFF;
                }else{ // R3/$1/$2 - ��������(1)/��������(0) ��� ������� (1���=1����)
                  en=phh[p->Number]; // ����
                  if(Apply(&en,4,&M,2)){ posred=0; break; }
                }
                if(M.VarI[1].Check==0){ // �������������
                  if(M.n[1]!=0){ // ���������
                    if(pho[p->Number]==0x40) pho[p->Number]=-1;
                    phh[p->Number]=en;
                  }else{ // ���������
                    if(pho[p->Number]==0x40){ break; }
                    if(pho[p->Number]==-1){ pho[p->Number]=0x40; break; }
                    // 3.57m2 ���� ����� �� �����, �� ��� ������ �����
                    // KillHero(p->Number);
                    // RedrawMap();
                    pho[p->Number]=0x40;
                  }
                }else{ // ���������
                  v=1; if(pho[p->Number]==0x40) v=0;
                  Apply(&v,4,&M,1);
                }
                break;
              case 4: // R4/$ - ��������� ������� ��� ���
                if(p->Flags&0x02) v=1; else v=0;
                if(Apply(&v,4,&M,1)) posred=0;
                if(v) p->Flags|=0x02; else p->Flags&=0xFD;
                break;
              case 5: // R5/$ ��� �������� ������ (���������)
                posred=0;
                if(p->TempMod&0x800000) v=1; else v=0;
                if(Apply(&v,4,&M,1)) break;
                if(v) p->TempMod|=0x800000; else p->TempMod&= ~0x800000;
                break;
              case 6: // R6/$ ��� �������� ����� (���������)
                posred=0;
                if(p->TempMod&0x400000) v=1; else v=0;
                if(Apply(&v,4,&M,1)) break;
                if(v) p->TempMod|=0x400000; else p->TempMod&= ~0x400000;
                break;
              case 7: // 3.59 R7/$ ��� ������������ � ����� (���������)
                posred=0;
                v=p->TempMod; if(Apply(&v,4,&M,1)) break; p->TempMod=v;
                break;
              default: MError("\"HE:R\"-wrong syntax."); goto l_exit;
            }
            if(Num>2){ // ���� ��� �����������
              v=1; Apply(&v,4,&M,2);
              if(v==1) RedrawMap();
            }else{
              if(posred) RedrawMap();
            }
          }else if(Cmd=='Y'){ // Ynum/power/length/flag ���������
            // flag = 1-set,0-del,2-add/sub,3=del all
            if(Num<4){ MError("\"HE:Y\"-wrong syntax."); goto l_exit; }
            if((M.VarI[1].Check==1)||
               (M.VarI[2].Check==1)){ // ?
               int pwr,len;
              GetHeroCurse(M.n[0],&pwr,&len,p->Number);
              Apply(&pwr,4,&M,1);
              Apply(&len,4,&M,2);
            }else{
              if(AddCurse(M.n[0],M.n[1],M.n[2],M.n[3],p->Number)){ MError("\"HE:Y\"-cannot add curse."); goto l_exit; }
            }
            RedrawMap();
          }else if(Cmd=='T'){ // ����� Tx/y/l/mtype/mnum
            if(Num<5){ MError("\"HE:T\"-wrong syntax."); goto l_exit; }
              if(DoBattle(&M.n[4],p,M.n[3],PosMixed(M.n[0],M.n[1],M.n[2])))
                ERMFlags[0]=1; else ERMFlags[0]=0;
          }else if(Cmd=='H'){ // Hslot/type/min/max ��������� ��������� ����� �����
            if(Num<4){ MError("\"HE:H\"-wrong syntax."); goto l_exit; }
            if((M.n[0]<0)||(M.n[0]>2)){ MError("\"HE:H\"-slot number out of range (0...2)."); goto l_exit; }
            Apply(&HTable[p->Number].ArmyType[M.n[0]],4,&M,1);
            Apply(&HTable[p->Number].ArmyNum[M.n[0]][0],4,&M,2);
            Apply(&HTable[p->Number].ArmyNum[M.n[0]][1],4,&M,3);
          }else if(Cmd=='D'){ // D creature upgrade
            FortOnHill(p->Number);
            RedrawRes();
/*
          }else if(Cmd=='G'){ // Gx/y/l/sound go to Boat
            if(Num<4){ MError("\"HE:G\"-wrong syntax."); goto l_exit; }
            int x,y,l,sound,pdx,pdy;
            if(Apply(&x,4,&M,0)) break;
            if(Apply(&y,4,&M,1)) break;
            if(Apply(&l,4,&M,2)) break;
            if(Apply(&sound,4,&M,3)) break;
//            p->x=x; p->y; p->l=l;
//            JumpHero(p,x,y,l,sound);
            pdx=x-p->x; pdy=y-p->y;
            __asm{
int 3
              push   pdy
              push   pdx
              push   2
              push   p
              mov    ecx,0x6992B8
              mov    ecx,[ecx]
              mov    eax,0x47FCA0
              call   eax
            }
            _MapItem_ *mapitem=GetMapItem(x,y,l);
            __asm{
              mov   eax,mapitem
              mov   ecx,p
              push  eax
              push  ecx
              mov   ecx,0x6992B8
              mov   ecx,[ecx]
              mov   eax,0x4A0C80
              call  eax
            }
*/
          }else if(Cmd==' '){
          }else{
            Mess(&M);
          }
        }
        break;
      case 0x4649: // IF
        {
          int  fl,pt2,ps2,pt3,ps3,type,sind;
// unfortunately work only in MP mode 4F703E
//          if(Cmd=='T'){
//            Apply(&NextMessShowTime,4,&M,0);
//          }else 
          if(Cmd=='Q'){ // 1000 ������
           int showtime=NextMessShowTime;
           NextMessShowTime=0;
           if((M.n[0]<1)||(M.n[0]>1000)){ MError("\"IF:Q\"-wrong flag number (1...1000)."); goto l_exit; }
           if(Num==1){ // ������� ������
             ERMFlags[M.n[0]-1]=(char)Request0(ERM2String(&M.m.s[M.i],0,&i),showtime);
             M.i+=i;
             break;
           }else if(Num==2){ // ������ � ����������
             if((M.n[1]<-10)||(M.n[1]==0)){ MError("\"IF:Q\"-wrong z var index (-10...-1,1...1000)."); goto l_exit; }
             if(M.n[1]>1000)   ERMFlags[M.n[0]-1]=(char)Request0(ERM2String(StringSet::GetText(M.n[1]),1,0),showtime);
             else if(M.n[1]>0) ERMFlags[M.n[0]-1]=(char)Request0(ERM2String(ERMString[M.n[1]-1],1,0),showtime);
             else              ERMFlags[M.n[0]-1]=(char)Request0(ERM2String(ERMLString[-M.n[1]-1],1,0),showtime);
           }else{
             if(Num<6){ // + ���� �������� Qfl/pict/pics^text^
               type=M.n[3]; pt2=-1; ps2=0; pt3=-1;ps3=0; sind=M.n[4];
             }else if(Num<8){ // + ��� ��������
               // Qfl/pic1t/pic1s/pic2t/pic2s/type^text^
               type=M.n[5]; pt2=M.n[3]; ps2=M.n[4]; pt3=-1;ps3=0; sind=M.n[6];
             }else if(Num<10){ // + 3 ��������
               // Qfl/pic1t/pic1s/pic2t/pic2s/pic3t/pic3s/type^text^
               type=M.n[7]; pt2=M.n[3]; ps2=M.n[4]; pt3=M.n[5];ps3=M.n[6]; sind=M.n[8];
             }else{ MError("\"IF:Q\"-wrong syntax."); goto l_exit; }
             if(Num&1){ // �������� - ����������
               if((sind<-10)||(sind==0)){ MError("\"IF:Q\"-wrong z var index (-10...-1,1...1000)."); goto l_exit; }
               if(sind>1000)   fl=Request3Pic(ERM2String(StringSet::GetText(sind),1,0),M.n[1],M.n[2],pt2,ps2,pt3,ps3,type,showtime);
               else if(sind>0) fl=Request3Pic(ERM2String(ERMString[sind-1],1,0),M.n[1],M.n[2],pt2,ps2,pt3,ps3,type,showtime);
               else            fl=Request3Pic(ERM2String(ERMLString[-sind-1],1,0),M.n[1],M.n[2],pt2,ps2,pt3,ps3,type,showtime);
             }else{ // ������ - ���� ���������
               fl=Request3Pic(ERM2String(&M.m.s[M.i],0,&i),M.n[1],M.n[2],pt2,ps2,pt3,ps3,type,showtime);
               M.i+=i;
             }
             if(type==10){ // 3.58+
               ERMVar2[M.n[0]-1]=fl;
             }else if(type!=1){
               ERMFlags[M.n[0]-1]=(char)fl;
             }
             break;
           }
          }else if(Cmd=='M'){ // M^text^ , M1/$
            int showtime=NextMessShowTime;
            NextMessShowTime=0;
            if(Num==3){ // � ����� ������� ��� ����������
              int var=1; Apply(&var,4,&M,1);              
              //  1-���������
              //  2-������ 
              //  4-���� �� ������ �����
              //  7-������� �������
              // 10-����� � ������� � ����������
              var=Message(GetERMtext(&M,2),var,showtime);
              Apply(&var,4,&M,0);
            }else if(Num==2){ // � ����������
              if(M.n[0]==1){
                if((M.n[1]<-10)||(M.n[1]==0)){ MError("\"IF:M\"-wrong z var index (-10...-1,1...1000)."); goto l_exit; }
                if(M.n[1]>1000) Message(ERM2String(StringSet::GetText(M.n[1]),1,0),1,showtime);
                else if(M.n[1]>0) Message(ERM2String(ERMString[M.n[1]-1],1,0),1,showtime);
                else Message(ERM2String(ERMLString[-M.n[1]-1],1,0),1,showtime);
              }else{ MError("\"IF:M\"-wrong syntax (M1/$)."); goto l_exit; }
            }else{
              Message(ERM2String(&M.m.s[M.i],0,&i),1,showtime);
              M.i+=i;
            }
            break;
          }else{
            switch(Cmd){
              case 'V': // 1000 ������
                if(Num<2) goto l_exit;
                if((M.n[0]<1)||(M.n[0]>1000)) goto l_exit;
                if(M.n[1]) fl=1; else fl=0; // ���������� ���
                ERMFlags[M.n[0]-1]=(char)fl;
                break;
              case 'A': // ������ ��� ������ � 0 �� 10
              case 'S': //
              case 'R': //
                for(i=9;i>=0;i--,M.n[0]/=10){
                  fl=M.n[0]&1; // ���������� ���
                  if((Cmd=='S')&&(fl==0)) continue;
                  if(Cmd=='R'){ if(fl==0) continue; else fl=0; }
                  ERMFlags[i]=(char)fl;
                }
                break;
              case 'W': // ���������� ������ ����� ��� ����������
                if(M.n[0]==-1){ // ������� �����
                  struct _Hero_ *p=ERM_HeroStr;
                  if(p==0){ MError("\"IF:W\"-cannot find hero."); goto l_exit; }
                  M.n[0]=p->Number;
                }
                if((M.n[0]<0)||(M.n[0]>=HERNUM)){ MError("\"IF:W\"-hero number out of range."); goto l_exit; }
                ERMW=M.n[0];
                break;
              case 'P': // ��������/�����
                CustomPic(M.n[0],0);
                break;
              case 'E': // ������
                if(Num==2){
                  char *str;
                  if((M.n[0]<1)||(M.n[0]>10000)){ MError("\"IF:E\"-wrong var index (1...10000)."); goto l_exit; }
                  ERMVar2[M.n[0]-1]=CustomReq(M.n[1],0,&str);
                  StrCopy(ERMString[0],512,str);
                }else{
                  CustomReq(M.n[0],0,0);
                }
                break;
              case 'X': // X$ ����������� ������ �����
                if(M.n[0]==-1) M.n[0]=Random(0,TXTSphinx.sn-1);
                ERMFlags[0]=(char)SphinxReq(M.n[0]);
                break;
              case 'B': // B#/pic/rep ���������� ��������
                if(Num<3){ MError("\"IF:B\"-wrong syntax."); goto l_exit; }
                if((M.n[1]<-10)||(M.n[1]==0)){ MError("\"IF:B\"-wrong z var index (-10...-1,1...1000)."); goto l_exit; }
                if(M.n[1]>1000)   AddExtCMDPic(M.n[0],ERM2String2(0,StringSet::GetText(M.n[1])),M.n[2]);
                else if(M.n[1]>0) AddExtCMDPic(M.n[0],ERMString[M.n[1]-1],M.n[2]);
                else              AddExtCMDPic(M.n[0],ERMLString[-M.n[1]-1],M.n[2]);
                break;
              case 'F': // F#/... ���������� ������ +...
               {
                 int   tv;
                 char  HasCancel;
                 char *bth1,*bth2,*bth3,*bth4;
                 if(Num!=6){ MError("\"IF:F\"-wrong syntax."); goto l_exit; }
                 tv=0;
                 if(Apply(&tv,4,&M,5)){ MError("\"IF:F\"-cannot get or check var."); goto l_exit; }
                 if(tv!=0) HasCancel=1; else HasCancel=0;
                 if(Apply(&tv,4,&M,4)){ MError("\"IF:F\"-cannot get or check var."); goto l_exit; }
                 if(tv<-10){ MError("\"IF:F\"-wrong z var index (-10,...-1,(0),1...1000)."); goto l_exit; }
                 if(tv!=0){
                   if(tv>1000)   bth4=StringSet::GetText(tv);
                   else if(tv>0) bth4=ERMString[tv-1];
                   else          bth4=ERMLString[-tv-1];
                   bth4=ERM2String2(1,bth4);
                 }else bth4=0;
                 if(Apply(&tv,4,&M,3)){ MError("\"IF:F\"-cannot get or check var."); goto l_exit; }
                 if(tv<-10){ MError("\"IF:F\"-wrong z var index (-10,...-1,(0),1...1000)."); goto l_exit; }
                 if(tv!=0){
                   if(tv>1000)   bth3=StringSet::GetText(tv);
                   else if(tv>0) bth3=ERMString[tv-1];
                   else          bth3=ERMLString[-tv-1];
                   bth3=ERM2String2(2,bth3);
                 }else bth3=0;
                 if(Apply(&tv,4,&M,2)){ MError("\"IF:F\"-cannot get or check var."); goto l_exit; }
                 if(tv<-10){ MError("\"IF:F\"-wrong z var index (-10,...-1,(0),1...1000)."); goto l_exit; }
                 if(tv!=0){
                   if(tv>1000)   bth2=StringSet::GetText(tv);
                   else if(tv>0) bth2=ERMString[tv-1];
                   else          bth2=ERMLString[-tv-1];
                   bth2=ERM2String2(3,bth2);
                 }else bth2=0;
                 if(Apply(&tv,4,&M,1)){ MError("\"IF:F\"-cannot get or check var."); goto l_exit; }
                 if(tv<-10){ MError("\"IF:F\"-wrong z var index (-10,...-1,(0),1...1000)."); goto l_exit; }
                 if(tv!=0){
                   if(tv>1000)   bth1=StringSet::GetText(tv);
                   else if(tv>0) bth1=ERMString[tv-1];
                   else          bth1=ERMLString[-tv-1];
                   bth1=ERM2String2(4,bth1);
                 }else bth1=0;
                 if(Apply(&tv,4,&M,0)){ MError("\"IF:F\"-cannot get or check var."); goto l_exit; }
                 if(AddExtCMDRequest(tv,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                   bth1,bth2,bth3,bth4,HasCancel)==0){ MError("\"IF:F\"-cannot show dialog."); goto l_exit; }
                }
                break;
              case 'G': // GchRAD/var/state/header/txt1... ������ � ���������
               {
                 int   v,state,j,chRAD;
                 char *htxt,*txt[12];
                 if(Num<5){ MError("\"IF:G\"-wrong syntax."); goto l_exit; }
//                 if(Num>(12+3)){ MError("\"IF:G\"-wrong syntax."); goto l_exit; }
                 if(Apply(&chRAD,4,&M,0)){ MError("\"IF:G\"-cannot get or check var."); goto l_exit; }
                 if(Apply(&state,4,&M,2)){ MError("\"IF:G\"-cannot get or check var."); goto l_exit; }
                 if(Apply(&v,4,&M,3)){ MError("\"IF:G\"-cannot get or check var."); goto l_exit; }
                 if(v<-10){ MError("\"IF:G\"-wrong z var index (-10...-1,(0),1...1000)."); goto l_exit; }
                 if(v!=0){
                   if(v>1000)   htxt=StringSet::GetText(v);
                   else if(v>0) htxt=ERMString[v-1];
                   else         htxt=ERMLString[-v-1];
                   htxt=ERM2String2(5,htxt);
                 }else htxt=0;
                 for(j=0;j<(Num-4);j++){
                   if(Apply(&v,4,&M,(char)(j+4))){ MError("\"IF:G\"-cannot get or check var."); goto l_exit; }
                    // 3.57f check
                    if(j>11){ MError("\"IF:G\"-too many items."); goto l_exit; }
                   if(v==0) txt[j]=0;
                   else{
                     if((v<-10)||(v==0)){ MError("\"IF:G\"-wrong z var index (-10...-1,1...1000)."); goto l_exit; }
                     if(v>1000)   txt[j]=StringSet::GetText(v);
                     else if(v>0) txt[j]=ERMString[v-1];
                     else         txt[j]=ERMLString[-v-1];
                     txt[j]=ERM2String2(6+j,txt[j]);
                   }
                 }
                 for(;j<12;j++) txt[j]=0;
                 ERMVar2[M.n[1]-1]=MultiCheckReq(htxt,state,txt,chRAD);
                 break;
               }
              case 'D': // D#/... ���������� ������...
               {
                 int   tv;
                 char  HasCancel;
                 char *txt1,*txt2,*txt3,
                      *pic1,*pic2,*pic3,*pic4,
                      *pch1,*pch2,*pch3,*pch4,
                      *but1,*but2,*but3,*but4,
                      *bth1,*bth2,*bth3,*bth4;
                 if(Num<1){ MError("\"IF:D\"-wrong syntax."); goto l_exit; }
                 tv=0;
                 if(Num>15){
                   if(Apply(&tv,4,&M,15)){ MError("\"IF:D\"-cannot get or check var."); goto l_exit; }
                   if(tv<-10){ MError("\"IF:D\"-wrong z var index1(-10...-1,(0),1...1000)."); goto l_exit; }
                   if(tv!=0){
                     if(tv>1000)   but4=StringSet::GetText(tv);
                     else if(tv>0) but4=ERMString[tv-1];
                     else          but4=ERMLString[-tv-1];
                     but4=ERM2String2(18,but4);
                   }else but4=0;
                 }else but4=0;
                 if(Num>14){
                   if(Apply(&tv,4,&M,14)){ MError("\"IF:D\"-cannot get or check var."); goto l_exit; }
                   if(tv<-10){ MError("\"IF:D\"-wrong z var index2(-10...-1,(0),1...1000)."); goto l_exit; }
                   if(tv!=0){
                     if(tv>1000)   but3=StringSet::GetText(tv);
                     else if(tv>0) but3=ERMString[tv-1];
                     else          but3=ERMLString[-tv-1];
                     but3=ERM2String2(19,but3);
                   }else but3=0;
                 }else but3=0;
                 if(Num>13){
                   if(Apply(&tv,4,&M,13)){ MError("\"IF:D\"-cannot get or check var."); goto l_exit; }
                   if(tv<-10){ MError("\"IF:D\"-wrong z var index3(-10...-1,(0),1...1000)."); goto l_exit; }
                   if(tv!=0){
                     if(tv>1000)   but2=StringSet::GetText(tv);
                     else if(tv>0) but2=ERMString[tv-1];
                     else          but2=ERMLString[-tv-1];
                     but2=ERM2String2(20,but2);
                   }else but2=0;
                 }else but2=0;
                 if(Num>12){
                   if(Apply(&tv,4,&M,12)){ MError("\"IF:D\"-cannot get or check var."); goto l_exit; }
                   if(tv<-10){ MError("\"IF:D\"-wrong z var index4(-10...-1,(0),1...1000)."); goto l_exit; }
                   if(tv!=0){
                     if(tv>1000)   but1=StringSet::GetText(tv);
                     else if(tv>0) but1=ERMString[tv-1];
                     else          but1=ERMLString[-tv-1];
                     but1=ERM2String2(21,but1);
                   }else but1=0;
                 }else but1=0;
                 if(Num>11){
                   if(Apply(&tv,4,&M,11)){ MError("\"IF:D\"-cannot get or check var."); goto l_exit; }
                   if(tv<-10){ MError("\"IF:D\"-wrong z var index5(-10...-1,(0),1...1000)."); goto l_exit; }
                   if(tv!=0){
                     if(tv>1000)   pch4=StringSet::GetText(tv);
                     else if(tv>0) pch4=ERMString[tv-1];
                     else          pch4=ERMLString[-tv-1];
                     pch4=ERM2String2(22,pch4);
                   }else pch4=0;
                 }else pch4=0;
                 if(Num>10){
                   if(Apply(&tv,4,&M,10)){ MError("\"IF:D\"-cannot get or check var."); goto l_exit; }
                   if(tv<-10){ MError("\"IF:D\"-wrong z var index6(-10...-1,(0),1...1000)."); goto l_exit; }
                   if(tv!=0){
                     if(tv>1000)   pch3=StringSet::GetText(tv);
                     else if(tv>0) pch3=ERMString[tv-1];
                     else          pch3=ERMLString[-tv-1];
                     pch3=ERM2String2(23,pch3);
                   }else pch3=0;
                 }else pch3=0;
                 if(Num>9){
                   if(Apply(&tv,4,&M,9)){ MError("\"IF:D\"-cannot get or check var."); goto l_exit; }
                   if(tv<-10){ MError("\"IF:D\"-wrong z var index7(-10...-1,(0),1...1000)."); goto l_exit; }
                   if(tv!=0){
                     if(tv>1000)   pch2=StringSet::GetText(tv);
                     else if(tv>0) pch2=ERMString[tv-1];
                     else          pch2=ERMLString[-tv-1];
                     pch2=ERM2String2(24,pch2);
                   }else pch2=0;
                 }else pch2=0;
                 if(Num>8){
                   if(Apply(&tv,4,&M,8)){ MError("\"IF:D\"-cannot get or check var."); goto l_exit; }
                   if(tv<-10){ MError("\"IF:D\"-wrong z var index8(-10...-1,(0),1...1000)."); goto l_exit; }
                   if(tv!=0){
                     if(tv>1000)   pch1=StringSet::GetText(tv);
                     else if(tv>0) pch1=ERMString[tv-1];
                     else          pch1=ERMLString[-tv-1];
                     pch1=ERM2String2(25,pch1);
                   }else pch1=0;
                 }else pch1=0;
                 if(Num>7){
                   if(Apply(&tv,4,&M,7)){ MError("\"IF:D\"-cannot get or check var."); goto l_exit; }
                   if(tv<-10){ MError("\"IF:D\"-wrong z var index9(-10...-1,(0),1...1000)."); goto l_exit; }
                   if(tv!=0){
                     if(tv>1000)   pic4=StringSet::GetText(tv);
                     else if(tv>0) pic4=ERMString[tv-1];
                     else          pic4=ERMLString[-tv-1];
                     pic4=ERM2String2(26,pic4);
                   }else pic4=0;
                 }else pic4=0;
                 if(Num>6){
                   if(Apply(&tv,4,&M,6)){ MError("\"IF:D\"-cannot get or check var."); goto l_exit; }
                   if(tv<-10){ MError("\"IF:D\"-wrong z var indexA(-10...-1,(0),1...1000)."); goto l_exit; }
                   if(tv!=0){
                     if(tv>1000)   pic3=StringSet::GetText(tv);
                     else if(tv>0) pic3=ERMString[tv-1];
                     else          pic3=ERMLString[-tv-1];
                     pic3=ERM2String2(27,pic3);
                   }else pic3=0;
                 }else pic3=0;
                 if(Num>5){
                   if(Apply(&tv,4,&M,5)){ MError("\"IF:D\"-cannot get or check var."); goto l_exit; }
                   if(tv<-10){ MError("\"IF:D\"-wrong z var indexB(-10...-1,(0),1...1000)."); goto l_exit; }
                   if(tv!=0){
                     if(tv>1000)   pic2=StringSet::GetText(tv);
                     else if(tv>0) pic2=ERMString[tv-1];
                     else          pic2=ERMLString[-tv-1];
                     pic2=ERM2String2(28,pic2);
                   }else pic2=0;
                 }else pic2=0;
                 if(Num>4){
                   if(Apply(&tv,4,&M,4)){ MError("\"IF:D\"-cannot get or check var."); goto l_exit; }
                   if(tv<-10){ MError("\"IF:D\"-wrong z var indexC(-10...-1,(0),1...1000)."); goto l_exit; }
                   if(tv!=0){
                     if(tv>1000)   pic1=StringSet::GetText(tv);
                     else if(tv>0) pic1=ERMString[tv-1];
                     else          pic1=ERMLString[-tv-1];
                     pic1=ERM2String2(29,pic1);
                   }else pic1=0;
                 }else pic1=0;
                 if(Num>3){
                   if(Apply(&tv,4,&M,3)){ MError("\"IF:D\"-cannot get or check var."); goto l_exit; }
                   if(tv<-10){ MError("\"IF:D\"-wrong z var indexD(-10...-1,(0),1...1000)."); goto l_exit; }
                   if(tv!=0){
                     if(tv>1000)   txt3=StringSet::GetText(tv);
                     else if(tv>0) txt3=ERMString[tv-1];
                     else          txt3=ERMLString[-tv-1];
                     txt3=ERM2String2(30,txt3);
                   }else txt3=0;
                 }else txt3=0;
                 if(Num>2){
                   if(Apply(&tv,4,&M,2)){ MError("\"IF:D\"-cannot get or check var."); goto l_exit; }
                   if(tv<-10){ MError("\"IF:D\"-wrong z var indexE(-10...-1,(0),1...1000)."); goto l_exit; }
                   if(tv!=0){
                     if(tv>1000)   txt2=StringSet::GetText(tv);
                     else if(tv>0) txt2=ERMString[tv-1];
                     else          txt2=ERMLString[-tv-1];
                     txt2=ERM2String2(31,txt2);
                   }else txt2=0;
                 }else txt2=0;
                 if(Num>1){
                   if(Apply(&tv,4,&M,1)){ MError("\"IF:D\"-cannot get or check var."); goto l_exit; }
                   if(tv<-10){ MError("\"IF:D\"-wrong z var indexF(-10...-1,(0),1...1000)."); goto l_exit; }
                   if(tv!=0){
                     if(tv>1000)   txt1=StringSet::GetText(tv);
                     else if(tv>0) txt1=ERMString[tv-1];
                     else          txt1=ERMLString[-tv-1];
                     txt1=ERM2String2(32,txt1);
                   }else txt1=0;
                 }else txt1=0;
                 if(Apply(&tv,4,&M,0)){ MError("\"IF:D\"-cannot get or check var."); goto l_exit; }
                 bth1=but1;bth2=but2;bth3=but3;bth4=but4;HasCancel=1;
                 if(AddExtCMDRequest(tv,txt1,txt2,txt3,pic1,pic2,pic3,pic4,
                   pch1,pch2,pch3,pch4,but1,but2,but3,but4,
                   bth1,bth2,bth3,bth4,HasCancel)==0){ MError("\"IF:D\"-cannot show dialog."); goto l_exit; }
                }
                break;
              case 'N':{ // 3.58
                char *txt;
                if(Num<4){ // show
                  // N^text^ N1/$
                  if(Num==2){ // � ����������
                    if(M.n[0]==1){
                      if(M.n[0]>1000)   txt=StringSet::GetText(M.n[0]);
                      else if(M.n[0]>0) txt=ERMString[M.n[0]-1];
                      else              txt=ERMLString[-M.n[0]-1];
                      txt=ERM2String2(32,txt);
                    }else{ MError("\"IF:N\"-wrong syntax (M1/$)."); goto l_exit; }
                  }else{
                    txt=ERM2String(&M.m.s[M.i],0,&i);
                    M.i+=i;
                  }
                  Display8Dialog(txt,IF_N_Ar);
                }else{ // prepare
                 // Np1t/p1s/p2t/p2s/p3t/p3s/p4t/p4s/p5t/p5s/p6t/p6s/p7t/p7s/p8t/p8s
                  for(i=0;i<9;i++){ IF_N_Ar[i][0]=-1; IF_N_Ar[i][1]=0; }
                  for(i=0;i<Num/2;i++){
                    if(Apply(&IF_N_Ar[i][0],4,&M,(char)(i*2))){ MError("\"IF:N\"-cannot get or check var."); goto l_exit; }
                    if(Apply(&IF_N_Ar[i][1],4,&M,(char)(i*2+1))){ MError("\"IF:N\"-cannot get or check var."); goto l_exit; }
                  }
                }
              }
              break;
              case 'L':{ // L#   3.59 - put message to log
                char *lcstr="";
                if(M.n[0]<-10){ MError("\"IF:L\"-wrong z var index (-10...-1,1...1000)."); goto l_exit; }
                if(M.n[0]>1000)   lcstr=ERM2String(StringSet::GetText(M.n[0]),1,0);
                else if(M.n[0]>0) lcstr=ERM2String(ERMString[M.n[0]-1],1,0);
                else if(M.n[0]<0) lcstr=ERM2String(ERMLString[-M.n[0]-1],1,0);
                else{ lcstr=ERM2String(&M.m.s[M.i],0,&i); M.i+=i; }
                _asm{
                  mov  eax,lcstr
                  push eax
                  mov  eax,0x69D800
                  push eax
                  mov  eax,0x553C40
                  call eax
                  add  esp,8
                }
              }
              break;
              default:
                Mess(&M);
            }
          }
        }
        break;
      default:
        if(Cmd==' ') break;
        if(Cmd==0x0A) break;
        for(j=0;;j++){
          if(ERM_Addition[j].Id==0) break;
          if(ERM_Addition[j].Id!=Id) continue;
          if(ERM_Addition[j].Fun(Cmd,Num,sp,&M)) goto _processed;
        }
        if(PL_ERMErrDis==0){
          Mess(&M); goto l_exit;
        }  
_processed:
        break;
    }
  }while((M.m.s[M.i]!=';')||(M.i>=M.m.l));
  RETURNV
l_exit:
  M.i=Ind;
  if(PL_ERMErrDis==0){
    Mess(&M);
  }
  RETURNV
}
// ��������������� ��������� ��� ���� �� ���������
void ResetWoG356(void)
{
  #include "templ.h"
  for(int i=0;i<PL_WONUM;i++){
    PL_WoGOptions[0][i]=0;
  }
  PL_NoNPC=1; ResetNPC();
  RETURNV
}
// ������������� ��������� ��� ���������������� ����
void ResetWoG357(void)
{
  #include "templ.h"
  for(int i=0;i<PL_WONUM;i++){
    PL_WoGOptions[0][i]=PL_WoGOptions[1][i];
  }
  PL_CrExpStyle=0; 
  ResetNPC();
  RETURNV
}
// 3.58 ��� 3.57
// ������������� ��������� ��� ���������������� ���� �� ��������� � 3.57 �����
void ResetWoG358_357(void)
{
  #include "templ.h"
  for(int i=200;i<PL_WONUM;i++){ // ������� ��� ����� �����
    PL_WoGOptions[0][i]=0;
  }
  PL_CrExpStyle=0; 
//  PL_NoNPC=0; ResetNPC();
  RETURNV
}
// 3.58
void ResetCustomSettings(char *FName)
{
  #include "templ.h"
  // ������ ������ ������ ��������
  int k=LoadSetupState(FName,PL_WoGOptions,sizeof(PL_WoGOptions)/2);
  if(k<0){
    Message(ITxt(200,0,&Strings),1);
    RETURNV
  }
  if(CountERMScripts()==0) LoadERMTXT(1);
  PL_CustomOptionWasSet=CountERMScripts();
  ResetNPC();
  RETURNV
}

//static Dword Esi_;
static Word ScriptIndex4ERM=0;
static int   nL;

void FindERM(void)
{
  long   ts,ind,HSize,k;
  int    i,j,Ind,Post,Num;
  long   self;
  Dword  ToDoPo/*,ToDoPo2*/;
  Word   Id;
  Byte  *p,InstrFlag,PostFlag;
  int    FirstFlag,FirstMesFlag;
  Mes    M;
  _ToDo_ ltd;
//  int   Hn;
  int   ParSet;
  VarNum Par[16];
  _Main_        *MS;
  _PostERM_     *PERM;
  _GlbEvent_    *GEp0,*GEp1,*GEp,*GEp_;
  _CastleEvent_ *CEp0,*CEp1,*CEp;
  _Cmd_         *cp0,*cp;
  _ToDo_        *dp;
//  _ArtRes_      *Ap0,*Ap1,*Ap;
  _THero_       *THp0;
  _Hero_        *Hp0;
  #include "templ.h"
// 3.58
//  Main=(_Main_ *)Esi_;
  __asm{
    mov  eax,BASE
    mov  eax,[eax]
    add  eax,0x1FB70
    mov  Main,eax
  }
  ERMEnabled=0;
// 3.56 ������ ERM ������ �� WoG ������
  if(WoG==0) RETURNV
  // ������� ��� ������
  p=(Byte *)Heap; HSize=HeapSize;
  for(j=0;j<HSize;j++) p[j]=0;
  cp0=Heap; cp=0; cp0->Event=0;
  PERM=PostERM;
  __asm{
    mov  eax,BASE
    mov  ecx,[eax]
    add  ecx,0xA4
    mov  THp0,ecx
    mov  ecx,[eax]
    add  ecx,0x21620
    mov  Hp0,ecx
  }
//  Hn=0x9C;  // ���������� ������ ������
// 3.58
//  MS=(_Main_ *)Esi_;
  MS=Main;

  CEp0=MS->CEp0;
  CEp1=MS->CEp1;
//  Ap0=MS->Ap0;
//  Ap1=MS->Ap1;

  int NumOfScripts=CountERMScripts();
  int CurScript=0;
  int IntentionallyWoGifiedbyMapMaker=0;
  // Show clock
//  SetMouseCursor(1,1);
  if(nL==0){
    int gelcl=AddGlbEvent();
    if(gelcl<0){ Message("Cannot add global event (internal). ERM disabled",1); goto l_exit; }
    GEp0=MS->GEp0;
    GEp1=MS->GEp1;
    MesMan(&GEp0[gelcl].Mes,"ZVSE ",0);
    GEp0[gelcl].FirstDate=999;
    GEp0[gelcl].Repeater=0;
    GEp0[gelcl].HEnable=0;
    GEp0[gelcl].AIEnable=1;
  }else{
    GEp0=MS->GEp0;
    GEp1=MS->GEp1;
  }
  FirstFlag=0; FirstMesFlag=0;
  Post=0;
  if(nL==0) ResetWoG357(); // ��������� (�������� �������������)
  PL_NPCOptionWasSet=0; // ���� ����� ����������, �� �� ���������� ����� � 3.56
  // ���� ����� ��������� ���������������� �����, �� ����������� � ����� ��������
  PL_CustomOptionWasSet=0; // 3.58
  PL_DisableWogifyWasSet=0;
  PL_ExpoWasSet=0; // 3.58
  for(GEp_=GEp0;GEp_<=GEp1;GEp_++){
    // 3.59 reset script index
    ScriptIndex4ERM=0;
    if(GEp_==GEp1){ // ����� ��������� ��� ���
      // �������� �� ��������� ����� ����������� (5) � �������� 
      if((nL==0)&&(PL_ApplyWoG>0)&&(NumOfScripts==0)&&(FirstMesFlag==0)){
        // ���� ����� � ���� ���-�� �������������� � ������� �� ���� ���������� � ������ ���
        if(CountERMScripts()==0) LoadERMTXT(1);
        NumOfScripts=CountERMScripts();
        IntentionallyWoGifiedbyMapMaker=1;
        ResetNPC();
      }
      if((nL==0)&&(PL_CustomOptionWasSet!=0)&&(FirstMesFlag==0)){ // 3.58 custom options loaded
        NumOfScripts=PL_CustomOptionWasSet;
      }
      if((nL==0)&&(NumOfScripts==0)&&(FirstMesFlag==0)){
        // ���� ����� ����, �� WoG � ������ ��� ������
        if(FirstFlag>1){ // ���� ���� ������� ERM ������� � ����� �����
//            if((PL_DisableWogifyWasSet!=0)&&(PL_ApplyWoG==0)){
//              ResetWoG358(); // ���� ���� �������, � ��������� � ������, �� 358
//            }
          if(PL_ExpoWasSet!=0){ // ����� ��� 3.58 ������ ���� - ������ �� ����� � ����������
          }else{  // ����� ��� 3.57 - ���� �������� ����� ������ 3.57
            if(PL_NPCOptionWasSet==0){ // NPC �� ���� �������� ��� �� ���� ���������
              ResetWoG356(); // ���� ���� �������, �� ������, �� 356 ��������� � 0
            }else{ // ������� ���� � �����
              ResetWoG358_357(); // ����� 3.57 �����
            }
          }
        }else{ // � ����� ��� ��������
          // ��������, ��� �� ��������������
          if((PL_ApplyWoG==0)) Message(ITxt(199,0,&Strings),1);
        }
      }
      if(YesERMFile && ERMFile2Process){ // ����� ���� � ERM
        M.m.s=ITxt(0,0,&ErmTxt);
        M.m.l=StrLen(ITxt(0,0,&ErmTxt));
        M.i=0;
        GEp_--; // ������� �����
        ERMFile2Process=0; // ������� ��������� ����
      }else if(NumOfScripts!=0){
        // ����� ������� ����������� (WoG ���� ��� ��������� � ����)
        if(FirstMesFlag==0){ // ������ ������ ���
          if(YesERMFile){ // ���� ���� *.ERM
            if(nL){ // ��������
              if(LoadVersion4Scripts>9){ // 3.57m+ �������� ������� � ��� �� ������������
              }else{ // 3.57  ���� ��� ������� �������� - ���������
                ResetWoG356();
                break;
              }
            }else{ // �����
              if((PL_ApplyWoG==0 && WoGSpecMap==0)||(Request0(ITxt(198,0,&Strings))==0)){
                // ���� �� ������� �� �������������� ��� ������ �� ���� ��������������
                if(PL_ExpoWasSet!=0){ // ����� ��� 3.58 ������ ���� - ������ �� ����� � ����������
                }else{  // ����� ��� 3.57 - ���� �������� ����� ������ 3.57
                  if(PL_NPCOptionWasSet==0){ // NPC �� ���� �������� ��� �� ���� ���������
                    ResetWoG356(); // ���� ���� �������, �� ������, �� 356 ��������� � 0
                  }else{ // ������� ���� � �����
                    ResetWoG358_357(); // ����� 3.57 �����
                  }
                }
                ClearScriptFile();
                break;
              }
            }
          }else if(FirstFlag>1){ // ���� ���������� �������
            if(nL){ // ��������
              if(LoadVersion4Scripts>9){ // 3.57m+ �������� ������� � ��� �� ������������
              }else{ // 3.57  ���� ��� ������� �������� - ���������
                ResetWoG356();
                break;
              }
            }else{ // �����
              if(PL_CustomOptionWasSet!=0){ // 3.58 custom options loaded
              }else if((PL_ApplyWoG==0 && WoGSpecMap==0)||((IntentionallyWoGifiedbyMapMaker==0) && (Request0(ITxt(197,0,&Strings)))==0)){
                // ���� �� ������� �� �������������� ��� ������ �� ���� ��������������
                if(PL_ExpoWasSet!=0){ // ����� ��� 3.58 ������ ���� - ������ �� ����� � ����������
                }else{  // ����� ��� 3.57 - ���� �������� ����� ������ 3.57
                  if(PL_NPCOptionWasSet==0){ // NPC �� ���� �������� ��� �� ���� ���������
                    ResetWoG356(); // ���� ���� �������, �� ������, �� 356 ��������� � 0
                  }else{ // ������� ���� � �����
                    ResetWoG358_357(); // ����� 3.57 �����
                  }
                }
                ClearScriptFile();
                break;
              }
            }
          }else{ // ��� �������� ������ - ������� �� ���� ���, �.�. ������������
            // 3.58 option 4 WoGify but ask
            if((nL==0) && (PL_ApplyWoG==3) && (Request0(ITxt(226,0,&Strings))==0)){
              ClearScriptFile();
              __asm{
                mov   eax,BASE
                mov   eax,[eax]
                add   eax,0x1F86C
                mov   dword ptr [eax],SOGMAPTYPE
              }
              break;
            }
            __asm{
              mov   eax,BASE
              mov   eax,[eax]
              add   eax,0x1F86C
              mov   dword ptr [eax],SOGMAPTYPE
            }
          }
          FirstMesFlag=1;
        }
        int sn=GetERMScripts(CurScript++); NumOfScripts--;
        M.m.s=ERMBody[sn];
        M.m.l=StrLen(ERMBody[sn]);
        M.i=0;
        GEp_--; // ������� �����
        // 3.59 for local functions and vars 
        ScriptIndex4ERM=CurScript;
      }else{
        Post=1;
        if(nL &&(PERM->p!=0)){ // ���������� ��������������
          M.m.s=&PERM->s[PERM->p]; M.m.l=PERM->l-PERM->p; M.i=0;
        }else break; // ��� ����������
      }
    }else{
      M.m.s=GEp_->Mes.m.s; M.m.l=GEp_->Mes.m.l; M.i=0;
    }
    if(CheckMine(&M)){ // ��������� ���������
      if(FirstFlag==0){ // ���� ������ ���
        if(GEp0==0){ // ���� ������ ��� ���������� ���������
          // ������ �� ����� ����
          Message("No global events. Cannot continue",1); goto l_exit;
        }else{
          if((WoG==0)&&(nL==0)){
            Message(ITxt(25,0,&Strings),1);
          }
          ERMEnabled=1;
          for(k=0;k<M.m.l;k++) PERM->s[k]=M.m.s[k];
          PERM->s[k]=0;
          PERM->l=M.m.l; PERM->p=0;
          PERM->owner=&GEp_->Mes.m;
          GEp_->Mes.m.s=M.m.s=PERM->s;
        }
      }
      ++FirstFlag;
      if(Post && nL){
        // ���� ������ ������� ������ ���� ���
        // ������������, ��� ������ ���� ���������� - !#IF:A..........
      }
      do{ // ����� ��������� ��������
        M.c[0]='!';
        // 3.58 correction to skip ^ in comments
        if(SkipUntil2(&M)) break; // ��� ���������� - � ���� �������
        if(M.i>(M.m.l+5)) break; //��� ����� ��� �������
//    GEr.LastERM(sp->Self.s); // 3.58
        if((M.m.s[M.i]=='?')||(M.m.s[M.i]=='$')){ // �������-���������
          if(M.m.s[M.i]=='$') PostFlag=1; else PostFlag=0;
          ++M.i;
          Id=*(Word *)&M.m.s[M.i]; M.i+=2;
          if(cp!=0){
            ts=(Dword)sizeof(_Cmd_)+sizeof(_ToDo_)*(cp->Num-1);
            cp->Next=(_Cmd_ *)((Dword)cp+ts);
          }
          switch(Id){
            case 0x454C: // LE##/##/#;
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=3) goto l_exit;
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=0x20000000|PosMixed(M.n[0],M.n[1],M.n[2]);
              if(PostFlag) cp->Event|=0x08000000;
//              cp->Par[0]=M.VarI[0];
//              cp->Par[1]=M.VarI[1];
//              cp->Par[2]=M.VarI[2];
//              cp->ParSet=3;
              break;
            case 0x4547: // GE#;
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1) goto l_exit;
              if(M.n[0]<0) goto l_exit;
              for(GEp=GEp0;GEp<GEp1;GEp++){
                if(MakeSpec(&GEp->Mes.m,M.n[0])) goto _found5;
              }
              goto l_exit;
_found5:
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=(Dword)GEp; // ���. ��������� �������-����������
//              cp->ParSet=0;
              break;
            case 0x424F: // OB#x/#y/#l; OB#t; OB#t/#st;
              M.c[0]=';';
              Ind=M.i;
              if(cp!=0) cp=cp->Next; else cp=cp0;
              switch(GetNumAutoFl(&M)){
                case 1: // OB#t;
                  cp->Event=0x40000000|(M.n[0]<<12);
                  if(PostFlag) cp->Event|=0x08000000;
//                  cp->Par[0]=M.VarI[0]; cp->ParSet=1;
                  break;
                case 2: // OB#t/#st;
                  cp->Event=0x40000000|((M.n[0]<<12)+(M.n[1]+1));
                  if(PostFlag) cp->Event|=0x08000000;
//                  cp->Par[0]=M.VarI[0]; cp->Par[1]=M.VarI[1]; cp->ParSet=2;
                  break;
                case 3: // OB#x/#y/#l;
                  cp->Event=0x10000000|PosMixed(M.n[0],M.n[1],M.n[2]);
                  if(PostFlag) cp->Event|=0x08000000;
//                  cp->Par[0]=M.VarI[0]; cp->Par[1]=M.VarI[1]; cp->Par[2]=M.VarI[2]; cp->ParSet=3;
                  break;
                default: MError("\"!?OB:\"-wrong syntax (OB#t,OB#t/#st,OB#x/#y/#l)."); goto l_exit;
              }
              break;
            case 0x5546:{ // FU#;
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?FU:\"-wrong syntax."); goto l_exit; }
              if((M.n[0]<-100)||(M.n[0]==0)||(M.n[0]>30000)){ MError("\"!?FU:\"-wrong function index (-100...30000)."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              int funind=M.n[0];
              if(funind<0) funind=-funind+31000-1; // local functions
              cp->Event=funind;
//              cp->Par[0]=M.VarI[0]; cp->ParSet=1;
              if(ERMVarUsedStore==1) LogERMFunctionTrigger(M.n[0],&M.m.s[Ind]);
              break;}
            case 0x4142: // BA#;
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?BA:\"-wrong syntax."); goto l_exit; }
              if(M.n[0]>10){
                if((M.n[0]<50)||(M.n[0]>53)){ MError("\"!?BA:\"-wrong battle index (0,1,50,51,52,53)."); goto l_exit; }
              }else{
                if((M.n[0]<0)||(M.n[0]>1)){ MError("\"!?BA:\"-wrong battle index (0,1,50,51,52,53)."); goto l_exit; }
              }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=M.n[0]+30300;
//              cp->Par[0]=M.VarI[0]; cp->ParSet=1;
              break;
            case 'PI': // VC 'IP': // IP#;
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?IP:\"-wrong syntax."); goto l_exit; }
              if((M.n[0]<0)||(M.n[0]>3)){ MError("\"!?IP:\"-wrong index (0...4)."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=M.n[0]+30330;
              break;
            case 'FB': // VC 'BF': // BF#;
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?BF:\"-wrong syntax."); goto l_exit; }
              if((M.n[0]<0)||(M.n[0]>1)){ MError("\"!?BF:\"-wrong index (0...1)."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=M.n[0]+30800;
              break;
            case 0x5242: // BR;
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?BR:\"-wrong syntax."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=30302;
//              cp->Par[0]=M.VarI[0]; cp->ParSet=1;
              break;
            case 'MC': // VC 'CM': // CM; ���� ����� (0...5)
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?CM:\"-wrong syntax."); goto l_exit; }
              if((M.n[0]<0)||(M.n[0]>999)){ MError("\"!?CM:\"-wrong CM trigger."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              if(M.n[0]==5){
                cp->Event=30319;
              }else{
                cp->Event=30310+M.n[0];
              }
              break;
            case 'MM': // MM; ����� ����� (0-�����,1-�����)
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?MM:\"-wrong syntax."); goto l_exit; }
              if((M.n[0]<0)||(M.n[0]>999)){ MError("\"!?MM:\"-wrong MM trigger."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=30317+M.n[0];
              break;
            case 'EA': // VC 'AE': // AE; �������� ��������� (0-�����,1-�����)
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?AE:\"-wrong syntax."); goto l_exit; }
              if((M.n[0]<0)||(M.n[0]>1)){ MError("\"!?AE:\"-wrong AE trigger."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=30315+M.n[0];
              break;
            case 'GB': // VC 'BG': // BG;
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?BG:\"-wrong syntax."); goto l_exit; }
              if((M.n[0]<0)||(M.n[0]>1)){ MError("\"!?BG:\"-wrong BG trigger (0...1)."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=30303+M.n[0];
//              cp->Par[0]=M.VarI[0]; cp->ParSet=1;
              break;
            case 'WM': // VC 'MW': // MW#;
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?WM:\"-wrong syntax."); goto l_exit; }
              if((M.n[0]<0)||(M.n[0]>1)){ MError("\"!?WM:\"-wrong WM trigger (0...1)."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=M.n[0]+30305;
//              cp->Par[0]=M.VarI[0]; cp->ParSet=1;
              break;
            case 'HT': // VC 'TH': // TH#;
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?TH:\"-wrong syntax."); goto l_exit; }
              if((M.n[0]<0)||(M.n[0]>1)){ MError("\"!?TH:\"-wrong TH trigger (0...1)."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=M.n[0]+30324;
//              cp->Par[0]=M.VarI[0]; cp->ParSet=1;
              break;
            case 0x4D54: // TM#;
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?TM:\"-wrong syntax."); goto l_exit; }
              if((M.n[0]<1)||(M.n[0]>100)){ MError("\"!?TM:\"-wrong timer index (1...100)."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=M.n[0]-1+30000; // ��������
//              cp->Par[0]=M.VarI[0]; cp->ParSet=1;
              if(ERMVarUsedStore==1) LogERMTimerTrigger(M.n[0],&M.m.s[Ind]);
              break;
            case 0x4548: // HE#;
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?HE:\"-wrong syntax."); goto l_exit; }
              if((M.n[0]<0)||(M.n[0]>=HERNUM)){ MError("\"!?HE:\"-wrong hero index."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=M.n[0]+30100; // ��������
//              cp->Par[0]=M.VarI[0]; cp->ParSet=1;
              break;
            case 0x4D48: // HM#; -1 - every hero moves
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?HM:\"-wrong syntax."); goto l_exit; }
              if((M.n[0]<-1)||(M.n[0]>=HERNUM)){ MError("\"!?HM:\"-wrong hero index."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=M.n[0]+30401; // ��������
//              cp->Par[0]=M.VarI[0]; cp->ParSet=1;
              break;
            case 0x4C48: // HL#; -1 - every hero gains level
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?HL:\"-wrong syntax."); goto l_exit; }
              if((M.n[0]<-1)||(M.n[0]>=HERNUM)){ MError("\"!?HL:\"-wrong hero index."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=M.n[0]+30601; // ��������
//              cp->Par[0]=M.VarI[0]; cp->ParSet=1;
              break;
            case 'OC': // VC 'CO':
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?CO:\"-wrong syntax."); goto l_exit; }
              if((M.n[0]<0)||(M.n[0]>3)){ MError("\"!?CO:\"-wrong index (0...4)."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=M.n[0]+30340;
//              cp->Par[0]=M.VarI[0]; cp->ParSet=1;
              break;
            case 'PM': // VC 'MP': // MP; ������������ MP3
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?MP:\"-wrong syntax."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=30320;
              break; 
            case 'GM': // VC 'MG': // MG; magic casting on adv. map
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?MG:\"-wrong syntax."); goto l_exit; }
              if((M.n[0]<0)||(M.n[0]>1)){ MError("\"!?MG:\"-wrong index (0...1)."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=M.n[0]+30322;
              break;
            case 'NS': // VC 'SN': // SN; ������������ Sound
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?SN:\"-wrong syntax."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=30321;
              break;
            case 'RM': // VC 'MR': // 3.58 MR; Magic Resistance in Battle
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?MR:\"-wrong syntax."); goto l_exit; }
              if((M.n[0]<0)||(M.n[0]>2)){ MError("\"!?MR:\"-wrong index (0...2)."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=M.n[0]+30307;
              break;
            case 'FM': // VC 'MF': // 3.58 MF; Monster abilities in a Battle
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?MF:\"-wrong syntax."); goto l_exit; }
              if((M.n[0]<1)/*||(M.n[0]>2)*/){ MError("\"!?MF:\"-wrong index."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=M.n[0]+30800;
              break;
            case 'MG': // VC 'GM': // 3.58 GM#; After Load(0), Before Save(1) game trigger
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?GM:\"-wrong syntax."); goto l_exit; }
              if((M.n[0]<0)||(M.n[0]>1)){ MError("\"!?GM:\"-wrong index."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=M.n[0]+30360;
              break;
            case 'IP': // VC 'PI': // 3.58 PI; post instruction call
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?PI:\"-wrong syntax."); goto l_exit; }
//              if((M.n[0]<1)/*||(M.n[0]>2)*/){ MError("\"!?PI:\"-wrong index."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=30370;
              break;
            case 'LT': // : // TL#; # is number
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?TL:\"-wrong syntax."); goto l_exit; }
              if((M.n[0]<0)||(M.n[0]>4)){ MError("\"!?TL:\"-wrong index (0...4)."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=M.n[0]+30900;
              break;
            case 'LD': // 3.59 DL; dialog call back
              M.c[0]=';';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1){ MError("\"!?DL:\"-wrong syntax."); goto l_exit; }
              if(cp!=0) cp=cp->Next; else cp=cp0;
              cp->Event=30371;
              break;

////            case 'SV': // SV#; set scope number
////              M.c[0]=';';
////              Ind=M.i;
////              if(GetNumAutoFl(&M)!=1){ MError("\"!?SV:\"-wrong syntax."); goto l_exit; }
////              if((M.n[0]<0)||(M.n[0]>50000)){ MError("\"!?HL:\"-wrong scope index(0,1...50000)."); goto l_exit; }
////              CurrentScope=(Word)M.n[0];
////              break;
            default: MError("\"!?##:\"-wrong or not yet realized trigger type."); goto _cont;
          }
////
          cp->Type=Id;
          cp->Scope=ScriptIndex4ERM; // 3.59
////          cp->Type=CurrentScope;
////          AddScope(cp->Type);
////          ERMScope=FindScope(cp->Type);
          cp->Num=0;
          for(k=0;k<16;k++){
            VNCopy(&M.Efl[0][k][0],&cp->Efl[0][k][0]);
            VNCopy(&M.Efl[0][k][1],&cp->Efl[0][k][1]);
            VNCopy(&M.Efl[1][k][0],&cp->Efl[1][k][0]);
            VNCopy(&M.Efl[1][k][1],&cp->Efl[1][k][1]);
          }
          cp->Disabled=cp->DisabledPrev=0;
          if(ERMVarUsedStore==1) LogTriggerConditions(cp,&M.m.s[Ind]);
        }else if((M.m.s[M.i]=='!')||(M.m.s[M.i]=='#')){ // �������-�������� ��� ����������
          if(M.m.s[M.i]=='#') InstrFlag=1;
          else InstrFlag=0;
          ++M.i;
          self=M.i;
          Id=*(Word *)&M.m.s[M.i]; M.i+=2;
          ParSet=0;
          switch(Id){
            case 0x4547: // GE#:
              M.c[0]=':';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1) goto l_exit;
              if(M.n[0]<0) goto l_exit;
              for(GEp=GEp0;GEp<GEp1;GEp++){
                if(MakeSpec(&GEp->Mes.m,M.n[0])) goto _found;
              }
              goto l_exit;
_found:
              ToDoPo=(Dword)GEp;
              ParSet=0;
              break;
            case 0x454C: // LE$ LE##/##/#:
              M.c[0]=':';
              Ind=M.i;
              Num=GetNumAutoFl(&M);
              if(Num==3){
                ToDoPo=PosMixed(M.n[0],M.n[1],M.n[2]);
                Par[0]=M.VarI[0]; Par[1]=M.VarI[1]; Par[2]=M.VarI[2]; ParSet=3;
              }else if(Num==1){
                ToDoPo=*(Dword *)&M.VarI[0];
                Par[0]=M.VarI[0]; ParSet=1;
              }else{ MError("\"!!LE:\"-wrong syntax (LE$/$/$,LE$)."); goto l_exit; }
              break;
            case 0x4F4D: // MO$ MO##/##/#: or MOx/y/l/1 -dynamic
              M.c[0]=':';
              Ind=M.i;
              Num=GetNumAutoFl(&M);
              if(Num>=3){ // ����� ���� 4
                ToDoPo=PosMixed(M.n[0],M.n[1],M.n[2]);
                Par[0]=M.VarI[0]; Par[1]=M.VarI[1]; Par[2]=M.VarI[2]; ParSet=3;
              }else if(Num==1){
                ToDoPo=*(Dword *)&M.VarI[0];
                Par[0]=M.VarI[0]; ParSet=1;
              }else{ MError("\"!!MO:\"-wrong syntax (MO$/$/$(/$),MO$)."); goto l_exit; }
              break;
            case 0x4543: // CE##:
              M.c[0]=':';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1) goto l_exit;
              if(M.n[0]<0) goto l_exit;
              for(CEp=CEp0;CEp<CEp1;CEp++){
                if(MakeSpec(&CEp->Mes.m,M.n[0])) goto _found1;
              }
              goto l_exit;
_found1:
              ToDoPo=(Dword)CEp;
              ParSet=0;
              break;
            case 0x5241: // AR#:
              M.c[0]=':';
              Ind=M.i;
              Num=GetNumAutoFl(&M);
              if(Num==1){
//                MError("\"!!AR$:\"-disabled old style syntax."); goto l_exit;
/*
                if(M.n[0]<0) goto l_exit;
                for(Ap=Ap0;Ap<Ap1;Ap++){
                  if(MakeSpec(&Ap->Mes.m,M.n[0])) goto _found3;
                }
                goto l_exit;
_found3:
                ToDoPo=(Dword)Ap;
                ParSet=0;
*/
                 ToDoPo=0;
                 Par[0]=M.VarI[0]; ParSet=1;
             }else if(Num==3){
                ToDoPo=0;
//                ToDoPo2=PosMixed(M.n[0],M.n[1],M.n[2]);
                Par[0]=M.VarI[0]; Par[1]=M.VarI[1]; Par[2]=M.VarI[2]; ParSet=3;
              }
              break;
            case 0x4548: // HE#: ��� HE#1/#2/#3: ��� HE-1: ��� HEv:
              M.c[0]=':';
              Ind=M.i;
              switch(GetNumAutoFl(&M)){
                case 1:
                  if(M.n[0]==-1){ // �����, ����������� �� ������
                    ToDoPo=0;
                    Par[0]=M.VarI[0]; ParSet=1;
                  }else{
//                    if(M.VarI[0].Num!=0){
                      ToDoPo=1;
                      Par[0]=M.VarI[0]; ParSet=1;
//                      ToDoPo2=*(Dword *)&M.VarI[0]/*M.vi[0]*//*GetVar(&M,0)*/;
//                      if(ToDoPo2==0){ MError("\"HE#:\"-hero not found."); goto l_exit; }
//                    }else{
//                      if((M.n[0]<0)||(M.n[0]>=Hn)) goto l_exit;
//                      ToDoPo =(Dword)&Hp0 [M.n[0]];
//                      ToDoPo2=(Dword)&THp0[M.n[0]];
//                    }
                  }
                  break;
                case 3:
                  ToDoPo=0;
//                  ToDoPo2=PosMixed(M.n[0],M.n[1],M.n[2]);
                  Par[0]=M.VarI[0]; Par[1]=M.VarI[1]; Par[2]=M.VarI[2]; ParSet=3;
                  break;
                default:
                  goto l_exit;
              }
              break;
            case 0x4649: // IF:
              M.c[0]=':';
              Ind=M.i;
              if(GetNumAutoFl(&M)!=1) goto l_exit;
              ParSet=0;
              break;
            default:
              for(i=0;;i++){
                if(ERM_Addition[i].Id==0) break;
                if(ERM_Addition[i].Id==Id) goto _addfound;
              }
//__asm int 3
//              Message("Unknown Receiver or Instruction");
              DumpMessage(&M.m.s[M.i],-4);
              goto _next;
_addfound:
              ToDoPo=0;
              switch(ERM_Addition[i].Type){
                case 5: // ����������.����������
                  M.c[0]=':';
                  Ind=M.i;
                  if(GetNumAutoFl(&M)!=2){ MError("\"!!$$:\"-wrong syntax (t=5)."); goto l_exit; }
//                  ToDoPo=*(Dword *)&M.VarI[0];
//                  ToDoPo2=*(Dword *)&M.VarI[1];
                  Par[0]=M.VarI[0]; Par[1]=M.VarI[1]; ParSet=2;
                  break;
                case 4: // ����
                 {
//                  Cycle *cp;
                  M.c[0]=':';
                  Ind=M.i;
                  if(GetNumAutoFl(&M)!=4){ MError("\"!!$$:\"-wrong syntax for receiver (cycle)."); goto l_exit; }
//                  if((M.n[1]<-1000)||(M.n[1]>1000)){ MError("\"!!$$:\"-wrong value (cycle from -1000...1000)."); goto l_exit; }
//                  if((M.n[2]<-1000)||(M.n[2]>1000)){ MError("\"!!$$:\"-wrong value (cycle to -1000...1000)."); goto l_exit; }
//                  if((M.n[3]<-500)||(M.n[3]>500)){ MError("\"!!$$:\"-wrong value (cycle step -500...500)."); goto l_exit; }
//                  ToDoPo=M.n[0];
//                  cp=(Cycle *)&ToDoPo2;
//                  cp->From=M.n[1];
//                  cp->To=M.n[2];
//                  cp->Step=M.n[3];
                  Par[0]=M.VarI[0]; Par[1]=M.VarI[1];
                  Par[2]=M.VarI[2]; Par[3]=M.VarI[3];
                  ParSet=4;
                  break;
                 }
                case 3: // ��������� �����
                  M.c[0]=':';
                  Ind=M.i;
                  if(GetNumAutoFl(&M)!=1){ MError("\"!!$$:\"-wrong syntax (t=3)."); goto l_exit; }
                  ToDoPo=M.n[0];
                  Par[0]=M.VarI[0]; ParSet=1;
                  break;
                case 2: // ��������� �������/ �����(���)/��� � ������
                  M.c[0]=':';
                  Ind=M.i;
                  Num=GetNumAutoFl(&M);
                  switch(Num){
                    case 1:
                      Par[0]=M.VarI[0]; ParSet=1;
                      break;
                    case 2:
                      Par[0]=M.VarI[0]; Par[1]=M.VarI[1]; ParSet=2;
                      break;
                    case 3:
                      Par[0]=M.VarI[0]; Par[1]=M.VarI[1]; Par[2]=M.VarI[2]; ParSet=3;
                      break;
                    case 4: //3.58
                      Par[0]=M.VarI[0]; Par[1]=M.VarI[1]; Par[2]=M.VarI[2]; Par[3]=M.VarI[3]; ParSet=4;
                      break;
                    case 5: //3.58
                      Par[0]=M.VarI[0]; Par[1]=M.VarI[1]; Par[2]=M.VarI[2]; Par[3]=M.VarI[3]; Par[4]=M.VarI[4]; ParSet=5;
                      break;
                    default:
                      MError("\"!!$$:\"-wrong syntax (t=2)."); goto l_exit;
                  }
                  break;
                case 1: // ��������� �����/����������   ...$
//                  ToDoPo=(Dword)M.m.s[M.i++];
                  M.c[0]=':';
                  Ind=M.i;
                  if(GetNumAutoFl(&M)!=1){ MError("\"!!$$:\"-wrong syntax (t=1)."); goto l_exit; }
//                  ToDoPo=*(Dword *)&M.VarI[0];
//                  ToDoPo2=0;
                  Par[0]=M.VarI[0]; ParSet=1;
                  break;
                case 0:
                  M.c[0]=':';
                  Ind=M.i;
                  if(GetNumAutoFl(&M)!=1) goto l_exit;
//                  ToDoPo=M.n[0];
//                  ToDoPo2=0;
                  Par[0]=M.VarI[0]; ParSet=1;
                  break;
                default: MError("\"!!$$:\"-wrong syntax (t=unknown)."); goto l_exit;
              }
              if(ERMVarUsedStore==1){ LogERMAnyReceiver(Id,Par[0],&M.m.s[Ind]); }
          }
          if(InstrFlag==0){
            if(cp==0) goto l_exit;
            dp=&cp->ToDo[cp->Num];
          }else{
            dp=&ltd;
          }
          dp->Type=Id;
          for(k=0;k<16;k++){
            VNCopy(&M.Efl[0][k][0],&dp->Efl[0][k][0]);
            VNCopy(&M.Efl[0][k][1],&dp->Efl[0][k][1]);
            VNCopy(&M.Efl[1][k][0],&dp->Efl[1][k][0]);
            VNCopy(&M.Efl[1][k][1],&dp->Efl[1][k][1]);
          }
          dp->Disabled=dp->DisabledPrev=0;
          dp->Pointer=ToDoPo;
//          dp->Pointer[1]=ToDoPo2;
          dp->ParSet=ParSet;
          for(k=0;k<ParSet;k++) dp->Par[k]=Par[k];
          for(   ;k<16    ;k++) /**(Dword *)&dp->Par[k]=0;*/ SetMem(&dp->Par[k],sizeof(VarNum),0);
          dp->Com.s=&M.m.s[M.i];
          dp->Self.s=&M.m.s[self];
          dp->Self.l=M.i-self;
          if(ERMVarUsedStore==1) LogERMVarUsed(dp,&M.m.s[Ind]);
          ind=M.i; M.c[0]=';';
          if(SkipUntil(&M)) goto l_exit;
          dp->Com.l=(Word)(M.i-ind);
          if(InstrFlag){
            if((nL==0)|| Post){ // �� ��������� ������� ���������� ��� ��������
              if(Post){ // �� ���� ����� ���������
                // ���� ��������, ������ ���� ��������� � ������ ����
                // ��������� ����������
                ProcessCmd(dp,!nL,1); // ���� ����� ����, � �� ��������
              }else{
                if(nL==0){
                  if(CheckFlags(M.Efl)==0){ // �������� ����������
                    ProcessCmd(dp,1,0); // ���� ����� ����, � �� ��������
                  }
                }
              }
            }
//            InstrFlag=0;
          }else{
            cp->Num++;
            // ��������� �� ����� ��� ������
            if(((char *)&cp->ToDo[cp->Num])-((char *)cp0)>=HSize){
              Message("Sorry, your script is too big and there is not enough internal memory (30Mbytes!)",1);
              goto l_exit2;
            }
          }

_next:;
        }else if(M.m.s[M.i]=='@'){ // ���� ���������
          ++M.i;
          PERM->p=M.i;
          goto _contnext;
        }else{
          ++M.i;
        }
_cont:
        continue;
      }while(1);
    }
_contnext:;
  }
  ClearCrChanged();
  // Show arrow
//  SetMouseCursor(0,0);
  RETURNV
l_exit:
//  Message("{ERM} has wrong syntax. Disabled.",1);
  Message(ITxt(26,0,&Strings),1);
  Message(&M.m.s[Ind],1);
l_exit2:
  ERMEnabled=0;
  // Show arrow
//  SetMouseCursor(0,0);
  RETURNV
}

void InitERM(void)
{
  #include "templ.h"
  // ��������� WoG
  __asm{
    mov   eax,BASE
    mov   eax,[eax]
//    add   eax,0x1F86C+IDSHIFT
//    movzx eax,byte ptr [eax]
//    mov   WoG,eax
    add   eax,0x1F86C
    mov   eax,[eax]
    mov   IDummy,eax
  }
  if(IDummy==SOGMAPTYPE) WoG=1; else WoG=0;
  // !!!
  WoGatLoad=WoG;
  if(PL_ApplyWoG>1){
    WoG=1;
  }
  // ��������������� ���������
  ResetAll();
  WOG_CRC(8452453) 
    if(__v!=8452453) EXITERW(847662,ecx,__v) // RETURNV
// ������������� ����� ��� ���� �������� ��� ����� ����
  __asm mov edx,BASE
  __asm mov edx,[edx]
  __asm add edx,0x1F63E
  _EDX(CurDate);
  InitCastles();
  RETURNV
}
/* 3.58
void FindERMn(void)
{
  asm pusha;
  asm mov Esi_,esi
  asm mov nL,0
  STARTC("Find ERM in New Game",0)
  InitERM();
  LoadERMTXT(1);
  FindERM();
// �������� ��������
  StartAnimation();
  STOP
  asm popa;
}
*/
void FindERMn(void)
{
  __asm pusha;
  __asm mov nL,0
  #include "templ.h"
  InitERM();
  LoadERMTXT(1);
  FindERM();
// �������� ��������
  StartAnimation();
  STOP
  __asm popa;
}

void FindERMl()
{
  __asm pusha;
//  asm mov Esi_,esi
  __asm mov nL,1
  InitERM();
//  LoadERMTXT(1); // �������� ��������� ����������
//  FindERM();
  __asm popa;
}
//////////////////////////////
// 0-30000 functions
// 30000-30100 timers
// 30100-30300 heroes
// 30300 to battle
// 30301 from battle
// 30302 next battle turn
// 30303 monster's action
// 30304 monster's after action
// 30305 WM reach dest
// 30306 WM killed
// 30307 MR Magic Resistance in Battle (pre-trigger)
// 30308 MR Magic Resistance in Battle (post-trigger)
// 30309 MR Dwarf Magic Resistance
// 30310 mouse click �� ����� (������) !?CM0
// 30311 mouse click � ������ !?CM1
// 30312 mouse click in hero screen !?CM2
// 30313 mouse click it two heroes screen !?CM3
// 30314 mouse click in battlefield !?CM4
// 30315 ����� ���� ��������
// 30316 ����� ���� ��������
// 30317 mouse move over battlefield
// 30318 mouse move over townscreen
// 30319 mouse click �� ����� (�����) !?CM5
// 30320 MP3 music
// 30321 WAV and M82 Sound 3.58
// 30322 Magic cast (adv. map) (pre-trigger)
// 30323 Magic cast (adv. map) (post-trigger)
// 30324 Go to Town Hall Screen 3.58 !?TH0
// 30325 Leave Town Hall Screen 3.58 !?TH1
// 30330 MP before sending data before battle
// 30331 MP after receiving data before battle
// 30332 MP before sending data after battle
// 30333 MP after receiving data after battle
// 30334 MP received data during a battle
// 30340 CO ����� ��������� ������� ���������
// 30341 CO ����� �������� ������� ���������
// 30342 CO ����� ������� ��������� � ������
// 30343 CO ����� ����������� ��������� � ������
// 30350 to battle
// 30351 from battle
// 30352 universal to battle
// 30353 universal from battle
// 30360 Load Game
// 30361 Save Game
// 30370 Post Instruction call (������ ��� ������ ����� �����, �� �� ��������)
// 30371 Dlg CallBack
// 30400-30600 hero every movement
// 30600-30800 hero gain level
// 30800 setup battle field
// 30801 MFCall(1); !?MF1; - Block ability
// 30900-30904 ; TL - timer #-seconds to call
// 31000-31099 - 100 local functions
// ...
// 0x04000000 ... ���� ������������ ��� - �������
// 0x10000000+ OB position enter
// 0x20000000+ LE position
// 0x40000000+ OB type/subtype enter
// 0x08000000+ OB leave
//      +  0x10000000+ OB position leave
//      +  0x40000000+ OB type/subtype leave
Dword pointer;

char TrigIf[11];
void ProcessERM(void)
{
  struct _Cmd_ *cp;
  Dword  ev;
  int    i;
  char   OldIf[11];
  int    OldY[100];
  float  OldF[100];
  int    OldScope;
//  char   OldString[10][512];

  #include "templ.h"
  ev=pointer; // �� �� ��� ������
  cp=Heap;
  if(ERMEnabled==0) RETURNV // ERM �� �������
  while(cp->Event!=0){
    if(cp->Event==ev){ // ! ����� ������
      if((ev>=31000)&&(ev<31100)){ // local function should be in the same scope
        if(cp->Scope!=GlobalCurrentScope) goto _Cont;
      }
      OldScope=GlobalCurrentScope;
      GlobalCurrentScope=cp->Scope;
////      ERMScope=FindScope(cp->Type);
      if(cp->Disabled==0){ // �������� ���������?
        for(i=0;i<11;i++){  OldIf[i]=TrigIf[i]; TrigIf[i]=-1; }
        for(i=0;i<100;i++){ OldY[i]=ERMVarYT[i]; }
        for(i=0;i<100;i++){ OldF[i]=ERMVarFT[i]; }
//        for(i=0;i<10;i++) for(j=0;j<512;j++) { OldString[i][j]=ERMLString[i][j]; }
        if((cp->Event<30000)||((cp->Event>=31000)&&(cp->Event<31100))){ // function
        }else{ //other
          for(i=0;i<100;i++){ ERMVarYT[i]=0; }
          for(i=0;i<100;i++){ ERMVarFT[i]=0; }
        }
        if(ERM_GM_ai>=0) ERMFlags[999]=(char)ERM_GM_ai;
        else ERMFlags[999]=(char)(!IsAI(CurrentUser()));
        ERMFlags[998]=(char)IsThis(CurrentUser());
        // �������� �������
        ERMVar2[997]=ERM_PosX; ERMVar2[998]=ERM_PosY; ERMVar2[999]=ERM_PosL;
        TriggerBreak=0;
        if(CheckFlags(cp->Efl)==0){ // �������� ����������
          for(i=0;i<cp->Num;i++){
            if(ERMEnabled==0) RETURNV // ERM ��� ��������
/*
            if(CheckFlags(cp->ToDo[i].Efl)) continue; // �������� ����������
            ProcessCmd(&cp->ToDo[i],0,0);
            if(TriggerBreak){
              TriggerBreak=0;
              break;
            }
*/
// 3.59 if support
            Word cmd;
            cmd=cp->ToDo[i].Type;
            if(cmd=='fi'){  // if
              TrigIf[10]++; 
              if(TrigIf[10]>9){ MError("\"if\" - too many IFs (>10)"); RETURNV }
              if(TrigIf[10]<0){ MError("\"if\" - incorrect IF index (internal)"); RETURNV }
              if((TrigIf[10]==0) || (TrigIf[TrigIf[10]-1]==1)){ // active section
                TrigIf[TrigIf[10]]=!CheckFlags(cp->ToDo[i].Efl);
              }else{ // NOT active section
                TrigIf[TrigIf[10]]=-1;
              }
              continue;
            }else if(cmd=='le'){ // else
              if(TrigIf[10]<0){ MError("\"el\" - no IF for ELSE"); RETURNV }
              if(TrigIf[10]>9){ MError("\"el\" - too many IFs (>10)"); RETURNV }
              if(TrigIf[TrigIf[10]]==-1) continue; // not active section
              if(TrigIf[TrigIf[10]]==1) TrigIf[TrigIf[10]]=0; else TrigIf[TrigIf[10]]=1;
              continue;
            }else if(cmd=='ne'){ // endif
              if(TrigIf[10]<0){ MError("\"en\" - no IF for ENDIF"); RETURNV }
              if(TrigIf[10]>9){ MError("\"en\" - too many IFs (internal)"); RETURNV }
              TrigIf[10]--; 
              continue;
            }
            if(TrigIf[10]>=0){ // there is IF active
              if(TrigIf[TrigIf[10]]!=1) continue; // this part of IF is not active
            }
            if(CheckFlags(cp->ToDo[i].Efl)) continue; // �������� ����������
            ProcessCmd(&cp->ToDo[i],0,0);
            if(TriggerBreak){
              TriggerBreak=0;
              break;
            }
          }
        }
        for(i=0;i<11;i++){  TrigIf[i]=OldIf[i]; }
        if((cp->Event<30000)||((cp->Event>=31000)&&(cp->Event<31099))){ // function
        }else{ //other
          for(i=0;i<100;i++){ ERMVarYT[i]=OldY[i]; }
          for(i=0;i<100;i++){ ERMVarFT[i]=OldF[i]; }
        }
//        for(i=0;i<10;i++) for(j=0;j<512;j++) { ERMLString[i][j]=OldString[i][j]; }
      }
      GlobalCurrentScope=OldScope;

_Cont:;
    }
    if(cp->Next==0) break;
    cp=cp->Next;
  }
  RETURNV
}

void FUCall(int n)
{
  #include "templ.h"
  Dword oldpo=pointer;
  // 3.59
  if(n<0){
    if(n<-100){ MError("Local Fuction Index out of range (-1...-100)"); RETURNV }
    n=-n+31000-1;
  }else{
    if(n>30000){ MError("Fuction Index out of range (1...30000)"); RETURNV }
  }
  pointer=n;
//  ERM_PosX=0;ERM_PosY=0;ERM_PosL=0;
  ProcessERM();
  pointer=oldpo;
  RETURNV
}

// 3.58 post instruction call
void _PostInstrCall(void){
  #include "templ.h"
  if(nL==0){ // ���� ������ ����� ����
    Dword oldpo=pointer;
    pointer=30370;
    ProcessERM();
    pointer=oldpo;
  }
  RETURNV
}
void PostInstrCall(void){
  __asm pusha
  __asm mov ecx,0x698450
  __asm xor eax,eax
  __asm mov [ecx],eax
  _PostInstrCall();
  __asm popa
}
// Commander
void COCall(Dword n,_Hero_ *hp)
{
  #include "templ.h"
  Dword oldpo=pointer;
  int oldx=ERM_PosX,oldy=ERM_PosY,oldl=ERM_PosL;
  pointer=n+30340;
  ERM_GM_ai=IsThis(hp->Owner);
  ERM_HeroStr=hp;
  ERM_PosX=hp->x; ERM_PosY=hp->y; ERM_PosL=hp->l;
  ProcessERM();
  ERM_PosX=oldx; ERM_PosY=oldy; ERM_PosL=oldl;
  pointer=oldpo;
  RETURNV
}
// battle
void BACall(Dword n,_Hero_ *hp)
{
  #include "templ.h"
  Dword oldpo=pointer;
  pointer=n+30300;
  ERM_GM_ai=!G2B_CompleteAI;
//  ERM_PosX=0;ERM_PosY=0;ERM_PosL=0;
  ERM_HeroStr=hp; // 3.57f 29.01.03
  ProcessERM();
  pointer=oldpo;
  RETURNV
}
// Timer - 3.59
void TLCall(Dword timesec)
{
  #include "templ.h"
  Dword oldpo=pointer;
  if(timesec%60 == 0){ pointer=30904; ProcessERM(); }
  if(timesec%10 == 0){ pointer=30903; ProcessERM(); }
  if(timesec%5 == 0){ pointer=30902; ProcessERM(); }
  if(timesec%2 == 0){ pointer=30901; ProcessERM(); }
  pointer=30900; ProcessERM();
  pointer=oldpo;
  RETURNV
}

void DlgCallBack(int dlg,int item,int action)
{
  #include "templ.h"
  Dword Dlg_Oldpo=pointer;
  int oldx=ERM_PosX,oldy=ERM_PosY,oldl=ERM_PosL;
  pointer=30371; 
  ERM_PosX=dlg; ERM_PosY=item; ERM_PosL=action;
  ProcessERM();
  ERM_PosX=oldx; ERM_PosY=oldy; ERM_PosL=oldl;
  pointer=Dlg_Oldpo;
  RETURNV
}
/*
void DlgSpellCallBack(int dlg,int x,int y,int action)
{
  #include "templ.h"
  Dword Dlg_Oldpo=pointer;
  int oldx=ERM_PosX,oldy=ERM_PosY,oldl=ERM_PosL;
  pointer=30372; 
  ERM_PosX=x; ERM_PosY=y; ERM_PosL=action;
  ProcessERM();
  ERM_PosX=oldx; ERM_PosY=oldy; ERM_PosL=oldl;
  pointer=Dlg_Oldpo;
  RETURNV
}
*/
// multiplayer
void TriggerIP(Dword n)
{
  #include "templ.h"
  Dword oldpo=pointer;
  pointer=n+30330;
  ProcessERM();
  pointer=oldpo;
  RETURNV
}
// battle ������ �����
void BACall2(Dword /*n*/,int Day)
{
  #include "templ.h"
  Dword oldpo=pointer;
//  pointer=n+30300;
  pointer=30302;
//  ERM_PosX=0;ERM_PosY=0;ERM_PosL=0;
  ERMVar2[996]=Day;
  ProcessERM();
  pointer=oldpo;
  RETURNV
}

void MP3Call(void)
{
  #include "templ.h"
  Dword oldpo=pointer;
  pointer=30320;
  ProcessERM();
  pointer=oldpo;
  RETURNV
}

void SoundCall(void)
{
  #include "templ.h"
  Dword oldpo=pointer;
  pointer=30321;
  ProcessERM();
  pointer=oldpo;
  RETURNV
}

void AdvMagicCastCall(int beforeAFTER)
{
  #include "templ.h"
  Dword oldpo=pointer;
  pointer=30322+beforeAFTER;
  ProcessERM();
  pointer=oldpo;
  RETURNV
}

static int AMM_Skill=-1;
void AdvMagicManagerSkill(void)
{
  __asm{
    mov   eax, 0x59CBF0
    call  eax
  }
  __asm   pusha
  __asm{
        mov   eax,0x6992D0
        mov   eax,[eax]
        mov   eax,[eax+0x38]
  }
  _EAX(AMM_Skill);
  __asm   popa
}

void AdvMagicManager(void)
{
  __asm   pusha
  AMM_Skill=-1;
  AdvMagicCastCall(0);
  __asm   popa
  __asm   mov   eax,0x41C470
  __asm   call  eax
  __asm   pusha
  ERMVar2[996]=AMM_Skill;
  if(ERMVar2[996]==0x7801) ERMVar2[996]=-1;
  AdvMagicCastCall(1);
  __asm   popa
}

void BACall3(int beforeAFTER,int Day)
{
  #include "templ.h"
  Dword oldpo=pointer;
//  pointer=n+30300;
  pointer=30303+beforeAFTER;
//  ERM_PosX=0;ERM_PosY=0;ERM_PosL=0;
  ERMVar2[996]=Day;
  ProcessERM();
  pointer=oldpo;
  RETURNV
}
// 3.58 Mon Resist
void MRCall(int beforeAFTER)
{
  #include "templ.h"
  Dword oldpo=pointer;
  pointer=30307+beforeAFTER;
  ERM_GM_ai=!G2B_CompleteAI;
  ProcessERM();
  pointer=oldpo;
  RETURNV
}
void MFCall(int CallType)
{
  #include "templ.h"
  Dword oldpo=pointer;
  pointer=30800+CallType;
  ERM_GM_ai=!G2B_CompleteAI;
  ProcessERM();
  pointer=oldpo;
  RETURNV
}
// battle field
void BFCall(void)
{
  #include "templ.h"
  Dword oldpo=pointer;
  pointer=30800;
  ProcessERM();
  pointer=oldpo;
  RETURNV
}

int IsDisabled(Dword MixPos,int Owner)
{
  #include "templ.h"
  _ERM_Object_ *obj;
  if((Owner<0)||(Owner>8)) RETURN(1)
  if((MixPos&0x10000000)==0){ // �����
    RETURN(ERM_Hero[MixPos-30100].Disabled[Owner])
  }else{
    MixPos&=0x0FFFFFFF; // ����������� ���������� ���
    obj=FindObj(MixPos);
    if(obj==0) RETURN(0)
    M_MDisabled=obj->AMessage[Owner][0];
    M_MDisabledNext=obj->AMessage[Owner][1];
    obj->AMessage[Owner][0]=obj->AMessage[Owner][1];
    RETURN(obj->Disabled[Owner])
  }
}

/*
int ERM2Object(int GM_ai,Dword MixPos,_MapItem_ *Mi,_Hero_ *Hr)
{
  ERM_GM_ai=GM_ai;
  ERM_HeroStr=Hr;
  Dword lpointer,dpointer,oldpo;
  int ret;

  oldpo=pointer;
  MixedPos(&ERM_PosX,&ERM_PosY,&ERM_PosL,MixPos);
  if(Mi->OType!=0x22){ // ������
    dpointer=MixPos&0x07FF03FF;
    dpointer|=0x10000000;
  }else{ // �����
    dpointer=Mi->SetUp+30100;
  }
//  IsDisabled(dpointer,Hr->Owner);
  if(Mi->OType!=0x22){ // ������
    lpointer=Mi->OType<<12;
    lpointer|=0x40000000;
    pointer=lpointer;
    ProcessERM();
    lpointer=(Mi->OType<<12)+(Mi->OSType+1);
    lpointer|=0x40000000;
    pointer=lpointer;
    ProcessERM();
  }
  pointer=dpointer;
  ProcessERM();
  ret=IsDisabled(dpointer,Hr->Owner);
  pointer=oldpo;
  return ret;
}
*/
int ERM2Object(int prePOST,int GM_ai,Dword MixPos,_MapItem_ *Mi,_Hero_ *Hr,int o_t,int o_st)
{
  #include "templ.h"
  ERM_GM_ai=GM_ai;
  ERM_HeroStr=Hr;
  Dword lpointer,oldpo;
  int ret;

  oldpo=pointer;
  MixedPos(&ERM_PosX,&ERM_PosY,&ERM_PosL,MixPos);
// �� ���� ����� ������ ��������� �������
  if((o_t==0x22)&&(Mi->OType!=0x22)) RETURN(0) // ���� ������ ��� �����, � �� ����
  if(o_t!=0x22){ // ������
    lpointer=o_t<<12;
    lpointer|=0x40000000; if(prePOST) lpointer|=0x08000000;
    pointer=lpointer;
    ProcessERM();
    lpointer=(o_t<<12)+(o_st+1);
    lpointer|=0x40000000; if(prePOST) lpointer|=0x08000000;
    pointer=lpointer;
    ProcessERM();
  }else{
    if((int)Mi->SetUp==Hr->Number){ // ��� � ����� - ������ ���� ������ ��������
      lpointer=Hr->PlOType<<12;
      lpointer|=0x40000000; if(prePOST) lpointer|=0x08000000;
      pointer=lpointer;
      ProcessERM();
      lpointer=(Hr->PlOType<<12)+(Mi->OSType+1);
      lpointer|=0x40000000; if(prePOST) lpointer|=0x08000000;
      pointer=lpointer;
      ProcessERM();
    }
  }
  if(o_t!=0x22){ // ������
    lpointer=MixPos&0x07FF03FF;
    lpointer|=0x10000000; if(prePOST) lpointer|=0x08000000;
  }else{ // �����
    if((int)Mi->SetUp==Hr->Number){ // ��� � ����� - ������ ���� ������ ��������
      lpointer=MixPos&0x07FF03FF;
      lpointer|=0x10000000; if(prePOST) lpointer|=0x08000000;
    }else{
      lpointer=Mi->SetUp+30100;
    }
  }
  pointer=lpointer;
  ProcessERM();
//  Dword setup=MIp->SetUp; Word otype=MIp->OType;
//  if(otype==0x22){ // ����� "�����" ��� ������������
//    _Hero_ *hp=GetHeroStr(setup);
//    MIp->SetUp=hp->PlSetUp; MIp->OType=(Word)hp->PlOType;
//  }
  pointer=lpointer;
//asm int 3
  ret=IsDisabled(pointer,Hr->Owner);
  pointer=oldpo;
  RETURN(ret)
}

void HeroMove(_Hero_ *hp, int NewX, int NewY, int NewL)
{
  #include "templ.h"
  Dword oldpo=pointer;
  int oldx=ERM_PosX,oldy=ERM_PosY,oldl=ERM_PosL;
  if(hp==0){MError("\"HeroMoveTrigger:\"- cannot find hero."); RETURNV}
  ERM_GM_ai=-1;
  ERM_HeroStr=hp;
  ERM_PosX=NewX; ERM_PosY=NewY; ERM_PosL=NewL;
  // ����� �����
  pointer=30400;
  ProcessERM();
  // ���������� �����
  pointer=30401+hp->Number;
  ProcessERM();
  ERM_PosX=oldx; ERM_PosY=oldy; ERM_PosL=oldl;
  pointer=oldpo;
  RETURNV
}

static int     GL_PSkill;
static int     GL_SSkill[2];
static _Hero_ *GL_Hp;
static Dword   GL_oldpo;
void GainLevel(void)
{
  __asm pusha
  _ESI(GL_PSkill);
  _EBX(GL_Hp);
  #include "templ.h"
  if(GL_Hp==0){MError("\"HeroGainLevel:\"- cannot find hero."); RETURNV}
  GL_SSkill[0]=GL_SSkill[1]=-2;
//  ERM_GM_ai=-1;
  ERM_GM_ai=!IsAI(GL_Hp->Owner);
  ERM_HeroStr=GL_Hp;
//  ERM_PosX=NewX; ERM_PosY=NewY; ERM_PosL=NewL;
  // ����� �����
  GL_oldpo=pointer;
  pointer=30600;
  ProcessERM();
  // ���������� �����
  pointer=30601+GL_Hp->Number;
  ProcessERM();
  pointer=GL_oldpo;
  __asm{
    popa
    mov    eax,GL_PSkill
    mov    dl,[ebx+eax+0x476]
    inc    dl
    mov    [ebx+eax+0x476],dl
  }
  RETURNV
}

int ERM_HeroGainLevel(char Cmd,int Num,_ToDo_* /*sp*/,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  switch(Cmd){
    case 'S': // Mfirst(0...3)/SSkil1(-1,...)/SSkil2(-1,...)
      if(Num<3){ MError("\"!!HL:S\"-insufficient parameters."); RETURN(0) }
      Apply(&GL_PSkill,4,Mp,0);
      Apply(&GL_SSkill[0],4,Mp,1);
      Apply(&GL_SSkill[1],4,Mp,2);
      break;
    default:
      MError("\"!!HL:\"-wrong command.");
      RETURN(0)
  }
  RETURN(1)
}

static int     GL_Flag2;
static _Hero_ *GL_Hp2;
int __stdcall GainLevelSSkill(int Flag1,int PrevSkill)
{
  _EDX(GL_Flag2);
  _ECX(GL_Hp2);
  #include "templ.h"
  if(PrevSkill==-1){ // ���� ��� ������ �� ����
    if(GL_SSkill[0]!=-2){ // ���� ������ ������
      RETURN(GL_SSkill[0])
    }
  }else{
    if(GL_SSkill[1]!=-2){ // ���� ������ ������
      RETURN(GL_SSkill[1])
    }
  }
  __asm{
    push   PrevSkill
    push   Flag1
    mov    edx,GL_Flag2
    mov    ecx,GL_Hp2
    mov    eax,0x4DAF70
    call   eax
    mov    IDummy,eax
  }
  RETURN(IDummy)
}

// 49F830 edi=����� ��������� ������ 
// ���������� ��� ����������� �� �����.
/*
void EventERM(void)
{
  asm pusha;
  asm mov   pointer,edi
  asm mov   eax,-1
  asm mov   ERM_GM_ai,eax
  asm mov   eax,0
  asm mov   ERM_HeroStr,ebx
  ProcessERM();
  asm popa;
}
*/
//00481056 8B08
//00481058 52             push   edx  ?
//00481059 8B55EC
//0048105C 51             push   ecx  MixPos
//0048105D 52             push   edx  ->MIp
//0048105E 56             push   esi  ->Hp
//0048105F 8BCF           mov    ecx,edi ->advManager
//00481061E8DAFA0100     call   H3.004A0B40
//00481066 8B45F4
//static EE_AdvMan;
static _Event_ *EMUM_Ep;
static Dword    EMUM_First;
void __stdcall EventPrepareMithril(Dword par1)
{
  __asm    mov   eax,par1
  __asm    push  edi
  __asm    mov   EMUM_Ep,edi
  __asm    push  eax
  __asm    mov   eax,0x404130
  __asm    call  eax
  __asm    pop   edi
}
int EventMakeUpMithril(void)
{
  __asm    mov   eax,EMUM_Ep
  __asm    push  edx
  __asm    mov   edx,[eax+0x78]
  __asm    mov   EMUM_First,edx
  __asm    movsx edx,word ptr[eax+0x5E]
  __asm    cmp   edx,-1
  __asm    jne  _Ok
  __asm    xor   edx,edx
_Ok:
  __asm    mov   [eax+0x78],edx
  __asm    movsx edx,word ptr[eax+0x5C]
  __asm    mov   [eax+0x5C],edx
  __asm    pop   edx
  __asm    add   eax,0x5C
  __asm    mov   IDummy,eax
  return IDummy;
}
void __stdcall EventERM(_Hero_ *Hp,_MapItem_ *MIp,Dword MixPos,Dword _n1)
{ // ecx= -> advManager
//  Dword LEpo;
  Dword AdvMan;
  _ECX(AdvMan);
  #include "templ.h"
  __asm{
    pusha
//    mov    eax,MIp
//    mov    esi,AdvMan
//    mov    eax,[eax]
//    and    eax,0x3FF // ����� �������
//    lea    ecx,[eax+8*eax]
//    lea    eax,[eax+2*ecx]
//    lea    edx,[eax+2*eax]
//    mov    eax,[esi+0x5C]
//    mov    ecx,[eax+0x54]
//    lea    eax,[ecx+4*edx]
  }
//  LEpo=_EAX;
//  pointer=LEpo;
  ERM_GM_ai=-1;
  ERM_HeroStr=Hp;
  MixedPos(&ERM_PosX,&ERM_PosY,&ERM_PosL,MixPos);
  pointer=MixPos&0x07FF03FF;
  pointer|=0x20000000;
  ProcessERM();
  Dword setup=MIp->SetUp; Word otype=MIp->OType;
  if(otype==0x22){ // ����� "�����" ��� ������������
    _Hero_ *hp=GetHeroStr(setup);
    MIp->SetUp=hp->PlSetUp; MIp->OType=(Word)hp->PlOType;
  }
  EMUM_Ep=0;
  __asm{
    push  _n1
    push   MixPos
    push   MIp
    push   Hp
    mov    ecx,AdvMan
    mov    eax,0x4A0B40
    call   eax
  }
  if(EMUM_Ep!=0){ // ���� ��������� � ������� - �����������
    __asm    mov   eax,EMUM_Ep
    __asm    mov   ecx,[eax+0x78]
    __asm    mov   [eax+0x5E],cx
    __asm    mov   ecx,EMUM_First
    __asm    mov   [eax+0x78],ecx
  }
  if(otype==0x22){ // ����� "�����" ��� ������������
    MIp->SetUp=setup; MIp->OType=otype;
  }
  pointer=MixPos&0x07FF03FF;
  pointer|=0x28000000;
  ProcessERM();
  __asm{
    popa
  }
  RETURNV
}
__declspec( naked ) void GlobalEvent(void)
{
  __asm push eax;
  __asm mov  eax,[esp+8];
  __asm mov  pointer,eax;
  __asm mov   eax,-1
  __asm mov   ERM_GM_ai,eax
  __asm mov   eax,0
  __asm mov   ERM_HeroStr,eax
  __asm pop  eax
  __asm pusha;
  ProcessERM();
  pointer=Callers[3].forig;
  __asm popa;
  __asm jmp dword ptr [pointer]
}

void RunTimer(int Owner)
{
  #include "templ.h"
  int  i,day=GetCurDate();
  int  del;
  Word msk;
  msk=(Word)(1<<Owner);
  for(i=0;i<100;i++){
    if(ERMTimer[i].Owners==0) continue;
    if((ERMTimer[i].Owners&msk)==0) continue;
    if(ERMTimer[i].FirstDay>day) continue;
    if(ERMTimer[i].LastDay<day) continue;
    del=day-ERMTimer[i].FirstDay;
    if((del%ERMTimer[i].Period)!=0) continue;
    Dword oldpo=pointer;
    ERM_GM_ai=!IsAI(Owner);
    pointer=i+30000; // ��������
    ProcessERM();
    pointer=oldpo;
  }
  RETURNV
}
/////// Hint //////////
int CheckObjHint(_MapItem_ *Mp,char *Buf,int ThisSquare)
{
  #include "templ.h"
  int   x,y,l,hv,ind,flag;
  Dword mp;
  _ERM_Object_ *op;

/*
  if(((Dword)Mp)<HERNUM){ // �����
    ind=(Dword)Mp;
    hv=ERM_Hero[ind].HintVar;
    if(hv==0) return 0; // �� ������
    if(hv>500){ Error(); return 0; }
    StrCopy(Buf,512,ERM2String(ERMString[hv-1],1,0));
    return 1;
  }
*/
  if(Mp->OType==0x22){ // �����
    if(ThisSquare){ // ����� � ����� �����
      ind=Mp->SetUp;
      hv=ERM_Hero[ind].HintVar;
      if(hv==0) RETURN(0) // �� ������
      if((hv<0)||(hv>32000)){ Error(); RETURN(0) }
      if(hv>1000) StrCopy(Buf,512,ERM2String(StringSet::GetText(hv),1,0));
      else StrCopy(Buf,512,ERM2String(ERMString[hv-1],1,0));
      RETURN(1)
    }
  }
  // ������
  Map2Coord(Mp,&x,&y,&l);
  mp=PosMixed(x,y,l);
  op=FindObj(mp);
// 3.52 +3.56 (���� ������ ������ ��������, �� ���� ����� 0)
  if((op==0)||(op->HintVar==0)){
//    mp=((Mp->OType&0xFFF)<<16)+(Mp->OType&0xFFFF)+0x10000000;
    flag=0;
    if(Mp->OType==0x22){ // ����� ����� �� ����� �������
      int v=*(int *)Mp; _Hero_ *hp=GetHeroStr(v); Mp->OType=(Word)hp->PlOType; flag=1;
    }
    op=FindObjExt(Mp,x,y,l);
    if(flag==1){ Mp->OType=0x22; }
    if(op==0) RETURN(0) // �� �����
  }
// if(op==0) return 0; // �� �����
  hv=op->HintVar;
  if(hv==0) RETURN(0) // �� ������
  if((hv<0)||(hv>32000)){ Error(); RETURN(0) }
  if(hv>1000) StrCopy(Buf,512,ERM2String(StringSet::GetText(hv),1,0));
  else StrCopy(Buf,512,ERM2String(ERMString[hv-1],1,0));
  RETURN(1)
}

_MapItem_ *HC_Map;
Dword __stdcall HintControl0(Dword p3,Dword p2,Dword p1)
{
  __asm{
    push   p1
    push   p2
    push   p3
    mov    eax,0x40AF10
    call   eax
    mov    HC_Map,eax
    mov    DDummy,eax
  }
  return  DDummy;
}
static Dword HC_ECX, HC_ESI, HC_EBX;
void __stdcall HintControl(Dword p3,Dword p2,Dword p1,char *Buf)
{
  _ECX(HC_ECX); 
  _ESI(HC_ESI); 
  _EBX(HC_EBX);
  if(CheckObjHint(/*(_MapItem_ *)HC_EBX*/HC_Map,Buf,0)==0){
    if((HC_Map->OType==63)&&(HC_Map->OSType==0)){ // ��������
      StrCopy(Buf,512,ITxt(194,0,&Strings));
    }
    if(HC_Map->OType==63){
      if((HC_Map->OSType>=10)&&(HC_Map->OSType<=13)){
        StrCopy(Buf,512,ITxt(196,0,&Strings));
      }
    }
    if(HC_Map->OType==101){
      if((HC_Map->OSType>=7)&&(HC_Map->OSType<=10)){
        StrCopy(Buf,512,ITxt(201+HC_Map->OSType-7,0,&Strings));
      }
    }
  }
  __asm{
    mov    eax,p1
    mov    ecx,p2
    mov    edx,p3
    push   Buf
    push   eax
    push   ecx
    push   edx
    mov    esi,HC_ESI
    mov    ecx,HC_ECX
    mov    eax,0x5FF400
    call   eax
  }
}
static Dword *HW_ECX;
static char  *HW_Buf;
void __stdcall HintWindow(Dword *p3,Dword p2,Dword p1)
{
  _ECX(HW_ECX);
  int ret/*,ind*/;
  Dword mixp;
  _MapItem_ *mi,*mi2;
  #include "templ.h"
  if((p3[3]&0x0200)!=0){
    __asm{ 
      mov eax,0x697428; 
      mov HW_Buf,eax; 
    }
    mixp=HW_ECX[0x3A];
    mi=GetMapItem2(mixp);
    if(mi->OType==0x22){ // �����
//      ind=mi->SetUp;
//      ret=CheckObjHint((_MapItem_ *)ind,HW_Buf);
      ret=CheckObjHint(mi,HW_Buf,1);
    }else{ // ������
      __asm{ 
        mov ecx,mi; 
        mov eax,0x4FD0F0; 
        call eax; 
        mov mi2,eax; 
      }
      if(mi2!=0){
        mi=mi2;
      }
      ret=CheckObjHint(mi,HW_Buf,0);
    }
    if(ret){
      Message(HW_Buf,4);
      RETURNV
    }
    if((mi->OType==63)&&(mi->OSType==0)){ // ��������
      Message(ITxt(194,0,&Strings),4);
      RETURNV
    }
    if(mi->OType==63){
      if((mi->OSType>=10)&&(mi->OSType<=13)){
        Message(ITxt(196,0,&Strings),4);
        RETURNV
      }
    }
    if(mi->OType==101){
      if((mi->OSType>=7)&&(mi->OSType<=10)){
        Message(ITxt(201+mi->OSType-7,0,&Strings),4);
        RETURNV
      }
    }
  }
  __asm{
    push   p1
    push   p2
    push   p3
    mov    ecx,HW_ECX
    mov    eax,0x40A530
    call   eax
  }
  RETURNV
}
int AS_CGood[][3]={{12}, {5,1,3},{7,1,3},{9,50,200},{15,1,6},{16,1,6},
                   {17,1,2},{18,1,2},{19,1,2},{20,1,2},{21,100,500},
                   {64,1,4},{65,100,500}};
int AS_CBad[][3]={{48}, {1,0,0},{2,-1,-1},{3,0,0},{4,100,500},{6,1,3},
                   {8,0,0},{10,100,300},{22,0,0},{23,0,0},{24,0,0},
                   {25,0,0},{26,0,0},{27,0,0},{28,0,0},{29,0,0},
                   {30,0,0},{31,0,0},{32,0,0},{33,0,0},{34,0,0},
                   {35,0,0},{36,0,0},{37,0,0},{38,0,0},{39,0,0},
                   {40,0,0},{41,0,0},{42,0,0},{43,0,0},{44,0,0},
                   {45,0,0},{46,0,0},{47,0,0},{48,0,0},{49,0,0},
                   {50,0,0},{51,0,0},{52,0,0},{53,0,0},{54,0,0},
                   {55,0,0},{56,0,0},{57,0,0},{58,0,0},{59,0,0},
                   {60,0,0},{61,0,0},{62,0,0}};

#define SPHMOVEPOINTS 0x500
void ApplySphinx(int GM_ai,_Hero_ *Hr,_MapItem_ * /*Mi*/)
{
  #include "templ.h"
  int num,val,len,P_n;
  num=Random(0,TXTSphinx.sn-1);
  if(Hr->Movement<SPHMOVEPOINTS){ // ���� ��������� �������� � �����
    if(GM_ai){
      Message(ITxt(18,0,&Strings),1);
      RETURNV
    }
  }
  Hr->Movement-=SPHMOVEPOINTS; if(Hr->Movement<0) Hr->Movement=0;
  if(GM_ai){
    if(SphinxReq(num)) P_n=1; else P_n=0;
  }else{
    P_n=1; // AI
//    Mi->SetUp&=0xFFFFFFFE; // visited
  }
  if(P_n){
    num=AS_CGood[0][0]; num=Random(1,num);
    if(AS_CGood[num][1]==AS_CGood[num][2]) val=AS_CGood[num][1];
    else val=Random(AS_CGood[num][1],AS_CGood[num][2]);
    num=AS_CGood[num][0];
  }else{
    num=AS_CBad[0][0]; num=Random(1,num);
    if(AS_CBad[num][1]==AS_CBad[num][2]) val=AS_CBad[num][1];
    else val=Random(AS_CBad[num][1],AS_CBad[num][2]);
    num=AS_CBad[num][0];
  }
  len=Random(1,7);
  if(AddCurse(num,val,len,2,Hr->Number)){ Error(); RETURNV }
  if(GM_ai){
    if(P_n){
      Message(ITxt(190,0,&Strings),1);
    }else{
      Message(ITxt(191,0,&Strings),1);
    }
  }
  RedrawMap();
  RETURNV
}

void MagicWonder(_Hero_ *hp)
{
  #include "templ.h"
  int    i,j,s[2];
  int    olda,a[2],*dp[2],rnd;
  char   (*sk)[4],*en;
  Byte   (*ar[2])[2];

//  fl=DGET(MWEnabled);
//  if(fl==0) return; // MW �� �������
  sk=ArtSkill;
  for(i=0;i<19;i++){
    if(hp->IArt[i][0]==0x8D) goto _found; // ���� ��
  }
  RETURNV
_found:
  if(i==9){ // ���� 1
    s[0]=0; s[1]=2; ar[0]=Ar0; ar[1]=Ar2;
  }else if(i==10){ // ���� 2
    s[0]=3; s[1]=4; ar[0]=Ar3; ar[1]=Ar4;
  }else if(i==11){ // ���� 3
    s[0]=6; s[1]=7; ar[0]=Ar67; ar[1]=Ar67;
  }else if(i==12){ // ���� 4
    s[0]=5; s[1]=8; ar[0]=Ar5; ar[1]=Ar8;
  }else if(i==18){ // ���� 5
    s[0]=1; s[1]=12; ar[0]=Ar1; ar[1]=ArC;
  }else RETURNV
  dp[0]=hp->IArt[s[0]]; dp[1]=hp->IArt[s[1]];
  a[0]=*dp[0]; a[1]=*dp[1];
  for(j=0;j<2;j++){
    if(a[j]==-1) continue; // ���
    if(a[j]<=0x80){ // �� ���������
      olda=a[j];
//      for(i=0,rnd=0,p=(Dword *)Edi_;i<0xF5;i++) rnd+=p[i];
//      rnd+=DGET(MWRandom); DGET(MWRandom)=rnd;
//      rnd+=(rnd>>16);
//      rnd+=(Byte)(rnd>>8);
//      rnd&=0xFFF;
      rnd=Random(0,0xFFF);
      rnd=rnd%ar[j][0][0];
      for(i=1;ar[i][1]!=0;i++){
        if(rnd>=ar[j][i][0]) break;
      }
      a[j]=ar[j][i-1][1];
      __asm{
        mov  eax,BASE
        mov  eax,[eax]
        add  eax,0x4E2B4
        mov  en,eax
      }
      if(en[a[j]]!=0) RETURNV // ��� ��������
      hp->IArt[s[j]][0]=a[j];
      if(olda==0x80) olda=0;
      if(olda<=0x2C){
        for(i=0;i<4;i++){
          hp->PSkill[i]-=sk[olda][i];
        }
      }
      if(a[j]==0x80) a[j]=0;
      if(a[j]<=0x2C){
        for(i=0;i<4;i++){
          hp->PSkill[i]+=sk[a[j]][i];
        }
      }
    }
  }
  RETURNV
}

static _Hero_ *MQL_hp;
static Dword   MQL_ecx;
static char MQL_MesBuf[30000];
int _MakeQuestLog(void)
{
  #include "templ.h"
  int ind,hero,owner;
  _QuestLog_ *qlp;
  hero=MQL_hp->Number;
  owner=MQL_hp->Owner;
  ind=0; MQL_MesBuf[0]=0;
  if(WoGType){ StrCanc(MQL_MesBuf,30000,MQL_MesBuf,"{�������}\n\n"); }
  else{ StrCanc(MQL_MesBuf,30000,MQL_MesBuf,"{Papyrus}\n\n"); }
  while((qlp=GetQuest(hero,owner,&ind))!=0){
    StrCanc(MQL_MesBuf,30000,MQL_MesBuf,ERM2String(ERMString[qlp->z-1],1,0));
    StrCanc(MQL_MesBuf,30000,MQL_MesBuf,"\n-------------------------------------------\n");
  }
  if(ind!=0){ // ���-�� ����
    if(WoGType){ StrCanc(MQL_MesBuf,30000,MQL_MesBuf,"\n{������} {����������} {QuestLog?}"); }
    else{ StrCanc(MQL_MesBuf,30000,MQL_MesBuf,"\n{Do you want} {to} {see} {the} {QuestLog?}"); }
    RETURN(Request0(MQL_MesBuf))
  }
  RETURN(1)
}

void MakeQuestLog(void)
{
  __asm pusha
  _EAX(MQL_hp); 
  _ECX(MQL_ecx);
  if(_MakeQuestLog()){
    __asm{
      mov   ecx,MQL_ecx
      mov   eax,0x52E910
      call  eax
    }
  }
  __asm popa
}

int   AD_artnum,AD_ecx;
Dword AD_retval;
char  AD_Buf[1024];
void FindArtHint(void)
{
  #include "templ.h"
  int   hv;
  _ERM_Object_ *op;
  __asm{
    mov   eax,AD_artnum
    shl   eax,5
    add   eax,AD_ecx
    add   eax,0x10
    mov   eax,[eax]
    mov   AD_retval,eax
  }
  op=FindObj((5<<8)+AD_artnum+0x10000000);
  if(op==0) RETURNV
  hv=op->HintVar;
  if(hv==0) RETURNV // �� ������
  if((hv<0)||(hv>32000)){ Error(); RETURNV }
  if(hv>1000) StrCopy(AD_Buf,512,ERM2String(StringSet::GetText(hv),1,0));
  else StrCopy(AD_Buf,512,ERM2String(ERMString[hv-1],1,0));
  AD_retval=(Dword)AD_Buf;
  RETURNV
}

Dword ArtifacsDescription(void)
{
  __asm{
    pusha
    mov   AD_artnum,eax
    mov   AD_ecx,ecx
  }
  FindArtHint();
  __asm{
    popa
    mov   eax,AD_retval
    mov   DDummy,eax
  }
  return DDummy;
}

//static int Called=0;
void __stdcall ERMDebug(int,int,int,int,int,int,int,int,int,int)
{
 if(WoG==0) return; // �������������� ������ � WoG
  #include "templ.h"
 if(Request0(ITxt(193,0,&Strings))){ // �������
/*
      asm{
        mov  eax,BASE
        mov  eax,[eax]
        int 3
      }
*/
//    ShowDiplom(0);
//    if(Called==0) WoMoPlace(5,5,0,39);
//    else WoMoMove(5,5-1+Called,0,5,5+Called,0);
//    Called++;
//    MakeWoMo(5,5,0,1);
    Message(MapSavedWoG,1);
    GEr.Show(0,0,0,0,"");
    MError("Test ERM Error Message.");
//    ChooseArt(ERM_HeroStr);
  }
  RETURNV
}

int FOH_Monstr;
int FOH_ret;
int FOH_CanBeUpgraded(void)
{
  #include "templ.h"
  __asm pusha
  __asm mov  FOH_Monstr,ecx
  FOH_ret=-1;
  if((FOH_Monstr>=0)&&(FOH_Monstr<MONNUM)){
    if(MonsterUpgradeTable[FOH_Monstr]==-2) FOH_ret=0;
    if(MonsterUpgradeTable[FOH_Monstr]>=0) FOH_ret=1;
  }
  if(FOH_ret==-1){
    __asm{
      mov    ecx,FOH_Monstr
      mov    eax,0x47AA50
      call   eax
      mov    FOH_ret,eax
    }
  }
  __asm popa
//  __asm mov   eax,FOH_ret
  RETURN(FOH_ret)
}

int FOH_UpgradeTo(void)
{
  #include "templ.h"
  __asm pusha
  __asm mov  FOH_Monstr,ecx
  FOH_ret=-1;
  if((FOH_Monstr>=0)&&(FOH_Monstr<MONNUM)){
    if(MonsterUpgradeTable[FOH_Monstr]==-2) FOH_ret=0;
    else FOH_ret=MonsterUpgradeTable[FOH_Monstr];
  }
  if(FOH_ret==-1){
    __asm{
      mov    ecx,FOH_Monstr
      mov    eax,0x47AAD0
      call   eax
      mov    FOH_ret,eax
    }
  }
  __asm popa
//  __asm mov   eax,FOH_ret
  RETURN(FOH_ret)
}
/////////////////////////////
//00408951 8B4E44         mov    ecx,[esi+44]
//00408954 57             push   edi
//00408955E816A5FFFF     call   H3WOG.00402E70
//0040895A 84C0           test   al,al
//0040895C 0F854F010000   jne    H3WOG.00408AB1
static _MouseStr_ *MC_msp,MC_MouseStr;
static Dword MC_MixPos,MC_Oldpo;
static int MC_x,MC_y,MC_l,MC_Std,MC_changed;
void _MouseClick(int type)
{
  #include "templ.h"
  Copy((Byte *)MC_msp,(Byte *)&MC_MouseStr,sizeof(_MouseStr_));
  MC_changed=0;
  if(MapSmPos(&MC_MouseStr,&MC_MixPos)==1){
    if(MC_MouseStr.Item==0){ MC_MouseStr.Item=37; MC_changed=1; }
  }else{
    if(MC_MouseStr.Item==37){ MC_MouseStr.Item=0; MC_changed=1; }
  }
  MixedPos(&MC_x,&MC_y,&MC_l,MC_MixPos);
  MC_Std=1;
  MC_Oldpo=pointer;
  if(type){ // ����� ����
    pointer=30319;
  }else{ // ������ ����
    pointer=30310;
  }
  ProcessERM();
  pointer=MC_Oldpo;
  if(MC_changed==1){
    if(MC_MouseStr.Item==0) MC_MouseStr.Item=37;
    else{ if(MC_MouseStr.Item==37) MC_MouseStr.Item=0; }
  }
  Copy((Byte *)&MC_MouseStr,(Byte *)MC_msp,sizeof(_MouseStr_));
/*
AnimDlg *dlg=new AnimDlg();
__asm int 3
dlg->BuildDlg();
for(int i=0;i<1000;i++){
  int j=i;
}
delete dlg;
*/
  RETURNV
}

char __stdcall MouseClick(_MouseStr_ *msp)
{
  MC_msp=msp;
  __asm pusha
  _MouseClick(0);
  if(MC_Std==0){ // �� ���� ����������� �������
    __asm{ 
      popa
      mov al,1 
    }
  }else{ // ���� �����������
    __asm{
      popa
      mov    ecx,[esi+0x44]
      push   edi
      mov    eax,0x402E70
      call   eax
    }
  }
  __asm mov CDummy,al
  return CDummy;
}
int __stdcall MouseClick2(int p4,int p3,int p2,int p1)
{
  _EDI(MC_msp);
  __asm pusha
  _MouseClick(1);
  if(MC_Std==0){ // �� ���� ����������� �������
    __asm{ 
      popa; 
      mov eax,1 
    }
  }else{ // ���� �����������
    __asm{
      popa
      push   p1
      push   p2
      push   p3
      push   p4
      mov    eax,0x4099D0
      call   eax
    }
  }
  __asm mov  IDummy,eax
  return IDummy;
}
int __stdcall MouseClick3(int p3,int p2,int p1)
{
  _EDI(MC_msp);
  __asm pusha
  _MouseClick(1);
  if(MC_Std==0){ // �� ���� ����������� �������
    __asm{ 
      popa; 
      mov eax,1 
    }
  }else{ // ���� �����������
    __asm{
      popa
      push   p1
      push   p2
      push   p3
      mov    eax,0x409740
      call   eax
    }
  }
  __asm mov  IDummy,eax
  return IDummy;
}
static int MC_lhp,MC_rhp;
int ERM_MouseClick(char Cmd,int Num,_ToDo_* /*sp*/,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  int v,sind;
  switch(Cmd){
    case 'T': // T$ - ���
      v=MC_MouseStr.Type; if(Apply(&v,4,Mp,0)) break; MC_MouseStr.Type=v; break;
    case 'S': // S$ -
      v=MC_MouseStr.SType; if(Apply(&v,4,Mp,0)) break; MC_MouseStr.SType=v; break;
    case 'I': // I$ -
      v=MC_MouseStr.Item; if(Apply(&v,4,Mp,0)) break; MC_MouseStr.Item=v; break;
    case 'F': // F$ -
      v=MC_MouseStr.Flags; if(Apply(&v,4,Mp,0)) break; MC_MouseStr.Flags=v; break;
    case 'A': // A$/$ -
      if(Num<2){ MError("\"!!CM:A\"-wrong syntax."); RETURN(0) }
      v=MC_MouseStr.Xabs; if(Apply(&v,4,Mp,0)==0) MC_MouseStr.Xabs=v;
      v=MC_MouseStr.Yabs; if(Apply(&v,4,Mp,1)==0) MC_MouseStr.Yabs=v;
      break;
    case 'P': // P$/$/$ -
      if(Num<3){ MError("\"!!CM:P\"-wrong syntax."); RETURN(0) }
      v=MC_x; if(Apply(&v,4,Mp,0)==0){ MError("\"!!CM:P\"-cannot set position."); RETURN(0) }
      v=MC_y; if(Apply(&v,4,Mp,1)==0){ MError("\"!!CM:P\"-cannot set position."); RETURN(0) }
      v=MC_l; if(Apply(&v,4,Mp,2)==0){ MError("\"!!CM:P\"-cannot set position."); RETURN(0) }
      break;
    case 'R': // R$ - ����� ��������� (1) ��� ��� (0)
      v=MC_Std; if(Apply(&v,4,Mp,0)) break; MC_Std=v; break;
    case 'H': // A?$/?$ - ������ ������
      if(Num<2){ MError("\"!!CM:H\"-wrong syntax."); RETURN(0) }
      v=MC_lhp; if(Apply(&v,4,Mp,0)==0){ MError("\"!!CM:H\"-cannot set hero number."); RETURN(0) }
      v=MC_rhp; if(Apply(&v,4,Mp,1)==0){ MError("\"!!CM:H\"-cannot set hero number."); RETURN(0) }
      break;
    case 'D': // D$ - ��� ������� �� ���� ����� ���� ��������
      __asm{
        mov    eax,0x699420
        mov    eax,[eax]
        mov    eax,[eax+0x132D4]
        mov    v,eax
      }
      if(Apply(&v,4,Mp,0)) break;
      __asm{
        mov    eax,0x699420
        mov    eax,[eax]
        mov    ebx,v
        mov    [eax+0x132D4],ebx
      }
      break;
    case 'M': // 3.58 Mz#, M message text
      if(Num!=1){ MError("\"!!CM:M\"-wrong syntax."); RETURN(0) }
      if(Mp->VarI[0].Type!=7){ MError("\"!!CM:\"- not a Z variable."); RETURN(0) }
      sind=GetVarVal(&Mp->VarI[0]);
      if((sind<-10)||(sind==0)||(sind>1000)){ MError("\"!!MC:\"-wrong z (destination) index (-10...-1,1...1000)."); RETURN(0) }
      if(Mp->VarI[0].Check==1){ // ?
      }else{
        if(sind>0) ShowTSHint(ERMString[sind-1]);
        else       ShowTSHint(ERMLString[-sind-1]);
      }
      break;
    default: MError("\"!!CM:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
// ����� ����� � ������
int GetRealItem(Byte *TownMan,_MouseStr_ *MouseStr)
{
  #include "templ.h"
  int retval=MouseStr->Item;
  do{
    if(TownMan==0) break;
    if(retval<0) break;
    if(retval>0x2B) break;
    __asm{
      mov esi, MouseStr
      mov eax, [esi+0x14]
      mov edx, [esi+0x10]
      lea eax, [eax+eax*4]   
      lea ecx, [eax+eax*4] 
      shl ecx, 5 
      add ecx, edx         
      mov edx, [ebx+0x118]
      mov eax, [edx+0x50]
      xor edx, edx 
      mov dx,  [eax+ecx*2]
      dec edx
      mov retval, edx
    }
  }while(0);
  RETURN(retval)
}
static _MouseStr_ *MCT_msp;
static Byte *MCT_TownMan;
static int MCT_Ret;

int _MouseClickTown(void)
{
  #include "templ.h"
  // 3.58f fix click in allied town
  while(1){
    // if click to garrisoned or visiting hero
    if(MCT_msp->Item!=123) break;
    if(MCT_msp->Item==125) break;
    // left mouse click with any Shift/Alt modifier
    if(MCT_msp->Flags&512) break;
    int hi=-1;
    _Hero_ *hp=0;
    _CastleSetup_ *tp;
    __asm  mov   eax,MCT_TownMan
    __asm  mov   eax,[eax+0x38]
    __asm  mov   tp,eax
    if(tp==0) break;
    if(MCT_msp->Item==123) hi=tp->IHero;
    if(MCT_msp->Item==125) hi=tp->VHero;
    if(hi==-1) break;
    hp=GetHeroStr(hi);
    if(hp==0) break;
    if(hp->Owner==CurrentUser()) break;
    // not this owner - disable action
    RETURN(5)
  }
  Copy((Byte *)MCT_msp,(Byte *)&MC_MouseStr,sizeof(_MouseStr_));
  MC_MouseStr.Item=GetRealItem(MCT_TownMan,&MC_MouseStr);
  MC_Std=1;
  MC_Oldpo=pointer;
  pointer=30311; //
  ProcessERM();
  pointer=MC_Oldpo;
  Copy((Byte *)&MC_MouseStr,(Byte *)MCT_msp,sizeof(_MouseStr_));
  if(MC_Std==0){ // �� ���� ����������� �������
    RETURN(5)
  }
  RETURN(MCT_msp->SType-10)
}
int MouseClickTown(void)
{
  __asm pusha
  _ESI(MCT_msp);
  _EBX(MCT_TownMan);
  MCT_Ret=_MouseClickTown();
  __asm popa
  return MCT_Ret;
}

int _MouseOverTown(void)
{
  #include "templ.h"
  Copy((Byte *)MCT_msp,(Byte *)&MC_MouseStr,sizeof(_MouseStr_));
  MC_Std=1;
  MC_Oldpo=pointer;
  pointer=30318; //
  ProcessERM();
  pointer=MC_Oldpo;
  Copy((Byte *)&MC_MouseStr,(Byte *)MCT_msp,sizeof(_MouseStr_));
  RETURN(MC_Std)
}
void __stdcall MouseOverTown(_MouseStr_ *MStr)
{
  __asm{
    mov    ecx,0x69954C
    mov    ecx,[ecx]
    mov    eax,MStr
    push   eax
    mov    eax,0x5C7BA0
    call   eax
  }
  __asm pusha
  MCT_msp=MStr;
  _MouseOverTown();
  __asm popa
}

void _EnterTownHall(int Type)
{
  #include "templ.h"
  MC_Oldpo=pointer;
  pointer=30324+Type; //
  ProcessERM();
  pointer=MC_Oldpo;
  RETURNV
}
void EnterTownHall(void)
{
  __asm pusha
  _EnterTownHall(0);
  __asm popa
  __asm mov   eax,0x5D34D0
  __asm call  eax
  __asm pusha
  _EnterTownHall(1);
  __asm popa
}

int MouseClickHero(_MouseStr_ *msp,_Hero_ *hp)
{
  #include "templ.h"
  Copy((Byte *)msp,(Byte *)&MC_MouseStr,sizeof(_MouseStr_));
  MC_Std=1;
  ERM_HeroStr=hp;
  MC_lhp=hp->Number;
  MC_Oldpo=pointer;
  pointer=30312; //
  ProcessERM();
  pointer=MC_Oldpo;
  Copy((Byte *)&MC_MouseStr,(Byte *)msp,sizeof(_MouseStr_));
  if(MC_Std==0){ // �� ���� ����������� �������
    RETURN(1)
  }
  // 3.58
  int i,n,tp,ind=MC_MouseStr.Item;
  if((ind>=68)&&(ind<=74)){  // ��������� �� ���������
   while(1){
    if(WoG==0) break; // �� WoG
    if(!PL_CentElfDis) break; // Horse Elf disabled
    ind-=68;
    if(MC_MouseStr.Flags&0x200) break; // right mouse click
    if((MC_MouseStr.Flags&0x04)==0) break; // Cntrl
    if(hp==0) break;
    if(IsThis(hp->Owner)==0) break;
    tp=0;
    if(hp->Ct[ind]==15){ // Centaur Captain
      tp=19;
    }
    if(hp->Ct[ind]==19){ // Grand Elf
      tp=15;
    }
    if(tp==0) break;
    for(i=n=0;i<7;i++){
      if(hp->Ct[i]!=tp) continue;
      n+=hp->Cn[i]; // ������� ����� ������
    }
    if(n>hp->Cn[ind]) n=hp->Cn[ind]; // ����� �������
    if(n==0) break;
//    if(Request3Pic(
//    "{Grand} {Elves} and {Centaur} {Captains} are happy to meet each other in your army and want to be together forever...
//    \nDo you agree (Their Experience will be set to 0)?",21,15,21,19,21,192,2)){
    if(Request3Pic(ITxt(234,0,&Strings),21,15,21,19,21,192,2)){
      if(n==hp->Cn[ind]){
        hp->Ct[ind]=192;
        for(i=0;i<7;i++){
          if(n==0) break;
          if(hp->Ct[i]!=tp) continue;
          n-=hp->Cn[i]; // �������� ����� ������
          if(n<0){
            hp->Cn[i]=-n;
            break;
          }
          hp->Ct[i]=-1;
          hp->Cn[i]=0;
        }
      }else{
        hp->Cn[ind]-=n;
        for(i=0;i<7;i++){
          if(hp->Ct[i]!=tp) continue;
          hp->Ct[i]=192;
        }
      }
      RedrawHeroScreen(hp);
      RETURN(1)
    }
    RETURN(0)
   }
  }
  RETURN(0)
}
// ������� �� �����
static _MouseStr_ *MC2H_msp;
static int MC2H_Ret;
static Dword *MC2H_sm;
void _MouseClick2Hero(void)
{
  #include "templ.h"
  Copy((Byte *)MC2H_msp,(Byte *)&MC_MouseStr,sizeof(_MouseStr_));
  MC_Std=1;
//  ERM_HeroStr=hp;
  MC_lhp=((_Hero_ *)MC2H_sm[0x40/4])->Number;
  MC_rhp=((_Hero_ *)MC2H_sm[0x44/4])->Number;
  MC_Oldpo=pointer;
  pointer=30313; //
  ProcessERM();
  pointer=MC_Oldpo;
  Copy((Byte *)&MC_MouseStr,(Byte *)MC2H_msp,sizeof(_MouseStr_));
  if(MC_Std==0){ // �� ���� ����������� �������
    MC2H_Ret=0x0100; // >0xD7
  }else{
    MC2H_Ret=MC2H_msp->Item;
  }
  RETURNV
}

int MouseClick2Hero(void)
{
  _EDI(MC2H_msp);
  _EBX(MC2H_sm);
  __asm  pusha
  _MouseClick2Hero();
  __asm  popa
//__asm  mov    eax,MC2H_Ret
  __asm  xor    edx,edx
  return MC2H_Ret;
}

static _MouseStr_ *MCB_msp;
void _MouseClickBattle(void)
{
  #include "templ.h"
  Copy((Byte *)MCB_msp,(Byte *)&MC_MouseStr,sizeof(_MouseStr_));
  MC_Std=1;
  MC_Oldpo=pointer;
  pointer=30314; //
  ProcessERM();
  pointer=MC_Oldpo;
  Copy((Byte *)&MC_MouseStr,(Byte *)MCB_msp,sizeof(_MouseStr_));
  if(MC_Std==0){ // �� ���� ����������� �������
    MCB_msp->Item=0x07D0; //
  }
  RETURNV
}
void MouseClickBattle(void)
{
  __asm mov    MCB_msp,eax
  __asm pusha
  _MouseClickBattle();
  __asm popa
  __asm mov    ecx,[eax+0x0C]
  __asm test   ch,0x02
}
////////////////////////
// 30317 mouse move over battlefield
void _MouseMoveBattle(void)
{
  #include "templ.h"
  MC_Oldpo=pointer;
  pointer=30317;
  ProcessERM();
  pointer=MC_Oldpo;
  RETURNV
}
void __stdcall MouseMoveBattle(int p3,int p2,int p1) // ecx - also set
{
  __asm pusha
  _MouseMoveBattle();
  __asm popa
  __asm push   p1
  __asm push   p2
  __asm push   p3
  __asm mov    eax,0x4729D0
  __asm call   eax
}

int ERM_MouseMove(char Cmd,int Num,_ToDo_* /*sp*/,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i])
  char *orig=(char *)0x697428;
  int   v,sind;
  switch(Cmd){
    case 'M': // Mz#, M?z# message text
      if(Num!=1){ MError("\"!!MM:M\"-wrong syntax."); RETURN(0) }
      if(Mp->VarI[0].Type!=7){ MError("\"!!MM:\"- not a Z variable."); RETURN(0) }
      sind=GetVarVal(&Mp->VarI[0]);
      if((sind<-10)||(sind==0)||(sind>1000)){ MError("\"!!MM:\"-wrong z (destination) index (-10...-1,1...1000)."); RETURN(0) }
      if(Mp->VarI[0].Check==1){ // ?
        if(sind>0) StrCopy(ERMString[sind-1],512,orig);
        else       StrCopy(ERMLString[-sind-1],512,orig);
      }else{
        if(sind>0) StrCopy(orig,512,ERMString[sind-1]);
        else       StrCopy(orig,512,ERMLString[-sind-1]);
      }
      break;
    case 'S': // Sz# add message text
      if(Num!=1){ MError("\"!!MM:S\"-wrong syntax."); RETURN(0) }
      if(Mp->VarI[0].Type!=7){ MError("\"!!MM:\"- not a Z variable."); RETURN(0) }
      sind=GetVarVal(&Mp->VarI[0]);
      if((sind<-10)||(sind==0)||(sind>1000)){ MError("\"!!MM:\"-wrong z (destination) index (-10...-1,1...1000)."); RETURN(0) }
      if(Mp->VarI[0].Check==1){ // ?
        MError("\"!!MM:S\"- cannot use get or check syntax.");
        RETURN(0)
      }else{
        char *po;
        if(sind>0) po=ERMString[sind-1];
        else       po=ERMLString[-sind-1];
        __asm{
          mov    eax,0x699420
          mov    eax,[eax] // combat manager
          mov    ecx,[eax+0x132FC]
          mov    eax,po
          push   0
          push   1
          push   eax
          mov    eax,0x4729D0
          call   eax
        }
      }
      break;
    case 'D': // D$ - ��� ������� �� ���� ����� ���� ������ ����
      if(Num!=1){ MError("\"!!MM:M\"-wrong syntax."); RETURN(0) }
      __asm{
        mov    eax,0x699420
        mov    eax,[eax]
        mov    eax,[eax+0x132D4]
        mov    v,eax
      }
      if(Apply(&v,4,Mp,0)) break;
      __asm{
        mov    eax,0x699420
        mov    eax,[eax]
        mov    ebx,v
        mov    [eax+0x132D4],ebx
      }
      break;
    default: MError("\"!!MM:\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
/////////////////////////////
static void GameSaveLoadTR(int st){
  #include "templ.h"
  MC_Oldpo=pointer;
  pointer=30360+st;
  ProcessERM();
  pointer=MC_Oldpo;
  RETURNV
}
void GameBeforeSave(void){ GameSaveLoadTR(1); }
void GameAfterLoad(void){ GameSaveLoadTR(0); }

/////////////////////////////
void ClearQuestLog(void)
{
  #include "templ.h"
  int i;
  for(i=0;i<QWESTLOGNUM;i++){
    QuestLog[i].num=0;
    QuestLog[i].num=0;
    QuestLog[i].hero=0;
    QuestLog[i].owner=0;
    QuestLog[i].z=0;
  }
  RETURNV
}
void ClearScriptFile(void)
{
  #include "templ.h"
  int i;
  for(i=0;i<SCRIPTSNUM;i++){
    if(ERMScript[i].Used!=0){ // ��������� ������
      Free(ERMBody[i]);
    }
    ERMScript[i].Used=0;
//    for(j=0;j<63;j++) ERMScript[i].FileName[j]=0;
    ERMScript[i].Size=0;
    ERMBody[i]=0;
  }
  RETURNV
}
/////////////////////////////
static _Hero_ *ART_hp;
static int     ART_art;
static int     ART_pos;
static Dword   ART_Oldpo;
void ArtifactOnOff(int ONoff)
{
  #include "templ.h"
  int oldx=ERM_PosX,oldy=ERM_PosY,oldl=ERM_PosL;
  ART_Oldpo=pointer;
  ERM_HeroStr=ART_hp;
  ERM_PosX=ART_art; ERM_PosY=ART_pos;
  pointer=30315+ONoff; //
  ProcessERM();
  ERM_PosX=oldx; ERM_PosY=oldy; ERM_PosL=oldl;
  pointer=ART_Oldpo;
  RETURNV
}
void ArtifactOff(void)
{
  __asm  mov    eax,[edi+8*edx+0x12D]
  __asm  mov    ART_art,eax
  __asm  mov    eax,-1
  __asm  mov    ART_pos,edx
  __asm  mov    ART_hp,edi
  __asm  pusha
  ArtifactOnOff(0);
  __asm  popa
  __asm  mov    [edi+8*edx+0x12D],eax
}
void ArtifactOn(void)
{
  __asm  mov    ART_art,eax
  __asm  mov    ART_pos,esi
  __asm  mov    ART_hp,edi
  __asm  pusha
  ArtifactOnOff(1);
  __asm  popa
  __asm  mov    [edi+8*esi+0x12D],eax
}

int Check4NewSpecPic(int hn)
{
  #include "templ.h"
  if((hn<0)||(hn>=HERNUM)){ MError("Incorrect Hero index in get spec pic."); RETURN(0) }
  // 3.58
  if(HSpecNames[hn].PicNum==0){ // �� ����������� ERM
    // ��������� ���������� �������������
    RETURN(FindHeroSpecIcon(hn))
  }
  RETURN(HSpecNames[hn].PicNum)
}

void SendERMVars(int *len,Byte **buf)
{
  #include "templ.h"
  *len=1000*sizeof(int);
  *buf=(Byte *)&ERMVar2[9000];
  RETURNV
}
void ReceiveERMVars(int len,Byte *buf)
{
  #include "templ.h"
  int i;
  if(len!=(1000*sizeof(int))){ MError("Wrong length of sent ERM vars"); RETURNV }
  for(i=0;i<1000;i++) ERMVar2[9000+i]=((int *)buf)[i];
  RETURNV
}

/////////////
struct _CrChanged_{
  int DayOfSet;
} CrChanged[MONNUM];
void DaylyMonChanged(void)
{
  #include "templ.h"
  int day=GetCurDate();
  for(int i=0;i<MONNUM;i++){
    if(CrChanged[i].DayOfSet==0) continue;
    if((day-CrChanged[i].DayOfSet)>1) CrChanged[i].DayOfSet=0;
  }
  RETURNV
}
void CrIsChanged(int Num)
{
  #include "templ.h"
  if((Num<0)||(Num>=MONNUM)){ MError("Creature index out of range"); RETURNV }
  CrChanged[Num].DayOfSet=GetCurDate();
  RETURNV
}

void ClearCrChanged(void)
{
  for(int i=0;i<MONNUM;i++) CrChanged[i].DayOfSet=0;
}

struct _CrState_{
  int   Index;
  long  Group;     //  0...8,-1 - neutral
  long  SubGroup;  //  0...6,-1 - not available (423D87, 42A0FC)
  Dword Flags;     //  (424354, 42C6C0)
  long  CostRes[7];//  (42B73A)
  long  Fight;     //
  long  AIvalue;   //
  long  Grow;      //  ��������� ���������� �������� ��� �����
  long  HGrow;     //
  long  HitPoints; //
  long  Speed;     //
  long  Attack;    //
  long  Defence;   //
  long  DamageL;   //
  long  DamageH;   //
  long  NShots;    //
  long  HasSpell;  //  - ������� ��� �������
  long  AdvMapL;   //
  long  AdvMapH;   //
} CrState[MONNUM];
void SendCreatures(int *len,Byte **buf)
{
  #include "templ.h"
  int i,j,k;
  for(i=j=0;i<MONNUM;i++){
    if(CrChanged[i].DayOfSet==0) continue;
    CrState[j].Index=i;
    CrState[j].Group=MonTable[i].Group;
    CrState[j].SubGroup=MonTable[i].SubGroup;
    CrState[j].Flags=MonTable[i].Flags;
    for(k=0;k<7;k++) CrState[j].CostRes[k]=MonTable[i].CostRes[k];
    CrState[j].Fight=MonTable[i].Fight;
    CrState[j].AIvalue=MonTable[i].AIvalue;
    CrState[j].Grow=MonTable[i].Grow;
    CrState[j].HGrow=MonTable[i].HGrow;
    CrState[j].HitPoints=MonTable[i].HitPoints;
    CrState[j].Speed=MonTable[i].Speed;
    CrState[j].Attack=MonTable[i].Attack;
    CrState[j].Defence=MonTable[i].Defence;
    CrState[j].DamageL=MonTable[i].DamageL;
    CrState[j].DamageH=MonTable[i].DamageH;
    CrState[j].NShots=MonTable[i].NShots;
    CrState[j].HasSpell=MonTable[i].HasSpell;
    CrState[j].AdvMapL=MonTable[i].AdvMapL;
    CrState[j].AdvMapH=MonTable[i].AdvMapH;
    ++j;
  }
  *buf=(Byte *)CrState;
  *len=j*sizeof(_CrState_);
  RETURNV
}
void ReceiveCreatures(int len,Byte *buf)
{
  #include "templ.h"
  int i,j,k,num;
  num=len/sizeof(_CrState_);
  if(len!=(int)(num*sizeof(_CrState_))){ MError("Wrong length of sent Modified Creatures"); RETURNV };
  if((num<0)||(num>MONNUM)){ MError("Incorrect number of Modified Creature"); RETURNV }
  for(i=0;i<len;i++) ((Byte *)CrState)[i]=buf[i];
  for(j=0;j<num;j++){
    i=CrState[j].Index;
    if((i<0)||(i>MONNUM)){ MError("Incorrect index of Modified Creature"); RETURNV }
    MonTable[i].Group=CrState[j].Group;
    MonTable[i].SubGroup=CrState[j].SubGroup;
    MonTable[i].Flags=CrState[j].Flags;
    for(k=0;k<7;k++) MonTable[i].CostRes[k]=CrState[j].CostRes[k];
    MonTable[i].Fight=CrState[j].Fight;
    MonTable[i].AIvalue=CrState[j].AIvalue;
    MonTable[i].Grow=CrState[j].Grow;
    MonTable[i].HGrow=CrState[j].HGrow;
    MonTable[i].HitPoints=CrState[j].HitPoints;
    MonTable[i].Speed=CrState[j].Speed;
    MonTable[i].Attack=CrState[j].Attack;
    MonTable[i].Defence=CrState[j].Defence;
    MonTable[i].DamageL=CrState[j].DamageL;
    MonTable[i].DamageH=CrState[j].DamageH;
    MonTable[i].NShots=CrState[j].NShots;
    MonTable[i].HasSpell=CrState[j].HasSpell;
    MonTable[i].AdvMapL=CrState[j].AdvMapL;
    MonTable[i].AdvMapH=CrState[j].AdvMapH;
  }
  RETURNV
}

/////////////////////////////
void ResetSSNames(void)
{
  #include "templ.h"
  int i;
  if(SSNameBackStored==0){
    for(i=0;i<sizeof(SSNameBack);i++) ((Byte *)SSNameBack)[i]=((Byte *)SSNAME)[i];
    SSNameBackStored=1;
  }else{ // ����� �����������
    for(i=0;i<sizeof(SSNameBack);i++) ((Byte *)SSNAME)[i]=((Byte *)SSNameBack)[i];
  }
  if(SSDescBackStored==0){
    for(i=0;i<sizeof(SSDescBack);i++) ((Byte *)SSDescBack)[i]=((Byte *)SSDESC)[i];
    SSDescBackStored=1;
  }else{ // ����� �����������
    for(i=0;i<sizeof(SSDescBack);i++) ((Byte *)SSDESC)[i]=((Byte *)SSDescBack)[i];
  }
  if(SSNameDescBackStored==0){
    for(i=0;i<sizeof(SSNameDescBack);i++) ((Byte *)SSNameDescBack)[i]=((Byte *)SSNAMEDESC)[i];
    SSNameDescBackStored=1;
  }else{ // ����� �����������
    for(i=0;i<sizeof(SSNameDescBack);i++) ((Byte *)SSNAMEDESC)[i]=((Byte *)SSNameDescBack)[i];
  }
  RETURNV
}
void ResetMonNames(void)
{
  #include "templ.h"
  int i;
  if(MonNameBackStored==0){
    for(i=0;i<sizeof(MonTable2Back);i++) ((Byte *)MonTable2Back)[i]=((Byte *)MonTable2)[i];
    for(i=0;i<sizeof(MonTable3Back);i++) ((Byte *)MonTable3Back)[i]=((Byte *)MonTable3)[i];
    for(i=0;i<sizeof(MonTable4Back);i++) ((Byte *)MonTable4Back)[i]=((Byte *)MonTable4)[i];
    MonNameBackStored=1;
  }else{ // ����� �����������
    for(i=0;i<sizeof(MonTable2Back);i++) ((Byte *)MonTable2)[i]=((Byte *)MonTable2Back)[i];
    for(i=0;i<sizeof(MonTable3Back);i++) ((Byte *)MonTable3)[i]=((Byte *)MonTable3Back)[i];
    for(i=0;i<sizeof(MonTable4Back);i++) ((Byte *)MonTable4)[i]=((Byte *)MonTable4Back)[i];
  }
  for(i=0;i<MONNUM;i++){
    MonTable[i].NameS=MonTable2[i].NameS;
    MonTable[i].NameP=MonTable3[i].NameP;
    MonTable[i].Spec=MonTable4[i].Spec;
  }
  RETURNV
}

void ResetHSpec(void)
{
  #include "templ.h"
  int i;
  if(HSpecBackStored==0){
    for(i=0;i<sizeof(HSpecBack);i++) ((Byte *)HSpecBack)[i]=((Byte *)HSpecTable)[i];
    HSpecBackStored=1;
  }else{ // ����� �����������
    for(i=0;i<sizeof(HSpecBack);i++) ((Byte *)HSpecTable)[i]=((Byte *)HSpecBack)[i];
  }
  RETURNV
}

int SaveERM(void)
{
  #include "templ.h"
  int i;
////  _Scope_ *sp;
  if(Saver("LERM",4)) RETURN(1)
  if(Saver(ERMVar,sizeof(ERMVar))) RETURN(1)
  if(Saver(ERMVarMacro,sizeof(ERMVarMacro))) RETURN(1)
  if(Saver(ERMVar2,sizeof(ERMVar2))) RETURN(1)
  if(Saver(ERMVar2Macro,sizeof(ERMVar2Macro))) RETURN(1)
  if(Saver(&ERMW,sizeof(ERMW))) RETURN(1)
  if(Saver(ERMVarH,sizeof(ERMVarH))) RETURN(1)
  if(Saver(ERMVarHMacro,sizeof(ERMVarHMacro))) RETURN(1)
  if(Saver(ERMFlags,sizeof(ERMFlags))) RETURN(1)
  if(Saver(ERMFlagsMacro,sizeof(ERMFlagsMacro))) RETURN(1)
  if(Saver(ERM_Object,sizeof(ERM_Object))) RETURN(1)
  if(Saver(ERMString,sizeof(ERMString))) RETURN(1)
  if(Saver(ERMStringMacro,sizeof(ERMStringMacro))) RETURN(1)
  if(Saver(ERMTimer,sizeof(ERMTimer))) RETURN(1)
  if(Saver(&YesERMFile,sizeof(YesERMFile))) RETURN(1)
  if(Saver(ErmTxtName,sizeof(ErmTxtName))) RETURN(1)
  if(Saver(ERM_Hero,sizeof(ERM_Hero))) RETURN(1)
  if(Saver(&NextWeekOf,sizeof(NextWeekOf))) RETURN(1)
  if(Saver(&NextWeekMess,sizeof(NextWeekMess))) RETURN(1)
  if(Saver(&NextMonthOf,sizeof(NextMonthOf))) RETURN(1)
  if(Saver(&NextMonthOfMonster,sizeof(NextMonthOfMonster))) RETURN(1)
  if(Saver(Square,sizeof(Square))) RETURN(1)
  if(Saver(HTable,sizeof(HTable))) RETURN(1)
  if(Saver(QuestLog,sizeof(QuestLog))) RETURN(1)
  _ArtSetUp_ *ap;
  for(i=0;i<ARTNUM;i++){
    ap=&GetArtBase()[i];
    if(Saver(&ArtNames[i].NameVar,sizeof(int))) RETURN(1)
    if(Saver(&ap->Cost,sizeof(Dword))) RETURN(1)
    if(Saver(&ap->Position,sizeof(int))) RETURN(1)
    if(Saver(&ap->Type,sizeof(int))) RETURN(1)
    if(Saver(&ArtNames[i].DescVar,sizeof(int))) RETURN(1)
    if(Saver(&ap->SuperN,sizeof(int))) RETURN(1)
    if(Saver(&ap->PartOfSuperN,sizeof(int))) RETURN(1)
    if(Saver(&ap->Disable,sizeof(Byte))) RETURN(1)
    if(Saver(&ap->NewSpell,sizeof(Byte))) RETURN(1)
  }
  if(Saver(MonsterUpgradeTable,sizeof(MonsterUpgradeTable))) RETURN(1)
  if(Saver(ERMScript,sizeof(ERMScript))) RETURN(1)
  for(i=0;i<SCRIPTSNUM;i++){
    if(ERMScript[i].Used==0) continue;
    if(Saver(ERMBody[i],ERMScript[i].Size)) RETURN(1)
  }
  if(Saver(&PL_ExtDwellStd,sizeof(PL_ExtDwellStd))) RETURN(1)
  if(Saver(&EnableMithrill,sizeof(EnableMithrill))) RETURN(1)
  if(Saver(EnableChest,sizeof(EnableChest))) RETURN(1)
  if(Saver(MithrillVal,sizeof(MithrillVal))) RETURN(1)
  // ���������� ���� ������ �������� �����
  if(Saver(&PL_WoGOptions,sizeof(PL_WoGOptions)/2)) RETURN(1)
  if(Saver(SSAllNames,sizeof(SSAllNames))) RETURN(1)
  if(Saver(MonNames,sizeof(MonNames))) RETURN(1)
  // ��������� ������ ������������, �� �� �� ��������
  for(i=0;i<HERNUM;i++){
    if(Saver((Byte *)&HSpecTable[i],0x1C)) RETURN(1)
  }
  if(Saver(HSpecNames,sizeof(HSpecNames))) RETURN(1)
  if(Saver(Square2,sizeof(Square2))) RETURN(1)
  if(StringSet::Save()) RETURN(1)
// 3.58
  if(Saver(&AI_Delay,sizeof(AI_Delay))) RETURN(1)
  if(Saver(&AutoSaveFlag,sizeof(AutoSaveFlag))) RETURN(1)
////  v=CalculateScopes();
////  if(Saver(&v,sizeof(v))) return 1;
////  for(i=0;i<v;i++){
////    sp=GetScopeNum(i);
////    if(sp==0){ MError("Cannot find a scope (internal)."); return 1; }
////    if(Saver(&sp->Number,sizeof(sp->Number))) return 1;
////    if(Saver(&sp->Var[0],sizeof(sp->Var))) return 1;
////    if(Saver(&sp->String[0][0],sizeof(sp->String))) return 1;
////  }
  RETURN(0)
}

int LoadERM(int ver)
{
  #include "templ.h"
  int i,j,v,ArtNum,MonNum,Size;
////  _Scope_ *sp;
  char buf[4]; if(Loader(buf,4)) RETURN(1)
  if(buf[0]!='L'||buf[1]!='E'||buf[2]!='R'||buf[3]!='M')
      {MError("LoadERM cannot start loading"); RETURN(1)}
  if(Loader(ERMVar,sizeof(ERMVar))) RETURN(1)
  if(Loader(ERMVarMacro,sizeof(ERMVarMacro))) RETURN(1)
  if(Loader(ERMVar2,sizeof(ERMVar2))) RETURN(1)
  if(Loader(ERMVar2Macro,sizeof(ERMVar2Macro))) RETURN(1)
  if(Loader(&ERMW,sizeof(ERMW))) RETURN(1)
  if(Loader(ERMVarH,sizeof(ERMVarH))) RETURN(1)
  if(Loader(ERMVarHMacro,sizeof(ERMVarHMacro))) RETURN(1)
  if(Loader(ERMFlags,sizeof(ERMFlags))) RETURN(1)
  if(Loader(ERMFlagsMacro,sizeof(ERMFlagsMacro))) RETURN(1)
  if(Loader(ERM_Object,sizeof(ERM_Object))) RETURN(1)
  if(Loader(ERMString,sizeof(ERMString))) RETURN(1)
  if(Loader(ERMStringMacro,sizeof(ERMStringMacro))) RETURN(1)
  if(Loader(ERMTimer,sizeof(ERMTimer))) RETURN(1)
  if(Loader(&YesERMFile,sizeof(YesERMFile))) RETURN(1)
  if(Loader(ErmTxtName,sizeof(ErmTxtName))) RETURN(1)
  if(Loader(ERM_Hero,sizeof(ERM_Hero))) RETURN(1)
  if(LoadERMTXT(0)) RETURN(1)
  if(Loader(&NextWeekOf,sizeof(NextWeekOf))) RETURN(1)
  if(Loader(&NextWeekMess,sizeof(NextWeekMess))) RETURN(1)
  if(Loader(&NextMonthOf,sizeof(NextMonthOf))) RETURN(1)
  if(Loader(&NextMonthOfMonster,sizeof(NextMonthOfMonster))) RETURN(1)
  if(Loader(Square,sizeof(Square))) RETURN(1)
  _HeroInfo_ *hp;
  for(i=0;i<(HERNUM+8);i++){
    hp=&HTable[i];
    if(Loader(&hp->Enabled,sizeof(long))) RETURN(1)
    for(j=0;j<8;j++)
      if(Loader(&hp->_u1[j],sizeof(long))) RETURN(1)
    if(Loader(&hp->ArmyType[0],sizeof(long))) RETURN(1)
    if(Loader(&hp->ArmyType[1],sizeof(long))) RETURN(1)
    if(Loader(&hp->ArmyType[2],sizeof(long))) RETURN(1)
    if(Loader(&v,sizeof(long))) RETURN(1) //char  *HPSName;
    if(Loader(&v,sizeof(long))) RETURN(1) //char  *HPLName;
    for(j=0;j<8;j++)
      if(Loader(&hp->_u2[j],sizeof(Byte))) RETURN(1)
    if(Loader(&v,sizeof(long))) RETURN(1) //char  *Name;
    if(Loader(&hp->ArmyNum[0][0],sizeof(long))) RETURN(1)
    if(Loader(&hp->ArmyNum[0][1],sizeof(long))) RETURN(1)
    if(Loader(&hp->ArmyNum[1][0],sizeof(long))) RETURN(1)
    if(Loader(&hp->ArmyNum[1][1],sizeof(long))) RETURN(1)
    if(Loader(&hp->ArmyNum[2][0],sizeof(long))) RETURN(1)
    if(Loader(&hp->ArmyNum[2][1],sizeof(long))) RETURN(1)
//  if(Loader(HTable,sizeof(HTable))) return 1;
  }
  RefreshHeroPic();
  if(Loader(QuestLog,sizeof(QuestLog))) RETURN(1)
  _ArtSetUp_ *ap;
  if(ver<9) ArtNum=0x91;
  else if(ver<17) ArtNum=(0x91+10+1);
  else      ArtNum=ARTNUM;
  for(i=0;i<ArtNum;i++){
      ap=&GetArtBase()[i];
      if(Loader(&ArtNames[i].NameVar,sizeof(int))) RETURN(1)
      if(Loader(&ap->Cost,sizeof(Dword))) RETURN(1)
      if(Loader(&ap->Position,sizeof(int))) RETURN(1)
      if(Loader(&ap->Type,sizeof(int))) RETURN(1)
      if(Loader(&ArtNames[i].DescVar,sizeof(int))) RETURN(1)
      if(Loader(&ap->SuperN,sizeof(int))) RETURN(1)
      if(Loader(&ap->PartOfSuperN,sizeof(int))) RETURN(1)
      if(Loader(&ap->Disable,sizeof(Byte))) RETURN(1)
      if(Loader(&ap->NewSpell,sizeof(Byte))) RETURN(1)
      v=ArtNames[i].NameVar;
      if(v!=0){
        if((v<0)||(v>1000)){ MError("Artifact - wrong z var index for Name (1...1000)."); RETURN(1) }
        ap->Name=ERMString[v-1];
      }else{ ap->Name=ArtSetUpBack[i].Name; }
      v=ArtNames[i].DescVar;
      if(v!=0){
        if((v<0)||(v>1000)){ MError("Artifact - wrong z var index for Description (1...1000)."); RETURN(1) }
        ap->Description=ERMString[v-1];
      }else{ ap->Description=ArtSetUpBack[i].Description; }
    }
//    else if(ver<15) Size=(150+9+1+4+4+5+1+9*2)*sizeof(int);
  Size=sizeof(MonsterUpgradeTable);
  if(Loader(MonsterUpgradeTable,Size)) RETURN(1)
  LoadVersion4Scripts=ver;
  ClearScriptFile();
  if(Loader(ERMScript,sizeof(ERMScript))) RETURN(1) 
  for(i=0;i<SCRIPTSNUM;i++){
    if(ERMScript[i].Used==0) continue;
    ERMBody[i]=(char *)Alloc(ERMScript[i].Size);
    if(Loader(ERMBody[i],ERMScript[i].Size)) RETURN(1)
  }
  if(Loader(&PL_ExtDwellStd,sizeof(PL_ExtDwellStd))) RETURN(1)
  if(Loader(&EnableMithrill,sizeof(EnableMithrill))) RETURN(1)
  if(Loader(EnableChest,sizeof(EnableChest))) RETURN(1)
  if(Loader(MithrillVal,sizeof(MithrillVal))) RETURN(1)
  // ��������� ���� �������� �����
  if(Loader(&PL_WoGOptions,sizeof(PL_WoGOptions)/2)) RETURN(1)
  /* ������ ����� �� ���� ��������� !!!!! */
  // ��������� - ������ �������������
  //  EnableWoGDlgEdit=0;

  ResetSSNames();
  if(Loader(SSAllNames,sizeof(SSAllNames))) RETURN(1)
  for(i=0;i<SSNUM;i++){
      for(j=0;j<4;j++){
        v=SSAllNames[i].Var[j];
        if(v!=0){
          if((v<0)||(v>1000)){ MError("Secondary Skill - wrong z var index for Name (1...1000)."); RETURN(1) }
          if(j==0){
            SSNAME[i].Name=ERMString[v-1];
            SSNAMEDESC[i].Name[j]=ERMString[v-1];
          }else{
            SSDESC[i].Name[j-1]=ERMString[v-1];
            SSNAMEDESC[i].Name[j]=ERMString[v-1];
          }
        }
      }
    }
  ResetMonNames();
//    if(ver<15) Size=(150+9+1+4+4+5+1+9*2)*sizeof(_MonNames_);
  Size=sizeof(MonNames);
  if(Loader(MonNames,Size)) RETURN(1)
//    if(ver<15) MonNum=(150+9+1+4+4+5+1+9*2);
  MonNum=MONNUM;
  for(i=0;i<MonNum;i++){
      for(j=0;j<3;j++){
        v=MonNames[i].Var[j];
        if(v!=0){
          if((v<0)||(v>1000)){ MError("Monster - wrong z var index for Name (1...1000)."); RETURN(1) }
          switch(j){
            case 0: // single
              MonTable [i].NameS=ERMString[v-1];
              MonTable2[i].NameS=ERMString[v-1];
              break;
            case 1: // plural
              MonTable [i].NameP=ERMString[v-1];
              MonTable3[i].NameP=ERMString[v-1];
              break;
            case 2: // spec
              MonTable [i].Spec=ERMString[v-1];
              MonTable4[i].Spec=ERMString[v-1];
              break;
          }
        }
      }
    }
  ResetHSpec();
  // �������� ������ ������������, �� �� �� ��������
  for(i=0;i<HERNUM;i++){
    if(Loader((Byte *)&HSpecTable[i],0x1C)) RETURN(1)
  }
  if(Loader(HSpecNames,sizeof(HSpecNames))) RETURN(1)
  for(i=0;i<HERNUM;i++){
      for(j=0;j<3;j++){
        v=HSpecNames[i].Var[j];
        if(v!=0){
          if((v<0)||(v>1000)){ MError("HeroSpec - wrong z var index (1...1000)."); RETURN(1) }
          switch(j){
            case 0: // short
              HSpecTable[i].SpShort=ERMString[v-1];
              break;
            case 1: // full
              HSpecTable[i].SpFull=ERMString[v-1];
              break;
            case 2: // descr
              HSpecTable[i].SpDescr=ERMString[v-1];
              break;
          }
        }
      }
    }
  if(Loader(Square2,sizeof(Square2))) RETURN(1)
  if(StringSet::Load()) RETURN(1)
// 3.58
  if(Loader(&AI_Delay,sizeof(AI_Delay))) RETURN(1)
  SetDelay(AI_Delay);
  if(Loader(&AutoSaveFlag,sizeof(AutoSaveFlag))) RETURN(1)
  SetAutoSave(AutoSaveFlag);
// 3.59
//  __asm int 3
  SOD_CRC(3434345) 
    if(__v!=(SODCRC+3434345)) EXITERS(56437,edx,__v) // RETURNV


////  FreeAllScopes();
////  if(ver>9){
////    if(Loader(&v,sizeof(v))) return 1;
////    for(i=0;i<v;i++){
////      sp=(_Scope_ *)Alloc(sizeof(_Scope_));
////      if(sp==0){ MError("Cannot add a scope (no memory)."); return 1; }
////      if(Loader(&sp->Number,sizeof(sp->Number))) return 1;
////      if(Loader(&sp->Var[0],sizeof(sp->Var))) return 1;
////      if(Loader(&sp->String[0][0],sizeof(sp->String))) return 1;
////      sp->Next=FirstERMScope;
////      FirstERMScope=sp;
////    }
////  }
  RETURN(0)
}

void ResetERM(void)
{
  #include "templ.h"
  YVarInsideFunction=1; // disable wrong y var usage message
  int i,j,k;
  for(i=0;i<20;i++)  { ERMVar[i]=0;   for(j=0;j<8;j++) ERMVarMacro[i][j]=0; }
  for(i=0;i<500;i++) { ERMVar2[i]=0;  for(j=0;j<8;j++) ERMVar2Macro[i][j]=0; }
  for(i=1000;i<10000;i++) { ERMVar2[i]=0;  for(j=0;j<8;j++) ERMVar2Macro[i][j]=0; }
  for(i=0;i<500;i++) { ERMFlags[i]=0; for(j=0;j<8;j++) ERMFlagsMacro[i][j]=0; }
  for(i=0;i<300;i++) { for(j=0;j<512;j++) ERMString[i][j]=0; for(j=0;j<8;j++) ERMStringMacro[i][j]=0; }
  for(i=500;i<1000;i++) { for(j=0;j<512;j++) ERMString[i][j]=0; for(j=0;j<8;j++) ERMStringMacro[i][j]=0; }
  for(i=0;i<10;i++)  { for(j=0;j<512;j++) ERMLString[i][j]=0; }
  for(i=0;i<HERNUM;i++){
    for(j=0;j<50;j++){
      ERMVarH[i][j]=0;
      for(k=0;k<8;k++) ERMVarHMacro[i][j][k]=0;
    }
    for(j=1000;j<200;j++){
      ERMVarH[i][j]=0;
      for(k=0;k<8;k++) ERMVarHMacro[i][j][k]=0;
    }
  }
  for(i=0;i<ERMOBJECTS;i++){
    ERM_Object[i].Used=0;
    ERM_Object[i].HintVar=0;
    for(j=0;j<8;j++){
      ERM_Object[i].Disabled[j]=0;
      ERM_Object[i].AMessage[j][0]=0;
      ERM_Object[i].AMessage[j][1]=0;
    }
    ERM_Object[i].PosMix=0;
  }
  for(i=0;i<HERNUM;i++){
    ERM_Hero[i].HintVar=0;
    for(j=0;j<8;j++){
      ERM_Hero[i].Disabled[j]=0;
    }
  }
  for(i=0;i<16;i++) { ERMVarX[i]=0; }
  for(i=0;i<100;i++){ ERMVarY[i]=0; }
  for(i=0;i<100;i++){ ERMVarYT[i]=0; }
  for(i=0;i<100;i++){ ERMVarF[i]=0; }
  for(i=0;i<100;i++){ ERMVarFT[i]=0; }
  for(i=0;i<100;i++){ ERMTimer[i].Owners=0; }
  for(i=0;i<144;i++){
    for(j=0;j<144;j++){
      for(k=0;k<2;k++){
        Square[i][j][k].Hero=255;
        Square[i][j][k].Owner=-1;
        Square[i][j][k].Number=0;
        Square[i][j][k].NumberT=0;
        Square[i][j][k].NumberS=0;
      }
    }
  }
  ClearQuestLog();
  NextWeekOf=0;
  NextWeekMess=0;
  NextMonthOf=0;
  NextMonthOfMonster=0;
  // ���� ������ ���, �� �������� ���������
  if(HTableBackStored==0){
    for(i=0;i<sizeof(HTable);i++) ((Byte *)HTableBack)[i]=((Byte *)HTable)[i];
    HTableBackStored=1;
  }else{ // ����� �����������
    for(i=0;i<sizeof(HTable);i++) ((Byte *)HTable)[i]=((Byte *)HTableBack)[i];
  }
  for(i=0;i<8;i++){ // ������� ���� �����������
    for(j=0;j<8;j++){
      SetKeyMaster(i,j,0);
    }
  }
  // ��������� ����������
  // ���� ������ ���, �� �������� ���������
  if(ArtSetUpBackStored==0){
    for(i=0;i<sizeof(ArtSetUpBack);i++) ((Byte *)ArtSetUpBack)[i]=((Byte *)GetArtBase())[i];
    ArtSetUpBackStored=1;
  }else{ // ����� �����������
    for(i=0;i<sizeof(ArtSetUpBack);i++) ((Byte *)GetArtBase())[i]=((Byte *)ArtSetUpBack)[i];
  }
  for(i=0;i<ARTNUM;i++){
    ArtNames[i].NameVar=0; // ����� z ���������� (0-������������)
    ArtNames[i].DescVar=0;
  }
  for(i=0;i<MONNUM;i++) MonsterUpgradeTable[i]=-1;
  ClearScriptFile();
//  PL_ExtDwellStd=0;
  EnableMithrill=0;
  for(i=0;i<20;i++) EnableChest[i]=0;
  for(i=0;i<8;i++) MithrillVal[i]=0;
// 3.58
  ResetWoG357();
  // ��������� - ������ �������������
//  EnableWoGDlgEdit=0;

  ResetSSNames();
  for(i=0;i<SSNUM;i++){
    for(j=0;j<4;j++){
      SSAllNames[i].Var[j]=0;
    }
  }
  ResetMonNames();
  for(i=0;i<MONNUM;i++){
    for(j=0;j<3;j++){
      MonNames[i].Var[j]=0;
    }
  }
  ResetHSpec();
  for(i=0;i<HERNUM;i++){
    HSpecNames[i].PicNum=0;
    for(j=0;j<3;j++){
      HSpecNames[i].Var[j]=0;
    }
  }
  char *p=(char *)Square2;
  for(i=0;i<sizeof(Square2);i++) p[i]=0;
  StringSet::Clear();
  AI_Delay=0x1000;
  SetDelay(AI_Delay);
  AutoSaveFlag=1;
  SetAutoSave(AutoSaveFlag);
////  CurrentScope=0;
////  ERMScope=0;
////  FreeAllScopes();
  RETURNV
}
/////////////////// Scope
////_Scope_ *FindScope(Word ScopeNumber)
////{
////  _Scope_ *sp;
////  if(ScopeNumber==0) return 0;
////  sp=FirstERMScope;
////  while(sp!=0){
////    if(sp->Number==ScopeNumber) break;
////    sp=sp->Next;
////  }
////  return sp;
////}
////int AddScope(Word ScopeNumber)
////{
////  int i,j;
////  _Scope_ *sp;
////  if(ScopeNumber==0) return 1;
////  sp=FindScope(ScopeNumber);
////  while(sp!=0) return 0;
////  sp=(_Scope_ *)Alloc(sizeof(_Scope_));
////  if(sp==0){ MError("Cannot add a scope (no memory)."); return 1; }
////  sp->Number=ScopeNumber;
////  sp->Next=FirstERMScope;
////  FirstERMScope=sp;
////  for(i=0;i<1000;i++) sp->Var[i]=0;
////  for(i=0;i<1000;i++){
////    for(j=0;j<512;j++) sp->String[i][j]=0;
////  }
////  return 0;
////}
////void FreeAllScopes(void)
////{
////  _Scope_ *sp,*sp1;
////  sp=FirstERMScope;
////  while(sp!=0){
////    sp1=sp;
////    sp=sp->Next;
////    Free(sp1);
////  }
////  FirstERMScope=0;
////}
////int CalculateScopes(void)
////{
////  int num=0;
////  _Scope_ *sp;
////  sp=FirstERMScope;
////  while(sp!=0){
////    ++num;
////    sp=sp->Next;
////  }
////  return num;
////}
////_Scope_ *GetScopeNum(int SNum)
////{
////  int num=0;
////  _Scope_ *sp;
////  sp=FirstERMScope;
////  while(sp!=0){
////    if(num==SNum) return sp;
////    ++num;
////    sp=sp->Next;
////  }
////  return 0;
////}

static char CE_Ret;
int CheatEnabled(void)
{
  __asm pusha
  __asm mov  eax,0x4CE950
  __asm call eax
  __asm mov  CE_Ret,al
  if(CE_Ret==0){ if(PL_CheatDis) CE_Ret=1; } // 903
  __asm popa
//  __asm mov  al,CE_Ret
  return CE_Ret;
}

static int PCMC_Ecx,PCMC_Ret;
int ParseCheatMenuCommand(void)
{
  __asm pusha
  __asm mov  PCMC_Ecx,ecx
  PCMC_Ret=0;
  if(PL_CheatDis){
    if(PCMC_Ecx==40140){
      __asm{
        mov eax, 0x699650
        mov eax,[eax]
        push 0                            // lParam
        push 0                            // wParam
        push 0x10                         // Msg
        push eax                          // hWnd
        mov  eax,0x63A288
        mov  eax,[eax]
        call eax
//      call ds:PostMessageA                    ; Indirect Call Near Procedure
      }
    }  
  }else{
    __asm{
      mov  ecx,PCMC_Ecx
      mov  eax,0x4F49E0
      call eax
      mov  PCMC_Ret,eax
    }
  }
  __asm popa
//  __asm mov  eax,PCMC_Ret
  return PCMC_Ret;
}

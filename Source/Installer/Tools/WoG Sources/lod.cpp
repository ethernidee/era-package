#include <string.h>
#include <stdio.h>
#include "structs.h"
#include "common.h"
#include "txtfile.h"
#include "string.h"
#include "service.h"
#include "erm.h"
#include "b1.h"
#include "lod.h"

#define __FILENUM__ 19

LodTypes::_Table LodTypes::Table[4][3]={
  {{2,Seq[0][0]},{2,Seq[0][1]},{2,Seq[0][2]}},
  {{3,Seq[1][0]},{3,Seq[1][1]},{3,Seq[1][2]}},
  {{1,Seq[2][0]},{1,Seq[2][1]},{2,Seq[2][2]}},
  {{2,Seq[3][0]},{2,Seq[3][1]},{2,Seq[3][2]}}
};
// 1 def
// 2 txt,pic
// 3 wav
int LodTypes::Seq[4][3][100]={
  {{5,1},{4,0},{1,0}},
  {{7,3,1},{6,2,0},{2,1,0}},
  {{1},{0},{1,0}},
  {{1,3},{0,2},{1,0}}
};

int LastInd=8;
Byte LodTable[LODNUM][0x190];

#define SOD_LOD_ctor(lod,LODFilename) (((int (__fastcall *)(Byte*,int,char *))0x559420)(lod,0,LODFilename))
#define SOD_LOD_dtor(lod,LODFilename) (((int (__fastcall *)(Byte*,int,char *))0x559460)(lod,0,LODFilename))

#define SOD_LOD_load(lod,LODFilename) (((int (__fastcall *)(Byte*,int,char *,int))0x4FAF30)(&lod[4],0,LODFilename,1/*read only*/))
#define SOD_SearchFileFromLOD(lod,FilenameToSearch) (((char (__fastcall *)(Byte*,int,char *))0x4FB100)(&lod[4],0,FilenameToSearch))
#define SOD_LoadFileFromLOD(lod,FilenameToLoad) (((Byte *(__fastcall *)(Byte*,int,char *))0x4FACA0)(&lod[4],0,FilenameToLoad))

#define SOD_BinTree_FindItem(TreeRoot,Name) (((int (__fastcall *)(Dword,int,char *))0x55EE00)(TreeRoot,0,Name))
#define SOD_BinTree_RemoveItem(TreeRoot,Item_po,buf_po) (((int (__fastcall *)(Dword,int,Dword,Dword *))0x55DF20)(TreeRoot,0,Item_po,buf_po))

Lod *Lod::First=0;

Lod::Lod(int location,char *name){
  Ind=-1;
  #include "templ.h"
  Location=location;
  if(name==0){ 
    Name[0]=0; 
    TError("No name for LOD");
    RETURNV
  }
  strncpy(Name,name,31); Name[31]=0;
  Ind=LastInd++;
  if(Ind>=LODNUM){ 
    TError("Too many loaded LODs");
    RETURNV
  }
  memset(LodTable[Ind],0,0x190);
//  void (__fastcall *ctor)(Byte *lodthis,int,char *lodname); *(Dword *)&ctor=0x559420;
//  ctor(LodTable[Ind],0,Name);
  SOD_LOD_ctor(LodTable[Ind],Name);
  FileList.fl=0;
  Next=First;
  First=this;
  int ret=LoadIt();
  if(ret){ 
    char buf[1024];
    sprintf(buf,"Cannot Load LOD file.\nReason : %i\nName : %s\n\nThe game is unstable now!\nPlease fix the problem and run h3WoG.exe again",
      ret,Name);
    TError(buf);
  }
  RETURNV
}

Lod::~Lod(){
  #include "templ.h"
  if(Ind<0) RETURNV
  SOD_LOD_dtor(LodTable[Ind],Name);
  for(int i=0;i<FileList.sn;i++) LodTypes::RemoveItemFromTree(ITxt(i,0,&FileList));
  UnloadTXT(&FileList);
  FileList.fl=0;
  LodTypes::Del4List(Ind);
  Lod *cur=First,*prev=0;
  while(cur!=0){
    if(cur==this){
      if(prev==0) First=Next;
      else prev->Next=Next;
      break;
    }
    prev=cur; cur=Next;
  }
  RETURNV
}

int Lod::LoadIt(void){
  #include "templ.h"
  if(Ind<0) RETURN(1)
  char fullpathname[256];
  strncpy(fullpathname,GetFolder(Location),255); fullpathname[255]=0;
  strncat(fullpathname,Name,255-strlen(fullpathname)); fullpathname[255]=0;
  if(SOD_LOD_load(LodTable[Ind],fullpathname)) RETURN(2)
  if(SOD_SearchFileFromLOD(LodTable[Ind],"filelist.txt")==0) RETURN(3)
  Byte *item=0;
  item=SOD_LoadFileFromLOD(LodTable[Ind],"filelist.txt");
  if(item==0) RETURN(4)
  void *mem1=h3new(*(size_t *)&item[0x14]);
  Dword ts[50];
  ts[0/* -34 */]=0; if(mem1!=0) ts[0]=1;
  ts[1/* -30 */]=(Dword)mem1;
  ts[2/* -2C */]=0x641138;
  ts[3/* -28 */]=(Dword)&LodTable[Ind][4];
  __asm{
    mov     eax,item
    mov     edi,[eax+0x14]
    mov     edx,0x641138
    mov     esi,mem1
    push    edi
    push    esi
    lea     ecx,ts[2*4]
    mov     eax,[edx+4]  
    call    eax
  }
  void *mem2=h3new(0x34); if(mem2==0) RETURN(6)
  _FileLoaded_ *filelist=0;
  char *tname="filelist.txt";
  ts[6/* -1C */]=(Dword)mem2;
  __asm{
    mov     esi,mem1
    push    esi               
    mov     eax,item
    mov     edi,[eax+0x14]
    push    edi               
    mov     ebx,tname
    push    ebx               
    mov     ecx,mem2 
    mov     eax,0x5BC260 /*5BBF90*/
    call    eax
    mov     filelist,eax
  }
  if(ts[0]){ h3delete(mem1); }
  if(filelist==0) RETURN(7)
  FileList.fl=filelist;
  FileList.sn=filelist->Stop-filelist->Start;
//__asm int 3
  for(int i=0;i<FileList.sn;i++) LodTypes::RemoveItemFromTree(ITxt(i,0,&FileList));
  int ret=LodTypes::Add2List(Ind);
  RETURN(ret)
}


int LodTypes::Add2List(int ind){
  #include "templ.h"
  if((ind<0)||(ind>=LODNUM)){ TError("Incorrect LOD index to add"); RETURN(-1); }
  for(int i=0;i<4;i++){
    for(int j=0;j<2;j++){
      int  n=Table[i][j].Num; 
      int *t=Table[i][j].Inds;
      if(n>=LODNUM){ Del4List(ind); TError("Too many LODs"); RETURN(-2); }
      for(int k=99;k>0;k--){ t[k]=t[k-1];}
      t[0]=ind; Table[i][j].Num+=1;
    }
  }
  RETURN(0)  
}
int LodTypes::Del4List(int ind){
  #include "templ.h"
  if((ind<0)||(ind>=LODNUM)){ TError("Incorrect LOD index to del"); RETURN(-3); }
  for(int i=0;i<4;i++){
    for(int j=0;j<2;j++){
      int  n=Table[i][j].Num; 
      int *t=Table[i][j].Inds;
      for(int k=0;k<n;k++){ 
        if(t[k]==ind){ // found
          for(int l=k+1;l<n;l++) t[l-1]=t[l];
          t[n-1]=0;
          Table[i][j].Num-=1;
          break;
        }
      }
    }
  }
  RETURN(0)  
}
void LodTypes::RemoveItemFromTree(char *name){
  #include "templ.h"
//  Dword (__fastcall *FindItemInBinTree)(Dword TreeRoot,int,char *Name); *(Dword *)&FindItemInBinTree=0x55EE00;
//  Dword ret=FindItemInBinTree(0x69E560,0,name);
  Dword ret=SOD_BinTree_FindItem(0x69E560,name);
  if(ret==*(Dword *)(0x69E560+4)) RETURNV
  if(strncmp((char *)(ret+0x0C),name,12)!=0) RETURNV
//  void (__fastcall *RemoveItemFromBinTree)(Dword TreeRoot,int,Dword Item_po,Dword *buf_po); *(Dword *)&RemoveItemFromBinTree=0x55DF20;
  Dword buf=0;
//  RemoveItemFromBinTree(0x69E560,0,ret,&buf);
  SOD_BinTree_RemoveItem(0x69E560,ret,&buf);
  RETURNV
}

//////////////////////////////
int Lod::LoadCustomLOD(int location,char *name){
  #include "templ.h"
  Lod *lp=new Lod(location,name);
  RETURN(lp->Ind);
}

void Lod::UnloadCustomLOD(int ind){
  #include "templ.h"
  Lod *lp=First;
  while(lp!=0){
    if(lp->Ind==ind){ delete lp; break; } 
  }
  RETURNV
}

int ERM_LODs(char Cmd,int Num,_ToDo_* /*sp*/,Mes *Mp)
{
  #include "templ.h"
  switch(Cmd){
    case 'L': // 3.59 L$1 [var to store index]/$2/$3[z var with name]
     { 
      int loc=0,ind=-1;
      Apply(&ind,4,Mp,0);
      char *name="undefined";
      if(Num<3){ MError("\"LD:L\"-wrong syntax"); break; }
      if((Mp->n[2]<-10)||(Mp->n[2]==0)){ MError("\"LD:L\"-wrong z var index (-10...-1,1...1000)."); break; }
      if(Mp->n[2]>1000) name=ERM2String(StringSet::GetText(Mp->n[2]),1,0);
      else if(Mp->n[2]>0) name=ERM2String(ERMString[Mp->n[2]-1],1,0);
      else name=ERM2String(ERMLString[-Mp->n[2]-1],1,0);
      Apply(&loc,4,Mp,1);
      ind=Lod::LoadCustomLOD(loc,name);
      Apply(&ind,4,Mp,0);
      break;
     }
    case 'U': // 3.59 U$1 [loaded lod index]
     {
      int ind=-1;
      Apply(&ind,4,Mp,0);
      Lod::UnloadCustomLOD(ind);
      break;
     }
    default: MError("\"!!LD\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}

///////////////////////////////

int ResetLODs(void){
  // unload extra LODs
  Lod *lod=Lod::First;
  while(lod!=0){
    Lod *item=lod;
    lod=lod->Next;
    delete item;
  }
  LastInd=8;
  Lod::First=0;
  RETURN(0)
}

int LoadLODs(int /*ver*/)
{
  #include "templ.h"
  ResetLODs();
  char buf[4]; if(Loader(buf,4)) RETURN(1)
  if(buf[0]!='L'||buf[1]!='O'||buf[2]!='D'||buf[3]!='0') {MError("LoadNPC cannot start loading"); RETURN(1)}
  int  num,location;
  char name[32];
  if(Loader(&num,sizeof(int))) RETURN(1)
  if(num==0) RETURN(0)
  struct _lod_{ int l; char n[32]; };
  _lod_ *ar=(_lod_ *) new _lod_[num];
  if(ar==0) RETURN(1)
  for(int i=0;i<num;i++){
    if(Loader(&location,sizeof(int))) RETURN(1)
    if(Loader(name,32)) RETURN(1)
    name[31]=0;
    ar[i].l=location; strncpy(ar[i].n,name,32);
  }
  for(int i=0;i<num;i++){
    Lod::LoadCustomLOD(ar[num-i-1].l,ar[num-i-1].n);
  }
  delete ar;
  RETURN(0)
}

int SaveLODs(void){
  #include "templ.h"
  if(Saver("LOD0",4)) RETURN(1)
  int Num=LastInd-8;
  if(Saver(&Num,sizeof(int))) RETURN(1)
  if(Num==0) RETURN(0)
  Lod *lod=Lod::First;
  while(lod!=0){
    Lod *item=lod;
    lod=lod->Next;
    if(Saver(&item->Location,sizeof(int))) RETURN(1)
    if(Saver(&item->Name,32)) RETURN(1)
  }
  RETURN(0)
}

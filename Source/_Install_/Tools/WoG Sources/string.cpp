#include "structs.h"
#include "common.h"
#include "txtfile.h"
#include "b1.h"
//#include "casdem.h"
//#include "service.h"
//#include "herospec.h"
//#include "monsters.h"
//#include "anim.h"
//#include "womo.h"
//#include "sound.h"
//#include "npc.h"
#include "erm.h"
#include "string.h"
#include "prot.h"
#define __FILENUM__ 14
///////////////////////////
String::~String(){ Clear(); }
//  String(String &);
String::String(){Ind=0; Text=0;}
void String::Set(int ind,char *txt){
  STARTNC(__FILENUM__*1000000+__LINE__,txt) //  STARTC("String: Set",txt)
  if(ind<1){ MError("String: Index is below 1, Item is ignored."); }
  if(ind<1000){ // установим и z переменную также
    for(int i=0;i<512;i++){
     ERMString[ind-1][i]=txt[i];
     if(txt[i]==0) break;
    }
    ERMString[ind-1][511]=0;
  }
  Ind=ind;
  Text=txt;
  RETURNV
}
void String::Clear(){ if(Text) Free(Text); Text=0; Ind=0; }
int String::GetInd(){ return Ind; }
char *String::GetText(){ return Text; }

#define MAXSTRINGNUM 50000L
int     StringSet::Num=0;
String  StringSet::Body[MAXSTRINGNUM];
//  StringSet(StringSet &);
//  StringSet();
// ~StringSet();
//  StringSet &operator=(StringSet &);
void StringSet::Clear()
{
  #include "templ.h"
  for(int i=0;i<Num;i++) Body[i].Clear();
  Num=0;
  RETURNV
}
int StringSet::Add(int ind,char *txt){
  STARTNC(__FILENUM__*1000000+__LINE__,txt) //  STARTC("StringSet: Add",txt)
  for(int i=0;i<Num;i++){ if(Body[i].GetInd()==ind){ MError("String: Index is already used."); RETURN(-1) }}
  if(Num<MAXSTRINGNUM){ Body[Num++].Set(ind,txt); }
  else{ MError("String: Too many items."); RETURN(-1) }
  RETURN(0)
}
char *StringSet::GetText(int ind){
  #include "templ.h"
  for(int i=0;i<Num;i++){ if(Body[i].GetInd()==ind) RETURN(Body[i].GetText()) }
  RETURN("String was not found.")
}
int StringSet::Load(){
  #include "templ.h"
  char *txt;
  int ind,l;
  if(Loader(&Num,sizeof(Num))) RETURN(1)
  for(int i=0;i<Num;i++){
    if(Loader(&ind,sizeof(ind))) RETURN(1)
    if(Loader(&l,sizeof(l))) RETURN(1)
    txt=(char *)Alloc(l); if(txt==0) RETURN(1)
    if(Loader(txt,l)) RETURN(1)
    Body[i].Set(ind,txt);
  }
  RETURN(0)
}
int StringSet::Save(){
  #include "templ.h"
  if(Saver(&Num,sizeof(Num))) RETURN(1)
  for(int i=0;i<Num;i++){
    int ind=Body[i].GetInd();
    if(Saver(&ind,sizeof(ind))) RETURN(1)
    int l=StrLen(Body[i].GetText())+1;
    if(Saver(&l,sizeof(l))) RETURN(1)
    if(Saver(Body[i].GetText(),l)) RETURN(1)
  }
  RETURN(0)
}


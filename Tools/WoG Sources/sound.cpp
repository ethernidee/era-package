#include "structs.h"
#include "common.h"
#include "txtfile.h"
//#include "classes.h"
#include "herospec.h"
#include "service.h"
#include "b1.h"
#include "erm.h"
#include "sound.h"
#include "string.h"
#include "prot.h"
#define __FILENUM__ 10

/////////////////////////////////////
// MP3
#define MP3NUM 200
static struct _MP3{
  char *Old;
  char  New[256];
} MP3[MP3NUM]={
// города 0+
{"cstletown"},{"rampart"},{"towertown"},{"infernotown"},{"necrotown"},
{"dungeon"},{"stronghold"},{"fortresstown"},{"elemtown"},
// поверхности 9+
{"dirt"},{"sand"},{"grass"},{"snow"},{"swamp"},{"rough"},{"underground"},{"lava"},{"water"},
// 18+
{"mainmenuwog"},{"mainmenu"},
// 20+
{"aitheme0"},{"aitheme1"},{"aitheme2"},
// 23+
{"bladeabcampaign"},{"bladedbcampaign"},{"bladedscampaign"},
{"bladeflcampaign"},{"bladefwcampaign"},{"bladepfcampaign"},
// 29+
{"campainmusic01"},{"campainmusic02"},{"campainmusic03"},
{"campainmusic04"},{"campainmusic05"},{"campainmusic06"},
{"campainmusic07"},{"campainmusic08"},{"campainmusic09"},
{"campainmusic10"},{"campainmusic11"},
// 40+
{"combat01"},{"combat02"},{"combat03"},{"combat04"},
// 44+
{"eviltheme"},{"goodtheme"},{"neutraltheme"},{"secrettheme"},
// 48
{"looplepr"},
// 49+
{"losecastle"},{"defend castle"},
// 51+
{"losecombat"},{"retreat battle"},{"surrender battle"},{"win battle"},
// 55+
{"lose campain"},{"ultimatelose"},{"win scenario"}
//58 нет
// {"GRASS","..\\maps\\grass1"}
};
static char *MP3Name=0;

void ResetMP3(void)
{
  #include "templ.h"
  for(int i=0;i<MP3NUM;i++){
    for(int j=0;j<256;j++){
      MP3[i].New[j]=0;
    }
  }
  RETURNV
}
int SaveMP3(void)
{
  #include "templ.h"
  if(Saver("LMP3",4)) RETURN(1)
  for(int i=0;i<MP3NUM;i++){
    if(Saver(MP3[i].New,256)) RETURN(1)
  }
  RETURN(0)
}
int LoadMP3(int /*ver*/)
{
  #include "templ.h"
//  if(ver<10){ // не было этого вообще
    ResetMP3();
//    return 0;
//  }
  char buf[4]; if(Loader(buf,4)) RETURN(1)
  if(buf[0]!='L'||buf[1]!='M'||buf[2]!='P'||buf[3]!='3')
    {MError("LoadMP3 cannot start loading"); RETURN(1)}
  WOG_CRC(564) 
    if(__v!=564) EXITERW(835676,edx,__v) // RETURNV
  for(int i=0;i<MP3NUM;i++){
    if(Loader(MP3[i].New,256)) RETURN(1)
  }
  RETURN(0)
}
/*
static char* GetStd(int ind)
{
  if((ind<0)||(ind>58)) ind=0;
  return MP3Names[ind];
}
*/
static int FindThis(char *name)
{
  STARTNC(__FILENUM__*1000000+__LINE__,name) //  STARTC("MP3: Find This",name)
  int   i;
  _MP3 *mp;
  char  buf[256];
  StrCopy(buf,256,name);
  ToLower(buf);
  for(i=0;i<100;i++){
    mp=&MP3[i];
    if(StrCmp(buf,mp->Old)){ // нашли
      RETURN(i)
    }
  }
  RETURN(-1)
}

static void MP3Process(void)
{
  #include "templ.h"
  int i;
  MP3Call(); // пробежим по тригерам
  i=FindThis(MP3Name);
  if(i<0) RETURNV // нет такого - оставляем все как есть
  if(MP3[i].New[0]==0) RETURNV // нет нового установленного - пусть будет старый
  StrCopy(MP3Name,256,MP3[i].New);
  RETURNV
}

__declspec( naked ) void MP3Start(void)
{
  __asm pusha
  __asm mov    eax,0x6A33F4;
  __asm mov    MP3Name,eax
  MP3Process();
  __asm popa
  __asm mov    edi,0x6A33F4
  __asm ret
}

int ERM_MP3(char Cmd,int Num,_ToDo_* /*sp*/,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i]) //  STARTC("Process !!MP command",0)
  int i,ind,vv,v;
  if(WoG==0) RETURN(0) // поддерживается только в WoG
  switch(Cmd){
    case 'C': // C$  играть этот/какой играем
      if(Num!=1){ MError("\"!!MP:C\"-wrong syntax."); RETURN(0) }
      v=FindThis(MP3Name);
      if(Apply(&v,4,Mp,0)) break; // check or get
      if((v<1)||(v>100)){ MError("\"MP:C\"-wrong MP3 table index (1...100)."); RETURN(0) }
      StrCopy(MP3Name,256,MP3[v-1].New);
      break;
    case 'P': // P^text^ , P1/$ играем сейчас
      if(Num==2){ // с переменной
        if(Mp->n[0]==1){
          if((Mp->n[1]<1)||(Mp->n[1]>1000)){ MError("\"MP:P\"-wrong z var index (1...1000)."); RETURN(0) }
          StrCopy(MP3Name,256,ERM2String(ERMString[Mp->n[1]-1],1,0));
        }else{ MError("\"MP:P\"-wrong syntax (P1/$)."); RETURN(0) }
      }else{
        StrCopy(MP3Name,256,ERM2String(&Mp->m.s[Mp->i],0,&i));
        Mp->i+=i;
      }
      break;
    case 'S':    // S#/$ установить/получить файл для #
                 // S#/^text^ установить файл для #
     ind=0;
     if(Apply(&ind,4,Mp,0)){ MError("\"!!MP:S\"-cannot get or check num."); RETURN(0) }
     if((ind<1)||(ind>100)){ MError("\"MP:S\"-wrong MP3 table index (1...100)."); RETURN(0) }
     if(Num==1){ // S# восстановить оригинальный
      StrCopy(MP3[ind-1].New,256,"");
     }else if(Num==2){
      if(Mp->VarI[1].Check==1){ // получить
        Apply(&vv,4,Mp,1);
        if((vv<1)||(vv>1000)){ MError("\"!!MP:S\"-var is out of set (z1...z1000)."); RETURN(0) }
        StrCopy(ERMString[vv-1],256,MP3[ind-1].New);
      }else if(Mp->VarI[1].Check==0){ // установить
        if(Mp->VarI[1].Num!=0){ // переменная
          Apply(&vv,4,Mp,1);
          if((vv<1)||(vv>1000)){ MError("\"!!MP:S\"-var is out of set (z1...z1000)."); RETURN(0) }
          StrCopy(MP3[ind-1].New,256,ERMString[vv-1]);
        }else{           // копируем сам текст
          StrCopy(MP3[ind-1].New,256,ERM2String(&Mp->m.s[Mp->i],0,&vv));
          Mp->i+=vv;
        }
      }else{ MError("\"!!MP:S\"-wrong syntax."); RETURN(0) }
     }else{ MError("\"!!MP:S\"-wrong syntax."); RETURN(0) }
      break;
    default: MError("\"!!MP\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}
// играет MP3 по номеру
//:0059A4E3 8B4508         mov    eax,[ebp+08]
//:0059A4E6 83F802         cmp    eax,00000002
//:0059A4E9 7C16           jl     HEROES3.0059A501
//:0059A4EB 83F80A         cmp    eax,0000000A
//:0059A4EE 7F11           jg     HEROES3.0059A501
//:0059A4F0 8B0485304B6800 mov    eax,[4*eax+00684B30]
//:0059A4F7 6A00           push   00000000
//:0059A4F9 6A00           push   00000000
//:0059A4FB 50             push   eax
//:0059A4FC E8AF0A0000     call   HEROES3.0059AFB0

// вызов проц выше
//:004080A4 33D2           xor    edx,edx
//:004080A6 8A9130836700   mov    dl,[ecx+00678330]
//:004080AC 8B0D14946900   mov    ecx,[00699414]
//:004080B2 52             push   edx
//:004080B3 E828241900     call   HEROES3.0059A4E0

// еще один вызов
//:005C70E2 8B4B38         mov    ecx,[ebx+38]
//:005C70E5 6A01           push   00000001
//:005C70E7 56             push   esi
//:005C70E8 0FBE5104       movsx  edx,byte ptr [ecx+04]
//:005C70EC 8B0D14946900   mov    ecx,[00699414]
//:005C70F2 8B0495CC366400 mov    eax,[4*edx+006436CC]
//:005C70F9 50             push   eax
//:005C70FA E8B13EFDFF     call   HEROES3.0059AFB0
///////////////////////
//#define LOOPSNDNUM 0x46
//static struct _LSND{
//  char  New[256];
//} LSND[LOOPSNDNUM]={
//};
static char *SP_Current;
static void SoundProcess(void)
{
  #include "templ.h"
//  int i;
  SoundCall(); // пробежим по тригерам
//  i=FindThis(MP3Name);
//  if(i<0) RETURNV // нет такого - оставляем все как есть
//  if(MP3[i].New[0]==0) RETURNV // нет нового установленного - пусть будет старый
//  StrCopy(MP3Name,256,MP3[i].New);
  RETURNV
}

Dword SoundManager(void)
{
  __asm   pusha
  _ECX(SP_Current);
  SoundProcess();
  __asm   popa
  __asm   mov   ecx,SP_Current
  __asm   mov   eax,0x6992E0
  __asm   mov   eax,[eax]
  __asm   mov   DDummy,eax
  return DDummy;
}
int ERM_Sound(char Cmd,int/* Num*/,_ToDo_* /*sp*/,Mes *Mp)
{
  STARTNC(__FILENUM__*1000000+__LINE__,&Mp->m.s[Mp->i]) //  STARTC("Process !!SN command",0)
  char *sound=0;
  int vv=0;
  if(WoG==0) RETURN(0) // поддерживается только в WoG
  switch(Cmd){
    case 'S':    // S# получить/установить тек файл в z#
      if(Apply(&vv,4,Mp,0)){ // [check] or get
        if((vv<-10)||(vv==0)||(vv>1000)){ MError("\"!!SN:S\"- z var out of range (-10...-1,1...1000)."); RETURN(0) }
        if(vv>0) StrCopy(ERMString[vv-1],256,SP_Current);
        else     StrCopy(ERMLString[-vv-1],256,SP_Current);
      }else{ // set
        if((vv<-10)||(vv==0)){ MError("\"!!SN:S\"- z var out of range (-10...-1,1...1000)."); RETURN(0) }
        if(vv>1000)   SP_Current=StringSet::GetText(vv);
        else if(vv>0) SP_Current=ERMString[vv-1];
        else          SP_Current=ERMLString[-vv-1];
      }
      break;
    case 'P':    // P# проиграть файл в z#
      Apply(&vv,4,Mp,0);
      if((vv<-10)||(vv==0)){ MError("\"!!SN:S\"- z var out of range (-10...-1,1...1000)."); RETURN(0) }
      if(vv>1000)   sound=StringSet::GetText(vv);
      else if(vv>0) sound=ERMString[vv-1];
      else          sound=ERMLString[-vv-1];
      __asm{
        mov    ecx,sound
        mov    edx,-1
        push   3
        mov    eax,0x59A890
        call   eax
      }
      break;
    default: MError("\"!!SN\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}


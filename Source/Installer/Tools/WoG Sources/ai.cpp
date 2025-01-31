#include "structs.h"
#include "txtfile.h"
#include "service.h"
#include "common.h"
#include "erm.h"
#include "b1.h"
#include "womo.h"
#include "ai.h"
#include "prot.h"
#define __FILENUM__ 11

///////////////////////
/// AI Hero movement
#define AIRUNNUM 1000
/* struct _AIRun_{
  char  Used;
  char  Owner; // -1 -�����
  Word  Flags; // 1-active 2-donotdelafteruse
  short Num;
  short Hero;  // -1 -�����
  Dword MixPos;
};*/
_AIRun_ AIRun[AIRUNNUM];
short WayAI[3][MAXMAPSIZE+2][MAXMAPSIZE+2];
short StpAI[MAXMAPSIZE+2][MAXMAPSIZE+2];
int MapAI(int x,int y,int l)
{
  #include "templ.h"
  _MapItem_ *MIp;
  MIp=GetMapItem(x,y,l);
  if(EmptyPlace(MIp)==0) RETURN(1) else RETURN(0)
}

int FindWayAI(Point &e,Point &s,int ind,int shortway)
{
  #include "templ.h"
  short i,j,k,l,d,v,change,sz;

  for(i=0;i<MAXMAPSIZE;i++){
    for(j=0;j<MAXMAPSIZE;j++){
      WayAI[ind][i+1][j+1]=-1;
    }
  }
  sz=(short)GetMapSize();
  for(i=0;i<sz;i++)
    for(j=0;j<sz;j++)
      if(MapAI(i,j,s.l)) WayAI[ind][i+1][j+1]=-1; else WayAI[ind][i+1][j+1]=0;
  for(i=0;i<MAXMAPSIZE+2;i++){
    WayAI[ind][0][i]=-1; WayAI[ind][MAXMAPSIZE+1][i]=-1; WayAI[ind][i][0]=-1; WayAI[ind][i][MAXMAPSIZE+1]=-1;
  }
  WayAI[ind][s.x+1][s.y+1]=0; //��������� �����
  WayAI[ind][e.x+1][e.y+1]=1; //�������� �����
  if(s==e) RETURN(1)
  do{
    change=0;
    for(i=1;i<MAXMAPSIZE+1;i++)
      for(j=1;j<MAXMAPSIZE+1;j++){
        if(WayAI[ind][i][j]>0){ // ���� ��� ������
          for(k=-1;k<2;k++)
            for(l=-1;l<2;l++){
              if((k==0)&&(l==0)) continue;
              if(WayAI[ind][i+k][j+l]==-1) continue;
              if((k!=0)&&(l!=0)) d=3; // ���������
              else d=2; // ��� ��� ���
              v=(short)(WayAI[ind][i][j]+d);
              if((v<WayAI[ind][i+k][j+l])||(WayAI[ind][i+k][j+l]==0)){
                WayAI[ind][i+k][j+l]=v;
                change=1;
              }
            }
        }
      }
    if(shortway) if(WayAI[ind][s.x+1][s.y+1]!=0) break;
  }while(change!=0); // ���� ���-�� ��������
//  }while(Way[s.x][s.y]==0); // ���� � ��������� ����� �� ������� ���-��
  RETURN(0)
}

Dword MakeAIWay(Point &s,Point &e,int Steps,int ind)
{
  #include "templ.h"
  short i,j,k,l,v,m,n,step;

  for(i=0;i<MAXMAPSIZE+2;i++)
    for(j=0;j<MAXMAPSIZE+2;j++)
      StpAI[i][j]=0;
  step=1;
  i=(short)(s.x+1); j=short(s.y+1);
  m=i; n=j;
  do{
    v=WayAI[ind][i][j];
    for(k=-1;k<2;k++){
      for(l=-1;l<2;l++){
        if((k==0)&&(l==0)) continue;
        if(WayAI[ind][i+k][j+l]<=0) continue;
        if(WayAI[ind][i+k][j+l]<v){
          v=WayAI[ind][i+k][j+l]; m=short(i+k); n=short(j+l);
        }
      }
    }
//    if(v==-1) return;
    StpAI[m][n]=step++; i=m; j=n;
    if(step==Steps){ // ������� - �������
      break;
    }
  }while(((e.x+1)!=m)||((e.y+1)!=n)); // ���� �� �����
  RETURN(PosMixed(m-1,n-1,s.l))
}

int FindStep(int x,int y,int l,int x1,int y1,int l1,Dword *MixPos,int Steps){
  #include "templ.h"
  int i;
  Point s(x,y,l);
  Point e(x1,y1,l1);
  Point t;
  t=e;
  if(l==l1){
//    if(FindWay(s,e)==1) return 2; // ��� �� �����
    if(s==e) RETURN(2)
  }
  if((l!=l1)||(WayAI[0][x+1][y+1]<=0)){ // ��� ����
    s.MakeLine(e);
    for(i=0;i<Point::LineHasPoint;i++){
      if(FindWayAI(s,Point::Line[i],2,1)==1) RETURN(2)
      if(WayAI[2][s.x+1][s.y+1]<=0) continue; // ��� ����
      t=Point::Line[i]; goto l_Ok;
    }
    RETURN(0) // ��� ����
l_Ok:
    *MixPos=MakeAIWay(s,t,Steps,2);
    RETURN(1)
  }
  *MixPos=MakeAIWay(s,t,Steps,0);
  RETURN(1)
}

short AIRFindFree(void){ for(short i=0;i<AIRUNNUM;i++){ if(AIRun[i].Used==0) return i; } return -1; }
short AIRGetThis(short Hero,short Owner,short Num,int dir=0){
  #include "templ.h"
  short i,n,val;
  for(i=0,val=n=-1;i<AIRUNNUM;i++){
    if(AIRun[i].Used==0) continue;
//    if(Hero!=-1){ if(AIRun[i].Hero!=Hero) continue; }
    if(AIRun[i].Hero!=Hero) continue;
//    if(Owner!=-1){ if(AIRun[i].Owner!=Owner) continue; }
    if(AIRun[i].Owner!=Owner) continue;
    switch(dir){
      case 0: // ������
        if(Num!=-1){ if(AIRun[i].Num!=Num) continue; } break;
      case 1: // ����� � 0
        if((val==-1)||(AIRun[i].Num<val)){ val=AIRun[i].Num; n=i; } continue;
      case 2: // ����� � Num
        if(AIRun[i].Num>Num){
          if((val==-1)||(AIRun[i].Num<val)){ val=AIRun[i].Num; n=i; }
        }
        continue;
      case 3: // ����� �� ����������
        if((val==-1)||(AIRun[i].Num>val)){ val=AIRun[i].Num; n=i; }
        continue;
      case 4: // ��������
        if(Num!=-1){ if(AIRun[i].Num!=Num) continue; }
        if((AIRun[i].Flags&1)==0) continue;
        break;
    }
    RETURN(i)
  }
  if(dir) RETURN(n)
  RETURN(-1)
}
short AIRGetAny(short Hero,short Owner,short Num,int dir){
  #include "templ.h"
  short n;
  n=AIRGetThis(Hero,Owner,Num,dir); // ���� ���� ���� ���������������
  if(n>=0) RETURN(n)
  n=AIRGetThis(Hero,-1,Num,dir); // ���� ���� ���� ���������������
  if(n>=0) RETURN(n)
  n=AIRGetThis(-1,Owner,Num,dir); // ���� ���� ���� ���������������
  if(n>=0) RETURN(n)
  n=AIRGetThis(-1,-1,Num,dir); // ���� ���� ���� ���������������
  if(n>=0) RETURN(n)
  RETURN(-1)
}

short AIRGoNextActive(short ind){
  #include "templ.h"
  short n,ih,in,io;
  ih=AIRun[ind].Hero;
  io=AIRun[ind].Owner;
  in=AIRun[ind].Num;
  if(AIRun[ind].Flags&2){ // �� �������
    AIRun[ind].Flags&=~(1); // �� ��������
  }else{
    AIRun[ind].Used=0;   AIRun[ind].Hero=0;   AIRun[ind].Owner=0;
    AIRun[ind].Num=0;    AIRun[ind].Flags=0;  AIRun[ind].MixPos=0;
  }
  n=AIRGetThis(ih,io,in,2);
  if(n>=0){ // ���� ����
    AIRun[n].Flags|=1; RETURN(n)
  }
  n=AIRGetThis(ih,io,-1,1);
  if(n>=0){ // ���� ���������
    AIRun[n].Flags|=1; RETURN(n)
  }
  RETURN(-1)
}

short AIRAddThis(short Hero,short Owner,short Num)
{
  #include "templ.h"
  short n;
  n=AIRGetThis(Hero,Owner,Num);
  if(n>=0){ // ���� ����� ���
    RETURN(n)
  }
  if(Num==0) Num=AIRGetThis(Hero,Owner,Num,3);
  if(Num==-1) RETURN(-1)
  n=AIRFindFree(); if(n<0) RETURN(-1)
  AIRun[n].Used=1;
  AIRun[n].Hero=Hero;
  AIRun[n].Owner=(char)Owner;
  AIRun[n].Num=Num;
  RETURN(n)
}

short AIRDelThis(short Hero,short Owner,short Num)
{
  #include "templ.h"
  short n;
  n=AIRGetThis(Hero,Owner,Num);
  if(n<0) RETURN(-1)
  AIRun[n].Used=0;   AIRun[n].Hero=0;   AIRun[n].Owner=0;
  AIRun[n].Num=0;    AIRun[n].Flags=0;  AIRun[n].MixPos=0; AIRun[n].AIValue=0;
  n=AIRGetThis(Hero,Owner,Num,2);
  if(n<0) RETURN(-1)
  AIRun[n].Flags|=1;
  RETURN(n)
}

void AIRDelAll(short Hero,short Owner)
{
  #include "templ.h"
  short n;
  while((n=AIRGetThis(Hero,Owner,-1,1))>=0){
    AIRun[n].Used=0;   AIRun[n].Hero=0;   AIRun[n].Owner=0;
    AIRun[n].Num=0;    AIRun[n].Flags=0;  AIRun[n].MixPos=0;
  }
  RETURNV
}
// S�����/������/�����/�������/�����
// D�����/������
int ERM_AIRun(char Cmd,int Num,_ToDo_* /*sp*/,Mes *Mp)
{
  #include "templ.h"
  int   h,o,n,ind,chk,x,y,l;
  Dword mixpos,AIval;
  Word  flags;
  if(WoG==0) RETURN(0) // �������������� ������ � WoG
  switch(Cmd){
    case 'S': // S#�����/#������/#�����/$x/$y/$l/$����������/$�����
      if(Num<8){ MError("\"!!AI:S\"-wrong syntax."); RETURN(0) }
      if(Apply(&h,4,Mp,0)){ MError("\"!!AI:S\"-cannot get or check hero."); RETURN(0) }
      if(Apply(&o,4,Mp,1)){ MError("\"!!AI:S\"-cannot get or check owner."); RETURN(0) }
      if(Apply(&n,4,Mp,2)){ MError("\"!!AI:S\"-cannot get or check number."); RETURN(0) }
      ind=AIRGetThis((short)h,(short)o,(short)n);
      if(ind<0){ // ��� ������
        /*mixpos=-1;*/ x=-1; y=-1; l=0;
        flags=0; AIval=500000;
      }else{
        AIval=AIRun[ind].AIValue;
        mixpos=AIRun[ind].MixPos;
        MixedPos(&x,&y,&l,mixpos);
        flags=AIRun[ind].Flags;
      }
      chk=0;
      if(Apply(&x,4,Mp,3)) chk=1; // check or get
      if(Apply(&y,4,Mp,4)) chk=1; // check or get
      if(Apply(&l,4,Mp,5)) chk=1; // check or get
      if(Apply(&AIval,4,Mp,6)) chk=1; // check or get
      if(Apply(&flags,2,Mp,7))  chk=1; // check or get
      if(chk) break;
      if(ind<0){ // ��� ������ - �������
        ind=AIRAddThis((short)h,(short)o,(short)n);
        if(ind<0) break; // �� ����������
      }
      AIRun[ind].AIValue=AIval;
      mixpos=PosMixed(x,y,l);
      AIRun[ind].MixPos=mixpos;
      AIRun[ind].Flags=flags;
      break;
    case 'D': // D#�����/#������/#�����
      if(Num<3){ MError("\"!!AI:D\"-wrong syntax."); RETURN(0) }
      if(Apply(&h,4,Mp,0)){ MError("\"!!AI:D\"-cannot get or check hero."); RETURN(0) }
      if(Apply(&o,4,Mp,1)){ MError("\"!!AI:D\"-cannot get or check owner."); RETURN(0) }
      if(Apply(&n,4,Mp,2)){ MError("\"!!AI:D\"-cannot get or check number."); RETURN(0) }
      if(n<1) AIRDelAll((short)h,(short)o);
      else    AIRDelThis((short)h,(short)o,(short)n);
      break;
    default: MError("\"!!AI\"-wrong command."); RETURN(0)
  }
  RETURN(1)
}

///////////////////////

// ������ ������ �� ����� �� ����/�������
// stype=-1 -����� ������
// num=-1 - ���������
// ����� 0, ���� �� �����
_MapItem_ *SearchForObject(int x,int y,int l,int type,int stype,int num)
{
  #include "templ.h"
 int xi,yi,MapSize,dist,distp,xp,yp,indp;
 _MapItem_  *MIp0,*MIp;
 __asm{
    mov   ecx,BASE
    mov   ecx,[ecx]
    mov   eax,[ecx+0x1FC40]
    mov   MIp0,eax
    mov   eax,[ecx+0x1FC44]
    mov   MapSize,eax
  }
  distp=-1;
  for(yi=0;yi<MapSize;yi++){
    for(xi=0;xi<MapSize;xi++){
      MIp=&MIp0[xi+(yi+l*MapSize)*MapSize];
      if(MIp->OType!=type) continue;
      if((MIp->Attrib&0x10)==0) continue; // �� �. ������
      if(stype!=-1){ if(MIp->OSType!=stype) continue; }
      dist=Abs(xi-x)+Abs(yi-y);
      if(distp==-1){ distp=dist; xp=xi; yp=yi; indp=0; }
      if(num==-1){ // ���������
        if(dist<distp){ distp=dist; xp=xi; yp=yi; }
      }else{ // �� ������
        if(indp==num) RETURN(MIp)
      }
      indp++;
    }
  }
  if(num==-1){
    if(distp==-1) RETURN(0)
    else RETURN(GetMapItem(xp,yp,l))
  }else RETURN(0)
}

int GetDist(Point d,int ind)
{
  #include "templ.h"
  int i,j,shortest=-1,dist[3][3];
//  if(FindWayAI(s,e,ind)==1) return 0; // ��� �� �����
  if(WayAI[ind][d.x+1][d.y+1]==0) RETURN(-1)  // ��� ����
  if(WayAI[ind][d.x+1][d.y+1]<0){ // ����� ������ ������. �����
    for(i=0;i<3;i++){
      for(j=0;j<3;j++){
        dist[i][j]=WayAI[ind][d.x+i][d.y+j];
      }
    }
    for(i=0;i<9;i++){
      if(i==4) continue;
      if(dist[i/3][i%3]>0){
        if(shortest==-1) shortest=dist[i/3][i%3];
        if(shortest>dist[i/3][i%3]) shortest=dist[i/3][i%3];
      }
    }
    if(shortest==-1) RETURN(-1)
    RETURN(shortest+1)
  }else RETURN(WayAI[ind][d.x+1][d.y+1])
}

// ���� ���� � �������
// ����� ���� - ������� ��� 0
// ��������� *dist - ����� ���� �� �������
_MapItem_ *Way2Object(int x,int y,int l,int type,int stype,int num,int *dist)
{
  #include "templ.h"
  int xd,yd,ld;
  Point s(x,y,l),e;
  _MapItem_ *MIp;
  MIp=SearchForObject(x,y,l,type,stype,num); // ������� 2� ����
  if(MIp==0) RETURN((_MapItem_ *)-1) // ��� ������
  Map2Coord(MIp,&xd,&yd,&ld);
  e=Point(xd,yd,ld);
  *dist=GetDist(e,0); if(*dist==-1) RETURN(0) // ��� ����
  RETURN(MIp)
}

// ���� ������� �� ���� �������
// ����� ���� - ������ ��� 0
// ��������� *dist - ����� ���� �� �����
// *newmip - ����� ������� �� ��� �������
_MapItem_ *ToOtherSide(int x,int y,int l,int num,int *dist,_MapItem_ **newmip)
{
  #include "templ.h"
  int xd,yd,ld,xo,yo,lo;
  Point s(x,y,l),e;
  _MapItem_ *MIp,*MIpo;
  MIp=SearchForObject(x,y,l,103,-1,num); // subter gate
  if(MIp==0) RETURN((_MapItem_ *)-1) // ��� ������
  Map2Coord(MIp,&xd,&yd,&ld);
  e=Point(xd,yd,ld);
  *dist=GetDist(e,0); if(*dist==-1) RETURN(0) // ��� ����
  xo=xd; yo=yd; if(ld) lo=0; else lo=1;
  MIpo=SearchForObject(xo,yo,lo,103,-1,-1); // ��������� �� ������ �������
  if(MIpo==0) RETURN(0) // �� ����� �� ��� �������
  *newmip=MIpo;
  RETURN(MIp)
}

// ���� ���� ���� � ����� ���������� �� ������ ������� ����� ST Gate
// �����. ������� ������ ����� �� ���� �������
// *dist ����� ������ ����� ���� �� �������� �����
_MapItem_ *NearestSTway(int x,int y,int l,int xd,int yd,int ld,int *dists)
{
  #include "templ.h"
  int ind,xn,yn,ln,dist,distn,dist0=-1;
  _MapItem_ *MIp,*MIpn,*MIp0;
  Point s,e(xd,yd,ld);
  for(ind=0;;ind++){
    MIp=ToOtherSide(x,y,l,ind,&dist,&MIpn);
    if(MIp==(_MapItem_ *)-1) break; // ��� ���������
    if(MIp==0) continue; // ��� ����
    Map2Coord(MIp,&xn,&yn,&ln);
    s=Point(xn,yn,ln);
    distn=GetDist(s,1);
    if(distn==-1) continue; // ��� ���� �� ������ �������
    if(dist0==-1){ MIp0=MIp; dist0=dist+distn; }
    if(dist0>(dist+distn)){ MIp0=MIp; dist0=dist+distn; }
  }
  if(dist0==-1) RETURN(0) // ��� �������� ����
  *dists=dist0;
  RETURN(MIp0)
}

int Find2M(int x,int y,int l,int stype,int ind,int *dist,Dword *mp,int dir)
{
  #include "templ.h"
  int num,xd,yd,ld;
  Dword **dMIp;
  Point s(x,y,l),e;
  __asm{
    mov    ecx,BASE
    mov    ecx,[ecx]
    mov    eax,stype
    shl    eax,4
    lea    ecx,[eax+ecx+0x4E67C]
    mov    dMIp,ecx
  }
  if(dMIp[1]==0) RETURN(-1)
  num=dMIp[2]-dMIp[1];
  if(num==0) RETURN(-1)
  if((ind<0)||(ind>=num)) RETURN(-1)
  MixedPos(&xd,&yd,&ld,dMIp[1][ind]);
  e=Point(xd,yd,ld);
  *dist=GetDist(e,dir);
  if(*dist==-1) RETURN(-2) // ��� ���� �� ������ �������
  *mp=dMIp[1][ind];
  RETURN(0)
}

// ���� ���� ���� � ��������
// �����. ������� ������� �������� �� ���� �������
// *dist ����� ������ ����� ���� �� �������� �����
_MapItem_ *Nearest2Mway(int x,int y,int l,int xd,int yd,int ld,int *dists)
{
  #include "templ.h"
  int ret,i,j,dist,dist0,dist1,dist2=-1;
  Dword mp,mp0,mp2;
  for(i=0;i<8;i++){
    dist0=-1;
    for(j=0;;j++){
      ret=Find2M(x,y,l,i,j,&dist,&mp,0);
      if(ret==-1) break; // ������ ���
      if(ret==-2) continue; // ��� ����
      if(dist0==-1){ mp0=mp; dist0=dist; }
      if(dist0>dist){ mp0=mp; dist0=dist; }
    }
    if(dist0==-1) continue; // �� ����� ����� ����� ������� �� ������ �����������
    dist1=-1;
    for(j=0;;j++){
      ret=Find2M(xd,yd,ld,i,j,&dist,&mp,1);
      if(ret==-1) break; // ������ ���
      if(ret==-2) continue; // ��� ����
      if(dist1==-1){ mp0=mp; dist1=dist; }
      if(dist1>dist){ mp0=mp; dist1=dist; }
    }
    if(dist1==-1) continue; // �� ����� ����� ����� ������� �� ������ �����������
    if(dist2==-1){ mp2=mp0; dist2=dist0+dist1; }
    if(dist2>(dist0+dist1)){ mp2=mp0; dist2=dist0+dist1; }
  }
  if(dist2==-1) RETURN(0) // ��� �������� ����
  *dists=dist2;
  RETURN(GetMapItem2(mp2))
}

// ���� ���� ���� � ��������
// �����. ������� ������� �������� �� ���� �������
// *dist ����� ������ ����� ���� �� �������� �����
_MapItem_ *Nearest1Mway(int x,int y,int l,int xd,int yd,int ld,int *dists)
{
  #include "templ.h"
  int ind,ind2,dist,dist2,dist0=-1;
  int stype;
  _MapItem_ *MIp,*MIp2,*MIp0;
  Point s,e(xd,yd,ld);
  for(ind=0;;ind++){
    MIp=Way2Object(x,y,l,43,-1,ind,&dist); // ����� ����
    if(MIp==(_MapItem_ *)-1) break; // ��� ���������
    if(MIp==0) continue; // ��� ����
    // �������� ���� �� ����� �� �� �������� �������
    stype=MIp->OSType;
    for(ind2=0;;ind2++){
      MIp2=Way2Object(xd,yd,ld,44,stype,ind2,&dist2); // ���������� �����
      if(MIp2==(_MapItem_ *)-1) break; // ��� ���������
      if(MIp2==0) continue; // ��� ����
//      Map2Coord(MIp2,&xn,&yn,&ln);
//      s=Point(xn,yn,ln);
//      distn=GetDist(s,e);
      if(dist2==-1) continue; // ��� ���� �� ������ �������
      if(dist0==-1){ MIp0=MIp; dist0=dist+dist2; }
      if(dist0>(dist+dist2)){ MIp0=MIp; dist0=dist+dist2; }
    }
  }
  if(dist0==-1) RETURN(0) // ��� �������� ����
  *dists=dist0;
  RETURN(MIp0)
}

_MapItem_ *GetNearestWay(int x,int y,int l,int xd,int yd,int ld,int *dists,int *wtype)
{
  #include "templ.h"
  int YesR,YesST,Yes2M,Yes1M;
  _MapItem_ *MIpR,*MIpST,*MIp2M,*MIp1M;
  Point s(x,y,l),e(xd,yd,ld);
  // ��������� ����
  FindWayAI(s,e,0,0);
  FindWayAI(e,s,1,0);
  // ���� ������ ����
  YesR=GetDist(e,0);
  MIpR=GetMapItem(xd,yd,ld);
  // ���� �������
  MIpST=NearestSTway(x,y,l,xd,yd,ld,&YesST);
  if(MIpST==0) YesST=-1;
  // ���� 2� ���� ���
  MIp2M=Nearest2Mway(x,y,l,xd,yd,ld,&Yes2M);
  if(MIp2M==0) Yes2M=-1;
  // ���� 1� ���� ���
  MIp1M=Nearest1Mway(x,y,l,xd,yd,ld,&Yes1M);
  if(MIp1M==0) Yes1M=-1;

  if(YesR ==0){ *wtype=1; *dists=YesR;  RETURN(MIpR)  }
  if(YesST==0){ *wtype=2; *dists=YesST; RETURN(MIpST) }
  if(Yes2M==0){ *wtype=3; *dists=Yes2M; RETURN(MIp2M) }
  if(Yes1M==0){ *wtype=4; *dists=Yes1M; RETURN(MIp1M) }
  if(YesR <0) YesR =0x10000000;
  if(YesST<0) YesST=0x10000000;
  if(Yes2M<0) Yes2M=0x10000000;
  if(Yes1M<0) Yes1M=0x10000000;
  if((YesR<0x10000000)||(YesST<0x10000000)||(Yes2M<0x10000000)){ // ������������ ����
    if((YesR<YesST)&&(YesR<(Yes2M*2))){ *wtype=1; *dists=YesR;  RETURN(MIpR)  }
    if(YesST<(Yes2M*2)){ *wtype=2; *dists=YesST; RETURN(MIpST) }
    *wtype=3; *dists=Yes2M; RETURN(MIp2M)
  }else{ // �������� ������ ���� ����� ������ �����
    if(Yes1M<0x10000000){ *wtype=4; *dists=Yes1M; RETURN(MIp1M) }
    RETURN(0) // ��� ������ ����
  }
}
////////////////
int SaveAI(void)
{
  #include "templ.h"
  if(Saver("AIRC",4)) RETURN(1)
  if(Saver(AIRun,sizeof(AIRun))) RETURN(1)
  RETURN(0)
}

void ResetAI(void){
  #include "templ.h"
//__asm int 3
//  WOG_CRC(8452453) if(__v!=8452453) EXITER(847662,ecx,__v) // RETURNV
  for(int i=0;i<AIRUNNUM;i++){
    AIRun[i].Used=0;
    AIRun[i].Owner=0; // -1 -�����
    AIRun[i].Flags=0; // 1-active 2-donotdelafteruse
    AIRun[i].Num=0;
    AIRun[i].Hero=0;  // -1 -�����
    AIRun[i].AIValue=0; // ���������� ��� AI
    AIRun[i].MixPos=0;
  }
  RETURNV
}

int LoadAI(int /*ver*/)
{
  #include "templ.h"
  ResetAI();
  char buf[4]; if(Loader(buf,4)) RETURN(1)
  if(buf[0]!='A'||buf[1]!='I'||buf[2]!='R'||buf[3]!='C')
    {MError("LoadAI cannot start loading"); RETURN(1)}
  if(Loader(AIRun,sizeof(AIRun))) RETURN(1)
  RETURN(0)
}


#include "structs.h"
struct _AIRun_{
  char  Used;
  char  Owner; // -1 -�����
  Word  Flags; // 1-active 2-donotdelafteruse
  short Num;
  short Hero;  // -1 -�����
  Dword AIValue; // ���������� ��� AI 
  Dword MixPos;
//  Dword CurMixPos;
};
extern _AIRun_ AIRun[];
short AIRGetAny(short Hero,short Owner,short Num,int dir);
short AIRGoNextActive(short ind);
int ERM_AIRun(char Cmd,int Num,_ToDo_* /*sp*/,Mes *Mp);

_MapItem_ *GetNearestWay(int x,int y,int l,int xd,int yd,int ld,int *dists,int *wtype);
int SaveAI(void);
void ResetAI(void);
int LoadAI(int ver);


extern int NextWeekOf;   // недел€ кого-то
extern int NextWeekMess; // сообщение
extern int NextMonthOf;  // тип мес€ца
extern int NextMonthOfMonster; // монстр *2
extern int MonsterUpgradeTable[MONNUM];
extern int ERMVar2[];
extern int   ERMVarX[16];
extern int   ERMVarY[100];//,ERMVarYT[100];
extern float ERMVarF[100];//,ERMVarFT[100];

extern int ERMVarH[HERNUM][200];
extern char ERMString[][512];
extern char ERMLString[][512];
extern Dword pointer;
extern int ERM_GM_ai;   // кто посетил объект
extern _Hero_ *ERM_HeroStr;  // герой, посетивший объект
//extern int PL_ExtDwellStd; // 1-стандартные двелинги 8-го уровн€
extern int EnableMithrill;
#define SCRIPTSNUM 1102
//extern int PL_TowerStd;
//extern int PL_MLeaveStd;
//extern int PL_NoNPC;
#define PL_WONUM 1000
#define PL_ExtDwellStd PL_WoGOptions[0][0]// 0-стандартные двелинги 8-го уровн€
#define PL_TowerStd    PL_WoGOptions[0][1]
#define PL_MLeaveStd   PL_WoGOptions[0][2]
#define PL_NoNPC       PL_WoGOptions[0][3]
#define PL_NoTownDem   PL_WoGOptions[0][4]
#define PL_ApplyWoG    PL_WoGOptions[0][5]
#define PL_NPC2Hire    PL_WoGOptions[0][6]
#define PL_DwellAccum  PL_WoGOptions[0][7]
#define PL_GuardAccum  PL_WoGOptions[0][8]
#define PL_CentElfDis  PL_WoGOptions[0][9]
#define PL_MLeaveStyle PL_WoGOptions[0][10]
#define PL_CrExpEnable PL_WoGOptions[0][900]
#define PL_CrExpStyle  PL_WoGOptions[0][901]
#define PL_LeaveArt    PL_WoGOptions[0][902]
#define PL_CheatDis    PL_WoGOptions[0][903]
#define PL_ERMErrDis   PL_WoGOptions[0][904]
#define PL_ERMError    PL_WoGOptions[0][905]
#define PL_ExpGainDis  PL_WoGOptions[0][906]
extern int PL_WoGOptions[2][PL_WONUM]; // все опции
extern int EnableChest[];
extern int MithrillVal[8];

int CheckPlace4Hero(_MapItem_ *mip,Dword **stp);
int Apply(void *dp,char size,Mes *mp,char ind);
int NewMesMan(Mes *ms,_AMes_ *ap,int ind);
char *ERM2String(char *mes,int zstr,int *len);
int GetVarVal(VarNum *vnp);
Dword GetDinMixPos(_ToDo_ *sp);
//Dword GetDinMixPos(_ToDo_ *sp,int *number);
extern char  ERMFlags[];
/////////////////////
void ProcessERM(void);
void StepWater(int x,int y,int l);
void PathOverWater(int x1,int y1,int x2,int y2,int l);
//int  ERM2Object(int,Dword,_MapItem_ *,_Hero_ *);
int ERM2Object(int PREpost,int GM_ai,Dword MixPos,_MapItem_ *Mi,_Hero_ *Hr,int,int);
void RunTimer(int Owner);
/////////////////////////////////////////
void FUCall(int n);
int ERM_Universal(char Cmd,int Num,_ToDo_*,Mes *Mp);
Dword __stdcall HintControl0(Dword p3,Dword p2,Dword p1);
void __stdcall HintControl(Dword p3,Dword p2,Dword p1,char *Buf);
void __stdcall HintWindow(Dword *p3,Dword p2,Dword p1);
int WeekOf(void);
int MonthOf(void);
int MonthOf2(void);
void ApplySphinx(int GM_ai,_Hero_ *Hr,_MapItem_ * /*Mi*/);
void MagicWonder(_Hero_ *hp);
void BACall(Dword n,_Hero_ *hp);
void HeroMove(_Hero_ *hp, int NewX, int NewY, int NewL);
void GainLevel(void);
int __stdcall GainLevelSSkill(int Flag1,int PrevSkill);
void MakeQuestLog(void);
Dword ArtifacsDescription(void);
int CalcObjects(int t,int st);
int FindObjects(int t,int st,int i,int *xv,int *yv,int *lv);
void BFCall(void);
void BACall2(Dword,int);
void BACall3(int,int);
void ArtifactOff(void);
void ArtifactOn(void);
void TriggerIP(Dword n);
void COCall(Dword n,_Hero_ *hp);
// 3.58
void AdvMagicManager(void);
void AdvMagicManagerSkill(void);
void PostInstrCall(void);
int CheatEnabled(void);
int ParseCheatMenuCommand(void);
void EnterTownHall(void);
////////////////////////////////////////
void FindERM(void);
int SaveERM(void);
int LoadERM(int ver);
void ResetERM(void);
////////////////////////////////////////
void __stdcall ERMDebug(int,int,int,int,int,int,int,int,int,int);
int FOH_CanBeUpgraded(void);
int FOH_UpgradeTo(void);
char __stdcall MouseClick(_MouseStr_ *msp);
int MouseClickTown(void);
int MouseClickHero(_MouseStr_ *msp,_Hero_ *hp);
int MouseClick2Hero(void);
void MouseClickBattle(void);
_Scope_ *FindScope(Word ScopeNumber);
void FreeAllScopes(void);
int AddScope(Word ScopeNumber);
int CalculateScopes(void);
_Scope_ *GetScopeNum(int SNum);
void __stdcall EventPrepareMithril(Dword par1);
int EventMakeUpMithril(void);
int Check4NewSpecPic(int hn);
void SendERMVars(int *len,Byte **buf);
void ReceiveERMVars(int len,Byte *buf);
void SendCreatures(int *len,Byte **buf);
void ReceiveCreatures(int len,Byte *buf);
void DaylyMonChanged(void);
void CrIsChanged(int Num);
void ClearCrChanged(void);
char *ERM2String2(int ind,char *mes);
// 3.58
void SoundCall(void);
void MRCall(int beforeAFTER);
void MFCall(int CallType);
void __stdcall MouseOverTown(_MouseStr_ *MStr);
int __stdcall  MouseClick2(int p4,int p3,int p2,int p1);
int __stdcall MouseClick3(int p3,int p2,int p1);
void SaveManager(void);
void GameAfterLoad(void);
void GameBeforeSave(void);
void DumpERMVars(char *Text,char *Text2);
int Call_Function(int ind,int *var,int num);
// 3.59
void TLCall(Dword timesec);
void DlgCallBack(int dlg,int item,int action);
char *GetERMtext(Mes *Mp,int ind,int staticonly=0);
char *GetScriptName(int ind);



extern int        WoG;
extern int        WoGatLoad;
extern int        WoGType;
extern TxtFile    Strings;
extern Dword      OriginalCallPointer; // ��������������� ����������
extern _Hero_    *HeroEntered2Object;
struct __Callers{
  long  where;
  long  forig;
  long  fnew;
#ifdef DEBUG
// DEBUG ��� �������
  char *remember;
#endif  
};
extern __Callers Callers[];
extern _HeroSpec_ HSpecTable[];
extern _HeroBios_ HBiosTable[];
extern _MonInfo_ MonTableBack [MONNUM];
extern _MonInfo_  MonTable[MONNUM];
//extern _HeroInfo_ HTable[];
extern _HeroInfo_ HTable[HERNUM+8];
//extern Byte NewMonthMonTypes[];
extern _ArtSetUp_ ArtTable[ARTNUM];
extern _MNameS_  MonTable2[MONNUM];
extern _MNameP_  MonTable3[MONNUM];
extern _MNameSp_ MonTable4[MONNUM];
extern _CArtSetup_ CArtSetup[32];
extern _Spell_ Spells[SPELLNUM];

extern char MapSavedWoG[1024];

extern int NoMoreChecksS;
extern int NoMoreChecksW;

int Saver(void *Po,int Len);
int Loader(void *Po,int Len);
int FindManager(Dword po);
void ResetAll(void);

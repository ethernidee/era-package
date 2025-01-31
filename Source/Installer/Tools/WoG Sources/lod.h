#ifndef __LOD__
#define __LOD__

#include "structs.h"
//void *h3new(size_t sz);

class Lod{
//    Byte LodInternal[0x190];
   int     Ind;
   TxtFile FileList;

    int LoadIt(void);
  public:
   int     Location;
   char    Name[32];
   Lod        *Next;
   static Lod *First;

    Lod(int location,char *name);
    ~Lod();
    static int  LoadCustomLOD(int location,char *name);
    static void UnloadCustomLOD(int ind);
};

#define LODNUM 100
extern int LastInd;
extern Byte LodTable[LODNUM][0x190];

class LodTypes{
  public :
    static struct _Table{ int Num,*Inds; } Table[4][3];
    static int Seq[4][3][100];
    static int Add2List(int ind);
    static int Del4List(int ind);
    static void RemoveItemFromTree(char *name);
};

int ERM_LODs(char Cmd,int Num,_ToDo_*sp,Mes *Mp);
int LoadLODs(int /*ver*/);
int SaveLODs(void);
int ResetLODs(void);
int LoadCustomLOD(int location,char *name);

#endif
///////////////////////////////////////
// �������� TXT ������

struct _TxtString_{
  int    Exist;        // 1=�������� ������, 0=���
  char **Start;
  char **Stop;
  char **End;
};

struct _FileLoaded_{   // ������ 34
  Dword  Fun;          // +00 ������� ��� ������������ ������
  char   FileName[12]; // +04 
  Dword _u1[4];        // +10
  _TxtString_ **Start;  // +20 �� �� ������ ������
  _TxtString_ **Stop;   // +24 �� �� ������ �� ���������
  // +28 -> �� �� ��� ������ ��� ������
  // +2C -> ������ ���������� �����
  // +30 = ������ ������ �����
};

struct TxtFile{
  _FileLoaded_ *fl;
  int sn;
};

/////////////////////////
int LoadTXT(char *name, TxtFile *tf);
void UnloadTXT(TxtFile *tf);
char *ITxt(int StrNum,int ItemNum,TxtFile *tf);


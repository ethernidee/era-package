class String{
  int   Ind;
  char *Text;
  String(String &);
  public:
    String();
   ~String();
    void Set(int ind,char *txt);
    void Clear();
    int GetInd();
    char *GetText();
};
#define MAXSTRINGNUM 50000L
class StringSet{
  static int     Num;
  static String  Body[MAXSTRINGNUM];
  StringSet(StringSet &);
  StringSet();
 ~StringSet();
  StringSet &operator=(StringSet &);
  public:
    static void Clear();
    static int Add(int ind,char *txt);
    static char *GetText(int ind);
    static int Load();
    static int Save();
};

#pragma once
#include <windows.h>
#include <cstdio>
#include <vector>
#include <string>

namespace Era
{
  #pragma pack(push, 1)

  /* Hooks, requires at least 5 bytes */
  const int HOOKTYPE_JUMP   = 0;
  const int HOOKTYPE_CALL   = 1;
  const int HOOKTYPE_BRIDGE = 2;
  
  /*
  Automatically creates safe bridge to high-level function:
    BOOL __stdcall Handler (THookContext* Context);
  Returns "Execute default code" flag. If default code should be executed, it can contain any
  commands except jumps.
  */

  const int OPCODE_JUMP = 0xE9;
  const int OPCODE_CALL = 0xE8;
  const int OPCODE_RET  = 0xC3;

  const int EXEC_DEF_CODE = true;

  /* Erm triggers */
  const int TRIGGER_FU1       = 0;
  const int TRIGGER_FU30000   = 29999;
  const int TRIGGER_TM1       = 30000;
  const int TRIGGER_TM100     = 30099;
  const int TRIGGER_HE0       = 30100;
  const int TRIGGER_HE198     = 30298;
  const int TRIGGER_BA0       = 30300;
  const int TRIGGER_BA1       = 30301;
  const int TRIGGER_BR        = 30302;
  const int TRIGGER_BG0       = 30303;
  const int TRIGGER_BG1       = 30304;
  const int TRIGGER_MW0       = 30305;
  const int TRIGGER_MW1       = 30306;
  const int TRIGGER_MR0       = 30307;
  const int TRIGGER_MR1       = 30308;
  const int TRIGGER_MR2       = 30309;
  const int TRIGGER_CM0       = 30310;
  const int TRIGGER_CM1       = 30311;
  const int TRIGGER_CM2       = 30312;
  const int TRIGGER_CM3       = 30313;
  const int TRIGGER_CM4       = 30314;
  const int TRIGGER_AE0       = 30315;
  const int TRIGGER_AE1       = 30316;
  const int TRIGGER_MM0       = 30317;
  const int TRIGGER_MM1       = 30318;
  const int TRIGGER_CM5       = 30319;
  const int TRIGGER_MP        = 30320;
  const int TRIGGER_SN        = 30321;
  const int TRIGGER_MG0       = 30322;
  const int TRIGGER_MG1       = 30323;
  const int TRIGGER_TH0       = 30324;
  const int TRIGGER_TH1       = 30325;
  const int TRIGGER_IP0       = 30330;
  const int TRIGGER_IP1       = 30331;
  const int TRIGGER_IP2       = 30332;
  const int TRIGGER_IP3       = 30333;
  const int TRIGGER_CO0       = 30340;
  const int TRIGGER_CO1       = 30341;
  const int TRIGGER_CO2       = 30342;
  const int TRIGGER_CO3       = 30343;
  const int TRIGGER_BA50      = 30350;
  const int TRIGGER_BA51      = 30351;
  const int TRIGGER_BA52      = 30352;
  const int TRIGGER_BA53      = 30353;
  const int TRIGGER_GM0       = 30360;
  const int TRIGGER_GM1       = 30361;
  const int TRIGGER_PI        = 30370;
  const int TRIGGER_DL        = 30371;
  const int TRIGGER_HM        = 30400;
  const int TRIGGER_HM0       = 30401;
  const int TRIGGER_HM198     = 30599;
  const int TRIGGER_HL        = 30600;
  const int TRIGGER_HL0       = 30601;
  const int TRIGGER_HL198     = 30799;
  const int TRIGGER_BF        = 30800;
  const int TRIGGER_MF1       = 30801;
  const int TRIGGER_TL0       = 30900;
  const int TRIGGER_TL1       = 30901;
  const int TRIGGER_TL2       = 30902;
  const int TRIGGER_TL3       = 30903;
  const int TRIGGER_TL4       = 30904;
  const int TRIGGER_OB_POS    = (int)(0x10000000);
  const int TRIGGER_LE_POS    = (int)(0x20000000);
  const int TRIGGER_OB_LEAVE  = (int)(0x08000000);

  /* Era Triggers */
  const int TRIGGER_BEFORE_SAVE_GAME          = 77000; // DEPRECATED  
  const int TRIGGER_SAVEGAME_WRITE            = 77001;
  const int TRIGGER_SAVEGAME_READ             = 77002;
  const int TRIGGER_KEYPRESS                  = 77003;
  const int TRIGGER_OPEN_HEROSCREEN           = 77004;
  const int TRIGGER_CLOSE_HEROSCREEN          = 77005;
  const int TRIGGER_STACK_OBTAINS_TURN        = 77006;
  const int TRIGGER_REGENERATE_PHASE          = 77007;
  const int TRIGGER_AFTER_SAVE_GAME           = 77008;
  const int TRIGGER_SKEY_SAVEDIALOG           = 77009; // DEPRECATED  
  const int TRIGGER_HEROESMEET                = 77010; // DEPRECATED
  const int TRIGGER_BEFOREHEROINTERACT        = 77010;
  const int TRIGGER_AFTERHEROINTERACT         = 77011;
  const int TRIGGER_ONSTACKTOSTACKDAMAGE      = 77012;
  const int TRIGGER_ONAICALCSTACKATTACKEFFECT = 77013;
  const int TRIGGER_ONCHAT                    = 77014;

  struct THookContext
  {
    int EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX;
    int RetAddr;
  };

  typedef BOOL (__stdcall *THookHandler) (THookContext *Context);

  struct TEvent
  {
    char* Name;
    void* Data;
    int   DataSize;
  };

  typedef int TEventParams[16];
  typedef void (__stdcall *TEventHandler) (TEvent* Event);

  typedef char  TErmZVar[512];


  /* WoG vars */
  int*      v = (int*)      0x887664; // 1..10000
  TErmZVar* z = (TErmZVar*) 0x9271E8; // 1..1000
  int*      y = (int*)      0xA48D7C; // 1..100
  int*      x = (int*)      0x91DA34; // 1..16
  bool*     f = (bool*)     0x91F2DF; // 1..1000
  float*    e = (float*)    0xA48F14; // 1..100

  struct TGameState
  {
    int RootDlgId;
    int CurrentDlgId;
  };

  typedef void  (__stdcall *TWriteAtCode) (int Count, void* Src, void* Dst);
  typedef void* (__stdcall *THook) (void* HandlerAddr, int HookType, int PatchSize, void* CodeAddr);
  typedef void* (__stdcall *TApiHook) (void* HandlerAddr, int HookType, void* CodeAddr);
  typedef void  (__stdcall *TFatalError) (const char* Err);
  typedef int   (__stdcall *TRecallAPI) (THookContext* Context, int NumArgs);
  typedef void  (__stdcall *TRegisterHandler) (TEventHandler Handler, const char* EventName);
  typedef void  (__stdcall *TFireEvent) (const char* EventName, void* EventData, int DataSize);
  typedef void* (__stdcall *TLoadTxt) (const char* Name);
  typedef void  (__stdcall *TExecErmCmd) (const char* CmdStr);
  typedef void  (__stdcall *TReloadErm) ();
  typedef void  (__stdcall *TExtractErm) ();
  typedef void  (__stdcall *TFireErmEvent) (int EventID);
  typedef void  (__stdcall *TClearAllIniCache) ();
  typedef void  (__stdcall *TClearIniCache) (const char* FileName);
  typedef bool  (__stdcall *TReadStrFromIni) (const char* Key, const char* SectionName, const char* FilePath, char* Res);
  typedef bool  (__stdcall *TWriteStrToIni) (const char* Key, const char* Value, const char* SectionName, const char* FilePath);
  typedef bool  (__stdcall *TSaveIni) (const char* FilePath);
  typedef void  (__stdcall *TNameColor) (int Color32, const char* Name);
  typedef void  (__stdcall *TWriteSavegameSection) (int DataSize, void* Data, const char* SectionName);
  typedef int   (__stdcall *TReadSavegameSection) (int DataSize, void* Data, const char* SectionName);
  typedef void  (__stdcall *TGetGameState) (TGameState* GameState);
  typedef int   (__stdcall *TGetButtonID) (const char* ButtonName);
  typedef bool  (__stdcall *TPatchExists) (const char* PatchName);
  typedef bool  (__stdcall *TPluginExists) (const char* PluginName);
  typedef void  (__stdcall *TRedirectFile) ();
  typedef void  (__stdcall *TGlobalRedirectFile) ();
  typedef void  (__stdcall *TRedirectMemoryBlock) (void* OldAddr, int BlockSize, void* NewAddr);
  typedef void* (__stdcall *TGetRealAddr) (void* Addr);
  typedef void  (__stdcall *TSaveEventParams) ();
  typedef void  (__stdcall *TRestoreEventParams) ();
  typedef void  (__stdcall *TReportPluginVersion) (const char* VersionLine);
  typedef const char* (__stdcall *TGetEraVersion) ();
  typedef char* (__stdcall *TTr) (const char* key, const char** params, int highParams);
  typedef void  (__stdcall *TMemFree) (const void* buf);
  typedef void  (__stdcall *TNotifyError) (const char* error);

  /**
   * Replaces original function with the new one. HandlerFunc signature must be the same as original
   * function, except that one extra argument is passed on the stack as the very first argument. It holds
   * pointer to original replaced function.
   * Example:
   *   Splice((void*) 0x401000, (void*) MainProc);
   *   int __stdcall (void* OrigFunc, int Arg) MainProc {...}
   */
  typedef void* (__stdcall *TSplice) (void* OrigFunc, void* HandlerFunc);

  /**
   * Calls handler function, when execution reaches specified address. Handler receives THookContext pointer.
   * If it returns true, overwritten commands are executed. Otherwise overwritten commands are skipped.
   * Changes Context.RetAddr field to return to specific address after handler finishes execution with FALSE result.
   */
  typedef void* (__stdcall *THookCode) (void* Addr, THookHandler HandlerFunc);

  /**
   * Loads Pcx16 resource with rescaling support. Values <= 0 are considered 'auto'. If it's possible, images are scaled proportionally.
   * Resource name (name in binary resource tree) can be either fixed or automatic. Pass empty PcxName for automatic name.
   * If PcxName exceeds 12 characters, it's replaced with valid unique name. Check name field of result.
   * If resource is already registered and has proper format, it's returned with RefCount increased.
   * Result image dimensions may differ from requested if fixed PcxName is specified. Use automatic naming
   * to load image of desired size for sure.
   * Default image is returned in case of missing file and user is notified.
   */
  typedef void* (__stdcall *TLoadImageAsPcx16) (const char* FilePath, const char* PcxName, int Width, int Height);
 

  TEventParams* EventParams = NULL;


  TApiHook              ApiHook               = NULL;
  TClearAllIniCache     ClearAllIniCache      = NULL;
  TClearIniCache        ClearIniCache         = NULL;
  TExecErmCmd           ExecErmCmd            = NULL;
  TExtractErm           ExtractErm            = NULL;
  TFatalError           FatalError            = NULL;
  TFireErmEvent         FireErmEvent          = NULL;
  TFireEvent            FireEvent             = NULL;
  TGetButtonID          GetButtonID           = NULL;
  TGetEraVersion        GetEraVersion         = NULL;
  TGetGameState         GetGameState          = NULL;
  TGetRealAddr          GetRealAddr           = NULL;
  TGlobalRedirectFile   GlobalRedirectFile    = NULL;
  THook                 Hook                  = NULL;
  THookCode             HookCode              = NULL;
  TLoadImageAsPcx16     LoadImageAsPcx16      = NULL;
  TLoadTxt              LoadTxt               = NULL;
  TMemFree              MemFree               = NULL;
  TNameColor            NameColor             = NULL;
  TNotifyError          NotifyError           = NULL;
  TPatchExists          PatchExists           = NULL;
  TPluginExists         PluginExists          = NULL;
  TReadSavegameSection  ReadSavegameSection   = NULL;
  TReadStrFromIni       ReadStrFromIni        = NULL;
  TRecallAPI            RecallAPI             = NULL;
  TRedirectFile         RedirectFile          = NULL;
  TRedirectMemoryBlock  RedirectMemoryBlock   = NULL;
  TRegisterHandler      RegisterHandler       = NULL;
  TReloadErm            ReloadErm             = NULL;
  TReportPluginVersion  ReportPluginVersion   = NULL;
  TRestoreEventParams   RestoreEventParams    = NULL;
  TSaveEventParams      SaveEventParams       = NULL;
  TSaveIni              SaveIni               = NULL;
  TSplice               Splice                = NULL;
  TTr                   _tr                   = NULL;
  TWriteAtCode          WriteAtCode           = NULL;
  TWriteSavegameSection WriteSavegameSection  = NULL;
  TWriteStrToIni        WriteStrToIni         = NULL;

  /**
   * Returns translation for given complex key ('xxx.yyy.zzz') with substituted parameters.
   * Pass vector of (parameter name, parameter value) pairs to substiture named parameters.
   * Example: Mod\Lang\*.json file: { "eqs": { "greeting": "Hello, @name@" } }
   * Example: ShowMessage(tr("eqs.greeting", { "name", "igrik" }).c_str());
   * 
   * @param  key    Key to get translation for.
   * @param  params Vector of (parameter name, parameter value pairs).
   * @return        Translation string.
   */
  std::string tr (const char *key, const std::vector<std::string> params = {}) {
    const int MAX_PARAMS = 64;
    const char* _params[MAX_PARAMS];
    int numParams = params.size() <= MAX_PARAMS ? params.size() : MAX_PARAMS;

    for (int i = 0; i < numParams; i++) {
      _params[i] = params[i].c_str();
    }

    char* buf = _tr(key, _params, numParams - 1);
    MemFree(buf);

    return buf;
  }

  std::string IntToStr (int value) {
    char buf[64];
    sprintf(buf, "%d", value);
    
    return buf;
  }

  HINSTANCE hEra;
  HINSTANCE hAngel;

  void ConnectEra ()
  {
    hAngel                = LoadLibrary("angel.dll");
    EventParams           = (TEventParams*)         GetProcAddress(hAngel, "EventParams");
    RestoreEventParams    = (TRestoreEventParams)   GetProcAddress(hAngel, "RestoreEventParams");
    SaveEventParams       = (TSaveEventParams)      GetProcAddress(hAngel, "SaveEventParams");
    /***/
    hEra                  = LoadLibrary("era.dll");
    _tr                   = (TTr)                   GetProcAddress(hEra, "tr");
    ApiHook               = (TApiHook)              GetProcAddress(hEra, "ApiHook");
    ClearAllIniCache      = (TClearAllIniCache)     GetProcAddress(hEra, "ClearAllIniCache");
    ClearIniCache         = (TClearIniCache)        GetProcAddress(hEra, "ClearIniCache");
    ExecErmCmd            = (TExecErmCmd)           GetProcAddress(hEra, "ExecErmCmd");
    ExtractErm            = (TExtractErm)           GetProcAddress(hEra, "ExtractErm");
    FatalError            = (TFatalError)           GetProcAddress(hEra, "FatalError");
    FireErmEvent          = (TFireErmEvent)         GetProcAddress(hEra, "FireErmEvent");
    FireEvent             = (TFireEvent)            GetProcAddress(hEra, "FireEvent");
    GetButtonID           = (TGetButtonID)          GetProcAddress(hEra, "GetButtonID");
    GetEraVersion         = (TGetEraVersion)        GetProcAddress(hEra, "GetVersion");
    GetGameState          = (TGetGameState)         GetProcAddress(hEra, "GetGameState");
    GetRealAddr           = (TGetRealAddr)          GetProcAddress(hEra, "GetRealAddr");
    GlobalRedirectFile    = (TGlobalRedirectFile)   GetProcAddress(hEra, "GlobalRedirectFile");
    Hook                  = (THook)                 GetProcAddress(hEra, "Hook");
    HookCode              = (THookCode)             GetProcAddress(hEra, "HookCode");
    LoadImageAsPcx16      = (TLoadImageAsPcx16)     GetProcAddress(hEra, "LoadImageAsPcx16");
    LoadTxt               = (TLoadTxt)              GetProcAddress(hEra, "LoadTxt");
    MemFree               = (TMemFree)              GetProcAddress(hEra, "MemFree");
    NameColor             = (TNameColor)            GetProcAddress(hEra, "NameColor");
    NotifyError           = (TNotifyError)          GetProcAddress(hEra, "NotifyError");
    PatchExists           = (TPatchExists)          GetProcAddress(hEra, "PatchExists");
    PluginExists          = (TPluginExists)         GetProcAddress(hEra, "PluginExists");
    ReadSavegameSection   = (TReadSavegameSection)  GetProcAddress(hEra, "ReadSavegameSection");
    ReadStrFromIni        = (TReadStrFromIni)       GetProcAddress(hEra, "ReadStrFromIni");
    RecallAPI             = (TRecallAPI)            GetProcAddress(hEra, "RecallAPI");
    RedirectFile          = (TRedirectFile)         GetProcAddress(hEra, "RedirectFile");
    RedirectMemoryBlock   = (TRedirectMemoryBlock)  GetProcAddress(hEra, "RedirectMemoryBlock");
    RegisterHandler       = (TRegisterHandler)      GetProcAddress(hEra, "RegisterHandler");
    ReloadErm             = (TReloadErm)            GetProcAddress(hEra, "ReloadErm");
    ReportPluginVersion   = (TReportPluginVersion)  GetProcAddress(hEra, "ReportPluginVersion");
    SaveIni               = (TSaveIni)              GetProcAddress(hEra, "SaveIni");
    Splice                = (TSplice)               GetProcAddress(hEra, "Splice");
    WriteAtCode           = (TWriteAtCode)          GetProcAddress(hEra, "WriteAtCode");
    WriteSavegameSection  = (TWriteSavegameSection) GetProcAddress(hEra, "WriteSavegameSection");
    WriteStrToIni         = (TWriteStrToIni)        GetProcAddress(hEra, "WriteStrToIni");
  }
  
  #pragma pack(pop)
}

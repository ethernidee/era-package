#pragma once

#include "HoMM3.h"

void e_SetScreenOff(_bool_ value);
_bool_ e_IsScreenOff();

NOALIGN struct _CreatureExtraInfo_
{
 int downgrade_type;
 int upgrade_type;
 int grade;
};

//extern _CreatureExtraInfo_ e_CreatureExtraInfo[o_CREARURES_COUNT];
extern _CreatureExtraInfo_* e_CreatureExtraInfo;

void e_FillCreaturesExtra();

inline int e_GetCreatureGrade(int creature_ix)
{
 if (creature_ix < o_CREARURES_COUNT)
  return e_CreatureExtraInfo[creature_ix].grade;
 else
  return 0;
}

inline void e_UpdateHeroDlg()
{
 CALL_0(void, __cdecl, 0x4DB440);
 CALL_0(void, __cdecl, 0x4DB460);
 CALL_1(void, __thiscall, 0x4E1940, o_HeroDlg_Hero);
 CALL_1(void, __thiscall, 0x4D9A60, o_HeroDlg_Hero);
 CALL_5(void, __thiscall, 0x602930, o_WndMgr, 0x200, 5, 0x7F, 0x4008);
 o_CurrentDlg->Redraw();
}

inline void e_DrawWindowShadow(int x, int y, int w, int h)
{
 o_WndMgr->screen_pcx16->DrawShadowRect( x + w, y + 9, 7, h - 9);
 o_WndMgr->screen_pcx16->DrawShadowRect( x + w, y + 8, 8, h - 8);
 o_WndMgr->screen_pcx16->DrawShadowRect( x + 9, y + h, w - 2, 7);
 o_WndMgr->screen_pcx16->DrawShadowRect( x + 8, y + h, w, 8);
}

inline void e_Hero_CompressBackpack(_Hero_* hero)
{
 int i, temp_i;
 temp_i = 0;
 _Artifact_ temp_backpack[64];

 for (i = 0; i < 64; i++)
 {
  if (hero->backpack_art[i].id != -1)
  {
   temp_backpack[temp_i].id = hero->backpack_art[i].id;
   temp_backpack[temp_i].mod = hero->backpack_art[i].mod;
   temp_i++;
  }
 }
 for (i = temp_i; i < 64; i++)
 {
  temp_backpack[i].id = -1;
  temp_backpack[i].mod = 0;
 }
 MemCopy(hero->backpack_art, temp_backpack, sizeof(_Artifact_) * 64);
}

inline void e_ClickSound()
{
 LPCRITICAL_SECTION cs = *(LPCRITICAL_SECTION*)0x694DF4;
 if ( cs )
 {
  _dword_ v = *((_dword_ *)o_SoundMgr + 33);
  *((_dword_ *)o_SoundMgr + 33) = 1;
  cs[1].SpinCount = 64;
  cs[2].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)1;
  cs[1].LockSemaphore = (HANDLE)(HANDLE_FLAG_PROTECT_FROM_CLOSE | HANDLE_FLAG_INHERIT);
  CALL_2(void, __thiscall, 0x59A510, o_SoundMgr, cs);
  *((_dword_*)o_SoundMgr + 33) = v;
 }
}

inline void e_DlgButtonPress(_DlgButton_* btn)
{
 typedef int (__thiscall * _func_PressDlgButton)(_DlgButton_* this_, _EventMsg_* msg);
 _EventMsg_ msg;
 if ((btn->state & 0x20) == 0)
 if ( btn->state & 4 && !(btn->state & 8) )
  ((_func_PressDlgButton)0x456540)(btn, &msg);
}
inline BOOL e_DlgButtonUnpress(_DlgButton_* btn)
{
 if ((btn->state & 0x20) == 0)
 if ( btn->state & 4 && !(btn->state & 8) )
 {
  if ( !(btn->state & 1) )
   return FALSE;
  btn->state = (_byte_)(btn->state & 0xFE);
  btn->Draw();
  btn->RedrawScreen();
  return TRUE;
 }
 return FALSE;
}

#define o_NET_MSG_PlayerJoinTheGame 1040
#define o_NET_MSG_ChatMessage  1004

NOALIGN struct _NetMsg_
{
 _int_ src_player_id;
 _int_ src_player_net_id;
 _int_ type;
 _int_ size;
 _int_ field_10;
 _int_ field_14;
 _int_ data[1];

 inline int GetDataSize() {return (size - 20);}
};

NOALIGN struct _PlayerNetInfo_
{
 _int_ net_id;
 _char_ name[20];
 _int_ field_18[22];
 _int_ player_id;
 _int_ field[2];
};

NOALIGN struct _PlayerNetInfoShort_
{
 _int_ net_id;
 _char_ name[20];
 _int_ field_18[2];
};

#define o_MeNetInfoShort (*(_PlayerNetInfoShort_*)0x69D658)

int e_SendNetMsgVA(int type, int data_args_count, ...);
int e_SendNetMsg(int type, int data_size, _ptr_ data);


_bool_ e_CanShowMarket();
_bool_ e_ShowUnderHeroMarket();
_bool_ e_ShowMarket(_Town_* src_town);
_int_ e_CanShowRank();
_bool_ e_ShowUnderHeroRank();
_bool_ e_ShowRank();




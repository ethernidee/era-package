#pragma once

#include "patcher_x86.hpp"
#include "HoMM3_ids.h"
#include "HoMM3_Names.h"
#include "HoMM3_Base.h"
#include "HoMM3_Res.h"
#include "HoMM3_GUI.h"

//#include <ddraw.h>

// подключать так:
// #include "..\..\include\homm3.h"

#define EXE_VERSION *(_dword_*)0x588479
#define TE 0x001F0E12
#define WOG 0x001EC3A3
#define SOD 0xFFFFE403

// Разрешение игры
#define o_HD_X (*(_int_*)0x401448)
#define o_HD_Y (*(_int_*)0x40144F)
const int ORIG_X = 800;
const int ORIG_Y = 600;

// Абсолютный путь к корневой папке игры.
#define MAIN_ABSPATH *(_cstr_)0x698614
#define PATH_TO_GAME_FOLDER *(_int_*)0x698614

//#define o_HEROES_COUNT 156
//#define o_CREARURES_COUNT 150
#define o_HEROES_COUNT (*(_int_*)0x4BD145)
#define o_CREARURES_COUNT (*(_int_*)0x5C8047)

struct _Army_;
struct _CreatureInfo_;
struct _CreatureOnMap_;
struct _CrExpo_;
struct _TurnTimeStruct_;
struct _MapItem_;
struct _Artifact_;
struct _ArtInfo_;
struct _ArtOnMap_;
struct _Npc_;
struct _Hero_;
struct _HeroFlags_;
struct _HeroInfo_;
struct _HeroSpecInfo_;
struct _Mine_;
struct _Player_;
struct _Town_;
struct _MapGlobalEvent_;
struct _H3ObjectDraw_;
struct _BattleAnim_;
struct _BattleStack_;
struct _BattleHexAdjacent_;
struct _NewScenarioDlg_;
struct _H3Quest_;
struct _H3QuestGuard_;
struct _H3QuestSeerHut_;
// Видеоролики
struct _Video_;
// Карта игры.
struct _GameMap_;
// Объект на карте приключений.
struct _Object_;
// Объект - лагерь героя (при загрузке карты).
struct _PlaceHolder_;
// Список героев.
struct _HeroesList_;
// Внешнее жилище на карте.
struct _Dwelling_;

// Настройки зоны генератора случйных карт.
struct _ZoneSettings_;

// структура битвы ИИ на ИИ
struct _AIQuickBattleCreatures_;
struct _AIQuickBattle_;


// Менеджреры игры. Несколько из них ещё не распознаны.
// _bool32_ __cdecl sub_4EE1D0() - инициализация менеджеров. По ней распознан их размер.
// struct _Manager_; // Размер: 56

// Some Mgr по 0x699550, размер: 16

// Менеджер ввода, управляющий событиями ввода.
struct _InputMgr_; // Размер: 2400
#define o_InputMgr (*(_InputMgr_**)0x699530)

// Менеджер мыши.
struct _MouseMgr_; // Размер: 144
#define o_MouseMgr (*(_MouseMgr_**)0x6992B0)
// #define o_MouseMgr (*(_Struct_**)0x6992B0)

// Менеджер окна программы.
struct _WndMgr_; // Размер: 96
#define o_WndMgr (*(_WndMgr_**)0x6992D0)

// Менеджер звука.
struct _SoundMgr_; // Размер: 216
#define o_SoundMgr (*(_SoundMgr_**)0x699414)

// Some Mgr по 0x69941C, размер: 2260

// Менеджер игры.
struct _GameMgr_; // Размер: 321488
#define o_GameMgr (*(_GameMgr_**)0x699538)

// Менеджер карты приключений.
struct _AdvMgr_; // Размер: 952
#define o_AdvMgr (*(_AdvMgr_**)0x6992B8)

// Менеджер битвы.
struct _BattleMgr_; // Размер: 82156
#define o_BattleMgr (*(_BattleMgr_**)0x699420)

// Менеджер окна города.
struct _TownMgr_; // Размер: 472
#define o_TownMgr (*(_TownMgr_**)0x69954C)

// Менеджер создания диалогов
struct _ExecMgr_; // Размер: 16
#define o_ExecMgr (*(_ExecMgr_**)0x699550)

// Менеджер окна встречи героев
struct _SwapMgr_; // Размер: 104
#define o_SwapMgr (*(_SwapMgr_**)0x6A3D90)

// Some Mgr по 0x6992D4, размер: 112

// Some Mgr по 0x6992DC, размер: 1

// локализация WoG (0 - eng, 1 - rus)
#define isRusLangWoG (*(_int_*)0x80321C) 

#define o_ScreenBPP (*(_int_*)0x68C8C0)
#define o_ScreenWidth (*(_int_*)0x68C8C4)
#define o_ScreenHeight (*(_int_*)0x68C8C8)
#define o_DD (*(LPDIRECTDRAW*)0x6AAD20)
#define o_DDSurfacePrimary (*(LPDIRECTDRAWSURFACE*)0x6AAD24)
#define o_DDSurfaceBackBuffer (*(LPDIRECTDRAWSURFACE*)0x6AAD28)
#define o_DDSurface6AAD2C (*(LPDIRECTDRAWSURFACE*)0x6AAD2C)
#define o_DDSurface6AAD30 (*(LPDIRECTDRAWSURFACE*)0x6AAD30)
#define o_DDSurface6AAD34 (*(LPDIRECTDRAWSURFACE*)0x6AAD34)
#define o_FullScreenMode (*(_bool_*)0x698808)
#define o_hWnd (*(HWND*)0x699650)

#define HERO_INFO_OFFSET (*(_ptr_*)0x67DCE8)
//#define o_HeroInfo ((_HeroInfo_*)0x679DD0)
#define o_HeroInfo ((_HeroInfo_*)HERO_INFO_OFFSET)
#define o_pHeroInfo (*(_HeroInfo_**)0x67DCE8)

// получить кол-во героев в игре
#define o_HeroesCount (*(_int32_*)0x4BB1EE)

// Таблица специализаций героев
// #define o_HeroSpecInfo ((_HeroSpecInfo_*)0x678420)
#define o_HeroSpecInfo (*(_HeroSpecInfo_**)0x679C80)

// Таблица специализаций героев.
#define o_pHero_Spec_Table (_ptr_)0x679C80
#define o_pHeroSpec (*(_int_*)0x679C80)

#define o_NetworkGame *(_bool_*)0x69959C
//#define o_CampaignGame *(_bool_*)0x69779C
#define o_ActivePlayer (*(_Player_**)0x69CCFC)
#define o_ActivePlayerID *(_int_*)0x69CCF4
#define o_MeID *(_int_*)0x6995A4

#define o_Tavern_OnAdvMap *(_bool_*)0x6AAAB0 
#define o_Tavern_Structure *(_Dlg_*)0x6AAA54 
#define o_Tavern_Hero *(_Hero_*)0x6AA690 
#define o_Tavern_CostHero *(_int_*)0x67814C

#define o_Market_Hero (*(_Hero_**)0x6AAAE0)
#define o_DirectPlayCOMObject *(_ptr_*)0x69D858

//#define CREATURE_INFO_OFFSET (*(_ptr_*)0x47ADD1)
#define CREATURE_INFO_OFFSET (*(_ptr_*)0x6747B0)
//#define o_CreatureInfo ((_CreatureInfo_*)0x6703B8)
#define o_CreatureInfo ((_CreatureInfo_*)CREATURE_INFO_OFFSET)
#define o_pCreatureInfo (*(_CreatureInfo_**)0x6747B0)

#define o_GameMgrType (*(_int_*)0x698A40)
#define o_QuickBattle (*(_int_*)0x6987CC)
#define o_AutoSolo (*(_byte_*)0x691259)
#define o_TimeClick (*(_int_*)0x6977D4)
#define o_IsOnlineGame *(_bool_*)0x69959C

#define o_CombatOptionsDlg (*(_Dlg_**)0x694FE0)
#define o_Battle_MovementShadow (*(_int_*)0x698814)
#define o_Battle_CursorShadow (*(_int_*)0x698810)
#define o_Battle_ShowGrid (*(_int_*)0x69880C)
#define o_Battle_UserHighlightedGex (*(_int_*)0x688374)
#define o_MapWidth *(_dword_*)0x6783C8
#define o_MapHeight *(_dword_*)0x6783CC
#define o_ViewingWorldEarthAirNow *(_dword_*)0x6AACA4
#define o_ViewWorldEarthAirMapCellSize *(_float_*)0x68C708
#define o_MusicVolume (*(_byte_*)0x6987B0)
#define o_TextBuffer ((char*)0x697428)
#define o_NullString ((char*)0x691260)
#define o_TurnTimer ((_TurnTimeStruct_*)0x69D680)
#define o_ScreenLogStruct ((_ptr_)0x69D800)
#define o_ArtInfo (*(_ArtInfo_**)0x660B68)
#define o_RegKeyPath ((_char_*)0x67FE78)
#define o_RegKey_AppPath ((_char_*)0x67FC10)
#define o_RegKey_CDDrive ((_char_*)0x67FC08)

#define o_CurrentDlg (*(_Dlg_**)0x698AC8)

#define o_HeroDlg_Hero (*(_Hero_**)0x698B70)
#define o_CurArt (*(_Artifact_*)0x698AD8)
#define o_HeroDlg_SelStackIndex (*(_int_*)0x697788)


#define o_ChooseHexBySpellTeleport (*(_byte_*)0x6A3D0C)

// переменная для проверки стартовала ли игра (т.е. видима ли уже карта)
// например диалог повышения уровня при старте карты пропускается из-за неё
#define o_StartGame_SkipDialogs (*(_int_*)0x698450)

// переменная вога, которая блокирует изменение кадра курсора
#define WOG_DisableMouse (*(_int_*)0x840E10)
#define WOG_IDummy (*(_int_*)0x83EEFC)


//#define o_BattleAnimation ((_BattleAnim_*)0x641E18)
extern _BattleAnim_* o_BattleAnimation;
extern _int_ BattleAnims_Count;


#define p_NewScenarioDlg (*(_ptr_*)0x69FC44)

#define b_unpack_z(xyz) (((_int16_)(((_dword_)(xyz)) >> 14)) >> 12)
#define b_unpack_y(xyz) (((_int16_)(((_dword_)(xyz)) >> 10)) >> 6)
#define b_unpack_x(xyz) (((_int16_)(((_dword_)(xyz)) << 6)) >> 6)
#define b_pack_xyz(x, y, z) (_dword_)( (((_dword_)(((_word_)(y)) & 0x3FF)) << 16) | ((_dword_)(((_word_)(x)) & 0x3FF)) | (((_dword_)(((_word_)(z)) & 0xF)) << 26) )

// Текущая игра - встроенная кампания.
#define Game_Is_BuiltInCampaing (*(_bool8_*)0x69779C)

#define o_NewScenarioDlg (*(_NewScenarioDlg_**)0x69FC44)
#define o_Spells (*(_Spell_**)0x687FA8)

// Таблица заклинаний.
#define o_Spell (*(_Spell_**)0x687FA8)

// Минимальное время между кадрами (user).
#define MIN_FRAME_PERIOD 10

// Количество гексов поля боя.
#define BATTLE_HEXES_COUNT 187

// Количество стеков у каждой стороны на поле боя.
#define BATTLE_SIDE_STACKS_COUNT 21


// Количество порядков активных элементов отображения в бою.
#define BATTLE_MAPPING_PRIORITIES_COUNT 8

// Количество элементов замка.
#define CASTLE_ELEMENTS_COUNT 8

// Время ожидания одного кадра отроисовки полёта небаллистического выстрела или заклинания.
#define ShotFrameTime (*(_float_*)0x63B8A0)

// Время, до которого будет производиться ожидание при следующей отрисовке.
// Устанавливается каждой отрисовкой для следующей...
// ...чтобы, если на процессы между ними затратится время, оно автоматически вычлось из времени ожидания.
#define DrawingWaitTime (*(_dword_*)0x6989E8)

// Время следующего проигрыша анимации ожидания в бою.
#define WaitAnimTime (*(_dword_*)0x698A08)

// Массив множителей периодов ожиданий анимации для настройки скорости боя.
#define BattleAnimPeriodFactors ((_float_*)0x63CF7C)

// Настройка скорости боя (индес нужного множителя периодов ожиданий в массиве).
#define Settind_BattleFast (*(_dword_*)0x69883C)

// Временная текстовая переменная. Размер: 768 байт.
#define H3TempStr ((char*)0x697428)

// Пустая переменная.
#define EmptyVar (*(DWORD*)0x691260)

// Пустой звук.
#define EmptySample (*(_Sample_*)0x6992A8)

// Стандартный период анимации.
#define STD_FRAME_PERIOD 100

// Границы перерисовки поля боя.
#define BattleRedraw_Borders (*(_RedrawBorders_*)0x694F68)

// Боевые элементы замка.
#define CastleElements ((_CastleElement_*)0x63BE60)


// Номера гексов крепостной стены по рядам поля боя.
#define CastleWall_Gexes ((_byte_*)0x63BD00)

// константы ERA
#define FOH_ret (*(_int_*)0x27F93B0)
#define FOH_Monstr (*(_int_*)0x27718CC) 
// int* WoG_MonsterUpgradeTable = (int*)0xA49590;

// записать регистры
_int_ b_WriteRegistry() { return CALL_0(_int_, __cdecl, 0x50C370); }

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

NOALIGN struct _TagRect_
{
  _int_ left;
  _int_ top;
  _int_ right;
  _int_ bottom;
};

NOALIGN struct _Resources_
{
 _int_ wood;
 _int_ mercury;
 _int_ ore;
 _int_ sulfur;
 _int_ crystal;
 _int_ jems;
 _int_ gold;

 _bool8_ EnoughResources(_Resources_* cost);
 void RemoveResources(_Resources_* cost);
};

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////


NOALIGN struct _Army_
{
 _int_ type[7];
 _int_ count[7];
 
 // Конструтор.
 inline _Army_* Construct()
 {
   return CALL_1(_Army_*, __thiscall, 0x44A750, this);
 }
 
 // normal
 inline int GetStacksCount() {return CALL_1(int, __thiscall, 0x44A990, this);}
 inline int GetCreaturesCount() {return CALL_1(int, __thiscall, 0x44AA70, this);}
 inline void SwapStackTo(int ix, _Army_* dst_army, int dst_ix) {CALL_4(void, __thiscall, 0x44AA30, this, ix, dst_army, dst_ix);}
 inline void SplitStackByDlgTo(int i, _Army_* dst_army, int dst_i, _bool8_ is_hero, _bool8_ dst_is_hero)
  {CALL_6(void, __thiscall, 0x449B60, this, i, dst_army, dst_i, is_hero, dst_is_hero);}
  // igrik
  inline void AddStack(_int_ type, _int_ amount, _int_ slot) {CALL_4(void, __thiscall, 0x44A9B0, this, type, amount, slot);}
  inline _byte_ HasCreatureType(_int_ creature) { return CALL_2(_byte_, __thiscall, 0x44A850, this, creature);}
  inline _byte_ HasCreatures() { return CALL_1(_byte_, __thiscall, 0x449370, this); }
  inline _int_ Clear() { return CALL_1(_int_, __thiscall, 0x44A750, this); }
  inline _int_ ClearStack(_int_ stack) { return CALL_2(_int_, __thiscall, 0x44A830, this, stack); }
  inline _int_ ClearAndGive(_int_ type, _int_ count) { return CALL_3(_int_, __thiscall, 0x44A770, this, type, count); }
  inline _byte_ IsUndeadArmy() { return CALL_1(_byte_, __thiscall, 0x44A7F0, this); }
  inline _int_ NumberAlignments(_byte_ towns) { return CALL_2(_int_, __thiscall, 0x44A880, this, towns); }

};


NOALIGN struct _CreatureOnMap_
{
  // * +0
  _HStr_ message;
  // * +10
  _Resources_ cost;
  // * +2C
  _int32_ artifact;
};


// Получение имени существа по его номеру и количеству.
#define GetCreatureName(Type, Count) CALL_2(_cstr_, __fastcall, 0x43FE20, (_int_)Type, (_int_)Count)
// Получение грейда существа (-1 - нет грейда).
#define GetCreatureUprade(Type) CALL_1(_int_, __fastcall, 0x47AAD0, (_int_)Type)
#define GetCreatureUpradeWOG(Type) CALL_1(_int_, __fastcall, 0x74ECD3, (_int_)Type)
// Получение стоимости улучшения монстра (возвразает _Resources_)
#define GetCreatureUpradeCost(getCost, Type, UpType, Count) CALL_1(_int_, __fastcall, 0x54EB50, (_int_)Type, (_int_)Type, (_int_)Type, _Resources_* getCost)


NOALIGN struct _CreatureInfo_
{
 _int_ town;
 _int_ level;
 _char_* sound_name;
 _char_* def_name;
 _int_ flags;
 _char_* name_single;
 _char_* name_plural;
 _char_* specification_description;

 //_int_ cost_wood;
 //_int_ cost_mercury;
 //_int_ cost_ore;
 //_int_ cost_sulfur;
 //_int_ cost_crystal;
 //_int_ cost_jems;
 //_int_ cost_gold;
 _Resources_ cost;

 _int_ fight_value;
 _int_ AI_value;
 _int_ growth;
 _int_ horde_growth;
 _int_ hit_points;
 _int_ speed;
 _int_ attack;
 _int_ defence;
 _int_ damage_min;
 _int_ damage_max;
 _int_ shots;
 _int_ spells_count;
 _int_ advmap_low;
 _int_ advmap_high;

 inline _cstr_ GetName(_int_ type, _int_ count) {return CALL_2(_cstr_, __fastcall, 0x43FE20, type, count); }
 inline _int_ GetUprade(_int_ type) {return CALL_1(_int_, __fastcall, 0x47AAD0, type); }
 inline _int_ GetUpradeWoG(_int_ type) {return CALL_1(_int_, __fastcall, 0x74ECD3, type); }
 inline _int_ GetUpradeCost(_int_ type, _int_ typeUpgrade, _int_ count, _Resources_* getCost) 
  {return CALL_4(_int_, __fastcall, 0x54EB50, type, typeUpgrade, count, getCost); }
};

// 96 bytes
NOALIGN struct _HeroInfo_
{ 
 _dword_ sex;              // +0 - Пол (0 - женский, 1 - мужской)
 _dword_ race;             // +4 расса героя
 _dword_ classHero;          // +8  класс героя
 _dword_ second_skill_1;       // +12 первый вторичный навык
 _dword_ second_skill_1_lvl;     // +16 первый вторичный навык уровень
 _dword_ second_skill_2;       // +20 второй вторичный навык
 _dword_ second_skill_2_lvl;     // +24 второй вторичный навык уровень
 _dword_ spellBook;          // +28 есть ли книга заклинаний
 _dword_ startSpell;         // +32 стартовое заклинание
 _dword_ army_type[3];         // +36-44 типы существ при старте
 _ptr_ hps_name;
 _ptr_ hpl_name;
 _byte_ allowedInRoE;          // Разрешён ли в Возрождении Эрафии.
 _byte_ allowedInSoD;          // Разрешён ли не в Возрождении Эрафии.
 _byte_ isCampaing;          // Кампанейский ли.
 _byte_ isCanChoosingOnStart;    // Может ли стартовать в начале игры.
 _byte_ field_38[4];
 _ptr_ name;
 _dword_ army_count[6];
};

// 40 bytes
NOALIGN struct _HeroSpecInfo_
{ 
  _dword_ p0;
  _dword_ p1;
  _dword_ p2;
  _dword_ p3;
  _dword_ p4;
  _dword_ p5;
  _dword_ p6;
  _dword_ p7;
  _dword_ p8;
  _dword_ p9; 
};


NOALIGN struct _TurnTimeStruct_
{
 _dword_ last_shown;
 _dword_ turn_start;
 _dword_ turn_limit;
 _dword_ next_shown;
 _dword_ battle_start;

 inline void NewTurn() { CALL_1(void, __thiscall, 0x558130, this); }
};

NOALIGN struct _HString_
{
 _char_* c_str;
 _int_ length;
};
NOALIGN struct _HStringA_
{
 _HString_ h_str;
 _int_ a;
};
NOALIGN struct _HStringF_
{
 _bool8_ is_memory_allocated;
 _byte_ dummy_f1[3];
 _HString_ h_str;
 _int_ size;
};
NOALIGN struct _GlobalEvent_
{
 _HStringF_ message_f;
 _Resources_ resouces;
 _byte_ players_bits;
 _byte_ for_human;
 _byte_ for_ai;
 _word_ day;
 _word_ repeat;
};
NOALIGN struct _MapItem_
{
 _dword_  setup;      //+0
 _byte_  land;        //+4
 _byte_  land_type;   //+5
 _byte_  river;       //+6
 _byte_  river_type;  //+7
 _byte_  road;        //+8
 _byte_  road_type;   //+9
 _word_  field_0A;    //+10
 _byte_  mirror;      //+12
 _byte_  attrib;      //+13
 _word_  field_0E_bits; //+14

 _word_  field_10;    //+16
 _dword_  draw;       //+18
 _dword_  draw_end;   //+22
 _dword_  draw_end_2; //+26
 _word_  object_type; //+30

 _word_  _u3;         //+32
 _word_  os_type;     //+34
 _word_  draw_num;    //+36

 _dword_ GetReal__setup() { return CALL_1(_dword_, __thiscall, 0x4FD280, this);}
 _dword_ GetReal__object_type() { return CALL_1(_dword_, __thiscall, 0x4FD220, this);}
 
 // Сделать объект посещённым игроком.
 inline void SetAsVisited(_int_ player_ix)
 {
   CALL_2(void, __thiscall, 0x4FC620, this, player_ix);
 }
 
 // Сделать объект посещённым игроком.
 inline _bool8_ IsVisited(_int_ player_ix)
 {
   return CALL_2(_bool8_, __thiscall, 0x529B70, this, player_ix);
 } 

 // signed int __thiscall GetTerrainOverlayTypeOfMapItem(_MapItem_ *this)  
 inline int GetTerrainOverlayType()
 {
  return CALL_1(int, __thiscall, 0x4FD470, this);
 }
};


NOALIGN struct _Artifact_
{
 _int_ id;
 _int_ mod;
};

// 32 bytes.
NOALIGN struct _ArtInfo_
{
 char* name;
 _int_ cost;
 _int_ position; // Тип слота, а не номер (например, оба слота кольца - 1 тип)
 _int_ type;
 char* description;
 _int_ supercomposite;
 _int_ part_of_supercomposite;
 _byte_ disabled;
 _byte_ new_spell;
 _byte_ field_1E;
 _byte_ field_1F;
};

struct _ArtOnMap_
{
  // * +0
  _HStr_ message;
  // * +10
  _bool8_ isGuarded;
  _byte_ _f_11[3];
  // * +14
  _Army_ guardians;
};


// 8 bytes. Слот для артефакта.
NOALIGN struct _ArtSlotInfo_
{
  // +0. Имя слота.
  _cstr_ name;
  
  // +4. Тип слота.
  _int_ type;
};

NOALIGN struct _HeroFlags_
{
  // * 0x1
  // * Visited Well
  _dword_ well : 1;
  // * 0x2
  // * Visited Stables
  _dword_ stables : 1;
  // * 0x4
  // * Visited Buoy
  _dword_ buoy : 1; // 0x4
  // * 0x8
  // * Visited Swan Pond
  _dword_ swan_pond : 1;
  // * 0x10
  // * Visited idol of fortune on days 1~6, morale bonys
  _dword_ idol_fortune_morale : 1;
  // * 0x20
  // * -1 luck from fountain of fortune
  _dword_ fountain_fortune1 : 1;
  // * 0x40
  // * visited watering hole
  _dword_ watering_hole : 1;
  // * 0x80
  // * visited oasis
  _dword_ oasis : 1;
  // * 0x100
  // * visited temple on days 1~6
  _dword_ temple : 1;
  // * 0x200
  // * shipwreck morale penalty
  _dword_ shipwreck : 1;
  // * 0x400
  // * crypt morale penalty
  _dword_ crypt : 1;
  // * 0x800
  // * derelict ship morale penalty
  _dword_ derelect_ship : 1;
  // * 0x1000
  // * pyramid morale penalty
  _dword_ pyramid : 1;
  // * 0x2000
  // * visited faerie ring
  _dword_ faerie_ring : 1;
  // * 0x4000
  // * visited fountain of youth
  _dword_ fountain_of_youth : 1;
  // * 0x8000
  // * visited mermaids
  _dword_ mermaids : 1;
  // * 0x10000
  // * visited rally flag
  _dword_ rally_flag : 1;
  // * 0x20000
  // * hero is in tavern
  // * see 0x4DA4D1
  _dword_ in_tavern : 1;
  // * 0x40000
  // * hero is in a boat
  _dword_ in_boat : 1;
  // * 0x80000
  _dword_ unk1 : 1;
  // * 0x100000
  // * visited sirens
  _dword_ sirens : 1;
  // * 0x200000
  // * warrior's tomb morale penalty
  _dword_ warrior_tomb : 1;
  // * 0x400000
  // * typed luck cheat
  _dword_ luck_cheat : 1;
  // * 0x800000
  // * typed morale cheat
  _dword_ morale_cheat : 1;
  // * 0x01000000
  // * typed speed cheat
  _dword_ speed_cheat : 1;
  // * 0x02000000
  // * luck bonus from idol of fortune
  _dword_ idol_fortune_luck : 1;
  // * 0x04000000
  // * visited temple on day 7, +2 morale
  _dword_ temple2 : 1;
  // * 0x08000000
  // * +1 luck from fountain of fortune
  _dword_ fountain_fortune2 : 1;
  // * 0x10000000
  // * +2 luck from fountain of fortune
  _dword_ fountain_fortune3 : 1;
  // * 0x20000000
  // * +3 luck from fountain of fortune
  _dword_ fountain_fortune4 : 1;
  // * 0x40000000
  // * 0x80000000
  _dword_ unk4 : 2;
};


NOALIGN struct _Hero_: _Struct_
{
 _int16_ x; // +0
 _int16_ y; // +2
 _int16_ z; // +4
 _byte_ visible; // +6
 _dword_ mui_xyz; // +7
 _byte_ miu_is; // +11
  // miu = map_item under hero
 _dword_ miu_object_type; // +12
 _dword_ miu_object_c_flag; // +16
 _dword_ miu_UnderHero; // +20
 _word_ spell_points; // +24
 _dword_ id; // +26
 _dword_ id_wtf; // +30
 _int8_ owner_id; // +34
 _char_ name[13]; // +35
 _dword_ _class; // +48
 _byte_ pic; // +52
 _dword_ targetX; // +53
 _dword_ targetY; // +57
 _dword_ targetZ; // +61
 _word_ last_magic_school_level; // +65
 _byte_ target_is_critical; // +67
 _byte_ patrol_x; // +68
 _byte_ patrol_y; // +69
 _byte_ patrolRadius; // +70
 _byte_ facing; // +71
 _byte_ flags; // +72
 _dword_ movement_max; // +73
 _dword_ movement_curr; // +77
 _dword_ expa; // +81
 _word_ level; // +85
 _dword_ visited[10]; // +87 (0-learningStones, 1-marlettoTower, 2-gardenRevelation, 3-mercenaryCamp, 4-starAxis, 5-treeKnowldge, 6-libraryEnlightenment, 7-arena, 8-schoolMagic, 9-schoolWar)
 _dword_ shrineFlags[4]; // +127
 _byte_ levelSeed; // +143
 _byte_ lastWisdom; // +144
 _Army_ army; // +145
 _byte_ second_skill[28]; // +201
 _byte_ second_skill_show[28]; // +229 // secSkillPosition[28]
 _dword_ second_skill_count; // +257
 _dword_ temp_mod_flags; // + 261
 // _HeroFlags_ temp_mod_flags; // + 261
 float turnExperienceToRVRatio; // +265
 _byte_ dd_cast_this_turn; // +269
 _int32_ disguise_cast_power; // +270
 _int32_ fly_cast_power; // +274
 _int32_ waterwalk_cast_power; // +278
 _byte_ moraleBonus; // +282
 _byte_ luckBonus; // +283
 _byte_ is_sleeping; // +284
 _int32_ bounty; // +285
 _byte_ TownSpecialGrantedMask[8]; // +289 std::bitset<48> TownSpecialGrantedMask;
 _int32_ VisionsPower; // +297
 _Artifact_ doll_art[19]; // +301
 _byte_ free_add_slots; // +453
 _byte_ locked_slot[14]; // +454
 _Artifact_ backpack_art[64]; // +468
 _byte_ backpack_arts_count; // +980
 _dword_ female; // +981
 _bool8_ is_castom_biography; // +985
 _HStringF_ biography; // +986 std::string biography;
 _byte_ spells_spellbook[70]; // +1002
 _byte_ spells_available[70]; // +1072
 _byte_ primary_skill[4]; // +1142
 _int32_ aggression; // +1146
 _int32_ value_of_power; // +1150
 _int32_ value_of_duration; // +1154
 _int32_ value_of_knowledge; // +1158
 _int32_ value_of_spring; // +1162
 _int32_ value_of_well; // +1166

 // normal
 void Hide() {CALL_1(void, __thiscall, 0x4D7950, this);}
 void Show(_int_ mapitem_type, _int_ mapitem_setup) {CALL_3(void, __thiscall, 0x4D7840, this, mapitem_type, mapitem_setup);}
 char* Get_className() {return CALL_1(char*, __thiscall, 0x4D91E0, this);}
 int GetLandModifierUnder() {return CALL_1(int, __thiscall, 0x4E5210, this);}
 void CastFly(int powerCast) {CALL_2(void, __thiscall, 0x4E5C10, this, powerCast);}

 // телепортировать героя
 _byte_ Teleport(_dword_ xyz) { return CALL_6(_byte_, __thiscall, 0x41DAB0, o_AdvMgr, this, xyz, 0, 1, 0); }
 // дать армию герою
 _bool_ AddStack(_int_ type, _int_ amount, _int_ slot = -1) { return CALL_4(_bool_, __thiscall, 0x44A9B0, &this->army, type, amount, slot); }

 // обучение грамотностью между героями
 void TeachScholar(_Hero_* heroRight) { CALL_2(void, __fastcall, 0x4A25B0, this, heroRight); }

 void GiveArtifact(_Artifact_* art, int is_need_build_combo, int check_win_game) {CALL_4(void, __thiscall, 0x4E32E0, this, art, is_need_build_combo, check_win_game);}
 void GiveArtifact(_int_ art_id, int is_need_build_combo, int check_win_game) 
 {
  _Artifact_ art;
  art.id = art_id;
  art.mod = 0xFFFF;
  GiveArtifact(&art, is_need_build_combo, check_win_game);
 }

 _bool_ DoesHasArtifact(int art_id) {return CALL_2(_bool_, __thiscall, 0x4D9420, this, art_id);}
 _bool_ DoesWearArtifact(int art_id) {return CALL_2(_bool_, __thiscall, 0x4D9460, this, art_id);}
 void RemoveBattleMachine(int creature_id) {CALL_2(void, __thiscall, 0x4D94D0, this, creature_id);}
 int RemoveDollArtifact(int doll_slot_index) {return CALL_2(int, __thiscall, 0x4E2E40, this, doll_slot_index);}
 int AddDollArtifact(_Artifact_* art, int doll_slot_index) {return CALL_3(int, __thiscall, 0x4E2C70, this, art, doll_slot_index);}
 int RemoveBackpackArtifact(int index) {return CALL_2(int, __thiscall, 0x4E2FC0, this, index);}
 int AddBackpackArtifact(_Artifact_* art, int index) {return CALL_3(int, __thiscall, 0x4E3200, this, art, index);}

  // открытие окна героя
 _int_ ShowHeroScreen(_int_ noDissmiss, _int_ noRedrawAdvMap, _byte_ rightClickDlg)
 {
   return CALL_4(_int_, __fastcall, 0x4E1A70, this->id, noDissmiss, noRedrawAdvMap, rightClickDlg);
 }

 // получить стоимость маны за заклинание 
 _int_ GetSpellCost(_int_ spell_id, _Army_* army, _int_ land_modifier)
 {
   return CALL_4(_int_, __thiscall, 0x4E54B0, this, spell_id, army, land_modifier);
 }

  // Получение уровня силы магии в бою
 _int_ Get_School_Level_Of_Spell(_int_ spell_id, _int_ land_modifier)
 {
   return CALL_3(_int_, __thiscall, 0x4E52F0, this, spell_id, land_modifier);
 }

// Получение силы спелла от бонуса артов (длительность действия)
 _int_ Get_Spell_Rounds_Bonus_Arts()
 {
   return CALL_1(_int_, __thiscall, 0x4E5020, this);
 }
 // Получение силы спелла от бонуса втор.навыка Волшебство
 _int64_ Get_Spell_Power_Bonus_Arts_And_Sorcery(int spell, signed int damage, _BattleStack_* stack)
 {
   return CALL_4(_int64_, __thiscall, 0x4E59D0, this, spell, damage, stack);
 }

 // Получение бонуса к эффекту заклинания за специализацию.
 _int_ GetSpell_Specialisation_PowerBonuses(int Spell_id, signed int damage, int Creature_level)
 {
   return CALL_4(_int_, __thiscall, 0x4E6260, this, Spell_id, Creature_level, damage);
 }

 _int_ GetSpecialTerrain() {return CALL_1(_int_, __thiscall, 0x4E5130, this); } 

 // СПЕЦИАЛИЗАЦИИ ГЕРОЕВ
// float SS_GetArcheryPower = CALL_1(float, __thiscall, 0x4E43D0, hero);  // Стрельба (Archery)
// float SS_GetDiplomacyPower = CALL_1(float, __thiscall, 0x4E47F0, hero);  // Дипломатия (Diplomacy)
// float SS_GetEagleEyePower = CALL_1(float, __thiscall, 0x4E4690, hero);   // Зоркость (Eagle Eye)
// float SS_GetNecromancyPower = CALL_1(float, __thiscall, 0x4E3F40, hero, _bool8_ isSetMaxValuePower); // Некромантия (Necromancy)
// float SS_GetEstatesPower = CALL_1(float, __thiscall, 0x4E4600, hero);  // Имущество (Estates)
// float SS_GetLearningPower = CALL_1(float, __thiscall, 0x4E4AB0, hero);   // Обучение (Learning)
// float SS_GetOffensePower = CALL_1(float, __thiscall, 0x4E4520, hero);  // Нападение (Offense)
// float SS_GetArmorerPower = CALL_1(float, __thiscall, 0x4E4580, hero);  // Доспехи (Armorer)
// float SS_GetIntelligencePower = CALL_1(float, __thiscall, 0x4E4B20, hero); // Интеллект (Intelligence)
// float SS_GetResistancePower = CALL_1(float, __thiscall, 0x4E4950, hero); // Сопротивление (Resistance)
// float SS_GetFirstAidPower = CALL_1(float, __thiscall, 0x4E4B90, hero);   // Первая помощь (First Aid)
// _int_ SS_GetEstatesPower = CALL_1(_int_, __thiscall, 0x4E4600, hero);  // Имущество
// _int_ SS_GetMysticismPower = CALL_1(_int_, __thiscall, 0x4E41B0, hero);  // Мистицизм
// _int_ SS_GetScoutingRadius = CALL_1(_int_, __thiscall, 0x4E42E0, hero);  // Разведка
// _int_ ReCalculateMovementPoints = CALL_1(_int_, __thiscall, 0x4E4C00, hero, _bool8_ inOnBoat);  // Пересчитать мувпоинты
 
 
 //my
 void ShowSpellBookDlg(int a1, int a2, int land_modifier)
 {
  if (this->doll_art[17].id != -1)
  {
   _Dlg_* dlg = (_Dlg_*)o_New(0xD0);
   // create spellbook dlg
   CALL_5(void, __thiscall, 0x59C0F0, dlg, this, a1, a2, land_modifier);
   dlg->Run();
   // destroy spellbook dlg
   CALL_1(void, __thiscall, 0x59CBF0, dlg);
   o_Delete(dlg);
  }
 }
 void ShowSpellBookDlg(int a1, int a2) 
  {ShowSpellBookDlg(a1, a2, this->GetLandModifierUnder());}
};

// size 0x168 (360 bytes)
NOALIGN struct _Player_: _Struct_
{
  _int8_ id;
  _int8_ heroes_count;
  _word_ field_2;
  _int_ selected_hero_id;
  _int_ heroes_ids[8]; 
  _int_ tavern_heroes[2];

  _byte_ field_30[4];

  _int32_ AI_type;
  _int8_ visitedObelisks;

  _byte_ field_39[4];

  _byte_  daysLeft;
  _int8_  townsCount;
  _int8_  currentTown;
  _int8_  towns[48];

  _byte_ field_70[4];

  _int32_ topHeroIndex;

  _byte_ field_78[36];

  _Resources_ resourses;

  _int32_ magical_gardens;
  _int32_ magic_spring;
  _int8_ unknown4[12];

  _char_ player_name[21];

  _bool8_ isLocal;
  _bool8_ isHuman;

  _byte_ field_E3[3];

  _bool8_ human;

  _byte_ field_E7;

  _bool_ hasComboArtifacts;

  _byte_ field_EC[28];

  _Resources_ income;

  _byte_ field_124[4];

  double resourceImportance[7];

  _byte_ field_160[8];

  _byte_ IsHumanAndWTF() {return CALL_1(_byte_, __thiscall, 0x4BAA40, this);}
  _byte_ IsHuman() {return CALL_1(_byte_, __thiscall, 0x4BAA60, this);}

  void MoveHeroToTownUp(_Town_* town) { CALL_2(void, __thiscall, 0x4B9C80, this, town);}

  //my
  inline _bool_ IsActive() {return (_bool_)(this == o_ActivePlayer);}
};

NOALIGN struct _TownTowerLoaded_
{
  _byte_ field[36];
};


NOALIGN struct _Town_: _Struct_
{
 _int8_ id;
 _int8_ owner_id;
 _int8_ built_this_turn;
 _byte_ threatening_heroes;
 _int8_ type;
 _byte_ x;
 _byte_ y;
 _byte_ z;
 _byte_ boat_x;
 _byte_ boat_y;

 _word_ field_0A;

 _int_ up_hero_id;
 _int_ down_hero_id;

 _int8_ mag_level;
 _byte_ field_15;

 _word_ available_creatures[14];

 _byte_ isGrouped;
 _byte_ manaVortexFull;
 _dword_ pond_amount;
 _dword_ pond_resource;
 _dword_ summoningType;
 _word_ summoningPopulation;
 _word_ field_42;

 // настройка запрета заклинаний в редакторе карт в городе 0x5BEA52
 _dword_ spells[5][6];  // 0x44 размер 120
 _byte_ magic_hild[5];  // 0xBC

 _byte_ fields_C1[7];

 _char_ name[12];

  _dword_   spellDisabledMask[3]; 

  _Army_ guards; //+E0 = охрана замка
  _Army_ guards0; //+118 = охрана замка

  _dword_   built_bits; //*B +150h = уже построенные здания (0400)
  _dword_   built_bits2;
  _dword_   bonus_bits;//*B +158h = бонус на существ, ресурсы и т.п., вызванный строениями
  _dword_   bonus_bits2;
  _dword_   available_bits;      //*B- +160h = маска доступных для строения строений
  _dword_   available_bits2;     

 // normal

 char* GetTypeName() {return CALL_1(char*, __thiscall, 0x5C1850, this);}
 _Army_* GetUpArmy() {return CALL_1(_Army_*, __thiscall, 0x5C1860, this);}
 void SwapHeroes() {CALL_1(void, __thiscall, 0x5BE850, this);}
 void MoveHeroDown() {CALL_1(void, __thiscall, 0x5BE790, this);}
    
    // Построено ли в городе здание.
    inline _bool32_ IsBuildingBuilt(_int32_ building_id, _bool32_ unk_unused)
    {
      return CALL_3(_bool32_, __thiscall, 0x4305A0, this, building_id, unk_unused);
    }
};

// размер 136 байт на заклинание
NOALIGN struct _Spell_ 
{
 _int_ type;                 // -1 -enemy, 0 -area, +1 -friend
 _cstr_ wav_name;            //+4
 _int_ animation_ix;         //+8
 _dword_ flags;              //+C
 _cstr_   name;              // +10h
 _cstr_   short_name;        // +14h
 _int_    level;             // +18h
 _dword_  school_flags;      // +1Ch Air=1,Fire=2,Water=4,Earth=8
 _int_    mana_cost[4];      // +20h cost mana per skill level
 _int_    eff_power;         // +30h
 _int_    effect[4];         // +34h effect per skill level
 _int_    chance2get_var[9]; // +44h chance per class
 _int_    ai_value[4];       // +68h 
 _cstr_   description[4];    // +78h
};


NOALIGN struct _CreatureAnim_ // size = 84 Cranim.txt
{ 
  _int16_ i[6];
  _float_ f[18];  
};


NOALIGN struct _BattleStack_ : _Struct_  // размер 0x548 = 1352 байта
{
 _byte_ bShowAttackFrames;          // +0 
 _byte_ bShowRangeFrames;           // +1 
 _byte_ iShowAttackFrameType;       // +2 
 _byte_ iNextFrameType;             // +3 
 _byte_ iRemainingFrames;           // +4  
 _byte_ field_05[3];  // +5 выравнивание стуктуры 

 _int32_ iDrawPriority;             // +8 
 _byte_ bShowTroopCount;            // +12 0x0C 
 _byte_ field_0D[3];                // +13 0x0D выравнивание стуктуры

 _dword_ targetStackSide;           // +16 0x10 
 _dword_ targetStackIndex;          // +20 0x14
 _dword_ targetAttackLimit;         // +24 0x18

 _int32_ targetGexID;               // 28 +0x1C  позициякуда бежать/стрелять

 _byte_ isFireshield;               // +32 0x20 огненный щит
 _byte_ field_21[3];  // +33 0x21  выравнивание стуктуры 

 _int32_ clone_owner_stack_ix;          //+36  
 _int32_ clone_index;                   // +40 0x28 (номер стэка клона этого)
 // _List_<_int32_>* clones;            // Заменяем поле. Теперь это список клонов стека. 
 _dword_ clone_rounds_left_to_vanish;   // +44 0x2C (число раундов до исчезновения)

 _byte_ isMoving;  // +48 0x30 
 _byte_ letsPretendImNotHere;       // +49 0x31 
 _byte_ field_32[2];  // +50 0x30  выравнивание стуктуры

 _int32_ creature_id;               // +52 0x34 (тип монстра)
 _int32_ hex_ix;                    // +56 0x38  (позиция на поле боя) 
 _int32_ def_group_ix;              // +60 0x3C
 _int32_ def_frame_ix;              // +64 0x40

 _dword_ orientation;               // +68 0x44 направление монстра (1-как атакующий, 0-как защитник)
 _dword_ walkDirection;             // +72 0x48 ?

 _int32_ count_current;             // +76 0x4C (число монстров)
 _int32_ count_before_attack;       // +80 0x50 (число монстров до удара по ним в тек. атаку)
 
 _dword_ count_battle_resurrected;  // +84 0x54
 
 _int32_ lost_hp;                   // +88 0x58 потери здоровья последнего монстра
 _int32_ army_slot_ix;              // +92 0x5C номер слота of _Army_ (0...6), -1 - будет удален после битвы
 _int32_ count_at_start;            // +96 0x60 число монстров в начале битвы
 
 _dword_ base_speed;                // +100 0x64 базовая скорость с бонусами земли, спецов и т.д. По ней видимо вычисляются ускорение и замедление
 
 _dword_ anim_value;                // +104 0x68 = cranim.f[15] при инициализации
 _int32_ full_hp;                   // +108 0x6C полное здоровье (исп. как база для лечения)
 
 _bool32_ isLucky;                  // +112 0x70 в этом раунде была удача

//////////////////////////////////////////////////////////////////////////////////
 _CreatureInfo_ creature;
//////////////////////////////////////////////////////////////////////////////////
 //_int_ town;  //+116 0x74
 //_int_ level;  //+120 0x78
 //_char_* sound_name;  //+124 0x7C
 //_char_* def_name;  //+128 0x80
 //_int_ flags;  //+132 0x84
 //_char_* name_single;  //+136 0x88
 //_char_* name_plural;  //+140 0x8C
 //_char_* specification_description;  //+144 0x90
 //_int_ cost_wood;  //+148 0x94
 //_int_ cost_mercury;  //+152 0x98
 //_int_ cost_ore;  //+156 0x9C
 //_int_ cost_sulfur;  //+160 0xA0
 //_int_ cost_crystal;  //+164 0xA4
 //_int_ cost_jems;  //+168 0xA8
 //_int_ cost_gold;  //+172 0xAC
 //_int_ fight_value;  //+176 0xB0
 //_int_ AI_value;  //+180 0xB4
 //_int_ growth;  //+184 0xB8
 //_int_ horde_growth;  //+188 0xBC
 //_int_ hit_points;  //+192 0xC0
 //_int_ speed;  //+196 0xC4   
 //_int_ attack;  //+200 0xC8
 //_int_ defence;  //+204 0xCC
 //_int_ damage_min;  //+208 0xD0
 //_int_ damage_max;  //+212 0xD4
 //_int_ shots;  //+216 0xD8
 //_int_ spells_count;  //+220 0xDC
 //_int_ advmap_low;  //+224 0xE0
 //_int_ advmap_high;  //+228 0xE4
///////////////////////////////////////////////////////////////////////////////

 _byte_ show_fire_shield;       // +232 0xE8  (например у Ифритов он не отображается)
 _bool8_ isSomeKilled;          // +233 0xE9   =1, если умирал хоть один
 _bool8_ isAllKilled;           // +234 0xEA   =1, если был убит весь стэк

 _byte_ field_EB;  // +235 0xEB  выравнивание структуры

 _int32_ spellAfterAttack;    // +236 0xEC  номер заклинания существа в тек раунде 0x50 Acid breath
 
 _int32_ hitByCreature;         // +240 0xF0  _byte_=1 перед атакой на него 441434
 
 _int32_ side;                  // +244 0xF4  0 - attacker, 1 - defender 
 _dword_ index_on_side;         // +248 F8 dd = номер стэка у стороны на поле боя

 _dword_ iLastFidgetTime;       // +252 FC dd = ? что-то с магией
 _dword_ ySpecialMod;           // +256 100 dd 43DEA4
 _dword_ xSpecialMod;           // +260 104 dd 43DEAD
 _dword_ bPowSequenceComplete;  // +264 108 dd
 _dword_ yModify;               // +268 10C dd
 
 _CreatureAnim_ cr_anim;        // +272 0x110 
 _Def_* def;                    // +356 0x164 def монстра, загрузка: 43DA8E
 _Def_* def_shot;               // +360 0x168 def выстрела, загрузка: 43DA8E
 _dword_ image_height;          // +364 0x16С
 _Wav_* wav_move;               // +368 0x170 звук перемещения (move), загрузка: 43DA8E
 _Wav_* wav_attack;             // +372 0x174 звук атаки (attk/wnce/shot), загрузка: 43DA8E
 _Wav_* wav_wnce;               // +376 0x178 звук 'колдует' (wnce), загрузка: 43DA8E
 _Wav_* wav_shot;               // +380 0x17C звук выстрела (shot), загрузка: 43DA8E
 _Wav_* wav_kill;               // +384 0x180 звук смерти (kill), загрузка: 43DA8E
 _Wav_* wav_defend;             // +388 0x184 звук обороны (wnce/dfnd), загрузка: 43DA8E
 _Wav_* wav_ext1;               // +392 0x188 звук дополнительный 1 (ext1), загрузка: 43DA8E
 _Wav_* wav_ext2;               // +396 0x18С звук дополнительный 2 (ext2), загрузка: 43DA8E
 
 _dword_ turnsToNextMove;   // +400 0x190
 
 _int32_ active_spells_count;   // +404 0x194 dd = количество уже наложенных заклинаний
 _int32_ active_spell_duration[81]; // +408 0x198  есть заклинание (длительность) или нет
 _int32_ active_spells_power[81];   // +732 0x2DC (сила действия заклинания)
 
 _byte_ SpellInfluenceQueue[48];    // +1056 0x420 std::deque 

 _int32_ PaletteEffect;         // +1104 0x450  
 _int32_ retaliations;          // +1108 0x454 // 441B17 (кол-во ответов на атаку 0= не отв. на атаку)// настройка для грифонов 46D6A0
 _int32_ bless_value;           // +1112 0x458 Bless добавка к Max. Damage
 _int32_ curse_value;           // +1116 0x45C Curse убавка к Min. Damage
 _int32_ antimagic_value;       // +1120 0x460
 _int32_ bloodlast_value;       // +1124 0x464 Bloodlast добавка к Атаке с бонусами
 _int32_ precision_value;       // +1128 0x468 Precision добавка к Атаке с бонусами
 _int32_ weaknessPenalty;       // +1132 0x46C
 _int32_ stoneSkinBonus;        // +1136 0x470
 _int32_ disruptiverayPenalty;  // +1140 0x474
 _int32_ prayerBonus;           // +1144 0x478
 _int32_ mirthBonus;            // +1148 0x47C
 _int32_ sorrowPenalty;         // +1152 0x480
 _int32_ fortuneBonus;          // +1156 0x484
 _int32_ misfortunePenalty;     // +1160 0x488
 _int32_ slayerLevel;           // +1164 0x48C 
  
 _int32_ steps_to_target;       // +1168 0x490 dd (шаги до цели)
 _int32_ counerstrike_retaliations; // +1172 0x494 dd кол. доп. ответов на атаку, добавленных Counerstrike заклом
 
 _int32_ frenzyAdjust;          // +1176 0x498
 _int32_ blindFactor;           // +1180 0x49C
 _int32_ fire_shield_strength;  // +1184 0x4A0
 _float_ poison_penalty;        // +1188 0x4A4

 _int32_ protectionFromAirFactor;     // +1192 0x4A8
 _int32_ protectionFromFireFactor;    // +1196 0x4AC
 _int32_ protectionFromWaterFactor;   // +1200 0x4B0
 _int32_ protectionFromEarthFactor;   // +1204 0x4B4

 _int32_ shieldDamageFactor;    // +1208 0x4B8
 _int32_ airShieldDamageFactor; // +1212 0x4BC
 
 _bool8_ residualBlindness;     // +1216 0x4C0 db Blinded - снизить защиту (сбросить после?) при атаке на него (уст. перед ударом)
 _bool8_ residualParalyze;      // +1217 0x4C1 db Paralized - снизить защиту (сбросить после?) при атаке на него (уст. перед ударом)
 
 _bool8_ field4C2[2];  // +1218 0x4C2 выравнивание структур

 _int32_ forgetfulness_level;   // +1220 0x4C4 dd Forgetfulness - уровень (>2 - не может стрелять)
 _float_ slowPenalty;           // +1224 0x4C8
 _int32_ hasteBonus;            // +1228 0x4CС

 _int32_ diseaseDefensePenalty; // +1232 0x4D0
 _int32_ diseaseAttackPenalty;  // +1236 0x4D4
 
 _byte_ isNativeTerrain;        // +1240 0x4D8
 _byte_ field_4C9[3]; // +1241 0x4D9 выравнивание структуры
 
 _int32_ defend_bonus;          // +1244 0x4DC dd = величина бонуса при выборе защиты
 _int32_ faerie_dragon_spell;   // +1248 0x4E0 dd заклинание для сказ дракона

 _int32_ magicMirrorChance;     // +1252 0x4E4
 _int32_ morale;                // +1256  0x4E8 
 _int32_ luck;                  // +1260  0x4EC 

 _byte_ resetOnThisRound;       // +1264 0x4F0
 _byte_ isAreaEffectTarget;     // +1265 0x4F1

 _byte_ field_4F2[2]; // +1266 0x4F2 выравнивание структуры

 _List_<_int32_> binder_clients;         // +1268 0x4F4 (bound_armies std::vector)
 _List_<_int32_> binder_sources;         // +1284 0x504 (binder std::vector)
 _List_<_int32_> aura_clients;           // +1300 0x514 (aura_clients std::vector)
 _List_<_int32_> aura_sources;           // +1316 0x524 (aura_clients std::vector)

 _int32_ AI_expected_damage;    // +1332 0x534
 _int32_ AI_target;             // +1336 0x538
 _int32_ AI_target_value;       // +1340 0x53C
 _int32_ AI_target_distance;    // +1344 0x540
 _int32_ AI_possible_targets;   // +1348 0x544

 // normal
 inline void Construct(int creature_id, int count, _Hero_* hero_owner, int side, int index_on_side/*0 - 21*/, int position_hex_ix,  int army_slot_ix)
  {CALL_8(void, __thiscall, 0x43D5D0, this, creature_id, count, hero_owner, side, index_on_side, position_hex_ix, army_slot_ix);}

 inline _BattleStack_* Create() {return CALL_1(_BattleStack_*, __thiscall, 0x43CF70, this);} // need (_BattleStack_*)o_New(sizeof(_BattleStack_))
 inline void InitDefsAndWavs() {CALL_1(void, __thiscall, 0x43D710, this);}
 inline _int32_ InitSpells() {return CALL_1(_int32_, __thiscall, 0x43D2E0, this);}
 inline _int32_ Delete() {return CALL_1(_int32_, __thiscall, 0x43D120, this);}

 inline _int32_ GetFullHealth(_bool_ isAI) {return CALL_2(_int32_, __thiscall, 0x442DA0, this, isAI);}
 inline _int32_ GetSide() {return CALL_1(_int32_, __thiscall, 0x43FE60, this);}
 inline _Hero_* GetOwnerHero() {return CALL_1(_Hero_*, __thiscall, 0x4423B0, this);}
 inline _int32_ ResetSpell(_int32_ spell) {return CALL_2(_int32_, __thiscall, 0x444230, this, spell);}

 // получение базового урона монстром
  inline _int32_ Calc_Damage_Base(_bool_ isTeoretic = TRUE)
  {
   return CALL_2(_int32_, __thiscall, 0x442E80, this, isTeoretic);
  }
 
 // Подсчёт добавок к наносимому урону (возвращается новый урон).
 // Enemy - указатель на атакуемый стек.
 // BaseDamage - начальный урон.
 // IsShot - является ли атака выстрелом (TRUE - является).
 // Virtual - является ли подсчёт производимым ИИ (TRUE - является).
 // WayLength - пройденный путь до цели (для расчёта кавалерийского бонуса).
 // out_FireshieldDamage - указатель на переменную, в которую в результате работы функции запишется урон от огненного щита (0 - не подсчитывать).
 inline _int32_ Calc_Damage_Bonuses(_BattleStack_* enemy, _int32_ BaseDamage, _bool8_ IsShot, _bool8_ Virtual, _int32_ WayLength, _int32_* out_FireshieldDamage)
 {
   return CALL_7(_int32_, __thiscall, 0x443C60, this, enemy, BaseDamage, IsShot, Virtual, WayLength, out_FireshieldDamage);
 }

 // Проиграть анимацию заклинания на стеке
 inline _int_ PlayMagicAnimation(_int_ spell_anim_id, _byte_ is_show_damage = 0)
 {
  return CALL_5(_int_, __thiscall, 0x4963C0, o_BattleMgr, spell_anim_id, this, 100, is_show_damage);
 } 

  // проиграть анимацию заклинания на активном стеке (почему их 2 функции?)
 inline _byte_ PlayMagicAnimation2(_int_ spell_anim_id, _int_ is_show_damage = 0) 
 {
    return CALL_3(_byte_, __thiscall, 0x468570, o_BattleMgr, spell_anim_id, is_show_damage);
 } 

 // Проиграть анимацию самого стека 
  inline _byte_ PlayStackAnimation(_int_ anim_id, _int_ is_restore_state)
 {
  if (is_restore_state) // если необходимо восстановить исходную стойку
  {
    CALL_4(_byte_, __thiscall, 0x446660, this, anim_id, -1, 0);
    return CALL_4(_byte_, __thiscall, 0x446660, this, 2, 1, 0); 
  } else return CALL_4(_byte_, __thiscall, 0x446660, this, anim_id, -1, 0);
 } 

 // Сделать этот стек активным
 inline void SetActiveThisStack()
 {
   return CALL_3(void, __thiscall, 0x464F10, o_BattleMgr, this->side, this->index_on_side);
 }

 // переместить стек (если не хватает дальности хода, стек не двинется)
inline _byte_ Move(_int_ gex_id)
 {
   return CALL_3(_byte_, __thiscall, 0x445A30, this, gex_id, 0);
 }

 // поворот стека в противоположную сторону
 inline _byte_ Rotate()
 {
   return CALL_2(_byte_, __thiscall, 0x445A30, this, 1);
 }

 // Атаковать стеком (врукопашную)
 inline _byte_ Attack_Melee(_BattleStack_* enemy)
 {
   return CALL_3(_byte_, __thiscall, 0x441330, this, enemy, 2);
 }

 // Атаковать стеком (стрелять) 
 inline void Attack_Shoot(_BattleStack_* enemy)
 {
   return CALL_2(void, __thiscall, 0x43F620, this, enemy);
 }

 // Отрисовка выстрела стека по противнику и полёта снаряда.
 inline void Draw_Shot(_BattleStack_* enemy)
 {
   CALL_2(void, __thiscall, 0x43EFE0, this, enemy);
 }

 // может ли стрелять с проверкой на врага рядом
  _bool8_ CanShoot(_BattleStack_* aim = NULL) 
  {
    return CALL_2(_bool_, __thiscall, 0x442610, this, aim);
  }

  // впринципе умеет ли стрелять (без проверки на врага рядом)
  _bool8_ CanShoot2(_BattleStack_* aim = NULL) 
  {
    if (this->creature_id == CID_ARROW_TOWER)
        return TRUE;
    if ( (this->creature.flags & BCF_CAN_SHOOT) && this->creature.shots > 0)
        return TRUE;

    return FALSE;
  }
 
 // Получение второго гекса, занимаемого стеком (если стек 1-клеточный, первого).
 inline _int32_ GetSecondGexID()
 {
   return CALL_1(_int32_, __thiscall, 0x4463C0, this);
 } 
 
 // Уничтожение стека.
 // dead_itself - умер ли стек сам собой (например, как клон при гибели хозяина или окончании длительности заклинания).
 inline void Die(_bool8_ dead_itself)
 {
   CALL_2(void, __thiscall, 0x443E40, this, dead_itself);
 }

  // получение скорости стека
  inline _int_ GetSpeed()
  {
    return CALL_1(_int_, __thiscall, 0x4489F0, this);
  }

  // может ли дойти стек до цели
  inline _int_ CanReachToTarget(int gex_target, int a3 = 0, int a4 = 0)
  {
    return CALL_4(_int_, __thiscall, 0x446960, this, gex_target, a3, a4);
  }

  // получить иммунитет существа
  // caster_type: 0 - герой 1 - монстр, 2 - арт 
  inline double GetResistMagic(int spell_id, int side, char a5, char a6, int caster_type)
  {
    return CALL_7(double, __thiscall, 0x5A83A0, o_BattleMgr, spell_id, side, this, a5, a6, caster_type);
  }

  // получить ослабление силы магии (големы)
  inline int GetResistGolem(int spell_id, int damage)
  {
    return CALL_3(int, __fastcall, 0x44B180, damage, spell_id, this->creature_id);
  }

  // получить получить ослабление силы магии (защита от воды и т.п.)
  inline int GetResistSpellProtection(int spell_id, signed int damage)
  {
    return CALL_3(int, __stdcall, 0x5A7EC0, damage, spell_id, this);
  }

  // получить силу магии командира WoG
  inline int GetNPCMagicPower()
  {
    return CALL_1(int, __cdecl, 0x76BEEA, this);
  }

  // может ли колдовать как Сказочный Дракон
  inline _bool8_ CanCastSpellAkaFaerieDragon()
  {
    if (this->faerie_dragon_spell && this->creature.spells_count) 
    {
      return TRUE;
    }
    return FALSE;
  }

  // может ли колдовать как Элементаль
  inline _bool8_ CanCastSpellAkaElemental()
  {
    if (this->creature.spells_count) 
    {
      if (this->creature_id == CID_MASTER_GENIE ||
          this->creature_id == CID_OGRE_MAGE ||
          this->creature_id == CID_ICE_ELEMENTAL ||
          this->creature_id == CID_MAGMA_ELEMENTAL ||
          this->creature_id == CID_STORM_ELEMENTAL ||
          this->creature_id == CID_ENERGY_ELEMENTAL )
      {
        return TRUE;
      }
    }
    return FALSE;
  }

  // может ли монстр колдовать на позицию
  inline _bool8_ CanCastToGex(int targetPos)
  {
    return CALL_2(_bool8_, __thiscall, 0x4473E0, this, targetPos);
  }

 // может ли монст колдовать на поле боя (расширенная функция указанной выше)
 _bool8_ CanCastToBattleField()
 {
  _bool8_ result = FALSE;
  for(int i=0; i<=187; i++) {
    if(this->CanCastToGex(i)) {
      result = TRUE;
      break;
    }
  }
  return result;
 }

 // можно ли кастовать на монстра
 // 5A3F90 bool __thiscall CombatMan_CanUseSpell(_BattleMgr_ *this, int spell, int side, _BattleStack_ *targetMon, int a5, int a6)
  inline bool CanUseSpell(int spell_id, int side, char a5, int caster_type)
 {
   return CALL_6(bool, __thiscall, 0x5A3F90, o_BattleMgr, spell_id, side, this, a5, caster_type);
 }

 // получить кол-во воскрешаемых существ (Архангелы или Пит-Лорды)
 inline int Get_Resurrect_Count(_BattleStack_* stack_target)
 {
   return CALL_2(int, __thiscall, 0x447050, this, stack_target);
 }
 
 // Получение номера стрелковой башни стека (-1 - стек не является стрелковой башней).
 inline _int32_ Get_ArrowTowerNum()
 {
   // Выбираем номер стрелковой башни в зависимости от её позиции (стандартный способ игры).
   switch (this->hex_ix)
   {
     case 254:
       return 0;
     case 251:
       return 1;
     case 255:
       return 2;
     default:
       return -1;
   }
 }

 // WOG ФУНКЦИИ 
 #define WOG_IS_HARPY *(_byte_*)0x75E05B
 #define WOG_IS_HARPY_HAG *(_byte_*)0x75E060
 #define WOG_IS_DARKNESS_DRAGON *(_dword_*)0x75E064
 _bool8_ WOG_isHarpy()
 {
  if( this->creature_id == WOG_IS_HARPY ||
      this->creature_id == WOG_IS_HARPY_HAG ||
      this->creature_id == WOG_IS_DARKNESS_DRAGON ||
      CALL_1(int, __cdecl , 0x71E433, this) 
  ) {
    return TRUE;
  }
  return FALSE;
 }
};


// Структура стрелковой башни в бою.
NOALIGN struct _ArrowTower_
{
  _int32_ CreatureType; // +0h; Тип существа башни
  _Def_* Def; // +4h; Загруженный def существа башни
  _Def_* BulletDef; // +8h; Загруженный def снаряда башни
  _int32_ X_Position; // +Ch; Позиция изображения центра существа башни по горизонтали в пикселях
  _int32_ Y_Position; // +10h; Позиция изображения низа существа башни по вертикали в пикселях
  _int32_ Orientation; // +14h; Направление (0 - вправо, 1 - влево)
  _int32_ AnimSectionNum; // +18h; Номер секции кадров анимации башни
  _int32_ AnimFrameNum; // +1Ch; Текущий кадр секции анимации башни
  _int32_ StackNum; // +20h; Номер стека башни (сторона-владелец - всегда 1)
};

// Структура боевого элемента замка (массив из 8-ми элементов по 0x63BE60).
NOALIGN struct _CastleElement_
{
  _int16_ GexNum; // +0h; Позиция элемента (используется при его выборе как цели атаки)
  _int16_ SecondGex_Row; // +2h; Ряд второй позиции элемента (-1 - нет)
  _int16_ X_Position; // +4h; Горизонтальная позиция элемента в пикселях
  _int16_ Y_Position; // +6h; Вертикальная позиция элемента в пикселях
  _int32_ CastleDrawingPartNum; // +8h; Номер элемента замка среди всех отрисовывающихся частей замка
};

// структура боевого гекса на поле боя
// размер 112 байт на каждый из 187 гексов
NOALIGN struct _BattleHex_: _Struct_ 
{
 _int16_ X_Position; // +0h; Позиция центра гекса по горизонтали в пикселях
 _int16_ Y_Position; // +2h; Позиция низа гекса по вертикали в пикселях
 _int16_ Left; // +4h; X-координата левой границы гекса
 _int16_ Top; // +6h; Y-координата верхней границы гекса
 _int16_ Right; // +8h; X-координата правой границы гекса
 _int16_ Bottom; // +Ah; Y-координата нижней границы гекса
 _byte_ field_C[4]; //?
 _int32_ Flags; // +10h; Флаги гекса (1 - есть ли препятствие)
 _int_ ObstacleNum; // +14h; Номер препятствия, находящегося на стеке (-1 - нет)
 _byte_ bstack_side;
 _byte_ bstack_index;
 _byte_ field_1A[86]; //?
 
 // normal
 _BattleStack_* GetCreature() {return CALL_1(_BattleStack_*, __thiscall, 0x4E7230, this);}
};

NOALIGN struct _BattleHexAdjacent_
{
  // _int16_ topRight;
  // _int16_ right;
  // _int16_ bottomRight;
  // _int16_ bottomLeft;
  // _int16_ left;
  // _int16_ topLeft;
  _int16_ hexAdjacent[6];
};


// Структура боевой анимации.
NOALIGN struct _BattleAnim_
{
  _cstr_ DefName; // Имя def`а анимации
  _cstr_ TouchEffect_Name; // Имя тактильного эффекта анимации (для его воспроизведения на нестандартных элементах управления с помощью IFC20.dll)
  _dword_ Properties; // Свойства боевой анимации (по несколько битов)
  // ***
  // Начало описания свойств анимации
  // ***
    // (сдвиг - размер в битах - значение) 
    // 0 - 4 - Позиция отображения (0 - от земли на стеке или гексе, 1 - посередине гекса или стека, 2 - выше стека, 3 - перед стеком, 4 - с нижней и левой границы гекса, -1 - нет позиции)
    // 4 - 4 - Не используется
    // 8 - 1 - Прозрачность (0 - нет, 1 - есть)
    // 9 - 23 - Не используется
  // ***
  // Конец описания свойств анимации
  // ***
};

// Менеджер работы с другими менеджерами (размер - 16)
NOALIGN struct _ExecMgr_ : _Struct_
{
  // _Manager_ см. HoMM3_GUI.h
  _Manager_* previous;
  _Manager_* next;
  _Manager_* field_8;
  _Manager_* field_C;

  _byte_ CallManager(_Manager_* mgr)  { return CALL_2(_byte_, __thiscall, 0x4B09D0, this, mgr); }
  _int32_ PushManager(_Manager_* mgr) { return CALL_2(_int32_, __thiscall, 0x4B0770, this, mgr); }
  _int32_ AddManager(_Manager_* mgr)  { return CALL_3(_int32_, __thiscall, 0x4B0880, this, mgr, -1); }
  void RemoveManager(_Manager_* mgr)  { return CALL_2(void, __thiscall, 0x4B0950, this, mgr); }
};

#define o_SwapMan_SplitArmyStack (*(_bool_*)0x6A3D68)
// размер 104 байта
NOALIGN struct _SwapMgr_ : _Struct_
{
  _Manager_ mgr;       // 0...56
  _Dlg_* &dlg;            // +56
  _Pcx8_* pcx8_sel_rect;  // +60
  _Hero_* hero[2];        // +64
  _int32_ heroSelected;   // +72
  _int32_ heroClicked;    // +76
  _int32_ clickedCreatureSlot; // +80
  _int32_ slotClicked;    // +84
  _bool8_ isSelectedSlot; // +88
  _byte_ field_59[3];     // +89 (выравнивание)
  _byte_ isNetworkPlayer; // +5C (0-none; 1-yes)
  _byte_ networkPlayerID; // +5D (player id to network)
  _byte_ field_5E[2];     // +5E (выравнивание)
  _int_ unknown60;        // +60
  _int_ unknown64;        // +64
};


NOALIGN struct _BattleMgr_ : _Struct_
{
  _Manager_ mgr;      // 0...56
  _byte_ field_38[4]; // +56 (что-то из manager)

  enum BATTLE_ACTION
  {
    BA_CANCEL,
    BA_HERO_CAST_SPELL,
    BA_WALK,
    BA_DEFEND,
    BA_RETREAT,
    BA_SURRENDER,
    BA_WALK_ATTACK,
    BA_SHOOT,
    BA_WAIT,
    BA_CATAPULT,
    BA_MONSTER_SPELL,
    BA_FIRST_AID_TENT,
    BA_NOTHING //12 = No action(can be to disable stack for this round)
  };

  _int32_ action;                 // +60 (BG:A)
  _int32_ actionParam;            // +64
  _int32_ actionTarget;           // +68
  _int32_ actionParam2;           // +72
  _byte_ iLastDrawGridShade[187]; // +76
  _byte_ iCurDrawGridShade[187];  // +263
  _byte_ f_1C2[2];                // +450 (выравнивание)
  _BattleHex_ hex[187];           // +452 (112*187)
  _int32_ combatTerrain;          // +21396
  _int32_ combatFringe;           // +21400
  _int32_ iCombatCycleType;       // +21404
  _int32_ iElevationOverlay;      // +21408
  _bool32_ iDoorStatus;           // +21412
  _bool32_ bMoatOn;               // +21416
  _bool32_ moatIsWide;            // +21420
  _Pcx16_* saveScreenPreGrid;     // +21424 (Bitmap16Bit*)
  _Pcx16_* saveScreenPostGrid;    // +21428
  _Pcx16_* combatMouseBackground; // +21432
  _MapItem_* MapItem;             // +21436
  _int32_ special_Ground;         // +21440
  _bool8_ antiMagic_Garrison;     // +21444
  _bool8_ isBank;                 // +21445
  // _bool8_ f_53C6[2];           // +21446 (выравнивание)
  _int16_ seed;                   // +21446 я (igrik) сохраняю сюда зерно
  _Town_* town;                   // +21448
  _Hero_* hero[2];                // +21452
  _int32_ heroSpellPower[2];      // +21460
  _bool32_ playDoh;               // +21468
  _bool32_ playYeah;              // 21472
  _int32_ heroFrameType[2];       // +21476
  _int32_ heroFrameIndex[2];      // +21484
  _int32_ heroDataSet[2];         // +21492
  _dword_ heroLastFidgetTime[2];  // +21500
  _Def_* heroDefLoaded[2];        // +21508
  _Def_* heroFlagLoaded[2];       // +21516
  _int32_ heroFlagCadre[2];       // +21524
  _int32_ heroUpdateRect[2][4];   // +21532
  _int32_ heroFlagUpdateRect[2][4]; // +21564
  _List_<_int32_> EagleEyeSpellLearned[2]; // +21596 (H3Vector<INT32>)
  _byte_ armyEffected[2][20];     // +21668
  _bool8_ isHuman[2];             // +21668 (isNotAI[2])
  _bool8_ isLocalHuman[2];        // +21670 (isHuman[2])
  _int32_ playerID[2];            // +21672 (owner_id[2])
  _bool8_ hasArtifactAutoCast[2]; // 21680
  _byte_ f_54B2[2];         // +21682 (выравнивание)
  _bool32_ isCasted[2];           // +21684 (sideIsCasted[2])
  _int32_ countMonsters[2];       // +21692 (stacks_count[2])
  _Army_* army[2];                // +21700
  _BattleStack_ stack[2][21];     // +21708
  _bool8_ onNativeTerrain[2];     // +78492
  _byte_ f_1329E[2];      // +78494  (выравнивание)
  _int32_ turnsSinceLastEnchanterCast[2]; // +78496
  _int32_ summonedElemental[2];   // +78504
  _bool8_ sideRetreated[2];       // +78512
  _bool8_ sideSurrendered[2];     // +78514
  _int32_ gbThisNetHasControl;    // +78516 (netControl_BG_A)
  _int32_ currentStackSide;       // +78520 (current_stack_side)
  _int32_ currentStackIndex;      // +78524 (current_stack_ix)
  _int32_ currentActiveSide;      // +78528 (current_side)
  _int32_ autoCombatOn;           // +78532
  _BattleStack_* activeStack;     // +78536
  _BattleStack_* highlightedStack; // +78540
  _int32_ lastHexIndex;           // +78544
  _int32_ lastMoveToIndex;        // +78548
  _int32_ attackerHexIndex;       // +78552
  _int32_ lastCommand;            // +78556
  _int32_ combatCommand;          // +78560
  _int32_ castleAttackDone;       // +78564
  _Def_* currentSpellDef;         // +78568
  _int32_ currentSpellID;         // +78572
  _int32_ currentSpellDefFrame;   // +78576
  _int32_ numShootingTowers;      // +78580
  _int32_ isBattleOver;           // +78584
  _Dlg_* dlg;                     // +78588
  _int32_ bCombatShowIt;          // +78592 
  _dword_* iconWidgetWL[25];      // +78596 (iconWidget = _DlgStaticDef_?)
  _dword_* textWidgetWL[25];      // +78696 (textWidget = _DlgStaticText_?)
  _int32_ attackCursorEnumType[12];  // +78796
  _int32_ attackHex[12];          // +78844
  _int32_ lastAttackCursorEnumType; // +78892
  _int32_ iTtlCombatDirections;   // +78896
  _int32_ iBackgroundFrame;       // +78900
  _bool8_ bCreatureIsDead[2][20]; // +78904 (для воскрешения неэкспертной землёй?)
  _bool8_ bSomeCreaturesVanish;   // +78944 (для воскрешения неэкспертной землёй?)
  _byte_ f_13461[3];              // +78945 (выравнивание)
  char* backPcxName;              // +78948
  _BattleHexAdjacent_ adjacentSquares[187];    // +78952 (_BattleHexAdjacent_ adjacentSquares[187])
  _int32_ saveBiggestExtent;      // +81196
  _int32_ limitToExtent;          // +81200
  _int32_ computeExtentOnly;      // +81204
  _int32_ extent[4];              // +81208 (RECT = size 16 bytes)
  _int32_ sideWinner;             // +81224
  _int32_ necromanty_Count;       // +81228
  _int32_ necromanty_Type;        // +81232
  _dword_* NumberWindow;          // +81236
  _List_<_int32_> Obstacles;      // +81240 (_H3Vector_<H3Obstacle>)
  _bool8_ isTactics;              // +81256
  _byte_ f_13D69[3];              // +81257 (выравнивание)
  _int32_ round;                  // +81260
  _int32_ tacticsDifference;      // +81264
  _bool8_ cheatNoSpellLimit;      // +81268
  _bool8_ cheatShowHiddenObjects; // +81269
  _bool8_ cheatShowBlockedHexes;  // +81270
  _byte_ f_13D77;                 // +81271 (выравнивание)
  _TownTowerLoaded_ Towers[3];    // +81272 ( struct TownTowerLoaded (size 0x24h)
  _bool8_ waitPhase;              // +81380
  _byte_ f_13DE5[3];              // +81381 (выравнивание)
  _int32_ defenderHeroOriginalPSkill[4];  // +81384 (герой защитник: сохранить атаку до битвы)
  char* wallImagesNames[90];      // +81400
  _int32_ wallLevel[18];          // +81760
  _int32_ wallFrame[18];          // +81832
  _int32_ mapPoint;               // +81904 (пакованные координаты битвы)
  _Pcx8_* combatCellGrid;         // +81908
  _Pcx8_* combatCellShaded;       // +81912
  _int32_ obstacleAnimationFrame; // +81916
  _bool8_ redrawCreatureFrame[40];// +81920
  _bool8_ redrawHeroFrame[2];     // +81960
  _bool8_ redrawFlagFrame[2];     // +81962
  _bool8_ redrawTowersFrame[3];   // +81964
  _bool8_ askRunBattle;           // +81967
  _bool8_ anyActionTaken;         // +81968
  _byte_ creaturePath[187];       // +81969

 // normal
 //inline _Def_* LoadSpellAnimation(int spell_anim_ix)
 inline int GetHexIxAtXY(int x, int y) {return CALL_2(int, __stdcall, 0x464380, x - dlg->x, y - dlg->y);}
 inline void CastSpell(int spell_id, int hex_ix, int cast_type_012, int hex2_ix /*для телепорта и жертвы*/, int skill_level, int spell_power)
  {CALL_7(void, __thiscall, 0x5A0140, 
    this, spell_id, hex_ix, cast_type_012, hex2_ix, skill_level, spell_power);} 

// может ли впринципе сторона колдовать любое заклинание
  inline _bool8_ CanUseAnySpell(int side, _byte_ isHeroCaster)
 {
   return CALL_3(_bool8_, __thiscall, 0x41FA10, this, side, isHeroCaster);
 }

 // даём игроку управление для поиска цели уже выбранного заклинания
  inline void UserChooseSpellTarget(int spell, int position)
 {
   return CALL_4(void, __fastcall, 0x59EF60, this, position, spell, 0);
 }

 // скрытая ли битва: 0=видимая, 1=скрытая
  inline _bool8_ IsHiddenBattle()
 {
   return CALL_1(_bool8_, __thiscall, 0x46A080, this);
 }
 
 // Проверка необходимости отрисовки битвы.
 // При необходимости отрисовки возвращает FALSE, иначе TRUE.
 inline _bool8_ ShouldNotRenderBattle()
 {
   return CALL_1(_bool8_, __thiscall, 0x46A080, this);
 }

 // проиграть анимацию заклинания на активном стеке
 inline _byte_ StackActive_PlaySpellAnimation(_int_ spell_anim_id, _int_ play_damage_to_stack = 0) 
 {
    return CALL_3(_byte_, __thiscall, 0x468570, this, spell_anim_id, play_damage_to_stack);
 }

 // поставить тень курсора на гекс
 inline _int32_ SetCursorShadowOnGex(_int32_ GexID)
 {
  return CALL_1(_int32_, __fastcall, 0x59FA10, GexID);
 }

 // поставить тень курсора по площади
 // НЕДОПИСАННАЯ ФУНКЦИЯ! Не использовать!!!
 _int32_ SetCursorShadowOnArea_SplashShoot(_int32_ centerGexID)
 {
     // o_MouseMgr->SetMouseCursor(SPL_FIREBALL + 1, 3);
     // CALL_3(void, __thiscall, 0x50CEA0, o_MouseMgr, SPL_FIREBALL + 1, 3);
     _bool8_ status = true;

     AddHintSpell(SPL_FIREBALL, centerGexID);

     if (!status)
     {
        MouseMove(centerGexID);
        return centerGexID;
     }

     return centerGexID;
 }

 // поставить тень курсора по площади
 _int64_ SetShadowSettings_OnSquare(_bool8_ redraw)
 {
    _int_ save1 = o_Battle_MovementShadow;
    _int_ save2 = o_Battle_CursorShadow;
    // _int_ save3 = o_Battle_ShowGrid;

    _int64_ result = CALL_4(_int64_, __thiscall, 0x4798F0, this, o_Battle_ShowGrid, 1, redraw);

    o_Battle_MovementShadow = save1;
    o_Battle_CursorShadow = save2;
    // o_Battle_ShowGrid = save3;
    // b_WriteRegistry();
    return result;
 }

 // движение мыши в бою на гекс
 inline _byte_ MouseMove(_int32_ GexID)
 {
  return CALL_2(_byte_, __thiscall, 0x477550, this, GexID);
 }

 // получить тип курсора в бою
 inline _int32_ GetCursorFrame(_int32_ GexID)
 {
  return CALL_2(_int32_, __thiscall, 0x475DC0, this, GexID);
 }

 // добавить хинт действия в битве (в лог битвы) НЕ сохранится в логе
 // в зависимости от типа действия (считывается из кадра курсора мыши)
 inline void AddHintMessage_ByCursorFrame(_int32_ cursor_frame)
 {
  CALL_2(void, __thiscall, 0x4923C0, this, cursor_frame);
 }

 // добавить статус действия в битве (в лог битвы) сохранится в логе
 inline void AddStatusMessage(const char* statusbar_text)
 {
    return CALL_4(void, __thiscall, 0x4729D0, this->dlg, statusbar_text, 1, 0);
 } 

 // добавить хинт действия в битве (в лог битвы) НЕ сохранится в логе
 inline void AddHintMessage(const char* statusbar_text)
 {
    return CALL_4(void, __thiscall, 0x4729D0, this->dlg, statusbar_text, 0, 1);
 }

 // добавить хинт действия от заклинания в битве (в лог битвы) НЕ сохранится в логе
 inline void AddHintSpell(_int_ spell_id, _int_ hex_id)
 {
    return CALL_4(void, __thiscall, 0x5A89A0, this, spell_id, hex_id, 1);
 }

 // получить в текст урона, который можно записать в лог битвы
 inline _HStr_* GetHintMessage_AttackDamage(_HStr_* H3Str, _BattleStack_* atacker, _BattleStack_* target, _bool8_ isShoot, _int32_ stepsToTarget)
 {
  return CALL_5(_HStr_*, __fastcall, 0x492F50, H3Str, atacker, target, isShoot, stepsToTarget);
 }

 // Сделать стек активным
 inline void SetActiveStack(_int_ side, _int_ index_on_side)
 {
   return CALL_3(void, __thiscall, 0x464F10, this, side, index_on_side);
 }

 // Проиграть магическую анимацию на определенном гексе поля боя
 inline _byte_ PlayMagicAnimationOnGEX(_int_ anim_id, _int_ gex_id)
 {
  return CALL_5(_byte_, __thiscall, 0x496590, this, anim_id, gex_id, 100, 1);
 }
 
 // Сброс полей необходимости перерисовки.
 inline void ClearRedrawFields()
 {
   return CALL_1(void, __thiscall, 0x493290, this);
 } 
 
 // Указание необходимости перерисовки при следующей отрисовке для стека - стрелковой башни.
 inline void SetArrowTowerToRedraw(_BattleStack_* Stack)
 {
   return CALL_2(void, __thiscall, 0x46A040, this, Stack);
 }

 // получение прямого расстояния между двумя гексами (без учёта препятствий)
 inline _int_ GetDistance(_int_ gex_start, _int_ gex_finish)
 {
   return CALL_2(_int_, __fastcall, 0x469250, gex_start, gex_finish);
 } 
 
 // Определение границ перерисовки для кадра def`а.
 inline void SetSpecRedrawBorders(_Def_* Def, _int_ DefGroupNum, _int_ FrameNum, _int_ X_Pos, _int_ Y_Pos, _RedrawBorders_* out_Borders, _bool_ Reflected, _bool_ NeedAddToGlobalBorders)
 {
   CALL_9(void, __thiscall, 0x495AD0, this, Def, DefGroupNum, FrameNum, X_Pos, Y_Pos, out_Borders, Reflected, NeedAddToGlobalBorders);
 }
  
 // Вычисление границ необходимости обновления экрана на основе полей необходимости перерисовки боевых элементов.
 inline void SetRedrawBorders()
 {
   CALL_1(void, __thiscall, 0x495770, this);
 } 
 
 // Отрисовка поля боя.
 // Flip - необходимость обновления экрана.
 // SetBattleRedraws - необходимость настройки границ обновления экрана.
 // UseBattleRedraws - необходимость использования границ обновления экрана (при SetBattleRedraws = TRUE игнорируется, считаясь TRUE).
 // WaitingTime - время, на ожидание которого надо настроить следующую отрисовку (игнорируется при Wait = FALSE).
 // RedrawBackground - необходимость перерисовки заднего плана (и стёрки старого изображения).
 // Wait - необходимость ожидания. В случае FALSE время ожидания для следующей отрисовки не меняется.
 inline void RedrawBattlefield(_bool8_ Flip, _bool8_ SetBattleRedraws, _bool8_ UseBattleRedraws, _int_ WaitingTime, _bool8_ RedrawBackground, _bool8_ Wait)
 {
   return CALL_7(void, __thiscall, 0x493FC0, this, Flip, SetBattleRedraws, UseBattleRedraws, WaitingTime, RedrawBackground, Wait);
 } 
 
 inline _int32_ RedrawGrid()
 {
  return CALL_3(_int32_, __thiscall, 0x4934B0, o_BattleMgr, 0, 1);
 }

  inline void Redraw()
 {
  return RedrawBattlefield(1, 0, 0, 0, 1, 0);
 }

 // Обновление всего поля боя.
 inline void FlipBattlefield()
 {
   CALL_1(void, __fastcall, 0x493300, this);
 }

 inline void Highlight_Hex(int gex_id = -1, signed int item = -1) 
 {
  CALL_3(void, __thiscall, 0x493F10, this, gex_id, item);
 } 
 
 // Инициализация переменных, управляющих временем случайных анимаций.
 inline void InitRandAnimsTimes()
 {
   CALL_1(void, __thiscall, 0x479860, this);
 } 
 
 // Проигрывание одного кадра анимации ожидания поля боя.
 // Это анимация флагов героев, анимация самих героев, случайная анимация существ, мигающая рамка вокруг стеков.
 inline void PlayWaitAnim()
 {
   CALL_1(void, __thiscall, 0x495C50, this);
 }
  
 // Проигрывание одного кадра анимации ожидания поля боя только в случае наступления времени.
 inline void PlayWaitAnimOnce()
 {
   CALL_1(void, __thiscall, 0x473970, this);
 } 
 
 // Нанесение урона элементу замка по его номеру.
 inline void DamageCastleElement(_int_ CastleElementNum, _int_ Damage)
 {
   CALL_3(void, __thiscall, 0x465570, this, CastleElementNum, Damage);
 }

 inline _bool8_ Get_StackShoot_ObstacklePenalty(_BattleStack_* stack, _int32_ stackHexID, _int32_ gexTargetID)
 {
  return CALL_4(_bool8_, __thiscall, 0x4670F0, this, stack, stackHexID, gexTargetID);
 }
 
 inline _bool8_ Get_StackShoot_DistancePenalty(_BattleStack_* stack, _BattleStack_* target)
 {
  return CALL_3(_bool8_, __thiscall, 0x4671E0, this, stack, target);
 }
 
 // Удаление стека с гекса, на котором он стоит.
 inline void RemoveStackFromGexes(_BattleStack_* stack)
 {
   CALL_2(void, __thiscall, 0x468310, this, stack);
 } 
 
 // Постановка стека на гекс.
 inline void PutStackToGex(_BattleStack_* Stack, _int_ GexNum)
 {
   CALL_3(void, __thiscall, 0x4683A0, this, Stack, GexNum);
 }
 
 // Удаление препятствия.
 inline void RemoveObstacle(_int_ ObstacleNum)
 {
   CALL_2(void, __thiscall, 0x466710, this, ObstacleNum);
 }

 // проверка препятствий на гексе (0-пуст, 1-занят)
 inline _byte_ IsGexNotObstacle(_int_ gexID)
 {
    // проверяем, правильно ли передали в функцию номер гекса
    if (gexID <= 0 || gexID > 187)
      return 1; // не правильно, значит гекс занят

   return CALL_2(_byte_, __thiscall, 0x4695F0, this, gexID);
 }

  // функция проверки гекса на занят ли он (0-пуст, 1-занят)
  _byte_ IsGexNotFree(_int_ gexID)
  {
    // проверяем, правильно ли передали в функцию номер гекса
    if (gexID <= 0 || gexID > 187)
      return 1; // не правильно, значит гекс занят

    // проверяем есть ли живой стек в этом гексе
    _BattleStack_* stack = this->hex[gexID].GetCreature();
    if ( stack && stack->count_current > 0 )
      return 1; // стек с кол-вом существ больше нуля существует

    // теперь пусть работает SOD функция: есть ли на этом гексе стена или препятствие
    // она тоже возвращает, что гекс (0-пуст, 1-занят)
    return CALL_2(_byte_, __thiscall, 0x4695F0, this, gexID);
  }

  _int32_ GetEmptySquareAroundThis(_int32_ centerGex, _int32_ adjacentGexID)
  {
    // по умолчанию: гекс не найден
    int result = -1; 

    // оригинал: return CALL_2(signed int, __fastcall, 0x524370, centerGex, adjacentGexID);

    // если вышли за границы поля битвы: возвращаем "гекс не найден"
    if (centerGex <= 0 || centerGex > 187)
      return result;
    
    // получаем номер соседнего гекса из массива менеджера битвы
    result = this->adjacentSquares[centerGex].hexAdjacent[adjacentGexID];

    // если вышли за границы поля битвы: возвращаем "гекс не найден"
    if (result <= 0 || result > 187)
      result = -1;

    // проверяем гекс на препятсвия и другие гексы
    // 0 = гекс пуст
    // 1 = гекс занят
    if ( IsGexNotFree(result) )
      result = -1;
    
    // возвращаем id найденного гекса
    return result;
  }

 // проверить подконтролен ли стек ИИ
 inline _bool8_ IsStackAutoControlledByAI(_BattleStack_* stack)
 {
   return CALL_2(_bool8_, __thiscall, 0x474520, this, stack);
 }

 // получение мертвого стека (живое существо) на гексе поля боя
 inline _BattleStack_* Get_BattleStack_Resurrect(int side, int gex_id, int is_creature_cast)
 {
   return CALL_4(_BattleStack_*, __thiscall, 0x5A3FD0, this, side, gex_id, is_creature_cast);
 }

  // получение мертвого стека (некро существо) на гексе поля боя
 inline _BattleStack_* Get_BattleStack_AnimatedDead(int side, int gex_id)
 {
   return CALL_3(_BattleStack_*, __thiscall, 0x5A4260, this, side, gex_id);
 }

 // Перерасчёт морали и удачи в бою
 inline int RecalculateLuckAndMorale()
 {
   return CALL_1(int, __thiscall, 0x469330, this);
 }
 
 // my
 inline _BattleStack_* GetCurrentStack()
 {
  return &(stack[currentActiveSide][currentStackIndex]);
 }

 inline _BattleStack_* GetCreatureAtXY(int x, int y)
 {
  int hex_ix = GetHexIxAtXY(x, y);
  if (hex_ix != ID_NONE) 
   return hex[hex_ix].GetCreature();
  else
   return NULL;
 } 
 
  // Установка поля перерисовки для стека.
 inline void Set_Stack_Redrawable(_BattleStack_* Stack)
 {
   // Специальная функция для стрелковой башни.
   if (Stack->creature_id == CID_ARROW_TOWER)
   {
     this->SetArrowTowerToRedraw(Stack);
   }
   // Специальное поле для стеков.
   else
   {
     *(_bool8_*)((_dword_)this + 81920 + Stack->side*20 + Stack->index_on_side) = TRUE;
   }
 } 
 
 // Добавление области к границам перерисовки. Возврат необходимости отрисовки изображения (по настройкам).
 // Возвращение необходимости перерисовки.
 inline _bool_ AddUpdateArea(_int_ X_Pos, _int_ Y_Pos, _int_ Width, _int_ Height)
 {
   
   // Границы перерисовки.
   _RedrawBorders_ Brd;
   
   
   if (*(_bool8_*)((_ptr_)this + 81196) || *(_bool32_*)((_ptr_)this + 81200))
   {
     // Левая граница перерисовки.
     Brd.Left = max(X_Pos, BattleRedraw_Borders.Left);
     // Верхняя граница перерисовки.
     Brd.High = max(Y_Pos, BattleRedraw_Borders.High);
     // Правая граница перерисовки.
     Brd.Right = min(X_Pos + Width - 1, BattleRedraw_Borders.Right);
     // Нижняя граница перерисовки.
     Brd.Low = min(Y_Pos + Height - 1, BattleRedraw_Borders.Low);
     
     if (*(_bool8_*)((_ptr_)this + 81196))
     {
       // Настройка глобальных границ перерисовки.
       (*(_int_*)((_ptr_)this + 81208)) = min(*(_int_*)((_ptr_)this + 81208), Brd.Left);
       (*(_int_*)((_ptr_)this + 81212)) = min(*(_int_*)((_ptr_)this + 81212), Brd.High);
       (*(_int_*)((_ptr_)this + 81216)) = max(*(_int_*)((_ptr_)this + 81216), Brd.Right);
       (*(_int_*)((_ptr_)this + 81220)) = max(*(_int_*)((_ptr_)this + 81220), Brd.Low);
     }
     
     if (*(_bool32_*)((_ptr_)this + 81204)) return FALSE;
   }
   
   
   // Возвращаем необходимость отрисовки (если хоть частично изображение попало в границы перерисовки).
   if (*(_bool32_*)((_ptr_)this + 81200)
       && (Brd.Left > ((_RedrawBorders_*)((_ptr_)this + 81208))->Right || Brd.Right < ((_RedrawBorders_*)((_ptr_)this + 81208))->Left
           || Brd.High > ((_RedrawBorders_*)((_ptr_)this + 81208))->Low || Brd.Low < ((_RedrawBorders_*)((_ptr_)this + 81208))->High))
   {
     return FALSE;
   }
   else
   {
     return TRUE;
   }
 } 
 
 // Добавление области к границым перерисовки способом стека.
 // Возвращение необходимости перерисовки.
 inline _bool_ AddSpecUpdateArea(_Def_* Def, _int_ DefGroupNum, _int_ FrameNum, _int_ X_Pos, _int_ Y_Pos, _bool_ Reflected)
 {
   // Границы перерисовки.
   _RedrawBorders_ Brd;
   
   if (*(_bool8_*)((_ptr_)this + 81196) || *(_bool32_*)((_ptr_)this + 81200))
   {
     this->SetSpecRedrawBorders(Def, DefGroupNum, FrameNum, X_Pos, Y_Pos, &Brd, Reflected, *(_bool8_*)((_ptr_)this + 81196));
     if (*(_bool32_*)((_ptr_)this + 81204)) return FALSE;
   }
   // Возвращаем необходимость отрисовки (если хоть частично изображение попало в границы перерисовки).
   if (*(_bool32_*)((_ptr_)this + 81200)
       && (Brd.Left > ((_RedrawBorders_*)((_ptr_)this + 81208))->Right || Brd.Right < ((_RedrawBorders_*)((_ptr_)this + 81208))->Left
           || Brd.High > ((_RedrawBorders_*)((_ptr_)this + 81208))->Low || Brd.Low < ((_RedrawBorders_*)((_ptr_)this + 81208))->High))
   {
     return FALSE;
   }
   else
   {
     return TRUE;
   }
 } 
};

// * how h3combatmonster is represented during quick combat
NOALIGN struct _AIQuickBattleCreatures_
{
  _int32_ count;
  _int32_ type;
  _int32_ num1;
  _int32_ num2;
  _int32_ speed;
  double field_14;
  double field_1C;
  double field_24;
  _byte_ field_2C[4];
  _byte_ field_30[4];
  _byte_ field_34[4];
  _int32_ turretPriority;
  _int32_ unitPower;
  _int32_ stackPower;
  _byte_ field_44[4];
};

// * represents one of the two sides during quick combat
NOALIGN struct _AIQuickBattle_
{
  // H3Vector<_AIQuickBattleCreatures_> creatures;  // +0 ... +16
  _dword_ field_0;
  _dword_ field_4;
  _dword_ field_8;
  _dword_ field_C;
  _dword_ specialTerrain; 
  _dword_ spellPoints;
  _byte_ canCastSpells;
  _byte_ field_19[3]; 
  _dword_ armyStrength; 
  _byte_ tactics; 
  _byte_ field_21[3]; 
  _Hero_* heroA;
  _Army_ *army; 
  _Hero_* heroD;
  _byte_ turrets;
  _byte_ field_31;
  _word_ turretsLevel;

  inline void DeleteCreatures() { CALL_2(void, __thiscall, 0x424880, this, 1);}
};


//size = 0x88 (136 bytes)
NOALIGN struct _TownStartInfo_: _Struct_ 
{
 _int_ id; //+0
 _byte_ owner_id;//+4
 _byte_ field_5[19];//+5
 _bool8_ has_fort; //+0x18
 _byte_ field_19[3];//+0x19
 _Army_ army;//+0x1C
 _byte_ field_54[20];//+0x54
 _dword_ type;//+0x68
 _byte_ field_6C[28];//+0x54
};

NOALIGN struct _ArmyStartInfo_
{
 _int32_ type[7];
 _int16_ count[7];
};

NOALIGN struct _HeroStartInfo_ //size = 0x334 bytes
{
 _int8_ owner_id;   //! = хозяин (цвет) ff - ничей
 _byte_ _u1[3];
 _dword_ id;  // = номер подтипа (конкретный герой)
 _dword_ id_wtf;      // = id
 _bool8_ has_name;    // = 1-есть имя
 _char_ name[13];//! = имя,0
 _byte_ has_exp;    // = 1-есть опыт
 _byte_ _u2;
 _int_  exp;     //   +1c  dd   = опыт
 _bool8_   has_picture;    //   +20  db   = 1-есть картинка
 _byte_    picture_id;     //   +21  db   = номер картинки
 _bool8_   has_second_skills;   //   +22  db   = 1-есть 2-е скилы
 _byte_ _u3;
 _dword_ second_skills_count;   //!   +24  dd   = кол. вторых скилов
 _byte_ second_skill[8];//  +28  dd*8 = номера вторых скилов
 _byte_ second_skill_level[8];//   +30  db*8 = уровни вторых скилов
 _bool8_ has_army;    //   +38  db   = 1-есть существа
 _byte_ _u4[3];

 _ArmyStartInfo_ army; //+3c
 _bool8_ army_is_group;   //   +66  db   = группа/разброс

 _bool8_ has_arts;    //   +67  db   = 1-есть артифакты
 _Artifact_ doll_art[19];//+68  dd*2*13 = артифакты dd-номер,dd-(ff) +e8 -книга(3,ff)
 _Artifact_ backpack_art[64];//+100 dd*2*40 = арт в рюкзаке dd-номер, dd-(ff)
 _byte_ backpack_arts_count;   //   +300 db   = число артифактов в рюкзаке
 _dword_ xyz;   //   +301 2*dw = нач. позиция на карте
 _byte_ run_radius;     //!   +305 db   = радиус обегания
 _bool8_ has_biography;    //   +306 db   = 1-есть биография
 _byte_ _u6;   //+307
 _HStringF_ biography;      //   +308 dd   = 1-выделена память под биографию
 _int8_ sex;     //   +318 dd   = 0-м,1-ж,ff-умолчание
 _byte_ _u9[3];
 _bool8_ has_spells;   //   +31c db   = 1-есть заклинания
 _byte_ _u10[3];
 _byte_ spell[10];//  +320 db*a = заклинания
 _word_ _u11;
 _byte_ has_primary_skills;   //   +32c db   = 1-есть первичные умения
 _byte_ primary_skill[4];//  +32d db*4 = 4-ре первичных умения
 _byte_ _u12[3];
};

#define GAME_HEROES_AVAILABILITY_OFFSET (*(_ptr_*)0x412F1C)
#define GAME_PLAYERS_AVAILABILITY_OFFSET (*(_ptr_*)0x4868FB)

#define GAME_HEROES_OFFSET (*(_ptr_*)0x41C6B5)

// ******************************

struct _H3ObjectDraw_
{
  // * +0
  // index of H3ObjectAttributes
  _word_ sprite;
  // * +2
  // * reference to which square of the DEF (bottom right = 0, then left to right, down to top. Row 1: 0x10 and so on)
  _byte_ tileID;
  // * +3
  // * 0~6 drawing layer, 6 being top and 0 bottom
  _byte_ layer;
};

// Список героев.
NOALIGN struct _HeroesList_: public _List_<_Hero_>
{
  // Нет дополнительных полей, только методы.
  
  // Удаление списка героев.
  inline void Delete()
  {
    CALL_1(void, __thiscall, 0x45F830, this);
  }
};

// Структура битовой маски проходимости и триггеров шаблона.
NOALIGN struct _TmplPosMsk_
{
  // Первые 32 бита.
  _dword_ bits0; // +0
  // Последние 32 бита (используются только первые 16).
  _dword_ bits32; // +4
  
  
  // Установка всех битов маски.
  void SetAll(_dword_ value)
  {
    CALL_2(void, __thiscall, 0x4E6770, this, value);
  }
  
  
  // Установка указанного бита маски.
  void SetBit(_int_ bit_ix, _bool8_ value)
  {
    CALL_3(void, __thiscall, 0x506DD0, this, bit_ix, value);
  }
  
  
  // Получение указанного бита маски.
  _bool8_ GetBit(_int_ bit_ix)
  {
    return CALL_2(_bool8_, __thiscall, 0x506E30, this, bit_ix);
  }
  
};

// Структура битовой маски доступности территорий шаблона.
NOALIGN struct _TmplTerrMsk_
{
  // Первые 32 бита.
  _dword_ bits0; // +0
  
  
  // Установка всех битов маски.
  void SetAll(_dword_ value)
  {
    CALL_2(void, __thiscall, 0x506ED0, this, value);
  }
  
  
  // Установка указанного бита маски.
  void SetBit(_int_ bit_ix, _bool8_ value)
  {
    return CALL_3(void, __thiscall, 0x506E70, this, bit_ix, value);
  }
  
  // user
  
  // Получение указанного бита маски.
  _bool8_ GetBit(_int_ bit_ix)
  {
    return (((1 << (bit_ix & 0x1F)) & *(&this->bits0 + (bit_ix >> 5))) != 0);
  }
  
};


// Шаблон объекта на карте.
// Отвечает за тип объекта и всевозможные свойства, которые могут быть разными у одного тппа - проходимость и т. п.
NOALIGN struct _Template_: _Struct_
{
  // Имя def`а шаблона.
  _HStringF_ DefName; // + 0
  // Размер шаблона по-горизонтали (в клетках карты).
  _byte_ Size_x; // +16
  // Размер шаблона по-вертикали (в клетках карты).
  _byte_ Size_y; // +17
  _byte_ f12[10]; // +18
  // Битовая маска проходимых клеток (6*6, 2 бита в каждом байте и 2 байта полностью не используются).
  _TmplPosMsk_ ImpassBitMask; // +28
  _byte_ f24[8]; // +36
  // Битовая маска активируемых клеток (6*6, 2 бита в каждом байте и 2 байта полностью не используются).
  _TmplPosMsk_ TriggerBitMask; // +44
  _TmplTerrMsk_ terrs; // +52
  // Тип объекта шаблона.
  _int_ ObjType; // +56
  // Подтип объекта шабона.
  _int_ ObjSubtype; // +60
  _byte_ f40; // +64
  _byte_ f41[3]; // +65
};


// Объект на карте приключений.
NOALIGN struct _Object_
{
  _byte_ f0[4]; // +0h
  // X-координата положения на карте
  _byte_ x; // +4h
  // Y-координата положения на карте
  _byte_ y; // +5h
  // Z-координата положения на карте
  _byte_ z; // +6h
  // Результат выравнивания, не используется.
  _byte_ dummy_f7[1]; // +7h
  // Номер шаблона объекта.
  _int16_ template_id; // +8h
  _byte_ dummy_fA[2]; // +Ah
};


// Объект - лагерь героя.
NOALIGN struct _PlaceHolder_
{
  // Адрес общей структуры объекта лагеря.
  _Object_* object; // +0h
  // Номер игрока - хозяина лагеря.
  _byte_ player_ix; // +4h
  // Результат выравнивания, не используется.
  _byte_ dummy_f5[3]; // +5h
  // Номер героя лагеря (-1 - произвольный).
  _int_ hero_id; // +8h
  // Условная сила героя в лагере для произвольного героя.
  _byte_ hero_power; // +Ch
  // Результат выравнивания, не используется.
  _byte_ dummy_fD[3]; // +Dh
};


// квесты хижины провидцев и стражей прохода
#define o_QUESTSEERHUT_TXT (*(_TXT_**)0x68325C)
#define o_QUESTGUATDS_TXT (*(_TXT_**)0x683260)

NOALIGN struct _H3QuestVector_
{
  _int_ _init;  
  _int32_* first;
  _int32_* last;
  _int32_* capacity;
};

// Квест: хижина провидца или страж задания 
// размер разный: 64-80 байтов
NOALIGN struct _H3Quest_
{
  enum eQuestType
  {
    QT_None            = 0,
    QT_ExperienceLevel = 1,
    QT_PrimarySkill    = 2,
    QT_DefeatHero      = 3,
    QT_DefeatMonster   = 4,
    QT_BringArtifacts  = 5,
    QT_BringCreatures  = 6,
    QT_BringResources  = 7,
    QT_BeHero          = 8,
    QT_BePlayer        = 9,
  };
  // * +0
  // * 0x641798 + questType * 0x3C
  _ptr_* vTable;
  // * +4
  // * 0 = quest guard, 1 = seer hut
  _int32_ questor_type;
  // * +8
  _HStr_ message_proposal;
  // * +18 (+24)
  _HStr_ message_progress;
  // * +28 (+40)
  _HStr_ message_completion;
  // * +38 (+56)
  // * texts variant, of no apparent use
  _int32_ string_id;
  // * +3C (+60)
  _int32_ last_day;

  union QuestData
  {
    _int32_ achieveLevel;     // achieve level
    _byte_ achievePrimarySkill[4];  // have primary skills
    struct
    {
      _int32_ __0;
      _int32_ targetHero;
      _int32_ successfulPlayers;
    } killHero;           // kill certain hero
    struct
    {
      _int32_ __0;
      _dword_ packedCoords;
      _int32_ displayCreatureType;
      _int32_ player;
    } killMonster;          // kill a monster in certain position on the map
    _H3QuestVector_ getArtifacts; // bring artifacts
    struct
    {
      _H3QuestVector_ number;
      _H3QuestVector_ type;
    } getCreatures;         // get creatures
    _int_ getResources[7];      // get resources
    _int32_ beHero;         // visit as a certain hero
    _int32_ bePlayer;       // visit as a certain player      
  } data; 

  inline _int32_ GetQuestType() {return (this ? ((_dword_)vTable - 0x641798) / 0x3C + 1 : 0);}
};


// * quest guard is a quest plus a byte to show who visited
// * размер 5 байт
NOALIGN struct _H3QuestGuard_
{
  _H3Quest_* quest;
  _byte_ players_visited;
};


// * seer hut is a quest guard plus some information about reward
// * 0x80 byte (размер 19 байт)
NOALIGN struct _H3QuestSeerHut_
{
  // * +0 (+0)
  _H3Quest_* quest;
  // * +4 (+4)
  _byte_ players_visited;
  // * +5 (+5)
  _int32_ reward_type;
  // * +9 (+9)
  _int32_ reward_value;
  // * +D (+13)
  _int32_ reward_value2;
  // * +11 (+17)
  _byte_ seer_name_id;
  // * +12 (+18)
  _ptr_ _f_12;
};



// Карта игры (размер 3932 или 3936 - неизвестно, относится ли последнее dd к карте или просто к GameMgr).
NOALIGN struct _GameMap_: _Struct_
{
  // Список шаблонов объектов карты.
  _List_<_Template_> Templates; // +0

  // Список объектов на карте.
  _List_<_Object_> Objects; // +16
  
  // H3LoadedDEF
  _byte_ field_20[16]; // +32 

  // Список артефактов на карте.
  _List_<_ArtOnMap_> Artifacts; // +48

  // Список монстров на карте.
  _List_<_CreatureOnMap_> Monsters; // +64

  // H3PandorasBox
  _byte_ field_50[16]; // +80 

  // Список провидцев 
  _List_<_H3QuestSeerHut_> QuestSeerHuts; // +96

  // Список стражей задания 
  _List_<_H3QuestGuard_> QuestGuards; // +112

  // H3GlobalEvent
  _byte_ field_7C[16]; // +128

  // H3CastleEvent
  _byte_ field_90[16]; // +144
  
  // Список лагерей героя на карте.
  _List_<_PlaceHolder_> PlaceHolders; // +160
  
  // H3QuestGuard
  _byte_ field_B0[16]; // +176

  // unknow
  _byte_ field_C0[16]; // +192
  
  // Адрес 3-мерного массива [L][Y][X], хранящего свойства объекта каждой клетки карты.
  _MapItem_* items; // +208
  // Размер карты (по-горизонтали и по-вертикали).
  _int_ size; // +212
  // Есть ли у карты подземный уровень.
  _byte_ has_underground; // +216  
  _byte_ fD9[3]; // +217

  _List_<_Template_> objectLists[232]; // +220  
  
  //normal
  // Получение объекта карты по координатам (из массива items).
  inline _MapItem_* GetItem(_int_ x, _int_ y, _int_ z)
  {
     return CALL_4(_MapItem_*, __thiscall, 0x4086D0, this, x, y, z);
  }

  inline void DrawItem(_MapItem_* item, _H3ObjectDraw_* draw)
  {
     return CALL_3(void, __thiscall, 0x50588, this, item, draw);
  }
};


// Заголовочная информация карты. Размер: 720 байт.
NOALIGN struct _MapHeader_
{
  // +0.
  _byte_ f0[772];
//  h3unk _f_000[8]; // 0...7
// INT8 handicap[8]; // 8..15 
// INT32 townType[8]; // 16, 20, 24, 28, 32, 36, 40, 44
// h3unk _f_030[8]; // 48...55
// INT8 difficulty; // 56
// CHAR filename[251]; // 57...307
// CHAR saveDirectory[100]; // 308..407
// h3unk _f_198[12]; // 408..420
// INT32 heroMaybe[8];  // 428..459
// h3unk _f_1C4[8]; // 460..467
};




NOALIGN struct _GameMgr_: _Struct_
{
 _dword_ field_0;//+0 ???
 _byte_ disabled_shrines[70]; //+4 //??? //какие святыни еще можно поставить на карту (0)
 _byte_ disabled_spells[70];//+0x4A //разрешено закл (0) на карте или запрещено (1)
 LPCRITICAL_SECTION cs_bink;//+0x90 //CriticalSection Object для запуска/остановки видео BINKW32.DLL
 _List_<_TownStartInfo_> town_start_info;//+0x94
 _HeroStartInfo_ hero_start_info[156];//+0xA4
 _dword_ field_1F454;//+0x1F454
 _bool8_ is_cheater;//+0x1F458
 
 _byte_ f1F459[1]; // +1F459h
 
 // Номер сценария в кампании (с 1).
 _byte_ campaing_scenario_ix; // +1F45Ah
 
 _byte_ f1F45B[1]; // +1F45Bh
 
 // Номер кампании (определяющий её карту и пр.)
 _dword_ campaing_ix;  // +1F45Ch 
 
 _byte_ f1F460[52]; // +1F460h 
 
 // Списки сохранённых героев в кампании для перехода в следующие сценарии.
 _List_<_HeroesList_> saved_heroes_lists; // +1F494h 
 
 _byte_ f1F4A4[410]; // +1F4A4h 
 
 // Номер текущего дня (1-7).
 _word_ curr_day_ix; // +1F63Eh
 
 // Номер текущей недели (1-4).
 _word_ curr_week_ix; // +1F640h
 
 // Номер текущего месяца.
 _word_ curr_month_ix; // +1F642h 
 
 _byte_ f1F644[32]; // +1F644h

 // артефакты в торговце в замке
 _dword_ bMarketArt[7]; // +1F664h

 _dword_ f1F680; // +1F680h

 // первый торговец артефактами на карте в списке
 _dword_ bMarketOnMap_first; // +1F684h

  // последний торговец артефактами на карте в списке
 _dword_ bMarketOnMap_last;  // +1F688h

 _byte_ f1F68C[12]; // +1F68Ch 
 
 // Версия карты 0 - RoE, 1 - AB, 2 - SoD
 _dword_ map_version; // +1F698h
 
 _bool8_ IsCheater; // +1F69Ch
 
 // Является ли текущая игра обучением.
 _bool8_ is_tutorial; // +1F69Dh
 
 _byte_ f1F69E[59]; // +1F69Eh
 
 // Название файла карты.
 char map_name[248]; // +1F6D9h
 
 _byte_ f1F7D1[3]; // +1F6D1h
 
 // Путь к файлу карты.
 char map_path[100]; // +1F7D4h 
 
  _byte_ f1F838[52]; // +1F838h
  
  // Заголовочная информация карты игры.
  _MapHeader_ map_header; // +1F86Ch
  
  // Карта игры.
  _GameMap_ Map; // +1FB70h  +129904
 
  // _byte_ f20ACC[2900]; // +20ACCh

  _byte_ _field_20ACC[4]; // +20ACCh

  _Player_ players[8]; // +20AD0

  _List_<_Town_> towns;

  // Герои (перенесено).
  // быть внимательным! 
  // возможно я сбил структуру заполняя поля 
  // ниже _GameMap_ Map
  _Hero_ hero[156]; // +21620h
  
  // Положения героев (перенесено).
  _byte_ heroOwner[156]; // +4DF18h
  
  // Доступности героев игрокам (перенесено).
  _dword_ heroMayBeHiredBy[156]; // +4DFBDh
  
  _byte_ randomArtifacts[144]; // +4E22Dh
  
  _byte_ artifactsAllowed[144]; // +4E2BDh
  
  _byte_ f4E34D[1164]; // +4E34Dh

 
 inline _Player_* GetMe() {return CALL_1(_Player_*, __thiscall, 0x4CE670, this);}
 inline _int_  GetMeID() {return CALL_1(_int_, __thiscall, 0x4CE6E0, this);}
 inline char*  GetPlayerName(_int_ player_id) {return (char*)( ((_ptr_)this) + 0x20AD0 + player_id*0x168 + 0xCC );}
 inline char*  GetPlayerColorName(_int_ player_id) {return CALL_2(char*, __thiscall, 0x4CE820, this, player_id);}

 inline _int_  FindTownIdByXYZ(_int_ x, _int_ y, _int_ z) {return CALL_4(_int_, __thiscall, 0x4BB530,this, x, y, z);}

 inline _Hero_*  GetHero(_int_ hero_id) {
    if (hero_id < 0 || hero_id >= o_HEROES_COUNT) return 0;
    return ((_Hero_ *)(((_ptr_)this) + GAME_HEROES_OFFSET /*0x21620*/ + 1170 * hero_id)); 
}

 // inline char*  GetHeroName() {return *(char**)((_ptr_)this +  0x1F86C + 0x2D4);}
 inline _Player_* GetPlayer(_int_ player_id) {return ((_Player_ *)(((_ptr_)this) + 0x20AD0 + 360 * player_id));}
 inline _Town_*  GetTown(_int_ town_id) {return ((_Town_*)(*(_ptr_*)(((_ptr_)this) + 0x21614) + 360 * town_id));}
 inline _int_  GetTownsCount() {return ((_int_)((*(_dword_*)(((_ptr_)this) + 0x21618) - *(_dword_*)(((_ptr_)this) + 0x21614)) / 360));}
 inline _GlobalEvent_* GetGlobalEvent(_int_ index) {return ((_GlobalEvent_*)(*(_ptr_*)(((_ptr_)this) + 0x1fbf4) + 52 * index));}
 inline _int_  GetGlobalEventsCount() {return ((_int_)((*(_dword_*)(((_ptr_)this) + 0x1fbf8) - *(_dword_*)(((_ptr_)this) + 0x1fbf4)) / 52));}
 inline _int_  GetMapType() {return ( *(_dword_*)(((_ptr_)this) + 0x1f698) );}
 inline char*  GetScenarioName() {return *(char**)((_ptr_)this +  0x1F86C + 0x2D4);}
 inline _word_  GetDay() {return *(_word_*)((_ptr_)this + 0x01F63E);}
 inline _word_  GetWeek() {return *(_word_*)((_ptr_)this + 0x01F640);}
 inline _word_  GetMonth() {return *(_word_*)((_ptr_)this + 0x01F642);}
 inline _int_*  GetMerchantsArts() {return (_int_*)((_ptr_)this + 0x01F664);}
 inline _int_  GetCountsArtsOfPlayer(_int_ player_id, _int_ artifact_id) {return CALL_2(_int_, __thiscall, 0x4BA890, ( ((_ptr_)this) + 0x20AD0 + player_id*0x168), artifact_id);}
 inline _int_  GetPlayerGoldIncome(_int_ player_id) {return CALL_3(_int_, __thiscall, 0x4C75F0, this, player_id, 1);}
 
 // получить тип специальности героя
// inline _int_  GetHero_SpecInfo(_int_ hero_id, _int_ type) {return *(int*)(*(int*)0x679C80 + hero_id *40 + type);}


 inline _dword_  GetMapWidth() {return *(_dword_*)((_ptr_)this + 0x1FC44);}
 inline _byte_  GetMapDepth() {return *(_byte_*)((_ptr_)this + 0x1FC48);}

 inline _bool_  IsPlayerIngame(_int_ player_id) { return (_bool_)(1 - *(_byte_*)(((_ptr_)this) + 0x1F636 + player_id)); }
 inline _bool_  IsPlayerOutgame(_int_ player_id) { return (_bool_)(*(_byte_*)(((_ptr_)this) + 0x1F636 + player_id)); }
 inline _bool_  IsPlayerHuman(_int_ player_id) { return CALL_2(_bool_, __thiscall, 0x4CE600, this, player_id); }

 inline void ReplayOpponentTurn() {CALL_1(void, __thiscall, 0x49D410, this);}
 inline void ShowScenarioInfo() {CALL_1(void, __thiscall, 0x513950, this);}

 inline _byte_ PlayerIsInGameHuman(_int_ player_id) {return CALL_2(_byte_, __thiscall, 0x4CE630, this, player_id);}

 inline void  ShowFullCreatureInfoDlg(_Army_* army, _int_ index, _Hero_* hero, _int_ e0, _int_ x, _int_ y, _int8_ can_fired, _int8_ right_click)
  { CALL_9(void, __thiscall, 0x4C6910, this, army, index, hero, e0, x, y, can_fired, right_click); }

 // my
 inline void ShowFullCreatureInfoDlg(_Army_* army, _int_ index, _Hero_* hero, _int_ x, _int_ y, _bool8_ right_click)
 {

  if (hero)
   CALL_9(void, __thiscall, 0x4C6910, this, army, index, hero, 0, x, y, hero->army.GetStacksCount() > 1, right_click);
  else
   CALL_9(void, __thiscall, 0x4C6910, this, army, index, hero, 0, x, y, TRUE, right_click);
 }

  // user
  
  // Получение лодки на координатах.
  _Struct_* GetBoatAtCoords(_int_ x, _int_ y, _int_ z)
  {
    // Проходим по всем существующим лодкам.
    if (this->Field<_List_<_byte_>>(320440).Data)
    {
      for (_ptr_ i = (_ptr_)this->Field<_List_<_byte_>>(320440).Data; i < (_ptr_)this->Field<_List_<_byte_>>(320440).EndData; i += 40)
      {
        // Лодка существует и не имеет героя.
        if (((_Struct_*)i)->Field<_bool8_>(24) && !((_Struct_*)i)->Field<_bool8_>(36))
        {
           // Лодка - на текущих координатах.
           if (((_Struct_*)i)->Field<_int16_>(0) == x && ((_Struct_*)i)->Field<_int16_>(2) == y && ((_Struct_*)i)->Field<_int16_>(4) == z)
           {
             return (_Struct_*)i;
           }
        }
      }
    }
    
    // Не нашли.
    return NULL;
  }
  
  
  // Посадка героя в лодку на том месте, где он стоит (герой должен быть на карте и не в лодке, если лодки там же нет, она создаётся, если есть - она должна там стоять с начала игры).
  _bool32_ HeroPlaceToBoat(_Hero_* hero, _int_ boat_subtype)
  {
    
    // Лодка.
    _Struct_* boat;
    
    // Создаём лодку.
    _int_ boat_ix = CALL_7(_int_, __thiscall, 0x4BAF10, this, hero->x, hero->y, hero->z, hero->owner_id, FALSE, boat_subtype);
    
    // Не удалсь создать лодку.
    if (boat_ix < 0)
    {
      return FALSE;
    }
    // Сгенерировали лодку.
    else
    {
      boat = (_Struct_*)(this->Field<_List_<_byte_>>(320440).Data + 40*boat_ix);
    }
    
    
    
    // Сажаем героя в лодку.
    
    
    // Убираем лодку из информации клетки.
    CALL_1(void, __thiscall, 0x4D7950, boat);
    
    // Настраиваем героя.
    hero->temp_mod_flags |= 0x40000;
    hero->fly_cast_power = -1;
    hero->waterwalk_cast_power = -1;
    
    // Пересчитываем ходьбу героя в водную (new_mp = old_mp*new_max/old_max).
    if (!(hero->temp_mod_flags & 0x1000000))
    {
      _int_ new_max = CALL_2(_int32_, __thiscall, 0x4E4C00, hero, TRUE);
      hero->movement_curr = hero->movement_curr*new_max/hero->movement_max;
      hero->movement_max = new_max;
    }
    
    // Настраиваем лодку.
    boat->Field<_int32_>(32) = hero->id;
    boat->Field<_bool8_>(36) = TRUE;
    boat->Field<_int8_>(28) = hero->owner_id;
    
    return TRUE;
  }
 
 
};



// ******************************






// *************************************


#define o_GetTime() CALL_0(_dword_, __cdecl, 0x4F8970)

// typedef void (__thiscall *_func_MouseMan_SetCursor)(_ptr_ this_, _int_ frame, _int_ type);
// #define b_MouseMan_SetCursor(frame, type) ((_func_MouseMan_SetCursor)0x50CEA0)(o_MouseMgr,(_int_)(frame),(_int_)(type))

#define b_MouseMan_SetCursor(frame, type) CALL_3 (void, __thiscall, 0x50CEA0, o_MouseMgr, (_int_)frame, (_int_)type);
#define b_MouseMgr_SetCursor(frame, type) CALL_3 (void, __thiscall, 0x50CEA0, o_MouseMgr, (_int_)frame, (_int_)type);

#define o_GetMapCellVisability(x,y,z) CALL_3(_dword_, __fastcall, 0x4F8040, x, y, z)


// Максимальное случайное число.
#define RandMax 0x7FFF

// Случайное число без диапазона.
#define Rand() CALL_0(_dword_, __cdecl, 0x61842C)

// Получения случайного double.
inline double DoubleRand(double low, double high)
{
  return low + (double)Rand()/(double)RandMax*(high - low);
}


// Полувремязависимый ранодом.
// В зависиости от знчения своей управляющей переменной генерирует случайное целое число в указанных пределах по seed или текущему времени.
#define TRandint(Low, High) CALL_2(_int_, __fastcall, 0x50B3C0, (_int_)Low, (_int_)High)


// Случайное целое число в диапазоне.
#define Randint(Low, High) CALL_2(_int_, __fastcall, 0x50C7C0, (_int_)Low, (_int_)High)


// Ожидание до указанного времени (или времени, превышающего указанное).
#define WaitTill(Time) CALL_1(void, __fastcall, 0x4F8980, (_dword_)Time);


// Начало тактильного эффекта (IFC20.dll, не проявляется при стандартных средствах управления).
#define TouchEffectStart(Name, a2) CALL_2(void, __fastcall, 0x4B6750, (_cstr_)Name, (_dword_)a2)

// *************************************

// size 0x40 (64 byte)
NOALIGN struct _Mine_ 
{
  _byte_ owner;       // 0
  _byte_ type;        // 1
  _byte_ field_02[2]; // 2, 3
  _Army_ army;        // 4-59
  _byte_ x;           // 60
  _byte_ y;           // 61
  _byte_ z;           // 62
  _byte_ field_3F;    // 63
};  

NOALIGN struct _GarrisonBar_
{
 _byte_ field_0[28];
 _int_ x; //+28
 _int_ y; //+32
 _bool_ is_down_bar; //+36
 _int_ owner_id; //+40
 _int_ sel_slot_index;
 _byte_ field_2C[56];
 _Dlg_* parent_dlg;
 _Army_* army; //+108
 _int_ hero_pic; //+112
 _Hero_* hero; //+116

 // normal
 inline void Update(_bool_ a2, _int_ a3) { CALL_3(void, __thiscall, 0x5AA0C0, this, a2, a3); }
 inline void UpdateRedraw(_int_ a2) { CALL_2(void, __thiscall, 0x5AA090, this, a2); }
};

NOALIGN struct _TownMgr_: _Struct_
{
 // _byte_ field_0[56];
 _Manager_ mgr; 
 _Town_* town; //+56
 _byte_ field_48[220];
 _Dlg_* dlg; // +280
 _GarrisonBar_* garribar_up; //+284
 _GarrisonBar_* garribar_down; //+288

 _GarrisonBar_* garribar_sel; //+292
 _int_ garribar_slot_index_sel; //+296

 _GarrisonBar_* garribar_src; //+300
 _int_ garribar_slot_index_src; // +304
 _GarrisonBar_* garribar_dst; //+308
 _int_ garribar_slot_index_dst; //+312

 _ptr_ resources_bar;//+316

 _dword_ field_140;//+320

 _char_ statusbar_text[88]; // +324

 _int_ command_code; //+412
 
 _byte_ f1A0[56]; // +1A0h


 // normal

 void CreateNewGarriBars() {CALL_1(void, __thiscall, 0x5C7210, this);}
 void MoveHeroUp() {CALL_1(void, __thiscall, 0x5D5550, this);}
 void MoveHeroDown() {CALL_1(void, __thiscall, 0x5D5620, this);}


 void UnHighlightArmy() {CALL_1(void, __thiscall, 0x5D5930, this);} // отключить жёлтую обводку 
 void Redraw() {CALL_1(void, __thiscall, 0x5D5810, this);} // обновить экран города 

 // my 

 inline void DeleteGarriBars()
 {
  if (this->garribar_up) o_Delete(this->garribar_up); this->garribar_up = NULL;
  if (this->garribar_up) o_Delete(this->garribar_down); this->garribar_down = NULL;
 }

 inline void SwapHeroes() {this->town->SwapHeroes(); DeleteGarriBars(); CreateNewGarriBars();}

};


typedef void (__thiscall * _func_AdvMgr_ActivateHero)(_ptr_ this_, int hero_id, int a3, char a4, char a5);
#define o_AdvMgr_ActivateHero(advmgr, hero_id, a3, a4, a5) ((_func_AdvMgr_ActivateHero)0x417A80)((_ptr_)(advmgr), (int)(hero_id), (int)(a3), (char)(a4), (char)(a5))

typedef _MapItem_* (__thiscall * _func_GetMapItem)(_ptr_ this_, int x, int y, int z);
#define b_GetMapItem(x,y,z) ((_func_GetMapItem)0x4086D0)(*(_ptr_*)(o_AdvMgr + 92),(int)(x),(int)(y),(int)(z))

NOALIGN struct _AdvMgr_: _Struct_
{
 _Manager_ mgr; // 0...56
 _byte_ field_38[12]; //+56
 _Dlg_* dlg; //+68
 _byte_ field_48[20]; //+72
 _GameMap_* map; //+92
 // _byte_ field_60[488]; //+96
 _byte_ field_60[132]; //+96
 _dword_ pack_xyz_look;     //+228
 _dword_ pack_xyz;     //+232
 _byte_ field_EC[300]; //+236
 _dword_ monBattle_num;  //+536
 _dword_ monBattle_type;   //+540
 _dword_ monBattle_side;   //+544
 _byte_ field_220[36]; //+548

 // Фоновые звуки (ссылка на звук или 0, если не проигрывается).
 _Wav_* loop_sounds[70]; // +584
 _byte_ field_360[52]; //+864
 _int_ info_panel_current_type; //+916
 _int_ info_panel_current_id;   //+920
 _int_ info_panel_timer;        //+924 хранит время таймера переключения инфо-панели
 
 _byte_ f398[24]; // +398h
 
 
 //inline _Dlg_* GetDlg() {return *(_Dlg_**)((_ptr_)this + 68);}
 //inline _int_ GetCurrentInfoPanelID() {return *(_int_*)((_ptr_)this + 916);}
 inline _dword_ FullUpdate(_bool_ redraw_screen) {return CALL_3(_dword_, __thiscall, 0x417380, this, redraw_screen, 0/*not used*/);}
 inline _dword_ RebuildHeroInfoPanel(_bool_ even_if_on_top) {return CALL_2(_dword_, __thiscall, 0x4163B0, this, even_if_on_top);}
 inline _dword_ RebuildTownInfoPanel(_bool_ even_if_on_top) {return CALL_2(_dword_, __thiscall, 0x416450, this, even_if_on_top);}
 inline _dword_ UpdateInfoPanel(_bool_ even_if_on_top, _bool_ redraw, _bool_ redraw_screen)
  {return CALL_4(_dword_, __thiscall, 0x415D40, this, even_if_on_top, redraw, redraw_screen);}
 inline _dword_ RedrawInfoPanel(_bool_ redraw_screen) {return CALL_2(_dword_, __thiscall, 0x402BC0, dlg, redraw_screen);}
 inline _dword_ ViewWorld(_int_ a2, _int_ a3) {return CALL_3(_dword_, __thiscall, 0x5FC340, this, a2, a3);}
 inline _dword_ ShowPuzzleMap() {return CALL_1(_dword_, __thiscall, 0x41A750, this);}
 inline _dword_ DrawMap(_int_ x, _int_ y, _int_ z, _int_ a5, _bool_ update_info_panel)
  { return CALL_6(_dword_, __thiscall, 0x40F350, this, x,y,z, a5, update_info_panel);}
 inline _dword_ DrawMap(_dword_ xyz, _int_ a5, _bool_ update_info_panel)
  { return DrawMap(b_unpack_x(xyz), b_unpack_y(xyz), b_unpack_z(xyz), a5, update_info_panel);}
 inline _dword_ Dig(_int_ x, _int_ y, _int_ z) { return CALL_4(_dword_, __thiscall, 0x40EBF0, this, x,y,z); }
 inline _dword_ Dig() { return Dig(-1,0,0); }
 inline _byte_ ShowDlg_SystemOptions() {return CALL_1(_byte_, __thiscall, 0x41AB60, this); } 

 inline void HeroActive_Mobilize() { CALL_4(void, __thiscall, 0x417540, this, 0, 0, 0); } 
 inline void HeroActive_DeMobilize() { CALL_3(void, __thiscall, 0x4175E0, this, 0, 1); } 

 inline void SwapHeroes(_Hero_* heroLeft, _Hero_* heroRight) { CALL_3(void, __thiscall, 0x4AAA60, this, heroLeft, heroRight); }
};

//////////////////////////////////////////////////////////////////////////////////////////
//typedef _int8_ (__thiscall *_func_AdvMgr_FullUpdate)(_ptr_ this_, _byte_ redraw, _dword_ unused);
//#define b_AdvMgr_FullUpdate(redraw) ((_func_AdvMgr_FullUpdate)0x417380)(o_AdvMgr, (_byte_)(redraw), 0)

//typedef char (__thiscall * _func_AdvMgr_RebuildHeroInfoPanel)(_ptr_ advmgr, _int8_ a2);
//typedef char (__thiscall * _func_AdvManInfoPanel_Redraw)(_ptr_ this_, _int8_ a2);
//#define o_AdvMgr_RebuildHeroInfoPanel(this_, even_if_not_on_top) ((_func_AdvMgr_RebuildHeroInfoPanel)0x4163B0)((_ptr_)(this_),(_int8_)(even_if_not_on_top))
//#define b_AdvMgr_RedrawInfoPanel(this_, redraw_on_primary_buf) ((_func_AdvManInfoPanel_Redraw)0x402BC0)(*(_ptr_*)(this_ + 68), (_int8_)(redraw_on_primary_buf))

//#define b_AdvmanHeroInfoPanel_Update(draw) {((_func_RebuildAdvmanHeroInfoPanel)0x4163B0)(o_AdvMgr, 1); ((_func_RedrawAdvmanInfoPanel)0x402BC0)(*(_ptr_*)(o_AdvMgr + 68), (_int8_)(draw));}
//#define b_AdvMgr_CurrentInfoPanelID (*(_dword_*)(o_AdvMgr + 916))

//typedef void (__thiscall * _func_AdvMgr_ViewWorld)(_ptr_ this_, _int_ a2, _int_ a3);
//#define b_AdvMgr_ViewWorld(a2, a3) ((_func_AdvMgr_ViewWorld)0x5FC340)(o_AdvMgr, (_int_)(a2), (_int_)(a3))
//#define b_AdvMgr_ShowPuzzleMap() ((_func_this)0x41A750)(o_AdvMgr)

//typedef void (__thiscall *_func_AdvMgr_DrawMap)(_ptr_ this_, _int_ x, _int_ y, _int_ z, _bool_ a5, _bool_ a6);
//#define o_AdvMgr_DrawMap(this_,x,y,z,a5,a6) ((_func_AdvMgr_DrawMap)0x40F350)((_ptr_)(this_),(_int_)(x),(_int_)(y),(_int_)(z),(_bool_)(a5),(_bool_)(a6))
//#define b_AdvMgr_DrawMap(this_,xyz,a5,a6) o_AdvMgr_DrawMap(this_, b_unpack_x(xyz), b_unpack_y(xyz), b_unpack_z(xyz),(_bool_)(a5),(_bool_)(a6))


#define o_Terminate(pchar_reason_text) CALL_1(void, __fastcall, 0x4F3D20, pchar_reason_text)

//typedef void (* _func_PrintToScreenLog)(_ptr_ screen_log, char* format, ...);
//#define b_PrintToScreenLog(format, ...) ((_func_PrintToScreenLog)0x553C40)(o_ScreenLogStruct, (char*)(format), __VA_ARGS__)
#define b_PrintToScreenLog(format, ...) ((void (__cdecl *)(_ptr_, char*, ...))0x553C40)(o_ScreenLogStruct, (char*)(format), __VA_ARGS__)

typedef int (__cdecl * _func__beginthread)(_ptr_ func, SIZE_T dwStackSize, _ptr_ arg);
#define o__beginthread(func, stack_size, arg) ((_func__beginthread)0x61A56C)((_ptr_)(func), (SIZE_T)(stack_size), (_ptr_)(arg))




//////typedef LRESULT (CALLBACK *_func_WndProc)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//////#define o_WndProc(hWnd, message, wParam, lParam) ((_func_WndProc)0x4F8290)((HWND)(hWnd),(UINT)(message),(WPARAM)(wParam),(LPARAM)(lParam))


NOALIGN struct _InputMgr_
{
 __declspec(noinline) void SendEventMsg(int type, int subtype, int id, int x, int y, int flags, int flags_2, int new_param) // +0h
 {
  if ( (_ptr_)this )
  {
   if ( *((_ptr_ *)(_ptr_)this + 13) == 1 )
   {
    _ptr_ v = 32 * *((_ptr_ *)(_ptr_)this + 527);
    _EventMsg_ * msg = (_EventMsg_ *)((_ptr_)this + v + 56);
    *(_ptr_ *)((_ptr_)this + v + 68) = 0;

    ///
    msg->type = type;
    msg->subtype = subtype;
    msg->item_id = id;
    msg->x_abs = x;
    msg->y_abs = y;
    msg->flags = flags;
    msg->flags_2 = flags_2;
    msg->new_param = new_param;
    ///

    ++*((_ptr_ *)(_ptr_)this + 527);
    *((_ptr_ *)(_ptr_)this + 527) %= 64;
    if ( *((_ptr_ *)(_ptr_)this + 526) == *((_ptr_ *)(_ptr_)this + 527) )
    {
     *((_ptr_ *)(_ptr_)this + 526) += 1;
     *((_ptr_ *)(_ptr_)this + 526) %= 64;
    }
    *((_ptr_ *)(_ptr_)this + 597) = 0;
   }
  }
 }
 
 
 _byte_ f4[48]; // +4h
 
 // Возможен ли приём событий.
 _bool32_ CanRecieveMsg; // +34h
 // Принятые события.
 // При окончании массива он начинает заполняться сначала (т. е. будут затираться самые ранние события).
 _EventMsg_ Msg[64]; // +38h
 // Номер первого события для обработки.
 // При переполнении массива будет изменяться, чтобы всегда указывать на самое раннее сообщение.
 _int_ FirstMsg_ix; // +838h
 // Номер события, в которое запишется следующее принятое.
 _int_ NextMsg_ix; // +83Ch
 
 _byte_ f840[288]; // +840h
 
 
 // Взятие первого события из очереди.
 // out_event_msg - адрес сообщения, в которое запишется информация.
 inline void Peek_Event(_EventMsg_* out_event_msg)
 {
   CALL_2(void, __thiscall, 0x4EC660, this, out_event_msg);
 }
 
};



// CALL_1(int, __fastcall, 0x59A770, "BIND.wav");
// Sound_Play_Wav("BIND.wav");
// void Sound_Play_Wav (const char* name_wav)
// {
//  _int64_ ptr_wav = CALL_1(_int64_, __fastcall, 0x59A770, name_wav);
  
//  // _int32_ __thiscall Sound_WaitForWavToPlay(int this, int a2, int a3)
//  // Sound_Wait_Play_Wav
//  CALL_3(_int32_, __thiscall, 0x59A7C0, -1, );
//  return; 
// }

// CALL_1(int, __fastcall, 0x59A770, "BIND.wav");
// Sound_Play_Wav("BIND.wav");
/*_int64_ Sound_Play_Wav (const char* name_wav)
{
  return CALL_1(_int64_, __fastcall, 0x59A770, name_wav);
}*/

_byte_ Sound_Play_Wav (const char* name_wav)
{
  return CALL_3(_byte_, __fastcall, 0x59A890, name_wav, -1, 3);
}


// Менеджер звука (размер неизвестен, пока - для описания методов).
NOALIGN struct _SoundMgr_
{
  _byte_ f0[216]; // +0h
  
  // Старт проигрывания звука (возвращения индекса среди проигрываемых звуков).
  inline _dword_ StartSample(_Wav_* Wav)
  {
    return CALL_2(_dword_, __thiscall, 0x59A510, this, Wav);
  }
};

// ********************************************


// Состояние банка существ.
// Каждый банк может быть в одном из четырёх состояний, случайно выбирающемся в начале игры.
// Состояние определяет охрану и награду банка.
NOALIGN struct _CrBankState_
{
  // Защитники банка.
  _Army_ defenders; // +0h
  
  // Количества ресурсов, входящих в составе награды.
  _int_ resources_award[7]; // +38h
  
  // Тип существа, входящего в состав награды.
  _int_ creatures_award_ix; // +54h
  // Количество существ соответствующего типа, входящее в состав награды.
  _byte_ creatures_award_count; // +58h
  
  // Абсолютное значение шанса выпадения данного состояния.
  // Реальный шанс зависит от абсолютных значений всех состояний, но обычно они в сумме дают 100, т. е. это проценты.
  _byte_ chance; // +59h
  
  // Шанс появления улучшенного стека среди защитников банка при взятии в процентах.
  _byte_ upgrade_chance; // +5Ah
  
  // Количество артефактов-сокровищ, входящих в состав награды.
  _byte_ arts_treasure_count; // +5Bh
  // Количество малых артефактов, входящих в состав награды.
  _byte_ arts_minor_count; // +5Ch
  // Количество великих артефактов, входящих в состав награды.
  _byte_ arts_major_count; // +5Dh
  // Количество артефактов-реликтов, входящих в состав награды.
  _byte_ arts_relic_count; // +5Eh
  
  // Результат выравнивания, не используется.
  _byte_ dummy_f5F[1]; // +5Fh
};



// Тип банка существ как объекта на карте.
// Хранит в себе возможные состояния банка существ (т. е. его охрану и награду).
NOALIGN struct _CrBankType_
{
  // Всегда 1.
  _byte_ setup; // +0h
  
  // Результат выравнивания, не используется.
  _byte_ dummy_f1[3]; // +1h
  
  // Имя банка.
  _HStringA_ name; // +4h
  
  // Возможные состояния банка.
  _CrBankState_ States[4]; // +Ch
  
  
  // Конструктор.
  inline _CrBankType_* Contruct()
  {
    return CALL_1(_CrBankType_*, __thiscall, 0x47A400, this);
  }
};



// ********************************************

NOALIGN struct _NewScenarioDlg_ : public _Dlg_
{
  _byte_ field_48[24]; //+72
  _dword_ time_stored; // +96 (используется для даблклика)
  _bool8_ is_load_game; //+100
  _bool8_ is_save_game; //+101
  _bool8_ is_generated_maps; //+102
  _byte_ field_67[789];
  _bool8_ is_advanced_options; //+892
  _bool8_ is_select_scenario; //+893
  _bool8_ is_rmg_options; //+894
  _bool8_ is_rmg; //+895

  // +6304 dd РМГ: размер карты: 36/72/108/144
  // +6308 dd РМГ: количество уровней: 1/2
  // +6312 dd РМГ: количество игроков-людей: 1-8, -1(рандом)
  // +6316 dd РМГ: количество команд игроков-людей: 0-7, -1(рандом)
  // +6320 dd РМГ: количество игроков-компьютеров: 0-7, -1(рандом)
  // +6324 dd РМГ: количество команд игроков-компьютеров: 0-6, -1(рандом)
  // +6328 dd РМГ: водоносность 0,1,2 и 3
  // +6328 dd РМГ: сила монстров 0,1,2 и -1
  // +

  inline _dword_ UpdateRmgSettingsButtonsStatuses() { return CALL_1(_dword_, __thiscall, 0x57F240, this); }

};


// Внешнее жилище на карте. // размер 92 байта
NOALIGN struct _Dwelling_
{
  // Тип жилища как объекта (17 - обычное, 20 - с 4 существами).
  _byte_ type;
  // Подтип жилища как объекта.
  _byte_ subtype;
  _byte_ f2;
  _byte_ f3;
  // Типы существ, доступных для найма (-1 - нет).
  _int_  creature_types[4];
  // Количества существ, доступных для найма.
  _word_ creature_counts[4];
  // Защитники жилища.
  _Army_ defenders;
  // X-координата на карте.
  _byte_ x;           // +54 db (3)
  // Y-координата на карте.
  _byte_ y;           // +55 db
  // Находится ли в подземелье.
  _bool8_ l;
  // Игрок-хозяин (-1 - нет).
  _int8_ owner_ix;
  _byte_ f58;
  _byte_ f59;
  _byte_ f5A;
  _byte_ f5B;
  
  // Конструктор.
  inline _Dwelling_* Contruct()
  {
    return CALL_1(_Dwelling_*, __thiscall, 0x4B8250, this);
  }
};

// ********************************************

// 12 bytes. Сокровище зоны генератора случйных карт.
NOALIGN struct _ZoneTreasure_
{
  // +0. Минимальная ценность.
  _int32_ min_value;
  
  // +4. Минимальная ценность.
  _int32_ max_value;
  
  // +8. Частота появления.
  _int32_ density;
};


// 28 bytes. Связь зоны  генератора случйных карт с другой.
NOALIGN struct _ZoneConnection_
{
  // +0. Настройки зоны, с которой связана текущая.
  _ZoneSettings_ *another_zone_settings;
  
  // +4. Ценность прохода.
  _int32_ value;
  
  // +8. Широкий ли проход.
  _bool8_ is_wide;
  
  // +9. Охраняется ли стражем границы.
  _bool8_ has_border_guard;
  
  // +10. Была ли уже создана на заготовке карты.
  _bool8_ is_created;
  
  // +11. Результат выравнивания, не используется.
  _byte_ dummy_f11[1];
  
  // +12. Минимальное количество зон человека, необходимое для появления связи.
  _int32_ min_human_pos;
  
  // +16. Максимальное количество зон человека, подходящее для появления связи.
  _int32_ max_human_pos;
  
  // +20. Минимальное количество зон игроков, необходимое для появления связи.
  _int32_ min_total_pos;
  
  // +24. Максимальное количество зон игроков, подходящее для появления связи.
  _int32_ max_total_pos;
};


// 212 bytes. Настройки зоны генератора случйных карт.
NOALIGN struct _ZoneSettings_
{
  // +0. Номер зоны.
  _int32_ id;
  
  // +4. Тип зоны (0 - зона человека, 1 - зона ИИ, 2 - сокровищницы, 3 - пустая).
  _int32_ type;
  
  // +8. Базовый размер зоны.
  _int32_ base_size;
  
  // +12. Минимальное количество зон человека, необходимое для появления зоны.
  _int32_ min_human_pos;
  
  // +16. Максимальное количество зон человека, подходящее для появления зоны.
  _int32_ max_human_pos;
  
  // +20. Минимальное количество зон игроков, необходимое для появления зоны
  _int32_ min_ai_pos;
  
  // +24. Максимальное количество зон игроков, подходящее для появления зоны.
  _int32_ max_ai_pos;
  
  // +28. Игрок - владелец зоны.
  _int32_ owner;
  
  // +32. Минимальное количество городов без форта игрока.
  _int32_ min_player_towns;
  
  // +36. Минимальное количество городов с фортом игрока.
  _int32_ min_player_castles;
  
  // +40. Частота появления городов без форта игрока.
  _int32_ player_towns_density;
  
  // +44. Частота появления городов с фортом игрока.
  _int32_ player_castles_density;
  
  // +48. Минимальное количество нейтральных городов без форта.
  _int32_ min_neutral_towns;
  
  // +52. Минимальное количество нейтральных городов с фортом.
  _int32_ min_neutral_castles;
  
  // +56. Частота появления нейтральных городов без форта.
  _int32_ neutral_towns_density;
  
  // +60. Частота появления нейтральных городов с фортом.
  _int32_ neutral_castles_density;
  
  // +64. Должны ли все города зоны принадлежать одному типу.
  _bool8_ towns_are_the_same_type;
  
  // +65. Доступность городов.
  _bool8_ towns_aval[9];
  
  // +74. Результат выравнивания, не используется.
  _byte_ dummy_f4A[2];
  
  // +76. Минимальное количество шахт каждого типа.
  _int32_ min_mines[7];
  
  // +104. Частота появления шахт каждого типа.
  _int32_ mines_density[7];
  
  // +132. Соответствует ли тип территории родной земле города.
  _bool8_ terr_match_to_town;
  
  // +133. Доступности типов территорий.
  _bool8_ terrs_aval[8];
  
  // +141. Результат выравнивания, не используется.
  _byte_ dummy_f8D[3];
  
  // +144. Сила монстров (0 - нет монстров, 1 - слабые, 2 - средние, 3 - сильные).
  _int32_ monsters_strength;
  
  // +148. Соответствуют ли типы монстров типу города.
  _bool8_ monsters_match_to_town;
  
  // +149. Доступности монстров из городов.
  _bool8_ monsters_towns_aval[9];
  
  // +158. Результат выравнивания, не используется.
  _byte_ dummy_f9E[2];
  
  // +160. Сокровища зоны.
  _ZoneTreasure_ treasure[3];
  
  // +196. Связи с другими зонами.
  _List_<_ZoneConnection_> connections;
};


// структура курсора мыши (размер 144 байта)
NOALIGN struct _MouseMgr_ : _Struct_
{
  _Manager_ mgr;    // 0..56
  _int_ bNoChangePointer; // + 0x38
  _TagRect_ LastDraw;         // +60 0x3C
  _int_ type;                 // +76 0x4C
  _int_ cadre;                // +80 0x50
  _Def_* Sprite;              // +84 0x54
  _int_ ImageX;               // +88 0x58
  _int_ ImageY;               // +92 0x5C
  _int_ DisableCount;         // +96 0x60
  _bool8_ SystemPointerIsOn;  // +100 0x64
  _byte_ f_65[3];             // +101..103 (выравнивание)
  _int_ iHideCount;           // +104 0x68
  _int_ Busy;                 // +108 0x6C
  _int_ unknown1;             // +112 0x70
  _int_ unknown2;             // +116 0x74
  LPCRITICAL_SECTION CriticalSection; // +120 0x78

 // отключить курсор мыши
 inline void MouseOFF() { CALL_1(void, __thiscall, 0x50D740, this); } 
 // включить курсор мыши
 inline void MouseON(_byte_ show_cursor = 1) { CALL_2(void, __thiscall, 0x50D7B0, this, show_cursor); }
 // сменить кадр курсора мыши
 inline void SetMouseCursor(_int_ cadre, _int_ type) { CALL_3(void, __thiscall, 0x50CEA0, this, cadre, type); }
 inline void SetDefaultCursor() { CALL_3(void, __thiscall, 0x50CEA0, this, 0, 0); }
};


// структура видеороликов smk и bik (размер 20 байт)
NOALIGN struct _Video_
{
  char* Name;           // +0
  char* LoopName;       // +4
  _byte_ IsBink;        // +8 
  _byte_ FadeInLoop;    // +9
  _byte_ FadeOutAfter;  // +10  
  _byte_ Preload;       // +11
  _int32_ unk_C;        // +12
  _int32_ unk_10;       // +16
};

NOALIGN struct _VideoBINK_
{
  _int_ type;
  _int_ unknown;
  _int_ visible;
  _int_ video[2];
  _int_ pcx16_buffer;
  _int_ pcx16_scanlineSize;
  _int_ pcx16_height;
  _int_ x;
  _int_ y;
  _int_ width;
  _int_ hight;
  _int_ index;
  _int_ loop;
  _int_ animate;
  _int_ init;
};

NOALIGN struct _VideoSMK_
{
  _byte_ init;
  _int_ visible;
  _int_ video[2];
  _int_ x;
  _int_ y;
  _int_ width;
  _int_ hight;
  _int_ index;
  _int_ loop;
  _int_ animate;
  _int_ play;
};

#define o_VideoBINK ((_VideoBINK_*)0x694CF0)
#define o_VideoSMK ((_VideoSMK_*)0x69FE55)

#define o_VideoArray (*(_Video_**)0x44D5C5)

#define o_VideoIsBink (*(_int_*)0x6987F8)
#define o_VideoIsSmack (*(_int_*)0x69FE55)

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// структура передачи данных по сети
struct _NetData_
{
 _int_ recipient_id;        // +0 (номер игрока кому передаётся. (-1 = всем) )
 _int_ field_04;            // +4
 _int_ msg_id;              // +8 (id данных)
 _int_ size;                // +12   (размер буфера (20 + size shortData))
 _int_ field_10;            // +16
 _int_ shortData;           // +20 (наши данные, могут иметь больший объем)
 // _int_ shortData1;       // при необходимости
 // _int_ shortData2;       // при необходимости

 inline _int32_ SendData() {return CALL_4(_int32_, __fastcall, 0x5549E0, this, 127, 0, 1);}
 inline _int32_ SendShortData() {return CALL_1(_int32_, __thiscall, 0x481CB0, this);} 
};

// Переписанная геройская функция загрузки и проигрывания звука.
_Sample_ __fastcall rwr_Load_And_Start_Sample(_cstr_ WavName);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// основные WOG функции //////////////////////////////////////////////////////////////////////////////////////////////////////

// вызов функции ERM (опасный метод: не обнуляются переменные y, x)
inline void ERM_FU_CALL(int number_function) {CALL_1(void, __cdecl, 0x74CE30, number_function);}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////      Командирские функции by [igrik]       ///////////////////////////////////////////////////////////////////////////////////////

#define o_NPC_COUNT (*(_int_*)0x4BD145)   // кол-во командиров в игре (привязано к кол-ву героев)
#define o_Npc ((_Npc_*)0x28620C0)         // получение структуры командира

// Структура командира 0x128h (296)
NOALIGN struct _Npc_
{
 _int_ on;               // 0x00     +0    Доступность
 _int_ alive;            // 0x04     +4    Жив_или_мёртв  
 _int_ id;               // 0x08     +8    Номер_героя_хозяина (ну и номер командира) 
 _int_ type;             // 0x0C     +12   Тип_командира
 _int_ type_Hero;        // 0x10     +16   Тип_героя
 _int_ LastExpaInBattle; // 0x14     +20   Опыт в прошлых битвах
 _dword_ CustomPrimary;  // 0x18     +24   Если установить 1 (вкл), первичные навыки не будут изменяться с продвижением командира по уровням
                         //                Если установить 0, то здоровье и урон  будут автоматически прибавляться вместе с уровнем командира (из ERM Help = CO:P)
 _int_ attack;           // 0x1C     +28   Атака
 _int_ defence;          // 0x20     +32   Защита
 _int_ hit_points;       // 0x24     +36   Здоровье
 _int_ damage;           // 0x28     +40   Урон
 _int_ spell_power;      // 0x2C     +44   Сила_магии
 _int_ speed;            // 0x30     +48   Скорость
 _int_ resistance;       // 0x34     +52   Сопротивление

 _int_ lvl_attack;       // 0x38     +56   Уровень_Атаки
 _int_ lvl_defence;      // 0x3C     +60   Уровень_Защиты
 _int_ lvl_hit_points;   // 0x40     +64   Уровень_Здоровья
 _int_ lvl_damage;       // 0x44     +68   Уровень_Урона
 _int_ lvl_spell_power;  // 0x48     +72   Уровень_Сила_магии
 _int_ lvl_speed;        // 0x4C     +76   Уровень_Скорости
 _int_ lvl_resistance;   // 0x50     +80   Уровень_Сопротивления

 _word_ arts[10][8];     // 0x54     +84   Номер_артефакта; Кол-во проведённых с ним битв
 _char_ name[32];        // 0xF4     +244  Имя
 _int_ old_expa;         // 0x114    +276  Старый_опыт_героя
 _int_ now_expa;         // 0x118    +280  Текущий_опыт
 _int_ now_level;        // 0x11C    +284  Текущий_уровень (при отображении добавляем +1)
 _dword_ specBon[2];     // 0x120    +288  Особые_бонусы(сумма_битов); Запрещенные_бонусы(сумма_битов)
};

// функция получения адреса структуры командира
 inline _Npc_*  GetNpc(_int_ hero_id) {return ((_Npc_ *)(0x28620C0 + 296 * hero_id));}

 // функция получения строк из командирского текстовика "znpc00.txt" 
 inline char* Get_ITxt(int StrNum, int ItemNum) {return CALL_3 (char*, __cdecl, 0x77710B, StrNum, ItemNum, 0x2860724);}
 // функция получения строк из командирского текстовика "znpc01.txt" Имена и биографии
 inline char* Get_ITxtBio(int StrNum, int ItemNum) {return CALL_3 (char*, __cdecl, 0x77710B, StrNum, ItemNum, 0x286072C);}
// функция получения строк из  текстовика "zcrexp.txt"
 inline char* Get_ITxtExp(int StrNum) {return CALL_3 (char*, __cdecl, 0x77710B, StrNum -1, 1, 0x847D88);}
 // функция получения силы первичного командирского навыка
 inline int Get_NpcSkillPower(_Npc_* npc, int skill_id) {return CALL_2 (int, __thiscall, 0x769460, npc, skill_id);}
 // функция получения строк из переменной z
 inline char* GetText_FromERM(int ptr_String)    {int i = 0;  return CALL_3(char*, __cdecl, 0x73DF05, ptr_String, 0, &i);} 
 /* inline char* GetText_FromERM(int ptr_String, int* length)    {int i = 0;  return CALL_3(char*, __cdecl, 0x73DF05, ptr_String, 0, length);} */
 inline char* GetText_FromZVar(int z_num) {return CALL_3(char*, __cdecl, 0x73DF05, 0x9271E8 + 512*z_num, 1, 0);}
 inline char* GetText_FromERT(int z_num)  {return CALL_1 (char*, __cdecl, 0x776620, z_num);}
 
// структура опыта стека
 #define o_CrExpo_ ((_CrExpo_*)0x860550)         
// Структура опыта монстра 340
NOALIGN struct _CrExpo_: _Struct_
{
  _dword_ Expo; // тек. опыт на 1 существо
  _dword_ Num;  // число существ
  _byte_ field_0C[332]; 
};


char* GetShortFileName_Y(char* filename)
  {
    char* str_f = filename;
    char* str_r = NULL;

    if (filename)
    {
      for (int i = strlen(str_f) - 1; i >= 0; i--)
        if (str_f[i] == '\\')
        {
          str_r = str_f + i + 1;
          break;
        }

      if (!str_r) str_r = str_f;
    }

    return str_r;
  }

int GetWoGOptionsStatus(int option_id)
{
  return DwordAt(0x2771920 + (option_id * 4) );
}

void WoG_ErrorMsg(int type, int line)
{
  return CALL_2(void, __cdecl, 0x712272, type, line);
}

int WoG_StrLength(char* Source) 
{
  return CALL_1(int, __cdecl, 0x710B53, Source);
}

void WoG_StrCopy(char* Dest, int length, char* Source)
{
  return CALL_3(void, __cdecl, 0x710B9B, Dest, length, Source);
}

void WoG_StrCanc(char *Dest, int length, char *Source1, char *Source2) {
    return CALL_4(void, __cdecl, 0x710C1A, Dest, length, Source1, Source2);
}

void WoG_SplitPath(char *all, char *path, char *name) {
    return CALL_3(void, __cdecl, 0x716701, all, path, name);
}

int WoG_FindCData(int num) {
    return CALL_1(int, __cdecl, 0x771A13, num); 
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// Реализация объявленных функций //////////////////////////////

inline _bool8_ _Resources_::EnoughResources(_Resources_* cost)
{
    _bool8_ result = false;
    while (!result)
    {
        if (cost->wood > wood)
            break;
        if (cost->mercury > mercury)
            break;
        if (cost->ore > ore)
            break;
        if (cost->sulfur > sulfur)
            break;
        if (cost->crystal > crystal)
            break;
        if (cost->jems > jems)
            break;
        if (cost->gold > gold)
            break;
        result = true;
    }

    return result;
}

inline void _Resources_::RemoveResources(_Resources_* cost)
{
    wood -= cost->wood;
    mercury -= cost->mercury;
    ore -= cost->ore;
    sulfur -= cost->sulfur;
    crystal -= cost->crystal;
    jems -= cost->jems;
    gold -= cost->gold;
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////  

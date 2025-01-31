NOALIGN struct _AdvMgr_: _Struct_ // size: 952 bytes = 0x3B8
{
  _Manager_ mgr;              // 0...56
  _ptr_ pNetMsgHandler;       // +56 0x38
  _byte_ DebugShowFPS;        // +60 0x3C
  _byte_ DebugViewAll;        // +61 0x3D
  _byte_ f_3E[2];         // +62..63 выравнивание
  _int_ advCommand;           // +64 0x40
  _ptr_ advWindow;            // +68 0x44
  _ptr_ pRouteArray;          // +72 0x48
  _int_ bShowRoute;           // +76 0x4C
  _int_ seedingValid;         // +80 0x50
  _int_ fullySeeded;          // +84 0x54
  _int_ lastTerrain;          // +88 0x58
  _GameMap_* map;             // +92 0x5C 
  _Def_* groundTileset[10];   // +96 0x60
  _Def_* riverTileset[5];     // +136 0x88
  _Def_* roadTileset[4];      // +156 0x9C
  _Def_* borderTileset;       // +172 0xAC
  _Def_* arrowTileset;        // +176 0xB0
  _Def_* gemIcons[4];         // +180 0xB4
  _Def_* starTileset;         // +196 0xC4
  _Def_* radarIcons;          // +200 0xC8
  _Def_* cloudIcons;          // +204 0xCC
  _H3Vector_ CachedGraphics;  // +208 0xD0
  _Def_* monAttackSprites;    // +224 0xE0
  type_point mapOrigin;       // +228 0xE4
  type_point lastMapHover;    // +232 0xE8
  _int_ lastHoverX;           // +236 0xEC
  _int_ lastHoverY;           // +240 0xF0
  _int_ scrollX;              // +244 0xF4
  _int_ scrollY;              // +248 0xF8
  _int_ animFrame;            // +252 0xFC
  _int_ animCtr;              // +256 0x100
  _byte_ animCtrPaused;       // +260 0x104
  _byte_ f_105[3];        // +261...263 выравнивание
  _int_ flagFrame;            // +264 0x108
  _Def_* cursorIcons[18];     // +268 0x10C
  _Def_* boatIcons[3];        // +340 0x154
  _Def_* boatFrothIcons[3];   // +352 0x160
  _Def_* flagIcons[8];        // +364 0x16C
  _Def_* boatFlagIcons[24];   // +396 0x18C
  _byte_ heroVisible;         // +492 0x1EC
  _byte_ f_1ED[3];        // +493...495 выравнивание
  _int_ heroType;             // +496 0x1F0
  _int_ heroDirection;        // +500 0x1F4
  _int_ heroBaseFrame;        // +504 0x1F8
  _int_ heroSequence;         // +508 0x1FC
  _int_ heroFrameCount;       // +512 0x200
  _int_ heroTurning;          // +516 0x204
  _int_ heroDrawn;            // +520 0x208
  _byte_ bCurHeroMobile;      // +524 0x20C
  _byte_ f_20D[3];        // +525...527 выравнивание
  _int_ iShowMode;            // +528 0x210
  _int_ bForceCompleteDraw;   // +532 0x214
  _int_ monAttackObjIndex;    // +536 0x218
  _int_ monAttackSpriteIndex; // +540 0x21C
  _int_ monAttackFlip;        // +544 0x220
  _int_ touchedSounds;        // +548 0x224
  _SoundNode_ soundArray[4];  // +552 0x228
  _Wav_* loopedSample[70];    // +584 0x248
  _Wav_* heroSamples[11];     // +864 0x360
  _int_ bHeroLogoShowing;     // +908 0x38C
  _byte_ bHeroMoving;         // +912 0x390
  _byte_ f_391[3];        // +913...915 выравнивание
  _int_ CurrentBottomView;    // +916 0x394 (enum EBottomViewType)
  _int_ BottomViewOverride;   // +920 0x398 (enum EBottomViewType)
  _int_ BottomViewOverrideEndTime;  // +924 0x39C
  _int_ BottomViewResource;   // +928 0x3A0
  _int_ BottomViewResourceQty;// +932 0x3A4
  _H3Str_ BottomViewText;     // +936 0x3A8 (std::string)
  // end: +952 0x3B8
};

_SoundNode_ // Size = 8
{
  _int_ soundId; // enum e_looping_sound_id
  _int_ priority;
}

enum AdvManager::EBottomViewType
{
  BVTYPE_NONE             = 0,
  BVTYPE_NEW_TURN         = 1,
  BVTYPE_KINGDOM          = 2,
  BVTYPE_HERO             = 3,
  BVTYPE_TOWN             = 4,
  BVTYPE_ENEMY_TURN       = 5,
  BVTYPE_RESOURCE_MESSAGE = 6,
  BVTYPE_MESSAGE          = 7,
  BVTYPE_HOLD            = 8
}
0x40fc : Length = 622, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_ENUMERATE, public, value = 0, name = 'SELECT_NULL'
	list[1] = LF_ENUMERATE, public, value = 1, name = 'SELECT_MOVE'
	list[2] = LF_ENUMERATE, public, value = 2, name = 'SELECT_FLY'
	list[3] = LF_ENUMERATE, public, value = 3, name = 'SELECT_SPECIAL_ATTACK'
	list[4] = LF_ENUMERATE, public, value = 4, name = 'SELECT_TENT'
	list[5] = LF_ENUMERATE, public, value = 5, name = 'SELECT_ARMY_INFO'
	list[6] = LF_ENUMERATE, public, value = 6, name = 'CBT_ARROW_POINTER'
	list[7] = LF_ENUMERATE, public, value = 7, name = 'const_attack_northeast'
	list[8] = LF_ENUMERATE, public, value = 7, name = 'SELECT_ATTACK'
	list[9] = LF_ENUMERATE, public, value = 8, name = 'const_attack_east'
	list[10] = LF_ENUMERATE, public, value = 9, name = 'const_attack_southeast'
	list[11] = LF_ENUMERATE, public, value = 10, name = 'const_attack_southwest'
	list[12] = LF_ENUMERATE, public, value = 11, name = 'const_attack_west'
	list[13] = LF_ENUMERATE, public, value = 12, name = 'const_attack_northwest'
	list[14] = LF_ENUMERATE, public, value = 13, name = 'const_attack_up'
	list[15] = LF_ENUMERATE, public, value = 14, name = 'const_attack_down'
	list[16] = LF_ENUMERATE, public, value = 15, name = 'SELECT_SPECIAL_ATTACK_BROKEN'
	list[17] = LF_ENUMERATE, public, value = 16, name = 'SELECT_ATTACK_WALL'
	list[18] = LF_ENUMERATE, public, value = 17, name = 'SELECT_FIRST_AID'
	list[19] = LF_ENUMERATE, public, value = 18, name = 'SELECT_SACRIFICE'
	list[20] = LF_ENUMERATE, public, value = 19, name = 'SELECT_TELEPORT'
	list[21] = LF_ENUMERATE, public, value = 20, name = 'SELECT_CREATURE_SPELL'
	list[22] = LF_ENUMERATE, public, value = 21, name = 'SELECT_ENEMY_TENT'
	list[23] = LF_ENUMERATE, public, value = 22, name = 'const_select_tower_info'



	0x40fe : Length = 286, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_ENUMERATE, public, value = (LF_CHAR) -1(0xFF), name = 'const_no_wall_target'
	list[1] = LF_ENUMERATE, public, value = 0, name = 'eTargetUpperTower'
	list[2] = LF_ENUMERATE, public, value = 1, name = 'eTargetUpperWall'
	list[3] = LF_ENUMERATE, public, value = 2, name = 'eTargetMidUpperWall'
	list[4] = LF_ENUMERATE, public, value = 3, name = 'eTargetGate'
	list[5] = LF_ENUMERATE, public, value = 4, name = 'eTargetMidLowerWall'
	list[6] = LF_ENUMERATE, public, value = 5, name = 'eTargetLowerWall'
	list[7] = LF_ENUMERATE, public, value = 6, name = 'eTargetLowerTower'
	list[8] = LF_ENUMERATE, public, value = 7, name = 'eTargetMainBuilding'
	list[9] = LF_ENUMERATE, public, value = 8, name = 'kNumWallTargets'
	list[10] = LF_ENUMERATE, public, value = 0, name = 'const_first_wall_target'



	0x4317 : Length = 122, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_MEMBER, public, type = T_SHORT(0011), offset = 0
		member name = 'target_hex'
	list[1] = LF_MEMBER, public, type = T_SHORT(0011), offset = 2
		member name = 'blocked_row'
	list[2] = LF_MEMBER, public, type = T_SHORT(0011), offset = 4
		member name = 'hit_x'
	list[3] = LF_MEMBER, public, type = T_SHORT(0011), offset = 6
		member name = 'hit_y'
	list[4] = LF_MEMBER, public, type = 0x430F, offset = 8
		member name = 'wall'
	list[5] = LF_ONEMETHOD, public, VANILLA, index = 0x4318, name = 'get_blocked_hex'



	0x431c : Length = 138, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_MEMBER, public, type = 0x1BAC, offset = 0
		member name = 'type'
	list[1] = LF_MEMBER, public, type = 0x431B, offset = 4
		member name = 'Sprite'
	list[2] = LF_MEMBER, public, type = 0x431B, offset = 8
		member name = 'Missile'
	list[3] = LF_MEMBER, public, type = T_INT4(0074), offset = 12
		member name = 'X'
	list[4] = LF_MEMBER, public, type = T_INT4(0074), offset = 16
		member name = 'Y'
	list[5] = LF_MEMBER, public, type = T_INT4(0074), offset = 20
		member name = 'Facing'
	list[6] = LF_MEMBER, public, type = T_INT4(0074), offset = 24
		member name = 'Sequence'
	list[7] = LF_MEMBER, public, type = T_INT4(0074), offset = 28
		member name = 'Frame'



		0x431e : Length = 98, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_ENUMERATE, public, value = 0, name = 'eArcherMainBuilding'
	list[1] = LF_ENUMERATE, public, value = 1, name = 'eArcherLowerTower'
	list[2] = LF_ENUMERATE, public, value = 2, name = 'eArcherUpperTower'
	list[3] = LF_ENUMERATE, public, value = 3, name = 'kNumArchers'



	0x4320 : Length = 194, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_MEMBER, public, type = 0x1BAC, offset = 0
		member name = 'CreatureType'
	list[1] = LF_MEMBER, public, type = T_INT4(0074), offset = 4
		member name = 'MainBuildingX'
	list[2] = LF_MEMBER, public, type = T_INT4(0074), offset = 8
		member name = 'MainBuildingY'
	list[3] = LF_MEMBER, public, type = T_INT4(0074), offset = 12
		member name = 'LowerTowerX'
	list[4] = LF_MEMBER, public, type = T_INT4(0074), offset = 16
		member name = 'LowerTowerY'
	list[5] = LF_MEMBER, public, type = T_INT4(0074), offset = 20
		member name = 'UpperTowerX'
	list[6] = LF_MEMBER, public, type = T_INT4(0074), offset = 24
		member name = 'UpperTowerY'
	list[7] = LF_MEMBER, public, type = 0x1001, offset = 28
		member name = 'MissileName'



	0x4434 : Length = 618, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_NESTTYPE, type = 0x442B, TAttributes
	list[1] = LF_MEMBER, public, type = T_SHORT(0011), offset = 0
		member name = 'refX'
	list[2] = LF_MEMBER, public, type = T_SHORT(0011), offset = 2
		member name = 'refY'
	list[3] = LF_MEMBER, public, type = T_SHORT(0011), offset = 4
		member name = 'hexULX'
	list[4] = LF_MEMBER, public, type = T_SHORT(0011), offset = 6
		member name = 'hexULY'
	list[5] = LF_MEMBER, public, type = T_SHORT(0011), offset = 8
		member name = 'hexBRX'
	list[6] = LF_MEMBER, public, type = T_SHORT(0011), offset = 10
		member name = 'hexBRY'
	list[7] = LF_MEMBER, public, type = T_SHORT(0011), offset = 12
		member name = 'fullHexBRY'
	list[8] = LF_MEMBER, public, type = T_UINT4(0075), offset = 16
		member name = 'attributes'
	list[9] = LF_MEMBER, public, type = T_INT4(0074), offset = 20
		member name = 'obstacleIndex'
	list[10] = LF_MEMBER, public, type = T_CHAR(0010), offset = 24
		member name = 'armyGroup'
	list[11] = LF_MEMBER, public, type = T_CHAR(0010), offset = 25
		member name = 'armyIndex'
	list[12] = LF_MEMBER, public, type = T_CHAR(0010), offset = 26
		member name = 'partOfDouble'
	list[13] = LF_MEMBER, public, type = T_INT4(0074), offset = 28
		member name = 'iBodiesInHex'
	list[14] = LF_MEMBER, public, type = 0x442C, offset = 32
		member name = 'deadArmyGroup'
	list[15] = LF_MEMBER, public, type = 0x442C, offset = 46
		member name = 'deadArmyIndex'
	list[16] = LF_MEMBER, public, type = 0x442C, offset = 60
		member name = 'deadPartOfDouble'
	list[17] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 74
		member name = 'bValidMove'
	list[18] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 75
		member name = 'front_move'
	list[19] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 76
		member name = 'mouse_shaded'
	list[20] = LF_MEMBER, public, type = T_CHAR(0010), offset = 77
		member name = 'background_offset'
	list[21] = LF_MEMBER, public, type = 0x187D, offset = 80
		member name = 'obstacleLimitData'
	list[22] = LF_MEMBER, public, type = 0x187D, offset = 96
		member name = 'cloudLimitData'
	list[23] = LF_ONEMETHOD, public, VANILLA, index = 0x442E, name = 'hexcell'
	list[24] = LF_ONEMETHOD, public, VANILLA, index = 0x4430, name = 'get_army'
	list[25] = LF_ONEMETHOD, public, VANILLA, index = 0x4431, name = 'get_dead_army'
	list[26] = LF_ONEMETHOD, public, VANILLA, index = 0x4432, name = 'HasArmy'
	list[27] = LF_ONEMETHOD, public, VANILLA, index = 0x4433, name = 'limits'




_BattleStack_
0x49a1 : Length = 6382, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_NESTTYPE, type = 0x1FE1, __unnamed
	list[1] = LF_NESTTYPE, type = 0x1FE3, TSampleID
	list[2] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 0
		member name = 'bShowAttackFrames'
	list[3] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 1
		member name = 'bShowRangeFrames'
	list[4] = LF_MEMBER, public, type = T_CHAR(0010), offset = 2
		member name = 'iShowAttackFrameType'
	list[5] = LF_MEMBER, public, type = T_CHAR(0010), offset = 3
		member name = 'iNextFrameType'
	list[6] = LF_MEMBER, public, type = T_CHAR(0010), offset = 4
		member name = 'iRemainingFramesToPlay'
	list[7] = LF_MEMBER, public, type = T_INT4(0074), offset = 8
		member name = 'iDrawPriority'
	list[8] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 12
		member name = 'bShowTroopCount'
	list[9] = LF_MEMBER, public, type = T_INT4(0074), offset = 16
		member name = 'groupToAttack'
	list[10] = LF_MEMBER, public, type = T_INT4(0074), offset = 20
		member name = 'indexToAttack'
	list[11] = LF_MEMBER, public, type = T_INT4(0074), offset = 24
		member name = 'attackLimit'
	list[12] = LF_MEMBER, public, type = T_INT4(0074), offset = 28
		member name = 'targetCellIndex'
	list[13] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 32
		member name = 'bShowPowEffect'
	list[14] = LF_MEMBER, public, type = T_INT4(0074), offset = 36
		member name = 'iMirrorSourceIndex'
	list[15] = LF_MEMBER, public, type = T_INT4(0074), offset = 40
		member name = 'iMirrorDestIndex'
	list[16] = LF_MEMBER, public, type = T_INT4(0074), offset = 44
		member name = 'iRoundsLeftBeforeVanish'
	list[17] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 48
		member name = 'IsMoving'
	list[18] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 49
		member name = 'LetsPretendImNotHere'
	list[19] = LF_MEMBER, public, type = 0x1BAC, offset = 52
		member name = 'armyType'
	list[20] = LF_MEMBER, public, type = T_INT4(0074), offset = 56
		member name = 'gridIndex'
	list[21] = LF_MEMBER, public, type = T_INT4(0074), offset = 60
		member name = 'currFrameType'
	list[22] = LF_MEMBER, public, type = T_INT4(0074), offset = 64
		member name = 'currFrameIndex'
	list[23] = LF_MEMBER, public, type = T_INT4(0074), offset = 68
		member name = 'facing'
	list[24] = LF_MEMBER, public, type = T_INT4(0074), offset = 72
		member name = 'walkDirection'
	list[25] = LF_MEMBER, public, type = T_INT4(0074), offset = 76
		member name = 'numTroops'
	list[26] = LF_MEMBER, public, type = T_INT4(0074), offset = 80
		member name = 'numTroopsToShowOverride'
	list[27] = LF_MEMBER, public, type = T_INT4(0074), offset = 84
		member name = 'numTroopsBattleResurrected'
	list[28] = LF_MEMBER, public, type = T_INT4(0074), offset = 88
		member name = 'residualDamage'
	list[29] = LF_MEMBER, public, type = T_INT4(0074), offset = 92
		member name = 'origPos'
	list[30] = LF_MEMBER, public, type = T_INT4(0074), offset = 96
		member name = 'origNumTroops'
	list[31] = LF_MEMBER, public, type = T_INT4(0074), offset = 100
		member name = 'origSpeed'
	list[32] = LF_MEMBER, public, type = T_INT4(0074), offset = 104
		member name = 'origWalkCycleTime'
	list[33] = LF_MEMBER, public, type = T_INT4(0074), offset = 108
		member name = 'origHitPoints'
	list[34] = LF_MEMBER, public, type = T_INT4(0074), offset = 112
		member name = 'iLuckStatus'
	list[35] = LF_MEMBER, public, type = 0x1A9A, offset = 116
		member name = 'sMonInfo'
	list[36] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 212
		member name = 'show_fire_shield'
	list[37] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 213
		member name = 'bSomeUnitsDamaged'
	list[38] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 214
		member name = 'bAllUnitsKilled'
	list[39] = LF_MEMBER, public, type = 0x1B61, offset = 216
		member name = 'iPostPowSpellToCast'
	list[40] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 220
		member name = 'hitByCreature'
	list[41] = LF_MEMBER, public, type = T_INT4(0074), offset = 224
		member name = 'group'
	list[42] = LF_MEMBER, public, type = T_INT4(0074), offset = 228
		member name = 'index'
	list[43] = LF_MEMBER, public, type = T_ULONG(0022), offset = 232
		member name = 'iLastFidgetTime'
	list[44] = LF_MEMBER, public, type = T_INT4(0074), offset = 236
		member name = 'ySpecialMod'
	list[45] = LF_MEMBER, public, type = T_INT4(0074), offset = 240
		member name = 'xSpecialMod'
	list[46] = LF_MEMBER, public, type = T_INT4(0074), offset = 244
		member name = 'bPowSequenceComplete'
	list[47] = LF_MEMBER, public, type = T_32PCHAR(0410), offset = 248
		member name = 'yModify'
	list[48] = LF_MEMBER, public, type = 0x1FE4, offset = 252
		member name = 'sMonFrameInfo'
	list[49] = LF_MEMBER, public, type = 0x495C, offset = 336
		member name = 'stdIcon'
	list[50] = LF_MEMBER, public, type = 0x495C, offset = 340
		member name = 'missileIcon'
	list[51] = LF_MEMBER, public, type = T_INT4(0074), offset = 344
		member name = 'image_height'
	list[52] = LF_MEMBER, public, type = 0x1FE5, offset = 348
		member name = 'armySample'
	list[53] = LF_MEMBER, public, type = T_LONG(0012), offset = 380
		member name = 'expected_move_order'
	list[54] = LF_MEMBER, public, type = T_INT4(0074), offset = 384
		member name = 'numSpellInfluences'
	list[55] = LF_MEMBER, public, type = 0x1FE6, offset = 388
		member name = 'spellInfluence'
	list[56] = LF_MEMBER, public, type = 0x1FE7, offset = 708
		member name = 'spell_level'
	list[57] = LF_NESTTYPE, type = 0x496A, TSpellQueue
	list[58] = LF_MEMBER, public, type = 0x496A, offset = 1028
		member name = 'SpellInfluenceQueue'
	list[59] = LF_MEMBER, public, type = T_REAL32(0040), offset = 1068
		member name = 'PaletteEffect'
	list[60] = LF_MEMBER, public, type = T_INT4(0074), offset = 1072
		member name = 'retaliationCount'
	list[61] = LF_MEMBER, public, type = T_LONG(0012), offset = 1076
		member name = 'blessFactor'
	list[62] = LF_MEMBER, public, type = T_LONG(0012), offset = 1080
		member name = 'curseFactor'
	list[63] = LF_MEMBER, public, type = T_INT4(0074), offset = 1084
		member name = 'antiMagicSpellLevel'
	list[64] = LF_MEMBER, public, type = T_INT4(0074), offset = 1088
		member name = 'bloodlustBonus'
	list[65] = LF_MEMBER, public, type = T_INT4(0074), offset = 1092
		member name = 'precisionBonus'
	list[66] = LF_MEMBER, public, type = T_INT4(0074), offset = 1096
		member name = 'weaknessPenalty'
	list[67] = LF_MEMBER, public, type = T_INT4(0074), offset = 1100
		member name = 'toughskinBonus'
	list[68] = LF_MEMBER, public, type = T_INT4(0074), offset = 1104
		member name = 'disruptiverayPenalty'
	list[69] = LF_MEMBER, public, type = T_INT4(0074), offset = 1108
		member name = 'prayerBonus'
	list[70] = LF_MEMBER, public, type = T_INT4(0074), offset = 1112
		member name = 'mirthBonus'
	list[71] = LF_MEMBER, public, type = T_INT4(0074), offset = 1116
		member name = 'sorrowPenalty'
	list[72] = LF_MEMBER, public, type = T_INT4(0074), offset = 1120
		member name = 'fortuneBonus'
	list[73] = LF_MEMBER, public, type = T_INT4(0074), offset = 1124
		member name = 'misfortunePenalty'
	list[74] = LF_MEMBER, public, type = T_INT4(0074), offset = 1128
		member name = 'slayerLevel'
	list[75] = LF_MEMBER, public, type = T_INT4(0074), offset = 1132
		member name = 'joustBonus'
	list[76] = LF_MEMBER, public, type = T_INT4(0074), offset = 1136
		member name = 'counterstrokeBonus'
	list[77] = LF_MEMBER, public, type = T_REAL32(0040), offset = 1140
		member name = 'frenzyAdjust'
	list[78] = LF_MEMBER, public, type = T_REAL32(0040), offset = 1144
		member name = 'blindFactor'
	list[79] = LF_MEMBER, public, type = T_REAL32(0040), offset = 1148
		member name = 'fire_shield_strength'
	list[80] = LF_MEMBER, public, type = T_REAL32(0040), offset = 1152
		member name = 'poison_penalty'
	list[81] = LF_MEMBER, public, type = T_REAL32(0040), offset = 1156
		member name = 'protectionFromAirFactor'
	list[82] = LF_MEMBER, public, type = T_REAL32(0040), offset = 1160
		member name = 'protectionFromFireFactor'
	list[83] = LF_MEMBER, public, type = T_REAL32(0040), offset = 1164
		member name = 'protectionFromWaterFactor'
	list[84] = LF_MEMBER, public, type = T_REAL32(0040), offset = 1168
		member name = 'protectionFromEarthFactor'
	list[85] = LF_MEMBER, public, type = T_REAL32(0040), offset = 1172
		member name = 'shieldDamageFactor'
	list[86] = LF_MEMBER, public, type = T_REAL32(0040), offset = 1176
		member name = 'airShieldDamageFactor'
	list[87] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 1180
		member name = 'residualBlindness'
	list[88] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 1181
		member name = 'residualParalyze'
	list[89] = LF_MEMBER, public, type = T_LONG(0012), offset = 1184
		member name = 'backlash_chance'
	list[90] = LF_MEMBER, public, type = 0x1A78, offset = 1188
		member name = 'forgetfulness_level'
	list[91] = LF_MEMBER, public, type = T_REAL32(0040), offset = 1192
		member name = 'slowPenalty'
	list[92] = LF_MEMBER, public, type = T_INT4(0074), offset = 1196
		member name = 'tailwindBonus'
	list[93] = LF_MEMBER, public, type = T_INT4(0074), offset = 1200
		member name = 'diseaseDefensePenalty'
	list[94] = LF_MEMBER, public, type = T_INT4(0074), offset = 1204
		member name = 'diseaseAttackPenalty'
	list[95] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 1208
		member name = 'OnNativeTerrain'
	list[96] = LF_MEMBER, public, type = T_INT4(0074), offset = 1212
		member name = 'DefendBonus'
	list[97] = LF_METHOD, count = 2, list = 0x49A2, name = 'army'
	list[98] = LF_ONEMETHOD, public, VANILLA, index = 0x49A9, name = 'Init'
	list[99] = LF_ONEMETHOD, public, VANILLA, index = 0x49AA, name = 'initialize'
	list[100] = LF_ONEMETHOD, public, VANILLA, index = 0x49A8, name = 'InitClean'
	list[101] = LF_ONEMETHOD, public, VANILLA, index = 0x49A8, name = 'LoadResources'
	list[102] = LF_ONEMETHOD, public, VANILLA, index = 0x49A8, name = 'FreeResources'
	list[103] = LF_ONEMETHOD, public, VANILLA, index = 0x49A8, name = 'ResetRound'
	list[104] = LF_ONEMETHOD, public, VANILLA, index = 0x49A8, name = 'EndWalk'
	list[105] = LF_ONEMETHOD, public, VANILLA, index = 0x49AB, name = 'Walk'
	list[106] = LF_ONEMETHOD, public, VANILLA, index = 0x49AC, name = 'WalkTo'
	list[107] = LF_ONEMETHOD, public, VANILLA, index = 0x49AD, name = 'Fly'
	list[108] = LF_ONEMETHOD, public, VANILLA, index = 0x49AE, name = 'FlyTo'
	list[109] = LF_ONEMETHOD, public, VANILLA, index = 0x49AD, name = 'Teleport'
	list[110] = LF_ONEMETHOD, public, VANILLA, index = 0x49AE, name = 'TeleportTo'
	list[111] = LF_ONEMETHOD, public, VANILLA, index = 0x49AF, name = 'adjust_damage'
	list[112] = LF_ONEMETHOD, public, VANILLA, index = 0x49A8, name = 'adjust_hitpoints'
	list[113] = LF_ONEMETHOD, public, VANILLA, index = 0x49AC, name = 'attack_hex'
	list[114] = LF_METHOD, count = 2, list = 0x49B2, name = 'do_attack'
	list[115] = LF_ONEMETHOD, public, VANILLA, index = 0x49B6, name = 'do_multi_head_attack'
	list[116] = LF_METHOD, count = 2, list = 0x49B7, name = 'range_attack'
	list[117] = LF_ONEMETHOD, public, VANILLA, index = 0x49B5, name = 'AttackWall'
	list[118] = LF_ONEMETHOD, public, VANILLA, index = 0x49BA, name = 'Turn'
	list[119] = LF_ONEMETHOD, public, VANILLA, index = 0x49BB, name = 'NeedToTurn'
	list[120] = LF_METHOD, count = 2, list = 0x49BC, name = 'can_cast_resurrect'
	list[121] = LF_ONEMETHOD, public, VANILLA, index = 0x49BD, name = 'can_cast_spell'
	list[122] = LF_ONEMETHOD, public, VANILLA, index = 0x49BF, name = 'can_retaliate'
	list[123] = LF_ONEMETHOD, public, VANILLA, index = 0x49C0, name = 'can_shoot'
	list[124] = LF_ONEMETHOD, public, VANILLA, index = 0x49C3, name = 'cast_caliph_spell'
	list[125] = LF_ONEMETHOD, public, VANILLA, index = 0x49C3, name = 'cast_resurrect'
	list[126] = LF_ONEMETHOD, public, VANILLA, index = 0x49C3, name = 'cast_demonic_resurrect'
	list[127] = LF_ONEMETHOD, public, VANILLA, index = 0x49C4, name = 'check_special_attack'
	list[128] = LF_ONEMETHOD, public, VANILLA, index = 0x49C3, name = 'cast_spell'
	list[129] = LF_ONEMETHOD, public, VANILLA, index = 0x49C5, name = 'check_obstacle_attacks'
	list[130] = LF_ONEMETHOD, public, VANILLA, index = 0x49A8, name = 'clear_AI_values'
	list[131] = LF_ONEMETHOD, public, VANILLA, index = 0x49C6, name = 'consider_attack'
	list[132] = LF_ONEMETHOD, public, VANILLA, index = 0x49C0, name = 'enemy_is_adjacent'
	list[133] = LF_ONEMETHOD, public, VANILLA, index = 0x49C8, name = 'GetAttackMask'
	list[134] = LF_ONEMETHOD, public, VANILLA, index = 0x49C9, name = 'get_adjusted_attack'
	list[135] = LF_ONEMETHOD, public, VANILLA, index = 0x49C9, name = 'get_adjusted_defense'
	list[136] = LF_ONEMETHOD, public, VANILLA, index = 0x49CB, name = 'get_AI_expected_damage'
	list[137] = LF_ONEMETHOD, public, VANILLA, index = 0x49CC, name = 'get_AI_target'
	list[138] = LF_ONEMETHOD, public, VANILLA, index = 0x49CB, name = 'get_AI_target_value'
	list[139] = LF_METHOD, count = 2, list = 0x49CD, name = 'get_AI_target_time'
	list[140] = LF_ONEMETHOD, public, VANILLA, index = 0x49CB, name = 'get_AI_possible_targets'
	list[141] = LF_ONEMETHOD, public, VANILLA, index = 0x49C9, name = 'get_attack_modifier'
	list[142] = LF_METHOD, count = 2, list = 0x49CF, name = 'get_average_damage'
	list[143] = LF_ONEMETHOD, public, VANILLA, index = 0x49D3, name = 'get_berserk_targets'
	list[144] = LF_ONEMETHOD, public, VANILLA, index = 0x49D6, name = 'get_owning_side'
	list[145] = LF_ONEMETHOD, public, VANILLA, index = 0x49D6, name = 'get_controlling_side'
	list[146] = LF_ONEMETHOD, public, VANILLA, index = 0x49D7, name = 'get_owner'
	list[147] = LF_ONEMETHOD, public, VANILLA, index = 0x49D7, name = 'get_controller'
	list[148] = LF_ONEMETHOD, public, VANILLA, index = 0x49D8, name = 'get_defense_damage_modifier'
	list[149] = LF_ONEMETHOD, public, VANILLA, index = 0x49CB, name = 'get_defense_modifier'
	list[150] = LF_ONEMETHOD, public, VANILLA, index = 0x49CE, name = 'get_clockwise'
	list[151] = LF_ONEMETHOD, public, VANILLA, index = 0x49CE, name = 'get_counter_clockwise'
	list[152] = LF_ONEMETHOD, public, VANILLA, index = 0x49D9, name = 'get_fire_shield_strength'
	list[153] = LF_ONEMETHOD, public, VANILLA, index = 0x49DA, name = 'get_loss_combat_value'
	list[154] = LF_ONEMETHOD, public, VANILLA, index = 0x49DB, name = 'get_resurrection_size'
	list[155] = LF_ONEMETHOD, public, VANILLA, index = 0x49D6, name = 'get_second_grid_index'
	list[156] = LF_ONEMETHOD, public, VANILLA, index = 0x49DC, name = 'get_total_combat_value'
	list[157] = LF_ONEMETHOD, public, VANILLA, index = 0x49DD, name = 'get_total_hit_points'
	list[158] = LF_ONEMETHOD, public, VANILLA, index = 0x49DE, name = 'get_unit_combat_value'
	list[159] = LF_ONEMETHOD, public, VANILLA, index = 0x49DB, name = 'get_valid_caliph_spells'
	list[160] = LF_ONEMETHOD, public, VANILLA, index = 0x49E0, name = 'GetBestDirection'
	list[161] = LF_METHOD, count = 2, list = 0x49E1, name = 'is_adjacent'
	list[162] = LF_ONEMETHOD, public, VANILLA, index = 0x49C0, name = 'is_enemy'
	list[163] = LF_ONEMETHOD, public, VANILLA, index = 0x49BE, name = 'is_in_aura'
	list[164] = LF_ONEMETHOD, public, VANILLA, index = 0x49AC, name = 'move_to'
	list[165] = LF_ONEMETHOD, public, VANILLA, index = 0x49A8, name = 'new_turn'
	list[166] = LF_ONEMETHOD, public, VANILLA, index = 0x49C3, name = 'set_AI_expected_damage'
	list[167] = LF_ONEMETHOD, public, VANILLA, index = 0x49E2, name = 'FindPath'
	list[168] = LF_ONEMETHOD, public, VANILLA, index = 0x49A8, name = 'set_retaliation_count'
	list[169] = LF_ONEMETHOD, public, VANILLA, index = 0x49E3, name = 'ValidAttack'
	list[170] = LF_ONEMETHOD, public, VANILLA, index = 0x49A8, name = 'ResetPath'
	list[171] = LF_ONEMETHOD, public, VANILLA, index = 0x49AC, name = 'ValidPath'
	list[172] = LF_ONEMETHOD, public, VANILLA, index = 0x49E4, name = 'ValidFlight'
	list[173] = LF_ONEMETHOD, public, VANILLA, index = 0x49AD, name = 'ValidRange'
	list[174] = LF_ONEMETHOD, public, VANILLA, index = 0x49E5, name = 'DamageEnemy'
	list[175] = LF_ONEMETHOD, public, VANILLA, index = 0x49AD, name = 'Damage'
	list[176] = LF_ONEMETHOD, public, VANILLA, index = 0x49E7, name = 'ComputeBaseDamage'
	list[177] = LF_ONEMETHOD, public, VANILLA, index = 0x49E8, name = 'ComputeAttackerDamageBonuses'
	list[178] = LF_ONEMETHOD, public, VANILLA, index = 0x49EA, name = 'ComputeDefenderDamageBonuses'
	list[179] = LF_ONEMETHOD, public, VANILLA, index = 0x49EB, name = 'ComputeAttackerDamageReduction'
	list[180] = LF_ONEMETHOD, public, VANILLA, index = 0x49D8, name = 'ComputeDefenderDamageReduction'
	list[181] = LF_ONEMETHOD, public, VANILLA, index = 0x49B5, name = 'CancelSpellType'
	list[182] = LF_ONEMETHOD, public, VANILLA, index = 0x49A8, name = 'DecrementSpellRounds'
	list[183] = LF_ONEMETHOD, public, VANILLA, index = 0x49A8, name = 'GoBerserk'
	list[184] = LF_ONEMETHOD, public, VANILLA, index = 0x49EC, name = 'Cure'
	list[185] = LF_ONEMETHOD, public, VANILLA, index = 0x49ED, name = 'CanFit'
	list[186] = LF_ONEMETHOD, public, VANILLA, index = 0x49EE, name = 'DrawToBuffer'
	list[187] = LF_ONEMETHOD, public, VANILLA, index = 0x49EE, name = 'PlayAnimation'
	list[188] = LF_ONEMETHOD, public, VANILLA, index = 0x49A8, name = 'SetupAnimation'
	list[189] = LF_ONEMETHOD, public, VANILLA, index = 0x49EF, name = 'Strength'
	list[190] = LF_ONEMETHOD, public, VANILLA, index = 0x49BE, name = 'IsActive'
	list[191] = LF_ONEMETHOD, public, VANILLA, index = 0x49A8, name = 'CheckLuck'
	list[192] = LF_ONEMETHOD, public, VANILLA, index = 0x49F0, name = 'SetSpellInfluence'
	list[193] = LF_ONEMETHOD, public, VANILLA, index = 0x49B5, name = 'CancelIndividualSpell'
	list[194] = LF_ONEMETHOD, public, VANILLA, index = 0x49A8, name = 'CancelAllSpells'
	list[195] = LF_ONEMETHOD, public, VANILLA, index = 0x49D6, name = 'BottomY'
	list[196] = LF_ONEMETHOD, public, VANILLA, index = 0x49D6, name = 'MidY'
	list[197] = LF_ONEMETHOD, public, VANILLA, index = 0x49D6, name = 'TopY'
	list[198] = LF_ONEMETHOD, public, VANILLA, index = 0x49D6, name = 'LeftX'
	list[199] = LF_ONEMETHOD, public, VANILLA, index = 0x49D6, name = 'RightX'
	list[200] = LF_ONEMETHOD, public, VANILLA, index = 0x49D6, name = 'FrontX'
	list[201] = LF_ONEMETHOD, public, VANILLA, index = 0x49D6, name = 'MidX'
	list[202] = LF_ONEMETHOD, public, VANILLA, index = 0x49F1, name = 'Is'
	list[203] = LF_ONEMETHOD, public, VANILLA, index = 0x49BE, name = 'is_in_area_highlight'
	list[204] = LF_ONEMETHOD, public, VANILLA, index = 0x49EA, name = 'OffsetToFront'
	list[205] = LF_ONEMETHOD, public, VANILLA, index = 0x49B5, name = 'ProcessDeath'
	list[206] = LF_ONEMETHOD, public, VANILLA, index = 0x49F2, name = 'OtherArmyAdjacent'
	list[207] = LF_ONEMETHOD, public, VANILLA, index = 0x49F3, name = 'GetAdjacentCellIndex'
	list[208] = LF_METHOD, count = 2, list = 0x49F4, name = 'get_adjacent_hex'
	list[209] = LF_METHOD, count = 3, list = 0x49F5, name = 'get_attack_direction'
	list[210] = LF_ONEMETHOD, public, VANILLA, index = 0x49F6, name = 'get_multi_head_directions'
	list[211] = LF_ONEMETHOD, public, VANILLA, index = 0x49FA, name = 'get_spell_time'
	list[212] = LF_ONEMETHOD, public, VANILLA, index = 0x49FB, name = 'get_spell_level'
	list[213] = LF_ONEMETHOD, public, VANILLA, index = 0x49C5, name = 'set_inside_area_effect'
	list[214] = LF_ONEMETHOD, public, VANILLA, index = 0x49FC, name = 'play_sample'
	list[215] = LF_ONEMETHOD, public, VANILLA, index = 0x49FC, name = 'stop_sample'
	list[216] = LF_ONEMETHOD, public, VANILLA, index = 0x49FC, name = 'WaitSample'
	list[217] = LF_ONEMETHOD, public, VANILLA, index = 0x49A8, name = 'add_aura'
	list[218] = LF_ONEMETHOD, public, VANILLA, index = 0x49A8, name = 'remove_aura'
	list[219] = LF_ONEMETHOD, public, VANILLA, index = 0x49A8, name = 'remove_binding'
	list[220] = LF_ONEMETHOD, public, VANILLA, index = 0x49BE, name = 'cannot_attack'
	list[221] = LF_METHOD, count = 2, list = 0x49FD, name = 'GetName'
	list[222] = LF_ONEMETHOD, public, VANILLA, index = 0x49BE, name = 'IsIncapacitated'
	list[223] = LF_ONEMETHOD, public, VANILLA, index = 0x4A00, name = 'SetLuck'
	list[224] = LF_ONEMETHOD, public, VANILLA, index = 0x49E7, name = 'GetLuck'
	list[225] = LF_ONEMETHOD, public, VANILLA, index = 0x4A00, name = 'SetMorale'
	list[226] = LF_ONEMETHOD, public, VANILLA, index = 0x49E7, name = 'GetMorale'
	list[227] = LF_ONEMETHOD, public, VANILLA, index = 0x49D6, name = 'GetSpeed'
	list[228] = LF_ONEMETHOD, private, VANILLA, index = 0x49B8, name = 'animate_missile'
	list[229] = LF_METHOD, count = 2, list = 0x4A01, name = 'attack_wall'
	list[230] = LF_ONEMETHOD, private, VANILLA, index = 0x49C3, name = 'do_fire_shield'
	list[231] = LF_ONEMETHOD, private, VANILLA, index = 0x4A04, name = 'do_post_attack'
	list[232] = LF_ONEMETHOD, private, VANILLA, index = 0x49B5, name = 'DoHydraAttack'
	list[233] = LF_METHOD, count = 2, list = 0x4A06, name = 'find_flyer_attack_cell'
	list[234] = LF_ONEMETHOD, private, VANILLA, index = 0x49BE, name = 'LeavesNoBody'
	list[235] = LF_ONEMETHOD, private, VANILLA, index = 0x49AC, name = 'simple_move'
	list[236] = LF_ONEMETHOD, private, VANILLA, index = 0x49D2, name = 'ComputeKarma'
	list[237] = LF_MEMBER, private, type = T_INT4(0074), offset = 1216
		member name = 'iMorale'
	list[238] = LF_MEMBER, private, type = T_INT4(0074), offset = 1220
		member name = 'iLuck'
	list[239] = LF_MEMBER, private, type = T_UCHAR(0020), offset = 1224
		member name = 'reset_this_round'
	list[240] = LF_MEMBER, private, type = T_UCHAR(0020), offset = 1225
		member name = 'is_area_effect_target'
	list[241] = LF_MEMBER, private, type = 0x4998, offset = 1228
		member name = 'bound_armies'
	list[242] = LF_MEMBER, private, type = 0x4998, offset = 1240
		member name = 'binders'
	list[243] = LF_MEMBER, private, type = 0x4998, offset = 1252
		member name = 'aura_clients'
	list[244] = LF_MEMBER, private, type = 0x4998, offset = 1264
		member name = 'aura_sources'
	list[245] = LF_MEMBER, private, type = T_LONG(0012), offset = 1276
		member name = 'AI_expected_damage'
	list[246] = LF_MEMBER, private, type = 0x49C2, offset = 1280
		member name = 'AI_target'
	list[247] = LF_MEMBER, private, type = T_LONG(0012), offset = 1284
		member name = 'AI_target_value'
	list[248] = LF_MEMBER, private, type = T_LONG(0012), offset = 1288
		member name = 'AI_target_distance'
	list[249] = LF_MEMBER, private, type = T_LONG(0012), offset = 1292
		member name = 'AI_possible_targets'
	list[250] = LF_ONEMETHOD, public, VANILLA, (compgenx), index = 0x4A08, name = 'operator='
	list[251] = LF_ONEMETHOD, public, VANILLA, (compgenx), index = 0x49A8, name = '~army'
	list[252] = LF_ONEMETHOD, public, VANILLA, (compgenx), index = 0x4A0A, name = '__vecDelDtor'




_BattleHex_
0x4b04 : Length = 618, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_NESTTYPE, type = 0x442B, TAttributes
	list[1] = LF_MEMBER, public, type = T_SHORT(0011), offset = 0
		member name = 'refX'
	list[2] = LF_MEMBER, public, type = T_SHORT(0011), offset = 2
		member name = 'refY'
	list[3] = LF_MEMBER, public, type = T_SHORT(0011), offset = 4
		member name = 'hexULX'
	list[4] = LF_MEMBER, public, type = T_SHORT(0011), offset = 6
		member name = 'hexULY'
	list[5] = LF_MEMBER, public, type = T_SHORT(0011), offset = 8
		member name = 'hexBRX'
	list[6] = LF_MEMBER, public, type = T_SHORT(0011), offset = 10
		member name = 'hexBRY'
	list[7] = LF_MEMBER, public, type = T_SHORT(0011), offset = 12
		member name = 'fullHexBRY'
	list[8] = LF_MEMBER, public, type = T_UINT4(0075), offset = 16
		member name = 'attributes'
	list[9] = LF_MEMBER, public, type = T_INT4(0074), offset = 20
		member name = 'obstacleIndex'
	list[10] = LF_MEMBER, public, type = T_CHAR(0010), offset = 24
		member name = 'armyGroup'
	list[11] = LF_MEMBER, public, type = T_CHAR(0010), offset = 25
		member name = 'armyIndex'
	list[12] = LF_MEMBER, public, type = T_CHAR(0010), offset = 26
		member name = 'partOfDouble'
	list[13] = LF_MEMBER, public, type = T_INT4(0074), offset = 28
		member name = 'iBodiesInHex'
	list[14] = LF_MEMBER, public, type = 0x442C, offset = 32
		member name = 'deadArmyGroup'
	list[15] = LF_MEMBER, public, type = 0x442C, offset = 46
		member name = 'deadArmyIndex'
	list[16] = LF_MEMBER, public, type = 0x442C, offset = 60
		member name = 'deadPartOfDouble'
	list[17] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 74
		member name = 'bValidMove'
	list[18] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 75
		member name = 'front_move'
	list[19] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 76
		member name = 'mouse_shaded'
	list[20] = LF_MEMBER, public, type = T_CHAR(0010), offset = 77
		member name = 'background_offset'
	list[21] = LF_MEMBER, public, type = 0x187D, offset = 80
		member name = 'obstacleLimitData'
	list[22] = LF_MEMBER, public, type = 0x187D, offset = 96
		member name = 'cloudLimitData'
	list[23] = LF_ONEMETHOD, public, VANILLA, index = 0x4B02, name = 'hexcell'
	list[24] = LF_ONEMETHOD, public, VANILLA, index = 0x4B05, name = 'get_army'
	list[25] = LF_ONEMETHOD, public, VANILLA, index = 0x4B08, name = 'get_dead_army'
	list[26] = LF_ONEMETHOD, public, VANILLA, index = 0x4B09, name = 'HasArmy'
	list[27] = LF_ONEMETHOD, public, VANILLA, index = 0x4B0A, name = 'limits'



	0x4bbf : Length = 186, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_MEMBER, public, type = 0x495C, offset = 0
		member name = 'sprite'
	list[1] = LF_MEMBER, public, type = 0x1F13, offset = 4
		member name = 'info'
	list[2] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 8
		member name = 'grid_index'
	list[3] = LF_MEMBER, public, type = T_CHAR(0010), offset = 9
		member name = 'owner'
	list[4] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 10
		member name = 'is_visible'
	list[5] = LF_MEMBER, public, type = T_INT4(0074), offset = 12
		member name = 'damage'
	list[6] = LF_MEMBER, public, type = T_INT4(0074), offset = 16
		member name = 'duration'
	list[7] = LF_MEMBER, public, type = 0x1F15, offset = 20
		member name = 'dispel_effect'
	list[8] = LF_ONEMETHOD, public, VANILLA, index = 0x4BC0, name = 'IsVisible'


Я думаю что это структура дефа объектов на поле боя
0x4c64 : Length = 138, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_MEMBER, public, type = 0x1BAC, offset = 0
		member name = 'type'
	list[1] = LF_MEMBER, public, type = 0x4C50, offset = 4
		member name = 'Sprite'
	list[2] = LF_MEMBER, public, type = 0x4C50, offset = 8
		member name = 'Missile'
	list[3] = LF_MEMBER, public, type = T_INT4(0074), offset = 12
		member name = 'X'
	list[4] = LF_MEMBER, public, type = T_INT4(0074), offset = 16
		member name = 'Y'
	list[5] = LF_MEMBER, public, type = T_INT4(0074), offset = 20
		member name = 'Facing'
	list[6] = LF_MEMBER, public, type = T_INT4(0074), offset = 24
		member name = 'Sequence'
	list[7] = LF_MEMBER, public, type = T_INT4(0074), offset = 28
		member name = 'Frame'


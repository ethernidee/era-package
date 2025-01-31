Заголовочник карты вроде

0x3e44 : Length = 442, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_BCLASS, public, type = 0x24EF, offset = 0
	list[1] = LF_MEMBER, public, type = 0x1329, offset = 348
		member name = 'Name'
	list[2] = LF_MEMBER, public, type = 0x1329, offset = 360
		member name = 'Description'
	list[14] = LF_METHOD, count = 2, list = 0x3E40, name = 'NewSMapHeader'

И это		

0x3559 : Length = 742, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 0
		member name = 'iCurMap'
	list[1] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 1
		member name = 'iCurrentCampaign'
	list[2] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 2
		member name = 'bIsCheater'
	list[3] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 3
		member name = 'bSecretActive'
	list[4] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 4
		member name = 'bCustomCampaign'
	list[5] = LF_MEMBER, public, type = T_INT4(0074), offset = 8
		member name = 'NumMapRegions'
	list[6] = LF_MEMBER, public, type = 0x25E8, offset = 12
		member name = 'CampaignFilename'
	list[7] = LF_MEMBER, public, type = 0x10EC, offset = 73
		member name = 'bScenarioChoosable'
	list[8] = LF_MEMBER, public, type = 0x3550, offset = 81
		member name = 'bMapChoosable'
	list[9] = LF_MEMBER, public, type = 0x3551, offset = 113
		member name = 'bMapWon'
	list[10] = LF_MEMBER, public, type = 0x3553, offset = 370
		member name = 'iCurDays'
	list[11] = LF_MEMBER, public, type = 0x3553, offset = 882
		member name = 'score'
	list[12] = LF_MEMBER, public, type = 0x10EC, offset = 1394
		member name = 'bCampaignCompleted'
	list[13] = LF_MEMBER, public, type = T_INT4(0074), offset = 1404
		member name = 'briefing_choice'
	list[14] = LF_MEMBER, public, type = 0x3554, offset = 1408
		member name = 'map_traits'
	list[15] = LF_MEMBER, public, type = 0x2DB8, offset = 10624
		member name = 'carryover_artifact'
	list[16] = LF_MEMBER, public, type = 0x3556, offset = 10632
		member name = 'carryover_pool'
	list[17] = LF_MEMBER, public, type = 0x2D13, offset = 28872
		member name = 'carryover_pool_size'
	list[18] = LF_MEMBER, public, type = 0x2D14, offset = 28874
		member name = 'assigned_carryover'
	list[19] = LF_ONEMETHOD, public, VANILLA, index = 0x355A, name = 'SCampaign'
	list[20] = LF_ONEMETHOD, public, VANILLA, index = 0x355A, name = 'clear'
	list[21] = LF_ONEMETHOD, public, VANILLA, index = 0x355C, name = 'clear_carryover_pool'
	list[22] = LF_ONEMETHOD, public, VANILLA, index = 0x355A, name = 'give_custom_items'
	list[23] = LF_ONEMETHOD, public, VANILLA, index = 0x355A, name = 'DoPreLoadCustomization'
	list[24] = LF_ONEMETHOD, public, VANILLA, index = 0x355D, name = 'CampaignComplete'
	list[25] = LF_ONEMETHOD, public, VANILLA, index = 0x355E, name = 'GetExpCap'
	list[26] = LF_ONEMETHOD, public, VANILLA, index = 0x355E, name = 'GetDifficulty'
	list[27] = LF_ONEMETHOD, public, VANILLA, index = 0x355E, name = 'get_score'
	list[28] = LF_ONEMETHOD, public, VANILLA, index = 0x355E, name = 'get_total_time'



_GameMap_

0x3451 : Length = 1946, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_METHOD, count = 2, list = 0x3452, name = 'NewfullMap'
	list[1] = LF_ONEMETHOD, public, VANILLA, index = 0x3458, name = '~NewfullMap'
	list[2] = LF_ONEMETHOD, public, VANILLA, index = 0x3459, name = 'StampObject'
	list[3] = LF_ONEMETHOD, public, VANILLA, index = 0x345A, name = 'CalculateCellExtra'
	list[4] = LF_ONEMETHOD, public, VANILLA, index = 0x345B, name = 'GenerateHeightMap'
	list[5] = LF_ONEMETHOD, public, VANILLA, index = 0x345C, name = 'GetMapSize'
	list[6] = LF_ONEMETHOD, public, VANILLA, index = 0x345E, name = 'Read'
	list[7] = LF_ONEMETHOD, public, VANILLA, index = 0x345E, name = 'Save'
	list[8] = LF_ONEMETHOD, public, VANILLA, index = 0x345E, name = 'Load'
	list[9] = LF_METHOD, count = 4, list = 0x345F, name = 'cell'
	list[10] = LF_ONEMETHOD, public, VANILLA, index = 0x3464, name = 'GetNumLevels'
	list[11] = LF_ONEMETHOD, public, VANILLA, index = 0x3465, name = 'readObjectType'
	list[12] = LF_ONEMETHOD, public, VANILLA, index = 0x3465, name = 'saveObjectType'
	list[13] = LF_ONEMETHOD, public, VANILLA, index = 0x3465, name = 'loadObjectType'
	list[14] = LF_ONEMETHOD, public, VANILLA, index = 0x3466, name = 'readObject'
	list[15] = LF_ONEMETHOD, public, VANILLA, index = 0x3466, name = 'saveObject'
	list[16] = LF_ONEMETHOD, public, VANILLA, index = 0x3466, name = 'loadObject'
	list[17] = LF_ONEMETHOD, public, VANILLA, index = 0x3467, name = 'readTreasureData'
	list[18] = LF_ONEMETHOD, public, VANILLA, index = 0x3468, name = 'readArtifactData'
	list[19] = LF_ONEMETHOD, public, VANILLA, index = 0x3468, name = 'readResourceData'
	list[20] = LF_ONEMETHOD, public, VANILLA, index = 0x3468, name = 'readHeroData'
	list[21] = LF_ONEMETHOD, public, VANILLA, index = 0x3468, name = 'readBoatData'
	list[22] = LF_ONEMETHOD, public, VANILLA, index = 0x3468, name = 'readTownData'
	list[23] = LF_ONEMETHOD, public, VANILLA, index = 0x3468, name = 'readMonsterData'
	list[24] = LF_ONEMETHOD, public, VANILLA, index = 0x3468, name = 'readSignData'
	list[25] = LF_ONEMETHOD, public, VANILLA, index = 0x3468, name = 'readMineData'
	list[26] = LF_ONEMETHOD, public, VANILLA, index = 0x3468, name = 'readAbandonedMineData'
	list[27] = LF_ONEMETHOD, public, VANILLA, index = 0x3468, name = 'readGeneratorData'
	list[28] = LF_ONEMETHOD, public, VANILLA, index = 0x3468, name = 'readEventData'
	list[29] = LF_ONEMETHOD, public, VANILLA, index = 0x3468, name = 'readBlackBoxData'
	list[30] = LF_ONEMETHOD, public, VANILLA, index = 0x3468, name = 'readSpellScrollData'
	list[31] = LF_ONEMETHOD, public, VANILLA, index = 0x3468, name = 'readHolyGrailData'
	list[32] = LF_ONEMETHOD, public, VANILLA, index = 0x3468, name = 'readScholarData'
	list[33] = LF_ONEMETHOD, public, VANILLA, index = 0x3468, name = 'readSeerData'
	list[34] = LF_ONEMETHOD, public, VANILLA, index = 0x3468, name = 'readShrineData'
	list[35] = LF_ONEMETHOD, public, VANILLA, index = 0x3468, name = 'readGarrisonData'
	list[36] = LF_ONEMETHOD, public, VANILLA, index = 0x3468, name = 'readShipyardData'
	list[37] = LF_ONEMETHOD, public, VANILLA, index = 0x3469, name = 'readBlackBox'
	list[38] = LF_ONEMETHOD, public, VANILLA, index = 0x346A, name = 'readTimedEventList'
	list[39] = LF_ONEMETHOD, public, VANILLA, index = 0x346A, name = 'saveTimedEventList'
	list[40] = LF_ONEMETHOD, public, VANILLA, index = 0x346A, name = 'loadTimedEventList'
	list[41] = LF_ONEMETHOD, public, VANILLA, index = 0x346A, name = 'saveTownEventList'
	list[42] = LF_ONEMETHOD, public, VANILLA, index = 0x346A, name = 'loadTownEventList'
	list[43] = LF_ONEMETHOD, public, VANILLA, index = 0x346A, name = 'saveBlackBoxList'
	list[44] = LF_ONEMETHOD, public, VANILLA, index = 0x346A, name = 'loadBlackBoxList'
	list[45] = LF_ONEMETHOD, public, VANILLA, index = 0x3469, name = 'saveBlackBox'
	list[46] = LF_ONEMETHOD, public, VANILLA, index = 0x3469, name = 'loadBlackBox'
	list[47] = LF_ONEMETHOD, public, VANILLA, index = 0x346A, name = 'saveTreasureList'
	list[48] = LF_ONEMETHOD, public, VANILLA, index = 0x346A, name = 'loadTreasureList'
	list[49] = LF_ONEMETHOD, public, VANILLA, index = 0x346B, name = 'saveTreasureData'
	list[50] = LF_ONEMETHOD, public, VANILLA, index = 0x346B, name = 'loadTreasureData'
	list[51] = LF_ONEMETHOD, public, VANILLA, index = 0x346A, name = 'saveMonsterList'
	list[52] = LF_ONEMETHOD, public, VANILLA, index = 0x346A, name = 'loadMonsterList'
	list[53] = LF_ONEMETHOD, public, VANILLA, index = 0x346C, name = 'saveMonsterData'
	list[54] = LF_ONEMETHOD, public, VANILLA, index = 0x346C, name = 'loadMonsterData'
	list[55] = LF_ONEMETHOD, public, VANILLA, index = 0x3464, name = 'placeObjects'
	list[56] = LF_ONEMETHOD, public, VANILLA, index = 0x346D, name = 'PlaceObject'
	list[57] = LF_MEMBER, public, type = 0x3117, offset = 0
		member name = 'ObjectTypes'
	list[58] = LF_MEMBER, public, type = 0x3184, offset = 12
		member name = 'Objects'
	list[59] = LF_MEMBER, public, type = 0x31F5, offset = 24
		member name = 'Sprites'
	list[60] = LF_MEMBER, public, type = 0x3261, offset = 36
		member name = 'CustomTreasureList'
	list[61] = LF_MEMBER, public, type = 0x32CE, offset = 48
		member name = 'CustomMonsterList'
	list[62] = LF_MEMBER, public, type = 0x333A, offset = 60
		member name = 'BlackBoxList'
	list[63] = LF_MEMBER, public, type = 0x2660, offset = 72
		member name = 'SeerHutList'
	list[64] = LF_MEMBER, public, type = 0x33B4, offset = 84
		member name = 'TimedEventList'
	list[65] = LF_MEMBER, public, type = 0x3423, offset = 96
		member name = 'TownEventList'
	list[66] = LF_METHOD, count = 2, list = 0x346E, name = 'zCell'
	list[67] = LF_ONEMETHOD, private, VANILLA, index = 0x346F, name = 'Init'
	list[68] = LF_ONEMETHOD, private, VANILLA, index = 0x3458, name = 'Close'
	list[69] = LF_ONEMETHOD, private, VANILLA, index = 0x345A, name = 'calc_cell_extra'
	list[70] = LF_ONEMETHOD, private, VANILLA, index = 0x3470, name = 'readMapLayer'
	list[71] = LF_ONEMETHOD, private, VANILLA, index = 0x3470, name = 'saveMapLayer'
	list[72] = LF_ONEMETHOD, private, VANILLA, index = 0x3470, name = 'loadMapLayer'
	list[73] = LF_ONEMETHOD, private, VANILLA, index = 0x346A, name = 'readMapObjects'
	list[74] = LF_ONEMETHOD, private, VANILLA, index = 0x346A, name = 'saveMapObjects'
	list[75] = LF_ONEMETHOD, private, VANILLA, index = 0x346A, name = 'loadMapObjects'
	list[76] = LF_MEMBER, private, type = 0x1A65, offset = 108
		member name = 'cellData'
	list[77] = LF_MEMBER, private, type = T_INT4(0074), offset = 112
		member name = 'Size'
	list[78] = LF_MEMBER, private, type = T_UCHAR(0020), offset = 116
		member name = 'HasTwoLevels'
	list[79] = LF_ONEMETHOD, public, VANILLA, (compgenx), index = 0x3471, name = 'operator='
	list[80] = LF_ONEMETHOD, public, VANILLA, (compgenx), index = 0x3473, name = '__vecDelDtor'






	0x3e34 : Length = 970, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 0
		member name = 'Type'
	list[1] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 1
		member name = 'AllowNormalVictory'
	list[2] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 2
		member name = 'AppliesToComputer'
	list[3] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 3
		member name = 'ArtifactNum'
	list[4] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 4
		member name = 'CreatureType'
	list[5] = LF_MEMBER, public, type = T_INT4(0074), offset = 8
		member name = 'NumCreatures'
	list[6] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 12
		member name = 'ResourceType'
	list[7] = LF_MEMBER, public, type = T_INT4(0074), offset = 16
		member name = 'NumResources'
	list[8] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 20
		member name = 'TownX'
	list[9] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 21
		member name = 'TownY'
	list[10] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 22
		member name = 'TownZ'
	list[11] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 23
		member name = 'HallLevel'
	list[12] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 24
		member name = 'CastleLevel'
	list[13] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 25
		member name = 'HeroX'
	list[14] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 26
		member name = 'HeroY'
	list[15] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 27
		member name = 'HeroZ'
	list[16] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 28
		member name = 'HeroID'
	list[17] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 29
		member name = 'MonsterX'
	list[18] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 30
		member name = 'MonsterY'
	list[19] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 31
		member name = 'MonsterZ'
	list[20] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 32
		member name = 'GameWon'
	list[21] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 33
		member name = 'playerWinner'
	list[22] = LF_ONEMETHOD, public, VANILLA, index = 0x3E33, name = 'VictoryConditionStruct'
	list[23] = LF_ONEMETHOD, public, VANILLA, index = 0x1AC5, name = 'applies_to_player'
	list[24] = LF_ONEMETHOD, public, VANILLA, index = 0x1AC7, name = 'CheckForArtifactWin'
	list[25] = LF_ONEMETHOD, public, VANILLA, index = 0x1AC7, name = 'CheckForTotalCreatures'
	list[26] = LF_ONEMETHOD, public, VANILLA, index = 0x1AC7, name = 'CheckForTotalResources'
	list[27] = LF_ONEMETHOD, public, VANILLA, index = 0x1AC7, name = 'CheckForUpgradedTown'
	list[28] = LF_ONEMETHOD, public, VANILLA, index = 0x1AC7, name = 'CheckForGrailBuildingWin'
	list[29] = LF_ONEMETHOD, public, VANILLA, index = 0x1AC9, name = 'CheckForHeroDefeatWin'
	list[30] = LF_ONEMETHOD, public, VANILLA, index = 0x1AC7, name = 'IsTargetHeroDead'
	list[31] = LF_ONEMETHOD, public, VANILLA, index = 0x1ACC, name = 'IsTownCaptureTarget'
	list[32] = LF_ONEMETHOD, public, VANILLA, index = 0x1AC7, name = 'CheckForTownCaptureWin'
	list[33] = LF_ONEMETHOD, public, VANILLA, index = 0x1ACE, name = 'CheckForDefeatedMonsterWin'
	list[34] = LF_ONEMETHOD, public, VANILLA, index = 0x1AC7, name = 'CheckForFlaggedGeneratorWin'
	list[35] = LF_ONEMETHOD, public, VANILLA, index = 0x1AC7, name = 'CheckForFlaggedMineWin'
	list[36] = LF_ONEMETHOD, public, VANILLA, index = 0x1ACE, name = 'CheckForArtifactTransportWin'
	list[37] = LF_ONEMETHOD, public, VANILLA, index = 0x1ACC, name = 'IsGrailTarget'



	Условия поражения

	0x3e48 : Length = 334, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 0
		member name = 'Type'
	list[1] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 1
		member name = 'TownX'
	list[2] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 2
		member name = 'TownY'
	list[3] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 3
		member name = 'TownZ'
	list[4] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 4
		member name = 'HeroX'
	list[5] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 5
		member name = 'HeroY'
	list[6] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 6
		member name = 'HeroZ'
	list[7] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 7
		member name = 'HeroID'
	list[8] = LF_MEMBER, public, type = T_SHORT(0011), offset = 8
		member name = 'NumDays'
	list[9] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 10
		member name = 'GameLost'
	list[10] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 11
		member name = 'playerLoser'
	list[11] = LF_ONEMETHOD, public, VANILLA, index = 0x3E47, name = 'LossConditionStruct'
	list[12] = LF_ONEMETHOD, public, VANILLA, index = 0x1AD1, name = 'CheckForDefeatedHeroLoss'
	list[13] = LF_ONEMETHOD, public, VANILLA, index = 0x1AD3, name = 'CheckForDefeatedTownLoss'
	list[14] = LF_ONEMETHOD, public, VANILLA, index = 0x1AD4, name = 'CheckForTimeLimitExpired'



	Непосредственно сам менеджер

	0x3edc : Length = 7086, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_NESTTYPE, type = 0x3E4A, __unnamed
	list[1] = LF_ONEMETHOD, public, STATIC, index = 0x3E4B, name = 'saveString'
	list[2] = LF_ONEMETHOD, public, STATIC, index = 0x3E4B, name = 'loadString'
	list[3] = LF_MEMBER, public, type = 0x101D, offset = 0
		member name = 'newGameWin'
	list[4] = LF_MEMBER, public, type = 0x1CED, offset = 4
		member name = 'spellAllocInfo'
	list[5] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 74
		member name = 'bGrailAsked'
	list[6] = LF_MEMBER, public, type = 0x3C8C, offset = 76
		member name = 'townExtraPool'
	list[7] = LF_MEMBER, public, type = 0x3E4C, offset = 88
		member name = 'heroExtraPool'
	list[8] = LF_MEMBER, public, type = T_SHORT(0011), offset = 24664
		member name = 'difficultyRating'
	list[9] = LF_MEMBER, public, type = 0x3558, offset = 24668
		member name = 'sCampaign'
	list[10] = LF_MEMBER, public, type = T_CHAR(0010), offset = (LF_USHORT) 53552
		member name = 'bNewCampaignStarted'
	list[11] = LF_MEMBER, public, type = 0x2456, offset = (LF_USHORT) 53553
		member name = 'cGameFilename'
	list[12] = LF_MEMBER, public, type = T_CHAR(0010), offset = (LF_USHORT) 53904
		member name = 'numPlayers'
	list[13] = LF_MEMBER, public, type = T_CHAR(0010), offset = (LF_USHORT) 53905
		member name = 'numDeadPlayers'
	list[14] = LF_MEMBER, public, type = 0x1CBA, offset = (LF_USHORT) 53906
		member name = 'playerDead'
	list[15] = LF_MEMBER, public, type = T_USHORT(0021), offset = (LF_USHORT) 53914
		member name = 'day'
	list[16] = LF_MEMBER, public, type = T_USHORT(0021), offset = (LF_USHORT) 53916
		member name = 'week'
	list[17] = LF_MEMBER, public, type = T_USHORT(0021), offset = (LF_USHORT) 53918
		member name = 'month'
	list[18] = LF_MEMBER, public, type = 0x3E4D, offset = (LF_USHORT) 53920
		member name = 'cUniqueSystemID'
	list[19] = LF_MEMBER, public, type = 0x3A40, offset = (LF_USHORT) 53952
		member name = 'marketArtifacts'
	list[20] = LF_NESTTYPE, type = 0x3A89, BlackMarketList
	list[21] = LF_MEMBER, public, type = 0x3A89, offset = (LF_USHORT) 53980
		member name = 'BlackMarkets'
	list[22] = LF_MEMBER, public, type = T_SHORT(0011), offset = (LF_USHORT) 53992
		member name = 'ultimateX'
	list[23] = LF_MEMBER, public, type = T_SHORT(0011), offset = (LF_USHORT) 53994
		member name = 'ultimateY'
	list[24] = LF_MEMBER, public, type = T_UCHAR(0020), offset = (LF_USHORT) 53996
		member name = 'ultimateZ'
	list[25] = LF_MEMBER, public, type = T_UCHAR(0020), offset = (LF_USHORT) 53997
		member name = 'ultimateRadius'
	list[26] = LF_MEMBER, public, type = T_UCHAR(0020), offset = (LF_USHORT) 53998
		member name = 'ultimateValid'
	list[27] = LF_MEMBER, public, type = T_CHAR(0010), offset = (LF_USHORT) 53999
		member name = 'iGameType'
	list[28] = LF_MEMBER, public, type = T_CHAR(0010), offset = (LF_USHORT) 54000
		member name = 'bIsCheater'
	list[29] = LF_MEMBER, public, type = T_UCHAR(0020), offset = (LF_USHORT) 54001
		member name = 'is_tutorial'
	list[30] = LF_MEMBER, public, type = 0x24F1, offset = (LF_USHORT) 54002
		member name = 'sSetup'
	list[31] = LF_MEMBER, public, type = 0x2459, offset = (LF_USHORT) 54440
		member name = 'sMapHeader'
	list[32] = LF_MEMBER, public, type = 0x1AC2, offset = (LF_USHORT) 54812
		member name = 'VictoryCondition'
	list[33] = LF_MEMBER, public, type = 0x1ACF, offset = (LF_USHORT) 54848
		member name = 'LossCondition'
	list[34] = LF_MEMBER, public, type = 0x3450, offset = (LF_USHORT) 54860
		member name = 'worldMap'
	list[35] = LF_MEMBER, public, type = 0x3E4E, offset = (LF_USHORT) 54984
		member name = 'player'
	list[36] = LF_MEMBER, public, type = 0x35C7, offset = (LF_USHORT) 57736
		member name = 'tavern_heroes'
	list[37] = LF_MEMBER, public, type = 0x3799, offset = (LF_USHORT) 57744
		member name = 'townPool'
	list[38] = LF_MEMBER, public, type = 0x3E4F, offset = (LF_USHORT) 57756
		member name = 'heroPool'
	list[39] = LF_MEMBER, public, type = 0x3E50, offset = (LF_ULONG) 203676
		member name = 'heroAllocInfo'
	list[40] = LF_MEMBER, public, type = 0x3E51, offset = (LF_ULONG) 203804
		member name = 'artifactAllocInfo'
	list[41] = LF_MEMBER, public, type = 0x3E51, offset = (LF_ULONG) 203931
		member name = 'reservedArtifactInfo'
	list[42] = LF_MEMBER, private, type = 0x3550, offset = (LF_ULONG) 204058
		member name = 'InfoFlags'
	list[43] = LF_MEMBER, public, type = 0x10EC, offset = (LF_ULONG) 204090
		member name = 'GuardFlags'
	list[44] = LF_MEMBER, public, type = 0x3E52, offset = (LF_ULONG) 204098
		member name = 'cartographerMask'
	list[45] = LF_MEMBER, public, type = 0x3E53, offset = (LF_ULONG) 204104
		member name = 'cartographerFlags'
	list[46] = LF_MEMBER, public, type = 0x3B84, offset = (LF_ULONG) 204108
		member name = 'signPool'
	list[47] = LF_MEMBER, public, type = 0x385D, offset = (LF_ULONG) 204120
		member name = 'minePool'
	list[48] = LF_MEMBER, public, type = 0x3A14, offset = (LF_ULONG) 204132
		member name = 'generatorPool'
	list[49] = LF_MEMBER, public, type = 0x3CD8, offset = (LF_ULONG) 204144
		member name = 'garrisonPool'
	list[50] = LF_MEMBER, public, type = 0x3646, offset = (LF_ULONG) 204156
		member name = 'boatPool'
	list[51] = LF_MEMBER, public, type = 0x3B07, offset = (LF_ULONG) 204168
		member name = 'university_pool'
	list[52] = LF_MEMBER, public, type = 0x372D, offset = (LF_ULONG) 204180
		member name = 'creature_banks'
	list[53] = LF_MEMBER, public, type = T_RCHAR(0070), offset = (LF_ULONG) 204192
		member name = 'numObelisks'
	list[54] = LF_MEMBER, public, type = 0x2D15, offset = (LF_ULONG) 204193
		member name = 'obeliskPool'
	list[55] = LF_MEMBER, public, type = 0x3E54, offset = (LF_ULONG) 204241
		member name = 'cCurRumour'
	list[56] = LF_MEMBER, public, type = 0x3E55, offset = (LF_ULONG) 204542
		member name = 'rumourAllocInfo'
	list[57] = LF_NESTTYPE, type = 0x3961, TRumour
	list[58] = LF_NESTTYPE, type = 0x39AE, TRumourList
	list[59] = LF_MEMBER, public, type = 0x39AE, offset = (LF_ULONG) 204800
		member name = 'MapRumours'
	list[60] = LF_ONEMETHOD, public, VANILLA, index = 0x3E57, name = 'LoadGame'
	list[61] = LF_ONEMETHOD, public, VANILLA, index = 0x3E59, name = 'SaveGame'
	list[62] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5A, name = 'GetSaveGameHeaders'
	list[63] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5A, name = 'Load'
	list[64] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5A, name = 'Save'
	list[65] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5A, name = 'LoadRumours'
	list[66] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5A, name = 'SaveRumours'
	list[67] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5A, name = 'LoadBlackMarkets'
	list[68] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5A, name = 'SaveBlackMarkets'
	list[69] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5A, name = 'LoadSignPool'
	list[70] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5A, name = 'SaveSignPool'
	list[71] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5A, name = 'LoadMinePool'
	list[72] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5A, name = 'SaveMinePool'
	list[73] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5A, name = 'LoadGarrisonPool'
	list[74] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5A, name = 'SaveGarrisonPool'
	list[75] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5A, name = 'LoadBoatPool'
	list[76] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5A, name = 'SaveBoatPool'
	list[77] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5A, name = 'LoadObeliskPool'
	list[78] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5A, name = 'SaveObeliskPool'
	list[79] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5A, name = 'LoadPlayerData'
	list[80] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5A, name = 'SavePlayerData'
	list[81] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5A, name = 'LoadTownPool'
	list[82] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5A, name = 'SaveTownPool'
	list[83] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5A, name = 'LoadHeroPool'
	list[84] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5A, name = 'SaveHeroPool'
	list[85] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5B, name = 'SetCannedRumour'
	list[86] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5B, name = 'SetMapRumour'
	list[87] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5B, name = 'SetSpecialRumour'
	list[88] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5B, name = 'setup_shipyards'
	list[89] = LF_METHOD, count = 2, list = 0x3E5F, name = 'game'
	list[90] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = '~game'
	list[91] = LF_ONEMETHOD, public, VANILLA, index = 0x3E60, name = 'ValidateVictoryLossConditions'
	list[92] = LF_ONEMETHOD, public, VANILLA, index = 0x3E61, name = 'OnSameTeam'
	list[93] = LF_ONEMETHOD, public, VANILLA, index = 0x1CE1, name = 'IsLocalHumanTeam'
	list[94] = LF_ONEMETHOD, public, VANILLA, index = 0x1CE1, name = 'IsLivingTeam'
	list[95] = LF_ONEMETHOD, public, VANILLA, index = 0x1CE1, name = 'IsHumanTeam'
	list[96] = LF_ONEMETHOD, public, VANILLA, index = 0x1CE1, name = 'is_human_ally'
	list[97] = LF_ONEMETHOD, public, VANILLA, index = 0x1CE1, name = 'IsComputerTeam'
	list[98] = LF_ONEMETHOD, public, VANILLA, index = 0x3E62, name = 'GetTeam'
	list[99] = LF_ONEMETHOD, public, VANILLA, index = 0x1CE1, name = 'GetTeamMask'
	list[100] = LF_ONEMETHOD, public, VANILLA, index = 0x1CE1, name = 'GetNumAllies'
	list[101] = LF_ONEMETHOD, public, VANILLA, index = 0x3E65, name = 'SetInfoFlag'
	list[102] = LF_ONEMETHOD, public, VANILLA, index = 0x3E66, name = 'GetInfoFlag'
	list[103] = LF_MEMBER, public, type = 0x101D, offset = (LF_ULONG) 204812
		member name = 'armyWindow'
	list[104] = LF_MEMBER, public, type = T_INT4(0074), offset = (LF_ULONG) 204816
		member name = 'viewFrame'
	list[105] = LF_ONEMETHOD, public, VANILLA, index = 0x3E68, name = 'ViewArmy'
	list[106] = LF_ONEMETHOD, public, VANILLA, index = 0x3E69, name = 'GetWorldMapData'
	list[107] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'Overview'
	list[108] = LF_ONEMETHOD, public, VANILLA, index = 0x3E6A, name = 'get_alignment'
	list[109] = LF_ONEMETHOD, public, VANILLA, index = 0x3E6B, name = 'get_puzzle_origin'
	list[110] = LF_METHOD, count = 2, list = 0x3E6E, name = 'GetHero'
	list[111] = LF_ONEMETHOD, public, VANILLA, index = 0x3E6F, name = 'GetHeroId'
	list[112] = LF_ONEMETHOD, public, VANILLA, index = 0x3E70, name = 'GetCurrHero'
	list[113] = LF_ONEMETHOD, public, VANILLA, index = 0x3E71, name = 'GetCurrHeroId'
	list[114] = LF_ONEMETHOD, public, VANILLA, index = 0x3E73, name = 'GetStartingHeroId'
	list[115] = LF_ONEMETHOD, public, VANILLA, index = 0x3E75, name = 'GetNewHeroId'
	list[116] = LF_ONEMETHOD, public, VANILLA, index = 0x3E77, name = 'HeroIDToHeroPos'
	list[117] = LF_ONEMETHOD, public, VANILLA, index = 0x3E77, name = 'TownIDToTownPos'
	list[118] = LF_ONEMETHOD, public, VANILLA, index = 0x3E79, name = 'Scan'
	list[119] = LF_ONEMETHOD, public, VANILLA, index = 0x3E7B, name = 'RandomScan'
	list[120] = LF_ONEMETHOD, public, VANILLA, index = 0x3E7C, name = 'GetHeroBoat'
	list[121] = LF_ONEMETHOD, public, VANILLA, index = 0x3E7D, name = 'ClaimShipyard'
	list[122] = LF_METHOD, count = 2, list = 0x3E7F, name = 'GetTown'
	list[123] = LF_ONEMETHOD, public, VANILLA, index = 0x3E80, name = 'GetCurrTown'
	list[124] = LF_ONEMETHOD, public, VANILLA, index = 0x3E71, name = 'GetCurrTownId'
	list[125] = LF_ONEMETHOD, public, VANILLA, index = 0x3E81, name = 'GetTownId'
	list[126] = LF_ONEMETHOD, public, VANILLA, index = 0x1CE1, name = 'TownAlreadyBuiltOn'
	list[127] = LF_ONEMETHOD, public, VANILLA, index = 0x1CE3, name = 'GetTownName'
	list[128] = LF_ONEMETHOD, public, VANILLA, index = 0x3E82, name = 'ClaimTown'
	list[129] = LF_ONEMETHOD, public, VANILLA, index = 0x3E83, name = 'GetMine'
	list[130] = LF_ONEMETHOD, public, VANILLA, index = 0x3E81, name = 'GetMineId'
	list[131] = LF_ONEMETHOD, public, VANILLA, index = 0x3E85, name = 'ClaimMine'
	list[132] = LF_ONEMETHOD, public, VANILLA, index = 0x3E86, name = 'MineTypesOwned'
	list[133] = LF_ONEMETHOD, public, VANILLA, index = 0x3E87, name = 'GetGenerator'
	list[134] = LF_ONEMETHOD, public, VANILLA, index = 0x3E81, name = 'GetGeneratorId'
	list[135] = LF_ONEMETHOD, public, VANILLA, index = 0x3E88, name = 'ClaimGenerator'
	list[136] = LF_ONEMETHOD, public, VANILLA, index = 0x3E89, name = 'GetGarrison'
	list[137] = LF_ONEMETHOD, public, VANILLA, index = 0x3E81, name = 'GetGarrisonId'
	list[138] = LF_ONEMETHOD, public, VANILLA, index = 0x3E88, name = 'ClaimGarrison'
	list[139] = LF_ONEMETHOD, public, VANILLA, index = 0x3E71, name = 'GetBoatsBuilt'
	list[140] = LF_ONEMETHOD, public, VANILLA, index = 0x3E71, name = 'get_new_boat_id'
	list[141] = LF_ONEMETHOD, public, VANILLA, index = 0x3E8B, name = 'CreateBoat'
	list[142] = LF_ONEMETHOD, public, VANILLA, index = 0x3E8C, name = 'GetBoat'
	list[143] = LF_METHOD, count = 2, list = 0x3E8E, name = 'clear_event_records'
	list[144] = LF_ONEMETHOD, public, VANILLA, index = 0x26E5, name = 'get_liths'
	list[145] = LF_ONEMETHOD, public, VANILLA, index = 0x26E5, name = 'get_lith_exits'
	list[146] = LF_ONEMETHOD, public, VANILLA, index = 0x26E6, name = 'get_whirlpools'
	list[147] = LF_ONEMETHOD, public, VANILLA, index = 0x3E90, name = 'get_underground_gate_exit'
	list[148] = LF_ONEMETHOD, public, VANILLA, index = 0x3E92, name = 'get_random_lith_exit'
	list[149] = LF_METHOD, count = 2, list = 0x3E97, name = 'get_random_lith'
	list[150] = LF_ONEMETHOD, public, VANILLA, index = 0x3E92, name = 'get_random_whirlpool'
	list[151] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'play_recorded_events'
	list[152] = LF_ONEMETHOD, public, VANILLA, index = 0x3E98, name = 'record_claim_mine'
	list[153] = LF_ONEMETHOD, public, VANILLA, index = 0x3E98, name = 'record_claim_town'
	list[154] = LF_ONEMETHOD, public, VANILLA, index = 0x3E99, name = 'record_erase_object'
	list[155] = LF_ONEMETHOD, public, VANILLA, index = 0x3E9A, name = 'record_hide_boat'
	list[156] = LF_ONEMETHOD, public, VANILLA, index = 0x3E9C, name = 'record_hide_hero'
	list[157] = LF_ONEMETHOD, public, VANILLA, index = 0x3E9E, name = 'record_move'
	list[158] = LF_ONEMETHOD, public, VANILLA, index = 0x3E8D, name = 'record_player_death'
	list[159] = LF_ONEMETHOD, public, VANILLA, index = 0x3EA0, name = 'record_show_boat'
	list[160] = LF_ONEMETHOD, public, VANILLA, index = 0x3EA2, name = 'record_show_hero'
	list[161] = LF_ONEMETHOD, public, VANILLA, index = 0x3EA4, name = 'record_teleport'
	list[162] = LF_ONEMETHOD, public, VANILLA, index = 0x3EA5, name = 'replay_available'
	list[163] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'NextPlayer'
	list[164] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'calculate_production'
	list[165] = LF_ONEMETHOD, public, VANILLA, index = 0x3EA6, name = 'get_base_map_score'
	list[166] = LF_ONEMETHOD, public, VANILLA, index = 0x3EA6, name = 'get_current_turn'
	list[167] = LF_ONEMETHOD, public, VANILLA, index = 0x3EA6, name = 'get_map_score'
	list[168] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'mark_campaign_map_won'
	list[169] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'PerDay'
	list[170] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'PerWeek'
	list[171] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'PerMonth'
	list[172] = LF_ONEMETHOD, public, VANILLA, index = 0x3EA9, name = 'replace_recruit'
	list[173] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'set_recruits'
	list[174] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'UpdateNewGameWindow'
	list[175] = LF_ONEMETHOD, public, VANILLA, index = 0x3EAA, name = 'LoadMap'
	list[176] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'RandomizeHeroPool'
	list[177] = LF_ONEMETHOD, public, VANILLA, index = 0x3EAB, name = 'SetRandomHeroArmies'
	list[178] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'ProcessRandomObjects'
	list[179] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'ProcessRandomTowns'
	list[180] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'CreateTownHeroes'
	list[181] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'RandomizeHolyGrail'
	list[182] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'RandomizeEvents'
	list[183] = LF_ONEMETHOD, public, VANILLA, index = 0x3E88, name = 'RandomizeMine'
	list[184] = LF_ONEMETHOD, public, VANILLA, index = 0x3EAC, name = 'GetRandomNumTroops'
	list[185] = LF_ONEMETHOD, public, VANILLA, index = 0x3EAD, name = 'GetRandomArtifactId'
	list[186] = LF_ONEMETHOD, public, VANILLA, index = 0x3EAE, name = 'GetRandomMonster'
	list[187] = LF_ONEMETHOD, public, VANILLA, index = 0x3E86, name = 'SetupPuzzlePieces'
	list[188] = LF_ONEMETHOD, public, VANILLA, index = 0x3EAF, name = 'SetVisibility'
	list[189] = LF_ONEMETHOD, public, VANILLA, index = 0x3EB0, name = 'ResetVisibility'
	list[190] = LF_ONEMETHOD, public, VANILLA, index = 0x3EB1, name = 'GrowCoverOfDarkness'
	list[191] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'ResetAllPlayerVisibility'
	list[192] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'TurnOnAIMusic'
	list[193] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'TurnOffAIMusic'
	list[194] = LF_ONEMETHOD, public, VANILLA, index = 0x3EB2, name = 'GiveTroopsToNeutralTown'
	list[195] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'GiveTroopsToNeutralTowns'
	list[196] = LF_ONEMETHOD, public, VANILLA, index = 0x3EB4, name = 'GiveArmy'
	list[197] = LF_ONEMETHOD, public, VANILLA, index = 0x3EB6, name = 'ExperienceValueOfStack'
	list[198] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'SetupAdjacentMons'
	list[199] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'ShowComputerScreen'
	list[200] = LF_ONEMETHOD, public, VANILLA, index = 0x3EB7, name = 'WaitForPlayer'
	list[201] = LF_ONEMETHOD, public, VANILLA, index = 0x3EB8, name = 'ShowLuckInfo'
	list[202] = LF_ONEMETHOD, public, VANILLA, index = 0x3EB8, name = 'ShowMoraleInfo'
	list[203] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'ProcessMapExtra'
	list[204] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'SetupTowns'
	list[205] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'ProcessOnMapTowns'
	list[206] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'ProcessOnMapHeroes'
	list[207] = LF_ONEMETHOD, public, VANILLA, index = 0x3EB9, name = 'ComputeDailyGold'
	list[208] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'CheckHeroConsistency'
	list[209] = LF_ONEMETHOD, public, VANILLA, index = 0x3EBA, name = 'TransmitSaveGame'
	list[210] = LF_ONEMETHOD, public, VANILLA, index = 0x3EBB, name = 'ReceiveSaveGame'
	list[211] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'CancelComputerScreen'
	list[212] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'DoNewTurn'
	list[213] = LF_ONEMETHOD, public, VANILLA, index = 0x3E71, name = 'SetupCampaignGame'
	list[214] = LF_ONEMETHOD, public, VANILLA, index = 0x3E71, name = 'SetupHotSeatGame'
	list[215] = LF_ONEMETHOD, public, VANILLA, index = 0x3E71, name = 'SetupNetworkGame'
	list[216] = LF_ONEMETHOD, public, VANILLA, index = 0x3E71, name = 'SetupModemGame'
	list[217] = LF_ONEMETHOD, public, VANILLA, index = 0x3E71, name = 'SetupMultiPlayerGame'
	list[218] = LF_ONEMETHOD, public, VANILLA, index = 0x3E71, name = 'SetupNetworkGame2'
	list[219] = LF_ONEMETHOD, public, VANILLA, index = 0x3EAC, name = 'GetNumThievesGuilds'
	list[220] = LF_ONEMETHOD, public, VANILLA, index = 0x3E71, name = 'CalcDifficultyRating'
	list[221] = LF_ONEMETHOD, public, VANILLA, index = 0x3E71, name = 'GetNumMapLevels'
	list[222] = LF_ONEMETHOD, public, VANILLA, index = 0x3EBD, name = 'NewMap'
	list[223] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'ShowScenInfo'
	list[224] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'ShowHeroesLogo'
	list[225] = LF_ONEMETHOD, public, VANILLA, index = 0x3E88, name = 'SetMapSize'
	list[226] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'SetupOrigData'
	list[227] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'SetupNewRumour'
	list[228] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'CheckForTimeEvent'
	list[229] = LF_ONEMETHOD, public, VANILLA, index = 0x3EBE, name = 'GiveTimeEventReward'
	list[230] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'CheckForTownEvent'
	list[231] = LF_ONEMETHOD, public, VANILLA, index = 0x3EBF, name = 'GiveTownEventReward'
	list[232] = LF_ONEMETHOD, public, VANILLA, index = 0x3EC1, name = 'MakeTerrainVisible'
	list[233] = LF_ONEMETHOD, public, VANILLA, index = 0x3EC2, name = 'InitNewGame'
	list[234] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'GetMap'
	list[235] = LF_METHOD, count = 2, list = 0x3EC5, name = 'get_cell'
	list[236] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'CleanUpNewGameWindow'
	list[237] = LF_ONEMETHOD, public, VANILLA, index = 0x3EC6, name = 'ConvertObject'
	list[238] = LF_ONEMETHOD, public, VANILLA, index = 0x3EC7, name = 'InsertObject'
	list[239] = LF_ONEMETHOD, public, VANILLA, index = 0x3EC2, name = 'ProcessNewMap'
	list[240] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'InitNewGameWindow'
	list[241] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'SetupNetPlayerNames'
	list[242] = LF_ONEMETHOD, public, VANILLA, index = 0x3EB2, name = 'DrawNGKPDisplayString'
	list[243] = LF_ONEMETHOD, public, VANILLA, index = 0x3EC8, name = 'NGKPSetupDisplayString'
	list[244] = LF_ONEMETHOD, public, VANILLA, index = 0x3EC9, name = 'ProcessNGKeyPress'
	list[245] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'InitRandomArtifacts'
	list[246] = LF_ONEMETHOD, public, VANILLA, index = 0x3E88, name = 'SetupDynamicStuff'
	list[247] = LF_ONEMETHOD, public, VANILLA, index = 0x3ECA, name = 'SetupNewOverviewType'
	list[248] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'DoKnob'
	list[249] = LF_ONEMETHOD, public, VANILLA, index = 0x3EB9, name = 'ProcessIconSelect'
	list[250] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'SetupResources'
	list[251] = LF_ONEMETHOD, public, VANILLA, index = 0x3ECB, name = 'GetLossConditionText'
	list[252] = LF_ONEMETHOD, public, VANILLA, index = 0x3ECB, name = 'GetVictoryConditionText'
	list[253] = LF_ONEMETHOD, public, VANILLA, index = 0x3ECD, name = 'GetSideDesc'
	list[254] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'SetMarketArtifacts'
	list[255] = LF_ONEMETHOD, public, VANILLA, index = 0x1CE1, name = 'IsHuman'
	list[256] = LF_ONEMETHOD, public, VANILLA, index = 0x1CE1, name = 'IsLocalHuman'
	list[257] = LF_ONEMETHOD, public, VANILLA, index = 0x3ECE, name = 'GetPlayerName'
	list[258] = LF_ONEMETHOD, public, VANILLA, index = 0x3ECF, name = 'GetLocalPlayer'
	list[259] = LF_ONEMETHOD, public, VANILLA, index = 0x3ED0, name = 'GetLocalPlayerGamePos'
	list[260] = LF_ONEMETHOD, public, VANILLA, index = 0x3ED1, name = 'GetGamePosFromDPID'
	list[261] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'SetSummoningGenerators'
	list[262] = LF_ONEMETHOD, public, VANILLA, index = 0x3ED0, name = 'GetLastHuman'
	list[263] = LF_ONEMETHOD, public, VANILLA, index = 0x1CE1, name = 'IsLastHuman'
	list[264] = LF_ONEMETHOD, public, VANILLA, index = 0x3EA5, name = 'IsMultiplayer'
	list[265] = LF_ONEMETHOD, public, VANILLA, index = 0x3E5B, name = 'ResetGame'
	list[266] = LF_ONEMETHOD, public, VANILLA, index = 0x3ED2, name = 'GetRandomSpell'
	list[267] = LF_ONEMETHOD, private, VANILLA, index = 0x3ED4, name = 'clear_recruits'
	list[268] = LF_ONEMETHOD, private, VANILLA, index = 0x3ED5, name = 'load_recorded_events'
	list[269] = LF_ONEMETHOD, private, VANILLA, index = 0x3ED5, name = 'save_recorded_events'
	list[270] = LF_ONEMETHOD, private, VANILLA, index = 0x3ED7, name = 'set_weekly_recruits'
	list[271] = LF_ONEMETHOD, private, VANILLA, index = 0x3E5B, name = 'match_underground_gates'
	list[272] = LF_ONEMETHOD, private, VANILLA, index = 0x3EC6, name = 'randomize_university'
	list[273] = LF_MEMBER, private, type = 0x3ED8, offset = (LF_ULONG) 204820
		member name = 'two_way_liths'
	list[274] = LF_MEMBER, private, type = 0x3ED8, offset = (LF_ULONG) 204856
		member name = 'lith_exits'
	list[275] = LF_MEMBER, private, type = 0x2682, offset = (LF_ULONG) 204892
		member name = 'whirlpools'
	list[276] = LF_MEMBER, private, type = 0x2682, offset = (LF_ULONG) 204904
		member name = 'underground_gates'
	list[277] = LF_MEMBER, private, type = 0x1F72, offset = (LF_ULONG) 204916
		member name = 'underground_gate_exits'
	list[278] = LF_MEMBER, private, type = 0x36C0, offset = (LF_ULONG) 204928
		member name = 'recorded_events'
	list[279] = LF_ONEMETHOD, public, VANILLA, (compgenx), index = 0x3EDA, name = 'operator='
	list[280] = LF_ONEMETHOD, public, VANILLA, (compgenx), index = 0x3EDB, name = '__vecDelDtor'


Опции

	0x3ee6 : Length = 894, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_MEMBER, public, type = 0x3EE3, offset = 0
		member name = 'walkSpeed'
	list[1] = LF_MEMBER, public, type = T_INT4(0074), offset = 8
		member name = 'musicOn'
	list[2] = LF_MEMBER, public, type = T_INT4(0074), offset = 12
		member name = 'soundOn'
	list[3] = LF_MEMBER, public, type = T_INT4(0074), offset = 16
		member name = 'lastMusicVolume'
	list[4] = LF_MEMBER, public, type = T_INT4(0074), offset = 20
		member name = 'lastSoundVolume'
	list[5] = LF_MEMBER, public, type = T_INT4(0074), offset = 24
		member name = 'AutoSave'
	list[6] = LF_MEMBER, public, type = T_INT4(0074), offset = 28
		member name = 'ShowRoute'
	list[7] = LF_MEMBER, public, type = T_INT4(0074), offset = 32
		member name = 'MoveReminder'
	list[8] = LF_MEMBER, public, type = T_INT4(0074), offset = 36
		member name = 'QuickCombat'
	list[9] = LF_MEMBER, public, type = T_INT4(0074), offset = 40
		member name = 'VideoSubtitles'
	list[10] = LF_MEMBER, public, type = T_INT4(0074), offset = 44
		member name = 'TownOutlines'
	list[11] = LF_MEMBER, public, type = T_INT4(0074), offset = 48
		member name = 'AnimateSpellBook'
	list[12] = LF_MEMBER, public, type = T_INT4(0074), offset = 52
		member name = 'WindowScrollSpeed'
	list[13] = LF_MEMBER, public, type = T_INT4(0074), offset = 56
		member name = 'BlackoutComputer'
	list[14] = LF_MEMBER, public, type = T_INT4(0074), offset = 60
		member name = 'AutoCreatures'
	list[15] = LF_MEMBER, public, type = T_INT4(0074), offset = 64
		member name = 'AutoSpells'
	list[16] = LF_MEMBER, public, type = T_INT4(0074), offset = 68
		member name = 'AutoCatapult'
	list[17] = LF_MEMBER, public, type = T_INT4(0074), offset = 72
		member name = 'AutoBallista'
	list[18] = LF_MEMBER, public, type = T_INT4(0074), offset = 76
		member name = 'AutoFirstAidTent'
	list[19] = LF_MEMBER, public, type = T_INT4(0074), offset = 80
		member name = 'PreferBink'
	list[20] = LF_MEMBER, public, type = 0x3EE5, offset = 84
		member name = 'wc'
	list[21] = LF_MEMBER, public, type = T_INT4(0074), offset = 100
		member name = 'bCombatShowEntireGrid'
	list[22] = LF_MEMBER, public, type = T_INT4(0074), offset = 104
		member name = 'bCombatShowMouseHex'
	list[23] = LF_MEMBER, public, type = T_INT4(0074), offset = 108
		member name = 'iCombatGridLevel'
	list[24] = LF_MEMBER, public, type = T_INT4(0074), offset = 112
		member name = 'iCombatViewArmy'
	list[25] = LF_MEMBER, public, type = 0x184E, offset = 116
		member name = 'cDOSDigitalDriver'
	list[26] = LF_MEMBER, public, type = 0x184E, offset = 129
		member name = 'cDOSMIDIDriver'
	list[27] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 142
		member name = 'bDontTryRedbook'
	list[28] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 143
		member name = 'bFirstInstall'
	list[29] = LF_MEMBER, public, type = 0x25B1, offset = 144
		member name = 'cUniqueSystemID'
	list[30] = LF_MEMBER, public, type = T_INT4(0074), offset = 148
		member name = 'iCombatSpeed'
	list[31] = LF_MEMBER, public, type = 0x184E, offset = 152
		member name = 'cCurRemoteReceive'
	list[32] = LF_MEMBER, public, type = 0x184E, offset = 165
		member name = 'cRemoteReceiveDiff'
	list[33] = LF_MEMBER, public, type = 0x184E, offset = 178
		member name = 'cCurRemoteSend'
	list[34] = LF_MEMBER, public, type = 0x1A39, offset = 191
		member name = 'cNetName'


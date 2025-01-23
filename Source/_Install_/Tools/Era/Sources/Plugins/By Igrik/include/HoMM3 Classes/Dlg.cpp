0x3ddc : Length = 994, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_NESTTYPE, type = 0x2CDF, CChatStr
	list[1] = LF_ONEMETHOD, public, VANILLA, index = 0x2BDA, name = 'CChatManager'
	list[2] = LF_ONEMETHOD, public, VANILLA, index = 0x2BDB, name = '~CChatManager'
	list[3] = LF_ONEMETHOD, public, VANILLA, index = 0x2BDB, name = 'Init'
	list[4] = LF_ONEMETHOD, public, VANILLA, index = 0x2BDB, name = 'ShutDown'
	list[5] = LF_ONEMETHOD, public, VANILLA, index = 0x2BDD, name = 'AddChat'
	list[6] = LF_ONEMETHOD, public, VANILLA, index = 0x2BDD, name = 'SystemMsg'
	list[7] = LF_ONEMETHOD, public, VANILLA, index = 0x2BDD, name = 'TurnDurationMsg'
	list[8] = LF_ONEMETHOD, public, VANILLA, index = 0x2BDD, name = 'PlayerDropMsg'
	list[9] = LF_ONEMETHOD, public, VANILLA, index = 0x2BDD, name = 'PlayerEnterMsg'
	list[10] = LF_ONEMETHOD, public, VANILLA, index = 0x2BDF, name = 'UpdateWidget'
	list[11] = LF_ONEMETHOD, public, VANILLA, index = 0x2BDB, name = 'PauseTimeOuts'
	list[12] = LF_ONEMETHOD, public, VANILLA, index = 0x2BDB, name = 'ResumeTimeOuts'
	list[13] = LF_ONEMETHOD, public, VANILLA, index = 0x2BE1, name = 'HasChat'
	list[14] = LF_ONEMETHOD, public, VANILLA, index = 0x2BDB, name = 'ClearChat'
	list[15] = LF_ONEMETHOD, public, VANILLA, index = 0x25CD, name = 'GetCount'
	list[16] = LF_ONEMETHOD, public, VANILLA, index = 0x25CD, name = 'GetPosition'
	list[17] = LF_ONEMETHOD, public, VANILLA, index = 0x2BDA, name = 'SetPosition'
	list[18] = LF_ONEMETHOD, public, VANILLA, index = 0x2BDA, name = 'SetMaxLines'
	list[19] = LF_ONEMETHOD, public, VANILLA, index = 0x2BE1, name = 'ChatChanged'
	list[20] = LF_ONEMETHOD, public, VANILLA, index = 0x2BE1, name = 'HasOldChat'
	list[21] = LF_MEMBER, protected, type = 0x3DDA, offset = 0
		member name = 'msgArray'
	list[22] = LF_MEMBER, protected, type = T_INT4(0074), offset = 4
		member name = 'currMsg'
	list[23] = LF_MEMBER, protected, type = T_INT4(0074), offset = 8
		member name = 'msgCount'
	list[24] = LF_MEMBER, protected, type = T_32PRCHAR(0470), offset = 12
		member name = 'widgetText'
	list[25] = LF_MEMBER, protected, type = T_ULONG(0022), offset = 16
		member name = 'pauseTime'
	list[26] = LF_MEMBER, protected, type = T_UCHAR(0020), offset = 20
		member name = 'changed'
	list[27] = LF_MEMBER, protected, type = 0x1744, offset = 24
		member name = 'lastWidget'
	list[28] = LF_MEMBER, protected, type = T_INT4(0074), offset = 28
		member name = 'maxLines'
	list[29] = LF_MEMBER, protected, type = T_INT4(0074), offset = 32
		member name = 'position'
	list[30] = LF_MEMBER, protected, type = T_UCHAR(0020), offset = 36
		member name = 'chatKilled'
	list[31] = LF_MEMBER, protected, type = T_UCHAR(0020), offset = 37
		member name = 'isSysMsg'
	list[32] = LF_MEMBER, protected, type = 0x1C9B, offset = 40
		member name = 'g_chatSample'
	list[33] = LF_MEMBER, protected, type = 0x1C9B, offset = 44
		member name = 'g_playerDropSample'
	list[34] = LF_MEMBER, protected, type = 0x1C9B, offset = 48
		member name = 'g_sysMsgSample'
	list[35] = LF_MEMBER, protected, type = 0x1C9B, offset = 52
		member name = 'g_turnDurSample'
	list[36] = LF_MEMBER, protected, type = 0x1C9B, offset = 56
		member name = 'g_playerEnterSample'
	list[37] = LF_ONEMETHOD, protected, VANILLA, index = 0x25CD, name = 'GetNextFreeMsgNbr'
	list[38] = LF_ONEMETHOD, protected, VANILLA, index = 0x2BE0, name = 'GetNextMsgNbr'
	list[39] = LF_ONEMETHOD, protected, VANILLA, index = 0x2BDB, name = 'KillOldChat'
	list[40] = LF_ONEMETHOD, protected, VANILLA, index = 0x2BE3, name = 'UpdateWidgetText'
	list[41] = LF_ONEMETHOD, protected, VANILLA, index = 0x2BDB, name = 'UpdateNewChat'
	list[42] = LF_ONEMETHOD, public, VANILLA, (compgenx), index = 0x2BDB, name = '__dflt_ctor_closure'
	list[43] = LF_ONEMETHOD, public, VANILLA, (compgenx), index = 0x3DDB, name = '__vecDelDtor'


Даже не знаю что это:
	0x3def : Length = 758, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_BCLASS, public, type = 0x1743, offset = 0
	list[1] = LF_METHOD, count = 4, list = 0x3DEA, name = 'textEntryWidget'
	list[2] = LF_ONEMETHOD, public, VIRTUAL, index = 0x1E6B, name = '~textEntryWidget'
	list[3] = LF_ONEMETHOD, public, VANILLA, index = 0x3DEB, name = 'Open'
	list[4] = LF_ONEMETHOD, public, VANILLA, index = 0x1E6B, name = 'Close'
	list[5] = LF_ONEMETHOD, public, VIRTUAL, index = 0x1E70, name = 'Main'
	list[6] = LF_ONEMETHOD, public, VIRTUAL, index = 0x1E74, name = 'Draw'
	list[7] = LF_ONEMETHOD, public, INTRODUCING VIRTUAL, index = 0x1E6E, 
		vfptr offset = 48, name = 'SetFocus'
	list[8] = LF_ONEMETHOD, public, VANILLA, index = 0x1E76, name = 'SetupDisplayString'
	list[9] = LF_MEMBER, public, type = 0x105F, offset = 80
		member name = 'textBack'
	list[10] = LF_MEMBER, public, type = 0x3DEC, offset = 84
		member name = 'saveBack'
	list[11] = LF_MEMBER, public, type = T_USHORT(0021), offset = 88
		member name = 'cursorIndex'
	list[12] = LF_MEMBER, public, type = T_USHORT(0021), offset = 90
		member name = 'bufferSize'
	list[13] = LF_MEMBER, public, type = T_SHORT(0011), offset = 92
		member name = 'textWidth'
	list[14] = LF_MEMBER, public, type = T_SHORT(0011), offset = 94
		member name = 'textHeight'
	list[15] = LF_MEMBER, public, type = T_SHORT(0011), offset = 96
		member name = 'textX'
	list[16] = LF_MEMBER, public, type = T_SHORT(0011), offset = 98
		member name = 'textY'
	list[17] = LF_MEMBER, public, type = T_SHORT(0011), offset = 100
		member name = 'textLines'
	list[18] = LF_MEMBER, public, type = T_SHORT(0011), offset = 102
		member name = 'attributes'
	list[19] = LF_MEMBER, public, type = T_SHORT(0011), offset = 104
		member name = 'type'
	list[20] = LF_MEMBER, public, type = T_SHORT(0011), offset = 106
		member name = 'displayOffset'
	list[21] = LF_MEMBER, public, type = T_CHAR(0010), offset = 108
		member name = 'cursorFlashOn'
	list[22] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 109
		member name = 'focus'
	list[23] = LF_ONEMETHOD, public, INTRODUCING VIRTUAL, index = 0x1E70, 
		vfptr offset = 52, name = 'OnKeyPress'
	list[24] = LF_ONEMETHOD, public, VIRTUAL, index = 0x1E78, name = 'SetText'
	list[25] = LF_ONEMETHOD, public, VANILLA, index = 0x1E6F, name = 'GetCharPressed'
	list[26] = LF_ONEMETHOD, public, INTRODUCING VIRTUAL, index = 0x1E79, 
		vfptr offset = 56, name = 'IgnoreKey'
	list[27] = LF_ONEMETHOD, public, VIRTUAL, index = 0x1E6B, name = 'OnSetFocus'
	list[28] = LF_ONEMETHOD, public, VIRTUAL, index = 0x1E6B, name = 'OnKillFocus'
	list[29] = LF_ONEMETHOD, public, INTRODUCING VIRTUAL, index = 0x1E6E, 
		vfptr offset = 60, name = 'SetAutoDraw'
	list[30] = LF_MEMBER, protected, type = T_UCHAR(0020), offset = 110
		member name = 'autoDraw'
	list[31] = LF_ONEMETHOD, protected, INTRODUCING VIRTUAL, index = 0x1E74, 
		vfptr offset = 64, name = 'SaveBackground'
	list[32] = LF_ONEMETHOD, public, VANILLA, (compgenx), index = 0x3DEE, name = 'operator='
	list[33] = LF_ONEMETHOD, public, VANILLA, (compgenx), index = 0x1E6B, name = '__local_vftable_ctor_closure'
	list[34] = LF_ONEMETHOD, public, INTRODUCING VIRTUAL, (compgenx), index = 0x1E80, 
		vfptr offset = 0, name = '__vecDelDtor'





Диалог главного меню
0x473f : Length = 4510, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_BCLASS, public, type = 0x1A7C, offset = 0
	list[1] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 88
		member name = 'my_index'
	list[2] = LF_MEMBER, public, type = T_RCHAR(0070), offset = 89
		member name = 'pos_copy'
	list[3] = LF_MEMBER, public, type = 0x2D14, offset = 90
		member name = 'hero_pos'
	list[4] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 98
		member name = 'loadMode'
	list[5] = LF_MEMBER, public, type = 0x1744, offset = 100
		member name = 'human'
	list[6] = LF_MEMBER, public, type = 0x1744, offset = 104
		member name = 'text'
	list[7] = LF_MEMBER, public, type = 0x1710, offset = 108
		member name = 'handicap'
	list[8] = LF_MEMBER, public, type = 0x1710, offset = 112
		member name = 'townL'
	list[9] = LF_MEMBER, public, type = 0x1710, offset = 116
		member name = 'townR'
	list[10] = LF_MEMBER, public, type = 0x1710, offset = 120
		member name = 'heroL'
	list[11] = LF_MEMBER, public, type = 0x1710, offset = 124
		member name = 'heroR'
	list[12] = LF_MEMBER, public, type = 0x1710, offset = 128
		member name = 'resL'
	list[13] = LF_MEMBER, public, type = 0x1710, offset = 132
		member name = 'resR'
	list[14] = LF_MEMBER, public, type = 0x1710, offset = 136
		member name = 'name'
	list[15] = LF_MEMBER, public, type = 0x1710, offset = 140
		member name = 'flag'
	list[16] = LF_MEMBER, public, type = 0x1710, offset = 144
		member name = 'face'
	list[17] = LF_MEMBER, public, type = 0x1710, offset = 148
		member name = 'town'
	list[18] = LF_MEMBER, public, type = 0x1710, offset = 152
		member name = 'bonus'
	list[19] = LF_MEMBER, public, type = 0x4722, offset = 156
		member name = 'nameEdit'
	list[20] = LF_ONEMETHOD, public, VANILLA, index = 0x24D7, name = 'MaxPlayers'
	list[21] = LF_ONEMETHOD, public, VANILLA, index = 0x25B9, name = 'GetDeviceDesc'
	list[22] = LF_ONEMETHOD, public, VANILLA, index = 0x256A, name = 'FindCurrentVM'
	list[23] = LF_ONEMETHOD, public, VANILLA, index = 0x2476, name = 'SetVMIconStatus'
	list[24] = LF_MEMBER, public, type = T_ULONG(0022), offset = 160
		member name = 'freeBlocks'
	list[25] = LF_MEMBER, public, type = T_ULONG(0022), offset = 164
		member name = 'neededBlocks'
	list[26] = LF_MEMBER, public, type = T_INT4(0074), offset = 168
		member name = 'SavePart'
	list[27] = LF_MEMBER, public, type = 0x184E, offset = 172
		member name = 'tempFilename'
	list[28] = LF_MEMBER, public, type = T_LONG(0012), offset = 188
		member name = 'tempBufStart'
	list[29] = LF_MEMBER, public, type = T_INT4(0074), offset = 192
		member name = 'SelectedVMPort'
	list[30] = LF_NESTTYPE, type = 0x472F, EWidgetIDs
	list[31] = LF_MEMBER, public, type = T_ULONG(0022), offset = 196
		member name = 'clickTime'
	list[32] = LF_METHOD, count = 2, list = 0x4734, name = 'TSingleSelectionWindow'
	list[33] = LF_ONEMETHOD, public, VIRTUAL, index = 0x2476, name = '~TSingleSelectionWindow'
	list[34] = LF_ONEMETHOD, public, VIRTUAL, index = 0x24F3, name = 'DoModal'
	list[35] = LF_ONEMETHOD, public, VANILLA, index = 0x24E5, name = 'GetMapName'
	list[36] = LF_ONEMETHOD, public, VANILLA, index = 0x24E5, name = 'GetFileName'
	list[37] = LF_MEMBER, public, type = 0x24E0, offset = 200
		member name = 'SelectionHeaders'
	list[38] = LF_MEMBER, public, type = T_INT4(0074), offset = 204
		member name = 'num_mapFiles'
	list[39] = LF_MEMBER, public, type = T_INT4(0074), offset = 208
		member name = 'max_maps'
	list[40] = LF_MEMBER, public, type = T_32PINT4(0474), offset = 212
		member name = 'mapFilter'
	list[41] = LF_MEMBER, public, type = T_INT4(0074), offset = 216
		member name = 'mapsInFilter'
	list[42] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 220
		member name = 'loadGameMode'
	list[43] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 221
		member name = 'saveGameMode'
	list[44] = LF_MEMBER, public, type = T_INT4(0074), offset = 224
		member name = 'textIndex'
	list[45] = LF_MEMBER, public, type = 0x1A63, offset = 228
		member name = 'VictoryIcon'
	list[46] = LF_MEMBER, public, type = 0x1A63, offset = 232
		member name = 'LossIcon'
	list[47] = LF_MEMBER, public, type = 0x1A63, offset = 236
		member name = 'TownPix'
	list[48] = LF_MEMBER, public, type = 0x1A63, offset = 240
		member name = 'Resource'
	list[49] = LF_MEMBER, public, type = 0x1A63, offset = 244
		member name = 'heroSpecificAbility'
	list[50] = LF_MEMBER, public, type = 0x105F, offset = 248
		member name = 'GoldBox'
	list[51] = LF_MEMBER, public, type = 0x4461, offset = 252
		member name = 'Flags'
	list[52] = LF_MEMBER, public, type = 0x4461, offset = 284
		member name = 'Panels'
	list[53] = LF_MEMBER, public, type = 0x4735, offset = 316
		member name = 'HeroPix'
	list[54] = LF_MEMBER, public, type = 0x105F, offset = 836
		member name = 'randomTownQuestion'
	list[55] = LF_MEMBER, public, type = 0x105F, offset = 840
		member name = 'randomHeroQuestion'
	list[56] = LF_MEMBER, public, type = 0x105F, offset = 844
		member name = 'randomTown'
	list[57] = LF_MEMBER, public, type = 0x105F, offset = 848
		member name = 'randomHero'
	list[58] = LF_MEMBER, public, type = 0x105F, offset = 852
		member name = 'noDice'
	list[59] = LF_MEMBER, public, type = 0x105F, offset = 856
		member name = 'noHero'
	list[60] = LF_MEMBER, public, type = T_INT4(0074), offset = 860
		member name = 'sortDirection'
	list[61] = LF_MEMBER, public, type = T_INT4(0074), offset = 864
		member name = 'currentIndex'
	list[62] = LF_MEMBER, public, type = T_INT4(0074), offset = 868
		member name = 'currentMap'
	list[63] = LF_MEMBER, public, type = T_INT4(0074), offset = 872
		member name = 'durationIndex'
	list[64] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 876
		member name = 'inAdvancedOptions'
	list[65] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 877
		member name = 'inScenarioOptions'
	list[66] = LF_MEMBER, public, type = 0x4722, offset = 880
		member name = 'saveGameEdit'
	list[67] = LF_MEMBER, public, type = T_UCHAR(0020), offset = 884
		member name = 'mode'
	list[68] = LF_MEMBER, public, type = 0x4736, offset = 888
		member name = 'pNewPlayerUpdateMan'
	list[69] = LF_ONEMETHOD, public, VANILLA, index = 0x24F3, name = 'UpdatePlayerPositions'
	list[70] = LF_ONEMETHOD, public, VANILLA, index = 0x2476, name = 'MakeHeroFilter'
	list[71] = LF_ONEMETHOD, public, VANILLA, index = 0x24EE, name = 'Update'
	list[72] = LF_ONEMETHOD, public, VANILLA, index = 0x24F5, name = 'SortMaps'
	list[73] = LF_ONEMETHOD, public, VANILLA, index = 0x2476, name = 'SetupSecondMenu'
	list[74] = LF_ONEMETHOD, public, VANILLA, index = 0x2476, name = 'RestoreFirstMenu'
	list[75] = LF_ONEMETHOD, public, VANILLA, index = 0x2476, name = 'SetHumanSlot'
	list[76] = LF_ONEMETHOD, public, VIRTUAL, index = 0x24EE, name = 'WindowHandler'
	list[77] = LF_ONEMETHOD, public, VIRTUAL, index = 0x24EE, name = 'ExitDialog'
	list[78] = LF_ONEMETHOD, public, VANILLA, index = 0x2476, name = 'DrawBasicMapInfo'
	list[79] = LF_ONEMETHOD, public, VANILLA, index = 0x2521, name = 'HandleNetMsg'
	list[80] = LF_ONEMETHOD, public, VANILLA, index = 0x2503, name = 'OnGameTransmitInitMsg'
	list[81] = LF_ONEMETHOD, public, VANILLA, index = 0x2503, name = 'OnNewSetupInfoMsg'
	list[82] = LF_ONEMETHOD, public, VANILLA, index = 0x2503, name = 'OnNewPlayerMsg'
	list[83] = LF_ONEMETHOD, public, VANILLA, index = 0x2503, name = 'OnPlayerDroppedMsg'
	list[84] = LF_ONEMETHOD, public, VANILLA, index = 0x2503, name = 'OnSetAsHostMsg'
	list[85] = LF_ONEMETHOD, public, VANILLA, index = 0x2503, name = 'OnNewMapHeaderInfo'
	list[86] = LF_ONEMETHOD, public, VANILLA, index = 0x2503, name = 'OnGameHeaderInfoInitMsg'
	list[87] = LF_ONEMETHOD, public, VANILLA, index = 0x2503, name = 'OnGameHeaderInfoMsg'
	list[88] = LF_ONEMETHOD, public, VANILLA, index = 0x2503, name = 'OnGameHeaderInfoEndMsg'
	list[89] = LF_ONEMETHOD, public, VANILLA, index = 0x2503, name = 'OnScrollMsg'
	list[90] = LF_ONEMETHOD, public, VANILLA, index = 0x2503, name = 'OnBadVersionMsg'
	list[91] = LF_ONEMETHOD, public, VANILLA, index = 0x2470, name = 'OnSortMaps'
	list[92] = LF_ONEMETHOD, public, VANILLA, index = 0x256A, name = 'OnBeginGame'
	list[93] = LF_ONEMETHOD, public, VANILLA, index = 0x2470, name = 'OnChatWindowSlider'
	list[94] = LF_ONEMETHOD, public, VANILLA, index = 0x2470, name = 'OnDurationSlider'
	list[95] = LF_ONEMETHOD, public, VANILLA, index = 0x2470, name = 'OnFileMenuSlider'
	list[96] = LF_ONEMETHOD, public, VANILLA, index = 0x2470, name = 'OnNameSlider'
	list[97] = LF_ONEMETHOD, public, VANILLA, index = 0x24F4, name = 'SendPlayerPositions'
	list[98] = LF_ONEMETHOD, public, VANILLA, index = 0x24F4, name = 'SendGameHeaders'
	list[99] = LF_ONEMETHOD, public, VANILLA, index = 0x24F4, name = 'SendSetupInfo'
	list[100] = LF_ONEMETHOD, public, VANILLA, index = 0x256A, name = 'IsHost'
	list[101] = LF_ONEMETHOD, public, VANILLA, index = 0x2476, name = 'GetHeaders'
	list[102] = LF_ONEMETHOD, public, VANILLA, index = 0x24E2, name = 'GetHeader'
	list[103] = LF_ONEMETHOD, public, VANILLA, index = 0x2476, name = 'UpdateGameVars'
	list[104] = LF_ONEMETHOD, public, VANILLA, index = 0x24FA, name = 'SetCurrentMap'
	list[105] = LF_ONEMETHOD, public, VANILLA, index = 0x2470, name = 'SetFilter'
	list[106] = LF_ONEMETHOD, public, VANILLA, index = 0x256C, name = 'SendChat'
	list[107] = LF_ONEMETHOD, public, VANILLA, index = 0x2573, name = 'ReceiveChat'
	list[108] = LF_ONEMETHOD, public, VANILLA, index = 0x2476, name = 'DisplayChat'
	list[109] = LF_ONEMETHOD, public, VANILLA, index = 0x2539, name = 'OnRequestHeroFaceMsg'
	list[110] = LF_ONEMETHOD, public, VANILLA, index = 0x2539, name = 'OnRequestHeroFaceReplyMsg'
	list[111] = LF_ONEMETHOD, public, VANILLA, index = 0x2535, name = 'OnPingMsg'
	list[112] = LF_ONEMETHOD, public, VANILLA, index = 0x2539, name = 'OnPingResponseMsg'
	list[113] = LF_ONEMETHOD, public, VANILLA, index = 0x2575, name = 'GetHeroFace'
	list[114] = LF_ONEMETHOD, public, VANILLA, index = 0x2539, name = 'OnSetAGRMsg'
	list[115] = LF_ONEMETHOD, public, VANILLA, index = 0x2535, name = 'OnNewHostMsg'
	list[116] = LF_ONEMETHOD, public, VANILLA, index = 0x2470, name = 'OnPlayerPosClick'
	list[117] = LF_ONEMETHOD, public, VANILLA, index = 0x24D7, name = 'GetThisPlayerGamePos'
	list[118] = LF_ONEMETHOD, public, VANILLA, index = 0x2535, name = 'OnUpdatePlayerPosMsg'
	list[119] = LF_ONEMETHOD, public, VANILLA, index = 0x2476, name = 'CheckFaces'
	list[120] = LF_ONEMETHOD, public, VANILLA, index = 0x2476, name = 'SendPlayerFaces'
	list[121] = LF_ONEMETHOD, public, VANILLA, index = 0x256A, name = 'BeginSavedGame'
	list[122] = LF_ONEMETHOD, public, VANILLA, index = 0x256A, name = 'BeginNewGame'
	list[123] = LF_ONEMETHOD, public, VANILLA, index = 0x256A, name = 'IsMultiPlayer'
	list[124] = LF_ONEMETHOD, public, VANILLA, index = 0x2503, name = 'OnMapFileNameMsg'
	list[125] = LF_ONEMETHOD, public, VANILLA, index = 0x2503, name = 'OnHeaderConfirmMsg'
	list[126] = LF_ONEMETHOD, public, VANILLA, index = 0x2503, name = 'OnReqHeaderConfirmMsg'
	list[127] = LF_ONEMETHOD, public, VANILLA, index = 0x2503, name = 'OnMapHeaderRequestMsg'
	list[128] = LF_ONEMETHOD, public, VANILLA, index = 0x24F4, name = 'CheckMissingHeaders'
	list[129] = LF_ONEMETHOD, public, VANILLA, index = 0x2476, name = 'SetDifficultyHiLite'
	list[130] = LF_ONEMETHOD, public, VANILLA, index = 0x2476, name = 'SetupScenarioOptions'
	list[131] = LF_ONEMETHOD, public, VANILLA, index = 0x2476, name = 'SetupAdvancedOptions'
	list[132] = LF_ONEMETHOD, public, VANILLA, index = 0x2476, name = 'TurnOffScenarioOptions'
	list[133] = LF_ONEMETHOD, public, VANILLA, index = 0x2476, name = 'TurnOffAdvancedOptions'
	list[134] = LF_ONEMETHOD, public, VANILLA, index = 0x2476, name = 'UpdateMainWindow'
	list[135] = LF_ONEMETHOD, public, VANILLA, index = 0x2507, name = 'OnWidgetDeselect'
	list[136] = LF_ONEMETHOD, public, VANILLA, index = 0x2503, name = 'OnClickMsg'
	list[137] = LF_ONEMETHOD, public, VANILLA, index = 0x2470, name = 'ShowWidget'
	list[138] = LF_ONEMETHOD, public, VANILLA, index = 0x24F3, name = 'UpdateAllyEnemyFlags'
	list[139] = LF_ONEMETHOD, public, VANILLA, index = 0x24F3, name = 'TurnChatOn'
	list[140] = LF_ONEMETHOD, public, VANILLA, index = 0x24F3, name = 'TurnChatOff'
	list[141] = LF_ONEMETHOD, public, VANILLA, index = 0x2539, name = 'OnTownUpdateMsg'
	list[142] = LF_ONEMETHOD, public, VANILLA, index = 0x2476, name = 'UpdateNameLists'
	list[143] = LF_ONEMETHOD, public, VANILLA, index = 0x2593, name = 'UpdateTown'
	list[144] = LF_ONEMETHOD, public, VANILLA, index = 0x2495, name = 'CanChooseTown'
	list[145] = LF_ONEMETHOD, public, VANILLA, index = 0x2495, name = 'CanChooseHero'
	list[146] = LF_ONEMETHOD, public, VANILLA, index = 0x2495, name = 'HasMultipleTowns'
	list[147] = LF_ONEMETHOD, public, VANILLA, index = 0x2594, name = 'GetDisplayFace'
	list[148] = LF_ONEMETHOD, public, VANILLA, index = 0x2594, name = 'GetHeroInPos'
	list[149] = LF_ONEMETHOD, public, VANILLA, index = 0x2595, name = 'GetDisplayTown'
	list[150] = LF_ONEMETHOD, public, VANILLA, index = 0x24E5, name = 'GetHeroName'
	list[151] = LF_ONEMETHOD, public, VANILLA, index = 0x2596, name = 'OnNameChange'
	list[152] = LF_ONEMETHOD, public, VANILLA, index = 0x2476, name = 'UpdateNames'
	list[153] = LF_ONEMETHOD, public, VANILLA, index = 0x24F4, name = 'SetNewPlayerSlot'
	list[154] = LF_ONEMETHOD, public, VANILLA, index = 0x2597, name = 'HighlightFile'
	list[155] = LF_ONEMETHOD, public, VANILLA, index = 0x2599, name = 'DrawHeroAdvancedOption'
	list[156] = LF_ONEMETHOD, public, VANILLA, index = 0x259A, name = 'CalcPosition'
	list[157] = LF_ONEMETHOD, public, VANILLA, index = 0x2470, name = 'OnNameClick'
	list[158] = LF_ONEMETHOD, public, VANILLA, index = 0x2476, name = 'SetupLoadGameMode'
	list[159] = LF_ONEMETHOD, public, VANILLA, index = 0x2476, name = 'SetupNewGameMode'
	list[160] = LF_ONEMETHOD, public, VANILLA, index = 0x2545, name = 'IsVersionCompatible'
	list[161] = LF_ONEMETHOD, public, VANILLA, index = 0x24D7, name = 'GetFileSpecNbr'
	list[162] = LF_ONEMETHOD, public, VANILLA, index = 0x2476, name = 'OnDeleteFile'
	list[163] = LF_MEMBER, private, type = 0x245E, offset = 892
		member name = 'netPlayerHandler'
	list[164] = LF_MEMBER, private, type = T_UCHAR(0020), offset = 2828
		member name = 'receivedMaps'
	list[165] = LF_MEMBER, private, type = 0x4728, offset = 2832
		member name = 'chatSlider'
	list[166] = LF_MEMBER, private, type = 0x4728, offset = 2836
		member name = 'fileSlider'
	list[167] = LF_MEMBER, private, type = 0x4728, offset = 2840
		member name = 'durationSlider'
	list[168] = LF_MEMBER, private, type = 0x4728, offset = 2844
		member name = 'nameSlider'
	list[169] = LF_MEMBER, private, type = 0x1744, offset = 2848
		member name = 'chatWidget'
	list[170] = LF_MEMBER, private, type = 0x1744, offset = 2852
		member name = 'nameList1'
	list[171] = LF_MEMBER, private, type = 0x1744, offset = 2856
		member name = 'nameList2'
	list[172] = LF_MEMBER, private, type = T_UCHAR(0020), offset = 2860
		member name = 'mapChanged'
	list[173] = LF_MEMBER, private, type = T_UCHAR(0020), offset = 2861
		member name = 'readingMaps'
	list[174] = LF_MEMBER, private, type = 0x4737, offset = 2864
		member name = 'chatEdit'
	list[175] = LF_MEMBER, private, type = T_INT4(0074), offset = 2868
		member name = 'sortWhich'
	list[176] = LF_MEMBER, private, type = T_INT4(0074), offset = 2872
		member name = 'filterSize'
	list[177] = LF_MEMBER, private, type = T_UCHAR(0020), offset = 2876
		member name = 'scenarioOptionsStarted'
	list[178] = LF_MEMBER, private, type = T_UCHAR(0020), offset = 2877
		member name = 'chatShowing'
	list[179] = LF_MEMBER, private, type = 0x4738, offset = 2880
		member name = 'chatToggle'
	list[180] = LF_MEMBER, private, type = T_UCHAR(0020), offset = 2884
		member name = 'receivingMaps'
	list[181] = LF_MEMBER, private, type = 0x2C97, offset = 2888
		member name = 'flagBack'
	list[182] = LF_MEMBER, private, type = 0x248F, offset = 2892
		member name = 'gameVersion'
	list[183] = LF_MEMBER, private, type = 0x259C, offset = 2912
		member name = 'netMsgHandler'
	list[184] = LF_ONEMETHOD, private, VANILLA, index = 0x2577, name = 'GetThisPlayer'
	list[185] = LF_ONEMETHOD, private, VIRTUAL, index = 0x2495, name = 'ProcessRightSelect'
	list[186] = LF_NESTTYPE, type = 0x473A, EOtherWidgetIDs
	list[187] = LF_NESTTYPE, type = 0x473C, __unnamed
	list[188] = LF_ONEMETHOD, public, VANILLA, (compgenx), index = 0x473E, name = 'operator='
	list[189] = LF_ONEMETHOD, public, INTRODUCING VIRTUAL, (compgenx), index = 0x2622, 
		vfptr offset = 0, name = '__vecDelDtor'




		0x48ee : Length = 1722, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_BCLASS, public, type = 0x1DC9, offset = 0
	list[1] = LF_NESTTYPE, type = T_UCHAR(0020), TPixel
	list[2] = LF_NESTTYPE, type = 0x1777, __unnamed
	list[3] = LF_METHOD, count = 4, list = 0x239A, name = 'CSpriteFrame'
	list[4] = LF_ONEMETHOD, public, VANILLA, index = 0x23A0, name = 'Crop'
	list[5] = LF_ONEMETHOD, public, VANILLA, index = 0x23A1, name = 'Encode'
	list[6] = LF_ONEMETHOD, public, VIRTUAL, index = 0x239B, name = '~CSpriteFrame'
	list[7] = LF_ONEMETHOD, public, VANILLA, index = 0x239B, name = 'clear'
	list[8] = LF_ONEMETHOD, public, VANILLA, index = 0x48EF, name = 'Draw'
	list[9] = LF_ONEMETHOD, public, VANILLA, index = 0x48F2, name = 'DrawCreature'
	list[10] = LF_ONEMETHOD, public, VANILLA, index = 0x48F2, name = 'DrawCreatureAlpha'
	list[11] = LF_ONEMETHOD, public, VANILLA, index = 0x48F3, name = 'DrawAdvObj'
	list[12] = LF_ONEMETHOD, public, VANILLA, index = 0x48F4, name = 'DrawAdvObjWithFlag'
	list[13] = LF_ONEMETHOD, public, VANILLA, index = 0x48F4, name = 'DrawAdvObjWithFlagAlpha'
	list[14] = LF_ONEMETHOD, public, VANILLA, index = 0x48F3, name = 'DrawAdvObjShadow'
	list[15] = LF_ONEMETHOD, public, VANILLA, index = 0x48F5, name = 'DrawPointer'
	list[16] = LF_ONEMETHOD, public, VANILLA, index = 0x48F3, name = 'DrawInterface'
	list[17] = LF_ONEMETHOD, public, VANILLA, index = 0x48EF, name = 'DrawTile'
	list[18] = LF_ONEMETHOD, public, VANILLA, index = 0x48EF, name = 'DrawTileShadow'
	list[19] = LF_ONEMETHOD, public, VANILLA, index = 0x48EF, name = 'DrawShroudTile'
	list[20] = LF_ONEMETHOD, public, VANILLA, index = 0x48F3, name = 'DrawHero'
	list[21] = LF_ONEMETHOD, public, VANILLA, index = 0x48F3, name = 'DrawHeroShadow'
	list[22] = LF_ONEMETHOD, public, VANILLA, index = 0x48F3, name = 'DrawHeroAlpha'
	list[23] = LF_ONEMETHOD, public, VANILLA, index = 0x48F3, name = 'DrawCombatHero'
	list[24] = LF_ONEMETHOD, public, VANILLA, index = 0x48EF, name = 'DrawSpellEffect'
	list[25] = LF_ONEMETHOD, public, VANILLA, index = 0x48F6, name = 'DrawAdvObjWithFlagScaled50'
	list[26] = LF_ONEMETHOD, public, VANILLA, index = 0x48F7, name = 'DrawAdvObjShadowScaled50'
	list[27] = LF_ONEMETHOD, public, VANILLA, index = 0x48EF, name = 'DrawTileScaled50'
	list[28] = LF_ONEMETHOD, public, VANILLA, index = 0x48F6, name = 'DrawAdvObjWithFlagScaled25'
	list[29] = LF_ONEMETHOD, public, VANILLA, index = 0x48F7, name = 'DrawAdvObjShadowScaled25'
	list[30] = LF_ONEMETHOD, public, VANILLA, index = 0x48EF, name = 'DrawTileScaled25'
	list[31] = LF_ONEMETHOD, public, VANILLA, index = 0x48F8, name = 'GetDataSize'
	list[32] = LF_ONEMETHOD, public, VANILLA, index = 0x48F8, name = 'GetImageSize'
	list[33] = LF_ONEMETHOD, public, VANILLA, index = 0x48F9, name = 'GetEncodingMethod'
	list[34] = LF_ONEMETHOD, public, VANILLA, index = 0x48F8, name = 'GetWidth'
	list[35] = LF_ONEMETHOD, public, VANILLA, index = 0x48F8, name = 'GetHeight'
	list[36] = LF_ONEMETHOD, public, VANILLA, index = 0x48F8, name = 'GetCroppedWidth'
	list[37] = LF_ONEMETHOD, public, VANILLA, index = 0x48F8, name = 'GetCroppedHeight'
	list[38] = LF_ONEMETHOD, public, VANILLA, index = 0x48F8, name = 'GetCroppedX'
	list[39] = LF_ONEMETHOD, public, VANILLA, index = 0x48F8, name = 'GetCroppedY'
	list[40] = LF_ONEMETHOD, public, VANILLA, index = 0x48F8, name = 'GetPitch'
	list[41] = LF_ONEMETHOD, public, VANILLA, index = 0x48FA, name = 'GetMap'
	list[42] = LF_ONEMETHOD, public, VANILLA, index = 0x48FB, name = 'GetPixel'
	list[43] = LF_ONEMETHOD, public, STATIC, index = 0x48FC, name = 'SetPixelFormat'
	list[44] = LF_STATICMEMBER, public, type = T_USHORT(0021)		member name = 'div2mask'
	list[45] = LF_STATICMEMBER, public, type = T_USHORT(0021)		member name = 'div4mask'
	list[46] = LF_ONEMETHOD, private, VANILLA, index = 0x48FD, name = 'importPCXFile'
	list[47] = LF_ONEMETHOD, private, VANILLA, index = 0x48FD, name = 'importCroppedPCXFile'
	list[48] = LF_MEMBER, private, type = T_INT4(0074), offset = 28
		member name = 'DataSize'
	list[49] = LF_MEMBER, private, type = T_INT4(0074), offset = 32
		member name = 'ImageSize'
	list[50] = LF_MEMBER, private, type = 0x1772, offset = 36
		member name = 'EncodingMethod'
	list[51] = LF_MEMBER, private, type = T_INT4(0074), offset = 40
		member name = 'Width'
	list[52] = LF_MEMBER, private, type = T_INT4(0074), offset = 44
		member name = 'Height'
	list[53] = LF_MEMBER, private, type = T_INT4(0074), offset = 48
		member name = 'CroppedWidth'
	list[54] = LF_MEMBER, private, type = T_INT4(0074), offset = 52
		member name = 'CroppedHeight'
	list[55] = LF_MEMBER, private, type = T_INT4(0074), offset = 56
		member name = 'CroppedX'
	list[56] = LF_MEMBER, private, type = T_INT4(0074), offset = 60
		member name = 'CroppedY'
	list[57] = LF_MEMBER, private, type = T_INT4(0074), offset = 64
		member name = 'Pitch'
	list[58] = LF_MEMBER, private, type = T_32PUCHAR(0420), offset = 68
		member name = 'map'
	list[59] = LF_MEMBER, private, type = 0x1071, offset = 72
		member name = 'ddsd'
	list[60] = LF_MEMBER, private, type = 0x1E2F, offset = 196
		member name = 'ddsurf'
	list[61] = LF_MEMBER, private, type = T_ULONG(0022), offset = 200
		member name = 'compmap_len'
	list[62] = LF_MEMBER, private, type = T_32PUCHAR(0420), offset = 204
		member name = 'tempmem'
	list[63] = LF_ONEMETHOD, private, VANILLA, index = 0x239B, name = 'EncodeGeneral'
	list[64] = LF_ONEMETHOD, private, VANILLA, index = 0x239B, name = 'EncodeTileset'
	list[65] = LF_ONEMETHOD, private, VANILLA, index = 0x239B, name = 'EncodeAdvObj'
	list[66] = LF_ONEMETHOD, private, VANILLA, index = 0x48FE, name = 'DrawCreatureImpl'
	list[67] = LF_ONEMETHOD, private, VANILLA, index = 0x48F2, name = 'DrawAdvObjImpl'
	list[68] = LF_ONEMETHOD, private, VANILLA, index = 0x48F3, name = 'DrawAdvObjShadowImpl'
	list[69] = LF_ONEMETHOD, private, VANILLA, index = 0x48FF, name = 'Clip'
	list[70] = LF_ONEMETHOD, private, VANILLA, index = 0x48FF, name = 'ClipScaled50'
	list[71] = LF_ONEMETHOD, private, VANILLA, index = 0x48FF, name = 'ClipScaled25'
	list[72] = LF_ONEMETHOD, public, VANILLA, (compgenx), index = 0x239B, name = '__local_vftable_ctor_closure'
	list[73] = LF_ONEMETHOD, public, INTRODUCING VIRTUAL, (compgenx), index = 0x4900, 
		vfptr offset = 0, name = '__vecDelDtor'




0x4afe : Length = 1134, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_BCLASS, public, type = 0x1A7C, offset = 0
	list[1] = LF_NESTTYPE, type = 0x273E, EWidgetIDs
	list[2] = LF_METHOD, count = 4, list = 0x4AFA, name = 'TViewArmyWindow'
	list[3] = LF_ONEMETHOD, public, VIRTUAL, index = 0x1AAC, name = '~TViewArmyWindow'
	list[4] = LF_ONEMETHOD, public, VANILLA, index = 0x1AAC, name = 'DoModal'
	list[5] = LF_ONEMETHOD, public, VANILLA, index = 0x1AAC, name = 'QuickView'
	list[6] = LF_ONEMETHOD, public, VIRTUAL, index = 0x4AFB, name = 'WindowHandler'
	list[7] = LF_NESTTYPE, type = 0x2744, EOtherWidgetIDs
	list[8] = LF_NESTTYPE, type = 0x2746, __unnamed
	list[9] = LF_ONEMETHOD, private, VANILLA, index = 0x1AB2, name = 'create_background_widget'
	list[10] = LF_ONEMETHOD, private, VANILLA, index = 0x1AB3, name = 'create_name_widget'
	list[11] = LF_ONEMETHOD, private, VANILLA, index = 0x1AB7, name = 'create_portrait_widget'
	list[12] = LF_ONEMETHOD, private, VANILLA, index = 0x1AB8, name = 'create_attack_widget'
	list[13] = LF_ONEMETHOD, private, VANILLA, index = 0x1AB8, name = 'create_defense_widget'
	list[14] = LF_ONEMETHOD, private, VANILLA, index = 0x1ABA, name = 'create_damage_widget'
	list[15] = LF_ONEMETHOD, private, VANILLA, index = 0x1ABC, name = 'create_shots_widget'
	list[16] = LF_ONEMETHOD, private, VANILLA, index = 0x1AB8, name = 'create_hitpoints_widget'
	list[17] = LF_ONEMETHOD, private, VANILLA, index = 0x1ABD, name = 'create_hitpoints_left_widget'
	list[18] = LF_ONEMETHOD, private, VANILLA, index = 0x1AB8, name = 'create_speed_widget'
	list[19] = LF_ONEMETHOD, private, VANILLA, index = 0x1ABD, name = 'create_morale_widget'
	list[20] = LF_ONEMETHOD, private, VANILLA, index = 0x1ABD, name = 'create_luck_widget'
	list[21] = LF_ONEMETHOD, private, VANILLA, index = 0x4AFD, name = 'create_spell_influence_widgets'
	list[22] = LF_ONEMETHOD, private, VANILLA, index = 0x1AAC, name = 'create_ok_widget'
	list[23] = LF_ONEMETHOD, private, VANILLA, index = 0x1AAC, name = 'create_upgrade_widget'
	list[24] = LF_ONEMETHOD, private, VANILLA, index = 0x1AAC, name = 'create_dismiss_widget'
	list[25] = LF_ONEMETHOD, private, VANILLA, index = 0x1AAC, name = 'create_rollover_widget'
	list[26] = LF_ONEMETHOD, private, VANILLA, index = 0x1AAF, name = 'convertID2HelpID'
	list[27] = LF_MEMBER, private, type = 0x1BAC, offset = 88
		member name = 'ArmyType'
	list[28] = LF_MEMBER, private, type = T_INT4(0074), offset = 92
		member name = 'ArmySize'
	list[29] = LF_MEMBER, private, type = T_INT4(0074), offset = 96
		member name = 'morale'
	list[30] = LF_MEMBER, private, type = 0x1329, offset = 100
		member name = 'morale_help'
	list[31] = LF_MEMBER, private, type = T_INT4(0074), offset = 112
		member name = 'luck'
	list[32] = LF_MEMBER, private, type = 0x1329, offset = 116
		member name = 'luck_help'
	list[33] = LF_MEMBER, private, type = T_INT4(0074), offset = 128
		member name = 'Upgrade'
	list[34] = LF_MEMBER, private, type = T_UCHAR(0020), offset = 132
		member name = 'ShowingUpgradeButton'
	list[35] = LF_MEMBER, private, type = T_UCHAR(0020), offset = 133
		member name = 'ShowingDismissButton'
	list[36] = LF_MEMBER, private, type = T_UCHAR(0020), offset = 134
		member name = 'ShowingOkButton'
	list[37] = LF_MEMBER, private, type = 0x2747, offset = 136
		member name = 'Influence'
	list[38] = LF_MEMBER, private, type = 0x2748, offset = 148
		member name = 'Duration'
	list[39] = LF_MEMBER, private, type = 0x1EFF, offset = 160
		member name = 'RolloverWidget'
	list[40] = LF_MEMBER, private, type = 0x1C39, offset = 164
		member name = 'SpriteWidget'
	list[41] = LF_ONEMETHOD, public, VANILLA, (compgenx), index = 0x274A, name = 'operator='
	list[42] = LF_ONEMETHOD, public, INTRODUCING VIRTUAL, (compgenx), index = 0x1AC1, 
		vfptr offset = 0, name = '__vecDelDtor'
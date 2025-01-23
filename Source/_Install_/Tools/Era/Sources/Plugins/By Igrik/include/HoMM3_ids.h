#pragma once

#define ATTACKER 0
#define DEFENDER 1

// resourses
#define WOOD    0
#define MERCURY 1
#define ORE     2
#define SULFUR  3
#define CRYSTAL 4
#define JEMS    5
#define GOLD    6

// town types
#define TOWN_CASTLE     0
#define TOWN_RAMPART    1
#define TOWN_TOWER      2
#define TOWN_INFERNO    3
#define TOWN_NECROPOLIS 4
#define TOWN_DUNGEON    5
#define TOWN_STRONGHOLD 6
#define TOWN_FORTRESS   7
#define TOWN_CONFLUX    8
#define TOWN_COVE       9
#define TOWN_FACTORY    10

// map object types
#define MAPOBJECT_BOAT   8
#define MAPOBJECT_HERO   34
#define MAPOBJECT_TOWN   98

#define GAMETYPE_HOTSEAT 3

#define MAPTYPE_SOD      2
#define MAPTYPE_AB       1
#define MAPTYPE_ROE      0

#define ID_NONE         -1

// creatures ids
#define CID_PIKEMAN             0
#define CID_HALBERDIER          1
#define CID_ARCHER              2
#define CID_MARKSMAN            3
#define CID_GRIFFIN             4
#define CID_ROYAL_GRIFFIN       5
#define CID_SWORDSMAN           6
#define CID_CRUSADER            7
#define CID_MONK                8
#define CID_ZEALOT              9
#define CID_CAVALIER            10
#define CID_CHAMPION            11
#define CID_ANGEL               12
#define CID_ARCHANGEL           13

#define CID_CENTAUR             14
#define CID_CENTAUR_CAPTAIN     15
#define CID_DWARF               16
#define CID_BATTLE_DWARF        17
#define CID_WOOD_ELF            18
#define CID_GRAND_ELF           19
#define CID_PEGASUS             20
#define CID_SILVER_PEGASUS      21
#define CID_DENDROID_GUARD      22
#define CID_DENDROID_SOLDIER    23
#define CID_UNICORN             24
#define CID_WAR_UNICORN         25
#define CID_GREEN_DRAGON        26
#define CID_GOLD_DRAGON         27

#define CID_GREMLIN             28
#define CID_MASTER_GREMLIN      29
#define CID_STONE_GARGOYLE      30
#define CID_OBSIDIAN_GARGOYLE   31
#define CID_STONE_GOLEM         32
#define CID_IRON_GOLEM          33
#define CID_MAGE                34
#define CID_ARCH_MAGE           35
#define CID_GENIE               36
#define CID_MASTER_GENIE        37
#define CID_NAGA                38
#define CID_NAGA_QUEEN          39
#define CID_GIANT               40
#define CID_TITAN               41

#define CID_IMP                 42
#define CID_FAMILIAR            43
#define CID_GOG                 44
#define CID_MAGOG               45
#define CID_HELL_HOUND          46
#define CID_CERBERUS            47
#define CID_DEMON               48
#define CID_HORNED_DEMON        49
#define CID_PIT_FIEND           50
#define CID_PIT_LORD            51
#define CID_EFREETI             52
#define CID_EFREET_SULTAN       53
#define CID_DEVIL               54
#define CID_ARCH_DEVIL          55

#define CID_SKELETON            56
#define CID_SKELETON_WARRIOR    57
#define CID_WALKING_DEAD        58
#define CID_ZOMBIE              59
#define CID_WIGHT               60
#define CID_WRAITH              61
#define CID_VAMPIRE             62
#define CID_VAMPIRE_LORD        63
#define CID_LICH                64
#define CID_POWER_LICH          65
#define CID_BLACK_KNIGHT        66
#define CID_DREAD_KNIGHT        67
#define CID_BONE_DRAGON         68
#define CID_GHOST_DRAGON        69

#define CID_TROGLODYTE          70
#define CID_INFERNAL_TROGLODYTE 71
#define CID_HARPY               72
#define CID_HARPY_HAG           73
#define CID_BEHOLDER            74
#define CID_EVIL_EYE            75
#define CID_MEDUSA              76
#define CID_MEDUSA_QUEEN        77
#define CID_MINOTAUR            78
#define CID_MINOTAUR_KING       79
#define CID_MANTICORE           80
#define CID_SCORPICORE          81
#define CID_RED_DRAGON          82
#define CID_BLACK_DRAGON        83

#define CID_GOBLIN              84
#define CID_HOBGOBLIN           85
#define CID_WOLF_RIDER          86
#define CID_WOLF_RAIDER         87
#define CID_ORC                 88
#define CID_ORC_CHIEFTAIN       89
#define CID_OGRE                90
#define CID_OGRE_MAGE           91
#define CID_ROC                 92
#define CID_THUNDERBIRD         93
#define CID_CYCLOPS             94
#define CID_CYCLOPS_KING        95
#define CID_BEHEMOTH            96
#define CID_ANCIENT_BEHEMOTH    97

#define CID_GNOLL               98
#define CID_GNOLL_MARAUDER      99
#define CID_LIZARDMAN           100
#define CID_LIZARD_WARRIOR      101
#define CID_GORGON              102
#define CID_MIGHTY_GORGON       103
#define CID_SERPENT_FLY         104
#define CID_DRAGON_FLY          105
#define CID_BASILISK            106
#define CID_GREATER_BASILISK    107
#define CID_WYVERN              108
#define CID_WYVERN_MONARCH      109
#define CID_HYDRA               110
#define CID_CHAOS_HYDRA         111

#define CID_AIR_ELEMENTAL       112
#define CID_EARTH_ELEMENTAL     113
#define CID_FIRE_ELEMENTAL      114
#define CID_WATER_ELEMENTAL     115
#define CID_GOLD_GOLEM          116
#define CID_DIAMOND_GOLEM       117

#define CID_PIXIE               118
#define CID_SPRITE              119
#define CID_PSYCHIC_ELEMENTAL   120
#define CID_MAGIC_ELEMENTAL     121
#define CID_NOT_USED1           122
#define CID_ICE_ELEMENTAL       123
#define CID_NOT_USED2           124
#define CID_MAGMA_ELEMENTAL     125
#define CID_NOT_USED3           126
#define CID_STORM_ELEMENTAL     127
#define CID_NOT_USED4           128
#define CID_ENERGY_ELEMENTAL    129
#define CID_FIREBIRD            130
#define CID_PHOENIX             131

#define CID_AZURE_DRAGON        132
#define CID_CRYSTAL_DRAGON      133
#define CID_FAERIE_DRAGON       134
#define CID_RUST_DRAGON         135
#define CID_ENCHANTER           136
#define CID_SHARPSHOOTER        137
#define CID_HALFLING            138
#define CID_PEASANT             139
#define CID_BOAR                140
#define CID_MUMMY               141
#define CID_NOMAD               142
#define CID_ROGUE               143
#define CID_TROLL               144

#define CID_CATAPULT            145
#define CID_BALLISTA            146
#define CID_FIRST_AID_TENT      147
#define CID_AMMO_CART           148
#define CID_ARROW_TOWER         149

#define CID_SUPREME_ARCHANGEL   150
#define CID_DIAMOND_DRAGON      151
#define CID_LORD_OF_THUNDER     152
#define CID_HELL_BARON          153
#define CID_BLOOD_DRAGON        154
#define CID_DARKNESS_DRAGON     155
#define CID_GHOST_BEHEMOTH      156
#define CID_HELL_HYDRA          157
#define CID_SACRED_PHOENIX      158

#define CID_GHOST               159
#define CID_EMISSARY_OF_WAR     160
#define CID_EMISSARY_OF_PEACE   161
#define CID_EMISSARY_OF_MANA    162
#define CID_EMISSARY_OF_LORE    163

#define CID_FIRE_MESSENGER      164
#define CID_EARTH_MESSENGER     165
#define CID_AIR_MESSENGER       166
#define CID_WATER_MESSENGER     167

#define CID_GORYNYCH            168
#define CID_WAR_ZEALOT          169
#define CID_ARCTIC_SHARPSHOOTER 170
#define CID_LAVA_SHARPSHOOTER   171
#define CID_NIGHTMARE           172
#define CID_SANTA_GREMLIN       173

#define CID_COMMANDER_FIRST_A   174
#define CID_PALADIN_A           174
#define CID_HIEROPHANT_A        175
#define CID_TEMPLE_GUARDIAN_A   176
#define CID_SUCCUBUS_A          177
#define CID_SOUL_EATER_A        178
#define CID_BRUTE_A             179
#define CID_OGRE_LEADER_A       180
#define CID_SHAMAN_A            181
#define CID_ASTRAL_SPIRIT_A     182
#define CID_COMMANDER_LAST_A    182

#define CID_COMMANDER_FIRST_D   183
#define CID_PALADIN_D           183
#define CID_HIEROPHANT_D        184
#define CID_TEMPLE_GUARDIAN_D   185
#define CID_SUCCUBUS_D          186
#define CID_SOUL_EATER_D        187
#define CID_BRUTE_D             188
#define CID_OGRE_LEADER_D       189
#define CID_SHAMAN_D            190
#define CID_ASTRAL_SPIRIT_D     191
#define CID_COMMANDER_LAST_D    191

#define CID_SYLVAN_CENTAUR      192
#define CID_SORCERESS_WOG       193
#define CID_WEREWOLF            194
#define CID_HELL_STEED          195
#define CID_DRACOLICH           196
#define CID_LAST_WOG            196

// HotA
#define CID_CANNON               150 // Пушка
#define CID_SEA_DOG              151 // Морской волк
#define CID_NYMPH                153 // Нимфа
#define CID_OCEANID              154 // Океанида
#define CID_CREW_MATE            155 // Матрос
#define CID_SEAMAN               156 // Головорез
#define CID_PIRATE               157 // Пират
#define CID_CORSAIR              158 // Корсар
//  CID_SEA_DOG                  151 // Морской волк
#define CID_STORMBIRD            159 // Дух океана
#define CID_ASSID                160 // Ассида
#define CID_SEA_WITCH            161 // Жрица моря
#define CID_SORCERESS            162 // Заклинательница
#define CID_NIX                  163 // Никс
#define CID_NIX_WARRIOR          164 // Никс-воин
#define CID_SEA_SERPENT          165 // Морской змей 
#define CID_HASPID               166 // Аспид
// Factory
//      CID_HALFLING             138
#define CID_HALFLING_GRENADIER   171
#define CID_MECHANIC             172
#define CID_ENGINEER             173
#define CID_ARMADILOS            174
#define CID_ARMADILOS_BELLWETHER 175
#define CID_ARUTOMATON           176
#define CID_ARUTOMATON_SENTINEIL 177
#define CID_SANDWORM             178
#define CID_OLGOI_KHORKHOI       179
#define CID_GANSLINGER           180
#define CID_BOUNTYHUNTER         181
#define CID_COUATL               182
#define CID_COUATL_CRIMSON       183
#define CID_DREADNOUGTH          184
#define CID_JUGGERNAUT           185

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// arts ids
 
#define AID_SPELL_BOOK 0 
#define AID_SPELL_SCROLL 1 
#define AID_THE_GRAIL 2 
#define AID_CATAPULT 3 
#define AID_BALLISTA 4 
#define AID_AMMO_CART 5 
#define AID_FIRST_AID_TENT 6 
#define AID_CENTAURS_AXE 7 
#define AID_BLACKSHARD_OF_THE_DEAD_KNIGHT 8 
#define AID_GREATER_GNOLLS_FLAIL 9 
#define AID_OGRES_CLUB_OF_HAVOC 10 
#define AID_SWORD_OF_HELLFIRE 11 
#define AID_TITANS_GLADIUS 12 
#define AID_SHIELD_OF_THE_DWARVEN_LORDS 13 
#define AID_SHIELD_OF_THE_YAWNING_DEAD 14 
#define AID_BUCKLER_OF_THE_GNOLL_KING 15 
#define AID_TARG_OF_THE_RAMPAGING_OGRE 16 
#define AID_SHIELD_OF_THE_DAMNED 17 
#define AID_SENTINELS_SHIELD 18 
#define AID_HELM_OF_THE_ALABASTER_UNICORN 19 
#define AID_SKULL_HELMET 20 
#define AID_HELM_OF_CHAOS 21 
#define AID_CROWN_OF_THE_SUPREME_MAGI 22 
#define AID_HELLSTORM_HELMET 23 
#define AID_THUNDER_HELMET 24 
#define AID_BREASTPLATE_OF_PETRIFIED_WOOD 25 
#define AID_RIB_CAGE 26 
#define AID_SCALES_OF_THE_GREATER_BASILISK 27 
#define AID_TUNIC_OF_THE_CYCLOPS_KING 28 
#define AID_BREASTPLATE_OF_BRIMSTONE 29 
#define AID_TITANS_CUIRASS 30 
#define AID_ARMOR_OF_WONDER 31 
#define AID_SANDALS_OF_THE_SAINT 32 
#define AID_CELESTIAL_NECKLACE_OF_BLISS 33 
#define AID_LIONS_SHIELD_OF_COURAGE 34 
#define AID_SWORD_OF_JUDGEMENT 35 
#define AID_HELM_OF_HEAVENLY_ENLIGHTENMENT 36 
#define AID_QUIET_EYE_OF_THE_DRAGON 37 
#define AID_RED_DRAGON_FLAME_TONGUE 38 
#define AID_DRAGON_SCALE_SHIELD 39 
#define AID_DRAGON_SCALE_ARMOR 40 
#define AID_DRAGONBONE_GREAVES 41 
#define AID_DRAGON_WING_TABARD 42 
#define AID_NECKLACE_OF_DRAGONTEETH 43 
#define AID_CROWN_OF_DRAGONTOOTH 44 
#define AID_STILL_EYE_OF_THE_DRAGON 45 
#define AID_CLOVER_OF_FORTUNE 46 
#define AID_CARDS_OF_PROPHECY 47 
#define AID_LADYBIRD_OF_LUCK 48 
#define AID_BADGE_OF_COURAGE 49 
#define AID_CREST_OF_VALOR 50 
#define AID_GLYPH_OF_GALLANTRY 51 
#define AID_SPECULUM 52 
#define AID_SPYGLASS 53 
#define AID_AMULET_OF_THE_UNDERTAKER 54 
#define AID_VAMPIRES_COWL 55 
#define AID_DEAD_MANS_BOOTS 56 
#define AID_GARNITURE_OF_INTERFERENCE 57 
#define AID_SURCOAT_OF_COUNTERPOISE 58 
#define AID_BOOTS_OF_POLARITY 59 
#define AID_BOW_OF_ELVEN_CHERRYWOOD 60 
#define AID_BOWSTRING_OF_THE_UNICORNS_MANE 61 
#define AID_ANGEL_FEATHER_ARROWS 62 
#define AID_BIRD_OF_PERCEPTION 63 
#define AID_STOIC_WATCHMAN 64 
#define AID_EMBLEM_OF_COGNIZANCE 65 
#define AID_STATESMANS_MEDAL 66 
#define AID_DIPLOMATS_RING 67 
#define AID_AMBASSADORS_SASH 68 
#define AID_RING_OF_THE_WAYFARER 69 
#define AID_EQUESTRIANS_GLOVES 70 
#define AID_NECKLACE_OF_OCEAN_GUIDANCE 71 
#define AID_ANGEL_WINGS 72 
#define AID_CHARM_OF_MANA 73 
#define AID_TALISMAN_OF_MANA 74 
#define AID_MYSTIC_ORB_OF_MANA 75 
#define AID_COLLAR_OF_CONJURING 76 
#define AID_RING_OF_CONJURING 77 
#define AID_CAPE_OF_CONJURING 78 
#define AID_ORB_OF_THE_FIRMAMENT 79 
#define AID_ORB_OF_SILT 80 
#define AID_ORB_OF_TEMPESTUOUS_FIRE 81 
#define AID_ORB_OF_DRIVING_RAIN 82 
#define AID_RECANTERS_CLOAK 83 
#define AID_SPIRIT_OF_OPPRESSION 84 
#define AID_HOURGLASS_OF_THE_EVIL_HOUR 85 
#define AID_TOME_OF_FIRE_MAGIC 86 
#define AID_TOME_OF_AIR_MAGIC 87 
#define AID_TOME_OF_WATER_MAGIC 88 
#define AID_TOME_OF_EARTH_MAGIC 89 
#define AID_BOOTS_OF_LEVITATION 90 
#define AID_GOLDEN_BOW 91 
#define AID_SPHERE_OF_PERMANENCE 92 
#define AID_ORB_OF_VULNERABILITY 93 
#define AID_RING_OF_VITALITY 94 
#define AID_RING_OF_LIFE 95 
#define AID_VIAL_OF_LIFEBLOOD 96 
#define AID_NECKLACE_OF_SWIFTNESS 97 
#define AID_BOOTS_OF_SPEED 98 
#define AID_CAPE_OF_VELOCITY 99 
#define AID_PENDANT_OF_DISPASSION 100 
#define AID_PENDANT_OF_SECOND_SIGHT 101 
#define AID_PENDANT_OF_HOLINESS 102 
#define AID_PENDANT_OF_LIFE 103 
#define AID_PENDANT_OF_DEATH 104 
#define AID_PENDANT_OF_FREE_WILL 105 
#define AID_PENDANT_OF_NEGATIVITY 106 
#define AID_PENDANT_OF_TOTAL_RECALL 107 
#define AID_PENDANT_OF_COURAGE 108 
#define AID_EVERFLOWING_CRYSTAL_CLOAK 109 
#define AID_RING_OF_INFINITE_GEMS 110 
#define AID_EVERPOURING_VIAL_OF_MERCURY 111 
#define AID_INEXHAUSTIBLE_CART_OF_ORE 112 
#define AID_EVERSMOKING_RING_OF_SULFUR 113 
#define AID_INEXHAUSTIBLE_CART_OF_LUMBER 114 
#define AID_ENDLESS_SACK_OF_GOLD 115 
#define AID_ENDLESS_BAG_OF_GOLD 116 
#define AID_ENDLESS_PURSE_OF_GOLD 117 
#define AID_LEGS_OF_LEGION 118 
#define AID_LOINS_OF_LEGION 119 
#define AID_TORSO_OF_LEGION 120 
#define AID_ARMS_OF_LEGION 121 
#define AID_HEAD_OF_LEGION 122 
#define AID_SEA_CAPTAINS_HAT 123 
#define AID_SPELLBINDERS_HAT 124 
#define AID_SHACKLES_OF_WAR 125 
#define AID_ORB_OF_INHIBITION 126 
#define AID_VIAL_OF_DRAGON_BLOOD 127 
#define AID_ARMAGEDDONS_BLADE 128 
#define AID_ANGELIC_ALLIANCE 129 
#define AID_CLOAK_OF_THE_UNDEAD_KING 130 
#define AID_ELIXIR_OF_LIFE 131 
#define AID_ARMOR_OF_THE_DAMNED 132 
#define AID_STATUE_OF_LEGION 133 
#define AID_POWER_OF_THE_DRAGON_FATHER 134 
#define AID_TITANS_THUNDER 135 
#define AID_ADMIRALS_HAT 136 
#define AID_BOW_OF_THE_SHARPSHOOTER 137 
#define AID_WIZARDS_WELL 138 
#define AID_RING_OF_THE_MAGI 139 
#define AID_CORNUCOPIA 140 
#define AID_DIPLOMATS_SUIT 141 
#define AID_MIRED_IN_NEUTRALITY 142 
#define AID_IRONFIST_OF_THE_OGRE 143 

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////


// doll art slots
#define AS_HEAD    0
#define AS_SHOULDERS  1
#define AS_NECK    2
#define AS_RIGHT_HAND  3
#define AS_LEFT_HAND  4
#define AS_TORSO   5
#define AS_RIGHT_RING  6
#define AS_LEFT_RING  7
#define AS_FEET    8
#define AS_MISC_1   9
#define AS_MISC_2   10
#define AS_MISC_3   11
#define AS_MISC_4   12
#define AS_WAR_MACHINE_1 13
#define AS_WAR_MACHINE_2 14
#define AS_WAR_MACHINE_3 15
#define AS_WAR_MACHINE_4 16
#define AS_SPELL_BOOK  17
#define AS_MISC_5   18

#define AS_BALLISTA  AS_WAR_MACHINE_1
#define AS_AMMO_CART AS_WAR_MACHINE_2


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// Heroes Primary Skills
#define HPS_ATTACK      0
#define HPS_DEFENSE     1
#define HPS_SPELL_POWER 2
#define HPS_KNOWLEDGE   3

// Heroes Second levels
#define HSSL_NONE     0
#define HSSL_BASIC    1
#define HSSL_ADVANCED 2
#define HSSL_EXPERT   3

// Heroes Secondary Skills
#define HSS_PATHFINDING 0
#define HSS_ARCHERY  1
#define HSS_LOGISTICS 2
#define HSS_SCOUTING 3
#define HSS_DIPLOMACY 4
#define HSS_NAVIGATION 5
#define HSS_LEADERSHIP 6
#define HSS_WISDOM  7
#define HSS_MYSTICISM 8
#define HSS_LUCK  9
#define HSS_BALLISTICS 10
#define HSS_EAGLE_EYE 11
#define HSS_NECROMANCY 12
#define HSS_ESTATES  13
#define HSS_FIRE_MAGIC 14
#define HSS_AIR_MAGIC 15
#define HSS_WATER_MAGIC 16
#define HSS_EARTH_MAGIC 17
#define HSS_SCHOLAR  18
#define HSS_TACTICS  19
#define HSS_ARTILLERY 20
#define HSS_LEARNING 21
#define HSS_OFFENCE  22
#define HSS_ARMORER  23
#define HSS_INTELLIGENCE 24
#define HSS_SORCERY  25
#define HSS_RESISTANCE 26
#define HSS_FIRST_AID 27


// heroes spec info
#define HSI_SECOND_SKILL 0
#define HSI_CREATURE_BONUS 1
#define HSI_RESOURCE 2
#define HSI_SPELL 3
#define HSI_CREATURE_EXTRA 4
#define HSI_SPEED 5
#define HSI_CREATURE_UPGRADE 6
#define HSI_DRAGONS 7

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// heroes ids
#define HID_NONE -1
// Castle
#define HID_ORRIN 0
#define HID_VALESKA 1
#define HID_EDRIC 2
#define HID_SYLVIA 3
#define HID_LORD_HAART 4
#define HID_SORSHA 5
#define HID_CHRISTIAN 6
#define HID_TYRIS 7
#define HID_RION 8
#define HID_ADELA 9
#define HID_CUTHBERT 10
#define HID_ADELAIDE 11
#define HID_INGHAM 12
#define HID_SANYA 13
#define HID_LOYNIS 14
#define HID_CAITLIN 15
// Rampart
#define HID_MEPHALA 16
#define HID_UFRETIN 17
#define HID_JENOVA 18
#define HID_RYLAND 19
#define HID_THORGRIM 20
#define HID_IVOR 21
#define HID_CLANCY 22
#define HID_KYRRE 23
#define HID_CORONIUS 24
#define HID_ULAND 25
#define HID_ELLESHAR 26
#define HID_GEM 27
#define HID_MALCOM 28
#define HID_MELODIA 29
#define HID_ALAGAR 30
#define HID_AERIS 31
// Tower
#define HID_PIQUEDRAM 32
#define HID_THANE 33
#define HID_JOSEPHINE 34
#define HID_NEELA 35
#define HID_TOROSAR 36
#define HID_FAFNER 37
#define HID_RISSA 38
#define HID_IONA 39
#define HID_ASTRAL 40
#define HID_HALON 41
#define HID_SERENA 42
#define HID_DAREMYTH 43
#define HID_THEODORUS 44
#define HID_SOLMYR 45
#define HID_CYRA 46
#define HID_AINE 47
// Inferno
#define HID_FIONA 48
#define HID_RASHKA 49
#define HID_MARIUS 50
#define HID_IGNATIUS 51
#define HID_OCTAVIA 52
#define HID_CALH 53
#define HID_PYRE 54
#define HID_NYMUS 55
#define HID_AYDEN 56
#define HID_XYRON 57
#define HID_AXSIS 58
#define HID_OLEMA 59
#define HID_CALID 60
#define HID_ASH 61
#define HID_ZYDAR 62
#define HID_XARFAX 63
// Necropolis
#define HID_STRAKER         64
#define HID_VOKIAL          65
#define HID_MOANDOR         66
#define HID_CHARNA          67
#define HID_TAMIKA          68
#define HID_ISRA            69
#define HID_CLAVIUS         70
#define HID_GALTHRAN        71
#define HID_SEPTIENNA       72
#define HID_AISLINN         73
#define HID_SANDRO          74
#define HID_NIMBUS          75
#define HID_THANT           76
#define HID_XSI             77
#define HID_VIDOMINA        78
#define HID_NAGASH          79
// Dungeon
#define HID_LORELEI 80
#define HID_ARLACH 81
#define HID_DACE 82
#define HID_AJIT 83
#define HID_DAMACON 84
#define HID_GUNNAR 85
#define HID_SYNCA 86
#define HID_SHAKTI 87
#define HID_ALAMAR 88
#define HID_JAEGAR 89
#define HID_MALEKITH 90
#define HID_JEDDITE 91
#define HID_GEON 92
#define HID_DEEMER 93
#define HID_SEPHINROTH 94
#define HID_DARKSTORN 95
// Stronghold
#define HID_YOG 96
#define HID_GURNISSON 97
#define HID_JABARKAS 98
#define HID_SHIVA 99
#define HID_GRETCHIN 100
#define HID_KRELLION 101
#define HID_CRAG_HACK 102
#define HID_TYRAXOR 103
#define HID_GIRD 104
#define HID_VEY 105
#define HID_DESSA 106
#define HID_TEREK 107
#define HID_ZUBIN 108
#define HID_GUNDULA 109
#define HID_ORIS 110
#define HID_SAURUG 111
// Fortress
#define HID_BRON            112
#define HID_DRAKON          113
#define HID_WYSTAN          114
#define HID_TAZAR           115
#define HID_ALKIN           116
#define HID_KORBAC          117
#define HID_GERWULF         118
#define HID_BROGHILD        119
#define HID_MIRLANDA        120
#define HID_ROSIC           121
#define HID_VOY             122
#define HID_VERDISH         123
#define HID_MERIST          124
#define HID_STYG            125
#define HID_ANDRA           126
#define HID_TIVA            127
// Conflux
#define HID_PASIS           128
#define HID_THUNAR          129
#define HID_IGNISSA         130
#define HID_LACUS           131
#define HID_MONERE          132
#define HID_ERDAMON         133
#define HID_FIUR            134
#define HID_KALT            135
#define HID_LUNA            136
#define HID_BRISSA          137
#define HID_CIELE           138
#define HID_LABETHA         139
#define HID_INTEUS          140
#define HID_AENAIN          141
#define HID_GELARE          142
#define HID_GRINDAN         143
// Campanian heroes
#define HID_SIR_MULLICH     144
#define HID_ADRIENNE        145
#define HID_CATHERINE       146
#define HID_DRACON          147
#define HID_GELU            148
#define HID_KILGOR          149
#define HID_LORD_HAART_NECRO 150
#define HID_MUTARE          151
#define HID_ROLAND          152
#define HID_MUTARE_DRAKE    153
#define HID_BORAGUS         154
#define HID_XERON           155
// Cove
#define HID_СORKES          156
#define HID_JEREMY          157
#define HID_ILLOR           158
#define HID_DEREK           159
#define HID_LEENA           160
#define HID_ANABEL          161
#define HID_CASSIOPEIA      162
#define HID_MIRIAM          163
#define HID_CASMETRA        164
#define HID_EOVACIUS        165
#define HID_SPINT           166
#define HID_ANDAL           167
#define HID_MANFRED         168
#define HID_ZILARE          169
#define HID_ASTRA           170
#define HID_DARGEM          171
// Hota Campanian heroes
#define HID_BIDLEY          172
#define HID_TARK            173
#define HID_ELMORE          174
#define HID_BEATRICE        175
#define HID_KINKERIA        176
#define HID_RANLOO          177
#define HID_GISELLE         178
// Factory
#define HID_HENRIETTA       179
#define HID_SAM             180
#define HID_TANCRED         181
#define HID_MELCHIOR        182
#define HID_FLORIBERT       183
#define HID_WYNONA          184
#define HID_DUTY            185
#define HID_MORTON          186
#define HID_CELESTINE       187
#define HID_TODD            188
#define HID_AGAR            189
#define HID_BERTRAM         190
#define HID_WRATHMONT       191
#define HID_ZIPH            192
// Factory Campanian heroes
#define HID_VICTORIA        193
#define HID_EANSWYTHE       194
#define HID_FREDERICK       195
#define HID_TAVIN           196
#define HID_MURDOCH         197

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// spells
#define SPL_SUMMON_BOAT  0
#define SPL_SCUTTLE_BOAT 1
#define SPL_VISIONS   2
#define SPL_VIEW_EARTH  3
#define SPL_DISGUISE  4
#define SPL_VIEW_AIR  5
#define SPL_FLY    6
#define SPL_WATER_WALK  7
#define SPL_DIMENSION_DOOR 8
#define SPL_TOWN_PORTAL  9

#define SPL_QUICKSAND  10
#define SPL_LAND_MINE  11
#define SPL_FORCE_FIELD  12
#define SPL_FIRE_WALL  13
#define SPL_EARTHQUAKE  14
#define SPL_MAGIC_ARROW  15
#define SPL_ICE_BOLT  16
#define SPL_LIGHTNING_BOLT 17
#define SPL_IMPLOSION  18
#define SPL_CHAIN_LIGHTNING 19
#define SPL_FROST_RING  20
#define SPL_FIREBALL  21
#define SPL_INFERNO   22
#define SPL_METEOR_SHOWER 23
#define SPL_DEATH_RIPPLE 24
#define SPL_DESTROY_UNDEAD 25
#define SPL_ARMAGEDDON  26
#define SPL_SHIELD   27
#define SPL_AIR_SHIELD  28
#define SPL_FIRE_SHIELD  29
#define SPL_PROTECTION_FROM_AIR  30
#define SPL_PROTECTION_FROM_FIRE 31
#define SPL_PROTECTION_FROM_WATER 32
#define SPL_PROTECTION_FROM_EARTH 33
#define SPL_ANTI_MAGIC  34
#define SPL_DISPEL   35
#define SPL_MAGIC_MIRROR 36
#define SPL_CURE   37
#define SPL_RESURRECTION 38
#define SPL_ANIMATE_DEAD 39
#define SPL_SACRIFICE  40
#define SPL_BLESS   41
#define SPL_CURSE   42
#define SPL_BLOODLUST  43
#define SPL_PRECISION  44
#define SPL_WEAKNESS  45
#define SPL_STONE_SKIN  46
#define SPL_DISRUPTING_RAY 47
#define SPL_PRAYER   48
#define SPL_MIRTH   49
#define SPL_SORROW   50
#define SPL_FORTUNE   51
#define SPL_MISFORTUNE  52
#define SPL_HASTE   53
#define SPL_SLOW   54
#define SPL_SLAYER   55
#define SPL_FRENZY   56
#define SPL_TITANS_LIGHTNING_BOLT 57
#define SPL_COUNTERSTRIKE 58
#define SPL_BERSERK   59
#define SPL_HYPNOTIZE  60
#define SPL_FORGETFULNESS 61
#define SPL_BLIND   62
#define SPL_TELEPORT  63
#define SPL_REMOVE_OBSTACLE 64
#define SPL_CLONE   65
#define SPL_FIRE_ELEMENTAL 66
#define SPL_EARTH_ELEMENTAL 67
#define SPL_WATER_ELEMENTAL 68
#define SPL_AIR_ELEMENTAL 69

#define SPL_STONE   70 //443D3A 43E0EB 441B0D (!= НЕ ОТВ. НА АТАКУ)
#define SPL_POISON   71
#define SPL_BIND   72
#define SPL_DESEASE   73
#define SPL_PARALYZE  74
#define SPL_AGING   75
#define SPL_DEATH_CLOUD  76
#define SPL_THUNDERBOLT  77
#define SPL_DISPEL_POSITIVE_SPELL  78
#define SPL_DEATH_STARE  79
#define SPL_ACID_BREATH  80

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// spells flags
#define SPF_BATTLE    0x00000001 //- BF spell
#define SPF_MAP     0x00000002 //- MAP spell
#define SPF_TIME    0x00000004 //- Has a time scale (3 rounds or so)
#define SPF_CREATURE   0x00000008 //- Creature Spell
#define SPF_ON_STACK   0x00000010 //- target - single stack
#define SPF_ON_SHOOTING_STACK   0x00000020 //- target - single shooting stack (???)
#define SPF_HAS_MASS_ON_EXPERT 0x00000040 //- has a mass version at expert
#define SPF_ON_LOCATION   0x00000080 //- target - any location
#define SPF_ON_OBSTACLE 0x00000100 // target - only obstacle 
#define SPF_DAMAGE  0x00000200 // Damage Spell 
#define SPF_MIND    0x00000400 //- Mind spell
#define SPF_FRIENDLY_HAS_MASS   0x00000800 //- friendly and has mass version
#define SPF_NOT_ON_MACHINE  0x00001000 //- cannot be cast on SIEGE_WEAPON
#define SPF_ARTIFACT   0x00002000 //- Spell from Artifact
//0x00004000 -
//0x00008000 - AI 
//0x00010000 - AI area effect
//0x00020000 - AI
//0x00040000 - AI
//0x00080000 - AI number/ownership of stacks may be changed 
//0x00100000 - AI

// spells scool flags
#define SSF_AIR  1 
#define SSF_FIRE 2
#define SSF_WATER 4
#define SSF_EARTH 8

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// battle creatures flags
#define BCF_2HEX_WIDE           0x00000001              // Широкий - занимает две клетки
#define BCF_CAN_FLY             0x00000002              // летает
#define BCF_CAN_SHOOT           0x00000004              // стреляет
#define BCF_2HEX_ATTACK         0x00000008              // дыхание дракона
#define BCF_ALIVE               0x00000010              // живое существо (можно восстанавливаться вампиру)
#define BCF_CAN_ATTACK_WALL     0x00000020              // Катапульта. может разрушать стены
#define BCF_CANT_MOVE           0x00000040              // осадное оружие - не двигается (5508CB)
#define BCF_KING_1              0x00000080              // KING_1
#define BCF_KING_2              0x00000100              // KING_2
#define BCF_KING_3              0x00000200              // KING_3
#define BCF_MINDIMMUNITY        0x00000400              // Иммунитет к заклинаниям разума
#define BCF_NOOBSTACLEPENALTY   0x00000800              // Нет пенальти при выстреле за стены
#define BCF_NOMELEEPENALTY      0x00001000              // Нет пенальти в ближнем бою (для стрелков)
#define BCF_EMPTYFLAG           0x00002000              // В игре никогда не проверяется
#define BCF_FIREIMMUNITY        0x00004000              // имунитет к заклинаниям огня
#define BCF_DOUBLEATTACK        0x00008000              // атакует дважды
#define BCF_NORETALIATION       0x00010000              // атака без ответа
#define BCF_NOMORALE            0x00020000              // Нет пенальти морали (Элементали, Големы)
#define BCF_UNDEAD              0x00040000              // нежить
#define BCF_AROUNDATTACK        0x00080000              // Атакует всех вокруг, не работает вместе с Дыханием дракона
#define BCF_MAGOG               0x00100000              // расширенный радиус стреляющих юнитов (Магоги, Личи)
#define BCF_DIE                 0x00200000              // отряд убит
#define BCF_SUMMON              0x00400000              // отряд призван на поле боя
#define BCF_CLONE               0x00800000              // отряд является клоном (смерть с одной атаки)
#define BCF_MORALE              0x01000000              // В этом раунде битвы отряду выпала мораль
#define BCF_WAITING             0x02000000              // В этом раунде битвы отряд уже совершил некое действие
#define BCF_DONE                0x04000000              // В этом раунде битвы отряд уже совершил некое действие
#define BCF_DEFENDING           0x08000000              // Отряд стоит в защитном положении
#define BCF_SACRIFICED          0x10000000              // Флаг выставляется стэку, когда тот был принесён в Жертву
#define BCF_NOCOLORING          0x20000000              // Существа с этим флагом не меняют свой цвет при клонировании и окаменении
#define BCF_GRAY                0x40000000              // Отряд окрашен в серый цвет
#define BCF_DRAGON              0x80000000              // Дракон. На юнита с этим флагом действует Пузырёк с кровью дракона

//main def group id
#define DG_MAIN 0

// battle monsters defs groups ids
#define BMDG_MOVE 0                 // Анимация движения
#define BMDG_RANDANIM 1             // Случайная анимация, кривляние
#define BMDG_STAY 2                 // Анимация стойки
#define BMDG_DAMAGE 3               // Анимация получения повреждений
#define BMDG_DEFENCE 4              // Анимация получения повреждений в защитной стойке
#define BMDG_DEATH 5                // Анимация смерти
#define BMDG_SPEC_DEATH 6           // Особая анимация смерти (есть у Бехолдеров, Дурных Глаз, Золотых Големов, не используется)
#define BMDG_TURN_TO_RIGHT_BEGIN 7  // Анимация начала поворота вправо
#define BMDG_TURN_TO_LEFT_END 8     // Анимация конца поворота влево
#define BMDG_TURN_TO_LEFT_BEGIN 9   // Анимация начала поворота влево
#define BMDG_TURN_TO_RIGHT_END 10   // Анимация конца поворота вправо
#define BMDG_HIT_UP 11              // Анимация ближней атаки вверх
#define BMDG_HIT_STRAIGHT 12        // Анимация ближней атаки прямо
#define BMDG_HIT_DOWN 13            // Анимация ближней атаки вниз
#define BMDG_SHOT_UP 14             // Анимация дальней атаки вверх
#define BMDG_SHOT_STRAIGHT 15       // Анимация дальней атаки прямо
#define BMDG_SHOT_DOWN 16           // Анимация дальней атаки вниз
#define BMDG_CAST_UP 17             // Анимация колдовства вверх
#define BMDG_CAST_STRAIGHT 18       // Анимация колдовства прямо
#define BMDG_CAST_DOWN 19           // Анимация колдоства вниз
#define BMDG_BEGIN_MOVE 20          // Анимация начала движения
#define BMDG_END_MOVE 21            // Анимация начала движения


// ID нажатых кнопок (Virtual Keys)
#define VK_SHIFT        16
#define VK_CTRL         17
#define VK_ALT          18

#define VK_ESC          27
#define VK_ENTER        13
#define VK_SPACE        32

// ID нажатых кнопок (Hoat Key)
#define HK_ESC          1
#define HK_1            2
#define HK_2            3
#define HK_3            4
#define HK_4            5
#define HK_5            6
#define HK_6            7
#define HK_7            8
#define HK_8            9
#define HK_9            10
#define HK_0            11
#define HK_MINUS_1      12
#define HK_PLUS_1       13
#define HK_BACKSPACE    14
#define HK_CTRL         29
#define HK_LSHIFT       42
#define HK_RSHIFT       54

#define HK_ESC      1
#define HK_SPACE    57
#define HK_ALT      56
#define HK_ENTER    28

#define HK_F1       59
#define HK_F2       60
#define HK_F3       61
#define HK_F4       62
#define HK_F5       63
#define HK_F6       64
#define HK_F7       65
#define HK_F8       66
#define HK_F9       67
#define HK_F10      68
#define HK_F11      87
#define HK_F12      88
#define HK_DEL      83

#define HK_Q        16
#define HK_W        17
#define HK_E        18
#define HK_R        19
#define HK_T        20
#define HK_Y        21
#define HK_U        22
#define HK_I        23
#define HK_O        24
#define HK_P        25

#define HK_A        30
#define HK_S        31
#define HK_D        32
#define HK_F        33
#define HK_G        34
#define HK_H        35
#define HK_J        36
#define HK_K        37
#define HK_L        38

#define HK_Z        44
#define HK_X        45
#define HK_C        46
#define HK_V        47
#define HK_B        48
#define HK_N        49
#define HK_M        50

#define HK_NUM_0        82
#define HK_NUM_1        79
#define HK_NUM_2        80
#define HK_NUM_3        81
#define HK_NUM_4        75
#define HK_NUM_5        76
#define HK_NUM_6        77
#define HK_NUM_7        71
#define HK_NUM_8        72
#define HK_NUM_9        73
#define HK_NUM_PLUS     78
#define HK_NUM_MINUS    74

#define HK_ARROW_UP     72
#define HK_ARROW_DOWN   80
#define HK_ARROW_LEFT   75
#define HK_ARROW_RIGHT  77

#define HK_HOME         71

// уровень героя в опыте
#define HERO_EXPA_LVL_0 -2147483648
#define HERO_EXPA_LVL_1 0
#define HERO_EXPA_LVL_2 1000
#define HERO_EXPA_LVL_3 2000
#define HERO_EXPA_LVL_4 3200
#define HERO_EXPA_LVL_5 4600
#define HERO_EXPA_LVL_6 6200
#define HERO_EXPA_LVL_7 8000
#define HERO_EXPA_LVL_8 10000
#define HERO_EXPA_LVL_9 12200
#define HERO_EXPA_LVL_10 14700
#define HERO_EXPA_LVL_11 17500
#define HERO_EXPA_LVL_12 20600
#define HERO_EXPA_LVL_13 24320
#define HERO_EXPA_LVL_14 28784
#define HERO_EXPA_LVL_15 34140
#define HERO_EXPA_LVL_16 40567
#define HERO_EXPA_LVL_17 48279
#define HERO_EXPA_LVL_18 57533
#define HERO_EXPA_LVL_19 68637
#define HERO_EXPA_LVL_20 81961
#define HERO_EXPA_LVL_21 97949
#define HERO_EXPA_LVL_22 117134
#define HERO_EXPA_LVL_23 140156
#define HERO_EXPA_LVL_24 167782
#define HERO_EXPA_LVL_25 200933
#define HERO_EXPA_LVL_26 240714
#define HERO_EXPA_LVL_27 288451
#define HERO_EXPA_LVL_28 345735
#define HERO_EXPA_LVL_29 414475
#define HERO_EXPA_LVL_30 496963
#define HERO_EXPA_LVL_31 595948
#define HERO_EXPA_LVL_32 714730
#define HERO_EXPA_LVL_33 857268
#define HERO_EXPA_LVL_34 1028313
#define HERO_EXPA_LVL_35 1233567
#define HERO_EXPA_LVL_36 1479871
#define HERO_EXPA_LVL_37 1775435
#define HERO_EXPA_LVL_38 2130111
#define HERO_EXPA_LVL_39 2555722
#define HERO_EXPA_LVL_40 3066455
#define HERO_EXPA_LVL_41 3679334
#define HERO_EXPA_LVL_42 4414788
#define HERO_EXPA_LVL_43 5297332
#define HERO_EXPA_LVL_44 6356384
#define HERO_EXPA_LVL_45 7627246
#define HERO_EXPA_LVL_46 9152280
#define HERO_EXPA_LVL_47 10982320
#define HERO_EXPA_LVL_48 13178368
#define HERO_EXPA_LVL_49 15813625
#define HERO_EXPA_LVL_50 18975933
#define HERO_EXPA_LVL_51 22770702
#define HERO_EXPA_LVL_52 27324424
#define HERO_EXPA_LVL_53 32788890
#define HERO_EXPA_LVL_54 39346249
#define HERO_EXPA_LVL_55 47215079
#define HERO_EXPA_LVL_56 56657675
#define HERO_EXPA_LVL_57 67988790
#define HERO_EXPA_LVL_58 81586128
#define HERO_EXPA_LVL_59 97902933
#define HERO_EXPA_LVL_60 117483099
#define HERO_EXPA_LVL_61 140979298
#define HERO_EXPA_LVL_62 169174736
#define HERO_EXPA_LVL_63 203009261
#define HERO_EXPA_LVL_64 243610691
#define HERO_EXPA_LVL_65 292332407
#define HERO_EXPA_LVL_66 350798466
#define HERO_EXPA_LVL_67 420957736
#define HERO_EXPA_LVL_68 505148860
#define HERO_EXPA_LVL_69 606178208
#define HERO_EXPA_LVL_70 727413425
#define HERO_EXPA_LVL_71 872895685
#define HERO_EXPA_LVL_72 1047474397
#define HERO_EXPA_LVL_73 1256968851
#define HERO_EXPA_LVL_74 1508362195
#define HERO_EXPA_LVL_88 1810034207
#define HERO_EXPA_LVL_100 2073739175
#define HERO_EXPA_LVL_108 2100000000
#define HERO_EXPA_LVL_868 2144641867
#define HERO_EXPA_LVL_3732 2146553679
#define HERO_EXPA_LVL_5920 2146673313
#define HERO_EXPA_LVL_6424 2147293156
#define HERO_EXPA_LVL_MAX 2147400657
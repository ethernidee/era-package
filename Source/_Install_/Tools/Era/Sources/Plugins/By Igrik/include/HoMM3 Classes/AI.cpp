0x4080 : Length = 666, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_METHOD, count = 2, list = 0x4076, name = 'type_spellvalue'
	list[1] = LF_ONEMETHOD, public, VANILLA, index = 0x4077, name = 'can_cast_spells'
	list[2] = LF_ONEMETHOD, public, VANILLA, index = 0x4078, name = 'get_duration'
	list[3] = LF_ONEMETHOD, public, VANILLA, index = 0x4078, name = 'get_power'
	list[4] = LF_ONEMETHOD, public, VANILLA, index = 0x4078, name = 'get_mana'
	list[5] = LF_ONEMETHOD, public, VANILLA, index = 0x4078, name = 'get_stack_value'
	list[6] = LF_ONEMETHOD, public, VANILLA, index = 0x4070, name = 'get_best_spell_value'
	list[7] = LF_ONEMETHOD, public, VANILLA, index = 0x407A, name = 'get_value_of_increase'
	list[8] = LF_ONEMETHOD, public, VANILLA, index = 0x4067, name = 'get_raw_spell_value'
	list[9] = LF_ONEMETHOD, public, VANILLA, index = 0x407B, name = 'set_duration'
	list[10] = LF_ONEMETHOD, public, VANILLA, index = 0x407B, name = 'set_power'
	list[11] = LF_ONEMETHOD, public, VANILLA, index = 0x407B, name = 'set_mana'
	list[12] = LF_ONEMETHOD, public, VANILLA, index = 0x407B, name = 'set_stack_value'
	list[13] = LF_ONEMETHOD, protected, VANILLA, index = 0x4068, name = 'fill_creature_value_list'
	list[14] = LF_ONEMETHOD, protected, VANILLA, index = 0x4064, name = 'get_damage_spell_value'
	list[15] = LF_ONEMETHOD, protected, VANILLA, index = 0x4065, name = 'get_enchantment_value'
	list[16] = LF_ONEMETHOD, protected, VANILLA, index = 0x4065, name = 'get_mass_damage_spell_value'
	list[17] = LF_ONEMETHOD, protected, VANILLA, index = 0x4066, name = 'get_summoning_value'
	list[18] = LF_MEMBER, protected, type = 0x1AA2, offset = 0
		member name = 'our_hero'
	list[19] = LF_MEMBER, protected, type = T_LONG(0012), offset = 4
		member name = 'stack_value'
	list[20] = LF_MEMBER, protected, type = T_LONG(0012), offset = 8
		member name = 'power'
	list[21] = LF_MEMBER, protected, type = T_LONG(0012), offset = 12
		member name = 'duration'
	list[22] = LF_MEMBER, protected, type = T_LONG(0012), offset = 16
		member name = 'mana'
	list[23] = LF_MEMBER, protected, type = 0x407C, offset = 20
		member name = 'list'
	list[24] = LF_ONEMETHOD, public, VANILLA, (compgenx), index = 0x407E, name = 'operator='
	list[25] = LF_ONEMETHOD, public, VANILLA, (compgenx), index = 0x4068, name = '~type_spellvalue'
	list[26] = LF_ONEMETHOD, public, VANILLA, (compgenx), index = 0x407F, name = '__vecDelDtor'





	0x40ad : Length = 334, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_BCLASS, public, type = 0x401A, offset = 0
	list[1] = LF_METHOD, count = 4, list = 0x409D, name = 'type_AI_creature_purchaser'
	list[2] = LF_ONEMETHOD, public, VANILLA, index = 0x409F, name = 'do_purchase'
	list[3] = LF_ONEMETHOD, public, VANILLA, index = 0x40A1, name = 'get_purchase_value'
	list[4] = LF_METHOD, count = 2, list = 0x40A5, name = 'set'
	list[5] = LF_ONEMETHOD, public, VANILLA, index = 0x40A6, name = 'set_subtract_mode'
	list[6] = LF_ONEMETHOD, protected, VANILLA, index = 0x40A7, name = 'do_best_purchase'
	list[7] = LF_MEMBER, protected, type = T_LONG(0012), offset = 32
		member name = 'player_id'
	list[8] = LF_MEMBER, protected, type = T_32PLONG(0412), offset = 36
		member name = 'funds'
	list[9] = LF_MEMBER, protected, type = T_UCHAR(0020), offset = 40
		member name = 'subtract_cost_mode'
	list[10] = LF_MEMBER, protected, type = 0x40A8, offset = 44
		member name = 'creatures'
	list[11] = LF_ONEMETHOD, public, VANILLA, (compgenx), index = 0x40AA, name = 'operator='
	list[12] = LF_ONEMETHOD, public, VANILLA, (compgenx), index = 0x40AB, name = '~type_AI_creature_purchaser'
	list[13] = LF_ONEMETHOD, public, VANILLA, (compgenx), index = 0x40AC, name = '__vecDelDtor'



	0x430c : Length = 1458, Leaf = 0x1203 LF_FIELDLIST
	list[0] = LF_METHOD, count = 2, list = 0x42E7, name = 'searchArray'
	list[1] = LF_ONEMETHOD, public, VANILLA, index = 0x42E6, name = '~searchArray'
	list[2] = LF_ONEMETHOD, public, VANILLA, index = 0x42E6, name = 'Close'
	list[3] = LF_ONEMETHOD, public, VANILLA, index = 0x42E9, name = 'get_hex'
	list[4] = LF_ONEMETHOD, public, VANILLA, index = 0x42EA, name = 'get_cell'
	list[5] = LF_ONEMETHOD, public, VANILLA, index = 0x42EB, name = 'get_danger_value'
	list[6] = LF_ONEMETHOD, public, VANILLA, index = 0x42EC, name = 'get_visited_count'
	list[7] = LF_ONEMETHOD, public, VANILLA, index = 0x42ED, name = 'get_visited_cell'
	list[8] = LF_ONEMETHOD, public, VANILLA, index = 0x26E4, name = 'SeedPosition'
	list[9] = LF_ONEMETHOD, public, VANILLA, index = 0x267A, name = 'BuildPath'
	list[10] = LF_ONEMETHOD, public, VANILLA, index = 0x42E6, name = 'clear_path'
	list[11] = LF_ONEMETHOD, public, VANILLA, index = 0x42EC, name = 'get_path_steps'
	list[12] = LF_ONEMETHOD, public, VANILLA, index = 0x42EE, name = 'get_step'
	list[13] = LF_ONEMETHOD, public, VANILLA, index = 0x42EF, name = 'get_step_cell'
	list[14] = LF_ONEMETHOD, public, VANILLA, index = 0x42F0, name = 'get_travel_time'
	list[15] = LF_ONEMETHOD, public, VANILLA, index = 0x42F1, name = 'is_moat'
	list[16] = LF_ONEMETHOD, public, VANILLA, index = 0x42F2, name = 'limit_was_reached'
	list[17] = LF_ONEMETHOD, public, VANILLA, index = 0x42E6, name = 'lower_door'
	list[18] = LF_ONEMETHOD, public, VANILLA, index = 0x42F4, name = 'FindCombatPath'
	list[19] = LF_ONEMETHOD, public, VANILLA, index = 0x42F5, name = 'mark_teleport'
	list[20] = LF_ONEMETHOD, public, VANILLA, index = 0x42F7, name = 'SeedCombatPosition'
	list[21] = LF_ONEMETHOD, public, VANILLA, index = 0x40F3, name = 'set_danger_zones'
	list[22] = LF_ONEMETHOD, public, VANILLA, index = 0x42F8, name = 'set_rectangle'
	list[23] = LF_ONEMETHOD, private, VANILLA, index = 0x26A0, name = 'board_boat'
	list[24] = LF_ONEMETHOD, private, VANILLA, index = 0x42FA, name = 'build_combat_path'
	list[25] = LF_ONEMETHOD, private, VANILLA, index = 0x42FB, name = 'check_enemy_armies'
	list[26] = LF_ONEMETHOD, private, VANILLA, index = 0x26A8, name = 'check_town_portal'
	list[27] = LF_ONEMETHOD, private, VANILLA, index = 0x42FC, name = 'Clear'
	list[28] = LF_ONEMETHOD, private, VANILLA, index = 0x269E, name = 'enter_gate'
	list[29] = LF_ONEMETHOD, private, VANILLA, index = 0x26A3, name = 'enter_hostile_trigger'
	list[30] = LF_ONEMETHOD, private, VANILLA, index = 0x2686, name = 'enter_lith'
	list[31] = LF_ONEMETHOD, private, VANILLA, index = 0x26A2, name = 'enter_town'
	list[32] = LF_ONEMETHOD, private, VANILLA, index = 0x26A5, name = 'enter_trigger'
	list[33] = LF_ONEMETHOD, private, VANILLA, index = 0x42E6, name = 'Init'
	list[34] = LF_ONEMETHOD, private, VANILLA, index = 0x42FD, name = 'mark_enemy'
	list[35] = LF_ONEMETHOD, private, VANILLA, index = 0x42FE, name = 'PushCombatPoint'
	list[36] = LF_ONEMETHOD, private, VANILLA, index = 0x4300, name = 'PushPoint'
	list[37] = LF_ONEMETHOD, private, VANILLA, index = 0x4301, name = 'set_moat'
	list[38] = LF_ONEMETHOD, private, VANILLA, index = 0x4303, name = 'TestPossibleDirections'
	list[39] = LF_METHOD, count = 2, list = 0x4308, name = 'valid_move_adjacent'
	list[40] = LF_MEMBER, private, type = T_UINT4(0075), offset = 0
		member name = 'maxQueueCount'
	list[41] = LF_MEMBER, private, type = T_UCHAR(0020), offset = 4
		member name = 'pay_transition_costs'
	list[42] = LF_MEMBER, private, type = T_LONG(0012), offset = 8
		member name = 'this_turns_movement'
	list[43] = LF_MEMBER, private, type = T_LONG(0012), offset = 12
		member name = 'land_movement'
	list[44] = LF_MEMBER, private, type = T_LONG(0012), offset = 16
		member name = 'sea_movement'
	list[45] = LF_MEMBER, private, type = T_UCHAR(0020), offset = 20
		member name = 'can_summon_boat'
	list[46] = LF_MEMBER, private, type = T_UCHAR(0020), offset = 21
		member name = 'can_cast_teleport'
	list[47] = LF_MEMBER, private, type = T_UCHAR(0020), offset = 22
		member name = 'can_cast_flight'
	list[48] = LF_MEMBER, private, type = T_UCHAR(0020), offset = 23
		member name = 'can_cast_water_walk'
	list[49] = LF_MEMBER, private, type = 0x1A78, offset = 24
		member name = 'water_walk_level'
	list[50] = LF_MEMBER, private, type = 0x1A78, offset = 28
		member name = 'flight_level'
	list[51] = LF_MEMBER, private, type = T_UCHAR(0020), offset = 32
		member name = 'limit_reached'
	list[52] = LF_MEMBER, private, type = 0x267C, offset = 36
		member name = 'cellData'
	list[53] = LF_MEMBER, private, type = 0x1015, offset = 40
		member name = 'valid_rectangle'
	list[54] = LF_MEMBER, private, type = 0x4252, offset = 56
		member name = 'queue'
	list[55] = LF_MEMBER, private, type = 0x4146, offset = 68
		member name = 'result'
	list[56] = LF_MEMBER, private, type = 0x4146, offset = 80
		member name = 'visited_points'
	list[57] = LF_MEMBER, private, type = T_32PUCHAR(0420), offset = 92
		member name = 'bIsMoatSlowed'
	list[58] = LF_MEMBER, private, type = T_32PLONG(0412), offset = 96
		member name = 'danger_zones'
	list[59] = LF_ONEMETHOD, public, VANILLA, (compgenx), index = 0x430A, name = 'operator='
	list[60] = LF_ONEMETHOD, public, VANILLA, (compgenx), index = 0x430B, name = '__vecDelDtor'
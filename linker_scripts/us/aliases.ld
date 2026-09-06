/* Descriptive compatibility names are aliases only; owners remain
 * address-stable until their C implementations are byte-matched.
 *
 * This file is hand-written and tracked outside the splat-generated
 * pokestadiumgs.ld so a re-split does not silently drop it (splat rewrites
 * that file from scratch on every `splat split`). It is linked in via an
 * extra `-T` script from the Makefile, the same way hardware_regs.ld,
 * undefined_syms.ld, and the other hand-written scripts are.
 */
Audio_ThreadEntry = func_80035174;
Audio_RequestEvent = func_800355E4;
func_8005805C = GbSave_IdentifyFormat;
func_8005A228 = GbTower_PollPortState;
func_8005ADD8 = GbTower_StartPortSession;
func_8410F6AC = BattleAnim_ModelDispatch_148;
func_8412A9F4 = BattleAnim_Table_84185F10_009;
func_8413005C = BattleAnim_Table_84186004_050;
func_84131538 = BattleAnim_Table_84186004_082;
func_84115E28 = BattleAnim_Dispatch_107;
func_8412A934 = BattleAnim_Table_84185F10_008;
func_8412BFEC = BattleAnim_Table_84185F10_021;
func_8412D20C = BattleAnim_Table_84185F10_036;
func_84130B40 = BattleAnim_Table_84186004_068;
func_84113D7C = BattleAnim_Dispatch_218;
func_8412D06C = BattleAnim_Table_84185F10_035;
func_8003F3BC = ModelAnim_SetEventTrack;
func_8411D594 = BattleAnim_Dispatch_246;
func_8412D8C8 = BattleAnim_Table_84185F10_042;
func_8412E94C = BattleAnim_Table_84186004_000;
func_84110910 = BattleAnim_ModelDispatch_184;
func_84115FAC = BattleAnim_Dispatch_057;
func_84115A64 = BattleAnim_Dispatch_051;
func_8003AB68 = Geo_NodeBackground;
func_8412DBC0 = BattleAnim_Table_84185F10_045;
func_8412EFFC = BattleAnim_Table_84186004_005;
func_8003ABFC = Geo_NodeClearDepth;
func_861098CC = fragment49_main;
func_84130CE8 = BattleAnim_Table_84186004_072;
func_80040A9C = geo_layout_cmd_create_display_list_matrix;
func_8412C870 = BattleAnim_Table_84185F10_029;
func_8412DD0C = BattleAnim_Table_84185F10_048;
func_84129D8C = BattleAnim_Table_84185F10_000;
func_84130284 = BattleAnim_Table_84186004_053;
func_8410FB0C = BattleAnim_ModelDispatch_204;
func_8003FC8C = geo_layout_cmd_return;
func_80040D9C = geo_layout_cmd_set_node_flag4;
func_80040244 = geo_layout_cmd_create_light;
func_84110860 = BattleAnim_ModelDispatch_191;
func_841109FC = BattleAnim_ModelDispatch_113;
func_8410F1A8 = BattleAnim_ModelDispatch_127;

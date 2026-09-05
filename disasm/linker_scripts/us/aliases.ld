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

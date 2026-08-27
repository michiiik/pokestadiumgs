#include "global.h"


#ifdef VERSION_US
extern s32 MainPool_AllocAligned(s32, s32, s32);
extern void _bzero(s32, s32);
s32 func_80071940(s32 arg0, s32 arg1) {
    if (arg1 == 0) {
        arg1 = MainPool_AllocAligned(arg0, 0xAA8, 4);
    }
    _bzero(arg1, 0xAA8);
    return arg1;
}

extern s32 main_pool_get_available(void);
extern s32 func_8004DDF4(s32);
extern s32 func_8004DEF8(s32);
extern s32 MainPool_AllocState(s32, s32);
extern s32 WidgetTree_RunMessagePanelSilent(s32, s32);
extern void MainPool_FinalizeAllocation(s32);
void func_80071984(s32 arg0, s32 arg1) {
    s32 state;
    s32 before;
    s32 sp24;
    s32 delta;
    s32 *entry;

    before = main_pool_get_available();
    func_8004DDF4(arg1);
    entry = (s32 *)((u8 *)arg0 + (arg1 * 0xC));
    entry[1] = func_8004DEF8(arg1);
    state = MainPool_AllocState(main_pool_get_available(), 0);
    entry[0] = WidgetTree_RunMessagePanelSilent(state, arg1);
    entry[2] = before - sp24;
    MainPool_FinalizeAllocation(state);
    delta = before - main_pool_get_available();
    entry[2] = delta;
    *(s32 *)((u8 *)arg0 + 0xAA4) += delta;
}

extern void func_80071984(s32, s32);
void func_80071A40(s32 arg0, s16 *arg1) {
    s16 *ptr;

    ptr = arg1;
    while (*ptr >= 0) {
        func_80071984(arg0, *ptr);
        ptr++;
    }
}

s32 func_80071AA0(s32 arg0, s32 arg1)
{
  s32 temp_v1;
  int new_var2;
  s32 *new_var;
  if ((arg1 >= 0) && (arg1 < 0xE3))
  {
    temp_v1 = arg1 * 0xC;
    new_var = (s32 *) (((u8 *) (arg0 + temp_v1)) + 4);
    temp_v1 = *new_var;
    new_var2 = temp_v1 != 0;
    if (new_var2)
    {
      return temp_v1;
    }
  }
  return 0;
}

s32 func_80071ADC(s32 arg0, s32 arg1) {
    s32 value;

    if ((arg1 >= 0) && (arg1 < 0xE3)) {
        value = *(s32 *)((u8 *)arg0 + (arg1 * 0xC));
        if (value != 0) {
            return value;
        }
    }
    return 0;
}
#endif

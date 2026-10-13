/* Synthetic diagnostics only: these are not accepted owner replacements. */
typedef int s32;
void calibrated(s32 a, s32 b) { }
void noop_if(s32 event, s32 node) { if (event == 5) { node = node; } }
void noop_switch(s32 event, s32 node) { switch (event) { case 5: node = node; break; } }
void noop_goto(s32 event, s32 node) { if (event != 5) goto done; node = node; done:; }
s32 dense_four(s32 x) { switch (x) { case 0: return 17; case 1: return 31; case 2: return 47; case 3: return 73; default: return -1; } }
s32 dense_five(s32 x) { switch (x) { case 0: return 17; case 1: return 31; case 2: return 47; case 3: return 73; case 4: return 91; default: return -1; } }

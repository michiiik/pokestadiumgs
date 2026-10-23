# Fragment 50 auxiliary scene models

## Accepted owners (US ROM, 2026-10-24)

| Original owner | Name | Instruction bytes |
| --- | --- | ---: |
| `func_86207650` | `SceneAux_UpdatePosition` | 272 |
| `func_86207760` | `SceneAux_RenderModel` | 276 |
| `func_86207874` | `SceneAux_CreateModels` | 332 |
| `func_862079C0` | `SceneAux_LoadResources` | 184 |

All four owners are C. Their bodies total 1064 bytes. The 1072-byte original
text module also contains eight terminal zero alignment bytes, unchanged by
the compiler. The last assembly symbol counts these bytes (192 bytes); the
C function symbol counts its 184-byte body. No source padding is added.

## Recovered behavior and names

`SceneAux_UpdatePosition` handles event 2. Its callback data at node offset
20 selects one of four context positions, copied as three floats to node
position offset 36. Context offsets are 466576, 466560, 466608 and 466592
for indices 0 through 3. Y then increases by 1. An unmatched index keeps the
prior position and still increases Y. The unsigned index spelling preserves
the original event/case constant loads; the model constructor establishes
the four valid index values.

`SceneAux_RenderModel` handles event 5. It snapshots the current model from
`D_8009491C`, emits pipe synchronization, texture color with environment-
modulated texture alpha, and an environment alpha of 150. It binds segment
15 to the payload of an entry in archive 434, submits the shared display
list, then calls `GeoRender_ApplyMaterialState`.

The texture-entry selector is a four-byte table at context offset 474296.
`AuxTextureIds` represents those four entries directly, without describing
unrecovered context fields. Index selection comes from offset 20 of the
current model. The constructor writes indices 0 through 3 at model-record
offset 56, which is node offset 20 after the 36-byte record prefix.
`Geo_ProcessCallbacks` establishes `D_8009491C` while visiting children of a
model node (type 22). These producers and consumer justify the table view.
//@src/229E0.c

`SceneAux_CreateModels` makes four allocation attempts from the pool at
context offset 472380. Each successful allocation gets the position callback,
the layout result at context offset 368, its index, scale 9 on all three
axes, fixed rotation X of -14199, and rotation Y of 8192, 24576, -8192 or
-24576. Allocation failure skips that slot and continues. The callback address
is registered through the graph engine's existing callback-slot type.

`SceneAux_LoadResources` builds the geometry layout from `D_862091F0` using a
main-pool allocation state, stores the layout result, and finalizes that
allocation. It builds the shared display list from archive 434 entry 6 with
float arguments 0 and -12 and segment address `0x0F000000`. It initializes a
four-item pool using context offsets 472380 and 472400, then creates the
models. These data flow relationships establish the auxiliary-model names;
no specific visual identity for the models has been inferred.

## Source mechanisms and verification

- The position callback uses a four-case switch, aggregate three-float copies
  and an unsigned callback index. All vector fields are consumed.
- The renderer uses ordinary SDK display-list macros. A four-entry byte-array
  view preserves the original context/index load ordering; simpler byte-
  pointer expressions swapped three register operands despite matching the
  normalized opcode sequence. The complete ROM gate accepted the array view.
- Model construction uses a normal four-iteration loop and switch. Callee
  signatures retain the actual pointer/integer return and argument types from
  `src/229E0.c`, `src/3A00.c`, `src/4CC20.c` and fragment 64.
- Normal native `make COMPARE=1 RUN_CC_CHECK=1` passes with retail US ROM MD5
  `1561c75d11cedf356a8ddb1a4a5f9d5d`. The named source, consolidated declarations and
  texture-table typedef also pass a fresh ordinary ROM gate.
- Complete module section bytes, semantic relocations, function offsets,
  linked fragment 50 and collateral objects are checked against the assembly
  baseline. The eight-byte terminal symbol-size difference is metadata only.

Coverage is generated separately. No private diagnostic scripts or binary
artifacts accompany the source batch.

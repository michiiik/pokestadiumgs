# Region notes: fragment44_2030B0

## func_8AF154EC: 24-by-24 texture rectangle

The first candidate matches all 38 original words without a stack frame. The original `func_8AF15584` caller supplies two word coordinates computed from its signed halfword origins and word loop offsets, then ignores the result. The owner emits a texture rectangle ending at each supplied coordinate plus 24 and advances the display-list pointer by three command packets.

Use the standard `gSPTextureRectangle` macro in `lib/ultralib/include/PR/gbi.h`: coordinates shift by two into the 12-bit fields, tile is `G_TX_RENDERTILE`, texture coordinates are zero, and both texture increments are 1024. The existing global storage is declared `Gfx *D_800D0510`. No helper, caller or existing initializer body changes.

The full retained session notes/checkpoints and matching history were consulted. At fleet main `afee707ab78d3f63f2f9deeadc7551ec0080eeed`, the exact owner record and `2030B0` regional catalog are absent, so no owner-specific historical normalized/raw_similarity_score exists. The independently verified 20-by-20 sibling `func_8AF0B724` supplies the same command-packing model with a different rectangle extent.

On master `02680d84f35653f10181e17f52c589d27a97d468` with the verified `func_8AF0B724` from PR #1155 retained, the US `make rom COMPARE=1 -j2` build and per-object host checks pass. Explicit `md5sum -c baseroms/us/checksum.md5` passes with retail MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`; all 427 host syntax checks pass. No FAKE code, semantic renaming, known-token updates, padding, or authored CI/compiler/tool/layout/data/verification changes.

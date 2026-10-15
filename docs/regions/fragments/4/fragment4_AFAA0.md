# fragment4_AFAA0 matching notes

## func_81802438

One independent 30-word leaf now uses the standard gSPDisplayList macro. Its signed byte at offset 9 selects the existing display list D_81805940 for case 1 or D_81805960 for case 2. Other values emit nothing. Original data contains the two genuine four-command display lists; no data or layout was changed. The owner reads only its incoming word address and has no consumed result. No padding or shared switch tail is involved.

The definition retains the existing word-address calling convention. The same-file forward declaration is narrowed from unspecified parameters to one word, and func_81802BAC now passes its real first word explicitly without the unused second argument. Its later calls continue using both original inputs. func_81802CA8 already supplies one word. All compiled caller bytes remain retail-identical in the full build.

The first switch/macro recipe passes the full US make rom COMPARE=1 build with default host syntax checks and md5sum -c baseroms/us/checksum.md5: 1561c75d11cedf356a8ddb1a4a5f9d5d. No semantic names, new fakes, invented formals, CI, compiler or verification changes were introduced. The Public PR ROM Gate must independently validate the current head/merge result before merge.

Fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed has no exact owner attempt, reference or historical normalized/raw score for this function. Full regional notes retain func_818021B4 at normalized/raw 0.8095/0.7619 after eight guard variants, and func_81803558 at 0.9265/0.7794 with its actual float ABI prerequisite. Neither exhausted family was retried. Current master has no earlier regional note here. Every open PR scope was inspected; foreign fragment 13 owners/layout remain deferred.

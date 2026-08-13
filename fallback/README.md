# Stadium 2 working fallback

This directory records the last device-validated Stadium 2 Android build. The
APK itself is ignored by Git because APKs are build artifacts; keep the local
file alongside this record.

## APK

`pokemon-stadium-2-turnip-working-fallback-2026-08-13.apk`

- package: `com.pokemonstadium2recomp`
- size: `70,729,744` bytes
- SHA-256: `851136118F494C89199FCE82BEAFEB98BCB0BD9ABC7F7CA94DFB1A45AAA1A2C7`
- native payload: `libmain.so`, `libmain_hook.so`,
  `libfile_redirect_hook.so`, `libgsl_alloc_hook.so`, and `libhook_impl.so`

## Restore to Thor

```powershell
$adb = 'C:\Users\Michael\AppData\Local\Android\Sdk\platform-tools\adb.exe'
& $adb -s 3c43878a install -r .\fallback\pokemon-stadium-2-turnip-working-fallback-2026-08-13.apk
& $adb -s 3c43878a shell am force-stop com.pokemonstadium2recomp
& $adb -s 3c43878a shell monkey -p com.pokemonstadium2recomp 1
```

The validated launch log showed `Custom Vulkan driver active: Mesa Turnip`
on the Thor Adreno 740, and the selection screen rendered at about 39 FPS.
Audio initialized through AAudio. Do not replace this APK with a newly built
APK unless the replacement has been tested on the device.

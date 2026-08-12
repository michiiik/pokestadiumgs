param(
    [string]$AndroidSdk = "C:\projects\ddd-dl\.android-sdk",
    [string]$AndroidNdk = "C:\tmp\psr-android-deps\ndk\android-ndk-r27c",
    [string]$JavaHome = "C:\Users\laptop\.jdks\ms-17.0.17",
    [string]$Gradle = "C:\Users\laptop\.gradle\wrapper\dists\gradle-8.9-bin\90cnw93cvbtalezasaz0blq0a\gradle-8.9\bin\gradle.bat"
)

$requiredPaths = @($AndroidSdk, $AndroidNdk, $JavaHome, $Gradle)
foreach ($requiredPath in $requiredPaths) {
    if (-not (Test-Path -LiteralPath $requiredPath)) {
        throw "Required Android build dependency not found: $requiredPath"
    }
}

$androidRoot = (Resolve-Path (Join-Path $PSScriptRoot "..\android")).Path
$env:JAVA_HOME = $JavaHome
$env:ANDROID_HOME = $AndroidSdk
$env:ANDROID_SDK_ROOT = $AndroidSdk

& $Gradle --no-daemon --project-dir $androidRoot :app:assembleDebug "-PndkPath=$AndroidNdk"
if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

$apk = Join-Path $androidRoot "app\build\outputs\apk\debug\app-debug.apk"
if (-not (Test-Path -LiteralPath $apk)) {
    throw "Gradle reported success but the APK was not produced: $apk"
}

Write-Host "Android ARM64 probe built: $apk"
Get-FileHash -Algorithm SHA256 -LiteralPath $apk

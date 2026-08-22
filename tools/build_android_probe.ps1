param(
    [string]$AndroidSdk = "C:\Users\Michael\AppData\Local\Android\Sdk",
    [string]$AndroidNdk = "C:\Users\Michael\AppData\Local\Android\Sdk\ndk\27.2.12479018",
    [string]$JavaHome = "C:\Program Files\Java\jdk-17.0.2",
    [string]$Gradle = "C:\Users\Michael\.gradle\wrapper\dists\gradle-8.9-bin\90cnw93cvbtalezasaz0blq0a\gradle-8.9\bin\gradle.bat"
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

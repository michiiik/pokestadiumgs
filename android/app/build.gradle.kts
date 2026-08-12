plugins {
    id("com.android.application")
}

dependencies {
    implementation("androidx.drawerlayout:drawerlayout:1.2.0")
}

val repoRoot = rootDir.parentFile
val stadium1Root = repoRoot.parentFile.resolve("PokemonStadiumRecomp")
val stagedGameAssetsDir = layout.buildDirectory.dir("generated/game-assets")

android {
    namespace = "com.pokemonstadiumrecomp.probe"
    compileSdk = 35

    defaultConfig {
        applicationId = "com.pokemonstadium2recomp"
        minSdk = 26
        targetSdk = 35
        versionCode = 1
        versionName = "0.1"

        ndk {
            abiFilters += "arm64-v8a"
        }
    }

    sourceSets["main"].java.srcDir(
        stadium1Root.resolve("lib/SDL2/android-project/app/src/main/java")
    )
    sourceSets["main"].java.srcDir(
        stadium1Root.resolve("android/app/src/main/java")
    )
    sourceSets["main"].java.srcDir(
        stadium1Root.resolve("android/app/build/generated/source/companion")
    )
    sourceSets["main"].assets.srcDir(stagedGameAssetsDir)

    packaging {
        jniLibs {
            useLegacyPackaging = true
        }
    }
}

val stageGameAssets = tasks.register("stageGameAssets") {
    val outputDir = stagedGameAssetsDir.get().asFile
    outputs.dir(outputDir)

    doLast {
        delete(outputDir)
        copy {
            from(stadium1Root.resolve("assets"))
            into(outputDir.resolve("assets"))
        }
        copy {
            from(repoRoot.resolve("baserom.z64"))
            into(outputDir)
        }
    }
}

tasks.named("preBuild") {
    dependsOn(stageGameAssets)
}

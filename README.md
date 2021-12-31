# このプロジェクトについて

このプロジェクトは、 CMake で自動生成したソースファイルを扱うための仕組みを含むサンプルプロジェクトです。

## 使い方

macOS 環境:
```sh
cd /path/to/develop
git clone https://github.com/hotwatermorning/CMakeAutoGenTest.git
cd CMakeAutoGenTest
cmake . -B Build -G Xcode
open ./Build/CMakeAutoGenTestProject.xcodeproj
```

Xcode 上で AutoGenTest や CompileSchema ターゲットをビルドする際、必要なタイミング（初回ビルド時や .proto ファイルが変更されたときなど）でだけ CompileSchema ターゲットで protoc コマンドが実行される。


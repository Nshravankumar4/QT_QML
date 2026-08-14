# Qt Minimal Interview Project

This is a minimal and clean Qt 5.15.2 project for interview setup verification.

## Current project scope

- One C++ entry file.
- One QML screen.
- One button and one label.
- No networking code.
- No serial code.
- No model/controller files.

## Project files

- `CMakeLists.txt`
- `src/main.cpp`
- `qml/main.qml`
- `qml/qml.qrc`

## Required environment

- Qt 5.15.2 MSVC2019 64-bit
- CMake 3.19+
- Visual Studio 2019 Build Tools (or VS 2019)

## Build and run (PowerShell)

```powershell
cmake -S . -B build-qt5-vs -G "Visual Studio 16 2019" -A x64 -DCMAKE_PREFIX_PATH="C:/Qt/5.15.2/msvc2019_64"
cmake --build build-qt5-vs --config Debug
./build-qt5-vs/Debug/QtInterviewPrep.exe
```

## Qt Creator quick setup

1. Open this folder in Qt Creator.
2. Select kit: Desktop Qt 5.15.2 MSVC2019 64-bit.
3. Configure and run target `QtInterviewPrep`.

If include errors appear in editor, re-run CMake configure once with the correct kit.

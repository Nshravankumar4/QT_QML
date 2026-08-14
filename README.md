# Qt Interview Prep Project

This is a practical Qt/QML + C++ project scaffold for interview preparation.

## What this project demonstrates

- Qt Quick / QML UI with custom reusable components.
- Modern C++ backend classes connected to QML.
- QAbstractListModel based task board (common interview topic).
- TCP and UDP client basics using Qt Network.
- Serial port enumeration/open/close using Qt Serial Port.
- CMake-based Qt project setup suitable for Qt Creator.

## Recommended setup

1. Install Qt 5.15.2 MSVC2019 64-bit with these components:
   - Qt Quick
   - Qt Quick Controls 2
   - Qt Network
   - Qt Serial Port (optional: project still builds without it)
   - CMake toolchain
2. Install Qt Creator.
3. Open this folder as a CMake project in Qt Creator.
4. Configure and run target `QtInterviewPrep`.

### If configuration fails in Qt Creator (Qt 5.15.2)

- Ensure you selected Qt kit: Desktop Qt 5.15.2 MSVC2019 64-bit.
- In Qt Creator, verify that CMake shows a valid `CMAKE_PREFIX_PATH` pointing to your Qt installation.
- If needed, set `Qt5_DIR` manually to: `C:/Qt/5.15.2/msvc2019_64/lib/cmake/Qt5`.
- If your machine uses CMake 3.19.x, this project is compatible.

## Build from terminal (Windows PowerShell)

```powershell
cmake -S . -B build-qt5-vs -G "Visual Studio 16 2019" -A x64 -DCMAKE_PREFIX_PATH="C:/Qt/5.15.2/msvc2019_64"
cmake --build build-qt5-vs --config Debug
./build-qt5-vs/Debug/QtInterviewPrep.exe
```

## Interview practice tasks (do these one by one)

1. Add reconnection logic for TCP with max retry count and backoff.
2. Parse incoming JSON telemetry and bind to a new QML chart/table view.
3. Add unit tests for `TaskModel` add/remove behavior.
4. Refactor `NetworkManager` into interface + implementation for easier testing.
5. Implement message framing protocol for TCP (length-prefixed packets).
6. Add a serial read loop and parse line-delimited sensor frames.
7. Add keyboard shortcuts and a command palette style popup in QML.
8. Add logging categories and runtime log-level switch from UI.
9. Create a simple plugin-like module boundary using CMake targets.
10. Write a short design doc: architecture, threading, and error handling.

## Suggested interview talking points

- Why use `QAbstractListModel` instead of plain JS arrays in QML.
- How signals/slots bridge C++ and QML safely.
- Threading model: GUI thread vs worker thread for I/O.
- Why CMake target modularity matters in team-scale Qt projects.
- How you would mentor junior devs through code review and ownership.

# Qt Minimal Interview Project

This is a minimal and clean Qt 5.15.2 project demonstrating **Qt/QML and C++ communication**.

Perfect for interview preparation! Each file has clear comments explaining the flow.

---

## 📋 What This Project Shows

### Core Concepts Demonstrated:
1. **QObject & Meta-Object System** — Qt's reflection/introspection system
2. **Q_INVOKABLE** — Exposing C++ methods to QML
3. **Context Properties** — Registering C++ objects in QML
4. **Signal/Slot Communication** — Event handling between QML and C++
5. **Parent-Child Ownership** — Qt's memory management model
6. **QML Layout System** — ColumnLayout for UI arrangement
7. **Qt Resource System (qrc)** — Loading QML files from resources

---

## 📁 Project Structure

```
qt_interview_prep/
├── CMakeLists.txt           # Build configuration (CMake)
├── src/
│   ├── main.cpp             # Application entry point (10 steps)
│   ├── backend.h            # C++ classes exposed to QML (2 classes)
│   └── backend.cpp          # Implementation (4 functions)
├── qml/
│   ├── main.qml             # UI layout (8 components)
│   └── qml.qrc              # QML resource file
└── README.md                # This file
```

---

## 🎯 Current Project Scope

- **1 C++ entry file** (`main.cpp`) — 10 commented steps
- **2 QML backend classes** (`Backend`, `Backend_Next`)
- **1 QML screen** (`main.qml`) — 2 buttons + 1 label
- **Minimal** — No networking, serial, or database code
- **Interview-Ready** — Numbered comments in every file

---

## 🛠️ Required Environment

| Requirement | Version |
|---|---|
| Qt Framework | 5.15.2 MSVC2019 64-bit |
| CMake | 3.19+ |
| Visual Studio | 2019 Build Tools (or full VS 2019) |

---

## 🚀 Build and Run — PowerShell

**Step 1: Configure the project**
```powershell
cmake -S . -B build-qt5-vs -G "Visual Studio 16 2019" -A x64 -DCMAKE_PREFIX_PATH="C:/Qt/5.15.2/msvc2019_64"
```

**Step 2: Build the project**
```powershell
cmake --build build-qt5-vs --config Debug
```

**Step 3: Run the executable**
```powershell
./build-qt5-vs/Debug/QtInterviewPrep.exe
```

---

## 💡 How It Works

### Flow: Button Click → C++ Execution

1. **User clicks button** in QML UI
2. **QML signal triggered** (`onClicked`)
3. **QML calls C++ method** (e.g., `backend.showMessage()`)
4. **Qt meta-object system** marshals the call
5. **C++ function executes** (`Backend::showMessage()`)
6. **qDebug() outputs** to console

### Example:
```
User clicks "Call C++ Function" button
  ↓
main.qml: onClicked { backend.showMessage() }
  ↓
Qt meta-object system (MOC)
  ↓
C++: Backend::showMessage() executes
  ↓
Console: "Backend Function Called"
```

---

## 📖 Learning Sequence (Read in This Order)

For interview preparation, understand the code in this order:

1. **`src/backend.h`** (2 min)
   - Understand QObject inheritance
   - Learn Q_OBJECT macro purpose
   - See Q_INVOKABLE syntax

2. **`src/backend.cpp`** (3 min)
   - Constructor initialization lists
   - Parent-child relationships
   - Function implementations

3. **`src/main.cpp`** (5 min) — **Most Important**
   - Application initialization
   - QML engine creation
   - Context property registration (Step 4, 6)
   - Event loop startup

4. **`qml/main.qml`** (3 min)
   - UI layout structure
   - Button click handlers
   - C++ object access from QML

---

## 🎓 Qt Creator Setup

### Method 1: GUI (Easiest)
1. Open Qt Creator
2. **File → Open File or Project**
3. Select this folder
4. Select kit: **Desktop Qt 5.15.2 MSVC2019 64-bit**
5. Click **Configure** (CMake setup runs)
6. **Build → Run** (or press Ctrl+R)

### Method 2: Command Line
```powershell
# From project root directory
cmake -S . -B build-qt5-vs -G "Visual Studio 16 2019" -A x64 -DCMAKE_PREFIX_PATH="C:/Qt/5.15.2/msvc2019_64"
cmake --build build-qt5-vs --config Debug
./build-qt5-vs/Debug/QtInterviewPrep.exe
```

---

## 🐛 Troubleshooting

| Issue | Solution |
|---|---|
| **CMake errors** | Verify `CMAKE_PREFIX_PATH` points to Qt 5.15.2 |
| **Include errors in editor** | Re-run CMake configure in Qt Creator |
| **Build fails** | Check Visual Studio 2019 Build Tools are installed |
| **qrc file not found** | Ensure `AUTORCC` is enabled in CMakeLists.txt |
| **No console output** | Check Qt Creator's "Application Output" pane |

---

## 📚 Key Qt Concepts

### Q_OBJECT Macro
Enables the Meta-Object Compiler (MOC) to generate code for:
- Signals and slots
- Properties (Q_PROPERTY)
- Method invocation (Q_INVOKABLE)

### Context Properties
Makes C++ objects accessible in QML:
```cpp
engine.rootContext()->setContextProperty("backend", &backend);
// Now in QML: backend.showMessage() works
```

### Parent-Child Ownership
Qt's memory management:
- Parent automatically deletes children on destruction
- No manual `delete` needed for child objects
- Pass `parent` to constructor for automatic cleanup

### Q_INVOKABLE
Marks C++ methods callable from QML:
```cpp
Q_INVOKABLE void showMessage();  // QML can call this
```

---

## ✅ Interview Talking Points

1. **"Explain how QML calls C++ functions"**
   - Q_INVOKABLE marks methods as callable
   - Context properties expose objects to QML
   - Qt's meta-object system marshals calls

2. **"How is memory managed?"**
   - Parent-child relationships
   - Constructors pass parent parameter
   - Qt automatically deletes children

3. **"What's the purpose of Q_OBJECT?"**
   - Enables Meta-Object Compiler (MOC)
   - Provides signal/slot mechanism
   - Enables property system and introspection

4. **"Walk me through a button click"**
   - Button click triggers `onClicked` signal
   - Signal calls C++ method via context property
   - Meta-object system executes the function
   - Return value comes back to QML

---

## 📝 File Descriptions

| File | Lines | Purpose |
|---|---|---|
| `CMakeLists.txt` | 30 | Build configuration, compiler flags, linking |
| `src/main.cpp` | 43 | App initialization, QML engine, event loop |
| `src/backend.h` | 36 | 2 QObject classes, Q_INVOKABLE methods |
| `src/backend.cpp` | 36 | Constructor implementations, method bodies |
| `qml/main.qml` | 80 | Window, layout, buttons, label, signal handlers |
| `qml/qml.qrc` | 5 | Qt Resource System file mappings |

---

**Ready for interviews! Each file has numbered comments explaining every step.** 🚀

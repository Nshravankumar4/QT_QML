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
8. **Q_PROPERTY and QML Binding** — Automatic UI updates from C++ data
9. **QObject Ownership and Lifetime** — Parent-child cleanup and `deleteLater()`

---

## 📁 Project Structure

```
qt_interview_prep/
├── CMakeLists.txt           # Build configuration (CMake)
├── src/
│   ├── main.cpp             # Application entry point (10 steps)
│   ├── backend.h            # C++ classes exposed to QML (2 classes)
│   └── backend.cpp          # Implementation (4 functions)
│   ├── signal_slot_demo.h   # Dedicated signals and slots class
│   └── signal_slot_demo.cpp # connect(), emit, and C++ slot implementation
│   ├── vehicle_data.h        # Q_PROPERTY declaration and accessors
│   └── vehicle_data.cpp      # Property setter, getter, and NOTIFY signal
│   ├── ownership_demo.h       # QObject ownership and QPointer example
│   └── ownership_demo.cpp     # Child creation and deleteLater() logic
├── qml/
│   ├── main.qml             # UI layout (8 components)
│   └── qml.qrc              # QML resource file
└── README.md                # This file
```

---

## 🎯 Current Project Scope

- **1 C++ entry file** (`main.cpp`) — 10 commented steps
- **3 C++ QObject classes** (`Backend`, `Backend_Next`, `SignalSlotDemo`)
- **1 Q_PROPERTY data class** (`VehicleData`)
- **1 QObject ownership class** (`OwnershipDemo`)
- **1 dedicated signals and slots example** — C++ signal, C++ slot, and QML handler
- **1 QML screen** (`main.qml`) — 4 buttons + 2 labels
- **Ownership controls** — create a parent-owned child and schedule its deletion
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

### Flow: Signals and Slots Example

The third button demonstrates a separate `SignalSlotDemo` class:

1. QML calls `signalSlotDemo.triggerSignal()` through `Q_INVOKABLE`
2. C++ emits `messageChanged(QString)` with `emit`
3. `QObject::connect()` delivers the signal to the C++ `handleMessage()` slot
4. QML `Connections` receives `onMessageChanged(messageText)`
5. The QML label displays the received message

```text
QML button
   ↓
Q_INVOKABLE triggerSignal()
   ↓
emit messageChanged(text)
   ├── C++ handleMessage(text) slot → console output
   └── QML onMessageChanged(text) → label update
```

### Flow: Q_PROPERTY and QML Binding Example

1. QML reads `vehicleData.speed`
2. The user clicks **Increase Speed**
3. QML calls `vehicleData.increaseSpeed()`
4. C++ calls `setSpeed()` and changes `m_speed`
5. C++ emits `speedChanged()`
6. QML automatically reevaluates the binding and updates the speed label

```text
QML text: "Speed: " + vehicleData.speed
      ↑
   speedChanged()
      ↑
setSpeed(newSpeed) <- increaseSpeed()
```

### Flow: QObject Ownership Example

1. QML calls `ownershipDemo.createChild()`
2. C++ creates `new QObject(this)`
3. `this` becomes the child's parent and owner
4. QML calls `ownershipDemo.scheduleChildDeletion()`
5. C++ calls `deleteLater()` so deletion occurs through the event loop
6. `QPointer` becomes null when the child is destroyed

```text
OwnershipDemo parent
   |
   | owns lifetime
   v
QObject child
   |
   | deleteLater()
   v
Deleted safely by Qt event loop
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

5. **`src/signal_slot_demo.h`** (5 min)
   - `signals:` and `public slots:` sections
   - Signal parameters
   - Difference between a signal, slot, and `Q_INVOKABLE`

6. **`src/signal_slot_demo.cpp`** (5 min)
   - Typed `QObject::connect()` syntax
   - `emit` and one-to-many delivery
   - C++ slot execution

7. **Signals and Slots in `qml/main.qml`** (5 min)
   - `Connections` and `target`
   - `onMessageChanged` naming convention
   - C++ to QML communication

8. **`src/vehicle_data.h`** (5 min)
   - `Q_PROPERTY` syntax
   - READ, WRITE, and NOTIFY sections
   - Getter, setter, and change signal

9. **`src/vehicle_data.cpp`** (5 min)
   - Avoiding unnecessary signal emission
   - Updating the backing member
   - Calling the setter from a QML-invokable method

   10. **`src/ownership_demo.h`** (5 min)
      - Parent-child ownership
      - `QPointer` for observing QObject lifetime
      - QML-invokable ownership operations

   11. **`src/ownership_demo.cpp`** (5 min)
      - `new QObject(this)` ownership transfer
      - `deleteLater()` and the event loop
      - Null checks before using an object

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

### Signals and Slots

The dedicated class contains all the basic interview elements:

```cpp
signals:
   void messageChanged(const QString &message);

public slots:
   void handleMessage(const QString &message);
```

The signal announces that a message is available. The slot handles the message. `connect()` links
them, and `emit` sends the signal:

```cpp
QObject::connect(
   this,
   &SignalSlotDemo::messageChanged,
   this,
   &SignalSlotDemo::handleMessage);

emit messageChanged(QStringLiteral("Signal received successfully"));
```

QML receives the same signal with `Connections`:

```qml
Connections {
   target: signalSlotDemo

   function onMessageChanged(messageText) {
      message.text = messageText
   }
}
```

### Q_PROPERTY and QML Binding

The `VehicleData` class exposes a C++ property to QML:

```cpp
Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
```

- `READ speed`: QML reads the value using `speed()`
- `WRITE setSpeed`: QML can write the value using `setSpeed()`
- `NOTIFY speedChanged`: QML bindings refresh when the value changes

QML creates a binding instead of copying the value:

```qml
Label {
   text: "Speed: " + vehicleData.speed + " km/h"
}
```

When `setSpeed()` changes the value, it emits `speedChanged()`. QML then reevaluates the binding
automatically.

### QObject Ownership and Lifetime

The `OwnershipDemo` class creates a child with the parent argument:

```cpp
m_child = new QObject(this);
```

Qt automatically destroys the child when its parent is destroyed. For event-loop-safe deferred
cleanup, the example uses:

```cpp
m_child->deleteLater();
```

`QPointer<QObject>` is a guarded pointer. It automatically becomes `nullptr` when the observed
QObject is destroyed, helping prevent use-after-free access.

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

5. **"Explain signals and slots"**
   - A signal announces that an event occurred
   - A slot or QML handler responds to the event
   - `QObject::connect()` creates the relationship
   - `emit` sends the signal and its parameters

6. **"What is the difference between Q_INVOKABLE, a signal, and a slot?"**
   - `Q_INVOKABLE`: QML can call the C++ method
   - Signal: C++ announces an event
   - Slot: C++ function handles an event

7. **"What is QML Connections?"**
   - It listens to signals from a target QObject
   - `onMessageChanged` runs when the C++ signal is emitted

8. **"What is Q_PROPERTY?"**
   - It exposes a C++ value through Qt's meta-object system
   - READ identifies the getter
   - WRITE identifies the setter
   - NOTIFY identifies the change signal

9. **"What is QML binding?"**
   - A binding is an expression that stays connected to its dependencies
   - When `speedChanged()` is emitted, the speed label updates automatically

10. **"Why check whether the value changed in the setter?"**
    - It avoids unnecessary signal emissions
    - It prevents unnecessary QML binding reevaluation

11. **"How does QObject parent-child ownership work?"**
   - A parent owns its child QObject
   - Qt destroys children automatically when the parent is destroyed
   - Passing `this` as the parent establishes the relationship

12. **"Why use deleteLater()?"**
   - It schedules deletion through the event loop
   - It avoids destroying an object immediately while it may still be processing an event

13. **"What is QPointer?"**
   - It observes a QObject without owning it
   - It becomes null automatically when the QObject is destroyed

---

## 📝 File Descriptions

| File | Lines | Purpose |
|---|---|---|
| `CMakeLists.txt` | 30 | Build configuration, compiler flags, linking |
| `src/main.cpp` | 43 | App initialization, QML engine, event loop |
| `src/backend.h` | 36 | 2 QObject classes, Q_INVOKABLE methods |
| `src/backend.cpp` | 36 | Constructor implementations, method bodies |
| `src/signal_slot_demo.h` | 30 | Dedicated signal, slot, and Q_INVOKABLE declaration |
| `src/signal_slot_demo.cpp` | 25 | `connect()`, `emit`, and slot implementation |
| `src/vehicle_data.h` | 30 | `Q_PROPERTY`, getter, setter, and NOTIFY signal |
| `src/vehicle_data.cpp` | 25 | Property update logic and QML-invokable method |
| `src/ownership_demo.h` | 30 | QObject ownership, QPointer, and invokable methods |
| `src/ownership_demo.cpp` | 40 | Child creation, null checks, and deleteLater() |
| `qml/main.qml` | 80 | Window, layout, buttons, label, signal handlers |
| `qml/qml.qrc` | 5 | Qt Resource System file mappings |

---

**Ready for interviews! Each file has numbered comments explaining every step, including a separate
Signals and Slots example.** 🚀

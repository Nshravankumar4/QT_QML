# Qt Interview Prep — Complete Explanation

This document explains **every line** of your Qt 5.15 + QML project for interview preparation.

---

## 📊 Project Overview

Your project demonstrates **Qt/QML and C++ communication** with the following key files:

```text
QtInterviewPrep/
├── CMakeLists.txt              ← Build configuration (30 lines)
├── src/
│   ├── main.cpp                ← Application entry point (43 lines, 10 steps)
│   ├── backend.h               ← C++ classes (36 lines, 2 classes)
│   └── backend.cpp             ← Implementation (36 lines, 4 functions)
│   ├── signal_slot_demo.h      ← Dedicated signal/slot class
│   └── signal_slot_demo.cpp    ← connect(), emit, and slot implementation
│   ├── vehicle_data.h           ← Q_PROPERTY declaration and accessors
│   └── vehicle_data.cpp         ← Property update and NOTIFY signal
│   ├── ownership_demo.h         ← QObject ownership and QPointer declaration
│   └── ownership_demo.cpp       ← Child creation and deleteLater() logic
├── qml/
│   ├── main.qml                ← User interface (80 lines, 8 components)
│   └── qml.qrc                 ← Qt Resources (5 lines)
└── README.md                   ← Setup guide
```

---

## 🎯 Learning Path for Interviews

Read the files in this order:

1. **CMakeLists.txt** (5 min) — Understand build process
2. **src/backend.h** (3 min) — Learn C++ classes & Q_OBJECT
3. **src/backend.cpp** (3 min) — See implementations
4. **src/main.cpp** (5 min) — **Most important** — App initialization
5. **qml/main.qml** (3 min) — QML UI & signal handlers
6. **src/signal_slot_demo.h** (5 min) — signal, slot, and Q_INVOKABLE declaration
7. **src/signal_slot_demo.cpp** (5 min) — connect(), emit, and slot execution
8. **src/vehicle_data.h** (5 min) — Q_PROPERTY, READ, WRITE, and NOTIFY
9. **src/vehicle_data.cpp** (5 min) — getter, setter, change signal, and binding update
10. **src/ownership_demo.h** (5 min) — parent-child ownership and QPointer
11. **src/ownership_demo.cpp** (5 min) — child creation and deleteLater()

Total: ~50 minutes to master this project

---

# QObject Ownership and Lifetime — New Dedicated Class

The project now contains `OwnershipDemo` for object lifetime concepts:

```text
src/ownership_demo.h    - QObject ownership API and QPointer member
src/ownership_demo.cpp  - child creation and deferred deletion
```

## Complete flow

```text
QML calls createChild()
    ↓
m_child = new QObject(this)
    ↓
OwnershipDemo owns child lifetime
    ↓
QML calls scheduleChildDeletion()
    ↓
m_child->deleteLater()
    ↓
Qt event loop safely destroys child
```

## Code topics to understand

### 1. Parent-child ownership

```cpp
m_child = new QObject(this);
```

Passing `this` as the parent means Qt adds the child to the parent's object tree. When the parent
is destroyed, Qt automatically destroys the child.

### 2. Why the child is not manually deleted

The parent owns the child. Calling `delete` manually would create a dangerous ownership pattern.
Use the parent-child relationship for normal cleanup.

### 3. `deleteLater()`

```cpp
m_child->deleteLater();
```

This posts a deferred deletion event. Qt destroys the object when control returns to the event loop,
which is safer when the object may currently be processing an event.

### 4. `QPointer`

```cpp
QPointer<QObject> m_child;
```

`QPointer` is a non-owning guarded pointer. When the QObject is destroyed, Qt automatically changes
the pointer to `nullptr`.

### 5. Stack and heap lifetime

The `OwnershipDemo` object is created on the stack in `main.cpp`, so it is destroyed when `main()`
exits. Its heap child is destroyed automatically as part of the parent's destruction.

### 6. Null checks

The example checks `m_child` before creating or deleting it. This avoids duplicate creation and
prevents dereferencing a null pointer.

## Correct interview topics to cover

1. QObject parent-child ownership
2. Automatic child destruction
3. Stack object versus heap child object
4. Why owning raw pointers are dangerous without a parent
5. `deleteLater()` and the event loop
6. `QPointer` versus a raw non-owning pointer
7. Null checks and object lifetime
8. Context-property lifetime in QML
9. QML-owned versus C++-owned objects
10. Thread affinity and deleting objects in the correct thread
11. `QObject::destroyed` signal
12. Avoiding use-after-free and double deletion

## Most important interview answer

> In Qt, a QObject parent owns its children. When the parent is destroyed, Qt automatically deletes
> the children. `deleteLater()` schedules safe deferred deletion through the event loop, and
> `QPointer` becomes null automatically when the observed QObject is destroyed.

---

# Q_PROPERTY and QML Binding — New Dedicated Class

The project now contains a separate `VehicleData` class for this topic:

```text
src/vehicle_data.h    - Q_PROPERTY declaration, getter, setter, and signal
src/vehicle_data.cpp  - property update logic and QML-invokable method
```

## Complete flow

```text
QML binding reads vehicleData.speed
        ↑
speedChanged() notifies QML
        ↑
setSpeed(newSpeed) changes m_speed
        ↑
increaseSpeed() is called by QML
```

## Code topics to understand

### 1. `Q_PROPERTY`

```cpp
Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
```

This exposes `speed` to Qt's Meta-Object System and makes it available to QML.

### 2. `READ`

`READ speed` tells Qt to call `int speed() const` when QML reads `vehicleData.speed`.

### 3. `WRITE`

`WRITE setSpeed` tells Qt to call `void setSpeed(int speed)` when the property is assigned a new
value.

### 4. `NOTIFY`

`NOTIFY speedChanged` identifies the signal that tells QML the property value changed. QML bindings
are reevaluated after this signal is emitted.

### 5. Getter and backing member

```cpp
int VehicleData::speed() const
{
    return m_speed;
}
```

`m_speed` stores the value, while the getter provides controlled read access.

### 6. Setter and change check

```cpp
void VehicleData::setSpeed(int speed)
{
    if (m_speed == speed) {
        return;
    }

    m_speed = speed;
    emit speedChanged();
}
```

The equality check avoids emitting a change signal when the value did not actually change.

### 7. QML binding

```qml
Label {
    text: "Speed: " + vehicleData.speed + " km/h"
}
```

This is a binding, not a one-time assignment. QML remembers that the expression depends on
`vehicleData.speed` and reevaluates it after `speedChanged()`.

### 8. `Q_INVOKABLE` and property update

```cpp
Q_INVOKABLE void increaseSpeed();
```

QML calls this method. The method uses `setSpeed()`, which updates the member and emits the NOTIFY
signal.

## Correct interview topics to cover

1. What `Q_PROPERTY` does
2. READ getter, WRITE setter, and NOTIFY signal
3. The Qt Meta-Object System and MOC
4. Difference between a property and a normal C++ member
5. QML binding versus a one-time assignment
6. Why the setter checks whether the value changed
7. Why the NOTIFY signal must be emitted after updating the value
8. How C++ property changes update QML automatically
9. How QML can write a property through the setter
10. `Q_INVOKABLE` versus `Q_PROPERTY`
11. Binding reevaluation and dependency tracking
12. Binding loops and how they can occur
13. Property types supported across the QML-C++ boundary
14. Thread affinity when changing properties used by QML
15. Exposing objects through `setContextProperty()`

## Most important interview answer

> `Q_PROPERTY` exposes a C++ value to Qt's Meta-Object System. READ provides the getter, WRITE
> provides the setter, and NOTIFY provides the signal that tells QML to reevaluate bindings when
> the value changes.

---

# Signals & Slots — New Dedicated Class

The project now contains a separate class for this topic:

```text
src/signal_slot_demo.h    - class declaration, signal, slot, Q_INVOKABLE method
src/signal_slot_demo.cpp  - connect(), emit, and slot implementation
```

## Complete flow

```text
QML button
    |
    | signalSlotDemo.triggerSignal()
    v
SignalSlotDemo::triggerSignal()
    |
    | emit messageChanged(text)
    +----------------------+
    |                      |
    v                      v
C++ handleMessage()   QML onMessageChanged(messageText)
    |                      |
    v                      v
Console output         Label text update
```

## Code topics to understand

### 1. `QObject`

`SignalSlotDemo` inherits from `QObject` so it can use Qt's Meta-Object System, signals, slots,
parent-child ownership, and QML integration.

### 2. `Q_OBJECT`

`Q_OBJECT` enables Qt meta-object features. CMake's `CMAKE_AUTOMOC ON` runs MOC automatically for
this class.

### 3. `signals:`

```cpp
void messageChanged(const QString &message);
```

This declares an event notification. The signal does not contain the response logic.

### 4. `public slots:`

```cpp
void handleMessage(const QString &message);
```

This declares a function that can receive a compatible signal and handle its data.

### 5. `QObject::connect()`

```cpp
QObject::connect(
    this,
    &SignalSlotDemo::messageChanged,
    this,
    &SignalSlotDemo::handleMessage);
```

This connects the sender signal to the receiver slot. The typed pointer-to-member syntax allows the
compiler to check the signal and slot signatures.

### 6. `emit`

```cpp
emit messageChanged(QStringLiteral("Signal received successfully"));
```

This sends the signal. Every compatible connected receiver is notified.

### 7. Signal parameters

The `QString` parameter carries data from the signal sender to each receiver.

### 8. `Q_INVOKABLE`

```cpp
Q_INVOKABLE void triggerSignal();
```

This is a callable C++ method, not a signal or slot. QML calls it to begin the demonstration.

### 9. QML `Connections`

```qml
Connections {
    target: signalSlotDemo

    function onMessageChanged(messageText) {
        message.text = messageText
    }
}
```

`Connections` listens to signals from an exposed QObject. The handler name is formed from `on` plus
the signal name with its first letter capitalized.

### 10. C++ to QML communication

The C++ object is exposed in `main.cpp` with `setContextProperty()`. QML then accesses it using the
name `signalSlotDemo`.

## Correct interview topics to cover

1. Why a signal is a notification and does not implement response logic
2. What a slot is and how it receives signal parameters
3. `QObject::connect()` sender, signal, receiver, and slot
4. `emit` and one-to-many signal delivery
5. `Q_OBJECT` and MOC/AUTOMOC
6. Typed signal-slot connections and compile-time checking
7. Signals with parameters and compatible signatures
8. `Q_INVOKABLE` versus a signal versus a slot
9. QML `onSignalName` handlers
10. QML `Connections` and `target`
11. C++ to QML communication through `setContextProperty()`
12. Direct and queued connections
13. Thread affinity and UI updates on the UI thread
14. Connection lifetime and automatic disconnection when a QObject is destroyed
15. Connecting one signal to multiple slots

## Most important interview answer

> Signals and slots are Qt's type-safe communication mechanism. A signal announces that an event
> occurred, and a connected slot or QML handler responds to it without tightly coupling the sender
> to the receiver.

---

# 📝 Part 1: CMakeLists.txt — Build Configuration

Your CMake file:

```cmake
cmake_minimum_required(VERSION 3.19)

project(QtInterviewPrep VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 5.15 REQUIRED COMPONENTS Quick QuickControls2)

add_executable(QtInterviewPrep
    src/main.cpp
    qml/qml.qrc
)

target_link_libraries(QtInterviewPrep
    PRIVATE
        Qt5::Quick
        Qt5::QuickControls2
)

install(TARGETS QtInterviewPrep
    BUNDLE DESTINATION .
    RUNTIME DESTINATION bin
)
```

Let's understand it line by line.

---

## 2. `cmake_minimum_required`

```cmake
cmake_minimum_required(VERSION 3.19)
```

This tells CMake:

> The minimum CMake version required to build this project is 3.19.

If somebody tries to configure the project using an older CMake version, CMake can report an error.

### Interview answer

> `cmake_minimum_required()` specifies the minimum CMake version required by the project.

---

# 3. `project()`

```cmake
project(QtInterviewPrep VERSION 0.1 LANGUAGES CXX)
```

This defines your project.

### Project name

```text
QtInterviewPrep
```

### Version

```text
0.1
```

### Language

```text
CXX
```

`CXX` means **C++**.

So:

```cmake
project(QtInterviewPrep VERSION 0.1 LANGUAGES CXX)
```

basically says:

> Create a project called QtInterviewPrep, version 0.1, using C++.

---

# 4. C++ standard

```cmake
set(CMAKE_CXX_STANDARD 17)
```

This tells CMake to compile the project using **C++17**.

Therefore you can use things such as:

```cpp
auto
std::unique_ptr
std::make_unique
structured bindings
if constexpr
```

etc.

---

## 5. `CMAKE_CXX_STANDARD_REQUIRED`

```cmake
set(CMAKE_CXX_STANDARD_REQUIRED ON)
```

This is important.

It means:

> C++17 is required. Don't silently fall back to an older C++ standard.

Without it, depending on the compiler/configuration, CMake may not strictly enforce the requested standard.

### Interview answer

> `CMAKE_CXX_STANDARD_REQUIRED ON` ensures that the requested C++ standard is actually required for compilation.

---

# 6. `CMAKE_AUTOMOC`

```cmake
set(CMAKE_AUTOMOC ON)
```

This is **very important for Qt**.

Qt has a Meta-Object Compiler called **MOC**.

For example:

```cpp
class Vehicle : public QObject
{
    Q_OBJECT

signals:
    void speedChanged(int speed);
};
```

The `Q_OBJECT` macro requires MOC-generated code.

Normally, you could run MOC manually.

But:

```cmake
set(CMAKE_AUTOMOC ON)
```

tells CMake:

> Automatically run MOC when necessary.

This is particularly important when using:

```cpp
Q_OBJECT
signals
slots
Q_PROPERTY
```

### Interview question

**Q: Why do we need AUTOMOC?**

Answer:

> Qt's Meta-Object Compiler generates additional code required for features such as signals, slots, properties and the meta-object system. `CMAKE_AUTOMOC ON` allows CMake to automatically run MOC for relevant source files.

---

# 7. `CMAKE_AUTORCC`

```cmake
set(CMAKE_AUTORCC ON)
```

RCC means **Qt Resource Compiler**.

Qt applications commonly have resources such as:

```text
QML files
images
icons
fonts
translations
```

Your project has:

```text
qml/qml.qrc
```

For example, the `.qrc` might contain:

```xml
<RCC>
    <qresource prefix="/qml">
        <file>main.qml</file>
    </qresource>
</RCC>
```

`AUTORCC` tells CMake to automatically process the `.qrc` resource file.

This is how your QML file becomes available through:

```text
qrc:/qml/main.qml
```

---

# 8. `CMAKE_AUTOUIC`

```cmake
set(CMAKE_AUTOUIC ON)
```

UIC = **User Interface Compiler**.

This is mainly used with Qt Widgets `.ui` files created using Qt Designer.

For example:

```text
mainwindow.ui
```

CMake can automatically run Qt's UIC.

Your current project doesn't appear to use a `.ui` file, so `AUTOUIC` isn't really necessary here.

But it's commonly enabled in Qt projects.

---

# 9. `find_package`

```cmake
find_package(Qt5 5.15 REQUIRED COMPONENTS Quick QuickControls2)
```

This is one of the most important lines.

You're telling CMake:

> Find Qt 5.15 and specifically find the Qt Quick and Qt Quick Controls 2 modules.

You're using:

```text
Qt5::Quick
Qt5::QuickControls2
```

later in the file.

### `REQUIRED`

Means:

> If Qt isn't found, stop configuration and report an error.

Without `REQUIRED`, CMake could potentially continue even if Qt isn't available.

---

# 10. What are Quick and QuickControls2?

Your QML contains:

```qml
import QtQuick 2.15
import QtQuick.Controls 2.15
```

Therefore you need:

```cmake
Qt5::Quick
Qt5::QuickControls2
```

### QtQuick

Provides the basic QML engine/UI functionality.

### QtQuick.Controls

Provides controls such as:

```text
Button
Label
TextField
ComboBox
Slider
CheckBox
etc.
```

---

# 11. `add_executable`

```cmake
add_executable(QtInterviewPrep
    src/main.cpp
    qml/qml.qrc
)
```

This creates an executable called:

```text
QtInterviewPrep
```

and tells CMake that it is built using:

```text
src/main.cpp
qml/qml.qrc
```

So conceptually:

```text
main.cpp
   +
qml.qrc
   ↓
CMake
   ↓
QtInterviewPrep executable
```

---

# 12. Why is `qml.qrc` included?

This is extremely important.

Your C++ code has:

```cpp
const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
```

`qrc:/` means:

> Load the file from Qt's compiled-in resource system.

So your `main.qml` isn't necessarily being loaded directly from the filesystem.

Instead:

```text
main.qml
    ↓
qml.qrc
    ↓
Qt Resource System
    ↓
qrc:/qml/main.qml
```

This is a very common Qt deployment approach.

---

# 13. `target_link_libraries`

```cmake
target_link_libraries(QtInterviewPrep
    PRIVATE
        Qt5::Quick
        Qt5::QuickControls2
)
```

This tells CMake:

> Link the Qt Quick and Qt Quick Controls libraries with my executable.

Your executable is:

```text
QtInterviewPrep
```

and its dependencies are:

```text
Qt5::Quick
Qt5::QuickControls2
```

### What does `PRIVATE` mean?

It controls dependency propagation.

For this executable:

```text
QtInterviewPrep
       ↓
 Qt5::Quick
 Qt5::QuickControls2
```

Those dependencies are needed by this target but aren't propagated as public link dependencies to another target consuming this target.

For an executable, `PRIVATE` is generally what you'll see.

---

# 14. `install()`

```cmake
install(TARGETS QtInterviewPrep
    BUNDLE DESTINATION .
    RUNTIME DESTINATION bin
)
```

This tells CMake what to do when you run:

```bash
cmake --install .
```

It installs the executable.

For example, on platforms where executables are treated as runtime targets:

```text
bin/
   QtInterviewPrep
```

`BUNDLE` is mainly relevant to macOS application bundles.

For your interview, you don't need to spend much time on this part.

---

# 📝 Part 2: src/backend.h — C++ Classes

```cpp
#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

// ============================================================================
// Backend Class - C++ exposed to QML
// ============================================================================
// Key Concepts:
// 1. Inherits from QObject - enables Qt's meta-object system
// 2. Q_OBJECT macro - enables introspection
// 3. Q_INVOKABLE - marks methods callable from QML
// ============================================================================
class Backend : public QObject
{
    Q_OBJECT  // Required for Qt meta-object system

public:
    // Constructor
    // parent = nullptr for top-level objects
    explicit Backend(QObject *parent = nullptr);

    // Q_INVOKABLE makes this callable from QML
    Q_INVOKABLE void showMessage();
};


// Backend_Next Class - Second C++ object exposed to QML
class Backend_Next : public QObject
{
    Q_OBJECT

public:
    explicit Backend_Next(QObject *parent = nullptr);
    Q_INVOKABLE void showMessage_Next();
};

#endif // BACKEND_H
```

## Key Concepts

### QObject Inheritance
```cpp
class Backend : public QObject
```
- Inherits from QObject to enable:
  - Signals/slots
  - Q_PROPERTY
  - Parent-child memory management
  - Q_INVOKABLE methods callable from QML

**Interview Q:** "Why inherit from QObject?"
**Answer:** "QObject provides the meta-object system which enables signals, slots, properties, and allows QML to call C++ methods."

### Q_OBJECT Macro
```cpp
Q_OBJECT
```
- Tells Qt's Meta-Object Compiler to generate introspection code
- Enables signals, slots, and Q_INVOKABLE
- **Without it:** QML can't access the class's methods/properties

**Interview Q:** "What does Q_OBJECT do?"
**Answer:** "Q_OBJECT is a macro that marks a class for the Meta-Object Compiler (MOC), generating code for signals, slots, and Q_INVOKABLE methods."

### Q_INVOKABLE
```cpp
Q_INVOKABLE void showMessage();
```
- Marks a C++ method as callable from QML
- In QML: `backend.showMessage()` works because of Q_INVOKABLE
- Without Q_INVOKABLE: QML can't call this method

---

# 📝 Part 3: src/backend.cpp — Implementation

```cpp
#include "backend.h"

#include <QDebug>

// 1. Backend Constructor
// Initializes the QObject parent
Backend::Backend(QObject *parent)
    : QObject(parent)  // Call parent constructor
{
    qDebug() << "Backend Object Created";
}

// 2. Backend Function
// This is called from QML:  backend.showMessage()
void Backend::showMessage()
{
    qDebug() << "Backend Function Called";
}


// 3. Backend_Next Constructor
Backend_Next::Backend_Next(QObject *parent)
    : QObject(parent)
{
    qDebug() << "Backend_Next Object Created";
}

// 4. Backend_Next Function
// Called from QML:  backendnext.showMessage_Next()
void Backend_Next::showMessage_Next()
{
    qDebug() << "Backend_next Function Called";
}
```

## Key Concepts

### Initializer List
```cpp
Backend::Backend(QObject *parent)
    : QObject(parent)  // ← Initializer list
```
- Calls the base class QObject constructor with parent
- Proper initialization before member variables

**Why:** Ensures parent-child relationship is set up correctly.

### qDebug() Output
```cpp
qDebug() << "Backend Object Created";
```
- Outputs to console/debug pane
- Visible in Qt Creator's "Application Output"
- Confirms functions were actually called

---

# 📝 Part 4: src/main.cpp — Application Entry Point

**The most important file!** Shows how Qt, QML, and C++ work together.

```cpp
#include "backend.h"

#include <QGuiApplication>          // Application management
#include <QQmlApplicationEngine>    // QML engine
#include <QQmlContext>              // Context for exposing C++ objects

int main(int argc, char *argv[])
{
    // ================================================================
    // Step 1: Create QGuiApplication
    // ================================================================
    // Manages:
    // - Event loop
    // - Application lifecycle
    // - GUI-specific settings
    // Only ONE QGuiApplication per process
    QGuiApplication app(argc, argv);

    // ================================================================
    // Step 2: Create QML Engine
    // ================================================================
    // Loads and executes QML files
    // Manages:
    // - QML parsing and compilation
    // - JavaScript engine
    // - Object creation from QML
    QQmlApplicationEngine engine;

    // ================================================================
    // Step 3: Create C++ Backend Object #1
    // ================================================================
    // Backend object lives on the stack
    // Will be destroyed when main() exits
    Backend backend;

    // ================================================================
    // Step 4a: Expose Backend to QML
    // ================================================================
    // Makes Backend object accessible from QML code
    // Syntax: engine.rootContext()->setContextProperty("name", pointer)
    // 
    // After this line, QML can:
    // - Call:  backend.showMessage()
    // - Access: backend properties (if we had Q_PROPERTY)
    // - Connect: to backend signals (if we had Q_SIGNAL)
    engine.rootContext()->setContextProperty("backend", &backend);

    // ================================================================
    // Step 4b: Create and Expose Second Backend Object
    // ================================================================
    Backend_Next backendnext;
    engine.rootContext()->setContextProperty("backendnext", &backendnext);

    // ================================================================
    // Step 5: Define QML File Location
    // ================================================================
    // "qrc:/" means Qt Resource System
    // This loads from compiled resources, not the filesystem
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));

    // ================================================================
    // Step 6: Connect Error Handler
    // ================================================================
    // QObject::connect(sender, signal, receiver, slot)
    // 
    // This handles the case where QML fails to load
    // Lambda [url] captures url from outer scope
    // If obj is nullptr, the QML failed to load
    QObject::connect(
        &engine,                                    // Signal source
        &QQmlApplicationEngine::objectCreated,      // Which signal
        &app,                                       // Receiver
        [url](QObject *obj, const QUrl &objUrl) {   // Lambda slot
            if (!obj && objUrl == url) {
                QCoreApplication::exit(-1);         // Exit with error
            }
        });

    // ================================================================
    // Step 7: Load QML File
    // ================================================================
    // engine.load() does:
    // 1. Find qrc:/qml/main.qml in resources
    // 2. Parse the QML code
    // 3. Create the root ApplicationWindow
    // 4. Emit objectCreated signal (caught by lambda above)
    engine.load(url);

    // ================================================================
    // Step 8: Start Qt Event Loop
    // ================================================================
    // app.exec() starts the event loop and blocks until:
    // - User closes the window, OR
    // - QCoreApplication::quit() is called
    // 
    // The event loop handles:
    // - Mouse clicks and keyboard input
    // - Window events (resize, paint)
    // - Signals and slots
    // - Timers
    return app.exec();
}
```

## Interview Questions on main.cpp

**Q: Why create a QGuiApplication?**
A: It manages the application lifecycle, event loop, and GUI-specific settings. Every Qt GUI app needs exactly one.

**Q: What does setContextProperty do?**
A: It exposes a C++ object to QML so QML code can call its methods and access its properties. This is how QML and C++ communicate.

**Q: Why use `const QUrl url(...)`?**
A: To define the QML file location. `qrc:/` means load from Qt's compiled-in resource system (defined in qml.qrc).

**Q: What's the error handler lambda for?**
A: It catches QML loading failures. If the QML file can't be parsed or loaded, the app exits with error code -1.

**Q: Why call engine.load(url)?**
A: This actually loads and parses the QML file, creating the UI from the QML code.

**Q: What does app.exec() do?**
A: Starts the Qt event loop. The app blocks here until the user closes the window or quit() is called.

**Q: Explain the complete flow from button click to C++ execution**
A: 
1. User clicks button in QML
2. QML `onClicked` signal handler triggers
3. Calls `backend.showMessage()`
4. Qt meta-object system marshals the call to C++
5. `Backend::showMessage()` executes
6. `qDebug()` outputs to console

---

# 📝 Part 5: qml/main.qml — User Interface

```qml
// Step 1: Import QtQuick core types
import QtQuick 2.15

// Step 2: Import UI controls
import QtQuick.Controls 2.15

// Step 3: Import layout types
import QtQuick.Layouts 1.15


// Step 4: ApplicationWindow (root object)
// Top-level window container for QML applications
ApplicationWindow {

    // Window dimensions in logical pixels
    width: 640
    height: 420

    // Show the window on screen
    visible: true

    // Window title shown in title bar
    title: "Qt C++ and QML Communication"


    // Step 5: ColumnLayout
    // Arranges child items vertically (top to bottom)
    ColumnLayout {

        // Position in center of parent window
        anchors.centerIn: parent

        // Space between children
        spacing: 14


        // Step 6: Label (Display Text)
        Label {
            id: message
            text: "Hello Qt 5.15"
            font.pixelSize: 28
            Layout.alignment: Qt.AlignHCenter
        }


        // Step 7: First Button
        // Calls C++ Backend function
        Button {
            text: "Call C++ Function"
            Layout.alignment: Qt.AlignHCenter

            // onClicked: signal handler triggered on button click
            onClicked: {
                // Call C++ method on backend object
                // "backend" was exposed in main.cpp via setContextProperty
                // Qt's meta-object system marshals this call to C++
                backend.showMessage()
            }
        }


        // Step 8: Second Button
        // Calls C++ Backend_Next function
        Button {
            text: "Backend_next C++ Function"
            Layout.alignment: Qt.AlignHCenter

            onClicked: {
                // Call C++ method on second backend object
                // "backendnext" was exposed in main.cpp
                backendnext.showMessage_Next()
            }
        }
    }
}
```

## Interview Questions on main.qml

**Q: What do the imports do?**
A: Import QtQuick (core QML types), Controls (Button, Label), and Layouts (ColumnLayout).

**Q: Why use ColumnLayout?**
A: It automatically arranges children vertically with proper spacing and alignment. Responsive to window resize.

**Q: What does `anchors.centerIn: parent` do?**
A: Positions the layout in the center of its parent window.

**Q: How does QML call C++ functions?**
A: Via Q_INVOKABLE methods on context property objects. When you call `backend.showMessage()`, Qt marshals it to the C++ function.

**Q: What's `onClicked`?**
A: A signal handler. When the button is clicked, the onClicked handler is triggered.

---

# 🔄 Complete Data Flow

## Button Click → C++ Execution

```
┌─ User clicks button in QML UI
│
├─ main.qml: onClicked { backend.showMessage() }
│
├─ Qt meta-object system detects this is a Q_INVOKABLE method call
│
├─ Marshals call from QML JavaScript to C++
│
├─ Backend::showMessage() in backend.cpp executes
│
├─ qDebug() outputs: "Backend Function Called"
│
└─ Console output visible in Qt Creator's "Application Output" pane
```

## Application Startup → Window Display

```
┌─ main() starts
│
├─ Step 1: QGuiApplication created (manages app lifecycle)
│
├─ Step 2: QQmlApplicationEngine created (loads QML)
│
├─ Step 3-4: C++ Backend objects created & exposed to QML
│
├─ Step 5: QML file URL defined (qrc:/qml/main.qml)
│
├─ Step 6: Error handler connected (catches QML failures)
│
├─ Step 7: QML file loaded and parsed
│
├─ Step 8: app.exec() starts event loop
│
└─ Window appears, waiting for user interaction
```

---

# 📚 Summary Table

| Component | Purpose | Lines | Key Concept |
|---|---|---|---|
| CMakeLists.txt | Build configuration | 30 | AUTOMOC, AUTORCC, Qt linking |
| src/backend.h | C++ classes | 36 | QObject, Q_OBJECT, Q_INVOKABLE |
| src/backend.cpp | Implementation | 36 | Constructors, method bodies |
| src/main.cpp | Application entry | 43 | 8 steps: app → QML engine → context properties → event loop |
| qml/main.qml | User interface | 80 | 8 components: Window → Layout → Buttons → C++ calls |

---

# ✅ Interview Quick Reference

## Q: "How does QML call C++ functions?"
**A:** "C++ classes inherit from QObject and mark methods with Q_INVOKABLE. The C++ object is exposed to QML via `engine.rootContext()->setContextProperty()`. When QML calls the method, Qt's meta-object system marshals the call to C++."

## Q: "Explain the complete flow from button click to console output"
**A:**
1. User clicks button in QML UI
2. Button emits `clicked` signal
3. `onClicked` handler in QML is triggered
4. QML calls `backend.showMessage()`
5. Meta-object system marshals the call to C++
6. `Backend::showMessage()` in C++ executes
7. `qDebug()` outputs to console

## Q: "What's the purpose of Q_OBJECT?"
**A:** "Q_OBJECT is a macro that marks a class for Qt's Meta-Object Compiler (MOC). MOC generates code enabling signals, slots, Q_PROPERTY, and Q_INVOKABLE methods."

## Q: "Why do we need parent-child relationships in Qt?"
**A:** "Parent-child relationships enable automatic memory management. When a parent is destroyed, all children are automatically deleted, preventing memory leaks."

## Q: "What's the purpose of AUTOMOC?"
**A:** "AUTOMOC automatically runs Qt's Meta-Object Compiler on classes with Q_OBJECT, generating necessary introspection code. Without it, we'd run MOC manually."

## Q: "Explain the Qt event loop"
**A:** "`app.exec()` starts the event loop, which blocks and continuously processes events: mouse clicks, keyboard input, signals/slots, timers, window events. The app blocks here until user closes the window or `quit()` is called."

## Q: "What does setContextProperty do?"
**A:** "It exposes a C++ QObject to QML, making the object's Q_INVOKABLE methods and Q_PROPERTY properties accessible from QML code."

---

# 🚀 You're Ready for Interviews!

This project demonstrates:
✅ Qt/QML communication  
✅ C++ and QML integration  
✅ Meta-object system  
✅ Parent-child memory management  
✅ Signal/slot connections  
✅ CMake build system  
✅ Context properties  
✅ Event loop architecture  

All in a minimal, educational codebase. Perfect for interview preparation!

and ask:

> **Explain this line completely.**

A strong concise answer would be:

> `QObject::connect()` connects the `objectCreated` signal from `QQmlApplicationEngine` to a lambda function. The lambda captures the QML URL and checks whether the QML root object was successfully created. If object creation fails for the requested URL, the application exits with an error code. `Qt::QueuedConnection` ensures that the lambda is invoked through the receiver's event loop rather than immediately.

That is the kind of explanation I would practice for your **Lead Qt/C++ interview**.

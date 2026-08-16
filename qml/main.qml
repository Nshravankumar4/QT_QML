// 1. Import Qt Quick core types
import QtQuick 2.15

// 2. Import ready-made UI controls
// Examples: Button, Label, TextField
import QtQuick.Controls 2.15

// 3. Import layout types
// Examples: ColumnLayout, RowLayout, GridLayout
import QtQuick.Layouts 1.15


// 4. ApplicationWindow
// Root window of the QML application
ApplicationWindow {

    // Window size
    width: 640
    height: 420

    // Show the window
    visible: true

    // Window title
    title: "Qt C++ and QML Communication"


    // 5. ColumnLayout
    // Arranges child items vertically
    ColumnLayout {

        // Position layout in the center of the window
        anchors.centerIn: parent

        // Space between child items
        spacing: 14


        // 6. Label
        // Displays text
        Label {
            id: message

            // Text displayed by the Label
            text: "Hello Qt 5.15"

            // Font size
            font.pixelSize: 28

            // Center the Label horizontally
            Layout.alignment: Qt.AlignHCenter
        }


        // 7. Button
        // Calls C++ function when clicked
        Button {
            text: "Call C++ Function"

            // Center the button horizontally
            Layout.alignment: Qt.AlignHCenter

            // Signal handler executed when button is clicked
            onClicked: {

                // Call C++ Backend function
                // "backend" was exposed from main.cpp
                backend.showMessage()
            }
        }


        // 8. Second Button
        // Calls function from another C++ object
        Button {
            text: "Backend_next C++ Function"

            // Center the button horizontally
            Layout.alignment: Qt.AlignHCenter

            // Signal handler for button click
            onClicked: {

                // Call Backend_Next C++ function
                // "backendnext" was exposed from main.cpp
                backendnext.showMessage_Next()
            }
        }

        // Dedicated Signals and Slots example.
        Button {
            text: "Run Signals and Slots"
            Layout.alignment: Qt.AlignHCenter

            // QML calls the Q_INVOKABLE method in SignalSlotDemo.
            onClicked:
            {signalSlotDemo.triggerSignal()}
        }

        // Receives the custom signal emitted by the C++ object.
        Connections {
            target: signalSlotDemo

            function onMessageChanged(messageText) {
                message.text = messageText
            }
        }
    }
}

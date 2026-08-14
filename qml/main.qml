import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    width: 640
    height: 420
    visible: true
    title: "Qt Minimal"

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 14

        Label {
            id: message
            text: "Hello Qt 5.15"
            font.pixelSize: 28
            Layout.alignment: Qt.AlignHCenter
        }

        Button {
            text: "Click Me"
            Layout.alignment: Qt.AlignHCenter
            onClicked: message.text = "Qt is working"
        }
    }
}

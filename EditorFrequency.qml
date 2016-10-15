import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import "Style.js" as Style

RowLayout {
    id: root
    Layout.maximumHeight: Style.editorRowHeight

    property alias label: label
    property alias spinBox: spinBox

    signal frequencyChanged(double freq)

    EditorLabel {
        id: label
        text: qsTr("Frequency: ")
        Layout.maximumHeight: Style.editorRowHeight
        Layout.fillWidth: true
    }

    EditorDoubleSpinBox {
        id: spinBox
        Layout.maximumHeight: Style.editorRowHeight
        Layout.preferredWidth: Style.editorControlWidth
        onValueChanged: frequencyChanged(spinBox.value)
    }

}

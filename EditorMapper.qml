import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.11
import "Style.js" as Style

ColumnLayout {
    id: root
    Layout.maximumHeight: Style.editorRowHeight * 2

    property alias label: label
    property alias text: textInput.text
    property alias textColor: textInput.color
    property int maxIndexes: 1
    property string map: ""

    onMapChanged: textInput.text = map;

    // Force map re-evaluation on new Dataset.
    Connections {
        target: transport
        onDatasetImported: {
            var tempMap = map
            map = ""
            map = tempMap
        }
    }

    EditorLabel {
        id: label
        text: qsTr("Source Mapping: ")
        Layout.maximumHeight: Style.editorRowHeight
        Layout.preferredWidth: Style.editorLabelWidth
        Layout.fillWidth: true
    } // label

    Rectangle {
        id: textInputRect
        color: Style.editorTextInputColor
        height:Style.editorRowHeight
        width: Style.editorRowWidth
        Layout.fillWidth: true

        TextInput {
            id: textInput
            anchors.fill: parent
            font.pixelSize: 14
            onEditingFinished: {
                map = text
            }

            MouseArea {
                anchors.fill: textInput
                onClicked: {
                    textInput.forceActiveFocus()
                }
            }
        } // textInput
    } // textInputRect
} // root


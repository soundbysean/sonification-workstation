import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import "Style.js" as Style

Rectangle {
    id: rect

    property alias color: rect.color

    z: 300
    height: childrenRect.height + Style.editorMargin
    width: childrenRect.width + Style.editorMargin
    radius: Style.editorRadius
    anchors.centerIn: parent
    color: Style.editorBackgroundColor
    opacity: 0

    enabled: false

}
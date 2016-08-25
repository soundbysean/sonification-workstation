import QtQuick 2.7


Item {

    id: item

    property int type: -1 //OUT = 0, OSC = 1
    property bool created: false
    property var inputs: new Array
    property var outputs: new Array
    property string label: "SON"
    property string mainColor
    property string textColor
    property PatchManager myManager: null

    signal synthItemClicked(var i)

//    Component.onCompleted: {
//        synthItemClicked.connect
//    }

    function create() {
        created = true
        graph.createItem(this, type)
        canvas.requestPaint()
    }

    width: 64; height: 64

    onXChanged: canvas.requestPaint()
    onYChanged: canvas.requestPaint()

    FocusScope {
        id: scope
        anchors.fill: parent
    }

    Rectangle {
        id: rect
        z: 200
        anchors.fill: parent

        width: item.width * 0.8

        radius: 100
        color: mainColor
        opacity: created ? 1 : 0.4

        border.width: 0
        border.color: textColor


        MouseArea {
            id: mouseArea

            anchors.fill: rect

            drag.target: item
            drag.axis: Drag.XAndYAxis
            drag.minimumX: 0
            drag.minimumY: 0
            Drag.active: mouseArea.drag.active
            Drag.hotSpot.x: 36
            Drag.hotSpot.y: 32

            onReleased: mouseArea.Drag.drop()

            onClicked: {
                console.log("Item: click!")
                patchManager.setPatchPoint(item)
            }

        }

        Text {
            id: labelText
            text: label
            color: textColor
            anchors {
                centerIn: parent
            }
        }

    }

    Keys.onPressed: {
        if (event.key == Qt.Key_Backspace || event.key == Qt.Key_Delete) {
            console.log("Type: Back!")
            var i = synthWindow.synthItems.indexOf(this)
            synthWindow.synthItems.splice(i, 1)
            this.destroy()
            event.accepted = true;
        }
    }

}

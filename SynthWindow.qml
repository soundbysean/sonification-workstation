import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.0

ApplicationWindow {

    id: synthWindow

    // holds every item in the workspace for iterating
    property var synthItems: [dac]
    //canvas for drawing connections
    property alias canvas: canvas

    width: 640
    height: 480
    visible: true
    title: qsTr("Sonification Workstation: Synthesis")

    menuBar: MenuBar {
        id: menuBar
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered:  {
                    quit()
                    console.log("click")
                }

            }
        }
    }

    statusBar: StatusBar {
        id: statusBar
    }

    Item {
        id: window
        anchors.fill: parent

        // top panel
        Rectangle {
            id: toolbox

            height: 70
            color: "gray"
            anchors { right: parent.right; top: parent.top; left: parent.left}

            Row {
                id: palette
                anchors.centerIn: parent
                spacing: 8

                PaletteItem {
                    anchors.verticalCenter: parent.verticalCenter
                    componentFile: "OscillatorGUI.qml"
                    source: "images/oscIcon.png"
                    image: "images/oscIcon.png"
                }
            }
        }


        //this scroll area is the workspace where
        //synthItems are dropped and built into the
        //synthesis graph
        ScrollView {
            id: workspace

            anchors {
                top: toolbox.bottom
                left: window.left
                right: window.right
                bottom: window.bottom
            }
        }

        MouseArea {
            id: workspaceMouseArea
            hoverEnabled: true
            anchors.fill: workspace
            onMouseXChanged: if(patchManager.patch !== null) { canvas.requestPaint() }
            onMouseYChanged: if(patchManager.patch !== null) { canvas.requestPaint() }
        }

        OutGUI {
            id: dac
            created: true
            anchors {
                horizontalCenter: parent.horizontalCenter
                bottom: parent.bottom
                bottomMargin: 8
            }
        }

        PatchManager {
            id: patchManager
        }

        //canvas on which the connections are drawn
        Canvas {
            id: canvas
            z: 0

            anchors.fill: workspace

            onPaint: {


                // get context to draw with
                var ctx = getContext("2d")
                // clear canvas
                ctx.clearRect(0, 0, canvas.width, canvas.height)
                // setup the stroke
                ctx.lineWidth = 4
                ctx.strokeStyle = "chartreuse"

                // get each patch
                var count = patchManager.patches.length
                for(var i = 0; i < count; i++)
                {
                    var patch = patchManager.patches[i]
                    var startPoint = mapFromItem(window, patch.start.x, patch.start.y)
                    var beginX = startPoint.x + patch.start.width / 2
                    var beginY = startPoint.y + patch.start.height / 2
                    //                    console.log(patch.startPoint)
                    var endPoint = mapFromItem(window, patch.end.x, patch.end.y)
                    var endX = endPoint.x + patch.end.width / 2
                    var endY = endPoint.y + patch.end.height / 2

                    // begin a new path to draw
                    ctx.beginPath()
                    // line start point
                    ctx.moveTo(beginX,beginY)
                    // line end point
                    ctx.lineTo(endX,endY)
                    // stroke using line width and stroke style
                    ctx.stroke()
                }

                console.log(patchManager.patch)
                // in progress patches
                if (patchManager.patch !== null)
                {
                    patch = patchManager.patch
                    console.log("OnDraw: found patch in progress")

                    if (patch.end === null)
                    {
                        console.log("OnDraw: found patch end null")
                        startPoint = mapFromItem(window, patch.start.x, patch.start.y)
                        beginX = startPoint.x + patch.start.width / 2
                        beginY = startPoint.y + patch.start.height / 2

                        endPoint = mapToItem(canvas, workspaceMouseArea.mouseX, workspaceMouseArea.mouseY )
                        endX = endPoint.x
                        endY = endPoint.y

                        // begin a new path to draw
                        ctx.beginPath()
                        // line start point
                        ctx.moveTo(beginX,beginY)
                        // line end point
                        ctx.lineTo(endX,endY)
                        // stroke using line width and stroke style
                        ctx.stroke()
                    }
                }

            }



        }
    }

}

import QtQuick
import QtQuick.Controls

Pane {
    id: root

    required property var model
    property int itemCount: 5
    property int flickDeceleration: 1000
    property alias currentItem: pathView.currentItem
    property alias currentIndex: pathView.currentIndex

    implicitWidth: 100
    implicitHeight: 200
    Rectangle {
        anchors.centerIn: pathView
        anchors.verticalCenterOffset: (pathView.height / 10)
        implicitWidth: parent.width / 2
        implicitHeight: 2
        color: "black"
    }

    Rectangle {
        anchors.centerIn: pathView
        anchors.verticalCenterOffset: -(pathView.height / 10)
        implicitWidth: parent.width / 2
        implicitHeight: 2
        color: "black"
    }

    PathView {
        id: pathView
        anchors.fill: parent
        model: root.model
        pathItemCount: root.itemCount
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        highlightRangeMode: PathView.StrictlyEnforceRange
        delegate: Item {
            id: itm
            anchors.left: parent.left
            anchors.right: parent.right
            implicitHeight: parent.height / root.itemCount
            scale: PathView.iconScale ? PathView.iconScale : 1
            opacity: PathView.iconOpacity ? PathView.iconOpacity : 0

            Label {
                id: label
                text: modelData
                color: itm.PathView.isCurrentItem ? "red" : label.palette.windowText
                font.pointSize: 12
                anchors.centerIn: parent
            }
            MouseArea {
                id: itemMouseArea
                anchors.fill: parent
                onClicked: {
                    pathView.currentIndex = index
                }
            }
        }
        flickDeceleration: root.flickDeceleration
        path: Path {
            startX: pathView.width / 2
            startY: -(root.implicitHeight / 9)
            PathAttribute {
                name: "iconScale"
                value: 0.7
            }
            PathAttribute {
                name: "iconOpacity"
                value: 0.2
            }
            PathLine {
                x: pathView.width / 2
                y: root.height / 2
            }
            PathAttribute {
                name: "iconScale"
                value: 2
            }
            PathAttribute {
                name: "iconOpacity"
                value: 1
            }
            PathLine {
                x: pathView.width / 2
                y: root.height
            }
        }
    }
}

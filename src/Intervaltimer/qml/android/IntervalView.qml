import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Pane {
    id: root
    required property var defaultDuration
    required property var defaultDescription
    property color textColor: "#aaaaaa"
    property color placeholderTextColor: "#bbbbbb"

    signal deleteInterval()
    signal durationChanged(int duration)
    signal descriptionChanged(string description)
    background: Rectangle {
        anchors.fill: root
        color: "transparent"
    }

    contentItem: RowLayout {

        TextField {
            id: descriptionEdit
            selectByMouse: true
            text: root.defaultDescription
            color: root.textColor
            placeholderText: "Description"
            placeholderTextColor: root.placeholderTextColor
            onEditingFinished: () => {
                focus = false
                descriptionChanged(text)
            }

            implicitWidth: root.width * 0.4
            onFocusChanged: {
                if (focus)
                    selectAll()
            }
        }

        DurationControl {
            id: durationController
            duration: root.defaultDuration
            textColor: root.textColor
            implicitWidth: root.width * 0.4
            onDurationChanged: {
                root.durationChanged(durationController.duration)
           }
        }

        Button {
            text: "X"
            implicitWidth: root.width * 0.2
            onClicked: root.deleteInterval()
        }
    }
}

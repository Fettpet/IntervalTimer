import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Pane {
    id: root
    required property var defaultDuration
    required property var defaultDescription

    signal deleteInterval()
    signal durationChanged(int duration)
    signal descriptionChanged(string description)
    implicitWidth: 180
    background: Rectangle {
        width: parent.implicitWidth + 30
        height: parent.implicitHeight
        radius: 6
        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop {
                position: 0.0
                color: "aqua"
            }
            GradientStop {
                position: 0.3
                color: "teal"
            }

            GradientStop {
                position: 0.7
                color: "teal"
            }
            GradientStop {
                position: 1.0
                color: "aqua"
            }
        }
    }

    RowLayout {

        TextField {
            id: descriptionEdit
            selectByMouse: true
            text: root.defaultDescription
            placeholderText: "Description"
            onEditingFinished: descriptionChanged(text)
            Layout.fillWidth: true
            implicitWidth: root.implicitWidth * 0.4
            onFocusChanged: {
                if (focus)
                    selectAll()
            }
        }

        DurationControl {
            id: durationController
            duration: root.defaultDuration
            onDurationChanged: {
                root.durationChanged(durationController.duration)
           }
        }

        Button {
            text: "X"
            implicitWidth: root.implicitWidth * 0.2
            onClicked: root.deleteInterval()
        }
    }
}

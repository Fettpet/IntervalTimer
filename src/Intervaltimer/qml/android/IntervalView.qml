import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Pane {
    id: root
    required property var duration
    required property var description

    signal deleteInterval()
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
            text: root.description
            placeholderText: "Description"
            onEditingFinished: root.description = text
            Layout.fillWidth: true
            implicitWidth: root.implicitWidth * 0.4
            onFocusChanged: {
                if (focus)
                    selectAll()
            }
        }

        TextField {
            id: durationEdit

            selectByMouse: true
            validator: IntValidator {
                bottom: 1
            }
            placeholderText: "Duration"
            text: root.duration
            onEditingFinished: root.duration = text
            implicitWidth: root.implicitWidth * 0.4
            onFocusChanged: {
                if (focus)
                    selectAll()
            }
        }
        Button {
            text: "X"
            implicitWidth: root.implicitWidth * 0.2
            onClicked: root.deleteInterval()
        }
    }
}

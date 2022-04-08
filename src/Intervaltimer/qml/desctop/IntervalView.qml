import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Frame {
    id: root
    required property var duration
    required property var description

    background: Rectangle {
        width: parent.width
        height: parent.height
        radius: 6
        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop {
                position: 0.0
                color: "aqua"
            }
            GradientStop {
                position: 0.1
                color: "teal"
            }

            GradientStop {
                position: 0.9
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
            placeholderText: "Interval description"
            onEditingFinished: root.description = text
            Layout.fillWidth: true

            onFocusChanged: {
                if (focus) {
                    selectAll()
                    return
                }
                Qt.inputMethod.hide();
            }
        }

        TextField {
            id: durationEdit

            selectByMouse: true
            validator: IntValidator {
                bottom: 1
            }
            placeholderText: "Interval duration in seconds"
            text: root.duration
            onEditingFinished: root.duration = text

            onFocusChanged: {
                if (focus) {
                    selectAll()
                    return
                }
                Qt.inputMethod.hide();
            }
        }
    }
}

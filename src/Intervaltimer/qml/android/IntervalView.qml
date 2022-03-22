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
    anchors.left: parent.left
    anchors.right: parent.right

    RowLayout {

        TextField {
            id: descriptionEdit
            selectByMouse: true
            text: root.defaultDescription
            placeholderText: "Description"
            onEditingFinished: () => {
                focus = false
                descriptionChanged(text)
            }
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

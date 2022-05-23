import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Intervaltimer.Android

Pane {
    id: root
    required property var model
    readonly property string description: model.description ? model.description : ""
    readonly property int duration: model.duration ? model.duration : 0

    signal deleteInterval

    contentItem: RowLayout {
        implicitHeight: Math.max(descriptionEdit.implicitHeight,
                                 durationController.implicitHeight,
                                 deleteButton.implicitHeight)
        implicitWidth: 1.1 * (descriptionEdit.implicitWidth + durationController.implicitWidth
                              + deleteButton.implicitWidth)
        TextField {
            id: descriptionEdit
            selectByMouse: true
            text: root.description
            placeholderText: "Description"
            onEditingFinished: () => {
                                   focus = false
                                   model.description = text
                               }

            width: root.width * 0.35
            onFocusChanged: {
                if (focus) {
                    selectAll()
                    return
                }
                Qt.inputMethod.hide()
            }
        }

        DurationControl {
            id: durationController
            duration: root.duration
            width: root.width * 0.35
            onDurationChanged: {
                model.duration = duration
            }
            onFocusChanged: {
                if (focus) {
                    Qt.inputMethod.hide()
                }
            }
        }

        RoundButton {
            id: deleteButton
            text: "Delete"
            width: root.width * 0.2
            onClicked: root.deleteInterval()
        }
    }
}

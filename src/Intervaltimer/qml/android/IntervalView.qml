import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Intervaltimer.Android

Pane {
    id: root
    required property var model
    readonly property string description: model.description ? model.description : ""
    readonly property int duration: model.duration ? model.duration : 0
    property color textColor: Style.textColor
    property color placeHolderTextColor: Style.placeHolderTextColor

    signal deleteInterval

    background: Rectangle {
        anchors.fill: root
        color: "transparent"
    }

    contentItem: RowLayout {

        TextField {
            id: descriptionEdit
            selectByMouse: true
            text: root.description
            color: root.textColor
            placeholderText: "Description"
            placeholderTextColor: root.placeHolderTextColor
            onEditingFinished: () => {
                                   focus = false
                                   model.description = text
                               }

            implicitWidth: root.width * 0.4
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
            textColor: root.textColor
            implicitWidth: root.width * 0.4
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
            text: "Del"
            implicitWidth: root.width * 0.2
            onClicked: root.deleteInterval()
        }
    }
}

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Intervaltimer.Android

Pane {
    id: root
    required property var defaultDuration
    required property var defaultDescription
    property color textColor: Style.textColor
    property color placeHolderTextColor: Style.placeHolderTextColor

    signal deleteInterval
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
            placeholderTextColor: root.placeHolderTextColor
            onEditingFinished: () => {
                                   focus = false
                                   descriptionChanged(text)
                               }

            implicitWidth: root.width * 0.4
            onFocusChanged: {
                if (focus) {
                    selectAll()
                    return
                }
                Qt.inputMethod.hide();
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
            onFocusChanged: {
                if(focus) {
                    Qt.inputMethod.hide();
                }
            }
        }

        Button {
            text: "X"
            implicitWidth: root.width * 0.2
            onClicked: root.deleteInterval()
        }
    }
}

import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

import Intervaltimer
import Intervaltimer.Android

Popup {
    id: root

    required property color backgroundColor

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    width: 200
    height: 70
    background: Rectangle {
        id: backRectangle
        color: root.backgroundColor
        width: root.width
        height: root.height
        radius: 8
    }
    onOpened: nameEdit.focus = true

    ColumnLayout {
        id: layout
        property bool overrideActive: false
        RowLayout {
            TextField {
                id: nameEdit
                placeholderText: "Name"
                selectByMouse: true
                onFocusChanged: {
                    if (focus) {
                        selectAll()
                        return
                    }
                    Qt.inputMethod.hide();
                }
                onEditingFinished: () => {
                    focus = false
                    if (text === "") {
                        focus = true
                        return
                    }
                    if (PlanStorageModel.containsPlan(text)) {
                        layout.overrideActive = true
                        return
                    }
                    PlanStorageModel.appendPlan(text)
                    root.close()
                }
            }
            Button {
                text: "Save"
                onClicked: {
                    if (nameEdit.text === "") {
                        nameEdit.focus = true
                        return
                    }
                    if (PlanStorageModel.containsPlan(nameEdit.text)) {
                        layout.overrideActive = true
                        return
                    }

                    PlanStorageModel.appendPlan(nameEdit.text)
                    root.close()
                }
            }
        }
        Button {
            Layout.alignment: Qt.AlignCenter
            text: "Override"
            visible: layout.overrideActive
            enabled: visible
            onClicked: {
                if (nameEdit.text === "") {
                    nameEdit.focus = true
                    return
                }
                layout.overrideActive = false
                PlanStorageModel.appendPlan(nameEdit.text)
                root.close()
            }
        }
    }
}

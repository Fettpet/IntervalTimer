import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Window 2.2
import QtQuick.Layouts 1.0

import Intervaltimer 1.0
import Intervaltimer.Android 1.0

Popup {
    id: root
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    width: 200
    height: 70

    background: Rectangle {
        id: backRectangle
        color: "red"
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
                    if (focus)
                        selectAll()
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

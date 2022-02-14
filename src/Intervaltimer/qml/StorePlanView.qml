import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Window 2.2
import QtQuick.Layouts 1.0

import Intervaltimer 1.0

Popup {
    id: root
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    Rectangle {
        color: "red"
        width: 200
        height: 50
        RowLayout {
            TextField {
                id: nameEdit
                placeholderText: "Name"
            }
            Button {
                text: "save"
                onClicked: {
                    PlanStorageModel.appendPlan(nameEdit.text)
                    root.close()
                }
            }
        }
    }
}

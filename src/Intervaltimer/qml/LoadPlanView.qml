import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Window 2.2
import QtQuick.Layouts 1.0
import Intervaltimer 1.0

Popup {
    id: root
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    width: 200
    height: 300
    RowLayout {
        ColumnLayout {
            Repeater {
                model: PlanStorageModel

                Button {
                    text: nameRole
                    onClicked: {
                        PlanStorageModel.loadPlan(nameRole)
                    }
                }
            }
        }

        ColumnLayout {
            Repeater {
                model: PlanStorageModel

                Button {
                    text: "X"
                    onClicked: {
                        PlanStorageModel.removePlan(nameRole)
                    }
                }
            }
        }
    }
}

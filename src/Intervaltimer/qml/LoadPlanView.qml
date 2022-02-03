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
        height: 500
        ColumnLayout {
            Repeater {
                model: PlanStorageModel
                RowLayout {
                    Button {
                        text: nameRole
                        onClicked: {
                            PlanStorageModel.loadPlan(nameRole)
                        }
                    }
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
}

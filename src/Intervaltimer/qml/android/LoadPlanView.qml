import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Window 2.2
import QtQuick.Layouts 1.0
import Intervaltimer 1.0
import Intervaltimer.Android 1.0

Popup {
    id: root
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    width: layout.width + 20
    height: Math.min(300, layout.height + 20)

    background: Rectangle {
        id: backRectangle
        color: "red"
        width: root.width
        height: root.height

        radius: 8
    }

    Flickable {
        clip: true
        contentHeight: layout.height
        contentWidth: layout.width
        width: root.width
        height: root.height

        RowLayout {
            id: layout

            ColumnLayout {
                Repeater {
                    model: PlanStorageModel

                    delegate: Button {
                        text: nameRole
                        onClicked: {
                            root.close()
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
}

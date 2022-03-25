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
    width: layout.width + 20
    height: Math.min(300, layout.height + 20)
    background: Rectangle {
        id: backRectangle
        color: root.backgroundColor
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

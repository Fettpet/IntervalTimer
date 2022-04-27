import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Intervaltimer
import Intervaltimer.Android

Pane {
    id: root

    required property string name
    required property int repetitionCount
    required property bool expanded
    required property bool isRoot
    implicitWidth: layout.implicitWidth + 10
    implicitHeight: layout.implicitHeight + 10

    signal deletePlanModel
    signal deleteItem(int index)
    signal appendInterval
    signal appendPlan
    signal toggleExtended

    Connections {
        target: root

        function onDeleteItem(index) {
            if (root.planModel != null) {
                root.planModel.removeItem(index)
                root.planModel.reset()
            }
        }
    }

    background: Rectangle {
        width: root.implicitWidth * 1.1
        height: root.implicitHeight + 20
        radius: 12
        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop {
                position: 0.0
                color: Style.backgroundColor
            }
            GradientStop {
                position: 0.3
                color: Style.gradientColor
            }

            GradientStop {
                position: 0.7
                color: Style.gradientColor
            }
            GradientStop {
                position: 1.0
                color: Style.backgroundColor
            }
        }
    }

    contentItem: Pane {
        id: layout

        implicitWidth: planView.implicitWidth
        implicitHeight: planView.implicitHeight
        background: Rectangle {
            color: "transparent"
        }

        Pane {
            id: planView
            anchors.top: parent.top

            background: Rectangle {
                color: "transparent"
            }

            ColumnLayout {
                id: columnLayout
                RowLayout {
                    id: header
                    TextField {
                        text: root.name
                        color: Style.textColor
                        placeholderText: "Name"
                        placeholderTextColor: Style.placeHolderTextColor
                        onEditingFinished: () => {
                                               focus = false
                                           }
                        selectByMouse: true
                        onFocusChanged: {
                            if (focus) {
                                selectAll()
                                return
                            }
                            Qt.inputMethod.hide()
                        }
                    }
                    TextField {
                        id: repetitionEdit
                        implicitWidth: 50

                        validator: IntValidator {
                            bottom: 1
                        }
                        placeholderTextColor: Style.placeHolderTextColor
                        placeholderText: "Repetitions"
                        text: root.repetitionCount
                        color: Style.textColor
                        onEditingFinished: () => {
                                               focus = false
                                           }
                        selectByMouse: true
                        onFocusChanged: {
                            if (focus) {
                                selectAll()
                                return
                            }
                            Qt.inputMethod.hide()
                        }
                    }
                    ToolButton {
                        icon {
                            color: Style.textColor
                            source: root.expanded ? "qrc:/IntervalApplication/ressources/image/expanded.png" : "qrc:/IntervalApplication/ressources/image/closed.png"
                        }
                        onClicked: root.toggleExtended()
                    }
                }

                RowLayout {
                    RoundButton {
                        text: "Add Interval"
                        Layout.preferredHeight: root.expanded ? implicitHeight : 0
                        onClicked: root.appendInterval()
                    }
                    RoundButton {
                        text: "Add Plan"
                        Layout.preferredHeight: root.expanded ? implicitHeight : 0
                        onClicked: root.appendPlan()
                    }
                    RoundButton {
                        text: "X"
                        Layout.preferredHeight: root.expanded ? implicitHeight : 0
                        visible: root.expanded && !root.isRoot
                        //                        onClicked: root.deletePlanModel()
                    }
                }
            }
        }
    }
}

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Intervaltimer
import Intervaltimer.Android

Pane {
    id: root

    required property var model
    required property bool isRoot

    readonly property string name: model.name ? model.name : ""
    readonly property int repetitionCount: model.repetitionCount ? model.repetitionCount : 1
    readonly property bool expanded: model.expandedRole ? model.expandedRole : false

    implicitWidth: layout.implicitWidth + 10
    implicitHeight: layout.implicitHeight + 10

    signal appendInterval
    signal appendPlan
    signal deletePlan
    signal expand
    signal collapse

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
                        onAccepted: () => {
                                        model.name = text
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

                    SpinBox {
                        id: repetitionEdit
                        implicitWidth: 50
                        from: 1
                        value: root.repetitionCount
                        onValueModified: () => {
                                             model.repetitionCount = value
                                         }
                        onFocusChanged: {
                            if (focus) {
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
                        onClicked: {
                            model.expandedRole = !model.expandedRole
                            if (model.expandedRole) {
                                root.expand()
                            } else {
                                root.collapse()
                            }
                        }
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
                        text: "Delete"
                        Layout.preferredHeight: root.expanded ? implicitHeight : 0
                        visible: root.expanded && !root.isRoot
                        onClicked: root.deletePlan()
                    }
                }
            }
        }
    }
}

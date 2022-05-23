import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Intervaltimer
import Intervaltimer.Android

Pane {
    id: root

    required property var model
    required property bool isRoot
    required property int depth
    readonly property string name: model.name ? model.name : ""
    readonly property int repetitionCount: model.repetitionCount ? model.repetitionCount : 1
    readonly property bool expanded: model.expandedRole ? model.expandedRole : false

    implicitWidth: columnLayout.implicitWidth + 10
    implicitHeight: columnLayout.implicitHeight + 10

    signal appendInterval
    signal appendPlan
    signal deletePlan
    signal expand
    signal collapse

    anchors.top: parent.top

    contentItem: ColumnLayout {
        id: columnLayout
        RowLayout {
            id: header
            TextField {
                text: root.name
                placeholderText: "Name"
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
                implicitWidth: 120
                from: 1
                to: 10
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
            visible: root.expanded
            RoundButton {
                text: "Add Interval"
                onClicked: root.appendInterval()
            }
            RoundButton {
                text: "Add Plan"
                visible: enabled
                enabled: root.depth < 3
                onClicked: root.appendPlan()
            }
            RoundButton {
                text: "Delete"
                visible: !root.isRoot
                onClicked: root.deletePlan()
            }
        }
    }
}

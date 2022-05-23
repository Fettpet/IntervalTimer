import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Intervaltimer
import Intervaltimer.Android

Pane {
    id: root

    required property QtObject planModel
    property color backgroundColor: "#111111"
    property color gradientColor: "#333333"
    property color footerColor: "#333333"
    property color popupColor: "#555555"
    background: Rectangle {
        anchors.fill: parent
        color: root.backgroundColor
    }

    signal startRunning

    MenuView {
        id: menu
        anchors.right: parent.right
        anchors.top: parent.top
        z: 10
    }
    RoundButton {
        enabled: planModel ? !planModel.hasZeroDuration : false
        anchors.right: menu.right
        anchors.top: menu.bottom
        text: "Run"
        z: 10
        onClicked: root.startRunning()
    }

    TreeView {
        anchors.fill: parent
        model: root.planModel

        delegate: Item {
            id: itemDelegate
            implicitWidth: isInterval ? padding + labelInterval.x
                                        + labelInterval.implicitWidth : padding
                                        + labelPlan.x + labelPlan.implicitWidth
            implicitHeight: isInterval ? labelInterval.implicitHeight : labelPlan.implicitHeight
                                         * 1.5
            required property bool isPlan
            required property bool isInterval
            required property var model
            required property var index

            required property int depth
            required property TreeView treeView
            required property bool isTreeNode
            required property bool hasChildren

            required property bool expandedRole

            readonly property real indent: 20
            readonly property real padding: 5

            IntervalView {
                id: labelInterval

                x: padding + (itemDelegate.isTreeNode ? (itemDelegate.depth + 1)
                                                        * itemDelegate.indent : 0)
                width: 400
                visible: enabled
                enabled: itemDelegate.isInterval && itemDelegate.isTreeNode
                model: itemDelegate.model
                Material.elevation: itemDelegate.depth
                onDeleteInterval: {
                    root.planModel.removeItem(treeView.modelIndex(row, column))
                }
            }

            PlanView {
                id: labelPlan
                visible: enabled
                enabled: itemDelegate.isPlan && itemDelegate.isTreeNode
                isRoot: itemDelegate.depth == 0
                x: padding + (itemDelegate.isTreeNode ? (itemDelegate.depth + 1)
                                                        * itemDelegate.indent : 0)
                width: itemDelegate.width - itemDelegate.padding - x
                model: itemDelegate.model
                depth: itemDelegate.depth
                Material.elevation: itemDelegate.depth
                onExpand: {
                    treeView.expand(row)
                }

                onCollapse: treeView.collapse(row)

                onDeletePlan: {
                    root.planModel.removeItem(treeView.modelIndex(row, column))
                }

                onAppendInterval: {
                    var hasChildsBefore = itemDelegate.hasChildren
                    root.planModel.appendInterval(treeView.modelIndex(row,
                                                                      column))
                    if (!hasChildsBefore && itemDelegate.expandedRole) {
                        treeView.collapse(row)
                        treeView.expand(row)
                    }
                }

                onAppendPlan: {
                    var hasChildsBefore = itemDelegate.hasChildren
                    root.planModel.appendPlan(treeView.modelIndex(row, column))
                    if (!hasChildsBefore && itemDelegate.expandedRole) {
                        treeView.collapse(row)
                        treeView.expand(row)
                    }
                }
            }
        }
    }
}

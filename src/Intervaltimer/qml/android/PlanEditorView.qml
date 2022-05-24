import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Intervaltimer
import Intervaltimer.Android

Pane {
    id: root

    required property QtObject planModel

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
        id: view
        anchors.fill: parent
        model: root.planModel

        delegate: Item {
            id: itemDelegate
            implicitWidth: {
                if (!isTreeNode) {
                    return 1
                }
                if (isInterval) {
                    return padding + labelInterval.x + labelInterval.implicitWidth
                }
                return padding + labelPlan.x + labelPlan.implicitWidth
            }
            implicitHeight: {
                if (!isTreeNode) {
                    return 1
                }
                if (isInterval) {
                    return labelInterval.implicitHeight
                }
                return labelPlan.implicitHeight
            }

            onImplicitHeightChanged: view.forceLayout()

            required property bool isPlan
            required property bool isInterval
            required property var model
            required property var index

            required property int depth
            required property TreeView treeView
            required property bool isTreeNode
            required property bool hasChildren

            required property bool expandedRole

            readonly property real indent: 30
            readonly property real padding: 5

            IntervalView {
                id: labelInterval

                x: padding + (itemDelegate.isTreeNode ? itemDelegate.depth
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
                x: padding + (itemDelegate.isTreeNode ? itemDelegate.depth
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

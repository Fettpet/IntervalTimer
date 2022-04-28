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
    property color textColor: "#bbbbbb"
    background: Rectangle {
        anchors.fill: parent
        color: root.backgroundColor
    }

    signal startRunning

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
            required property var description
            required property var duration
            required property var subPlan
            required property var index
            required property var model
            required property var name
            required property var repetionCount

            required property int depth
            required property bool hasChildren
            required property TreeView treeView
            required property bool isTreeNode
            required property bool expanded

            readonly property real indent: 20
            readonly property real padding: 5

            IntervalView {
                id: labelInterval

                x: padding + (itemDelegate.isTreeNode ? (itemDelegate.depth + 1)
                                                        * itemDelegate.indent : 0)
                width: 400
                visible: enabled
                enabled: itemDelegate.isInterval && itemDelegate.isTreeNode
                defaultDuration: itemDelegate.duration ? itemDelegate.duration : 0
                defaultDescription: itemDelegate.description ? itemDelegate.description : ""
                onDescriptionChanged: description => {
                                          model.description = description
                                      }
                onDurationChanged: duration => model.duration = duration
                onDeleteInterval: {
                    root.planModel.removeItem(treeView.modelIndex(row, column))
                }
                textColor: "black"
                placeHolderTextColor: "darkgrey"
            }

            PlanView {
                id: labelPlan
                visible: enabled
                enabled: itemDelegate.isPlan && itemDelegate.isTreeNode
                expanded: itemDelegate.expanded
                isRoot: itemDelegate.depth == 0
                x: padding + (itemDelegate.isTreeNode ? (itemDelegate.depth + 1)
                                                        * itemDelegate.indent : 0)
                width: itemDelegate.width - itemDelegate.padding - x
                name: itemDelegate.name ? itemDelegate.name : ""
                repetitionCount: itemDelegate.repetionCount ? itemDelegate.repetionCount : 0

                onToggleExtended: {
                    treeView.toggleExpanded(row)
                }

                onDeletePlan: {
                    root.planModel.removeItem(treeView.modelIndex(row, column))
                }

                onAppendInterval: root.planModel.appendInterval(
                                      treeView.modelIndex(row, column))

                onAppendPlan: root.planModel.appendPlan(treeView.modelIndex(
                                                            row, column))
            }
        }
    }

    Rectangle {
        id: footerView
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        height: footer.implicitHeight
        anchors.right: parent.right

        color: root.footerColor
        RowLayout {
            id: footer
            anchors.horizontalCenter: parent.horizontalCenter
            RoundButton {
                text: "Save"
                onClicked: {
                    loaderStorePlan.open()
                    loaderLoadPlan.close()
                }
            }
            RoundButton {
                text: "Load"
                onClicked: {
                    loaderLoadPlan.open()
                    loaderStorePlan.close()
                }
            }
            RoundButton {
                enabled: planModel ? !planModel.hasZeroDuration : false
                text: "Run"
                onClicked: startRunning()
            }
        }
    }

    StorePlanView {
        id: loaderStorePlan
        backgroundColor: root.popupColor
        anchors.centerIn: parent
    }

    LoadPlanView {
        id: loaderLoadPlan
        backgroundColor: root.popupColor
        anchors.centerIn: parent
    }
}

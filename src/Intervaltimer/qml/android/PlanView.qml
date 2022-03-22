import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import Intervaltimer 1.0
import Intervaltimer.Android 1.0

Pane {
    id: root
    property QtObject planModel: null
    property Component childComponent: null

    implicitWidth: layout.implicitWidth + 10
    implicitHeight: layout.implicitHeight + 10
    signal deletePlanModel

    background: Rectangle {
        width: root.implicitWidth * 1.1
        height: root.implicitHeight + 20
        radius: 12
        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop {
                position: 0.0
                color: "aqua"
            }
            GradientStop {
                position: 0.3
                color: "teal"
            }

            GradientStop {
                position: 0.7
                color: "teal"
            }
            GradientStop {
                position: 1.0
                color: "aqua"
            }
        }
    }

    contentItem: Pane {
        id: layout

        implicitWidth: planView.implicitWidth
        implicitHeight: planView.implicitHeight
        background: Rectangle {color: "transparent"}



        Pane {
            id: planView
            anchors.top: parent.top

            background: Rectangle {color: "transparent"}

            ColumnLayout {
                id: columnLayout
                property bool isExtended: true
                RowLayout {
                    id: header
                    TextField {
                        text: planModel ? planModel.name : ""
                        placeholderText: "Name"
                        onEditingFinished: () => {
                            focus = false
                            planModel.name = text
                        }
                        selectByMouse: true
                        onFocusChanged: {
                            if (focus)
                                selectAll()
                        }
                    }
                    Button {
                        text: "E"
                        onClicked: columnLayout.isExtended = !columnLayout.isExtended
                    }
                }
                TextField {
                    id: repetitionEdit
                    implicitWidth: 50
                    Layout.preferredHeight: columnLayout.isExtended? implicitHeight : 0
                    visible: columnLayout.isExtended
                    validator: IntValidator {
                        bottom: 1
                    }
                    placeholderText: "Repetitions"
                    text: planModel ? planModel.repetitions : ""
                    onEditingFinished: () => {
                        focus = false
                        planModel.repetitions = text
                                       }
                    selectByMouse: true
                    onFocusChanged: {
                        if (focus)
                            selectAll()
                    }
                }
                Button {
                    text: "Add Interval"
                    Layout.preferredHeight: columnLayout.isExtended? implicitHeight : 0
                    visible: columnLayout.isExtended
                    onClicked: root.planModel.appendInterval()
                }
                Button {
                    text: "Add Plan"
                    Layout.preferredHeight: columnLayout.isExtended? implicitHeight : 0
                    visible: columnLayout.isExtended
                    onClicked: root.planModel.appendPlan()
                }
                Button {
                    text: "Delete Plan"
                    Layout.preferredHeight: columnLayout.isExtended? implicitHeight : 0
                    visible: columnLayout.isExtended
                    onClicked: root.deletePlanModel()
                }
                Repeater {
                    id: repeater

                    Layout.preferredHeight: columnLayout.isExtended ? implicitHeight : 0
                    visible: columnLayout.isExtended
                    model: root.planModel
                    clip: false
                    delegate: RowLayout {
                        id: planLayout
                        required property bool isPlan
                        required property bool isInterval
                        required property var description
                        required property var duration
                        required property var subPlan
                        required property var index
                        required property var model
                        visible: columnLayout.isExtended
                        Loader {
                            active: planLayout.isInterval
                            visible: active
                            sourceComponent: RowLayout {
                                IntervalView {
                                    defaultDescription: planLayout.description
                                    defaultDuration: planLayout.duration
                                    onDescriptionChanged: (description) => {
                                                           console.error("Test", description)
                                                              model.description = description
                                                          }
                                    onDurationChanged: (duration) => model.duration = duration
                                    onDeleteInterval: root.planModel.removeItem(index)
                                }
                            }
                        }
                        Loader {
                            id: planLoader
                            active: planLayout.isPlan
                            visible: active
                            sourceComponent: childComponent
                            onLoaded: {
                                item.planModel = planLayout.subPlan
                            }
                        }
                        Connections {
                            enabled: planLayout.isPlan
                            target: planLoader.item
                            function onDeletePlanModel() {
                                root.planModel.removeItem(index)
                            }
                        }
                    }
                }
            }
        }
    }
}

import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import Intervaltimer 1.0
import Intervaltimer.Android 1.0

Frame {
    id: root
    property QtObject planModel: null
    property Component childComponent: null

    implicitWidth: layout.implicitWidth
    implicitHeight: layout.implicitHeight
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
                position: 0.1
                color: "teal"
            }

            GradientStop {
                position: 0.9
                color: "teal"
            }
            GradientStop {
                position: 1.0
                color: "aqua"
            }
        }
    }

    contentItem: Frame {
        id: layout

        implicitWidth: planView.width +repetitionEdit.width

        implicitHeight: planView.height + repetitionEdit.height
        TextField {
            id: repetitionEdit
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            width: 100
            validator: IntValidator {
                bottom: 1
            }
            placeholderText: "Repetitions"
            text: planModel ? planModel.repetitions : ""
            onEditingFinished: planModel.repetitions = text
            selectByMouse: true
            onFocusChanged: {
                if (focus)
                    selectAll()
            }
        }

        Frame {
            id: planView
            anchors.left: repetitionEdit.right
            anchors.top: parent.top
            anchors.leftMargin: 10
            ColumnLayout {
                id: columnLayout
                property bool isExtended: true
                RowLayout {
                    id: header
                    TextField {
                        text: planModel ? planModel.name : ""
                        placeholderText: "Name"
                        onEditingFinished: planModel.name = text
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
                ListView {
                    id: repeater
                    width: 500

                    Layout.preferredHeight: columnLayout.isExtended? implicitHeight : 0
                    implicitHeight: 200
                    model: root.planModel
                    clip: true
                    delegate: RowLayout {
                        id: planLayout
                        required property var name
                        required property bool isPlan
                        required property bool isInterval
                        required property var description
                        required property var duration
                        required property var subPlan
                        required property var index
                        required property var model

                        Loader {
                            active: planLayout.isInterval
                            visible: active
                            sourceComponent: RowLayout {
                                IntervalView {
                                    description: planLayout.description
                                    duration: planLayout.duration
                                    onDescriptionChanged: model.description = description
                                    onDurationChanged: model.duration = duration
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

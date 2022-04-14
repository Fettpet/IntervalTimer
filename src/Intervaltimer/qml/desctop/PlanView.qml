import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Intervaltimer
import Intervaltimer.Desctop

Frame {
    id: root
    property QtObject planModel: null
    property Component childComponent: null

    signal deletePlanModel

    background: Rectangle {
        width: layout.width * 1.1
        height: layout.height + 20
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

    contentItem: RowLayout {
        id: layout
        TextField {
            id: repetitionEdit

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

        ColumnLayout {

            RowLayout {
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
                RoundButton {
                    text: "Interval"
                    onClicked: root.planModel.appendInterval()
                }
                RoundButton {
                    text: "Plan"
                    onClicked: root.planModel.appendPlan()
                }
                RoundButton {
                    text: "X"
                    onClicked: root.deletePlanModel()
                }
            }
            Repeater {
                id: repeater
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
                            }
                            RoundButton {
                                text: "X"
                                onClicked: root.planModel.removeItem(index)
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

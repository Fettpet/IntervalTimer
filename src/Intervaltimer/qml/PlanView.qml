import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import Intervaltimer 1.0

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
        TextInput {
            id: repetitionEdit

            validator: IntValidator {
                bottom: 1
            }
            text: planModel ? planModel.repetitions : ""
            onEditingFinished: planModel.repetitions = text
        }

        ColumnLayout {
            RowLayout {
                TextInput {
                    text: planModel ? planModel.name : ""
                    onEditingFinished: planModel.name = text
                }
                Button {
                    text: "Interval"
                    onClicked: root.planModel.appendInterval()
                }
                Button {
                    text: "Plan"
                    onClicked: root.planModel.appendPlan()
                }
                Button {
                    text: "X"
                    onClicked: root.deletePlanModel()
                }
            }
            Repeater {
                id: repeater
                model: root.planModel

                clip: true
                delegate: RowLayout {
                    id: layout
                    required property var name
                    required property bool isPlan
                    required property bool isInterval
                    required property var description
                    required property var duration
                    required property var subPlan
                    required property var index
                    required property var model

                    Loader {
                        active: layout.isInterval
                        visible: active
                        sourceComponent: RowLayout {
                            IntervalView {
                                description: layout.description
                                duration: layout.duration
                                onDescriptionChanged: model.description = description
                                onDurationChanged: model.duration = duration
                            }
                            Button {
                                text: "X"
                                onClicked: root.planModel.removeItem(index)
                            }
                        }
                    }
                    Loader {
                        id: planLoader
                        active: layout.isPlan
                        visible: active
                        sourceComponent: childComponent
                        onLoaded: {
                            item.planModel = layout.subPlan
                        }
                    }
                    Connections {
                        enabled: layout.isPlan
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

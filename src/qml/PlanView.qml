import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import Intervaltimer 1.0

Frame {
    id: root
    property QtObject planModel: null
    property Component childComponent: null

    contentItem: RowLayout {
        Text {
            text: planModel ? planModel.repetitions : ""
        }

        ColumnLayout {
            implicitWidth: 250
            implicitHeight: 250
            RowLayout {
                Text {
                    text: planModel ? planModel.name : ""
                }
                Button {
                    text: "Interval"
                    onClicked: root.planModel.appendInterval()
                }
                Button {
                    text: "Plan"
                    onClicked: root.planModel.appendPlan()
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

                    Loader {
                        active: layout.isInterval
                        visible: active
                        sourceComponent: RowLayout {
                            IntervalView {
                                description: layout.description
                                duration: layout.duration
                            }
                            Button {
                                text: "X"
                                onClicked: root.planModel.removeItem(index)
                            }
                        }
                    }
                    Loader {
                        active: layout.isPlan
                        visible: active
                        sourceComponent: childComponent
                        onLoaded: {
                            item.planModel = layout.subPlan
                        }
                    }
                }
            }
        }
    }
}

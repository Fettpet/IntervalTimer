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
            text: planModel.repetitions
        }

        ColumnLayout {
            implicitWidth: 250
            implicitHeight: 250
            Text {
                text: planModel.name
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

    //contentItem: TreeView {// RowLayout {
    //     id: header
    //     TextField {
    //         id: name
    //         text: root.plan ? root.plan.getName() : ""
    //         onEditingFinished: root.plan.setName(text)
    //     }
    //     Button {
    //         text: "Interval"
    //         onClicked: root.plan.appendInterval()
    //     }
    //     Button {
    //         text: "Plan"
    //         onClicked: root.plan.appendPlan()
    //     }
    // }
    // ListView {
    //     id: viewIn

    //     delegate: RowLayout {
    //         id: delegate
    //         required property var model
    //         required property string description
    //         required property var duration
    //         required property bool isPlan
    //         required property bool isInterval
    //         required property QtObject subPlan

    //         Loader {
    //             active: delegate.isPlan
    //             visible: active
    //             sourceComponent: childComponent
    //             onLoaded: {
    //                 item.plan = delegate.subPlan
    //             }
    //         }
    //         Loader {
    //             active: delegate.isInterval
    //             visible: active
    //             sourceComponent: Interval {
    //                 description: delegate.description
    //                 duration: delegate.duration

    //                 onDescriptionChanged: {
    //                     model.description = description
    //                 }

    //                 onDurationChanged: {
    //                     model.duration = duration
    //                 }
    //             }
    //         }
    //     }
    // }
    // }
}

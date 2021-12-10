import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import Intervaltimer 1.0

Frame {
    id: root
    property QtObject plan: null
    property Component childComponent: null

    contentItem: ColumnLayout {

            RowLayout {
                id: header
                TextField {
                    id: name
                    text: root.plan ? root.plan.getName() : ""
                    onEditingFinished: root.plan.setName(text)
                }
                Button {
                    text: "Interval"
                    onClicked: root.plan.appendInterval()
                }
                Button {
                    text: "Plan"
                    onClicked: root.plan.appendPlan()
                }
            }
            ListView {
                id: viewIn
                implicitWidth: 250
                implicitHeight: 250
                clip: true

                model: PlanModel {
                    id: planModel
                    plan: root.plan
                }

                delegate: RowLayout {
                    id: delegate
                    required property string description
                    required property var duration
                    required property bool isPlan
                    required property bool isInterval
                    required property QtObject subPlan

                    Loader {
                        active: delegate.isPlan
                        visible: active
                        sourceComponent: childComponent
                        onLoaded: {
                             item.plan = delegate.subPlan
                        }
                    }
                    Loader {
                        active: delegate.isInterval
                        visible: active
                        sourceComponent: Interval {
                            description: delegate.description ? delegate.description : ""
                            duration: delegate.duration ? delegate.duration : ""
                        }
                    }
                }
            }
        }
}


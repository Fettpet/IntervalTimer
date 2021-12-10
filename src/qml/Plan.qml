import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import Intervaltimer 1.0

ColumnLayout {
    id: root
    required property var plan

    RowLayout {
        TextField {
            id: name
            text: root.plan ? root.plan.getName() : ""
            onEditingFinished: root.plan.setName(text)
        }
        Button {
            text: "Interval"
            onClicked: viewIn.appenInterval()
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

        function appenInterval() {
            console.error("Append Interval");
            root.plan.appendInterval()
        }

        delegate: RowLayout {
            id: delegate
            required property bool isPlan
            required property bool isInterval
            Text {
                enabled: delegate.isPlan;
                visible: enabled
                text: "Plan"
            }

            Frame {
                enabled: delegate.isInterval
                visible: enabled
                Interval {
                    description: "description"
                    duration: "duration"
                }
            }
        }
    }
}

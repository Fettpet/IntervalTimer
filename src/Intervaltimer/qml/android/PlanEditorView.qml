import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import Intervaltimer 1.0
import Intervaltimer.Android 1.0

Pane {
    id: root

    property QtObject planModel: null

    background: Rectangle {
        anchors.fill: parent
        color: "teal"
    }

    signal startRunning
    ColumnLayout {
        id: layout
        Loader {
            sourceComponent: planComponent
            onLoaded: item.planModel = planModel
        }

        Component {
            id: planComponent
            PlanView {
                childComponent: planComponent
            }
        }
        RowLayout {
            id: footer
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                text: "Save"
                onClicked: {
                    loaderStorePlan.open()
                    loaderLoadPlan.close()
                }
            }
            Button {
                text: "Load"
                onClicked: {
                    loaderLoadPlan.open()
                    loaderStorePlan.close()
                }
            }
            Button {
                text: "Run"
                onClicked: startRunning()
            }
        }

        StorePlanView {
            id: loaderStorePlan
            anchors.centerIn: layout
        }

        LoadPlanView {
            id: loaderLoadPlan
            anchors.centerIn: layout
        }
    }
}

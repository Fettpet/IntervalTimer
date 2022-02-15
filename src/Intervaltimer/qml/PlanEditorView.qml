import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import Intervaltimer 1.0

Frame {
    id: root
    property QtObject planModel: null

    signal startRunning
    ColumnLayout {
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
            anchors.centerIn: parent
        }

        LoadPlanView {
            id: loaderLoadPlan
            anchors.centerIn: parent
        }
    }
}

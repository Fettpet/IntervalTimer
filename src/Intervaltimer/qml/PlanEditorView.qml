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

        StorePlanView {
            id: loaderStorePlan
        }

        LoadPlanView {
            id: loaderLoadPlan
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
                }
            }
            Button {
                text: "Load"
                onClicked: {
                    loaderLoadPlan.open()
                }
            }
            Button {
                text: "run"
                onClicked: startRunning()
            }
        }
    }
}

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Intervaltimer
import Intervaltimer.Android

Window {
    id: root

    property bool isRunning: false
    required property var rootPlanModel
    title: qsTr("IntervalTimer")
    width: 640
    height: 480
    visible: true

    Pane {
        id: flickable

        width: root.width
        height: root.height
        clip: true
        padding: 0

        Loader {
            id: editorLoader
            active: !root.isRunning
            sourceComponent: PlanEditorView {
                id: planEditorView
                planModel: rootPlanModel
                width: root.width
                height: root.height
                onStartRunning: {
                    PlanRunner.start()
                    root.isRunning = true
                }
            }
        }
        Loader {
            id: runnerLoader
            active: root.isRunning
            sourceComponent: PlanRunningView {
                backgroundColor: "#111111"
                textColor: "#bbbbbb"
                width: root.width
                height: root.height
                onStopRunning: {
                    root.isRunning = false
                }
            }
        }
    }
}

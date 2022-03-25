import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import Intervaltimer 1.0
import Intervaltimer.Android 1.0

Window {
    id: root

    property bool isRunning: false

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
                planModel: PlanModel
                width: root.width
                height: root.height
                backgroundColor: "#111111"
                gradientColor: "#333333"
                footerColor: "#333333"
                popupColor: "#555555"
                textColor: "#bbbbbb"
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

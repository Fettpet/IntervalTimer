import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import Intervaltimer 1.0
import Intervaltimer.Desctop 1.0

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("IntervalTimer")
    property bool isRunning: false

    color: "teal"

    Flickable {
        id: flickable

        width: root.width
        height: root.height
        contentHeight: root.isRunning ? runnerLoader.height : editorLoader.height
        contentWidth: root.isRunning ? runnerLoader.width : editorLoader.width
        clip: true

        Loader {
            id: editorLoader
            active: !root.isRunning
            sourceComponent: PlanEditorView {
                id: planEditorView
                planModel: PlanModel
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
                width: root.width
                height: root.height
                onStopRunning: {
                    root.isRunning = false
                }
            }
        }
    }
}

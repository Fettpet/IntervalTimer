import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Intervaltimer

Popup {
    id: root
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    ColumnLayout {
        Label {
            text: "Über Intervaltimer"
        }
        Label {
            text: "Version " + ConstantStorage.projectVersionMajor + "."
                  + ConstantStorage.projectVersionMinor + "." + ConstantStorage.projectVersionPatch
        }
        Label {
            text: "Copyright 2022 HicknHack Software GmbH"
        }
        Label {
            text: "All rights reserved"
        }
    }
}

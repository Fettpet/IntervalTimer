import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Intervaltimer

Popup {
    id: root
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    ColumnLayout {
        Text {
            text: "Über Intervaltimer"
        }
        Text {
            text: "Version " + ConstantStorage.projectVersionMajor + "."
                  + ConstantStorage.projectVersionMinor + "." + ConstantStorage.projectVersionPatch
        }
        Text {
            text: "Copyright 2022 HicknHack Software GmbH"
        }
        Text {
            text: "All rights reserved"
        }
    }
}

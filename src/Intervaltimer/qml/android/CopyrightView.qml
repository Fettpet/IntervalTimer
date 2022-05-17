import QtQuick
import QtQuick.Controls

Popup {
    id: root
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    Label {
        textFormat: Text.StyledText
        text: "Copyright © 2022 <a href=\"https://www.hicknhack-software.com/\">Hicknhack Software GmbH</a> <br> All rights reserved."
    }
}

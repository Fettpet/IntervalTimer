import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Intervaltimer

Popup {
    id: root
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    ColumnLayout {
        Label {
            text: "Lizenz"
        }
        Label {
            text: "Dieses Produkt enthält Grafiken und Quellcode der folgenden Rechteinhaber:"
        }
        ToolSeparator {}
        Label {
            text: "Qt " + ConstantStorage.qtVersion
        }
        Label {
            textFormat: Text.StyledText
            text: "Licenced under GNU Lesser General Public License (<a href=\"https://www.gnu.org/licenses/lgpl-3.0.html\">LGPLv3</a>)"
            onLinkActivated: link => {
                                 Qt.openUrlExternally(link)
                             }
        }
        ToolSeparator {}
        Label {
            text: "The Qt Toolkit"
        }
        Label {
            textFormat: Text.StyledText
            text: "Copyright © 2022 The Qt Company Ltd. and other contributors (<a href=\"https://www.qt.io/licensing/\">Licencing</a>)"
            onLinkActivated: link => {
                                 Qt.openUrlExternally(link)
                             }
        }
    }
}

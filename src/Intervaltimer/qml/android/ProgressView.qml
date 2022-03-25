// Source https://stackoverflow.com/a/22903361
import QtQml
import QtQuick

Canvas {
    id: root
    antialiasing: true

    property color primaryColor: "orange"
    property color secondaryColor: "lightblue"
    property color textColor: "black"
    property color backgroundColor: "teal"
    width: 240
    height: 240
    property string text: "Text"

    property real minimumValueInner: 0
    property real maximumValueInner: 100
    property real currentValueInner: 33

    property real minimumValueOuter: 0
    property real maximumValueOuter: 100
    property real currentValueOuter: 33

    property int widthLineInner: 10
    property int widthLineOuter: 10

    // this is the angle that splits the circle in two arcs
    // first arc is drawn from 0 radians to angle radians
    // second arc is angle radians to 2*PI radians
    signal clicked

    onPrimaryColorChanged: requestPaint()
    onSecondaryColorChanged: requestPaint()
    onMinimumValueInnerChanged: requestPaint()
    onMaximumValueInnerChanged: requestPaint()
    onCurrentValueInnerChanged: requestPaint()
    onMinimumValueOuterChanged: requestPaint()
    onMaximumValueOuterChanged: requestPaint()
    onCurrentValueOuterChanged: requestPaint()

    onPaint: {
        var ctx = getContext("2d")
        ctx.save()

        ctx.clearRect(0, 0, root.width, root.height)
        ctx.fillStyle = root.backgroundColor
        ctx.rect(0, 0, root.width, root.height)
        // First, thinner arc
        // From angle to 2*PI
        ctx.beginPath()
        ctx.lineWidth = root.widthLineInner
        ctx.strokeStyle = primaryColor
        ctx.arc(_m.centerWidth, _m.centerHeight, _m.radiusInner,
                _m.angleOffset + _m.angleInner, _m.angleOffset + 2 * Math.PI)
        ctx.stroke()

        // Second, thicker arc
        // From 0 to angle
        ctx.beginPath()
        ctx.lineWidth = root.widthLineInner
        ctx.strokeStyle = root.secondaryColor
        ctx.arc(_m.centerWidth, _m.centerHeight, _m.radiusInner,
                _m.angleOffset, _m.angleOffset + _m.angleInner)
        ctx.stroke()

        // First, thinner arc
        // From angle to 2*PI
        ctx.beginPath()
        ctx.lineWidth = root.widthLineOuter
        ctx.strokeStyle = primaryColor
        ctx.arc(_m.centerWidth, _m.centerHeight, _m.radiusOuter,
                _m.angleOffset + _m.angleOuter, _m.angleOffset + 2 * Math.PI)
        ctx.stroke()

        // Second, thicker arc
        // From 0 to angle
        ctx.beginPath()
        ctx.lineWidth = root.widthLineOuter
        ctx.strokeStyle = root.secondaryColor
        ctx.arc(_m.centerWidth, _m.centerHeight, _m.radiusOuter,
                _m.angleOffset, _m.angleOffset + _m.angleOuter)
        ctx.stroke()

        ctx.restore()
    }

    Text {
        anchors.centerIn: parent

        text: root.text
        color: root.textColor
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        onClicked: root.clicked()
        onPressedChanged: root.requestPaint()
    }

    QtObject {
        id: _m
        property real centerWidth: root.width / 2
        property real centerHeight: root.height / 2

        property real radiusInner: Math.min(
                                       root.width - 3 * root.widthLineInner,
                                       root.height - 3 * root.widthLineInner) / 2
        property real angleInner: (root.currentValueInner - root.minimumValueInner)
                                  / (root.maximumValueInner - root.minimumValueInner) * 2 * Math.PI

        property real radiusOuter: Math.min(
                                       root.width - root.widthLineOuter,
                                       root.height - root.widthLineOuter) / 2
        property real angleOuter: (root.currentValueOuter - root.minimumValueOuter)
                                  / (root.maximumValueOuter - root.minimumValueOuter) * 2 * Math.PI

        // we want both circle to start / end at 12 o'clock
        // without this offset we would start / end at 9 o'clock
        property real angleOffset: -Math.PI / 2
    }
}

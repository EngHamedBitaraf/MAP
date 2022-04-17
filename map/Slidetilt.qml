import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
///custom slider tilt for map
    Slider {
        id :uzoom
        value: 0
        width: 200
        maximumValue: 100
        minimumValue: 0
        style:SliderStyle {
            groove: Rectangle {
                implicitHeight: 3
                color: "lightgrey"
                border {
                    color: "#999"
                    width: 1
                        }
                    radius: 10
                Rectangle {
                    implicitHeight: 3
                    color: "orange"
                    implicitWidth: styleData.handlePosition
                    border {
                        color: "#999"
                        width: 1
                    }
                        radius: 10
                }
            }
        }

        Text {
            y: -3
            width: 45
            height: 21
            color: "orange"
            anchors.left :  uzoom.right
            font.pointSize: 12
            anchors.leftMargin: 13
            anchors.horizontalCenter: uzoom

            text: qsTr("Titl")
        }
    }



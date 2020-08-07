import QtQuick 2.12
import QtQuick.Controls 2.5
import QtLocation 5.12
import QtPositioning 5.12

import Kea 1.0

Map {

    id: utmDisplay

    plugin: Plugin{
        name: "mapboxgl"
    }

    property variant topLeft: QtPositioning.coordinate(6.0524,10.1084)
    property variant bottomRight: QtPositioning.coordinate(6.0242,10.1437)
    property variant centerofMap: QtPositioning.coordinate(6.0379,10.1225)

    property variant screenView: QtPositioning.rectangle(topLeft, bottomRight)

    MapItemView{
        model: DroneModel{
            droneManager: DM
        }

        delegate: MapQuickItem{

            coordinate: QtPositioning.coordinate(Latitude, Longitude)
            anchorPoint.x: image.width
            anchorPoint.y: image.height/2;



            sourceItem: Grid{
                columns: 2
                Grid{
                    horizontalItemAlignment: Grid.AlignVCenter
                    columns: 1
                    Image {
                        id: image
                        source: "airplane.png"
                    }
                    Rectangle{
                        color: "lightblue"
                        width: registration.width * 1.4
                        height: registration.height * 1.4
                        border.width: 1
                        radius: 5
                        opacity: 1
                        Text {
                            id: registration
                            anchors.centerIn: parent
                            text: Registration
                            font.family: "Helvetica"; font.pointSize: 9;
                        }
                        MouseArea{
                           anchors.fill: parent
                           hoverEnabled: true
                           onEntered: {
                               drone_tooltip.start()
                           }
                        }
                    }
                }
                    /*Image {
                    id: imageAlt
                    source: "u.png"
                }*/
                Rectangle{ //Make this visible (opacity  = 1) when hovering over target image
                    id: drone_info
                    color: "lightblue"
                    width: alt.width * 1.4
                    height: alt.height * 1.4
                    border.width: 1
                    radius: 5
                    opacity: 0
                    Text {
                        id: alt
                        anchors.centerIn: parent
                        text: {
                            var text = Registration + " is at altitude " + Altitude + " meters"
                            return text}
                        font.family: "Helvetica"; font.pointSize: 11
                    }
                }
            }


            SequentialAnimation{
                id:drone_tooltip
                running: false

                NumberAnimation {
                    target: drone_info
                    property: "opacity"
                    to: 1.0
                    duration: 200
                    easing.type: Easing.InOutQuad
                }

                PauseAnimation {
                    duration: 1500
                }

                NumberAnimation {
                    target: drone_info
                    property: "opacity"
                    to: 0.0
                    duration: 200
                }
            }
        }
    }

    zoomLevel: 13
    //visibleRegion: screenView
    center: centerofMap


}

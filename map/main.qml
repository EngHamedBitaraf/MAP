import QtQuick 2.0
import QtQuick.Window 2.0
import QtLocation 5.12
import QtPositioning 5.12
import QtQuick.Shapes 1.1
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
Item {
    anchors.fill: parent
/// rectangel for display in widget
        Rectangle{
               anchors.fill: parent
               visible: true

     //        PositionSource {
     //            active: true
     //            onPositionChanged: {
     //                //map.center =position.coordinate;
     //                console.log("jfdkjg")
     //            }
     //        }
               /// address marker  in map
               Address {
                   id: address
                   street: "Narmak"
                   city: "Tehran"
                   country: "IRAN"
                   countryCode: "IR"
               }
             /// display map
             Map{
                 id:map
                 anchors.fill: parent
                 color: "gray"
                 /// plugin type map
                 plugin: Plugin {
                     name: "osm"//"itemsoverlay"//"mapbox"//"here" //"esri"//"mapboxgl"
                     /// type parametr plugin  =>>>> https://doc.qt.io/qt-5/location-plugin-osm.html
         //            PluginParameter{
         //                name:
         //                value:
         //            }
                 }
             // osm 5 type
                 activeMapType:supportedMapTypes[4]
                 center: QtPositioning.coordinate(52.520663,13.416552)
                 zoomLevel:uzoom.value
                 tilt: utile.value
                 bearing: ubearing.value
                 fieldOfView: ufov.value
                 ///item marker in map
                 MapQuickItem{
                     id: marker
                     coordinate:QtPositioning.coordinate(52.520663,13.416552)
                     sourceItem: Image {
                         visible: hide_show.checked
                         id: image
                         source: "qrc:/icons8-place-marker-48.png"
                          MouseArea{
                              id:mouse
                              anchors.fill: parent
                              onClicked: {
                                  toolTip.showToolTip =true
                              }
                          }
                        CustomTooltip{
                            id:toolTip
                            toolTip: "djksfhskjdfs"
                        }
                     }
                     anchorPoint.x :image.width /4
                     anchorPoint.y:image.height
                }
                 ///route item road in map

                 MapItemView{
                     model: routmodel
                     delegate: Component{
                         MapRoute{
                             route: routeData
                             line.color: "blue"
                             line.width: 4
                         }
                     }
                 }


     /// show circel
     //        MapCircle {
     //            color: "red"
     //            center: QtPositioning.coordinate(59.930243,10.714635)
     //            radius: 100
     //        }


             }
         // address to query
         GeocodeModel {
             plugin: map.plugin
             query: address
             onLocationsChanged: {
                 if (count)
                   marker.coordinate =get(0).coordinate;
                 map.center.latitude = get(0).coordinate.latitude
                 map.center.longitude = get(0).coordinate.longitude
             }
             Component.onCompleted:update()

        }
         // show route
         RouteModel{
             id :routmodel
             plugin: map.plugin
             query: RouteQuery {id : routquery}
             Component.onCompleted: {
                     routquery.addWaypoint(QtPositioning.coordinate(35.7178984,51.4905671));
                     routquery.addWaypoint(QtPositioning.coordinate(52.432053,13.535652));
                 update();

                 }
         }
     }
        /// featuer map zoom , tite , ....
        ColumnLayout{
        Slidezoom{
            id:uzoom
        }
        Slidetilt{
            id :utile }
        Sliderbearing{id:ubearing}
        SliderFov{id:ufov}
        CheckBox{
            id: hide_show
            checked: true
            text: "Show"

        }
        }


}

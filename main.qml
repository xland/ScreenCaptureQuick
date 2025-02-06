import QtQuick
import QtQuick.Window

Window {
    id:root
    visible: true
    color: "transparent"
    title: "ScreenCapture"

    Image {
        id: backgroundImage
        source: "image://ProviderImgScreen/background"
        anchors.fill: parent
    }
    MouseArea {
        anchors.fill: parent
        onPressed: mouse => {
            //console.log("allen");
            //root.width += 100;
            //root.height += 100;
        }
    }
}

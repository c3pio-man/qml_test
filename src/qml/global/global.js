function dp(v) {
    return Math.round((v * DeviceInfoProvider.getDpi() * DeviceInfoProvider.getScaleFactor()) / 160);
}

function scrollPageUp(list_view) {
    if(!list_view.atYBeginning) {
        if(list_view.visibleArea.yPosition - 0.9 * list_view.visibleArea.heightRatio < 0) {
            list_view.positionViewAtBeginning()
        } else {
            list_view.contentY -= list_view.height * 0.9
        }
    }
    list_view.returnToBounds()
}

function scrollPageDown(list_view) {
    if(!list_view.atYEnd) {
        if(list_view.visibleArea.yPosition + 0.9 * list_view.visibleArea.heightRatio > 1.0 - list_view.visibleArea.heightRatio) {
            list_view.positionViewAtEnd()
        } else {
            list_view.contentY += list_view.height * 0.9
        }
    }
    list_view.returnToBounds()
}

function formatSecondsAsTime(seconds) {
    var h = Math.floor(seconds / 3600);
    var m = Math.floor((seconds - (h * 3600))/60);
    var s = Math.floor(seconds - (h * 3600) - (m * 60));

    if(h === 0) {
        return ('0' + m).slice(-2) + ':' + ('0' + s).slice(-2);
    } else {
        return h + ':' + ('0' + m).slice(-2) + ':' + ('0' + s).slice(-2);
    }
}

function prettifyFolderName(folder_name) {
    var text = folder_name
    var pattern = /^file:\/\/\/mnt\/ext1/gi
    if(!DeviceInfoProvider.isEmulator()) {
        pattern = /^file:\/\/\/mnt\/ext1/gi
        text = text.replace(pattern, qsTr("@DeviceMemory"));
        pattern = /^file:\/\/\/mnt\/ext2/gi
        text = text.replace(pattern, qsTr("@SDcard"));
        pattern = /^\/mnt\/ext1/gi
        text = text.replace(pattern, qsTr("@DeviceMemory"));
        pattern = /^\/mnt\/ext2/gi
        text = text.replace(pattern, qsTr("@SDcard"));
        return text
    } else {
        pattern = /^file:system\/mnt\/ext1/gi
        text = text.replace(pattern, qsTr("@DeviceMemory"));
        pattern = /^file:system\/mnt\/ext2/gi
        text = text.replace(pattern, qsTr("@SDcard"));
        pattern = /^(.*)system\/mnt\/ext1/gi
        text = text.replace(pattern, qsTr("@DeviceMemory"));
        pattern = /^(.*)system\/mnt\/ext2/gi
        text = text.replace(pattern, qsTr("@SDcard"));
        return text
    }
}

function getSpecialFolderName(name) {
    if(name === "./system/mnt/ext1"
            || name === "/mnt/ext1"
            || name === "file:system/mnt/ext1"
            || name === "file:///mnt/ext1") {
        return qsTr("@DeviceMemory")
    }

    if(name === "./system/mnt/ext2"
            || name === "/mnt/ext2"
            || name === "file:system/mnt/ext2"
            || name === "file:///mnt/ext2") {
        return qsTr("@SDcard")
    }

    return name
}

function openContextMenu(context_menu, menu_items, transparent_rect) {
    context_menu.visible = true
    context_menu.item.menuItems = menu_items
    context_menu.item.transparentRect = transparent_rect
    context_menu.item.show()
}

function openPopupMenu(popup_menu, menu_items, transparent_rect, type, uppercase) {
    popup_menu.visible = true
    popup_menu.item.menuItems = menu_items
    popup_menu.item.transparentRect = transparent_rect
    popup_menu.item.state = type
    if(uppercase) {
        popup_menu.item.font.capitalization = Font.AllUppercase;
    }
    popup_menu.item.show()
}

function openConfirmationDialog(confirmation_dialog, title, callback) {
    confirmation_dialog.visible = true;
    confirmation_dialog.callback = callback;
    confirmation_dialog.item.title = title;
}

var defaultNormalImagesPrefix = "image://resource/"
var defaultInvertedImagesPrefix = "image://resource_inv/"

function getNormalImage(imageName) {
    return defaultNormalImagesPrefix + imageName
}

function getInvertedImage(imageName) {
    return defaultInvertedImagesPrefix + imageName
}

/**
 *
 * Manage the content-related events
 *
 **/


// Get the required modules
const { ipcMain, BrowserWindow } = require("electron");

// Wait for the "window-close" event
ipcMain.on("window-close", (event, args) => {

    BrowserWindow.getFocusedWindow().close();

});

// Wait for the "window-min" event
ipcMain.on("window-min", (event, args) => {

    BrowserWindow.getFocusedWindow().minimize();

});

// Wait for the "window-max" event
ipcMain.on("window-max", (event, args) => {

    var win = BrowserWindow.getFocusedWindow();

    if (win.isMaximized()) {

        win.unmaximize();

    } else {

        win.maximize();

    }

});

// Wait for the "window-ready" event
ipcMain.on("window-ready", (event, args) => {

    if (module.exports.windowLoaded != null) {

        module.exports.windowLoaded();

    }

});

module.exports = {

    windowLoaded: null

};
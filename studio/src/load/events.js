/**
 *
 * Manage the content-related events
 *
 **/


// Get the required modules
const { ipcMain, BrowserWindow } = require("electron");
const { loadWindow } = require("./window-manager");
const { showWindow } = require("./windows");
const fs = require("fs");

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

// Wait for the "get-data" event
ipcMain.on("get-data", (event, args) => {

    const data = {

        app: false,
        settings: false,
        editorSettings: false,
        ...args

    };

    event.sender.send("get-data-reply", {

        app: data.app ? (JSON.parse(fs.readFileSync("./data/app.json").toString())) : null,
        settings: data.settings ? JSON.parse(fs.readFileSync("./data/settings.json").toString()) : null,
        editorSettings: data.editorSettings ? JSON.parse(fs.readFileSync("./data/editor.settings.json").toString()) : null

    });

});

// Wait for the "show-alert" event
ipcMain.on("show-alert", (event, args) => {

    loadWindow.alert(args.title, args.message, args.type, BrowserWindow.fromId(event.sender.id), function(window) {

        window.once("ready-to-show", function() {

            showWindow(window, function() {}, false, 0);

        });

        window.on("close", function() {

            event.sender.send("show-alert-reply", undefined);

        });

    });

});

module.exports = {

    windowLoaded: null

};
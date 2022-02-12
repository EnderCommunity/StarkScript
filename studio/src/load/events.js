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
const path = require("path");
const chokidar = require('chokidar');

// Wait for the "window-close" event
ipcMain.on("window-close", (event, args) => {

    BrowserWindow.fromWebContents(event.sender).close();

});

// Wait for the "window-min" event
ipcMain.on("window-min", (event, args) => {

    BrowserWindow.fromWebContents(event.sender).minimize();

});

// Wait for the "window-max" event
ipcMain.on("window-max", (event, args) => {

    var win = BrowserWindow.fromWebContents(event.sender);

    if (win.isMaximized()) {

        win.unmaximize();

    } else {

        win.maximize();

    }

});

// Wait for the "window-ready" event
ipcMain.on("main-window-ready", (event, args) => {

    if (module.exports.studio.mainWindowLoaded != null) {

        module.exports.studio.mainWindowLoaded();

        module.exports.studio.mainWindowLoaded = null;

    }

});

// Wait for the "get-data" event
ipcMain.on("get-data", (event, args) => {

    const data = {

        app: false,
        settings: false,
        editorSettings: false,
        ...args[1]

    };

    console.log(data);

    event.sender.send("get-data-reply-" + args[0], {

        app: data.app ? (JSON.parse(fs.readFileSync("./data/app.json").toString())) : null,
        settings: data.settings ? JSON.parse(fs.readFileSync("./data/settings.json").toString()) : null,
        editorSettings: data.editorSettings ? JSON.parse(fs.readFileSync("./data/editor.settings.json").toString()) : null

    });

});

// Wait for the "show-alert" event
ipcMain.on("show-alert", (event, args) => {

    // Open an alert window
    loadWindow.alert(args[1].title, args[1].message, args[1].type, BrowserWindow.fromId(event.sender.id), function(window) {

        // Wait for the window to be ready for the user to see
        window.once("ready-to-show", function() {

            showWindow(window, function() {}, false, 0);

        });

        // Alert the process that requested this alert window about it being closed
        window.on("close", function() {

            event.sender.send("show-alert-reply-" + args[0], undefined);

        });

    });

});

// Wait for the "show-about" event
ipcMain.on("show-about", (event, args) => {

    // Open the "about" window
    loadWindow.about(BrowserWindow.fromId(event.sender.id), function(window) {

        // Wait for the window to be ready for the user to see
        window.once("ready-to-show", function() {

            showWindow(window, function() {}, false, 0);

        });

        // Alert the process that requested this window about it being closed
        window.on("close", function() {

            event.sender.send("show-about-reply-" + args[0], undefined);

        });

    });

});

// Wait for the "open-editor" event
ipcMain.on("open-editor", (event, args) => {

    // Open an editor window
    loadWindow.editor(args[1], function(window) {

        // Wait for the window to be ready for the user to see
        window.once("ready-to-show", function() {

            showWindow(window, function() {}, false, 0);

        });

        // Alert the process that requested this window about it being closed
        window.on("close", function() {

            event.sender.send("open-editor-reply-" + args[0], undefined);

        });

    });

});

// Wait of the "fs-read-dir" event
ipcMain.on("fs-read-dir", (event, args) => {

    // Define the return object
    var result = {

        files: [],
        folders: []

    };

    // Read the direcotry
    fs.promises.readdir(args[1]).then(filenames => {

        // Sort the results
        for (let filename of filenames) {

            if (fs.statSync(path.join(args[1], filename)).isDirectory()) {

                result.folders.push(filename);

            } else {

                result.files.push(filename);

            }

        }

        event.sender.send("fs-read-dir-reply-" + args[0], result);

    });

});

// Wait of the "fs-read-dir" event
ipcMain.on("fs-read-file", (event, args) => {

    // Check if the file exists
    if (fs.existsSync(args[1][0])) {

        // Read the file
        fs.readFile(args[1][0], args[1][1], function(err, data) {

            if (err) {

                throw err;

            }

            // Return the file data
            event.sender.send("fs-read-file-reply-" + args[0], false, data);

        });

    } else {

        // Return an error code
        event.sender.send("fs-read-file-reply-" + args[0], true, null);

    }

});

// Wait of the "path-get-absolute" event
ipcMain.on("path-get-absolute", (event, args) => {

    // Return the absolute path
    event.sender.send("path-get-absolute-reply-" + args[0], path.resolve(args[1]).replace(/\\/g, "/"));

});

// Wait of the "fs-watch" event
ipcMain.on("fs-watch", (event, args) => {

    var watcher = chokidar.watch(args[1], { ignored: /^\./, persistent: true });

    // Link all the events
    // [add: 0] [unlink: 1] [change: 2] [error: 3]
    watcher
        .on('add', function(path) {

            event.sender.send("fs-watch-reply-" + args[0], 0, path.replace(/\\/g, "/"));

        })
        .on('change', function(path) {

            event.sender.send("fs-watch-reply-" + args[0], 2, path.replace(/\\/g, "/"));

        })
        .on('unlink', function(path) {

            event.sender.send("fs-watch-reply-" + args[0], 1, path.replace(/\\/g, "/"));

        })
        .on('error', function(error) {

            event.sender.send("fs-watch-reply-" + args[0], 3, error);

            throw error;

        })

});

// Wait for the "window-close" event
ipcMain.on("window-set-background", (event, args) => {

    var win = BrowserWindow.fromWebContents(event.sender);

    win.setBackgroundColor(args);
    win.blur();
    win.focus();

});

module.exports = {

    studio: null

};
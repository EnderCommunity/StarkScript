/**
 *
 * The windows manager
 *
 **/


// Import all the needed modules
const { BrowserWindow } = require('electron');
const { hideWindow } = require("./windows");

// Use this:
// https://www.npmjs.com/package/glasstron

// Define a function that can create windows with frames
function createWindow(properties) {

    // Create the window
    const win = new BrowserWindow({

        frame: false,
        alwaysOnTop: false,
        center: true,
        resizable: true,
        movable: true,
        minimizable: true,
        maximizable: true,
        closable: true,
        fullscreenable: false,
        skipTaskbar: false,
        hasShadow: true,
        focusable: true,
        title: "StarkStudio",
        width: 640,
        height: 420,
        minWidth: 120,
        minHeight: 80,
        show: false,
        paintWhenInitiallyHidden: true,
        titleBarStyle: 'hidden',

        // Temp
        // titleBarOverlay: {
        //
        //     color: '#000000',
        //     symbolColor: '#ffffff'
        //
        // },

        webPreferences: {

            devTools: true, // Change this to "false"
            preload: `${__dirname}/preload.js`,
            sandbox: true,
            webSecurity: true,
            imageAnimationPolicy: "noAnimation",
            webgl: false,
            backgroundThrottling: true,
            autoplayPolicy: "user-gesture-required",
            accessibleTitle: "Stark Studio",
            spellcheck: false,
            enableWebSQL: false

        },

        // Add the custom properties to this object
        ...properties

    });

    // Hide the menu
    win.setMenu(null);

    // Add the window events
    win.on("maximize", function() {

        // Manage the "on-window-max" event
        win.send("max-change", true);

    });
    win.on("unmaximize", function() {

        // Manage the "on-window-max" event
        win.send("max-change", false);

    });

    // Return the window object
    return win;

}

// Define the object that this file will return
module.exports = {

    lang: null,
    loadWindow: {

        main: function(callback) {

            // Create a window
            var window = createWindow({

                width: 700,
                height: 520,
                minWidth: 700,
                minHeight: 520

            });

            // Load the main layout
            window.loadFile(`./app/local-view/${module.exports.lang}/main.view.html`);

            // Pass the window object to the callback function
            callback(window);

        },
        editor: function(folder, callback) {

            // Create a window
            var window = createWindow({

                width: 900,
                height: 620,
                minWidth: 800,
                minHeight: 540,
                maximize: true

            });

            window.shouldMaximize = true;

            // Load the main layout
            window.loadFile(`./app/local-view/${module.exports.lang}/editor.view.html`);

            // Pass the window object to the callback function
            callback(window);

        },
        alert: function(title, message, type, parent, callback) {

            // Create a window
            var window = createWindow({

                width: 420,
                height: 200,
                minWidth: 420,
                minHeight: 200,
                maximizable: false,
                minimizable: false,
                resizable: false,
                parent: parent,
                modal: true

            });

            // Load the main layout
            window.loadFile(`./app/local-view/${module.exports.lang}/alert.view.html`);

            // Pass the window object to the callback function
            callback(window);

        },
        about: function(parent, callback) {

            // Create a window
            var window = createWindow({

                width: 400,
                height: 360,
                minWidth: 400,
                minHeight: 360,
                maximizable: false,
                minimizable: false,
                resizable: false,
                parent: parent,
                modal: true

            });

            // Load the main layout
            window.loadFile(`./app/local-view/${module.exports.lang}/about.view.html`);

            // Pass the window object to the callback function
            callback(window);

        }

    }

};
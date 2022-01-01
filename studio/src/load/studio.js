/**
 *
 * The studio initial loader
 *
 **/


// Get the required moduels for the inital start
const { showWindow, closeWindow } = require("./windows");
const manager = require("./window-manager");
const { getSettings } = require("./settings");

// Define the studio settings variable
var studioSettings;

// Define a variable to store all the windows that this program will use
var windows = {

    splash: null,
    alert: null,
    about: null,
    main: null,
    editors: []

};

// Define a function that will wait for all the windows to fully load
var initalWindows = 4,
    loadedInitalWindows = 0;

function checkInitalWindows() {

    if (++loadedInitalWindows == initalWindows) {

        // Close the splash screen
        closeWindow(windows.splash);

        // Temp
        showWindow(windows.editors[0], function() {}, false);
        windows.editors[0].openDevTools();
        setTimeout(function() {
            showWindow(windows.main, function() {}, false);
            windows.main.openDevTools();
            setTimeout(function() {
                showWindow(windows.about, function() {}, false);
                setTimeout(function() {
                    showWindow(windows.alert, function() {}, false);
                }, 500);
            }, 500);
        }, 500);

    }

}


// Define the object that this file will return
module.exports = {

    loadStudio: function(splashWindow) {

        // Set up the content-related events
        require(`${__dirname}/events.js`).windowLoaded = checkInitalWindows;

        // Store the splash widnow object
        windows.splash = splashWindow;

        // Load the settings
        studioSettings = getSettings();

        manager.lang = studioSettings.lang;

        // Start loading all the windows
        manager.loadWindow.Editor("./", function(window) {

            // Save the window object
            windows.editors.push(window);

            // Wait for the window to finish loading
            window.webContents.once('did-finish-load', function() {

                //checkInitalWindows();

            });

        });
        manager.loadWindow.Main(function(window) {

            // Save the window object
            windows.main = window;

            // Wait for the window to finish loading
            window.webContents.once('did-finish-load', function() {

                //checkInitalWindows();

            });

        });
        manager.loadWindow.About(windows.main, function(window) {

            // Save the window object
            windows.about = window;

            // Wait for the window to finish loading
            window.webContents.once('did-finish-load', function() {

                //checkInitalWindows();

            });

        });
        manager.loadWindow.Alert("title", "message", "type", windows.main, function(window) {

            // Save the window object
            windows.alert = window;

            // Wait for the window to finish loading
            window.webContents.once('did-finish-load', function() {

                //checkInitalWindows();

            });

        });

    }

}
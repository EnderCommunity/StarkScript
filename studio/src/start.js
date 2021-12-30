/**
 *
 * The start file
 *
 **/


// Get the required moduels for the inital start
const { app, BrowserWindow } = require('electron');
const { hideWindow, showWindow } = require("./load/windows");
const { loadStudio } = require("./load/studio");

// Define a function that can create the splash screen
function createSplash(callback) {

    // Create the window
    const win = new BrowserWindow({

        frame: false,
        alwaysOnTop: true,
        center: true,
        resizable: false,
        movable: false,
        minimizable: false,
        maximizable: false,
        closable: false,
        fullscreenable: false,
        skipTaskbar: true,
        hasShadow: true,
        focusable: false,
        opacity: 0,
        title: "Stark Studio",
        width: 640,
        height: 420

    });

    // Load the splash file
    win.loadFile('view://splash!0');

    // Hide the window properly
    hideWindow(win);

    // Wait for the splash window to load
    win.webContents.once('did-finish-load', function() {

        // Show the splash window
        showWindow(win, callback);

    });

    // Return the window object
    return win;

}

// Wait for Electron to get ready
app.whenReady().then(() => {

    // Show the splash screen
    const splashWindow = createSplash(function() {

        // Load up the studio
        loadStudio(splashWindow);

    });

    app.on('activate', () => {

        if (BrowserWindow.getAllWindows().length === 0) {

            // Load up the studio
            loadStudio(splashWindow);

        }

    });

});

// Check if all the windows are closed
app.on('window-all-closed', () => {

    // Close the app when all the windows are closed on Windows and Linux
    if (process.platform !== 'darwin') {

        app.quit();

    }

});
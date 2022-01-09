/**
 *
 * Manage the window's content
 *
 **/


// Get the required modules
const { contextBridge, ipcRenderer } = require("electron");

// Expose protected methods that allow the renderer process to use
// the ipcRenderer without exposing the entire object
const electronAPI = {

    require: function(module) {

        var modulesWhitelist = [],
            isWhitelisted = false;

        modulesWhitelist.forEach(name => {

            if (name == module) {

                isWhitelisted = true;

            }

        });

        if (isWhitelisted) {

            return require(module);

        } else {

            throw new Error("Unsafe module has been detected!");

        }

    },
    send: (channel, data) => {

        ipcRenderer.send(channel, data);

    },
    receive: (channel, callback) => {

        ipcRenderer.on(channel, (event, ...args) => callback(...args));

    },
    tell: (channel, data, callback) => {

        // Send the data
        ipcRenderer.send(channel, data);

        // Wait for the callback
        if (typeof callback == "function") {

            ipcRenderer.once(channel + "-reply", (event, ...args) => callback(...args));

        }

    },
    alert: (title, type, message, callback = null) => {

        electronAPI.tell("show-alert", {

            title: title,
            type: type,
            message: message

        }, callback);

    },
    alertType: {

        info: 0,
        warn: 1,
        error: 2

    }

};
contextBridge.exposeInMainWorld("electron", electronAPI);
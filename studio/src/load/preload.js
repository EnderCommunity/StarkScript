/**
 *
 * Manage the window's content
 *
 **/


// Get the required modules
const { contextBridge, ipcRenderer, remote } = require("electron");

// Expose protected methods that allow the renderer process to use
// the ipcRenderer without exposing the entire object
contextBridge.exposeInMainWorld(
    "electron", {

        send: (channel, data) => {

            ipcRenderer.send(channel, data);

        },
        receive: (channel, callback) => {

            ipcRenderer.on(channel, (event, ...args) => callback(...args));

        }
    }
);
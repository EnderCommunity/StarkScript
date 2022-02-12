/**
 *
 * Manage the window's content
 *
 **/


// Get the required modules
const { contextBridge, ipcRenderer } = require("electron");
// const { fs } = require("fs");

// Expose protected methods that allow the renderer process to use
// the ipcRenderer without exposing the entire object
var maxTellID = 0;
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
        tell: (channel, data, callback, keep = false) => {

            // Get the ID of this call
            const id = maxTellID++;

            // Check if the channel is supported by this function
            var isAllowed = false;
            [
                "get-data",
                "show-alert",
                "show-about",
                "fs-read-dir",
                "fs-read-file",
                "fs-watch",
                "open-editor",
                "path-get-absolute"
            ].forEach(function(name) {

                if (name == channel) {

                    isAllowed = true;

                }

            });

            if (isAllowed) {

                // Send the data
                ipcRenderer.send(channel, [id, data]);

                // Wait for the callback
                if (typeof callback == "function") {

                    ipcRenderer[(keep) ? "on" : "once"](channel + "-reply-" + id, (event, ...args) => callback(...args));

                }

            } else {

                throw new Error("Unsupported channel!");

            }

        },
        getData: (options, callback) => {

            electronAPI.tell("get-data", options, callback);

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

        },
        filesSystem: {

            readDir: (dir, callback) => {

                electronAPI.tell("fs-read-dir", String(dir), callback);

            },

            readFile: (dir, callback, format = "utf8") => {

                electronAPI.tell("fs-read-file", [String(dir), String(format)], callback);

            },

            observer: {

                trigger: {

                    // [add: 0] [unlink: 1] [change: 2] [error: 3]
                    add: 0,
                    unlink: 1,
                    change: 2,
                    error: 3

                },

                linkPath: (dir, callback) => {

                    electronAPI.tell("fs-watch", String(dir), callback, true);

                }

            },

            path: {

                getAbsolute: (path, callback) => {

                    electronAPI.tell("path-get-absolute", path, callback);

                }

            }

        }

    },
    toolsAPI = {

        getValue: (name) => {

            var result = location.search.substring(location.search.indexOf(name) + name.length + 1);

            if (result.indexOf("&") != 0) {

                result.substring(0, result.indexOf("&"));

            }

            return decodeURI(result);

        },
        getLocalString: (lang, path) => {

            if (localStrings == null) {

                return path;

            } else {

                return (function() {

                    if (typeof localStrings[lang] == "object") {

                        var tmp = localStrings[lang][path.substring(0, path.indexOf(":"))];

                        if (typeof tmp == "object") {

                            var pathArray = path.substring(path.indexOf(":") + 1).split(".");
                            for (var i = 0; i < pathArray.length; i++) {

                                tmp = tmp[pathArray[i]];

                                if (tmp == undefined) {

                                    break;

                                }

                            }

                            delete pathArray;

                            if (typeof tmp == "string") {

                                return tmp;

                            } else {

                                return "INVALID_PATH::" + path;

                            }

                        } else {

                            return "INVALID_BASE::" + path;

                        }

                        delete tmp;

                    } else {

                        return "INVALID_LANG::" + path;

                    }

                })();

            }

        }

    };
var localStrings = null;
electronAPI.filesSystem.readFile(`./app/local.json`, function(didFail, data) {

    if (!didFail) {

        localStrings = JSON.parse(data);

    } else {

        throw new Error("Couldn't load local strings!");

    }

});

contextBridge.exposeInMainWorld("electron", electronAPI);
contextBridge.exposeInMainWorld("tools", toolsAPI);
contextBridge.exposeInMainWorld("$$", function(string) {

    if (typeof settings.lang == "string") {

        return toolsAPI.getLocalString(settings.lang, string);

    } else {

        return toolsAPI.getLocalString("en", string);

    }

});

var settings = {};
electronAPI.getData({

    settings: true

}, function(data) {

    settings = data.settings;

});
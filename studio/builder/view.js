/**
 *
 * Manage "view" files
 *
 **/


// Get the required modules
const { errorMonitor } = require("events");
const fs = require("fs");

// Get the content of the "frame.html" file
const windowFrame = fs.readFileSync("./src/interface/frame.html").toString();

// Define a function that can process the <window> element's attributes
function processPreferences(attributes) {

    // Define the return object
    var windowSettings = {};

    // Separate all the attributes
    attributes.replace(/(.*?)="(.*?)"/g, function(attributeMatch, attributeName, attributeValue) {

        windowSettings[attributeName.replace(/\s|\n/g, "")] = (function() {

            if (attributeValue == "false" || attributeValue == "0" || attributeValue == "no") {

                return false;

            } else if (attributeValue == "true" || attributeValue == "1" || attributeValue == "yes") {

                return true;

            } else {

                return attributeValue;

            }

        })();

    });

    // Return the "window settings"
    return windowSettings;

}

// Define a function that can process special properties inside the "frame.html" file
function processProp(name, windowSettings) {

    if (name == "title") {

        return (windowSettings.title != undefined) ? `${windowSettings.title} | $\${app:title}` : "$${app:title}";

    } else if (name == "titleDisplay") {

        return (windowSettings["show-title"]) ? "block" : "none";

    } else if (name == "controlsHideDisplay") {

        return (windowSettings["enable-min"]) ? "block" : "none";

    } else if (name == "controlsMaxDisplay") {

        return (windowSettings["enable-max"] && !windowSettings["start-max"]) ? "block" : "none";

    } else if (name == "controlsUnmaxDisplay") {

        return (windowSettings["enable-max"] && windowSettings["start-max"]) ? "block" : "none";

    } else if (name == "controlsCloseDisplay") {

        return (windowSettings["enable-close"]) ? "block" : "none";

    } else {

        throw new Error(`Unknown frame property! (${name})`);

    }

}

// Define a function that can return the code that should be inserted in the CSS section
function insertCSS(innerContent) {

    var stylesheetsString = '',
        matches = innerContent.match(/<stylesheet(.*?)\/>/g) || [];

    for (var i = 0; i < matches.length; i++) {

        stylesheetsString += matches[i].replace("<stylesheet", `<link rel="stylesheet" `).replace("/>", ">\n");

    }

    return stylesheetsString;

}

// Define a function that can return the code that should be inserted in the JS section
function insertJS(innerContent) {

    var scriptsString = '',
        matches = innerContent.match(/<javascript(.*?)\/>/g) || [];

    for (var i = 0; i < matches.length; i++) {

        scriptsString += matches[i].replace("<javascript", `<script ${(matches[i].indexOf("type") == -1) ? "type=\"text/javascript\"" : ""} `).replace("/>", "></script>\n");

    }

    return scriptsString;

}

// Define a function that can return the code that should be inserted in the Content section
function insertContent(innerContent) {

    var matches = innerContent.match(/<content>(.*?)<\/content>/g) || ["<content>Empty Window!</content>"];
    return matches[0].substring("<content>".length, matches[0].length - "</content>".length);

}

// Get the depth of a file relative to the "root"/start directory
function calcDepth(path) {

    return path.substring("./src/".length).split("/").length - 1;

}

// Get the relative path of a file
function getRelativeStudio(path) {

    // Define the return string
    var relativeStart = "./";

    // Start calculating the depth of this file
    var depth = calcDepth(path);

    // Generate the relative start string
    for (var i = 0; i < depth; i++) {

        relativeStart += "../"

    }

    // Return the start string
    return relativeStart;

}

// Get the final relative path of the "node_modules" folder
function getRelativeNodeModules(path) {

    // Define the return string
    var relativeStart = "./";

    // Start calculating the depth of this file
    var depth = calcDepth(path) + 1;

    // Generate the relative start string
    for (var i = 0; i < depth; i++) {

        relativeStart += "../"

    }

    // Return the start string
    return `${relativeStart}node_modules/`;

}

// Define the exports object for this module
module.exports = {

    // Process "view" files
    viewProcessor(content, path) {

        // Define an object to keep track of the preferences of this "view" file
        var windowSettings = {};

        // Return the processed content
        return content.

        // Replace the end-of-line characters so they won't interfere with the regex lookups
        replace(/\r|\n/g, function(match) {

            return `&esc;${(match == "\n") ? "n" : "r"}&`;

        }).

        // Replace the <window> element with the content of the "frame.html" file
        replace(/<window(.*?)>(.*?)<\/window>/, function(match, attributes, innerContent) {

            // Process the window's preferences
            windowSettings = processPreferences(attributes);

            // Return the content of this <window> element inside a window frame
            return windowFrame.

            // Apply settings-related changes to the frame
            replace(/prop::(.*?):/g, function(match, name) {

                return processProp(name, windowSettings);

            }).

            // Insert content into the frame
            replace(/<!-- @insert::(.*?) -->/g, function(insertMatch, insertType) {

                if (insertType == "CSS") {

                    return insertCSS(innerContent);

                } else if (insertType == "JAVASCRIPT") {

                    return insertJS(innerContent);

                } else if (insertType == "CONTENT") {

                    return insertContent(innerContent);

                } else {

                    throw new Error(`Unknown insert command! (${insertType})`);

                }

            });

        }).

        // Re-add the end-of-line characters
        replace(/&esc;(n|r)&/g, function(match, type) {

            return (type == "n") ? "\n" : "\r";

        });

    },

    pathsProcessor(content, path) {

        // Return the processed content
        return content.

        // Replace all the "custom protocols"
        replace(/(studio|node_modules):\/\//g, function(match, protocol) {

            // Check the protocol type
            if (protocol == "studio") {

                // Get the final relative path of this file
                return getRelativeStudio(path);

            } else {

                // Get the final relative path of the "node_modules" folder
                return getRelativeNodeModules(path);

            }

        });

    }

};
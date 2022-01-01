/**
 *
 * Manage the input directory ("/src")
 *
 **/


// Get the required modules
const fs = require("fs");
const { viewProcessor } = require("./view");

// Define a variable to keep track of the timeout status of the files search
var searchTimeout = -1;

// Define the constants that hold the reading mode values for the "readR" function
const R_READ_FILES = 0,
    R_READ_FOLDERS = 1;

// Define a recursive function that can read the src directory
function readR(dir, callback, timeoutFunction, mode = R_READ_FILES) {

    // Read the "/src" directory
    fs.readdir(dir, (err, files) => {

        if (err) {

            throw err;

        };

        // Reset the timeout
        if (searchTimeout != -1) {

            clearTimeout(searchTimeout);
            searchTimeout = setTimeout(timeoutFunction, 1500);

        }

        // Start sorting all the paths
        files.forEach(function(file) {

            var stats = fs.statSync(`${dir}/${file}`);

            if (stats.isFile()) {

                if (mode == R_READ_FILES) {

                    callback(`${dir}/${file}`);

                }

            } else {

                if (mode == R_READ_FOLDERS) {

                    callback(`${dir}/${file}`);

                }

                readR(`${dir}/${file}`, callback, timeoutFunction, mode);

            }

        });

    });

}

// Check if a JSON file and exists and is valid
function isValidJSON(path) {

    // Check if the JSON file exists
    if (fs.existsSync(path)) {

        // Check if this is a valid JSON file
        try {

            JSON.parse(fs.readFileSync(path).toString());

        } catch {

            return false;

        }

        return true;

    } else {

        return false;

    }

}

// Define the exports object for this module
module.exports = {

    // Get the app info
    getAppInfo() {

        return JSON.parse(fs.readFileSync("./data/app.json").toString());

    },

    // Read the "/local" directory
    readLocal(callback) {

        // Return a promise
        return new Promise(resolve => {

            // Define the final resolve value
            var langs = [];

            // Start a timeout for the scan
            var timeoutFunction = function() {

                if (searchTimeout != -1) {

                    searchTimeout = -1;

                    resolve(langs);

                }

            };
            searchTimeout = setTimeout(timeoutFunction, 1500);

            // Call the recursive-reading function
            readR("./local", function(dir) {

                if (dir.split("/").length == 3) {

                    langs.push(dir.substring("./local/".length));

                }

            }, timeoutFunction, R_READ_FOLDERS);

        });

    },

    // Read the "/src" directory
    readSrc(ignoreList, callback) {

        // Return a promise
        return new Promise(resolve => {

            // Start a timeout for the scan
            var timeoutFunction = function() {

                if (searchTimeout != -1) {

                    searchTimeout = -1;

                    resolve();

                }

            };
            searchTimeout = setTimeout(timeoutFunction, 1500);

            // Call the recursive-reading function
            readR("./src", function(path) {

                var isAllowed = true;
                ignoreList.forEach(function(file) {

                    if (path.indexOf(file) != -1) {

                        isAllowed = false;

                    }

                });

                if (isAllowed) {

                    callback(path);

                }

            }, timeoutFunction);

        });

    },

    // Check if a path if for a "view" file
    isView(path) {

        return path.lastIndexOf(".view.html") == path.length - ".view.html".length &&
            path.length == path.lastIndexOf(".view.html") + ".view.html".length;

    },

    // Check if a path if for a HTML file
    isHTML(path) {

        return path.lastIndexOf(".html") == path.length - ".html".length &&
            path.length == path.lastIndexOf(".html") + ".html".length;

    },

    // Check if a language folder is valid
    isValidLang(lang) {

        // Check if the these JSON files exist, and check if they are valid:
        // config.json
        // basic-interface.json
        if (isValidJSON(`./local/${lang}/config.json`) &&
            isValidJSON(`./local/${lang}/general.json`) &&
            isValidJSON(`./local/${lang}/basic-interface.json`)) {

            // Get the JSON content of all the files that require content-validation
            var config = JSON.parse(fs.readFileSync(`./local/${lang}/config.json`).toString());

            // Check if the JSON content of the "config.json" file is valid
            // name                                     <string>
            // code                                     <string>
            // direction                                <string>
            if ((typeof config.name + typeof config.code + typeof config.direction)
                .split("string").length != 4) {

                return false;

            }

            return true;

        } else {

            return false;

        }

    },

    // Return the JSON content of a file
    getJSONContent(path) {

        return JSON.parse(fs.readFileSync(path).toString());

    },

    // Get the content of a file
    getContent(path) {

        return fs.readFileSync(path).toString();

    },

    // Process the content of a "view" file
    processView(content, path) {

        return viewProcessor(content, path);

    }

};
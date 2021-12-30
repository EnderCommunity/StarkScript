/**
 *
 * Manage the files processor
 *
 **/


// Get the required modules
const { match } = require("assert");
const fs = require("fs");
const path = require('path');

// Get the content of the "widnow-frame.html" file
const windowFramePath = path.resolve(__dirname, "./src/interface/window-frame.html"),
    viewFrameContent = fs.readFileSync(windowFramePath).toString();

// Define the build and src directories paths
const buildDir = path.normalize(`${__dirname}/build`),
    srcDir = path.normalize(`${__dirname}/src`),
    appDir = path.normalize(`${__dirname}/app`);

// Keep track of the used files
var usedFiles = {},
    filesCount = 0,
    searchTimeout = -1;

// Define a function that can copy files into the "/build" directory
function addFile(fileName, fileExtension, srcPath) {

    var relativePath = path.normalize(`${fileExtension}/${fileName}.${fileExtension}`).replace(/\\/g, "/"),
        destDir = path.normalize(`${buildDir}/${fileExtension}/`);

    // Check if a custom folder for the file's extension exists
    if (!fs.existsSync(destDir)) {

        // Create this directory
        fs.mkdirSync(destDir);

    }

    // Copy this file to the destination directory
    fs.writeFile(path.join(buildDir, relativePath), fs.readFileSync(srcPath).toString(), function(err) {

        if (err) {

            throw err;

        }

    });

    return relativePath;

}

// Define a function that can organise the window's content
function processViewContent(content) {

    var windowValues = {};

    return content.replace(/\r|\n/g, function(match) {

        return `&esc;${(match == "\n") ? "n" : "r"}&`;

    }).replace(/<window(.*?)>(.*?)<\/window>/, function(match, attributes, innerContent) {

        // Get the window attributes/settings
        attributes.replace(/(.*?)=?"(.*?)"/g, function(attributeMatch, attributeName, attributeValue) {

            windowValues[attributeName.replace(/\s|\n/g, "")] = (function() {

                if (attributeValue == "false" || attributeValue == "0" || attributeValue == "no") {

                    return false;

                } else if (attributeValue == "true" || attributeValue == "1" || attributeValue == "yes") {

                    return true;

                } else {

                    return attributeValue;

                }

            })();

        });

        // Prepare the final output
        return viewFrameContent.replace(/prop::(.*?):/g, function(match, name) {

            if (name == "title") {

                return (windowValues.title != undefined) ? `${windowValues.title} | $\${app:title}` : "$${app:title}";

            } else if (name == "titleDisplay") {

                return (windowValues["show-title"]) ? "block" : "none";

            } else if (name == "controlsHideDisplay") {

                return (windowValues["enable-min"]) ? "block" : "none";

            } else if (name == "controlsMaxDisplay") {

                return (windowValues["enable-max"] && !windowValues["start-max"]) ? "block" : "none";

            } else if (name == "controlsUnmaxDisplay") {

                return (windowValues["enable-max"] && windowValues["start-max"]) ? "block" : "none";

            } else if (name == "controlsCloseDisplay") {

                return (windowValues["enable-close"]) ? "block" : "none";

            } else {

                throw new Error(`Unknown property! (${name})`);

            }

        }).replace(/<!-- @insert::(.*?) -->/g, function(insertMatch, insertType) {

            if (insertType == "CSS") {

                var stylesheetsString = '',
                    matches = innerContent.match(/<stylesheet(.*?)\/>/g);
                matches = (matches == null) ? [] : matches;

                for (var i = 0; i < matches.length; i++) {

                    stylesheetsString += matches[i].replace("<stylesheet", `<link rel="stylesheet" `).replace("/>", ">\n");

                }

                return stylesheetsString;

            } else if (insertType == "JAVASCRIPT") {

                var scriptsString = '',
                    matches = innerContent.match(/<javascript(.*?)\/>/g);
                matches = (matches == null) ? [] : matches;

                for (var i = 0; i < matches.length; i++) {

                    scriptsString += matches[i].replace("<javascript", `<script type="text/javascript" `).replace("/>", "></script>\n");

                }

                return scriptsString;

            } else if (insertType == "CONTENT") {

                var matches = innerContent.match(/<content>(.*?)<\/content>/g);
                return matches[0].substring(9, matches[0].length - 10);

            } else {

                return "ERROR::INVALID_INSERT";

            }

        });

    }).replace(/&esc;(n|r)&/g, function(match, type) {

        return (type == "n") ? "\n" : "\r";

    }).replace(/studio:\/\/(.*?)"/g, function(match, srcPath) {

        srcPath = path.normalize(srcPath);

        if (srcPath.indexOf(/\s/) != -1) {

            throw new Error("You may not include any whitespace characters within file paths!");

        }

        // Get the extension of the file
        var ext = path.extname(srcPath).substring(1);

        if (ext.indexOf("html") != -1) {

            throw new Error("Files with the HTML extension are considered invalid!");

        }

        // Get the absolute path of the file
        var absolutePath = path.normalize(`${__dirname}/src/${srcPath}`);

        if (typeof usedFiles[srcPath] != "string") {

            usedFiles[srcPath] = addFile(++filesCount, ext, absolutePath);

            console.log("Added file:", srcPath, absolutePath);

        }

        return `./../${usedFiles[srcPath]}"`;

    });

}

// Prepare the "/build" directory
function prepareBuildDir(resolve) {

    fs.mkdirSync(buildDir);

    fs.mkdirSync(path.normalize(`${buildDir}/views`));
    fs.mkdirSync(path.normalize(`${buildDir}/load`));

    resolve("'/build' directory ready!");

}

// Prepare the "/app" directory
var appLangs, langsJSON = {},
    appInfo;

function prepareAppDir(langs, resolve) {

    fs.mkdirSync(appDir);

    appLangs = langs;

    langs.forEach(function(lang) {

        var langDir = path.join(__dirname, "local", lang);

        fs.mkdirSync(path.join(appDir, lang));

        langsJSON[lang] = {};

        fs.readdir(langDir, (err, files) => {

            if (err) {

                throw err;

            };

            files.forEach(file => {

                langsJSON[lang][file.substring(0, file.indexOf("."))] = JSON.parse(fs.readFileSync(path.join(langDir, file)).toString());

            });

        });

    });

    appInfo = JSON.parse(fs.readFileSync("./app.json").toString());

    resolve("'/app' directory ready!");

}

// Take care of localising files' content
function processLocalStrings(lang, content) {

    return content.replace(/\$\${(.*?):(.*?)}/g, function(match, file, value) {

        if (file == "lang") {

            return match;

        } else {

            var returnVal = (file == "app") ? appInfo : langsJSON[lang][file];
            value.split('.').forEach(val => {

                returnVal = returnVal[val];

            });

            return returnVal;

        }

    });

}

module.exports = {

    processView(filePath) {

        // Get the file content
        fs.readFile(filePath, {}, function(err, data) {

            if (err) {

                throw err;

            }

            const fileContent = data.toString();

            // Add the view frame
            const finalContent = processViewContent(fileContent);

            // Replace variables
            // ...

            // Save in "/build"
            fs.writeFile(path.normalize(`${buildDir}/views/${path.basename(filePath)}.html`), finalContent, (err) => {

                if (err) {

                    throw err;

                }

            });

        });

    },
    processFile(filePath, realtivePath) {

        // Get the file content
        var fileContent = fs.readFileSync(filePath).toString();

        // Replace "view://" paths
        fileContent = fileContent.replace(/view:\/\/(.*?)!([0-9])/g, function(match, viewPath, backNum) {

            return path.normalize(`app/$\${config:code}/views/${viewPath}.view.html`).replace(/\\/g, "/");

        });

        // Replace variables
        // ...

        // Copy this file to the destination directory
        fs.writeFile(path.join(buildDir, realtivePath), fileContent, function(err) {

            if (err) {

                throw err;

            }

        });

    },
    freeBuildDir() {

        return new Promise(resolve => {

            // Check if the "/build" directory exists
            if (fs.existsSync(buildDir)) {

                // Delete the "/build" directory
                fs.rm(buildDir, { recursive: true, force: true }, function() {

                    prepareBuildDir(resolve);

                });

            } else {

                // Create the "/build" directory
                prepareBuildDir(resolve);

            }

        });

    },
    readSrc(dir, callback, endCallback) {

        if (typeof dir != "string") {

            dir = srcDir;

        }

        // Start a timeout
        var timeoutFunction = function() {

            if (searchTimeout != -1) {

                searchTimeout = -1;

                endCallback();

            }

        };
        searchTimeout = setTimeout(timeoutFunction, 1500);

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

            // Star sorting all the paths
            files.forEach(function(file) {

                const filePath = path.normalize(`${dir}/${file}`);
                var stats = fs.statSync(filePath);

                if (stats.isFile()) {

                    callback(filePath);

                } else {

                    module.exports.readSrc(filePath, callback, endCallback);

                }

            });

        });

    },
    isView(filePath) {

        return (path.extname(filePath) == ".view");

    },
    srcRealtivePath(filePath) {

        return filePath.substring(__dirname.length).substring(5).replace(/\\/g, "/");

    },
    isMainNodeJS(filePath) {

        var relativePath = module.exports.srcRealtivePath(filePath);

        return (path.extname(relativePath) == ".js" && (relativePath.indexOf("load") == 0 || relativePath.indexOf("/") == -1));

    },
    initializeAppDir(langs) {

        return new Promise(resolve => {

            // Check if the "/build" directory exists
            if (fs.existsSync(appDir)) {

                // Delete the "/build" directory
                fs.rm(appDir, { recursive: true, force: true }, function() {

                    prepareAppDir(langs, resolve);

                });

            } else {

                // Create the "/build" directory
                prepareAppDir(langs, resolve);

            }

        });

    },
    localizeLang(lang, dir = buildDir) {

        // Read the "/src" directory
        fs.readdir(dir, (err, files) => {

            if (err) {

                throw err;

            };

            // Star sorting all the paths
            files.forEach(function(file) {

                const filePath = path.normalize(`${dir}/${file}`);
                var stats = fs.statSync(filePath);

                if (stats.isFile()) {

                    var newPath = path.join(appDir, lang, path.normalize(filePath.substring(buildDir.length))),
                        folder = newPath.substring(appDir.length + 1 + lang.length + 1).replace(/\\/g, "/");

                    if (folder.indexOf("/") != -1) {

                        folder = folder.substring(0, folder.indexOf("/"));

                        var folderPath = path.join(appDir, lang, folder);

                        if (!fs.existsSync(folderPath)) {

                            // Create this directory
                            fs.mkdirSync(folderPath);

                        }

                    }

                    fs.writeFile(newPath, processLocalStrings(lang, fs.readFileSync(filePath).toString()), function(err) {

                        if (err) {

                            throw err;

                        }

                    });

                } else {

                    module.exports.localizeLang(lang, filePath);

                }

            });

        });

    },
    localize(lang, dir = buildDir) {

        appLangs.forEach(function(lang) {

            module.exports.localizeLang(lang);

        });

    }

};
/**
 *
 * Manage the output directory ("/app")
 *
 **/


// Get the required modules
const fs = require("fs");

// Create the output directory
function createDir(resolve) {

    // Create the "/app" directory
    fs.mkdirSync("./app/");

    // Create the "local-view" folder inside the "/app" directory
    fs.mkdirSync("./app/local-view/");

    // Resolve the promise
    resolve();

}

// Define the exports object for this module
module.exports = {

    // Prepare the output directory
    prepareDir() {

        // Return a promise
        return new Promise(resolve => {

            // Check if the "/app" directory exists
            if (fs.existsSync("./app/")) {

                // Delete the "/app" directory
                fs.rm("./app/", { recursive: true, force: true }, function() {

                    createDir(resolve);

                });

            } else {

                createDir(resolve);

            }

        });

    },

    // Create a folder inside the "/tmp" folder
    createFolder(path) {

        // Only pay attention to the slash characters after the "./src/" part
        var folders = path.substring("./src/".length).split("/"),
            relativeDir = "./app";
        for (var i = 0; i < folders.length - 1; i++) {

            relativeDir += `/${folders[i]}`;

            // Check if the current folder doesn't exists
            if (!fs.existsSync(relativeDir)) {

                // Create the current folder
                fs.mkdirSync(relativeDir);

            }

        }

    },

    // Save all the translation strings into one big file
    writeAppLocal(viewPath, langs, localJSON) {

        fs.writeFileSync("./app/langs.json", JSON.stringify(langs));
        fs.writeFileSync("./app/local.json", JSON.stringify(localJSON));

        // Create all the language folders inside the "view" folder
        langs.forEach(function(lang) {

            fs.mkdirSync(`${viewPath}/${lang}/`);

        });

    },

    // Add a file to the temporary folder
    writeFile(path, content) {

        fs.writeFileSync(path, content);

    },

    // Replace all the language strings
    processLangStrings(lang, strings, content, appInfo) {

        // Look for the strings
        return content.replace(/\$\${(.*?):(.*?)}/g, function(match, section, valuePath) {

            // Prepare the return string
            var finalValue = (section == "app") ? appInfo : strings[section];
            if (!(typeof finalValue == "object" && finalValue != null)) {

                throw new Error(`Invalid language section call! (${section}, in ${lang})`);

            }

            // Look through the value path
            valuePath.split(".").forEach(function(name) {

                try {

                    finalValue = finalValue[name];

                    if (finalValue == null || finalValue == undefined) {

                        throw 0;

                    }

                } catch {

                    throw new Error(`Invalid language string call! (${section} -> ${valuePath}, in ${lang})`);

                }

            });

            // Check if the final value is valid
            if (typeof finalValue == "string") {

                return finalValue;

            } else {

                throw new Error(`Invalid language string destination! (${section} -> ${valuePath}, in ${lang})`);

            }

        });

    }

};
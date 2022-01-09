/**
 *
 * Manage the building process
 *
 **/


// Get the required modules
const { prepareDir, createFolder, writeAppLocal, writeFile, processLangStrings } = require("./output");
const { getAppInfo, readLocal, readSrc, isView, isValidLang, getJSONContent, getContent, processView } = require("./input");
const { pathsProcessor } = require("./view");

// Run the code inside an asynchronous function to ensure that all the code will run after the
// checks are done
(async function() {

    // Get the app info
    var appInfo = getAppInfo();

    // Prepare the output directory "/app"
    await prepareDir();

    // Get all the translation strings from the "/local" directory
    var langs = await readLocal(),
        langStrings = {};

    // Check if all the language folders are valid
    langs.forEach(function(lang) {

        if (isValidLang(lang)) {

            langStrings[lang] = {

                config: getJSONContent(`./local/${lang}/config.json`),
                general: getJSONContent(`./local/${lang}/general.json`),
                "basic-interface": getJSONContent(`./local/${lang}/basic-interface.json`)

            };

        }

    });

    // Save all the string translations in one file for the final output's JS code to use
    writeAppLocal("./app/local-view", langs, langStrings);

    // Go through all the files in the "/src" directory
    await readSrc(["frame.html"], function(path) {

        // Get the content of the current file
        var content = getContent(path),
            finalPath = `./app/${path.substring("./src/".length)}`;

        // Check if this is a "view" file
        if (isView(path)) {

            finalPath = `./app/local-view/$LANG/${path.substring(path.lastIndexOf("/") + 1)}`;

            content = processView(content, finalPath);

        } else {

            // Make sure to copy the folders before the files
            createFolder(path);

        }

        // Replace all the "custom protocols" paths
        content = pathsProcessor(content, finalPath);

        if (finalPath.indexOf("$LANG") == -1) {

            // Add this file to the "/app" directory
            writeFile(finalPath, content);
            console.log(`Added file: ${finalPath}`);

        } else {

            // Add thos file to the "/app/local-view/" directory for all the languaegs
            langs.forEach(function(lang) {

                var langPath = finalPath.replace(/\$LANG/g, lang);

                writeFile(langPath, processLangStrings(lang, langStrings[lang], content, appInfo));

                console.log(`Added file: ${langPath}`);

            });

        }

    });

    // Organise the processed content inside the temporary directory
    // ...

})();
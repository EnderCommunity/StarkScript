/**
 *
 * Manage the building process
 *
 **/


// Get the required modules
const isNode = require("detect-node");
const { processView, processFile, freeBuildDir, readSrc, isView, isMainNodeJS, srcRealtivePath, initializeAppDir, localize } = require("./files-processor");

(async function() {

    // Clean the "/build" directory
    await freeBuildDir();

    // Go through all the files in the "/src" directory
    readSrc(null, function(path) {

        // Note that you should not add ".view" files outside the "interface" folder!

        // Check if this is a view file
        if (isView(path)) {

            // Process this file as a "view" file
            processView(path);

        } else if (isMainNodeJS(path)) { // Check if this is a JS file that is related to the main process of electron

            processFile(path, srcRealtivePath(path));

            // processNodeFile();

        }

        // Now, the "/build" directory should have all the files that are used by the current build

        // ...

    }, async function() {

        await initializeAppDir([
            "en-GB",
            "ar"
        ]);

        // Create local variants of the app
        localize();

    });

})();
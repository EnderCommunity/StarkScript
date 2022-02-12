/**
 *
 * Manage the editor session
 *
 **/


// Keep track of the max file ID
var maxFileID = 0;

// Define the custom session objects
function SessionFile(relativePath, barIndex = -1) {

    // Get the name of the file
    this.name = relativePath.substring(relativePath.lastIndexOf("/") + 1);

    // Get the file's extension
    if (this.name.indexOf(".") != -1) {

        this.extension = this.name.substring(this.name.indexOf("."));

    } else {

        this.extension = "";

    }

    // Save the relative path of the file
    this.path = relativePath;

    // Save the bar index of this file
    this.index = barIndex;

    // Save the file ID
    this.id = maxFileID++;

}

// Define the session object
var session = {

    dir: null, // The working directory (project root directory)

    files: {}, //  All the files within this session

    openFiles: [],

    currentFile: -1

    // ...

};

// Define a function that can create a session from scratch
function createSession(absoluteProjectDir) {

    // Read the content of the project manifest file
    electron.filesSystem.readFile(absoluteProjectDir + "/manifest.json", function(data) {

        try {

            // Parse the file's data
            data = JSON.parse(data);

            // Start creating the session

            // Save the current files
            electron.filesSystem.readDir("./", function(result) {

                console.log(result);

            }, true);

            // Start observing the project
            /* electron.filesSystem.observer.linkPath(absoluteProjectDir + "/src/", function(type, data) {

                console.log(type);
                console.log(data);

            }); */

            session.dir = absoluteProjectDir;

            //session.files[];

        } catch {

            electron.alert("INVALID_PROJECT", 0, "INVALID_PROJECT_DESC", function() {

                console.log(1);

            });

        }

    });

}

// Define a function that can be used to save a session
function saveSession(session) {

    var exportData = {

        dir: null,
        openFiles: []

    };

    // Get the main dir
    exportData.dir = session.dir;

    // Get the path and index of each file
    for (var file in session.openFiles) {

        // [<index>, <relative path>]
        exportData.openFiles.push(
            [
                session.openFiles[file].index,
                session.openFiles[file].path
            ]
        );

    }

}

// Define a function that can load sessions
function loadSession() {

    electron.alert("Not ready!", electron.alertType.warn, "Sessions are not ready for use yet!", function() {

        console.log(1);

    });

}
/**
 *
 * Manage the cleaning process
 *
 **/


// Get the required modules
const fs = require("fs");

// Delete the "/app" directory
if (fs.existsSync("./app/")) {

    fs.rmSync("./app/", { recursive: true, force: true });

}
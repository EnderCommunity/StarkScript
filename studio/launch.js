/**
 *
 * Launch the app
 *
 **/


// Get the required modules
const fs = require("fs");

// Get the content of the "settings.json" file
const settings = JSON.parse(fs.readFileSync("./settings.json").toString());

// Start the studio
require(`./app/${settings.lang}/start.js`);
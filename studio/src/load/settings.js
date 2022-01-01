/**
 *
 * The studio settings loader
 *
 **/


// Get the required moduels
const fs = require("fs");

// Define the object that this file will return
module.exports = {

    // Define a function that can get the content of the settings file
    getSettings() {

        return JSON.parse(fs.readFileSync("./data/settings.json").toString());

    }

};
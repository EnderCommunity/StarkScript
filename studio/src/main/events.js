/**
 * 
 * Keep track of all the events in the main window
 * 
 **/


// Get all the required elements
const settingsButton = document.getElementById("options--settings"),
    aboutButton = document.getElementById("options--about"),
    signOutButton = document.getElementById("options--signout"),
    signInButton = document.getElementById("options--signin"),
    cloneButton = document.getElementById("options--cloneproject"),
    openButton = document.getElementById("options--openproject"),
    createButton = document.getElementById("options--createproject"),
    openEmptyButton = document.getElementById("options--openempty"),
    profileButton = document.getElementById("projects--profile");

// Listen for any click events
settingsButton.onclick = function() {

    electron.alert("Not ready!", electron.alertType.info, "The 'settings' menu is not ready!", function() {});

};
aboutButton.onclick = function() {

    electron.tell("show-about");

};
signOutButton.onclick = function() {

    electron.alert("Not ready!", electron.alertType.info, "The 'sign out' button is not ready!", function() {});

};
signInButton.onclick = function() {

    electron.alert("Not ready!", electron.alertType.info, "The 'sign in' button is not ready!", function() {});

};
cloneButton.onclick = function() {

    electron.alert("Not ready!", electron.alertType.info, "The 'clone' button is not ready!", function() {});

};
openButton.onclick = function() {

    electron.alert("Not ready!", electron.alertType.info, "The 'open' button is not ready!", function() {});

};
createButton.onclick = function() {

    electron.alert("Not ready!", electron.alertType.info, "The 'create' button is not ready!", function() {});

};
openEmptyButton.onclick = function() {

    electron.tell("open-editor", null);
    electron.send("window-close");

};
profileButton.onclick = function() {

    electron.alert("Not ready!", electron.alertType.info, "The 'user profile' button is not ready!", function() {});

};
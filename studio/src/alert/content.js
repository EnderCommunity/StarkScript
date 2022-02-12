/**
 * 
 * Manage the content of the alert window
 * 
 **/

// Update the title and message
document.getElementById("alert-title").innerText = winVals.title;
document.getElementById("alert-message").innerText = winVals.message;

// Update the icon
// (info: 0, warn: 1, error: 2)
document.getElementById((function() {

    if (winVals.type == 1) {

        return "icon--warn";

    } else if (winVals.type == 2) {

        return "icon--error";

    } else {

        return "icon--info";

    }

})()).style.display = null;
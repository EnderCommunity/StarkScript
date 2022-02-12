/**
 * 
 * Manage the location search attribute info
 * 
 **/

// Get all the URL search attribute info
var winVals = {};
location.search.substring(1).split("&").forEach(function(val) {

    var valInfo = val.split("=");

    // The name of the value
    valInfo[0];

    // The value
    valInfo[1];

    // Save this value to the `winVals` object
    winVals[valInfo[0]] = decodeURI(valInfo[1]);

});

// The winVals object should contain the following values now:
// type                     The alert type
//                          <int> [0 - informative, 1 - warning, 2 - error]
// title                    The alert title
//                          <string>
// message                  The alert message
//                          <string>
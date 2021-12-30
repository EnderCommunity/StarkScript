/**
 *
 * The start file
 *
 **/


// Define the function that this module will return
module.exports = {

    hideWindow: function(window, opacity = true) {

        window.hide();
        if (opacity) {

            window.setOpacity(0);

        }

    },
    showWindow: function(window, callback = function() {}, opacity = true) {

        if (opacity) {

            window.show();
            setTimeout(function() {

                window.setOpacity(1);

                if (window.shouldMaximize) {

                    window.maximize();

                }

                callback();

            }, 400);

        } else {

            setTimeout(function() {

                window.show();

                if (window.shouldMaximize) {

                    window.maximize();

                }

                callback();

            }, 400);

        }

    },
    closeWindow: function(window) {

        window.setClosable(true);
        window.close();

    }

};
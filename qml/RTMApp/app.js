/* Main application engine for RTMApp
 */

.pragma library

/**
 * Test login
 */
function test_login() {
    console.log("this.api_key is " + settings.value("foursquare/apikey"));
}

/**
 * Initialize the app.
 *
 * @param settings the application settings object.
 * @return app object.
 */
var init = function(settings) {
    return {
            // methods
            test_login: test_login
    };
}

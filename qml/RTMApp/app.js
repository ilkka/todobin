/* Main application engine for RTMApp
 */

/**
 * Test login
 */
function test_login() {
    console.log("this.api_key is " + this.api_key);
}

/**
 * Initialize the app.
 *
 * @param settings the application settings object.
 * @return app object.
 */
var init = function(settings) {
    return {
            // data
            api_key: settings.apikey,
            secret: settings.secret,
            endpoint: settings.endpoint,

            // methods
            test_login: test_login
    };
}

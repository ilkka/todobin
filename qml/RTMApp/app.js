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
 * @param api_key the RTM API key.
 * @param secret the RTM shared secret.
 * @param endpoint the RTM API endpoint URL.
 * @return app object.
 */
var init = function(api_key, secret, endpoint) {
    return {
            // data
            api_key: api_key,
            secret: secret,
            endpoint: endpoint,

            // methods
            test_login: test_login
    };
}

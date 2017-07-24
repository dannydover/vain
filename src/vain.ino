/*
 * Project vain
 * Description:
 * Author: Danny Dover
 */

 /*  TO DO

 0. Right code to refresh token after indicated expiration
 1. Extract client_id and store as part of customer data? I don't want it stored in this code or with the generic webhook
 2. Error handling, what happens if Google API requests don't return expected results?
 3. Fiture out where method for subscribing to realTimeActiveUsers goes.
 4. fix tokenExpirationInSeconds which is currently a false int/string mixup. The problem is parsing the JSON in the attemptToAuthDevice method
 5. Find consistent naming convention for variables
 6. Create easier to understand naming convention for methods/webhooks
 7. Display real-time vistors number on external display


 */

 String device_code = "";
 String user_code = "";
 String access_token = "";
 String refresh_token = "";
 int realTimeActiveUsers = 88;
 String tokenExpirationInSeconds = "";
 bool authenticated = false;

 void setup() {
     Serial.begin(9600);
     Serial.println("Serial Output is working");

     //Device authenticates with Google Analytics API using following protocol:
     //https://developers.google.com/identity/protocols/OAuth2ForDevices

     Particle.publish("initiateGAuth", PRIVATE);
     Particle.subscribe("initiateGAuthResponse", parseAuthResponse, MY_DEVICES);
     delay(10000);


     Serial.print("Device Code: ");
     Serial.println(device_code);

     Serial.println("Please enter the following code at www.google.com/device - User Code: ");
     Serial.println(user_code);

     // TO CODE: STEP 4 - Your application starts polling Google's authorization server (NEW WEBHOOK) to determine whether the user has authorized your app.
     Particle.subscribe("gAuthPollResponse", attemptToAuthDevice, MY_DEVICES);
     Particle.subscribe("hook-error/pollGAuthForAuth", attemptToAuthDeviceErrors, MY_DEVICES);

     while (authenticated == false) {
         Serial.println("Polling Google Auth Service");

         Particle.publish("pollGAuthForAuth", device_code, PRIVATE);
         delay(20000);
     }


     // TO CODE: STEP 6 Collect the next response to your polling request which contains the tokens your app needs to authorize requests on the user's behalf.
     Serial.print("Access Token: ");
     Serial.println(access_token);





     Particle.subscribe("realTimeActiveUsers", howManyRealTimeUsers, MY_DEVICES); // WHERE DOES THIS GO?

 }

 void loop() {

     // TO CODE: After authenticating, request real time number from Google API every 30 seconds (NEW WEBHOOK)
     if (authenticated == true) {
         Particle.publish("getGARealTimeActiveUsers", access_token, PRIVATE);
         Serial.print("Real Time Active Users: ");
         Serial.println(realTimeActiveUsers);

         delay(30000);
     }

     // TO CODE: Keep track of seconds passed (number of times API requested) and periodically use refresh token to request new access token


     // TO CODE: Display real-time vistors number on external display


 }

 void parseAuthResponse(const char *event, const char *data) {
     Serial.println("Status: Received initiateGAuthResponse response");

     //Split JSON payload strubg into two global variables (split is by "~")
     String str = String(data);
     char strBuffer[125] = "";
     str.toCharArray(strBuffer, 125);
     device_code = strtok(strBuffer, "~");
     user_code = strtok(NULL, "~");
 }


 void attemptToAuthDeviceErrors(const char *event, const char *data) {
     Serial.println("Status: Received errors from Google Auth while polling: ");
     Serial.println(data);
 }


 void attemptToAuthDevice(const char *event, const char *data) {
     String token_type = "";

     Serial.println("Status: Received successful response from Google's Auth Service after user input");

     Serial.print("authDeviceResponse: ");
     Serial.println(data);

     //Split JSON payload string into global variables (split is by "~")
     String str = String(data);

     char strBuffer[250] = "";
     str.toCharArray(strBuffer, 250);
     access_token = strtok(strBuffer, "~");
     token_type = strtok(NULL, "~");
     tokenExpirationInSeconds = strtok(NULL, "~");
     refresh_token = strtok(NULL, "~");

     Serial.print("access_token: ");
     Serial.println(access_token);

     Serial.print("token_type: ");
     Serial.println(token_type);

     Serial.print("tokenExpirationInSeconds: ");
     Serial.println(tokenExpirationInSeconds);

     Serial.print("refresh_token: ");
     Serial.println(refresh_token);

     if (access_token.length() > 5) {
         authenticated = true;
         Serial.print("Authenticated: true");
     }
 }


 void howManyRealTimeUsers(const char *event, const char *data) {
     Serial.println("Status: Received amount of Real Time Active Users: ");
     Serial.println(data);

     String dataString = String(data);

     if (dataString.length() == 0) {
         realTimeActiveUsers = 0;
     }

     //convert data into integer
     char carray[sizeof(dataString)];
     dataString.toCharArray(carray, sizeof(carray));
     realTimeActiveUsers = atoi(carray);
 }

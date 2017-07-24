/*
 * Project: Vain
 * Description:
 * Author: Danny Dover
 */

 /*  TO DO

    * Display real-time vistors number on external display
    * Fix bug that appears to be preventing code from executing after line 176
    * Fix bug of when number of users gets stuck at last value when value switches to 0
    * Extract client_id and store as part of customer data? I don't want it stored in the generic webhook
    * Implement more robust error handling, what happens if Google API requests don't return expected results?
    * Create easier to understand naming convention for methods/webhooks


 */

 String deviceCode = "";
 String userCode = "";
 String accessToken = "";
 String refreshToken = "";
 int realTimeActiveUsers = 88;
 unsigned long tokenExpirationTime = 0;
 bool authenticated = false;
 int pollingRate = 30000; //30 seconds expressed in milliseconds
 int requestCounter = 0;

 void setup() {
     Particle.subscribe("initiateGAuthResponse", parseAuthResponse, MY_DEVICES);
     Particle.subscribe("gAuthPollResponse", attemptToAuthDevice, MY_DEVICES);
     Particle.subscribe("hook-error/pollGAuthForAuth", attemptToAuthDeviceErrors, MY_DEVICES);
     Particle.subscribe("realTimeActiveUsers", howManyRealTimeUsers, MY_DEVICES);
     Particle.subscribe("refreshAccessTokenResponse", requestRefreshTokenResponse, MY_DEVICES);

     Serial.begin(9600);
     Serial.println("Status: Serial output is operational...");

     /* Device authenticates with Google Analytics API using following protocol:
        https://developers.google.com/identity/protocols/OAuth2ForDevices
        The steps identified as part of this protocol (and explained on that URL) are included
        in the code comments that follow.
     */

     //Step 1: Request device and user codes
     Particle.publish("initiateGAuth", PRIVATE);
     delay(10000);

     //Step 2: Handle the authorization server response
     // See function parseAuthResponse()

     //Step 3: Display the user code
     Serial.print("Device Code: ");
     Serial.println(deviceCode);

     Serial.println("Please enter the following code at www.google.com/device - User Code: ");
     Serial.println(userCode);

     //Step 4 - Your application starts polling Google's authorization server to determine whether the user has authorized your app.
     while (authenticated == false) {
         Serial.println("Status: Polling Google authorization service...");

         Particle.publish("pollGAuthForAuth", deviceCode, PRIVATE);
         delay(20000);
     }

     //Step 5: User responds to access request
     // User must input deviceCode in the web form located at https://www.google.com/device while logged into
     // their applicable Google (Analytics) account.


     //Step 6: Handle responses to polling requests
     // See function attemptToAuthDevice()
     Serial.print("Access Token: ");
     Serial.println(accessToken);
 }

 void loop() {

     // After authenticating, request amount of real time active users from Google Analytics API every 30 seconds
     if (authenticated == true) {
         Particle.publish("getGARealTimeActiveUsers", accessToken, PRIVATE);
         requestCounter++;
         Serial.print("Real Time Active Users: ");
         Serial.println(realTimeActiveUsers);

         // If access token is going to expire, request a new one from Google.
         if ((requestCounter * pollingRate) > (tokenExpirationTime * 1000)) {
            Particle.publish("requestAccessTokenRefresh", refreshToken, PRIVATE);

            /* Debugging Code
            Serial.print("requestCounter * pollingRate : ");
            Serial.println(requestCounter * pollingRate);

            Serial.print("tokenExpirationTime * 1000 : ");
            Serial.println(tokenExpirationTime * 1000);

            Serial.print("refreshToken : ");
            Serial.println(refreshToken);
            */
         }

         delay(pollingRate); //default is 30 seconds
     }

     // TO CODE: Display real-time vistors number on external display



 }

 void parseAuthResponse(const char *event, const char *data) {
     Serial.println("Status: Received initiateGAuthResponse response");

     //Split JSON payload string into two global variables (split is by "~")
     String str = String(data);
     char strBuffer[125] = "";
     str.toCharArray(strBuffer, 125);
     deviceCode = strtok(strBuffer, "~");
     userCode = strtok(NULL, "~");
 }


 void attemptToAuthDeviceErrors(const char *event, const char *data) {
     Serial.println("Status: Received errors from Google Auth while polling: ");
     Serial.println(data);
 }


 void attemptToAuthDevice(const char *event, const char *data) {
     String tokenType = "";

     Serial.println("Status: Received successful response from Google's Auth Service after user input");

     Serial.print("authDeviceResponse: ");
     Serial.println(data);

     //Split JSON payload string into global variables (split is by "~")
     String str = String(data);

     char strBuffer[250] = "";
     str.toCharArray(strBuffer, 250);
     accessToken = strtok(strBuffer, "~");
     tokenType = strtok(NULL, "~");
     String expiration = strtok(NULL, "~");
     refreshToken = strtok(NULL, "~");

     //Manually subtract 10 minutes from received token expiration time in order
     //to give time to get new access token. This line also coverts string to int.
     tokenExpirationTime = expiration.toInt() - 600;

     Serial.print("accessToken: ");
     Serial.println(accessToken);

     Serial.print("tokenType: ");
     Serial.println(tokenType);

     Serial.print("tokenExpirationTime: ");
     Serial.println(tokenExpirationTime);

     Serial.print("refreshToken: ");
     Serial.println(refreshToken);

     if (accessToken.length() > 5) {
         authenticated = true;
         Serial.println("Authenticated: true");
     }
 }

 void howManyRealTimeUsers(const char *event, const char *data) {
     Serial.println("Status: Received amount of Real Time Active Users: ");
     Serial.println(data);

     String dataString = String(data);

     if (dataString.length() == 0) {
         realTimeActiveUsers = 0;
     } else {
       //convert non-zero data into integer
       char carray[sizeof(dataString)];
       dataString.toCharArray(carray, sizeof(carray));
       realTimeActiveUsers = atoi(carray);
    }
 }

 void requestRefreshTokenResponse(const char *event, const char *data) {
   String tokenType = "";

   Serial.println("Status: Received response from request to refresh access token: ");
   Serial.println(data);

   //Split JSON payload string into global variables (split is by "~")
   String str = String(data);

   char strBuffer[250] = "";
   str.toCharArray(strBuffer, 250);
   accessToken = strtok(strBuffer, "~");
   tokenType = strtok(NULL, "~");
   String expiration = strtok(NULL, "~");

   requestCounter = 0;
 }

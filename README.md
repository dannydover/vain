# Vain: A Tangible Google Analytics Display

Vain is a Photon (a $20 web enabled micro-controller that is similar to an Arduino) based project that displays real-time Google Analytics data on a real-world display. Since the device does not have any physical user input mechanisms, it relies on [Google’s OAuth 2.0 for Limited-Input Device protocol](https://developers.google.com/identity/protocols/OAuth2ForDevices) for authenticating the appropriate Google Analytics account. Webhooks via [Particle.io’s free service](https://www.particle.io) are used to authenticate the device and then repeatedly request the current amount of real-time active users on a given website. This data is then displayed on an external display.

## Required Hardware

* Particle Photon ([~$19.00 USD](https://www.sparkfun.com/products/13774))
* Display (Many display options can work but a Liquid Crystal Display is likely
	the cheapest and easiest option) ([~$15.00 USD](https://www.sparkfun.com/products/9052))
* Breadboard ([~$6.00](https://www.sparkfun.com/products/12615))
* Jumper Cables ([~$6.00](https://www.sparkfun.com/products/8431))

## Getting Access to Google’s APIs and Collecting Your Credentials

**Step 1.** Create a new project with Google API Manager:

To create a new project within the Google API manager, go to https://https://console.developers.google.com. Once at that URL, click the small downward facing triangle in the main navigation and then click the plus symbol "+" to create a new project.

If you get stuck or the interface has changed, see this URL (https://support.google.com/cloud/answer/6251787) for more detailed information and up-to-date instructions on creating a new project within the Google API manager.
![step-1](https://user-images.githubusercontent.com/136573/28741600-ce13fdb8-73ce-11e7-8efb-ac488e2ac1b3.png)

**Step 2.** Enable the Google Analytics API for your project:

While within your newly created project and while on the Dashboard tab, click “+Enable API” link and search for “Analytics API”.
![step-2](https://user-images.githubusercontent.com/136573/28741604-ce1865ec-73ce-11e7-8704-5ab8f37fa563.png)

**Step 3.** Create credentials for your newly enabled API access:

Now you have created a new project, you need to create credentials in order to access it. Click the “Credentials” menu item on the subnavigation and then click “Create credentials”. Next choose the “OAuth client ID” form of credentials. If required, give your product a name to be shown to users. (If Google requires this step for your project, it will prompt you for this information). When asked to specify your Application type, select “Other”, give the set of credentials a name (example, Vain Photon) and click “Create”. Store the resulting “Client ID” and “Client Secret“ in a secure location. You are going to need this information shortly.
![step-3a](https://user-images.githubusercontent.com/136573/28741603-ce146fd2-73ce-11e7-9109-9e76c87e2e94.png)
![step-3b](https://user-images.githubusercontent.com/136573/28741602-ce144cf0-73ce-11e7-96fa-d2023e4da784.png)

**Step 4.** Request access to the Google Analytics Real Time Beta API.

At the time of creating this project, the Google Analytics Real Time Reporting API was in limited beta. This meant you needed to sign up for access in addition to enabling the API on your API manager. To do this, visit this URL https://developers.google.com/analytics/devguides/reporting/realtime/v3/ and fill out the accompanying form. Depending on the Google’s policies and the current status of the Real Time Analytics API, you may or may not be required to this step. *Note: The “project number” that is required on the form is located within your project “Settings” menu within your API Manager.*
![step-4a](https://user-images.githubusercontent.com/136573/28741606-ce2b8b72-73ce-11e7-95c5-26e7dc608574.png)
![step-4b](https://user-images.githubusercontent.com/136573/28741605-ce28e98a-73ce-11e7-98a0-a234c715238c.png)


## A Note on Authenticating on a Limited-input Device
Normally when authenticating with OAuth you simply input your credentials into the device that needs access. For better or for worse, your Vain device does not have any inputs which means that the normal method of authenticating  with OAuth is not possible. As such we must use a protocol called "OAuth 2.0 For Limited-input Device". The full documentation for [OAuth2ForDevices is here.](https://developers.google.com/identity/protocols/OAuth2ForDevices). This codebase follows this protocol and each of the required steps and the corresponding code is documented within comments within the codebase. To keep things clear though, the steps for this protocol are included below:

1. Your application sends a request to Google's authorization server that identifies the scopes that your application will request permission to access.
2. The server responds with several pieces of information used in subsequent steps, such as a device code and a user code.
3. You display information that the user can enter on a separate device to authorize your app.
4. Your application starts polling Google's authorization server to determine whether the user has authorized your app.
5. The user switches to a device with richer input capabilities, launches a web browser, navigates to the URL displayed in step 3 and enters a code that is also displayed in step 3. The user can then grant (or deny) access to your application.
6. The next response to your polling request contains the tokens your app needs to authorize requests on the user's behalf. (If the user refused access to your application, the response does not contain tokens.)

The image below illustrates this process:

![deviceflow](https://user-images.githubusercontent.com/136573/28741718-8d0be4fe-73d1-11e7-87aa-a411f817bbe7.png)

([Image credit:](https://developers.google.com/identity/protocols/OAuth2ForDevices))


The scope that we will be using with this project is "https://www.googleapis.com/auth/analytics.readonly".


## Creating Your Webhooks

Webhooks are a mechanism for querying information from the web. You could certainly
make the applicable HTTP requests from the the device itself but using webhooks
decreases bandwidth usage and perhaps more importantly gives you better logging
and debugging capabilities than manual HTTP requests.

### Creating a webhook on Particle.io in order to query Real Time Active Users

This section is still being developed.
Description. Explain JSON.



Authenticating your device with Google's API requires three separate webhooks:

### 1. WEBHOOKNAME

This section is still being developed.

### 2. WEBHOOKNAME

This section is still being developed.

### 3. WEBHOOKNAME

This section is still being developed.


### A note on Mustaches

The Photon's firmware (which is written in C++) can't natively parse JSON. While
we could include a JSON parsing library in our code, we are going to use a simpler
method in order to maintain a small file size on the micro-controller program.

To do this, we format the webhook responses using a format called Mustache. You
can read the [Mustache format documentation](http://mustache.github.io/) here but
general idea is we are going to specify the keys of the JSON data that we want
and then separate these pieces of datum with tildes ~ so that we can then split
them in our code (this is an easy way to return multiple pieces of data from our
webhooks)


## Flashing Your Photon with the Vain Firmware
Now that the webhooks are created, we need to load firmware onto the Photon that
calls and processes these webhooks. The firmware that you need is the very same
firmware that is in this repo. To use it, all you need to do is download and then
upload it to your Photon.

This section is still being developed.

web based IDE is easiest? add instructions? Clean integration with github is a bit tricky


## Wiring Your Device
Now that your accounts are configured, the appropriate webhooks are setup
and the firmware is loaded onto your device, your last remaining step is to wire
up your micro-controller and display.

### Breadboard Diagram of a Simple LCD Display Setup

![vain - lcd breadboard](https://user-images.githubusercontent.com/136573/28605821-7bf1d534-7188-11e7-8153-0963185340b7.png)

Common LCD pin mappings are shown below but don't blindly trust these, check them
against your device's official documentation:

![common LCD pin mapping](https://user-images.githubusercontent.com/136573/28605838-953b324c-7188-11e7-8aac-433b90a65852.png)


## That's it!
You now have your very own tangible Google Analytics display. Your vanity can
now be known to all :-p

If you have an issues or code recommendation, feel free to submit pull requests
or issues via Github.


## Known Issues:
* The below issues should be moved to Github issues.
* Fix bug that creates 1 cycle lag between getting the user count and displaying the count
* Fix bug of when number of users gets stuck at last value when value switches to 0
* Fix bug that appears to be preventing code from executing after line 176
* Extract client_id and store as part of customer data? I don't want it stored in the generic webhook
* Implement more robust error handling, what happens if Google API requests don't return expected results?

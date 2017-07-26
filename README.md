# Vain: A Tangible Google Analytics Display

Vain is a Photon (a $20 web enabled micro-controller that is similar to an Arduino) based project that displays real-time Google Analytics data on a real-world display. Since the device does not have any physical user inputs, it relies on Google’s OAuth 2.0 for Limited-Input Device protocol for authenticating Google Analytics the appropriate Google Analytics account. Webhooks via [Particle.io’s free service](https://www.particle.io) are used to authenticate the device and then repeatedly request the amount of real-time active users on a given website. This data is then displayed on an external display.

## Required Hardware

* Particle Photon ([~$19.00 USD](https://www.sparkfun.com/products/13774))
* Display (Many display options can work but a Liquid Crystal Display is likely
	the cheapest and easiest option) ([~$15.00 USD](https://www.sparkfun.com/products/9052))
* Breadboard ([~$6.00](https://www.sparkfun.com/products/12615))
* Jumper Cables ([~$6.00](https://www.sparkfun.com/products/8431))

## Getting Access to Google’s APIs and Collecting Your Credentials


## A Note on Authenticating on a Limited-input Device
	[documentation for OAuth2ForDevices](https://developers.google.com/identity/protocols/OAuth2ForDevices)


## Creating Your Webhooks

  Webhooks are a mechanism for querying information from the web. You could request
  data from the device itself but using webhooks decreases bandwidth usage and gives
  you better logging and debugging capabilities than manual HTTP requests.

  ### Creating a webhook on Particle.io in order to query Real Time Active Users

  Description. Explain JSON.



  Authenticating your device with Google's API requires three seperate webhooks:

  ### 1. WEBHOOKNAME

  ### 2. WEBHOOKNAME

  ### 3. WEBHOOKNAME


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

  web based IDE is easiest? add instructions? Clean intergration with github is a bit tricky


## Wiring Your Device
  Now that your accounts are configured, the appropriate webhooks are setup
  and the firmware is loaded onto your device, your last remaining step is to wire
  up your micro-controller and display.

  ### Breadboard diagram of a simple LCD display setup
  ![vain - lcd_bb](https://user-images.githubusercontent.com/136573/28605821-7bf1d534-7188-11e7-8153-0963185340b7.png)

	Common LCD pin mappings are shown below (Although don't blindly trust this,
	check this against your device's official documentation):
	![pin mapping](https://user-images.githubusercontent.com/136573/28605838-953b324c-7188-11e7-8aac-433b90a65852.png)


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

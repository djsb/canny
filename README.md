canny
=====

Canny is a \$7 implementation of a controller for the cheap bulbs sold under the
brands MiLight, LimitlessLed, Easybulb or any other futlight clone.

It uses a ESP8266 device and a nRF24L01 radio module to directly interface with
the compatible bulbs.

*note: this project is not yet out-of-the-box deployable. Drop me a message if
you'd like to test.*

 

Features
--------

Canny pretends to overcome the limitations of these devices by bringing
additional features and reliability.

**Gateway capabilities:**

-   Individually control up to 2048 bulbs

**Software capabilities:**

-   Manual control over bulbs or groups of bulbs

-   Geofence rules

-   Timers

-   Bulbs as notification devices for smartphone calls, others

**IoT capabilities:**

-   Expandable to other usages over the Muzzley platform

**Security:**

-   Additional security to standard milight/easybulb bridge authentication

 

Requirements
------------

Canny relies on specific hardware and software requirements.

**Hardware:**

-   ESP8266 compatible module (amazon
    [link](https://www.amazon.com/NodeMcu-Internet-Things-Development-ESP8266/dp/B01H701G6M/ref=sr_1_16?s=pc&ie=UTF8&qid=1486169007&sr=1-16&keywords=esp8266))

-   nRF24L01 radio module (amazon
    [link](https://www.amazon.com/Leatest-2-4Ghz-nRF24L01-Transceiver-Module/dp/B007ZZANPA/ref=sr_1_1?s=pc&ie=UTF8&qid=1486169071&sr=1-1&keywords=nRF24L01))

-   some wiring to connect the ESP8266 and nRF24L01 (amazon
    [link](https://www.amazon.com/Header-Copper-Flexible-Arduino-Breadboard/dp/B0126HIIDA/ref=sr_1_3?s=pc&ie=UTF8&qid=1486169146&sr=1-3&keywords=arduino+wire))

**Software:**

-   Arduino.cc IDE ([link](http://arduino.cc/))

-   Arduino.cc with opened Canny project file (this project).

-   Arduino IDE: Installed support for the ESP8266 board: "Tools -\> Board”,
    selecting the correct ESP module

-   Arduino IDE: Correctly installed library: wifi manager

-   Arduino IDE: Correctly installed library: “MQTT” by Joel Gaelwiler

-   Arduino IDE: Correctly installed library: “arduino json” by Benoit Blanchon

 

Setup
-----

### Setup: Hardware Setup

 

### Setup: Muzzley developer account

 

### Setup: ESP8266 Arduino IDE Environment

1.  **Increase MQTT buffer size: ** Update the installed “MQTT” by Joel
    Gaelwiler library by editing the file “MQTTClient.h” inside the “src” folder
    from "\#define MQTT_BUFFER_SIZE 128” to "\#define MQTT_BUFFER_SIZE 512”

 

### Setup: Configuring and Uploading Code

 

First Time Usage
----------------

### First Time Usage: Configuring WiFi

For first time you deploy the software into the ESP8266 or if it cannot connect
to your WiFi network, it will automatically enter in configuration mode. You
should to the following steps:

1.  Connect your smartphone to a WiFi network named: “**CANNY-SETUP**"

2.  Wait a few seconds until you get a configuration screen. Follow the steps in
    order to connect your Canny gateway to your local network.

*note: after your configuration, due to a existing bug, you need to manually
reset the ESP8266. Just unplug the power cable.*

 

### First Time Usage: Pairing Bulbs

Once you get Canny connected to your local network, you’ll be able to configure
and control your home bulbs. Steps:

1.  Connect your smartphone to your local WiFi network (important step!).

2.  Download and open the Muzzley App. Follow the link: [Google
    Play](https://play.google.com/store/apps/details?id=com.muzzley&hl=en), [App
    Store](https://itunes.apple.com/pt/app/muzzley/id604133373?l=en&mt=8) or
    [Windows 10
    Store](https://www.microsoft.com/en-us/store/p/muzzley/9wzdncrdrjk1)

3.  Once you’re logged on Muzzley, click the Add Device button and scroll down
    to the Milight, Easybulb (Canny GW).

4.  Make sure your smartphone is connected to the same network as your Canny GW.
    Hit the Search button. Note: This is only for setup; you can later control
    the bulbs from the internet.

**More bulbs:** Repeat step 3 for each bulb you’d like to add to the Muzzley
app.

 

After you add a bulb to the Muzzley App you need to pair each entry to a
physical bulb. Do the following:

1.  On the Muzzley App press the bulb you’ve just added.

2.  You’ll find a pairing button on the top left corner of the screen. Press it.

3.  At the same time: Turn the bulb on (physical switch) and press the “Pair /
    Unpair” button.

4.  Your light should blink. If not, repeat step 3.

 

Improvements
------------

 

License
-------

Otherwise stated on individual project files, Canny's license is MIT.

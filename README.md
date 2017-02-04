canny
=====

Canny is a \$7 (hw components cost) implementation of a controller for the cheap
bulbs sold under the brands MiLight, LimitlessLed, Easybulb or any other
futlight clone.

It uses a ESP8266 device and a nRF24L01 radio module to directly interface with
the compatible bulbs.

![](https://cdn.muzzley.com/things/profiles/futlight/profile.jpg)

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

The hardware setup is quite simple if you have a ESP8266 development board with
physical pins for IO. All you have to do it connect both hardware modules and
power the main board.

-   **DIAGRAM**

The above diagram illustrates the connectivity between the ESP8266 and the
nRF24L01 module.

![](https://raw.githubusercontent.com/djsb/canny/master/ReadmeImages/nodemcu-nrf24l01-muzzley-crop.png)

-   **PICTURE**

![](https://raw.githubusercontent.com/djsb/canny/master/ReadmeImages/nodemcu-nrf24l01-muzzley-real.jpg)

### Setup: Muzzley developer account

This step is optional and you should consider it, if you’d like to fork this
project and have your own implementation or use Muzzley for business features
(example: have your own controlling App).

Otherwise, just proceed to the next step.

 

### Setup: ESP8266 Arduino IDE Environment

1.  **Increase MQTT buffer size:** Update the installed “MQTT” by Joel Gaelwiler
    library by editing the file “MQTTClient.h” inside the “src” folder from
    "\#define MQTT_BUFFER_SIZE 128” to "\#define MQTT_BUFFER_SIZE 512”

2.  Open the Canny.ino project into Arduino.cc IDE

3.  Compile

4.  Push code into arduino

*Note: If you have gone through the step “Setup: Muzzley developer account”, you
need to update Muzzley’s credentials at canny.ino file. Variables to update:
MProfileID, MUUID and MAppToken.*

 

### Setup: Configuring and Uploading Code

 

First Time Usage
----------------

Find the first usage guidelines, once you have deployed the software onto the
ESP8266 and you have all the hardware setup done.

### First Time Usage: Configuring WiFi

For first time you deploy the software into the ESP8266 or if it cannot connect
to your WiFi network, it will automatically enter in configuration mode. You
should to the following steps:

1.  Connect your smartphone to a WiFi network named: “**CANNY-SETUP**“.
    [Screenshot
    link](https://github.com/djsb/canny/blob/master/ReadmeImages/IMG_1654.PNG).

2.  Wait a few seconds until you get a configuration screen. Follow the steps in
    order to connect your Canny gateway to your local network. [Screenshot
    link](https://github.com/djsb/canny/blob/master/ReadmeImages/IMG_1655.PNG).

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

3.  Once you’re logged on Muzzley, click the **Add Device** button and scroll
    down to the Milight, Easybulb (Canny GW). [Screenshot
    link](https://github.com/djsb/canny/blob/master/ReadmeImages/IMG_1656.PNG).

4.  Make sure your smartphone is connected to the same network as your Canny GW.
    Hit the Search button. Note: This is only for setup; you can later control
    the bulbs from the internet. Screenshot link.

**More bulbs:** Repeat step 3 for each bulb you’d like to add to the Muzzley
app.

 

After you add a bulb to the Muzzley App you need to pair each entry to a
physical bulb. Do the following:

1.  On the Muzzley App press the bulb you’ve just added. [Screenshot
    link](https://github.com/djsb/canny/blob/master/ReadmeImages/IMG_1657.PNG).

2.  You’ll find a pairing button on the top left corner of the screen. Press it.
    [Screenshot
    link](https://github.com/djsb/canny/blob/master/ReadmeImages/IMG_1658.PNG).

3.  At the same time: Turn the bulb on (physical switch) and press the “Pair /
    Unpair” button. [Screenshot
    link](https://github.com/djsb/canny/blob/master/ReadmeImages/IMG_1659.PNG).

4.  Your light should blink. If not, repeat step 3.

 

Improvements
------------

Please send your feedback or pull requests.

Feature improvements:

-   Add hardreset button to clear wifi and paired bulbs configuration

-   Better Support for white only bulbs

Other project improvements:

-   3D print case

Credits
-------

This project uses libraries from other people as well as research made on the
milight protocol. Some credits:

-   Henryk Plotz: PL1167 promiscuous reverse engineering over protocol

-   Joel Gaelwiler: MQTT implementation

-   Benoit Blanchon: jSON Parser

License
-------

Otherwise stated on individual project files, Canny's license is MIT.

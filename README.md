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

 

Gateway capabilities:

-   Individually control up to 2048 bulbs

Software capabilities:

-   Manual control over bulbs or groups of bulbs

-   Geofence rules

-   Timers

-   Bulbs as notification devices for smartphone calls, others

IoT capabilities:

-   Expandable to other usages over the Muzzley platform

Security:

-   Additional security to standard milight/easybulb bridge authentication

 

Requirements
------------

Canny relies on specific hardware and software requirements.

Hardware:

-   ESP8266 compatible module (amazon
    [link](https://www.amazon.com/NodeMcu-Internet-Things-Development-ESP8266/dp/B01H701G6M/ref=sr_1_16?s=pc&ie=UTF8&qid=1486169007&sr=1-16&keywords=esp8266))

-   nRF24L01 radio module (amazon
    [link](https://www.amazon.com/Leatest-2-4Ghz-nRF24L01-Transceiver-Module/dp/B007ZZANPA/ref=sr_1_1?s=pc&ie=UTF8&qid=1486169071&sr=1-1&keywords=nRF24L01))

-   some wiring to connect the ESP8266 and nRF24L01 (amazon
    [link](https://www.amazon.com/Header-Copper-Flexible-Arduino-Breadboard/dp/B0126HIIDA/ref=sr_1_3?s=pc&ie=UTF8&qid=1486169146&sr=1-3&keywords=arduino+wire))



Setup
-----

### Setup: Hardware Setup

 

### Setup: Muzzley developer account

 

### Setup: ESP8266 Arduino IDE Environment

 

### Setup: Configuring and Uploading Code

 

First Time Usage
----------------

### First Time Usage: Configuring WiFi

 

### First Time Usage: Pairing Bulbs

 

Improvements
------------

 

License
-------

Otherwise stated on individual project files, Canny's license is MIT.

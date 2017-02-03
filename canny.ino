#include <DNSServer.h>
#include <FS.h>
#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <MQTTClient.h>
#include <SPI.h>
#include "RF24.h"
#include "PL1167_nRF24.h"
#include "MiLightRadio.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include "ESP8266SSDP.h" // for muzzley local discovery
#include "Data.h"
#include "SupportFunctions.h"
#include "MuzzleyRegister.h"
#include <ESP8266HTTPClient.h>



#define CE_PIN 2
#define CSN_PIN 15

RF24 radio(CE_PIN, CSN_PIN);
PL1167_nRF24 prf(radio);
MiLightRadio mlr(prf);
int sequence = 0xFF;
int globalcolor = 0x00;
int reset_counter = 0;

WiFiClientSecure net;
MQTTClient client;
WiFiManager wifiManager;

ESP8266WebServer HTTP(80);

Data data;
MuzzleyRegister muzzleyconf;
SupportFunctions sf;

// ********************* Declaring functions ****************************
void set_status(int ControlIDone, int ControlIDTwo, int ControlIDThree, bool status);
void send_command(int outgoingPckt [7]);
void set_brightness(int ControlIDone, int ControlIDTwo, int ControlIDThree, int bright);
void set_maxwhite(int ControlIDone, int ControlIDTwo, int ControlIDThree);
void circle_brightness();
void set_color(int ControlIDone, int ControlIDTwo, int ControlIDThree, int color);
void set_pair(int ControlIDone, int ControlIDTwo, int ControlIDThree, String component);


// ********************* WiFi, status and first setup *******************

//gets called when WiFiManager enters configuration mode
void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
  //entered config mode, make led toggle faster
}




void connect(); // <- predefine connect() for setup()

void setup() {
  Serial.begin(115200);
  
  SPIFFS.begin();
  //SPIFFS.format();

  

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  //reset settings - for testing
  //wifiManager.resetSettings();

  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect("CANNY-SETUP")) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  }

 
  delay(200);
  // init Muzzley DeviceKey and SerialNumber
  String deviceKey; // = "bc0ca451-25c7-4fee-9c45-df03f87e7e5d";
  uint8_t mac[6];
  WiFi.macAddress(mac);
  String serialNumber = sf.macToStr(mac);

  muzzleyconf.getDeviceKey(&deviceKey, &serialNumber);
  if (deviceKey == ""){
    Serial.println("D: 1001");
      
      HTTPClient httpclient;
      httpclient.begin("http://global-manager.muzzley.com/deviceapp/register");
    
      httpclient.POST("{\"profileId\": \"555b46d0db93b4a08a9c9b38\",\"serialNumber\": \"" + serialNumber + "\"}");
      
      muzzleyconf.registerDeviceKey(serialNumber, httpclient.getString(), &deviceKey);
      httpclient.end();
      ESP.restart();
  }else{
    // found device Key
    Serial.println("D: 1000");
  }



 
  // initialize SSD discovery
  //Serial.println("Starting SSDP...\n");
  SSDP.setDeviceType("urn:Muzzley:device:56f5ac9fca1a124ae2906977:1");
  SSDP.setSchemaURL("description.xml");
  SSDP.setHTTPPort(80);
  SSDP.setName("Muzzley");
  SSDP.setSerialNumber(serialNumber);
  SSDP.setMACAddress(sf.macToStr(mac));
  SSDP.setURL("index.html");
  SSDP.setModelName("Muzzley");
  //SSDP.setModelNumber("929000226503");
  SSDP.setModelURL("http://www.canny.io");
  SSDP.setManufacturer("Canny");
  SSDP.setManufacturerURL("http://canny.io");
  SSDP.setDeviceKey(deviceKey);
  SSDP.begin();



  // initiliaze web server
  HTTP.on("/index.html", HTTP_GET, [](){
    Serial.println("HTTP index.html request");
    HTTP.send(200, "text/plain", "Future Canny configuration tool!");
  });
  HTTP.on("/description.xml", HTTP_GET, [](){
    //Serial.println("\ndescription.xml requested");
    SSDP.schema(HTTP.client());
  });
  HTTP.begin();



  client.begin("geoplatform.muzzley.com", 8883, net); // MQTT brokers usually use port 8883 for secure connections
  //connect();
  
  //data.mountbulbdata();

  delay (200);
  mlr.begin();

}



void connect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("\nAttempting MQTT connection...");
    delay (10); // TODO djsb - crash without this
    if (client.connect("ESP8266Client", "40e30d82-7cd2-477c-b3b0-700e184e0652", "2a3a08767d145205")) {
      Serial.println("connected");
      client.subscribe("v1/iot/profiles/56f5ac9fca1a124ae2906977/channels/1372ce90-d539-491b-b046-ef5b24aad3a5/#");
    } else {
      Serial.print("failed, rc=");
      Serial.println(" try again in 5 seconds");
      delay(1000);
    }
  }
}


void loop() {
  client.loop();
  delay(20);
  
  if (!client.connected()) {
    connect();
  }



  if (mlr.available()) {
    uint8_t packet[7];
    size_t packet_length = sizeof(packet);
    mlr.read(packet, packet_length);
    printf("\nReceived packet: ");
    for (int i = 0; i < packet_length; i++) {
      printf("%02X ", packet[i]);
    }
  }

  // check if the reset button is pressed. If so, enable reset procedure
  // TODO: The reset procedure is making the device crash

  // handle http
  HTTP.handleClient();
}


void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  Serial.print("\nIncoming message: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.print(payload);
  Serial.println();

  String component = sf.getValue(topic, '/', 7);
  String properties = sf.getValue(topic, '/', 9);

  // get bulb details (if bulb is known)
  String config = data.get_config();
  DynamicJsonBuffer jsonBuf;
  JsonObject& bulb = jsonBuf.parseObject(config);

  // initialize bulb properties
  int ControlIDone = 0;
  int ControlIDTwo = 0;
  int ControlIDThree = 0;
  bool status = false;
  int brightness = 0;
  int colorr = 0;
  int colorg = 0;
  int colorb = 0;

  // check if this bulb exists in the json bulb data
  if (bulb.containsKey(component))
  {
    //Serial.println("messageReceived(): Bulb already exists");
    ControlIDone = bulb[component]["ControlIDone"];
    ControlIDTwo = bulb[component]["ControlIDTwo"];
    ControlIDThree = bulb[component]["ControlIDThree"];
    status = bulb[component]["state"]["status"];
    brightness = bulb[component]["state"]["brightness"];
    colorr = bulb[component]["state"]["colorr"];
    colorg = bulb[component]["state"]["colorg"];
    colorb = bulb[component]["state"]["colorb"];  
  }else{
    //Serial.println("messageReceived(): Bulb does not yet exist");
    data.add_bulb(component);
    // after updating the json with the new bulb, reload the json
    config = data.get_config();
    JsonObject& bulb = jsonBuf.parseObject(config);
  }
  
  bulb.printTo(Serial);

  ControlIDone = bulb[component]["ControlIDone"];
  ControlIDTwo = bulb[component]["ControlIDTwo"];
  ControlIDThree = bulb[component]["ControlIDThree"];
  status = bulb[component]["state"]["status"];
  brightness = bulb[component]["state"]["brightness"];
  colorr = bulb[component]["state"]["colorr"];
  colorg = bulb[component]["state"]["colorg"];
  colorb = bulb[component]["state"]["colorb"];

  // parse topic
  if (properties == "assign-button"){
    set_pair(ControlIDone, ControlIDTwo, ControlIDThree, component);
  }

  // parse json payload
  StaticJsonBuffer<400> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(payload);

  // check if the following operations are actions to perform on the device
  if ((strcmp (root["io"],"w") == 0)){
  
    // Set status (on/off)
    if ((properties == "status")){
      bool status = root["data"]["value"];
      set_status(ControlIDone, ControlIDTwo, ControlIDThree, status);
      data.update_bulb_state(component, properties, status);
    }
  
    // Set color RGB
    if ((properties == "color")){
      byte r = root["data"]["value"]["r"];
      byte g = root["data"]["value"]["g"];
      byte b = root["data"]["value"]["b"];
      int hue = int(sf.rgbToHue(r,g,b) * 100);
      
      // if the user presses the white color button, override the HUE to 1024. 
      if ((r == 255) && (g == 255) && (b == 255)){
        set_maxwhite(ControlIDone, ControlIDTwo, ControlIDThree);
      }
      else{
        set_color(ControlIDone, ControlIDTwo, ControlIDThree, hue);
      }

      // update the bulb state for color r, g, b
      int colorr = root["data"]["value"]["r"];
      int colorg = root["data"]["value"]["g"];
      int colorb = root["data"]["value"]["b"];
      data.update_bulb_state(component, "colorr", colorr);
      data.update_bulb_state(component, "colorg", colorg);
      data.update_bulb_state(component, "colorb", colorb);
    }

  // Set brightness. From 0 to 1
    if ((properties == "brightness")){
      double bright = root["data"]["value"];
      int brightness = bright*100;
      set_brightness(ControlIDone, ControlIDTwo, ControlIDThree, bright*100);
      data.update_bulb_state(component, properties, brightness);
    }
  } // end of Muzzley IO Write actions
}

// ******************* Mi Light Features ****************

void set_maxwhite(int ControlIDone, int ControlIDTwo, int ControlIDThree){  
  int outgoingPacket2 [7] = { ControlIDone, ControlIDTwo, ControlIDThree, 0x00, 0x00, 0x13, sequence++};
  send_command(outgoingPacket2);
}


void circle_brightness(int ControlIDone, int ControlIDTwo, int ControlIDThree){

 for (int brightnessi=1; brightnessi<=100; brightnessi++){
   set_brightness(ControlIDone, ControlIDTwo, ControlIDThree, brightnessi);
 }
}

void set_color(int ControlIDone, int ControlIDTwo, int ControlIDThree, int color){
  int newcolor = map(color, 0, 99, 0x00, 0xFF);
  
  int counter=0;
  int newbright = 0x90;
  counter++;
  
  int outgoingPacket2 [7] = { ControlIDone, ControlIDTwo, ControlIDThree, newcolor, 0xA8, 0x0F, sequence++};
  send_command(outgoingPacket2);

  globalcolor = newcolor;
}

void set_brightness(int ControlIDone, int ControlIDTwo, int ControlIDThree, int bright){ 
 int brightnessi = map(bright, 0, 100, 1, 28);
 int counter=0;
 int newbright = 0x90;
    counter++;
    if (brightnessi >= 1 && brightnessi <=19){
      newbright = 0x88 - (brightnessi * 0x08);
    }

    if (brightnessi > 19 && brightnessi <=28){
      newbright = 0xF8 - ((brightnessi-20) * 0x08);
    }
  
    int outgoingPacket2 [7] = { ControlIDone, ControlIDTwo, ControlIDThree, globalcolor++, newbright, 0x0E, sequence++};
    send_command(outgoingPacket2);

}

void set_status(int ControlIDone, int ControlIDTwo, int ControlIDThree, bool status){
 // 0x03 for on, 0x04 for off
 int bulbstatus = 0x03;
 if (status==true)
   bulbstatus = 0x03;
 if (status==false)
   bulbstatus = 0x04;

  int outgoingPacket2 [7] = { ControlIDone, ControlIDTwo, ControlIDThree, globalcolor, 0XD1, bulbstatus, sequence++};
  send_command(outgoingPacket2);
}


void set_pair(int ControlIDone, int ControlIDTwo, int ControlIDThree, String component){

  // search ID of component
  Serial.println(component);
  
  
 int outgoingPacket2 [7] = { ControlIDone, ControlIDTwo, ControlIDThree, globalcolor, 0XD1, 0x03, sequence++};
 send_command(outgoingPacket2);

 int outgoingPacket3 [7] = { ControlIDone, ControlIDTwo, ControlIDThree, globalcolor, 0xD1, 0x13, sequence++};
 send_command(outgoingPacket3);
 delay (300);
 send_command(outgoingPacket3);
}

void send_command(int outgoingPckt [7]){
  
  uint8_t outgoingPacket_tmp [7] ;
  for (int i = 0; i < 7; i++)
  {
    outgoingPacket_tmp[i] = (uint8_t)outgoingPckt[i];
  }

  mlr.write(outgoingPacket_tmp, sizeof(outgoingPacket_tmp));
  printf("\nSending packet: ");
  for (int ps = 0; ps < sizeof(outgoingPacket_tmp); ps++) {
    printf("%02X ", outgoingPacket_tmp[ps]);   
  }
  delay(50);

  // send the instruction multiple times
  for (int resendcounter = 0; resendcounter < 50; resendcounter++)
  {
    mlr.resend();
    delay(1);
  }
  printf("Sent!");
}














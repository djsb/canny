#include <Arduino.h>
#include <FS.h>
#include <ArduinoJson.h>
#include "MuzzleyRegister.h"
#include "SupportFunctions.h"




// constructor
MuzzleyRegister::MuzzleyRegister()
{
  int _serialNumber = 010;
}

void MuzzleyRegister::getDeviceKey(String *d1, String *d2){

    if (SPIFFS.exists("/muzzleyconfig.json")) {
      //file exists, reading and loading
      //Serial.println("MuzzleyRegister::getDeviceKey(): reading config file");
      File configFile = SPIFFS.open("/muzzleyconfig.json", "r");
      if (configFile) {
        //Serial.println("MuzzleyRegister::getDeviceKey(): opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          //Serial.println("\nMuzzleyRegister::getDeviceKey(): parsed json");
          String tmpjson = json["deviceKey"];
          String tmpserial = json["serialNumber"];
          *d1 = tmpjson;
          *d2 = tmpserial;
          configFile.close();
          
        } else {
          Serial.println("MuzzleyRegister::getDeviceKey(): failed to load json config");
        } 
      }
    }else{
      Serial.println("MuzzleyRegister::getDeviceKey(): config file does not exist. Calling Muzzley register...");

      // register on Muzzley and get deviceKey

      
    } 

  
  
}


void MuzzleyRegister::save_config(String deviceKey, String serialNumber)
{

  DynamicJsonBuffer jsonBuffer;
  JsonObject& settings = jsonBuffer.createObject();
  settings["deviceKey"] = deviceKey;
  settings["serialNumber"] = serialNumber;

  File configFile = SPIFFS.open("/muzzleyconfig.json", "w");

  if (!configFile) {
    Serial.println("failed to open config file for writing");
  }

  settings.printTo(configFile);
  configFile.close();

}


void MuzzleyRegister::registerDeviceKey(String serialNumber, String payload, String *_deviceKey) {

  // extract from pauyload the deviceKey
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(payload);
  if (json.success()) {
    String deviceKey = json["deviceKey"];
    *_deviceKey = deviceKey;

    // save device key to muzzleyconfig.json
    save_config(deviceKey, serialNumber);
    
  } else {
    Serial.println("E: 1002");
  }



}



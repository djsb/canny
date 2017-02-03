#include <Arduino.h>
#include "Data.h"
#include <FS.h>
#include <ArduinoJson.h>

Data::Data()
{

}


void Data::printconfig() {

    if (SPIFFS.exists("/bulbdata.json")) {
      File configFile = SPIFFS.open("/bulbdata.json", "r");

      while (configFile.available()) {
        //Lets read line by line from the file
        String line = configFile.readString();
        Serial.println(line);
      }
      configFile.close();
    } else {
      Serial.println("printconfig: failed to open bulbdata.json");
    }

 
  //end read
}


void Data::mountbulbdata() {
  //clean FS, for testing
  //SPIFFS.format();

  //read configuration from FS json
  //Serial.println("mounting Buµlb FS...");


    //Serial.println("  . starting");
    if (SPIFFS.exists("/bulbdata.json")) {
      File configFile = SPIFFS.open("/bulbdata.json", "r");

      printconfig();

      if (configFile) {
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        if (json.success()) {
          //Serial.println("\nbulbdata parsed json");
        } else {
          Serial.println("failed to load bulb data file");
        }
      }
    }

  //end read
}

String Data::get_config() {
  if (SPIFFS.exists("/bulbdata.json")) {
    File configFile = SPIFFS.open("/bulbdata.json", "r");

    if (configFile) {
      size_t size = configFile.size();
      // Allocate a buffer to store contents of the file.
      std::unique_ptr<char[]> buf(new char[size]);

      configFile.readBytes(buf.get(), size);
      DynamicJsonBuffer jsonBuffer;
      JsonObject& json = jsonBuffer.parseObject(buf.get());
      //json.printTo(Serial);
      if (json.success()) {
        //Serial.println("\nbulbdata parsed json");
        String tmpjson;
        json.printTo(tmpjson);
        configFile.close();
        return tmpjson;
      } else {
        Serial.println("Data::get_config(): failed to parse bulb data file");
        return "";
      }
    }
  } else {
    Serial.println("Data::get_config(): File does not exist");
    return "";
  }
}



void Data::save_config(JsonObject& root)
{
  File configFile = SPIFFS.open("/bulbdata.json", "w");

  if (!configFile) {
    Serial.println("failed to open config file for writing");
  }

  root.printTo(configFile);
  configFile.close();
}

void Data::create_component(JsonObject& root, String component)
{

  //genenate control ID
  int randOne = 0xB0;
  int randTwo = 0x27; randTwo = random(0x27, 0x88);
  int randThree = 0x59; randThree = random(0x10, 0x6D);


  JsonObject& bulb = root.createNestedObject(component);
  bulb["ComponentID"] = component;
  bulb["type"] = 1; // 1 for color, 2 for white, ...
  bulb["ControlIDone"] = randOne;
  bulb["ControlIDTwo"] = randTwo;
  bulb["ControlIDThree"] = randThree;
  JsonObject& state = bulb.createNestedObject("state");
  state["status"] = false;
  state["brightness"] = 254;
  state["colorr"] = 0;
  state["colorg"] = 0;
  state["colorb"] = 0;

  // save to file
  save_config(root);
}

// Updates a specific state for a component
bool Data::update_bulb_state(String component, String properties, int value){
  String config = get_config();
  DynamicJsonBuffer jsonBuffer;
  JsonObject& obj = jsonBuffer.parseObject(config);

  JsonObject& bulb = obj[component];
  bulb["ComponentID"] = bulb["ComponentID"];
  bulb["type"] = bulb["type"];
  bulb["ControlIDone"] = bulb["ControlIDone"];
  bulb["ControlIDTwo"] = bulb["ControlIDTwo"];
  bulb["ControlIDThree"] = bulb["ControlIDThree"];

  // keeping previous states
  int status = bulb["state"]["status"];
  int brightness = bulb["state"]["brightness"];
  int colorr = bulb["state"]["colorr"];
  int colorg = bulb["state"]["colorg"];
  int colorb = bulb["state"]["colorb"];
  
  JsonObject& state = bulb.createNestedObject("state");

  // update the color Status
  if (properties == "status"){
    state["status"] = value;
  }else{
    state["status"] = status;
  }

  // update the color Brightness
  if (properties == "brightness"){
    state["brightness"] = value;
  }else{
    state["brightness"] = brightness;
  }

  // update the color R
  if (properties == "colorr"){
    state["colorr"] = value;
  }else{
    state["colorr"] = colorr;
  }

  // update the color G
  if (properties == "colorg"){
    state["colorg"] = value;
  }else{
    state["colorg"] = colorg;
  }
  
  // set the color B
  if (properties == "colorb"){
    state["colorb"] = value;
  }else{
    state["colorr"] = colorb;
  }


  // save to file
  save_config(obj);

}


// returns 0/false if doesn't exist; 1/true if exists
bool Data::search_bulb(String component){
  String config = get_config();
  DynamicJsonBuffer jsonBuffer;
  JsonObject& obj = jsonBuffer.parseObject(config);
  bool exists = false;
  if (obj.containsKey(component))
  {
    exists = true;
  }else{
    exists = false;
  }
  return exists;
}

void Data::add_bulb(String component)
{
  String config = get_config();
  DynamicJsonBuffer jsonBuffer;
  JsonObject& obj = jsonBuffer.parseObject(config);
  create_component(obj, component);

}


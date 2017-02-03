#ifndef Data_h
#define Data_h

#include <ArduinoJson.h>


class Data
{
  public:
    Data();
    void printconfig();
    void save_config(JsonObject& root);
    void mountbulbdata();
    void create_component(JsonObject& root, String component);
    String get_config();
    bool search_bulb(String component);
    bool update_bulb_state(String component, String properties, int value);
    void add_bulb(String component);
  private:
};

#endif


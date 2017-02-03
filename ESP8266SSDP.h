/*

Fork of the ESP8266 SSDP to extend Muzzley discovery protocol

*/

#ifndef ESP8266SSDP_H
#define ESP8266SSDP_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

class UdpContext;

#define SSDP_UUID_SIZE              37
#define SSDP_SCHEMA_URL_SIZE        64
#define SSDP_DEVICE_TYPE_SIZE       64
#define SSDP_FRIENDLY_NAME_SIZE     64
#define SSDP_SERIAL_NUMBER_SIZE     32
#define SSDP_PRESENTATION_URL_SIZE  128
#define SSDP_MAC_SIZE  32
#define SSDP_MODEL_NAME_SIZE        64
#define SSDP_MODEL_URL_SIZE         128
#define SSDP_MODEL_VERSION_SIZE     32
#define SSDP_MANUFACTURER_SIZE      64
#define SSDP_MANUFACTURER_URL_SIZE  128
#define SSDP_DEVICEKEY_SIZE  128

typedef enum {
  NONE,
  SEARCH,
  NOTIFY
} ssdp_method_t;


struct SSDPTimer;

class SSDPClass{
  public:
    SSDPClass();
    ~SSDPClass();

    bool begin();

    void schema(WiFiClient client);

    void setDeviceType(const String& deviceType) { setDeviceType(deviceType.c_str()); }
    void setDeviceType(const char *deviceType);
    void setName(const String& name) { setName(name.c_str()); }
    void setName(const char *name);
    void setURL(const String& url) { setURL(url.c_str()); }
    void setURL(const char *url);
    void setSchemaURL(const String& url) { setSchemaURL(url.c_str()); }
    void setSchemaURL(const char *url);
    void setSerialNumber(const String& serialNumber) { setSerialNumber(serialNumber.c_str()); }
    void setSerialNumber(const char *serialNumber);
    void setSerialNumber(const uint32_t serialNumber);
    void setModelName(const String& name) { setModelName(name.c_str()); }
    void setModelName(const char *name);
    void setModelNumber(const String& num) { setModelNumber(num.c_str()); }
    void setModelNumber(const char *num);
    void setModelURL(const String& url) { setModelURL(url.c_str()); }
    void setModelURL(const char *url);
    void setManufacturer(const String& name) { setManufacturer(name.c_str()); }
    void setManufacturer(const char *name);
    void setManufacturerURL(const String& url) { setManufacturerURL(url.c_str()); }
    void setManufacturerURL(const char *url);
    void setHTTPPort(uint16_t port);
    void setMACAddress(const String& mac) { setMACAddress(mac.c_str()); };
    void setMACAddress(const char *mac);
    void setDeviceKey(const String& deviceKey) { setDeviceKey(deviceKey.c_str()); };
    void setDeviceKey(const char *deviceKey);
    void setTTL(uint8_t ttl);

  protected:
    void _send(ssdp_method_t method);
    void _update();
    void _startTimer();
    static void _onTimerStatic(SSDPClass* self);

    UdpContext* _server;
    SSDPTimer* _timer;
    uint16_t _port;
    uint8_t _ttl;

    IPAddress _respondToAddr;
    uint16_t  _respondToPort;

    bool _pending;
    unsigned short _delay;
    unsigned long _process_time;
    unsigned long _notify_time;

    char _schemaURL[SSDP_SCHEMA_URL_SIZE];
    char _uuid[SSDP_UUID_SIZE];
    char _deviceType[SSDP_DEVICE_TYPE_SIZE];
    char _friendlyName[SSDP_FRIENDLY_NAME_SIZE];
    char _serialNumber[SSDP_SERIAL_NUMBER_SIZE];
    char _presentationURL[SSDP_PRESENTATION_URL_SIZE];
    char _macAddress[SSDP_MAC_SIZE];
    char _manufacturer[SSDP_MANUFACTURER_SIZE];
    char _manufacturerURL[SSDP_MANUFACTURER_URL_SIZE];
    char _deviceKey[SSDP_DEVICEKEY_SIZE];
    char _modelName[SSDP_MODEL_NAME_SIZE];
    char _modelURL[SSDP_MODEL_URL_SIZE];
    char _modelNumber[SSDP_MODEL_VERSION_SIZE];
};

extern SSDPClass SSDP;

#endif


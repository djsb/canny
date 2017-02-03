#ifndef MuzzleyRegister_h
#define MuzzleyRegister_h

class MuzzleyRegister
{
  public:
    MuzzleyRegister();
    void getDeviceKey(String *d1, String *d2);
    void registerDeviceKey(String serialNumber, String payload, String *deviceKey);
    void save_config(String deviceKey, String serialNumber);

  private:

};

#endif


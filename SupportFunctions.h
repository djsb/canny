#ifndef SupportFunctions_h
#define SupportFunctions_h

class SupportFunctions
{
  public:
    SupportFunctions();
    String getValue(String data, char separator, int index);
    double rgbToHue(byte r, byte g, byte b);
    double threeway_max(double a, double b, double c);
    double threeway_min(double a, double b, double c);
    String macToStr(const uint8_t* mac);
    String randomStr(int length, String *randomstring);
  private:
};

#endif


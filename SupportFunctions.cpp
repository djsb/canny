#include <Arduino.h>
#include "SupportFunctions.h"


// constructor
SupportFunctions::SupportFunctions()
{

}

String SupportFunctions::getValue(String data, char separator, int index) {
 int found = 0;
  int strIndex[] = {
0, -1  };
  int maxIndex = data.length()-1;
  for(int i=0; i<=maxIndex && found<=index; i++){
  if(data.charAt(i)==separator || i==maxIndex){
  found++;
  strIndex[0] = strIndex[1]+1;
  strIndex[1] = (i == maxIndex) ? i+1 : i;
  }
 }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}


double SupportFunctions::rgbToHue(byte r, byte g, byte b) { 
    double rd = (double) r/255;
    double gd = (double) g/255;
    double bd = (double) b/255;
    double max = threeway_max(rd, gd, bd);
    double min = threeway_min(rd, gd, bd);
    double h, s, l = (max + min) / 2;

    if (max == min) {
        h = s = 0; // achromatic
    } else {
        double d = max - min;
        s = l > 0.5 ? d / (2 - max - min) : d / (max + min);
        if (max == rd) {
            h = (gd - bd) / d + (gd < bd ? 6 : 0);
        } else if (max == gd) {
            h = (bd - rd) / d + 2;
        } else if (max == bd) {
            h = (rd - gd) / d + 4;
        }
        h /= 6;
    }
    return h;
}

double SupportFunctions::threeway_max(double a, double b, double c) {
    return max(a, max(b, c));
}

double SupportFunctions::threeway_min(double a, double b, double c) {

    return min(a, min(b, c));
}

String SupportFunctions::macToStr(const uint8_t* mac)
{
  String result;
  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);
    if (i < 5)
      result += ':';
  }
  return result;
}

String SupportFunctions::randomStr(int length, String *randomstring)
{

  char letters[] = {'a', 'b','c', 'd', 'e', 'f', 'g', 'h', 'i', 'j','k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'x', 'y', 'z'};
  const byte lettersLength = sizeof(letters) / sizeof(letters[0]);

  for (int n = 0; n < length ; n++)
  {
    *randomstring = String(*randomstring + letters[random(0, lettersLength)]);
  }


}



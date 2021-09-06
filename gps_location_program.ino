#include <TinyGPS++.h>
#include <SoftwareSerial.h>

float latitude , longitude;

String lat_str , lng_str;
int pm;

TinyGPSPlus  gps;              // The TinyGPS++ object
SoftwareSerial  ss(5, 6) ;   // The serial connection to the GPS device. tx,rx

void setup() {
Serial.begin(115200);
  ss.begin(9600);
}

void loop()
{
  while (ss.available() > 0)
  
    if (gps.encode(ss.read()))
    {
      if (gps.location.isValid())
      {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6);
        longitude = gps.location.lng();
        lng_str = String(longitude , 6);
      }

     
Serial.print("lan :" + lat_str );
Serial.print("\t");
Serial.print("lng :" + lng_str);
//Serial.print("date :" + date_str);
//Serial.print(" time :" + time_str); 
Serial.println();
delay(500);
    }
    }

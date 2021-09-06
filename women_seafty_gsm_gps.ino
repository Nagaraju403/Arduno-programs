#include <SoftwareSerial.h>
#include <TinyGPS++.h>
SoftwareSerial mySerial(9, 10);   // gsm   gps---tx,rx
String str;
float latitude , longitude;
void SendMessage();
String lat_str , lng_str;
int pm;
int button=13;
TinyGPSPlus  gps;  
void setup(){
  mySerial.begin(9600);   // Setting the baud rate of GSM Module 
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
  pinMode(button,INPUT_PULLUP);
}
void loop(){
 int b=digitalRead(button);
 if(b==0){
  SendMessage();
 }
mylocation();
}
 void SendMessage(){
  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.println("AT+CMGS=\"+919493393702\"\r");
  delay(1000);
  str="mylocation of lat"+lat_str +" lon " + lng_str+" hear i am waiting for you";
  mySerial.println(str);
  delay(1000);
  mySerial.println((char)26);
  delay(1000);
}
void mylocation(){
    while (Serial.available() > 0)
  
    if (gps.encode(Serial.read()))
    {
      if (gps.location.isValid())
      {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6);
        longitude = gps.location.lng();
        lng_str = String(longitude , 6);
      }
}
}

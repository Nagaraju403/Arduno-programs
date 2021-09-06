// slider v0, gauge v1
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "pn72OxcjcfVwyZTrznwKnwwe6FDf8dLT";
char ssid[] = "DESKTOP-LBTA2FN 3846";
char pass[] = "123456789";

BLYNK_WRITE(V0)
{
  int pinValue = param.asInt();  
  // String i = param.asStr();
  // double d = param.asDouble();
  
  analogWrite(D1,pinValue);
  Blynk.virtualWrite(V1, pinValue);
  Serial.print("V0 Slider value is: ");
  Serial.println(pinValue);
}
void setup()
{
  pinMode(D1,OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}
void loop()
{
  Blynk.run();
}

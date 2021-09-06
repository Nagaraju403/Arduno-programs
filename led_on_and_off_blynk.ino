#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "a3MX8FECPL-9tOWHucKZIf1oVrOkkVVW";
char ssid[] = "BNR";
char pass[] = "nagaraju";

void setup()
{
  pinMode(D1,OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
} 
  BLYNK_WRITE(1)     // v1
  {
    int led = param.asInt();
    if(led==1)
    digitalWrite(D1,HIGH);
    else
    digitalWrite(D1,LOW);
  }
void loop()
{
  Blynk.run();
}

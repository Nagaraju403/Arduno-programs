#define BLYNK_PRINT Serial
#include<ESP8266WiFi.h>
#include<BlynkSimpleEsp8266.h>
#include<DHT.h>
String i;

char auth[] = "Al-OhlSxLfqOz-8VeCZ9-HMR_3lTV8pZ";
char ssid[] = "BNR";
char pass[] = "nagaraju";

#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);

void setup()
{
  Serial.begin(9600);
    Blynk.begin(auth,ssid,pass);
  pinMode(D4,INPUT);
  dht.begin();
}

void sendSensor()  // fun defination
{
  float h=dht.readHumidity();
  float t=dht.readTemperature();
  Blynk.virtualWrite(V5,h);      // V5 blynk humidity pin
  Blynk.virtualWrite(V6,t);      // V6 blynk temp pin 
  Blynk.virtualWrite(V4,i.toInt());
}

void loop()
{
   i=Serial.readString();
  sendSensor();
  Blynk.run();
}

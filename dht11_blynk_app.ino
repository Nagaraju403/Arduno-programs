#define BLYNK_PRINT Serial
#include<ESP8266WiFi.h>
#include<BlynkSimpleEsp8266.h>
#include<DHT.h>

char auth[ ] = "o0Pt1Icx-Co6AmZIxwmTa33gsD85pNUa";
char ssid[ ] = "BNR";
char pass[ ] = "nagaraju";

#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
SimpleTimer timer;

void sendSensor()
{
  float h=dht.readHumidity();
  float t=dht.readTemperature();

  if(isnan(h) || isnan(t))
  {
    Serial.println("Failed to read from DHT sensor data..!");
    return;
  }
  Blynk.virtualWrite(V5,h);      // V5 blynk humidity pin
  Blynk.virtualWrite(V6,t);      // V6 blynk temp pin 
}
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth,ssid,pass);
  pinMode(D4,INPUT);
  dht.begin();
  timer.setInterval(1000L,sendSensor);
}
void loop()
{
  Blynk.run();
  timer.run();
}

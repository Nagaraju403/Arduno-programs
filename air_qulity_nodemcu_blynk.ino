#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"
    
#define DHTPIN D2     
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

char auth[] = "gqGOfuQrVQsu98nsCaeq2zzWb0g5-21j"; 
char ssid[] = "BNR"; // Enter WIFI Name Here
char pass[] = "nagaraju"; // Enter WIFI Password Here
 
int mq5 = D5;  
int mq135 = A0;
int mq5_data = 0; 
int mq135_data = 0;
void setup() 
{
  Serial.begin(9600);
  dht.begin();
  Blynk.begin(auth, ssid, pass);
  pinMode(D4,INPUT);
  pinMode(D5,INPUT);
}
 
void sendSensor()
{
 float h = dht.readHumidity();
  float t = dht.readTemperature();
  mq5_data = digitalRead(mq5);
  mq135_data = analogRead(mq135); 

Serial.println(h);
Serial.println(t);
Serial.println(mq5_data);
Serial.println(mq135_data);
  
  Blynk.virtualWrite(V2, mq5_data);
  Blynk.virtualWrite(V3, mq135_data);
  Blynk.virtualWrite(V5,h);      // V5 blynk humidity pin
  Blynk.virtualWrite(V6,t);      // V6 blynk temp pin 

}

void loop()
{
  sendSensor();
  Blynk.run();
}

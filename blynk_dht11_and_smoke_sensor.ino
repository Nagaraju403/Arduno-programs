#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHTesp.h"

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif
int Sensor_PIN  = D3;            //D3
int sensorValue;
int gas_sensor=A0;

DHTesp dht;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "cEQrIa5B6C-k_808atMH456JssD5GSdQ";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "BNR";
char pass[] = "nagaraju";

float Temperature;
float Humidity;

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  Temperature = dht.getTemperature(); // Gets the values of the temperature
  Humidity = dht.getHumidity(); // Gets the values of the humidity
  sensorValue = analogRead(A0);
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, Temperature);
  Blynk.virtualWrite(V6, Humidity);
  //Blynk.virtualWrite(V4,sensorValue);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  dht.setup(Sensor_PIN, DHTesp::DHT11);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
timer.setInterval(1000L,getSendData);
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}

void getSendData()
{
sensorValue = analogRead(A0);
  Blynk.virtualWrite(V4,sensorValue); //virtual pin V3

  if (sensorValue > 900 )
  {
    Blynk.notify("Smoke Detected!!!");
  }
 
}

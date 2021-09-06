#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME680 bme;

float Temperature;
float Humidity;
float Pressure;
float Gas;
float Altitude;
float DewPont;

BlynkTimer timer;

char auth[] = " xxx-xxxx-xxx";
char ssid[] = "xxx-xxxx-xxx";
char pass[] = "xxx-xxxx-xxx";

void setup()
{
  Blynk.begin(auth, ssid, pass);
  bme.begin(0x76);

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
  
  timer.setInterval(2000L, bme680);
}

void bme680()
{
  Temperature = bme.readTemperature();
  Blynk.virtualWrite(V1, Temperature);

  Humidity = bme.readHumidity();
  Blynk.virtualWrite(V2, Humidity);

  Pressure = bme.readPressure() / 100.0F;
  Blynk.virtualWrite(V3, Pressure);

  Altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  Blynk.virtualWrite(V4, Altitude);

  Gas = (bme.gas_resistance / 1000.0);
  Blynk.virtualWrite(V5, Gas);

  if ((Gas > 0)  && (Gas  <= 50)) {
    Blynk.virtualWrite(V6, "IAQ GOOD");
  }
  if ((Gas > 51)  && (Gas  <= 100)) {
    Blynk.virtualWrite(V6, "IAQ Average");
  }
  if ((Gas > 101)  && (Gas  <= 150)) {
    Blynk.virtualWrite(V6, "IAQ Little Bad");
  }
  if ((Gas > 151)  && (Gas  <= 200)) {
    Blynk.virtualWrite(V6, "IAQ Bad");
  }
  if ((Gas > 201)  && (Gas  <= 300)) {
    Blynk.virtualWrite(V6, "IAQ Worse");
  }
  if ((Gas > 301)  && (Gas  <= 500)) {
    Blynk.virtualWrite(V6, "IAQ Very Bad");
  }

  double DewPoint = DewPointFast(Temperature, Humidity);
  Blynk.virtualWrite(V7, DewPoint);
}

void loop()
{
  Blynk.run();
  timer.run();
}
// DewPoint Calculation
double DewPointFast(double celsius, double Humidity)
{
  double a = 17.271;
  double b = 237.7;
  double temp = (a * celsius) / (b + celsius) + log(Humidity * 0.01);
  double Td = (b * temp) / (a - temp);
  return Td;
}

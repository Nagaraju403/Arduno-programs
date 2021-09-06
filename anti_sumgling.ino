#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "";
char ssid[] = "";
char pass[] = "";

int fire_sensor = 0;
int tilt_sensor = 0;
int vibration_sensor = 0;

#define vibration_sensor D2
#define tilt_sensor D1
#define fire_sensor D0

BlynkTimer timer;
void setup() {
  Serial.begin(9600);
  pinMode(fire_sensor, INPUT);
  pinMode(tilt_sensor, INPUT);
  pinMode(vibration_sensor, INPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, notifiaction);
}
BLYNK_WRITE(V0) {
  fire_sensor = param.asInt();
  tilt_sensor = param.asInt();
  vibration_sensor = param.asInt();
}

void notifiaction() {
  int sensor1 = digitalRead(fire_sensor);
  int sensor2 = digitalRead(tilt_sensor);
  int sensor3 = digitalRead(vibration_sensor);
if (sensor1 == 1) 
    {
      Blynk.notify("WARNING! A fire was detected");
    }

  else if (sensor2 == 1) 
  {
  Blynk.notify("WARNING! A fire was detected");
  }
    else if (sensor3 == 1) 
  {
  Blynk.notify("WARNING! A fire was detected");
  }
}

void loop() {
  Blynk.virtualWrite(V5,fire_sensor);
  Blynk.virtualWrite(V5,tilt_sensor);
  Blynk.virtualWrite(V5,vibration_sensor);
  Blynk.run();
  timer.run();
}

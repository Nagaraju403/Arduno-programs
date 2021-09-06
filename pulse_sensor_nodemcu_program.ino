#include <SoftwareSerial.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp8266.h>
#define WIFI_SSID "Rasheduzzaman"
#define WIFI_PASS "rasheduzzaman"
SoftwareSerial NodeMCU(D5, D6);

int bPin = D8;
int rPin = D3;
int gPin = D4;
int val;
const int numReadings = 10;
int readings[numReadings]; 
int readIndex = 0; 
int total = 0; 
int average = 0; 
int inputPin = A0;
char auth[] = "rOzLiWPvrC3F_jRGxD_0d1_VdGwhNNhq";
void setup() {
 Serial.begin(9600);
 NodeMCU.begin(4800);
 pinMode(rPin, OUTPUT);
 pinMode(gPin, OUTPUT);
 pinMode(bPin, OUTPUT);
 pinMode(inputPin, INPUT);
 for (int thisReading = 0; thisReading < numReadings; thisReading++) {
 readings[thisReading] = 0;
 }
 Blynk.begin(auth, WIFI_SSID, WIFI_PASS);
}
void loop() {
 total = total - readings[readIndex];
 readings[readIndex] = analogRead(inputPin);
 total = total + readings[readIndex];
 readIndex = readIndex + 1;
 if (readIndex >= numReadings) {
 readIndex = 0;
 }
 average = total / numReadings;
 int hr = average / 8;
//  bpm->save(hr);
 Blynk.virtualWrite(V0, hr);
 if (hr > 125) {
 Blynk.tweet("Patient's pulse rate is so high.");
 Blynk.email("Subject", "Patient's pulse rate is so high.");
 Blynk.notify("Patient's pulse rate is so high.");
 digitalWrite(gPin, LOW);
 digitalWrite(rPin, HIGH);
 digitalWrite(bPin, HIGH);
 }
 else {
 digitalWrite(bPin, LOW);
 digitalWrite(rPin, LOW);
 digitalWrite(gPin, HIGH);
 }
 while (NodeMCU.available() > 0) {
 val = NodeMCU.parseFloat();
 if (NodeMCU.read() == '\n') {
 Serial.println(val);
 temperature->save(val);
 Blynk.virtualWrite(V1, "Temperature(C)");
 Blynk.virtualWrite(V2, val);
 }
 }
 Blynk.run();
 delay(5000);
}

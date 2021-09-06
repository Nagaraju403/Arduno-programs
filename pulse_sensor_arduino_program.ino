#include <SoftwareSerial.h>
SoftwareSerial ArduinoUno(6, 5);
void setup() {
 Serial.begin(9600);
 ArduinoUno.begin(4800);
 pinMode(6, INPUT);
 pinMode(5, OUTPUT);
 }
void loop() {
 float temp = analogRead(A0);
 temp = (temp * 0.49);
 ArduinoUno.print(temp);
 ArduinoUno.println("\n");
 delay(5000);
}

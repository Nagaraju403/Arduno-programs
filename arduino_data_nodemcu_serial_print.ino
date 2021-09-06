#include<ESP8266WiFi.h>
String inString = "";
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  int inChar = Serial.read();
    if (isDigit(inChar)) {
      inString += (char)inChar;
    }
    if (inChar == '\n') {
      Serial.print("Value:");
      Serial.println(inString.toInt());
      inString = "";
    }
  }

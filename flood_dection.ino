#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>

#include<ESP8266WiFi.h>
#include <Ultrasonic.h>
#include <LiquidCrystal.h>
volatile int flow_frequency; // Measures flow sensor pulses
// Calculated litres/hour
char auth[ ] = "B2ced7qB1HSQF1Hdst7Dd_T4auVl5dVP";
char ssid[ ] = "BNR";
char pass[ ] = "nagaraju";
 float vol = 0.0,l_minute;
 Ultrasonic ultrasonic(12, 13);
int distance;
unsigned char flowsensor = 2; // Sensor Input
int water_level_sensor=A0;
unsigned long currentTime;
unsigned long cloopTime;

LiquidCrystal lcd(12, 11, 5, 4, 3, 9);
WidgetLCD lcd1(V1);
void flow () // Interrupt function
{
   flow_frequency++;
}
void setup()
{
   pinMode(flowsensor, INPUT);
   pinMode(A0,INPUT);
   digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
   Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);
   lcd.begin(16, 2);
   attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING); // Setup Interrupt
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Water Flow Meter");
   lcd.setCursor(0,1);
   lcd.print("Circuit Digest");
   currentTime = millis();
   cloopTime = currentTime;
    lcd.clear(); //Use it to clear the LCD Widget
  lcd1.print(0, 0, "Distance in cm");
}
void loop ()
{
  distance = ultrasonic.read();
  int val = analogRead(A0); // read input value
   currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {
    cloopTime = currentTime; // Updates cloopTime
    if(flow_frequency != 0){
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_minute = (flow_frequency / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Rate: ");
      lcd.print(l_minute);
      lcd.print(" L/M");
      l_minute = l_minute/60;
      lcd.setCursor(0,1);
      vol = vol +l_minute;
      lcd.print("Vol:");
      lcd.print(vol);
      lcd.print(" L");
      flow_frequency = 0; // Reset Counter
      Serial.print(l_minute, DEC); // Print litres/hour
      Serial.println(" L/Sec");
    }
    else {
      Serial.println(" flow rate = 0 ");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Rate: ");
      lcd.print( flow_frequency );
      lcd.print(" L/M");
      lcd.setCursor(0,1);
      lcd.print("Vol:");
      lcd.print(vol); 
      lcd.print(" L");
    }
   }

 
  Serial.print("Pin Value   ");
  Serial.println(val);
  lcd1.print(4, 1, val);
  delay(2000);
  
  Serial.print("Distance in CM: ");
  Serial.println(distance);
  lcd1.print(4, 1, distance);
  Blynk.run();

  delay(3500);

}

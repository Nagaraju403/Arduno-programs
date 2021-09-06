#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include<ESP8266WiFi.h>
#include "DHT.h"
#include<Servo.h>

char auth[ ] = "6IxJqBCIkluz77rhfF4nkWlRB7p1rPBC";
char ssid[ ] = "BNR";
char pass[ ] = "nagaraju";

#define rain_sensor D1
int soil_sensor=D2;
#define DHTPIN D5   
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);
Servo myservo;
WidgetLCD lcd(V1);
void setup()
{
  Serial.begin(9600);
  dht.begin();
  pinMode(rain_sensor,INPUT);
  pinMode(soil_sensor,INPUT);
  myservo.attach(D4);
  myservo.write(0);
    Blynk.begin(auth, ssid, pass);
    lcd.clear(); 
  lcd.print(2, 0, "My Project"); 
  delay(1000);
}

void loop()
{
  int rain_sensor_value=digitalRead(rain_sensor);
  int soil_sensor_value=digitalRead(soil_sensor);
  float t = dht.readTemperature();
  Serial.println(rain_sensor_value);
  Serial.println(soil_sensor_value);
  Serial.println(t);
  delay(1000);

   if(t>32 || rain_sensor_value== 0 ||  soil_sensor_value==0)
   {
    myservo.write(90);
lcd.print(4, 1, "shield close");
 Serial.println("Shiled close"); 
   }
else 
{
myservo.write(90);
lcd.print(4, 1, "shield open");
 Serial.println("Shiled open");   
}
 Blynk.run();
 delay(2000);
 }

 

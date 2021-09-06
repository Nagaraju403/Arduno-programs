#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "xhVno4vO0PvglJOr7gxfkQIW3d3mAXrU";
char ssid[] = "BNR";
char pass[] = "nagaraju";

int buzzer= D4;
int vs = D0;  
int sdata = 0; 
#define fire_sensor D1   // fire sensor 
int tild_sensor=A0;

String vdata = ""; 
void myTimerEvent()
{
  Blynk.virtualWrite(V1, millis() / 1000);
} 
void setup()
{
  Serial.begin(9600);
  pinMode(vs ,INPUT);
  pinMode(fire_sensor,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(tild_sensor,INPUT); 
  Blynk.begin(auth, ssid, pass);
}
void loop()
{
  
  sensorvalue();
  fire();
  tild();
  Blynk.run();
}
 
void sensorvalue()
{
  long measurement =vibration();
  Serial.println(measurement);
  Blynk.virtualWrite(V3, measurement);
  if( measurement > 1000 )
  {
    Blynk.notify("Vibration detected!!");
    digitalWrite(buzzer,1);
    delay(1000);
    digitalWrite(buzzer,0);
    delay(1000);
  }
vdata = vdata + "Vibration: " + measurement;  
  Blynk.virtualWrite(V2, vdata);
vdata = ""; 
}
 
long vibration(){
  long measurement=pulseIn (vs, HIGH);  
  return measurement;
}


void fire()
{
  int fire_value=digitalRead(D1);
  Serial.println(fire_value);
  Blynk.virtualWrite(V4,fire_value);
  if( fire_value == 0 )
  {
    Blynk.notify("fire detected!!");
        digitalWrite(buzzer,1);
    delay(1000);
    digitalWrite(buzzer,0);
    delay(1000);
  }
}

void tild()
{
  int tild_value=analogRead(A0);
  Serial.println(tild_value);
  Blynk.virtualWrite(V5,tild_value);
  if( tild_value >200 )
  {
    Blynk.notify("tild detected!!");
        digitalWrite(buzzer,1);
    delay(1000);
    digitalWrite(buzzer,0);
    delay(1000);
  }
}

#define BLYNK_PRINT Serial
#include<ESP8266WiFi.h>
#include<BlynkSimpleEsp8266.h>
int mq3=A0;
int led=D3;
int buzzer=D4;
char auth[] = "PyI6PAZahaStUY7KZfEqc3piHvyqlvpr";
char ssid[] = "BNR";
char pass[] = "nagaraju";
int n;
String i;

void setup()
{
  Serial.begin(9600);
    Blynk.begin(auth,ssid,pass);
  pinMode(A0,INPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
}

void sendSensor()
{
  Blynk.virtualWrite(V5,n);            
  Blynk.virtualWrite(V4,i.toInt());
}

void loop()
{
    n=analogRead(mq3);
    i=Serial.readString();
    Serial.println(n);
  sendSensor();

  if(n>880)
  {
    digitalWrite(led,1);
    digitalWrite(buzzer,1);
  }
   else
  {
    digitalWrite(led,0);
    digitalWrite(buzzer,0);
  }
  Blynk.run();
}

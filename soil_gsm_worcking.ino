#include<SoftwareSerial.h>
SoftwareSerial Serial1(6,7);
#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
int led=7;
int flag=0;
String str="";
int relay=A0;

#define motor 8
#define sensor 13
void setup()
{
  lcd.begin(16,2);
  Serial1.begin(9600);
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(sensor, INPUT);
  lcd.print("Water Irrigaton");
  lcd.setCursor(4,1);
  delay(100);
  lcd.clear();
  lcd.print("Smart");
  lcd.setCursor(0,1);
  lcd.print("Agriculture");
  delay(2000);
  lcd.clear();
  lcd.print("System Ready");
}

void loop()
{
    lcd.setCursor(0,0);
    lcd.print("Automatic Mode    ");
    if(digitalRead(sensor)==1 && flag==0)
    {
      delay(1000);
      if(digitalRead(sensor)==1)
      {
        digitalWrite(led, HIGH);
        sendSMS("Low Soil Moisture detected. Motor turned ON");
        lcd.begin(16,2);
        lcd.setCursor(0,1);
        lcd.print("Motor ON    ");
        //motor on
        digitalWrite(motor, HIGH);
        delay(2000);
        flag=1;
      }
    }
    else if(digitalRead(sensor)==0 && flag==1)
    {
      delay(1000);
      if(digitalRead(sensor)==0)
      {
        digitalWrite(led, LOW);
        sendSMS("Soil Moisture is Normal. Motor turned OFF");
        //motor off
        digitalWrite(motor, LOW);
        lcd.begin(16,2);
        lcd.print("Motor OFF");
        lcd.setCursor(0,1);
        lcd.print("Motor OFF");
        delay(2000);
        flag=0;
      }
    }
}
void sendSMS(String msg)
{
  lcd.clear();
  lcd.print("Sending SMS");
  Serial1.println("AT+CMGF=1");
  delay(500);
  Serial1.print("AT+CMGS=");
  Serial1.print('"');
  Serial1.print("+918328659339");    // number
  Serial1.print('"');
  Serial1.println();
  delay(500);
  Serial1.println(msg);
  delay(500);
  Serial1.write(26);
  delay(1000);
  lcd.clear();
  lcd.print("SMS Sent");
  delay(1000);
  lcd.begin(16,2);
}

void gsmInit()
{
  lcd.clear();
  lcd.print("Finding Module..");
  boolean at_flag=1;
  while(at_flag)
  {
    Serial1.println("AT");
    while(Serial1.available()>0)
    {
      if(Serial1.find("OK"))
      at_flag=0;
    }
    delay(1000);
  }
  Serial1.println("ATE0");
  lcd.clear();
  lcd.print("Finding Network..");
  boolean net_flag=1;
  while(net_flag)
  {
    Serial1.println("AT+CPIN?");
    while(Serial1.available()>0)
    {
      if(Serial1.find("READY"))
      net_flag=0;
      break;
    }
    delay(1000);
  }
   Serial1.println("AT+CNMI=2,2,0,0,0");
   delay(1000);
   Serial1.println("AT+CMGF=1");
   delay(1000);
   Serial1.println("AT+CSMP=17,167,0,0");
   lcd.clear();
   Serial1.flush();
}

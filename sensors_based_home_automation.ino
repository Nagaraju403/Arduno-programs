#include <LiquidCrystal.h>
#include<Servo.h>
LiquidCrystal lcd(0,1,2,3,4,5);
Servo myservo;
int ir1=8;
int ir2=9;
int ir3=7;
int firesensor=10;
int ldr=A0;
int led1=11;
int dcmotor=12;
int buzzer=13;

void setup()
{
  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
  pinMode(ir3,INPUT);
  pinMode(firesensor,INPUT);
  pinMode(ldr,INPUT);
  pinMode(led1,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(dcmotor,OUTPUT);
  Serial.begin(9600);
  myservo.attach(6);
  lcd.begin(16,2);
  lcd.setCursor(5,0);
  lcd.print("KVSW");
  lcd.setCursor(0,1);
  lcd.print("Home Automation");
  myservo.write(0);
  Serial.println("HOME AUTOMATION");
}

void loop()
{
 int a=digitalRead(ir1);
 int b=digitalRead(ir2);
 int c=digitalRead(ir3);
 int d=digitalRead(firesensor);
 int e=analogRead(ldr);
 //Serial.println(e);

  if(a==0)
  {
    myservo.write(90);
    Serial.println("motor on");
    delay(5000);
    myservo.write(0);
   Serial.println("motor off");
    //delay(1000);
    digitalWrite(dcmotor,0);
    digitalWrite(led1,0);
    digitalWrite(buzzer,0);
   
  }
  else if(b==0)
  {
    digitalWrite(dcmotor,1);
    Serial.println("DC MOTOR ON");
    digitalWrite(led1,0);
    digitalWrite(buzzer,0);
    myservo.write(0);
    //Serial.print("ALL OFF");
  }
  else if(c==0)
  {
    digitalWrite(led1,1);
    Serial.println("LED ON");
    digitalWrite(dcmotor,0);
    digitalWrite(buzzer,0);
    myservo.write(0);
   // Serial.print("ALL OFF");
  }
  else if(d==1)
  {
    digitalWrite(buzzer,1);
    Serial.println("BUZZER ON");
    digitalWrite(dcmotor,0);
    digitalWrite(led1,0);
    myservo.write(0);
   // Serial.print("ALL OFF");
  }
  else
  {
     digitalWrite(buzzer,0);
    digitalWrite(dcmotor,0);
    digitalWrite(led1,0);
    myservo.write(0);
    Serial.println("**********");
  }
}

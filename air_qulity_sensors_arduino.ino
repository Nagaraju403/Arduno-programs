#include<LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
int mq135=A1;
int mq7=A2;
int buzz=8;
int led1=9,led2=10,led3=11,led4=12,led5=13;
void setup() {
  lcd.begin(16,2);
  pinMode(mq135,INPUT);
   pinMode(mq7,INPUT);
   pinMode(buzz,OUTPUT);digitalWrite(buzz,0);
    pinMode(led1,OUTPUT);digitalWrite(led1,0);
     pinMode(led2,OUTPUT);digitalWrite(led2,0);
      pinMode(led3,OUTPUT);digitalWrite(led3,0);
       pinMode(led4,OUTPUT);digitalWrite(led4,0);
        pinMode(led5,OUTPUT);digitalWrite(led5,0);
        lcd.setCursor(2,0);
        lcd.print("AIR QUALITY");
  Serial.begin(9600);
  Serial.println("AIR QUQLITY");
        delay(3000);
}

void loop() {
  int mq135_val=analogRead(mq135);
  int mq7_val=analogRead(mq7);
  Serial.println(mq7_val);
  lcd.clear();
  if((0<mq135_val)&&(mq135_val<100)||(mq7_val>=220))
  {
    digitalWrite(led1,1);
    digitalWrite(led2,0);
    digitalWrite(led3,0);
    digitalWrite(led4,0);
    digitalWrite(led5,0);
    lcd.setCursor(0,0);
    lcd.print("AQ level is: ");
    lcd.print(mq135_val); 
        lcd.clear();  
    delay(2000);
    lcd.setCursor(0,0);
    lcd.print("AQ is GOOD");
    Serial.print("MQ-135 level is: ");
    Serial.println(mq135_val);
    Serial.println("GREEN LED IS ON");
    delay(1000);

    lcd.setCursor(0,1);
    lcd.print("AQ level is: ");
    lcd.print(mq7_val);
  delay(2000);
  lcd.setCursor(0,1);
  lcd.print("CO IS DETECTED  ");
     Serial.print("MQ-7 level is: ");
  Serial.println(mq7_val);
  Serial.println("CO IS DETECTED");
  delay(1000);
  }
else if((101<mq135_val)&&(mq135_val<200)||(mq7_val>=220))
  {
    digitalWrite(led1,0);
    digitalWrite(led2,1);
    digitalWrite(led3,0);
    digitalWrite(led4,0);
    digitalWrite(led5,0);
    lcd.setCursor(0,0);
    lcd.print("AQ level is: ");
    lcd.print(mq135_val); 
    lcd.clear();   
    delay(2000);
    lcd.setCursor(0,0);
    lcd.print("AQ is MODERATE");
  Serial.print("MQ-135 level is: ");
    Serial.println(mq135_val);
  Serial.println("YELLOW LED IS ON");
    delay(1000);

    lcd.setCursor(0,1);
    lcd.print("AQ level is: ");
    lcd.print(mq7_val);
  delay(2000);
  lcd.setCursor(0,1);
  lcd.print("CO IS DETECTED   ");
     Serial.print("MQ-7 level is: ");
  Serial.println(mq7_val);
  Serial.println("CO IS DETECTED");
  delay(1000);
  }
  else if((201<mq135_val)&&(mq135_val<300)||(mq7_val>=220))
  {
    digitalWrite(led1,0);
    digitalWrite(led2,0);
    digitalWrite(led3,1);
    digitalWrite(led4,0);
    digitalWrite(led5,0);
    digitalWrite(8,1);
    delay(2000);
        digitalWrite(8,0);
    delay(2000);
     lcd.setCursor(0,0);
    lcd.print("AQ level is: ");
    lcd.print(mq135_val); 
    lcd.clear();   
    delay(2000);
    lcd.setCursor(0,0);
    lcd.print("AQ is UNHEALTHY");
    Serial.print("MQ-135 level is: ");
    Serial.println(mq135_val);
    Serial.println("ORANGE LED IS ON");
    delay(1000);

    lcd.setCursor(0,1);
    lcd.print("AQ level is: ");
    lcd.print(mq7_val);
  delay(2000);
  lcd.setCursor(0,1);
  lcd.print("CO IS DETECTED   ");
     Serial.print("MQ-7 level is: ");
  Serial.println(mq7_val);
  Serial.println("CO IS DETECTED");
  delay(1000);
  }
  else if((301<mq135_val)&&(mq135_val<400)||(mq7_val>=220))
  {
    digitalWrite(led1,0);
    digitalWrite(led2,0);
    digitalWrite(led3,0);
    digitalWrite(led4,1);
    digitalWrite(led5,0);
        digitalWrite(8,1);
    delay(2000);
        digitalWrite(8,0);
    delay(2000);
     lcd.setCursor(0,0);
    lcd.print("AQ level is: ");
    lcd.print(mq135_val); 
    lcd.clear();   
    delay(2000);
    lcd.setCursor(0,0);
    lcd.print("AQ is VERTUNHEALTHY");
    Serial.print("MQ-135 level is: ");
    Serial.println(mq135_val);
    Serial.println("BLUE LED IS ON");
    delay(1000);

   lcd.setCursor(0,1);
    lcd.print("AQ level is: ");
    lcd.print(mq7_val);
  delay(2000);
  lcd.setCursor(0,1);
  lcd.print("CO IS DETECTED   ");
     Serial.print("MQ-7 level is: ");
  Serial.println(mq7_val);
  Serial.println("CO IS DETECTED");
  delay(1000);
  }
  else if((401<mq135_val)&&(mq135_val<500)||(mq7_val>=220))
  {
    digitalWrite(led1,0);
    digitalWrite(led2,0);
    digitalWrite(led3,0);
    digitalWrite(led4,0);
    digitalWrite(led5,1);
        digitalWrite(8,1);
    delay(2000);
        digitalWrite(8,0);
    delay(2000);
    lcd.setCursor(0,0);
    lcd.print("AQ level is: ");
    lcd.print(mq135_val); 
    lcd.clear();   
    delay(2000);
    lcd.setCursor(0,0);
    lcd.print("AQ is HAZARDOUS");
    Serial.print("MQ-135 level is: ");
    Serial.println(mq135_val);
    Serial.println("RED LED IS ON");
    delay(1000);

    lcd.setCursor(0,1);
    lcd.print("AQ level is: ");
    lcd.print(mq7_val);
  delay(2000);
  lcd.setCursor(0,1);
  lcd.print("CO IS DETECTED    ");
     Serial.print("MQ-7 level is: ");
  Serial.println(mq7_val);
  Serial.println("CO IS DETECTED");
  delay(1000);
  }

   //else if(mq7_val>=220){
      //lcd.clear();
  //lcd.setCursor(0,1);
  //lcd.print("CO IS DETECTED");
    // Serial.print("MQ-7 level is: ");
  //Serial.println(mq7_val);
  //Serial.println("CO IS DETECTED");
  //digitalWrite(8,1);
  //delay(2000);
 //}
  else
  {
      lcd.setCursor(0,1);
  lcd.print("CO NOT DETECTED");
   Serial.print("MQ-7 level is: ");
  Serial.println(mq7_val);
  Serial.println("CO NOT DETECTED");
    //digitalWrite(8,0);
  delay(2000);
  //delay(1000);
  }
}

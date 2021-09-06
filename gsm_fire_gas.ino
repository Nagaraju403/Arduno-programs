#include<SoftwareSerial.h>
#include<LiquidCrystal.h>
SoftwareSerial gsm(8,7);
LiquidCrystal lcd(2,3,A1,A3,A4,A5);
int redled1=5;
int greenled1=4;
int redled2=11;
int greenled2=10;
int buzzer=13;
int gas_sensor1=A2;
int flame_sensor=12;



void setup() {
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  
  pinMode(A2,INPUT);
  pinMode(12,INPUT);
  pinMode(6,OUTPUT);
  lcd.begin(16,2);
  Serial.begin(9600);
  gsm.begin(9600);
  lcd.clear();

}

void loop() {
  lcd.clear();
  int redled1=0;
  int greenled1=0;
  int redled2=0;
  int greenled2=0;
  int a=analogRead(A2);
  Serial.print("Gas values are:");
  Serial.println(a);
  if(a>250){
   gsm.println("ATD7793906471rn");
    digitalWrite(5,HIGH); 
    digitalWrite(4,LOW);
    tone(13,700);
    delay(2000);
    noTone(13);
    Serial.println("Harmfull gases are detected");
    delay(1000);
    
  gsm.print("AT+CMGF=1\r"); 
  delay(1000);
  gsm.println("AT+CMGS=\"+917793906471\"");delay(1000);   Serial.println("message sent to the required number"); delay(1000);
 
  gsm.println("Harmful gases are detected"); 
  delay(1000);
  gsm.println((char)26); 
  delay(1000);
  gsm.println();
  lcd.print("GAS LEAKAGE");
   
     
}
else{
   //lcd.setCursor(0,1);
   Serial.println("No gas leakage");
  lcd.print("No gas leakage");
 
  digitalWrite(5,LOW);
    digitalWrite(4,HIGH);
  noTone(13);
}
  
  
delay(1000); 
  lcd.clear();
int b=digitalRead(12);
  Serial.print("Fire values are:");
  Serial.println(b);
  if(b==0){
  gsm.println("ATD7793906471rn");
    digitalWrite(11,HIGH);  // red
    tone(13,700);
    delay(2000);
    noTone(13);
    lcd.setCursor(0,0);
    digitalWrite(10,LOW); //green
    gsm.println("AT+CMGF=1"); //Sets the GSM module in text mode
    delay(1000); //Delay of 1 Second
   gsm.print("AT+CMGF=1\r"); 
  delay(1000);
  gsm.println("AT+CMGS=\"+917793906471\""); Serial.println("message sent to the required number");
  delay(1000);
   gsm.println("Fire Detected in your house"); 
  delay(1000);
  gsm.println((char)26); 
  delay(1000);
  gsm.println();
    
    lcd.println(" Fire Detected");
     
}
  
else{
  lcd.setCursor(0,1);
  Serial.println(" no fire detected");
  lcd.print(" no fire ");
  digitalWrite(10,1);
    digitalWrite(11,LOW);
  noTone(13);
}
delay(1000); 
}

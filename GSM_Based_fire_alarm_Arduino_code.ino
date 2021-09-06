// Techatronic.com  
 #include <Wire.h>           
 #include <LiquidCrystal.h>    
 LiquidCrystal lcd(2,3,4,5,6,7);   
  int val = 0 ;  
  int temp=0,i=0;  
  char str[15];  
 void setup()  
 {  
    Serial.begin(9600);  
    lcd.begin(16,2);      
   // lcd.backlight();  
    pinMode(4,INPUT);  // Flame Sensor  
    pinMode(5,OUTPUT); // Led  
    pinMode(6,OUTPUT); // Buzzer  
    lcd.setCursor(0,0);  
    lcd.print(" GSM Base Fire     ");  
    lcd.setCursor(0,1);  
    lcd.print("Security System ");  
    delay(2000);  
    lcd.clear();  
    Serial.println("AT+CNMI=2,2,0,0,0");  
    delay(500);  
    Serial.println("AT+CMGF=1");  
    delay(1000);  
 }  
 void loop()  
 {  
  if(temp==1)  
  {  
   check();  
   temp=0;  
   i=0;  
   delay(1000);  
  }  
   val = digitalRead(4); // pir sensor output pin connected  
   Serial.println(val); // see the value in serial mpnitor in Arduino IDE  
   delay(100);  
  if(val == 0 )  
   {  
   Serial.print("\r");  
   delay(1000);           
   Serial.print("AT+CMGF=1\r");  
   digitalWrite( 5,HIGH); // led   
   digitalWrite( 6,HIGH); // Buzzer  
   lcd.setCursor(0,0);  
   lcd.print(" Fire Detected     ");  
   lcd.setCursor(0,1);  
   lcd.print("   Be Safe    ");    
    delay(1000);  
   /*Replace XXXXXXXXXX to 10 digit mobile number & ZZ to 2 digit country code*/  
   Serial.print("AT+CMGS=\"+917007651787\"\r");    
   delay(1000);  
   //The text of the message to be sent.  
   Serial.print("Fire Alert");  
   delay(1000);  
   Serial.write(0x1A);  
 }  
 else  
  {  
     digitalWrite( 5,LOW); // led  
     digitalWrite( 6,LOW); // Buzzer  
     lcd.setCursor(0,0);  
     lcd.print("  FIRE NOT    ");  
     lcd.setCursor(0,1);  
     lcd.print("  DETECTED    ");  
  }  
  }  
  void serialEvent()   
  {  
  }  
  void check()  
  {  
   }  

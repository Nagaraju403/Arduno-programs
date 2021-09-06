//#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

#define Bz 11
#define rLed 10
#define gLed 9

int pirPin = 13;
int sensorValue = LOW;  //note sure what this is just yet //default sensor state 

long i;
int screenOffMsg =0;
String password="1234";
String temPassword;
boolean activated = false; //checks the state of the alarm 
boolean isActivated;
boolean activateAlarm = false;  // check where this is being used 
boolean alarmActivated = false; 
boolean enteredPassword; // checks the stated of the password 
boolean passChangeMode = false;
boolean passChanged =false;
//keypad
const byte Rows = 4;
const byte Cols = 4;
char keypressed; 
char KeyMap [Rows][Cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte  ROWPINS[Rows] = {1, 2, 3, 4};
byte  COLPINS[Cols] = {5, 6, 7, 8};

Keypad myKeypad = Keypad( makeKeymap(KeyMap),ROWPINS, COLPINS, Rows, Cols);
//LCD
const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd( rs, en, d4, d5, d6, d7);

void setup () {
  lcd.begin(16,2);
  pinMode(Bz, OUTPUT);
  pinMode(pirPin, INPUT);
}
void loop() {

  if (activateAlarm){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Alarm will be");
    lcd.setCursor(0,1);
    lcd.print("activated in");
    int countdown = 9;
    while (countdown != 0) {
      lcd.setCursor(13,1);
      lcd.print(countdown);
      countdown --;
      tone(Bz, 700, 100);
      delay(1000);      
      }
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Alarm Activated!");
      
      //sensorValue = digitalRead(pirPin);

      digitalWrite(rLed, HIGH);
      digitalWrite(gLed, LOW);
      activateAlarm = false;
      alarmActivated= true;
    }
//trigger
    if (alarmActivated == true){
      sensorValue = digitalRead(pirPin);
       
      if(sensorValue == HIGH) {
      lcd.clear();
      enterPassword();
         
        }
        else {
          noTone(Bz);
          digitalWrite(rLed, HIGH);
        }
      
       }

    if (!alarmActivated) {
      if(screenOffMsg == 0){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("A - Activate");
        lcd.setCursor(0,1);
        lcd.print("B - Change Pass");
        screenOffMsg = 1;
        digitalWrite(rLed, LOW);
        digitalWrite(gLed, HIGH);
      }
      keypressed = myKeypad.getKey();
      if (keypressed == 'A'){
        tone(Bz, 1000, 200);
        activateAlarm = true;
       
      }

      else if (keypressed =='B') {
        lcd.clear();
        int i =1;
        tone(Bz, 2000, 100);
        temPassword = "";
        lcd.setCursor(0,0);
        lcd.print("Current Password");
        lcd.setCursor(0,1);
        lcd.print(">");
        passChangeMode = true;
        passChanged = true;
        while(passChanged) {      
      keypressed = myKeypad.getKey();
      if (keypressed != NO_KEY){
        if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
            keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
            keypressed == '8' || keypressed == '9' ) {
         temPassword += keypressed;
         lcd.setCursor(i,1);
         lcd.print("*");
         i++;
         tone(Bz, 2000, 100);
        }
      }
      if (i > 5 || keypressed == '#') {
        temPassword = "";
        i=1;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Current Password");
        lcd.setCursor(0,1);
        lcd.print(">"); 
      }
      if ( keypressed == '*') {
        i=1;
        tone(Bz, 2000, 100);
        if (password == temPassword) {
          temPassword="";
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Set New Password");
          lcd.setCursor(0,1);
          lcd.print(">");
          while(passChangeMode) {
            keypressed = myKeypad.getKey();
            if (keypressed != NO_KEY){
              if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
                  keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
                  keypressed == '8' || keypressed == '9' ) {
                temPassword += keypressed;
                lcd.setCursor(i,1);
                lcd.print("*");
                i++;
                tone(Bz, 2000, 100);
              }
            }
            if (i > 5 || keypressed == '#') {
              temPassword = "";
              i=1;
              tone(Bz, 2000, 100);
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Set New Password");
              lcd.setCursor(0,1);
              lcd.print(">");
            }
            if ( keypressed == '*') {
              i=1;
              tone(Bz, 2000, 100);
              password = temPassword;
              passChangeMode = false;
              passChanged = false;
              screenOffMsg = 0;
            }            
          }
        }
      }
    }
   }
  }
 }
 void enterPassword() {
 // tone(Bz, 700, 100);
 // delay (1000);
 // tone(Bz, 700, 100);
  //delay(10000); 
 // tone(Bz, 700, 100);
  int k=5;
  temPassword = "";
  activated = true;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" *** ALARM *** ");
  lcd.setCursor(0,1);
  lcd.print("Pass>");
      while(activated) {
      keypressed = myKeypad.getKey();
      if (keypressed != NO_KEY){
        if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
            keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
            keypressed == '8' || keypressed == '9' ) {
          temPassword += keypressed;
          lcd.setCursor(k,1);
          lcd.print("*");
          k++;
        }
      }
      if (k > 9 || keypressed == '#') {
        temPassword = "";
        k=5;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" *** ALARM *** ");
        lcd.setCursor(0,1);
        lcd.print("Pass>");
      }
      if ( keypressed == '*') {
        if ( temPassword == password ) {
          activated = false;
          alarmActivated = false;
          noTone(Bz);
          screenOffMsg = 0; 
        }
        else if (temPassword != password) {
          lcd.setCursor(0,1);
          lcd.print("Wrong! Try Again");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(" *** ALARM *** ");
          lcd.setCursor(0,1);
          lcd.print("Pass>");
        }
      }
      //
      tone(Bz, 1000);    
    }
    noTone(Bz);
    digitalWrite(rLed, HIGH);
    
}

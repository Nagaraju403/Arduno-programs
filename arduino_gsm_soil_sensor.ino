#include <EEPROM.h>
#include <SoftwareSerial.h> //Create software serial object to communicate with SIM800L
#include<LiquidCrystal.h>
#include <AltSoftSerial.h>
//#include <TinyGPS++.h>
#include<DHT.h>

#define DHTPIN 13
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal lcd(12, 11, 5,4,3,2);
//LiquidCrystal lcd(12,13,a0,a1,a2,a3);
//const int rs = 12, en = 13, d4 = A0, d5 = A1, d6 = A2, d7 = A3;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

SoftwareSerial GSM(10, 11);  //SIM800L Tx & Rx is connected to Arduino #10 & #11
//AltSoftSerial neogps;
//TinyGPSPlus gps;

String phone_no1 = "+918639259224"; //change +91 with country code and 8639259224 with phone number to sms
String phone_no2 = "+916300277171";

String        RxString  = ""; // Will hold the incoming String  from the GSM shield
char          RxChar    = ' ';
int           Counter   = 0;
String        GSM_Nr    = "";
String        GSM_Msg   = "";

#define Relay1 2 // Load1 Pin Out
#define pirpin 6
int moisture_pin = A4;
int moisture_pin2 = 5;
int raindrop = 4;
int pirval = LOW;
int load1;

boolean stopping1 = true; //humidity stopping loop
boolean stopping2 = true; //temperature stoping loop
boolean stopping3 = true; //soil moisture stopping loop
boolean stopping4 = true; //rain fall stopping loop
boolean stopping5 = true; //motor off stopping loop due to rain fall
//boolean stopping6=true;  // stopping loop due to dryrun
//boolean stopping7=true;  //motor off stopping loop due to dryrun
boolean stopping8 = true; //irrigation complete stopping loop
boolean stopping9 = true; //PIR stopping loop

void setup() { // put your setup code here, to run once
  pinMode(Relay1, OUTPUT); digitalWrite(Relay1, 1);
  pinMode(DHTPIN, INPUT);
  pinMode(raindrop, INPUT);
  pinMode(moisture_pin2, INPUT);
  pinMode(pirpin, INPUT);
  lcd.begin(16, 2);

  Serial.begin(9600);//Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  GSM.begin(9600);   //Begin serial communication with Arduino and SIM800L
  dht.begin();
  //neogps.begin(9600);

  Serial.println(F("Initializing...."));
  initModule("AT", "OK", 1000);              //Scan for GSM Module
  initModule("AT+CPIN?", "READY", 1000);     //this command is used to check whether SIM card is inserted in GSM Module or not
  initModule("AT+CMGF=1", "OK", 1000);       //Set SMS mode to ASCII
  initModule("AT+CNMI=2,2,0,0,0", "OK", 1000); //Set device to read SMS if available and print to serial
  Serial.println(F("Initialized Successfully"));
  sendSMS(phone_no1, "Your System got power supply");
 
  load1 = EEPROM.read(1);

  relays();

  delay(100);
}

void loop() {

  int moisture_value;
  int moisture;

  int moisture_value2;
  int moisture2;

  int rainval;

  byte h, t;

  h = dht.readHumidity(); delay(250); //Serial.println(h); delay(1000);
  t = dht.readTemperature(); //delay(1000);

  moisture_value = analogRead(moisture_pin); moisture = map(moisture_value, 550, 10, 0, 100);
  //Serial.println(soil_moisture); delay(1000);

  moisture_value2 = digitalRead(moisture_pin2);
  // moisture2=map(moisture_value2,550,10,0,100);
  //Serial.println(moisture2); delay(1000);

  //poweronval=analogRead(poweronpin);
  // power1=map(poweronval,550,10,0,100);
  // Serial.println(power1); delay(1000);

  rainval = digitalRead(raindrop);
  //Serial.println(rainval); delay(1000);
  pirval = digitalRead(pirpin); Serial.print("PIR:  "); Serial.println(pirval); delay(1000);

  //dryrunval=digitalRead(dryrun);


  // scan for data from software serial port
  //-----------------------------------------------
  RxString = "";
  Counter = 0;
  while (GSM.available()) {
    delay(1);  // short delay to give time for new data to be placed in buffer
    // get new character
    RxChar = char(GSM.read());
    //add first 200 character to string
    if (Counter < 200) {  RxString.concat(RxChar); Counter = Counter + 1;
    }
  }

  //Serial.println(power_on);
  // Is there a new SMS?
  //-----------------------------------------------
  if (Received(F("CMT:")) ) GetSMS();

  if (GSM_Nr == phone_no1 || GSM_Nr == phone_no2) {

    if (GSM_Msg == "Motor on") {load1 = 0; sendSMS(GSM_Nr, "You switched on your motor and your motor is RUNNING");
    }
    if (GSM_Msg == "Motor off") {load1 = 1; sendSMS(GSM_Nr, "You switched OFF your motor and your motor is STOPED");
    }

    if (GSM_Msg == "check temp") {sendSMS(GSM_Nr, "Temperature:" + String(t) + "*C");
    }
    if (GSM_Msg == "check hum") {sendSMS(GSM_Nr, "Humidity:" + String(h));
    }

    if (GSM_Msg == "Motor status") {
      String loadst = "";

      if (load1 == 0) {
        loadst = "motor RUNNING\r\n";
      }
      else {
        loadst = "motor NOT RUNNING\r\n";
      }
      sendSMS(GSM_Nr, loadst);
    }

    if (GSM_Msg == "Location") {sendSmsGPS();
    }

    eeprom_write();
    relays();

  }

  mahi();


  //checking for humidity in air and sending sms to farmer if humidity is high
  if (h > 70) {
    if (stopping1 == true) {sendSMS(phone_no1, "Humidity is high its goin to rain");
    }
    stopping1 = false;
  }
  else {
    stopping1 = true;
  }

  //checking for temperature is high and sending sms to farmer if temperature is high
  if (t > 38) {
    if (stopping2 == true) {sendSMS(phone_no1, "Temperature is high do you want to turn on your Motor");
    }
    stopping2 = false;
  }
  else {
    stopping2 = true;
  }

  //soil sensor loop
  if (moisture < 0) {
    if (stopping3 == true) {sendSMS(phone_no1, "your soil is dry, do you want to turn on your motor?"); lcd.clear(); lcd.setCursor(0, 0); lcd.print(F("Your Soil is dry")); delay(5000); delay(2000);
    }
    stopping3 = false;
  }
  else {
    stopping3 = true;
  }

  //rain fall checking
  if (rainval == 0) {
    if (stopping4 == true) {sendSMS(phone_no1, "It's Raining on your field, Your motor is turning off");
    }
    stopping4 = false;
  }
  else {
    stopping4 = true;
  }

  if ((rainval == 0) && (load1 == 0)) {
    if (stopping5 == true) {load1 = 1;
    }
    stopping5 = false;
  }
  else {
    stopping5 = true;
  }

  //dry run checking
  //if(dryrunval==1){
  //if(stopping6==true) {
  //sendSMS(phone_no1,"your motor went to into dry run, hence turning off your motor");
  //}
  //stopping6= false;
  //}
  //else{
  //   stopping6= true; }

  //if((dryrunval==1)&& (load1==0)){
  //if(stopping7==true) {
  //load1=1;
  //relays();
  //delay(2000);}
  //stopping7= false;
  //}
  //else{
  //   stopping7= true; }

  //soil sensor loop2
  if (moisture_value2 == 0) {
    if (stopping8 == true) {
      sendSMS(phone_no1, "your field got completely irrigated, Do you want to turn it off?");
    }
    stopping8 = false;
  }
  else {
    stopping8 = true;
  }

 
  //person checking
 if (pirval == HIGH) {
    if (stopping9 == true) {
     sendSMS(phone_no1, "Person Detected");
      delay(2000);
    }
    stopping9 = false;
  }
  else {
    stopping9 = true;
  }

  GSM_Nr = "";
  GSM_Msg = "";
}//END OF VOID LOOP

void eeprom_write() {
  EEPROM.write(1, load1);
}

void relays() {
  digitalWrite(Relay1, load1);
}

void mahi() {
  if (load1 == 0) {lcd.clear(); lcd.setCursor(1, 0); lcd.print(F("Your Motor is")); lcd.setCursor(5, 1); lcd.print(F("RUNNING"));
  }
  if (load1 == 1) {lcd.clear(); lcd.setCursor(1, 0); lcd.print(F("Your Motor is")); lcd.setCursor(0, 1); lcd.print(F("STOPPED RUNNING"));
  }
}

// Send SMS
void sendSMS(String number, String msg) {
  GSM.print("AT+CMGS=\""); GSM.print(number); GSM.println("\"\r\n"); //AT+CMGS=”Mobile Number” <ENTER> - Assigning recipient’s mobile number
  delay(500);
  GSM.println(msg); // Message contents
  delay(500);
  GSM.write(byte(26)); //Ctrl+Z  send message command (26 in decimal).
  delay(5000);
}

// Get SMS Content
void GetSMS() {
  //Get SMS number
  //================================================
  GSM_Nr  = RxString;
  //get number
  int t1 = GSM_Nr.indexOf('"');
  GSM_Nr.remove(0, t1 + 1);
  t1 = GSM_Nr.indexOf('"');
  GSM_Nr.remove(t1);

  // Get SMS message
  //================================================
  GSM_Msg = RxString;
  t1 = GSM_Msg.indexOf('"');
  GSM_Msg.remove(0, t1 + 1);
  t1 = GSM_Msg.indexOf('"');
  GSM_Msg.remove(0, t1 + 1);
  t1 = GSM_Msg.indexOf('"');
  GSM_Msg.remove(0, t1 + 1);
  t1 = GSM_Msg.indexOf('"');
  GSM_Msg.remove(0, t1 + 1);
  t1 = GSM_Msg.indexOf('"');
  GSM_Msg.remove(0, t1 + 1);
  t1 = GSM_Msg.indexOf('"');
  GSM_Msg.remove(0, t1 + 1);
  GSM_Msg.remove(0, 1);
  GSM_Msg.trim();

  Serial.print(F("Number:")); Serial.println(GSM_Nr);
  Serial.print(F("SMS:")); Serial.println(GSM_Msg);
}

// Search for specific characters inside RxString
boolean Received(String S) {
  if (RxString.indexOf(S) >= 0) return true; else return false;
}

// Init GSM Module
void initModule(String cmd, char *res, int t) {
  while (1) {
    Serial.println(cmd);
    GSM.println(cmd);
    delay(100);
    while (GSM.available() > 0) {
      if (GSM.find(res)) {
        Serial.println(res);
        delay(t);
        return;
      } else {
        Serial.println("Error");
      }
    }
    delay(t);
  }
}

void sendSmsGPS() {
  // Can take up to 60 seconds
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 2000;)
  {
    while (neogps.available())
    {
      if (gps.encode(neogps.read()))
      {
        newData = true;
      }
    }
  }
  if (newData)      //If newData is true
  {
    float flat, flon;
    unsigned long age;
    Serial.print(F("Latitude= ")); Serial.print(gps.location.lat(), 6); Serial.print(F(" Longitude= ")); Serial.println(gps.location.lng(), 6); newData = false; delay(300);
    //sendSMS(GSM_Nr,"https://maps.google.com/maps?q=loc:" + String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6));
    GSM.print("AT+CMGS=\""); GSM.print(GSM_Nr); GSM.println("\"\r\n"); //AT+CMGS=”Mobile Number” <ENTER> - Assigning recipient’s mobile number
    delay(500);
    GSM.println("https://maps.google.com/maps?q=loc:" + String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6)); // Message contents
    delay(1000);
    GSM.write(byte(26)); //Ctrl+Z  send message command (26 in decimal).
    delay(1000);
  }
}

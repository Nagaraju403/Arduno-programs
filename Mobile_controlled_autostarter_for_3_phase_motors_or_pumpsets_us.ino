// https://www.youtube.com/watch?v=3qB12Ck96tU

#include <SoftwareSerial.h>  //Library for Serial communication
SoftwareSerial mygsm(3, 4);   //Pin and Name declaration of serial communication with GSM module
char mes[100];
int p=1;
int q=1;
int onpin=7;
int offpin=6;

//Setting up the Arduino NANO microcontroller for Serial communication and pinmode. 
void setup()
{
Serial.begin(9600); //initiating the Serial port with 9600 bps baud rate
mygsm.begin(9600); //initiating the serial communication with GSM module with 9600 baud rate
pinMode(onpin,OUTPUT);
digitalWrite(onpin,HIGH);//by default tracking signal pin is LOW 
pinMode(offpin,OUTPUT);
digitalWrite(offpin,HIGH);//by default tracking signal pin is LOW
delay(20000);
mygsm.println("AT+CMGF=1");         // AT command for GSM module for set to TEXT mode
mygsm.println("AT+CNMI=1,2,0,0,0"); // AT command for GSM module for continuous SMS reading
delay(1000);
SendSMS();
}

void loop()
{
while(mygsm.available()) // Checking for SMS Reception at GSM module 
{
mes[p]=mygsm.read();
Serial.print(p);
Serial.print("\t");
Serial.print(mes[p]);
Serial.print("\n");
p=p+1;
q=2;
}
p=1;
if(q==2)
{
q=1;
if( mes[13]=='9' && mes[14]=='5'&& mes[15]=='1' && mes[16]=='3' ........Continuoue for your number ) // Checking for recipient phone number
{
if(mes[52]=='O' && mes[53]=='N')  //Checking for Received SMS content
{
digitalWrite(onpin,LOW);  //Enable the tracking signal
SendSMSON();
delay(10000);
digitalWrite(onpin,HIGH);
}

if(mes[52]=='O' && mes[53]=='F' && mes[54]=='F')  //Checking for Received SMS content
{
digitalWrite(offpin,LOW);  //Enable the tracking signal
SendSMSOFF();
delay(4000);
digitalWrite(offpin,HIGH);
}
}




if( mes[13]=='9' && mes[14]=='3'&& mes[15]=='8' && mes[16]=='0'  ........Continuoue for your number ) // Checking for recipient phone number
{
if(mes[52]=='O' && mes[53]=='N')  //Checking for Received SMS content
{
digitalWrite(onpin,LOW);  //Enable the tracking signal
delay(10000);
digitalWrite(onpin,HIGH);
}

if(mes[52]=='O' && mes[53]=='F' && mes[54]=='F')  //Checking for Received SMS content
{
digitalWrite(offpin,LOW);  //Enable the tracking signal
delay(4000);
digitalWrite(offpin,HIGH);
}
}
}
}

void SendSMS()
{
delay(1000);                   // Generate precise delay of 1ms 
mygsm.println("AT+CMGF=1");                    //To send SMS in Text Mode
delay(100);
mygsm.println("AT+CMGS=\"+91YourNumber\"\r");  // destination phone number 
delay(100);
mygsm.print("Home Borewell...\n Current Came......");           //the content of the message
delay(100);
mygsm.println((char)26);                       //the stopping character Ctrl+Z
delay(500);  
}
void SendSMSON()
{
delay(1000);                   // Generate precise delay of 1ms 
mygsm.println("AT+CMGF=1");                    //To send SMS in Text Mode
delay(100);
mygsm.println("AT+CMGS=\"+91YourNumber\"\r");  // destination phone number 
delay(100);
mygsm.print("Home Borewell...\n Turned ON......");           //the content of the message
delay(100);
mygsm.println((char)26);                       //the stopping character Ctrl+Z
delay(500);  
}
void SendSMSOFF()
{
delay(1000);                   // Generate precise delay of 1ms 
mygsm.println("AT+CMGF=1");                    //To send SMS in Text Mode
delay(100);
mygsm.println("AT+CMGS=\"+91YourNumber\"\r");  // destination phone number 
delay(100);
mygsm.print("Home Borewell...\n Turned OFF......");           //the content of the message
delay(100);
mygsm.println((char)26);                       //the stopping character Ctrl+Z
delay(500);  

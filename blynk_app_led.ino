#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[ ] = "B2ced7qB1HSQF1Hdst7Dd_T4auVl5dVP";
char ssid[ ] = "BNR";
char pass[ ] = "nagaraju";
WidgetLCD lcd(V2);
BlynkTimer timer;
void blinkLedWidget()  
{
  if (led1.getValue()) {
    led1.off();
    Serial.println("LED on V1: off");
  } else {
    led1.on();
    Serial.println("LED on V1: on");
  }
}

void setup()
{
  
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, blinkLedWidget);
  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(4, 0, " My Project ");
}
void loop()
{
  lcd.print(4, 1, "Protuction shield open");
  Blynk.run();
  timer.run();
}

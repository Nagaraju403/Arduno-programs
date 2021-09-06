#include <ESP8266WiFi.h>
const char *ssid =  "BNR";    
const char *pass =  "nagaraju";
WiFiClient client; 
void setup() 
{
       Serial.begin(9600);
       delay(10);              
       Serial.println("Connecting to ");
       Serial.println(ssid);  
       WiFi.begin(ssid, pass); 
       while (WiFi.status() != WL_CONNECTED) 
          {
            delay(500);
            Serial.print(".");
          }
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.print("NodeMCU IP Address : ");
      Serial.println(WiFi.localIP() ); 
}
void loop() 
{      
}

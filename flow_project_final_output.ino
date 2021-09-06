#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <Ultrasonic.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "xhVno4vO0PvglJOr7gxfkQIW3d3mAXrU";
char ssid[] = "BNR";
char pass[] = "nagaraju";
 
#define SENSOR  2
int Sensor = A0;   // water level sensor
Ultrasonic ultrasonic(12, 13);   // trig,echo
int distance;
 
long currentMillis = 0;
long previousMillis = 0;
int interval = 1000;

float calibrationFactor = 4.5;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned long flowMilliLitres;
unsigned int totalMilliLitres;
float flowLitres;
float totalLitres;
 
void IRAM_ATTR pulseCounter()
{
  pulseCount++;
}
 
WiFiClient client;
WidgetLCD lcd(V1); 
void setup()
{
  Serial.begin(115200); 
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SENSOR, INPUT_PULLUP);
  pinMode(Sensor, INPUT);
  Blynk.begin(auth, ssid, pass);
  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  previousMillis = 0;
 
  attachInterrupt(digitalPinToInterrupt(SENSOR), pulseCounter, FALLING);
      lcd.clear(); 
  lcd.print(0, 0, "My Project"); 
}
 
void flow()
{
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) 
  {    
    pulse1Sec = pulseCount;
    pulseCount = 0;
    flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
    previousMillis = millis(); 
    flowMilliLitres = (flowRate / 60) * 1000;
    flowLitres = (flowRate / 60);
    totalMilliLitres += flowMilliLitres;
    totalLitres += flowLitres;

    Serial.print("Flow rate: ");
    Serial.println(float(flowRate));  // Print the integer part of the variable
    Serial.print("L/min");
    Serial.print("\t");       // Print tab space
    
    //Blynk.virtualWrite(V1, float(flowRate));
    lcd.print(4, 1, float(flowRate));
  }
  }

  void ultra() {
  // Pass INC as a parameter to get the distance in inches
  int distance = ultrasonic.read();
  
  Serial.print("Distance in CM: ");
  Serial.println(distance);
  delay(1000);
  Blynk.virtualWrite(V2,distance);
}

void level_sensor()
{
int  ad_value = analogRead(Sensor);
  
  Serial.print("Output: ");
  Serial.println(ad_value); 
  delay(500);
  Blynk.virtualWrite(V3,ad_value);
}

void loop()
{
  flow();
  ultra();
  level_sensor();
  Blynk.run();
}

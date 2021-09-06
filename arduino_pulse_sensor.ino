#define USE_ARDUINO_INTERRUPTS true    
#include <PulseSensorPlayground.h>        
const int PulseWire = 0;   // a0              
int Threshold = 550;           
                                                             
PulseSensorPlayground pulseSensor;  
void setup() {   
  Serial.begin(9600);          
  pulseSensor.analogInput(PulseWire);          
  pulseSensor.setThreshold(Threshold);   
   if (pulseSensor.begin()) {   
  }
}
void loop() {
 int myBPM = pulseSensor.getBeatsPerMinute();                                                
if (pulseSensor.sawStartOfBeat()) {                                  
 Serial.println(myBPM);                   
}                   
}

  

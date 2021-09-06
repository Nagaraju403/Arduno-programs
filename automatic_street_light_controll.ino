#include <Servo.h>
Servo servo1;

int ir1=13,ir2=12,ir3=11,ir4=10,ir5=9,ir6=8;
int ir7=7;
int led1=6,led2=5,led3=4,led4=2,led5=1,led6=0;

int value_1 =0;
const int servo_1 =3;

void setup()
{
    pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
  pinMode(ir3,INPUT);
  pinMode(ir4,INPUT);
  pinMode(ir5,INPUT);
  pinMode(ir6,INPUT);
  pinMode(ir7,INPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(led5,OUTPUT);
  pinMode(led6,OUTPUT);

  servo1.attach(servo_1);
}

void loop()
{
 
  value_1 = digitalRead(ir7);
 

      // servo 1 code //
     
  {
    if (value_1==0)
      {
        servo1.write(0);
        delay(3000);
      }
     
  }
 
  if (value_1==1)
      {
        servo1.write(90);
        delay(60);
      }

 

      // Parking Slot 1 IR & Led
 if (digitalRead(ir1)==0)      
               {
                 digitalWrite(led1, HIGH);
               }

          else if (digitalRead(ir1)==1)    
               {
                 digitalWrite(led1, LOW);
               }


               
  // Parking Slot 2 IR & Led
 if (digitalRead(ir2)==0)  // if the IR sensor value is < 500 then the motor will start rotating    
               {
                 digitalWrite(led2, HIGH);
               }

          else if (digitalRead(ir2)==1)  // if the IR sensor value is < 500 then the motor will start rotating    
               {
                 digitalWrite(led2, LOW);
               }



  // Parking Slot 3 IR & Led
 if (digitalRead(ir3)==0)  // if the IR sensor value is < 500 then the motor will start rotating    
               {
                 digitalWrite(led3, HIGH);
               }

          else if (digitalRead(ir3)==1)  // if the IR sensor value is < 500 then the motor will start rotating    
               {
                 digitalWrite(led3, LOW);
               }


  // Parking Slot 4 IR & Led
 if (digitalRead(ir4)==0)  // if the IR sensor value is < 500 then the motor will start rotating    
               {
                 digitalWrite(led4, HIGH);
               }

          else if (digitalRead(ir4)==1)  // if the IR sensor value is < 500 then the motor will start rotating    
               {
                 digitalWrite(led4, LOW);

                 
               }
     // Parking Slot 5 IR & Led
 if (digitalRead(ir5)==0)  // if the IR sensor value is < 500 then the motor will start rotating    
               {
                 digitalWrite(led5, HIGH);
               }

          else if (digitalRead(ir5)==1)  // if the IR sensor value is < 500 then the motor will start rotating    
               {
                 digitalWrite(led5, LOW);
               }


  // Parking Slot 6 IR & Led
 if (digitalRead(ir6)==0)  // if the IR sensor value is < 500 then the motor will start rotating    
               {
                 digitalWrite(led6, HIGH);
               }

          else if (digitalRead(ir6)==1)  // if the IR sensor value is < 500 then the motor will start rotating    
               {
                 digitalWrite(led6, LOW);
               }            
}

#include<LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);
#define led 13
#define buzzer 11
char tag[] ="26009F44BF42"; // Replace with your Tag ID
char input[12];        
int count = 0;        
boolean match = 0;      // A variable to store the Tag match status
void setup()
{
  lcd.begin(16,2);
  Serial.begin(9600);   
  pinMode(led,OUTPUT);  
  lcd.print("Welcome 2 APSSDC");
}
void loop()
{    
  if(Serial.available())// check serial data ( RFID reader)
  {        
    count = 0; // Reset the counter to zero
    /* Keep reading Byte by Byte from the Buffer till the RFID Reader Buffer is empty 
       or till 12 Bytes (the ID size of our Tag) is read */
    while(Serial.available() && count < 12) 
    {
      input[count] = Serial.read(); // Read 1 Byte of data and store it in the input[] variable
      count++; // increment counter
      delay(5);
    }
    /* When the counter reaches 12 (the size of the ID) we stop and compare each value 
        of the input[] to the corresponding stored value */
    if(count == 12) // 
    {
      count =0; // reset counter varibale to 0
      match = 1;
      /* Iterate through each value and compare till either the 12 values are 
         all matching or till the first mistmatch occurs */
      while(count<12 && match !=0)  
      {
        if(input[count]==tag[count])
        match = 1; // everytime the values match, we set the match variable to 1
        else
        match= 0; 
                               /* if the ID values don't match, set match variable to 0 and 
                                  stop comparing by exiting the while loop */
        count++; // increment i
      }
    }
    if(match == 1) // If match variable is 1, then it means the tags match
    {
      lcd.setCursor(0,0);
      lcd.print("Name: B Nagaraju");
      lcd.setCursor(0,1);
      lcd.print("ID:AO0715276");
      Serial.println("Emp Name: Bommanaboina Nagaraju");
      Serial.println("Emp ID: AO0715276");
      digitalWrite(led,HIGH);
      delay (5000);       // Relay on for 5 sec
      digitalWrite (led,LOW);
    }
    else
    {
      lcd.print("Data Not Matech");
      Serial.println("Data not matech");
      digitalWrite(buzzer,HIGH);
      delay(500);
      digitalWrite(buzzer,LOW);
    }
    /* Fill the input variable array with a fixed value 'F' to overwrite 
    all values getting it empty for the next read cycle */
    for(count=0; count<12; count++) 
    {
      input[count]= 'F';
    }
    count = 0; // Reset counter variable
  }
}

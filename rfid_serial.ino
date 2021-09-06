String carddata[3]={"26009F44BF42","26009F2EDD4A","26009F33A52F"};
String user_name[3]={"Mahidhar B","Nagaraju B","Md Madevi"};
String user_number[3]={"401","402","403"};
String data=" ";
void setup() 
{
Serial.begin(9600);
}
void loop() {
if(Serial.available()>0)
{
  String str=Serial.readString();
  if(data!=str)
    {
      for(int a=0;a<3;a++)
        {
        if(carddata[a]==str)
          {
            Serial.print(user_name[a]);
            Serial.println();
            Serial.print(user_number[a]);
            Serial.println();
          }
        }
   }
  }
}

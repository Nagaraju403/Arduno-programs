void setup()
{
  Serial.begin(9600);
}
void loop()
{
  if(Serial.available())
  {
    Serial.print((char)Serial.read());
  }
}


// 26009F44BF42
// 26009F2EDD4A
// 26009F33A52F

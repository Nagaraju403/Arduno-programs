const int trigPin = 8;
const int echoPin = 7;
const int buzz = 5;
const int vib = 2;
// defines variables
long duration;
float distance;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(buzz, OUTPUT);
pinMode(vib, OUTPUT);
Serial.begin(9600); // Starts the serial communication
}
void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2.0;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
if (distance < 20)
{
Serial.print(distance);
Serial.println("Object Alert");
digitalWrite(vib, HIGH);
digitalWrite(buzz,HIGH);
delay(100);


digitalWrite(buzz,LOW);
digitalWrite(vib, LOW);
for (int i= (distance-40); i>0; i--)
delay(10);
}
}

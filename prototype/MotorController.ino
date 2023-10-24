char t;

void setup() {
pinMode(8,OUTPUT); //left motors forward
pinMode(9,OUTPUT); //left motors back
pinMode(10,OUTPUT); //right motor forward
pinMode(11,OUTPUT); //right motor back
Serial.begin(9600);
}
 void loop()
 {
if(Serial.available())
{
 t = Serial.read();
Serial.println(t);
}
 
if(t == 'F')
 {
digitalWrite(11,HIGH);
digitalWrite(9,HIGH);
 }

if(t == 'B')
 {
digitalWrite(10,LOW);
digitalWrite(8,LOW);
 }

if(t == 'L')
 {
digitalWrite(11,HIGH);

 }

if(t == 'R')
 {

digitalWrite(9,HIGH);
 }
if(t == 'S')
 {
digitalWrite(11,LOW);
digitalWrite(9,LOW);
digitalWrite(10,LOW);
digitalWrite(8,LOW);

 }

delay(2000);

 }

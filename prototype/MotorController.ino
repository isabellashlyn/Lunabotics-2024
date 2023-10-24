char t;
#include list

std::list<int> left_pins = {8, 9};
std::list<int> right_pins = {10, 11};

void setup() {
pinMode(left_pins.front(),OUTPUT); //left motors forward
pinMode(left_pins.back(),OUTPUT); //left motors back
pinMode(right_pins.front(),OUTPUT); //right motor forward
pinMode(right_pins.back(),OUTPUT); //right motor back
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
digitalWrite(right_pins.back(),HIGH);
digitalWrite(left_pins.back(),HIGH);
 }

if(t == 'B')
 {
digitalWrite(right_pins.front(),LOW);
digitalWrite(left_pins.front(,LOW);
 }

if(t == 'L')
 {
digitalWrite(right_pins.back(),HIGH);

 }

if(t == 'R')
 {

digitalWrite(left_pins.back(),HIGH);
 }
if(t == 'S')
 {
digitalWrite(right_pins.back(),LOW);
digitalWrite(left_pins.back(),LOW);
digitalWrite(right_pins.front(),LOW);
digitalWrite(left_pins.front(,LOW);

 }

delay(2000);

 }

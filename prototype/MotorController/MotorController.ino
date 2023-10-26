char t;

int left_pins[] = {8, 9};
int right_pins[] = {10, 11};

void setup() {
pinMode(left_pins[0],OUTPUT); //left motors forward
pinMode(left_pins[1],OUTPUT); //left motors back
pinMode(right_pins[0],OUTPUT); //right motor forward
pinMode(right_pins[1],OUTPUT); //right motor back
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
digitalWrite(right_pins[1],HIGH);
digitalWrite(left_pins[1],HIGH);
 }

if(t == 'B')
 {
digitalWrite(right_pins[0],LOW);
digitalWrite(left_pins[0],LOW);
 }

if(t == 'L')
 {
digitalWrite(right_pins[1],HIGH);

 }

if(t == 'R')
 {

digitalWrite(left_pins[1],HIGH);
 }
if(t == 'S')
 {
digitalWrite(right_pins[1],LOW);
digitalWrite(left_pins[1],LOW);
digitalWrite(right_pins[0],LOW);
digitalWrite(left_pins[0],LOW);

 }

delay(2000);

 }

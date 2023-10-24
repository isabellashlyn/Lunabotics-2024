const int KILL_SWITCH = 1;

bool ks;
void setup() {
  // put your setup code here, to run once:
  ks = false;
  pinMode(KILL_SWITCH, INPUT);
  Serial.begin(9600);
}

void loop() {
  while (!ks) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.write((digitalRead(KILL_SWITCH) == HIGH) ? "1" : "0");
    if(digitalRead(KILL_SWITCH) == HIGH){
      ks = true;
    }
  }
  digitalWrite(LED_BUILTIN, LOW);
}

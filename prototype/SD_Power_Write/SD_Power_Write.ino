#include <Arduino.h>
#include <SD.h>
#include <Adafruit_INA219.h>
#include <Wire.h>
#define SDFILE_PIN_CS	10
#define VCC_ACTIVE
#define FILE_BASE_NAME "PowerData"
File sdFile;
const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
char fileName[] = FILE_BASE_NAME "00.txt";
#define SerialMonitor sdFile
int i = 1;

Adafruit_INA219 ina219;

void setup(){
  Serial.setup(9600);
  while(!Serial){
    delay(1);
  }

  pinMode(SDFILE_PIN_CS, OUTPUT);
  // Check if the card is present and can be initialized
  if (!SD.begin()) {
    Serial.println(F("Card failed, or not present"));
    while (1);
  }
  Serial.println(F("card initialized."));
  while (SD.exists(fileName)) {
    Serial.print(fileName[BASE_NAME_SIZE]);
    Serial.println(*(fileName + BASE_NAME_SIZE + 1));
    if (*(fileName + BASE_NAME_SIZE + 1) != '9') {
      Serial.println("Add1");
      *(fileName + BASE_NAME_SIZE + 1) = (char)(*(fileName + BASE_NAME_SIZE + 1) + 1);
      Serial.println(fileName);
    } else if (fileName[BASE_NAME_SIZE] != '9') {
      fileName[BASE_NAME_SIZE + 1] = '0';
      fileName[BASE_NAME_SIZE]++;
    } else {
      Serial.println(F("Can't create file name"));
      return;
    }
    Serial.println((SD.exists(fileName)) ? "True" : "False");
  }

  Serial.print("opened: ");
  Serial.println(fileName);
  if(!ina219.begin()){
    Serial.println("Failed to find Power Sensor");
    while(true){delay(10);}
  }

}

void loop(){
  float power_mW = 0;
  sdFile = SD.open(fileName, FILE_WRITE);
  power_mW = ina219.getPower_mW();

  Serial.println(power_mW);
  sdFile.println(power_mW);

  sdFile.close();

  delay(1000);
}
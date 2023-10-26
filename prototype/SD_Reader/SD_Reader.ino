#include "Arduino.h"
#include "SD.h"
#define SDFILE_PIN_CS	10
#define FILE_BASE_NAME "Data"
File sdFile;
const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
char fileName[] = FILE_BASE_NAME "00.txt";
#define SerialMonitor sdFile
int i = 1;
// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup()
{
  // Setup Serial which is useful for debugging
  // Use the Serial Monitor to view printed messages
  Serial.begin(9600);
  Serial.println("start");
  Serial.println(fileName);
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

}
// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop()
{
  sdFile = SD.open(fileName, FILE_WRITE);
  if (i == 1) {
    sdFile.println("ENTER SENSOR DATA HERE");
  }
  if (sdFile) {
    delay(1000);
    sdFile.close();
    
  }else  {

    if (i == 2)
    { // if the file didn't open, print an error
      Serial.println("sd card removed");
      i = i + 1;
    }
  }
}

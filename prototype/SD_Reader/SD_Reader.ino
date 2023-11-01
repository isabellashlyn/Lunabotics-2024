#include "Arduino.h" // Include the Arduino library
#include "SD.h"      // Include the SD card library

#define SDFILE_PIN_CS   10 // Define chip select pin for the SD card reader
#define FILE_BASE_NAME "Data" // Define the basic file name

File sdFile; // File object for writing to the SD card

const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1; // Get the size of FILE_BASE_NAME
char fileName[] = FILE_BASE_NAME "00.txt"; // Start with "Data00.txt"

int i = 1; // Variable to control the writing to SD card

void setup()
{
  Serial.begin(9600); 
  Serial.println("start"); 
  Serial.println(fileName); // Send the initial file name to serial monitor

  pinMode(SDFILE_PIN_CS, OUTPUT); // Define the SD CS pin as output

  // Check if SD card is properly placed and able to initialize
  if (!SD.begin()) {
    Serial.println(F("Card failed, or not present"));
    while (1); //if SD card fails to initialize, stuck the program here
  }
  Serial.println(F("card initialized.")); //if SD card initializes properly, send message to serial monitor

  // Check if the file exists in the SD card
  while (SD.exists(fileName)) {

    // if there's a file with the same name, increase the file number ("00.txt", "01.txt", etc)
    if (*(fileName + BASE_NAME_SIZE + 1) != '9') {
      *(fileName + BASE_NAME_SIZE + 1) = (char)(*(fileName + BASE_NAME_SIZE + 1) + 1);
    } else if (fileName[BASE_NAME_SIZE] != '9') {
      fileName[BASE_NAME_SIZE + 1] = '0';
      fileName[BASE_NAME_SIZE]++;
    } else {
      Serial.println(F("Can't create file name"));
      return; // If it gets to "99.txt", print an error message and exit the program
    }
  }

  Serial.print("opened: ");
  Serial.println(fileName); // Print the name of the file that just opened
}

void loop()
{
  sdFile = SD.open(fileName, FILE_WRITE); // Open the file to write in the SD card

  if (i == 1) {
    sdFile.println("ENTER SENSOR DATA HERE"); // print an instruction only once
    i++;
  }

  if (sdFile) { // If the file is ready to write
    delay(1000); // pause for 1 second
    sdFile.close(); // Close the file to save the data safely

  }
  else { // If the file does not exist or the SD card is removed

    if (i == 2){ // Print the error message only once
      Serial.println("sd card removed"); // Inform via the serial monitor
      i++;
    }
  }
}

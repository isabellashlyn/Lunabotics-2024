#include <Wire.h> // Include the Wire library for I2C communication
#include <Adafruit_INA219.h> // Include the Adafruit library to control INA219 sensor

Adafruit_INA219 ina219; // Create a new object ina219. This will be used to interact with the INA219 sensor

float totalPower = 0; // Declare a variable to store the total power consumption

void setup(void) // Function to set up the initial state
{
  Serial.begin(115200); // Start serial communication for debugging and output

  // This loop will pause Arduino Zero, Leonardo, etc until serial console opens
  while (!Serial) {
    delay(1);
  }

  Serial.println("Hello!"); // Send "Hello!" to the serial monitor

  // Initialize the INA219
  if (! ina219.begin()) {
    // If the INA219 sensor didn't initialize, print an error
    Serial.println("Failed to find INA219 chip");

    // Stop the code execution indefinitely until the chip is found
    while (1) {
      delay(10);
    }
  }

  Serial.println("Measuring voltage and current with INA219 ..."); // Print a message to the monitor informing we are starting to measure
}

void loop(void) // Function that loops forever and where the main code goes
{
  float shuntvoltage = 0; // Declare a variable to store the shunt voltage
  float busvoltage = 0; // Declare a variable to store the bus voltage
  float current_mA = 0; // Declare a variable to store the current in mA
  float loadvoltage = 0; // Declare a variable to store the load voltage
  float power_mW = 0; // Declare a variable to store the power in mW

  // Call functions to obtain measures from the INA219 sensor
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000); // Calculate the load voltage
  power_mW = current_mA * loadvoltage; // Calculate the power

  totalPower += power_mW; // Update total power

  // Print the values to the Serial Monitor
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage); 
  Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); 
  Serial.println(" mV");
  Serial.print("Load Voltage:  "); Serial.print(loadvoltage); 
  Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); 
  Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW); 
  Serial.println(" mW");
  Serial.print("Total Power:   "); Serial.print(totalPower); 
  Serial.println(" mW");
  Serial.println("");  

  delay(1000);  // Pause for a second before the next measurement
}

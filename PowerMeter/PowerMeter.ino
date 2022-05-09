#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219_B;
Adafruit_INA219 ina219_A(0x41);
Adafruit_INA219 ina219_C(0x44);
Adafruit_INA219 ina219_D(0x45);

void setup(void) 
{
  Serial.begin(115200);
  while (!Serial) 
  {
      // will pause Zero, Leonardo, etc until serial console opens
      delay(1);
  }

// Set up the serial port to talk to the P{
  Serial1.begin(9600);
  while (!Serial1) {Serial.print ("Waiting for Pi port");}

  uint32_t currentFrequency;

  
  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).

  if (! ina219_A.begin()) 
  {
    Serial.println("Failed to find ina219_A chip");
//    while (1) { delay(10); }
  }
  if (! ina219_B.begin()) 
  {
    Serial.println("Failed to find ina219_B chip");
//    while (1) { delay(10); }
  }

  if (! ina219_C.begin()) 
  {
    Serial.println("Failed to find ina219_C chip");
 //   while (1) { delay(10); }
  }

  if (! ina219_D.begin()) 
  {
    Serial.println("Failed to find ina219_D chip");
 //   while (1) { delay(10); }
  }
  
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219_B.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  //ina219_B.setCalibration_16V_400mA();

  Serial.println("Measuring voltage and current with ina219 ...");
  delay(100);
} // setup

void loop(void) 
{
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;
  float cum_batt_current = 0.0;

  //Serial1.println ("testing");    
  Serial.println ("Printed to Serial1");
  
//--------------------------------------------------------------------------------------
// Read battery
  shuntvoltage = ina219_A.getShuntVoltage_mV();
  busvoltage = ina219_A.getBusVoltage_V();
  current_mA = ina219_A.getCurrent_mA();
  power_mW = ina219_A.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);

  // Accumulate the battery current
  cum_batt_current = cum_batt_current + current_mA;
  
  Serial.print("Bus Voltage Battery:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage Battery: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage Battery:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current Battery:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power Battery:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("");

// Output a CSV line to read by the Pi
// Change these to Serial1
  Serial1.print("B");Serial1.print(",");
  Serial1.print(busvoltage);Serial1.print(",");
  Serial1.print(shuntvoltage);Serial1.print(",");
  Serial1.print(loadvoltage);Serial1.print(",");
  Serial1.print(current_mA);Serial1.print(",");
  Serial1.print(power_mW);Serial1.print(",");
  //Serial1.println("");
//-------------------------------------------------------------------------------------------------
// Read solar
  shuntvoltage = ina219_B.getShuntVoltage_mV();
  busvoltage = ina219_B.getBusVoltage_V();
  current_mA = ina219_B.getCurrent_mA();
  power_mW = ina219_B.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  Serial.print("Bus Voltage Solar:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage Solar: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage Solar:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current Solar:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power Solar:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("");

// Output a CSV line to read by the Pi
// Change these to Serial1
  Serial1.print("S");Serial1.print(",");
  Serial1.print(busvoltage);Serial1.print(",");
  Serial1.print(shuntvoltage);Serial1.print(",");
  Serial1.print(loadvoltage);Serial1.print(",");
  Serial1.print(current_mA);Serial1.print(",");
  Serial1.print(power_mW);Serial1.print(",");
 // Serial1.println("");

//-------------------------------------------------------------------------------------------------
// Read Load
  shuntvoltage = ina219_C.getShuntVoltage_mV();
  busvoltage = ina219_C.getBusVoltage_V();
  current_mA = ina219_C.getCurrent_mA();
  power_mW = ina219_C.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  Serial.print("Bus Voltage Load:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage Load: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage Load:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current Load:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power Load:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("");

// Output a CSV line to read by the Pi
// Change these to Serial1
  Serial1.print("L");Serial1.print(",");
  Serial1.print(busvoltage);Serial1.print(",");
  Serial1.print(shuntvoltage);Serial1.print(",");
  Serial1.print(loadvoltage);Serial1.print(",");
  Serial1.print(current_mA);Serial1.print(",");
  Serial1.print(power_mW);Serial1.print(",");
  //Serial1.println("");

  //-------------------------------------------------------------------------------------------------
//// Read D
  shuntvoltage = ina219_D.getShuntVoltage_mV();
  busvoltage = ina219_D.getBusVoltage_V();
  current_mA = ina219_D.getCurrent_mA();
  power_mW = ina219_D.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
//  
  Serial.print("Bus Voltage PS:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage PS: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage PS:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current PS:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power PS:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("");

// Output a CSV line to read by the Pi
// Change these to Serial1
  Serial1.print("P");Serial1.print(",");
  Serial1.print(busvoltage);Serial1.print(",");
  Serial1.print(shuntvoltage);Serial1.print(",");
  Serial1.print(loadvoltage);Serial1.print(",");
  Serial1.print(current_mA);Serial1.print(",");
  Serial1.print(power_mW);Serial1.print(",");
  Serial1.println(cum_batt_current);
  Serial.println("----------------------------------------------------------");
  
  delay(1000);
}

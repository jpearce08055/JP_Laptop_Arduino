//Read INA260 power measurement devices on Skunkworks solar power project.

#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_INA260.h>

Adafruit_INA260 ina260_A = Adafruit_INA260();
Adafruit_INA260 ina260_B = Adafruit_INA260();
Adafruit_INA260 ina260_C = Adafruit_INA260();
Adafruit_INA260 ina260_D = Adafruit_INA260();

//Initialize cumulative battery current
  float cum_batt_current = 0.0;

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

  
  // Initialize the INA260.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).

  if (! ina260_A.begin(0x40)) 
  {
    Serial.println("Failed to find ina260_A chip");
    delay(2000);
  }
  if (! ina260_B.begin(0x41)) 
  {
    Serial.println("Failed to find ina260_B chip");
    delay(2000);
  }

  if (! ina260_C.begin(0x44)) 
  {
    Serial.println("Failed to find ina260_C chip");
    delay(2000);
  }

  if (! ina260_D.begin(0x45)) 
  {
    Serial.println("Failed to find ina260_D chip");
    delay(2000);
  }
  
  Serial.println("Measuring voltage and current with ina260 ...");
  delay(100);
  

  
} // setup

void loop(void) 
{
  // NOTE - shunt voltage isn't measured by the INA260 but it's kept in the code to
  // maintain a consistent output record format
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;

  //Serial1.println ("testing");    
  Serial.println ("Printed to Serial1");

 // Have to read in B,S,L,P order to keep the output record fields in the right order

 //--------------------------------------------------------------------------------------
// Read B = battery
  //shuntvoltage = ina260_A.getShuntVoltage_mV();
  busvoltage = ina260_B.readBusVoltage()/1000;
  current_mA = ina260_B.readCurrent();
  power_mW = ina260_B.readPower();
  loadvoltage = busvoltage + (shuntvoltage / 1000);

  // Accumulate the battery current
  cum_batt_current = cum_batt_current + current_mA;
  
  Serial.print("Bus Voltage Battery:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage Battery: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage Battery:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current Battery:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power Battery:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.print("Cum Battery Current    "); Serial.print(cum_batt_current); Serial.println(" mA");
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
// Read Solar
  //shuntvoltage = ina260_C.getShuntVoltage_mV();
  busvoltage = ina260_C.readBusVoltage()/1000;
  current_mA = ina260_C.readCurrent();
  power_mW = ina260_C.readPower();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  shuntvoltage = 0.0; // set for consistency with 219 and to keep the output record consistent
  
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
  //shuntvoltage = ina260_D.getShuntVoltage_mV();
  busvoltage = ina260_D.readBusVoltage()/1000;
  current_mA = ina260_D.readCurrent();
  power_mW = ina260_D.readPower();
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
//// Read A = PS
  //shuntvoltage = ina260_A.getShuntVoltage_mV();
  busvoltage = ina260_A.readBusVoltage()/1000;
  current_mA = ina260_A.readCurrent();
  power_mW = ina260_A.readPower();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
//  
  Serial.print("Bus Voltage PS:   "); Serial.print(busvoltage); Serial.println(" V");
  //Serial.print("Shunt Voltage PS: "); Serial.print(shuntvoltage); Serial.println(" mV");
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

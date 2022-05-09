/***************************************************
 * Infrared CO2 Sensor0-5000ppm
 * ****************************************************
 * This example The sensors detect CO2
 *
 * @author lg.gang(lg.gang@qq.com)
 * @version  V1.0
 * @date  2016-7-6
 *
 * GNU Lesser General Public License.
 * See <http://www.gnu.org/licenses/> for details.
 * All above must be included in any redistribution
 * 
 * LCD Notes
 *    Connection:
   Plug the LCD Keypad to the UNO(or other controllers)
   Temperture sensor:
   S(blue) -- A1()
     Note: A0 has been occupied.
   VCC(red) -- VCC
   GND(black) -- GND
 * 
 * ****************************************************/
int sensorIn = A5;
int SerialPrint = 1;

#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);        // select the pins used on the LCD panel

//unsigned long tepTimer ;

void setup(){
  Serial.begin(9600);
  // Set the default voltage of the reference voltage
  analogReference(DEFAULT);

  lcd.begin(16, 2);                       // start the library
  lcd.setCursor(0, 0);
  lcd.print ("Setting up");
  delay (1000);
}

void loop(){
  //Read voltage
  int sensorValue = analogRead(sensorIn);

  // The analog signal is converted to a voltage
  float voltage = sensorValue*(5000/1024.0);
  if(voltage == 0)
  {
    Serial.println("Fault");
  }
  else if(voltage < 400)
  {
    Serial.println("preheating");
  }
  else
  {
    int voltage_diference=voltage-400;
    float concentration=voltage_diference*50.0/16.0;

    lcd.setCursor(0, 0);
    lcd.print("V:");
    lcd.print(voltage_diference);
    lcd.print (" mv   ");
    lcd.setCursor(0, 1);
    lcd.print("C:");
    lcd.print (concentration);
    lcd.print(" ppm");
    
    // Print Voltage
    if (SerialPrint == 1)
    {
      Serial.print("voltage:");
      Serial.print(voltage);
      Serial.println("mv");
      //Print CO2 concentration
      Serial.print(concentration);
      Serial.println("ppm");
    }   
  }
  delay(1000);
}

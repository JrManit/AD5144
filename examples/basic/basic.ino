#include <AD5144.h>

#define POT_ADDR 0x2E   // digital pot address

// creates communication object with address 0x2E
AD5144 digital_pot(POT_ADDR);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // initialises the communication via I2C
  // and enables RDAC adjustment through digital interface
  if(digital_pot.init() != 0);
    Serial.println("Cannot send data to the IC.");
}

void loop() {
  // put your main code here, to run repeatedly:

  // read the current RDAC1 value
  int ret = digital_pot.read_data(AD5144_ADDR_RDAC1, AD5144_RDAC);
  Serial.print("Read RDAC1 Value: ");
  Serial.println(ret, DEC);

  // set new value to RDAC1 (0~255)
  uint16_t data = 0x123;
  ret = digital_pot.write_data(AD5144_CTRL_RDAC_WRITE, AD5144_ADDR_RDAC1, data);
  if(ret != 0)  // check if data is sent successfully
    Serial.println("Error!");
    
  // read the new RDAC value
  ret = digital_pot.read_data(AD5144_ADDR_RDAC1, AD5144_RDAC);
  Serial.print("New RDAC1 Value: ");
  Serial.println(ret, DEC);   

  // read the current EEPROM1 value
  ret = digital_pot.read_data(AD5144_ADDR_RDAC1, AD5144_EEPROM);
  Serial.print("Read EEPROM1 Value: ");
  Serial.println(ret, DEC);
   
  // copy RDAC1 to EEPROM1
  ret = digital_pot.copy_data(AD5144_ADDR_RDAC1, AD5144_RDAC2EEPROM);
  if(ret != 0)    // check if data is sent successfully
    Serial.println("Error!");
  
  // read the new EEPROM1 value
  ret = digital_pot.read_data(AD5144_ADDR_RDAC1, AD5144_EEPROM);
  Serial.print("Read EEPROM1 Value: ");
  Serial.println(ret, DEC);
}

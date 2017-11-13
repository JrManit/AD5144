#include "AD5144.h"
#include <Arduino.h>
#include <Wire.h>

// Constructor
AD5144::AD5144(int addr){
  _addr = addr;  
}

int AD5144::init(void){
  Wire.begin();

  // Enable wiper adjustment.
  write_data(AD5144_CTRL_WRITE_CTRTL_REG, 0x00, AD5144_RDAC_WRITE_ENABLE|
                                                AD5144_EEPROM_PROGRAM_ENABLE|
                                                AD5144_POTENTIOMETER_MODE|
                                                AD5144_BURST_MODE_DISABLE);
  return copy_data(AD5144_ADDR_ALL, AD5144_EEPROM2RDAC);
}

int AD5144::write_data(uint16_t ctrl, uint16_t channel, uint16_t data){
  Wire.beginTransmission(_addr);
  Wire.write((ctrl<<4)|channel);
  Wire.write(data);
  return Wire.endTransmission();
}


int AD5144::read_data(uint16_t channel, uint16_t data){
  Wire.beginTransmission(_addr);
  Wire.write((AD5144_CTRL_READ<<4)|channel);
  Wire.write(data);
  if(Wire.endTransmission() != 0)
    Serial.println("Failed");
  
  Wire.requestFrom(_addr, 1);
  if(Wire.available()) 
    return (int)Wire.read();
  else
    return -1;
}

int AD5144::copy_data(uint16_t channel, uint16_t data){
  Wire.beginTransmission(_addr);
  Wire.write((AD5144_CTRL_COPY_VALUE<<4)|channel );
  Wire.write(data);
  return Wire.endTransmission();
}

int AD5144::reset(void){
  Wire.beginTransmission(_addr);
  Wire.write(AD5144_CTRL_RESET<<4 );
  Wire.write(0x00);
  return Wire.endTransmission();
}


int AD5144::shutdown(uint16_t channel, uint16_t mode){
  Wire.beginTransmission(_addr);
  Wire.write((AD5144_CTRL_SHUTDOWN<<4)|channel );
  Wire.write(mode);
  return Wire.endTransmission();
}






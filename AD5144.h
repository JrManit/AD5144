/*
 * AD5272.h - Wrapper for I2C communication with AD5144
 * 
 * Jirapong Manit
 *  November 2017
 */
#ifndef _AD5144_H
#define _AD5144_H

#include <stdint.h>


/*
 *  Control Bits[DB15:DB12] -- Address Bits[DB11:DB8] -- Data Bits[DB7:DB0]
 */

// Memory address
#define AD5144_ADDR_RDAC1 0x00
#define AD5144_ADDR_RDAC2 0x01
#define AD5144_ADDR_RDAC3 0x02
#define AD5144_ADDR_RDAC4 0x03  
#define AD5144_ADDR_ALL   0x08

// -- Read back contents -- //
#define AD5144_INPUT_REG  0x00  // Input register read out address  
#define AD5144_EEPROM     0x01  // EEPROM read out address
#define AD5144_CTRL_REG   0x02  // Control register read out address  
#define AD5144_RDAC       0x03  // RDAC read out address

// -- Control Bits -- //
#define AD5144_CTRL_NOP           0x00  // no operation
#define AD5144_CTRL_RDAC_WRITE    0x01	// write data to RDAC
#define AD5144_CTRL_REG_WRITE     0x02	// write data to input register
#define AD5144_CTRL_READ          0x03	// read back contents
#define AD5144_CTRL_LINEAR        0x04  // Linear RDAC in/decrement control
#define AD5144_CTRL_6DB_RDAC      0x05  // +/- 6dB RDAC
#define AD5144_CTRL_COPY_INPUT    0x06  // Copy input register to RDAC (software LRDAC) 
#define AD5144_CTRL_COPY_VALUE    0x07	// copy data RDAC <-> EEPROM
#define AD5144_CTRL_EEPROM_WRITE  0x08  // write data to EEPROM
#define AD5144_CTRL_TOP_SCALE     0x09  // Software reset
#define AD5144_CTRL_RESET         0x0B  // Software reset
#define AD5144_CTRL_SHUTDOWN      0x0C  // Software shutdown

#define AD5144_CTRL_WRITE_CTRTL_REG   0x0D  // Copy serial register data to control register


#define AD5144_EEPROM2RDAC	  0x00	// data bits for copying EEPROM to RDAC
#define AD5144_RDAC2EEPROM	  0x01	// data bits for copying RDAC to EEPROM

#define AD5144_NORMAL_MODE	  0x00	// Normal mode shutdown
#define AD5144_SHUTDOWN_MODE  0x01	// Shutdown mode

#define AD5144_RDAC_LINEAR_INC   0x01  // Linear RDAC increment
#define AD5144_RDAC_LINEAR_DEC   0x00  // Linear RDAC decrement   

//--  Control Register Bits --//
#define AD5144_RDAC_WRITE_ENABLE    0x01    // (default)
#define AD5144_RDAC_WRITE_DISABLE   0x00    

#define AD5144_EEPROM_PROGRAM_ENABLE    0x02  // (default)
#define AD5144_EEPROM_PROGRAM_DISABLE   0x00

#define AD5144_LINEAR_MODE          0x04      
#define AD5144_POTENTIOMETER_MODE   0x00      // (default)

#define AD5144_BURST_MODE_ENABLE    0x08      
#define AD5144_BURST_MODE_DISABLE   0x00      // (default)



class AD5144{
  public:
    AD5144(int addr);

    int init(void);
    int write_data(uint16_t ctrl, uint16_t channel, uint16_t data);
    int read_data(uint16_t channel, uint16_t data);
    
	  int copy_data(uint16_t channel, uint16_t data);

	  int reset(void);
	  int shutdown(uint16_t channel, uint16_t mode);

    inline int get_addr(void){return _addr;}
    inline void set_addr(int addr){_addr = addr;}
    
  private:
    int _addr;
};

#endif

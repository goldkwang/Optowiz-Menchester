
//
// [DCLee] 지금 구현되어 있는 프로그램에서 ACK와 NACK 처리가 정확한지 확인 필요, 2018.12.26.
//

//#include <SI_EFM8LB1_Register_Enums.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Declaration Variables
//#include "debug.h"
//#include "i2c_master_gpio.h"
#include <intrinsics.h>
#include <iods4835.h>

#include "includes.h"

#define xdata

void Delay_us(int us_interval)
{
	// Implement microseconds delay function.
	int xdata i;

    for (i=0; i< us_interval; i++);
	return;
}

void i2c_master_gpio_init(void)
{
#if 0 // Example program -->
//	P0IO |= 0xC0;  //Set SCL, SDA to output
//    SCL = 1;  // Set SCL, SDA High
//    SDA = 1;
#endif // <--

#if __HW_I2C_MASTER_ENABLE__ == 1  
//  I2CM_Init (I2CM_MASTER_1, I2CM_CLOCK_DIV_400KHZ, I2CM_MSDA_PIN_GP10, 0);      //Init I2C Master, SDA - GP10, SCL - GP11
  I2CM_Init (I2CM_MASTER_1, I2CM_CLOCK_DIV_100KHZ, I2CM_MSDA_PIN_GP10, 0);      //Init I2C Master, SDA - GP10, SCL - GP11
#else  
  
//    P0MDIN |= P0MDIN_B2__DIGITAL; P0MDOUT |= P0MDOUT_B2__PUSH_PULL;  //Set SCL, SDA to output
//    P0MDIN |= P0MDIN_B3__DIGITAL; P0MDOUT |= P0MDOUT_B3__PUSH_PULL; // Set SCL to output

    S_DATA_OUTPUT_MODE;
    S_CLOCK_OUTPUT_MODE;
    
    S_CLOCK = S_CLOCK_HIGH;  // Set SCL, SDA High
    S_DATA = S_DATA_HIGH;
#endif
}

void i2c_master_gpio_start(void)
{
#if 0 // Example program -->
    //start
    P0IO |= 0xC0;  //Set SCL, SDA to output
    SDA = 1;
    SCL = 1;  // Set SCL, SDA High
    Delay_us(7);

    SDA = 0;    // Clear SDA
    Delay_us(7);
    SCL = 0;    // Clear SCL
    Delay_us(7);
#endif // <--

#if __HW_I2C_MASTER_ENABLE__ == 1  
#else  
    //start
//    P0MDIN |= P0MDIN_B2__DIGITAL; P0MDOUT |= P0MDOUT_B2__PUSH_PULL;  //Set SCL, SDA to output
//    P0MDIN |= P0MDIN_B3__DIGITAL; P0MDOUT |= P0MDOUT_B3__PUSH_PULL; // Set SCL to output

    S_DATA_OUTPUT_MODE;
    S_CLOCK_OUTPUT_MODE;
    
    S_DATA = S_DATA_HIGH;
    S_CLOCK = S_CLOCK_HIGH;  // Set SCL, SDA High
    Delay_us(7);

    S_DATA = S_DATA_LOW;     // Clear SDA
    Delay_us(7);
    S_CLOCK = S_CLOCK_LOW;  // Clear SCL
    Delay_us(7);
#endif
}

void i2c_master_gpio_stop(void)
{
#if 0 // Example program -->
    P0IO |= 0x80;   // Set SDA to output
    SDA = 0;    // Clear SDA Low
    Delay_us(7);

    SCL = 1;    // Set SCL High
    Delay_us(7);
    SDA = 1; // Set SDA High

    P0IO &= (~0xC0);    // Set SDA to Input
#endif // <--

#if __HW_I2C_MASTER_ENABLE__ == 1  
#else  
#endif
//    P0MDIN |= P0MDIN_B2__DIGITAL; P0MDOUT |= P0MDOUT_B2__PUSH_PULL;   // Set SDA to output
    S_DATA_OUTPUT_MODE;
    S_DATA = S_DATA_LOW;    // Clear SDA Low
    Delay_us(7);

    S_CLOCK = S_CLOCK_HIGH;  // Set SCL High
    Delay_us(7);
    S_DATA = S_DATA_HIGH; // Set SDA High

//    P0MDIN |= P0MDIN_B2__DIGITAL; P0MDOUT &= (~P0MDOUT_B2__PUSH_PULL); S_DATA = S_DATA_HIGH;  // Set SDA to Input
    S_DATA_INPUT_MODE;
}

void write_i2c_master_gpio_byte(unsigned char byte)
{
#if 0 // Example program -->
    unsigned char i = 0;

    P0IO |= 0x80;       // Set SDA to output

    for (i = 0; i < 8 ; i++)
    {
        if((byte & 0x80)==0x80) SDA = 1;    // Set SDA High
        else                    SDA = 0;    // Clear SDA Low

        SCL = 1;        // Set SCL High, Clock data
        _nop_();
        byte = byte << 1; // Shift data in buffer right one
        SCL = 0;        // Clear SCL
        _nop_();
    }
    SDA = 0; //listen for ACK
    P0IO &= (~0x80);

    SCL = 1;
    _nop_();_nop_();
    SCL = 0;
    _nop_();_nop_(); //Clear SCL.
    P0IO |= 0x80;       // Set SDA to Output
#endif // <--

#if __HW_I2C_MASTER_ENABLE__ == 1  
#else  
    unsigned char xdata i = 0;

//    P0MDIN |= P0MDIN_B2__DIGITAL; P0MDOUT |= P0MDOUT_B2__PUSH_PULL;       // Set SDA to output
    S_DATA_OUTPUT_MODE;

    for (i = 0; i < 8 ; i++)
    {
        if((byte & 0x80)==0x80)
        	S_DATA = S_DATA_HIGH;    // Set SDA High
        else
        	S_DATA = S_DATA_LOW;    // Clear SDA Low

        S_CLOCK = S_CLOCK_HIGH;    // Set SCL High, Clock data
//        _nop_();
//        _nop_();
//        _nop_();
        asm("nop");
        asm("nop");
        asm("nop");
        
        byte = byte << 1; // Shift data in buffer right one
        S_CLOCK = S_CLOCK_LOW;        // Clear SCL
//        _nop_();
//        _nop_();
//        _nop_();
        asm("nop");
        asm("nop");
        asm("nop");
    }
    S_DATA = S_DATA_LOW; //listen for ACK
//    P0MDIN |= P0MDIN_B2__DIGITAL; P0MDOUT &= (~P0MDOUT_B2__PUSH_PULL); S_DATA = S_DATA_HIGH;  // Set SDA to Input
    S_DATA_INPUT_MODE;

    S_CLOCK = S_CLOCK_HIGH;
//    _nop_();_nop_();
//    _nop_();
        asm("nop");
        asm("nop");
        asm("nop");

    S_CLOCK = S_CLOCK_LOW;
//    _nop_();_nop_(); //Clear SCL.
//    _nop_();
        asm("nop");
        asm("nop");
        asm("nop");

//    P0MDIN |= P0MDIN_B2__DIGITAL; P0MDOUT |= P0MDOUT_B2__PUSH_PULL;       // Set SDA to Output
    S_DATA_OUTPUT_MODE;
#endif
}

unsigned char read_i2c_master_gpio_byte(unsigned char ch)
{
#if 0 // Example program -->
    unsigned char i, buff=0;

    P0IO &= (~0x80);    // Set SDA to input

    for(i=0; i<8; i++)
    {
        _nop_();_nop_();
        SCL = 1;
        _nop_();_nop_();// Set SCL High, Clock bit out
        buff <<= 1;

        // Read data on SDA pin
        if ((P0&0x80) == 0x80) {
            buff |= 0x01;
        }
        SCL = 0; // Clear SCL
        _nop_();_nop_();
    }
    if(ch == 0) //ACK
    {
        SDA = 1; //SDA HIGH.
    }
    else //NACK.
    {
        SDA = 0; //SDA LOW.
    }
    SCL = 1;
    _nop_();_nop_();
    SCL = 0; //SCL LOW.
    SDA = 1; //SDA HIGH.
    _nop_();_nop_();
    P0IO |= 0x80;   // Set SDA to Output

    return buff;
#endif // <--

#if __HW_I2C_MASTER_ENABLE__ == 1  
    return 0;
#else  
    unsigned char xdata i, buff;

    buff = 0;

//    P0MDIN |= P0MDIN_B2__DIGITAL; P0MDOUT &= (~P0MDOUT_B2__PUSH_PULL); S_DATA = S_DATA_HIGH;    // Set SDA to input
    S_DATA_INPUT_MODE;

    for(i=0; i<8; i++)
    {
//        _nop_();_nop_();
        asm("nop");
        asm("nop");
        S_CLOCK = S_CLOCK_HIGH;
//        _nop_();_nop_();// Set SCL High, Clock bit out
//        _nop_();_nop_();// Set SCL High, Clock bit out
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        buff <<= 1;

        // Read data on SDA pin
        // if ((P0&0x80) == 0x80)
        if (S_DATA_IN == S_DATA_HIGH)
        {
            buff |= 0x01;
        }
        S_CLOCK = S_CLOCK_LOW; // Clear SCL
//        _nop_();_nop_();
        asm("nop");
        asm("nop");
    }
    
    S_DATA_OUTPUT_MODE;

    if(ch == 1) //NACK
    {
    	S_DATA = S_DATA_HIGH; //SDA HIGH.
    }
    else //ACK.
    {
    	S_DATA = S_DATA_LOW; //SDA LOW.
    }
//    _nop_();_nop_();
        asm("nop");
        asm("nop");
    S_CLOCK = S_CLOCK_HIGH;
//    _nop_();_nop_();
//    _nop_();_nop_();
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
    S_CLOCK = S_CLOCK_LOW; //SCL LOW.
    S_DATA = S_DATA_HIGH; //SDA HIGH.
//    _nop_();_nop_();
        asm("nop");
        asm("nop");

//    P0MDIN |= P0MDIN_B2__DIGITAL; P0MDOUT |= P0MDOUT_B2__PUSH_PULL;   // Set SDA to Output
//    S_DATA_OUTPUT_MODE;

    return buff;
#endif
}

unsigned int read_master_gpio_word(unsigned char slave, unsigned char page_address, unsigned char index_address)
{
#if __HW_I2C_MASTER_ENABLE__ == 1  
  return 0;
#else  
    unsigned int xdata temp;
    unsigned char xdata ucHibyte = 0;
    unsigned char xdata ucLobyte = 0;
//    unsigned char xdata ucNack = 0;

    ucHibyte=0;
    ucLobyte=0;

    i2c_master_gpio_start();
    write_i2c_master_gpio_byte(slave);
    write_i2c_master_gpio_byte(page_address);
    write_i2c_master_gpio_byte(index_address);

    i2c_master_gpio_start();
    write_i2c_master_gpio_byte(slave+1);

    ucHibyte=read_i2c_master_gpio_byte(0);
    ucLobyte=read_i2c_master_gpio_byte(1);
    //ucHibyte=read_i2c_byte(1);

    i2c_master_gpio_stop();

    temp = (ucHibyte<<8) + ucLobyte;

    return temp;
#endif
}

void write_master_gpio_word(unsigned char slave, unsigned char page_address, unsigned char index_address, unsigned char value)
{
#if __HW_I2C_MASTER_ENABLE__ == 1  
#else  
    i2c_master_gpio_start();
    write_i2c_master_gpio_byte(slave);
    write_i2c_master_gpio_byte(page_address);
    write_i2c_master_gpio_byte(index_address);
    write_i2c_master_gpio_byte(value);
    i2c_master_gpio_stop();
#endif
}

uint8_t read_master_gpio_single_byte(unsigned char slave, unsigned char reg_address)
{
#if __HW_I2C_MASTER_ENABLE__ == 1  
//  unsigned char ret_val;
  unsigned char r_data[8];
  
//  if (slave == LD_DRIVER_I2C_ADDR)
//    return (unsigned char)0xDD;
  
  slave = slave >> 1;
  
//  ret_val = I2CM_ReadNBytes(I2CM_MASTER_1, slave, reg_address, &r_data[0], 1);
  I2CM_ReadNBytes(I2CM_MASTER_1, slave, reg_address, &r_data[0], 1);
  return r_data[0];  
#else  
//    unsigned char xdata temp;
//    unsigned char xdata ucHibyte = 0;
    unsigned char xdata ucLobyte = 0;
//    unsigned char xdata ucNack = 0;

//    ucHibyte=0;
//    ucLobyte=0;

    i2c_master_gpio_start();
    write_i2c_master_gpio_byte(slave);
    write_i2c_master_gpio_byte(reg_address);
    // write_i2c_master_gpio_byte(index_address);

    i2c_master_gpio_start();
    write_i2c_master_gpio_byte(slave+1);
    ucLobyte=read_i2c_master_gpio_byte(1);
    i2c_master_gpio_stop();

    return ucLobyte;
#endif

}

void read_master_gpio_multiple_bytes(unsigned char slave, unsigned char reg_address, unsigned char length, unsigned char * valuePtr)
{
#if __HW_I2C_MASTER_ENABLE__ == 1  
//  unsigned char ret_val;
//  unsigned char r_data[8];
  
//  if (slave == LD_DRIVER_I2C_ADDR)
//    return;
//  ret_val = I2CM_ReadNBytes(I2CM_MASTER_1, slave, reg_address, &r_data[0], length);
  slave = slave >> 1;
  I2CM_ReadNBytes(I2CM_MASTER_1, slave, reg_address, valuePtr, length);

  return;    
#else  
//    unsigned char xdata temp;
    unsigned char xdata idx;
//    unsigned char xdata ucHibyte = 0;
//    unsigned char xdata ucLobyte = 0;
//    unsigned char xdata ucNack = 0;

//    ucHibyte=0;
//    ucLobyte=0;

    i2c_master_gpio_start();
    write_i2c_master_gpio_byte(slave);
    write_i2c_master_gpio_byte(reg_address);
    // write_i2c_master_gpio_byte(index_address);

    i2c_master_gpio_start();
    write_i2c_master_gpio_byte(slave+1);

    for (idx=0; idx < length; idx++)
    {
    	if ((idx+1) == length)
    	{
    		// NACK
            valuePtr[idx]=read_i2c_master_gpio_byte(1);
    	}
    	else
    	{
    		// ACK
    		valuePtr[idx]=read_i2c_master_gpio_byte(0);
    	}
    }

//    ucLobyte=read_i2c_master_gpio_byte(1);
    //ucHibyte=read_i2c_byte(1);

    i2c_master_gpio_stop();

//    temp = (ucHibyte<<8) + ucLobyte;
//
//    return temp;
#endif
}

void write_master_gpio_single_byte(unsigned char slave, unsigned char reg_address, unsigned char value)
{
#if __HW_I2C_MASTER_ENABLE__ == 1  
//  unsigned char ret_val;
  unsigned char w_data[4];
  
//  if (slave == LD_DRIVER_I2C_ADDR)
//    return;
  w_data[0] = value;
  slave = slave >> 1;
  
//  ret_val = I2CM_WriteNBytes(I2CM_MASTER_1, slave, reg_address, &w_data[0], 1);
  I2CM_WriteNBytes(I2CM_MASTER_1, slave, reg_address, &w_data[0], 1);
  return;
#else  
    i2c_master_gpio_start();
    write_i2c_master_gpio_byte(slave);
    write_i2c_master_gpio_byte(reg_address);
    write_i2c_master_gpio_byte(value);
    i2c_master_gpio_stop();
#endif
}

void write_master_gpio_multiple_bytes(unsigned char slave, unsigned char reg_address, unsigned char length, unsigned char * valuePtr)
{
#if __HW_I2C_MASTER_ENABLE__ == 1  
//  unsigned char ret_val;
//  unsigned char w_data[8];
  
//  if (slave == LD_DRIVER_I2C_ADDR)
//    return;

  slave = slave >> 1;
  //  ret_val = I2CM_WriteNBytes(I2CM_MASTER_1, slave, reg_address, valuePtr, length);
  I2CM_WriteNBytes(I2CM_MASTER_1, slave, reg_address, valuePtr, length);
  return;
#else  

	uint8_t	idx;

    i2c_master_gpio_start();
    write_i2c_master_gpio_byte(slave);
    write_i2c_master_gpio_byte(reg_address);
    for (idx=0; idx < length; idx++)
    {
        write_i2c_master_gpio_byte(valuePtr[idx]);
    }
    i2c_master_gpio_stop();
#endif
}


void confirm_write_master_gpio_multiple_bytes(unsigned char slave, unsigned char reg_address, unsigned char length, unsigned char * valuePtr)
{
#if __HW_I2C_MASTER_ENABLE__ == 1  
  unsigned char idx;
  unsigned char r_data[8];
  
//  if (slave == LD_DRIVER_I2C_ADDR)
//    return;

  slave = slave >> 1;
  //  ret_val = I2CM_WriteNBytes(I2CM_MASTER_1, slave, reg_address, valuePtr, length);
  I2CM_WriteNBytes(I2CM_MASTER_1, slave, reg_address, valuePtr, length);
  
  for (idx=0; idx<10; idx++)
  {
    I2CM_ReadNBytes(I2CM_MASTER_1, slave, reg_address, &r_data[0], 1);
    
    if (r_data[0] == valuePtr[0])
    {
      break;
    }
    else
    {
      I2CM_WriteNBytes(I2CM_MASTER_1, slave, reg_address, valuePtr, length);
    }
    
  }
  return;
#else  

	uint8_t	idx;

    i2c_master_gpio_start();
    write_i2c_master_gpio_byte(slave);
    write_i2c_master_gpio_byte(reg_address);
    for (idx=0; idx < length; idx++)
    {
        write_i2c_master_gpio_byte(valuePtr[idx]);
    }
    i2c_master_gpio_stop();
#endif
}

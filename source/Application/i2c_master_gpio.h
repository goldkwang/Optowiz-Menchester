
#ifndef __I2C_MASTER_GPIO_H__
#define __I2C_MASTER_GPIO_H__

#ifdef __DECLARE_VARS__
#define _EXTERN_C_
#else
#define _EXTERN_C_ extern
#endif

//SI_SBIT (S_DATA, SFR_P0, 2);
#define S_DATA  (PO1_bit.PO10)
#define S_DATA_IN   (PI1_bit.PI10)

#define S_DATA_LOW		0
#define S_DATA_HIGH		1
#define S_DATA_ACK		0
#define S_DATA_NACK		1

//SI_SBIT (S_CLOCK, SFR_P0, 3);
#define S_CLOCK  (PO1_bit.PO11)

#define S_CLOCK_LOW		0
#define S_CLOCK_HIGH	1

//#define S_DATA_OUTPUT_MODE	(P0MDIN |= P0MDIN_B2__DIGITAL; P0MDOUT |= P0MDOUT_B2__PUSH_PULL;)
//#define S_DATA_INPUT_MODE	(P0MDIN |= P0MDIN_B2__DIGITAL; P0MDOUT &= (~P0MDOUT_B2__PUSH_PULL); S_DATA = S_DATA_HIGH;)
#define S_DATA_OUTPUT_MODE	{ IEN1_bit.IEN10 = 0; PD1_bit.PD10 = 1;}
#define S_DATA_INPUT_MODE	{ IEN1_bit.IEN10 = 1; PD1_bit.PD10 = 0; S_DATA = S_DATA_HIGH;}

#define S_CLOCK_OUTPUT_MODE	{IEN1_bit.IEN11 = 0; PD1_bit.PD11 = 1;} 

extern void i2c_master_gpio_init(void);
extern void i2c_master_gpio_start(void);
extern void i2c_master_gpio_stop(void);
extern void write_i2c_master_gpio_byte(unsigned char byte);
extern unsigned char read_i2c_master_gpio_byte(unsigned char ch);
extern unsigned int read_master_gpio_word(unsigned char slave, unsigned char page_address, unsigned char index_address);
extern void write_master_gpio_word(unsigned char slave, unsigned char page_address, unsigned char index_address, unsigned char value);
extern uint8_t read_master_gpio_single_byte(unsigned char slave, unsigned char reg_address);
extern void write_master_gpio_single_byte(unsigned char slave, unsigned char reg_address, unsigned char value);
extern void write_master_gpio_multiple_bytes(unsigned char slave, unsigned char reg_address, unsigned char length, unsigned char * valuePtr);
extern void read_master_gpio_multiple_bytes(unsigned char slave, unsigned char reg_address, unsigned char length, unsigned char * valuePtr);
extern void confirm_write_master_gpio_multiple_bytes(unsigned char slave, unsigned char reg_address, unsigned char length, unsigned char * valuePtr);

//_EXTERN_C_ uint8_t xdata tx_i2c_master_data[128];
//_EXTERN_C_ uint8_t xdata rx_i2c_master_data[128];
_EXTERN_C_ uint8_t xdata tx_i2c_master_data[16];
_EXTERN_C_ uint8_t xdata rx_i2c_master_data[16];

#endif

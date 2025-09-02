//#include <intrinsics.h>
//#include <iods4830a.h>
//#include <stdio.h>
//#include <string.h>
#include "includes.h"
//#include "drv_max5825.h"

#define MAX5825 0x20
#define REF_2_5V 0x21
#define REF_2_0V 0x22
#define REF_4_0V 0x23

/*
void Max5725_dac_set(unsigned char dac_no, unsigned char ch, unsigned int Data);
unsigned int Max5725_dac_get(unsigned char dac_no, unsigned char ch);
void Max5725_dac_init(unsigned char dac_no);
void Max5725_dac_Clear(unsigned char dac_no);
void Max5725_dac_CS_En(unsigned char dac_no);
void Max5725_dac_CS_DIS(unsigned char dac_no);
*/

void Delay(long time)
{
    //time = time * 10;
	while(time--);
	//WDCN_bit.RWT = 1; 
}

void Delay_m(int msec)
{
	Delay(msec * 1000);
}


/*******************************************************************************
 * Function: Max5725_dac_Clear
 *
 *  This function clears the coresponding max5725.
 *
 * Input:     unsiged char dac_no: max5725 select
 * Output:    No
 *
 ******************************************************************************/
void Max5825_dac_Clear(unsigned char dac_no)
{
	return;
	//Chip Clear Reset
//	MAX5825_CLR = HIGH;
//	MAX5825_CLR = LOW;
//	Delay(1);
//	MAX5825_CLR = HIGH;
	
}

/*******************************************************************************
 * Function: Max5825_dac_init
 *
 *  This function initializes max5825. And, CS port and Clear port Direction setup
 *
 * Input:     unsiged char dac_no: max5725 select
 *            
 * Output:    No
 *
 ******************************************************************************/
void Max5825_dac_init(void)
{

	
	unsigned char txdata[3];

	//make write to data
	txdata[0] = 0x21; //ref 2.5v , Always On
	txdata[1] = 0x00;
	txdata[2] = 0x00;

//	I2CWrite2Bytes(MAX5825,txdata[0],txdata[1],txdata[2]); //REF volteage set
        write_master_gpio_multiple_bytes(MAX5825, txdata[0], 2, &txdata[1]);
//void write_master_gpio_multiple_bytes(unsigned char slave, unsigned char reg_address, unsigned char length, unsigned char * valuePtr)

	Delay(4);
	
	//make write to data
	//txdata[0] = 0x30;//power up, Clear
	//txdata[1] = 0x96;
	//txdata[2] = 0x30;

	
	txdata[0] = 0x40;//power up, Clear
	txdata[1] = 0xff;
	txdata[2] = 0x00;
		
//	I2CWrite2Bytes(MAX5825,txdata[0],txdata[1],txdata[2]); //
        write_master_gpio_multiple_bytes(MAX5825, txdata[0], 2, &txdata[1]);

	Delay(4);
	

}	

/*******************************************************************************
 * Function: Max5825_dac_set
 *
 *  This function writes the setting value to the corresponding dac channel
 *
 * Input:     unsiged char dac_no: max5825 select
 *            unsiged char ch : max5825 setting target channel
 *            unsiged char int Data : setting dac value
 * Output:    No
 *
 ******************************************************************************/
void Max5825_dac_set(unsigned char dac_no, unsigned char ch, unsigned int data)
{
	unsigned char txdata[3];   

	//make write to data
	//txdata[0] = 0x80 | (ch & 0x0F); //CODEn
	//txdata[1] = (data >> 4) & 0x00FF;
	//txdata[2] = (data << 4) & 0x00F0;

	//Sending Write to Data
	//I2CWrite2Bytes(MAX5825,txdata[0],txdata[1],txdata[2]);

	//Delay(4);
	
	//make write to data
	//txdata[0] = 0x90 | (ch & 0x0F); //LODEn
	//txdata[1] = 0x00;
	//txdata[2] = 0x00;

	//Sending Write to Data
	//I2CWrite2Bytes(MAX5825,txdata[0],txdata[1],txdata[2]);

	//make write to data
	txdata[0] = 0xA0 | (ch & 0x0F); //LODE_ALL
	txdata[1] = (data >> 4) & 0x00FF;
	txdata[2] = (data << 4) & 0x00F0;

	//Sending Write to Data
//	I2CWrite2Bytes(MAX5825,txdata[0],txdata[1],txdata[2]);
        write_master_gpio_multiple_bytes(MAX5825, txdata[0], 2, &txdata[1]);

	Delay(4);
}

/*******************************************************************************
 * Function: Max5825_dac_get
 *
 *  This function read the setting value to the corresponding dac channel
 *
 * Input:     unsiged char dac_no: max5825 select
 *            unsiged char ch : max5825 setting target channel
 * Output:    Read DAC data
 *
 ******************************************************************************/
unsigned int Max5825_dac_get(unsigned char dac_no, unsigned char ch)
{
	unsigned char txdata[3];
	unsigned char rxdata1,rxdata2;
	unsigned int read_data;


	//make write to data
	txdata[0] = 0x90 | (ch & 0x0F); //LOADn

	//Seding and Read
//	I2CRead2Bytes(MAX5825,txdata[0],&rxdata1, &rxdata2);
        read_master_gpio_multiple_bytes(MAX5825, txdata[0], 2, &txdata[1]);
//void read_master_gpio_multiple_bytes(unsigned char slave, unsigned char reg_address, unsigned char length, unsigned char * valuePtr)

        rxdata1 = txdata[1];
        rxdata2 = txdata[2];
        
	read_data = rxdata1;
	read_data = (read_data << 4) & 0x0FF0;
	read_data = read_data + ((rxdata2 >> 4) & 0x0F);

#if 0
	//make write to data
	txdata[0] = 0xD0 | (ch & 0x0f);;//Data Req
	txdata[1] = 0x00;
	txdata[2] = 0x00;

	//Sending Write to Data
	I2CWrite2Bytes(MAX5825,txdata[0],txdata[1],txdata[2]);
	
	//make write to data
	txdata[0] = 0xE8; //SPI Read Data
	txdata[1] = 0x00;
	txdata[2] = 0x00;

	//Sending Write to Data
	rxdata[0] = SPIWriteRead8(txdata[0]);
	rxdata[1] = SPIWriteRead8(txdata[1]);
	rxdata[2] = SPIWriteRead8(txdata[2]);

	Delay(1);
	Max5725_dac_CS_DIS(dac_no);

	read_data = rxdata[1];
	read_data = (read_data << 4) & 0x0FF0;
	read_data = read_data + ((rxdata[2] >> 4) & 0x0F);

	Delay(1);

	return read_data;
#endif
 	
	return read_data;
}




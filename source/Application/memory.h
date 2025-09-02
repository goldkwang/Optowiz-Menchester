/*******************************************************************************
* Copyright (C) 2018 Maxim Integrated Products, Inc., All Rights Reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
* OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*
* Except as contained in this notice, the name of Maxim Integrated
* Products, Inc. shall not be used except as stated in the Maxim Integrated
* Products, Inc. Branding Policy.
*
* The mere transfer of this software does not imply any licenses
* of trade secrets, proprietary technology, copyrights, patents,
* trademarks, maskwork rights, or any other form of intellectual
* property whatsoever. Maxim Integrated Products, Inc. retains all
* ownership rights.
*******************************************************************************
*/

#ifndef __MEMORY_H_   
#define __MEMORY_H_

#include <iods4835.h>
#include <intrinsics.h>

#include "memory_map.h"
#include "includes.h"
//-----------------------------------------------------------------------------
// global variables prototypes
//-----------------------------------------------------------------------------

#ifdef __DECLARE_VARS__
#define _EXTERN_C_
#else
#define _EXTERN_C_ extern
#endif

//#ifndef __SFP28_ER__
//
//#define __QSFP28_ER4__    0
//#define __QSFP28_LR4__    0
//#define __QSFP28_CWDM4__  0
//#define __QSFP28_SR4__    0
//
//#define __SFP28_ER__  1
//#endif

//#define _M(x,y) (( (x) << 6) |( (y) << 1))
//
__no_init volatile __io unsigned char GP_REG1  @ _M(1,22);

/* NORMV Register (	 //description)*/
//__no_init volatile __io unsigned int NORMV1  @ _M(1,29);


#if __SFP28_ER__ == 1


//-----------------------------------------------------------------------------
// SRAM defines
//-----------------------------------------------------------------------------
/*******    Create memory for all A2 lower registers in the defined locaitons     ********/
/*** SFF-8636 ***/

#pragma location = A0_SRAM_OFFSET
__no_init unsigned char I2C_Slave_Buffer_A0_Local_Memory[256];
#pragma required = I2C_Slave_Buffer_A0_Local_Memory

#pragma location = A2_LOWER_SRAM_OFFSET
__no_init unsigned char I2C_Slave_Buffer_A2[128];
#pragma required = I2C_Slave_Buffer_A2

#pragma location = A2_UPPER_SRAM_OFFSET
__no_init unsigned char I2C_Slave_Buffer_A2_Pn_Up[128];
#pragma required = I2C_Slave_Buffer_A2_Pn_Up

//#pragma location = COMMON_MEM_SRAM 
//__no_init unsigned char COMMON_MEMORY[256];
//#pragma required = COMMON_MEMORY 

#pragma location = I2C_WRITE_LIST 
__no_init i2cWriteStruct write_i2c_list[128];  // 64 --> 128
#pragma required = write_i2c_list 

//I2C Receive buffer
#pragma location = I2C_RX_BUF_ADD
__no_init unsigned char I2C_Rx_Buffer[256];
#pragma required = I2C_Rx_Buffer

#pragma location = PAGE00H_UPPER
__no_init unsigned char I2C_Slave_Buffer_A2_P00H_Up[128];
#pragma required = I2C_Slave_Buffer_A2_P00H_Up

#pragma location = PAGE01H_UPPER
__no_init unsigned char I2C_Slave_Buffer_A2_P01H_Up[128];
#pragma required = I2C_Slave_Buffer_A2_P01H_Up

#pragma location = PAGE02H_UPPER
__no_init unsigned char I2C_Slave_Buffer_A2_P02H_Up[128];
#pragma required = I2C_Slave_Buffer_A2_P02H_Up

#pragma location = PAGE80H_UPPER
__no_init unsigned char I2C_Slave_Buffer_A2_P80H_Up[128];
#pragma required = I2C_Slave_Buffer_A2_P80H_Up

#pragma location = PAGE81H_UPPER
__no_init unsigned char I2C_Slave_Buffer_A2_P81H_Up[128];
#pragma required = I2C_Slave_Buffer_A2_P81H_Up

#pragma location = PAGE82H_UPPER
__no_init unsigned char I2C_Slave_Buffer_A2_P82H_Up[128];
#pragma required = I2C_Slave_Buffer_A2_P82H_Up

#if __SFP28_ER_SEMI_TUNABLE__==1

#pragma location = PAGE83H_UPPER
__no_init unsigned char I2C_Slave_Buffer_A2_P83H_Up[128];
#pragma required = I2C_Slave_Buffer_A2_P83H_Up

#pragma location = PAGE84H_UPPER
__no_init unsigned char I2C_Slave_Buffer_A2_P84H_Up[128];
#pragma required = I2C_Slave_Buffer_A2_P84H_Up

#endif

//#pragma location = I2C_WRITE_LIST
//__no_init i2cWriteStruct write_i2c_list[64];
//#pragma required = write_i2c_list

#pragma location = RX_COUNT_ADD
__no_init unsigned int Rx_Count;
#pragma required = Rx_Count

#pragma location = MEM_ADD_ADD
__no_init unsigned int Mem_Address;
#pragma required = Mem_Address

//-----------------------------------------------------------------------------
// default values defines
//-----------------------------------------------------------------------------

#if __SFP28_ER_SEMI_TUNABLE__ == 1

#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1

#pragma location = FLASH_A0_CONST_START

const unsigned char FlashData_A0_Const[] = // 3G ST-SFP+ Serial ID
                            { // DEFAULT VALUES
                              0x03,  // IDENTIFER(0x01),   SFP/SFP+/SFP28 and later
                              0x04,  // EXT. IDENTIFER, Addr 0x01, SFP ftn def'd by two-wire if ID only
                              0x07,  // CONNECTOR Types(0x02): LC (0x07)
                              0x00,  // (0x03) Transceiver Compliance Codes [Address A0h, Bytes 3-10 and 36], 10G-ER, LRM, LR, SR, SX, LX, CA, CP
                              0x00,  // (0x04) SONET Compliance codes, Addr 0x84, ESCON, OC-192, SONET, OC-48, 
                              0x00,  // (0x05) SAS/SATA compliance codes, Addr 0x05, OC-12, OC-3
                              0x00,  // (0x06) Gigabit Ethernet Compliant codes, Addr 0x06, 
                              0x00,  // (0x07) Fibre Channel link length/ Transmitter Technology,  Addr 0x87
                              0x00,  // (0x08) Fibre Channel transmission media (MSB), Addr 0x88
                              0x00,  // (0x09) Fibre Channel transmission media (LSB), Addr 0x89
                              0x00,  // (0x0A) See byte 36 ¡°extended compliance code¡±
                              0x03,  // (0x0B) Encoding, Addr 0x8B, for NRZ(0x03) or 64B/66B (0x05)
                              0x1E,  // (0x0C) BR, Addr 0x8C, Nominal bit rate, units of 100 Mbps. For BR > 3 G
                              0x00,  // (0x0D) Rate Identifier, Extended rateselect Compliance, Addr 0x8D, Rate Select enable: Ver 2, 0x02
                              0x14,  // (0x0E) Lenght (SMF), Addr 0x8E
                              0x00,  // (0x0F) Lenght (OM3 50um), Addr 0x8F
                              0x00,  // (0x10) Lenght (OM2 50um), Addr 0x90
                              0x00,  // (0x11) Lenght (OM1 62. um), Addr 0x91
                              0x00,  // (x012) Lenght (OM4), Addr 0x92
                              0x00,  // (x013) Lenght (OM3), Addr 0x92
                              'O',//0x00,  // (0x14) Vendor Name[0], Addr 0x95
                              'p',//0x00,  // (x015) Vendor Name[1], Addr 0x95
                              't',//0x00,  // (0x16) Vendor Name[2], Addr 0x96
                              'o',//0x00,  // (0x17) Vendor Name[3], Addr 0x97
                              'W',//0x00,  // (0x18) Vendor Name[4], Addr 0x98
                              'i',//0x00,  // (0x19) Vendor Name[5], Addr 0x99
                              'z',//0x00,  // (0x1A) Vendor Name[6], Addr 0x9A
                              ' ',//0x00,  // (0x1B) Vendor Name[7], Addr 0x9B
                              ' ',//0x00,  // (0x1C) Vendor Name[8], Addr 0x9C
                              ' ',//0x00,  // (0x1D) Vendor Name[9], Addr 0x9D
                              ' ',//0x00,  // (0x1E) Vendor Name[10], Addr 0x9E
                              ' ',//0x00,  // (0x1F) Vendor Name[11], Addr 0x9F
                              ' ',//0x00,  // (0x20) Vendor Name[12], Addr 0xA0
                              ' ',//0x00,  // (0x21) Vendor Name[13], Addr 0xA1
                              ' ',//0x00,  // (0x22) Vendor Name[14], Addr 0xA2
                              ' ',//0x00,  // (0x23) Vendor Name[15], Addr 0xA3
                              0x00,  // (0x24) 100GBASE-ER4 or 25GBASE-ER, Code for electronic or optical compatibility, Extended Module, Addr 0xA4
                              0x00,  // (0x25) Vendor OUI[0], Addr 0xA5
                              0x00,  // (0x26) Vendor OUI[1], Addr 0xA6
                              0x00,  // (0x27) Vendor OUT[2], Addr 0xA7
                              'D',//0x48,  // (0x28) Vendor PN[0], Addr 0xA8 "SDX2DLE-IT29x" x= A/B/C/D
                              'P',//0x46,  // (0x29) Vendor PN[1], Addr 0xA9
                              '3',//0x52,  // (0x2A) Vendor PN[2], Addr 0xAA
                              '1',//0x44,  // (0x2B) Vendor PN[3], Addr 0xAB
                              'D',//0x5F,  // (0x2C) Vendor PN[4], Addr 0xAC
                              '-',//0x31,  // (0x2D) Vendor PN[5], Addr 0xAD
                              'E',//0x30,  // (0x2E) Vendor PN[6], Addr 0xAE
                              'M',//0x38,  // (0x2F) Vendor PN[7], Addr 0xAF
                              '5',//0x20,  // (0x30) Vendor PN[8], Addr 0xB0
                              '1',//0x62,  // (0x31) Vendor PN[9], Addr 0xB1
                              'C',//0x79,  // (0x32) Vendor PN[10], Addr 0xB2
                              ' ',//0x43,  // (0x33) Vendor PN[11], Addr 0xB3
                              ' ',//0x6C,  // (0x34) Vendor PN[12], Addr 0xB4
                              ' ',//0x61,  // (0x35) Vendor PN[13], Addr 0xB5
                              ' ',//0x72,  // (0x36) Vendor PN[14], Addr 0xB6
                              ' ',//0x6B,  // (0x37) Vendor PN[15], Addr 0xB7
                              '1',  // (0x38) Vendor Rev[0], Addr 0xB8
                              '.',  // (0x39) Vendor Rev[1], Addr 0xB9
                              '0',  // (0x3A) Vendor Rev[2], Addr 0xB8
                              ' ',  // (0x3B) Vendor Rev[3], Addr 0xB9
                              
                              0x05,  //0x3C,  //Wave Length or Copper Cable Attenuation[0], Addr 0xBA, 1302 nm
                              0x83,  //0x3D,  //Wave Length or Copper Cable Attenuation[1], Addr 0xBB          
                              
                              0x00,  // (0x3E) Unallocated
                              0xCE,  // (0x3F) CC_BASE, Check code for Base ID Fields (addresses 0 to 62)
                              0x16,  // (0x40) Options_1, 5:High Power Level Declaration (3), 4:Paging, 3: CDR, 2: Cooled, 1: Power Level Declaration(1, 2), 0: Linear Receiver Output
                              0x1A,  // (0x41) Options_2, 7: RDT, 6: Tunable, 5: RS, 4: TX_DIS, 3: TX_FAULT, 2: LOS(SD), 1: LOS(RX_LOS) 
                              0x1E,  // (0x42) BR, max: Upper bit rate margin, units of % (see details for rates < 3 Gb/s)
                              0x0C,  // (0x43) BR, min: Lower bit rate margin, units of % (see details for rates > 1.2 Gb/s)
                              'X',  // (0x44) Vendor SN[0], Addr 0xC4
                              'C',  // (0x45) Vendor SN[1], Addr 0xC5
                              '2',  // (0x46) Vendor SN[2], Addr 0xC6
                              '1',  // (0x47) Vendor SN[3], Addr 0xC7
                              '3',  // (0x48) Vendor SN[4], Addr 0xC8
                              '3',  // (0x49) Vendor SN[5], Addr 0xC9
                              '0',  // (0x4A) Vendor SN[6], Addr 0xCA
                              '0',  // (0x4B) Vendor SN[7], Addr 0xCB
                              '0',  // (0x4C) Vendor SN[8], Addr 0xCC
                              '1',  // (0x4D) Vendor SN[9], Addr 0xCD
                              0x20,  // (0x4E) Vendor SN[10], Addr 0xCE
                              0x20,  // (0x4F) Vendor SN[11], Addr 0xCF
                              0x20,  // (0x50) Vendor SN[12], Addr 0xD0
                              0x20,  // (0x51) Vendor SN[13], Addr 0xD1
                              0x20,  // (0x52) Vendor SN[14], Addr 0xD2
                              0x20,  // (0x53) Vendor SN[15], Addr 0xD3
                              0x32,  // (0x54) DATECODE[0], Addr 0xD4
                              0x30,  // (0x55) DATECODE[1], Addr 0xD5
                              0x32,  // (0x56) DATECODE[2], Addr 0xD6
                              0x31,  // (0x57) DATECODE[3], Addr 0xD7
                              0x30,  // (0x58) DATECODE[4], Addr 0xD8
                              0x31,  // (0x59) DATECODE[5], Addr 0xD9
                              0x32,  // (0x5A) DATECODE[6], Addr 0xDA
                              0x37,  // (0x5B) DATECODE[7], Addr 0xDB
                              0x68,  // (0x5C) Diagnostic Monitoring type, Addr 0xDC, 6: DDM, 5: Internally calibrated, 4: Externally calibrated, 3: AVG/OMA, 
                              0x78,  // (0x5D) Enhanced Options, Addr 0xDD, Rate Select enable: 0x18, Ethernet only: 0x10
                              0x08,  // (0x5E) SFF-8472 Compliance, Includes functionality described in Rev 12.3 of SFF-8472.
                              0x00,  // (0x5F) CC_EXT[7], Addr 0xDF, the sum of the contents of all the bytes from byte 64 to byte 94, inclusive
                              0x00,  //VENDOR_SPECIFIC_EE[0], Addr 0xE0
                              0x00,  //VENDOR_SPECIFIC_EE[1], Addr 0xE1
                              0x00,  //VENDOR_SPECIFIC_EE[2], Addr 0xE2
                              0x00,  //VENDOR_SPECIFIC_EE[3], Addr 0xE3
                              0x00,  //VENDOR_SPECIFIC_EE[4], Addr 0xE4
                              0x00,  //VENDOR_SPECIFIC_EE[5], Addr 0xE5
                              0x00,  //VENDOR_SPECIFIC_EE[6], Addr 0xE6
                              0x00,  //VENDOR_SPECIFIC_EE[7], Addr 0xE7
                              0x00,  //VENDOR_SPECIFIC_EE[8], Addr 0xE8, LD Bias Real Value(Ch0)
                              0x00,  //VENDOR_SPECIFIC_EE[9], Addr 0xE9
                              0x00,  //VENDOR_SPECIFIC_EE[10], Addr 0xEA, LD Bias Real Value(Ch1)
                              0x00,  //VENDOR_SPECIFIC_EE[11], Addr 0xEB
                              0x00,  //VENDOR_SPECIFIC_EE[12], Addr 0xEC, LD Bias Real Value(Ch2)
                              0x00,  //VENDOR_SPECIFIC_EE[13], Addr 0xED
                              0x00,  //VENDOR_SPECIFIC_EE[14], Addr 0xEE, LD Bias Real Value(Ch3)
                              0x00,  //VENDOR_SPECIFIC_EE[15], Addr 0xEF
                              0x00,  //VENDOR_SPECIFIC_EE[16], Addr 0xF0, MPD0_ADC MSB
                              0x00,  //VENDOR_SPECIFIC_EE[17], Addr 0xF1
                              0x00,  //VENDOR_SPECIFIC_EE[18], Addr 0xE2, MPD1_ADC MSB
                              0x00,  //VENDOR_SPECIFIC_EE[19], Addr 0xF3
                              0x00,  //VENDOR_SPECIFIC_EE[20], Addr 0xF4, MPD2_ADC MSB
                              0x00,  //VENDOR_SPECIFIC_EE[21], Addr 0xF5
                              0x00,  //VENDOR_SPECIFIC_EE[22], Addr 0xF6, MPD3_ADC MSB
                              0x00,  //VENDOR_SPECIFIC_EE[23], Addr 0xF7
                              0x00,  //VENDOR_SPECIFIC_EE[24], Addr 0xF8, RSSI0_ADC MSB
                              0x00,  //VENDOR_SPECIFIC_EE[25], Addr 0xF9
                              0x00,  //VENDOR_SPECIFIC_EE[26], Addr 0xFA, RSSI0_ADC MSB
                              0x00,  //VENDOR_SPECIFIC_EE[27], Addr 0xFB
                              0x00,  //VENDOR_SPECIFIC_EE[28], Addr 0xFC, RSSI0_ADC MSB
                              0x00,  //VENDOR_SPECIFIC_EE[29], Addr 0xFD
                              0x00,  //VENDOR_SPECIFIC_EE[30], Addr 0xFE, RSSI0_ADC MSB
                              0x00,   //VENDOR_SPECIFIC_EE[31],Addr 0xFF
                            };


#pragma required = FlashData_A0_Const

#else

#pragma location = FLASH_A0_CONST_START

const unsigned char FlashData_A0_Const[] =
                            { // DEFAULT VALUES
                              0x0B,  // IDENTIFER(0x01),   DWDM-SFP28
                              0x04,  // EXT. IDENTIFER, Addr 0x01, SFP ftn def'd by two-wire if ID only
                              0x07,  // CONNECTOR Types(0x02): LC (0x07)
                              0x00,  // (0x03) Transceiver Compliance Codes [Address A0h, Bytes 3-10 and 36], 10G-ER, LRM, LR, SR, SX, LX, CA, CP
                              0x00,  // (0x04) SONET Compliance codes, Addr 0x84, ESCON, OC-192, SONET, OC-48, 
                              0x00,  // (0x05) SAS/SATA compliance codes, Addr 0x05, OC-12, OC-3
                              0x00,  // (0x06) Gigabit Ethernet Compliant codes, Addr 0x06, 
                              0x00,  // (0x07) Fibre Channel link length/ Transmitter Technology,  Addr 0x87
                              0x00,  // (0x08) Fibre Channel transmission media (MSB), Addr 0x88
                              0x00,  // (0x09) Fibre Channel transmission media (LSB), Addr 0x89
                              0x00,  // (0x0A) See byte 36 ¡°extended compliance code¡±
                              0x03,  // (0x0B) Encoding, Addr 0x8B, for NRZ(0x03) or 64B/66B (0x05)
                              0xFF,  // (0x0C) BR, Addr 0x8C, Nominal bit rate, units of 100 Mbps. For BR > 25.4G
                              0x00,  // (0x0D) Rate Identifier, Extended rateselect Compliance, Addr 0x8D, Rate Select enable: Ver 2, 0x02
                              0x14,  // (0x0E) Lenght (SMF), Addr 0x8E
                              0x00,  // (0x0F) Lenght (OM3 50um), Addr 0x8F
                              0x00,  // (0x10) Lenght (OM2 50um), Addr 0x90
                              0x00,  // (0x11) Lenght (OM1 62. um), Addr 0x91
                              0x00,  // (x012) Lenght (OM4), Addr 0x92
                              0x00,  // (x013) Lenght (OM3), Addr 0x92
                              'O',//0x00,  // (0x14) Vendor Name[0], Addr 0x95
                              'p',//0x00,  // (x015) Vendor Name[1], Addr 0x95
                              't',//0x00,  // (0x16) Vendor Name[2], Addr 0x96
                              'o',//0x00,  // (0x17) Vendor Name[3], Addr 0x97
                              'W',//0x00,  // (0x18) Vendor Name[4], Addr 0x98
                              'i',//0x00,  // (0x19) Vendor Name[5], Addr 0x99
                              'z',//0x00,  // (0x1A) Vendor Name[6], Addr 0x9A
                              ' ',//0x00,  // (0x1B) Vendor Name[7], Addr 0x9B
                              ' ',//0x00,  // (0x1C) Vendor Name[8], Addr 0x9C
                              ' ',//0x00,  // (0x1D) Vendor Name[9], Addr 0x9D
                              ' ',//0x00,  // (0x1E) Vendor Name[10], Addr 0x9E
                              ' ',//0x00,  // (0x1F) Vendor Name[11], Addr 0x9F
                              ' ',//0x00,  // (0x20) Vendor Name[12], Addr 0xA0
                              ' ',//0x00,  // (0x21) Vendor Name[13], Addr 0xA1
                              ' ',//0x00,  // (0x22) Vendor Name[14], Addr 0xA2
                              ' ',//0x00,  // (0x23) Vendor Name[15], Addr 0xA3
                              0x00,  // (0x24) 100GBASE-ER4 or 25GBASE-ER, Code for electronic or optical compatibility, Extended Module, Addr 0xA4
                              0x00,  // (0x25) Vendor OUI[0], Addr 0xA5
                              0x00,  // (0x26) Vendor OUI[1], Addr 0xA6
                              0x00,  // (0x27) Vendor OUT[2], Addr 0xA7
                              'S',//0x48,  // (0x28) Vendor PN[0], Addr 0xA8 "SDX2DLE-IT29x" x= A/B/C/D
                              'D',//0x46,  // (0x29) Vendor PN[1], Addr 0xA9
                              'X',//0x52,  // (0x2A) Vendor PN[2], Addr 0xAA
                              '2',//0x44,  // (0x2B) Vendor PN[3], Addr 0xAB
                              'D',//0x5F,  // (0x2C) Vendor PN[4], Addr 0xAC
                              'L',//0x31,  // (0x2D) Vendor PN[5], Addr 0xAD
                              'E',//0x30,  // (0x2E) Vendor PN[6], Addr 0xAE
                              '-',//0x38,  // (0x2F) Vendor PN[7], Addr 0xAF
                              'I',//0x20,  // (0x30) Vendor PN[8], Addr 0xB0
                              'T',//0x62,  // (0x31) Vendor PN[9], Addr 0xB1
                              '2',//0x79,  // (0x32) Vendor PN[10], Addr 0xB2
                              '7',//0x43,  // (0x33) Vendor PN[11], Addr 0xB3
                              'C',//0x6C,  // (0x34) Vendor PN[12], Addr 0xB4
                              ' ',//0x61,  // (0x35) Vendor PN[13], Addr 0xB5
                              ' ',//0x72,  // (0x36) Vendor PN[14], Addr 0xB6
                              ' ',//0x6B,  // (0x37) Vendor PN[15], Addr 0xB7
                              '1',  // (0x38) Vendor Rev[0], Addr 0xB8
                              '.',  // (0x39) Vendor Rev[1], Addr 0xB9
                              '1',  // (0x3A) Vendor Rev[2], Addr 0xB8
                              ' ',  // (0x3B) Vendor Rev[3], Addr 0xB9
                              0x00,  //0x3C,  //Wave Length or Copper Cable Attenuation[0], Addr 0xBA, 1302 nm
                              0x00,  //0x3D,  //Wave Length or Copper Cable Attenuation[1], Addr 0xBB
                              0x00,  // (0x3E) Unallocated
                              0xCE,  // (0x3F) CC_BASE, Check code for Base ID Fields (addresses 0 to 62)
                              0x3C,  // (0x40) Options_1, 5:High Power Level Declaration (3), 4:Paging, 3: CDR, 2: Cooled, 1: Power Level Declaration(1, 2), 0: Linear Receiver Output
                              0x7A,  // (0x41) Options_2, 7: RDT, 6: Tunable, 5: RS, 4: TX_DIS, 3: TX_FAULT, 2: LOS(SD), 1: LOS(RX_LOS) 
                              0x67,  // (0x42) BR, max: Upper bit rate margin, units of % (see details for rates > 25.4 Gb/s)
                              0x00,  // (0x43) BR, min: Lower bit rate margin, units of % (see details for rates > 25.4 Gb/s)
                              'T',  // (0x44) Vendor SN[0], Addr 0xC4
                              'S',  // (0x45) Vendor SN[1], Addr 0xC5
                              'E',  // (0x46) Vendor SN[2], Addr 0xC6
                              '2',  // (0x47) Vendor SN[3], Addr 0xC7
                              '0',  // (0x48) Vendor SN[4], Addr 0xC8
                              '4',  // (0x49) Vendor SN[5], Addr 0xC9
                              '5',  // (0x4A) Vendor SN[6], Addr 0xCA
                              '0',  // (0x4B) Vendor SN[7], Addr 0xCB
                              '0',  // (0x4C) Vendor SN[8], Addr 0xCC
                              '0',  // (0x4D) Vendor SN[9], Addr 0xCD
                              '0',  // (0x4E) Vendor SN[10], Addr 0xCE
                              '1',  // (0x4F) Vendor SN[11], Addr 0xCF
                              0x20,  // (0x50) Vendor SN[12], Addr 0xD0
                              0x20,  // (0x51) Vendor SN[13], Addr 0xD1
                              0x20,  // (0x52) Vendor SN[14], Addr 0xD2
                              0x20,  // (0x53) Vendor SN[15], Addr 0xD3
                              0x32,  // (0x54) DATECODE[0], Addr 0xD4
                              0x30,  // (0x55) DATECODE[1], Addr 0xD5
                              0x32,  // (0x56) DATECODE[2], Addr 0xD6
                              0x30,  // (0x57) DATECODE[3], Addr 0xD7
                              0x31,  // (0x58) DATECODE[4], Addr 0xD8
                              0x30,  // (0x59) DATECODE[5], Addr 0xD9
                              0x32,  // (0x5A) DATECODE[6], Addr 0xDA
                              0x33,  // (0x5B) DATECODE[7], Addr 0xDB
                              0x68,  // (0x5C) Diagnostic Monitoring type, Addr 0xDC, 6: DDM, 5: Internally calibrated, 4: Externally calibrated, 3: AVG/OMA, 
                              0x78,  // (0x5D) Enhanced Options, Addr 0xDD, Rate Select enable: 0x18, Ethernet only: 0x10
                              0x08,  // (0x5E) SFF-8472 Compliance, Includes functionality described in Rev 12.3 of SFF-8472.
                              0x00,  // (0x5F) CC_EXT[7], Addr 0xDF, the sum of the contents of all the bytes from byte 64 to byte 94, inclusive
                              0x00,  //VENDOR_SPECIFIC_EE[0], Addr 0xE0
                              0x00,  //VENDOR_SPECIFIC_EE[1], Addr 0xE1
                              0x00,  //VENDOR_SPECIFIC_EE[2], Addr 0xE2
                              0x00,  //VENDOR_SPECIFIC_EE[3], Addr 0xE3
                              0x00,  //VENDOR_SPECIFIC_EE[4], Addr 0xE4
                              0x00,  //VENDOR_SPECIFIC_EE[5], Addr 0xE5
                              0x00,  //VENDOR_SPECIFIC_EE[6], Addr 0xE6
                              0x00,  //VENDOR_SPECIFIC_EE[7], Addr 0xE7
                              0x00,  //VENDOR_SPECIFIC_EE[8], Addr 0xE8, LD Bias Real Value(Ch0)
                              0x00,  //VENDOR_SPECIFIC_EE[9], Addr 0xE9
                              0x00,  //VENDOR_SPECIFIC_EE[10], Addr 0xEA, LD Bias Real Value(Ch1)
                              0x00,  //VENDOR_SPECIFIC_EE[11], Addr 0xEB
                              0x00,  //VENDOR_SPECIFIC_EE[12], Addr 0xEC, LD Bias Real Value(Ch2)
                              0x00,  //VENDOR_SPECIFIC_EE[13], Addr 0xED
                              0x00,  //VENDOR_SPECIFIC_EE[14], Addr 0xEE, LD Bias Real Value(Ch3)
                              0x00,  //VENDOR_SPECIFIC_EE[15], Addr 0xEF
                              0x00,  //VENDOR_SPECIFIC_EE[16], Addr 0xF0, MPD0_ADC MSB
                              0x00,  //VENDOR_SPECIFIC_EE[17], Addr 0xF1
                              0x00,  //VENDOR_SPECIFIC_EE[18], Addr 0xE2, MPD1_ADC MSB
                              0x00,  //VENDOR_SPECIFIC_EE[19], Addr 0xF3
                              0x00,  //VENDOR_SPECIFIC_EE[20], Addr 0xF4, MPD2_ADC MSB
                              0x00,  //VENDOR_SPECIFIC_EE[21], Addr 0xF5
                              0x00,  //VENDOR_SPECIFIC_EE[22], Addr 0xF6, MPD3_ADC MSB
                              0x00,  //VENDOR_SPECIFIC_EE[23], Addr 0xF7
                              0x00,  //VENDOR_SPECIFIC_EE[24], Addr 0xF8, RSSI0_ADC MSB
                              0x00,  //VENDOR_SPECIFIC_EE[25], Addr 0xF9
                              0x00,  //VENDOR_SPECIFIC_EE[26], Addr 0xFA, RSSI0_ADC MSB
                              0x00,  //VENDOR_SPECIFIC_EE[27], Addr 0xFB
                              0x00,  //VENDOR_SPECIFIC_EE[28], Addr 0xFC, RSSI0_ADC MSB
                              0x00,  //VENDOR_SPECIFIC_EE[29], Addr 0xFD
                              0x00,  //VENDOR_SPECIFIC_EE[30], Addr 0xFE, RSSI0_ADC MSB
                              0x00,   //VENDOR_SPECIFIC_EE[31],Addr 0xFF
                            };


#pragma required = FlashData_A0_Const

#endif

#else


#pragma location = FLASH_A0_CONST_START
const unsigned char FlashData_A0_Const[] =
                            { // DEFAULT VALUES
                              0x03,  // IDENTIFER(0x01),   SFP28
                              0x04,  // EXT. IDENTIFER, Addr 0x01, SFP ftn def'd by two-wire if ID only
                              0x07,  // CONNECTOR Types(0x02): LC (0x07)
                              0x00,  // (0x03) Transceiver Compliance Codes [Address A0h, Bytes 3-10 and 36], 10G-ER, LRM, LR, SR, SX, LX, CA, CP
                              0x00,  // (0x04) SONET Compliance codes, Addr 0x84, ESCON, OC-192, SONET, OC-48, 
                              0x00,  // (0x05) SAS/SATA compliance codes, Addr 0x05, OC-12, OC-3
                              0x00,  // (0x06) Gigabit Ethernet Compliant codes, Addr 0x06, 
                              0x00,  // (0x07) Fibre Channel link length/ Transmitter Technology,  Addr 0x87
                              0x00,  // (0x08) Fibre Channel transmission media (MSB), Addr 0x88
                              0x00,  // (0x09) Fibre Channel transmission media (LSB), Addr 0x89
                              0x02,  // (0x0A) See byte 36 ¡°extended compliance code¡±
                              0x03,  // (0x0B) Encoding, Addr 0x8B, for NRZ(0x03) or 64B/66B (0x05)
                              0xFF,  // (0x0C) BR, Addr 0x8C, Nominal bit rate, units of 100 Mbps. For BR > 25.4G
                              0x00,  // (0x0D) Rate Identifier, Extended rateselect Compliance, Addr 0x8D, Rate Select enable: Ver 2, 0x02
                              0x1E,  // (0x0E) Lenght (SMF), Addr 0x8E
                              0x00,  // (0x0F) Lenght (OM3 50um), Addr 0x8F
                              0x00,  // (0x10) Lenght (OM2 50um), Addr 0x90
                              0x00,  // (0x11) Lenght (OM1 62. um), Addr 0x91
                              0x00,  // (x012) Lenght (OM4), Addr 0x92
                              0x00,  // (x013) Lenght (OM3), Addr 0x92
                              'C',//0x00,  // (0x14) Vendor Name[0], Addr 0x95
                              'O',//0x00,  // (x015) Vendor Name[1], Addr 0x95
                              'S',//0x00,  // (0x16) Vendor Name[2], Addr 0x96
                              'E',//0x00,  // (0x17) Vendor Name[3], Addr 0x97
                              'T',//0x00,  // (0x18) Vendor Name[4], Addr 0x98
                              ' ',//0x00,  // (0x19) Vendor Name[5], Addr 0x99
                              'I',//0x00,  // (0x1A) Vendor Name[6], Addr 0x9A
                              'n',//0x00,  // (0x1B) Vendor Name[7], Addr 0x9B
                              'c',//0x00,  // (0x1C) Vendor Name[8], Addr 0x9C
                              '.',//0x00,  // (0x1D) Vendor Name[9], Addr 0x9D
                              ' ',//0x00,  // (0x1E) Vendor Name[10], Addr 0x9E
                              ' ',//0x00,  // (0x1F) Vendor Name[11], Addr 0x9F
                              ' ',//0x00,  // (0x20) Vendor Name[12], Addr 0xA0
                              ' ',//0x00,  // (0x21) Vendor Name[13], Addr 0xA1
                              ' ',//0x00,  // (0x22) Vendor Name[14], Addr 0xA2
                              ' ',//0x00,  // (0x23) Vendor Name[15], Addr 0xA3
                              0x04,  // (0x24) 100GBASE-ER4 or 25GBASE-ER, Code for electronic or optical compatibility, Extended Module, Addr 0xA4
                              0x00,  // (0x25) Vendor OUI[0], Addr 0xA5
                              0x00,  // (0x26) Vendor OUI[1], Addr 0xA6
                              0x00,  // (0x27) Vendor OUT[2], Addr 0xA7
                              'C',//0x48,  // (0x28) Vendor PN[0], Addr 0xA8
                              'S',//0x46,  // (0x29) Vendor PN[1], Addr 0xA9
                              '1',//0x52,  // (0x2A) Vendor PN[2], Addr 0xAA
                              'X',//0x44,  // (0x2B) Vendor PN[3], Addr 0xAB
                              'Q',//0x5F,  // (0x2C) Vendor PN[4], Addr 0xAC
                              '-',//0x31,  // (0x2D) Vendor PN[5], Addr 0xAD
                              '0',//0x30,  // (0x2E) Vendor PN[6], Addr 0xAE
                              '1',//0x38,  // (0x2F) Vendor PN[7], Addr 0xAF
                              'L',//0x20,  // (0x30) Vendor PN[8], Addr 0xB0
                              '3',//0x62,  // (0x31) Vendor PN[9], Addr 0xB1
                              'C',//0x79,  // (0x32) Vendor PN[10], Addr 0xB2
                              'W',//0x43,  // (0x33) Vendor PN[11], Addr 0xB3
                              'I',//0x6C,  // (0x34) Vendor PN[12], Addr 0xB4
                              ' ',//0x61,  // (0x35) Vendor PN[13], Addr 0xB5
                              ' ',//0x72,  // (0x36) Vendor PN[14], Addr 0xB6
                              ' ',//0x6B,  // (0x37) Vendor PN[15], Addr 0xB7
                              'V',  // (0x38) Vendor Rev[0], Addr 0xB8
                              '1',  // (0x39) Vendor Rev[1], Addr 0xB9
                              'R',  // (0x3A) Vendor Rev[2], Addr 0xB8
                              '1',  // (0x3B) Vendor Rev[3], Addr 0xB9
                              0x05,  //0x3C,  //Wave Length or Copper Cable Attenuation[0], Addr 0xBA, 1302 nm
                              0x1E,  //0x3D,  //Wave Length or Copper Cable Attenuation[1], Addr 0xBB
                              0x00,  // (0x3E) Unallocated
                              0xCE,  // (0x3F) CC_BASE, Check code for Base ID Fields (addresses 0 to 62)
                              0x3E,  // (0x40) Options_1, 5:High Power Level Declaration, 4:Paging, 3: CDR, 2: Cooled, 1: Power Level Declaration, 0: Linear Receiver Output
                              0x12,  // (0x41) Options_2, 7: RDT, 6: Tunable, 5: RS, 4: TX_DIS, 3: TX_FAULT, 2: LOS(SD), 1: LOS(RX_LOS) 
                              0x00,  // (0x42) BR, max: Upper bit rate margin, units of % (see details for rates > 25.4 Gb/s)
                              0x00,  // (0x43) BR, min: Lower bit rate margin, units of % (see details for rates > 25.4 Gb/s)
                              'T',  // (0x44) Vendor SN[0], Addr 0xC4
                              'S',  // (0x45) Vendor SN[1], Addr 0xC5
                              'E',  // (0x46) Vendor SN[2], Addr 0xC6
                              '2',  // (0x47) Vendor SN[3], Addr 0xC7
                              '0',  // (0x48) Vendor SN[4], Addr 0xC8
                              '0',  // (0x49) Vendor SN[5], Addr 0xC9
                              '4',  // (0x4A) Vendor SN[6], Addr 0xCA
                              '0',  // (0x4B) Vendor SN[7], Addr 0xCB
                              '0',  // (0x4C) Vendor SN[8], Addr 0xCC
                              '0',  // (0x4D) Vendor SN[9], Addr 0xCD
                              '0',  // (0x4E) Vendor SN[10], Addr 0xCE
                              '1',  // (0x4F) Vendor SN[11], Addr 0xCF
                              0x20,  // (0x50) Vendor SN[12], Addr 0xD0
                              0x20,  // (0x51) Vendor SN[13], Addr 0xD1
                              0x20,  // (0x52) Vendor SN[14], Addr 0xD2
                              0x20,  // (0x53) Vendor SN[15], Addr 0xD3
                              0x32,  // (0x54) DATECODE[0], Addr 0xD4
                              0x30,  // (0x55) DATECODE[1], Addr 0xD5
                              0x30,  // (0x56) DATECODE[2], Addr 0xD6
                              0x31,  // (0x57) DATECODE[3], Addr 0xD7
                              0x31,  // (0x58) DATECODE[4], Addr 0xD8
                              0x37,  // (0x59) DATECODE[5], Addr 0xD9
                              0x00,  // (0x5A) DATECODE[6], Addr 0xDA
                              0x00,  // (0x5B) DATECODE[7], Addr 0xDB
                              0x68,  // (0x5C) Diagnostic Monitoring type, Addr 0xDC, 6: DDM, 5: Internally calibrated, 4: Externally calibrated, 3: AVG/OMA, 
                              0x40,  // (0x5D) Enhanced Options, Addr 0xDD, Rate Select enable: 0x18, Ethernet only: 0x10
                              0x08,  // (0x5E) SFF-8472 Compliance, Includes functionality described in Rev 12.3 of SFF-8472.
                              0x00,  // (0x5F) CC_EXT[7], Addr 0xDF, the sum of the contents of all the bytes from byte 64 to byte 94, inclusive
                              0xFF,  //VENDOR_SPECIFIC_EE[0], Addr 0xE0
                              0xFF,  //VENDOR_SPECIFIC_EE[1], Addr 0xE1
                              0xFF,  //VENDOR_SPECIFIC_EE[2], Addr 0xE2
                              0xFF,  //VENDOR_SPECIFIC_EE[3], Addr 0xE3
                              0xFF,  //VENDOR_SPECIFIC_EE[4], Addr 0xE4
                              0xFF,  //VENDOR_SPECIFIC_EE[5], Addr 0xE5
                              0xFF,  //VENDOR_SPECIFIC_EE[6], Addr 0xE6
                              0xFF,  //VENDOR_SPECIFIC_EE[7], Addr 0xE7
                              0xFF,  //VENDOR_SPECIFIC_EE[8], Addr 0xE8, LD Bias Real Value(Ch0)
                              0xFF,  //VENDOR_SPECIFIC_EE[9], Addr 0xE9
                              0xFF,  //VENDOR_SPECIFIC_EE[10], Addr 0xEA, LD Bias Real Value(Ch1)
                              0xFF,  //VENDOR_SPECIFIC_EE[11], Addr 0xEB
                              0xFF,  //VENDOR_SPECIFIC_EE[12], Addr 0xEC, LD Bias Real Value(Ch2)
                              0xFF,  //VENDOR_SPECIFIC_EE[13], Addr 0xED
                              0xFF,  //VENDOR_SPECIFIC_EE[14], Addr 0xEE, LD Bias Real Value(Ch3)
                              0xFF,  //VENDOR_SPECIFIC_EE[15], Addr 0xEF
                              0xFF,  //VENDOR_SPECIFIC_EE[16], Addr 0xF0, MPD0_ADC MSB
                              0xFF,  //VENDOR_SPECIFIC_EE[17], Addr 0xF1
                              0xFF,  //VENDOR_SPECIFIC_EE[18], Addr 0xE2, MPD1_ADC MSB
                              0xFF,  //VENDOR_SPECIFIC_EE[19], Addr 0xF3
                              0xFF,  //VENDOR_SPECIFIC_EE[20], Addr 0xF4, MPD2_ADC MSB
                              0xFF,  //VENDOR_SPECIFIC_EE[21], Addr 0xF5
                              0xFF,  //VENDOR_SPECIFIC_EE[22], Addr 0xF6, MPD3_ADC MSB
                              0xFF,  //VENDOR_SPECIFIC_EE[23], Addr 0xF7
                              0xFF,  //VENDOR_SPECIFIC_EE[24], Addr 0xF8, RSSI0_ADC MSB
                              0xFF,  //VENDOR_SPECIFIC_EE[25], Addr 0xF9
                              0xFF,  //VENDOR_SPECIFIC_EE[26], Addr 0xFA, RSSI0_ADC MSB
                              0xFF,  //VENDOR_SPECIFIC_EE[27], Addr 0xFB
                              0xFF,  //VENDOR_SPECIFIC_EE[28], Addr 0xFC, RSSI0_ADC MSB
                              0xFF,  //VENDOR_SPECIFIC_EE[29], Addr 0xFD
                              0xFF,  //VENDOR_SPECIFIC_EE[30], Addr 0xFE, RSSI0_ADC MSB
                              0xFF,   //VENDOR_SPECIFIC_EE[31],Addr 0xFF
                            };
#pragma required = FlashData_A0_Const
                                                          
#endif                                                          
                                                          
//Table 0/1
#if 0
#pragma location = FLASH_USER_EERPOM_START                

const unsigned int FlashDataUeserEEPROM[] =               
                            {                                                                                       
                                0x0000,                   //Address 0x00-01
                                0x0000,                   //Address 0x02-03
                                0x0000,                   //Address 0x04-05
                                0x0000,                   //Address 0x06-07
                                0x0000,                   //Address 0x08-09
                                0x0000,                   //Address 0x0A-0B
                                0x0000,                   //Address 0x0C-0D
                                0x0000,                   //Address 0x0E-0F
                                0x0000,                   //Address 0x10-11
                                0x0000,                   //Address 0x12-13
                                0x0000,                   //Address 0x14-15
                                0x0000,                   //Address 0x16-17
                                0x0000,                   //Address 0x18-19
                                0x0000,                   //Address 0x1A-1B
                                0x0000,                   //Address 0x1C-1D
                                0x0000,                   //Address 0x1E-1F
                                0x0000,                   //Address 0x20-21
                                0x0000,                   //Address 0x22-23
                                0x0000,                   //Address 0x24-25
                                0x0000,                   //Address 0x26-27
                                0x0000,                   //Address 0x28-29
                                0x0000,                   //Address 0x2A-2B
                                0x0000,                   //Address 0x2C-2D
                                0x0000,                   //Address 0x2E-2F
                                0x0000,                   //Address 0x30-31
                                0x0000,                   //Address 0x32-33
                                0x0000,                   //Address 0x34-35
                                0x0000,                   //Address 0x36-37
                                0x0000,                   //Address 0x38-39
                                0x0000,                   //Address 0x3A-3C
                                0x0000,                   //Address 0x3C-3D
                                0x0000,                   //Address 0x3E-3F
                                0x0000,                   //Address 0x40-41
                                0x0000,                   //Address 0x42-43
                                0x0000,                   //Address 0x44-45
                                0x0000,                   //Address 0x46-47
                                0x0000,                   //Address 0x48-49
                                0x0000,                   //Address 0x4A-4C
                                0x0000,                   //Address 0x4C-4D
                                0x0000,                   //Address 0x4E-4F
                                0x0000,                   //Address 0x50-51
                                0x0000,                   //Address 0x52-53
                                0x0000,                   //Address 0x54-55
                                0x0000,                   //Address 0x56-57
                                0x0000,                   //Address 0x58-59
                                0x0000,                   //Address 0x5A-5C
                                0x0000,                   //Address 0x5C-5D
                                0x0000,                   //Address 0x5E-5F
                                0x0000,                   //Address 0x60-61
                                0x0000,                   //Address 0x62-63
                                0x0000,                   //Address 0x64-65
                                0x0000,                   //Address 0x66-67
                                0x0000,                   //Address 0x68-69
                                0x0000,                   //Address 0x6A-6C
                                0x0000,                   //Address 0x6C-6D
                                0x0000,                   //Address 0x6E-6F
                                0x0000,                   //Address 0x70-71
                                0x0000,                   //Address 0x72-73
                                0x0000,                   //Address 0x74-75
                                0x0000,                   //Address 0x76-77
                                0x0000,                   //Address 0x78-79
                                0x0000,                   //Address 0x7A-7C
                                0x0000,                   //Address 0x7C-7D
                                0x0000,                   //Address 0x7E-7F

                            };


#pragma required = FlashDataUeserEEPROM                   

#endif
                                                          

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------
/*******    A2 Lower Memory Map: This is the offset location of the registers    ********/
#define A2_TEMP_HIGH_ALARM_OFF                    0x00
#define A2_TEMP_LOW_ALARM_OFF                     0x02
#define A2_TEMP_HIGH_WARNING_OFF                  0x04
#define A2_TEMP_LOW_WARNING_OFF                   0x06
#define A2_VCC_HIGH_ALARM_OFF                 0x08
#define A2_VCC_LOW_ALARM_OFF                  0x0A
#define A2_VCC_HIGH_WARNING_OFF               0x0C
#define A2_VCC_LOW_WARNING_OFF                0x0E
#define A2_TX_BIAS_HIGH_ALARM_OFF                    0x10
#define A2_TX_BIAS_LOW_ALARM_OFF                     0x12
#define A2_TX_BIAS_HIGH_WARNING_OFF                  0x14
#define A2_TX_BIAS_LOW_WARNING_OFF                   0x16
#define A2_TX_POWER_HIGH_ALARM_OFF                0x18
#define A2_TX_POWER_LOW_ALARM_OFF                 0x1A
#define A2_TX_POWER_HIGH_WARNING_OFF              0x1C
#define A2_TX_POWER_LOW_WARNING_OFF               0x1E
#define A2_RX_POWER_HIGH_ALARM_OFF                0x20
#define A2_RX_POWER_LOW_ALARM_OFF                 0x22
#define A2_RX_POWER_HIGH_WARNING_OFF              0x24
#define A2_RX_POWER_LOW_WARNING_OFF               0x26
#define A2_LASER_TEMP_HIGH_ALARM_OFF              0x28
#define A2_LASER_TEMP_LOW_ALARM_OFF               0x2A
#define A2_LASER_TEMP_HIGH_WARNING_OFF            0x2C
#define A2_LASER_TEMP_LOW_WARNING_OFF             0x2E
#define A2_TECC_HIGH_ALARM_OFF                    0x30
#define A2_TECC_LOW_ALARM_OFF                     0x32
#define A2_TECC_HIGH_WARNING_OFF                  0x34
#define A2_TECC_LOW_WARNING_OFF                   0x36

#define A2_RESERVED_38_4B_OFF                     0x38
#define A2_RX_PWR_EXT_COEFF_4_OFF                 0x38
#define A2_RX_PWR_EXT_COEFF_3_OFF                 0x3C
#define A2_RX_PWR_EXT_COEFF_2_OFF                 0x40
#define A2_RX_PWR_EXT_COEFF_1_OFF                 0x44
#define A2_RX_PWR_EXT_COEFF_0_OFF                 0x48

#define A2_RESERVED_4C_5F_OFF                     0x4C
#define A2_TX_I_SLOPE_OFF                         0x4C
#define A2_TX_I_OFFSET_OFF                        0x4E

#define A2_TX_PWR_SLOPE_OFF                       0x50
#define A2_TX_PWR_OFFSET_OFF                      0x52

#define A2_TEMP_SLOPE_OFF                         0x54
#define A2_TEMP_OFFSET_OFF                        0x56

#define A2_VCC_SLOPE_OFF                          0x58
#define A2_VCC_OFFSET_OFF                         0x5A

#define A2_CC_DMI_OFF                             0x5F

#define A2_TEMPERATURE_OFF                        0x60
#define A2_VCC_OFF                                0x62
#define A2_TX_BIAS_OFF                            0x64
#define A2_TX_POWER_OFF                           0x66
#define A2_RX_POWER_OFF                           0x68
#define A2_LASER_TEMP_OFF                         0x6A
#define A2_TEC_CURRENT_OFF                        0x6C
#define A2_STATUS_CONTROL_OFF                     0x6E
#define A2_RESERVED_6F_OFF                        0x6F
#define A2_ALARM_WARNING_70_OFF                   0x70
#define A2_ALARM_WARNING_71_OFF                   0x71
#define A2_TXEQ_72_OFF                            0x72
#define A2_RXPREEMP_73_OFF                        0x73
#define A2_ALARM_WARNING_74_OFF                   0x74
#define A2_ALARM_WARNING_75_OFF                   0x75
#define A2_EXTENDED_CONTROL_STATUS_OFF            0x76

#define A2_RESERVED_77_OFF                        0x77
#define A2_64GFC_MODE_OFF                         0x77

#define A2_READ_CHIP_STATUS_OFF                   0x78
#define A2_OPERATION_MODE_OFF                     0x79
#define A2_LUT_MODE_OFF                           0x7A
#define A2_PASSWORD_OFF                           0x7B
#define A2_TABLE_OFF                              0x7F

#define SFP28_LOWER_MEMORY_PAGE_SEL               0x7F

#endif

//-----------------------------------------------------------------------------
// default values defines
//-----------------------------------------------------------------------------
#if __SFP28_ER_SEMI_TUNABLE__ == 1

#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1

#pragma location = FLASH_A2_LOWER_CONST_START                         


const unsigned int FlashDataA2_Const[] =                        
                            {                             
                                0x005F,                   //Address 0x00-01 // Temp High Alarm, +95 oC
                                0x00E2,                   //Address 0x02-03 // Temp Low Alarm, -30 oC
                                0x0055,                   //Address 0x04-05 // Temp High Warning, +85 oC
                                0x00EC,                   //Address 0x06-07 // Temp Low Warning, -20 oC
                                0xCC8D,                   //Address 0x08-09 // Voltage High Alarm, 3.63 V
                                0x0474,                   //Address 0x0A-0B // Voltage Low Alarm, 2.97 V
                                0x5A87,                   //Address 0x0C-0D // Voltage High Warning, 3.465 V
                                0x767A,                   //Address 0x0E-0F // Voltage Low Warning, 3.135 V
                                0x50C3,                   //Address 0x10-11 // Bias High Alarm, 100 mA (50,000 -> 0xC350)
                                0xF401,                   //Address 0x12-13 // Bias Low Alarm, 1 mA
                                0xC8AF,                   //Address 0x14-15 // Bias High Warning, 90 mA (45,000 -> 0xAFC8)
                                0xE803,                   //Address 0x16-17 // Bias Low Warning, 2 mA
                                0x35FC,                   //Address 0x18-19 // TX Power High Alarm, +8.1 dBm
                                0x1027,                   //Address 0x1A-1B // TX Power Low Alarm, 0 dBm
                                0x77F6,                   //Address 0x1C-1D // TX Power High Warning, 8 dBm (0xF677)
                                0xE83D,                   //Address 0x1E-1F // TX Power Low Warning, 2 dBm
                                0xCB07,                   //Address 0x20-21 // RX Power High Alarm, - 7 dBm
                                0x1F00,                   //Address 0x22-23 // RX Power Low Alarm, - 25 dBm
                                0x3006,                   //Address 0x24-25 // RX Power High Warning, - 8 dBm
                                0x3200,                   //Address 0x26-27 // RX Power Low Warning, - 23 dBm
                                0x0000,  // 0xFF7F,                   //Address 0x28-29 // Optional Laser Temp High Alarm
                                0x0000,  // 0x0080,                   //Address 0x2A-2B // Optional Laser Temp Low Alarm
                                0x0000,  // 0xFF7F,                   //Address 0x2C-2D // Optional Laser Temp High Warning
                                0x0000,  // 0x0080,                   //Address 0x2E-2F // Optional Laser Temp Low Warning
                                0x0000,  // 0xFF7F,                   //Address 0x30-31 // Optional TEC Current High Alarm
                                0x0000,  // 0x0080,                   //Address 0x32-33 // Optional TEC Current Low Alarm
                                0x0000,  // 0xFF7F,                   //Address 0x34-35 // Optional TEC Current High Warning
                                0x0000,  // 0x0080,                   //Address 0x36-37 // Optional TEC Current Low Warning
                                0x0000,                   //Address 0x38-39  // Rx_PWR(4)
                                0x0000,                   //Address 0x3A-3C  // Rx_PWR(4)
                                0x0000,                   //Address 0x3C-3D  // Rx_PWR(3)
                                0x0000,                   //Address 0x3E-3F  // Rx_PWR(3)
                                0x0000,                   //Address 0x40-41  // Rx_PWR(2)
                                0x0000,                   //Address 0x42-43  // Rx_PWR(2)
                                0x803F,  // 0x0000,                   //Address 0x44-45  // Rx_PWR(1)
                                0x0000,                   //Address 0x46-47  // Rx_PWR(1)
                                0x0000,                   //Address 0x48-49  // Rx_PWR(0)
                                0x0000,                   //Address 0x4A-4C  // Rx_PWR(0)
                                0x0001,                   //Address 0x4C-4D  // Tx_I(Slope)
                                0x0000,                   //Address 0x4E-4F  // Tx_I(Offset)
                                0x0001,                   //Address 0x50-51  // Tx_PWR(Slope)
                                0x0000,                   //Address 0x52-53  // Tx_PWR(Offset))
                                0x0001,                   //Address 0x54-55  // TEMP(Slope)
                                0x0000,                   //Address 0x56-57  // TEMP(Offset))
                                0x0001,                   //Address 0x58-59  // VCC(Slope)
                                0x0000,                   //Address 0x5A-5B  // VCC(Offset))
                                0x0000,                   //Address 0x5C-5D
                                0x0000,                    //Address 0x5E-5F
                                0x0000,                   //Address 0x60-61
                                0x0000,                   //Address 0x62-63
                                0x0000,                   //Address 0x64-65
                                0x0000,                   //Address 0x66-67
                                0x0000,                   //Address 0x68-69
                                0x0000,                   //Address 0x6A-6C
                                0x0000,                   //Address 0x6C-6D
                                0x0000,                   //Address 0x6E-6F
                                0x0000,                   //Address 0x70-71
                                0x0000,                   //Address 0x72-73
                                0x0000,                   //Address 0x74-75
                                0x0000,                   //Address 0x76-77
                                0x0000,                   //Address 0x78-79
                                0x0000,                   //Address 0x7A-7C
                                0x0000,                   //Address 0x7C-7D
                                0x0000                    //Address 0x7E-7F
                            };


#pragma required = FlashDataA2_Const                            

#else

#pragma location = FLASH_A2_LOWER_CONST_START                         


const unsigned int FlashDataA2_Const[] =                        
                            {                             
                                0x005F,                   //Address 0x00-01 // Temp High Alarm, +95 oC
                                0x00E2,                   //Address 0x02-03 // Temp Low Alarm, -30 oC
                                0x0055,                   //Address 0x04-05 // Temp High Warning, +85 oC
                                0x00EC,                   //Address 0x06-07 // Temp Low Warning, -20 oC
                                0xCC8D,                   //Address 0x08-09 // Voltage High Alarm, 3.63 V
                                0x0474,                   //Address 0x0A-0B // Voltage Low Alarm, 2.97 V
                                0x5A87,                   //Address 0x0C-0D // Voltage High Warning, 3.465 V
                                0x767A,                   //Address 0x0E-0F // Voltage Low Warning, 3.135 V
                                0xC8AF,                   //Address 0x10-11 // Bias High Alarm, 90 mA
                                0xF401,                   //Address 0x12-13 // Bias Low Alarm, 1 mA
                                0x409C,                   //Address 0x14-15 // Bias High Warning, 80 mA
                                0xE803,                   //Address 0x16-17 // Bias Low Warning, 2 mA
                                0x78F6,                   //Address 0x18-19 // TX Power High Alarm, +8 dBm
                                0x9313,                   //Address 0x1A-1B // TX Power Low Alarm, -3 dBm
                                0xABDB,                   //Address 0x1C-1D // TX Power High Warning, +5 dBm (0x7B87) --> +7.5 dBm (0xDBAB)
                                0x2E31,                   //Address 0x1E-1F // TX Power Low Warning, 0 dBm
                                0xCB07,                   //Address 0x20-21 // RX Power High Alarm, - 7 dBm
                                0x1F00,                   //Address 0x22-23 // RX Power Low Alarm, - 25 dBm
                                0x3006,                   //Address 0x24-25 // RX Power High Warning, - 8 dBm
                                0x3200,                   //Address 0x26-27 // RX Power Low Warning, - 23 dBm
                                0x0000,  // 0xFF7F,                   //Address 0x28-29 // Optional Laser Temp High Alarm
                                0x0000,  // 0x0080,                   //Address 0x2A-2B // Optional Laser Temp Low Alarm
                                0x0000,  // 0xFF7F,                   //Address 0x2C-2D // Optional Laser Temp High Warning
                                0x0000,  // 0x0080,                   //Address 0x2E-2F // Optional Laser Temp Low Warning
                                0x0000,  // 0xFF7F,                   //Address 0x30-31 // Optional TEC Current High Alarm
                                0x0000,  // 0x0080,                   //Address 0x32-33 // Optional TEC Current Low Alarm
                                0x0000,  // 0xFF7F,                   //Address 0x34-35 // Optional TEC Current High Warning
                                0x0000,  // 0x0080,                   //Address 0x36-37 // Optional TEC Current Low Warning
                                0x0000,                   //Address 0x38-39  // Rx_PWR(4)
                                0x0000,                   //Address 0x3A-3C  // Rx_PWR(4)
                                0x0000,                   //Address 0x3C-3D  // Rx_PWR(3)
                                0x0000,                   //Address 0x3E-3F  // Rx_PWR(3)
                                0x0000,                   //Address 0x40-41  // Rx_PWR(2)
                                0x0000,                   //Address 0x42-43  // Rx_PWR(2)
                                0x803F,  // 0x0000,                   //Address 0x44-45  // Rx_PWR(1)
                                0x0000,                   //Address 0x46-47  // Rx_PWR(1)
                                0x0000,                   //Address 0x48-49  // Rx_PWR(0)
                                0x0000,                   //Address 0x4A-4C  // Rx_PWR(0)
                                0x0001,                   //Address 0x4C-4D  // Tx_I(Slope)
                                0x0000,                   //Address 0x4E-4F  // Tx_I(Offset)
                                0x0001,                   //Address 0x50-51  // Tx_PWR(Slope)
                                0x0000,                   //Address 0x52-53  // Tx_PWR(Offset))
                                0x0001,                   //Address 0x54-55  // TEMP(Slope)
                                0x0000,                   //Address 0x56-57  // TEMP(Offset))
                                0x0001,                   //Address 0x58-59  // VCC(Slope)
                                0x0000,                   //Address 0x5A-5B  // VCC(Offset))
                                0x0000,                   //Address 0x5C-5D
                                0x0000,                    //Address 0x5E-5F
                                0x0000,                   //Address 0x60-61
                                0x0000,                   //Address 0x62-63
                                0x0000,                   //Address 0x64-65
                                0x0000,                   //Address 0x66-67
                                0x0000,                   //Address 0x68-69
                                0x0000,                   //Address 0x6A-6C
                                0x0000,                   //Address 0x6C-6D
                                0x0000,                   //Address 0x6E-6F
                                0x0000,                   //Address 0x70-71
                                0x0000,                   //Address 0x72-73
                                0x0000,                   //Address 0x74-75
                                0x0000,                   //Address 0x76-77
                                0x0000,                   //Address 0x78-79
                                0x0000,                   //Address 0x7A-7C
                                0x0000,                   //Address 0x7C-7D
                                0x0000                    //Address 0x7E-7F
                            };


#pragma required = FlashDataA2_Const                            
     
#endif
                    
#else

#pragma location = FLASH_A2_LOWER_CONST_START                         
const unsigned int FlashDataA2_Const[] =                        
                            {                             
                                0xFF7F,                   //Address 0x00-01 // Temp High Alarm
                                0x0080,                   //Address 0x02-03 // Temp Low Alarm
                                0xFF7F,                   //Address 0x04-05 // Temp High Warning
                                0x0080,                   //Address 0x06-07 // Temp Low Warning
                                0xFFFF,                   //Address 0x08-09 // Voltage High Alarm
                                0x0000,                   //Address 0x0A-0B // Voltage High Alarm
                                0xFFFF,                   //Address 0x0C-0D // Voltage High Warning
                                0x0000,                   //Address 0x0E-0F // Voltage High Warning
                                0xFFFF,                   //Address 0x10-11 // Bias High Alarm
                                0x0000,                   //Address 0x12-13 // Bias High Alarm
                                0xFFFF,                   //Address 0x14-15 // Bias High Warning
                                0x0000,                   //Address 0x16-17 // Bias High Warning
                                0xFFFF,                   //Address 0x18-19 // TX Power High Alarm
                                0x0000,                   //Address 0x1A-1B // TX Power High Alarm
                                0xFFFF,                   //Address 0x1C-1D // TX Power High Warning
                                0x0000,                   //Address 0x1E-1F // TX Power High Warning
                                0xFFFF,                   //Address 0x20-21 // RX Power High Alarm
                                0x0000,                   //Address 0x22-23 // RX Power High Alarm
                                0xFFFF,                   //Address 0x24-25 // RX Power High Warning
                                0x0000,                   //Address 0x26-27 // RX Power High Warning
                                0x0000,  // 0xFF7F,                   //Address 0x28-29 // Optional Laser Temp High Alarm
                                0x0000,  // 0x0080,                   //Address 0x2A-2B // Optional Laser Temp High Alarm
                                0x0000,  // 0xFF7F,                   //Address 0x2C-2D // Optional Laser Temp High Alarm
                                0x0000,  // 0x0080,                   //Address 0x2E-2F // Optional Laser Temp High Alarm
                                0x0000,  // 0xFF7F,                   //Address 0x30-31 // Optional TEC Current High Alarm
                                0x0000,  // 0x0080,                   //Address 0x32-33 // Optional TEC Current High Alarm
                                0x0000,  // 0xFF7F,                   //Address 0x34-35 // Optional TEC Current High Alarm
                                0x0000,  // 0x0080,                   //Address 0x36-37 // Optional TEC Current High Alarm
                                0x0000,                   //Address 0x38-39  // Rx_PWR(4)
                                0x0000,                   //Address 0x3A-3C  // Rx_PWR(4)
                                0x0000,                   //Address 0x3C-3D  // Rx_PWR(3)
                                0x0000,                   //Address 0x3E-3F  // Rx_PWR(3)
                                0x0000,                   //Address 0x40-41  // Rx_PWR(2)
                                0x0000,                   //Address 0x42-43  // Rx_PWR(2)
                                0x803F,  // 0x0000,                   //Address 0x44-45  // Rx_PWR(1)
                                0x0000,                   //Address 0x46-47  // Rx_PWR(1)
                                0x0000,                   //Address 0x48-49  // Rx_PWR(0)
                                0x0000,                   //Address 0x4A-4C  // Rx_PWR(0)
                                0x0001,                   //Address 0x4C-4D  // Tx_I(Slope)
                                0x0000,                   //Address 0x4E-4F  // Tx_I(Offset)
                                0x0001,                   //Address 0x50-51  // Tx_PWR(Slope)
                                0x0000,                   //Address 0x52-53  // Tx_PWR(Offset))
                                0x0001,                   //Address 0x54-55  // TEMP(Slope)
                                0x0000,                   //Address 0x56-57  // TEMP(Offset))
                                0x0001,                   //Address 0x58-59  // VCC(Slope)
                                0x0000,                   //Address 0x5A-5B  // VCC(Offset))
                                0x0000,                   //Address 0x5C-5D
                                0x0000,                    //Address 0x5E-5F
                                0x0000,                   //Address 0x60-61
                                0x0000,                   //Address 0x62-63
                                0x0000,                   //Address 0x64-65
                                0x0000,                   //Address 0x66-67
                                0x0000,                   //Address 0x68-69
                                0x0000,                   //Address 0x6A-6C
                                0x0000,                   //Address 0x6C-6D
                                0x0000,                   //Address 0x6E-6F
                                0x0000,                   //Address 0x70-71
                                0x0000,                   //Address 0x72-73
                                0x0000,                   //Address 0x74-75
                                0x0000,                   //Address 0x76-77
                                0x0000,                   //Address 0x78-79
                                0x0000,                   //Address 0x7A-7C
                                0x0000,                   //Address 0x7C-7D
                                0x0000                    //Address 0x7E-7F
                            };                            
#pragma required = FlashDataA2_Const                            
                                                          
                   
#endif
                                                          
#if 0

#pragma location = FLASH_PAGE80H_PAGE81H_START            
const unsigned char FlashDataPage80h81h[] =               
                            {                             
//Page 80h MAX24016                                       
                                0x00,                     //unsigned char PAGE80H_RESERVED0;                                              //Address 0x80       
                                0x14,                     //unsigned char TXCTRL1;                                                        //Address 0x81     
                                0x21,                     //unsigned char TXCTRL2;                                                        //Address 0x82     
                                0xD2,                     //unsigned char TXCTRL3;                                                        //Address 0x83     
                                0x3F,                     //unsigned char TXCTRL4;                                                        //Address 0x84     
                                0x44,                     //unsigned char TXCTRL5;                                                        //Address 0x85     
                                0x02,                     //unsigned char TXCTRL6;                                                        //Address 0x86     
                                0x5E,                     //unsigned char TXCTRL7;                                                        //Address 0x87     
                                0x06,                     //unsigned char TXCTRL8;                                                        //Address 0x88     
                                0x00,                     //unsigned char SET_MOD0;                                                       //Address 0x89     
                                0x2C,                     //unsigned char SET_MOD1;                                                       //Address 0x8A     
                                0xFF,                     //unsigned char MODMAX;                                                         //Address 0x8B     
                                0x00,0x00,                //unsigned char PAGE80H_RESERVED1[2];                                           //Address 0x8C-0x8D
                                0x14,                     //unsigned char APCCTRL1;                                                       //Address 0x8E     
                                0x62,                     //unsigned char APCCTRL2;                                                       //Address 0x8F     
                                0x00,                     //unsigned char SET_APC0;                                                       //Address 0x90     
                                0x00,                     //unsigned char SET_APC1;                                                       //Address 0x91     
                                0x00,                     //unsigned char SET_BIAS0;                                                      //Address 0x92     
                                0x00,                     //unsigned char SET_BIAS1;                                                      //Address 0x93     
                                0xFF,                     //unsigned char BIASMAX;                                                        //Address 0x94     
                                0xFF,                     //unsigned char MPDMAX;                                                         //Address 0x95     
                                0x00,0x00,                //unsigned char PAGE3_RESERVED2[8];                                             //Address 0x96-0x9D  
                                0x00,0x00,                
                                0x00,0x00,                
                                0x00,0x00,                
                                0x45,                     //unsigned char LDOCTRL;                                                        //Address 0x9E     
                                0x00,0x00,                //unsigned char PAGE80H_RESERVED3[2];                                           //Address 0x9F-0xA0
                                0xF0,                     //unsigned char RXCTRL1;                                                        //Address 0xA1     
                                0x05,                     //unsigned char RXCTRL2;                                                        //Address 0xA2     
                                0x0A,                     //unsigned char RXCTRL3;                                                        //Address 0xA3     
                                0x00,                     //unsigned char RXCTRL4;                                                        //Address 0xA4     
                                0x00,                     //unsigned char PAGE80H_RESERVED4;                                              //Address 0xA5     
                                0xD8,                     //unsigned char RXLOS1;                                                         //Address 0xA6     
                                0x0A,                     //unsigned char RXLOS2;                                                         //Address 0xA7     
                                0x00,                     //unsigned char RXLOS3;                                                         //Address 0xA8     
                                0x06,                     //unsigned char RXLOS4;                                                         //Address 0xA9     
                                0x00,                     //unsigned char PAGE80H_RESERVED5;                                              //Address 0xAA     
                                0x90,                     //unsigned char FAULTCTRL;                                                      //Address 0xAB     
                                0xFF,                     //unsigned char FAULTMASK1;                                                     //Address 0xAC     
                                0x7E,                     //unsigned char FAULTMASK2;                                                     //Address 0xAD     
                                0x00,                     //unsigned char PAGE80H_RESERVED6[13];                                          //Address 0xAE-0xBA 
                                0x00,0x00,                
                                0x00,0x00,                
                                0x00,0x00,                
                                0x00,0x00,                
                                0x00,0x00,                
                                0x00,0x00,                                            
                                0x04,                     //unsigned char TOPCTRL;                                                        //Address 0xBB     
                                0x00,                     //unsigned char PAGE80H_RESERVED7;                                              //Address 0xBC     
                                0x00,                     //unsigned char EVENT1;                                                         //Address 0xBD     
                                0x00,                     //unsigned char EVENT2;                                                         //Address 0xBE     
                                0x00,                     //unsigned char PAGE80H_RESERVED8;                                              //Address 0xBF     
                                0x00,                     //unsigned char PINSTAT;                                                        //Address 0xC0     
                                0x00,                     //unsigned char TOPSTAT;                                                        //Address 0xC1     
                                0x00,                     //unsigned char FAULTSTAT1;                                                     //Address 0xC2     
                                0x00,                     //unsigned char FAULTSTAT2;                                                     //Address 0xC3     
                                0x00,                     //unsigned char TXSTAT;                                                         //Address 0xC4     
                                0x00,                     //unsigned char RXSTAT;                                                         //Address 0xC5     
                                0x00,0x00,                //unsigned char PAGE80H_RESERVED9[18];                                          //Address 0xC6-xD7 
                                0x00,0x00,                
                                0x00,0x00,                
                                0x00,0x00,                
                                0x00,0x00,                
                                0x00,0x00,                
                                0x00,0x00,                
                                0x00,0x00,                
                                0x00,0x00,                                                                                                             
                                0x00,                     //unsigned char DDMSTAT15;                                                      //Address 0xD8     
                                0x00,                     //unsigned char DDMSTAT16;                                                      //Address 0xD9     
                                0x00,                     //unsigned char DDMSTAT17;                                                      //Address 0xDA     
                                0x00,                     //unsigned char DDMSTAT18;                                                      //Address 0xDB     
                                0x00,0x00,                //unsigned char PAGE80H_RESERVED10[20];                                         //Address 0xDC-0xEF
                                0x00,0x00,                
                                0x00,0x00,                
                                0x00,0x00,                
                                0x00,0x00,                
                                0x00,0x00,                
                                0x00,0x00,                
                                0x00,0x00,                
                                0x00,0x00,                                               
                                0x00,0x00,                //unsigned char RXPU;                                                           //Address 0xF0     
                                0x00,                     //unsigned char PAGE80H_RESERVED11[15];                                         //Address 0xF1-0xFF 
                                0x00,0x00,                
                                0x00,0x00,                
                                0x00,0x00,                
                                0x00,0x00,                
                                0x00,0x00,                
                                0x00,0x00,                
                                0x00,0x00,                                                                                                     
//Page 81h                                                
                                0x00,0x00,                //Address 0x80-81
                                0x00,0x00,                //Address 0x82-83
                                0x00,0x00,                //Address 0x84-85
                                0x00,0x00,                //Address 0x86-87
                                0x00,0x00,                //Address 0x88-89
                                0x00,0x00,                //Address 0x8A-8C
                                0x00,0x00,                //Address 0x8C-8D
                                0x00,0x00,                //Address 0x8E-8F
                                0x00,0x00,                //Address 0x90-91
                                0x00,0x00,                //Address 0x92-93
                                0x00,0x00,                //Address 0x94-95
                                0x00,0x00,                //Address 0x96-97
                                0x00,0x00,                //Address 0x98-99
                                0x00,0x00,                //Address 0x9A-9C
                                0x00,0x00,                //Address 0x9C-9D
                                0x00,0x00,                //Address 0x9E-9F
                                0x00,0x00,                //Address 0xA0-A1
                                0x00,0x00,                //Address 0xA2-A3
                                0x00,0x00,                //Address 0xA4-A5
                                0x00,0x00,                //Address 0xA6-A7
                                0x00,0x00,                //Address 0xA8-A9
                                0x00,0x00,                //Address 0xAA-AC
                                0x00,0x00,                //Address 0xAC-AD
                                0x00,0x00,                //Address 0xAE-AF
                                0x00,0x00,                //Address 0xA0-A1
                                0x00,0x00,                //Address 0xA2-A3
                                0x00,0x00,                //Address 0xA4-A5
                                0x00,0x00,                //Address 0xA6-A7
                                0x00,0x00,                //Address 0xA8-A9
                                0x00,0x00,                //Address 0xAA-AC
                                0x00,0x00,                //Address 0xAC-AD
                                0x00,0x00,                //Address 0xAE-AF
                                0x00,0x00,                //Address 0xB0-B1
                                0x00,0x00,                //Address 0xB2-B3
                                0x00,0x00,                //Address 0xB4-B5
                                0x00,0x00,                //Address 0xB6-B7
                                0x00,0x00,                //Address 0xB8-B9
                                0x00,0x00,                //Address 0xBA-BC
                                0x00,0x00,                //Address 0xBC-BD
                                0x00,0x00,                //Address 0xBE-BF
                                0x00,0x00,                //Address 0xC0-C1
                                0x00,0x00,                //Address 0xC2-C3
                                0x00,0x00,                //Address 0xC4-C5
                                0x00,0x00,                //Address 0xC6-C7
                                0x00,0x00,                //Address 0xC8-C9
                                0x00,0x00,                //Address 0xCA-CB
                                0x00,0x00,                //Address 0xCC-CD
                                0x00,0x00,                //Address 0xCE-CF
                                0x00,0x00,                //Address 0xD0-D1
                                0x00,0x00,                //Address 0xD2-D3
                                0x00,0x00,                //Address 0xD4-D5
                                0x00,0x00,                //Address 0xD6-D7
                                0x00,0x00,                //Address 0xD8-D9
                                0x00,0x00,                //Address 0xDA-DB
                                0x00,0x00,                //Address 0xDC-DC
                                0x00,0x00,                //Address 0xDE-DF
                                0x00,0x00,                //Address 0xE0-E1
                                0x00,0x00,                //Address 0xE2-E3
                                0x00,0x00,                //Address 0xE4-E5
                                0x00,0x00,                //Address 0xE6-E7
                                0x00,0x00,                //Address 0xE8-E9
                                0x00,0x00,                //Address 0xEA-EB
                                0x00,0x00,                //Address 0xEC-ED
                                0x00,0x00,                //Address 0xEE-EF
                                0x00,0x00,                //Address 0xF0-F1
                                0x00,0x00,                //Address 0xF2-F3
                                0x00,0x00,                //Address 0xF4-F5
                                0x00,0x00,                //Address 0xF6-F7
                                0x00,0x00,                //Address 0xF8-F9
                                0x00,0x00,                //Address 0xFA-FB
                                0x00,0x00,                //Address 0xFC-FD
                                0x00,0x00                 //Address 0xFE-FF
                            };                            
#pragma required = FlashDataPage80h81h                    
                                                          
                                                          
//Table 88h,89h                                           
#pragma location = FLASH_PAGE88H_PAGE89H_START            
const unsigned char FlashDataPage88h89h[] =               
                            {                             
                                                          
                                0x00,0x00,                //Address 0x00-01
                                0x00,0x00,                //Address 0x02-03
                                0x00,0x00,                //Address 0x04-05
                                0x00,0x00,                //Address 0x06-07
                                0x00,0x00,                //Address 0x08-09
                                0x00,0x00,                //Address 0x0A-0B
                                0x00,0x00,                //Address 0x0C-0D
                                0x00,0x00,                //Address 0x0E-0F
                                0x00,0x00,                //Address 0x10-11
                                0x00,0x00,                //Address 0x12-13
                                0x00,0x00,                //Address 0x14-15
                                0x00,0x00,                //Address 0x16-17
                                0x00,0x00,                //Address 0x18-19
                                0x00,0x00,                //Address 0x1A-1B
                                0x00,0x00,                //Address 0x1C-1D
                                0x00,0x00,                //Address 0x1E-1F
                                0x00,0x00,                //Address 0x20-21
                                0x00,0x00,                //Address 0x22-23
                                0x00,0x00,                //Address 0x24-25
                                0x00,0x00,                //Address 0x26-27
                                0x00,0x00,                //Address 0x28-29
                                0x00,0x00,                //Address 0x2A-2B
                                0x00,0x00,                //Address 0x2C-2D
                                0x00,0x00,                //Address 0x2E-2F
                                0x00,0x00,                //Address 0x30-31
                                0x00,0x00,                //Address 0x32-33
                                0x00,0x00,                //Address 0x34-35
                                0x00,0x00,                //Address 0x36-37
                                0x00,0x00,                //Address 0x38-39
                                0x00,0x00,                //Address 0x3A-3C
                                0x00,0x00,                //Address 0x3C-3D
                                0x00,0x00,                //Address 0x3E-3F
                                0x00,0x00,                //Address 0x40-41
                                0x00,0x00,                //Address 0x42-43
                                0x00,0x00,                //Address 0x44-45
                                0x00,0x00,                //Address 0x46-47
                                0x00,0x00,                //Address 0x48-49
                                0x00,0x00,                //Address 0x4A-4C
                                0x00,0x00,                //Address 0x4C-4D
                                0x00,0x00,                //Address 0x4E-4F
                                0x00,0x00,                //Address 0x50-51
                                0x00,0x00,                //Address 0x52-53
                                0x00,0x00,                //Address 0x54-55
                                0x00,0x00,                //Address 0x56-57
                                0x00,0x00,                //Address 0x58-59
                                0x00,0x00,                //Address 0x5A-5C
                                0x00,0x00,                //Address 0x5C-5D
                                0x00,0x00,                //Address 0x5E-5F
                                0x00,0x00,                //Address 0x60-61
                                0x00,0x00,                //Address 0x62-63
                                0x00,0x00,                //Address 0x64-65
                                0x00,0x00,                //Address 0x66-67
                                0x00,0x00,                //Address 0x68-69
                                0x00,0x00,                //Address 0x6A-6C
                                0x00,0x00,                //Address 0x6C-6D
                                0x00,0x00,                //Address 0x6E-6F
                                0x00,0x00,                //Address 0x70-71
                                0x00,0x00,                //Address 0x72-73
                                0x00,0x00,                //Address 0x74-75
                                0x00,0x00,                //Address 0x76-77
                                0x00,0x00,                //Address 0x78-79
                                0x00,0x00,                //Address 0x7A-7C
                                0x00,0x00,                //Address 0x7C-7D
                                0x00,0x00,                //Address 0x7E-7F
//Page 81h                                                
                                0x00,0x00,                //Address 0x80-81
                                0x00,0x00,                //Address 0x82-83
                                0x00,0x00,                //Address 0x84-85
                                0x00,0x00,                //Address 0x86-87
                                0x00,0x00,                //Address 0x88-89
                                0x00,0x00,                //Address 0x8A-8C
                                0x00,0x00,                //Address 0x8C-8D
                                0x00,0x00,                //Address 0x8E-8F
                                0x00,0x00,                //Address 0x90-91
                                0x00,0x00,                //Address 0x92-93
                                0x00,0x00,                //Address 0x94-95
                                0x00,0x00,                //Address 0x96-97
                                0x00,0x00,                //Address 0x98-99
                                0x00,0x00,                //Address 0x9A-9C
                                0x00,0x00,                //Address 0x9C-9D
                                0x00,0x00,                //Address 0x9E-9F
                                
#ifdef DCDC_BIASING                                                          
                                0x00,0x00,                //Address 0xA0-A1
                                0x00,0x00,                //Address 0xA2-A3
                                0x00,0x00,                //Address 0xA4-A5
                                0x00,0x00,                //Address 0xA6-A7
                                0x00,0x00,                //Address 0xA8-A9
                                0x00,0x00,                //Address 0xAA-AC
                                0x00,0x00,                //Address 0xAC-AD
                                0x00,0x00,                //Address 0xAE-AF
                                0x00,0x00,                //Address 0xB0-B1
                                0x00,0x00,                //Address 0xB2-B3
                                0x00,0x00,                //Address 0xB4-B5
                                0x00,0x00,                //Address 0xB6-B7
                                0x00,0x00,                //Address 0xB8-B9
                                0x00,0x00,                //Address 0xBA-BC
                                0x00,0x00,                //Address 0xBC-BD
                                0x00,0x00,                //Address 0xBE-BF
                                0x00,0x00,                //Address 0xC0-C1
                                0x00,0x00,                //Address 0xC2-C3
                                0x00,0x00,                //Address 0xC4-C5
                                0x00,0x00,                //Address 0xC6-C7
                                0x00,0x00,                //Address 0xC8-C9
                                0x00,0x00,                //Address 0xCA-CB
                                0x00,0x00,                //Address 0xCC-CD
                                0x00,0x00,                //Address 0xCE-CF
                                0x00,0x00,                //Address 0xD0-D1
                                0x00,0x00,                //Address 0xD2-D3
                                0x00,0x00,                //Address 0xD4-D5
                                0x00,0x00,                //Address 0xD6-D7
                                0x00,0x00,                //Address 0xD8-D9
                                0x00,0x00,                //Address 0xDA-DB
                                0x00,0x00,                //Address 0xDC-DC
                                0x00,0x00,                //Address 0xDE-DF
                                0x00,0x00,                //Address 0xE0-E1
                                0x00,0x00,                //Address 0xE2-E3
                                0x00,0x00,                //Address 0xE4-E5
                                0x00,0x00,                //Address 0xE6-E7
                                0x00,0x00,                //Address 0xE8-E9
                                0x00,0x00,                //Address 0xEA-EB
                                0x00,0x00,                //Address 0xEC-ED
                                0x00,0x00,                //Address 0xEE-EF
                                0x00,0x00,                //Address 0xF0-F1
                                0x00,0x00,                //Address 0xF2-F3
                                0x00,0x00,                //Address 0xF4-F5
                                0x00,0x00,                //Address 0xF6-F7
                                0x00,0x00,                //Address 0xF8-F9
                                0x00,0x00,                //Address 0xFA-FB
                                0x00,0x00,                //Address 0xFC-FD
                                0x00,0x00                 //Address 0xFE-FF  
                                                          
                                                          
#else                                                     
                                0x00,0x00,                //Address 0xA0-A1
                                0x00,0x00,                //Address 0xA2-A3
                                0x00,0x00,                //Address 0xA4-A5
                                0x00,0x00,                //Address 0xA6-A7
                                0x00,0x00,                //Address 0xA8-A9
                                0x00,0x00,                //Address 0xAA-AC
                                0x00,0x00,                //Address 0xAC-AD
                                0x00,0x00,                //Address 0xAE-AF
                                0x00,0x00,                //Address 0xB0-B1
                                0x00,0x00,                //Address 0xB2-B3
                                0x00,0x00,                //Address 0xB4-B5
                                0x00,0x00,                //Address 0xB6-B7
                                0x00,0x00,                //Address 0xB8-B9
                                0x00,0x00,                //Address 0xBA-BC
                                0x00,0x00,                //Address 0xBC-BD
                                0x00,0x00,                //Address 0xBE-BF
                                0x00,0x00,                //Address 0xC0-C1
                                0x00,0x00,                //Address 0xC2-C3
                                0x00,0x00,                //Address 0xC4-C5
                                0x00,0x00,                //Address 0xC6-C7
                                0x00,0x00,                //Address 0xC8-C9
                                0x00,0x00,                //Address 0xCA-CB
                                0x00,0x00,                //Address 0xCC-CD
                                0x00,0x00,                //Address 0xCE-CF
                                0x00,0x00,                //Address 0xD0-D1
                                0x00,0x00,                //Address 0xD2-D3
                                0x00,0x00,                //Address 0xD4-D5
                                0x00,0x00,                //Address 0xD6-D7
                                0x00,0x00,                //Address 0xD8-D9
                                0x00,0x00,                //Address 0xDA-DB
                                0x00,0x00,                //Address 0xDC-DC
                                0x00,0x00,                //Address 0xDE-DF
                                0x00,0x00,                //Address 0xE0-E1
                                0x00,0x00,                //Address 0xE2-E3
                                0x00,0x00,                //Address 0xE4-E5
                                0x00,0x00,                //Address 0xE6-E7
                                0x00,0x00,                //Address 0xE8-E9
                                0x00,0x00,                //Address 0xEA-EB
                                0x00,0x00,                //Address 0xEC-ED
                                0x00,0x00,                //Address 0xEE-EF
                                0x00,0x00,                //Address 0xF0-F1
                                0x00,0x00,                //Address 0xF2-F3
                                0x00,0x00,                //Address 0xF4-F5
                                0x00,0x00,                //Address 0xF6-F7
                                0x00,0x00,                //Address 0xF8-F9
                                0x00,0x00,                //Address 0xFA-FB
                                0x00,0x00,                //Address 0xFC-FD
                                0x00,0x00                 //Address 0xFE-FF                            
#endif                                                    
                                                          
                            };                            
#pragma required = FlashDataPage88h89h                    
                                                          
                                                          
                                                          
//Table 8Ah,8Bh                                           
#pragma location = FLASH_PAGE8AH_PAGE8BH_START            
const unsigned char FlashDataPage8Ah8Bh[] =               
                            {                             
                                                          
                                0x00,0x00,                //Address 0x00-01
                                0x00,0x00,                //Address 0x02-03
                                0x00,0x00,                //Address 0x04-05
                                0x00,0x00,                //Address 0x06-07
                                0x00,0x00,                //Address 0x08-09
                                0x00,0x00,                //Address 0x0A-0B
                                0x00,0x00,                //Address 0x0C-0D
                                0x00,0x00,                //Address 0x0E-0F
                                0x00,0x00,                //Address 0x10-11
                                0x00,0x00,                //Address 0x12-13
                                0x00,0x00,                //Address 0x14-15
                                0x00,0x00,                //Address 0x16-17
                                0x00,0x00,                //Address 0x18-19
                                0x00,0x00,                //Address 0x1A-1B
                                0x00,0x00,                //Address 0x1C-1D
                                0x00,0x00,                //Address 0x1E-1F
                                0x00,0x00,                //Address 0x20-21
                                0x00,0x00,                //Address 0x22-23
                                0x00,0x00,                //Address 0x24-25
                                0x00,0x00,                //Address 0x26-27
                                0x00,0x00,                //Address 0x28-29
                                0x00,0x00,                //Address 0x2A-2B
                                0x00,0x00,                //Address 0x2C-2D
                                0x00,0x00,                //Address 0x2E-2F
                                0x00,0x00,                //Address 0x30-31
                                0x00,0x00,                //Address 0x32-33
                                0x00,0x00,                //Address 0x34-35
                                0x00,0x00,                //Address 0x36-37
                                0x00,0x00,                //Address 0x38-39
                                0x00,0x00,                //Address 0x3A-3C
                                0x00,0x00,                //Address 0x3C-3D
                                0x00,0x00,                //Address 0x3E-3F
                                0x00,0x00,                //Address 0x40-41
                                0x00,0x00,                //Address 0x42-43
                                0x00,0x00,                //Address 0x44-45
                                0x00,0x00,                //Address 0x46-47
                                0x00,0x00,                //Address 0x48-49
                                0x00,0x00,                //Address 0x4A-4C
                                0x00,0x00,                //Address 0x4C-4D
                                0x00,0x00,                //Address 0x4E-4F
                                0x00,0x00,                //Address 0x50-51
                                0x00,0x00,                //Address 0x52-53
                                0x00,0x00,                //Address 0x54-55
                                0x00,0x00,                //Address 0x56-57
                                0x00,0x00,                //Address 0x58-59
                                0x00,0x00,                //Address 0x5A-5C
                                0x00,0x00,                //Address 0x5C-5D
                                0x00,0x00,                //Address 0x5E-5F
                                0x00,0x00,                //Address 0x60-61
                                0x00,0x00,                //Address 0x62-63
                                0x00,0x00,                //Address 0x64-65
                                0x00,0x00,                //Address 0x66-67
                                0x00,0x00,                //Address 0x68-69
                                0x00,0x00,                //Address 0x6A-6C
                                0x00,0x00,                //Address 0x6C-6D
                                0x00,0x00,                //Address 0x6E-6F
                                0x00,0x00,                //Address 0x70-71
                                0x00,0x00,                //Address 0x72-73
                                0x00,0x00,                //Address 0x74-75
                                0x00,0x00,                //Address 0x76-77
                                0x00,0x00,                //Address 0x78-79
                                0x00,0x00,                //Address 0x7A-7C
                                0x00,0x00,                //Address 0x7C-7D
                                0x00,0x00,                //Address 0x7E-7F
//Page 8Bh                                                
                                0x00,0x00,                //Address 0x80-81
                                0x00,0x00,                //Address 0x82-83
                                0x00,0x00,                //Address 0x84-85
                                0x00,0x00,                //Address 0x86-87
                                0x00,0x00,                //Address 0x88-89
                                0x00,0x00,                //Address 0x8A-8C
                                0x00,0x00,                //Address 0x8C-8D
                                0x00,0x00,                //Address 0x8E-8F
                                0x00,0x00,                //Address 0x90-91
                                0x00,0x00,                //Address 0x92-93
                                0x00,0x00,                //Address 0x94-95
                                0x00,0x00,                //Address 0x96-97
                                0x00,0x00,                //Address 0x98-99
                                0x00,0x00,                //Address 0x9A-9C
                                0x00,0x00,                //Address 0x9C-9D
                                0x00,0x00,                //Address 0x9E-9F
                                                          
                                                          
                                0x00,0x00,                //Address 0xA0-A1
                                0x00,0x00,                //Address 0xA2-A3
                                0x00,0x00,                //Address 0xA4-A5
                                0x00,0x00,                //Address 0xA6-A7
                                0x00,0x00,                //Address 0xA8-A9
                                0x00,0x00,                //Address 0xAA-AC
                                0x00,0x00,                //Address 0xAC-AD
                                0x00,0x00,                //Address 0xAE-AF
                                0x00,0x00,                //Address 0xB0-B1
                                0x00,0x00,                //Address 0xB2-B3
                                0x00,0x00,                //Address 0xB4-B5
                                0x00,0x00,                //Address 0xB6-B7
                                0x00,0x00,                //Address 0xB8-B9
                                0x00,0x00,                //Address 0xBA-BC
                                0x00,0x00,                //Address 0xBC-BD
                                0x00,0x00,                //Address 0xBE-BF
                                0x00,0x00,                //Address 0xC0-C1
                                0x00,0x00,                //Address 0xC2-C3
                                0x00,0x00,                //Address 0xC4-C5
                                0x00,0x00,                //Address 0xC6-C7
                                0x00,0x00,                //Address 0xC8-C9
                                0x00,0x00,                //Address 0xCA-CB
                                0x00,0x00,                //Address 0xCC-CD
                                0x00,0x00,                //Address 0xCE-CF
                                0x00,0x00,                //Address 0xD0-D1
                                0x00,0x00,                //Address 0xD2-D3
                                0x00,0x00,                //Address 0xD4-D5
                                0x00,0x00,                //Address 0xD6-D7
                                0x00,0x00,                //Address 0xD8-D9
                                0x00,0x00,                //Address 0xDA-DB
                                0x00,0x00,                //Address 0xDC-DC
                                0x00,0x00,                //Address 0xDE-DF
                                0x00,0x00,                //Address 0xE0-E1
                                0x00,0x00,                //Address 0xE2-E3
                                0x00,0x00,                //Address 0xE4-E5
                                0x00,0x00,                //Address 0xE6-E7
                                0x00,0x00,                //Address 0xE8-E9
                                0x00,0x00,                //Address 0xEA-EB
                                0x00,0x00,                //Address 0xEC-ED
                                0x00,0x00,                //Address 0xEE-EF
                                0x00,0x00,                //Address 0xF0-F1
                                0x00,0x00,                //Address 0xF2-F3
                                0x00,0x00,                //Address 0xF4-F5
                                0x00,0x00,                //Address 0xF6-F7
                                0x00,0x00,                //Address 0xF8-F9
                                0x00,0x00,                //Address 0xFA-FB
                                0x00,0x00,                //Address 0xFC-FD
                                0x00,0x00                 //Address 0xFE-FF     
                                                          
                            };                            
#pragma required = FlashDataPage8Ah8Bh                    
                                                          
                                                          
//Page 90h                                                
#pragma location = FLASH_PAGE90H_START                    
const unsigned int FlashDataPage90h[] =                   
                            {                             
                                                          
                                0x0001,                   //unsigned int  TEMP_SLOPE;                                                     //Address 0x80-0x81 
                                0x0000,                   //signed int    TEMP_OFFSET;                                                    //Address 0x82-0x83
                                0x0001,                   //unsigned int  VCC_SLOPE;                                                      //Address 0x84-0x85
                                0x0000,                   //signed int    VCC_OFFSET;                                                     //Address 0x86-0x87
                                0x0001,                   //unsigned int  TX_BIAS_SLOPE;                                                  //Address 0x88-0x89
                                0x0000,                   //signed int    TX_BIAS_OFFSET;                                                 //Address 0x8A-0x8B
                                0x0001,                   //unsigned int  TX_POWER_SLOPE;                                                 //Address 0x8C-0x8D
                                0x0000,                   //signed int    TX_POWER_OFFSET;                                                //Address 0x8E-0x8F
                                0x0001,                   //unsigned int  RX_POWER_HP_SLOPE;                                              //Address 0x90-0x91
                                0x0000,                   //signed int    RX_POWER_HP_OFFSET;                                             //Address 0x92-0x93
                                0x0001,                   //unsigned int  RX_POWER_LP_SLOPE;                                              //Address 0x94-0x95
                                0x0000,                   //signed int    RX_POWER_LP_OFFSET;                                             //Address 0x96-0x97
                                0x0001,                   //unsigned int  LASER_TEMP_SLOPE;                                               //Address 0x98-0x99
                                0x0000,                   //signed int    LASER_TEMP_OFFSET;                                              //Address 0x9A-0x9B
                                0x0001,                   //unsigned int  TEC_CURRENT_SLOPE;                                              //Address 0x9C-0x9D
                                0x0000,                   //signed int    TEC_CURRENT_OFFSET;                                             //Address 0x9E-0x9F                              
                                0x0000,                   //unsigned int  CONTROL;                                                        //Address 0xA0-0xA1                          
                                0x0000,                   //unsigned int  MOD;                                                            //Address 0xA2-0xA3     
                                0x0000,                   //unsigned int  BIAS;                                                           //Address 0xA4-0xA4     
                                0x0000,                   //unsigned int  APD;                                                            //Address 0xA6-0xA7   
                                0x0000,                   //unsigned int  MODULE_CONTROL1;                                                //Address 0xA8-0xA9  
                                0x0600,                   //unsigned int  RXLOS_ASSERT_TH;                                                //Address 0xAA-0xAB 
                                0x0C00,                   //unsigned int  RXLOS_DEASSERT_TH;                                              //Address 0xAC-0xAD
                                0x0000,                     
                                0x0D00,                   //unsigned int  IDAC1_CONFIG;                                                   //Address 0xB0-0xB1
                                0x0000,                   //unsigned int  IDAC1_OUTPUT;                                                   //Address 0xB2-0xB3
                                0x0007,                   //unsigned int  IDAC1_MAXOUTPUT;                                                //Address 0xB4-0xB5
                                0x0000,                   //unsigned int  PAGE90H_RESERVED3;                                              //Address 0xB4-0xB7
                                0xDF33,                   //unsigned int  SH_CONFIG;                                                      //Address 0xB8-0xB9
                                0x0020,                   //unsigned int  HIGH_LOW_SWITCH_ADC;                                            //Address 0xBA-0xBB   
                                0x0000,0x0000,            //unsigned int  PAGE90H_RESERVED4[2];                                           //Address 0xBC-0xBF   
                                0x4080,                   //unsigned int  DS_DAC5_CONFIG;                                                 //Address 0xC0-0xC1
                                0x0019,                   //unsigned int  DS_DAC5_DPDUTY;                                                 //Address 0xC2-0xC3
                                0xFFFF,                   //unsigned int  DS_DAC5_DACFS;                                                  //Address 0xC4-0xC4
                                0x0000,                   //unsigned int  PAGE90H_RESERVED4;                                              //Address 0xC6-0xC7
                                0x0030,                   //unsigned int  IDAC_APC1_TARGET;                                               //Address 0xC8-0xC9
                                0x0008,                   //unsigned int  IDAC_APC1_MAXBIAS;                                              //Address 0xCA-0xCB  
                                0x0006,                   //unsigned int  IDAC_APC1_INITBIAS;                                             //Address 0xCC-0xCD 
                                0x1400,                   //unsigned int  IDAC_APC1_I_STEP;                                               //Address 0xCE-0xCF 
                                0x0000,0x0000,            //unsigned int  PAGE90H_RESERVED5[2];                                           //Address 0xD0-0xD3   
                                0x0030,                   //unsigned int  DCDC2_APC1_TARGET;                                              //Address 0xD4-0xD5
                                0x204E,                   //unsigned int  DCDC2_APC1_MAXBIAS;                                             //Address 0xD6-0xD7 
                                0x0030,                   //unsigned int  DCDC2_APC1_INITBIAS;                                            //Address 0xD8-0xD9 
                                0x1000,                   //unsigned int  DCDC2_APC1_I_STEP;                                              //Address 0xDA-0xDB
                                0x0000,0x0000,            //unsigned int  PAGE90H_RESERVED6[2];                                           //Address 0xDC-0xDF 
                                0xC083,                   //unsigned int  PLA1_CONFIG;                                                    //Address 0xE0-0xE1
                                0x0800,                   //unsigned int  PLA1_INPUT_SEL;                                                 //Address 0xE2-0xE3
                                0x4081,                   //unsigned int  PLA2_CONFIG;                                                    //Address 0xE4-0xE5
                                0x0000,                   //unsigned int  PLA2_INPUT_SEL;                                                 //Address 0xE6-0xE7
                                0xC082,                   //unsigned int  PLA3_CONFIG;                                                    //Address 0xE8-0xE9
                                0x0000,                   //unsigned int  PLA3_INPUT_SEL;                                                 //Address 0xEA-0xEB
                                0x0000,                   //unsigned int  PLA4_CONFIG;                                                    //Address 0xEC-0xED
                                0x0000,                   //unsigned int  PLA4_INPUT_SEL;                                                 //Address 0xEE-0xEF                                                               
                                0xFFFF,                   //unsigned char PASSWORD1_BYTE3 BYTE2;                                          //Address 0xF0     
                                0xFFFF,                   //unsigned char PASSWORD1_BYTE1 BYTE0;                                          //Address 0xF1     
                                0xFFFF,                   //unsigned char PASSWORD2_BYTE3 BYTE2;                                          //Address 0xF2     
                                0xFFFF,                   //unsigned char PASSWORD2_BYTE1 BYTE0;                                          //Address 0xF3       
                                0x0000,0x0000,            //unsigned char PAGE90H_RESERVED11[8];                                          //Address 0xF8-0xFF
                                0x0000,0x0000       
                         

                            };
#pragma required = FlashDataPage90h


//Page 91h
#pragma location = FLASH_PAGE91H_START
const unsigned char FlashDataPage91h[] =
                            {

                                0x00,                     //unsigned char DEVICE_CONFIG;                                                  //Address 0x80	   
                                0x00,                     //unsigned char PMIC_SELECT;                                                    //Address 0x81	   
                                0x3B,0x06,                //unsigned int  TEC2_SETPOINT;                                                  //Address 0x82-0x83
                                0x23,0x33,                //unsigned int  TEC2_KP;                                                        //Address 0x84-0x85
                                0x1E,0x01,                //unsigned int  TEC2_KI;                                                        //Address 0x86-0x86
                                0x00,0x00,                //unsigned int  TEC2_KD;                                                        //Address 0x88-0x89
                                0x00,0xAA,                //unsigned int  TEC2_SHIFT;                                                     //Address 0x8A-0x8B
                                0x01,0x00,                //unsigned int  TEC2_POSERRCLAMP;                                               //Address 0x8C-0x8D
                                0xFF,0x00,                //unsigned int  TEC2_NEGERRCLAMP;                                               //Address 0x8E-0x8F
                                0x2A,0x3E,                //unsigned int  TEC2_POSOPCLAMP;                                                //Address 0x90-0x91
                                0xD5,0xC4,                //unsigned int  TEC2_NEGOPCLAMP;                                                //Address 0x92-0x93
                                0x03,0x98,                //unsigned int  TEC2_CNFGCURRENTMEA_BURSTGPIOCONFIG;                            //Address 0x94-0x95
                                0x00,0x00,                //unsigned int  TEC2_OFFSETRIGGER;                                              //Address 0x96-0x97
                                0x00,0x00,                //unsigned int  TEC2_BURSTPWMDUTYOFFSET;                                        //Address 0x98-0x99
                                0x4C,0x90,                //unsigned int  TEC2_NORMAL_VCC;                                                //Address 0x9A-0x9B
                                0x00,0x00,0x00,0x00,      //unsigned int  PAGE91H_RESERVED0[2];                                           //Address 0x9C-0x9F
                                0x00,0x69,                //unsigned int  BUCK_PMOS_ON_STARTUP;                                           //Address 0xA0-0xA1
                                0x00,0x00,                //unsigned int  BUCK_NMOS_ON_STARTUP;                                           //Address 0xA2-0xA3
                                0x00,0x18,                //unsigned int  BUCK_PMOS_ON;                                                   //Address 0xA4-0xA5
                                0x00,0x00,                //unsigned int  BUCK_NMOS_ON;                                                   //Address 0xA6-0xA7
                                0x02,0x03,                //unsigned int  BUCK_IZDAC;                                                     //Address 0xA8-0xA9
                                0x00,0x30,                //unsigned int  BUCK_DC_DC_OPTIONS;                                             //Address 0xAA-0xAB
                                0x00,0x00,                //unsigned int  BUCK_PI_CTRL;                                                   //Address 0xAC-0xAD
                                0x00,0x64,                //unsigned int  BUCK_OUTERLOOPKP;                                               //Address 0xAE-0xAF
                                0x27,0x10,                //unsigned int  BUCK_OUTERLOOPKI;                                               //Address 0xB0-0xB1
                                0x00,0x37,                //unsigned int  BUCK_OUTLOOPSHIFT;                                              //Address 0xB2-0xB3
                                0x7F,0xFF,                //unsigned int  BUCK_OUTLOOPPOSTCLAMP;                                          //Address 0xB4-0xB4
                                0x00,0x00,                //unsigned int  BUCK_VRDCDC_CTRL;                                               //Address 0xB6-0xB7
#ifdef DCDC_BIASING
                                0x7D,0x00,                //unsigned int  BUCK_MAX_DCDC1;                                                 //Address 0xB8-0xB9
                                0x32,0xC8,                //unsigned int  BUCK_MAX_DCDC2;                                                 //Address 0xBA-0xBB
                                0x61,0xA8,                //unsigned int  BUCK_DC_DC1_TARGET;                                             //Address 0xBC-0xBD
                                0x00,0x00,                //unsigned int  BUCK_DC_DC2_TARGET;                                             //Address 0xBE-0xBF
#else
                                0x7D,0x00,                //unsigned int  BUCK_MAX_DCDC1;                                                 //Address 0xB8-0xB9
                                0x7D,0x00,                //unsigned int  BUCK_MAX_DCDC2;                                                 //Address 0xBA-0xBB
                                0x61,0xA8,                //unsigned int  BUCK_DC_DC1_TARGET;                                             //Address 0xBC-0xBD
                                0x61,0xA8,                //unsigned int  BUCK_DC_DC2_TARGET;                                             //Address 0xBE-0xBF
#endif                            
                                0x00,0x7F,                //unsigned int  APD_ERRSTARTCLAMP;                                              //Address 0xC0-0xC1
                                0xB3,0x00,                //unsigned int  APD_DUTYCLAMP;                                                  //Address 0xC2-0xC3
                                0x08,0x00,                //unsigned int  APD_INTEGRALGAIN;                                               //Address 0xC4-0xC5
                                0x00,0x40,                //unsigned int  APD_DUTYSTARTINCCLAMP;                                          //Address 0xC6-0xC7
                                0xFF,0xF7,                //unsigned int  APD_INTEGRALCLAMP;                                              //Address 0xC8-0xC9
                                0x00,0x20,                //unsigned int  APD_APDNEGERRCLAMP;                                             //Address 0xCA-0xCB
                                0x00,0x20,                //unsigned int  APD_APDPOSERRCLAMP;                                             //Address 0xCC-0xCC
                                0xF0,0x00,                //unsigned int  APD_PROPORTIONALGAIN;                                           //Address 0xCE-0xCF
                                0x0B,0x54,                //unsigned int  APD_TARGET_OUTPUT;                                              //Address 0xD0-0xD1
                                0x20,0x44,                //unsigned int  APD_CONFIG;                                                     //Address 0xD2-0xD3
                                0x00,0x00,0x00,0x00,      //unsigned int  PAGE91H_RESERVED1[6];                                           //Address 0xD4-0xDF 
                                0x00,0x00,0x00,0x00, 
                                0x00,0x00,0x00,0x00,  
                                0x00,0xB0,                //unsigned int  INV_ERRSTARTCLAMP;                                              //Address 0xE0-0xE1
                                0xEF,0x00,                //unsigned int  INV_DUTYCLAMP;                                                  //Address 0xE2-0xE3
                                0x01,0xFF,                //unsigned int  INV_INTEGRALGAIN;                                               //Address 0xE4-0xE5
                                0x00,0x7F,                //unsigned int  INV_DUTYSTARTINCCLAMP;                                          //Address 0xE6-0xE7
                                0xEF,0x00,                //unsigned int  INV_INTEGRALCLAMP;                                              //Address 0xE8-0xE9
                                0x00,0xB0,                //unsigned int  INV_APDNEGERRCLAMP;                                             //Address 0xEA-0xEB
                                0x00,0xB0,                //unsigned int  INV_APDPOSERRCLAMP;                                             //Address 0xEC-0xED
                                0x80,0x00,                //unsigned int  INV_PROPORTIONALGAIN;                                           //Address 0xEE-0xEF
                                0xF3,0x1C,                //unsigned int  INV_TARGET_OUTPUT;                                              //Address 0xF0-0xF1
                                0xA0,0x44,                //unsigned int  INV_APD_CONFIG;                                                 //Address 0xF2-0xF3
                                0x00,0x00,0x00,0x00,      //unsigned int  PAGE91H_RESERVED2[6];                                           //Address 0xF4-0xFF    
                                0x00,0x00,0x00,0x00,       
                                0x00,0x00,0x00,0x00                               

                            };
#pragma required = FlashDataPage91h


#endif



// Set the 32-byte MAXQ flash password at code address 10h, need to check "Place constants in CODE" in Options/General/Target
#pragma location=0x0020
const unsigned int password[16] = {0x2222, 0x2222, 0x2222, 0x2222, 0x2222, 0x2222, 0x2222, 0x2222, 0x2222, 0x2222, 0x2222, 0x2222, 0x2222, 0x2222, 0x2222, 0x2222};

#endif // __MEMORY_H

//-----------------------------------------------------------------------------
// end of file
//-----------------------------------------------------------------------------





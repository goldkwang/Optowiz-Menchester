/*******************************************************************************
* Copyright (C) 2017 Maxim Integrated Products, Inc., All Rights Reserved.
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

#ifndef __MEM_ACCESS_H_
#define __MEM_ACCESS_H_

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------

#define ACCESS_LEVEL_NONE                     0
#define ACCESS_LEVEL_RO                       1
#define ACCESS_LEVEL_RW                       2

// LUT definition
#define LUT_1       1
#define LUT_2       2
#define LUT_3       3
#define LUT_4       4
#define LUT_5       5
#define LUT_6       6
#define LUT_7       7
#define LUT_8       8

#define MEMORY_WRITE_BUFFER_SIZE    256

//possible flags for WriteBufferStatus
typedef enum WRITE_BUFFER_STATUS_ENUM_TAG
{
   MEMORY_WRITE_BUFFER_IDLE,
   MEMORY_WRITE_BUFFER_WRITING,
   MEMORY_WRITE_BUFFER_WAITING_TO_PROCESS,
   MEMORY_WRITE_BUFFER_READING
} WriteBufferStatus_E;

//structure of parameters for communication from host over I2C
typedef struct WRITE_BUFFER_STRUCTURE_TAG
{
   unsigned char           devAddress;                                    //A0 or A2
   WriteBufferStatus_E     bufferStatus;                                  //flag showing status of transaction
   unsigned char           numOfEntries;                                  //num of bytes received           
   unsigned char           address;                                       //current register address
   unsigned char           writeBufferEntry[MEMORY_WRITE_BUFFER_SIZE];    //I2C data bytes
} WriteBuffer_S;

#define PLA_TXD    1
#define PLA_RSEL   2
#define PLA_TXF    3
#define PLA_LOS    4

#define TEC_CH1              0
#define TEC_CH2              1
#define TEC1_ENABLE                            0x01
#define TEC2_ENABLE                            0x02
#define BUCK1_ENABLE                           0x04 
#define BUCK2_ENABLE                           0x08 
#define BUCK3_ENABLE                           0x10
#define BOOST3_ENABLE                          0x20
#define BUCK4_ENABLE                           0x40
               
//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
void Process_PMIC(void);
void Buck_Init(unsigned int Channel, unsigned int Target);
void Boost_Init(unsigned int Channel);
void External_Boost(unsigned int Channel);
void SW_Delay(unsigned int DelayCounter);
void TECC_Init(unsigned int Channel);
void ProcessReceivedI2CData(void);
void CopyLutToSram(unsigned char table_num);
unsigned int GetIntFromFlash(unsigned char table_num, unsigned int address);
unsigned char GetLUTByteFromFlash(unsigned char table_num, unsigned int index);
void CheckPasswordLevel(void);
void Memory_Init(void);
unsigned int InitPLA(unsigned int PLA, unsigned int Config);
void UpdateInternalTemp(void);
void UpdateExternalTemp(void);


//-----------------------------------------------------------------------------
// global variables prototypes
//-----------------------------------------------------------------------------


#endif  //__MEM_ACCESS_H_

//End

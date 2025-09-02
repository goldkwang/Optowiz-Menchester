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


//-----------------------------------------------------------------------------
// MemoryAccess.h
//-----------------------------------------------------------------------------

#ifndef MEMORYACCESS_H
#define MEMORYACCESS_H





//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------


#define ACCESS_LEVEL_NONE                     0
#define ACCESS_LEVEL_RO                       1
#define ACCESS_LEVEL_RW                       2


//Password definition
#define PASSWORD1_B0                          0xFF   
#define PASSWORD1_B1                          0xFF   
#define PASSWORD1_B2                          0xFF
#define PASSWORD1_B3                          0xFF
                          
#define PASSWORD2_B0                          0xFF
#define PASSWORD2_B1                          0xFF
#define PASSWORD2_B2                          0xFF
#define PASSWORD2_B3                          0xFF



// LUT definition
#define LUT_1       1
#define LUT_2       2
#define LUT_3       3
#define LUT_4       4
#define LUT_5       5
#define LUT_6       6
#define LUT_7       7
#define LUT_8       8




#define MEMORY_WRITE_BUFFER_SIZE    8




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
} WriteBuffer_S, *WriteBuffer_P;




               
//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------

void MemoryAccessInit(void);
void ProcessTwsiWriteBuffers(void);
void CopyLutToSram(unsigned char table_num);
unsigned int GetIntFromFlash(unsigned char table_num, unsigned int address);
unsigned char GetLUTByteFromFlash(unsigned char table_num, unsigned int index);




//-----------------------------------------------------------------------------
// global variables prototypes
//-----------------------------------------------------------------------------






#endif // MEMORYACCESS_H

//-----------------------------------------------------------------------------
// end of file
//-----------------------------------------------------------------------------


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

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <iods4835.h>
#include <intrinsics.h>

#include "board.h"
#include "i2cslave.h"
#include "memory_access.h"
#include "includes.h"
#include <string.h>

//-----------------------------------------------------------------------------
// global variables defined in this module
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// local function declaration
//-----------------------------------------------------------------------------


void Board_Init(void)
{     
  
   GPIO_Init();                                                                 //Initialize GPIO
   
   I2CMaster_Init();                                                            //Initialize I2CS     
          
   I2CS_Init();                                                                 //Initialize I2CS  

   ADC_Init();                                                                  //Initialize ADC registers (but ADC is not enabled yet)   
   
   DCDC_Init();
   
   APD_Init();   

   INV_Init(); 

   TEC_Init(); 
   
   IDAC_Init();    
   
   DSDAC_Init();   
   
   SH_Init();  

   Timer1_Init();                                                               //Timer_Init  

}

//------------------------------------------------------------------------------
// Initialize_Memory: This function reads LUTs values from flash, load into
// SRAM and initializes SRAM with default/save values.
//------------------------------------------------------------------------------
void Initialize(void)
{     

   Memory_Init();                                                               //Initialize the memory
   
   Board_Init();
  
   //MAX24016_Init();
   
   //Loop();  
  
}


//-----------------------------------------------------------------------------
// end of file
//-----------------------------------------------------------------------------

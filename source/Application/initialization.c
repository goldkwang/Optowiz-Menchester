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

//-----------------------------------------------------------------------------
// Board_Init function
//   - all blocks in EVK board are initialized here
//-----------------------------------------------------------------------------
void Board_Init(void)
{  
    
//   GPIO_Init();                                                                 //Initialize GPIO
   
   ADC_Init();                                                                  //Initialize ADC registers (but ADC is not enabled yet)   
   
   I2CMaster_Init();                                                            //Initialize I2C Master     
          
   // SH_Init();                                                                   //Initialize Sample and Hold
   
    PLA_Init();                                                                  //Initialize PLA
  
   WATCHDOG_Init();                                                             //Initialize Watchdog

//   Max5825_dac_init();
}

//------------------------------------------------------------------------------
// Initialization Function
//      - : This function reads LUTs values from flash, load into
//          SRAM and initializes SRAM with default/save values and initialize 
//          all hardware Peripherals.
//------------------------------------------------------------------------------
void Initialization(void)
{     
   GPIO_Init();                                                                 //Initialize GPIO

   Memory_Init();                                                               //Initialize the memory
   Board_Init();                                                                //Initialize SC evk board

   INRUSH_Init();
   
//   SW_Delay(5000);
   
//   PO2_bit.PO27 = 1;
   initialize_variables();
  
}


//-----------------------------------------------------------------------------
// end of file
//-----------------------------------------------------------------------------

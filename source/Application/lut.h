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

#ifndef __LUT_H_
#define __LUT_H_

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------

#define LUT_APD_EN                            0x2000
#define LUT_MOD_EN                            0x8000

#define APCCN_CONFIG                          0x0100

#define APC_INDEX_APC_TARGET                  0 
#define APC_INDEX_APC_MAXBIAS                 1 
#define APC_INDEX_APC_INITBIAS                2 
#define APC_INDEX_APC_I_STEP                  3 
#define APC_INDEX_APC_BIASREG                 4 



               
//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------

void LUT_Process(signed int temp_value);
void LUT_APD_Process(signed int temp_value);
void LUT_BIAS_Process(signed int temp_value);
void LUT_MOD_Process(signed int temp_value);
unsigned int INIT_BIAS_LUT(signed int temp_value);
//-----------------------------------------------------------------------------
// global variables prototypes
//-----------------------------------------------------------------------------


#endif  //__LUT_H_

//-----------------------------------------------------------------------------
// end of file
//-----------------------------------------------------------------------------



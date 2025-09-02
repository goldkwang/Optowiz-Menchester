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

#ifndef __APC_H_
#define __APC_H_

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------
#define APC_ENABLE                            0x4000
#define INIT_BIAS_LUT_ENABLE                  0x0400

#define APCCN_CONFIG                          0x0100

#define APC_INDEX_APC_TARGET                  0 
#define APC_INDEX_APC_MAXBIAS                 1 
#define APC_INDEX_APC_INITBIAS                2 
#define APC_INDEX_APC_I_STEP                  3 
#define APC_INDEX_APC_BIASREG                 4 


#define APC_ERROR                             50


#define APC_DCDC_BIASING_INIT_BIAS         0x2EE0
//-----------------------------------------------------------------------------
//EA defines
//-----------------------------------------------------------------------------
#define MAX_EA_OUPUT         0x3400

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------

void APC_Init(void);
void APC_EnableConversion(void);
void APC_Process(void);
void APC_EnableConversion(void);

//-----------------------------------------------------------------------------
// global variables prototypes
//-----------------------------------------------------------------------------


#endif  //__APC_H_

//-----------------------------------------------------------------------------
// end of file
//-----------------------------------------------------------------------------


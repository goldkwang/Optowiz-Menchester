/*******************************************************************************
* Copyright (C) 2018 Maxim Integrated Products, Inc., All rights Reserved.
* 
* Maxim Integrated Company Confidential
*
* * This software is protected by copyright laws of the United States and
* of foreign countries. This material may also be protected by patent laws
* and technology transfer regulations of the United States and of foreign
* countries. This software is furnished under a license agreement and/or a
* nondisclosure agreement and may only be used or reproduced in accordance
* with the terms of those agreements. Dissemination of this information to
* any party or parties not specified in the license agreement and/or
* nondisclosure agreement is expressly prohibited.
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


#ifndef _DDM_H_
#define _DDM_H_


//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------
#define ADDRESS_ADC_FACTORY_SCALE                     0x0034
#define ADDRESS_ADC_FACTORY_OFFSET                    0x0035
//#define ADDRESS_ADC_FACTORY_SCALE                     0x0017
//#define ADDRESS_ADC_FACTORY_OFFSET                    0x0018
#define ADDRESS_ADC_FACTORY_TEMP_SCALE                0x0019
#define ADDRESS_ADC_FACTORY_TEMP_OFFSET               0x001A
//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
void DDM_Read(void);
void CalibConstantRead(void);
void ProcessTemperature(void);
static unsigned int ApplyInternalScale(unsigned int unRaw_adc, unsigned int unScale, signed int sOffset);
extern signed int sPrev_lut_temp;


#endif //_DDM_H_
//-----------------------------------------------------------------------------
// end of file
//-----------------------------------------------------------------------------





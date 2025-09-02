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


#ifndef _LSM_H_
#define _LSM_H_

#if __SFP28_ER__== 1

#else
 
#endif

#define STATE_POR                  1
#define STATE_PMIC_INIT            2
#define STATE_DCDC_INIT            3
#define STATE_INV_INIT             4
#define STATE_IDAC_INIT            5
#define STATE_APD_INIT             6
#define STATE_TEC_INIT             7
#define STATE_APD_LUT_INIT         8
#define STATE_INIT                 9
#define STATE_DRIVER_INIT          10
#define STATE_TEC_STABLE           11
#define STATE_APC_RAMP             12
#define STATE_MOD_INIT             13
#define STATE_NORMAL_OPERATION     14



//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
extern void StateMachine(void);
extern void StateMachineUpdateTXDDelayCount(unsigned int data);
extern unsigned char Module_State;





#endif //_LSM_H_

//-----------------------------------------------------------------------------
// end of file
//-----------------------------------------------------------------------------



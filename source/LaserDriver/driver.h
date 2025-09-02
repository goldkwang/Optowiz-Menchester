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


#ifndef _DRIVER_COMM_H_
#define _DRIVER_COMM_H_

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "memory_map.h"

#if __SFP28_ER__== 1
//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------
#define DRIVER_SLAVE_ADDR                       0x18  // MALD-37845B

#define COMMAND_DEVICE_RESET			0xAA  // 0x80   

// Page 00h

#define ADDR_P00_CHIPID                         0x00
#define ADDR_P00_REVID                          0x01
#define ADDR_P00_RESET                          0x02
#define ADDR_P00_I2C_ADDRESS_MODE               0x03
#define ADDR_P00_RX_BIAS_CURRENT                0x04
#define ADDR_P00_RX_RSSI_MONCLK                 0x05
#define ADDR_P00_RX_CH_MODE                     0x06
#define ADDR_P00_RX_CH_MODE_N(n)                (ADDR_P00_RX_CH_MODE + (n))

#define ADDR_P00_RX_LOS_LOL_MASK                0x0A
#define ADDR_P00_RX_LOS_LOL_STATUS              0x0B
#define ADDR_P00_RX_ALARM_STATUS                0x0D
#define ADDR_P00_RX_LOS_LOL_ALARM               0x0D
#define ADDR_P00_RX_CH_AFE_MISCL                0x0E
#define ADDR_P00_RX_CH_AFE_MISCL_N(n)           (0x0E + (n))
#define ADDR_P00_RX_CH_SLA                      0x12
#define ADDR_P00_RX_CH_SLA_N(n)                 (0x12 + (n))

#define ADDR_P00_RX_TIA_CTRL                    0x16
#define ADDR_P00_RX_CDR_LBW                     0x1A
#define ADDR_P00_RX_CH_LOKPHASEADJ              0x1B
#define ADDR_P00_RX_CH_LOKPHASEADJ_N(n)         (0x1B + (n))

#define ADDR_P00_RX_CH_OUTPUT_SWING             0x20
#define ADDR_P00_RX_CH_OUTPUT_SWING_N(n)        (0x20 + (n))

#define ADDR_P00_RX_CH_OUTPUT_DEEMPH            0x24
#define ADDR_P00_RX_CH_OUTPUT_DEEMPH_N(n)       (0x24 + (n))

#define ADDR_P00_RX_CH_OUTPUT_XPADJ             0x27
#define ADDR_P00_RX_CH_OUTPUT_XPADJ_N(n)        (0x27 + (n))

#define ADDR_P00_REG_PAGE                       0xFF    // Page 00,01,02 same address

// Page 01h

#define ADDR_P01_TX_BIAS_CURRENT                0x04
#define ADDR_P01_TX_MONCLK                      0x05
#define ADDR_P01_TX_CH_MODE                     0x06
#define ADDR_P01_TX_CH_MODE_N(n)                (ADDR_P01_TX_CH_MODE + (n))

#define ADDR_P01_TX_LOS_LOL_MASK                0x0A
#define ADDR_P01_TX_LOS_LOL_STATUS              0x0B
#define ADDR_P01_TX_ALARM_STATUS                0x0C
#define ADDR_P01_TX_LOS_LOL_ALARM               0x0D
#define ADDR_P01_TXFAULT_STATE                  0x0E
#define ADDR_P01_TX_FAULT_ALARM_MASK            0x0F
#define ADDR_P01_TX_FAULT_ALARM                 0x10
#define ADDR_P01_TX_IGNORE_TXFAULT              0x11
#define ADDR_P01_TX_CH_AFE_MISCL                0x12
#define ADDR_P01_TX_CH_AFE_MISCL_N(n)           (ADDR_P01_TX_CH_AFE_MISCL + (n))

#define ADDR_P01_TX_CH_CTLE                     0x16
#define ADDR_P01_TX_CH_CTLE_N(n)                (ADDR_P01_TX_CH_CTLE + (n))

#define ADDR_P01_TX_CDR_LBW                     0x1A
#define ADDR_P01_TX_CH_LOKPHASEADJ              0x1B
#define ADDR_P01_TX_CH_LOKPHASEADJ_N(n)         (ADDR_P01_TX_CH_LOKPHASEADJ + (n))

#define ADDR_P01_TX_CH_OUTPUT_IBIAS             0x20
#define ADDR_P01_TX_CH_OUTPUT_IBIAS_N(n)        (ADDR_P01_TX_CH_OUTPUT_IBIAS + (n))

#define ADDR_P01_TX_CH_OUTPUT_IMOD              0x24
#define ADDR_P01_TX_CH_OUTPUT_IMOD_N(n)         (ADDR_P01_TX_CH_OUTPUT_IMOD + (n))

#define ADDR_P01_TX_CH_OUTPUT_PreFall           0x28
#define ADDR_P01_TX_CH_OUTPUT_PreFall_N(n)      (ADDR_P01_TX_CH_OUTPUT_PreFall + (n))

#define ADDR_P01_TX_CH_OUTPUT_EYE               0x2C
#define ADDR_P01_TX_CH_OUTPUT_EYE_N(n)          (ADDR_P01_TX_CH_OUTPUT_EYE + (n))

#define ADDR_P01_VCSEL_IBURNIN                  0x30
#define ADDR_P01_VCSEL_BURNIN_EN                0x31
#define ADDR_P01_ADC_CONFIG                     0x40
#define ADDR_P01_ADC_OUT0_MSBS                  0x41
#define ADDR_P01_ADC_OUT0_LSBS                  0x42
#define ADDR_P01_ADC_Driver_Measmt_Select       0x43
#define ADDR_P01_ADC_DRIVER_CH_SELECT           0x44


// SAMPLE CHIP MAX...
#define ADDR_TXCTRL1					0x01 
#define ADDR_TXCTRL2					0x02 
#define ADDR_TXCTRL3					0x03 
#define ADDR_TXCTRL4					0x04 
#define ADDR_TXCTRL5					0x05 
#define ADDR_TXCTRL6					0x06 
#define ADDR_TXCTRL7					0x07 
#define ADDR_TXCTRL8					0x08 
#define ADDR_SET_MOD0					0x09
#define ADDR_SET_MOD1					0x0A
#define ADDR_MODMAX					0x0B
#define ADDR_APCCTRL1					0x0E
#define ADDR_APCCTRL2					0x0F
#define ADDR_SET_APC0					0x10
#define ADDR_SET_APC1					0x11
#define ADDR_SET_BIAS0					0x12
#define ADDR_SET_BIAS1					0x13
#define ADDR_BIASMAX					0x14
#define ADDR_MPDMAX					0x15
#define ADDR_LDOCTRL   				        0x1E
#define ADDR_RXCTRL1					0x21
#define ADDR_RXCTRL2   				        0x22
#define ADDR_RXCTRL3					0x23
#define ADDR_RXCTRL4   				        0x24
#define ADDR_RXLOS1					0x26
#define ADDR_RXLOS2   				        0x27
#define ADDR_RXLOS3					0x28
#define ADDR_RXLOS4   				        0x29
#define ADDR_FAULTCTRL 				        0x2B
#define ADDR_FAULTMASK1 				0x2C
#define ADDR_FAULTMASK2 				0x2D
#define ADDR_TOPCTRL					0x3B 
#define ADDR_EVENT1   				        0x3D
#define ADDR_EVENT2   				        0x3E

#define ADDR_PINSTAT                                    0x40 
#define ADDR_TOPSTAT                                    0x41
#define ADDR_FAULTSTAT1                                 0x42
#define ADDR_FAULTSTAT2                                 0x43
#define ADDR_TXSTAT                                     0x44
#define ADDR_RXSTAT                                     0x45



#define ADDR_DDMSTAT15  				0x58
#define ADDR_DDMSTAT16   				0x59
#define ADDR_DDMSTAT17                                  0x5A
#define ADDR_DDMSTAT18                                  0x5B
#define ADDR_RXPU                                       0x70


#else
//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------
#define DRIVER_SLAVE_ADDR                               0x46

#define COMMAND_DEVICE_RESET				0x80   

#define ADDR_TXCTRL1					0x01 
#define ADDR_TXCTRL2					0x02 
#define ADDR_TXCTRL3					0x03 
#define ADDR_TXCTRL4					0x04 
#define ADDR_TXCTRL5					0x05 
#define ADDR_TXCTRL6					0x06 
#define ADDR_TXCTRL7					0x07 
#define ADDR_TXCTRL8					0x08 
#define ADDR_SET_MOD0					0x09
#define ADDR_SET_MOD1					0x0A
#define ADDR_MODMAX					0x0B
#define ADDR_APCCTRL1					0x0E
#define ADDR_APCCTRL2					0x0F
#define ADDR_SET_APC0					0x10
#define ADDR_SET_APC1					0x11
#define ADDR_SET_BIAS0					0x12
#define ADDR_SET_BIAS1					0x13
#define ADDR_BIASMAX					0x14
#define ADDR_MPDMAX					0x15
#define ADDR_LDOCTRL   				        0x1E
#define ADDR_RXCTRL1					0x21
#define ADDR_RXCTRL2   				        0x22
#define ADDR_RXCTRL3					0x23
#define ADDR_RXCTRL4   				        0x24
#define ADDR_RXLOS1					0x26
#define ADDR_RXLOS2   				        0x27
#define ADDR_RXLOS3					0x28
#define ADDR_RXLOS4   				        0x29
#define ADDR_FAULTCTRL 				        0x2B
#define ADDR_FAULTMASK1 				0x2C
#define ADDR_FAULTMASK2 				0x2D
#define ADDR_TOPCTRL					0x3B 
#define ADDR_EVENT1   				        0x3D
#define ADDR_EVENT2   				        0x3E

#define ADDR_PINSTAT                                    0x40 
#define ADDR_TOPSTAT                                    0x41
#define ADDR_FAULTSTAT1                                 0x42
#define ADDR_FAULTSTAT2                                 0x43
#define ADDR_TXSTAT                                     0x44
#define ADDR_RXSTAT                                     0x45



#define ADDR_DDMSTAT15  				0x58
#define ADDR_DDMSTAT16   				0x59
#define ADDR_DDMSTAT17                                  0x5A
#define ADDR_DDMSTAT18                                  0x5B
#define ADDR_RXPU                                       0x70


#endif



//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------
void Driver_SoftReset(unsigned char SlaveAddress, PAGE04H_MEMORY_MAP *DRIVER_MEMORY);
void Driver_ReadTOPSTAT(unsigned char SlaveAddress, PAGE04H_MEMORY_MAP *DRIVER_MEMORY);
void Driver_ReadRXSTAT(unsigned char SlaveAddress, PAGE04H_MEMORY_MAP *DRIVER_MEMORY);
void Driver_ReadTXSTAT(unsigned char SlaveAddress, PAGE04H_MEMORY_MAP *DRIVER_MEMORY);
void Driver_TXControlRegsWrite(unsigned char SlaveAddress, PAGE04H_MEMORY_MAP *DRIVER_MEMORY);
void Driver_TXRegsWrite(unsigned char SlaveAddress, PAGE04H_MEMORY_MAP *DRIVER_MEMORY);
void Driver_RXRegsWrite(unsigned char SlaveAddress, PAGE04H_MEMORY_MAP *DRIVER_MEMORY);
void Driver_TopCtrlRegsWrite(unsigned char SlaveAddress, PAGE04H_MEMORY_MAP *DRIVER_MEMORY);
void Driver_ControlRegsWrite(unsigned char SlaveAddress, PAGE04H_MEMORY_MAP *DRIVER_MEMORY);
void Driver_TXControlRegsRead(unsigned char SlaveAddress, PAGE04H_MEMORY_MAP *DRIVER_MEMORY);
void Driver_TXRegsRead(unsigned char SlaveAddress, PAGE04H_MEMORY_MAP *DRIVER_MEMORY);
void Driver_RXRegsRead(unsigned char SlaveAddress, PAGE04H_MEMORY_MAP *DRIVER_MEMORY);
void Driver_ControlRegsRead(unsigned char SlaveAddress, PAGE04H_MEMORY_MAP *DRIVER_MEMORY);
void Driver_StatusRegsRead(unsigned char SlaveAddress, PAGE04H_MEMORY_MAP *DRIVER_MEMORY);
void Driver_TXModWrite(unsigned char SlaveAddress, PAGE04H_MEMORY_MAP *DRIVER_MEMORY);
void Driver_TXBiasWrite(unsigned char SlaveAddress, PAGE04H_MEMORY_MAP *DRIVER_MEMORY);
void Driver_RegsReadOut(unsigned char SlaveAddress, PAGE04H_MEMORY_MAP *DRIVER_MEMORY);
void Driver_Init(unsigned char SlaveAddress, PAGE04H_MEMORY_MAP *DRIVER_MEMORY );

#endif //_DRIVER_COMM_H_

//-----------------------------------------------------------------------------
// end of file
//-----------------------------------------------------------------------------


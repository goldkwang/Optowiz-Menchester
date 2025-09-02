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


#ifndef _ALARM_WARNING_H_
#define _ALARM_WARNING_H_

#define VCC_DDM           0x01
#define TEMP_DDM          0x02
#define TXP_DDM           0x04
#define RXP_DDM           0x08
#define BIAS_DDM          0x10
#define LASER_TEMP_DDM  0x20
#define TEC_CURRENT_DDM   0x40


#define TEMP_HIGH_FLAG                    0x80
#define TEMP_LOW_FLAG                     0x40
#define VCC_HIGH_FLAG                     0x20
#define VCC_LOW_FLAG                      0x10
#define TX_BIAS_HIGH_FLAG                 0x08
#define TX_BIAS_LOW_FLAG                  0x04
#define TX_POWER_HIGH_FLAG                0x02
#define TX_POWER_LOW_FLAG                 0x01
#define RX_POWER_HIGH_FLAG                0x80
#define RX_POWER_LOW_FLAG                 0x40
#define LASER_TEMP_HIGH_FLAG              0x20
#define LASER_TEMP_LOW_FLAG               0x10
#define TEC_CURRENT_HIGH_FLAG             0x08
#define TEC_CURRENT_LOW_FLAG              0x04


#define AW_MODE_LATCHED_EN                0x80
#define TXF_AW_EN                         0x80
#define TXF_TXD_EN                        0x08

void SetUnsignedAlarmsAndWarnings(unsigned int which, unsigned int ddm_value);
void SetSignedAlarmsAndWarnings(unsigned int which,signed int ddm_value);
void TXF_AlarmWarn_Check(void);
void Clear_TXF_Status(void);


extern unsigned char RT_ALARM2;
extern unsigned char RT_ALARM3;
extern unsigned char RT_WARN2;
extern unsigned char RT_WARN3;


#endif //_ALARM_WARNING_H_


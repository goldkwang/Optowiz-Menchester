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
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <intrinsics.h>
#include <iods4835.h>
#include <stdio.h>
#include <string.h>
#include "includes.h"

//-----------------------------------------------------------------------------
// variables defined in this module
//-----------------------------------------------------------------------------
//static unsigned char s_ucTXF_status = 0;
//static unsigned char s_ucReal_time_ALARM2 = 0;
//static unsigned char s_ucReal_time_ALARM3 = 0;
//static unsigned char s_ucReal_time_WARN2 = 0;
//static unsigned char s_ucReal_time_WARN3 = 0;

//-----------------------------------------------------------------------------
// SetAlarmAndWarning() function
// Makes comparisons to fault and warning levels
// Sets appropriate fault and warning flags
//-----------------------------------------------------------------------------
void SetUnsignedAlarmsAndWarnings(unsigned int unWhich, unsigned int unDdm_value)
{
#if __SFP28_ER__ == 1
#else

  unsigned int *pThreshold_ptr;
  unsigned int unThreshold;
  unsigned char ucAlarm_register = 0x00;
  unsigned char ucWarn_register = 0x00;
  unsigned char ucAlarm_clear_register = 0x00;
  unsigned char ucWarn_clear_register = 0x00;  
  unsigned char ucHigh_flag;
  unsigned char ucLow_flag;
  
  
  switch (unWhich)
  {    
   case VCC_DDM:                                                                // VCC
                   pThreshold_ptr = &VCC_ALARM_HI;                                //get ptr for hi alarm, this is the first parameter in memory map
                   ucHigh_flag = VCC_HIGH_FLAG;                                     //this is the proper status flag to set
                   ucLow_flag = VCC_LOW_FLAG;
                   break;   
   
   case BIAS_DDM:                                                               // Bias
                   pThreshold_ptr = &BIAS_ALARM_HI;
                   ucHigh_flag = TX_BIAS_HIGH_FLAG;
                   
                   if(TXDStatus() == DE_ASSERTED)                               //laser is on, ok to flag low bias
                   {
                     ucLow_flag = TX_BIAS_LOW_FLAG;
                   }
                   else                                                         //laser ramp not complete, don't flag low bias
                   {
                     ucLow_flag = 0x00;                                            //null flag
                   }
                   break;
   
   case TXP_DDM:                                                                // TX power
                 pThreshold_ptr = &TX_POWER_ALARM_HI;
                 ucHigh_flag = TX_POWER_HIGH_FLAG;
                 
                 if(TXDStatus() == DE_ASSERTED)                                 //laser is on, ok to flag low txp
                 {
                  ucLow_flag = TX_POWER_LOW_FLAG;
                 }
                 else                                                           //laser ramp not complete, don't flag low bias
                 {
                   ucLow_flag = 0x00;                                              //null flag
                 }
                 break;
   
   case RXP_DDM:                                                                // RX power  
                 pThreshold_ptr = &RX_POWER_ALARM_HI;
                 ucHigh_flag = RX_POWER_HIGH_FLAG;
                 ucLow_flag = RX_POWER_LOW_FLAG;
                 break;

   default: 
                 unDdm_value = 0;
                 pThreshold_ptr = &TX_POWER_ALARM_HI;                             //give some value
                 ucHigh_flag = 0x00;                                                //will not set any flags
                 ucLow_flag = 0x00;
                 break;
  }
  
  
  
  // high alarm comparison
  unThreshold = __swap_bytes(*pThreshold_ptr);                                      //read unThreshold
  if (unDdm_value > unThreshold)
  {
    ucAlarm_register |= ucHigh_flag;
  }
  else
  {
    ucAlarm_clear_register |= ucHigh_flag;
  }
    
  // low alarm comparison
  pThreshold_ptr++;                                                               //increment to the next unThreshold
  unThreshold = __swap_bytes(*pThreshold_ptr);                                      //read unThreshold
  if (unDdm_value < unThreshold)
  {
    ucAlarm_register |= ucLow_flag;
  }
  else
  {
    ucAlarm_clear_register |= ucLow_flag;
  } 
  
  //high warning comparison
  pThreshold_ptr++;                                                               //increment to the next unThreshold
  unThreshold = __swap_bytes(*pThreshold_ptr);
  if (unDdm_value > unThreshold)
  {
    ucWarn_register |= ucHigh_flag;
  }
  else
  {
    ucWarn_clear_register |= ucHigh_flag;
  }
        
  //low warning comparison
  pThreshold_ptr++;                                                               //increment to the next unThreshold
  unThreshold = __swap_bytes(*pThreshold_ptr);
  if (unDdm_value < unThreshold)
  {
    ucWarn_register |= ucLow_flag;
  }  
  else
  {
    ucWarn_clear_register |= ucLow_flag;
  }
  
  //store alarms and warnings back
  if(unWhich == RXP_DDM)
  {
    if(PAGE90H_Memory.AW_MODE & AW_MODE_LATCHED_EN)
    {
      __disable_interrupt();                                                      //disable so I2C interrupt to clear doesn't corrupt data
      ALARM2 |= ucAlarm_register;                                                        //add these bits to existing alarms
      WARN2 |= ucWarn_register;    
      __enable_interrupt(); 
      
      s_ucReal_time_ALARM2 |= ucAlarm_register;                                                      
      s_ucReal_time_WARN2  |= ucWarn_register;   
      s_ucReal_time_ALARM2 &= ~ucAlarm_clear_register;                                                       
      s_ucReal_time_WARN2  &= ~ucWarn_clear_register;        
      
    }
    else
    {
      ALARM2 |= ucAlarm_register;                                                      
      WARN2  |= ucWarn_register;   
      ALARM2 &= ~ucAlarm_clear_register;                                                       
      WARN2  &= ~ucWarn_clear_register;               
    }  
  }
  else
  {
    if(PAGE90H_Memory.AW_MODE & AW_MODE_LATCHED_EN)
    {
      __disable_interrupt();                                                      //disable so I2C interrupt to clear doesn't corrupt data
      ALARM3 |= ucAlarm_register;                                                        //add these bits to existing alarms
      WARN3 |= ucWarn_register;
      __enable_interrupt();
      
      s_ucReal_time_ALARM3 |= ucAlarm_register;                                                      
      s_ucReal_time_WARN3  |= ucWarn_register;   
      s_ucReal_time_ALARM3 &= ~ucAlarm_clear_register;                                                       
      s_ucReal_time_WARN3  &= ~ucWarn_clear_register;         
    }
    else
    {
      ALARM3 |= ucAlarm_register;                                                      
      WARN3  |= ucWarn_register;   
      ALARM3 &= ~ucAlarm_clear_register;                                                       
      WARN3  &= ~ucWarn_clear_register;               
    }
  }
#endif
}


void SetSignedAlarmsAndWarnings(unsigned int unWhich,signed int sDdm_value)
{
#if __SFP28_ER__ == 1
#else
  
  signed int *pThreshold_ptr;
  signed int unThreshold;
  unsigned char ucAlarm_register = 0x00;
  unsigned char ucWarn_register = 0x00;
  unsigned char ucAlarm_clear_register = 0x00;
  unsigned char ucWarn_clear_register = 0x00;   
  unsigned char ucHigh_flag;
  unsigned char ucLow_flag;
  
  
  switch (unWhich)
  { 
   case TEMP_DDM:                                                         // Laser Temp
                 pThreshold_ptr = &TEMP_ALARM_HI;                           //get ptr for hi alarm, this is the first parameter in memory map
                 ucHigh_flag = TEMP_HIGH_FLAG;                                //this is the proper status flag to set
                 ucLow_flag = TEMP_LOW_FLAG;
                 break;       
    
    
   case LASER_TEMP_DDM:                                                         // Laser Temp
                 pThreshold_ptr = &LASER_TEMP_ALARM_HI;                           //get ptr for hi alarm, this is the first parameter in memory map
                 ucHigh_flag = LASER_TEMP_HIGH_FLAG;                                //this is the proper status flag to set
                 ucLow_flag = LASER_TEMP_LOW_FLAG;
                 break;   
             
   case TEC_CURRENT_DDM:                                                        // RX power  
                 pThreshold_ptr = &TECC_ALARM_HI;
                 ucHigh_flag = TEC_CURRENT_HIGH_FLAG;
                 ucLow_flag = TEC_CURRENT_LOW_FLAG;
                 break;                 
                   
   default: 
                 sDdm_value = 0;
                 pThreshold_ptr = &LASER_TEMP_ALARM_HI;                           //give some value
                 ucHigh_flag = 0x00;                                                //will not set any flags
                 ucLow_flag = 0x00;
                 break;
  }
  
  // high alarm comparison
  unThreshold = __swap_bytes(*pThreshold_ptr);                                      //read unThreshold
  if (sDdm_value > unThreshold)
  {
    ucAlarm_register |= ucHigh_flag;
  }
  else
  {
    ucAlarm_clear_register |= ucHigh_flag;
  } 
  
  // low alarm comparison
  pThreshold_ptr++;                                                               //increment to the next unThreshold
  unThreshold = __swap_bytes(*pThreshold_ptr);                                      //read unThreshold
  if (sDdm_value < unThreshold)
  {
    ucAlarm_register |= ucLow_flag;
  }
  else
  {
    ucAlarm_clear_register |= ucLow_flag;
  } 
  
  //high warning comparison
  pThreshold_ptr++;                                                               //increment to the next unThreshold
  unThreshold = __swap_bytes(*pThreshold_ptr);
  if (sDdm_value > unThreshold)
  {
    ucWarn_register |= ucHigh_flag;
  }
  else
  {
    ucWarn_clear_register |= ucHigh_flag;
  }
  
  //low warning comparison
  pThreshold_ptr++;                                                               //increment to the next unThreshold
  unThreshold = __swap_bytes(*pThreshold_ptr);
  if (sDdm_value < unThreshold)
  {
    ucWarn_register |= ucLow_flag;
  }  
  else
  {
    ucWarn_clear_register |= ucLow_flag;
  }
  
  //store alarms and warnings back
  if(unWhich == TEMP_DDM)
  {
    if(PAGE90H_Memory.AW_MODE & AW_MODE_LATCHED_EN)
    {    
      __disable_interrupt();                                                      //disable so I2C interrupt to clear doesn't corrupt data
      ALARM3 |= ucAlarm_register;                                                        //add these bits to existing alarms
      WARN3  |= ucWarn_register;    
      __enable_interrupt();
      
      s_ucReal_time_ALARM3 |= ucAlarm_register;                                                      
      s_ucReal_time_WARN3  |= ucWarn_register;   
      s_ucReal_time_ALARM3 &= ~ucAlarm_clear_register;                                                       
      s_ucReal_time_WARN3  &= ~ucWarn_clear_register;         
      
    }
    else
    {
      ALARM3 |= ucAlarm_register;                                                      
      WARN3  |= ucWarn_register;   
      ALARM3 &= ~ucAlarm_clear_register;                                                       
      WARN3  &= ~ucWarn_clear_register;               
    }
  }
  else
  {
    if(PAGE90H_Memory.AW_MODE & AW_MODE_LATCHED_EN)
    {   
      __disable_interrupt();                                                      //disable so I2C interrupt to clear doesn't corrupt data
      ALARM2 |= ucAlarm_register;                                                        //add these bits to existing alarms
      WARN2 |= ucWarn_register;
      __enable_interrupt();
      
      s_ucReal_time_ALARM2 |= ucAlarm_register;                                                      
      s_ucReal_time_WARN2  |= ucWarn_register;   
      s_ucReal_time_ALARM2 &= ~ucAlarm_clear_register;                                                       
      s_ucReal_time_WARN2  &= ~ucWarn_clear_register;         
    }
    else
    {
      ALARM2 |= ucAlarm_register;                                                      
      WARN2  |= ucWarn_register;   
      ALARM2 &= ~ucAlarm_clear_register;                                                       
      WARN2  &= ~ucWarn_clear_register;               
    }    
  }  
#endif

}

void TXF_AlarmWarn_Check(void)
{
#if __SFP28_ER__ == 1
#else
  unsigned char temp = 0;
  unsigned char state = 0;
  
  temp = ALARM3 & ~PAGE90H_Memory.TXF_ALARM3MASK;
  if(temp != 0)
  {
    state |= 0x80;
  }
  temp = ALARM2 & ~PAGE90H_Memory.TXF_ALARM2MASK;
  if(temp != 0)
  {
    state |= 0x40;
  }   
  
  temp = WARN3 & ~PAGE90H_Memory.TXF_WARN3MASK;
  if(temp != 0)
  {
    state |= 0x20;
  }

  temp = WARN2 & ~PAGE90H_Memory.TXF_WARN2MASK;
  if(temp != 0)
  {
    state |= 0x10;
  }
  __disable_interrupt();
  s_ucTXF_status |= state;
  __enable_interrupt();
    
  if(PAGE90H_Memory.TXF_CONTROL & TXF_AW_EN)
  {  
    
    if(s_ucTXF_status != 0)
    {
      PLACNT3_bit.SB1 = 1;
    }
    else
    {
      PLACNT3_bit.SB1 = 0;
    }      
      
  }
#endif
   
}

void Clear_TXF_Status(void)
{
#if __SFP28_ER__ == 1
  
#if __SFP28_ER_SEMI_TUNABLE__ == 1

  // TX Fault: GP23
  __disable_interrupt();  
  
  PLA_Soft_Tx_Fault_Control(DE_ASSERTED);
  
//  s_ucTXF_status = 0;
//  WARN3  = s_ucReal_time_WARN3;
//  WARN2  = s_ucReal_time_WARN2;
//  ALARM3 = s_ucReal_time_ALARM3;
//  ALARM2 = s_ucReal_time_ALARM2;            
  __enable_interrupt(); 
  
#else
  
#endif
  
#else
  __disable_interrupt();  
  s_ucTXF_status = 0;
  WARN3  = s_ucReal_time_WARN3;
  WARN2  = s_ucReal_time_WARN2;
  ALARM3 = s_ucReal_time_ALARM3;
  ALARM2 = s_ucReal_time_ALARM2;            
  __enable_interrupt(); 
#endif
}



//-----------------------------------------------------------------------------
// end of file
//-----------------------------------------------------------------------------


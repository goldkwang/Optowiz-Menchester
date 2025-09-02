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
// includes
//-----------------------------------------------------------------------------
#include <intrinsics.h>
#include <iods4835.h>
#include <stdio.h>
#include <string.h>
#include "includes.h"

//-----------------------------------------------------------------------------
// static variables defined in this module
//-----------------------------------------------------------------------------

//static unsigned char s_ucModule_state = STATE_POR;


//-----------------------------------------------------------------------------
// StateMachine function
//   - Module statemachine
//-----------------------------------------------------------------------------
void StateMachine(void)
{
#if __SFP28_ER__ == 1
  
  state_transition_control();
  
#else
  
  unsigned int unPower=0;
  signed int sTemp=0;
  unsigned int unAdc=0,ucTarget = 0;
  unsigned int unControl = 0;
  unsigned char ucPmic = 0;
  static unsigned int s_unCount=0;
  
  unControl = __swap_bytes(PAGE90H_Memory.CONTROL);

  switch(s_ucModule_state)
  {
     case STATE_POR:

                        unPower = __swap_bytes(VCC);                               
                         
                        if(unPower > 28500)                                     //Check if VCC(>2.85V) is stable
                        {
                          if(s_unCount < 10)                                    //10times
                          {
                            
                            s_unCount++;
                            
                          }
                          else
                          {
                            
                            s_unCount = 0;

                            INRUSH_Init();                                      // Disable Inrush current limitation 
                            s_ucModule_state = STATE_DCDC_INIT;                 //Move to next state

                          }
                          
                         }
     
                         break;
                        
     case STATE_DCDC_INIT:                        

                         DCDC_Init();                                           //DCDC Init

                         SW_Delay(2000);                                        //delay for ramping 
                         
                         s_ucModule_state = STATE_INV_INIT;                     //move to next step
                         
                         break;

     case STATE_INV_INIT:                        

                         INV_Init();                                            //INV init

                         SW_Delay(5000);                                        //delay for ramping (load internal Kp, Ki for initialization)
                         
                         s_ucModule_state = STATE_IDAC_INIT;                    //move to next step
                         
                         break;                         
                         
     case STATE_IDAC_INIT:                        
                         
                         IDAC_Init();                                           //IDAC init
                         
                         SW_Delay(2000);
                         
                         INV_Update_KPKI();                                     //Update Kp Ki(stored in FLash) after INV DCDC initialization
                         
                         DSDAC_Init();                                          //DS-DAC init
                         
                         s_ucModule_state = STATE_APD_INIT;                     //move to next step
                         
                         break; 
                         
     case STATE_APD_INIT:                        
                                                
                         APD_Init();                                            //APD init
                        
                         SW_Delay(2000);
                         
                         s_ucModule_state = STATE_TEC_INIT;                     //move to next step
                         
                         break;
                        
     case STATE_TEC_INIT:
                                                      
                        
                        if(PAGEA0H_Memory.ADC_VTHERM2_READOUT != 0)             //Check if Vtherm is ready, then enable TEC
                        { 

                           TEC_Init();                                          //TEC init
                         
                           SW_Delay(1000); 
                           
                           s_ucModule_state = STATE_APD_LUT_INIT;               //Move to next state
                         
                         }
      
                         break;       
       
     case STATE_APD_LUT_INIT:
                      
                        sTemp = (signed int)__swap_bytes((unsigned int)TEMPERATURE);                               
                         
                        if(sTemp != 0)                                          //Check if VCC is stable
                        { 
                           LUT_APD_Process(sTemp);                              //Init APD lut loop
    
                           s_ucModule_state = STATE_DRIVER_INIT;                //Move to next state
                    
                         }
     
                         break;
              
     case STATE_DRIVER_INIT:
 
                         Driver_Init(DRIVER_SLAVE_ADDR, &DRIVER_Memory);        //Driver init
                         s_ucModule_state = STATE_TEC_STABLE;                   //Move to next state

                         break;       

     case STATE_TEC_STABLE:
       
                         
                         ucPmic = PAGE91H_Memory.PMIC_SELECT;
                         
                         if(ucPmic & TEC2_ENABLE)                               //if TEC is enabled, wait for TEC stability
                         {
                         
                             unAdc = __swap_bytes(PAGEA0H_Memory.ADC_VTHERM2_READOUT); //read current laser temperature ADC
                                                                                
                             if((unAdc < __swap_bytes(PAGE91H_Memory.TEC2_SETPOINT)+200)&&(unAdc > __swap_bytes(PAGE91H_Memory.TEC2_SETPOINT)- 200))//compare with setpoint
                             {                           
                               s_unCount++;                         
                             }
                             else
                             {                               
                               s_unCount = 0;                                                                  
                             }
                             
                             if(s_unCount > 5)                                  //if ADC is stable
                             {
                               
                               s_unCount = 0;
                               
                               APC_Init();                                      //init APC
                               
                               s_ucModule_state = STATE_APC_RAMP;               //move to next step                               
                                 
                             }
                        }
                        else                                                    //if TEC is disabled
                        {
                          
                          APC_Init();                                           //init APC                  
                          
                          s_ucModule_state = STATE_APC_RAMP;                    //move to next step                    
                          
                        }

                         break;                          

     case STATE_APC_RAMP:

                         if((unControl & APC_ENABLE)&&(TXDStatus() == DE_ASSERTED))//if APC is enable and TXD is de-asserted
                         {
                                               
                             APC_Process();                                     //APC processing
                             
                             unAdc = __swap_bytes(PAGEA0H_Memory.ADC_TX_POWER); //Read txpower unAdc
                             APCIDX1  = APC_INDEX_APC_TARGET;                   //Read current APC ucTarget   
                             ucTarget = APCDATA1;
                             
                             //compare the ADC and the Target
                             if(((ucTarget > unAdc)&&((ucTarget-unAdc)<APC_ERROR))||\
                                ((ucTarget < unAdc)&&((unAdc-ucTarget)<APC_ERROR)))
                             {                                             
                               s_unCount++;                         
                             }
                             else
                             {
                                s_unCount = 0;
                             }
                               
                             if(s_unCount > 5)                                  //if ADC is stable
                             {
                               
                               s_unCount = 0;
                               s_ucModule_state = STATE_MOD_INIT;               //move to next step       
                               
                                                              
                             }
                         }
                         else                                                   //if APC is disabled or TXD is asserted
                         {
                           
                           s_unCount = 0;                          
                           s_ucModule_state = STATE_MOD_INIT;                   //move to next step
                        
                         }
                             
                         break; 
                         
     case STATE_MOD_INIT:     
       
                         sTemp = (signed int)__swap_bytes((unsigned int)TEMPERATURE); //read current temperature   
                               
                         LUT_MOD_Process(sTemp);                                //Init MOD lut loop
                         
                         TXD_External_Interrupt_init();                         //Init TXD interrupt
                         
                         IMR_bit.IM0 = 1;                                       //External interrupt enable(TXD)
                         IMR_bit.IM4 = 1;                                       //SH module interrupt enable  
                         
                         s_ucModule_state = STATE_NORMAL_OPERATION;             //move to next step
                         
                         break;

     case STATE_NORMAL_OPERATION:
        
                         
                         APC_Process();                                         //APC processing
                         
                         sTemp = (signed int)__swap_bytes((unsigned int)TEMPERATURE); //read current temperature
                         
                         LUT_Process(sTemp);                                    //Loop
                         
                         MonitorModuleStatus();                                 //Monitor module status                      
                           
                         break;    

                default:
                         break;
  }
  
  PAGEA0H_Memory.STATE_MACHINE_STATE = s_ucModule_state;                        //update current status to readout table
  UpdateByteA2hTable(PAGE_A0H,&PAGEA0H_Memory.STATE_MACHINE_STATE, s_ucModule_state);//udpate A2h higher memory if the current table is A0h  


#endif

}

#if __SFP28_ER__== 1

#else
#endif


//-----------------------------------------------------------------------------
// end of file
//-----------------------------------------------------------------------------


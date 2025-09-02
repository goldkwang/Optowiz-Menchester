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


//------------------------------------------------------------------------------
// MonitorTXD Function
//      - Monitor txd status 
//------------------------------------------------------------------------------
void MonitorTXD(void)
{
#if __SFP28_ER__ == 1
  
#if __SFP28_ER_SEMI_TUNABLE__ == 1
  if(TXDStatus() == DE_ASSERTED)                                                //if TXD is de-asserted
  {
    
  }
  
#endif
  
#else

  if(TXDStatus() == DE_ASSERTED)                                                //if TXD is de-asserted
  {
    
#ifdef DCDC_BIASING                                                             //DCDC Biasing
    
    if( PAGE91H_Memory.PMIC_SELECT & BUCK2_ENABLE )                             //need re-enable DCDC2 and Apc again after TXD de-asserted
    {
       DCDC_SEL = DC_DC_CH2;                                                    //select DCDC2
       DCCN = DCCNSET;                                                          //reset DCDC set if the current less than 200mA, note: The DC-DC ramp should allow to startup DC for >200mA startup load for various DC_DC target output.
       APC_Init();                                                              //init APC
       
    }
    
#else                                                                           //IDAC Biasing
    
    if( PAGE91H_Memory.PMIC_SELECT & BUCK1_ENABLE )                             //need re-enable APC
    {    
      APC_Init();                                                               //init APC
    }
    
#endif
    
  }
    
#endif

}


//------------------------------------------------------------------------------
// TXDStatus Function
//      - return the current tx disable stutus(including soft txdisable)
//------------------------------------------------------------------------------
unsigned char TXDStatus(void)
{
#if __SFP28_ER__ == 1
#if __SFP28_ER_SEMI_TUNABLE__ == 1
  unsigned char ucStatus = DE_ASSERTED;
  
  if(PLACNT1_bit.PLA_OUT == 1)                                                  //if TXD is asserted
  {
    ucStatus = ASSERTED;                                                        //update the TXD status
  }
  else
  {

    ucStatus = DE_ASSERTED;                                                     //update the TXD status
  }
  
  return ucStatus; 
  
#else
  return 0;
#endif
  
#else
  
  unsigned char ucStatus = DE_ASSERTED;
  
  if(PLACNT1_bit.PLA_OUT == 1)                                                  //if TXD is asserted
  {
    ucStatus = ASSERTED;                                                        //update the TXD status
  }
  else
  {

    ucStatus = DE_ASSERTED;                                                     //update the TXD status
  }
  
  return ucStatus; 
#endif
  
}

//------------------------------------------------------------------------------
// MonitorTXF Function
//      - Check the tx fault status
//------------------------------------------------------------------------------
void MonitorTXF(void)
{
#if __SFP28_ER__ == 1
#else

  if(DRIVER_Memory.TOPSTAT & 0x01)                                            //read current TXF status from max24016
  {
    PLACNT3_bit.SB2 = 1;                                                        //set PLA3.SB2 to 1 for TXF assert
  }
  else
  {
    PLACNT3_bit.SB2 = 0;                                                        //set PLA3.SB2 to 0 for TXF DE-assert(from max24016 side)
  }  
  
  if(PAGE90H_Memory.TXF_CONTROL & TXF_TXD_EN)                                   //if TXF triggers TXD is enabled
  {
    if(PLACNT3_bit.PLA_OUT == 1)                                                //if TX Fault is asserted
    {
      PLACNT1_bit.SB2 = 1;                                                      //set TX disable
      
#ifndef DCDC_BIASING                                                            //DCDC biasing
           
      IDCD1 = 0;                                                                //Write 0 to IDAC    
#endif   
      
    }
    else                                                                        //TXF is de-asserted
    {
      if(PLACNT1_bit.SB2 == 1)                                                  //if soft control 2 of TXD is asserted(this is set by TXF if TXF_TXD_EN is enabled and TXF is asserted)                                 
      {
        PLACNT1_bit.SB2 = 0;                                                    //clear PLA SB2 When TXF is de-asserted
        
        if(TXDStatus() == DE_ASSERTED)                                          //if TXD is de-asserted
        {
          
#ifdef DCDC_BIASING  
          
          if( PAGE91H_Memory.PMIC_SELECT & BUCK2_ENABLE )                       //need re-enable DCDC2 again after TXD de-asserted
          {
             DCDC_SEL = DC_DC_CH2;                                              //select DCDD2
             DCCN = DCCNSET;                                                    //re-enable DCDC2
             APC_Init();                                                        //APC init again 
             
          }
          
#else            
          if( PAGE91H_Memory.PMIC_SELECT & BUCK1_ENABLE )                       //need re-enable DCDC1 again after TXD de-asserted
          {    
            APC_Init();                                                         //APC init again 
          }
          
#endif

        }

      }
    }

  }
#endif

}

//------------------------------------------------------------------------------
// MonitorPINStauts Function
//      - Check the pins status
//------------------------------------------------------------------------------
void MonitorPINStauts(void)
{
#if __SFP28_ER__ == 1


#else
  unsigned char ucState = 0;

  //TXD GP07
  if(PI0 & 0x080)                                                               //pin status of TXD
  {
    ucState |= 0x80;
  }

  //TX Fault GP02
  if(PI0 & 0x004)                                                               //pin status of TXF
  {
    ucState |= 0x04;
  }  
  
  //RXLOS GP01
  if(PI0 & 0x002)                                                               //pin status of RX Los
  {
    ucState |= 0x02;
  }  

  __disable_interrupt();                                                        
  if(PLACNT1_bit.SB1 == 1)                                                      //soft disable status
  {
    ucState |= 0x40;
  }
  STATUS_CONTROL_6E = ucState;                                                  //update to 0x6E
  __enable_interrupt();
#endif
}



//------------------------------------------------------------------------------
// MonitorTECStauts Function
//      - read current tec pwm duty, this value can be read by Host
//------------------------------------------------------------------------------
void MonitorTECStauts(void)
{
#if __SFP28_ER__ == 1
#else
  unsigned int unTEC_duty = 0;
  
  unTEC_duty = GetTec2(INDEX_TEC_PWMDUTY);                                      //get current duty of TEC
  
  PAGEA0H_Memory.TEC2_PWM_DUTY= __swap_bytes(unTEC_duty);                       //update to readout page
  UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.TEC2_PWM_DUTY, unTEC_duty);   
#endif
}




//------------------------------------------------------------------------------
// MonitorMAX24016Status Function
//      - Update realtime status of max24016
//------------------------------------------------------------------------------
void MonitorDriverStatus(void)
{
#if __SFP28_ER__ == 1
#else
  static unsigned char s_ucStep = 0;
  
  switch(s_ucStep)
  {

    case 0:   
             //Read Top stat Register
             Driver_ReadTOPSTAT(DRIVER_SLAVE_ADDR, &DRIVER_Memory);             
             UpdateByteA2hTable(PAGE_80H,&DRIVER_Memory.TOPSTAT,DRIVER_Memory.TOPSTAT);  
             s_ucStep = 1;
             break;
     
    case 1:   
             //Read Tx stat Register
             Driver_ReadTXSTAT(DRIVER_SLAVE_ADDR, &DRIVER_Memory);             
             UpdateByteA2hTable(PAGE_80H,&DRIVER_Memory.TXSTAT,DRIVER_Memory.TXSTAT);  
             s_ucStep = 2;
             break;
             
    case 2:   
             //Read RX stat Register
             Driver_ReadRXSTAT(DRIVER_SLAVE_ADDR, &DRIVER_Memory);             
             UpdateByteA2hTable(PAGE_80H,&DRIVER_Memory.RXSTAT,DRIVER_Memory.RXSTAT);    

             s_ucStep = 3;
             break;
    
    case 3:   
             //Read stat Register
             Driver_StatusRegsRead(DRIVER_SLAVE_ADDR, &DRIVER_Memory);
             
             UpdateByteA2hTable(PAGE_80H,&DRIVER_Memory.PINSTAT,DRIVER_Memory.PINSTAT);    
             UpdateByteA2hTable(PAGE_80H,&DRIVER_Memory.FAULTSTAT1,DRIVER_Memory.FAULTSTAT1);    
             UpdateByteA2hTable(PAGE_80H,&DRIVER_Memory.FAULTSTAT2,DRIVER_Memory.FAULTSTAT2);    
             UpdateByteA2hTable(PAGE_80H,&DRIVER_Memory.DDMSTAT15,DRIVER_Memory.DDMSTAT15);    
             UpdateByteA2hTable(PAGE_80H,&DRIVER_Memory.DDMSTAT16,DRIVER_Memory.DDMSTAT16);    
             UpdateByteA2hTable(PAGE_80H,&DRIVER_Memory.DDMSTAT17,DRIVER_Memory.DDMSTAT17);    
             UpdateByteA2hTable(PAGE_80H,&DRIVER_Memory.DDMSTAT18,DRIVER_Memory.DDMSTAT18); 
             UpdateByteA2hTable(PAGE_80H,&DRIVER_Memory.RXPU,DRIVER_Memory_Readout.RXPU);
             s_ucStep = 0;
             break;        
     
    default:
            break;
      
      
  }
#endif

}


//------------------------------------------------------------------------------
// MonitorMAX24016RegsReadOut Function
//      - Update all realtime value of max24016 register if this function is 
//        enabled.
//------------------------------------------------------------------------------
void MonitorDriverRegsReadOut(void)
{
#if __SFP28_ER__ == 1
#else
  static unsigned char s_ucStep = 0;
  
  if(__swap_bytes(PAGE90H_Memory.MODULE_CONTROL1) & MON_DRIVER_REGS_EN)         //if driver regs monitor function is enable, this is for debugging use only.                                
  {
    switch(s_ucStep)
    {
  
      case 0:   
               //Read Top stat Register
               Driver_ReadTOPSTAT(DRIVER_SLAVE_ADDR, &DRIVER_Memory_Readout);               
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.TOPSTAT,DRIVER_Memory_Readout.TOPSTAT);  
               s_ucStep = 1;
               break;
       
      case 1:   
               //Read Tx stat Register
               Driver_ReadTXSTAT(DRIVER_SLAVE_ADDR, &DRIVER_Memory_Readout);              
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.TXSTAT,DRIVER_Memory_Readout.TXSTAT);  
               s_ucStep = 2;
               break;
               
      case 2:   
               //Read RX stat Register
               Driver_ReadRXSTAT(DRIVER_SLAVE_ADDR, &DRIVER_Memory_Readout);               
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.RXSTAT,DRIVER_Memory_Readout.RXSTAT);    
  
               s_ucStep = 3;
               break;
       
      case 3:   
               //Read stat Register
               Driver_StatusRegsRead(DRIVER_SLAVE_ADDR, &DRIVER_Memory_Readout);
               
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.PINSTAT,DRIVER_Memory_Readout.PINSTAT);    
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.FAULTSTAT1,DRIVER_Memory_Readout.FAULTSTAT1);    
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.FAULTSTAT2,DRIVER_Memory_Readout.FAULTSTAT2);    
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.DDMSTAT15,DRIVER_Memory_Readout.DDMSTAT15);    
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.DDMSTAT16,DRIVER_Memory_Readout.DDMSTAT16);    
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.DDMSTAT17,DRIVER_Memory_Readout.DDMSTAT17);    
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.DDMSTAT18,DRIVER_Memory_Readout.DDMSTAT18); 
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.RXPU,DRIVER_Memory_Readout.RXPU);
               s_ucStep = 4;
               
               break;             
  
      case 4:   
               //Read control Register
               Driver_ControlRegsRead(DRIVER_SLAVE_ADDR, &DRIVER_Memory_Readout);
               
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.FAULTCTRL,DRIVER_Memory_Readout.FAULTCTRL);    
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.FAULTMASK1,DRIVER_Memory_Readout.FAULTMASK1);    
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.FAULTMASK2,DRIVER_Memory_Readout.FAULTMASK2); 
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.TOPCTRL,DRIVER_Memory_Readout.TOPCTRL); 
               
               s_ucStep = 5;              
               
               break;
       
      case 5:   
               //Read Tx Register
               Driver_TXRegsRead(DRIVER_SLAVE_ADDR, &DRIVER_Memory_Readout);
           
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.SET_MOD0,DRIVER_Memory_Readout.SET_MOD0);  
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.SET_MOD1,DRIVER_Memory_Readout.SET_MOD1);
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.MODMAX,DRIVER_Memory_Readout.MODMAX);
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.APCCTRL1,DRIVER_Memory_Readout.APCCTRL1);
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.APCCTRL2,DRIVER_Memory_Readout.APCCTRL2);
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.SET_APC0,DRIVER_Memory_Readout.SET_APC0);
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.SET_APC1,DRIVER_Memory_Readout.SET_APC1);
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.SET_BIAS0,DRIVER_Memory_Readout.SET_BIAS0);
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.SET_BIAS1,DRIVER_Memory_Readout.SET_BIAS1);
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.BIASMAX,DRIVER_Memory_Readout.BIASMAX);
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.MPDMAX,DRIVER_Memory_Readout.MPDMAX);
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.LDOCTRL,DRIVER_Memory_Readout.LDOCTRL);               
               
               s_ucStep = 6;
               
               break;
               
      case 6:   
               //Read RX Register
               Driver_RXRegsRead(DRIVER_SLAVE_ADDR, &DRIVER_Memory_Readout);

               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.RXCTRL1,DRIVER_Memory_Readout.RXCTRL1);  
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.RXCTRL2,DRIVER_Memory_Readout.RXCTRL2);
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.RXCTRL3,DRIVER_Memory_Readout.RXCTRL3);
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.RXCTRL4,DRIVER_Memory_Readout.RXCTRL4);
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.RXLOS1,DRIVER_Memory_Readout.RXLOS1);
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.RXLOS2,DRIVER_Memory_Readout.RXLOS2);
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.RXLOS3,DRIVER_Memory_Readout.RXLOS3);
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.RXLOS4,DRIVER_Memory_Readout.RXLOS4);
               
               s_ucStep = 7;
               
               break;
       
      case 7:   
               //Read tx control Register
               Driver_TXControlRegsRead(DRIVER_SLAVE_ADDR, &DRIVER_Memory_Readout);
               
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.TXCTRL1,DRIVER_Memory_Readout.TXCTRL1);  
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.TXCTRL2,DRIVER_Memory_Readout.TXCTRL2);
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.TXCTRL3,DRIVER_Memory_Readout.TXCTRL3);
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.TXCTRL4,DRIVER_Memory_Readout.TXCTRL4);
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.TXCTRL5,DRIVER_Memory_Readout.TXCTRL5);
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.TXCTRL6,DRIVER_Memory_Readout.TXCTRL6);
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.TXCTRL7,DRIVER_Memory_Readout.TXCTRL7);
               UpdateByteA2hTable(PAGE_81H,&DRIVER_Memory_Readout.TXCTRL8,DRIVER_Memory_Readout.TXCTRL8);               
               
               s_ucStep = 0;
               
               break;              
               
      default :
               s_ucStep = 0;
               
               break;               
               
    }
  }
#endif

}

//------------------------------------------------------------------------------
// MonitorRXLOS Function
//      - Monitor RX los with RSSI
//------------------------------------------------------------------------------
void MonitorRXLOS(void)
{
#if __SFP28_ER__ == 1
#if __SFP28_ER_SEMI_TUNABLE__ == 1
  
//  unsigned int RSSI_DEASSERTED_TH = 0;
//  unsigned int RSSI_ASSERTED_TH = 0;  
//  unsigned int RSSI = 0;
//  
//  if(__swap_bytes(PAGE90H_Memory.MODULE_CONTROL1) & RXLOS_EN)                   //if RX LOS is enabled?
//  {
//    
//    RSSI_DEASSERTED_TH = __swap_bytes(PAGE90H_Memory.RXLOS_DEASSERT_TH);        //read RX LOS de-asserted threshold
//    RSSI_ASSERTED_TH   = __swap_bytes(PAGE90H_Memory.RXLOS_ASSERT_TH);          //read RX LOS asserted threshold
//    RSSI =  __swap_bytes(RX_POWER);                                             //read current RX power
//    
//    if(PLACNT2_bit.SB1 == 0)                                                    //if RX LOS PLA SB1 equals 0, means RX LOS is de-asserted                                       
//    {
//      if(RSSI < RSSI_ASSERTED_TH)                                               //compare with asserted threshold
//      {
//        PLACNT2_bit.SB1 = 1;                                                    //RX LOS assert
//      }
//    }
//    else                                                                        //RX LOS is de-asserted
//    {
//      if(RSSI >= RSSI_DEASSERTED_TH)                                            //compare with de-asserted threshold
//      {
//        PLACNT2_bit.SB1 = 0;                                                    //RX LOS de-assert
//      }
//    }
//  }

#endif
  
#else
  
  unsigned int RSSI_DEASSERTED_TH = 0;
  unsigned int RSSI_ASSERTED_TH = 0;  
  unsigned int RSSI = 0;
  
  if(__swap_bytes(PAGE90H_Memory.MODULE_CONTROL1) & RXLOS_EN)                   //if RX LOS is enabled?
  {
    
    RSSI_DEASSERTED_TH = __swap_bytes(PAGE90H_Memory.RXLOS_DEASSERT_TH);        //read RX LOS de-asserted threshold
    RSSI_ASSERTED_TH   = __swap_bytes(PAGE90H_Memory.RXLOS_ASSERT_TH);          //read RX LOS asserted threshold
    RSSI =  __swap_bytes(RX_POWER);                                             //read current RX power
    
    if(PLACNT2_bit.SB1 == 0)                                                    //if RX LOS PLA SB1 equals 0, means RX LOS is de-asserted                                       
    {
      if(RSSI < RSSI_ASSERTED_TH)                                               //compare with asserted threshold
      {
        PLACNT2_bit.SB1 = 1;                                                    //RX LOS assert
      }
    }
    else                                                                        //RX LOS is de-asserted
    {
      if(RSSI >= RSSI_DEASSERTED_TH)                                            //compare with de-asserted threshold
      {
        PLACNT2_bit.SB1 = 0;                                                    //RX LOS de-assert
      }
    }
  }
#endif
}


//------------------------------------------------------------------------------
// MonitorModuleStatus Function
//      - Monitor module's status
//------------------------------------------------------------------------------
void MonitorModuleStatus(void)
{
#if __SFP28_ER__ == 1
  
  MonitorTECStauts();                                                           //monitor TEC status(current duty)
  
  MonitorTXF();                                                                 //monitor TX fault
  
  MonitorPINStauts();                                                           //monitor pins status
  
  MonitorDriverStatus();                                                        //monitor Driver(max24016) status
  
  MonitorDriverRegsReadOut();                                                   //monitor Dirver(max24016) realtime regs, if this function is enabled
  
#else
  
  MonitorTECStauts();                                                           //monitor TEC status(current duty)
  
  MonitorTXF();                                                                 //monitor TX fault
  
  MonitorPINStauts();                                                           //monitor pins status
  
  MonitorDriverStatus();                                                        //monitor Driver(max24016) status
  
  MonitorDriverRegsReadOut();                                                   //monitor Dirver(max24016) realtime regs, if this function is enabled
  
#endif
  
}




//-----------------------------------------------------------------------------
// end of file
//-----------------------------------------------------------------------------


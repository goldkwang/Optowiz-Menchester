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
#include <string.h>
#include "includes.h"


//-----------------------------------------------------------------------------
// APC_Init function
//   - APC initialize function, the init bias is got from BIAS LUT
//-----------------------------------------------------------------------------
void APC_Init(void)
{     
#if __SFP28_ER__ == 1

#else

  
  unsigned int unControl;
  unsigned int unLut_data;
    signed int iTemp = 0;
  static unsigned int s_unOld_control = 0;
  
  APCCN1   = 0;                                                                 //disable APC
  
  unControl = __swap_bytes(PAGE90H_Memory.CONTROL);                             //read current control status
  
  if(unControl & APC_ENABLE)                                                    //if APC is enabled and TXD is deasserted, then implement following code
  {    
    if(TXDStatus() == DE_ASSERTED)
    {
   
      APCCN1_bit.APCI = 0;                                                      //Clear APC flag

      
#ifdef DCDC_BIASING                                                             //DCDC biasing
      
       if(unControl & INIT_BIAS_LUT_ENABLE)                                     //check INIT_BIAS_LUT is enabled?
       {
         iTemp = (signed int)__swap_bytes((unsigned int)TEMPERATURE);           //get current module temperature
         unLut_data = INIT_BIAS_LUT(iTemp);                                     //look up table
       }
       else
       {
         unLut_data = __swap_bytes(PAGE90H_Memory.DCDC2_APC1_INITBIAS);         //if INIT_BIAS_LUT loop is not enabled, get the APC init bias from DCDC2_APC1_INITBIAS    
       }
    
       write_bias(unLut_data/2);
       SW_Delay(500);
       write_bias(unLut_data);
       
       APCIDX1  = APC_INDEX_APC_INITBIAS;                                       //configure APC INIT BIAS   
       APCDATA1  = unLut_data;  
       
       APCIDX1  = APC_INDEX_APC_TARGET;                                         //configure APC TARGET  
       APCDATA1 = __swap_bytes(PAGE90H_Memory.DCDC2_APC1_TARGET);
       APCIDX1  = APC_INDEX_APC_MAXBIAS;
       APCDATA1 = __swap_bytes(PAGE90H_Memory.DCDC2_APC1_MAXBIAS);              //configure APC MAX BIAS   
       APCIDX1  = APC_INDEX_APC_I_STEP;
       APCDATA1 = __swap_bytes(PAGE90H_Memory.DCDC2_APC1_I_STEP);               //configure APC I STEP   
       
       APCCN1   = APCCN_CONFIG;                                                 //configure APC control
       APCCN1_bit.APCCONV = 1;                                                  //enable APC convert 
       
#else                                                                           //IDAC Biasing
       
       if(unControl & INIT_BIAS_LUT_ENABLE)                                     //if init_bias lut is enabled              
       {
         iTemp = (signed int)__swap_bytes((unsigned int)TEMPERATURE);           //read current temperature
         unLut_data = INIT_BIAS_LUT(iTemp);                                     //search from LUT, return result
       }
       else
       {
         unLut_data = __swap_bytes(PAGE90H_Memory.IDAC_APC1_INITBIAS);          //read from in
       }

       if(unLut_data > 205)
       {
         write_bias(unLut_data - 205);                                                //update bias step by step
       }
       else
       {
         write_bias(unLut_data/2);                                                //update bias step by step
       }
       SW_Delay(500);
       write_bias(unLut_data);
    
       APCIDX1  = APC_INDEX_APC_TARGET;                                         //Set APC target
       APCDATA1 = __swap_bytes(PAGE90H_Memory.IDAC_APC1_TARGET); 
       APCIDX1  = APC_INDEX_APC_MAXBIAS;                                        //Set Maxim Bias output
       APCDATA1 = __swap_bytes(PAGE90H_Memory.IDAC_APC1_MAXBIAS);
               
       APCIDX1  = APC_INDEX_APC_INITBIAS;                                       //Set init bias for APC
       APCDATA1  = unLut_data;  
       
       APCIDX1  = APC_INDEX_APC_I_STEP;                                         //Set apc I step
       APCDATA1 = __swap_bytes(PAGE90H_Memory.IDAC_APC1_I_STEP); 
       
       APCCN1   = APCCN_CONFIG;                                                 //enable APC
       APCCN1_bit.APCCONV = 1;                                                  //enable APC convert

#endif

    }   
  }
  else                                                                          //if APC is disabled
  {
    
    if(TXDStatus() == DE_ASSERTED)                                              //if tx disable is de-asserted
    {


#ifdef DCDC_BIASING                                                             //DCDC biasing
      
       unLut_data = __swap_bytes(PAGE91H_Memory.BUCK_DC_DC2_TARGET);            //read current target for DCDC2 , if APC is disabled  

       if(unLut_data > 500)
       {
         write_bias(unLut_data-500);
       }
       else
       {
         write_bias(unLut_data/2);
       }
       
       SW_Delay(800);
       
       write_bias(unLut_data);
       
#else                                                                           //IDAC Biasing
       
       unLut_data = __swap_bytes(PAGE90H_Memory.IDAC1_OUTPUT);                  //read current ouput for IDAC , if APC is disabled
     
       if(unLut_data > 205)
       {
         write_bias(unLut_data - 205);                                                //update bias step by step
       }
       else
       {
         write_bias(unLut_data/2);                                                //update bias step by step
       }
     
       SW_Delay(800);
      
       write_bias(unLut_data);
#endif        

#if 0        
       SW_Delay(1000);
       DS_DAC_Duty(DSDAC_CH4, __swap_bytes(PAGE90H_Memory.DS_DAC4_DPDUTY));
#endif
 
    }
    
  }

  if(unControl != s_unOld_control)                                              //if APC control is changed
  {
    //re-set Bias after APC loop is disabled
    if((s_unOld_control & APC_ENABLE)&&(~(unControl & APC_ENABLE))&&(TXDStatus() == DE_ASSERTED))
    {
      
#ifdef DCDC_BIASING
      unLut_data = __swap_bytes(PAGE91H_Memory.BUCK_DC_DC2_TARGET);             //APC loop is disabled, so update DCDC2 target from BUCK_DC_DC2_TARGET
#else
      unLut_data = __swap_bytes(PAGE90H_Memory.IDAC1_OUTPUT);                   //APC loop is disabled, so update DCDC2 target from BUCK_DC_DC2_TARGET
#endif    
                
      write_bias(unLut_data);                                                   //update bias
      
    }
    s_unOld_control = unControl;                                                //save current control status
  }
#endif
}


//-----------------------------------------------------------------------------
// APC_EnableConversion function
//   - this function will enable APC once
//-----------------------------------------------------------------------------
void APC_EnableConversion(void)
{   
#if __SFP28_ER__ == 1

#else

  APCCN1_bit.APCI    = 0;                                                       //clear apci flag
  APCCN1_bit.APCCONV = 1;                                                       //enable APC convert
#endif
}


//-----------------------------------------------------------------------------
// APC_Process function
//   - Handle APC process
//-----------------------------------------------------------------------------
void APC_Process(void)
{     
#if __SFP28_ER__ == 1

#else

  unsigned int unNew_Bias = 0;
  unsigned int unControl;
  static unsigned int s_unOld_bias = 0; 
  static unsigned int s_unCount = 0; 
  
  unControl = __swap_bytes(PAGE90H_Memory.CONTROL);                             //read current control status

#ifdef DCDC_BIASING 
  if((unControl & APC_ENABLE)&&(PAGE91H_Memory.PMIC_SELECT & BUCK2_ENABLE ))    //if APC and DCDC2 are enabled in DCDC2 Biasing mode, implement following code
#else
  if((unControl & APC_ENABLE)&&(PAGE91H_Memory.PMIC_SELECT & BUCK1_ENABLE ))    //if APC and IDAC are enabled in DCDC1 Biasing mode, implement following code
#endif
  {
    if(TXDStatus() == DE_ASSERTED)                                              //check if module is in TX disable status        
    {
      if(APCCN1_bit.APCI)                                                       //APC conversion is completed? 
      {
        APCIDX1  = APC_INDEX_APC_BIASREG;                                       //read new bias setting
        unNew_Bias = APCDATA1; 
        
        if(unNew_Bias != s_unOld_bias)                                          //if it's not equal with current setting, update bias
        {
          write_bias(unNew_Bias);                                               //update bias
          s_unOld_bias = unNew_Bias;                                            //save current setting
        }
        
        APCCN1_bit.APCI = 0;                                                    //clear APCI flag
        APCCN1_bit.APCCONV = 1;                                                 //enable APC conversion
      }
      else
      {
        s_unCount++;                                                            //count
        
        if(s_unCount > 50)                                                      //
        {
           s_unCount = 0;                                                       //clear count
           APCCN1_bit.APCI = 0;                                                 //clear APCI flag           
           APCCN1_bit.APCCONV = 1;                                              //Enable APC conversion
        }

      }
          
    }
    else
    {
      s_unOld_bias = 0;                                                         //if tx is disable, set old bias to 0
      s_unCount =0;                                                             //clear count   
    }
  }
  else
  {
    APCCN1_bit.APCI = 0;                                                        //clear APCI flag  
    APCCN1   = 0;                                                               //disable APC
    s_unOld_bias = 0;                                                           //clear old bias
    s_unCount = 0;                                                              //clear count
    
  }
#endif
}

//-----------------------------------------------------------------------------
// end of file
//-----------------------------------------------------------------------------


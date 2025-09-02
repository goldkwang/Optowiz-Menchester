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
#include "includes.h"
#include <string.h>

//-----------------------------------------------------------------------------
// global variables defined in this module
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// local function declaration
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// UpdateFromAPDLUTs Function
//      - Update APD setting with temperature index, the LUT is stored in page 
//        8A and 8B
//------------------------------------------------------------------------------
void UpdateFromAPDLUTs(unsigned int unIndex)
{
#if __SFP28_ER__== 1
#else
  
  unsigned int unLut_byte_value;
  unsigned int unControl;
  
  unControl = __swap_bytes(PAGE90H_Memory.CONTROL);                             //read current control status
 
  unIndex = unIndex<<1;                                                         //transfer to byte address
  unIndex += 0x80;                                                              //need add offset 0x80 for correct table address

  
  //do 2 degree LUTs first
  if((unControl & LUT_APD_EN) && (PAGE91H_Memory.PMIC_SELECT & APD_ENABLE))     
  {
    unLut_byte_value = GetIntFromFlash(PAGE_8AH, unIndex);                      //get new value based upon new unIndex
    
    PAGEA0H_Memory.APD_CURRENT_SETTING = __swap_bytes(unLut_byte_value);        //page A0h memory
    UpdateWordA2hTable(PAGE_A0H, &PAGEA0H_Memory.APD_CURRENT_SETTING, unLut_byte_value);//update A2h Corresponding registers when current table is A0h  
    
    unLut_byte_value = CalcExternalBoostTarget(unLut_byte_value);               //calc target for APD
    
    __disable_interrupt(); 
    APDIDX2 = IDX_TARGET;                                                       //Target Voltage
    APDDAT2 = unLut_byte_value;    
    __enable_interrupt(); 
  } 
#endif

}


//------------------------------------------------------------------------------
// UpdateFromMODLUTs Function
//      - Update modulation setting with temperature index, the LUT is stored 
//        in page 88h and 89h
//------------------------------------------------------------------------------
void UpdateFromMODLUTs(unsigned int unIndex)
{
#if __SFP28_ER__== 1
#else
 
  unsigned int unLut_byte_value;
  unsigned int unControl;
  
  unControl = __swap_bytes(PAGE90H_Memory.CONTROL);                             //read current control status
 
  unIndex = unIndex<<1;                                                         //transfer to byte address
  unIndex += 0x80;                                                              //need add offset 0x80 for correct table address

  //do 2 degree LUTs first
#ifdef DCDC_BIASING  
  if((unControl & LUT_MOD_EN) && (PAGE91H_Memory.PMIC_SELECT & BUCK2_ENABLE))    
#else
  if((unControl & LUT_MOD_EN) && (PAGE91H_Memory.PMIC_SELECT & BUCK1_ENABLE))    
#endif
  {
    unLut_byte_value = GetIntFromFlash(PAGE_88H, unIndex);                      //get new value based upon new index
    PAGEA0H_Memory.MOD_CURRENT_SETTING = __swap_bytes(unLut_byte_value);        //page A0h memory
    UpdateWordA2hTable(PAGE_A0H, &PAGEA0H_Memory.MOD_CURRENT_SETTING, unLut_byte_value);//update A2h Corresponding registers when current table is A0h  
    
    write_mod(unLut_byte_value);                                                //update mod
    
  } 

#endif

}

//------------------------------------------------------------------------------
// INIT_BIAS_LUT Function
//      - Search and return init bias from Bias LUT with temperature Index
//------------------------------------------------------------------------------
unsigned int INIT_BIAS_LUT(signed int sTemp_value)
{
#if __SFP28_ER__== 1
//  unsigned int unTemp_index = 0;  
  unsigned int unLut_byte_value = 0;

  return  unLut_byte_value;

#else
 
  unsigned int unTemp_index = 0;  
  unsigned int unLut_byte_value = 0;

  sTemp_value = sTemp_value >> 8;                                               //get a truncated integer
  
  if(sTemp_value < -40)                                                         //-40 is the minimum range
  {
    sTemp_value = -40;
  }
  if(sTemp_value > 108)                                                         //108 is the maximum range
  {
   sTemp_value = 108;
  }
   
  sTemp_value &= 0xFFFE;                                                        //only need 2 deg resolution

  sTemp_value = sTemp_value >> 2;                                               //divide by 4 because 4 deg steps
  sTemp_value += 20;                                                            //becuase LUT starts at -40C, 2deg steps  
  unTemp_index = (unsigned char)sTemp_value;                                    //change to char
  
  PAGEA0H_Memory.BIAS_TINDEX =  __swap_bytes(unTemp_index);                     //udpate a0h
  UpdateWordA2hTable(PAGE_A0H, &PAGEA0H_Memory.BIAS_TINDEX, unTemp_index);      //update A2h Corresponding registers when current table is A0h 
   
  unTemp_index = unTemp_index<<1;
  unTemp_index += 0xA0;                                                         //need add offset 0xA0 for correct table address

  unLut_byte_value = GetIntFromFlash(PAGE_89H, unTemp_index);                   //get new value based upon new index

  return  unLut_byte_value;
#endif

}



//------------------------------------------------------------------------------
// LUT_APD_Process Function
//      - Processing ADP look up table
//------------------------------------------------------------------------------
void LUT_APD_Process(signed int sTemp_value)
{
#if __SFP28_ER__== 1
#else
 
  static signed int s_sPrev_lut_temp = -50;
  unsigned int unLut_update = 0;
  unsigned int unTemp_index = 0;  
  unsigned int unData = 0;
  unsigned int unControl;
  
  unControl = __swap_bytes(PAGE90H_Memory.CONTROL);                             //read current control status
  
  //APD Lut Loop
  if(unControl & LUT_APD_EN)                                                    //check if APD lut loop is enabled?                  
  {
    
      //LUT operation
      sTemp_value = sTemp_value >> 8;                                           //get a truncated integer
      
      if(sTemp_value < -40)                                                     //-40 is the minimum range
      {
        sTemp_value = -40;
      }
      if(sTemp_value > 104)                                                     //104 is the maximum range
      {
       sTemp_value = 104;
      }
       
         
      unLut_update = 0;                                                         //assume no update needed
      
      if(sTemp_value >= (s_sPrev_lut_temp + 2  ) )                              //more than 2 deg above previous lut index, need to jump up
      {
        unLut_update = 1;
      }
      else if(sTemp_value < (s_sPrev_lut_temp - 1 ) )                           //fallen below LUT level by the hystereses amount
      {
        unLut_update = 1;
      }
      
      
      if(unLut_update)
      {
  
        sTemp_value &= 0xFFFE;                                                  //only need 2 deg resolution
        s_sPrev_lut_temp = sTemp_value;                                         //store new lut step, this should be an even number
        sTemp_value = sTemp_value >> 1;                                         //divide by 2 because 2 deg steps
        sTemp_value += 20;                                                      //becuase LUT starts at -40C, 2deg steps  
        unTemp_index = (unsigned char)sTemp_value;                              //change to char
        
        PAGEA0H_Memory.APD_TINDEX =  __swap_bytes(unTemp_index);
        UpdateWordA2hTable(PAGE_A0H, &PAGEA0H_Memory.APD_TINDEX, unTemp_index);
        
        UpdateFromAPDLUTs(unTemp_index);                                        //make all updates from LUTs

      }

    
  }
  else
  {
    APDIDX2 = IDX_TARGET;                                                       //Target Voltage
    unData =  APDDAT2 ;
    
    if(unData != CalcExternalBoostTarget( __swap_bytes(PAGE91H_Memory.APD_TARGET_OUTPUT) ))
    {  
      unData  = CalcExternalBoostTarget( __swap_bytes(PAGE91H_Memory.APD_TARGET_OUTPUT) );
      APDIDX2 = IDX_TARGET;                                                       //Target Voltage
      APDDAT2 = unData;
      
      PAGEA0H_Memory.APD_CURRENT_SETTING = __swap_bytes(PAGE91H_Memory.APD_TARGET_OUTPUT);      
      UpdateWordA2hTable(PAGE_A0H, &PAGEA0H_Memory.APD_CURRENT_SETTING, unData);
    }
    
    s_sPrev_lut_temp = -50;
  }
#endif
}

//------------------------------------------------------------------------------
// LUT_MOD_Process Function
//      - Processing Modulation look up table
//------------------------------------------------------------------------------
void LUT_MOD_Process(signed int sTemp_value)
{
#if __SFP28_ER__== 1
#else
  
  unsigned int unLut_update = 0;
  unsigned int unTemp_index = 0;
  unsigned int unMod = 0;  
  unsigned int unControl;
  static signed int s_sPrev_lut_temp = -50;
  static unsigned int s_unOld_control = 0;  
  static unsigned char s_First_implement_flag = 1;  
  
  unControl = __swap_bytes(PAGE90H_Memory.CONTROL);                             //read current control status
  unControl &= LUT_MOD_EN;                                                      //get mod lut loop status
  
  if(unControl & LUT_MOD_EN)                                                    //if mod lut loop is enabled?
  {

      //LUT operation
      sTemp_value = sTemp_value >> 8;                                           //get a truncated integer
      
      if(sTemp_value < -40)                                                     //-40 is the minimum range
      {
        sTemp_value = -40;
      }
      if(sTemp_value > 104)                                                      //104 is the maximum range
      {
        sTemp_value = 104;
      }      
         
      unLut_update = 0;                                                         //assume no update needed
      
      if(sTemp_value >= (s_sPrev_lut_temp + 2  ) )                              //more than 2 deg above previous lut index, need to jump up
      {
        unLut_update = 1;
      }
      else if(sTemp_value < (s_sPrev_lut_temp - 1 ) )                           //fallen below LUT level by the hystereses amount
      {
        unLut_update = 1;
      }
      
      
      if(unLut_update)
      {
        
        
        sTemp_value &= 0xFFFE;                                                  //only need 2 deg resolution
        s_sPrev_lut_temp = sTemp_value;                                         //store new lut step, this should be an even number
        sTemp_value = sTemp_value >> 1;                                         //divide by 2 because 2 deg steps
        sTemp_value += 20;                                                      //becuase LUT starts at -40C, 2deg steps  
        unTemp_index = (unsigned char)sTemp_value;                              //change to char
        
        PAGEA0H_Memory.MOD_TINDEX =  __swap_bytes(unTemp_index);
        UpdateWordA2hTable(PAGE_A0H, &PAGEA0H_Memory.MOD_TINDEX, unTemp_index); 
        
        UpdateFromMODLUTs(unTemp_index);                                        //make all updates from LUTs

      }    
  } 
  else                                                                          //mod lut loop is disabled
  {
    if((unControl != s_unOld_control)||(s_First_implement_flag == 1))           //if previous mod lut loop is enabled or this function is first implemented
    {
      
      Driver_TXModWrite(DRIVER_SLAVE_ADDR, &DRIVER_Memory);                 //update mode from max24016 setting in page 80h
      
      unMod = DRIVER_Memory.SET_MOD1;                                         //read current mode set
      unMod = unMod*2;
      unMod = unMod + DRIVER_Memory.SET_MOD0;                                 //clac mode to 16bit
        
      PAGEA0H_Memory.MOD_CURRENT_SETTING = __swap_bytes(unMod);                 //page 0xA0 memory
      UpdateWordA2hTable(PAGE_A0H, &PAGEA0H_Memory.MOD_CURRENT_SETTING, unMod); //update A2h Corresponding registers when current table is A0h 
      
      s_First_implement_flag = 0;                                               //clear first implement flag
    }
    s_sPrev_lut_temp = -50;
  }
  
  s_unOld_control = unControl;                                                  //save current control status
#endif
}


//------------------------------------------------------------------------------
// LUT_Process Function
//      - All LUTs have been proccessing here.
//------------------------------------------------------------------------------
void LUT_Process(signed int sTemp_value)
{ 
#if __SFP28_ER__== 1
#else
     
  LUT_APD_Process(sTemp_value);                                                 //APD lut loop
  LUT_MOD_Process(sTemp_value);                                                 //Mod lut loop
#endif
  
}

//-----------------------------------------------------------------------------
// end of file
//-----------------------------------------------------------------------------

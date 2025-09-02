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
#include <iods4835.h>
#include "includes.h"
#include <intrinsics.h> 
#include <math.h> 
//-----------------------------------------------------------------------------
// local variables defined in this module
//-----------------------------------------------------------------------------
unsigned int unAdc_scale;
signed int sAdc_offset;
unsigned int unTemp_scale;
signed int sTemp_offset;
signed int sPrev_lut_temp = -60;                                                //set out of range so first temp will force an update

//-----------------------------------------------------------------------------
// local function declaration
//-----------------------------------------------------------------------------

static unsigned int ConvertVccScale(unsigned int unParam);
//static unsigned int ApplyInternalScale(unsigned int unRaw_adc, unsigned int unScale, unsigned int sOffset);
#if 0
static unsigned int CalibrateUnsignedDDM(unsigned int nValue, unsigned int unSlope, signed int sOffset);
static signed int CalibrateSignedDDM(signed int nValue, unsigned int unSlope, signed int sOffset);
#endif
//static signed int CalibrateTempDDM(signed int unValue, unsigned int unSlope, signed int sOffset);



//-----------------------------------------------------------------------------
// CalcIavg function
//   - Calculate Bias, note: the bias can be from IDAC or DCDC1
//-----------------------------------------------------------------------------
//unsigned int CalcIavg(void)
unsigned int CalcIavg(unsigned char chNo)
{
#if __SFP28_ER__== 1
  float fBias = 0;
  
  switch (chNo) {
  case 0:
    if(IDCN1 & 0x0001)                                                            //check if IDAC1 is enabled
    {
      fBias = (float)IDCD1;
      
      fBias = 244*fBias;                                                          //calibration              
      fBias = fBias/10;
      
      switch(IDCN1_bit.RANGE_SEL)
      {
      case 0:                                                                  //full scale 25mA
        fBias = fBias/8;
        break;
      case 1:                                                                  //full scale 50mA
        fBias = fBias/4;
        break;  
      case 2:                                                                  //full scale 100mA
        fBias = fBias/2;
        break;   
      case 3:                                                                  //full scale 200mA
        fBias = fBias;
        break;                  
      default:
        break;
      }
    }
    break;
    
  case 1:
    if(IDCN2 & 0x0001)                                                            //check if IDAC1 is enabled
    {
      fBias = (float)IDCD2;
      
      fBias = 244*fBias;                                                          //calibration              
      fBias = fBias/10;
      
      switch(IDCN2_bit.RANGE_SEL)
      {
      case 0:                                                                  //full scale 25mA
        fBias = fBias/8;
        break;
      case 1:                                                                  //full scale 50mA
        fBias = fBias/4;
        break;  
      case 2:                                                                  //full scale 100mA
        fBias = fBias/2;
        break;   
      case 3:                                                                  //full scale 200mA
        fBias = fBias;
        break;                  
      default:
        break;
      }
    }
    break;
    
  case 2:
    if(IDCN3 & 0x0001)                                                            //check if IDAC1 is enabled
    {
      fBias = (float)IDCD3;
      
      fBias = 244*fBias;                                                          //calibration              
      fBias = fBias/10;
      
      switch(IDCN3_bit.RANGE_SEL)
      {
      case 0:                                                                  //full scale 25mA
        fBias = fBias/8;
        break;
      case 1:                                                                  //full scale 50mA
        fBias = fBias/4;
        break;  
      case 2:                                                                  //full scale 100mA
        fBias = fBias/2;
        break;   
      case 3:                                                                  //full scale 200mA
        fBias = fBias;
        break;                  
      default:
        break;
      }
    }
    break;
    
  case 3:
    if(IDCN4 & 0x0001)                                                            //check if IDAC1 is enabled
    {
      fBias = (float)IDCD4;
      
      fBias = 244*fBias;                                                          //calibration              
      fBias = fBias/10;
      
      switch(IDCN4_bit.RANGE_SEL)
      {
      case 0:                                                                  //full scale 25mA
        fBias = fBias/8;
        break;
      case 1:                                                                  //full scale 50mA
        fBias = fBias/4;
        break;  
      case 2:                                                                  //full scale 100mA
        fBias = fBias/2;
        break;   
      case 3:                                                                  //full scale 200mA
        fBias = fBias;
        break;                  
      default:
        break;
      }
    }
    break;
    
  default:
    fBias = 0;
    break;
  }
  
  return (unsigned int)fBias;
  
#else


  float fBias = 0;
  
#ifdef DCDC_BIASING                                                             //DCDC Biasing
  
  fBias = (float)__swap_bytes(PAGEA0H_Memory.ADC_TX_BIAS) ;                                      //read current ADC 
                                
  fBias = fBias * 260.03 -11805;                                                //Internal calibration

#else                                                                           //IDAC Biasing
  if(IDCN1 & 0x0001)                                                            //check if IDAC1 is enabled
  {
    fBias = (float)IDCD1;
      
    fBias = 244*fBias;                                                          //calibration              
    fBias = fBias/10;
    
    switch(IDCN1_bit.RANGE_SEL)
    {
       case 0:                                                                  //full scale 25mA
                fBias = fBias/8;
                break;
       case 1:                                                                  //full scale 50mA
                fBias = fBias/4;
                break;  
       case 2:                                                                  //full scale 100mA
                fBias = fBias/2;
                break;   
       case 3:                                                                  //full scale 200mA
                fBias = fBias;
                break;                  
      default:
                break;
    }
  }
  
#endif
  
  
  return (unsigned int)fBias;
#endif
  
}


//-----------------------------------------------------------------------------
// DDM_Read function
//   - Read ADC and calibrate all DDM 
//-----------------------------------------------------------------------------
void DDM_Read(void)
{
#if __SFP28_ER__== 1
  
  unsigned int unDdm_value;
//  unsigned int unCal_slope;
//  signed int sCal_offset;
  signed int sddm_value;
//  double dData = 0;
//  static unsigned char ucFirstImpFlag = 1;
  A2_PAGE_80H_MEMORY_MAP  * flashPtr, * controlMemoryPtr;
  A2_PAGE_81H_MEMORY_MAP  * flashPtr1, * controlMemoryPtr_1;  
  A2_LOWER_MEMORY_MAP  * lower_memory_map_ptr;

  flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
  flashPtr1 = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P81H_Up[0];
  lower_memory_map_ptr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];
  controlMemoryPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_Pn_Up[0];
  controlMemoryPtr_1 = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_Pn_Up[0];

  ProcessTemperature();                                                         //internal temperature calibration
  
  if(ADST_bit.ADDAI)                                                            //make sure new conversion is completed
  {
  
    /////////////////       VCC           ///////////////////////////
    unDdm_value = ADC_ReadOut(CONFG_VCC_COMP);                                  //Read data
    
    //unDdm_value = ApplyInternalScale(unDdm_value, unAdc_scale, sAdc_offset);
    flashPtr->ADC_VCC= __swap_bytes(unDdm_value);                          //update raw adc to A0h
    //UpdateWordA0hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_VCC,unDdm_value);           //update A2h Corresponding registers when current table is A0h 
    
//    unDdm_value = ConvertVccScale(unDdm_value);                                 //calibrate VCC with internal scale and offset
    unDdm_value = ConvertVccScale(unDdm_value) + __swap_bytes(flashPtr->VCC_Offset);                                 //calibrate VCC with internal scale and offset

//    unCal_slope = __swap_bytes(PAGE90H_Memory.VCC_SLOPE);                       //read external slope 
//    sCal_offset = (signed int)__swap_bytes((unsigned int)PAGE90H_Memory.VCC_OFFSET);// read external offset
//    unDdm_value = CalibrateUnsignedDDM(unDdm_value, unCal_slope, sCal_offset);  //calibrate ddm with external slope and offset

//    unCal_slope = __swap_bytes(flashPtr->VCC_Slope);                       //read external slope 
//    sCal_offset = (signed int)__swap_bytes((unsigned int)flashPtr->VCC_Offset);// read external offset
//    unDdm_value = CalibrateUnsignedDDM(unDdm_value, unCal_slope, sCal_offset);  //calibrate ddm with external slope and offset

//    VCC = __swap_bytes(unDdm_value);                                            //update to DDM
#if __HFR_REQ_DDM_FLAG_VER__==1
    
    if (ddm_vcc_flag == 0)
    {
      lower_memory_map_ptr->A2_VCC = __swap_bytes(unDdm_value);                                            //update to DDM      
    }
    else if (ddm_vcc_flag > 20)
    {
      ddm_vcc_flag = 0;
      lower_memory_map_ptr->A2_VCC = __swap_bytes(unDdm_value);                                            //update to DDM      
      
    }
    else
    {
      ddm_vcc_flag++;
    }

#else
    lower_memory_map_ptr->A2_VCC = __swap_bytes(unDdm_value);                                            //update to DDM
#endif
    
    SetUnsignedAlarmsAndWarnings(VCC_DDM, unDdm_value);                         //alarm and warning checking
  
  
////////////////   TEC V_THM     /////////////////////////////
    unDdm_value = ADC_ReadOut(CONFG_VTHERM1);                                   //read raw ADC 
//    unDdm_value = ADC_ReadOut(CONFG_VTHERM2);                                   //read raw ADC 
    
    flashPtr1->V_THM = __swap_bytes(unDdm_value);              //update raw adc to A0h
    
    if (lower_memory_map_ptr->A2_TABLE == 0x81)
    {
      controlMemoryPtr_1->V_THM = __swap_bytes(unDdm_value);              
    }
    
        ////////////////   APD Voltage     /////////////////////////////
    unDdm_value = ADC_ReadOut(CONFG_EXT_BOOST1);                                //read raw adc
    
    flashPtr->APD_ADC = __swap_bytes(unDdm_value);                //update raw adc to 80h 
    if (lower_memory_map_ptr->A2_TABLE == 0x80)
    {
      controlMemoryPtr->APD_ADC = __swap_bytes(unDdm_value);              
    }
 //
//    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_APDFB_READOUT, unDdm_value);//update A2h Corresponding registers when current table is A0h 
//   
//    unCal_slope = 0x00F8;                                                       //Internal calibraton                                 
//    sCal_offset = 0;
//    unDdm_value = CalibrateUnsignedDDM(unDdm_value, unCal_slope, sCal_offset);
//    
//    PAGEA0H_Memory.APDFB_READOUT= __swap_bytes(unDdm_value);                    //update DDM
//    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.APDFB_READOUT, unDdm_value);    //update A2h Corresponding registers when current table is A0h      

    /////////////////   TX Power        ////////////////////////////
//    unDdm_value = ADC_ReadOut(CONFG_APC1);                                      //Read data
//    
//    PAGEA0H_Memory.ADC_TX_POWER= __swap_bytes(unDdm_value);                     //update raw adc to A0h
//    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_TX_POWER, unDdm_value);     //update A2h Corresponding registers when current table is A0h   
//    
//    unCal_slope = __swap_bytes(PAGE90H_Memory.TX_POWER_SLOPE);                  //read external slope 
//    sCal_offset = (signed int)__swap_bytes((unsigned int)PAGE90H_Memory.TX_POWER_OFFSET);// read external offset
//    unDdm_value = CalibrateUnsignedDDM(unDdm_value, unCal_slope, sCal_offset);  //calibrate ddm with external slope and offset
//    
//    if(TXDStatus() == ASSERTED)                                                 //report back 1 when laser is off
//    {
//      unDdm_value = 0x0001;      
//    }
//    
//    if(unDdm_value < 1)
//    {
//      unDdm_value = 1;                                                          //limit min DDM value to 1, means -40dBm
//    }
//       
//
//    TX_POWER = __swap_bytes(unDdm_value);                                       //update to DDM
//    SetUnsignedAlarmsAndWarnings(TXP_DDM, unDdm_value);                         //alarm and warning checking

    
    ////////////////   TX BIAS        /////////////////////////////                                                           
//    unDdm_value = ADC_ReadOut(CONFG_BIAS);                                      //read raw ADC 
//    
//    PAGEA0H_Memory.ADC_TX_BIAS = __swap_bytes(unDdm_value);                     //update raw adc to A0h
//    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_TX_BIAS, unDdm_value);      //update A2h Corresponding registers when current table is A0h 
//    
//    unDdm_value = CalcIavg();                                                   //calculate Bias
//    
//    unCal_slope = __swap_bytes(PAGE90H_Memory.TX_BIAS_SLOPE);                   //read external slope 
//    sCal_offset = (signed int)__swap_bytes(PAGE90H_Memory.TX_BIAS_OFFSET);      //read external offset
//    unDdm_value = CalibrateUnsignedDDM(unDdm_value, unCal_slope, sCal_offset);  //calibrate ddm with external slope and offset
//    
//    
//    if(TXDStatus() == ASSERTED)                                                 //report back 0 when laser is off
//    {
//      unDdm_value = 0x0000;
//    }
//
//    TX_BIAS = __swap_bytes(unDdm_value);                                        //update to DDM
//    SetUnsignedAlarmsAndWarnings(BIAS_DDM, unDdm_value);                        //alarm and warning checking


    ////////////////   Laser Temperature     /////////////////////////////
//    unDdm_value = ADC_ReadOut(CONFG_VTHERM2);                                   //read raw ADC 
//    
//    PAGEA0H_Memory.ADC_VTHERM2_READOUT= __swap_bytes(unDdm_value);              //update raw adc to A0h
//    PAGEA0H_Memory.ADC_LASER_TEMP = PAGEA0H_Memory.ADC_VTHERM2_READOUT;         //update raw adc to A0h
//    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_VTHERM2_READOUT, unDdm_value);//update A2h Corresponding registers when current table is A0h  
//    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_LASER_TEMP, unDdm_value);   //update A2h Corresponding registers when current table is A0h  
//   
//    //10000*EXP(3920*(1/T - 1/(25+273.5))) = R
//    dData = (double)unDdm_value;                                                //calculate laser temperature
//    dData = dData/(65536-dData);
//    dData = log(dData);
//    dData = 3930/(13.18128+ dData);
//    dData -= 273.15;
//    dData *= 256;
//
//    sddm_value = (signed int)dData;           
//    
//    unCal_slope = __swap_bytes(PAGE90H_Memory.LASER_TEMP_SLOPE);                //read external slope 
//    sCal_offset = (signed int)__swap_bytes(PAGE90H_Memory.LASER_TEMP_OFFSET);   //read external offset
//    sddm_value = CalibrateSignedDDM(sddm_value, unCal_slope, sCal_offset);      //calibrate DDM
//    
//    dData = (double)sddm_value;
//    
//    if(ucFirstImpFlag != 1)                                                     //check first implement flag, if it's not the first calibration, the software averaging is needed.
//    {
//     dData = dData*0.1 + ((double)__swap_bytes(LASER_TEMP)*0.9);                //software averaging
//    }   
//    
//    sddm_value = (signed int)dData;   
//    
//    LASER_TEMP = __swap_bytes(sddm_value);                                      //update to DDM
//    
//    SetSignedAlarmsAndWarnings(LASER_TEMP_DDM, sddm_value);                     //alarm and warning checking
    
       
    ////////////////   TEC Current       /////////////////////////////    
//     sddm_value = ADC_ReadOut(CONFG_TECC);                                      //read raw adc
//
//    PAGEA0H_Memory.ADC_TEC2_CURRENT = __swap_bytes(sddm_value);                 //update raw adc to A0h
//    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_TEC2_CURRENT, (unsigned int)sddm_value); //update A2h Corresponding registers when current table is A0h 
//
//    unCal_slope = 0x0500;                                                       //internal slope 
//    sCal_offset = 77;                                                           //internal offset 
//    sddm_value = CalibrateSignedDDM(sddm_value, unCal_slope, sCal_offset);      //internal calibration
//
//    unCal_slope = __swap_bytes(PAGE90H_Memory.TEC_CURRENT_SLOPE);               //read external slope 
//    sCal_offset = (signed int)__swap_bytes(PAGE90H_Memory.TEC_CURRENT_OFFSET);  //read external offset 
//    sddm_value = CalibrateSignedDDM(sddm_value, unCal_slope, sCal_offset);      //calibrate DDM
//    
//    TEC_CURRENT = __swap_bytes(sddm_value);                                     //update DDM
//    SetSignedAlarmsAndWarnings(TEC_CURRENT_DDM, sddm_value);                    //alarm and warning checking
//        
//    TXF_AlarmWarn_Check();                                                      //check TXF status 


    ////////////////   DCDC1 Voltage     /////////////////////////////
//    unDdm_value = ADC_ReadOut(CONFG_DC_DCFB1);                                  //read raw adc
//    
//    PAGEA0H_Memory.ADC_DC1_READOUT= __swap_bytes(unDdm_value);                  //update raw adc to A0h
//    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_DC1_READOUT, unDdm_value);  //update A2h Corresponding registers when current table is A0h 
//
//    unCal_slope = 0x0119;                                                       //Internal calibraton                                        
//    sCal_offset = 0;
//    unDdm_value = CalibrateUnsignedDDM(unDdm_value, unCal_slope, sCal_offset);  //calibrate DDM
//     
//    //Note: DCDC1 is designed to supply VCCDAC, those IDAC pins which are uesed as ADC input, the voltage will not exceed VCCDAC, so in this case, it's needed to check if the DCDC1 is enabled?
//    if( PAGE91H_Memory.PMIC_SELECT & BUCK1_ENABLE )                             //check DCDC1 is enabled? 
//    {
//      PAGEA0H_Memory.DC1_READOUT= __swap_bytes(unDdm_value);                    //update DDM
//      UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.DC1_READOUT, unDdm_value);    //update A2h Corresponding registers when current table is A0h  
//    }
//    else
//    {
//      PAGEA0H_Memory.DC1_READOUT= 0;                                            //update DDM
//      UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.DC1_READOUT, 0);              //update A2h Corresponding registers when current table is A0h  
//    } 
    
    ////////////////   DCDC2 Voltage     /////////////////////////////
//    unDdm_value = ADC_ReadOut(CONFG_DC_DCFB2);                                  //read raw adc                     
//    
//    PAGEA0H_Memory.ADC_DC2_READOUT= __swap_bytes(unDdm_value);                  //update raw adc to A0h
//    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_DC2_READOUT, unDdm_value);  //update A2h Corresponding registers when current table is A0h 
//
//
//    unCal_slope = 0x0119;                                                       //Internal calibraton      
//    sCal_offset = 0;
//
//    unDdm_value = CalibrateUnsignedDDM(unDdm_value, unCal_slope, sCal_offset);  //calibrate DDM
//    
//    //Note: the DCDC2 FB can be provided only when DCDC2 is enabled
//    if( PAGE91H_Memory.PMIC_SELECT & BUCK2_ENABLE ) 
//    {
//      PAGEA0H_Memory.DC2_READOUT= __swap_bytes(unDdm_value);                    //update DDM 
//      UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.DC2_READOUT, unDdm_value);    //update A2h Corresponding registers when current table is A0h     
//    } 
//    else
//    {
//      PAGEA0H_Memory.DC2_READOUT= 0;                                            //update DDM
//      UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.DC2_READOUT, 0);              //update A2h Corresponding registers when current table is A0h  
//    }      

    ////////////////   APD Voltage     /////////////////////////////
//    unDdm_value = ADC_ReadOut(CONFG_EXT_BOOST1);                                //read raw adc
//    
//    PAGEA0H_Memory.ADC_APDFB_READOUT= __swap_bytes(unDdm_value);                //update raw adc to A0h 
//
//    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_APDFB_READOUT, unDdm_value);//update A2h Corresponding registers when current table is A0h 
//   
//    unCal_slope = 0x00F8;                                                       //Internal calibraton                                 
//    sCal_offset = 0;
//    unDdm_value = CalibrateUnsignedDDM(unDdm_value, unCal_slope, sCal_offset);
//    
//    PAGEA0H_Memory.APDFB_READOUT= __swap_bytes(unDdm_value);                    //update DDM
//    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.APDFB_READOUT, unDdm_value);    //update A2h Corresponding registers when current table is A0h      
     
     
    ////////////////   INV Voltage     /////////////////////////////
//    unDdm_value = ADC_ReadOut(CONFG_EXT_INV);                                   //read raw adc
//                           
//    PAGEA0H_Memory.ADC_INVFB_READOUT= __swap_bytes(unDdm_value);                //update raw adc to A0h 
//
//    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_INVFB_READOUT, unDdm_value);//update A2h Corresponding registers when current table is A0h  
//  
//    sddm_value = (signed int)unDdm_value;
//    unCal_slope  = 0x0071;                                                      //Internal calibration                                             
//    sCal_offset = 12000;
//    sddm_value = CalibrateSignedDDM(sddm_value, unCal_slope, sCal_offset);    
//    sddm_value = 0 - sddm_value;
    
    //Note: DCDC1 is designed to supply VCCDAC, those IDAC pins which are uesed as ADC input, the voltage will not exceed VCCDAC, so in this case, it's needed to check if the DCDC1 is enabled?
//    if( PAGE91H_Memory.PMIC_SELECT & BUCK1_ENABLE )                             //check DCDC1 is enabled? 
//    {
//      PAGEA0H_Memory.INVFB_READOUT= __swap_bytes(sddm_value);                   //update DDM
//      UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.INVFB_READOUT, sddm_value);   //update A2h Corresponding registers when current table is A0h  
//    }
//    else
//    {
//      PAGEA0H_Memory.INVFB_READOUT= 0;                                          //update DDM
//      UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.INVFB_READOUT, 0);            //update A2h Corresponding registers when current table is A0h  
//    }      
 
    
    ////////////////   VTEC Voltage     /////////////////////////////
//    unDdm_value = ADC_ReadOut(CONFG_VTEC);                                      //read raw adc
//    
//    PAGEA0H_Memory.ADC_TEC2_VOLTAGE = __swap_bytes(unDdm_value);                //update raw adc to A0h 
//    UpdateWordA2hTable(PAGE_A0H, &PAGEA0H_Memory.ADC_TEC2_VOLTAGE, unDdm_value);//update A2h Corresponding registers when current table is A0h    
//
//    sddm_value = (signed int)unDdm_value;
//    
//    unCal_slope = 0x0019;                                                       //Internal calibration
//    sCal_offset = 150;
//    sddm_value = CalibrateSignedDDM(sddm_value, unCal_slope, sCal_offset);          
//    
//    PAGEA0H_Memory.TEC2_VOLTAGE= __swap_bytes(sddm_value);                      //update DDM
//    UpdateWordA2hTable(PAGE_A0H, &PAGEA0H_Memory.TEC2_VOLTAGE, sddm_value);     //update A2h Corresponding registers when current table is A0h 
// 

    ////////////////   SH0 Voltage     /////////////////////////////
//    unDdm_value = __swap_bytes(PAGEA0H_Memory.ADC_SH0_RX_POWER);                //read raw adc
//    sddm_value = (signed int)unDdm_value;
//    
//    unCal_slope = 0x00BC;                                                       //Internal calibration
//    sCal_offset = 0;
//    sddm_value = CalibrateSignedDDM(sddm_value, unCal_slope, sCal_offset);     
//    
//    if(sddm_value < 0)
//    {
//      sddm_value = 0;
//    }
//    
//    PAGEA0H_Memory.SH0_READOUT= __swap_bytes(sddm_value);                       //update DDM
//    UpdateWordA2hTable(PAGE_A0H, &PAGEA0H_Memory.SH0_READOUT, sddm_value);      //update A2h Corresponding registers when current table is A0h 

    ////////////////   SH1 Voltage     /////////////////////////////
//    unDdm_value = __swap_bytes(PAGEA0H_Memory.ADC_SH1_RX_POWER);                //read raw adc
//    sddm_value = (signed int)unDdm_value;
//    
//    unCal_slope = 0x00BC;                                                       //Internal calibration
//    sCal_offset = 0;
//    sddm_value = CalibrateSignedDDM(sddm_value, unCal_slope, sCal_offset);     
//    
//    if(sddm_value < 0)
//    {
//      sddm_value = 0;
//    }
//    
//    PAGEA0H_Memory.SH0_READOUT= __swap_bytes(sddm_value);                       //update DDM
//    UpdateWordA2hTable(PAGE_A0H, &PAGEA0H_Memory.SH1_READOUT, sddm_value);      //update A2h Corresponding registers when current table is A0h 
         
    sddm_value = GetTec1(INDEX_TEC_PWMDUTY);
    flashPtr1->TEC1_DUTY_CYCLE= __swap_bytes(sddm_value);                          //update raw adc to A0h
    
    unDdm_value = GetTec1(INDEX_TEC_CURR_MEAS);
    flashPtr1->TEC1_I_MEAS = __swap_bytes(unDdm_value);                          //update raw adc to A0h
    
    if (lower_memory_map_ptr->A2_TABLE == 0x81)
    {
      controlMemoryPtr_1->TEC1_DUTY_CYCLE = __swap_bytes(sddm_value);              
      controlMemoryPtr_1->TEC1_I_MEAS = __swap_bytes(unDdm_value);              
    }

    ADST_bit.ADDAI = 0;
    
//    ucFirstImpFlag = 0;                                                         //clear flag
      
  } 

#else  
  
  unsigned int unDdm_value;
  unsigned int unCal_slope;
  signed int sCal_offset;
  signed int sddm_value;
  double dData = 0;
  static unsigned char ucFirstImpFlag = 1;


  ProcessTemperature();                                                         //internal temperature calibration
  
  if(ADST_bit.ADDAI)                                                            //make sure new conversion is completed
  {
  
    /////////////////       VCC           ///////////////////////////
    unDdm_value = ADC_ReadOut(CONFG_VCC_COMP);                                  //Read data
    
    //unDdm_value = ApplyInternalScale(unDdm_value, unAdc_scale, sAdc_offset);
    PAGEA0H_Memory.ADC_VCC= __swap_bytes(unDdm_value);                          //update raw adc to A0h
    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_VCC,unDdm_value);           //update A2h Corresponding registers when current table is A0h 
    
    unDdm_value = ConvertVccScale(unDdm_value);                                 //calibrate VCC with internal scale and offset

    unCal_slope = __swap_bytes(PAGE90H_Memory.VCC_SLOPE);                       //read external slope 
    sCal_offset = (signed int)__swap_bytes((unsigned int)PAGE90H_Memory.VCC_OFFSET);// read external offset
    unDdm_value = CalibrateUnsignedDDM(unDdm_value, unCal_slope, sCal_offset);  //calibrate ddm with external slope and offset
               
    VCC = __swap_bytes(unDdm_value);                                            //update to DDM
    
    SetUnsignedAlarmsAndWarnings(VCC_DDM, unDdm_value);                         //alarm and warning checking
  
    
    /////////////////   TX Power        ////////////////////////////
    unDdm_value = ADC_ReadOut(CONFG_APC1);                                      //Read data
    
    PAGEA0H_Memory.ADC_TX_POWER= __swap_bytes(unDdm_value);                     //update raw adc to A0h
    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_TX_POWER, unDdm_value);     //update A2h Corresponding registers when current table is A0h   
    
    unCal_slope = __swap_bytes(PAGE90H_Memory.TX_POWER_SLOPE);                  //read external slope 
    sCal_offset = (signed int)__swap_bytes((unsigned int)PAGE90H_Memory.TX_POWER_OFFSET);// read external offset
    unDdm_value = CalibrateUnsignedDDM(unDdm_value, unCal_slope, sCal_offset);  //calibrate ddm with external slope and offset
    
    if(TXDStatus() == ASSERTED)                                                 //report back 1 when laser is off
    {
      unDdm_value = 0x0001;      
    }
    
    if(unDdm_value < 1)
    {
      unDdm_value = 1;                                                          //limit min DDM value to 1, means -40dBm
    }
       

    TX_POWER = __swap_bytes(unDdm_value);                                       //update to DDM
    SetUnsignedAlarmsAndWarnings(TXP_DDM, unDdm_value);                         //alarm and warning checking

    
    ////////////////   TX BIAS        /////////////////////////////                                                           
    unDdm_value = ADC_ReadOut(CONFG_BIAS);                                      //read raw ADC 
    
    PAGEA0H_Memory.ADC_TX_BIAS = __swap_bytes(unDdm_value);                     //update raw adc to A0h
    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_TX_BIAS, unDdm_value);      //update A2h Corresponding registers when current table is A0h 
    
    unDdm_value = CalcIavg();                                                   //calculate Bias
    
    unCal_slope = __swap_bytes(PAGE90H_Memory.TX_BIAS_SLOPE);                   //read external slope 
    sCal_offset = (signed int)__swap_bytes(PAGE90H_Memory.TX_BIAS_OFFSET);      //read external offset
    unDdm_value = CalibrateUnsignedDDM(unDdm_value, unCal_slope, sCal_offset);  //calibrate ddm with external slope and offset
    
    
    if(TXDStatus() == ASSERTED)                                                 //report back 0 when laser is off
    {
      unDdm_value = 0x0000;
    }

    TX_BIAS = __swap_bytes(unDdm_value);                                        //update to DDM
    SetUnsignedAlarmsAndWarnings(BIAS_DDM, unDdm_value);                        //alarm and warning checking


    ////////////////   Laser Temperature     /////////////////////////////
    unDdm_value = ADC_ReadOut(CONFG_VTHERM2);                                   //read raw ADC 
    
    PAGEA0H_Memory.ADC_VTHERM2_READOUT= __swap_bytes(unDdm_value);              //update raw adc to A0h
    PAGEA0H_Memory.ADC_LASER_TEMP = PAGEA0H_Memory.ADC_VTHERM2_READOUT;         //update raw adc to A0h
    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_VTHERM2_READOUT, unDdm_value);//update A2h Corresponding registers when current table is A0h  
    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_LASER_TEMP, unDdm_value);   //update A2h Corresponding registers when current table is A0h  
   
    //10000*EXP(3920*(1/T - 1/(25+273.5))) = R
    dData = (double)unDdm_value;                                                //calculate laser temperature
    dData = dData/(65536-dData);
    dData = log(dData);
    dData = 3930/(13.18128+ dData);
    dData -= 273.15;
    dData *= 256;

    sddm_value = (signed int)dData;           
    
    unCal_slope = __swap_bytes(PAGE90H_Memory.LASER_TEMP_SLOPE);                //read external slope 
    sCal_offset = (signed int)__swap_bytes(PAGE90H_Memory.LASER_TEMP_OFFSET);   //read external offset
    sddm_value = CalibrateSignedDDM(sddm_value, unCal_slope, sCal_offset);      //calibrate DDM
    
    dData = (double)sddm_value;
    
    if(ucFirstImpFlag != 1)                                                     //check first implement flag, if it's not the first calibration, the software averaging is needed.
    {
     dData = dData*0.1 + ((double)__swap_bytes(LASER_TEMP)*0.9);                //software averaging
    }   
    
    sddm_value = (signed int)dData;   
    
    LASER_TEMP = __swap_bytes(sddm_value);                                      //update to DDM
    
    SetSignedAlarmsAndWarnings(LASER_TEMP_DDM, sddm_value);                     //alarm and warning checking
    
       
    ////////////////   TEC Current       /////////////////////////////    
     sddm_value = ADC_ReadOut(CONFG_TECC);                                      //read raw adc

    PAGEA0H_Memory.ADC_TEC2_CURRENT = __swap_bytes(sddm_value);                 //update raw adc to A0h
    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_TEC2_CURRENT, (unsigned int)sddm_value); //update A2h Corresponding registers when current table is A0h 

    unCal_slope = 0x0500;                                                       //internal slope 
    sCal_offset = 77;                                                           //internal offset 
    sddm_value = CalibrateSignedDDM(sddm_value, unCal_slope, sCal_offset);      //internal calibration

    unCal_slope = __swap_bytes(PAGE90H_Memory.TEC_CURRENT_SLOPE);               //read external slope 
    sCal_offset = (signed int)__swap_bytes(PAGE90H_Memory.TEC_CURRENT_OFFSET);  //read external offset 
    sddm_value = CalibrateSignedDDM(sddm_value, unCal_slope, sCal_offset);      //calibrate DDM
    
    TEC_CURRENT = __swap_bytes(sddm_value);                                     //update DDM
    SetSignedAlarmsAndWarnings(TEC_CURRENT_DDM, sddm_value);                    //alarm and warning checking
        
    TXF_AlarmWarn_Check();                                                      //check TXF status 


    ////////////////   DCDC1 Voltage     /////////////////////////////
    unDdm_value = ADC_ReadOut(CONFG_DC_DCFB1);                                  //read raw adc
    
    PAGEA0H_Memory.ADC_DC1_READOUT= __swap_bytes(unDdm_value);                  //update raw adc to A0h
    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_DC1_READOUT, unDdm_value);  //update A2h Corresponding registers when current table is A0h 

    unCal_slope = 0x0119;                                                       //Internal calibraton                                        
    sCal_offset = 0;
    unDdm_value = CalibrateUnsignedDDM(unDdm_value, unCal_slope, sCal_offset);  //calibrate DDM
     
    //Note: DCDC1 is designed to supply VCCDAC, those IDAC pins which are uesed as ADC input, the voltage will not exceed VCCDAC, so in this case, it's needed to check if the DCDC1 is enabled?
    if( PAGE91H_Memory.PMIC_SELECT & BUCK1_ENABLE )                             //check DCDC1 is enabled? 
    {
      PAGEA0H_Memory.DC1_READOUT= __swap_bytes(unDdm_value);                    //update DDM
      UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.DC1_READOUT, unDdm_value);    //update A2h Corresponding registers when current table is A0h  
    }
    else
    {
      PAGEA0H_Memory.DC1_READOUT= 0;                                            //update DDM
      UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.DC1_READOUT, 0);              //update A2h Corresponding registers when current table is A0h  
    } 
    
    ////////////////   DCDC2 Voltage     /////////////////////////////
    unDdm_value = ADC_ReadOut(CONFG_DC_DCFB2);                                  //read raw adc                     
    
    PAGEA0H_Memory.ADC_DC2_READOUT= __swap_bytes(unDdm_value);                  //update raw adc to A0h
    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_DC2_READOUT, unDdm_value);  //update A2h Corresponding registers when current table is A0h 


    unCal_slope = 0x0119;                                                       //Internal calibraton      
    sCal_offset = 0;

    unDdm_value = CalibrateUnsignedDDM(unDdm_value, unCal_slope, sCal_offset);  //calibrate DDM
    
    //Note: the DCDC2 FB can be provided only when DCDC2 is enabled
    if( PAGE91H_Memory.PMIC_SELECT & BUCK2_ENABLE ) 
    {
      PAGEA0H_Memory.DC2_READOUT= __swap_bytes(unDdm_value);                    //update DDM 
      UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.DC2_READOUT, unDdm_value);    //update A2h Corresponding registers when current table is A0h     
    } 
    else
    {
      PAGEA0H_Memory.DC2_READOUT= 0;                                            //update DDM
      UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.DC2_READOUT, 0);              //update A2h Corresponding registers when current table is A0h  
    }      
    ////////////////   APD Voltage     /////////////////////////////
    unDdm_value = ADC_ReadOut(CONFG_EXT_BOOST1);                                //read raw adc
    
    PAGEA0H_Memory.ADC_APDFB_READOUT= __swap_bytes(unDdm_value);                //update raw adc to A0h 

    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_APDFB_READOUT, unDdm_value);//update A2h Corresponding registers when current table is A0h 
   
    unCal_slope = 0x00F8;                                                       //Internal calibraton                                 
    sCal_offset = 0;
    unDdm_value = CalibrateUnsignedDDM(unDdm_value, unCal_slope, sCal_offset);
    
    PAGEA0H_Memory.APDFB_READOUT= __swap_bytes(unDdm_value);                    //update DDM
    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.APDFB_READOUT, unDdm_value);    //update A2h Corresponding registers when current table is A0h      
     
     
    ////////////////   INV Voltage     /////////////////////////////
    unDdm_value = ADC_ReadOut(CONFG_EXT_INV);                                   //read raw adc
                           
    PAGEA0H_Memory.ADC_INVFB_READOUT= __swap_bytes(unDdm_value);                //update raw adc to A0h 

    UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_INVFB_READOUT, unDdm_value);//update A2h Corresponding registers when current table is A0h  
  
    sddm_value = (signed int)unDdm_value;
    unCal_slope  = 0x0071;                                                      //Internal calibration                                             
    sCal_offset = 12000;
    sddm_value = CalibrateSignedDDM(sddm_value, unCal_slope, sCal_offset);    
    sddm_value = 0 - sddm_value;
    
    //Note: DCDC1 is designed to supply VCCDAC, those IDAC pins which are uesed as ADC input, the voltage will not exceed VCCDAC, so in this case, it's needed to check if the DCDC1 is enabled?
    if( PAGE91H_Memory.PMIC_SELECT & BUCK1_ENABLE )                             //check DCDC1 is enabled? 
    {
      PAGEA0H_Memory.INVFB_READOUT= __swap_bytes(sddm_value);                   //update DDM
      UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.INVFB_READOUT, sddm_value);   //update A2h Corresponding registers when current table is A0h  
    }
    else
    {
      PAGEA0H_Memory.INVFB_READOUT= 0;                                          //update DDM
      UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.INVFB_READOUT, 0);            //update A2h Corresponding registers when current table is A0h  
    }      
 
    
    ////////////////   VTEC Voltage     /////////////////////////////
    unDdm_value = ADC_ReadOut(CONFG_VTEC);                                      //read raw adc
    
    PAGEA0H_Memory.ADC_TEC2_VOLTAGE = __swap_bytes(unDdm_value);                //update raw adc to A0h 
    UpdateWordA2hTable(PAGE_A0H, &PAGEA0H_Memory.ADC_TEC2_VOLTAGE, unDdm_value);//update A2h Corresponding registers when current table is A0h    

    sddm_value = (signed int)unDdm_value;
    
    unCal_slope = 0x0019;                                                       //Internal calibration
    sCal_offset = 150;
    sddm_value = CalibrateSignedDDM(sddm_value, unCal_slope, sCal_offset);          
    
    PAGEA0H_Memory.TEC2_VOLTAGE= __swap_bytes(sddm_value);                      //update DDM
    UpdateWordA2hTable(PAGE_A0H, &PAGEA0H_Memory.TEC2_VOLTAGE, sddm_value);     //update A2h Corresponding registers when current table is A0h 
 

    ////////////////   SH0 Voltage     /////////////////////////////
    unDdm_value = __swap_bytes(PAGEA0H_Memory.ADC_SH0_RX_POWER);                //read raw adc
    sddm_value = (signed int)unDdm_value;
    
    unCal_slope = 0x00BC;                                                       //Internal calibration
    sCal_offset = 0;
    sddm_value = CalibrateSignedDDM(sddm_value, unCal_slope, sCal_offset);     
    
    if(sddm_value < 0)
    {
      sddm_value = 0;
    }
    
    PAGEA0H_Memory.SH0_READOUT= __swap_bytes(sddm_value);                       //update DDM
    UpdateWordA2hTable(PAGE_A0H, &PAGEA0H_Memory.SH0_READOUT, sddm_value);      //update A2h Corresponding registers when current table is A0h 

    ////////////////   SH1 Voltage     /////////////////////////////
    unDdm_value = __swap_bytes(PAGEA0H_Memory.ADC_SH1_RX_POWER);                //read raw adc
    sddm_value = (signed int)unDdm_value;
    
    unCal_slope = 0x00BC;                                                       //Internal calibration
    sCal_offset = 0;
    sddm_value = CalibrateSignedDDM(sddm_value, unCal_slope, sCal_offset);     
    
    if(sddm_value < 0)
    {
      sddm_value = 0;
    }
    
    PAGEA0H_Memory.SH0_READOUT= __swap_bytes(sddm_value);                       //update DDM
    UpdateWordA2hTable(PAGE_A0H, &PAGEA0H_Memory.SH1_READOUT, sddm_value);      //update A2h Corresponding registers when current table is A0h 
         

    ADST_bit.ADDAI = 0;
    
    ucFirstImpFlag = 0;                                                         //clear flag
      
  } 
#endif

}



//------------------------------------------------------------------------------
// ProcessTemperature function
//     - Temperature Calibration
//------------------------------------------------------------------------------
signed int TempCalibration( signed int sTemperature)
{
#if __SFP28_ER__== 1
  
  signed long int slValue;
    
    // temperature calibration formula:
    //   temperature = (adc * scale)/4096 - offset
    slValue = sTemperature;
    slValue = slValue * unTemp_scale;
    slValue = slValue >> 12;
    
    slValue = slValue - sTemp_offset;
    
    slValue = slValue<<1;
    
    // 추가: Offset 7.5 C를 빼줌.  0x780
//    sTemperature = (signed int) slValue - 0x780;
    sTemperature = (signed int) slValue;
    
    return sTemperature; 

#else
  
  signed long int slValue;
    
    // temperature calibration formula:
    //   temperature = (adc * scale)/4096 - offset
    slValue = sTemperature;
    slValue = slValue * unTemp_scale;
    slValue = slValue >> 12;
    
    slValue = slValue - sTemp_offset;
    
    slValue = slValue<<1;
    
    sTemperature = (signed int) slValue;
    
    return sTemperature; 
  
#endif
}


signed int TempCalibration_adjusted( signed int sTemperature)
{
#if __QSFP28_LR4__== 1
  
#elif __SFP28_ER__== 1
#if __SFP28_ER_SEMI_TUNABLE__ == 1

// ----------------------------------
  
  signed long int slValue, slRefValue;
  FP32 slSlope, slOffset, slResult;
  A2_PAGE_80H_MEMORY_MAP	* flashPtr;
//  PAGE06H_MEMORY_MAP  * upper_memory_map_ptr;
  
  flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
  //  flashPtr1 = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P81H_Up[0];
//  lower_memory_map_ptr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];

    slValue = sTemperature;
    slRefValue = (signed long int)__swap_bytes(flashPtr->nt_temp);
    if (slRefValue < 0x0F00)
    {
      slRefValue = 0x1900;
    }
    
    if (slValue > slRefValue)
    {
        slSlope = itemp_ht_slope;
        slOffset = itemp_ht_offset;
    }
    else
    {
        slSlope = itemp_lt_slope;
        slOffset = itemp_lt_offset;
    }
    
//    upper_memory_map_ptr->c_slope = __swap_bytes_to_float(slSlope);
//    upper_memory_map_ptr->c_offset = __swap_bytes_to_float(slOffset);
    
    slResult = (FP32)(((FP32)slValue * slSlope) + slOffset);
    sTemperature = (signed int)slResult;
    
    // 추가: Offset 7.5 C를 빼줌.  0x780
//    sTemperature = (signed int) slValue - 0x780;
    
    return sTemperature; 

#endif
    
#else
 
#endif
}

// Till Here, 2019.10.02. -->
//-----------------------------------------------------------------------------
// ProcessTemperature function
//   - Calculate Temperature
//-----------------------------------------------------------------------------
void ProcessTemperature(void)
{
#if __SFP28_ER__== 1
 
#if __SFP28_ER_SEMI_TUNABLE__ == 1

// ----------------------------------
  signed int sInternalTemp = 0, sInternalTemp_adjusted;
  A2_PAGE_80H_MEMORY_MAP  * flashPtr;
  A2_LOWER_MEMORY_MAP  * lower_memory_map_ptr;

  flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
//  flashPtr1 = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P81H_Up[0];
  lower_memory_map_ptr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];
  
  
  //Internal Temperature
  if( ADST_bit.ITEMPI )                                                         //Check if Internal Temperature sensor is completed
  {
      ADST_bit.ITEMPI = 0;                                                      //Clear Internal temperature sensor conversion complete flag
      
      sInternalTemp = ITEMP_DATA;                                               //Read the internal temperature
      
//      flashPtr->ADC_INTERNAL_TEMP = __swap_bytes(sInternalTemp);                //update raw adc to A0h 
      
      sInternalTemp = TempCalibration( sInternalTemp);                          //internal calibration for internal temperature
      
      flashPtr->rawCurrTemp = (signed int)__swap_bytes((unsigned int)sInternalTemp);
      
      sInternalTemp_adjusted = TempCalibration_adjusted(sInternalTemp);
      
#if __HFR_REQ_DDM_FLAG_VER__==1
    if (ddm_temperature_flag == 0)
    {
      lower_memory_map_ptr->A2_TEMPERATURE = (signed int)__swap_bytes((unsigned int)sInternalTemp_adjusted);      //udpate DDM
    }
    else if (ddm_temperature_flag > 20)
    {
      ddm_temperature_flag = 0;
      lower_memory_map_ptr->A2_TEMPERATURE = (signed int)__swap_bytes((unsigned int)sInternalTemp_adjusted);      //udpate DDM      
    }
    else
    {
      ddm_temperature_flag++;
    }
      
#else
//      lower_memory_map_ptr->TEMPERATURE = (signed int)__swap_bytes((unsigned int)sInternalTemp);      //udpate DDM
      lower_memory_map_ptr->A2_TEMPERATURE = (signed int)__swap_bytes((unsigned int)sInternalTemp_adjusted);      //udpate DDM
#endif
    
//      SetSignedAlarmsAndWarnings(TEMP_DDM,sInternalTemp);                       //alarm warning checking
      
      APD_Process(sInternalTemp);                                               //lut-like process,including APD loop
    
  }
  
// ----------------------------------
  
#else
  
//  unsigned int unCal_slope;
//  signed int sCal_offset;
  signed int sInternalTemp = 0;
  A2_PAGE_80H_MEMORY_MAP  * flashPtr;
//  A2_PAGE_81H_MEMORY_MAP  * flashPtr1;  
  A2_LOWER_MEMORY_MAP  * lower_memory_map_ptr;

  flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
//  flashPtr1 = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P81H_Up[0];
  lower_memory_map_ptr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];
  
  //Internal Temperature
  if( ADST_bit.ITEMPI )                                                         //Check if Internal Temperature sensor is completed
  {
      ADST_bit.ITEMPI = 0;                                                      //Clear Internal temperature sensor conversion complete flag
      
      sInternalTemp = ITEMP_DATA;                                               //Read the internal temperature
      
//      PAGEA0H_Memory.ADC_INTERNAL_TEMP = __swap_bytes(sInternalTemp);           //update raw adc to A0h 
//      UpdateWordA2hTable(PAGE_A0H, &PAGEA0H_Memory.ADC_INTERNAL_TEMP, sInternalTemp);//update A2h Corresponding registers when current table is A0h  
      flashPtr->ADC_INTERNAL_TEMP = __swap_bytes(sInternalTemp);                //update raw adc to A0h 
//      UpdateWordA0hTable(PAGE_A0H, &I2C_Slave_Buffer_A4_Local_Memory[FLASH_ADC_INTERNAL_TEMP], sInternalTemp);//update A2h Corresponding registers when current table is A0h  
      
      sInternalTemp = TempCalibration( sInternalTemp);                          //internal calibration for internal temperature
      
//      unCal_slope = __swap_bytes(PAGE90H_Memory.TEMP_SLOPE);                    //read external slope
//      sCal_offset = (signed int)__swap_bytes(PAGE90H_Memory.TEMP_OFFSET);       //read external offset
//      
//      sInternalTemp = CalibrateSignedDDM(sInternalTemp, unCal_slope, sCal_offset);//external calibration 

//      unCal_slope = __swap_bytes(flashPtr->ITEMP_Slope);                    //read external slope
//      sCal_offset = (signed int)__swap_bytes(flashPtr->ITEMP_Offset);       //read external offset
//      
//      sInternalTemp = CalibrateSignedDDM(sInternalTemp, unCal_slope, sCal_offset);//external calibration 

#if __HFR_REQ_DDM_FLAG_VER__==1
    if (ddm_temperature_flag == 0)
    {
      lower_memory_map_ptr->A2_TEMPERATURE = (signed int)__swap_bytes((unsigned int)sInternalTemp);      //udpate DDM
    }
    else if (ddm_temperature_flag > 20)
    {
      ddm_temperature_flag = 0;
      lower_memory_map_ptr->A2_TEMPERATURE = (signed int)__swap_bytes((unsigned int)sInternalTemp);      //udpate DDM
    }
    else
    {
      ddm_temperature_flag++;
    }
      
#else
//      TEMPERATURE = (signed int)__swap_bytes((unsigned int)sInternalTemp);      //udpate DDM
      lower_memory_map_ptr->A2_TEMPERATURE = (signed int)__swap_bytes((unsigned int)sInternalTemp);      //udpate DDM
#endif
    
      SetSignedAlarmsAndWarnings(TEMP_DDM,sInternalTemp);                       //alarm warning checking
    
//      LUT_Process(sInternalTemp);                                               //lut process,including APD,MOD loop

  }
  
#endif

#else
  
  unsigned int unCal_slope;
  signed int sCal_offset;
  signed int sInternalTemp = 0;
  
  //Internal Temperature
  if( ADST_bit.ITEMPI )                                                         //Check if Internal Temperature sensor is completed
  {
      ADST_bit.ITEMPI = 0;                                                      //Clear Internal temperature sensor conversion complete flag
      
      sInternalTemp = ITEMP_DATA;                                               //Read the internal temperature
      
      PAGEA0H_Memory.ADC_INTERNAL_TEMP = __swap_bytes(sInternalTemp);           //update raw adc to A0h 
      UpdateWordA2hTable(PAGE_A0H, &PAGEA0H_Memory.ADC_INTERNAL_TEMP, sInternalTemp);//update A2h Corresponding registers when current table is A0h  
      
      sInternalTemp = TempCalibration( sInternalTemp);                          //internal calibration for internal temperature
      
      unCal_slope = __swap_bytes(PAGE90H_Memory.TEMP_SLOPE);                    //read external slope
      sCal_offset = (signed int)__swap_bytes(PAGE90H_Memory.TEMP_OFFSET);       //read external offset
      
      sInternalTemp = CalibrateSignedDDM(sInternalTemp, unCal_slope, sCal_offset);//external calibration 

      TEMPERATURE = (signed int)__swap_bytes((unsigned int)sInternalTemp);      //udpate DDM
  
      SetSignedAlarmsAndWarnings(TEMP_DDM,sInternalTemp);                       //alarm warning checking
    
      LUT_Process(sInternalTemp);                                               //lut process,including APD,MOD loop

  }

#endif
}

//-----------------------------------------------------------------------------
// ProcessRSSI function
//   - Calculate RSSI, the ADC is from SH block
//-----------------------------------------------------------------------------
void ProcessRSSI(void)
{
#if __SFP28_ER__== 1
// 임시로 막음, RSSI 측정 시 처리 필요
//
//  unsigned int unLow_power_adc = 0, unHigh_power_adc = 0;
//  volatile unsigned int unDdm_value = 0; 
//  unsigned int unCal_slope = 0;
//    signed int sCal_offset = 0;
//    signed int sTemp = 0;
//  
//  sTemp = (signed int) __swap_bytes(PAGEA0H_Memory.ADC_SH0_RX_POWER);           //read current SH0 raw ADC
//  
//  if(sTemp < 0)      
//  {
//     unLow_power_adc   = 0;
//  }
//  else
//  {
//     unLow_power_adc  = (unsigned int)sTemp;
//  }
//  
//  sTemp = (signed int) __swap_bytes(PAGEA0H_Memory.ADC_SH1_RX_POWER);           //read current SH1 raw ADC
//  
//  if(sTemp < 0)
//  {
//     unHigh_power_adc   = 0;
//  }
//  else
//  {
//     unHigh_power_adc  = (unsigned int)sTemp;
//  }
//  
//  /////////////////   RX_POWER (RSSI)       ////////////////////////////
//
//  if(unLow_power_adc < __swap_bytes(PAGE90H_Memory.HIGH_LOW_SWITCH_ADC))        //if SH0 is less than RSSI switch ADC, firmware will use SH0 Raw ADC to calculate RSSI;
//  {
//    unDdm_value = unLow_power_adc;
//    unCal_slope = __swap_bytes(PAGE90H_Memory.RX_POWER_LP_SLOPE);               //read low power scale
//    sCal_offset = (signed int)__swap_bytes((unsigned int)PAGE90H_Memory.RX_POWER_LP_OFFSET);//read low power offset
//  }
//  else                                                                          //if SH0 is bigger than RSSI switch ADC, firmware will use SH1 Raw ADC to calculate RSSI;
//  {
//    unDdm_value = unHigh_power_adc;
//    unCal_slope = __swap_bytes(PAGE90H_Memory.RX_POWER_HP_SLOPE);               //read high power scale
//    sCal_offset = (signed int)__swap_bytes((unsigned int)PAGE90H_Memory.RX_POWER_HP_OFFSET);//read high power offset    
//  } 
//  
//  unDdm_value = CalibrateUnsignedDDM(unDdm_value, unCal_slope, sCal_offset);    //calibrate RSSI
//
//  if(unDdm_value < 1)                                                           //RSSI must > 0, to aviod calculation error in some Host system;
//  {
//    unDdm_value = 1;
//  }
//  
//  RX_POWER = __swap_bytes(unDdm_value);                                         //update RSSI DDM
//
//
//
//  
//  SetUnsignedAlarmsAndWarnings(RXP_DDM, unDdm_value);                           //check RSSI alarm & warning
  

#else

  unsigned int unLow_power_adc = 0, unHigh_power_adc = 0;
  volatile unsigned int unDdm_value = 0; 
  unsigned int unCal_slope = 0;
    signed int sCal_offset = 0;
    signed int sTemp = 0;
  
  sTemp = (signed int) __swap_bytes(PAGEA0H_Memory.ADC_SH0_RX_POWER);           //read current SH0 raw ADC
  
  if(sTemp < 0)      
  {
     unLow_power_adc   = 0;
  }
  else
  {
     unLow_power_adc  = (unsigned int)sTemp;
  }
  
  sTemp = (signed int) __swap_bytes(PAGEA0H_Memory.ADC_SH1_RX_POWER);           //read current SH1 raw ADC
  
  if(sTemp < 0)
  {
     unHigh_power_adc   = 0;
  }
  else
  {
     unHigh_power_adc  = (unsigned int)sTemp;
  }
  
  /////////////////   RX_POWER (RSSI)       ////////////////////////////

  if(unLow_power_adc < __swap_bytes(PAGE90H_Memory.HIGH_LOW_SWITCH_ADC))        //if SH0 is less than RSSI switch ADC, firmware will use SH0 Raw ADC to calculate RSSI;
  {
    unDdm_value = unLow_power_adc;
    unCal_slope = __swap_bytes(PAGE90H_Memory.RX_POWER_LP_SLOPE);               //read low power scale
    sCal_offset = (signed int)__swap_bytes((unsigned int)PAGE90H_Memory.RX_POWER_LP_OFFSET);//read low power offset
  }
  else                                                                          //if SH0 is bigger than RSSI switch ADC, firmware will use SH1 Raw ADC to calculate RSSI;
  {
    unDdm_value = unHigh_power_adc;
    unCal_slope = __swap_bytes(PAGE90H_Memory.RX_POWER_HP_SLOPE);               //read high power scale
    sCal_offset = (signed int)__swap_bytes((unsigned int)PAGE90H_Memory.RX_POWER_HP_OFFSET);//read high power offset    
  } 
  
  unDdm_value = CalibrateUnsignedDDM(unDdm_value, unCal_slope, sCal_offset);    //calibrate RSSI

  if(unDdm_value < 1)                                                           //RSSI must > 0, to aviod calculation error in some Host system;
  {
    unDdm_value = 1;
  }
  
  RX_POWER = __swap_bytes(unDdm_value);                                         //update RSSI DDM



  
  SetUnsignedAlarmsAndWarnings(RXP_DDM, unDdm_value);                           //check RSSI alarm & warning
  

#endif
  
}



//-----------------------------------------------------------------------------
// CalibrateUnsignedDDM function
//   - Calibrate unsigned value for DDM (VCC, bias, TX Power, RX Power)
//-----------------------------------------------------------------------------
#if 0
static unsigned int CalibrateUnsignedDDM(unsigned int unValue, unsigned int unSlope, signed int sOffset)
{
#if __SFP28_ER__== 1

  unsigned int result;
 
  MCNT = 0x23;                                                                  //clear
  MA = unValue;                                                                 //multiply result and slope
  MB = unSlope;
  asm("nop");
  MA = 1;                                                                       //add one for rounding
  MB = 128;                                                                     //this will be last bit shifted, 2^7
  asm("nop");
  
  SHFT_bit.SHVAL = 8;
  SHFT_bit.RSHFT = 1;                                                           //shift right 8 times
   
  MCNT_bit.SUS = 0;                                                             //switch to signed for offset
  MA = 1;                                                              
  MB = (unsigned int)sOffset;                                                   //add offset to accumlator
  asm("nop");
  
  if(MC2 == 0xFFFF)                                                             //now a negative number
  {
   result = 0;                                                                  //clamp to 0
  }
  else if(MC1)                                                                  //greater than 16 bit
  {
   result = 0xFFFF;                                                             //clamp to full scale
  }
  else
  {
     result = MC0;                                                              //return calculated results
  }
  
  return(result);
 
#else

  unsigned int result;
 
  MCNT = 0x23;                                                                  //clear
  MA = unValue;                                                                 //multiply result and slope
  MB = unSlope;
  asm("nop");
  MA = 1;                                                                       //add one for rounding
  MB = 128;                                                                     //this will be last bit shifted, 2^7
  asm("nop");
  
  SHFT_bit.SHVAL = 8;
  SHFT_bit.RSHFT = 1;                                                           //shift right 8 times
   
  MCNT_bit.SUS = 0;                                                             //switch to signed for offset
  MA = 1;                                                              
  MB = (unsigned int)sOffset;                                                   //add offset to accumlator
  asm("nop");
  
  if(MC2 == 0xFFFF)                                                             //now a negative number
  {
   result = 0;                                                                  //clamp to 0
  }
  else if(MC1)                                                                  //greater than 16 bit
  {
   result = 0xFFFF;                                                             //clamp to full scale
  }
  else
  {
     result = MC0;                                                              //return calculated results
  }
  
  return(result);
 
#endif
 
}


//-----------------------------------------------------------------------------
// CalibrateSignedDDM function
//   - Calibrate signed value for DDM (Temperature, TEC Current, Laser Temp)
//-----------------------------------------------------------------------------
static signed int CalibrateSignedDDM(signed int unValue, unsigned int unSlope, signed int sOffset)
{
#if __SFP28_ER__== 1
  signed int result;
  
  MCNT = 0x23;                                                                  //clear
  MCNT_bit.SUS = 0;                                                             //need signed operation
  
  MA = (unsigned int)unValue;                                                   //multiply result and slope
  MB = unSlope;
  asm("nop");
  MA = 1;                                                                       //add one for rounding
  MB = 128;                                                                     //this will be last bit shifted, 2^7
  asm("nop");
  
  SHFT_bit.SHVAL = 8;
  SHFT_bit.RSHFT = 1;                                                           //shift right 8 times
   
  MCNT_bit.SUS = 0;                                                             //switch to signed for offset
  MA = 1;                                                              
  MB = (unsigned int)sOffset;                                                   //add offset to accumlator
  asm("nop");
  
  result = (signed int)MC0;
  
  return(result);

#else
  signed int result;
  
  MCNT = 0x23;                                                                  //clear
  MCNT_bit.SUS = 0;                                                             //need signed operation
  
  MA = (unsigned int)unValue;                                                   //multiply result and slope
  MB = unSlope;
  asm("nop");
  MA = 1;                                                                       //add one for rounding
  MB = 128;                                                                     //this will be last bit shifted, 2^7
  asm("nop");
  
  SHFT_bit.SHVAL = 8;
  SHFT_bit.RSHFT = 1;                                                           //shift right 8 times
   
  MCNT_bit.SUS = 0;                                                             //switch to signed for offset
  MA = 1;                                                              
  MB = (unsigned int)sOffset;                                                   //add offset to accumlator
  asm("nop");
  
  result = (signed int)MC0;
  
  return(result);

#endif
}

#endif

//-----------------------------------------------------------------------------
// ConvertVccScale function
//Can be changed to MAC, if timing become critical. This is used for 6.5535V full scale
//Used for Vcc measurement. Convert 1.2V to 
//1.22/6.55 = 0.18626 = ~1526/8192 => 0.18628

//  1.22/2^12 = 297.85uV per lsb
//    297.85uV / 100uV = 2.9785
//    2.9785 * 4 = 11.914  because of internal divide by 4 for VCC
//    11.914 ~= 3050 / 256
//-----------------------------------------------------------------------------
static unsigned int ConvertVccScale(unsigned int unAdc_value)   
{
#if __SFP28_ER__== 1

  unsigned long unScaled_value;
   
   unScaled_value = (unsigned long)unAdc_value;

   unScaled_value = unScaled_value * 375;                                       //Multiple by 1526
   
   unScaled_value = unScaled_value >> 8;                                        //Divide by 8192
   
   return (unsigned int)unScaled_value;               

#else

  unsigned long unScaled_value;
   
   unScaled_value = (unsigned long)unAdc_value;

   unScaled_value = unScaled_value * 375;                                       //Multiple by 1526
   
   unScaled_value = unScaled_value >> 8;                                        //Divide by 8192
   
   return (unsigned int)unScaled_value;               

#endif
}




#if 0
static unsigned int ApplyInternalScale(unsigned int unRaw_adc, unsigned int unScale, signed int sOffset)
{
   unsigned long ulCalibration_data;

   if(ADST_bit.VOFF_CANCEL)
   {
     ulCalibration_data = unRaw_adc;
   }
   else
   {
     if(unRaw_adc > sOffset)
     {
       ulCalibration_data = unRaw_adc - sOffset;
     }
     else
     {
       ulCalibration_data = 0;
     }
   }
  
   //Scale multiplication
   ulCalibration_data = ulCalibration_data * unScale;
   
   ulCalibration_data = ulCalibration_data >> 12;


   //Limit check
   if(ulCalibration_data > 0xFFFF )
   {
      ulCalibration_data = 0xFFFF;
   }
   
   return (unsigned int)ulCalibration_data;    
}
#endif

//-----------------------------------------------------------------------------
// CalibConstantRead function
//   - Read factory calibration factor
//-----------------------------------------------------------------------------
void CalibConstantRead(void)
{
#if __SFP28_ER__== 1

   unAdc_scale   = Info_Read(ADDRESS_ADC_FACTORY_SCALE);                        //read factory adc scale
   sAdc_offset   = (signed int) Info_Read(ADDRESS_ADC_FACTORY_OFFSET);          //read factory adc offset
   unTemp_scale  = Info_Read(ADDRESS_ADC_FACTORY_TEMP_SCALE);                   //read factory temp scale
   sTemp_offset  = (signed int) Info_Read(ADDRESS_ADC_FACTORY_TEMP_OFFSET);     //read factory temp offset

#else

   unAdc_scale   = Info_Read(ADDRESS_ADC_FACTORY_SCALE);                        //read factory adc scale
   sAdc_offset   = (signed int) Info_Read(ADDRESS_ADC_FACTORY_OFFSET);          //read factory adc offset
   unTemp_scale  = Info_Read(ADDRESS_ADC_FACTORY_TEMP_SCALE);                   //read factory temp scale
   sTemp_offset  = (signed int) Info_Read(ADDRESS_ADC_FACTORY_TEMP_OFFSET);     //read factory temp offset

#endif
   
}


//-----------------------------------------------------------------------------
// SH0 ISR function
//   - SH0 interrupt service routine
//-----------------------------------------------------------------------------
#pragma vector = 4
__interrupt void SH_Interrupt(void)
{
#if __SFP28_ER__== 1
////    unsigned int unAdc = 0;
//    
//    MACSEL_bit.MACRSEL = 1;                                                     //switch to user MAC
//    
//    if((ADST_bit.SH0I)&&(ADST_bit.SH1I))                                        //if SH0 and SH1 are ready to read
//    {
////      unAdc = SH0_DATA;                                                         //read raw adc
////      
////      PAGEA0H_Memory.ADC_SH0_RX_POWER = __swap_bytes(unAdc);                    //update raw adc to readout table
////      UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_SH0_RX_POWER, unAdc);     //update A2h Corresponding registers when current table is A0h  
////      
////      unAdc = SH1_DATA;                                                         //read raw adc
////      
////      PAGEA0H_Memory.ADC_SH1_RX_POWER = __swap_bytes(unAdc);                    //update raw adc to readout table
////      UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_SH1_RX_POWER, unAdc);     //update A2h Corresponding registers when current table is A0h  
////      
//      ADST_bit.SH0I = 0;                                                        //clear SHI flag
//      ADST_bit.SH1I = 0;                                                        //clear SHI flag
//      
//      ProcessRSSI();                                                            //calibrate RSSI                                                
//      MonitorRXLOS();                                                           //monitor RX LOS
//      
//    } 
//
//    MACSEL_bit.MACRSEL = 0;                                                     //switch to user MAC 
//    IMR = GP_REG1;                                                              //restore IMR

#else
    unsigned int unAdc = 0;
    
    MACSEL_bit.MACRSEL = 1;                                                     //switch to user MAC
    
    if((ADST_bit.SH0I)&&(ADST_bit.SH1I))                                        //if SH0 and SH1 are ready to read
    {
      unAdc = SH0_DATA;                                                         //read raw adc
      
      PAGEA0H_Memory.ADC_SH0_RX_POWER = __swap_bytes(unAdc);                    //update raw adc to readout table
      UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_SH0_RX_POWER, unAdc);     //update A2h Corresponding registers when current table is A0h  
      
      unAdc = SH1_DATA;                                                         //read raw adc
      
      PAGEA0H_Memory.ADC_SH1_RX_POWER = __swap_bytes(unAdc);                    //update raw adc to readout table
      UpdateWordA2hTable(PAGE_A0H,&PAGEA0H_Memory.ADC_SH1_RX_POWER, unAdc);     //update A2h Corresponding registers when current table is A0h  
      
      ADST_bit.SH0I = 0;                                                        //clear SHI flag
      ADST_bit.SH1I = 0;                                                        //clear SHI flag
      
      ProcessRSSI();                                                            //calibrate RSSI                                                
      MonitorRXLOS();                                                           //monitor RX LOS
      
    } 

    MACSEL_bit.MACRSEL = 0;                                                     //switch to user MAC 
    IMR = GP_REG1;                                                              //restore IMR

#endif
}


//-----------------------------------------------------------------------------
// end of file
//-----------------------------------------------------------------------------

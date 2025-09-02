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
#include <iods4835.h>
#include "includes.h"
#include "intrinsics.h"


////////////////////////////////////////////////////////////////////////////////
//Soft Reset the CDR
////////////////////////////////////////////////////////////////////////////////
void Driver_SoftReset(unsigned char ucSlave_address, PAGE04H_MEMORY_MAP *DRIVER_MEMORY)
{
#if __QSFP28_LR4__== 1
  
  unsigned char fail = 0;
  PAGE04H_MEMORY_MAP * CDR_DRIVER_MEMORY = (PAGE04H_MEMORY_MAP *)&I2C_Slave_Buffer_A0_P4_Up[0];
     
     //Set Soft Reset bit in the TOP CTRL Register
     CDR_DRIVER_MEMORY->P00_RESET = COMMAND_DEVICE_RESET;
	 
     //Write Global Control Register
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P00_RESET,  (unsigned char *)&CDR_DRIVER_MEMORY->P00_RESET, 1); 

     //Clear Soft Control Register
     CDR_DRIVER_MEMORY->P00_RESET =0x00;

#elif __SFP28_ER__==1
     
#else
  
  unsigned char fail = 0;
     
     //Set Soft Reset bit in the TOP CTRL Register
     DRIVER_MEMORY->TOPCTRL |= COMMAND_DEVICE_RESET;
	 
     //Write Global Control Register
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_TOPCTRL,  (unsigned char *)&DRIVER_MEMORY->TOPCTRL, 1); 

     //Clear Soft Control Register
     DRIVER_MEMORY->TOPCTRL &=~1;

#endif
}


////////////////////////////////////////////////////////////////////////////////
//Write TX Registers to CDR
////////////////////////////////////////////////////////////////////////////////
void Driver_TXControlRegsWrite(unsigned char ucSlave_address, PAGE04H_MEMORY_MAP *DRIVER_MEMORY)
{
#if __QSFP28_LR4__== 1
  
  unsigned char fail = 0;
  unsigned char tmp_page_sel[4];
  unsigned char idx;
  PAGE04H_MEMORY_MAP * CDR_DRIVER_MEMORY = (PAGE04H_MEMORY_MAP *)&I2C_Slave_Buffer_A0_P4_Up[0];
     
     //Write Global Control Registers
     // Page 00h
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P00_RX_BIAS_CURRENT,     (unsigned char *)&CDR_DRIVER_MEMORY->P00_RX_BIAS_CURRENT, 1);     
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P00_RX_RSSI_MONCLK,     (unsigned char *)&CDR_DRIVER_MEMORY->P00_RX_RSSI_MONCLK, 1);     
     
     for (idx=0; idx < 4; idx++) {
       fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P00_RX_CH_MODE_N(idx),     (unsigned char *)&CDR_DRIVER_MEMORY->P00_RX_CH_MODE_N[idx], 1);     
       fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P00_RX_CH_AFE_MISCL_N(idx),     (unsigned char *)&CDR_DRIVER_MEMORY->P00_RX_CH_AFE_MISCL_N[idx], 1);    
       fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P00_RX_CH_SLA_N(idx),     (unsigned char *)&CDR_DRIVER_MEMORY->P00_RX_CH_SLA_N[idx], 1);    
       fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P00_RX_CH_LOKPHASEADJ_N(idx),     (unsigned char *)&CDR_DRIVER_MEMORY->P00_RX_CH_LOKPHASEADJ_N[idx], 1);    

       fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P00_RX_CH_OUTPUT_SWING_N(idx),     (unsigned char *)&CDR_DRIVER_MEMORY->P00_RX_CH_OUTPUT_SWING_N[idx], 1);    
       fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P00_RX_CH_OUTPUT_DEEMPH_N(idx),     (unsigned char *)&CDR_DRIVER_MEMORY->P00_RX_CH_OUTPUT_DEEMPH_N[idx], 1);    
       fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P00_RX_CH_OUTPUT_XPADJ_N(idx),     (unsigned char *)&CDR_DRIVER_MEMORY->P00_RX_CH_OUTPUT_XPADJ_N[idx], 1);    
     }
     
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P00_RX_TIA_CTRL,     (unsigned char *)&CDR_DRIVER_MEMORY->P00_RX_TIA_CTRL, 1);     
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P00_RX_CDR_LBW,     (unsigned char *)&CDR_DRIVER_MEMORY->P00_RX_CDR_LBW, 1);     
     
     // Page 01h
     tmp_page_sel[0] = 1; // Select Page 01h
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P00_REG_PAGE,     (unsigned char *)&tmp_page_sel[0], 1);     
     
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P01_TX_BIAS_CURRENT,     (unsigned char *)&CDR_DRIVER_MEMORY->P01_TX_BIAS_CURRENT, 1);     
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P01_TX_MONCLK,     (unsigned char *)&CDR_DRIVER_MEMORY->P01_TX_MONCLK, 1);     

     for (idx=0; idx < 4; idx++) {
       fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P01_TX_CH_MODE_N(idx),     (unsigned char *)&CDR_DRIVER_MEMORY->P01_TX_CH_MODE_N[idx], 1);     
       fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P01_TX_CH_AFE_MISCL_N(idx),     (unsigned char *)&CDR_DRIVER_MEMORY->P01_TX_CH_AFE_MISCL_N[idx], 1);     
       fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P01_TX_CH_CTLE_N(idx),     (unsigned char *)&CDR_DRIVER_MEMORY->P01_TX_CH_CTLE_N[idx], 1); 
       
       fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P01_TX_CH_LOKPHASEADJ_N(idx),     (unsigned char *)&CDR_DRIVER_MEMORY->P01_TX_CH_LOKPHASEADJ_N[idx], 1);     
       fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P01_TX_CH_OUTPUT_IBIAS_N(idx),     (unsigned char *)&CDR_DRIVER_MEMORY->P01_TX_CH_OUTPUT_IBIAS_N[idx], 1);     
       fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P01_TX_CH_OUTPUT_IMOD_N(idx),     (unsigned char *)&CDR_DRIVER_MEMORY->P01_TX_CH_OUTPUT_IMOD_N[idx], 1);    
       
       fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P01_TX_CH_OUTPUT_PreFall_N(idx),     (unsigned char *)&CDR_DRIVER_MEMORY->P01_TX_CH_OUTPUT_PreFall_N[idx], 1);    
       fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P01_TX_CH_OUTPUT_EYE_N(idx),     (unsigned char *)&CDR_DRIVER_MEMORY->P01_TX_CH_OUTPUT_EYE_N[idx], 1);    

     }
     
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P01_TX_FAULT_ALARM,     (unsigned char *)&CDR_DRIVER_MEMORY->P01_TX_FAULT_ALARM, 1);     
  
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P01_TX_IGNORE_TXFAULT,     (unsigned char *)&CDR_DRIVER_MEMORY->P01_TX_IGNORE_TXFAULT, 1);     
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P01_TX_CDR_LBW,     (unsigned char *)&CDR_DRIVER_MEMORY->P01_TX_CDR_LBW, 1);     
     
#elif __SFP28_ER__==1
     
#else
  
  unsigned char fail = 0;
     
     //Write Global Control Registers
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_TXCTRL1,     (unsigned char *)&DRIVER_MEMORY->TXCTRL1, 1);
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_TXCTRL2,     (unsigned char *)&DRIVER_MEMORY->TXCTRL2, 1);     
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_TXCTRL3,     (unsigned char *)&DRIVER_MEMORY->TXCTRL3, 1);
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_TXCTRL4,     (unsigned char *)&DRIVER_MEMORY->TXCTRL4, 1);      
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_TXCTRL5,     (unsigned char *)&DRIVER_MEMORY->TXCTRL5, 1);
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_TXCTRL6,     (unsigned char *)&DRIVER_MEMORY->TXCTRL6, 1); 
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_TXCTRL7,     (unsigned char *)&DRIVER_MEMORY->TXCTRL7, 1);
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_TXCTRL8,     (unsigned char *)&DRIVER_MEMORY->TXCTRL8, 1); 
  
#endif
}

////////////////////////////////////////////////////////////////////////////////
//Write TX  Registers to driver
////////////////////////////////////////////////////////////////////////////////
void Driver_TXRegsWrite(unsigned char ucSlave_address, PAGE04H_MEMORY_MAP *DRIVER_MEMORY)
{
#if __QSFP28_LR4__== 1
//     unsigned char fail = 0;

#elif __SFP28_ER__==1
     

#else
     unsigned char fail = 0;

     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_MODMAX,      (unsigned char *)&DRIVER_MEMORY->MODMAX, 1); 
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_APCCTRL1,    (unsigned char *)&DRIVER_MEMORY->APCCTRL1, 1);
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_APCCTRL2,    (unsigned char *)&DRIVER_MEMORY->APCCTRL2, 1);      
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_SET_APC0,    (unsigned char *)&DRIVER_MEMORY->SET_APC0, 1);      
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_SET_APC1,    (unsigned char *)&DRIVER_MEMORY->SET_APC1, 1);
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_BIASMAX,     (unsigned char *)&DRIVER_MEMORY->BIASMAX, 1);  
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_MPDMAX,      (unsigned char *)&DRIVER_MEMORY->MPDMAX, 1);       
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_LDOCTRL,     (unsigned char *)&DRIVER_MEMORY->LDOCTRL, 1); 
  
#endif

}


////////////////////////////////////////////////////////////////////////////////
//Write RX Registers to CDR
////////////////////////////////////////////////////////////////////////////////
void Driver_RXRegsWrite(unsigned char ucSlave_address, PAGE04H_MEMORY_MAP *DRIVER_MEMORY)
{
#if __QSFP28_LR4__== 1
//     unsigned char fail = 0;
  
#elif __SFP28_ER__==1
     

#else
     unsigned char fail = 0;
     
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_RXCTRL1,     (unsigned char *)&DRIVER_MEMORY->RXCTRL1, 1);
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_RXCTRL2,     (unsigned char *)&DRIVER_MEMORY->RXCTRL2, 1);  
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_RXCTRL3,     (unsigned char *)&DRIVER_MEMORY->RXCTRL3, 1);  
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_RXCTRL4,     (unsigned char *)&DRIVER_MEMORY->RXCTRL4, 1);
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_RXLOS1,      (unsigned char *)&DRIVER_MEMORY->RXLOS1, 1);  
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_RXLOS2,      (unsigned char *)&DRIVER_MEMORY->RXLOS2, 1);       
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_RXLOS3,      (unsigned char *)&DRIVER_MEMORY->RXLOS3, 1);  
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_RXLOS4,      (unsigned char *)&DRIVER_MEMORY->RXLOS4, 1);     
 
#endif

}

////////////////////////////////////////////////////////////////////////////////
//Write Top Control Registers to driver
////////////////////////////////////////////////////////////////////////////////
void Driver_TopCtrlRegsWrite(unsigned char ucSlave_address, PAGE04H_MEMORY_MAP *DRIVER_MEMORY)
{
#if __QSFP28_LR4__== 1
//     unsigned char fail = 0;

#elif __SFP28_ER__==1
     
 
#else
     unsigned char fail = 0;

     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_TOPCTRL,     (unsigned char *)&DRIVER_MEMORY->TOPCTRL, 1); 
  
#endif
}

////////////////////////////////////////////////////////////////////////////////
//Write control Registers to driver
////////////////////////////////////////////////////////////////////////////////
void Driver_ControlRegsWrite(unsigned char ucSlave_address, PAGE04H_MEMORY_MAP *DRIVER_MEMORY)
{
#if __QSFP28_LR4__== 1
//     unsigned char fail = 0;
     
#elif __SFP28_ER__==1
     
 
#else
     unsigned char fail = 0;
     
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_FAULTCTRL,   (unsigned char *)&DRIVER_MEMORY->FAULTCTRL, 1);
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_FAULTMASK1,  (unsigned char *)&DRIVER_MEMORY->FAULTMASK1, 1);  
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_FAULTMASK2,  (unsigned char *)&DRIVER_MEMORY->FAULTMASK2, 1);  
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_EVENT1,      (unsigned char *)&DRIVER_MEMORY->EVENT1, 1);  
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_EVENT2,      (unsigned char *)&DRIVER_MEMORY->EVENT2, 1);  
  
#endif

}

////////////////////////////////////////////////////////////////////////////////
//Read MAX24016 TOPSTAT Register 
////////////////////////////////////////////////////////////////////////////////
void Driver_ReadTOPSTAT(unsigned char ucSlave_address, PAGE04H_MEMORY_MAP *DRIVER_MEMORY)
{
#if __QSFP28_LR4__== 1
//     unsigned char fail = 0;
      
#elif __SFP28_ER__==1
     

#else
     unsigned char fail = 0;
      
     //Write Global Control Register
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_TOPSTAT,  (unsigned char *)&DRIVER_MEMORY->TOPSTAT, 1 );  
  
#endif
}

////////////////////////////////////////////////////////////////////////////////
//Read MAX24016 RXSTAT Register 
////////////////////////////////////////////////////////////////////////////////
void Driver_ReadRXSTAT(unsigned char ucSlave_address, PAGE04H_MEMORY_MAP *DRIVER_MEMORY)
{
#if __QSFP28_LR4__== 1
//     unsigned char fail = 0;
#elif __SFP28_ER__==1
     

#else
     unsigned char fail = 0;
            
     //Write Global Control Register
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_RXSTAT,  (unsigned char *)&DRIVER_MEMORY->RXSTAT, 1);  
  
#endif

}

////////////////////////////////////////////////////////////////////////////////
//Read MAX24016 TXSTAT Register 
////////////////////////////////////////////////////////////////////////////////
void Driver_ReadTXSTAT(unsigned char ucSlave_address, PAGE04H_MEMORY_MAP *DRIVER_MEMORY)
{
#if __QSFP28_LR4__== 1
//     unsigned char fail = 0;
#elif __SFP28_ER__==1
     
 
#else
     unsigned char fail = 0;
            
     //Write Global Control Register
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_TXSTAT,  (unsigned char *)&DRIVER_MEMORY->TXSTAT, 1);  
  
#endif

}

////////////////////////////////////////////////////////////////////////////////
//ReadGlobal Registers from the driver
////////////////////////////////////////////////////////////////////////////////
void Driver_TXControlRegsRead(unsigned char ucSlave_address, PAGE04H_MEMORY_MAP *DRIVER_MEMORY)
{
#if __QSFP28_LR4__== 1
//     unsigned char fail = 0;
#elif __SFP28_ER__==1
     

#else
     unsigned char fail = 0;
     
     //Write Global Control Registers
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_TXCTRL1,     (unsigned char *)&DRIVER_MEMORY->TXCTRL1, 1);
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_TXCTRL2,     (unsigned char *)&DRIVER_MEMORY->TXCTRL2, 1);     
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_TXCTRL3,     (unsigned char *)&DRIVER_MEMORY->TXCTRL3, 1);
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_TXCTRL4,     (unsigned char *)&DRIVER_MEMORY->TXCTRL4, 1);      
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_TXCTRL5,     (unsigned char *)&DRIVER_MEMORY->TXCTRL5, 1);
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_TXCTRL6,     (unsigned char *)&DRIVER_MEMORY->TXCTRL6, 1); 
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_TXCTRL7,     (unsigned char *)&DRIVER_MEMORY->TXCTRL7, 1);
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_TXCTRL8,     (unsigned char *)&DRIVER_MEMORY->TXCTRL8, 1); 
  
#endif

}

////////////////////////////////////////////////////////////////////////////////
//Read TX Registers from driver
////////////////////////////////////////////////////////////////////////////////
void Driver_TXRegsRead(unsigned char ucSlave_address, PAGE04H_MEMORY_MAP *DRIVER_MEMORY)
{
#if __QSFP28_LR4__== 1
//     unsigned char fail = 0;
#elif __SFP28_ER__==1
     
 
#else
     unsigned char fail = 0;
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_SET_MOD0,    (unsigned char *)&DRIVER_MEMORY->SET_MOD0, 1);      
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_SET_MOD1,    (unsigned char *)&DRIVER_MEMORY->SET_MOD1, 1);
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_MODMAX,      (unsigned char *)&DRIVER_MEMORY->MODMAX, 1); 
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_APCCTRL1,    (unsigned char *)&DRIVER_MEMORY->APCCTRL1, 1);
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_APCCTRL2,    (unsigned char *)&DRIVER_MEMORY->APCCTRL2, 1);      
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_SET_APC0,    (unsigned char *)&DRIVER_MEMORY->SET_APC0, 1);      
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_SET_APC1,    (unsigned char *)&DRIVER_MEMORY->SET_APC1, 1);
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_SET_BIAS0,   (unsigned char *)&DRIVER_MEMORY->SET_BIAS0, 1); 
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_SET_BIAS1,   (unsigned char *)&DRIVER_MEMORY->SET_BIAS1, 1);
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_BIASMAX,     (unsigned char *)&DRIVER_MEMORY->BIASMAX, 1);  
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_MPDMAX,      (unsigned char *)&DRIVER_MEMORY->MPDMAX, 1);       
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_LDOCTRL,     (unsigned char *)&DRIVER_MEMORY->LDOCTRL, 1); 
  
#endif

}

////////////////////////////////////////////////////////////////////////////////
//Read RX Registers to CDR
////////////////////////////////////////////////////////////////////////////////
void Driver_RXRegsRead(unsigned char ucSlave_address, PAGE04H_MEMORY_MAP *DRIVER_MEMORY)
{
#if __QSFP28_LR4__== 1
//     unsigned char fail = 0;
     
#elif __SFP28_ER__==1
     

#else
     unsigned char fail = 0;
     
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_RXCTRL1,     (unsigned char *)&DRIVER_MEMORY->RXCTRL1, 1);
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_RXCTRL2,     (unsigned char *)&DRIVER_MEMORY->RXCTRL2, 1);  
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_RXCTRL3,     (unsigned char *)&DRIVER_MEMORY->RXCTRL3, 1);  
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_RXCTRL4,     (unsigned char *)&DRIVER_MEMORY->RXCTRL4, 1);
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_RXLOS1,      (unsigned char *)&DRIVER_MEMORY->RXLOS1, 1);  
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_RXLOS2,      (unsigned char *)&DRIVER_MEMORY->RXLOS2, 1);       
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_RXLOS3,      (unsigned char *)&DRIVER_MEMORY->RXLOS3, 1);  
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_RXLOS4,      (unsigned char *)&DRIVER_MEMORY->RXLOS4, 1);     
  
#endif
  
     

}
////////////////////////////////////////////////////////////////////////////////
//Read control Registers from driver
////////////////////////////////////////////////////////////////////////////////
void Driver_ControlRegsRead(unsigned char ucSlave_address, PAGE04H_MEMORY_MAP *DRIVER_MEMORY)
{
#if __QSFP28_LR4__== 1
//     unsigned char fail = 0;
#elif __SFP28_ER__==1
     

#else
     unsigned char fail = 0;
     
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_FAULTCTRL,   (unsigned char *)&DRIVER_MEMORY->FAULTCTRL, 1);
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_FAULTMASK1,  (unsigned char *)&DRIVER_MEMORY->FAULTMASK1, 1);  
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_FAULTMASK2,  (unsigned char *)&DRIVER_MEMORY->FAULTMASK2, 1);  
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_TOPCTRL,     (unsigned char *)&DRIVER_MEMORY->TOPCTRL, 1); 
  
#endif
}

////////////////////////////////////////////////////////////////////////////////
//Read status Registers from driver
////////////////////////////////////////////////////////////////////////////////
void Driver_StatusRegsRead(unsigned char ucSlave_address, PAGE04H_MEMORY_MAP *DRIVER_MEMORY)
{
#if __QSFP28_LR4__== 1
//     unsigned char fail = 0;
#elif __SFP28_ER__==1
     

#else
     unsigned char fail = 0;
     
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_PINSTAT,     (unsigned char *)&DRIVER_MEMORY->PINSTAT, 1); 
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_FAULTSTAT1,  (unsigned char *)&DRIVER_MEMORY->FAULTSTAT1, 1);  
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_FAULTSTAT2,  (unsigned char *)&DRIVER_MEMORY->FAULTSTAT2, 1);      
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_DDMSTAT15,   (unsigned char *)&DRIVER_MEMORY->DDMSTAT15, 1);  
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_DDMSTAT16,   (unsigned char *)&DRIVER_MEMORY->DDMSTAT16, 1);      
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_DDMSTAT17,   (unsigned char *)&DRIVER_MEMORY->DDMSTAT17, 1);  
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_DDMSTAT18,   (unsigned char *)&DRIVER_MEMORY->DDMSTAT18, 1);  
     fail |= I2CM_ReadNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_RXPU,        (unsigned char *)&DRIVER_MEMORY->RXPU, 1);      
   
#endif
  
}


////////////////////////////////////////////////////////////////////////////////
//Driver Bias and Mod setting
////////////////////////////////////////////////////////////////////////////////

/* Customer can modify following code for Bias and Mod setting when using other driver */
void Driver_TXModWrite(unsigned char ucSlave_address, PAGE04H_MEMORY_MAP *DRIVER_MEMORY)
{
#if __QSFP28_LR4__== 1
     unsigned char fail = 0;
     unsigned char tmp_page_sel[4];
     unsigned char idx;
     PAGE04H_MEMORY_MAP * CDR_DRIVER_MEMORY = (PAGE04H_MEMORY_MAP *)&I2C_Slave_Buffer_A0_P4_Up[0];
//     unsigned char mod_value;
     
     tmp_page_sel[0] = 1; // Select Page 01h
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P00_REG_PAGE,     (unsigned char *)&tmp_page_sel[0], 1);     

//     mod_value = DRIVER_MEMORY->SET_MOD1;
     for (idx=0; idx<4; idx++)
     {
//       mod_value = CDR_DRIVER_MEMORY->P01_TX_CH_OUTPUT_IMOD_N[idx];
//       CDR_DRIVER_MEMORY->P01_TX_CH_OUTPUT_IMOD_N[idx] = mod_value;
       fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P01_TX_CH_OUTPUT_IMOD_N(idx),    (unsigned char *)&CDR_DRIVER_MEMORY->P01_TX_CH_OUTPUT_IMOD_N[idx], 1);      
     }

//     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_SET_MOD0,    (unsigned char *)&DRIVER_MEMORY->SET_MOD0, 1);      
//     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_SET_MOD1,    (unsigned char *)&DRIVER_MEMORY->SET_MOD1, 1);

#elif __SFP28_ER__==1
     

#else
     unsigned char fail = 0;
     
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_SET_MOD0,    (unsigned char *)&DRIVER_MEMORY->SET_MOD0, 1);      
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_SET_MOD1,    (unsigned char *)&DRIVER_MEMORY->SET_MOD1, 1);
  
#endif


}

void Driver_TXBiasWrite(unsigned char ucSlave_address, PAGE04H_MEMORY_MAP *DRIVER_MEMORY)
{
#if __QSFP28_LR4__== 1
     unsigned char fail = 0;
     unsigned char tmp_page_sel[4];
     unsigned char idx;
     PAGE04H_MEMORY_MAP * CDR_DRIVER_MEMORY = (PAGE04H_MEMORY_MAP *)&I2C_Slave_Buffer_A0_P4_Up[0];
     unsigned char ibias_value;
     
     tmp_page_sel[0] = 1; // Select Page 01h
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P00_REG_PAGE,     (unsigned char *)&tmp_page_sel[0], 1);     

//     ibias_value = DRIVER_MEMORY->SET_BIAS1;
     for (idx=0; idx<4; idx++)
     {
       CDR_DRIVER_MEMORY->P01_TX_CH_OUTPUT_IBIAS_N[idx] = ibias_value;
       fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_P01_TX_CH_OUTPUT_IBIAS_N(idx),    (unsigned char *)&CDR_DRIVER_MEMORY->P01_TX_CH_OUTPUT_IBIAS_N[idx], 1);      
     }
     
//     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_SET_BIAS0,   (unsigned char *)&DRIVER_MEMORY->SET_BIAS0, 1); 
//     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_SET_BIAS1,   (unsigned char *)&DRIVER_MEMORY->SET_BIAS1, 1);

#elif __SFP28_ER__==1
     

#else
     unsigned char fail = 0;
     
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_SET_BIAS0,   (unsigned char *)&DRIVER_MEMORY->SET_BIAS0, 1); 
     fail |= I2CM_WriteNBytes(I2CM_MASTER_1, ucSlave_address, ADDR_SET_BIAS1,   (unsigned char *)&DRIVER_MEMORY->SET_BIAS1, 1);
  
#endif


}


////////////////////////////////////////////////////////////////////////////////
//Driver Initialization
////////////////////////////////////////////////////////////////////////////////
void Driver_Init(unsigned char ucSlave_address, PAGE04H_MEMORY_MAP *DRIVER_MEMORY )
{
#if __QSFP28_LR4__== 1
     //Softe reset Max24016
     //Driver_SoftReset(ucSlave_address,DRIVER_MEMORY);
     
     SW_Delay(1000);
     
     //Write TX Register
     Driver_TXRegsWrite(ucSlave_address, DRIVER_MEMORY);
     
     //Write TX control Register
     Driver_TXControlRegsWrite(ucSlave_address, DRIVER_MEMORY);
     
     //Write RX Register
     Driver_RXRegsWrite(ucSlave_address, DRIVER_MEMORY);

     //Write Control Register
     Driver_ControlRegsWrite(ucSlave_address, DRIVER_MEMORY);     

     //Read driver status register   
     Driver_StatusRegsRead(ucSlave_address, DRIVER_MEMORY);
     
     //Write Top control Register
     Driver_TopCtrlRegsWrite(ucSlave_address, DRIVER_MEMORY);

#elif __SFP28_ER__==1
     

#else
     //Softe reset Max24016
     //Driver_SoftReset(ucSlave_address,DRIVER_MEMORY);
     
     SW_Delay(1000);
     
     //Write TX Register
     Driver_TXRegsWrite(ucSlave_address, DRIVER_MEMORY);
     
     //Write TX control Register
     Driver_TXControlRegsWrite(ucSlave_address, DRIVER_MEMORY);
     
     //Write RX Register
     Driver_RXRegsWrite(ucSlave_address, DRIVER_MEMORY);

     //Write Control Register
     Driver_ControlRegsWrite(ucSlave_address, DRIVER_MEMORY);     

     //Read driver status register   
     Driver_StatusRegsRead(ucSlave_address, DRIVER_MEMORY);
     
     //Write Top control Register
     Driver_TopCtrlRegsWrite(ucSlave_address, DRIVER_MEMORY);
  
#endif

}

//End
//-----------------------------------------------------------------------------
// end of file
//-----------------------------------------------------------------------------

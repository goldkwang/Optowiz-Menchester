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
#include <intrinsics.h>
#include <iods4835.h>


#include "includes.h"
//#include "MemoryAccess.h"
//#include "i2cslave.h"
//#include "memory_map.h"

//-----------------------------------------------------------------------------
// global variables defined in this module
//-----------------------------------------------------------------------------
   
static unsigned char ActiveSlave;

//unsigned int Rx_Count;
//unsigned int Mem_Address;

//-----------------------------------------------------------------------------
// external global variables defined elsewhere
//-----------------------------------------------------------------------------
extern unsigned char PasswordLevel;

//extern unsigned char sfpStat[];
extern WriteBuffer_S twsiSlaveBuf;

static void I2C_Slave_Stop(void);
__interrupt void I2CS_Interrupt(void);

//-----------------------------------------------------------------------------
// SmbusInit() function
//   - initialize the slave I2C port 
//-----------------------------------------------------------------------------

void I2CS_Init(void)
{    
#if __SFP28_ER__ == 1
  
  I2CCN_S = 0x0000;                                                            //Clear All I2C modules Settings
   I2CIE_S = 0x0000;
   I2CST_S = 0x0000;
   I2CCN_S = 0x0000;    
    
   MADDR = A2_LOWER_SRAM_OFFSET;                                                //Slave Address 1 (I2CSLA_S = A0), set location
   MADDR_bit.ROLLOVR = 1;                                                       //256 bit rollover
   
   MADDR2 = A0_SRAM_OFFSET;                                                     //Slave Address 2 (I2CSLA2_S = A4), set location
   MADDR2_bit.ROLLOVR = 1;                                                      //256 bit rollover

 
   I2CTXFIE_bit.TXPG_EN = 1;                                                    //Enable Tx Pages
   CUR_SLA_bit.MADDR_EN1 = 1;                                                   //Enable Mem Address detection for Slave Address (0xA2) 
   CUR_SLA_bit.MADDR_EN2 = 1;                                                   //Enable Mem Address detection for Slave Address (0xA0) 
   I2CIE2_S_bit.MADIE = 1;                                                      //Enable Interrupt for Memory Address 
   I2CIE2_S_bit.SADIE = 1;                                                      //Enable Start+Address clock interrupt  
   I2CIE_S_bit.I2CAMIE = 1;                                                     //Enable Interrupt for Address Cycle Interrupt 
   I2CIE2_S_bit.I2CSPIE = 1;                                                    //Enable Stop Interrupt   
   
   I2CTXFIE = 0x0082;                                                           //Enable Tx Page and Threshold Interrupt        
   I2CRXFIE = 0x0082;                                                           //Enable Rx FIFO and Threshold Interrupt    
   I2CTXFST = 0x0000;
   I2CRXFST = 0x0000;
   
   I2CSLA_S = SLAVE_ADDRESS_A2;                                                 //Configure Slave Address 0xA2
   I2CSLA2_S = SLAVE_ADDRESS_A0;                                                //Configure Slave Address 0xA0        
   
   I2CCN_S_bit.ADDR2EN = 1;                                                     //Enable Slave2 
   I2CCN_S_bit.I2CEN = 1;                                                       //Enable I2C module
   
   Rx_Count = 0;                                                                //clear Rx_Count
   Mem_Address = 0;                                                             //clear Mem_Address
   
   UpdateTxBuffer1_2();                                                         //Update TX page

#else
  
  I2CCN_S = 0x0000;                                                            //Clear All I2C modules Settings
   I2CIE_S = 0x0000;
   I2CST_S = 0x0000;
   I2CCN_S = 0x0000;    
    
   MADDR = A2_LOWER_SRAM_OFFSET;                                                //Slave Address 1 (I2CSLA_S = A2), set location
   MADDR_bit.ROLLOVR = 1;                                                       //256 bit rollover
   
   MADDR2 = A0_SRAM_OFFSET;                                                     //Slave Address 2 (I2CSLA2_S = A0), set location
   MADDR2_bit.ROLLOVR = 1;                                                      //256 bit rollover

 
   I2CTXFIE_bit.TXPG_EN = 1;                                                    //Enable Tx Pages
   CUR_SLA_bit.MADDR_EN1 = 1;                                                   //Enable Mem Address detection for Slave Address (0xA2) 
   CUR_SLA_bit.MADDR_EN2 = 1;                                                   //Enable Mem Address detection for Slave Address (0xA0) 
   I2CIE2_S_bit.MADIE = 1;                                                      //Enable Interrupt for Memory Address 
   I2CIE2_S_bit.SADIE = 1;                                                      //Enable Start+Address clock interrupt  
   I2CIE_S_bit.I2CAMIE = 1;                                                     //Enable Interrupt for Address Cycle Interrupt 
   I2CIE2_S_bit.I2CSPIE = 1;                                                    //Enable Stop Interrupt   
   
   I2CTXFIE = 0x0082;                                                           //Enable Tx Page and Threshold Interrupt        
   I2CRXFIE = 0x0082;                                                           //Enable Rx FIFO and Threshold Interrupt    
   I2CTXFST = 0x0000;
   I2CRXFST = 0x0000;
   
   I2CSLA_S = SLAVE_ADDRESS_A2;                                                 //Configure Slave Address 0xA2
   I2CSLA2_S = SLAVE_ADDRESS_A0;                                                //Configure Slave Address 0xA0        
   
   I2CCN_S_bit.ADDR2EN = 1;                                                     //Enable Slave2 
   I2CCN_S_bit.I2CEN = 1;                                                       //Enable I2C module
   
   Rx_Count = 0;                                                                //clear Rx_Count
   Mem_Address = 0;                                                             //clear Mem_Address
   
   UpdateTxBuffer1_2();                                                         //Update TX page
#endif
} 


//-----------------------------------------------------------------------------
// I2C Slave Stop function
//  Sets up received data to be processed
//-----------------------------------------------------------------------------
static void I2C_Slave_Stop(void)
{
#if __SFP28_ER__ == 1
  
  if( (twsiSlaveBuf.devAddress == 0xA2) || (twsiSlaveBuf.devAddress == 0xA0) )  //if slave address is correct
  {
    
    ReadI2CRxBuffer(RX_COUNT_ADD,I2C_RX_BUF_ADD);                               //Read from FIFO
        
    //this limits to 8 bytes being copied to writeBufferEntry
    if( (twsiSlaveBuf.numOfEntries < MEMORY_WRITE_BUFFER_SIZE) && (Rx_Count <= MEMORY_WRITE_BUFFER_SIZE) )
    { 
      for(unsigned char i = 0; i < Rx_Count; i++)                               //for each byte
      {
        twsiSlaveBuf.writeBufferEntry[twsiSlaveBuf.numOfEntries] = I2C_Rx_Buffer[i];  //copy to write buffer
        twsiSlaveBuf.numOfEntries++;                                            //increment count
      }
    }
    
    if(twsiSlaveBuf.numOfEntries)                                               //Anything to be written
    {
       twsiSlaveBuf.bufferStatus = MEMORY_WRITE_BUFFER_WAITING_TO_PROCESS;      //set flag for processing
       I2CCN_S_bit.I2CACK = 1;                                                  //NACK all trafic while processing
       ProcessReceivedI2CData();
       Rx_Count = 0;
    }   
  }
#else
  
  if( (twsiSlaveBuf.devAddress == 0xA2) || (twsiSlaveBuf.devAddress == 0xA0) )  //if slave address is correct
  {
    
    ReadI2CRxBuffer(RX_COUNT_ADD,I2C_RX_BUF_ADD);                               //Read from FIFO
        
    //this limits to 8 bytes being copied to writeBufferEntry
    if( (twsiSlaveBuf.numOfEntries < MEMORY_WRITE_BUFFER_SIZE) && (Rx_Count <= MEMORY_WRITE_BUFFER_SIZE) )
    { 
      for(unsigned char i = 0; i < Rx_Count; i++)                               //for each byte
      {
        twsiSlaveBuf.writeBufferEntry[twsiSlaveBuf.numOfEntries] = I2C_Rx_Buffer[i];  //copy to write buffer
        twsiSlaveBuf.numOfEntries++;                                            //increment count
      }
    }
    
    if(twsiSlaveBuf.numOfEntries)                                               //Anything to be written
    {
       twsiSlaveBuf.bufferStatus = MEMORY_WRITE_BUFFER_WAITING_TO_PROCESS;      //set flag for processing
       I2CCN_S_bit.I2CACK = 1;                                                  //NACK all trafic while processing
       ProcessReceivedI2CData();
       Rx_Count = 0;
    }   
  }
#endif
}


//-----------------------------------------------------------------------------
// I2C Slave Isr function
//   - i2c slave interrupt service routine
//-----------------------------------------------------------------------------
#pragma vector = 2
__interrupt void I2CS_Interrupt(void)
{
#if __SFP28_ER__ == 1
#if __HFR_REQ_DDM_FLAG_VER__==1
  unsigned char curr_addr, check_addr, check_end_addr;
  unsigned int curr_mem_addr;
#endif
  
  //Note: Please do NOT use MAC in I2C interrupt, otherwise it will cause conflict; (In SH interrupt, the code is using MAC1; ) 
  // MACSEL_bit.MACRSEL = 1;                                                       //switch to user MAC      
  if(I2CST2_S_bit.I2CSPI)                                                       //Stop Interrupt flag
  {   
    I2CST2_S_bit.I2CSPI = 0;                                                    //Clear stop interrupt flag
            
    if(I2CCN_S_bit.I2CMODE == 0)                                                //if write mode
    {        
      I2C_Slave_Stop();                                                         //Read Buffer and execute                 
      I2CRXFST_bit.THSH = 0;                                                    //Clear threshold flag as data has been read
    }
    else
    {
//      asm("nop");                        
      
#if __HFR_REQ_DDM_FLAG_VER__==1
      curr_mem_addr = MPNTR;                                                        //Read Memory address including SRAM memory map
      curr_mem_addr &=0x00FF;                                                    
      curr_addr = (unsigned char)curr_mem_addr;
      
      I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_READ_CHIP_STATUS] = twsiSlaveBuf.address;
      I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_READ_CHIP_STATUS+1] = curr_addr;
      //          I2C_Slave_Buffer_A0[QSFP_LOWER_MEMORY_RESERVED5+2] = check_addr;
      
      if ( twsiSlaveBuf.address == (curr_addr-1))
      {
        check_addr = curr_addr -1;
        check_end_addr = check_addr;
      }
      else if (twsiSlaveBuf.address == ((curr_addr-1) + 8))
      {
        check_addr = curr_addr -1;
        check_end_addr = check_addr + 3;
        
      }
      else if (twsiSlaveBuf.address == ((curr_addr-1) + 16))
      {
        check_addr = curr_addr -1;
        //            check_end_addr = check_addr + 3;
        check_end_addr = check_addr + 7;
        
      }          
      else if (twsiSlaveBuf.address == ((curr_addr-1) + 24))
      {
        check_addr = curr_addr -1;
        //            check_end_addr = check_addr + 3;
        check_end_addr = check_addr + 11;
        
      } 
      else if (twsiSlaveBuf.address == ((curr_addr-1) + 32))
      {
        check_addr = curr_addr -1;
        //            check_end_addr = check_addr + 3;
        check_end_addr = check_addr + 15;
        
      } 
      else
      {
         check_addr = curr_addr -1;
        //            check_end_addr = check_addr + 3;
        check_end_addr = check_addr + 15;       
      }
      
      switch (check_addr)
      {
      case LOWER_MEMORY_A2_TEMPERATURE : // LOWER_MEMORY_A2_TEMPERATURE: 0x60 (96)
        if (check_end_addr == check_addr)
        {
          ddm_temperature_flag = 1;
        }
        else
        {
          ddm_temperature_flag = 0;
        }
        break;
      case (LOWER_MEMORY_A2_TEMPERATURE+1) : // LOWER_MEMORY_A2_TEMPERATURE: 0x60 (96)
        ddm_temperature_flag = 0;
        break;
      case LOWER_MEMORY_A2_VCC : // LOWER_MEMORY_A2_TEMPERATURE: 0x60 (96)
        if (check_end_addr == check_addr)
        {
          ddm_vcc_flag = 1;
        }
        else
        {
          ddm_vcc_flag = 0;
        }
        break;
      case (LOWER_MEMORY_A2_VCC+1) : // LOWER_MEMORY_A2_TEMPERATURE: 0x60 (96)
          ddm_vcc_flag = 0;
        break;
      case LOWER_MEMORY_A2_TX_BIAS : // LOWER_MEMORY_A2_TEMPERATURE: 0x60 (96)
        if (check_end_addr == check_addr)
        {
          ddm_tx_bias_flag = 1;
        }
        else
        {
          ddm_tx_bias_flag = 0;
        }
        break;
      case (LOWER_MEMORY_A2_TX_BIAS+1) : // LOWER_MEMORY_A2_TEMPERATURE: 0x60 (96)
          ddm_tx_bias_flag = 0;
        break;
      case LOWER_MEMORY_A2_TX_POWER : // LOWER_MEMORY_A2_TEMPERATURE: 0x60 (96)
        if (check_end_addr == check_addr)
        {
          ddm_tx_power_flag = 1;
        }
        else
        {
          ddm_tx_power_flag = 0;
        }
        break;
      case (LOWER_MEMORY_A2_TX_POWER+1) : // LOWER_MEMORY_A2_TEMPERATURE: 0x60 (96)
          ddm_tx_power_flag = 0;
        break;
      case LOWER_MEMORY_A2_RX_POWER : // LOWER_MEMORY_A2_TEMPERATURE: 0x60 (96)
        if (check_end_addr == check_addr)
        {
          ddm_rx_power_flag = 1;
        }
        else
        {
          ddm_rx_power_flag = 0;
        }
        break;
      case (LOWER_MEMORY_A2_RX_POWER+1) : // LOWER_MEMORY_A2_TEMPERATURE: 0x60 (96)
          ddm_rx_power_flag = 0;
        break;
      default:
          ddm_temperature_flag = 0;
          ddm_vcc_flag = 0;
          ddm_tx_bias_flag = 0;
          ddm_tx_power_flag = 0;
          ddm_rx_power_flag = 0;
        break;
      }
      
#else
      asm("nop");                        

#endif
    }
  }
  
  if(I2CST2_S_bit.SADI)                                                         //Interrupt after Start and Address clock started
  {   
    I2CST2_S_bit.SADI = 0;                                                      //Clear Start and Address clock started flag   
    UpdateAllTxBuffers();                                                       //Assembly function call-Update all TXPAGE with current address and be ready for transmission if requested  
    Rx_Count = 0;                                                               //Set rx_count = 0    
  }
  
  if(I2CST_S_bit.I2CAMI)                                                        //Interrupt after Address matching 
  {  
    I2CST_S_bit.I2CAMI = 0;                                                     //Clear Address matched interrupt flag
    
    switch(CUR_SLA & 0x000F)                                                    //get slave address  
    {
    case 1: twsiSlaveBuf.devAddress = SLAVE_ADDRESS_A2;
    break;
    
    case 2: twsiSlaveBuf.devAddress = SLAVE_ADDRESS_A0;
    break;
    
    case 4: twsiSlaveBuf.devAddress = SLAVE_ADDRESS_B2;
    break;
    
    case 8: twsiSlaveBuf.devAddress = SLAVE_ADDRESS_B0;
    break;
    default:
      break;
    }
    Rx_Count = 0;                                                               //Set rx_count = 0
  } 
  else if(I2CST2_S_bit.MADI)                                                    //memory address detected
  {   
    I2CST2_S_bit.MADI = 0;                                                      //Clear Memory Address interrupt flag 
    MPNTR = 0;                                                                  //Dummy write, this will update current address update
    Mem_Address = MPNTR;                                                        //Read Memory address including SRAM memory map
    Mem_Address &=0x00FF;                                                       //Clear page info 
    twsiSlaveBuf.address = (unsigned char)Mem_Address;                          //record memory address to write buffer
    twsiSlaveBuf.numOfEntries = 0;                                              //clear rx number
    Rx_Count = 0;                                                               //Set rx_count = 0
    ActiveSlave = CUR_SLA & 0x000F;                                             //Findout Active Slave Address
    if(ActiveSlave == 1)
    {  
      CUR_SLA = 0xF1;
      UpdateTxBuffer();                                                        //Update TX Page for A2 Slave Address  
    }
    else if(ActiveSlave == 2)
    {
      CUR_SLA = 0xF2;          
      UpdateTxBuffer();                                                        //Update TX Page for A0 Slave Address
    }           
    else if(ActiveSlave == 4)
    {
      CUR_SLA = 0xF4;          
      UpdateTxBuffer();                                                        //Update TX Page for A0 Slave Address
    }           
    else if(ActiveSlave == 8)
    {
      CUR_SLA = 0xF8;                    
      UpdateTxBuffer();                                                        //Update TX Page for A0 Slave Address
    }           
  }
  else if(I2CRXFST_bit.THSH)                                                    //receive FIFO has received 4 bytes
  {   
    I2CRXFST_bit.THSH = 0;                                                      //Clear Threshold flag 
    ReadI2CRxBuffer(RX_COUNT_ADD,I2C_RX_BUF_ADD);                               //Read data from receive buffer    
  }    
  else if(I2CTXFST_bit.THSH)                                                    //TX Page Threshold Interrupt, 4 bytes remaining
  {
    I2CTXFST_bit.THSH = 0;                                                      //clear flag
    ActiveSlave = CUR_SLA & 0x000F;                                             //Findout Active Slave Address
    
    if(ActiveSlave == 1)
    {  
      CUR_SLA = 0xF1;
      UpdateTxBuffer();                                                        //Update TX Page for A2 Slave Address  
    }
    else if(ActiveSlave == 2)
    {
      CUR_SLA = 0xF2;          
      UpdateTxBuffer();                                                        //Update TX Page for A0 Slave Address
    }           
    else if(ActiveSlave == 4)
    {
      CUR_SLA = 0xF4;          
      UpdateTxBuffer();                                                        //Update TX Page for A0 Slave Address
    }           
    else if(ActiveSlave == 8)
    {
      CUR_SLA = 0xF8;                    
      UpdateTxBuffer();                                                        //Update TX Page for A0 Slave Address
    }
    twsiSlaveBuf.address += 8;                                                  //add 8 to the address
  }   
  
  //MACSEL_bit.MACRSEL = 0;                                                       //change back to normal MAC
#else

  //Note: Please do NOT use MAC in I2C interrupt, otherwise it will cause conflict; (In SH interrupt, the code is using MAC1; ) 
 // MACSEL_bit.MACRSEL = 1;                                                       //switch to user MAC      
   
  if(I2CST2_S_bit.I2CSPI)                                                       //Stop Interrupt flag
  {   
    I2CST2_S_bit.I2CSPI = 0;                                                    //Clear stop interrupt flag
            
    if(I2CCN_S_bit.I2CMODE == 0)                                                //if write mode
    {        
      I2C_Slave_Stop();                                                         //Read Buffer and execute                 
      I2CRXFST_bit.THSH = 0;                                                    //Clear threshold flag as data has been read
    }
    else
    {
      asm("nop");                        
    }
  }
  
  if(I2CST2_S_bit.SADI)                                                         //Interrupt after Start and Address clock started
  {   
    I2CST2_S_bit.SADI = 0;                                                      //Clear Start and Address clock started flag   
    UpdateAllTxBuffers();                                                       //Assembly function call-Update all TXPAGE with current address and be ready for transmission if requested  
    Rx_Count = 0;                                                               //Set rx_count = 0    
  }
  
  if(I2CST_S_bit.I2CAMI)                                                        //Interrupt after Address matching 
  {  
    I2CST_S_bit.I2CAMI = 0;                                                     //Clear Address matched interrupt flag

    switch(CUR_SLA & 0x000F)                                                    //get slave address  
    {
        case 1: twsiSlaveBuf.devAddress = SLAVE_ADDRESS_A2;
                break;
                
        case 2: twsiSlaveBuf.devAddress = SLAVE_ADDRESS_A0;
                break;
                
        case 4: twsiSlaveBuf.devAddress = SLAVE_ADDRESS_B2;
                break;
                
        case 8: twsiSlaveBuf.devAddress = SLAVE_ADDRESS_B0;
                break;
        default:
                break;
    }
    Rx_Count = 0;                                                               //Set rx_count = 0
  } 
  else if(I2CST2_S_bit.MADI)                                                    //memory address detected
  {   
    I2CST2_S_bit.MADI = 0;                                                      //Clear Memory Address interrupt flag 
    MPNTR = 0;                                                                  //Dummy write, this will update current address update
    Mem_Address = MPNTR;                                                        //Read Memory address including SRAM memory map
    Mem_Address &=0x00FF;                                                       //Clear page info 
    twsiSlaveBuf.address = (unsigned char)Mem_Address;                          //record memory address to write buffer
    twsiSlaveBuf.numOfEntries = 0;                                              //clear rx number
    Rx_Count = 0;                                                               //Set rx_count = 0
    ActiveSlave = CUR_SLA & 0x000F;                                             //Findout Active Slave Address
    if(ActiveSlave == 1)
    {  
       CUR_SLA = 0xF1;
       UpdateTxBuffer();                                                        //Update TX Page for A2 Slave Address  
    }
    else if(ActiveSlave == 2)
    {
       CUR_SLA = 0xF2;          
       UpdateTxBuffer();                                                        //Update TX Page for A0 Slave Address
    }           
    else if(ActiveSlave == 4)
    {
       CUR_SLA = 0xF4;          
       UpdateTxBuffer();                                                        //Update TX Page for A0 Slave Address
    }           
    else if(ActiveSlave == 8)
    {
       CUR_SLA = 0xF8;                    
       UpdateTxBuffer();                                                        //Update TX Page for A0 Slave Address
    }           
  }
  else if(I2CRXFST_bit.THSH)                                                    //receive FIFO has received 4 bytes
  {   
    I2CRXFST_bit.THSH = 0;                                                      //Clear Threshold flag 
    ReadI2CRxBuffer(RX_COUNT_ADD,I2C_RX_BUF_ADD);                               //Read data from receive buffer    
  }    
  else if(I2CTXFST_bit.THSH)                                                    //TX Page Threshold Interrupt, 4 bytes remaining
  {
    I2CTXFST_bit.THSH = 0;                                                      //clear flag
    ActiveSlave = CUR_SLA & 0x000F;                                             //Findout Active Slave Address
  
    if(ActiveSlave == 1)
    {  
       CUR_SLA = 0xF1;
       UpdateTxBuffer();                                                        //Update TX Page for A2 Slave Address  
    }
    else if(ActiveSlave == 2)
    {
       CUR_SLA = 0xF2;          
       UpdateTxBuffer();                                                        //Update TX Page for A0 Slave Address
    }           
    else if(ActiveSlave == 4)
    {
       CUR_SLA = 0xF4;          
       UpdateTxBuffer();                                                        //Update TX Page for A0 Slave Address
    }           
    else if(ActiveSlave == 8)
    {
       CUR_SLA = 0xF8;                    
       UpdateTxBuffer();                                                        //Update TX Page for A0 Slave Address
    }
    twsiSlaveBuf.address += 8;                                                  //add 8 to the address
  }   

  //MACSEL_bit.MACRSEL = 0;                                                       //change back to normal MAC
#endif
}


//-----------------------------------------------------------------------------
// end of file
//-----------------------------------------------------------------------------



//End


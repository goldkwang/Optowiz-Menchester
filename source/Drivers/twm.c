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

#include <intrinsics.h>
#include <iods4835.h>
#include <stdio.h>
#include <string.h>
#include "twm.h"

/*******************************************************************************
 * Function: TWM_Init
 *
 * Initialize Initialize 3-wire master
 *
 * Input:   unsigned int Clock_Period - clock period code from clock period
 *                                      settings in twm.h
 *          unsigned char CS_Disable  - if 0 CS will be driven else
 *                                      if 1 CS will be ignored
 *
 * Output:    None
 *
 * Example:   
 *
 * Remarks:   No validation performed on any parameters
 *
 ******************************************************************************/ 
void TWM_Init(unsigned int Clock_Period, unsigned char CS_Disable)
{
//    PD1_bit.PD10 = 1;                       // SDA out/in
    IEN1_bit.IEN10 = 1;   //SDA set as input??
    PD1_bit.PD11 = 1;                       // CK output
    PD1_bit.PD12 = 1;                       // CS output
    
#ifdef PASS_2_CS_WORKAROUND
    PD0_bit.PD03 = 1;               // use as workaround for CS problem 
    PO0_bit.PO03 = 0;
#endif
    
    
    TWR_bit.CLK_EXT = Clock_Period;         // clock period
    if (CS_Disable == 0)
    {
        PD1_bit.PD12 = 1;                   // set CS as output 
        TWR_bit.DIS_CS = 0;                 // enable CS 
    }
    else
    {
        TWR_bit.DIS_CS = 1;                 // disable CS
      
    }
    TWR_bit.TWI = 0;                        // clear any status
    TWR_bit.TWEN = 1;                       // enable 3-wire interface 
}


/*******************************************************************************
 * Function: TWM_WriteNBytes
 *
 * Write 1..8 bytes to 3-wire slave at specified register address
 *
 * Input:     unsigned char reg_addr - register address for write
 *            const unsigned char *data_ptr - pointer to data array to write
 *            unsigned char num_bytes - number of bytes to write, max 8
 *
 * Output:    return_code - TWM_STATUS_NO_ERRORS
 *                          TWM_STATUS_WRITE_TIMEOUT
 *
 * Example:  
 *
 * Remarks:   No validation performed on any parameters
 *
 ******************************************************************************/
unsigned char TWM_WriteNBytes(unsigned char reg_addr,
                              const unsigned char *data_ptr,
                              unsigned char num_bytes)
{
    unsigned char i;
    unsigned char return_code = TWM_STATUS_NO_ERRORS;
    unsigned int timeout_cnt = TWM_RX_TX_TIMEOUT_COUNT;
    
    if (num_bytes > 8)                        // clamp bytes written to max 8
    {
        num_bytes = 8; 
    }
    if (num_bytes == 0)                       // clamp bytes written min 1
    {
        num_bytes = 1; 
    }

#ifdef PASS_2_CS_WORKAROUND           
    PO0_bit.PO03 = 1;                          // use as workaround for CS
#endif
    TWR_bit.TWI = 0;                          // clear any status    
    TWR_bit.MADR_3W = 0;                      // FIFO pointer to 0
    TWR_bit.NB_3W = num_bytes - 1;                // write len
    for (i = 0; i < num_bytes; i++)           // copy data to FIFO
    {
        DADDR = data_ptr[i];       
    }
    TWR_bit.AD_SEL = 1;                       // DADDR set to register address
    DADDR = reg_addr << 1;                    // shift L addr, set as write operation      

    while (!TWR_bit.TWI)                    // wait for complete or timeout
    {
      if (--timeout_cnt == 0)
      {
          return_code = TWM_STATUS_WRITE_TIMEOUT;
          break;
      }        
    }
#ifdef PASS_2_CS_WORKAROUND           
    PO0_bit.PO03 = 0;                          // use as workaround for CS
#endif    
    return (return_code);

}


/*******************************************************************************
 * Function: TWM_ReadNBytes
 *
 * Read 1..8 bytes from 3-wire slave from specified registers
 *
 * Input:     unsigned char reg_addr - register address for read
 *            unsigned char *data_ptr - pointer to data array for read data
 *            unsigned char num_bytes - number of bytes to read, max 8
 *
 * Output:    return_code - TWM_STATUS_NO_ERRORS
 *                          TWM_STATUS_READ_TIMEOUT
 *
 * Example:   
 *
 * Remarks:   No validation performed on any parameters
 *
 ******************************************************************************/
unsigned char TWM_ReadNBytes(unsigned char reg_addr, unsigned char *data_ptr,
                             unsigned char num_bytes)
{
    unsigned char i;
    unsigned char return_code = TWM_STATUS_NO_ERRORS;
    unsigned int timeout_cnt = TWM_RX_TX_TIMEOUT_COUNT;
 
    if (num_bytes > 8)                      // clamp bytes written to max 8
    {
        num_bytes = 8; 
    }
    if (num_bytes == 0)                     // clamp bytes written min 1
    {
        num_bytes = 1; 
    }
#ifdef PASS_2_CS_WORKAROUND           
    PO0_bit.PO03 = 1;                          // use as workaround for CS
#endif    
    TWR_bit.TWI = 0;                        // clear any status    
    TWR_bit.MADR_3W = 0;                    // FIFO pointer to 0
    TWR_bit.NB_3W = num_bytes - 1;          // read len
    TWR_bit.AD_SEL = 1;                     // DADDR set to register address
    DADDR = (reg_addr << 1) | 0x01;         // shift L addr, set as read operation
    
    while (!TWR_bit.TWI)                    // wait for complete or timeout
    {
      if (--timeout_cnt == 0)
      {
          return_code = TWM_STATUS_READ_TIMEOUT;
          break;
      }        
    }  
    
    
    TWR_bit.AD_SEL = 0;                     // DADDR set to read FIFO
    TWR_bit.MADR_3W = 0;                    // FIFO pointer to 0

    for (i = 0; i < num_bytes; i++)
    {
      data_ptr[i] = DADDR;      
    }
#ifdef PASS_2_CS_WORKAROUND           
    PO0_bit.PO03 = 0;                          // use as workaround for CS
#endif
    return (return_code);

}


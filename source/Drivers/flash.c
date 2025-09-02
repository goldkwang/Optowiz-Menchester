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


#include <intrinsics.h>
#include <iods4835.h>

#include "flash.h"
#include "includes.h"

/*******************************************************************************
 * Function: ReadFromFlash
 *
 * This function reads data from flash and write into SRAM.
 *
 * Input:     None
 *
 * Output:    None
 *
 * Example:   To Recall (read) block of data from flash into sram...
 *                  ReadFromFlash();
 *********
 * Notes:
 *********
 * 1.
 * During block read from flash global interrupt is disabled.
 *
 * 2.
 * Last parmeter into read_block_from_flash() function is no of WORDS to be
 * read from flash.
 *
 ******************************************************************************/

void ReadFromFlash(unsigned int SourceAddress, unsigned int DesAddress, unsigned int length)
{
     //Read data from flash and store into sram
     //Assembly function call
     read_block_from_flash(SourceAddress, DesAddress, length>>1);
}


unsigned int Read_Word_from_Flash(unsigned int SourceAddress)
{
    unsigned int Word;
    Word = read_word_from_flash(SourceAddress);
    return Word;
}

/*******************************************************************************
 * Function: StoreConfigInFlash
 *
 * This function reads data from flash and write into SRAM.
 *
 * Input:     None
 *
 * Output:    None
 *
 * Example:   To Store block of data from sram into flash.
 *                  StoreConfigInFlash();
 *********
 * Notes:
 *********
 * 1.
 * During block read from flash global interrupt is disabled.
 *
 * 2.
 * Last parmeter into write_block_to_flash() function is no of WORDS to be
 * written into flash. This should be less than page size (256 Words)
 *
 * 3.
 * Flash erase timing          40msec (MAX.)
 * Flash per word write time   40usec (MAX.)
 * To meet the above timing on power dowm, Power Supply should have large value
 *
 * 4.
 * Flash Endurance is 20,000 (Min.) WRITE CYCLES.
 *
 ******************************************************************************/
void StoreConfigInFlash(unsigned int flash_address, unsigned int sram_address, unsigned int length)
{
     unsigned int uiFlashFail;

     //Disable Global Interrupt
     __disable_interrupt();

     //Flash page erase can take max. of 40msec and 
     //if DVDD level (say power supply start falling) is lower than 
     //Supply Monitor Level, don't write into flash.
  //   if((!SVMI))
     {
         //Flash Page Erase
         //Assembly Function Calls
         uiFlashFail = clear_block_in_flash(flash_address);

        //Write Block of data from SRAM to Flash
        //Assembly call
        if(!uiFlashFail)  //Write new Configuration in flash is no flash failure
        {
            uiFlashFail = write_block_to_flash(flash_address, sram_address, length>>1);
        }
     }     
     
     if(uiFlashFail != 0)
     {
        //not able to attempt write to flash
        uiFlashFail |= 0x80;   //TOSANJAY : System Error
     }

     //Enable Global Interrupt
     __enable_interrupt();
}

void CopySramToFlash(unsigned int sram_add, unsigned int flash_add, unsigned int length)
{
     unsigned int fail = 0x000;
     unsigned char interrupt;
     
     interrupt = IC;                                                      //save current settings
     __disable_interrupt();                                               //Disable Global Interrupt

     
     if((!SVM_bit.SVMI))                                                  //do not attempt delete if VCC is below threshold 
     {                  
        fail = clear_block_in_flash(flash_add);                           //Flash Page Erase, assembly routine.  Can take up to 40ms to complete

        if(!fail)                                                         //if erase executed properly
        {
          if (length > 128)
          {
            write_block_to_flash(flash_add, sram_add, 64);           //assembly call to write block of data to flash    
            write_block_to_flash(flash_add+128, sram_add+128, 64);           //assembly call to write block of data to flash    
          }
          else
          {
            write_block_to_flash(flash_add, sram_add, length>>1);           //assembly call to write block of data to flash    
          }
        }
     }
     
     IC = interrupt;                                                      //re-store interrupts

     //Enable Global Interrupt
     __enable_interrupt();     
     
}

//-----------------------------------------------------------------------------
// FlashReadBlock
//   - read a block of words from flash starting at FlashAddr and storing to RAM 
//    starting at uiramAddr
//-----------------------------------------------------------------------------
void FlashReadBlock(unsigned int flash_add, unsigned int sram_add, unsigned int length)
{   
  
  read_block_from_flash(flash_add, sram_add, (length>>1) );         //Read data from flash and store into sram, Assembly function call 
}

//End

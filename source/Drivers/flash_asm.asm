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


        NAME flash_asm

        RSEG CSTACK:DATA:SORT:NOROOT(1)

        PUBLIC read_block_from_flash
        PUBLIC write_block_to_flash
        PUBLIC Device_Reset
        PUBLIC clear_block_in_flash
        PUBLIC Info_Read


UROM_flashWrite     EQU     108E6h    //1097Ah 
UROM_copyBuffer     EQU     109ACh    //10A40h      
UROM_flashErasePage EQU     1092Ch 
UROM_InfoRead       EQU     10A1Ch    //
SOFT_RESET          EQU     1118Ah
READ_MEM            EQU     111AAh    //110B6h     

        RSEG CODE:CODE:REORDER:NOROOT(1)

////////////////////////////////
//this deletes one page of flash
////////////////////////////////

clear_block_in_flash:
  push PSF                //push registers to stack that are destroyed
  push LC[0]
  push LC[1]
  push GR
  push AP
  push APC
  push DPC
  push A[10]
  push A[11]  

  move DPC, #01Ch         //set all pointers to word mode
  move LC[0], #128        //set word count to 128
  move AP, #0             //set A[0] as active -> flash address
  sr                      //shift right to give word address
  call UROM_flashErasePage  //erase page containing A0  
  
  move Acc, #0              //clear A0
  move Acc.0, C             //carry bit has error status

clear_exit:
  POP A[11]
  pop A[10]
  pop DPC                 //pop destroyed registers off stack
  pop APC                 
  pop AP
  pop GR
  pop LC[1]
  pop LC[0]
  pop PSF
  ret                     //returns A[0]

///////////////////////////////////////////////////////
//Reset the device
///////////////////////////////////////////////////////
        RSEG CODE:CODE:REORDER:NOROOT(1)

Device_Reset:
  CALL SOFT_RESET
  RET


        RSEG CODE:CODE:REORDER:NOROOT(1)
////////////////////////////////////////////////
//this writes one word of data from sram to flash
//assumes that the flash has already been erased
/////////////////////////////////////////////////

write_block_to_flash:
#define SVM M1[9]
#define SVMI SVM.3

  push PSF                //push registers to stack that are destroyed
  push LC[0]
  push LC[1]
  push GR
  push AP
  push APC
  push DPC
  push A[10]
  push A[11]  

  move DPC, #01Ch         //set all pointers to word mode
  move LC[0], A[2]        //move byte count to LC[0]
  move APC, #0            //no increment
  move AP, #1             //set A[1] as active
  sr                      //shift right to give word address
  move DP[0], A[1]        //move sram address to DP
  move AP, #0             //set A[0] as active
  sr                      //shift right to give word address
  
write_loop:
  move A[1], @DP[0]++     //get data from sram address
  move C, SVMI            //move SVM interrupt to carry
  jump C, write_exit
  call UROM_flashWrite 
  jump C, write_exit      //Carry is set on error
  add #1                  //should add 1 to A[0]
  djnz LC[0], write_loop
  
  move C, #0              //set carry to 0 to indicate passing
  
write_exit:
  move AP, #0               //set A0 as active
  move ACC, #0              //clear A0
  move ACC.0, C             //set to C for error status
  
  POP A[11]
  pop A[10]  
  pop DPC                   //pop destroyed registes off stack
  pop APC                 
  pop AP
  pop GR
  pop LC[1]
  pop LC[0]
  pop PSF
  ret

    RSEG CODE:CODE:REORDER:NOROOT(1)
Info_Read:
  MOVE A[1], A[0]               //set info address
  CALL UROM_InfoRead
  ret
  

///////////////////////////////////////////////////////
//reads a block of memory from flash to a sram variable
///////////////////////////////////////////////////////
        RSEG CODE:CODE:REORDER:NOROOT(1)

//Important note:
//This function is implement to allow interrupt generation while reading
//flash data from UROM
read_block_from_flash:

#if 0
  //push registers onto stack that will be destroyed
  PUSH    DPC                
  PUSH    DPC     
  MOVE    @--DP[1], DP[0] 
  MOVE    @--DP[1], BP 
  MOVE    @--DP[1], OFFS 
  MOVE    @--DP[1], LC[0] 
  MOVE    @--DP[1], APC 
  MOVE    @--DP[1], AP 
  MOVE    @--DP[1], PSF 
  POP     @--DP[1]     
  
  
  MOVE    DPC,  #01Ch         //set all pointers to word mode
  MOVE    APC,  #0            //no increment
  MOVE    AP,   #1             //set to A1, sram address
  SR                      //shift right to give word mode address
  MOVE    BP,   A[1]           //MOVE sram address to BP
  MOVE    OFFS, #0           //set offset to 0
  
  MOVE    AP,   #0             //set to A0, flash address
  SR
  ADD     #08000h             //add to address flash
  MOVE    DP[0],A[0]        //MOVE flash address to DP0
  
  MOVE    LC[0],A[2]        //MOVE number of words to loop count
  
  CALL    UROM_copyBuffer
  
  MOVE    DP[1],  DP[1]                  
  MOVE    DPC,    @DP[1]++   

  MOVE    DP[1],  DP[1]                  
  MOVE    PSF,    @DP[1]++                  
  MOVE    AP,     @DP[1]++    
  MOVE    APC,    @DP[1]++    
  MOVE    LC[0],  @DP[1]++          

  MOVE    DP[1],  DP[1]                  
  MOVE    OFFS,   @DP[1]++    

  MOVE    DP[1],  DP[1]         
  MOVE    BP,     @DP[1]++    

  MOVE    DP[1],  DP[1]         
  MOVE    DP[0],  @DP[1]++    

  POP     DPC
  RET 
 

#endif





#if 1
  push DPC                //push registers onto stack that will be destroyed
  push BP
  push OFFS
  push DP[0]
  push LC[0]
  push APC
  push AP
  push PSF
  
  move DPC, #01Ch         //set all pointers to word mode
  move APC, #0            //no increment
  move AP, #1             //set to A1, sram address
  sr                      //shift right to give word mode address
  move BP, A[1]           //move sram address to BP
  move OFFS, #0           //set offset to 0
  
  move AP, #0             //set to A0, flash address
  sr
  add #08000h             //add to address flash
  move DP[0], A[0]        //move flash address to DP0
  
  move LC[0], A[2]        //move number of words to loop count
  
  call UROM_copyBuffer
  
  pop PSF                 //pop registers off stack
  pop AP
  pop APC
  pop LC[0]
  pop DP[0]
  pop OFFS
  pop BP
  pop DPC
  ret
#endif 
  

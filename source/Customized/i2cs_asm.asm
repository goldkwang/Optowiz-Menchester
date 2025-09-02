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


        NAME i2cs_asm

        RSEG CSTACK:DATA:SORT:NOROOT(1)

        PUBLIC UpdateTxBuffer
        PUBLIC UpdateTxBuffer1_2
        PUBLIC UpdateAllTxBuffers
        PUBLIC ReadI2CRxBuffer

//Design: Update these SFR using using desing SFRs names
// Please update M2[x] also according to the name you are using
#define RPNTR M2[8]
#define SLA   M2[21]

//Function prototype in 'C' void UpdateTxBuffer(void)
        RSEG CODE:CODE:REORDER:NOROOT(1)
UpdateTxBuffer:
    
    PUSH    DPC                           //Back up on HW Stack
    PUSH    DP[0]

    MOVE DPC, #01Ch                       //set all pointers to word mode
    
    MOVE RPNTR, #0000h                    //Get Current Mem Address in RPNTR

    MOVE DP[0], RPNTR               
    MOVE M2[0], @DP[0]                    //Update I2CBUF_S from SRAM data (in word) and increment the SRAM address

    MOVE DP[0], RPNTR                     
    MOVE M2[0], @DP[0]                   

    MOVE DP[0], RPNTR
    MOVE M2[0], @DP[0]

    MOVE DP[0], RPNTR
    MOVE M2[0], @DP[0]
  
    POP  DP[0]                            //Restore register values
    POP  DPC
    RET                     //returns A[0]

//Function prototype in 'C' void UpdateTxBuffer1_2(void)        
        RSEG CODE:CODE:REORDER:NOROOT(1)
UpdateTxBuffer1_2:
//This function updates page data of two slave addresses (I2CSLA_S and I2CSLA2_S)

    PUSH    DPC                           //Back up on HW Stack
    PUSH    DP[0]

    MOVE DPC, #01Ch                       //set all pointers to word mode

    MOVE SLA, #00F1h                       //Select Slave Address - 1 Slave Address A2h  (I2CSLA_S)
    
    MOVE RPNTR, #0000h                    //Get Current Mem Address in RPNTR
  
    MOVE DP[0], RPNTR               
    MOVE M2[0], @DP[0]                    //Update I2CBUF_S from SRAM data (in word) and increment the SRAM address

    MOVE DP[0], RPNTR                     
    MOVE M2[0], @DP[0]                   

    MOVE DP[0], RPNTR
    MOVE M2[0], @DP[0]

    MOVE DP[0], RPNTR
    MOVE M2[0], @DP[0]
    
    MOVE SLA, #00F2h                      //Select Slave Address - 2 Slave Address A2h  (I2CSLA2_S)
    
    MOVE RPNTR, #0000h                    //Get Current Mem Address in RPNTR
  
    MOVE DP[0], RPNTR               
    MOVE M2[0], @DP[0]                    //Update I2CBUF_S from SRAM data (in word) and increment the SRAM address

    MOVE DP[0], RPNTR                     
    MOVE M2[0], @DP[0]                   

    MOVE DP[0], RPNTR
    MOVE M2[0], @DP[0]

    MOVE DP[0], RPNTR
    MOVE M2[0], @DP[0]
    
  
    POP  DP[0]                            //Restore register values
    POP  DPC
    RET                     //returns A[0]

//Function prototype in 'C' void UpdateAllTxBuffers(void)        
        RSEG CODE:CODE:REORDER:NOROOT(1)
UpdateAllTxBuffers:
//This function updates page data of all slave addresses

    PUSH    DPC
    PUSH    DP[0]
  
    //Important Note: 
    //Pages are updated in the word mode. (less instructions)
    MOVE DPC, #01Ch         
    
    MOVE SLA, #00F1h                      //Select Slave Address - 1 (I2CSLA_S)
    MOVE RPNTR, #0000h                    //Get Current Mem Address in RPNTR  
    
    MOVE DP[0], RPNTR               
    MOVE M2[0], @DP[0]                    //Update I2CBUF_S from SRAM data (in word) and increment the SRAM address

    MOVE DP[0], RPNTR                     
    MOVE M2[0], @DP[0]                   

    MOVE DP[0], RPNTR
    MOVE M2[0], @DP[0]

    MOVE DP[0], RPNTR
    MOVE M2[0], @DP[0]
    
    MOVE SLA, #00F2h                      //Select Slave Address - 2 (I2CSLA2_S)  
    MOVE RPNTR, #0000h                    //Get Current Mem Address in RPNTR
  
    MOVE DP[0], RPNTR               
    MOVE M2[0], @DP[0]                    //Update I2CBUF_S from SRAM data (in word) and increment the SRAM address

    MOVE DP[0], RPNTR                     
    MOVE M2[0], @DP[0]                   

    MOVE DP[0], RPNTR
    MOVE M2[0], @DP[0]

    MOVE DP[0], RPNTR
    MOVE M2[0], @DP[0]
    
    MOVE SLA, #00F4h                      ////Select Slave Address - 3 (I2CSLA3_S)  
    
    MOVE RPNTR, #0000h                    //Get Current Mem Address in RPNTR
 
    MOVE DP[0], RPNTR               
    MOVE M2[0], @DP[0]                    //Update I2CBUF_S from SRAM data (in word) and increment the SRAM address

    MOVE DP[0], RPNTR                     
    MOVE M2[0], @DP[0]                   

    MOVE DP[0], RPNTR
    MOVE M2[0], @DP[0]

    MOVE DP[0], RPNTR
    MOVE M2[0], @DP[0]
    
    MOVE SLA, #00F8h                      //Select Slave Address - 4 (I2CSLA4_S)  
    MOVE RPNTR, #0000h                    //Get Current Mem Address in RPNTR
    
    MOVE DP[0], RPNTR               
    MOVE M2[0], @DP[0]                    //Update I2CBUF_S from SRAM data (in word) and increment the SRAM address

    MOVE DP[0], RPNTR                     
    MOVE M2[0], @DP[0]                   

    MOVE DP[0], RPNTR
    MOVE M2[0], @DP[0]

    MOVE DP[0], RPNTR
    MOVE M2[0], @DP[0]
    
    POP  DP[0]  
    POP  DPC
    
    RET                     //returns A[0]


//Function prototype in 'C' void ReadI2CRxBuffer(unsigned int AddrRx_Cnt, AddrI2CBuffer)
      RSEG CODE:CODE:REORDER:NOROOT(1)        
ReadI2CRxBuffer:
    PUSH DPC
    PUSH DP[0]
    PUSH PSF  
    PUSH OFFS
    PUSH BP
    PUSH AP
        
    MOVE DPC,    #0000h           //rx_count address in byte mode      
   
    MOVE DP[0],  A[0]             //rx_count address in DP[0]

    MOVE DPC,    #001Ch         

    MOVE A[0],   @DP[0]           //Read rx_count SRAM location and copy data into A[0]
  

    MOVE DPC,   #0000h            //Set DPC in byte mode

    MOVE    M2[5].0, #0x0         //Clear FIFO EMPTY Bit, if already set. I2CRXFST_bit.EMPTY = 0; 
    
    MOVE BP,    A[1]              //Load Temporary I2C Buffer in BP
    
    MOVE AP, #0
READ_BUFFER:
    MOVE    C,    M2[5].0       //M2[5].0 ->Load FIFO Empty Bit read to Carry
    SJUMP   C,    UPDATE_REGS   //If Set, FIFO read completed
    MOVE    OFFS,  A[0]          //Load OFFS from A[0]
    MOVE    @BP[OFFS], M2[0]     //Read a byte from FIFO
    ADD     #1                   //Increment rx_count as post increment is not allowed with BP[OFFS] when used as destination
    SJUMP   READ_BUFFER
UPDATE_REGS:
    MOVE    DPC,    #001Ch       //Word mode
    MOVE    @DP[0], A[0]         //Update rx_count

    POP    AP
    POP    BP
    POP    OFFS
    POP    PSF
    POP    DP[0]
    POP    DPC
    RET
    
    

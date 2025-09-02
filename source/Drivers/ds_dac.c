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
// Includes
//-----------------------------------------------------------------------------
#include <intrinsics.h>
#include <iods4835.h>
#include "ds_dac.h"

////////////////////////////////////////////////////////////////////////////////
// DSDAC Channel configuration
// Full scale is configured for normal mode operation
////////////////////////////////////////////////////////////////////////////////
void DS_DAC_Init(unsigned int Channel, unsigned int Config, unsigned int FullScale)
{
     unsigned int local;                                                        //Work around to write on the DPCN 
     if( Channel < 16 )
     {        
        local = DPCN;
        local = local & ~0x003F;
        local |= Channel;
        local |= (DS_CONFIG<<4);
        DPCN = local;
        DPDATA = Config;                                                        //Config DS DAC
        
        if( (Config & 0x0040) == 0)                                             //If DS DAC is configured for the normal mode
        {
            local = DPCN;
            local = local & ~0x003F;
            local |= Channel;
            local |= (DS_FULL_SCALE_CNFG<<4);
            DPCN = local;
            DPDATA = FullScale;                                                 //Write DS DAC Full scale register
        }       
    }
}

////////////////////////////////////////////////////////////////////////////////
// Write DSDAC Duty Register
////////////////////////////////////////////////////////////////////////////////
void DS_DAC_Duty(unsigned int Channel, unsigned int Duty)
{
     unsigned int local;                                                        //Work around to write on the DPCN   
     if( Channel < 16 )
     {
        local = DPCN;
        local = local & ~0x003F;
        local |= Channel;
        local |= (DS_DUTY<<4);
        DPCN = local;
        DPDATA = Duty;                                                             //Write Duty
     }
}

////////////////////////////////////////////////////////////////////////////////
// Read DSDAC Duty Register
////////////////////////////////////////////////////////////////////////////////
unsigned int DS_DAC_Read_Duty(unsigned int Channel)
{
     unsigned int local;                                                        //Work around to write on the DPCN   
     unsigned int Duty = 0;
     
     if( Channel < 16 )
     {
        local = DPCN;
        local = local & ~0x003F;
        local |= Channel;
        local |= (DS_DUTY<<4);
        DPCN = local;
        Duty = DPDATA;                                                           //Read Duty
     }
     
     return Duty;
}


////////////////////////////////////////////////////////////////////////////////
// Slowing Ramp the DC_DC Buck output to target.
////////////////////////////////////////////////////////////////////////////////
void RampDS_DAC(unsigned int Channel,unsigned int Target)
{
    unsigned int delay, Step;

    //Slowing change DS-DAC to target
    for(Step = DS_DAC_Read_Duty(Channel); Step < Target; Step = Step + DSDAC_RAMP_STEP)
    {
        DS_DAC_Duty(Channel, Step);                                             //Start with initial value
        
        for(delay = 0; delay < 2000; delay++)                                   //Delay
        {
             //Reset Watchdog Timer
             WDCN_bit.RWT = 1; 
        }
    }
    //Set the final output
    DS_DAC_Duty(Channel, Target);   
}





////////////////////////////////////////////////////////////////////////////////
// DS DAC Configuration
////////////////////////////////////////////////////////////////////////////////
void DS_DAC_Config(unsigned int Channel, unsigned int RegSel, unsigned int Data)
{
     unsigned int local;                                                        //Work around to write on the DPCN   
     
     if( Channel < 16 )
     {
        local = DPCN;
        local = local & ~0x003F;
        local |= Channel;
        local |= (RegSel<<4);
        DPCN = local;
        DPDATA = Data;                                                             //Write Duty
     }
}

//End
////////////////////////////////////////////////////////////////////////////////

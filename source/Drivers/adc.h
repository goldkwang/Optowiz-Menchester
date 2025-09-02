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

#ifndef _ADC_H_
#define _ADC_H_



////////////////////////////////////////////////////////////////////////////////
//ADC channel PRIORITY in the sequence
////////////////////////////////////////////////////////////////////////////////
#define PRIORITY_1                 1
#define PRIORITY_2                 2
#define PRIORITY_3                 3

////////////////////////////////////////////////////////////////////////////////
//ADC Acquistion Extension
////////////////////////////////////////////////////////////////////////////////
#define NO_ACQ_EXT                 0<<2
#define ACQ_EXT_0_5us              1<<2
#define ACQ_EXT_1_0us              2<<2
#define ACQ_EXT_2_0us              3<<2

////////////////////////////////////////////////////////////////////////////////
//ADC Averaging
////////////////////////////////////////////////////////////////////////////////
#define ADC_AVG_001SMP             0<<4
#define ADC_AVG_002SMP             1<<4
#define ADC_AVG_004SMP             2<<4
#define ADC_AVG_008SMP             3<<4
#define ADC_AVG_016SMP             4<<4
#define ADC_AVG_032SMP             5<<4
#define ADC_AVG_064SMP             6<<4
#define ADC_AVG_128SMP             7<<4

////////////////////////////////////////////////////////////////////////////////
//Bipoler
////////////////////////////////////////////////////////////////////////////////
#define ADC_BI_POLAR                1<<7
#define ADC_UNI_POLAR               0<<7

#define DATA_BUFFG                  0
#define CONFIG_REG                  1
#define CHANNEL_CONFIG              2
#define LOW_THRESHOLD               3
#define HIGH_THRESHOLD              4

void ADC_Config(unsigned int Index, unsigned int Priority, unsigned int Acquistion, unsigned int Avg, unsigned int BIP_Sel);
void ADC_Channel_Config(unsigned int Index, unsigned int Positive, unsigned int Negative);
unsigned int ADC_ReadOut(unsigned int Config_No);
unsigned int QT_Config(unsigned int Index, unsigned int LowThreshold, unsigned int HighThreshold);
unsigned int ADC_ReadOutCheck(unsigned int Value);

#endif //_ADC_H_


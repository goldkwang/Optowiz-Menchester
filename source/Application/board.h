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

#ifndef _BOARD_H_
#define   _BOARD_H_


// [DCLEE DEBUG] 191209: I2C_Master_HW_Control_Enable -->
#define __HW_I2C_MASTER_ENABLE__ 1


//-----------------------------------------------------------------------------
//ADC Channels Configuration defines
//-----------------------------------------------------------------------------

#define ADST_SET  0xE000                                                        //enable ADC offset cancelation for bi-pol channels and enable SH0 interrupt and SH1 interrupt
#define ADCN_SET  0xA900

#if __SFP28_ER__==1

#if __SFP28_ER_SEMI_TUNABLE__ == 1

/////////////////       ADC config defines        ///////////////////////////
#define CONFG_RSSI         0                                                 //Config 0
#define CONFG_TX_PWR_NON      1                                                 //Config 1
//#define CONFG_RSSI2         2                                                 //Config 2
//#define CONFG_RSSI3         3                                                   //Config 3
//#define CONFG_MPD0          4                                                   //Config 4
//#define CONFG_MPD1          5                                                   //Config 5
//#define CONFG_MPD2          6                                                   //Config 6
//#define CONFG_MPD3          7                                                   //Config 7

#define CONFG_TECC          6                                                   //Config 6

#define CONFG_APC1          8                                                   //Config 8

#define CONFG_TEC1          9                                                   //Config 9
#define CONFG_TEC2         10                                                   //Config 10
#define CONFG_EXT_INV      12                                                   //Config 12 (APD-1, Fixed by ADC Controller)
//#define CONFG_EXT_BOOST1   13                                                   //Config 13 (APD-2, Fixed by ADC Controller) --> ADC17
#define CONFG_APD3         14                                                   //Config 14 (APD-3, Fixed by ADC Controller)
#define CONFG_EXT_BOOST1         15                                                   //Config 15 (APD-4, Fixed by ADC Controller, Used as BUCK4 in EVKIT)
//#define CONFG_APD4         15                                                   //Config 15 (APD-4, Fixed by ADC Controller, Used as BUCK4 in EVKIT)
#define CONFG_VTHERM1      16                                                   //Config 16 (TEC-1, Fixed by ADC Controller)
#define CONFG_VTHERM2      17                                                   //Config 17 (TEC-2, Fixed by ADC Controller)
#define CONFG_DC_DCFB1     18                                                   //Config 18 (DC-DC1, Fixed by ADC Controller)
#define CONFG_DC_DCFB2     19                                                   //Config 19 (DC-DC2, Fixed by ADC Controller)
#define CONFG_DC_DCFB3     20                                                   //Config 20 (DC-DC3, Fixed by ADC Controller)

#define CONFG_ADC_OFFSET   22                                                   //Config 22 for ADC offset
#define CONFG_VCC_COMP     23                                                   //Config 23 VCC for DS-DAC and TEC, Fixed by ADC Controller

#if __SFP_PLUS_3G_ER_SEMI_TUNABLE_HW_VER_2__ == 1

/////////////////       ADC channel defines        ///////////////////////////
//#define VTHERM2_GP00        0                                                   //Vtherm GP00, Pin 40, ADC Channel 0
#define V_THM_ADC1          1                                                     //Vtherm GP01, Pin 37, ADC Channel 1,       V_THM
//#define RSSI_GP02_ADC2     2                                                    //GP02, Pin 36, ADC Channel 2,                RSSI2
#define TX_PWR_MON_GP03_ADC3      3                                             //GP03, Pin 11, ADC Channel 3,                TX_POWER_MON, MPD_MON_MCU
//#define DC_DC_FB1         4                                                   //DCDC1 FB, VCCDAC, Pin 5, ADC Channel 4 
//#define MPD3_GP05_ADC5      5                                                   //MD, GP05, Pin 12, ADC Channel 5,            MPD3
//#define TX_PWR_MON_GP05_ADC5      5                                                   //MD, GP05, Pin 12, ADC Channel 5,            MPD3
//#define VTEC              6                                                   //VTEC, GP06, Pin 13, ADC Channel 6
//#define MPD0_GP06_ADC6      6                                                   //VTEC, GP06, Pin 13, ADC Channel 6           MPD0
#define APD_FB_GP06_ADC6      6                                                   //VTEC, GP06, Pin 13, ADC Channel 6           APD_FB
//#define GP07_ADC7         7                                                   //GP07, Pin 14, ADC Channel 7
//#define LX2                 8                                                   //LX2, Pin 27, ADC Channel 8,                 
//#define LX4                 9                                                   //LX4, Pin 22, ADC Channel 9
//#define DC_DC_FB2           10                                                  //DCDC2 FB, GP12, Pin 30, ADC Channel 10 
//#define RSSI0_GP12_ADC10    10                                                  //DCDC2 FB, GP12, Pin 30, ADC Channel 10        RSSI0
//#define MPD0_GP13_ADC11     11                                                  //BIAS_FB, GP13, Pin 7, ADC Channel 11,       
//#define MPD2_GP14_ADC12     12                                                  //DC_DC_BIAS_I, GP14, Pin 6, ADC Channel 12,  
//#define INVFB               13                                                  //INVFB, GP15, Pin 6, ADC Channel 13,
//#define RSSI2_GP16_ADC14    14                                                  //APDFB, GP16, Pin 3, ADC Channel 14,         
//#define GP17_ADC15        15                                                  //GP17, Pin 38, ADC Channel 15
//#define GP20_ADC16        16                                                  //GP20, Pin 1, ADC Channel 16
//#define APD_FB_GP21_ADC17    17                                                  //GP21, Pin 2, ADC Channel 17,                ADC_FB
//#define GP22_ADC17          18                                                  //GP22, Pin 8, ADC Channel 18
//#define GP23_ADC19          19                                                  //GP23, Pin 9, ADC Channel 19
//#define GP24_ADC20          20                                                  //GP24, Pin 10, ADC Channel 20
#define TEC_ISENSE          21                                                  //TEC_ISENSE, GP25, Pin 19, ADC Channel 21
//#define GP26_ADC22          22                                                  //GP26, Pin 20, ADC Channel 22
//#define GP27_ADC23          23                                                  //GP27, Pin 21, ADC Channel 23
//#define MPD1_GP26_ADC22       22                                                  //GP26, Pin 20, ADC Channel 22                MPD1
#define RSSI_GP27_ADC23       23                                                  //GP27, Pin 21, ADC Channel 23                RSSI

#define VCC_DIV             29                                                  //VCC DIV 
#define GND_REF             30                                                  //Ground
#define VCCO                31                                                  //VCC

////////////////////////////////////////////////////////////////////////////////

#else

/////////////////       ADC channel defines        ///////////////////////////
//#define VTHERM2_GP00        0                                                   //Vtherm GP00, Pin 40, ADC Channel 0
#define V_THM_ADC1          1                                                     //Vtherm GP01, Pin 37, ADC Channel 1,       V_THM
#define RSSI_GP02_ADC2     2                                                    //GP02, Pin 36, ADC Channel 2,                RSSI2
#define TX_PWR_MON_GP03_ADC3      3                                             //GP03, Pin 11, ADC Channel 3,                TX_POWER_MON, MPD_MON_MCU
//#define DC_DC_FB1         4                                                   //DCDC1 FB, VCCDAC, Pin 5, ADC Channel 4 
//#define MPD3_GP05_ADC5      5                                                   //MD, GP05, Pin 12, ADC Channel 5,            MPD3
//#define TX_PWR_MON_GP05_ADC5      5                                                   //MD, GP05, Pin 12, ADC Channel 5,            MPD3
//#define VTEC              6                                                   //VTEC, GP06, Pin 13, ADC Channel 6
//#define MPD0_GP06_ADC6      6                                                   //VTEC, GP06, Pin 13, ADC Channel 6           MPD0
#define APD_FB_GP06_ADC6      6                                                   //VTEC, GP06, Pin 13, ADC Channel 6           APD_FB
//#define GP07_ADC7         7                                                   //GP07, Pin 14, ADC Channel 7
//#define LX2                 8                                                   //LX2, Pin 27, ADC Channel 8,                 
//#define LX4                 9                                                   //LX4, Pin 22, ADC Channel 9
//#define DC_DC_FB2           10                                                  //DCDC2 FB, GP12, Pin 30, ADC Channel 10 
//#define RSSI0_GP12_ADC10    10                                                  //DCDC2 FB, GP12, Pin 30, ADC Channel 10        RSSI0
//#define MPD0_GP13_ADC11     11                                                  //BIAS_FB, GP13, Pin 7, ADC Channel 11,       
//#define MPD2_GP14_ADC12     12                                                  //DC_DC_BIAS_I, GP14, Pin 6, ADC Channel 12,  
//#define INVFB               13                                                  //INVFB, GP15, Pin 6, ADC Channel 13,
//#define RSSI2_GP16_ADC14    14                                                  //APDFB, GP16, Pin 3, ADC Channel 14,         
//#define GP17_ADC15        15                                                  //GP17, Pin 38, ADC Channel 15
//#define GP20_ADC16        16                                                  //GP20, Pin 1, ADC Channel 16
//#define APD_FB_GP21_ADC17    17                                                  //GP21, Pin 2, ADC Channel 17,                ADC_FB
//#define GP22_ADC17          18                                                  //GP22, Pin 8, ADC Channel 18
//#define GP23_ADC19          19                                                  //GP23, Pin 9, ADC Channel 19
//#define GP24_ADC20          20                                                  //GP24, Pin 10, ADC Channel 20
#define TEC_ISENSE          21                                                  //TEC_ISENSE, GP25, Pin 19, ADC Channel 21
//#define GP26_ADC22          22                                                  //GP26, Pin 20, ADC Channel 22
//#define GP27_ADC23          23                                                  //GP27, Pin 21, ADC Channel 23
//#define MPD1_GP26_ADC22       22                                                  //GP26, Pin 20, ADC Channel 22                MPD1
//#define MPD2_GP27_ADC23       23                                                  //GP27, Pin 21, ADC Channel 23                MPD2

#define VCC_DIV             29                                                  //VCC DIV 
#define GND_REF             30                                                  //Ground
#define VCCO                31                                                  //VCC

////////////////////////////////////////////////////////////////////////////////

#endif

#else

/////////////////       ADC config defines        ///////////////////////////
//#define CONFG_DC_DCFB1      0                                                 //Config 0
//#define CONFG_DC_DCFB2      1                                                 //Config 1
//#define CONFG_DC_DCFB3      2                                                 //Config 2
#define CONFG_RSSI         0                                                 //Config 0
//#define CONFG_RSSI0         0                                                 //Config 0
#define CONFG_TX_PWR_NON      1                                                 //Config 1
//#define CONFG_RSSI1         1                                                 //Config 1
//#define CONFG_RSSI2         2                                                 //Config 2
//#define CONFG_RSSI3         3                                                   //Config 3
//#define CONFG_MPD0          4                                                   //Config 4
//#define CONFG_MPD1          5                                                   //Config 5
//#define CONFG_MPD2          6                                                   //Config 6
//#define CONFG_MPD3          7                                                   //Config 7

#define CONFG_TECC          6                                                   //Config 6

#define CONFG_APC1          8                                                   //Config 8
//#define CONFG_RSSI          8                                                   //Config 8

#define CONFG_TEC1          9                                                   //Config 9
#define CONFG_TEC2         10                                                   //Config 10
#define CONFG_EXT_INV      12                                                   //Config 12 (APD-1, Fixed by ADC Controller)
#define CONFG_EXT_BOOST1   13                                                   //Config 13 (APD-2, Fixed by ADC Controller) --> ADC17
#define CONFG_APD3         14                                                   //Config 14 (APD-3, Fixed by ADC Controller)
#define CONFG_APD4         15                                                   //Config 15 (APD-4, Fixed by ADC Controller, Used as BUCK4 in EVKIT)
#define CONFG_VTHERM1      16                                                   //Config 16 (TEC-1, Fixed by ADC Controller)
#define CONFG_VTHERM2      17                                                   //Config 17 (TEC-2, Fixed by ADC Controller)
#define CONFG_DC_DCFB1     18                                                   //Config 18 (DC-DC1, Fixed by ADC Controller)
#define CONFG_DC_DCFB2     19                                                   //Config 19 (DC-DC2, Fixed by ADC Controller)
#define CONFG_DC_DCFB3     20                                                   //Config 20 (DC-DC3, Fixed by ADC Controller)

#define CONFG_ADC_OFFSET   22                                                   //Config 22 for ADC offset
#define CONFG_VCC_COMP     23                                                   //Config 23 VCC for DS-DAC and TEC, Fixed by ADC Controller

/////////////////       ADC channel defines        ///////////////////////////
//#define VTHERM2_GP00        0                                                   //Vtherm GP00, Pin 40, ADC Channel 0
#define V_THM_ADC1          1                                                     //Vtherm GP01, Pin 37, ADC Channel 1,       V_THM
//#define RSSI1_GP01_ADC1     1                                                   //GP01, Pin 37, ADC Channel 1,                RSSI1
#define RSSI2_GP02_ADC2     2                                                   //GP02, Pin 36, ADC Channel 2,                RSSI2
#define RSSI_GP02_ADC2     2                                                   //GP02, Pin 36, ADC Channel 2,                RSSI2
#define RSSI3_GP03_ADC3      3                                                   //GP03, Pin 11, ADC Channel 3,                RSSI3
//#define DC_DC_FB1         4                                                   //DCDC1 FB, VCCDAC, Pin 5, ADC Channel 4 
#define MPD3_GP05_ADC5      5                                                   //MD, GP05, Pin 12, ADC Channel 5,            MPD3
#define TX_PWR_MON_GP05_ADC5      5                                                   //MD, GP05, Pin 12, ADC Channel 5,            MPD3
//#define VTEC              6                                                   //VTEC, GP06, Pin 13, ADC Channel 6
//#define MPD0_GP06_ADC6      6                                                   //VTEC, GP06, Pin 13, ADC Channel 6           MPD0
#define APD_FB_GP06_ADC6      6                                                   //VTEC, GP06, Pin 13, ADC Channel 6           APD_FB
//#define GP07_ADC7         7                                                   //GP07, Pin 14, ADC Channel 7
//#define LX2                 8                                                   //LX2, Pin 27, ADC Channel 8,                 
//#define LX4                 9                                                   //LX4, Pin 22, ADC Channel 9
//#define DC_DC_FB2           10                                                  //DCDC2 FB, GP12, Pin 30, ADC Channel 10 
#define RSSI0_GP12_ADC10    10                                                  //DCDC2 FB, GP12, Pin 30, ADC Channel 10        RSSI0
//#define MPD0_GP13_ADC11     11                                                  //BIAS_FB, GP13, Pin 7, ADC Channel 11,       
//#define MPD2_GP14_ADC12     12                                                  //DC_DC_BIAS_I, GP14, Pin 6, ADC Channel 12,  
//#define INVFB               13                                                  //INVFB, GP15, Pin 6, ADC Channel 13,
//#define RSSI2_GP16_ADC14    14                                                  //APDFB, GP16, Pin 3, ADC Channel 14,         
//#define GP17_ADC15        15                                                  //GP17, Pin 38, ADC Channel 15
//#define GP20_ADC16        16                                                  //GP20, Pin 1, ADC Channel 16
#define APD_FB_GP21_ADC17    17                                                  //GP21, Pin 2, ADC Channel 17,                ADC_FB
//#define GP22_ADC17          18                                                  //GP22, Pin 8, ADC Channel 18
//#define GP23_ADC19          19                                                  //GP23, Pin 9, ADC Channel 19
//#define GP24_ADC20          20                                                  //GP24, Pin 10, ADC Channel 20
#define TEC_ISENSE          21                                                  //TEC_ISENSE, GP25, Pin 19, ADC Channel 21
//#define GP26_ADC22          22                                                  //GP26, Pin 20, ADC Channel 22
//#define GP27_ADC23          23                                                  //GP27, Pin 21, ADC Channel 23
#define MPD1_GP26_ADC22       22                                                  //GP26, Pin 20, ADC Channel 22                MPD1
#define MPD2_GP27_ADC23       23                                                  //GP27, Pin 21, ADC Channel 23                MPD2

#define VCC_DIV             29                                                  //VCC DIV 
#define GND_REF             30                                                  //Ground
#define VCCO                31                                                  //VCC

////////////////////////////////////////////////////////////////////////////////

#endif

#else

///////////////////       ADC config defines        ///////////////////////////
////#define CONFG_DC_DCFB1      0                                                 //Config 0
////#define CONFG_DC_DCFB2      1                                                 //Config 1
////#define CONFG_DC_DCFB3      2                                                 //Config 2
//#define CONFG_VTEC          3                                                   //Config 3
//#define CONFG_TECN          4                                                   //Config 4
//#define CONFG_BIAS          5                                                   //Config 5
//#define CONFG_TECC          6                                                   //Config 6
//#define CONFG_MON5          7                                                   //Config 7
//#define CONFG_APC1          8                                                   //Config 8
//#define CONFG_TEC1          9                                                   //Config 9
//#define CONFG_TEC2         10                                                   //Config 10
//#define CONFG_EXT_INV      12                                                   //Config 12 (APD-1, Fixed by ADC Controller)
//#define CONFG_EXT_BOOST1   13                                                   //Config 13 (APD-2, Fixed by ADC Controller)
//#define CONFG_APD3         14                                                   //Config 14 (APD-3, Fixed by ADC Controller)
//#define CONFG_APD4         15                                                   //Config 15 (APD-4, Fixed by ADC Controller, Used as BUCK4 in EVKIT)
//#define CONFG_VTHERM1      16                                                   //Config 16 (TEC-1, Fixed by ADC Controller)
//#define CONFG_VTHERM2      17                                                   //Config 17 (TEC-2, Fixed by ADC Controller)
//#define CONFG_DC_DCFB1     18                                                   //Config 18 (DC-DC1, Fixed by ADC Controller)
//#define CONFG_DC_DCFB2     19                                                   //Config 19 (DC-DC2, Fixed by ADC Controller)
//#define CONFG_DC_DCFB3     20                                                   //Config 20 (DC-DC3, Fixed by ADC Controller)
//
//#define CONFG_ADC_OFFSET   22                                                   //Config 22 for ADC offset
//#define CONFG_VCC_COMP     23                                                   //Config 23 VCC for DS-DAC and TEC, Fixed by ADC Controller
//
///////////////////       ADC channel defines        ///////////////////////////
//#define VTHERM2_GP00        0                                                   //Vtherm GP00, Pin 40, ADC Channel 0
//#define RSSI_GP01_ADC1        1                                                   //GP01, Pin 37, ADC Channel 1
////#define GP02_ADC1           2                                                   //GP02, Pin 36, ADC Channel 2
////#define GP03_ADC3           3                                                   //GP03, Pin 11, ADC Channel 3
//#define DC_DC_FB1           4                                                   //DCDC1 FB, VCCDAC, Pin 5, ADC Channel 4 
//#define MD                  5                                                   //MD, GP05, Pin 12, ADC Channel 5
//#define VTEC                6                                                   //VTEC, GP06, Pin 13, ADC Channel 6
////#define GP07_ADC7           7                                                   //GP07, Pin 14, ADC Channel 7
////#define LX2                 8                                                   //LX2, Pin 27, ADC Channel 8
//#define LX4                 9                                                   //LX4, Pin 22, ADC Channel 9
//#define DC_DC_FB2           10                                                  //DCDC2 FB, GP12, Pin 30, ADC Channel 10 
//#define BIAS_FB             11                                                  //BIAS_FB, GP13, Pin 7, ADC Channel 11
//#define DC_DC_BIAS_ISENSE   12                                                  //DC_DC_BIAS_I, GP14, Pin 6, ADC Channel 12
//#define INVFB               13                                                  //INVFB, GP15, Pin 6, ADC Channel 13
//#define APDFB               14                                                  //APDFB, GP13, Pin 3, ADC Channel 14
////#define GP17_ADC15          15                                                  //GP17, Pin 38, ADC Channel 15
////#define GP20_ADC16          16                                                  //GP20, Pin 1, ADC Channel 16
////#define GP21_ADC17          17                                                  //GP21, Pin 2, ADC Channel 17
////#define GP22_ADC17          18                                                  //GP22, Pin 8, ADC Channel 18
////#define GP23_ADC19          19                                                  //GP23, Pin 9, ADC Channel 19
////#define GP24_ADC20          20                                                  //GP24, Pin 10, ADC Channel 20
//#define TEC_ISENSE          21                                                  //TEC_ISENSE, GP25, Pin 19, ADC Channel 21
////#define GP26_ADC22          22                                                  //GP26, Pin 20, ADC Channel 22
////#define GP27_ADC23          23                                                  //GP27, Pin 21, ADC Channel 23
//
//#define VCC_DIV             29                                                  //VCC DIV 
//#define GND_REF             30                                                  //Ground
//#define VCCO                31                                                  //VCC

////////////////////////////////////////////////////////////////////////////////

#endif


#define WRITE_RESET          0x0001
#define WRITE_TOPCTRL        0x0002
#define WRITE_TX_CNTL        0x0004
#define WRITE_TX_CONFIG      0x0008
#define WRITE_RX_CONFIG      0x0010
#define WRITE_CONTROL        0x0020
#define WRITE_TX_SET_EQ      0x0040
#define WRITE_RX_SET_PE      0x0080
#define WRITE_TX_MOD         0x0100
#define WRITE_TX_BIAS        0x0200



#define ASSERTED             1
#define DE_ASSERTED          0

#ifndef DCDC_BIASING
//#define BIAS_MAX             0x0733                                             //IDAC biasing limitation ~90mA
#define BIAS_MAX             0x0FFF                                             //IDAC biasing limitation ~90mA
#endif

#define MOD_MAX              0x01FF


//-----------------------------------------------------------------------------
//DCDC Configuration defines
//-----------------------------------------------------------------------------
#define DCCNSET              0x032E

//-----------------------------------------------------------------------------
//External DCDC Configuration defines
//-----------------------------------------------------------------------------
#define APD_INIT_KP          0x5000
#define APD_INIT_KI          0x000A

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
void INRUSH_Init(void);
void WATCHDOG_Init(void);
void GPIO_Init(void);
void ADC_Init(void);
void DCDC_Init(void);   
void APD_Init(void);   
void INV_Init(void); 
void INV_Update_KPKI(void);
void TEC_Init(void);   
void IDAC_Init(void);       
void DSDAC_Init(void); 
void SH_Init(void);
void I2CMaster_Init(void);
void PLA_Init(void);
void Initialization(void);
unsigned int ReadWaitingI2C(void);
void PLA_Soft_TXD_Control(unsigned char control);
void WriteWaitingI2C(unsigned int unData);
void MasterI2CArbitration(void);
void write_bias(unsigned int unBias);
void write_mod(unsigned int unMod);
void TXD_External_Interrupt_init(void);
void TECC_Disable(unsigned int unChannel);
void PLA_Pin_TXD_Control(unsigned char unControl);
void PLA_Soft_TXD_Control_forced(unsigned char control);
#endif   // _BOARD_H_

//-----------------------------------------------------------------------------
// end of file
//-----------------------------------------------------------------------------


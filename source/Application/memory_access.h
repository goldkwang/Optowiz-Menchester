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

#ifndef __MEM_ACCESS_H_
#define __MEM_ACCESS_H_

// Manchester Control Function Declaration
extern void Manchester_Control_I2C(unsigned char command);

#ifndef __SFP28_ER__

#define __QSFP28_ER4__ 1
#define __QSFP28_LR4__ 0
#define __QSFP28_CWDM4__ 0
#define __QSFP28_SR4__ 0

#define __SFP28_ER__ 1
#define __SFP28_ER_SEMI_TUNABLE__ 1
#define __SFP_PLUS_3G_ER_SEMI_TUNABLE__ 1
#define __SFP_PLUS_3G_10G_ER_SEMI_TUNABLE__ 0

#define __SFP_PLUS_3G_ER_SEMI_TUNABLE_SW_VER_2__ 0
// __SFP_PLUS_3G_ER_SEMI_TUNABLE_SW_VER_2__ RSSI ���� ó���� �µ����� Interpolation ���� �����ϴ� ������� ����

#define __SFP_PLUS_3G_ER_SEMI_TUNABLE_HW_VER_2__ 0
// __SFP_PLUS_3G_ER_SEMI_TUNABLE_HW_VER_2__ current mirror ����, RSSI���� DS4835 ADC23 �ɿ� ���� ������

#define __HSFP_10G_ER_SEMI_TUNABLE__ 1

#define __HSFP_10G_MULTI_RATE_SEMI_TUNABLE__ 1

// 2021.06.02. for SKT Spec. -->
// A0H, Reg 60 ~ 62�� �� ä���� �⺻ ������ ǥ�� �ϵ��� ������
#define __WAVELENGTH_LIKE_FIXED_VER__ 1

#define __WAVELENGTH_LIKE_FIXED_VER_50PM__ 1

#define __FIXED_MODE_SFP_VER__ 1
#define __TUNABLE_MODE_SFP_VER__ 0

#define __HFR_REQ_VER__ 1
#define __HFR_REQ_DDM_FLAG_VER__ 1

#define __WO_TXDIS_PIN_MONITORING__ 0

#define __INTEROPERABILITY_TEST__ 1
#define __INTEROPERABILITY_TEST_P00H__ 1
#define __INTEROPERABILITY_TEST_P02H__ 0

#define __INTEROPERABILITY_TEST_POLL_PAGESEL__ 1

// 2021.06.02. for SKT Spec. <--

#define __WAVELENGTH_ANY_VER__ 1

#define __WAVELENGTH_1290_VER__ 0
#define __WAVELENGTH_1270_VER__ 0
#define __WAVELENGTH_1330_VER__ 0
#define __WAVELENGTH_1350_VER__ 0
#define __WAVELENGTH_1410_VER__ 0
#define __WAVELENGTH_1430_VER__ 0
#define __WAVELENGTH_1450_VER__ 0
#define __WAVELENGTH_1470_VER__ 0
#define __WAVELENGTH_1490_VER__ 0
#define __WAVELENGTH_1510_VER__ 0

// 3G SFP+ Wavelength
// #define __WAVELENGTH_1410_VER__ 0
#define __WAVELENGTH_1530_VER__ 0
#define __WAVELENGTH_1550_VER__ 0

#define __RLASER_TRIM_11_OHM__ 0
#define __RLASER_TRIM_13_OHM__ 1
#define __RLASER_TRIM_18_OHM__ 0

#define __EXTERNAL_CALIBRATION_ENABLE_OPTIONS__ 0
#define __ADDITIONAL_ENHANCED_FEATURES_ENABLE__ 1

#define __PRBS_GEN_MODE_AT_TX_SIGNAL_LOS_LOL_ST__ 0

#define __TUNABLE_CH_UPDATE_VER_1__ 1
// VER_1: Group A, B: 1 ~ 4: �ش� ���� �;߸� ä�� ���� ������
//        Group C, D: 5 ~ 8

#endif

// FW Version Descriptions: 2020.11.13. / 01.9 (240718)
// FW Version Descriptions: 2025.06.24. / 02.0 (250624)
#define FW_VER_0 '0'
#define FW_VER_1 '2'
#define FW_VER_2 '.'
#define FW_VER_3 '4'

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------

#define ACCESS_LEVEL_NONE 0
#define ACCESS_LEVEL_RO 1
#define ACCESS_LEVEL_RW 2

#if __SFP28_ER__ == 1

typedef struct
{
   unsigned char page;
   unsigned char addr;
} i2cWriteStruct;

// Page definition
#define PAGE_0 0
#define PAGE_1 1
#define PAGE_00H 0x00
#define PAGE_01H 0x01
#define PAGE_02H 0x02
#define PAGE_03H 0x03
#define PAGE_04H 0x04
#define PAGE_05H 0x05
#define PAGE_06H 0x06

#define PAGE_80H 0x80
#define PAGE_81H 0x81
#define PAGE_82H 0x82
#define PAGE_83H 0x83
#define PAGE_84H 0x84

#define MEMORY_WRITE_BUFFER_SIZE 256

#define EVK_TYPE_IDAC_BIAS 0x58

// #define EVK_TYPE_DCDC_BIAS    0x90

// possible flags for WriteBufferStatus
typedef enum WRITE_BUFFER_STATUS_ENUM_TAG
{
   MEMORY_WRITE_BUFFER_IDLE,
   MEMORY_WRITE_BUFFER_WRITING,
   MEMORY_WRITE_BUFFER_WAITING_TO_PROCESS,
   MEMORY_WRITE_BUFFER_READING
} WriteBufferStatus_E;

// structure of parameters for communication from host over I2C
typedef struct WRITE_BUFFER_STRUCTURE_TAG
{
   unsigned char devAddress;                                 // A0 or A2
   WriteBufferStatus_E bufferStatus;                         // flag showing status of transaction
   unsigned char numOfEntries;                               // num of bytes received
   unsigned char address;                                    // current register address
   unsigned char writeBufferEntry[MEMORY_WRITE_BUFFER_SIZE]; // I2C data bytes
} WriteBuffer_S;

#define PLA_TXD 1
#define PLA_RSEL 2
#define PLA_TXF 3
#define PLA_LOS 4

#define TEC_CH1 0
#define TEC_CH2 1

#define BUCK1_ENABLE 0x80
#define BUCK2_ENABLE 0x40
#define TEC2_ENABLE 0x20
#define TEC1_ENABLE 0x10
#define APD_ENABLE 0x08
#define INV_ENABLE 0x04
#define LB_IDAC_ENABLE 0x04

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
void SW_Delay(unsigned int unDelay_counter);
void ProcessReceivedI2CData(void);
// void CopyLutToSram(unsigned char ucTable_num);
unsigned int GetIntFromFlash(unsigned char ucTable_num, unsigned int unAddress);

// unsigned char GetLUTByteFromFlash(unsigned char ucTable_num, unsigned int unIndex);
void CheckPasswordLevel(void);
void Memory_Init(void);
void UpdateInternalTemp(void);
// void UpdateExternalTemp(void);
void ADC_Init(void);

// void UpdateWordA2hTable(unsigned char ucTable, unsigned int *pAddress, unsigned int unData);
// void UpdateByteA2hTable(unsigned char ucTable, unsigned char *pAddress, unsigned char ucData);

// Functions for Other MCUs, by DLEE

extern unsigned long __swap_bytes_to_long(unsigned long src);
extern void tx_input_equalization(unsigned char chNo, unsigned char set_value);
extern void rx_output_deemphasis(unsigned char chNo, unsigned char set_value);
extern void rx_output_amplitude(unsigned char chNo, unsigned char set_value);
extern float __swap_bytes_to_float(float src);

extern void update_msa_control_regs_from_tx_cdr(void);
extern void update_msa_control_regs_from_rx_cdr(void);

//-----------------------------------------------------------------------------
// global variables prototypes
//-----------------------------------------------------------------------------

#else

//-----------------------------------------------------------------------------
// global variables prototypes
//-----------------------------------------------------------------------------
#endif

#endif //__MEM_ACCESS_H_

// End

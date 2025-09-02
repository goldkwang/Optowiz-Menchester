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

#ifndef __MEM_MAP_H_
#define __MEM_MAP_H_

#ifndef __QSFP28_ER4__

#define __QSFP28_ER4__ 0
#define __QSFP28_LR4__ 0
#define __QSFP28_CWDM4__ 0
#define __QSFP28_SR4__ 0

#define __SFP28_ER__ 1
#endif

/*******    Memory locations for in SRAM     ********/

#define RX_COUNT_ADD 0x0080         // location for Rx_Count
#define MEM_ADD_ADD 0x0082          // location for Mem_Address
#define A0_SRAM_OFFSET 0x0100       // location of A0 memory in SRAM: I2C_Slave_Buffer_A0_Local_Memory[256]
#define A2_LOWER_SRAM_OFFSET 0x0200 // locatino of A2 lower memory in SRAM: I2C_Slave_Buffer_A2[128]
#define A2_UPPER_SRAM_OFFSET 0x0280 // locatino of A2 upper memory in SRAM: I2C_Slave_Buffer_A2_P0_Up[128]

#define I2C_WRITE_LIST 0x0300 // location of scratch area for LUT copies
#define I2C_RX_BUF_ADD 0x0400 // location of 256 byte I2C Rx Buffer

#define PAGE00H_UPPER 0x0500 // location of 128 byte Page02h : I2C_Slave_Buffer_A2_P0_Up[128]: User EEPROM
#define PAGE01H_UPPER 0x0580 // location of 128 byte Page03h : I2C_Slave_Buffer_A2_P1_Up[128]: User EEPROM
#define PAGE02H_UPPER 0x0600 // location of 128 byte Page04h : I2C_Slave_Buffer_A2_P2_Up[128], Tunable
#define PAGE80H_UPPER 0x0680 // location of 128 byte Page80h : I2C_Slave_Buffer_A2_P80h_Up[128], Vendor Config 1
#define PAGE81H_UPPER 0x0700 // location of 128 byte Page81h : I2C_Slave_Buffer_A2_P81h_Up[128], Vendor Config 2
#define PAGE82H_UPPER 0x0780 // location of 128 byte Page82h : I2C_Slave_Buffer_A2_P82h_Up[128], CDRs

/*******    Memory locations for A0, A2 and LUTs in Flash     ********/
#define FLASH_A0_CONST_START 0xEE00       // Flash location for A0 memory:
#define FLASH_A2_LOWER_CONST_START 0xEF00 // Flash location for A2 LOWER Cibf:
#define FLASH_USER_EERPOM_START 0xF000    // Flash location for User EEPROM, A2 Device Page00, Page01 Upper Memory
#define FLASH_A0_START 0xF200             // Flash location for A0 Device memory: 256 bytes
#define FLASH_A2_START 0xF400             // Flash location for A2 Device memory lower memory: 128 bytes
#define FLASH_PAGE02H_START 0xF600        // Flash location for Page 02h
#define FLASH_PAGE80H_START 0xF800        // Flash location for Page 80h
#define FLASH_PAGE81H_START 0xFA00        // Flash location for Page 81h
#define FLASH_PAGE82H_START 0xFC00        // Flash location for Page 82h

/******************* PAGE80h,81h Module Specific Configuration Memory: 128 + 128 bytes *************/
// Device Address: 0xA2
//-----------------------------------------------------------------------------
// TRX Module Configuration defines
//-----------------------------------------------------------------------------
#define MAX_TRX_SIGNALS 1
#define MAX_CHANNELS_PER_SIGNAL 1

typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef float FP32;
typedef signed short int16_t;
typedef signed char int8_t;

#ifndef __NEW_TX_POWER_MON_BY_TEMPERATURE__
#define __NEW_TX_POWER_MON_BY_TEMPERATURE__ 1
#endif

#if __SFP28_ER__ == 1

typedef struct
{

} A0_MEMORY_MAP;

typedef struct
{

        /*******    A2 Lower Memory Map: This is the offset location of the registers    ********/
        unsigned int A2_TEMP_HIGH_ALARM_OFF;         // Address 0x00
        unsigned int A2_TEMP_LOW_ALARM_OFF;          // Address 0x02
        unsigned int A2_TEMP_HIGH_WARNING_OFF;       // Address 0x04
        unsigned int A2_TEMP_LOW_WARNING_OFF;        // Address 0x06
        unsigned int A2_VOLTAGE_HIGH_ALARM_OFF;      // Address 0x08
        unsigned int A2_VOLTAGE_LOW_ALARM_OFF;       // Address 0x0A
        unsigned int A2_VOLTAGE_HIGH_WARNING_OFF;    // Address 0x0C
        unsigned int A2_VOLTAGE_LOW_WARNING_OFF;     // Address 0x0E
        unsigned int A2_BIAS_HIGH_ALARM_OFF;         // Address 0x10
        unsigned int A2_BIAS_LOW_ALARM_OFF;          // Address 0x12
        unsigned int A2_BIAS_HIGH_WARNING_OFF;       // Address 0x14
        unsigned int A2_BIAS_LOW_WARNING_OFF;        // Address 0x16
        unsigned int A2_TX_POWER_HIGH_ALARM_OFF;     // Address 0x18
        unsigned int A2_TX_POWER_LOW_ALARM_OFF;      // Address 0x1A
        unsigned int A2_TX_POWER_HIGH_WARNING_OFF;   // Address 0x1C
        unsigned int A2_TX_POWER_LOW_WARNING_OFF;    // Address 0x1E
        unsigned int A2_RX_POWER_HIGH_ALARM_OFF;     // Address 0x20
        unsigned int A2_RX_POWER_LOW_ALARM_OFF;      // Address 0x22
        unsigned int A2_RX_POWER_HIGH_WARNING_OFF;   // Address 0x24
        unsigned int A2_RX_POWER_LOW_WARNING_OFF;    // Address 0x26
        unsigned int A2_LASER_TEMP_HIGH_ALARM_OFF;   // Address 0x28
        unsigned int A2_LASER_TEMP_LOW_ALARM_OFF;    // Address 0x2A
        unsigned int A2_LASER_TEMP_HIGH_WARNING_OFF; // Address 0x2C
        unsigned int A2_LASER_TEMP_LOW_WARNING_OFF;  // Address 0x2E
        unsigned int A2_TECC_HIGH_ALARM_OFF;         // Address 0x30
        unsigned int A2_TECC_LOW_ALARM_OFF;          // Address 0x32
        unsigned int A2_TECC_HIGH_WARNING_OFF;       // Address 0x34
        unsigned int A2_TECC_LOW_WARNING_OFF;        // Address 0x36
        unsigned int A2_RESERVED_38_4B_OFF;          // Address 0x38

        unsigned int A2_RESERVED_4C_5F_OFF;          // Address 0x4C
        unsigned int A2_TEMPERATURE_OFF;             // Address 0x60
        unsigned int A2_VCC_OFF;                     // Address 0x62
        unsigned int A2_TX_BIAS_OFF;                 // Address 0x64
        unsigned int A2_TX_POWER_OFF;                // Address 0x66
        unsigned int A2_RX_POWER_OFF;                // Address 0x68
        unsigned int A2_LASER_TEMP_OFF;              // Address 0x6A
        unsigned int A2_TEC_CURRENT_OFF;             // Address 0x6C
        unsigned int A2_STATUS_CONTROL_OFF;          // Address 0x6E
        unsigned int A2_RESERVED_6F_OFF;             // Address 0x6F
        unsigned int A2_ALARM_WARNING_70_OFF;        // Address 0x70
        unsigned int A2_ALARM_WARNING_71_OFF;        // Address 0x71
        unsigned int A2_TXEQ_72_OFF;                 // Address 0x72
        unsigned int A2_RXPREEMP_73_OFF;             // Address 0x73
        unsigned int A2_ALARM_WARNING_74_OFF;        // Address 0x74
        unsigned int A2_ALARM_WARNING_75_OFF;        // Address 0x75
        unsigned int A2_EXTENDED_CONTROL_STATUS_OFF; // Address 0x76
        unsigned int A2_RESERVED_77_OFF;             // Address 0x77
        unsigned int A2_READ_CHIP_STATUS_OFF;        // Address 0x78
        unsigned int A2_OPERATION_MODE_OFF;          // Address 0x79
        unsigned int A2_LUT_MODE_OFF;                // Address 0x7A
        unsigned int A2_PASSWORD_OFF;                // Address 0x7B
        unsigned int A2_TABLE_OFF;                   // Address 0x7F

} A2_LOWER_MEMORY_MAP;

typedef struct
{
        uint16_t flash_reset_flag; // Address 0x80, size = 2
        uint16_t module_state;     // Address 0x82, size = 2
        uint8_t command;           // Address 0x84, size = 1,
                                   // B[7:4] = command, if [3:2]=00, 0010b, 0100b, 1000b: Write I2C, 0011b, 0101b, 1001b: Read I2C,
                                   //                   if [3:2]= 01b(restore), 10b(save) [7:4]: save or restore page no, 0h, 1h, 2h, 3h, 9h(A4 device address)
                                   // [3:2] = extended_command(01b: Restore, 10b: NVR Save, 00b: Internal I2C Operation,
                                   // [1:0] = cmd_status: 00b: IDLE, 01b: Command completed successfully, 10b: Command in progress, 11b: Command failed
        uint8_t page;              // Address 0x85, size = 1
        uint8_t addr;              // Address 0x86, size = 1
        uint8_t data_length;       // Address 0x87, size = 1
        uint8_t w_data[4];         // Address 0x88, size = 4
        uint8_t r_data[4];         // Address 0x8c, size = 4

        uint8_t LdControlMode;    // Address 0x90, size = 1
        uint8_t LdControlMode_1;  // Address 0x91, size = 1
        uint16_t ModBiasSet;      // Address 0x92, size = 2
        uint16_t XconBiasSet;     // Address 0x94, size = 2
        uint16_t forcedLdBiasSet; // Address 0x96, size = 2

        unsigned int nt_ModBiasSet;  // Address 0x98-0x99
        unsigned int nt_XconBiasSet; // Address 0x9A-0x9B
        unsigned int nt_LdBiasSet;   // Address 0x9B-0x9C
        signed int nt_temp;          // Address 0x9E-0x9F

        unsigned int ht_ModBiasSet;  // Address 0xA0-0xA1
        unsigned int ht_XconBiasSet; // Address 0xA2-0xA3
        unsigned int ht_LdBiasSet;   // Address 0xA4-0xA5
        signed int ht_temp;          // Address 0xA6-0xA7

        unsigned int lt_ModBiasSet;  // Address 0xA8-0xA9
        unsigned int lt_XconBiasSet; // Address 0xAA-0xAB
        unsigned int lt_LdBiasSet;   // Address 0xAC-0xAD
        signed int lt_temp;          // Address 0xAE-0xAF

#if __NEW_TX_POWER_MON_BY_TEMPERATURE__ == 1

        unsigned int txPower_at_highTemp;   // Address 0xB0 - 0xB1, 70 C
        unsigned int txPower_at_normalTemp; // Address 0xB2-0xB3, 25 C
        unsigned int txPower_at_lowTemp;    // Address 0xB4-0xB5, 0 C
        unsigned int txPower_at_ddm_offset; // Address 0xB6-0xB7
#else

        FP32 txPower_coeff_0; // addr = 0xB0, size = 4
        FP32 txPower_coeff_1; // addr = 0xB4, size = 4

#endif

        uint16_t VCC_Slope;    // Address 0xB8-0xB9
        uint16_t VCC_Offset;   // Address 0xBA-0xBB
        uint16_t ITEMP_Slope;  // Address 0xBC-0xBD
        uint16_t ITEMP_Offset; // Address 0xBE-0xBF

        FP32 rxPower_coeff_0; // addr = 0xC0, size = 4
        FP32 rxPower_coeff_1; // addr = 0xC4, size = 4
        FP32 rxPower_coeff_2; // addr = 0xC8, size = 4
        FP32 rxPower_coeff_3; // addr = 0xCC, size = 4
        FP32 rxPower_coeff_4; // addr = 0xC0, size = 4

        uint16_t ADC_VCC;           // Address 0xD4-0xD5
        uint16_t ADC_INTERNAL_TEMP; // Address 0xD6-0xD7

} A2_PAGE_80H_MEMORY_MAP;

// typedef A2_PAGE_80H_MEMORY_MAP flashStructType;

typedef struct
{
        unsigned char DEVICE_CONFIG; // Address 0x00, 0x80
        unsigned char PMIC_SELECT;   // Address 0x01, 0x81

        unsigned int APD_ERRSTARTCLAMP;     // Address 0x02, 0x82
        unsigned int APD_DUTYCLAMP;         // Address 0x04, 0x84
        unsigned int APD_INTEGRALGAIN;      // Address 0x06, 0x86
        unsigned int APD_DUTYSTARTINCCLAMP; // Address 0x08, 0x88
        unsigned int APD_INTEGRALCLAMP;     // Address 0x0A, 0x8A
        unsigned int APD_APDNEGERRCLAMP;    // Address 0x0C, 0x8C
        unsigned int APD_APDPOSERRCLAMP;    // Address 0x0E, 0x8E
        unsigned int APD_PROPORTIONALGAIN;  // Address 0x10, 0x90

        unsigned int APD_TARGET_OUTPUT;   // Address 0x12, 0x92
        unsigned int APD_CONFIG;          // Address 0x14, 0x94
        unsigned int APD_CURRENT_SETTING; // Address 0x16, 0x96

        unsigned int V_THM; // Address 0x18, 0x98

        unsigned int TEC1_SETPOINT;                       // Address 0x1A, 0x9A
        unsigned int TEC1_KP;                             // Address 0x1C, 0x9C
        unsigned int TEC1_KI;                             // Address 0x1E, 0x9E
        unsigned int TEC1_KD;                             // Address 0x20, 0xA0
        unsigned int TEC1_SHIFT;                          // Address 0x22, 0xA2
        unsigned int TEC1_POSERRCLAMP;                    // Address 0x24, 0xA4
        unsigned int TEC1_NEGERRCLAMP;                    // Address 0x26, 0xA6
        unsigned int TEC1_POSOPCLAMP;                     // Address 0x28, 0xA8
        unsigned int TEC1_NEGOPCLAMP;                     // Address 0x2A, 0xAA
        unsigned int TEC1_CNFGCURRENTMEA_BURSTGPIOCONFIG; // Address 0x2C, 0xAC
        unsigned int TEC1_OFFSETRIGGER;                   // Address 0x2E, 0xAE
        unsigned int TEC1_BURSTPWMDUTYOFFSET;             // Address 0x30, 0xB0
        unsigned int TEC1_NORMAL_VCC;                     // Address 0x32, 0xB2
        unsigned int TEC1_DUTY_CYCLE;                     // Address 0x34, 0xB4
        unsigned int TEC1_I_MEAS;                         // Address 0x36, 0xB6

        unsigned int IDAC_CONFIG; // addr = 0x38, 0xB8
} A2_PAGE_81H_MEMORY_MAP;

typedef union
{
        uint8_t c_data[4];
        uint16_t u2_data[2];
        unsigned long u_data;
        float fp;
} IEEE_754_FP_Type;

// Flash Memory �Ҵ� ������ ����
#define FLASH_MEMORY_BASE 0x00

#define FLASH_RESET_FLAG_REG_OFFSET FLASH_MEMORY_BASE
#define FLASH_RESET_FLAG_REG_SIZE 2
#define FLASH_RESET_FLAG_REG (FLASH_RESET_FLAG_REG_OFFSET)

#define FLASH_MODULE_STATE_OFFSET (FLASH_RESET_FLAG_REG_OFFSET + FLASH_RESET_FLAG_REG_SIZE)
#define FLASH_MODULE_STATE_SIZE 2
#define FLASH_MODULE_STATE (FLASH_MODULE_STATE_OFFSET)

#define FLASH_COMMAND_OFFSET (FLASH_MODULE_STATE_OFFSET + FLASH_MODULE_STATE_SIZE)
#define FLASH_COMMAND_SIZE 1
#define FLASH_COMMAND (FLASH_COMMAND_OFFSET)

#define FLASH_PAGE_OFFSET (FLASH_COMMAND_OFFSET + FLASH_COMMAND_SIZE)
#define FLASH_PAGE_SIZE 1
#define FLASH_PAGE (FLASH_PAGE_OFFSET)

#define FLASH_ADDR_OFFSET (FLASH_PAGE_OFFSET + FLASH_PAGE_SIZE)
#define FLASH_ADDR_SIZE 1
#define FLASH_ADDR (FLASH_ADDR_OFFSET)

#define FLASH_DATA_LENGTH_OFFSET (FLASH_ADDR_OFFSET + FLASH_ADDR_SIZE)
#define FLASH_DATA_LENGTH_SIZE 1
#define FLASH_DATA_LENGTH (FLASH_DATA_LENGTH_OFFSET)

#define FLASH_W_DATA_OFFSET (FLASH_DATA_LENGTH_OFFSET + FLASH_DATA_LENGTH_SIZE)
#define FLASH_W_DATA_SIZE 4
#define FLASH_W_DATA(n) (FLASH_W_DATA_OFFSET + (((n) - 1) * 0x01))

#define FLASH_R_DATA_OFFSET (FLASH_W_DATA_OFFSET + FLASH_W_DATA_SIZE)
#define FLASH_R_DATA_SIZE 4
#define FLASH_R_DATA(n) (FLASH_R_DATA_OFFSET + (((n) - 1) * 0x01))

#define FLASH_LD_CONTROL_MODE_OFFSET (FLASH_R_DATA_OFFSET + FLASH_R_DATA_SIZE)
#define FLASH_LD_CONTROL_MODE_SIZE 1
#define FLASH_LD_CONTROL_MODE(n) (FLASH_LD_CONTROL_MODE_OFFSET + (((n) - 1) * 0x01))

#define FLASH_LD_CONTROL_MODE_1_OFFSET (FLASH_LD_CONTROL_MODE_OFFSET + FLASH_LD_CONTROL_MODE_SIZE)
#define FLASH_LD_CONTROL_MODE_1_SIZE 1
#define FLASH_LD_CONTROL_MODE_1(n) (FLASH_LD_CONTROL_MODE_1_OFFSET + (((n) - 1) * 0x01))

#define FLASH_MOD_BIAS_SET_OFFSET (FLASH_LD_CONTROL_MODE_1_OFFSET + FLASH_LD_CONTROL_MODE_1_SIZE)
#define FLASH_MOD_BIAS_SET_SIZE 2
#define FLASH_MOD_BIAS_SET(n) (FLASH_MOD_BIAS_SET_OFFSET + (((n) - 1) * 0x02))

#define FLASH_XCON_BIAS_SET_OFFSET (FLASH_MOD_BIAS_SET_OFFSET + FLASH_MOD_BIAS_SET_SIZE)
#define FLASH_XCON_BIAS_SET_SIZE 2
#define FLASH_XCON_BIAS_SET(n) (FLASH_XCON_BIAS_SET_OFFSET + (((n) - 1) * 0x02))

#define FLASH_FORCED_LD_BIAS_SET_OFFSET (FLASH_XCON_BIAS_SET_OFFSET + FLASH_XCON_BIAS_SET_SIZE)
#define FLASH_FORCED_LD_BIAS_SET_SIZE 2
#define FLASH_FORCED_LD_BIAS_SET(n) (FLASH_FORCED_LD_BIAS_SET_OFFSET + (((n) - 1) * 0x02))

// Redefined address
// APD Configuration Registers
#define FLASH_APD_ERRSTARTCLAMP (0x30)
#define FLASH_APD_DUTYCLAMP (0x32)
#define FLASH_APD_INTEGRALGAIN (0x34)
#define FLASH_APD_DUTYSTARTINCCLAMP (0x36)
#define FLASH_APD_INTEGRALCLAMP (0x38)
#define FLASH_APD_APDNEGERRCLAMP (0x3A)
#define FLASH_APD_APDPOSERRCLAMP (0x3C)
#define FLASH_APD_PROPORTIONALGAIN (0x3E)

#define FLASH_APD_TARGET_OUTPUT (0x6E)
#define FLASH_APD_CONFIG (0x8E)
#define FLASH_APD_CURRENT_SETTING (0xE4)

// TEC Configuration Registers
#define FLASH_TEC1_SETPOINT (0x70)
#define FLASH_TEC1_KP (0x72)
#define FLASH_TEC1_KI (0x74)
#define FLASH_TEC1_KD (0x76)
#define FLASH_TEC1_SHIFT (0x78)
#define FLASH_TEC1_POSERRCLAMP (0x7A)
#define FLASH_TEC1_NEGERRCLAMP (0x7C)
#define FLASH_TEC1_POSOPCLAMP (0x7E)
#define FLASH_TEC1_NEGOPCLAMP (0x80)
#define FLASH_TEC1_CNFGCURRENTMEA_BURSTGPIOCONFIG (0x82)
#define FLASH_TEC1_OFFSETRIGGER (0x84)
#define FLASH_TEC1_BURSTPWMDUTYOFFSET (0x86)
#define FLASH_TEC1_NORMAL_VCC (0x88)

// -----------------------------------------------------------------------------

#if __NEW_TX_POWER_MON_BY_TEMPERATURE__ == 1

// Tx Power at measured temparature (70, 25, 0), 0.1 uA ����)
#define FLASH_TX_POWER_HTEMP 0x30
#define FLASH_TX_POWER_HTEMP_N(n) (FLASH_TX_POWER_HTEMP + 2 * (n))

#define FLASH_TX_POWER_NORMTEMP 0x32
#define FLASH_TX_POWER_NORMTEMP_N(n) (FLASH_TX_POWER_NORMTEMP + 2 * (n))

#define FLASH_TX_POWER_LTEMP 0x34
#define FLASH_TX_POWER_LTEMP_N(n) (FLASH_TX_POWER_LTEMP + 2 * (n))

#endif

// Page_02h Memory Map
typedef struct
{

} PAGE_02H_MEMORY_MAP;

// Page 82h MAOM-37032A CDR structure

typedef struct
{
        // Page 00h
        unsigned char P00_CHIPID;         // Address 0x80
        unsigned char P00_REVID;          // Address 0x81
        unsigned char P00_RESET;          // Address 0x82
        unsigned char P00_LB_MISCL;       // Address 0x83
        unsigned char P00_RESERVED_1[2];  // Address 0x84, 0x85
        unsigned char P00_LOS_LOL_STATUS; // Address 0x86
        unsigned char P00_RESERVED_2[9];  // Address 0x87 - 0x8F

        unsigned char P00_RX_MODES;         // Address 0x90
        unsigned char P00_RX_PKNG_LOS_THRS; // Address 0x91
        unsigned char P00_RX_RX_SLA;        // Address 0x92
        unsigned char P00_RX_CDRLBW;        // Address 0x93
        unsigned char P00_RX_CDR_MISCL;     // Address 0x94
        unsigned char P00_RX_OP_SWING;      // Address 0x95
        unsigned char P00_RX_OP_DEEMPH;     // Address 0x96

        unsigned char P00_RESERVED_3[9]; // Address 0x97 - 0x9F

        unsigned char P00_TX_MODES;    // Address 0xA0
        unsigned char P00_TX_ADAPT_EQ; // Address 0xA1
        unsigned char P00_TX_LOS_THRS; // Address 0xA2

        unsigned char P00_RESERVED_4[1]; // Address 0xA3

        unsigned char P00_TX_CDRLBW;    // Address 0xA4
        unsigned char P00_TX_CDR_MISCL; // Address 0xA5

        unsigned char P00_TX_OP_SWING;    // Address 0xA6
        unsigned char P00_TX_OP_DEEMPH;   // Address 0xA7
        unsigned char P00_TX_OP_EYESHAPE; // Address 0xA8

        unsigned char P00_GPDAC;          // Address 0xA9
        unsigned char P00_RESERVED_5[1];  // Address 0xAA
        unsigned char P00_RESERVED_6;     // Address 0xAB
        unsigned char P00_RESERVED_7[36]; // Address 0xAC - 0xCF

        unsigned char P00_PRBSGEN;     // Address 0xD0
        unsigned char P00_PRBSGEN_DAC; // Address 0xD1

        unsigned char P00_PRBSCHK_ENBL;  // Address 0xD2
        unsigned char P00_PRBSCHK_BANK;  // Address 0xD3
        unsigned char P00_PRBSCHK_MODE;  // Address 0xD4
        unsigned char P00_PRBSCHK_Eye;   // Address 0xD5
        unsigned char P00_PRBSCHK_DELAY; // Address 0xD6
        unsigned char P00_PRBSCHK_ERR_1; // Address 0xD7
        unsigned char P00_PRBSCHK_ERR_2; // Address 0xD8

        unsigned char P00_RESERVED_8[7]; // Address 0xD9 - 0xDF

        unsigned char P00_ADC_CONFIG_0; // Address 0xE0
        unsigned char P00_ADC_CONFIG_2; // Address 0xE1

        unsigned char P00_RESERVED_9[3]; // Address 0xE2 - 0xE4

        unsigned char P00_ADC_OUT0_MSBS; // Address 0xE5
        unsigned char P00_ADC_OUT0_LSBS; // Address 0xE6

} A2_PAGE_82H_MEMORY_MAP;

#endif // __MEM_MAP_Hd

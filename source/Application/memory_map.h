#ifndef __MEM_MAP_H_
#define __MEM_MAP_H_

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
#define PAGE83H_UPPER 0x0800 // location of 128 byte Page82h : I2C_Slave_Buffer_A2_P83h_Up[128], CDRs
#define PAGE84H_UPPER 0x0880 // location of 128 byte Page82h : I2C_Slave_Buffer_A2_P84h_Up[128], CDRs

/*******    Memory locations for A0, A2 and LUTs in Flash     ********/
#if __HFR_REQ_VER__ == 1

#define FLASH_CH_NO_VENDOR_SPECIFIC 0xEC00 // Flash location for A2 Page 2 144, 145 registers: [DLEE, 20210818, HFR requests]

#endif

#define FLASH_A0_CONST_START 0xEE00       // Flash location for A0 memory:
#define FLASH_A2_LOWER_CONST_START 0xEF00 // Flash location for A2 LOWER Cibf:
// #define FLASH_A0_CONST_START            0x0600                                  //Flash location for A0 memory:
// #define FLASH_A2_LOWER_CONST_START      0x0700                                  //Flash location for A2 LOWER Cibf:
// #define FLASH_A0_CONST_START            0xFE00                                  //Flash location for A0 memory:
// #define FLASH_A2_LOWER_CONST_START      0xFF00                                  //Flash location for A2 LOWER Cibf:
#define FLASH_USER_EERPOM_START 0xF000 // Flash location for User EEPROM, A2 Device Page00, Page01 Upper Memory
#define FLASH_A0_START 0xF200          // Flash location for A0 Device memory: 256 bytes
#define FLASH_A2_START 0xF400          // Flash location for A2 Device memory lower memory: 128 bytes
#define FLASH_PAGE02H_START 0xF600     // Flash location for Page 02h
#define FLASH_PAGE80H_START 0xF800     // Flash location for Page 80h
#define FLASH_PAGE81H_START 0xFA00     // Flash location for Page 81h
#define FLASH_PAGE82H_START 0xFC00     // Flash location for Page 82h

/******************* PAGE80h,81h Module Specific Configuration Memory: 128 + 128 bytes *************/
// Device Address: 0xA2
//-----------------------------------------------------------------------------
// TRX Module Configuration defines
//-----------------------------------------------------------------------------
#define MAX_TRX_SIGNALS 1
#define MAX_CHANNELS_PER_SIGNAL 1

#define MAX_TUNABLE_WAVELENGTHS 4

// Manchester Mode Control Definitions
#define A2_PAGE_81H_MANCHESTER_MODE_ADDR 0x02 // Manchester Mode Control at 0x82
#define MANCHESTER_MODE_DISABLED 0x00         // Manchester output disabled
#define MANCHESTER_MODE_1MIN 0x01             // Manchester output for 1 minute
#define MANCHESTER_MODE_5MIN 0x05             // Manchester output for 5 minutes

typedef unsigned long uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef float FP32;
typedef signed short int16_t;
typedef signed char int8_t;

#ifndef __NEW_TX_POWER_MON_BY_TEMPERATURE__
#define __NEW_TX_POWER_MON_BY_TEMPERATURE__ 0
#endif

typedef struct
{

        /*******    A2 Lower Memory Map: This is the offset location of the registers    ********/
        unsigned int A2_TEMP_HIGH_ALARM;   // Address 0x00
        unsigned int A2_TEMP_LOW_ALARM;    // Address 0x02
        unsigned int A2_TEMP_HIGH_WARNING; // Address 0x04
        unsigned int A2_TEMP_LOW_WARNING;  // Address 0x06
        unsigned int A2_VCC_HIGH_ALARM;    // Address 0x08
        unsigned int A2_VCC_LOW_ALARM;     // Address 0x0A
        unsigned int A2_VCC_HIGH_WARNING;  // Address 0x0C
        unsigned int A2_VCC_LOW_WARNING;   // Address 0x0E

        unsigned int A2_TX_BIAS_HIGH_ALARM;    // Address 0x10
        unsigned int A2_TX_BIAS_LOW_ALARM;     // Address 0x12
        unsigned int A2_TX_BIAS_HIGH_WARNING;  // Address 0x14
        unsigned int A2_TX_BIAS_LOW_WARNING;   // Address 0x16
        unsigned int A2_TX_POWER_HIGH_ALARM;   // Address 0x18
        unsigned int A2_TX_POWER_LOW_ALARM;    // Address 0x1A
        unsigned int A2_TX_POWER_HIGH_WARNING; // Address 0x1C
        unsigned int A2_TX_POWER_LOW_WARNING;  // Address 0x1E

        unsigned int A2_RX_POWER_HIGH_ALARM;     // Address 0x20
        unsigned int A2_RX_POWER_LOW_ALARM;      // Address 0x22
        unsigned int A2_RX_POWER_HIGH_WARNING;   // Address 0x24
        unsigned int A2_RX_POWER_LOW_WARNING;    // Address 0x26
        unsigned int A2_LASER_TEMP_HIGH_ALARM;   // Address 0x28
        unsigned int A2_LASER_TEMP_LOW_ALARM;    // Address 0x2A
        unsigned int A2_LASER_TEMP_HIGH_WARNING; // Address 0x2C
        unsigned int A2_LASER_TEMP_LOW_WARNING;  // Address 0x2E

        unsigned int A2_TECC_HIGH_ALARM;   // Address 0x30
        unsigned int A2_TECC_LOW_ALARM;    // Address 0x32
        unsigned int A2_TECC_HIGH_WARNING; // Address 0x34
        unsigned int A2_TECC_LOW_WARNING;  // Address 0x36

        unsigned int A2_Enhanced_Ctrl_Advs;                     // Address 0x38-0x39 (56-57)
        unsigned int A2_Enhanced_Status_Advs;                   // Address 0x3A-0x3B (58-59)
        unsigned int A2_Enhanced_Signal_Integrity_Ctrl_Advs[3]; // Address 0x3C-0x41 (60-65)

        unsigned char A2_Max_Power_Consumption;         // Address 0x42 (66), Max power consumption of the module, LSB=0.1W
        unsigned char A2_Secondary_Ext_Spec_Compliance; // Address 0x43 (67)

        unsigned char A2_RESERVED_44_46[3]; // Address 0x44-0x46 (68-70), Future Advertisements, Future Status

        unsigned char A2_Enhanced_Controls[4]; // Address 0x47-0x4A (71-74), Enhanced control registers

        unsigned char A2_RESERVED_4B_5E[20]; // Address 0x4B-0x5E (75-94), Reserved
        unsigned char A2_CC_DMI;             // Address 0x5F

        unsigned int A2_TEMPERATURE; // Address 0x60
        unsigned int A2_VCC;         // Address 0x62
        unsigned int A2_TX_BIAS;     // Address 0x64
        unsigned int A2_TX_POWER;    // Address 0x66
        unsigned int A2_RX_POWER;    // Address 0x68
        unsigned int A2_LASER_TEMP;  // Address 0x6A
        unsigned int A2_TEC_CURRENT; // Address 0x6C

        unsigned char A2_STATUS_CONTROL; // Address 0x6E, TX Disable State[7], Soft TX Disable Select[6], RS(1) State [5], Rate_Select State RS(0) [4],
                                         //               Soft Rate_Select Select RS(0) [3], TX Fault State [2], Rx_LOS State [1], Data_Ready_Bar State [0]
        unsigned char A2_RESERVED_6F;    // Address 0x6F

        unsigned char A2_ALARM_WARNING_70;        // Address 0x70, TEMP(0xC0), VCC(0x30), TX_Bias(0x0C), TX_Power(0x03) High, Low Alarm
        unsigned char A2_ALARM_WARNING_71;        // Address 0x71, RX_Power(0xC0), Optional_LD_Temp, Optional_TEC_Currnet High, Low Alarm
        unsigned char A2_TXEQ_72;                 // Address 0x72
        unsigned char A2_RXPREEMP_73;             // Address 0x73
        unsigned char A2_ALARM_WARNING_74;        // Address 0x74, TEMP, VCC, TX_Bias, TX_Power High, Low Warning
        unsigned char A2_ALARM_WARNING_75;        // Address 0x75, RX_Power, Optional_LD_Temp, Optional_TEC_Currnet High, Low Warning
        unsigned char A2_EXTENDED_CONTROL_STATUS; // Address 0x76, Soft RS(1) Select [3], Power Level Operation State [1], Power Level Select [0]
        unsigned char A2_RESERVED_77;             // Address 0x77
        unsigned char A2_READ_CHIP_STATUS;        // Address 0x78
        unsigned char A2_OPERATION_MODE;          // Address 0x79
        unsigned char A2_LUT_MODE;                // Address 0x7A
        unsigned char A2_PASSWORD[4];             // Address 0x7B
        unsigned char A2_TABLE;                   // Address 0x7F

} A2_LOWER_MEMORY_MAP;

#define LOWER_MEMORY_A2_TEMP_HIGH_ALARM 0x00
#define LOWER_MEMORY_A2_TEMP_LOW_ALARM 0x02
#define LOWER_MEMORY_A2_TEMP_HIGH_WARNING 0x04
#define LOWER_MEMORY_A2_TEMP_LOW_WARNING 0x06
#define LOWER_MEMORY_A2_VCC_HIGH_ALARM 0x08
#define LOWER_MEMORY_A2_VCC_LOW_ALARM 0x0A
#define LOWER_MEMORY_A2_VCC_HIGH_WARNING 0x0C
#define LOWER_MEMORY_A2_VCC_LOW_WARNING 0x0E

#define LOWER_MEMORY_A2_TX_BIAS_HIGH_ALARM 0x10
#define LOWER_MEMORY_A2_TX_BIAS_LOW_ALARM 0x12
#define LOWER_MEMORY_A2_TX_BIAS_HIGH_WARNING 0x14
#define LOWER_MEMORY_A2_TX_BIAS_LOW_WARNING 0x16
#define LOWER_MEMORY_A2_TX_POWER_HIGH_ALARM 0x18
#define LOWER_MEMORY_A2_TX_POWER_LOW_ALARM 0x1A
#define LOWER_MEMORY_A2_TX_POWER_HIGH_WARNING 0x1C
#define LOWER_MEMORY_A2_TX_POWER_LOW_WARNING 0x1E

#define LOWER_MEMORY_A2_RX_POWER_HIGH_ALARM 0x20
#define LOWER_MEMORY_A2_RX_POWER_LOW_ALARM 0x22
#define LOWER_MEMORY_A2_RX_POWER_HIGH_WARNING 0x24
#define LOWER_MEMORY_A2_RX_POWER_LOW_WARNING 0x26
#define LOWER_MEMORY_A2_LASER_TEMP_HIGH_ALARM 0x28
#define LOWER_MEMORY_A2_LASER_TEMP_LOW_ALARM 0x2A
#define LOWER_MEMORY_A2_LASER_TEMP_HIGH_WARNING 0x2C
#define LOWER_MEMORY_A2_LASER_TEMP_LOW_WARNING 0x2E

#define LOWER_MEMORY_A2_TECC_HIGH_ALARM 0x30
#define LOWER_MEMORY_A2_TECC_LOW_ALARM 0x32
#define LOWER_MEMORY_A2_TECC_HIGH_WARNING 0x34
#define LOWER_MEMORY_A2_TECC_LOW_WARNING 0x36

#define LOWER_MEMORY_A2_RX_PWR_4 0x38
#define LOWER_MEMORY_A2_RX_PWR_3 0x3C
#define LOWER_MEMORY_A2_RX_PWR_2 0x40
#define LOWER_MEMORY_A2_RX_PWR_1 0x44
#define LOWER_MEMORY_A2_RX_PWR_0 0x48

#define LOWER_MEMORY_A2_TX_I_Slope 0x4C
#define LOWER_MEMORY_A2_TX_I_Offset 0x4E

#define LOWER_MEMORY_A2_TX_PWR_Slope 0x50
#define LOWER_MEMORY_A2_TX_PWR_Offset 0x52

#define LOWER_MEMORY_A2_Temp_Slope 0x54
#define LOWER_MEMORY_A2_Temp_Offset 0x56

#define LOWER_MEMORY_A2_VCC_Slope 0x58
#define LOWER_MEMORY_A2_VCC_Offset 0x5A

#define LOWER_MEMORY_A2_RESERVED_5C_5E 0x5C
#define LOWER_MEMORY_A2_CC_DMI 0x5F

#if __ADDITIONAL_ENHANCED_FEATURES_ENABLE__ == 1
#define LOWER_MEMORY_A2_MAX_POWER_CONSUMPTION 0x42
#endif

#define LOWER_MEMORY_A2_TEMPERATURE 0x60
#define LOWER_MEMORY_A2_VCC 0x62
#define LOWER_MEMORY_A2_TX_BIAS 0x64
#define LOWER_MEMORY_A2_TX_POWER 0x66
#define LOWER_MEMORY_A2_RX_POWER 0x68
#define LOWER_MEMORY_A2_LASER_TEMP 0x6A
#define LOWER_MEMORY_A2_TEC_CURRENT 0x6C

#define LOWER_MEMORY_A2_STATUS_CONTROL 0x6E
#define LOWER_MEMORY_A2_RESERVED_6F 0x6F

#define LOWER_MEMORY_A2_ALARM_WARNING_70 0x70
#define LOWER_MEMORY_A2_ALARM_WARNING_71 0x71
#define LOWER_MEMORY_A2_TXEQ_72 0x72
#define LOWER_MEMORY_A2_RXPREEMP_73 0x73
#define LOWER_MEMORY_A2_ALARM_WARNING_74 0x74
#define LOWER_MEMORY_A2_ALARM_WARNING_75 0x75
#define LOWER_MEMORY_A2_EXTENDED_CONTROL_STATUS 0x76
#define LOWER_MEMORY_A2_RESERVED_77 0x77
#define LOWER_MEMORY_A2_READ_CHIP_STATUS 0x78
#define LOWER_MEMORY_A2_OPERATION_MODE 0x79
#define LOWER_MEMORY_A2_LUT_MODE 0x7A
#define LOWER_MEMORY_A2_PASSWORD 0x7B
#define LOWER_MEMORY_A2_TABLE 0x7F

typedef struct
{
        uint16_t flash_reset_flag; // addr = 0, size = 2
        uint16_t module_state;     // addr = 2, size = 2
        uint8_t command;           // addr = 4, size = 1,
                                   // B[7:4] = command, if [3:2]=00, 0010b, 0100b, 1000b: Write I2C, 0011b, 0101b, 1001b: Read I2C,
                                   //                   if [3:2]= 01b(restore), 10b(save) [7:4]: save or restore page no, 0h, 1h, 2h, 3h, 9h(A4 device address)
                                   // [3:2] = extended_command(01b: Restore, 10b: NVR Save, 00b: Internal I2C Operation,
                                   // [1:0] = cmd_status: 00b: IDLE, 01b: Command completed successfully, 10b: Command in progress, 11b: Command failed
        uint8_t page;              // addr = 5, size = 1
        uint8_t addr;              // addr = 6, size = 1
        uint8_t data_length;       // addr = 7, size = 1
        uint8_t w_data[4];         // addr = 8, size = 4
        uint8_t r_data[4];         // addr = 0x0C, size = 4

        uint8_t LdControlMode;    // addr = 0x10, size = 1
        uint8_t rate_select;      // addr = 0x11, size = 1, 0x88: 25G, 0x80: Bypass(10G), 0x00 -> 10G(Set), 0x08: (25G Rx, Bypass Tx)
        uint16_t ModBiasSet;      // addr = 0x12, size = 2
        uint16_t XconBiasSet;     // addr = 0x14, size = 2
        uint16_t forcedLdBiasSet; // addr = 0x16, size = 2

        unsigned int nt_ModBiasSet[MAX_TUNABLE_WAVELENGTHS];  // Address 0x18-0x1F
        unsigned int nt_XconBiasSet[MAX_TUNABLE_WAVELENGTHS]; // Address 0x20-0x27
        unsigned int nt_LdBiasSet[MAX_TUNABLE_WAVELENGTHS];   // Address 0x28-0x2F

        unsigned int ht_ModBiasSet[MAX_TUNABLE_WAVELENGTHS];  // Address 0x30-0x37
        unsigned int ht_XconBiasSet[MAX_TUNABLE_WAVELENGTHS]; // Address 0x38-0x3F
        unsigned int ht_LdBiasSet[MAX_TUNABLE_WAVELENGTHS];   // Address 0x40-0x47

        unsigned int lt_ModBiasSet[MAX_TUNABLE_WAVELENGTHS];  // Address 0x48-0x4F
        unsigned int lt_XconBiasSet[MAX_TUNABLE_WAVELENGTHS]; // Address 0x50-0x57
        unsigned int lt_LdBiasSet[MAX_TUNABLE_WAVELENGTHS];   // Address 0x58-0x5F

        signed int nt_temp; // Address 0x60
        signed int ht_temp; // Address 0x62
        signed int lt_temp; // Address 0x64

        unsigned int vapd_dac; // VAPD DAC value: 0x66

        uint16_t VCC_Slope;    // Address 0x68-0x69
        uint16_t VCC_Offset;   // Address 0x6A-0x6B
        uint16_t ITEMP_Slope;  // Address 0x6C-0x6D
        uint16_t ITEMP_Offset; // Address 0x6E-0x6F

        uint16_t ADC_VCC;     // Address 0x70
        uint16_t rawCurrTemp; // Address 0x72

        unsigned char curr_los_flag; // Address 0x74
        unsigned char prev_los_flag; // Address 0x75

        unsigned int mpd_adc;          // ADC mpd0: 0x76
        unsigned int rssi_adc;         // ADC rssi0: 0x78
        unsigned int APD_ADC;          // APD_ADC value: 0x7A
        unsigned int vapd_dac_readout; // VAPD_DAC value readout: 0x7C
        unsigned int dac_gpdac;        // readout dac value: 0x7E
} A2_PAGE_80H_MEMORY_MAP;

typedef struct
{
        unsigned char DEVICE_CONFIG;           // Address 0x00, 0x80
        unsigned char PMIC_SELECT;             // Address 0x01, 0x81
        unsigned char MANCHESTER_MODE_CONTROL; // Address 0x02, 0x82 - Manchester Mode Control (0=disabled, 1=1min, 5=5min)
        unsigned char RESERVED_83;             // Address 0x03, 0x83

        unsigned int RESERVED_84_91[7]; // Address 0x04-0x11, 0x84-0x91

        unsigned int APD_TARGET_OUTPUT;   // Address 0x12, 0x92
        unsigned int APD_CONFIG;          // Address 0x14, 0x94
        unsigned int APD_CURRENT_SETTING; // Address 0x16, 0x96

        unsigned int APD_ADC_RAW;                    // Address 0x18, 0x98
        unsigned int APD_Vbr;                        // Address 0x1A, 0x9A
        unsigned char APD_VBR_DIFF;                  // Address 0x1C, 0x9C, TruLight =2, MACOM = 3
        unsigned char A2_PAGE_81H_RESERVED_1A_1D[1]; // Address 0x1D, 0x9D

        unsigned int V_THM; // Address 0x1E, 0x9E

        unsigned int TEC1_SETPOINT;                       // Address 0x20, 0xA0
        unsigned int TEC1_KP;                             // Address 0x22, 0xA2
        unsigned int TEC1_KI;                             // Address 0x24, 0xA4
        unsigned int TEC1_KD;                             // Address 0x26, 0xA6
        unsigned int TEC1_SHIFT;                          // Address 0x28, 0xA8
        unsigned int TEC1_POSERRCLAMP;                    // Address 0x2A, 0xAA
        unsigned int TEC1_NEGERRCLAMP;                    // Address 0x2C, 0xAC
        unsigned int TEC1_POSOPCLAMP;                     // Address 0x2E, 0xAE
        unsigned int TEC1_NEGOPCLAMP;                     // Address 0x30, 0xB0
        unsigned int TEC1_CNFGCURRENTMEA_BURSTGPIOCONFIG; // Address 0x32, 0xB2
        unsigned int TEC1_OFFSETRIGGER;                   // Address 0x34, 0xB4
        unsigned int TEC1_BURSTPWMDUTYOFFSET;             // Address 0x36, 0xB6
        unsigned int TEC1_NORMAL_VCC;                     // Address 0x38, 0xB8
        unsigned int TEC1_DUTY_CYCLE;                     // Address 0x3A, 0xBA
        unsigned int TEC1_I_MEAS;                         // Address 0x3C, 0xBC

        unsigned int IDAC_CONFIG; // addr = 0x3E, 0xBE

        FP32 txPower_coeff_0; // addr = 0x40 ~ 0x43, size = 4, 0xC0 ~ 0xC3
        FP32 txPower_coeff_1; // addr = 0x44 ~ 0x47, size = 4, 0xC4 ~ 0xC7

        unsigned int nt_tec_setpoint_per_wavelength[MAX_TUNABLE_WAVELENGTHS]; // 0x48 ~ 0x4F, 0xC8 ~ 0xCF
        unsigned int ht_tec_setpoint_per_wavelength[MAX_TUNABLE_WAVELENGTHS]; // 0x50 ~ 0x57, 0xD0 ~ 0xD7
        unsigned int lt_tec_setpoint_per_wavelength[MAX_TUNABLE_WAVELENGTHS]; // 0x58 ~ 0x5F, 0xD8 ~ 0xDF

        FP32 rxPower_coeff_0; // addr = 0x60, size = 4, 0xE0
        FP32 rxPower_coeff_1; // addr = 0x64, size = 4, 0xE4
        FP32 rxPower_coeff_2; // addr = 0x68, size = 4, 0xE8
        FP32 rxPower_coeff_3; // addr = 0x6C, size = 4, 0xEC
        FP32 rxPower_coeff_4; // addr = 0x70, size = 4, 0xF0

        unsigned int idcn; // IDCN1: 0x74, --> 0xF4  --> LOS ASSERT
        unsigned int idcd; // IDCD1: 0x76, --> 0xF6  --> LOS DeAssert

        unsigned int tec_setpoint_per_wavelength[MAX_TUNABLE_WAVELENGTHS]; // 0x78 ~ 0x7F, 0xF8 ~ 0xFF
} A2_PAGE_81H_MEMORY_MAP;

typedef union
{
        uint8_t c_data[4];
        uint16_t u2_data[2];
        unsigned long u_data;
        float fp;
} IEEE_754_FP_Type;

// ---------------------------------------------------------
// A2_PAGE_80H_MEMORY_MAP
// ---------------------------------------------------------

// Flash Memory �Ҵ� ������ ����
#define FLASH_MEMORY_BASE 0x00

#define FLASH_RESET_FLAG_REG (0x00)
#define FLASH_MODULE_STATE (0x02)
#define FLASH_COMMAND (0x04)
#define FLASH_PAGE (0x05)
#define FLASH_ADDR (0x06)
#define FLASH_DATA_LENGTH (0x07)
#define FLASH_W_DATA(n) ((0x08) + (((n) - 1) * 0x01))
#define FLASH_R_DATA(n) ((0x0C) + (((n) - 1) * 0x01))

#define FLASH_LD_CONTROL_MODE (0x10)
#define FLASH_LD_CONTROL_MODE_n(n) ((0x10) + (((n) - 1) * 0x01))
#define FLASH_LD_CONTROL_MODE_1(n) ((0x11) + (((n) - 1) * 0x01))

#define FLASH_MOD_BIAS_SET (0x12)
#define FLASH_XCON_BIAS_SET (0x14)
#define FLASH_FORCED_LD_BIAS_SET (0x16)

#define FLASH_MOD_BIAS_SET_N(n) ((0x12) + (((n) - 1) * 0x02))
#define FLASH_XCON_BIAS_SET_N(n) ((0x14) + (((n) - 1) * 0x02))
#define FLASH_FORCED_LD_BIAS_SET_N(n) ((0x16) + (((n) - 1) * 0x02))

#define FLASH_NT_MOD_BIAS_SET (0x18)
#define FLASH_NT_MOD_BIAS_SET_N(n) ((FLASH_NT_MOD_BIAS_SET) + (((n) - 1) * 0x02))

#define FLASH_NT_XCON_BIAS_SET (0x20)
#define FLASH_NT_XCON_BIAS_SET_N(n) ((FLASH_NT_XCON_BIAS_SET) + (((n) - 1) * 0x02))

#define FLASH_NT_FORCED_LD_BIAS_SET (0x28)
#define FLASH_NT_FORCED_LD_BIAS_SET_N(n) ((FLASH_NT_FORCED_LD_BIAS_SET) + (((n) - 1) * 0x02))

#define FLASH_HT_MOD_BIAS_SET (0x30)
#define FLASH_HT_MOD_BIAS_SET_N(n) ((FLASH_HT_MOD_BIAS_SET) + (((n) - 1) * 0x02))

#define FLASH_HT_XCON_BIAS_SET (0x38)
#define FLASH_HT_XCON_BIAS_SET_N(n) ((FLASH_HT_XCON_BIAS_SET) + (((n) - 1) * 0x02))

#define FLASH_HT_FORCED_LD_BIAS_SET (0x40)
#define FLASH_HT_FORCED_LD_BIAS_SET_N(n) ((FLASH_HT_FORCED_LD_BIAS_SET) + (((n) - 1) * 0x02))

#define FLASH_LT_MOD_BIAS_SET (0x48)
#define FLASH_LT_MOD_BIAS_SET_N(n) ((FLASH_LT_MOD_BIAS_SET) + (((n) - 1) * 0x02))

#define FLASH_LT_XCON_BIAS_SET (0x50)
#define FLASH_LT_XCON_BIAS_SET_N(n) ((FLASH_LT_XCON_BIAS_SET) + (((n) - 1) * 0x02))

#define FLASH_LT_FORCED_LD_BIAS_SET (0x58)
#define FLASH_LT_FORCED_LD_BIAS_SET_N(n) ((FLASH_LT_FORCED_LD_BIAS_SET) + (((n) - 1) * 0x02))

#define FLASH_NT_TEMP (0x60)
#define FLASH_HT_TEMP (0x62)
#define FLASH_LT_TEMP (0x64)

#define FLASH_VAPD_DAC (0x66)

#define FLASH_VCC_SLOPE (0x68)
#define FLASH_VCC_OFFSET (0x6A)
#define FLASH_ITEMP_SLOPE (0x6C)
#define FLASH_ITEMP_OFFSET (0x6E)

#define FLASH_ADC_VCC (0x70)
#define FLASH_ADC_INTERNAL_TEMP (0x72)

#define FLASH_DAC_READOUT (0x74)
#define FLASH_MPD_ADC_READOUT (0x76)
#define FLASH_RSSI_ADC_READOUT (0x78)

#define FLASH_APD_ADC_READOUT (0x7A)

#define FLASH_VAPD_DAC_READOUT (0x7C)
#define FLASH_DAC_GPDAC_READOUT (0x7E)
#define FLASH_VAPD_DAC_SET (0x66)

#define FLASH_RAW_CURRENT_TEMP (0x72)

#define RAW_HIGH_TEMP_CT_VALUE 0x4600
#define RAW_ROOM_TEMP_CT_VALUE 0x1900
#define RAW_LOW_TEMP_CT_VALUE 0x0000

#define RAW_HIGH_TEMP_IT_VALUE 0x5500
#define RAW_ROOM_TEMP_IT_VALUE 0x1900
#define RAW_LOW_TEMP_IT_VALUE 0xEC00 // -20

// ---------------------------------------------------------
// A2_PAGE_81H_MEMORY_MAP
// ---------------------------------------------------------

// Redefined address
#define FLASH_DEVICE_CONFIG (0x00)
#define FLASH_PMIC_SELECT (0x01)

// APD Configuration Registers
#define FLASH_APD_ERRSTARTCLAMP (0x02)
#define FLASH_APD_DUTYCLAMP (0x04)
#define FLASH_APD_INTEGRALGAIN (0x06)
#define FLASH_APD_DUTYSTARTINCCLAMP (0x08)
#define FLASH_APD_INTEGRALCLAMP (0x0A)
#define FLASH_APD_APDNEGERRCLAMP (0x0C)
#define FLASH_APD_APDPOSERRCLAMP (0x0E)
#define FLASH_APD_PROPORTIONALGAIN (0x10)

#define FLASH_APD_TARGET_OUTPUT (0x12)
#define FLASH_APD_CONFIG (0x14)
#define FLASH_APD_CURRENT_SETTING (0x16)

#define FLASH_APD_ADC (0x18)

#define FLASH_APD_Vbr (0x1A)
#define FLASH_APD_VBR_DIFF (0x1C)

#define FLASH_V_THM (0x1E)

// TEC Configuration Registers
#define FLASH_TEC1_SETPOINT (0x20)
#define FLASH_TEC1_KP (0x22)
#define FLASH_TEC1_KI (0x24)
#define FLASH_TEC1_KD (0x26)
#define FLASH_TEC1_SHIFT (0x28)
#define FLASH_TEC1_POSERRCLAMP (0x2A)
#define FLASH_TEC1_NEGERRCLAMP (0x2C)
#define FLASH_TEC1_POSOPCLAMP (0x2E)
#define FLASH_TEC1_NEGOPCLAMP (0x30)
#define FLASH_TEC1_CNFGCURRENTMEA_BURSTGPIOCONFIG (0x32)
#define FLASH_TEC1_OFFSETRIGGER (0x34)
#define FLASH_TEC1_BURSTPWMDUTYOFFSET (0x36)
#define FLASH_TEC1_NORMAL_VCC (0x38)
#define FLASH_TEC1_DUTY_CYCLE (0x3A)
#define FLASH_TEC1_I_MEAS (0x3C)

#define FLASH_IDAC_CONFIG (0x3E)

#define FLASH_TX_POWER_AT_HT (0x40)
#define FLASH_TX_POWER_AT_HT_N(n) ((FLASH_TX_POWER_AT_HT) + (((n) - 1) * 0x02))

#define FLASH_TX_POWER_AT_NT (0x48)
#define FLASH_TX_POWER_AT_NT_N(n) ((FLASH_TX_POWER_AT_NT) + (((n) - 1) * 0x02))

#define FLASH_TX_POWER_AT_LT (0x50)
#define FLASH_TX_POWER_AT_LT_N(n) ((FLASH_TX_POWER_AT_LT) + (((n) - 1) * 0x02))

#define FLASH_TX_POWER_AT_DDM_OFFSET (0x58)
#define FLASH_TX_POWER_AT_DDM_OFFSET_N(n) ((FLASH_TX_POWER_AT_DDM_OFFSET) + (((n) - 1) * 0x02))

#define FLASH_TX_POWER_COEFF_0 (0x40)
#define FLASH_TX_POWER_COEFF_0_N(n) ((FLASH_TX_POWER_COEFF_0) + (((n) - 1) * 0x04))

#define FLASH_TX_POWER_COEFF_1 (0x44)
#define FLASH_TX_POWER_COEFF_1_N(n) ((FLASH_TX_POWER_COEFF_1) + (((n) - 1) * 0x04))

#define FLASH_NT_TEC_SETPOINT_PER_WAVELENGTH (0x48)
#define FLASH_NT_TEC_SETPOINT_PER_WAVELENGTH_N(n) ((FLASH_NT_TEC_SETPOINT_PER_WAVELENGTH) + (((n) - 1) * 0x02))

#define FLASH_HT_TEC_SETPOINT_PER_WAVELENGTH (0x50)
#define FLASH_HT_TEC_SETPOINT_PER_WAVELENGTH_N(n) ((FLASH_HT_TEC_SETPOINT_PER_WAVELENGTH) + (((n) - 1) * 0x02))

#define FLASH_LT_TEC_SETPOINT_PER_WAVELENGTH (0x58)
#define FLASH_LT_TEC_SETPOINT_PER_WAVELENGTH_N(n) ((FLASH_LT_TEC_SETPOINT_PER_WAVELENGTH) + (((n) - 1) * 0x02))

#define FLASH_RX_POWER_COEFF_0 (0x60)
#define FLASH_RX_POWER_COEFF_1 (0x64)
#define FLASH_RX_POWER_COEFF_2 (0x68)
#define FLASH_RX_POWER_COEFF_3 (0x6C)
#define FLASH_RX_POWER_COEFF_4 (0x70)

#define FLASH_IDCN_READOUT (0x74)
#define FLASH_IDCD_READOUT (0x76)

#define FLASH_CDR_LD_DRV_CTRL5_REG (0x74)
#define FLASH_CDR_LD_DRV_CTRL5_REG_N(n) ((FLASH_CDR_LD_DRV_CTRL5_REG) + (((n) - 1)))

#define FLASH_TEC_SETPOINT_PER_WAVELENGTH (0x78)
#define FLASH_TEC_SETPOINT_PER_WAVELENGTH_N(n) ((FLASH_TEC_SETPOINT_PER_WAVELENGTH) + (((n) - 1) * 0x02))

// Page_02h Memory Map
typedef struct
{

        unsigned char Dithering;                     // Address 0x00, 0x80
        unsigned char A2_PAGE_02H_RESERVED_81_83[3]; // Address 0x01, 0x81

        unsigned int LFL1; // Address 0x04, 0x84, Lasers First Frequency (THz)
        unsigned int LFL2; // Address 0x06, 0x86, Lasers First Frequency (GHz*10), in units of 0.1 GHz
        unsigned int LFH1; // Address 0x08, 0x88, Lasers Last Frequency (THz)
        unsigned int LFH2; // Address 0x0A, 0x8A, Lasers Last Frequency (GHz*10), in units of 0.1 GHz

        signed int LGrid; // Address 0x0C, 0x8C, Laser��s minimum supported grid spacing (GHz*10), i.e., in units of 0.1 GHz
                          //  NOTE: LGrid can be a positive ornegative number.

        unsigned char A2_PAGE_02H_RESERVED_8E_8F[2]; // Address 0x0E, 0x8E

        unsigned int Channel_Number_Set; // Address 0x10, 0x90, User input of wavelength channel # integer 1 to N (N=Number of channels)
        unsigned int Wavelength_Set;     // Address 0x12, 0x92, User input of Wavelength setpoint. (Units of 0.05 nm)

        unsigned char A2_PAGE_02H_RESERVED_94_96[3]; // Address 0x14, 0x94

        unsigned char Tx_Dither; // Address 0x17, 0x97, Logic 1 disables Dither, 0 enables Dither.

        unsigned int Frequency_Error;  // Address 0x18, 0x98, Frequency error reported in 16 bit signed integer with LSB=0.1 GHz
        unsigned int Wavelength_Error; // Address 0x1A, 0x9A, Wavelength error reported in 16 bit signed integer with LSB=0.005 nm

        unsigned char A2_PAGE_02H_RESERVED_9C_A7[12]; // Address 0x1C, 0x9C

        unsigned char Current_Status; // Address 0x28, 0xA8, A2h byte 168 is the current status register
                                      //  containing unlatched status bits for TEC
                                      //  Fault, Wavelength Unlock, and TxTune
                                      //  (i.e., tuning operation is in process and is not yet completed).

        unsigned char A2_PAGE_02H_RESERVED_AA_AB[3]; // Address 0x29 ~ 0x2B, 0xAA

        unsigned char Latched_Status; // Address 0x2C, 0xAC, A2h byte 172 is the latched status register. The latched indicators for TEC Fault
                                      //  and Wavelength Unlock are located here. Bit 4, Bad Channel, indicates a bad channel
                                      //  number request (i.e., a channel number outside of the supported range). Bit 3, New
                                      //  Channel, indicates that a channel change operation has completed. Bit 2 indicates
                                      //  that Tx Dither has been requested in a module that does not support dithering.

} PAGE_02H_MEMORY_MAP;

// 1 ~ 4 (�� ���� Wavelength�� ���� ����� ä�� ��ȣ): SFF-8690 ����
#define P02H_CHANNEL_NUMBER_SET 0x10

// Channel number = 1 + (Desired Frequency - First Frequency) / Grid Spacing
#define P02H_WAVELENGTH_SET 0x12

#define P02H_CURR_STAT_DEBUG 0x30

// A0H Memory Map Definitions
#define A0H_SERIAL_ID_VENDOR_NAME 0x14
#define A0H_SERIAL_ID_VENDOR_OUI 0x25
#define A0H_SERIAL_ID_VENDOR_PN 0x28
#define A0H_SERIAL_ID_VENDOR_REV 0x38

#define A0H_SERIAL_ID_WAVELENGTH 0x3C
#define A0H_SERIAL_ID_WAVELENGTH_FRACTION 0x3E

#define A0H_SERIAL_ID_CC_BASE 0x3F

#define A0H_SERIAL_ID_OPT_VALUE_64 0x40
#define A0H_SERIAL_ID_OPT_VALUE_65 0x41

#define A0H_SERIAL_ID_VENDOR_SN 0x44

#define A0H_SERIAL_ID_DATE_CODE 0x32

#define A0H_SERIAL_ID_CC_EXT 0x5F

// GN1157 LD Driver structure:
//    TX/RX Channel Control Registers: I2C Address (0xA8 )
// Page 82h    Register Address: 0x00 ~ 0x7F

typedef struct
{
        // Page 82h
        unsigned char P00_DIG_CORE_ID;    // Address 0x00, Unique identifier of digital core
        unsigned char P00_ID;             // Address 0x01, Device identification
        unsigned char P00_SR1;            // Address 0x02, Status Register 1
        unsigned char P00_SR2;            // Address 0x03, Status Register 2
        unsigned char P00_APC_COUNTER[2]; // Address 0x04, 5

        unsigned char P00_ADC_4[2];  // Address 0x06 - 0x07
        unsigned char P00_ADC_5[2];  // Address 0x08 ~ 0x09
        unsigned char P00_ADC_6[2];  // Address 0x0A ~ 0x0B
        unsigned char P00_ADC_7[2];  // Address 0x0C ~ 0x0D
        unsigned char P00_ADC_8[2];  // Address 0x0E ~ 0x0F
        unsigned char P00_ADC_9[2];  // Address 0x10 ~ 0x11
        unsigned char P00_ADC_10[2]; // Address 0x12 - 0x13

        unsigned char P00_RESERVED_1[4];  // Address 0x14 ~ 0x17
        unsigned char P00_VCPA_DAC;       // Address 0x18
        unsigned char P00_VEQ_DAC;        // Address 0x19
        unsigned char P00_BIAS_TCA_DAC;   // Address 0x1A
        unsigned char P00_MON_TCA_DAC;    // Address 0x1B
        unsigned char P00_VF_TCA_DAC;     // Address 0x1C
        unsigned char P00_MOD_SET_DAC[2]; // Address 0x1D ~ 0x1E

        unsigned char P00_BIAS_SET_DAC[2]; // Address 0x1F - 0x20

        unsigned char P00_VSET_DAC; // Address 0x21 ~ 0x22

        unsigned char P00_RESERVED_2[2]; // Address 0x23 ~ 0x24

        unsigned char P00_RX_RATE_SELECT[2]; // Address 0x25 ~ 0x26

        unsigned char P00_RESERVED_3[2]; // Address 0x27 ~ 0x28

        unsigned char P00_ADC_1; // Address 0x29, ADC clock rate, bit length and VCC select, 0x1E
        unsigned char P00_ADC_2; // Address 0x2A, ADC MUX, 0x00
        unsigned char P00_ADC_3; // Address 0x2B, ADC start/done/cycle, 0x03

        unsigned char P00_DIGITAL_VCO;              // Address 0x2C, Digital block VCO configuration, 0x02
        unsigned char P00_EXT_RX_PWR_LOS_CONTROL;   // Address 0x2D, Control for external Rx power LOS
        unsigned char P00_EXT_RX_PWR_LOS_THRESHOLD; // Address 0x2E, Sets the threshold for external Rx power LOS

        unsigned char P00_RESERVED_4[1]; // Address 0x2F

        unsigned char P00_LOS_VBE_DAC;   // Address 0x30
        unsigned char P00_LOS_VT_DAC;    // Address 0x31
        unsigned char P00_RX_CONTROL_1;  // Address 0x32
        unsigned char P00_RX_CONTROL_2;  // Address 0x33
        unsigned char P00_RESERVED_5[3]; // Address 0x34 ~ 0x36

        unsigned char P00_LDD_EYE_OPTIMIZE; // Address 0x37
        unsigned char P00_TX_RATE_SELECT;   // Address 0x38
        unsigned char P00_ISNK_MAX;         // Address 0x39
        unsigned char P00_APC_WINDOW;       // Address 0x3A
        unsigned char P00_APC_MODE;         // Address 0x3B
        unsigned char P00_RESERVED_6[1];    // Address 0x3C

        unsigned char P00_CR2; // Address 0x3D, Control Register 2, 0x1E
        unsigned char P00_CR1; // Address 0x3E, Control Register 1, 0xD1

        unsigned char P00_RESERVED_7[0x41]; // Address 0x3F ~ 0x7F

} A2_PAGE_82H_MEMORY_MAP;

// GN1157 --> Register Address Definitions
// Page 82h
#define P00_DIG_CORE_ID 0x00
#define P00_ID 0x01
#define P00_SR1 0x02
#define P00_SR2 0x03
#define P00_APC_COUNTER 0x04
#define P00_APC_COUNTER_MSB 0x04
#define P00_APC_COUNTER_LSB 0x05

#define P00_ADC_4 0x06
#define P00_ADC_4_MSB 0x06
#define P00_ADC_4_LSB 0x07

#define P00_ADC_5 0x08
#define P00_ADC_5_MSB 0x08
#define P00_ADC_5_LSB 0x09

#define P00_ADC_6 0x0A
#define P00_ADC_6_MSB 0x0A
#define P00_ADC_6_LSB 0x0B

#define P00_ADC_7 0x0C
#define P00_ADC_7_MSB 0x0C
#define P00_ADC_7_LSB 0x0D

#define P00_ADC_8 0x0E
#define P00_ADC_8_MSB 0x0E
#define P00_ADC_8_LSB 0x0F

#define P00_ADC_9 0x10
#define P00_ADC_9_MSB 0x10
#define P00_ADC_9_LSB 0x11

#define P00_ADC_10 0x12
#define P00_ADC_10_MSB 0x12
#define P00_ADC_10_LSB 0x13

#define P00_RSVD_1 0x14

#define P00_VCPA_DAC 0x18
#define P00_VEQ_DAC 0x19
#define P00_BIAS_TCA_DAC 0x1A
#define P00_MON_TCA_DAC 0x1B
#define P00_VF_TCA_DAC 0x1C
#define P00_MOD_SET_DAC 0x1D
#define P00_MOD_SET_DAC_MSB 0x1D
#define P00_MOD_SET_DAC_LSB 0x1E

#define P00_BIAS_SET_DAC 0x1F
#define P00_BIAS_SET_DAC_MSB 0x1F
#define P00_BIAS_SET_DAC_LSB 0x20

#define P00_VSET_DAC 0x21
#define P00_VSET_DAC_MSB 0x21
#define P00_VSET_DAC_LSB 0x22

#define P00_RSVD_6 0x24

#define P00_RX_RATE_SELECT 0x25
#define P00_RX_RATE_SELECT_MSB 0x25
#define P00_RX_RATE_SELECT_LSB 0x26

#define P00_RSVD_8 0x28

#define P00_ADC_1 0x29
#define P00_ADC_2 0x2A
#define P00_ADC_3 0x2B

#define P00_DIGITAL_VCO 0x2C
#define P00_EXT_RX_PWR_LOS_CONTROL 0x2D
#define P00_EXT_RX_PWR_LOS_THRESHOLD 0x2E

#define P00_LOS_VBE_DAC 0x30
#define P00_LOS_VT_DAC 0x31
#define P00_RX_CONTROL_1 0x32
#define P00_RX_CONTROL_2 0x33

#define P00_RSVD_12 0x36

#define P00_LDD_EYE_OPTIMIZE 0x37
#define P00_TX_RATE_SELECT 0x38
#define P00_ISNK_MAX 0x39
#define P00_APC_WINDOW 0x3A
#define P00_APC_MODE 0x3B

#define P00_RSVD_13 0x3C

#define P00_CR2 0x3D
#define P00_CR1 0x3E

// GN1157 <--

#endif // __MEM_MAP_Hd

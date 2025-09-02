#ifndef INC_MODULE_CONFIG_H_
#define INC_MODULE_CONFIG_H_

typedef unsigned char INT8U;
typedef unsigned short INT16U;
typedef unsigned long INT32U;


#define  SLAVE_ADDR_A0               0xA0 // Device addresses (7 bits,
#define  SLAVE_ADDR_A2               0xA2 // Device addresses (7 bits,  --> Using Vendor Specific for mass production

// --------------------------------
// SMBUS_Specific Memory map
// --------------------------------

#define LOWER_PAGE_ADDR 128

#define A2_LOW_PAGE 0x00
////#define A0_UPPER_PAGE 0x00
////#define A2_LOW_PAGE 0x01
#define A2_UPPER_PAGE0 0x00
#define A2_UPPER_PAGE1 0x01
#define A2_UPPER_PAGE2 0x02
#define A2_UPPER_PAGE_80H 0x80
#define A2_UPPER_PAGE_81H 0x81
#define A2_UPPER_PAGE_82H 0x82

// I2C Addresses
#define I2C_ADDR_A0	0xA0
#define I2C_ADDR_A2	0xA2

//module start page
#define MODULE_START_PAGE 0x04;

#define MAX_WRITE_LIST_ENTRY	128

#define xdata 

// CDRs

#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1

#define TX_RX_COMBO_CDR_I2C_ADDR	0xA8
#define TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR	0xA8
#define TX_RX_COMBO_CDR_PMIC_I2C_ADDR	0xA8

#else

// TX&RX Combo CDR MAOM_37032A
//#define TX_RX_COMBO_CDR_I2C_ADDR	0x98
//#define TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR	0x98
//#define TX_RX_COMBO_CDR_PMIC_I2C_ADDR	0x9E

#define TX_RX_COMBO_CDR_I2C_ADDR	0xA8
#define TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR	0xA8
#define TX_RX_COMBO_CDR_PMIC_I2C_ADDR	0xA8

#endif


//-----------------------------------------------------------------------------
// Global VARIABLES
//-----------------------------------------------------------------------------
// Global holder for SMBus data.
// All receive data is written here
// NUM_BYTES_WR used because an SMBus write is Master->Slave
#ifdef __DECLARE_VARS__

#define EXTERN_SMBUS_S
#define _EXTERN_C_
#else

#define EXTERN_SMBUS_S extern
#define _EXTERN_C_  extern

#endif

#define MAX_TRX_SIGNALS	1
#define MAX_CHANNELS_PER_SIGNAL	1

#define DAC_MAX_SIG_NO	1
#define DAC_MAX_CH_NO	4

#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1

#define BIAS_DEC_STEP				10
#define MAX_LD_BIAS_DA				0xFFF /* 4095 */
#define MIN_LD_BIAS_DA				0x00  /* 2.5 V: 106 mA */

//------------------------------------------------------------------------------------
// MOD Bias Control
//------------------------------------------------------------------------------------
#define MAX_MOD_BIAS_DA				0xFFF /* 4095 */
#define MIN_MOD_BIAS_DA				0x00  /* 2.5 V: 106 mA */

//------------------------------------------------------------------------------------
// Cross Control
//------------------------------------------------------------------------------------
#define MAX_Xcon_DA			0x7F /* 127 */
#define MIN_Xcon_DA			0

#else

#define BIAS_DEC_STEP				10
// #define MAX_LD_BIAS_DA				4000
#define MAX_LD_BIAS_DA				4095
// #define MAX_LD_BIAS_DA				1170
//#define MAX_LD_BIAS_DA				0xD7  /* 2.5 V: 106 mA */
//#define MAX_LD_BIAS_DA				0x78  /* 2.5 V: 106 mA */
#define MIN_LD_BIAS_DA				0x00  /* 2.5 V: 106 mA */

//------------------------------------------------------------------------------------
// MOD Bias Control
//------------------------------------------------------------------------------------
// #define MAX_MOD_BIAS_DA				3450
// #define MAX_MOD_BIAS_DA				4095
#define MAX_MOD_BIAS_DA				65530
//#define MAX_MOD_BIAS_DA				669 /* 400 mV */
//#define MAX_MOD_BIAS_DA				250 /* 400 mV */

//------------------------------------------------------------------------------------
// Cross Control
//------------------------------------------------------------------------------------
// #define MAX_Xcon_DA			3071
#define MAX_Xcon_DA			4095
//#define MAX_Xcon_DA			255

#endif

//------------------------------------------------------------------------------------
// TEC Control
//------------------------------------------------------------------------------------
// 75 C
//#define MIN_TEC_CONTROL_DA    0x2175
//#define MIN_TEC_CONTROL_DA    0x268B

// 80 C, 79.94 ��
#define MIN_TEC_CONTROL_DA    0x1D13

// 35 C
//#define MAX_TEC_CONTROL_DA    0x6502
// 20 ��
#define MAX_TEC_CONTROL_DA    0x8E58

#define HIGH_TEMP_THRESHOLD   ((signed char)80)
#define LOW_TEMP_THRESHOLD  ((signed char)-15)

#define HIGH_TEMP_OFFSET_VALUE   ((signed char)30)
#define LOW_TEMP_OFFSET_VALUE  ((signed char)55)

#define CH_TYPE_BSET		0
#define CH_TYPE_MSET		1
#define CH_TYPE_CPA		2
#define CH_TYPE_STROBE  	3

#define CH_TYPE_IBMON	0
#define CH_TYPE_RSSI		1
#define CH_TYPE_MPD		2

#define BSET_DAC_CH1		0
#define MSET_DAC_CH1		0
#define CPA_DAC_CH1			0

#define BSET_DAC_CH2		1
#define MSET_DAC_CH2		1
#define CPA_DAC_CH2			1

#define BSET_DAC_CH3		2
#define MSET_DAC_CH3		2
#define CPA_DAC_CH3			2

#define BSET_DAC_CH4		3
#define MSET_DAC_CH4		3
#define CPA_DAC_CH4			3


// TX CDR: M37049, RX CDR: M37046, LD Drive: MAMF_011039
//#define TX_CDR_I2C_ADDR	0x18
//#define LD_DRIVER_I2C_ADDR	0x20

// LD Drive Registers
#define LDD_PAGE_SEL	((uint8_t)0xFF)

// 011039 TOSA PINs
// TOSA1_RESET Pin: P1.3
//SI_SBIT (TOSA1_RESET, SFR_P1, 3);// TOSA1_RESET, active LOW
//#define TOSA1_RESET_ON	0
//#define TOSA1_RESET_OFF	1

// TXDIS_TOSA Pin: P2.1, Connect to Power Down(PD) pin at 011039 LDD Control IC
//SI_SBIT (TXDIS_TOSA, SFR_P2, 1);// TOSA1_RESET, active High
//#define TXDIS_TOSA_OFF	0
//#define TXDIS_TOSA_ON	1

// TXDIS_CDR
// TXDIS_CDR Pin: P1.2
//SI_SBIT (TXDIS_CDR, SFR_P1, 2);// TXDIS_CDR, active High
#define TXDIS_CDR PO0_bit.PO00
#define TXDIS_CDR_ON	1
#define TXDIS_CDR_OFF	0

#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
#define GN_1157_CHIPID      0xC4

#else
// MAOM_37032A
#define MAOM_37032A_CHIPID      0x8D
#define MAOM_37032A_SW_RESET	0xAA

// MAOM_37030B
#define MAOM_37030B_CHIPID      0x30
#define MAOM_37030B_SW_RESET	0xAA

// MAOM_37031B
#define MAOM_37031B_CHIPID      0x31
#define MAOM_37031B_SW_RESET	0xAA

#endif


// Module Pin Definitions
// MSA Input Pins
#define MSA_INPUT_RS0 PI1_bit.PI13
#define MSA_INPUT_RS1 PI1_bit.PI15
#define MSA_INPUT_TXDIS PI2_bit.PI24

// MSA Output Pins
#define MSA_OUTPUT_RX_LOS PO2_bit.PO22
#define MSA_OUTPUT_TX_FAULT PO2_bit.PO23

#if __SFP_PLUS_3G_ER_SEMI_TUNABLE_HW_VER_2__ == 1

// Internal Output Pins
#define INT_OUTPUT_TXDIS_CDR  PO0_bit.PO00
#define INT_OUTPUT_RS1_uC     PO2_bit.PO26
#define INT_OUTPUT_RS0_uC     PO2_bit.PO21
//#define INT_OUTPUT_CDR_PWR_EN     PO2_bit.PO27

#else

// Internal Output Pins
#define INT_OUTPUT_TXDIS_CDR  PO0_bit.PO00
#define INT_OUTPUT_RS1_uC     PO2_bit.PO26
#define INT_OUTPUT_RS0_uC     PO2_bit.PO27
//#define INT_OUTPUT_CDR_PWR_EN     PO2_bit.PO27

#endif

// Internal Input Pins
#define INT_INPUT_RX_LOS_uC  PI0_bit.PI07
#define INT_INPUT_TX_FAULT_uC  PI0_bit.PI05

#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__==1
// Internal Output Pins
#define INT_RSTB  PO2_bit.PO25

#endif

// TEC Stable Thresholds +/- 64 (ADC value ����):�� 0.2 C �̳�, �� 18 pm ���� ����
#define TEC_STABLE_DIFF_RANGE 8

// TruLite APD: 20mV / ��
#define APD_VBR_DIFF_VALUE  2

// MACOM APD: 30mV / ��
//#define APD_VBR_DIFF_VALUE  3

// Registers
// 37031C CDR Registers

//#define  P00_CHIPID  0x00
//#define  P00_REVID   0x01
//#define  P00_RESET   0x02
//#define  P00_LB_MISCL  0x03
//#define  P00_RESERVED_1  0x04
//#define  P00_LOS_LOL_STATUS  0x06
//#define  P00_RESERVED_2  0x07
// 
//#define  P00_RX_MODES  0x10
//#define  P00_RX_PKNG_LOS_THRS  0x11
//#define  P00_RX_RX_SLA   0x12
//#define  P00_RX_CDRLBW   0x13
//#define  P00_RX_CDR_MISCL  0x14   
//#define  P00_RX_OP_SWING   0x15
//#define  P00_RX_OP_DEEMPH  0x16
// 
//#define  P00_RESERVED_3  0x17 
// 
//#define  P00_TX_MODES  0x20
//#define  P00_TX_ADAPT_EQ   0x21
//#define  P00_TX_LOS_THRS   0x22
// 
//#define  P00_RESERVED_4 Address 0x23
// 
//#define  P00_TX_CDRLBW   0x24
//#define  P00_TX_CDR_MISCL  0x25
//
//#define  P00_TX_OP_SWING   0x26 
//#define  P00_TX_OP_DEEMPH  0x27
//#define  P00_TX_OP_EYESHAPE  0x28 
//
//#define  P00_GPDAC   0x29
//#define  P00_RESERVED_5  0x2A
//#define  P00_RESERVED_6  0x2B
//#define  P00_RESERVED_7  0x2C
// 
//#define  P00_PRBSGEN   0x50
//#define  P00_PRBSGEN_DAC   0x51
// 
//#define  P00_PRBSCHK_ENBL  0x52
//#define  P00_PRBSCHK_BANK  0x53
//#define  P00_PRBSCHK_MODE  0x54
//#define  P00_PRBSCHK_Eye   0x55
//#define  P00_PRBSCHK_DELAY   0x56
//#define  P00_PRBSCHK_ERR_1   0x57 
//#define  P00_PRBSCHK_ERR_2   0x58
// 
//#define  P00_RESERVED_8  0x59 
//
//#define  P00_ADC_CONFIG_0  0x60
//#define  P00_ADC_CONFIG_2  0x61
// 
//#define  P00_RESERVED_9[3]   0x62 
// 
//#define  P00_ADC_OUT0_MSBS   0x65
//#define  P00_ADC_OUT0_LSBS   0x66





// Detailed Register Values
//#define M37049_CHIPID	0x89
//
//#define M37049_SW_RESET	0xAA
//
//// Detailed Register Values
//#define M37057_CHIPID	0x8A
//
//#define M37057_SW_RESET	0xAA

// LD Driver IC: 011039
//#define PAGE_0_TEMP_MON_LSB	0x04
//#define PAGE_0_TEMP_MON_MSB	0x05
//
//#define PAGE0_ADC_ENABLE_LSB	0x30
//#define PAGE0_ADC_ENABLE_MSB	0x31
//
//#define PAGE0_ADC_UPDATE_LSB	0x32
//#define PAGE0_ADC_UPDATE_MSB	0x33
//
//#define PAGE0_ADC_CTRL			0x36
//
//// Each channel
//#define PAGE_N_CH_TEMP_MON_LSB	0x24
//#define PAGE_N_CH_TEMP_MON_MSB	0x25
//
//#define PAGE_N_EXT_SRC_MON_LSB	0x26
//#define PAGE_N_EXT_SRC_MON_MSB		0x27



//typedef struct {
//	uint8_t	page;
//	uint8_t addr;
//} i2cWriteStruct;

typedef union {
	uint8_t byte_data[4];
	uint16_t word_data[2];
	unsigned long long_data;
	float fp_data;
} longDataType;

//EXTERN_SMBUS_S uint8_t xdata SMB_DATA_IN[NUM_BYTES_WR];

// Global holder for SMBus data.
// All transmit data is read from here
// NUM_BYTES_RD used because an SMBus read is Slave->Master
//EXTERN_SMBUS_S uint8_t xdata SMB_DATA_OUT[NUM_BYTES_RD];


EXTERN_SMBUS_S uint8_t page_password_enable[16]; //(0:Disable, 1:Enable)
                                                       //[0]: page 0, [1]: page 1, [2]: page 2, [3]: page 3, ... , [9]: A4
// Free side device manufacturer passwords: C05E7001H(0, 1, 3, 9 page enable)
// Fixed side system manufacturer passwords: 00001011H

EXTERN_SMBUS_S longDataType current_password;
EXTERN_SMBUS_S longDataType fixed_side_password;
EXTERN_SMBUS_S longDataType changing_fixed_side_password;

EXTERN_SMBUS_S uint8_t page_vendor_control; // 0: Normal, 1: Extend Access

// TOSA_control
_EXTERN_C_ INT16U  bset_dac_ch_no, mset_dac_ch_no, cpa_dac_ch_no;

_EXTERN_C_ INT16U  LdBiasDa;
_EXTERN_C_ INT16U  ModBiasCurSet, ModBiasCurDa;

_EXTERN_C_ INT16U  prevLdBiasDa;

_EXTERN_C_ INT8U   LdBiasSetFlag;
_EXTERN_C_ INT8U   LdBiasSetFlag2;

_EXTERN_C_ INT8U  LdControlMode;
_EXTERN_C_ INT16U  ModBiasSet, XconBiasSet;
_EXTERN_C_ INT16U  forcedLdBiasSet;
_EXTERN_C_ INT16U xdata ModBiasDa, XconBiasDa;
_EXTERN_C_ INT16U xdata prevModBiasDa, prevXconBiasDa;
_EXTERN_C_ INT16U TEC_Control_Da, prev_TEC_Control_Da;

  // [DCLEE: 191114] Alarm ���� -->

_EXTERN_C_ FP32	xdata txPower_coeff_0;
_EXTERN_C_ FP32	xdata txPower_coeff_1;
//_EXTERN_C_ FP32	xdata txPower_coeff_0[MAX_TUNABLE_WAVELENGTHS];
//_EXTERN_C_ FP32	xdata txPower_coeff_1[MAX_TUNABLE_WAVELENGTHS];
//_EXTERN_C_ FP32	xdata txPower_coeff_2[MAX_TRX_SIGNALS][MAX_CHANNELS_PER_SIGNAL];
//_EXTERN_C_ FP32	xdata txPower_coeff_3[MAX_TRX_SIGNALS][MAX_CHANNELS_PER_SIGNAL];
//_EXTERN_C_ FP32	xdata txPower_coeff_4[MAX_TRX_SIGNALS][MAX_CHANNELS_PER_SIGNAL];

_EXTERN_C_ FP32	xdata rxPower_coeff_0;
_EXTERN_C_ FP32	xdata rxPower_coeff_1;
_EXTERN_C_ FP32	xdata rxPower_coeff_2;
_EXTERN_C_ FP32	xdata rxPower_coeff_3;
_EXTERN_C_ FP32	xdata rxPower_coeff_4;


//_EXTERN_C_ FP32	ext_calib_txPower_coeff_0;
//_EXTERN_C_ FP32	ext_calib_txPower_coeff_1;
_EXTERN_C_ FP32	ext_calib_txPower_coeff_1;  // TX_POWER_Slope
_EXTERN_C_ signed int	ext_calib_txPower_coeff_0;  // TX_POWER_Offset

_EXTERN_C_ FP32	ext_calib_rxPower_coeff_0;
_EXTERN_C_ FP32	ext_calib_rxPower_coeff_1;
_EXTERN_C_ FP32	ext_calib_rxPower_coeff_2;
_EXTERN_C_ FP32	ext_calib_rxPower_coeff_3;
_EXTERN_C_ FP32	ext_calib_rxPower_coeff_4;

_EXTERN_C_ FP32 ext_calib_Tx_I_Slope;
_EXTERN_C_ signed int ext_calib_Tx_I_Offset;

_EXTERN_C_ FP32 ext_calib_Temp_Slope;
_EXTERN_C_ signed int ext_calib_Temp_Offset;

_EXTERN_C_ FP32 ext_calib_Vcc_Slope;
_EXTERN_C_ signed int ext_calib_Vcc_Offset;



//_EXTERN_C_ uint8_t xdata tx_i2c_master_data[16];
//_EXTERN_C_ uint8_t xdata rx_i2c_master_data[16];

_EXTERN_C_ uint16_t xdata write_i2c_count, read_i2c_count;

_EXTERN_C_ uint16_t curr_channel_no, curr_wavelength;

_EXTERN_C_ uint16_t cdr_reset_counter;


#if __HFR_REQ_DDM_FLAG_VER__==1
//[DLEE, 210901] for DDM Monitoring Flag Operation
_EXTERN_C_ uint8_t  ddm_temperature_flag;
_EXTERN_C_ uint8_t  ddm_vcc_flag;
_EXTERN_C_ uint8_t  ddm_tx_bias_flag;
_EXTERN_C_ uint8_t  ddm_tx_power_flag;
_EXTERN_C_ uint8_t  ddm_rx_power_flag;
#endif


#define FIXED_SIDE_SYSTEM_MANUFACTURER_PASSWORD_DEFAULT ((unsigned long)0x00001011)
#define FREE_SIDE_SYSTEM_MANUFACTURER_PASSWORD_DEFAULT ((unsigned long)0xC05E7001)
#define FREE_SIDE_SYSTEM_MANUFACTURER_PASSWORD_DEFAULT_2 ((unsigned long)0x19991217)
#define FREE_SIDE_SYSTEM_MANUFACTURER_PASSWORD_DEFAULT_3 ((unsigned long)0xC05E7ACC)
#define FREE_SIDE_SYSTEM_MANUFACTURER_PASSWORD_DEFAULT_4 ((unsigned long)0xC05E70FF)

#define FIXED_SIDE_SYSTEM_MANUFACTURER_PASSWORD_FW_DOWNLOAD ((unsigned long)0x4657444C)

// Functions
//extern uint8_t read_master_gpio_single_byte(unsigned char slave, unsigned char reg_address);
//extern void read_master_gpio_multiple_bytes(unsigned char slave, unsigned char reg_address, unsigned char length, unsigned char * valuePtr);
//extern void write_master_gpio_single_byte(unsigned char slave, unsigned char reg_address, unsigned char value);
//extern void write_master_gpio_multiple_bytes(unsigned char slave, unsigned char reg_address, unsigned char length, unsigned char * valuePtr);
extern void restore_from_flash_memory(uint8_t page_no);
extern void save_to_flash_memory(uint8_t page_no);
extern void save_to_flash_memory_ch_no(void);

extern void exec_lower_page_memory(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value);
extern void check_password_control(void);
extern void exec_write_entry(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value);
extern void exec_upper_page0_memory(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value);
extern void exec_upper_page1_memory(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value);
extern void exec_upper_page2_memory(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value);
extern void exec_upper_page3_memory(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value);
extern void exec_upper_page80H_memory(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value);
extern void exec_upper_page81H_memory(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value);
extern void exec_upper_page82H_memory(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value);
extern void exec_upper_page83H_memory(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value);
extern void exec_upper_page84H_memory(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value);
extern void exec_non_standard_A0_memory(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value);
extern void insert_write_entry(uint8_t dev_addr, uint8_t page, uint8_t write_addr);
extern void polled_write_entry(void);

//extern void Ld_Ch_seq_init(void);

extern void LdInit(void);
extern void LdControl_manually(INT8U sigNo, INT8U chNo );
extern void LdControl(INT8U sigNo, INT8U chNo );
extern void ModBiasControl_manually( INT8U sigNo, INT8U chNo );
extern void XconBiasControl( INT8U sigNo, INT8U chNo );
//extern void ModulatorOff( INT8U sigNo, INT8U chNo );
extern void LD_Drive_Set( char ch_type, char ch_num, int value );
extern uint16_t LD_Drive_Get( char ch_type, char ch_num);
extern uint16_t tx_cdr_init(uint8_t flag);
extern void tx_cdr_init_by_channel(uint8_t chNo, uint8_t flag);
extern void LdInit_forced_on_first( void );

extern uint16_t cdr_power_management_init(uint8_t flag);
extern uint16_t cdr_pmic_ch_control_reinit(uint8_t flag);
extern uint16_t check_n_recover_cdr_fault_or_hw_reset(void); // [DCLEE] 200927, detect and reinit operation for CDR abnormal reset situations. 

extern void LdControl_APC_3(INT8U sigNo, INT8U chNo );
extern void ModBiasControl_APC_3(INT8U sigNo, INT8U chNo );
extern void XconBiasControl_APC_3(INT8U sigNo, INT8U chNo );
extern void TEC_Control_APC_3(INT8U sigNo, INT8U chNo );

//extern FP32 power_2(INT32S b_n, INT32S pwr);
//extern FP32 conv_mantiza_2_fp32(INT32S e_f, INT32S m_f);
//extern FP32 ieee_754_sp_float_point_conv(INT32U fp_val);
//extern FP32 update_coef(INT16U fp_addr);
//extern void update_coef_all(void);

extern void polled_tx_cdr_reg_info(void);
extern void polled_LD_DC_reg_info(uint8_t page_no);
//
extern void get_adc_from_LDD_IC(void);
extern void trigger_LDD_IC_ADC_Mon(void);
//
//extern void LdControl_APC(INT8U sigNo, INT8U chNo );
//extern void LdControl_APC_1(INT8U sigNo, INT8U chNo );
//extern void LdControl_APC_2(INT8U sigNo, INT8U chNo );
//extern void LdControl_APC_3(INT8U sigNo, INT8U chNo );

extern void polled_tx_rx_combo_cdr_reg_info(void);
extern void polled_tx_cdr_reg_info(void);
extern void polled_rx_cdr_reg_info(void);

extern void factory_reset_eeprom_info(void);
extern void store_data_to_flash(void);

extern void restore_memory_from_flash_all(void);
extern void restore_memory_from_flash_tx_cdr(void);
extern void restore_memory_from_flash_rx_cdr(void);

#if 1
extern void I2C_Slave_Memory_Map_Write(uint8_t dev_addr, uint8_t page, uint8_t mem_address_index, uint8_t write_value);
#else
extern unsigned char I2C_Slave_Memory_Map_Write(uint8_t dev_addr, uint8_t page, uint8_t mem_address_index, uint8_t write_value);
#endif

extern void FLASH_Read(unsigned int dest, unsigned int src, unsigned int numbytes);

extern void load_init_data_from_flash(void);
extern void Ld_Ch_seq_init(void);

extern void initialize_variables();
extern void eml_bias_set(unsigned char bias_ch, unsigned int unBias);

extern uint16_t tx_cdr_init_from_flash(uint8_t flag);
extern uint16_t rx_cdr_init_from_flash(uint8_t flag);
extern void factory_reset_for_tx_rx_cdr(void);

extern void APD_Process(signed int sTemp_value);
extern uint16_t rate_select_control_cdr(uint8_t flag);

extern void rx_cdr_forced_mute_enable(unsigned char flag);
extern void wavelength_info_set(void);

extern void update_A0H_cc_base_value(void);

extern void LdControl_first_init();
extern void reset_gn1157();
#endif

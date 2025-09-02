/*
 * state_transition.h
 *
 *  Created on: 2019. 4. 24.
 *      Author: DongchoonLee
 */

#ifndef INC_STATE_TRANSITION_H_
#define INC_STATE_TRANSITION_H_

#ifdef __DECLARE_VARS__
#define _EXTERN_C_
#else
#define _EXTERN_C_ extern
#endif

#define _EXEC_STATE_TRANSITION_ 1

#define __NEW_TX_POWER_MON_BY_TEMPERATURE__ 0

// Number of Channels
#define SFP28_CONTROL_LANES	1

// State values are similar with CFP definitions.
#define ASSERTED_STATE		1
#define DEASSERTED_STATE	0

#define SFP28_MODULE_STATE_RESET				0x0000
#define SFP28_MODULE_STATE_INIT				0x0001
#define SFP28_MODULE_STATE_LOW_POWER			0x0002
#define SFP28_MODULE_STATE_HIGH_POWER_UP		0x0004
#define SFP28_MODULE_STATE_TX_OFF			0x0008
#define SFP28_MODULE_STATE_TX_TURN_ON		0x0010
#define SFP28_MODULE_STATE_READY				0x0020
#define SFP28_MODULE_STATE_FAULT				0x0040
#define SFP28_MODULE_STATE_TX_TURN_OFF		0x0080
#define SFP28_MODULE_STATE_HIGH_POWER_DOWN	0x0100

extern void state_transition_control(void);
extern uint8_t FPGA_Read_byte(uint8_t dev_addr, uint8_t mem_address_index, uint8_t page_addr);
extern void FPGA_Write_byte(uint8_t dev_addr, uint8_t mem_address_index, uint8_t page_addr, uint8_t write_value);

extern void assert_regs(uint8_t dev_addr, uint8_t reg, uint8_t page_addr, unsigned short set_bit);
extern void deassert_regs(uint8_t dev_addr, uint8_t reg, uint8_t page_addr, unsigned short set_bit);
extern void update_sfp28_state(unsigned short st_val);

extern unsigned char check_mod_lopwrs(void);
extern unsigned char check_tx_dis(void);

extern unsigned char check_mod_rsts(void);
extern void set_on_tx_dis_manually(void);
extern void set_off_tx_dis_manually(void);
extern void set_tx_dis_at_network_lanes(unsigned char n_lane, unsigned char bitVal);
extern int	turn_on_tx_network_lanes(void);
extern int	turn_off_tx_network_lanes(void);
extern void sfp28_state_reset(void);
extern void sfp28_state_initialize(void);
extern void sfp28_state_low_power(void);
extern void sfp28_state_high_power_up(void);
extern void sfp28_state_high_power_down(void);
extern void sfp28_state_tx_off(uint8_t *sigNo, uint8_t *chNo );
extern void sfp28_state_tx_turn_on(void);
extern void sfp28_state_tx_turn_off(void);
extern void sfp28_state_ready(uint8_t *sigNo, uint8_t *chNo );
extern void sfp28_state_fault(uint8_t *sigNo, uint8_t *chNo);
extern void high_power_up_action(void);
extern void high_power_down_action(void);
extern void MonitoringDataCon( uint8_t sigNo, uint8_t chNo );
extern void MonitoringDataCon_Lpmode( void);
extern void detect_cdr_alarm(void);
extern void update_faws_summary_registers(void);
extern uint8_t detect_current_alarm_state(uint8_t pVal, uint8_t cVal, uint8_t mask, uint8_t retMask);
extern void detect_channel_thr_alarm(void);
extern void detect_module_thr_alarm(void);
extern uint8_t check_thr_alarm(uint16_t mVal, uint16_t haVal, uint16_t laVal, uint16_t hwVal, uint16_t lwVal, uint8_t mask, uint8_t value_type);
extern void preAdjustAdc(void);
extern void preAdjustAdc_Lpmode(void);
extern short ThToTempConversion(uint16_t th_temp);
extern void forced_TX_DISABLE_ON(unsigned char tx_dis_flag);
extern void forced_TX_DISABLE_OFF(unsigned char tx_dis_flag);
extern void PLA_Soft_RX_LOS_Control(unsigned char unControl);
extern void PLA_Soft_RX_LOS_Control_from_CDR(unsigned char unControl);
extern unsigned char PLA_RX_LOS_Status(void);
extern void PLA_Soft_Tx_Fault_Control(unsigned char unControl);
extern unsigned char PLA_Tx_Fault_Status(void);
extern void PLA_Soft_Tx_Fault_Control_at_TxTune(unsigned char unControl);
extern void update_rate_select_operation(void);
extern void detect_rx_los_from_cdr(void);
extern void PLA_Soft_RX_LOS_Control_from_CDR(unsigned char unControl);
extern void ddm_mon_rx_power_from_CDR(void);

_EXTERN_C_ unsigned short sfp28_module_state;
_EXTERN_C_ unsigned char already_act_reset_flag;
_EXTERN_C_ unsigned char main_idx;
_EXTERN_C_ unsigned char main_sigNo;
_EXTERN_C_ unsigned char high_power_up_action_flag;
_EXTERN_C_ unsigned short faws_type_a_src;
_EXTERN_C_ unsigned short faws_type_b_src;
_EXTERN_C_ unsigned short faws_type_c_src;

_EXTERN_C_ uint8_t prev_los_flag, prev_lol_flag;
_EXTERN_C_ uint8_t prev_module_temp_thr_flag, prev_module_vcc_thr_flag;
_EXTERN_C_ uint8_t prev_channel_rx_power12_thr_flag, prev_channel_rx_power34_thr_flag;
_EXTERN_C_ uint8_t prev_channel_tx_power12_thr_flag, prev_channel_tx_power34_thr_flag;
_EXTERN_C_ uint8_t prev_channel_tx_bias12_thr_flag, prev_channel_tx_bias34_thr_flag;

_EXTERN_C_ unsigned short sfp28_module_debug_run_state;

_EXTERN_C_ unsigned char vendor_specific_pin_control_config; // B[1]: TX_DIS, B[0]: RX_LOS, active high

_EXTERN_C_ unsigned char tx_dis_flag_before_isr, tx_dis_flag_after_isr;
_EXTERN_C_ unsigned char rx_los_flag_before_isr, rx_los_flag_after_isr;

_EXTERN_C_ unsigned char prev_cdr_los_lol_status;

#if __NEW_TX_POWER_MON_BY_TEMPERATURE__==1
extern void calSlope_Offset(unsigned char chNo);

_EXTERN_C_ FP32  ht_slope;
_EXTERN_C_ FP32  ht_offset;
_EXTERN_C_ FP32  lt_slope;
_EXTERN_C_ FP32  lt_offset;

#endif

extern void cal_Temp_Slope_Offset(void);

_EXTERN_C_ FP32  itemp_ht_slope;
_EXTERN_C_ FP32  itemp_ht_offset;
_EXTERN_C_ FP32  itemp_lt_slope;
_EXTERN_C_ FP32  itemp_lt_offset;


// LPMODE Pin: P0.1
//SI_SBIT (LPMODE, SFR_P0, 1);// LPMODE, active LOW

#define LPMODE  PI2_bit.PI22

#define LPMODE_ON 1              // 0 = Board Controller disconnected
//     to EFM8 UART pins
#define LPMODE_OFF    0              // 1 = Board Controller connected

#define TX_DIS_ON	1
#define TX_DIS_OFF	0

//SI_SBIT (RESETL, SFR_P0, 7);// RESETL or MOD_RSTn
//SI_SBIT (MOD_RSTn, SFR_P0, 7);// RESETL or MOD_RSTn
#define MOD_RSTn  PI2_bit.PI20

//SI_SBIT (MODSELL, SFR_P0, 6);// MODESEL
#define MODSELL  PI1_bit.PI17

//SI_SBIT (INTL, SFR_P1, 0);// INTL
#define INTL  PI0_bit.PI07

#define RX_LOS  PI2_bit.PI05

#define __LOS_ASSERT_ENABLE__ 1

#define __RX_LOS_DDM_NO_FILTER__ 1

//#define LOS_ASSERTION_THRESHOLD 63  // -22.006 dBm, ER(DML APD) Reference
//#define LOS_DEASSERTION_THRESHOLD  100 // -20 dBm, ER(DML APD) Reference

//#define LOS_ASSERTION_THRESHOLD 10  // -30 dBm, ER(DML APD) Reference
//#define LOS_DEASSERTION_THRESHOLD  20 // -26.989 dBm, ER(DML APD) Reference

//#define LOS_ASSERTION_THRESHOLD  20 // -26.989 dBm, ER(DML APD) Reference
//#define LOS_DEASSERTION_THRESHOLD 31 // -25.08638306 dBm, ER(DML APD) Reference
//#define LOS_DEASSERTION_THRESHOLD 50  // -23.01029996 dBm, ER(DML APD) Reference

//#define LOS_ASSERTION_THRESHOLD  10 // -30 dBm, ER(DML APD) Reference
//#define LOS_DEASSERTION_THRESHOLD 16 // -28.... dBm, ER(DML APD) Reference

#define LOS_ASSERTION_THRESHOLD  14 // -30 dBm, ER(DML APD) Reference
#define LOS_DEASSERTION_THRESHOLD 18 // -28.... dBm, ER(DML APD) Reference

#endif /* INC_STATE_TRANSITION_H_ */

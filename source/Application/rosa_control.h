/*
 * rosa_control.h
 *
 *  Created on: 2019. 4. 29.
 *      Author: DongchoonLee
 */

#ifndef INC_ROSA_CONTROL_H_
#define INC_ROSA_CONTROL_H_

#ifdef __DECLARE_VARS__
#define _EXTERN_C_
#else
#define _EXTERN_C_ extern
#endif

// TX CDR: M37049, RX CDR: M37046, LD Drive: MAMF_011039
//#define RX_CDR_I2C_ADDR	0x16

//#define RX_CDR_I2C_ADDR	0x0B

// RXDIS_CDR
// RXDIS_CDR Pin: P1.2
//SI_SBIT (RXDIS_CDR, SFR_P3, 0);// RXDIS_CDR, active High
#define RXDIS_CDR_ON	1
#define RXDIS_CDR_OFF	0

// RX CDR Registers: M37049
//#define RX_CDR_CHIPID	0x00
//#define RX_CDR_REVID	0x01
//#define RX_CDR_RESET	0x02
//#define RX_CDR_ALARM_TYPE	0x03
//#define RX_CDR_CDRBIAS	0x04
//#define RX_CDR_I2C_ADDR_MODE	0x05
//
//#define RX_CDR_CDR_LD	0x0C
//
//#define RX_CDR_PRBSGEN	0x10
//#define RX_CDR_PRBSGEN_PLL	0x11
//#define RX_CDR_PRBSGEN_PLL_LOCK	0x12
//
//#define RX_CDR_LOSLOL_STATUS	0x14
//#define RX_CDR_LOSLOL_STATUS_1	0x15
//#define RX_CDR_LOSLOL_ALARM		0x16
//
//#define RX_CDR_MODE_CH_ALL	0x30
//#define RX_CDR_LOSLOL_MASK_CH_ALL	0x31
//#define RX_CDR_LOS_THRS_CH_ALL	0x32
//#define RX_CDR_SLA_CH_ALL	0x33
//#define RX_CDR_OUTPUT_SWING_CH_ALL	0x34
//#define RX_CDR_OUTPUT_DEEMPH_CH_ALL	0x35
//
//#define RX_CDR_PRBSCHK_ALL	0x39
//#define RX_CDR_PRBSCHK_BANK_ALL	0x3A
//#define RX_CDR_PRBSCHK_MODE_ALL	0x3B
//#define RX_CDR_PRBSCHK_EYE_ALL	0x3C
//#define RX_CDR_PRBSCHK_DELAY_ALL	0x3D
//
//#define RX_CDR_MODE_CH_N(m)	(RX_CDR_MODE_CH_ALL + (m)*(0x10))
//#define RX_CDR_LOSLOL_MASK_CH_N(m)	(RX_CDR_LOSLOL_MASK_CH_ALL + (m)*(0x10))
//#define RX_CDR_LOS_THRS_CH_N(m)	(RX_CDR_LOS_THRS_CH_ALL + (m)*(0x10))
//#define RX_CDR_SLA_CH_N(m)	(RX_CDR_SLA_CH_ALL + (m)*(0x10))
//#define RX_CDR_OUTPUT_SWING_CH_N(m)	(RX_CDR_OUTPUT_SWING_CH_ALL + (m)*(0x10))
//#define RX_CDR_OUTPUT_DEEMPH_CH_N(m)	(RX_CDR_OUTPUT_DEEMPH_CH_ALL + (m)*(0x10))
//
//#define RX_CDR_PRBSCHK_N(m)	(RX_CDR_PRBSCHK_ALL + (m)*(0x10))
//#define RX_CDR_PRBSCHK_BANK_N(m)	(RX_CDR_PRBSCHK_BANK_ALL + (m)*(0x10))
//#define RX_CDR_PRBSCHK_MODE_N(m)	(RX_CDR_PRBSCHK_MODE_ALL + (m)*(0x10))
//#define RX_CDR_PRBSCHK_EYE_N(m)	(RX_CDR_PRBSCHK_EYE_ALL + (m)*(0x10))
//#define RX_CDR_PRBSCHK_DELAY_N(m)	(RX_CDR_PRBSCHK_DELAY_ALL + (m)*(0x10))
//
//#define RX_CDR_PRBSCHK_ERROR_1(m)	(0x3E + (m)*(0x10))
//#define RX_CDR_PRBSCHK_ERROR_2(m)	(0x3F + (m)*(0x10))
//
//// Detailed Register Values
//#define M37046_CHIPID	0x86
//
//#define M37046_SW_RESET	0xAA


extern uint16_t rx_cdr_init(uint8_t flag);
extern void rx_cdr_init_by_channel(uint8_t chNo, uint8_t flag);
extern void polled_rx_cdr_reg_info(void);

#endif /* INC_ROSA_CONTROL_H_ */

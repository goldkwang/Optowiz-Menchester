/*
 * state_transition.c
 *
 *  Created on: 2019. 4. 24.
 *      Author: DongchoonLee
 */
//#include <SI_EFM8LB1_Register_Enums.h>                  // SFR declarations
//#include "retargetserial.h"
//
//// $[Generated Includes]
//// [Generated Includes]$
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
//
//#include "sff_8636.h"
//#include "SMBus_Drv.h"
//#include "timer_def.h"
//#include "i2c_master_gpio.h"
//
//#include "adc_drv.h"
//
//#include "debug.h"
//#include "dac_drv.h"
//#include "state_transition.h"
//#include "tosa_control.h"
//#include "rosa_control.h"
#include <intrinsics.h>
#include <iods4835.h>

//#include "iods4835.h"
#include "includes.h"

#ifndef xdata
#define xdata
#endif

void modsell_check(void)
{
#if __SFP28_ER__ == 1

#else
  
  //  I2CCN_S_bit.I2CEN = 1;                                                       //Enable I2C module

  if (MODSELL == 1) {
    if (I2CCN_S_bit.I2CEN == 1) 
    {
      I2CCN_S_bit.I2CEN = 0;                                                       //Enable I2C module
    }
  }
  else {
    if (I2CCN_S_bit.I2CEN == 0) 
    {
      I2CS_Init();                                                               //Initialize I2CS, then enable interrupt, i2c slave will ack when it has been enabled, so enable interrupt immedietly  
      IMR_bit.IM2 = 1;                                                           //I2C Slave module interrupt enable            
    }    
  }
  
#endif
  
}


void state_transition_control(void)
{

//	uint16_t * tmp_ptr;

#if _EXEC_STATE_TRANSITION_==1

//        modsell_check();
        
	if ((sfp28_module_state & SFP28_MODULE_STATE_FAULT) == SFP28_MODULE_STATE_FAULT)
	{
		sfp28_state_fault(&main_sigNo, &main_idx);
    
      // PO2_bit.PO26 ^= 1;
	}
	else
	{
		sfp28_module_debug_run_state++;
//		tmp_ptr = (uint16_t *)&I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_RESERVED8];

		switch (sfp28_module_state & ~SFP28_MODULE_STATE_FAULT)
		{
			case SFP28_MODULE_STATE_RESET:
      // PO1_bit.PO15 ^= 1;
      // PO2_bit.PO26 = 1;
				// Check chip access availability and wait until OK

				// Process xxxx_RESET_STATE
				sfp28_state_reset();
				break;

			case SFP28_MODULE_STATE_INIT:
      // PO1_bit.PO15 ^= 1;
      // PO2_bit.PO26 = 0;
				// Transit State
				sfp28_state_initialize();
				break;

			case SFP28_MODULE_STATE_LOW_POWER:
      // PO1_bit.PO15 ^= 1;
				sfp28_state_low_power();
				break;

			case SFP28_MODULE_STATE_HIGH_POWER_UP:
      // PO1_bit.PO15 ^= 1;
				sfp28_state_high_power_up();
				break;

			case SFP28_MODULE_STATE_TX_OFF:
      // PO1_bit.PO15 ^= 1;
				sfp28_state_tx_off(&main_sigNo, &main_idx);
				break;

			case SFP28_MODULE_STATE_TX_TURN_ON:
      // PO1_bit.PO15 ^= 1;
				sfp28_state_tx_turn_on();
				break;

			case SFP28_MODULE_STATE_READY:
      // PO1_bit.PO15 ^= 1;
				sfp28_state_ready(&main_sigNo, &main_idx);
				break;

			case SFP28_MODULE_STATE_TX_TURN_OFF:
      // PO1_bit.PO15 ^= 1;
				sfp28_state_tx_turn_off();
				break;

			case SFP28_MODULE_STATE_HIGH_POWER_DOWN:
      // PO1_bit.PO15 ^= 1;
				sfp28_state_high_power_down();
				break;

			default:
      // PO1_bit.PO15 ^= 1;
				//printf("Invalid sfp28_module_state (%04lx) \n", sfp28_module_state);
				break;
		}
//		*tmp_ptr = __swap_bytes(sfp28_module_debug_run_state);

	}
#endif

}

uint8_t FPGA_Read_byte(uint8_t dev_addr, uint8_t mem_address_index, uint8_t page_addr)
{
	uint8_t rx_memory_value, tmp_mem_address_index, page_select_value;

	if (dev_addr == 0xA2) {
		if (mem_address_index < (uint8_t)LOWER_PAGE_ADDR){
			rx_memory_value = I2C_Slave_Buffer_A2[mem_address_index];
		}
		else {
			page_select_value = page_addr;
			tmp_mem_address_index = mem_address_index & (uint8_t)0x7F;
			switch (page_select_value) {
				case 0x00:
					rx_memory_value = I2C_Slave_Buffer_A2_P00H_Up[tmp_mem_address_index];
					break;

				case 0x01:
					rx_memory_value = I2C_Slave_Buffer_A2_P01H_Up[tmp_mem_address_index];
					break;

				case 0x02:
					rx_memory_value = I2C_Slave_Buffer_A2_P02H_Up[tmp_mem_address_index];
					break;

				case 0x80:
					rx_memory_value = I2C_Slave_Buffer_A2_P80H_Up[tmp_mem_address_index];
					break;

				case 0x81:
					rx_memory_value = I2C_Slave_Buffer_A2_P81H_Up[tmp_mem_address_index];
					break;

				case 0x82:
					rx_memory_value = I2C_Slave_Buffer_A2_P82H_Up[tmp_mem_address_index];
					break;

				case 0x83:
					rx_memory_value = I2C_Slave_Buffer_A2_P83H_Up[tmp_mem_address_index];
					break;
                                        
				default:
					rx_memory_value = 0xDD;
					break;
			}
		}
	}
	else if (dev_addr == 0xA0){
		rx_memory_value = I2C_Slave_Buffer_A0_Local_Memory[tmp_mem_address_index];
	}
	return ((uint8_t)rx_memory_value);
}

void FPGA_Write_byte(uint8_t dev_addr, uint8_t mem_address_index, uint8_t page_addr, uint8_t write_value)
{
//	uint8_t * tmp_memory_array;
	uint8_t tmp_mem_address_index, page_select_value;

	if (dev_addr == 0xA2) {
		if (mem_address_index < (uint8_t)LOWER_PAGE_ADDR){
			I2C_Slave_Buffer_A2[mem_address_index] = write_value;
		}
		else {
			page_select_value = page_addr;
			tmp_mem_address_index = mem_address_index & (uint8_t)0x7F;
			switch (page_select_value) {
				case 0x00:
					I2C_Slave_Buffer_A2_P00H_Up[tmp_mem_address_index] = write_value;
					break;

				case 0x01:
					I2C_Slave_Buffer_A2_P01H_Up[tmp_mem_address_index] = write_value;
					break;

				case 0x02:
					I2C_Slave_Buffer_A2_P02H_Up[tmp_mem_address_index] = write_value;
					break;

				case 0x80:
					I2C_Slave_Buffer_A2_P80H_Up[tmp_mem_address_index] = write_value;
					break;

				case 0x81:
					I2C_Slave_Buffer_A2_P81H_Up[tmp_mem_address_index] = write_value;
					break;

				case 0x82:
					I2C_Slave_Buffer_A2_P82H_Up[tmp_mem_address_index] = write_value;
					break;

				case 0x83:
					I2C_Slave_Buffer_A2_P83H_Up[tmp_mem_address_index] = write_value;
					break;

                                case 0x84:
					I2C_Slave_Buffer_A2_P84H_Up[tmp_mem_address_index] = write_value;
					break;
                                        
				default:
					break;
			}
		}
	}
	else if (dev_addr == 0xA0){
		I2C_Slave_Buffer_A0_Local_Memory[tmp_mem_address_index] = write_value;
	}
}

void assert_regs(uint8_t dev_addr, uint8_t reg, uint8_t page_addr, unsigned short set_bit)
{/*{{{*/
	unsigned char xdata wVal;

	wVal = FPGA_Read_byte(dev_addr, reg, page_addr);
	wVal |= set_bit;
	FPGA_Write_byte(dev_addr, reg, page_addr, wVal);

	return;
}/*}}}*/

void deassert_regs(uint8_t dev_addr, uint8_t reg, uint8_t page_addr, unsigned short set_bit)
{/*{{{*/
	unsigned char xdata wVal;

	wVal = FPGA_Read_byte(dev_addr, reg, page_addr);
	wVal &= (~set_bit);
	FPGA_Write_byte(dev_addr, reg, page_addr, wVal);

	return;
}/*}}}*/

void update_sfp28_state(unsigned short st_val)
{/*{{{*/
	A2_PAGE_80H_MEMORY_MAP	xdata * flashPtr;

	flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];

	if (st_val == SFP28_MODULE_STATE_FAULT)
	{
		sfp28_module_state = sfp28_module_state  | st_val;
		flashPtr->module_state = __swap_bytes(sfp28_module_state);
		// FPGA_Write_word(CFP_FPGA_VR_1_MOD_STATE, cfp_module_state);

	}
	else
	{
		sfp28_module_state = (sfp28_module_state & SFP28_MODULE_STATE_FAULT) | st_val;
		// FPGA_Write_word(SFP28_FPGA_VR_1_MOD_STATE, sfp28_module_state);
		flashPtr->module_state = __swap_bytes(sfp28_module_state);

	}

	// Set Module FAWS Latch Register
	// assert_regs(CFP_FPGA_VR_1_MOD_FAWS_LATCH, st_val);
	return;
}/*}}}*/


void set_on_tx_dis_manually(void)
{/*{{{*/
#if __SFP28_ER__ == 1
  
#if __SFP28_ER_SEMI_TUNABLE__ == 1
  
//    PLA_Soft_TXD_Control(ASSERTED);
//    PLA_Soft_TXD_Control_forced(ASSERTED);
    PLA_Soft_TXD_Control_forced(DE_ASSERTED);  // W/O TXDIS, Temporarily 210909
//    PLACNT1_bit.SB1 = 1;
    return;
    
#else

//  unsigned char chNo;

  ModBiasSet = 0;
  XconBiasSet = 0;
  forcedLdBiasSet = 0;   
  
  LdControl_manually(0, 0 );
  ModBiasControl_manually(0, 0 );
  XconBiasControl(0, 0 );    
  
  return;
  
#endif
  
#else

#endif

}/*}}}*/

void set_off_tx_dis_manually(void)
{/*{{{*/
#if __SFP28_ER__ == 1
#if __SFP28_ER_SEMI_TUNABLE__ == 1
  
//    PLA_Soft_TXD_Control(DE_ASSERTED);
    PLA_Soft_TXD_Control_forced(ASSERTED);
//    PLACNT1_bit.SB1 = 0;
    return;
    
#else
  
//  unsigned char chNo;
  A2_PAGE_80H_MEMORY_MAP	xdata * flashPtr;
  
  flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
  
  ModBiasSet = __swap_bytes(flashPtr->ModBiasSet);
  XconBiasSet = __swap_bytes(flashPtr->XconBiasSet);
  forcedLdBiasSet = __swap_bytes(flashPtr->forcedLdBiasSet);   
  
  LdControl_manually(0, 0 );
  ModBiasControl_manually(0, 0 );
  XconBiasControl(0, 0 );    
  
  return;
  
#endif
  
#else

#endif
        
}/*}}}*/

void set_tx_dis_at_network_lanes_in_isr(unsigned char n_lane, unsigned char bitVal)
{
#if __SFP28_ER__ == 1
#if __SFP28_ER_SEMI_TUNABLE__ == 1
  
  if (bitVal == 1)
  { // TX Disable
//    PLA_Soft_TXD_Control(ASSERTED);
    PLA_Soft_TXD_Control_forced(ASSERTED);

  }
  else
  {// TX Enable
//    PLA_Soft_TXD_Control(DE_ASSERTED);
    PLA_Soft_TXD_Control_forced(DE_ASSERTED);
  }
//    PLACNT1_bit.SB1 = 0;
    return;
    
#else
//  unsigned char chNo;
//  unsigned char reg_addr;
//  A2_PAGE_80H_MEMORY_MAP	xdata * flashPtr;
//  
//  flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
  
  if (bitVal == 1)
  { // TX Disable

    eml_bias_set(0, (unsigned int)0);
//    reg_addr = chNo + 4; // EAM Bias Set 0 - 3 : DAC ChNo 4 ~ 7
//    Max5825_dac_set(0, reg_addr, 0);            
//    reg_addr = chNo; // VC Set 0 - 3 : DAC ChNo 0 - 3, CrossPoint
//    Max5825_dac_set(0, reg_addr, 0);            
    
  }
  else 
  { // TX Enable
    eml_bias_set(0, (unsigned int)forcedLdBiasSet);
//    reg_addr = chNo + 4; // EAM Bias Set 0 - 3 : DAC ChNo 4 ~ 7
//    Max5825_dac_set(0, reg_addr, ModBiasSet);            
//    reg_addr = chNo; // VC Set 0 - 3 : DAC ChNo 0 - 3, CrossPoint
//    Max5825_dac_set(0, reg_addr, XconBiasSet);            
    
  }
  
//  LdControl_manually(0, chNo );
//  ModBiasControl_manually(0, chNo );
//  XconBiasControl(0, chNo );    
  
  return;
#endif
  
#else
  
#endif
  
}

void set_tx_dis_at_network_lanes(unsigned char n_lane, unsigned char bitVal)
{
#if __SFP28_ER__ == 1
#if __SFP28_ER_SEMI_TUNABLE__ == 1
  
  if (bitVal == 1)
  { // TX Disable
    PLA_Soft_TXD_Control(ASSERTED);
  }
  else
  {// TX Enable
    PLA_Soft_TXD_Control(DE_ASSERTED);
  }
//    PLACNT1_bit.SB1 = 0;
    return;
    
#else
//  unsigned char chNo;
//  unsigned char reg_addr;
  A2_PAGE_80H_MEMORY_MAP	xdata * flashPtr;
  
  flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
  

  
  if (bitVal == 1)
  { // TX Disable
   
    eml_bias_set(0, (unsigned int)0);
//    reg_addr = chNo + 4; // EAM Bias Set 0 - 3 : DAC ChNo 4 ~ 7
//    Max5825_dac_set(0, reg_addr, 0);            
//    reg_addr = chNo; // VC Set 0 - 3 : DAC ChNo 0 - 3, CrossPoint
//    Max5825_dac_set(0, reg_addr, 0);            
    
  }
  else 
  { // TX Enable
    ModBiasSet = __swap_bytes(flashPtr->ModBiasSet);
    XconBiasSet = __swap_bytes(flashPtr->XconBiasSet);
    forcedLdBiasSet = __swap_bytes(flashPtr->forcedLdBiasSet);   
    LdControl_manually(0, 0 );
    ModBiasControl_manually(0, 0 );
    XconBiasControl(0, 0 );    
    
  }
  

  return;
#endif
  
#else

#endif
        
}


void forced_TX_DISABLE_ON(unsigned char tx_dis_flag)
{
//  return;
  
  tx_dis_flag_before_isr = 1;
  tx_dis_flag_after_isr = 1;
  
  set_tx_dis_at_network_lanes_in_isr(0, 1);
//  set_tx_dis_at_network_lanes_in_isr(1, 1);
//  set_tx_dis_at_network_lanes_in_isr(2, 1);
//  set_tx_dis_at_network_lanes_in_isr(3, 1);

  tx_dis_flag_before_isr = 0;

}

void forced_TX_DISABLE_OFF(unsigned char tx_dis_flag)
{
//  return;
  
  tx_dis_flag_before_isr = 1;
  tx_dis_flag_after_isr = 1;

  set_tx_dis_at_network_lanes_in_isr(0, 0);
//  set_tx_dis_at_network_lanes_in_isr(1, 0);
//  set_tx_dis_at_network_lanes_in_isr(2, 0);
//  set_tx_dis_at_network_lanes_in_isr(3, 0);

  tx_dis_flag_before_isr = 0;
}

int	turn_on_tx_network_lanes(void)
{/*{{{*/
#if __SFP28_ER__ == 1
  
#if __WO_TXDIS_PIN_MONITORING__==1
  if (MSA_INPUT_TXDIS == 1) 
  { // TX DISABLE
//    set_tx_dis_at_network_lanes(0, 1);
    set_tx_dis_at_network_lanes(0, 0); // Ignore this pin state temporarily
  }
  else
  {
    set_tx_dis_at_network_lanes(0, 0);
  }
#else
  
  if (MSA_INPUT_TXDIS == 1) 
  { // TX DISABLE
    set_tx_dis_at_network_lanes(0, 1);
  }
  else
  {
    set_tx_dis_at_network_lanes(0, 0);
  }
#endif
  
  tx_dis_flag_after_isr = 0;
  
  return 1;
#else
  return 1;
#endif

}/*}}}*/

int	turn_off_tx_network_lanes(void)
{/*{{{*/
	set_on_tx_dis_manually();

	return 1;
}/*}}}*/


// State functions: reset, initialize, low_power, high_power_up, high_power_down, tx_off, tx_turn_on, tx_turn_off, ready, fault

void sfp28_state_reset(void)
{/*{{{*/
#if _EXEC_STATE_TRANSITION_==1
  
  if (already_act_reset_flag == 0)
  {
    // set_off_tx_dis_manually();
    
    set_on_tx_dis_manually();
    
    LdInit();
#if __SFP28_ER_SEMI_TUNABLE__ == 1
    
#else
    
    IDAC_Init();                                           //IDAC init
    DSDAC_Init();    
    SW_Delay(2000);
#endif
    
    APD_Init();
    
    already_act_reset_flag = 1;
  }
  
  // if (ms_cnt > 1000)
  {
    //		ms_cnt = 0;
    
    if (check_mod_rsts() == DEASSERTED_STATE)
    {
      update_sfp28_state(SFP28_MODULE_STATE_INIT);
    }
    else
    {
      update_sfp28_state(SFP28_MODULE_STATE_RESET);
      //			assert_regs(I2C_ADDR_A0, SFP28_LOWER_MEMORY_STATUS_LSB, A0_LOW_PAGE, STATUS_LSB_DATA_NOT_READY);
    }
  }
  /*
	 * put_c('r');
	 */
#endif

}/*}}}*/

void sfp28_state_initialize(void)
{/*{{{*/
#if _EXEC_STATE_TRANSITION_==1
//  uint8_t xdata rVal1, rVal2;
  load_init_data_from_flash( );
  
  // [DCLEE] 200319: TXDIS PIN Interrupt Enable -->
  TXD_External_Interrupt_init();                         //Init TXD interrupt
  
  IMR_bit.IM0 = 1;                                       //External interrupt enable(TXD)
  
  update_sfp28_state(SFP28_MODULE_STATE_LOW_POWER);
  set_on_tx_dis_manually();

#endif

}/*}}}*/

void sfp28_state_low_power(void )
{/*{{{*/
#if _EXEC_STATE_TRANSITION_==1
  
  
  // if (ms_cnt > 250)
  {
    //ms_cnt = 0;
    
    if (check_mod_lopwrs() == (unsigned char)ASSERTED_STATE)
    {
      // MOD_LOPWRs Asserted
      update_sfp28_state(SFP28_MODULE_STATE_LOW_POWER);
    }
    else
    {
      // MOD_LOPWRs De-asserted
      update_sfp28_state(SFP28_MODULE_STATE_HIGH_POWER_UP);
    }
    
    if (check_mod_rsts() == ASSERTED_STATE)
    {
      update_sfp28_state(SFP28_MODULE_STATE_RESET);
    }
  }
  /*
	 * put_c('l');
	 */
#endif

}/*}}}*/

void sfp28_state_high_power_up(void)
{/*{{{*/
#if _EXEC_STATE_TRANSITION_==1
  if (high_power_up_action_flag == 0)
  {
    set_on_tx_dis_manually();
    high_power_up_action();
    high_power_up_action_flag = 1;
    //set_off_tx_dis_manually();
  }
  
  
  if ((check_mod_lopwrs() == ASSERTED_STATE) || (check_mod_rsts() == ASSERTED_STATE))
  {
    // MOD_LOPWRs Asserted
    update_sfp28_state(SFP28_MODULE_STATE_HIGH_POWER_DOWN);
  }
  else
  {
    update_sfp28_state(SFP28_MODULE_STATE_TX_OFF);
  }

#endif

}/*}}}*/

void sfp28_state_high_power_down(void)
{/*{{{*/
#if _EXEC_STATE_TRANSITION_==1
  if (high_power_up_action_flag == 1)
  {
    high_power_down_action();
    high_power_up_action_flag = 0;
    // set_off_tx_dis_manually();
    set_on_tx_dis_manually();
    
  }
  
  if ((sfp28_module_state & SFP28_MODULE_STATE_HIGH_POWER_DOWN) == SFP28_MODULE_STATE_HIGH_POWER_DOWN)
  {
    if (check_mod_lopwrs() == ASSERTED_STATE)
    {
      update_sfp28_state(SFP28_MODULE_STATE_LOW_POWER);
    }
    
    if (check_mod_rsts() == ASSERTED_STATE)
    {
      update_sfp28_state(SFP28_MODULE_STATE_RESET);
    }
  }

#endif

}/*}}}*/

void sfp28_state_tx_off(uint8_t *sigNo, uint8_t *chNo )
{/*{{{*/
#if _EXEC_STATE_TRANSITION_==1
//  MonitoringDataCon(0, 0);
  
  if (check_tx_dis() == (unsigned char)ASSERTED_STATE)
  {
    // Assert TX_DISs: keep on TX_Off state
    update_sfp28_state(SFP28_MODULE_STATE_TX_OFF);
  }
  else
  {
    // De-assert TX_DISs
    update_sfp28_state(SFP28_MODULE_STATE_TX_TURN_ON);
  }
  
  if ((check_mod_lopwrs() == (unsigned char)ASSERTED_STATE) || (check_mod_rsts() == (unsigned char)ASSERTED_STATE))
  {
    // Assert TX_DISs
    update_sfp28_state(SFP28_MODULE_STATE_HIGH_POWER_DOWN);
  }
  MonitoringDataCon(0, 0);
  
#endif

}/*}}}*/

void sfp28_state_tx_turn_on(void)
{/*{{{*/

#if _EXEC_STATE_TRANSITION_==1
  
  // [DCLEE] 200923, VIAVI ��񿡼� ���� ���� �� ���Ž�ȣ�� Ŭ�� ��ȣ ���� ��� ���� �ذ� -->
//  LdInit_forced_on_first(); <-- �� ������ ����
  
  
  if (turn_on_tx_network_lanes() != 0)
  {
    // transition to Ready state
    
    update_sfp28_state(SFP28_MODULE_STATE_READY);
      LdInit_forced_on_first(); // <-- ���⿡�� ��� ���� 

  }
  else
  {
    // transition to Fault state
    
    update_sfp28_state(SFP28_MODULE_STATE_FAULT);
    
  }
  
#endif

}/*}}}*/

void sfp28_state_tx_turn_off(void)
{/*{{{*/

#if _EXEC_STATE_TRANSITION_==1
  
  turn_off_tx_network_lanes();
  
  if ((check_mod_lopwrs() == ASSERTED_STATE) || (check_mod_rsts() == ASSERTED_STATE))
  {
    // Assert TX_DISs
    update_sfp28_state(SFP28_MODULE_STATE_HIGH_POWER_DOWN);
  }
  else if (check_tx_dis() == ASSERTED_STATE)
  {
    // Assert TX_DISs: keep on TX_Off state
    update_sfp28_state(SFP28_MODULE_STATE_TX_OFF);
  }
  else
  {
    update_sfp28_state(SFP28_MODULE_STATE_TX_OFF);
  }

#endif

}/*}}}*/

void sfp28_state_ready(uint8_t *sigNo, uint8_t *chNo )
{/*{{{*/
#if _EXEC_STATE_TRANSITION_==1

  LdControl(0, 0);
  MonitoringDataCon(0, 0);
 
  if ((check_mod_lopwrs() == ASSERTED_STATE) || (check_mod_rsts() == ASSERTED_STATE))
  {
    
    update_sfp28_state(SFP28_MODULE_STATE_TX_TURN_OFF);
    
  }
  else if (check_tx_dis() == ASSERTED_STATE)
  {
    
    update_sfp28_state(SFP28_MODULE_STATE_TX_TURN_OFF);
    
  }
  else
  {
    turn_on_tx_network_lanes();
  }
  
  check_n_recover_cdr_fault_or_hw_reset();

	
#endif

}/*}}}*/

void sfp28_state_fault(uint8_t *sigNo, uint8_t *chNo)
{/*{{{*/
#if _EXEC_STATE_TRANSITION_==1

  unsigned int  reset_flag;
  A2_PAGE_80H_MEMORY_MAP	xdata * flashPtr;
  
  flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
  
  reset_flag = __swap_bytes(flashPtr->flash_reset_flag);
  if (reset_flag != 0x0C00)
  {
    return;
  }
  

  if (high_power_up_action_flag == 1)
  {
    high_power_down_action();
    high_power_up_action_flag = 0;
  }
  MonitoringDataCon(0, 0);
  
  if (check_mod_rsts() == ASSERTED_STATE)
  {
    // Assert TX_DISs

    update_sfp28_state(SFP28_MODULE_STATE_RESET);

  }
                

#endif

}/*}}}*/


void high_power_up_action(void)
{
#if __SFP28_ER__== 1
  
#if __SFP28_ER_SEMI_TUNABLE__ == 1
    
//  uint8_t chNo, idx, prev_reg_value;
  A2_PAGE_81H_MEMORY_MAP	xdata * flashPtr;
  unsigned int unDdm_value, ref_v_thm_value, idx_tec_check_cnt;
  int diff_value;
  uint8_t tmp_value;
  
  flashPtr = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P81H_Up[0];

//        return;

  tmp_value = I2C_Slave_Buffer_A2_P80H_Up[FLASH_LD_CONTROL_MODE];

#if 1  
  // Power turn on at the reg 9018: P3V3_OFF REG to 0x000f
  
  // TEC_SET DAC control
  if ((flashPtr->PMIC_SELECT & TEC1_ENABLE) == TEC1_ENABLE)
  {
    if (tmp_value == 0) {          
//      flashPtr->TEC1_SETPOINT = flashPtr->nt_tec_setpoint_per_wavelength[curr_channel_no-1];
      flashPtr->TEC1_SETPOINT = flashPtr->nt_tec_setpoint_per_wavelength[(curr_channel_no-1)%4];
    }
    else
    {
      TEC_Control_APC_3(0, 0);
    }
    
//    flashPtr->TEC1_SETPOINT = flashPtr->nt_tec_setpoint_per_wavelength[curr_channel_no-1];

    TEC_Init();
    asm("nop");         
    asm("nop");         
    asm("nop");         
    asm("nop");         
    asm("nop");         
    asm("nop");
    
    ref_v_thm_value = __swap_bytes(flashPtr->TEC1_SETPOINT);
    
    for (idx_tec_check_cnt=0; idx_tec_check_cnt < 30000; idx_tec_check_cnt++)
    {
      WDCN_bit.RWT = 1;                                                      //Reset Watchdog Timer
      unDdm_value = ADC_ReadOut(CONFG_VTHERM1);                                   //read raw ADC 
            
      flashPtr->V_THM = __swap_bytes(unDdm_value);              //update raw adc to A0h
    
      if (ref_v_thm_value > unDdm_value)
      {
        diff_value = ref_v_thm_value - unDdm_value;
      }
      else
      {
        diff_value = unDdm_value - ref_v_thm_value;
      }
      
      if (diff_value < TEC_STABLE_DIFF_RANGE)
      {
       // TEC stable state
        break;
      }
      SW_Delay(2);
//      SW_Delay(20);
      
    }
  }
#endif
  
//  SW_Delay(100);
  
  // Reset clear for TX and RX CDRs
  
//  TXDIS_CDR = TXDIS_CDR_OFF;
  WDCN_bit.RWT = 1;                                                      //Reset Watchdog Timer
  // RX CDRs
//  tx_cdr_init(0);
//  
//  // TX CDRs
//  rx_cdr_init(0);
  
//  PLA_Soft_TXD_Control_forced(ASSERTED);
  
#if __WO_TXDIS_PIN_MONITORING__==1
  
  PLA_Soft_TXD_Control(DE_ASSERTED);
  
#else
  
  PLA_Soft_TXD_Control(ASSERTED);
  
#endif
  
  
  reset_gn1157();
    
  cdr_power_management_init(0);
  
  update_msa_control_regs_from_tx_cdr();
  update_msa_control_regs_from_rx_cdr();

#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
  
#if 1
  // GN_1157
  // P00_BIAS_TCA_DAC
  tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[P00_BIAS_TCA_DAC];
//  tx_i2c_master_data[0] &= 0xB7;
//  tx_i2c_master_data[0] = 0xFF;
  
  write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_BIAS_TCA_DAC, 1, &tx_i2c_master_data[0]);

  I2C_Slave_Buffer_A2_P82H_Up[P00_BIAS_TCA_DAC] = tx_i2c_master_data[0];

  // P00_MON_TCA_DAC
  tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[P00_MON_TCA_DAC];
//  tx_i2c_master_data[0] &= 0xB7;
//  tx_i2c_master_data[0] = 0xFF;
  
  write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_MON_TCA_DAC, 1, &tx_i2c_master_data[0]);

  I2C_Slave_Buffer_A2_P82H_Up[P00_MON_TCA_DAC] = tx_i2c_master_data[0];

  // P00_VF_TCA_DAC
  tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[P00_VF_TCA_DAC];
//  tx_i2c_master_data[0] &= 0xB7;
//  tx_i2c_master_data[0] = 0xFF;
  
  write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_VF_TCA_DAC, 1, &tx_i2c_master_data[0]);

  I2C_Slave_Buffer_A2_P82H_Up[P00_VF_TCA_DAC] = tx_i2c_master_data[0];
  
#endif
  
  tx_cdr_init(0);
  rx_cdr_init(0);
  
  update_rate_select_operation();

//  PLA_Soft_TXD_Control_forced(DE_ASSERTED);
  PLA_Soft_TXD_Control(DE_ASSERTED);

  // TX Enalbe and APC Mode Disable
//  tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[P00_CR1];
////  tx_i2c_master_data[0] &= 0xB7;
//  tx_i2c_master_data[0] &= 0xA7;
//  
//  write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_CR1, 1, &tx_i2c_master_data[0]);
//
//  I2C_Slave_Buffer_A2_P82H_Up[P00_CR1] = tx_i2c_master_data[0];
  
#else
  
  tx_i2c_master_data[0] = 0x0B;
  write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_OPMODE_CTRL, 1, &tx_i2c_master_data[0]);
  
//  tx_i2c_master_data[0] = 0xCA;
//  write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_CTRL0, 1, &tx_i2c_master_data[0]);

  tx_i2c_master_data[0] = 0xCE;
  write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_CTRL0, 1, &tx_i2c_master_data[0]);

#endif
  
//  SW_Delay(10);
//  
//  
//  asm("nop");         
//  asm("nop");         
//  asm("nop");         
//  asm("nop");         
//  asm("nop");         
//  asm("nop");         
//  
//  asm("nop");         
//  asm("nop");         
//  asm("nop");         
//  asm("nop");         
//  asm("nop");         
//  asm("nop");         
//  
//  
//  SW_Delay(10);
  
#else
  
  
//  uint8_t chNo, idx, prev_reg_value;
  A2_PAGE_81H_MEMORY_MAP	xdata * flashPtr;
  
  flashPtr = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P81H_Up[0];
  
  // Power turn on at the reg 9018: P3V3_OFF REG to 0x000f
  
  // TEC_SET DAC control
  if ((flashPtr->PMIC_SELECT & TEC1_ENABLE) == TEC1_ENABLE)
  {
    TEC_Init();
    asm("nop");         
    asm("nop");         
    asm("nop");         
    asm("nop");         
    asm("nop");         
    asm("nop");        
  }
  SW_Delay(100);
  
  // Reset clear for TX and RX CDRs
  
//  TXDIS_CDR = TXDIS_CDR_OFF;
  WDCN_bit.RWT = 1;                                                      //Reset Watchdog Timer
  // RX CDRs
  tx_cdr_init(0);
//  
//  // TX CDRs
  rx_cdr_init(0);

  SW_Delay(10);
  
  
  asm("nop");         
  asm("nop");         
  asm("nop");         
  asm("nop");         
  asm("nop");         
  asm("nop");         
  
  asm("nop");         
  asm("nop");         
  asm("nop");         
  asm("nop");         
  asm("nop");         
  asm("nop");         
  
  
  SW_Delay(10);
                
#endif
#endif

  return;
}


void high_power_down_action(void)
{
#if __SFP28_ER__== 1
//  uint8_t chNo;
  
//  TXDIS_CDR = TXDIS_CDR_ON;
  
//  tx_cdr_init(1);
//  
//  // RX CDRs
//  rx_cdr_init(1);
  

#else

#endif

}

// Absolute value macro
#define ABS(num) (num < 0 ? -num: num)


#define _ADC_MON_BLOCK_ 1


void cal_Temp_Slope_Offset(void)
{
#if __SFP28_ER_SEMI_TUNABLE__ == 1
  
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
  
  FP32  tx_h_slope, tx_h_offset;
  FP32  tx_l_slope, tx_l_offset;
  signed int sDdm_value_h, sDdm_value_n, sDdm_value_l;
  A2_PAGE_80H_MEMORY_MAP	xdata * flashPtr;
  
  flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
//  upper_memory_map_ptr = (PAGE06H_MEMORY_MAP *)&I2C_Slave_Buffer_A0_P6_Up[0];
 
  sDdm_value_h = __swap_bytes(flashPtr->ht_temp);
  sDdm_value_n = __swap_bytes(flashPtr->nt_temp);
  sDdm_value_l = __swap_bytes(flashPtr->lt_temp);
  
  if (sDdm_value_h <  (signed int)0x4100) // 65C ����
  {
    sDdm_value_h = (signed int)RAW_HIGH_TEMP_IT_VALUE;
  }

  if (sDdm_value_n <  (signed int)0x0F00) // 15C ����
  {
    sDdm_value_n = (signed int)RAW_ROOM_TEMP_IT_VALUE;
  }

//  if (sDdm_value_l <  (signed int)0xE100) // -30C ����
  if (sDdm_value_l <  (signed int)0xEC00) // -20C ����
  {
    sDdm_value_l = (signed int)RAW_LOW_TEMP_IT_VALUE;
  }

  tx_h_slope = ((FP32)(21760.0-6400.0)) / ((FP32)sDdm_value_h - (FP32)sDdm_value_n); // 21,760 -> 0x5500 (85 C), 17920 -> 0x4600 (70 C), 6400 -> 0x1900
  
  tx_h_offset = (FP32)6400.0 - (FP32)(((FP32)tx_h_slope) * ((FP32)sDdm_value_n));
  
//  tx_l_slope = ((FP32)(6400.0+7680.0)) / ((FP32)sDdm_value_n - (FP32)sDdm_value_l); // - 7,680 -> - 0x1E00 (0xE100) (-30 C), 
  tx_l_slope = ((FP32)(6400.0+5120.0)) / ((FP32)sDdm_value_n - (FP32)sDdm_value_l); // - 5,120 -> - 0x1400 (0xEC00) (-20 C), 
  
  tx_l_offset = (FP32)(6400.0)  - (FP32)(((FP32)tx_l_slope) * ((FP32)sDdm_value_n));
  
  itemp_ht_slope = tx_h_slope;
  itemp_ht_offset = tx_h_offset;
  itemp_lt_slope = tx_l_slope;
  itemp_lt_offset = tx_l_offset;
  
//  upper_memory_map_ptr->h_slope = __swap_bytes_to_float(itemp_ht_slope);
//  upper_memory_map_ptr->h_offset = __swap_bytes_to_float(itemp_ht_offset);
//  upper_memory_map_ptr->l_slope = __swap_bytes_to_float(itemp_lt_slope);
//  upper_memory_map_ptr->l_offset = __swap_bytes_to_float(itemp_lt_offset);
  
#else
  
  FP32  tx_h_slope, tx_h_offset;
  FP32  tx_l_slope, tx_l_offset;
  signed int sDdm_value_h, sDdm_value_n, sDdm_value_l;
  A2_PAGE_80H_MEMORY_MAP	xdata * flashPtr;
  
  flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
//  upper_memory_map_ptr = (PAGE06H_MEMORY_MAP *)&I2C_Slave_Buffer_A0_P6_Up[0];
 
  sDdm_value_h = __swap_bytes(flashPtr->ht_temp);
  sDdm_value_n = __swap_bytes(flashPtr->nt_temp);
  sDdm_value_l = __swap_bytes(flashPtr->lt_temp);
  
  if (sDdm_value_h <  (signed int)0x4100) // 65C ����
  {
    sDdm_value_h = (signed int)RAW_HIGH_TEMP_IT_VALUE;
  }

  if (sDdm_value_n <  (signed int)0x0F00) // 15C ����
  {
    sDdm_value_n = (signed int)RAW_ROOM_TEMP_IT_VALUE;
  }

//  if (sDdm_value_l <  (signed int)0xE100) // -30C ����
  if (sDdm_value_l <  (signed int)0xEC00) // -20C ����
  {
    sDdm_value_l = (signed int)RAW_LOW_TEMP_IT_VALUE;
  }

  tx_h_slope = ((FP32)(21760.0-6400.0)) / ((FP32)sDdm_value_h - (FP32)sDdm_value_n); // 21,760 -> 0x5500 (85 C), 17920 -> 0x4600 (70 C), 6400 -> 0x1900
  
  tx_h_offset = (FP32)6400.0 - (FP32)(((FP32)tx_h_slope) * ((FP32)sDdm_value_n));
  
//  tx_l_slope = ((FP32)(6400.0+7680.0)) / ((FP32)sDdm_value_n - (FP32)sDdm_value_l); // - 7,680 -> - 0x1E00 (0xE100) (-30 C), 
  tx_l_slope = ((FP32)(6400.0+5120.0)) / ((FP32)sDdm_value_n - (FP32)sDdm_value_l); // - 5,120 -> - 0x1400 (0xEC00) (-20 C), 
  
  tx_l_offset = (FP32)(6400.0)  - (FP32)(((FP32)tx_l_slope) * ((FP32)sDdm_value_n));
  
  itemp_ht_slope = tx_h_slope;
  itemp_ht_offset = tx_h_offset;
  itemp_lt_slope = tx_l_slope;
  itemp_lt_offset = tx_l_offset;
  
//  upper_memory_map_ptr->h_slope = __swap_bytes_to_float(itemp_ht_slope);
//  upper_memory_map_ptr->h_offset = __swap_bytes_to_float(itemp_ht_offset);
//  upper_memory_map_ptr->l_slope = __swap_bytes_to_float(itemp_lt_slope);
//  upper_memory_map_ptr->l_offset = __swap_bytes_to_float(itemp_lt_offset);
  
#endif

#else
  
  FP32  tx_h_slope, tx_h_offset;
  FP32  tx_l_slope, tx_l_offset;
  signed int sDdm_value_h, sDdm_value_n, sDdm_value_l;
  A2_PAGE_80H_MEMORY_MAP	xdata * flashPtr;
  
  flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
//  upper_memory_map_ptr = (PAGE06H_MEMORY_MAP *)&I2C_Slave_Buffer_A0_P6_Up[0];
 
  sDdm_value_h = __swap_bytes(flashPtr->ht_temp);
  sDdm_value_n = __swap_bytes(flashPtr->nt_temp);
  sDdm_value_l = __swap_bytes(flashPtr->lt_temp);
  
  if (sDdm_value_h <  (signed int)0x4100) // 65C ����
  {
    sDdm_value_h = (signed int)RAW_HIGH_TEMP_CT_VALUE;
  }

  if (sDdm_value_n <  (signed int)0x0F00) // 15C ����
  {
    sDdm_value_n = (signed int)RAW_ROOM_TEMP_CT_VALUE;
  }

  if (sDdm_value_l <  (signed int)0xF600) // -10C ����
  {
    sDdm_value_l = (signed int)RAW_LOW_TEMP_CT_VALUE;
  }

  tx_h_slope = ((FP32)(17920.0-6400.0)) / ((FP32)sDdm_value_h - (FP32)sDdm_value_n); // 19200 -> 0x4600, 6400 -> 0x1900
  
  tx_h_offset = (FP32)6400.0 - (FP32)(((FP32)tx_h_slope) * ((FP32)sDdm_value_n));
  
  tx_l_slope = ((FP32)(6400.0-0.0)) / ((FP32)sDdm_value_n - (FP32)sDdm_value_l);
  
  tx_l_offset = (FP32)(6400.0)  - (FP32)(((FP32)tx_l_slope) * ((FP32)sDdm_value_n));
  
  itemp_ht_slope = tx_h_slope;
  itemp_ht_offset = tx_h_offset;
  itemp_lt_slope = tx_l_slope;
  itemp_lt_offset = tx_l_offset;
  
//  upper_memory_map_ptr->h_slope = __swap_bytes_to_float(itemp_ht_slope);
//  upper_memory_map_ptr->h_offset = __swap_bytes_to_float(itemp_ht_offset);
//  upper_memory_map_ptr->l_slope = __swap_bytes_to_float(itemp_lt_slope);
//  upper_memory_map_ptr->l_offset = __swap_bytes_to_float(itemp_lt_offset);
  
#endif
  
}


// TX Power Monitoring
#if __NEW_TX_POWER_MON_BY_TEMPERATURE__==1
//
//FP32  ht_slope[4];
//FP32  ht_offset[4];
//FP32  lt_slope[4];
//FP32  lt_offset[4];

void calSlope_Offset(unsigned char chNo)
{
  FP32  tx_h_slope, tx_h_offset;
  FP32  tx_l_slope, tx_l_offset;
//  signed int temparature_value;
//  FP32 xdata p, f_x1, f_x2, f_y1, f_y2;
//  uint16_t cV, unDdm_value, unDdm_value_1;
  uint16_t unDdm_value_h, unDdm_value_n, unDdm_value_l;
//  signed short  sDdm_value; 
//  uint16_t * xdata tmp_ptr;
//  A2_LOWER_MEMORY_MAP * xdata lowerMemoryMapPtr;
  A2_PAGE_80H_MEMORY_MAP	xdata * flashPtr;
  
  flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];

//  lowerMemoryMapPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];
   
  unDdm_value_h = __swap_bytes(flashPtr->txPower_at_highTemp);
  unDdm_value_n = __swap_bytes(flashPtr->txPower_at_normalTemp);
  unDdm_value_l = __swap_bytes(flashPtr->txPower_at_lowTemp);
  
  tx_h_slope = ((FP32)unDdm_value_h - (FP32)unDdm_value_n)/(FP32)(7500.0-2500.0);
  
  tx_h_offset = ((FP32)unDdm_value_n) - (FP32)((FP32)tx_h_slope) * (FP32)2500.0;
  
  tx_l_slope = ((FP32)unDdm_value_n - (FP32)unDdm_value_l)/(FP32)(2500.0-0.0);
  
  tx_l_offset = ((FP32)unDdm_value_n) - (FP32)((FP32)tx_l_slope) * (FP32)2500.0;
  
  ht_slope = tx_h_slope;
  ht_offset = tx_h_offset;
  lt_slope = tx_l_slope;
  lt_offset = tx_l_offset;
  
}


void ddm_mon_tx_power(void) 
{
  // [DCLEE: 191114] Alarm ���� -->
//  FP32 xdata p,f1,f2,f3, f4;
  FP32 xdata p,f1,f2;
//  FP32 xdata * fpPtr;  
  uint16_t unDdm_value, unDdm_value_1, curr_temperature;
  signed short  sDdm_value; 
//  int xdata idx_s, idx_c;
//  uint16_t * xdata tmp_ptr;
  A2_LOWER_MEMORY_MAP * xdata lowerMemoryMapPtr;
//  A2_PAGE_80H_MEMORY_MAP	xdata * flashPtr;
  
//  flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];

  lowerMemoryMapPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];
   
  sDdm_value = __swap_bytes(lowerMemoryMapPtr->A2_TEMPERATURE);
  
  if (sDdm_value < 0)
  {
    curr_temperature = 0;
    unDdm_value = 0;
  }
  else
  {
    unDdm_value = (sDdm_value >> 8) & 0x00FF;
    unDdm_value = unDdm_value * 100;
    curr_temperature = unDdm_value;
    
  }
  
  if ((sfp28_module_state & SFP28_MODULE_STATE_READY) != SFP28_MODULE_STATE_READY)
  {
    p = 0;
    unDdm_value_1 = p*10.0;
    
    //        tmp_ptr = (uint16_t *)&I2C_Slave_Buffer_A2_P00H_Up[(UPPER_MEMORY_PAGE0_MPDn_ADC(idx_c) & 0x7F)];
    //        *tmp_ptr = __swap_bytes(unDdm_value);
#if __HFR_REQ_DDM_FLAG_VER__==1
    if (ddm_tx_power_flag == 0)
    {
      lowerMemoryMapPtr->A2_TX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
    }
    else if (ddm_tx_power_flag > 20)
    {
      ddm_tx_power_flag = 0;
      lowerMemoryMapPtr->A2_TX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
    }
    else
    {
      ddm_tx_power_flag++;
    }

#else    
    lowerMemoryMapPtr->A2_TX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
#endif
    
  }
  else
  {
    
    
    if (curr_temperature > 2500)
    { // High Temperature Processing
      f1 = ht_slope;
      f2 = ht_offset;
      
    }
    else
    { // Low Temperature Processing
      f1 = lt_slope;
      f2 = lt_offset;        
    }
    
    p = (FP32)unDdm_value;
    
//    cV = 1000;     
    
    p = f1 * p + f2;
    
    if( p<0 )	p=0;
    
    
    unDdm_value_1 = (unsigned int)p;
    
#if __HFR_REQ_DDM_FLAG_VER__==1
    if (ddm_tx_power_flag == 0)
    {
      lowerMemoryMapPtr->A2_TX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
    }
    else if (ddm_tx_power_flag > 20)
    {
      ddm_tx_power_flag = 0;
      lowerMemoryMapPtr->A2_TX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
    }
    else
    {
      ddm_tx_power_flag++;
    }

#else    
    lowerMemoryMapPtr->A2_TX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
#endif
    
  }
  
}

#else

void ddm_mon_tx_power(void) 
{
#if __SFP28_ER_SEMI_TUNABLE__ == 1
  
  // [DCLEE: 191114] Alarm ���� -->
//  FP32 xdata p,f1,f2,f3, f4;
  FP32 xdata p,f1;
//  FP32 xdata * fpPtr;  
  uint16_t unDdm_value;
  unsigned long unDdm_value_1;
//  signed short  sDdm_value; 
//  int xdata idx_s, idx_c;
  A2_PAGE_80H_MEMORY_MAP	xdata * flashPtr;
//  uint16_t * xdata tmp_ptr;
  A2_LOWER_MEMORY_MAP * xdata lowerMemoryMapPtr;

  lowerMemoryMapPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];
  
  flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
  
//  if ((sfp28_module_state & SFP28_MODULE_STATE_READY) != SFP28_MODULE_STATE_READY)
//  {
//    unDdm_value = ADC_ReadOut(CONFG_TX_PWR_NON);                                      //Read data
//    p = 0;
//    //        unDdm_value = p;
//    unDdm_value_1 = p*10.0;
//    
//    tmp_ptr = (uint16_t *)&I2C_Slave_Buffer_A0_P0_Up[(UPPER_MEMORY_PAGE0_MPDn_ADC(idx_c) & 0x7F)];
//    *tmp_ptr = __swap_bytes(unDdm_value);
//    
//  }
  
//  if ((curr_channel_no >= 1) && (curr_channel_no <= 4))
//  {
//    t_chNo = curr_channel_no - 1;
//  }
//  else
//  {
//    t_chNo = 0; // curr_channel_no = 1
//  }        
  
  unDdm_value = ADC_ReadOut(CONFG_TX_PWR_NON);                                      //Read data
  
  p = (FP32)unDdm_value;
  
//  cV = 1000;
  
  f1 = p;
//  p = f1*txPower_coeff_1[t_chNo] + txPower_coeff_0[t_chNo];
  p = f1*txPower_coeff_1 + txPower_coeff_0;
  
  if( p<0 )	p=0;
    
  unDdm_value_1 = (unsigned long)p*10.0;
  //      unDdm_value_1 = 9000;
  
  // External Calibration ���� fucntion �� �߰� �ʿ�
  // ...
  // 
  
  if(TXDStatus() == ASSERTED)                                                 //report back 1 when laser is off
  {
    unDdm_value_1 = 0x0001;      
  }
  
  if(unDdm_value_1 < 1)
  {
    unDdm_value_1 = 1;                                                          //limit min DDM value to 1, means -40dBm
  }
  else if (unDdm_value_1 > 65535)
  {
    unDdm_value_1 = 65535;
  }
  
#if __HFR_REQ_DDM_FLAG_VER__==1
    if (ddm_tx_power_flag == 0)
    {
      lowerMemoryMapPtr->A2_TX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
      flashPtr->mpd_adc = __swap_bytes(unDdm_value);
    }
    else if (ddm_tx_power_flag > 20)
    {
      ddm_tx_power_flag = 0;
      lowerMemoryMapPtr->A2_TX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
      flashPtr->mpd_adc = __swap_bytes(unDdm_value);
    }
    else
    {
      ddm_tx_power_flag++;
    }

#else    
  lowerMemoryMapPtr->A2_TX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
  flashPtr->mpd_adc = __swap_bytes(unDdm_value);
#endif
  
  
//  tmp_ptr = (uint16_t *)&I2C_Slave_Buffer_A0_P0_Up[(UPPER_MEMORY_PAGE0_MPDn_ADC(idx_c) & 0x7F)];
//  *tmp_ptr = __swap_bytes(unDdm_value);
  
  
#else
  
  // [DCLEE: 191114] Alarm ���� -->
  FP32 xdata p,f1,f2,f3, f4;
  FP32 xdata * fpPtr;  
  uint16_t cV, unDdm_value, unDdm_value_1;
  signed short  sDdm_value; 
  int xdata idx_s, idx_c;
  flashStructType	xdata * flashPtr;
  uint16_t * xdata tmp_ptr;
  LOWER_MEMORY_MAP * xdata lowerMemoryMapPtr;

  lowerMemoryMapPtr = (LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A0[0];
  
  flashPtr = (flashStructType *)&I2C_Slave_Buffer_A4_Local_Memory[0];
  
  for (idx_s=0; idx_s<MAX_TRX_SIGNALS; idx_s++)
  {
    for (idx_c=0; idx_c < MAX_CHANNELS_PER_SIGNAL ; idx_c++)
    {
      if ((qsfp_module_state & QSFP_MODULE_STATE_READY) != QSFP_MODULE_STATE_READY)
      {
        unDdm_value = ADC_ReadOut(CONFG_MPD0 + idx_c);                                      //Read data
        p = 0;
        //        unDdm_value = p;
        unDdm_value_1 = p*10.0;
        
        tmp_ptr = (uint16_t *)&I2C_Slave_Buffer_A0_P0_Up[(UPPER_MEMORY_PAGE0_MPDn_ADC(idx_c) & 0x7F)];
        *tmp_ptr = __swap_bytes(unDdm_value);
        
        continue;
      }
      unDdm_value = ADC_ReadOut(CONFG_MPD0 + idx_c);                                      //Read data
      
      p = (FP32)unDdm_value;
      
      //			if (idx_c == 0)
      //			{
      //				fpPtr = (FP32 *)&I2C_Slave_Buffer_A0_P1_Up[UPPER_MEMORY_PAGE1_TXPWR_F1_ADC(idx_c) & 0x7F];
      //				*fpPtr = p;
      //			}
      
      cV = 1000;
      // flashPtr->txPowerMonCal[idx_s][idx_c];
//      p = p * (FP32)cV * 0.001;
      
      f1 = p;
      //			if (idx_c == 0)
      //			{
      //				fpPtr = (FP32 *)&I2C_Slave_Buffer_A0_P1_Up[UPPER_MEMORY_PAGE1_TXPWR_R1_ADC(idx_c) & 0x7F];
      //				*fpPtr = f1;
      //			}
      
      //      f2 = f1 * p;
      //      f3 = f2 * p;
      //      // Coefficient processing, by Sean, 2011.03.22. -->
      //      f4 = f3 * p;
      //      // Coefficient processing, by Sean, 2011.03.22. <--
      //      //f5 = f4 * p;
      //      //p = f5*(1.51088E-9) + f4*(-9.71769E-6) + f3*(0.02497) + f2*(-32.0141) + f1*(20488.82202) + (-5.23507E+6);
      //      // Coefficient processing, by Sean, 2011.03.22. -->
      //      /*
      //      * p = f3*(1.94089E-4) + f2*(-0.78682) + f1*(1066.65852) + (-482931.1956);
      //      */
      //      p = f4*txPower_coeff_4[idx_s][idx_c] + f3*txPower_coeff_3[idx_s][idx_c] + f2*txPower_coeff_2[idx_s][idx_c] + f1*txPower_coeff_1[idx_s][idx_c] + txPower_coeff_0[idx_s][idx_c];
      p = f1*txPower_coeff_1[idx_s][idx_c] + txPower_coeff_0[idx_s][idx_c];
      // Coefficient processing, by Sean, 2011.03.22. <--
      /*
      */
      //			if (idx_c == 0)
      //			{
      //				fpPtr = (FP32 *)&I2C_Slave_Buffer_A0_P1_Up[UPPER_MEMORY_PAGE1_TXPWR_E1_ADC(idx_c) & 0x7F];
      //				*fpPtr = p;
      //			}
      
      if( p<0 )	p=0;
      
      //			if (idx_c == 0)
      //			{
      //				fpPtr = (FP32 *)&I2C_Slave_Buffer_A0_P1_Up[UPPER_MEMORY_PAGE1_TXPWR_E0_ADC(idx_c) & 0x7F];
      //				*fpPtr = p;
      //
      ////				fpPtr = (FP32 *)&I2C_Slave_Buffer_A0_P1_Up[UPPER_MEMORY_PAGE1_TXPWR_E3_ADC(idx_c) & 0x7F];
      ////				*fpPtr = txPower_coeff_1[idx_s][idx_c];
      ////
      ////				fpPtr = (FP32 *)&I2C_Slave_Buffer_A0_P1_Up[UPPER_MEMORY_PAGE1_TXPWR_E4_ADC(idx_c) & 0x7F];
      ////				*fpPtr = txPower_coeff_0[idx_s][idx_c];
      //
      //
      //			}
      
      //      TxPwrMon[idx_s][idx_c] = p;
      unDdm_value_1 = (unsigned int)p*10.0;
//      unDdm_value_1 = 9000;
      lowerMemoryMapPtr->TX_POWER[idx_c] = __swap_bytes((uint16_t)unDdm_value_1);
      
      tmp_ptr = (uint16_t *)&I2C_Slave_Buffer_A0_P0_Up[(UPPER_MEMORY_PAGE0_MPDn_ADC(idx_c) & 0x7F)];
      *tmp_ptr = __swap_bytes(unDdm_value);
    }
    
  }

//	// Tx Power Mon: Network Lanes
//	tmpVal = (INT16U)TxPwrMonT[0][0];
//	lowerMemoryMapPtr->TX1_POWER = (uint16_t)tmpVal;
//
//	tmpVal = (INT16U)TxPwrMonT[0][1];
//	lowerMemoryMapPtr->TX2_POWER = (uint16_t)tmpVal;
//
//	tmpVal = (INT16U)TxPwrMonT[0][2];
//	lowerMemoryMapPtr->TX3_POWER = (uint16_t)tmpVal;
//
//	tmpVal = (INT16U)TxPwrMonT[0][3];
//	lowerMemoryMapPtr->TX4_POWER = (uint16_t)tmpVal;
  
#endif
}

#endif

void ddm_mon_rx_power(void)
{
  // [DCLEE: 191114] Alarm ���� -->
  FP32 xdata p,f1,f2,f3, f4;
//  FP32 xdata * fpPtr;  
  uint16_t unDdm_value, unDdm_value_1;
//  signed short  sDdm_value; 
//  int xdata idx_s, idx_c;
//  uint16_t * xdata tmp_ptr;
  A2_LOWER_MEMORY_MAP * xdata lowerMemoryMapPtr;
  A2_PAGE_80H_MEMORY_MAP	xdata * flashPtr, * controlMemoryPtr_1;
  A2_PAGE_81H_MEMORY_MAP	xdata * flashPtr_1;
  uint16_t los_assert_threshold, los_deassert_threshold;
  unsigned char read_data[4];
  
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE_SW_VER_2__ == 1
  // [DCLEE: 2021.04.08.] �µ����� RSSI ���� �����ϴ� ��ƾ�� �߰�
  uint16_t unDdm_value_2;
  signed char  curr_temp, reference_temp, ht_temp, lt_temp, ddm_curr_temp;
  
  ddm_curr_temp = (signed char)I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_TEMPERATURE];
  reference_temp = (signed char)I2C_Slave_Buffer_A2_P80H_Up[FLASH_NT_TEMP];
  ht_temp = (signed char)I2C_Slave_Buffer_A2_P80H_Up[FLASH_HT_TEMP];
  lt_temp = (signed char)I2C_Slave_Buffer_A2_P80H_Up[FLASH_LT_TEMP];
  curr_temp = (signed char)I2C_Slave_Buffer_A2_P80H_Up[FLASH_RAW_CURRENT_TEMP];

#endif
  
#if __LOS_ASSERT_ENABLE__==1
  unsigned char p_los_flag, mask_flag;  
#endif
  
//      I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_RESERVED_77] = I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_RESERVED_77] + 1;

//            I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_READ_CHIP_STATUS] = rx_los_flag_after_isr;

//  if (rx_los_flag_after_isr != 0)
//  {
//    rx_los_flag_after_isr=0;
//    return;
//  }
            
//      I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_READ_CHIP_STATUS] = I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_READ_CHIP_STATUS] + 1;
//        I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_OPERATION_MODE] = I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_OPERATION_MODE] + 1;
//        I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_LUT_MODE] = I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_LUT_MODE] + 1;

  flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
  flashPtr_1 = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P81H_Up[0];

  lowerMemoryMapPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];
  controlMemoryPtr_1 = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_Pn_Up[0];
  
  los_assert_threshold = __swap_bytes(flashPtr_1->idcn);
  los_deassert_threshold = __swap_bytes(flashPtr_1->idcd);
  
  if (los_assert_threshold > 21)
  {
    los_assert_threshold = LOS_ASSERTION_THRESHOLD;
  }
  
  if (los_deassert_threshold > 31)
  {
    los_deassert_threshold = LOS_DEASSERTION_THRESHOLD;
  }
//            I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_OPERATION_MODE] = I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_OPERATION_MODE] + 1;

#if __LOS_ASSERT_ENABLE__==1
  p_los_flag = lowerMemoryMapPtr->A2_STATUS_CONTROL; // RXLOS State: [1]
  
  mask_flag = 0x01;
  flashPtr->curr_los_flag = 0;
#endif
 
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
  
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE_HW_VER_2__ == 1

  unDdm_value = ADC_ReadOut(CONFG_RSSI);                                      //Read data
    
#else
  
//      I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_RESERVED_77] = I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_RESERVED_77] + 1;
//        I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_LUT_MODE] = I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_LUT_MODE] + 1;

// #if __HSFP_10G_ER_SEMI_TUNABLE__==1
//   unDdm_value = ADC_ReadOut(CONFG_RSSI);                                      //Read data
  
// #else

  // GN_1157
  read_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_ADC_9, 2, &read_data[0]);
  
  unDdm_value =   __swap_bytes(*(unsigned int *)(&read_data[0]));
  
// #endif
  
#if __RX_LOS_DDM_NO_FILTER__==1
  if (unDdm_value == 0)
  {
    unDdm_value = 1;
  }
#endif

//  unDdm_value = read_data[0];
//  unDdm_value = ((unDdm_value << 8) & 0xFF00);
//  unDdm_value += read_data[0];
  
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE_SW_VER_2__ == 1
  // [DCLEE: 2021.04.08.] �µ����� RSSI ���� �����ϴ� ��ƾ�� �߰�
  unDdm_value_2 = unDdm_value;
  
  if (curr_temp > reference_temp)
  {
    // High Temp. Control, HIGH_TEMP_OFFSET_VALUE
    
  }
  else
  {
    // Low Temp. Control, LOW_TEMP_OFFSET_VALUE
    
  }
  
#endif

  
#endif
  
#else

  unDdm_value = ADC_ReadOut(CONFG_RSSI);                                      //Read data

#endif
  
  p = (FP32)unDdm_value;
  
//  cV = 1000; // flashPtr->txPowerMonCal[idx_s][idx_c];
  
  f1 = p;
  f2 = f1 * p;
  f3 = f2 * p;
  // Coefficient processing, by Sean, 2011.03.22. -->
  f4 = f3 * p;
  p = f4*rxPower_coeff_4 + f3*rxPower_coeff_3 + f2*rxPower_coeff_2 + f1*rxPower_coeff_1 + rxPower_coeff_0;
  // Coefficient processing, by Sean, 2011.03.22. <--
  if( p<0 )	p=0;
  unDdm_value_1 = p*10.0;
      
#if __LOS_ASSERT_ENABLE__==1
      // [DCLEE] 200319 --> LOS ASSERT & DEASSERT Update
      
      mask_flag = 0x02;
      
      if ((p_los_flag & mask_flag) == mask_flag)
      { // los status
//        if (unDdm_value_1 <= LOS_DEASSERTION_THRESHOLD)
        if (unDdm_value_1 <= los_deassert_threshold)
        {
          // set los alarm
      // [DCLEE] 210513 --> LOS PLA ���Ȯ��
          PLA_Soft_RX_LOS_Control(ASSERTED);
      // [DCLEE] 210513 <-- LOS PLA ���Ȯ��
#if __HFR_REQ_DDM_FLAG_VER__==1
          if (ddm_rx_power_flag == 0)
          {
#if __RX_LOS_DDM_NO_FILTER__==1
            
            if (INT_INPUT_RX_LOS_uC == 1)
            {
              unDdm_value_1 = 0;     
            }
            lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);          
#else     
            lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)0);
#endif
          }
          else if (ddm_rx_power_flag > 20)
          {
            ddm_rx_power_flag = 0;
#if __RX_LOS_DDM_NO_FILTER__==1
            
            if (INT_INPUT_RX_LOS_uC == 1)
            {
              unDdm_value_1 = 0;     
            }
            lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);          
#else     
            lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)0);
#endif
          }
          else
          {
            ddm_rx_power_flag++;
          }
          
#else    
    
#if __RX_LOS_DDM_NO_FILTER__==1
          if (INT_INPUT_RX_LOS_uC == 1)
          {
            unDdm_value_1 = 0;     
          }

          lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);          
#else     
          lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)0);
#endif

#endif
          
          flashPtr->curr_los_flag |= mask_flag;
          

        }
        else
        {
          // clear los_alarm 
      // [DCLEE] 210513 --> LOS PLA ���Ȯ��
          PLA_Soft_RX_LOS_Control(DE_ASSERTED);
      // [DCLEE] 210513 <-- LOS PLA ���Ȯ��
#if __HFR_REQ_DDM_FLAG_VER__==1
          if (ddm_rx_power_flag == 0)
          {
            lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
          }
          else if (ddm_rx_power_flag > 20)
          {
            ddm_rx_power_flag = 0;
            lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
          }
          else
          {
            ddm_rx_power_flag++;
          }

#else    
          lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
#endif
          
        }
      }
      else
      {
//        if (unDdm_value_1 <= LOS_ASSERTION_THRESHOLD)
        if (unDdm_value_1 <= los_assert_threshold)
        {
          // set los_alarm
      // [DCLEE] 210513 --> LOS PLA ���Ȯ��
          PLA_Soft_RX_LOS_Control(ASSERTED);
      // [DCLEE] 210513 <-- LOS PLA ���Ȯ��

#if __HFR_REQ_DDM_FLAG_VER__==1
          if (ddm_rx_power_flag == 0)
          {
#if __RX_LOS_DDM_NO_FILTER__==1
            if (INT_INPUT_RX_LOS_uC == 1)
            {
              unDdm_value_1 = 0;     
            }
            lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);          
#else     
            lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)0);
#endif
          }
          else if (ddm_rx_power_flag > 20)
          {
            ddm_rx_power_flag = 0;
#if __RX_LOS_DDM_NO_FILTER__==1
            if (INT_INPUT_RX_LOS_uC == 1)
            {
              unDdm_value_1 = 0;     
            }
            lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);          
#else     
            lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)0);
#endif
          }
          else
          {
            ddm_rx_power_flag++;
          }
          
#else    
          
#if __RX_LOS_DDM_NO_FILTER__==1
          if (INT_INPUT_RX_LOS_uC == 1)
          {
            unDdm_value_1 = 0;     
          }
          lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);          
#else     
          lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)0);
#endif
          
#endif
          flashPtr->curr_los_flag |= mask_flag;

        }
        else
        {
          // clear los_alarm 
      // [DCLEE] 210513 --> LOS PLA ���Ȯ��
          PLA_Soft_RX_LOS_Control(DE_ASSERTED);
      // [DCLEE] 210513 <-- LOS PLA ���Ȯ��
#if __HFR_REQ_DDM_FLAG_VER__==1
          if (ddm_rx_power_flag == 0)
          {
            lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
          }
          else if (ddm_rx_power_flag > 20)
          {
            ddm_rx_power_flag = 0;
            lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
          }
          else
          {
            ddm_rx_power_flag++;
          }

#else    
          lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
#endif
        }
      }
//      flashPtr->rx_power[idx_c] = __swap_bytes((uint16_t)unDdm_value_1);
//      tmp_ptr = (uint16_t *)&I2C_Slave_Buffer_A0_P0_Up[(UPPER_MEMORY_PAGE0_RSSIn_ADC(idx_c) & 0x7F)];
//      *tmp_ptr = __swap_bytes(unDdm_value);
      
      flashPtr->rssi_adc = __swap_bytes(unDdm_value);
      
      if (lowerMemoryMapPtr->A2_TABLE == 0x80)
      {
        controlMemoryPtr_1->rssi_adc = __swap_bytes(unDdm_value);              
      }
      
      // [DCLEE] 200319 <-- LOS ASSERT & DEASSERT Update

      // [DCLEE] 210513 --> LOS PLA ���Ȯ��
      
      lowerMemoryMapPtr->A2_RESERVED_6F = PI0;
//      I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_READ_CHIP_STATUS] = I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_READ_CHIP_STATUS] + 1;

//      lowerMemoryMapPtr->A2_RESERVED_77 = (lowerMemoryMapPtr->A2_RESERVED_77 + 1);
//    if(PI0_bit.PI07 == 0)                                                       //check the external TXD input
//    {
//      lowerMemoryMapPtr->A2_RESERVED_6F = 2;
//      
//    }
//    else if(PI0_bit.PI07 == 1)  
//    {
//      lowerMemoryMapPtr->A2_RESERVED_6F = 1;
//    }
//    else
//    {
//      lowerMemoryMapPtr->A2_RESERVED_6F = 4;
//      
//    }
      
      // [DCLEE] 210513 <-- LOS PLA ���Ȯ��

#else
      
#if __HFR_REQ_DDM_FLAG_VER__==1
      if (ddm_rx_power_flag == 0)
      {
        lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
      }
      else if (ddm_rx_power_flag > 20)
      {
        ddm_rx_power_flag = 0;
        lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
      }
      else
      {
        ddm_rx_power_flag++;
      }

#else    
  lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
#endif
  
  //      tmp_ptr = (uint16_t *)&I2C_Slave_Buffer_A0_P0_Up[(UPPER_MEMORY_PAGE0_RSSIn_ADC(idx_c) & 0x7F)];
  //      *tmp_ptr = __swap_bytes(unDdm_value);

#endif
}


void ddm_mon_rx_power_from_CDR(void)
{
  // [DCLEE: 191114] Alarm ���� -->
  FP32 xdata p,f1,f2,f3, f4;
//  FP32 xdata * fpPtr;  
  uint16_t unDdm_value, unDdm_value_1;
//  signed short  sDdm_value; 
//  int xdata idx_s, idx_c;
//  uint16_t * xdata tmp_ptr;
  A2_LOWER_MEMORY_MAP * xdata lowerMemoryMapPtr;
  A2_PAGE_80H_MEMORY_MAP	xdata * flashPtr;
  A2_PAGE_81H_MEMORY_MAP	xdata * flashPtr_1;
  uint16_t los_assert_threshold, los_deassert_threshold;
  
#if __LOS_ASSERT_ENABLE__==1
//  unsigned char p_los_flag, mask_flag;
  unsigned char mask_flag;
#endif
  
  flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
  flashPtr_1 = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P81H_Up[0];

  lowerMemoryMapPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];
  
  los_assert_threshold = __swap_bytes(flashPtr_1->idcn);
  los_deassert_threshold = __swap_bytes(flashPtr_1->idcd);
 
  if (los_assert_threshold > 21)
  {
    los_assert_threshold = LOS_ASSERTION_THRESHOLD;
  }
  
  if (los_deassert_threshold > 31)
  {
    los_deassert_threshold = LOS_DEASSERTION_THRESHOLD;
  }
  
#if __LOS_ASSERT_ENABLE__==1
//  p_los_flag = lowerMemoryMapPtr->A2_STATUS_CONTROL; // RXLOS State: [1]
  
  mask_flag = 0x01;
  flashPtr->curr_los_flag = 0;
#endif
 
  unDdm_value = ADC_ReadOut(CONFG_RSSI);                                      //Read data
  
#if __RX_LOS_DDM_NO_FILTER__==1
  if (unDdm_value == 0)
  {
   unDdm_value = 1; 
  }  
#endif

  p = (FP32)unDdm_value;
  
//  cV = 1000; // flashPtr->txPowerMonCal[idx_s][idx_c];
  
  f1 = p;
  f2 = f1 * p;
  f3 = f2 * p;
  // Coefficient processing, by Sean, 2011.03.22. -->
  f4 = f3 * p;
  p = f4*rxPower_coeff_4 + f3*rxPower_coeff_3 + f2*rxPower_coeff_2 + f1*rxPower_coeff_1 + rxPower_coeff_0;
  // Coefficient processing, by Sean, 2011.03.22. <--
  if( p<0 )	p=0;
  unDdm_value_1 = p*10.0;
      
#if __LOS_ASSERT_ENABLE__==1
        if (unDdm_value_1 <= los_deassert_threshold)
        {
          // set los alarm
          PLA_Soft_RX_LOS_Control(ASSERTED);
          
#if __HFR_REQ_DDM_FLAG_VER__==1
          if (ddm_rx_power_flag == 0)
          {
#if __RX_LOS_DDM_NO_FILTER__==1
            lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);          
#else     
            lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)0);
#endif
          }
          else if (ddm_rx_power_flag > 20)
          {
            ddm_rx_power_flag = 0;
#if __RX_LOS_DDM_NO_FILTER__==1
            lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);          
#else     
            lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)0);
#endif
          }
          else
          {
            ddm_rx_power_flag++;
          }

#else    

#if __RX_LOS_DDM_NO_FILTER__==1
          lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);          
#else     
          lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)0);
#endif
          
#endif
          
//          lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)0);
          flashPtr->curr_los_flag |= mask_flag;
          

        }
        else
        {
          // clear los_alarm 
          PLA_Soft_RX_LOS_Control(DE_ASSERTED);
#if __HFR_REQ_DDM_FLAG_VER__==1
          if (ddm_rx_power_flag == 0)
          {
            lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);

          }
          else if (ddm_rx_power_flag > 20)
          {
            ddm_rx_power_flag = 0;
            lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);

          }
          else
          {
            ddm_rx_power_flag++;
          }

#else    
          lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
#endif
          
        }
        
//      // [DCLEE] 200319 --> LOS ASSERT & DEASSERT Update
//      
//      mask_flag = 0x02;
//      
//      if ((p_los_flag & mask_flag) == mask_flag)
//      { // los status
////        if (unDdm_value_1 <= LOS_DEASSERTION_THRESHOLD)
//        if (unDdm_value_1 <= los_deassert_threshold)
//        {
//          // set los alarm
//          PLA_Soft_RX_LOS_Control(ASSERTED);
//#if __RX_LOS_DDM_NO_FILTER__==1
//          lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);          
//#else     
//          lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)0);
//#endif
////          lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)0);
//          flashPtr->curr_los_flag |= mask_flag;
//          
//
//        }
//        else
//        {
//          // clear los_alarm 
//          PLA_Soft_RX_LOS_Control(DE_ASSERTED);
//          lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
//        }
//      }
//      else
//      {
////        if (unDdm_value_1 <= LOS_ASSERTION_THRESHOLD)
//        if (unDdm_value_1 <= los_assert_threshold)
//        {
//          // set los_alarm
//          PLA_Soft_RX_LOS_Control(ASSERTED);
//#if __RX_LOS_DDM_NO_FILTER__==1
//          lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);          
//#else     
//          lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)0);
//#endif
////          lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)0);
//          flashPtr->curr_los_flag |= mask_flag;
//
//        }
//        else
//        {
//          // clear los_alarm 
//          PLA_Soft_RX_LOS_Control(DE_ASSERTED);
//          lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
//        }
//      }
////      flashPtr->rx_power[idx_c] = __swap_bytes((uint16_t)unDdm_value_1);
////      tmp_ptr = (uint16_t *)&I2C_Slave_Buffer_A0_P0_Up[(UPPER_MEMORY_PAGE0_RSSIn_ADC(idx_c) & 0x7F)];
////      *tmp_ptr = __swap_bytes(unDdm_value);
      
      flashPtr->rssi_adc = __swap_bytes(unDdm_value);
      
      lowerMemoryMapPtr->A2_RESERVED_6F = PI0;
          
      // [DCLEE] 200319 <-- LOS ASSERT & DEASSERT Update
      
#else
      
#if __HFR_REQ_DDM_FLAG_VER__==1
      if (ddm_rx_power_flag == 0)
      {
        lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
        
      }
      else if (ddm_rx_power_flag > 20)
      {
        ddm_rx_power_flag = 0;
        lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
        
      }
      else
      {
        ddm_rx_power_flag++;
      }

#else    
  lowerMemoryMapPtr->A2_RX_POWER = __swap_bytes((uint16_t)unDdm_value_1);
#endif
  
  //      tmp_ptr = (uint16_t *)&I2C_Slave_Buffer_A0_P0_Up[(UPPER_MEMORY_PAGE0_RSSIn_ADC(idx_c) & 0x7F)];
  //      *tmp_ptr = __swap_bytes(unDdm_value);

#endif
}

//-----------------------------------------------------------------------------
// PLA_Soft_RXLOS_Control function
//   - Set PLA2 soft control, 1 or 0 (SB1)
//-----------------------------------------------------------------------------
void PLA_Soft_RX_LOS_Control(unsigned char unControl)
{
#if __SFP28_ER__== 1
  
#if __SFP28_ER_SEMI_TUNABLE__ == 1

  
  if(unControl == ASSERTED)
  {
    if (INT_INPUT_RX_LOS_uC == 0)
    {
      __disable_interrupt();  

      if (rx_los_flag_after_isr == 0)
      {
        PLACNT2_bit.SB1 = 1;                                                       //Set High for TX disable assert
      }
      __enable_interrupt();  
      if (rx_los_flag_after_isr == 0)
      {
        rx_cdr_forced_mute_enable(ASSERTED);
      }
     }
  }
  else
  {
    if (INT_INPUT_RX_LOS_uC == 0)
    {
      __disable_interrupt();  
      if (rx_los_flag_after_isr == 0)
      {
        PLACNT2_bit.SB1 = 0;                                                       //Set Low for TX disable de-assert
      }
      __enable_interrupt();  
      if (rx_los_flag_after_isr == 0)
      {
        rx_cdr_forced_mute_enable(DE_ASSERTED);
      }
    }
  }

  
//  if(unControl == ASSERTED)
//  {
////     PLACNT2_bit.SB1 = 1;                                                       //Set High for TX disable assert
//     rx_cdr_forced_mute_enable(ASSERTED);
//  }
//  else
//  {
////     PLACNT2_bit.SB1 = 0;                                                       //Set Low for TX disable de-assert
//     rx_cdr_forced_mute_enable(DE_ASSERTED);
//  }
//    
#endif
  
#else
 
#endif
  
}

// [DCLEE] 210513 --> LOS PLA ���Ȯ��

void PLA_Soft_RX_LOS_Control_from_CDR(unsigned char unControl)
{
#if __SFP28_ER__== 1
  
#if __SFP28_ER_SEMI_TUNABLE__ == 1
   
//  rx_los_flag_before_isr = 1;
//  rx_los_flag_after_isr = 1;
  rx_los_flag_before_isr += 1;
  rx_los_flag_after_isr += 1;
  
  if (INT_INPUT_RX_LOS_uC == 1)
  {
    // Assert RX_LOS
  __disable_interrupt();  
     PLACNT2_bit.SB1 = 1;                                                       //Set High for TX disable assert
  __enable_interrupt();  
     rx_cdr_forced_mute_enable(ASSERTED);    
  }
  else if(unControl == ASSERTED)
  {
    // Assert RX_LOS
  __disable_interrupt();  
     PLACNT2_bit.SB1 = 1;                                                       //Set High for TX disable assert
  __enable_interrupt();  
     rx_cdr_forced_mute_enable(ASSERTED);        
  }
  else
  {
    // De-Assert RX_LOS
  __disable_interrupt();  
     PLACNT2_bit.SB1 = 0;                                                       //Set High for TX disable assert
  __enable_interrupt();  
    
  }
  rx_los_flag_before_isr = 0;
  
#if 0
  __disable_interrupt();  
  
  rx_los_flag_before_isr = 1;
  rx_los_flag_after_isr = 1;


//  PLA_Soft_RX_LOS_Control(unControl);
  
  if(unControl == ASSERTED)
  {
//     PLACNT2_bit.SB2 = 1;                                                       //Set High for TX disable assert
     PLACNT2_bit.SB1 = 1;                                                       //Set High for TX disable assert
     rx_cdr_forced_mute_enable(ASSERTED);
  }
  else
  {
//     PLACNT2_bit.SB2 = 0;                                                       //Set Low for TX disable de-assert
     PLACNT2_bit.SB1 = 0;                                                       //Set Low for TX disable de-assert
//     PLACNT2_bit.SB2 = 0;                                                       //Set Low for TX disable de-assert
//     ddm_mon_rx_power_from_CDR();
//     rx_cdr_forced_mute_enable(DE_ASSERTED);
  }
  
  rx_los_flag_before_isr = 0;
  __enable_interrupt();  

//  __disable_interrupt();  
//  
////  PLA_Soft_RX_LOS_Control(unControl);
//  
//  if(unControl == ASSERTED)
//  {
//     PLACNT2_bit.SB2 = 1;                                                       //Set High for TX disable assert
////     PLACNT2_bit.SB1 = 1;                                                       //Set High for TX disable assert
////     rx_cdr_forced_mute_enable(ASSERTED);
//  }
//  else
//  {
////     PLACNT2_bit.SB2 = 0;                                                       //Set Low for TX disable de-assert
////     PLACNT2_bit.SB1 = 0;                                                       //Set Low for TX disable de-assert
//     PLACNT2_bit.SB2 = 0;                                                       //Set Low for TX disable de-assert
////     rx_cdr_forced_mute_enable(DE_ASSERTED);
//  }
//  __enable_interrupt();  
    
#endif
  
#endif
  
#else
 
#endif
  
}

// [DCLEE] 210513 <-- LOS PLA ���Ȯ��

unsigned char PLA_RX_LOS_Status(void)
{
#if __SFP28_ER_SEMI_TUNABLE__ == 1
  if (PLACNT2_bit.PLA_OUT == 1)
  {
    // RX LOS �߻�
    return (ASSERTED);
  }
  else
  {
    // RX LOS ����
    return (DE_ASSERTED);
    
  }
#endif
  
}


unsigned char PLA_Tx_Fault_Status(void)
{
#if __SFP28_ER_SEMI_TUNABLE__ == 1
  if (PLACNT3_bit.PLA_OUT == 1)
  {
    // Tx Fault �߻�
    return (ASSERTED);
  }
  else
  {
    // Tx Fault ����
    return (DE_ASSERTED);
    
  }
#endif
  
}

void PLA_Soft_Tx_Fault_Control(unsigned char unControl)
{
#if __SFP28_ER__== 1
  
#if __SFP28_ER_SEMI_TUNABLE__ == 1
  
  if(unControl == ASSERTED)
  {
     PLACNT3_bit.SB1 = 1;                                                       //Set High for TX Fault assert
  }
  else
  {
     PLACNT3_bit.SB1 = 0;                                                       //Set Low for TX Fault de-assert
  }
    
#endif
  
#else
 
#endif
  
}

void PLA_Soft_Tx_Fault_Control_at_TxTune(unsigned char unControl)
{
#if __SFP28_ER__== 1
  
#if __SFP28_ER_SEMI_TUNABLE__ == 1
  
  if(unControl == ASSERTED)
  {
     PLACNT3_bit.SB2 = 1;                                                       //Set High for TX Fault assert
  }
  else
  {
     PLACNT3_bit.SB2 = 0;                                                       //Set Low for TX Fault de-assert
  }
    
#endif
  
#else
 
#endif
  
}


void ddm_mon_tx_bias(void)
{
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
  
  // [DCLEE: 191114] Alarm ���� -->
  uint16_t unDdm_value, unDdm_value_1;
  FP32 f_val;
 
  A2_LOWER_MEMORY_MAP * xdata lowerMemoryMapPtr;

  lowerMemoryMapPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];
  
   
  unDdm_value = LD_Drive_Get(CH_TYPE_BSET, 0);
  
  
  if (unDdm_value != 0){
    
//    p = (float)unDdm_value;
//    p = ((p * 2000)/4096)*50;
//    
//    unDdm_value_1 = (unsigned int)p;
    unDdm_value_1 = unDdm_value * 33; // 33 = 66 / 2 : 66 is I_BIAS_base, 66 uA/count
    
    f_val = (FP32)unDdm_value;
    f_val = f_val * 19.536; // 19.536 = 39.072 / 2 = (160,000 uA)/4095 / 2
    unDdm_value_1 = (uint16_t)f_val;
  }
  else {
    
    unDdm_value_1 = unDdm_value;
  }
  
  if(TXDStatus() == ASSERTED)                                                 //report back 1 when laser is off
  {
    unDdm_value_1 = 0x0000;      
  }

#if __HFR_REQ_DDM_FLAG_VER__==1
  if (ddm_tx_bias_flag == 0)
  {
    lowerMemoryMapPtr->A2_TX_BIAS = __swap_bytes((uint16_t)unDdm_value_1);
    
  }
  else if (ddm_tx_bias_flag > 20)
  {
    ddm_tx_bias_flag = 0;
    lowerMemoryMapPtr->A2_TX_BIAS = __swap_bytes((uint16_t)unDdm_value_1);
    
  }
  else
  {
    ddm_tx_bias_flag++;
  }
  
#else
  lowerMemoryMapPtr->A2_TX_BIAS = __swap_bytes((uint16_t)unDdm_value_1);
#endif
  
#else
  
  // [DCLEE: 191114] Alarm ���� -->
//  FP32 xdata p,f1,f2,f3, f4;
//  FP32 xdata p;
//  FP32 xdata * fpPtr;  
  uint16_t unDdm_value, unDdm_value_1;
//  signed short  sDdm_value; 
//  unsigned long bias_value;
//  int xdata idx_s, idx_c;
//  uint16_t * xdata tmp_ptr;
 
  A2_LOWER_MEMORY_MAP * xdata lowerMemoryMapPtr;
//  A2_PAGE_80H_MEMORY_MAP	xdata * flashPtr;
  
//  flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];

  lowerMemoryMapPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];
  
  
//  if ((sfp28_module_state & SFP28_MODULE_STATE_READY) != SFP28_MODULE_STATE_READY)
//  {
//    unDdm_value = 0;
//    unDdm_value_1 = unDdm_value;
//    lowerMemoryMapPtr->A2_TX_BIAS = __swap_bytes((uint16_t)unDdm_value_1);
//    return;
//    
//  }
  
  unDdm_value = LD_Drive_Get(CH_TYPE_BSET, 0);
  
  
  if (unDdm_value != 0){
    
//    p = (float)unDdm_value;
//    p = ((p * 2000)/4096)*50;
//    
//    unDdm_value_1 = (unsigned int)p;
    unDdm_value_1 = unDdm_value * 33; // 33 = 66 / 2 : 66 is I_BIAS_base, 66 uA/count
  }
  else {
    
    unDdm_value_1 = unDdm_value;
  }
  
  if(TXDStatus() == ASSERTED)                                                 //report back 1 when laser is off
  {
    unDdm_value_1 = 0x0000;      
  }

#if __HFR_REQ_DDM_FLAG_VER__==1
  if (ddm_tx_bias_flag == 0)
  {
    lowerMemoryMapPtr->A2_TX_BIAS = __swap_bytes((uint16_t)unDdm_value_1);
    
  }
  else if (ddm_tx_bias_flag > 20)
  {
    ddm_tx_bias_flag = 0;
    lowerMemoryMapPtr->A2_TX_BIAS = __swap_bytes((uint16_t)unDdm_value_1);
    
  }
  else
  {
    ddm_tx_bias_flag++;
  }
  
#else
  lowerMemoryMapPtr->A2_TX_BIAS = __swap_bytes((uint16_t)unDdm_value_1);
#endif
  
#endif
  
}

void preAdjustAdc(void)
{
#if __SFP28_ER__== 1
#else

#endif

}

void preAdjustAdc_Lpmode(void)
{

#if __SFP28_ER__== 1
#else

#endif

}


// TEC �µ� ���� ����

signed short ThToTempConversion( uint16_t th_temp ){/*{{{*/
#if __SFP28_ER__== 1
  return 0;
  
#else

#endif

}/*}}}*/

void MonitoringDataCon( INT8U sigNo, INT8U chNo ){/*{{{*/
#if __SFP28_ER__== 1
  // [DCLEE: 191114] Alarm ���� -->
//  lowerMemoryMapPtr->A2_RESERVED_77 = (lowerMemoryMapPtr->A2_RESERVED_77 + 1);
//  I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_RESERVED_77] = I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_RESERVED_77] + 1;

//  detect_rx_los_from_cdr();
  ddm_mon_tx_power();
  
//  detect_rx_los_from_cdr();
  ddm_mon_rx_power();

  
//  I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_RESERVED_77] = I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_RESERVED_77] + 1;
//  I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_READ_CHIP_STATUS] = I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_READ_CHIP_STATUS] + 1;
    
//  detect_rx_los_from_cdr();
  ddm_mon_tx_bias();

  // Get CDR alarms
  detect_cdr_alarm();

//  detect_rx_los_from_cdr();
  detect_module_thr_alarm();

//  detect_rx_los_from_cdr();
  detect_channel_thr_alarm();

//  detect_rx_los_from_cdr();
  
#else

#endif
}/*}}}*/

void MonitoringDataCon_Lpmode( void ){/*{{{*/
#if __SFP28_ER__== 1
  // [DCLEE: 191114] Alarm ���� -->
  // Get CDR alarms
  //	detect_cdr_alarm();
  detect_module_thr_alarm();
  //	detect_channel_thr_alarm();

#else

#endif
}/*}}}*/

void detect_rx_los_from_cdr(void)
{
#if __SFP28_ER__== 1
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
  
//        uint8_t xdata tx_cdr_alarm, rx_cdr_alarm, los_flag, lol_flag;
        uint8_t xdata rx_cdr_alarm;
//        uint8_t tx_fault_alarm;
        
//        return;

	rx_cdr_alarm = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, (uint8_t)P00_SR1);
       if ((rx_cdr_alarm & 0x01) == 0x01)
        {
          // CDR RX LOS Status
          PLA_Soft_RX_LOS_Control_from_CDR(ASSERTED);
        }
        else
        {
          // CDR RX LOS Clear Status
          PLA_Soft_RX_LOS_Control_from_CDR(DE_ASSERTED);
        }
        
        return;
#endif
#endif
}

void detect_cdr_alarm(void)
{
#if __SFP28_ER__== 1
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
  
//        uint8_t xdata tx_cdr_alarm, rx_cdr_alarm, los_flag, lol_flag;
        uint8_t xdata rx_cdr_alarm;
        uint8_t tx_fault_alarm;
//  A2_LOWER_MEMORY_MAP * xdata lowerMemoryMapPtr;
//  A2_PAGE_80H_MEMORY_MAP	xdata * flashPtr;
//  
//  flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];

//  lowerMemoryMapPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];

//	los_flag = 0;
//	lol_flag = 0;

	rx_cdr_alarm = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, (uint8_t)P00_SR1);
//        rx_cdr_alarm = rx_cdr_alarm;
        if ((rx_cdr_alarm & 0x01) == 0x01)
        {
          // CDR RX LOS Status
          PLA_Soft_RX_LOS_Control_from_CDR(ASSERTED);
        }
        else
        {
          // CDR RX LOS Clear Status
          PLA_Soft_RX_LOS_Control_from_CDR(DE_ASSERTED);
        }
        
        if (sfp28_module_state == SFP28_MODULE_STATE_READY)
        {        
          tx_fault_alarm = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, (uint8_t)P00_SR1);
          if ((tx_fault_alarm & 0xF0) == 0x00)
          {
            PLA_Soft_Tx_Fault_Control(DE_ASSERTED);
//            PLACNT3_bit.SB2 = ASSERTED; // Using Soft TX Fault pin to H ���

          }
          else
          {
            PLA_Soft_Tx_Fault_Control(ASSERTED);          
          }
        }
        
        
//	los_flag = (rx_cdr_alarm & 0x04);
//	lol_flag = ((rx_cdr_alarm) & 0x02);

//	tx_cdr_alarm = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, (uint8_t)P00_LOS_LOL_STATUS);
//	los_flag |= ((tx_cdr_alarm << 4) & 0xF0);
//	lol_flag |= (tx_cdr_alarm & 0xF0);

//	prev_los_flag = lowerMemoryMapPtr->LOS;
//	prev_lol_flag = lowerMemoryMapPtr->LOL;
//
//	lowerMemoryMapPtr->LOS = (uint8_t)los_flag;
//	lowerMemoryMapPtr->LOL = (uint8_t)lol_flag;

	return;
  
#else
  
//        uint8_t xdata tx_cdr_alarm, rx_cdr_alarm, los_flag, lol_flag;
        uint8_t xdata rx_cdr_alarm;
        uint8_t tx_fault_alarm;
//  A2_LOWER_MEMORY_MAP * xdata lowerMemoryMapPtr;
//  A2_PAGE_80H_MEMORY_MAP	xdata * flashPtr;
//  
//  flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];

//  lowerMemoryMapPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];

//	los_flag = 0;
//	lol_flag = 0;

	rx_cdr_alarm = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, (uint8_t)P00_LOS_LOL_STATUS);
        rx_cdr_alarm = rx_cdr_alarm;
        
        
        if (sfp28_module_state == SFP28_MODULE_STATE_READY)
        {        
          tx_fault_alarm = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, (uint8_t)P00_TXFAULT_STATUS);
          if (tx_fault_alarm == 0x00)
          {
            PLA_Soft_Tx_Fault_Control(DE_ASSERTED);
//            PLACNT3_bit.SB2 = ASSERTED; // Using Soft TX Fault pin to H ���

          }
          else
          {
            PLA_Soft_Tx_Fault_Control(ASSERTED);          
          }
        }
        
        
//	los_flag = (rx_cdr_alarm & 0x04);
//	lol_flag = ((rx_cdr_alarm) & 0x02);

//	tx_cdr_alarm = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, (uint8_t)P00_LOS_LOL_STATUS);
//	los_flag |= ((tx_cdr_alarm << 4) & 0xF0);
//	lol_flag |= (tx_cdr_alarm & 0xF0);

//	prev_los_flag = lowerMemoryMapPtr->LOS;
//	prev_lol_flag = lowerMemoryMapPtr->LOL;
//
//	lowerMemoryMapPtr->LOS = (uint8_t)los_flag;
//	lowerMemoryMapPtr->LOL = (uint8_t)lol_flag;

	return;
        
#endif
        
#else

#endif
}

uint8_t check_thr_alarm(uint16_t mVal, uint16_t haVal, uint16_t laVal, uint16_t hwVal, uint16_t lwVal, uint8_t mask, uint8_t value_type)
{
  // [DCLEE: 191114] Alarm ���� -->
	uint8_t rVal;
	signed short xdata s_mVal, s_haVal, s_laVal, s_hwVal, s_lwVal;

	rVal = 0;

	if (value_type == 0)
	{
		// unsigned mode
		if (mVal > haVal)
		{
			rVal |= 0x88;
		}

		else if (mVal < laVal)
		{
			rVal |= 0x44;
		}

		else if (mVal > hwVal)
		{
			rVal |= 0x22;
		}

		else if (mVal < lwVal)
		{
			rVal |= 0x11;
		}

	}
	else
	{
		// signed mode
		s_mVal = (signed short)mVal;
		s_haVal = (signed short)haVal;
		s_laVal = (signed short)laVal;
		s_hwVal = (signed short)hwVal;
		s_lwVal = (signed short)lwVal;

		if (s_mVal > s_haVal)
		{
			rVal |= 0x88;
		}

		else if (s_mVal < s_laVal)
		{
			rVal |= 0x44;
		}

		else if (s_mVal > s_hwVal)
		{
			rVal |= 0x22;
		}

		else if (s_mVal < s_lwVal)
		{
			rVal |= 0x11;
		}

	}

	rVal = rVal & mask;
	return (rVal);
}


void detect_module_thr_alarm(void)
{
  // [DCLEE: 191114] Alarm ���� -->
	// Free side module threshold alarm: High Alarm, Warning, Low Warning, Alarm
	uint16_t xdata mVal, haVal, hwVal, laVal, lwVal;
//	signed short s_mVal, s_haVal, s_hwVal, s_laVal, s_lwVal;
	uint8_t xdata	rVal, rMask;
	A2_LOWER_MEMORY_MAP * xdata lowerMemoryMapPtr;
        unsigned char prev_alarm_1, prev_warning_1, rVal_1, rVal_2;

	// ------------------------------------------------
		// Module Alarms and Warnings 1
		// ------------------------------------------------

	lowerMemoryMapPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];

	// Temp Alarm Monitoring
	rVal = 0;
	mVal = __swap_bytes(lowerMemoryMapPtr->A2_TEMPERATURE);

	haVal = __swap_bytes(lowerMemoryMapPtr->A2_TEMP_HIGH_ALARM);
	laVal = __swap_bytes(lowerMemoryMapPtr->A2_TEMP_LOW_ALARM);
	hwVal = __swap_bytes(lowerMemoryMapPtr->A2_TEMP_HIGH_WARNING);
	lwVal = __swap_bytes(lowerMemoryMapPtr->A2_TEMP_LOW_WARNING);

	rMask = 0xF0;
	rVal = check_thr_alarm(mVal, haVal, laVal, hwVal, lwVal, rMask,1);
        rVal_1 = (rVal & 0xC0);
        rVal_2 = ((rVal<<2) & 0xC0);

	prev_alarm_1 = lowerMemoryMapPtr->A2_ALARM_WARNING_70;
	prev_warning_1 = lowerMemoryMapPtr->A2_ALARM_WARNING_74;
        
        prev_alarm_1 = (prev_alarm_1 & 0x3F);
        prev_warning_1 = (prev_warning_1 & 0x3F);

        prev_alarm_1 = prev_alarm_1 | rVal_1;
        prev_warning_1 = prev_warning_1 | rVal_2;
        
	lowerMemoryMapPtr->A2_ALARM_WARNING_70 = prev_alarm_1;
	lowerMemoryMapPtr->A2_ALARM_WARNING_74 = prev_warning_1;

	// 3V Alarm Monitoring
	rVal = 0;
	mVal = __swap_bytes(lowerMemoryMapPtr->A2_VCC);

	haVal = __swap_bytes(lowerMemoryMapPtr->A2_VCC_HIGH_ALARM);
	laVal = __swap_bytes(lowerMemoryMapPtr->A2_VCC_LOW_ALARM);
	hwVal = __swap_bytes(lowerMemoryMapPtr->A2_VCC_HIGH_WARNING);
	lwVal = __swap_bytes(lowerMemoryMapPtr->A2_VCC_LOW_WARNING);

	rMask = 0xF0;
	rVal = check_thr_alarm(mVal, haVal, laVal, hwVal, lwVal, rMask, 0);

        rVal_1 = ((rVal>>2) & 0x30);
        rVal_2 = (rVal & 0x30);

	prev_alarm_1 = lowerMemoryMapPtr->A2_ALARM_WARNING_70;
	prev_warning_1 = lowerMemoryMapPtr->A2_ALARM_WARNING_74;
        
        prev_alarm_1 = (prev_alarm_1 & 0xCF);
        prev_warning_1 = (prev_warning_1 & 0xCF);

        prev_alarm_1 = prev_alarm_1 | rVal_1;
        prev_warning_1 = prev_warning_1 | rVal_2;
        
	lowerMemoryMapPtr->A2_ALARM_WARNING_70 = prev_alarm_1;
	lowerMemoryMapPtr->A2_ALARM_WARNING_74 = prev_warning_1;
        
        return;
}

void detect_channel_thr_alarm(void)
{
  // [DCLEE: 191114] Alarm ���� -->
        // Free side channel threshold alarm: High Alarm, Warning, Low Warning, Alarm
	// Free side module threshold alarm: High Alarm, Warning, Low Warning, Alarm
	uint16_t xdata mVal, haVal, hwVal, laVal, lwVal;
	uint8_t xdata	rVal, rMask;
        unsigned char prev_alarm_1, prev_warning_1, rVal_1, rVal_2;
	A2_LOWER_MEMORY_MAP * xdata lowerMemoryMapPtr;

	lowerMemoryMapPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];

	// RX POWER Monitoring
	rVal = 0;
//	rVal1 = 0;
//	mVal = lowerMemoryMapPtr->RX1_POWER;
	mVal = __swap_bytes(lowerMemoryMapPtr->A2_RX_POWER);

	haVal = __swap_bytes(lowerMemoryMapPtr->A2_RX_POWER_HIGH_ALARM);
	laVal = __swap_bytes(lowerMemoryMapPtr->A2_RX_POWER_LOW_ALARM);
	hwVal = __swap_bytes(lowerMemoryMapPtr->A2_RX_POWER_HIGH_WARNING);
	lwVal = __swap_bytes(lowerMemoryMapPtr->A2_RX_POWER_LOW_WARNING);

	rMask = 0xF0;
	rVal = check_thr_alarm(mVal, haVal, laVal, hwVal, lwVal, rMask, 0);

        rVal_1 = (rVal & 0xC0);
        rVal_2 = ((rVal<<2) & 0xC0);

	prev_alarm_1 = lowerMemoryMapPtr->A2_ALARM_WARNING_71;
	prev_warning_1 = lowerMemoryMapPtr->A2_ALARM_WARNING_75;
        
        prev_alarm_1 = (prev_alarm_1 & 0x3F);
        prev_warning_1 = (prev_warning_1 & 0x3F);

        prev_alarm_1 = prev_alarm_1 | rVal_1;
        prev_warning_1 = prev_warning_1 | rVal_2;
        
	lowerMemoryMapPtr->A2_ALARM_WARNING_71 = prev_alarm_1;
	lowerMemoryMapPtr->A2_ALARM_WARNING_75 = prev_warning_1;


	// TX Power
	// TX1 POWER Monitoring
	rVal = 0;
//	rVal1 = 0;
//	mVal = lowerMemoryMapPtr->TX1_POWER;
	mVal = __swap_bytes(lowerMemoryMapPtr->A2_TX_POWER);

	haVal = __swap_bytes(lowerMemoryMapPtr->A2_TX_POWER_HIGH_ALARM);
	laVal = __swap_bytes(lowerMemoryMapPtr->A2_TX_POWER_LOW_ALARM);
	hwVal = __swap_bytes(lowerMemoryMapPtr->A2_TX_POWER_HIGH_WARNING);
	lwVal = __swap_bytes(lowerMemoryMapPtr->A2_TX_POWER_LOW_WARNING);

	rMask = 0x0F;
	rVal = check_thr_alarm(mVal, haVal, laVal, hwVal, lwVal, rMask, 0);

        rVal_1 = ((rVal>>2) & 0x03);
        rVal_2 = (rVal & 0x03);

	prev_alarm_1 = lowerMemoryMapPtr->A2_ALARM_WARNING_70;
	prev_warning_1 = lowerMemoryMapPtr->A2_ALARM_WARNING_74;
        
        prev_alarm_1 = (prev_alarm_1 & 0xFC);
        prev_warning_1 = (prev_warning_1 & 0xFC);

        prev_alarm_1 = prev_alarm_1 | rVal_1;
        prev_warning_1 = prev_warning_1 | rVal_2;
        
	lowerMemoryMapPtr->A2_ALARM_WARNING_70 = prev_alarm_1;
	lowerMemoryMapPtr->A2_ALARM_WARNING_74 = prev_warning_1;


	// TX Bias
	// TX1 Bias Monitoring
	rVal = 0;
//	rVal1 = 0;
//	mVal = lowerMemoryMapPtr->TX1_POWER;
	mVal = __swap_bytes(lowerMemoryMapPtr->A2_TX_BIAS);

	haVal = __swap_bytes(lowerMemoryMapPtr->A2_TX_BIAS_HIGH_ALARM);
	laVal = __swap_bytes(lowerMemoryMapPtr->A2_TX_BIAS_LOW_ALARM);
	hwVal = __swap_bytes(lowerMemoryMapPtr->A2_TX_BIAS_HIGH_WARNING);
	lwVal = __swap_bytes(lowerMemoryMapPtr->A2_TX_BIAS_LOW_WARNING);

	rMask = 0x0F;
	rVal = check_thr_alarm(mVal, haVal, laVal, hwVal, lwVal, rMask, 0);
        rVal_1 = (rVal & 0x0C);
        rVal_2 = ((rVal<<2) & 0x0C);

	prev_alarm_1 = lowerMemoryMapPtr->A2_ALARM_WARNING_70;
	prev_warning_1 = lowerMemoryMapPtr->A2_ALARM_WARNING_74;
        
        prev_alarm_1 = (prev_alarm_1 & 0xF3);
        prev_warning_1 = (prev_warning_1 & 0xF3);

        prev_alarm_1 = prev_alarm_1 | rVal_1;
        prev_warning_1 = prev_warning_1 | rVal_2;
        
	lowerMemoryMapPtr->A2_ALARM_WARNING_70 = prev_alarm_1;
	lowerMemoryMapPtr->A2_ALARM_WARNING_74 = prev_warning_1;


        return;
}

uint8_t detect_current_alarm_state(uint8_t pVal, uint8_t cVal, uint8_t mask, uint8_t retMask)
{
//	uint8_t xdata rVal, retVal;
	uint8_t xdata rVal;

	rVal = ((pVal ^ cVal) & cVal) & (~mask);

	if (rVal != 0x00)
	{
		return (retMask);
	}
	else
	{
		return (0x00);
	}

}


void update_faws_summary_registers(void)
{
#if __SFP28_ER__
//  A2_STATUS_CONTROL
        uint8_t xdata gVal, eVal; // , rVal, cVal, rMask;
	A2_LOWER_MEMORY_MAP * xdata lowerMemoryMapPtr;

	lowerMemoryMapPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];

	// B7: CH_TXPWR, B6: CH_TXBIAS, B5: CH_RXPWR, B4: M_VCC, B3: M_TEMP, B2: LOL, B1: FLT, B0: LOS        
	gVal = lowerMemoryMapPtr->A2_STATUS_CONTROL;
        gVal &= 0x49;
        
        // TXDIS PIN State
        if (MSA_INPUT_TXDIS == ASSERTED)
        {
          // Asserted TXDIS PIN
          gVal |= 0x80;
        }
        
        // RS(1) State
        if (MSA_INPUT_RS1 == ASSERTED)
        {
          // Asserted RS1 PIN
          gVal |= 0x20;
        }
         
        // RS(0) State
        if (MSA_INPUT_RS0 == ASSERTED)
        {
          // Asserted RS0 PIN
          gVal |= 0x10;
        }
        
        // TX Fault State
        if (PLA_Tx_Fault_Status() == ASSERTED)
        {
          // Asserted TXF output
          gVal |= 0x04;
        }
          
        // RX LOS State
        if (PLA_RX_LOS_Status() == ASSERTED)
        {
          // Asserted RX LOS output
          gVal |= 0x02;
        }
	
        lowerMemoryMapPtr->A2_STATUS_CONTROL = 	gVal;
       
        eVal = lowerMemoryMapPtr->A2_EXTENDED_CONTROL_STATUS;
        eVal |= 0x02;  // 2021.05.13. Power Level 2 Control is specified.
        lowerMemoryMapPtr->A2_EXTENDED_CONTROL_STATUS = eVal;

//        if ((gVal & 0x18) == 0x00)
//        {
//          // RS0 : Low/0
//          if ((gVal & 0x20)==0x20)
//          {
//            // RS1 pin: H, RS0: L
//            // TX Bypass and RX Lock at high bit rate 
//            rate_select_control_cdr(2);
//          }
//          else if ((eVal & 0x08) == 0x08)
//          {
//            // RS(1) Select bit: 1, RS0: L
//            // TX Bypass and RX Lock at high bit rate 
//            rate_select_control_cdr(2);
//            
//          }
//          else
//          {
//            // RS(1) Select bit: 0, RS0: L
//            // TX and RX Lock at low bit rate 
//            rate_select_control_cdr(0);
//
//          }
//          
//        }
//        else
//        {
//          // RS0: High/1
//          if ((gVal & 0x20)==0x20)
//          {
//            // RS1 pin: H, RS0: H
//            // TX and RX Lock at high bit rate 
//            rate_select_control_cdr(3);
//            
//          }
//          else if ((eVal & 0x08) == 0x08)
//          {
//            // RS(1) Select bit: 1, RS0: H
//            // TX and RX Lock at high bit rate 
//            rate_select_control_cdr(3);
//            
//          }
//          else
//          {
//            // RS(1) Select bit: 0, RS0: H
//            // TX and RX Bypass  
//            rate_select_control_cdr(1);
//
//          }
//          
//        }
#else
  
        uint8_t xdata gVal, pVal, rVal, cVal, rMask;
	A2_LOWER_MEMORY_MAP * xdata lowerMemoryMapPtr;

	lowerMemoryMapPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];

	// B7: CH_TXPWR, B6: CH_TXBIAS, B5: CH_RXPWR, B4: M_VCC, B3: M_TEMP, B2: LOL, B1: FLT, B0: LOS
	gVal = 0;

	// LOS
	pVal = prev_los_flag;
	cVal = lowerMemoryMapPtr->LOS;
	rMask = lowerMemoryMapPtr->MASK_LOS;

	rVal = detect_current_alarm_state(pVal, cVal, rMask, 0x01);

	gVal = gVal | rVal;

	// LOL
	pVal = prev_lol_flag;
	cVal = lowerMemoryMapPtr->LOL;
	rMask = lowerMemoryMapPtr->MASK_LOL;

	rVal = detect_current_alarm_state(pVal, cVal, rMask, 0x04);

	gVal = gVal | rVal;

	// M_TEMP
	pVal = prev_module_temp_thr_flag;
	cVal = lowerMemoryMapPtr->MOD_INT_TEMP_FLAG0;
	rMask = lowerMemoryMapPtr->MASK_TEMP;

	rVal = detect_current_alarm_state(pVal, cVal, rMask, 0x08);

	gVal = gVal | rVal;

	// M_VCC
	pVal = prev_module_vcc_thr_flag;
	cVal = lowerMemoryMapPtr->MOD_INT_VCC_FLAG1;
	rMask = lowerMemoryMapPtr->MASK_VCC;

	rVal = detect_current_alarm_state(pVal, cVal, rMask, 0x10);

	gVal = gVal | rVal;

	// CHANNEL RX POWER
	pVal = prev_channel_rx_power12_thr_flag;
	cVal = lowerMemoryMapPtr->CH_MON_INT_FLAG_RX_POW12;
	rMask = page3MemoryMapPtr->MASK_RX1_2;

	rVal = detect_current_alarm_state(pVal, cVal, rMask, 0x20);

	gVal = gVal | rVal;

	pVal = prev_channel_rx_power34_thr_flag;
	cVal = lowerMemoryMapPtr->CH_MON_INT_FLAG_RX_POW34;
	rMask = page3MemoryMapPtr->MASK_RX3_4;

	rVal = detect_current_alarm_state(pVal, cVal, rMask, 0x20);

	gVal = gVal | rVal;

	// CHANNEL TX BIAS
	pVal = prev_channel_tx_bias12_thr_flag; 
	cVal = lowerMemoryMapPtr->CH_MON_INT_FLAG_TX_BIAS12;
	rMask = page3MemoryMapPtr->MASK_TXB1_2;

	rVal = detect_current_alarm_state(pVal, cVal, rMask, 0x40);

	gVal = gVal | rVal;

        pVal = prev_channel_tx_bias34_thr_flag; 
	cVal = lowerMemoryMapPtr->CH_MON_INT_FLAG_TX_BIAS34;
	rMask = page3MemoryMapPtr->MASK_TXB3_4;

	rVal = detect_current_alarm_state(pVal, cVal, rMask, 0x40);

	gVal = gVal | rVal;

        
	// CHANNEL TX POWER
	pVal = prev_channel_tx_power12_thr_flag;
	cVal = lowerMemoryMapPtr->CH_MON_INT_FLAG_TX_POWER12;
	rMask = page3MemoryMapPtr->MASK_TXP1_2;

	rVal = detect_current_alarm_state(pVal, cVal, rMask, 0x80);

	gVal = gVal | rVal;

	pVal = prev_channel_tx_power34_thr_flag;
	cVal = lowerMemoryMapPtr->CH_MON_INT_FLAG_TX_POWER34;
	rMask = page3MemoryMapPtr->MASK_TXP3_4;

	rVal = detect_current_alarm_state(pVal, cVal, rMask, 0x80);

	gVal = gVal | rVal;

	// Determine INTL pin and STATUS bit

	cVal = lowerMemoryMapPtr->STATUS_LSB;
	if ((vendor_specific_pin_control_config & 0x01) == 0x01)
	{ // RX_LOS Selected
		rVal = lowerMemoryMapPtr->LOS;

		if ((rVal & 0x0F) != 0x00) {
			// RX LOS ����:
//PO0_bit.PO06
			INTL = 1; // Pin output is High: alarm
//			PO0_bit.PO06 = 1; // Pin output is High: alarm
			cVal |= 0x02;
		}
		else
		{
			INTL = 0; // Pin output is Low: No alarm
//			PO0_bit.PO06 = 0; // Pin output is Low: No alarm
			cVal &= 0xFD;
		}
	}
	else
	{
		// Normal Pin Operation: INTL Pin
		if (gVal == 0)
		{// Normal State
			INTL = 1; // Pin output is High: No alarm
//			PO0_bit.PO06 = 1; // Pin output is High: No alarm
			cVal |= 0x02;
		}
		else
		{// Alarm State
			INTL = 0; // Pin output is Low: IRQ ��û
//			PO0_bit.PO06 = 0; // Pin output is Low: IRQ ��û
			cVal &= 0xFD;
		}
	}

	lowerMemoryMapPtr->STATUS_LSB = cVal;
#endif

}


void update_rate_select_operation(void)
{
#if __SFP28_ER__
//  A2_STATUS_CONTROL
        uint8_t xdata gVal, eVal; // , rVal, cVal, rMask;
	A2_LOWER_MEMORY_MAP * xdata lowerMemoryMapPtr;

	lowerMemoryMapPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];

	// B7: CH_TXPWR, B6: CH_TXBIAS, B5: CH_RXPWR, B4: M_VCC, B3: M_TEMP, B2: LOL, B1: FLT, B0: LOS        
	gVal = lowerMemoryMapPtr->A2_STATUS_CONTROL;
  gVal &= 0x49;
          
#if __HSFP_10G_MULTI_RATE_SEMI_TUNABLE__ == 1

#else

  // RS(1) State
  if (MSA_INPUT_RS1 == ASSERTED)
  {
    // Asserted RS1 PIN
    gVal |= 0x20;
  }
    
  // RS(0) State
  if (MSA_INPUT_RS0 == ASSERTED)
  {
    // Asserted RS0 PIN
    gVal |= 0x10;
  }
  
#endif

          
  eVal = lowerMemoryMapPtr->A2_EXTENDED_CONTROL_STATUS;

  if ((gVal & 0x18) == 0x00)
  {
    // RS0 : Low/0
    if ((gVal & 0x20)==0x20)
    {
      // RS1 pin: H, RS0: L
      // TX Bypass and RX Lock at high bit rate 
      rate_select_control_cdr(2);
    }
    else if ((eVal & 0x08) == 0x08)
    {
      // RS(1) Select bit: 1, RS0: L
      // TX Bypass and RX Lock at high bit rate 
      rate_select_control_cdr(2);
      
    }
    else
    {
      // RS(1) Select bit: 0, RS0: L
      // TX and RX Lock at low bit rate 
      rate_select_control_cdr(0);

    }
    
  }
  else
  {
    // RS0: High/1
    if ((gVal & 0x20)==0x20)
    {
      // RS1 pin: H, RS0: H
      // TX and RX Lock at high bit rate 
      rate_select_control_cdr(3);
      
    }
    else if ((eVal & 0x08) == 0x08)
    {
      // RS(1) Select bit: 1, RS0: H
      // TX and RX Lock at high bit rate 
      rate_select_control_cdr(3);
      
    }
    else
    {
      // RS(1) Select bit: 0, RS0: H
      // TX and RX Bypass  
      rate_select_control_cdr(1);

    }
    
  }
        
#endif

}

void sfp28_register_initialization(void)
{

}


void check_hw_interlock(void)
{

}

void update_module_io_pin_state(void)
{

}

unsigned char check_mod_rsts(void)
{/*{{{*/
	//unsigned char xdata wVal;

  return 0;
  
//  PI2_bit.PI26;
//	if ((MOD_RSTn == 0))
//	{
//		// MOD_RSTs Asserted
//		return 1;
//	}
//	else
//	{
//		// MOD_RSTs De-asserted
//		return 0;
//	}

}/*}}}*/

unsigned char check_mod_lopwrs(void)
{/*{{{*/
//	uint8_t	xdata cVal, ret_val;

        return 0;
        
//	// Get MOD_LOPWR and soft Module Low Power
//	cVal = I2C_Slave_Buffer_A0[SFP28_LOWER_MEMORY_POWER_MODE];
//	//check_hw_interlock();
//	if ((vendor_specific_pin_control_config & 0x02) == 0x02)
//	{
//		if ((cVal & 0x03) == 0x03)
//		{
//			ret_val = 1;
//		}
//		else
//		{
//			ret_val = 0;
//		}
//	}
//	else
//	{
//
//		if ((cVal & 0x03) == 0x01)
//		{
//			ret_val = 0;
//		}
//		else if ((cVal & 0x03) == 0x03)
//		{
//			ret_val = 1;
//		}
//
//		else if (LPMODE == LPMODE_ON)
//		{
//			ret_val = 1;
//		}
//		else
//		{
//			ret_val = 0;
//		}
//          // 191202 <-- MVI for CISCO, HUAWEI Routers, ROTN System as like Ciena, Huawei, ZTE
//
//
//	}
//
//
//
//
//	return ret_val;

}/*}}}*/

#define HI_POWER_MODE_ENABLE  0

unsigned char check_tx_dis(void)
{/*{{{*/
//	unsigned short xdata wVal;
//	uint8_t	xdata cVal, ret_val, cVal1;
	A2_LOWER_MEMORY_MAP * xdata lower_memory_map_ptr;
        
        unsigned char rVal;
        
	lower_memory_map_ptr = (A2_LOWER_MEMORY_MAP * )&I2C_Slave_Buffer_A2[0];
        rVal = lower_memory_map_ptr->A2_STATUS_CONTROL;
        
#if __WO_TXDIS_PIN_MONITORING__==1
        
//        if (MSA_INPUT_TXDIS == ASSERTED)
//        {
//          PLA_Soft_TXD_Control(ASSERTED);          
//        }        
//        else 
        if ((rVal & 0x40) == 0x40)
        {
          PLA_Soft_TXD_Control(ASSERTED);
        }
        else
        {
          PLA_Soft_TXD_Control(DE_ASSERTED);          
        }
        
#else
        
        if (MSA_INPUT_TXDIS == ASSERTED)
        {
          PLA_Soft_TXD_Control(ASSERTED);          
        }        
        else 
          if ((rVal & 0x40) == 0x40)
        {
          PLA_Soft_TXD_Control(ASSERTED);
        }
        else
        {
          PLA_Soft_TXD_Control(DE_ASSERTED);          
        }
        
#endif
        
//        if ((rVal & 0x40) == 0x40)
//        {
//          PLA_Soft_TXD_Control(ASSERTED);
//        }
//        else
//        {
//          PLA_Soft_TXD_Control(DE_ASSERTED);          
//        }
        
//        return (0);
        
#if __WO_TXDIS_PIN_MONITORING__==1
        if ((rVal & 0x40) == 0x40)
        {
          rVal = 1;
        }
        else
        {
//          PLA_Soft_TXD_Control(DE_ASSERTED);
          PLACNT1_bit.SB1 = 0;                                                       //Set High for TX disable assert    

          rVal = 0;
          
        }        
#else
        
        rVal = TXDStatus();
#endif
        
        return (rVal);
        
//	// Check TX_DISs = TX_DIS OR (Soft Tx Disable)
//	lower_memory_map_ptr = (LOWER_MEMORY_MAP * )&I2C_Slave_Buffer_A0[0];
//
//	cVal1 = I2C_Slave_Buffer_A0[SFP28_LOWER_MEMORY_POWER_MODE]; // Power Mode
//	cVal = lower_memory_map_ptr->TX_DISABLE;
//
//
//	{
//		if ((cVal & 0x0F) == 0x0F)
//		{
//			// TX DISABLE: ON
//			ret_val = 1;
//		}
//#if __SFP28_ER__== 1
//#if HI_POWER_MODE_ENABLE == 1
//		else if ((cVal1 & 0x04) == 0x00)
//		{
//			ret_val = 1;
//		}
//#endif
//#endif
//		else
//		{
//			// TX DISABLE: OFF
//			ret_val = 0;
//		}
//	}
//	return ret_val;

}/*}}}*/

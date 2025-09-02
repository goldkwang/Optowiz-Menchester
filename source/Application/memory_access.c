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
// includes
//-----------------------------------------------------------------------------
#include <iods4835.h>
#include <intrinsics.h>

#include "flash.h"
#include "i2cslave.h"
#include "memory_access.h"
#include "includes.h"
#include <string.h>

//-----------------------------------------------------------------------------
// global variables defined in this module
//-----------------------------------------------------------------------------
const unsigned char c_Build_date[12] = __DATE__;

// static void AddBuildDate(void);
static unsigned char s_ucPassword_entry[4];
// static unsigned int s_unFlash_value;
WriteBuffer_S twsiSlaveBuf;
//-----------------------------------------------------------------------------
// local function declaration
//-----------------------------------------------------------------------------

// static void ProcessTable80h(char cStart_addr, char cNum_bytes);
// static void ProcessTable90h(char cStart_addr, char cNum_bytes);
// static void ProcessTable91h(char cStart_addr, char cNum_bytes);

//------------------------------------------------------------------------------
// Memory_Init Function
//      - reads LUTs values from flash, load into SRAM and initializes SRAM
//        with default/save values.
//------------------------------------------------------------------------------
void Memory_Init(void)
{

	unsigned char *pPtr;
	//  unsigned int idx;

	pPtr = memset(&I2C_Slave_Buffer_A0_Local_Memory[0], 0x00, 256); // Clear A0h System Configuration memory
	if (pPtr != NULL)
	{
		asm("nop"); // To Keep Static analysis tool happy
	}

	pPtr = memset(&I2C_Slave_Buffer_A2[0], 0x00, 128); // Clear A2h Lower memory
	if (pPtr != NULL)
	{
		asm("nop"); // To Keep Static analysis tool happy
	}

	pPtr = memset(&I2C_Slave_Buffer_A2_Pn_Up[0], 0x00, 128); // Clear A2h Page 00h Upper memory
	if (pPtr != NULL)
	{
		asm("nop"); // To Keep Static analysis tool happy
	}

	pPtr = memset(&I2C_Slave_Buffer_A2_P00H_Up[0], 0x00, 128); // Clear A2h Page 00h Upper memory
	if (pPtr != NULL)
	{
		asm("nop"); // To Keep Static analysis tool happy
	}

	pPtr = memset(&I2C_Slave_Buffer_A2_P01H_Up[0], 0x00, 128); // Clear A2h Page 01h Upper memory
	if (pPtr != NULL)
	{
		asm("nop"); // To Keep Static analysis tool happy
	}

	pPtr = memset(&I2C_Slave_Buffer_A2_P02H_Up[0], 0x00, 128); // Clear A0h Page 02h Upper memory
	if (pPtr != NULL)
	{
		asm("nop"); // To Keep Static analysis tool happy
	}

	pPtr = memset(&I2C_Slave_Buffer_A2_P80H_Up[0], 0x00, 128); // Clear A0h Page 80h Upper memory
	if (pPtr != NULL)
	{
		asm("nop"); // To Keep Static analysis tool happy
	}

	pPtr = memset(&I2C_Slave_Buffer_A2_P81H_Up[0], 0x00, 128); // Clear A0h Page 81h Upper memory
	if (pPtr != NULL)
	{
		asm("nop"); // To Keep Static analysis tool happy
	}

	pPtr = memset(&I2C_Slave_Buffer_A2_P82H_Up[0], 0x00, 128); // Clear A0h Page 82h Upper memory
	if (pPtr != NULL)
	{
		asm("nop"); // To Keep Static analysis tool happy
	}

	pPtr = memset(&I2C_Slave_Buffer_A2_P83H_Up[0], 0x00, 128); // Clear A0h Page 83h Upper memory
	if (pPtr != NULL)
	{
		asm("nop"); // To Keep Static analysis tool happy
	}

	pPtr = memset(&I2C_Slave_Buffer_A2_P84H_Up[0], 0x00, 128); // Clear A0h Page 84h Upper memory
	if (pPtr != NULL)
	{
		asm("nop"); // To Keep Static analysis tool happy
	}

	memset(write_i2c_list, 0xFF, sizeof(write_i2c_list));

	// ---------------------------

	CalibConstantRead(); // Factory calibration parameters

	I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_STATUS_CONTROL] = 0x01; // Data not ready

	//  STATUS_CONTROL_6E = 0x01;                                                     //Data not ready

	//  for (idx=0; idx<16; idx++)
	//  {
	//    page_password_enable[idx] = 1;
	//  }
}

//------------------------------------------------------------------------------
// SW_Delay Function
//      - software delay for general purpose
//------------------------------------------------------------------------------
void SW_Delay(unsigned int unDelay_counter)
{
	volatile unsigned int unCounter = 0;
	for (unCounter = 0; unCounter < unDelay_counter; unCounter++)
	{

		WDCN_bit.RWT = 1; // Reset Watchdog Timer
		asm("nop");
		asm("nop");
		asm("nop");
	}
}

//------------------------------------------------------------------------------
// ProcessTable80hData Function
//      - process table 80h
//------------------------------------------------------------------------------
#if __SFP28_ER__ == 1
//	I2C_Slave_Memory_Map_Write(DEV_addr,address_index,SMB0DAT);

#if __INTEROPERABILITY_TEST_POLL_PAGESEL__ == 1

int check_current_upper_page(uint8_t page_no)
{
	unsigned char *src_ptr, *target_ptr;
	int idx;

	src_ptr = (unsigned char *)A2_UPPER_SRAM_OFFSET;

	switch (page_no)
	{
	case PAGE_00H:
		target_ptr = (unsigned char *)PAGE00H_UPPER;
		break;
	case PAGE_01H:
		target_ptr = (unsigned char *)PAGE01H_UPPER;
		break;
	case PAGE_02H:
		target_ptr = (unsigned char *)PAGE02H_UPPER;
		break;
	case PAGE_80H:
		target_ptr = (unsigned char *)PAGE80H_UPPER;
		break;
	case PAGE_81H:
		target_ptr = (unsigned char *)PAGE81H_UPPER;
		break;
	case PAGE_82H:
		target_ptr = (unsigned char *)PAGE82H_UPPER;
		break;
	case PAGE_83H:
		target_ptr = (unsigned char *)PAGE83H_UPPER;
		break;
	case PAGE_84H:
		target_ptr = (unsigned char *)PAGE84H_UPPER;
		break;
	}

	for (idx = 0; idx < 16; idx++)
	{
		if (src_ptr[idx] != target_ptr[idx])
		{
			return 1; // Different upper memory
		}
	}
	return 0; // Same upper memory
}

void update_upper_page(uint8_t page_no)
{

	if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_00H)
	{
		// copy from Page00h area to upper memory
		memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE00H_UPPER, 128);
	}
	else if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_01H)
	{
		// copy from Page01h area to upper memory
		memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE01H_UPPER, 128);
	}
	else if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_02H)
	{
		// copy from Page03h area to upper memory
		memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE02H_UPPER, 128);
	}
	else if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_80H)
	{
		// copy from Page04h area to upper memory
		memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE80H_UPPER, 128);
	}
	else if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_81H)
	{
		// copy from Page05h area to upper memory
		memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE81H_UPPER, 128);
	}
	else if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_82H)
	{
		// copy from Page05h area to upper memory
		memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE82H_UPPER, 128);
	}
	else if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_83H)
	{
		// copy from Page05h area to upper memory
		memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE83H_UPPER, 128);
	}
	else if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_84H)
	{
		// copy from Page05h area to upper memory
		memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE84H_UPPER, 128);
	}
}

#endif

void I2C_Slave_Memory_Map_Write(uint8_t dev_addr, uint8_t page, uint8_t mem_address_index, uint8_t write_value)
{
	//	uint8_t * tmp_memory_array;
	uint8_t xdata tmp_mem_address_index, page_select_value;
	uint8_t t_page_no;

	page_select_value = page;
	if (dev_addr == 0xA2)
	{
		if (mem_address_index < (uint8_t)LOWER_PAGE_ADDR)
		{
			if ((mem_address_index == A2_STATUS_CONTROL_OFF))
			{
#if __WO_TXDIS_PIN_MONITORING__ == 1

				if ((write_value & 0x40) != 0x00)
				{ // TX_DISABLE: [7]: Tx Disable State, [6]: Soft TX Disable Select
					forced_TX_DISABLE_ON(write_value);
				}
				else if ((write_value & 0x40) == 0x00)
				{
					forced_TX_DISABLE_OFF(write_value);
				}

#else

				if ((write_value & 0xC0) != 0x00) // 0x72
				{								  // TX_DISABLE: [7]: Tx Disable State, [6]: Soft TX Disable Select
					forced_TX_DISABLE_ON(write_value);
				}
				else if ((write_value & 0xC0) == 0x00) // 0x32
				{
					forced_TX_DISABLE_OFF(write_value);
				}

#endif
				I2C_Slave_Buffer_A2[mem_address_index] = write_value;
				update_rate_select_operation();
				insert_write_entry(dev_addr, 0, mem_address_index);
			}
			else if ((mem_address_index == A2_EXTENDED_CONTROL_STATUS_OFF))
			{
				I2C_Slave_Buffer_A2[mem_address_index] = write_value;
				//                                if ((write_value & 0x08) == 0x08) { // Lock to high rate
				////                                  rate_select_control_cdr(3);
				//                                    update_rate_select_operation();
				//                                }
				//                                else if ((write_value & 0x08) == 0x00) { // Bypass or Lock to low rate
				////                                  rate_select_control_cdr(1);
				//                                    update_rate_select_operation();
				//                                }
				update_rate_select_operation();
				//                                *((unsigned int *)&I2C_Slave_Buffer_A2_P02H_Up[0x44]) = __swap_bytes(write_i2c_count); // for DEBUG, 191104

				//				I2C_Slave_Buffer_A2[mem_address_index] = write_value;
				insert_write_entry(dev_addr, 0, mem_address_index);
			}
			else if ((mem_address_index >= A2_RX_PWR_EXT_COEFF_4_OFF) && (mem_address_index < A2_TEMPERATURE_OFF))
			{
				I2C_Slave_Buffer_A2[mem_address_index] = write_value;
				insert_write_entry(dev_addr, 0, mem_address_index);
			}
			else if (mem_address_index == A2_TABLE_OFF)
			{
#if __INTEROPERABILITY_TEST_POLL_PAGESEL__ == 1
				insert_write_entry(dev_addr, 0, mem_address_index);
				I2C_Slave_Buffer_A2[mem_address_index] = write_value;
				//                          if (check_current_upper_page(write_value) == 1)
				//                          {
				//                            // Page is different, update upper memory
				//                            update_upper_page(write_value);
				//                            I2C_Slave_Buffer_A2[mem_address_index] = write_value;
				//                          }
				//                          else
				//                          {
				//                            // Page is same, do not update upper memory
				//                            I2C_Slave_Buffer_A2[mem_address_index] = write_value;
				//
				//                          }

#else
				if (write_value > 3)
				{
					if (page_vendor_control == 1)
					{
						I2C_Slave_Buffer_A2[mem_address_index] = write_value;
					}
					else if (page_vendor_control == 0)
					{
						I2C_Slave_Buffer_A2[mem_address_index] = 0x00;
					}
					else
					{
						I2C_Slave_Buffer_A2[mem_address_index] = 0x00;
						page_vendor_control = 0;
					}
				}
				else if (write_value == 1)
				{
					if (page_vendor_control == 1)
					{
						I2C_Slave_Buffer_A2[mem_address_index] = write_value;
					}
					else if (page_vendor_control == 0)
					{
						I2C_Slave_Buffer_A2[mem_address_index] = 0x00;
					}
				}
				else
				{
					I2C_Slave_Buffer_A2[mem_address_index] = write_value;
				}
#endif
			}
			//			else if ((mem_address_index >= A2_PASSWORD_OFF)&&(mem_address_index < QSFP_LOWER_MEMORY_PASSWORD_ENTRY_AREA)) {
			//
			//				if (page_password_enable[2] == 1)
			//				{
			//					// Fixed side :password enable
			//					tmp_mem_address_index = mem_address_index - QSFP_LOWER_MEMORY_PASSWORD_CHANGE_ENTRY_AREA;
			//					tmp_mem_address_index %= 4;
			//
			//					changing_fixed_side_password.byte_data[tmp_mem_address_index] = write_value;
			//					I2C_Slave_Buffer_A0[mem_address_index] = write_value;
			//					insert_write_entry(dev_addr, 0, mem_address_index);
			//				}
			//			}
			else if ((mem_address_index >= A2_PASSWORD_OFF) && (mem_address_index < A2_TABLE_OFF))
			{
				tmp_mem_address_index = mem_address_index - A2_PASSWORD_OFF;
				tmp_mem_address_index %= 4;
				current_password.byte_data[tmp_mem_address_index] = write_value;

				I2C_Slave_Buffer_A2[mem_address_index] = write_value;
				insert_write_entry(dev_addr, 0, mem_address_index);
			}
			//			else if (mem_address_index == QSFP_LOWER_MEMORY_VENDOR_SPECIFIC_CONFIG) {
			//				if (sfp28_module_state == SFP28_MODULE_STATE_LOW_POWER) {
			//					I2C_Slave_Buffer_A2[mem_address_index] = write_value;
			//					insert_write_entry(dev_addr, 0, mem_address_index);
			//				}
			//			}
			//			else if ((mem_address_index >= A2_TEMP_HIGH_ALARM_OFF)&&(mem_address_index < A2_RESERVED_38_4B_OFF)) {
			else if ((mem_address_index < A2_RESERVED_38_4B_OFF))
			{
				if (page_password_enable[0] == 1)
				{
					I2C_Slave_Buffer_A2[mem_address_index] = write_value;
					insert_write_entry(dev_addr, 0, mem_address_index);
				}
			}
			// [DCLEE] 201201: TX Equalization and RX Deemphasis ���� ���� ó�� �߰� -->
			else if ((mem_address_index == A2_TXEQ_72_OFF))
			{
				I2C_Slave_Buffer_A2[mem_address_index] = write_value;
				insert_write_entry(dev_addr, 0, mem_address_index);
			}
			else if ((mem_address_index == A2_RXPREEMP_73_OFF))
			{
				I2C_Slave_Buffer_A2[mem_address_index] = write_value;
				insert_write_entry(dev_addr, 0, mem_address_index);
			}
			// <--
		}
		else
		{
			tmp_mem_address_index = mem_address_index & (uint8_t)0x7F;
			switch (page_select_value)
			{
			case 0x00:
				if (page_password_enable[page_select_value] == 1)
				{
					//						if (mem_address_index == PAGE0_UPPER_MEMORY_VENDOR_SPECIFIC_CONFIG) {
					//							I2C_Slave_Buffer_A0_P0_Up[tmp_mem_address_index] = write_value;
					//							insert_write_entry(dev_addr, 0, mem_address_index);
					//						}
					//						else {
					//							I2C_Slave_Buffer_A0_P0_Up[tmp_mem_address_index] = write_value;
					//						}

					I2C_Slave_Buffer_A2_P00H_Up[tmp_mem_address_index] = write_value; // USER EEPROM Page 0
				}
				//					else if (mem_address_index == PAGE0_UPPER_MEMORY_VENDOR_SPECIFIC_CONFIG) {
				//						if (qsfp_module_state == QSFP_MODULE_STATE_LOW_POWER) {
				//							I2C_Slave_Buffer_A0_P0_Up[tmp_mem_address_index] = write_value;
				//							insert_write_entry(dev_addr, 0, mem_address_index);
				//						}
				//					}
				else
				{
					return;
				}
				break;

			case 0x01:
				if (page_password_enable[page_select_value] == 1)
				{
					I2C_Slave_Buffer_A2_P01H_Up[tmp_mem_address_index] = write_value; // USER EEPROM Page 1
					insert_write_entry(dev_addr, page_select_value, mem_address_index);
				}
				else
				{
					return;
				}
				break;

			case 0x02: // Tunable Control & Status
				if (page_password_enable[page_select_value] == 1)
				{
					I2C_Slave_Buffer_A2_P02H_Up[tmp_mem_address_index] = write_value;
					insert_write_entry(dev_addr, page_select_value, mem_address_index);
					//                                                I2C_Slave_Buffer_A2_P02H_Up[P02H_CURR_STAT_DEBUG+2] = 1;
				}
				else
				{
					if ((tmp_mem_address_index >= P02H_CHANNEL_NUMBER_SET) && (tmp_mem_address_index < (P02H_WAVELENGTH_SET + 2)))
					{
						I2C_Slave_Buffer_A2_P02H_Up[tmp_mem_address_index] = write_value;
						insert_write_entry(dev_addr, page_select_value, mem_address_index);

						//                                            I2C_Slave_Buffer_A2_P02H_Up[P02H_CURR_STAT_DEBUG+1] = mem_address_index;
					}
					else
					{
						//                                            I2C_Slave_Buffer_A2_P02H_Up[P02H_CURR_STAT_DEBUG+3] = mem_address_index;
						return;
					}
				}
				break;

				//				case 0x03:
				//					if (page_password_enable[page_select_value] == 1) {
				//						I2C_Slave_Buffer_A0_P3_Up[tmp_mem_address_index] = write_value;
				//					}
				//					else if ((mem_address_index >= (uint8_t)PAGE3_MEMORY_VENDOR_SPECIFIC2) && (mem_address_index <= 255))
				//					{
				//						I2C_Slave_Buffer_A0_P3_Up[tmp_mem_address_index] = write_value;
				//					}
				//					else {
				//						return;
				//					}
				//					break;

			case 0x80:
				t_page_no = 10;
				if (page_password_enable[t_page_no] == 1)
				{
					I2C_Slave_Buffer_A2_P80H_Up[tmp_mem_address_index] = write_value;
					insert_write_entry(dev_addr, page_select_value, mem_address_index);
				}
				break;

			case 0x81:
				t_page_no = 11;
				if (page_password_enable[t_page_no] == 1)
				{
					I2C_Slave_Buffer_A2_P81H_Up[tmp_mem_address_index] = write_value;
					insert_write_entry(dev_addr, page_select_value, mem_address_index);
				}
				break;

			case 0x82:
				t_page_no = 12;
				if (page_password_enable[t_page_no] == 1)
				{
					I2C_Slave_Buffer_A2_P82H_Up[tmp_mem_address_index] = write_value;
					insert_write_entry(dev_addr, page_select_value, mem_address_index);
				}
				break;

			case 0x83:
				t_page_no = 13;
				if (page_password_enable[t_page_no] == 1)
				{
					I2C_Slave_Buffer_A2_P83H_Up[tmp_mem_address_index] = write_value;
					insert_write_entry(dev_addr, page_select_value, mem_address_index);
				}
				break;

			case 0x84:
				t_page_no = 14;
				if (page_password_enable[t_page_no] == 1)
				{
					I2C_Slave_Buffer_A2_P84H_Up[tmp_mem_address_index] = write_value;
					insert_write_entry(dev_addr, page_select_value, mem_address_index);
				}
				break;

			default:
				return;
			}
			//			insert_write_entry(dev_addr, page_select_value, mem_address_index);
		}
	}
	else if (dev_addr == 0xA0)
	{
		if (page_password_enable[9] == 1)
		{
			I2C_Slave_Buffer_A0_Local_Memory[mem_address_index] = write_value;
			insert_write_entry(dev_addr, dev_addr, mem_address_index);
		}
	}
}

void insert_write_entry(uint8_t dev_addr, uint8_t page, uint8_t write_addr)
{
	if (write_i2c_list[write_i2c_count].page == (uint8_t)0xFF)
	{
		write_i2c_list[write_i2c_count].page = page;
		write_i2c_list[write_i2c_count].addr = write_addr;
		write_i2c_count = (write_i2c_count + 1) % MAX_WRITE_LIST_ENTRY;
		//                *((unsigned int)&I2C_Slave_Buffer_A4_Local_Memory[0xF2]) = __swap_bytes(write_i2c_count); // for DEBUG, 191104
	}
}

uint8_t get_reg_memory(uint8_t dev_addr, uint8_t page, uint8_t mem_address_index)
{
	uint8_t xdata rx_memory_value, tmp_mem_address_index, page_select_value;

	if (dev_addr == 0xA2)
	{
		if (mem_address_index < (uint8_t)LOWER_PAGE_ADDR)
		{
			rx_memory_value = I2C_Slave_Buffer_A2[mem_address_index];
		}
		else
		{
			page_select_value = page;
			tmp_mem_address_index = mem_address_index & (uint8_t)0x7F;
			switch (page_select_value)
			{
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

			case 0x84:
				rx_memory_value = I2C_Slave_Buffer_A2_P84H_Up[tmp_mem_address_index];
				break;

			default:
				rx_memory_value = 0xDD;
				break;
			}
		}
	}
	else if (dev_addr == 0xA0)
	{
		rx_memory_value = I2C_Slave_Buffer_A0_Local_Memory[mem_address_index];
	}
	return ((uint8_t)rx_memory_value);
}

void polled_write_entry(void)
{
	uint8_t xdata idx, c_page, c_addr, c_dev_addr, c_value;

	for (idx = 0; idx < MAX_WRITE_LIST_ENTRY; idx++)
	{
		if (write_i2c_list[read_i2c_count].page != (uint8_t)0xFF)
		{
			if (write_i2c_list[read_i2c_count].page == (uint8_t)0xA0)
			{
				c_dev_addr = 0xA0;
				c_page = 0;
				c_addr = write_i2c_list[read_i2c_count].addr;
			}
			else
			{
				c_dev_addr = 0xA2;
				c_page = write_i2c_list[read_i2c_count].page;
				c_addr = write_i2c_list[read_i2c_count].addr;
			}
			c_value = get_reg_memory(c_dev_addr, c_page, c_addr);

			exec_write_entry(c_dev_addr, c_page, c_addr, c_value);
			write_i2c_list[read_i2c_count].page = 0xFF;
			write_i2c_list[read_i2c_count].addr = 0xFF;

			read_i2c_count = (read_i2c_count + 1) % MAX_WRITE_LIST_ENTRY;

			//                        *((unsigned int *)&I2C_Slave_Buffer_A2_P02H_Up[0x40]) = __swap_bytes(read_i2c_count); // for DEBUG, 191104
		}
		else
		{
			if (read_i2c_count != write_i2c_count)
				read_i2c_count = write_i2c_count;
			//                        if (read_i2c_count != write_i2c_count)
			//                        {
			//                          read_i2c_count = (read_i2c_count + 1) % MAX_WRITE_LIST_ENTRY;
			//
			//                          *((unsigned int *)&I2C_Slave_Buffer_A2_P02H_Up[0x40]) = __swap_bytes(read_i2c_count); // for DEBUG, 191104
			//
			//                        }
			//                        else
			//                        {
			//                          break;
			//                        }
			break;
		}
	}
}

void exec_write_entry(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value)
{
	//	uint8_t xdata idx, c_page, c_addr, c_dev_addr, c_value;

	//        if (I2C_Slave_Memory_Map_Write(dev_addr, page, mem_addr, mem_value) == 0) {
	//          return;
	//        }

	if (dev_addr == 0xA2)
	{
		if (mem_addr < (uint8_t)LOWER_PAGE_ADDR)
		{
			exec_lower_page_memory(dev_addr, page, mem_addr, mem_value);
		}
		else
		{
			switch (page)
			{
			case 0x00:
				exec_upper_page0_memory(dev_addr, page, mem_addr, mem_value);
				break;

			case 0x01:
				exec_upper_page1_memory(dev_addr, page, mem_addr, mem_value);
				break;

			case 0x02:
				exec_upper_page2_memory(dev_addr, page, mem_addr, mem_value);
				break;

				//				case 0x03:
				//					exec_upper_page3_memory(dev_addr, page, mem_addr, mem_value);
				//					break;

			case 0x80:
				exec_upper_page80H_memory(dev_addr, page, mem_addr, mem_value);
				break;

			case 0x81:
				exec_upper_page81H_memory(dev_addr, page, mem_addr, mem_value);
				break;

			case 0x82:
				exec_upper_page82H_memory(dev_addr, page, mem_addr, mem_value);
				break;

			case 0x83:
				exec_upper_page83H_memory(dev_addr, page, mem_addr, mem_value);
				break;

			case 0x84:
				exec_upper_page84H_memory(dev_addr, page, mem_addr, mem_value);
				break;

			default:
				break;
			}
		}
	}
	else if (dev_addr == 0xA0)
	{
		exec_non_standard_A0_memory(dev_addr, page, mem_addr, mem_value);
	}
	return;
}

unsigned long __swap_bytes_to_long(unsigned long src)
{
	longDataType dest, t_long_data;

	t_long_data.long_data = src;
	dest.byte_data[0] = t_long_data.byte_data[3];
	dest.byte_data[1] = t_long_data.byte_data[2];
	dest.byte_data[2] = t_long_data.byte_data[1];
	dest.byte_data[3] = t_long_data.byte_data[0];

	return (dest.long_data);
}

float __swap_bytes_to_float(float src)
{
	longDataType dest, t_long_data;

	t_long_data.fp_data = src;
	dest.byte_data[0] = t_long_data.byte_data[3];
	dest.byte_data[1] = t_long_data.byte_data[2];
	dest.byte_data[2] = t_long_data.byte_data[1];
	dest.byte_data[3] = t_long_data.byte_data[0];

	return (dest.fp_data);
}

void check_password_control(void)
{
	uint8_t xdata page_no;
	unsigned long swap_long_data;

	swap_long_data = __swap_bytes_to_long(current_password.long_data);

	if (swap_long_data == FIXED_SIDE_SYSTEM_MANUFACTURER_PASSWORD_DEFAULT)
	{
		memset(&page_password_enable[0], 0x00, sizeof(page_password_enable));
		page_password_enable[0] = 1;
		page_password_enable[1] = 1;
		page_password_enable[2] = 1;
		page_password_enable[10] = 1; // for 80H flash program execution
		page_password_enable[11] = 1; // for 81H flash program execution
		page_password_enable[12] = 1; // for 81H flash program execution
		page_password_enable[9] = 1;
	}
	else if (swap_long_data == fixed_side_password.long_data)
	{
		memset(&page_password_enable[0], 0x00, sizeof(page_password_enable));
		page_password_enable[0] = 1;
		page_password_enable[1] = 1;
		page_password_enable[2] = 1;
		page_password_enable[10] = 1; // for 80H flash program execution
		page_password_enable[11] = 1; // for 81H flash program execution
		page_password_enable[12] = 1; // for 81H flash program execution
		page_password_enable[9] = 1;
	}
	else if ((swap_long_data & 0xFFFFFFF0) == (FREE_SIDE_SYSTEM_MANUFACTURER_PASSWORD_DEFAULT & 0xFFFFFFF0))
	{
		page_no = current_password.byte_data[3] & 0x0F;
		//		memset(&page_password_enable[0],0x01,sizeof(page_password_enable));
		//		page_password_enable[2] = 0;
		memset(&page_password_enable[0], 0x00, sizeof(page_password_enable));
		page_password_enable[page_no] = 1;
		page_password_enable[10] = 1; // for 80H flash program execution
		page_password_enable[11] = 1; // for 81H flash program execution
		page_password_enable[12] = 1; // for 82H flash program execution
		page_password_enable[13] = 1; // for 83H flash program execution
		page_password_enable[14] = 1; // for 84H flash program execution
		page_password_enable[9] = 1;
	}
	else if (swap_long_data == FREE_SIDE_SYSTEM_MANUFACTURER_PASSWORD_DEFAULT_2)
	{
		memset(&page_password_enable[0], 0x01, sizeof(page_password_enable));
		page_password_enable[0] = 0;
		page_password_enable[1] = 0;
	}
	else if (swap_long_data == FREE_SIDE_SYSTEM_MANUFACTURER_PASSWORD_DEFAULT_3)
	{
		page_vendor_control = 1;
	}
	else if (swap_long_data == FREE_SIDE_SYSTEM_MANUFACTURER_PASSWORD_DEFAULT_4)
	{
		page_vendor_control = 0;
	}
	else if (swap_long_data == FIXED_SIDE_SYSTEM_MANUFACTURER_PASSWORD_FW_DOWNLOAD)
	{
		I2C_Slave_Buffer_A2[A2_LUT_MODE_OFF] = 0x00;
		DEV_NUM = 0x00;
	}

	I2C_Slave_Buffer_A2[A2_PASSWORD_OFF + 0] = 0xFF;
	I2C_Slave_Buffer_A2[A2_PASSWORD_OFF + 1] = 0xFF;
	I2C_Slave_Buffer_A2[A2_PASSWORD_OFF + 2] = 0xFF;
	I2C_Slave_Buffer_A2[A2_PASSWORD_OFF + 3] = 0xFF;
}

void exec_lower_page_memory(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value)
{
	// uint8_t xdata c_dev_addr, c_addr, c_page, c_length, c_value[4];
#if __EXTERNAL_CALIBRATION_ENABLE_OPTIONS__ == 1
	A2_LOWER_MEMORY_MAP xdata *lowMemPtr;
	IEEE_754_FP_Type m_data;
	unsigned int unDdm_value;
	signed int sddm_value;
#endif

	//        unsigned char tmpValue;
	//
	//	uint8_t xdata rVal1, rVal2;
	//	uint8_t tmp_mem_address_index, page_select_value;
	uint8_t xdata r_val1;

#if __EXTERNAL_CALIBRATION_ENABLE_OPTIONS__ == 1
	lowMemPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];
#endif

	switch (mem_addr)
	{

	case (A2_PASSWORD_OFF + 3):
		check_password_control();
		break;

#if __EXTERNAL_CALIBRATION_ENABLE_OPTIONS__ == 1
	case (A2_RX_PWR_EXT_COEFF_4_OFF + 3):
		m_data.fp = __swap_bytes_to_float(lowMemPtr->A2_RX_PWR_4);
		ext_calib_rxPower_coeff_4 = m_data.fp;
		break;

	case (A2_RX_PWR_EXT_COEFF_3_OFF + 3):
		m_data.fp = __swap_bytes_to_float(lowMemPtr->A2_RX_PWR_3);
		ext_calib_rxPower_coeff_3 = m_data.fp;
		break;

	case (A2_RX_PWR_EXT_COEFF_2_OFF + 3):
		m_data.fp = __swap_bytes_to_float(lowMemPtr->A2_RX_PWR_2);
		ext_calib_rxPower_coeff_2 = m_data.fp;
		break;

	case (A2_RX_PWR_EXT_COEFF_1_OFF + 3):
		m_data.fp = __swap_bytes_to_float(lowMemPtr->A2_RX_PWR_1);
		ext_calib_rxPower_coeff_1 = m_data.fp;
		break;

	case (A2_RX_PWR_EXT_COEFF_0_OFF + 1):
		m_data.fp = __swap_bytes_to_float(lowMemPtr->A2_RX_PWR_0);
		ext_calib_rxPower_coeff_0 = m_data.fp;
		break;

	case (A2_TX_I_SLOPE_OFF + 1):
		unDdm_value = __swap_bytes(lowMemPtr->A2_TX_I_Slope);
		ext_calib_Tx_I_Slope = (FP32)((FP32)unDdm_value / 256.0);
		break;

	case (A2_TX_I_OFFSET_OFF + 1):
		sddm_value = (signed int)__swap_bytes(lowMemPtr->A2_TX_I_Offset);
		ext_calib_Tx_I_Offset = sddm_value;
		break;

	case (A2_TX_PWR_SLOPE_OFF + 1):
		unDdm_value = __swap_bytes(lowMemPtr->A2_TX_PWR_Slope);
		ext_calib_txPower_coeff_1 = (FP32)((FP32)unDdm_value / 256.0);
		break;

	case (A2_TX_PWR_OFFSET_OFF + 1):
		sddm_value = (signed int)__swap_bytes(lowMemPtr->A2_TX_PWR_Offset);
		ext_calib_txPower_coeff_0 = sddm_value;
		break;

	case (A2_TEMP_SLOPE_OFF + 1):
		unDdm_value = __swap_bytes(lowMemPtr->A2_Temp_Slope);
		ext_calib_Temp_Slope = (FP32)((FP32)unDdm_value / 256.0);
		break;

	case (A2_TEMP_OFFSET_OFF + 1):
		sddm_value = (signed int)__swap_bytes(lowMemPtr->A2_Temp_Offset);
		ext_calib_Temp_Offset = sddm_value;
		break;

	case (A2_VCC_SLOPE_OFF + 1):
		unDdm_value = __swap_bytes(lowMemPtr->A2_VCC_Slope);
		ext_calib_Vcc_Slope = (FP32)((FP32)unDdm_value / 256.0);
		break;

	case (A2_VCC_OFFSET_OFF + 1):
		sddm_value = (signed int)__swap_bytes(lowMemPtr->A2_VCC_Offset);
		ext_calib_Vcc_Offset = sddm_value;
		break;
#endif

	case (A2_STATUS_CONTROL_OFF):
		// ISR ��ƾ���� ó����
		update_rate_select_operation();

#if __HSFP_10G_MULTI_RATE_SEMI_TUNABLE__ == 1

#if __HFR_REQ_VER__ == 1
		//            save_to_flash_memory(0x02);
		save_to_flash_memory_ch_no();
#else
		save_to_flash_memory(0x02);
#endif

#else
#endif
		break;

	case (A2_TXEQ_72_OFF):
		// TX INPUT EQUALIZATION: TX CDR CONTROL
		r_val1 = (mem_value >> 4) & 0x0F;
		//          r_val2 = mem_value & 0x0F;

		tx_input_equalization(1, r_val1);

		break;

	case (A2_RXPREEMP_73_OFF):
		// RX_OUTPUT_DEEMPH: RX CDR CONTROL
		r_val1 = (mem_value >> 4) & 0x0F;
		//          r_val2 = mem_value & 0x0F;

		rx_output_deemphasis(1, r_val1);

		break;

	case (A2_EXTENDED_CONTROL_STATUS_OFF):
		update_rate_select_operation();

#if __HSFP_10G_MULTI_RATE_SEMI_TUNABLE__ == 1

#if __HFR_REQ_VER__ == 1
		//            save_to_flash_memory(0x02);
		save_to_flash_memory_ch_no();
#else
		save_to_flash_memory(0x02);
#endif

#else
#endif
		//          tmpValue = page_password_enable[0];
		//          page_password_enable[0] = 1;
		//          save_to_flash_memory(0x00);
		//          page_password_enable[0] = tmpValue;
		break;

	case (A2_64GFC_MODE_OFF):
		break;

	case (A2_TABLE_OFF):
#if __INTEROPERABILITY_TEST_POLL_PAGESEL__ == 1

		if (check_current_upper_page(mem_value) == 1)
		{
			// Page is different, update upper memory
			update_upper_page(mem_value);
			//            I2C_Slave_Buffer_A2[mem_address_index] = write_value;
		}
		else
		{
			// Page is same, do not update upper memory
			//            I2C_Slave_Buffer_A2[mem_address_index] = write_value;
		}
#endif
		break;
	}
}

void exec_upper_page0_memory(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value)
{
}

void exec_upper_page1_memory(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value)
{
}

void exec_upper_page2_memory(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value)
{
	//	uint8_t c_dev_addr, c_addr, c_page, c_length, c_value[4], idx, page_no, t_data;
	PAGE_02H_MEMORY_MAP *controlMemoryPtr, *controlMemoryPtr_1;
	//	IEEE_754_FP_Type m_data, m_data1;
	//	IEEE_754_FP_Type m_data;
	//	int16_t * tmpPtr;
	//        uint16_t  ch_no_set, ch_wavelength_set;
	uint16_t ch_no_set;
	A2_PAGE_80H_MEMORY_MAP *flashPtr;
	A2_PAGE_81H_MEMORY_MAP *flashPtr_1;
	unsigned int unDdm_value, ref_v_thm_value, idx_tec_check_cnt;
	int diff_value;
	unsigned int p2_current_status, p2_latched_status, new_channel_flag;
	A2_LOWER_MEMORY_MAP *lowerMemoryPtr;

	controlMemoryPtr_1 = (PAGE_02H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_Pn_Up[0];
	lowerMemoryPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];

	new_channel_flag = 0;
	controlMemoryPtr = (PAGE_02H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P02H_Up[0];
	flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
	flashPtr_1 = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P81H_Up[0];

	p2_current_status = controlMemoryPtr->Current_Status;
	p2_latched_status = controlMemoryPtr->Latched_Status;

	switch ((mem_addr & 0x7F))
	{
	case (P02H_CHANNEL_NUMBER_SET + 1):
		ch_no_set = __swap_bytes(controlMemoryPtr->Channel_Number_Set);
		// A, B Group: 1, 2, 3, 4
		// C, D Group: 5, 6, 7, 8
		//          if ((ch_no_set >= 1) && (ch_no_set <= 4))

#if __TUNABLE_CH_UPDATE_VER_1__ == 1
		if ((ch_no_set >= 1) && (ch_no_set <= 4))
		{
			if ((curr_channel_no >= 1) && (curr_channel_no <= 4))
			{
				if (curr_channel_no != ch_no_set)
				{
					new_channel_flag = 1;
				}
				curr_channel_no = ch_no_set;
			}
			else if ((curr_channel_no >= 5) && (curr_channel_no <= 8))
			{
				controlMemoryPtr->Channel_Number_Set = __swap_bytes(curr_channel_no);
			}
			else
			{
				if (curr_channel_no != ch_no_set)
				{
					new_channel_flag = 1;
				}
				curr_channel_no = ch_no_set;
			}
		}
		else if ((ch_no_set >= 5) && (ch_no_set <= 8))
		{
			if ((curr_channel_no >= 5) && (curr_channel_no <= 8))
			{
				if (curr_channel_no != ch_no_set)
				{
					new_channel_flag = 1;
				}
				curr_channel_no = ch_no_set;
			}
			else if ((curr_channel_no >= 1) && (curr_channel_no <= 4))
			{
				controlMemoryPtr->Channel_Number_Set = __swap_bytes(curr_channel_no);
			}
			else
			{
				if (curr_channel_no != ch_no_set)
				{
					new_channel_flag = 1;
				}
				curr_channel_no = ch_no_set;
			}
		}
		else
		{
			if ((curr_channel_no >= 1) && (curr_channel_no <= 8))
			{
				controlMemoryPtr->Channel_Number_Set = __swap_bytes(curr_channel_no);
			}
			else
			{
				p2_latched_status = p2_latched_status | 0x10;
				controlMemoryPtr->Latched_Status = p2_latched_status;
				if (lowerMemoryPtr->A2_TABLE == 0x02)
				{
					controlMemoryPtr_1->Latched_Status = p2_latched_status;
				}

				curr_channel_no = 1;
			}
		}

#else
		if ((ch_no_set >= 1) && (ch_no_set <= 8))
		{
			if (curr_channel_no != ch_no_set)
			{
				new_channel_flag = 1;
			}
			curr_channel_no = ch_no_set;
		}
		else
		{
			p2_latched_status = p2_latched_status | 0x10;
			controlMemoryPtr->Latched_Status = p2_latched_status;
			if (lowerMemoryPtr->A2_TABLE == 0x02)
			{
				controlMemoryPtr_1->Latched_Status = p2_latched_status;
			}

			curr_channel_no = 1;
		}

#endif

		//          I2C_Slave_Buffer_A2_P02H_Up[P02H_CURR_STAT_DEBUG] = 2;

		//          ModBiasSet = __swap_bytes(flashPtr->nt_ModBiasSet[curr_channel_no-1]);
		//
		//          XconBiasSet = __swap_bytes(flashPtr->nt_XconBiasSet[curr_channel_no-1]);
		//
		//          forcedLdBiasSet = __swap_bytes(flashPtr->nt_LdBiasSet[curr_channel_no-1]);

		PLA_Soft_TXD_Control(ASSERTED);
		PLA_Soft_Tx_Fault_Control_at_TxTune(ASSERTED);

		p2_current_status = p2_current_status | 0x10;
		controlMemoryPtr->Current_Status = p2_current_status;
		if (lowerMemoryPtr->A2_TABLE == 0x02)
		{
			controlMemoryPtr_1->Current_Status = p2_current_status;
		}

		//          flashPtr->ModBiasSet = flashPtr->nt_ModBiasSet[curr_channel_no-1];
		//
		//          flashPtr->XconBiasSet = flashPtr->nt_XconBiasSet[curr_channel_no-1];
		//
		//          flashPtr->forcedLdBiasSet = flashPtr->nt_LdBiasSet[curr_channel_no-1];

		flashPtr->ModBiasSet = flashPtr->nt_ModBiasSet[(curr_channel_no - 1) % 4];

		flashPtr->XconBiasSet = flashPtr->nt_XconBiasSet[(curr_channel_no - 1) % 4];

		flashPtr->forcedLdBiasSet = flashPtr->nt_LdBiasSet[(curr_channel_no - 1) % 4];

		ModBiasSet = __swap_bytes(flashPtr->ModBiasSet);

		XconBiasSet = __swap_bytes(flashPtr->XconBiasSet);

		forcedLdBiasSet = __swap_bytes(flashPtr->forcedLdBiasSet);

		//          ConfigTec1(INDEX_TEC_SETPOINT, __swap_bytes(flashPtr->TEC1_SETPOINT));
		//          flashPtr_1->TEC1_SETPOINT = flashPtr_1->tec_setpoint_per_wavelength[curr_channel_no-1];

		//          flashPtr_1->TEC1_SETPOINT = flashPtr_1->nt_tec_setpoint_per_wavelength[curr_channel_no-1];
		flashPtr_1->TEC1_SETPOINT = flashPtr_1->nt_tec_setpoint_per_wavelength[(curr_channel_no - 1) % 4];

		//          PLA_Soft_TXD_Control(ASSERTED);

		if ((flashPtr_1->PMIC_SELECT & TEC1_ENABLE) == TEC1_ENABLE)
		{
			ConfigTec1(INDEX_TEC_SETPOINT, __swap_bytes(flashPtr_1->TEC1_SETPOINT));
			//            TEC_Init();
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");

			ref_v_thm_value = __swap_bytes(flashPtr_1->TEC1_SETPOINT);

			for (idx_tec_check_cnt = 0; idx_tec_check_cnt < 3000; idx_tec_check_cnt++)
			{
				WDCN_bit.RWT = 1;						  // Reset Watchdog Timer
				unDdm_value = ADC_ReadOut(CONFG_VTHERM1); // read raw ADC

				flashPtr_1->V_THM = __swap_bytes(unDdm_value); // update raw adc to A0h

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
			}

			if (diff_value > (TEC_STABLE_DIFF_RANGE * 10))
			{
				p2_current_status = p2_current_status | 0x60;
				p2_latched_status = p2_latched_status | 0x60;

				controlMemoryPtr->Current_Status = p2_current_status;
				controlMemoryPtr->Latched_Status = p2_latched_status;

				if (lowerMemoryPtr->A2_TABLE == 0x02)
				{
					controlMemoryPtr_1->Current_Status = p2_current_status;
					controlMemoryPtr_1->Latched_Status = p2_latched_status;
				}
			}
		}

		//          cdr_power_management_init(0);

		prevLdBiasDa = 0;
		prevModBiasDa = 0;
		prevXconBiasDa = 0;

		LdControl(0, 0);

		//          SW_Delay(10000);
		SW_Delay(1000);

		PLA_Soft_Tx_Fault_Control_at_TxTune(DE_ASSERTED);
		PLA_Soft_TXD_Control(DE_ASSERTED);

		p2_current_status = p2_current_status & 0xEF;

		if (new_channel_flag == 1)
		{
			p2_latched_status = p2_latched_status | 0x08;
		}

		controlMemoryPtr->Current_Status = p2_current_status;
		controlMemoryPtr->Latched_Status = p2_latched_status;

		if (lowerMemoryPtr->A2_TABLE == 0x02)
		{
			controlMemoryPtr_1->Current_Status = p2_current_status;
			controlMemoryPtr_1->Latched_Status = p2_latched_status;
		}

		wavelength_info_set();

		if (new_channel_flag == 1)
		{
			// [DCLEE] 200923 --> Save eeprom for page 02H, �켱 ���۽�Ű�� ����
#if __HFR_REQ_VER__ == 1
			//            save_to_flash_memory(0x02);
			save_to_flash_memory_ch_no();
#else
			save_to_flash_memory(0x02);
#endif
		}

		break;

	case (P02H_WAVELENGTH_SET + 1):
		//          ch_wavelength_set = __swap_bytes(controlMemoryPtr->Wavelength_Set);

		//          if ((ch_no_set >= 1) && (ch_no_set <= 4))
		//          {
		//            curr_channel_no = ch_no_set;
		//          }
		//          else
		//          {
		//            curr_channel_no = 1;
		//          }

		wavelength_info_set();

		break;

	case (0x7F):
#if __HFR_REQ_VER__ == 1
		save_to_flash_memory(0x02);
//            save_to_flash_memory_ch_no();
#endif

		break;
	}
}

void exec_upper_page82H_memory(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value)
{
	write_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, (mem_addr & 0x7F), mem_value);
}

void exec_upper_page83H_memory(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value)
{
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
#else
	// TX&RX Combo CDR: MAOM-37032A
	write_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, (mem_addr & 0x7F), mem_value);
#endif
}

void exec_upper_page84H_memory(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value)
{
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1

#else
	// TX&RX Combo CDR: MAOM-37032A
	write_master_gpio_single_byte(TX_RX_COMBO_CDR_PMIC_I2C_ADDR, (mem_addr & 0x7F), mem_value);
#endif
}

void exec_upper_page80H_memory(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value)
{
	uint8_t c_dev_addr, c_addr, c_page, c_length, c_value[4], idx, page_no, t_data;
	A2_PAGE_80H_MEMORY_MAP *flashPtr, *flashPtr_1;
	A2_LOWER_MEMORY_MAP *lowerMemoryPtr;

	//	IEEE_754_FP_Type m_data, m_data1;
	//	IEEE_754_FP_Type m_data;
	//	int16_t * tmpPtr;

	flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
	flashPtr_1 = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_Pn_Up[0];
	lowerMemoryPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];

	switch ((mem_addr & 0x7F))
	{
	case (FLASH_COMMAND):

		c_page = flashPtr->page;
		c_page = c_page;

		c_addr = flashPtr->addr;
		c_addr = c_addr;

		c_length = flashPtr->data_length;

		if (c_length > 4)
			c_length = 4;

		if ((flashPtr->command & 0x0F) == (uint8_t)0x04)
		{ // Restore
			t_data = flashPtr->command;
			t_data = (t_data & 0xFC) | 0x02;
			flashPtr->command = t_data;
			if (lowerMemoryPtr->A2_TABLE == 0x80)
			{
				flashPtr_1->command = t_data;
			}

			//            page_no = (flashPtr->command & 0xF0) >> 4;
			page_no = c_page;

			restore_from_flash_memory(page_no);

			t_data = (t_data & 0xFC) | 0x01;
			flashPtr->command = t_data;
			if (lowerMemoryPtr->A2_TABLE == 0x80)
			{
				flashPtr_1->command = t_data;
			}
		}
		else if ((flashPtr->command & 0x0F) == (uint8_t)0x08)
		{ // Save
			t_data = flashPtr->command;
			t_data = (t_data & 0xFC) | 0x02;
			flashPtr->command = t_data;
			if (lowerMemoryPtr->A2_TABLE == 0x80)
			{
				flashPtr_1->command = t_data;
			}

			//            page_no = (flashPtr->command & 0xF0) >> 4;
			page_no = c_page;

			save_to_flash_memory(page_no);

			t_data = (t_data & 0xFC) | 0x01;
			flashPtr->command = t_data;
			if (lowerMemoryPtr->A2_TABLE == 0x80)
			{
				flashPtr_1->command = t_data;
			}
		}
		else if (flashPtr->command == (uint8_t)0x20)
		{
			// DRIVER Control IC: MAMF011039
			flashPtr->command = 0x22;
			if (lowerMemoryPtr->A2_TABLE == 0x80)
			{
				flashPtr_1->command = 0x22;
			}

			flashPtr->command = 0x21;
			if (lowerMemoryPtr->A2_TABLE == 0x80)
			{
				flashPtr_1->command = 0x21;
			}
		}
		else if (flashPtr->command == (uint8_t)0x40)
		{
			// TX CDR: M37049
			flashPtr->command = 0x42;
			if (lowerMemoryPtr->A2_TABLE == 0x80)
			{
				flashPtr_1->command = 0x42;
			}

			//            c_dev_addr = TX_RX_COMBO_CDR_I2C_ADDR;
			//
			//            for (idx=0; idx<4; idx++)
			//            {
			//              //c_value[idx] = I2C_Slave_Buffer_A4_Local_Memory[FLASH_W_DATA(idx+1)];
			//              c_value[idx] = flashPtr->r_data[idx];
			//            }
			//            write_master_gpio_single_byte(c_dev_addr,  c_addr, c_value[0]);

			//            PLACNT1_bit.SB1 = TXDIS_CDR_ON; // Using Soft TXDIS pin ���
			//
			//           cdr_power_management_init(0);
			//           PLACNT1_bit.SB1 = TXDIS_CDR_OFF; // Using Soft TXDIS pin ���

			cdr_pmic_ch_control_reinit(0);
			prevLdBiasDa = 0;
			prevModBiasDa = 0;
			prevXconBiasDa = 0;

			flashPtr->command = 0x41;
			if (lowerMemoryPtr->A2_TABLE == 0x80)
			{
				flashPtr_1->command = 0x41;
			}
		}
		else if (flashPtr->command == (uint8_t)0x80)
		{
			// RX CDR: M37046
			flashPtr->command = 0x82;
			if (lowerMemoryPtr->A2_TABLE == 0x80)
			{
				flashPtr_1->command = 0x82;
			}

			c_dev_addr = TX_RX_COMBO_CDR_I2C_ADDR;

			for (idx = 0; idx < 4; idx++)
			{
				// c_value[idx] = I2C_Slave_Buffer_A4_Local_Memory[FLASH_W_DATA(idx+1)];
				c_value[idx] = flashPtr->r_data[idx];
			}
			write_master_gpio_single_byte(c_dev_addr, c_addr, c_value[0]);

			flashPtr->command = 0x81;
			if (lowerMemoryPtr->A2_TABLE == 0x80)
			{
				flashPtr_1->command = 0x81;
			}
		}
		else if (flashPtr->command == (uint8_t)0x30)
		{
			// Read DRIVER Control IC: MAMF011039
			flashPtr->command = 0x32;
			if (lowerMemoryPtr->A2_TABLE == 0x80)
			{
				flashPtr_1->command = 0x32;
			}

			// #if __QSFP28_LR4__== 1
			//             c_dev_addr = LD_DRIVER_I2C_ADDR;
			// #endif
			//
			//
			//             polled_LD_DC_reg_info(flashPtr->page);

			flashPtr->command = 0x31;
			if (lowerMemoryPtr->A2_TABLE == 0x80)
			{
				flashPtr_1->command = 0x31;
			}
		}
		else if (flashPtr->command == (uint8_t)0x50)
		{
			// Read TX CDR: M37049
			flashPtr->command = 0x52;
			if (lowerMemoryPtr->A2_TABLE == 0x80)
			{
				flashPtr_1->command = 0x52;
			}

			c_dev_addr = TX_RX_COMBO_CDR_I2C_ADDR;

			polled_tx_rx_combo_cdr_reg_info();

			flashPtr->command = 0x51;
			if (lowerMemoryPtr->A2_TABLE == 0x80)
			{
				flashPtr_1->command = 0x51;
			}
		}
		else if (flashPtr->command == (uint8_t)0x90)
		{
			// Read RX CDR: M37046
			flashPtr->command = 0x92;
			if (lowerMemoryPtr->A2_TABLE == 0x80)
			{
				flashPtr_1->command = 0x92;
			}

			//            c_dev_addr = RX_CDR_I2C_ADDR;
			//            polled_rx_cdr_reg_info();

			flashPtr->command = 0x91;
			if (lowerMemoryPtr->A2_TABLE == 0x80)
			{
				flashPtr_1->command = 0x91;
			}
		}
		else if (flashPtr->command == (uint8_t)0x10)
		{
			// Set TOSA Target Power
			flashPtr->command = 0x12;
			if (lowerMemoryPtr->A2_TABLE == 0x80)
			{
				flashPtr_1->command = 0x12;
			}

			flashPtr->command = 0x11;
			if (lowerMemoryPtr->A2_TABLE == 0x80)
			{
				flashPtr_1->command = 0x11;
			}
		}
		break;

	case (FLASH_LD_CONTROL_MODE):
		LdControlMode = flashPtr->LdControlMode;
		break;

	case (FLASH_MOD_BIAS_SET + 1):
		// Modulation Control
		ModBiasSet = __swap_bytes(flashPtr->ModBiasSet);
		ModBiasControl_manually(0, 0);

		break;

	case (FLASH_XCON_BIAS_SET + 1):
		XconBiasSet = __swap_bytes(flashPtr->XconBiasSet);
		XconBiasControl(0, 0);
		break;

	case (FLASH_FORCED_LD_BIAS_SET + 1):
		forcedLdBiasSet = __swap_bytes(flashPtr->forcedLdBiasSet);
		LdControl_manually(0, 0);
		// Bias Control
		break;

	case (FLASH_NT_TEMP + 1):
		cal_Temp_Slope_Offset();
		break;

	case (FLASH_HT_TEMP + 1):
		cal_Temp_Slope_Offset();
		break;

	case (FLASH_LT_TEMP + 1):
		cal_Temp_Slope_Offset();
		break;

		//
		// #if __NEW_TX_POWER_MON_BY_TEMPERATURE__==1
		//        case (FLASH_TX_POWER_HTEMP + 1):
		//          calSlope_Offset(0);
		//          break;
		//
		//        case (FLASH_TX_POWER_NORMTEMP + 1):
		//          calSlope_Offset(0);
		//          break;
		//
		//        case (FLASH_TX_POWER_LTEMP + 1):
		//          calSlope_Offset(0);
		//          break;
		//
		// #else
		//
		// #endif
		//        case (FLASH_RX_POWER_COEFF_0 + 3):
		//            m_data.fp = __swap_bytes_to_float(flashPtr->rxPower_coeff_0);
		//            rxPower_coeff_0 = m_data.fp;
		//          break;
		//
		//        case (FLASH_RX_POWER_COEFF_1 + 3):
		//          m_data.fp = __swap_bytes_to_float(flashPtr->rxPower_coeff_1);
		//          rxPower_coeff_1 = m_data.fp;
		//          break;
		//
		//        case (FLASH_RX_POWER_COEFF_2 + 3):
		//          m_data.fp = __swap_bytes_to_float(flashPtr->rxPower_coeff_2);
		//          rxPower_coeff_2 = m_data.fp;
		//          break;
		//
		//        case (FLASH_RX_POWER_COEFF_3 + 3):
		//          m_data.fp = __swap_bytes_to_float(flashPtr->rxPower_coeff_3);
		//          rxPower_coeff_3 = m_data.fp;
		//          break;
		//
		//        case (FLASH_RX_POWER_COEFF_4 + 3):
		//          m_data.fp = __swap_bytes_to_float(flashPtr->rxPower_coeff_4);
		//          rxPower_coeff_4 = m_data.fp;
		//          break;
	}
}

void exec_upper_page81H_memory(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value)
{
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
	// GN_1157

	//	uint8_t c_dev_addr, c_addr, c_page, c_length, c_value[4], idx, page_no, t_data;
	//	uint8_t c_chNo;
	A2_PAGE_81H_MEMORY_MAP *flashPtr;
	//	IEEE_754_FP_Type m_data, m_data1;
	IEEE_754_FP_Type m_data;
	//	int16_t * tmpPtr;
	//        unsigned int unData = 0, unData_1 = 0;

	flashPtr = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P81H_Up[0];

	switch ((mem_addr & 0x7F))
	{
	case (FLASH_PMIC_SELECT):
		TEC_Init();
		APD_Init();
		//          IDAC_Init();

		break;

	case (FLASH_TEC1_SETPOINT + 1): // update TEC setpoint
		ConfigTec1(INDEX_TEC_SETPOINT, __swap_bytes(flashPtr->TEC1_SETPOINT));
		break;

	case (FLASH_TEC1_KP + 1):
		ConfigTec1(INDEX_TEC_Kp, __swap_bytes(flashPtr->TEC1_KP)); // update TEC Kp
		break;

	case (FLASH_TEC1_KI + 1):
		ConfigTec1(INDEX_TEC_Ki, __swap_bytes(flashPtr->TEC1_KI)); // update Ki
		break;

	case (FLASH_TEC1_KD + 1):
		ConfigTec1(INDEX_TEC_Kd, __swap_bytes(flashPtr->TEC1_KD)); // update Kd
		break;

	case (FLASH_TEC1_SHIFT + 1): // udpate shift
		ConfigTec1(INDEX_TEC_SHIFT, __swap_bytes(flashPtr->TEC1_SHIFT));
		break;

	case (FLASH_TEC1_POSERRCLAMP + 1): // update positive error clamp
		ConfigTec1(INDEX_TEC_POS_ERR_CP, __swap_bytes(flashPtr->TEC1_POSERRCLAMP));
		break;

	case (FLASH_TEC1_NEGERRCLAMP + 1): // update negative error clamp
		ConfigTec1(INDEX_TEC_NEG_ERR_CP, __swap_bytes(flashPtr->TEC1_NEGERRCLAMP));
		break;

	case (FLASH_TEC1_POSOPCLAMP + 1): // update positive output clamp
		ConfigTec1(INDEX_TEC_POS_OP_CP, __swap_bytes(flashPtr->TEC1_POSOPCLAMP));

		break;

	case (FLASH_TEC1_NEGOPCLAMP + 1): // update negative output clamp
		ConfigTec1(INDEX_TEC_NEG_OP_CP, __swap_bytes(flashPtr->TEC1_NEGOPCLAMP));
		break;

	case (FLASH_TEC1_CNFGCURRENTMEA_BURSTGPIOCONFIG + 1): // update current configuration
		ConfigTec1(INDEX_TEC_CURR_CONFIG, __swap_bytes(flashPtr->TEC1_CNFGCURRENTMEA_BURSTGPIOCONFIG));
		break;

	case (FLASH_TEC1_OFFSETRIGGER + 1): // update offset trigger
		ConfigTec1(INDEX_TEC_OFFSET_TRIG, __swap_bytes(flashPtr->TEC1_OFFSETRIGGER));
		break;

	case (FLASH_TEC1_BURSTPWMDUTYOFFSET + 1): // update duty offset
		ConfigTec1(INDEX_TEC_DUTY_OFFSET, __swap_bytes(flashPtr->TEC1_BURSTPWMDUTYOFFSET));
		break;

	case (FLASH_TEC1_NORMAL_VCC + 1):
		NORMV = __swap_bytes(flashPtr->TEC1_NORMAL_VCC); // udpate normal VCC
		break;

#if __NEW_TX_POWER_MON_BY_TEMPERATURE__ == 1
	case (FLASH_TX_POWER_HTEMP + 1):
		calSlope_Offset(0);
		break;

	case (FLASH_TX_POWER_NORMTEMP + 1):
		calSlope_Offset(0);
		break;

	case (FLASH_TX_POWER_LTEMP + 1):
		calSlope_Offset(0);
		break;

#else
	case (FLASH_TX_POWER_COEFF_0 + 3):
		m_data.fp = __swap_bytes_to_float(flashPtr->txPower_coeff_0);

		//          if (curr_channel_no == 1)
		{
			txPower_coeff_0 = m_data.fp;
		}

		break;

	case (FLASH_TX_POWER_COEFF_1 + 3):
		m_data.fp = __swap_bytes_to_float(flashPtr->txPower_coeff_1);
		//          if (curr_channel_no == 1)
		{
			txPower_coeff_1 = m_data.fp;
		}
		break;

#endif
	case (FLASH_RX_POWER_COEFF_0 + 3):
		m_data.fp = __swap_bytes_to_float(flashPtr->rxPower_coeff_0);
		rxPower_coeff_0 = m_data.fp;
		break;

	case (FLASH_RX_POWER_COEFF_1 + 3):
		m_data.fp = __swap_bytes_to_float(flashPtr->rxPower_coeff_1);
		rxPower_coeff_1 = m_data.fp;
		break;

	case (FLASH_RX_POWER_COEFF_2 + 3):
		m_data.fp = __swap_bytes_to_float(flashPtr->rxPower_coeff_2);
		rxPower_coeff_2 = m_data.fp;
		break;

	case (FLASH_RX_POWER_COEFF_3 + 3):
		m_data.fp = __swap_bytes_to_float(flashPtr->rxPower_coeff_3);
		rxPower_coeff_3 = m_data.fp;
		break;

	case (FLASH_RX_POWER_COEFF_4 + 3):
		m_data.fp = __swap_bytes_to_float(flashPtr->rxPower_coeff_4);
		rxPower_coeff_4 = m_data.fp;
		break;

	// Manchester Mode Control at 0x82
	case A2_PAGE_81H_MANCHESTER_MODE_ADDR:
		// 구조체 멤버에 값 저장
		flashPtr->MANCHESTER_MODE_CONTROL = mem_value; // unsigned char로 변경됨
		// I2C 버퍼 직접 업데이트 (절대 주소 사용)
		I2C_Slave_Buffer_A2_P81H_Up[A2_PAGE_81H_MANCHESTER_MODE_ADDR] = mem_value;
		// 맨체스터 제어 함수 호출 - 0: 해제 모드, 1: 1분 모드, 5: 5분 모드
		Manchester_Control_I2C(mem_value);
		break;
	}

#else

	//	uint8_t c_dev_addr, c_addr, c_page, c_length, c_value[4], idx, page_no, t_data;
	//	uint8_t c_chNo;
	A2_PAGE_81H_MEMORY_MAP *flashPtr;
	//	IEEE_754_FP_Type m_data, m_data1;
	IEEE_754_FP_Type m_data;
	//	int16_t * tmpPtr;
	unsigned int unData = 0, unData_1 = 0;

	flashPtr = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P81H_Up[0];

	switch ((mem_addr & 0x7F))
	{
	case (FLASH_PMIC_SELECT):
		TEC_Init();
		APD_Init();
		//          IDAC_Init();

		break;

	case (FLASH_TEC1_SETPOINT + 1): // update TEC setpoint
		ConfigTec1(INDEX_TEC_SETPOINT, __swap_bytes(flashPtr->TEC1_SETPOINT));
		break;

	case (FLASH_TEC1_KP + 1):
		ConfigTec1(INDEX_TEC_Kp, __swap_bytes(flashPtr->TEC1_KP)); // update TEC Kp
		break;

	case (FLASH_TEC1_KI + 1):
		ConfigTec1(INDEX_TEC_Ki, __swap_bytes(flashPtr->TEC1_KI)); // update Ki
		break;

	case (FLASH_TEC1_KD + 1):
		ConfigTec1(INDEX_TEC_Kd, __swap_bytes(flashPtr->TEC1_KD)); // update Kd
		break;

	case (FLASH_TEC1_SHIFT + 1): // udpate shift
		ConfigTec1(INDEX_TEC_SHIFT, __swap_bytes(flashPtr->TEC1_SHIFT));
		break;

	case (FLASH_TEC1_POSERRCLAMP + 1): // update positive error clamp
		ConfigTec1(INDEX_TEC_POS_ERR_CP, __swap_bytes(flashPtr->TEC1_POSERRCLAMP));
		break;

	case (FLASH_TEC1_NEGERRCLAMP + 1): // update negative error clamp
		ConfigTec1(INDEX_TEC_NEG_ERR_CP, __swap_bytes(flashPtr->TEC1_NEGERRCLAMP));
		break;

	case (FLASH_TEC1_POSOPCLAMP + 1): // update positive output clamp
		ConfigTec1(INDEX_TEC_POS_OP_CP, __swap_bytes(flashPtr->TEC1_POSOPCLAMP));

		break;

	case (FLASH_TEC1_NEGOPCLAMP + 1): // update negative output clamp
		ConfigTec1(INDEX_TEC_NEG_OP_CP, __swap_bytes(flashPtr->TEC1_NEGOPCLAMP));
		break;

	case (FLASH_TEC1_CNFGCURRENTMEA_BURSTGPIOCONFIG + 1): // update current configuration
		ConfigTec1(INDEX_TEC_CURR_CONFIG, __swap_bytes(flashPtr->TEC1_CNFGCURRENTMEA_BURSTGPIOCONFIG));
		break;

	case (FLASH_TEC1_OFFSETRIGGER + 1): // update offset trigger
		ConfigTec1(INDEX_TEC_OFFSET_TRIG, __swap_bytes(flashPtr->TEC1_OFFSETRIGGER));
		break;

	case (FLASH_TEC1_BURSTPWMDUTYOFFSET + 1): // update duty offset
		ConfigTec1(INDEX_TEC_DUTY_OFFSET, __swap_bytes(flashPtr->TEC1_BURSTPWMDUTYOFFSET));
		break;

	case (FLASH_TEC1_NORMAL_VCC + 1):
		NORMV = __swap_bytes(flashPtr->TEC1_NORMAL_VCC); // udpate normal VCC
		break;

// APD Parameters
#if __HSFP_10G_ER_SEMI_TUNABLE__ == 1

#else

	case (FLASH_APD_ERRSTARTCLAMP + 1):
		APDIDX4 = IDX_ERRP_START_CLAMP; // APD Error Start Clamp
		APDDAT4 = __swap_bytes(flashPtr->APD_ERRSTARTCLAMP);

		APDIDX4 = IDX_DUTY; // Duty Cycle

		break;

	case (FLASH_APD_DUTYCLAMP + 1):
		APDIDX4 = IDX_DUTY_CLAMP; // APD Duty Clamp
		APDDAT4 = __swap_bytes(flashPtr->APD_DUTYCLAMP);

		APDIDX4 = IDX_DUTY; // Duty Cycle
		break;

	case (FLASH_APD_INTEGRALGAIN + 1):
		APDIDX4 = IDX_INTEGAL_GAIN; // APC Integral gain
		APDDAT4 = __swap_bytes(flashPtr->APD_INTEGRALGAIN);

		APDIDX4 = IDX_DUTY; // Duty Cycle
		break;

	case (FLASH_APD_DUTYSTARTINCCLAMP + 1):
		APDIDX4 = IDX_START_DUTY_CLAMP; // APD Duty Start Clamp
		APDDAT4 = __swap_bytes(flashPtr->APD_DUTYSTARTINCCLAMP);
		APDIDX4 = IDX_DUTY; // Duty Cycle
		break;

	case (FLASH_APD_INTEGRALCLAMP + 1):
		APDIDX4 = IDX_CLAMP_INTEGAL; // APD Integral clamp
		APDDAT4 = __swap_bytes(flashPtr->APD_INTEGRALCLAMP);
		APDIDX4 = IDX_DUTY; // Duty Cycle
		break;

	case (FLASH_APD_APDNEGERRCLAMP + 1):
		APDIDX4 = IDX_ERRN_CLAMP; // APD Error Negative Clamp
		APDDAT4 = __swap_bytes(flashPtr->APD_APDNEGERRCLAMP);
		APDIDX4 = IDX_DUTY; // Duty Cycle
		break;

	case (FLASH_APD_APDPOSERRCLAMP + 1):
		APDIDX4 = IDX_ERRP_CLAMP; // APD Error Positive Clamp
		APDDAT4 = __swap_bytes(flashPtr->APD_APDPOSERRCLAMP);
		;
		APDIDX4 = IDX_DUTY; // Duty Cycle
		break;

	case (FLASH_APD_PROPORTIONALGAIN + 1):
		APDIDX4 = IDX_PROP_GAIN; // APD Proportional Gain
		APDDAT4 = __swap_bytes(flashPtr->APD_PROPORTIONALGAIN);
		APDIDX4 = IDX_DUTY; // Duty Cycle
		break;

#endif

	case (FLASH_APD_TARGET_OUTPUT + 1):
		//            APDIDX2 = IDX_TARGET;                                           //APD Target Voltage
		//            APDDAT2 = CalcExternalBoostTarget( __swap_bytes(flashPtr->APD_TARGET_OUTPUT) );
		unData_1 = APDCN4;
		if ((unData_1 & 0x04) == 0x00)
		{
			if (flashPtr->APD_TARGET_OUTPUT > 500)
			{
				unData = CalcExternalBoostTarget(500);
			}
			APDIDX4 = IDX_TARGET; // Target Voltage
			APDDAT4 = unData;
			//        flashPtr->APD_CURRENT_SETTING = __swap_bytes(flashPtr->APD_TARGET_OUTPUT);
			flashPtr->APD_CURRENT_SETTING = __swap_bytes(unData);

			//            APDCN2 =  __swap_bytes(flashPtr->APD_CONFIG);                        //Configure APD setting
			//
			//            SW_Delay(1000);
			//
			//            unData  = CalcExternalBoostTarget( __swap_bytes(flashPtr->APD_TARGET_OUTPUT) );
			//            APDIDX2 = IDX_TARGET;                                                   //Target Voltage
			//            APDDAT2 = unData;
			//            //        flashPtr->APD_CURRENT_SETTING = __swap_bytes(flashPtr->APD_TARGET_OUTPUT);
			//            flashPtr->APD_CURRENT_SETTING = __swap_bytes(unData);

			//        APDCN2 =  __swap_bytes(flashPtr->APD_CONFIG);                        //Configure APD setting
		}
		else
		{
			APDIDX4 = IDX_TARGET; // APD Target Voltage
			APDDAT4 = CalcExternalBoostTarget(__swap_bytes(flashPtr->APD_TARGET_OUTPUT));
		}
		APDIDX4 = IDX_DUTY; // Duty Cycle
		break;

	case (FLASH_APD_CONFIG + 1):
		if (flashPtr->PMIC_SELECT & APD_ENABLE) // if APD is enabled?
		{
			//              APDCN2 =  __swap_bytes(flashPtr->APD_CONFIG);           //update APD CONFIG
			// Read APDCN2, when APDCN2_bits.
			unData = APDCN4;
			if ((unData & 0x04) == 0x00)
			{
				// Set Config Enable

				if (flashPtr->APD_TARGET_OUTPUT > 500)
				{

					unData = CalcExternalBoostTarget(500);
					APDIDX4 = IDX_TARGET; // Target Voltage
					APDDAT4 = unData;
					//        flashPtr->APD_CURRENT_SETTING = __swap_bytes(flashPtr->APD_TARGET_OUTPUT);
					flashPtr->APD_CURRENT_SETTING = __swap_bytes(unData);

					APDCN4 = __swap_bytes(flashPtr->APD_CONFIG); // Configure APD setting

					SW_Delay(1000);

					unData = CalcExternalBoostTarget(__swap_bytes(flashPtr->APD_TARGET_OUTPUT));
					APDIDX4 = IDX_TARGET; // Target Voltage
					APDDAT4 = unData;
					//        flashPtr->APD_CURRENT_SETTING = __swap_bytes(flashPtr->APD_TARGET_OUTPUT);
					flashPtr->APD_CURRENT_SETTING = __swap_bytes(unData);

					//        APDCN2 =  __swap_bytes(flashPtr->APD_CONFIG);                        //Configure APD setting
				}
				else
				{
					unData = CalcExternalBoostTarget(__swap_bytes(flashPtr->APD_TARGET_OUTPUT));
					APDIDX4 = IDX_TARGET; // Target Voltage
					APDDAT4 = unData;
					//        flashPtr->APD_CURRENT_SETTING = __swap_bytes(flashPtr->APD_TARGET_OUTPUT);
					flashPtr->APD_CURRENT_SETTING = __swap_bytes(unData);

					APDCN4 = __swap_bytes(flashPtr->APD_CONFIG); // Configure APD setting
				}
				APDIDX4 = IDX_DUTY; // Duty Cycle
			}
		}
		else
		{
			APDIDX4 = IDX_DUTY; // Duty Cycle
			APDCN4 = 0;			// if APD is disabled, set APDCN to 0
		}
		break;

#if __NEW_TX_POWER_MON_BY_TEMPERATURE__ == 1
	case (FLASH_TX_POWER_HTEMP + 1):
		calSlope_Offset(0);
		break;

	case (FLASH_TX_POWER_NORMTEMP + 1):
		calSlope_Offset(0);
		break;

	case (FLASH_TX_POWER_LTEMP + 1):
		calSlope_Offset(0);
		break;

#else
	case (FLASH_TX_POWER_COEFF_0 + 3):
		m_data.fp = __swap_bytes_to_float(flashPtr->txPower_coeff_0);

		//          if (curr_channel_no == 1)
		{
			txPower_coeff_0 = m_data.fp;
		}

		break;

	case (FLASH_TX_POWER_COEFF_1 + 3):
		m_data.fp = __swap_bytes_to_float(flashPtr->txPower_coeff_1);
		//          if (curr_channel_no == 1)
		{
			txPower_coeff_1 = m_data.fp;
		}
		break;

//        case (FLASH_TX_POWER_COEFF_0 + 7):
//          m_data.fp = __swap_bytes_to_float(flashPtr->txPower_coeff_0[1]);
//          if (curr_channel_no == 2)
//          {
//            txPower_coeff_0 = m_data.fp;
//          }
//          break;
//
//        case (FLASH_TX_POWER_COEFF_1 + 7):
//          m_data.fp = __swap_bytes_to_float(flashPtr->txPower_coeff_1[1]);
//          if (curr_channel_no == 2)
//          {
//            txPower_coeff_1 = m_data.fp;
//          }
//          break;
//
//        case (FLASH_TX_POWER_COEFF_0 + 11):
//          m_data.fp = __swap_bytes_to_float(flashPtr->txPower_coeff_0[2]);
//          if (curr_channel_no == 3)
//          {
//            txPower_coeff_0 = m_data.fp;
//          }
//          break;
//
//        case (FLASH_TX_POWER_COEFF_1 + 11):
//          m_data.fp = __swap_bytes_to_float(flashPtr->txPower_coeff_1[2]);
//          if (curr_channel_no == 3)
//          {
//            txPower_coeff_1 = m_data.fp;
//          }
//          break;
//
//        case (FLASH_TX_POWER_COEFF_0 + 15):
//          m_data.fp = __swap_bytes_to_float(flashPtr->txPower_coeff_0[3]);
//          if (curr_channel_no == 4)
//          {
//            txPower_coeff_0 = m_data.fp;
//          }
//          break;
//
//        case (FLASH_TX_POWER_COEFF_1 + 15):
//          m_data.fp = __swap_bytes_to_float(flashPtr->txPower_coeff_1[3]);
//          if (curr_channel_no == 4)
//          {
//            txPower_coeff_1 = m_data.fp;
//          }
//          break;
//
#endif
	case (FLASH_RX_POWER_COEFF_0 + 3):
		m_data.fp = __swap_bytes_to_float(flashPtr->rxPower_coeff_0);
		rxPower_coeff_0 = m_data.fp;
		break;

	case (FLASH_RX_POWER_COEFF_1 + 3):
		m_data.fp = __swap_bytes_to_float(flashPtr->rxPower_coeff_1);
		rxPower_coeff_1 = m_data.fp;
		break;

	case (FLASH_RX_POWER_COEFF_2 + 3):
		m_data.fp = __swap_bytes_to_float(flashPtr->rxPower_coeff_2);
		rxPower_coeff_2 = m_data.fp;
		break;

	case (FLASH_RX_POWER_COEFF_3 + 3):
		m_data.fp = __swap_bytes_to_float(flashPtr->rxPower_coeff_3);
		rxPower_coeff_3 = m_data.fp;
		break;

	case (FLASH_RX_POWER_COEFF_4 + 3):
		m_data.fp = __swap_bytes_to_float(flashPtr->rxPower_coeff_4);
		rxPower_coeff_4 = m_data.fp;
		break;

	case A2_PAGE_81H_MANCHESTER_MODE_ADDR:
		// Manchester Mode Control
		Manchester_Control_I2C(mem_value);
		break;
	}

#endif
}

void exec_non_standard_A0_memory(uint8_t dev_addr, uint8_t page, uint8_t mem_addr, uint8_t mem_value)
{
}

void tx_input_equalization(uint8_t chNo, uint8_t set_value)
{
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
	// GN_1157

#else

	uint8_t xdata c_value1, c_dev_addr, c_addr;

	// TX INPUT EQUALIZATION: TX CDR CONTROL
	c_dev_addr = TX_RX_COMBO_CDR_I2C_ADDR;
	c_addr = P00_TX_ADAPT_EQ;

	switch (set_value)
	{
	case 0:
		c_value1 = 0x00;
		break;
	case 1:
		c_value1 = 0x02;
		break;
	case 2:
		c_value1 = 0x04;
		break;
	case 3:
		c_value1 = 0x06;
		break;
	case 4:
		c_value1 = 0x0A;
		break;
	case 5:
		c_value1 = 0x0C;
		break;
	case 6:
		c_value1 = 0x0E;
		break;
	case 7:
		c_value1 = 0x10;
		break;

	case 8:
		c_value1 = 0x12;
		break;

	case 9:
		c_value1 = 0x14;
		break;

	case 10:
		c_value1 = 0x16;
		break;

	case 11:
		c_value1 = 0x1A;
		break;

	case 12:
		c_value1 = 0x1E;
		break;

	default:
		c_value1 = 0x06; // 10 dB channel loss: adaptive mode
		break;
	}
	write_master_gpio_single_byte(c_dev_addr, c_addr, c_value1);
#endif
}

void rx_output_deemphasis(uint8_t chNo, uint8_t set_value)
{
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
	// GN_1157

#else
	uint8_t xdata c_value1, c_value2, c_dev_addr, c_addr;

	// RX_OUTPUT_DEEMPH: RX CDR CONTROL
	c_dev_addr = TX_RX_COMBO_CDR_I2C_ADDR;
	c_addr = P00_RX_OP_DEEMPH;
	c_value2 = read_master_gpio_single_byte(c_dev_addr, c_addr);
	c_value2 = c_value2 & 0x0F;

	switch (set_value)
	{
	case 0:
		c_value1 = 0x00;
		break;
	case 1:
		c_value1 = 0x30;
		break;
	case 2:
		c_value1 = 0x60;
		break;
	case 3:
		c_value1 = 0x80;
		break;
	case 4:
		c_value1 = 0xA0;
		break;
	case 5:
		c_value1 = 0xC0;
		break;
	case 6:
		c_value1 = 0xE0;
		break;
	case 7:
		c_value1 = 0xF0;
		break;

	default:
		c_value1 = 0x00; // 10 dB channel loss: adaptive mode
		break;
	}
	c_value1 = c_value1 | c_value2;

	write_master_gpio_single_byte(c_dev_addr, c_addr, c_value1);
#endif
}

void rx_output_amplitude(uint8_t chNo, uint8_t set_value)
{
	//	uint8_t xdata c_value1, c_value2, c_dev_addr, c_addr;
	//
	//	// RX_OUTPUT_DEEMPH: RX CDR CONTROL
	//	c_dev_addr = RX_CDR_I2C_ADDR;
	//	c_addr = RX_CDR_OUTPUT_SWING_CH_N(chNo);
	//	c_value2 = read_master_gpio_single_byte(c_dev_addr, c_addr);
	//	c_value2 = c_value2 & 0xC0;
	//
	//	switch (set_value) {
	//		case 0:
	//			c_value1 = 0x00; // 100 Ohm load 300(mVppd)
	//			break;
	//		case 1:
	//			c_value1 = 0x0F; // 100 Ohm load 450(mVppd)
	//			break;
	//		case 2:
	//			c_value1 = 0x1e; // 100 Ohm load 600(mVppd)
	//			break;
	//		case 3:
	//			c_value1 = 0x3C; // 100 Ohm load 900(mVppd)
	//			break;
	//
	//		default:
	//			c_value1 = 0x3F;  // 100 Ohm load 930(mVppd)
	//			break;
	//	}
	//	c_value1 = c_value1 | c_value2;
	//
	//	write_master_gpio_single_byte(c_dev_addr,  c_addr, c_value1);
}

void update_msa_control_regs_from_tx_cdr(void)
{
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
	// GN_1157

#else

	// tx_equalization magnitude
	//    	uint8_t chNo, c_value1, c_value2, c_addr, c_flag, c_val[4], tx_adpative_eq_control;
	uint8_t c_value2, c_addr, c_val[4];

	// [DCLEE] 2020.05.28. TX&RX CDR Control -->
	//        uint8_t c_flag2, c_value3;

	//        c_addr = P00_TX_MODES;
	//        c_value3 = I2C_Slave_Buffer_A2_P82H_Up[c_addr];
	//
	//        if ((c_value3 & 0x20) == 0x20)
	//        {
	////          c_value1 = c_val[1];
	//        }
	//        else
	//        {
	////          c_value1 = c_val[0];
	//        }

	c_addr = P00_TX_ADAPT_EQ;
	c_value2 = I2C_Slave_Buffer_A2_P82H_Up[c_addr];
	c_value2 &= 0xC3;

	switch (c_value2)
	{
	case 0x00: // 0 dB
		c_val[0] = 0x00;
		break;
	case 0x04: // 1 dB
		c_val[0] = 0x11;
		break;
	case 0x08: // 2 dB
		c_val[0] = 0x22;
		break;
	case 0x0C: // 3 dB
		c_val[0] = 0x33;
		break;
	case 0x10: // Adaptive mode
		//                            c_val[chNo] = 0x0B;
		//          c_flag = (0x01 << chNo);
		//          tx_adpative_eq_control |= c_flag;
		//
		c_val[0] = 0xFF;

		break;
	case 0x14: // 4 dB
		c_val[0] = 0x44;
		break;

	case 0x18: // 5 dB
		c_val[0] = 0x55;
		break;

	case 0x1C: // 6 dB
		c_val[0] = 0x66;
		break;

	case 0x20: // 7 dB
		c_val[0] = 0x77;
		break;

	case 0x24: // 8 dB
		c_val[0] = 0x88;
		break;

	case 0x28: // 9 dB
		c_val[0] = 0x99;
		break;

	case 0x2C: // 10 dB
		c_val[0] = 0xAA;
		break;

	case 0x30: // 10.5 dB
		c_val[0] = 0xBB;
		break;

	case 0x34: // 11 dB
		c_val[0] = 0xCC;
		break;

	case 0x38: // 11.5 dB
		c_val[0] = 0xDD;
		break;

	case 0x3C: // 12 dB
		c_val[0] = 0xEE;
		break;

	default: // 2 dB
		c_val[0] = 0x22;
		break;
	}

	I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_TXEQ_72] = c_val[0];
#endif
}

void update_msa_control_regs_from_rx_cdr(void)
{
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
	// GN_1157

#else
	// output_deemphasis
	//    	uint8_t chNo, c_value1, c_value2, c_dev_addr, c_addr, c_flag, c_val[4], tx_adpative_eq_control;
	uint8_t c_value2, c_addr, c_val[4];

	// [DCLEE] 2020.05.28. TX&RX CDR Control -->
	//        uint8_t c_flag2, c_value3;

	c_addr = P00_RX_OP_DEEMPH;
	c_value2 = I2C_Slave_Buffer_A2_P82H_Up[c_addr];

	switch (c_value2)
	{		   // Deemph Value
	case 0x00: // 0 dB
		c_val[0] = 0x00;
		break;
	case 0x10: // 0.4 dB
		c_val[0] = 0x11;
		break;
	case 0x20: // 0.7 dB
		c_val[0] = 0x11;
		break;
	case 0x30: // 1.0 dB
		c_val[0] = 0x11;
		break;
	case 0x40: // 1.2 dB
		c_val[0] = 0x22;
		break;
	case 0x50: // 1.5 dB
		c_val[0] = 0x22;
		break;
	case 0x60: // 2 dB
		c_val[0] = 0x22;
		break;
	case 0x70: // 2.5 dB
		c_val[0] = 0x33;
		break;
	case 0x80: // 3 dB
		c_val[0] = 0x33;
		break;
	case 0x90: // 3.5 dB
		c_val[0] = 0x44;
		break;
	case 0xa0: // 4 dB
		c_val[0] = 0x44;
		break;
	case 0xb0: // 4.5 dB
		c_val[0] = 0x55;
		break;
	case 0xc0: // 5 dB
		c_val[0] = 0x55;
		break;
	case 0xd0: // 5.5 dB
		c_val[0] = 0x66;
		break;

	case 0xe0: // 6 dB
		c_val[0] = 0x66;
		break;

	case 0xf0: // 6.5 dB
		c_val[0] = 0x77;
		break;

	default:
		c_val[0] = 0x00;
		break;
	}

	I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_RXPREEMP_73] = c_val[0];

#endif
}
// [DCLEE] 2020.04.16. <-- SQ DISABLE, TX_in_EQ, etc.

#else

#endif

#if __SFP28_ER__ == 1
/*****************************************************************************
 *
 *  Name:              ProcessReceivedI2CData
 *
 *  Description:       This function checks
 *                     the status of the write buffer. If a write transaction
 *                     from the host has placed data in the buffer then this
 *                     function processes the data and forwards it to RAM, FLASH
 *                     or the MAX395X
 *****************************************************************************/
void ProcessReceivedI2CData(void)
{
	unsigned char ucTemp;
	unsigned char *pSram_addr_ptr;
	unsigned int unNum_bytes;
	unsigned int unAddr;
	unsigned int unFlash_write;
	unsigned int unCheck_pw;
	unsigned int unDCDCSel = DCDC_SEL; // store DCDC_SEL, this register might be changed in following code
	unsigned char dev_address, page_sel;

	dev_address = twsiSlaveBuf.devAddress;

	if (twsiSlaveBuf.bufferStatus == MEMORY_WRITE_BUFFER_WAITING_TO_PROCESS) // there is data to process
	{
		if (twsiSlaveBuf.devAddress == 0xA0) // Slave address A4,
		{
			page_sel = 0x00; //[DCLEE] 2019.10.07. <--

			unAddr = twsiSlaveBuf.address;
			unNum_bytes = twsiSlaveBuf.numOfEntries;
			pSram_addr_ptr = (unsigned char *)A0_SRAM_OFFSET; // set ram address
			pSram_addr_ptr += unAddr;

			for (ucTemp = 0; ucTemp < unNum_bytes; ucTemp++) // copy incoming data to ram
			{
				*pSram_addr_ptr = I2C_Rx_Buffer[ucTemp];
				*pSram_addr_ptr++;

				I2C_Slave_Memory_Map_Write(dev_address, page_sel, unAddr, I2C_Rx_Buffer[ucTemp]); // [DCLEE] 2019.10.07. <--

				unAddr++;
				if (unAddr >= 256)
				{
					unAddr = 0;
					pSram_addr_ptr = (unsigned char *)A0_SRAM_OFFSET;
				}
			}
			//        CopySramToFlash(A4_SRAM_OFFSET, FLASH_A4_START, 256);                   //copy whole block of memory to flash
		}
		else if (twsiSlaveBuf.address < 0x80) // A2 Lower Memory
		{
			unFlash_write = 0;
			unCheck_pw = 0;
			unAddr = twsiSlaveBuf.address;
			unNum_bytes = twsiSlaveBuf.numOfEntries;
			pSram_addr_ptr = (unsigned char *)A2_LOWER_SRAM_OFFSET; // set ram address
			pSram_addr_ptr += unAddr;

			page_sel = 0x00; //[DCLEE] 2019.10.07. <--

			for (ucTemp = 0; ucTemp < unNum_bytes; ucTemp++)
			{
				// all config below ddm values
				//          if(unAddr < 0x60)
				//          {
				//            *pSram_addr_ptr = I2C_Rx_Buffer[ucTemp];
				//            unFlash_write = 1;
				//          }
				//
				//          else if(unAddr == 0x6E)                                               //Soft operation(Soft TXD)
				//          {
				//              if(I2C_Rx_Buffer[ucTemp] & 0x40)                                  //soft TXD assert
				//              {
				//                *pSram_addr_ptr |= 0x40;
				//                PLA_Soft_TXD_Control(ASSERTED);
				//
				// #ifndef DCDC_BIASING
				//                //LB is generated by IDAC
				//                IDCD1 = 0;                                                      //Write 0 to IDAC
				// #endif
				//
				//                Clear_TXF_Status();                                             //clear TXF flags
				//              }
				//              else                                                              //soft TXD de-assert
				//              {
				//                *pSram_addr_ptr &= ~0x40;
				//
				//                if(PLACNT1_bit.SB1 == 1)                                        //if previous soft TXD is asserted,
				//                {
				//                  PLA_Soft_TXD_Control(DE_ASSERTED);                            //set soft TXD to de-assert
				//                  MonitorTXD();                                                 //check TXD status, if no TXD is asserted, re-start APC loop
				//
				//                }
				//              }
				//
				//          }
				//          //table select
				//          else
				if (unAddr == 0x7F)
				{
#if __INTEROPERABILITY_TEST_POLL_PAGESEL__ == 1
					if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] != I2C_Rx_Buffer[ucTemp]) // if changing the table
					{
						page_sel = I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] = I2C_Rx_Buffer[ucTemp]; // set new table in sram
						I2C_Slave_Memory_Map_Write(dev_address, page_sel, unAddr, I2C_Rx_Buffer[ucTemp]);	 // [DCLEE] 2019.10.07. <--
					}
#else

					if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] != I2C_Rx_Buffer[ucTemp]) // if changing the table
					{
						I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] = I2C_Rx_Buffer[ucTemp]; // set new table in sram
						if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_00H)
						{
							// copy from Page00h area to upper memory
							memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE00H_UPPER, 128);
						}
						else if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_01H)
						{
							// copy from Page02h area to upper memory
							memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE01H_UPPER, 128);
						}
						else if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_02H)
						{
							// copy from Page03h area to upper memory
							memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE02H_UPPER, 128);
						}
						else if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_80H)
						{
							// copy from Page04h area to upper memory
							memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE80H_UPPER, 128);
						}
						else if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_81H)
						{
							// copy from Page05h area to upper memory
							memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE81H_UPPER, 128);
						}
						else if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_82H)
						{
							// copy from Page05h area to upper memory
							memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE82H_UPPER, 128);
						}
						else if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_83H)
						{
							// copy from Page05h area to upper memory
							memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE83H_UPPER, 128);
						}
						else if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_84H)
						{
							// copy from Page05h area to upper memory
							memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE84H_UPPER, 128);
						}
						else
						{
							//                     CopyLutToSram(I2C_Slave_Buffer_A0[127]);                                 //copy this LUT from flash to A2 upper memory
						}
					}
					else
					{
#if __INTEROPERABILITY_TEST__ == 1

#else

						if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_00H)
						{
							// copy from Page00h area to upper memory
							memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE00H_UPPER, 128);
						}
						else if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_02H)
						{
							// copy from Page03h area to upper memory
							memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE02H_UPPER, 128);
						}
						else if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_80H)
						{
							// copy from Page04h area to upper memory
							memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE80H_UPPER, 128);
						}
						else if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_81H)
						{
							// copy from Page05h area to upper memory
							memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE81H_UPPER, 128);
						}
						else if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_82H)
						{
							// copy from Page05h area to upper memory
							memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE82H_UPPER, 128);
						}
						else if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_83H)
						{
							// copy from Page05h area to upper memory
							memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE83H_UPPER, 128);
						}
						else if (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL] == PAGE_84H)
						{
							// copy from Page05h area to upper memory
							memcpy((unsigned char *)A2_UPPER_SRAM_OFFSET, (unsigned char *)PAGE84H_UPPER, 128);
						}
#endif
					}
#endif
				}
				else
				{
					page_sel = I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL];
					//              exec_write_entry(dev_address, page_sel, unAddr, I2C_Rx_Buffer[ucTemp]);        // [DCLEE] 2019.10.07. <--
					I2C_Slave_Memory_Map_Write(dev_address, page_sel, unAddr, I2C_Rx_Buffer[ucTemp]); // [DCLEE] 2019.10.07. <--
																									  // I2C_Slave_Memory_Map_Write
				}
				//          //tx and rx emphasis
				//          else if( (unAddr == 0x72) || (unAddr == 0x73) )
				//          {
				//              *pSram_addr_ptr = I2C_Rx_Buffer[ucTemp];
				//              unFlash_write = 1;
				//          }
				//          //control
				//          else if ((unAddr >= 0x7B) && (unAddr <= 0x7E) )
				//          {
				//            s_ucPassword_entry[unAddr - 0x7B] = I2C_Rx_Buffer[ucTemp];
				//            unCheck_pw = 1;
				//          }

				*pSram_addr_ptr++;
				unAddr++;
				if (unAddr >= 128)
				{
					unAddr = 0;
					pSram_addr_ptr = (unsigned char *)A2_LOWER_SRAM_OFFSET;
				}
			}

			if (unCheck_pw)
			{
				// CheckPasswordLevel();
				// PasswordLevel = ACCESS_LEVEL_RW;
				s_ucPassword_entry[0] = s_ucPassword_entry[0];
			}
			if (unFlash_write)
			{
				//           CopySramToFlash(A0_LOWER_SRAM_OFFSET, FLASH_A0_START, 128);          //copy whole block of memory to flash
			}
		}
		else // A0 Upper Memory (Tables)
		{
			unAddr = twsiSlaveBuf.address;
			unNum_bytes = twsiSlaveBuf.numOfEntries;
			pSram_addr_ptr = (unsigned char *)A2_UPPER_SRAM_OFFSET; // set ram address
			pSram_addr_ptr += (unAddr - 128);
			page_sel = I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL];
			for (ucTemp = 0; ucTemp < unNum_bytes; ucTemp++)
			{
				*pSram_addr_ptr = I2C_Rx_Buffer[ucTemp];
				*pSram_addr_ptr++;

				//           exec_write_entry(dev_address, page_sel, unAddr, I2C_Rx_Buffer[ucTemp]);        // [DCLEE] 2019.10.07. <--
				I2C_Slave_Memory_Map_Write(dev_address, page_sel, unAddr, I2C_Rx_Buffer[ucTemp]); // [DCLEE] 2019.10.07. <--
																								  // I2C_Slave_Memory_Map_Write

				unAddr++;
				if (unAddr >= 256)
				{
					unAddr = 128;
					pSram_addr_ptr = (unsigned char *)A2_UPPER_SRAM_OFFSET;
				}
			}

			unFlash_write = 1;										  // assume a write, change below if required
			switch (I2C_Slave_Buffer_A2[SFP28_LOWER_MEMORY_PAGE_SEL]) // look for special processing in each table
			{
			case 0:
				unFlash_write = 0;
				break;
			case 1:
				unFlash_write = 0;
				break;

			case 0x02:
				unFlash_write = 0;
				break;

			case 0x80:
				unFlash_write = 0;
				break;

			case 0x81:
				unFlash_write = 0;
				break;

			case 0x82:
				unFlash_write = 0;
				break;

			case 0x83:
				unFlash_write = 0;
				break;

			case 0x84:
				unFlash_write = 0;
				break;

				//            case 0x06:
				//              unFlash_write = 0;
				//              break;

				//            case 0x80:
				//              ProcessTable80h(twsiSlaveBuf.address, twsiSlaveBuf.numOfEntries); //process table 80h data
				//              unFlash_write = 1;
				//              break;
				//
				//            case 0x88:
				//            case 0x89:
				//            case 0x8A:
				//            case 0x8B:
				//
				//              unFlash_write = 1;
				//              break;
				//
				//            case 0x90:
				//              ProcessTable90h(twsiSlaveBuf.address, twsiSlaveBuf.numOfEntries); //process table 90h data
				//              unFlash_write = 1;
				//              break;
				//
				//            case 0x91:
				//              ProcessTable91h(twsiSlaveBuf.address, twsiSlaveBuf.numOfEntries); //process table 91h data
				//              unFlash_write = 1;
				//              break;

			default:
				unFlash_write = 0; // do not write to flash or sram
				break;
			}

			if (unFlash_write)
			{
				//           CopyLutToFlash(I2C_Slave_Buffer_A0[QSFP_LOWER_MEMORY_PAGE_SEL]);                                        //copy whole block of memory to flash
			}
		}
		twsiSlaveBuf.numOfEntries = 0;						  // clear
		twsiSlaveBuf.bufferStatus = MEMORY_WRITE_BUFFER_IDLE; // set as idle
		I2CCN_S_bit.I2CACK = 0;								  // re-enable acks
	}

	DCDC_SEL = unDCDCSel; // restore DCDC_SEL
}

#else

#endif

unsigned int GetLutAddress(unsigned char ucTable_num)
{
	return 0;
}

//-----------------------------------------------------------------------------
// CopyLutToSram function
//  copies given table from flash to A2 upper memory
//-----------------------------------------------------------------------------
void CopyLutToSram(unsigned char ucTable_num)
{
}

//-----------------------------------------------------------------------------
// GetIntFromFlash function
//  reads back one word from provided flash table for address provided
//-----------------------------------------------------------------------------
unsigned int GetIntFromFlash(unsigned char ucTable_num, unsigned int unAddr)
{

	return 0;
}

//-----------------------------------------------------------------------------
//  GetLUTByteFromFlash function
//  reads back one byte from LUT for index provided
//-----------------------------------------------------------------------------
unsigned char GetLUTByteFromFlash(unsigned char ucTable_num, unsigned int unIndex)
{

	return 0;
}

unsigned int GetA0hTableWordAddrOffset(unsigned char ucTable, unsigned int *pAddress)
{

	return 0;
}
//------------------------------------------------------------------------------
// Update Read Only data to Table 5 if it is selected
//------------------------------------------------------------------------------
void UpdateWordA0hTable(unsigned char ucTable, unsigned int *pAddress, unsigned int unData)
{
}

unsigned int GetA0hTableByteAddrOffset(unsigned char ucTable, unsigned char *pAddress)
{

	return 0;
}

//------------------------------------------------------------------------------
// Update Read Only data to Table 5 if it is selected
//------------------------------------------------------------------------------
void UpdateByteA0hTable(unsigned char ucTable, unsigned char *pAddress, unsigned char ucData)
{
}

//-----------------------------------------------------------------------------
// End of file
//-----------------------------------------------------------------------------

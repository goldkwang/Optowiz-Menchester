#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "flash.h"
#include "i2cslave.h"
#include "memory_access.h"

#define __DECLARE_VARS__
#include <intrinsics.h>
#include "iods4835.h"

#include "includes.h"

#define __ROSA_WOORIRO_VER__ 1

// Flash Functions
//
// Page_no == 9 --> I2C_Slave_Buffer_A0_Local_Memory (A0 device address)
// Page_no == 0 --> I2C_Slave_Buffer_A2 (Control and Threshold)
// Page_no == 1 --> I2C_Slave_Buffer_A2_P00H_Up and I2C_Slave_Buffer_A2_P01H_Up
//              --> FLASH_USER_EERPOM_START
// Page_no == 2 --> I2C_Slave_Buffer_A2_P02H_Up
// Page_no == 0x80, page_passwork_enable[10] --> I2C_Slave_Buffer_A2_P80H_Up
// Page_no == 0x81, page_passwork_enable[11] --> I2C_Slave_Buffer_A2_P81H_Up
// Page_no == 0x82, page_passwork_enable[12] --> I2C_Slave_Buffer_A2_P82H_Up

void restore_from_flash_memory(uint8_t page_no)
{
        //	int  i;
        uint8_t *xdata flash_memory;
        uint8_t *xdata ram_memory;
        uint8_t t_page_no;

        if (page_no == 9)
        {
                if (page_password_enable[page_no] == 1)
                {
                        ram_memory = (uint8_t *)&I2C_Slave_Buffer_A0_Local_Memory[0];
                        flash_memory = (uint8_t *)((FLASH_A0_START));
                        FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 256);
                }
        }

        if (page_no == 0)
        {
                if (page_password_enable[page_no] == 1)
                {
                        ram_memory = (uint8_t *)&I2C_Slave_Buffer_A2[0];
                        flash_memory = (uint8_t *)((FLASH_A2_START));
                        FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 128);
                }
        }

        if (page_no == 1)
        {
                if (page_password_enable[page_no] == 1)
                {
                        ram_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P00H_Up[0];
                        flash_memory = (uint8_t *)((FLASH_USER_EERPOM_START));
                        FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 128);

                        ram_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P01H_Up[0];
                        flash_memory = (uint8_t *)((FLASH_USER_EERPOM_START + 128));
                        FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 128);
                }
        }

        if (page_no == 2)
        {
                if (page_password_enable[page_no] == 1)
                {
                        ram_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P02H_Up[0];
                        flash_memory = (uint8_t *)((FLASH_PAGE02H_START));
                        FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 128);
                }
        }

        if (page_no == 0x80)
        {
                t_page_no = 10;
                if (page_password_enable[t_page_no] == 1)
                {
                        ram_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P80H_Up[0];
                        flash_memory = (uint8_t *)((FLASH_PAGE80H_START));
                        FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 128);
                }
        }

        if (page_no == 0x81)
        {
                t_page_no = 11;
                if (page_password_enable[t_page_no] == 1)
                {
                        ram_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P81H_Up[0];
                        flash_memory = (uint8_t *)((FLASH_PAGE81H_START));
                        FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 128);
                }
        }

        if (page_no == 0x82)
        {
                t_page_no = 12;
                if (page_password_enable[t_page_no] == 1)
                {
                        ram_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P82H_Up[0];
                        flash_memory = (uint8_t *)((FLASH_PAGE82H_START));
                        FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 128);
                }
        }

        return;
}

// void CopySramToFlash(unsigned int sram_add, unsigned int flash_add, unsigned int length)

void FLASH_Update(unsigned int dest, unsigned int src, unsigned int numbytes)
{
        CopySramToFlash(src, dest, numbytes);
}

// void ReadFromFlash(unsigned int SourceAddress, unsigned int DesAddress, unsigned int length)
// void FlashReadBlock(unsigned int flash_add, unsigned int sram_add, unsigned int length)

void FLASH_Read(unsigned int dest, unsigned int src, unsigned int numbytes)
{
        FlashReadBlock(src, dest, numbytes);
}

// #define FLASH_A0_CONST_START            0xEE00                                  //Flash location for A0 memory:
// #define FLASH_A2_LOWER_CONST_START      0xEF00                                  //Flash location for A2 LOWER Cibf:
// #define FLASH_USER_EERPOM_START         0xF000                                  //Flash location for User EEPROM, A2 Device Page00, Page01 Upper Memory
// #define FLASH_A0_START                  0xF200                                  //Flash location for A0 Device memory: 256 bytes
// #define FLASH_A2_START                  0xF400                                  //Flash location for A2 Device memory lower memory: 128 bytes
// #define FLASH_PAGE02H_START             0xF600                                  //Flash location for Page 02h
// #define FLASH_PAGE80H_START             0xF800                                  //Flash location for Page 80h
// #define FLASH_PAGE81H_START             0xFA00                                  //Flash location for Page 81h
// #define FLASH_PAGE82H_START             0xFC00                                  //Flash location for Page 82h

//
// Page_no == 9 --> I2C_Slave_Buffer_A0_Local_Memory (A0 device address)
// Page_no == 0 --> I2C_Slave_Buffer_A2 (Control and Threshold)
// Page_no == 1 --> I2C_Slave_Buffer_A2_P00H_Up and I2C_Slave_Buffer_A2_P01H_Up
//              --> FLASH_USER_EERPOM_START
// Page_no == 2 --> I2C_Slave_Buffer_A2_P02H_Up
// Page_no == 0x80, page_passwork_enable[10] --> I2C_Slave_Buffer_A2_P80H_Up, Module Configuration value 1
// Page_no == 0x81, page_passwork_enable[11] --> I2C_Slave_Buffer_A2_P81H_Up, Module Configuration value 2
// Page_no == 0x82, page_passwork_enable[12] --> I2C_Slave_Buffer_A2_P82H_Up, CDR Configuration values

// [DCLEE] Till Now, 2019.12.27 -->
#if __HFR_REQ_VER__ == 1
void save_to_flash_memory_ch_no(void)
{
#if __HSFP_10G_MULTI_RATE_SEMI_TUNABLE__ == 1

        uint8_t *dump_memory;
        uint8_t *default_memory;
        // uint16_t curr_ch_no_flash;
        uint8_t flash_curr_specific_info[4];

        // curr_ch_no_flash = __swap_bytes(curr_channel_no);
        *(uint16_t *)&flash_curr_specific_info[0] = __swap_bytes(curr_channel_no);

        flash_curr_specific_info[2] = I2C_Slave_Buffer_A2[A2_STATUS_CONTROL_OFF];
        flash_curr_specific_info[3] = I2C_Slave_Buffer_A2[A2_EXTENDED_CONTROL_STATUS_OFF];

        dump_memory = (uint8_t *)&flash_curr_specific_info[0];
        default_memory = (uint8_t *)FLASH_CH_NO_VENDOR_SPECIFIC;
        FLASH_Update((unsigned int)default_memory, (unsigned int)dump_memory, 4);

        *(unsigned int *)&I2C_Slave_Buffer_A2_P01H_Up[0x78] = __swap_bytes(curr_channel_no);
        I2C_Slave_Buffer_A2_P01H_Up[0x7A] = I2C_Slave_Buffer_A2[A2_STATUS_CONTROL_OFF];
        I2C_Slave_Buffer_A2_P01H_Up[0x7B] = I2C_Slave_Buffer_A2[A2_EXTENDED_CONTROL_STATUS_OFF];

        return;

#else
        uint8_t *dump_memory;
        uint8_t *default_memory;
        uint16_t curr_ch_no_flash;

        curr_ch_no_flash = __swap_bytes(curr_channel_no);

        dump_memory = (uint8_t *)&curr_ch_no_flash;
        default_memory = (uint8_t *)FLASH_CH_NO_VENDOR_SPECIFIC;
        FLASH_Update((unsigned int)default_memory, (unsigned int)dump_memory, 2);

        *(unsigned int *)&I2C_Slave_Buffer_A2_P01H_Up[0x78] = __swap_bytes(curr_channel_no);

        return;
#endif
}
#endif

void save_to_flash_memory(uint8_t page_no)
{
        uint8_t *dump_memory;
        uint8_t *default_memory;
        uint8_t t_page_no;

        if (page_no == 0)
        {
                if (page_password_enable[page_no] == 1)
                {
                        dump_memory = (uint8_t *)&I2C_Slave_Buffer_A2[0];
                        default_memory = (uint8_t *)FLASH_A2_START;
                        FLASH_Update((unsigned int)default_memory, (unsigned int)dump_memory, 128);

                        //                        CopyLutToFlash(0);
                }
        }

        if (page_no == 1)
        {
                if (page_password_enable[page_no] == 1)
                {
                        dump_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P00H_Up[0];
                        default_memory = (uint8_t *)(FLASH_USER_EERPOM_START);
                        FLASH_Update((unsigned int)default_memory, (unsigned int)dump_memory, 256);

                        //                        dump_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P00H_Up[0];
                        //			default_memory = (uint8_t *)(FLASH_USER_EERPOM_START);
                        //			FLASH_Update((unsigned int)default_memory, (unsigned int)dump_memory, 128);
                        //
                        //			dump_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P01H_Up[0];
                        //			default_memory = (uint8_t *)(FLASH_USER_EERPOM_START+128);
                        //			FLASH_Update((unsigned int)default_memory, (unsigned int)dump_memory, 128);
                }
        }

        if (page_no == 2)
        {
                // [DCLEE] Always Channel No Save
                //		if (page_password_enable[page_no] == 1)
                {
                        dump_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P02H_Up[0];
                        default_memory = (uint8_t *)(FLASH_PAGE02H_START);
                        FLASH_Update((unsigned int)default_memory, (unsigned int)dump_memory, 128);
                }
        }

        if (page_no == 0x80)
        {
                t_page_no = 10;

                if (page_password_enable[t_page_no] == 1)
                {
                        store_data_to_flash();
                        //			dump_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P80H_Up[0];
                        //			default_memory = (uint8_t *)(FLASH_PAGE80H_START);
                        //			FLASH_Update((unsigned int)default_memory, (unsigned int)dump_memory, 128);
                }
        }

        if (page_no == 0x81)
        {
                t_page_no = 11;
                if (page_password_enable[t_page_no] == 1)
                {
                        dump_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P81H_Up[0];
                        default_memory = (uint8_t *)(FLASH_PAGE81H_START);
                        FLASH_Update((unsigned int)default_memory, (unsigned int)dump_memory, 128);
                }
        }

        if (page_no == 0x82)
        {
                t_page_no = 12;
                if (page_password_enable[t_page_no] == 1)
                {
                        dump_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P82H_Up[0];
                        default_memory = (uint8_t *)(FLASH_PAGE82H_START);
                        FLASH_Update((unsigned int)default_memory, (unsigned int)dump_memory, 128);
                }
        }

        if (page_no == 9)
        { // dev_I2C_address

                if (page_password_enable[page_no] == 1)
                {
                        //			store_data_to_flash();
                        dump_memory = (uint8_t *)&I2C_Slave_Buffer_A0_Local_Memory[0];
                        default_memory = (uint8_t *)(FLASH_A0_START);
                        FLASH_Update((unsigned int)default_memory, (unsigned int)dump_memory, 256);
                }
        }

        if (page_no == 0x0F)
        {
                factory_reset_eeprom_info();
        }

        return;
}

// Polled CDR Regs
// TX&RX CDR Initialization

// void polled_tx_cdr_reg_info(void)
//{
//	uint8_t  reg_addr;
////
////	reg_addr = TX_CDR_CHIPID;
////	rVal = read_master_gpio_single_byte(TX_CDR_I2C_ADDR, TX_CDR_CHIPID);
////	I2C_Slave_Buffer_A0_P5_Up[reg_addr] = rVal;
////
////	reg_addr = TX_CDR_REVID;
////	rVal = read_master_gpio_single_byte(TX_CDR_I2C_ADDR, TX_CDR_REVID);
////	I2C_Slave_Buffer_A0_P5_Up[reg_addr] = rVal;
//
//	for (reg_addr = 0; reg_addr < 128; reg_addr += 2)
//	{
//		read_master_gpio_multiple_bytes(TX_CDR_I2C_ADDR, reg_addr, 2, &I2C_Slave_Buffer_A0_P5_Up[reg_addr]);
////		rVal = 1;
////		rVal = 2;
////		rVal = 3;
////		rVal = 4;
//	}
//
//}

void polled_tx_rx_cdr_reg_info(void)
{
        uint8_t xdata reg_addr;

        for (reg_addr = 0; reg_addr < 128; reg_addr += 4)
        {
                WDCN_bit.RWT = 1; // reset watchdog timer
                read_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, reg_addr, 4, &I2C_Slave_Buffer_A2_P82H_Up[reg_addr]);
        }
}

/* �ʱ�ȭ �� flash memory�� �����Ǿ� �ִ� �����ڷ���� �����ͼ� �ʱ�ȭ �� */
void load_init_data_from_flash(void)
{ /*{{{*/
        // [DCLEE: 191114] Alarm ���� -->
        //	int idx_f, idx_s;
        unsigned int initFlag, curr_chNo;
        IEEE_754_FP_Type m_data;
        A2_PAGE_80H_MEMORY_MAP *flashPtr;
        A2_PAGE_81H_MEMORY_MAP *flashPtr_1;
        PAGE_02H_MEMORY_MAP *upperMemoryPtr_02h;

        flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
        flashPtr_1 = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P81H_Up[0];
        upperMemoryPtr_02h = (PAGE_02H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P02H_Up[0];

        initFlag = __swap_bytes(flashPtr->flash_reset_flag);
        if (initFlag == 0x0C00)
        {
                wavelength_info_set();

                curr_channel_no = __swap_bytes(upperMemoryPtr_02h->Channel_Number_Set);

                //          if ((curr_channel_no >= 1) && (curr_channel_no <= 4))
                if ((curr_channel_no >= 1) && (curr_channel_no <= 8))
                {
                        //            curr_chNo = curr_channel_no - 1;
                        curr_chNo = (curr_channel_no - 1) % 4;
                }
                else
                {
                        curr_chNo = 0; // curr_channel_no = 1
                }

                //          for (idx_s=1; idx_s<2; idx_s++)
                {
                        //            for (idx_f=1; idx_f<5; idx_f++)
                        {
                                //              LdControlMode = __swap_bytes(flashPtr->LdControlMode);
                                //              LdControlMode = flashPtr->LdControlMode;
                                //
                                //              ModBiasSet = __swap_bytes(flashPtr->ModBiasSet);
                                //
                                //              XconBiasSet = __swap_bytes(flashPtr->XconBiasSet);
                                //
                                //              forcedLdBiasSet = __swap_bytes(flashPtr->forcedLdBiasSet);

                                LdControlMode = flashPtr->LdControlMode;

                                flashPtr->ModBiasSet = flashPtr->nt_ModBiasSet[curr_chNo];

                                flashPtr->XconBiasSet = flashPtr->nt_XconBiasSet[curr_chNo];

                                flashPtr->forcedLdBiasSet = flashPtr->nt_LdBiasSet[curr_chNo];

                                ModBiasSet = __swap_bytes(flashPtr->ModBiasSet);

                                XconBiasSet = __swap_bytes(flashPtr->XconBiasSet);

                                forcedLdBiasSet = __swap_bytes(flashPtr->forcedLdBiasSet);

                                //              flashPtr_1->TEC1_SETPOINT = flashPtr_1->tec_setpoint_per_wavelength[curr_channel_no-1];
                                //              flashPtr_1->TEC1_SETPOINT = flashPtr_1->nt_tec_setpoint_per_wavelength[curr_channel_no-1];
                                flashPtr_1->TEC1_SETPOINT = flashPtr_1->nt_tec_setpoint_per_wavelength[(curr_channel_no - 1) % 4];

                                cal_Temp_Slope_Offset();

#if __NEW_TX_POWER_MON_BY_TEMPERATURE__ == 1
                                calSlope_Offset(0);

#else
                                //              curr_channel_no = __swap_bytes(upperMemoryPtr_02h->Channel_Number_Set);
                                //
                                //              if ((curr_channel_no >= 1) && (curr_channel_no <= 4))
                                //              {
                                //                curr_chNo = curr_channel_no - 1;
                                //              }
                                //              else
                                //              {
                                //                curr_chNo = 0; // curr_channel_no = 1
                                //              }
                                //
                                m_data.fp = __swap_bytes_to_float(flashPtr_1->txPower_coeff_0);
                                //              m_data.fp = __swap_bytes_to_float(flashPtr_1->txPower_coeff_0[curr_chNo]);
                                if (m_data.u_data != 0xFFFFFFFF)
                                        txPower_coeff_0 = m_data.fp;
                                else
                                        txPower_coeff_0 = (float)0.0;

                                //              m_data.fp = __swap_bytes_to_float(flashPtr_1->txPower_coeff_1[curr_chNo]);
                                m_data.fp = __swap_bytes_to_float(flashPtr_1->txPower_coeff_1);
                                if (m_data.u_data != 0xFFFFFFFF)
                                        txPower_coeff_1 = m_data.fp;
                                else
                                        txPower_coeff_1 = (float)0.0;
#endif

                                m_data.fp = __swap_bytes_to_float(flashPtr_1->rxPower_coeff_0);
                                if (m_data.u_data != 0xFFFFFFFF)
                                        rxPower_coeff_0 = m_data.fp;
                                else
                                        rxPower_coeff_0 = (float)0;

                                m_data.fp = __swap_bytes_to_float(flashPtr_1->rxPower_coeff_1);
                                if (m_data.u_data != 0xFFFFFFFF)
                                        rxPower_coeff_1 = m_data.fp;
                                else
                                        rxPower_coeff_1 = (float)0;

                                m_data.fp = __swap_bytes_to_float(flashPtr_1->rxPower_coeff_2);
                                if (m_data.u_data != 0xFFFFFFFF)
                                        rxPower_coeff_2 = m_data.fp;
                                else
                                        rxPower_coeff_2 = (float)0;

                                m_data.fp = __swap_bytes_to_float(flashPtr_1->rxPower_coeff_3);
                                if (m_data.u_data != 0xFFFFFFFF)
                                        rxPower_coeff_3 = m_data.fp;
                                else
                                        rxPower_coeff_3 = (float)0;

                                m_data.fp = __swap_bytes_to_float(flashPtr_1->rxPower_coeff_4);
                                if (m_data.u_data != 0xFFFFFFFF)
                                        rxPower_coeff_4 = m_data.fp;
                                else
                                        rxPower_coeff_4 = (float)0;
                        }
                }
        }
        else
        {

                flashPtr->flash_reset_flag = __swap_bytes(0x0C00);
        }

        return;

} /*}}}*/

void load_vendor_user_nvr_from_flash(void)
{ /*{{{*/
        //	int idx_f;
        //	unsigned int wval, fpga_addr;
        //	XU8	 *w_ptr;
        //
        //	w_ptr = (U8 *)&wval;

} /*}}}*/

/* ���� �����Ǿ� �ִ� �ڷḦ flash memory�� ������ */
void store_data_to_flash(void)
{ /*{{{*/
        //	int idx_f, idx_s;
        uint8_t *default_memory;
        uint8_t *dump_memory;
        unsigned char sw_tx_dis;
        A2_PAGE_80H_MEMORY_MAP *flashPtr;

        flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
        dump_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P80H_Up[0];

        //        sw_tx_dis = FPGA_Read_byte(I2C_ADDR_A2, QSFP_LOWER_MEMORY_TX_DISABLE, A2_LOW_PAGE);
        sw_tx_dis = 0;
        if (sw_tx_dis == 0)
        {
                //          flashPtr->LdControlMode = __swap_bytes(LdControlMode);
                flashPtr->LdControlMode = LdControlMode;

                flashPtr->ModBiasSet = __swap_bytes(ModBiasSet);

                flashPtr->XconBiasSet = __swap_bytes(XconBiasSet);

                flashPtr->forcedLdBiasSet = __swap_bytes(forcedLdBiasSet);
        }

        default_memory = (uint8_t *)(FLASH_PAGE80H_START);
        FLASH_Update((unsigned int)default_memory, (unsigned int)dump_memory, 128);

        return;
} /*}}}*/

void factory_reset_eeprom_info(void)
{

        uint8_t *dump_memory;
        uint8_t *default_memory;
        A2_PAGE_80H_MEMORY_MAP *flashPtr1;
        A2_PAGE_81H_MEMORY_MAP *flashPtr;
        PAGE_02H_MEMORY_MAP *tunableControlMemPtr;

        // [DCLEE] 200616 --> Factory reset for TX (MAOM-37049), RX CDR (MAOM-37046)
        // CDR Info
        //        factory_reset_for_tx_rx_cdr();
        // [DCLEE] 200616 <-- Factory reset for TX (MAOM-37049), RX CDR (MAOM-37046)

        //	flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
        //	flashPtr1 = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P81H_Up[0];

        //	if (margc > 1) {
        //		printf("Invalid Command: *dump parameters \r\n");
        //		goto USAGE;
        //	}
        dump_memory = (uint8_t *)&I2C_Slave_Buffer_A0_Local_Memory[0];
        default_memory = (uint8_t *)FLASH_A0_CONST_START;
        //	default_memory = (uint8_t *)&FlashData_A0_Const[0];
        FLASH_Read((unsigned int)dump_memory, (unsigned int)default_memory, 128);

        // #if __WAVELENGTH_1270_VER__==1
        //         I2C_Slave_Buffer_A0_Local_Memory[60] = 0x04;
        //         I2C_Slave_Buffer_A0_Local_Memory[61] = 0xF7;
        // #elif __WAVELENGTH_1290_VER__==1
        //         I2C_Slave_Buffer_A0_Local_Memory[60] = 0x05;
        //         I2C_Slave_Buffer_A0_Local_Memory[61] = 0x0B;
        // #elif __WAVELENGTH_1330_VER__==1
        //         I2C_Slave_Buffer_A0_Local_Memory[60] = 0x05;
        //         I2C_Slave_Buffer_A0_Local_Memory[61] = 0x33;
        // #elif __WAVELENGTH_1350_VER__==1
        //         I2C_Slave_Buffer_A0_Local_Memory[60] = 0x05;
        //         I2C_Slave_Buffer_A0_Local_Memory[61] = 0x47;
        // #elif __WAVELENGTH_1410_VER__==1
        //         I2C_Slave_Buffer_A0_Local_Memory[60] = 0x05;
        //         I2C_Slave_Buffer_A0_Local_Memory[61] = 0x83;
        // #elif __WAVELENGTH_1430_VER__==1
        //         I2C_Slave_Buffer_A0_Local_Memory[60] = 0x05;
        //         I2C_Slave_Buffer_A0_Local_Memory[61] = 0x97;
        // #elif __WAVELENGTH_1450_VER__==1
        //         I2C_Slave_Buffer_A0_Local_Memory[60] = 0x05;
        //         I2C_Slave_Buffer_A0_Local_Memory[61] = 0xAB;
        // #elif __WAVELENGTH_1470_VER__==1
        //         I2C_Slave_Buffer_A0_Local_Memory[60] = 0x05;
        //         I2C_Slave_Buffer_A0_Local_Memory[61] = 0xBF;
        // #elif __WAVELENGTH_1490_VER__==1
        //         I2C_Slave_Buffer_A0_Local_Memory[60] = 0x05;
        //         I2C_Slave_Buffer_A0_Local_Memory[61] = 0xD3;
        // #elif __WAVELENGTH_1510_VER__==1
        //         I2C_Slave_Buffer_A0_Local_Memory[60] = 0x05;
        //         I2C_Slave_Buffer_A0_Local_Memory[61] = 0xE7;
        // #elif __WAVELENGTH_1530_VER__==1
        //         I2C_Slave_Buffer_A0_Local_Memory[60] = 0x05;
        //         I2C_Slave_Buffer_A0_Local_Memory[61] = 0xFB;
        // #elif __WAVELENGTH_1550_VER__==1
        //         I2C_Slave_Buffer_A0_Local_Memory[60] = 0x06;
        //         I2C_Slave_Buffer_A0_Local_Memory[61] = 0x0F;
        // #else
        //         I2C_Slave_Buffer_A0_Local_Memory[60] = 0x00;
        //         I2C_Slave_Buffer_A0_Local_Memory[61] = 0x00;
        // #endif

        default_memory = (uint8_t *)FLASH_A0_START;
        FLASH_Update((unsigned int)default_memory, (unsigned int)dump_memory, 128);

        //
        dump_memory = (uint8_t *)&I2C_Slave_Buffer_A2[0];
        default_memory = (uint8_t *)FLASH_A2_LOWER_CONST_START;
        //	default_memory = (uint8_t *)&FlashDataA2_Const[0];
        FLASH_Read((unsigned int)dump_memory, (unsigned int)default_memory, 128);

        //        I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_STATUS_CONTROL] = 0x08;
        //        I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_EXTENDED_CONTROL_STATUS] = 0x08;

        I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_STATUS_CONTROL] = 0x00;
        I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_EXTENDED_CONTROL_STATUS] = 0x00;

        default_memory = (uint8_t *)FLASH_A2_START;
        FLASH_Update((unsigned int)default_memory, (unsigned int)dump_memory, 128);

        //
        dump_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P01H_Up[0];
        memset(dump_memory, 0x00, 128);

        dump_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P00H_Up[0];
        memset(dump_memory, 0x00, 128);

        default_memory = (uint8_t *)FLASH_USER_EERPOM_START;
        FLASH_Update((unsigned int)default_memory, (unsigned int)dump_memory, 256);
        SW_Delay(100);

        // A2 Page_02H Data Set
        dump_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P02H_Up[0];
        memset(dump_memory, 0x00, 128);
        tunableControlMemPtr = (PAGE_02H_MEMORY_MAP *)&dump_memory[0];
        tunableControlMemPtr->Channel_Number_Set = __swap_bytes(1);

        default_memory = (uint8_t *)FLASH_PAGE02H_START;
        FLASH_Update((unsigned int)default_memory, (unsigned int)dump_memory, 128);
        SW_Delay(100);

        //	// A2 Page_80H Data Set
        //	dump_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P80H_Up[0];
        //	memset(dump_memory,0x00,128);
        //	flashPtr1 = (A2_PAGE_80H_MEMORY_MAP *)&dump_memory[0];
        ////	flashPtr->tec_set = __swap_bytes(0x0bde); // 1900 mV
        ////	flashPtr->tec_enable = 0;
        ////	flashPtr->tec_shutdown = 1;
        //
        //        flashPtr1->VCC_Slope = __swap_bytes(1);
        //        flashPtr1->VCC_Offset = __swap_bytes(0);
        //        flashPtr1->ITEMP_Slope = __swap_bytes(1);
        //        flashPtr1->ITEMP_Offset = __swap_bytes(0);
        //
        //        default_memory = (uint8_t *)FLASH_PAGE80H_START;
        //	FLASH_Update((unsigned int)default_memory, (unsigned int)dump_memory, 128);
        //
        // A2 Page_81H Data Set
        dump_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P81H_Up[0];
        memset(dump_memory, 0x00, 128);
        flashPtr = (A2_PAGE_81H_MEMORY_MAP *)&dump_memory[0];
        // TEC
        flashPtr->TEC1_SETPOINT = __swap_bytes(0x401b); // 52C Setting

        flashPtr->TEC1_KP = __swap_bytes(3840);                            //
        flashPtr->TEC1_KI = __swap_bytes(8192);                            // 256 -> 8192
        flashPtr->TEC1_KD = __swap_bytes(0);                               //
        flashPtr->TEC1_SHIFT = __swap_bytes(1911);                         //
        flashPtr->TEC1_POSERRCLAMP = __swap_bytes(256);                    //
        flashPtr->TEC1_NEGERRCLAMP = __swap_bytes(65280);                  //
        flashPtr->TEC1_POSOPCLAMP = __swap_bytes(16500);                   //
        flashPtr->TEC1_NEGOPCLAMP = __swap_bytes(50000);                   // 45000 -> 50000
        flashPtr->TEC1_CNFGCURRENTMEA_BURSTGPIOCONFIG = __swap_bytes(920); //
        flashPtr->TEC1_OFFSETRIGGER = __swap_bytes(0);                     //
        flashPtr->TEC1_OFFSETRIGGER = __swap_bytes(0);                     //
        flashPtr->TEC1_NORMAL_VCC = __swap_bytes(19600);                   //

// APD
#if __HSFP_10G_ER_SEMI_TUNABLE__ == 1

#else

        flashPtr->APD_ERRSTARTCLAMP = __swap_bytes(0x007F);     // (127)
        flashPtr->APD_DUTYCLAMP = __swap_bytes(0xB300);         // (45824)
                                                                //        flashPtr->APD_INTEGRALGAIN = __swap_bytes(0x0800); //
        flashPtr->APD_INTEGRALGAIN = __swap_bytes(0x0001);      // (1)
        flashPtr->APD_DUTYSTARTINCCLAMP = __swap_bytes(0x0040); // (64)
        flashPtr->APD_INTEGRALCLAMP = __swap_bytes(0xFFF7);     // (65527)
        flashPtr->APD_APDNEGERRCLAMP = __swap_bytes(0x0020);    // (32)
        flashPtr->APD_APDPOSERRCLAMP = __swap_bytes(0x0020);    // (32)
        flashPtr->APD_PROPORTIONALGAIN = __swap_bytes(0xF000);  // (61440)
#endif

        flashPtr->APD_CONFIG = __swap_bytes(0x2044);        // (8260)
        flashPtr->APD_TARGET_OUTPUT = __swap_bytes(0x09C4); // 25V
                                                            //        flashPtr->APD_TARGET_OUTPUT = __swap_bytes(0x0A8C); // 27V

        flashPtr->APD_VBR_DIFF = APD_VBR_DIFF_VALUE; // TruLight 20 mV, MACOM 30 mV

        // IDAC1 ~ IDAC4
        //        flashPtr->IDAC_CONFIG = __swap_bytes(0x000D); //

        flashPtr->rxPower_coeff_0 = __swap_bytes_to_float((FP32)0.1854);
        flashPtr->rxPower_coeff_1 = __swap_bytes_to_float((FP32)0.0076);
        flashPtr->rxPower_coeff_2 = __swap_bytes_to_float((FP32)2e-7);

        //        flashPtr->idcn = __swap_bytes(10); // LOS Assert Threshold: -30 dBm
        //        flashPtr->idcd = __swap_bytes(15); // LOS DeAssert Threshold, -28 dBm

        //        flashPtr->idcn = __swap_bytes(14); // LOS Assert Threshold: -30 dBm
        //        flashPtr->idcd = __swap_bytes(18); // LOS DeAssert Threshold, -28 dBm

        //        flashPtr->idcn = __swap_bytes(0x0A); // LOS Assert Threshold: -30 dBm
        //        flashPtr->idcd = __swap_bytes(0x10); // LOS DeAssert Threshold, -28 (-30.457) dBm
        flashPtr->idcn = __swap_bytes(0x09); // LOS Assert Threshold: -30.5 dBm
        flashPtr->idcd = __swap_bytes(0x0E); // LOS DeAssert Threshold, -28.5 (-28.538) dBm

        // flashPtr->MANCHESTER_MODE_CONTROL = 5; // 5분

        default_memory = (uint8_t *)FLASH_PAGE81H_START;
        FLASH_Update((unsigned int)default_memory, (unsigned int)dump_memory, 128);
        SW_Delay(100);

        // A2 Page_80H Data Set
        dump_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P80H_Up[0];
        memset(dump_memory, 0x00, 128);
        flashPtr1 = (A2_PAGE_80H_MEMORY_MAP *)&dump_memory[0];
        //	flashPtr->tec_set = __swap_bytes(0x0bde); // 1900 mV
        //	flashPtr->tec_enable = 0;
        //	flashPtr->tec_shutdown = 1;

        flashPtr1->flash_reset_flag = __swap_bytes(0x0C00);
        flashPtr1->VCC_Slope = __swap_bytes(1);
        flashPtr1->VCC_Offset = __swap_bytes(0);
        flashPtr1->ITEMP_Slope = __swap_bytes(1);
        flashPtr1->ITEMP_Offset = __swap_bytes(0);

        default_memory = (uint8_t *)FLASH_PAGE80H_START;
        FLASH_Update((unsigned int)default_memory, (unsigned int)dump_memory, 128);

        SW_Delay(100);

        // [DCLEE] 200616 --> Factory reset for TX (MAOM-37049), RX CDR (MAOM-37046)
        // CDR Info
        factory_reset_for_tx_rx_cdr();
        // [DCLEE] 200616 <-- Factory reset for TX (MAOM-37049), RX CDR (MAOM-37046)

        SW_Delay(100);

        restore_memory_from_flash_all();

        return;
}

// RX CDR Registers

// Module DOM and Channel DOM

// RX CDR Initialization
uint16_t rx_cdr_init(uint8_t flag)
{
#if __SFP28_ER__ == 1
#if __SFP28_ER_SEMI_TUNABLE__ == 1

#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
        // GN_1157
        //	uint8_t	xdata tVal, r_chNo, reg_addr;
        uint8_t xdata reg_addr;
        uint8_t xdata rVal;
        uint16_t ret_val = 0;

        // Check TX CDR Communication: Read CHIPID: 0x89 default.
        rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_ID);
        if (rVal != GN_1157_CHIPID)
        {
                ret_val = SFP28_MODULE_STATE_FAULT;
                return ret_val;
        }

        ret_val = 0;

        // Set RX Registers
        memset(&rx_i2c_master_data[0], 0x00, 16);

        //        // P00_RX_CONTROL_1
        //        reg_addr = P00_RX_CONTROL_1;
        //        rx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
        //
        //        // P00_RX_CONTROL_2
        //        rx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1];
        //
        //	if (flag == 0) {
        //		// Power Down Off
        //		rx_i2c_master_data[1] = rx_i2c_master_data[1] & 0xDF; // 0x00; // start Addr: 0x3E
        //	}
        //	else if (flag == 1) {
        //		// Power Down Set
        //		rx_i2c_master_data[1] = rx_i2c_master_data[1] | 0x20; // 0x00; // start Addr: 0x3E
        //	}
        //	else {
        //		// Power Down Off
        //		rx_i2c_master_data[1] = rx_i2c_master_data[1] & 0xDF; // 0x00; // start Addr: 0x3E
        //	}
        //
        //        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = rx_i2c_master_data[1];
        //        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_CONTROL_1, 2, &rx_i2c_master_data[0]);

        // P00_RX_RATE_SELECT
        reg_addr = P00_RX_RATE_SELECT;

        // P00_RX_RATE_SELECT_MSB
        rx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 0];

        // P00_RX_RATE_SELECT_LSB
        rx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 1];
        //        rx_i2c_master_data[1] = 0x01;

        //        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = rx_i2c_master_data[1];
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_RATE_SELECT, 2, &rx_i2c_master_data[0]);

        // P00_EXT_RX_PWR_LOS_CONTROL
        reg_addr = P00_EXT_RX_PWR_LOS_CONTROL;
        rx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 0];
        //        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];

        // P00_EXT_RX_PWR_LOS_THRESHOLD
        rx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 1];
        //        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = tx_i2c_master_data[1];

        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_EXT_RX_PWR_LOS_CONTROL, 2, &rx_i2c_master_data[0]);

        // P00_LOS_VBE_DAC
        reg_addr = P00_LOS_VBE_DAC;
        rx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 0];
        //        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];

        // P00_LOS_VT_DAC
        rx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 1];
        //        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = tx_i2c_master_data[1];

        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_LOS_VBE_DAC, 2, &rx_i2c_master_data[0]);

        // P00_RX_CONTROL_1
        reg_addr = P00_RX_CONTROL_1;
        rx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 0];

        // P00_RX_CONTROL_2
        rx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 1];

        if (flag == 0)
        {
                // Power Down Off
                rx_i2c_master_data[1] = rx_i2c_master_data[1] & 0xDF; // 0x00; // start Addr: 0x3E
        }
        else if (flag == 1)
        {
                // Power Down Set
                rx_i2c_master_data[1] = rx_i2c_master_data[1] | 0x20; // 0x00; // start Addr: 0x3E
        }
        else
        {
                // Power Down Off
                rx_i2c_master_data[1] = rx_i2c_master_data[1] & 0xDF; // 0x00; // start Addr: 0x3E
        }

        I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 1] = rx_i2c_master_data[1];
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_CONTROL_1, 2, &rx_i2c_master_data[0]);

        return ret_val;

#else

        //	uint8_t	xdata tVal, r_chNo, reg_addr;
        uint8_t xdata reg_addr;
        uint8_t xdata rVal;
        uint16_t ret_val = 0;

        // Check RX CDR Communication: Read CHIPID: 0x30 default.
        rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, 0x00);
        if (rVal != MAOM_37030B_CHIPID)
        {
                ret_val = SFP28_MODULE_STATE_FAULT;
                return ret_val;
        }

        //        reg_addr = P00_LB_MISCL;
        //        rx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] | 0x80; // Normal Signal Enable
        //	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_LB_MISCL, 1, &rx_i2c_master_data[0]);

        reg_addr = P00_RX_MODES;

        // Set RX CDR Registers
        // Mode
        if (flag == 0)
        {
                // Power Down Off
                rx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 0] & 0x7F; // 0x00; // start Addr: 0x10
        }
        else if (flag == 1)
        {
                // Power Down Set
                rx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 0] | 0x80; // 0x00; // start Addr: 0x10
        }
        else
        {
                // Power Down Off
                rx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 0] & 0x7F; // 0x00; // start Addr: 0x10
        }

        I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 0] = rx_i2c_master_data[0];

        // LOS THRS
        rx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 1]; // 0x00; // Addr: 0x11

        // RX_SLA
        rx_i2c_master_data[2] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 2]; // 0x04; // Addr: 0x12

        // RX_CDRLBW
        rx_i2c_master_data[3] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 3]; // 0x10; // Addr: 0x13

        // RX_CDR_MISCL
        rx_i2c_master_data[4] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 4]; // 0x20; // Addr: 0x14

        // RX_OP_SWING
        rx_i2c_master_data[5] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 5]; // 0x20; // Addr: 0x15

        // RX_OP_DEEMPH
        rx_i2c_master_data[6] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 6]; // 0x00; // Addr: 0x16

        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_MODES, 7, &rx_i2c_master_data[0]);
        return ret_val;

#endif

#else

        //	uint8_t	xdata rVal, tVal;
        uint8_t xdata rVal;
        uint16_t ret_val = 0;

        // Check TX CDR Communication: Read CHIPID: 0x89 default.
        rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, 0x00);
        if (rVal != MAOM_37032A_CHIPID)
        {
                ret_val = SFP28_MODULE_STATE_FAULT;
                return ret_val;
        }

        // Set RX CDR Registers
        // Mode
        if (flag == 0)
        {
                // Power Down Off
        }
        else
        {
                // Power Down Set
                rx_i2c_master_data[0] = 0xA0; // start Addr: 0x30
                write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_MODES, 1, &rx_i2c_master_data[0]);
                return ret_val;
        }

        // LOS LOL MASK CH
        rx_i2c_master_data[1] = 0x00; // Addr: 0x31

        // LOS THRS
        rx_i2c_master_data[2] = 0x00; // Addr: 0x32

        // CTLE
        rx_i2c_master_data[3] = 0x10; // Addr: 0x33

        // OUTPUT Swing
        rx_i2c_master_data[4] = 0x20; // Addr: 0x34

        // OUTPUT DE-EMPHASIS
        rx_i2c_master_data[5] = 0x00; // Addr: 0x35

        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_MODES, 1, &rx_i2c_master_data[0]);

        return ret_val;
#endif
#endif
}

uint16_t rx_cdr_init_from_flash(uint8_t flag)
{
#if __SFP28_ER_SEMI_TUNABLE__ == 1
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
        // GN_1157
        return 0;

#else

        uint8_t xdata rVal;
        uint8_t xdata reg_addr;
        uint8_t read_val[18];
        uint8_t *xdata flash_memory;
        //        uint8_t rate_select;
        uint8_t device_id;
        uint16_t ret_val = 0;

        // Check TX CDR Communication: Read CHIPID: 0x89 default.
        rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_CHIPID);
        if (rVal != MAOM_37030B_CHIPID)
        {
                ret_val = SFP28_MODULE_STATE_FAULT;
                return ret_val;
        }

        flash_memory = (uint8_t *)(FLASH_PAGE82H_START);

        FLASH_Read((unsigned int)(&read_val[0]), (unsigned int)flash_memory, 2);

        device_id = read_val[0];
        //	device_revid = read_val[1];

        if (device_id != (uint8_t)MAOM_37030B_CHIPID)
        {
                ret_val = SFP28_MODULE_STATE_FAULT;
                return ret_val;
        }

        // Set RX CDR Registers

        memset(&read_val[0], 0, 16);

        // RX_Mode
        reg_addr = P00_RX_MODES;
        flash_memory = (uint8_t *)(FLASH_PAGE82H_START + reg_addr);
        FLASH_Read((unsigned int)(&read_val[0]), (unsigned int)flash_memory, 8);
        //        read_val[0] = 0x40;

        if (flag == 0)
        {
                // Power Down Off
                rx_i2c_master_data[0] = read_val[0] & 0x7F; // 0x00; // start Addr: 0x10
        }
        else if (flag == 1)
        {
                // Power Down Set
                rx_i2c_master_data[0] = read_val[0] | 0x80; // 0x00; // start Addr: 0x10
        }
        else
        {
                // Power Down Off
                rx_i2c_master_data[0] = read_val[0] & 0x7F; // 0x00; // start Addr: 0x10
        }

        // Rate Select: 200722 -->

        I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 0] = rx_i2c_master_data[0];

        //	// LOS THRS
        rx_i2c_master_data[1] = read_val[1]; // 0x00; // Addr: 0x11
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 1] = rx_i2c_master_data[1];
        //
        //
        //	// RX_SLA
        rx_i2c_master_data[2] = read_val[2]; // 0x04; // Addr: 0x12
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 2] = rx_i2c_master_data[2];
        //
        //	// RX_CDRLBW
        rx_i2c_master_data[3] = read_val[3]; // 0x10; // Addr: 0x13
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 3] = rx_i2c_master_data[3];
        //
        //        // RX_CDR_MISCL
        rx_i2c_master_data[4] = read_val[4]; // 0x10; // Addr: 0x14
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 4] = rx_i2c_master_data[4];
        //
        //	// RX_OP_SWING
        rx_i2c_master_data[5] = read_val[5]; // 0x20; // Addr: 0x15
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 5] = rx_i2c_master_data[5];
        //
        //	// RX_OP_DEEMPH
        rx_i2c_master_data[6] = read_val[6]; // 0x00; // Addr: 0x16
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 6] = rx_i2c_master_data[6];

        //        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_MODES, 7, &rx_i2c_master_data[0]);
        //        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_MODES, 1, &rx_i2c_master_data[0]);

        return ret_val;

#endif

#else
        return 0;
#endif
}

void rx_cdr_init_by_channel(uint8_t chNo, uint8_t flag)
{
#if __SFP28_ER__ == 1
#if __SFP28_ER_SEMI_TUNABLE__ == 1

#else
        //	uint8_t	xdata tVal, r_chNo, reg_addr;
        uint8_t xdata reg_addr;

        reg_addr = P00_LB_MISCL;
        rx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 0] | 0x80; // Normal Signal Enable
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_LB_MISCL, 1, &rx_i2c_master_data[0]);

        reg_addr = P00_RX_MODES;

        // Set RX CDR Registers
        // Mode
        if (flag == 0)
        {
                // Power Down Off
                rx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 0] & 0x5F; // 0x00; // start Addr: 0x30
        }
        else if (flag == 1)
        {
                // Power Down Set
                rx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 0] | 0xA0; // 0x00; // start Addr: 0x30
        }
        else
        {
                // Power Down Off
                rx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 0] & 0x5F; // 0x00; // start Addr: 0x30
        }

        // LOS LOL MASK CH
        rx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 1]; // 0x00; // Addr: 0x31

        // LOS THRS
        rx_i2c_master_data[2] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 2]; // 0x04; // Addr: 0x32

        // CTLE
        rx_i2c_master_data[3] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 3]; // 0x10; // Addr: 0x33

        // OUTPUT Swing
        rx_i2c_master_data[4] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 4]; // 0x20; // Addr: 0x34

        // OUTPUT DE-EMPHASIS
        rx_i2c_master_data[5] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 5]; // 0x00; // Addr: 0x35

        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_MODES, 1, &rx_i2c_master_data[0]);

#endif

#endif
}

void rx_cdr_forced_mute_enable(unsigned char flag)
{
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
        // GN_1157
        uint8_t reg_addr, rVal;

        reg_addr = P00_RX_CONTROL_2;

        //	rx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0]; // 0x00; // Addr: 0x15
        rVal = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 0]; // 0x00; // Addr: 0x15
        read_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_CONTROL_2, 1, &rx_i2c_master_data[0]);

        if (flag == 1)
        {
                // Forced mute set, bit 1: Force Rx Squelch 0 = Normal operation, 1 = Forced squelch on Rx output
                rVal = rVal | 0x02;
        }
        else
        {
                // Forced mute clear
                rVal = rVal & 0xFD;
        }

        if (rVal != rx_i2c_master_data[0])
        {
                rx_i2c_master_data[0] = rVal;
                write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_CONTROL_2, 1, &rx_i2c_master_data[0]);
        }

#else
        uint8_t reg_addr, rVal;

        reg_addr = P00_RX_OP_SWING;

        //	rx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0]; // 0x00; // Addr: 0x15
        rVal = I2C_Slave_Buffer_A2_P82H_Up[reg_addr + 0]; // 0x00; // Addr: 0x15
        read_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_OP_SWING, 1, &rx_i2c_master_data[0]);

        if (flag == 1)
        {
                // Forced mute set
                rVal = rVal | 0x40;
        }
        else
        {
                // Forced mute clear
                rVal = rVal & 0xBF;
        }

        if (rVal != rx_i2c_master_data[0])
        {
                rx_i2c_master_data[0] = rVal;
                write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_OP_SWING, 1, &rx_i2c_master_data[0]);
        }
#endif
}

void initialize_variables()
{

        //	flashStructType	xdata * flashPtr;
        //	int xdata idx;
        //
        //	flashPtr = (flashStructType *)&I2C_Slave_Buffer_A4_Local_Memory[0];
        unsigned int reset_flag;
        A2_PAGE_80H_MEMORY_MAP xdata *flashPtr;
        //        A2_PAGE_81H_MEMORY_MAP	xdata * flashPtr_1;

        flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
        //        flashPtr_1 = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P81H_Up[0];

        already_act_reset_flag = 0;
        //	sfp28_module_state = SFP28_MODULE_STATE_RESET;
        high_power_up_action_flag = 0;

        vendor_specific_pin_control_config = 0;

        page_vendor_control = 0;

        Ld_Ch_seq_init();

        memset(page_password_enable, 0, sizeof(page_password_enable));
        // display_trx_info(margc, margv);
        //	display_trx_info();
        //	i2c_master_gpio_init(); // Initialization for I2C_Master (P0.2: S_DATA, P0.3: S_CLOCK)
        //	I2CS_init();
        //
        //	WDTCN = 0xA5;  // WatchDog Timer Reset

        write_i2c_count = 0;
        read_i2c_count = 0;
        cdr_reset_counter = 0;

        tx_dis_flag_before_isr = 0;
        tx_dis_flag_after_isr = 0;

        rx_los_flag_before_isr = 0;
        rx_los_flag_after_isr = 0;

        prev_cdr_los_lol_status = 0;

#if __HFR_REQ_DDM_FLAG_VER__ == 1
        ddm_temperature_flag = 0;
        ddm_vcc_flag = 0;
        ddm_rx_power_flag = 0;
        ddm_tx_bias_flag = 0;
        ddm_tx_power_flag = 0;
#endif

        restore_memory_from_flash_all();

        reset_flag = __swap_bytes(flashPtr->flash_reset_flag);
        if (reset_flag != 0x0C00)
        {
                sfp28_module_state = SFP28_MODULE_STATE_FAULT;
        }
        else
        {
                sfp28_module_state = SFP28_MODULE_STATE_RESET;
        }

        // printf("size of lower memory: %d \r\n", (short) (sizeof(LOWER_MEMORY_MAP)));
        // IE_EA = 1;

        //	INT_OUTPUT_TXDIS_CDR = TXDIS_CDR_ON; // Keep TXDIS
        PLACNT1_bit.SB1 = TXDIS_CDR_ON; // Using Soft TXDIS pin ���
                                        //        PLACNT3_bit.SB2 = ASSERTED; // Using Soft TX Fault pin to H ���

        PLA_Soft_Tx_Fault_Control(ASSERTED);

        INT_OUTPUT_RS1_uC = 0;
        INT_OUTPUT_RS0_uC = 0;

#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
        INT_RSTB = 0;   // Reset Normal
        SW_Delay(1000); // [DCLEE] 21.01.29. <-- ���Ŀ� �ð��� ���� �ʿ� ����. ���� ���ؼ� ����
        INT_RSTB = 1;   // Reset Normal
#endif

        // CDR I/F Status check
        //	polled_rx_cdr_reg_info();
        SW_Delay(50000); // [DCLEE] 21.01.29. <-- ���Ŀ� �ð��� ���� �ʿ� ����. ���� ���ؼ� ����
        polled_tx_rx_combo_cdr_reg_info();
        SW_Delay(10000); // [DCLEE] 21.01.29. <-- ���Ŀ� �ð��� ���� �ʿ� ����. ���� ���ؼ� ����

        //        tx_cdr_init_from_flash(1);
        //        rx_cdr_init_from_flash(1);

        //        cdr_power_management_init(1);

        //	tx_cdr_init(1);
        //	rx_cdr_init(1);
        //
        ////	WDTCN = 0xA5;
        //
        //	restore_memory_from_flash_rx_cdr();
        //	restore_memory_from_flash_tx_cdr();

        // PIN Init
        // DAC1_setOutput(flashPtr->tec_set);

        tx_cdr_init_from_flash(1);
        rx_cdr_init_from_flash(1);

        //        update_msa_control_regs_from_tx_cdr();
        //        update_msa_control_regs_from_rx_cdr();

        main_sigNo = 0;
        main_idx = 0;

        // Initialize Autoscan mode
        //	polled_adc_operation();
        //
        //	WDTCN = 0xA5;

        // IE_EA = 1;

        // [DCLEE] 20.09.17. rate select control for RS1/RS0 Pin or Soft register bit info. 10G, 25G ���� ����� ���� ����, MSA ����� ���� �ٸ�, 10G ����� ��� -->
        update_rate_select_operation();

        wavelength_info_set();

        *((unsigned int *)&I2C_Slave_Buffer_A2_P02H_Up[0x50]) = __swap_bytes(cdr_reset_counter); // for DEBUG, 191104
}

void restore_memory_from_flash_all(void)
{
        //	int xdata i;
        uint8_t *xdata flash_memory;
        uint8_t *xdata ram_memory;
        //	A2_PAGE_80H_MEMORY_MAP	* flashPtr1;
        //	A2_PAGE_81H_MEMORY_MAP	* flashPtr;

        //	flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
        //	flashPtr1 = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P81H_Up[0];

        ram_memory = (uint8_t *)&I2C_Slave_Buffer_A0_Local_Memory[0];
        flash_memory = (uint8_t *)((FLASH_A0_START));
        FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 256);

        ram_memory = (uint8_t *)&I2C_Slave_Buffer_A2[0];
        flash_memory = (uint8_t *)((FLASH_A2_START));
        FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 128);

        // [DCLEE] 20.09.17. rate select control for RS1/RS0 Pin or Soft register bit info. 10G, 25G ���� ����� ���� ����, MSA ����� ���� �ٸ�, 10G ����� ��� -->
        // �Ʒ� ������ ���� --> �ٽ� open, 200920_a version������
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1

#if __HSFP_10G_MULTI_RATE_SEMI_TUNABLE__ == 1
        I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_STATUS_CONTROL] &= 0x08;
        I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_EXTENDED_CONTROL_STATUS] &= 0x08;

#else
        I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_STATUS_CONTROL] &= 0xF7;
        I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_EXTENDED_CONTROL_STATUS] &= 0xF7;
#endif

#else
        I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_STATUS_CONTROL] |= 0x08;
        I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_EXTENDED_CONTROL_STATUS] |= 0x08;
#endif
#if __INTEROPERABILITY_TEST_P00H__ == 1
        I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_TABLE] = 0x00;
#elif __INTEROPERABILITY_TEST_P02H__ == 1
        I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_TABLE] = 0x02;
#else
        I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_TABLE] = 0x00;
#endif
        //         <--

        ram_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P00H_Up[0];
        flash_memory = (uint8_t *)((FLASH_USER_EERPOM_START));
        FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 128);

        // [DEBUG DCLEE] 2020.11.13. FW Version: 0x80, 0x81, 0x82, 0x83: ASCII vv.v
        I2C_Slave_Buffer_A2_P00H_Up[0] = FW_VER_0;
        I2C_Slave_Buffer_A2_P00H_Up[1] = FW_VER_1;
        I2C_Slave_Buffer_A2_P00H_Up[2] = FW_VER_2;
        I2C_Slave_Buffer_A2_P00H_Up[3] = FW_VER_3;

        ram_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P01H_Up[0];
        flash_memory = (uint8_t *)((FLASH_USER_EERPOM_START + 128));
        FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 128);

        //        A0_UPPER_SRAM_OFFSET

#if __INTEROPERABILITY_TEST_P00H__ == 1
        ram_memory = (uint8_t *)A2_UPPER_SRAM_OFFSET;
        flash_memory = (uint8_t *)((FLASH_USER_EERPOM_START));
        FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 128);

        I2C_Slave_Buffer_A2_Pn_Up[0] = FW_VER_0;
        I2C_Slave_Buffer_A2_Pn_Up[1] = FW_VER_1;
        I2C_Slave_Buffer_A2_Pn_Up[2] = FW_VER_2;
        I2C_Slave_Buffer_A2_Pn_Up[3] = FW_VER_3;

#elif __INTEROPERABILITY_TEST_P02H__ == 1
        ram_memory = (uint8_t *)A2_UPPER_SRAM_OFFSET;
        flash_memory = (uint8_t *)((FLASH_PAGE02H_START));
        FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 128);
#else
        ram_memory = (uint8_t *)A2_UPPER_SRAM_OFFSET;
        flash_memory = (uint8_t *)((FLASH_USER_EERPOM_START));
        FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 128);
#endif

        ram_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P02H_Up[0];
        flash_memory = (uint8_t *)((FLASH_PAGE02H_START));
        FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 128);

        ram_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P80H_Up[0];
        flash_memory = (uint8_t *)((FLASH_PAGE80H_START));
        FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 128);

        ram_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P81H_Up[0];
        flash_memory = (uint8_t *)((FLASH_PAGE81H_START));
        FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 128);

#if __HFR_REQ_VER__ == 1
#if __HSFP_10G_MULTI_RATE_SEMI_TUNABLE__ == 1
        uint16_t ch_no_from_flash;
        uint8_t temp_data_flash[4];
        uint8_t module_status, enhaced_module_status;

        ram_memory = (uint8_t *)&temp_data_flash[0];
        flash_memory = (uint8_t *)((FLASH_CH_NO_VENDOR_SPECIFIC));
        FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 4);

        ch_no_from_flash = __swap_bytes(*(uint16_t *)&temp_data_flash[0]);

        *(unsigned int *)&I2C_Slave_Buffer_A2_P01H_Up[0x78] = __swap_bytes(ch_no_from_flash);

        if ((ch_no_from_flash > 0) && (ch_no_from_flash < 9))
        {
                *(unsigned int *)&I2C_Slave_Buffer_A2_P02H_Up[0x10] = __swap_bytes(ch_no_from_flash);
        }

        module_status = temp_data_flash[2];
        enhaced_module_status = temp_data_flash[3];

        I2C_Slave_Buffer_A2_P01H_Up[0x7A] = module_status;

        I2C_Slave_Buffer_A2_P01H_Up[0x7B] = enhaced_module_status;

        if (module_status != 0xFF)
        {
                // I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_STATUS_CONTROL] = module_status & 0x08;
                I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_STATUS_CONTROL] = module_status;
        }

        if (enhaced_module_status != 0xFF)
        {
                // I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_EXTENDED_CONTROL_STATUS] = enhaced_module_status & 0x08;
                I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_EXTENDED_CONTROL_STATUS] = enhaced_module_status;
        }

#else
        uint16_t ch_no_from_flash, temp_data_flash;

        ram_memory = (uint8_t *)&temp_data_flash;
        flash_memory = (uint8_t *)((FLASH_CH_NO_VENDOR_SPECIFIC));
        FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 2);

        ch_no_from_flash = __swap_bytes(*(uint16_t *)&temp_data_flash[0]);

        *(unsigned int *)&I2C_Slave_Buffer_A2_P01H_Up[0x78] = __swap_bytes(ch_no_from_flash);

        if ((ch_no_from_flash > 0) && (ch_no_from_flash < 9))
        {
                *(unsigned int *)&I2C_Slave_Buffer_A2_P02H_Up[0x10] = __swap_bytes(ch_no_from_flash);
        }
#endif

#endif

        current_password.long_data = 0;
        fixed_side_password.long_data = 0x00001011;

        //        restore_memory_from_flash_tx_cdr();
        //        restore_memory_from_flash_rx_cdr();

        // #if _DEBUG_MODE_== 1
        //	printf("\r\n");
        //	printf("current_password = (%x %x %x %x)\r\n",(uint16_t)current_password.byte_data[0],(uint16_t)current_password.byte_data[1],(uint16_t)current_password.byte_data[2],(uint16_t)current_password.byte_data[3] );
        //	printf("fixed_side_password = (%x %x %x %x)\r\n",(uint16_t)fixed_side_password.byte_data[0],(uint16_t)fixed_side_password.byte_data[1],(uint16_t)fixed_side_password.byte_data[2],(uint16_t)fixed_side_password.byte_data[3] );
        // #endif
        //
        // #if _DEBUG_MODE_== 1
        // #endif

        return;
}

void restore_memory_from_flash_tx_cdr(void)
{
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1

        //	int xdata i;
        uint8_t *xdata flash_memory;
        uint8_t *xdata ram_memory;
        uint8_t xdata device_id;
        //	uint8_t xdata device_id, device_revid;
        uint8_t read_val[4];

        ram_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P82H_Up[0];
        flash_memory = (uint8_t *)(FLASH_PAGE82H_START);

        FLASH_Read((unsigned int)(&read_val[0]), (unsigned int)flash_memory, 2);

        device_id = read_val[1];
        if (device_id == (uint8_t)GN_1157_CHIPID)
        {
                //		if (device_revid == ram_memory[1])
                {
                        FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 128);
                }
        }

#else

        //	int xdata i;
        uint8_t *xdata flash_memory;
        uint8_t *xdata ram_memory;
        uint8_t xdata device_id;
        //	uint8_t xdata device_id, device_revid;
        uint8_t read_val[4];

        ram_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P82H_Up[0];
        flash_memory = (uint8_t *)(FLASH_PAGE82H_START);

        FLASH_Read((unsigned int)(&read_val[0]), (unsigned int)flash_memory, 2);

        device_id = read_val[0];
        //	device_revid = read_val[1];
        if (device_id == (uint8_t)MAOM_37032A_CHIPID)
        {
                //		if (device_revid == ram_memory[1])
                {
                        FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 128);
                }
        }

#endif
}

void restore_memory_from_flash_rx_cdr(void)
{
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1

#else
        ////	int xdata i;
        //	uint8_t * xdata flash_memory;
        //	uint8_t * xdata ram_memory;
        //	uint8_t xdata device_id, device_revid;
        //        uint8_t read_val[4];
        //
        //	ram_memory = (uint8_t *)&I2C_Slave_Buffer_A0_P4_Up[0];
        //	flash_memory = (uint8_t *)(FLASH_PAGE04H_START);
        //
        ////        Read_Word_from_Flash
        ////        FLASH_PAGE04H_START
        //
        //        FLASH_Read((unsigned int)(&read_val[0]), (unsigned int)flash_memory, 2);
        //        device_id = read_val[0];
        //	device_revid = read_val[1];
        //	if (device_id == (uint8_t)M37046_CHIPID)
        //	{
        //		if (device_revid == ram_memory[1])
        //		{
        //			FLASH_Read((unsigned int)ram_memory, (unsigned int)flash_memory, 128);
        //		}
        //	}

#endif
}

// [DCLEE] 200616 --> Factory reset for TX CDR (MAOM-37049)
void save_memory_to_flash_tx_rx_cdr(void)
{
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
        // GN_1157
        uint8_t *xdata flash_memory;
        uint8_t *xdata ram_memory;
        uint8_t xdata device_id;

        ram_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P82H_Up[0];
        flash_memory = (uint8_t *)(FLASH_PAGE82H_START);

        device_id = I2C_Slave_Buffer_A2_P82H_Up[P00_ID];

        if (device_id == (uint8_t)GN_1157_CHIPID)
        {
                FLASH_Update((unsigned int)flash_memory, (unsigned int)ram_memory, 128);
        }

#else
        uint8_t *xdata flash_memory;
        uint8_t *xdata ram_memory;
        uint8_t xdata device_id;

        ram_memory = (uint8_t *)&I2C_Slave_Buffer_A2_P82H_Up[0];
        flash_memory = (uint8_t *)(FLASH_PAGE82H_START);

        device_id = I2C_Slave_Buffer_A2_P82H_Up[0];

        if (device_id == (uint8_t)MAOM_37030B_CHIPID)
        {
                FLASH_Update((unsigned int)flash_memory, (unsigned int)ram_memory, 128);
        }

#endif
}

void factory_reset_for_tx_rx_cdr(void)
{
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
        // GN_1157

        polled_tx_rx_combo_cdr_reg_info();

        SW_Delay(100);

        // Invert Polarity: W(0x40) = 0x02, W(0x50) = 0x02, W(0x60) = 0x06, W(0x70) = 0x06
        I2C_Slave_Buffer_A2_P82H_Up[P00_VCPA_DAC] = 0x00; // Disable TX Crossing Point
                                                          //  I2C_Slave_Buffer_A2_P82H_Up[P00_VEQ_DAC] = 0x01;  // Disable VEQ ftn, power the associated circuitry down
        I2C_Slave_Buffer_A2_P82H_Up[P00_VEQ_DAC] = 0x41;  // Disable VEQ ftn, power the associated circuitry down

        I2C_Slave_Buffer_A2_P82H_Up[P00_BIAS_TCA_DAC] = 0xFF; // Disable VEQ ftn, power the associated circuitry down
        I2C_Slave_Buffer_A2_P82H_Up[P00_MON_TCA_DAC] = 0xFF;  // Disable VEQ ftn, power the associated circuitry down
                                                              //  I2C_Slave_Buffer_A2_P82H_Up[P00_VF_TCA_DAC] = 0x80;  // Disable VEQ ftn, power the associated circuitry down
        I2C_Slave_Buffer_A2_P82H_Up[P00_VF_TCA_DAC] = 0xFF;   // Disable VEQ ftn, power the associated circuitry down

#if 1

        I2C_Slave_Buffer_A2_P82H_Up[P00_MOD_SET_DAC_MSB] = 0x00; // 12 bits, MSB 4 bits
        I2C_Slave_Buffer_A2_P82H_Up[P00_MOD_SET_DAC_LSB] = 0x00; // LSB 8 bits

        I2C_Slave_Buffer_A2_P82H_Up[P00_BIAS_SET_DAC_MSB] = 0x00; // 12 bits, MSB 4 bits
        I2C_Slave_Buffer_A2_P82H_Up[P00_BIAS_SET_DAC_LSB] = 0x00; // LSB 8 bits

        I2C_Slave_Buffer_A2_P82H_Up[P00_VSET_DAC_MSB] = 0x00; // 10 bits, MSB 2 bits
        I2C_Slave_Buffer_A2_P82H_Up[P00_VSET_DAC_LSB] = 0x00; // LSB 8 bits

#endif

        I2C_Slave_Buffer_A2_P82H_Up[P00_RX_RATE_SELECT_MSB] = 0x00; //
        I2C_Slave_Buffer_A2_P82H_Up[P00_RX_RATE_SELECT_LSB] = 0x01; // Low rate select, Typically 3.4 GHz

#if 1

        I2C_Slave_Buffer_A2_P82H_Up[P00_ADC_1] = 0x1E; // TX_VCC2, 200 kHz, 16-bit resolution
        I2C_Slave_Buffer_A2_P82H_Up[P00_ADC_2] = 0x00; // ADC MUX (000 = Temp)
        I2C_Slave_Buffer_A2_P82H_Up[P00_ADC_3] = 0x03; // Write/Read - Start continuous conversion cycling through Mux channels 0(TEMP), 2(VCC), 3(TX BIAS), 5(TX_PWR), 6(RX_PWR), 4(TX MOD)

        I2C_Slave_Buffer_A2_P82H_Up[P00_DIGITAL_VCO] = 0x02;              // Nominal VCO Speed (MHz), 0.74 MHz
        I2C_Slave_Buffer_A2_P82H_Up[P00_EXT_RX_PWR_LOS_CONTROL] = 0x14;   // manual RSSI range adaption, high current range register 2 k��, enable internal RSSI resistors
        I2C_Slave_Buffer_A2_P82H_Up[P00_EXT_RX_PWR_LOS_THRESHOLD] = 0x00; //

        //  I2C_Slave_Buffer_A2_P82H_Up[P00_LOS_VBE_DAC] = 0x1F;  //
        //  I2C_Slave_Buffer_A2_P82H_Up[P00_LOS_VT_DAC] = 0x1F;  //
        I2C_Slave_Buffer_A2_P82H_Up[P00_LOS_VBE_DAC] = 0x50; //
        I2C_Slave_Buffer_A2_P82H_Up[P00_LOS_VT_DAC] = 0x10;  //

#endif

        //  I2C_Slave_Buffer_A2_P82H_Up[P00_RX_CONTROL_1] = 0x05;  // bit[2:0] = 101 (800 mVppd), Pre-emphasis disable
        I2C_Slave_Buffer_A2_P82H_Up[P00_RX_CONTROL_1] = 0xAD; // bit[2:0] = 101 (800 mVppd), Pre-emphasis disable
        I2C_Slave_Buffer_A2_P82H_Up[P00_RX_CONTROL_2] = 0x00; // not squelch on LOS, inter LOS, normal operation, 2 uA offset current disable

        //  I2C_Slave_Buffer_A2_P82H_Up[P00_LDD_EYE_OPTIMIZE] = 0x00;  //
        I2C_Slave_Buffer_A2_P82H_Up[P00_LDD_EYE_OPTIMIZE] = 0x3C; // [DCLEE] 210812. <--

        I2C_Slave_Buffer_A2_P82H_Up[P00_TX_RATE_SELECT] = 0x01; // Low rate

        I2C_Slave_Buffer_A2_P82H_Up[P00_ISNK_MAX] = 0xFF;   //
        I2C_Slave_Buffer_A2_P82H_Up[P00_APC_WINDOW] = 0x40; //
        I2C_Slave_Buffer_A2_P82H_Up[P00_APC_MODE] = 0x00;   //

        I2C_Slave_Buffer_A2_P82H_Up[P00_CR2] = 0x1E; //
        I2C_Slave_Buffer_A2_P82H_Up[P00_CR1] = 0x81; //

        //  cdr_pmic_ch_control_reinit(0);

        //  SW_Delay(100);

        //  polled_tx_rx_combo_cdr_reg_info();

        //  SW_Delay(100);

        save_memory_to_flash_tx_rx_cdr();

#else

        polled_tx_rx_combo_cdr_reg_info();

        // Invert Polarity: W(0x40) = 0x02, W(0x50) = 0x02, W(0x60) = 0x06, W(0x70) = 0x06
        I2C_Slave_Buffer_A2_P82H_Up[P00_LB_MISCL] = 0x80;
        I2C_Slave_Buffer_A2_P82H_Up[P00_MISC] = 0x03;

        // P00_Global_Bias3
        I2C_Slave_Buffer_A2_P82H_Up[P00_Global_Bias3] = 0x07; // 2020.10.23. �߰� Factory reset

        // RX CDR Part
#if __ROSA_WOORIRO_VER__ == 1
        I2C_Slave_Buffer_A2_P82H_Up[P00_RX_MODES] = 0x40; // In case of Wooriro ROSA, no polarity inversion

#else
        //  I2C_Slave_Buffer_A2_P82H_Up[P00_RX_MODES] = 0x42;
        I2C_Slave_Buffer_A2_P82H_Up[P00_RX_MODES] = 0x44;
#endif

        I2C_Slave_Buffer_A2_P82H_Up[P00_RX_OP_SWING] = 0x9E; // RX Output swing 1E --> 9E

        // TX CDR Part
        //  I2C_Slave_Buffer_A2_P82H_Up[P00_TX_MODES] = 0x42;
        I2C_Slave_Buffer_A2_P82H_Up[P00_TX_MODES] = 0x40;
        //  I2C_Slave_Buffer_A2_P82H_Up[P00_TX_MODES] = 0x48; // TX Rate detect enable
        //  I2C_Slave_Buffer_A2_P82H_Up[P00_TX_ADAPT_EQ] = 0x0C; // CTLE: 3 dB
        I2C_Slave_Buffer_A2_P82H_Up[P00_TX_ADAPT_EQ] = 0x00; // CTLE: 0 dB

        I2C_Slave_Buffer_A2_P82H_Up[P00_TX_CDRLBW] = 0x00; // [2:0] tx_cdr_lbw_adj: 000b: TX CDR LBW 16MHz (recommended PLL BW for 20G or higher data rate).

        // LD Control
        I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL0] = 0x0F;
        I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL2] = 0x40;
#if __WAVELENGTH_1290_VER__ == 1
        //  I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL3] = 0xA1;
        //  I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL5] = 0xBF; // C �׷�: BF, D �׷�: A8, default: BF
        I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL3] = 0x9A;
        I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL5] = 0x89; // C �׷�: BF, D �׷�: A8, default: BF
#elif __WAVELENGTH_1270_VER__ == 1
        I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL3] = 0xA1;
        I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL5] = 0xBF; // C �׷�: BF, D �׷�: A8, default: BF
#elif __WAVELENGTH_1330_VER__ == 1
        I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL3] = 0x9A;
        I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL5] = 0xBF; // C �׷�: BF, D �׷�: A8, default: BF
#elif __WAVELENGTH_1350_VER__ == 1
        I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL3] = 0x9A;
        I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL5] = 0xBF; // C �׷�: BF, D �׷�: A8, default: BF
#else
        I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL3] = 0xA1;
        I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL5] = 0xBF; // C �׷�: BF, D �׷�: A8, default: BF
#endif

        I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL4] = 0xA3;
        //  I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL5] = 0x8F;
        //  I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL5] = 0x9F;

        save_memory_to_flash_tx_rx_cdr();

#endif
}

// [DCLEE] 200616 <-- Factory reset for TX CDR (MAOM-37049)

// APD Vbr Control: ST-SFP28: APD4 ��� (QSFP28: APD2 ���)
void APD_Process(signed int sTemp_value)
{
#if __SFP28_ER_SEMI_TUNABLE__ == 1

#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1

#if __HSFP_10G_ER_SEMI_TUNABLE__ == 1

        unsigned int set_boost_value = 0;
        unsigned int unData = 0;
        unsigned int diff_value, vbr_diff_value;
        signed int ref_temp_value;

        A2_PAGE_81H_MEMORY_MAP *flashPtr, *commomMemoryPtr;
        A2_PAGE_80H_MEMORY_MAP *flashPtr_1;
        A2_LOWER_MEMORY_MAP *lowerMemoryPtr;

        flashPtr = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P81H_Up[0];
        flashPtr_1 = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
        commomMemoryPtr = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_Pn_Up[0];
        lowerMemoryPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];

        ref_temp_value = __swap_bytes(flashPtr_1->nt_temp);
        ref_temp_value = ref_temp_value >> 8;

        vbr_diff_value = (unsigned int)(flashPtr->APD_VBR_DIFF);
        if (vbr_diff_value > 10)
        {
                vbr_diff_value = APD_VBR_DIFF_VALUE;
        }

        //  return;

        if ((flashPtr->PMIC_SELECT & APD_ENABLE) == APD_ENABLE) // if TEC is enabled?
        {
                if (~(APDCN4 & 0x0040))
                {
                        sTemp_value = sTemp_value >> 8; // get a truncated integer

                        if (sTemp_value < -40) //-40 is the minimum range
                        {
                                sTemp_value = -40;
                        }
                        if (sTemp_value > 104) // 104 is the maximum range
                        {
                                sTemp_value = 104;
                        }

                        if (sTemp_value > ref_temp_value)
                        {
                                diff_value = sTemp_value - ref_temp_value;
                                //        set_boost_value = __swap_bytes(flashPtr->APD_TARGET_OUTPUT) + (diff_value * APD_VBR_DIFF_VALUE);
                                set_boost_value = __swap_bytes(flashPtr->APD_TARGET_OUTPUT) + (diff_value * vbr_diff_value);
                        }
                        else if (sTemp_value < ref_temp_value)
                        {
                                diff_value = ref_temp_value - sTemp_value;
                                //        set_boost_value = __swap_bytes(flashPtr->APD_TARGET_OUTPUT) - (diff_value * APD_VBR_DIFF_VALUE);
                                set_boost_value = __swap_bytes(flashPtr->APD_TARGET_OUTPUT) - (diff_value * vbr_diff_value);
                        }
                        else
                        {
                                diff_value = 0;
                                //        set_boost_value = __swap_bytes(flashPtr->APD_TARGET_OUTPUT) + (diff_value * APD_VBR_DIFF_VALUE);
                                set_boost_value = __swap_bytes(flashPtr->APD_TARGET_OUTPUT) + (diff_value * vbr_diff_value);
                        }

                        //      if (sTemp_value < 10)
                        //      {
                        //        diff_value = 10 - sTemp_value;
                        //        set_boost_value = __swap_bytes(flashPtr->APD_TARGET_OUTPUT) - (diff_value * APD_VBR_DIFF_VALUE);
                        //      }
                        //      else if (sTemp_value > 54)
                        //      {
                        //        diff_value = sTemp_value - 54;
                        //        set_boost_value = __swap_bytes(flashPtr->APD_TARGET_OUTPUT) + (diff_value * APD_VBR_DIFF_VALUE);
                        //      }
                        //      else
                        //      {
                        //        diff_value = 0;
                        //        set_boost_value = __swap_bytes(flashPtr->APD_TARGET_OUTPUT) + (diff_value * APD_VBR_DIFF_VALUE);
                        //      }

                        unData = CalcExternalBoostTarget(set_boost_value);
                        APDIDX4 = IDX_TARGET; // Target Voltage
                        APDDAT4 = unData;
                        APDIDX4 = IDX_DUTY; // Target Voltage
                        flashPtr->APD_CURRENT_SETTING = __swap_bytes(unData);
                        flashPtr->APD_Vbr = __swap_bytes(set_boost_value);

                        if (lowerMemoryPtr->A2_TABLE == 0x81)
                        {
                                commomMemoryPtr->APD_CURRENT_SETTING = __swap_bytes(unData);
                                commomMemoryPtr->APD_Vbr = __swap_bytes(set_boost_value);
                        }
                }
        }

#endif

#else

        unsigned int set_boost_value = 0;
        unsigned int unData = 0;
        unsigned int diff_value, vbr_diff_value;
        signed int ref_temp_value;

        A2_PAGE_81H_MEMORY_MAP *flashPtr;
        A2_PAGE_80H_MEMORY_MAP *flashPtr_1;

        flashPtr = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P81H_Up[0];
        flashPtr_1 = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];

        ref_temp_value = __swap_bytes(flashPtr_1->nt_temp);
        ref_temp_value = ref_temp_value >> 8;

        vbr_diff_value = (unsigned int)(flashPtr->APD_VBR_DIFF);
        if (vbr_diff_value > 10)
        {
                vbr_diff_value = APD_VBR_DIFF_VALUE;
        }

        //  return;

        if ((flashPtr->PMIC_SELECT & APD_ENABLE) == APD_ENABLE) // if TEC is enabled?
        {
                if (~(APDCN4 & 0x0040))
                {
                        sTemp_value = sTemp_value >> 8; // get a truncated integer

                        if (sTemp_value < -40) //-40 is the minimum range
                        {
                                sTemp_value = -40;
                        }
                        if (sTemp_value > 104) // 104 is the maximum range
                        {
                                sTemp_value = 104;
                        }

                        if (sTemp_value > ref_temp_value)
                        {
                                diff_value = sTemp_value - ref_temp_value;
                                //        set_boost_value = __swap_bytes(flashPtr->APD_TARGET_OUTPUT) + (diff_value * APD_VBR_DIFF_VALUE);
                                set_boost_value = __swap_bytes(flashPtr->APD_TARGET_OUTPUT) + (diff_value * vbr_diff_value);
                        }
                        else if (sTemp_value < ref_temp_value)
                        {
                                diff_value = ref_temp_value - sTemp_value;
                                //        set_boost_value = __swap_bytes(flashPtr->APD_TARGET_OUTPUT) - (diff_value * APD_VBR_DIFF_VALUE);
                                set_boost_value = __swap_bytes(flashPtr->APD_TARGET_OUTPUT) - (diff_value * vbr_diff_value);
                        }
                        else
                        {
                                diff_value = 0;
                                //        set_boost_value = __swap_bytes(flashPtr->APD_TARGET_OUTPUT) + (diff_value * APD_VBR_DIFF_VALUE);
                                set_boost_value = __swap_bytes(flashPtr->APD_TARGET_OUTPUT) + (diff_value * vbr_diff_value);
                        }

                        //      if (sTemp_value < 10)
                        //      {
                        //        diff_value = 10 - sTemp_value;
                        //        set_boost_value = __swap_bytes(flashPtr->APD_TARGET_OUTPUT) - (diff_value * APD_VBR_DIFF_VALUE);
                        //      }
                        //      else if (sTemp_value > 54)
                        //      {
                        //        diff_value = sTemp_value - 54;
                        //        set_boost_value = __swap_bytes(flashPtr->APD_TARGET_OUTPUT) + (diff_value * APD_VBR_DIFF_VALUE);
                        //      }
                        //      else
                        //      {
                        //        diff_value = 0;
                        //        set_boost_value = __swap_bytes(flashPtr->APD_TARGET_OUTPUT) + (diff_value * APD_VBR_DIFF_VALUE);
                        //      }

                        unData = CalcExternalBoostTarget(set_boost_value);
                        APDIDX4 = IDX_TARGET; // Target Voltage
                        APDDAT4 = unData;
                        APDIDX4 = IDX_DUTY; // Target Voltage
                        flashPtr->APD_CURRENT_SETTING = __swap_bytes(unData);
                        flashPtr->APD_Vbr = __swap_bytes(set_boost_value);
                }
        }

#endif

#else

        unsigned int set_boost_value = 0;
        unsigned int unData = 0;
        unsigned int diff_value;

        A2_PAGE_81H_MEMORY_MAP *flashPtr;

        flashPtr = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P81H_Up[0];

        //  return;

        if ((flashPtr->PMIC_SELECT & APD_ENABLE) == APD_ENABLE) // if TEC is enabled?
        {
                if (~(APDCN4 & 0x0040))
                {
                        sTemp_value = sTemp_value >> 8; // get a truncated integer

                        if (sTemp_value < -40) //-40 is the minimum range
                        {
                                sTemp_value = -40;
                        }
                        if (sTemp_value > 104) // 104 is the maximum range
                        {
                                sTemp_value = 104;
                        }

                        if (sTemp_value < 10)
                        {
                                diff_value = 10 - sTemp_value;
                                set_boost_value = __swap_bytes(flashPtr->APD_TARGET_OUTPUT) - (diff_value * APD_VBR_DIFF_VALUE);
                        }
                        else if (sTemp_value > 54)
                        {
                                diff_value = sTemp_value - 54;
                                set_boost_value = __swap_bytes(flashPtr->APD_TARGET_OUTPUT) + (diff_value * APD_VBR_DIFF_VALUE);
                        }
                        else
                        {
                                diff_value = 0;
                                set_boost_value = __swap_bytes(flashPtr->APD_TARGET_OUTPUT) + (diff_value * APD_VBR_DIFF_VALUE);
                        }
                        unData = CalcExternalBoostTarget(set_boost_value);
                        APDIDX4 = IDX_TARGET; // Target Voltage
                        APDDAT4 = unData;
                        APDIDX4 = IDX_DUTY; // Target Voltage
                        flashPtr->APD_CURRENT_SETTING = __swap_bytes(unData);
                        flashPtr->APD_Vbr = __swap_bytes(set_boost_value);
                }
        }

#endif
}

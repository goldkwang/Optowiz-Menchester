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

#ifndef _INCLUDES_H_
#define _INCLUDES_H_

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------

#ifndef NDEBUG
#define DEBUG_MODE      0
#endif

#define VERSION_NUMBER  1
#define DEBUG_NUMBER    1

//#define DCDC_BIASING    

#define SC_FW_P2  

#ifndef __QSFP28_ER4__

#define __QSFP28_ER4__    0
#define __QSFP28_LR4__    0
#define __QSFP28_CWDM4__  0
#define __QSFP28_SR4__    0

#define __SFP28_ER__    1
#define __SFP28_ER_SEMI_TUNABLE__    1

#define __SFP_PLUS_3G_ER_SEMI_TUNABLE__    1

#define __SFP_PLUS_3G_10G_ER_SEMI_TUNABLE__ 0

#define __HSFP_10G_ER_SEMI_TUNABLE__    1

#define __HSFP_10G_MULTI_RATE_SEMI_TUNABLE__    1

#define __SFP_PLUS_3G_ER_SEMI_TUNABLE_SW_VER_2__    0
// __SFP_PLUS_3G_ER_SEMI_TUNABLE_SW_VER_2__ RSSI ���� ó���� �µ����� Interpolation ���� �����ϴ� ������� ����

#define __SFP_PLUS_3G_ER_SEMI_TUNABLE_HW_VER_2__    0
// __SFP_PLUS_3G_ER_SEMI_TUNABLE_HW_VER_2__ current mirror ����, RSSI���� DS4835 ADC23 �ɿ� ���� ������ 

// 2021.06.02. for SKT Spec. -->
// A0H, Reg 60 ~ 62�� �� ä���� �⺻ ������ ǥ�� �ϵ��� ������
#define __WAVELENGTH_LIKE_FIXED_VER__  1

#define __WAVELENGTH_LIKE_FIXED_VER_50PM__  1

#define __FIXED_MODE_SFP_VER__  1
#define __TUNABLE_MODE_SFP_VER__  0

#define __HFR_REQ_VER__ 1
#define __HFR_REQ_DDM_FLAG_VER__  1

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
//#define __WAVELENGTH_1410_VER__ 0
#define __WAVELENGTH_1530_VER__ 0
#define __WAVELENGTH_1550_VER__ 0


#define __RLASER_TRIM_11_OHM__ 0
#define __RLASER_TRIM_13_OHM__ 1
#define __RLASER_TRIM_18_OHM__ 0

#define __CCONST_ABSOLUTE_ADDRESS_DEF__ 0

#define __EXTERNAL_CALIBRATION_ENABLE_OPTIONS__ 0
#define __ADDITIONAL_ENHANCED_FEATURES_ENABLE__ 1

#define __PRBS_GEN_MODE_AT_TX_SIGNAL_LOS_LOL_ST__ 0

#define __TUNABLE_CH_UPDATE_VER_1__ 1
// VER_1: Group A, B: 1 ~ 4: �ش� ���� �;߸� ä�� ���� ������
//        Group C, D: 5 ~ 8

#endif

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include ".\Customized\i2cslave.h"
#include ".\Drivers\flash.h"
#include ".\Drivers\adc.h"
#include ".\Drivers\ds_dac.h"
#include ".\Drivers\dc_dc.h"
#include ".\Drivers\i2cm.h"
#include ".\Drivers\tec.h"
#include ".\Drivers\pwm.h"
#include ".\Drivers\timer.h"
//#include ".\LaserDriver\driver.h"
#include ".\Application\memory_access.h"
#include ".\Application\memory.h"
#include ".\Application\memory_map.h"
#include ".\Application\ddm.h"
#include ".\Application\board.h"
#include ".\Application\apc.h"
#include ".\Application\lut.h"
#include ".\Application\monitor.h"
#include ".\Application\state_machine.h"
#include ".\MSA\alarm_warning.h"

#include ".\Application\module_config.h"
#include ".\Application\state_transition.h"
#include ".\Application\rosa_control.h"
#include ".\Application\i2c_master_gpio.h"
#include ".\Application\drv_max5825.h"


#endif   //_INCLUDES_H_


//-----------------------------------------------------------------------------
// end of file
//-----------------------------------------------------------------------------


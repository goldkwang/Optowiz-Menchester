/*
 * tosa_control.c
 *
 *  Created on: 2019. 4. 29.
 *      Author: DongchoonLee
 */
#include <intrinsics.h>
#include <iods4835.h>

#include "includes.h"
#include <string.h>

//#define __WAVELENGTH_1290_VER__ 1
//#define __WAVELENGTH_1270_VER__ 0
//#define __WAVELENGTH_1330_VER__ 0
//#define __WAVELENGTH_1350_VER__ 0
//#define __WAVELENGTH_1410_VER__ 0
//#define __WAVELENGTH_1430_VER__ 0
//#define __WAVELENGTH_1450_VER__ 0
//#define __WAVELENGTH_1470_VER__ 0
//#define __WAVELENGTH_1490_VER__ 0
//#define __WAVELENGTH_1510_VER__ 0
//
//#define __RLASER_TRIM_11_OHM__ 0
//#define __RLASER_TRIM_13_OHM__ 1
//#define __RLASER_TRIM_18_OHM__ 0


#if __WAVELENGTH_ANY_VER__==1

#if __WAVELENGTH_LIKE_FIXED_VER__ == 1

#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1

#if __WAVELENGTH_LIKE_FIXED_VER_50PM__ == 1

unsigned int wavelength_info[3][4][4] = {
  { // 1411
    { 0x6DA6, 0x6DB7, 0x6DC7, 0x6DD8 },
    { 0x6DE8, 0x6DF9, 0x6E09, 0x6E1A },
    { 0x6E3B, 0x6E4C, 0x6E5C, 0x6E6D },
    { 0x6E7E, 0x6E8E, 0x6E9F, 0x6EB0 }    
  },
  { // 1531
    { 0x777F, 0x778F, 0x779E, 0x77AE },
    { 0x77BE, 0x77CD, 0x77DD, 0x77ED },
    { 0x780C, 0x781C, 0x782C, 0x783C },
    { 0x784B, 0x785B, 0x786B, 0x787B }
  },
  { // 1551
    { 0x78EA, 0x78FA, 0x790A, 0x791A },
    { 0x792A, 0x793A, 0x794A, 0x795B },
    { 0x797B, 0x798B, 0x799B, 0x79AB },
    { 0x79BB, 0x79CC, 0x79DC, 0x79EC }
  }
};

unsigned int wavelength_info_A0_60_61[3][4][4] = {
  { // 1411
    { 1401, 1402, 1403, 1404 },
    { 1405, 1406, 1407, 1408 },
    { 1411, 1412, 1413, 1414 },
    { 1415, 1416, 1417, 1418 }    
  },
  { // 1531
    { 1521, 1522, 1523, 1524 },
    { 1525, 1526, 1527, 1528 },
    { 1531, 1532, 1533, 1534 },
    { 1535, 1536, 1537, 1538 }    
  },
  { // 1551
    { 1541, 1542, 1543, 1544 },
    { 1545, 1546, 1547, 1548 },
    { 1551, 1552, 1553, 1554 },
    { 1555, 1556, 1557, 1558 }    
  }
};

#else

unsigned int wavelength_info[3][4][4] = {
  { // 1411
    { 1403, 1404, 1405, 1405 },
    { 1406, 1407, 1408, 1409 },
    { 1410, 1411, 1412, 1413 },
    { 1414, 1415, 1415, 1416 }    
  },
  { // 1531
    { 1529, 1530, 1531, 1531 },
    { 1532, 1533, 1534, 1535 },
    { 1536, 1537, 1538, 1538 },
    { 1539, 1540, 1541, 1542 }    
  },
  { // 1551
    { 1547, 1548, 1549, 1550 },
    { 1550, 1551, 1552, 1553 },
    { 1554, 1555, 1556, 1557 },
    { 1558, 1558, 1559, 1560 }    
  }
};


unsigned char wavelength_info_fraction[3][4][4] = {
  { // 1411
    { 52, 35, 17, 99 },
    { 82, 64, 47, 30 },
    { 95, 79, 62, 45 },
    { 28, 12, 95, 79 }    
  },
  { // 1531
    { 55, 33, 12, 90 },
    { 68, 47, 25, 4 },
    { 61, 40, 19, 98 },
    { 77, 56, 35, 14 }    
  },
  { // 1551
    { 72, 52, 32, 12 },
    { 92, 72, 52, 33 },
    { 94, 75, 56, 36 },
    { 17, 98, 79, 61 }    
  }
};

#endif

#else

unsigned int wavelength_info[10][4][4] = {
  { // 1271
    { 1263, 1264, 1265, 1266 },
    { 1267, 1267, 1268, 1269 },
    { 1271, 1271, 1272, 1273 },
    { 1274, 1275, 1275, 1276 }
  },
  {  // 1291
    { 1283, 1284, 1285, 1285 },
    { 1286, 1287, 1288, 1289 },
    { 1290, 1291, 1292, 1293 },
    { 1294, 1295, 1295, 1296 }
  },
  { // 1331
    { 1323, 1324, 1325, 1325 },
    { 1326, 1327, 1328, 1329 },
    { 1330, 1331, 1332, 1333 },
    { 1334, 1334, 1335, 1336 }    
  },
  { // 1351
    { 1343, 1343, 1344, 1345 },
    { 1346, 1347, 1348, 1348 },
    { 1350, 1351, 1352, 1353 },
    { 1353, 1354, 1355, 1356 }    
  },
  { // 1411
    { 1403, 1404, 1405, 1405 },
    { 1406, 1407, 1408, 1409 },
    { 1410, 1411, 1412, 1413 },
    { 1414, 1415, 1415, 1416 }    
  },
  { // 1431
    { 1423, 1424, 1425, 1426 },
    { 1426, 1427, 1428, 1429 },
    { 1431, 1432, 1432, 1433 },
    { 1434, 1435, 1436, 1437 }    
  },
  { // 1451
    { 1444, 1444, 1445, 1446 },
    { 1447, 1447, 1448, 1449 },
    { 1451, 1451, 1452, 1453 },
    { 1454, 1455, 1455, 1456 }    
  },
  { // 1471
    { 1463, 1464, 1465, 1466 },
    { 1467, 1467, 1468, 1469 },
    { 1471, 1471, 1472, 1473 },
    { 1474, 1475, 1475, 1476 }    
  },
  { // 1491
    { 1483, 1484, 1485, 1485 },
    { 1486, 1487, 1488, 1489 },
    { 1490, 1491, 1492, 1493 },
    { 1494, 1495, 1495, 1496 }    
  },
  { // 1511
    { 1503, 1504, 1505, 1506 },
    { 1506, 1507, 1508, 1509 },
    { 1511, 1512, 1512, 1513 },
    { 1514, 1515, 1516, 1517 }    
  }
};


unsigned char wavelength_info_fraction[10][4][4] = {
  { // 1271
    { 88, 68, 48, 28 },
    { 9, 89, 69, 50 },
    { 12, 92, 73, 55 },
    { 36, 17, 98, 80 }
  },
  {  // 1291
    { 36, 18, 1, 84 },
    { 66, 49, 32, 15 },
    { 82, 65, 49, 32 },
    { 16, 0, 84, 68 }
  },
  { // 1331
    { 51, 32, 12, 93 },
    { 74, 54, 35, 16 },
    { 78, 60, 41, 22 },
    { 4, 86, 68, 50 }    
  },
  { // 1351
    { 8, 91, 74, 57 },
    { 40, 23, 6, 90 },
    { 57, 41, 24, 8 },
    { 92, 77, 61, 45 }    
  },
  { // 1411
    { 52, 35, 17, 99 },
    { 82, 64, 47, 30 },
    { 95, 79, 62, 45 },
    { 28, 12, 95, 79 }    
  },
  { // 1431
    { 52, 36, 21, 6 },
    { 90, 75, 60, 46 },
    { 16, 2, 87, 73 },
    { 59, 44, 30, 16 }    
  },
  { // 1451
    { 0, 78, 57, 35 },
    { 14, 92, 71, 50 },
    { 8, 87, 66, 45 },
    { 24, 4, 83, 63 }    
  },
  { // 1471
    { 83, 64, 44, 25 },
    { 5, 86, 67, 48 },
    { 10, 92, 73, 54 },
    { 36, 18, 99, 81 }    
  },
  { // 1491
    { 39, 21, 4, 87 },
    { 70, 53, 36, 19 },
    { 86, 69, 53, 36 },
    { 20, 4, 88, 72 }    
  },
  { // 1511
    { 47, 32, 17, 2 },
    { 87, 73, 58, 43 },
    { 15, 0, 86, 72 },
    { 58, 44, 31, 17 }    
  }
};

#endif

#else

#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1

unsigned int wavelength_info[3][4][4] = {
  { // 1411
    { 0x6DA6, 0x6DB6, 0x6DC7, 0x6DD7 },
    { 0x6DE8, 0x6DF8, 0x6E09, 0x6E19 },
    { 0x6E3B, 0x6E4B, 0x6E5C, 0x6E6C },
    { 0x6E7D, 0x6E8E, 0x6E9F, 0x6EAF }    
  },
  { // 1531
    { 0x777F, 0x778E, 0x779E, 0x77AD },
    { 0x77BD, 0x77CD, 0x77DD, 0x77EC },
    { 0x780C, 0x781B, 0x782B, 0x783B },
    { 0x784B, 0x785B, 0x786A, 0x787A }
  },
  { // 1551
    { 0x78EA, 0x78FA, 0x790A, 0x791A },
    { 0x792A, 0x793A, 0x794A, 0x795A },
    { 0x797A, 0x798A, 0x799B, 0x79AB },
    { 0x79BB, 0x79CB, 0x79DB, 0x79EC }
  }
};


#else

unsigned int wavelength_info[10][4][4] = {
  { // 1271
    { 0x62BD, 0x62CD, 0x62DD, 0x62ED },
    { 0x62FD, 0x630D, 0x631D, 0x632E },
    { 0x634E, 0x635E, 0x636E, 0x637E },
    { 0x638F, 0x639F, 0x63AF, 0x63BF }
  },
  {  // 1291
    { 0x6443, 0x6453, 0x6464, 0x6474 },
    { 0x6485, 0x6495, 0x64A6, 0x64B7 },
    { 0x64D8, 0x64E9, 0x64F9, 0x650A },
    { 0x651B, 0x652C, 0x653C, 0x654D }
  },
  { // 1331
    { 0x6766, 0x6776, 0x6786, 0x6796 },
    { 0x67A6, 0x67B6, 0x67C7, 0x67D7 },
    { 0x67F7, 0x6807, 0x6818, 0x6828 },
    { 0x6838, 0x6849, 0x6859, 0x6869 }    
  },
  { // 1351
    { 0x68ED, 0x68FE, 0x690E, 0x691F },
    { 0x692F, 0x6940, 0x6951, 0x6961 },
    { 0x6983, 0x6994, 0x69A4, 0x69B5 },
    { 0x69C6, 0x69D7, 0x69E8, 0x69F9 }    
  },
  { // 1411
    { 0x6DA6, 0x6DB6, 0x6DC7, 0x6DD7 },
    { 0x6DE8, 0x6DF8, 0x6E09, 0x6E19 },
    { 0x6E3B, 0x6E4B, 0x6E5C, 0x6E6C },
    { 0x6E7D, 0x6E8E, 0x6E9F, 0x6EAF }    
  },
  { // 1431
    { 0x6F36, 0x6F47, 0x6F58, 0x6F69 },
    { 0x6F7A, 0x6F8B, 0x6F9C, 0x6FAD },
    { 0x6FCF, 0x6FE0, 0x6FF1, 0x7002 },
    { 0x7013, 0x7024, 0x7036, 0x7047 }    
  },
  { // 1451
    { 0x70D0, 0x70DF, 0x70EF, 0x70FF },
    { 0x710E, 0x711E, 0x712E, 0x713D },
    { 0x715D, 0x716D, 0x717D, 0x718D },
    { 0x719C, 0x71AC, 0x71BC, 0x71CC }    
  },
  { // 1471
    { 0x725C, 0x726C, 0x727C, 0x728C },
    { 0x729D, 0x72AD, 0x72BD, 0x72CD },
    { 0x72EE, 0x72FE, 0x730E, 0x731E },
    { 0x732F, 0x733F, 0x734F, 0x7360 }    
  },
  { // 1491
    { 0x73E3, 0x73F4, 0x7404, 0x7415 },
    { 0x7425, 0x7436, 0x7447, 0x7457 },
    { 0x7479, 0x7489, 0x749A, 0x74AB },
    { 0x74BC, 0x74CC, 0x74DD, 0x74EE }    
  },
  { // 1511
    { 0x7575, 0x7586, 0x7597, 0x75A8 },
    { 0x75B9, 0x75CA, 0x75DB, 0x75EC },
    { 0x760E, 0x7620, 0x7631, 0x7642 },
    { 0x7653, 0x7664, 0x7676, 0x7687 }    
  }
};

#endif

#endif

#elif __WAVELENGTH_1290_VER__==1

unsigned int wavelength_info[4][4] = {  
  { 0x6443, 0x6453, 0x6464, 0x6474 },
  { 0x6485, 0x6495, 0x64A6, 0x64B7 },
  { 0x64D8, 0x64E9, 0x64F9, 0x650A },
  { 0x651B, 0x652C, 0x653C, 0x654D }
};

#elif __WAVELENGTH_1270_VER__==1

unsigned int wavelength_info[4][4] = {  
  { 0x62BD, 0x62CD, 0x62DD, 0x62ED },
  { 0x62FD, 0x630D, 0x631D, 0x632E },
  { 0x634E, 0x635E, 0x636E, 0x637E },
  { 0x638F, 0x639F, 0x63AF, 0x63BF }
};

#elif __WAVELENGTH_1330_VER__==1

unsigned int wavelength_info[4][4] = {  
  { 0x6443, 0x6453, 0x6464, 0x6474 },
  { 0x6485, 0x6495, 0x64A6, 0x64B7 },
  { 0x64D8, 0x64E9, 0x64F9, 0x650A },
  { 0x651B, 0x652C, 0x653C, 0x654D }
};

#elif __WAVELENGTH_1350_VER__==1

unsigned int wavelength_info[4][4] = {  
  { 0x68ED, 0x68FE, 0x690E, 0x691F },
  { 0x692F, 0x6940, 0x6951, 0x6961 },
  { 0x6983, 0x6994, 0x69A4, 0x69B5 },
  { 0x69C6, 0x69D7, 0x69E8, 0x69F9 }
};

#elif __WAVELENGTH_1410_VER__==1
// 3G ST-SFP+ 1411 Wavelength�� ���� ���

unsigned int wavelength_info[4][4] = {  
  { 0x6DA6, 0x6DB6, 0x6DC7, 0x6DD7 },
  { 0x6DE8, 0x6DF8, 0x6E09, 0x6E19 },
  { 0x6E3B, 0x6E4B, 0x6E5C, 0x6E6C },
  { 0x6E7D, 0x6E8E, 0x6E9F, 0x6EAF }
};

#elif __WAVELENGTH_1430_VER__==1

unsigned int wavelength_info[4][4] = {  
  { 0x6F36, 0x6F47, 0x6F58, 0x6F69 },
  { 0x6F7A, 0x6F8B, 0x6F9C, 0x6FAD },
  { 0x6FCF, 0x6FE0, 0x6FF1, 0x7002 },
  { 0x7013, 0x7024, 0x7036, 0x7047 }
};

#elif __WAVELENGTH_1450_VER__==1

unsigned int wavelength_info[4][4] = {  
  { 0x70D0, 0x70DF, 0x70EF, 0x70FF },
  { 0x710E, 0x711E, 0x712E, 0x713D },
  { 0x715D, 0x716D, 0x717D, 0x718D },
  { 0x719C, 0x71AC, 0x71BC, 0x71CC }
};

#elif __WAVELENGTH_1470_VER__==1

unsigned int wavelength_info[4][4] = {  
  { 0x725C, 0x726C, 0x727C, 0x728C },
  { 0x729D, 0x72AD, 0x72BD, 0x72CD },
  { 0x72EE, 0x72FE, 0x730E, 0x731E },
  { 0x732F, 0x733F, 0x734F, 0x7360 }
};

#elif __WAVELENGTH_1490_VER__==1

unsigned int wavelength_info[4][4] = {  
  { 0x73E3, 0x73F4, 0x7404, 0x7415 },
  { 0x7425, 0x7436, 0x7447, 0x7457 },
  { 0x7479, 0x7489, 0x749A, 0x74AB },
  { 0x74BC, 0x74CC, 0x74DD, 0x74EE }
};

#elif __WAVELENGTH_1510_VER__==1

unsigned int wavelength_info[4][4] = {  
  { 0x7575, 0x7586, 0x7597, 0x75A8 },
  { 0x75B9, 0x75CA, 0x75DB, 0x75EC },
  { 0x760E, 0x7620, 0x7631, 0x7642 },
  { 0x7653, 0x7664, 0x7676, 0x7687 }
};

//#elif __WAVELENGTH_1410_VER__==1
//// 3G ST-SFP+ 1411 Wavelength
//
//unsigned int wavelength_info[4][4] = {  
//  { 0x6DA6, 0x6DB6, 0x6DC7, 0x6DD7 },
//  { 0x6DE8, 0x6DF8, 0x6E09, 0x6E19 },
//  { 0x6E3B, 0x6E4B, 0x6E5C, 0x6E6C },
//  { 0x6E7D, 0x6E8E, 0x6E9F, 0x6EAF }
//};

#elif __WAVELENGTH_1530_VER__==1
// 3G ST-SFP+ 1531 Wavelength

unsigned int wavelength_info[4][4] = {  
  { 0x777F, 0x778E, 0x779E, 0x77AD },
  { 0x77BD, 0x77CD, 0x77DD, 0x77EC },
  { 0x780C, 0x781B, 0x782B, 0x783B },
  { 0x784B, 0x785B, 0x786A, 0x787A }
};

#elif __WAVELENGTH_1550_VER__==1
// 3G ST-SFP+ 1551 Wavelength

unsigned int wavelength_info[4][4] = {  
  { 0x78EA, 0x78FA, 0x790A, 0x791A },
  { 0x792A, 0x793A, 0x794A, 0x795A },
  { 0x797A, 0x798A, 0x799B, 0x79AB },
  { 0x79BB, 0x79CB, 0x79DB, 0x79EC }
};

#endif

void Ld_Ch_seq_init(void)
{
//	bset_dac_ch_no[0][0]	= BSET_DAC_CH1;
//	mset_dac_ch_no[0][0]	= MSET_DAC_CH1;
//	cpa_dac_ch_no [0][0]	= CPA_DAC_CH1;
//
//	bset_dac_ch_no[0][1]	= BSET_DAC_CH2;
//	mset_dac_ch_no[0][1]	= MSET_DAC_CH2;
//	cpa_dac_ch_no [0][1]	= CPA_DAC_CH2;
//
//	bset_dac_ch_no[0][2]	= BSET_DAC_CH3;
//	mset_dac_ch_no[0][2]	= MSET_DAC_CH3;
//	cpa_dac_ch_no [0][2]	= CPA_DAC_CH3;
//
//	bset_dac_ch_no[0][3]	= BSET_DAC_CH4;
//	mset_dac_ch_no[0][3]	= MSET_DAC_CH4;
//	cpa_dac_ch_no [0][3]	= CPA_DAC_CH4;

  prevXconBiasDa = 0;
  prevModBiasDa = 0;
  prevLdBiasDa = 0;
  
}

void LdInit(void)
{
//	uint8_t idx;

	// Initialize LD Control variables		
        LdBiasSetFlag = 'T';
        
	// Modulation_bias_control(grpNo, chNo);

	// XCon_bias_control(grpNo, chNo);


}

void LdControl_manually(INT8U sigNo, INT8U chNo ){/*{{{*/
#if __SFP28_ER_SEMI_TUNABLE__ == 1
	unsigned int da;
//        unsigned int  rDa;
//        unsigned char sw_tx_dis, curr_sw_tx_dis;
	A2_PAGE_80H_MEMORY_MAP	* flashPtr;
	A2_PAGE_80H_MEMORY_MAP	* flashPtr_1;
        A2_LOWER_MEMORY_MAP * lowerMemoryPtr;
        
	flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
	flashPtr_1 = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_Pn_Up[0];
	lowerMemoryPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];
        
	da = forcedLdBiasSet;
       
	if( da > MAX_LD_BIAS_DA )
		da = MAX_LD_BIAS_DA;
	else if( da < 1 )
		da = 0;
        
        LdBiasDa = da;
//        rDa = LD_Drive_Get(CH_TYPE_BSET,0);
        
        if (LdBiasDa != prevLdBiasDa)
        {
          LD_Drive_Set(CH_TYPE_BSET, 0, LdBiasDa);
        }
//        else if (rDa != LdBiasDa)
//        {
//          LD_Drive_Set(CH_TYPE_BSET, 0, LdBiasDa);          
//        }
        prevLdBiasDa = LdBiasDa;

//		tmp_ptr = (uint16_t *)&I2C_Slave_Buffer_A0_P0_Up[(UPPER_MEMORY_PAGE0_LD_BIASn_DAC(chNo) & 0x7F)];
//		*tmp_ptr = LdBiasDa;
        
        
        flashPtr->forcedLdBiasSet = __swap_bytes(LdBiasDa);
        if (lowerMemoryPtr->A2_TABLE == 0x80)
        {
          flashPtr_1->forcedLdBiasSet = __swap_bytes(LdBiasDa);          
        }
  
#else
	signed int da;
//	flashStructType	xdata * flashPtr;
//	uint16_t xdata * tmp_ptr;
//
//	flashPtr = (flashStructType *)&I2C_Slave_Buffer_A4_Local_Memory[0];
        unsigned char sw_tx_dis, curr_sw_tx_dis;

	sw_tx_dis = FPGA_Read_byte(I2C_ADDR_A2, A2_STATUS_CONTROL_OFF, A2_LOW_PAGE);
        sw_tx_dis &= 0xC0;
        
	da = forcedLdBiasSet;

        if ((sw_tx_dis & 0xC0) != 0x00)
        {
          da = 0;
        }
       
	if( da > MAX_LD_BIAS_DA )
		da = MAX_LD_BIAS_DA;
	else if( da < 0 )
		da = 0;

	curr_sw_tx_dis = FPGA_Read_byte(I2C_ADDR_A2, A2_STATUS_CONTROL_OFF, A2_LOW_PAGE);
        curr_sw_tx_dis &= 0xC0;
        
        if (sw_tx_dis == curr_sw_tx_dis)
	{
		LdBiasDa = da;
		LD_Drive_Set(CH_TYPE_BSET, 0, LdBiasDa);
		prevLdBiasDa = LdBiasDa;

//		tmp_ptr = (uint16_t *)&I2C_Slave_Buffer_A0_P0_Up[(UPPER_MEMORY_PAGE0_LD_BIASn_DAC(chNo) & 0x7F)];
//		*tmp_ptr = LdBiasDa;
	}

#endif
        
}/*}}}*/

void LdControl_first_init( )
{
  LD_Drive_Set(CH_TYPE_BSET, 0, 0);
  LD_Drive_Set(CH_TYPE_MSET, 0, 0);
  LD_Drive_Set(CH_TYPE_CPA, 0, 0); 
}

void LdControl(INT8U sigNo, INT8U chNo )
{/*{{{*/
#if __SFP28_ER_SEMI_TUNABLE__ == 1
  
	uint8_t tmp_value;

//        return;

	tmp_value = I2C_Slave_Buffer_A2_P80H_Up[FLASH_LD_CONTROL_MODE];

	/* �ӽ������� �� ������ ����. ���� TEC��� �������� ��� �� ������ �����Ŵ */
//        detect_rx_los_from_cdr();
        
	if (LdBiasSetFlag == 'T')
	{
		if (tmp_value == 0) {
			LdControl_manually(0, 0);
			//*tmp_ptr1 = sfp28_module_debug_run_state;
		} else if (tmp_value == 1) {
			LdControl_APC_3(0, 0);
//			*tmp_ptr1 = sfp28_module_debug_run_state;
		}
	}

        if (tmp_value == 0) {
          
//          detect_rx_los_from_cdr();
          ModBiasControl_manually(0, 0);
          
//          detect_rx_los_from_cdr();
          XconBiasControl(0, 0);
        }
        else
        {
//  detect_rx_los_from_cdr();
          ModBiasControl_APC_3(0, 0);
          
//  detect_rx_los_from_cdr();
          XconBiasControl(0, 0);
//          XconBiasControl_APC_3(0, 0);
//  detect_rx_los_from_cdr();
          TEC_Control_APC_3(0, 0);
//  detect_rx_los_from_cdr();
        }

#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
        
#else
        LD_Drive_Set(CH_TYPE_STROBE, 0, 1);
#endif
        
	LdBiasSetFlag = 'T';

#else
  

//	INT8U	xdata TX_DISABLE;
//	flashStructType	xdata * flashPtr;
//	uint16_t xdata * tmp_ptr, * tmp_ptr1;
	uint8_t tmp_value;

//	flashPtr = (flashStructType *)&I2C_Slave_Buffer_A4_Local_Memory[0];

	tmp_value = I2C_Slave_Buffer_A2_P80H_Up[FLASH_LD_CONTROL_MODE];

	/* �ӽ������� �� ������ ����. ���� TEC��� �������� ��� �� ������ �����Ŵ */
	if (LdBiasSetFlag == 'T')
	{
		if (tmp_value == 0) {
			LdControl_manually(0, 0);
			//*tmp_ptr1 = sfp28_module_debug_run_state;
		} else if (tmp_value == 1) {
//			LdControl_APC_3(0, 0);
//			*tmp_ptr1 = sfp28_module_debug_run_state;
		}
	}


	ModBiasControl_manually(0, 0);

	XconBiasControl(0, 0);

	LdBiasSetFlag = 'T';
#endif
        
}/*}}}*/


void LdControl_APC_3(INT8U sigNo, INT8U chNo )
{/*{{{*/ // maintain a Tx Power
#if __SFP28_ER_SEMI_TUNABLE__ == 1
  
	signed int xdata da, diff, offset_value, offset_value_1;
	signed int xdata div_value, m_div_value;
	A2_PAGE_80H_MEMORY_MAP	* flashPtr;
//	A2_PAGE_81H_MEMORY_MAP	* flashPtr_1;
//        A2_LOWER_MEMORY_MAP * lowerMemoryPtr;
//	signed int xdata * tmp_ptr;
	signed char	xdata t_chNo;
        signed char  curr_temp, reference_temp, ht_temp, lt_temp, ddm_curr_temp;
//        unsigned int rDa;
	A2_PAGE_80H_MEMORY_MAP	* flashPtr_1;
        A2_LOWER_MEMORY_MAP * lowerMemoryPtr;
        
	flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
	flashPtr_1 = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_Pn_Up[0];
	lowerMemoryPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];
        
//	flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
//	flashPtr_1 = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P81H_Up[0];
//        lowerMemoryPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];

        
        ddm_curr_temp = (signed char)I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_TEMPERATURE];
        reference_temp = (signed char)I2C_Slave_Buffer_A2_P80H_Up[FLASH_NT_TEMP];
        ht_temp = (signed char)I2C_Slave_Buffer_A2_P80H_Up[FLASH_HT_TEMP];
        lt_temp = (signed char)I2C_Slave_Buffer_A2_P80H_Up[FLASH_LT_TEMP];
        curr_temp = (signed char)I2C_Slave_Buffer_A2_P80H_Up[FLASH_RAW_CURRENT_TEMP];
//	t_chNo = (uint16_t)curr_channel_no - 1;
//        if ((curr_channel_no >= 1) && (curr_channel_no <= 4))
        if ((curr_channel_no >= 1) && (curr_channel_no <= 8))
        {
//          t_chNo = curr_channel_no - 1;
          t_chNo = (curr_channel_no - 1)%4;
        }
        else
        {
          t_chNo = 0; // curr_channel_no = 1
        }        
        
        if (curr_temp > reference_temp)
        {
          // High Temp. Control
          div_value = __swap_bytes(flashPtr->ht_LdBiasSet[t_chNo]) - __swap_bytes(flashPtr->nt_LdBiasSet[t_chNo]);
          div_value = (div_value * 100) / (ht_temp - reference_temp);
        }
        else
        {
          // Low Temp. Control
          m_div_value = __swap_bytes(flashPtr->nt_LdBiasSet[t_chNo]) - __swap_bytes(flashPtr->lt_LdBiasSet[t_chNo]);
          m_div_value = (m_div_value * 100) / (reference_temp - lt_temp);
          
        }

	da = (unsigned int)__swap_bytes(flashPtr->nt_LdBiasSet[t_chNo]);

	diff = (signed char)(curr_temp - reference_temp);

	if (diff < 0) {
		diff = (-1) * diff;

                offset_value_1 = (diff * m_div_value);
                if (offset_value_1 < 0)
                {
                  offset_value_1 = offset_value_1 - 50;
                }
                else
                {
                  offset_value_1 = offset_value_1 + 50;
                }
                
                offset_value = offset_value_1 / 100;
                da = da - offset_value;
	}
	else {
		offset_value = (diff * div_value)/100;

                offset_value_1 = (diff * div_value);
                if (offset_value_1 < 0)
                {
                  offset_value_1 = offset_value_1 - 50;
                }
                else
                {
                  offset_value_1 = offset_value_1 + 50;
                }
                
                offset_value = offset_value_1 / 100;
		da = da + offset_value;
	}
        
        // [DCLEE] 2020.08.19. ���� 80, -15 �� �����Ͽ� ����/���� ������ ���� ��Ŀ��� ��� tracing �ϴ� �������� ��ȯ
        if (ddm_curr_temp > HIGH_TEMP_THRESHOLD)
        {
//          da = (unsigned int)__swap_bytes(flashPtr->ht_LdBiasSet[t_chNo]);
        }
        else if (ddm_curr_temp < LOW_TEMP_THRESHOLD)
        {
//          da = (unsigned int)__swap_bytes(flashPtr->lt_LdBiasSet[t_chNo]);
          
        }

	if( da > MAX_LD_BIAS_DA )
		da = MAX_LD_BIAS_DA;
	else if( da < MIN_LD_BIAS_DA )
		da = MIN_LD_BIAS_DA;
	else if( da < 1 )
		da = 0;

	
        LdBiasDa = da;
//        rDa = LD_Drive_Get(CH_TYPE_BSET,bset_dac_ch_no);
        
        if (LdBiasDa != prevLdBiasDa)
        {
          LD_Drive_Set(CH_TYPE_BSET, bset_dac_ch_no, LdBiasDa);
        }
//        else if (rDa != LdBiasDa)
//        {
//          LD_Drive_Set(CH_TYPE_BSET, bset_dac_ch_no, LdBiasDa);          
//        }
        
//        if (LdBiasDa != prevLdBiasDa)
//        {
//          LD_Drive_Set(CH_TYPE_BSET, bset_dac_ch_no, LdBiasDa );
//        }
        prevLdBiasDa = LdBiasDa;

//        tmp_ptr = (signed int *)&I2C_Slave_Buffer_A0_P0_Up[(UPPER_MEMORY_PAGE0_LD_BIASn_DAC(chNo) & 0x7F)];
//        *tmp_ptr = __swap_bytes(LdBiasDa);
        flashPtr->forcedLdBiasSet = __swap_bytes(LdBiasDa);
        if (lowerMemoryPtr->A2_TABLE == 0x80)
        {
          flashPtr_1->forcedLdBiasSet = __swap_bytes(LdBiasDa);          
        }

  
#else
  
	signed int xdata da, diff, offset_value, offset_value_1;
//	signed int xdata curr_pwr, target_pwr;
	signed char xdata div_value, m_div_value;
	flashStructType	xdata * flashPtr;
	signed int xdata * tmp_ptr;
//	signed char xdata * tmp_ptr3;
	signed char	xdata t_chNo;
//	uint16_t	xdata div_value1, div_value2, div_value3;
//	uint16_t	xdata m_div_value1, m_div_value2, m_div_value3;
        signed char  curr_temp, reference_temp, ht_temp, lt_temp;
//        signed int daa;
        
//        LOWER_MEMORY_MAP * xdata lowerMemoryMapPtr;
        
//	lowerMemoryMapPtr = (LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A0[0];
	flashPtr = (flashStructType *)&I2C_Slave_Buffer_A4_Local_Memory[0];


//        curr_temp = __swap_bytes(lowerMemoryMapPtr->TEMPERATURE);
//        curr_temp = (curr_temp >> 8) & 0xFFFF;
//        
//        reference_temp = __swap_bytes(flashPtr->tosa_global_temp);
//        reference_temp = (reference_temp >> 8) & 0xFFFF;
        
        curr_temp = (signed char)I2C_Slave_Buffer_A0[QSFP_LOWER_MEMORY_TEMPERATURE];
        reference_temp = (signed char)I2C_Slave_Buffer_A4_Local_Memory[FLASH_NT_TEMP];
        ht_temp = (signed char)I2C_Slave_Buffer_A4_Local_Memory[FLASH_HT_TEMP];
        lt_temp = (signed char)I2C_Slave_Buffer_A4_Local_Memory[FLASH_LT_TEMP];
        
	t_chNo = (uint16_t)chNo;
        
        if (curr_temp > reference_temp)
        {
          // High Temp. Control
          div_value = flashPtr->ht_LdBiasSet[0][t_chNo] - flashPtr->nt_LdBiasSet[0][t_chNo];
          div_value = (div_value * 100) / (ht_temp - reference_temp);
        }
        else
        {
          // Low Temp. Control
          m_div_value = flashPtr->nt_LdBiasSet[0][t_chNo] - flashPtr->lt_LdBiasSet[0][t_chNo];
          m_div_value = (m_div_value * 100) / (reference_temp - lt_temp);
          
        }

//	da = __swap_bytes(flashPtr->forcedLdBiasSet[0][t_chNo]);
	da = (unsigned int)flashPtr->nt_LdBiasSet[0][t_chNo];

	// da = LdBiasDa[0][t_chNo];

//	diff = target_value - monitor_value;
	diff = (signed char)(curr_temp - reference_temp);

	if (diff < 0) {
		diff = (-1) * diff;
//		offset_value = (diff * m_div_value)/100;

//                round_value = (diff * m_div_value)%100;
//                if (round_value > 49)
//                {
//                  da = da - offset_value - 1;
//                }
//                else
//                {
//                  da = da - offset_value;
//                }

                offset_value_1 = (diff * m_div_value);
                if (offset_value_1 < 0)
                {
                  offset_value_1 = offset_value_1 - 50;
                }
                else
                {
                  offset_value_1 = offset_value_1 + 50;
                }
                
                offset_value = offset_value_1 / 100;
                da = da - offset_value;
	}
	else {
		offset_value = (diff * div_value)/100;

//                round_value = (diff * div_value)%100;
//                if (round_value > 49)
//                {
//                  da = da + offset_value + 1;
//                }
//                else
//                {
//                  da = da + offset_value;
//                }
                offset_value_1 = (diff * div_value);
                if (offset_value_1 < 0)
                {
                  offset_value_1 = offset_value_1 - 50;
                }
                else
                {
                  offset_value_1 = offset_value_1 + 50;
                }
                
                offset_value = offset_value_1 / 100;
		da = da + offset_value;
	}

	if( da > MAX_LD_BIAS_DA )
		da = MAX_LD_BIAS_DA;
	else if( da < MIN_LD_BIAS_DA )
		da = MIN_LD_BIAS_DA;
	else if( da < 0 )
		da = 0;

	// if (da != (INT16S)LdBiasDa[sigNo][chNo])
	{
		LdBiasDa[0][t_chNo] = da;
                		
//                daa = (signed int)(LD_Drive_Get(CH_TYPE_BSET, bset_dac_ch_no[0][t_chNo]));
//                if (da != daa) {		
//                  LD_Drive_Set(CH_TYPE_BSET, bset_dac_ch_no[0][t_chNo], LdBiasDa[0][t_chNo] );
//                }
                  LD_Drive_Set(CH_TYPE_BSET, bset_dac_ch_no[0][t_chNo], LdBiasDa[0][t_chNo] );
		prevLdBiasDa[0][t_chNo] = LdBiasDa[0][t_chNo];

		tmp_ptr = (signed int *)&I2C_Slave_Buffer_A0_P0_Up[(UPPER_MEMORY_PAGE0_LD_BIASn_DAC(chNo) & 0x7F)];
		*tmp_ptr = __swap_bytes(LdBiasDa[0][t_chNo]);
	}
//	*tmp_ptr1 = qsfp_module_debug_run_state;
//	flashPtr->tosa_diff_value_ref = div_value;
        
//	flashPtr->tosa_diff_value_ref = offset_value;
        
#endif

}/*}}}*/

//------------------------------------------------------------------------------------
// MOD Bias Control
//------------------------------------------------------------------------------------
// #define MAX_MOD_BIAS_DA				3450
// #define MAX_MOD_BIAS_DA				4095
// #define MAX_MOD_BIAS_DA				669 /* 400 mV */

void ModBiasControl_manually( INT8U sigNo, INT8U chNo ){/*{{{*/
#if __SFP28_ER_SEMI_TUNABLE__ == 1
  
        unsigned int  da;
//        unsigned char sw_tx_dis, curr_sw_tx_dis;
	A2_PAGE_80H_MEMORY_MAP	* flashPtr;
//	flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
	A2_PAGE_80H_MEMORY_MAP	* flashPtr_1;
        A2_LOWER_MEMORY_MAP * lowerMemoryPtr;
        
	flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
	flashPtr_1 = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_Pn_Up[0];
	lowerMemoryPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];

        if (ModBiasSet == 0xFFFF)
                ModBiasSet = 0;

        da = ModBiasSet;
     
        if (da > MAX_MOD_BIAS_DA)
        {
		ModBiasDa = MAX_MOD_BIAS_DA;
        }
        else
        {
		ModBiasDa = da;
          
        }
                
//        rDa = LD_Drive_Get(CH_TYPE_MSET,0);
        
        if (ModBiasDa != prevModBiasDa)
        {
          LD_Drive_Set(CH_TYPE_MSET, 0, ModBiasDa);
        }
//        else if (rDa != ModBiasDa)
//        {
//          LD_Drive_Set(CH_TYPE_MSET, 0, ModBiasDa);          
//        }

//        if (prevModBiasDa != ModBiasDa)
//        {
//          LD_Drive_Set( CH_TYPE_MSET, 0, ModBiasDa);
//        }
        prevModBiasDa = ModBiasDa;
        
        flashPtr->ModBiasSet = __swap_bytes(ModBiasDa);
        if (lowerMemoryPtr->A2_TABLE == 0x80)
        {
          flashPtr_1->ModBiasSet = __swap_bytes(ModBiasDa);          
        }
        
  
#else
  
        unsigned int  da;
        unsigned char sw_tx_dis, curr_sw_tx_dis;

	sw_tx_dis = FPGA_Read_byte(I2C_ADDR_A2, A2_STATUS_CONTROL_OFF, A2_LOW_PAGE);
        sw_tx_dis &= 0xC0;

        if (ModBiasSet == 0xFFFF)
                ModBiasSet = 0;

        da = ModBiasSet;

        if ((sw_tx_dis & 0xC0) != 0x00)
        {
          da = 0;
        }
      
        if (da > MAX_MOD_BIAS_DA)
        {
		ModBiasDa = MAX_MOD_BIAS_DA;
        }
        else
        {
		ModBiasDa = da;
          
        }
                

#if	__DEBUG__
		/*
		 * sprintf(tmpStr, "MOD_BIAS = %d %d\n", ModBiasDa, ModBiasSet);
		 * write(0, tmpStr, 0);
		 */
#endif
	curr_sw_tx_dis = FPGA_Read_byte(I2C_ADDR_A2, A2_STATUS_CONTROL_OFF, A2_LOW_PAGE);
        curr_sw_tx_dis &= 0xC0;
        
	// if (da != (INT16S)LdBiasDa[sigNo][chNo])
        if (sw_tx_dis == curr_sw_tx_dis)
	{
		LD_Drive_Set( CH_TYPE_MSET, 0, ModBiasDa);
        }
        
#endif
        
}/*}}}*/


void ModBiasControl_APC_3(INT8U sigNo, INT8U chNo )
{/*{{{*/ // maintain a Tx Power
#if __SFP28_ER_SEMI_TUNABLE__ == 1
  
	signed int xdata diff, offset_value, offset_value_1;
	signed int xdata div_value, m_div_value;
	A2_PAGE_80H_MEMORY_MAP	* flashPtr;
//	A2_PAGE_81H_MEMORY_MAP	* flashPtr_1;
//        A2_LOWER_MEMORY_MAP * lowerMemoryPtr;
//	signed int xdata * tmp_ptr;
	signed char	xdata t_chNo;
        signed char  curr_temp, reference_temp, ht_temp, lt_temp, ddm_curr_temp;
        unsigned int  da;
	A2_PAGE_80H_MEMORY_MAP	* flashPtr_1;
        A2_LOWER_MEMORY_MAP * lowerMemoryPtr;
        
	flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
	flashPtr_1 = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_Pn_Up[0];
	lowerMemoryPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];
        
//	flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
//	flashPtr_1 = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P81H_Up[0];
//        lowerMemoryPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];

        
        ddm_curr_temp = (signed char)I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_TEMPERATURE];
        reference_temp = (signed char)I2C_Slave_Buffer_A2_P80H_Up[FLASH_NT_TEMP];
        ht_temp = (signed char)I2C_Slave_Buffer_A2_P80H_Up[FLASH_HT_TEMP];
        lt_temp = (signed char)I2C_Slave_Buffer_A2_P80H_Up[FLASH_LT_TEMP];
        curr_temp = (signed char)I2C_Slave_Buffer_A2_P80H_Up[FLASH_RAW_CURRENT_TEMP];

//	t_chNo = (uint16_t)curr_channel_no - 1;
//        if ((curr_channel_no >= 1) && (curr_channel_no <= 4))
        if ((curr_channel_no >= 1) && (curr_channel_no <= 8))
        {
//          t_chNo = curr_channel_no - 1;
          t_chNo = (curr_channel_no - 1)%4;
        }
        else
        {
          t_chNo = 0; // curr_channel_no = 1
        }        
                
        if (curr_temp > reference_temp)
        {
          // High Temp. Control
          div_value = __swap_bytes(flashPtr->ht_ModBiasSet[t_chNo]) - __swap_bytes(flashPtr->nt_ModBiasSet[t_chNo]);
          div_value = (div_value * 100) / (ht_temp - reference_temp);
        }
        else
        {
          // Low Temp. Control
          m_div_value = __swap_bytes(flashPtr->nt_ModBiasSet[t_chNo]) - __swap_bytes(flashPtr->lt_ModBiasSet[t_chNo]);
          m_div_value = (m_div_value * 100) / (reference_temp - lt_temp);
          
        }

//	da = __swap_bytes(flashPtr->ModBiasSet[0][t_chNo]);
	da = (unsigned int)__swap_bytes(flashPtr->nt_ModBiasSet[t_chNo]);

	diff = (signed char)(curr_temp - reference_temp);

	if (diff < 0) {
		diff = (-1) * diff;
                offset_value_1 = (diff * m_div_value);
                if (offset_value_1 < 0)
                {
                  offset_value_1 = offset_value_1 - 50;
                }
                else
                {
                  offset_value_1 = offset_value_1 + 50;
                }
                
                offset_value = offset_value_1 / 100;
		da = da - offset_value;
	}
	else {
                offset_value_1 = (diff * div_value);
                if (offset_value_1 < 0)
                {
                  offset_value_1 = offset_value_1 - 50;
                }
                else
                {
                  offset_value_1 = offset_value_1 + 50;
                }
                
                offset_value = offset_value_1 / 100;
		da = da + offset_value;
	}
        
        // [DCLEE] 2020.08.19. ���� 80, -15 �� �����Ͽ� ����/���� ������ ���� ��Ŀ��� ��� tracing �ϴ� �������� ��ȯ
        if (ddm_curr_temp > HIGH_TEMP_THRESHOLD)
        {
//          da = (unsigned int)__swap_bytes(flashPtr->ht_ModBiasSet[t_chNo]);
        }
        else if (ddm_curr_temp < LOW_TEMP_THRESHOLD)
        {
//          da = (unsigned int)__swap_bytes(flashPtr->lt_ModBiasSet[t_chNo]);
          
        }

	if( da > MAX_MOD_BIAS_DA )
		da = MAX_MOD_BIAS_DA;
	else if( da < 1 )
		da = 0;

	
        ModBiasDa = da;
        
//        rDa = LD_Drive_Get(CH_TYPE_MSET,0);
        
        if (ModBiasDa != prevModBiasDa)
        {
          LD_Drive_Set(CH_TYPE_MSET, 0, ModBiasDa);
        }
//        else if (rDa != ModBiasDa)
//        {
//          LD_Drive_Set(CH_TYPE_MSET, 0, ModBiasDa);          
//        }

//        if (prevModBiasDa != ModBiasDa)
//        {
//          LD_Drive_Set( CH_TYPE_MSET, 0, ModBiasDa);
//        }
        prevModBiasDa = ModBiasDa;
        flashPtr->ModBiasSet = __swap_bytes(ModBiasDa);
        if (lowerMemoryPtr->A2_TABLE == 0x80)
        {
          flashPtr_1->ModBiasSet = __swap_bytes(ModBiasDa);          
        }
        
//        LD_Drive_Set( CH_TYPE_MSET, mset_dac_ch_no, ModBiasDa );
                
	
  
#else
  
  
	signed int xdata da, diff, offset_value, offset_value_1;
//	signed int xdata curr_pwr, target_pwr;
	signed char xdata div_value, m_div_value;
	flashStructType	xdata * flashPtr;
//	signed int xdata * tmp_ptr, * tmp_ptr1, * tmp_ptr2;
//	signed char xdata * tmp_ptr3;
	signed char	xdata t_chNo;
//	uint16_t	xdata div_value1, div_value2, div_value3;
//	uint16_t	xdata m_div_value1, m_div_value2, m_div_value3;
        signed char  curr_temp, reference_temp, ht_temp, lt_temp;
//        unsigned int  daa;
        
//        LOWER_MEMORY_MAP * xdata lowerMemoryMapPtr;
        
//	lowerMemoryMapPtr = (LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A0[0];
	flashPtr = (flashStructType *)&I2C_Slave_Buffer_A4_Local_Memory[0];


//        curr_temp = __swap_bytes(lowerMemoryMapPtr->TEMPERATURE);
//        curr_temp = (curr_temp >> 8) & 0xFFFF;
//        
//        reference_temp = __swap_bytes(flashPtr->tosa_global_temp);
//        reference_temp = (reference_temp >> 8) & 0xFFFF;
        
        curr_temp = (signed char)I2C_Slave_Buffer_A0[QSFP_LOWER_MEMORY_TEMPERATURE];
        reference_temp = (signed char)I2C_Slave_Buffer_A4_Local_Memory[FLASH_NT_TEMP];
        ht_temp = (signed char)I2C_Slave_Buffer_A4_Local_Memory[FLASH_HT_TEMP];
        lt_temp = (signed char)I2C_Slave_Buffer_A4_Local_Memory[FLASH_LT_TEMP];
        
	t_chNo = (uint16_t)chNo;
        
        if (curr_temp > reference_temp)
        {
          // High Temp. Control
          div_value = flashPtr->ht_ModBiasSet[0][t_chNo] - flashPtr->nt_ModBiasSet[0][t_chNo];
          div_value = (div_value * 100) / (ht_temp - reference_temp);
        }
        else
        {
          // Low Temp. Control
          m_div_value = flashPtr->nt_ModBiasSet[0][t_chNo] - flashPtr->lt_ModBiasSet[0][t_chNo];
          m_div_value = (m_div_value * 100) / (reference_temp - lt_temp);
          
        }

//	da = __swap_bytes(flashPtr->ModBiasSet[0][t_chNo]);
	da = (unsigned int)flashPtr->nt_ModBiasSet[0][t_chNo];

	// da = LdBiasDa[0][t_chNo];

//	diff = target_value - monitor_value;
	diff = (signed char)(curr_temp - reference_temp);

	if (diff < 0) {
		diff = (-1) * diff;
//		offset_value = (diff * m_div_value)/100;
                offset_value_1 = (diff * m_div_value);
                if (offset_value_1 < 0)
                {
                  offset_value_1 = offset_value_1 - 50;
                }
                else
                {
                  offset_value_1 = offset_value_1 + 50;
                }
                
                offset_value = offset_value_1 / 100;
		da = da - offset_value;
	}
	else {
//		offset_value = (diff * div_value)/100;
                offset_value_1 = (diff * div_value);
                if (offset_value_1 < 0)
                {
                  offset_value_1 = offset_value_1 - 50;
                }
                else
                {
                  offset_value_1 = offset_value_1 + 50;
                }
                
                offset_value = offset_value_1 / 100;
		da = da + offset_value;
	}

	if( da > MAX_MOD_BIAS_DA )
		da = MAX_MOD_BIAS_DA;
	else if( da < 0 )
		da = 0;

	// if (da != (INT16S)LdBiasDa[sigNo][chNo])
	{
		ModBiasDa[0][t_chNo] = da;
//                daa = (unsigned int)(LD_Drive_Get(CH_TYPE_MSET, mset_dac_ch_no[sigNo][chNo]));
//                if (ModBiasDa[sigNo][chNo] != daa) {		
//                  LD_Drive_Set( CH_TYPE_MSET, mset_dac_ch_no[sigNo][chNo], ModBiasDa[sigNo][chNo] );
//                }
                  LD_Drive_Set( CH_TYPE_MSET, mset_dac_ch_no[sigNo][chNo], ModBiasDa[sigNo][chNo] );
                
//		LD_Drive_Set(CH_TYPE_CPA, cpa_dac_ch_no[0][t_chNo], XconBiasDa[0][t_chNo] );
//		prevLdBiasDa[0][t_chNo] = LdBiasDa[0][t_chNo];

//		tmp_ptr = (uint16_t *)&I2C_Slave_Buffer_A0_P0_Up[(UPPER_MEMORY_PAGE0_LD_BIASn_DAC(chNo) & 0x7F)];
//		*tmp_ptr = __swap_bytes(LdBiasDa[0][t_chNo]);
	}
//	*tmp_ptr1 = qsfp_module_debug_run_state;
//	flashPtr->tosa_diff_value_ref = div_value;
        
//	flashPtr->tosa_diff_value_ref = offset_value;
        
#endif
        
}/*}}}*/

//------------------------------------------------------------------------------------
// Cross Control
//------------------------------------------------------------------------------------
// #define MAX_Xcon_DA			3071
// #define MAX_Xcon_DA			4095

void XconBiasControl( INT8U sigNo, INT8U chNo ){/*{{{*/
#if __SFP28_ER_SEMI_TUNABLE__ == 1
        unsigned int  da;
	A2_PAGE_80H_MEMORY_MAP	* flashPtr;
	A2_PAGE_80H_MEMORY_MAP	* flashPtr_1;
        A2_LOWER_MEMORY_MAP * lowerMemoryPtr;
        
	flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
	flashPtr_1 = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_Pn_Up[0];
	lowerMemoryPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];

	if( XconBiasSet == 0xFFFF )
		XconBiasSet = 0;
	da = XconBiasSet;


        if( da > MAX_Xcon_DA )
        {
                XconBiasDa = MAX_Xcon_DA;
        }
        else
        {
                XconBiasDa = da;
         }

//        rDa = LD_Drive_Get(CH_TYPE_CPA,0);
        
        if (XconBiasDa != prevXconBiasDa)
        {
          LD_Drive_Set(CH_TYPE_CPA, 0, XconBiasDa);
        }
//        else if (rDa != XconBiasDa)
//        {
//          LD_Drive_Set(CH_TYPE_CPA, 0, XconBiasDa);          
//        }

//        if (prevXconBiasDa != XconBiasDa)
//        {
//          LD_Drive_Set( CH_TYPE_CPA, 0, XconBiasDa);
//        }
        prevXconBiasDa = XconBiasDa;
        
//        LD_Drive_Set( CH_TYPE_CPA, 0, XconBiasDa);
        flashPtr->XconBiasSet = __swap_bytes(XconBiasDa);
        if (lowerMemoryPtr->A2_TABLE == 0x80)
        {
          flashPtr_1->XconBiasSet = __swap_bytes(XconBiasDa);          
        }
        

#else  
        unsigned int  da;
        unsigned char sw_tx_dis, curr_sw_tx_dis;

	sw_tx_dis = FPGA_Read_byte(I2C_ADDR_A2, A2_STATUS_CONTROL_OFF, A2_LOW_PAGE);
        sw_tx_dis &= 0xC0;

	if( XconBiasSet == 0xFFFF )
		XconBiasSet = 0;
	da = XconBiasSet;

        if ((sw_tx_dis & 0xC0) != 0x00)
        {
          da = 0;
        }

        if( da > MAX_Xcon_DA )
        {
                XconBiasDa = MAX_Xcon_DA;
        }
        else
        {
                XconBiasDa = da;
         }

        
	curr_sw_tx_dis = FPGA_Read_byte(I2C_ADDR_A2, A2_STATUS_CONTROL_OFF, A2_LOW_PAGE);
        curr_sw_tx_dis &= 0xC0;
        
        if (sw_tx_dis == curr_sw_tx_dis)
	{
          LD_Drive_Set( CH_TYPE_CPA, 0, XconBiasDa);
        }
        
#endif
        
}/*}}}*/


void XconBiasControl_APC_3(INT8U sigNo, INT8U chNo )
{/*{{{*/ // maintain a Tx Power
#if __SFP28_ER_SEMI_TUNABLE__ == 1
  
	signed int xdata da, diff, offset_value, offset_value_1;
	signed int xdata div_value, m_div_value;
	A2_PAGE_80H_MEMORY_MAP	* flashPtr;
//	A2_PAGE_81H_MEMORY_MAP	* flashPtr_1;
//        A2_LOWER_MEMORY_MAP * lowerMemoryPtr;
//	signed int xdata * tmp_ptr;
	signed char	xdata t_chNo;
        signed char  curr_temp, reference_temp, ht_temp, lt_temp, ddm_curr_temp;
//        unsigned int  rDa;
	A2_PAGE_80H_MEMORY_MAP	* flashPtr_1;
        A2_LOWER_MEMORY_MAP * lowerMemoryPtr;
        
	flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
	flashPtr_1 = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_Pn_Up[0];
	lowerMemoryPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];
        
//	flashPtr = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
//	flashPtr_1 = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P81H_Up[0];
//        lowerMemoryPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];

        
        ddm_curr_temp = (signed char)I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_TEMPERATURE];
        reference_temp = (signed char)I2C_Slave_Buffer_A2_P80H_Up[FLASH_NT_TEMP];
        ht_temp = (signed char)I2C_Slave_Buffer_A2_P80H_Up[FLASH_HT_TEMP];
        lt_temp = (signed char)I2C_Slave_Buffer_A2_P80H_Up[FLASH_LT_TEMP];
        curr_temp = (signed char)I2C_Slave_Buffer_A2_P80H_Up[FLASH_RAW_CURRENT_TEMP];
        
	t_chNo = (uint16_t)curr_channel_no - 1;
//        if ((curr_channel_no >= 1) && (curr_channel_no <= 4))
        if ((curr_channel_no >= 1) && (curr_channel_no <= 8))
        {
//          t_chNo = curr_channel_no - 1;
          t_chNo = (curr_channel_no - 1)%4;
        }
        else
        {
          t_chNo = 0; // curr_channel_no = 1
        }        
        
        if (curr_temp > reference_temp)
        {
          // High Temp. Control
          div_value = __swap_bytes(flashPtr->ht_XconBiasSet[t_chNo]) - __swap_bytes(flashPtr->nt_XconBiasSet[t_chNo]);
          div_value = (div_value * 100) / (ht_temp - reference_temp);
        }
        else
        {
          // Low Temp. Control
          m_div_value = __swap_bytes(flashPtr->nt_XconBiasSet[t_chNo]) - __swap_bytes(flashPtr->lt_XconBiasSet[t_chNo]);
          m_div_value = (m_div_value * 100) / (reference_temp - lt_temp);
          
        }

//	da = __swap_bytes(flashPtr->XconBiasSet[0][t_chNo]);
	da = (unsigned int)__swap_bytes(flashPtr->nt_XconBiasSet[t_chNo]);

	diff = (signed char)(curr_temp - reference_temp);

	if (diff < 0) {
		diff = (-1) * diff;
                offset_value_1 = (diff * m_div_value);
                if (offset_value_1 < 0)
                {
                  offset_value_1 = offset_value_1 - 50;
                }
                else
                {
                  offset_value_1 = offset_value_1 + 50;
                }
                
                offset_value = offset_value_1 / 100;
                
		da = da - offset_value;
	}
	else {
                offset_value_1 = (diff * div_value);
                if (offset_value_1 < 0)
                {
                  offset_value_1 = offset_value_1 - 50;
                }
                else
                {
                  offset_value_1 = offset_value_1 + 50;
                }
                
                offset_value = offset_value_1 / 100;

//                offset_value = (diff * div_value)/100;

                da = da + offset_value;
	}
        
        // [DCLEE] 2020.08.19. ���� 80, -15 �� �����Ͽ� ����/���� ������ ���� ��Ŀ��� ��� tracing �ϴ� �������� ��ȯ
        if (ddm_curr_temp > HIGH_TEMP_THRESHOLD)
        {
//          da = (unsigned int)__swap_bytes(flashPtr->ht_XconBiasSet[t_chNo]);
        }
        else if (ddm_curr_temp < LOW_TEMP_THRESHOLD)
        {
//          da = (unsigned int)__swap_bytes(flashPtr->lt_XconBiasSet[t_chNo]);
          
        }

	if( da > MAX_Xcon_DA )
		da = MAX_Xcon_DA;
	else if( da < 0 )
		da = 0;

        XconBiasDa = da;
        
//        rDa = LD_Drive_Get(CH_TYPE_CPA,0);
        
        if (XconBiasDa != prevXconBiasDa)
        {
          LD_Drive_Set(CH_TYPE_CPA, 0, XconBiasDa);
        }
//        else if (rDa != XconBiasDa)
//        {
//          LD_Drive_Set(CH_TYPE_CPA, 0, XconBiasDa);          
//        }
        
//        if (prevXconBiasDa != XconBiasDa)
//        {
//          LD_Drive_Set( CH_TYPE_CPA, 0, XconBiasDa);
//        }
        prevXconBiasDa = XconBiasDa;
//        LD_Drive_Set(CH_TYPE_CPA, cpa_dac_ch_no, XconBiasDa );
        
        if (lowerMemoryPtr->A2_TABLE == 0x80)
        {
          flashPtr_1->XconBiasSet = __swap_bytes(XconBiasDa);          
        }
                
	 
#else
  
  
  signed int xdata da, diff, offset_value, offset_value_1;
//	signed int xdata curr_pwr, target_pwr;
	signed char xdata div_value, m_div_value;
	flashStructType	xdata * flashPtr;
//	signed int xdata * tmp_ptr, * tmp_ptr1, * tmp_ptr2;
//	signed char xdata * tmp_ptr3;
	signed char	xdata t_chNo;
//	uint16_t	xdata div_value1, div_value2, div_value3;
//	uint16_t	xdata m_div_value1, m_div_value2, m_div_value3;
        signed char  curr_temp, reference_temp, ht_temp, lt_temp;
//        unsigned int  daa;
        
//        LOWER_MEMORY_MAP * xdata lowerMemoryMapPtr;
//        
//	lowerMemoryMapPtr = (LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A0[0];
	flashPtr = (flashStructType *)&I2C_Slave_Buffer_A4_Local_Memory[0];


//        curr_temp = __swap_bytes(lowerMemoryMapPtr->TEMPERATURE);
//        curr_temp = (curr_temp >> 8) & 0xFFFF;
//        
//        reference_temp = __swap_bytes(flashPtr->tosa_global_temp);
//        reference_temp = (reference_temp >> 8) & 0xFFFF;
        
        curr_temp = (signed char)I2C_Slave_Buffer_A0[QSFP_LOWER_MEMORY_TEMPERATURE];
        reference_temp = (signed char)I2C_Slave_Buffer_A4_Local_Memory[FLASH_NT_TEMP];
        ht_temp = (signed char)I2C_Slave_Buffer_A4_Local_Memory[FLASH_HT_TEMP];
        lt_temp = (signed char)I2C_Slave_Buffer_A4_Local_Memory[FLASH_LT_TEMP];
        
	t_chNo = (uint16_t)chNo;
        
        if (curr_temp > reference_temp)
        {
          // High Temp. Control
          div_value = flashPtr->ht_XconBiasSet[0][t_chNo] - flashPtr->nt_XconBiasSet[0][t_chNo];
          div_value = (div_value * 100) / (ht_temp - reference_temp);
        }
        else
        {
          // Low Temp. Control
          m_div_value = flashPtr->nt_XconBiasSet[0][t_chNo] - flashPtr->lt_XconBiasSet[0][t_chNo];
          m_div_value = (m_div_value * 100) / (reference_temp - lt_temp);
          
        }

//	da = __swap_bytes(flashPtr->XconBiasSet[0][t_chNo]);
	da = (unsigned int)flashPtr->nt_XconBiasSet[0][t_chNo];

	// da = LdBiasDa[0][t_chNo];

//	diff = target_value - monitor_value;
	diff = (signed char)(curr_temp - reference_temp);

	if (diff < 0) {
		diff = (-1) * diff;
                offset_value_1 = (diff * m_div_value);
                if (offset_value_1 < 0)
                {
                  offset_value_1 = offset_value_1 - 50;
                }
                else
                {
                  offset_value_1 = offset_value_1 + 50;
                }
                
                offset_value = offset_value_1 / 100;
                
		da = da - offset_value;
	}
	else {
                offset_value_1 = (diff * div_value);
                if (offset_value_1 < 0)
                {
                  offset_value_1 = offset_value_1 - 50;
                }
                else
                {
                  offset_value_1 = offset_value_1 + 50;
                }
                
                offset_value = offset_value_1 / 100;

//                offset_value = (diff * div_value)/100;

                da = da + offset_value;
	}

	if( da > MAX_Xcon_DA )
		da = MAX_Xcon_DA;
	else if( da < 0 )
		da = 0;

	// if (da != (INT16S)LdBiasDa[sigNo][chNo])
	{
		XconBiasDa[0][t_chNo] = da;
//                daa = (unsigned int)(LD_Drive_Get(CH_TYPE_CPA, cpa_dac_ch_no[0][t_chNo]));
//                if (XconBiasDa[0][t_chNo] != daa) {		
//                  LD_Drive_Set(CH_TYPE_CPA, cpa_dac_ch_no[0][t_chNo], XconBiasDa[0][t_chNo] );
//                }
                  LD_Drive_Set(CH_TYPE_CPA, cpa_dac_ch_no[0][t_chNo], XconBiasDa[0][t_chNo] );
                
//		prevLdBiasDa[0][t_chNo] = LdBiasDa[0][t_chNo];

//		tmp_ptr = (uint16_t *)&I2C_Slave_Buffer_A0_P0_Up[(UPPER_MEMORY_PAGE0_LD_BIASn_DAC(chNo) & 0x7F)];
//		*tmp_ptr = __swap_bytes(LdBiasDa[0][t_chNo]);
	}
//	*tmp_ptr1 = qsfp_module_debug_run_state;
//	flashPtr->tosa_diff_value_ref = div_value;
        
//	flashPtr->tosa_diff_value_ref = offset_value;
        
#endif

}/*}}}*/

void LdInit_forced_on_first( void ){/*{{{*/

#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
        // APC Mode disable
        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[P00_CR1];  
        tx_i2c_master_data[0] &= 0xE7;
        I2C_Slave_Buffer_A2_P82H_Up[P00_CR1] = tx_i2c_master_data[0];
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_CR1, 1, &tx_i2c_master_data[0]);
        
        LdBiasSetFlag2 = 1;
        
//        LdControl_first_init();
        
        LdControl(0, 0);
        
        // TX_DIS: normal op (0)
        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[P00_CR1];  
        tx_i2c_master_data[0] &= 0xBF;
        I2C_Slave_Buffer_A2_P82H_Up[P00_CR1] = tx_i2c_master_data[0];        
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_CR1, 1, &tx_i2c_master_data[0]);
        
#else
        tx_i2c_master_data[0] = 0x0B;
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_OPMODE_CTRL, 1, &tx_i2c_master_data[0]);
        
//        tx_i2c_master_data[0] = 0xCA;
//        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_CTRL0, 1, &tx_i2c_master_data[0]);

	//return;
//        ModBiasControl_manually(0, 0 );
//        XconBiasControl(0, 0 );
//
//        LdControl_manually(0, 0 );
//        
//        LD_Drive_Set(CH_TYPE_STROBE, 0, 1);

        LdBiasSetFlag2 = 1;
        LdControl(0, 0);
//        exec_upper_page2_memory(0xA2, 0x02, 0x91, I2C_Slave_Buffer_A2_P02H_Up[0x11]);
        
//        SW_Delay(20);
//
//        tx_i2c_master_data[0] = 0xCA;
//        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_CTRL0, 1, &tx_i2c_master_data[0]);
//        
//        SW_Delay(20);

//        tx_i2c_master_data[0] = 0xCE;
//        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_CTRL0, 1, &tx_i2c_master_data[0]);
//
//        SW_Delay(1000);
        
        tx_i2c_master_data[0] = 0xCA;
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_CTRL0, 1, &tx_i2c_master_data[0]);
        
#endif
        
}/*}}}*/


void TEC_Control_APC_3(INT8U sigNo, INT8U chNo )
{/*{{{*/ // maintain a Tx Power
#if __SFP28_ER_SEMI_TUNABLE__ == 1
  
	signed long xdata da, diff, offset_value, offset_value_1;
	signed int xdata div_value, m_div_value;
//	signed int xdata div_value, m_div_value, ofVal;
//	signed int xdata s_div_value, s_m_div_value;
//	A2_PAGE_80H_MEMORY_MAP	* flashPtr_2;
//	A2_PAGE_80H_MEMORY_MAP	* flashPtr_3;
	A2_PAGE_81H_MEMORY_MAP	* flashPtr;
//        A2_LOWER_MEMORY_MAP * lowerMemoryPtr;
//	signed int xdata * tmp_ptr;
	signed char	xdata t_chNo;
        signed char  curr_temp, reference_temp, ht_temp, lt_temp, ddm_curr_temp;
//        unsigned int  rDa;
	A2_PAGE_81H_MEMORY_MAP	* flashPtr_1;
        A2_LOWER_MEMORY_MAP * lowerMemoryPtr;
        
	flashPtr_1 = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_Pn_Up[0];
	lowerMemoryPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];
        
//	flashPtr_2 = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
//	flashPtr_3 = (A2_PAGE_80H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P80H_Up[0];
	flashPtr = (A2_PAGE_81H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P81H_Up[0];
//        lowerMemoryPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];

        
        ddm_curr_temp = (signed char)I2C_Slave_Buffer_A2[LOWER_MEMORY_A2_TEMPERATURE];
        reference_temp = (signed char)I2C_Slave_Buffer_A2_P80H_Up[FLASH_NT_TEMP];
        ht_temp = (signed char)I2C_Slave_Buffer_A2_P80H_Up[FLASH_HT_TEMP];
        lt_temp = (signed char)I2C_Slave_Buffer_A2_P80H_Up[FLASH_LT_TEMP];
        curr_temp = (signed char)I2C_Slave_Buffer_A2_P80H_Up[FLASH_RAW_CURRENT_TEMP];
        
	t_chNo = (uint16_t)curr_channel_no - 1;
//        if ((curr_channel_no >= 1) && (curr_channel_no <= 4))
        if ((curr_channel_no >= 1) && (curr_channel_no <= 8))
        {
//          t_chNo = curr_channel_no - 1;
          t_chNo = (curr_channel_no - 1)%4;
        }
        else
        {
          t_chNo = 0; // curr_channel_no = 1
        }        
        
        if (curr_temp > reference_temp)
        {
          // High Temp. Control
          div_value = __swap_bytes(flashPtr->ht_tec_setpoint_per_wavelength[t_chNo]) - __swap_bytes(flashPtr->nt_tec_setpoint_per_wavelength[t_chNo]);
//          div_value = (div_value * 100) / (ht_temp - reference_temp);
          div_value = (div_value * 10) / ((ht_temp - reference_temp)/10);
//          s_div_value = div_value;
//          flashPtr_2->vapd_dac = __swap_bytes(div_value);
        }
        else
        {
          // Low Temp. Control
          m_div_value = __swap_bytes(flashPtr->nt_tec_setpoint_per_wavelength[t_chNo]) - __swap_bytes(flashPtr->lt_tec_setpoint_per_wavelength[t_chNo]);
//          m_div_value = (m_div_value * 100) / (reference_temp - lt_temp);
          m_div_value = (m_div_value * 10) / ((reference_temp - lt_temp)/10);
//          s_m_div_value = m_div_value;
//          flashPtr->idcn = __swap_bytes(m_div_value);
          
        }

//	da = __swap_bytes(flashPtr->XconBiasSet[0][t_chNo]);
	da = (unsigned int)__swap_bytes(flashPtr->nt_tec_setpoint_per_wavelength[t_chNo]);

	diff = (signed char)(curr_temp - reference_temp);

	if (diff < 0) {
		diff = (-1) * diff;
                offset_value_1 = (diff * m_div_value);
                if (offset_value_1 < 0)
                {
                  offset_value_1 = offset_value_1 - 50;
                }
                else
                {
                  offset_value_1 = offset_value_1 + 50;
                }
                
                offset_value = offset_value_1 / 100;
                
		da = da - offset_value;
//		da = da + offset_value; // [DCLEE] 2020.08.10 
//                ofVal = offset_value;
//                flashPtr->idcd = __swap_bytes(ofVal);
	}
	else {
                offset_value_1 = (diff * div_value);
                if (offset_value_1 < 0)
                {
                  offset_value_1 = offset_value_1 - 50;
                }
                else
                {
                  offset_value_1 = offset_value_1 + 50;
                }
                
                offset_value = offset_value_1 / 100;

//                offset_value = (diff * div_value)/100;

//                da = da + offset_value;
                da = da + offset_value; // [DCLEE] 2020.08.10 
                
//                ofVal = offset_value;
//                flashPtr_2->vapd_dac_readout = __swap_bytes(ofVal);
                
	}

        // [DCLEE] 2020.08.19. ���� 80, -15 �� �����Ͽ� ����/���� ������ ���� ��Ŀ��� ��� tracing �ϴ� �������� ��ȯ
        if (ddm_curr_temp > HIGH_TEMP_THRESHOLD)
        {
//          da = (unsigned int)__swap_bytes(flashPtr->ht_tec_setpoint_per_wavelength[t_chNo]);
        }
        else if (ddm_curr_temp < LOW_TEMP_THRESHOLD)
        {
//          da = (unsigned int)__swap_bytes(flashPtr->lt_tec_setpoint_per_wavelength[t_chNo]);
          
        }
        
	if( da > MAX_TEC_CONTROL_DA ) // 35 C�� Thermister �� --> 20 �� �� ����
        {
		da = MAX_TEC_CONTROL_DA;
        }
        else if ( da < MIN_TEC_CONTROL_DA ) // 75 C�� Thermister �� --> 80 �� �� ���� (200923)
        {
          	da = MIN_TEC_CONTROL_DA;
        }
//	else if( da < 0 )
//		da = 0;

        TEC_Control_Da = da;
        
//        rDa = LD_Drive_Get(CH_TYPE_CPA,0);
        
        if (TEC_Control_Da != prev_TEC_Control_Da)
        {
//          LD_Drive_Set(CH_TYPE_CPA, 0, TEC_Control_Da);
          flashPtr->TEC1_SETPOINT = __swap_bytes(TEC_Control_Da);
          
          ConfigTec1(INDEX_TEC_SETPOINT, __swap_bytes(flashPtr->TEC1_SETPOINT)); 

        }
//        else if (rDa != XconBiasDa)
//        {
//          LD_Drive_Set(CH_TYPE_CPA, 0, XconBiasDa);          
//        }
        
//        if (prevXconBiasDa != XconBiasDa)
//        {
//          LD_Drive_Set( CH_TYPE_CPA, 0, XconBiasDa);
//        }
        prev_TEC_Control_Da = TEC_Control_Da;
//        LD_Drive_Set(CH_TYPE_CPA, cpa_dac_ch_no, XconBiasDa );
                
        if (lowerMemoryPtr->A2_TABLE == 0x81)
        {
          flashPtr_1->TEC1_SETPOINT = __swap_bytes(TEC_Control_Da);          
        }

#endif

}/*}}}*/


void LD_Drive_Set( char ch_type, char ch_num, int value )
{/*{{{*/
#if __QSFP28_SR4__== 1

#elif ((__QSFP28_LR4__== 1) || (__QSFP28_CWDM4__== 1))
        
#elif __SFP28_ER__==1
  
#if __SFP28_ER_SEMI_TUNABLE__ == 1

#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
  
	unsigned char xdata rVal, rVal1;
        A2_PAGE_80H_MEMORY_MAP * flashPtr; 
        unsigned char  cVal1, cVal2;
        
        flashPtr = (A2_PAGE_80H_MEMORY_MAP *)(&I2C_Slave_Buffer_A2_P80H_Up[0]);

	ch_num = 0;
        ch_num++;

	// Delay_x1us(5);
	if (ch_type == CH_TYPE_BSET)
	{          
          // ---------------------------------------------------
          // BIAS_SET_DAC: (0x1F, 0x20), Bias current at start-up (APC mode) or Bias current at manually
          //         MSB[3:0]: LSB[7:0]: 12-bit, 0x000 = 0 mA, 0xFFF = max Isnk.
          
//          reg_addr = P00_BIAS_SET_DAC; 
          cVal1 = (unsigned char)((value >> 8) & 0x0F);
          cVal2 = (unsigned char)(value & 0x00FF);
          
          read_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_BIAS_SET_DAC, 2, &tx_i2c_master_data[0]);
          
          rVal1 = tx_i2c_master_data[0];
          rVal1 = cVal1;
          tx_i2c_master_data[0] = rVal1;          
          tx_i2c_master_data[1] = cVal2;
          
          if (tx_dis_flag_before_isr == 1) {
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_BIAS_SET_DAC, 2, &tx_i2c_master_data[0]);
          }
          else if (tx_dis_flag_after_isr == 0) {
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_BIAS_SET_DAC, 2, &tx_i2c_master_data[0]);
          }
          I2C_Slave_Buffer_A2_P82H_Up[P00_BIAS_SET_DAC_MSB] = tx_i2c_master_data[0];
          I2C_Slave_Buffer_A2_P82H_Up[P00_BIAS_SET_DAC_LSB] = tx_i2c_master_data[1];
          
          // Strobe DAC
                    
	}
	else if (ch_type == CH_TYPE_MSET)
	{
          // ---------------------------------------------------
          // MOD_SET_DAC: (0x1D, 0x1E), modulation current
          //         MSB[3:0]: LSB[7:0]: 12-bit, 0x000 = 0 mApp, 0xFFF = max Imod.
          
//          reg_addr = P00_MOD_SET_DAC; 

          cVal1 = (unsigned char)((value >> 8) & 0x0F);
          cVal2 = (unsigned char)(value & 0x00FF);
          
          read_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_MOD_SET_DAC, 2, &tx_i2c_master_data[0]);
          
          rVal1 = tx_i2c_master_data[0];
          rVal1 = cVal1;
          tx_i2c_master_data[0] = rVal1;          
          tx_i2c_master_data[1] = cVal2;
          
          if (tx_dis_flag_before_isr == 1) {
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_MOD_SET_DAC, 2, &tx_i2c_master_data[0]);
          }
          else if (tx_dis_flag_after_isr == 0) {
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_MOD_SET_DAC, 2, &tx_i2c_master_data[0]);
          }
          
          I2C_Slave_Buffer_A2_P82H_Up[P00_MOD_SET_DAC_MSB] = tx_i2c_master_data[0];
          I2C_Slave_Buffer_A2_P82H_Up[P00_MOD_SET_DAC_LSB] = tx_i2c_master_data[1];
          
//          // Strobe DAC          
          
	}
	else if (ch_type == CH_TYPE_CPA)
	{
          // VCPA_DAC. Adjustment of the Tx crossing point.
          // Bit 0 is the enable (1= enabled, 0 = disabled)
          // Bits [7:1]: control the magnitude of the crsssing point when enabled
          // For bits [7:1], a setting of 0x00 = min crossing, 0x7F = maximun crossing

//          reg_addr = P00_VCPA_DAC; 
          rVal1 = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_VCPA_DAC);

          if ((rVal1 & 0x01) == 0x01)
          {
            // Set to enabled crossing point
            rVal1 = 0x01;            
          }
          else
          {
            // Set to disable crossing point
            rVal1 = 0x01;
           
          }
          
          cVal1 = (value << 1) & 0x00FE;
          rVal = cVal1 | rVal1;
          
          if (tx_dis_flag_before_isr == 1) {
            write_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_VCPA_DAC, rVal);
          }
          else if (tx_dis_flag_after_isr == 0) {
            write_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_VCPA_DAC, rVal);
          }
          
          I2C_Slave_Buffer_A2_P82H_Up[P00_VCPA_DAC] = tx_i2c_master_data[0];
          
          rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_VCPA_DAC);
          value = (unsigned int)((rVal >> 1) & 0x7F);
          flashPtr->dac_gpdac = __swap_bytes(value);

        }

	return;

#else
  
//	unsigned char xdata reg_addr, rVal, rVal1;
	unsigned char xdata rVal, rVal1;
        A2_PAGE_80H_MEMORY_MAP * flashPtr; 
//        unsigned char  cVal1, cVal2, r_data[4];
        unsigned char  cVal1, cVal2;
        
        flashPtr = (A2_PAGE_80H_MEMORY_MAP *)(&I2C_Slave_Buffer_A2_P80H_Up[0]);

	ch_num = 0;
        ch_num++;

	// Delay_x1us(5);
	if (ch_type == CH_TYPE_BSET)
	{          
//          eml_bias_set(ch_num, (unsigned int)value);
          
          // ---------------------------------------------------
          // I0_MSB: (0x39), Initial Current MSB
          //         [5:4]: im0[9:8] Initial modulation current MSB. Also used for open loop mode
          //         [1:0]: ib0[9:8] Initial bias current MSB. Also used for open loop mode
          // IB0_LSB: (0x3A), Initial bias Current LSB. Also used for open loop mode (values are strobed to the bias DAC).
          
//          reg_addr = P00_I0_MSB; 
          cVal1 = (unsigned char)((value >> 8) & 0x03);
          cVal2 = (unsigned char)(value & 0x00FF);
          
          read_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_I0_MSB, 3, &tx_i2c_master_data[0]);
          
          rVal1 = tx_i2c_master_data[0];
          rVal1 = rVal1 & 0xFC;
          rVal1 = rVal1 | cVal1;
          tx_i2c_master_data[0] = rVal1;          
          tx_i2c_master_data[1] = cVal2;
          
          if (tx_dis_flag_before_isr == 1) {
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_I0_MSB, 3, &tx_i2c_master_data[0]);
          }
          else if (tx_dis_flag_after_isr == 0) {
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_I0_MSB, 3, &tx_i2c_master_data[0]);
          }
          
          // Strobe DAC
          
//          rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_STROBE);
//          rVal = rVal | 0x01;
//          write_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_STROBE, rVal);
//          
          
	}
	else if (ch_type == CH_TYPE_MSET)
	{
//          reg_addr = 4; // EAM Bias Set :DAC ChNo 4
//          if (tx_dis_flag_before_isr == 1) {
//            DS_DAC_Duty(reg_addr, value);
//          }
//          else if (tx_dis_flag_after_isr == 0) {
//            DS_DAC_Duty(reg_addr, value);
//          }
//          value = DS_DAC_Read_Duty(reg_addr);
//          
//          flashPtr->dac = __swap_bytes(value);
          
          // ---------------------------------------------------
          
          // I0_MSB: (0x39), Initial Current MSB
          //         [5:4]: im0[9:8] Initial modulation current MSB. Also used for open loop mode
          //         [1:0]: ib0[9:8] Initial bias current MSB. Also used for open loop mode
          // IM0_LSB: (0x3B), Initial Modulation Current LSB. Also used for open loop mode (values are strobed to the bias DAC).
          
//          reg_addr = P00_I0_MSB; // VC Set 0: DAC ChNo 0, CrossPoint
          cVal1 = (unsigned char)((value >> 8) & 0x03);
          cVal1 = (cVal1 << 4);
          cVal2 = (unsigned char)(value & 0x00FF);
          
          read_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_I0_MSB, 3, &tx_i2c_master_data[0]);
          
          rVal1 = tx_i2c_master_data[0];
          rVal1 = rVal1 & 0xCF;
          rVal1 = rVal1 | cVal1;
          tx_i2c_master_data[0] = rVal1;          
          tx_i2c_master_data[2] = cVal2;
          
          if (tx_dis_flag_before_isr == 1) {
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_I0_MSB, 3, &tx_i2c_master_data[0]);
          }
          else if (tx_dis_flag_after_isr == 0) {
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_I0_MSB, 3, &tx_i2c_master_data[0]);
          }
          
//          // Strobe DAC
//          
//          rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_STROBE);
//          rVal = rVal | 0x01;
//          write_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_STROBE, rVal);
          
//          flashPtr->dac_gpdac = __swap_bytes(value);
          
          
	}
	else if (ch_type == CH_TYPE_CPA)
	{
          // TX DCD control. Crossing point adjustment is approximately 0.75%/LSB
          // or -23.5% + tx_dcd x 0.75% where tx_dcd is the decimal code
          // This adjustment to the crossing point is only active when 0x40[0]=0b
          // LD_DRV_CTRL4 (0x42 address, tx_dcd[5:0]): default is 0x9F

          rVal1 = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_DRV_CTRL2);

          if ((rVal1 & 0x01) == 0x01)
          {
            // tx_dcd_off: (TX crossing point adjustment enabled)
            // No action
            rVal1 = rVal1 & 0xFE;
            write_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_DRV_CTRL2, rVal1);            
            
          }
          else
          {
            // tx_dcd_off: (TX crossing point adjustment disabled)
            // No action
//            rVal1 = rVal1 & 0xFE;
//            write_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_DRV_CTRL2, rVal1);            
          }
          
//          reg_addr = ch_num; // VC Set 0: DAC ChNo 0, CrossPoint
          rVal1 = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_DRV_CTRL4);
          rVal1 = rVal1 & 0xC0;
          rVal = (unsigned char)(value & 0x3F);
          rVal = rVal1 | rVal;
          
          if (tx_dis_flag_before_isr == 1) {
            write_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_DRV_CTRL4, rVal);
          }
          else if (tx_dis_flag_after_isr == 0) {
            write_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_DRV_CTRL4, rVal);
          }
          
          rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_DRV_CTRL4);
          value = (unsigned int)(rVal & 0x3F);
          flashPtr->dac_gpdac = __swap_bytes(value);

        }
	else if (ch_type == CH_TYPE_STROBE)
	{
          // Strobe DAC
          
          rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_STROBE);
          rVal = rVal | 0x01;
          write_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_STROBE, rVal);
          
	}

	return;

#endif
        
#else
  
	unsigned char xdata reg_addr, rVal;
        A2_PAGE_80H_MEMORY_MAP * flashPtr; 
        
        flashPtr = (A2_PAGE_80H_MEMORY_MAP *)(&I2C_Slave_Buffer_A2_P80H_Up[0]);

	ch_num = 0;

	// Delay_x1us(5);
	if (ch_type == CH_TYPE_BSET)
	{          
          eml_bias_set(ch_num, (unsigned int)value);
	}
	else if (ch_type == CH_TYPE_MSET)
	{
          reg_addr = 4; // EAM Bias Set :DAC ChNo 4
          if (tx_dis_flag_before_isr == 1) {
            DS_DAC_Duty(reg_addr, value);
          }
          else if (tx_dis_flag_after_isr == 0) {
            DS_DAC_Duty(reg_addr, value);
          }
          value = DS_DAC_Read_Duty(reg_addr);
          
          flashPtr->dac = __swap_bytes(value);
          
	}
	else if (ch_type == CH_TYPE_CPA)
	{
          reg_addr = ch_num; // VC Set 0: DAC ChNo 0, CrossPoint
          rVal = (unsigned char)value;
          if (tx_dis_flag_before_isr == 1) {
            write_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_GPDAC, rVal);
          }
          else if (tx_dis_flag_after_isr == 0) {
            write_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_GPDAC, rVal);
          }
//          Max5825_dac_set(0, reg_addr, value);
          rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_GPDAC);
          value = (unsigned int)rVal;
          flashPtr->dac_gpdac = __swap_bytes(value);

        }
	else
	{
		return;
	}

	return;
   
#endif
        
#endif

}/*}}}*/
// LD_Drive_Set Control Function Lib. End.

void eml_bias_set(unsigned char bias_ch, unsigned int unBias)
{
#if __SFP28_ER_SEMI_TUNABLE__ == 1

#else
  
  
  A2_PAGE_80H_MEMORY_MAP * flashPtr; 
  
  flashPtr = (A2_PAGE_80H_MEMORY_MAP *)(&I2C_Slave_Buffer_A2_P80H_Up[0]);

  if((IDCN2 & 0x0001))                                       //check if IDAC and DCDC1 are enabled
  {
    unBias = unBias;
  }
  else
  {
    unBias = 0;                                                                 //if IDAC and DCDC1 are disabled, set Bias to 0
  }
  
  
  if(unBias > BIAS_MAX)                                                         //Max Bias checking(internal use), customer can change BIAS_MAX for their application,
  {
    
    unBias = BIAS_MAX;
    
  }
  
  if (tx_dis_flag_before_isr == 1) {
    if(unBias != IDCD2)                                                           //if not equal, update IDCD1
    {      
      __disable_interrupt();                                                       //disable interrupt before updating IDAC, some operation in ISR may update IDAC too
      IDCD2 = unBias;                                                              //Update IDCD1
      __enable_interrupt();                                                        //enable interrupt
      
    } 
  }
  else if (tx_dis_flag_after_isr == 0) {
    if(unBias != IDCD2)                                                           //if not equal, update IDCD1
    {      
      __disable_interrupt();                                                       //disable interrupt before updating IDAC, some operation in ISR may update IDAC too
      IDCD2 = unBias;                                                              //Update IDCD1
      __enable_interrupt();                                                        //enable interrupt
      
    } 
  }
  
  flashPtr->idcn = __swap_bytes(IDCN2);
  flashPtr->idcd = __swap_bytes(IDCD2);
   
#endif
  
}


uint16_t LD_Drive_Get( char ch_type, char ch_num)
{/*{{{*/
#if __QSFP28_SR4__== 1 
  
#elif ((__QSFP28_LR4__== 1) || (__QSFP28_CWDM4__== 1))
  
#elif __SFP28_ER_SEMI_TUNABLE__ == 1

#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
  
//	unsigned char xdata rVal, rVal1;
//        A2_PAGE_80H_MEMORY_MAP * flashPtr; 
//        unsigned char  cVal1, cVal2;
        uint16_t unDdm_value;
        
//        flashPtr = (A2_PAGE_80H_MEMORY_MAP *)(&I2C_Slave_Buffer_A2_P80H_Up[0]);

	ch_num = 0;
        ch_num++;

	// Delay_x1us(5);
	// Delay_x1us(5);
	if (ch_type == CH_TYPE_BSET)
	{          
          // ---------------------------------------------------
          // BIAS_SET_DAC: (0x1F, 0x20), Bias current at start-up (APC mode) or Bias current at manually
          //         MSB[3:0]: LSB[7:0]: 12-bit, 0x000 = 0 mA, 0xFFF = max Isnk.
          
//          reg_addr = P00_BIAS_SET_DAC; 
          unDdm_value = 0;
          read_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_BIAS_SET_DAC, 2, &tx_i2c_master_data[0]);
          
          unDdm_value = tx_i2c_master_data[0];
          unDdm_value = (unDdm_value & 0x0F)<<8;
          unDdm_value += tx_i2c_master_data[1];
                    
	}
	else if (ch_type == CH_TYPE_MSET)
	{
          // ---------------------------------------------------
          // MOD_SET_DAC: (0x1D, 0x1E), modulation current
          //         MSB[3:0]: LSB[7:0]: 12-bit, 0x000 = 0 mApp, 0xFFF = max Imod.
          
//          reg_addr = P00_MOD_SET_DAC; 
          unDdm_value = 0;
          read_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_MOD_SET_DAC, 2, &tx_i2c_master_data[0]);
          
          unDdm_value = tx_i2c_master_data[0];
          unDdm_value = (unDdm_value & 0x0F)<<8;
          unDdm_value += tx_i2c_master_data[1];
          
	}
	else if (ch_type == CH_TYPE_CPA)
	{
          // VCPA_DAC. Adjustment of the Tx crossing point.
          // Bit 0 is the enable (1= enabled, 0 = disabled)
          // Bits [7:1]: control the magnitude of the crsssing point when enabled
          // For bits [7:1], a setting of 0x00 = min crossing, 0x7F = maximun crossing

//          reg_addr = P00_VCPA_DAC; 
          unDdm_value = 0;
          read_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_VCPA_DAC, 1, &tx_i2c_master_data[0]);
          
          unDdm_value = tx_i2c_master_data[0];
          unDdm_value = (unDdm_value & 0xFE)>> 1;

        }
        else
        {
          unDdm_value = 0;
        }
	return unDdm_value;

#else
  
//	unsigned char xdata reg_addr, rVal, rVal1;
  	unsigned char xdata rVal;
        A2_PAGE_80H_MEMORY_MAP * flashPtr; 
//        unsigned char  cVal1, cVal2, r_data[4];
        uint16_t unDdm_value;
        flashPtr = (A2_PAGE_80H_MEMORY_MAP *)(&I2C_Slave_Buffer_A2_P80H_Up[0]);

	ch_num = 0;
        ch_num++;

	// Delay_x1us(5);
	if (ch_type == CH_TYPE_BSET)
	{          
//          eml_bias_set(ch_num, (unsigned int)value);
          
          // ---------------------------------------------------
          // I0_MSB: (0x39), Initial Current MSB
          //         [5:4]: im0[9:8] Initial modulation current MSB. Also used for open loop mode
          //         [1:0]: ib0[9:8] Initial bias current MSB. Also used for open loop mode
          // IB0_LSB: (0x3A), Initial bias Current LSB. Also used for open loop mode (values are strobed to the bias DAC).
          
//          reg_addr = P00_I0_MSB; 
          
          unDdm_value = 0;
          read_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_I0_MSB, 3, &tx_i2c_master_data[0]);
          
          unDdm_value = tx_i2c_master_data[0];
          unDdm_value = (unDdm_value & 0x03)<<8;
          unDdm_value += tx_i2c_master_data[1];
                    
	}
	else if (ch_type == CH_TYPE_MSET)
	{
          
          // ---------------------------------------------------
          
          // I0_MSB: (0x39), Initial Current MSB
          //         [5:4]: im0[9:8] Initial modulation current MSB. Also used for open loop mode
          //         [1:0]: ib0[9:8] Initial bias current MSB. Also used for open loop mode
          // IM0_LSB: (0x3B), Initial Modulation Current LSB. Also used for open loop mode (values are strobed to the bias DAC).
          
//          reg_addr = P00_I0_MSB; 
          
          unDdm_value = 0;
          read_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_I0_MSB, 3, &tx_i2c_master_data[0]);
          
          unDdm_value = (tx_i2c_master_data[0] & 0x30);
          unDdm_value = (unDdm_value<<4);
          unDdm_value += tx_i2c_master_data[2];          
          
	}
	else if (ch_type == CH_TYPE_CPA)
	{
          // TX DCD control. Crossing point adjustment is approximately 0.75%/LSB
          // or -23.5% + tx_dcd x 0.75% where tx_dcd is the decimal code
          // This adjustment to the crossing point is only active when 0x40[0]=0b
          // LD_DRV_CTRL4 (0x42 address, tx_dcd[5:0]): default is 0x9F

//          unDdm_value = __swap_bytes(flashPtr->dac_gpdac);
          
          rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_DRV_CTRL4);
          unDdm_value = (unsigned int)(rVal & 0x3F);
          flashPtr->dac_gpdac = __swap_bytes(unDdm_value);

        }
        else
        {
          unDdm_value = 0;
        }
	return unDdm_value;

#endif
        
#else
        return (0);
#endif

}/*}}}*/



void trigger_LDD_IC_ADC_Mon(void)
{
#if __QSFP28_LR4__== 1

#endif
}

void get_adc_from_LDD_IC(void)
{
        
}

void polled_LD_DC_reg_info(uint8_t page_no)
{
#if __QSFP28_LR4__== 1
#elif __SFP28_ER__== 1
//  polled_tx_rx_combo_cdr_reg_info();
#endif
}

// TX CDR Initialization
void polled_tx_rx_combo_cdr_reg_info(void)
{
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
  // GN_1157
 	uint8_t xdata reg_addr;

	for (reg_addr = 0; reg_addr < 128; reg_addr += 4)
	{
                WDCN_bit.RWT = 1;                                                       //reset watchdog timer
		read_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, reg_addr, 4, &I2C_Slave_Buffer_A2_P82H_Up[reg_addr]);
	}      
  
#else
 	uint8_t xdata reg_addr;

	for (reg_addr = 0; reg_addr < 128; reg_addr += 4)
	{
                WDCN_bit.RWT = 1;                                                       //reset watchdog timer
		read_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, reg_addr, 4, &I2C_Slave_Buffer_A2_P82H_Up[reg_addr]);
	}
        
	for (reg_addr = 0; reg_addr < 128; reg_addr += 4)
	{
                WDCN_bit.RWT = 1;                                                       //reset watchdog timer
		read_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, reg_addr + 0x80, 4, &I2C_Slave_Buffer_A2_P83H_Up[reg_addr]);
	}
        
        // Power Management Register Reading. 
        // The registers that control the power management circuitry are located at I2C address 4Fh. 
        // Before the registers at 4Fh may be read or written, communication with address 4Fh must first be enabled by writing 0x05 = 01h. 
        // When communications with the power management registers is not active it should be disabled by writing 0x05 = 00h.
        
        tx_i2c_master_data[0] = 0x01;
	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_PASSTHROUGH_EN, 1, &tx_i2c_master_data[0]);

	for (reg_addr = 0; reg_addr < 128; reg_addr += 4)
	{
                WDCN_bit.RWT = 1;                                                       //reset watchdog timer
		read_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_PMIC_I2C_ADDR, reg_addr, 4, &I2C_Slave_Buffer_A2_P84H_Up[reg_addr]);
	}
        
        tx_i2c_master_data[0] = 0x00;
	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_PASSTHROUGH_EN, 1, &tx_i2c_master_data[0]);
       
#endif
}

uint16_t tx_cdr_init(uint8_t flag)
{
#if __SFP28_ER_SEMI_TUNABLE__ == 1

#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
  // GN_1157
  
	uint8_t	xdata rVal;
	uint8_t	xdata reg_addr;
//        uint8_t read_val[18];
//	uint8_t * xdata flash_memory;
//        uint8_t rate_select;
//	uint8_t device_id;
        uint16_t ret_val;
//        int idx;

	// Check TX CDR Communication: Read CHIPID: 0x89 default.
	rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_ID);
	if (rVal != GN_1157_CHIPID)
	{
		ret_val = SFP28_MODULE_STATE_FAULT;
		return ret_val;
	}
                
        ret_val = 0;

        // Set TX Driver Registers
        // P00_CR2
        memset(&tx_i2c_master_data[0],0x00,16);
        
//	// TX_Mode
//        reg_addr = P00_CR2;
//        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
//
//
//        tx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1];
//	if (flag == 0) {
//		// Power Down Off
//		tx_i2c_master_data[1] = tx_i2c_master_data[1] & 0xDF; // 0x00; // start Addr: 0x3E
//	}
//	else if (flag == 1) {
//		// Power Down Set
//		tx_i2c_master_data[1] = tx_i2c_master_data[1] | 0x20; // 0x00; // start Addr: 0x3E
//	}
//	else {
//		// Power Down Off
//		tx_i2c_master_data[1] = tx_i2c_master_data[1] & 0xDF; // 0x00; // start Addr: 0x3E
//	}
//
//        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = tx_i2c_master_data[1];        
//        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_CR2, 2, &tx_i2c_master_data[0]);
        

	// P00_LDD_EYE_OPTIMIZE
        reg_addr = P00_LDD_EYE_OPTIMIZE;
        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
//        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];        
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_LDD_EYE_OPTIMIZE, 1, &tx_i2c_master_data[0]);
        
        // P00_TX_RATE_SELECT
        reg_addr = P00_TX_RATE_SELECT;
        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
//        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = tx_i2c_master_data[1];        
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_TX_RATE_SELECT, 1, &tx_i2c_master_data[0]);
        
        // P00_ISNK_MAX
        reg_addr = P00_ISNK_MAX;
        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
//        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+2] = tx_i2c_master_data[2];        
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_ISNK_MAX, 1, &tx_i2c_master_data[0]);

        // P00_APC_WINDOW
        reg_addr = P00_APC_WINDOW;
        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
//        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+3] = tx_i2c_master_data[3];        
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_APC_WINDOW, 1, &tx_i2c_master_data[0]);

        // P00_APC_MODE
        reg_addr = P00_APC_MODE;
        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
//        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+4] = tx_i2c_master_data[4];        
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_APC_MODE, 1, &tx_i2c_master_data[0]);

//        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_LDD_EYE_OPTIMIZE, 5, &tx_i2c_master_data[0]);
                
        // P00_VEQ_DAC
        reg_addr = P00_VEQ_DAC;
        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
//        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];        
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_VEQ_DAC, 1, &tx_i2c_master_data[0]);
        
        // P00_BIAS_TCA_DAC
        reg_addr = P00_BIAS_TCA_DAC;
        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
//        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = tx_i2c_master_data[1];        
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_BIAS_TCA_DAC, 1, &tx_i2c_master_data[0]);

        // P00_MON_TCA_DAC
        reg_addr = P00_MON_TCA_DAC;
        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
//        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+2] = tx_i2c_master_data[2];        
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_MON_TCA_DAC, 1, &tx_i2c_master_data[0]);

        // P00_VF_TCA_DAC
        reg_addr = P00_VF_TCA_DAC;
        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
//        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+3] = tx_i2c_master_data[3];        
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_VF_TCA_DAC, 1, &tx_i2c_master_data[0]);
////
//        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_VEQ_DAC, 4, &tx_i2c_master_data[0]);

        // P00_VSET_DAC (MSB)
        reg_addr = P00_VSET_DAC;
        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
//        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];        
        
        // P00_VSET_DAC_LSB
        tx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1];
//        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = tx_i2c_master_data[1];        

        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_VSET_DAC, 2, &tx_i2c_master_data[0]);

	// TX_Mode
        reg_addr = P00_CR2;
        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_CR2, 1, &tx_i2c_master_data[0]);

        reg_addr = P00_CR1;

        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
	if (flag == 0) {
		// Power Down Off
		tx_i2c_master_data[0] = tx_i2c_master_data[0] & 0xDF; // 0x00; // start Addr: 0x3E
	}
	else if (flag == 1) {
		// Power Down Set
		tx_i2c_master_data[0] = tx_i2c_master_data[0] | 0x20; // 0x00; // start Addr: 0x3E
	}
	else {
		// Power Down Off
		tx_i2c_master_data[0] = tx_i2c_master_data[0] & 0xDF; // 0x00; // start Addr: 0x3E
	}

        tx_i2c_master_data[0] = 0x81;
        
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
        
//        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_CR2, 2, &tx_i2c_master_data[0]);
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_CR1, 1, &tx_i2c_master_data[0]);
        
        return ret_val;

#else
        
	uint8_t	xdata rVal;
	uint8_t	xdata reg_addr;
//        uint8_t read_val[18];
//	uint8_t * xdata flash_memory;
//        uint8_t rate_select;
//	uint8_t device_id;
        uint16_t ret_val;

	// Check TX CDR Communication: Read CHIPID: 0x89 default.
	rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_CHIPID);
	if (rVal != MAOM_37030B_CHIPID)
	{
		ret_val = SFP28_MODULE_STATE_FAULT;
		return ret_val;
	}

	// Set TX CDR Registers
        
//        reg_addr = P00_LB_MISCL;
//        // LB_MISCL = 0xC2
//        // nonfc_mode([7]=1), txfault_op_type([6]=1, CMOS), rxlos_op_type([1]=1, CMOS)
//        // 
//        // MISC
//        // start_op ([1]=1, start operation
//        // dc_los_sel([0]=1, RX LOS comes from DC LOS (GPADC/RSSI pin usually connects to external TIA RSSI current)
//        
//        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
//        tx_i2c_master_data[0] &= 0xF3; // Disable loopbacks
//        
//        tx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1];
//        
//        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_LB_MISCL, 1, &tx_i2c_master_data[0]);
        
        reg_addr = P00_LB_MISCL;
        // LB_MISCL = 0xC2
        // nonfc_mode([7]=1), txfault_op_type([6]=1, CMOS), rxlos_op_type([1]=1, CMOS)
        // 
        // MISC
        // start_op ([1]=1, start operation
        // dc_los_sel([0]=1, RX LOS comes from DC LOS (GPADC/RSSI pin usually connects to external TIA RSSI current)
        
        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] | 0x80;
        tx_i2c_master_data[0] &= 0xF3; // Disable loopbacks
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
        
//        tx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] | 0x02;
//        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = tx_i2c_master_data[1];
//        
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_LB_MISCL, 1, &tx_i2c_master_data[0]);
        
// P00_Global_Bias3, 20.10.09. Tx Shaping
        reg_addr = P00_Global_Bias3;        
        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];        
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_Global_Bias3, 1, &tx_i2c_master_data[0]);
        
        memset(&tx_i2c_master_data[0],0x00,16);
        
	// TX_Mode
        reg_addr = P00_TX_MODES;
        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];

	if (flag == 0) {
		// Power Down Off
		tx_i2c_master_data[0] = tx_i2c_master_data[0] & 0x7F; // 0x00; // start Addr: 0x30
	}
	else if (flag == 1) {
		// Power Down Set
		tx_i2c_master_data[0] = tx_i2c_master_data[0] | 0x80; // 0x00; // start Addr: 0x30
	}
	else {
		// Power Down Off
		tx_i2c_master_data[0] = tx_i2c_master_data[0] & 0x7F; // 0x00; // start Addr: 0x30
	}

        // Rate Select: 200722 -->

        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
 
	// TX_ADAPT_EQ
        tx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1]; // Addr: 0x21
        
	// LOS THRS
        tx_i2c_master_data[2] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+2]; // Addr: 0x22


	// TX_CDRLBW
        tx_i2c_master_data[4] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+4]; // Addr: 0x24
        
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_TX_MODES, 3, &tx_i2c_master_data[0]);

//	// TX_CDR_MISCL
//	tx_i2c_master_data[5] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+5]; // Addr: 0x25
//
//	// LD_CTRL0
//	tx_i2c_master_data[7] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+7]; // Addr: 0x27
//
//	// TIA_CTRL0
//        tx_i2c_master_data[8] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+8]; // Addr: 0x28
//
//	// TIA_CTRL1
//	tx_i2c_master_data[9] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+9]; // Addr: 0x29
//        
//	// TIA_CTRL2
//	tx_i2c_master_data[10] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+10]; // Addr: 0x2A
//        
//	// PD_LDD_CTRL
//	tx_i2c_master_data[11] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+11]; // Addr: 0x2B
//        
//	// OPMODE_CTRL
//	tx_i2c_master_data[12] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+12]; // Addr: 0x2C
//        
//	// PAVG_TARGET
//	tx_i2c_master_data[13] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+13];  // Addr: 0x2D
//        
// 	// APC_CTRL0
//	tx_i2c_master_data[14] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+14]; // Addr: 0x2E
//        
// 	// APC_CTRL1
//	tx_i2c_master_data[15] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+15]; // Addr: 0x2F
//        
//        // Undefined Registers
//        tx_i2c_master_data[3] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+3]; // Addr: 0x23
//        tx_i2c_master_data[6] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+6]; // Addr: 0x26
//
//                  
//        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_TX_MODES, 16, &tx_i2c_master_data[0]);
        
        // From APC_CTRL2
//        memset(&tx_i2c_master_data[0],0,16);
//        
//        reg_addr = P00_APC_CTRL2;
//
//        // APC_CTRL2
//	tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0]; // Addr: 0x30
//
//	// APC_CTRL3
//	tx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1]; // Addr: 0x31
//        
//	// APC_CTRL4
//	tx_i2c_master_data[2] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+2]; // Addr: 0x32
//
//                  
//        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_APC_CTRL2, 3, &tx_i2c_master_data[0]);
//        
//
//        // From BIAS_LIMIT
//        reg_addr = P00_BIAS_LIMIT;
//
//        // BIAS_LIMIT
//	tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0]; // Addr: 0x3C
//
//	// MOD_LIMIT
//	tx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1]; // Addr: 0x3D
//        
//        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_BIAS_LIMIT, 2, &tx_i2c_master_data[0]);
        
	// LD_DRV_CTRL0
        reg_addr = P00_LD_DRV_CTRL0;
	tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0]; // Addr: 0x3E
        
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_DRV_CTRL0, 1, &tx_i2c_master_data[0]);
        
        // From LD_DRV_CTRL2
        reg_addr = P00_LD_DRV_CTRL2;        

        // LD_DRV_CTRL2
	tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0]; // Addr: 0x40

	// LD_DRV_CTRL3
	tx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1]; // Addr: 0x41
        
	// LD_DRV_CTRL4
	tx_i2c_master_data[2] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+2]; // Addr: 0x42
                  
	// LD_DRV_CTRL5
	tx_i2c_master_data[3] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+3]; // Addr: 0x43
        
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_DRV_CTRL2, 4, &tx_i2c_master_data[0]);
//                  
//	// DATA_OK
//	tx_i2c_master_data[5] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+5]; // Addr: 0x45
//                  
//	// STROBE
//	tx_i2c_master_data[6] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+6]; // Addr: 0x46
//                                   
//        // Undefined Register
//        tx_i2c_master_data[4] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+4]; // Addr: 0x44
//        
//        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_DRV_CTRL2, 7, &tx_i2c_master_data[0]);
        
//        reg_addr = P00_LB_MISCL;
        // LB_MISCL = 0xC2
        // nonfc_mode([7]=1), txfault_op_type([6]=1, CMOS), rxlos_op_type([1]=1, CMOS)
        // 
        // MISC
        // start_op ([1]=1, start operation
        // dc_los_sel([0]=1, RX LOS comes from DC LOS (GPADC/RSSI pin usually connects to external TIA RSSI current)
        
//        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] | 0x80;
//        tx_i2c_master_data[0] &= 0xF3; // Disable loopbacks
//        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
        
        reg_addr = P00_MISC;
        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] | 0x02;
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = tx_i2c_master_data[0];
        
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_MISC, 1, &tx_i2c_master_data[0]);
        
	return ret_val;
        
#endif

#else
//	uint8_t	xdata rVal, tVal;
	uint8_t	xdata rVal;
	uint16_t ret_val = 0;

	// Check TX CDR Communication: Read CHIPID: 0x89 default.
	rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_CHIPID);
	if (rVal != MAOM_37030B_CHIPID)
	{
		ret_val = SFP28_MODULE_STATE_FAULT;
		return ret_val;
	}

	// Set TX CDR Registers
	// Mode
	if (flag == 0) {
		// Power Down Off
		tx_i2c_master_data[0] = 0x00; // start Addr: 0x30
	}
	else if (flag == 1) {
		// Power Down Set
		tx_i2c_master_data[0] = 0xA0; // start Addr: 0x30
		write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_TX_MODES, 1, &tx_i2c_master_data[0]);
		return ret_val;
	}
	else {
		// Power Down Off
		tx_i2c_master_data[0] = 0x00; // start Addr: 0x30
	}

	// LOS LOL MASK CH
	tx_i2c_master_data[1] = 0x00; // Addr: 0x31

	// LOS THRS
	tx_i2c_master_data[2] = 0x04; // Addr: 0x32

	// CTLE
	tx_i2c_master_data[3] = 0x10; // Addr: 0x33

	// OUTPUT Swing
	tx_i2c_master_data[4] = 0x20; // Addr: 0x34

	// OUTPUT DE-EMPHASIS
	tx_i2c_master_data[5] = 0x00; // Addr: 0x35

	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_TX_MODES, 1, &tx_i2c_master_data[0]);
        
	return ret_val;
#endif
}

uint16_t tx_cdr_init_from_flash(uint8_t flag)
{
#if __SFP28_ER_SEMI_TUNABLE__ == 1

#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
  // GN_1157
  
	uint8_t	xdata rVal;
	uint8_t	xdata reg_addr;
        uint8_t read_val[24];
	uint8_t * xdata flash_memory;
//        uint8_t rate_select;
	uint8_t device_id;
        uint16_t ret_val = 0;
        int idx;

	// Check TX CDR Communication: Read CHIPID: 0x89 default.
	rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_ID);
	if (rVal != GN_1157_CHIPID)
	{
		ret_val = SFP28_MODULE_STATE_FAULT;
		return ret_val;
	}

	flash_memory = (uint8_t *)(FLASH_PAGE82H_START);
        
  FLASH_Read((unsigned int)(&read_val[0]), (unsigned int)flash_memory, 2);

  device_id = read_val[1];
//	device_revid = read_val[1];

	if (device_id != (uint8_t)GN_1157_CHIPID)
	{
    ret_val = SFP28_MODULE_STATE_FAULT;
    return ret_val;
  }        

        // P00_VCPA_DAC ~ P00_VSET_DAC
  reg_addr = P00_VCPA_DAC;
	flash_memory = (uint8_t *)(FLASH_PAGE82H_START+reg_addr);
  FLASH_Read((unsigned int)(&read_val[0]), (unsigned int)flash_memory, 12);
  
  for (idx = 0; idx < 11; idx++)
  {
    I2C_Slave_Buffer_A2_P82H_Up[reg_addr+idx] = read_val[idx];
  }

  // P00_RX_RATE_SELECT
//        reg_addr = P00_RX_RATE_SELECT;
  reg_addr = P00_RSVD_6;
	flash_memory = (uint8_t *)(FLASH_PAGE82H_START+reg_addr);
  FLASH_Read((unsigned int)(&read_val[0]), (unsigned int)flash_memory, 4);
  
  I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = read_val[1];
  I2C_Slave_Buffer_A2_P82H_Up[reg_addr+2] = read_val[2];
//        for (idx = 0; idx < 2; idx++)
//        {
//          I2C_Slave_Buffer_A2_P82H_Up[reg_addr+idx] = read_val[idx];
//        }

        // P00_ADC_1 ~ P00_EXT_RX_PWR_LOS_THRESHOLD, P00_RSVD_8
//        reg_addr = P00_ADC_1;
  reg_addr = P00_RSVD_8;
	flash_memory = (uint8_t *)(FLASH_PAGE82H_START+reg_addr);
  FLASH_Read((unsigned int)(&read_val[0]), (unsigned int)flash_memory, 8);
  
  for (idx = 0; idx < 7; idx++)
  {
    I2C_Slave_Buffer_A2_P82H_Up[reg_addr+idx] = read_val[idx];
  }
  
  // P00_LOS_VBE_DAC ~ P00_RX_CONTROL_2
  reg_addr = P00_LOS_VBE_DAC;
	flash_memory = (uint8_t *)(FLASH_PAGE82H_START+reg_addr);
  FLASH_Read((unsigned int)(&read_val[0]), (unsigned int)flash_memory, 4);
  
  for (idx = 0; idx < 4; idx++)
  {
    I2C_Slave_Buffer_A2_P82H_Up[reg_addr+idx] = read_val[idx];
  }

        // P00_LDD_EYE_OPTIMIZE ~ P00_APC_MODE
//        reg_addr = P00_LDD_EYE_OPTIMIZE;
  reg_addr = P00_RSVD_12;
	flash_memory = (uint8_t *)(FLASH_PAGE82H_START+reg_addr);
  FLASH_Read((unsigned int)(&read_val[0]), (unsigned int)flash_memory, 6);
  
  for (idx = 0; idx < 6; idx++)
  {
    I2C_Slave_Buffer_A2_P82H_Up[reg_addr+idx] = read_val[idx];
  }

  // P00_CR2 ~ P00_CR1, P00_RSVD_13
//        reg_addr = P00_CR2;
  reg_addr = P00_RSVD_13;
	flash_memory = (uint8_t *)(FLASH_PAGE82H_START+reg_addr);
  FLASH_Read((unsigned int)(&read_val[0]), (unsigned int)flash_memory, 4);
  
  for (idx = 0; idx < 3; idx++)
  {
    I2C_Slave_Buffer_A2_P82H_Up[reg_addr+idx] = read_val[idx];
  }
  return ret_val;
        
#else
	uint8_t	xdata rVal;
	uint8_t	xdata reg_addr;
        uint8_t read_val[18];
	uint8_t * xdata flash_memory;
//        uint8_t rate_select;
	uint8_t device_id;
        uint16_t ret_val;

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
// P00_Global_Bias3
        reg_addr = P00_Global_Bias3;
	flash_memory = (uint8_t *)(FLASH_PAGE82H_START+reg_addr);
        FLASH_Read((unsigned int)(&read_val[0]), (unsigned int)flash_memory, 2);
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = read_val[0];
        
#if 0
	// Set TX CDR Registers
        
        reg_addr = P00_LB_MISCL;
        // LB_MISCL = 0xC2
        // nonfc_mode([7]=1), txfault_op_type([6]=1, CMOS), rxlos_op_type([1]=1, CMOS)
        // 
        // MISC
        // start_op ([1]=1, start operation
        // dc_los_sel([0]=1, RX LOS comes from DC LOS (GPADC/RSSI pin usually connects to external TIA RSSI current)

	flash_memory = (uint8_t *)(FLASH_PAGE82H_START+reg_addr);
        FLASH_Read((unsigned int)(&read_val[0]), (unsigned int)flash_memory, 2);
        read_val[0] &= 0xF3; // Disable loopbacks
        read_val[0] |= 0x80;
        read_val[1] |= 0x02;
//        read_val[0] = 0x80;
//        read_val[1] = 0x02;
//        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_LB_MISCL, 2, &read_val[0]);
//        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_LB_MISCL, 2, &read_val[0]);
        
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = read_val[0];
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = read_val[1];

#endif
        
        memset(&read_val[0],0,16);
        
	// TX_Mode
        reg_addr = P00_TX_MODES;
	flash_memory = (uint8_t *)(FLASH_PAGE82H_START+reg_addr);
        FLASH_Read((unsigned int)(&read_val[0]), (unsigned int)flash_memory, 8);
//        read_val[0] = 0x40;

	if (flag == 0) {
		// Power Down Off
		tx_i2c_master_data[0] = read_val[0] & 0x7F; // 0x00; // start Addr: 0x30
	}
	else if (flag == 1) {
		// Power Down Set
		tx_i2c_master_data[0] = read_val[0] | 0x80; // 0x00; // start Addr: 0x30
	}
	else {
		// Power Down Off
		tx_i2c_master_data[0] = read_val[0] & 0x7F; // 0x00; // start Addr: 0x30
	}

        // Rate Select: 200722 -->

        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];

	// TX_ADAPT_EQ
	tx_i2c_master_data[1] = read_val[1]; // 0x00; // Addr: 0x21
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = tx_i2c_master_data[1];

        
	// LOS THRS
	tx_i2c_master_data[2] = read_val[2]; // 0x04; // Addr: 0x22
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+2] = tx_i2c_master_data[2];

	// TX_CDRLBW
	tx_i2c_master_data[4] = read_val[4]; // 0x10; // Addr: 0x24
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+4] = tx_i2c_master_data[4];

	// TX_CDR_MISCL
	tx_i2c_master_data[5] = read_val[5]; // 0x20; // Addr: 0x25
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+5] = tx_i2c_master_data[5];

#if 0
	// LD_CTRL0
	tx_i2c_master_data[7] = read_val[7]; // 0x00; // Addr: 0x27
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+7] = tx_i2c_master_data[7];

	// TIA_CTRL0
	tx_i2c_master_data[8] = read_val[8]; // 0x00; // Addr: 0x28
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+8] = tx_i2c_master_data[8];

	// TIA_CTRL1
	tx_i2c_master_data[9] = read_val[9]; // 0x00; // Addr: 0x29
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+9] = tx_i2c_master_data[9];
        
	// TIA_CTRL2
	tx_i2c_master_data[10] = read_val[10]; // 0x00; // Addr: 0x2A
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+10] = tx_i2c_master_data[10];
        
	// PD_LDD_CTRL
	tx_i2c_master_data[11] = read_val[11]; // 0x00; // Addr: 0x2B
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+11] = tx_i2c_master_data[11];
        
	// OPMODE_CTRL
	tx_i2c_master_data[12] = read_val[12]; // 0x00; // Addr: 0x2C
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+12] = tx_i2c_master_data[12];
        
	// PAVG_TARGET
	tx_i2c_master_data[13] = read_val[13]; // 0x00; // Addr: 0x2D
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+13] = tx_i2c_master_data[13];
        
 	// APC_CTRL0
	tx_i2c_master_data[14] = read_val[14]; // 0x00; // Addr: 0x2E
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+14] = tx_i2c_master_data[14];
        
 	// APC_CTRL1
	tx_i2c_master_data[15] = read_val[15]; // 0x00; // Addr: 0x2F
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+15] = tx_i2c_master_data[15];
                  
//        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_TX_MODES, 16, &tx_i2c_master_data[0]);
//        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_TX_MODES, 1, &tx_i2c_master_data[0]);
        
        // From APC_CTRL2
        reg_addr = P00_APC_CTRL2;
	flash_memory = (uint8_t *)(FLASH_PAGE82H_START+reg_addr);
        FLASH_Read((unsigned int)(&read_val[0]), (unsigned int)flash_memory, 3);

        // APC_CTRL2
	tx_i2c_master_data[0] = read_val[0]; // 0x00; // Addr: 0x30
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];

	// APC_CTRL3
	tx_i2c_master_data[1] = read_val[1]; // 0x00; // Addr: 0x31
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = tx_i2c_master_data[1];

        
	// APC_CTRL4
	tx_i2c_master_data[2] = read_val[2]; // 0x04; // Addr: 0x32
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+2] = tx_i2c_master_data[2];

                  
//        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_APC_CTRL2, 3, &tx_i2c_master_data[0]);
        

        // From BIAS_LIMIT
        reg_addr = P00_BIAS_LIMIT;
	flash_memory = (uint8_t *)(FLASH_PAGE82H_START+reg_addr);
        FLASH_Read((unsigned int)(&read_val[0]), (unsigned int)flash_memory, 2);
//
//        // BIAS_LIMIT
	tx_i2c_master_data[0] = read_val[0]; // 0x00; // Addr: 0x3C
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
//
//	// MOD_LIMIT
	tx_i2c_master_data[1] = read_val[1]; // 0x00; // Addr: 0x3D
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = tx_i2c_master_data[1];
        
#endif
        

        
        // From LD_DRV_CTRL0
        reg_addr = P00_LD_DRV_CTRL0;
	flash_memory = (uint8_t *)(FLASH_PAGE82H_START+reg_addr);
        FLASH_Read((unsigned int)(&read_val[0]), (unsigned int)flash_memory, 2);
//
//        
//	// LD_DRV_CTRL0
	tx_i2c_master_data[0] = read_val[0]; // 0x04; // Addr: 0x3E
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
//        
//        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_BIAS_LIMIT, 3, &tx_i2c_master_data[0]);
//        
        

//        // From LD_DRV_CTRL2
        reg_addr = P00_LD_DRV_CTRL2;
	flash_memory = (uint8_t *)(FLASH_PAGE82H_START+reg_addr);
        FLASH_Read((unsigned int)(&read_val[0]), (unsigned int)flash_memory, 4);
//        
//
//        // LD_DRV_CTRL2
	tx_i2c_master_data[0] = read_val[0]; // 0x00; // Addr: 0x40
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
//
//	// LD_DRV_CTRL3
	tx_i2c_master_data[1] = read_val[1]; // 0x00; // Addr: 0x41
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = tx_i2c_master_data[1];
//
//        
//	// LD_DRV_CTRL4
	tx_i2c_master_data[2] = read_val[2]; // 0x04; // Addr: 0x42
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+2] = tx_i2c_master_data[2];
//                  
//	// LD_DRV_CTRL5
	tx_i2c_master_data[3] = read_val[3]; // 0x04; // Addr: 0x43
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+3] = tx_i2c_master_data[3];
        

        
////                  
////	// DATA_OK
//	tx_i2c_master_data[5] = read_val[5]; // 0x04; // Addr: 0x45
//        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+5] = tx_i2c_master_data[5];
////                  
////	// STROBE
//	tx_i2c_master_data[6] = read_val[6]; // 0x04; // Addr: 0x46
//        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+6] = tx_i2c_master_data[6];
        
#if 0        
#endif
        
//        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_DRV_CTRL2, 7, &tx_i2c_master_data[0]);
//        
	return ret_val;
        
//        <-- ST-SFP28 
#endif // end of #if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
        
#else
        return 0;
#endif
}


//.Supply 3.3V to MALD-37030 and allow sufficient time for the power supply voltage to cross above the POR threshold
//.Write 0x27 = 04h; soft TX disable
//.Write 0x05 = 01h; Initialize communications with power management circuitry
//.Write configuration data to power management circuitry at I2C address 4Fh. 1.8V buck should be enabled (4Fh.0x06[7] = 1b) but laser anode buck-boost should be disabled (4Fh.0x07[0] = 0b)
//.Write 0x05 = 00h; Terminate communications with power management circuitry
//.Write configuration data to TX and RX channels at I2C address 4Ch
//.Write 0x05 = 01h; Initialize communications with power management circuitry
//.Enable laser anode buck-boost (4Fh.0x07[0] = 1b)
//.Write 0x05 = 00h; Terminate communications with power management circuitry
//.Write 0x27[2] = 0b; Enable TX

uint16_t cdr_power_management_init(uint8_t flag)
{
#if __SFP28_ER_SEMI_TUNABLE__ == 1
  
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
  // GN_1157
//	uint8_t	xdata rVal, tVal;
	uint8_t	xdata rVal,  reg_addr;
	uint16_t ret_val = 0;

	// Check CDR Communication: Read CHIPID: 0xC4 default.
	rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_ID);
	if (rVal != GN_1157_CHIPID)
	{
		ret_val = SFP28_MODULE_STATE_FAULT;
		return ret_val;
	}
        
        // Reset CDR
        reg_addr = P00_CR1;
        rVal = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
//        rVal &= 0x7F;
//        tx_i2c_master_data[0] = rVal;
        tx_i2c_master_data[0] = 0x01;
	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_CR1, 1, &tx_i2c_master_data[0]);
        SW_Delay(100);
//        tx_i2c_master_data[0] |= 0x80;
        tx_i2c_master_data[0] = 0x81;
	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_CR1, 1, &tx_i2c_master_data[0]);
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
        SW_Delay(100);
  
#else
//	uint8_t	xdata rVal, tVal;
	uint8_t	xdata rVal,  reg_addr;
	uint16_t ret_val = 0;

	// Check TX CDR Communication: Read CHIPID: 0x89 default.
	rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_CHIPID);
	if (rVal != MAOM_37030B_CHIPID)
	{
		ret_val = SFP28_MODULE_STATE_FAULT;
		return ret_val;
	}
        
        // Reset CDR
        reg_addr = P00_RESET;
        rVal = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
        rVal = 0xAA;
        tx_i2c_master_data[0] = rVal;
	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_RESET, 1, &tx_i2c_master_data[0]);
        SW_Delay(100);
        tx_i2c_master_data[0] = 0x00;
	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_RESET, 1, &tx_i2c_master_data[0]);
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
        SW_Delay(100);
        
                
        // soft TX disable
//	rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_LD_CTRL0);
        reg_addr = P00_LD_CTRL0;
        rVal = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
        rVal = rVal | 0x04;
        tx_i2c_master_data[0] = rVal;
	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_LD_CTRL0, 1, &tx_i2c_master_data[0]);
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
        
//        SW_Delay(100);
        
        // Read/write to PMIC register
        tx_i2c_master_data[0] = 0x01;
	confirm_write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_PASSTHROUGH_EN, 1, &tx_i2c_master_data[0]);
        I2C_Slave_Buffer_A2_P82H_Up[P00_PASSTHROUGH_EN] = tx_i2c_master_data[0];
        SW_Delay(100);
        
        // Reset PMIC
        reg_addr = P00_RESET;
        rVal = I2C_Slave_Buffer_A2_P84H_Up[reg_addr+0];
        rVal = 0xAA;
        tx_i2c_master_data[0] = rVal;
	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_PMIC_I2C_ADDR, P00_RESET, 1, &tx_i2c_master_data[0]);
        SW_Delay(100);
        tx_i2c_master_data[0] = 0x00;
	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_PMIC_I2C_ADDR, P00_RESET, 1, &tx_i2c_master_data[0]);
        I2C_Slave_Buffer_A2_P84H_Up[reg_addr+0] = tx_i2c_master_data[0];
        SW_Delay(10);

        
        // PMIC, Enable 1.8V (0x06[7] = 1b) and disable laser anode buck-boost (0x07[0] = 0b
//	read_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_PMIC_I2C_ADDR, P01_PMIC_USR1, 2, &tx_i2c_master_data[0]);        
        reg_addr = P01_PMIC_USR1;
        rVal = I2C_Slave_Buffer_A2_P84H_Up[reg_addr+0];
//        rVal = tx_i2c_master_data[0];
//        tx_i2c_master_data[0] = rVal | 0x80;
        tx_i2c_master_data[0] = 0x80;
        I2C_Slave_Buffer_A2_P84H_Up[reg_addr+0] = tx_i2c_master_data[0];
        
//        rVal = tx_i2c_master_data[1];
        rVal = I2C_Slave_Buffer_A2_P84H_Up[reg_addr+1];
//        tx_i2c_master_data[1] = rVal & 0xFE;
        tx_i2c_master_data[1] = 0x00;
        I2C_Slave_Buffer_A2_P84H_Up[reg_addr+1] = tx_i2c_master_data[1];
        
	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_PMIC_I2C_ADDR, P01_BUCK_BOOST_USR0, 1, &tx_i2c_master_data[1]);
        SW_Delay(10);
         
	confirm_write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_PMIC_I2C_ADDR, P01_PMIC_USR1, 1, &tx_i2c_master_data[0]);
        SW_Delay(10);
       
        // Read/write to RF register
        tx_i2c_master_data[0] = 0x00;
	confirm_write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_PASSTHROUGH_EN, 1, &tx_i2c_master_data[0]);
        I2C_Slave_Buffer_A2_P82H_Up[P00_PASSTHROUGH_EN] = tx_i2c_master_data[0];

        // TX&RX CDR Initialization
        ret_val = tx_cdr_init(flag);
        if (ret_val != 0)
        {
          return (ret_val);
        }
        SW_Delay(100);
        
        ret_val = rx_cdr_init(flag);
        if (ret_val != 0)
        {
          return (ret_val);
        }
         SW_Delay(100);
       
        // Read/write to PMIC register
        tx_i2c_master_data[0] = 0x01;
	confirm_write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_PASSTHROUGH_EN, 1, &tx_i2c_master_data[0]);
        SW_Delay(10);
        
        //.Enable laser anode buck-boost (4Fh.0x07[0] = 1b)
//        rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_PMIC_I2C_ADDR, P01_BUCK_BOOST_USR0);
//        tx_i2c_master_data[0] = rVal | 0x01;         
        tx_i2c_master_data[0] = 0x21;         
	confirm_write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_PMIC_I2C_ADDR, P01_BUCK_BOOST_USR0, 1, &tx_i2c_master_data[0]);
        I2C_Slave_Buffer_A2_P84H_Up[P01_BUCK_BOOST_USR0] = tx_i2c_master_data[0];
        SW_Delay(10);
//	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_PMIC_I2C_ADDR, P01_BUCK_BOOST_USR0, 1, &tx_i2c_master_data[0]);
//        SW_Delay(10);
        
        tx_i2c_master_data[0] = 0x80;         
	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_PMIC_I2C_ADDR, P01_FAIL_CTRL, 1, &tx_i2c_master_data[0]);
        I2C_Slave_Buffer_A2_P84H_Up[P01_FAIL_CTRL] = tx_i2c_master_data[0];
        
        // [DCLEE] 20.10.09. -->
#if __RLASER_TRIM_11_OHM__==1
        //        tx_i2c_master_data[0] = 0x07;         // <-- 18 ��
        tx_i2c_master_data[0] = 0x00;         // <-- 13 ��
#elif __RLASER_TRIM_13_OHM__==1
        //        tx_i2c_master_data[0] = 0x07;         // <-- 18 ��
        tx_i2c_master_data[0] = 0x02;         // <-- 13 ��
#elif __RLASER_TRIM_18_OHM__==1
        //        tx_i2c_master_data[0] = 0x07;         // <-- 18 ��
        tx_i2c_master_data[0] = 0x07;         // <-- 13 ��
#endif
        
	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_PMIC_I2C_ADDR, P01_TRIM_BYTE4, 1, &tx_i2c_master_data[0]);
        I2C_Slave_Buffer_A2_P84H_Up[P01_TRIM_BYTE4] = tx_i2c_master_data[0];
        
        SW_Delay(10);
        
        // Read/write to RF register
        tx_i2c_master_data[0] = 0x00;
	confirm_write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_PASSTHROUGH_EN, 1, &tx_i2c_master_data[0]);

        SW_Delay(10);
        // soft TX Enable
//	rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_LD_CTRL0);
//        rVal = rVal & 0xFB;
//        tx_i2c_master_data[0] = rVal;
        reg_addr = P00_LD_CTRL0;
        rVal = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
//        rVal = rVal & 0xFB;
        rVal = 0xCA;
        tx_i2c_master_data[0] = rVal;
 	confirm_write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_LD_CTRL0, 1, &tx_i2c_master_data[0]);
        SW_Delay(10);
// 	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_LD_CTRL0, 1, &tx_i2c_master_data[0]);
//        SW_Delay(10);

#endif
#endif
        
	return ret_val;
}

#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
void reset_gn1157()
{
  INT_RSTB = 0; // Reset Normal
  SW_Delay(1000); // [DCLEE] 21.01.29. <-- ���Ŀ� �ð��� ���� �ʿ� ����. ���� ���ؼ� ����
  INT_RSTB = 1; // Reset Normal
}

#endif

uint16_t cdr_pmic_ch_control_reinit(uint8_t flag)
{
#if __SFP28_ER_SEMI_TUNABLE__ == 1
	uint16_t ret_val = 0;
  
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
        // GN_1157
        // Reset GN1157
        PLA_Soft_TXD_Control(ASSERTED);
        
        reset_gn1157();
        

        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[P00_CR1];  
        tx_i2c_master_data[0] &= 0x7F;
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_CR1, 1, &tx_i2c_master_data[0]);
        
        SW_Delay(100);
        tx_i2c_master_data[0] |= 0x80;
        I2C_Slave_Buffer_A2_P82H_Up[P00_CR1] = tx_i2c_master_data[0];
        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_CR1, 1, &tx_i2c_master_data[0]);
        
        SW_Delay(10);
        // APC Mode disable
//        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[P00_CR1];  
        tx_i2c_master_data[0] = tx_i2c_master_data[0] & (0xF7);
//        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_CR1, 1, &tx_i2c_master_data[0]);
        I2C_Slave_Buffer_A2_P82H_Up[P00_CR1] = tx_i2c_master_data[0];

        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[P00_CR1];  
        tx_i2c_master_data[0] = tx_i2c_master_data[0] & 0xBF;
        I2C_Slave_Buffer_A2_P82H_Up[P00_CR1] = tx_i2c_master_data[0];        
//        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_CR1, 1, &tx_i2c_master_data[0]);

        
//        LdBiasSetFlag2 = 1;
//        LdControl(0, 0);
        
        tx_cdr_init(0);
        rx_cdr_init(0);
        
        update_rate_select_operation();

        // TX_DIS: normal op (0)
//        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[P00_CR1];  
//        tx_i2c_master_data[0] &= 0xBF;
//        I2C_Slave_Buffer_A2_P82H_Up[P00_CR1] = tx_i2c_master_data[0];        
//        write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_CR1, 1, &tx_i2c_master_data[0]);

        LdBiasSetFlag2 = 1;
        LdControl(0, 0);

        PLA_Soft_TXD_Control(DE_ASSERTED);

//        tx_cdr_init(0);
//        rx_cdr_init(0);

#else

	uint8_t	xdata rVal,  reg_addr;
	uint16_t ret_val = 0;

	// Check TX CDR Communication: Read CHIPID: 0x89 default.
	rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_CHIPID);
	if (rVal != MAOM_37030B_CHIPID)
	{
		ret_val = SFP28_MODULE_STATE_FAULT;
		return ret_val;
	}
        
        // Reset CDR --> Skip
        reg_addr = P00_RESET;
//        rVal = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
//        rVal = 0xAA;
//        tx_i2c_master_data[0] = rVal;
//	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_RESET, 1, &tx_i2c_master_data[0]);
//        SW_Delay(100);
        tx_i2c_master_data[0] = 0x00;
	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_RESET, 1, &tx_i2c_master_data[0]);
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
//        SW_Delay(100);
        
                
        // soft TX disable
//	rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_LD_CTRL0);
        reg_addr = P00_LD_CTRL0;
        rVal = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
        rVal = rVal | 0x04;
        tx_i2c_master_data[0] = rVal;
	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_LD_CTRL0, 1, &tx_i2c_master_data[0]);
        I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
        
//        SW_Delay(100);
        
        // Read/write to PMIC register
        tx_i2c_master_data[0] = 0x01;
	confirm_write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_PASSTHROUGH_EN, 1, &tx_i2c_master_data[0]);
        I2C_Slave_Buffer_A2_P82H_Up[P00_PASSTHROUGH_EN] = tx_i2c_master_data[0];
        SW_Delay(100);
        
        // Reset PMIC --> Skip
        reg_addr = P00_RESET;
//        rVal = I2C_Slave_Buffer_A2_P84H_Up[reg_addr+0];
//        rVal = 0xAA;
//        tx_i2c_master_data[0] = rVal;
//	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_PMIC_I2C_ADDR, P00_RESET, 1, &tx_i2c_master_data[0]);
//        SW_Delay(100);
        tx_i2c_master_data[0] = 0x00;
	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_PMIC_I2C_ADDR, P00_RESET, 1, &tx_i2c_master_data[0]);
        I2C_Slave_Buffer_A2_P84H_Up[reg_addr+0] = tx_i2c_master_data[0];
//        SW_Delay(10);

        
        // PMIC, Enable 1.8V (0x06[7] = 1b) and disable laser anode buck-boost (0x07[0] = 0b
//	read_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_PMIC_I2C_ADDR, P01_PMIC_USR1, 2, &tx_i2c_master_data[0]);        
        reg_addr = P01_PMIC_USR1;
        rVal = I2C_Slave_Buffer_A2_P84H_Up[reg_addr+0];
//        rVal = tx_i2c_master_data[0];
//        tx_i2c_master_data[0] = rVal | 0x80;
        tx_i2c_master_data[0] = 0x80;
        I2C_Slave_Buffer_A2_P84H_Up[reg_addr+0] = tx_i2c_master_data[0];
        
//        rVal = tx_i2c_master_data[1];
        rVal = I2C_Slave_Buffer_A2_P84H_Up[reg_addr+1];
//        tx_i2c_master_data[1] = rVal & 0xFE;
        tx_i2c_master_data[1] = 0x00;
        I2C_Slave_Buffer_A2_P84H_Up[reg_addr+1] = tx_i2c_master_data[1];
        
	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_PMIC_I2C_ADDR, P01_BUCK_BOOST_USR0, 1, &tx_i2c_master_data[1]);
        SW_Delay(10);
         
	confirm_write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_PMIC_I2C_ADDR, P01_PMIC_USR1, 1, &tx_i2c_master_data[0]);
        SW_Delay(10);
       
        // Read/write to RF register
        tx_i2c_master_data[0] = 0x00;
	confirm_write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_PASSTHROUGH_EN, 1, &tx_i2c_master_data[0]);
        I2C_Slave_Buffer_A2_P82H_Up[P00_PASSTHROUGH_EN] = tx_i2c_master_data[0];

        // TX&RX CDR Initialization
        tx_cdr_init_from_flash(flag);
        ret_val = tx_cdr_init(flag);
        if (ret_val != 0)
        {
          return (ret_val);
        }
        SW_Delay(100);
        
        rx_cdr_init_from_flash(flag);
        ret_val = rx_cdr_init(flag);
        if (ret_val != 0)
        {
          return (ret_val);
        }
         SW_Delay(100);
       
        // Read/write to PMIC register
        tx_i2c_master_data[0] = 0x01;
	confirm_write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_PASSTHROUGH_EN, 1, &tx_i2c_master_data[0]);
        SW_Delay(10);
        
        //.Enable laser anode buck-boost (4Fh.0x07[0] = 1b)
//        rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_PMIC_I2C_ADDR, P01_BUCK_BOOST_USR0);
//        tx_i2c_master_data[0] = rVal | 0x01;         
        tx_i2c_master_data[0] = 0x21;         
	confirm_write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_PMIC_I2C_ADDR, P01_BUCK_BOOST_USR0, 1, &tx_i2c_master_data[0]);
        I2C_Slave_Buffer_A2_P84H_Up[P01_BUCK_BOOST_USR0] = tx_i2c_master_data[0];
        SW_Delay(10);
//	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_PMIC_I2C_ADDR, P01_BUCK_BOOST_USR0, 1, &tx_i2c_master_data[0]);
//        SW_Delay(10);
        
        tx_i2c_master_data[0] = 0x80;         
	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_PMIC_I2C_ADDR, P01_FAIL_CTRL, 1, &tx_i2c_master_data[0]);
        I2C_Slave_Buffer_A2_P84H_Up[P01_FAIL_CTRL] = tx_i2c_master_data[0];
        
        // [DCLEE] 20.10.09. -->
//        tx_i2c_master_data[0] = 0x07;         // <-- 18 ��
//        tx_i2c_master_data[0] = 0x02;         // <-- 13 ��
#if __RLASER_TRIM_11_OHM__==1
        //        tx_i2c_master_data[0] = 0x07;         // <-- 18 ��
        tx_i2c_master_data[0] = 0x00;         // <-- 13 ��
#elif __RLASER_TRIM_13_OHM__==1
        //        tx_i2c_master_data[0] = 0x07;         // <-- 18 ��
        tx_i2c_master_data[0] = 0x02;         // <-- 13 ��
#elif __RLASER_TRIM_18_OHM__==1
        //        tx_i2c_master_data[0] = 0x07;         // <-- 18 ��
        tx_i2c_master_data[0] = 0x07;         // <-- 13 ��
#endif
	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_PMIC_I2C_ADDR, P01_TRIM_BYTE4, 1, &tx_i2c_master_data[0]);
        I2C_Slave_Buffer_A2_P84H_Up[P01_TRIM_BYTE4] = tx_i2c_master_data[0];

        SW_Delay(10);        
        // Read/write to RF register
        tx_i2c_master_data[0] = 0x00;
	confirm_write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_PASSTHROUGH_EN, 1, &tx_i2c_master_data[0]);

        SW_Delay(10);
        // soft TX Enable
//	rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_LD_CTRL0);
//        rVal = rVal & 0xFB;
//        tx_i2c_master_data[0] = rVal;
        reg_addr = P00_LD_CTRL0;
        rVal = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
//        rVal = rVal & 0xFB;
        rVal = 0xCA;
        tx_i2c_master_data[0] = rVal;
 	confirm_write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_LD_CTRL0, 1, &tx_i2c_master_data[0]);
        SW_Delay(10);
// 	write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_LD_CTRL0, 1, &tx_i2c_master_data[0]);
//        SW_Delay(10);

#endif
        
#endif
        
	return ret_val;
}

uint16_t check_n_recover_cdr_fault_or_hw_reset(void)
{
  
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
  // GN_1157
//	uint8_t	xdata rVal,  rVal2;
//	uint16_t ret_val = 0;
        
        return 0;
        
#if 0
	// Check TX CDR Communication: Read CHIPID: 0x89 default.
	rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_ID);
	if (rVal != GN_1157_CHIPID)
	{
		ret_val = SFP28_MODULE_STATE_FAULT;
		return ret_val;
	}
        
	rVal2 = read_master_gpio_single_byte(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_SR2);
	rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_CR1);
        
        if ((rVal2 == 0x80) && (rVal == 0xD1))
        {
          // CDR reset by any trigger events, under voltage, over voltage, low limit current, or soft reset
          cdr_pmic_ch_control_reinit(0);
          prevLdBiasDa = 0;
          prevModBiasDa = 0;
          prevXconBiasDa = 0;
          
          cdr_reset_counter++;
          *((unsigned int *)&I2C_Slave_Buffer_A2_P02H_Up[0x50]) = __swap_bytes(cdr_reset_counter); // for DEBUG, 191104

        }
        return 0;
#endif

#else
	uint8_t	xdata rVal,  rVal2;
	uint16_t ret_val = 0;

	// Check TX CDR Communication: Read CHIPID: 0x89 default.
	rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_CHIPID);
	if (rVal != MAOM_37030B_CHIPID)
	{
		ret_val = SFP28_MODULE_STATE_FAULT;
		return ret_val;
	}
        
//        reg_addr = P00_LB_MISCL;
//	rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_LB_MISCL);
//	rVal1 = read_master_gpio_single_byte(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_MISC);
	rVal2 = read_master_gpio_single_byte(TX_RX_COMBO_CDR_DML_DRV_I2C_ADDR, P00_STATUS0);
        
//        if ((rVal == 0x00) && (rVal1 == 0x00) && (rVal2 == 0x01))
        if ((rVal2 == 0x01))
        {
          // CDR reset by any trigger events, under voltage, over voltage, low limit current, or soft reset
          cdr_pmic_ch_control_reinit(0);
          prevLdBiasDa = 0;
          prevModBiasDa = 0;
          prevXconBiasDa = 0;
          
          cdr_reset_counter++;
          *((unsigned int *)&I2C_Slave_Buffer_A2_P02H_Up[0x50]) = __swap_bytes(cdr_reset_counter); // for DEBUG, 191104

        }
        return 0;

#endif
        
  
}


uint16_t rate_select_control_cdr(uint8_t flag)
{
#if __SFP28_ER_SEMI_TUNABLE__ == 1
  
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1
  // GN_1157
  // flag = 0x00, 0x02 : 3G
  // flag = 0x01, 0x03 : 10G
  A2_LOWER_MEMORY_MAP * xdata lowerMemoryMapPtr;
  A2_PAGE_82H_MEMORY_MAP	xdata * flashPtr, * controlMemoryPtr_1;

	uint8_t	xdata rVal;
	uint8_t	xdata reg_addr;
  uint16_t ret_val;

	// Check TX CDR Communication: Read CHIPID: 0x89 default.
	rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_ID);
	if (rVal != GN_1157_CHIPID)
	{
		ret_val = SFP28_MODULE_STATE_FAULT;
		return ret_val;
	}

	// Set TX CDR Registers
  flashPtr = (A2_PAGE_82H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P82H_Up[0];

  lowerMemoryMapPtr = (A2_LOWER_MEMORY_MAP *)&I2C_Slave_Buffer_A2[0];
  controlMemoryPtr_1 = (A2_PAGE_82H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_Pn_Up[0];
  
        
#if __SFP_PLUS_3G_10G_ER_SEMI_TUNABLE__ == 1

        // 3G Rate Select Only

        // TX_Mode        

        if (flag == 3)
        { // 10G
          // RS1=1, RS0=1: TX & RX Lock at high bit rate
          reg_addr = P00_TX_RATE_SELECT;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          
//          if ((tx_i2c_master_data[0] & 0x01) != 0x01)
          if ((tx_i2c_master_data[0] & 0x01) != 0x00)
          {
            // Set to Low rate --> Bit[0]=1
//            tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0xFE) | 0x01;
            tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0xFE);
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_TX_RATE_SELECT, 1, &tx_i2c_master_data[0]);
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
                      
          }
          
          reg_addr = P00_RX_RATE_SELECT;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          tx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1];
          
//          if ((tx_i2c_master_data[1] & 0x01) != 0x01)
          if ((tx_i2c_master_data[1] & 0x01) != 0x00)
          {
//            tx_i2c_master_data[1] = (tx_i2c_master_data[0] & 0xFE) | 0x01;
            tx_i2c_master_data[1] = (tx_i2c_master_data[0] & 0xFE);
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_RATE_SELECT, 2, &tx_i2c_master_data[0]);            
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = tx_i2c_master_data[1];
          }          
        }
        else if (flag == 2)
        {  // Low rate: 3G
          // RS1=1, RS0=0: TX Bypass & RX Lock at high bit rate
          reg_addr = P00_TX_RATE_SELECT;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          
          if ((tx_i2c_master_data[0] & 0x01) != 0x01)
          {
            // Set to Low rate --> Bit[0]=1
            tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0xFE) | 0x01;
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_TX_RATE_SELECT, 1, &tx_i2c_master_data[0]);
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
                      
          }
          
          reg_addr = P00_RX_RATE_SELECT;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          tx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1];
          
          if ((tx_i2c_master_data[1] & 0x01) != 0x01)
          {
            tx_i2c_master_data[1] = (tx_i2c_master_data[0] & 0xFE) | 0x01;
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_RATE_SELECT, 2, &tx_i2c_master_data[0]);            
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = tx_i2c_master_data[1];
          }          
        
        }
        else if (flag == 1)
        { // 10G, High bit rate
          // RS1=0, RS0=1: TX & RX Bypass 
          reg_addr = P00_TX_RATE_SELECT;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          
//          if ((tx_i2c_master_data[0] & 0x01) != 0x01)
          if ((tx_i2c_master_data[0] & 0x01) != 0x00)
          {
            // Set to Low rate --> Bit[0]=1
//            tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0xFE) | 0x01;
            tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0xFE);
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_TX_RATE_SELECT, 1, &tx_i2c_master_data[0]);
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
                      
          }
          
          reg_addr = P00_RX_RATE_SELECT;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          tx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1];
          
//          if ((tx_i2c_master_data[1] & 0x01) != 0x01)
          if ((tx_i2c_master_data[1] & 0x01) != 0x00)
          {
            tx_i2c_master_data[1] = (tx_i2c_master_data[0] & 0xFE);
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_RATE_SELECT, 2, &tx_i2c_master_data[0]);            
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = tx_i2c_master_data[1];
          }          
          
        }
        else
        { // 3G, Low bit rate
          // RS1=0, RS0=0: TX & RX Lock at low bit rate
          reg_addr = P00_TX_RATE_SELECT;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          
          if ((tx_i2c_master_data[0] & 0x01) != 0x01)
          {
            // Set to Low rate --> Bit[0]=1
            tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0xFE) | 0x01;
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_TX_RATE_SELECT, 1, &tx_i2c_master_data[0]);
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
                      
          }
          
          reg_addr = P00_RX_RATE_SELECT;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          tx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1];
          
          if ((tx_i2c_master_data[1] & 0x01) != 0x01)
          {
            tx_i2c_master_data[1] = (tx_i2c_master_data[0] & 0xFE) | 0x01;
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_RATE_SELECT, 2, &tx_i2c_master_data[0]);            
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = tx_i2c_master_data[1];
          }          
          
        }
                
        return 0;
        
#elif __HSFP_10G_ER_SEMI_TUNABLE__==1

#if __HSFP_10G_MULTI_RATE_SEMI_TUNABLE__ == 1
        // TX_Mode        

        if (flag == 3)
        { // 10G
          // RS1=1, RS0=1: TX & RX Lock at high bit rate
          reg_addr = P00_TX_RATE_SELECT;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          
//          if ((tx_i2c_master_data[0] & 0x01) != 0x01)
          if ((tx_i2c_master_data[0] & 0x01) != 0x00)
          {
            // Set to Low rate --> Bit[0]=1
//            tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0xFE) | 0x01;
            tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0xFE);
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_TX_RATE_SELECT, 1, &tx_i2c_master_data[0]);
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
                  
            if (lowerMemoryMapPtr->A2_TABLE == 0x82)
            {
              I2C_Slave_Buffer_A2_Pn_Up[reg_addr+0] = tx_i2c_master_data[0];             
            }
                            
          }
          
          reg_addr = P00_RX_RATE_SELECT;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          tx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1];
          
//          if ((tx_i2c_master_data[1] & 0x01) != 0x01)
          if ((tx_i2c_master_data[1] & 0x01) != 0x00)
          {
//            tx_i2c_master_data[1] = (tx_i2c_master_data[0] & 0xFE) | 0x01;
            tx_i2c_master_data[1] = (tx_i2c_master_data[0] & 0xFE);
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_RATE_SELECT, 2, &tx_i2c_master_data[0]);            
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = tx_i2c_master_data[1];

            if (lowerMemoryMapPtr->A2_TABLE == 0x82)
            {
              I2C_Slave_Buffer_A2_Pn_Up[reg_addr+0] = tx_i2c_master_data[0];             
              I2C_Slave_Buffer_A2_Pn_Up[reg_addr+1] = tx_i2c_master_data[1];             
            }
          }          
        }
        else if (flag == 2)
        {  // Low rate: 3G
          // RS1=1, RS0=0: TX Bypass & RX Lock at high bit rate
          reg_addr = P00_TX_RATE_SELECT;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          
          if ((tx_i2c_master_data[0] & 0x01) != 0x01)
          {
            // Set to Low rate --> Bit[0]=1
            tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0xFE) | 0x01;
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_TX_RATE_SELECT, 1, &tx_i2c_master_data[0]);
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];

            if (lowerMemoryMapPtr->A2_TABLE == 0x82)
            {
              I2C_Slave_Buffer_A2_Pn_Up[reg_addr+0] = tx_i2c_master_data[0];             
            }
                      
          }
          
          reg_addr = P00_RX_RATE_SELECT;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          tx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1];
          
          if ((tx_i2c_master_data[1] & 0x01) != 0x01)
          {
            tx_i2c_master_data[1] = (tx_i2c_master_data[0] & 0xFE) | 0x01;
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_RATE_SELECT, 2, &tx_i2c_master_data[0]);            
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = tx_i2c_master_data[1];

            if (lowerMemoryMapPtr->A2_TABLE == 0x82)
            {
              I2C_Slave_Buffer_A2_Pn_Up[reg_addr+0] = tx_i2c_master_data[0];             
              I2C_Slave_Buffer_A2_Pn_Up[reg_addr+1] = tx_i2c_master_data[1];             
            }
          }          
        
        }
        else if (flag == 1)
        { // 10G, High bit rate
          // RS1=0, RS0=1: TX & RX Bypass 
          reg_addr = P00_TX_RATE_SELECT;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          
//          if ((tx_i2c_master_data[0] & 0x01) != 0x01)
          if ((tx_i2c_master_data[0] & 0x01) != 0x00)
          {
            // Set to Low rate --> Bit[0]=1
//            tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0xFE) | 0x01;
            tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0xFE);
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_TX_RATE_SELECT, 1, &tx_i2c_master_data[0]);
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
                      
            if (lowerMemoryMapPtr->A2_TABLE == 0x82)
            {
              I2C_Slave_Buffer_A2_Pn_Up[reg_addr+0] = tx_i2c_master_data[0];             
            }
          }
          
          reg_addr = P00_RX_RATE_SELECT;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          tx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1];
          
//          if ((tx_i2c_master_data[1] & 0x01) != 0x01)
          if ((tx_i2c_master_data[1] & 0x01) != 0x00)
          {
            tx_i2c_master_data[1] = (tx_i2c_master_data[0] & 0xFE);
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_RATE_SELECT, 2, &tx_i2c_master_data[0]);            
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = tx_i2c_master_data[1];

            if (lowerMemoryMapPtr->A2_TABLE == 0x82)
            {
              I2C_Slave_Buffer_A2_Pn_Up[reg_addr+0] = tx_i2c_master_data[0];             
              I2C_Slave_Buffer_A2_Pn_Up[reg_addr+1] = tx_i2c_master_data[1];             
            }
          }          
          
        }
        else
        { // 3G, Low bit rate
          // RS1=0, RS0=0: TX & RX Lock at low bit rate
          reg_addr = P00_TX_RATE_SELECT;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          
          if ((tx_i2c_master_data[0] & 0x01) != 0x01)
          {
            // Set to Low rate --> Bit[0]=1
            tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0xFE) | 0x01;
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_TX_RATE_SELECT, 1, &tx_i2c_master_data[0]);
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
                      
            if (lowerMemoryMapPtr->A2_TABLE == 0x82)
            {
              I2C_Slave_Buffer_A2_Pn_Up[reg_addr+0] = tx_i2c_master_data[0];             
            }
          }
          
          reg_addr = P00_RX_RATE_SELECT;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          tx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1];
          
          if ((tx_i2c_master_data[1] & 0x01) != 0x01)
          {
            tx_i2c_master_data[1] = (tx_i2c_master_data[0] & 0xFE) | 0x01;
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_RATE_SELECT, 2, &tx_i2c_master_data[0]);            
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = tx_i2c_master_data[1];

            if (lowerMemoryMapPtr->A2_TABLE == 0x82)
            {
              I2C_Slave_Buffer_A2_Pn_Up[reg_addr+0] = tx_i2c_master_data[0];             
              I2C_Slave_Buffer_A2_Pn_Up[reg_addr+1] = tx_i2c_master_data[1];             
            }
          }          
          
        }
                
        return 0;

#else

        // HSFP 10G  bitrate ����Ǵ� ����
        reg_addr = P00_TX_RATE_SELECT;
        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
        
//        if ((tx_i2c_master_data[0] & 0x01) != 0x01)
        if ((tx_i2c_master_data[0] & 0x01) == 0x01)
        {
          // Set to Low rate --> Bit[0]=1
//          tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0xFE) | 0x01;
          tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0xFE) | 0x00;
          write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_TX_RATE_SELECT, 1, &tx_i2c_master_data[0]);
          I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
          
        }
        
        reg_addr = P00_RX_RATE_SELECT;
        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
        tx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1];
        
//        if ((tx_i2c_master_data[1] & 0x01) != 0x01)
        if ((tx_i2c_master_data[1] & 0x01) != 0x01)
        {
//          tx_i2c_master_data[1] = (tx_i2c_master_data[0] & 0xFE) | 0x01;
          tx_i2c_master_data[1] = (tx_i2c_master_data[0] & 0xFE) | 0x00;
          write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_RATE_SELECT, 2, &tx_i2c_master_data[0]);            
          I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
          I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = tx_i2c_master_data[1];
        }          
        
        return 0;
#endif

#else
        // 3G ���� bitrate �� ����Ǵ� ����
        reg_addr = P00_TX_RATE_SELECT;
        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
        
        if ((tx_i2c_master_data[0] & 0x01) != 0x01)
        {
          // Set to Low rate --> Bit[0]=1
          tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0xFE) | 0x01;
          write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_TX_RATE_SELECT, 1, &tx_i2c_master_data[0]);
          I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
          
        }
        
        reg_addr = P00_RX_RATE_SELECT;
        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
        tx_i2c_master_data[1] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1];
        
        if ((tx_i2c_master_data[1] & 0x01) != 0x01)
        {
          tx_i2c_master_data[1] = (tx_i2c_master_data[0] & 0xFE) | 0x01;
          write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_RATE_SELECT, 2, &tx_i2c_master_data[0]);            
          I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
          I2C_Slave_Buffer_A2_P82H_Up[reg_addr+1] = tx_i2c_master_data[1];
        }          
        
        return 0;

#endif
  
#else

	uint8_t	xdata rVal;
	uint8_t	xdata reg_addr;
        uint16_t ret_val;

	// Check TX CDR Communication: Read CHIPID: 0x89 default.
	rVal = read_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_CHIPID);
	if (rVal != MAOM_37030B_CHIPID)
	{
		ret_val = SFP28_MODULE_STATE_FAULT;
		return ret_val;
	}

	// Set TX CDR Registers
        
	// TX_Mode
//        reg_addr = P00_TX_MODES;
//        tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];

        if (flag == 3)
        {
          // RS1=1, RS0=1: TX & RX Lock at high bit rate
          reg_addr = P00_TX_MODES;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          
          if ((tx_i2c_master_data[0] & 0x70) != 0x40)
          {
            tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0x8F) | 0x40;
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_TX_MODES, 1, &tx_i2c_master_data[0]);
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
            
            // [DCLEE: 20.08.26.] LD_DRV_CTRL3 ����: 25G ���ý� 0xA1, 10G ���ý� 0x9A�� ����
            // 25G: high bit rate
#if __WAVELENGTH_1290_VER__==1
//            rVal = 0xA1;
            rVal = 0x9A;
            write_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_DRV_CTRL3, rVal);            
            I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL3] = rVal;
#elif __WAVELENGTH_1270_VER__==1
            rVal = 0xA1;
            write_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_DRV_CTRL3, rVal);            
            I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL3] = rVal;
#elif __WAVELENGTH_1330_VER__==1
            rVal = 0x9A;
            write_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_DRV_CTRL3, rVal);            
            I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL3] = rVal;
#else
            rVal = 0xA1;
            write_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_DRV_CTRL3, rVal);            
            I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL3] = rVal;
            
#endif
            
          }
          
          reg_addr = P00_RX_MODES;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          
          if ((tx_i2c_master_data[0] & 0x70) != 0x40)
          {
            tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0x8F) | 0x40;
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_MODES, 1, &tx_i2c_master_data[0]);            
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
          }          
        }
        else if (flag == 2)
        {
          // RS1=1, RS0=0: TX Bypass & RX Lock at high bit rate
          reg_addr = P00_TX_MODES;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          
          if ((tx_i2c_master_data[0] & 0x70) != 0x10)
          {
            tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0x8F) | 0x10;
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_TX_MODES, 1, &tx_i2c_master_data[0]);
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
            
            // [DCLEE: 20.08.26.] LD_DRV_CTRL3 ����: 10G ���ý� 0xA1, 10G ���ý� 0x9A�� ����
            // 10G: TX Bypass
//            rVal = 0x9A;
#if __WAVELENGTH_1290_VER__==1
//            rVal = 0xA1;
            rVal = 0x9A;
#elif __WAVELENGTH_1270_VER__==1
            rVal = 0xA1;
#elif __WAVELENGTH_1330_VER__==1
            rVal = 0x9A;
#else
            rVal = 0xA1;
#endif
            
            write_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_DRV_CTRL3, rVal);            
            I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL3] = rVal;
            
            
          }
          
          reg_addr = P00_RX_MODES;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          
          if ((tx_i2c_master_data[0] & 0x70) != 0x40)
          {
            tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0x8F) | 0x40;
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_MODES, 1, &tx_i2c_master_data[0]);            
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
          }          
          
        }
        else if (flag == 1)
        {
          // RS1=0, RS0=1: TX & RX Bypass 
          reg_addr = P00_TX_MODES;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          
          if ((tx_i2c_master_data[0] & 0x70) != 0x10)
          {
            tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0x8F) | 0x10;
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_TX_MODES, 1, &tx_i2c_master_data[0]);
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
            
            // [DCLEE: 20.08.26.] LD_DRV_CTRL3 ����: 10G ���ý� 0xA1, 10G ���ý� 0x9A�� ����
            // 10G: TX Bypass
//            rVal = 0x9A;
//            rVal = 0xA1;
#if __WAVELENGTH_1290_VER__==1
//            rVal = 0xA1;
            rVal = 0x9A;
#elif __WAVELENGTH_1270_VER__==1
            rVal = 0xA1;
#elif __WAVELENGTH_1330_VER__==1
            rVal = 0x9A;
#else
            rVal = 0xA1;
#endif
            write_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_DRV_CTRL3, rVal);            
            I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL3] = rVal;
          }
          
          reg_addr = P00_RX_MODES;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          
          if ((tx_i2c_master_data[0] & 0x70) != 0x10)
          {
            tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0x8F) | 0x10;
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_MODES, 1, &tx_i2c_master_data[0]);            
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
          }          
          
        }
        else
        {
          // RS1=0, RS0=0: TX & RX Lock at low bit rate
          reg_addr = P00_TX_MODES;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          
          if ((tx_i2c_master_data[0] & 0x70) != 0x10)
          {
            tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0x8F) | 0x10;
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_TX_MODES, 1, &tx_i2c_master_data[0]);
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
            
            // [DCLEE: 20.08.26.] LD_DRV_CTRL3 ����: 10G ���ý� 0xA1, 10G ���ý� 0x9A�� ����
            // 10G: TX Bypass
//            rVal = 0x9A;
//            rVal = 0xA1;
#if __WAVELENGTH_1290_VER__==1
//            rVal = 0xA1;
            rVal = 0x9A;
#elif __WAVELENGTH_1270_VER__==1
            rVal = 0xA1;
#elif __WAVELENGTH_1330_VER__==1
            rVal = 0x9A;
#else
            rVal = 0xA1;
#endif
            write_master_gpio_single_byte(TX_RX_COMBO_CDR_I2C_ADDR, P00_LD_DRV_CTRL3, rVal);            
            I2C_Slave_Buffer_A2_P82H_Up[P00_LD_DRV_CTRL3] = rVal;
          }
          
          reg_addr = P00_RX_MODES;
          tx_i2c_master_data[0] = I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0];
          
          if ((tx_i2c_master_data[0] & 0x70) != 0x10)
          {
            tx_i2c_master_data[0] = (tx_i2c_master_data[0] & 0x8F) | 0x10;
            write_master_gpio_multiple_bytes(TX_RX_COMBO_CDR_I2C_ADDR, P00_RX_MODES, 1, &tx_i2c_master_data[0]);            
            I2C_Slave_Buffer_A2_P82H_Up[reg_addr+0] = tx_i2c_master_data[0];
          }          
          
        }
                
        return 0;

#endif
        
#endif
        
}

void wavelength_info_set(void)
{
#if __WAVELENGTH_ANY_VER__==1
  unsigned int  lf_l1, ref_wavelength_id;
#endif
   unsigned int  lf_l2, chNo, grpNo;
  PAGE_02H_MEMORY_MAP * p02_memPtr;
  
  
  p02_memPtr = (PAGE_02H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P02H_Up[0];
  
#if __WAVELENGTH_ANY_VER__==1
  lf_l1 = __swap_bytes(p02_memPtr->LFL1);
#endif
  lf_l2 = __swap_bytes(p02_memPtr->LFL2);
  
#if __WAVELENGTH_ANY_VER__==1
  
#if __SFP_PLUS_3G_ER_SEMI_TUNABLE__ == 1

  if ((lf_l1 >= 211) && (lf_l1 <= 213))
  { // 1411
    ref_wavelength_id = 0;
    switch (lf_l2)
    {
    case 2300 :
      grpNo = 0;
      break;
      
    case 7200 :
      grpNo = 1;
      break;
      
    case 1000 :
      grpNo = 2;
      break;
      
    case 6000 :
      grpNo = 3;
      break;
      
    default:
      grpNo = 0;
      break;
    }
    
  }
  else if ((lf_l1 >= 194) && (lf_l1 <= 196))
  { // 1531
    ref_wavelength_id = 1;
    
    switch (lf_l2)
    {
    case 7000 :
      grpNo = 0;
      break;
      
    case 3000 :
      grpNo = 1;
      break;
      
    case 8000 :
      grpNo = 2;
      break;
      
    case 4000 :
      grpNo = 3;
      break;
      
    default:
      grpNo = 0;
      break;
    }
    
  }
  else if ((lf_l1 >= 192) && (lf_l1 <= 193))
  { // 1551
    ref_wavelength_id = 2;
    
    switch (lf_l2)
    {
    case 4000 :
      grpNo = 0;
      break;
      
    case 0 :
      grpNo = 1;
      break;
      
    case 5000 :
      grpNo = 2;
      break;
      
    case 1000 :
      grpNo = 3;
      break;
      
    default:
      grpNo = 0;
      break;
    }
    
  }
  else
  { // Default 1411
    ref_wavelength_id = 0;
    switch (lf_l2)
    {
    case 2300 :
      grpNo = 0;
      break;
      
    case 7200 :
      grpNo = 1;
      break;
      
    case 1000 :
      grpNo = 2;
      break;
      
    case 6000 :
      grpNo = 3;
      break;
      
    default:
      grpNo = 0;
      break;
    }
  }
  
#else
  if ((lf_l1 >= 234) && (lf_l1 <= 237))
  { // 1271
    ref_wavelength_id = 0;
    switch (lf_l2)
    {
    case 7500 :
      grpNo = 0;
      break;
      
    case 1500 :
      grpNo = 1;
      break;
      
    case 4000 :
      grpNo = 2;
      break;
      
    case 8000 :
      grpNo = 3;
      break;
      
    default:
      grpNo = 0;
      break;
    }
  }
  else if ((lf_l1 >= 231) && (lf_l1 <= 233))
  { // 1291
    ref_wavelength_id = 1;
    switch (lf_l2)
    {
    case 1500 :
      grpNo = 0;
      break;
      
    case 5500 :
      grpNo = 1;
      break;
      
    case 8000 :
      grpNo = 2;
      break;
      
    case 2000 :
      grpNo = 3;
      break;
      
    default:
      grpNo = 0;
      break;
    }
  }
  else if ((lf_l1 >= 224) && (lf_l1 <= 226))
  { // 1331
    ref_wavelength_id = 2;
    switch (lf_l2)
    {
    case 1000 :
      grpNo = 0;
      break;
      
    case 5500 :
      grpNo = 1;
      break;
      
    case 8600 :
      grpNo = 2;
      break;
      
    case 3100 :
      grpNo = 3;
      break;
      
    default:
      grpNo = 0;
      break;
    }
    
  }
  else if ((lf_l1 >= 221) && (lf_l1 <= 223))
  { // 1351
    ref_wavelength_id = 3;
    switch (lf_l2)
    {
    case 8000 :
      grpNo = 0;
      break;
      
    case 2500 :
      grpNo = 1;
      break;
      
    case 5600 :
      grpNo = 2;
      break;
      
    case 100 :
      grpNo = 3;
      break;
      
    default:
      grpNo = 0;
      break;
    }
    
  }    
  else if ((lf_l1 >= 211) && (lf_l1 <= 213))
  { // 1411
    ref_wavelength_id = 4;
    switch (lf_l2)
    {
    case 2300 :
      grpNo = 0;
      break;
      
    case 7200 :
      grpNo = 1;
      break;
      
    case 1000 :
      grpNo = 2;
      break;
      
    case 6000 :
      grpNo = 3;
      break;
      
    default:
      grpNo = 0;
      break;
    }
    
  }
  else if ((lf_l1 >= 208) && (lf_l1 <= 210))
  { // 1431
    ref_wavelength_id = 5;
    
    switch (lf_l2)
    {
    case 2300 :
      grpNo = 0;
      break;
      
    case 7300 :
      grpNo = 1;
      break;
      
    case 1000 :
      grpNo = 2;
      break;
      
    case 6000 :
      grpNo = 3;
      break;
      
    default:
      grpNo = 0;
      break;
    }
    
  }
  else if ((lf_l1 >= 205) && (lf_l1 <= 207))
  { // 1451
    ref_wavelength_id = 6;
    
    switch (lf_l2)
    {
    case 2800 :
      grpNo = 0;
      break;
      
    case 8300 :
      grpNo = 1;
      break;
      
    case 2600 :
      grpNo = 2;
      break;
      
    case 8100 :
      grpNo = 3;
      break;
      
    default:
      grpNo = 0;
      break;
    }
    
  }
  else if ((lf_l1 >= 203) && (lf_l1 <= 204))
  { // 1471
    ref_wavelength_id = 7;
    
    switch (lf_l2)
    {
    case 4600 :
      grpNo = 0;
      break;
      
    case 100 :
      grpNo = 1;
      break;
      
    case 4500 :
      grpNo = 2;
      break;
      
    case 0 :
      grpNo = 3;
      break;
      
    default:
      grpNo = 0;
      break;
    }
    
  }
  else if ((lf_l1 >= 200) && (lf_l1 <= 202))
  { // 1491
    ref_wavelength_id = 8;
    
    switch (lf_l2)
    {
    case 7600 :
      grpNo = 0;
      break;
      
    case 3100 :
      grpNo = 1;
      break;
      
    case 7500 :
      grpNo = 2;
      break;
      
    case 3000 :
      grpNo = 3;
      break;
      
    default:
      grpNo = 0;
      break;
    }
    
  }
  else if ((lf_l1 >= 197) && (lf_l1 <= 199))
  { // 1511
    ref_wavelength_id = 9;
    
    switch (lf_l2)
    {
    case 600 :
      grpNo = 0;
      break;
      
    case 6100 :
      grpNo = 1;
      break;
      
    case 500 :
      grpNo = 2;
      break;
      
    case 6000 :
      grpNo = 3;
      break;
      
    default:
      grpNo = 0;
      break;
    }
    
  }
  else
  { // Default 1291
    ref_wavelength_id = 1;
    switch (lf_l2)
    {
    case 1500 :
      grpNo = 0;
      break;
      
    case 5500 :
      grpNo = 1;
      break;
      
    case 8000 :
      grpNo = 2;
      break;
      
    case 2000 :
      grpNo = 3;
      break;
      
    default:
      grpNo = 0;
      break;
    }    
  }
   
#endif
  
#elif __WAVELENGTH_1290_VER__==1

  switch (lf_l2)
  {
  case 1500 :
    grpNo = 0;
    break;
    
  case 5500 :
    grpNo = 1;
    break;
    
  case 8000 :
    grpNo = 2;
    break;
    
  case 2000 :
    grpNo = 3;
    break;
    
  default:
    grpNo = 0;
    break;
  }

#elif __WAVELENGTH_1270_VER__==1

  switch (lf_l2)
  {
  case 7500 :
    grpNo = 0;
    break;
    
  case 1500 :
    grpNo = 1;
    break;
    
  case 4000 :
    grpNo = 2;
    break;
    
  case 8000 :
    grpNo = 3;
    break;
    
  default:
    grpNo = 0;
    break;
  }
#elif __WAVELENGTH_1330_VER__==1

  switch (lf_l2)
  {
  case 1000 :
    grpNo = 0;
    break;
    
  case 5500 :
    grpNo = 1;
    break;
    
  case 8600 :
    grpNo = 2;
    break;
    
  case 3100 :
    grpNo = 3;
    break;
    
  default:
    grpNo = 0;
    break;
  }
  
#elif __WAVELENGTH_1350_VER__==1

  switch (lf_l2)
  {
  case 8000 :
    grpNo = 0;
    break;
    
  case 2500 :
    grpNo = 1;
    break;
    
  case 5600 :
    grpNo = 2;
    break;
    
  case 100 :
    grpNo = 3;
    break;
    
  default:
    grpNo = 0;
    break;
  }

#elif __WAVELENGTH_1410_VER__==1
// 3G ST-SFP+ 1411 Wavelength�� ���� ���

  switch (lf_l2)
  {
  case 2300 :
    grpNo = 0;
    break;
    
  case 7200 :
    grpNo = 1;
    break;
    
  case 1000 :
    grpNo = 2;
    break;
    
  case 6000 :
    grpNo = 3;
    break;
    
  default:
    grpNo = 0;
    break;
  }

#elif __WAVELENGTH_1430_VER__==1

  switch (lf_l2)
  {
  case 2300 :
    grpNo = 0;
    break;
    
  case 7300 :
    grpNo = 1;
    break;
    
  case 1000 :
    grpNo = 2;
    break;
    
  case 6000 :
    grpNo = 3;
    break;
    
  default:
    grpNo = 0;
    break;
  }

#elif __WAVELENGTH_1450_VER__==1

  switch (lf_l2)
  {
  case 2800 :
    grpNo = 0;
    break;
    
  case 8300 :
    grpNo = 1;
    break;
    
  case 2600 :
    grpNo = 2;
    break;
    
  case 8100 :
    grpNo = 3;
    break;
    
  default:
    grpNo = 0;
    break;
  }

#elif __WAVELENGTH_1470_VER__==1

  switch (lf_l2)
  {
  case 4600 :
    grpNo = 0;
    break;
    
  case 100 :
    grpNo = 1;
    break;
    
  case 4500 :
    grpNo = 2;
    break;
    
  case 0 :
    grpNo = 3;
    break;
    
  default:
    grpNo = 0;
    break;
  }

#elif __WAVELENGTH_1490_VER__==1

  switch (lf_l2)
  {
  case 7600 :
    grpNo = 0;
    break;
    
  case 3100 :
    grpNo = 1;
    break;
    
  case 7500 :
    grpNo = 2;
    break;
    
  case 3000 :
    grpNo = 3;
    break;
    
  default:
    grpNo = 0;
    break;
  }

#elif __WAVELENGTH_1510_VER__==1

  switch (lf_l2)
  {
  case 600 :
    grpNo = 0;
    break;
    
  case 6100 :
    grpNo = 1;
    break;
    
  case 500 :
    grpNo = 2;
    break;
    
  case 6000 :
    grpNo = 3;
    break;
    
  default:
    grpNo = 0;
    break;
  }

//#elif __WAVELENGTH_1410_VER__==1
//// 3G ST-SFP+ 1411 Wavelength
//
//  switch (lf_l2)
//  {
//  case 2300 :
//    grpNo = 0;
//    break;
//    
//  case 7200 :
//    grpNo = 1;
//    break;
//    
//  case 1000 :
//    grpNo = 2;
//    break;
//    
//  case 6000 :
//    grpNo = 3;
//    break;
//    
//  default:
//    grpNo = 0;
//    break;
//  }
//  
#elif __WAVELENGTH_1530_VER__==1
// 3G ST-SFP+ 1531 Wavelength

  switch (lf_l2)
  {
  case 7000 :
    grpNo = 0;
    break;
    
  case 3000 :
    grpNo = 1;
    break;
    
  case 8000 :
    grpNo = 2;
    break;
    
  case 4000 :
    grpNo = 3;
    break;
    
  default:
    grpNo = 0;
    break;
  }
  
#elif __WAVELENGTH_1550_VER__==1
// 3G ST-SFP+ 1551 Wavelength

  switch (lf_l2)
  {
  case 4000 :
    grpNo = 0;
    break;
    
  case 0 :
    grpNo = 1;
    break;
    
  case 5000 :
    grpNo = 2;
    break;
    
  case 1000 :
    grpNo = 3;
    break;
    
  default:
    grpNo = 0;
    break;
  }
  
#else

  switch (lf_l2)
  {
  case 7500 :
    grpNo = 0;
    break;
    
  case 1500 :
    grpNo = 1;
    break;
    
  case 4000 :
    grpNo = 2;
    break;
    
  case 8000 :
    grpNo = 3;
    break;
    
  default:
    grpNo = 0;
    break;
  }
  
#endif
  
  chNo = __swap_bytes(p02_memPtr->Channel_Number_Set);

//  if ((chNo > 0) && (chNo < 5))
  if ((chNo > 0) && (chNo < 9))
  {
//    chNo = chNo - 1;
    chNo = (chNo - 1)%4;
  }
  else
  {
    chNo = 0;
  } 
#if __WAVELENGTH_ANY_VER__==1
#if __WAVELENGTH_LIKE_FIXED_VER__ == 1

#if __WAVELENGTH_LIKE_FIXED_VER_50PM__ == 1
// //  long wl_l_val;
// //  unsigned int wl_val_1, wl_val_f;
//   unsigned int wl_val_1;
//   unsigned int * wl_val_ptr;
  
//   p02_memPtr->Wavelength_Set = __swap_bytes(wavelength_info[ref_wavelength_id][grpNo][chNo]);

#if __FIXED_MODE_SFP_VER__==1
  
  // wl_val_1 = wavelength_info_A0_60_61[ref_wavelength_id][grpNo][chNo];  
  // wl_val_ptr = (unsigned int *)&I2C_Slave_Buffer_A0_Local_Memory[A0H_SERIAL_ID_WAVELENGTH];
  // *wl_val_ptr = __swap_bytes(wl_val_1);  
  // I2C_Slave_Buffer_A0_Local_Memory[A0H_SERIAL_ID_WAVELENGTH_FRACTION] = 0;
  
  // update_A0H_cc_base_value();
  
#else
  
  wl_l_val = wavelength_info[ref_wavelength_id][grpNo][chNo];
  wl_l_val = wl_l_val * 5;
  
  wl_val_ptr = (unsigned int *)&I2C_Slave_Buffer_A0_Local_Memory[A0H_SERIAL_ID_WAVELENGTH];
  wl_val_1 = wl_l_val / 100;
  wl_val_f = wl_l_val % 100;
  *wl_val_ptr = __swap_bytes(wl_val_1);
  I2C_Slave_Buffer_A0_Local_Memory[A0H_SERIAL_ID_WAVELENGTH_FRACTION] = wl_val_f;
  update_A0H_cc_base_value();
  
  
#endif
    

#else

//  double wl_f_val;
  long wl_l_val;
  unsigned int wl_val_1;
  unsigned int * wl_val_ptr;
  
  //  I2C_Slave_Buffer_A0_Local_Memory[];
  //  A0H_SERIAL_ID_WAVELENGTH, A0H_SERIAL_ID_WAVELENGTH_FRACTION
  wl_val_ptr = (unsigned int *)&I2C_Slave_Buffer_A0_Local_Memory[A0H_SERIAL_ID_WAVELENGTH];
  *wl_val_ptr = __swap_bytes(wavelength_info[ref_wavelength_id][grpNo][chNo]);
  I2C_Slave_Buffer_A0_Local_Memory[A0H_SERIAL_ID_WAVELENGTH_FRACTION] = wavelength_info_fraction[ref_wavelength_id][grpNo][chNo];
  
  wl_l_val = wavelength_info[ref_wavelength_id][grpNo][chNo];
  wl_l_val = (wl_l_val * 100) + wavelength_info_fraction[ref_wavelength_id][grpNo][chNo];
  wl_val_1 = (unsigned int)(wl_l_val / 5);
  p02_memPtr->Wavelength_Set = __swap_bytes(wl_val_1);
  
  update_A0H_cc_base_value();

#endif
    
#else
  p02_memPtr->Wavelength_Set = __swap_bytes(wavelength_info[ref_wavelength_id][grpNo][chNo]);  
#endif
  
#else
  p02_memPtr->Wavelength_Set = __swap_bytes(wavelength_info[grpNo][chNo]);
#endif
    
  if (grpNo < 2)
  {
    // A, B Group
    p02_memPtr->Channel_Number_Set = __swap_bytes(chNo + 1);
    curr_channel_no = __swap_bytes(p02_memPtr->Channel_Number_Set);
  }
  else
  {
    // C, D Group
    p02_memPtr->Channel_Number_Set = __swap_bytes(chNo + 5);
    curr_channel_no = __swap_bytes(p02_memPtr->Channel_Number_Set);
    
  }
  
  return;
  
}

#if __WAVELENGTH_LIKE_FIXED_VER__ == 1

void update_A0H_cc_base_value(void)
{
  unsigned int comp_value;
  unsigned int idx;
//  unsigned char curr_cc_base, calculate_cc_base, curr_passwd;
  unsigned char curr_cc_base, calculate_cc_base;
  
  curr_cc_base = I2C_Slave_Buffer_A0_Local_Memory[A0H_SERIAL_ID_CC_BASE];
  
  comp_value = 0;
  for (idx=0; idx < A0H_SERIAL_ID_CC_BASE; idx++)
  {
    comp_value += I2C_Slave_Buffer_A0_Local_Memory[idx];
  }
  calculate_cc_base = (unsigned char)(comp_value & 0x00FF);
  
  if (curr_cc_base != calculate_cc_base)
  {
    I2C_Slave_Buffer_A0_Local_Memory[A0H_SERIAL_ID_CC_BASE] = calculate_cc_base;
    
//    curr_passwd = page_password_enable[9];
//    page_password_enable[9] = 1;
//    save_to_flash_memory(9);
//    page_password_enable[9] = curr_passwd;

  }
  return;
}
#endif

#if 0

#define CONST_LIGHT_SPEED_C ((long)299792458)
// 1271 nm
#define WL_1271_FREQ_A  (236.75)
#define WL_1271_FREQ_B  (236.15)
#define WL_1271_FREQ_C  (235.4)
#define WL_1271_FREQ_D  (234.8)

// 1291 nm
#define WL_1291_FREQ_A  (233.15)
#define WL_1291_FREQ_B  (232.55)
#define WL_1291_FREQ_C  (231.8)
#define WL_1291_FREQ_D  (231.2)

// 1331 nm
#define WL_1331_FREQ_A  (226.10)
#define WL_1331_FREQ_B  (225.55)
#define WL_1331_FREQ_C  (224.86)
#define WL_1331_FREQ_D  (224.31)

// 1351 nm
#define WL_1351_FREQ_A  (222.80)
#define WL_1351_FREQ_B  (222.25)
#define WL_1351_FREQ_C  (221.56)
#define WL_1351_FREQ_D  (221.01)

// 1411 nm
#define WL_1411_FREQ_A  (213.23)
#define WL_1411_FREQ_B  (212.72)
#define WL_1411_FREQ_C  (212.10)
#define WL_1411_FREQ_D  (211.60)

// 1431 nm
#define WL_1431_FREQ_A  (210.23)
#define WL_1431_FREQ_B  (209.73)
#define WL_1431_FREQ_C  (209.10)
#define WL_1431_FREQ_D  (208.60)

// 1451 nm
#define WL_1451_FREQ_A  (207.28)
#define WL_1451_FREQ_B  (206.83)
#define WL_1451_FREQ_C  (206.26)
#define WL_1451_FREQ_D  (205.81)

// 1471 nm
#define WL_1471_FREQ_A  (204.46)
#define WL_1471_FREQ_B  (204.01)
#define WL_1471_FREQ_C  (203.45)
#define WL_1471_FREQ_D  (203.00)

// 1491 nm
#define WL_1491_FREQ_A  (201.76)
#define WL_1491_FREQ_B  (201.31)
#define WL_1491_FREQ_C  (200.75)
#define WL_1491_FREQ_D  (200.30)

// 1511 nm
#define WL_1511_FREQ_A  (199.06)
#define WL_1511_FREQ_B  (198.61)
#define WL_1511_FREQ_C  (198.05)
#define WL_1511_FREQ_D  (197.60)

// 1531 nm
#define WL_1531_FREQ_A  (195.70)
#define WL_1531_FREQ_B  (195.30)
#define WL_1531_FREQ_C  (194.80)
#define WL_1531_FREQ_D  (194.40)

// 1551 nm
#define WL_1551_FREQ_A  (193.40)
#define WL_1551_FREQ_B  (193.00)
#define WL_1551_FREQ_C  (192.50)
#define WL_1551_FREQ_D  (192.10)

//

unsigned int wavelength_group_get(void)
{
  unsigned int  lf_l1, lf_l2, grpNo;
  PAGE_02H_MEMORY_MAP * p02_memPtr;
  double  freq;
  
  
  p02_memPtr = (PAGE_02H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P02H_Up[0];
  
  lf_l1 = __swap_bytes(p02_memPtr->LFL1);
  lf_l2 = __swap_bytes(p02_memPtr->LFL2);
  
  freq = (double)lf_l1 + ((double)lf_l2 / 10000.0);
  grpNo = 0;

  if (freq <= WL_1431_FREQ_D)
  {  // 1271 ~ 1431
    if (freq <= WL_1331_FREQ_D)
    {  // 1271 ~ 1331
      if (freq <= WL_1291_FREQ_D)
      {  // 1271 ~ 1291
        if (freq <= WL_1271_FREQ_D)
        { // 1271
          if (freq == WL_1271_FREQ_A)
          {
            grpNo = 0;
          }
          else if (freq == WL_1271_FREQ_B)
          {
            grpNo = 1;
          }
          else if (freq == WL_1271_FREQ_C)
          {
            grpNo = 2;
          }
          else if (freq == WL_1271_FREQ_D)
          {
            grpNo = 3;
          }
          else
          {
            grpNo = 0;
          }
        }
        else
        { // 1291
          if (freq == WL_1291_FREQ_A)
          {
            grpNo = 0;
          }
          else if (freq == WL_1291_FREQ_B)
          {
            grpNo = 1;
          }
          else if (freq == WL_1291_FREQ_C)
          {
            grpNo = 2;
          }
          else if (freq == WL_1291_FREQ_D)
          {
            grpNo = 3;
          }
          else
          {
            grpNo = 0;
          }          
        }       
      }
      else
      { // 1331
        if (freq == WL_1331_FREQ_A)
        {
          grpNo = 0;
        }
        else if (freq == WL_1331_FREQ_B)
        {
          grpNo = 1;
        }
        else if (freq == WL_1331_FREQ_C)
        {
          grpNo = 2;
        }
        else if (freq == WL_1331_FREQ_D)
        {
          grpNo = 3;
        }
        else
        {
          grpNo = 0;
        }          
        
      }

    }
    else
    {  // 1351 ~ 1431
      if (freq <= WL_1411_FREQ_D)
      {  // 1351 ~ 1411
        if (freq <= WL_1351_FREQ_D)
        {  // 1351
          if (freq == WL_1351_FREQ_A)
          {
            grpNo = 0;
          }
          else if (freq == WL_1351_FREQ_B)
          {
            grpNo = 1;
          }
          else if (freq == WL_1351_FREQ_C)
          {
            grpNo = 2;
          }
          else if (freq == WL_1351_FREQ_D)
          {
            grpNo = 3;
          }
          else
          {
            grpNo = 0;
          }
        }
        else
        { // 1411
          if (freq == WL_1411_FREQ_A)
          {
            grpNo = 0;
          }
          else if (freq == WL_1411_FREQ_B)
          {
            grpNo = 1;
          }
          else if (freq == WL_1411_FREQ_C)
          {
            grpNo = 2;
          }
          else if (freq == WL_1411_FREQ_D)
          {
            grpNo = 3;
          }
          else
          {
            grpNo = 0;
          }          
          
        }
        
      }
      else 
      { // 1431
        if (freq == WL_1431_FREQ_A)
        {
          grpNo = 0;
        }
        else if (freq == WL_1431_FREQ_B)
        {
          grpNo = 1;
        }
        else if (freq == WL_1431_FREQ_C)
        {
          grpNo = 2;
        }
        else if (freq == WL_1431_FREQ_D)
        {
          grpNo = 3;
        }
        else
        {
          grpNo = 0;
        }          
        
      }
    }
  }
  else
  {  // 1451 ~ 1551
    if (freq <= WL_1491_FREQ_D)
    {  // 1451 ~ 1491
      
      if (freq <= WL_1471_FREQ_D)
      {  // 1451 ~ 1471
        
        if (freq <= WL_1451_FREQ_D)
        {  // 1451
          if (freq == WL_1451_FREQ_A)
          {
            grpNo = 0;
          }
          else if (freq == WL_1451_FREQ_B)
          {
            grpNo = 1;
          }
          else if (freq == WL_1451_FREQ_C)
          {
            grpNo = 2;
          }
          else if (freq == WL_1451_FREQ_D)
          {
            grpNo = 3;
          }
          else
          {
            grpNo = 0;
          }          
          
        }
        else
        {  // 1471
          if (freq == WL_1471_FREQ_A)
          {
            grpNo = 0;
          }
          else if (freq == WL_1471_FREQ_B)
          {
            grpNo = 1;
          }
          else if (freq == WL_1471_FREQ_C)
          {
            grpNo = 2;
          }
          else if (freq == WL_1471_FREQ_D)
          {
            grpNo = 3;
          }
          else
          {
            grpNo = 0;
          }          
          
        }        
      }
      else
      {  // 1491
        if (freq == WL_1491_FREQ_A)
        {
          grpNo = 0;
        }
        else if (freq == WL_1491_FREQ_B)
        {
          grpNo = 1;
        }
        else if (freq == WL_1491_FREQ_C)
        {
          grpNo = 2;
        }
        else if (freq == WL_1491_FREQ_D)
        {
          grpNo = 3;
        }
        else
        {
          grpNo = 0;
        }          
        
      }
      
    }
    else
    {  // 1511 ~ 1551
      
      if (freq <= WL_1531_FREQ_D)
      {  // 1511 ~ 1531
        
        if (freq <= WL_1511_FREQ_D)
        {  // 1511
          if (freq == WL_1511_FREQ_A)
          {
            grpNo = 0;
          }
          else if (freq == WL_1511_FREQ_B)
          {
            grpNo = 1;
          }
          else if (freq == WL_1511_FREQ_C)
          {
            grpNo = 2;
          }
          else if (freq == WL_1511_FREQ_D)
          {
            grpNo = 3;
          }
          else
          {
            grpNo = 0;
          }          
          
        }
        else
        {  // 1531
          if (freq == WL_1531_FREQ_A)
          {
            grpNo = 0;
          }
          else if (freq == WL_1531_FREQ_B)
          {
            grpNo = 1;
          }
          else if (freq == WL_1531_FREQ_C)
          {
            grpNo = 2;
          }
          else if (freq == WL_1531_FREQ_D)
          {
            grpNo = 3;
          }
          else
          {
            grpNo = 0;
          }          
          
        }        
      }
      else
      {  // 1551
        if (freq == WL_1551_FREQ_A)
        {
          grpNo = 0;
        }
        else if (freq == WL_1551_FREQ_B)
        {
          grpNo = 1;
        }
        else if (freq == WL_1551_FREQ_C)
        {
          grpNo = 2;
        }
        else if (freq == WL_1551_FREQ_D)
        {
          grpNo = 3;
        }
        else
        {
          grpNo = 0;
        }          
        
      }
      
    }
      
  }
  return grpNo;
}

unsigned int wavelength_info_get(void)
{
  unsigned int  lf_l1, lf_l2, chNo, wavelength_value;
  PAGE_02H_MEMORY_MAP * p02_memPtr;
  double  freq;
  
  
  p02_memPtr = (PAGE_02H_MEMORY_MAP *)&I2C_Slave_Buffer_A2_P02H_Up[0];
  
  lf_l1 = __swap_bytes(p02_memPtr->LFL1);
  lf_l2 = __swap_bytes(p02_memPtr->LFL2);
  
  
  chNo = __swap_bytes(p02_memPtr->Channel_Number_Set);

  if ((chNo > 0) && (chNo < 9))
  {
    chNo = (chNo - 1)%4;
  }
  else
  {
    chNo = 0;
  }
  
  lf_l2 = lf_l2 + (chNo * 150);
  
  freq = (double)lf_l1 + ((double)lf_l2 / 10000.0);
  
  wavelength_value = freq;

}

#endif

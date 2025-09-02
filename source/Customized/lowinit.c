/*
 * lowinit.c
 *
 * This module contains the function '__low_level_init', a function
 * that is called before the 'main' function of the program.  Normally
 * low-level initializations - such as setting the prefered interrupt
 * level or setting the watchdog - can be performed here.
 *
 * Note that this function is called before the data segments are
 * initialized, this means that this function can't rely on the
 * values of global or static variables.
 *
 * When this function returns zero, the startup code will inhibit the
 * initialization of the data segments.  The result is faster startup,
 * the drawback is that neither global nor static data will be
 * initialized.
 *
 * Copyright 1999-2004 IAR Systems. All rights reserved.
 *
 * $Revision: 907 $
 */
#include <iods4835.h>
#pragma language=extended

__fastcall
unsigned char 
__low_level_init ( void )
{
  /*==================================*/
  /*  Disable Watchdog                */
  /*  before segment initializations  */
  /*==================================*/
  WDCN_bit.EWT  = 0;                                                            //Disable reset on watchdog
  WDCN_bit.WD1  = 1;                                                            // 
  WDCN_bit.WD0  = 1;                                                            //21 count -> 131.104ms
  WDCN_bit.RWT  = 1;                                                            //Reset watchdog timer     
  /*==================================*/
  /* Choose if segment initialization */
  /* should be done or not.           */
  /* Return: 0 to omit seg_init       */
  /*         1 to run seg_init        */
  /*==================================*/

  return (1);
}

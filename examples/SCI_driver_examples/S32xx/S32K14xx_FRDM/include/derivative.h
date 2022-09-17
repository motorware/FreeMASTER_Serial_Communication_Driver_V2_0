/*
 * Note: This file is recreated by the project wizard whenever the MCU is
 *       changed and should not be edited by hand
 */

/* Include the derivative-specific header file */

#define __FPU_PRESENT 1

/* Watchdog disable */
#ifndef DISABLE_WDOG
  #define DISABLE_WDOG                 1
#endif

/** __FPU_USED indicates whether an FPU is used or not. For this, __FPU_PRESENT has to be checked prior to making use of FPU specific registers and functions.
*/

#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    #if (__FPU_PRESENT == 1)
        #define __FPU_USED       1
    #else
        #warning "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
        #define __FPU_USED       0
    #endif
#else
    #if defined(__GNUC__)
        #define __FPU_USED       0
    #endif
#endif

#include "S32K144.h"




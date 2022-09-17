/**
*   @file    nvic.c
*   @version M4_SRC_SW_VERSION_MAJOR.M4_SRC_SW_VERSION_MINOR.1.0
*
*   @brief   AUTOSAR M4_SRC_MODULE_NAME - nvic driver
*   @details Functions that manage interrupts and exceptions via the NVIC (adapted from CMSIS_core)

*   This file contains sample code only. It is not part of the production code deliverables.
*
*   @addtogroup BUILD_ENV
*   @{
*/
/*==================================================================================================
*   Project              : M4_SRC_PROJECT_NAME
*   Platform             : M4_SRC_MCU_FAMILY
*   Peripheral           : M4_SRC_USED_PERIPHERAL
*   Dependencies         : M4_SRC_AR_MODULE_DEPENDENCY
*
*   Autosar Version      : M4_SRC_AR_SPEC_VERSION_MAJOR.M4_SRC_AR_SPEC_VERSION_MINOR.M4_SRC_AR_SPEC_VERSION_PATCH
*   Autosar Revision     : M4_SRC_AR_RELEASE_REVISION
*   Autosar Conf.Variant :
*   SW Version           : M4_SRC_SW_VERSION_MAJOR.M4_SRC_SW_VERSION_MINOR.M4_SRC_SW_VERSION_PATCH
*   Build Version        : M4_SRC_BUILD_ID
*
*   (c) Copyright M4_SRC_YEAR_ID M4_SRC_COPYRIGHTED_TO
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
ifdef(`M4_SRC_KEEP_REVISION_HISTORY', `dnl - DO NOT modify this M4 line!
Revision History:
                             Modification     Tracking
Author (core ID)              Date D/M/Y       Number     Description of Changes
---------------------------   ----------    ------------  ------------------------------------------
Marius Rotaru (rtrm001)       08/06/2015    ENGR00345201  Create NVIC driver
---------------------------   ----------    ------------  ------------------------------------------
',)dnl - DO NOT modify this M4 line!
==================================================================================================*/
#include "typedefs.h"
#include "StdRegMacros.h"
#include "Std_Types.h"
#include "nvic.h"
#include "s32k144.h"

/*==================================================================================================
*                                        LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*================================================================================================*/
/** 
* @brief Set Priority Grouping
* @details The function sets the priority grouping field using the required unlock sequence.
*  The parameter PriorityGroup is assigned to the field SCB->AIRCR [10:8] PRIGROUP field.
*   Only values from 0..7 are used.
*   In case of a conflict between priority grouping and available
*   priority bits (__NVIC_PRIO_BITS), the smallest possible priority group is set
*/
/*================================================================================================*/
void NVIC_SetPriorityGrouping(uint32 PriorityGroup)
{
    /* Set the PRIGROUP[10:8] bits according to NVIC_PriorityGroup value */
    /* CM4.AIRCR.R = (uint32)0x05FA0000 | PriorityGroup; */
    FSL_SCB->AIRCR = 0x05FA0000;
}

/*================================================================================================*/
/** 
* @brief Enable External Interrupt
* @details The function enables a device-specific interrupt in the NVIC interrupt controller.
*/
/*================================================================================================*/ 
void NVIC_EnableIRQ(uint8 IRQn)
 {
    REG_BIT_SET32((NVIC_BASEADDR + NVIC_ISER_OFFSET(IRQn)), 1 << (IRQn % 32) ); /* enable interrupt */
 }

/*================================================================================================*/
/** 
* @brief Disable External Interrupt
* @details The function disables a device-specific interrupt in the NVIC interrupt controller
*/
/*================================================================================================*/  
void NVIC_DisableIRQ(uint8 IRQn)
{
    REG_WRITE32((NVIC_BASEADDR + NVIC_ICER_OFFSET(IRQn)), 1 << (IRQn % 32) );
}

/*================================================================================================*/
/** 
* @brief Set Interrupt Priority
* @details The function sets the priority of an interrupt.
*/
/*================================================================================================*/  
void NVIC_SetPriority(uint8 IRQn, uint8 priority)
{
    REG_RMW32((NVIC_BASEADDR + NVIC_IPRO_OFFSET(IRQn)), NVIC_IPRO_MASK(IRQn), priority );
}

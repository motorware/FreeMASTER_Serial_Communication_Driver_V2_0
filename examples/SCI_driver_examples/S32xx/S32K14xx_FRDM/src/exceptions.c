/*================================================================================================*/
/**
*   @file    exceptions.c
*   @version M4_SRC_SW_VERSION_MAJOR.M4_SRC_SW_VERSION_MINOR.1.0
*
*   @brief   AUTOSAR M4_SRC_MODULE_NAME - Interrupts table for M4
*   @details Interrupts table for M4
*            This file contains sample code only. It is not part of the production code deliverables
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
Marius Rotaru (rtrm001)       14/07/2015    ENGR00345201  FileCreation
---------------------------   ----------    ------------  ------------------------------------------
',)dnl - DO NOT modify this M4 line!
==================================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif


#if defined(__IAR_SYSTEMS_ICC__)
#pragma location=".systeminit"
#else
__attribute__ ((section (".systeminit"))) 
#endif
void NMI_Handler(void)
{
    while(1);
}
#if defined(__IAR_SYSTEMS_ICC__)
#pragma location=".systeminit"
#else
__attribute__ ((section (".systeminit"))) 
#endif
void HardFault_Handler(void)
{
    while(1);
}
#if defined(__IAR_SYSTEMS_ICC__)
#pragma location=".systeminit"
#else
__attribute__ ((section (".systeminit"))) 
#endif
void MemManage_Handler(void)
{
    while(1);
}
#if defined(__IAR_SYSTEMS_ICC__)
#pragma location=".systeminit"
#else
__attribute__ ((section (".systeminit"))) 
#endif
void BusFault_Handler(void)
{
    while(1);
}
#if defined(__IAR_SYSTEMS_ICC__)
#pragma location=".systeminit"
#else
__attribute__ ((section (".systeminit"))) 
#endif
void UsageFault_Handler(void)
{
    while(1);
}
#if defined(__IAR_SYSTEMS_ICC__)
#pragma location=".systeminit"
#else
__attribute__ ((section (".systeminit"))) 
#endif
void SVC_Handler(void)
{
    while(1);
}
#if defined(__IAR_SYSTEMS_ICC__)
#pragma location=".systeminit"
#else
__attribute__ ((section (".systeminit"))) 
#endif
void DebugMon_Handler(void)
{
    while(1);
}
#if defined(__IAR_SYSTEMS_ICC__)
#pragma location=".systeminit"
#else
__attribute__ ((section (".systeminit"))) 
#endif
void PendSV_Handler(void)
{
    while(1);
}
#if defined(__IAR_SYSTEMS_ICC__)
#pragma location=".systeminit"
#else
__attribute__ ((section (".systeminit"))) 
#endif
void SysTick_Handler(void)
{
    while(1);
}
#if defined(__IAR_SYSTEMS_ICC__)
#pragma location=".systeminit"
#else
__attribute__ ((section (".systeminit"))) 
#endif
void undefined_handler(void)
{
   while(1);
}


#ifdef __cplusplus
}
#endif




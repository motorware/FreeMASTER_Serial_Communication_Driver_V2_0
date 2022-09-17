/******************************************************************************
*
*   (c) Copyright 2004-2016 NXP Semiconductors, Inc.
*   All Rights Reserved.
*
******************************************************************************/
/*!
*
*   @file    compiler.h
*
*   @brief   Compiler abstraction.
*
******************************************************************************/
#ifndef COMPILER_H
#define COMPILER_H

#ifdef __cplusplus
extern "C"{
#endif

/* Green Hills */
#ifdef __ghs__
    #define ASM                 asm
    #define INTERRUPT_FUNC
#endif

/* GCC */
#ifdef __GNUC__
    #define ASM                 __asm
    #define INTERRUPT_FUNC      __attribute__ ((interrupt))
#endif

/* IAR */
#ifdef __IAR_SYSTEMS_ICC__
    #define ASM                 __asm
    #define INTERRUPT_FUNC      __irq
#endif

#ifdef __cplusplus
}
#endif

#endif

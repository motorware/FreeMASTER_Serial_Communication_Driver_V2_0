/******************************************************************************
*
*   (c) Copyright 2004-2016 NXP Semiconductors, Inc.
*   All Rights Reserved.
*
******************************************************************************/
/*!
*
*   @file    periphinit.h
*
*   @brief   Header file for MCU peripherals settings which are
*            needed for FreeMASTER example application.
*
******************************************************************************/
extern void init_all(void);
extern void EnableIrq(void);
extern void DisableIrq(void);
extern void DisableCAN(void);
extern void delay_us(volatile int us);
extern uint16_t SPI_0_SendWord(uint16_t ui16Data);

#define US_TO_CYCLES(x) (x * 11)

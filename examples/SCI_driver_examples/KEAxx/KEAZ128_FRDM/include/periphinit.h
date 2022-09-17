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
void init_all(void);
void UART2_Init(void);
void UART2_Enable_Interrupt(void);
void SPI1_Init(void);
void MSCAN_Init(void);
void MSCAN_Enable_Interrupt(void);
void delay_us(volatile int us);
uint16_t SPI_SendWord(uint16_t ui16Data);
#define US_TO_CYCLES(x) (x * 3)
/******************************************************************************
*
*   (c) Copyright 2004-2016 NXP Semiconductors, Inc.
*   All Rights Reserved.
*
******************************************************************************/
/*!
*
*   @file    periphinit.c
*
*   @brief   This file contains functions for MCU peripherals settings which are
*            needed for FreeMASTER example application.
*
******************************************************************************/

#ifdef __cplusplus
extern "C"{
#endif

#include "derivative.h"
#include "core_cm0plus.h"
#include "core_cmFunc.h"
#include "MC33903_routines.h"
#include "freemaster.h"
#include "freemaster_KEAxx.h"
#include "periphinit.h"


/******************************************************************************
* Local functions
******************************************************************************/

#if FMSTR_USE_SCI
/* Configure UART2 */
void UART2_Init()
{
    /* Enable power for UART2*/
    SIM->SCGC |= SIM_SCGC_UART2_MASK;
    /* Speed = 24MHz/(16*13) == 115384 bit/s */
    UART2->BDL = 13;
    UART2->C1 = 0;
    UART2->C2 = UART_C2_TE_MASK|UART_C2_RE_MASK;
}
/* UART2 interrupt handler */
void UART2_IRQHandler()
{
    FMSTR_Isr();
}
/* Set UART2 interrupt handler */
void UART2_Enable_Interrupt()
{
    __disable_irq();
    NVIC_EnableIRQ(14);
    __enable_irq();
}
#endif

#if FMSTR_USE_MSCAN
/* Configure SPI1 */
void SPI1_Init()
{
    /* Enable SPI power */
    SIM->SCGC |= SIM_SCGC_SPI1_MASK;

    /* SPI enable, master mode, sampling at falling edges */
    SPI1_C1 = 0x54;
    /* Slave select output pin not used by SPI module */
    SPI1_C2 = 0x00;

    /* Baud rate prescaler and divider */
    /* SPIBaudRate = Bus_clock/BaudRateDivisor */
    /* BaudRateDivisor = (SPPR+1)*2^(SPR+1) = (0+1)*2^(2+1) */
    /* For SPIBaudRate = 3.0MHz and BusClock = 24MHz, BaudRateDivisor = 8 */
    SPI1_BR = (0 << SPI_BR_SPPR_SHIFT) | 2;

    /* Read the data register to clear the status flags */
    (void)SPI1_D;
    /* Read the status register and */
    (void)SPI1_S;

    /* Configure SPI's pin direction */
    GPIOA->PDDR = 0x0B000000;
}

/* Configure MSCAN */
void MSCAN_Init()
{
    unsigned int i;

    /* Enable MSCAN power */
    SIM->SCGC |= SIM_SCGC_MSCAN_MASK;

    /* 500kb/s @ 24MHz */
    /* Set to Init mode */
    MSCAN->CANCTL0 |= MSCAN_CANCTL0_INITRQ_MASK;
    while((MSCAN->CANCTL1&MSCAN_CANCTL1_INITAK_MASK) != MSCAN_CANCTL1_INITAK_MASK) {
        ; /* Wait for init acknowledge */
    }
    /* Enables MSCAN module */
    MSCAN->CANCTL1 = (MSCAN_CANCTL1_CANE_MASK | MSCAN_CANCTL1_CLKSRC_MASK);
    /* Sets TimeSegments */
    MSCAN->CANBTR1 = MSCAN_CANBTR1_TSEG1(9-1);
    MSCAN->CANBTR1 |= MSCAN_CANBTR1_TSEG2(6-1); /* 8MHz/(9+6+1) == 500kbit/s */
    /* Sets Prescaller=3 */
    MSCAN->CANBTR0 = MSCAN_CANBTR0_BRP(3-1); /* 24MHz/3=8MHz on MSCAN */
    MSCAN->CANBTR0 |= MSCAN_CANBTR0_SJW(1-1);
    /* Sets two 32 bit acceptance filters */
    MSCAN->CANIDAC = 0;
    /* Clears ID */
    MSCAN->CANIDAR_BANK_1[0] = 0;
    MSCAN->CANIDAR_BANK_1[1] = 0;
    MSCAN->CANIDAR_BANK_1[2] = 0;
    MSCAN->CANIDAR_BANK_1[3] = 0;
    MSCAN->CANIDAR_BANK_2[0] = 0;
    MSCAN->CANIDAR_BANK_2[1] = 0;
    MSCAN->CANIDAR_BANK_2[2] = 0;
    MSCAN->CANIDAR_BANK_2[3] = 0;
    /* Sets Filter Mask */
    MSCAN->CANIDMR_BANK_1[0] = 255;
    MSCAN->CANIDMR_BANK_1[1] = 255;
    MSCAN->CANIDMR_BANK_1[2] = 255;
    MSCAN->CANIDMR_BANK_1[3] = 255;
    MSCAN->CANIDMR_BANK_2[0] = 255;
    MSCAN->CANIDMR_BANK_2[1] = 255;
    MSCAN->CANIDMR_BANK_2[2] = 255;
    MSCAN->CANIDMR_BANK_2[3] = 255;

    /* Sets normal mode */
    MSCAN->CANCTL0 &= ~MSCAN_CANCTL0_INITRQ_MASK;
    while(MSCAN->CANCTL1 & MSCAN_CANCTL1_INITAK_MASK) {
        ; /* Wait for init mode exit */
    }
    /* CAN0CTL0: RXFRM=0,RXACT=0,CSWAI=0,SYNCH=0,TIME=0,WUPE=0,SLPRQ=0,INITRQ=0 */
    MSCAN->CANCTL0 = 0;
    /* Disable all RX interrupts */
    MSCAN->CANRIER = 0;
    /* Disable all TX interrupts */
    MSCAN->CANTIER = 0;

    /* Clear Receive buffer */
    MSCAN->RSIDR0 = 0;
    MSCAN->RSIDR1 = 0;
    for (i=0; i<8; ++i)
        MSCAN->REDSR[i] = 0;
    MSCAN->RDLR = 0;
}

/* MSCAN receive interrupt handler */
void MSCAN_RX_IRQHandler()
{
    FMSTR_Isr();
}

/* MSCAN transmit interrupt handler */
void MSCAN_TX_IRQHandler()
{
    FMSTR_Isr();
}

/* Set MSCAN interrupt handlers */
void MSCAN_Enable_Interrupt()
{
    __disable_irq();
    NVIC_EnableIRQ(30);
    NVIC_EnableIRQ(31);
    __enable_irq();
}
#endif

/******************************************************************************
* Global functions
******************************************************************************/
/* Initialization of all peripherals */
void init_all(void)
{
#if FMSTR_USE_SCI
    UART2_Init();
    UART2_Enable_Interrupt();
#endif

#if FMSTR_USE_MSCAN
    SPI1_Init();
    MC33903_Config();
    MSCAN_Init();
    MSCAN_Enable_Interrupt();
#endif
}

/* Send word through SPI1 */
uint16_t SPI_SendWord(uint16_t ui16Data)
{
    uint16_t ui16OutData;
    GPIOA->PCOR = 0x08000000;

    /* Wait for empty data register */
    while ((SPI1_S & SPI_S_SPTEF_MASK) == 0)
    {
    }
    /* Load first 8-bit word into data transmission register */
    SPI1_D = (uint8_t)(ui16Data >> 8);
    /* Wait for the end of the transfer */
    while ((SPI1_S & SPI_S_SPRF_MASK) == 0)
    {
    }
    /* Store the second 8-bit word */
    ui16OutData = SPI1_D;
    /* Wait for empty data register */
    while ((SPI1_S & SPI_S_SPTEF_MASK) == 0)
    {
    }
    /* Load the second 8-bit word into data transmission register */
    SPI1_D = (uint8_t)ui16Data;
    /* Wait for the end of the transfer */
    while ((SPI1_S & SPI_S_SPRF_MASK) == 0)
    {
    }
    ui16OutData |= (uint16_t)(SPI1_D << 8); /* Store the first 8-bit word */

    GPIOA->PSOR = 0x08000000;
    return ui16OutData;
}

/* Microseconds delay */
void delay_us(volatile int us)
{
    uint32_t cycles = US_TO_CYCLES(us);
    /* Delay function - do nothing for a number of cycles */
    while(cycles--);
}

#ifdef __cplusplus
}
#endif

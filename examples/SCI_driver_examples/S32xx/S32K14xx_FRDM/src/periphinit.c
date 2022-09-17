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

#include "S32K144.h"
#include "compiler.h"
#include "freemaster.h"
#include "freemaster_S32xx.h"
#include "Std_Types.h"
#include "periphinit.h"
#include "MC33903_routines.h"
#include "nvic.h"

/******************************************************************************
* Local function prototypes
******************************************************************************/
void clk_init(void);
void FlexCAN_0_Init(void);
void GPIO_Init_CAN(void);

/* Microseconds delay */
void delay_us(volatile int us)
{
    uint32_t cycles = US_TO_CYCLES(us);
    /* Delay function - do nothing for a number of cycles */
    while(cycles--);
}

/* Function used to enable the interrupt number id and set up the priority */
void sys_enableIsrSource(uint8 id, uint8 prio)
{
    NVIC_EnableIRQ(id);
    NVIC_SetPriority(id, prio);
}

/* Function used to register the interrupt handler in the interrupt vector */
void  sys_registerIsrHandler(uint8_t irq_id, uint32 isr_handler)
{
    REG_WRITE32(REG_READ32(0xE000ED08) + ((16 + irq_id) << 2), isr_handler);
}

/* Enable external interrupts */
void EnableIrq(void)
{
    ASM(" cpsie i");
}

/* Disable external interrupts */
void DisableIrq(void)
{
    ASM(" cpsid i");
}

/******************************************************************************
* Local functions
******************************************************************************/
/* Clock init */
void clk_init(void)
{
    /* System clock initialization */

    /* FIRC Configuration */
    /* SCG_FIRCDIV: FIRCDIV3=1, FIRCDIV2=1, FIRCDIV1=1 */
    SCG->FIRCDIV = SCG_FIRCDIV_FIRCDIV1(1) | SCG_FIRCDIV_FIRCDIV2(1);
    /* SCG_FIRCCFG: RANGE=0 */
    SCG->FIRCCFG = 0;
    while(SCG->FIRCCSR & SCG_FIRCCSR_LK_MASK);
    /* SCG_FIRCCSR: FIRCEN=1 */
    SCG->FIRCCSR = SCG_FIRCCSR_FIRCEN(1);
    while(!(SCG->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK));

    /* SIRC Configuration */
    SCG->SIRCDIV = SCG_SIRCDIV_SIRCDIV1(1) | SCG_SIRCDIV_SIRCDIV2(1);
    SCG->SIRCCFG = 0x01; /* SCG_SIRCCFG: RANGE=1 */
    while(SCG->FIRCCSR & SCG_SIRCCSR_LK_MASK);
    SCG->SIRCCSR = SCG_SIRCCSR_SIRCEN(1);
    while(!(SCG->SIRCCSR & SCG_SIRCCSR_SIRCVLD_MASK));

    /* SOSC Configuration */ 
    /* 8 MHz crystal */
    SCG->SOSCDIV = SCG_SOSCDIV_SOSCDIV1(1) | SCG_SOSCDIV_SOSCDIV2(1);
    SCG->SOSCCFG = SCG_SOSCCFG_EREFS(1) | SCG_SOSCCFG_RANGE(3);
    while(SCG->SOSCCSR & SCG_SIRCCSR_LK_MASK);
    SCG->SOSCCSR |= SCG_SOSCCSR_SOSCEN(1);
    while(!(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK));

    /* SPLL Configuration 112 MHz */
    /* SCG_SPLLDIV: SPLLDIV3=1, SPLLDIV2=1, SPLLDIV1=1 */
    SCG->SPLLDIV = SCG_SPLLDIV_SPLLDIV1(1) | SCG_SPLLDIV_SPLLDIV2(3);
    /* 8 MHz / 1 = 8 MHz */
    /* 8 MHz / 1 * 28 = 224 MHz VCO, I guess that means 112 MHz PLL (?) */
    /* system OSC (8 MHz) */
    SCG->SPLLCFG = SCG_SPLLCFG_PREDIV(0) | SCG_SPLLCFG_MULT(4);
    while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK);

    SCG->SPLLCSR |= SCG_SPLLCSR_SPLLEN(1);          /* SCG_SPLLCSR: SPLLEN=1 */
    while(!(SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK));

    /* configure  RUN mode */
    /* CORE_CLK = 80 MHz; SYS_CLK = 80 MHz; BUS_CLK = 40 MHz; FLASH_CLK = 20 MHz; src = PLL  */
    SCG->RCCR = SCG_RCCR_DIVCORE(0) | SCG_RCCR_DIVPLAT(0) | SCG_RCCR_DIVBUS(1) | SCG_RCCR_DIVSLOW(3) | SCG_RCCR_SCS(6);

    /* Switch to run mode */
    SMC->PMCTRL = SMC_PMCTRL_RUNM(0);
    while(!(SMC->PMSTAT & 0x00000001u));
}

/* This function initializes the GPIO pins for FlexCAN0 */
void GPIO_Init_CAN(void)
{
    /* FlexCAN0 TxD pin */
    /* Alternative 5 (CAN0_TX) */
    PORTE->PCR[5] = PORT_PCR_MUX(5) | PORT_PCR_DSE(1) | PORT_PCR_PE(0) | PORT_PCR_PS(1);

    /* FlexCAN0 RxD pin */
    /* Alternative 5 (CAN0_RX) */
    PORTE->PCR[4] = PORT_PCR_MUX(5) | PORT_PCR_PFE(0) | PORT_PCR_PE(1) | PORT_PCR_PS(1);
}

void GPIO_Init_LPUART1(void)
{
    /* LPUART1 TxD pin */
    /* Alternative 2 (LPUART1_TX) */
    PORTC->PCR[7] = PORT_PCR_MUX(2);
    /* PTD7 configured as output */
    PTC->PSOR |= 0x00000080;
    PTC->PDDR |= 0x00000080;

    /* LPUART1 RxD pin */
    /* Alternative 2 (LPUART1_RX) */
    PORTC->PCR[6] = PORT_PCR_MUX(2);
}

/* This function initializes the GPIO pins for LSPI */
void GPIO_Init_LPSPI1(void)
{
    /* SPI1_SCK pin */
    PORTB->PCR[14] = PORT_PCR_MUX(3) | PORT_PCR_PE(0) | PORT_PCR_PS(1);
    PTB->PSOR = 0x00004000;
    PTB->PDDR |= 0x00004000;

    /* SPI1_SCK SIN pin */
    PORTB->PCR[15] = PORT_PCR_MUX(3) | PORT_PCR_PE(1) | PORT_PCR_PS(1);

    /* SPI1_MOSI pin */
    PORTB->PCR[16] = PORT_PCR_MUX(3) | PORT_PCR_PE(0) | PORT_PCR_PS(1);
    PTB->PSOR = 0x00010000;
    PTB->PDDR |= 0x00010000;

    /* SPI1_PCS pin */
    PORTB->PCR[17] = PORT_PCR_MUX(3) | PORT_PCR_PE(0) | PORT_PCR_PS(1);
    PTB->PSOR = 0x00020000;
    PTB->PDDR |= 0x00020000;
}

void LPSPI1_init(void)
{
    /* Enable clock */
    PCC->PCCn[ PCC_LPSPI1_INDEX ] = PCC_PCCn_PCS(3);
    PCC->PCCn[ PCC_LPSPI1_INDEX ] = PCC_PCCn_PCS(3) | PCC_PCCn_PR(1) | PCC_PCCn_CGC(1);

    /* Configure LPSPI1*/
    LPSPI1->CR = LPSPI_CR_MEN(1) | LPSPI_CR_DBGEN(1);
    LPSPI1->CFGR1 = LPSPI_CFGR1_MASTER(1);
    LPSPI1->CCR = LPSPI_CCR_SCKDIV(255) | LPSPI_CCR_DBT(255) | LPSPI_CCR_PCSSCK(255) | LPSPI_CCR_SCKDIV(255);
    LPSPI1->TCR = LPSPI_TCR_FRAMESZ(15) | LPSPI_TCR_PCS(3) | LPSPI_TCR_PRESCALE(0);
}

/* This function initializes the LPUART1 */
void LPUART1_init(void)
{
    /* Enable clock */
    PCC->PCCn[ PCC_LPUART1_INDEX ] = PCC_PCCn_PCS(6);
    PCC->PCCn[ PCC_LPUART1_INDEX ] = PCC_PCCn_PCS(6) | PCC_PCCn_PR(1) | PCC_PCCn_CGC(1);

    /* Software Reset - on */
    LPUART1->GLOBAL |= LPUART_GLOBAL_RST_MASK ;
    ASM(" nop");
    ASM(" nop");
    ASM(" nop");
    ASM(" nop");
    ASM(" nop");
    ASM(" nop");
    ASM(" nop");
    ASM(" nop");
    ASM(" nop");
    ASM(" nop");
    /* Software Reset - off */
    LPUART1->GLOBAL &= ~LPUART_GLOBAL_RST_MASK;
    ASM(" nop");
    ASM(" nop");
    ASM(" nop");
    ASM(" nop");
    ASM(" nop");
    ASM(" nop");
    ASM(" nop");
    ASM(" nop");
    ASM(" nop");
    ASM(" nop");

    /* Idle Line Type Select */
    /* Receiver Disble */
    /* Transmitter Disable */
    /* Receiver Interrupt Disable */
    /* Transmission Complete Interrupt Disable */
    /* Transmit Interrupt Disable */
    LPUART1->CTRL = LPUART_CTRL_ILT(0) | LPUART_CTRL_RE(0) | LPUART_CTRL_TE(0) | LPUART_CTRL_RIE(0) | LPUART_CTRL_TCIE(0) | LPUART_CTRL_TIE(0) | LPUART_CTRL_TXINV(0);

    /* Set baud rate to 115200 bit/s */
    /* Baud Rate Modulo Divisor. */
    /* RX Input Active Edge Interrupt Enable */
    /* Resynchronization Disable */
    /* Both Edge Sampling */
    /* Over Sampling Ratio (OSR+1) */
    LPUART1->BAUD = LPUART_BAUD_SBR(43) | LPUART_BAUD_RXEDGIE(0) | LPUART_BAUD_RESYNCDIS(0) | LPUART_BAUD_BOTHEDGE(1) | LPUART_BAUD_OSR(3);

    /* Receiver Enable */
    /* Transmitter Enable */
    LPUART1->CTRL |= LPUART_CTRL_RE(1) | LPUART_CTRL_TE(1);
}

/* FlexCAN0 init */
void FlexCAN_0_Init(void)
{
    int ii = 0;

    /* Disable the FlexCAN module */
    CAN0->MCR |= CAN_MCR_MDIS_MASK;
    while((CAN0->MCR & CAN_MCR_NOTRDY_MASK)!=CAN_MCR_NOTRDY_MASK);
    /* Sets clock source */
    /* 40 MHz bus clock */
    CAN0->CTRL1 |= CAN_CTRL1_CLKSRC(1);
    /* Enable the FlexCAN module */
    CAN0->MCR &= ~CAN_MCR_MDIS_MASK;

    /* Wait for entering the freeze mode */
    while((CAN0->MCR & CAN_MCR_FRZACK_MASK ) == 0){}
    /* Set Final bit rate: 500 kbit/s @40MHz */
    /* set prescaler, phase segments, clock sourceand propagation segment */
    CAN0->CTRL1 = CAN_CTRL1_PRESDIV(7) | CAN_CTRL1_RJW(3) | CAN_CTRL1_PSEG1(3) | CAN_CTRL1_PSEG2(3) | CAN_CTRL1_PROPSEG(0);
    /* Set Masks */
    /* Sets RX Global Mask */
    CAN0->RXMGMASK = 0xFFFFFFFFUL;
    /* Sets RX MB14 Mask */
    CAN0->RX14MASK = 0xFFFFFFFFUL;
    /* RX MB15 Mask */
    CAN0->RX15MASK = 0xFFFFFFFFUL;
    /* Clear all MB flags */
    CAN0->IFLAG1 = 0xFFFFFFFFUL;
    /* Disable all MB interrupts */
    CAN0->IMASK1 = 0x00000000UL;

    /* Set maximum number of FlaxCAN MB to 16 (of 32 available) */
    CAN0->MCR &= ~CAN_MCR_MAXMB_MASK;
    CAN0->MCR |= CAN_MCR_MAXMB(15);
    /* Transmit a frame in nominal rate */
    /* 8 bytes per message buffer for region 0 */
    /* 8 bytes per message buffer for region 1 */
    CAN0->FDCTRL = CAN_FDCTRL_FDRATE(0) | CAN_FDCTRL_MBDSR0(0) | CAN_FDCTRL_MBDSR1(0);

    /* Clear messages buffers */
    for(ii=0; ii<CAN_RAMn_COUNT; ++ii)
        CAN0->RAMn[ii] = 0x0;

    /* Enable CAN */
    /* Set No freeze mode request */
    /* Enable the FlexCAN module */
    CAN0->MCR &= ~( CAN_MCR_HALT_MASK | CAN_MCR_MDIS_MASK );
}

/* LEDs GPIO init */
void GPIO_Init_LED(void)
{
    /* Enable clock */
    /* PCC.LPUART2.B.CGC = 0; */ /* Clock Control */
    /* PCC.LPUART2.B.PCS = 3; */ /* Peripheral Clock Source Select - 011 - SCGFIRCLK - Fast IRC Clock(scg_firc_slow_clk), (maximum is 48MHz). */
    /* PCC.LPUART2.B.CGC = 1; */ /* Clock Control */
    (*(volatile uint32_t *) 0x40065130UL) = 0x40000000;

    PORTD->PCR[0] = PORT_PCR_MUX(1);
    PORTD->PCR[15] = PORT_PCR_MUX(1);
    PORTD->PCR[16] = PORT_PCR_MUX(1);

    PTD->PSOR |= (1 << 0) | (1 << 15) | (1 << 16);
    PTD->PDDR |= (1 << 0) | (1 << 15) | (1 << 16);
}

Std_ReturnType sys_init(void)
{
    /* workaround enable peripheral clock - write directly to PCC register instead of using register defined in .h file*/
    (*(volatile uint32*)(0x40065020))=0xC3000000;
    (*(volatile uint32*)(0x40065034))=0xC3000000;
    (*(volatile uint32*)(0x40065080))=0xC3000000;
    (*(volatile uint32*)(0x40065084))=0xC3000000;
    (*(volatile uint32*)(0x40065090))=0xC3000000;
    (*(volatile uint32*)(0x40065094))=0xC3000000;
    (*(volatile uint32*)(0x40065098))=0xC3000000;
    (*(volatile uint32*)(0x4006509C))=0xC3000000;
    (*(volatile uint32*)(0x400650AC))=0xC3000000;
    (*(volatile uint32*)(0x400650B0))=0xC3000000;
    (*(volatile uint32*)(0x400650B4))=0xC3000000;
    (*(volatile uint32*)(0x400650B8))=0xC3000000;
    (*(volatile uint32*)(0x400650C4))=0xC3000000;
    (*(volatile uint32*)(0x400650C8))=0xC3000000;
    (*(volatile uint32*)(0x400650CC))=0xC3000000;
    (*(volatile uint32*)(0x400650D8))=0xC3000000;
    (*(volatile uint32*)(0x400650DC))=0xC3000000;
    (*(volatile uint32*)(0x400650E0))=0xC3000000;
    (*(volatile uint32*)(0x400650E4))=0xC3000000;
    (*(volatile uint32*)(0x400650E8))=0xC3000000;
    (*(volatile uint32*)(0x400650EC))=0xC3000000;
    (*(volatile uint32*)(0x400650F0))=0xC3000000;
    (*(volatile uint32*)(0x400650F4))=0xC3000000;
    (*(volatile uint32*)(0x400650FC))=0xC3000000;
    (*(volatile uint32*)(0x40065100))=0xC3000000;
    (*(volatile uint32*)(0x40065114))=0xC3000000;
    (*(volatile uint32*)(0x40065120))=0xC3000000;
    (*(volatile uint32*)(0x40065124))=0xC3000000;
    (*(volatile uint32*)(0x40065128))=0xC3000000;
    (*(volatile uint32*)(0x4006512C))=0xC3000000;
    (*(volatile uint32*)(0x40065130))=0xC3000000;
    (*(volatile uint32*)(0x40065134))=0xC3000000;
    (*(volatile uint32*)(0x40065148))=0xC3000000;
    (*(volatile uint32*)(0x40065168))=0xC3000000;
    (*(volatile uint32*)(0x40065178))=0xC3000000;
    (*(volatile uint32*)(0x40065180))=0xC3000000;
    (*(volatile uint32*)(0x40065184))=0xC3000000;
    (*(volatile uint32*)(0x4006518C))=0xC3000000;
    (*(volatile uint32*)(0x40065190))=0xC3000000;
    (*(volatile uint32*)(0x40065194))=0xC3000000;

    return(E_OK);
}

/******************************************************************************
* Global functions
******************************************************************************/
/* Initialization of all peripherals */
void init_all(void)
{
    DisableIrq();

    /* Set system modules */
    sys_init();

    /* Set clock */
    clk_init();

    /* Flush and enable I cache and write buffer */
    (*(volatile uint32_t *) 0xE0082000ul) = 0x85000003ul;

    /* LEDs GPIO initialization */
    GPIO_Init_LED();

    /* SPI1 */
    GPIO_Init_LPSPI1();
    LPSPI1_init();

    /* SBC initialization via SPI */
    MC33903_Config();

#if FMSTR_USE_FLEXCAN
    /* Set TxD and RxD pins for FlexCAN usage */
    GPIO_Init_CAN();
    /* Initialize FlexCAN */
    FlexCAN_0_Init();
    /* Enable CAN0 interrupts */
    sys_enableIsrSource(81, 0xF0);
#elif FMSTR_USE_LPUART
    GPIO_Init_LPUART1();
    LPUART1_init();
    /* Enable LPUART1 interrupts */
    sys_enableIsrSource(33, 0xF0);
#endif
    EnableIrq();
}

/* This routine disables CAN module */
void DisableCAN(void)
{
    /* Disable the FlexCAN module */
    CAN0->MCR |= CAN_MCR_MDIS(1);
    /* Make sure CAN is disabled */
    while(CAN0->MCR & CAN_MCR_NOTRDY_MASK); /* Make sure CAN is disabled */
}

#if FMSTR_USE_LPUART
INTERRUPT_FUNC void LPUART1_RxTx_IRQHandler(void)
{
    /* Call interrupt routine */
    FMSTR_Isr();
}
#elif FMSTR_USE_FLEXCAN
INTERRUPT_FUNC void CAN0_ORed_Message_buffer_IRQHandler(void)
{
    /* Call interrupt routine */
    FMSTR_Isr();
}
#endif

uint16_t SPI_0_SendWord(uint16_t data)
{
    uint16_t outData;

    LPSPI1->TDR = data;

    /* Wait for the end of the transfer */
    while ((LPSPI1->SR & LPSPI_SR_RDF_MASK) == 0 );
    /* Store the second 8-bit word */
    outData = LPSPI1->RDR;

    return(outData);
}

#ifdef __cplusplus
}
#endif

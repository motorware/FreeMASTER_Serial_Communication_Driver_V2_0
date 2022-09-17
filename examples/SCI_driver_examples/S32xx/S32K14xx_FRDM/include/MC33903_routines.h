/******************************************************************************
*
*   (c) Copyright 2004-2016 NXP Semiconductors, Inc.
*   All Rights Reserved.
*
******************************************************************************/
/*!
*
*   @file    MC33903_routines.h
*
*   @brief   MC33903 System Basis Chip configuration header file
*
******************************************************************************/
#ifndef MC33903_ROUTINES_H_
#define MC33903_ROUTINES_H_

/*******************************************************************************
* Constants and macros
*******************************************************************************/
/************************* INITIAL CONFIGURATION SECTION **********************/
/* LIN1 and LIN2 configured as LIN master term, IO output drivers disabled */
#define SBC_LIN_INITVAL     SBC_LIN_TERM0_0

/* Watchdog is accessed in simple 8/16 bit SPI, window disabled */
#define SBC_WDT_INITVAL     SBC_8_16_SPI

/* VREG: 1ms reset pulse, SBC reset at 0.7Vdd, Vaux = 5V */
#define SBC_VREG_INITVAL    SBC_RST_1ms|SBC_RST_07VDD|SBC_VAUX_5V

/* MISC: No RANDOM bits for mode change, no SPI parity, 100 us for INT pulse */
#define SBC_MISC_INITVAL    0x0000

/* Watchdog default timeout */
#define SBC_WDT_TIMEOUT     SBC_WDOG_320ms

/* All interrupt sources disabled */
#define SBC_INT_INITVAL     0x00

/* Enable Vaux and 5V CAN, Vdd PNP on, enable entry to low power modes */
#define SBC_REG_INITVAL     SBC_5VCAN_0|SBC_VDD_OFF_EN /* SBC_VAUX_0|SBC_VDD_BAL_AUTO|SBC_VDD_BAL_EN (!!!) */

/* CAN transceiver enabled, fast slew rate */
#define SBC_CAN_INITV       SBC_CAN_TX_RX|SBC_CAN_SLEW_RATE_FAST

/* LIN transceivers enabled, 20 kbps */
#define SBC_LIN1_INITV      SBC_LIN_MODE_1|SBC_LIN_MODE_0|SBC_LIN_TERM_ON

/* I/O0, I/O1 in high impedance state, WAKE/INT disabled */
#define SBC_IO_INITV        0x00

/* MUX output, internal temperature sensor */
#define SBC_MUX_INITV       SBC_INT_TEMP


/***************************** DO NOT MODIFY section ***************************/
/* REGISTERS ADDRESSES */
#define SBC_MUX             (0x0000 << 9)  /* MUX register */
#define SBC_RAM_A           (0x0001 << 9)  /* 8 bit RAM register */
#define SBC_RAM_B           (0x0002 << 9)  /* 8 bit RAM register */
#define SBC_RAM_C           (0x0003 << 9)  /* 8 bit RAM register */
#define SBC_RAM_D           (0x0004 << 9)  /* 8 bit RAM register */
#define SBC_INIT_VREG       (0x0005 << 9)  /* Voltage regulator initialization */
#define SBC_INIT_WDOG       (0x0006 << 9)  /* Watchdog initialization register */
#define SBC_INIT_LIN_IO     (0x0007 << 9)  /* LIN I/O initialization register */
#define SBC_INIT_MISC       (0x0008 << 9)  /* MISC initialization register */
#define SBC_SPECIAL_MODE    (0x0009 << 9)  /* Special Mode register */
#define SBC_IMCUSTP_WDNOR   (0x000A << 9)  /* Timer: I_MCU and Watchdog period */
#define SBC_CYC_SENSE_INT   (0x000B << 9)  /* Timer: Cyclic sense and cyclic int periods */
#define SBC_WDOGSTP_FWU     (0x000C << 9)  /* Timer: Watchdog and forced wake-up period */
#define SBC_WDOG_REFRESH    (0x000D << 9)  /* Watchdog refresh register */
#define SBC_MODE_RM         (0x000E << 9)  /* Mode register */
#define SBC_REGULATOR       (0x000F << 9)  /* Voltage regulators control register */
#define SBC_CAN             (0x0010 << 9)  /* CAN interface register */
#define SBC_IO              (0x0011 << 9)  /* I/O terminal register */
#define SBC_INTERRUPT       (0x0012 << 9)  /* Interrupts register */
#define SBC_LIN1            (0x0013 << 9)  /* LIN 1 interface register */
#define SBC_LIN2            (0x0014 << 9)  /* LIN 2 interface register */


/* SELECTION BITS */
#define SBC_REGISTER        0x0000  /* Register (read) */
#define SBC_FLAG            0xC000  /* Flag (read) */
#define SBC_WR              0x4000  /* Register (write) */
#define SBC_PARITY          0x0100  /* Parity */
#define SBC_NEXT            0x0100  /* Next */
#define SBC_HL              0x0080  /* Register sub-address selection */


/* FLAG BITS */
#define SBC_INT             0x8000
#define SBC_WU              0x4000
#define SBC_RST             0x2000
#define SBC_CAN_G           0x1000
#define SBC_LIN_G           0x0800
#define SBC_IO_G            0x0400
#define SBC_SAFE_G          0x0200
#define SBC_VREG_G          0x0100
#define SBC_CAN_BUS         0x0080
#define SBC_CAN_LOC         0x0040
#define SBC_LIN1_FLAGS      0x0020
#define SBC_LIN0_FLAGS      0x0010
#define SBC_IO_FLAG1        0x0008
#define SBC_IO_FLAG0        0x0004
#define SBC_REG_FLAG1       0x0002
#define SBC_REG_FLAG0       0x0001


/* MUX REGISTER */
/* Control bits */
#define SBC_MUX2            0x0080
#define SBC_MUX1            0x0040
#define SBC_MUX0            0x0020
#define SBC_INT2K_EN        0x0010
/* MUX options */
#define SBC_MUX_DISABLE     0x0000
#define SBC_VDD_OUT         SBC_MUX0
#define SBC_INT_VREF        SBC_MUX1
#define SBC_INT_TEMP        SBC_MUX1|SBC_MUX0
#define SBC_IO_0            SBC_MUX2
#define SBC_IO_1            SBC_MUX2|SBC_MUX0
#define SBC_VSUP1           SBC_MUX2|SBC_MUX1
#define SBC_VSENSE          SBC_MUX2|SBC_MUX1|SBC_MUX0
/* Pull down options */
#define SBC_INT2K_ENABLE    SBC_INT2K_EN
#define SBC_INT2K_DISABLE   0x0000


/* VOLTAGE REGULATOR INITIALIZATION REGISTER */
/* Control bits */
#define SBC_VDD_LOW_RST1    0x0040
#define SBC_VDD_LOW_RST0    0x0020
#define SBC_VDD_LOW_RST_D1  0x0010
#define SBC_VDD_LOW_RST_D0  0x0008
#define SBC_AUX5            0x0004
/* Reset and interrupt conditions */
#define SBC_RST_09VDD       0x0000
#define SBC_INT_RST         SBC_VDD_LOW_RST0
#define SBC_RST_07VDD       SBC_VDD_LOW_RST1
#define SBC_SBC_RESET       SBC_VDD_LOW_RST1|SBC_VDD_LOW_RST0
/* Reset duration after Vdd recovery or threshold cross */
#define SBC_RST_1ms         0x0000
#define SBC_RST_5ms         SBC_VDD_LOW_RST_D0
#define SBC_RST_10ms        SBC_VDD_LOW_RST_D1
#define SBC_RST_20ms        SBC_VDD_LOW_RST_D1|SBC_VDD_LOW_RST_D0
/* Vaux  output voltage operation */
#define SBC_VAUX_3V         0x0000
#define SBC_VAUX_5V         SBC_AUX5


/* WATCHDOG INITIALIZATION REGISTER */
/* Control bits */
#define SBC_WD2INT          0x0080
#define SBC_MCU_OC          0x0040
#define SBC_OC_TIM          0x0020
#define SBC_WD_SAFE         0x0010
#define SBC_WD_SPI_1        0x0008
#define SBC_WD_SPI_0        0x0004
#define SBC_WD_NOR_WDW      0x0002
/* Watchdog refresh options in normal mode */
#define SBC_8_16_SPI        0x0000
#define SBC_ENH_SPI1        SBC_WD_SPI_0
#define SBC_ENH_SPI2        SBC_WD_SPI_1
#define SBC_ENH_SPI4        SBC_WD_SPI_1|SBC_WD_SPI_0

/* LIN INITIALIZATION REGISTER */
/* Control bits */
#define SBC_IO1_OFF         0x0080
#define SBC_LIN_TERM1_1     0x0040
#define SBC_LIN_TERM1_0     0x0020
#define SBC_LIN_TERM0_1     0x0010
#define SBC_LIN_TERM0_0     0x0008
#define SBC_IO1_OUT_EN      0x0004
#define SBC_IO0_OUT_EN      0x0002
#define SBC_CYC_IO0_INV     0x0001

/* MISC INITIALIZATION REGISTER */
/* Control bits */
#define SBC_CHNG_MODE_RDM   0x0080
#define SBC_SPI_PARITY      0x0040
#define SBC_INT_PULSE_LO    0x0020
#define SBC_INT_WIDTH       0x0010
#define SBC_INT_FLASH50     0x0008
#define SBC_SAFE_RES_2      0x0004
#define SBC_SAFE_RES_1      0x0002
#define SBC_SAFE_RES_0      0x0001

/* SPECIAL MODE REGISTER */
/* Control bits */
#define SBC_SEL_MODE_1      0x0080
#define SBC_SEL_MODE_0      0x0040
#define SBC_RANDOM_MASK     0x003F
/* Change mode selection */
#define SBC_GOTO_RESET      0x0000
#define SBC_GOTO_INIT       SBC_SEL_MODE_0
#define SBC_GOTO_FLASH      SBC_SEL_MODE_1
#define SBC_NO_CHANGE       SBC_SEL_MODE_0|SBC_SEL_MODE_0

/* TIMER: I_MCU OVERCURRENT TIME AND WATCHDOG PERIOD IN NORMAL MODE */
/* Control fields */
#define SBC_IMCU_STP_TIM    0x0080
#define SBC_IMCU_STP_PRESC0 0x0000
#define SBC_IMCU_STP_PRESC1 0x0020
#define SBC_IMCU_STP_PRESC2 0x0040
#define SBC_IMCU_STP_PRESC3 0x0060
#define SBC_WD_NOR_TIM0     0x0000
#define SBC_WD_NOR_TIM1     0x0008
#define SBC_WD_NOR_TIM2     0x0010
#define SBC_WD_NOR_TIM3     0x0018
#define SBC_WD_NOR_PRESC0   0x0000
#define SBC_WD_NOR_PRESC1   0x0001
#define SBC_WD_NOR_PRESC2   0x0002
#define SBC_WD_NOR_PRESC3   0x0003
#define SBC_WD_NOR_PRESC4   0x0004
#define SBC_WD_NOR_PRESC5   0x0005
#define SBC_WD_NOR_PRESC6   0x0006
#define SBC_WD_NOR_PRESC7   0x0007
/* Overcurrent times options */
#define SBC_OVCURR_3ms      SBC_IMCU_STP_PRESC0
#define SBC_OVCURR_4ms      SBC_IMCU_STP_TIM|SBC_IMCU_STP_PRESC0
#define SBC_OVCURR_6ms      SBC_IMCU_STP_PRESC1
#define SBC_OVCURR_8ms      SBC_IMCU_STP_TIM|SBC_IMCU_STP_PRESC1
#define SBC_OVCURR_12ms     SBC_IMCU_STP_PRESC2
#define SBC_OVCURR_16ms     SBC_IMCU_STP_TIM|SBC_IMCU_STP_PRESC2
#define SBC_OVCURR_24ms     SBC_IMCU_STP_PRESC3
#define SBC_OVCURR_32ms     SBC_IMCU_STP_TIM|SBC_IMCU_STP_PRESC3
/* Watchdog period in normal mode options */
#define SBC_WDOG_2_5ms      SBC_WD_NOR_TIM0|SBC_WD_NOR_PRESC0
#define SBC_WDOG_3ms        SBC_WD_NOR_TIM1|SBC_WD_NOR_PRESC0
#define SBC_WDOG_3_5ms      SBC_WD_NOR_TIM2|SBC_WD_NOR_PRESC0
#define SBC_WDOG_4ms        SBC_WD_NOR_TIM3|SBC_WD_NOR_PRESC0
#define SBC_WDOG_5ms        SBC_WD_NOR_TIM0|SBC_WD_NOR_PRESC1
#define SBC_WDOG_6ms        SBC_WD_NOR_TIM1|SBC_WD_NOR_PRESC1
#define SBC_WDOG_7ms        SBC_WD_NOR_TIM2|SBC_WD_NOR_PRESC1
#define SBC_WDOG_8ms        SBC_WD_NOR_TIM3|SBC_WD_NOR_PRESC1
#define SBC_WDOG_10ms       SBC_WD_NOR_TIM0|SBC_WD_NOR_PRESC2
#define SBC_WDOG_12ms       SBC_WD_NOR_TIM1|SBC_WD_NOR_PRESC2
#define SBC_WDOG_14ms       SBC_WD_NOR_TIM2|SBC_WD_NOR_PRESC2
#define SBC_WDOG_16ms       SBC_WD_NOR_TIM3|SBC_WD_NOR_PRESC2
#define SBC_WDOG_20ms       SBC_WD_NOR_TIM0|SBC_WD_NOR_PRESC3
#define SBC_WDOG_24ms       SBC_WD_NOR_TIM1|SBC_WD_NOR_PRESC3
#define SBC_WDOG_28ms       SBC_WD_NOR_TIM2|SBC_WD_NOR_PRESC3
#define SBC_WDOG_32ms       SBC_WD_NOR_TIM3|SBC_WD_NOR_PRESC3
#define SBC_WDOG_40ms       SBC_WD_NOR_TIM0|SBC_WD_NOR_PRESC4
#define SBC_WDOG_48s        SBC_WD_NOR_TIM1|SBC_WD_NOR_PRESC4
#define SBC_WDOG_56ms       SBC_WD_NOR_TIM2|SBC_WD_NOR_PRESC4
#define SBC_WDOG_64ms       SBC_WD_NOR_TIM3|SBC_WD_NOR_PRESC4
#define SBC_WDOG_80ms       SBC_WD_NOR_TIM0|SBC_WD_NOR_PRESC5
#define SBC_WDOG_96ms       SBC_WD_NOR_TIM1|SBC_WD_NOR_PRESC5
#define SBC_WDOG_112ms      SBC_WD_NOR_TIM2|SBC_WD_NOR_PRESC5
#define SBC_WDOG_128ms      SBC_WD_NOR_TIM3|SBC_WD_NOR_PRESC5
#define SBC_WDOG_160ms      SBC_WD_NOR_TIM0|SBC_WD_NOR_PRESC6
#define SBC_WDOG_192ms      SBC_WD_NOR_TIM1|SBC_WD_NOR_PRESC6
#define SBC_WDOG_224ms      SBC_WD_NOR_TIM2|SBC_WD_NOR_PRESC6
#define SBC_WDOG_256ms      SBC_WD_NOR_TIM3|SBC_WD_NOR_PRESC6
#define SBC_WDOG_320ms      SBC_WD_NOR_TIM0|SBC_WD_NOR_PRESC7
#define SBC_WDOG_384ms      SBC_WD_NOR_TIM1|SBC_WD_NOR_PRESC7
#define SBC_WDOG_448ms      SBC_WD_NOR_TIM2|SBC_WD_NOR_PRESC7
#define SBC_WDOG_512ms      SBC_WD_NOR_TIM3|SBC_WD_NOR_PRESC7

/* TIMER: CYCLIC SENSE PERIOD AND CYCLIC INTERRUPT PERIODS (LP MODE) */
/* Control bits */
#define SBC_CYC_SENSE_TIM   0x0080
#define SBC_CYC_SENSE_PRE2  0x0040
#define SBC_CYC_SENSE_PRE1  0x0020
#define SBC_CYC_SENSE_PRE0  0x0010
#define SBC_CYC_INT_TIM     0x0008
#define SBC_CYC_INT_PRE2    0x0004
#define SBC_CYC_INT_PRE1    0x0002
#define SBC_CYC_INT_PRE0    0x0001

/* TIMER: WATCHDOG IN LP VDD ON MODE AND FORCED WAKE-UP PERIOD IN LP MODE */
/* Control bits */
#define SBC_WDOG_STP_TIM    0x0080
#define SBC_WDOG_STP_PRE2   0x0040
#define SBC_WDOG_STP_PRE1   0x0020
#define SBC_WDOG_STP_PRE0   0x0010
#define SBC_FWU_TIM         0x0008
#define SBC_FWU_PRE2        0x0004
#define SBC_FWU_PRE1        0x0002
#define SBC_FWU_PRE0        0x0001

/* MODE REGISTER */
/* Control bits */
#define SBC_MODE_4          0x0080
#define SBC_MODE_3          0x0040
#define SBC_MODE_2          0x0020
#define SBC_MODE_1          0x0010
#define SBC_MODE_0          0x0008
/* Sleep mode options */
#define SBC_SLEEP           SBC_MODE_3|SBC_MODE_2
#define SBC_SLEEP_CYCSEN    SBC_MODE_3|SBC_MODE_2|SBC_MODE_0
#define SBC_SLEEP_FWU       SBC_MODE_3|SBC_MODE_2|SBC_MODE_1
#define SBC_SLEEP_CYC_FWU   SBC_MODE_3|SBC_MODE_2|SBC_MODE_1|SBC_MODE_0
/* Stop mode options */
#define SBC_STOP            SBC_MODE_4
#define SBC_STOP_FWU        SBC_MODE_3
#define SBC_STOP_CYCSEN     SBC_MODE_2
#define SBC_STOP_CYCINT     SBC_MODE_1
#define SBC_STOP_WDEN       SBC_MODE_0

/* VOLTAGE REGULATORS CONTROL REGISTER */
/* Control bits */
#define SBC_VAUX_1          0x0080
#define SBC_VAUX_0          0x0040
#define SBC_5VCAN_1         0x0010
#define SBC_5VCAN_0         0x0008
#define SBC_VDD_BAL_EN      0x0004
#define SBC_VDD_BAL_AUTO    0x0002
#define SBC_VDD_OFF_EN      0x0001

/* CAN INTERFACE REGISTER */
/* Control bits */
#define SBC_CAN_MODE_1      0x0080
#define SBC_CAN_MODE_0      0x0040
#define SBC_CAN_SLEWRATE_1  0x0020
#define SBC_CAN_SLEWRATE_0  0x0010
#define SBC_CAN_WAKE_PULSE  0x0008
#define SBC_CAN_INT_MODE    0x0001
/* CAN transceiver modes */
#define SBC_CAN_NO_WU_INT           0x0000
#define SBC_CAN_RX_ONLY             SBC_CAN_MODE_0
#define SBC_CAN_WKUP_INT            SBC_CAN_MODE_1
#define SBC_CAN_TX_RX               SBC_CAN_MODE_1|SBC_CAN_MODE_0
/* CAN transceiver slew rates */
#define SBC_CAN_SLEW_RATE_FAST      0x0000
#define SBC_CAN_SLEW_RATE_MEDIUM    SBC_CAN_SLEWRATE_0
#define SBC_CAN_SLEW_RATE_SLOW      SBC_CAN_SLEWRATE_1
/* CAN bus failure flags */
#define SBC_CAN_UF          0x0080
#define SBC_CAN_F           0x0040
#define SBC_CANL_VSUP       0x0020
#define SBC_CANL_VDD        0x0010
#define SBC_CANL_GND        0x0008
#define SBC_CANH_VSUP       0x0004
#define SBC_CANH_VDD        0x0002
#define SBC_CANH_GND        0x0001

/* I/O REGISTER */
/* Control bits */
#define SBC_IO3_1           0x0080
#define SBC_IO3_0           0x0040
#define SBC_IO2_1           0x0020
#define SBC_IO2_0           0x0010
#define SBC_IO1_1           0x0008
#define SBC_IO1_0           0x0004
#define SBC_IO0_1           0x0002
#define SBC_IO0_0           0x0001

/* INTERRUPTS REGISTER */
/* Control bits */
#define SBC_CAN_FAIL_INT    0x0080
#define SBC_MCU_REQ_INT     0x0040
#define SBC_LIN1_FAIL_INT   0x0020
#define SBC_LIN2_FAIL_INT   0x0010
#define SBC_IOX_INT         0x0008
#define SBC_SPI_F_INT       0x0002
#define SBC_VMON_F_INT      0x0001

/* LIN 1/2 REGISTERS */
#define SBC_LIN_MODE_1      0x0080
#define SBC_LIN_MODE_0      0x0040
#define SBC_LIN_SLEWRATE_1  0x0020
#define SBC_LIN_SLEWRATE_0  0x0010
#define SBC_LIN_TERM_ON     0x0004
/* LIN transceiver modes */
#define SBC_LIN_NO_WU_INT           0x0000
#define SBC_LIN_SLPWU_NORINT        SBC_LIN_MODE_1
#define SBC_LIN_TX_RX               SBC_LIN_MODE_1|SBC_LIN_MODE_0
/* LIN transceiver slew rates */
#define SBC_LIN_SLEW_RATE_20KBPS    0x0000
#define SBC_LIN_SLEW_RATE_10KBPS    SBC_LIN_SLEWRATE_0
#define SBC_LIN_SLEW_RATE_FAST      SBC_LIN_SLEWRATE_1

/*******************************************************************************
* Global function prototypes
*******************************************************************************/
void MC33903_Write (uint16_t u16SBC_Address, uint8_t u8SBC_Data);
uint16_t MC33903_Read (uint16_t u16SBC_Address, uint8_t u8SBC_Data);
void MC33903_Config(void);
void MC33903_ClearWDT(void);
void MC33903_SetWDTperiod(uint8_t u8WDT_Period);
void MC33903_CAN_Config(uint8_t u8CANMode);
void MC33903_SetCyclicSense(uint8_t u8CycSens_Period);
void MC33903_StopMode (uint8_t u8StopMode);
void MC33903_SleepMode (uint8_t u8SleepMode);

#endif /* MC33903_ROUTINES_H_ */

/******************************************************************************
*
*   (c) Copyright 2004-2016 NXP Semiconductors, Inc.
*   All Rights Reserved.
*
******************************************************************************/
/*!
*
*   @file    MC33903_routines.c
*
*   @brief   MC33903 System Basis Chip configuration function source file with
*            routines for SBC setup and diagnostics.
*
******************************************************************************/

#include "S32K144.h"
#include "compiler.h"
#include "MC33903_routines.h"
#include "periphinit.h"

/******************************************************************************
* Global functions
******************************************************************************/
/******************************************************************************
*
* Function: void MC33903_Write(uint16_t u16SBC_Address, uint8_t u8SBC_Data)
*
* Description:  Writes 8-bit value into SBC register via SPI0.
*
* Param[in]:    u16SBC_Address      SBC register address shifted left by 8 bits
*               u8SBC_Data          8-bit register value
*
* Notes:        SPI_0_Init (spi.c) function must be already called prior to this
*               function call.
*
******************************************************************************/
void MC33903_Write(uint16_t u16SBC_Address, uint8_t u8SBC_Data)
{
    uint16_t u16SBC_Command;    /* Data word to be sent to the SBC */

    u16SBC_Command = (u16SBC_Address | SBC_WR | u8SBC_Data);

    (void)SPI_0_SendWord(u16SBC_Command);  /* Send data to SBC */
}

/******************************************************************************
*
* Function: uint16_t MC33903_Read(uint16_t u16SBC_Address, uint8_t u8SBC_Data)
*
* Description:  Reads 8-bit value from SBC register via SPI0.
*
* Param[in]:    u16SBC_Address      SBC register address shifted left by 8 bits
*               u8SBC_Data          8-bit register sub-address
*
* Return:       uint16_t            Register value
*
* Notes:        SPI_0_Init (spi.c) function must be already called prior to this
*               function call.
*
******************************************************************************/
uint16_t MC33903_Read(uint16_t u16SBC_Address, uint8_t u8SBC_Data)
{
    uint16_t u16SBC_Command;    /* Data word to be sent to the SBC */
    uint16_t u16RxData;         /* Variable to store received word */

    u16SBC_Command = (u16SBC_Address | u8SBC_Data);

    u16RxData = SPI_0_SendWord(u16SBC_Command);

    return(u16RxData);
}

/******************************************************************************
*
* Function: void MC33903_Config(void)
*
* Description:  Performs initial SBC configuration.
*
* Notes:        SPI_0_Init (spi.c) function must be already called prior to this
*               function call.
*
******************************************************************************/
void MC33903_Config(void)
{
    /* Read 16 bit flags */
    MC33903_Read(SBC_REGISTER|SBC_WR|SBC_REGULATOR|SBC_NEXT, 0x00);

    /* Clear flags if needed */
    /* Clear VREG flags */
    MC33903_Read(SBC_FLAG|SBC_REGULATOR|SBC_NEXT, SBC_HL);
    MC33903_Write(SBC_FLAG|SBC_REGULATOR|SBC_NEXT, 0x00);

    /* Clear SAFE flag */
    MC33903_Write(SBC_FLAG|SBC_MODE_RM|SBC_NEXT, SBC_HL);

    /* Clear IO flags */
    MC33903_Write(SBC_FLAG|SBC_IO|SBC_NEXT, 0x00);

    /* Clear LIN flags */
    MC33903_Write(SBC_FLAG|SBC_LIN1|SBC_NEXT, 0x00);

    /* Clear CAN flags */
    MC33903_Write(SBC_FLAG|SBC_CAN|SBC_NEXT, 0x00);

    /* LIN1 and LIN2 */
    MC33903_Write(SBC_REGISTER|SBC_INIT_LIN_IO, SBC_LIN_INITVAL);

    /* Watchdog settings */
    MC33903_Write(SBC_REGISTER|SBC_INIT_WDOG, SBC_WDT_INITVAL);

    /* VREG */
    MC33903_Write(SBC_REGISTER|SBC_INIT_VREG, SBC_VREG_INITVAL);

    /* MISC */
    MC33903_Write(SBC_REGISTER|SBC_INIT_MISC, SBC_MISC_INITVAL);

    /* Wait at least 50 microseconds before writing to timers registers */
    delay_us(50);

    /* Set watchdog default period */
    MC33903_SetWDTperiod(SBC_WDT_TIMEOUT);

    MC33903_ClearWDT();  /* Transition to normal mode */

    /* Resources initial configuration */
    /* Interrupt sources */
    MC33903_Write(SBC_REGISTER|SBC_INTERRUPT, SBC_INT_INITVAL);

    /* Regulator */
    MC33903_Write(SBC_REGISTER|SBC_REGULATOR, SBC_REG_INITVAL);

    /* CAN transceiver */
    MC33903_CAN_Config(SBC_CAN_INITV);

    /* LIN transceivers */
    MC33903_Write(SBC_REGISTER|SBC_LIN1,SBC_LIN1_INITV);

    /* I/O configuration */
    MC33903_Write(SBC_REGISTER|SBC_IO,SBC_IO_INITV);

    /* MUX output */
    MC33903_Write(SBC_REGISTER|SBC_MUX, SBC_MUX_INITV);

    /* Read MODE flag register to clear SAFE flag */
    MC33903_Write(SBC_FLAG|SBC_MODE_RM|SBC_NEXT, 0x80);
}

/******************************************************************************
*
* Function: void MC33903_ClearWDT(void)
*
* Description:  Resets SBC watchdog.
*
* Notes:        SPI_0_Init (spi.c) function must be already called prior to this
*               function call.
*
******************************************************************************/
void MC33903_ClearWDT(void)
{
    /* Read MODE flag register to clear SAFE flag */
    MC33903_Write(SBC_FLAG|SBC_MODE_RM|SBC_NEXT, 0x80);

    /* Clear watchdog */
    MC33903_Write(SBC_REGISTER|SBC_WDOG_REFRESH, 0x00);
}

/******************************************************************************
*
* Function: void MC33903_SetWDTperiod(uint8_t u8WDT_Period)
*
* Description:  Sets SBC watchdog period.
*
* Param[in]:    u8WDT_Period        Watchdog period (see SBC_WDT_TIMEOUT macro
*                                   in the MC33903_routines.h initial
*                                   configurating section)
*
* Notes:        SPI_0_Init (spi.c) function must be already called prior to this
*               function call.
*
******************************************************************************/
void MC33903_SetWDTperiod(uint8_t u8WDT_Period)
{
    MC33903_Write(SBC_REGISTER|SBC_IMCUSTP_WDNOR, u8WDT_Period);
}

/******************************************************************************
*
* Function: void MC33903_CAN_Config(uint8_t u8CANMode)
*
* Description:  Performs SBC CAN transceiver configuration.
*
* Param[in]:    u8CANMode           SBC CAN configuration (see SBC_CAN_INITV
*                                   macro in the MC33903_routines.h initial
*                                   configuration section)
*
* Notes:        SPI_0_Init (spi.c) function must be already called prior to this
*               function call.
*
******************************************************************************/
void MC33903_CAN_Config(uint8_t u8CANMode)
{
    /* CAN configuration */
    MC33903_Write(SBC_REGISTER|SBC_CAN, u8CANMode);
}

/******************************************************************************
*
* Function: void MC33903_SetCyclicSense(uint8_t u8CycSens_Period)
*
* Description:  Configures SBC cyclic sense and cyclic sense interrupt period.
*
* Param[in]:    u8CycSens_Period    SBC cyclic sense and cyclic interrupt
*                                   settings (see MC33903_routines.h for
*                                   predefined macros)
*
* Notes:        SPI_0_Init (spi.c) function must be already called prior to this
*               function call.
*
******************************************************************************/
void MC33903_SetCyclicSense(uint8_t u8CycSens_Period)
{
    /* Update timer register */
    MC33903_Write(SBC_REGISTER|SBC_CYC_SENSE_INT,u8CycSens_Period);
}

/******************************************************************************
*
* Function: void MC33903_StopMode(uint8_t u8StopMode)
*
* Description:  Sets the SBC Stop mode.
*
* Param[in]:    u8StopMode          SBC Stop mode settings (see
*                                   MC33903_routines.h for predefined macros)
*
* Notes:        SPI_0_Init (spi.c) function must be already called prior to this
*               function call.
*
******************************************************************************/
void MC33903_StopMode(uint8_t u8StopMode)
{
    /* Send Stop mode command */
    MC33903_Write(SBC_REGISTER|SBC_MODE_RM, SBC_MODE_4|u8StopMode);
}

/******************************************************************************
*
* Function: uint16_t MC33903_Read(uint16_t u16SBC_Address, uint8_t u8SBC_Data)
*
* Description:  Sets the SBC Sleep mode.
*
* Param[in]:    u8SleepMode         SBC Sleep mode settings (see
*                                   MC33903_routines.h for predefined macros)
*
* Notes:        SPI_0_Init (spi.c) function must be already called prior to this
*               function call.
*
******************************************************************************/
void MC33903_SleepMode(uint8_t u8SleepMode)
{
    /* Send Sleep mode command */
    MC33903_Write(SBC_REGISTER|SBC_MODE_RM, u8SleepMode);
}

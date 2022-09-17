/******************************************************************************
*
*   (c) Copyright 2004-2016 NXP Semiconductors, Inc.
*   All Rights Reserved.
*
******************************************************************************/
/*!
*
*   @file    main.c
*
*   @brief   Advanced sample application demonstrating the functionality of 
*            FreeMASTER Serial Communication Driver.
*
******************************************************************************/

#include "derivative.h" /* Include peripheral declarations KEA128 */
#include "freemaster.h"
#include "freemaster_example.h"
#include "periphinit.h"

int main(void)
{
    /* Initialization of all peripherals */
    init_all();

    /* Initialize FreeMASTER driver */
    FMSTR_Example_Init();

    while(1)
    {
        /* Task of the example application */
        FMSTR_Example_Poll();
    }
    return(0);
}

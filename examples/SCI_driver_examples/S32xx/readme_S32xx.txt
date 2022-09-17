FreeMASTER Serial Communication Driver examples for ARM Cortex S32xx family.
================================================================================

This folders contains example and test applications for S32xx family port of  
the FreeMASTER communication driver. Please see the User Manual for more 
information about the driver configuration and usage.

================================================================================
S32Kxx FreeMASTER SCI Driver example:
  - Location:        <install_path>/examples/SCI_driver_examples/S32xx/S32K14xx_FRDM
  - Used Hardware:   FRDM-PK144 NXP Freedom Development Platform for S32K 32-bit
                     Automotive General Purpose Microcontroller (part number FRDMPK144Q100).
  - IDE Environment: S32 Design Studio for ARM (the application was created
                     using built-in Design Studio project creation wizard).
  - Communication:   SCI (115200Bd used in example application) - port J7 (through OpenSDA) on FRDMPK144Q100
                     FlexCAN (500kbit/s used in example application) - port J13 on FRDMPK144Q100
                     BDM and PacketDriven BDM - port J7 (through OpenSDA) on FRDMPK144Q100
--------------------------------------------------------------------------------
Copyright 2004-2016, NXP Semiconductors, Inc.
ALL RIGHTS RESERVED, www.nxp.com
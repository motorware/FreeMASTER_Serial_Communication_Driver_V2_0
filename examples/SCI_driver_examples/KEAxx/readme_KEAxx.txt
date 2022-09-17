FreeMASTER Serial Communication Driver examples for ARM Cortex KEAxx family.
================================================================================

This folders contains example and test applications for KEAxx family port of  
the FreeMASTER communication driver. Please see the User Manual for more 
information about the driver configuration and usage.

================================================================================
KEAxx FreeMASTER SCI Driver example:
  - Location:        <install_path>/examples/SCI_driver_examples/KEAxx/KEAZ128_FRDM
  - Used Hardware:   FRDM-KEAZ128 NXP Freedom Development Platform for Ultra 
                     Reliable Kinetis EA Series MCUs (part number FRDM-KEAZ128Q80).
  - IDE Environment: S32 Design Studio for ARM (the application was created
                     using built-in Design Studio project creation wizard).
  - Communication:   SCI (115200Bd used in example application) - port J7 (through OpenSDA) on FRDM-KEAZ128Q80
                     FlexCAN (500kbit/s used in example application) - port J13 on FRDM-KEAZ128Q80
                     BDM and PacketDriven BDM - port J7 (through OpenSDA) on FRDM-KEAZ128Q80
--------------------------------------------------------------------------------
Copyright 2004-2016, NXP Semiconductors, Inc.
ALL RIGHTS RESERVED, www.nxp.com
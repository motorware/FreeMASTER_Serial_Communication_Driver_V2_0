Note to FreeMASTER-over-USB functionality:
==========================================

This USB folder is included for backward compatibility with the Freescale Medical 
USB Stack only. This stack has been superseded by the new USB stack which is part
of Kinetis SDK. Refer to the www.nxp.com/ksdk for downloads and more 
information about this software product.

For new projects, use the FreeMASTER with the Kinetis SDK USB stack only. Refer
to demo application in the /demos/freemaster_demo folder in the KSDK installation.

When using the old USB stack from this folder, set the FMSTR_USB_LEGACY_STACK option
to 1 along with the FMSTR_USE_USB_CDC in the freemaster_cfg.h.

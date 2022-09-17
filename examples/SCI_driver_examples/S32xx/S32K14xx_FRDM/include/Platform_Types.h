/**
*   @file           Platform_Types.h
*   @implements     Platform_Types.h_Artifact
*   @version M4_SRC_SW_VERSION_MAJOR.M4_SRC_SW_VERSION_MINOR.1.0
*
*   @brief   AUTOSAR M4_SRC_MODULE_NAME - Platform dependend data type definitions.
*   @details AUTOSAR platform types header file. It contains all 
*            platform dependent types and symbols. Those types must be abstracted in order to 
*            become platform and compiler independent.
*
*   @addtogroup BASE_COMPONENT
*   @{
*/
/*==================================================================================================
*   Project              : M4_SRC_PROJECT_NAME
*   Platform             : M4_SRC_MCU_FAMILY
*   Peripheral           : M4_SRC_USED_PERIPHERAL
*   Dependencies         : M4_SRC_AR_MODULE_DEPENDENCY
*
*   Autosar Version      : M4_SRC_AR_SPEC_VERSION_MAJOR.M4_SRC_AR_SPEC_VERSION_MINOR.M4_SRC_AR_SPEC_VERSION_PATCH
*   Autosar Revision     : M4_SRC_AR_RELEASE_REVISION
*   Autosar Conf.Variant :
*   SW Version           : M4_SRC_SW_VERSION_MAJOR.M4_SRC_SW_VERSION_MINOR.M4_SRC_SW_VERSION_PATCH
*   Build Version        : M4_SRC_BUILD_ID
*
*   (c) Copyright M4_SRC_YEAR_ID M4_SRC_COPYRIGHTED_TO
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
ifdef(`M4_SRC_KEEP_REVISION_HISTORY', `dnl - DO NOT modify this M4 line!
Revision History:
                             Modification     Tracking
Author (core ID)              Date D/M/Y       Number     Description of Changes
---------------------------   ----------    ------------  ------------------------------------------
Marius Rotaru (rtrm001)       12/05/2011    ENGR00142144  File creation according to ASR4.0.2 specs
---------------------------   ----------    ------------  ------------------------------------------
Victor Burlacu-Zane           18/08/2011    ENGR00155002  Updated for Leopard 0.8.1
---------------------------   ----------    ------------  ------------------------------------------
Victor Burlacu-Zane           02/03/2012    ENGR00175905  Updated Misra comments
---------------------------   ----------    ------------  ------------------------------------------
Marius Rotaru (rtrm001)       25/07/2012    ENGR00218370  Re-sync from ASR4.0 legacy vob
---------------------------   ----------    ------------  ------------------------------------------
Alexandra Amarandei (b14660)  27/06/2013    ENGR00265778  Update misra for latest PClint
---------------------------   ----------    ------------  ------------------------------------------
Alexandra Amarandei (b14660)  12/09/2013    ENGR00277604  Updates for Faraday platform
---------------------------   ----------    ------------  ------------------------------------------
Alexandra Amarandei (b14660)  27/03/2014    ENGR00297594  Add design entities
---------------------------   ----------    ------------  ------------------------------------------
Marius Rotaru      (rtrm001)  12/12/2014    ENGR00341254  Added support for AARCH64
---------------------------   ----------    ------------  ------------------------------------------
',)dnl - DO NOT modify this M4 line!
==================================================================================================*/

/**   
* @note         It is not allowed to add any extension to this file. Any extension invalidates the 
*               AUTOSAR conformity
*/

#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Platform_Types_h_REF_1
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely on the
* significance of more than 31 characters. The used compilers use more than 31 chars for identifiers
*/

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/**
* @brief          8bit Type Processor
* @implements     CPU_TYPE_enumeration
*/
#define CPU_TYPE_8 8

/**
* @brief          16bit Type Processor
* @implements     CPU_TYPE_enumeration
*/
#define CPU_TYPE_16 16

/**
* @brief          32bit Type Processor
* @implements     CPU_TYPE_enumeration
*/
#define CPU_TYPE_32 32

/**
* @brief          64bit Type Processor
* @implements     CPU_TYPE_enumeration
*/
#define CPU_TYPE_64 64

/**
* @brief          MSB First Processor
* @implements     CPU_BIT_ORDER_enumeration
*/
#define MSB_FIRST 0

/**
* @brief          LSB First Processor
* @implements     CPU_BIT_ORDER_enumeration
*/
#define LSB_FIRST 1

/**
* @brief          HIGH_BYTE_FIRST Processor
* @implements     CPU_BYTE_ORDER_enumeration
*/
#define HIGH_BYTE_FIRST 0

/** 
* @brief          LOW_BYTE_FIRST Processor
* @implements     CPU_BYTE_ORDER_enumeration
*/
#define LOW_BYTE_FIRST 1

/** 
* @brief          Processor type
* @implements     CPU_TYPE_enumeration
*/
#define CPU_TYPE CPU_TYPE_32

/** 
* @brief          Bit order on register level.
* @implements     CPU_BIT_ORDER_enumeration
*/
#define CPU_BIT_ORDER (MSB_FIRST)

/** 
* @brief The byte order on memory level shall be indicated in the platform types header file using 
*        the symbol CPU_BYTE_ORDER.
* @implements     CPU_BYTE_ORDER_enumeration
*/
#define CPU_BYTE_ORDER LOW_BYTE_FIRST

#ifndef TRUE
    /** 
    * @brief Boolean true value
    * @implements TRUE_FALSE_enumeration
    */
    #define TRUE 1
#endif
#ifndef FALSE
    /** 
    * @brief Boolean false value
    * @implements TRUE_FALSE_enumeration
    */
    #define FALSE 0
#endif

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/** 
* @brief The standard AUTOSAR type boolean shall be implemented on basis of an eight bits long 
*        unsigned integer.
* @implements boolean_type
*/
typedef unsigned char boolean;


/** 
* @brief Unsigned 8 bit integer with range of 0 ..+255 (0x00..0xFF) - 
*        8 bit
* @implements uint8_type
*/
typedef unsigned char uint8;

/** 
* @brief Unsigned 16 bit integer with range of 0 ..+65535 (0x0000..0xFFFF) - 
*        16 bit
* @implements uint16_type
*/
typedef unsigned short uint16;

/** 
* @brief Unsigned 32 bit integer with range of 0 ..+4294967295 (0x00000000..0xFFFFFFFF) - 
*        32 bit
* @implements uint32_type
*/
typedef unsigned long uint32;

/** 
* @brief Signed 8 bit integer with range of -128 ..+127 (0x80..0x7F) - 
*        7 bit + 1 sign bit 
* @implements sint8_type
*/
typedef signed char sint8;

/** 
* @brief Signed 16 bit integer with range of -32768 ..+32767 (0x8000..0x7FFF) - 
*        15 bit + 1 sign bit 
* @implements sint16_type
*/
typedef signed short sint16;

/** 
* @brief Signed 32 bit integer with range of -2147483648.. +2147483647 (0x80000000..0x7FFFFFFF) - 
*        31 bit + 1 sign bit 
* @implements sint32_type
*/
typedef signed long sint32;

/** 
* @brief Unsigned integer at least 8 bit long. Range of at least 0 ..+255 (0x00..0xFF) - 
*        8 bit
* @implements uint8_least_type
*/
typedef unsigned long uint8_least;

/** 
* @brief  Unsigned integer at least 16 bit long. Range of at least 0 ..+65535 (0x0000..0xFFFF) - 
*         16 bit
* @implements uint16_least_type
*/
typedef unsigned long uint16_least;

/** 
* @brief Unsigned integer at least 32 bit long. Range of at least 0 ..+4294967295 
*       (0x00000000..0xFFFFFFFF) - 32 bit
* @implements uint32_least_type
*/
typedef unsigned long uint32_least;

/** 
* @brief Signed integer at least 8 bit long. Range - at least -128 ..+127. 
*        At least 7 bit + 1 bit sign
* @implements sint8_least_type
*/
typedef signed long sint8_least;

/** 
* @brief Signed integer at least 16 bit long. Range - at least -32768 ..+32767. 
*        At least 15 bit + 1 bit sign
* @implements sint16_least_type
*/
typedef signed long sint16_least;

/** 
* @brief Signed integer at least 32 bit long. Range - at least -2147483648.. +2147483647. 
*       At least 31 bit + 1 bit sign
* @implements sint32_least_type
*/
typedef signed long sint32_least;

/** 
* @brief 32bit long floating point data type
* @implements float32_type
*/
typedef float float32;

/** 
* @brief 64bit long floating point data type
* @implements float64_type
*/
typedef double float64;

/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif


#endif /* #ifndef PLATFORM_TYPES_H */

/** @} */

/**
*   @file    Std_Types.h
*   @implements     Std_Types.h_Artifact
*   @version M4_SRC_SW_VERSION_MAJOR.M4_SRC_SW_VERSION_MINOR.1.0
*
*   @brief   AUTOSAR M4_SRC_MODULE_NAME - Standard types definition.
*   @details AUTOSAR standard types header file. It contains all types that are used across several
*                modules of the basic software and that are platform and compiler independent
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
Marius Rotaru (rtrm001)       02/08/2011    ENGR00154309  Removed AutoSAR inter-module version check
---------------------------   ----------    ------------  ------------------------------------------
Victor Burlacu-Zane           01/03/2012    ENGR00175905  Updated Misra comments
---------------------------   ----------    ------------  ------------------------------------------
Subramanya M Naik(b37356)     10/04/2012    ENGR00176437  Updated Misra comments
---------------------------   ----------    ------------  ------------------------------------------
Marius Rotaru (rtrm001)       25/07/2012    ENGR00218370  Re-sync from ASR4.0 legacy vob
---------------------------   ----------    ------------  ------------------------------------------
Alexandra Amarandei (b14660)  27/06/2013    ENGR00265778  Update misra for latest PClint
---------------------------   ----------    ------------  ------------------------------------------
Alexandra Amarandei (b14660)  27/03/2014    ENGR00297594  Add design entities
---------------------------   ----------    ------------  ------------------------------------------
Madi Petrareanu    (b37403)   28/04/2015    ENGR00363853  Correct name of version information macros
---------------------------   ----------    ------------  ------------------------------------------
',)dnl - DO NOT modify this M4 line!
==================================================================================================*/

/**
* @page misra_violations MISRA-C:2004 violations
*
*
* @section Std_Types_h_REF_1
* Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the
* contents of a header being included twice.
* This comes from the order of includes in the .c file and from include dependencies. As a safe
* approach, any file must include all its dependencies. Header files are already protected against
* double inclusions.
*
* @section Std_Types_h_REF_2
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely on the
* significance of more than 31 characters. The used compilers use more than 31 chars for identifiers
*/

#ifndef STD_TYPES_H
#define STD_TYPES_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Platform_Types.h"

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/
/**
* @brief Physical state 5V or 3.3V
* @implements SymbolDefinitions_enumeration
*/
#define STD_HIGH    0x01

/**
* @brief Physical state 0V.
* @implements SymbolDefinitions_enumeration
*/
#define STD_LOW     0x00

/**
* @brief Logical state active.
* @implements SymbolDefinitions_enumeration
*/
#define STD_ACTIVE  0x01

/**
* @brief Logical state idle.
* @implements SymbolDefinitions_enumeration
*/
#define STD_IDLE    0x00

/**
* @brief ON State.
* @implements SymbolDefinitions_enumeration
*/
#define STD_ON      0x01

/**
* @brief OFF state.
* @implements SymbolDefinitions_enumeration
*/
#define STD_OFF     0x00

/**
* @brief Return code for failure/error.
* @implements SymbolDefinitions_enumeration
*/
#define E_NOT_OK    0x01

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/**
* @brief The compiler abstraction shall provide the NULL_PTR define with a void pointer to zero
*        definition.
*/
#ifndef NULL_PTR
  #define NULL_PTR ((void *)0)
#endif

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
* @brief Because E_OK is already defined within OSEK, the symbol E_OK has to be shared. To avoid
*        name clashes and redefinition problems, the symbols have to be defined in the following way
*       (approved within implementation).
*/
#ifndef STATUSTYPEDEFINED
    #define STATUSTYPEDEFINED
    /**
    * @brief Success return code
    */
    #define E_OK      0x00
    /**
    * @brief This type is defined for OSEK compliance.
    */
    typedef unsigned char StatusType;
#endif

/**
* @brief This type can be used as standard API return type which is shared between the RTE and the
*        BSW modules.
* @implements Std_ReturnType_type
*/
typedef unsigned char Std_ReturnType;


/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef STD_TYPES_H */

/** @} */

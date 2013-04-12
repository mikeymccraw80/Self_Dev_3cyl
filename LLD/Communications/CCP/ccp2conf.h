#ifndef CCP2CONF_H
#define CCP2CONF_H

//===========================================================================
// Include Files
//===========================================================================
#include "reuse.h"
#include "ccp2main.h"
#include "dd_flexcan_interface.h"

//===========================================================================
// Macro Definitions (application specific)
//===========================================================================

// Memory Map of Product RAM
// REGISTER space is used for the Working Page for RAM Overlay.  The Reference
// page is placed in the 0x*0000000 space, so we add xxxxx to determine the
// corresponding Working Page address in yyyyyy.
// INCA will request writes to the 0xA0000000 space, so the register user function
// must translate these to the working page.
// The size of the calibrations is set to 128K
#define FLASH_START_ADDRESS    ((uint8_t*)(0x00000000))
#define FLASH_STOP_ADDRESS     ((uint8_t*)(0x0017FFFF))

#define RAM_START_ADDRESS      ((uint8_t*)(0x40000000))
#define RAM_STOP_ADDRESS       ((uint8_t*)(0x4000FFFF))

// shall be checked for instrumented unit
#define RAM2_START_ADDRESS     ((uint8_t*)(0x40010000))
#define RAM2_STOP_ADDRESS      ((uint8_t*)(0x4002FFFF))

// Vertical external ram
#define EXTERNAL_RAM_START_ADDRESS  ((uint8_t*)0x30000000)
#define EXTERNAL_RAM_STOP_ADDRESS   ((uint8_t*)0x3001FFFF)

#define CAL_START_ADDRESS      ((uint8_t*)(0x00020000))
#define CAL_STOP_ADDRESS       ((uint8_t*)(0x0003FFFF))

// shall be checked for instrumented unit
#define RAM2_ED_START_ADDRESS  ((uint8_t*)(0x40010000))
#define RAM2_ED_STOP_ADDRESS   ((uint8_t*)(0x4002FFFF))

#define REGISTER_START_ADDRESS ((uint8_t*)(0x00020000))
#define REGISTER_STOP_ADDRESS  ((uint8_t*)(0x0003FFFF))


// Obsolete Function Names
#define CCP_BackgroundTask CCP_Periodic_Task

// CAN IDs for CCP
#define CCP_CANID_CRO       (0x7D0)
#define CCP_CANID_DTO       (0x7D4)
#define CCP_CANID_DAQ0      (0x7D5)
#define CCP_CANID_DAQ1      (0x7D6)
#define CCP_CANID_DAQ2      (0x7D7)
#define CCP_CANID_DAQ3      (0x7D8)
#define CCP_INCA_RECEIVE    (0x6FB)
#define CCP_INCA_TRANSIT    (0x6FA)


//===========================================================================
// Macro Definitions
//===========================================================================
#define INITIAL_SESSION_STATUS_STATE (0x00)

// ECU CCP definition            
#define CCP_CRO             (CCP_CANID_CRO)  // CCP CRO CAN Identifier     
#define CCP_DTO             (CCP_CANID_DTO)  // CCP DTO CAN Identifier     
#define CCP_STATION_ADDRESS (0x0000)         // CCP station address for ECU

// Older versions of the ITS software only support 24-bit addressing.  To make
// use of it with 32-bit addresses, the ITS_ADDRESS_MASK will supply the upper
// byte of the address.
// if ITS_PATCH_IS_REQUIRED == true, then
// address = address | ITS_ADDRESS_MASK
#define ITS_PATCH_IS_REQUIRED          (false)
#define ITS_ADDRESS_MASK               (0xA0000000)

// Applicable to little-endian CPUs only.  Depending on the instrumentation software,
// it may be necessary to transmit DAQ data in big endian format.  This may need to
// be true for ITS use.
#define FORCE_MSB_FIRST_DAQ_PROCESSING (false)

// DAQ lists are based on 16-bit addresses to save RAM.  This is the base address
// to be added to DAQ list pointers.
#define CCP_RAM_BASE_ADDRESS     (0x40000000U)

// TO BE REMOVED WHEN FUNCTIONS ARE ACTUALLY DEFINED!!!
//#define CCP_Write_To_EEPROM_Memory_User( a, b ) { PARAM_NOT_USED(a); PARAM_NOT_USED(b); }
//#define CCP_Write_To_FLASH_Memory_User( a, b ) { PARAM_NOT_USED(a); PARAM_NOT_USED(b); }

//===========================================================================
// #defines for the 'dimensions' of the ODT's and DAQ's
//===========================================================================
#define NUMBER_OF_DAQ_LISTS ( 0x04 ) // Max. 0xFE DAQ lists total
#define NUMBER_OF_RESUMEABLE_DAQ_LISTS ( 0x04 )

//===========================================================================
// Enumeration Definitions (must be prior to constant definition)
//===========================================================================

//===========================================================================
// CCP 2.1 Command Codes
//
// The following commands are optional, if the ECU does not support DAQ:
//
//    GET_DAQ_SIZE,
//    SET_DAQ_PTR,
//    WRITE_DAQ,
//    START_STOP.
//
// If SELECT_CAL_PAGE is implemented, GET_ACTIVE_CAL_PAGE is required.
//===========================================================================
typedef enum CCP_Command_Code_tag
{
   CC_CONNECT             = 0x01,
   CC_SET_MTA             = 0x02,
   CC_DNLOAD              = 0x03,
   CC_UPLOAD              = 0x04,
   CC_TEST                = 0x05, // OPTIONAL COMMAND
   CC_START_STOP          = 0x06,
   CC_DISCONNECT          = 0x07,
   CC_START_STOP_ALL      = 0x08, // OPTIONAL COMMAND
   CC_GET_ACTIVE_CAL_PAGE = 0x09, // OPTIONAL COMMAND
   CC_SET_S_STATUS        = 0x0C, // OPTIONAL COMMAND
   CC_GET_S_STATUS        = 0x0D, // OPTIONAL COMMAND
   CC_BUILD_CHKSUM        = 0x0E, // OPTIONAL COMMAND
   CC_SHORT_UP            = 0x0F, // OPTIONAL COMMAND
   CC_CLEAR_MEMORY        = 0x10, // OPTIONAL COMMAND
   CC_SELECT_CAL_PAGE     = 0x11, // OPTIONAL COMMAND
   CC_GET_SEED            = 0x12, // OPTIONAL COMMAND
   CC_UNLOCK              = 0x13, // OPTIONAL COMMAND
   CC_GET_DAQ_SIZE        = 0x14,
   CC_SET_DAQ_PTR         = 0x15,
   CC_WRITE_DAQ           = 0x16,
   CC_EXCHANGE_ID         = 0x17,
   CC_PROGRAM             = 0x18, // OPTIONAL COMMAND
   CC_MOVE                = 0x19, // OPTIONAL COMMAND
   CC_GET_CCP_VERSION     = 0x1B,
   CC_DIAG_SERVICE        = 0x20, // OPTIONAL COMMAND
   CC_ACTION_SERVICE      = 0x21, // OPTIONAL COMMAND
   CC_PROGRAM_6           = 0x22, // OPTIONAL COMMAND
   CC_DNLOAD_6            = 0x23  // OPTIONAL COMMAND

}  CCP_Command_Code_T;

//===========================================================================
// Constant Definitions
//===========================================================================
// This defines the number of CCP command messages available.
#define CCP_COMMAND_QUANTITY (CC_DNLOAD_6 + 1)

// Constant array of function pointers for CCP commands
extern CCP_CRC_T (* const CCP_COMMAND_FCN_PTR[CCP_COMMAND_QUANTITY])( void );

#endif // CCP2CONF_H

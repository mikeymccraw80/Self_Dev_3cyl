#ifndef KW2CFG_H
#define KW2CFG_H
/* ============================================================================ *\
 * kw2cfg.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2cfg.h-1:incl:mt20a#1
 * Revision:        1
 * Creation date:   Tuesday, June 18, 2002 9:01:26 AM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains function to configure the re-useable kw2000 with this package.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */


/* ============================================================================ *\
 * Standard header files.
\* ============================================================================ */
#include "reuse.h"
#include "lux_type.h"

/* ============================================================================ *\
 * Other header files.
\* ============================================================================ */
// #include "immo.h"
// #include "id_cald.h"

/* ============================================================================ *\
 * Standard header files.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Other header files.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Exported preprocessor #define commands.
\* ============================================================================ */

#define dgPowertrainGroup        (0x0000)
#define dgAllGroup               (0xff00)

/*--- Data Types list (format: 0xX0) ---*/
#define dtUnsignedNumeric              (0 << 4)
#define dtSignedNumeric                (1 << 4)
#define dtBitMappedReportedWithoutMask (2 << 4)
#define dtBitMappedReportedWithMask    (3 << 4)
#define dtBinaryCodedDecimal           (4 << 4)
#define dtStateEncodedVariable         (5 << 4)
#define dtASCII                        (6 << 4)
#define dtSignedFloatingPointIEEE      (7 << 4)
#define dtPacket                       (8 << 4)
#define dtFormula                      (9 << 4)


/*--- ECU Identifier Object list: standards ---*/
#define eioVehicleManufacturerEnableCounter         (0xA0)
#define eioCrankShaftAdaptiveCylinder	            (0x0A)
#define eioTECDSampleCounter		            (0x0B)
#define eioVehicleIdentificationNumber              (0x90)
#define eioRepairShopCodeOrTesterSerialNumber       (0x98)
#define eioProgrammingDate                          (0x99)

#define eioVehicleManufacturerECUHardwareNumber     (0x91)
#define eioSystemSupplierECUHardwareNumber          (0x92)
#define eioSystemSupplierECUHardwareVersionNumber   (0x93)/* Not implemented */
#define eioSystemSupplierECUSoftwareName            (0x94)
#define eioSystemSupplierECUSoftwareVersionNumber   (0x95)
#define eioExhaustRegulationOrTypeApprovalNumber    (0x96)
#define eioSystemNameOrEngineType                   (0x97)

/*--- ECU Identifier Object list: manufacturer specific (9Ah..9Fh) ---*/
#define eioDiagnosticDataIdentifier                 (0x9A)
#define eioSoftwareName                             (0x9B)
/*--- ECU Indentifier Object list: immobilizer deactivation ---*/
#define eioDeactivateImmobilizerFunction            (0xA2)
/*--- Special ---*/
#define eioEndOfScalingTable                        (0xFF)

/*--- List of Identification Options ---*/
#define ioReportECUIdentificationTable              (0x80)
#define ioReportECUIdentificationScalingTable       (0x81)
#define ioReportCheryECUIdentificationSWname     (0x82)
#define ioReportCheryECUIdentificationHWname      (0x83)
#define ioReportCheryECUIdentificationSerialNumbername (0x84)
#define ioReportCheryECUIdentificationOrPrgname   (0x85)
#define ioReportCheryECUIdentificationNO1Prgname  (0x86)
#define ioReportCheryECUIdentificationNO2Prgname  (0x87)
#define ioReportCheryECUIdentificationNO3Prgname  (0x88)



#define ioReportVIN                                 (0x90)
#define ioReportVMECUHN                             (0x91)
#define ioSystemSupplierECUSoftwareName             (0x94)
#define ioReportSystemNameOrEngineType              (0x97)
#define ioRepairShopCodeOrTesterSerialNumber	    (0x98)
#define ioProgrammingDate			    (0x99)

#define ioSecretKEY        (0x10)
#define ioSecretCode       (0x20)
#define ioEe_immo_option   (0x30)


/* ============================================================================ *\
 * Exported type declarations.
\* ============================================================================ */

typedef uint8_t Kw2SparkAdvanceDegB ;
#define Prec_Kw2SparkAdvanceDegB (180.0 / 256)
#define Min_Kw2SparkAdvanceDegB  (-90.0)
#define Max_Kw2SparkAdvanceDegB  (255.0 * 180.0 / 256 - 90.0)

#define RFactor_SparkAdvance_Deg_B_Kw2SparkAdvanceDegB (256.0 / 90) /* OK */
#define RFactor_Kw2SparkAdvanceDegB_SparkAdvance_Deg_B (256.0 / 90) /* OK */


typedef uint8_t Kw2MicroSec ;

#define Prec_Kw2MicroSec (256.0 / 3)
#define Min_Kw2MicroSec  (0.0)
#define Max_Kw2MicroSec  (255 * 256.0 / 3)

#define RFactor_MicroSec_INJ_Kw2MicroSec (2048.0 * 3) /*--- OK ---*/
#define RFactor_Kw2MicroSec_MicroSec_INJ (2048.0 * 3) /*--- OK ---*/
#define RFactor_MicroSec_EST_Kw2MicroSec (2048.0 * 3) /*--- OK ---*/
#define RFactor_Kw2MicroSec_MicroSec_EST (2048.0 * 3) /*--- OK ---*/

#define CrankShaftAdaptiveCylinderSize    (16)

/* ============================================================================ *\
 * Exported variables.
\* ============================================================================ */
/*  none */


/* ============================================================================ *\
 * Exported Function prototypes
 * ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Exported INLINE functions and #define function-like macros.
\* ============================================================================ */

#define CanBeProgrammed()              ( true )

#define Get_Security_Seed_Data()       ((uint16_t) Kw2000Seed )

#define Get_Security_Key_Data()        ((uint16_t) Kw2000Key )

#define Get_L2_Security_Seed_Data()    ((uint16_t) Kw2000Level2Seed )

#define Get_L2_Security_Key_Data()     ((uint16_t) Kw2000Level2Key )


/* ============================================================================ *\
 * Exported preprocessor #define commands.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Exported type declarations.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Exported variables.
\* ============================================================================ */
/*  none */


/* ============================================================================ *\
 * Exported Function prototypes
 * ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Exported INLINE functions and #define function-like macros.
\* ============================================================================ */
/*  none  */





/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
 * 23/05/03     sgchia      118
 * + Kw2000 DE broadcast code reading.
 *
 * 09/06/06     Jerry.Wu    mt20u2#51
 * + Update kword spec
 *   - Add new macros
 *
 * 05/01/07     LShoujun    mt20u2#72
 * + Integrated generic immobiliser from MT22U project
 *   - defined: ioSecretKEY, ioSecretCode, ioEe_immo_option
 *
 * 12/03/07     LShoujun    mt20u2#78
 * + Integrate P2 old immo into dev10
 *   - Recovered eioDeactivateImmobilizerFunction for old immo
\* ============================================================================ */
#endif

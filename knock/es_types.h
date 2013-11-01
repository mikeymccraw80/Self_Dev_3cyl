#ifndef ES_TYPE_H
#define ES_TYPE_H

/* ============================================================================ *\
 * Standard header files.
\* ============================================================================ */
#include "lux_type.h"
#include "lux_math.h"
#include "lux_lkup.h"


/* ============================================================================ *\
 * Other header files.
\* ============================================================================ */


/* ============================================================================ *\
 * Exported preprocessor #define commands.
\* ============================================================================ */

#define SLOW_CELL_MATRIX_RPM_COLUMN_NUMBER (5)
#define SLOW_CELL_MATRIX_LOAD_ROW_NUMBER   (3)
#define SLOW_CELL_MATRIX_SIZE (SLOW_CELL_MATRIX_RPM_COLUMN_NUMBER * \
                               SLOW_CELL_MATRIX_LOAD_ROW_NUMBER)


/* ============================================================================ *\
 * Exported type declarations.
\* ============================================================================ */


typedef struct
{
    bitfield8_t  Bit7          : 1 ;
    bitfield8_t  Bit6          : 1 ;
    bitfield8_t  Bit5          : 1 ;
    bitfield8_t  Bit4          : 1 ;
    bitfield8_t  Bit3          : 1 ;
    bitfield8_t  Bit2          : 1 ;
    bitfield8_t  Bit1          : 1 ;
    bitfield8_t  Esc_Enabled  : 1 ;
} EscOptions_Type ;

typedef struct
{
    bitfield8_t  KnockActive                    : 1 ;
    bitfield8_t  KnockPresent                   : 1 ;
    bitfield8_t  MultiplierDeltaRPM             : 1 ;
    bitfield8_t  MultiplierDeltaTPS             : 1 ;
    bitfield8_t  MADTransientDetected           : 1 ;
    bitfield8_t  MADFilteringEnabled            : 1 ;
    bitfield8_t  TipInConditionsDetected        : 1 ;
    bitfield8_t  EscEnabled                     : 1 ;
} EscFlag_Type ;


typedef union
{
 	uint8_t Byte;
	struct
   {
      bitfield8_t Unused		: 2; /* unused bits */
      bitfield8_t RamptoZeroActive	: 1; /* ESC Adaptive ramping to zero */
      bitfield8_t RamptoTgtActive	: 1; /* ESC Adaptive ramping to target value */
      bitfield8_t Cylinder3Ramping	: 1; /* clinder 3 ramping flag */
      bitfield8_t Cylinder2Ramping	: 1; /* clinder 2 ramping flag */
      bitfield8_t Cylinder1Ramping	: 1; /* clinder 1 ramping flag */
      bitfield8_t Cylinder0Ramping	: 1; /* clinder 0 ramping flag */
	} Bits;
} ESCRAMPING_T;


typedef uint16_t               CrankAngleInDeg_W ;
#define Prec_CrankAngleInDeg_W                ( 1.0 /64.0 )
#define Min_CrankAngleInDeg_W                        ( -512.0 )
#define Max_CrankAngleInDeg_W         ( 65535 /64.0-512.0 )

/* T_MILLISECONDSb: Range [0ms, 1024ms) Res: 0.015625ms */
//typedef FIXED_UW_06                              T_MILLISECONDSb;
#define Prec_T_MILLISECONDSb                    (1.0/64.0)
#define Min_T_MILLISECONDSb                          0.0
#define Max_T_MILLISECONDSb                   Prec_T_MILLISECONDSb*65535

				      
/* T_CRANK_ANGLEa: Range [-512CAD, 512CAD) Res: 0.015625CAD */
//typedef INTEGER                              T_CRANK_ANGLEa;
#define Prec_T_CRANK_ANGLEa       (1.0/64.0)  
#define Min_T_CRANK_ANGLEa                        ( -512.0 )
#define Max_T_CRANK_ANGLEa        ( 32767 / 64 )


typedef uint8_t                      KnockIntegrator_Type_B ;
#define Prec_KnockIntegrator_Type_B  (1.0)
#define Min_KnockIntegrator_Type_B   (0.0)
#define Max_KnockIntegrator_Type_B   (255 * Prec_KnockIntegrator_Type_B)

typedef uint16_t                       KnockIntegrator_Type ;
#define Prec_KnockIntegrator_Type  (Prec_KnockIntegrator_Type_B / 256)
#define Min_KnockIntegrator_Type   (0.0)
#define Max_KnockIntegrator_Type   (65535 * Prec_KnockIntegrator_Type)

#define RFactor_KnockIntegrator_Type_B_KnockIntegrator_Type (256.0)

typedef uint32_t                       KnockIntegrator_Type_Base ;
#define Prec_KnockIntegrator_Type_Base  (Prec_KnockIntegrator_Type)
#define Min_KnockIntegrator_Type_Base   (0.0)
#define Max_KnockIntegrator_Type_Base   \
  (MAX_uint32_t * Prec_KnockIntegrator_Type_Base)

#define RFactor_KnockIntegrator_Type_Base_KnockIntegrator_Type (65536.0)




typedef uint8_t                      BPFCenterFreq_Type ;
#define Prec_BPFCenterFreq_Type      (1.0)
#define Min_BPFCenterFreq_Type       (0.0)
#define Max_BPFCenterFreq_Type       (15 * Prec_BPFCenterFreq_Type)




#endif /* ES_TYPE_H */

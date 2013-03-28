#ifndef DD_DSPI_H
#define DD_DSPI_H

#include "hw_dspi.h"

typedef enum
{
   DSPI_DEVICE_A,  // @emem DSPI Device A
   DSPI_DEVICE_B,  // @emem DSPI Device B
   DSPI_DEVICE_C,  // @emem DSPI Device C
   DSPI_DEVICE_D,  // @emem DSPI Device D
   DSPI_DEVICE_MAX
} DSPI_Index_T;

// @enum DSPI_Device_Type_T | Defines device type master/slave .
typedef enum 
{
   DSPI_DEVICE_TYPE_SLAVE,
   DSPI_DEVICE_TYPE_MASTER

} DSPI_Device_Type_T;

//=============================================================================
// Enumeration: DSPI Configuration (DCONF)
//
//  DCONF[1:0]     Configuration
// ===========  =============================================================
//         00   SPI
//         01   DSI
//         10   CSI
//         11   Reserved
//=============================================================================
typedef enum DSPI_MCR_DCONF_Tag
{
   DSPI_MCR_DCONF_SPI,
   DSPI_MCR_DCONF_DSI,
   DSPI_MCR_DCONF_CSI,
   DSPI_MCR_DCONF_RESERVED

}  DSPI_MCR_DCONF_T;


//=============================================================================
// Enumeration: Sample Point     (SMPL_PT)
//
//  SMPL_PT     Number of system clock cycles between odd-numbered edge
//   [1:0]            of SCK and sampling of SIN
// ========  ===============================================================
//      00   0
//      01   1
//      10   2
//      11   Reserved
//=============================================================================

typedef enum DSPI_MCR_SMPL_PT_Tag
{
   DSPI_MCR_SMPL_PT_0,
   DSPI_MCR_SMPL_PT_1,
   DSPI_MCR_SMPL_PT_2,
   DSPI_MCR_SMPL_PT_RESERVED

}  DSPI_MCR_SMPL_PT_T;

typedef enum DSPI_CONT_SCK_State_Tag
{
   DSPI_CONT_SCK_DISABLE,
   DSPI_CONT_SCK_ENABLE
} DSPI_CONT_SCK_State_T;

typedef enum DSPI_MCR_Parity_Error_Tag
{
   DSPI_MCR_SPI_FRAMES_TX_CONTINUE,
   DSPI_MCR_SPI_FRAMES_TX_STOP
} DSPI_MCR_Parity_Error_T;



typedef enum 
{
   DSPI_CTAR_SCK_INACTIVE_STATE_LO,
   DSPI_CTAR_SCK_INACTIVE_STATE_HI
} DSPI_CTAR_Clock_Polarity_T;

typedef enum 
{
   DSPI_CTAR_SCK_PHASE_LEADING_EDGE,
   DSPI_CTAR_SCK_PHASE_FALLING_EDGE

} DSPI_CTAR_Clock_Phase_T;

typedef enum 
{
   DSPI_CTAR_DBR_DISABLE,
   DSPI_CTAR_DBR_ENABLE

} DSPI_CTAR_DBR_State_T;

//=============================================================================
// Enumeration: Framesize     (FMSZ)
//
//    FMSZ[3:0]    Framesize
// =============  ==========================================================
//
//         0000   Reserved
//         0001   Reserved
//         0010   Reserved
//         0011   4
//         0100   5
//         0101   6
//         0110   7
//         0111   8
//         1000   9
//         1001   10
//         1010   11
//         1011   12
//         1100   13
//         1101   14
//         1110   15
//         1111   16
//
//=============================================================================

typedef enum DSPI_CTAR_FMSZ_Tag
{
   DSPI_CTAR_FMSZ_RESERVED1,
   DSPI_CTAR_FMSZ_RESERVED2,
   DSPI_CTAR_FMSZ_RESERVED3,
   DSPI_CTAR_FMSZ_4,
   DSPI_CTAR_FMSZ_5,
   DSPI_CTAR_FMSZ_6,
   DSPI_CTAR_FMSZ_7,
   DSPI_CTAR_FMSZ_8,
   DSPI_CTAR_FMSZ_9,
   DSPI_CTAR_FMSZ_10,
   DSPI_CTAR_FMSZ_11,
   DSPI_CTAR_FMSZ_12,
   DSPI_CTAR_FMSZ_13,
   DSPI_CTAR_FMSZ_14,
   DSPI_CTAR_FMSZ_15,
   DSPI_CTAR_FMSZ_16

}  DSPI_CTAR_FMSZ_T;

typedef enum DSPI_CTAR_SLAVE_FMSZ_Tag
{
   DSPI_CTAR_SLAVE_FMSZ_RESERVED1,
   DSPI_CTAR_SLAVE_FMSZ_RESERVED2,
   DSPI_CTAR_SLAVE_FMSZ_RESERVED3,
   DSPI_CTAR_SLAVE_FMSZ_4,
   DSPI_CTAR_SLAVE_FMSZ_5,
   DSPI_CTAR_SLAVE_FMSZ_6,
   DSPI_CTAR_SLAVE_FMSZ_7,
   DSPI_CTAR_SLAVE_FMSZ_8,
   DSPI_CTAR_SLAVE_FMSZ_9,
   DSPI_CTAR_SLAVE_FMSZ_10,
   DSPI_CTAR_SLAVE_FMSZ_11,
   DSPI_CTAR_SLAVE_FMSZ_12,
   DSPI_CTAR_SLAVE_FMSZ_13,
   DSPI_CTAR_SLAVE_FMSZ_14,
   DSPI_CTAR_SLAVE_FMSZ_15,
   DSPI_CTAR_SLAVE_FMSZ_16,
   DSPI_CTAR_SLAVE_FMSZ_17,
   DSPI_CTAR_SLAVE_FMSZ_18,
   DSPI_CTAR_SLAVE_FMSZ_19,
   DSPI_CTAR_SLAVE_FMSZ_20,
   DSPI_CTAR_SLAVE_FMSZ_21,
   DSPI_CTAR_SLAVE_FMSZ_22,
   DSPI_CTAR_SLAVE_FMSZ_23,
   DSPI_CTAR_SLAVE_FMSZ_24,
   DSPI_CTAR_SLAVE_FMSZ_25,
   DSPI_CTAR_SLAVE_FMSZ_26,
   DSPI_CTAR_SLAVE_FMSZ_27,
   DSPI_CTAR_SLAVE_FMSZ_28,
   DSPI_CTAR_SLAVE_FMSZ_29,
   DSPI_CTAR_SLAVE_FMSZ_30,
   DSPI_CTAR_SLAVE_FMSZ_31,
   DSPI_CTAR_SLAVE_FMSZ_32

}  DSPI_CTAR_SLAVE_FMSZ_T;

//=============================================================================
// Enumeration: PCS to SCK Delay Prescaler.     (PCSSCK)
//
//   PCSSCK       PCS to SCK Delay
//    [1:0]        Prescaler Value
// =========  ==============================================================
//
//       00   1
//       01   3
//       10   5
//       11   7
//
//=============================================================================

typedef enum DSPI_CTAR_PCSSCK_Tag
{
   DSPI_CTAR_PCSSCK_1,
   DSPI_CTAR_PCSSCK_3,
   DSPI_CTAR_PCSSCK_5,
   DSPI_CTAR_PCSSCK_7

}  DSPI_CTAR_PCSSCK_T;


//=============================================================================
// Enumeration: After SCK Delay Prescaler     (PASC)
//
//   PASC       After SCK Delay
//  [1:0]         Prescaler Value
// =======  =================================================================
//
//     00   1
//     01   3
//     10   5
//     11   7
//
//=============================================================================
typedef enum DSPI_CTAR_PASC_Tag
{
   DSPI_CTAR_PASC_1,
   DSPI_CTAR_PASC_3,
   DSPI_CTAR_PASC_5,
   DSPI_CTAR_PASC_7

}  DSPI_CTAR_PASC_T;




//=============================================================================
// Enumeration: Delay after Transfer Prescaler (PDT)
//
//    PDT       Delay after Transfer
//   [1:0]        Prescaler Value
// ========  ===============================================================
//
//      00   1
//      01   3
//      10   5
//      11   7
//
//=============================================================================

typedef enum DSPI_CTAR_PDT_Tag
{
   DSPI_CTAR_PDT_1,
   DSPI_CTAR_PDT_3,
   DSPI_CTAR_PDT_5,
   DSPI_CTAR_PDT_7

}  DSPI_CTAR_PDT_T;

//=============================================================================
// Enumeration: Baud Rate Prescaler (PBR)
//
//    PBR       Delay after Transfer
//    [1:0]       Prescaler Value
// ==========  ==============================================================
//
//        00   2
//        01   3
//        10   5
//        11   7
//
//=============================================================================

typedef enum DSPI_CTAR_PBR_Tag
{
   DSPI_CTAR_PBR_2,
   DSPI_CTAR_PBR_3,
   DSPI_CTAR_PBR_5,
   DSPI_CTAR_PBR_7

}  DSPI_CTAR_PBR_T;

//=============================================================================
// Enumeration: Scaler values for CSSCK, ASC and DT
//
//   CSSCK  -   PCS to SCK Delay Scaler
//   ASC    -   After SCK Delay Scaler
//   DT     -   Delay after Transfer Scaler.
//
//  DT/ASC/
//   CSSCK
//   [3:0]     Scaler Value
// =========  ==============================================================
//     0000   2
//     0001   4
//     0010   8
//     0011   16
//     0100   32
//     0101   64
//     0110   128
//     0111   256
//     1000   512
//     1001   1024
//     1010   2048
//     1011   4096
//     1100   8192
//     1101   16384
//     1110   32768
//     1111   65536
//
//
//=============================================================================

typedef enum DSPI_CTAR_CSSCK_DT_ASC_SCALER_Tag
{
   DSPI_CTAR_CSSCK_DT_ASC_SCALER_2,
   DSPI_CTAR_CSSCK_DT_ASC_SCALER_4,
   DSPI_CTAR_CSSCK_DT_ASC_SCALER_8,
   DSPI_CTAR_CSSCK_DT_ASC_SCALER_16,
   DSPI_CTAR_CSSCK_DT_ASC_SCALER_32,
   DSPI_CTAR_CSSCK_DT_ASC_SCALER_64,
   DSPI_CTAR_CSSCK_DT_ASC_SCALER_128,
   DSPI_CTAR_CSSCK_DT_ASC_SCALER_256,
   DSPI_CTAR_CSSCK_DT_ASC_SCALER_512,
   DSPI_CTAR_CSSCK_DT_ASC_SCALER_1024,
   DSPI_CTAR_CSSCK_DT_ASC_SCALER_2048,
   DSPI_CTAR_CSSCK_DT_ASC_SCALER_4096,
   DSPI_CTAR_CSSCK_DT_ASC_SCALER_8192,
   DSPI_CTAR_CSSCK_DT_ASC_SCALER_16384,
   DSPI_CTAR_CSSCK_DT_ASC_SCALER_32768,
   DSPI_CTAR_CSSCK_DT_ASC_SCALER_65536

}  DSPI_CTAR_CSSCK_DT_ASC_SCALER_T;

//=============================================================================
// Enumeration: Scaler values for BR
//
// BR[3:0]  Baud Rate Scaler Value
// =======  ================================================================
//    0000  2
//    0001  4
//    0010  6
//    0011  8
//    0100  16
//    0101  32
//    0110  64
//    0111  128
//    1000  256
//    1001  512
//    1010  1024
//    1011  2048
//    1100  4096
//    1101  8192
//    1110  16384
//    1111  32768
//=============================================================================

typedef enum DSPI_CTAR_BR_SCALER_Tag
{
   DSPI_CTAR_BR_SCALER_2,
   DSPI_CTAR_BR_SCALER_4,
   DSPI_CTAR_BR_SCALER_6,
   DSPI_CTAR_BR_SCALER_8,
   DSPI_CTAR_BR_SCALER_16,
   DSPI_CTAR_BR_SCALER_32,
   DSPI_CTAR_BR_SCALER_64,
   DSPI_CTAR_BR_SCALER_128,
   DSPI_CTAR_BR_SCALER_256,
   DSPI_CTAR_BR_SCALER_512,
   DSPI_CTAR_BR_SCALER_1024,
   DSPI_CTAR_BR_SCALER_2048,
   DSPI_CTAR_BR_SCALER_4096,
   DSPI_CTAR_BR_SCALER_8192,
   DSPI_CTAR_BR_SCALER_16384,
   DSPI_CTAR_BR_SCALER_32768

}  DSPI_CTAR_BR_SCALER_T;


//=============================================================================
// Enumeration: Clock and Transfer Attributes Select  (CTAS)
//
//  CTAS       Use Clock and Transfer
//               Attributes from
// =======  =================================================================
//
//    000   DSPI_CTAR0
//    001   DSPI_CTAR1
//    010   DSPI_CTAR2
//    011   DSPI_CTAR3
//    100   DSPI_CTAR4
//    101   DSPI_CTAR5
//    110   DSPI_CTAR6
//    111   DSPI_CTAR7
//
//=============================================================================

typedef enum DSPI_PUSHR_DSICR_CTAS_Tag
{
   DSPI_PUSHR_DSICR_CTAS_CTAR0,
   DSPI_PUSHR_DSICR_CTAS_CTAR1,
   DSPI_PUSHR_DSICR_CTAS_CTAR2,
   DSPI_PUSHR_DSICR_CTAS_CTAR3,
   DSPI_PUSHR_DSICR_CTAS_CTAR4,
   DSPI_PUSHR_DSICR_CTAS_CTAR5,
   DSPI_PUSHR_DSICR_CTAS_CTAR6,
   DSPI_PUSHR_DSICR_CTAS_CTAR7

}  DSPI_PUSHR_DSICR_CTAS_T;


typedef enum DSPI_DSICR_Sourc_Data_Tag
{
   DSPI_DSICR_SOURCE_DATA_SDR,
   DSPI_DSICR_SOURCE_DATA_ASDR
}  DSPI_DSICR_Source_Data_T;

typedef enum DSPI_DSICR_Timed_Serial_Bus_Tag
{
   DSPI_DSICR_TIMED_SERIAL_BUS_DISABLED,
   DSPI_DSICR_TIMED_SERIAL_BUS_ENABLED
}  DSPI_DSICR_Timed_Serial_Bus_T;

typedef enum DSPI_DSICR_Trigger_Polarity_Tag
{
   DSPI_DSICR_TRIGGER_FALLING_EDGE,
   DSPI_DSICR_TRIGGER_RISING_EDGE
}  DSPI_DSICR_Trigger_Polarity_T;

typedef enum DSPI_PUSHR_Parity_Tag
{
   DSPI_PUSHR_PARITY_DISABLE,
   DSPI_PUSHR_PARITY_ENABLE
}  DSPI_PUSHR_Parity_T;

typedef enum DSPI_PUSHR_Parity_Polarity_Tag
{
   DSPI_PUSHR_EVEN_PARITY,
   DSPI_PUSHR_ODD_PARITY
}  DSPI_PUSHR_Parity_Polarity_T;

//=============================================================================
// @enum DSPI Device Control and Transfer Configuration Position
//=============================================================================

typedef enum DSPI_TX_FIFO_Fill_Request_Tag
{
   DSPI_TX_FIFO_FILL_REQUEST_INTERRUPT,
   DSPI_TX_FIFO_FILL_REQUEST_DMA
}  DSPI_TX_FIFO_Fill_Request_T;

typedef enum DSPI_RX_FIFO_Drain_Request_Tag
{
   DSPI_RX_FIFO_DRAIN_REQUEST_INTERRUPT,
   DSPI_RX_FIFO_DRAIN_REQUEST_DMA
}  DSPI_RX_FIFO_Drain_Request_T;

typedef enum DSPI_Interrupt_DMA_Request_Tag
{
   DSPI_INTERRUPT_DMA_REQUEST_DISABLE,
   DSPI_INTERRUPT_DMA_REQUEST_ENABLE
}  DSPI_Request_State_T;



typedef enum DSPI_Interrupt_Tag
{
   DSPI_INTERRUPT_TX_COMPLETE,
   DSPI_INTERRUPT_DSPI_FINISHED,
   DSPI_INTERRUPT_TX_FIFO_UNDERFLOW,
   DSPI_INTERRUPT_TX_FIFO_FILL,
   DSPI_INTERRUPT_RX_FIFO_OVERFLOW,
   DSPI_INTERRUPT_RX_FIFO_DRAIN,
   DSPI_INTERRUPT_DSI_PARITY_ERROR,
   DSPI_INTERRUPT_SPI_PARITY_ERROR,
   DSPI_INTERRUPT_DSI_RX_ACTIVE_BITS,
   DSPI_INTERRUPT_MAX

}  DSPI_Interrupt_T;



typedef enum DSPI_CS_Tag
{
   DSPI_CS_0,
   DSPI_CS_1,
   DSPI_CS_2,
   DSPI_CS_3,
   DSPI_CS_4,
   DSPI_CS_5,
   DSPI_CS_6,
   DSPI_CS_7,
   DSPI_CS_MAX

} DSPI_CS_T;




#define DSPI_DBR_Raw_Value( dbr ) \
   ( dbr == DSPI_CTAR_DBR_DISABLE ? 0 : 1 )

#define DSPI_Get_PBR_Value( pbr ) \
   ( ( pbr == 0 ) ? 2 :\
     ( ( pbr << 1 ) + 1 ))

#define DSPI_Get_BDR_Value( bdr ) \
   ( (bdr == DSPI_CTAR_BR_SCALER_2)      ? 2       : \
   ( (bdr == DSPI_CTAR_BR_SCALER_4)      ? 4       : \
   ( (bdr == DSPI_CTAR_BR_SCALER_6)      ? 6       : \
   ( (bdr == DSPI_CTAR_BR_SCALER_8)      ? 8       : \
   ( (bdr == DSPI_CTAR_BR_SCALER_16)     ? 16      : \
   ( (bdr == DSPI_CTAR_BR_SCALER_32)     ? 32      : \
   ( (bdr == DSPI_CTAR_BR_SCALER_64)     ? 64      : \
   ( (bdr == DSPI_CTAR_BR_SCALER_128)    ? 128     : \
   ( (bdr == DSPI_CTAR_BR_SCALER_256)    ? 256     : \
   ( (bdr == DSPI_CTAR_BR_SCALER_512)    ? 512     : \
   ( (bdr == DSPI_CTAR_BR_SCALER_1024)   ? 1024    : \
   ( (bdr == DSPI_CTAR_BR_SCALER_2048)   ? 2048    : \
   ( (bdr == DSPI_CTAR_BR_SCALER_4096)   ? 4096    : \
   ( (bdr == DSPI_CTAR_BR_SCALER_8192)   ? 8192    : \
   ( (bdr == DSPI_CTAR_BR_SCALER_16384)  ? 16384   : \
   ( (bdr == DSPI_CTAR_BR_SCALER_32768)  ? 32768   : 2 ))))))))))))))))

#define DSPI_Get_BDR_Raw_Value( bdr ) \
   ( (bdr <= 2)      ? DSPI_CTAR_BR_SCALER_2       : \
   ( (bdr <= 4)      ? DSPI_CTAR_BR_SCALER_4       : \
   ( (bdr <= 6)      ? DSPI_CTAR_BR_SCALER_6       : \
   ( (bdr <= 8)      ? DSPI_CTAR_BR_SCALER_8       : \
   ( (bdr <= 16)     ? DSPI_CTAR_BR_SCALER_16      : \
   ( (bdr <= 32)     ? DSPI_CTAR_BR_SCALER_32      : \
   ( (bdr <= 64)     ? DSPI_CTAR_BR_SCALER_64      : \
   ( (bdr <= 128)    ? DSPI_CTAR_BR_SCALER_128     : \
   ( (bdr <= 256)    ? DSPI_CTAR_BR_SCALER_256     : \
   ( (bdr <= 512)    ? DSPI_CTAR_BR_SCALER_512     : \
   ( (bdr <= 1024)   ? DSPI_CTAR_BR_SCALER_1024    : \
   ( (bdr <= 2048)   ? DSPI_CTAR_BR_SCALER_2048    : \
   ( (bdr <= 4096)   ? DSPI_CTAR_BR_SCALER_4096    : \
   ( (bdr <= 8192)   ? DSPI_CTAR_BR_SCALER_8192    : \
   ( (bdr <= 16384)  ? DSPI_CTAR_BR_SCALER_16384   : \
   ( (bdr <= 32768)  ? DSPI_CTAR_BR_SCALER_32768   : 0 ))))))))))))))))

#define DSPI_Get_PDT_PCSSCK_Scaled_Value( pdt ) \
   ( ( pdt << 1 ) + 1 )

#define DSPI_Get_CSSCK_DT_ASC_Raw_Value( cssck_dt_asc_scaled ) \
   ( (cssck_dt_asc_scaled <= 2)      ? DSPI_CTAR_CSSCK_DT_ASC_SCALER_2      : \
   ( (cssck_dt_asc_scaled <= 4)      ? DSPI_CTAR_CSSCK_DT_ASC_SCALER_4      : \
   ( (cssck_dt_asc_scaled <= 8)      ? DSPI_CTAR_CSSCK_DT_ASC_SCALER_8      : \
   ( (cssck_dt_asc_scaled <= 16)     ? DSPI_CTAR_CSSCK_DT_ASC_SCALER_16     : \
   ( (cssck_dt_asc_scaled <= 32)     ? DSPI_CTAR_CSSCK_DT_ASC_SCALER_32     : \
   ( (cssck_dt_asc_scaled <= 64)     ? DSPI_CTAR_CSSCK_DT_ASC_SCALER_64     : \
   ( (cssck_dt_asc_scaled <= 128)    ? DSPI_CTAR_CSSCK_DT_ASC_SCALER_128    : \
   ( (cssck_dt_asc_scaled <= 256)    ? DSPI_CTAR_CSSCK_DT_ASC_SCALER_256    : \
   ( (cssck_dt_asc_scaled <= 512)    ? DSPI_CTAR_CSSCK_DT_ASC_SCALER_512    : \
   ( (cssck_dt_asc_scaled <= 1024)   ? DSPI_CTAR_CSSCK_DT_ASC_SCALER_1024   : \
   ( (cssck_dt_asc_scaled <= 2048)   ? DSPI_CTAR_CSSCK_DT_ASC_SCALER_2048   : \
   ( (cssck_dt_asc_scaled <= 4096)   ? DSPI_CTAR_CSSCK_DT_ASC_SCALER_4096   : \
   ( (cssck_dt_asc_scaled <= 8192)   ? DSPI_CTAR_CSSCK_DT_ASC_SCALER_8192   : \
   ( (cssck_dt_asc_scaled <= 16384)  ? DSPI_CTAR_CSSCK_DT_ASC_SCALER_16384  : \
   ( (cssck_dt_asc_scaled <= 32768)  ? DSPI_CTAR_CSSCK_DT_ASC_SCALER_32768  : \
   ( (cssck_dt_asc_scaled <= 65536)  ? DSPI_CTAR_CSSCK_DT_ASC_SCALER_65536  : 0xff ))))))))))))))))

#define DSPI_Get_PCSSCK_Delay_Value( pcssck ) \
   ( ( pcssck << 1 ) + 1 )

#define DSPI_Get_CSSCK_Delay_Value( cssck ) \
   ( 1 << (cssck + 1) )

#define DSPI_Get_PASCK_Delay_Value( pasck ) \
   ( ( pasck << 1 ) + 1 )

#define DSPI_Get_ASCK_Delay_Value( asck ) \
   ( 1 << (asck + 1) )

// DSPI_A
// @type DSPI_A | Handle to DSPI_A Registers
#define SECTION_DSPI_A_REGISTER
#include "section.h"
extern DSPI_T DSPI_A;
#define SECTION_END
#include "section.h"

// DSPI_B
// @type DSPI_B | Handle to DSPI_B Registers
#define SECTION_DSPI_B_REGISTER
#include "section.h"
extern DSPI_T DSPI_B;
#define SECTION_END
#include "section.h"

// DSPI_C
// @type DSPI_C | Handle to DSPI_C Registers
#define SECTION_DSPI_C_REGISTER
#include "section.h"
extern DSPI_T DSPI_C;
#define SECTION_END
#include "section.h"

// DSPI_D
// @type DSPI_D | Handle to DSPI_D Registers
#define SECTION_DSPI_D_REGISTER
#include "section.h"
extern DSPI_T DSPI_D;
#define SECTION_END
#include "section.h"





#endif


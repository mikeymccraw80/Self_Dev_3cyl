#ifndef IO_SPI_TIMING_H
#define IO_SPI_TIMING_H
//=============================================================================
//
//       COPYRIGHT, 2000, DELPHI DELCO ELECTRONICS SYSTEMS CORPORATION
//
//===========================================================================*
// %name:            io_spi_timing.h %
//
// created_by:       rskearne
//
// date_created:     Tue Aug 13 11:05:27 2002
//
// %derived_by:      dzhrz4 %
//
// %date_modified:   Tue Feb 28 08:05:25 2006 %
//
// %version:         2 %
//
//===========================================================================*
// SPECIFICATION REVISION:
//
//===========================================================================*
// REUSE:
// none
//
//=============================================================================
#define SPI_INTERRUPT_TIME_SEC ( 0.01000000 )

#define SEC_TO_CLOCK(t)         ( ( t / SPI_INTERRUPT_TIME_SEC )  )
/*
#define HFPS_COP_OFFSET          SEC_TO_CLOCK( 0.00781250 )
#define HFPS_COP_INTERVAL        SEC_TO_CLOCK( 0.02734375 )

#define HFPS_LPC_OFFSET          SEC_TO_CLOCK( 0.03906250 )
#define HFPS_LPC_INTERVAL        SEC_TO_CLOCK( 0.50000000 )

#define HFPS_CTRL_OFFSET         SEC_TO_CLOCK( 0.04296875 )
#define HFPS_CTRL_INTERVAL       SEC_TO_CLOCK( 0.12500000 )

#define PHD_OFFSET               SEC_TO_CLOCK( 0.00000000 )
#define PHD_INTERVAL             SEC_TO_CLOCK( 0.00781250 )

#define L9942_OFFSET             SEC_TO_CLOCK( 0.00000000 )
#define L9942_INTERVAL           SEC_TO_CLOCK( 0.06250000 )
*/
#define VSEP_SOH_OFFSET          SEC_TO_CLOCK( 0.00000000 )
#define VSEP_SOH_INTERVAL        SEC_TO_CLOCK( 0.02000000 )

#define VSEP_SOH_STATUS_OFFSET   SEC_TO_CLOCK( 0.03500000 )
#define VSEP_SOH_STATUS_INTERVAL SEC_TO_CLOCK( 0.16000000 )

#define VSEP_PWM_OFFSET(x)       SEC_TO_CLOCK( 0.01000000*x )
#define VSEP_PWM_INTERVAL        SEC_TO_CLOCK( 0.01000000 )

#define VSEP_PCH_OFFSET          SEC_TO_CLOCK( 0.01500000 )
#define VSEP_PCH_INTERVAL        SEC_TO_CLOCK( 0.01000000 )

#define VSEP_FAULT_OFFSET        SEC_TO_CLOCK( 0.00500000 )
#define VSEP_FAULT_INTERVAL      SEC_TO_CLOCK( 0.01000000 )

#endif /* IO_SPI_TIMING_H */
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80      *
\*===========================================================================*/

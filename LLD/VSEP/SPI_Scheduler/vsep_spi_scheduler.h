#ifndef VSEP_SPI_SCHEDULER_H
#define VSEP_SPI_SCHEDULER_H

#include "io_type.h"
#include "list.h"

typedef struct {
    void        *receive_data;
    void        *transmit_data;
    uint16_t    length_of_receive_message;
    uint16_t    length_of_transmit_message;
} SPI_Message_Definition_T;

typedef struct {
    SPI_Message_Definition_T const * spi_msg;
    uint32_t                  interval;
    uint32_t                  time;
    struct list_head          list;
} SPI_Message_Queue_T;

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

//=============================================================================
// VSEP_SPI_SCHEDULER_Initialize

//=============================================================================
void VSEP_SPI_SCHEDULER_Initialize(void);


//=============================================================================
// SPI_SCHEDULER_Set_Enable
//
// @func Enable or disable sending periodic messages 
// 
// @rdesc bool | The previous state of the scheduler.
// @flag  true | If the scheduler was previously running
// @flag false | If the scheduler was previously disabled
//
// @end
//=============================================================================
bool VSEP_SPI_SCHEDULER_Set_Enable( bool in_enable);

//=============================================================================
// SPI_SCHEDULER_Get_Status
//
// @func Get the state of the SPI scheduler. Is it enabled or disabled? 
// 
// @rdesc bool | The state of the SPI scheduler
// @flag  true | If the scheduler is running 
// @flag false | If the scheduler is disabled
//
// @end
//=============================================================================
bool VSEP_SPI_SCHEDULER_Get_Status( void );



//=============================================================================
// VSEP_SPI_SCHEDULER_10MS
//=============================================================================
void VSEP_SPI_SCHEDULER_10MS(void);



#endif // IO_SPI_SCHEDULER_H
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
\*===========================================================================*/

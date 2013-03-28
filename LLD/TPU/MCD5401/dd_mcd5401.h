#ifndef DD_MCD5401_H
#define DD_MCD5401_H

//===========================================================================
// include files                                                       
//===========================================================================
#include "mcd5401.h"
#include "dd_tpu.h"

//===========================================================================
// Macro Definitions                                                         
//===========================================================================

//===========================================================================
// ICPCE Host Service Request Definitions 
//===========================================================================
#define MCD5401_HSR_SHUTDOWN              ( 7 )
#define MCD5401_HSR_INIT_RISING_EDGE      ( 6 )
#define MCD5401_HSR_INIT_FALLING_EDGE     ( 5 )
#define MCD5401_HSR_INIT_BOTH_EDGE        ( 4 )
#define MCD5401_HSR_REQUEST_EVENT_TIME    ( 3 )
#define MCD5401_HSR_UPDATE_EVENT_TIME     ( 2 )



#endif // DD_MCD5401_H

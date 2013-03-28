#ifndef DD_MCD5411_H
#define DD_MCD5411_H

#include "mcd5411.h"


//===========================================================================
// Macro Definations for Host Service Request                                
//===========================================================================
#define MCD5411_HSR_CRIT_EDGE_FALLING     ( 5 )
#define MCD5411_HSR_CRIT_EDGE_RISING      ( 3 )

//===========================================================================
// Macro Definations
//===========================================================================
#define MCD5411_CAME_REPLICATE_ENABLE       (1)
#define MCD5411_CAME_REPLICATE_DISABLE      (0)
#define MCD5411_COHERENCY_BIT_MASK (uint32_t)( 0x80000000 )


#endif // DD_MCD5411_H

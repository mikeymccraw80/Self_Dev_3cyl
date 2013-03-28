#ifndef DD_XBAR_MPC5634_H
#define DD_XBAR_MPC5634_H

#include "hw_xbar_mpc5634.h"

//=============================================================================
// @doc IO_PERIPHERAL & XBAR & DEVICE & API
//=============================================================================

//=============================================================================
// XBAR
//=============================================================================
#define SECTION_XBAR_REGISTER
#include "section.h"
extern XBAR_T XBAR_5634;
#define SECTION_END
#include "section.h"

// @enum XBAR_Slave_Port_ID_T | XBAR Slave Port ID type
typedef enum XBAR_Slave_Port_ID_Tag
{
   XBAR_SLAVE_FLASH       =  0,  //@emem Slave Port ID for Flash
   XBAR_SLAVE_EBI         =  1,  //@emem Slave Port ID for EBI
   XBAR_SLAVE_L2SRAM      =  3,  //@emem Slave Port ID for L2SRAM
   XBAR_SLAVE_P_BRIDGE_A  =  6,  //@emem Slave Port ID for P Bridge A
   XBAR_SLAVE_P_BRIDGE_B  =  7   //@emem Slave Port ID for P Bridge B

}  XBAR_Slave_Port_ID_T;

// @enum XBAR_Slave_Config_Locked_T | XBAR Slave Read Only type
typedef enum XBAR_Slave_Read_Only_Tag
{
   XBAR_SLAVE_CONFIG_UNLOCKED,  //@emem SPGCR can be written
   XBAR_SLAVE_CONFIG_LOCKED    //@emem SPGCR is Read Only

}  XBAR_Slave_Config_Locked_T;

// @enum XBAR_Slave_Arbitration_T | XBAR Slave Arbitration Policy type
typedef enum XBAR_Slave_Arbitration_Tag
{
   XBAR_SLAVE_FIXED_ARBITRATION,       //@emem Fixed Arbitration
   XBAR_SLAVE_ROUND_ROBIN_ARBITRATION  //@emem Round Robin Arbitration

}  XBAR_Slave_Arbitration_T;

// @enum XBAR_Slave_Park_Control_T | XBAR Slave Parking Algoritm type
typedef enum XBAR_Slave_Park_Control_Tag
{
   XBAR_SLAVE_FIXED_PARKING,        //@emem Park on Master defined in PARK
   XBAR_SLAVE_LAST_MASTER_PARKING,  //@emem Park on last owning master
   XBAR_SLAVE_NO_MASTER_PARKING     //@emem Park on no master.

}  XBAR_Slave_Park_Control_T;

// @enum XBAR_Slave_Park_Selection_T | XBAR Slave Parking Master Selection type
typedef enum XBAR_Slave_Park_Selection_Tag
{
   XBAR_SLAVE_PARK_MASTER_0,  //@emem Park on Master 0
   XBAR_SLAVE_PARK_MASTER_1,  //@emem Park on Master 1
   XBAR_SLAVE_PARK_MASTER_2,  //@emem Park on Master 2.
   XBAR_SLAVE_PARK_MASTER_3   //@emem Park on Master 3.(only on 4x5 systems)

}  XBAR_Slave_Park_Selection_T;

// @enum XBAR_Priority_Master_T | XBAR Master Priority types
typedef enum XBAR_Master_Priority_Selection_Tag
{
   XBAR_MASTER_HIGHEST_PRIORITY_0,    //@emem Highest Priority assigned
   XBAR_MASTER_PRIORITY_1,                    //@emem Second Highest Priority assigned
   XBAR_MASTER_PRIORITY_2,                    //@emem Third Highest Priority assigned
   XBAR_MASTER_PRIORITY_3,   
   XBAR_MASTER_PRIORITY_4,  
   XBAR_MASTER_PRIORITY_5,  
   XBAR_MASTER_PRIORITY_6,     
   XBAR_MASTER_LOWEST_PRIORITY_7      //@emem Lowest Priority_7 assigned

}  XBAR_Master_Priority_Selection_T;

//@enum XBAR_Slave_Halt_Low_Priority_T | XBAR Slave initial Arbitration priority
typedef enum XBAR_Slave_Halt_Low_Priority_Tag
{
   XBAR_SLAVE_HIGHEST_INITIAL_PRIORITY, // @enum Highest initial priority assigned
   XBAR_SLAVE_LOWEST_INITIAL_PRIORITY   // @enum lowest initial priority assigned
   
}  XBAR_Slave_Halt_Low_Priority_T;

//@enum XBAR_Slave_High_Priority_Selection_T | XBAR High Priority input Selection 
typedef enum XBAR_Slave_High_Priority_Selection_Tag
{
   XBAR_SLAVE_HIGH_PRIORITY_INPUT_DISABLE,  //@enum highest priority input is disabled
   XBAR_SLAVE_HIGH_PRIORITY_INPUT_ENABLE    //@enum highest priority input is enabled
   
}  XBAR_Slave_High_Priority_Selection_T;

// @enum XBAR_Slave_Park_Selection_T | XBAR Slave Parking Master Selection type
typedef enum XBAR_Slave_Park_Tag
{
   XBAR_SLAVE_PARK_ON_MASTER_0,  //@emem Park on Master 0
   XBAR_SLAVE_PARK_ON_MASTER_1,  //@emem Park on Master 1
   XBAR_SLAVE_PARK_ON_MASTER_2,  //@emem Park on Master 2.
   XBAR_SLAVE_PARK_ON_MASTER_3,   //@emem Park on Master 3.(only on 4x5 systems)
   XBAR_SLAVE_PARK_ON_MASTER_4,  //@emem Park on Master 4.
   XBAR_SLAVE_PARK_ON_MASTER_5,  //@emem Park on Master 5.
   XBAR_SLAVE_PARK_ON_MASTER_6,  //@emem Park on Master 6.
   XBAR_SLAVE_PARK_ON_MASTER_7   //@emem Park on Master 7.

}  XBAR_Slave_Park_T;



#endif // DD_XBAR_MPC5634_H


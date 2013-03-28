#ifndef DD_XBAR_MPC5644_H
#define DD_XBAR_MPC5644_H

#include "hw_xbar_mpc5644.h"

//=============================================================================
// XBAR
//=============================================================================
#define SECTION_XBAR_REGISTER
#include "section.h"
extern XBAR_T XBAR_5644;
#define SECTION_END
#include "section.h"


// @enum XBAR_Slave_Port_ID_T | XBAR Slave Port ID type
typedef enum XBAR_Slave_Port_ID_Tag
{
   XBAR_SLAVE_FLASH       =  0,  //@emem Slave Port ID for Flash
   XBAR_SLAVE_EBI         =  1,  //@emem Slave Port ID for EBI
   XBAR_SLAVE_L2SRAM      =  2,  //@emem Slave Port ID for L2SRAM
   XBAR_SLAVE_P_BRIDGE_B  =  7   //@emem Slave Port ID for P Bridge

}  XBAR_Slave_Port_ID_T;

// @enum XBAR_Master_Priority_T | XBAR Master Priority types
typedef enum XBAR_Master_Priority_Tag
{
   XBAR_MASTER_HIGHEST_PRIORITY     = 0,    //@emem Highest Priority assigned
   XBAR_MASTER_2ND_HIGHEST_PRIORITY = 1,    //@emem Second Highest Priority assigned
   XBAR_MASTER_3RD_HIGHEST_PRIORITY = 2,    //@emem Third Highest Priority assigned
   XBAR_MASTER_4TH_HIGHEST_PRIORITY = 3,    //@emem Fourth Highest Priority assigned
   XBAR_MASTER_5TH_HIGHEST_PRIORITY = 4,    //@emem Fifth Highest Priority assigned
   XBAR_MASTER_3RD_LOWEST_PRIORITY  = 5,    //@emem Third Lowest Priority assigned
   XBAR_MASTER_2ND_LOWEST_PRIORITY  = 6,    //@emem Second Lowest Priority assigned
   XBAR_MASTER_LOWEST_PRIORITY      = 7     //@emem Lowest Priority assigned

}  XBAR_Master_Priority_T;

// @enum XBAR_Slave_Config_Locked_T | XBAR Slave Read Only type
typedef enum XBAR_Slave_Read_Only_Tag
{
   XBAR_SLAVE_CONFIG_UNLOCKED,  //@emem SPGCR can be written
   XBAR_SLAVE_CONFIG_LOCKED     //@emem SPGCR is Read Only

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
   XBAR_SLAVE_PARK_RESERVED1, //@emem Reserved
   XBAR_SLAVE_PARK_RESERVED2, //@emem Reserved
   XBAR_SLAVE_PARK_MASTER_4,  //@emem Park on Master 4
   XBAR_SLAVE_PARK_RESERVED3, //@emem Reserved
   XBAR_SLAVE_PARK_MASTER_6,  //@emem Park on Master 6
   XBAR_SLAVE_PARK_MASTER_7   //@emem Park on Master 7

}  XBAR_Slave_Park_Selection_T;

// @enum XBAR_High_Priority_Enable_T | XBAR High Priority Enable type
typedef enum XBAR_High_Priority_Enable_Tag
{
   XBAR_High_Priority_Disable,  //@emem Park on Master 0
   XBAR_High_Priority_Enable    //@emem Park on Master 1

} XBAR_High_Priority_Enable_T;



#endif // DD_XBAR_MPC5644_H


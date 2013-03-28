//=============================================================================
// Include the Type file for the device driver
//=============================================================================

//=============================================================================
// Include interface for the device driver
//=============================================================================
#include "dd_xbar_mpc5634.h"


//=============================================================================
// XBAR
//=============================================================================
#define SECTION_XBAR_5634_REGISTER
#include "section.h"
XBAR_T XBAR_5634;
#define SECTION_END
#include "section.h"


//=============================================================================
// XBAR_MPC5634M_Initialize_Device
//=============================================================================
void XBAR_MPC5634M_Initialize_Device( void )
{

   XBAR_MPR_T mpr;
   XBAR_SGPCR_T sgpcr;
   
   mpr.U32   = 0;
   sgpcr.U32 = 0;


      //These bits set the arbitration priority for master port 0 (e200z4 core instruction bus) on the associatedslave port.
       //000 This master has the highest priority when accessing the slave port.
      //...
      //111 This master has the lowest priority when accessing the slave port.
      mpr.F.MSTR0 = XBAR_MASTER_PRIORITY_1;
      //These bits set the arbitration priority for master port 1 (eDMA) on the associated slave port.
      //000 This master has the highest priority when accessing the slave port.
      //...
      //111 This master has the lowest priority when accessing the slave port.
      mpr.F.MSTR1 = XBAR_MASTER_HIGHEST_PRIORITY_0;
      //These bits set the arbitration priority for master port 2 (unused) on the associated slave port.
      //000 This master has the highest priority when accessing the slave port.
      //...
      //111 This master has the lowest priority when accessing the slave port.
      mpr.F.MSTR2 = XBAR_MASTER_PRIORITY_2;
      //These bits set the arbitration priority for master port 4 (e200z335 core Load/Store and e200z335 core Nexus) on the associated slave port.
      //000 This master has the highest priority when accessing the slave port.
      //...
      //111 This master has the lowest priority when accessing the slave port.
      mpr.F.MSTR4 = XBAR_MASTER_PRIORITY_3;


      //Read Only
      //This bit is used to force all of a slave port's registers to be read only. 
      //Once written to ¡®1¡¯ it can only be cleared by hardware reset.
      //This bit is initialized by hardware reset. The reset value is 0.
      sgpcr.F.RO   = XBAR_SLAVE_CONFIG_UNLOCKED;
      //Halt Low Priority
      //This bit is used to set the initial arbitration priority of the max_halt_request input.
      //This bit is initialized by hardware reset. The reset value is 0.
      sgpcr.F.HLP  = XBAR_SLAVE_HIGHEST_INITIAL_PRIORITY;
      // High Priority Enable
      //These bits are used to enable the mX_high_priority inputs for the respective master.
     //These bits are initialized by hardware reset. The reset value is 0.
      sgpcr.F.HPE4 = XBAR_SLAVE_HIGH_PRIORITY_INPUT_DISABLE;
      sgpcr.F.HPE2 = XBAR_SLAVE_HIGH_PRIORITY_INPUT_DISABLE;
      sgpcr.F.HPE1 = XBAR_SLAVE_HIGH_PRIORITY_INPUT_DISABLE;
      sgpcr.F.HPE0 = XBAR_SLAVE_HIGH_PRIORITY_INPUT_DISABLE;

	//Arbitration Mode
       //These bits are used to select the arbitration policy for the slave port.
      //These bits are initialized by hardware reset. The reset value is 00.
      sgpcr.F.ARB  = XBAR_SLAVE_FIXED_ARBITRATION;

      //Parking Control
      //These bits determine the parking control used by this slave port.
      //These bits are initialized by hardware reset. The reset value is 00.
      sgpcr.F.PCTL = XBAR_SLAVE_FIXED_PARKING;
      //PARK
      //These bits are used to determine which master port this slave port parks on when no masters are actively
      //making requests and the PCTL bits are set to 00.
      //These bits are initialized by hardware reset. The reset value is 000.
      sgpcr.F.PARK = XBAR_SLAVE_PARK_ON_MASTER_0;


      //XBAR_SLAVE_FLASH
     if (! XBAR_5634.SLAVE_PORT[XBAR_SLAVE_FLASH].SGPCR.F.RO)
     {
      //Master Priority Register for Slave port 0
        XBAR_5634.SLAVE_PORT[XBAR_SLAVE_FLASH].MPR        = mpr;
      //General Purpose Control Register for Slave port 0
         XBAR_5634.SLAVE_PORT[XBAR_SLAVE_FLASH].SGPCR      = sgpcr;
      }

      //XBAR_SLAVE_EBI
   if (! XBAR_5634.SLAVE_PORT[XBAR_SLAVE_EBI].SGPCR.F.RO)
   {
      //Master Priority Register for Slave port 1
      XBAR_5634.SLAVE_PORT[XBAR_SLAVE_EBI].MPR          = mpr;
	//General Purpose Control Register for Slave port 1
      XBAR_5634.SLAVE_PORT[XBAR_SLAVE_EBI].SGPCR        = sgpcr;
   }

     //XBAR_SLAVE_L2SRAM
   if (! XBAR_5634.SLAVE_PORT[XBAR_SLAVE_L2SRAM].SGPCR.F.RO)
   {
        //Master Priority Register for Slave port 3
      XBAR_5634.SLAVE_PORT[XBAR_SLAVE_L2SRAM].MPR       = mpr;
	 //General Purpose Control Register for Slave port 3
      XBAR_5634.SLAVE_PORT[XBAR_SLAVE_L2SRAM].SGPCR     = sgpcr;
   }

   //XBAR_SLAVE_P_BRIDGE_B
   if (! XBAR_5634.SLAVE_PORT[XBAR_SLAVE_P_BRIDGE_B].SGPCR.F.RO)
   {
      //Master Priority Register for Slave port 7
      XBAR_5634.SLAVE_PORT[XBAR_SLAVE_P_BRIDGE_B].MPR   = mpr;
     //General Purpose Control Register for Slave port 7
      XBAR_5634.SLAVE_PORT[XBAR_SLAVE_P_BRIDGE_B].SGPCR = sgpcr;
   }


}



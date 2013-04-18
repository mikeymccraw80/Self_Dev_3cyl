//=============================================================================
// Include the Type file for the device driver
//=============================================================================

//=============================================================================
// Include interface for the device driver
//=============================================================================
#include "dd_xbar_mpc5644.h"


//=============================================================================
// XBAR
//=============================================================================
#define SECTION_XBAR_5644_REGISTER
#include "section.h"
XBAR_T XBAR_5644;
#define SECTION_END
#include "section.h"


//=============================================================================
// XBAR_MPC5644M_Initialize_Device
//=============================================================================
void XBAR_MPC5644A_Initialize_Device( void )

{

   XBAR_MPR_T mpr;
   XBAR_SGPCR_T sgpcr;
   
   mpr.U32   = 0;
   sgpcr.U32 = 0;


      // MSTR0        [2:0] rw Master 0 Priority.
      //                      These bits set the arbitration priority for master port 0
      //                      on the associated slave port.
      //                      %000 = This master has the highest priority
      //                      %001 = This master has the second highest priority
      //                          .
      //                          .
      //                      %111 = This master has the lowest priority
      mpr.F.MSTR0 = XBAR_MASTER_3RD_HIGHEST_PRIORITY;
     // MSTR1        [6:4] rw Master 1 Priority.
     //                      These bits set the arbitration priority for master port 1
     //                      on the associated slave port.
     //                      %000 = This master has the highest priority
     //                      %001 = This master has the second highest priority
     //                        .
     //                        .
     //                      %111 = This master has the lowest priority
      mpr.F.MSTR1 = XBAR_MASTER_2ND_HIGHEST_PRIORITY;
     // MSTR4        [18:16] rw Master 4 Priority.
     //                      These bits set the arbitration priority for master port 4
     //                      on the associated slave port.
     //                      %000 = This master has the highest priority
    //                      %001 = This master has the second highest priority
    //                           .
    //                           .
    //                      %100 = This master has the lowest priority
    //                      %101 - 111 = Reserved
      mpr.F.MSTR4 = XBAR_MASTER_HIGHEST_PRIORITY;
    // MSTR6        [26:24] rw Master 6 Priority.
    //                      These bits set the arbitration priority for master port 6
    //                      on the associated slave port.
    //                      %000 = This master has the highest priority
    //                      %001 = This master has the second highest priority
    //                           .
    //                           .
    //                      %100 = This master has the lowest priority
    //                      %101 -111 = Reserved
      mpr.F.MSTR6 = XBAR_MASTER_2ND_LOWEST_PRIORITY;
    // MSTR7        [26:24] rw Master 7 Priority.
    //                      These bits set the arbitration priority for master port 7
    //                      on the associated slave port.
    //                      %000 = This master has the highest priority
    //                      %001 = This master has the second highest priority
    //                      %100 = This master has the lowest priority
    //                      %101 -111 = Reserved
      mpr.F.MSTR7 = XBAR_MASTER_LOWEST_PRIORITY;

    // HPEx         [23:16] rw High Priority Enable - These bits are used to enable
    //                      the mX_high_priority inputs for the respective master.
    //                      These bits are initialized by hardware reset.
    //                      The reset value is 0
    //                      0 = The mX_high_priority input is disabled on this
    //                          slave port
    //                      1 = The mX_high_priority input is enabled on this
    //                          slave port.
    //
      sgpcr.F.HPE7   = XBAR_High_Priority_Disable;
      sgpcr.F.HPE6  = XBAR_High_Priority_Disable;
      sgpcr.F.HPE4 = XBAR_High_Priority_Disable;
      sgpcr.F.HPE1 = XBAR_High_Priority_Disable;
      sgpcr.F.HPE0 = XBAR_High_Priority_Disable;

	//Arbitration Mode
       //These bits are used to select the arbitration policy for the slave port.
      //These bits are initialized by hardware reset. The reset value is 00.
      sgpcr.F.ARB  = XBAR_SLAVE_ROUND_ROBIN_ARBITRATION;

     //                      This bit forces slave registers to be read only after
     //                      to a 1.
     //                      %0 = This slave register is writeable
     //                      %1 = This slave register is Read Only
      sgpcr.F.RO  = XBAR_SLAVE_CONFIG_UNLOCKED;

      //Parking Control
      //These bits determine the parking control used by this slave port.
      //These bits are initialized by hardware reset. The reset value is 00.
      sgpcr.F.PCTL = XBAR_SLAVE_FIXED_PARKING;
      //PARK
      //These bits are used to determine which master port this slave port parks on when no masters are actively
      //making requests and the PCTL bits are set to 00.
      //These bits are initialized by hardware reset. The reset value is 000.
      sgpcr.F.PARK = XBAR_SLAVE_PARK_MASTER_0;


      //XBAR_SLAVE_FLASH
     if (! XBAR_5644.SLAVE_PORT[XBAR_SLAVE_FLASH].SGPCR.F.RO)
     {
      //Master Priority Register for Slave port 0
        XBAR_5644.SLAVE_PORT[XBAR_SLAVE_FLASH].MPR        = mpr;
      //General Purpose Control Register for Slave port 0
         XBAR_5644.SLAVE_PORT[XBAR_SLAVE_FLASH].SGPCR      = sgpcr;
      }

      //XBAR_SLAVE_EBI
   if (! XBAR_5644.SLAVE_PORT[XBAR_SLAVE_EBI].SGPCR.F.RO)
   {
      //Master Priority Register for Slave port 1
      XBAR_5644.SLAVE_PORT[XBAR_SLAVE_EBI].MPR          = mpr;
	//General Purpose Control Register for Slave port 1
      XBAR_5644.SLAVE_PORT[XBAR_SLAVE_EBI].SGPCR        = sgpcr;
   }

     //XBAR_SLAVE_L2SRAM
   if (! XBAR_5644.SLAVE_PORT[XBAR_SLAVE_L2SRAM].SGPCR.F.RO)
   {
        //Master Priority Register for Slave port 3
      XBAR_5644.SLAVE_PORT[XBAR_SLAVE_L2SRAM].MPR       = mpr;
	 //General Purpose Control Register for Slave port 3
      XBAR_5644.SLAVE_PORT[XBAR_SLAVE_L2SRAM].SGPCR     = sgpcr;
   }

   //XBAR_SLAVE_P_BRIDGE_B
   if (! XBAR_5644.SLAVE_PORT[XBAR_SLAVE_P_BRIDGE_B].SGPCR.F.RO)
   {
      //Master Priority Register for Slave port 7
      XBAR_5644.SLAVE_PORT[XBAR_SLAVE_P_BRIDGE_B].MPR   = mpr;
     //General Purpose Control Register for Slave port 7
      XBAR_5644.SLAVE_PORT[XBAR_SLAVE_P_BRIDGE_B].SGPCR = sgpcr;
   }


}




//=============================================================================
// header files
//=============================================================================
#include "hw_fmpll.h"
#include "dd_fmpll.h"
#include "io_config_fmpll.h"

//=============================================================================
// Local object definitions
//=============================================================================
#define SECTION_FMPLL_REGISTER
#include "section.h"
FMPLL_T FMPLL;
#define SECTION_END
#include "section.h"

//=============================================================================
// Global object definitions
//=============================================================================
//
// Function external to this module. This is the prototype of a function that
//  exists in an assembly language module that is called from within here to
//  to initialize the FM PLL.
//   FMPLL will be initialized and the system clock may be different than when
//    this function was called. The system clock may be FM as well.
//
//=============================================================================



//=============================================================================
// FMPLL_Initialize_Device
//=============================================================================
void FMPLL_Initialize_Device(void )
{

   FMPLL_ESYNCR1_T   ecr1_temp;
   FMPLL_ESYNCR2_T   ecr2_temp;
   FMPLL_SYNFMMR_T mod_control_temp;

   ecr1_temp.U32 = FMPLL.ESYNCR1.U32;
   ecr2_temp.U32 = FMPLL.ESYNCR2.U32;

   //=============================================================================
   // 1b) Clear FMPLL_SYNCR2[LOLRE]. If this bit is set, the MCU will go into reset
   // when MFD is written.
   //=============================================================================
   ecr2_temp.F.LOLRE  = 0;

   //=============================================================================
   // 1c) Clear FMPLL_SYNCR2[LOLIRQ].
   //=============================================================================
   ecr2_temp.F.LOLIRQ = 0;

   FMPLL.ESYNCR2.U32 = ecr2_temp.U32;

   //=============================================================================
   // 1d) Select the Enhanced operation mode
   //=============================================================================
   ecr1_temp.F.EMODE = 1;
  

    //=============================================================================
   // 1f) Write FMPLL_SYNCR1[EPREDIV] for the desired final value.
   //=============================================================================
   ecr1_temp.F.EPREDIV = FMPLL_EPREDIV_VALUE; 
   
   //=============================================================================
   // 1h) Write FMPLL_SYNCR1[EMFD] for the desired final value.
   //=============================================================================
   ecr1_temp.F.EMFD =FMPLL_EMFD_VALUE;
   
    FMPLL.ESYNCR1.U32 = ecr1_temp.U32;

   //=============================================================================
   // 1g) Write the ERFD control field for desired final RFD value.
   //=============================================================================
   ecr2_temp.F.ERFD =FMPLL_ERFD_VALUE;
   
   FMPLL.ESYNCR2.U32 = ecr2_temp.U32;


   //=============================================================================
   // 2) Wait for Lock
   // To ensure proper operation across all MPC5500 MCUs, execute an mbar or
   // msync instruction between the write to change the FMPLL_SYNCR[MFD]
   // and the read to check the lock status shown by FMPLL_SYNSR[LOCK].
   // Furthermore, buffering writes to the FMPLL, as controlled by
   // PBRIDGE_A_OPACR[BW0], must be disabled.
   //=============================================================================

   __asm("     msync");

   while (!FMPLL.SYNSR.F.LOCK) {}

   //=============================================================================
   // 3) Enable FM by Programing the MODSEL, MODPERIOD and INCSTEP fields of the SYNFMMR.
   //=============================================================================
   mod_control_temp.F.MODSEL = FMPLL_MODULATION_CENTERED_AROUND_NORMAL_FREQ;
   mod_control_temp.F.MODPERIOD = FMPLL_MODULATION_PERIOD;
   mod_control_temp.F.INCSTEP =FMPLL_INCREMENT_STEP;

   FMPLL.SYNFMMR.U32 = mod_control_temp.U32;

      //=============================================================================
      // 4) Poll the BSY bit of the SYNFMMR until it negates..
      //=============================================================================
   while (FMPLL.SYNFMMR.F.BSY== 1) {}

         //=============================================================================
      // 5) Assert the MODEN bit of the SYNFMMR
      //=============================================================================
   FMPLL.SYNFMMR.F.MODEN = 1;


   //=============================================================================
   // 7) Engage normal mode by writing to the CLKCFG field of ESYNCR1.
   //=============================================================================
   ecr1_temp.F.CLKCFG = FMPLL_CLKCFG_VALUE;
   FMPLL.ESYNCR1.U32 = ecr1_temp.U32;

      //=============================================================================
   // 2) Wait for Lock
   // To ensure proper operation across all MPC5500 MCUs, execute an mbar or
   // msync instruction between the write to change the FMPLL_SYNCR[MFD]
   // and the read to check the lock status shown by FMPLL_SYNSR[LOCK].
   // Furthermore, buffering writes to the FMPLL, as controlled by
   // PBRIDGE_A_OPACR[BW0], must be disabled.
   //=============================================================================

   __asm("     msync");

   while (!FMPLL.SYNSR.F.LOCK) {}


   //=============================================================================
   // 8) Done, so write LOLIRQ, LOLRE, etc.
   //=============================================================================
   ecr2_temp.F.LOCEN   = 0;
   ecr2_temp.F.LOLRE   =  0;
   ecr2_temp.F.LOCRE   = 0;
   ecr2_temp.F.LOLIRQ  = 0;
   ecr2_temp.F.LOCIRQ  = 0;

   FMPLL.ESYNCR2.U32  = ecr2_temp.U32;


}




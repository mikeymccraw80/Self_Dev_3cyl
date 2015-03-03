
#include "dd_swt.h"

//=============================================================================
// Register overlay of the submodule
//=============================================================================
#define SECTION_SWT_REGISTER
#include "section.h"
SWT_T SWT;
#define SECTION_END
#include "section.h"

//==========================================================================
// Local object-like(name and constant) macros
//==========================================================================
#define SWT_LOCK_MASK            (0x00000030UL)
#define SWT_UNLOCK_SEQ_A         (0xC520)
#define SWT_UNLOCK_SEQ_B         (0xD928)
#define SWT_SERVICE_KEY_A        (0xA602UL)
#define SWT_SERVICE_KEY_B        (0xB480UL)
#define SWT_LOCK_STATE_SHIFT     (4UL)

//SKn+1 = (17*SKn+3) mod 2^16  is the formula used
#define SWT_Get_PseudoRandom_Key(key)  (((17UL*(key))+3UL) % 0x00010000UL)

//=============================================================================
// SWT_Get_Lock_Status
//=============================================================================
INLINE SWT_Lock_Status_T SWT_Get_Lock_Status(void)
{
   SWT_Lock_Status_T lock_status;
   SWT_Lock_Status_T temp_lock;

   temp_lock = (SWT_Lock_Status_T)((SWT.SWT_MCR.U32 & SWT_LOCK_MASK) >> SWT_LOCK_STATE_SHIFT);

   if((temp_lock == SWT_BOTH_LOCK) ||(temp_lock == SWT_HARD_LOCK) )
   {
      lock_status = SWT_HARD_LOCK;
   }
   else if(temp_lock == SWT_SOFT_LOCK)
   {
      lock_status = SWT_SOFT_LOCK;
   }
   else 
   {
      lock_status = SWT_NO_LOCK;
   }

   return (lock_status);
}


//=============================================================================
// SWT_Set_Lock_Status
//=============================================================================
static void SWT_Set_Reset_Lock(SWT_Lock_T lock_key)
{
   SWT_MCR_T temp_MCR;                        // local varible created as register is not bit accessible
   temp_MCR.U32 = SWT.SWT_MCR.U32;
   if (!(temp_MCR.F.HLK))                    // exit on hard lock
   {
      switch (lock_key)
      {
      case (SWT_SET_SOFT_LOCK):
         if(!(temp_MCR.F.SLK))
         {
            temp_MCR.F.SLK = 1;
            SWT.SWT_MCR.U32 = temp_MCR.U32;             // SWT is Soft locked
         }
      break;

      case (SWT_RESET_SOFT_LOCK):
         if((temp_MCR.F.SLK == 1))
         {
            SWT.SWT_SR.U32 = SWT_UNLOCK_SEQ_A;
            SWT.SWT_SR.U32 = SWT_UNLOCK_SEQ_B;       //SWT is unlocked
         }
      break;

      case (SWT_SET_HARD_LOCK):
         if((temp_MCR.F.SLK == 1))
         {
            SWT.SWT_SR.U32 = SWT_UNLOCK_SEQ_A;
            SWT.SWT_SR.U32 = SWT_UNLOCK_SEQ_B;       //unlock soft lock
         }
         temp_MCR.F.HLK  = 1;
         SWT.SWT_MCR.U32 = temp_MCR.U32;               // SWT is hard locked
      break;

      default:
      break;
     }
   }
}

//=============================================================================
// SWT_Initialize_Device
//=============================================================================
void SWT_Set_Timeout_Value(uint32_t in_time)
{
	SWT_MCR_T temp_MCR;

	if (!(SWT.SWT_MCR.F.HLK)) //exit on hard lock
	{
		if (SWT.SWT_MCR.F.SLK == SWT_SOFT_LOCK_ENABLE) {
			SWT.SWT_SR.U32 = SWT_UNLOCK_SEQ_A;
			SWT.SWT_SR.U32 = SWT_UNLOCK_SEQ_B; //SWT is unlocked
		}

		SWT.SWT_MCR.F.WEN = SWT_DISABLE;
		temp_MCR.U32 = SWT.SWT_MCR.U32;
		temp_MCR.F.KEY = SWT_FIXED_SERVICE_MODE; //Keyed Service Mode, two pseudorandom key values are used to service the watchdog
		SWT.SWT_TO = in_time; //timeout_value updated  here
		temp_MCR.F.SLK = SWT_SOFT_LOCK_ENABLE; //SWT_CR, SWT_TO, SWT_WN and SWT_SK are read-only registers
		temp_MCR.F.CSL = SWT_OSCILLATOR_CLOCK;
		temp_MCR.F.WEN = SWT_ENABLE;
		SWT.SWT_MCR.U32 = temp_MCR.U32;
	}
}

//=============================================================================
// SWT_Service_WatchDog
//=============================================================================

void SWT_Service_WatchDog(void)
{
	uint32_t SWT_KEY_Val;
	uint32_t SWT_SR_Val1;
	uint32_t SWT_SR_Val2;
	// uint32_t cs;

	/* check for fixed or random service mode */
	if (SWT.SWT_MCR.F.KEY == SWT_KEYED_SERVICE_MODE) {
		// cs = Enter_Critical_Section();

		// Read Key Value
		SWT_KEY_Val = SWT.SWT_SK.U32;

		// Generate Keys
		SWT_SR_Val1 = SWT_Get_PseudoRandom_Key(SWT_KEY_Val);
		SWT_SR_Val2 = SWT_Get_PseudoRandom_Key(SWT_SR_Val1);

		// Service Watchdog
		SWT.SWT_SR.U32 = SWT_SR_Val1;
		SWT.SWT_SR.U32 = SWT_SR_Val2;

		// Leave_Critical_Section(cs);
	} else {
		SWT.SWT_SR.U32 = SWT_SERVICE_KEY_A;
		SWT.SWT_SR.U32 = SWT_SERVICE_KEY_B;
	}
}

//=============================================================================
// SWT_Enable_WatchDog
//=============================================================================
void SWT_Enable_WatchDog(bool state)
{
	SWT_MCR_T temp_MCR;
	SWT_Lock_Status_T lock_status;
	lock_status = SWT_Get_Lock_Status();
	if(lock_status != SWT_HARD_LOCK )                    //exit on Hard lock
	{
		if(lock_status == SWT_SOFT_LOCK )
		{
			SWT_Set_Reset_Lock(SWT_RESET_SOFT_LOCK);       // unlock  on soft lock
		}
		temp_MCR.U32 = SWT.SWT_MCR.U32;
		temp_MCR.F.WEN = state;                              //Enable the SWT only when no hard lock and no soft lock
		SWT.SWT_MCR.U32 = temp_MCR.U32;
	}
}



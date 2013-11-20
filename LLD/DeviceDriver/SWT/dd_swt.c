
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
#define SWT_UNLOCK_SEQ_A         (0xC520)
#define SWT_UNLOCK_SEQ_B         (0xD928)
#define SWT_SERVICE_KEY_A        (0xA602UL)
#define SWT_SERVICE_KEY_B        (0xB480UL)
#define SWT_LOCK_STATE_SHIFT     (4UL)

//SKn+1 = (17*SKn+3) mod 2^16  is the formula used
#define SWT_Get_PseudoRandom_Key(key)  (((17UL*(key))+3UL) % 0x00010000UL)


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





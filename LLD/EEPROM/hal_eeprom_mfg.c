
#include "reuse.h"
#include "hls.h"
#include "filenvmd.h"

#define  VehicleIdentificationNumberSize (17)

uint32_t rolling_counter_mfg;

//=============================================================================
// MFG_InitEepromWithHLS
//=============================================================================
void MFG_InitEepromWithHLS(void)
{
	unsigned char idx;
	for ( idx = 0 ; idx < VehicleIdentificationNumberSize ; idx++ ) {
		scnVehInfo.VIN[idx]= NsFILE_NVM_EE_ManufactData.VaFILE_EE_VIN[idx];
	}
}


#include "reuse.h"
#include "hls.h"
#include "filenvmd.h"

#define  VehicleIdentificationNumberSize (17)
#define  ReservedForCustomer_Size        (40)

uint32_t rolling_counter_mfg;

//=============================================================================
// MFG_InitEepromToHLS
//=============================================================================
void MFG_InitEepromToHLS(void)
{
	unsigned char idx;
	FCMTabEntry * p;

	for ( idx = 0 ; idx < VehicleIdentificationNumberSize ; idx++ ) {
		scnVehInfo.VIN[idx]= NsFILE_NVM_EE_ManufactData.VaFILE_EE_VIN[idx];
	}

	for (idx = 0; idx < SY_FCMTSIZE; idx ++) {
		p = (FCMTabEntry *)NsFILE_NVM_EE_ManufactData.VaFILE_EE_ReservedForCustomer;
		FCMTab[idx] = *p;
		p ++;
	}
}

//=============================================================================
// MFG_UpdateEepromFromHLS
//=============================================================================
void MFG_UpdateEepromFromHLS(void)
{
	unsigned char idx;
	FCMTabEntry * p;

	for (idx = 0; idx < SY_FCMTSIZE; idx ++) {
		p = (FCMTabEntry *)NsFILE_NVM_EE_ManufactData.VaFILE_EE_ReservedForCustomer;
		*p = FCMTab[idx];
		p ++;
	}
}

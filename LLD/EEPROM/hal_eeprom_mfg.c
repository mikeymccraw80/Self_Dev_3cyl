
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
	uint8_t * p;

	for ( idx = 0 ; idx < VehicleIdentificationNumberSize ; idx++ ) {
		scnVehInfo.VIN[idx]= NsFILE_NVM_EE_ManufactData.VaFILE_EE_VIN[idx];
	}

	for (idx = 0; idx < HLS_DataStoreEEP_SIZE; idx ++) {
		p = (uint8_t *)NsFILE_NVM_EE_ManufactData.VaFILE_EE_ReservedForCustomer;
		HLS_DataStoreEEP[idx] = *p;
		p ++;
	}
}

//=============================================================================
// MFG_UpdateEepromFromHLS
//=============================================================================
void MFG_UpdateEepromFromHLS(void)
{
	unsigned char idx;
	uint8_t * p;

	for (idx = 0; idx < HLS_DataStoreEEP_SIZE; idx ++) {
		p = (uint8_t *)NsFILE_NVM_EE_ManufactData.VaFILE_EE_ReservedForCustomer;
		*p = HLS_DataStoreEEP[idx];
		p ++;
	}
}

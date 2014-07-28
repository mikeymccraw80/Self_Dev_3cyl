/*  Include Header Files */
#include "dd_sswt.h"
#include "reuse.h"
#include "hw_sprs_cu.h"
#include "e200z3.h"
#include "io_config_fmpll.h"


#define WDT_INIT_TIMEOUT_MSEC ((uint32_t)1000)
/* The division by 2 in the following macro is due to the fact that the WDG reset */
/* occures on the 2nd time the timeout time is reached. This implies that the     */
/* WDG needs to be kicked more than twice per period.                             */
#define WDT_RESCALED_TOUT(x) (uint32_t)((SYSTEM_FREQUENCY_HZ/(2*1000))*x)

static uint32_t hwi_wdg_timeout;
bool  hwi_wdg_disabled=false;

/******************************************************************************/
/* Function   : hwi_wdg_cfg_timeout                                           */
/* Description: start up the CPU watchdog when called for the first time      */
/*              It is assumed that the timeout value will not exceed          */
/*              the timer period * 2**32 (33 sec)                             */
/******************************************************************************/

static void hwi_wdg_cfg_timeout(uint32_t timeout)
{
	union SPR_TCRVAL tcr_temp;
	uint32_t   tempval;
	uint16_t   wdt_timeout_pos = 33; /* position in 64 bit timer, MSb is 0 */
	uint32_t   mask=0x80000000;

	/* Backup timeout value */
	hwi_wdg_timeout = timeout;

	/* Configure time out */
	/* Rem: the timeout period goes in multiple of power of two of the RT clock */
	tempval = WDT_RESCALED_TOUT(timeout);

	/* The API specifies that the closest possible timeout is to be used.   */
	/* The algo is to add half of the MSb to force a roll over if the value */
	/* is higher than MSb+(Msb/2) and process that new value                */
	while (mask > tempval) {
		mask /=2;
		wdt_timeout_pos++;
	}
	tempval = tempval + mask/2;
	mask *= 2;
	if (mask> tempval) {
		wdt_timeout_pos++;
	}


	tcr_temp.R = READ_SPR_VALUE(SPR_TCR);
	tcr_temp.B.WP = wdt_timeout_pos & 3;
	tcr_temp.B.WPEXT = (wdt_timeout_pos >> 2) & 0xf;
	STORE_SPR_VALUE (SPR_TCR, tcr_temp.R);
}


/******************************************************************************/
/* Function   : hwi_init_watchdog                                             */
/* Description: start up the CPU watchdog when called for the first time      */
/******************************************************************************/

void hwi_init_watchdog(HWI_WATCHDOG_STATUS p_l_watchdog_status)
{
	union SPR_TCRVAL tcr_temp;
	union SPR_TSRVAL tsr_temp;

	uint32_t msr_value;

	/* Initialise Machine State Exceptions */
	msr_value = READ_MSR_VALUE();
	msr_value |= MSR_CE_CHECK_ENABLE;
	STORE_MSR_VALUE(msr_value);

	tcr_temp.R = READ_SPR_VALUE(SPR_TCR);

	switch(p_l_watchdog_status) {
	case HWI_WATCHDOG_ENABLE: {
		/* configure time out period */
		hwi_wdg_cfg_timeout(WDT_INIT_TIMEOUT_MSEC);

		/* To service the watchdog, reset the SPR_TSR.WIS flag before the timeout period expires */
		tsr_temp.R = READ_SPR_VALUE(SPR_TSR);
		tsr_temp.B.WIS = 1;
		STORE_SPR_VALUE (SPR_TSR, tsr_temp.R);

		/* Assert processor reset output */
		/* REM: once set to a non 0 value, WRC cannot be changed */
		tcr_temp.R = READ_SPR_VALUE(SPR_TCR);
		tcr_temp.B.WRC = 0;
		tcr_temp.B.WIE = 1;
		STORE_SPR_VALUE (SPR_TCR, tcr_temp.R);

		break;
	}

	case HWI_WATCHDOG_DISABLE:
	default: {
		hwi_wdg_disabled=true;
		tcr_temp.R = READ_SPR_VALUE(SPR_TCR);
		/* disable WDG action */
		tcr_temp.B.WRC = 0;
		STORE_SPR_VALUE (SPR_TCR, tcr_temp.R);
		break;
	}
	}
}

/******************************************************************************/
/* Function   : hwi_kick_watchdog_position                                    */
/* Description: service the CPU internal watchdog and reconfigure the period  */
/*              when needed.                                                  */
/******************************************************************************/

void hwi_kick_watchdog_position(uint8_t position)
{
	union SPR_TCRVAL tcr_temp;

	/* directly set the watchdog exception position */
	tcr_temp.R = READ_SPR_VALUE(SPR_TCR);
	tcr_temp.B.WP = position & 3;
	tcr_temp.B.WPEXT = (position >> 2) & 0xf;
	STORE_SPR_VALUE (SPR_TCR, tcr_temp.R);

	if (hwi_wdg_disabled == false) {
		/* Assert processor reset output */
		/* REM: once set to a non 0 value, WRC cannot be changed */
		tcr_temp.R = READ_SPR_VALUE(SPR_TCR);
		tcr_temp.B.WRC = 1;
		tcr_temp.B.WIE = 1;
		STORE_SPR_VALUE (SPR_TCR, tcr_temp.R);
	}
}

/******************************************************************************/
/* Function   : hwi_kick_watchdog                                             */
/* Description: service the CPU internal watchdog and reconfigure the period  */
/*              when needed.                                                  */
/******************************************************************************/

void hwi_kick_watchdog(uint32_t timeout)
{
	union SPR_TSRVAL tsr_temp;
	union SPR_TCRVAL tcr_temp;

	/* To service the watchdog, reset the SPR_TSR.WIS flag before the timeout period expires */
	tsr_temp.R = READ_SPR_VALUE(SPR_TSR);
	tsr_temp.B.WIS = 1;
	STORE_SPR_VALUE (SPR_TSR, tsr_temp.R);

	if (timeout != hwi_wdg_timeout) {
		/* configure time out period */
		hwi_wdg_cfg_timeout(timeout);
		if (hwi_wdg_disabled == false) {
			/* Assert processor reset output */
			/* REM: once set to a non 0 value, WRC cannot be changed */
			tcr_temp.R = READ_SPR_VALUE(SPR_TCR);
			// tcr_temp.B.WRC = 2;
			tcr_temp.B.WRC = 1;
			tcr_temp.B.WIE = 1;
			STORE_SPR_VALUE (SPR_TCR, tcr_temp.R);
		}
	}
}


/******************************************************************************/
/* Function   : hwi_kick_watchdog                                             */
/* Description: service the CPU internal watchdog without reconfiguring the   */
/*              timeout period.                                               */
/******************************************************************************/

void hwi_kick_wdg_local(void)
{
	union SPR_TSRVAL tsr_temp;

	/* To service the watchdog, reset the SPR_TSR.WIS flag before the timeout period expires */
	tsr_temp.R = READ_SPR_VALUE(SPR_TSR);
	tsr_temp.B.WIS = 1;
	STORE_SPR_VALUE (SPR_TSR, tsr_temp.R);
}

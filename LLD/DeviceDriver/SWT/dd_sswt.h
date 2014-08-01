#ifndef DD_SSWT_H
#define DD_SSWT_H

#include "reuse.h"


/****************************************************************************/
/*                   CPU REGISTERS: TIMERS                                  */
/****************************************************************************/

union SPR_TBLVAL {
	volatile uint32_t R;
	struct {
		volatile uint32_t TBLVALUE:32;
	} B;
};

union SPR_TBUVAL {
	volatile uint32_t R;
	struct {
		volatile uint32_t TBUVALUE:32;
	} B;
};

union SPR_TCRVAL {
	volatile uint32_t R;
	struct {
		volatile uint32_t WP:2;
		volatile uint32_t WRC:2;
		volatile uint32_t WIE:1;
		volatile uint32_t DIE:1;
		volatile uint32_t FP:2;
		volatile uint32_t FIE:1;
		volatile uint32_t ARE:1;
		volatile uint32_t :1;
		volatile uint32_t WPEXT:4;
		volatile uint32_t FPEXT:4;
		volatile uint32_t :13;
	} B;
};

union SPR_TSRVAL {
	volatile uint32_t R;
	struct {
		volatile uint32_t ENW:1;
		volatile uint32_t WIS:1;
		volatile uint32_t WRS:2;
		volatile uint32_t DIS:1;
		volatile uint32_t FIS:1;
		volatile uint32_t :26;
	} B;
};


union SPR_DECVAL {
	volatile uint32_t R;
	struct {
		volatile uint32_t DECVALUE:32;
	} B;
};

union SPR_DECARVAL {
	volatile uint32_t R;
	struct {
		volatile uint32_t DECARVALUE:32;
	} B;
};


#define SPR_TCR       340
#define SPR_TSR       336


/* CPU Watchdog */
typedef enum {
	HWI_WATCHDOG_DISABLE,
	HWI_WATCHDOG_ENABLE
} HWI_WATCHDOG_STATUS;

/* Machine check register definition */
#define MSR_CRITICAL_ENABLE       (0x20000U)
#define MSR_EXTERNAL_ENABLE       (0x8000U)
#define MSR_FLOATING_POINT_ENABLE (0x2000U)
#define MSR_MACHINE_CHECK_ENABLE  (0x1000U)
#define MSR_CE_CHECK_ENABLE       (0x20000U)

#define SSWT_EXPIRATION_TIME_13MS  (44) //2 ** 20,
#define SSWT_EXPIRATION_TIME_26MS  (43) //2 ** 21,
#define SSWT_EXPIRATION_TIME_52MS  (42) //2 ** 22,
#define SSWT_EXPIRATION_TIME_104MS (41) //2 ** 23,


void hwi_kick_wdg_local(void);
void hwi_kick_watchdog(uint32_t timeout);
void hwi_kick_watchdog_position(uint8_t position);
void hwi_init_watchdog(HWI_WATCHDOG_STATUS p_l_watchdog_status);

#endif // DD_SWT_H


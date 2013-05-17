#ifndef DD_SCI_INTERFACE_H
#define DD_SCI_INTERFACE_H
//=============================================================================
//                                                                           *
//                COPYRIGHT, 2001, DELPHI Technologies, Inc                  *
//                                                                           *
//===========================================================================*

#include "io_type.h"

typedef struct SCI_Interface_Tag {
	/* basic functions */
	int (*init)(void);
	int (*read)(void);
	int (*write)(int ch);
	int (*poll)(void); //return how many chars left in the rx buffer
	int (*reset)(void); // recover from err status

	/* get error status flag */
	int (*GetAllErrFlag)(void);
	int (*GetFrmErrFlag)(void);
	int (*GetActiveFlag)(void);

	/* interupt call back */
	void (*RxInt)(void);
	void (*RxIntDisable)(void);
	void (*RxIntEnable)(void);
	void (*TxCPInt)(void);
} sci_bus_t;

extern const sci_bus_t scia;
extern const sci_bus_t scib;




#endif // COMMPORT_H


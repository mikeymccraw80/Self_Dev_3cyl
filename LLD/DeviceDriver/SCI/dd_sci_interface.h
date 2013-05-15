#ifndef DD_SCI_INTERFACE_H
#define DD_SCI_INTERFACE_H
//=============================================================================
//                                                                           *
//                COPYRIGHT, 2001, DELPHI Technologies, Inc                  *
//                                                                           *
//===========================================================================*

#include "io_type.h"

typedef struct SCI_Interface_Tag {
	int (*init)(void);
	int (*read)(void);
	int (*write)(int ch);
	int (*poll)(void); //return how many chars left in the rx buffer
	/* interupt call back */
	void (*RxInt)(void);
	void (*TxCPInt)(void);
} sci_bus_t;

extern const sci_bus_t scia;
extern const sci_bus_t scib;




#endif // COMMPORT_H


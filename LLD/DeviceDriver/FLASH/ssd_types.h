/*****************************************************************
* PROJECT : Standard Software Driver (SSD) for M10ST based devices
* FILE    : ssd_types.h
*
* DESCRIPTION : Type definition for SSD
*
* COPYRIGHT :(c) 2008, Freescale & STMicroelectronics
*
* VERSION   : EAR 0.2
* DATE      : 04.18.2008
* AUTHOR    : ...
*
* HISTORY :
* 2007.12.07    Arvind Awasthi    Initial Version
* 2008.04.18    Leonardo Colombo  Changed header in agreement with JDP SW
*                                 template
******************************************************************/

#ifndef _C90FL_TYPES_H_
#define _C90FL_TYPES_H_

/*************************************************************************/
/*  SSD general data types                                               */
/*************************************************************************/

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE (!FALSE)
#endif

typedef unsigned char BOOL;

typedef signed char INT8;
typedef unsigned char UINT8;
typedef volatile signed char VINT8;
typedef volatile unsigned char VUINT8;

typedef signed short INT16;
typedef unsigned short UINT16;
typedef volatile signed short VINT16;
typedef volatile unsigned short VUINT16;

typedef signed long INT32;
typedef unsigned long UINT32;
typedef volatile signed long VINT32;
typedef volatile unsigned long VUINT32;

typedef signed long long INT64;
typedef unsigned long long UINT64;
typedef volatile signed long long VINT64;
typedef volatile unsigned long long VUINT64;

#endif  /* _C90FL_TYPES_H_ */

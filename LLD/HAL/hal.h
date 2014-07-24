#ifndef HAL_H
#define HAL_H

#include "reuse.h"
#include "t_gentypes.h"

//=============================================================================
// define
//=============================================================================
typedef signed char        SHORTINT;
typedef unsigned char      BYTE;
typedef short signed int   INTEGER;
typedef short unsigned int WORD;
typedef long signed int    LONGINT;
typedef long unsigned int  LONGWORD;
typedef signed int         MEDINT;
typedef unsigned int       MEDWORD;

/* range: [0, 255] */
typedef BYTE               T_COUNT_BYTE;
#define V_COUNT_BYTE(val)  (BYTE)(val)         /* no scaling is needed       */
#define S_COUNT_BYTE       0                   /* Count is integral          */

/* power-of-two range: [0, 1024) */
typedef WORD             T_MILLISECONDSb;
#define V_MILLISECONDSb(val)    (WORD)((val)*64)
#define S_MILLISECONDSb         6

/* power-of-two range: [-256, 256) */
typedef INTEGER T_ANGLEa;
#define V_ANGLEa(val)  (INTEGER)((val)*128)
#define S_ANGLEa 7

/* power-of-two range: [0, 8192) */
typedef WORD T_RPMa;
#define V_RPMa(val)  (WORD)((val)*8)
#define S_RPMa 3

#endif 

#ifndef POWERPC_DIABDATA_TYPES_H
#define POWERPC_DIABDATA_TYPES_H

//=============================================================================
// Include Files
//=============================================================================

//=============================================================================
// Function Prototypes
//=============================================================================

//=============================================================================
//   Standard Types:
//=============================================================================
typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned long   uint32_t;
typedef unsigned long long uint64_t;

typedef signed char     int8_t;
typedef signed short    int16_t;
typedef signed long     int32_t;
typedef signed long long int64_t;

typedef uint8_t         bitfield8_t;
typedef uint16_t        bitfield16_t;
typedef uint32_t        bitfield32_t;

typedef uint8_t bool;
#define false (0)
#define true  (1)


typedef uint8_t            sig_atomic_t;
#define SIG_ATOMIC_SIZE    (8*sizeof(sig_atomic_t))
#define SIG_ATOMIC_MIN     UINT8_MIN
#define SIG_ATOMIC_MAX     UINT8_MAX

//=============================================================================
//   Standard Type Specifiers:
//=============================================================================
typedef enum
{
   CAN_PORT_ERROR_NONE,
   CAN_PORT_ERROR_BUSOFF,
   CAN_PORT_ERROR_BUSERROR
} CAN_Port_Error_T;

//=============================================================================
//   Interrupt Handling:
//=============================================================================
// interrupt state in condition codes register, which is 8 bits
typedef uint32_t interrupt_state_t;

typedef uint32_t Critical_Status_T;

//=============================================================================
// Stack Pointer
//=============================================================================
// stack pointer is a 16-bit register
typedef uint32_t stack_pointer_t;

#endif // POWERPC_DIABDATA_TYPES_H


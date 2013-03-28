#ifndef DD_PFI_H
#define DD_PFI_H

//=============================================================================
// Device Driver for Primitive
//=============================================================================
#include "dd_mcd5417.h"
#include "io_config_crank.h"

//=============================================================================
//   Type declarations
//=============================================================================
// @enum Pfi_Flag_T | Defines flag position in the 32 bit uint
typedef enum
{
   PFI_FLAG_FUEL_DELIVERY_MODE            =  0, // @emem only use for get and storage. use explicit func for set.
   PFI_FLAG_TRIM_PULSE_ENABLED            =  1, // @emem enable Multiple Trim pulses
   PFI_FLAG_UPDATE_ENABLED                =  2, // @emem 
   PFI_FLAG_PRIME_PULSE_COMPLETE          =  3  // @emem 

}  Pfi_Flag_T;



typedef enum Pfi_Fuel_Delivery_Mode_Tag
{
   PFI_FUEL_DELIVERY_SIMULTANEOUS,
   PFI_FUEL_DELIVERY_SEQUENTIAL

}  Pfi_Fuel_Delivery_Mode_T;

typedef enum Pfi_Angle_Tag
{
   PFI_ANGLE_NORMAL,
   PFI_ANGLE_TRIM

}  Pfi_Angle_T;

typedef enum
{
   PFI_NORMAL_ANGLE,
   PFI_TRIM_ANGLE

}  PFI_Angle_T;

typedef struct IO_PFI_Initialization_Parameters_Tag
{
   uCrank_Angle_T boundary_fraction;

}  IO_PFI_Initialization_Parameters_T;

typedef struct PFI_Flags_Tag
{
   bitfield32_t Update_Enabled         :  1;
   bitfield32_t Prime_Pulse_Complete   :  1;
   bitfield32_t                        : 30;

}  PFI_Flags_T;





#endif // DD_PFI_H

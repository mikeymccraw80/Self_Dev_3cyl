#ifndef DD_FMPLL_H
#define DD_FMPLL_H

#include "hw_fmpll.h"


//=============================================================================
// @globalv FMPLL_T | FMPLL |
// The Register Memory Overlay of the Frequency Modulated Phase Lock Loop
// to provide software access and debug information.
//
// @end
//=============================================================================
#define SECTION_FMPLL_REGISTER
#include "section.h"
extern FMPLL_T FMPLL;
#define SECTION_END
#include "section.h"


typedef enum
{
   FMPLL_MODULATION_CENTERED_AROUND_NORMAL_FREQ,
   FMPLL_MODULATION_CENTERED_BELOW_NORMAL_FREQ
}FMPLL_Modulation_Selection_T;


// @enum FMPLL_Configuration_Width_T | Defines width for extract and insertion of the channel configuration 
typedef enum
{
   FMPLL_CONFIGURATION_WIDTH_MODULATION_SELECTION           =  1, // @emem     0  Modulation selection
   FMPLL_CONFIGURATION_WIDTH_LOSS_OF_CLOCK_CIRCUIT_ENABLE   =  1, // @emem     1  Loss of Clock Circuit Enable
   FMPLL_CONFIGURATION_WIDTH_LOSS_OF_LOCK_RESET_ENABLE      =  1, // @emem     2  Loss of lock Reset Enable
   FMPLL_CONFIGURATION_WIDTH_LOSS_OF_CLOCK_RESET_ENABLE     =  1, // @emem     3  Loss of Clock Reset Enable
   FMPLL_CONFIGURATION_WIDTH_LOSS_OF_LOCK_IRQ_ENABLE        =  1, // @emem     4  Loss of lock Interrupt Request Enable
   FMPLL_CONFIGURATION_WIDTH_LOSS_OF_CLOCK_IRQ_ENABLE       =  1  // @emem     5  Loss of Clock Interrupt Request Enable
}  FMPLL_Configuration_Width_T;

// @enum FMPLL_Configuration_Position_T | Defines position for extract and insertion of the channel configuration
typedef enum
{
   FMPLL_CONFIGURATION_POSITION_MODULATION_SELECTION           = 0, // @emem   0  Modulation selection
   FMPLL_CONFIGURATION_POSITION_LOSS_OF_CLOCK_CIRCUIT_ENABLE   = 1, // @emem   1  Loss of Clock Circuit Enable
   FMPLL_CONFIGURATION_POSITION_LOSS_OF_LOCK_RESET_ENABLE      = 2, // @emem   2  Loss of lock Reset Enable
   FMPLL_CONFIGURATION_POSITION_LOSS_OF_CLOCK_RESET_ENABLE     = 3, // @emem   3  Loss of Clock Reset Enable
   FMPLL_CONFIGURATION_POSITION_LOSS_OF_LOCK_IRQ_ENABLE        = 4, // @emem   4  Loss of lock Interrupt Request Enable
   FMPLL_CONFIGURATION_POSITION_LOSS_OF_CLOCK_IRQ_ENABLE       = 5  // @emem   5  Loss of Clock Interrupt Request Enable
}  FMPLL_Configuration_Position_T;



typedef enum
{
   FMPLL_MODE_BYPASS_EXTERNAL_REF_PLL_OFF,
   FMPLL_MODE_BYPASS_CRYSTAL_REF_PLL_OFF,
   FMPLL_MODE_BYPASS_EXTERNAL_REF_PLL_ON,
   FMPLL_MODE_BYPASS_CRYSTAL_REF_PLL_ON,
   FMPLL_MODE_NORMAL_EXTERNAL_REF_PLL_ON = 6,
   FMPLL_MODE_NORMAL_CRYSTAL_REF_PLL_ON = 7
}FMPLL_Clock_Configuration_T;

typedef enum FMPLL_SYNCR_Prediv_Tag
{
   FMPLL_ESYNCR1_PREDIV_DIV_BY_1,      // @emem  0000   
   FMPLL_ESYNCR1_PREDIV_DIV_BY_2,      // @emem  0001   
   FMPLL_ESYNCR1_PREDIV_DIV_BY_3,      // @emem  0010   
   FMPLL_ESYNCR1_PREDIV_DIV_BY_4,      // @emem  0011   
   FMPLL_ESYNCR1_PREDIV_DIV_BY_5,      // @emem  0100   
   FMPLL_ESYNCR1_PREDIV_DIV_BY_6,      // @emem  0101   
   FMPLL_ESYNCR1_PREDIV_DIV_BY_7,      // @emem  0110   
   FMPLL_ESYNCR1_PREDIV_DIV_BY_8,      // @emem  0111   
   FMPLL_ESYNCR1_PREDIV_DIV_BY_9,      // @emem  1000   
   FMPLL_ESYNCR1_PREDIV_DIV_BY_10,     // @emem  1001   
   FMPLL_ESYNCR1_PREDIV_DIV_BY_11,     // @emem  1010   
   FMPLL_ESYNCR1_PREDIV_DIV_BY_12,     // @emem  1011   
   FMPLL_ESYNCR1_PREDIV_DIV_BY_13,     // @emem  1100   
   FMPLL_ESYNCR1_PREDIV_DIV_BY_14,     // @emem  1101   
   FMPLL_ESYNCR1_PREDIV_DIV_BY_15,     // @emem  1110   
   FMPLL_ESYNCR1_PREDIV_INVALID        // @emem  1111   

}  FMPLL_ESYNCR1_Prediv_T;

typedef enum
{
   FMPLL_ESYNCR2_ERFD_DIV_BY_2,
   FMPLL_ESYNCR2_ERFD_DIV_BY_4,
   FMPLL_ESYNCR2_ERFD_DIV_BY_8,
   FMPLL_ESYNCR2_ERFD_DIV_BY_16

}FMPLL_ESYNCR2_Reduced_Freq_Div_T;


//=============================================================================
// To ensure proper operation across all MPC5500 MCUs, execute an mbar or
// msync instruction between the write to change the
// FMPLL_SYNCR[MFD] and the read to check the lock status shown by
// FMPLL_SYNSR[LOCK].
// Furthermore, buffering writes to the FMPLL, as controlled by
// PBRIDGE_A_OPACR[BW0], must be disabled. Buffered Writes are disabled at reset.
//=============================================================================


#endif // DD_FMPLL_H


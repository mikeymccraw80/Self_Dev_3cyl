//=============================================================================
// Include file
//=============================================================================

#include "reuse.h"
#include "dd_siu_hwinfo.h"
#include "dd_flash_hwinfo.h"
#include "dd_swt_interface.h"
#include "dd_mmu_interface.h"
#include "dd_flash_interface.h"
#include "dd_xbar_interface.h"
#include "dd_flash_memory_interface.h"
#include "dd_intc_interface.h"
#include "dd_dma_interface.h"
#include "dd_mios_interface.h"
#include "dd_dspi_interface.h"
#include "dd_pit_interface.h"
#include "io_config_swt.h"
#include "io_config_dma.h"
#include "io_config_pit.h"
#include "io_config_eeprom.h"
#include "hal_emulated_eeprom.h"
#include "dd_l9958.h"
#include "dd_tle4471.h"
#include "dd_vsep_est_select.h"
#include "dd_stm_interface.h"
#include "hal_os.h"
#include "dd_sswt.h"
#include "hal_eeprom_mfg.h"
#include "cn_io_transfer.h"
#include "hal_analog.h"
#include "hal_gpio.h"
#include "hwiocald.h"

/* private variable define */
static bool BatteryRemoved;

/* global variable define */
CPU_Info_T CPU_Info;
FLASH_MODULE_T Flash_Info;
HWIO_Reset_Status_T Reset_Status;

/* global variable reference */
//The address of these variables are the size numbers because these variables are calculated by the linker
extern char HWIO_DATA_ROM_START[];
extern char HWIO_DATA_RAM_START[];
extern char HWIO_BSS_START[];
extern uint16_t HWIO_DATA_SIZE;
extern uint16_t HWIO_BSS_SIZE;

/* private function define */
void CPU_DIAB_Set_Data_Area_Pointers(void);
 
void CPU_DIAB_Copy_Table( void )
{
   /* move initialized data from ROM to RAM if defined at	*/
   /* different locations					*/
   if( &HWIO_DATA_ROM_START[0] != &HWIO_DATA_RAM_START[0] ) 
   {
       Copy_Longs((void*)&HWIO_DATA_ROM_START[0],&HWIO_DATA_RAM_START[0],(((uint16_t)(&HWIO_DATA_SIZE)+3)/4));
   }
   /* clear uninitialized data				*/
   if (&HWIO_BSS_SIZE) 
   {
   // bss zero has been done in dd_start.s 
   // Clear_Longs(&HWIO_BSS_START[0],(((uint16_t)(&HWIO_BSS_SIZE)+3)/4));
   }
}

//=============================================================================
// CPU_DIAB_Set_Data_Area_Pointers
//=============================================================================

asm void CPU_DIAB_Set_Data_Area_Pointers(void)
{
   ;--------------------------------------------
   ; Clear r0 to use in following instructions.
   ;--------------------------------------------
    addis    r0,0,0

    addis    r13,r0,__SDA_BASE_@ha  # Initialize r13 to sdata base
    addi     r13,r13,__SDA_BASE_@l  # (provided by linker).
}

//=============================================================================
// Initialize all hardware related registers.  It is assumed that
// the processor has just come out of reset.
//=============================================================================
void InitializeHardwareRegisters(void)
{
	bool flash_init_sucess;

	Reset_Status = SIU_RESET_Get_Status();

	FMPLL_Initialize_Device();

	// Set the watchdog timeout for 400ms during initialization
	SWT_Set_Timeout_Value(SWT_TIMEOUT_VALUE_INIT) ;
	SWT_Service_WatchDog();

	CPU_DIAB_Set_Data_Area_Pointers();
	CPU_DIAB_Copy_Table();

	CPU_Info =  SIU_Get_CPU_Information();
	Flash_Info = Get_FLASH_Driver_Mode();

	if(CPU_LCI == CPU_Info) {
		MPC5644_FLASH_Initialize_Normal();
		XBAR_MPC5644A_Initialize_Device();
	} else {
		MPC5634_FLASH_Initialize_Normal();
		XBAR_MPC5634M_Initialize_Device();
	}
	flash_init_sucess = flash_memory_interface->FLASH_Memory_Initial();

	SIU_Initialize_Device();
	SIU_GPIO_Initialize_Device();

	/* set tle4471 watchdog, , typical expire time is 50ms, min is 35ms */
	InitRamVariable_EnableLogMaxHWWDTime();
	SetHWIO_ServiceExtCOP_1Time();

	/* init the INTC */
	INTC_Initialize_Device();

	/* init STM device */
	STM_Initialize_Device();
	STM_Set_Timer_Enable(true);

	ECSM_Initialize_Device();

	Enable_MachineCheck(); // enable machine check exception to capture ECC

	DMA_Initialize_Device();
	DMA_Initialize_Channel(
	DMA_CHANNEL_QADC_FISR1_CFFF_1,
	DMA_QADC_CFFF_1_Source_Address,
	DMA_QADC_CFFF_1_Second_32Bit,
	DMA_QADC_CFFF_1_Third_32Bit,
	DMA_QADC_CFFF_1_Slast,
	DMA_QADC_CFFF_1_Dest_Address,
	DMA_QADC_CFFF_1_Sixth_32Bit,
	DMA_QADC_CFFF_1_Dlast,
	DMA_QADC_CFFF_1_Eighth_32Bit);

	DMA_Initialize_Channel(
	DMA_CHANNEL_QADC_FISR1_RFDF_1,
	DMA_QADC_RFDF_1_Source_Address,
	DMA_QADC_RFDF_1_Second_32Bit,
	DMA_QADC_RFDF_1_Third_32Bit,
	DMA_QADC_RFDF_1_Slast,
	DMA_QADC_RFDF_1_Dest_Address,
	DMA_QADC_RFDF_1_Sixth_32Bit,
	DMA_QADC_RFDF_1_Dlast,
	DMA_QADC_RFDF_1_Eighth_32Bit);

	DMA_Initialize_Channel(
	DMA_CHANNEL_QADC_FISR4_CFFF_4,
	DMA_QADC_CFFF_4_Source_Address,
	DMA_QADC_CFFF_4_Second_32Bit,
	DMA_QADC_CFFF_4_Third_32Bit,
	DMA_QADC_CFFF_4_Slast,
	DMA_QADC_CFFF_4_Dest_Address,
	DMA_QADC_CFFF_4_Sixth_32Bit,
	DMA_QADC_CFFF_4_Dlast,
	DMA_QADC_CFFF_4_Eighth_32Bit);

	DMA_Initialize_Channel(
	DMA_CHANNEL_QADC_FISR4_RFDF_4,
	DMA_QADC_RFDF_4_Source_Address,
	DMA_QADC_RFDF_4_Second_32Bit,
	DMA_QADC_RFDF_4_Third_32Bit,
	DMA_QADC_RFDF_4_Slast,
	DMA_QADC_RFDF_4_Dest_Address,
	DMA_QADC_RFDF_4_Sixth_32Bit,
	DMA_QADC_RFDF_4_Dlast,
	DMA_QADC_RFDF_4_Eighth_32Bit);

	/* init adc device and calibrate it */
	QADC_Initialize_Device();
	QADC_ANALOG_Calibrate_Converter(ADC_CONVERTER_0);
	QADC_ANALOG_Calibrate_Converter(ADC_CONVERTER_1);

	/* init pit device */
	PIT_Initialize_Device();

	/* init MIOS device */
	MIOS_Initialize_Device();

	/* EMIOS DMA Channel for SOH Module */
	DMA_Initialize_Channel(
	DMA_CHANNEL_MIOS_EMIOSFLAG_4,
	DMA_EMIOSFLAG_4_Source_Address,
	DMA_EMIOSFLAG_4_Second_32Bit,
	DMA_EMIOSFLAG_4_Third_32Bit,
	DMA_EMIOSFLAG_4_Slast,
	DMA_EMIOSFLAG_4_Dest_Address,
	DMA_EMIOSFLAG_4_Sixth_32Bit,
	DMA_EMIOSFLAG_4_Dlast,
	DMA_EMIOSFLAG_4_Eighth_32Bit);

	/* init DSPI B device */
	DSPI_B_Initialize_Device();
	DSPI_B_Enable_Transfer(true);

	/* init can device and ccp can id and channel */
	FlexCAN_A_Initialize_Device();
	CCP_Initialize();
	HAL_CAN_Initialize();

	/* init L9958 device */
	L9958_Device_Initialize();

	//Prepare Vsep clock
	IO_Pulse_VSEP_CLK_Enable();
	HAL_GPIO_SET_GEN_Enable(false);  // Enable FSE pin
	HAL_GPIO_SET_FSE_Enable(false);  // Enable the IOEN line to enable the IO pins
	VSEP_Initialize_Device();

	/* feed tle4471 watchdog */
	SetHWIO_ServiceExtCOP_1Time();
}

//=============================================================================
// Refreshes all the hardware related registers.
//=============================================================================
void RefreshHardwareRegisters(void)
{
}


//=============================================================================
// This procedure is the very last to be called after processor
// reset.  It is assumed that the scheduler will be the next to run.
//=============================================================================
void InitializeHardwareLast(void)
{
	EEPROM_Operation_Status_T op_Return;

	HAL_ResetDiag_Log_Parameters(Reset_Status, 0x41400);

	HAL_GPIO_DI_Active_Status_Init();
	if(!HAL_GPIO_GET_Reset_DIO_Status()) {
		BatteryRemoved =  true;
	} else {
		BatteryRemoved =  false; 
	}

	HAL_GPIO_Reset_DIO_Output_Confige(true);

	// only LCI will do the instrumentation operation
	if(CPU_LCI == CPU_Info) {
		// resotre cal backup to ram
		INST_Restore_Working_Page(Reset_Status);
	}
	HAL_GPIO_SET_Reset_DIO_Enable(true);

	EEPROM_Restore_Vehicle_NVRAM_Block(Reset_Status);
	if (HAL_OS_Get_PowerFail_Flag()) {
		EEPROM_Clear_Vehicle_NVRAM_Block();
		// power fail flag will be clear when nvram clear
		HAL_OS_Set_PowerFail_Flag(true);
	}
	op_Return = EEPROM_Restore_MFG_NVM_Block();  // restore Pfalsh MFG if it is valid
	INST_Initialize_Calibration_Pages();

	/* init vin for hls variable */
	MFG_InitEepromToHLS();

	/* read reset type, set power fail flag */
	// if ((Reset_Status.bits.Power_On_Reset == false) 
	  // && (Reset_Status.bits.External_Reset \
	   // || Reset_Status.bits.Watchdog_Reset \
	   // || Reset_Status.bits.SoftwareSystem_Reset \
	   // || Reset_Status.bits.SoftwareExternal_Reset \
	   // || Reset_Status.bits.CheckStop_Reset))
	// {
		// HAL_OS_Set_PowerFail_Flag(true);
	// }

	/* detect the running reset */
	if (Reset_Status.bits.Power_On_Reset == false) {
		HAL_OS_Set_RunningReset_Flag(true);
	}

	/* feed tle4471 watchdog */
	SetHWIO_ServiceExtCOP_1Time();

	/* enable QADC DMA time base scan after initialize DMA and QADC */
	DMA_Enable_Request(DMA_CHANNEL_QADC_FISR1_CFFF_1);
	DMA_Enable_Request(DMA_CHANNEL_QADC_FISR1_RFDF_1);
	DMA_Enable_Request(DMA_CHANNEL_QADC_FISR4_CFFF_4);
	DMA_Enable_Request(DMA_CHANNEL_QADC_FISR4_RFDF_4);
	/* set up PIT time 5us(ADC FIFO0), 20us(ADC FIFO4) to trigger the adc */
	PIT_TIMER_Set_Value(PIT_CHANNEL_1, PIT_LOAD_VALUE_20US);
	PIT_TIMER_Set_Value(PIT_CHANNEL_0, PIT_LOAD_VALUE_5US);
	PIT_TIMER_Set_Value( PIT_CHANNEL_RTI, RTI_LOAD_VALUE_1MS);
	STM_Timer_UDelay(1000);

	/* init tpu device, this part must placed behind nvram erase */
	TPU_Initialize_Device();
	// InitializeComplexIO();
	// FI_Initialize();

	/* feed tle4471 watchdog */
	SetHWIO_ServiceExtCOP_1Time();

	/* init the canobd schedule table */
	CAN_Reset_Init();
}


//=============================================================================
// Refreshes all the hardware related registers.
//=============================================================================
bool Get_BatteryRemove_Status(void)
{
	return BatteryRemoved;
}

//=============================================================================
// exit
//=============================================================================
void exit(void)
{
	// Set the watchdog timeout to 300ms for flash erase/program
	SWT_Set_Timeout_Value(SWT_TIMEOUT_VALUE_INIT) ;
	SWT_Service_WatchDog();

	// Set ppc core watchdog timer to 419ms
	hwi_kick_watchdog_position(SSWT_EXPIRATION_TIME_419MS);
	hwi_kick_wdg_local();

	EEPROM_Backup_MFG_NVM_Block( KbHWIO_EraseMFGafterMFGCorrupted );
	EEPROM_Backup_Vehicle_NVRAM_Block();

	// only LCI will do the instrumentation operation, backup cal 
	if(CPU_LCI == CPU_Info) {
		INST_Backup_Working_Page();
	}

	//Set TOD low now since all power down processing is complete
	HAL_GPIO_SET_TODO_Enable(false);

	INTC_EXCEPTION_Halt();
	// Wait in an infinite loop for the power supply to shutdown
	do {} while (true);
}

//=============================================================================
// Defination
//=============================================================================
#define VOLT(x)                                                 (x * 1000)
#define UNIT                                                    (65535 / 5000)
#define MANIFOLD_AIR_PRESSURE                                   (VOLT(0.5) * UNIT)
#define MANIFOLD_AIR_TEMPERATURE                                (VOLT(0.5) * UNIT)
#define ENGINE_COOLANT_TEMPERATURE                              (VOLT(4.5) * UNIT)
#define THROTTLE_POSITION_SENSOR1                               (VOLT(4.5) * UNIT)
#define THROTTLE_POSITION_SENSOR2                               (VOLT(4.5) * UNIT)

//=============================================================================
// This procedure is to check the illegal condition to brach into testability
// software
// The illegal condition should be defined in TSR as:
// 1. function test:
//    TPS1 > 4.5v
//    TPS2 > 4.5v
//    MAP  < 0.5v
//    MAT  < 0.5
//    CLT  > 4.5v
//    Break swith == 0v
//=============================================================================

bool InitializeIllegalConditionCheck(void)
{
   bool return_code = false;
   return_code = ( (HAL_Analog_Get_TPS1VI_Value() << 2) > THROTTLE_POSITION_SENSOR1 &&
                   (HAL_Analog_Get_TPS2VI_Value() << 2) > THROTTLE_POSITION_SENSOR2 &&
                   (HAL_Analog_Get_MAPVI_Value()  << 2) < MANIFOLD_AIR_PRESSURE &&
                   (HAL_Analog_Get_MATVI_Value()  << 2) < MANIFOLD_AIR_TEMPERATURE &&
                   (HAL_Analog_Get_CLTVI_Value()  << 2) > ENGINE_COOLANT_TEMPERATURE &&
                   (HAL_GPIO_GET_BRKSWDI_Status()) == false
                 )?true:false;
   return return_code;
}

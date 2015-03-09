
#ifndef HW_ETPU_UCODE_H
#define HW_ETPU_UCODE_H



/***************************************************************/
/* eTPU Microcode Channel PRAM Start Allocation Address Offset */
/***************************************************************/
#define ETPU_PRAM_START_OFFSET  ( 0x004C )

/**********************************/
/* extern MARKAB Microcode Image  */
/**********************************/
extern const unsigned long etpu_ucode_image [( 0x1000 )];

/*************************************************/
/* Start RQOMBE Primitive Definitions            */
/*************************************************/

/*************************************************/
/* RQOMBE Function Configuration Information     */
/*************************************************/

/* RQOMBE Function Mode [0] is not used */
/* RQOMBE Function Mode [1] is not used */


/*************************************************/
/* RQOMBE Host Service Request Definitions       */
/*************************************************/

#define RQOMBE_HSR_SHUTDOWN     ( 7 )
#define RQOMBE_HSR_REQUEST      ( 6 )
#define RQOMBE_HSR_INITIALIZE   ( 5 )

/************************************/
/* End RQOMBE Primitive Definitions */
/************************************/

/*************************************************/
/* Start RQOME Primitive Definitions             */
/*************************************************/

/*************************************************/
/* RQOME Function Configuration Information      */
/*************************************************/

/* RQOME Function Mode [0] */
/*    0 = Actual TCR1 event stored in TCR1 units */
/*    1 = Actual TCR1 event stored in TCR2 units */

/* RQOME Function Mode [1] */
/*    0 = Actual TCR2 event stored in TCR1 units */
/*    1 = Actual TCR2 event stored in TCR2 units */

#define RQOME_STORE_ACTUAL_TCR1 ( 0 )
#define RQOME_STORE_ACTUAL_TCR2 ( 1 )


/*************************************************/
/* RQOME Host Service Request Definitions        */
/*************************************************/

#define RQOME_HSR_SHUTDOWN     ( 7 )
#define RQOME_HSR_REQUEST      ( 6 )
#define RQOME_HSR_INITIALIZE   ( 5 )
#define RQOME_HSR_UPDATE       ( 4 )

/***********************************/
/* End RQOME Primitive Definitions */
/***********************************/


/************************************/
/* Start EPPE Primitive Definitions */
/************************************/

/********************************************/
/* EPPE Function Configuration Information */
/********************************************/
/* EPPE Function Mode [0] */
#define EPPE_TIMEBASE_TCR1  ( 0 )
#define EPPE_TIMEBASE_TCR2  ( 1 )

/* EPPE Function Mode [1] */
#define EPPE_CAM_NORMAL_MODE   ( 0 )
#define EPPE_CAM_BACKUP_MODE   ( 1 )

/* Critical Edge Definitions */
#define EPPE_CRIT_FALLING   ( 0 )
#define EPPE_CRIT_RISING    ( 1 )

/* Minimum Period Methods */
#define EPPE_HW_MIN_PERIOD  ( 1 )
#define EPPE_SW_MIN_PERIOD  ( 0 )

/* Gap Detect Methods */
#define EPPE_PERCENT_PERIOD ( 0 )
#define EPPE_1_X__Y_1       ( 1 )

/* TCR2 Options */
#define EPPE_TIME_MODE      ( 0x00 )
#define EPPE_ANGLE_HW       ( 0x01 )
#define EPPE_EDGE_COUNT     ( 0x02 )

/******************************************/
/* EPPE Host Service Request Definitions  */
/******************************************/
#define EPPE_HSR_SHUTDOWN     ( 7 )
#define EPPE_HSR_INIT         ( 5 )
#define EPPE_HSR_REQUEST_BKUP ( 4 )
#define EPPE_HSR_EXIT_BKUP    ( 3 )
#define EPPE_HSR_UPDATE       ( 2 )

/***********************************/
/* End EPPE Primitive Definitions */
/***********************************/


/*************************************************/
/* Start CAMe Primitive Definitions              */
/*************************************************/

/*************************************************/
/* CAMe Function Configuration Information       */
/*************************************************/

/* CAMe Function Mode [0] */
/*    0 = TCR1 time base  */
/*    1 = TCR2 time base  */
#define CAME_TCR1_TIMEBASE ( 0 )
#define CAME_TCR2_TIMEBASE ( 1 )

/* CAMe Function Mode [1] */
/*    0 = Replicated cam output mirrors input */
/*    1 = Replicated cam output inverts input */
#define CAME_OUT_MIRROR_IN ( 0 )
#define CAME_OUT_INVERT_IN ( 1 )

/*************************************************/
/* CAMe Host Service Request Definitions         */
/*************************************************/

#define CAME_HSR_SHUTDOWN       ( 7 )
#define CAME_HSR_INIT_CRIT_RISE ( 3 )
#define CAME_HSR_INIT_CRIT_FALL ( 5 )

/***********************************/
/* End CAMe Primitive Definitions  */
/***********************************/

/*************************************************/
/* Start PWMIE Primitive Definitions             */
/*************************************************/

/*************************************************/
/* PWMIE Function Configuration Information      */
/*************************************************/

/* PWMIE Function Mode [0] */
/*     0 = TCR1 time base  */
/*     1 = TCR2 time base  */
#define PWMIE_TIMEBASE_TCR1 ( 0 )
#define PWMIE_TIMEBASE_TCR2 ( 1 )

/* PWMIE Function Mode [1]       */
/*    0 = Falling edges critical */
/*    1 = Rising edges critical  */
#define PWMIE_FALLING_EDGE ( 0 )
#define PWMIE_RISING_EDGE  ( 1 )

/*************************************************/
/* PWMIE Host Service Request Definitions        */
/*************************************************/

#define PWMIE_HSR_SHUTDOWN   ( 7 )
#define PWMIE_HSR_INITIALIZE ( 5 )

/***********************************/
/* End PWMIE Primitive Definitions */
/***********************************/

/*************************************************/
/* Start SPWMe Primitive Definitions             */
/*************************************************/

/*************************************************/
/* SPWMe Function Configuration Information      */
/*************************************************/

/* SPWMe Function Mode [0] */
/*    0 = TCR1 time base  */
/*    1 = TCR2 time base  */
#define SPWME_TIMEBASE_TCR1 ( 0 )
#define SPWME_TIMEBASE_TCR2 ( 1 )

/* SPWMe Function Mode [1] */
/*    0 = active low polarity  */
/*    1 = active high polarity  */
#define SPWME_POLARITY_ACTIVE_LOW ( 0 )
#define SPWME_POLARITY_ACTIVE_HIGH ( 1 )

/*************************************************/
/* SPWMe Host Service Request Definitions        */
/*************************************************/

#define SPWME_HSR_SHUTDOWN  ( 7 )
#define SPWME_HSR_INIT ( 5 )
#define SPWME_HSR_UPDATE ( 1 )

/***********************************/
/* End SPWMe Primitive Definitions */
/***********************************/

/**************************************/
/* Start PWMOE Primitive Definitions  */
/**************************************/

/*************************************************/
/* PWMOE Function Configuration Information      */
/*************************************************/

/* PWMOE Function Mode [0] */
/*     0 = TCR1 time base  */
/*     1 = TCR2 time base  */
#define PWMOE_TIMEBASE_TCR1 ( 0 )
#define PWMOE_TIMEBASE_TCR2 ( 1 )

/* PWMOE Function Mode [1] */
/*     0 = Update type is immediate   */
/*     1 = Update type is synchronous */
#define PWMOE_IMMEDIATE_UPDATE   ( 0 )
#define PWMOE_SYNCHRONOUS_UPDATE ( 1 )

/*******************************************/
/* PWMOE Host Service Request Definitions  */
/*******************************************/

#define PWMOE_HSR_SHUTDOWN    ( 7 )
#define PWMOE_HSR_INIT        ( 5 )
#define PWMOE_HSR_OUTPUT_HIGH ( 3 )
#define PWMOE_HSR_OUTPUT_LOW  ( 2 )
#define PWMOE_HSR_UPDATE      ( 1 )

/***********************************/
/* End PWMOE Primitive Definitions */
/***********************************/

/***********************************/
/* Start FIE Primitive Definitions */
/***********************************/

/******************************************/
/* FIE Function Configuration Information */
/******************************************/
/* FIE Function Mode [0] */
#define FIE_FI_TIMEBASE_TCR1 ( 0 )
#define FIE_FI_TIMEBASE_TCR2 ( 1 )

/* FIE Function Mode [1] */
#define FIE_ET_TIMEBASE_TCR1 ( 0 )
#define FIE_ET_TIMEBASE_TCR2 ( 1 )

/****************************************/
/* FIE Host Service Request Definitions */
/****************************************/
#define FIE_HSR_SHUTDOWN            ( 7 )
#define FIE_HSR_INIT_RISING_EDGE    ( 6 )
#define FIE_HSR_INIT_FALLING_EDGE   ( 5 )
#define FIE_HSR_INIT_EITHER_EDGE    ( 4 )
#define FIE_HSR_REQUEST_EVENT_TIME  ( 3 )
#define FIE_HSR_UPDATE_EVENT_TIME   ( 2 )

/*********************************/
/* End FIE Primitive Definitions */
/*********************************/


/*************************************************/
/* Start ECE Primitive Definitions               */
/*************************************************/

/*************************************************/
/* ECE Function Configuration Information        */
/*************************************************/

/* ECE Function Mode [0]  */
/*    0 = Use TCR1    */
/*    1 = Use TCR2    */
#define ECE_TIMEBASE_TCR1 ( 0 )
#define ECE_TIMEBASE_TCR2 ( 1 )

/* ECE Function Mode [1] */
/*    0 = One-shot mode    */
/*    1 = Continuous mode  */
#define ECE_MODE_ONESHOT    ( 0 )
#define ECE_MODE_CONTINUOUS ( 1 )

/*************************************************/
/* ECE Host Service Request Definitions          */
/*************************************************/

#define ECE_HSR_SHUTDOWN   ( 7 )
#define ECE_HSR_INITIALIZE ( 5 )

/***********************************/
/* End ECE Primitive Definitions   */
/***********************************/

/*************************************************/
/* Start VSSBe Primitive Definitions             */
/*************************************************/

/*************************************************/
/* VSSBe Function Configuration Information      */
/*************************************************/

/* VSSBe Function Mode [0]       */
/*    0 = TCR1 time base         */
/*    1 = TCR2 time base         */
#define VSSBE_TCR1_TIMEBASE ( 0 )
#define VSSBE_TCR2_TIMEBASE ( 1 ) 

/* VSSBe Function Mode [1]       */
/*    0 = identify low freq chan */
/*    1 = identify hi freq chan  */
#define VSSBE_LO_SPD_ID ( 0 )
#define VSSBE_HI_SPD_ID ( 1 ) 

/*************************************************/
/* VSSBe Host Service Request Definitions        */
/*************************************************/

#define VSSBE_HSR_SHUTDOWN  ( 7 )
#define VSSBE_HSR_INIT      ( 5 )    

/*************************************************/
/* End VSSBe Primitive Definitions               */
/*************************************************/

/*************************************/
/* Start ICPCE Primitive Definitions */
/*************************************/

/********************************************/
/* ICPCE Function Configuration Information */
/********************************************/
/* ICPCE Function Mode [0] */
#define ICPCE_TIMEBASE_TCR1 ( 0 )
#define ICPCE_TIMEBASE_TCR2 ( 1 )

/* ICPCE Function Mode [1] */
#define ICPCE_HISTORY_PREVIOUS_EDGE ( 0 )
#define ICPCE_HISTORY_XTH_EDGE      ( 1 )

/******************************************/
/* ICPCE Host Service Request Definitions */
/******************************************/
#define ICPCE_HSR_SHUTDOWN          ( 7 )
#define ICPCE_HSR_INIT_RISING_EDGE  ( 6 )
#define ICPCE_HSR_INIT_FALLING_EDGE ( 5 )
#define ICPCE_HSR_INIT_BOTH_EDGE    ( 4 )

/***********************************/
/* End ICPCE Primitive Definitions */
/***********************************/


/*************************************************/
/* Start GDFBE Primitive Definitions              */
/*************************************************/

/*************************************************/
/* GDFBE Function Configuration Information       */
/*************************************************/

/* GDFBE Function Mode [0] */
/*    0 = TCR1 time base */
/*    1 = TCR2 time base */
#define GDFBE_TCR1_TIMEBASE ( 0 )
#define GDFBE_TCR2_TIMEBASE ( 1 )

/* GDFBE Function Mode [1] */
/*    0 = Feedback and output are the same polarity */
/*    1 = Feedback and output are opposite polarities */
#define GDFBE_SAME_POLARITY ( 0 )
#define GDFBE_OPP_POLARITY  ( 1 )


/*************************************************/
/* GDFBE Host Service Request Definitions        */
/*************************************************/

#define GDFBE_HSR_SHUTDOWN     ( 7 )
#define GDFBE_HSR_CLEAR_FAULTS ( 6 )
#define GDFBE_HSR_INITIALIZE   ( 5 )

/************************************/
/* End GDFBE Primitive Definitions  */
/************************************/

/**************************************/
/* Start MPTACE Primitive Definitions */
/**************************************/

/*********************************************/
/* MPTACE Function Configuration Information */
/*********************************************/

/* MPTACE Function Mode [0] */
#define MPTACE_TIMEBASE_TCR1 ( 0 )
#define MPTACE_TIMEBASE_TCR2 ( 1 )

/* MPTACE Function Mode [1] */
#define MPTACE_TIME_MODE     ( 0 )
#define MPTACE_ANGLE_MODE    ( 1 )

/*******************************************/
/* MPTACE Host Service Request Definitions */
/*******************************************/
#define MPTACE_HSR_SHUTDOWN            ( 7 )
#define MPTACE_HSR_REQUEST             ( 6 )
#define MPTACE_HSR_INITIALIZE          ( 5 )
#define MPTACE_HSR_UPDATE              ( 4 )
#define MPTACE_HSR_ABORT_REQUEST       ( 3 )

/************************************/
/* End MPTACE Primitive Definitions */
/************************************/


/*************************************************/
/* Start DESFIE Primitive Definitions            */
/*************************************************/

/*************************************************/
/* DESFIE Function Configuration Information     */
/*************************************************/

/* DESFIE Function Mode [1] */
/*    0 = Fuel output active low */
/*    1 = Fuel output active high */
#define DESFIE_FUEL_ON_LOW  ( 0 )
#define DESFIE_FUEL_ON_HIGH ( 1 )

/* DESFIE Function Mode [0] */
/*    0 = Use TCR1 as time base */
/*    1 = Use TCR2 as time base */
#define DESFIE_TCR1_TIMEBASE ( 0 )
#define DESFIE_TCR2_TIMEBASE ( 1 )


/*************************************************/
/* DESFIE Host Service Request Definitions       */
/*************************************************/

#define DESFIE_HSR_SHUTDOWN     ( 7 )
#define DESFIE_HSR_BOUNDARY     ( 6 )
#define DESFIE_HSR_INITIALIZE   ( 5 )
#define DESFIE_HSR_UPDATE       ( 4 )

/************************************/
/* End DESFIE Primitive Definitions */
/************************************/

/*************************************************/
/* Start SENTDE Function Definitions             */
/*************************************************/

/*************************************************/
/* SENTDE Function Configuration Information     */
/*************************************************/

/* SENTDE Function Mode [0] */
/*    0 = TCR1 time base  */
/*    1 = TCR2 time base  */
#define SENTDE_TIMEBASE_TCR1 ( 0 )
#define SENTDE_TIMEBASE_TCR2 ( 1 )

/* SENTDE Function Mode [1] */
/*    0 = enable serial data processing  */
/*    1 = disable serial data processing  */
#define SENTDE_ENABLE_SERIAL  ( 0 )
#define SENTDE_DISABLE_SERIAL ( 1 )

/*************************************************/
/* SENTDE Host Service Request Definitions       */
/*************************************************/

#define SENTDE_HSR_SHUTDOWN       ( 7 )
#define SENTDE_HSR_INIT_CRIT_RISE ( 3 )
#define SENTDE_HSR_INIT_CRIT_FALL ( 5 )

/***********************************/
/* End SENTDE Function Definitions */
/***********************************/

/*************************************************/
/* Start ROCBe Primitive Definitions             */
/*************************************************/

/*************************************************/
/* ROCBe Function Configuration Information      */
/*************************************************/

/* ROCBe Function Mode [0]       */
/*    0 = TCR1 time base         */
/*    1 = TCR2 time base         */
#define ROCBE_TCR1_TIMEBASE ( 0 )
#define ROCBE_TCR2_TIMEBASE ( 1 ) 

/* ROCBe Function Mode [1]       */
/*    0 = HSR driven ROC mode    */
/*    1 = DRA mode               */
/*    OC mode is selectd by HSR  */
#define ROCBE_HSR_MODE  ( 0 )
#define ROCBE_DRA_MODE  ( 1 ) 

/* ROCBe Pin State Definitions   */
#define ROCBE_LOW  ( 0 )
#define ROCBE_HIGH ( 1 )

/*************************************************/
/* ROCBe Host Service Request Definitions        */
/*************************************************/

#define ROCBE_HSR_SHUTDOWN     ( 7 )
#define ROCBE_HSR_REQUEST_ROC  ( 6 )
#define ROCBE_HSR_INITIALIZE   ( 5 )
#define ROCBE_HSR_REQUEST_OC   ( 4 )
#define ROCBE_HSR_UPDATE_OC    ( 3 )
#define ROCBE_HSR_STOP         ( 2 )

/*************************************************/
/* End ROCBe Primitive Definitions               */
/*************************************************/

/*******************************************************/
/* MARKAB eTPU Microcode Set Global Variables Address  */
/*     byte address offset from start of eTPU RAM      */
/*******************************************************/
#define GLOBAL_CAUSE_OF_EXCEPTION    ( 0x0000 )
#define GLOBAL_TACH_CHAN_NUMBER      ( 0x0001 )
#define GLOBAL_CAM_CHAN_NUMBER       ( 0x0002 )
#define GLOBAL_DIG_CHAN_NUMBER       ( 0x0003 )
#define GLOBAL_PEPPE_ENGINE_DATA     ( 0x0005 )
#define GLOBAL_PDESFIE_ENGINE_DATA   ( 0x0009 )
#define GLOBAL_MPTACE_EXTRA_PULSES   ( 0x000C )
#define GLOBAL_MPTACE_ON_TIME_2      ( 0x000D )
#define GLOBAL_MPTACE_OFF_TIME_2     ( 0x0011 )
#define GLOBAL_MPTACE_ON_TIME_3      ( 0x0015 )
#define GLOBAL_CAME_MIN_PER          ( 0x0019 )
#define GLOBAL_CAME_REP_OUT_CHAN_NUM ( 0x001C )
#define GLOBAL_CAME_REP_OUT_LAG_TIME ( 0x001D )
#define GLOBAL_DESFIE_NORMAL_OFFSET  ( 0x0021 )
#define GLOBAL_DESFIE_TRIM_OFFSET    ( 0x0025 )
#define GLOBAL_DESFIE_KINJ           ( 0x0029 )
#define GLOBAL_DESFIE_MIN_INJ_OFF    ( 0x002D )
#define GLOBAL_DESFIE_MIN_TRIM       ( 0x0031 )
#define GLOBAL_DESFIE_EDGE_TIME      ( 0x0035 )
#define GLOBAL_DESFIE_EDGE_COUNT     ( 0x0039 )
#define GLOBAL_DESFIE_PERIOD         ( 0x003D )

/*************************************************************/
/* MARKAB eTPU microcode set - code entry table base address */
/*************************************************************/
#define ETPU_ENTRYTABLE_ADDRESS  ( 0x3000 )

/*************************************************************/
/* MARKAB eTPU microcode set primitive function information  */
/*************************************************************/

/**********************************************************/
/* MARKAB eTPU microcode set primitive function numbers   */
/**********************************************************/
#define RQOMBE_FUNCTION_NUM    ( 16 )//MCD-5413: Repeating Queued Output Match, Version B (Dual-Action) 
#define RQOME_FUNCTION_NUM     ( 17 )//MCD-5406: Repeating Queued Output Match 
#define EPPE_FUNCTION_NUM      ( 18 )//MCD-5408: Engine Position Processing (Crank) 
#define CAME_FUNCTION_NUM      ( 19 )//MCD-5411: Cam Input Processing 
#define PWMIE_FUNCTION_NUM     ( 20 )//MCD-5402: PWM Input 
#define SPWME_FUNCTION_NUM     ( 21 )//MCD-5421: Synchronous PWM Output 
#define PWMOE_FUNCTION_NUM     ( 22 )//MCD-5403: PWM Output 
#define FIE_FUNCTION_NUM       ( 23 )//MCD-5401: Frequency Input 
#define ECE_FUNCTION_NUM       ( 24 )//MCD-5409: Event Capture 
#define VSSBE_FUNCTION_NUM     ( 25 )//MCD-5416: Vehicle Speed Sensor, Version B 
#define ICPCE_FUNCTION_NUM     ( 26 )//MCD-5407: Input Capture / Pulse Counter 
#define GDFBE_FUNCTION_NUM     ( 27 )//MCD-5434: General Diagnostic Feedback 
#define MPTACE_FUNCTION_NUM    ( 28 )//MCD-5412: Multi-Pulse Time-Angle Combination (Spark) 
#define DESFIE_FUNCTION_NUM    ( 29 )//MCD-5417: Dual End-Angle Sequential Fuel Injection 
#define SENTDE_FUNCTION_NUM    ( 30 )//MCD-5446: SENT Signal Processing, Version D 
#define ROCBE_FUNCTION_NUM     ( 31 )//MCD-5415: Repeating Output Compare with Digital Ratio Adapter, Version B

/*********************************************************/
/* MARKAB eTPU microcode set primitive entry table type  */
/*   where: 0 = Standard                                 */
/*          1 = Alternate                                */
/*********************************************************/
#define RQOMBE_ENTRYTABLE_TYPE ( 0 )
#define RQOME_ENTRYTABLE_TYPE  ( 0 )
#define EPPE_ENTRYTABLE_TYPE   ( 0 )
#define CAME_ENTRYTABLE_TYPE   ( 0 )
#define PWMIE_ENTRYTABLE_TYPE  ( 0 )
#define SPWME_ENTRYTABLE_TYPE  ( 0 )
#define PWMOE_ENTRYTABLE_TYPE  ( 0 )
#define FIE_ENTRYTABLE_TYPE    ( 0 )
#define ECE_ENTRYTABLE_TYPE    ( 0 )
#define VSSBE_ENTRYTABLE_TYPE  ( 0 )
#define ICPCE_ENTRYTABLE_TYPE  ( 0 )
#define GDFBE_ENTRYTABLE_TYPE  ( 0 )
#define MPTACE_ENTRYTABLE_TYPE ( 0 )
#define DESFIE_ENTRYTABLE_TYPE ( 0 )
#define SENTDE_ENTRYTABLE_TYPE ( 0 )
#define ROCBE_ENTRYTABLE_TYPE  ( 0 )

/*********************************************************************/
/* MARKAB eTPU microcode set primitives - SPRAM frame size in bytes  */
/*********************************************************************/
#define RQOMBE_SPRAM_FRAME_SIZE ( 0x0018 )
/* RQOMBE SPRAM Frame size is a function of its array size, consult the MCD */
#define RQOME_SPRAM_FRAME_SIZE  ( 0x0018 )
/* RQOME SPRAM Frame size is a function of its array size, consult the MCD */
#define EPPE_SPRAM_FRAME_SIZE   ( 0x0088 )
/* EPPE SPRAM Frame size is a function of its array size, consult the MCD */
#define CAME_SPRAM_FRAME_SIZE   ( 0x0038 )
#define PWMIE_SPRAM_FRAME_SIZE  ( 0x0018 )
#define SPWME_SPRAM_FRAME_SIZE  ( 0x0030 )
#define PWMOE_SPRAM_FRAME_SIZE  ( 0x0010 )
#define FIE_SPRAM_FRAME_SIZE    ( 0x0010 )
#define ECE_SPRAM_FRAME_SIZE    ( 0x0018 )
/* ECE SPRAM Frame size is a function of its array size, consult the MCD */
#define VSSBE_SPRAM_FRAME_SIZE  ( 0x0058 )
#define ICPCE_SPRAM_FRAME_SIZE  ( 0x0010 )
#define GDFBE_SPRAM_FRAME_SIZE  ( 0x0008 )
#define MPTACE_SPRAM_FRAME_SIZE ( 0x0028 )
#define DESFIE_SPRAM_FRAME_SIZE ( 0x0010 )
#define SENTDE_SPRAM_FRAME_SIZE ( 0x0060 )
#define ROCBE_SPRAM_FRAME_SIZE  ( 0x0020 )

/***********************************************************************/
/* MARKAB eTPU recovery opcode to be placed in ETPUSCMOFFDATAR by CPU  */
/***********************************************************************/
#define ETPU_RECOVERY_OPCODE  ( (0xF7C0001F) )


/**************************/
/* MARKAB eTPU Checksums  */
/**************************/
#define ETPU_CHECKSUM_14K   (0x497C3710)

#define ETPU_CHECKSUM_16K   (0x1D0BF6B9)


#endif /* HW_ETPU_UCODE_H */

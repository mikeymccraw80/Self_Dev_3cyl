#ifndef DCANP_USID_H
#define DCANP_USID_H
/******************************************************************************
 *
 * Filename:          dcanp_usid.h
 *
 * Description:       Unit and Scaling ID datatypes and conversion macros.
 *                    These definitions and conversions are based on the
 *                    Draft International Standard ISO/DIS 15031-5.4,
 *                    SAE J-1979.
 *
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 2005, 2007, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#5/incl/dcanp_usid.h/1 %
 * %date_created:  Fri Sep 10 14:27:12 2010 %
 * %version:       1 %
 * %derived_by:    pz0vmh %
 *
 *****************************************************************************/

/*****************************************************************************
 *  Global Data Type Include Files
 *****************************************************************************/
#include "t_base.h"
#include "t_fixed.h"

#define CeUSID_SEC_TO_MS ( 1000 )

/*****************************************************************************
 *  Definitions for Unit and Scaling ID $0A
 *
 *  Description    Scaling/bit         Min Value       Max Value
 *      Time      0.1220703125 mv            0 v      7.9998779 v
 *                    unsigned
 *
 *****************************************************************************/

/*  range: [0, 8) */
typedef FIXED_UW_13                 T_USID_0Ah_U_0_8 ;
#define V_USID_0Ah_U_0_8(val)  (WORD)((val)*8192)
#define S_USID_0Ah_U_0_8       ( 13 )
#define CeUSID_0Ah_U_MAX       ( 7.9998779296875 )

/*****************************************************************************
 * 
 * Function:     PerfOFVC_USID_0Ah_Scale_VOLTb
 *
 * Description:  Converts VOLTb to USID_0Ah scaling.
 *
 * Parameters:   WORD with 1 bit = 0.48828125 mv (unsigned)
 * Return:       WORD with 1 bit = 0.1220703125 mv (unsigned)
 *****************************************************************************/

#define PerfOFVC_USID_0Ah_Scale_VOLTb(var_cnts) \
            ( usCVRT_usp(var_cnts,   \
                   S_VOLTb, S_USID_0Ah_U_0_8) ) 
                    
/*****************************************************************************
 *  Definitions for Unit and Scaling ID $0E
 *
 *  Description    Scaling/bit         Min Value       Max Value
 *      Time        0.001 Amp           0 Amp         65.535 Amp
 *                    unsigned
 *
 *  Note:  to simplify the definitions below, this data type is defined in
 *         terms of ma rather than Amps.
 *
 *****************************************************************************/

/*  range: [0, 65535) */
typedef FIXED_UW_00                 T_USID_0Eh_I_0_65535 ;
#define V_USID_0Eh_I_0_65535(val)  (WORD)((val))
#define S_USID_0Eh_I_0_65535       ( 0 )
#define CeUSID_0Eh_I_MAX       ( 65535 )

/*****************************************************************************
 * 
 * Function:     PerfOFVC_USID_0Eh_Scale_0_8Amps
 *
 * Description:  Converts Amps in 0.00012207 A per count to USID_0Eh scaling.
 *               Note that T_AMPSa is identical to T_AMPS_0_8
 *
 * Parameters:   WORD with 1 bit = 0.00012207 A (unsigned)
 * Return:       WORD with 1 bit = 1 ma (unsigned)
 *****************************************************************************/

#define CeUSID_A_TO_ma ( 1000 )
#define PerfOFVC_USID_0Eh_Scale_0_8Amps(var_cnts) \
            ( usMUL_us_usp(var_cnts, V_COUNT_WORD(CeUSID_A_TO_ma),  \
                   S_AMPS_0_8, S_COUNT_WORD, S_USID_0Eh_I_0_65535) ) 

/*****************************************************************************
 *  Definitions for Unit and Scaling ID $10
 *
 *  Description    Scaling/bit         Min Value       Max Value
 *      Time           1 ms                0 ms        65535 ms
 *                    unsigned
 *
 *****************************************************************************/

/*  range: [0, 65535] */
typedef FIXED_UW_00                  T_USID_10h_MS_0_65535 ;
#define V_USID_10h_MS_0_65535(val)   (WORD)((val)*1)
#define S_USID_10h_MS_0_65535        ( 0 )
#define CeUSID_10h_MS_MAX            ( 65535 )

/*****************************************************************************
 * 
 * Function:     PerfOFVC_USID_10h_Scale_0p12207ms
 *
 * Description:  Converts MS in 7.8125 ms counts to USID_10h scaling.
 *
 * Parameters:   WORD with 1 bit = 0.12207 ms (unsigned)
 * Return:       WORD with 1 bit = 1 ms (unsigned)
 *****************************************************************************/

#define PerfOFVC_USID_10h_Scale_0p12207ms(var_cnts) \
            ( ( var_cnts >= C_R0p12207ms16_msec(CeUSID_10h_MS_MAX) ) ? \
                 V_USID_10h_MS_0_65535(CeUSID_10h_MS_MAX) : \
            ( usMUL_us_usp(var_cnts, V_COUNT_WORD(CeUSID_SEC_TO_MS),  \
                   SwTIME_t_R0p12207ms, S_COUNT_WORD, S_USID_10h_MS_0_65535) ) ) 
 
/*****************************************************************************
 * 
 * Function:     PerfOFVC_USID_10h_Scale_7p8ms
 *
 * Description:  Converts MS in 7.8125 ms counts to USID_10h scaling.
 *
 * Parameters:   WORD with 1 bit = 7.8125 ms (unsigned)
 * Return:       WORD with 1 bit = 1 ms (unsigned)
 *****************************************************************************/

#define PerfOFVC_USID_10h_Scale_7p8ms(var_cnts) \
            ( ( var_cnts >= C_R7p8125ms16_msec(CeUSID_10h_MS_MAX) ) ? \
                 V_USID_10h_MS_0_65535(CeUSID_10h_MS_MAX) : \
            ( usMUL_us_usp(var_cnts, V_COUNT_WORD(CeUSID_SEC_TO_MS),  \
                   SwTIME_t_R7p8125ms, S_COUNT_WORD, S_USID_10h_MS_0_65535) ) ) 
 
/*****************************************************************************
 * 
 * Function:     PerfOFVC_USID_10h_Scale_15p6ms
 *
 * Description:  Converts MS in 15.625 ms counts to USID_10h scaling.
 *
 * Parameters:   WORD with 1 bit = 15.625 ms (unsigned)
 * Return:       WORD with 1 bit = 1 ms (unsigned)
 *****************************************************************************/

#define PerfOFVC_USID_10h_Scale_15p6ms(var_cnts) \
            ( ( var_cnts >= C_R15p625ms16_msec(CeUSID_10h_MS_MAX) ) ? \
                 V_USID_10h_MS_0_65535(CeUSID_10h_MS_MAX) : \
            ( usMUL_us_usp(var_cnts, V_COUNT_WORD(CeUSID_SEC_TO_MS),  \
                   SwTIME_t_R15p625ms, S_COUNT_WORD, S_USID_10h_MS_0_65535) ) ) 
  
/*****************************************************************************
 * 
 * Function:     PerfOFVC_15p6ms_Scale_USID_10h
 *
 * Description:  Converts Sec in USID_10h scaling to 15.625 ms counts.
 *
 * Parameters:   WORD with 1 bit = 1 ms (unsigned)
 * Return:       WORD with 1 bit = 15.625 ms (unsigned)
 *****************************************************************************/

#define PerfOFVC_15p6ms_Scale_USID_10h(var_cnts) \
            ( usDIV_us_usp(var_cnts, V_COUNT_WORD(CeUSID_SEC_TO_MS),  \
                   S_USID_10h_MS_0_65535, S_COUNT_WORD, SwTIME_t_R15p625ms) ) 
   
/*****************************************************************************
 * 
 * Function:     PerfOFVC_USID_10h_Scale_64s
 *
 * Description:  Converts Seconds in 0-64 s range to USID_10h scaling.
 *
 * Parameters:   WORD with 1 bit = 0.0009765625 ms (unsigned)
 * Return:       WORD with 1 bit = 1 ms (unsigned)
 *****************************************************************************/

#define PerfOFVC_USID_10h_Scale_64s(secs) \
            ( usMUL_us_usp(secs, V_COUNT_WORD(CeUSID_SEC_TO_MS),  \
                   S_SECONDS_0_64, S_COUNT_WORD, S_USID_10h_MS_0_65535) ) 
  
/*****************************************************************************
 *  Definitions for Unit and Scaling ID $20
 *
 *  Description    Scaling/bit         Min Value       Max Value
 *     Ratio        0.0039062              0           255.993
 *                   unsigned
 *
 *****************************************************************************/

/*  range: [0, 256) */
typedef FIXED_UW_08                   T_USID_20h_RATIO_0_256 ;
#define V_USID_20h_RATIO_0_256(val)   (WORD)((val)*256)
#define S_USID_20h_RATIO_0_256        ( 8 )
#define CeUSID_20h_RATIO_0_256_MAX            ( 255.996 )

/*****************************************************************************
 * 
 * Function:     PerfOFVC_USID_20h_Scale_RATIO_0_128
 *
 * Description:  Converts ratio with 0-128 range to USID_20h scaling.
 *
 *               Converts input range [0,128) to output range [0,256).
 *
 * Parameters:   WORD with 1 bit = 0.001953125 (unsigned)
 * Return:       WORD with 1 bit = 0.00390625 (unsigned)
 *****************************************************************************/

#define PerfOFVC_USID_20h_Scale_RATIO_0_128(var_cnts) \
            ( usCVRT_usp(var_cnts,   \
                   S_RATIO_0_128, S_USID_20h_RATIO_0_256) ) 
 
/*****************************************************************************
 *  Definitions for Unit and Scaling ID $24
 *
 *  Description    Scaling/bit         Min Value       Max Value
 *     Ratio        0.0039062              0           255.993
 *                   unsigned
 *
 *****************************************************************************/

/*  range: [0, 65535] */
typedef FIXED_UW_00                   T_USID_24h_COUNTS_0_65535 ;
#define V_USID_24h_COUNTS_0_65535(val)   (WORD)((val)*1)
#define S_USID_24h_COUNTS_0_65535        ( 0 )
#define CeUSID_24h_COUNTS_0_65535_MAX            ( 65535 )

/*****************************************************************************
 * 
 * Function:     PerfOFVC_USID_24h_Scale_COUNT_WORD
 *
 * Description:  Converts byte with 0-255 range to USID_24h scaling.
 *
 *               Converts input range [0,65535] to output range [0,65535].
 *
 * Parameters:   WORD with 1 bit = 1 count (unsigned)
 * Return:       WORD with 1 bit = 1 count (unsigned)
 *****************************************************************************/

#define PerfOFVC_USID_24h_Scale_COUNT_WORD(var_cnts) \
            ( (T_USID_24h_COUNTS_0_65535) var_cnts ) 
 
/*****************************************************************************
 *  Definitions for Unit and Scaling ID $29
 *
 *  Description    Scaling/bit         Min Value       Max Value
 *   Pressure      .00025 kPa            0 kPa        16.384 kPa
 *   (vacuum)        unsigned
 *
 *****************************************************************************/

/*  range: [0, 16.384) */
typedef FIXED_UW_12                    T_USID_29h_kPa_0_16p384 ;
#define V_USID_29h_kPa_0_16p384(val)   (WORD)((val)*4000)
#define S_USID_29h_kPa_0_16p384        ( 12 )
#define CeUSID_29h_kPa_MAX             ( 16.38375 )

/*****************************************************************************
 * 
 * Function:     PerfOFVC_USID_29h_Scale_T_VAC_PER_SEC
 *
 * Description:  Converts VAC_PER_SEC in inches of H2O to USID_29h scaling.
 *
 *               Note that this clips the input value (which is signed) from
 *               the range of [-32, 32) to the output range [0, 16.38375].
 *               The conversion factor uses the relationship of 
 *               1 inch water = 0.2490889 kPa. ( J1979/ISO15031-5 specified
 *                  conversion factor) 
 *               0.9765625 is the ratio of 4000/4096 (USID scaling /
 *               power of two scaling) 
 *
 * Parameters:   WORD with 1 bit = 0.0009765625 inches of H2O (signed)
 * Return:       WORD with 1 bit = 0.00025 kPa (unsigned)
 *****************************************************************************/

#define CeUSID_VAC_PER_SEC_TO_kPa ( 0.24325087890625 ) /* 0.9765625 * 0.2490889 */
#define PerfOFVC_USID_29h_Scale_T_VAC_PER_SEC(vac_per_sec) \
            ( usMUL_ss_usp(vac_per_sec,  \
                  V_RATIO_0_1(CeUSID_VAC_PER_SEC_TO_kPa),  \
                      S_VAC_PER_SEC, S_RATIO_0_1, S_USID_29h_kPa_0_16p384) ) 
  
/*****************************************************************************
 *  Definitions for Unit and Scaling ID $2B
 *
 *  Description    Scaling/bit         Min Value       Max Value
 *   Switches      1 switch/bit       0 switches    65535 switches
 *                  unsigned
 *
 *****************************************************************************/

/*  range: [0, 65535] */
typedef FIXED_UW_00                     T_USID_2Bh_SWTCH_0_65535 ;
#define V_USID_2Bh_SWTCH_0_65535(val)   (WORD)((val)*1)
#define S_USID_2Bh_SWTCH_0_65535        ( 0 )

/*****************************************************************************
 * 
 * Function:     PerfOFVC_USID_2Bh_Scale_T_WORD
 *
 * Description:  Converts WORD to USID_2Bh scaling.
 *
 * Parameters:   WORD with 1 bit = counts (unsigned)
 * Return:       WORD with 1 bit = switches (unsigned)
 *****************************************************************************/

#define PerfOFVC_USID_2Bh_Scale_T_WORD(switches) ( switches ) 
  
/*****************************************************************************
 *  Definitions for Unit and Scaling ID $9C
 *
 *  Description    Scaling/bit         Min Value       Max Value
 *   Pressure       .01 degrees     -327.68 degrees   327.67 degrees
 *  (absolute)       signed
 *
 *****************************************************************************/

/*  range: [-327.68, 327.68] */
typedef FIXED_SW_00                      T_USID_9Ch_CAMPHI_N327p68_327p68 ;
#define V_USID_9Ch_CAMPHI_N327p68_327p68(val)   (WORD)((val)*100)
#define S_USID_9Ch_CAMPHI_N327p68_327p68       ( 0 )
#define CeUSID_9Ch_CAMPHI_DIFF_MAX             (  327.67 )
#define CeUSID_9Ch_CAMPHI_DIFF_MIN             ( -327.68 )
 
/*****************************************************************************
 * 
 * Function:     PerfOFVC_USID_9Ch_Scale_T_CAMPHI
 *
 * Description:  Converts CAM Phaser Angle in degrees to USID_9Ch scaling.
 *
 *               Note that this converts the input value (which is signed)
 *               from the range of [-256, 256) to the output range
 *               [-327.68, 327.68].
 *               100 is used to convert the CAM Phaser Angle value to the
 *               USID value in hundreths of degrees, the displayed value
 *               will effectively be divided by 100, placing the decimal
 *               point correctly.) 
 *
 * Parameters:   WORD with 1 bit = 0.0078125 degrees (signed)
 * Return:       WORD with 1 bit = 0.01 degrees (signed)
 *****************************************************************************/

#define CeUSID_CAMPHI_TO_Angle ( 100 )
#define PerfOFVC_USID_9Ch_Scale_T_CAMPHI(angle) \
         ( ssMUL_ss_usp(angle, V_COUNT_WORD(CeUSID_CAMPHI_TO_Angle),  \
                S_CAMPHI, S_COUNT_WORD, S_USID_9Ch_CAMPHI_N327p68_327p68) ) 
 
/*****************************************************************************
 *  Definitions for Unit and Scaling ID $FD
 *
 *  Description    Scaling/bit         Min Value       Max Value
 *   Pressure       .001 kPa         -32.768 kPa       32.767 kPa
 *  (absolute)       signed
 *
 *****************************************************************************/

/*  range: [-32.768, 32.768] */
typedef FIXED_SW_10                        T_USID_FDh_kPa_N32p768_32p768 ;
#define V_USID_FDh_kPa_N32p768_32p768(val)   (WORD)((val)*1000)
#define S_USID_FDh_kPa_N32p768_32p768       ( 10 )
#define CeUSID_FDh_kPa_DIFF_MAX             (  32.767 )
#define CeUSID_FDh_kPa_DIFF_MIN             ( -32.768 )
 
/*****************************************************************************
 * 
 * Function:     PerfOFVC_USID_FDh_Scale_T_KPA_DIFF
 *
 * Description:  Converts signed pressure in kPa to USID_FDh scaling.
 *
 *               Note that this clips the input value (which is signed) from
 *               the range of [-256, 256) to the output range
 *               [-32.768, 32.768].
 *               0.9765625 is the ratio of 1000/1024 (USID scaling /
 *               power of two scaling) 
 *
 * Parameters:   WORD with 1 bit = 0.00390625 Pa (signed)
 * Return:       WORD with 1 bit = 1.0 Pa (signed)
 *****************************************************************************/

#define CeUSID_KPA_DIFF_TO_kPa ( 0.9765625 )
#define PerfOFVC_USID_FDh_Scale_T_KPA_DIFF(vac_diff) \
   ( ( vac_diff >= V_KPA_DIFF(CeUSID_FDh_kPa_DIFF_MAX) ) ? \
        V_USID_FDh_kPa_N32p768_32p768(CeUSID_FDh_kPa_DIFF_MAX) : \
      ( ( vac_diff <= V_KPA_DIFF(CeUSID_FDh_kPa_DIFF_MIN) ) ? \
           V_USID_FDh_kPa_N32p768_32p768(CeUSID_FDh_kPa_DIFF_MIN) : \
         ( ssMUL_ss_usp(vac_diff, V_RATIO_0_1(CeUSID_KPA_DIFF_TO_kPa),  \
                S_KPA_DIFF, S_RATIO_0_1, S_USID_FDh_kPa_N32p768_32p768) ) ) ) 
 
/*****************************************************************************
 *  Definitions for Unit and Scaling ID $FE
 *
 *  Description    Scaling/bit         Min Value       Max Value
 *   Pressure      .00025 kPa         -8.192 kPa       8.192 kPa
 *   (vacuum)         signed
 *
 *****************************************************************************/

/*  range: [-8.192, 8.192) */
typedef FIXED_SW_12                        T_USID_FEh_kPa_N8p192_8p192 ;
#define V_USID_FEh_kPa_N8p192_8p192(val)   (WORD)((val)*4000)
#define S_USID_FEh_kPa_N8p192_8p192        ( 12 )
#define CeUSID_FEh_kPa_MAX             ( 8.191875 )
#define CeUSID_FEh_kPa_MIN             ( -8.192 )
 
/*****************************************************************************
 * 
 * Function:     PerfOFVC_USID_FEh_Scale_T_VAC
 *
 * Description:  Converts VAC in inches of water to USID_FEh scaling.
 *
 *               Note that this clips the input value (which is signed) from
 *               the range of [-32, 32) to the output range
 *               [-8.191875, 8.191875].
 *               The conversion factor uses the relationship of 
 *               1 inch water = 0.2490889 kPa. ( J1979/ISO15031-5 specified
 *                  conversion factor) 
 *               0.9765625 is the ratio of 4000/4096 (USID scaling /
 *               power of two scaling) 
 *
 * Parameters:   WORD with 1 bit = 0.9765625 inches of water (signed)
 * Return:       WORD with 1 bit = 0.25 Pa (signed)
 *****************************************************************************/

#define CeUSID_VAC_TO_kPa ( 0.24325087890625 ) /* = 0.9765625 * 0.2490889 */
#define PerfOFVC_USID_FEh_Scale_T_VAC(vac) \
            ( ssMUL_ss_usp(vac, V_RATIO_0_1(CeUSID_VAC_TO_kPa),  \
                   S_VAC, S_RATIO_0_1, S_USID_FEh_kPa_N8p192_8p192) ) 
 
#endif
/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1     051206 hdb 5378 Created module.
* 1.1.1 070413 hdb 6268 Service $06 corrections for PIDs
*                       Add:  PerfOFVC_15p6ms_Scale_USID_10h
* 2     070416 hdb 6272 Improve scaling of PerfOFVC_15p6ms_Scale_USID_10h
*                        by dividing instead of multiplying.
* 3     070416 hdb 6262 Add Service ID $06 Test Result Threshold and Data for
*                         O2 Heater Results and Rear O2 Response Results.
*                       Add USID $0E for Amps,
*                           PerfOFVC_USID_10h_Scale_0p12207ms conversion
* 4     071108 hdb 6618 Define USID $9C for Angles
*                         Also add PerfOFVC_USID_10h_Scale_64s
*
* 5.0  100906    hdg  xxx  Implemented CAN OBD in MT22.1 paltform.
******************************************************************************/

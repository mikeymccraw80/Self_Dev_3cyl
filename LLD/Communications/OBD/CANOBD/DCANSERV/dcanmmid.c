/******************************************************************************
 *
 * Filename:          dcanmmid.c
 *
 * Description:       This contains the list of Monitor IDs and Test IDs for
 *                    SID $06
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
 * Copyright 2005-2008, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:      ctc_pt3#2/csrc/dcanmmid.c/5 %
 * %date_created:   Wed Mar  7 10:04:24 2012 %
 * %version:        5 %
 * %derived_by:     hzpcqq %
 *
 *****************************************************************************/
/******************************************************************************
* APP Include Files
******************************************************************************/
// #include "obdsfexi.h"
/******************************************************************************
* CAN OBD Service Include Files
******************************************************************************/
#include "dcanpmid.h"
#include "dcanp_usid.h" 
/******************************************************************************
* CAN OBD NW Layer Include Files
******************************************************************************/


#if (XeDCAN_SID_06_Supported == CeDCAN_Supported)
/******************************************************************************
 *  Static Data Definitions
 *****************************************************************************/

/******************************************************************************
 *  Global Data Definitions
 *****************************************************************************/

/******************************************************************************
 *  Static Function Prototypes
 *****************************************************************************/
/*********************************************************************
 * MID/TID Connections for SID 06                                     *
 *********************************************************************/

/*********************************************************************/
/* FUNCTION:    GetDCAN_Dflt_Parameter()                             */
/* DESCRIPTION: Default Min Value for TIDs                           */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_Dflt_Parameter(void* LpDCAN_Output )
{
   *((T_COUNT_WORD*)LpDCAN_Output) = V_COUNT_WORD(65535);
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_Dflt_TestMin_Val()                           */
/* DESCRIPTION: Default Min Value for TIDs                           */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_Dflt_TestMin_Val(void* LpDCAN_Output )
{
   *((T_COUNT_WORD*)LpDCAN_Output) = V_COUNT_WORD(0);
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_Dflt_TestMax_Val()                           */
/* DESCRIPTION: Default Max Value for TIDs                           */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_Dflt_TestMax_Val(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = V_COUNT_WORD(65535);
}
#ifdef OBD_CONTROLLER_IS_MT80
/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_01_TID_03_TstRslt()                      */
/* DESCRIPTION: MID 01 TID 03 test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_01_TID_03_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_U_11_RespLeanThrsh();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_01_TID_03_TstThshMin()                   */
/* DESCRIPTION: MID 01 TID 03 Test threshold Min                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_01_TID_03_TstThshMin(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_U_11_RespLeanThrsh();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_01_TID_03_TstThshMax()                   */
/* DESCRIPTION: MID 01 TID 03 Test threshold Max                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_01_TID_03_TstThshMax(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_U_11_RespLeanThrsh();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_01_TID_04_TstRslt()                      */
/* DESCRIPTION: MID 01 TID 04 test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_01_TID_04_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_U_11_RespRichThrsh();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_01_TID_04_TstThshMin()                   */
/* DESCRIPTION: MID 01 TID 04 Test threshold Min                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_01_TID_04_TstThshMin(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_U_11_RespRichThrsh();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_01_TID_04_TstThshMax()                   */
/* DESCRIPTION: MID 01 TID 04 Test threshold Max                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_01_TID_04_TstThshMax(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_U_11_RespRichThrsh();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_01_TID_05_TstRslt()                      */
/* DESCRIPTION: MID 01 TID 05 test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_01_TID_05_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_11_RespRL_Avg_TstRslt();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_01_TID_05_TstThshMin()                   */
/* DESCRIPTION: MID 01 TID 05 Test threshold Min                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_01_TID_05_TstThshMin(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_11_RespRL_Avg_TstThrshMin();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_01_TID_05_TstThshMax()                   */
/* DESCRIPTION: MID 01 TID 05 Test threshold Max                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_01_TID_05_TstThshMax(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_11_RespRL_Avg_TstThrshMax();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_01_TID_06_TstRslt()                      */
/* DESCRIPTION: MID 01 TID 06 test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_01_TID_06_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_11_RespLR_Avg_TstRslt();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_01_TID_06_TstThshMin()                   */
/* DESCRIPTION: MID 01 TID 06 Test threshold Min                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_01_TID_06_TstThshMin(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_11_RespLR_Avg_TstThrshMin();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_01_TID_06_TstThshMax()                   */
/* DESCRIPTION: MID 01 TID 06 Test threshold Max                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_01_TID_06_TstThshMax(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_11_RespLR_Avg_TstThrshMax();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_01_TID_81_TstRslt()                      */
/* DESCRIPTION: MID 01 TID 81 test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_01_TID_81_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_11_RespRL_Sw_TstRslt();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_01_TID_81_TstThshMin()                   */
/* DESCRIPTION: MID 01 TID 81 Test threshold Min                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_01_TID_81_TstThshMin(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_11_RespRL_Sw_TstThrshMin();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_01_TID_81_TstThshMax()                   */
/* DESCRIPTION: MID 01 TID 81 Test threshold Max                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_01_TID_81_TstThshMax(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_11_RespRL_Sw_TstThrshMax();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_01_TID_82_TstRslt()                      */
/* DESCRIPTION: MID 01 TID 82 test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_01_TID_82_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_11_RespLR_Sw_TstRslt();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_01_TID_82_TstThshMin()                   */
/* DESCRIPTION: MID 01 TID 82 Test threshold Min                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_01_TID_82_TstThshMin(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_11_RespLR_Sw_TstThrshMin();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_01_TID_82_TstThshMax()                   */
/* DESCRIPTION: MID 01 TID 82 Test threshold Max                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_01_TID_82_TstThshMax(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_11_RespLR_Sw_TstThrshMax();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_01_TID_83_TstRslt()                      */
/* DESCRIPTION: MID 01 TID 83 test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_01_TID_83_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_11_RespRatio_TstRslt();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_01_TID_83_TstThshMin()                   */
/* DESCRIPTION: MID 01 TID 83 Test threshold Min                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_01_TID_83_TstThshMin(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_11_RespRatio_TstThrshMin();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_01_TID_83_TstThshMax()                   */
/* DESCRIPTION: MID 01 TID 83 Test threshold Max                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_01_TID_83_TstThshMax(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_11_RespRatio_TstThrshMax();
}
#endif
/**********************************************************
* All MID 0x02 TID functions.                             *
**********************************************************/
/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_03_TstRslt()                      */
/* DESCRIPTION: MID 02 TID 03 test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_03_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_U_TD_12_LeanThrshResult();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_03_TstThshMin()                   */
/* DESCRIPTION: MID 02 TID 03 test maximum                           */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_03_TstThshMin(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_U_TD_12_LeanThrshMin();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_03_TstThshMax()                   */
/* DESCRIPTION: MID 02 TID 03 test maximum                           */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_03_TstThshMax(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_U_TD_12_LeanThrshMax();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_04_TstRslt()                      */
/* DESCRIPTION: MID 02 TID 04 test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_04_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_U_TD_12_RichThrshResult();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_04_TstThshMin()                   */
/* DESCRIPTION: MID 02 TID 04 test maximum                           */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_04_TstThshMin(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_U_TD_12_RichThrshMin();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_04_TstThshMax()                   */
/* DESCRIPTION: MID 02 TID 04 test maximum                           */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_04_TstThshMax(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_U_TD_12_RichThrshMax();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_05_TstRslt()                      */
/* DESCRIPTION: MID 02 TID 05 test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_05_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_t_12_TD_Resp_Sw_TstTimeResult();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_05_TstThshMin()                   */
/* DESCRIPTION: MID 02 TID 05 test maximum                           */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_05_TstThshMin(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_t_12_TD_Resp_Sw_TstTimeMin();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_05_TstThshMax()                   */
/* DESCRIPTION: MID 02 TID 05 test maximum                           */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_05_TstThshMax(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_t_12_TD_Resp_Sw_TstTimeMax();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_06_TstRslt()                      */
/* DESCRIPTION: MID 02 TID 06 test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_06_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_t_12_TP_Resp_Sw_TstTimeResult();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_06_TstThshMin()                   */
/* DESCRIPTION: MID 02 TID 06 test maximum                           */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_06_TstThshMin(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_t_12_TP_Resp_Sw_TstTimeMin();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_06_TstThshMax()                   */
/* DESCRIPTION: MID 02 TID 06 test maximum                           */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_06_TstThshMax(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_t_12_TP_Resp_Sw_TstTimeMax();
}

#ifdef OBD_CONTROLLER_IS_MT80
/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_BA_TstRslt()                      */
/* DESCRIPTION: MID 02 TID BA test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_BA_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_R_12_LeanThreshResult();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_BA_TstThshMin()                   */
/* DESCRIPTION: MID 02 TID BA test maximum                           */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_BA_TstThshMin(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_R_12_LeanThreshMin();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_BA_TstThshMax()                   */
/* DESCRIPTION: MID 02 TID BA test maximum                           */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_BA_TstThshMax(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_R_12_LeanThreshMax();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_BB_TstRslt()                      */
/* DESCRIPTION: MID 02 TID BB test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_BB_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_R_12_RichThreshResult();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_BB_TstThshMin()                   */
/* DESCRIPTION: MID 02 TID BB test maximum                           */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_BB_TstThshMin(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_R_12_RichThreshMin();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_BB_TstThshMax()                   */
/* DESCRIPTION: MID 02 TID BB test maximum                           */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_BB_TstThshMax(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_R_12_RichThreshMax();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_BC_TstRslt()                      */
/* DESCRIPTION: MID 02 TID BC test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_BC_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_R_12_ResponseRichLeanResult();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_BC_TstThshMin()                   */
/* DESCRIPTION: MID 02 TID BC test maximum                           */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_BC_TstThshMin(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_R_12_ResponseRichLeanMin();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_BC_TstThshMax()                   */
/* DESCRIPTION: MID 02 TID BC test maximum                           */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_BC_TstThshMax(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_R_12_ResponseRichLeanMax();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_BD_TstRslt()                      */
/* DESCRIPTION: MID 02 TID BD test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_BD_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_R_12_ResponseLeanRichResult();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_BD_TstThshMin()                   */
/* DESCRIPTION: MID 02 TID BD test maximum                           */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_BD_TstThshMin(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_R_12_ResponseLeanRichMin();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_02_TID_BD_TstThshMax()                   */
/* DESCRIPTION: MID 02 TID BD test maximum                           */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_02_TID_BD_TstThshMax(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_R_12_ResponseLeanRichMax();
}
#if XeSYST_EOSD_21_SENSOR == CeSYST_EOSD_SENSOR_PRESENT
/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_05_TID_03_TstRslt()                      */
/* DESCRIPTION: MID 05 TID 03 test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_05_TID_03_TstRslt(void* LpDCAN_Output)
{
   Parameter_Not_Used(LpDCAN_Output);
//   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_U_21_RespLeanThrsh();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_05_TID_03_TstThshMin()                   */
/* DESCRIPTION: MID 05 TID 03 Test threshold Min                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_05_TID_03_TstThshMin(void* LpDCAN_Output)
{
   Parameter_Not_Used(LpDCAN_Output);
//   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_U_21_RespLeanThrsh();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_05_TID_03_TstThshMax()                   */
/* DESCRIPTION: MID 05 TID 03 Test threshold Max                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_05_TID_03_TstThshMax(void* LpDCAN_Output)
{
   Parameter_Not_Used(LpDCAN_Output);
//   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_U_21_RespLeanThrsh();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_05_TID_04_TstRslt()                      */
/* DESCRIPTION: MID 05 TID 04 test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_05_TID_04_TstRslt(void* LpDCAN_Output)
{
   Parameter_Not_Used(LpDCAN_Output);
 //  *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_U_21_RespRichThrsh();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_05_TID_04_TstThshMin()                   */
/* DESCRIPTION: MID 05 TID 04 Test threshold Min                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_05_TID_04_TstThshMin(void* LpDCAN_Output)
{
   Parameter_Not_Used(LpDCAN_Output);
//   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_U_21_RespRichThrsh();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_05_TID_04_TstThshMax()                   */
/* DESCRIPTION: MID 05 TID 04 Test threshold Max                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_05_TID_04_TstThshMax(void* LpDCAN_Output)
{
   Parameter_Not_Used(LpDCAN_Output);
//   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_U_21_RespRichThrsh();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_05_TID_05_TstRslt()                      */
/* DESCRIPTION: MID 05 TID 05 test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_05_TID_05_TstRslt(void* LpDCAN_Output)
{
   Parameter_Not_Used(LpDCAN_Output);
//   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_21_RespRL_Avg_TstRslt();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_05_TID_05_TstThshMin()                   */
/* DESCRIPTION: MID 05 TID 05 Test threshold Min                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_05_TID_05_TstThshMin(void* LpDCAN_Output)
{
   Parameter_Not_Used(LpDCAN_Output);
//   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_21_RespRL_Avg_TstThrshMin();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_05_TID_05_TstThshMax()                   */
/* DESCRIPTION: MID 05 TID 05 Test threshold Max                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_05_TID_05_TstThshMax(void* LpDCAN_Output)
{
   Parameter_Not_Used(LpDCAN_Output);
//   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_21_RespRL_Avg_TstThrshMax();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_05_TID_06_TstRslt()                      */
/* DESCRIPTION: MID 05 TID 06 test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_05_TID_06_TstRslt(void* LpDCAN_Output)
{
   Parameter_Not_Used(LpDCAN_Output);
//   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_21_RespLR_Avg_TstRslt();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_05_TID_06_TstThshMin()                   */
/* DESCRIPTION: MID 05 TID 06 Test threshold Min                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_05_TID_06_TstThshMin(void* LpDCAN_Output)
{
   Parameter_Not_Used(LpDCAN_Output);
//   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_21_RespLR_Avg_TstThrshMin();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_05_TID_06_TstThshMax()                   */
/* DESCRIPTION: MID 05 TID 06 Test threshold Max                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_05_TID_06_TstThshMax(void* LpDCAN_Output)
{
   Parameter_Not_Used(LpDCAN_Output);
//   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_21_RespLR_Avg_TstThrshMax();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_05_TID_81_TstRslt()                      */
/* DESCRIPTION: MID 05 TID 81 test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_05_TID_81_TstRslt(void* LpDCAN_Output)
{
   Parameter_Not_Used(LpDCAN_Output);
//   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_21_RespRL_Sw_TstRslt();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_05_TID_81_TstThshMin()                   */
/* DESCRIPTION: MID 05 TID 81 Test threshold Min                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_05_TID_81_TstThshMin(void* LpDCAN_Output)
{
   Parameter_Not_Used(LpDCAN_Output);
//   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_21_RespRL_Sw_TstThrshMin();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_05_TID_81_TstThshMax()                   */
/* DESCRIPTION: MID 05 TID 81 Test threshold Max                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_05_TID_81_TstThshMax(void* LpDCAN_Output)
{
   Parameter_Not_Used(LpDCAN_Output);
//   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_21_RespRL_Sw_TstThrshMax();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_05_TID_82_TstRslt()                      */
/* DESCRIPTION: MID 05 TID 82 test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_05_TID_82_TstRslt(void* LpDCAN_Output)
{
   Parameter_Not_Used(LpDCAN_Output);
//   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_21_RespLR_Sw_TstRslt();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_05_TID_82_TstThshMin()                   */
/* DESCRIPTION: MID 05 TID 82 Test threshold Min                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_05_TID_82_TstThshMin(void* LpDCAN_Output)
{
   Parameter_Not_Used(LpDCAN_Output);
//   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_21_RespLR_Sw_TstThrshMin();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_05_TID_82_TstThshMax()                   */
/* DESCRIPTION: MID 05 TID 82 Test threshold Max                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_05_TID_82_TstThshMax(void* LpDCAN_Output)
{
   Parameter_Not_Used(LpDCAN_Output);
//   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_21_RespLR_Sw_TstThrshMax();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_05_TID_83_TstRslt()                      */
/* DESCRIPTION: MID 05 TID 83 test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_05_TID_83_TstRslt(void* LpDCAN_Output)
{
   Parameter_Not_Used(LpDCAN_Output);
//   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_21_RespRatio_TstRslt();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_05_TID_83_TstThshMin()                   */
/* DESCRIPTION: MID 05 TID 83 Test threshold Min                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_05_TID_83_TstThshMin(void* LpDCAN_Output)
{
   Parameter_Not_Used(LpDCAN_Output);
//   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_21_RespRatio_TstThrshMin();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_05_TID_83_TstThshMax()                   */
/* DESCRIPTION: MID 05 TID 83 Test threshold Max                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_05_TID_83_TstThshMax(void* LpDCAN_Output)
{
   Parameter_Not_Used(LpDCAN_Output);
//   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_21_RespRatio_TstThrshMax();
}
#endif
#endif
/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_21_TID_A1_TstRslt()                      */
/* DESCRIPTION: MID 21 TID A1 test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_21_TID_A1_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetICMD_t_B1_EWMA_OSC_TstRslt();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_21_TID_A1_TstThshMin()                   */
/* DESCRIPTION: MID 21 TID A1 Test threshold Min                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_21_TID_A1_TstThshMin(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetICMD_t_B1_EWMA_OSC_TstThrshMin();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_21_TID_A1_TstThshMax()                   */
/* DESCRIPTION: MID 21 TID A1 Test threshold Max                     */
/*              Required for MID 21, TID A1                          */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_21_TID_A1_TstThshMax(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetICMD_t_B1_EWMA_OSC_TstThrshMax();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_22_TID_A2_TstRslt()                      */
/* DESCRIPTION: MID 22 TID A2 test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_22_TID_A2_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetICMD_t_B2_EWMA_OSC_TstRslt();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_22_TID_A2_TstThshMin()                   */
/* DESCRIPTION: MID 22 TID A2 Test threshold Min                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_22_TID_A2_TstThshMin(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetICMD_t_B2_EWMA_OSC_TstThrshMin();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_22_TID_A2_TstThshMax()                   */
/* DESCRIPTION: MID 22 TID A2 Test threshold Max                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_22_TID_A2_TstThshMax(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetICMD_t_B2_EWMA_OSC_TstThrshMax();
}
#ifdef OBD_CONTROLLER_IS_MT80
/**********************************************************
* All MID 0x41 TID functions.                             *
**********************************************************/
/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_41_TID_B1_TstThshResult()                */
/* DESCRIPTION: MID 41 TID B1 test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_41_TID_B1_TstThshResult(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_I_E_11_CurrentTestResult();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_41_TID_B1_TstThshMin()                   */
/* DESCRIPTION: MID 41 TID B1 test threshold min                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_41_TID_B1_TstThshMin(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_I_E_11_CurrentTestMin();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_41_TID_B1_TstThshMax()                   */
/* DESCRIPTION: MID 41 TID B1 test threshold max                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_41_TID_B1_TstThshMax(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_I_E_11_CurrentTestMax();
}

/**********************************************************
* All MID 0x42 TID functions.                             *
**********************************************************/
/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_42_TID_B1_TstThshResult()                */
/* DESCRIPTION: MID 42 TID B1 test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_42_TID_B1_TstThshResult(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_I_E_12_CurrentTestResult();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_42_TID_B1_TstThshMin()                   */
/* DESCRIPTION: MID 42 TID B1 test threshold min                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_42_TID_B1_TstThshMin(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_I_E_12_CurrentTestMin();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_42_TID_B1_TstThshMax()                   */
/* DESCRIPTION: MID 42 TID B1 test threshold max                     */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_42_TID_B1_TstThshMax(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetEOSD_I_E_12_CurrentTestMax();
}

#endif
/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_A2_TID_0B_TstRslt()                      */
/* DESCRIPTION: MID A2 TID 0B test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_A2_TID_0B_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetMISF_Cyl1_MF_EWMA_Cts_TstData();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_A2_TID_0C_TstRslt()                      */
/* DESCRIPTION: MID A2 TID 0C test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_A2_TID_0C_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetMISF_Cyl1_MF_Counts_TstData();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_A3_TID_0B_TstRslt()                      */
/* DESCRIPTION: MID A3 TID 0B test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_A3_TID_0B_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetMISF_Cyl2_MF_EWMA_Cts_TstData();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_A3_TID_0C_TstRslt()                      */
/* DESCRIPTION: MID A3 TID 0C test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_A3_TID_0C_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetMISF_Cyl2_MF_Counts_TstData();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_A4_TID_0B_TstRslt()                      */
/* DESCRIPTION: MID A4 TID 0B test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_A4_TID_0B_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetMISF_Cyl3_MF_EWMA_Cts_TstData();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_A4_TID_0C_TstRslt()                      */
/* DESCRIPTION: MID A4 TID 0C test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_A4_TID_0C_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetMISF_Cyl3_MF_Counts_TstData();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_A5_TID_0B_TstRslt()                      */
/* DESCRIPTION: MID A5 TID 0B test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_A5_TID_0B_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetMISF_Cyl4_MF_EWMA_Cts_TstData();
}

/*********************************************************************/
/* FUNCTION:    GetDCAN_MID_A5_TID_0C_TstRslt()                      */
/* DESCRIPTION: MID A5 TID 0C test result                            */
/* TYPE       : T_COUNT_WORD                                         */
/* PARAMETERS:  (void*)                                              */
/*                                                                   */
/* RETURN:      None                                                 */
/*********************************************************************/
static void GetDCAN_MID_A5_TID_0C_TstRslt(void* LpDCAN_Output)
{
   *((T_COUNT_WORD*)LpDCAN_Output) = GetMISF_Cyl4_MF_Counts_TstData();
}

/*********************************************************************/
/*            CONSTANTS DEFS                                         */
/*********************************************************************/
/*********************************************************
* This is the list of supported MIDs                     *
* IMPORTANT : Supported Ranges 00,20,40,60,80,A0,C0,E0   *
*             must be ONLY included in the table if      *
*             there are MIDs supported in the respective *
*             range                                      *
*********************************************************/
const TsDCAN_MID_DEFINITION_ARRAY_TYPE CaDCAN_Supported_MIDs[] =
{
   /******************************************************************
   *     MID Num        Number Of TIDs  Attributes                   *
   ******************************************************************/
   {     CeDCAN_MID_00,       0,        CaDCAN_MID_NO_TID_Attributes },
#ifdef OBD_CONTROLLER_IS_MT80
   {     CeDCAN_MID_01,       7,        CaDCAN_MID_01_TID_Attributes },
 #if XeSYST_EOSD_12_SENSOR == CeSYST_EOSD_SENSOR_PRESENT
   {     CeDCAN_MID_02,       8,        CaDCAN_MID_02_TID_Attributes },
 #endif
 #if XeSYST_EOSD_21_SENSOR == CeSYST_EOSD_SENSOR_PRESENT
   {     CeDCAN_MID_05,       7,        CaDCAN_MID_05_TID_Attributes },
 #endif
#else
   CaEXSD_RSP_B1S1_MID
 #if XeSYST_EOSD_12_SENSOR == CeSYST_EOSD_SENSOR_PRESENT
   {     CeDCAN_MID_02,       4,        CaDCAN_MID_02_TID_Attributes },
 #endif
   CaEXSD_RSP_B2S1_MID
#endif
   {     CeDCAN_MID_20,       0,        CaDCAN_MID_NO_TID_Attributes },
   {     CeDCAN_MID_21,       1,        CaDCAN_MID_21_TID_Attributes },
#if XeSYST_EXHAUST_CONFIGURATION == CeSYST_DUAL_BANK_DUAL_CATALYST
   {     CeDCAN_MID_22,       1,        CaDCAN_MID_22_TID_Attributes },
#endif
   {     CeDCAN_MID_40,       0,        CaDCAN_MID_NO_TID_Attributes },
#ifdef OBD_CONTROLLER_IS_MT80
   {     CeDCAN_MID_41,       1,        CaDCAN_MID_41_TID_Attributes },
 #if XeSYST_EOSD_12_SENSOR == CeSYST_EOSD_SENSOR_PRESENT
   {     CeDCAN_MID_42,       1,        CaDCAN_MID_42_TID_Attributes },
 #endif
#else
   CaEXSD_HTR_B1S1_MID
   CaEXSD_HTR_B1S2_MID   
   CaEXSD_HTR_B2S1_MID
   CaEXSD_HTR_B2S2_MID
#endif
   {     CeDCAN_MID_60,       0,        CaDCAN_MID_NO_TID_Attributes },
   {     CeDCAN_MID_80,       0,        CaDCAN_MID_NO_TID_Attributes },
   {     CeDCAN_MID_A0,       0,        CaDCAN_MID_NO_TID_Attributes },
   {     CeDCAN_MID_A2,       2,        CaDCAN_MID_A2_TID_Attributes },
   {     CeDCAN_MID_A3,       2,        CaDCAN_MID_A3_TID_Attributes },
   {     CeDCAN_MID_A4,       2,        CaDCAN_MID_A4_TID_Attributes },
   {     CeDCAN_MID_A5,       2,        CaDCAN_MID_A5_TID_Attributes }
};

/* Number of Supported MIDs */
const BYTE CyDCAN_NumOf_MIDs =
      (sizeof( CaDCAN_Supported_MIDs ) /
       sizeof( TsDCAN_MID_DEFINITION_ARRAY_TYPE ));

/**********************************************************
* Table Name  : CaDCAN_MID_NO_TID_Attributes              *
* Description : This is the default table when no TIDs    *
*               are supported                             *
**********************************************************/
const TsDCAN_MID_TID_AttrType CaDCAN_MID_NO_TID_Attributes[] =
{
    {
        CeDCAN_No_TID,                  /* TID NUMBER */
        CeDGDM_NoFault,                 /* TID NUMBER */
        GetDCAN_Dflt_Parameter,         /* PARAMETER */
        GetDCAN_Dflt_TestMin_Val,       /* MINIMUM THRESHOLD */
        GetDCAN_Dflt_TestMax_Val,       /* MAXIMUM THRESHOLD */
        CeDCAN_NO_SCID                  /* SCALING ID */
    }
};

#ifdef OBD_CONTROLLER_IS_MT80
/**********************************************************
* Table Name  : CaDCAN_MID_01_TID_Attributes              *
* Description : This table contains all the information   *
*               for MID 01 and their TIDS                 *
**********************************************************/
const TsDCAN_MID_TID_AttrType CaDCAN_MID_01_TID_Attributes[] =
{
    /* TID CeDCAN_TID_03 */
    {
        CeDCAN_TID_03,                    /* TID NUMBER */
        CeDGDM_NoFault,                   /* DTC NUMBER */
        GetDCAN_MID_01_TID_03_TstRslt,    /* PARAMETER */
        GetDCAN_MID_01_TID_03_TstThshMin, /* MINIMUM THRESHOLD */
        GetDCAN_MID_01_TID_03_TstThshMax, /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_0A                    /* SCALING ID */
    },
    /* TID CeDCAN_TID_04 */
    {
        CeDCAN_TID_04,                    /* TID NUMBER */
        CeDGDM_NoFault,                   /* DTC NUMBER */
        GetDCAN_MID_01_TID_04_TstRslt,    /* PARAMETER */
        GetDCAN_MID_01_TID_04_TstThshMin, /* MINIMUM THRESHOLD */
        GetDCAN_MID_01_TID_04_TstThshMax, /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_0A                    /* SCALING ID */
    },
    /* TID CeDCAN_TID_05 */
    {
        CeDCAN_TID_05,                    /* TID NUMBER */
        CeDGDM_O2_11_Response,            /* DTC NUMBER */
        GetDCAN_MID_01_TID_05_TstRslt,    /* PARAMETER */
        GetDCAN_MID_01_TID_05_TstThshMin, /* MINIMUM THRESHOLD */
        GetDCAN_MID_01_TID_05_TstThshMax, /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_10                    /* SCALING ID */
    },
    /* TID CeDCAN_TID_06 */
    {
        CeDCAN_TID_06,                    /* TID NUMBER */
        CeDGDM_O2_11_Response,            /* DTC NUMBER */
        GetDCAN_MID_01_TID_06_TstRslt,    /* PARAMETER */
        GetDCAN_MID_01_TID_06_TstThshMin, /* MINIMUM THRESHOLD */
        GetDCAN_MID_01_TID_06_TstThshMax, /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_10                    /* SCALING ID */
    },
    /* TID CeDCAN_TID_81 */
    {
        CeDCAN_TID_81,                    /* TID NUMBER */
        CeDGDM_O2_11_Response,            /* DTC NUMBER */
        GetDCAN_MID_01_TID_81_TstRslt,    /* PARAMETER */
        GetDCAN_MID_01_TID_81_TstThshMin, /* MINIMUM THRESHOLD */
        GetDCAN_MID_01_TID_81_TstThshMax, /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_2B                    /* SCALING ID */
    },
    /* TID CeDCAN_TID_82 */
    {
        CeDCAN_TID_82,                    /* TID NUMBER */
        CeDGDM_O2_11_Response,            /* DTC NUMBER */
        GetDCAN_MID_01_TID_82_TstRslt,    /* PARAMETER */
        GetDCAN_MID_01_TID_82_TstThshMin, /* MINIMUM THRESHOLD */
        GetDCAN_MID_01_TID_82_TstThshMax, /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_2B,                   /* SCALING ID */
    },
    /* TID CeDCAN_TID_83 */
    {
        CeDCAN_TID_83,                    /* TID NUMBER */
        CeDGDM_O2_11_Response,            /* DTC NUMBER */
        GetDCAN_MID_01_TID_83_TstRslt,    /* PARAMETER */
        GetDCAN_MID_01_TID_83_TstThshMin, /* MINIMUM THRESHOLD */
        GetDCAN_MID_01_TID_83_TstThshMax, /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_20                    /* SCALING ID */
    }
};
#endif

#if XeSYST_EOSD_12_SENSOR == CeSYST_EOSD_SENSOR_PRESENT
/**********************************************************
* Table Name  : CaDCAN_MID_02_TID_Attributes              *
* Description : This table contains all the information   *
*               for MID 02 and their TIDS                 *
**********************************************************/
const TsDCAN_MID_TID_AttrType CaDCAN_MID_02_TID_Attributes[] =
{
    /* TID CeDCAN_TID_03 */
    {
        CeDCAN_TID_03,                    /* TID NUMBER */
        CeDGDM_NoFault,                   /* DGDM ENUMERATION INDEX */
        GetDCAN_MID_02_TID_03_TstRslt,    /* PARAMETER */
        GetDCAN_MID_02_TID_03_TstThshMin, /* MINIMUM THRESHOLD */
        GetDCAN_MID_02_TID_03_TstThshMax, /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_0A                    /* SCALING ID */
    },
    /* TID CeDCAN_TID_04 */
    {
        CeDCAN_TID_04,                    /* TID NUMBER */
        CeDGDM_NoFault,                   /* DGDM ENUMERATION INDEX */
        GetDCAN_MID_02_TID_04_TstRslt,    /* PARAMETER */
        GetDCAN_MID_02_TID_04_TstThshMin, /* MINIMUM THRESHOLD */
        GetDCAN_MID_02_TID_04_TstThshMax, /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_0A                    /* SCALING ID */
    },
    /* TID CeDCAN_TID_05 */
    {
        CeDCAN_TID_05,                    /* TID NUMBER */
        CeDGDM_O2_12_DFCO_TimeResp,       /* DGDM ENUMERATION INDEX */
        GetDCAN_MID_02_TID_05_TstRslt,    /* PARAMETER */
        GetDCAN_MID_02_TID_05_TstThshMin, /* MINIMUM THRESHOLD */
        GetDCAN_MID_02_TID_05_TstThshMax, /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_10                    /* SCALING ID */
    },
    /* TID CeDCAN_TID_06 */
    {
        CeDCAN_TID_06,                    /* TID NUMBER */
        CeDGDM_O2_12_PE_RespRate,         /* DGDM ENUMERATION INDEX */
        GetDCAN_MID_02_TID_06_TstRslt,    /* PARAMETER */
        GetDCAN_MID_02_TID_06_TstThshMin, /* MINIMUM THRESHOLD */
        GetDCAN_MID_02_TID_06_TstThshMax, /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_10                    /* SCALING ID */
    }
   #ifdef OBD_CONTROLLER_IS_MT80
     ,
    /* TID CeDCAN_TID_BA */
    {
        CeDCAN_TID_BA,                    /* TID NUMBER */
        CeDGDM_O2_12_Response,            /* DGDM ENUMERATION INDEX */
        GetDCAN_MID_02_TID_BA_TstRslt,    /* PARAMETER */
        GetDCAN_MID_02_TID_BA_TstThshMin, /* MINIMUM THRESHOLD */
        GetDCAN_MID_02_TID_BA_TstThshMax, /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_0A                    /* SCALING ID */
    },
    /* TID CeDCAN_TID_BB */
    {
        CeDCAN_TID_BB,                    /* TID NUMBER */
        CeDGDM_O2_12_Response,            /* DGDM ENUMERATION INDEX */
        GetDCAN_MID_02_TID_BB_TstRslt,    /* PARAMETER */
        GetDCAN_MID_02_TID_BB_TstThshMin, /* MINIMUM THRESHOLD */
        GetDCAN_MID_02_TID_BB_TstThshMax, /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_0A                    /* SCALING ID */
    },
    /* TID CeDCAN_TID_BC */
    {
        CeDCAN_TID_BC,                    /* TID NUMBER */
        CeDGDM_O2_12_Response,            /* DGDM ENUMERATION INDEX */
        GetDCAN_MID_02_TID_BC_TstRslt,    /* PARAMETER */
        GetDCAN_MID_02_TID_BC_TstThshMin, /* MINIMUM THRESHOLD */
        GetDCAN_MID_02_TID_BC_TstThshMax, /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_10                    /* SCALING ID */
    },
    /* TID CeDCAN_TID_BD */
    {
        CeDCAN_TID_BD,                    /* TID NUMBER */
        CeDGDM_O2_12_Response,            /* DGDM ENUMERATION INDEX */
        GetDCAN_MID_02_TID_BD_TstRslt,    /* PARAMETER */
        GetDCAN_MID_02_TID_BD_TstThshMin, /* MINIMUM THRESHOLD */
        GetDCAN_MID_02_TID_BD_TstThshMax, /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_10                    /* SCALING ID */
    }
   #endif
};
#endif
#ifdef OBD_CONTROLLER_IS_MT80
#if XeSYST_EOSD_21_SENSOR == CeSYST_EOSD_SENSOR_PRESENT
/**********************************************************
* Table Name  : CaDCAN_MID_05_TID_Attributes              *
* Description : This table contains all the information   *
*               for MID 05 and their TIDS                 *
**********************************************************/
const TsDCAN_MID_TID_AttrType CaDCAN_MID_05_TID_Attributes[] =
{
    /* TID CeDCAN_TID_03 */
    {
        CeDCAN_TID_03,                    /* TID NUMBER */
        CeDGDM_NoFault,                   /* DTC NUMBER */
        GetDCAN_MID_05_TID_03_TstRslt,    /* PARAMETER */
        GetDCAN_MID_05_TID_03_TstThshMin, /* MINIMUM THRESHOLD */
        GetDCAN_MID_05_TID_03_TstThshMax, /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_0A                    /* SCALING ID */
    },
    /* TID CeDCAN_TID_04 */
    {
        CeDCAN_TID_04,                    /* TID NUMBER */
        CeDGDM_NoFault,                   /* DTC NUMBER */
        GetDCAN_MID_05_TID_04_TstRslt,    /* PARAMETER */
        GetDCAN_MID_05_TID_04_TstThshMin, /* MINIMUM THRESHOLD */
        GetDCAN_MID_05_TID_04_TstThshMax, /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_0A                    /* SCALING ID */
    },
    /* TID CeDCAN_TID_05 */
    {
        CeDCAN_TID_05,                    /* TID NUMBER */
        CeDGDM_O2_21_Response,            /* DTC NUMBER */
        GetDCAN_MID_05_TID_05_TstRslt,    /* PARAMETER */
        GetDCAN_MID_05_TID_05_TstThshMin, /* MINIMUM THRESHOLD */
        GetDCAN_MID_05_TID_05_TstThshMax, /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_10                    /* SCALING ID */
    },
    /* TID CeDCAN_TID_06 */
    {
        CeDCAN_TID_06,                    /* TID NUMBER */
        CeDGDM_O2_21_Response,            /* DTC NUMBER */
        GetDCAN_MID_05_TID_06_TstRslt,    /* PARAMETER */
        GetDCAN_MID_05_TID_06_TstThshMin, /* MINIMUM THRESHOLD */
        GetDCAN_MID_05_TID_06_TstThshMax, /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_10                    /* SCALING ID */
    },
    /* TID CeDCAN_TID_81 */
    {
        CeDCAN_TID_81,                      /* TID NUMBER */
        CeDGDM_O2_21_Response,              /* DTC NUMBER */
        GetDCAN_MID_05_TID_81_TstRslt,      /* PARAMETER */
        GetDCAN_MID_05_TID_81_TstThshMin,   /* MINIMUM THRESHOLD */
        GetDCAN_MID_05_TID_81_TstThshMax,   /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_2B                      /* SCALING ID */
    },
    /* TID CeDCAN_TID_82 */
    {
        CeDCAN_TID_82,                      /* TID NUMBER */
        CeDGDM_O2_21_Response,              /* DTC NUMBER */
        GetDCAN_MID_05_TID_82_TstRslt,      /* PARAMETER */
        GetDCAN_MID_05_TID_82_TstThshMin,   /* MINIMUM THRESHOLD */
        GetDCAN_MID_05_TID_82_TstThshMax,   /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_2B                      /* SCALING ID */
    },
    /* TID CeDCAN_TID_83 */
    {
        CeDCAN_TID_83,                      /* TID NUMBER */
        CeDGDM_O2_21_Response,              /* DTC NUMBER */
        GetDCAN_MID_05_TID_83_TstRslt,      /* PARAMETER */
        GetDCAN_MID_05_TID_83_TstThshMin,   /* MINIMUM THRESHOLD */
        GetDCAN_MID_05_TID_83_TstThshMax,   /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_20                      /* SCALING ID */
    }
};
#endif
#endif

/**********************************************************
* Table Name  : CaDCAN_MID_21_TID_Attributes              *
* Description : This table contains all the information   *
*               for MID 21 and their TIDS                 *
**********************************************************/
const TsDCAN_MID_TID_AttrType CaDCAN_MID_21_TID_Attributes[] =
{
    /* TID CeDCAN_TID_A1 */
    {
        CeDCAN_TID_A1,                      /* TID NUMBER */
        CeDGDM_CatalystBank1,               /* DTC NUMBER */
        GetDCAN_MID_21_TID_A1_TstRslt,      /* PARAMETER */
        GetDCAN_MID_21_TID_A1_TstThshMin,   /* MINIMUM THRESHOLD */
        GetDCAN_MID_21_TID_A1_TstThshMax,   /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_10                      /* SCALING ID */
    }
};

#if XeSYST_EXHAUST_CONFIGURATION == CeSYST_DUAL_BANK_DUAL_CATALYST
/**********************************************************
* Table Name  : CaDCAN_MID_22_TID_Attributes              *
* Description : This table contains all the information   *
*               for MID 22 and their TIDS                 *
**********************************************************/
const TsDCAN_MID_TID_AttrType CaDCAN_MID_22_TID_Attributes[] =
{
    /* TID CeDCAN_TID_A2 */
    {
        CeDCAN_TID_A2,                      /* TID NUMBER */
        CeDGDM_CatalystBank2,               /* DTC NUMBER */
        GetDCAN_MID_22_TID_A2_TstRslt,      /* PARAMETER */
        GetDCAN_MID_22_TID_A2_TstThshMin,   /* MINIMUM THRESHOLD */
        GetDCAN_MID_22_TID_A2_TstThshMax,   /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_10                      /* SCALING ID */
    }
};
#endif

#ifdef OBD_CONTROLLER_IS_MT80
/**********************************************************
* Table Name  : CaDCAN_MID_41_TID_Attributes              *
* Description : This table contains all the information   *
*               for MID 41 and their TIDS                 *
**********************************************************/
const TsDCAN_MID_TID_AttrType CaDCAN_MID_41_TID_Attributes[] =
{
    /* TID CeDCAN_TID_B1 */
    {
        CeDCAN_TID_B1,                        /* TID NUMBER */
        CeDGDM_O2_11_Heater,                  /* DGDM ENUMERATION INDEX */
        GetDCAN_MID_41_TID_B1_TstThshResult,  /* PARAMETER */
        GetDCAN_MID_41_TID_B1_TstThshMin,     /* MINIMUM THRESHOLD */
        GetDCAN_MID_41_TID_B1_TstThshMax,     /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_0E                        /* SCALING ID */
    }
};

#if XeSYST_EOSD_12_SENSOR == CeSYST_EOSD_SENSOR_PRESENT
/**********************************************************
* Table Name  : CaDCAN_MID_42_TID_Attributes              *
* Description : This table contains all the information   *
*               for MID 42 and their TIDS                 *
**********************************************************/
const TsDCAN_MID_TID_AttrType CaDCAN_MID_42_TID_Attributes[] =
{
    /* TID CeDCAN_TID_B1 */
    {
        CeDCAN_TID_B1,                      /* TID NUMBER */
        CeDGDM_O2_12_Heater,                  /* DGDM ENUMERATION INDEX */
        GetDCAN_MID_42_TID_B1_TstThshResult,  /* PARAMETER */
        GetDCAN_MID_42_TID_B1_TstThshMin,     /* MINIMUM THRESHOLD */
        GetDCAN_MID_42_TID_B1_TstThshMax,     /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_0E                      /* SCALING ID */
    }
};
#endif
#endif

/**********************************************************
* Table Name  : CaDCAN_MID_A2_TID_Attributes              *
* Description : This table contains all the information   *
*               for MID A2 and their TIDS                 *
**********************************************************/
const TsDCAN_MID_TID_AttrType CaDCAN_MID_A2_TID_Attributes[] =
{
    /* TID CeDCAN_TID_0B */
    {
        CeDCAN_TID_0B,                      /* TID NUMBER */
        CeDGDM_Misfire,                     /* DTC NUMBER */
        GetDCAN_MID_A2_TID_0B_TstRslt,      /* PARAMETER */
        GetDCAN_Dflt_TestMin_Val,           /* MINIMUM THRESHOLD */
        GetDCAN_Dflt_TestMax_Val,           /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_24                      /* SCALING ID */
    },
    /* TID CeDCAN_TID_0C */
    {
        CeDCAN_TID_0C,                      /* TID NUMBER */
        CeDGDM_Misfire,                     /* DTC NUMBER */
        GetDCAN_MID_A2_TID_0C_TstRslt,      /* PARAMETER */
        GetDCAN_Dflt_TestMin_Val,           /* MINIMUM THRESHOLD */
        GetDCAN_Dflt_TestMax_Val,           /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_24                      /* SCALING ID */
    }
};

/**********************************************************
* Table Name  : CaDCAN_MID_A3_TID_Attributes              *
* Description : This table contains all the information   *
*               for MID A3 and their TIDS                 *
**********************************************************/
const TsDCAN_MID_TID_AttrType CaDCAN_MID_A3_TID_Attributes[] =
{
    /* TID CeDCAN_TID_0B */
    {
        CeDCAN_TID_0B,                      /* TID NUMBER */
        CeDGDM_Misfire,                     /* DTC NUMBER */
        GetDCAN_MID_A3_TID_0B_TstRslt,      /* PARAMETER */
        GetDCAN_Dflt_TestMin_Val,           /* MINIMUM THRESHOLD */
        GetDCAN_Dflt_TestMax_Val,           /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_24                      /* SCALING ID */
    },
    /* TID CeDCAN_TID_0C */
    {
        CeDCAN_TID_0C,                      /* TID NUMBER */
        CeDGDM_Misfire,                     /* DTC NUMBER */
        GetDCAN_MID_A3_TID_0C_TstRslt,      /* PARAMETER */
        GetDCAN_Dflt_TestMin_Val,           /* MINIMUM THRESHOLD */
        GetDCAN_Dflt_TestMax_Val,           /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_24                      /* SCALING ID */
    }
};

/**********************************************************
* Table Name  : CaDCAN_MID_A4_TID_Attributes              *
* Description : This table contains all the information   *
*               for MID A4 and their TIDS                 *
**********************************************************/
const TsDCAN_MID_TID_AttrType CaDCAN_MID_A4_TID_Attributes[] =
{
    /* TID CeDCAN_TID_0B */
    {
        CeDCAN_TID_0B,                      /* TID NUMBER */
        CeDGDM_Misfire,                     /* DTC NUMBER */
        GetDCAN_MID_A4_TID_0B_TstRslt,      /* PARAMETER */
        GetDCAN_Dflt_TestMin_Val,           /* MINIMUM THRESHOLD */
        GetDCAN_Dflt_TestMax_Val,           /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_24                      /* SCALING ID */
    },
    /* TID CeDCAN_TID_0C */
    {
        CeDCAN_TID_0C,                      /* TID NUMBER */
        CeDGDM_Misfire,                     /* DTC NUMBER */
        GetDCAN_MID_A4_TID_0C_TstRslt,      /* PARAMETER */
        GetDCAN_Dflt_TestMin_Val,           /* MINIMUM THRESHOLD */
        GetDCAN_Dflt_TestMax_Val,           /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_24                      /* SCALING ID */
    }
};

/**********************************************************
* Table Name  : CaDCAN_MID_A5_TID_Attributes              *
* Description : This table contains all the information   *
*               for MID A5 and their TIDS                 *
**********************************************************/
const TsDCAN_MID_TID_AttrType CaDCAN_MID_A5_TID_Attributes[] =
{
    /* TID CeDCAN_TID_0B */
    {
        CeDCAN_TID_0B,                      /* TID NUMBER */
        CeDGDM_Misfire,                     /* DTC NUMBER */
        GetDCAN_MID_A5_TID_0B_TstRslt,      /* PARAMETER */
        GetDCAN_Dflt_TestMin_Val,           /* MINIMUM THRESHOLD */
        GetDCAN_Dflt_TestMax_Val,           /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_24                      /* SCALING ID */
    },
    /* TID CeDCAN_TID_0C */
    {
        CeDCAN_TID_0C,                      /* TID NUMBER */
        CeDGDM_Misfire,                     /* DTC NUMBER */
        GetDCAN_MID_A5_TID_0C_TstRslt,      /* PARAMETER */
        GetDCAN_Dflt_TestMin_Val,           /* MINIMUM THRESHOLD */
        GetDCAN_Dflt_TestMax_Val,           /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_24                      /* SCALING ID */
    }
};
#if 0
/**********************************************************
* Table Name  : CaDCAN_MID_A6_TID_Attributes              *
* Description : This table contains all the information   *
*               for MID A6 and their TIDS                 *
**********************************************************/
const TsDCAN_MID_TID_AttrType CaDCAN_MID_A6_TID_Attributes[] =
{
    /* TID CeDCAN_TID_0B */
    {
        CeDCAN_TID_0B,                      /* TID NUMBER */
        CeDGDM_Misfire,                     /* DTC NUMBER */
        GetDCAN_MID_A6_TID_0B_TstRslt,      /* PARAMETER */
        GetDCAN_Dflt_TestMin_Val,           /* MINIMUM THRESHOLD */
        GetDCAN_Dflt_TestMax_Val,           /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_24                      /* SCALING ID */
    },
    /* TID CeDCAN_TID_0C */
    {
        CeDCAN_TID_0C,                      /* TID NUMBER */
        CeDGDM_Misfire,                     /* DTC NUMBER */
        GetDCAN_MID_A6_TID_0C_TstRslt,      /* PARAMETER */
        GetDCAN_Dflt_TestMin_Val,           /* MINIMUM THRESHOLD */
        GetDCAN_Dflt_TestMax_Val,           /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_24                      /* SCALING ID */
    }
};

/**********************************************************
* Table Name  : CaDCAN_MID_A7_TID_Attributes              *
* Description : This table contains all the information   *
*               for MID A7 and their TIDS                 *
**********************************************************/
const TsDCAN_MID_TID_AttrType CaDCAN_MID_A7_TID_Attributes[] =
{
    /* TID CeDCAN_TID_0B */
    {
        CeDCAN_TID_0B,                      /* TID NUMBER */
        CeDGDM_Misfire,                     /* DTC NUMBER */
        GetDCAN_MID_A7_TID_0B_TstRslt,      /* PARAMETER */
        GetDCAN_Dflt_TestMin_Val,           /* MINIMUM THRESHOLD */
        GetDCAN_Dflt_TestMax_Val,           /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_24                      /* SCALING ID */
    },
    /* TID CeDCAN_TID_0C */
    {
        CeDCAN_TID_0C,                      /* TID NUMBER */
        CeDGDM_Misfire,                     /* DTC NUMBER */
        GetDCAN_MID_A7_TID_0C_TstRslt,      /* PARAMETER */
        GetDCAN_Dflt_TestMin_Val,           /* MINIMUM THRESHOLD */
        GetDCAN_Dflt_TestMax_Val,           /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_24                      /* SCALING ID */
    }
};

/**********************************************************
* Table Name  : CaDCAN_MID_E1_TID_Attributes              *
* Description : This table contains all the information   *
*               for MID E1 and their TIDS                 *
**********************************************************/
const TsDCAN_MID_TID_AttrType CaDCAN_MID_E1_TID_Attributes[] =
{
    /* TID CeDCAN_TID_80 */
    {
        CeDCAN_TID_80,                        /* TID NUMBER */
        CeDGDM_EVPD_RestrictedVentPath,       /* DTC NUMBER */
        GetDCAN_MID_E1_TID_80_TstRslt,        /* PARAMETER */
        GetDCAN_MID_E1_TID_80_TstThshMin,     /* MINIMUM THRESHOLD */
        GetDCAN_MID_E1_TID_80_TstThshMax,     /* MAXIMUM THRESHOLD */
        CeDCAN_SCID_FE                        /* SCALING ID */
    }
};
#endif
/******************************************************************************
 *  Function Definitions
 *****************************************************************************/

#endif
/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.0   050111 ban xxxx Created module.
* 1.1   050912 ban xxxx Added: GetDCAN_MID_A2_TID_0C_TstRslt
*                              GetDCAN_MID_A2_TID_0B_TstRslt
*                              GetDCAN_MID_A3_TID_0B_TstRslt
*                              GetDCAN_MID_A3_TID_0C_TstRslt
*                              GetDCAN_MID_A4_TID_0B_TstRslt
*                              GetDCAN_MID_A4_TID_0C_TstRslt
*                              GetDCAN_MID_A5_TID_0B_TstRslt
*                              GetDCAN_MID_A5_TID_0C_TstRslt
*                              GetDCAN_MID_A6_TID_0B_TstRslt
*                              GetDCAN_MID_A6_TID_0C_TstRslt
*                              GetDCAN_MID_A7_TID_0B_TstRslt
*                              GetDCAN_MID_A7_TID_0C_TstRslt
* 3     060310 hdb 5378 EOSD corrections to USID for MID 01/05 TID 83
*
* 1.2   060403 tln 5601 Added missing MIDs 0x40, 0x60, 0x80, 0xC0
* 4.0   060407 caw -BM- Merge
* tci_pt3#2
*      070503  AB  xxxx Removed MID 3C TID 82
*                       Added TID 80 in MID 3D .
*
******************************************************************************/
/************************************************************************
*                                                                      *
* Change Log: GMDAT MT80 J300                                          *
*                                                                      *
* Rev.    Date    User RSM#  Description of Changes                    *
* ----  --------  ---- ----  ------------------------------------------*
* 1      070629   abh  6023  Added to implement DG services for J300
* tci_pt3#2
*        080403   VP   6833  Added MID 31, TID-91.
* kok_pt2#2
*        110719   cjk  7640  Update Exhaust Sensor Diagnostic (EXSD)
*                      8907   interface
* 4      111104   cjqq  9487  Remove CeDGDM_O2_12_Response.

* 5      120307   cjqq  xxxx  MT80 and MT92 obd integrate.
***********************************************************************/

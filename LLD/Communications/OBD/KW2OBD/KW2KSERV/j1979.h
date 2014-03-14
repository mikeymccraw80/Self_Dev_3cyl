#ifndef J1979
#define J1979
/***********************************************************************
*  DELCO ELECTRONICS CORPORATION, INC.                                 *
*  COPYRIGHT 1999 DELCO ELECTRONICS CORPORATION, INC.                  *
*  ALL RIGHTS RESERVED                                                 *
*  This program may not be reproduced, in whole or in part in any form *
*  or by any means whatsoever without the written permission of:       *
*                                                                      *
*         DELCO ELECTRONICS CORPORATION                                *
*         One Corporate Center                                         *
*         Kokomo, Indiana  46904-9005                                  *
*         USA                                                          *
*                                                                      *
************************************************************************
* Filename     : j1979.h                                               *
*                                                                      *
* Project Name : Common J1979                                          *
*                                                                      *
* Applicable   :                                                       *
* Documents                                                            *
*                                                                      *
* Version      :                                                       *
*                                                                      *
* Purpose      : Create interface variables for Keyword J1979 message  *
*                handling                                              *
*                                                                      *
* Description  :                                                       *
*                                                                      *
************************************************************************
* $Source: ems_project@brighton.tcb:gmdat05:j1979.h $
* $Revision: 1.2 $
* $Author: brighton.tcb:/ems/users/nz35qp/dsds/jincho:nz35qp $
************************************************************************
*                                                                      *
* Change Log:                                                          *
*                                                                      *
* Rev.  Date     Who  Description of Changes                           *
* ---- --------  ---- -------------------------------------------------*
* 1.01  11 Aug 97 TLP  Added ifndef,source/rev,changelog,compile check *
* 1.1   03-23-98  CDW     Created from Lansing 2000 code  SCR05083645  *
* 1.1   10-15-98  cdw     New version created from Daewoo delivery     *
* 1.5   11-15-98  cdw     Fixed and reduce function code               *
* 1.6   02-10-98  cdw     Fixed and reduce function code               *
* 1.7   10-04-99  HFU     Removed TestID 06 in SID06 in Daewoo Project.*
* 1.8   03-31-00  bdt     Removed SID08 from T-150 project.            *
* 1.9   05-24-00  hfu     Removed SID 06, TestID_07, CompID_4Cin Gas  *
*                         Application from T150..                      *
************************************************************************
* GMDAT 2005 Partition and Node                                        *
************************************************************************
* 1.1   041021 kmf 4585  Changed name of CeTestID_0ACompID_03 to
*                        CeTestID_0ACompID_83
* 1.2   041025 kmf 4585  Changed name of CeTestID_04CompID_60 to
*                        CeTestID_04CompID_E0
************************************************************************
*/
#include "t_base.h"
#include "t_user.h"
#include "kw2type.h"



/*********************************************************************/
/*          TYPEDEFS                                                 */
/*********************************************************************/



#define Cy1979_PID00             0x00
#define Cy1979_PID01              0x01
#define Cy1979_PID02             0x02
#define Cy1979_PID03             0x03
#define Cy1979_PID04             0x04
#define Cy1979_PID05             0x05
#define Cy1979_PID06             0x06
#define Cy1979_PID07              0x07
#define Cy1979_PID08             0x08
#define Cy1979_PID09              0x09
#define Cy1979_PID0A             0x0a
#define Cy1979_PID0B              0x0b
#define Cy1979_PID0C             0x0c
#define Cy1979_PID0D              0x0d
#define Cy1979_PID0E             0x0e
#define Cy1979_PID0F             0x0f
#define Cy1979_PID10             0x10
#define Cy1979_PID11              0x11
#define Cy1979_PID12             0x12
#define Cy1979_PID13              0x13
#define Cy1979_PID14             0x14
#define Cy1979_PID15             0x15
#define Cy1979_PID16             0x16
#define Cy1979_PID17              0x17
#define Cy1979_PID18             0x18
#define Cy1979_PID19              0x19
#define Cy1979_PID1A             0x1a
#define Cy1979_PID1B              0x1b
#define Cy1979_PID1C            0x1c
#define Cy1979_PID1D              0x1d
#define Cy1979_PID1E             0x1e
#define Cy1979_PID1F            0x1f
#define Cy1979_PID20            0x20
#define Cy1979_PID21             0x21
#define Cy1979_PID22             0x22
#define Cy1979_PID23              0x23
#define Cy1979_PID24             0x24
#define Cy1979_PID25              0x25
#define Cy1979_PID26             0x26
#define Cy1979_PID27             0x27
#define Cy1979_PID28             0x28
#define Cy1979_PID29              0x29
#define Cy1979_PID2A             0x2a
#define Cy1979_PID2B             0x2b
#define Cy1979_PID2C             0x2c
#define Cy1979_PID2D              0x2d
#define Cy1979_PID2E            0x2e
#define Cy1979_PID2F             0x2f
#define Cy1979_PID30             0x30
#define Cy1979_PID31              0x31
#define Cy1979_PID32             0x32
#define Cy1979_PID33              0x33
#define Cy1979_PID34             0x34
#define Cy1979_PID35              0x35
#define Cy1979_PID36             0x36
#define Cy1979_PID37              0x37
#define Cy1979_PID38             0x38
#define Cy1979_PID39              0x39
#define Cy1979_PID3A             0x3a
#define Cy1979_PID3B              0x3b
#define Cy1979_PID3C             0x3c
#define Cy1979_PID3D             0x3d
#define Cy1979_PID3E             0x3e
#define Cy1979_PID3F             0x3f
#define Cy1979_PID40             0x40
#define Cy1979_PID41              0x41
#define Cy1979_PID42             0x42
#define Cy1979_PID43             0x43
#define Cy1979_PID44             0x44
#define Cy1979_PID45              0x45
#define Cy1979_PID46             0x46
#define Cy1979_PID51             0x51
#define Cy1979_PID5A             0x5A



#define Cy1979_InfoType2             2
#define Cy1979_InfoType3             3
#define Cy1979_InfoType4             4
#define Cy1979_InfoType5             5
#define Cy1979_InfoType6             6
#define Cy1979_InfoType7             7
#define Cy1979_InfoType8             8
#define Cy1979_InfoType9             9

#define Cy1979_InfoType0             0
#define Cy1979_InfoType1             1
#define Cy1979_InfoType2             2
#define Cy1979_InfoType3             3
#define Cy1979_InfoType4             4
#define Cy1979_InfoType5             5
#define Cy1979_InfoType6             6
#define Cy1979_InfoType7             7
#define Cy1979_InfoType8             8
#define Cy1979_InfoType9             9
#define Cy1979_InfoType10             10
#define Cy1979_InfoType11             11
#define Cy1979_InfoType12             12
#define Cy1979_InfoType13             13
#define Cy1979_InfoType14             14
#define Cy1979_InfoType15             15
#define Cy1979_InfoType16             16
#define Cy1979_InfoType17             17
#define Cy1979_InfoType18             18
#define Cy1979_InfoType19             19
#define Cy1979_InfoType20             20
#define Cy1979_InfoType21             21
#define Cy1979_InfoType22             22
#define Cy1979_InfoType23             23
#define Cy1979_InfoType24             24
#define Cy1979_InfoType25             25
#define Cy1979_InfoType26             26
#define Cy1979_InfoType27             27
#define Cy1979_InfoType28             28
#define Cy1979_InfoType29             29
#define Cy1979_InfoType30             30
#define Cy1979_InfoType31             31

#define Cy1979_Mode_49_Data_Length   7
#define Cy1979_InfoType0_MsgCnt      1
#define Cy1979_InfoType_MaxDataCnt   6
#define Cy1979_InfoType_01_BitPosVal 0x80
#define Cy1979_InfoType1_MsgCnt      1
#define Cy1979_InfoType1_DataCnt     2
#define Cy1979_NumOfMsgsToRptVIN     5

#define Cy1979_InfoType_02_BitPosVal 0x40
#define Cy1979_InfoType_03_BitPosVal 0x20
#define Cy1979_InfoType_04_BitPosVal 0x10
#define Cy1979_InfoType_05_BitPosVal 0x08
#define Cy1979_InfoType_06_BitPosVal 0x04
#define Cy1979_NumOfMsgsToRptCalID   4
#define Cy1979_NumOfMsgsToRptCVNs    Cy1979_MaxCalIDs
#define Cy1979_Mode09_MsgNumLoc      1
#define Cy1979_InfoTypeDataIdx       1
#define Cy1979_PerRespMaxChar        4
#define Chk1979_Md9_InfoTypeSupported(LyVal,LyBit) \
      ( ((LyVal & LyBit) == LyBit) ? CbTRUE:CbFALSE )


/*********************************************************************/
/*          GLOBAL FUNCTION PROTOTYPES                               */
/*********************************************************************/
extern void J1979Mode1Handler (void);
extern void J1979Mode2Handler (void);
extern void J1979Mode3Handler (void);
extern void FormJ1979_Mode_43_Data (void);
extern void J1979Mode4Handler (void);
extern void J1979Mode7Handler (void);
extern void FormJ1979_Mode_47_Data (void);
extern void J1979Mode9Handler (void);
extern void FormJ1979_NextMode49(void);

/*                                                                   */
/*-------------------------------------------------------------------*/
/*--- End of file kwj1979.h ---*/

#endif /* KWJ1979_H */

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 *
\* ============================================================================ */


;******************************************************************************
;**                        Copyright (c) 2001 Delphi DE
;**                          All rights reserved.
;**                  Developed under contract by ETAS, Inc.
;**
;** File Name:    convert_code.pri
;** Project:      Delphi EMS_Core ProF Configuration Development
;** File Type:    ProF Configuration File
;** CM ID:
;** Description:  Procedure used to convert the PTP file to binary so it can
;**               be programmed.
;**
;** Revision History: 
;** Date     Engineer   Changes
;** ---------------------------------------------------------------------------
;** 03/20/01 * DLN      Initial release.
;** 04/10/01 * DLN      Removed check, always convert.
;** 03/06/02 * JWD      Added check and convert for Intel Hex files.
;******************************************************************************

procedure convert
{
[con]
  CHECK_FILE_EXTENSION ("%1","HEX")
  case 11 : HEX2PTP
  default : con1
[con_END]

[HEX2PTP]
  DISPLAY_MESSAGE (" Converting Intel Hex File --> S3 S-Record...",FALSE)
  DISPLAY_MESSAGE (" %1",FALSE)
  DISPLAY_MESSAGE (" ",FALSE)
  RUN (INC_P"redir.bat",INC_P"ix2ptp.exe",%1,%1".s19")
  default : con2
[HEX2PTP_END]

[con1]
  DISPLAY_MESSAGE (" Converting S3 S-Record File --> S2 S-Record File...",FALSE)
  DISPLAY_MESSAGE (" %1",FALSE)
  DISPLAY_MESSAGE (" ",FALSE)
  RUN (INC_P"PTPRM.EXE",%1,%1"stripped")
  RUN (INC_P"PTP.EXE",cut,-fill_byte=FF,-replace,-output=ftemp.s19,%1"stripped",FILL_CODE_START_PTP":"FILL_CODE_END_PTP","FILL_CODE_START24,FILL_CAL_START_PTP":"FILL_CAL_END_PTP","FILL_CAL_START24)

   RUN (INC_P"PTP.EXE",format,-replace, -srecord_type=2,-output=%1"tp2",ftemp.s19)
  RUN_DOS ("DEL",ftemp.s19)
  RUN_DOS ("DEL",%1"stripped")
  default : conv
[con1_END]

[con2]
  DISPLAY_MESSAGE (" Converting S3 S-Record File --> S2 S-Record File...",FALSE)
  DISPLAY_MESSAGE (" %1.s19",FALSE)
  DISPLAY_MESSAGE (" ",FALSE)
  RUN (INC_P"PTP.EXE",cut,-fill_byte=00,-output=ftemp.s19,%1,FILL_CODE_START_PTP":"FILL_CODE_END_PTP","FILL_CODE_START24,FILL_CAL_START_PTP":"FILL_CAL_END_PTP","FILL_CAL_START24)
  RUN_DOS ("DEL",%1".s19")
  RUN (INC_P"PTP.EXE",format,-srecord_type=2,%1".remap",-output=%1"tp2")
  RUN_DOS ("DEL",ftemp.s19)
  default : conv
[con2_END]

[conv]
  DISPLAY_MESSAGE (" Converting S2 S-Record File --> Binary File ...",FALSE)
  DISPLAY_MESSAGE (" ",FALSE)
  RUN_DLL ("CONVERT.DLL",convert,-h,-q,-i,-f0xFF,FILL_CODE_START,FILL_CODE_END,TRIM_CODE_START,TRIM_CODE_END,CONV,%1tp2)
  case TRUE : CHECK
  default : $return FALSE
[conv_END]

[CHECK]
  RUN_DOS ("DEL",%1"tp2");
  CHECK_PROGRAMMING_FILE ("%1."EXT, 1)
  case TRUE : $return TRUE
  case WARNING : $return TRUE
  default : $return FALSE
[CHECK_END]
}

;******************************************************************************
;**                  Copyright (c) 2001,2002,2003 Delphi DE
;**                          All rights reserved.
;**                  Developed under contract by ETAS, Inc.
;**
;** File Name:    common.pri
;** Project:      Delphi EMS_Core ProF Configuration Development
;** File Type:    ProF Configuration File
;** Description:  Common defines for the configuration
;******************************************************************************

#define ESCAPE      27
#define WARNING     77
#define ECU_ADDRESS $11
#define EXT         "BIN"
#define CONV        -b

#define INC_P       "C:\$prof\MT22p3_chery_hwio\"
#define CONFIG      "C:\$prof\MT22p3_chery_hwio\MT22p3_chery_hwio.cnf"
#define CONFIG_CODE "C:\$prof\MT22p3_chery_hwio\MT22p3_chery_hwio_code.cnf"
#define CONFIG_CAL  "C:\$prof\MT22p3_chery_hwio\MT22p3_chery_hwio_cal.cnf"
#define CONVERT     "C:\$prof\MT22p3_chery_hwio\convert.exe"
#define GET_KEY     "C:\$prof\MT22p3_chery_hwio\key.dll"

;** Cal sizes
#define FILL_CAL_START_PTP     00020000
#define FILL_CAL_END_PTP       0003FFFF

#define FILL_CAL_START24         020000

#define FILL_CAL_START        -s0x20000
#define FILL_CAL_END          -e0x3FFFF

#define TRIM_CAL_START        -x0x20000
#define TRIM_CAL_END          -y0x3FFFF

;** Code sizes
#define FILL_CODE_START_PTP    00040000
#define FILL_CODE_END_PTP      0017FFFF

#define FILL_CODE_START24        040000

#define FILL_CODE_START      -s0x020000
#define FILL_CODE_END        -e0x17FFFF

#define TRIM_CODE_START      -x0x020000
#define TRIM_CODE_END        -y0x17FFFF

#define FALSE       0
#define TRUE        1
#define OVER_WRITE  3

#define RED_FALSE       $4000
#define BLINK_FALSE     $2000
#define GREEN_FALSE     $6000

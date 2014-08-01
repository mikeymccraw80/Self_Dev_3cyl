echo begin to get chery cal and merge it into build s19
..\tools\utility\ptp.exe cut -output=cal_image.s19 -fillvalue=00 -quiet -replace mt22p3_chery_4cyl_cal.s19 00020004,131064,00020004
..\tools\utility\ptp.exe merge -replace -output=merged_cal.s19 mt22p3_chery_4cyl.s19 cal_image.s19
DEL cal_image.s19
PAUSE
REM ptp.exe dump mt22p3_chery_4cyl_cal.s19 -replace -output=cal_image.s19 -range=00020000,131072
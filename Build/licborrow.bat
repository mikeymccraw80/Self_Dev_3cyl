@echo off

REM echo =================display the current license status =====================
REM lmutil lmborrow -status
REM echo =========================================================================
REM pause

set cur_month=%date:~0,2%
if %cur_month%==01 set month=Jan
if %cur_month%==02 set month=Feb
if %cur_month%==03 set month=Mar
if %cur_month%==04 set month=Apr
if %cur_month%==05 set month=May
if %cur_month%==06 set month=Jun
if %cur_month%==07 set month=Jul
if %cur_month%==08 set month=Aug
if %cur_month%==09 set month=Sep
if %cur_month%==10 set month=Oct
if %cur_month%==11 set month=Nov
if %cur_month%==12 set month=Dec
set day=%date:~3,2%
set year=%date:~6,4%

set line=-
set licdate=%day%%line%%month%%line%%year%
set lichour=%time:~0,2%
set licmin=%time:~2,3%
set /A lichour=%lichour%+12
if %lichour% gtr 23 set lichour=23
echo %licdate% %lichour%%licmin%

echo ================= try to get a new temparory license ====================
REM echo "<command format>: lmborrow wrsd 20-Apr-2013 17:00"
lmutil lmborrow wrsd %licdate% %lichour%%licmin%
call build_HWIO.bat
lmutil lmborrow -status
REM echo =========================================================================

pause
@echo on

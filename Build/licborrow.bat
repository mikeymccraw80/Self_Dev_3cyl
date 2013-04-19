@echo off

echo " display the current license status "
lmutil lmborrow -status
echo +====================================
pause

echo " try to get a new temparory license "

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
REM echo %month%
set day=%date:~3,2%
REM echo %day%
set year=%date:~6,4%
REM echo %year%
REM set lictime=%time:~0,5%
set lictime=23:59
echo %lictime%
set line=-
REM echo %line%

set licdate=%day%%line%%month%%line%%year%
echo %licdate%

lmutil lmborrow wrsd %licdate% %lictime%

REM if %1.==. goto help

REM if exist foo.c del foo.c
REM lmutil lmborrow wrsd %1 %2
REM echo main() > foo.c
REM echo { >> foo.c
REM echo int a; >> foo.c
REM echo } >> foo.c
REM C:\BuildArea\Chery_MT22p3_LLD\tools\diab\WIN32\bin\dcc.exe -tPPCE200Z3NEN:simple foo.c
REM del foo.c
REM if exist c.out del c.out
lmutil lmborrow -status 
REM echo "<command format>: licborrow 20-Apr-2013 17:00"
pause
@echo on

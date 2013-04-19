@echo off

if %1.==. goto help

REM if exist foo.c del foo.c
lmutil lmborrow wrsd %1 %2
REM echo main() > foo.c
REM echo { >> foo.c
REM echo int a; >> foo.c
REM echo } >> foo.c
REM C:\BuildArea\Chery_MT22p3_LLD\tools\diab\WIN32\bin\dcc.exe -tPPCE200Z3NEN:simple foo.c
REM del foo.c
REM if exist c.out del c.out
lmutil lmborrow -status 
goto end

:help
echo "<command format>: licborrow 20-Apr-2013 17:00"
:end
@echo on

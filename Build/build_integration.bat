@echo off
cls
echo +============================================================================+  > build.log
echo .                                                                            . >> build.log
echo .                       Chery MT22p3  C O M P I L E  S T A R T               . >> build.log
echo .                                                                            . >> build.log
echo +============================================================================+ >> build.log

del obj_list.txt

del ..\objs\intr_ems.o
del ..\objs\app_main.o
del ..\objs\intr_var.o

rem The real thing
set TARGET=INTEGRATION
..\tools\utility\gnumake 2>&1 | ..\tools\utility\mtee.exe /t/d/+ build.log
pause


cls
@echo on



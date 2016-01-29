@echo off
cls
echo +============================================================================+  > build.log
echo .                                                                            . >> build.log
echo .                       Chery MT22p3  C O M P I L E  S T A R T               . >> build.log
echo .                                                                            . >> build.log
echo +============================================================================+ >> build.log


del obj_list.txt
del ..\objs\app_main.o
del ..\objs\intr_var.o
del ..\objs\j1939_app.o

rem The real thing
set TARGET=HWIO_LIB
set CYLINDER_APP=3
..\tools\utility\gnumake 2>&1 | ..\tools\utility\mtee.exe /t/d/+ build.log
pause


cls
@echo on



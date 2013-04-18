@echo off
cls
echo +============================================================================+  > build.log
echo .                                                                            . >> build.log
echo .                       Chery MT22p3  C O M P I L E  S T A R T               . >> build.log
echo .                                                                            . >> build.log
echo +============================================================================+ >> build.log


del obj_list.txt

rem The real thing
set TARGET=HWIO_LIB
..\tools\utility\gnumake 2>&1 | ..\tools\utility\mtee.exe /t/d/+ build.log
pause


cls
@echo on



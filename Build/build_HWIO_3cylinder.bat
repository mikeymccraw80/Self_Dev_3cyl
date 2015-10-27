@echo off
cls
echo +============================================================================+  > build.log
echo .                                                                            . >> build.log
echo .                       Chery MT22p3  C O M P I L E  S T A R T               . >> build.log
echo .                                                                            . >> build.log
echo +============================================================================+ >> build.log

del obj_list.txt
del ERROR.err

rem The real thing
set TARGET=HWIO
set ETCSOH=ENABLE
set CYLINDER_APP=3
soh_cfg.exe hwio_with_soh
..\tools\utility\gnumake 2>&1 | ..\tools\utility\mtee.exe /t/d/+ build.log
pause


cls
@echo on



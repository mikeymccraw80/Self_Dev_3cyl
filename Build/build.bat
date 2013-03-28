@echo off
cls
echo +============================================================================+  > build.log
echo .                                                                            . >> build.log
echo .                            D C D C  C O M P I L E  S T A R T               . >> build.log
echo .                                                                            . >> build.log
echo +============================================================================+ >> build.log


del obj_list.txt

rem The real thing
..\tools\utility\gnumake 2>&1 | ..\tools\utility\mtee.exe /t/d/+ build.log
pause


cls
@echo on



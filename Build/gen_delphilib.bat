@echo off
cls
echo +============================================================================+  > build.log
echo .                                                                            . >> build.log
echo .                            B U I L D LIB S T A R T                         . >> build.log
echo .  Build START time                                                          . >> build.log
        time/t >> build.log
echo .                                                                            . >> build.log
echo +============================================================================+ >> build.log

echo +============================================================================+
echo .                                                                            .
echo .                     Building HWIO Chery  LIB                               .
echo .                                     ===========                            .
echo .                     Errors and Messages are redirected.                    .
echo .                                                                            .
echo .                       See readme file to locate files                      .
echo .                                                                            .
echo .  Build START time                                                          .
        time/t
echo .                                                                            .
echo +============================================================================+

rem The real thing
REM set SOFTWARE=

REM md ..\tools\delphilib\outputlib

REM ..\tools\diab\WIN32\bin\dar -r ..\tools\delphilib\outputlib\mt22p3_chery_4cyl.a ..\objs\io_config_cam.o ..\objs\io_config_crank.o ..\objs\io_config_dma.o ..\objs\io_config_dspi.o ..\objs\io_config_flexcan.o ..\objs\io_config_mios.o ..\objs\io_config_mmu.o ..\objs\io_config_qadc.o ..\objs\io_config_siu.o ..\objs\io_config_spark.o ..\objs\io_config_stm.o ..\objs\io_config_tpu.o ..\objs\dd_swt.o ..\objs\dd_fmpll.o ..\objs\dd_mmu.o ..\objs\CFlashDepletionRecover.o ..\objs\cblankcheck.o ..\objs\cchecksum.o ..\objs\cfactorymarginreadcheck.o ..\objs\cflasharrayintegritycheck.o ..\objs\cflashecclogiccheck.o ..\objs\cflasherase.o ..\objs\cflashinit.o ..\objs\cflashprogram.o ..\objs\cflashresume.o ..\objs\cflashsuspend.o ..\objs\cgetlock.o ..\objs\cprogramverify.o ..\objs\csetlock.o ..\objs\dd_c90fl_flash.o ..\objs\dd_c90fl_flash_init.o ..\objs\dd_c90lc_flash.o ..\objs\dd_c90lc_flash_init.o ..\objs\dd_flash_memory_interface.o ..\objs\dd_flash_mpc5634.o ..\objs\dd_flash_mpc5644.o ..\objs\ssd_c90fl_FlashDepletionRecover.o ..\objs\ssd_c90fl_blankcheck.o ..\objs\ssd_c90fl_checksum.o ..\objs\ssd_c90fl_factorymarginreadcheck.o ..\objs\ssd_c90fl_flasharrayintegritycheck.o ..\objs\ssd_c90fl_flashecclogiccheck.o ..\objs\ssd_c90fl_flasherase.o ..\objs\ssd_c90fl_flashinit.o ..\objs\ssd_c90fl_flashprogram.o ..\objs\ssd_c90fl_flashresume.o ..\objs\ssd_c90fl_flashsuspend.o ..\objs\ssd_c90fl_getlock.o ..\objs\ssd_c90fl_programverify.o ..\objs\ssd_c90fl_setlock.o ..\objs\ssd_c90lc_BlankCheck.o ..\objs\ssd_c90lc_CheckSum.o ..\objs\ssd_c90lc_FactoryMarginReadCheck.o ..\objs\ssd_c90lc_FlashArrayIntegrityCheck.o ..\objs\ssd_c90lc_FlashECCLogicCheck.o ..\objs\ssd_c90lc_FlashErase.o ..\objs\ssd_c90lc_FlashInit.o ..\objs\ssd_c90lc_FlashProgram.o ..\objs\ssd_c90lc_FlashResume.o ..\objs\ssd_c90lc_FlashSuspend.o ..\objs\ssd_c90lc_GetLock.o ..\objs\ssd_c90lc_ProgramVerify.o ..\objs\ssd_c90lc_SetLock.o ..\objs\dd_expection.o ..\objs\dd_expection_handler.o ..\objs\dd_intc.o ..\objs\dd_intc_Exception_Alignment.o ..\objs\dd_intc_Exception_Aux_Proc_Unavailable.o ..\objs\dd_intc_Exception_Data_Storage.o ..\objs\dd_intc_Exception_Data_Tlb.o ..\objs\dd_intc_Exception_Debug.o ..\objs\dd_intc_Exception_Decrementer.o ..\objs\dd_intc_Exception_Fixed_Interval_Timer.o ..\objs\dd_intc_Exception_Fp_Unavailable.o ..\objs\dd_intc_Exception_Instruction_Storage.o ..\objs\dd_intc_Exception_Instruction_Tlb.o ..\objs\dd_intc_Exception_Machine_Check.o ..\objs\dd_intc_Exception_Not_Available.o ..\objs\dd_intc_Exception_Program.o ..\objs\dd_intc_Exception_Spe_Apu_Unavail.o ..\objs\dd_intc_Exception_Spe_Fp_Data.o ..\objs\dd_intc_Exception_Spe_Fp_Round.o ..\objs\dd_intc_Exception_System_Call.o ..\objs\dd_intc_Exception_Watchdog.o ..\objs\dd_intc_exception_external.o ..\objs\dd_intc_interrupt.o ..\objs\dd_intc_vector.o ..\objs\dd_pit.o ..\objs\dd_siu.o ..\objs\dd_xbar_mpc5634.o ..\objs\dd_xbar_mpc5644.o ..\objs\dd_ecsm.o ..\objs\dd_dma.o ..\objs\dd_qadc.o ..\objs\dd_mios.o ..\objs\dd_dspi.o ..\objs\dd_flexcan.o ..\objs\dd_tpu.o ..\objs\dd_stm.o ..\objs\dd_vsep.o ..\objs\dd_vsep_deps.o ..\objs\dd_vsep_discrete.o ..\objs\dd_vsep_est_select.o ..\objs\dd_vsep_fault.o ..\objs\dd_vsep_pwm.o ..\objs\dd_vsep_soh.o ..\objs\dd_vsep_vr.o ..\objs\dd_vsep_init.o ..\objs\dd_vsep_config.o ..\objs\io_spi_scheduler.o ..\objs\io_spi_scheduler_init.o ..\objs\io_spi_config.o ..\objs\dd_l9958.o ..\objs\dd_l9958_fault.o ..\objs\dd_l9958_init.o ..\objs\dd_l9958_fault_interface.o ..\objs\dd_l9958_config.o ..\objs\dd_mcd5408.o ..\objs\dd_mcd5412.o ..\objs\dd_mcd5417.o ..\objs\mcd5417.o ..\objs\dd_mcd5411.o ..\objs\mcd5411.o ..\objs\dd_mcd5401.o ..\objs\hw_etpu_ucode.o ..\objs\dd_crank.o ..\objs\dd_crank_scheduler.o ..\objs\dd_spark.o ..\objs\dd_pfi.o ..\objs\cxio_initialization.o ..\objs\dd_fi.o ..\objs\dd_cam.o ..\objs\exit.o ..\objs\io_init.o ..\objs\main.o ..\objs\os_interface.o ..\objs\os_main.o ..\objs\os_normal.o ..\objs\os_sw_intc.o ..\objs\os_timebase.o ..\objs\hal_soh.o ..\objs\soh.o ..\objs\soh_nvm.o ..\objs\soh_s12x.o ..\objs\inst_config.o ..\objs\inst_overlay.o ..\objs\inst_overlay_mem.o ..\objs\inst_overlay_nvm.o ..\objs\hal_eeprom_mfg.o ..\objs\hal_eeprom_nvm.o ..\objs\hal_emulated_eeprom.o ..\objs\ccp2conf.o ..\objs\ccp2daq.o ..\objs\ccp2flexcan.o ..\objs\ccp2main.o ..\objs\ccp2mem.o ..\objs\ccp2mode.o ..\objs\ccp2nvmd.o ..\objs\ccp2session_nvm.o ..\objs\hal_analog.o ..\objs\hal_can.o ..\objs\hal_eng.o ..\objs\hal_fuel.o ..\objs\hal_gpio.o ..\objs\hal_os.o ..\objs\hal_pulse.o ..\objs\hal_spark.o ..\objs\hal_ucram.o ..\objs\hal_vcpc.o ..\objs\hwiocald.o ..\objs\io_interface_analog.o ..\objs\io_interface_eng.o ..\objs\io_interface_fuel.o ..\objs\io_interface_gpio.o ..\objs\io_interface_os.o ..\objs\io_interface_pulse.o ..\objs\io_interface_spark.o ..\objs\io_interface_vcpc.o ..\objs\io_conversion.o 

REM python gen_delphilib.py
gen_delphilib.exe
del ..\tools\delphilib\outputlib\mt22p3_chery_4cyl.a
call get_lib.bat
del get_lib.bat

copy ..\HLS\HLS.h ..\tools\delphilib\outputlib\HLS.h
copy ..\bin\Engine.mt22p3_chery_4cyl.a2l ..\tools\delphilib\outputlib\Engine.mt22p3_chery_4cyl.a2l
copy mt22p3_chery_4cyl.dld ..\tools\delphilib\outputlib\mt22p3_chery_4cyl.dld
copy ..\bin\mt22p3_chery_4cyl.exmap ..\tools\delphilib\outputlib\mt22p3_chery_4cyl.exmap

echo +============================================================================+ >> build.log
echo .                                                                            .
echo .                          B U I L D  C O M P L E T E                        . >> build.log
echo .  Build END time                                                            . >> build.log
        time/t  >> build.log
echo .                                                                            .
echo +============================================================================+ >> build.log
echo +============================================================================+
echo .                                                                            .
echo .  BUILD COMPLETE!                                                           .
echo .                                                                            .
echo .  Refer to the build.log file for errors and build messages                 .
echo .                                                                            .
echo .                       See readme file to locate files                      .
echo .                                                                            .
echo .  Build END time                                                            .
        time/t
echo .                                                                            .
echo .                                                                            .
echo +============================================================================+
pause
cls
echo on
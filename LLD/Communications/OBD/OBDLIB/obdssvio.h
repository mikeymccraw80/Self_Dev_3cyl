#ifndef OBDSSVIO_H
#define OBDSSVIO_H
/******************************************************************************
 * 
 * Filename:          obdssvio.h
 * 
 * Description:       This header file defines all necessary input resources of HAL
 *                    for obd system moduel. In order to prevent private subsystem
 *                    files from modifications due to input name changes
 *                    all input remaping should be done solely in this file
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    None
 * 
 * Forward Engine Management Systems
 * 
 * Copyright 2007-2008, Delphi Technologies, Inc.
 * All rights reserved.
 * 
 *****************************************************************************
 * 
 * Current Module Info:
 * %full_name:      mt20u2#1/incl/obdssvio.h/2 %
 * %date_created:   Fri Sep 17 10:23:34 2010 %
 * %version:        2 %
 * %derived_by:     lz37cb %
 * 
 *****************************************************************************/
/******************************************************************************
* APP Include Files
******************************************************************************/
#include "obdsfcfg.h"
#if(XeOBDS_SYST_CONTROLLER_DIAG_TYPE == CeOBDS_SYST_CONTROLLER_IS_MT80)
#include "spi_port.h"/*For SPIPort_Initialize()*/
#include "inst_overlay.h"  /*for INST_Set_Active_Calibration_Page()*/
#include "io_spi_chip_select.h" /*for MTSA_SPI_CHANNEL_0*/
#include "kw2k_port.h"/*KW2000_Port_Send_Standard_Positive_Answer()
                        KW2000_Port_Send_Standard_Negative_Answer()*/
                        
//#include "cn_io_transfer.h"     /* Transmit_Message */
#include "io_initialize.h"

#include "hal_adc.h" /*GetIO_Pct_BufferedAnalogValue ()*/
#include "hal.h"             /* Get_IO_Analog_AD_EGR_PINTAL_POSITION_FB */
#include "hal_os.h"

#include "dd_dma.h" /*for DMA_Clear_Device()*/
#include "dd_scu.h"
#include "ccp2conf.h"
#elif (XeOBDS_SYST_CONTROLLER_DIAG_TYPE == CeOBDS_SYST_CONTROLLER_IS_MT22p1)
#include "kw2app.h"
#endif

#endif /*OBDSSVIO_H*/

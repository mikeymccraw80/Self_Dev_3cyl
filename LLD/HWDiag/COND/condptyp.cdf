 ##############################################################################
 #
 # Filename:          condptyp.cdf
 #
 # Description:       Global cdf-Data Type Definitions
 #                    header file for COND subsystem.
 #
 # Global Functions Defined:
 #                    None
 # Static Functions Defined:
 #                    None
 # Inline Functions Defined:
 #                    None
 #
 # Forward Engine Management Systems
 #
 # Copyright 2007, Delphi Technologies, Inc.
 # All rights reserved.
 #
 #############################################################################
 #
 # Current Module Info:
 # %full_name:      mt20u2#1/ascii/condptyp.cdf/1 %
 # %date_created:   Wed Jan 30 09:52:59 2008 %
 # %version:        1 %
 # %derived_by:     wzmkk7 %
 #
 #############################################################################

 #############################################################################
 #  Global cdf-type Definitions
 #############################################################################

apptypes
{
  .t_cond_time_sec_0_16 {
     :kind = fixed;
     :precision = 16/65536;
     :range = 0.0 TO <16;
  }
}

##############################################################################
#
# Revision History:
#
# Rev.  YYMMDD Who RSM# Changes
# ----- ------ --- ---- ------------------------------------------------------
# 1     070305 gps 5202 COND: Validate APS Inputs Using Short to Ground Method.
#                       CORE Part. Created the file.
#
##############################################################################

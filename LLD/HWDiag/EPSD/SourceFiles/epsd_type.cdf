#******************************************************************************
#*
#* Filename:          epsd_type.cdf
#*
#* Description:       This is a common file used by EPSD subsystems. It
#*                    contains the fixed, annotation, array, table  types used
#                     by the cdf files of all applications. The cdf files are
#*                    written per the Caldef Language Specifications and form
#*                    inputs to the i6lgen tool to generate i6l file from
#*                    ieee file.  The i6l file is used as an input to either
#*                    CALTOOL or CALDS for calibration development.
#*
#* Global Functions Defined:
#*                    None
#* Static Functions Defined:
#*                    None
#* Inline Functions Defined:
#*                    None
#*
#* Forward Engine Management Systems
#*
#* Copyright 1997-2003, Delphi Technologies, Inc.
#* All rights reserved.
#*
#*****************************************************************************
#*
#* Current Module Info:
#* %derived_by:      vzp48z %
#* %full_name:       mt20u2#5/ascii/epsd_type.cdf/1 %
#* %date_created:    Wed Mar 19 10:10:33 2008 %
#* %version:         1 %
#*
#*****************************************************************************/

# =============================================================================
# ========================= A N N O T A T I O N S  ============================
# ================ (Listed in Alphabetical order of names) ====================
# =============================================================================
#				None

# =============================================================================
# =============================== F I X E D ===================================
# ================ (Listed in Alphabetical order of names) ====================
# =============================================================================

fixed
{
          .epsd_t_count_word
          {
             :kind = fixed;
             :precision = 1;
             :range = 0 TO <65536;
          }

          .epsd_t_kpaa
          {
             :kind = fixed;
             :precision = 256/65536; #0.00390625;
             :range = 0.0 TO <256;
          }

          .epsd_t_p_code
          {
             :kind = fixed;
             :precision = 1;
             :range = 0 TO <65535;
          }

          .epsd_t_w_R7p8125ms
          {
             :kind = fixed;
             :precision = 0.0078125;            # 7.8125/1000
             :range = 0.0 TO <0.0078125*65536;  # 511.9921875 seconds
          }

          .epsd_t_voltb
          {
             :kind = fixed;
             :precision = 0.000488281;
             :range = 0 TO < 65535*0.000488281;
             #       (= 0 TO 31.99949534)
          }

}

#******************************************************************************
#
# Revision History:
#
# Rev.  YYMMDD Who RSM# Changes
# ----- ------ --- ---- -------------------------------------------------------
# 1.0          rag      Created module.
#
###############################################################################

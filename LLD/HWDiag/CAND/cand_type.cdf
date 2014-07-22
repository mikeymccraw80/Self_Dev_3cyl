#******************************************************************************
#*
#* Filename:          cand_type.cdf
#*
#* Description:       This is a common file used by cand subsystems. It
#*                    contains the fixed types. The cdf files are
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
#* %full_name:       mt20u2#5/ascii/cand_type.cdf/1 %
#* %date_created:    Wed Mar 19 09:46:30 2008 %
#* %version:         1 %
#*
#*****************************************************************************/

# =============================================================================
# ========================= A N N O T A T I O N S  ============================
# ================ (Listed in Alphabetical order of names) ====================
# =============================================================================
fixed
{
          .cand_t_count_word
          {
             :kind = fixed;
             :precision = 1;
             :range = 0 TO <65536;
          }


          .cand_t_voltb
          {
             :kind = fixed;
             :precision = 0.000488281;
             :range = 0 TO < 65535*0.000488281;
             #       (= 0 TO 31.99949534)
          }

          .cand_t_p_code
          {
             :kind = fixed;
             :precision = 1;
             :range = 0 TO <65535;
          }

}

# ============================================================================
# File revision history (top to bottom, first revision to last revision
# ============================================================================
#
# Date         user id     SCR       (description on following lines)
# ----------   -------     ---
# 16/12/05     LShoujun    mt20u2#36
# + Baseline - Add CAN Commu Failure Diag
#*****************************************************************************

#******************************************************************************
#*
#* Filename:          ofvc_type.cdf
#*
#* Description:       This is a common file used by ofvc subsystems. It
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
#* Copyright 1997-2005, Delphi Technologies, Inc.
#* All rights reserved.
#*
#*****************************************************************************
#*
#* Current Module Info:
#* %derived_by:     wzmkk7 %
#* %full_name:      mt20u2#7/ascii/ofvc_type.cdf/1 %
#* %date_created:   Tue Dec 23 09:07:50 2008 %
#* %version:        1 %
#*
#*****************************************************************************/
# =============================================================================
# ========================= A N N O T A T I O N S  ============================
# ================ (Listed in Alphabetical order of names) ====================
# =============================================================================

# =============================================================================
# =============================== F I X E D ===================================
# ================ (Listed in Alphabetical order of names) ====================
# =============================================================================

fixed
{
          .ofvc_t_kilometersa
          {
             :kind = fixed;
             :precision = 1;
             :range = 0 TO <65536;
          }
          .ofvc_t_count_word
          {
             :kind = fixed;
             :precision = 1;
             :range = 0 TO <65536;
          }
          .ofvc_t_voltb
          {
             :kind = fixed;
             :precision = 0.000488281;
             :range = 0 TO < 65535*0.000488281;
             #       (= 0 TO 31.99949534)
          }
          .ofvc_t_y_R31p25ms
          {
             :kind = fixed;
             :precision = 0.03125;              # 31.25/1000
             :range = 0.0 TO <0.03125*256;      # 7.96875 seconds
          }
          .ofvc_t_anglea
          {
             :kind = fixed;
             :precision = 512/65536; # 0.0078125;
             :range = -256 TO <256;
          }
          .ofvc_t_count_byte
          {
             :kind = fixed;
             :precision = 1;
             :range = 0 TO <256;
          }
         .ofvc_size13_1to13
          {
             :kind = fixed;
             :precision = 1;
             :range = 1 TO <14;
          }
          .ofvc_t_bpw
          {
             :kind = fixed;
             :precision = 1024/65536; #0.015625;
             :range = 0 TO <1024;
          }
}
# =============================================================================
# ============================= ENUMERATIONS  =================================
# ================ (Listed in Alphabetical order of names) ====================
# =============================================================================

enum
{
         .ofvc_size13_1to13
          {
             :kind = fixed;
             :precision = 1;
             :range = 1 TO <14;
          }
}   
#******************************************************************************
#
# Revision History:
#
# Rev.  YYMMDD    Who    RSM#                        Changes
# ----- ------ --- ---- -------------------------------------------------------
# 1.0   12/04/05 Q.W    MT20A-294                Created module.
#
#       SCR       mm/dd/yy    Author
# 1.1   mt20u2#16 29/07/05    Liu Shoujun
#       + Error Correction added into Level 6B 
#         - Corrected the range of ofvc_t_kilometersa.
#
# Aug/26/05    Q.W         mt20u2#17
# + Add Tooth Error Correction Diangostic (TECD) module
#    - Add new type define for OFVC calibration parameter support.
###############################################################################

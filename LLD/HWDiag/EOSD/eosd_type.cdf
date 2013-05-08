#******************************************************************************
#*
#* Filename:          cal_type.cdf
#*
#* Description:       This is a common file used by eosd subsystems. It
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
#* %derived_by:     vzp48z %
#* %full_name:      mt20u2#5/ascii/eosd_type.cdf/1 %
#* %date_created:   Wed Mar 19 10:10:26 2008 %
#* %version:        1 %
#*
#*****************************************************************************/

# =============================================================================
# ========================= A N N O T A T I O N S  ============================
# ================ (Listed in Alphabetical order of names) ====================
# =============================================================================
anns
{
          .eosd_temp_09_brkpts_m40_120
          {
            :kind = define_annotation;
            :units = "Deg C";
#                    (Index 0 : -40 to 120 incr=20)
            :table = (-40, -20, 0, 20, 40, 60, 80, 100, 120) ;
          }

           .eosd_temp_05_brkpts_CARB_delta
          {
            :kind = define_annotation;
            :units = "Deg C";
            :table = (0, 8.33, 19.44, 27, 35) ;
          }

         .blm_cell_num
	  {
	    :kind = define_annotation;
	    :units = "BLM Cell#";
	    :table = (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
	              14, 15, 16, 17, 18, 19, 20, 21);
	  }

}

# =============================================================================
# =============================== F I X E D ===================================
# ================ (Listed in Alphabetical order of names) ====================
# =============================================================================

fixed
{
          .eosd_t_count_word
          {
             :kind = fixed;
             :precision = 1;
             :range = 0 TO <65536;
          }

          .eosd_t_uword
          {
             :kind = fixed;
             :precision=1;
             :range = 0 TO <65536; # 65535*1;
          }

          .eosd_t_percentb
          {
             :kind = fixed;
             :precision = 0.001525878;
             :range = 0.0 TO <0.001525878*65536; # 99.99994061
          }

          .eosd_t_deg_ca
          {
             :kind = fixed;
             :precision = 512/65536; #0.0078125
             :range = -256 TO <256;
          }

          .eosd_t_kph
          {
             :kind = fixed;
             :precision = 512/65536; #0.0078125;
             :range = 0.0 TO <512;
          }

          .eosd_t_min
          {
             :kind = fixed;
             :precision = 1; #1.0
             :range = 0 TO 65535;
          }

          .eosd_t_gram_sec
          {
             :kind = fixed;
             :precision = 256/65536; #0.00390625;
             :range = 0.0 TO <256;
          }

          .eosd_t_filter
          {
             :kind = fixed;
             :precision = 1/65536; # 0.000015258;
             :range = 0 TO <1; # 65536*0.000015258;
          }

          .eosd_t_w_R125ms
          {
             :kind = fixed;
             :precision = 0.125;                # 125/1000
             :range = 0.0 TO <0.125*65536;      # 8191.875 seconds
          }

          .eosd_t_gramsb
          {
             :kind = fixed;
             :precision = 0.00390625;
             :range = 0.0 TO <16777216;
          }

          .eosd_t_w_R500ms
          {
             :kind = fixed;
             :precision = 0.5;                  # 500/1000
             :range = 0.0 TO <0.5*65536;        # 32767.5 seconds
          }

          .eosd_t_p_code
          {
             :kind = fixed;
             :precision = 1;
             :range = 0 TO <65535;
          }

           .eosd_t_rpma
          {
             :kind = fixed;
             :precision = 8192/65536; #0.125;
             :range = 0.0 TO <8192;
          }

          .eosd_t_kpaa
          {
             :kind = fixed;
             :precision = 256/65536; #0.00390625;
             :range = 0.0 TO <256;
          }

          .eosd_t_percenta
          {
             :kind = fixed;
             :precision = 0.003051757;
             :range = 0.0 TO <0.003051757*65536; # 1.9999643625;
          }

          .eosd_t_voltb
          {
             :kind = fixed;
             :precision = 0.000488281;
             :range = 0 TO < 65535*0.000488281;
             #       (= 0 TO 31.99949534)
          }

	  .eosd_t_grams_per_sec
	  {
	     :kind = fixed;
	     :precision = 512/65536; #0.0078125;
	     :range = 0.0 TO <512;
	  }

	  .eosd_t_ratio_0_1
          {
	     :kind = fixed;
	     :precision = 1/65536; #0.000015258;
	     :range = 0.0 TO <1; #0.000015258*65535;
             # 0 to 0.99993303
	  }

          .eosd_t_percent_multa
	  {
	     :kind = fixed;
	     :precision = 2/65536;
	     :range = 0.0 TO <2;
	  }

          .eosd_t_count_byte
          {
             :kind = fixed;
             :precision = 1;
             :range = 0 TO <256;
          }

          .eosd_t_w_R1000ms
          {
             :kind = fixed;
             :precision = 1;                    # 1000/1000
             :range = 0.0 TO <1*65536;          # 65535 seconds
          }

          .eosd_t_ratio_0_32
          {
             :kind = fixed;
             :precision = 32/65536; #
             :range = 0.0 TO <32; #
             # 0 to 31.99
          }

          .eosd_t_amp
          {
             :kind = fixed;
             :precision = 8/65536;
             :range = 0.0 TO <8; # 7.99987793;
          }

	  .eosd_t_w_R15p625ms
          {
	  :kind = fixed;
	  :precision = 0.015625;             # 15.625/1000
	  :range = 0.0 TO <0.015625*65536;   # 1023.984375 seconds
	  }

	  .eosd_t_ratio_0_128
          {
	     :kind = fixed;
	     :precision = 128/65536; #0.001953125;
	     :range = 0.0 TO <128;   #0.001953125*65535;
             # 0 to 127.998
	  }
	  



}

# =============================================================================
# ============================= ENUMERATIONS  =================================
# ================ (Listed in Alphabetical order of names) ====================
# =============================================================================

enum
{
         .eosd_size2_0to1
          {
             :kind = fixed;
             :precision = 1;
             :range = 0 TO <2;
          }
          .eosd_size4_0to3
          {
             :kind = fixed;
             :precision = 1;
             :range = 0 TO <4;
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
# 21/12/05     LShoujun    mt20u2#38(SCR)
# + Rearrangement for calibration location
#   - replaced acpd_size4_0to3 with eosd_size4_0to3
#
###############################################################################

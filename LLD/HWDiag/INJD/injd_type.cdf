#******************************************************************************
#*
#* Filename:          cal_type.cdf
#*
#* Description:       This is a common file used by injd subsystems. It
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
#* %full_name:      mt20u2#5/ascii/injd_type.cdf/1 %
#* %date_created:   Wed Mar 19 10:11:36 2008 %
#* %version:        1 %
#*
#*****************************************************************************/

# =============================================================================
# ========================= A N N O T A T I O N S  ============================
# ================ (Listed in Alphabetical order of names) ====================
# =============================================================================
anns
{

          .injd_rpm_13_brkpts_500to_6500
          {
            :kind = define_annotation;
            :units = "RPM";

#           (Index 0 : 500 to 6500 incr=500)
            :table = (500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500,
                      5000, 5500, 6000, 6500) ;

          }

          .injd_percent_09_brkpts_0to_100
          {
            :kind = define_annotation;
            :units = "Percent";

#                    (Index 0 : 0 to 100 incr=12.5)
            :table = (0, 12.5, 25.0, 37.5, 50.0, 62.5, 75, 87.5, 100) ;
          }

          .injd_rpm_08_brkpts_0to_7000
          {
            :kind = define_annotation;
            :units = "RPM";

#           (Index 0 : 0 to 7000 incr=1000)
            :table = (0, 1000, 2000, 3000, 4000, 5000, 6000, 7000) ;
          }

          .injd_percent_05_brkpts_0to_100
          {
            :kind = define_annotation;
            :units = "Percent";

#                    (Index 0 : 0 to 100 incr=25)
            :table = (0, 25, 50, 75, 100) ;
          }

          .injd_rpm_21_brkpts_600to7000
          {
            :kind = define_annotation;
            :units = "RPM";

#           (Index 0 : 600 to 3000 incr=200, 3000 to 7000 incr=500)
            :table = (600, 800, 1000 , 1200, 1400, 1600, 1800, 2000,
                      2200, 2400, 2600, 2800, 3000, 3500, 4000, 4500, 5000,
                      5500, 6000, 6500, 7000) ;
          }

          .injd_percent_17_brkpts_0to_100
          {
            :kind = define_annotation;
            :units = "Percent";

#                    (Index 0 : 0 to 100.0 incr=6.25)
            :table = (0, 6.25, 12.5, 18.75, 25.0, 31.25, 37.5, 43.75,
                      50.0, 56.25, 62.5, 68.75, 75.0, 81.25, 87.5,
                      93.75, 100.0) ;
          }

          .injd_temp_17_brkpts_m40to_152
          {
            :kind = define_annotation;
            :units = "Deg C";

#                    (Index 0 : -256 to 256 incr=32)
            :table = (-40, -28, -16, -4, 8, 20, 32, 44, 56,
                       68, 80, 92, 104, 116, 128, 140, 152);
          }

          .injd_rpm_17_brkpts_0to_6400
          {
            :kind = define_annotation;
            :units = "RPM";

#                    (Index 0 : 0 to 6400 incr=400)
            :table = (0, 400, 800, 1200, 1600, 2000, 2400, 2800, 3200,
                      3600, 4000, 4400, 4800, 5200, 5600, 6000, 6400) ;
          }

          .injd_pressure_11_brkpts_0to_100
          {
            :kind = define_annotation;
            :units = "KPA";

#                    (Index 0 : 0 to 100 incr=10)
            :table = (0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100) ;
          }

}

# =============================================================================
# ============================= ENUMERATIONS  =================================
# ================ (Listed in Alphabetical order of names) ====================
# =============================================================================

enum
{
         .injd_size2_0to1
          {
             :kind = fixed;
             :precision = 1;
             :range = 0 TO <2;
          }
             .injd_size4_0to3
          {
             :kind = fixed;
             :precision = 1;
             :range = 0 TO <4;
          }
}

# =============================================================================
# =============================== F I X E D ===================================
# ================ (Listed in Alphabetical order of names) ====================
# =============================================================================

fixed
{

          .injd_t_count_byte
          { 
             :kind = fixed;
             :precision = 1;
             :range = 0 TO <256;
          }

          .injd_t_count_word
          {
             :kind = fixed;
             :precision = 1;
             :range = 0 TO <65536;
          }

          .injd_t_percentb
          {
             :kind = fixed;
             :precision = 0.001525878;
             :range = 0.0 TO <0.001525878*65536; # 99.99994061
          }

          .injd_t_ratio_0_2
          {
             :kind = fixed;
             :precision = 2/65536; #0.000030517;
             :range = 0.0 TO <2; #0.000030517*65535;
             # 0 to 1.999931595
          }

          .injd_t_ratio_0_8
          {
             :kind = fixed;
             :precision = 8/65536; #0.00012207;
             :range = 0.0 TO <8; #0.00012207*65535;
             # 0 to 7.99985745
          }

          .injd_t_ratio_0_16
          {
             :kind = fixed;
             :precision = 16/65536; #0.00024414;
             :range = 0.0 TO <16; #0.00024414*65535;
             # 0 to 15.99995904
          }

          .injd_t_rpma
          {
             :kind = fixed;
             :precision = 8192/65536; #0.125;
             :range = 0.0 TO <8192;
          }

          .injd_t_percenta
          {
             :kind = fixed;
             :precision = 0.003051757;
             :range = 0.0 TO <0.003051757*65536; # 1.9999643625;
          }

          .injd_t_percent_multb
          {
             :kind = fixed;
             :precision = 0.00001525878;
             :range = 0.0 TO <0.00001525878*65536; # 1.0;
          }

          .injd_t_ratio_0_1
          {
             :kind = fixed;
             :precision = 1/65536; #0.000015258;
             :range = 0.0 TO <1; #0.000015258*65535;
             # 0 to 0.99993303
          }

          .injd_t_deg_ca
          {
             :kind = fixed;
             :precision = 512/65536; #0.0078125
             :range = -256 TO <256;
          }

          .injd_t_voltb
          {
             :kind = fixed;
             :precision = 0.000488281;
             :range = 0 TO < 65535*0.000488281;
             #       (= 0 TO 31.99949534)
          }

          .injd_t_kph
          {
             :kind = fixed;
             :precision = 512/65536; #0.0078125;
             :range = 0.0 TO <512;
          }

          .injd_t_grams_cyl_0_1
          {
             :kind = fixed;
             :precision = 0.000030517;
             :range = 0.0 TO <0.000030517*65535; # 1.999931595;
          }

          .injd_t_ubyte
          {
             :kind = fixed;
             :precision=1;
             :range = 0 TO <256;
          }

          .injd_t_uword
          {
             :kind = fixed;
             :precision=1;
             :range = 0 TO <65536; # 65535*1;
          }

          .injd_t_ratio_0_4
          {
             :kind = fixed;
             :precision = 4/65536; #0.000061035;
             :range = 0.0 TO <4; #0.000061035*65535;
             # 0 to 3.999928725
          }

          .injd_t_microseconds
          {
             :kind = fixed;
             :precision = 1;
             :range = 0 TO <1*65535;
          }

          .injd_t_p_code
          {
             :kind = fixed;
             :precision = 1;
             :range = 0 TO <65535;
          }

            .injd_t_hires_clktcks_longa
          {
             :kind = fixed;
             :precision = 1; #1/8*system clock
             :range = 0 TO <4294967296;
          }

          .injd_t_y_R125ms
          {
          :kind = fixed;
          :precision = 0.125;                # 125/1000
          :range = 0.0 TO <0.125*256;        # 31.875 seconds
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

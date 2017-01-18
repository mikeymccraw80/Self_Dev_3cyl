#******************************************************************************
#*
#* Filename:          cal_type.cdf
#*
#* Description:       This is a common file used by all subsystems. It
#*                    contains the fixed and annotation types used by the
#*                    cdf files of all applications. The cdf files are
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
#* Copyright 1997-2006, Delphi Technologies, Inc.
#* All rights reserved.
#*
#*****************************************************************************
#*
#* Current Module Info:
#* %full_name:     mt20u2#3/ascii/cal_type.cdf/1 %
#* %date_created:  Wed Nov 28 09:53:05 2007 %
#* %version:       1 %
#* %derived_by:    wzmkk7 %
#*
#*****************************************************************************/

types
{

    .NbAcClutchStates
    {
        :kind = define_annotation;
        :units = "( 0=A/C_Off_/_1=A/C_On)";
        :table = ( 0, 1 );
    }

    .CrankAngleInDeg_W
    {
        :kind = fixed;
        :precision = ( 0.351562 );
        :range = ( 0.000000 ) TO ( 65535 * 0.351562 );
    }

    .CrankAngleInDeg_B
    {
        :kind = fixed;
        :precision = ( 0.351562 );
        :range = ( 0.000000 ) TO ( 65535 * 0.351562 );
    }

    .MicroSec_58X
    {
        :kind = fixed;
        :precision = ( 7.60000 );
        :range = ( 0.000000 ) TO ( 65535 * 7.600000 );
    }

    .t_crank_angle		 
    {
           :kind = fixed;
           :precision = 1/64; #0.015625;
           :range = ( 0.000000 ) TO <   ( 65535 /64 );
     }

    .t_crank_anglea
    {
       :kind = fixed;
       :precision = 1024/65536; #0.015625;
       :range = -512 TO <512;
    }

   . CrankAngleInDeg_W
    {
       : kind = fixed;
       : precision = ( 0.015625 );
       : range = ( -512 ) TO ( 511 );
       : biased;
    }


     .T_HERTZ
     {
           :kind = fixed;
           :precision = 0.25;
           :range = 0 TO <16384;
      }

     .Fixed_Shortcard
     {
           :kind = fixed;
           :precision = 1;
           :range = 0 TO <256;
      }

     .Fixed_Cardinal
     {
           :kind = fixed;
           :precision = 1;
           :range = 0 TO <65535;
      }

     .Millivolts_B
     {
         : kind = fixed;
         : precision = (4.8828125);
         : range = (0.000000) TO (255 * 4.8828125);
     }

     .Millivolts_0to5000_W
     {
         : kind = fixed;
         : precision = ( 5000.0 / 65536 );
         : range = ( 0.000000 ) TO ( 65535 * ( 5000.0 / 65536) );
     }

     .EOBD_2nd_LOOP_W
     {
         : kind = fixed;
         : precision = ( 0.008 );
         : range = ( 0.000000 ) TO ( 65535 * 0.008 );
     }

      .Volts_Plus_Fraction
     {
         : kind = fixed;
         : precision = (0.0003906);
        : range = (0.000000) TO (65535 * 0.0003906);
     }


    .size2_0to1
      {
           :kind = fixed;
           :precision = 1;
           :range = 0 TO <2;
      }

    .Every_10th_Loop_Sec_B
    {
       : kind = fixed;
       : precision = ( 0.100000 );
       : range = ( 0.000000 ) TO ( 25.500000 );
    }
  
#if CcSYST_NUM_OF_CYLINDERS == 3
    .CylinderNumber_Type
     {
         :kind = fixed;
         :precision = ( 1.0 );
         :range = (1.0) TO (3.0);
      }
#else

    .CylinderNumber_Type
     {
         :kind = fixed;
         :precision = ( 1.0 );
         :range = (1.0) TO (4.0);
      }

#endif
 
   .BPFGain_Type
    {
        : kind = fixed;
        : precision = ( 6.000000 );
        : range = ( 0.000000 ) TO ( 24.000000 );
    }
 
   .Volt0to5Volts_W
   {
       :kind = fixed;
       :precision = ( 5.0/65536 );
       :range = ( 0.000000 ) TO ( 65535 * ( 5.0 / 65536 ));
    }
  
    .Multiplier_0_to_2
    {
       : kind = fixed;
       : precision = ( 2.0/256 );
       : range = ( 0.000000 ) TO ( 255 * 2.0/256 );
    }

    .WindowStartAngle_Type
    {
       : kind = fixed;
       : precision = ( 0.351562 );
       : range = ( -128 * 0.351562 ) TO ( 127 * 0.351562 );
       : biased;
    }


    .Seconds_Low
    {
       : kind = fixed;
       : precision = ( 1.000000 );
       : range = ( 0.000000 ) TO ( 65535.000000 );
    }
    
    .t_millisecondsb
    {
           : kind = fixed;
           : precision = ( 1.000000/64 );
           : range = ( 0.000000 ) TO ( 65535.000000/64.0 );
    }

    .RPM_B
    {
       : kind = fixed;
       : precision = ( 25.000000 );
       : range = ( 0.000000 ) TO ( 6375.000000 );
    }

    .kPa_B
    {
       : kind = fixed;
       : precision = ( 0.368862 );
       : range = ( 28 * 0.368862 ) TO ( 283  * 0.368862 );
       : biased;
    }

    .Percent_B
    {
       : kind = fixed;
       : precision = ( 100.0/256 );
       : range = ( 0.000000 ) TO ( 255 * 100.0/256 );
    }

    .Every_4th_Loop_Sec_W
    {
       : kind = fixed;
       : precision = ( 0.04000 );
       : range = ( 0.000000 ) TO ( 2621.4 );
    }
    
    .Every_16th_Loop_Sec_W
    {
       : kind = fixed;
       : precision = ( 0.16000 );
       : range = ( 0.000000 ) TO ( 10485.6 );
    }

    .RPM_W
    {
       : kind = fixed;
       : precision = ( 1.0/8.0 );
       : range = ( 0.000000 ) TO ( 65535 * 1.0/8.0 );
    }

   .uint8_t
    {
       : kind = fixed;
       : precision = ( 1.0 );
       : range = ( 0.000000 ) TO ( 255 );
    }

    .uint16_t
    {
       : kind = fixed;
       : precision = ( 1.0 );
       : range = ( 0.000000 ) TO ( 65535 );
    }

     .Filter_Q_W
    {
       :kind = fixed;
       :precision = ( 1.0 / 65536 );
       :range = ( 0.000000 ) TO ( 65535 * ( 1 / 65536 ));
    }

     .TPS_B
    {
       :kind = fixed;
       :precision = ( 0.390625 );
       :range = ( 0.000000 ) TO ( 99.609375 );
    }

    .Volt0to5Volts_B
    {
       : kind = fixed;
       : precision = ( 5.0 / 256 );
       : range = ( 0.000000 ) TO ( 255 * 5.0 / 256 );
    }

    .kPa_Delta
    {
       : kind = fixed;
       : precision = ( 0.368862 );
       : range = ( 0.000000 ) TO ( 255 * 0.368862 );
    }

    .Every_16th_Loop_Sec_B
    {
       : kind = fixed;
       : precision = ( 0.16000 );
       : range = ( 0.000000 ) TO ( 40.800000 );
    }

    .Every_2nd_Loop_Sec_B
    {
       : kind = fixed;
       : precision = ( 0.02 );
       : range = ( 0.000000 ) TO ( 5.100000 );
    }

    .RPM_Hi_Res_W
    {
       : kind = fixed;
       : precision = ( 1.000000 );
       : range = ( 0.000000 ) TO ( 65535.000000 );
    }

    .Every_4th_Loop_Sec_B
    {
       : kind = fixed;
       : precision = ( 0.04000 );
       : range = ( 0.000000 ) TO ( 10.200000 );
    }

     .Every_Loop_Sec_B
    {
       : kind = fixed;
       : precision = ( 0.01000 );
       : range = ( 0.000000 ) TO ( 2.550000 );
    }
    
    .Every_Loop_Sec_W
    {
       : kind = fixed;
       : precision = ( 0.01000 );
       : range = ( 0.000000 ) TO ( 655.350000 );
    }

    .Multiplier_0_to_64
    {
       : kind = fixed;
       : precision = ( 64.0/256 );
       : range = ( 0.000000 ) TO ( 255 * 64.0/256 );
    }

    .Multiplier_0_to_4
    {
       : kind = fixed;
       : precision = ( 4.0/256 );
       : range = ( 0.000000 ) TO ( 255 * 4.0/256 );
    }

     .ESC_Attack_B
    {
       :kind = fixed;
       :precision = ( 0.017578);
       :range = ( 0.000000 ) TO ( 255 * 0.017578);
    }

    .CrankDeg_Sec_B
    {
       :kind = fixed;
       :precision = ( (90.0*64)/(65536*4) );
       :range = ( 0.000000 ) TO ( 255 * (90.0*64)/(65536*4));
    }

    .CrankAngleInDeg_Plus_Fraction
    {
       : kind = fixed;
       : precision = ( 0.001373 );
       : range = ( 0.000000 ) TO ( 65535 * 0.001373 );
    }

    .kPa_W
    {
       : kind = fixed;
       : precision = ( 5.0 / 256 );
       : range = ( 0.000000 ) TO ( 5376 * ( 5.0 / 256 ) );
    }

    .CrankDeg8Times_Sec_B
    {
       :kind = fixed;
       :precision = ( (90.0*64)/(65536*4) * 8);
       :range = ( 0.000000 ) TO ( 255 * 8* (90.0*64)/(65536*4));
    }

    .SparkAdvance_Delta_Deg_B
    {
       : kind = fixed;
       : precision = ( 90.0/256 );
       : range = ( 0.0 ) TO ( 255 * 90.0/256 );
    }

    .SparkAdvance_Deg_B
    {
       : kind = fixed;
       : precision = ( 90.0/256 );
       : range = ( -64 * 90.0/256 ) TO ( 191 * 90.0/256 );
       : biased;
    }

   . Degrees_C_B
    {
       : kind = fixed;
       : precision = ( 0.750000 );
       : range = ( -40.500000 ) TO ( 150.750000 );
       : biased;
    }

   .Percent_W
    {
            : kind = fixed;
            : precision = (0.024414);
            : range = (0.000000) TO (65535 * 0.024414);
    }
 
  .KnockControl_Timer_Type
   {
      : kind = fixed;
      : precision = ( 0.02 );
      : range = ( 0.000000 ) TO ( 5.100000 );
   }

   .Filter_Coefficient
   {
         : kind = fixed;
         : precision = (1.0 );
         : range = (0.000000) TO (65536*65535);
   }

   
   .Multiplier_0_to_1
   {
      : kind = fixed;
      : precision = ( 1.0/256 );
      : range = ( 0.000000 ) TO ( 255 * 1.0/256 );
   }


     .Multiplier_0_to_1_W
   {
      : kind = fixed;
      : precision = ( 1.0/65536 );
      : range = ( 0.000000 ) TO ( 65535 * 1.0/65536 );
   }

   
   .Diag58XSec
   {
      : kind = fixed;
      : precision = ( 0.062500 );
      : range = ( 0.000000 ) TO ( 15.937500 );
   }


   .PulsesPerKilometer
   {
      : kind = fixed;
      : precision = ( 1.000000 );
      : range = ( 0.000000 ) TO ( 65535.000000 );
   }


   .KPH
   {
      : kind = fixed;
      : precision = ( 1.000000 );
      : range = ( 0.000000 ) TO ( 255.000000 );
   }
   
      .EOBD_KPH
   {
      : kind = fixed;
      : precision = ( 0.0078125 );
      : range = ( 0.000000 ) TO ( 511.9921875 );
   }


  .VSSDiagSec
   {
      : kind = fixed;
      : precision = ( 0.062500 );
      : range = ( 0.000000 ) TO ( 15.937500 );
   }
   

   .Volts_B
   {
      : kind = fixed;
      : precision = ( 0.100000 );
      : range = ( 0.000000 ) TO ( 25.500000 );
   }

   
   .KPH_0to128by8_Steps
   {
      :kind = define_annotation;
      :units = "km/h";
      :table =
         ( 0 TO 128 BY 8);
   }


     .RPM_0to6400by800_Steps
    {
        :kind = define_annotation;
        :units = "RPM";
        :table =
           ( 0 TO 6400 BY 800 );
    }
    
    .RPM_0to6400by400_Steps
     {
            :kind = define_annotation;
            :units = "RPM";
            :table =
               ( 0 TO 6400 BY 400 );
    }
    
   .RPM_400to6400by400_Steps
   {
      :kind = define_annotation;
      :units = "RPM";
      :table =
         ( 400 TO 6400 BY 400 );
    }

   .kPa_0to60by10_Steps
  {
      :kind = define_annotation;
      :units = "kPa";
      :table =
         ( 0 TO 60 BY 10 );
   }
   
 .kPa_20to100by20_Steps
  {
       :kind = define_annotation;
       :units = "kPa";
       :table =
          ( 20 TO 100 BY 20 );
  }
  
  .CylinderNumber_Index_Type_3Cyl
   {
      :kind = define_annotation;
      :units = "counts";
      :table =
         ( 0 TO 2 BY 1 );
  }
 
   .CylinderNumber_Index_Type
   {
      :kind = define_annotation;
      :units = "counts";
      :table =
         ( 0 TO 3 BY 1 );
  }


   .kPa_60to100by10_Steps
   {
      :kind = define_annotation;
      :units = "kPa";
      :table =
        ( 60, 70, 80, 90, 100 );
   }
   
   .NUMBER_OF_CYLINDERS_3Cyl
  {
       :kind = define_annotation;
	:units = "Cylinder_#";
      :table = ( 1,2,3 );
  }


   .NUMBER_OF_CYLINDERS
  {
       :kind = define_annotation;
	:units = "Cylinder_#";
      :table = ( 1, 2, 3, 4 );
  }
 
  .kPa_20to80by10_80to100by5_Steps
   {
      :kind = define_annotation;
      :units = "kPa";
      :table =
         ( 20, 30, 40, 50, 60, 70, 80, 85, 90, 95, 100 );
   }



   .Deg_C_m40to152by12_Steps
   {
     :kind = define_annotation;
     :units = "Degrees_C";
     :table =
         ( -40, -28, -16, -4, 8, 20, 32, 44, 56, 68, 80, 92, 104, 116,
           128, 140, 152 );
   }

          .t_deg_ca
          {
             :kind = fixed;
             :precision = 512/65536; #0.0078125
             :range = -256 TO <256;
          }

          .t_count_byte
          {
             :kind = fixed;
             :precision = 1;
             :range = 0 TO <256;
          }

          .t_count_word
          {
             :kind = fixed;
             :precision = 1;
             :range = 0 TO <65535;
          }
          
          .t_count_long
	  {
	     :kind = fixed;
	     :precision = 1;
	     :range = 0 TO <65535*65535;
          }


          .t_rpma
          {
             :kind = fixed;
             :precision = 8192/65536; #0.125;
             :range = 0.0 TO <8192;
          }

          .t_w_R7p8125ms
          {
             :kind = fixed;
             :precision = 0.0078125;            # 7.8125/1000
             :range = 0.0 TO <0.0078125*65536;  # 511.9921875 seconds
          }

          .Mileage_In_100M_L
          {
             :kind = fixed;
             :precision = ( 0.1 ); 
             :range = 0.0 TO < 4294967295*0.1;
          }

          .MicroSec_TCNT_Type
          {
             :kind = fixed;
             :precision = ( 0.9536743 ); 
             :range = 0.0 TO < 65535*0.9536743;
          }

  }  

#******************************************************************************
#
# Revision History:
#
# Rev.  YYMMDD Who RSM# Changes
# ----- ------ --- ---- -------------------------------------------------------
# 
#
###############################################################################

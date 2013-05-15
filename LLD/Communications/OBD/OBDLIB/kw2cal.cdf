#******************************************************************************
#* Filename:             kw2cal.cdf
#*
#* Description:          This file contains the definition of the calibration
#*                       constant, tables as declared in the c2_cal.c file
#*
#* List of functions:    None
#*
#* List of inlines:      None
#*
#* #******************************************************************************/
cl2_fixed
{
          .t_byte 
          { 
             :kind = fixed; 
             :precision = 1;
             :range = 0 TO 255; 
          } 
          .t_ubyte
          {
              :kind = fixed;
              :precision =1;
              :range = 0 TO <256;
          }
          .t_word 
          { 
             :kind = fixed; 
             :precision = 1; 
             :range = 0 TO 65535; 
          } 
          .t_udword 
          { 
             :kind = fixed; 
             :precision = 1;
             :range = 0 TO 4294967295;
          } 
          .t_w_R31p25ms
          {
             :kind = fixed;
             :precision = 0.03125;              # 31.25/1000
             :range = 0.0 TO 0.03125*65535;    # 2047.96875 seconds
          }
          .t_y_R31p25ms
          {
             :kind = fixed;
             :precision = 0.03125;              # 31.25/1000
             :range = 0.0 TO 0.03125*255;      # 7.96875 seconds
          }
          .t_voltb
          {
             :kind = fixed;
             :precision = 0.000488281;
             :range = 0 TO 65535*0.000488281;
          }
}

cl2_anns
{
   .mode_01_pids
   {
     :kind = define_annotation;
     :units = "Bit Encoded";
     :table = (0, 1, 2, 3);
   }  
   .mode_02_pids
   {
     :kind = define_annotation;
     :units = "Bit Encoded";
     :table = (0, 1, 2, 3);
   }
   .index_0_to_0
   {
    :kind = define_annotation;
    :units = "Bit Encoded";
    :table = (0);
   }
   .index_0_to_1
   {
    :kind = define_annotation;
    :units = "Bit Encoded";
    :table = (0, 1);
   }
   .char_16_values
   {
    :kind = define_annotation;
    :units = "Bit Encoded";
    :table = (0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
   }    
   .mode_08_testRange
   {
     :kind = define_annotation;
     :units = "Bit Encoded";
     :table = (0, 1, 2, 3);
   }
   .mode_06_TestIDs
   {
     :kind = define_annotation;
     :units = "Bit Encoded";
     :table = (0, 1, 2, 3, 4, 5, 6);
   }
   .mode_06_TestRange
   {
     :kind = define_annotation;
     :units = "Bit Encoded";
     :table = (0, 1, 2, 3);
   }
   .mode_01_PID20_Thru40
   {
     :kind = define_annotation;
     :units = "Bit Encoded";
     :table = (0, 1, 2, 3);
   }
   .mode_01_PID40_Thru60
   {
     :kind = define_annotation;
     :units = "Bit Encoded";
     :table = (0, 1, 2, 3);
   }
   .mode_02_PID20_Thru40
   {
     :kind = define_annotation;
     :units = "Bit Encoded";
     :table = (0, 1, 2, 3);
   }
   .mode_02_PID40_Thru60
   {
     :kind = define_annotation;
     :units = "Bit Encoded";
     :table = (0, 1, 2, 3);
   }
   .mode_05_TestID_Supported
   { 
     :kind = define_annotation;
     :units = "Bit Encoded";
     :table = (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
              11, 12, 13, 14, 15, 16, 17, 18, 19);
   }
   .mode_3C_Block_14_Data
   { 
     :kind = define_annotation;
     :units = "Calibration Constant";
     :table = (0, 1, 2, 3);
   }
   .mode_3C_Block_16to17_Data
   { 
     :kind = define_annotation;
     :units = "Calibration Constant";
     :table = (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
   }
   .mode_3C_Block_18_Data
   { 
     :kind = define_annotation;
     :units = "Calibration Constant";
     :table = (0, 1);
   }
   .mode_3C_Block_19to1C_Data
   { 
     :kind = define_annotation;
     :units = "Calibration Constant";
     :table = (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
              11, 12, 13, 14, 15, 16, 17, 18, 19);
   }
   .mode_3C_Block_1Dto20_Data
   { 
     :kind = define_annotation;
     :units = "Calibration Constant";
     :table = (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
              11, 12, 13, 14, 15, 16, 17, 18, 19);
   }
   .mode_3C_Block_21_Data
   { 
     :kind = define_annotation;
     :units = "Calibration Constant";
     :table = (0, 1);
   }
}

#*:calsets.c2_cals = c2_cal;
#*****************************************************************************
#
# Testing date:                
#  
# Revision history:
#    Rev 1.1   27 Jan 1998      CGSmith
#       Created module from CGS Baseline for Class-2
#    Rev 1.2   26 May 1998      CGSmith
#       Integrated Offline Level 10, 11 and 12 changes 
#       to Mainline Node 
#    Rev 1.3   08 July 1998    CGSmith
#       Changed as per Level 13 release 
#    Rev 1.4   24 July 1998    CGSmith
#       Added support for K_BC_Data
#       Changed as per level 14 release  
#    Rev 1.5   05 Aug. 1998    John Zha
#       Create for reuser kw2000 program   
#    Rev 1.6   07 Aug. 1998    Carl Walthall
#       Create for reuser kw2000 program
#    Rev 1.7   08 Nov. 1999    Haifan Fu
#       Delete unused definition in kw2000 program
#
#    SCR       mm/dd/yy    Author
#    mt20u2#16 29/07/05    Liu Shoujun
#    + Error Correction added into Level 6B 
#      - Added Ka1979_M1_PID40_Thru60_Supp
#
# 12/09/05     LShoujun    mt20u2#25 
#  + Updated i6lgen.exe to version 3.3
#    - Changed the CALDEF for the CALs in kw2cal
# 
# March/09/2006 Q.W        mt20u2#47
#  + Support SAE J1979 kw2000 modes
#    - Define type: t_ubyte
#****************************************************************************/
#
# $Source: ems_project@brighton.tcb:daewoo_2002:kw2cal.cdf $
# $Revision: 1.1 $
# $Author: brighton.tcb:/users/safayyad...daewoo_2002_MathLib:safayyad $
#

#!/usr/contrib/bin/perl
###############################################################################
#
# This script does postprocessing of a2l-file.
# The result is printed on STDOUT.
# It can be used for Excalibur or Tricore input a2l-files.
#
# Syntax:
#
#   a2lcorr.pl a2l_file_name a2l_patch_file_name <corr_mode_mask>
#
# Use the following corr_mode_mask value to turn on/off required correction
# (by default corr_mode_mask is set to 0xFFFF):
#
#
#   x x x x  x x x x  x x x x  x x x x  (binary)
#   | | | |  | | | |  | | | |  | | | |
#   | | | |  | | | |  | | | |  | | | |
#   | | | |  | | | |  | | | |  | | | +- Patch a2l-file (PatchA2lBuff)
#   | | | |  | | | |  | | | |  | | |      0: Off
#   | | | |  | | | |  | | | |  | | |      1: On
#   | | | |  | | | |  | | | |  | | +--- Not implemented
#   | | | |  | | | |  | | | |  | |        0: Off
#   | | | |  | | | |  | | | |  | |        1: On
#   | | | |  | | | |  | | | |  | +----- Correct DGDM bit-fields (FixDgdmA2lBuff)
#   | | | |  | | | |  | | | |  |          0: Off
#   | | | |  | | | |  | | | |  |          1: On
#   | | | |  | | | |  | | | |  +------- Fix wrong annotation definitions (FixAnnsA2lBuff)
#   | | | |  | | | |  | | | |             0: Off
#   | | | |  | | | |  | | | |             1: On
#   | | | |  | | | |  | | | +---------- Swap long/short names (SwapNamesA2lBuff)
#   | | | |  | | | |  | | |               0: Off
#   | | | |  | | | |  | | |               1: On
#   | | | |  | | | |  | | +------------ Remove EGRS symbols (RemoveEGRS_A2lBuff)
#   | | | |  | | | |  | |                 0: Off
#   | | | |  | | | |  | |                 1: On
#   | | | |  | | | |  | +-------------- Not implemented
#   | | | |  | | | |  |                   0: Off
#   | | | |  | | | |  |                   1: On
#   | | | |  | | | |  +---------------- Remove obsolete DGDM calibrations (RemoveDGDM_CalsA2lBuff)
#   | | | |  | | | |                      0: Off
#   | | | |  | | | |                      1: On
#   | | | |  | | | +------------------- Generate complete list of DGDM numerator measurements (GenDGDM_NumrtrsA2lBuff)
#   | | | |  | | |                        0: Off
#   | | | |  | | |                        1: On
#   | | | |  | | +--------------------- Add System Configuration calibrations folder (AddSystemConfigCalsA2lBuff)
#   | | | |  | |                          0: Off
#   | | | |  | |                          1: On
#   | | | |  | +----------------------- Not implemented
#   | | | |  |                            0: Off
#   | | | |  |                            1: On
#   | | | |  +------------------------- Fix Measurement Size (FixMeasSizeA2lBuff)
#   | | | |                               0: Off
#   | | | |                               1: On
#   | | | +---------------------------- Remove not needed measurements (RemoveMeasurementsA2lBuff)
#   | | |                                 0: Off
#   | | |                                 1: On
#   | | +------------------------------ Separate DGDM Transmission calibrations (SeprtDGDM_CalsA2lBuff)
#   | |                                   0: Off
#   | |                                   1: On
#   | +-------------------------------- Not implemented
#   |                                     0: Off
#   |                                     1: On
#   +---------------------------------- Not implemented
#                                         0: Off
#                                         1: On
#
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#
# Rev.  YYMMDD Who Changes
# ----- ------ --- ------------------------------------------------------------
# 1.1   020416 gps Initial release.
# 1.2   020429 woz Corrected bitmasks for KwDGDM_DummyBits and KwDGDM_P_Code.
# 1.3   020612 gps Corrected FixDgdmA2lBuff processing.
#                  Added RemoveEGRS_A2lBuff to get rid off all EGRS specific
#                   symbols.
# 1.4   020824 gps Modified SwapNamesA2lBuff in order to completely implement
#                   substitution of long with short names.
# 1.5   021106 gps Corrected SwapNamesA2lBuff to support real anc-record format
#                   (description field doesn't have to provide short name).
# 1.6   030311 gps Corrected bitmasks for KeDGDM_DenomId and KwDGDM_DummyBits.
#                  Added CorrectTnblAxisA2lBuff to fix tunable axis definitions.
#                  Improved SwapNamesA2lBuff
# 1.7   030320 gps Improved CorrectTnblAxisA2lBuff.
# 1.8   030411 gps Improved RemoveEGRS_A2lBuff.
#                  Added RemoveDGDM_CalsA2lBuff.
# 1.9   030411 gps Updated RemoveDGDM_CalsA2lBuff.
# 2.0   030428 hdb 2608  Check for space end of line after coefficients to
#                        make the checks more specific.
# 2.1   030503 kan Updated RemoveDGDM_CalsA2lBuff
# 2.2   030604 gps Corrected CorrectTnblAxisA2lBuff.
# 2.3   030605 gps Supplemental fix to CorrectTnblAxisA2lBuff.
# 2.4   030606 caw Added KtEXAC_AXIS_EngSpdAirflowDelta to something.
# 2.5   030606 caw Updated CorrectTnblAxisA2lBuff.
# 2.6   030607 arr Fixed t_w_R7p8125ms_grams/sec
# 2.7   030606 caw Updated CorrectTnblAxisA2lBuff.
# 2.8   030618 ksr Updated CorrectTnblAxisA2lBuff.
# 2.9   030620 gps Corrected CorrectTnblAxisA2lBuff AXIS_PTS_REF line
#                   processing error.
# 3.0   030623 gps CorrectTnblAxisA2lBuff Improvements.
#                  Substituted static @ta_comp_method_list
#                   with @ta_comp_method_param_list.
# 3.1   030623 gps Added FixETC_BitFieldsA2lBuff.
# tci_pt3#3.2
#       030711 ela Updated CorrectTnblAxisA2lBuff to include
#                  KtEXAC_k_CatTempIncreasing and KtEXAC_k_CatTempDecreasing
# 3.3   030725 caw Updated CorrectTnblAxisA2lBuff to include
#                   KtELCL_AXIS_PWMFanDC.
# 3.2.1.1
#       030807 ksr CorrectTnblAxisA2lBuff for Torque.
#              gps Updated script to warn if the AXIS cal is not found.
# tci_pt3#3.3
#       030711 PVD Added new function AddSystemConfigCalsA2lBuff to add
#                  system configuration cals.
# 3.3.1.3
#       030925 gps BOOLEAN anc-definition Corrections,
#                  Masking DC2 Related Measurements.
#                  Optimized the following subroutines:
#                   CorrectTnblAxisA2lBuff,
#                   AddSystemConfigCalsA2lBuff,
#                   FixETC_BitFieldsA2lBuff.
#                  Added:
#                   FixUlongBooleansA2lBuff,
#                   RemoveMeasurementsA2lBuff.
# 3.5   030925 gps VCPS : Disabling Faults and Ratio Monitor
#                   for Cam Phasing.
#                  Modified FixDgdmA2lBuff (adjustments to KeDGDM_DenomId).
# 3.3.1.1.1.1
#       030924 kan Updated CorrectTnblAxisA2lBuff to include
#                  KtEXAC_k_CatTgtIncreasing and KtEXAC_k_CatTgtDecreasing
# 3.6   030928 arr ---- Merged 'a2lcorr.pl-3.5' with 'a2lcorr.pl-3.3.1.1.1.1'.
# 3.7   030930 gps UWORD definitions interpreted as ULONG corrections.
#                  Added FixUlongWordsA2lBuff.
#                  Corrected CorrectTnblAxisA2lBuff.
# 3.8   031002 rag Merge 3.6.1.1 and 3.7.
# 3.9   031009 ses Added KtEOSD_I_HtrCurrThrsh_Brkpts
# 4.0   031011 gps Corrected KtEOSD_I_HtrCurrThrsh_Brkpts implementation.
#                  Simplified CorrectTnblAxisA2lBuff.
# 4.2   031029 gps Combined the following subroutines:
#                    FixUlongBooleansA2lBuff,
#                    FixUlongWordsA2lBuff
#                   into one FixMeasSizeA2lBuff.
#                  Added SCUCOR to the processing list.
# tci_pt3#4.2
#       031105 mm  Added KtFLOS_T_CoolantTemp_Brkpts.
# tci_pt3#4.4
#       031203 mm  Added VRFATSR and EAP12TSR in FixMeasSizeA2lBuff.
# 4.5   031216 ksr Added  : KeTRVC_TransCntrlType. Removed KeTRVC_TransType &
#                  KeTRVC_AutoTransCntrlType from AddSystemConfigCalsA2lBuff.
# 4.8   040201 gps TOOLS : a2lcorr.pl Modifications.
#                  Removal of Extra Old Type Checking in FixMeasSizeA2lBuff.
# 4.6.1.1
#       040212 arr Added TCDRMRES to update its size.
# 4.9   040212 arr Merged 'a2lcorr.pl-4.8' with 'a2lcorr.pl-4.6.1.1.1'.
# 4.10  040219 gps Corrected "unit selection logic" in CorrectTnblAxisA2lBuff.
# 5.0   040226 ksr Added KtSPRK_AXIS_IdleCL_SparkDelayTime as tunable axis.
# 4.11  040220 gps DGDM : FRxPCODE and FRxPCODE Corrections.
#                  Created CorrFailRecDefsA2lBuff.
#                  Updated FixMeasSizeA2lBuff.
# 4.6   040217 jyz Added: KtFLOS_t_FntMaxDcTmr
# 4.7   040219 jyz Added: KtFLOS_t_ExTempModelDelayTmrThrsh
#                         KtVIOS_t_PumpingCircuitDelayTime
# 4.11  040302 arr Merged 'a2lcorr.pl-4.10' with 'a2lcorr.pl-4.6.1.2.2'.
# 4.6.2 040126 gps VCPS : Correct Small Phaser Sizes in Response Diagnostic.
#                  Updated CorrectTnblAxisA2lBuff.
# 6.0   040308 gps Merged 'a2lcorr.pl-4.6.2' with 'a2lcorr.pl-4.12'.
# 5.1   040309 as -BM- Merged 'a2lcorr.pl-4.12' with 'a2lcorr.pl-5.0'.
# 6.1   040309 as -BM- Merged 'a2lcorr.pl-6.0' with 'a2lcorr.pl-5.1'.
# 4.9.1 040228 hdb Added SQDN entries to tunable axis.
# 6.2   040309 arr Merged 'a2lcorr.pl-6.1' with 'a2lcorr.pl-4.9.1'.
# 6.3   040311 arr Fixed missing comma.
# 6.4   040315 gps ETCD Measurement Size Corrections.
#                  Removed FixETC_BitFieldsA2lBuff.
# tcb_pt1#2
#       040604 kan Made part of MT34 project
# 6.4.1.1
#       040406 jyz Added KtTORQ_M_TipInBumpRampRateGear6
# 6.4.2 040414 gps VCPS : Include New Advance and Retard
#                   Distinction in Phaser Response Diagnostic.
#                  Updated CorrectTnblAxisA2lBuff.
# 6.4.3 040427 gps Merged 'a2lcorr.pl-6.4.1.1' with 'a2lcorr.pl-6.4.2'.
# 6.4.1.2
#       040426 ksr Added KtTORQ_r_TipInBumpRampRateModAT
# 6.4.3.1
#       040424 jyz Added KtSPRK_AXIS_IAT_TipInRetScalar
#                        KtSPRK_IAT_TipInRetScalar
#                        KtSPRK_phi_CrankCltRPM
#                        KtSPRK_t_IdleCL_SparkDelayTime
#                        KtSPRK_phi_CrankToRunDownStep
#                        KtSPRK_phi_CrankToRunUpStep
#                        KtSPRK_AXIS_CoolantTemp
# 6.4.3 040422 caw Added Cal Axis for: KtTORQ_M_TipInBumpRampRateGr14W
# 6.4.3.1
#       040427 rmn ----  Merged 'a2lcorr.pl-6.4.3.1' with 'a2lcorr.pl-6.4.2.1'.
# 6.6   040427 gps Merged 'a2lcorr.pl-6.4.3' with 'a2lcorr.pl-6.4.1.2.1.1'.
# 6.4.1.1.1.1
#       040427  pd Added EBKDCLTM,EBKONTMR,EBKSWDTM
# 6.7   040428 arr Merged 'a2lcorr.pl-6.6' with 'a2lcorr.pl-6.4.1.1.1.1'.
# 6.8   040430  pd Deleted EBKDCLTM,EBKONTMR,EBKSWDTM
# 3.0   040803 rag Merge with Latest Reuse Version
# 4.0   040923 kan RSM 4438, Modify sub FixDgdmA2lBuff so that COT bitfield cal
#                   ConvTempOption is displayed correctly in A2L file
# 3.1.1 040928 rag Merge with Latest Reuse
# 6.8.1.1
#       040621 rmn 4083 Added cal axis for the all the cals KtSQUP_DC_xxOnAppStdDCBase
# 6.10  040713 gps RSM #04207; DGDM : Change a2l File Generation Process
#                   to Allow Visibility of All Ratio Monitor Numerators in INCA.
#                  Added GenDGDM_NumrtrsA2lBuff.
#
###############################################################################
#
# Rev.  YYMMDD Who RSM  Changes
# ----- ------ --- ------------------------------------------------------------
# 6.9   040713 caw 4152 Added: KtIDLE_AXIS_p_PS_DeltaOffset
#                              KtIDLE_AXIS_p_PS_Offset
# 6.11  040714 caw  BM  Merge
# 6.9   040713 ela 4190 Changed from UBYTE to UWORD for the following parameters
#                       FR1DTCID, FR2DTCID, FR3DTCID, and FR4DTCID.
# 6.13  040726 as  -BM- Merged 'a2lcorr.pl-6.12' with 'a2lcorr.pl-tci_pt3#6.9'
# 7.0   040804 hdb 4312 SQSR:ARFA 390 ; Modify 0% LR control method during R-N
#                       shift: add tunable axis KtSQSR_AXIS_t_TimePRNDL_InReverse
# 6.12.1.1
#       040728 jyz 4283 Added: KtETSE_AXIS_K_Runner_CLT_Corr
# 6.12.1.2
#       040819 caw BM   Merged changes.
# 6.14  040827 ksr 4291 Added: KtTORQ_r_TipInBumpRampRateModAT_Gear1 - 6

# 7.1.1 040910 jyz 4429 Added KtELCL_Pct_AC_VeryLowLoadDC
# 7.1   040819 arr 3726 SQSR_ARFA_310 : Adding LR 100% DC hold control when cold
#                        (During NR control)
# 7.2   040909 arr 3726 Renamed KtSQSR_Cnt_NR_FullDC_Delay to
#                        KtSQSR_t_NR_FullDC_LowTempDelay and made time based.
# 8.4   040713 gps 4547 TRNS : ARFA0448, Power On Upshift Release Time Table Redefinitons
#                        (Input TQI -> TOS, TQI).
#                       Updated CorrectTnblAxisA2lBuff.
# 6.12.1.1
#       040728 jyz 4283 Added: KtETSE_AXIS_K_Runner_CLT_Corr
# 9.0   041020 wei -BM- Merged 'a2lcorr.pl-6.12.1.1' with 'a2lcorr.pl-7.0.1.2'.
# 7.0.1.1.1.1
#       041015 rmn 4533 Added KtTORQ_AXIS_UpShfTqRedAbsSpark
# 9.1   041020 wei -BM- Merged 'a2lcorr.pl-7.0.1.1.1.1' with 'a2lcorr.pl-9.0'.
# 9.2   041024 hdb ---- Add axis definitions for AbuseTqRdctPOffUp cals.
# 8.5   041028 rmn ---- Merged 'a2lcorr.pl-8.3' with 'a2lcorr.pl-9.2'.
# 8.6   041103 gps ---- Merged 'a2lcorr.pl-8.4' with 'a2lcorr.pl-8.5'.
# 8.6.1 041129 hdb 4557 ARFA0432 (SQDN part) Enhance POnDnLS control during
#                        POffUp with torque reduction control.
#                        Add tunable axis KtSQDN_AXIS_n_PrstRl_LSRtnDwn2
# 8.6.1.1
#       041130 jyz 4512 Added KtSPRK_IAT_EngineSpeedMult
# 10.0  041203 wei -BM- Merged 'a2lcorr.pl-8.6.1' with 'a2lcorr.pl-8.6.1.1'.
# tci_pt3 8.7
#       041203 ela ---- Merged 'a2lcorr.pl-8.6' with 'a2lcorr.pl-tci pt3 8.6'.
# 10.1  041204 gps ---- Merged 'a2lcorr.pl-10.0' with 'a2lcorr.pl-tci_pt3#8.7'.
# 8.6.2.1
#       041203 gps 4682 IDLE : P/N/D/R Shift Load Compensation Tables Conversion.
#                       Updated CorrectTnblAxisA2lBuff.
# 10.2  041203 gps 4682 IDLE : P/N/D/R Shift Load Compensation Tables Conversion.
#                       Merged 'a2lcorr.pl-10.1' with 'a2lcorr.pl-8.6.2.1'.
# 10.3  041206 gps 4665 DGDM/A2l : Separate Engine and Transmission DGDM Calibrations
#                       Added SeprtDGDM_CalsA2lBuff.
# 8.3.2.1
#       041116 jyz 4612 Make CVNCRC to display as ULONG
# 10.4  041206 gps ---- Merged 'a2lcorr.pl-10.3' with 'a2lcorr.pl-8.3.2.1'.
# 7     050119 gps 4790 SOFT: Update GMDAT version of Perl script a2lcorr.pl
#                        to match that being used in Reuse Software.
# 8     050302 aob 4841 Added KtIDLE_AXIS_n_Prop_Control and 
#                        KtIDLE_AXIS_n_Integral_Control.
# 9
#       050509 hdb 5126 Ram diagnostic corrections
#                       Update FRAMSADR and FRAMTADR to ULONG.
# 9.1.1 051003 at  -BM- Added KtEPSE_dm_Std_PurgeValveFlow
#                             KtEPSE_dm_Std_PurgeValveTnkFlow
#                             KtEPSE_AXIS_Std_PurgeValveFlow
#                             KtETCS_Pct_TPS_NoiseLimMaxTPS
#                             KtETCS_AXIS_TPS_NoiseLimMaxTPS
#                             KtIDLE_PS_CrampAF_OfstRPM_Mult
#                             KtIDLE_n_AXIS_PS_CrampAF_OfstMult
#                       
# 9.1.2 051006 at  -BM- Added AXIS entries for: KtFLOS_AXIS_T_DsrdFntHtrVolts
#                                               KtFLOS_AXIS_T_DsrdRrHtrVolts
#                                               KtIDLE_AXIS_BatVoltAirflowOfst
#       051129 wei -BM- Added AXIS for KtIDLE_AXIS_AlterPWM_RPM_VSSMult
#                                      KtTORQ_AXIS_TC_LoadTorq
# 5     060213 hdb 5490 Update anc files to latest toolset.
#                        Remove tunable axis processing.
#                        Uncheck coefficient accuracy.
# 6     060313 hdb 5490 Remove coefficient accuracy.
#                       Remove fix to DGDM arrays due to changes in i6lgen.
#
###############################################################################
#
# Current Module Info:
# %version:        7 %
# %full_name:      tcb_pt1#1/Perl/a2lcorr.pl/7 %
# %date_created:   Wed Jan 19 10:10:23 2005 %
# %derived_by:     pzb6v4 %
#
###############################################################################

# Constants

$errNA  =  1;
$errOK  =  0;
$errNOK = -1;

$true  = 1;
$false = 0;

# Global Variables

$ErrCode = $errOK;

$OLD_BEGIN_REXP="\\/\\/\\*\\s+old\\s+first\\s+\\*\\/\\/";
$OLD_END_REXP="\\/\\/\\*\\s+old\\s+last\\s+\\*\\/\\/";
$NEW_BEGIN_REXP="\\/\\/\\*\\s+new\\s+begin\\s+\\*\\/\\/";
$NEW_END_REXP="\\/\\/\\*\\s+new\\s+end\\s+\\*\\/\\/";

$A2lFileName      = "leccore1.a2l";
$A2lPatchFileName = "a2l_patch.txt";
$CorrModeMask = 0xDB9D;

$TmpLine = "";
$LineCnt = 0;
$StartProccessing = $false;

###############################################################################
#
# Subroutines
#
###############################################################################
sub PrintList
{
  local( *list ) = @_;

  foreach ( @list )
  {
    print STDERR "+ $_\n";
  }
}

sub PrintBuff
{
  local( *buff ) = @_;

  foreach ( @buff )
  {
    print;
  }
}

sub FillFileBuff
{
  local( *file_name, *file_buff ) = @_;
  local( $filehandler ) = -1;

  if ( !open(filehandler, $file_name) )
  {
    print STDERR "(!) FillFileBuff() : Cannot open file $file_name\n";
    return( $errNOK );
  }

  while ( <filehandler> )
  {
    push( @file_buff, $_ );
  }

  close( filehandler );
  return( $errOK );
}

sub PatchA2lBuff
{
  local( *a2l_file_buff, *a2l_patch_file_buff ) = @_;
  local( $index, $index1, $index_start ) = ( -1, -1, -1 );
  local( $old_begin_rexp_started, $old_end_rexp_started ) = ( $false, $false );
  local( $new_begin_rexp_started, $new_end_rexp_started ) = ( $false, $false );
  local( $start_expr, $end_expr ) = ( "", "" );
  local( $patch_a2l_buff, $subs_a2l_buff ) = ( $false, $false );
  local( @new_buff ) = ();

  $index = -1;
  while ( ++$index <= $#a2l_patch_file_buff )
  {
    if ( $a2l_patch_file_buff[$index] =~ /$OLD_BEGIN_REXP/ )
    {
      $start_expr = "";
      $end_expr = "";
      $patch_a2l_buff = $false;
      splice ( @new_buff, 0 );
      $new_end_rexp_started = $false;
      $old_begin_rexp_started = $true;
      $index++;
    }
    elsif ( $a2l_patch_file_buff[$index] =~ /$OLD_END_REXP/ )
    {
      $old_begin_rexp_started = $false;
      $old_end_rexp_started = $true;
      $index++;
    }
    elsif ( $a2l_patch_file_buff[$index] =~ /$NEW_BEGIN_REXP/ )
    {
      $old_end_rexp_started = $false;
      $new_begin_rexp_started = $true;
      $index++;
    }
    elsif ( $a2l_patch_file_buff[$index] =~ /$NEW_END_REXP/ )
    {
      $new_begin_rexp_started = $false;
      $new_end_rexp_started = $true;
      $patch_a2l_buff = $true;
    }

    if ( ($old_begin_rexp_started == $true)
      && ($a2l_patch_file_buff[$index] =~ /\S/) )
    {
      $start_expr = $a2l_patch_file_buff[$index];
      ($start_expr = $start_expr) =~ s/^\s+//;
      ($start_expr = $start_expr) =~ s/\s+$//;
    }
    elsif ( ($old_end_rexp_started == $true)
         && ($a2l_patch_file_buff[$index] =~ /\S/) )

    {
      $end_expr = $a2l_patch_file_buff[$index];
      ($end_expr = $end_expr) =~ s/^\s+//;
      ($end_expr = $end_expr) =~ s/\s+$//;
    }

    if ( $new_begin_rexp_started == $true )
    {
      push( @new_buff, $a2l_patch_file_buff[$index] );
    }

    if ( $patch_a2l_buff == $true )
    {
      if ( $start_expr eq "" || $end_expr eq "" || ($#new_buff<0) )
      {
        print STDERR "(!) PatchA2lBuff() : Patch file cannot be proccesed.\n";
        return( $errNOK );
      }
      $index1 = -1;
      $subs_a2l_buff = $false;
      while ( ++$index1 <= $#a2l_file_buff )
      {
        if ( $subs_a2l_buff == $false )
        {
          if ( $a2l_file_buff[$index1] =~ /$start_expr/ )
          {
            $index_start = $index1;
            $subs_a2l_buff = $true;
          }
        }
        else
        {
          if ( $a2l_file_buff[$index1] =~ /$end_expr/ )
          {
            $subs_a2l_buff = $false;
            splice( @a2l_file_buff, $index_start, $index1-$index_start+1, @new_buff );
            $index1 = $#a2l_file_buff + 1;
          }
        }
      }
      if ( $index1 != $#a2l_file_buff + 2 )
      {
        print STDERR "(!) PatchA2lBuff() : A2l file cannot be proccesed.\n";
        return( $errNOK );
      }

      $new_begin_rexp_started = $false;
      $patch_a2l_buff = $false;
    }
  }

  return( $errOK );
}

sub FixDgdmA2lBuff
{
  local( *a2l_file_buff ) = @_;
  local( $index ) = -1;
  local( $start_processing ) = $false;
  local( $tmp_line ) = "";
  local( $mask, $max_range ) = ( "", "" );

  $start_processing = $false;
  $index = -1;
  while ( ++$index <= $#a2l_file_buff )
  {
    $tmp_line = $a2l_file_buff[$index];
    if ( $start_processing == $false )
    {
      if ( $tmp_line =~ /\/begin\s+CHARACTERISTIC\s+KsDGDM_[^.]+\.(\w+)/ )
      {
        $start_processing = $true;

        #################################################################
        #
        #    WORD  KeDGDM_DTC_DepListId : 3;  /* byte   0, bits 0-2 */
        #    WORD  KeDGDM_LightEnable : 1;    /* byte   0, bit   3  */
        #    WORD  KbDGDM_FaultTypeC : 1;     /* byte   0, bit   4  */
        #    WORD  KbDGDM_FaultTypeE : 1;     /* byte   0, bit   5  */
        #    WORD  KbDGDM_FaultTypeB : 1;     /* byte   0, bit   6  */
        #    WORD  KbDGDM_FaultTypeA : 1;     /* byte   0, bit   7  */
        #    WORD  KeDGDM_DenomId    : 6;     /* byte   1, bits 0-5 */
        #    WORD  KwDGDM_DummyBits  : 2;     /* byte   1, bits 6-7 */
        #    WORD  KwDGDM_P_Code : 16;        /* bytes 2-3: LSB/MSB */
        #
        ##################################################################

        if ( $1 eq "KeDGDM_DTC_DepListId" )
        {
          $mask = "0x00000007";
          $max_range = "7.000000";
        }
        elsif ( $1 eq "KeDGDM_LightEnable" )
        {
          $mask = "0x00000008";
          $max_range = "1.000000";
        }
        elsif ( $1 eq "KbDGDM_FaultTypeC" )
        {
          $mask = "0x00000010";
          $max_range = "1.000000";
        }
        elsif ( $1 eq "KbDGDM_FaultTypeE" )
        {
          $mask = "0x00000020";
          $max_range = "1.000000";
        }
        elsif ( $1 eq "KbDGDM_FaultTypeB" )
        {
          $mask = "0x00000040";
          $max_range = "1.000000";
        }
        elsif ( $1 eq "KbDGDM_FaultTypeA" )
        {
          $mask = "0x00000080";
          $max_range = "1.000000";
        }
        elsif ( $1 eq "KeDGDM_DenomId" )
        {
          $mask = "0x0000003F";
          $max_range = "63.000000";
        }
        elsif ( $1 eq "KwDGDM_DummyBits" )
        {
          $mask = "0x000000C0";
          $max_range = "3.000000";
        }
        elsif ( $1 eq "KwDGDM_P_Code" )
        {
          $mask = "0x0000FFFF";
          $max_range = "65535.000000";
        }
        else
        {
          $start_processing = $false;
        }
      }
      ##############################################################################
      # For COT Bitfield calibration ConvTempOption
      ##############################################################################
      elsif ( $tmp_line =~ /\/begin\s+CHARACTERISTIC\s+ConvTempOption[^.]*\.(\w+)/ )
      {
        $start_processing = $true;

        #################################################################
        #
        #  WORD UnusedBit8              : 1;      /* byte   0, bit   0  */
        #  WORD UnusedBit9              : 1;      /* byte   0, bit   1  */
        #  WORD UnusedBit10             : 1;      /* byte   0, bit   2  */
        #  WORD UnusedBit11             : 1;      /* byte   0, bit   3  */
        #  WORD UnusedBit12             : 1;      /* byte   0, bit   4  */
        #  WORD BlmUpdateForDevelopment : 1;      /* byte   0, bit   5  */
        #  WORD BlmLearnInConvProt      : 1;      /* byte   0, bit   6  */
        #  WORD ConvProtectionEnable    : 1;      /* byte   0, bit   7  */
        #  WORD UnusedBit0              : 1;      /* byte   1, bit   0  */
        #  WORD UnusedBit1              : 1;      /* byte   1, bit   1  */
        #  WORD UnusedBit2              : 1;      /* byte   1, bit   2  */
        #  WORD UnusedBit3              : 1;      /* byte   1, bit   3  */
        #  WORD UnusedBit4              : 1;      /* byte   1, bit   4  */
        #  WORD UnusedBit5              : 1;      /* byte   1, bit   5  */
        #  WORD UnusedBit6              : 1;      /* byte   1, bit   6  */
        #  WORD UnusedBit7              : 1;      /* byte   1, bit   7  */
        #
        ##################################################################

        if ( $1 eq "UnusedBit8" )
        {
          $mask = "0x00000001";
          $max_range = "1.000000";
        }
        elsif ( $1 eq "UnusedBit9" )
        {
          $mask = "0x00000002";
          $max_range = "1.000000";
        }
        elsif ( $1 eq "UnusedBit10" )
        {
          $mask = "0x00000004";
          $max_range = "1.000000";
        }
        elsif ( $1 eq "UnusedBit11" )
        {
          $mask = "0x00000008";
          $max_range = "1.000000";
        }
        elsif ( $1 eq "UnusedBit12" )
        {
          $mask = "0x00000010";
          $max_range = "1.000000";
        }
        elsif ( $1 eq "BlmUpdateForDevelopment" )
        {
          $mask = "0x00000020";
          $max_range = "1.000000";
        }
        elsif ( $1 eq "BlmLearnInConvProt" )
        {
          $mask = "0x00000040";
          $max_range = "1.000000";
        }
        elsif ( $1 eq "ConvProtectionEnable" )
        {
          $mask = "0x00000080";
          $max_range = "1.000000";
        }
        elsif ( $1 eq "UnusedBit0" )
        {
          $mask = "0x00000100";
          $max_range = "1.000000";
        }
        elsif ( $1 eq "UnusedBit1" )
        {
          $mask = "0x00000200";
          $max_range = "1.000000";
        }
        elsif ( $1 eq "UnusedBit2" )
        {
          $mask = "0x00000400";
          $max_range = "1.000000";
        }
        elsif ( $1 eq "UnusedBit3" )
        {
          $mask = "0x00000800";
          $max_range = "1.000000";
        }
        elsif ( $1 eq "UnusedBit4" )
        {
          $mask = "0x00001000";
          $max_range = "1.000000";
        }
        elsif ( $1 eq "UnusedBit5" )
        {
          $mask = "0x00002000";
          $max_range = "1.000000";
        }
        elsif ( $1 eq "UnusedBit6" )
        {
          $mask = "0x00004000";
          $max_range = "1.000000";
        }
        elsif ( $1 eq "UnusedBit7" )
        {
          $mask = "0x00008000";
          $max_range = "1.000000";
        }
        else
        {
          $start_processing = $false;
        }
      }
    }
    else
    {
      if ( $tmp_line =~ /\/end\s+CHARACTERISTIC/ )
      {
        $start_processing = $false;
      }
      elsif ( $tmp_line =~ /(0\s+)\d+\.\d+/ )
      {
        $tmp_line = $` . $1 . $max_range . $';
        $a2l_file_buff[$index] = $tmp_line;
      }
      elsif ( $tmp_line =~ /(BIT_MASK\s+)\w+/ )
      {
        $tmp_line = $` . $1 . $mask . $';
        $start_processing = $false;
        $a2l_file_buff[$index] = $tmp_line;
      }
    }
  }

  return( $errOK );
}

sub FixAnnsA2lBuff
{
  local( *a2l_file_buff ) = @_;
  local( $index ) = -1;
  local( $start_processing ) = $false;
  local( $tmp_line ) = "";
  local( $line_cnt ) = -1;

  $start_processing = $false;
  $index = -1;
  while ( ++$index <= $#a2l_file_buff )
  {
    $tmp_line = $a2l_file_buff[$index];
    if ( $start_processing == $false )
    {
      if ( $tmp_line =~ /\/begin\s+AXIS_DESCR\s+FIX_AXIS/ )
      {
        $start_processing = $true;
        $line_cnt = 0;
      }
    }
    else
    {
      if ( ++$line_cnt == 2 )
      {
        if ( $tmp_line =~ /(\w+\.)/ )
        {
          $tmp_line = "$`$'";
          $a2l_file_buff[$index] = $tmp_line;
          $start_processing = $false;
        }
      }
    }
  }

  return( $errOK );
}

sub SwapNamesA2lBuff
{
  local( *a2l_file_buff ) = @_;
  local( $index ) = -1;
  local( $start_processing ) = $false;
  local( $offset ) = -1;
  local( $tmp_line ) = "";
  local( $short_name, $long_name, $end_line ) = ( "", "", "" );
  local( %short_name_list ) = ();

  $start_processing = $false;
  $index = -1;
  while ( ++$index <= $#a2l_file_buff )
  {
    $tmp_line = $a2l_file_buff[$index];
    if ( $start_processing == $false )
    {
      if ( $tmp_line =~ /^(\s*\/begin\s+MEASUREMENT\s+)([a-zA-Z0-9_\.\[\]]+)/ )
      {
        $start_processing = $true;
        $a2l_file_buff[$index] = $1;
        $long_name = $2;
        $end_line = $';
        $offset = 0;
      }
    }
    else
    {
      ++$offset;
      if ( $tmp_line =~ /^(\s*DISPLAY_IDENTIFIER\s+)(\w+)/ )
      {
        $short_name = $2;
        $tmp_line = $1 . $long_name . $';
        $a2l_file_buff[$index] = $tmp_line;
        $a2l_file_buff[$index-$offset] = $a2l_file_buff[$index-$offset] . $short_name . $end_line;
        $short_name_list{$long_name} = $short_name;
        $start_processing = $false;
      }
    }
  }

  $start_processing = $false;
  $index = -1;
  while ( ++$index <= $#a2l_file_buff )
  {
    $tmp_line = $a2l_file_buff[$index];
    if ( $start_processing == $false )
    {
      if ( $tmp_line =~ /\/begin\s+LOC_MEASUREMENT\s+/ )
      {
        $start_processing = $true;
      }
    }
    else
    {
      if ( $tmp_line =~ /\/end\s+LOC_MEASUREMENT/ )
      {
        $start_processing = $false;
      }
    }
    if ( $start_processing == $true )
    {
      if ( $tmp_line =~ /([a-zA-Z0-9_\.\[\]]+)(\s*$)/ )
      {
        if ( ! defined($short_name_list{$1}) )
        {
          print STDERR "(!) SwapNamesA2lBuff() : No replacement for $1.\n";
#          print STDERR "$a2l_file_buff[$index-2]";
#          print STDERR "$a2l_file_buff[$index-1]";
#          print STDERR "$a2l_file_buff[$index]";
#          print STDERR "$a2l_file_buff[$index+1]";
#          print STDERR "$a2l_file_buff[$index+2]\n";
        }
        else
        {
          $tmp_line = $` . $short_name_list{$1} . $2 . $';
          $a2l_file_buff[$index] = $tmp_line;
        }
      }
    }
  }

  return( $errOK );
}

sub RemoveEGRS_A2lBuff
{
  local( *a2l_file_buff ) = @_;
  local( $index, $index1 ) = ( -1, -1 );
  local( $start_processing ) = $false;
  local( $tmp_line, $tmp_str ) = ( "", "" );
  local( %egrsym_idx_list ) = ();

  $start_processing = $false;
  $index  = -1;
  $index1 = -1;
  while ( ++$index <= $#a2l_file_buff )
  {
    $tmp_line = $a2l_file_buff[$index];
    if ( $start_processing == $false )
    {
      if ( $tmp_line =~ /\/begin\s+FUNCTION\s+(egr\w+)/ )
      {
        $start_processing = $true;
        $tmp_str = $1;
        $egrsym_idx_list{$tmp_str} = ++$index1;
        splice( @a2l_file_buff, $index, 1 );
        --$index;
      }
    }
    else
    {
      if ( $tmp_line =~ /\/end\s+FUNCTION/ )
      {
        $start_processing = $false;
      }
      elsif ( $tmp_line =~ /([a-zA-Z0-9_.]+)\s*$/ )
      {
        $tmp_str = $1;
        if ( ! ($tmp_line =~ /\/end\s+/) )
        {
          $egrsym_idx_list{$tmp_str} = ++$index1;
        }
      }
      splice( @a2l_file_buff, $index, 1 );
      --$index;
    }
  }

#  print STDERR "BEGIN\n";

  $start_processing = $false;
  $index = -1;
  while ( ++$index <= $#a2l_file_buff )
  {
    $tmp_line = $a2l_file_buff[$index];
    if ( $start_processing == $false )
    {
      if ( ($tmp_line =~ /\/begin\s+MEASUREMENT\s+([a-zA-Z0-9_.]+)/) ||
           ($tmp_line =~ /\/begin\s+CHARACTERISTIC\s+([a-zA-Z0-9_.]+)/) )
      {
        $tmp_str = $1;
        if ( defined($egrsym_idx_list{$tmp_str}) )
        {
          $start_processing = $true;
          splice( @a2l_file_buff, $index, 1 );
          --$index;
        }
      }
      elsif ( $tmp_line =~ /^\s*(\w+)\s*$/ )
      {
        $tmp_str = $1;
        if ( defined($egrsym_idx_list{$tmp_str}) )
        {
          splice( @a2l_file_buff, $index, 1 );
          --$index;
        }
      }
    }
    else
    {
      if ( ($tmp_line =~ /\/end\s+MEASUREMENT/) ||
           ($tmp_line =~ /\/end\s+CHARACTERISTIC/) )
      {
        $start_processing = $false;
      }
      splice( @a2l_file_buff, $index, 1 );
      --$index;
    }
  }

#  print STDERR "END\n";

  return( $errOK );
}


sub RemoveDGDM_CalsA2lBuff
{
  local( *a2l_file_buff ) = @_;
  local( $start_processing ) = $false;
  local( $tmp_line, $tmp_str, $tmp_str1 ) = ( "", "", "" );
  local( $index ) = ( -1 );
  local( %delsym_idx_list ) =
       (
        'KcACOD_ACClutchOutFailThrsh', 0,
        'KcACOD_ACClutchOutSampleThrsh', 1,
#        'KcESTD_FailThrsh', 2,
#        'KcESTD_SampleThrsh', 3,
        'KcVCPD_B1_Intk_CntlVlvFailThrsh', 4,
        'KcVCPD_B1_Intk_CntlVlvSmplThrsh', 5,
        'KcVCPD_B2_Intk_CntlVlvFailThrsh', 6,
        'KcVCPD_B2_Intk_CntlVlvSmplThrsh', 7,
#        'KfESTD_t_EnableDelayTime', 8,
 #       'KfESTD_U_IgnVoltResetThrsh', 9,
#        'KfINJD_n_EngSpdThrshLo', 10,
#        'KfINJD_t_InjCircuitFailThrsh', 11,
        'KsDGDM_ACCR_Open.KbDGDM_FaultTypeA', 12,
        'KsDGDM_ACCR_Open.KbDGDM_FaultTypeB', 13,
        'KsDGDM_ACCR_Open.KbDGDM_FaultTypeC', 14,
        'KsDGDM_ACCR_Open.KbDGDM_FaultTypeE', 15,
        'KsDGDM_ACCR_Open.KeDGDM_DenomId', 16,
        'KsDGDM_ACCR_Open.KeDGDM_DTC_DepListId', 17,
        'KsDGDM_ACCR_Open.KeDGDM_LightEnable', 18,
        'KsDGDM_ACCR_Open.KwDGDM_DummyBits', 19,
        'KsDGDM_ACCR_Open.KwDGDM_P_Code', 20,
        'KsDGDM_ACCR_Short.KbDGDM_FaultTypeA', 21,
        'KsDGDM_ACCR_Short.KbDGDM_FaultTypeB', 22,
        'KsDGDM_ACCR_Short.KbDGDM_FaultTypeC', 23,
        'KsDGDM_ACCR_Short.KbDGDM_FaultTypeE', 24,
        'KsDGDM_ACCR_Short.KeDGDM_DenomId', 25,
        'KsDGDM_ACCR_Short.KeDGDM_DTC_DepListId', 26,
        'KsDGDM_ACCR_Short.KeDGDM_LightEnable', 27,
        'KsDGDM_ACCR_Short.KwDGDM_DummyBits', 28,
        'KsDGDM_ACCR_Short.KwDGDM_P_Code', 29,
        'KsDGDM_CanisterPurge_Open.KbDGDM_FaultTypeA', 30,
        'KsDGDM_CanisterPurge_Open.KbDGDM_FaultTypeB', 31,
        'KsDGDM_CanisterPurge_Open.KbDGDM_FaultTypeC', 32,
        'KsDGDM_CanisterPurge_Open.KbDGDM_FaultTypeE', 33,
        'KsDGDM_CanisterPurge_Open.KeDGDM_DenomId', 34,
        'KsDGDM_CanisterPurge_Open.KeDGDM_DTC_DepListId', 35,
        'KsDGDM_CanisterPurge_Open.KeDGDM_LightEnable', 36,
        'KsDGDM_CanisterPurge_Open.KwDGDM_DummyBits', 37,
        'KsDGDM_CanisterPurge_Open.KwDGDM_P_Code', 38,
        'KsDGDM_CanisterPurge_Short.KbDGDM_FaultTypeA', 39,
        'KsDGDM_CanisterPurge_Short.KbDGDM_FaultTypeB', 40,
        'KsDGDM_CanisterPurge_Short.KbDGDM_FaultTypeC', 41,
        'KsDGDM_CanisterPurge_Short.KbDGDM_FaultTypeE', 42,
        'KsDGDM_CanisterPurge_Short.KeDGDM_DenomId', 43,
        'KsDGDM_CanisterPurge_Short.KeDGDM_DTC_DepListId', 44,
        'KsDGDM_CanisterPurge_Short.KeDGDM_LightEnable', 45,
        'KsDGDM_CanisterPurge_Short.KwDGDM_DummyBits', 46,
        'KsDGDM_CanisterPurge_Short.KwDGDM_P_Code', 47,
        'KsDGDM_EST_Cylinder_1.KbDGDM_FaultTypeA', 48,
        'KsDGDM_EST_Cylinder_1.KbDGDM_FaultTypeB', 49,
        'KsDGDM_EST_Cylinder_1.KbDGDM_FaultTypeC', 50,
        'KsDGDM_EST_Cylinder_1.KbDGDM_FaultTypeE', 51,
        'KsDGDM_EST_Cylinder_1.KeDGDM_DenomId', 52,
        'KsDGDM_EST_Cylinder_1.KeDGDM_DTC_DepListId', 53,
        'KsDGDM_EST_Cylinder_1.KeDGDM_LightEnable', 54,
        'KsDGDM_EST_Cylinder_1.KwDGDM_DummyBits', 55,
        'KsDGDM_EST_Cylinder_1.KwDGDM_P_Code', 56,
        'KsDGDM_EST_Cylinder_2.KbDGDM_FaultTypeA', 57,
        'KsDGDM_EST_Cylinder_2.KbDGDM_FaultTypeB', 58,
        'KsDGDM_EST_Cylinder_2.KbDGDM_FaultTypeC', 59,
        'KsDGDM_EST_Cylinder_2.KbDGDM_FaultTypeE', 60,
        'KsDGDM_EST_Cylinder_2.KeDGDM_DenomId', 61,
        'KsDGDM_EST_Cylinder_2.KeDGDM_DTC_DepListId', 62,
        'KsDGDM_EST_Cylinder_2.KeDGDM_LightEnable', 63,
        'KsDGDM_EST_Cylinder_2.KwDGDM_DummyBits', 64,
        'KsDGDM_EST_Cylinder_2.KwDGDM_P_Code', 65,
        'KsDGDM_EST_Cylinder_3.KbDGDM_FaultTypeA', 66,
        'KsDGDM_EST_Cylinder_3.KbDGDM_FaultTypeB', 67,
        'KsDGDM_EST_Cylinder_3.KbDGDM_FaultTypeC', 68,
        'KsDGDM_EST_Cylinder_3.KbDGDM_FaultTypeE', 69,
        'KsDGDM_EST_Cylinder_3.KeDGDM_DenomId', 70,
        'KsDGDM_EST_Cylinder_3.KeDGDM_DTC_DepListId', 71,
        'KsDGDM_EST_Cylinder_3.KeDGDM_LightEnable', 72,
        'KsDGDM_EST_Cylinder_3.KwDGDM_DummyBits', 73,
        'KsDGDM_EST_Cylinder_3.KwDGDM_P_Code', 74,
        'KsDGDM_EST_Cylinder_4.KbDGDM_FaultTypeA', 75,
        'KsDGDM_EST_Cylinder_4.KbDGDM_FaultTypeB', 76,
        'KsDGDM_EST_Cylinder_4.KbDGDM_FaultTypeC', 77,
        'KsDGDM_EST_Cylinder_4.KbDGDM_FaultTypeE', 78,
        'KsDGDM_EST_Cylinder_4.KeDGDM_DenomId', 79,
        'KsDGDM_EST_Cylinder_4.KeDGDM_DTC_DepListId', 80,
        'KsDGDM_EST_Cylinder_4.KeDGDM_LightEnable', 81,
        'KsDGDM_EST_Cylinder_4.KwDGDM_DummyBits', 82,
        'KsDGDM_EST_Cylinder_4.KwDGDM_P_Code', 83,
        'KsDGDM_EST_Cylinder_5.KbDGDM_FaultTypeA', 84,
        'KsDGDM_EST_Cylinder_5.KbDGDM_FaultTypeB', 85,
        'KsDGDM_EST_Cylinder_5.KbDGDM_FaultTypeC', 86,
        'KsDGDM_EST_Cylinder_5.KbDGDM_FaultTypeE', 87,
        'KsDGDM_EST_Cylinder_5.KeDGDM_DenomId', 88,
        'KsDGDM_EST_Cylinder_5.KeDGDM_DTC_DepListId', 89,
        'KsDGDM_EST_Cylinder_5.KeDGDM_LightEnable', 90,
        'KsDGDM_EST_Cylinder_5.KwDGDM_DummyBits', 91,
        'KsDGDM_EST_Cylinder_5.KwDGDM_P_Code', 92,
        'KsDGDM_EST_Cylinder_6.KbDGDM_FaultTypeA', 93,
        'KsDGDM_EST_Cylinder_6.KbDGDM_FaultTypeB', 94,
        'KsDGDM_EST_Cylinder_6.KbDGDM_FaultTypeC', 95,
        'KsDGDM_EST_Cylinder_6.KbDGDM_FaultTypeE', 96,
        'KsDGDM_EST_Cylinder_6.KeDGDM_DenomId', 97,
        'KsDGDM_EST_Cylinder_6.KeDGDM_DTC_DepListId', 98,
        'KsDGDM_EST_Cylinder_6.KeDGDM_LightEnable', 99,
        'KsDGDM_EST_Cylinder_6.KwDGDM_DummyBits', 100,
        'KsDGDM_EST_Cylinder_6.KwDGDM_P_Code', 101,
        'KsDGDM_Inj_Cylinder_1.KbDGDM_FaultTypeA', 120,
        'KsDGDM_Inj_Cylinder_1.KbDGDM_FaultTypeB', 121,
        'KsDGDM_Inj_Cylinder_1.KbDGDM_FaultTypeC', 122,
        'KsDGDM_Inj_Cylinder_1.KbDGDM_FaultTypeE', 123,
        'KsDGDM_Inj_Cylinder_1.KeDGDM_DenomId', 124,
        'KsDGDM_Inj_Cylinder_1.KeDGDM_DTC_DepListId', 125,
        'KsDGDM_Inj_Cylinder_1.KeDGDM_LightEnable', 126,
        'KsDGDM_Inj_Cylinder_1.KwDGDM_DummyBits', 127,
        'KsDGDM_Inj_Cylinder_1.KwDGDM_P_Code', 128,
        'KsDGDM_Inj_Cylinder_2.KbDGDM_FaultTypeA', 129,
        'KsDGDM_Inj_Cylinder_2.KbDGDM_FaultTypeB', 130,
        'KsDGDM_Inj_Cylinder_2.KbDGDM_FaultTypeC', 131,
        'KsDGDM_Inj_Cylinder_2.KbDGDM_FaultTypeE', 132,
        'KsDGDM_Inj_Cylinder_2.KeDGDM_DenomId', 133,
        'KsDGDM_Inj_Cylinder_2.KeDGDM_DTC_DepListId', 134,
        'KsDGDM_Inj_Cylinder_2.KeDGDM_LightEnable', 135,
        'KsDGDM_Inj_Cylinder_2.KwDGDM_DummyBits', 136,
        'KsDGDM_Inj_Cylinder_2.KwDGDM_P_Code', 137,
        'KsDGDM_Inj_Cylinder_3.KbDGDM_FaultTypeA', 138,
        'KsDGDM_Inj_Cylinder_3.KbDGDM_FaultTypeB', 139,
        'KsDGDM_Inj_Cylinder_3.KbDGDM_FaultTypeC', 140,
        'KsDGDM_Inj_Cylinder_3.KbDGDM_FaultTypeE', 141,
        'KsDGDM_Inj_Cylinder_3.KeDGDM_DenomId', 142,
        'KsDGDM_Inj_Cylinder_3.KeDGDM_DTC_DepListId', 143,
        'KsDGDM_Inj_Cylinder_3.KeDGDM_LightEnable', 144,
        'KsDGDM_Inj_Cylinder_3.KwDGDM_DummyBits', 145,
        'KsDGDM_Inj_Cylinder_3.KwDGDM_P_Code', 146,
        'KsDGDM_Inj_Cylinder_4.KbDGDM_FaultTypeA', 147,
        'KsDGDM_Inj_Cylinder_4.KbDGDM_FaultTypeB', 148,
        'KsDGDM_Inj_Cylinder_4.KbDGDM_FaultTypeC', 149,
        'KsDGDM_Inj_Cylinder_4.KbDGDM_FaultTypeE', 150,
        'KsDGDM_Inj_Cylinder_4.KeDGDM_DenomId', 151,
        'KsDGDM_Inj_Cylinder_4.KeDGDM_DTC_DepListId', 152,
        'KsDGDM_Inj_Cylinder_4.KeDGDM_LightEnable', 153,
        'KsDGDM_Inj_Cylinder_4.KwDGDM_DummyBits', 154,
        'KsDGDM_Inj_Cylinder_4.KwDGDM_P_Code', 155,
        'KsDGDM_Inj_Cylinder_5.KbDGDM_FaultTypeA', 156,
        'KsDGDM_Inj_Cylinder_5.KbDGDM_FaultTypeB', 157,
        'KsDGDM_Inj_Cylinder_5.KbDGDM_FaultTypeC', 158,
        'KsDGDM_Inj_Cylinder_5.KbDGDM_FaultTypeE', 159,
        'KsDGDM_Inj_Cylinder_5.KeDGDM_DenomId', 160,
        'KsDGDM_Inj_Cylinder_5.KeDGDM_DTC_DepListId', 161,
        'KsDGDM_Inj_Cylinder_5.KeDGDM_LightEnable', 162,
        'KsDGDM_Inj_Cylinder_5.KwDGDM_DummyBits', 163,
        'KsDGDM_Inj_Cylinder_5.KwDGDM_P_Code', 164,
        'KsDGDM_Inj_Cylinder_6.KbDGDM_FaultTypeA', 165,
        'KsDGDM_Inj_Cylinder_6.KbDGDM_FaultTypeB', 166,
        'KsDGDM_Inj_Cylinder_6.KbDGDM_FaultTypeC', 167,
        'KsDGDM_Inj_Cylinder_6.KbDGDM_FaultTypeE', 168,
        'KsDGDM_Inj_Cylinder_6.KeDGDM_DenomId', 169,
        'KsDGDM_Inj_Cylinder_6.KeDGDM_DTC_DepListId', 170,
        'KsDGDM_Inj_Cylinder_6.KeDGDM_LightEnable', 171,
        'KsDGDM_Inj_Cylinder_6.KwDGDM_DummyBits', 172,
        'KsDGDM_Inj_Cylinder_6.KwDGDM_P_Code', 173,
        'KsDGDM_MIL_Open.KbDGDM_FaultTypeA', 174,
        'KsDGDM_MIL_Open.KbDGDM_FaultTypeB', 175,
        'KsDGDM_MIL_Open.KbDGDM_FaultTypeC', 176,
        'KsDGDM_MIL_Open.KbDGDM_FaultTypeE', 177,
        'KsDGDM_MIL_Open.KeDGDM_DenomId', 178,
        'KsDGDM_MIL_Open.KeDGDM_DTC_DepListId', 179,
        'KsDGDM_MIL_Open.KeDGDM_LightEnable', 180,
        'KsDGDM_MIL_Open.KwDGDM_DummyBits', 181,
        'KsDGDM_MIL_Open.KwDGDM_P_Code', 182,
        'KsDGDM_MIL_Short.KbDGDM_FaultTypeA', 183,
        'KsDGDM_MIL_Short.KbDGDM_FaultTypeB', 184,
        'KsDGDM_MIL_Short.KbDGDM_FaultTypeC', 185,
        'KsDGDM_MIL_Short.KbDGDM_FaultTypeE', 186,
        'KsDGDM_MIL_Short.KeDGDM_DenomId', 187,
        'KsDGDM_MIL_Short.KeDGDM_DTC_DepListId', 188,
        'KsDGDM_MIL_Short.KeDGDM_LightEnable', 189,
        'KsDGDM_MIL_Short.KwDGDM_DummyBits', 190,
        'KsDGDM_MIL_Short.KwDGDM_P_Code', 191,
        'KsDGDM_VCPD_B1_Intk_CntrlVlv.KbDGDM_FaultTypeA', 246,
        'KsDGDM_VCPD_B1_Intk_CntrlVlv.KbDGDM_FaultTypeB', 247,
        'KsDGDM_VCPD_B1_Intk_CntrlVlv.KbDGDM_FaultTypeC', 248,
        'KsDGDM_VCPD_B1_Intk_CntrlVlv.KbDGDM_FaultTypeE', 249,
        'KsDGDM_VCPD_B1_Intk_CntrlVlv.KeDGDM_DenomId', 250,
        'KsDGDM_VCPD_B1_Intk_CntrlVlv.KeDGDM_DTC_DepListId', 251,
        'KsDGDM_VCPD_B1_Intk_CntrlVlv.KeDGDM_LightEnable', 252,
        'KsDGDM_VCPD_B1_Intk_CntrlVlv.KwDGDM_DummyBits', 253,
        'KsDGDM_VCPD_B1_Intk_CntrlVlv.KwDGDM_P_Code', 254,
        'KsDGDM_VCPD_B2_Intk_CntrlVlv.KbDGDM_FaultTypeA', 255,
        'KsDGDM_VCPD_B2_Intk_CntrlVlv.KbDGDM_FaultTypeB', 256,
        'KsDGDM_VCPD_B2_Intk_CntrlVlv.KbDGDM_FaultTypeC', 257,
        'KsDGDM_VCPD_B2_Intk_CntrlVlv.KbDGDM_FaultTypeE', 258,
        'KsDGDM_VCPD_B2_Intk_CntrlVlv.KeDGDM_DenomId', 259,
        'KsDGDM_VCPD_B2_Intk_CntrlVlv.KeDGDM_DTC_DepListId', 260,
        'KsDGDM_VCPD_B2_Intk_CntrlVlv.KeDGDM_LightEnable', 261,
        'KsDGDM_VCPD_B2_Intk_CntrlVlv.KwDGDM_DummyBits', 262,
        'KsDGDM_VCPD_B2_Intk_CntrlVlv.KwDGDM_P_Code', 263,
        'KfACOD_U_SystemThrshLo', 264
       );
  local( %delfunc_idx_list ) = ();
#  local( @delidx_list ) = sort keys( %delsym_idx_list );

#  print STDERR "BEGIN\n";

  $start_processing = $false;
  $index = -1;
  while ( ++$index <= $#a2l_file_buff )
  {
    $tmp_line = $a2l_file_buff[$index];
    if ( $start_processing == $false )
    {
      if ( ($tmp_line =~ /\/begin\s+MEASUREMENT\s+([a-zA-Z0-9_.]+)/) ||
           ($tmp_line =~ /\/begin\s+CHARACTERISTIC\s+([a-zA-Z0-9_.]+)/) )
      {
        $tmp_str = $1;
        if ( defined($delsym_idx_list{$tmp_str}) )
        {
          $start_processing = $true;
#          $delidx_list[$delsym_idx_list{$tmp_str}] .= " Removed";
          splice( @a2l_file_buff, $index, 1 );
          --$index;
#  print STDERR "del0 $tmp_str\n";
        }
      }
    }
    else
    {
      if ( ($tmp_line =~ /\/end\s+MEASUREMENT/) ||
           ($tmp_line =~ /\/end\s+CHARACTERISTIC/) )
      {
        $start_processing = $false;
      }
      splice( @a2l_file_buff, $index, 1 );
      --$index;
    }
  }

  $start_processing = $false;
  $index = -1;
  while ( ++$index <= $#a2l_file_buff )
  {
    $tmp_line = $a2l_file_buff[$index];
    if ( $start_processing == $false )
    {
      if ( $tmp_line =~ /\/begin\s+FUNCTION\s+\w+/ )
      {
        $start_processing = $true;
      }
    }
    else
    {
      if ( $tmp_line =~ /\/end\s+FUNCTION/ )
      {
        $start_processing = $false;
      }
      elsif ( $tmp_line =~ /([a-zA-Z0-9_.]+)\s*$/ )
      {
        $tmp_str1 = $`;
        $tmp_str  = $1;
        if ( defined($delsym_idx_list{$tmp_str}) )
        {
          if ( $tmp_str1 =~ /\sREF_CHARACTERISTIC\s/ )
          {
            $a2l_file_buff[$index] = "$tmp_str1\n";
          }
          else
          {
            splice( @a2l_file_buff, $index, 1 );
            --$index;
          }
#  print STDERR "del1 $tmp_str\n";
        }
      }
    }
  }

#  $index = -1;
#  while ( ++$index <= $#delidx_list )
#  {
#    if ( ! ($delidx_list[$index] =~ / Removed/) )
#    {
#      print STDERR "$delidx_list[$index]\n";
#    }
#  }

#  print STDERR "END:\n";

  $start_processing = $false;
  $index1 = -1;
  $index  = -1;
  while ( ++$index <= $#a2l_file_buff )
  {
    $tmp_line = $a2l_file_buff[$index];
    if ( $start_processing == $false )
    {
      if ( $tmp_line =~ /\/begin\s+FUNCTION\s+(\w+)/ )
      {
        $tmp_str  = $1;
        $start_processing = $true;
      }
    }
    else
    {
      if ( $tmp_line =~ /\/end\s+FUNCTION/ )
      {
        $start_processing = $false;
      }
      elsif ( $tmp_line =~ /\/begin\s+REF_CHARACTERISTIC\s*$/ )
      {
        $delfunc_idx_list{$tmp_str} = ++$index1;
#        print STDERR "list $tmp_str\n";
      }
    }
  }

  $start_processing = $false;
  $index  = -1;
  while ( ++$index <= $#a2l_file_buff )
  {
    $tmp_line = $a2l_file_buff[$index];
    if ( $start_processing == $false )
    {
      if ( $tmp_line =~ /\/begin\s+FUNCTION\s+(\w+)/ )
      {
        $tmp_str  = $1;
        if ( defined($delfunc_idx_list{$tmp_str}) )
        {
          $start_processing = $true;
          splice( @a2l_file_buff, $index, 1 );
          --$index;
#          print STDERR "del0 $tmp_str\n";
        }
      }
      elsif ( $tmp_line =~ /^\s*(\w+)\s*$/ )
      {
        $tmp_str  = $1;
        if ( defined($delfunc_idx_list{$tmp_str}) )
        {
          splice( @a2l_file_buff, $index, 1 );
          --$index;
#          print STDERR "del1 $tmp_str\n";
        }
      }
    }
    else
    {
      if ( $tmp_line =~ /\/end\s+FUNCTION/ )
      {
        $start_processing = $false;
      }
      splice( @a2l_file_buff, $index, 1 );
      --$index;
    }
  }

  return( $errOK );
}

sub AddSystemConfigCalsA2lBuff
{
  local( *a2l_file_buff )  = @_;
  local( $index ) = -1;
  local( @sys_conf_cal_section ) = (
  "    /begin FUNCTION a_System_Configuration\n",
  "        \"Cals for configuring the system to an application.\"\n",
  "      /begin REF_CHARACTERISTIC\n",
  "          KeFLOS_HeaterDriverConfig\n",
  "          KeHVAC_AC_PressSenseType\n",
  "          KeHWIO_Cam1OccurredTrue\n",
  "          KeHWIO_Cam2OccurredTrue\n",
  "          KeSYST_CruiseType\n",
  "          KeVIOS_ExhaustConfig\n",
  "          KeVIOS_O2_PumpingCurrentEnable\n",
  "          KeVIOS_SystemVulnerabilityState\n",
  "          KeVIOS_TCS_CAN_Version\n",
  "          KeVIOS_VehicleSpeedSource\n",
  "          KfEPSE_V_CylinderVolume\n",
  "          KwFILE_ROM_CalibrationChecksum\n",
  "          KbFILE_NVM_Reset\n",
  "          KbSYST_NoStartCalibration\n",
  "          KbELCL_Use2FanLogic\n",
  "          KbEPSE_FuelTankVacSensorExists\n",
  "          KbETCD_UseTwoBrakeSwitches\n",
  "          KbFUEL_LPI_SystemPresent\n",
  "          KbINST_CCP_TransDatalog\n",
  "          KeSYST_AlterType\n",
  "          KeVIOS_PS_PressSenseType\n",
  "          KeTRVC_TransCntrlType\n",
  "      /end REF_CHARACTERISTIC\n",
  "    /end FUNCTION\n\n",
  );

  $index = $#a2l_file_buff;
  while ( $index >= 0 )
  {
    if ( $a2l_file_buff[$index] =~ /\/end MODULE/ )
    {
      last;
    }
    --$index;
  }

#  print STDERR "$#a2l_file_buff, $index\n";
  splice( @a2l_file_buff, $index, 0, @sys_conf_cal_section );

  return( $errOK );
}

sub FixMeasSizeA2lBuff
{
  local( *a2l_file_buff ) = @_;
  local( $index ) = -1;
  local( $start_processing ) = $false;
  local( $tmp_line ) = "";
  local( $new_type_name ) = "";
  local( $line_cnt ) = -1;
  local( %measurement_asc_list ) = (
#   Measurement Name,   New Type Name

    'EAIRAFCM', 'UBYTE',
    'EAIRFLTF', 'UBYTE',
    'EAATTSR',  'UBYTE',
    'EAP1RFCM', 'UBYTE',
    'EAP1RTFL', 'UBYTE',
    'EAP2RFCM', 'UBYTE',
    'EAP2RTFL', 'UBYTE',
    'EAP3RFCM', 'UBYTE',
    'EAP3RTFL', 'UBYTE',
    'EAP1LFCM', 'UBYTE',
    'EAP1LRTF', 'UBYTE',
    'EAP2LFCM', 'UBYTE',
    'EAP2LRTF', 'UBYTE',
    'EAP3LFCM', 'UBYTE',
    'EAP3LRTF', 'UBYTE',
    'EAP1HFCM', 'UBYTE',
    'EAP1HRTF', 'UBYTE',
    'EAP2HFCM', 'UBYTE',
    'EAP2HRTF', 'UBYTE',
    'EAP3HFCM', 'UBYTE',
    'EAP3HRTF', 'UBYTE',
    'EAP12FCM', 'UBYTE',
    'EAP12TFL', 'UBYTE',
    'EAP13FCM', 'UBYTE',
    'EAP13TFL', 'UBYTE',
    'EAP23FCM', 'UBYTE',
    'EAP23TFL', 'UBYTE',
    'EAP12FCT', 'UBYTE',
    'EAP12TSR', 'UBYTE',
    'ETALFCM',  'UBYTE',
    'ETALTF',   'UBYTE',
    'ETAHFCM',  'UBYTE',
    'ETAHTF',   'UBYTE',
    'ETP1RFCM', 'UBYTE',
    'ETP1RTFL', 'UBYTE',
    'ETP2RFCM', 'UBYTE',
    'ETP2RTFL', 'UBYTE',
    'ETPCRFCM', 'UBYTE',
    'ETPCRTFL', 'UBYTE',
    'ETP1LFCM', 'UBYTE',
    'ETP1LTFL', 'UBYTE',
    'ETP2LFCM', 'UBYTE',
    'ETP2LTFL', 'UBYTE',
    'ETP1HFCM', 'UBYTE',
    'ETP1HTFL', 'UBYTE',
    'ETP2HFCM', 'UBYTE',
    'ETP2HTFL', 'UBYTE',
    'RAP1LFCM', 'UBYTE',
    'RAP1LRTF', 'UBYTE',
    'RAP2LFCM', 'UBYTE',
    'RAP2LRTF', 'UBYTE',
    'RAP1HFCM', 'UBYTE',
    'RAP1HRTF', 'UBYTE',
    'RAP2HFCM', 'UBYTE',
    'RAP2HRTF', 'UBYTE',
    'VRFAFCM',  'UBYTE',
    'VRFATF',   'UBYTE',
    'VRFBFCM',  'UBYTE',
    'VRFBTF',   'UBYTE',
    'VRFATSR',  'UBYTE',
    'VRFBTSR',  'UBYTE',
    'RAP12FCM', 'UBYTE',
    'RAP12TFL', 'UBYTE',
    'RAP13FCM', 'UBYTE',
    'RAP13TFL', 'UBYTE',
    'RAP1RFCM', 'UBYTE',
    'RAP1RTFL', 'UBYTE',
    'RAP23FCM', 'UBYTE',
    'RAP23TFL', 'UBYTE',
    'RAP2RFCM', 'UBYTE',
    'RAP2RTFL', 'UBYTE',
    'RAP3RFCM', 'UBYTE',
    'RAP3RTFL', 'UBYTE',
    'TRQDHFCM', 'UBYTE',
    'TRQDHTF',  'UBYTE',
    'TRQDLFCM', 'UBYTE',
    'TRQDLTF',  'UBYTE',
    'VRFARTFL', 'UBYTE',
    'VRFBRTFL', 'UBYTE',
    'VRFCRTFL', 'UBYTE',
    'DMRAM1',   'UWORD',
    'DMRAM2',   'UWORD',
    'DMRAM3',   'UWORD',
    'DMRAM4',   'UWORD',
    'DMRAM5',   'UWORD',
    'SCUCOR',   'UWORD',
    'TCDRMRES', 'UWORD',
    'FFDTCID',  'UBYTE',
    'FR1DTCID', 'UWORD',
    'FR2DTCID', 'UWORD',
    'FR3DTCID', 'UWORD',
    'FR4DTCID', 'UWORD',
    'FR1PCODE', 'UWORD',
    'FR2PCODE', 'UWORD',
    'FR3PCODE', 'UWORD',
    'FR4PCODE', 'UWORD',
    'FRAMSADR', 'ULONG',
    'FRAMTADR', 'ULONG',
    'FROMTADR', 'ULONG',
    'CVNCRC',   'ULONG'
  );
  local( $num_of_completed_subs ) = ( -1 );
  local( @measurement_list ) = sort keys (%measurement_asc_list);

  $num_of_completed_subs = 0;
  $start_processing = $false;
  $index = -1;
  while ( ++$index <= $#a2l_file_buff )
  {
    $tmp_line = $a2l_file_buff[$index];
    if ( $start_processing == $false )
    {
      if ( $tmp_line =~ /\/begin\s+MEASUREMENT\s+(\w+)/ )
      {
        if ( defined($measurement_asc_list{$1}) )
        {
          $start_processing = $true;
          $line_cnt = 0;
          $new_type_name    = $measurement_asc_list{$1};
        }
      }
    }
    else
    {
      if ( ++$line_cnt == 2 )
      {
        if ( $tmp_line =~ /(\s)\w+(\s)/ )
        {
          $a2l_file_buff[$index] = $` . $1 . $new_type_name . $2 . $';
#          print STDERR "$a2l_file_buff[$index-2]\n";
#          print STDERR "< $tmp_line";
#          print STDERR "> $a2l_file_buff[$index]\n";
          if ( ++$num_of_completed_subs > $#measurement_list )
          {
            last;
          }
        }
        else
        {
          print STDERR "(!) FixMeasSizeA2lBuff() : $a2l_file_buff[$index-2]\n";
          return( $errNOK );
        }
        $start_processing = $false;
      }
    }
  }

  return( $errOK );
}

sub RemoveMeasurementsA2lBuff
{
  local( *a2l_file_buff )  = @_;
  local( $index ) = ( -1 );
  local( $start_processing ) = $false;
  local( $tmp_line ) = "";
  local( $tmp_str ) = "";
  local( %remove_list ) = (
    'EAPS3DIS', 0,
    'EAPS3NRM', 1,
    'EAPS3RAW', 2,
    'EAPS3WT',  3,
    'EAPS3MIN', 4,
    'EAPS3FL',  5,
    'EAP3RTFL', 6,
    'EAP3RFCM', 7,
    'EAP23TFL', 8,
    'EAP23FCM', 9,
    'EAP3HRTF', 10,
    'EAP3HFCM', 11,
    'EAP3LRTF', 12,
    'EAP3LFCM', 13,
    'EAP13TFL', 14,
    'EAP13FCM', 15,
    'EAMN23ER', 16,
    'EAMN13ER', 17,
    'EAP3LFCT', 18,
    'EAP3HFCT', 19,
    'VRFCRTFL', 20,
    'EVRFCRAW', 21,
    'RAP13FCM', 22,
    'RAP13TFL', 23,
    'RAP23FCM', 24,
    'RAP23TFL', 25,
    'RAP3RFCM', 26,
    'RAP3RTFL', 27
  );
  local( $num_of_completed_subs ) = ( -1 );
  local( @measurement_list ) = sort keys (%remove_list);

  $num_of_completed_subs = 0;
  $start_processing = $false;
  $index = -1;
  while ( ++$index <= $#a2l_file_buff )
  {
    $tmp_line = $a2l_file_buff[$index];
    if ( $start_processing == $false )
    {
      if ( $tmp_line =~ /\/begin\s+MEASUREMENT\s+(\w+)/ )
      {
        $tmp_str = $1;
        if ( defined($remove_list{$tmp_str}) )
        {
          $start_processing = $true;
#          print STDERR "[1] Removing $tmp_str ...\n";
          splice( @a2l_file_buff, $index, 1 );
          --$index;
        }
      }
    }
    else
    {
      splice( @a2l_file_buff, $index, 1 );
      --$index;
      if ( $tmp_line =~ /\/end\s+MEASUREMENT/ )
      {
        $start_processing = $false;
        if ( ++$num_of_completed_subs > $#measurement_list )
        {
          last;
        }
      }
    }
  }

  $index = -1;
  while ( ++$index <= $#a2l_file_buff )
  {
    if ( $a2l_file_buff[$index] =~ /\/begin\s+LOC_MEASUREMENT/ )
    {
      last;
    }
  }
  $num_of_completed_subs = 0;
  while ( ++$index <= $#a2l_file_buff )
  {
    $tmp_line = $a2l_file_buff[$index];
    if ( $tmp_line =~ /(\w+)(\s*$)/ )
    {
      $tmp_str = $` . $2;
      if ( defined($remove_list{$1}) )
      {
#        print STDERR "[2] Removing $1 ...\n";
        if ( $tmp_str =~ /^\s*$/ )
        {
          splice( @a2l_file_buff, $index, 1 );
          --$index;
        }
        else
        {
          $a2l_file_buff[$index] = $tmp_str;
        }
        if ( ++$num_of_completed_subs > $#measurement_list )
        {
          last;
        }
      }
    }
  }

  return( $errOK );
}

sub GenDGDM_NumrtrsA2lBuff
{
  local( *a2l_file_buff )  = @_;
  local( $index, $index1 ) = ( -1, -1 );
  local( $start_processing ) = $false;
  local( $tmp_line ) = "";
  local( $num_of_numrtrs ) = ( 0 );
  local( @numrtr_list ) = ();
  local( @tmp_numrtr_list ) = ();

  $index = -1;
  $num_of_numrtrs = 0;
  while ( ++$index <= $#a2l_file_buff )
  {
    $tmp_line = $a2l_file_buff[$index];
    if ( $tmp_line =~ /DISPLAY_IDENTIFIER\s+KsDGDM\w+\.KwDGDM_P_Code/ )
    {
      $num_of_numrtrs++;
    }
  }

# 0
# 1    /begin MEASUREMENT			NaDGDM_RM_NumrtrArry
# 2					"Ratio Monitor Numerator for element 0 on the list of all diagnostics."
# 3					UWORD
# 4					NaDGDM_RM_NumrtrArry_plus_0x02_DS_Scaling
# 5					0 0.000000
# 6					0.000000 65535.000000
# 7	   ECU_ADDRESS			0xD00083B6
# 8	   DISPLAY_IDENTIFIER		RMAN000
# 9   /end MEASUREMENT

  $start_processing = $false;
  $index = -1;
  while ( ++$index <= $#a2l_file_buff )
  {
    $tmp_line = $a2l_file_buff[$index];
    if ( $start_processing == $false )
    {
      if ( $tmp_line =~ /(^\s*\/begin\s+MEASUREMENT\s+NaDGDM_RM_NumrtrArry)/ )
      {
        $start_processing = $true;
        $tmp_line = $1;
        push( @tmp_numrtr_list, $a2l_file_buff[$index-1] );
      }
    }
    if ( $start_processing == $true )
    {
      push( @tmp_numrtr_list, $tmp_line );
      if ( $tmp_line =~ /\/end\s+MEASUREMENT/ )
      {
        $start_processing = $false;
        $index1 = 1;
        while ( $index1 < $num_of_numrtrs )
        {
          splice( @numrtr_list, 0, $#numrtr_list+1, @tmp_numrtr_list );
          $numrtr_list[1] .= "_plus_" . 2*$index1 . "\n";
          ($numrtr_list[2] = $numrtr_list[2]) =~ s/element 0/element $index1/;
          if ( $numrtr_list[7] =~ /(ECU_ADDRESS\s+)(\w+)/ )
          {
            $numrtr_list[7] = $` . $1;
            $numrtr_list[7] .= sprintf( "0x%08X", hex($2)+2*$index1 );
            $numrtr_list[7] .= $';
          }
          if ( $numrtr_list[8] =~ /(DISPLAY_IDENTIFIER\s+RMAN)(\w+)/ )
          {
            $numrtr_list[8] = $` . $1;
            $numrtr_list[8] .= sprintf( "%03d", $index1 );
            $numrtr_list[8] .= $';
          }
          splice( @a2l_file_buff, $index+1+($index1-1)*($#numrtr_list+1), 0, @numrtr_list );
          $index1++;
        }
        last;
      }
    }
  }

  $start_processing = $false;
  $index = $#a2l_file_buff;
  while ( $index >= 0 )
  {
    $tmp_line = $a2l_file_buff[$index];
    if ( $start_processing == $false )
    {
      if ( $tmp_line =~ /(^\s*NaDGDM_RM_NumrtrArry)/ )
      {
        $start_processing = $true;
        $tmp_line = $1;
      }
    }
    if ( $start_processing == $true )
    {
      $start_processing = $false;
      $index1 = 1;
      while ( $index1 < $num_of_numrtrs )
      {
        splice( @tmp_numrtr_list, 0 );
        push( @tmp_numrtr_list, $tmp_line . "_plus_" . 2*$index1 . "\n" );
        splice( @a2l_file_buff, $index+$index1, 0, @tmp_numrtr_list );
        $index1++;
      }
      last;
    }
    $index--;
  }

  return( $errOK );
}

sub SeprtDGDM_CalsA2lBuff
{
  local( *a2l_file_buff )  = @_;
  local( $index, $index1 ) = ( -1, -1 );
  local( $start_processing ) = $false;
  local( $tmp_line ) = "";
  local( $tmp_str ) = "";
  local( %trans_cal_asc_list ) = ();
  local( $num_of_symbols_found ) = ( 0 );

  $index  = -1;
  $index1 = -1;
  while ( ++$index <= $#a2l_file_buff )
  {
    if ( $a2l_file_buff[$index] =~ /\/begin\s+CHARACTERISTIC\s+(K.DGDM\S+)/ )
    {
      $tmp_str = $1;
      if ( $a2l_file_buff[$index+1] =~ /^(\s+\")TRND\s*,\s*/ )
      {
        $a2l_file_buff[$index+1] = $1 . $';
        $trans_cal_asc_list{$tmp_str} = ++$index1;
      }
    }
  }

  $start_processing = $false;
  $index = -1;
  while ( ++$index <= $#a2l_file_buff )
  {
    $tmp_line = $a2l_file_buff[$index];
    if ( $start_processing == $false )
    {
      if ( $tmp_line =~ /(\/begin\s+FUNCTION\s+)dgdmcald/ )
      {
        $tmp_line = $` . $1 . "dgdmctrn" . $';
        push( @dgdm_trns_cals_buff, "\n" );
        push( @dgdm_trns_cals_buff, $tmp_line );
        $start_processing = $true;
      }
    }
    else
    {
      if ( $tmp_line =~ /(K.DGDM\S+)/ )
      {
        $tmp_str = $1;
        if ( $tmp_line =~ /(\/begin\s+REF_CHARACTERISTIC)\s+/ )
        {
          if ( defined($trans_cal_asc_list{$tmp_str}) )
          {
            $a2l_file_buff[$index] = $` . $1 . "\n";
            push( @dgdm_trns_cals_buff, $tmp_line );
          }
          else
          {
            push( @dgdm_trns_cals_buff, $` . $1 . "\n" );
          }
        }
        elsif ( defined($trans_cal_asc_list{$tmp_str}) )
        {
          ++$num_of_symbols_found;
          splice( @a2l_file_buff, $index, 1 );
          --$index;
          push( @dgdm_trns_cals_buff, $tmp_line );
        }
      }
      else
      {
        push( @dgdm_trns_cals_buff, $tmp_line );
      }

      if ( $tmp_line =~ /\/end\s+FUNCTION/ )
      {
        if ( $num_of_symbols_found > 0 )
        {
          splice( @a2l_file_buff, $index+1, 0, @dgdm_trns_cals_buff );
        }
        last;
      }
    }
  }

  $start_processing = $false;
  while ( ++$index <= $#a2l_file_buff )
  {
    $tmp_line = $a2l_file_buff[$index];
    if ( $start_processing == $false )
    {
      if ( $tmp_line =~ /(\/begin\s+FUNCTION\s+)Cals_Transmission/ )
      {
        $start_processing = $true;
      }
    }
    else
    {
      if ( $tmp_line =~ /\/end\s+SUB_FUNCTION/ )
      {
        ($tmp_line = $a2l_file_buff[$index-1]) =~ s/\S+/dgdmctrn/;
        $a2l_file_buff[$index-1] .= $tmp_line;
        last;
      }
    }
  }

  return( $errOK );
}

###############################################################################
#
# Main
#
###############################################################################

if ( $#ARGV == 1 )
{
  $A2lFileName      = $ARGV[0];
  $A2lPatchFileName = $ARGV[1];
}
elsif ( $#ARGV == 2 )
{
  $A2lFileName      = $ARGV[0];
  $A2lPatchFileName = $ARGV[1];
  $CorrModeMask     = hex( $ARGV[2] );
}

if ( $CorrModeMask & 0x0001 )
{
  if ( ($ErrCode=&FillFileBuff(*A2lPatchFileName, *A2lPatchFileBuff)) != $errOK )
  {
    exit $ErrCode;
  }
}

if ( ($ErrCode=&FillFileBuff(*A2lFileName, *A2lFileBuff)) != $errOK )
{
  exit $ErrCode;
}

if ( $CorrModeMask & 0x0001 )
{
  if ( ($ErrCode=&PatchA2lBuff(*A2lFileBuff, *A2lPatchFileBuff)) != $errOK )
  {
    exit $ErrCode;
  }
#  print STDERR "PatchA2lBuff() is done\n";
}

if ( $CorrModeMask & 0x0100 )
{
  if ( ($ErrCode=&GenDGDM_NumrtrsA2lBuff(*A2lFileBuff)) != $errOK )
  {
    exit $ErrCode;
  }
#  print STDERR "GenDGDM_NumrtrsA2lBuff() is done\n";
}

if ( $CorrModeMask & 0x0004 )
{
  if ( ($ErrCode=&FixDgdmA2lBuff(*A2lFileBuff)) != $errOK )
  {
    exit $ErrCode;
  }
#  print STDERR "FixDgdmA2lBuff() is done\n";
}

if ( $CorrModeMask & 0x0008 )
{
  if ( ($ErrCode=&FixAnnsA2lBuff(*A2lFileBuff)) != $errOK )
  {
    exit $ErrCode;
  }
#  print STDERR "FixAnnsA2lBuff() is done\n";
}

if ( $CorrModeMask & 0x0020 )
{
  if ( ($ErrCode=&RemoveEGRS_A2lBuff(*A2lFileBuff)) != $errOK )
  {
    exit $ErrCode;
  }
#  print STDERR "RemoveEGRS_A2lBuff() is done\n";
}

if ( $CorrModeMask & 0x0010 )
{
  if ( ($ErrCode=&SwapNamesA2lBuff(*A2lFileBuff)) != $errOK )
  {
    exit $ErrCode;
  }
#  print STDERR "SwapNamesA2lBuff() is done\n";
}

if ( $CorrModeMask & 0x0080 )
{
  if ( ($ErrCode=&RemoveDGDM_CalsA2lBuff(*A2lFileBuff)) != $errOK )
  {
    exit $ErrCode;
  }
#  print STDERR "RemoveDGDM_CalsA2lBuff() is done\n";
}

if ( $CorrModeMask & 0x0200 )
{
  if ( ($ErrCode=&AddSystemConfigCalsA2lBuff(*A2lFileBuff)) != $errOK )
  {
    exit $ErrCode;
  }
#  print STDERR "AddSystemConfigCalsA2lBuff() is done\n";
}

if ( $CorrModeMask & 0x0800 )
{
  if ( ($ErrCode=&FixMeasSizeA2lBuff(*A2lFileBuff)) != $errOK )
  {
    exit $ErrCode;
  }
#  print STDERR "FixMeasSizeA2lBuff() is done\n";
}

if ( $CorrModeMask & 0x1000 )
{
  if ( ($ErrCode=&RemoveMeasurementsA2lBuff(*A2lFileBuff)) != $errOK )
  {
    exit $ErrCode;
  }
#  print STDERR "RemoveMeasurementsA2lBuff() is done\n";
}

if ( $CorrModeMask & 0x2000 )
{
  if ( ($ErrCode=&SeprtDGDM_CalsA2lBuff(*A2lFileBuff)) != $errOK )
  {
    exit $ErrCode;
  }
#  print STDERR "SeprtDGDM_CalsA2lBuff() is done\n";
}

&PrintBuff( *A2lFileBuff );

exit $ErrCode;

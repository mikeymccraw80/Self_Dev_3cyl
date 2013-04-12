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
#   | | | |  | | | |  | | | |  | | +--- Fix cofficient accuracy (FixCoefA2lBuff)
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
#   | | | |  | | | |  | +-------------- Correct known tunable axis instances (CorrectTnblAxisA2lBuff)
#   | | | |  | | | |  |                   0: Off
#   | | | |  | | | |  |                   1: On
#   | | | |  | | | |  +---------------- Remove obsolete DGDM calibrations (RemoveDGDM_CalsA2lBuff)
#   | | | |  | | | |                      0: Off
#   | | | |  | | | |                      1: On
#   | | | |  | | | +------------------- Fix ETC bit fields (FixETC_BitFieldsA2lBuff)
#   | | | |  | | |                        0: Off
#   | | | |  | | |                        1: On
#   | | | |  | | +--------------------- Add System Configuration calibrations folder (AddSystemConfigCalsA2lBuff)
#   | | | |  | |                          0: Off
#   | | | |  | |                          1: On
#   | | | |  | +----------------------- Fix ULONG Booleans (FixUlongBooleansA2lBuff)
#   | | | |  |                            0: Off
#   | | | |  |                            1: On
#   | | | |  +------------------------- Remove not needed measurements (RemoveMeasurementsA2lBuff)
#   | | | |                               0: Off
#   | | | |                               1: On
#   | | | +---------------------------- Fix ULONG Words (FixUlongWordsA2lBuff)
#   | | |                                 0: Off
#   | | |                                 1: On
#   | | +------------------------------ Not implemented
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
#
###############################################################################
#
# Current Module Info:
# %full_name:      tcb_pt1#1/Perl/a2lcorr.pl/4.0 %
# %date_created:   Sat Oct 11 10:49:05 2003 %
# %version:        4.0 %
# %derived_by:     gpstepie %
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
$CorrModeMask = 0xFFDF;

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

sub FixCoefA2lBuff
{
  local( *a2l_file_buff ) = @_;
  local( $index ) = -1;
  local( $start_processing ) = $false;
  local( $tmp_line ) = "";

  $start_processing = $false;
  $index = -1;
  while ( ++$index <= $#a2l_file_buff )
  {
    $tmp_line = $a2l_file_buff[$index];
    if ( $start_processing == $false )
    {
      if ( $tmp_line =~ /\/begin\s+COMPU_METHOD/ )
      {
        $start_processing = $true;
      }
    }
    else
    {
      if ( $tmp_line =~ /^\s*COEFFS\s+/ )
      {
        if ( $tmp_line =~ /0\.007812000000$/ )
        {
          $tmp_line = $` . "0.007812500000" . $';
        }
        elsif ( $tmp_line =~ /0\.003906000000$/ )
        {
          $tmp_line = $` . "0.003906250000" . $';
        }
        elsif ( $tmp_line =~ /0\.001953000000$/ )
        {
          $tmp_line = $` . "0.001953250000" . $';
        }
        elsif ( $tmp_line =~ /0\.000977000000$/ )
        {
          $tmp_line = $` . "0.000976562500" . $';
        }
        elsif ( $tmp_line =~ /0\.000488000000$/ )
        {
          $tmp_line = $` . "0.000488281250" . $';
        }
        elsif ( $tmp_line =~ /0\.000244000000$/ )
        {
          $tmp_line = $` . "0.000244140625" . $';
        }
        elsif ( $tmp_line =~ /0\.000122000000$/ )
        {
          $tmp_line = $` . "0.000122070312" . $';
        }
        elsif ( $tmp_line =~ /0\.000061000000$/ )
        {
          $tmp_line = $` . "0.000061035156" . $';
        }
        elsif ( $tmp_line =~ /0\.000031000000$/ )
        {
          $tmp_line = $` . "0.000030517578" . $';
        }
        elsif ( $tmp_line =~ /0\.000015000000$/ )
        {
          $tmp_line = $` . "0.000015258789" . $';
        }
        elsif ( $tmp_line =~ /0\.000008000000$/ )
        {
          $tmp_line = $` . "0.000007629394" . $';
        }
        elsif ( $tmp_line =~ /0\.000004000000$/ )
        {
          $tmp_line = $` . "0.000003814697" . $';
        }
        elsif ( $tmp_line =~ /0\.000002000000$/ )
        {
          $tmp_line = $` . "0.000001907348" . $';
        }
        elsif ( $tmp_line =~ /0\.000001000000$/ )
        {
          $tmp_line = $` . "0.000000953674" . $';
        }
        $a2l_file_buff[$index] = $tmp_line;
      }
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

sub CorrectTnblAxisA2lBuff
{
  local( *a2l_file_buff ) = @_;
  local( %table_def ) =
    (
    #  table name, tunable axis name
      'KtEPSE_dm_Std_ThrottleFlow',      'KtEPSE_AXIS_StdThrottleFlow',
      'KtEPSE_dm_Std_ThrotFlowLrnLimLo', 'KtEPSE_AXIS_StdThrottleFlow',
      'KtEPSE_dm_Std_ThrotFlowLrnLimHi', 'KtEPSE_AXIS_StdThrottleFlow',
      'KtETSE_T_CombustionGasTemp',      'KtETSE_AXIS_dm_CombustGasTemp',
      'KtETSE_k_HTC_ExhaustMnfd',        'KtETSE_AXIS_dm_ExhaustMnfd',
      'KtETSE_k_HTC_IntakePlenumPreEGR', 'KtETSE_AXIS_dm_IntkPlnmPreEGR',
      'KtETSE_k_HTC_EGR_Inlet',          'KtETSE_AXIS_dm_EGR_InletOutlet',
      'KtETSE_k_HTC_EGR_Outlet',         'KtETSE_AXIS_dm_EGR_InletOutlet',
      'KtTORQ_M_PropTerm',               'KtTORQ_M_PropTerm_Brkpts',
      'KtVIOS_U_ETCM_SpringCompTerm',    'KtVIOS_ETCM_SpringCompBrkpts',
      'KtETSE_Runner_ICT_Corr',          'KtETSE_AXIS_dm_Runner_ICT_Corr',
      'KtEXAC_T_EngSpdAirflowDelta',     'KtEXAC_AXIS_EngSpdAirflowDelta',
      'KtIDLE_n_AlterPWM_OffsetDecr',    'KtIDLE_AXIS_n_AlterPWM_RPM_Ofst',
      'KtIDLE_n_AlterPWM_OffsetIncr',    'KtIDLE_AXIS_n_AlterPWM_RPM_Ofst',
      'KtSPRK_phi_Base',                 'KtSPRK_AXIS_BaseSprkAdv',
      'KtSPRK_phi_Base_LowOct',          'KtSPRK_AXIS_BaseSprkAdv',
      'KtSPRK_phi_BaseConvMgt',          'KtSPRK_AXIS_BaseSprkAdv',
      'KtSPRK_phi_MBT_SpkAdv',           'KtSPRK_AXIS_BaseSprkAdv',
      'KtTRQC_phi_MBT_SpkAdv',           'KtSPRK_AXIS_BaseSprkAdv',
      'KtSPRK_phi_BaseIdle',             'KtSPRK_AXIS_IdleBaseSprkAdv',
      'KtSPRK_phi_BaseIdleConvMngt',     'KtSPRK_AXIS_IdleBaseSprkAdv',
      'KtEXAC_k_CatTempIncreasing',      'KtEXAC_AXIS_EngSpdAirflowDelta',
      'KtEXAC_k_CatTempDecreasing',      'KtEXAC_AXIS_EngSpdAirflowDelta',
      'KtEXAC_k_CatTgtIncreasing',       'KtEXAC_AXIS_EngSpdAirflowDelta',
      'KtEXAC_k_CatTgtDecreasing',       'KtEXAC_AXIS_EngSpdAirflowDelta',
      'KtELCL_Pct_AC_HighLoadDC',        'KtELCL_AXIS_PWMFanDC',
      'KtELCL_Pct_AC_HighSpdLowLoadDC',  'KtELCL_AXIS_PWMFanDC',
      'KtELCL_Pct_AC_HighSpdMedLoadDC',  'KtELCL_AXIS_PWMFanDC',
      'KtELCL_Pct_AC_MedSpdLowLoadDC',   'KtELCL_AXIS_PWMFanDC',
      'KtELCL_Pct_AC_MedSpdMedLoadDC',   'KtELCL_AXIS_PWMFanDC',
      'KtELCL_Pct_AC_LowSpdLowLoadDC',   'KtELCL_AXIS_PWMFanDC',
      'KtELCL_Pct_AC_LowSpdMedLoadDC',   'KtELCL_AXIS_PWMFanDC',
      'KtELCL_Pct_AC_Off_FanDC',         'KtELCL_AXIS_PWMFanDC',
      'KtTORQ_M_TipInBumpRampRateGear1', 'KtTORQ_AXIS_TipInBumpRampRate',
      'KtTORQ_M_TipInBumpRampRateGear2', 'KtTORQ_AXIS_TipInBumpRampRate',
      'KtTORQ_M_TipInBumpRampRateGear3', 'KtTORQ_AXIS_TipInBumpRampRate',
      'KtTORQ_M_TipInBumpRampRateGear4', 'KtTORQ_AXIS_TipInBumpRampRate',
      'KtTORQ_M_TipInBumpRampRateGear5', 'KtTORQ_AXIS_TipInBumpRampRate',
      'KtIDLE_Pct_PS_CrampAirflowOfst',  'KtIDLE_AXIS_PS_CrampAirflowOfst',
      'KtEOSD_I_11_HtrCurrFiltThrsh',    'KtEOSD_I_HtrCurrThrsh_Brkpts',
      'KtEOSD_I_12_HtrCurrFiltThrsh',    'KtEOSD_I_HtrCurrThrsh_Brkpts',
      'KtEOSD_I_21_HtrCurrFiltThrsh',    'KtEOSD_I_HtrCurrThrsh_Brkpts',
      'KtEOSD_I_22_HtrCurrFiltThrsh',    'KtEOSD_I_HtrCurrThrsh_Brkpts'
    );
  local( %tunable_axis_def ) =
    (
    #  tunable axis name, index to tunable axis comp method
      'KtEPSE_AXIS_StdThrottleFlow', 0,
      'KtETSE_AXIS_dm_CombustGasTemp', 1,
      'KtETSE_AXIS_dm_ExhaustMnfd', 1,
      'KtETSE_AXIS_dm_IntkPlnmPreEGR', 1,
      'KtETSE_AXIS_dm_EGR_InletOutlet', 2,
      'KtTORQ_M_PropTerm_Brkpts', 3,
      'KtVIOS_ETCM_SpringCompBrkpts', 4,
      'KtETSE_AXIS_dm_Runner_ICT_Corr', 1,
      'KtEXAC_AXIS_EngSpdAirflowDelta', 5,
      'KtIDLE_AXIS_n_AlterPWM_RPM_Ofst', 6,
      'KtSPRK_AXIS_BaseSprkAdv', 7,
      'KtELCL_AXIS_PWMFanDC', 8,
      'KtSPRK_AXIS_IdleBaseSprkAdv',7,
      'KtTORQ_AXIS_TipInBumpRampRate', 3,
      'KtIDLE_AXIS_PS_CrampAirflowOfst', 9,
      'KtEOSD_I_HtrCurrThrsh_Brkpts', 0 
    );
  local( @ta_comp_method_param_list ) =
    ( '%:0.0 1.0 0.000000 0.0 0.0 0.003051757',            # 0
      'g\/s:0.0 1.0 0.000000 0.0 0.0 0.0078125',           # 1
      'g\/s:0.0 1.0 0.000000 0.0 0.0 0.0009765625',        # 2
      'Newton-meter:0.0 1.0 0.000000 0.0 0.0 0.0625',      # 3
      '%:0.0 1.0 0.000000 0.0 0.0 0.00390625',             # 4
      'gm\/sec:0.0 1.0 0.000000 0.0 0.0 0.0078125',        # 5
      '% duty cycle:0.0 1.0 0.000000 0.0 0.0 0.001525878', # 6
      'RPM:0.0 1.0 0.000000 0.0 0.0 0.125',                # 7
      'deg C:0.0 1.0 0.000000 0.0 0.0 0.0078125',          # 8
      'kpa:0.0 1.0 0.000000 0.0 0.0 0.5',                  # 9
      'amps:0.0 1.0 0.000000 0.0 0.0 0.00012207'           # 10
    );


  local( @table_list ) = sort keys (%table_def);
  local( @ta_comp_method_list ) = ();
  local( @curr_tunable_axis_list, @curr_ta_comp_method_list ) = ( (), () );
  local( $index, $index1, $index2 ) = ( -1, -1, -1 );
  local( $start_processing ) = $false;
  local( $tmp_str, $tmp_str1, $tmp_str2 ) = ( "", "", "" );
  local( $tmp_line ) = "";

  splice( @ta_comp_method_list, 0, -1, @ta_comp_method_param_list );
  $index  = -1;
  while ( ++$index <= $#ta_comp_method_list )
  {
    $ta_comp_method_list[$index] = "NULL";
  }

#  print STDERR "\@ta_comp_method_list\n";
#  &PrintList( *ta_comp_method_list );

  $start_processing = $false;
  $index  = -1;
  while ( ++$index <= $#a2l_file_buff )
  {
    $tmp_line = $a2l_file_buff[$index];
    if ( $start_processing == $false )
    {
      if ( $tmp_line =~ /\/begin\s+COMPU_METHOD\s+(.*)/ )
      {
        $tmp_str = $1;
        $start_processing = $true;
      }
    }
    else
    {
      if ( $tmp_line =~ /\/end\s+COMPU_METHOD/ )
      {
        $start_processing = $false;
        if ( grep(/NULL/, @ta_comp_method_list) == 0 )
        {
          $index = $#a2l_file_buff;
        }
      }
      else
      {
        $index1 = -1;
        while ( ++$index1 <= $#ta_comp_method_param_list )
        {
          if ( $ta_comp_method_list[$index1] eq "NULL" )
          {
            $ta_comp_method_param_list[$index1] =~ /([^:]+):(.*)/;
            $tmp_str1 = $1;
            $tmp_str2 = $2;
            if ( $tmp_line =~ /$tmp_str1/
              && $a2l_file_buff[$index+1] =~ /$tmp_str2/ )
            {
              $ta_comp_method_list[$index1] = $tmp_str;
            }
          }
        }
      }
    }
  }

#  print STDERR "\@ta_comp_method_list\n";
#  &PrintList( *ta_comp_method_list );

  $start_processing = $false;
  $index = -1;
  $index1 = 0;
  while ( ++$index <= $#a2l_file_buff )
  {
    $tmp_line = $a2l_file_buff[$index];
    if ( $start_processing == $false )
    {
      if ( $tmp_line =~ /\/begin\s+CHARACTERISTIC\s+/ )
      {
        $index2 = -1;
        while ( ++$index2 <= $#table_list )
        {
          $tmp_str = $table_list[$index2];
          if ( $tmp_line =~ /\/begin\s+CHARACTERISTIC\s+$tmp_str\.data/ )
          {
#            print STDERR "Removing $tmp_str\n";
            splice( @table_list, $index2, 1 );
            $index2 = $#table_list;
            $start_processing = $true;
          }
        }
      }
    }
    else
    {
      if ( $tmp_line =~ /(\s+AXIS_PTS_REF\s+)/ )
      {
        $tmp_line = "$1$table_def{$tmp_str}\.data\n";
        if ( grep(/$table_def{$tmp_str}/, @curr_tunable_axis_list) == 0 )
        {
#          print STDERR " curr_tunable_axis_list : adding ($table_def{$tmp_str})\n";
          push( @curr_tunable_axis_list, $table_def{$tmp_str} );
        }
#        print STDERR "\n- $a2l_file_buff[$index]";
#        print STDERR "+ $tmp_line\n";
        $a2l_file_buff[$index] = $tmp_line;
        $start_processing = $false;
        if ( $#table_list < 0 )
        {
          $index1 = $index;
          $index  = $#a2l_file_buff;
        }
      }
      elsif ( $tmp_line =~ /\/end\s+CHARACTERISTIC/ )
      {
        $start_processing = $false;
      }
    }
  }

  if ( $#table_list >= 0 )
  {
    print STDERR "(?) CorrectTnblAxisA2lBuff() : The following tables weren't processed:\n";
    foreach ( @table_list )
    {
      print STDERR "  $_\n";
    }
  }

  $index = -1;
  while ( ++$index <= $#curr_tunable_axis_list )
  {
    $tmp_str = $curr_tunable_axis_list[$index];
    if ( ! defined($tunable_axis_def{$tmp_str}) )
    {
      print STDERR "(!) CorrectTnblAxisA2lBuff() : No comp-method found for $tmp_str\n";
    }
  }

  $index = -1;
  while ( ++$index <= $#curr_tunable_axis_list )
  {
    $tmp_str = $curr_tunable_axis_list[$index];
    if ( grep(/$ta_comp_method_list[$tunable_axis_def{$tmp_str}]/, @curr_ta_comp_method_list) == 0 )
    {
      if ( "$ta_comp_method_list[$tunable_axis_def{$tmp_str}]" eq "NULL" )
      {
        print STDERR "(!) CorrectTnblAxisA2lBuff() : No comp-method $ta_comp_method_param_list[$tunable_axis_def{$tmp_str}] was found.\n";
        return( $errNOK );
      }
#      print STDERR "  curr_ta_comp_method_list : adding ($tmp_str, $ta_comp_method_list[$tunable_axis_def{$tmp_str}])\n";
      push( @curr_ta_comp_method_list, $ta_comp_method_list[$tunable_axis_def{$tmp_str}] );
    }
  }

#  print STDERR "\@curr_tunable_axis_list\n";
#  &PrintList( *curr_tunable_axis_list );
#  print STDERR "\@curr_ta_comp_method_list\n";
#  &PrintList( *curr_ta_comp_method_list );

  $start_processing = $false;
  $index  = $index1;
  while ( ++$index <= $#a2l_file_buff )
  {
    $tmp_line = $a2l_file_buff[$index];
    if ( $start_processing == $false )
    {
      if ( $tmp_line =~ /\/begin\s+AXIS_PTS\s+/ )
      {
        $index2 = -1;
        while ( ++$index2 <= $#curr_tunable_axis_list )
        {
          $tmp_str = $curr_tunable_axis_list[$index2];
          if ( $tmp_line =~ /\/begin\s+AXIS_PTS\s+($tmp_str)/ )
          {
            ($tmp_line = $tmp_line) =~ s/$1\S+/$tmp_str\.data/;
            $tmp_str1 = $ta_comp_method_list[$tunable_axis_def{$tmp_str}];
            splice( @curr_tunable_axis_list, $index2, 1 );
            $index2 = $#curr_tunable_axis_list;
#            print STDERR "\n-1- $a2l_file_buff[$index]";
#            print STDERR "+1+ $tmp_line\n";
            $a2l_file_buff[$index] = $tmp_line;
            $start_processing = $true;
          }
        }
      }
    }
    else
    {
      if ( $tmp_line =~ /\/end\s+AXIS_PTS/ )
      {
        $start_processing = $false;
        if ( $#curr_tunable_axis_list < 0 )
        {
          $index1 = $index;
          $index  = $#a2l_file_buff;
        }
      }
      elsif ( $tmp_line =~ /\sN_EQUALS_E_Comp\s/ )
      {
        ($tmp_line = $tmp_line) =~ s/N_EQUALS_E_Comp/$tmp_str1/;
#        print STDERR "\n-2- $a2l_file_buff[$index]";
#        print STDERR "+2+ $tmp_line\n";
        $a2l_file_buff[$index] = $tmp_line;
      }
      elsif ( $tmp_line =~ /(\s+DISPLAY_IDENTIFIER\s+)/ )
      {
        $tmp_line = "$1$tmp_str\.data\n";
#        print STDERR "\n-3- $a2l_file_buff[$index]";
#        print STDERR "+3+ $tmp_line\n";
        $a2l_file_buff[$index] = $tmp_line;
      }
    }
  }

  if ( $#curr_tunable_axis_list >= 0 )
  {
    print STDERR "(!) CorrectTnblAxisA2lBuff() : The following tunable axes weren't processed:\n";
    foreach ( @curr_tunable_axis_list )
    {
      print STDERR "  $_\n";
    }
    return( $errNOK );
  }

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
        'KfACOD_U_SystemThrshLo', 0
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

sub FixETC_BitFieldsA2lBuff
{
  local( *a2l_file_buff )  = @_;
  local( $index ) = ( -1 );
  local( $start_processing ) = $false;
  local( $tmp_line ) = "";
  local( $tmp_str ) = "";
  local( %mask_list ) = (
    'EAP1RTFL', '0x00000100',
    'EAP2RFCM', '0x00010000',
    'EAP2RTFL', '0x01000000'
  );
  local( $num_of_completed_subs ) = ( -1 );
  local( @measurement_list ) = sort keys (%mask_list);

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
        if ( defined($mask_list{$tmp_str}) )
        {
          $start_processing = $true;
        }
      }
    }
    else
    {
      if ( $tmp_line =~ /\/end\s+MEASUREMENT/ )
      {
        $start_processing = $false;
      }
      elsif ( $tmp_line =~ /(BIT_MASK\s+)0x00000001/ )
      {
        $a2l_file_buff[$index] = $` . $1 . $mask_list{$tmp_str} . $';
#        print STDERR "Processing $tmp_str:$mask_list{$tmp_str}\n";
#        print STDERR "< $tmp_line";
#        print STDERR "> $a2l_file_buff[$index]\n";
        if ( ++$num_of_completed_subs > $#measurement_list )
        {
          last;
        }
      }
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
  "          KeTORQ_ChassisTorqCntrlType\n",
  "          KeTRVC_TransType\n",
  "          KeVIOS_ExhaustConfig\n",
  "          KeVIOS_O2_PumpingCurrentEnable\n",
  "          KeVIOS_SystemVulnerabilityState\n",
  "          KeVIOS_TCS_CAN_Version\n",
  "          KeVIOS_VehicleSpeedSource\n",
  "          KfEPSE_V_CylinderVolume\n",
  "          KfTORQ_EngineDisplacement\n",
  "          KfTRQC_EngineDisplacement\n",
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

sub FixUlongBooleansA2lBuff
{
  local( *a2l_file_buff ) = @_;
  local( $index ) = -1;
  local( $start_processing ) = $false;
  local( $tmp_line ) = "";
  local( $line_cnt ) = -1;
  local( %ulong_boolean_list ) = (
    'EAP12FCM', 0,
    'EAP12TFL', 1,
    'EAP13FCM', 2,
    'EAP13TFL', 3,
    'EAP1RFCM', 4,
    'EAP1RTFL', 5,
    'EAP1LFCM', 6,
    'EAP1LRTF', 7,
    'EAP2LFCM', 8,
    'EAP2LRTF', 9,
    'EAP3LFCM', 10,
    'EAP3LRTF', 11,
    'EAP1HFCM', 12,
    'EAP1HRTF', 13,
    'EAP2HFCM', 14,
    'EAP2HRTF', 15,
    'EAP3HFCM', 16,
    'EAP3HRTF', 17,
    'EAP23FCM', 18,
    'EAP23TFL', 19,
    'EAP2RFCM', 20,
    'EAP2RTFL', 21,
    'EAP3RFCM', 22,
    'EAP3RTFL', 23,
    'ETAHFCM',  24,
    'ETAHTF',   25,
    'ETALFCM',  26,
    'ETALTF',   27,
    'ETP1RFCM', 28,
    'ETP1RTFL', 29,
    'ETP1LFCM', 30,
    'ETP1LTFL', 31,
    'ETP1HFCM', 32,
    'ETP1HTFL', 33,
    'ETP2RFCM', 34,
    'ETP2RTFL', 35,
    'ETP2LFCM', 36,
    'ETP2LTFL', 37,
    'ETP2HFCM', 38,
    'ETP2HTFL', 39,
    'ETPCRFCM', 40,
    'ETPCRTFL', 41,
    'RAP12FCM', 42,
    'RAP12TFL', 43,
    'RAP13FCM', 44,
    'RAP13TFL', 45,
    'RAP1RFCM', 46,
    'RAP1RTFL', 47,
    'RAP23FCM', 48,
    'RAP23TFL', 49,
    'RAP2RFCM', 50,
    'RAP2RTFL', 51,
    'RAP3RFCM', 52,
    'RAP3RTFL', 53,
    'TRQDHFCM', 54,
    'TRQDHTF',  55,
    'TRQDLFCM', 56,
    'TRQDLTF',  57,
    'VRFARTFL', 58,
    'VRFBRTFL', 59,
    'VRFCRTFL', 60
  );
  local( $num_of_completed_subs ) = ( -1 );
  local( @measurement_list ) = sort keys (%ulong_boolean_list);

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
        if ( defined($ulong_boolean_list{$1}) )
        {
          $start_processing = $true;
          $line_cnt = 0;
        }
      }
    }
    else
    {
      if ( ++$line_cnt == 2 )
      {
        if ( $tmp_line =~ /ULONG/ )
        {
          $a2l_file_buff[$index] = "$`UBYTE$'";
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
          print STDERR "(!) FixUlongBooleansA2lBuff() : $a2l_file_buff[$index-2]\n";
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

sub FixUlongWordsA2lBuff
{
  local( *a2l_file_buff ) = @_;
  local( $index ) = -1;
  local( $start_processing ) = $false;
  local( $tmp_line ) = "";
  local( $line_cnt ) = -1;
  local( %ulong_words_list ) = (
    'DMRAM1', 0,
    'DMRAM2', 1,
    'DMRAM3', 2,
    'DMRAM4', 3,
    'DMRAM5', 4
  );
  local( $num_of_completed_subs ) = ( -1 );
  local( @measurement_list ) = sort keys (%ulong_words_list);

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
        if ( defined($ulong_words_list{$1}) )
        {
          $start_processing = $true;
          $line_cnt = 0;
        }
      }
    }
    else
    {
      if ( ++$line_cnt == 2 )
      {
        if ( $tmp_line =~ /ULONG/ )
        {
          $a2l_file_buff[$index] = "$`UWORD$'";
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
          print STDERR "(!) FixUlongWordsA2lBuff() : $a2l_file_buff[$index-2]\n";
        }
        $start_processing = $false;
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

if ( $CorrModeMask & 0x0002 )
{
  if ( ($ErrCode=&FixCoefA2lBuff(*A2lFileBuff)) != $errOK )
  {
    exit $ErrCode;
  }
#  print STDERR "FixCoefA2lBuff() is done\n";
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

if ( $CorrModeMask & 0x0040 )
{
  if ( ($ErrCode=&CorrectTnblAxisA2lBuff(*A2lFileBuff)) != $errOK )
  {
    exit $ErrCode;
  }
#  print STDERR "CorrectTnblAxisA2lBuff() is done\n";
}

if ( $CorrModeMask & 0x0080 )
{
  if ( ($ErrCode=&RemoveDGDM_CalsA2lBuff(*A2lFileBuff)) != $errOK )
  {
    exit $ErrCode;
  }
#  print STDERR "RemoveDGDM_CalsA2lBuff() is done\n";
}

if ( $CorrModeMask & 0x0100 )
{
  if ( ($ErrCode=&FixETC_BitFieldsA2lBuff(*A2lFileBuff)) != $errOK )
  {
    exit $ErrCode;
  }
#  print STDERR "FixETC_BitFieldsA2lBuff() is done\n";
}

if ( $CorrModeMask & 0x0200 )
{
  if ( ($ErrCode=&AddSystemConfigCalsA2lBuff(*A2lFileBuff)) != $errOK )
  {
    exit $ErrCode;
  }
#  print STDERR "AddSystemConfigCalsA2lBuff() is done\n";
}

if ( $CorrModeMask & 0x0400 )
{
  if ( ($ErrCode=&FixUlongBooleansA2lBuff(*A2lFileBuff)) != $errOK )
  {
    exit $ErrCode;
  }
#  print STDERR "FixUlongBooleansA2lBuff() is done\n";
}

if ( $CorrModeMask & 0x0800 )
{
  if ( ($ErrCode=&RemoveMeasurementsA2lBuff(*A2lFileBuff)) != $errOK )
  {
    exit $ErrCode;
  }
#  print STDERR "RemoveMeasurementsA2lBuff() is done\n";
}

if ( $CorrModeMask & 0x1000 )
{
  if ( ($ErrCode=&FixUlongWordsA2lBuff(*A2lFileBuff)) != $errOK )
  {
    exit $ErrCode;
  }
#  print STDERR "FixUlongWordsA2lBuff() is done\n";
}

&PrintBuff( *A2lFileBuff );

exit $ErrCode;

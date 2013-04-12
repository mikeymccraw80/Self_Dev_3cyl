#!/usr/contrib/bin/perl
##########################################################################
#
# This script is used by Makefile to update
# ancillary file based on extended map file.
#
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#
# Rev.  YYMMDD Who Changes
# ----- ------ --- -------------------------------------------------------
# 1.1   001123 gps Initial release.
# 1.2   010516 gps Fixed symbol length 40 problem.
# 1.3   010712 gps Added preproccesing for extra ancillary input records.
# 1.4   010716 gps Excluded .text symbols from the reference list.
# 1.5   020316 gps Added ExtractSymInfoDC2 to be able to use different
#                   (common) exmap-file format.
# 1.6   020605 gps Added additional modification for length 40 problem.
# 1.7   021106 gps Changes in description field.
#                  Modified AddDscrpt2AncFile.
# 1.8   030103 hdb Add changes to update scalings for transmission time
#                    variables.
# 6.0   031007 kan Modified subroutine AddDscrpt2AncFile so that both
#                   embedded and non-embedded ancillary files may be used
#                   during software build process
# 7     040201 gps TOOLS : ancupdate.pl Modifications Due 
#                   to Compile Time Switches Presence in anc-files.
#                  Modified and enhanced CreateCorrctdAncFile.
# 9     050310 caw Updated directory for Configuration_Objects.
# tcb_pt1#1.1.3
#       040604 kan Modified path names for GMDAT project:
#                   WAS: FS026_04Hyundai_EMSCore
#                   IS:  5SF65_GMDAT_MT34
# tcb_pt1#1.1.4
#       040803 rag Modified to support GMDAT Configuration
# tcb_pt1#5
#       060224 hdb 5490 Upgrade all ancillary files to new format.
#                   Allow for structures and arrays.
# 11    060714 hdb ---- Correct problem when subsystem is excluded from
#                       build (no entries in exmap file) but ancillary
#                       file is still present, and variable is part of
#                       a structure.
#
##########################################################################

# Constants

$errOK  =  0;
$errNA  =  1;
$errNOK =  -1;

$true  = 1;
$false = 0;

# Global Variables

($ProgramName = $0) =~ s/[^\/]*\///g;
$ErrCode = $errOK;

# Can be overwritten by input arguments
$MapFile = "leccore.exmap";
# $AncFile = "/users/gpstepie/public/dc2pool.anc";
$AncFile = "/tmp/dc2p.anc";
$FILEHANDLER;

undef %SymbolAscList1;
undef %SymbolAscList2;
@AncBuffer    = ();
undef %TransTimeList;

###############################################################################
#
# Subroutines
#
###############################################################################

sub PrintList
{
  local( *list1, *list2 ) = @_;
  local( $index1 );
  
  $Index1 = -1;
  while ( ++$Index1 <= $#list1 )
  {
    print STDOUT "$list1[$Index1], $list2[$Index1]\n";
  }
}

sub DisplaySymbolLists
{
   print  "\n\nSymbolAscList1 \n\n";
   foreach $key (keys %SymbolAscList1)
   {
     print  "SymbolList1   $key = $SymbolAscList1{$key} \n";
   }
   print  "\n\nSymbolAscList2 \n\n";
   foreach $key (keys %SymbolAscList2)
   {
     print  "SymbolList2   $key = $SymbolAscList2{$key} \n";
   }
}

sub BuildTimeConvertTable
{
  local( *time_list ) = @_;
  local ( %BaseTimeList, $collecting, $match_val );

  while ( <FILEHANDLER> )
  {
    if (  ( /define\s+(CcSYST_BASE_LOOP[a-zA-Z0-9_]+)\s+(\d*\.\d*)/ )
       || ( /define\s+(CcSYST_BASE_LOOP[a-zA-Z0-9_]+)\s+\(\s*(\d*\.\d*)\s*\)/ ) )
    {
      $BaseTimeList{$1} = $2;
    }
  }

  close( FILEHANDLER );
  
  while ( <FILEHANDLER> )
  {
    if ( $use_if eq TRUE )
    {
      if ( $collecting eq TRUE )
      {
        if ( ( /define\s+([a-zA-Z0-9_]+)\s+([a-zA-Z0-9_]+)/ )
          || ( /define\s+([a-zA-Z0-9_]+)\s+\(\s*([a-zA-Z0-9_]+)\s*\)/ ) )
        {
          $time_list{$1} = $BaseTimeList{$2};
        }
        elsif ( /else/ )
        {
          $collecting = FALSE;
        }
      }
      elsif ( /endif/ )
      {
         $use_if = FALSE;
      }
    }
    elsif ( $use_else eq TRUE )
    {
      if ( /endif/ )
      {
        $use_else = FALSE;
        $collecting = FALSE;
      }
      elsif ( $collecting eq TRUE )
      {
        if ( ( /define\s+([a-zA-Z0-9_]+)\s+([a-zA-Z0-9_]+)/ )
          || ( /define\s+([a-zA-Z0-9_]+)\s+\(\s*([a-zA-Z0-9_]+)\s*\)/ ) )
        {
          $time_list{$1} = $BaseTimeList{$2};
        }
      }
      elsif ( /else/ )
      {
         $collecting = TRUE;
      }
    }
    elsif ( /if(.*)/ )
    {
      if ( $1 =~ /XeTRNS_SYST_BASE_LOOP_TIME\s*==\s*([a-zA-Z0-9_]+)/ )
      {
        $if_val = $1;
        if ( $match_val eq $if_val )
        {
          $use_if = TRUE;
          $collecting = TRUE;
        }
        else
        {
          $use_else = TRUE;
        }
      }
    }
    elsif ( ( /define\s+XeTRNS_SYST_BASE_LOOP_TIME\s+([a-zA-Z0-9_]+)/ )
         || ( /define\s+XeTRNS_SYST_BASE_LOOP_TIME\s+\(\s*([a-zA-Z0-9_]+)\s*\)/ ) )
    {
      $match_val = $1;
    }
    elsif ( /define\s+(CcTRNS_SYST_BASE_LOOP[a-zA-Z0-9_]+)\s+\(\s*([a-zA-Z0-9_]+)\s*\*\s*(\d+)\s*\)/ )
    {
      $time_list{$1} = $time_list{$2} * $3;
    }
    elsif ( /define\s+(CcTRNS_SYST_BASE_LOOP[a-zA-Z0-9_]+)\s+\(\s*([a-zA-Z0-9_]+)\s*\/\s*(\d+)\s*\)/ )
    {
      $time_list{$1} = $time_list{$2} / $3;
    }
  }

  close( FILEHANDLER );
  return( $errOK );
}

sub ExtractSymInfo
{
  local( *map_file, *sym_asc_list1, *sym_asc_list2 ) = @_;
  local( $tmp_str ) = "";

  if ( ! open(FILEHANDLER, $map_file) )
  {
    print STDERR "(!) ExtractSymInfo, open($map_file): $?, $!\n";
    return( $errNOK );
  }

  while ( <FILEHANDLER> )
  {
    if ( /([a-zA-Z0-9_]+)\.([a-zA-Z0-9_]+)/ )
    {
      $tmp_str = $2;
      if ( ! defined($sym_asc_list1{$tmp_str}) )
      {
        #  Table 1 - key is 'variable_name', data is file_name
        $sym_asc_list1{$tmp_str} = $1;
#        print STDERR " list1 ! defined($sym_asc_list1{$tmp_str}) for $tmp_str \n";   # TEST HDB
      }
      else
      {
#        print STDERR "(!) $map_file : [1] Redundant symbol information $tmp_str\n";
      }
      $tmp_str = $&;
      if ( ! defined($sym_asc_list2{$tmp_str}) )
      {
        #  Table 1 - key is 'file_name.variable_name', data is file_name
        $sym_asc_list2{$tmp_str} = $1;
#        print STDERR " list2 ! defined($sym_asc_list2{$tmp_str}) for $tmp_str \n";   # TEST HDB
      }
      else
      {
#        print STDERR "(!) $map_file : [2] Redundant symbol information $tmp_str\n";
      }
    }
  }

  close( FILEHANDLER );
  return( $errOK );
}

sub CreateCorrctdAncFile
{
  local( *sym_asc_list1, *sym_asc_list2, *anc_buffer ) = @_;
  local( $tmp_line, $file_name ) = ( "", "" );
  local( $sym_name_old, $sym_name_old1, $sym_name_old2, $sym_name ) = ( "", "", "", "" );
  local( $index, $index1, $index2, $index3, $index4, $index5, $index6 ) = ( -1, -1, -1, -1, -1, -1, -1 );
  local( $symbol_exists ) = $false;
  local( @sym_list )      = sort keys (%sym_asc_list1);
  local( @tmp_buffer )    = ();

  if ( ! open(FILEHANDLER, $AncFile) )
  {
    print STDERR "(!) CreateCorrctdAncFile, open($AncFile): $?, $!\n";
    return( $errNOK );
  }

  $/='}';  # set terminator to scan for everything to next '}' (ignore line breaks)

  while ( <FILEHANDLER> )
  {
    push( @tmp_buffer, $_ );
  }
  close( FILEHANDLER );
  
  $index1 = $index2 = $index3 = $index4 = $index5 = $index6 = 0;
  foreach ( @tmp_buffer )
  {
    # extract symbol name

    $tmp_line = $_;
    $symbol_exists = $false;
    if ( ( /(variable_location\.symbol\s*\=\s*)([._a-zA-Z0-9]+)(\s*\;)/ )   #variable name only
      || ( /(variable_location\.symbol\s*\=\s*)([._a-zA-Z0-9]+)(\s*\[.+\;)/ ) )  #indexed variable
    {
      $sym_name_old = $sym_name_old1 = $sym_name_old2 = $2;
      ($sym_name_old = $sym_name_old) =~ s/^_//;
      $file_name = "";
      $structure_detail = "";
      $structure_variable = FALSE;
      if ( $sym_name_old =~ /\./ )
      {
         $left_part   = $`;  # preceeding \.
         $right_part  = $';  # following \.
         if ( defined $sym_asc_list1{$left_part} )
         {
           #  must be a structure
           $file_name     = $sym_asc_list1{$left_part};
           $sym_name_old2 = $file_name . "." . $left_part;
           $structure_variable = TRUE;
           $structure_detail = $right_part;
         }
         else
         {
           #  not a structure, might be a file name.
           $file_name     = $left_part;
           $sym_name_old  = $right_part;
           ($sym_name_old = $sym_name_old) =~ s/^_//;
           # right part could still be a structure
           if ( $sym_name_old =~ /\./ )
           {
              $sym_name_old   = $`;  # preceeding \.
              $structure_detail  = $';  # following \.
              $structure_variable = TRUE;
           }
           $sym_name_old2 = $file_name . "." . $sym_name_old;
         }
      }
      else
      {
        $sym_name_old2 = $sym_name_old;
      }
      if ( defined($sym_asc_list1{$sym_name_old2}) )
      {
        # no module name : the anc-name matches the code-name
        $sym_name_old2 = $sym_asc_list1{$sym_name_old2} . "." . $sym_name_old2;
        ($tmp_line = $tmp_line) =~ s/$sym_name_old1/$sym_name_old2/g;
        push( @anc_buffer, $tmp_line );
        $symbol_exists = $true;
        ++$index1;
#        $index1 == 1 && print STDERR "(i) CreateCorrctdAncFile, [1] $sym_name_old1 -> $sym_name_old2\n";
        ($structure_variable eq TRUE) && $index1 == 1 && print STDERR "(i) CreateCorrctdAncFile, [1] $sym_name_old1 -> $sym_name_old2\n";
      }
      elsif ( defined($sym_asc_list2{$sym_name_old2}) )
      {
        # module name included : the anc-name matches the code-name
        $rep_val = $sym_name_old2;
        if ( $structure_variable eq TRUE )
        {
           $rep_val = $sym_name_old2 . '.' . $structure_detail;
        }
        ($tmp_line = $tmp_line) =~ s/$sym_name_old1/$rep_val/g;
        push( @anc_buffer, $tmp_line );
        $symbol_exists = $true;
        ++$index2;
#        $index2 == 1 && print STDERR "(i) CreateCorrctdAncFile, [2] $sym_name_old1 -> $sym_name_old2\n";
        ($structure_variable eq TRUE) && $index2 == 1 && print STDERR "(i) CreateCorrctdAncFile, [2] $sym_name_old1 -> $sym_name_old2\n";
      }
      elsif ( length($sym_name_old1) < 40 )
      {
        # the anc-name does not match the code-name
        # the anc-name is fully defined
        # are there any cases where the module name is incorrect ?
        if ( defined($sym_asc_list1{$sym_name_old}) )
        {
          $sym_name = $sym_asc_list1{$sym_name_old} . "." . $sym_name_old;
          ($tmp_line = $tmp_line) =~ s/$sym_name_old1/$sym_name/g;
          if ( ("$file_name" ne "") && ("$file_name" ne "$sym_asc_list1{$sym_name_old}") )
          {
            print STDERR "(!) CreateCorrctdAncFile, $sym_name_old1 : module name is no longer valid (L<40)\n";
          }
          push( @anc_buffer, $tmp_line );
          $symbol_exists = $true;
          ++$index3;
#          $index3 == 1 && print STDERR "(i) CreateCorrctdAncFile, [3] $sym_name_old1 -> $sym_name\n";
          ($structure_variable eq TRUE) && $index3 == 1 && print STDERR "(i) CreateCorrctdAncFile, [3] $sym_name_old1 -> $sym_name\n";
        }
      }
      else
      {
        # the anc-name does not match the code-name
        # the anc-name may include only the left-most portion of the code name
        # are there any cases where the code name was truncated and can be restored ?
        $index = -1;
        while ( ++$index <= $#sym_list )
        {
          if ( $sym_name_old eq substr($sym_list[$index],0,length($sym_name_old) ) )
          {
            $sym_name = $sym_asc_list1{$sym_list[$index]} . "." . $sym_list[$index];
            ($tmp_line = $tmp_line) =~ s/$sym_name_old1/$sym_name/g;
            if ( ("$file_name" ne "") && ("$file_name" ne "$sym_asc_list1{$sym_list[$index]}") )
            {
              print STDERR "(!) CreateCorrctdAncFile, $sym_name_old1 : module name is no longer valid\n";
            }
            push( @anc_buffer, $tmp_line );
            $symbol_exists = $true;
            ++$index4;
#            $index4 == 1 && print STDERR "(i) CreateCorrctdAncFile, [4] $sym_name_old1 -> $sym_name\n";
            ($structure_variable eq TRUE) && $index4 == 1 && print STDERR "(i) CreateCorrctdAncFile, [4] $sym_name_old1 -> $sym_name\n";
            last;
          }
        }
      }
      if ( $symbol_exists == $false )
      {
        # the anc-record should be ignored, watch out for potential compile time switches.
        if ( $tmp_line =~ /\s#[ie][^\{]+\{/ )
        {
          if ( $tmp_line =~ /\*?\-?\s*\w*\.?\w+\s*\{/ )
          {
            $tmp_line = $`;
            push( @anc_buffer, $tmp_line );
#            print STDERR "(i) CreateCorrctdAncFile, Addition of a compile time switch section\n[$tmp_line]\n";
            $index5++;
          }
          else
          {
            print STDERR "(!) CreateCorrctdAncFile, $AncFile : Incorrect anc-record\n[$tmp_line]\n";
          }
        }
      }
    }
    elsif ( /DAQ\s*\{/ || /Calibrations\s*\{/ )
    {
      push( @anc_buffer, $tmp_line );
    }
    $index6++;
  }

  printf( STDERR "(i) CreateCorrctdAncFile, Processed/Total number of anc-records %d\/%d\n",
          $index1 + $index2 + $index3 + $index4,
          $index6 );
#  if ( $error_found eq TRUE )
#  {
#     $ret_value = $errNOK;
#     print STDERR "Syntactical errors found.\n";
#  }
#  else
#  {
#     $ret_value = $errOK;
#  }

  return( $errOK );
}

sub AddDscrpt2AncFile
{
  local( *anc_buffer, *time_table ) = @_;
  local( $tmp_line1, $tmp_line2, $tmp_line3 ) = ( "", "", "" );
  local( $tmp_str ) = "";
  local( $index ) = -1;
  
  $index = -1;
  while ( ++$index <= $#anc_buffer )
  {
    # extract symbol name
    $tmp_line1 = $anc_buffer[$index];
    
    # check for time symbol formatted as (symbol/constant)
    if ( $tmp_line1 =~ /\s*ds_const_a\s*=\s*\((\s*)([a-zA-Z0-9_]+)(\s*\/\s*)(\d+)(\s*)\)/ )
    {
       $time_val = $time_table{$2} / $4;
       if ( $time_val eq "" )
       {
          print STDERR "$2 is invalid in ";
          print STDERR $tmp_line1;
       }
       else
       {
          $time_char = "\"${time_val}\"";
          ($tmp_line1 = $tmp_line1) =~ s/\($1$2$3$4$5\)/$time_char/;
       }
    }
    # else check for time symbol formatted as symbol
    elsif ( $tmp_line1 =~ /\s*ds_const_a\s*=\s*([a-zA-Z0-9_]+)/ )
    {
       $time_val = $time_table{$1};
       if ( $time_val eq "" )
       {
          print STDERR "$1 is invalid in ";
          print STDERR $tmp_line1;
       }
       else
       {
          $time_char = "\"${time_val}\"";
          ($tmp_line1 = $tmp_line1) =~ s/$1/$time_char/;
       }
    }
    # else if this entry contains ds_const_a
    elsif ( $tmp_line1 =~ /\s*ds_const_a\s*=\s*/ )
    {
       #  check for valid numeric scaling format, such as "-1.000" or "1" or "0.0125"  
       if ( ! ( ( $tmp_line1 =~ /\s*ds_const_a\s*=\s*\"\-?\d+\.\d+\"/ )
             || ( $tmp_line1 =~ /\s*ds_const_a\s*=\s*\"\-?\d+\"/ ) ) )
       {
          print STDERR "\n\ninvalid ds_const_a entry in the following specification:";
          print STDERR $tmp_line1;
       }
    }
    
    if ( $tmp_line1 =~ /\sdescription\s*=/ )
    {
    }
    elsif ( $tmp_line1 =~ /\n(\*?-?)(\s*label\s*=[^\;]+\;)/ )
    {
      $tmp_str = $1;
      ($tmp_line2 = $2) =~ s/label      /description/;
      $tmp_line1 =~ /([a-zA-Z0-9_.]+)\s*\{/;
      $tmp_line3 = $1;
      ($tmp_line2 = $tmp_line2) =~ s/=[^;]+/= \"$tmp_line3\"/;
      ($tmp_line1 = $tmp_line1) =~ s/\}/${tmp_line2}\n${tmp_str}\}/;
    }
    print $tmp_line1;
  }
  return( $errOK );
}

###############################################################################
#
# Main
#
###############################################################################

if ( $#ARGV eq 1 )
{
  $MapFile = $ARGV[0];
  $AncFile = $ARGV[1];
}

$vehcfg = $ENV{'VEHCFG'};
#if ( $home_dir eq "" )
#{
#  $vehcfg = "Lambda_PCM";
#}
$home_dir = $ENV{'HOME_DIR'};
if ( $home_dir eq "" )
{
  $home_dir = "../";
}

#print STDERR "ancupdate.pl - Building tables\n";
if ( ($ErrCode=&BuildTimeConvertTable(*TransTimeList)) != $errOK )
{
  exit( $ErrCode );
}

#print STDERR "ancupdate.pl - Extracting Symbol Information\n";
if ( ($ErrCode=&ExtractSymInfo(*MapFile, *SymbolAscList1, *SymbolAscList2)) != $errOK )
{
  exit( $ErrCode );
}

#  &DisplaySymbolLists();

#print STDERR "ancupdate.pl - Creating Corrected ANC File\n";
if ( ($ErrCode=&CreateCorrctdAncFile(*SymbolAscList1, *SymbolAscList2, *AncBuffer)) != $errOK )
{
  exit( $ErrCode );
}

#print STDERR "ancupdate.pl - Adding Descriptions to ANC File\n";
if ( ($ErrCode=&AddDscrpt2AncFile(*AncBuffer, *TransTimeList)) != $errOK )
{
  exit( $ErrCode );
}

exit( $ErrCode );
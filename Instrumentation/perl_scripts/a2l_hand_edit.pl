#!/usr/contrib/bin/perl

###############################################################################
#
# a2l_method inserts the hand edited values for ETC and GAN update.
#
###############################################################################
#
# Revision History:
#
# Rev.  YYMMDD Who RSM# Changes
# ----- ------ --- ---- -------------------------------------------------------
# 1.0   030317 kan 2502 H. Breidenbach original author. Modified to allow
#                        functionality from within Tasking Makefile
# 2.0   030424 hdb 2608 Rescale SfSHPT_a_CurrentGradeAccelRaw to % instead
#                        of M/s/s.
# 2.1   030908 hdb 3110 Undo rescale of SfSHPT_a_CurrentGradeAccelRaw
# 3.0   030919  pd 1326 Removed the section dealing with ETC and ETR
#                        calibrations.
#
###############################################################################
#
# Current Module Info:
# %full_name:      mt20u2#4/perl/a2l_hand_edit.pl/1 %
# %date_created:   Wed Nov 28 09:53:07 2007 %
# %version:        1 %
# %derived_by:     wzmkk7 %
#
###############################################################################



if(! $ARGV[0]) {
   print "Usage : a2l_hand_edit.pl  <filename>  \n";
   print "           output is STDOUT\n";
   exit;
   }

#**************************************************************
#  Pull in the arguments from the invocation request and put  *
#  them into variables                                        *
#**************************************************************

$fname=$ARGV[0];               # get file name
$wname = "mod_${fname}";

open(REL,$fname) || die "Can't open infile $fname !\n";


$started_grade = FALSE;

while(<REL>) {

    $line = $_;
    chop $line;

    if ( $suppress_one_line eq TRUE )
    {
        $suppress_one_line = FALSE;
    }
    elsif ( $suppress_print ne TRUE )
    {
        print STDOUT $line . "\n";
    }
}
close (REL);

exit;


#######################################################
#
#  end of main code.
#
#######################################################


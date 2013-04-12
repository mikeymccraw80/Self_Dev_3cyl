# Application File
# What the script does -->
# Feed a STAR 12 MAP file and get all the information about various sections
# of RAM/ROM with details about every module.
# How to Run - On command prompt, invoke this with the map file name and redirect
# the output to any other file. The output is tab delimited so it looks good
# in an excel file.
#
# Priyadarshi
@MAP_ORIG = (<>); #Take the map file as input
print "MODULE\tTEXT\tCONST\tSHARED_CAL\tBSS\tiRAM\tNVRAM\tRAM_CAN\tEEPROM_START\tEEPROM_APPL\tVECTOR\tRAM_BOOT\tDEBUG\n";
while ($line <= $#MAP_ORIG) #Process entire file
{
   if( ($MAP_ORIG[$line] =~ /\.o\:/) && ($MAP_ORIG[$line+1] =~ /^start.*length.*/) ) #Match the section which contains memory information about modules
   {
      $text = $const = $SHARED_CAL = $bss = $iRAM = $nvram = 0;
      $ram_can = $eeprom_start = $eeprom_appl = $vector = $ram_boot = $debug = 0; #Initialize for each module
      chomp($fname = $MAP_ORIG[$line]); #Get module name
      $line++;
      while (!($MAP_ORIG[$line] =~ /^\n/)) #Module specific info ends here
      {
         $temp = $MAP_ORIG[$line]; # Get the section size "length" data - START
         $_ = $temp;
         s/start.*length//;
         s/section.*//;
         chomp;
         $temp = $_;               # Get the section size "length" data - END
         # Assign the captured size to relevant section
         if($MAP_ORIG[$line] =~ /\.text/)
         {
            $text = $temp;
         }
         elsif($MAP_ORIG[$line] =~ /\.const/)
         {
            $const = $temp;
         }
         elsif($MAP_ORIG[$line] =~ /\.SHARED_CAL/)
         {
            $SHARED_CAL = $temp
         }
         elsif($MAP_ORIG[$line] =~ /\.bss/)
         {
            $bss = $temp;
         }
         elsif($MAP_ORIG[$line] =~ /\.iRAM/)
         {
            $iRAM = $temp;
         }
         elsif($MAP_ORIG[$line] =~ /\.nvram/)
         {
            $nvram = $temp;
         }
         elsif($MAP_ORIG[$line] =~ /\.ram_can/)
         {
            $ram_can = $temp;
         }
         elsif($MAP_ORIG[$line] =~ /\.eeprom_start/)
         {
            $eeprom_start = $temp;
         }
         elsif($MAP_ORIG[$line] =~ /\.eeprom_appl/)
         {
            $eeprom_appl = $temp;
         }
         elsif($MAP_ORIG[$line] =~ /\.vector/)
         {
            $vector = $temp;
         }
         elsif($MAP_ORIG[$line] =~ /\.ram_boot/)
         {
            $ram_boot = $temp;
         }
         elsif($MAP_ORIG[$line] =~ /\.debug/)
         {
            $debug = $temp;
         }
         else
         {
            print "Unidentified section , please check the following line\n";
            print "$MAP_ORIG[$line]\n";
         }
         $line++;
      } #end while - #Module specific info ends here
      print "$fname\t$text\t$const\t$SHARED_CAL\t$bss\t$iRAM\t$nvram\t$ram_can\t$eeprom_start\t$eeprom_appl\t$vector\t$ram_boot\t$debug\n";
   } #end if - Match the section which contains memory information about modules
   $line++;
} #end while - Process entire file
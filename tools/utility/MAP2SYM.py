""" Utility to grep out exmap information from mapfile 
    Packed to MAP2SYM.exe using pyinstaller

Change Log:
   2011.12.07 Revision 2.0 : split symbol's name by dot to handle the static variables defined in the function
   2012.08.22 Revision 3.0 : Add optional argv to support exclude file
"""

__author__ = "xu hui(hui.xu2@delphi.com)"
__version__ = "$Revision: 2.0 $"
__date__ = "$Date: 2011/09/05 14:04:19 $"
__copyright__ = ""

import os
import sys
import re

if len(sys.argv) >= 5 and len(sys.argv) <= 6:

   exclude_list = list()

   if len(sys.argv) == 6:
      try:
         exclude_file = file(sys.argv[5],'r')
      except IOError:
         print 'File open error:'
         print sys.argv[5]+'does not exsit'
         sys.exit(0)
      execlude_line = exclude_file.readlines()
      exclude_file.close()
      for line in execlude_line:
         exclude_list.append(line.split('.')[0])

   try:
      infile = file(sys.argv[1],'r')
   except IOError:
      print 'File open error:'
      print sys.argv[1]+'does not exsit'
      sys.exit(0)
   all_lines = infile.readlines()
   infile.close()
   for line in all_lines:
      if bool(re.match('.*Link Editor Memory Map.*',line)):
         sec_s_idx = all_lines.index(line)
      if bool(re.match('.*Link editor command file symbols.*',line)):
         sec_e_idx = all_lines.index(line)

   process_lines = all_lines[sec_s_idx:sec_e_idx]

   MapTagList = list()
   s_module = False
   ModuleName = str() 


   for line in process_lines:
      if bool(re.match('^\s+\.(?!debug)',line)):
         s_module = True
         ModuleName  = os.path.split(line.split()[-1])[-1].split('.')[0]
         continue
      if bool(re.match('^\s$',line)):
         s_module = False
      if s_module == True:
         MapTag = dict()
         MapTag['Module'] = ModuleName 
         MapTag['Address'] = line.split()[1]
         MapTag['Name'] = (line.split()[0]).split('.')[0]
         MapTagList.append(MapTag)
 
   outfile = file(sys.argv[2],'w')
   for li in MapTagList:
      if long(li['Address'],16) >= long(sys.argv[3],16):
         if long(li['Address'],16) <= long(sys.argv[4],16):
            continue_flg = 0
            for exclude in exclude_list:
               if exclude == li['Module']:
                  continue_flg = 1
                  break
            if continue_flg == 1:
               continue_flg = 0
               continue
            outfile.write(li['Address']+' '+li['Module']+'.'+li['Name']+'\n')
   outfile.close()

else:
   print 'Usage:<command> in_mapfile out_mapfile start_address end_address [exclude]'


import os
import sys
import shutil 

if __name__ == "__main__":
	if os.path.exists(r'soh_cfg.txt') == True:
		soh_cfg_file = open("soh_cfg.txt", "r")
		line = soh_cfg_file.readline()
		if sys.argv[1] in line:
			print sys.argv[1]
			print "same soh config as previous"
			soh_cfg_file.close()
		else:
			print sys.argv[1]
			try :
				# os.rmdir("..\\objs")
				shutil.rmtree("..\\objs")
			except:
				print "objs dir is clean, because objs is not existed"
			soh_cfg_file.close()
			soh_cfg_file = open("soh_cfg.txt", "w+") #clear the file
			soh_cfg_file.write(sys.argv[1])
			soh_cfg_file.close()
			print "different soh config from previous"
	else:
		print "soh cfg file error, delete all obj files"
		try :
			# os.rmdir("..\\objs")
			shutil.rmtree("..\\objs")
		except:
			print "objs dir is clean, because objs is not existed"
		soh_cfg_file = open("soh_cfg.txt", "w+")
		soh_cfg_file.write(sys.argv[1])
		soh_cfg_file.close()

	sys.exit()

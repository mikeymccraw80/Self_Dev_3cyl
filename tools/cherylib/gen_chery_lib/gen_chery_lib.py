import os
import sys
import os.path

def gen_objs_lib():
	bat_file = file("gen_chery_lib.bat", "w")
	bat_file.write("..\\tools\\diab\\WIN32\\bin\\dar -r .\\chery_hls_lib.a ")
	rootdir = ".\\"
	for parent, dirnames, filenames in os.walk(rootdir):
		for filename in filenames:
			if os.path.splitext(filename)[1] != '.o':
				continue
			name = os.path.join(parent, filename)
			if name.find("gen_chery_lib") >= 0:
				continue
			obj_str = name + " "
			print obj_str
			bat_file.write(obj_str)

	bat_file.close()
if __name__ == "__main__":
	gen_objs_lib()
	sys.exit()
import os
import sys

def gen_objs_lib():
	objs_file = file("obj_list.txt", "r")
	bat_file = file("get_lib.bat", "w")
	bat_file.write("md ..\\tools\\delphilib\\outputlib \n")
	bat_file.write("..\\tools\\diab\\WIN32\\bin\\dar -r ..\\tools\\delphilib\\outputlib\\mt22p3_chery_4cyl.a ")
	while True:
		line = objs_file.readline()
		if "app_main.o" in line:
			continue
		if "intr_var.o" in line:
			continue
		if len(line) <= 2:
			break
		# print line
		obj_str = line[0:len(line)-2] + " "
		print obj_str
		bat_file.write(obj_str)
	objs_file.close()
	bat_file.close()
if __name__ == "__main__":
	gen_objs_lib()
	sys.exit()
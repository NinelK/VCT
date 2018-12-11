import os

def parse(strs):
	P = strs[1].split(".txt")
	Ebond = float(strs[0][1:])
	PRC = float(P[0][1:])
	return Ebond, PRC

def rename_30(old_name):
	parts = old_name.split("_")
	return "result_combined30_%s_%s" % (parts[-2],parts[-1])

def rename_10(old_name):
	parts = old_name.split("_")
	return "result_alone10_%s_%s" % (parts[-2],parts[-1])

files = os.listdir("./res_oven2/")

data_new = {}
for file in files: 
	if file.endswith(".txt"):
		with open("./res_oven2/"+file,"r") as f:
			s = f.readlines()
			if file.split("_")[1] == "all1020":
				Ebond, PRC = parse(file.split("_")[2:])
				data_new.update({"%.1f_%.2f" % (Ebond, PRC):s[1]})

files = os.listdir(".")

for file in files: 
	if file.endswith(".txt"):
		with open(file,"r") as f:
			s = f.readlines()
			if file.split("_")[1] == "all":	
				Ebond, PRC = parse(file.split("_")[2:])
				if ("%.1f_%.2f" % (Ebond, PRC) in data_new.keys()):
					with open(rename_30(file),"w") as fw:
						fw.write(s[0])
						fw.write(s[1]+data_new["%.1f_%.2f" % (Ebond, PRC)])
				else:
					with open(rename_10(file),"w") as fw:
						fw.write(s[0])
						fw.write(s[1])


#print data_new
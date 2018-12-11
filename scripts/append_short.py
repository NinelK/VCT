import os

def parse(strs):
	P = strs[1].split(".txt")
	Ebond = float(strs[0][1:])
	PRC = float(P[0][1:])
	return Ebond, PRC

def rename(old_name):
	return "result_all_"+old_name+".txt"

files = os.listdir("./res_long_erode1/")

data = {}
for file in files: 
	if file.endswith(".txt"):
		with open("./res_long_erode1/"+file,"r") as f:
			s = f.readlines()
			#if file.split("_")[1] == "0":
			Ebond, PRC = parse(file.split("_")[2:])
			if ("E%.1f_P%.2f" % (Ebond, PRC) in data.keys()):
				data["E%.1f_P%.2f" % (Ebond, PRC)] = s[1] + data["E%.1f_P%.2f" % (Ebond, PRC)]
			else:
				data.update({"E%.1f_P%.2f" % (Ebond, PRC):s[1]})

print s[0]

for k,v in zip(data.keys(),data.values()):
	with open(rename(k),"w") as f:
		f.write(s[0])
		f.write(v)

# for file in files: 
# 	if file.endswith(".txt"):
# 		with open(file,"r") as f:
# 			s = f.readlines()
# 			if file.split("_")[1] == "all":	
# 				Ebond, PRC = parse(file.split("_")[2:])
# 				if ("%.1f_%.2f" % (Ebond, PRC) in data_new.keys()):
# 					with open(rename_30(file),"w") as fw:
# 						fw.write(s[0])
# 						fw.write(s[1]+data_new["%.1f_%.2f" % (Ebond, PRC)])
# 				else:
# 					with open(rename_10(file),"w") as fw:
# 						fw.write(s[0])
# 						fw.write(s[1])


#print data_new
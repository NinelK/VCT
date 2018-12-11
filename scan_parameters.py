import subprocess

def frange(x, y, jump):
  while x <= y:
    yield x
    x += jump

#E_bond = 5.0
#PRC = 0.60

for E_bond in [5.0,2.5]:
	for PRC in [0.78]:
		subprocess.call(["python","check_connectivity.py","%.1f" % E_bond,"%.2f" % PRC,"%d" % 0])
		subprocess.call(["python","check_connectivity.py","%.1f" % E_bond,"%.2f" % PRC,"%d" % 20])

for E_bond in [1.0]:
	for PRC in frange(0.60,0.789,0.03):
		subprocess.call(["python","check_connectivity.py","%.1f" % E_bond,"%.2f" % PRC,"%d" % 0])
for E_bond in [1.0]:
	for PRC in frange(0.60,0.789,0.03):
		subprocess.call(["python","check_connectivity.py","%.1f" % E_bond,"%.2f" % PRC,"%d" % 20])

#for E_bond in [5.0,2.5,7.5,0.0,10.0]:
#	for PRC in frange(0.60,0.759,0.03):
#		subprocess.call(["python","check_connectivity.py","%.1f" % E_bond,"%.2f" % PRC,"%d" % 0])
#
#for E_bond in [5.0,2.5,7.5,0.0,10.0]:
#	for PRC in frange(0.60,0.759,0.03):
#		subprocess.call(["python","check_connectivity.py","%.1f" % E_bond,"%.2f" % PRC,"%d" % 20])

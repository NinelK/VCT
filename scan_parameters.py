import subprocess

def frange(x, y, jump):
  while x <= y:
    yield x
    x += jump

#E_bond = 5.0
#PRC = 0.60

for E_bond in range(10):
	for PRC in frange(0.65,0.709,0.01):
		subprocess.call(["python","check_connectivity.py","%.1f" % E_bond,"%.2f" % PRC,"%d" % 30])

for E_bond in range(10):
	for PRC in frange(0.65,0.709,0.01):
		subprocess.call(["python","check_connectivity.py","%.1f" % E_bond,"%.2f" % PRC,"%d" % 50])

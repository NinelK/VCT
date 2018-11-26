import subprocess

def frange(x, y, jump):
  while x <= y:
    yield x
    x += jump

#E_bond = 5.0
#PRC = 0.60

for E_bond in frange(0.0,10.0,1.0):
	for PRC in frange(0.60,0.75,0.01):
		subprocess.call(["python","check_connectivity.py","%.1f" % E_bond,"%.2f" % PRC])
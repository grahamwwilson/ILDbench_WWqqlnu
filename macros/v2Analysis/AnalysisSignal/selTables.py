import sys
from operator import add 
import math

def efferr(num,den):
	eff = num/den
	n = den
	return math.sqrt( eff*(1-eff)/ n ) 
		
def eff(num,den):
	return num/den

ifilename = sys.argv[1]
ifile =  open(ifilename,"r")

#establish cut flow
CUT = []
lines = ifile.readlines()
for line in lines:
	line = line.split()
	if(line[0] == '*'):
		if(line[2] =='cut'):
			CUT = line[3:]
			break

print CUT
ifile.close()
ifile = open(ifilename,"r")

list2f = ['BHAg','ZHAD', 'ZL']
list4f = ['WL','ZEEL','ZNUL', 'ZNUS', 'WWHAD','WWL','ZZHAD','ZZL','ZZS', 'ZWML', 'ZZWWH', 'ZZWWL']
list6f = ['EEWW', 'LLWW', 'TTB', 'VVWW','XXWW', 'XXZ', 'YYZ']
listH = ['EEH', 'MUH', 'TAUH', 'QQH', 'NNH']
listS = ['WS', 'WWS']

count2f = [0.] * len(CUT)
count4f = [0.] * len(CUT)
count6f = [0.] * len(CUT)
countH = [0.] * len(CUT)
countS = [0.] * len(CUT)


#parse file for wildcard
lines = ifile.readlines()
for line in lines:
	line = line.split()
	if(line[0] == '*'):
		#print line
		if(line[2] == 'tot'):
			counts = map(float, line[3:])
			#seprate tags
			tag = line[1]
			if tag in list2f:
				count2f = list(map(add,count2f,counts))
			if tag in list4f:
				count4f = list(map(add,count4f,counts))
			if tag in list6f:
				count6f = list(map(add,count6f,counts))
			if tag in listH:
				countH = list(map(add,countH,counts))
			if tag in listS:
				countS = list(map(add,countS,counts))	

print count2f
print count4f
print count6f
print countH
print countS

samp = ['Signal','2f','4f','6f','Higgs']
ofilename = sys.argv[2]
ofile = open(ofilename,"w")
ofile.write(" \\begin{tabular}{");
for col in xrange(len(samp)+1):
	ofile.write("|p{0.12\\textwidth}|");
ofile.write("}\n")
ofile.write("\\hline \n   & ")
for i in xrange(len(samp)):
	if i == len(samp)-1 :
		ofile.write(samp[i] + " \\\\ ")
	else:
		ofile.write(samp[i]+ " & ")
	
ofile.write("\\hline \n")
for i in xrange(len(CUT)):

	#ofile.write( CUT[i] +" & "+str(countS[i])+" & "+str(count2f[i])+" & "+str(count4f[i])+ " & " +str(count6f[i])+ " & "+str(countH[i]) + " \\\\ \n")
	ofile.write(CUT[i]+" &\\num{"+"{:.2e}".format(countS[i])+"} & \\num{"+ "{:.2e}".format(count2f[i]) +"} & \\num{"+"{:.2e}".format(count4f[i])+"} & \\num{"+ "{:.2e}".format(count6f[i])+"} & \\num{"+"{:.2e}".format(countH[i]) + "} \\\\ \n")
	ofile.write("\\hline \n")

ofile.write(" \epsilon & ${:.4g} \\pm {:.2g}$ & ${:.4g} \\pm {:.2g}$ & ${:.4g} \\pm {:.2g}$ & ${:.4g} \\pm {:.2g}$ & ${:.4g} \\pm {:.2g} \\\\ \n".format(eff(countS[-1],countS[0]), efferr(countS[-1],countS[0]), eff(count2f[-1],count2f[0]), efferr(count2f[-1],count2f[0]), eff(count4f[-1],count4f[0]), efferr(count4f[-1],count4f[0]), eff(count6f[-1],count6f[0]), efferr(count6f[-1],count6f[0]), eff(countH[-1],countH[0]), efferr(countH[-1],countH[0])))



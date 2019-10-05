import sys
import os
import subprocess

#input file list

datalistname = str(sys.argv[3]);
idatalist = open(datalistname, "r")

idatafiles = [f.rstrip() for f in idatalist if ".root" in f ]
print(idatafiles)

numFiles = int(sys.argv[1]) 
ifile = 1 #file counter

nthreads = sys.argv[2]

treename = str(sys.argv[4])
filetag = str(sys.argv[5])
ofilename = str(sys.argv[6])
ofileopt = str(sys.argv[7])
#lum = str(sys.argv[8]);
pem = str(sys.argv[8]);
pep = str(sys.argv[9]);
lumi = str(sys.argv[10]);

if (numFiles == 0 ):
	numFiles = len(idatafiles)
print( "from runmacro numFiles == ", numFiles," nthreads == ",nthreads)
cmd = "./compiledthreads "+str(nthreads)+" "+treename+" "+filetag+" "+ofilename+" "+ofileopt+" "+pem+" "+pep+" "+lumi+" "
 
for f in idatafiles:
	if (ifile <= numFiles):
		pathsplit = f.split("/")
		namesplit = pathsplit[-1].split(".")
		tag = namesplit[0]
	
		cmd = cmd + "\""+f+"\" "
	ifile = ifile + 1

print cmd
os.system(cmd)	

import sys

ifile = sys.argv[1]
f = open(ifile,"r")
#print ifile
manifest = open("cutsequence0manifest.list", "a")

lines = f.readlines()
#print lines
#print "hi"
#print lines[-1]
newline = lines[-1].split()

manifest.write("$ "+newline[1]+" value \n")


import sys
import subprocess

def bash( bashCommand ):
        process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
        #process = subprocess.Popen(bashCommand.split())
        output, error = process.communicate()
	print output
        return output ,error





#arg 1 = sequence-i file

#location of analysis code
PATH1 = "/afs/desy.de/user/a/anguiano/work/repos/ILDbench_WWqqlnu/macros/v2Analysis/CutOpt/Analysis/"
MYPATH = "/afs/desy.de/user/a/anguiano/work/repos/ILDbench_WWqqlnu/macros/v2Analysis/CutOpt/SequenceOpt/"


sequencefilename = sys.argv[1]


seqfile = open(sequencefilename,"r")

#read and store all cuts (unoptimized)

lines = seqfile.readlines()
cutsequence = []

for line in lines:
	cutsequence.append( line.split() )

seqfile.close()
#print cutsequence

#create a new empty cut manifest
manifestname = sequencefilename[:-5]+"manifest.list"
manifestfile = open(manifestname,"w")
manifestfile.write("")
manifestfile.close()

cutnum = 0
#produce a cutlist for histset
for cuts in cutsequence:
	
	cutfilename = sequencefilename[:-5]
	cutfilename = cutfilename+"cut"+str(cutnum)+".cutlist"

	print cutfilename
	#make a cut file
	cutfile = open(cutfilename, "w")
	#write the current manifest to cutfile
	manifest = open(manifestname,"r")
	mlines = manifest.readlines()
	#write all lines from manifest, the ith cuts will be written after manifest
	cutfile.writelines(mlines)
	cutfile.write(lines[cutnum])
	cutfile.close()	
	
	#the cutfile is now defined do optimization
	#something will write new lines to the manifest
	#actuall call something that does work
	bash("python tempmanifest.py "+cutfilename)	
	cmd = "./../Analysis/runmyanalysis.sh TIGHT "+MYPATH+cutfilename+" ./testOfile/"+cutfilename[:-8]+".root"
	print cmd
	bash(cmd )
	


	cutnum= cutnum+1

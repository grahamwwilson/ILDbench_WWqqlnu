

import subprocess 


DATASET = '4f_WW_semi_LR'


def bash( bashCommand ):
	process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
	#process = subprocess.Popen(bashCommand.split())
	output, error = process.communicate()
	return output ,error

bashCommand ='ls ./steeringMacros/TauFinderSteeringS1LR/' 
OUTPUT = bash( bashCommand ) #get name of all xml Files
DATASETLIST = OUTPUT[0].split('\n')
print DATASETLIST
#loop over each file and run in marlin, print which file we are running too
for DATASET in DATASETLIST:
	if DATASET == '': continue
	print "Starting Run "+ DATASET
	DATASETNAME = DATASET[:-4]
	#print DATASETNAME
	bash('rm /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RunLogs/'+DATASETNAME+'.out.gz')
	bash('Marlin ./steeringMacros/TauFinderSteeringS1LR/'+DATASET+' > /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RunLogs/'+DATASETNAME+'.out')
	bash('gzip /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RunLogs/'+DATASETNAME+'.out')
	bash('mv /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RootFiles/file.root /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RootFiles/'+DATASETNAME+'.root')
	break



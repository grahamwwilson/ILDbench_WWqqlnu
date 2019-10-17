

import subprocess 

#SUBSET = 'S1'
SUBSET = 'S2'
#SUBSET = 'B1'

def bash( bashCommand ):
	process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
	#process = subprocess.Popen(bashCommand.split())
	output, error = process.communicate()
	return output ,error

#bashCommand ='ls ./steeringMacros/TauFinderSteeringS1LR/' 
bashCommand = 'ls ./steeringMacros/TauFinderSteeringS2LR/'
#bashCommand = 'ls ./steeringMacros/TauFinderSteeringB1LR/'

#path = './steeringMacros/TauFinderSteeringS1LR/'
path = './steeringMacros/TauFinderSteeringS2LR/'
#path = './steeringMacros/TauFinderSteeringB1LR/'

OUTPUT = bash( bashCommand ) #get name of all xml Files
DATASETLIST = OUTPUT[0].split('\n')
print DATASETLIST
#loop over each file and run in marlin, print which file we are running too
for DATASET in DATASETLIST:
	if DATASET == '': continue
	print "Starting Run "+ DATASET
	DATASETNAME = DATASET[:-4]
	DATASETNAME = DATASETNAME+SUBSET
	print DATASETNAME
	bash('rm /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RunLogs/'+DATASETNAME+'.out.gz')
	#bash('Marlin ./steeringMacros/TauFinderSteeringS1LR/'+DATASET+' > /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RunLogs/'+DATASETNAME+'.out')
	#log = bash('Marlin ./steeringMacros/TauFinderSteeringS1LR/'+DATASET)
	log = bash('Marlin '+path+DATASET)
	file = open('/nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RunLogs/'+DATASETNAME+'.out','w')
	file.write(log[0])
	bash('gzip /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RunLogs/'+DATASETNAME+'.out')
	bash('mv /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RootFiles/file.root /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RootFiles/'+DATASETNAME+'.root')
	



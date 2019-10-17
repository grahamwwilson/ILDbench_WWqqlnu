import subprocess

def bash( bashCommand ):
        process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
        #process = subprocess.Popen(bashCommand.split())
        output, error = process.communicate()
        return output ,error


#[ path , subset ]
args = ["./steeringMacros/wwv2Steering/", "S1" ]
#args = ["./steeringMacros/qqRemainSteering/qqJetSteeringS2LR/", "S2" ]
#args = ["./steeringMacros/qqRemainSteering/qqJetSteeringB1LR/", "B1" ]

path = args[0]

#get the list of xml files
OUTPUT = bash( "ls "+path )
DATASETLIST =  OUTPUT[0].split('\n')
print DATASETLIST


SUBSET = args[1]

for DATASET in DATASETLIST:
        if DATASET == '': continue
        print "Starting Run "+ DATASET
        DATASETNAME = DATASET[:-4]
        DATASETNAME = DATASETNAME+SUBSET
        print DATASETNAME
        bash('rm /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/v2files/RunLogs/'+DATASETNAME+'.out.gz')
        #bash('Marlin ./steeringMacros/TauFinderSteeringS1LR/'+DATASET+' > /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RunLogs/'+DATASETNAME+'.out')
        #log = bash('Marlin ./steeringMacros/TauFinderSteeringS1LR/'+DATASET)
        log = bash('Marlin '+path+DATASET)
        file = open('/nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/v2files/RunLogs/'+DATASETNAME+'.out','w')
        file.write(log[0])
        bash('gzip /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/v2files/RunLogs/'+DATASETNAME+'.out')
        bash('mv /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/v2files/RootFiles/file.root /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/v2files/RootFiles/'+DATASETNAME+'.root')


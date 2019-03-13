

DATASET=TauFinder22


#remove the output log otherwise it will not overwrite
rm /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RunLogs/${DATASET}.out.gz

Marlin ./steeringMacros/TauFinderSteeringB1LR/${DATASET}.xml > /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RunLogs/${DATASET}.out

gzip /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RunLogs/${DATASET}.out

#mv ${DATASET}.out.gz /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RunLogs
mv /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RootFiles/file.root /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RootFiles/${DATASET}TEST.root

#slcio tends to be really big so normally just overwrite it
#mv jets.slcio /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/slcioFiles/${DATASET}_jets.slcio
#mv jets.slcio /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/slcioFiles/




#set analysis dataset variablei
#just uncomment the one to be run
#DATASET=4f_WW_semi_LR
DATASET=4f_WW_semi_RL
#DATASET=2f_Z_had_LR
#DATASET=4f_WW_had_LR
#DATASET=4f_ZZ_semi_LR

#remove the output log otherwise it will not overwrite
rm /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/RunLogs/${DATASET}.out.gz

Marlin ./steering/${DATASET}.xml > ${DATASET}.out

gzip ${DATASET}.out

mv ${DATASET}.out.gz /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/RunLogs
mv file.root /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/RootFiles/${DATASET}.root

#slcio tends to be really big so normally just overwrite it
#mv jets.slcio /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/slcioFiles/${DATASET}_jets.slcio
mv jets.slcio /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/slcioFiles/


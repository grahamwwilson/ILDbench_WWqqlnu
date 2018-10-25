


#set analysis dataset variablei
#just uncomment the one to be run
DATASET=4f_WW_semi_LR
#DATASET=2f_Z_had_LR
#DATASET=4f_WW_had_LR
#DATASET=4f_ZZ_semi_LR

#remove the output log otherwise it will not overwrite
rm /afs/desy.de/group/flc/pool/anguiano/WWFiles/${DATASET}.out.gz

Marlin ./steering/${DATASET}.xml > ${DATASET}.out

gzip ${DATASET}.out

mv ${DATASET}.out.gz /afs/desy.de/group/flc/pool/anguiano/WWFiles/
mv file.root /afs/desy.de/group/flc/pool/anguiano/WWFiles/${DATASET}.root
mv jets.slcio /afs/desy.de/group/flc/pool/anguiano/WWFiles/${DATASET}_jets.slcio

 

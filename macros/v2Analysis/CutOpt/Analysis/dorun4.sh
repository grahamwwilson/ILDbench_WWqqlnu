./runmyanalysis4.sh > run4.log
./runmyanalysis4T.sh > run4T.log

cd ../AnalysisSignal

./runmyanalysis4.sh > run4S.log
./runmyanalysis4T.sh > run4ST.log

cd ../Analysis

python selTables.py run4.log ../AnalysisSignal/run4S.log run4.table
python selTables.py run4T.log ../AnalysisSignal/run4ST.log run4T.table


#some other macro to print summary?
python summarizerun.py run4.table run4T.table summary4.out

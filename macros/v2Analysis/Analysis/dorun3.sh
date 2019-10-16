./runmyanalysis3.sh > run3.log
./runmyanalysis3T.sh > run3T.log

cd ../AnalysisSignal

./runmyanalysis3.sh > run3S.log
./runmyanalysis3T.sh > run3ST.log

cd ../Analysis

python selTables.py run3.log ../AnalysisSignal/run3S.log run3.table
python selTables.py run3T.log ../AnalysisSignal/run3ST.log run3T.table


#some other macro to print summary?
python summarizerun.py run3.table run3T.table summary3.out

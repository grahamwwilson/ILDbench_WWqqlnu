./runmyanalysis2.sh > run2.log
./runmyanalysis2T.sh > run2T.log

cd ../AnalysisSignal

./runmyanalysis2.sh > run2S.log
./runmyanalysis2T.sh > run2ST.log

cd ../Analysis

python selTables.py run2.log ../AnalysisSignal/run2S.log run2.table
python selTables.py run2T.log ../AnalysisSignal/run2ST.log run2T.table


#some other macro to print summary?
python summarizerun.py run2.table run2T.table summary2.out

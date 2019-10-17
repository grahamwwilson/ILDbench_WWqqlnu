./runmyanalysis.sh > run1.log
./runmyanalysisT.sh > run1T.log

cd ../AnalysisSignal

./runmyanalysis.sh > run1S.log
./runmyanalysisT.sh > run1ST.log

cd ../Analysis

python selTables.py run1.log ../AnalysisSignal/run1S.log run1.table
python selTables.py run1T.log ../AnalysisSignal/run1ST.log run1T.table


#some other macro to print summary?
python summarizerun.py run1.table run1T.table summary1.out

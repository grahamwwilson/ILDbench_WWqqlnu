

#input is: num files, numthreads,  yourdata.list, Treename, DataTag (A unique identifier for a specific dataset), outputfile name, outputfile option
#0 is all files, optimal threads is 8 at t3.unl

# last three inputs are Pe- Pe+ and luminosity fb-1 for (Pe-,Pe+) scenario
python runmacro.py 0 8 "datalists/4f_singleW_semileptonic.list" "tree" "WS1" "eventSelSTau.root" "RECREATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/4f_singleW_semileptonic.list" "tree" "WSBG" "eventSelSTau.root" "UPDATE" "-0.8" "0.3" "1600"


python runmacro.py 0 8 "datalists/4f_WW_semileptonic.list" "tree" "WWS1" "eventSelSTau.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/4f_WW_semileptonic.list" "tree" "WWS2" "eventSelSTau.root" "UPDATE" "-0.8" "0.3" "1600"

python runmacro.py 0 8 "datalists/4f_WW_semileptonic.list" "tree" "WWS1BG" "eventSelSTau.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/4f_WW_semileptonic.list" "tree" "WWS2BG" "eventSelSTau.root" "UPDATE" "-0.8" "0.3" "1600"













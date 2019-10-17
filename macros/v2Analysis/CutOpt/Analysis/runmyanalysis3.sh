

#input is: num files, numthreads,  yourdata.list, Treename, DataTag (A unique identifier for a specific dataset), outputfile name, outputfile option
#0 is all files, optimal threads is 8 at t3.unl

# last three inputs are Pe- Pe+ and luminosity fb-1 for (Pe-,Pe+) scenario
#python runmacro.py 0 8 "datalists/DYJetsToLL_HT.list" "KUAnalysis" "DY" "susyHists.root" "RECREATE"
#python runmacro.py 0 8 "datalists/WJetsToLNu_HT.list" "KUAnalysis" "WJET" "susyHists.root" "UPDATE"
#python runmacro.py 0 8 "datalists/QCD_HT.list" "KUAnalysis" "QCD" "susyHists.root" "UPDATE"
#python runmacro.py 0 8 "datalists/TTJets_HT.list" "KUAnalysis" "TTJ" "susyHists.root" "UPDATE"
#python runmacro.py 0 8 "datalists/ZJetsToNuNu_HT.list" "KUAnalysis" "ZNUNU" "susyHists.root" "UPDATE"
#python runmacro.py 0 8 "datalists/SMS_TChiWZ_ZToLL.list" "SMS_300_75" "WZ_300_75" "susyHists.root" "UPDATE"
#python runmacro.py 0 8 "datalists/SMS_TChiWZ_ZToLL.list" "SMS_175_135" "WZ_175_135" "susyHists.root" "UPDATE"

#pol scenrio 2
python runmacro.py 0 8 "datalists/2f_Z_bhabhag.list" "tree" "BHAg" "eventSel2.root" "RECREATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/2f_Z_hadronic.list" "tree" "ZHAD" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/2f_Z_leptonic.list" "tree" "ZL" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/4f_singleW_leptonic.list" "tree" "WL" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/4f_singleW_semileptonic.list" "tree" "WS" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/4f_singleZee_leptonic.list" "tree" "ZEEL" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/4f_singleZee_semileptonic.list" "tree" "ZEES" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/4f_singleZnunu_leptonic.list" "tree" "ZNUL" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/4f_singleZnunu_semileptonic.list" "tree" "ZNUS" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/4f_WW_hadronic.list" "tree" "WWHAD" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"

python runmacro.py 0 8 "datalists/4f_WW_leptonic.list" "tree" "WWL" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/4f_WW_semileptonic.list" "tree" "WWS" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/4f_ZZ_hadronic.list" "tree" "ZZHAD" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/4f_ZZ_leptonic.list" "tree" "ZZL" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/4f_ZZ_semileptonic.list" "tree" "ZZS" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"

python runmacro.py 0 8 "datalists/eeH.list" "tree" "EEH" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/mumuH.list" "tree" "MUH" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/tautauH.list" "tree" "TAUH" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/qqH.list" "tree" "QQH" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/nunuH.list" "tree" "NNH" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"

python runmacro.py 0 8 "datalists/4f_singleZsingleWMix_leptonic.list" "tree" "ZWML" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/4f_ZZWWMix_hadronic.list" "tree" "ZZWWH" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/4f_ZZWWMix_leptonic.list" "tree" "ZZWWL" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/6f_eeWW.list" "tree" "EEWW" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/6f_llWW.list" "tree" "LLWW" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/6f_ttbar.list" "tree" "TTB" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/6f_vvWW.list" "tree" "VVWW" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/6f_xxWW.list" "tree" "XXWW" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/6f_xxxxZ.list" "tree" "XXZ" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"
python runmacro.py 0 8 "datalists/6f_yyyyZ.list" "tree" "YYZ" "eventSel2.root" "UPDATE" "-0.8" "-0.3" "400"

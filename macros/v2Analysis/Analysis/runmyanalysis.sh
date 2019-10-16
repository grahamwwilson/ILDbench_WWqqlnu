

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

python runmacro.py 0 8 "datalists/2f_Z_bhabhag.list" "tree" "BHAg" "eventSel.root" "RECREATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/2f_Z_hadronic.list" "tree" "ZHAD" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/2f_Z_leptonic.list" "tree" "ZL" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/4f_singleW_leptonic.list" "tree" "WL" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/4f_singleW_semileptonic.list" "tree" "WS" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/4f_singleZee_leptonic.list" "tree" "ZEEL" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/4f_singleZee_semileptonic.list" "tree" "ZEES" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/4f_singleZnunu_leptonic.list" "tree" "ZNUL" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/4f_singleZnunu_semileptonic.list" "tree" "ZNUS" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/4f_WW_hadronic.list" "tree" "WWHAD" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"

python runmacro.py 0 8 "datalists/4f_WW_leptonic.list" "tree" "WWL" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/4f_WW_semileptonic.list" "tree" "WWS" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/4f_ZZ_hadronic.list" "tree" "ZZHAD" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/4f_ZZ_leptonic.list" "tree" "ZZL" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/4f_ZZ_semileptonic.list" "tree" "ZZS" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"

python runmacro.py 0 8 "datalists/eeH.list" "tree" "EEH" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/mumuH.list" "tree" "MUH" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/tautauH.list" "tree" "TAUH" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/qqH.list" "tree" "QQH" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/nunuH.list" "tree" "NNH" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"

python runmacro.py 0 8 "datalists/4f_singleZsingleWMix_leptonic.list" "tree" "ZWML" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/4f_ZZWWMix_hadronic.list" "tree" "ZZWWH" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/4f_ZZWWMix_leptonic.list" "tree" "ZZWWL" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/6f_eeWW.list" "tree" "EEWW" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/6f_llWW.list" "tree" "LLWW" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/6f_ttbar.list" "tree" "TTB" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/6f_vvWW.list" "tree" "VVWW" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/6f_xxWW.list" "tree" "XXWW" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/6f_xxxxZ.list" "tree" "XXZ" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"
python runmacro.py 0 8 "datalists/6f_yyyyZ.list" "tree" "YYZ" "eventSel.root" "UPDATE" "-0.8" "0.3" "1600"











import numpy as np


import sys

ycuts = [ 1e-3, 5e-3, 1e-4, 5e-4, 1e-5, 5e-5, 1e-6, 5e-6 ] 
#input arguments arg1 = input file list (slcio)
#				 arg2 = output file path (steering files)
#				 arg3 = tau optimization params in a single string split at spaces "searchcone isocone isoE"
#				 arg4 = ouput rootfile tag "S1" "S2" or "B1"

inputFileName = str( sys.argv[1] )
outputPath = str( sys.argv[2] )
tauParameters = str(sys.argv[3]).split()
tag = str(sys.argv[4])
#assume gear file
gearfile = "gear_ILD_l5_v02_dd4hep.xml"
#assume only signal
nlep = 2
nferm = 4

filenum = 1
#totalTrees = 7




for y in ycuts:
	file = open(outputPath+'TauFinder'+str(filenum)+'.xml','w')
	#write to file	
	file.write("<!-- automatically generated steering -->\n")
	file.write("\n ")
	file.write("<marlin>\n")
	file.write("	<execute>\n ")
	file.write("		<processor name= \"MyTauFinder\" />\n" )
	file.write("		<processor name= \"MyTauSelector\" />\n" )
	file.write("		<processor name= \"MyRemainJets\" />\n" )
	file.write("		<processor name= \"MyWWAnalysis\" />\n" )
	file.write("	</execute>\n ")
	file.write("\n")

	file.write("	<global>\n")
	file.write("		<parameter name=\"LCIOInputFiles\"> " +inputFileName+" </parameter>\n")
	file.write("		<parameter name=\"SkipNEvents \" value = \"0\" />\n")
	file.write("		<parameter name=\"MaxRecordNumber\" value = \"0\" />\n")
	file.write("		<parameter name=\"SupressCheck\" value = \"false\" />\n")
	file.write("		<parameter name=\"GearXMLFile\" value = \""+gearfile+"\" />\n")
	file.write("		<parameter name=\"Verbosity\"  options = \"DEBUG0-4,MESSAGE0-4,WARNING0-4,ERROR0-4,SILENT\" > DEBUG </parameter>\n")
	file.write("	</global>\n")
	file.write("\n")

	file.write("	<processor name= \"MyTauFinder\" type=\"TauFinder\" >\n" )
	file.write("		<parameter name=\"PFOCollection\" type=\"string\" lcioInType=\"ReconstructedParticle\"> PandoraPFOs </parameter>\n")
	file.write("		<parameter name=\"TauRecCollection\" type=\"string\" lcioOutType=\"ReconstructedParticle\"> preTauJets </parameter>\n")
	file.write("		<parameter name=\"TauRecRestCollection\" type=\"string\" lcioOutType=\"ReconstructedParticle\"> preRemainPFOs </parameter>\n")
	file.write("		<parameter name=\"TauRecLinkCollectionName\" type=\"string\" lcioOutType=\"LCRelation\"> TauLink </parameter>\n")
	file.write("		<parameter name=\"pt_cut\" value=\"0.2\" />\n")
	file.write("		<parameter name=\"cosT_cut\" value=\"0.99\" />\n")
	file.write("		<parameter name=\"searchConeAngle\" value=\""+tauParameters[0]+"\" />\n")
	file.write("		<parameter name=\"isolationConeAngle\" value=\""+tauParameters[1]+"\" />\n")
	file.write("		<parameter name=\"isolationEnergy\" value=\""+tauParameters[2]+"\" />\n")
	file.write("		<parameter name=\"ptseed\" value=\"5.0\" />\n")
	file.write("		<parameter name=\"invariant_mass\" value=\"2.0\" />\n")
	file.write("	</processor>\n")	
	file.write("\n")
   

	file.write("	<processor name= \"MyTauSelector\" type=\"TauSelector\" >\n" )
	file.write("		<parameter name=\"InputRemainCollectionName\" type=\"string\" lcioInType=\"ReconstructedParticle\"> preRemainPFOs </parameter>\n" )
	file.write("		<parameter name=\"InputTauJetCollectionName\" type=\"string\" lcioInType=\"ReconstructedParticle\"> preTauJets </parameter>\n" )
	file.write("		<parameter name=\"OutputRemainCollectionName\" type=\"string\" lcioOutType=\"ReconstructedParticle\"> RemainPFOs </parameter>\n")
	file.write(" 		<parameter name=\"OutputTauJetCollectionName\" type=\"string\" lcioOutType=\"ReconstructedParticle\"> TauJets </parameter>\n")
	file.write("	</processor>\n")

	file.write("	<processor name=\"MyRemainJets\" type=\"FastJetProcessor\">\n")
	file.write("		<parameter name=\"recParticleIn\" type=\"string\" lcioInType=\"ReconstructedParticle\"> RemainPFOs </parameter>\n" )
	file.write("		<parameter name=\"jetOut\" type=\"string\" lcioOutType=\"ReconstructedParticle\"> RemainJets </parameter>\n" )
	file.write("		<parameter name=\"algorithm\" type=\"StringVec\"> ee_kt_algorithm </parameter>\n")
	file.write("		<parameter name=\"clusteringMode\" type=\"StringVec\"> ExclusiveYCut "+ str(y) +" </parameter> \n ")
	file.write("		<parameter name=\"recombinationScheme\" type=\"string\"> E_scheme </parameter> \n")
	file.write("	</processor>\n") 


	file.write("	<processor name= \"MyWWAnalysis\" type=\"WWAnalysis\">\n")
	file.write("		<parameter name=\"McParticleCollectionName\" value=\"MCParticle\" />\n")
	file.write("		<parameter name=\"InputParticleColletionName\" type=\"string\" lcioInType=\"ReconstructedParticle\"> PandoraPFOs </parameter>\n")
	file.write("		<parameter name=\"InputTrackCollectionName\" value=\"MarlinTrkTracks\" />\n")
	file.write("		<parameter name=\"InputRecoRelationCollectionName\" value=\"RecoMCTruthLink\" />\n")
	file.write("		<parameter name=\"InputJetCollectionsNames\">  TauJets </parameter>\n ")
	file.write("		<parameter name=\"InputRemainCollectionsNames\"> RemainPFOs </parameter>\n ")
  	file.write("		<parameter name=\"InputRemainJetCollectionsNames\"> RemainJets </parameter>\n ")
	file.write("		<parameter name=\"RemainYCut\" value=\""+ str(y) +"\" /> \n")
	file.write("		<parameter name=\"NFermions\" value=\"4\" /> \n")
	file.write("		<parameter name=\"Nleptons\" value=\"2\" /> \n")
	file.write("		<parameter name=\"Normalization\" value=\"0.784017\" /> \n")
	file.write("		<parameter name=\"Xsec\" value=\"9521.45\" /> \n" )
	file.write("		<parameter name=\"XsecError\" value=\"10.6\" /> \n" )
	file.write("		<parameter name=\"Njets\" value=\"3\" />\n " )
	file.write("		<parameter name=\"Ncuts\" value=\"7\" /> \n" )
	file.write("		<parameter name=\"OutPath\" value=\"/afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/WqqJetOptFiles/RootFiles/WqqOptycut"+str(filenum)+tag+"\" /> \n")
	file.write("	</processor> \n")
	file.write("\n")

	file.write("</marlin>\n")
	file.close()
	filenum = filenum+1




import numpy as np

#when running edit inputfile/output path and number of fermions

#3 parameter optimzation, searchcone, iso angle, iso E
#inputFileName = '/pnfs/desy.de/ilc/prod/ilc/mc-opt-3/ild/dst-merged/500-TDR_ws/4f_WW_semileptonic/ILD_l5_o1_v02/v02-00-01/rv02-00-01.sv02-00-01.mILD_l5_o1_v02.E500-TDR_ws.I250018.P4f_ww_sl.eL.pR.n001.d_dstm_10318_0.slcio'
inputFileName = '/pnfs/desy.de/ilc/prod/ilc/mc-opt-3/ild/dst-merged/500-TDR_ws/4f_singleW_semileptonic/ILD_l5_o1_v02/v02-00-01/rv02-00-01.sv02-00-01.mILD_l5_o1_v02.E500-TDR_ws.I250042.P4f_sw_sl.eL.pR.n001.d_dstm_10417_0.slcio'

#inputFileName = '/pnfs/desy.de/ilc/prod/ilc/mc-opt-3/ild/dst-merged/500-TDR_ws/4f_WW_hadronic/ILD_l5_o1_v02/v02-00-01/rv02-00-01.sv02-00-01.mILD_l5_o1_v02.E500-TDR_ws.I250006.P4f_ww_h.eL.pR.n001.d_dstm_10398_0.slcio'

gearfile = "gear_ILD_l5_v02_dd4hep.xml"

#outputPath = './TauFinderSteeringS1LR/'
outputPath = './TauFinderSteeringS2LR/'
#outputPath = './TauFinderSteeringB1LR/'
nlep = 2
nferm = 4
#nlep = 0

searchConeAngleMin = 0.
searchConeAngleMax = 0.16
searchConeAngleStep = 0.01 #10mrad step

isoAngleMin = 0.
isoAngleMax = 0.16
isoAngleStep = 0.01 #10mrad step

isoEnergyMin = 0.
isoEnergyMax = 6.
isoEnergyStep = 0.5 #1gev step

#number of trees per file
nTreesPerFile = 50


#create the parameter sets
coneValues = np.arange(searchConeAngleMin, searchConeAngleMax, searchConeAngleStep)
isoAngleValues = np.arange(isoAngleMin, isoAngleMax, isoAngleStep)
isoEnergyValues = np.arange(isoEnergyMin, isoEnergyMax, isoEnergyStep)

print coneValues
print isoAngleValues
print isoEnergyValues

nbinsCone = len(coneValues)
nbinsIsoCone = len(isoAngleValues)
nbinsIsoE = len(isoEnergyValues)

print nbinsCone
print nbinsIsoCone
print nbinsIsoE

totalTrees = nbinsCone* nbinsIsoCone * nbinsIsoE

print totalTrees



#test
#nTreesPerFile = 2
TreePerFileTracker = nTreesPerFile
treenum = 1
filenum = 1
#totalTrees = 7

cone_itr = 0
angle_itr = 0
ener_itr = 0

file = open(outputPath+'TauFinder'+str(filenum)+'.xml','w')

#write all headers 
while treenum <= totalTrees:

	if 	treenum > TreePerFileTracker:
		file.close()
		filenum = filenum+1
		file = open(outputPath+'TauFinder'+str(filenum)+'.xml','w')
		TreePerFileTracker = TreePerFileTracker + nTreesPerFile
		

	
	#write to file	
	file.write("<!-- automatically generated steering -->\n")
	file.write("\n ")
	file.write("<marlin>\n")
	file.write("	<execute>\n ")
	for i in range( treenum ,TreePerFileTracker+1):
		if i > totalTrees : break
		file.write("		<processor name= \"MyTauFinder"+str(i)+"\" />\n" )
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
	for t in range( treenum, TreePerFileTracker+1):
		if ener_itr == nbinsIsoE:
			angle_itr = angle_itr+1
			ener_itr = 0
		if angle_itr == nbinsIsoCone:
			cone_itr = cone_itr+1
			angle_itr = 0
		if t > totalTrees : break
		file.write("	<processor name= \"MyTauFinder"+str(t)+"\" type=\"TauFinder\" >\n" )
		file.write("		<parameter name=\"PFOCollection\" type=\"string\" lcioInType=\"ReconstructedParticle\"> PandoraPFOs </parameter>\n")
		file.write("		<parameter name=\"TauRecCollection\" type=\"string\" lcioOutType=\"ReconstructedParticle\"> TauJets"+str(t)+" </parameter>\n")
		file.write("		<parameter name=\"TauRecRestCollection\" type=\"string\" lcioOutType=\"ReconstructedParticle\"> RemainPFOs"+str(t)+" </parameter>\n")
		file.write("		<parameter name=\"TauRecLinkCollectionName\" type=\"string\" lcioOutType=\"LCRelation\"> TauLink"+str(t)+" </parameter>\n")
		file.write("		<parameter name=\"pt_cut\" value=\"0.2\" />\n")
		file.write("		<parameter name=\"cosT_cut\" value=\"0.99\" />\n")
		file.write("		<parameter name=\"searchConeAngle\" value=\""+str(coneValues[cone_itr])+"\" />\n")
		file.write("		<parameter name=\"isolationConeAngle\" value=\""+str(isoAngleValues[angle_itr])+"\" />\n")
		file.write("		<parameter name=\"isolationEnergy\" value=\""+str(isoEnergyValues[ener_itr])+"\" />\n")
		file.write("		<parameter name=\"ptseed\" value=\"5.0\" />\n")
		file.write("		<parameter name=\"invariant_mass\" value=\"2.0\" />\n")
		file.write("	</processor>\n")	
		file.write("\n")	
		ener_itr = ener_itr+1
		

	file.write("	<processor name= \"MyWWAnalysis\" type=\"WWAnalysis\">\n")
	file.write("		<parameter name=\"McParticleCollectionName\" value=\"MCParticle\" />\n")
	file.write("		<parameter name=\"InputParticleColletionName\" type=\"string\" lcioInType=\"ReconstructedParticle\"> PandoraPFOs </parameter>\n")
	file.write("		<parameter name=\"InputTrackCollectionName\" value=\"MarlinTrkTracks\" />\n")
	file.write("		<parameter name=\"InputRecoRelationCollectionName\" value=\"RecoMCTruthLink\" />\n")
#	file.write("		<parameter name=\"InputJetCollectionName\" value=\"FastJets\" />\n")
#	file.write("		<parameter name=\"InputJetWithOverlayCollectionName\" value=\"FastJetsWithOverlay\" />\n")
	file.write("		<parameter name=\"InputJetCollectionsNames\"> ")
	for i in range( treenum , TreePerFileTracker+1 ):
		if i> totalTrees : break
		file.write(" TauJets"+str(i))
	file.write(" </parameter>\n")
	file.write("		<parameter name=\"NFermions\" value=\""+str(nferm)+"\" />\n")
	file.write("		<parameter name=\"Nleptons\" value=\""+str(nlep)+"\" />\n")
	file.write("		<parameter name=\"Normalization\" value=\"0.784017\" />\n")
	file.write("		<parameter name=\"Njets\" value=\"3\" />\n")
	file.write("		<parameter name=\"Ncuts\" value=\"7\" />\n")
	file.write("		<parameter name=\"OutPath\" value=\"/nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RootFiles/\" />\n")
	file.write("	</processor>\n")
	file.write("\n")

	file.write("</marlin>\n")
	#ready next tree
	treenum = treenum+nTreesPerFile


#print "<!-- automatically generated steering -->"
#print "<marlin>"
#print " "

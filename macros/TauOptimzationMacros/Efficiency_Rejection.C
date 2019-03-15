

//from ROOT import TCanvas, TFile, TH1D, TH2D, TProfile, TLegend, TGraph, TTree, gDirectory
//import ROOT as rt
//import subprocess
//from array import array
//import math

#include <vector>

Long64_t LoadTree(Long64_t entry, TTree* fChain, int fCurrent)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
     // Notify();
   }
   return centry;
}
std::vector<double> makearray(double mini,double Maxi,double step){
	//start = mini
	std::vector<double> arr;
	while(mini < Maxi){
		arr.push_back(mini);
		mini = mini + step;
		//mini = round(mini, 4)
	}
	return arr;
}
void printvec(std::vector<double> v){
	for(int i=0; i<v.size(); i++){
		std::cout<<v.at(i)<<" ";
	}
		std::cout<<std::endl;
}
void printvec(std::vector<std::vector<double> > v){
	for(int i=0; i<v.size(); i++){
		for(int j=0; j<v.at(i).size(); j++){
			std::cout<<v.at(i).at(j)<<" ";
		}
		std::cout<<std::endl;
	}
		std::cout<<std::endl;
}
void Efficiency_Rejection(const char* subsetTag, const char* particletypeTag , const char* backgroundTag, int nFiles, int nTreesPerFile){
	//#on run define what subset
//SUBSET = ['S1', 'S2', 'B1']
//PARTICLETYPE = ['MUON', 'ELECTRON', 'TAU0', 'TAU1', 'TAU2', 'TAU3', 'TAU4', 'BG1']
//nFIles = 39
	std::vector<std::string> filenames{};
	std::vector<std::string> bgfilenames{};

	for(int i=1; i<=nFiles; i++){
		std::stringstream fstream;
		std::stringstream bgfstream;
		fstream << "TauFinder"<< i<<subsetTag<<".root";
		bgfstream<< "TauFinder"<<i<<backgroundTag<<".root";
		filenames.push_back( fstream.str() );
		bgfilenames.push_back( bgfstream.str() );
	}

	for(int i=0; i<filenames.size(); i++){
		std::cout<<filenames.at(i)<<std::endl;
		std::cout<<bgfilenames.at(i)<<std::endl;
	}


	//make the arrays
	double searchConeAngleMin = 0.;
	double searchConeAngleMax = 0.16;
	double searchConeAngleStep = 0.01; //#10mrad step

	double isoAngleMin = 0.;
	double isoAngleMax = 0.10;
	double isoAngleStep = 0.01;// #10mrad step

	double isoEnergyMin = 0.;
	double isoEnergyMax = 11.;
	double isoEnergyStep = 1.;// #1gev step

	//#number of trees per file
	//#nTreesPerFile = 50


//#create the parameter sets
	std::vector<double> coneValues = makearray(searchConeAngleMin, searchConeAngleMax, searchConeAngleStep);
	std::vector<double> isoAngleValues = makearray(isoAngleMin, isoAngleMax, isoAngleStep);
	std::vector<double> isoEnergyValues = makearray(isoEnergyMin, isoEnergyMax, isoEnergyStep);
	printvec(coneValues);
	printvec(isoAngleValues);
	printvec(isoEnergyValues);
	std::cout<< coneValues.size() * isoAngleValues.size() * isoEnergyValues.size()<<std::endl;


	//#make a little sublist of [tree number, cone angle, iso angle, iso energy]
	std::vector<std::vector<double> > treedetails{};
	double treenum = 1;
	for(int c=0 ; c< coneValues.size() ;c++){
		for( int iA=0; iA< isoAngleValues.size(); iA++){
			for(int iE=0; iE < isoEnergyValues.size(); iE++){
				std::vector<double> det{treenum, coneValues.at(c), isoAngleValues.at(iA), isoEnergyValues.at(iE) };
				treedetails.push_back(det);
				treenum = treenum + 1.;
			}
		}

	}
	//printvec( treedetails );
	
	std::string path = "/nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/EffRootFiles/";
	std::stringstream outstream;
	outstream<<path<<subsetTag<<particletypeTag<<".root";	
	std::string outfilename = outstream.str();
	TFile* outputFile = new TFile(outfilename.c_str(),"RECREATE");

	std::stringstream outtreename;
	outtreename<<subsetTag<<particletypeTag;
	TTree* outputTree = new TTree(outtreename.str().c_str(), outtreename.str().c_str());
	
	double eff_s;
	double eff_b;
	double RR;
	double treeN;
	double searchCone;
	double isoCone;
	double isoE;
	double p;
	double effp;
	double N_s;
	double N_b;
	double Total_s;
	double Total_b; 

//#set branches
	outputTree->Branch("eff_s",&eff_s,"eff_s/F");
	outputTree->Branch("eff_b",&eff_b,"eff_b/F");
	outputTree->Branch("RR",&RR,"RR/F");
	outputTree->Branch("treeN",&treeN,"treeN/F");
	outputTree->Branch("searchCone",&searchCone,"searchCone/F");
	outputTree->Branch("isoCone",&isoCone,"isoCone/F");
	outputTree->Branch("isoE",&isoE,"isoE/F");
	outputTree->Branch("p",&p,"p/F");
	outputTree->Branch("effp",&effp,"effp/F");
	//outputTree->Branch("N_s",&N_s,"N_s/F")
	//outputTree->Branch("N_b",&N_b,"N_b/F")
	outputTree->Branch("Total_s", &Total_s,"Total_s/F");
	outputTree->Branch("Total_b", &Total_b,"Total_b/F");



	TTree* tree;
	TTree* treebg;
	//make reading vars outside the loops
	bool isMuon;
	TBranch* bisMuon;
	
	TLorentzVector* MCf0;
	TBranch* bMCf0;

	std::string inpath = "/nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RootFiles/";
	//loop over files
//	for( int ifile=0; ifile<filenames.size(); ifile++){// filenameBG in zip(FILESUBSET, BGFILESUBSET):
	for( int ifile=0; ifile<1; ifile++){	
		std::stringstream inf;
		inf<< inpath << filenames.at(ifile);
		TFile* currentFile =  TFile::Open(inf.str().c_str());
		std::stringstream infbg;
		infbg<< inpath << bgfilenames.at(ifile);
		TFile* currentBGFile = TFile::Open(infbg.str().c_str());

		//for both files get the branches we need
		//(TTree)root_file->Get(root_file->GetListOfKeys()->At(0)->GetName());
		
		std::vector<std::string> treeNames{};
		std::vector<std::string> bgtreeNames{};
		for(int nt =0 ; nt<nTreesPerFile; nt++){
			treeNames.push_back( std::string(currentFile->GetListOfKeys()->At(nt)->GetName()));
			bgtreeNames.push_back( std::string(currentBGFile->GetListOfKeys()->At(nt)->GetName()));
		} 	 		
		for(int i=0; i<treeNames.size(); i++){
			cout<<treeNames.at(i)<<" ";
			cout<<bgtreeNames.at(i)<<" ";
		}
		std::cout<<std::endl;

		//loop over all trees
		for(itree= 0; itree<treeNames.size(); itree++){//,tnbg in zip(treeNames, treeNamesBG):
			tree = (TTree*)currentFile->Get(treeNames.at(itree).c_str());
			treebg = (TTree*)currentBGFile->Get(bgtreeNames.at(itree).c_str());

			//declare variables and fill locally
		//	TTreeReader sReader(tree);
		//	TTreeReader bgReader(treebg);
		//	bool isMuon; 
//Abandon ttreereader it sucks do manually
			// https://root.cern.ch/how/how-read-tree
			//bisMuon = tree->GetBranch((treeNames.at(itree)+"isMuon").c_str());
			
			//bMCf0 = tree->GetBranch((treeNames.at(itree)+"MCf0").c_str());
		    tree->SetBranchAddress((treeNames.at(itree)+"MCf0").c_str(), &MCf0, &bMCf0);
			tree->SetBranchAddress((treeNames.at(itree)+"isMuon").c_str(), &isMuon, &bisMuon);
		  //	auto branch  = theTree->GetBranch("event");
  		//	bisMuon->SetAddress(&isMuon);

		//	bMCf0->SetBranchAddress(&MCf0);

			auto nevent = tree->GetEntries();
   			for (Int_t i=0;i<nevent;i++) {
      				tree->GetEvent(i);		
					//bMCf0->GetEvent(i);
					std::cout<<isMuon<<std::endl;
					//std::cout<<MCf0.E()<<std::endl;
			}
	
		//	 Long64_t nentries = tree->GetEntriesFast();
	/*		int fCurrent = -1;
  			 Long64_t nbytes = 0, nb = 0;
  			 for (Long64_t jentry=0; jentry<nentries;jentry++) {
     		//	Long64_t ientry = LoadTree(jentry, tree, fCurrent );
     		 //	if (ientry < 0) break;
     			 nb = tree->GetEntry(jentry);   nbytes += nb;
				
				//std::cout<<MCf0->CosTheta()<<std::endl;
				std::cout<<isMuon<<std::endl;

			}*/
			
					//here are the variables we fill
		//	TTreeReaderValue<bool> isMuon(sReader, ();
		//	TTreeReaderValue<bool> isTau(sReader, (treeNames.at(itree)+"isTau").c_str());
		//	TTreeReaderValue<bool> isElectron(sReader, (treeNames.at(itree)+"isElectron").c_str());
		//	TTreeReaderValue<int> tauType(sReader, (treeNames.at(itree)+"tauType").c_str());
		//	TTreeReaderValue<int> nTaus(sReader, (treeNames.at(itree)+"nTaus").c_str());
			//mc variables + pdgs
		//	TTreeReaderValue<TLorentzVector> mcf0CT(sReader, (treeNames.at(itree)+"MCf0.").c_str());


		//	TTreeReaderValue<int> nTausBG(bgReader, (bgtreeNames.at(itree)+"nTaus").c_str());
			////mc variables + pdgss
		//	 while (sReader.Next()) {
      			
      	//		std::cout<< (*mcf0CT).CosTheta() << " ";		
		//	}
		//	while (bgReader.Next()){
			//	std::cout<< *nTausBG << " ";
	//		}

		}	


	}
}

/*
def bash( bashCommand ):
	process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
	#process = subprocess.Popen(bashCommand.split())
	output, error = process.communicate()
	return output ,error
def GetKeyNames( self, dir = "" ):
        self.cd(dir)
        return [key.GetName() for key in gDirectory.GetListOfKeys()]
TFile.GetKeyNames = GetKeyNames

def GetTreeObject(tree, branchName ,value):
	branchesObj = tree.GetListOfBranches()
	branches = []
	for b in branchesObj:
		branches.append( b.GetName() )
		
#	print "got branches"
	#print branches
	branch = [b for b in branches if branchName in b]
	#print "got branch"
	#print branch
	#print "done"
	tree.SetBranchAddress(branch[0],value)
	#return branch.GetEntries()
	#ranch.GetLeafEntry
	#leafs = tree.GetListOfLeaves()
	#print leafs

def makearray(mini,Maxi,step):
	#start = mini
	arr = []
	while mini < Maxi :
		arr.append(mini)
		mini = mini + step
		mini = round(mini, 4)
	return arr

def getmaxenergy( ntaus, vec4):
	if ntaus == 0:
		return 0.
	maxE = 0.
	for v in vec4:
		if v.E() > maxE:
			maxE = v.E()

	return maxE

def passAcceptance( flist, fpdglist):
	passes = True
	for mcf, pdg in zip(flixt, fpdglist):
		if abs(pdg) != 12 and abs(pdg) != 14 and abs(pdg) != 16:
			#no neutrinos allowed
			if abs( mcf.CosTheta() > 0.995 ):
				passes = False
	return passes 

#run over 3 subsets S1, S2, B1

#on run define what subset
SUBSET = ['S1', 'S2', 'B1']
PARTICLETYPE = ['MUON', 'ELECTRON', 'TAU0', 'TAU1', 'TAU2', 'TAU3', 'TAU4', 'BG1']

#CHOOSE SUBSET/PTYPE INDICES
BGSUBSET = SUBSET[2]
BGPARTICLETYPE = PARTICLETYPE[7]
SUBSET = SUBSET[0]
PARTICLETYPE = PARTICLETYPE[0]



#Since i didnt store it, figure out the parameters for each tree and store them with the eff
searchConeAngleMin = 0.
searchConeAngleMax = 0.16
searchConeAngleStep = 0.01 #10mrad step

isoAngleMin = 0.
isoAngleMax = 0.11
isoAngleStep = 0.01 #10mrad step

isoEnergyMin = 0.
isoEnergyMax = 11.
isoEnergyStep = 1. #1gev step

#number of trees per file
#nTreesPerFile = 50


#create the parameter sets
coneValues = makearray(searchConeAngleMin, searchConeAngleMax, searchConeAngleStep)
isoAngleValues = makearray(isoAngleMin, isoAngleMax, isoAngleStep)
isoEnergyValues = makearray(isoEnergyMin, isoEnergyMax, isoEnergyStep)

#make a little sublist of [tree number, cone angle, iso angle, iso energy]
treedetails = []
treenum = 1
for c in coneValues:
	for iA in isoAngleValues:
		for iE in isoEnergyValues:
			treedetails.append( [ treenum, c, iA, iE ])
			treenum = treenum + 1

#print treedetails

LS = bash('ls /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RootFiles/')
LS = LS[0].split('\n')

#collect the files of chosen subset
FILESUBSET = [f for f in LS if SUBSET in f]
BGFILESUBSET = [f for f in LS if BGSUBSET in f]

#print FILESUBSET
#print BGFILESUBSET

#we need to write all this stuff to a tree in a rootfile
outputFile = TFile.Open('/nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/EffRootFiles/'+SUBSET+PARTICLETYPE+'.root','RECREATE')
outputTree = TTree(SUBSET+PARTICLETYPE, SUBSET+PARTICLETYPE)
eff_s, eff_b, RR, treeN, searchCone, isoCone, isoE, p, effp, N_s, N_b, Total_s, Total_b = array( 'f', [ 0. ] ),array( 'f', [ 0. ]) ,array( 'f', [ 0. ]) ,array( 'f', [ 0. ]) ,array( 'f', [ 0. ]) ,array( 'f', [ 0. ]) ,array( 'f', [ 0. ]) ,array( 'f', [ 0. ]) ,array( 'f', [ 0. ]) ,array( 'f', [ 0. ]) ,array( 'f', [ 0. ]) ,array( 'f', [ 0. ]) ,array( 'f', [ 0. ]) 
#eff_sL, eff_bL, RRL, treeNL, searchConeL, isoConeL, isoEL, pL, effpL, N_sL, N_bL, Total_sL, Total_bL = [], [], [], [], [], [], [], [], [], [], [], [], []
Emax_s, Emax_b = array( 'f', [0.] ), array( 'f', [0.] )
#set branches
outputTree.Branch("eff_s",eff_s,"eff_s/F")
outputTree.Branch("eff_b",eff_b,"eff_b/F")
outputTree.Branch("RR",RR,"RR/F")
outputTree.Branch("treeN",treeN,"treeN/F")
outputTree.Branch("searchCone",searchCone,"searchCone/F")
outputTree.Branch("isoCone",isoCone,"isoCone/F")
outputTree.Branch("isoE",isoE,"isoE/F")
outputTree.Branch("p",p,"p/F")
outputTree.Branch("effp",effp,"effp/F")
outputTree.Branch("N_s",N_s,"N_s/F")
outputTree.Branch("N_b",N_b,"N_b/F")
outputTree.Branch("Total_s", Total_s,"Total_s/F")
outputTree.Branch("Total_b", Total_b,"Total_b/F")
#outputTree.Branch("Emax_s", Emax_s,"Emax_s/F") #the higheest energy tau reconstucted
#outputTree.Branch("Emax_b", Emax_b,"Emax_b/F")

#iterator for tree details
treedetails_itr = 0;
#combine FILESUBSETS
#FILESUPERSET = []
#for f1 in FILESUBSET:#
#	FILESUPERSET.append(f1)
#for b1 in BGFILESUBSET:
#	FILESUPERSET.append(b1)

#FILESUBSET = FILESUPERSET
#tree loop vars
isMuon = array('i',[0])
isTau = array('i',[0])
isElectron = array('i',[0])
tauType = array('i',[0])
nTaus = array('i',[0])
nTausBG = array('i',[0])
#tauTLV = rt.vector('TLorentzVector')()
#tauTLVBG = rt.vector('TLorentzVector')()

#look at acceptance
#currently we only look at 4f events
mcf0 = TLorentzVector()
mcf1 = TLorentzVector()
mcf2 = TLorentzVector()
mcf3 = TLorentzVector()
mcf0_pdg = array('i',[0])
mcf1_pdg = array('i',[0])
mcf2_pdg = array('i',[0])
mcf3_pdg = array('i',[0])
mcf0bg = TLorentzVector()
mcf1bg = TLorentzVector()
mcf2bg = TLorentzVector()
mcf3bg = TLorentzVector()
mcf0_pdgbg = array('i',[0])
mcf1_pdgbg = array('i',[0])
mcf2_pdgbg = array('i',[0])
mcf3_pdgbg = array('i',[0])





print FILESUBSET
print BGFILESUBSET
#loop over the list of files and collect all the trees
for filename, filenameBG in zip(FILESUBSET, BGFILESUBSET):
	currentFile = TFile.Open('/nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RootFiles/'+filename)
	currentBGFile = TFile.Open('/nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RootFiles/'+filenameBG)	

	keyList = currentFile.GetKeyNames('./')
	print "\nKeys in file:", keyList
	treeNames = currentFile.GetKeyNames('./')
	treeNamesBG = currentBGFile.GetKeyNames('./')
	#extract each tree
	for tn,tnbg in zip(treeNames, treeNamesBG):
		tree = currentFile.Get(tn)
		treebg = currentBGFile.Get(tnbg)

		GetTreeObject(tree, 'isMuon', isMuon )
		GetTreeObject(tree, 'nTaus', nTaus )
		GetTreeObject(tree, 'isTau', isTau)
		GetTreeObject(tree, 'isElectron', isElectron)
		GetTreeObject(tree, 'tauType', tauType)
		GetTreeObject(treebg, 'nTaus', nTausBG)
	#	GetTreeObject(tree, 'tauTLV', tauTLV)
	#	GetTreeObject(treebg, 'tauTLV', tauTLVBG) 
		GetTreeObject(tree, 'MCf0', mcf0)
		GetTreeObject(tree, 'MCf1', mcf1)
		GetTreeObject(tree, 'MCf2', mcf2)
		GetTreeObject(tree, 'MCf3', mcf3)
		GetTreeObject(tree, 'MCf0_PDG', mcf0_pdg)
		GetTreeObject(tree, 'MCf1_PDG', mcf1_pdg)
		GetTreeObject(tree, 'MCf2_PDG', mcf2_pdg)
		GetTreeObject(tree, 'MCf3_PDG', mcf3_pdg)
		GetTreeObject(tree, 'MCf0', mcf0bg)
		GetTreeObject(tree, 'MCf1', mcf1bg)
		GetTreeObject(tree, 'MCf2', mcf2bg)
		GetTreeObject(tree, 'MCf3', mcf3bg)
		GetTreeObject(tree, 'MCf0_PDG', mcf0_pdgbg)
		GetTreeObject(tree, 'MCf1_PDG', mcf1_pdgbg)
		GetTreeObject(tree, 'MCf2_PDG', mcf2_pdgbg)
		GetTreeObject(tree, 'MCf3_PDG', mcf3_pdgbg)
		
		#for entry, entryBG in zip(tree, treebg):
		for entry in tree:
			mcflist = [ mcf0, mcf1, mcf2, mcf3 ]
			mcfpdglist = [mcf0_pdg, mcf1_pdg, mcf2_pdg, mcf3_pdg ]
			if passAcceptance(mcflist, mcfpdglist) == False:
				continue

			#does entry pass mc acceptance
			if isMuon[0] and PARTICLETYPE == 'MUON':
				Total_s[0] = Total_s[0]+1.
				round(Total_s[0])
				#print nTaus
				if nTaus[0] == 1:
					N_s[0] = N_s[0] + 1.
					round(N_s[0])

		#print N_s[0], Total_s[0]
			if isTau[0] and PARTICLETYPE == 'TAU0' and tauType[0] == 0:
				Total_s[0] = Total_s[0]+1.
				round(Total_s[0])
				if nTaus[0] == 1:
					N_s[0] = N_s[0] + 1.
					round(N_s[0])

			if isTau[0] and PARTICLETYPE == 'TAU1' and tauType[0] == 1:
				Total_s[0] = Total_s[0]+1.
				round(Total_s[0])
				if nTaus[0] == 1:
					N_s[0] = N_s[0] + 1.
					round(N_s[0])

			if isTau[0] and PARTICLETYPE == 'TAU2' and tauType[0] == 2:
				Total_s[0] = Total_s[0]+1.
				round(Total_s[0])
				if nTaus[0] == 1:
					N_s[0] = N_s[0] + 1.
					round(N_s[0])

			if isTau[0] and PARTICLETYPE == 'TAU3' and tauType[0] == 3:
				Total_s[0] = Total_s[0]+1.
				round(Total_s[0])
				if nTaus[0] == 1:
					N_s[0] = N_s[0] + 1.
					round(N_s[0])

			if isTau[0] and PARTICLETYPE == 'TAU4' and tauType[0] == 4:
				Total_s[0] = Total_s[0]+1.
				round(Total_s[0])
				if nTaus[0] == 1:
					N_s[0] = N_s[0] + 1.
					round(N_s[0])

			if isElectron[0] and PARTICLETYPE == 'ELECTRON':
				Total_s[0] = Total_s[0]+1.
				round(Total_s[0])
				if nTaus[0] == 1:
					N_s[0] = N_s[0] + 1.
					round(N_s[0])

		for entry in treebg:
			mcfbglist = [ mcf0bg, mcf1bg, mcf2bg, mcf3bg ]
			mcfpdgbglist = [mcf0_pdgbg, mcf1_pdgbg, mcf2_pdgbg, mcf3_pdgbg ]
			if passAcceptance(mcfbglist, mcfpdgbglist) == False:
				continue

			if True: #this is background
				Total_b[0] = Total_b[0]+1.
				round(Total_b[0])
				#print nTausBG[0]
				if nTausBG[0] >= 1:
					N_b[0] = N_b[0] + 1.
					round(N_b[0])
		
		eff_s[0] = (N_s[0]/Total_s[0])
		treeN[0] =(treedetails[treedetails_itr][0])
		searchCone[0] = (treedetails[treedetails_itr][1])
		isoCone[0] = (treedetails[treedetails_itr][2])
		isoE[0] =(treedetails[treedetails_itr][3])			
		eff_b[0] =(N_b[0]/Total_b[0])
		RR[0] = (1. - eff_b[0])
		p[0] = (N_s[0] / (N_s[0] + N_b[0]))
		effp[0] = eff_s[0] * p[0]
	#	Emax_s[0] =getmaxenergy( nTaus[0], tauTLV)
	#	Emax_b[0] =getmaxenergy( nTausBG[0], tauTLVBG)
		print eff_s[0], eff_b[0], RR[0], treeN[0], searchCone[0], isoCone[0], isoE[0], p[0], effp[0], N_s[0], N_b[0], Total_s[0], Total_b[0] #, Emax_s[0], Emax_b[0]
		outputTree.Fill()
		treedetails_itr += 1
		
	
		#loop over the tree
		#for nevents in tree:

		#	GetTreeObject(tree, 'isMuon' )
		#	break
	#		if PARTICLETYPE == 'MUON':
	#			#if nevent.(tn+'isMuon'):
	#			if 0:
	#				Total_s = Total_s+ 1.
	#			#	if nevent.(tn+'nTaus') == 1:
	#			if 0:
	#					N_s = N_s + 1.
	#				
	#		if PARTICLETYPE == 'ELECTRON':
	#			True
#
#			if PARTICLETYPE == 'TAU0':
#				True
#
#			if PARTICLETYPE == 'TAU1':
#				True
##			if PARTICLETYPE == 'TAU2':
#				True
#
#			if PARTICLETYPE == 'TAU3':
#				True
#	
#			if PARTICLETYPE == 'TAU4':
#				True

		#populate variables according to the current tree and fill our output tree
#		eff_sL.append(N_s/Total_s)
#		treeNL.append(treedetails[treedetails_itr][0])
#		searchConeL.append(treedetails[treedetails_itr][1])
#		isoConeL.append(treedetails[treedetails_itr][2])
#		isoEL.append(treedetails[treedetails_itr][3])
		#tree.Fill()

#we have to loop over the bg file separate
#for filename in BGFILESUBSET:
#	currentFile = TFile.Open(filename)
#	treeNames = currentFile.GetKeyNames('./')
	#extract each tree
#	for tn in treeNames:
#		tree = currentFile.Get(tn)
		#loop over the tree
#		for nevents in tree:
#			Total_b = Total_b + 1.
		#if nevent.(tn+'nTaus') :
#		if 0:
#				N_b = N_b + 1.
#
#		eff_bL.append(N_b/Total_b)
#		RRL.append(1. - eff_b)
#		pL.append(N_s / (N_s + N_b))
#		effPL.append(1.)
		
#loop over everything
#for A,B,C,D,E,F,G,H,I,J,K,L,M in zip(eff_sL, eff_bL, RRL, treeNL, searchConeL, isoConeL, isoEL, pL, effpL, N_sL, N_bL, Total_sL, Total_bL):
#	eff_s, eff_b, RR, treeN, searchCone, isoCone, isoE, p, effp, N_s, N_b, Total_s, Total_b = A,B,C,D,E,F,G,H,I,J,K,L,M
#	effp = eff_s * p
#	outputTree.Fill()
	

outputFile.Write()
		
*/




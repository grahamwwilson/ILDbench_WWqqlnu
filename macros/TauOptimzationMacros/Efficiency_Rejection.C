

//from ROOT import TCanvas, TFile, TH1D, TH2D, TProfile, TLegend, TGraph, TTree, gDirectory
//import ROOT as rt
//import subprocess
//from array import array
//import math

#include <vector>
#include <math.h>
using namespace std;
bool passAcceptance( TLorentzVector* MCf0, TLorentzVector* MCf1, TLorentzVector* MCf2, TLorentzVector* MCf3, int pdg0,int pdg1, int pdg2, int pdg3){

	//std::cout<< fabs(MCf0->CosTheta()) <<" "<<fabs(MCf1->CosTheta())<< " "<<fabs(MCf2->CosTheta()) <<" "<<fabs(MCf3->CosTheta()) <<std::endl;
//	std::cout<< pdg0<<" "<<pdg1<<" "<<pdg2<<" "<<pdg3<<std::endl;
	if( (fabs(MCf0->CosTheta()) > 0.995) && (std::abs(pdg0) != 12) && (std::abs(pdg0) != 14) && (std::abs(pdg0) !=16) ) { return false;}
	if( (fabs(MCf1->CosTheta()) > 0.995) && (std::abs(pdg1) != 12) && (std::abs(pdg1) != 14) && (std::abs(pdg1) !=16) ) { return false;}
	if( (fabs(MCf2->CosTheta()) > 0.995) && (std::abs(pdg2) != 12) && (std::abs(pdg2) != 14) && (std::abs(pdg2) !=16) ) { return false;}
	if( (fabs(MCf3->CosTheta()) > 0.995) && (std::abs(pdg3) != 12) && (std::abs(pdg3) != 14) && (std::abs(pdg3) !=16) ) { return false;}

	return true;
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

void Efficiency_RejectionRun(const char* subsetTag, const char* particletypeTag , const char* backgroundTag, int nFiles, int nTreesPerFile){
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
		std::cout<<filenames.at(i)<<" ";
	//	std::cout<<bgfilenames.at(i)<<std::endl;
	}
	std::cout<<std::endl;
	for(int i=0; i<filenames.size(); i++){
	//	std::cout<<filenames.at(i)<<std::endl;
		std::cout<<bgfilenames.at(i)<<" ";;
	}
	std::cout<<std::endl;

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
//	printvec( treedetails );
	
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
	outputTree->Branch("eff_s",&eff_s,"eff_s/D");
	outputTree->Branch("eff_b",&eff_b,"eff_b/D");
	outputTree->Branch("RR",&RR,"RR/D");
	outputTree->Branch("treeN",&treeN,"treeN/D");
	outputTree->Branch("searchCone",&searchCone,"searchCone/D");
	outputTree->Branch("isoCone",&isoCone,"isoCone/D");
	outputTree->Branch("isoE",&isoE,"isoE/D");
	outputTree->Branch("p",&p,"p/D");
	outputTree->Branch("effp",&effp,"effp/D");
	//outputTree->Branch("N_s",&N_s,"N_s/F")
	//outputTree->Branch("N_b",&N_b,"N_b/F")
	//outputTree->Branch("Total_s", &Total_s,"Total_s/F");
	//outputTree->Branch("Total_b", &Total_b,"Total_b/F");



	TTree* tree;
	TTree* treebg;
	//make reading vars outside the loops
	bool isMuon;
	TBranch* bisMuon;
	bool isTau;
	TBranch* bisTau;
	bool isElectron;
	TBranch* bisElectron;
	int tauType;
	TBranch* btauType;
	int nTaus;
	TBranch* bnTaus;
	
	TLorentzVector* MCf0 = new TLorentzVector();
	TBranch* bMCf0;
	TLorentzVector* MCf1 = new TLorentzVector();
	TBranch* bMCf1;
	TLorentzVector* MCf2 = new TLorentzVector();
	TBranch* bMCf2;
	TLorentzVector* MCf3 = new TLorentzVector();
	TBranch* bMCf3;

	int MCf0_PDG;
	TBranch* bMCf0_PDG;
	int MCf1_PDG;
	TBranch* bMCf1_PDG;
	int MCf2_PDG;
	TBranch* bMCf2_PDG;
	int MCf3_PDG;
	TBranch* bMCf3_PDG;

	//int nTausBG;
	//TBranch* ntausBG;
	//try to use same mcf vars for bg

	int treeDetailsItr=0;

	std::string inpath = "/nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RootFiles/";
	//loop over files
	for( int ifile=0; ifile<filenames.size(); ifile++){// filenameBG in zip(FILESUBSET, BGFILESUBSET):
//	for( int ifile=0; ifile<1; ifile++){	
		std::stringstream inf;
		inf<< inpath << filenames.at(ifile);
		TFile* currentFile =  TFile::Open(inf.str().c_str());
		std::stringstream infbg;
		infbg<< inpath << bgfilenames.at(ifile);
		TFile* currentBGFile = TFile::Open(infbg.str().c_str());

		std::cout<<"Current File "<< inf.str()<<std::endl;
		std::cout<<"Current BG File "<< infbg.str()<<std::endl;

		//for both files get the branches we need
		//(TTree)root_file->Get(root_file->GetListOfKeys()->At(0)->GetName());
		
	
		std::vector<std::string> treeNames{};
		std::vector<std::string> bgtreeNames{};
		for(int nt =0 ; nt<nTreesPerFile; nt++){
			treeNames.push_back( std::string(currentFile->GetListOfKeys()->At(nt)->GetName()));
			bgtreeNames.push_back( std::string(currentBGFile->GetListOfKeys()->At(nt)->GetName()));
		} 	


		//loop over all trees
		for(int itree= 0; itree<treeNames.size(); itree++){//,tnbg in zip(treeNames, treeNamesBG):
			//currentFile
			tree = (TTree*)currentFile->Get(treeNames.at(itree).c_str());
			treebg = (TTree*)currentBGFile->Get(bgtreeNames.at(itree).c_str());
		//	std::cout<<"currentFile tree name "<< tree->GetName()<<std::endl;;
		//	std::cout<<"currentBGFile tree name "<< treebg->GetName()<<std::endl;;			


		    tree->SetBranchAddress((treeNames.at(itree)+"MCf0").c_str(), &MCf0, &bMCf0);
			tree->SetBranchAddress((treeNames.at(itree)+"MCf1").c_str(), &MCf1, &bMCf1);
			tree->SetBranchAddress((treeNames.at(itree)+"MCf2").c_str(), &MCf2, &bMCf2);
			tree->SetBranchAddress((treeNames.at(itree)+"MCf3").c_str(), &MCf3, &bMCf3);
			tree->SetBranchAddress((treeNames.at(itree)+"MCf0_PDG").c_str(), &MCf0_PDG, &bMCf0_PDG);
			tree->SetBranchAddress((treeNames.at(itree)+"MCf1_PDG").c_str(), &MCf1_PDG, &bMCf1_PDG);
			tree->SetBranchAddress((treeNames.at(itree)+"MCf2_PDG").c_str(), &MCf2_PDG, &bMCf2_PDG);
			tree->SetBranchAddress((treeNames.at(itree)+"MCf3_PDG").c_str(), &MCf3_PDG, &bMCf3_PDG);
			tree->SetBranchAddress((treeNames.at(itree)+"isMuon").c_str(), &isMuon, &bisMuon);
			tree->SetBranchAddress((treeNames.at(itree)+"isTau").c_str(), &isTau, &bisTau);
			tree->SetBranchAddress((treeNames.at(itree)+"isElectron").c_str(), &isElectron, &bisElectron);
			tree->SetBranchAddress((treeNames.at(itree)+"tauType").c_str(), &tauType, &btauType);
			tree->SetBranchAddress((treeNames.at(itree)+"nTaus").c_str(), &nTaus, &bnTaus);

			//loop signal tree
			auto nevent = tree->GetEntries();
			//nevent = 1000;

			//zero counts
			Total_s = 0.;
			N_s = 0.;
   			for (Int_t i=0;i<nevent;i++) {
      				tree->GetEvent(i);		

					if( !passAcceptance( MCf0, MCf1, MCf2, MCf3, MCf0_PDG, MCf1_PDG, MCf2_PDG, MCf3_PDG) ){
						//std::cout<<"FAIL ";
					 continue;
					}
					
						//std::cout<<"PASS "<<std::endl;
					
		
				
				std::string PARTICLETYPE = std::string(particletypeTag);
				if( isMuon && PARTICLETYPE.compare("MUON")==0 ){
					Total_s++;
					if(nTaus >= 1){
						N_s += 1.;
					}
				}
				if(isTau && PARTICLETYPE.compare("TAU0")==0){
					Total_s += 1.;
					if(nTaus >= 1){
						N_s += 1.;
					}
				}
				if(isTau && PARTICLETYPE.compare("TAU1")==0 && tauType == 1){
					Total_s += 1.;
					if(nTaus >= 1){
						N_s += 1.;
					}
				}
				if(isTau && PARTICLETYPE.compare("TAU2")==0 && tauType == 2){
					Total_s += 1.;
					if(nTaus >= 1){
						N_s += 1.;
					}
				}
				if(isTau && PARTICLETYPE.compare("TAU3")==0 && tauType == 3){
					Total_s += 1.;
					if(nTaus >= 1){
						N_s += 1.;
					}
				}
			 	if(isTau && PARTICLETYPE.compare("TAU4")==0 && tauType == 4){
					Total_s += 1.;
					if(nTaus >= 1){
						N_s += 1.;
					}
				}
				if(isElectron && PARTICLETYPE.compare("ELECTRON")==0){
					Total_s += 1.;

					if(nTaus >= 1){
						N_s += 1.;
					}
				
				}
			}
		
			//redirect other tree to same vars
 			treebg->SetBranchAddress((bgtreeNames.at(itree)+"MCf0").c_str(), &MCf0, &bMCf0);
			treebg->SetBranchAddress((bgtreeNames.at(itree)+"MCf1").c_str(), &MCf1, &bMCf1);
			treebg->SetBranchAddress((bgtreeNames.at(itree)+"MCf2").c_str(), &MCf2, &bMCf2);
			treebg->SetBranchAddress((bgtreeNames.at(itree)+"MCf3").c_str(), &MCf3, &bMCf3);
			treebg->SetBranchAddress((bgtreeNames.at(itree)+"MCf0_PDG").c_str(), &MCf0_PDG, &bMCf0_PDG);
			treebg->SetBranchAddress((bgtreeNames.at(itree)+"MCf1_PDG").c_str(), &MCf1_PDG, &bMCf1_PDG);
			treebg->SetBranchAddress((bgtreeNames.at(itree)+"MCf2_PDG").c_str(), &MCf2_PDG, &bMCf2_PDG);
			treebg->SetBranchAddress((bgtreeNames.at(itree)+"MCf3_PDG").c_str(), &MCf3_PDG, &bMCf3_PDG);
			treebg->SetBranchAddress((bgtreeNames.at(itree)+"nTaus").c_str(), &nTaus, &bnTaus);

			//loop over bg tree
			//zero counts
			Total_b = 0.;
			N_b = 0.;
			
			nevent = treebg->GetEntries();
	//		nevent = 40;
   			for (Int_t i=0;i<nevent;i++) {
      				treebg->GetEvent(i);		
					if( !passAcceptance( MCf0, MCf1, MCf2, MCf3, MCf0_PDG, MCf1_PDG, MCf2_PDG, MCf3_PDG) ){
						//std::cout<<"FAIL ";
					 continue;
					}
					//std::cout<<"PASS "<<std::endl;
					Total_b += 1.;
					if(nTaus >= 1){
						N_b += 1.;
					}
					
			}
			

			eff_s = N_s/Total_s;
			eff_b = N_b/Total_b;
			RR = 1. - eff_b;
			treeN = treedetails.at(treeDetailsItr).at(0);
			searchCone = treedetails.at(treeDetailsItr).at(1);
			isoCone = treedetails.at(treeDetailsItr).at(2);
			isoE = treedetails.at(treeDetailsItr).at(3);
			p = N_s/ (N_s+N_b);
			effp = eff_s * p;
		
			std::cout<< eff_s<< " "<< eff_b<<" "<< RR << " "<< treeN<<" "<<searchCone<<" "<<isoCone<<" "<<isoE<<" "<<p<<" "<<effp<<" "<<std::endl;

			outputTree->Fill();
	
			treeDetailsItr++;
			

		}//end tree loop	

		
	}//end file loop
	outputFile->Write();
}
void Efficiency_Rejection(){
	std::vector<const char*> subsets{"S1","S2","B1"};
	std::vector<const char*> ptypes{"MUON", "ELECTRON", "TAU0", "TAU1", "TAU2", "TAU3", "TAU4"};
	int nFiles = 39;
	int nTreesPerFile = 50;
	Efficiency_RejectionRun(subsets[0], ptypes[0], subsets[2], nFiles, nTreesPerFile );//M0
	Efficiency_RejectionRun(subsets[0], ptypes[2], subsets[2], nFiles, nTreesPerFile );//T0
	Efficiency_RejectionRun(subsets[0], ptypes[3], subsets[2], nFiles, nTreesPerFile );//T1
	Efficiency_RejectionRun(subsets[0], ptypes[4], subsets[2], nFiles, nTreesPerFile );//T2
	Efficiency_RejectionRun(subsets[0], ptypes[5], subsets[2], nFiles, nTreesPerFile );//T3
	Efficiency_RejectionRun(subsets[0], ptypes[6], subsets[2], nFiles, nTreesPerFile );//T4
	Efficiency_RejectionRun(subsets[1], ptypes[1], subsets[2], nFiles, nTreesPerFile );//E0
	
}





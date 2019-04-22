

//from ROOT import TCanvas, TFile, TH1D, TH2D, TProfile, TLegend, TGraph, TTree, gDirectory
//import ROOT as rt
//import subprocess
//from array import array
//import math

#include <vector>
#include <math.h>
#include "TLorentzVector.h"
#include "TBranch.h"
#include <sstream>
#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include <string>
#include "TVector3.h"
#include "TROOT.h"

using namespace std;
bool passAcceptance( TLorentzVector* MCf0, TLorentzVector* MCf1, TLorentzVector* MCf2, TLorentzVector* MCf3, int pdg0,int pdg1, int pdg2, int pdg3){

	//std::cout<< fabs(MCf0->CosTheta()) <<" "<<fabs(MCf1->CosTheta())<< " "<<fabs(MCf2->CosTheta()) <<" "<<fabs(MCf3->CosTheta()) <<std::endl;
//	std::cout<< pdg0<<" "<<pdg1<<" "<<pdg2<<" "<<pdg3<<std::endl;
	//cut reduced from 0.995 to 0.99
	if( (fabs(MCf0->CosTheta()) > 0.99) && (std::abs(pdg0) != 12) && (std::abs(pdg0) != 14) && (std::abs(pdg0) !=16) ) { return false;}
	if( (fabs(MCf1->CosTheta()) > 0.99) && (std::abs(pdg1) != 12) && (std::abs(pdg1) != 14) && (std::abs(pdg1) !=16) ) { return false;}
	if( (fabs(MCf2->CosTheta()) > 0.99) && (std::abs(pdg2) != 12) && (std::abs(pdg2) != 14) && (std::abs(pdg2) !=16) ) { return false;}
	if( (fabs(MCf3->CosTheta()) > 0.99) && (std::abs(pdg3) != 12) && (std::abs(pdg3) != 14) && (std::abs(pdg3) !=16) ) { return false;}

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
bool foundMatch( TLorentzVector*& mcl, std::vector<TLorentzVector>& taujets , double& minTauPsi, std::vector<double>& psitau ){

	std::vector<double> psis(taujets.size());
	//match threshold 100mrad
	double radcut = 0.1;
	bool pass = false;
	double cospsi{};
	double psi{};
	minTauPsi = 999;
	for(unsigned int i=0; i< taujets.size(); i++){

		cospsi = mcl->Vect().Dot( taujets.at(i).Vect() )/ (mcl->Vect().Mag() * taujets.at(i).Vect().Mag() );
		psi = acos(cospsi);
		psis.at(i) = psi;	
		if(psi < minTauPsi ){
			minTauPsi = psi;
			//_indexOfMinTauPsi = i;
			if(minTauPsi <= radcut) pass = true;
		}
		
		
	}	
	psitau = psis;
	return pass;
}
void countByBin( int nTaus, double cutparam, bool matchfound,
	std::vector<double>& N, std::vector<double>& N_match, std::vector<double>& Total, std::vector<double>& cuts){

		
			for( int j=0; j<cuts.size()-1; j++){
				if( cutparam >= cuts.at(j) && cutparam < cuts.at(j+1)){
					Total.at(j) += 1.;
					if( nTaus >= 1 ){
						N.at(j) += 1.;
					}
					if(matchfound){
						N_match.at(j) +=1.;
					}
				}
			}
		

}
void removeFSRPhoton( std::vector<TLorentzVector>& V , std::vector<TLorentzVector>& I , std::vector<int>& Vpdg, TLorentzVector*& mcl , std::vector<int>& RemovalCand){
	
		double tolerance =  1e-3;
		bool skip = false;
		TLorentzVector tau;
		for(int i=0; i< V.size(); i++){
			skip = false;
			//loop over removal cand, if i == index in removal cand skip
			for(int j=0; j<RemovalCand.size(); j++){
				if( i == RemovalCand.at(j)){ 
					skip = true;
				}
			}
			if(skip) continue;
			tau += V.at(i);
		}
		for(int i=0; i< I.size(); i++){
			tau += I.at(i);
		}
	
		double Mdiff = tau.M() - mcl->M();
		std::cout<<"Mdiff "<<Mdiff<<std::endl;
		
		if(Mdiff < 0 ){
			//something is wrong
			std::cout<<" Mdiff < 0!"<<std::endl;		
			return;
		}//stopping condition removed too much

		//look at gamma that minimizes Mdiff - gammaE
		//loop over visible guys
		double mindiff= 999.;
		int candInd = -1;
		double diff;
		for(int i=0; i< Vpdg.size(); i++){
			skip = false;
			//loop over removal cand, if i == index in removal cand skip
			for(int j=0; j<RemovalCand.size(); j++){
				if( i == RemovalCand.at(j)){ 
					skip = true;
				}
			}
			if(skip) continue;

			
			if(Vpdg.at(i) == 22){
				TLorentzVector Vnew;
				Vnew = tau - V.at(i);	
				diff = Vnew.M() - mcl->M();
				if( diff < mindiff && diff > 0.){
					mindiff = diff;
					candInd = i;
				}
			}
		}  
		std::cout<<"mindiff cand i : "<< mindiff<<" "<<candInd<<std::endl;
		//if we cant find anything just return
		if( candInd == -1 ) return;
		//we have a removal candidate
		//are we within tolerance?
		if( mindiff <= tolerance ){
			//dont do anything else just set a candidate to be removed
			RemovalCand.push_back(candInd); 
			return;
		}
		else{ //try removing another photon
			RemovalCand.push_back(candInd);
			removeFSRPhoton(V,I,Vpdg,mcl,RemovalCand);

		}
	
		//return;
}
//make sure filtered input is an empty vector
void removeExtraNeutrino(std::vector<TLorentzVector>& Invis, std::vector<int>& InvisPdg, std::vector<TLorentzVector>& filteredInvis, std::vector<int>& filteredInvisPdg, int mcpdg ){
	
		//	std::vector<TLorentzVector> filteredInvis{};
		//	std::vector<int> filteredInvisPdg{};
			//remove W neutrino
			for(int i =0; i<Invis.size(); i++){
				//if the neutrino pdg is same sign remove it
				if( abs(InvisPdg.at(i)) == 16){
					if( InvisPdg.at(i) * mcpdg > 0 ){
						//this is good one push back
						filteredInvis.push_back( Invis.at(i) );
						filteredInvisPdg.push_back( InvisPdg.at(i)	);
					}
					else{ //its W neutrino do nothing 
					}
				}
				else{
					//store all other neutrinos
					filteredInvis.push_back( Invis.at(i) );
					filteredInvisPdg.push_back( InvisPdg.at(i)	);
				}
			}
}
void filterFSR(std::vector<TLorentzVector>& unfilteredV, std::vector<TLorentzVector>& unfilteredI, std::vector<TLorentzVector>& filteredV, std::vector<TLorentzVector>& filteredI, std::vector<int>& unfilteredVpdg, std::vector<int>& unfilteredIpdg, std::vector<int>& filteredVpdg, std::vector<int>& filteredIpdg, TLorentzVector*& mcl, int mcpdg){


	//boost everything into CM
	TVector3 mcboost = mcl->BoostVector();
	mcl->Boost(-mcboost);
	for(int i =0; i<unfilteredV.size(); i++){
		unfilteredV.at(i).Boost(-mcboost);
	}
	for(int i =0; i<unfilteredI.size(); i++){
		unfilteredI.at(i).Boost(-mcboost);
	}
	
	
	//do a mass check within tolerance, if everything is fine just spit out  the input as filtered
	//hardcoded tolerance 1e-3
	TLorentzVector tau;
	double tolerance = 1e-3;
	for(int i =0; i<unfilteredV.size(); i++){
		tau+= unfilteredV.at(i);
	}
	for(int i =0; i<unfilteredI.size(); i++){
		tau+= unfilteredI.at(i);
	}

	if( fabs(tau.M() - mcl->M()) < tolerance){
		std::cout<< tau.M() <<" "<<mcl->M()<<" within tolerance "<<std::endl;

		//boost and return so we dont double boost later
		mcl->Boost(mcboost);
		for(int i =0; i<unfilteredV.size(); i++){
			unfilteredV.at(i).Boost(mcboost);
		}
		for(int i =0; i<unfilteredI.size(); i++){
			unfilteredI.at(i).Boost(mcboost);
		}
		//copy unfiltered to filtered
		filteredV = unfilteredV;
		filteredI = unfilteredI;
		filteredVpdg = unfilteredVpdg;
		filteredIpdg = unfilteredIpdg;

		return;
		
	}
	else{
	

		//this function populates the filtered vector itself
		removeExtraNeutrino( unfilteredI, unfilteredIpdg, filteredI, filteredIpdg, mcpdg);
		//after extra neutrino is removed, 
		std::vector<int> partsToBeRemoved{};
		removeFSRPhoton(unfilteredV , filteredI , unfilteredVpdg, mcl , partsToBeRemoved);
		//remove the FSR candidates
		bool skip= false;
		for(int i=0; i<unfilteredV.size(); i++){
			skip = false;
			for( int j=0; j<partsToBeRemoved.size(); j++){
				if(i== partsToBeRemoved.at(j)){
					skip = true;
				}
			}
			if(skip) continue;

			filteredV.push_back( unfilteredV.at(i) );
			filteredVpdg.push_back( unfilteredVpdg.at(i) );
		}
	
	}//end else


	//boost back into lab (both filtered and unfiltered)
	mcl->Boost(mcboost);
	for(int i =0; i<unfilteredV.size(); i++){
		unfilteredV.at(i).Boost(mcboost);
	}
	for(int i =0; i<unfilteredI.size(); i++){
		unfilteredI.at(i).Boost(mcboost);
	}
	for(int i=0; i<filteredV.size(); i++){
		filteredV.at(i).Boost(mcboost);
	}
	for(int i=0; i<filteredI.size(); i++){
		filteredI.at(i).Boost(mcboost);
	}


}
bool foundPromptTauMatch( TLorentzVector*& mcl, int mclpdg, std::vector<TLorentzVector> mcV, std::vector<TLorentzVector> mcI, std::vector<int> mcVpdg, std::vector<int> mcIpdg, std::vector<TLorentzVector> taujets, double& minTauPsi, std::vector<double>& psitau){
	double radcut = 0.1;

	double cospsi{};
	double psi{};
	minTauPsi = 999;
	std::vector<TLorentzVector> fV{};
	std::vector<TLorentzVector> fI{};
	std::vector<int> fVpdg{};
	std::vector<int> fIpdg{};
	//first task, remove potential FSR photons
	filterFSR(mcV, mcI, fV, fI, mcVpdg, mcIpdg, fVpdg, fIpdg, mcl , mclpdg);
	//second task, match visible non-FSR objects to tau jet
	TLorentzVector V;
	for(unsigned int i=0; i< fV.size(); i++){
		V += fV.at(i);
	}
	//copy to ptr
	TLorentzVector* Vtemp = new TLorentzVector();
	Vtemp->SetXYZM(V.Px(), V.Py(), V.Pz(), V.M());
	bool pass = foundMatch( Vtemp, taujets , minTauPsi, psitau );

	return pass;


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
	double isoAngleMax = 0.16;
	double isoAngleStep = 0.01;// #10mrad step

	double isoEnergyMin = 0.;
	double isoEnergyMax = 6.;
	double isoEnergyStep = .5;// #1gev step

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
	
	//double eff_s;
	//double eff_b;
	//double RR;
	double s_ratio; //Ns/Ntot
	double b_ratio; //Nb/Ntot
	double ds_ratio; //error on sratio
	double db_ratio; //error on bratio
	double s_matchratio; //Nmatch/Ntot
	double ds_matchratio; //error on smatchratio
	double singleJetFakeProb; //binomial prob of a single quark jet creating a tau jet
	double singleJetFakeIneff; //1- singlefakeprob
	double dsingleJetFakeProb; //"binomial" error on single prob
	std::vector<double> psitau{};
	double minTauPsi; //the match psi value
	double optProd; //singleGetFakeIneff*s_matchratio
	
	double treeN;
	double searchCone;
	double isoCone;
	double isoE;
	//double p;
	//double effp;
	double N_s; //number of events with >= 1 reco tau jet
	double N_match; //number of matches
	double matchratio; //Nmatch/Ns (matching efficiency)
	double N_b;
	double Total_s;
	double Total_b; 

	//efficiencies as a function of polar angle
	//calculate errors downstream since bins will be combined (very fine binning upstream here)
	//( -q cos theta) 
	int cThetaBins = 20; //bins of cosT =.1
	std::vector<double> N_s_cTheta(cThetaBins);
	std::vector<double> N_match_cTheta(cThetaBins);
    std::vector<double> Total_s_cTheta(cThetaBins);
	std::vector<double> N_b_cTheta(cThetaBins);
	std::vector<double> Total_b_cTheta(cThetaBins);
	std::vector<double> cThetaCuts(cThetaBins+1);
	cThetaCuts.at(0) = -1.;
	for(int i=1; i < cThetaBins+1; i++){
		cThetaCuts.at(i) = cThetaCuts.at(i-1) + .1;
	}
	//check costheta bins
	for(unsigned int i=0; i< cThetaCuts.size(); i++){
		std::cout<< cThetaCuts.at(i) <<" ";
	}
	std::cout<<std::endl;

	int momBins = 20;
	std::vector<double> N_s_mom( momBins );
	std::vector<double> N_match_mom( momBins );
	std::vector<double> Total_s_mom( momBins );
	std::vector<double> momCuts(momBins+1);
	momCuts.at(0) = 0.;
	for(int i=1; i< momBins+1; i++){
		momCuts.at(i) = momCuts.at(i-1) + 10.;
	}
	for(unsigned int i=0; i< momCuts.size(); i++){
		std::cout<< momCuts.at(i) << " ";
	}
	std::cout<<std::endl;

	//q sintheta
	int sThetaBins = 20;
	std::vector<double> N_s_sTheta(sThetaBins);
	std::vector<double> N_match_sTheta(sThetaBins);
	std::vector<double> Total_s_sTheta( sThetaBins );
	std::vector<double> sThetaCuts;
	sThetaCuts = cThetaCuts;

	//single jet fake prob must be calculated later if bins are combined

	//efficiencies as a function of trackE+Mult -- call it taujetcomposition
	int tjCompBins = 49;
	std::vector<double> N_s_tjComp(tjCompBins);
	std::vector<double> N_match_tjComp(tjCompBins);
    std::vector<double> Total_s_tjComp(tjCompBins);
	std::vector<double> N_b_tjComp(tjCompBins);
	std::vector<double> Total_b_tjComp(tjCompBins);
	std::vector<double> tjCompCuts(tjCompBins+1);
	//tjCompCuts.at(0) = 1.01;
	double trkFrac = 0.01;
	double jetmult = 1.;
	for(int i=0; i< tjCompBins+1; i++){
		tjCompCuts.at(i) = 	jetmult + trkFrac;
		trkFrac = trkFrac + 0.01;
		if(trkFrac > 0.1){
			trkFrac = 0.01;
			jetmult = jetmult + 1;
		}	
	}
	//check tjcomp bins
	for(unsigned int i=0; i< tjCompCuts.size(); i++){
		std::cout<< tjCompCuts.at(i)<< " ";
	}
	std::cout<<std::endl;


	//TODO redefine tree etc do matching

//#set branches
/*	outputTree->Branch("eff_s",&eff_s,"eff_s/D");
	outputTree->Branch("eff_b",&eff_b,"eff_b/D");
	outputTree->Branch("RR",&RR,"RR/D");
	outputTree->Branch("treeN",&treeN,"treeN/D");
	outputTree->Branch("searchCone",&searchCone,"searchCone/D");
	outputTree->Branch("isoCone",&isoCone,"isoCone/D");
	outputTree->Branch("isoE",&isoE,"isoE/D");
	outputTree->Branch("p",&p,"p/D");
	outputTree->Branch("effp",&effp,"effp/D");
	outputTree->Branch("N_s",&N_s,"N_s/F")
	outputTree->Branch("N_b",&N_b,"N_b/F")
	outputTree->Branch("Total_s", &Total_s,"Total_s/F");
	outputTree->Branch("Total_b", &Total_b,"Total_b/F");
*/
	outputTree->Branch("s_ratio",&s_ratio,"s_ratio/D");
	outputTree->Branch("b_ratio",&b_ratio,"b_ratio/D");
	outputTree->Branch("ds_ratio",&ds_ratio,"ds_ratio/D");
	outputTree->Branch("db_ratio",&db_ratio,"db_ratio/D");
	outputTree->Branch("s_matchratio",&s_matchratio,"s_matchratio/D");
	outputTree->Branch("ds_matchratio",&ds_matchratio,"ds_matchratio/D");
	outputTree->Branch("singleJetFakeProb",&singleJetFakeProb,"singleJetFakeProb/D");
	outputTree->Branch("singleJetFakeIneff",&singleJetFakeIneff,"singleJetFakeIneff/D");
	outputTree->Branch("dsingleJetFakeProb", &dsingleJetFakeProb, "dsingleJetFakeProb/D");
	//outputTree->Branch("minTauPsi",&minTauPsi,"minTauPsi/D");
	outputTree->Branch("optProd",&optProd,"optProd/D");
	outputTree->Branch("treeN",&treeN,"treeN/D");
	outputTree->Branch("searchCone",&searchCone,"searchCone/D");
	outputTree->Branch("isoCone",&isoCone,"isoCone/D");
	outputTree->Branch("isoE",&isoE,"isoE/D");
    outputTree->Branch("N_s",&N_s,"N_s/D");
	outputTree->Branch("N_match",&N_match,"N_match/D");
    outputTree->Branch("matchratio",&matchratio,"matchratio/D");
    outputTree->Branch("N_b",&N_b,"N_b/D");
    outputTree->Branch("Total_s",&Total_s,"Total_s/D");
    outputTree->Branch("Total_b",&Total_b,"Total_b/D");
	//outputTree->Branch("psitau",&psitau);


	//other efficiencies
	outputTree->Branch("N_s_cTheta",&N_s_cTheta);
	outputTree->Branch("N_match_cTheta",&N_match_cTheta);
	outputTree->Branch("Total_s_cTheta",&Total_s_cTheta);
//	outputTree->Branch("N_b_cTheta",&N_b_cTheta);
//	outputTree->Branch("Total_b_cTheta",&Total_b_cTheta);

	//need to add more variables upstream to deal with this
	outputTree->Branch("N_s_tjComp",&N_s_tjComp);
	outputTree->Branch("N_match_tjComp",&N_match_tjComp);
	outputTree->Branch("Total_s_tjComp",&Total_s_tjComp);
	outputTree->Branch("N_b_tjComp",&N_b_tjComp);
	outputTree->Branch("Total_b_tjComp",&Total_b_tjComp);

	outputTree->Branch("N_s_mom", &N_s_mom);
	outputTree->Branch("N_match_mom", &N_match_mom);
	outputTree->Branch("Total_s_mom", &Total_s_mom);

	outputTree->Branch("N_s_sTheta", &N_s_sTheta);
	outputTree->Branch("N_match_sTheta",&N_match_sTheta);
	outputTree->Branch("Total_s_sTheta",&Total_s_sTheta);

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

	//this will work best for not taus
	int indexOfMinTauPsi;
	TBranch* bindexOfMinTauPsi;

	std::vector<TLorentzVector>* tauTLV = new std::vector<TLorentzVector>();
	TBranch* btauTLV{};

	std::vector<int>* MCTauVisibleDaughters_pdg = new std::vector<int>();
	TBranch* bMCTauVisibleDaughters_pdg{};
	std::vector<TLorentzVector>* MCTauVisibleDaughters = new std::vector<TLorentzVector>();
	TBranch* bMCTauVisibleDaughters{};

	std::vector<int>* MCTauInvisibleDaughters_pdg = new std::vector<int>();
	TBranch* bMCTauInvisibleDaughters_pdg{};
	std::vector<TLorentzVector>* MCTauInvisibleDaughters = new std::vector<TLorentzVector>();
	TBranch* bMCTauInvisibleDaughters{};
	
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


	//Get branches for decay vectors


	//int nTausBG;
	//TBranch* ntausBG;
	//try to use same mcf vars for bg

	int treeDetailsItr=0;

	std::cout<<"Running Mode "<< subsetTag << " " << particletypeTag <<std::endl;

	std::string inpath = "/nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RootFiles/";
	//loop over files
	//for( int ifile=0; ifile<filenames.size(); ifile++){// filenameBG in zip(FILESUBSET, BGFILESUBSET):
	for( unsigned int ifile=0; ifile<filenames.size(); ifile++){	
		std::stringstream inf;
		inf<< inpath << filenames.at(ifile);
		TFile* currentFile = TFile::Open(inf.str().c_str());

	
		std::stringstream infbg;
		infbg<< inpath << bgfilenames.at(ifile);
		TFile* currentBGFile = TFile::Open(infbg.str().c_str());

		std::cout<<"Current File "<< inf.str()<<std::endl;
		std::cout<<"Current BG File "<< infbg.str()<<std::endl;

		
		//for both files get the branches we need
		//(TTree)root_file->Get(root_file->GetListOfKeys()->At(0)->GetName());
		
	
		std::vector<std::string> treeNames{};
		std::vector<std::string> bgtreeNames{};
		int nTreesInFile=currentFile->GetListOfKeys()->GetEntries();
		std::cout<<"ntreesinFile"<<nTreesInFile<<std::endl;
		
		for(int nt =0 ; nt<nTreesInFile; nt++){
			
			treeNames.push_back( std::string(currentFile->GetListOfKeys()->At(nt)->GetName()));
			bgtreeNames.push_back( std::string(currentBGFile->GetListOfKeys()->At(nt)->GetName()));
			
		} 	
		

		//loop over all trees
		for(unsigned int itree= 0; itree<treeNames.size(); itree++){//,tnbg in zip(treeNames, treeNamesBG):
			//currentFile
			tree = (TTree*)currentFile->Get(treeNames.at(itree).c_str());
			treebg = (TTree*)currentBGFile->Get(bgtreeNames.at(itree).c_str());
			std::cout<<"currentFile tree name "<< tree->GetName()<<std::endl;;
			std::cout<<"currentBGFile tree name "<< treebg->GetName()<<std::endl;;			


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
			
			tree->SetBranchAddress((treeNames.at(itree)+"MCTauVisibleDaughters_pdg").c_str(), &MCTauVisibleDaughters_pdg, &bMCTauVisibleDaughters_pdg);
			tree->SetBranchAddress((treeNames.at(itree)+"MCTauVisibleDaughters").c_str(), &MCTauVisibleDaughters, &bMCTauVisibleDaughters);
			tree->SetBranchAddress((treeNames.at(itree)+"MCTauInvisibleDaughters_pdg").c_str(), &MCTauInvisibleDaughters_pdg, &bMCTauInvisibleDaughters_pdg);
			tree->SetBranchAddress((treeNames.at(itree)+"MCTauInvisibleDaughters").c_str(), &MCTauInvisibleDaughters, &bMCTauInvisibleDaughters);

			tree->SetBranchAddress((treeNames.at(itree)+"tauTLV").c_str(),&tauTLV,&btauTLV);
			tree->SetBranchAddress((treeNames.at(itree)+"indexOfMinTauPsi").c_str(), &indexOfMinTauPsi, &bindexOfMinTauPsi);

			//loop signal tree
			auto nevent = tree->GetEntries();
			//nevent = 1000;
			std::cout<<"Nentries "<< nevent<<std::endl;
			//zero counts
			Total_s = 0.;
			N_s = 0.;
			N_match = 0.;
			for(unsigned int i=0; i< N_s_cTheta.size(); i++){
				N_s_cTheta.at(i)=0.;
				N_match_cTheta.at(i)=0.;
				Total_s_cTheta.at(i)=0.;
			}
   			for (Int_t i=0;i<nevent;i++) {
      				tree->GetEvent(i);		

					if( !passAcceptance( MCf0, MCf1, MCf2, MCf3, MCf0_PDG, MCf1_PDG, MCf2_PDG, MCf3_PDG) ){
						//std::cout<<"FAIL ";
					 continue;
					}
					
						//std::cout<<"PASS "<<std::endl;
					
		
				bool found = false;
				std::string PARTICLETYPE = std::string(particletypeTag);
				if( isMuon && PARTICLETYPE.compare("MUON")==0 ){
					Total_s++;
					if(nTaus >= 1){
						N_s += 1.;
					}
					//do matching
					if( foundMatch( MCf2, *tauTLV, minTauPsi, psitau) ){
						N_match += 1.;
					}
					//do cTheta eff by bin
			
					found = foundMatch( MCf2, *tauTLV, minTauPsi, psitau);
					countByBin( nTaus, (MCf2_PDG/abs(MCf2_PDG)) *MCf2->CosTheta(), found, N_s_cTheta, N_match_cTheta, Total_s_cTheta, cThetaCuts);

					countByBin( nTaus, MCf2->P(), found, N_s_mom, N_match_mom, Total_s_mom, momCuts);
					
					countByBin( nTaus,  -(MCf2_PDG/abs(MCf2_PDG))*sin(MCf2->Theta()), found, N_s_sTheta, N_match_sTheta, Total_s_sTheta, sThetaCuts);


				}
				if(isTau && PARTICLETYPE.compare("TAU0")==0){
					Total_s += 1.;
					if(nTaus >= 1){
						N_s += 1.;
					}
					//do fsr removal & matching in tau
					if(foundPromptTauMatch( MCf2, MCf2_PDG, *MCTauVisibleDaughters, *MCTauInvisibleDaughters, *MCTauVisibleDaughters_pdg, *MCTauInvisibleDaughters_pdg, *tauTLV, minTauPsi,  psitau)){
						N_match += 1.;
					}
					found = foundPromptTauMatch( MCf2, MCf2_PDG, *MCTauVisibleDaughters, *MCTauInvisibleDaughters, *MCTauVisibleDaughters_pdg, *MCTauInvisibleDaughters_pdg, *tauTLV, minTauPsi,  psitau);
					countByBin( nTaus, MCf2->CosTheta(), found, N_s_cTheta, N_match_cTheta, Total_s_cTheta, cThetaCuts);
				}
				if(isTau && PARTICLETYPE.compare("TAU1")==0 && tauType == 1){
					Total_s += 1.;
					if(nTaus >= 1){
						N_s += 1.;
					}
					if(foundPromptTauMatch( MCf2, MCf2_PDG, *MCTauVisibleDaughters, *MCTauInvisibleDaughters, *MCTauVisibleDaughters_pdg, *MCTauInvisibleDaughters_pdg, *tauTLV, minTauPsi,  psitau)){
						N_match += 1.;
					}
					found = foundPromptTauMatch( MCf2, MCf2_PDG, *MCTauVisibleDaughters, *MCTauInvisibleDaughters, *MCTauVisibleDaughters_pdg, *MCTauInvisibleDaughters_pdg, *tauTLV, minTauPsi,  psitau);
					countByBin( nTaus, MCf2->CosTheta(), found, N_s_cTheta, N_match_cTheta, Total_s_cTheta, cThetaCuts);
				}
				if(isTau && PARTICLETYPE.compare("TAU2")==0 && tauType == 2){
					Total_s += 1.;
					if(nTaus >= 1){
						N_s += 1.;
					}
					if(foundPromptTauMatch( MCf2, MCf2_PDG, *MCTauVisibleDaughters, *MCTauInvisibleDaughters, *MCTauVisibleDaughters_pdg, *MCTauInvisibleDaughters_pdg, *tauTLV, minTauPsi,  psitau)){
						N_match += 1.;
					}
					found = foundPromptTauMatch( MCf2, MCf2_PDG, *MCTauVisibleDaughters, *MCTauInvisibleDaughters, *MCTauVisibleDaughters_pdg, *MCTauInvisibleDaughters_pdg, *tauTLV, minTauPsi,  psitau);
					countByBin( nTaus, MCf2->CosTheta(), found, N_s_cTheta, N_match_cTheta, Total_s_cTheta, cThetaCuts);
				}
				if(isTau && PARTICLETYPE.compare("TAU3")==0 && tauType == 3){
					Total_s += 1.;
					if(nTaus >= 1){
						N_s += 1.;
					}
					if(foundPromptTauMatch( MCf2, MCf2_PDG, *MCTauVisibleDaughters, *MCTauInvisibleDaughters, *MCTauVisibleDaughters_pdg, *MCTauInvisibleDaughters_pdg, *tauTLV, minTauPsi,  psitau)){
						N_match += 1.;
					}
					found = foundPromptTauMatch( MCf2, MCf2_PDG, *MCTauVisibleDaughters, *MCTauInvisibleDaughters, *MCTauVisibleDaughters_pdg, *MCTauInvisibleDaughters_pdg, *tauTLV, minTauPsi,  psitau);
					countByBin( nTaus, MCf2->CosTheta(), found, N_s_cTheta, N_match_cTheta, Total_s_cTheta, cThetaCuts);
				}
			 	if(isTau && PARTICLETYPE.compare("TAU4")==0 && tauType == 4){
					Total_s += 1.;
					if(nTaus >= 1){
						N_s += 1.;
					}
					if(foundPromptTauMatch( MCf2, MCf2_PDG, *MCTauVisibleDaughters, *MCTauInvisibleDaughters, *MCTauVisibleDaughters_pdg, *MCTauInvisibleDaughters_pdg, *tauTLV, minTauPsi,  psitau)){
						N_match += 1.;
					}
					found = foundPromptTauMatch( MCf2, MCf2_PDG, *MCTauVisibleDaughters, *MCTauInvisibleDaughters, *MCTauVisibleDaughters_pdg, *MCTauInvisibleDaughters_pdg, *tauTLV, minTauPsi,  psitau);
					countByBin( nTaus, MCf2->CosTheta(), found, N_s_cTheta, N_match_cTheta, Total_s_cTheta, cThetaCuts);
				}
				if(isElectron && PARTICLETYPE.compare("ELECTRON")==0){
					Total_s += 1.;

					if(nTaus >= 1){
						N_s += 1.;
					}
					if( foundMatch( MCf2, *tauTLV, minTauPsi, psitau) ){
						N_match += 1.;
					}
					found = foundMatch( MCf2, *tauTLV, minTauPsi, psitau);
					countByBin( nTaus, MCf2->CosTheta(), found, N_s_cTheta, N_match_cTheta, Total_s_cTheta, cThetaCuts);
				
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
			std::cout<<"Nentries "<< nevent<<std::endl;
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
					//countByBin( nTaus, MCf2.CosTheta(), found, N_s_cTheta, N_match_cTheta, Total_s_cTheta, cThetaCuts);
			}
			

		//	eff_s = N_s/Total_s;
		//	eff_b = N_b/Total_b;
		//	RR = 1. - eff_b;
			treeN = treedetails.at(treeDetailsItr).at(0);
			searchCone = treedetails.at(treeDetailsItr).at(1);
			isoCone = treedetails.at(treeDetailsItr).at(2);
			isoE = treedetails.at(treeDetailsItr).at(3);
		//	p = N_s/ (N_s+N_b);
		//	effp = eff_s * p;

			s_ratio = N_s/Total_s; //Ns/Ntot
			b_ratio = N_b/Total_b; //Nb/Ntot
			ds_ratio = sqrt( s_ratio*(1-s_ratio)/Total_s ); //error on sratio
		   db_ratio = sqrt( b_ratio*(1-b_ratio)/Total_b ); //error on bratio
			s_matchratio = N_match/Total_s; //Nmatch/Ntot
		   ds_matchratio = sqrt( s_matchratio*(1-s_matchratio)/ Total_s); //error on smatchratio
		   singleJetFakeProb = 1- sqrt(sqrt(1-b_ratio )); //binomial prob of a single quark jet creating a tau jet
		   singleJetFakeIneff = sqrt(sqrt(1-b_ratio)); //1- singlefakeprob
		   dsingleJetFakeProb = (1./4.) * sqrt( b_ratio/ ( Total_b * sqrt( 1 - b_ratio) ) )	;
		   optProd = singleJetFakeIneff*s_matchratio; //singleGetFakeIneff*s_matchratio
		   matchratio = N_match/N_s; //Nmatch/Ns (matching efficiency)
	
		
		//	std::cout<< eff_s<< " "<< eff_b<<" "<< RR << " "<< treeN<<" "<<searchCone<<" "<<isoCone<<" "<<isoE<<" "<<p<<" "<<effp<<" "<<std::endl;

			outputTree->Fill();
	
			treeDetailsItr++;
			
			if(treeDetailsItr >= treedetails.size()) break;

		}//end tree loop	

		
	}//end file loop
	outputFile->Write();
}
void Efficiency_Rejection(){

	gROOT->ProcessLine(".L ~/work/repos/ILDbench_WWqqlnu/source/src/loader.C+");

	std::vector<const char*> subsets{"S1","S2","B1"};
	std::vector<const char*> ptypes{"MUON", "ELECTRON", "TAU0", "TAU1", "TAU2", "TAU3", "TAU4"};
	int nFiles = 62;
	int nTreesPerFile = 50;
	Efficiency_RejectionRun(subsets[0], ptypes[0], subsets[2], nFiles, nTreesPerFile );//M0
	//Efficiency_RejectionRun(subsets[0], ptypes[2], subsets[2], nFiles, nTreesPerFile );//T0
	//Efficiency_RejectionRun(subsets[0], ptypes[3], subsets[2], nFiles, nTreesPerFile );//T1
	//Efficiency_RejectionRun(subsets[0], ptypes[4], subsets[2], nFiles, nTreesPerFile );//T2
	//Efficiency_RejectionRun(subsets[0], ptypes[5], subsets[2], nFiles, nTreesPerFile );//T3
	//Efficiency_RejectionRun(subsets[0], ptypes[6], subsets[2], nFiles, nTreesPerFile );//T4
	//Efficiency_RejectionRun(subsets[1], ptypes[1], subsets[2], nFiles, nTreesPerFile );//E0
	
}





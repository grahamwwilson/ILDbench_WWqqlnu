#ifndef _EVTPART_
#define _EVTPART_
#include "EVENT/MCParticle.h"
#include "EVENT/ReconstructedParticle.h"
#include "lcio.h"
#include "TTree.h"
#include "TH1D.h"
#include <vector>
#include <algorithm>
#include "TLorentzVector.h"
#include "TVector3.h"
#include <math.h>
#include <iostream>
#include <sstream>
using namespace lcio;
class eventVariables{

	//this will have 2 main components to populate
	//mcparticles and 1 set of jets
	//each instance should have a string classifier for plotting

	public:

	eventVariables(const char* variableSetName, int nfermion, int nlepton, int nJets, TTree*& tree);
	void setParticles(std::vector<MCParticle*> mcpartvec, std::vector<ReconstructedParticle*> jets );
	void initLocalTree();

	const char* _variableSetName{};
	int _nfermions{};
	int _nleptons{};
	unsigned int _nJets{};

	TTree* _localTree{};


	//monte carlo
	std::vector<MCParticle*> _mcpartvec{};
	std::vector<TLorentzVector*> _MCf{};
	std::vector<int> _MCfpdg{};
	TLorentzVector* _mcl{};
	TLorentzVector* _mcqq{};
	int _mclepCharge{};
	//mc lepton multiplicity info
	int _mclepTrkMult{};
	int _mclepPfoMult{};
	//event information
	bool _isTau{};
	bool _isMuon{};
	bool _isSignal{};//is this a signal event or background?


	//input jets
	std::vector<ReconstructedParticle*> _jets{};
	std::vector<TLorentzVector*> _tlvjets{};
	

	//mc jet tagging
	std::vector<int> _jetmctags{};
	bool _isMCTagValid{};
	

	//analysis tagging 
	std::vector<int> _jetanatags{};
	

	//physics quantities with mc jet tagging
	//this requires there to be valid tagging
	 TLorentzVector* _mctWl{};
	 TLorentzVector* _mctlep{};
	 TLorentzVector* _mctWqq{};
	 TLorentzVector* _mctNu{};
	 int _mctlepCharge{};
	 //CM TGC
	 std::vector<TLorentzVector*> _mctCMjets{};
	 TLorentzVector* _mctCMNu{};
	
	 double _mctWmProdAngle{};
	
	  
		
	//analysis tagging quantities
	TLorentzVector* _anaWl{};
	TLorentzVector* _analep{};
	TLorentzVector* _anaWqq{};
	TLorentzVector* _anaNu{};
	int _analepCharge{};
	//CM TGC
	std::vector<TLorentzVector*> _anaCMjets{};
	TLorentzVector* _anaCMNu{};

	double _anaWmProdAngle{};


	//methods used to populate event variables	
	void initMCVars(bool& isTau, bool& isMuon, int& mclepCharge, TLorentzVector*& mcl, TLorentzVector*& mcqq, std::vector<TLorentzVector*>& MCf, std::vector<int>& MCfpdg, int& mclepTrkMult, int& mclepPfoMult);
	
	//gets the FSP MCParticles from MC Lepton
	void exploreDaughterParticles(MCParticle* p , std::vector<MCParticle*>& FSP);

	// FSP MC Lepton Helper
	bool allChildrenAreSimulation(MCParticle* p);	
	
	// another FSP Lepton Helper
	void getMCLeptonMult(std::vector<MCParticle*>& FSPs, int& mclepTrkMult, int& mclepPfoMult);
	
	void initJetTLV(std::vector<TLorentzVector*>& jetvec);

	void setJetTags(std::vector<int>& localjettags, std::vector<int> tagset );

	void MCTagJets(std::vector<int>& jetmctags, bool& isMCTagValid, int& mctlepCharge);

	void computeRecoResultsFromTags(std::vector<int>& tagset, TLorentzVector*& Wl, TLorentzVector*& lep, TLorentzVector*& Wqq, TLorentzVector*& Nu); 
	
	void populateCMTLVs(std::vector<int>& tagset, TLorentzVector*& Wl, TLorentzVector*& Wqq, TLorentzVector*& Nu, std::vector<TLorentzVector*>& CMjets,  TLorentzVector*& CMNu );

	void getCosThetaW(int& lepCharge, TLorentzVector*& Wl, TLorentzVector*& Wqq, double& WmProdAngle);
	

	//printing stuff
	void printEventVariables();
	void printTLV(TLorentzVector* v);
	void printTLVVec( std::vector<TLorentzVector*> v);
	void printPDGVec(std::vector<int> v);
	void printReconstructedParticle(ReconstructedParticle* p);
	void printReconstructedParticleVec(std::vector<ReconstructedParticle*> v);

};
#endif

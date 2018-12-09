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
#include <math.h>
#include <iostream>

class eventVariables(){

	//this will have 2 main components to populate
	//mcparticles and 1 set of jets
	//each instance should have a string classifier for plotting

	public:

	eventVariables(const char* variableSetName, int nfermion, int nlepton, std::vector<MCParticle*> mcpartvec, std::vector<ReconstructedParticle*> jets, TTree* tree);

	const char* _variableSetName;
	int _nfermion;
	int _nlepton;

	//this class should also add to a main tree that is set created in main analysis code
	TTree* _localTree;

	//monte carlo
	std::vector<MCParticle*> _mcpartvec{};
	std::vector<TLorentzVector*> _MCf{};
	std::vector<int> _MCfpdg{};
	TLorentzVector* _mcl{};
	int _mclepCharge{};
	//event information
	bool _isTau{};
	bool _isMuon{};
	bool _isSignal{};//is this a signal event or background?


	//input jets
	std::vector<ReconstructedParticle*> _jets{};
	std::vector<TLorentzVector*> _tlvjets{};
	

	//mc jet tagging
	std::vector<int> _jetmctags{};
	bool isTagValid{};
	

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
	
	  
		
	//analysis tagging quantities
	TLorentzVectur* _anaWl{};
	TLorentzVector* _analep{};
	TLorentzVector* _anaWqq{];
	TLorentzVector* _anaNu{};
	int _analepCharge{};
	//CM TGC
	std::vector<TLorentzVector*> _anaCMjets{};
	TLorentzVector* _anaCMNu{};


	//methods used to populate event variables	
	void classifyEvent(bool& isTau, bool& isMuon, std::vector<TlorentzVector*>& MCf, std::vector<int>& MCfpdg);

	//printing stuff
	void printEventVariables();
	void printTLVVec( std::vector<TLorentzVector*> v);
	void printPDGVec(std::vector<TLorentzVector*> v);

};
#endif

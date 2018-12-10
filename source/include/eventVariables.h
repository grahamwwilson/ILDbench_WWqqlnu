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
using namespace lcio;
class eventVariables{

	//this will have 2 main components to populate
	//mcparticles and 1 set of jets
	//each instance should have a string classifier for plotting

	public:

	eventVariables(const char* variableSetName, int nfermion, int nlepton);
	void setParticles(std::vector<MCParticle*> mcpartvec, std::vector<ReconstructedParticle*> jets );

	const char* _variableSetName{};
	int _nfermions{};
	int _nleptons{};


	//monte carlo
	std::vector<MCParticle*> _mcpartvec{};
	std::vector<TLorentzVector*> _MCf{};
	std::vector<int> _MCfpdg{};
	TLorentzVector* _mcl{};
	TLorentzVector* _mcqq{};
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
	TLorentzVector* _anaWl{};
	TLorentzVector* _analep{};
	TLorentzVector* _anaWqq{};
	TLorentzVector* _anaNu{};
	int _analepCharge{};
	//CM TGC
	std::vector<TLorentzVector*> _anaCMjets{};
	TLorentzVector* _anaCMNu{};


	//methods used to populate event variables	
	void initMCVars(bool& isTau, bool& isMuon, int& _mclepCharge, TLorentzVector*& mcl, std::vector<TLorentzVector*>& MCf, std::vector<int>& MCfpdg);
	
	void initJetTLV(std::vector<TLorentzVector*>& jetvec);
	

	//printing stuff
	void printEventVariables();
	void printTLV(TLorentzVector* v);
	void printTLVVec( std::vector<TLorentzVector*> v);
	void printPDGVec(std::vector<int> v);

};
#endif

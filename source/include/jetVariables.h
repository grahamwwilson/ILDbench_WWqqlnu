#ifndef _JET_
#define _JET_
#include "variableSet.h"
#include "TTree.h"
#include "EVENT/ReconstructedParticle.h"
#include "lcio.h"
#include "TLorentzVector.h"
using namespace lcio;
class jetVariables{
	public:

	jetVariables(eventVariables*& evtvar, LCEvent*& evt, std::string inputJetCollectionName);
	void initLocalTree();

	LCEvent* _localEvt{};
	std::string _inputJetCollectionName{};
	eventVariables* _evtvar{};
	TTree* _localTree{};
	//local jets copy
	const char* _variableSetName{};
	unsigned int _nJets{};
	std::vector<ReconstructedParticle*> _jets{};
	std::vector<TLorentzVector*> _tlvjets{};

	double _logyMinus{};
	double _logyPlus{};
	std::vector<double> _jetMinPsi{}

	//MC tag jet variables
	int _mctlepPfoMult{};
	int _mctlepTrkMult{};
	int _mctUpPfoMult{};
	int _mctDwnPfoMult{};
	int _mctUpTrkMult{};
	int _mctDwnTrkMult{};


	//analysis jet variables
	int _analepPfoMult{};
	int _analepTrkMult{};



	void setLogYVariables(double& logyMinus, double& logyPlus);

	void setMCTJetMultiplicity(int& mctlepPfoMult, int& mctlepTrkMult, int& mctUpPfoMult, int& mctDwnPfoMult, int& mctUpTrkMult, int& mctDwnTrkMult);

	void setMCTMinPsi(std::vector<double>& minPsi);
	
	void setAnaJetMultiplicity();


};
#endif

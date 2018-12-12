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

	jetVariables(eventVariables*& evtvar);
	void initLocalTree();

	eventVariables* _evtvar{};
	TTree* _localTree{};
	//local jets copy
	std::vector<ReconstructedParticle*> _jets{};
	std::vector<TLorentzVector*> _tlvjets{};

	double _logym{};
	double _logyp{};

	//MC tag jet variables
	int _mctlepPfoMult{};
	int _mctlepTrkMult{};
	int _mctUpPfoMult{};
	int _mctDwnPfoMult{};
	int _mctUpTrkMult{};
	int _mctDwnTrkMult{};
	std::vector<double> mctjetMinPsi{}; 

	//analysis jet variables
	int _analepPfoMult{};
	int _analepTrkMult{};
	int _anajetMinPsi{};

};
#endif

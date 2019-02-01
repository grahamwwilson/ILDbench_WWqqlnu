#ifndef _TAUFIND_
#define _TAUFIND_
#include "EVENT/MCParticle.h"
#include "EVENT/ReconstructedParticle.h"
#include "EVENT/LCRelation.h"
#include "lcio.h"
#include "TTree.h"
#include <vector>
#include "TLorentzVector.h"
#include <math.h>
#include <iostream>
#include "overlayVariables.h"

using namespace lcio;
class tauFinderVariables{
	public:
	
	tauFinderVariables(const char* variableSetName, TTree*& tree);

	void setParticles(std::vector<ReconstructedParticle*>& taus, std::vector<LCRelation*>& pfo2mc);
	void initLocalTree();

	TTree* _localTree{};
	std::vector<LCRelation*> _pfo2mc{};
	const char* _variableSetName{};
	std::vector<ReconstructedParticle*> _taus{};
	std::vector<TLorentzVector*> _tlvtaus{};

	MCParticle* _mcTau{};
	TLorentzVector* _mcTauTlv{};

	//tau variables
	int _nTaus{};
	std::vector<int> _tauTrkMult{};
	std::vector<int> _tauPfoMult{};//total pfos trk+neutrals
	
	std::vector<int> _tauNOLTrks{};
	std::vector<int> _tauNOLPfos{};
	std::vector<double> _tauOLEFrac{};
	std::vector<double> _tauOLMFrac{};
	
	std::vector<double> _tauTrueFrac{};
	
	//mct tau
	std::vector<double> _tauPsi{};
	int _indexOfMinTauPsi{};
	double _minTauPsi{};

	void setMCTau(MCParticle*& mctau);
	void setTauVariables();
	void setTauOLVariables(std::vector<MCParticle*> mcpartvec); //quick fix throw in mcpartvec
	void setMCTTauVariables();
	TLorentzVector* createReconstructedParticleTLV(ReconstructedParticle* p);
	
	
	
};
#endif

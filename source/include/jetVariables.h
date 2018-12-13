#ifndef _JET_
#define _JET_
#include "eventVariables.h"
#include "TTree.h"
#include "EVENT/ReconstructedParticle.h"
#include "lcio.h"
#include "TLorentzVector.h"
#include "marlin/Processor.h"
#include "EVENT/LCCollection.h"
using namespace lcio;
class jetVariables{
	public:

	jetVariables(eventVariables*& evtvar, std::string inputJetCollectionName);
	void setParticles(LCEvent*& evt, std::vector<ReconstructedParticle*> jets, std::vector<TLorentzVector*> tlvjets);
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
	std::vector<double> _jetMaxCosPsi{};

	//MC tag jet variables
	int _mctlepPfoMult{};
	int _mctlepTrkMult{};
	int _mctUpPfoMult{};
	int _mctDwnPfoMult{};
	int _mctUpTrkMult{};
	int _mctDwnTrkMult{};
	double _mctlepMaxCosPsi{};
	double _mctUpMaxCosPsi{};
	double _mctDwnMaxCosPsi{};

	//analysis jet variables
	int _analepPfoMult{};
	int _analepTrkMult{};



	void setLogYVariables(double& logyMinus, double& logyPlus);

	void setMCTJetMultiplicity(int& mctlepPfoMult, int& mctlepTrkMult, int& mctUpPfoMult, int& mctDwnPfoMult, int& mctUpTrkMult, int& mctDwnTrkMult, double& mctlepMaxCosPsi, double& mctUpMaxCosPsi, double& mctDwnMaxCosPsi);

	void setMaxCosPsi(std::vector<double>& jetMaxCosPsi); 
	
	void setAnaJetMultiplicity(std::vector<int>& anatags, int& analepPfoMult, int& analepTrkMult);
	
	void printJetVariables();
	
	void printVec(std::vector<double> v);


};
#endif

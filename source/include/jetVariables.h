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
	jetVariables(const char* variableSetName, TTree*& tree);
	void setParticles(LCEvent*& evt, std::vector<ReconstructedParticle*> jets, std::vector<TLorentzVector*> tlvjets);
	void setParticles(std::vector<ReconstructedParticle*> jets, LCEvent*& evt, std::string collname);
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
	std::vector<TLorentzVector> _jetstlv{};

	double _logyMinus{};
	double _logyPlus{};
	double _yMinus{};
	double _yPlus{};
	std::vector<double> _jetMaxCosPsi{};
	int _jetLeastNTrks{}; //least tracks not including 0 tracks

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

	void setjetLeastTrks(int& jetLeastNTrks);

	void setMCTJetMultiplicity(int& mctlepPfoMult, int& mctlepTrkMult, int& mctUpPfoMult, int& mctDwnPfoMult, int& mctUpTrkMult, int& mctDwnTrkMult, double& mctlepMaxCosPsi, double& mctUpMaxCosPsi, double& mctDwnMaxCosPsi);

	void setMaxCosPsi(std::vector<double>& jetMaxCosPsi); 
	
	void setAnaJetMultiplicity(std::vector<int>& anatags, int& analepPfoMult, int& analepTrkMult);
	
	void printJetVariables();
	
	void printVec(std::vector<double> v);

	TLorentzVector* createReconstructedParticleTLV(ReconstructedParticle* p);
};
#endif

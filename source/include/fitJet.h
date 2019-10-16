
#ifndef _FITJETS_
#define _FITJETS_

#include "EVENT/MCParticle.h"
#include "EVENT/ReconstructedParticle.h"
#include "EVENT/LCRelation.h"
#include "lcio.h"
#include "TTree.h"
#include <vector>
#include "TLorentzVector.h"
#include <math.h>
#include <iostream>
#include "JetFitObject.h"
#include "NeutrinoFitObject.h"
#include "LeptonFitObject.h"
#include "ISRPhotonFitObject.h"
#include "MassConstraint.h"

//#include "overlayVariables.h"
#include <sstream>
using namespace lcio;
class fitJet{

	public:
	fitJet( int id,  TTree* tree);

	//void setParticles( std::vector<TLorentzVector*> jfos, std::vector<TLorentzVector*> lepjfos, TLorentzVector* nufo, TLorentzVector* gfo, double m1,double m2, double fitprob , double chi2 );// std::vector<ReconstructedParticle*>& remainpfos);//, std::vector<LCRelation*>& pfo2mc);
	//void setParticles( std::vector<JetFitObject*> jfos, std::vector<JetFitObject*> lepjfos, NeutrinoFitObject* nufo, ISRPhotonFitObject* gfo, MassConstraint& w, double fitprob, double chi2);
	void setParticles(std::vector<JetFitObject*> jfos, std::vector<LeptonFitObject*> lfos, std::vector<JetFitObject*> ljfos, NeutrinoFitObject* nufo, ISRPhotonFitObject* gfo, MassConstraint& w, double fitprob, double chi2, double nuz, double Eg);
	void initLocalTree();

	int _id{};
	double _fitprob{-1};
	double _chi2{-1};
	
	TTree* _localTree{};
	//qq pieces
	//int ntau{};
	std::vector<double> _qqPx{-999};
	std::vector<double> _qqPy{-999};
	std::vector<double> _qqPz{-999};
	std::vector<double> _qqE{-999};
	//std::vector<int> _nTrks{};
	//std::vector<int> _nPfos{};
	double _qqfitMass{-999};

	//lepton pieces
	std::vector<double> _lPx{-999};
	std::vector<double> _lPy{-999};
	std::vector<double> _lPz{-999};
	std::vector<double> _lE{-999};
	std::vector<double> _lq{-999}; //use this to determine track or neutral


	//store the nu pz / isr E calculations prefit
	double _nuPzISR{-999};
	double _gEISR{-999};
	

	//will probably need to eventually store track params/ k,theta,phi + matrix later

	//neutrino piece
	double _nuPx{-999};
	double _nuPy{-999};
	double _nuPz{-999};
	double _nuE{-999};

	double _lnufitMass{-999};

	//isr piece
	double _gPx{-999};
	double _gPy{-999};
	double _gPz{-999};
	double _gE{-999};

	
	
	//lets not store all tau pfo for now
	//std::vector<std::vector<double> > _tauPfoQ{};
	//std::vector<std::vector<double> >
	
	

//	const char* _variableSetName{};
//	std::vector<ReconstructedParticle*> _taus{};
//	std::vector<TLorentzVector> _tlvtaus{};
//	std::vector<ReconstructedParticle*> _remainpfos{};
//	std::vector<TLorentzVector> _tlvremainpfos{};
	


	//helper variable, mc matching is done in taufinder variables
	//just plug it in here dont recalculate opening angles
//	int _mcselindex = -1;
//	int _eselindex = -1;

	//tau selected by mc matching
//	std::vector<TLorentzVector> _mcselremainpfos{};
//	std::vector<ReconstructedParticle*> _mcselremainRP{};
	
	//tau selected by highest energy
//	std::vector<TLorentzVector> _eselremainpfos{};
//	std::vector<ReconstructedParticle*> _eselremainRP{};

	//flag if mcsel and esel select the same tau jet 1.0 = yes, 0.0 = no
//	double _esel_match_mcsel{};

	/*TLorentzVector* createReconstructedParticleTLV(ReconstructedParticle* p);
	void setMCSelIndex( int index );
	void setESelIndex();
	void populateRemainFromSelIndex(int selIndex, std::vector<TLorentzVector>& selremainpfos, std::vector<ReconstructedParticle*>& selremainRP );
	void evaluateSelection();
	*/
};
#endif

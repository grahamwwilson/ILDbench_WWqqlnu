
#ifndef _MCPART2_
#define _MCPART2_
#include "EVENT/MCParticle.h"
#include "EVENT/ReconstructedParticle.h"
#include "lcio.h"
#include "TTree.h"
#include <vector>
#include "TLorentzVector.h"
#include "TVector3.h"
#include <math.h>
#include <iostream>
#include <sstream>
#include "classifyTau.h"

using namespace lcio;

class mcVars{
	public:
	//mcVariables( const char* variableSetName, int nfermion, int nlepton, TTree*& tree);
	mcVars( int nfermion, int nlepton, TTree* tree);
	void setParticles(std::vector<MCParticle*>& mcpartvec);
	void initLocalTree();

	const char* _variableSetName{};
	int _nfermions{};
	int _nleptons{};
	TTree* _localTree{};

	std::vector<MCParticle*> _mcpartvec{};
	std::vector<MCParticle*> _MCPf{};
	std::vector<TLorentzVector*> _MCf{};
	//no more tlv its 
	
	std::vector<double> _MCfpx{};
	std::vector<double> _MCfpy{};
	std::vector<double> _MCfpz{};
	std::vector<double> _MCfE{};	

	//vtx info
	std::vector<double> _MCfprodVtxX{};
	std::vector<double> _MCfprodVtxY{};
	std::vector<double> _MCfprodVtxZ{};

	std::vector<double> _MCfendVtxX{};
	std::vector<double> _MCfendVtxY{};
	std::vector<double> _MCfendVtxZ{};

	//tau daughter info, no more tlv
	std::vector<double> _genTauVisPx{};
	std::vector<double> _genTauVisPy{};
	std::vector<double> _genTauVisPz{};
	std::vector<double> _genTauVisE{};
	std::vector<bool> _genTauVisVtxisNOTParentEnd{};

	//vis daughters vtx info
	std::vector<double> _genTauVisX{};
	std::vector<double> _genTauVisY{};
	std::vector<double> _genTauVisZ{};

	//vertexIsNotEndpointOfParent();
	std::vector<double> _genTauIPx{};
	std::vector<double> _genTauIPy{};
	std::vector<double> _genTauIPz{};
	std::vector<double> _genTauIE{};

	std::vector<int> _MCfpdg{};
	std::vector<TLorentzVector> _MCTauVisibleDaughters{};
	std::vector<int> _MCTauVisibleDaughters_pdg{};
	std::vector<double> _MCTauVisibleDaughters_charge{};
	std::vector<TLorentzVector> _MCTauInvisibleDaughters{};
	std::vector<int> _MCTauInvisibleDaughters_pdg{};

	TLorentzVector* _mcl{};
	TLorentzVector* _mcqq{};
	int _mclepCharge{};
	//mc lepton multiplicity info
	int _mclepTrkMult{};
	int _mclepPfoMult{};
	//event information
	int _isTau{};
	int _tauType{}; //0=not a tau event 1=muon 2=electron 3=had1p 4=had3p 5=other
	int _isMuon{};
	int _isElectron{};


	void initMCVars();
	
	//gets the FSP MCParticles from MC Lepton
	void exploreDaughterParticles(MCParticle* p , std::vector<MCParticle*>& FSP);

	// FSP MC Lepton Helper
	bool allChildrenAreSimulation(MCParticle* p);	
	
	// another FSP Lepton Helper
	void getMCLeptonMult(std::vector<MCParticle*>& FSPs);
	
	int getTauDecayMode(MCParticle* mctau);	
};


#endif

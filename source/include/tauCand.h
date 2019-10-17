
#ifndef _TAUCAND_
#define _TAUCAND_

#include "EVENT/MCParticle.h"
#include "EVENT/ReconstructedParticle.h"
#include "EVENT/LCRelation.h"
#include "lcio.h"
#include "TTree.h"
#include <vector>
#include "TLorentzVector.h"
#include <math.h>
#include <iostream>
#include <marlin/Global.h>
#include "gear/BField.h"
//#include "overlayVariables.h"
#include <sstream>
using namespace lcio;
class tauCand{

	public:
	tauCand(int id, TTree* tree);

	void setParticles( std::vector<ReconstructedParticle*>& taus);// std::vector<ReconstructedParticle*>& remainpfos);//, std::vector<LCRelation*>& pfo2mc);
	void initLocalTree();
	int _id{};

	
	TTree* _localTree{};
	
	//int ntau{};
	
	double _candPx{};
	double _candPy{};
	double _candPz{};
	double _candE{};
	int _candnTrks{};
	int _candnPfos{};

	//store all cand pfos, store track parameters covariance matrix, store pandora pfo cov matrix as well
	//neutrals
	std::vector<double> _candNeuPx{};
	std::vector<double> _candNeuPy{};
	std::vector<double> _candNeuPz{};
	std::vector<double> _candNeuE{};

	std::vector< std::vector<float> > _neuCov{};	

	//store the tracks but dont put them on the tree
	std::vector<Track*> _tracks{};
	double _bfield{};
	
	//tracks
	std::vector<double> _candTrkd0{};
	std::vector<double> _candTrkPhi{};
	std::vector<double> _candTrkOm{};
	std::vector<double> _candTrkz0{};
	std::vector<double> _candTrktlam{};

	std::vector< std::vector<float> >_trkCov{};

	

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

#ifndef _OVERLAY_
#define _OVERLAY_
#include "EVENT/MCParticle.h"
#include "EVENT/ReconstructedParticle.h"
#include "EVENT/LCRelation.h"
#include "IMPL/ReconstructedParticle.h"
#include "lcio.h"
#include "TTree.h"
#include <vector>
#include <algorithm>
#include "TLorentzVector.h"
#include <math.h>
#include <iostream>
#include <sstream>
using namespace lcio;

class overlayVariables{

	public:
		overlayVariables(const char* variableSetName, TTree*& tree, unsigned int nJets );
		void setParticles(std::vector<ReconstructedParticle*>& jets, std::vector<LCRelation*>& pfo2mc);
		void initLocalTree();

		TTree* _localTree{};	

		const char* _variableSetName{};
		unsigned int _nJets{};
		//std::string LCRelationName{};
		std::vector<LCRelation*> _pfo2mc{};

		//trimmed mcparticle list
		std::vector<MCParticle*> _MCOverlay{};
		std::vector<int> _MCOverlayIDs{};

		std::vector<ReconstructedParticle*> _jets{};
		std::vector<ReconstructedParticle*> _purgedJets{};//jets free from overlay
		std::vector<TLorentzVector*> _tlvpurgedJets{};

		std::vector< std::vector<ReconstructedParticle*> > _overlayParticles{};//populate from a set of reco jets
		std::vector< std::vector<TLorentzVector*> > _tlvoverlayParticles{};
		std::vector< TLorentzVector*> _tlvoverlaySum{};//4vector sum of the particles per jet

		void setMCOverlay(std::vector<MCParticle*>& MCOverlay, std::vector<int>& MCOverlayIDs, std::vector<MCParticle*>& mcpartvec );

		void setOverlayParticles(std::vector<ReconstructedParticle*>& overlayParticles, std::vector<TLorentzVector*>& tlvoverlayParticles, ReconstructedParticle*& purgedJet, TLorentzVector*& purgedTLVJet, const std::vector<ReconstructedParticle*>& jetParticles );
		
		void setOverlayparticlesLoop(std::vector<std::vector<ReconstructedParticle*> >& overlayParticles, std::vector<std::vector<TLorentzVector*> >& tlvoverlayParticles, std::vector<ReconstructedParticle*>& purgedJets, std::vector<TLorentzVector*>& tlvpurgedJets, std::vector<ReconstructedParticle*>& jets );

		bool particleIsOverlay(int id );

		TLorentzVector* createReconstructedParticleTLV(ReconstructedParticle* p);

		ReconstructedParticle* makePurgedJet( std::vector<ReconstructedParticle*> newParticles, std::vector<TLorentzVector*> newTLVs);
		
		void sumOverlayParticles(TLorentzVector*& tlvoverlaySum, std::vector<TLorentzVector*>& jetParticles);
	
		void sumOverlayParticlesLoop(std::vector<TLorentzVector*>& tlvoverlaySum, std::vector<std::vector<TLorentzVector*> >& tlvjets);

		void printOverlayVariables();

};
#endif

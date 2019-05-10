


#ifndef _JETOL_
#define _JETOL_

#include "EVENT/MCParticle.h"
#include "EVENT/ReconstructedParticle.h"
#include "EVENT/LCRelation.h"
#include "IMPL/ReconstructedParticleImpl.h"
#include "lcio.h"
#include "TTree.h"
#include <vector>
#include <algorithm>
#include "TLorentzVector.h"
#include <math.h>
#include <iostream>
#include <sstream>
using namespace lcio;

class jetOverlay{

	public:
		overlayVariables( const char* variableSetName, Tree*& tree );
		void setParticles(std::vector<ReconstructedParticle*>& jets, std::vector<LCRelation*>& pfo2mc, int njets);

		TTree* _localTree{};
		unsigned int _nJets{};
		const char* _variableSetName{};
		std::vector<MCParticle*> _MCOverlay{};
		std::vector<int> _MCOverlayIDs{};

		std:vector<ReconstructedParticle*> _jets{};
		std::vector< std::vector<ReconstructedParticle*> > _overlayParticles{};
		std::vector< std::vector<TLorentzVector> > _tlvoverlayParticles{};

		void setMCOverlay(std::vector<MCParticle*>& MCOverlay, std::vector<int>& MCOverlayIDs, std::vector<MCParticle*>& mcpartvec );	
		TLorentzVector* createReconstructedParticleTLV(ReconstructedParticle* p);
		void setOverlayParticles(std::vector<ReconstructedParticle*>& overlayParticles, std::vector<TLorentzVector*>& tlvoverlayParticles, ReconstructedParticle*& purgedJet, TLorentzVector*& purgedTLVJet, const std::vector<ReconstructedParticle*>& jetParticles );
		bool particleIsOverlay(int id );

};
#endif

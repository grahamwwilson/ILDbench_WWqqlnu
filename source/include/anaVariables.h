#ifndef _ANAVAR_
#define _ANAVAR_
#include "lcio.h"
#include "TLorentzVector.h"
#include "EVENT/ReconstructedParticle.h"
#include <iostream>
#include "TTree.h"
#include "eventVariables.h"
using namespace lcio;
class anaVariables{
	public:

		anaVariables(TTree*& tree, eventVariables*& evtVar);
		void setParticles(std::vector<ReconstructedParticle*>& jets);
		void initLocalTree();

		const char* _variableSetName{};
		unsigned int _nJets{};

		TTree* _localTree{};

		std::vector<ReconstructedParticle*> _jets{};
		std::vector<TLorentzVector*> _tlvjets{};


		//the analysis tags
		std::vector<int> _jetanatags{};
		int _analepCharge{};

		//variables
		TLorentzVector* _analepLeadingTracktlv{};

	
		void printAnaVariables();
	
		void setLeadingTrack(TLorentzVector*& analepLeadingTracktlv );

		void getLeptonJetCharge_byLeadingTrack(int& analepCharge );
	
		void identifyLeptonJet_bySeparation(std::vector<double>& jetMaxCosPsi, std::vector<int>& jetanatags);

		void identifyLeptonJet_byTrkMult(std::vector<int>& jetanatags);

		int tagGenericLepton();
	
		int tagGenericQuark();

		void setAnaEventVariables(eventVariables*& evtVar);
		
			

};
#endif

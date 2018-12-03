#ifndef _MVA_
#define _MVA_
#include "lcio.h"
#include "EVENT/MCParticle.h"
#include "EVENT/ReconstructedParticle.h"
#include "TString.h"
#include <iostream>
#include <cassert>
using namespace lcio;
class mva {

	public:


		mva();

		//training for lepton jet discrimination
		void makeTrainingVariables(ReconstructedParticle* signal, ReconstructedParticle* u_background, ReconstructedParticle* d_background);
				
		void writeTree();


		double s_isolation;
		double bu_isolation;
		double bd_isolation;
		 
		double s_tmultiplicity;
		double bu_tmultiplicity;
		double bd_tmultiplicity;
	
		double s_met;
		double bu_met;
		double bd_met;

		TTree* tree;
		TFile* f; 
		

} ;		

#endif

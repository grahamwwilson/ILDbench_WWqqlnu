

#include "mva.h"


mva::mva(){
	
	//init file
	f = new TFile("TrainingTree.root", "RECREATE");

	tree = new TTree("tree", "tree");

	tree->Branch("s_isolation", &s_isolation, "s_isolation/D");
	tree->Branch("bu_isolation", &bu_isolation,"bu_isolation/D");
	tree->Branch("bd_isolation", &bd_isolation,"bd_isolation/D");

	tree->Branch("s_tmultiplicity", &s_tmultiplicity, "s_tmultiplicity/D");
	tree->Branch("bu_tmultiplicity", &bu_tmultiplicity, "bu_tmultiplicity/D");
	tree->Branch("bd_tmultiplicity", &bd_tmultiplicity, "bd_tmultiplicity/D");

 	tree->Branch("s_met", &s_met, "s_met/D");
	tree->Branch("bu_met", &bu_met, "bu_met/D");
	tree->Branch("bd_met", &bd_met, "bd_met/D");
	
}
double mva::getIsoAngle(ReconstructedParticle* j1, ReconstructedParticle* j2){

	const double* j1mom = j1->getMomentum();
	const double* j2mom = j2->getMomentum();

	TVector3 v1(j1mom[0],j1mom[1],j1mom[2]);
	TVector3 v2(j2mom[0],j2mom[1],j2mom[2]);

	return v1.Angle(v2);
	
}
TLorentzVector* mva::boostPart(ReconstructedParticle* jet, ReconstructedParticle* part){

	const double* jmom = jet->getMomentum();
	const double* pmom = part->getMomentum();
	TLorentzVector *j,*pcm;
	j = new TLorentzVector();
	pcm = new TLorentzVector();
	j->SetXYZM(jmom[0],jmom[1],jmom[2],jet->getMass());
	pcm->SetXYZM(pmom[0],pmom[1],pmom[2],part->getMass());
	
	TVector3 jetBoost = j->BoostVector();
	jetBoost = -jetBoost;

	pcm->Boost(jetBoost);
		
	return pcm;
} 
double mva::getJetMET(ReconstructedParticle* jet){
	
	//boost all the particles to jetCM
	
	std::vector<ReconstructedParticle*> parts{};
	parts = jet->getParticles();
	std::vector<TLorentzVector*> CMparts(parts.size());

	for(unsigned int i=0; i<parts.size(); i++){
		CMparts.at(i) = boostPart(jet, parts.at(i));
	}

	// MET is sum px,py
	double px=0.0;
	double py=0.0;
	for(unsigned int i=0; i<CMparts.size(); i++){
		px += CMparts.at(i)->Px();
		py += CMparts.at(i)->Py();
	}
	
	return std::sqrt( px*px + py*py );

}
void mva::makeTrainingVariables(ReconstructedParticle* signal, ReconstructedParticle* u_background, ReconstructedParticle* d_background){
		
		std::vector<ReconstructedParticle*> s_parts{};
		std::vector<ReconstructedParticle*> bu_parts{};
		std::vector<ReconstructedParticle*> bd_parts{};

		s_parts = signal->getParticles();
		bu_parts = u_background->getParticles();
		bd_parts = d_background->getParticles();
		
		/* isolation variables */
		//iso angle is the smallest opening to the nearest jet
		double miniso; //[0,pi]
		double a1,a2;
		//signal iso
		a1 = getIsoAngle( signal, u_background );
		a2 = getIsoAngle( signal, d_background );
		s_isolation = (a1 >= a2) ? a2 : a1 ;
		
		a1 = getIsoAngle( u_background, signal );
		a2 = getIsoAngle( u_background, d_background);
		bu_isolation = (a1 >= a2) ? a2 : a1 ;

		a1 = getIsoAngle( d_background, signal );
		a2 = getIsoAngle( d_background, u_background);
		bd_isolation = (a1 >= a2) ? a2 : a1 ;
		/* end isolation */

		/* multiplicity variables */
		s_tmultiplicity = 0;
		bu_tmultiplicity = 0;
		bd_tmultiplicity = 0;
		//count tracks
		for(unsigned int i=0; i<s_parts.size(); i++){
			if(s_parts.at(i)->getCharge() != 0){
				s_tmultiplicity++;
			}			
		}		
		for(unsigned int i=0; i<bu_parts.size(); i++){
			if(bu_parts.at(i)->getCharge() != 0){
				bu_tmultiplicity++;
			}			
		}	
		for(unsigned int i=0; i<bd_parts.size(); i++){
			if(bd_parts.at(i)->getCharge() != 0){
				bd_tmultiplicity++;
			}			
		}	
		/* end mulitplicty */

		/*begin MET variables */
		//boost into jet CM, add up pT
		s_met = getJetMET( signal );
		bu_met = getJetMET( u_background );
		bd_met = getJetMET( d_background );
		/*end MET*/


		tree->Fill();

}


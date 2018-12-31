


#include "overlayVariables.h"

overlayVariables overlayVariables(){
	

}
void setMCOverlay(std::vector<MCParticle*>& MCOverlay, std::vector<int> MCOverlayIDs, std::vector<MCParticle*>& mcpartvec ){
	
	//this skims over mcparts and creates a list of all the overlay particles
	for( unsigned int i=0; i<mcpartvec.size(); i++){
		if(mcpartvec.at(i)->isOverlay()){
			MCOverlay.push_back(mcpartvec.at(i));
			MCOverlayIDs.push_back(mcpartvec.at(i)->id());
		}
	}

	//we will sort the ids but not the mcparts
	 std::sort (MCOverlayIDs.begin(), MCOverlayIDs.end());	

}
void setOverlayParticles(std::vector<ReconstructedParticle*>& overlayParticleSet, LCRelation*& pfo2mc, std::vector<ReconstructedParticle*>& jetParticles ){
		
	
}
		
void overlayVariables::setOverlayparticlesLoop(std::vector<ReconstructedParticle*>& overlayParticleSet, LCRelation*& pfo2mc, std::vector<ReconstructedParticle*>& jets ){
	for(unsigned int i=0; i< _nJets; i++){
		setOverlayParticles( overlayParticleSet, mcpartvec, pfo2mc, jets.at(i)->getParticles());
	}	

}

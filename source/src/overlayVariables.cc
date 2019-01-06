
#include "overlayVariables.h"

overlayVariables::overlayVariables(const char* variableSetName, TTree*& tree, unsigned int nJets){
	
	_localTree = tree;	

	_variableSetName = variableSetName;
	_nJets = nJets;

	//allocate vectors
	std::vector< std::vector<ReconstructedParticle*> > op(nJets);
	std::vector< std::vector<TLorentzVector*> > tlvop(nJets);
	std::vector<TLorentzVector*> sum(nJets);
	
	_overlayParticles = op;
	_tlvoverlayParticles = tlvop;
	_tlvoverlaySum = sum;
	
}
void overlayVariables::setParticles(std::vector<ReconstructedParticle*>& jets, std::vector<LCRelation*>& pfo2mc){

	_jets = jets;
	_pfo2mc = pfo2mc;
}
void overlayVariables::setMCOverlay(std::vector<MCParticle*>& MCOverlay, std::vector<int>& MCOverlayIDs, std::vector<MCParticle*>& mcpartvec ){
	
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
bool overlayVariables::particleIsOverlay(int id ){
	//find particle in LCRelation list
	for(unsigned int i=0; i<_pfo2mc.size(); i++){
			
		if( _pfo2mc.at(i)->getFrom()->id() == id ){
			//we have located pfo on the list look at  the matching mcparticle
			//is this id on the local overlay list?
			for(unsigned int j=0; j<_MCOverlayIDs.size(); j++){
				if( _MCOverlayIDs.at(j) == _pfo2mc.at(i)->getTo()->id() ){
					std::cout<<"found a particle: wgts " (int(_pfo2mc.at(i)->getWeight())%10000)/1000. <<" "<<(int(_pfo2mc.at(i)->getWeight())/10000)/1000. << std::endl;
					//this particle has overlay contribution
					//is the contribution significant?
					if(((int(_pfo2mc.at(i)->getWeight())%10000)/1000.) > 0.5 ){ return true; };
					if(((int(_pfo2mc.at(i)->getWeight())/10000)/1000.) > 0.5 ){ return true; };
				}
			}
			
		}	
	}
		return false;
}
TLorentzVector* overlayVariables::createReconstructedParticleTLV(ReconstructedParticle* p){
	TLorentzVector* t = new TLorentzVector();
	t->SetXYZM(p->getMomentum()[0], p->getMomentum()[1], p->getMomentum()[2], p->getMass());
	return t;
}
void overlayVariables::setOverlayParticles(std::vector<ReconstructedParticle*>& overlayParticles, std::vector<TLorentzVector*>& tlvoverlayParticles, const std::vector<ReconstructedParticle*>& jetParticles ){
		
	//loop over thejet particles, if it is overlay keep it
	for(unsigned int i=0; i< jetParticles.size(); i++){
		if(particleIsOverlay( jetParticles.at(i)->id() )){
			overlayParticles.push_back(jetParticles.at(i));
			tlvoverlayParticles.push_back( createReconstructedParticleTLV( jetParticles.at(i) ));
		}
	}


}
		
void overlayVariables::setOverlayparticlesLoop(std::vector<std::vector<ReconstructedParticle*> >& overlayParticles, std::vector<std::vector<TLorentzVector*> > tlvoverlayParticles, std::vector<ReconstructedParticle*>& jets ){
	for(unsigned int i=0; i< _nJets; i++){
		setOverlayParticles( overlayParticles.at(i), tlvoverlayParticles.at(i) , jets.at(i)->getParticles());
	}	

}
void overlayVariables::sumOverlayParticles(TLorentzVector*& tlvoverlaySum, std::vector<TLorentzVector*>& jetParticles){
	

	TLorentzVector* tlv = new TLorentzVector();
	for(unsigned int i =0; i<jetParticles.size(); i++){
		*tlv  += *jetParticles.at(i);
	}
	tlvoverlaySum = tlv;
}
void overlayVariables::sumOverlayParticlesLoop(std::vector<TLorentzVector*>& tlvoverlaySum, std::vector<std::vector<TLorentzVector*> >& tlvjets){
	
	for(unsigned int i=0; i< tlvoverlaySum.size(); i++){
		sumOverlayParticles( tlvoverlaySum.at(i), tlvjets.at(i) );
	}
	
}
void overlayVariables::printOverlayVariables(){
	//
	std::cout<<"overlayVariables: '"<<_variableSetName<<"'"<<std::endl;
	std::cout<<"# MC Overlay Particles: "<<_MCOverlayIDs.size()<<" # of Reconstructed Overlay Particles: ";
	unsigned int noparts=0;
	for(unsigned int i=0; i< _overlayParticles.size(); i++){
		noparts += _overlayParticles.at(i).size();
	}
	std::cout<<noparts<<std::endl;
	std::cout<<"overlaySum Per jet "<<std::endl;
	for(unsigned int i=0; i<_tlvoverlaySum.size(); i++){
		std::cout<<i<<" "<<_tlvoverlaySum.at(i)->Px()<<" "<<_tlvoverlaySum.at(i)->Py()<<" "<<_tlvoverlaySum.at(i)->Pz()<<" "<<_tlvoverlaySum.at(i)->E()<<" "<<_tlvoverlaySum.at(i)->M()<<std::endl;
	}
	

}
void overlayVariables::initLocalTree(){
	/*
	for(unsigned int i=0; i< _nJets; i++){
		std::stringstream name;
		name << _variableSetName << "mctCMjet"<<i;
		_localTree->Branch(name.str().c_str(),"TLorentzVector", &_mctCMjets.at(i),16000,0);
	}
	*/
}

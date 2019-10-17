#include "jetOverlay.h"



jetOverlay::jetOverlay(const char* variableSetName, TTree*& tree){
	


	_localTree = tree;	

	_variableSetName = variableSetName;


}
TLorentzVector* jetOverlay::createReconstructedParticleTLV(ReconstructedParticle* p){
	TLorentzVector* t = new TLorentzVector();
	t->SetXYZM(p->getMomentum()[0], p->getMomentum()[1], p->getMomentum()[2], p->getMass());
	return t;
}
void jetOverlay::setMCOverlay(std::vector<MCParticle*>& MCOverlay, std::vector<int>& MCOverlayIDs, std::vector<MCParticle*>& mcpartvec ){
	
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
void jetOverlay::setParticles(std::vector<ReconstructedParticle*>& jets, std::vector<LCRelation*>& pfo2mc, int njets, std::vector<MCParticle*>& mcpartvec){

	

	_jets = jets;
	_pfo2mc = pfo2mc;
	_nJets = njets;

	//clear vectors that are event dependent (using pushback)
	_MCOverlay.clear();
	_MCOverlayIDs.clear();

	

	for(unsigned int i=0; i<_overlayParticles.size(); i++){
		_overlayParticles.at(i).clear();
		_tlvoverlayParticles.at(i).clear();
	}

	std::vector<std::vector<ReconstructedParticle*> > op(njets);
	std::vector<std::vector<TLorentzVector> > tlop(njets);

	_overlayParticles = op;
	_tlvoverlayParticles = tlop;

	setMCOverlay( _MCOverlay, _MCOverlayIDs, mcpartvec);

}
bool jetOverlay::particleIsOverlay(int id ){
	//find particle in LCRelation list
	for(unsigned int i=0; i<_pfo2mc.size(); i++){
			
		if( _pfo2mc.at(i)->getFrom()->id() == id ){
			//we have located pfo on the list look at  the matching mcparticle
			//is this id on the local overlay list?
			for(unsigned int j=0; j<_MCOverlayIDs.size(); j++){
				if( _MCOverlayIDs.at(j) == _pfo2mc.at(i)->getTo()->id() ){
					//std::cout<<"found a particle: wgts "<< (int(_pfo2mc.at(i)->getWeight())%10000)/1000. <<" "<<(int(_pfo2mc.at(i)->getWeight())/10000)/1000. << std::endl;
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
void jetOverlay::setOverlayParticles(std::vector<ReconstructedParticle*>& overlayParticles, std::vector<TLorentzVector>& tlvoverlayParticles,  const std::vector<ReconstructedParticle*>& jetParticles ){
		
std::cout<<"jets from set overlay size 2 "<<  _jets.size() <<std::endl;
	//loop over thejet particles, if it is overlay keep it
	for(unsigned int i=0; i< jetParticles.size(); i++){
		if(particleIsOverlay( jetParticles.at(i)->id() )){
			overlayParticles.push_back(jetParticles.at(i));
			tlvoverlayParticles.push_back( *createReconstructedParticleTLV( jetParticles.at(i) ));
		}

	}



}
void jetOverlay::setOverlay(){
	

		for(unsigned int i=0; i< _nJets; i++){
			if(_nJets==1){
				setOverlayParticles( _overlayParticles.at(i), _tlvoverlayParticles.at(i), _jets);
			}
			else{
				setOverlayParticles( _overlayParticles.at(i), _tlvoverlayParticles.at(i) ,  _jets.at(i)->getParticles());
			}
		}	
	

}
void jetOverlay::initLocalTree(){
	std::string vsn(_variableSetName);
	_localTree->Branch((vsn+"JetOLtlv").c_str(), "vector<vector<TLorentzVector> >", &_tlvoverlayParticles);
}
void jetOverlay::printOL(){
	for(unsigned int i=0; i<_tlvoverlayParticles.size(); i++){
		std::cout<<"jet "<<i<<" size: "<< _tlvoverlayParticles.at(i).size()<<std::endl;
		for(unsigned int j=0; j<_tlvoverlayParticles.at(i).size(); j++){
			TLorentzVector t = _tlvoverlayParticles.at(i).at(j);
			std::cout<< t.Px()<< " "<<t.Py()<<" "<< t.Pz() <<std::endl;
		}
	}
}

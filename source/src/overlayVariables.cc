
#include "overlayVariables.h"

overlayVariables::overlayVariables(const char* variableSetName, TTree*& tree, unsigned int nJets, bool tagOpt){
	

	_tagOpt = tagOpt;
	_localTree = tree;	

	_variableSetName = variableSetName;
	_nJets = nJets;

	//allocate vectors
	std::vector< std::vector<ReconstructedParticle*> > op(nJets);
	std::vector< std::vector<TLorentzVector*> > tlvop(nJets);
	std::vector<TLorentzVector*> sum(nJets);

	std::vector<ReconstructedParticle*> cleanjets(nJets);
	std::vector<TLorentzVector*> cleantlv(nJets);
	_tlvpurgedJets = cleantlv;
	_purgedJets = cleanjets;
	
	_overlayParticles = op;
	_tlvoverlayParticles = tlvop;
	_tlvoverlaySum = sum;
	
}
void overlayVariables::setParticles(std::vector<ReconstructedParticle*>& jets, std::vector<LCRelation*>& pfo2mc){

	_jets = jets;
	_pfo2mc = pfo2mc;

	//clear vectors that are event dependent (using pushback)
	_MCOverlay.clear();
	_MCOverlayIDs.clear();

	for(unsigned int i=0; i<_nJets; i++){
		_overlayParticles.at(i).clear();
		_tlvoverlayParticles.at(i).clear();
	}

	_overlay_cosTheta.clear();
	_overlay_phi.clear();

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
					std::cout<<"found a particle: wgts "<< (int(_pfo2mc.at(i)->getWeight())%10000)/1000. <<" "<<(int(_pfo2mc.at(i)->getWeight())/10000)/1000. << std::endl;
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
void overlayVariables::makePurgedJet(ReconstructedParticle*& newJet ,TLorentzVector*& newJetTLV, std::vector<ReconstructedParticle*> newParticles, std::vector<TLorentzVector*> newTLVs){
	
	ReconstructedParticleImpl* jet = new ReconstructedParticleImpl();

	//newJet->setType(oldJet->getType());
	//newJet->setCovMatrix (oldJet->getCovMatrix())
	TLorentzVector* t = new TLorentzVector();
	for(unsigned int i=0; i< newTLVs.size(); i++){
		*t += *newTLVs.at(i);
	}
	jet->setEnergy( t->E());
	jet->setMass( t->M() );
	double* mom = new double[3];
	mom[0] = t->Px();
	mom[1] = t->Py();
	mom[2] = t->Pz();
	jet->setMomentum( mom );



	float charge =0.;
	for(unsigned int i=0; i< newParticles.size(); i++){
		charge  += newParticles.at(i)->getCharge();
		jet->addParticle( newParticles.at(i) );
	}
	jet->setCharge(charge); //sum of new tracks
	//newJet->setReferencePoint (oldJet->getReferencePoint()) //

	newJet = jet;
	newJetTLV = t;
}
void overlayVariables::setOverlayParticles(std::vector<ReconstructedParticle*>& overlayParticles, std::vector<TLorentzVector*>& tlvoverlayParticles, ReconstructedParticle*& purgedJet, TLorentzVector*& purgedTLVJet, const std::vector<ReconstructedParticle*>& jetParticles ){
		
	std::vector<ReconstructedParticle*> newParticles{};
	std::vector<TLorentzVector*> newTLVs{};
	//loop over thejet particles, if it is overlay keep it
	for(unsigned int i=0; i< jetParticles.size(); i++){
		if(particleIsOverlay( jetParticles.at(i)->id() )){
			overlayParticles.push_back(jetParticles.at(i));
			tlvoverlayParticles.push_back( createReconstructedParticleTLV( jetParticles.at(i) ));
		}
		else{
			newParticles.push_back(jetParticles.at(i));
			newTLVs.push_back( createReconstructedParticleTLV( jetParticles.at(i) ));
		}
	}

	//make the clean jet
	makePurgedJet( purgedJet, purgedTLVJet, newParticles, newTLVs);

}
		
void overlayVariables::setOverlayparticlesLoop(std::vector<std::vector<ReconstructedParticle*> >& overlayParticles, std::vector<std::vector<TLorentzVector*> >& tlvoverlayParticles, std::vector<ReconstructedParticle*>& purgedJets, std::vector<TLorentzVector*>& tlvpurgedJets, std::vector<ReconstructedParticle*>& jets ){
	for(unsigned int i=0; i< _nJets; i++){
		setOverlayParticles( overlayParticles.at(i), tlvoverlayParticles.at(i) , purgedJets.at(i), tlvpurgedJets.at(i), jets.at(i)->getParticles());
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
void overlayVariables::setTagVariables(std::vector<int>& tags){

		_jetTags = tags;
		//look at jets
		unsigned int ntrks{};
		TLorentzVector* qq = new TLorentzVector();
		for(unsigned int i=0; i<_overlayParticles.size(); i++){

				//loop and count tracks of the i-th jet
				ntrks = 0;
				for(unsigned int j=0; j<_overlayParticles.at(i).size(); j++){
					if(_overlayParticles.at(i).at(j)->getCharge() != 0){
						ntrks++;
					}
				}

				if( (abs(tags.at(i))<6) && ((abs(tags.at(i))%2) == 0) ){
					//uplike quark
					_upliketag_overlay = _tlvoverlaySum.at(i);
					_upliketag_overlay_ntracks = ntrks;
					_upliketag_overlay_Efrac = _tlvoverlaySum.at(i)->E()/_jets.at(i)->getEnergy();
					*qq += *_tlvoverlaySum.at(i);
				}
				if( (abs(tags.at(i))<6) && ((abs(tags.at(i))%2) != 0) ){
					//dwnlike quark
					_dwnliketag_overlay = _tlvoverlaySum.at(i);
					_dwnliketag_overlay_ntracks = ntrks;
					_dwnliketag_overlay_Efrac = _tlvoverlaySum.at(i)->E()/_jets.at(i)->getEnergy();
					*qq += *_tlvoverlaySum.at(i);
				}
				if( (abs(tags.at(i))>6) && (abs(tags.at(i))<17) ){
					//lepton
					_leptontag_overlay = _tlvoverlaySum.at(i);
					_leptontag_overlay_ntracks = ntrks;
					_leptontag_overlay_Efrac = _tlvoverlaySum.at(i)->E()/_jets.at(i)->getEnergy();
				}
		}
		_Wqq_overlay = qq;

}
void overlayVariables::setTotalVariables(){
	//distribution of all the particles from the overlay

		TLorentzVector t;
		for(unsigned int i=0; i<_tlvoverlaySum.size(); i++){
			t+= *_tlvoverlaySum.at(i);
		}
		_overlay_totalMass = t.M();
		_overlay_totalEnergy = t.E();

		for(unsigned int i=0; i< _tlvoverlayParticles.size(); i++){
			for(unsigned int j=0; j<_tlvoverlayParticles.at(i).size(); j++){
				_overlay_cosTheta.push_back( _tlvoverlayParticles.at(i).at(j)->CosTheta() );
				_overlay_phi.push_back( _tlvoverlayParticles.at(i).at(j)->Phi() );
			}
		}

}
void overlayVariables::printOverlayVariables(){
	//
	std::cout<<"overlayVariables: '"<<_variableSetName<<"'"<<std::endl;
	std::cout<<"# MC Overlay Particles: "<<_MCOverlayIDs.size()<<" # of Reconstructed Overlay Particles: ";
	unsigned int noparts=0;
	unsigned int notlvs=0;
	for(unsigned int i=0; i< _overlayParticles.size(); i++){
		noparts += _overlayParticles.at(i).size();
	}
	for(unsigned int i=0; i< _tlvoverlayParticles.size(); i++){
		notlvs = _tlvoverlayParticles.at(i).size();
	}
	std::cout<<noparts<<" # of Reconstructed Overlay TLVS: "<< notlvs<<std::endl;
	std::cout<<"overlay tlvs: "<<std::endl;
/*	TLorentzVector* t;
	for(unsigned int i=0; i< _tlvoverlayParticles.size();i++){
		for(unsigned int j=0; j< _tlvoverlayParticles.at(i).size();j++){
			t = _tlvoverlayParticles.at(i).at(j);			
			std::cout<< t->Px()<< " "<< t->Py() << " " << t->Pz() <<" "<< t->E()<<" "<< t->M()<<std::endl;
		}
	}*/
	std::cout<<"overlaySum Per jet "<<std::endl;
	for(unsigned int i=0; i<_tlvoverlaySum.size(); i++){
		std::cout<<i<<" "<<_tlvoverlaySum.at(i)->Px()<<" "<<_tlvoverlaySum.at(i)->Py()<<" "<<_tlvoverlaySum.at(i)->Pz()<<" "<<_tlvoverlaySum.at(i)->E()<<" "<<_tlvoverlaySum.at(i)->M()<<std::endl;
	}
	
	std::cout<<"purged jets :"<<std::endl;
	TLorentzVector* p;
	for(unsigned int i=0; i<_tlvpurgedJets.size(); i++){
		p = _tlvpurgedJets.at(i);
		std::cout<<i<<" "<<p->Px()<<" "<<p->Py()<<" "<<p->Pz()<<" "<<p->E()<<" "<<p->M()<<std::endl;
	}
	

}
void overlayVariables::initLocalTree(){
	/*
	for(unsigned int i=0; i< _nJets; i++){
		std::stringstream name;
		name << _variableSetName << "jet"<<i<<"_ovrSum";
		_localTree->Branch(name.str().c_str(),"TLorentzVector", &_tlvoverlaySum.at(i),16000,0);
	}

	for(unsigned int i=0; i< _nJets; i++){
		std::stringstream name;
		name << _variableSetName << "jet"<<i<<"_purged";
		_localTree->Branch(name.str().c_str(),"TLorentzVector", &_tlvpurgedJets.at(i),16000,0);
	}
	
	*/

	std::string vsn(_variableSetName);
	_localTree->Branch((vsn+"JetOLtlv").c_str(), "vector<vector<TLorentzVector> >", &_tlvoverlayParticles);

	//_localTree->Branch((vsn+"OLtlv").c_str(), "vector<TLorentzVector>", &_OLParticles);	
	//_localTree->Branch((vsn+"ovr_totalMass").c_str(), &_overlay_totalMass, (vsn+"ovr_totalMass/D").c_str());		
	//_localTree->Branch((vsn+"ovr_totalEnergy").c_str(), &_overlay_totalEnergy, (vsn+"ovr_totalEnergy/D").c_str());
	//_localTree->Branch((vsn+"ovr_cosTheta.").c_str(), &_overlay_cosTheta);
	//_localTree->Branch((vsn+"ovr_phi.").c_str(), &_overlay_phi);							

	if(_tagOpt){
		_localTree->Branch((vsn+"upliketag_ovr").c_str(),"TLorentzVector",&_upliketag_overlay, 16000,0);
		_localTree->Branch((vsn+"dwnliketag_ovr").c_str(),"TLorentzVector",&_dwnliketag_overlay, 16000,0);
		_localTree->Branch((vsn+"leptontag_ovr").c_str(),"TLorentzVector",&_leptontag_overlay, 16000,0);
		
		_localTree->Branch((vsn+"upliketag_ovr_ntrks").c_str(), &_upliketag_overlay_ntracks, (vsn+"upliketag_ovr_ntrks/I").c_str());		
		_localTree->Branch((vsn+"dwnliketag_ovr_ntrks").c_str(), &_dwnliketag_overlay_ntracks, (vsn+"dwnliketag_ovr_ntrks/I").c_str());
		_localTree->Branch((vsn+"leptontag_ovr_ntrks").c_str(), &_leptontag_overlay_ntracks, (vsn+"leptontag_ovr_ntrks/I").c_str());
				
		_localTree->Branch((vsn+"upliketag_ovr_Efrac").c_str(), &_upliketag_overlay_Efrac, (vsn+"upliketag_ovr_Efrac/D").c_str());
		_localTree->Branch((vsn+"dwnliketag_ovr_Efrac").c_str(), &_dwnliketag_overlay_Efrac, (vsn+"dwnliketag_ovr_Efrac/D").c_str());
		_localTree->Branch((vsn+"leptontag_ovr_Efrac").c_str(), &_leptontag_overlay_Efrac, (vsn+"leptontag_ovr_Efrac/D").c_str());	

		_localTree->Branch((vsn+"Wqqtag_ovr").c_str(), "TLorentzVector", &_Wqq_overlay, 16000,0);											

	}
		
	
}

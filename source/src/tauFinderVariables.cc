#include "tauFinderVariables.h"

tauFinderVariables::tauFinderVariables(const char* variableSetName, TTree*& tree){
	_localTree = tree;
	_variableSetName = variableSetName;
}
TLorentzVector* tauFinderVariables::createReconstructedParticleTLV(ReconstructedParticle* p){
	TLorentzVector* t = new TLorentzVector();
	t->SetXYZM(p->getMomentum()[0], p->getMomentum()[1], p->getMomentum()[2], p->getMass());
	return t;
}
void tauFinderVariables::setParticles(std::vector<ReconstructedParticle*>& taus, std::vector<LCRelation*>& pfo2mc){
	_taus = taus;//based on the number of taus allocate space for all the arrays
	_nTaus = (int) _taus.size();

	//std::vector<TLorentzVector*> tlv(_nTaus);
	std::vector< std::vector<double> > tlv(_nTaus);
	_tlvtaus = tlv;

	std::vector<int> tmult(_nTaus);
	_tauTrkMult = tmult;
	std::vector<int> pmult(_nTaus);
	_tauPfoMult = pmult;

	std::vector<int> olt(_nTaus);
	_tauNOLTrks = olt;
	std::vector<int> olp(_nTaus);
	_tauNOLPfos = olp;
	
	std::vector<double> ef(_nTaus);
	_tauOLEFrac = ef;

	std::vector<double> mctau(_nTaus);
	_tauPsi = mctau;

	std::vector<double> truefr(_nTaus);
	_tauTrueFrac = truefr;

	TLorentzVector* t;
	for(unsigned int i=0; i<_nTaus; i++){
		
	 	//_tlvtaus.at(i) = createReconstructedParticleTLV( _taus.at(i) );
		t = createReconstructedParticleTLV( _taus.at(i) );
		_tlvtaus.at(i) = new std::vector<double>{ t->Px(), t->Py(), t->Pz(), t->M() };
	}

	_pfo2mc = pfo2mc;

}
void tauFinderVariables:: setMCTau( MCParticle*& mcTau ){
	_mcTau = mcTau;
	_mcTauTlv = new TLorentzVector();
	_mcTauTlv->SetXYZM(mcTau->getMomentum()[0], mcTau->getMomentum()[1], mcTau->getMomentum()[2], mcTau->getMass() );
}
void tauFinderVariables::setTauVariables(){
	
	int n=0;
	int c=0;
	for(unsigned int i=0; i<_taus.size(); i++){
		std::vector<ReconstructedParticle*> tauparts = _taus.at(i)->getParticles();
		for(unsigned int j=0; j<tauparts.size(); j++){
			if(tauparts.at(j)->getCharge() != 0  ){
				c++;
			}
				n++;
		}
		//we looped over 1 tau reset c/n counts after saving
		_tauTrkMult.at(i) = c;
		_tauPfoMult.at(i) = n;
		n=0;
		c=0;
	}
}
void tauFinderVariables::setTauOLVariables(std::vector<MCParticle*> mcpartvec){
	//just use OL class
	overlayVariables* OLTau = new overlayVariables( _variableSetName, _localTree, _taus.size(), false);
	OLTau->setParticles(_taus, _pfo2mc);
	OLTau->setMCOverlay(OLTau->_MCOverlay, OLTau->_MCOverlayIDs, mcpartvec );
	OLTau->setOverlayparticlesLoop(OLTau->_overlayParticles, OLTau->_tlvoverlayParticles, OLTau->_purgedJets, OLTau->_tlvpurgedJets, _taus);
	OLTau->sumOverlayParticlesLoop(OLTau->_tlvoverlaySum, OLTau->_tlvoverlayParticles);
	OLTau->setTotalVariables();	
	
	//2d vec of  overlay particles, count multiplicity
	int n=0;
	int c=0;
	for(unsigned int i=0; i< OLTau->_overlayParticles.size(); i++){
		for(unsigned int j=0; j< OLTau->_overlayParticles.at(i).size(); j++){
			if( OLTau->_overlayParticles.at(i).at(j)->getCharge() != 0 ){
				c++;
			}
			n++;
		}
		_tauNOLTrks.at(i) = c;
		_tauNOLPfos.at(i) = n;
		c=0;
		n=0;
	}
	//look at overlay jet energy fraction
	for(unsigned int i=0; i< OLTau->_tlvoverlaySum.size(); i++){
		_tauOLEFrac.at(i) = OLTau->_tlvoverlaySum.at(i)->E()/_taus.at(i)->getEnergy();
	}

	//figure out visible MC energy
	std::vector<MCParticle*> taudaughters{};
	taudaughters = _mcTau->getDaughters();
	TLorentzVector MCtauVis;
	//loop over daughters, sum into 4vec visible particles
	for(unsigned int i=0; i< taudaughters.size(); i++){
		//sum visible components
		if( abs(taudaughters.at(i)->getPDG()) !=12 && abs(taudaughters.at(i)->getPDG()) != 14 && abs(taudaughters.at(i)->getPDG()) != 16 ){
			TLorentzVector visibledaughter;
			visibledaughter.SetXYZM(  taudaughters.at(i)->getMomentum()[0], taudaughters.at(i)->getMomentum()[1], taudaughters.at(i)->getMomentum()[2], taudaughters.at(i)->getMass());
			MCtauVis += visibledaughter;
		}
	}
	
	for(unsigned int i=0; i<OLTau->_tlvpurgedJets.size(); i++){
		_tauTrueFrac.at(i) = OLTau->_tlvpurgedJets.at(i)->E() / MCtauVis.E();
	}
}
void tauFinderVariables::setMCTTauVariables(){
	//find opening angle between tau& mcTau  acos(psi)
	TLorentzVector mc;
	mc.SetXYZM(  _mcTau->getMomentum()[0], _mcTau->getMomentum()[1], _mcTau->getMomentum()[2], _mcTau->getMass() );

	double cospsi{};
	double psi{};
	_minTauPsi = 999;
	for(unsigned int i=0; i< _tlvtaus.size(); i++){

		cospsi = mc.Vect().Dot( _tlvtaus.at(i)->Vect() )/ (mc.Vect().Mag() * _tlvtaus.at(i)->Vect().Mag() );
		psi = acos(cospsi);
		_tauPsi.at(i) = psi;	
		if(psi < _minTauPsi ){
			_minTauPsi = psi;
			_indexOfMinTauPsi = i;
		}

	}	
	
}
void tauFinderVariables::initLocalTree(){

	std::string vsn(_variableSetName);

	_localTree->Branch((vsn+"mcTau").c_str(),"TLorentzVector",&_mcTauTlv,16000,0);

/*	for(int i=0; i< _nTaus; i++){
		std::stringstream name;
		name << _variableSetName << "tauJet" << i;
		_localTree->Branch(name.str().c_str(),"TLorentzVector",&_tlvtaus.at(i),16000,0);
	}
*/
	_localTree->Branch((vsn+"tauTLV.").c_str(), &_tlvtaus);

	_localTree->Branch((vsn+"nTaus").c_str(),&_nTaus,(vsn+"nTaus/I").c_str());

	_localTree->Branch((vsn+"tauTrkMult").c_str(), &_tauTrkMult);
	_localTree->Branch((vsn+"tauPfoMult").c_str(), &_tauPfoMult);

	_localTree->Branch((vsn+"tauNOLTrks").c_str(), &_tauNOLTrks);
	_localTree->Branch((vsn+"tauNOLPfos").c_str(), &_tauNOLPfos);

	_localTree->Branch((vsn+"tauOLEFrac").c_str(), &_tauOLEFrac);
	_localTree->Branch((vsn+"tauOLMFrac").c_str(), &_tauOLMFrac);
	
	_localTree->Branch((vsn+"tauTrueFrac").c_str(), &_tauTrueFrac);

	_localTree->Branch((vsn+"tauPsi").c_str(), &_tauPsi);
	_localTree->Branch((vsn+"minTauPsi").c_str(), &_minTauPsi, (vsn+"minTauPsi/D").c_str());
	_localTree->Branch((vsn+"indexOfMinTauPsi").c_str(), &_indexOfMinTauPsi, (vsn+"indexOfMinTauPsi/I").c_str());
	
	

}

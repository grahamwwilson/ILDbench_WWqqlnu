#include "fitJet.h"

fitJet::fitJet(int id, TTree* tree){
	_localTree = tree;
	//_variableSetName = variableSetName;
	_id = id;
	initLocalTree();	
}
/*TLorentzVector* remainPfos::createReconstructedParticleTLV(ReconstructedParticle* p){
	TLorentzVector* t = new TLorentzVector();
	t->SetXYZM(p->getMomentum()[0], p->getMomentum()[1], p->getMomentum()[2], p->getMass());
	return t;
}*/
//void fitJet::setParticles( std::vector<TLorentzVector*> jfos, std::vector<TLorentzVector*> lepjfos, TLorentzVector* nufo, TLorentzVector* gfo, double m1, double m2, double fitprob, double chi2){// std::vector<ReconstructedParticle*>& remainpfos){
//void fitJet::setParticles( std::vector<JetFitObject*> jfos, std::vector<JetFitObject*> lepjfos, NeutrinoFitObject* nufo, ISRPhotonFitObject* gfo, MassConstraint& w, double fitprob, double chi2){
void fitJet::setParticles(std::vector<JetFitObject*> jfos, std::vector<LeptonFitObject*> lfos, std::vector<JetFitObject*> ljfos, NeutrinoFitObject* nufo, ISRPhotonFitObject* gfo, MassConstraint& w, double fitprob, double chi2, double nuz, double Eg){

///	ntau = taus.size();
//
	_fitprob = fitprob;
	_chi2 = chi2;

	int njfo = jfos.size();
	std::vector<double> px(njfo);
	std::vector<double> py(njfo);
	std::vector<double> pz(njfo);
	std::vector<double> E(njfo);
//	std::vector<int> ntrks(ntau);
//	std::vector<int> pfos(ntau);	

	for(unsigned int i=0; i<njfo; i++){
		px.at(i) = jfos.at(i)->getPx();
		py.at(i) = jfos.at(i)->getPy();
		pz.at(i) = jfos.at(i)->getPz();
		E.at(i) = jfos.at(i)->getE();
		
	}
	_qqPx =px;
	_qqPy = py;
	_qqPz = pz;
	_qqE = E;

//do lepton
	
	njfo = lfos.size()+ ljfos.size();
	std::vector<double> lpx{};
	std::vector<double> lpy{};
	std::vector<double> lpz{};
	std::vector<double> lE{};
	std::vector<double> lq{};
	
	for(unsigned int i=0; i< lfos.size(); i++){
		//double tpx =  doe the pxpypze work for LFO????????
		lpx.push_back(lfos.at(i)->getPx());
		lpy.push_back( lfos.at(i)->getPy());
		lpz.push_back( lfos.at(i)->getPz());
		lE.push_back( lfos.at(i)->getE());
		lq.push_back( fabs(lfos.at(i)->getParam(0))/lfos.at(i)->getParam(0) );	
	}
	for(unsigned int i=0; i<ljfos.size(); i++){
		lpx.push_back(ljfos.at(i)->getPx());
		lpy.push_back(ljfos.at(i)->getPy());
		lpz.push_back(ljfos.at(i)->getPz());
		lE.push_back(ljfos.at(i)->getE());
		lq.push_back( 0.);
	}
	_lPx = lpx;
	_lPy = lpy;
	_lPz = lpz;
	_lE = lE;
	_lq = lq;

//do neutrino
	_nuPx = nufo->getPx();
	_nuPy = nufo->getPy();
	_nuPz = nufo->getPz();
	_nuE = nufo->getE();

//do isr photon
	_gPx = gfo->getPx();
	_gPy = gfo->getPy();
	_gPz = gfo->getPz();
	_gE = gfo->getE();
	
	// set constrained masses directly
	_qqfitMass = w.getMass(1);
	_lnufitMass = w.getMass(2);
	
	_nuPzISR = nuz;
	_gEISR = Eg;

//	_nTrks = ntrks;
//	_nPfos = pfos;
	
/*	_taus = taus;
	std::vector<TLorentzVector> tlv( _taus.size() );
	_tlvtaus = tlv;
	for( unsigned int i=0; i< _tlvtaus.size(); i++ ){
		_tlvtaus.at(i) = *(createReconstructedParticleTLV(_taus.at(i)));
	}


	_remainpfos = remainpfos;
	std::vector<TLorentzVector> tlvr( _remainpfos.size() );
	_tlvremainpfos = tlvr;
	for( unsigned int i=0; i< _remainpfos.size(); i++){
		_tlvremainpfos.at(i) = *(createReconstructedParticleTLV(_remainpfos.at(i)));
	}

	//make fresh vector because we are going to use push_back
	std::vector<TLorentzVector> mcsel{};
	_mcselremainpfos = mcsel;

	std::vector<ReconstructedParticle*> mcrp{};
	_mcselremainRP = mcrp;
	
	std::vector<TLorentzVector> esel{};
	_eselremainpfos = esel;

	std::vector<ReconstructedParticle*> rmrp{};
	_eselremainRP = rmrp;
	
	_esel_match_mcsel = -1.;

	_mcselindex = -1;
	_eselindex = -1;
*/
}
/*void remainPfos::setMCSelIndex( int index ){
	_mcselindex = index;
}
void remainPfos::setESelIndex(){
	//index of highest energy tau
	if(_tlvtaus.size() == 0) return;	
	int EIndex=-1;
	double Emax = 0.;
	for(unsigned int i=0; i< _taus.size(); i++){
		if(_taus.at(i)->getEnergy() > Emax){
			Emax = _taus.at(i)->getEnergy();
			EIndex = i;
		}
	}
	
	_eselindex = EIndex;
}
//populate mcselremain based on mcselection
void remainPfos::populateRemainFromSelIndex(int selIndex, std::vector<TLorentzVector>& selremainpfos, std::vector<ReconstructedParticle*>& selremainRP ){
	if(_tlvtaus.size() == 0 ) return;

	//add all remain pfos immediately
	for(unsigned int i=0; i< _tlvremainpfos.size(); i++){
		selremainpfos.push_back( _tlvremainpfos.at(i) );
		selremainRP.push_back( _remainpfos.at(i) );
	}
	for(unsigned int i=0; i< _tlvtaus.size(); i++){
		if(i == selIndex) continue;
		//pull the tau apart and add each component
		std::vector<ReconstructedParticle*> unselectedComponents = _taus.at(i)->getParticles();
		for( unsigned int j=0; j< unselectedComponents.size(); j++){
			selremainpfos.push_back( *(createReconstructedParticleTLV( unselectedComponents.at(j))) );
			selremainRP.push_back( unselectedComponents.at(j) );
		}
		
	}
}
void remainPfos::evaluateSelection(){
	if( _mcselindex == -1 ){
		_esel_match_mcsel=-1.0;
	}
	else if( (_mcselindex == _eselindex)){
		_esel_match_mcsel=1.0;
	}
	else{
		_esel_match_mcsel=0.0;
	}

}*/
void fitJet::initLocalTree(){
	std::stringstream ss;
	ss<< _id;
	std::string id = ss.str();
//	_localTree->Branch(("ntau"+id).c_str(), &ntau);
	_localTree->Branch(("qqPx"+id).c_str(), "vector<double>", &_qqPx);
	_localTree->Branch(("qqPy"+id).c_str(), "vector<double>", &_qqPy);
	_localTree->Branch(("qqPz"+id).c_str(), "vector<double>", &_qqPz);
	_localTree->Branch(("qqE"+id).c_str(), "vector<double>", &_qqE);
//	_localTree->Branch(("tauNTrks"+id).c_str(), "vector<int>", &_nTrks);
//	_localTree->Branch(("tauNPfos"+id).c_str(), "vector<int>", &_nPfos);		
	_localTree->Branch(("lPx"+id).c_str(), "vector<double>", &_lPx);
	_localTree->Branch(("lPy"+id).c_str(), "vector<double>", &_lPy);
	_localTree->Branch(("lPz"+id).c_str(), "vector<double>", &_lPz);
	_localTree->Branch(("lE"+id).c_str(), "vector<double>", &_lE);
	_localTree->Branch(("lq"+id).c_str(), "vector<double>", &_lq);

	_localTree->Branch(("nuPzISR"+id).c_str(), &_nuPzISR);
	_localTree->Branch(("gEISR"+id).c_str(),&_gEISR);

	_localTree->Branch(("nuPx"+id).c_str(), &_nuPx);
	_localTree->Branch(("nuPy"+id).c_str(), &_nuPy);
	_localTree->Branch(("nuPz"+id).c_str(), &_nuPz);
	_localTree->Branch(("nuE"+id).c_str(), &_nuE);

	_localTree->Branch(("gPx"+id).c_str(), &_gPx);
	_localTree->Branch(("gPy"+id).c_str(), &_gPy);
	_localTree->Branch(("gPz"+id).c_str(), &_gPz);
	_localTree->Branch(("gE"+id).c_str(), &_gE);

	_localTree->Branch(("qqfitMass"+id).c_str(), &_qqfitMass);
	_localTree->Branch(("lnufitMass"+id).c_str(), &_lnufitMass);

	_localTree->Branch(("fitprob"+id).c_str(), &_fitprob);
	_localTree->Branch(("chi2"+id).c_str(), &_chi2);





/*std::string vsn(_variableSetName);
	_localTree->Branch((vsn+"mcselremainpfos").c_str(),"vector<TLorentzVector>", &_mcselremainpfos);
	_localTree->Branch((vsn+"eselremainpfos").c_str(),"vector<TLorentzVector>", &_eselremainpfos);
	_localTree->Branch((vsn+"eselmatchmcsel").c_str(),&_esel_match_mcsel, (vsn+"eselmatchmcsel/D").c_str() );
	*/	
}

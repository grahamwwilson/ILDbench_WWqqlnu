#include "remainPfos.h"

remainPfos::remainPfos( const char* variableSetName, TTree*& tree){
	_localTree = tree;
	_variableSetName = variableSetName;
}
TLorentzVector* remainPfos::createReconstructedParticleTLV(ReconstructedParticle* p){
	TLorentzVector* t = new TLorentzVector();
	t->SetXYZM(p->getMomentum()[0], p->getMomentum()[1], p->getMomentum()[2], p->getMass());
	return t;
}
void remainPfos::setParticles( std::vector<ReconstructedParticle*>& taus, std::vector<ReconstructedParticle*>& remainpfos){

	_taus = taus;
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

}
void remainPfos::setMCSelIndex( int index ){
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

}
void remainPfos::initLocalTree(){
	std::string vsn(_variableSetName);
	_localTree->Branch((vsn+"mcselremainpfos").c_str(),"vector<TLorentzVector>", &_mcselremainpfos);
	_localTree->Branch((vsn+"eselremainpfos").c_str(),"vector<TLorentzVector>", &_eselremainpfos);
	_localTree->Branch((vsn+"eselmatchmcsel").c_str(),&_esel_match_mcsel, (vsn+"eselmatchmcsel/D").c_str() );
		
}

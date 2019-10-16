#include "tauCand.h"

tauCand::tauCand(int id, TTree* tree){
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
void tauCand::setParticles( std::vector<ReconstructedParticle*>& taus){// std::vector<ReconstructedParticle*>& remainpfos){
	//size should alwasy be 1
	int ntau = taus.size();
	std::vector<double> px(ntau);
	std::vector<double> py(ntau);
	std::vector<double> pz(ntau);
	std::vector<double> E(ntau);
	std::vector<int> ntrk(ntau);
	std::vector<int> pfos(ntau);	

	std::vector<double> nepx{};
	std::vector<double> nepy{};
	std::vector<double> nepz{};
	std::vector<double> neE{};

	std::vector<std::vector<float> > neCovs{};
        std::vector<float> neCov{};

	std::vector<double> trd0{};
	std::vector<double> trphi{};
	std::vector<double> trom{};
	std::vector<double> trz0{};
	std::vector<double> trtl{};
	
	std::vector< std::vector<float> > trCovs{};
	 std::vector<float> trCov{};

	std::vector<Track*> marlinTrks{};

	//units for track P calcutions
	double BField = marlin::Global::GEAR->getBField().at(gear::Vector3D(0.,0.,0.)).z();
	_bfield = BField;
	const double c = 2.99792458e8; // m*s^-1        
  	const double mm2m = 1e-3;
  	const double eV2GeV = 1e-9;
  	const double eB = BField*c*mm2m*eV2GeV;

	//there should always only be 1 candidate on the vector
	for(unsigned int i=0; i<taus.size(); i++){
		px.at(i) = taus.at(i)->getMomentum()[0];
		py.at(i) = taus.at(i)->getMomentum()[1];
		pz.at(i) = taus.at(i)->getMomentum()[2];
		E.at(i) = taus.at(i)->getEnergy();
		//count multiplicity
		pfos.at(i) = taus.at(i)->getParticles().size();
	        ntrk.at(i) = 0;
		std::vector<ReconstructedParticle*> parts = taus.at(i)->getParticles();
		std::vector<Track*> trks{};
		for(unsigned int j=0; j< parts.size(); j++){
			//get the pfos and cov matrix
			if(parts.at(j)->getCharge() == 0){
				nepx.push_back(parts.at(j)->getMomentum()[0]);
				nepy.push_back(parts.at(j)->getMomentum()[1]);
				nepz.push_back(parts.at(j)->getMomentum()[2]);
				neE.push_back(parts.at(j)->getEnergy());
				const std::vector<float> tempcov = parts.at(j)->getCovMatrix();
				neCov = tempcov;					
			}
			if( parts.at(j)->getCharge() != 0	){
				//get tracks and cov matrix
				 trks = parts.at(j)->getTracks();	
				ntrk.at(i) = ntrk.at(i)+1;
				Track* tP;
				double maxP =0.;
				//loop over tracks find highest P track
				for(unsigned int k=0; k<trks.size(); k++){
					Track* t = trks.at(k); 
					double omega = t->getOmega();
					double q = omega/fabs(omega);	
					double pt = q*eB/omega;
					double tpz = pt*t->getTanLambda();
					if( sqrt(pt*pt + tpz*tpz) > maxP ){
						maxP = sqrt(pt*pt + tpz*tpz);
						tP = t;
					} 
				}
				//save stuff from highest P track
				trd0.push_back( tP->getD0() );
				trphi.push_back(tP->getPhi() );
				trom.push_back(tP->getOmega() );
				trz0.push_back(tP->getZ0() );
				trtl.push_back(tP->getTanLambda() );
				//save the trk
				marlinTrks.push_back(tP);			
				//make a copy of the const
				const std::vector<float> tempcov = tP->getCovMatrix();			
				trCov = tempcov ;
			}//end charge check
			//add all the cov matrix
			 trCovs.push_back( trCov );
			 neCovs.push_back( neCov );
		}//end parts loop

	}//end loop over all taus
	if(taus.size()>0){
	_candPx =px.at(0);
	_candPy = py.at(0);
	_candPz = pz.at(0);
	_candE = E.at(0);
	_candnTrks = ntrk.at(0);
	_candnPfos = pfos.at(0);
	}
	else{	
	_candPx = 999;
	_candPy = 999;
	_candPz = 999;
	_candE = 999;
	_candnTrks = -1;
	_candnPfos = -1;

	}
	_candNeuPx = nepx;
	_candNeuPy = nepy;
	_candNeuPz = nepz;
	_candNeuE = neE;
	_neuCov = neCovs;

	_candTrkd0 = trd0;
	_candTrkPhi = trphi;
	_candTrkOm = trom;
	_candTrkz0 = trz0;
	_candTrktlam = trtl;
	_trkCov = trCovs;
	
	_tracks = marlinTrks;


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
void tauCand::initLocalTree(){
	std::stringstream ss;
	ss<< _id;
	std::string id = ss.str();

	//_localTree->Branch("ntau", &ntau, "ntau/I");
	_localTree->Branch(("candPx"+id).c_str(), &_candPx);
	_localTree->Branch(("candPy"+id).c_str(), &_candPy);
	_localTree->Branch(("candPz"+id).c_str(), &_candPz);
	_localTree->Branch(("candE"+id).c_str(), &_candE);
	_localTree->Branch(("candNTrks"+id).c_str(), &_candnTrks);
	_localTree->Branch(("candNPfos"+id).c_str(),  &_candnPfos);		

	_localTree->Branch(("candNeuPx"+id).c_str(), "vector<double>", &_candNeuPx);
	_localTree->Branch(("candNeuPy"+id).c_str(), "vector<double>", &_candNeuPy);
	_localTree->Branch(("candNeuPz"+id).c_str(), "vector<double>", &_candNeuPz);
	_localTree->Branch(("candNeuE"+id).c_str(), "vector<double>", &_candNeuE);
//	_localTree->Branch(("candNeuCov"+id).c_str(), "vector<vector<float> >" ,&_neuCov);

	_localTree->Branch(("candTrkd0"+id).c_str(), "vector<double>", &_candTrkd0);
	_localTree->Branch(("candTrkPhi"+id).c_str(), "vector<double>", &_candTrkPhi);
	_localTree->Branch(("candTrkOm"+id).c_str(), "vector<double>", &_candTrkOm);
	_localTree->Branch(("candTrkz0"+id).c_str(), "vector<double>", &_candTrkz0);
	_localTree->Branch(("candTrktlam"+id).c_str(), "vector<double>", &_candTrktlam);
	_localTree->Branch(("candTrkCov"+id).c_str(), "vector<vector<float> >",&_trkCov);
/*std::string vsn(_variableSetName);
	_localTree->Branch((vsn+"mcselremainpfos").c_str(),"vector<TLorentzVector>", &_mcselremainpfos);
	_localTree->Branch((vsn+"eselremainpfos").c_str(),"vector<TLorentzVector>", &_eselremainpfos);
	_localTree->Branch((vsn+"eselmatchmcsel").c_str(),&_esel_match_mcsel, (vsn+"eselmatchmcsel/D").c_str() );
	*/	
}

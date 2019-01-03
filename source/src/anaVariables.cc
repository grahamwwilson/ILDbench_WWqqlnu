
#include "anaVariables.h"

anaVariables::anaVariables(TTree*& tree, eventVariables*& evtVar ){

	_localTree = tree;
	_variableSetName = evtVar->_variableSetName;
	_nJets = evtVar->_nJets;

	std::vector<int> temp(_nJets);
	_jetanatags = temp;
	

}
void anaVariables::setParticles(std::vector<ReconstructedParticle*>& jets ){
	_jets = jets;
}
int anaVariables::tagGenericQuark(){
	return 1;
}
int anaVariables::tagGenericLepton(){
	return 13;
}
void anaVariables::identifyLeptonJet_byTrkMult(std::vector<int>& jetanatags){
	unsigned int indexofminjet = 999;
	int minTracks = 999999;
	int countTracks=0;
	std::vector<ReconstructedParticle*> _parts{};
	for(unsigned int i=0; i<_jets.size(); i++){
		_parts = _jets.at(i)->getParticles();
		//count the tracks 
		for(unsigned int j=0; j<_parts.size(); j++){
			if( _parts.at(j)->getCharge() != 0){
				countTracks++;
			}
		}//end count
		if( countTracks < minTracks ){
			indexofminjet = i;
			minTracks = countTracks;
		}
		//reset for next jet
		countTracks = 0;
	}
	
	//do tagging
	for(unsigned int i=0; i<jetanatags.size(); i++){
		if( i == indexofminjet){
			jetanatags.at(i) = tagGenericLepton();
		}
		else{
			jetanatags.at(i) = tagGenericQuark();
		}
	}
	
}
void anaVariables::identifyLeptonJet_bySeparation(std::vector<double>& jetMaxCosPsi, std::vector<int>& jetanatags){
	//jetMaxCosPsi comes from jet variables
	//determine the min of each max
	double minMaxCosPsi = 999;
	unsigned int minindex = 999;
	for(unsigned int i=0; i<jetMaxCosPsi.size(); i++){
		if( jetMaxCosPsi.at(i) < minMaxCosPsi){
			minMaxCosPsi = jetMaxCosPsi.at(i);
			minindex = i;
		}
	}
	//tag min as lepton	
	for( unsigned int i=0; i<jetanatags.size(); i++){
		if( i == minindex){
			jetanatags.at(i) = tagGenericLepton();
		}
		else{
			jetanatags.at(i) = tagGenericQuark();
		}
	}
}

//needs to already be tagged
void anaVariables::getLeptonJetCharge_byLeadingTrack(int& analepCharge ){
		
	//use lepton tags to highest momentum charged particle in jet
	std::vector<ReconstructedParticle*> _parts{};
	for(unsigned int i=0; i<_jetanatags.size(); i++){
		if( abs(_jetanatags.at(i)) > 6 && abs(_jetanatags.at(i)) < 18 ){
			_parts = _jets.at(i)->getParticles();
			//loop over particles

			double maxP = 0;
			for(unsigned int j=0; j<_parts.size(); j++){
				if(_parts.at(j)->getCharge() != 0){
					
					const double* p = _parts.at(j)->getMomentum();
					double P = std::sqrt( p[0]*p[0] + p[1]*p[1] + p[2]*p[2] );
					if(P > maxP){
						maxP = P;
						analepCharge = _parts.at(j)->getCharge(); 
					}		
			
				}
			}
			return;

		}
	}
}
void anaVariables::setLeadingTrack(TLorentzVector*& analepLeadingTracktlv ){
	
	//use mctags to find lepton jet, get the highest momentum track
	std::vector<ReconstructedParticle*> _parts{};
	for(unsigned int i=0; i<_jetanatags.size(); i++){
		if( abs(_jetanatags.at(i)) > 6 && abs(_jetanatags.at(i)) < 18 ){
			_parts = _jets.at(i)->getParticles();
			//loop over particles

			double maxP = 0;
			int maxPindex = -1;
			for(unsigned int j=0; j<_parts.size(); j++){
				if(_parts.at(j)->getCharge() != 0){
					
					const double* p = _parts.at(j)->getMomentum();
					double P = std::sqrt( p[0]*p[0] + p[1]*p[1] + p[2]*p[2] );
					if(P > maxP){
						maxP = P;
						maxPindex = j;
					}		
			
				}
			}
			//if we find a leading track save it
			if(maxPindex==-1){
				 std::cout<<"no leading track!"<<std::endl;
				 analepLeadingTracktlv = new TLorentzVector();
				 analepLeadingTracktlv->SetXYZM(-1,-1,-1,-1);
				 return;
			}
			else{
				const double* mom = _parts.at(maxPindex)->getMomentum();
				analepLeadingTracktlv = new TLorentzVector();
				analepLeadingTracktlv->SetXYZM(mom[0],mom[1],mom[2],_parts.at(maxPindex)->getMass());

			}
			return;

		}
	}

}
void anaVariables::setAnaEventVariables(eventVariables*& evtVar){

	evtVar->setJetTags( evtVar->_jetanatags, _jetanatags );
	evtVar->computeRecoResultsFromTags(_jetanatags, evtVar->_anaWl,evtVar->_analep, evtVar->_anaWqq, evtVar->_anaNu);
	evtVar->populateCMTLVs(_jetanatags, evtVar->_anaWl, evtVar->_anaWqq, evtVar->_anaNu, evtVar->_anaCMjets, evtVar->_anaCMNu); 

}
void anaVariables::printAnaVariables(){
	std::cout<<"anaVariables: '"<<_variableSetName<<"'"<<std::endl;
	std::cout<<"ana tagged charge "<<_analepCharge<<std::endl;
	std::cout<<"leading lepton track tlv: "<<std::endl;
	std::cout<<_analepLeadingTracktlv->Px()<<" "<<_analepLeadingTracktlv->Py()<<" "<<_analepLeadingTracktlv->Pz()<<" "<<_analepLeadingTracktlv->E()<<" "<<_analepLeadingTracktlv->M()<<std::endl;

}
void anaVariables::initLocalTree(){
			std::string vsn(_variableSetName);
			_localTree->Branch((vsn+"analepLeadingTracktlv").c_str(),"TLorentzVector",&_analepLeadingTracktlv,16000,0);
			_localTree->Branch((vsn+"analepCharge").c_str(), &_analepCharge,(vsn+"analepCharge/I").c_str());

}


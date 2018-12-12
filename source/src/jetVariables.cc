#include "jetVariables.h"


jetVariables::jetVariables(eventVariables*& evtvar, LCEvent*& evt, std::string inputJetCollectionName){
	_evtvar=evtvar;
	_localTree = evtvar->_localTree;

	_localEvt = evt;
	_inputJetCollectionName = inputJetCollectionName;

	//init rest of local stuff
	_variableSetName = evtvar->_variableSetName;
	_nJets = evtvar->_nJets;
	_jets = evtvar->_jets;
	_tlvjets = evtvar->_tlvjets;

	//init vector size
	std::vector<double> temp(_nJets);
 	_jetMinPsi = temp; 


}
void jetVariables::getLogYVariables(double& logyMinus, double& logyPlus){
	yMinus =(double) std::log( evt->getCollection(_inputJetCollectionName)->getParameters().getFloatVal( "y_{n-1,n}" ));
    yPlus  =(double) std::log(evt->getCollection(_inputJetCollectionName)->getParameters().getFloatVal( "y_{n,n+1}" ));
}
void jetVariables::setMCTJetMultiplicity( int& mctlepPfoMult, int& mctlepTrkMult, int& mctUpPfoMult, int& mctDwnPfoMult, int& mctUpTrkMult, int& mctDwnTrkMult ){

	//mctagged jets must already be populated in evt variables

	std::vector<int> _localmctTags = _evtvar->_jetmctags;

	std::vector<int> _pfoMult(_nJets);
	std::vector<int> _trkMult(_nJets);
	int pfoCount = 0;
	int trkCount = 0;
	//first loop over each jet and get charge and pfo multiplicities
	for(unsigned int i=0; i<_jets.size(); i++){
		std::vector<ReconstructedParticle*> _jetParts = _jets.at(i)->getParticles();
		for(unsigned int j=0; j< _jetparts.size(); j++){
			if( _jetparts.at(i)->getCharge() != 0){
				trkCount++;
			}
			pfoCount++;
		}
		_pfoMult.at(i) = pfoCount;
		_trkMult.at(i) = trkCount;
		pfoCount = 0;
		trkCount = 0;
	}
	
	//loop over the tags and assign mults to corresponding variables
	for(unsigned int i=0; i< _localmctTags.size(); i++){
		//is it a quark?
		if( abs(_localmctTags.at(i)) < 6 ){
			//is it uplike or downlike?
			if( abs(_localmctTags.at(i)) % 2 == 0){
				//its uplike
				mctUpTrkMult = _trkMult.at(i);
				mctUpPfoMult = _pfoMult.at(i);
			}
			else{
				//its downlike
				mctDwnTrkMult = _trkMult.at(i);
				mctDwnPfoMult = _pfoMult.at(i);
			}
		}
		else{
		//its a lepton
			mctlepTrkMult = _trkMult.at(i);
			mctlepPfoMult = _pfoMult.at(i);
		}

	}

}
void jetVariables::setMinPsi(std::vector<double>& minPsi){
		

}
	

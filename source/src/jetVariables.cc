#include "jetVariables.h"


jetVariables::jetVariables(eventVariables*& evtvar, std::string inputJetCollectionName){
	_evtvar=evtvar;
	_localTree = evtvar->_localTree;

	_inputJetCollectionName = inputJetCollectionName;

	//init rest of local stuff
	_variableSetName = evtvar->_variableSetName;
	_nJets = evtvar->_nJets;
	

	//init vector size
	std::vector<double> temp(_nJets);
 	_jetMaxCosPsi = temp; 


}
void jetVariables::setParticles(LCEvent*& evt, std::vector<ReconstructedParticle*> jets, std::vector<TLorentzVector*> tlvjets){
	_localEvt = evt;
	_jets = jets;
	_tlvjets = tlvjets;
}
void jetVariables::setLogYVariables(double& logyMinus, double& logyPlus){
	logyMinus =(double) std::log( _localEvt->getCollection(_inputJetCollectionName)->getParameters().getFloatVal( "y_{n-1,n}" ));
    logyPlus  =(double) std::log( _localEvt->getCollection(_inputJetCollectionName)->getParameters().getFloatVal( "y_{n,n+1}" ));
}
void jetVariables::setMCTJetMultiplicity( int& mctlepPfoMult, int& mctlepTrkMult, int& mctUpPfoMult, int& mctDwnPfoMult, int& mctUpTrkMult, int& mctDwnTrkMult, double& mctlepMaxCosPsi, double& mctUpMaxCosPsi, double& mctDwnMaxCosPsi){

	//mctagged jets must already be populated in evt variables

	std::vector<int> _localmctTags = _evtvar->_jetmctags;

	std::vector<int> _pfoMult(_nJets);
	std::vector<int> _trkMult(_nJets);
	int pfoCount = 0;
	int trkCount = 0;
	//first loop over each jet and get charge and pfo multiplicities
	for(unsigned int i=0; i<_jets.size(); i++){
		std::vector<ReconstructedParticle*> _jetParts = _jets.at(i)->getParticles();
		for(unsigned int j=0; j< _jetParts.size(); j++){
			if( _jetParts.at(j)->getCharge() != 0){
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
				mctUpMaxCosPsi = _jetMaxCosPsi.at(i);
				
			}
			else{
				//its downlike
				mctDwnTrkMult = _trkMult.at(i);
				mctDwnPfoMult = _pfoMult.at(i);
				mctDwnMaxCosPsi = _jetMaxCosPsi.at(i);
			}
		}
		else{
		//its a lepton
			mctlepTrkMult = _trkMult.at(i);
			mctlepPfoMult = _pfoMult.at(i);
			mctlepMaxCosPsi = _jetMaxCosPsi.at(i);
		}

	}

}
void jetVariables::setMaxCosPsi(std::vector<double>& jetMaxCosPsi){

	TVector3 j1{};
	TVector3 j2{};	
	double maxCosPsi= -2.0;
	double CosPsi;
	for(unsigned int i=0; i<_tlvjets.size(); i++){
		j1 = _tlvjets.at(i)->Vect();
		for(unsigned int j=0; j<_tlvjets.size(); j++){
		//compute all cos psi w.r.t. ji
			if( i != j){
				j2 = _tlvjets.at(j)->Vect();		
				CosPsi = j1.Dot(j2)/( j1.Mag() * j2.Mag() );
				if(CosPsi > maxCosPsi){
					maxCosPsi = CosPsi;
				}
			}
		}
		jetMaxCosPsi.at(i) = maxCosPsi;
		maxCosPsi = -2.0;
	}
}
void jetVariables::setAnaJetMultiplicity(std::vector<int>& anatags, int& analepPfoMult, int& analepTrkMult){
	int pfoCount = 0;
	int trkCount = 0;
	//first loop over each jet and get charge and pfo multiplicities
	for(unsigned int i=0; i<anatags.size(); i++){
		if( abs(anatags.at(i))>6 && abs(anatags.at(i))<16){
			std::vector<ReconstructedParticle*> _jetParts = _jets.at(i)->getParticles();
			for(unsigned int j=0; j< _jetParts.size(); j++){
				if( _jetParts.at(j)->getCharge() != 0){
					trkCount++;
				}
				pfoCount++;
			}
			analepPfoMult = pfoCount;
			analepTrkMult = trkCount;
			return;
		}
	}
}
void jetVariables::printVec(std::vector<double> v){
	for(unsigned int i =0; i< v.size(); i++){
		std::cout<<v.at(i)<<" ";
	}
	std::cout<<std::endl;
}
void jetVariables::printJetVariables(){

	std::cout<<" log Y- : "<< _logyMinus <<" log Y+ : "<< _logyPlus <<std::endl;
	std::cout<<" Jet Cos Psi: ";
	printVec(_jetMaxCosPsi);
	std::cout<<" MCT Multiplicities "<< std::endl;
	std::cout<<"type	pfomult		trkmult"<<std::endl;
	std::cout<<"lep		"<<_mctlepPfoMult<<"	"<<_mctlepTrkMult<<std::endl;
	std::cout<<" up		"<<_mctUpPfoMult<< "	"<<_mctUpTrkMult<<std::endl;
	std::cout<<"dwn		"<<_mctDwnPfoMult<<"	"<<_mctDwnTrkMult<<std::endl;

	std::cout<<" Ana Multiplicities "<< std::endl;
	std::cout<<"type	pfomult		trkmult"<<std::endl;
	std::cout<<"lep		"<<_analepPfoMult<<"	"<<_analepTrkMult<<std::endl;



	//TODO print ana mult	
}
void jetVariables::initLocalTree(){

	std::string vsn(_variableSetName);
	_localTree->Branch((vsn+"logyMinus").c_str(), &_logyMinus,(vsn+"logyMinus/D").c_str());
	_localTree->Branch((vsn+"logyPlus").c_str(), &_logyPlus,(vsn+"logyPlus/D").c_str());
	
	
	for(unsigned int i=0; i< _nJets; i++){
		std::stringstream name;
		name << _variableSetName << "jetMaxCosPsi"<<i;
		_localTree->Branch(name.str().c_str(), &_jetMaxCosPsi.at(i), (name.str()+"/D").c_str());
	}

	_localTree->Branch((vsn+"mctlepPfoMult").c_str(), &_mctlepPfoMult, (vsn+"mctlepPfoMult/I").c_str());
	_localTree->Branch((vsn+"mctlepTrkMult").c_str(), &_mctlepTrkMult, (vsn+"mctlepTrkMult/I").c_str());
	_localTree->Branch((vsn+"mctUpPfoMult").c_str(), &_mctUpPfoMult, (vsn+"mctUpPfoMult/I").c_str());
	_localTree->Branch((vsn+"mctUpTrkMult").c_str(), &_mctUpTrkMult, (vsn+"mctUpTrkMult/I").c_str());
	_localTree->Branch((vsn+"mctDwnPfoMult").c_str(), &_mctDwnPfoMult, (vsn+"mctDwnPfoMult/I").c_str());
	_localTree->Branch((vsn+"mctDwnTrkMult").c_str(), &_mctDwnTrkMult, (vsn+"mctDwnTrkMult/I").c_str());

	_localTree->Branch((vsn+"mctlepMaxCosPsi").c_str(), &_mctlepMaxCosPsi, (vsn+"mctlepMaxCosPsi/D").c_str());
	_localTree->Branch((vsn+"mctUpMaxCosPsi").c_str(), &_mctUpMaxCosPsi, (vsn+"mctUpMaxCosPsi/D").c_str());
	_localTree->Branch((vsn+"mctDwnMaxCosPsi").c_str(), &_mctDwnMaxCosPsi, (vsn+"mctDwnMaxCosPsi/D").c_str());

	_localTree->Branch((vsn+"analepPfoMult").c_str(), &_analepPfoMult, (vsn+"analepPfoMult/I").c_str());
	_localTree->Branch((vsn+"analepTrkMult").c_str(), &_analepTrkMult, (vsn+"analepTrkMult/I").c_str());
}

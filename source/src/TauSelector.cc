#include "TauSelector.h"

TauSelector aTauSelector;


TauSelector::TauSelector() : Processor("TauSelector") {


  // register steering parameters: name, description, class-variable, default value


	
//input particle collection:
	std::string inputParticleCollectionName = "x";
  	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			     	"InputRemainCollectionName" , 
			     	"Input Remain Particle Collection Name "  ,
			     	_inputRemainCollectionName,
			      	inputParticleCollectionName);

	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
					"InputTauJetCollectionName" ,
					"Input Tau Jet Particle Collection Name " ,
					_inputTauJetCollectionName,
					inputParticleCollectionName);

  	std::string outputParticleCollectionName = "x";
  	registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
                    "OutputRemainCollectionName" ,
			     	"Output Particle Collection Name "  ,
                    _outputRemainCollectionName,
                     outputParticleCollectionName);

	registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
					"OutputTauJetCollectionName",
					"Output Tau Collection Name",
					_outputTauJetCollectionName,
					outputParticleCollectionName);
}

void TauSelector::init() {

  streamlog_out(DEBUG) << "   init called  " << std::endl;
                   
  // usually a good idea to
  printParameters() ;
  nEvt = 0;
 
}

void TauSelector::processRunHeader( LCRunHeader* run) {
  streamlog_out(MESSAGE) << " processRunHeader "  << run->getRunNumber() << std::endl ;
}

bool TauSelector::FindPFOs( LCEvent* evt, std::string _inputParticleCollectionName, std::vector<ReconstructedParticle*>& _pfovec ) {

	bool collectionFound = false;

  	// clear old global pfovector
	_pfovec.clear();
  	typedef const std::vector<std::string> StringVec ;
  	StringVec* strVec = evt->getCollectionNames() ;
	
	//iterate over collections, find the matching name
  	for(StringVec::const_iterator itname=strVec->begin(); itname!=strVec->end(); itname++){
     
		//if found print name and number of elements
    		if(*itname==_inputParticleCollectionName){ 
			LCCollection* collection = evt->getCollection(*itname);
			std::cout<< "Located Pfo Collection "<< *itname<< " with "<< collection->getNumberOfElements() << " elements " <<std::endl;
			collectionFound = true;

 			//add the collection elements to the global vector
      			for(int i=0; i<collection->getNumberOfElements(); i++){
				ReconstructedParticle* recoPart = dynamic_cast<ReconstructedParticle*>(collection->getElementAt(i));
				_pfovec.push_back(recoPart);
      			}
    		}
  	}
	
	if(!collectionFound){
		std::cout<<"Pfo Collection "<< _inputParticleCollectionName << "not found"<<std::endl;
	}

   
	return collectionFound;
}

void TauSelector::printReconstructedParticle(ReconstructedParticle* p){
	std::cout<<p->id()<<" "<<p->getType()<<" "<<p->getMomentum()[0]<<" "<<p->getMomentum()[1]<<" "<<p->getMomentum()[2]<<" "<<p->getEnergy()<<" "<< p->getMass()<<std::endl;
}

void TauSelector::processEvent( LCEvent * evt ) {
 
 //get particle collections

 FindPFOs(evt, _inputRemainCollectionName, _Remainpfovec);
 FindPFOs(evt, _inputTauJetCollectionName, _TauJetpfovec);

 LCCollectionVec *SelectedCollection = new LCCollectionVec(LCIO::RECONSTRUCTEDPARTICLE);
 SelectedCollection->setSubset(true);

 LCCollectionVec *SelectedTau = new LCCollectionVec(LCIO::RECONSTRUCTEDPARTICLE);
 SelectedTau->setSubset(true);

 for( unsigned int i=0; i<_Remainpfovec.size(); i++){
	SelectedCollection->addElement(_Remainpfovec.at(i));
 }
 //get highest energy index
 int EselIndex=-1;
 double emax= 0;
 for( unsigned int i=0; i<_TauJetpfovec.size(); i++){
	if(_TauJetpfovec.at(i)->getEnergy() > emax){
		emax = _TauJetpfovec.at(i)->getEnergy();
		EselIndex = i;
	}
 }
 //add particles from other taus to collection
 for( unsigned int i=0; i<_TauJetpfovec.size(); i++){
	if( i == EselIndex){
		SelectedTau->addElement(_TauJetpfovec.at(i));
	}
	else{
		std::vector<ReconstructedParticle*> unselectedComponents{};
		unselectedComponents = _TauJetpfovec.at(i)->getParticles();
		for( unsigned int j=0; j<unselectedComponents.size(); j++){
			SelectedCollection->addElement(unselectedComponents.at(j));
		}
	}
 }
 
  evt->addCollection(SelectedCollection, _outputRemainCollectionName.c_str() );
  evt->addCollection(SelectedTau, _outputTauJetCollectionName.c_str() );
  
  nEvt++;
}
void TauSelector::end(){
	
}


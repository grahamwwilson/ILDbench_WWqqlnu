#include "WWAnalysis.h"

WWAnalysis aWWAnalysis;


WWAnalysis::WWAnalysis() : Processor("WWAnalysis") {


  // register steering parameters: name, description, class-variable, default value

	registerProcessorParameter( "Printing" ,
	                            "Print certain messages"  ,
	                             _printing,
	                             (int)5 ) ;

	std::string inputMcParticleCollectionName = "x";
	registerInputCollection( LCIO::MCPARTICLE,
				"McParticleCollectionName" ,
				"Name of the MCParticle input collection" ,
				_inputMcParticleCollectionName,
				inputMcParticleCollectionName);

	//input collection parameters
	std::string inputJetCollectionName = "x";
  	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			     	"InputJetCollectionName" , 
			     	"Input Jet Collection Name "  ,
			     	_inputJetCollectionName,
			      	inputJetCollectionName);

	//collection for fast jet with no prior overlay removal
	std::string inputJetWithOverlayCollectionName = "x";
  	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			     	"InputJetWithOverlayCollectionName" , 
			     	"Input Jet With Overlay Collection Name "  ,
			     	_inputJetWithOverlayCollectionName,
			      	inputJetWithOverlayCollectionName);

	//input track and particle collections:
	std::string inputParticleCollectionName = "x";
  	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			     	"InputParticleCollectionName" , 
			     	"Input Particle Collection Name "  ,
			     	_inputParticleCollectionName,
			      	inputParticleCollectionName);

 	std::string inputTrackCollectionName = "x";
  	registerInputCollection( LCIO::TRACK,
				"InputTrackCollectionName" ,
				"Input Track Collection Name " ,
				_inputTrackCollectionName,
				inputTrackCollectionName);


	std::string inputRecoRelationCollectionName = "x";
  	registerInputCollection( LCIO::LCRELATION,
			     	"InputRecoRelationCollectionName" , 
			     	"Input Reco Relation Collection Name "  ,
			     	_inputRecoRelationCollectionName,
			      	inputRecoRelationCollectionName);

	//parameters for running in backgrounds: #fermions, # leptons
	registerProcessorParameter("NFermions",
								"number of fermions in event",
								_nfermions,
								(int)4);

	registerProcessorParameter("Nleptons",
								"number of leptons in event",
								_nleptons,
								(int) 2);
   
	registerProcessorParameter("Normalization",
								"event normalization bg/signal",
								weight,
								(double) 1.0);

	registerProcessorParameter("Njets",
								"number of jets from fast jet",
								_nJets,
								(int) 3);

	registerProcessorParameter("Ncuts",
								"nmber of event selection cuts",
								ncuts,
								(int) 0);



}


void WWAnalysis::init() {
  
  streamlog_out(DEBUG) << "   init called  " << std::endl;
  // usually a good idea to
  printParameters() ;
  file = new TFile("file.root","RECREATE");
 
  _tree = new TTree("tree", "tree");
  _tree->Branch("runNumber", &_nRun, "runNumber/I");
  _tree->Branch("eventNumber", &_nEvt, "eventNumber/I");

/*  ev1 = new eventVariables("a", _nfermions, _nleptons, _nJets, _tree);
  ev1->initLocalTree();

  //set up jet variables
  jv1 = new jetVariables(ev1, _inputJetCollectionName);
  jv1->initLocalTree();

  ppfov1 = new PandoraPfoVariables(_tree);
  ppfov1->initLocalTree();

  ana1 = new anaVariables(_tree, ev1);
  ana1->initLocalTree();		 */

  //temp setup
	ev_eekt = new eventVariables("eekt",_nfermions, _nleptons, _nJets, _tree);
    ev_eekt->initLocalTree();
   jv_eekt= new jetVariables(ev_eekt, _JetCollName_eekt) ;
	jv_eekt->initLocalTree();
   ana_eekt = new anaVariables(_tree, ev_eekt);
	ana_eekt->initLocalTree();

	ev_kt15 = new eventVariables("kt15",_nfermions, _nleptons, _nJets, _tree);
	ev_kt15->initLocalTree();
	jv_kt15 = new jetVariables(ev_kt15, _JetCollName_kt15);
	jv_kt15->initLocalTree();
	ana_kt15 = new anaVariables(_tree, ev_kt15);
	ana_kt15->initLocalTree();
	
	ev_kt08 = new eventVariables("kt08",_nfermions, _nleptons, _nJets, _tree);
	ev_kt08->initLocalTree();
	jv_kt08 = new jetVariables(ev_kt08, _JetCollName_kt08);
	jv_kt08->initLocalTree();
	ana_kt08 = new anaVariables(_tree, ev_kt08);
	ana_kt08->initLocalTree();



   ppfov = new PandoraPfoVariables(_tree);
  ppfov->initLocalTree();


  h1 = new HistoManager(ncuts,weight); // no need to init until the class is more finalized
 // h1->initHists1();
 // h1->initHists2();

  _nRun = 0;
  _nEvt = 0;

  nEvt = 0;


	

	

	//overlay!
	_tree->Branch("OverlaynTotalEvents",&OverlaynTotalEvents,"OverlaynTotalEvents/I");
	_tree->Branch("OverlayPairBgOverlaynEvents",&OverlayPairBgOverlaynEvents,"OverlayPairBgOverlaynEvents/I");
	_tree->Branch("uplike_rejects_costheta.",&uplike_rejects_costheta);
	_tree->Branch("downlike_rejects_costheta.",&downlike_rejects_costheta);
	_tree->Branch("lepton_rejects_costheta.",&lepton_rejects_costheta);
	_tree->Branch("uplike_rejects_pt.",&uplike_rejects_pt);
	_tree->Branch("downlike_rejects_pt.",&downlike_rejects_pt);
	_tree->Branch("lepton_rejects_pt.",&lepton_rejects_pt);

	_tree->Branch("uplike_rejects_P.",&uplike_rejects_P);
	_tree->Branch("downlike_rejects_P.",&downlike_rejects_P);
	_tree->Branch("lepton_rejects_P.",&lepton_rejects_P);


}

void WWAnalysis::processRunHeader( LCRunHeader* run) {
  streamlog_out(MESSAGE) << " processRunHeader "  << run->getRunNumber() << std::endl ;
}
void WWAnalysis::initOverlayEff(){
	

	std::vector<TH1D*> temp1(8);
	std::vector<TH1D*> temp2(8);
	maxcostheta_cut = temp1;
	maxcostheta_cut_ovr = temp2;
	
	
	for(unsigned int i=0; i< maxcostheta_cut.size(); i++){

		char cuts[100];
         sprintf(cuts, "_%d", i);
         std::string cutnum(cuts);

		maxcostheta_cut.at(i) = new TH1D(("maxcostheta_cut"+cutnum).c_str(), ("The polar angle of most forward jet with overlay removal with cut "+cutnum).c_str(),20,0,1.0);
		maxcostheta_cut.at(i)->Sumw2(true);

		maxcostheta_cut_ovr.at(i) = new TH1D(("maxcostheta_cut_ovr"+cutnum).c_str(), ("The polar angle of most forward jet without overlay removal and cut"+cutnum).c_str(),20,0,1.0);
		maxcostheta_cut_ovr.at(i)->Sumw2(true);

		maxcostheta_cut_mc.at(i) = new TH1D(("maxcostheta_cut_mc"+cutnum).c_str(), ("The polar angle of most forward mc particle"+cutnum).c_str(),20,0,1.0);
		maxcostheta_cut_mc.at(i)->Sumw2(true);

		mctag_mc_dM.at(i) = new TH1D(("mctag_mc_dM"+cutnum).c_str(), ("#Delta M = M_{qq}^{mctag} - M_{qq}^{mc}"+cutnum).c_str(),100,-20,20);

		mctag_mc_dM.at(i)->Sumw2(true);

	
	
		mctag_mc_dM_ovr.at(i) = new TH1D(("mctag_mc_dM_ovr"+cutnum).c_str(),("#Delta M = M_{qq}^{mctag} - M_{qq}^{mc}"+cutnum).c_str(),100,-20,20);
		
		mctag_mc_dM_ovr.at(i)->Sumw2(true);
	
	}
}
/*****************
locate the pfo collection with specified name
populated the global pfo vectors with particles from that collection for this event
******************/
bool WWAnalysis::FindPFOs( LCEvent* evt ) {

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
/*****************
locate the track collection with specified name
populate the global track vectors with tracks from the collection for this event
******************/
bool WWAnalysis::FindTracks( LCEvent* evt ) {

	bool collectionFound = false;

	// clear old global track vector
 	_trackvec.clear();
  	typedef const std::vector<std::string> StringVec ;
  	StringVec* strVec = evt->getCollectionNames() ;

	//iterate over collections, find the matching name
 	for(StringVec::const_iterator itname=strVec->begin(); itname!=strVec->end(); itname++){   

		//if found print name and number of elements 
    		if(*itname==_inputTrackCollectionName){
      			LCCollection* collection = evt->getCollection(*itname);
      			std::cout<< "Located Track Collection "<< *itname<< " with "<< collection->getNumberOfElements() << " elements " <<std::endl;
     		
			collectionFound = true;
		
			//add the collection elements to the global vector
      			for(int i=0; i<collection->getNumberOfElements(); i++){
				Track* track = dynamic_cast<Track*>(collection->getElementAt(i));
				_trackvec.push_back(track);
      			}
    		}
  	}

  	if(!collectionFound){
		std::cout<<"Track Collection "<< _inputTrackCollectionName << "not found"<<std::endl;
	}

  	return collectionFound;
}
bool WWAnalysis::FindMCParticles( LCEvent* evt ){
   
	bool collectionFound = false;

  	// clear old global MCParticle vector
  	_mcpartvec.clear();
  	typedef const std::vector<std::string> StringVec ;
  	StringVec* strVec = evt->getCollectionNames() ;

	//iterate over collections, find the matching name
  	for(StringVec::const_iterator itname=strVec->begin(); itname!=strVec->end(); itname++){    
    
		//if found print name and number of elements 
		if(*itname==_inputMcParticleCollectionName){
      			LCCollection* collection = evt->getCollection(*itname);
     			std::cout<< "Located MC Collection "<< *itname<< " with "<< collection->getNumberOfElements() << " elements " <<std::endl;
      			collectionFound = true;
      
			//add the collection elements to the global vector
			for(unsigned int i=0;i<collection->getNumberOfElements();i++){
				MCParticle* mcPart = dynamic_cast<MCParticle*>(collection->getElementAt(i));
				_mcpartvec.push_back(mcPart);

       
      			}
    		}
  	}

  	if(!collectionFound){
		std::cout<<"MC Collection "<< _inputMcParticleCollectionName << "not found"<<std::endl;
	}
  
  	return collectionFound;
}
bool WWAnalysis::FindRecoToMCRelation( LCEvent* evt ){
   
	bool collectionFound = false;

  	// clear old global MCParticle vector
  	_reco2mcvec.clear();
  	typedef const std::vector<std::string> StringVec ;
  	StringVec* strVec = evt->getCollectionNames() ;

	//iterate over collections, find the matching name
  	for(StringVec::const_iterator itname=strVec->begin(); itname!=strVec->end(); itname++){    
    
		//if found print name and number of elements 
		if(*itname==_inputRecoRelationCollectionName){
      			LCCollection* collection = evt->getCollection(*itname);
     			std::cout<< "Located MC Collection "<< *itname<< " with "<< collection->getNumberOfElements() << " elements " <<std::endl;
      			collectionFound = true;
      
			//add the collection elements to the global vector
			for(unsigned int i=0;i<collection->getNumberOfElements();i++){
				LCRelation* recoRelation = dynamic_cast<LCRelation*>(collection->getElementAt(i));
				_reco2mcvec.push_back(recoRelation);

       
      			}
    		}
  	}

  	if(!collectionFound){
		std::cout<<"LCRelation Collection "<< _inputRecoRelationCollectionName << "not found"<<std::endl;
	}
  
  	return collectionFound;
}
/*bool WWAnalysis::FindMCTruthToRecoLink( LCEvent* evt ){
	
}*/
/*
bool WWAnalysis::FindJets( LCEvent* evt ) {

	bool collectionFound = false;

  	// clear old global pfovector
	_jets.clear();
  	typedef const std::vector<std::string> StringVec ;
  	StringVec* strVec = evt->getCollectionNames() ;
	
	//iterate over collections, find the matching name
  	for(StringVec::const_iterator itname=strVec->begin(); itname!=strVec->end(); itname++){
     
		//if found print name and number of elements
    		if(*itname==_inputJetCollectionName){ 
			LCCollection* collection = evt->getCollection(*itname);
			std::cout<< "Located Jets Collection "<< *itname<< " with "<< collection->getNumberOfElements() << " elements " <<std::endl;
			collectionFound = true;

 			//add the collection elements to the global vector
      			for(unsigned int i=0; i<collection->getNumberOfElements(); i++){
				ReconstructedParticle* recoPart = dynamic_cast<ReconstructedParticle*>(collection->getElementAt(i));
				_jets.push_back(recoPart);
      			}
    		}
  	}
	
	if(!collectionFound){
		std::cout<<"Jet Collection "<< _inputJetCollectionName << "not found"<<std::endl;
	}

   
	return collectionFound;
}
*/
/*
bool WWAnalysis::FindJetsWithOverlay( LCEvent* evt ) {

	bool collectionFound = false;

  	// clear old global pfovector
	_jetswithoverlay.clear();
  	typedef const std::vector<std::string> StringVec ;
  	StringVec* strVec = evt->getCollectionNames() ;
	
	//iterate over collections, find the matching name
  	for(StringVec::const_iterator itname=strVec->begin(); itname!=strVec->end(); itname++){
     
		//if found print name and number of elements
    		if(*itname==_inputJetWithOverlayCollectionName){ 
			LCCollection* collection = evt->getCollection(*itname);
			std::cout<< "Located Jets With Overlay Collection "<< *itname<< " with "<< collection->getNumberOfElements() << " elements " <<std::endl;
			collectionFound = true;

 			//add the collection elements to the global vector
      			for(unsigned int i=0; i<collection->getNumberOfElements(); i++){
				ReconstructedParticle* recoPart = dynamic_cast<ReconstructedParticle*>(collection->getElementAt(i));
				_jetswithoverlay.push_back(recoPart);
      			}
    		}
  	}
	
	if(!collectionFound){
		std::cout<<"Jet Collection "<< _inputJetWithOverlayCollectionName << "not found"<<std::endl;
	}

   
	return collectionFound;
}
*/
bool WWAnalysis::FindJetCollection( LCEvent* evt, std::string JetCollectionName, std::vector<ReconstructedParticle*>& localVec ) {

	bool collectionFound = false;

  	// clear old global pfovector
	localVec.clear();
  	typedef const std::vector<std::string> StringVec ;
  	StringVec* strVec = evt->getCollectionNames() ;
	
	//iterate over collections, find the matching name
  	for(StringVec::const_iterator itname=strVec->begin(); itname!=strVec->end(); itname++){
     
		//if found print name and number of elements
    		if(*itname==JetCollectionName){ 
			LCCollection* collection = evt->getCollection(*itname);
			std::cout<< "Located Jet Collection "<< *itname<< " with "<< collection->getNumberOfElements() << " elements " <<std::endl;
			collectionFound = true;

 			//add the collection elements to the global vector
      			for(unsigned int i=0; i<collection->getNumberOfElements(); i++){
				ReconstructedParticle* recoPart = dynamic_cast<ReconstructedParticle*>(collection->getElementAt(i));
				 localVec.push_back(recoPart);
      			}
    		}
  	}
	
	if(!collectionFound){
		std::cout<<"Jet Collection "<< JetCollectionName << "not found"<<std::endl;
	}   
	return collectionFound;
}

/*
void WWAnalysis::analyzeLeadingTracks(){
	ReconstructedParticle* leader;
	std::vector<ReconstructedParticle*> d;
	std::vector<Track*> dt;
	double maxP = -9999;
    double maxtP = -9999;
	int maxindex= -1;
	int maxtindex = -1;
	double tp;
	const double* mom;
	double p;

	const double c = 2.99792458e8; // m*s^-1        
  	const double mm2m = 1e-3;
  	const double eV2GeV = 1e-9;
    const double BField = marlin::Global::GEAR->getBField().at(gear::Vector3D(0.,0.,0.)).z();

  	const double eB = BField*c*mm2m*eV2GeV;

	for(int i=0; i< _jets.size(); i++){

		d = _jets.at(i)->getParticles();
		for(unsigned int j=0; j< d.size(); j++){
			if(d.at(j)->getCharge() !=0){
				mom = d.at(j)->getMomentum();
				p = std::sqrt( mom[0]*mom[0] + mom[1]*mom[1] + mom[2]*mom[2]);
			//	std::cout<<"om "<<om<<" "<<fabs(om)<<" "<<minOm<<std::endl;
			//	std::cout<<" p "<<p<<std::endl;
				if( p > maxP){
					maxP = p;
					maxindex=j;
				}//end max reset
			}//end charge condition
		}//end jet particles

		if(maxindex == -1) { std::cout<< "continuing" <<std::endl; continue;} //no tracks in this jet

		//the maxpt track may have more than 1 associated tracks so pick out the one with highest pt
		dt = d.at(maxindex)->getTracks();

		for(int j=0; j< dt.size();j++){
			double p_t = abs(dt.at(j)->getOmega())*eB;
			double p_z = p_t*dt.at(j)->getTanLambda();

			tp = std::sqrt(p_t*p_t + p_z*p_z);
			if(tp > maxtP){
				maxtP = tp;
				maxtindex=j;
			}

		}		
		//look at track of this particle
	    Track* t = dt.at(maxtindex);
		std::cout<<"jet "<<i<< std::endl;
		
			std::cout<<t->getD0()<<" ";
			std::cout<<t->getPhi()<<" ";
			std::cout<<t->getOmega()<<" ";
			std::cout<<t->getZ0()<<" ";
			std::cout<<t->getTanLambda()<<" ";
		 
		std::cout<<std::endl;
    
		if(i == ljet_index){
			leadingptljet = maxtP ;
			leadingd0ljet = t->getD0();
		//	leadingd0relerrljet = sqrt(t->getCovMatrix()[0])/fabs(t->getD0());
			leadingd0relerrljet = fabs(t->getD0())/sqrt(t->getCovMatrix()[0]);
		}
		else{
			//we lazily just examing 1 q jet for now
			leadingptqjet = maxtP;
			leadingd0qjet = t->getD0();
		//	leadingd0relerrqjet = sqrt(t->getCovMatrix()[0])/fabs(t->getD0());
			leadingd0relerrqjet = fabs(t->getD0())/sqrt(t->getCovMatrix()[0]);
		}
		//reset maxindex and max p new jet
		maxtP = -9999;
		maxindex= -1;
		maxtindex = -1;
		maxP = -9999;
	}//end jet loop
 
}*/

/* deal with 2f backgrounds */
/*
MCParticle* WWAnalysis::classifyEvent2fermion( std::vector<TLorentzVector*>& _MCf, std::vector<int>& _MCFpdg){
	for(int i=0; i<_mcpartvec.size(); i++){
		std::vector<int> parentpdgs{};
		std::vector<int> daughterpdgs{};
		std::vector<MCParticle*> mcparents{};
		std::vector<MCParticle*> daughters{};
		daughters = _mcpartvec.at(i)->getDaughters();
		for(int j = 0; j<daughters.size(); j++){
			daughterpdgs.push_back(daughters.at(j)->getPDG());
			
		}
		//allowed quarks
		std::vector<int> quarks{ 1, 2, 3, 4, 5, -1, -2, -3, -4, -5};
	//	std::vector<int> leptons{11, 12, 13, 14, 15, 16, -11, -12, -13, -14, -15, -16};
		//we require exactly 2 elements from leptons and 2 from quarks
		int lep=0;
		int qrk=0;

		//categorize the event for plotting
		for(int k=0; k<quarks.size(); k++){
			qrk += std::count(daughterpdgs.begin(),daughterpdgs.end(),quarks.at(k));
		}
		//for(int k=0; k<leptons.size(); k++){
		//	lep += std::count(daughterpdgs.begin(),daughterpdgs.end(),leptons.at(k));
		//}

		if( (qrk+lep) == 2 ){
			//found the proper set 
			for(int j=0; j<parentpdgs.size(); j++){
				std::cout<<parentpdgs.at(j)<<" ";
			}
			std::cout<< " -> "<<_mcpartvec.at(i)->getPDG()<<" -> ";
			for(int j=0; j<daughters.size(); j++){
				std::cout<<daughters.at(j)->getPDG()<<" ";
			}
			std::cout<<std::endl;

			for(int j=0; j<daughters.size(); j++){
				std::cout<<daughters.at(j)->getPDG()<<" " 
                                                                    << daughters.at(j)->getMomentum()[0] << " "
                                                                    << daughters.at(j)->getMomentum()[1] << " "
                                                                    << daughters.at(j)->getMomentum()[2] << " "
                                                                    << daughters.at(j)->getEnergy() << " " << std::endl;
                            TLorentzVector mcVec(TVector3(daughters.at(j)->getMomentum()),daughters.at(j)->getEnergy());
                            *_MCf[j] = mcVec;
                            _MCfpdg[j] = daughters.at(j)->getPDG();
			}
			return _mcpartvec.at(i);
		}
		
	}
	return NULL;


}
*/

void WWAnalysis::populateJetsWithOverlayTLVs(std::vector<ReconstructedParticle*> j){
	/*
	std::vector<TLorentzVector*> temp(_jetswithoverlay.size());
	jetswithoverlay=temp;
	for(unsigned int i=0; i<_jetswithoverlay.size(); i++){
	
	//	TLorentzVector* j = new TLorentzVector();

		jetswithoverlay.at(i) = new TLorentzVector();

		jetswithoverlay.at(i)->SetXYZM(_jetswithoverlay.at(i)->getMomentum()[0], _jetswithoverlay.at(i)->getMomentum()[1], _jetswithoverlay.at(i)->getMomentum()[2], _jetswithoverlay.at(i)->getMass() );
		//tempjets.at(i) = j;

		std::cout<<_jetswithoverlay.at(i)->getMomentum()[0]<<" "<< _jetswithoverlay.at(i)->getMomentum()[1]<<" "<<_jetswithoverlay.at(i)->getMomentum()[2]<< " "<< _jetswithoverlay.at(i)->getMass()<<std::endl;
	}
*/

}

void WWAnalysis::FindMCOverlay( MCParticle* p , std::vector<MCParticle*>& FSP){
/*	if(p->isCreatedInSimulation()) return;
	if(! (p->isOverlay())) return;

	//std::cout<<p->id()<<" ";
	//std::cout<<p->getPDG()<<" -> ";
	std::vector<MCParticle*> d = p->getDaughters();
	
	for(unsigned int i=0; i< d.size(); i++){
		if( (! d.at(i)->isCreatedInSimulation() ) && ( allChildrenAreSimulation(d.at(i)) || (d.at(i)->getDaughters().size()==0)  ) && (d.at(i)->isOverlay() ) ){
		
		//this is an initial final state particle
			FSP.push_back(d.at(i));
		}
		if( (! d.at(i)->isCreatedInSimulation()) &&  d.at(i)->isOverlay() ){//&& (d.at(i)->getCharge() != 0) ){
			std::cout<< "( "<< d.at(i)->id()<<" "<<d.at(i)->getPDG() <<" "<< d.at(i)->isDecayedInTracker()<<" "<< d.at(i)->isDecayedInCalorimeter()<<" ) ";
		}
	}
	//std::cout<<std::endl;
	for(unsigned int i=0; i<d.size(); i++){
		FindMCOverlay(d.at(i), FSP);
	}
*/


}
void WWAnalysis::AnalyzeOverlay( LCEvent* evt ){
/*

 //LCParameters param = evt->getParameters();
	//tag events with no overlay
	std::string key = "Overlay.nTotalEvents";
	//the global: 
	OverlaynTotalEvents = (evt->getParameters()).getIntVal(key);

	key = "Overlay.PairBgOverlay.nEvents";

	OverlayPairBgOverlaynEvents = (evt->getParameters()).getIntVal(key);

	std::cout<<"noverlay "<< OverlaynTotalEvents<< std::endl;
	std::cout<<"npairbg "<< OverlayPairBgOverlaynEvents <<std::endl;

	std::cout<<"finding jets with overlay "<<std::endl;
	 FindJetsWithOverlay( evt );
	populateJetsWithOverlayTLVs(_jetswithoverlay);

	//relevant quantities to find...
	//-- cos theta of particles that are thrown out by kt
	std::vector<ReconstructedParticle*> rejectedbeamparticles{};
	std::vector<std::vector<ReconstructedParticle*> >  rejectjets{};

	//go through mcf, from this particle go through and tag a jet that corresponds for the mc particle, for both sets of jets

	//tag jets
	std::vector<int> jetmctags(_nJets);
	std::vector<int> jetwithoverlaymctags(_nJets);

	MCTagjets(_MCf, _MCfpdg, jets, jetmctags);
	MCTagjets(_MCf, _MCfpdg, jetswithoverlay, jetwithoverlaymctags);

	//if we double tag a jet just return ignore this event
	// right now these break the code
	
	for(unsigned int i=0; i<jetmctags.size(); i++){
			for(unsigned int j=i+1; j<jetmctags.size(); j++){
				if(jetmctags.at(i) == jetmctags.at(j)){
					return;
				}
			}
		}
		for(unsigned int i=0; i<jetwithoverlaymctags.size(); i++){
			for(unsigned int j=i+1; j<jetwithoverlaymctags.size(); j++){
				if(jetwithoverlaymctags.at(i) == jetwithoverlaymctags.at(j)){
					return;
				}
			}
		}

	//print out the mctags to see what is matched to what
	std::cout<<"jet tags ";
	for(int i=0; i<jetmctags.size();i++){
		std::cout<< _MCfpdg.at( jetmctags.at(i) )<<" ";
	}
	std::cout<<std::endl;

	std::cout<<"jetwith overlay tags ";
	for(int i=0; i<jetwithoverlaymctags.size();i++){
		std::cout<< _MCfpdg.at( jetwithoverlaymctags.at(i) )<<" ";
	}
	std::cout<<std::endl;
	

	for(int i=0; i< jetmctags.size(); i++){
		//find the corresponding jet with overlay
		for(int j=0; j< jetwithoverlaymctags.size(); j++){
			if(jetmctags.at(i) == jetwithoverlaymctags.at(j)){
				//both jets refer to same mc particle

				//figure out what particles got rejected and save them
				std::vector<ReconstructedParticle*> p = _jets.at(i)->getParticles();
				std::vector<ReconstructedParticle*> pwo = _jetswithoverlay.at(j)->getParticles();
				
				 //loop over the sets of particles and find whats missing
				for(int k = 0; k < pwo.size(); k++){
					bool containsParticle = false;
					for(int l = 0; l < p.size(); l++){
						if( p.at(l)->id() == pwo.at(k)->id() ){
							containsParticle = true;
						}
					}
					if(!containsParticle){
						//particle k is a reject
						rejectedbeamparticles.push_back(pwo.at(k));
					}
				}//end loops over 2 sets of particles
				rejectjets.push_back(rejectedbeamparticles);
				rejectedbeamparticles.clear();
			}//end if we matched the two jets
			//add the rejects to reject jet vector
			
		}
	}


	//debug check
	for(int i=0; i<_jets.size(); i++){
		std::cout<<"jets "<<i<<std::endl;
		std::vector<ReconstructedParticle*> p{};
		p = _jets.at(i)->getParticles();
		for(int j=0; j<p.size(); j++){
			std::cout<<p.at(j)->id()<<" ";
		}
				std::cout<<std::endl;
	}
	for(int i=0; i<_jetswithoverlay.size(); i++){
		std::cout<<"jets with o "<<i<<std::endl;
		std::vector<ReconstructedParticle*> p{};
		p = _jetswithoverlay.at(i)->getParticles();
		for(int j=0; j<p.size(); j++){
			std::cout<<p.at(j)->id()<<" ";
		}
		std::cout<<std::endl;
	}
	for(int i=0; i<rejectjets.size(); i++){
		std::cout<<"reject "<<i<<std::endl;
		for(int j=0; j<rejectjets.at(i).size(); j++){
			std::cout<<rejectjets.at(i).at(j)->id()<<" ";
		}
				std::cout<<std::endl;
	}
	

	//loop over the jets with overlay removal,
	//categorize by flavor the rejected particles
	//indices of mctags/reject jets/ jets w/ overlay removal should match
	TLorentzVector temp;
	const double* momtemp;
	double masstemp;
	for(int i=0; i<rejectjets.size(); i++){
		//jet associated pdg
		int pdg = abs(_MCfpdg.at(jetmctags.at(i)) );

		
		if(	pdg == 2 || pdg == 4 ){
			//uplike quark
			for(int j=0; j<rejectjets.at(i).size(); j++){
				//loop over reject particles of jet i
				momtemp = rejectjets.at(i).at(j)->getMomentum();
				masstemp = rejectjets.at(i).at(j)->getMass();
				temp.SetXYZM(momtemp[0],momtemp[1],momtemp[2],masstemp);
				
				uplike_rejects_costheta.push_back( temp.CosTheta() );
				uplike_rejects_pt.push_back( temp.Pt() );
				uplike_rejects_P.push_back( temp.P() );				
			}//end loop over particles

		}//end uplike
		if(pdg == 1 || pdg == 3 || pdg == 5){
			//downlike quark
				for(int j=0; j<rejectjets.at(i).size(); j++){
				//loop over reject particles of jet i
				momtemp = rejectjets.at(i).at(j)->getMomentum();
				masstemp = rejectjets.at(i).at(j)->getMass();
				temp.SetXYZM(momtemp[0],momtemp[1],momtemp[2],masstemp);
				
				downlike_rejects_costheta.push_back( temp.CosTheta() );
				downlike_rejects_pt.push_back( temp.Pt() );
				downlike_rejects_P.push_back( temp.P() );				
			}//end loop over particles

		}	//end downlike
		if(pdg == 13 || pdg == 15){
			//lepton 
			for(int j=0; j<rejectjets.at(i).size(); j++){
				//loop over reject particles of jet i
				momtemp = rejectjets.at(i).at(j)->getMomentum();
				masstemp = rejectjets.at(i).at(j)->getMass();
				temp.SetXYZM(momtemp[0],momtemp[1],momtemp[2],masstemp);
				
				downlike_rejects_costheta.push_back( temp.CosTheta() );
				downlike_rejects_pt.push_back( temp.Pt() );
				downlike_rejects_P.push_back( temp.P() );				
			}//end loop over particles
			
			
		}//end lepton

	}//end loop over rejectjets

	//end debug check

	*/

}
void WWAnalysis::AnalyzeOverlayAcceptance(std::vector<TLorentzVector*> _jetswithoverlay, std::vector<TLorentzVector*> _jetsremovedoverlay ){
	/*

	//loop over the jets and fill histograms in custom cutflow
	//find max costheta
	double max=-1;
	for(unsigned int i =0; i<_jetswithoverlay.size(); i++){
		if( fabs(_jetswithoverlay.at(i)->CosTheta())>max){
			max=fabs(_jetswithoverlay.at(i)->CosTheta());
		}
	}
	//fill the histos
	for(unsigned int i=0; i<maxcosthetacuts.size(); i++){
		if( max<= maxcosthetacuts.at(i) ){
			maxcostheta_cut.at(i)->Fill(max);
		}
	}
	
	max=-1;
	for(unsigned int i=0; i<_jetsremovedoverlay.size(); i++){
		if( fabs(_jetsremovedoverlay.at(i)->CosTheta())>max){
			max=fabs(_jetsremovedoverlay.at(i)->CosTheta());
		}
	}
	
	for(unsigned int i=0; i<maxcosthetacuts.size(); i++){
		if( max <= maxcosthetacuts.at(i) ){
			maxcostheta_cut_ovr.at(i)->Fill(max);
		}
	}

	//we would hope mc data structure is already populated for this section
	max = -1;
	for(unsigned int i=0; i<_MCf.size(); i++){
		if( ( fabs( _MCfpdg.at(i)) != 14) && (fabs( _MCfpdg.at(i)) != 16) ){
			//no neutrinos
			if( fabs(_MCf.at(i)->CosTheta()) > max){
				max=fabs(_MCf.at(i)->CosTheta());
			}
		}
	}
	for(unsigned int i=0; i<maxcosthetacuts.size(); i++){
			if(max <= maxcosthetacuts.at(i)){
				maxcostheta_cut_mc.at(i)->Fill(max);
		}

	}

	//redo tagging because pls no more globals
	std::vector<int> jetmctags(_nJets);
	std::vector<int> jetwithoverlaymctags(_nJets);

	MCTagjets(_MCf, _MCfpdg, jets, jetmctags);
	MCTagjets(_MCf, _MCfpdg, jetswithoverlay, jetwithoverlaymctags);

	//if we double tag a jet just return ignore this event
	// right now these break the code
	
	for(unsigned int i=0; i<jetmctags.size(); i++){
			for(unsigned int j=i+1; j<jetmctags.size(); j++){
				if(jetmctags.at(i) == jetmctags.at(j)){
					return;
				}
			}
		}
		for(unsigned int i=0; i<jetwithoverlaymctags.size(); i++){
			for(unsigned int j=i+1; j<jetwithoverlaymctags.size(); j++){
				if(jetwithoverlaymctags.at(i) == jetwithoverlaymctags.at(j)){
					return;
				}
			}
		}

	
	//using tagged jets fill our dM plots based on the cut 
	//call analyzedijet first it populates mcqqmass
	//next calculate mctagged qq mass
	//use old max from mc level
	double mctagqqmass;
	TLorentzVector mctagqq;
	for(unsigned int i=0; i<jetmctags.size(); i++){
		if( fabs(_MCfpdg.at(jetmctags.at(i)) ) <=5 ){
			mctagqq+= *(jets.at(i));
		}
	}
	mctagqqmass = mctagqq.M();
	
	for(unsigned int i=0; i<maxcosthetacuts.size(); i++){
		//this will be as a function of max cos theta, 
		if(max <= maxcosthetacuts.at(i)){
			mctag_mc_dM.at(i)->Fill( mctagqqmass - mcqqmass );
		}
	}

	

	//redo mctagqqmass with overlay included mctagged jets

	TLorentzVector mctagqqovr;
	for(unsigned int i=0; i<jetwithoverlaymctags.size(); i++){
		if( fabs(_MCfpdg.at(jetwithoverlaymctags.at(i)) ) <=5 ){
			mctagqqovr+= *(jetswithoverlay.at(i));
		}
	}
	mctagqqmass = mctagqqovr.M();

	for(unsigned int i=0; i<maxcosthetacuts.size(); i++){
		if(max <= maxcosthetacuts.at(i)){
			mctag_mc_dM_ovr.at(i)->Fill(mctagqqmass - mcqqmass);
		}
	}

	*/

}
void WWAnalysis::processSignalVariableSet(LCEvent* evt, eventVariables*& evtVar, jetVariables*& jetVar, PandoraPfoVariables*& ppfoVar, anaVariables*& anaVar , std::vector<ReconstructedParticle*> jets){

	std::cout<<"Populating Event Variables "<<evtVar->_variableSetName<<std::endl;
	evtVar->setParticles(_mcpartvec, jets);
	evtVar->initMCVars(evtVar->_isTau, evtVar->_isMuon, evtVar->_mclepCharge, evtVar->_mcl, evtVar->_mcqq, evtVar->_MCf, evtVar->_MCfpdg, evtVar->_mclepTrkMult, evtVar->_mclepPfoMult);
	evtVar->initJetTLV(evtVar->_tlvjets);
	evtVar->MCTagJets( evtVar->_jetmctags, evtVar->_isMCTagValid, evtVar->_mctlepCharge);
	evtVar->computeRecoResultsFromTags(evtVar->_jetmctags, evtVar->_mctWl, evtVar->_mctlep, evtVar->_mctWqq, evtVar->_mctNu);
	evtVar->populateCMTLVs(evtVar->_jetmctags, evtVar->_mctWl, evtVar->_mctWqq, evtVar->_mctNu, evtVar->_mctCMjets,  evtVar->_mctCMNu );
	evtVar-> getCosThetaW(evtVar->_mctlepCharge, evtVar->_mctWl, evtVar->_mctWqq, evtVar->_mctWmProdAngle);


	jetVar->setParticles(evt, evtVar->_jets, evtVar->_tlvjets);
	jetVar->setLogYVariables(jetVar->_logyMinus, jetVar->_logyPlus);
	jetVar->setMaxCosPsi(jetVar->_jetMaxCosPsi); 
	jetVar->setMCTJetMultiplicity(jetVar->_mctlepPfoMult, jetVar->_mctlepTrkMult, jetVar->_mctUpPfoMult, jetVar->_mctDwnPfoMult, jetVar->_mctUpTrkMult, jetVar->_mctDwnTrkMult, jetVar->_mctlepMaxCosPsi, jetVar->_mctUpMaxCosPsi, jetVar->_mctDwnMaxCosPsi);
	

	ppfoVar->setParticles(_pfovec);
	ppfoVar->populateVariables(ppfoVar->_nTracks, ppfoVar->_nParticles, ppfoVar->_totalPt, ppfoVar->_totalE, ppfoVar->_totalM);	


	anaVar->setParticles(_pfovec);
	anaVar->identifyLeptonJet_byTrkMult(anaVar->_jetanatags);
	anaVar->getLeptonJetCharge_byLeadingTrack(anaVar->_analepCharge );
	anaVar->setLeadingTrack(anaVar->_analepLeadingTracktlv );
	anaVar->setAnaEventVariables(evtVar);

	jetVar->setAnaJetMultiplicity( anaVar->_jetanatags, jetVar->_analepPfoMult, jetVar->_analepTrkMult);
}
void WWAnalysis::printSignalVariableSet( eventVariables*& evtVar, jetVariables*& jetVar, PandoraPfoVariables*& ppfoVar, anaVariables*& anaVar ){
	std::cout<<"Printing Event Variables "<<evtVar->_variableSetName <<std::endl;
	evtVar->printEventVariables();	
	ppfoVar->printPandoraPfoVariables();
	jetVar->printJetVariables();
	anaVar->printAnaVariables();

}
void WWAnalysis::processEvent( LCEvent * evt ) {

  _nEvt++;
 // Get Process name and cross section
 //  *_Process = evt->getParameters().getStringVal("Process");
 // _xsec = evt->getParameters().getFloatVal("CrossSection_fb");

 FindMCParticles(evt);
// FindJets(evt);
FindJetCollection( evt, _JetCollName_eekt, _eektJets );
FindJetCollection( evt, _JetCollName_kt15, _kt15Jets );
FindJetCollection( evt, _JetCollName_kt08, _kt08Jets );
FindRecoToMCRelation( evt );
 FindTracks(evt);
 FindPFOs(evt);


	///little test area for lcrelation
	for(unsigned int i=0; i< _reco2mcvec.size(); i++){
			if( i < 1 ){
				LCObject* from =_reco2mcvec.at(i)->getFrom();
				LCObject* to =_reco2mcvec.at(i)->getTo();
				
				std::cout<<"from "<<from->id()<<" to "<<to->id()<<std::endl;
				float wgt = _reco2mcvec.at(i)->getWeight();
				std::cout<<"weights "<<_reco2mcvec.at(i)->getWeight()<<std::endl;
				std::cout<<"Decoded weights "<<  "trackwgt = " << (int(wgt)%10000)/1000. <<  " clusterwgt  = " << (int(wgt)/10000)/1000. <<std::endl; 

			}	
	}


 
//quickfix:::: if there are no jets... !!!!cant do anything TODO explore this phenomenon more
	//happens if we look for jets with eekt after using kt
	if(_eektJets.size() == 0 || _kt15Jets.size() == 0 || _kt08Jets.size() == 0){ 
		std::cout<<"NO JETS HERE!!!!!!!!"<<std::endl;
		return;
	}
	



	processSignalVariableSet(evt, ev_eekt, jv_eekt, ppfov, ana_eekt, _eektJets);
	printSignalVariableSet( ev_eekt, jv_eekt, ppfov, ana_eekt);

	processSignalVariableSet(evt, ev_kt15, jv_kt15, ppfov, ana_kt15, _kt15Jets);
	printSignalVariableSet( ev_kt15, jv_kt15, ppfov, ana_kt15);

	processSignalVariableSet(evt, ev_kt08, jv_kt08, ppfov, ana_kt08, _kt08Jets);
	printSignalVariableSet( ev_kt08, jv_kt08, ppfov, ana_kt08);

	/* new class testing area */
	//make event variables with 3 overlay removed jets
/*	std::cout<<"Populating Event Variables a"<<std::endl;
	ev1->setParticles(_mcpartvec, _jets);
	ev1->initMCVars(ev1->_isTau, ev1->_isMuon, ev1->_mclepCharge, ev1->_mcl, ev1->_mcqq, ev1->_MCf, ev1->_MCfpdg, ev1->_mclepTrkMult, ev1->_mclepPfoMult);
	ev1->initJetTLV(ev1->_tlvjets);
	ev1->MCTagJets( ev1->_jetmctags, ev1->_isMCTagValid, ev1->_mctlepCharge);
	ev1->computeRecoResultsFromTags(ev1->_jetmctags, ev1->_mctWl, ev1->_mctlep, ev1->_mctWqq, ev1->_mctNu);
	ev1->populateCMTLVs(ev1->_jetmctags, ev1->_mctWl, ev1->_mctWqq, ev1->_mctNu, ev1->_mctCMjets,  ev1->_mctCMNu );
	ev1-> getCosThetaW(ev1->_mctlepCharge, ev1->_mctWl, ev1->_mctWqq, ev1->_mctWmProdAngle);


	jv1->setParticles(evt, ev1->_jets, ev1->_tlvjets);
	jv1->setLogYVariables(jv1->_logyMinus, jv1->_logyPlus);
	jv1->setMaxCosPsi(jv1->_jetMaxCosPsi); 
	jv1->setMCTJetMultiplicity(jv1->_mctlepPfoMult, jv1->_mctlepTrkMult, jv1->_mctUpPfoMult, jv1->_mctDwnPfoMult, jv1->_mctUpTrkMult, jv1->_mctDwnTrkMult, jv1->_mctlepMaxCosPsi, jv1->_mctUpMaxCosPsi, jv1->_mctDwnMaxCosPsi);
	

	ppfov1->setParticles(_pfovec);
	ppfov1->populateVariables(ppfov1->_nTracks, ppfov1->_nParticles, ppfov1->_totalPt, ppfov1->_totalE, ppfov1->_totalM);	


	ana1->setParticles(_pfovec);
	ana1->identifyLeptonJet_byTrkMult(ana1->_jetanatags);
	ana1->getLeptonJetCharge_byLeadingTrack(ana1->_analepCharge );
	ana1->setLeadingTrack(ana1->_analepLeadingTracktlv );
	ana1->setAnaEventVariables(ev1);

	jv1->setAnaJetMultiplicity( ana1->_jetanatags, jv1->_analepPfoMult, jv1->_analepTrkMult);
	

	std::cout<<"Printing Event Variables a"<<std::endl;
	ev1->printEventVariables();	
	ppfov1->printPandoraPfoVariables();
	jv1->printJetVariables();
	ana1->printAnaVariables();
*/
/*

	//fill base histograms and produce histos with sequential cuts hist0 is always no cuts
	FillHistos(0);
	//cut #1 trueq == lq, lepton sign is correctly assessed
//	if(trueq == lq){
//		FillHistos(1);
//	}
	//cut #1 require polar angle of q's or lepton to be > cos(theta)=0.995
	bool PolarAngleRequirementMet = true;

	for(int i=0; i<_nfermions; i++){

		if( abs(_MCfpdg[i]) == 12 || abs(_MCfpdg[i]) == 14 || abs(_MCfpdg[i]) == 16 ){
		//dont worry about neutrino angle
			continue;	
		} 
		if( fabs(_MCf[i]->CosTheta()) > 0.995 ){
			//a particle has failed break out
			PolarAngleRequirementMet = false;
			break;
		}
	}


	if(PolarAngleRequirementMet){
		FillHistos(1);
	
		//continue cutflow
		if( totaltracks > 10 ){
			FillHistos(2);
			if( total_Pt > 7.0 ){
				FillHistos(3);
				if(total_E < 500.0){
					FillHistos(4);
				if( total_M	> 80.0 && total_M < 500.0 ){
					FillHistos(5);
					if(_yMinus > -9.5 ){
						FillHistos(6);
						if(_yPlus>-12 && _yPlus< -2.9){
							FillHistos(7);

								if(trueq == lq){
			std::cout<<"got correct charge"<<std::endl;
			if(isTau) tauqmatch++;
			if(isMuon) muonqmatch++;
		}
		else{
			std::cout<<"charge wrong "<<std::endl;
		}
		if(psi_mcl_ljet > 0.7){
			std::cout<<"jet loose match"<<std::endl;
			if(isTau) ljetmatchmctau++;
			if(isMuon) ljetmatchmcmuon++;
		}
						}
					}
			
				}
					
			} }
				
		}
	} 
	
	
	
 */
  _tree->Fill();
/* removed for refactor
	//clear vectors for next event
	uplike_rejects_costheta.clear();
	downlike_rejects_costheta.clear();
	lepton_rejects_costheta.clear();

	uplike_rejects_pt.clear(); 
	downlike_rejects_pt.clear();
	lepton_rejects_pt.clear();
	
	uplike_rejects_P.clear();
	downlike_rejects_P.clear();
	lepton_rejects_P.clear();

*/

 nEvt++;
}
void WWAnalysis::end(){

	

	/* print out stuff */
/*
	std::cout<<" nelec "<<nelec<<" nmuon "<< nmuon <<" ntau "<< ntau << std::endl;
	std::cout<<" nevents "<< nEvt << " mu q match "<< muonqmatch <<  " tau q match "<< tauqmatch <<std::endl;

	std::cout<<" jet match tau "<<ljetmatchmctau<<" "<<ljetmatchmcmuon<<std::endl;
*/
	file->Write();
}


#include "WWAnalysis2.h"

WWAnalysis2 aWWAnalysis2;


WWAnalysis2::WWAnalysis2() : Processor("WWAnalysis2") {


	//load vector<TLorentzVector>
	//gROOT->ProcessLine("cd()");
//
	//gROOT->ProcessLine(".L ~/work/repos/ILDbench_WWqqlnu/source/src/loader.C+");

  // register steering parameters: name, description, class-variable, default value

	registerProcessorParameter( "Printing" ,
	                            "Print certain messages"  ,
	                             _printing,
	                             (int)5 ) ;

/*	registerProcessorParameter( "RunSignalMode",
								"toggle to run over signal or bg events",
								_runSignalMode,
								(int) 1 );
*/
	std::string inputMcParticleCollectionName = "x";
	registerInputCollection( LCIO::MCPARTICLE,
				"McParticleCollectionName" ,
				"Name of the MCParticle input collection" ,
				_inputMcParticleCollectionName,
				inputMcParticleCollectionName);

	

 	std::string inputTrackCollectionName = "x";
  	registerInputCollection( LCIO::TRACK,
				"InputTrackCollectionName" ,
				"Input Track Collection Name " ,
				_inputTrackCollectionName,
				inputTrackCollectionName);

	std::vector<std::string> inputCollectionNames{ "x" };
	registerInputCollections( LCIO::RECONSTRUCTEDPARTICLE,
							"InputTauJetCollectionsNames",
							"Name of the Input Tau Jet collections",
							_tauJetCollectionsNames,
							inputCollectionNames);

	registerInputCollections( LCIO::RECONSTRUCTEDPARTICLE, "InputTauCandCollectionsNames","tau candidates", _tauCandCollectionsNames, inputCollectionNames);

	
 
    	//input remain collection 
/*	std::vector<std::string> inputRemainCollectionsNames{"x"};
	registerInputCollections( LCIO::RECONSTRUCTEDPARTICLE,
					"InputRemainPFOCollectionsNames",
					"Input Remain Collections Name",
					_remPFOCollectionsNames,
					inputRemainCollectionsNames);
*/
	std::vector<std::string> inputRemainJetsCollNames{"x"};
	registerInputCollections( LCIO::RECONSTRUCTEDPARTICLE,
					"InputRemainJetCollectionsNames",
					"name of jet collection formed from Remain Pfos",
					_remJetCollectionsNames,
					inputRemainJetsCollNames);


/*	std::string inputRecoRelationCollectionName = "x";
  	registerInputCollection( LCIO::LCRELATION,
			     	"InputRecoRelationCollectionName" , 
			     	"Input Reco Relation Collection Name "  ,
			     	_inputRecoRelationCollectionName,
			      	inputRecoRelationCollectionName);
*/
	//parameters for running in backgrounds: #fermions, # leptons
	//need to store y cut for remain jets, i dont see how to pull it from lcio
	//only store 1 value -- restrict us to 1 jet collection per run
	registerProcessorParameter("RemainYCut",
								"Ycut for remain jet collection",
								_remainYcut,
								(double) -1.);


	registerProcessorParameter("NFermions",
								"number of fermions in event",
								_nfermions,
								(int)4);

	registerProcessorParameter("Nleptons",
								"number of leptons in event",
								_nleptons,
								(int) 2);
   
/*	registerProcessorParameter("Normalization",
								"event normalization bg/signal",
								weight,
								(double) 1.0);//deprecate this
*/
/*	registerProcessorParameter("Xsec",
								"Process crossection in fb",
								_xsec,
								(double) 1.0);

	registerProcessorParameter("XsecError",
							   "Error on cross section in fb",
								_xsecerr,
								(double) 1.0);
*/
/*	registerProcessorParameter("Njets",
								"number of jets from fast jet",
								_nJets,
								(int) 3);

	registerProcessorParameter("Ncuts",
								"nmber of event selection cuts",
								ncuts,
								(int) 0);
*/
	std::string defaultpath= "./";
	registerProcessorParameter("OutPath",
							   "path of output rootfile",
								_outpath,
								defaultpath );


}
	

//void WWAnalysis2::initTauFinderOptimization(){
void WWAnalysis2::inittree(){
		
		TTree* t = new TTree("tree","Tree");	
		int nColl = _tauJetCollectionsNames.size();
	
		std::vector< tauJet* > tauJets(nColl);
		std::vector< tauCand* > tauCands(nColl);
		std::vector< remainjet* > remJets(nColl);	
		std::vector< fitJet* > fitJets(nColl);
		
		t->Branch("xsec",&_xsec,"xsec/F");
		t->Branch("xsecerr",&_xsecerr,"xsecerr/F");
		//beam scenario
		t->Branch("beampart1", &_beampart1, "beampart1/I");
		t->Branch("beampart2", &_beampart2, "beampart2/I");
		t->Branch("polarization1", &_polarization1, "polarization1/I");
		t->Branch("polarization2", &_polarization2, "polarization2/I");
		
		t->Branch("nLL",&_nLL,"nLL/I");
		t->Branch("nRR",&_nRR,"nRR/I");
		t->Branch("nLR",&_nLR,"nLR/I");
		t->Branch("nRL",&_nRL,"nRL/I");
	
		t->Branch("nevt",&_nEvt,"nevt/I");
		t->Branch("ycut",&_remainYcut,"ycut/D");

		t->Branch("nPandoraTrks",&_nPandoraTrks,"nPandoraTrks/I");
		t->Branch("nPandoraPfos",&_nPandoraPfos,"nPandoraPfos/I");
		t->Branch("wwlike","vector<int>",&_wwlike );	
		//init 1 mc
		mcVars* mcv = new mcVars(_nfermions, _nleptons, t);
		_mcv = mcv;	
	

		for(unsigned int i=0; i<nColl; i++){
			tauJets.at(i) = new tauJet(i,t);
			tauCands.at(i) = new tauCand(i,t);
			remJets.at(i) = new remainjet(i,t);
			fitJets.at(i) = new fitJet(i,t);		
		}
		_tauJets = tauJets;
		_tauCands = tauCands;
		_remJets = remJets;
		_fitJets = fitJets;
		_tree = t;
		
		//the number of tau jet collections should match the number of remain collections
/*			std::vector<TTree*> t(_inputJetCollectionsNames.size());
			std::vector<tauFinderVariables*> f(_inputJetCollectionsNames.size());
			std::vector<mcVariables*> m(_inputJetCollectionsNames.size());

			std::vector<remainPfos*> r(_inputRemainCollectionsNames.size());
			std::vector<overlayVariables*> orp(_inputRemainCollectionsNames.size());

			std::vector<jetOverlay*> j1(_inputRemainCollectionsNames.size());

			_trees = t;
			_tf = f;
			_mcv = m;
			_rp = r;
			_ol1j = j1;

			//Here are some hax, make vector of ttree all pointers to the same tree
			//then we can make a no effort super tree with all the branches for working on the optimized taufinder
					TTree* supertree=new TTree("tree","Tree");
				
			//hacks will need to be removed if you want to do jet/tau optimization again

			for(unsigned int i=0; i< _inputJetCollectionsNames.size(); i++){
			//	_trees.at(i) = new TTree(_inputJetCollectionsNames.at(i).c_str(), _inputJetCollectionsNames.at(i).c_str());
			//begin hack
				_trees.at(i) = supertree;

				//for each tree init branches for event level information
				_trees.at(i)->Branch((_inputJetCollectionsNames.at(i)+"xsec").c_str(),&_xsec,"xsec/D");
				_trees.at(i)->Branch((_inputJetCollectionsNames.at(i)+"xsecerr").c_str(),&_xsecerr,"xsecerr/D");
				_trees.at(i)->Branch((_inputJetCollectionsNames.at(i)+"nevt").c_str(),&_nEvt,"nevt/I");
				_trees.at(i)->Branch((_inputJetCollectionsNames.at(i)+"ycut").c_str(),&_remainYcut,"ycut/D");

				_tf.at(i) = new tauFinderVariables(_inputJetCollectionsNames.at(i).c_str(), _trees.at(i));
				_tf.at(i)->initLocalTree();
				_mcv.at(i) = new mcVariables(_inputJetCollectionsNames.at(i).c_str(), _nfermions, _nleptons, _trees.at(i));
				_mcv.at(i)->initLocalTree();
				_rp.at(i) = new remainPfos(_inputRemainCollectionsNames.at(i).c_str(), _trees.at(i));
				_rp.at(i)->initLocalTree();

				_ol1j.at(i) = new jetOverlay(_inputRemainCollectionsNames.at(i).c_str(), _trees.at(i));
				_ol1j.at(i)->initLocalTree();
			
			}

			std::vector<jetVariables*> jsup( _inputRemainJetsCollNames.size() );
			_js = jsup;
			std::vector<jetOverlay*> olnj( _inputRemainJetsCollNames.size() );
			_rjOL = olnj;
			
			for(unsigned int i=0; i< _inputRemainJetsCollNames.size(); i++){
				if(_inputJetCollectionsNames.size() == 1){
					_js.at(i) = new jetVariables( _inputRemainJetsCollNames.at(i).c_str(), _trees.at(0));
					_js.at(i)->initLocalTree();
					_rjOL.at(i) = new jetOverlay( _inputRemainJetsCollNames.at(i).c_str(), _trees.at(0));
					_rjOL.at(i)->initLocalTree();

				}else if( _inputJetCollectionsNames.size() > 1){
					_js.at(i) = new jetVariables( _inputRemainJetsCollNames.at(i).c_str(), _trees.at(i));
					_js.at(i)->initLocalTree();
					_rjOL.at(i) = new jetOverlay( _inputRemainJetsCollNames.at(i).c_str(), _trees.at(i));
					_rjOL.at(i)->initLocalTree();
				}
			}
	*/			

			
}
void WWAnalysis2::init() {
  
  streamlog_out(DEBUG) << "   init called  " << std::endl;
  // usually a good idea to
  printParameters() ;

//init particle collection vectors
//	std::vector<std::vector<ReconstructedParticle*> > initParticleCollections(_inputJetCollectionsNames.size());
//	std::vector<std::vector<ReconstructedParticle*> > initRemainCollections( _inputRemainCollectionsNames.size());
	int size = _tauJetCollectionsNames.size();
	std::vector<std::vector<ReconstructedParticle*> > initTauJetColls(size);
	std::vector<std::vector<ReconstructedParticle*> > initTauCandColls(size);
	std::vector<std::vector<ReconstructedParticle*> > initRemJetColls(size);

	
	for(unsigned int i=0; i<size; i++){
		std::vector<ReconstructedParticle*> TJcoll{};
		std::vector<ReconstructedParticle*> TCcoll{};
		std::vector<ReconstructedParticle*> RJcoll{};
		//initParticleCollections.at(i)=Jcollection ;
		//_particleCollections.push_back(collection);
		//initRemainCollections.at(i)=Rcollection;
		initTauJetColls.at(i) = TJcoll;
		initTauCandColls.at(i) = TCcoll;
		initRemJetColls.at(i) = RJcoll;

	}
//	_particleCollections = initParticleCollections;
//	_remainCollections = initRemainCollections;
	_tauJetCollections = initTauJetColls;
	_tauCandCollections = initTauCandColls;
	_remJetCollections = initRemJetColls;
/*
	//init remainjet collections
	std::vector<std::vector<ReconstructedParticle*> > initRemainJetColl(_inputRemainJetsCollNames.size());
	for(unsigned int i=0; i<_inputRemainJetsCollNames.size(); i++){
		std::vector<ReconstructedParticle*> Jcollection{};
		initRemainJetColl.at(i) = Jcollection;
	}
	_remainJetCollections = initRemainJetColl;
*/

// std::cout<<"set filepath "<<std::endl;
  _outpath = _outpath+"file.root";
  file = new TFile(_outpath.c_str(),"RECREATE");

  inittree();
	
  _nRun = 0;
  _nEvt = 0;

  _nLL = 0;
  _nRR = 0;
  _nLR = 0;
  _nRL = 0;

	
}
void WWAnalysis2::processRunHeader( LCRunHeader* run) {
  streamlog_out(MESSAGE) << " processRunHeader "  << run->getRunNumber() << std::endl ;
}

/*****************
locate the pfo collection with specified name
populated the global pfo vectors with particles from that collection for this event
******************/

bool WWAnalysis2::FindPFOCollection( LCEvent* evt, std::string PfoCollectionName, std::vector<ReconstructedParticle*>& localVec ){
	bool collectionFound = false;

  	// clear old global pfovector
	localVec.clear();
  	typedef const std::vector<std::string> StringVec ;
  	StringVec* strVec = evt->getCollectionNames() ;
	
	//iterate over collections, find the matching name
  	for(StringVec::const_iterator itname=strVec->begin(); itname!=strVec->end(); itname++){
     
		//if found print name and number of elements
    		if(*itname==PfoCollectionName){ 
			LCCollection* collection = evt->getCollection(*itname);
			std::cout<< "Located Pfo Collection "<< *itname<< " with "<< collection->getNumberOfElements() << " elements " <<std::endl;
			collectionFound = true;

 			//add the collection elements to the global vector
      			for(int i=0; i<collection->getNumberOfElements(); i++){
				ReconstructedParticle* recoPart = dynamic_cast<ReconstructedParticle*>(collection->getElementAt(i));
				localVec.push_back(recoPart);
      			}
    		}
  	}
	
	if(!collectionFound){
		std::cout<<"Pfo Collection "<< PfoCollectionName << "not found"<<std::endl;
	}

   
	return collectionFound;
}
/*****************
locate the track collection with specified name
populate the global track vectors with tracks from the collection for this event
******************/
bool WWAnalysis2::FindTracks( LCEvent* evt ) {

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
bool WWAnalysis2::FindMCParticles( LCEvent* evt ){
   
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
/*bool WWAnalysis2::FindRecoToMCRelation( LCEvent* evt ){
   
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


//void WWAnalysis2::processOverlayVariables(overlayVariables*& oVar, std::vector<ReconstructedParticle*> jets, std::vector<MCParticle*> mcpartvec , std::vector<LCRelation*> pfo2mc){
/*	oVar->setParticles(jets, pfo2mc);

	oVar->setMCOverlay(oVar->_MCOverlay, oVar->_MCOverlayIDs, mcpartvec );
	//	std::cout<<"2"<<std::endl;
	oVar->setOverlayparticlesLoop(oVar->_overlayParticles, oVar->_tlvoverlayParticles, oVar->_purgedJets, oVar->_tlvpurgedJets, jets);
//	std::cout<<"3"<<std::endl;
	oVar->sumOverlayParticlesLoop(oVar->_tlvoverlaySum, oVar->_tlvoverlayParticles);
//	std::cout<<"4"<<std::endl;
	oVar->setTotalVariables();
*/
//}//


/*
void WWAnalysis2::initTauWithNoMCLepton(tauFinderVariables*& t){

	//set up a normal tau but dont set any MC info or do matching
	//assume particles have already been set, just deal with mc stuff
	std::vector<double> tempD{ -1 };
	t->_mcTau = new MCParticleImpl();
	t->_tauPsi = tempD;
	t->_indexOfMinTauPsi = -1;
	t->_minTauPsi = -1;

}
void WWAnalysis2::initEmptyTau(tauFinderVariables*& t, MCParticle* tau ){//when there are no tau jets reconstructed

	t->_nTaus=0;
	std::vector<int> tempI{ -1 };
	std::vector<double> tempD{ -1 };
	t->_tauTrkMult = tempI;
	t->_tauPfoMult = tempI;
	t->_tauCharge = tempD;
	t->_tauNOLTrks = tempI;
	t->_tauNOLPfos = tempI;
	t->_tauOLEFrac = tempD;
	t->_tauOLMFrac = tempD;
	t->_tauTrueFrac = tempD;

	//std::vector<ReconstructedParticle*> _taus{};
	std::vector<ReconstructedParticle*> tempP{ new ReconstructedParticleImpl() };
	t->_taus = tempP;
	std::vector<TLorentzVector*> tempT{new TLorentzVector() };
	t->_tlvtaus = tempT;

	std::vector<TLorentzVector> tempT2{};
	TLorentzVector tlv;
	tempT2.push_back(tlv);
	t->_taustest = tempT2;
	

	
	if( tau == NULL){
		initTauWithNoMCLepton(t);
	}
	else{
		t->setMCTau( tau );
		//also set null matching
		t->_tauPsi = tempD;
		t->_indexOfMinTauPsi = -1;
		t->_minTauPsi = -1;
	}

	

}
void WWAnalysis2::SetTauOptimizationVariables(LCEvent* evt){
	std::cout<<"Jet collections size "<< _particleCollections.size()<<std::endl;
	//do tau optimization stuff
	for(unsigned int i=0; i<_tf.size(); i++){
		//make sure we have jets in this particular collection
		if( _particleCollections.at(i).size() == 0){
			std::cout<<"No Taus in: "<< _inputJetCollectionsNames.at(i)<<std::endl;

			//have to save 
			_mcv.at(i)->setParticles(_mcpartvec);
			_mcv.at(i)->initMCVars();

			_rp.at(i)->_eselindex =-1;
			_rp.at(i)->_mcselindex = -1;
			_rp.at(i)->evaluateSelection();
			if( _mcv.at(i)->_isMuon || _mcv.at(i)->_isTau || _mcv.at(i)->_isElectron){
				//there is a lepton 
				initEmptyTau(  _tf.at(i), _mcv.at(i)->_MCPf.at(2));
			}
			else{
				//there is no lepton
			 	initEmptyTau( _tf.at(i), NULL);
			}
			//remove for hax
			//_trees.at(i)->Fill();
		}
		else{
			//there are reconstructed taus
			std::cout<<"setting parts and filling trees"<<std::endl;
			

			_tf.at(i)->setParticles(_particleCollections.at(i), _reco2mcvec);
			_tf.at(i)->setTauVariables();
			_mcv.at(i)->setParticles(_mcpartvec);
			_mcv.at(i)->initMCVars();

			_rp.at(i)->setParticles( _particleCollections.at(i),_remainCollections.at(i));
			_rp.at(i)->setESelIndex();
			_rp.at(i)->populateRemainFromSelIndex(_rp.at(i)->_eselindex, _rp.at(i)->_eselremainpfos , _rp.at(i)->_eselremainRP);



			//can look at overlay without an mc lep
			_ol1j.at(i)->setParticles(_rp.at(i)->_eselremainRP, _reco2mcvec, 1, _mcpartvec);
			_ol1j.at(i)->setOverlay();


			std::cout<<"about to check tf size :"<< _tf.size() <<std::endl;
			//if i=1 then J>= 1 dont allow multi jets when looping over multi parameter points of tau jets
			//if there taus then there are remain pfos to be clustered separately
			if( _tf.size() == 1 ){
				std::cout<<"about to loop over collection size "<< _remainJetCollections.size()<<std::endl;
				for(unsigned int J=0; J<_remainJetCollections.size(); J++){
					for(unsigned int K=0; K<_remainJetCollections.at(J).size(); K++){
						std::cout<<_remainJetCollections.at(J).at(K)->getEnergy()<<std::endl;
					}
					//std::cout<<"y+ "<<evt->getCollection(_inputRemainJetsCollNames.at(J))->getParameters().getFloatVal( "y_{n,n+1}" )<<std::endl;
					//std::cout<<"coll name "<< _inputRemainJetsCollNames.at(J)<<std::endl;
					_js.at(J)->setParticles(_remainJetCollections.at(J), evt, _inputRemainJetsCollNames.at(J));
					_rjOL.at(J)->setParticles( _remainJetCollections.at(J), _reco2mcvec, _remainJetCollections.at(J).size(), _mcpartvec);
					_rjOL.at(J)->setOverlay();
				}			
			}
			else if( _tf.size() > 1){
				
				_js.at(i)->setParticles(_remainJetCollections.at(i), evt, _inputRemainJetsCollNames.at(i));
				_rjOL.at(i)->setParticles( _remainJetCollections.at(i), _reco2mcvec, _remainJetCollections.at(i).size(), _mcpartvec);
				_rjOL.at(i)->setOverlay();
			}
	

			//make sure this isnt bg
			if( _mcv.at(i)->_isMuon || _mcv.at(i)->_isTau || _mcv.at(i)->_isElectron){
			//	_mcv.at(i)->setParticles(_mcpartvec);//throw in any jets
			//	_mcv.at(i)->initMCVars();
				_tf.at(i)->setMCTau(_mcv.at(i)->_MCPf.at(2)); //the mctau is any lepton
				_tf.at(i)->setMCTTauVariables();
				_tf.at(i)->setTauOLVariables(_mcpartvec);

				_rp.at(i)->setMCSelIndex( _tf.at(i)->_indexOfMinTauPsi );
				_rp.at(i)->populateRemainFromSelIndex(_rp.at(i)->_mcselindex, _rp.at(i)->_mcselremainpfos, _rp.at(i)->_mcselremainRP );
				_rp.at(i)->evaluateSelection();
				std::cout<< "mcindex "<< _rp.at(i)->_mcselindex<<" eindex "<< _rp.at(i)->_eselindex<<std::endl;

				
				

			}
			else{

				initTauWithNoMCLepton(_tf.at(i) );
			}
		
				//debug print OL
			//std::cout<<"debug print OL"<<std::endl;
			//_ol1j.at(i)->printOL();
			//_trees.at(i)->Fill();
			//continued super tree hacks
		//	_trees.at(0)->Fill(); //only fill one tree or we end up filling the same tree many times
		}

	}
	_trees.at(0)->Fill();

}*/
void WWAnalysis2::FillNtuple( LCEvent * evt ) {

	int ncoll = _tauJetCollectionsNames.size();
	//do mc separate
//	std::cout<< "populating mc "<<std::endl;
	_mcv->setParticles(_mcpartvec);
//remove mc population for now (to make higgs go faster)
	_mcv->initMCVars();	
//
//	std::cout<<"mc populated"<<std::endl;	
	//fill various classes
	for(int i=0; i<ncoll; i++){

//		std::cout<<" populating taujet "<<i<<std::endl;
		_tauJets.at(i)->setParticles(_tauJetCollections.at(i));
//		std::cout<<"taujet populated "<<std::endl;

//		std::cout<<"populating taucand "<<i<<std::endl;
		_tauCands.at(i)->setParticles(_tauCandCollections.at(i));
//		std::cout<<"taucand populated "<<std::endl;

//		std::cout<<"populating rem "<<i<< std::endl;
		_remJets.at(i)->setParticles(_remJetCollections.at(i));
//		std::cout<<"rem populated "<<std::endl;
	}
//	std::cout<<"filling tree"<<std::endl;
	//_tree->Fill();
//	std::cout<<"tree filled"<<std::endl;
}
void WWAnalysis2::dofit(int coneNumber){
	//determine WWlike
	if(_nPandoraTrks < 10){
		_wwlike.at(coneNumber) = 0;	
		 return;
	}
	if(_tauCandCollections.at(coneNumber).size() < 1){
		_wwlike.at(coneNumber) = 0;
		 return;
	}
	std::vector<ReconstructedParticle*> qqjets = _remJetCollections.at(coneNumber);
	if(qqjets.size() < 1){
		_wwlike.at(coneNumber) = 0;
		 return;
	}

	//do pt<2 cut on remjets transfer RP* to TLV
	std::vector<TLorentzVector> qqtlv{};
	for(unsigned int i=0; i< qqjets.size(); i++){
	//	TLorentzVector p;
		double px = qqjets.at(i)->getMomentum()[0];
		double py = qqjets.at(i)->getMomentum()[1];
		double pt = sqrt( px*px + py*py);
		if( pt > 2){
			double pz = qqjets.at(i)->getMomentum()[2];
			double E = qqjets.at(i)->getEnergy();
			TLorentzVector p(px,py,pz,E);
			qqtlv.push_back(p);
		}
	}
	//form wqq from qqtlv
	TLorentzVector Wqq;
	for(unsigned int i=0; i< qqtlv.size(); i++){
		Wqq += qqtlv.at(i);
	}

	//qq mass check
	if( Wqq.M() < 30. ){
		_wwlike.at(coneNumber) = 0;
	 return;
	}
	if( Wqq.M() > 140. ){
	 	_wwlike.at(coneNumber) = 0;
		return;
	}
	//at this point the event is WWLike
	_wwlike.at(coneNumber)=1;
	std::cout<<" WWLIKE! mass: "<<Wqq.M()<<" " <<std::endl;
	double qqdE = 0.5 * sqrt(Wqq.E());
	double dphi = 0.1;
	double dtheta = 0.1;

	//all criteria passed at this point, start up the constrained fit
//	JetFitObject *qqJFO = new JetFitObject( Wqq.E(), Wqq.Theta(), Wqq.Phi(), qqdE, dtheta, dphi, Wqq.M());
	//add all individual minijets 
	std::vector<JetFitObject*> qqJFOs(qqtlv.size());
	for(unsigned int i=0; i<qqJFOs.size(); i++){
		JetFitObject* jfo = new JetFitObject( qqtlv[i].E(),qqtlv[i].Theta(), qqtlv[i].Phi(), 0.8*sqrt(qqtlv[i].E()), 0.1,0.1, qqtlv[i].M());
		qqJFOs[i] = jfo;
	}

//prepare Wl side of the event //try to do this with lepton fit object later.. just use jets for now
	ReconstructedParticle* l = _tauCandCollections.at(coneNumber).at(0);
	TLorentzVector lep(l->getMomentum()[0], l->getMomentum()[1], l->getMomentum()[2], l->getEnergy());
	//create neutrino (remember it will still be boosted in x)

	//make two neutrinos with the two solutions to possible ISR energies
	double Eg1, Eg2;
	TLorentzVector Vis( Wqq.Px()+lep.Px(), Wqq.Py()+lep.Py(), Wqq.Pz()+lep.Pz(), Wqq.E()+lep.E() );
	double nsq = (500-Vis.E())*(500-Vis.E());	
	Eg1 = (nsq - Vis.Px()*Vis.Px() - Vis.Py()*Vis.Py() - Vis.Pz()*Vis.Pz()) / ( 1000 - 2*Vis.E()-2*Vis.Pz() );
	Eg2 = (nsq - Vis.Px()*Vis.Px() - Vis.Py()*Vis.Py() - Vis.Pz()*Vis.Pz()) / ( 1000 - 2*Vis.E()+2*Vis.Pz() );

	//form two neutrinos
	double nuz1, nuz2;
	nuz1 = -(Vis.E() + Eg1);
	nuz2 = -(Vis.E() + Eg2);

	TLorentzVector nu1, nu2;
	nu1.SetXYZM( -(lep.Px()+Wqq.Px()), -(lep.Py()+Wqq.Py()), nuz1, 0);
	nu2.SetXYZM( -(lep.Px()+Wqq.Px()), -(lep.Py()+Wqq.Py()), nuz2, 0);
	//form two leptonic Ws
	TLorentzVector Wl1 = lep + nu1;
	TLorentzVector Wl2 = lep + nu2;
	//take nu candidate closest to nominal W mass
	double m1diff,m2diff;
	m1diff = fabs(80. - Wl1.M());
	m2diff = fabs(80. - Wl2.M());
	double nuz, Eg;
	if( m1diff < m2diff ){
		nuz = nuz1;
		Eg = Eg1;	
	}
	else{
		nuz = nuz2;
		Eg = Eg2;
	}
	



	TLorentzVector nu;
	//try guessing half PZ to neutrino and half to ISR
//	nu.SetXYZM( 3.5-(lep.Px()+Wqq.Px()), -(lep.Py()+Wqq.Py()), -(lep.Pz()+Wqq.Pz()), 0. );
//		nu.SetXYZM( 3.5-(lep.Px()+Wqq.Px()), -(lep.Py()+Wqq.Py()), -(lep.Pz()+Wqq.Pz())/2., 0. );
	nu.SetXYZM( -(lep.Px()+Wqq.Px()), -(lep.Py()+Wqq.Py()), nuz, 0);

//	double ldE = 0.20  * sqrt( lep.E() );
//	JetFitObject *lJFO = new JetFitObject( lep.E(), lep.Theta(), lep.Phi(), ldE, 0.01, 0.01, lep.M());
	std::vector<LeptonFitObject*> lLFOs{};
	std::vector<JetFitObject*> lJFOs{};
	///loop over tracks and neutrals from tauCand class -> these values need to be populated in advancei
	//std::cout<<"about to do lep stuff"<<std::endl;
	tauCand* cand = _tauCands.at(coneNumber);
	for(unsigned int i=0; i< cand->_tracks.size(); i++){
		LeptonFitObject* lfo= new LeptonFitObject(cand->_tracks.at(i), cand->_bfield, 0);//assume mass is 0 for now
		lLFOs.push_back(lfo);
	}
	//create the neutral part of the lepton (assume its all photons)-> photon error model
	for(unsigned int i=0;i< cand->_candNeuPx.size(); i++){
		TLorentzVector p(cand->_candNeuPx[i], cand->_candNeuPy[i], cand->_candNeuPz[i], cand->_candNeuE[i]);
		JetFitObject* jfo = new JetFitObject(p.E(), p.Theta(), p.Phi(), 0.2*sqrt(p.E()),0.1,0.1);
		lJFOs.push_back(jfo);
	}
//	std::cout<<"did lep stuff"<<std::endl;

//	double ndE =;
	NeutrinoFitObject *nFO = new NeutrinoFitObject( nu.E(), nu.Theta(), nu.Phi(), 0.8*sqrt(nu.E()), dtheta, dphi);

	MomentumConstraint pxc (0, 1, 0, 0, 3.5);//xangle boost 3.5Gev in x
        pxc.setName("sum(p_x)");
//	pxc.addToFOList( *qqJFO );
	for(unsigned int i=0; i<qqJFOs.size(); i++){
		pxc.addToFOList( *(qqJFOs[i]) );
	
	}
//	pxc.addToFOList( *lJFO );
	for(unsigned int i=0; i<lLFOs.size(); i++){
		pxc.addToFOList( *(lLFOs[i]) );
	}
	for(unsigned int i=0; i<lJFOs.size(); i++){
		pxc.addToFOList( *(lJFOs[i]) );
	}
	pxc.addToFOList( *nFO );
        
	MomentumConstraint pyc (0, 0, 1);
        pyc.setName("sum(p_y)");
//	pyc.addToFOList( *qqJFO );
        for(unsigned int i=0; i<qqJFOs.size(); i++){
                pyc.addToFOList( *(qqJFOs[i]) );
        }

//	pyc.addToFOList( *lJFO );
	for(unsigned int i=0; i<lLFOs.size(); i++){
                pyc.addToFOList( *(lLFOs[i]) );
        }
        for(unsigned int i=0; i<lJFOs.size(); i++){
                pyc.addToFOList( *(lJFOs[i]) );
        }
	pyc.addToFOList( *nFO );

        MomentumConstraint pzc (0, 0, 0, 1);
        pzc.setName("sum(p_z)");
//	pzc.addToFOList( *qqJFO );
        for(unsigned int i=0; i<qqJFOs.size(); i++){
                pzc.addToFOList( *(qqJFOs[i]) );
        }

//	pzc.addToFOList( *lJFO );
	for(unsigned int i=0; i<lLFOs.size(); i++){
                pzc.addToFOList( *(lLFOs[i]) );
        }
        for(unsigned int i=0; i<lJFOs.size(); i++){
                pzc.addToFOList( *(lJFOs[i]) );
        }
	pzc.addToFOList( *nFO );

	MomentumConstraint ec(1, 0, 0, 0, 500);
        ec.setName("sum(E)");
//	ec.addToFOList( *qqJFO );
        for(unsigned int i=0; i<qqJFOs.size(); i++){
                ec.addToFOList( *(qqJFOs[i]) );
        }

//	ec.addToFOList( *lJFO );
	for(unsigned int i=0; i<lLFOs.size(); i++){
                ec.addToFOList( *(lLFOs[i]) );
        }
        for(unsigned int i=0; i<lJFOs.size(); i++){
                ec.addToFOList( *(lJFOs[i]) );
        }
	ec.addToFOList( *nFO );


//  b = (double) 0.00464564*( std::log(_ecm*_ecm*3814714.)-1. );
  //= 2*alpha/pi*( ln(s/m_e^2)-1 )
  //  ISRPzMaxB = std::pow((double)_isrpzmax,b);
	double b =  0.00464564*( std::log(500*500*3814714.)-1. );
	double ISRPzMaxB = std::pow(225.,b);
//	ISRPhotonFitObject *photon = new ISRPhotonFitObject (0., 0., -pzc.getValue(), b, ISRPzMaxB);
//		ISRPhotonFitObject *photon = new ISRPhotonFitObject (0., 0., nu.Pz(), b, ISRPzMaxB);
	ISRPhotonFitObject *photon = new ISRPhotonFitObject(0.,0.,Eg, b, ISRPzMaxB);
	pxc.addToFOList (*(photon));
        pyc.addToFOList (*(photon));
        pzc.addToFOList (*(photon));
        ec.addToFOList  (*(photon));
		
        MassConstraint w(0.);
//        w.addToFOList (*qqJFO, 1);
        for(unsigned int i=0; i<qqJFOs.size(); i++){
                w.addToFOList( *(qqJFOs[i]),1 );
        }

//        w.addToFOList (*lJFO, 2);
	for(unsigned int i=0; i<lLFOs.size(); i++){
                w.addToFOList( *(lLFOs[i]), 2 );
        }
        for(unsigned int i=0; i<lJFOs.size(); i++){
                w.addToFOList( *(lJFOs[i]), 2 );
        }
        w.addToFOList (*nFO, 2);


	BaseFitter *pfitter;
	pfitter = new OPALFitterGSL();
	BaseFitter &fitter = *pfitter;

//	fitter.addFitObject( *qqJFO );
        for(unsigned int i=0; i<qqJFOs.size(); i++){
                fitter.addFitObject( *(qqJFOs[i]) );
        }
	for(unsigned int i=0; i<lLFOs.size(); i++){
		fitter.addFitObject(*(lLFOs[i]));
	}
	for(unsigned int i=0; i<lJFOs.size(); i++){
		fitter.addFitObject(*(lJFOs[i]) );
	}

//	fitter.addFitObject( *lJFO );
	fitter.addFitObject( *nFO );
	fitter.addFitObject( *photon);

	fitter.addConstraint (pxc);
        fitter.addConstraint (pyc);
        fitter.addConstraint (pzc);
        fitter.addConstraint (ec);
        fitter.addConstraint (w);

	//_fitprob = fitter.fit();
	//_chi2 = fitter.getChi2();
	double fitprob;
	double chi2;
	
	fitprob = fitter.fit();
	chi2 = fitter.getChi2();
//std::cout<<fitprob<<" ";
//	TLorentzVector* qqtlv = new TLorentzVector(qqJFO->getPx(), qqJFO->getPy(), qqJFO->getPz(), qqJFO->getE());
//	TLorentzVector* ltlv = new TLorentzVector(lJFO->getPx(), lJFO->getPy(), lJFO->getPz(), lJFO->getE());
//	TLorentzVector* nutlv = new TLorentVector(nFO->getPx(), nFO->getPy(), nFO->getPz(), nFO->getE());
//	TLorentzVector* gtlv = new TLorentzVector(photon->getPx(), photon->getPy(), photon->getPz(), photon->getE());
	
	//gotta stick fit objects onto vector
//	std::vector<JetFitObject*> qqvec{ qqJFO };
//	std::vector<JetFitObject*> lvec{ lJFO };
	
//make this just to fill
//ISRPhotonFitObject *photon = new ISRPhotonFitObject(0,0.,Eg,b,ISRPzMaxB);
//MassConstraint w(0.);
//	_fitJets.at(coneNumber)->setParticles(qqvec, lvec, nFO, photon, w, fitprob, chi2);
//	_fitJets.at(coneNumber)->setParticles(qqJFOs, lvec, nFO, photon, w, fitprob, chi2);
	_fitJets.at(coneNumber)->setParticles(qqJFOs, lLFOs, lJFOs,nFO, photon, w, fitprob,chi2, nuz, Eg);

}
void WWAnalysis2::processEvent( LCEvent * evt ) {
 //std::cout<<"
 std::cout<<"Ycut: "<< _remainYcut<<std::endl;
 std::cout<<"event No. "<< _nEvt<<std::endl;
 // Get Process name and cross section
 //  *_Process = evt->getParameters().getStringVal("Process");
 // _xsec = evt->getParameters().getFloatVal("CrossSection_fb");

// FindRecoToMCRelation( evt );
 FindMCParticles(evt);
// FindJets(evt);
//
//automatically load PandoraPFOs to get multiplicity
FindPFOCollection( evt, "PandoraPFOs", _pandoraPFOs);

int ncoll = _tauJetCollectionsNames.size();
for(int i=0; i< ncoll; i++){
	FindPFOCollection(evt, _tauJetCollectionsNames.at(i), _tauJetCollections.at(i));
	FindPFOCollection(evt, _tauCandCollectionsNames.at(i), _tauCandCollections.at(i));
	FindPFOCollection(evt, _remJetCollectionsNames.at(i), _remJetCollections.at(i));
} 
/*
for(unsigned int i=0; i<_inputJetCollectionsNames.size(); i++){
	FindPFOCollection(evt, _inputJetCollectionsNames.at(i), _particleCollections.at(i));
	FindPFOCollection(evt, _inputRemainCollectionsNames.at(i), _remainCollections.at(i));
}
for(unsigned int i=0; i<_inputRemainJetsCollNames.size(); i++){
	FindPFOCollection(evt, _inputRemainJetsCollNames.at(i), _remainJetCollections.at(i));
}*/

//doing tau optimization
//SetTauOptimizationVariables(evt);
//extract event level information
std::string bp1;
std::string bp2;
std::string pol1;
std::string pol2; 
	_xsec = evt->parameters().getFloatVal("crossSection");
	_xsecerr = evt->parameters().getFloatVal("crossSectionError");
	
	bp1 = evt->parameters().getStringVal("beam_particle1");
	bp2 = evt->parameters().getStringVal("beam_particle2");
	
	pol1 = evt->parameters().getStringVal("polarization1");
	pol2 = evt->parameters().getStringVal("polarization2");

		

	if( bp1.compare("e1") == 0){
		_beampart1 = -1;
		_beampart2 = 1;
	}
	else{
		_beampart1 = 1;
		_beampart2 = -1;
	}

	if(pol1.compare("L")==0){
		_polarization1 = -1;
	}
	else{ 
		_polarization1 = 1;
	}
	if(pol2.compare("L")==0){
		_polarization2 = -1;
	}
	else{
		_polarization2 = 1;
	}


	//fill pandora pfo vars
	_nPandoraPfos = _pandoraPFOs.size();
	_nPandoraTrks = 0;
	for(unsigned int i=0; i<_pandoraPFOs.size(); i++){
		if(_pandoraPFOs.at(i)->getCharge() != 0){
			_nPandoraTrks = _nPandoraTrks + 1;
		}
	}

	if(_polarization1 == -1 && _polarization2 == -1){
		_nLL++;
	}
	if(_polarization1 == -1 && _polarization2 == 1){
		_nLR++;
	}
	if(_polarization1 == 1 && _polarization2 == 1){
		_nRR++;
	}
	if(_polarization1 == 1 && _polarization2 == -1){
		_nRL++;
	}


	FillNtuple(evt);
	std::cout<<"event number "<<_nEvt<<" ";
	//reset this
//	_wwlike[0] = 0;
	//determine if event is WW like, if it is do a 5C fit. the fit has to be w.r.t some specific cone and lepton selection
//	dofit(0);//arg conenumber 0 = muon	
	dofit(0);	
	//FillNtuple(evt);
	_tree->Fill();
 _nEvt++;
}
void WWAnalysis2::end(){

	

	/* print out stuff */
/*
	std::cout<<" nelec "<<nelec<<" nmuon "<< nmuon <<" ntau "<< ntau << std::endl;
	std::cout<<" nevents "<< nEvt << " mu q match "<< muonqmatch <<  " tau q match "<< tauqmatch <<std::endl;

	std::cout<<" jet match tau "<<ljetmatchmctau<<" "<<ljetmatchmcmuon<<std::endl;
*/
	file->Write();
}


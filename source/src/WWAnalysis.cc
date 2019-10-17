#include "WWAnalysis.h"

WWAnalysis aWWAnalysis;

WWAnalysis::WWAnalysis() : Processor("WWAnalysis") {


	//load vector<TLorentzVector>
	//gROOT->ProcessLine("cd()");
	gROOT->ProcessLine(".L ~/work/repos/ILDbench_WWqqlnu/source/src/loader.C+");

  // register steering parameters: name, description, class-variable, default value

	registerProcessorParameter( "Printing" ,
	                            "Print certain messages"  ,
	                             _printing,
	                             (int)5 ) ;

	registerProcessorParameter( "RunSignalMode",
								"toggle to run over signal or bg events",
								_runSignalMode,
								(int) 1 );

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
							"InputJetCollectionsNames",
							"Name of the Input particle collections",
							_inputJetCollectionsNames,
							inputCollectionNames);
 
    	//input remain collection 
	std::vector<std::string> inputRemainCollectionsNames{"x"};
	registerInputCollections( LCIO::RECONSTRUCTEDPARTICLE,
					"InputRemainCollectionsNames",
					"Input Remain Collections Name",
					_inputRemainCollectionsNames,
					inputRemainCollectionsNames);

	std::vector<std::string> inputRemainJetsCollNames{"x"};
	registerInputCollections( LCIO::RECONSTRUCTEDPARTICLE,
					"InputRemainJetCollectionsNames",
					"name of jet collection formed from Remain Pfos",
					_inputRemainJetsCollNames,
					inputRemainJetsCollNames);


	std::string inputRecoRelationCollectionName = "x";
  	registerInputCollection( LCIO::LCRELATION,
			     	"InputRecoRelationCollectionName" , 
			     	"Input Reco Relation Collection Name "  ,
			     	_inputRecoRelationCollectionName,
			      	inputRecoRelationCollectionName);

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
   
	registerProcessorParameter("Normalization",
								"event normalization bg/signal",
								weight,
								(double) 1.0);//deprecate this

	registerProcessorParameter("Xsec",
								"Process crossection in fb",
								_xsec,
								(double) 1.0);

	registerProcessorParameter("XsecError",
							   "Error on cross section in fb",
								_xsecerr,
								(double) 1.0);

	registerProcessorParameter("Njets",
								"number of jets from fast jet",
								_nJets,
								(int) 3);

	registerProcessorParameter("Ncuts",
								"nmber of event selection cuts",
								ncuts,
								(int) 0);

	std::string defaultpath= "./";
	registerProcessorParameter("OutPath",
							   "path of output rootfile",
								_outpath,
								defaultpath );


}
	

void WWAnalysis::initTauFinderOptimization(){

		//the number of tau jet collections should match the number of remain collections
			std::vector<TTree*> t(_inputJetCollectionsNames.size());
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
			

			
}
void WWAnalysis::init() {
  
  streamlog_out(DEBUG) << "   init called  " << std::endl;
  // usually a good idea to
  printParameters() ;

//init particle collection vectors
	std::vector<std::vector<ReconstructedParticle*> > initParticleCollections(_inputJetCollectionsNames.size());
	std::vector<std::vector<ReconstructedParticle*> > initRemainCollections( _inputRemainCollectionsNames.size());
	for(unsigned int i=0; i<_inputJetCollectionsNames.size(); i++){
		std::vector<ReconstructedParticle*> Jcollection{};
		std::vector<ReconstructedParticle*> Rcollection{};
		initParticleCollections.at(i)=Jcollection ;
		//_particleCollections.push_back(collection);
		initRemainCollections.at(i)=Rcollection;
	}
	_particleCollections = initParticleCollections;
	_remainCollections = initRemainCollections;

	//init remainjet collections
	std::vector<std::vector<ReconstructedParticle*> > initRemainJetColl(_inputRemainJetsCollNames.size());
	for(unsigned int i=0; i<_inputRemainJetsCollNames.size(); i++){
		std::vector<ReconstructedParticle*> Jcollection{};
		initRemainJetColl.at(i) = Jcollection;
	}
	_remainJetCollections = initRemainJetColl;


// std::cout<<"set filepath "<<std::endl;
  _outpath = _outpath+"file.root";
  file = new TFile(_outpath.c_str(),"RECREATE");

  initTauFinderOptimization();
	
  _nRun = 0;
  _nEvt = 0;



	
}
void WWAnalysis::processRunHeader( LCRunHeader* run) {
  streamlog_out(MESSAGE) << " processRunHeader "  << run->getRunNumber() << std::endl ;
}

/*****************
locate the pfo collection with specified name
populated the global pfo vectors with particles from that collection for this event
******************/

bool WWAnalysis::FindPFOCollection( LCEvent* evt, std::string PfoCollectionName, std::vector<ReconstructedParticle*>& localVec ){
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


void WWAnalysis::processOverlayVariables(overlayVariables*& oVar, std::vector<ReconstructedParticle*> jets, std::vector<MCParticle*> mcpartvec , std::vector<LCRelation*> pfo2mc){
/*	oVar->setParticles(jets, pfo2mc);

	oVar->setMCOverlay(oVar->_MCOverlay, oVar->_MCOverlayIDs, mcpartvec );
	//	std::cout<<"2"<<std::endl;
	oVar->setOverlayparticlesLoop(oVar->_overlayParticles, oVar->_tlvoverlayParticles, oVar->_purgedJets, oVar->_tlvpurgedJets, jets);
//	std::cout<<"3"<<std::endl;
	oVar->sumOverlayParticlesLoop(oVar->_tlvoverlaySum, oVar->_tlvoverlayParticles);
//	std::cout<<"4"<<std::endl;
	oVar->setTotalVariables();
*/
}



void WWAnalysis::initTauWithNoMCLepton(tauFinderVariables*& t){

	//set up a normal tau but dont set any MC info or do matching
	//assume particles have already been set, just deal with mc stuff
	std::vector<double> tempD{ -1 };
	t->_mcTau = new MCParticleImpl();
	t->_tauPsi = tempD;
	t->_indexOfMinTauPsi = -1;
	t->_minTauPsi = -1;

}
void WWAnalysis::initEmptyTau(tauFinderVariables*& t, MCParticle* tau ){//when there are no tau jets reconstructed

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
void WWAnalysis::SetTauOptimizationVariables(LCEvent* evt){
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

}
void WWAnalysis::processEvent( LCEvent * evt ) {

 std::cout<<"Ycut: "<< _remainYcut<<std::endl;
 std::cout<<"event No. "<< _nEvt<<std::endl;
 // Get Process name and cross section
 //  *_Process = evt->getParameters().getStringVal("Process");
 // _xsec = evt->getParameters().getFloatVal("CrossSection_fb");

 FindRecoToMCRelation( evt );
 FindMCParticles(evt);
// FindJets(evt);
for(unsigned int i=0; i<_inputJetCollectionsNames.size(); i++){
	FindPFOCollection(evt, _inputJetCollectionsNames.at(i), _particleCollections.at(i));
	FindPFOCollection(evt, _inputRemainCollectionsNames.at(i), _remainCollections.at(i));
}
for(unsigned int i=0; i<_inputRemainJetsCollNames.size(); i++){
	FindPFOCollection(evt, _inputRemainJetsCollNames.at(i), _remainJetCollections.at(i));
}

//doing tau optimization
SetTauOptimizationVariables(evt);


 _nEvt++;
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


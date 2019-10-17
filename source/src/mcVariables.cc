#include "mcVariables.h"


mcVariables::mcVariables(const char* variableSetName, int nfermions, int nleptons, TTree*& tree){
	_variableSetName = variableSetName;
	_nfermions = nfermions;
	_nleptons = nleptons;
	
	_localTree = tree;
	
	//allocate correct size for fermion vectors
	std::vector<TLorentzVector*> mcf(nfermions);
	for(unsigned int i=0; i<mcf.size(); i++){
		mcf.at(i) = new TLorentzVector();
	}
	_MCf = mcf;
	std::vector<int> mcfpdg(nfermions);
	_MCfpdg = mcfpdg;

	std::vector<MCParticle*> mcpf(nfermions);
	_MCPf = mcpf;




}
void mcVariables::setParticles(std::vector<MCParticle*>& mcpartvec ){
	_mcpartvec = mcpartvec;
}
//recursive helper
bool mcVariables::allChildrenAreSimulation(MCParticle* p){
	std::vector<MCParticle*> d = p->getDaughters();
	bool flag = true;
	for(unsigned int i=0; i<d.size(); i++){
		if( ! d.at(i)->isCreatedInSimulation() ){
			flag= false;
		}
	}
	return flag;
}
//recursive function to go through and look at the decay chain of a particle
//look at specifically charged particles
void mcVariables::exploreDaughterParticles(MCParticle* p , std::vector<MCParticle*>& FSP){
	if(p->isCreatedInSimulation()) return;

	//std::cout<<p->id()<<" ";
	//std::cout<<p->getPDG()<<" -> ";
	std::vector<MCParticle*> d = p->getDaughters();
	
	for(unsigned int i=0; i< d.size(); i++){
		if( (! d.at(i)->isCreatedInSimulation() ) && ( allChildrenAreSimulation(d.at(i)) || (d.at(i)->getDaughters().size()==0)  ) ){
		//this is an initial final state particle
			FSP.push_back(d.at(i));
		}
		//if( (! d.at(i)->isCreatedInSimulation()) ){//&& (d.at(i)->getCharge() != 0) ){
		//	std::cout<< "( "<< d.at(i)->id()<<" "<<d.at(i)->getPDG() <<" "<< d.at(i)->isDecayedInTracker()<<" "<< d.at(i)->isDecayedInCalorimeter()<<" ) ";
		//}
	}
	//std::cout<<std::endl;
	for(unsigned int i=0; i<d.size(); i++){
		exploreDaughterParticles(d.at(i), FSP);
	}
		
}
void mcVariables::getMCLeptonMult(std::vector<MCParticle*>& FSPs){
  int countparts=0;
  int counttracks=0;
  for(unsigned int i=0; i<FSPs.size(); i++){
		if( (abs(FSPs.at(i)->getPDG()) == 12) || (abs(FSPs.at(i)->getPDG()) == 14) || (abs(FSPs.at(i)->getPDG()) == 16)){
		//	std::cout<<"neut skipped"<<std::endl;
			continue;
		}
		else{
			//not a neutrino
			if(FSPs.at(i)->getCharge() != 0){
				counttracks++;
			}
			//count tracks and neutrals
			countparts++;
		//f	std::cout<<"part counted"<<std::endl;
		}
  }

  _mclepPfoMult = countparts;
  _mclepTrkMult = counttracks;
}
int mcVariables::getTauDecayMode(MCParticle* mctau){
		//1= muon 2=elec 3=had1p 4=had3p 5=other (5p)
		//with the tau mcp get its immediate decay products
		//from daniels code decayChPi=0, decayRho, decayA1_1p, decayA1_3p , decayEl, decayMu , decayW , decayK , decayMultiprong , decayOthersingleprong, decayUnrecognised
		int mode = classifyTau::getMCdecayMode(mctau);
		if(mode == 5) return 1;
		if(mode == 4) return 2;

		//if its something else just count tracks
		std::vector<MCParticle*> dec =  classifyTau::getstablemctauDaughters(mctau);
	//	std::cout<<"TAU DETAILS"<<std::endl;
	//	std::cout<<"N tau daughters = "<<dec.size()<<std::endl;
	//	std::cout<<"tau daughter pdg = ";
		int tcount = 0;
		for(unsigned int i=0; i< dec.size(); i++){
	//		std::cout<< dec.at(i)->getPDG();
				if(dec.at(i)->getCharge() != 0){
					tcount++;
				}
		}
	//	std::cout<<std::endl;
	//	std::cout<<"N tau tracks = "<<tcount<<std::endl;
		if(tcount == 1) return 3;
		if(tcount == 3) return 4;
		return 5;
		
}
void mcVariables::initMCVars(){

	for(unsigned int i=0; i<_mcpartvec.size(); i++){
		std::vector<int> parentpdgs{};
		std::vector<int> daughterpdgs{};
		std::vector<MCParticle*> mcparents{};
		std::vector<MCParticle*> daughters{};
	
		daughters = _mcpartvec.at(i)->getDaughters();
		for(unsigned int j = 0; j<daughters.size(); j++){
			daughterpdgs.push_back(daughters.at(j)->getPDG());
			
		}
		//allowed quarks
		std::vector<int> quarks{ 1, 2, 3, 4, 5, -1, -2, -3, -4, -5};
		std::vector<int> leptons{11, 12, 13, 14, 15, 16, -11, -12, -13, -14, -15, -16};
		//we require exactly 2 elements from leptons and 2 from quarks
		int lep=0;
		int qrk=0;

		//categorize the event for plotting
		for(unsigned int k=0; k<quarks.size(); k++){
			qrk += std::count(daughterpdgs.begin(),daughterpdgs.end(),quarks.at(k));
		}
		for(unsigned int k=0; k<leptons.size(); k++){
			lep += std::count(daughterpdgs.begin(),daughterpdgs.end(),leptons.at(k));
		}
		TLorentzVector qq;
		if( qrk == (_nfermions-_nleptons) && lep == _nleptons){

			
			
			for(unsigned int j=0; j<daughters.size(); j++){
				
               // TLorentzVector mcVec(TVector3(daughters.at(j)->getMomentum()),daughters.at(j)->getEnergy());
				TLorentzVector mcVec;
				mcVec.SetXYZM(daughters.at(j)->getMomentum()[0], daughters.at(j)->getMomentum()[1], daughters.at(j)->getMomentum()[2], daughters.at(j)->getMass() );
				_MCPf[j] = daughters.at(j);
                *_MCf[j] = mcVec;
                _MCfpdg[j] = daughters.at(j)->getPDG();

				//is this the lepton?
				if(abs(_MCfpdg[j]) == 13  || abs(_MCfpdg[j]) == 15 || abs(_MCfpdg[j]) == 11){
					//mcl = new TLorentzVector(mcVec.Vect(),mcVec.E());
					_mcl = new TLorentzVector();
					_mcl->SetXYZM( mcVec.Px(), mcVec.Py(), mcVec.Pz(), mcVec.M() );

					//also get all of the leptons visible FSP
					std::vector<MCParticle*> mclepFSP{};
					exploreDaughterParticles(daughters.at(i), mclepFSP );
					getMCLeptonMult( mclepFSP );
				}
				if(abs(_MCfpdg[j]) < 6){
					qq += *_MCf[j];
				}
			}//end daughter loop
			_mcqq = new TLorentzVector(qq.Vect(),qq.E());


			if (std::find(daughterpdgs.begin(),daughterpdgs.end(), 13) != daughterpdgs.end() ||
				std::find(daughterpdgs.begin(),daughterpdgs.end(), -13) != daughterpdgs.end() ){
				//identify event containing muon
				_isMuon = true;
				_isTau = false;
				_isElectron = false;
				_tauType = 0;
				//get true charge of the muon
				if (std::find(daughterpdgs.begin(),daughterpdgs.end(), 13) != daughterpdgs.end() ){
					_mclepCharge = -1;
				}
				else{
					_mclepCharge = 1;
				}
			}
			if (std::find(daughterpdgs.begin(),daughterpdgs.end(), 15) != daughterpdgs.end() ||
				std::find(daughterpdgs.begin(),daughterpdgs.end(), -15) != daughterpdgs.end() ){
				//ntau++;
				//identify event containing a tau
				_isTau = true;
				_isMuon = false;
				_isElectron=false;
				

				
				for(unsigned int I=0; I<daughters.size(); I++){
					if( abs(daughters.at(I)->getPDG())==15){
						_tauType = getTauDecayMode(daughters.at(I));
					
					//save stable daughters
				    std::vector<MCParticle*> dec =  classifyTau::getstablemctauDaughters(daughters.at(I));
					std::vector<TLorentzVector> mctaudaughters{};
					std::vector<int> mctaudaughterspdg{};
					std::vector<double> mctaudaughterscharge{};

					std::vector<TLorentzVector> mcinvisdaughters{};
					std::vector<int> mcinvisdaughterspdg{};

					
					for(unsigned int K =0; K<dec.size(); K++){
						int taupdg = abs(dec.at(K)->getPDG());
						if( taupdg != 12 && taupdg != 14 && taupdg != 16 ){
							TLorentzVector t;
							t.SetXYZM(dec.at(K)->getMomentum()[0], dec.at(K)->getMomentum()[1], dec.at(K)->getMomentum()[2], dec.at(K)->getMass() );
							mctaudaughters.push_back( t);
							mctaudaughterspdg.push_back(dec.at(K)->getPDG());
							mctaudaughterscharge.push_back( dec.at(K)->getCharge());
						}
						else{
							TLorentzVector t;
							t.SetXYZM(dec.at(K)->getMomentum()[0], dec.at(K)->getMomentum()[1], dec.at(K)->getMomentum()[2], dec.at(K)->getMass() );
							mcinvisdaughters.push_back( t);
							mcinvisdaughterspdg.push_back(dec.at(K)->getPDG());
						}
					}

					_MCTauVisibleDaughters = mctaudaughters;
					_MCTauVisibleDaughters_pdg = mctaudaughterspdg;
					_MCTauVisibleDaughters_charge = mctaudaughterscharge;

					_MCTauInvisibleDaughters = mcinvisdaughters;
					_MCTauInvisibleDaughters_pdg = mcinvisdaughterspdg;

					}//end get mctau
			
				}

				//save the stable daughters
				

				//identify the true charge of the lepton
				if (std::find(daughterpdgs.begin(),daughterpdgs.end(), 15) != daughterpdgs.end() ){
					_mclepCharge = -1;
				}
				else{
					_mclepCharge = 1;
				}
			}
			if (std::find(daughterpdgs.begin(),daughterpdgs.end(), 11) != daughterpdgs.end() ||
				std::find(daughterpdgs.begin(),daughterpdgs.end(), -11) != daughterpdgs.end() ){
				//identify event containing electron
				_isMuon = false;
				_isTau = false;
				_isElectron = true;
				_tauType = 0;
				//get true charge of the electron
				if (std::find(daughterpdgs.begin(),daughterpdgs.end(), 11) != daughterpdgs.end() ){
					_mclepCharge = -1;
				}
				else{
					_mclepCharge = 1;
				}
			}
	
			
			//if we have found the true decay set break out of the mcpart vec loop
			return;
			//break;
		}//end if 2qrk & 2 lep

	}//end mcpartvec loop

	//if nothing is found return 
	return;
}
void mcVariables::initLocalTree(){
	std::string vsn(_variableSetName);

	/*** Tree MC info ***/
	_localTree->Branch((vsn+"isMuon").c_str(), &_isMuon,(vsn+"isMuon/O").c_str());
	_localTree->Branch((vsn+"isTau").c_str(),&_isTau,(vsn+"isTau/O").c_str());
	_localTree->Branch((vsn+"isElectron").c_str(),&_isElectron,(vsn+"isElectron/O").c_str());
	_localTree->Branch((vsn+"tauType").c_str(),&_tauType,(vsn+"tauType/I").c_str());
	_localTree->Branch((vsn+"mclepCharge").c_str(), &_mclepCharge,(vsn+"mclepCharge/I").c_str());

	_localTree->Branch((vsn+"mclepTrkMult").c_str(), &_mclepTrkMult,(vsn+"mclepTrkMult/I").c_str());
	_localTree->Branch((vsn+"mclepPfoMult").c_str(), &_mclepPfoMult,(vsn+"mclepProMult/I").c_str());

	//add alll the other vars here
	for(int i=0; i< _nfermions; i++){
		std::stringstream name;
		name << _variableSetName << "MCf" << i;
		_localTree->Branch(name.str().c_str(),"TLorentzVector",&_MCf[i],16000,0);
		name <<"_PDG";
		_localTree->Branch(name.str().c_str(), &_MCfpdg.at(i), (name.str()+"/I").c_str());
	}

	_localTree->Branch((vsn+"MCTauVisibleDaughters").c_str(),"vector<TLorentzVector>", &_MCTauVisibleDaughters);//TODO fill this
	_localTree->Branch((vsn+"MCTauVisibleDaughters_pdg").c_str(),"vector<int>", &_MCTauVisibleDaughters_pdg);
	_localTree->Branch((vsn+"MCTauVisibleDaughters_charge").c_str(),"vector<double>", &_MCTauVisibleDaughters_charge);

	_localTree->Branch((vsn+"MCTauInvisibleDaughters").c_str(),"vector<TLorentzVector>", &_MCTauInvisibleDaughters);
	_localTree->Branch((vsn+"MCTauInvisibleDaughters_pdg").c_str(),"vector<int>", &_MCTauInvisibleDaughters_pdg);

	_localTree->Branch((vsn+"mcl").c_str(),"TLorentzVector",&_mcl,16000,0);
	_localTree->Branch((vsn+"mcqq").c_str(),"TLorentzVector",&_mcqq,16000,0);
	//_localTree->Branch("mcqq.",&_mcl);
	
	

	
}

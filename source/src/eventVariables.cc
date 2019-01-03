
#include "eventVariables.h"

eventVariables::eventVariables(const char* variableSetName, int nfermions, int nleptons, int nJets, TTree*& tree){
	_variableSetName = variableSetName;
	_nfermions = nfermions;
	_nleptons = nleptons;
	_nJets = nJets;
	_localTree = tree;
	
	//allocate correct size for fermion vectors
	std::vector<TLorentzVector*> mcf(nfermions);
	for(unsigned int i=0; i<mcf.size(); i++){
		mcf.at(i) = new TLorentzVector();
	}
	_MCf = mcf;
	std::vector<int> mcfpdg(nfermions);
	_MCfpdg = mcfpdg;

	std::vector<TLorentzVector*> j1(nJets);
	std::vector<TLorentzVector*> j2(nJets);
	std::vector<TLorentzVector*> j3(nJets);
	for(unsigned int i=0; i<j1.size(); i++){
		j1.at(i) = new TLorentzVector();
		j2.at(i) = new TLorentzVector();
		j3.at(i) = new TLorentzVector();

	}
	_tlvjets = j1;
	_mctCMjets = j2;
	_anaCMjets = j3;
}
void eventVariables::setParticles(std::vector<MCParticle*> mcpartvec, std::vector<ReconstructedParticle*> jets ){
	_mcpartvec = mcpartvec;
	_jets = jets;
}
//recursive helper
bool eventVariables::allChildrenAreSimulation(MCParticle* p){
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
void eventVariables::exploreDaughterParticles(MCParticle* p , std::vector<MCParticle*>& FSP){
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
void eventVariables::getMCLeptonMult(std::vector<MCParticle*>& FSPs, int& mclepTrkMult, int& mclepPfoMult){
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

  mclepPfoMult = countparts;
  mclepTrkMult = counttracks;
}
void eventVariables::initMCVars(bool& isTau, bool& isMuon, int& mclepCharge, TLorentzVector*& mcl, TLorentzVector*& mcqq, std::vector<TLorentzVector*>& MCf, std::vector<int>& MCfpdg, int& mclepTrkMult, int& mclepPfoMult){

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
				
                TLorentzVector mcVec(TVector3(daughters.at(j)->getMomentum()),daughters.at(j)->getEnergy());
                *MCf[j] = mcVec;
                MCfpdg[j] = daughters.at(j)->getPDG();

				//is this the lepton?
				if(abs(MCfpdg[j]) == 13  || abs(MCfpdg[j]) == 15){
					mcl = new TLorentzVector(mcVec.Vect(),mcVec.E());

					//also get all of the leptons visible FSP
					std::vector<MCParticle*> mclepFSP{};
					exploreDaughterParticles(daughters.at(i), mclepFSP );
					getMCLeptonMult( mclepFSP, mclepTrkMult, mclepPfoMult );
				}
				if(abs(MCfpdg[j]) < 6){
					qq += *MCf[j];
				}
			}//end daughter loop
			mcqq = new TLorentzVector(qq.Vect(),qq.E());


			if (std::find(daughterpdgs.begin(),daughterpdgs.end(), 13) != daughterpdgs.end() ||
				std::find(daughterpdgs.begin(),daughterpdgs.end(), -13) != daughterpdgs.end() ){
				//identify event containing muon
				isMuon = true;
				isTau = false;
				//get true charge of the muon
				if (std::find(daughterpdgs.begin(),daughterpdgs.end(), 13) != daughterpdgs.end() ){
					mclepCharge = -1;
				}
				else{
					mclepCharge = 1;
				}
			}
			if (std::find(daughterpdgs.begin(),daughterpdgs.end(), 15) != daughterpdgs.end() ||
				std::find(daughterpdgs.begin(),daughterpdgs.end(), -15) != daughterpdgs.end() ){
				//ntau++;
				//identify event containing a tau
				isTau = true;
				isMuon = false;
				//identify the true charge of the lepton
				if (std::find(daughterpdgs.begin(),daughterpdgs.end(), 15) != daughterpdgs.end() ){
					mclepCharge = -1;
				}
				else{
					mclepCharge = 1;
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
void eventVariables::initJetTLV(std::vector<TLorentzVector*>& jetvec){
	
	for(unsigned int i=0; i<_jets.size(); i++){	
		jetvec.at(i)->SetXYZM(_jets.at(i)->getMomentum()[0], _jets.at(i)->getMomentum()[1], _jets.at(i)->getMomentum()[2], _jets.at(i)->getMass() );
		
	}

}
void eventVariables::setJetTags(std::vector<int>& localjettags, std::vector<int> tagset ){
	localjettags = tagset;
}
/***** local mc jet tagging methods  *****/
void eventVariables::MCTagJets(std::vector<int>& jetmctags, bool& isMCTagValid, int& mctlepCharge ){

	std::vector<int> pdgtags(_nJets);
	double maxangle;
	double angle;
	int maxindex = -1;
	for(unsigned int i=0; i<_tlvjets.size(); i++){
		//match each particle
		maxangle = -9999;
		maxindex = -1;
		//get  mcparticle closest to jet
		for(unsigned int j=0; j<_MCf.size(); j++){
			//skip neutrinos
			if( abs(_MCfpdg.at(j)) == 14 || abs(_MCfpdg.at(j)) == 16 ) continue;
			
				angle = _MCf.at(j)->Vect().Dot( _tlvjets.at(i)->Vect() )/ (_MCf.at(j)->Vect().Mag() * _tlvjets.at(i)->Vect().Mag() );

			if(angle > maxangle ){
				maxangle = angle;
				maxindex = j;
			}			


		}
		//take the matched particle and save it
		pdgtags.at(i) = _MCfpdg.at(maxindex);
	}//end match

	isMCTagValid = true;
	//validate the matching (has a particle been doubly matched to a jet?)
		for(unsigned int i=0; i<pdgtags.size(); i++){
			for(unsigned int j=i+1; j<pdgtags.size(); j++){
				if(pdgtags.at(i) == pdgtags.at(j)){
					isMCTagValid = false;
				}
			}
		}
	jetmctags = pdgtags;
	//also set charge
	mctlepCharge = _mclepCharge;

}
/***** end local mc jet tagging *****/
/*** calculate variables based on input set of tags ***/
/*** formatting is function( &{inputtags}, &{output variables} ) ***/
void eventVariables::computeRecoResultsFromTags(std::vector<int>& tagset, TLorentzVector*& Wl, TLorentzVector*& lep, TLorentzVector*& Wqq, TLorentzVector*& Nu){

	TLorentzVector qq;
	for(unsigned int i=0; i< tagset.size(); i++){
		if(abs(tagset.at(i)) < 6){
			qq += *_tlvjets.at(i);
		}
		if(abs(tagset.at(i)) == 13 || abs(tagset.at(i)) == 15){
			lep = new TLorentzVector( _tlvjets.at(i)->Vect(), _tlvjets.at(i)->E() );
		}
	}
	Wqq = new TLorentzVector(qq.Vect(), qq.E());

	TVector3 MissP( -(lep->Px() + Wqq->Px()), -(lep->Py() + Wqq->Py()), -(lep->Pz() + Wqq->Pz()) );

	Nu = new TLorentzVector();
	Nu->SetXYZM(MissP.X(), MissP.Y(), MissP.Z(), 0.0);

	TLorentzVector wl;
	wl = *Nu + *lep;

	Wl = new TLorentzVector(wl.Vect(), wl.E());

}
/*** end tagged calculations ***/
/*** CM boosting methods ***/
	// function( {I I I I}, {O O O} )
void eventVariables::populateCMTLVs(std::vector<int>& tagset, TLorentzVector*& Wl, TLorentzVector*& Wqq, TLorentzVector*& Nu, std::vector<TLorentzVector*>& CMjets,  TLorentzVector*& CMNu ){

	TVector3 Wqqboost = Wqq->BoostVector();
	TVector3 Wlboost = Wl->BoostVector();

	Wqqboost = -Wqqboost;
	Wlboost = -Wlboost;

//	Wqqboost.Print();
//	Wlboost.Print();


	TLorentzVector cmtemp;
	for(unsigned int i=0; i<tagset.size(); i++){
		cmtemp = *(_tlvjets.at(i));
		if( abs(tagset.at(i)) < 6){
			cmtemp.Boost(Wqqboost);
		}
		else{
			cmtemp.Boost(Wlboost);
		}
		CMjets.at(i)->SetPxPyPzE(cmtemp.Px(),cmtemp.Py(),cmtemp.Pz(), cmtemp.E());
	}
	
	//boost nu also
	CMNu = new TLorentzVector();
	CMNu->SetXYZM(Nu->Px(),Nu->Py(),Nu->Pz(),0.0);
	CMNu->Boost(Wlboost);

}
void eventVariables::getCosThetaW(int& lepCharge, TLorentzVector*& Wl, TLorentzVector*& Wqq, double& WmProdAngle){
	//get the production angle of W-
	//our unit z vector along the beam axis
	TVector3 z(0.0,0.0,1.0);
	if(lepCharge < 0 ){
		//W- is the lepton
		TVector3 Wm(Wl->Px(),Wl->Py(),Wl->Pz());
		Wm = Wm * (1/Wm.Mag());
		WmProdAngle = Wm.Dot(z);
		
	}
	else{
		//infer qq charge to be W-
		TVector3 Wm(Wqq->Px(),Wqq->Py(),Wqq->Pz());
		Wm = Wm * (1/Wm.Mag());
		WmProdAngle = Wm.Dot(z);
	}

}
/*** end CM boosting ***/
void eventVariables::printTLV(TLorentzVector* v){
	std::cout<<v->Px()<<" "<<v->Py()<<" "<<v->Pz()<<" "<<v->E()<<" "<<v->M()<<std::endl;
}
void eventVariables::printTLVVec( std::vector<TLorentzVector*> v){
	for( unsigned int i=0; i< v.size(); i++){
		std::cout<<v.at(i)->Px()<<" "<<v.at(i)->Py()<<" "<<v.at(i)->Pz()<<" "<<v.at(i)->E()<<" "<<v.at(i)->M()<<std::endl;
	}
}
void eventVariables::printPDGVec(std::vector<int> v){
	for( unsigned int i=0; i< v.size(); i++){
		std::cout<<v.at(i)<<" ";
	}
	std::cout<<std::endl;
}
void eventVariables::printReconstructedParticle(ReconstructedParticle* p){
	std::cout<<p->getMomentum()[0]<<" "<<p->getMomentum()[1]<<" "<<p->getMomentum()[2]<<" "<<p->getEnergy()<<" "<<p->getMass()<<std::endl;
}
void eventVariables::printReconstructedParticleVec(std::vector<ReconstructedParticle*> v){
	for(unsigned int i=0; i< v.size(); i++){
		printReconstructedParticle(v.at(i));
	}
}

void eventVariables::printEventVariables(){
	std::cout<<"eventVariables: '"<<_variableSetName<<"'"<<std::endl;
	std::cout<<"nfermions = "<<_nfermions<<"  nleptons = "<<_nleptons<<std::endl;
	std::cout<<"MC PDGS: ";	
	printPDGVec(_MCfpdg);
	std::cout<<"MC TLVS: "<<std::endl;	
	printTLVVec(_MCf);
	std::cout<<"MC Lepton TLV: ";
	printTLV(_mcl);
	std::cout<<"MC Lepton Charge: "<<_mclepCharge<<std::endl;
	std::cout<<"MC qq TLV: ";
	printTLV(_mcqq);
	std::cout<<"Reco Parts Jets: "<<std::endl;
	printReconstructedParticleVec(_jets);
	std::cout<<"Reco Jet TLV: "<<std::endl;
	printTLVVec(_tlvjets);
	std::cout<<"Jet MC Tags: ";
	printPDGVec(_jetmctags);
	std::cout<<"MC Tag Valid = "<<_isMCTagValid<<std::endl;
	std::cout<<"MC Tag Quantities----"<<std::endl;
	std::cout<<"mctlep ";
	printTLV(_mctlep);
	std::cout<<"mctWqq ";
	printTLV(_mctWqq);
	std::cout<<"mctNu ";
	printTLV(_mctNu);
	std::cout<<"mctWl ";
	printTLV(_mctWl);
	std::cout<<"W Rest Frame (CM mc tagged)"<<std::endl;
	printTLVVec(_mctCMjets);
	std::cout<<"CM neutrino"<<std::endl;
	printTLV(_mctCMNu);
	std::cout<<"----------------"<<std::endl;
	std::cout<<std::endl;
	//after analysis code is done, print ana quantities
	std::cout<<"Jet ANA Tags: ";
	printPDGVec(_jetanatags);
	std::cout<<"Ana Tag Quantities----"<<std::endl;
	std::cout<<"analep ";
	printTLV(_analep);
	std::cout<<"anaWqq ";
	printTLV(_anaWqq);
	std::cout<<"anaNu ";
	printTLV(_anaNu);
	std::cout<<"anaWl ";
	printTLV(_anaWl);
	std::cout<<"W Rest Frame (CM ana tagged)"<<std::endl;
	printTLVVec(_anaCMjets);
	std::cout<<"CM ana neutrino"<<std::endl;
	printTLV(_anaCMNu);
	std::cout<<"----------------"<<std::endl;
	

}
void eventVariables::initLocalTree(){
	std::string vsn(_variableSetName);

	/*** Tree MC info ***/
	_localTree->Branch((vsn+"isMuon").c_str(), &_isMuon,(vsn+"isMuon/O").c_str());
	_localTree->Branch((vsn+"isTau").c_str(),&_isTau,(vsn+"isTau/O").c_str());
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

	_localTree->Branch("mcl","TLorentzVector",&_mcl,16000,0);
	_localTree->Branch("mcqq","TLorentzVector",&_mcqq,16000,0);
	
	for(unsigned int i=0; i< _nJets; i++){
		std::stringstream name;
		name << _variableSetName << "jet"<<i;
		_localTree->Branch(name.str().c_str(),"TLorentzVector", &_tlvjets.at(i),16000,0);
	}
	/*** End Tree MC info ***/

	/*** MC tagging quantities ***/
	_localTree->Branch((vsn+"mctWl").c_str(),"TLorentzVector",&_mctWl,16000,0);
	_localTree->Branch((vsn+"mctlep").c_str(),"TLorentzVector",&_mctlep,16000,0);
	_localTree->Branch((vsn+"mctWqq").c_str(),"TLorentzVector",&_mctWqq,16000,0);
	_localTree->Branch((vsn+"mctNu").c_str(),"TLorentzVector",&_mctNu,16000,0);
	_localTree->Branch((vsn+"mctlepCharge").c_str(),&_mctlepCharge, (vsn + "mctlepCharge/I").c_str());  
	//CM stuff
	for(unsigned int i=0; i< _nJets; i++){
		std::stringstream name;
		name << _variableSetName << "mctCMjet"<<i;
		_localTree->Branch(name.str().c_str(),"TLorentzVector", &_mctCMjets.at(i),16000,0);
	}
	_localTree->Branch((vsn+"mctWmProdAngle").c_str(),&_mctWmProdAngle,(vsn+"mctWmProdAngle/D").c_str());
	_localTree->Branch((vsn+"mctCMNu").c_str(),"TLorentzVector",&_mctCMNu,16000,0);

	_localTree->Branch((vsn+"isMCTagValid").c_str(), &_isMCTagValid,(vsn+"isMCTagValid/O").c_str());
	/*** end MC tagging info ***/

	/*** Ana tagging quantities ***/
	_localTree->Branch((vsn+"anaWl").c_str(),"TLorentzVector",&_anaWl,16000,0);
	_localTree->Branch((vsn+"analep").c_str(),"TLorentzVector",&_analep,16000,0);
	_localTree->Branch((vsn+"anaWqq").c_str(),"TLorentzVector",&_anaWqq,16000,0);
	_localTree->Branch((vsn+"anaNu").c_str(),"TLorentzVector",&_anaNu,16000,0);
	_localTree->Branch((vsn+"analepCharge").c_str(),&_analepCharge, (vsn + "analepCharge/I").c_str());  
	//CM stuff
	for(unsigned int i=0; i< _nJets; i++){
		std::stringstream name;
		name << _variableSetName << "anaCMjet"<<i;
		_localTree->Branch(name.str().c_str(),"TLorentzVector", &_anaCMjets.at(i),16000,0);
	}
	_localTree->Branch((vsn+"anaWmProdAngle").c_str(),&_anaWmProdAngle,(vsn+"anaWmProdAngle/D").c_str());
	_localTree->Branch((vsn+"anaCMNu").c_str(),"TLorentzVector",&_anaCMNu,16000,0);
	/*** end Ana tagging ***/

}

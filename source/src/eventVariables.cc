
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

	std::vector<TLorentzVector*> j(nJets);
	for(unsigned int i=0; i<j.size(); i++){
		j.at(i) = new TLorentzVector();
	}
	_tlvjets = j;
	_mctCMjets = j;
	_anaCMjets = j;
}
void eventVariables::setParticles(std::vector<MCParticle*> mcpartvec, std::vector<ReconstructedParticle*> jets ){
	_mcpartvec = mcpartvec;
	_jets = jets;
}
void eventVariables::initMCVars(bool& isTau, bool& isMuon, int& mclepCharge, TLorentzVector*& mcl, TLorentzVector*& mcqq, std::vector<TLorentzVector*>& MCf, std::vector<int>& MCfpdg){

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
void eventVariables::MCTagJets(std::vector<int>& jetmctags, bool& isMCTagValid ){

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
	

}
void eventVariables::initLocalTree(){
	char* vsn;
	strcpy(vsn,_variableSetName);
	_localTree->Branch(strcat(vsn,"isMuon"), &_isMuon,strcat(vsn,"isMuon/O"));
	_localTree->Branch(strcat(vsn,"isTau"),&_isTau,strcat(vsn,"isTau/O"));
	_localTree->Branch(strcat(vsn,"mclepCharge"), &_mclepCharge,strcat(vsn,"mclepCharge/O"));

}

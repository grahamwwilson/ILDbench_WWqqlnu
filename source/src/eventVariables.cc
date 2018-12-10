
#include "eventVariables.h"

eventVariables::eventVariables(const char* variableSetName, int nfermions, int nleptons, int nJets){
	_variableSetName = variableSetName;
	_nfermions = nfermions;
	_nleptons = nleptons;
	
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
					std::cout<<"entered mcl condition"<<std::endl;
					mcl = new TLorentzVector(mcVec.Vect(),mcVec.E());
					//*mcl = mcVec;
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

}


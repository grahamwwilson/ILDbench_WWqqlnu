
#include "PandoraPfoVariables.h"

PandoraPfoVariables::PandoraPfoVariables(TTree*& tree){
	_localTree = tree;
}
void PandoraPfoVariables::setParticles(std::vector<ReconstructedParticle*>& pfovec){
	_PandoraPfos = pfovec;
}
void PandoraPfoVariables::populateVariables(int& nTracks, int& nParticles, double& totalPt, double& totalE, double& totalM){
	
	nParticles =(int) _PandoraPfos.size();
	TLorentzVector p;
	TLorentzVector p_Sum;
	int trackCount = 0;

	for(unsigned int i=0; i< _PandoraPfos.size(); i++){
		p.SetXYZM( _PandoraPfos.at(i)->getMomentum()[0], _PandoraPfos.at(i)->getMomentum()[1], _PandoraPfos.at(i)->getMomentum()[2], _PandoraPfos.at(i)->getMass() );
		p_Sum += p;
		if(_PandoraPfos.at(i)->getCharge() != 0){
			trackCount++;
		}
	}

	nTracks = trackCount;
	totalPt = p_Sum.Pt();
	totalE = p_Sum.E();
	totalM = p_Sum.M();
	
}
void PandoraPfoVariables::printPandoraPfoVariables(){
	
	std::cout<<"Pandora Variables----"<<std::endl;
	std::cout<<" nTracks = "<<_nTracks<<" nParticles = "<<_nParticles<<std::endl;
	std::cout<<"totalPt = "<<_totalPt<<" totalE = "<<_totalE<<" totalM = "<<_totalM<<std::endl;	
	
}
void PandoraPfoVariables::initLocalTree(){
	
	_localTree->Branch("PPfonTracks", &_nTracks,"PPfonTracks/I");
	_localTree->Branch("PPfonParticles", &_nParticles,"PPfonParticles/I");
	_localTree->Branch("PPfototalPt", &_totalPt,"PPfototalPt/D");
	_localTree->Branch("PPfototalE", &_totalE,"PPfototalE/D");
	_localTree->Branch("PPfototalM", &_totalM,"PPfototalM/D");


}

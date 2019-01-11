
#include "PandoraPfoVariables.h"

PandoraPfoVariables::PandoraPfoVariables(TTree*& tree, const char* variableSetName){
	_localTree = tree;
	_variableSetName = variableSetName;
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

std::string vsn(_variableSetName);
	
	_localTree->Branch((vsn+"PfonTracks").c_str(), &_nTracks,(vsn+"PfonTracks/I").c_str());
	_localTree->Branch((vsn+"PfonParticles").c_str(), &_nParticles,(vsn+"PfonParticles/I").c_str());
	_localTree->Branch((vsn+"PfototalPt").c_str(), &_totalPt,(vsn+"PfototalPt/D").c_str());
	_localTree->Branch((vsn+"PfototalE").c_str(), &_totalE,(vsn+"PfototalE/D").c_str());
	_localTree->Branch((vsn+"PfototalM").c_str(), &_totalM,(vsn+"PfototalM/D").c_str());


}

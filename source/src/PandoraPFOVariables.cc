
#include "PandoraPFOVariables.h"

PandoraPFOVariables::PandoraPFOVariables(std::vector<ReconstructedParticle*> pfovec){
	
}
void PandoraPFOVariables::setParticles(std::vector<ReconstructedParticle*> pfovec){
	_PandoraPFOs = pfovec;
}
void PandoraPFOVariables::populateVariables(int& nTracks, int& nParticles, double& totalPt, double& totalE, double& totalM){
	
	nParticles = _PandoraPFOs.size();
	TLorentzVector p;
	TLorentzVector p_Sum;
	int trackCount = 0;

	for(unsigned int i=0; i< _PandoraPFOs.size(); i++){
		p.SetXYZM( _PandoraPFOs.at(i)->getMomentum()[0], _PandoraPFOs.at(i)->getMomentum()[1], _PandoraPFOs.at(i)->getMomentum()[2], _PandoraPFOs.at(i)->getMass() );
		p_Sum += p;
		if(_PandoraPFOs.at(i)->getCharge() != 0){
			trackCount++;
		}
	}

	nTracks = trackCount;
	totalPt = p_Sum.Pt();
	totalE = p_Sum.E();
	totalM = p_Sum.M();
	
}
void PandoraPFOVariables::printPandoraPFOVariables(){
	
	std::cout<<"Pandora Variables----"<<std::endl;
	std::cout<<" nTracks = "<<_nTracks<<" nParticles = "<<_nParticles<<std::endl;
	std::cout<<"totalPt = "<<_totalPt<<" totalE = "<<_totalE<<" totalM = "<<_totalM<<std::endl;	
	
}

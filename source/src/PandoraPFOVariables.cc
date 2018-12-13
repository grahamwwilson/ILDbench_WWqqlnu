
#include "PandoraPFOVariables.h"

PandoraPFOVariables::PandoraPFOVariables(std::vector<ReconstructedParticle*> pfovec){
	
}
void PandoraPFOVariables::setParticles(std::vector<ReconstructedParticle*> pfovec){
	_PandoraPFOs = pfovec;
}
void PandoraPFOVariables::populateVariables(int& nTracks, int& nParticles, double& totalPt, double& totalE, double& totalM){
	
}

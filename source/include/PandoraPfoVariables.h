

class PandoraPFOVariables{

	PandoraPFOVariables();
	void setParticles(std::vector<ReconstructedParticle*> pfovec);
	void initLocalTree();

	std::vector<ReconstructedParticle*> _PandoraPFOs{};	
	TTree* _localTree{};

	int _nTracks{};
	int _nParticles{};
	double _totalPt{};
	double _totalE{};
	double _totalM{};

	void populateVariables(int& nTracks, int& nParticles, double& totalPt, double& totalE, double& totalM);	
	
	void printPandoraPFOVariables();


};

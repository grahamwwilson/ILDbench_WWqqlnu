

class PandoraPFOVariables{

	PandoraPFOVariables(std::vector<ReconstructedParticle*> pfovec);
	void initLocalTree();

	std::vector<ReconstructedParticle*> _PandoraPFOs{};	
	TTree* _localTree{};

	int nTracks{};
	int nParticles{};
	double totalPt{};
	double totalE{};
	double totalM{};

	void printPandoraPFOVariables();


};

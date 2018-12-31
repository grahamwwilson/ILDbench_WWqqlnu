

class overlayVariables{

	public:
		overlayVariables(const char* variableSetName, TTree*& tree, unsigned int nJets );
		void setParticles();
		void initLocalTree();

		TTree* _localTree{};	

		const char* _variableSetName{};
		unsigned int _nJets{};
		//std::string LCRelationName{};

		//trimmed mcparticle list
		std::vector<MCParticle*> _MCOverlay{};
		std::vector<int> _MCOverlayIDs{};

		std::vector< std::vector<ReconstructedParticle*> > _overlayParticles{};//populate from a set of reco jets
		std::vector< std::vector<TLorentzVector*> > _tlvoverlayParticles{};

		void setMCOverlay(std::vector<MCParticle*>& MCOverlay, std::vector<int> MCOverlayIDs, std::vector<MCParticle*>& mcpartvec );

		void setOverlayParticles(std::vector<ReconstructedParticle*>& overlayParticleSet, std::vector<MCParticle*>& mcpartvec, LCRelation*& pfo2mc, std::vector<ReconstructedParticle*>& jetParticles );
		
		void setOverlayparticlesLoop(std::vector<ReconstructedParticle*>& overlayParticleSet, std::vector<MCParticle*>& mcpartvec, LCRelation*& pfo2mc, std::vector<ReconstructedParticle*>& jets );

		


};

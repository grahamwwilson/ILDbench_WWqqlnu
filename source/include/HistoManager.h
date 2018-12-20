#ifndef _HISTMAN_
#define _HISTMAN_
#include "TH1D.h"
#include <vector>
/* WIP */

class HistoManager{

	public:
	HistoManager(int nCuts, double weight);

	double _weight{};
	int _nCuts{};
	//two types of hists
	//Type1: hist depending on cutflow

	std::vector<TH1D*> WmassMuon{}, WmassTau{}, qqmassMuon{}, qqmassTau{};
	std::vector<TH1D*> WEMuon{}, WETau{}, EtotalMuon{}, EtotalTau{};
	std::vector<TH1D*> Wm_cosTheta{};

	std::vector<TH1D*> LjetMassMuon{}, LjetMassTau{};

	//tgc hists
	std::vector<TH1D*> costhetawMuon{} , costhetawTau{};
	std::vector<TH1D*> thetaLMuon{}, thetaLTau{};
	std::vector<TH1D*> phiLMuon{}, phiLTau{};
	std::vector<TH1D*> thetaHMuon{}, thetaHTau{};
	std::vector<TH1D*> phiHMuon{}, phiHTau{};

    //jet information histograms
    std::vector<TH1D*>  leptonMCNPartsMuon{}, leptonMCNTracksMuon{}, leptonMCNPartsTau{}, leptonMCNTracksTau{};
	std::vector<TH1D*>  jetNpartsMuon{}, minjetNpartsMuon{}, jetNpartsTau{}, minjetNpartsTau{};
    std::vector<TH1D*>  jetNtracksMuon{}, minjetNtracksMuon{},  jetNtracksTau{}, minjetNtracksTau{};

    //lepton jet info
	std::vector<TH1D*> ljetleadingd0Muon{}, ljetleadingd0Tau{}, ljetleadingptMuon{}, ljetleadingptTau{};
    std::vector<TH1D*> ljetd0relerrMuon{}, ljetd0relerrTau{}; 
    std::vector<TH1D*> qjetleadingd0Muon{}, qjetleadingd0Tau{}, qjetleadingptMuon{}, qjetleadingptTau{};
    std::vector<TH1D*> qjetd0relerrMuon{}, qjetd0relerrTau{};
	
	std::vector<TH1D*> psiljetmclMuon{}, psiljetmclTau{};

	std::vector<TH1D*> htotalTracks{};


	//Type2: hist not depending on cutflow	
	//these are populated directly from pandora pfos
	TH1D* htotaltracks{};
	TH1D* htotalPt{};
	TH1D* htotalE{};
	TH1D* htotalM{};
	TH1D* hym{};
	TH1D* hyp{};

	void initHists1();
	void initHists2();

	void FillHists1(int histNumber );
	void FillHists2(double weight);

	void FillMuonHistos(int histNumber);
	void FillTauHistos(int histNumber);
	void fillEventSelectionHistos(double weight);	

};
#endif

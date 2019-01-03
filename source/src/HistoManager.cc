#include "HistoManager.h"
HistoManager::HistoManager(int nCuts, double weight){
	_nCuts = nCuts;
	_weight = weight;
}
void HistoManager::initHists1(){

	double pi = 3.1416;
	for(int i=0; i<= _nCuts; i++){
		 char cuts[100];
         sprintf(cuts, "_%d", i);
         std::string cutnum(cuts);

		/* init histograms */
		//some general plots
		WmassMuon.push_back( new TH1D(("Wmassmuon"+cutnum).c_str(),"W^{#pm} Mass from l #nu, with true #mu",100, 50.0, 120.0 ));
		WmassTau.push_back( new TH1D(("Wmasstau"+cutnum).c_str(),"W^{#pm} Mass from l #nu, with true #tau",100, 50.0, 120.0 ));
        qqmassMuon.push_back( new TH1D(("qqmassmuon"+cutnum).c_str(),"qq Mass, with true #mu",100,50.0,120.0));
		qqmassTau.push_back( new TH1D(("qqmasstau"+cutnum).c_str(),"qq Mass, with true #tau",100,50.0,120.0));
		WEMuon.push_back( new TH1D(("WEmuon"+cutnum).c_str(),"W^{#pm} Energy, with true #mu",100, 25.0, 300.0));
		WETau.push_back( new TH1D(("WEtau"+cutnum).c_str(),"W^{#pm} Energy, with true #tau ",100, 25.0, 300.0 ));
		EtotalMuon.push_back( new TH1D(("EtotalMuon"+cutnum).c_str(),"WW Total Energy, with true #mu",100,100,550)); 
		EtotalTau.push_back( new TH1D(("EtotalTau"+cutnum).c_str(),"WW Total Energy, with true #tau",100,100,550));
		
		//TGC stuff
		LjetMassMuon.push_back(new TH1D(("Ljetmassmuon"+cutnum).c_str(),"Mass of Lepton Jet with true #mu",100, 0.0 ,20.0 ));
		LjetMassTau.push_back(new TH1D(("Ljetmasstau"+cutnum).c_str(),"Mass of Lepton Jet with true #tau",100, 0.0, 20.0 ));

		costhetawMuon.push_back( new TH1D(("costhetawMuon"+cutnum).c_str(), "production angle of W^- in Muon event",100,-1.0,1.0));
		thetaLMuon.push_back( new TH1D(("thetaLMuon"+cutnum).c_str(), "polar angle of CM lepton in Muon event",100, 0.0,  pi));
		phiLMuon.push_back( new TH1D(("phiLMuon"+cutnum).c_str(), "azimuthal angle of CM Lepton in Muon event", 100,-pi,pi));
		thetaHMuon.push_back( new TH1D(("thetaHMuon"+cutnum).c_str(), "polar angle of CM quark in Muon event",100,0.0,pi));
		phiHMuon.push_back( new TH1D(("phiHMuon"+cutnum).c_str(),"azimuthal angle of CM quark in Muon event", 100,-pi,pi));

		costhetawTau.push_back( new TH1D(("costhetawTau"+cutnum).c_str(), "production angle of W^- in Tau event",100,-1.0,1.0));
		thetaLTau.push_back( new TH1D(("thetaLTau"+cutnum).c_str(), "polar angle of CM lepton in Tau event",100, 0.0, pi));
		phiLTau.push_back( new TH1D(("phiLTau"+cutnum).c_str(), "azimuthal angle of CM Lepton in Tau event", 100,-pi,pi));
		thetaHTau.push_back( new TH1D(("thetaHTau"+cutnum).c_str(), "polar angle of CM quark in Tau event",100,0.0,pi));
		phiHTau.push_back( new TH1D(("phiHTau"+cutnum).c_str(),"azimuthal angle of CM quark in Tau event", 100,-pi,pi));


        
	 //jet information histograms
   		leptonMCNPartsMuon.push_back( new TH1D(("leptonMCNPartsMuon"+cutnum).c_str(), "True Visible Particles Radiated/Decayed from Lepton in Muon Event", 20,0.5,20.5));
		leptonMCNTracksMuon.push_back( new TH1D(("leptonMCNTracksMuon"+cutnum).c_str(), "True Visible Tracks Decayed from Lepton in Muon Event",20,0.5,20.5));
		jetNpartsMuon.push_back( new TH1D(("jetNpartsMuon"+cutnum).c_str(), "Visible Particles per Jet in Muon Event",50,0.5,50.5));
        jetNtracksMuon.push_back( new TH1D(("jetNtracksMuon"+cutnum).c_str(), "Visible Tracks per Jet in Muon Event", 50,0.5,50.5));		
minjetNpartsMuon.push_back( new TH1D(("minjetNpartsMuon"+cutnum).c_str(), "Visible Particle of Jet with least Particles in Muon Event",25,0.5,25.5));
		minjetNtracksMuon.push_back( new TH1D(("minjetNtracksMuon"+cutnum).c_str(), "Visible Tracks of Jet with least Particlesin Muon Event",25,0.5,25.5));

		leptonMCNPartsTau.push_back( new TH1D(("leptonMCNPartsTau"+cutnum).c_str(), "True Visible Particles Radiated/Decayed from Lepton in Tau Event", 20,0.5,20.5));
		leptonMCNTracksTau.push_back( new TH1D(("leptonMCNTracksTau"+cutnum).c_str(), "True Visible Tracks Decayed from Lepton in Tau Event",20,0.5,20.5));
		jetNpartsTau.push_back( new TH1D(("jetNpartsTau"+cutnum).c_str(), "Visible Particles per Jet in Tau Event",20,0.5,20.5));
        jetNtracksTau.push_back( new TH1D(("jetNtracksTau"+cutnum).c_str(), "Visible Tracks per Jet in Tau Event", 20,0.5,50.5));
		minjetNpartsTau.push_back( new TH1D(("minjetNpartsTau"+cutnum).c_str(), "Visible Particle of Jet with least Particles in Tau Event",25,0.5,25.5));
		minjetNtracksTau.push_back( new TH1D(("minjetNtracksTau"+cutnum).c_str(), "Visible Tracks of Jet with least Particlesin Tau Event",25,0.5,25.5));

		//some jet leading track parameters
		ljetleadingd0Muon.push_back( new TH1D(("ljetleadingd0Muon"+cutnum).c_str(), "d0 of the leading track of lepton jet in muon event",50,-0.1,0.1));
		ljetleadingptMuon.push_back( new TH1D(("ljetleadingptMuon"+cutnum).c_str(), "p of the leading track of lepton jet in muon event", 100,0.0, 200.0));
		ljetd0relerrMuon.push_back( new TH1D(("ljetd0relerrMuon"+cutnum).c_str(),"d0/ #delta d0  of leading track of lepton jet in muon event",20,0.0,100));
		qjetleadingd0Muon.push_back( new TH1D(("qjetleadingd0Muon"+cutnum).c_str(), "d0 of the leading track of q jet in muon event",50,-0.1,0.1));
		qjetleadingptMuon.push_back( new TH1D(("qjetleadingptMuon"+cutnum).c_str(), "p of the leading track of q jet in muon event", 100,0.0, 200.0));
		qjetd0relerrMuon.push_back( new TH1D(("qjetd0relerrMuon"+cutnum).c_str(),"d0/ #delta d0  of leading track of q jet in muon event",100,0.0,100));
		ljetleadingd0Tau.push_back( new TH1D(("ljetleadingd0Tau"+cutnum).c_str(), "d0 of the leading track of lepton jet in Tau event",50,-.1,.1));
		ljetleadingptTau.push_back( new TH1D(("ljetleadingptTau"+cutnum).c_str(), "p of the leading track of lepton jet in Tau event", 100,0.0, 200.0));
		ljetd0relerrTau.push_back( new TH1D(("ljetd0relerrTau"+cutnum).c_str(),"d0/ #delta d0  of leading track of lepton jet in Tau event",100,0.0,100));
		qjetleadingd0Tau.push_back( new TH1D(("qjetleadingd0Tau"+cutnum).c_str(), "d0 of the leading track of q jet in Tau event",50,-.1,.1));
		qjetleadingptTau.push_back( new TH1D(("qjetleadingptTau"+cutnum).c_str(), "p of the leading track of q jet in Tau event", 100,0.0, 200.0));
		qjetd0relerrTau.push_back( new TH1D(("qjetd0relerrTau"+cutnum).c_str(),"d0/ #delta d0  of leading track of q jet in Tau event",100,0.0,100));
	
		psiljetmclMuon.push_back( new TH1D(("psiljetmclMuon"+cutnum).c_str(),"angle between the lepton jet and the true lepton muon",100,-1.0,1.0));
		psiljetmclTau.push_back( new TH1D(("psiljetmclTau"+cutnum).c_str(),"angle between the lepton jet and the true lepton muon",100,-1.0,1.0));	
	
		htotalTracks.push_back( new TH1D(("htotalTracks"+cutnum).c_str(),"total charged pfos",141,-0.5,140));
		/* end init histograms */
		}

	

}
void HistoManager::initHists2(){

	htotaltracks = new TH1D("htotaltracks","total tracks;Number of Charged PFOs;Events Per Bin",141,-0.5,140);
	htotalPt = new TH1D("htotalPt","total pt;P_{t} [GeV]; Events Per Bin",100,0,100);
	htotalE = new TH1D("htotalE","Total Visible Energy; Energy [GeV]; Events Per Bin",100,0,650);	
	htotalM = new TH1D("htotalM","Total Mass; Mass [GeV]; Events Per Bin",100,0,650);
	hym = new TH1D("htotalym","y-;log y-;Events Per Bin",100,-15.0,0);
	hyp = new TH1D("hyp","y+;log y+; Events Per Bin",100,-15,0);

}
void HistoManager::FillHists1(int histNumber ){
/*	
	if(isTau){
		FillTauHistos(histNumber);
	}
	if(isMuon){
		FillMuonHistos(histNumber);
	}

	htotalTracks[histNumber]->Fill( _trackvec.size(), weight);
*/
}
void HistoManager::FillMuonHistos(int histNumber){
/*
//	WmassMuon[histNumber]->Fill( Wqq->M() );
	WmassMuon[histNumber]->Fill(Wl->M() );
	qqmassMuon[histNumber]->Fill(Wqq->M() );
	WEMuon[histNumber]->Fill(Wqq->E() );
	WEMuon[histNumber]->Fill(Wl->E() );
	EtotalMuon[histNumber]->Fill(Wqq->E() + Wl->E() );

	LjetMassMuon[histNumber]->Fill( _jets.at( ljet_index )->getMass() );

	//TGC stuff
	costhetawMuon[histNumber]->Fill(getCosThetaW());
	thetaLMuon[histNumber]->Fill( CMJets.at(ljet_index)->Theta());
	phiLMuon[histNumber]->Fill( CMJets.at(ljet_index)->Phi());
	for(unsigned int i=0; i<CMJets.size(); i++){
		if( i != ljet_index ){
			thetaHMuon[histNumber]->Fill( CMJets.at(i)->Theta()); 
			phiHMuon[histNumber]->Fill( CMJets.at(i)->Phi());
		}
	} 

    //jet details
    leptonMCNPartsMuon[histNumber]->Fill(lnmcparts);
	leptonMCNTracksMuon[histNumber]->Fill(lnmctracks); 
    for(unsigned int i=0; i<jetNparts.size(); i++){
		jetNpartsMuon[histNumber]->Fill(jetNparts.at(i));
		jetNtracksMuon[histNumber]->Fill(jetNtracks.at(i));
	}
	minjetNpartsMuon[histNumber]->Fill(lnparts);
	minjetNtracksMuon[histNumber]->Fill(lntracks);

	//more jet details
	ljetleadingd0Muon[histNumber]->Fill(leadingd0ljet);
	ljetleadingptMuon[histNumber]->Fill(leadingptljet);
	ljetd0relerrMuon[histNumber]->Fill(leadingd0relerrljet);
	qjetleadingd0Muon[histNumber]->Fill(leadingd0qjet);
	qjetleadingptMuon[histNumber]->Fill(leadingptqjet);
	qjetd0relerrMuon[histNumber]->Fill(leadingd0relerrqjet);


	 psiljetmclMuon[histNumber]->Fill(psi_mcl_ljet);
*/
}
void HistoManager::FillTauHistos(int histNumber){
/*
//	WmassTau[histNumber]->Fill( Wqq->M() );
	WmassTau[histNumber]->Fill( Wl->M() );
	qqmassTau[histNumber]->Fill( Wqq->M() );
	WETau[histNumber]->Fill( Wqq->E() );
	WETau[histNumber]->Fill(Wl->E() );
	EtotalTau[histNumber]->Fill(Wqq->E() + Wl->E());

	LjetMassTau[histNumber]->Fill( _jets.at(ljet_index)->getMass() );

	//TGC stuff
	costhetawTau[histNumber]->Fill(getCosThetaW());
	thetaLTau[histNumber]->Fill( CMJets.at(ljet_index)->Theta());
	phiLTau[histNumber]->Fill( CMJets.at(ljet_index)->Phi());
	for(unsigned int i=0; i<CMJets.size(); i++){
		if( i != ljet_index ){
			thetaHTau[histNumber]->Fill( CMJets.at(i)->Theta()); 
			phiHTau[histNumber]->Fill( CMJets.at(i)->Phi());
		}
	} 
	
	//jet details
    leptonMCNPartsTau[histNumber]->Fill(lnmcparts);
	leptonMCNTracksTau[histNumber]->Fill(lnmctracks);
	for(unsigned int i=0; i<jetNparts.size(); i++){ 
		jetNpartsTau[histNumber]->Fill(jetNparts.at(i));
	    jetNtracksTau[histNumber]->Fill(jetNtracks.at(i));
	}
	minjetNpartsTau[histNumber]->Fill(lnparts);
	minjetNtracksTau[histNumber]->Fill(lntracks);

	ljetleadingd0Tau[histNumber]->Fill(leadingd0ljet);
	ljetleadingptTau[histNumber]->Fill(leadingptljet);
	ljetd0relerrTau[histNumber]->Fill(leadingd0relerrljet);
	qjetleadingd0Tau[histNumber]->Fill(leadingd0qjet);
	qjetleadingptTau[histNumber]->Fill(leadingptqjet);
	qjetd0relerrTau[histNumber]->Fill(leadingd0relerrqjet);

	 psiljetmclTau[histNumber]->Fill(psi_mcl_ljet);
*/
}
void HistoManager::fillEventSelectionHistos(double weight){
/*
	htotaltracks->Fill( totaltracks, w);
	htotalPt->Fill( total_Pt ,w);
	htotalE->Fill( total_E ,w);
	htotalM->Fill( total_M ,w);
	hym->Fill( _yMinus ,w);
	hyp->Fill( _yPlus ,w);
*/

}


void tauplot(){

		TFile* fLR = TFile::Open("../../4f_WW_semi_LR.root");
//	TTreeReader tLRread("tree", fLR);

	//TTreeReader pureLRread("puretree", fLR);
	TTreeReader tauLRread("tautree", fLR);

	TTreeReaderValue<bool> isMuon(tauLRread, "evtauisMuon");	
	TTreeReaderValue<bool> isTau(tauLRread, "evtauisTau");
	TTreeReaderValue<int> tautype(tauLRread, "evtautauType");
	//TTreeReaderValue<int> nTaus(tautree, "taunTaus");

	TH1D* htype = new TH1D("htype","type",6, -0.5,5.5);


	while( tauLRread.Next() ){
		htype->Fill(*tautype);



			bool acceptanceCut = true;
		if( fabs(evtauMCf0->CosTheta()) > 0.995 ) acceptanceCut = false;
		if( fabs(evtauMCf1->CosTheta()) > 0.995 ) acceptanceCut = false;
		if( fabs(evtauMCf2->CosTheta()) > 0.995 ) acceptanceCut = false;

















	}

	TCanvas *c1 = new TCanvas("c1","multipads",800,600);
	htype->Draw();



	//do a basic requirement for found taus
}


void tauplot(){

		TFile* fLR = TFile::Open("../../4f_WW_semi_LR.root");
//	TTreeReader tLRread("tree", fLR);

	TTreeReader pureLRread("puretree", fLR);
	TTreeReader tauLRread("tautree", fLR);

	TTreeReaderValue<bool> isMuon(pureLRread, "pureisMuon");	
	TTreeReaderValue<bool> isTau(pureLRread, "pureisTau");
	TTreeReaderValue<int> tautype(pureLRread, "puretauType");
	//TTreeReaderValue<int> nTaus(tautree, "taunTaus");

	TH1D* htype = new TH1D("htype","type",6, -0.5,5.5);


	while( pureLRread.Next() ){
		htype->Fill(*tautype);
	}

	TCanvas *c1 = new TCanvas("c1","multipads",800,600);
	htype->Draw();

}

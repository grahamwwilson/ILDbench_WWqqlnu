
void tauplot(){

		TFile* fLR = TFile::Open("../../4f_WW_semi_LR.root");
//	TTreeReader tLRread("tree", fLR);

	TTreeReader pureLRread("puretree", fLR);
	TTreeReader tauLRread("tautree", fLR);

	TTreeReaderValue<bool> isMuon(pureLRread, "pureisMuon");	
	TTreeReaderValue<bool> isTau(pureLRread, "pureisTau");
	TTreeReaderValue<int> tautype(pureLRread, "puretauType");
	TTreeReaderValue<int> nTaus(tautree, "taunTaus");

	

}

#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TFile.h"
#include "TH1D.h"

void justin_plot(){
	
	//readin file
	//file path ../../file.root
	//TFile *qq = TFile::Open("2f_Z.root");
//	TCanvas *c1 = new TCanvas("c1","multipads",800,600);
	TFile* fLR = TFile::Open("../../4f_WW_semi_LR.root");

	//read in all the trees from LR
	//TTree* tLR;
	//flR->GetObject("tree", tLR);

	TTreeReader tLRread("tree", fLR);
	TTreeReader eektLRread("eekttree", fLR);
	
	TTreeReaderValue<double> purePfototalELR(tLRread, "purePfototalE");	
	TTreeReaderValue<int> eektmctlepTrkMultLR(eektLRread,"eektmctlepTrkMult");	
	TTreeReaderValue<int> eektmctUpTrkMultLR(eektLRread,"eektmctUpTrkMult");
	TTreeReaderValue<int> eektmctDwnTrkMultLR(eektLRread,"eektmctDwnTrkMult");

	TH1D *h1 = new TH1D("h1","purePfototalELR;TotalEnergy;Entries",100,0.,550.);
	TH1D *htrk = new TH1D("htrk","Track Multiplicity MCTagged Jets;N Tracks",40,-.5 ,40.5);
	TH1D *htrku = new TH1D("htrku","",40,-.5,40.5);
	TH1D *htrkd = new TH1D("htrkd","",40,-.5,40.5);
	while( tLRread.Next()){
		h1->Fill(*purePfototalELR);	
	}

	int numevents=0; // number of events that fall within the criteria  0<ntracks<=3
	while( eektLRread.Next()){
		htrk->Fill(*eektmctlepTrkMultLR);
		htrku->Fill(*eektmctUpTrkMultLR);
		htrkd->Fill(*eektmctDwnTrkMultLR);
		if( *eektmctlepTrkMultLR <= 3 && *eektmctlepTrkMultLR > 0) numevents++;
	}
	std::cout<<"number of events within track criteria = "<<numevents;
	std::cout<<" number outside cut = "<< 11800 - numevents <<std::endl;

	TCanvas *c1 = new TCanvas("c1","multipads",800,600);
	h1->Draw();
	TCanvas *c2 = new TCanvas("c2","multipads",800,600);
	htrk->Draw();
	htrku->SetLineColor(kRed);
	htrkd->SetLineColor(kBlue);
	htrku->Draw("same");
	htrkd->Draw("same");

}

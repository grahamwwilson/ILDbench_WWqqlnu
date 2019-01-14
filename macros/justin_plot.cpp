#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TFile.h"
#include "TH1D.h"
#include "TLorentzVector.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TTreeReaderArray.h"

void justin_plot(string htype="hx",float ymax=800.0, float xlmin=0.35, float ylmin=0.58){
	
	//readin file
	//file path ../../file.root
	//TFile *qq = TFile::Open("2f_Z.root");
//	TCanvas *c1 = new TCanvas("c1","multipads",800,600);
	TFile* fLR = TFile::Open("../../4f_WW_semi_LR.root");


	double mctagcut = 2.5;

	//read in all the trees from LR
	//TTree* tLR;
	//flR->GetObject("tree", tLR);

	TTreeReader tLRread("tree", fLR);
	TTreeReader eektLRread("eekttree", fLR);
	TTreeReader pureLRread("puretree", fLR);
	
	TTreeReaderValue<double> purePfototalELR(tLRread, "purePfototalE");	
	TTreeReaderValue<double> pandoraPfoTotalELR(tLRread, "pandoraPfototalE");


	TTreeReaderValue<int> eektmctlepTrkMultLR(eektLRread,"eektmctlepTrkMult");	
	TTreeReaderValue<int> eektmctUpTrkMultLR(eektLRread,"eektmctUpTrkMult");
	TTreeReaderValue<int> eektmctDwnTrkMultLR(eektLRread,"eektmctDwnTrkMult");
    TTreeReaderValue<double> eekttagCosPsiSumLR(eektLRread,"eekttagCosPsiSum");
	TTreeReaderValue<double> eektupliketag_ovr_EfracLR(eektLRread,"eektupliketag_ovr_Efrac");
    TTreeReaderValue<double> eektdwnliketag_ovr_EfracLR(eektLRread,"eektdwnliketag_ovr_Efrac");
    TTreeReaderValue<double> eektleptontag_ovr_EfracLR(eektLRread,"eektleptontag_ovr_Efrac");
	TTreeReaderValue<int> eektleptontag_ovr_ntrksLR(eektLRread,"eektleptontag_ovr_ntrks");
	TTreeReaderValue<int> eektupliketag_ovr_ntrksLR(eektLRread,"eektupliketag_ovr_ntrks");
	TTreeReaderValue<int> eektdwnliketag_ovr_ntrksLR(eektLRread,"eektdwnliketag_ovr_ntrks");
	//TTreeReaderValue<TLorentzVector> eektmctWqqLR(eektLRread,"eektmctWqq");

	//TTreeReaderValue<double> puremctWqqLR(pureLRread,"puremctWqq.M");
//	TTreeReaderValue<double> puremcqqLR(pureLRread,"mcqq.fM()");
	//TTreeReaderValue<double> puretagCosPsiSumLR(pureLRread,"puretagCosPsiSum");

	//pfo energy
	TH1D *h1 = new TH1D("htotalEPure","purePfototalELR;TotalEnergy;Entries",100,0.,600.);
	TH1D *htotalE = new TH1D("htotalEPandora","Total Energy of PandoraPFOs;Energy GeV;Entries Per Bin",100,0.,600.);	

	//tk mult for flavors eekt
	TH1D *htrk = new TH1D("htrk","Track Multiplicity of MCTagged Jets;N Tracks",25,-.5 ,25.5);
	TH1D *htrku = new TH1D("htrku","",25,-.5,25.5);
	TH1D *htrkd = new TH1D("htrkd","",25,-.5,25.5);

	//overlay mct jet flavors eekt
	TH1D* hlEfrac = new TH1D("hlEfrac","Overlay Jet Energy Fraction; Jet Energy %",50,0.,1.0);
	TH1D* huEfrac = new TH1D("huEfrac","",50,0.,1.0);
	TH1D* hdEfrac = new TH1D("hdEfrac","Overlay Jet Energy Fraction; Jet Energy %",50,0.,1.0);
	TH1D* hlntrks = new TH1D("hlntrks","Reconstructed Overlay Tracks; N Tracks",20,-.5,20.5);
	TH1D* huntrks = new TH1D("huntrks","Reconstructed Overlay Tracks; N Tracks",20,-.5,20.5);
	TH1D* hdntrks = new TH1D("hdntrks","Reconstructed Overlay Tracks; N Tracks",20,-.5,20.5);

	//wqq overlay/no overlay 
	TH1D* hpureWqq = new TH1D("hpureWqq","",100,0.,150.);
	TH1D* hmcWqq =  new TH1D("hmcWqq","MC Tagged W #rightarrow qq Mass;Mass GeV",100,0.,150.);
	TH1D* heektWqq = new TH1D("heektWqq","",100,0.,150.);


	///loop over tree
	while( tLRread.Next()){
		h1->Fill(*purePfototalELR);
		htotalE->Fill(*pandoraPfoTotalELR);	
	}

	////loop over eekt tree
	int numevents=0; // number of events that fall within the criteria  0<ntracks<=3
	int nvts=0;
	int nevtoverlaytrks=0;
	TLorentzVector t;
	while( eektLRread.Next()){
		
		if( *eekttagCosPsiSumLR < mctagcut ) continue;
		nvts++;
		htrk->Fill(*eektmctlepTrkMultLR);
		htrku->Fill(*eektmctUpTrkMultLR);
		htrkd->Fill(*eektmctDwnTrkMultLR);
		
		hlEfrac->Fill(*eektleptontag_ovr_EfracLR);
		huEfrac->Fill(*eektupliketag_ovr_EfracLR);
		hdEfrac->Fill(*eektdwnliketag_ovr_EfracLR);

		hlntrks->Fill(*eektleptontag_ovr_ntrksLR);
		huntrks->Fill(*eektupliketag_ovr_ntrksLR);
		hdntrks->Fill(*eektdwnliketag_ovr_ntrksLR);

	//	t=*eektmctWqqLR;
		//heektWqq->Fill((*eektmctWqqLR));
		//std::cout<<(*eektmctWqqLR).M()<<" ";

		if( *eektmctlepTrkMultLR <= 3 && *eektmctlepTrkMultLR > 0) numevents++;
		if( *eektleptontag_ovr_ntrksLR > 0 ) nevtoverlaytrks++;
	}
	std::cout<<"number of events within track criteria = "<<numevents;
	std::cout<<" number outside cut = "<< nvts - numevents <<" "<< (double(nvts-numevents)/double(nvts) )*100.<<"%" <<std::endl;
	std::cout<<"the number of events with lepton is contaminated with at least 1 track "<< nevtoverlaytrks <<" "<< (double(nevtoverlaytrks)/double(nvts))*100.<<"%"<<std::endl;


	//loop over pure tree
	while( pureLRread.Next()){
		
		//std::cout<<*puremcqqLR<<" ";
		//hmcWqq->Fill((*puremcqqLR));

	//	if( *puretagCosPsiSumLR < mctagcut ) continue;
		
		//	hpureWqq->Fill((*puremctWqqLR));

	}


const float dx=0.36;
	const float dy=0.26;



//plotting for pandora and pure pfo energy
	TCanvas *c1 = new TCanvas("c1","multipads",800,600);
	h1->SetLineColor(kBlue);
	htotalE->SetLineColor(kRed);
	//htotalE->SetStats(false);
	htotalE->Draw();
	h1->Draw("sames");
	TLegend* leg0 = new TLegend(xlmin,ylmin,xlmin+dx,ylmin+dy);
leg0->SetHeader("#sqrt{s} = 500 GeV: e^{-}_{L} e^{+}_{R} #rightarrow W^{-} W^{+} #rightarrow q q l #nu","C");
leg0->AddEntry(htotalE,"PandoraPFOs","l");
leg0->AddEntry(h1,"Overlay Removed","l");

leg0->SetBorderSize(1);                          // Include border
leg0->Draw();


// trk multiplicity by jet flavor for eekt
TCanvas *c2 = new TCanvas("c2","multipads",800,600);
	htrk->SetLineColor(kGreen);
	htrk->SetStats(false);
	htrk->Draw();
	htrku->SetLineColor(kRed);
	htrkd->SetLineColor(kBlue);
	htrku->Draw("same");
	htrkd->Draw("same");	


	TLegend* leg1 = new TLegend(xlmin,ylmin,xlmin+dx,ylmin+dy);
leg1->SetHeader("#sqrt{s} = 500 GeV: e^{-}_{L} e^{+}_{R} #rightarrow W^{-} W^{+} #rightarrow q q l #nu","C");
leg1->AddEntry(htrk,"lepton","l");
leg1->AddEntry(htrku,"u-like q","l");
leg1->AddEntry(htrkd,"d-like q","l");


leg1->SetBorderSize(1);                          // Include border
leg1->Draw();


//energy fraction per jet flavor, eektS
TCanvas *c3 = new TCanvas("c3","multipads",800,600);
		
		hlEfrac->SetLineColor(kGreen);
		huEfrac->SetLineColor(kRed);
		hdEfrac->SetLineColor(kBlue);
		//hlEfrac->SetStats(false);
		hdEfrac->Draw();		
		hlEfrac->Draw("sames");
		huEfrac->Draw("sames");
		

		
	TLegend* leg2 = new TLegend(xlmin,ylmin,xlmin+dx,ylmin+dy);
leg2->SetHeader("#sqrt{s} = 500 GeV: e^{-}_{L} e^{+}_{R} #rightarrow W^{-} W^{+} #rightarrow q q l #nu","C");
leg2->AddEntry(hlEfrac,"lepton","l");
leg2->AddEntry(huEfrac,"u-like q","l");
leg2->AddEntry(hdEfrac,"d-like q","l");


leg2->SetBorderSize(1);                          // Include border
leg2->Draw();


//number of overlay tracks per jet flavor eekt
TCanvas *c4 = new TCanvas("c4","multipads",800,600);
		
		hlntrks->SetLineColor(kGreen);
		huntrks->SetLineColor(kRed);
		hdntrks->SetLineColor(kBlue);
		//hlntrks->SetStats(false);
		
		huntrks->Draw();
		hdntrks->Draw("sames");		
		hlntrks->Draw("sames");
		
		

		
	TLegend* leg3 = new TLegend(xlmin,ylmin,xlmin+dx,ylmin+dy);
leg3->SetHeader("#sqrt{s} = 500 GeV: e^{-}_{L} e^{+}_{R} #rightarrow W^{-} W^{+} #rightarrow q q l #nu","C");
leg3->AddEntry(hlEfrac,"lepton","l");
leg3->AddEntry(huEfrac,"u-like q","l");
leg3->AddEntry(hdEfrac,"d-like q","l");


leg3->SetBorderSize(1);                          // Include border
leg3->Draw();

}

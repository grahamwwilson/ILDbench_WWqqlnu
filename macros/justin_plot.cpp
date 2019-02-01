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
	TTreeReader kt15LRread("kt15tree", fLR);
	TTreeReader kt08LRread("kt08tree", fLR);
	
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


	TTreeReaderValue<double> kt15upliketag_ovr_EfracLR(kt15LRread,"kt15upliketag_ovr_Efrac");
    TTreeReaderValue<double> kt15dwnliketag_ovr_EfracLR(kt15LRread,"kt15dwnliketag_ovr_Efrac");
    TTreeReaderValue<double> kt15leptontag_ovr_EfracLR(kt15LRread,"kt15leptontag_ovr_Efrac");
	TTreeReaderValue<int> kt15leptontag_ovr_ntrksLR(kt15LRread,"kt15leptontag_ovr_ntrks");
	TTreeReaderValue<int> kt15upliketag_ovr_ntrksLR(kt15LRread,"kt15upliketag_ovr_ntrks");
	TTreeReaderValue<int> kt15dwnliketag_ovr_ntrksLR(kt15LRread,"kt15dwnliketag_ovr_ntrks");


	TTreeReaderValue<double> kt08upliketag_ovr_EfracLR(kt08LRread,"kt08upliketag_ovr_Efrac");
    TTreeReaderValue<double> kt08dwnliketag_ovr_EfracLR(kt08LRread,"kt08dwnliketag_ovr_Efrac");
    TTreeReaderValue<double> kt08leptontag_ovr_EfracLR(kt08LRread,"kt08leptontag_ovr_Efrac");
	TTreeReaderValue<int> kt08leptontag_ovr_ntrksLR(kt08LRread,"kt08leptontag_ovr_ntrks");
	TTreeReaderValue<int> kt08upliketag_ovr_ntrksLR(kt08LRread,"kt08upliketag_ovr_ntrks");
	TTreeReaderValue<int> kt08dwnliketag_ovr_ntrksLR(kt08LRread,"kt08dwnliketag_ovr_ntrks");
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

	//overlay for kt15
	TH1D* h15lEfrac = new TH1D("h15lEfrac","Overlay Jet Energy Fraction With kt R=1.5; Jet Energy %",50,0.,1.0);
	TH1D* h15uEfrac = new TH1D("h15uEfrac","",50,0.,1.0);
	TH1D* h15dEfrac = new TH1D("h15dEfrac","Overlay Jet Energy Fraction With kt R=1.5; Jet Energy %",50,0.,1.0);
	TH1D* h15lntrks = new TH1D("h15lntrks","Reconstructed Overlay Tracks With kt R=1.5; N Tracks",20,-.5,20.5);
	TH1D* h15untrks = new TH1D("h15untrks","Reconstructed Overlay Tracks With kt R=1.5; N Tracks",20,-.5,20.5);
	TH1D* h15dntrks = new TH1D("h15dntrks","Reconstructed Overlay Tracks With kt R=1.5; N Tracks",20,-.5,20.5);

	//overlay for kt08
	TH1D* h08lEfrac = new TH1D("h08lEfrac","Overlay Jet Energy Fraction With kt R=0.8; Jet Energy %",50,0.,1.0);
	TH1D* h08uEfrac = new TH1D("h08uEfrac","",50,0.,1.0);
	TH1D* h08dEfrac = new TH1D("h08dEfrac","Overlay Jet Energy Fraction With kt R=0.8; Jet Energy %",50,0.,1.0);
	TH1D* h08lntrks = new TH1D("h08lntrks","Reconstructed Overlay Tracks With kt R=0.8; N Tracks",20,-.5,20.5);
	TH1D* h08untrks = new TH1D("h08untrks","Reconstructed Overlay Tracks With kt R=0.8; N Tracks",20,-.5,20.5);
	TH1D* h08dntrks = new TH1D("h08dntrks","Reconstructed Overlay Tracks With kt R=0.8; N Tracks",20,-.5,20.5);

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

	while( kt15LRread.Next()){
		h15lEfrac->Fill(*kt15leptontag_ovr_EfracLR);
		h15uEfrac->Fill(*kt15upliketag_ovr_EfracLR);
		h15dEfrac->Fill(*kt15dwnliketag_ovr_EfracLR);

		h15lntrks->Fill(*kt15leptontag_ovr_ntrksLR);
		h15untrks->Fill(*kt15upliketag_ovr_ntrksLR);
		h15dntrks->Fill(*kt15dwnliketag_ovr_ntrksLR);
	}

		while( kt08LRread.Next()){
		h08lEfrac->Fill(*kt08leptontag_ovr_EfracLR);
		h08uEfrac->Fill(*kt08upliketag_ovr_EfracLR);
		h08dEfrac->Fill(*kt08dwnliketag_ovr_EfracLR);

		h08lntrks->Fill(*kt08leptontag_ovr_ntrksLR);
		h08untrks->Fill(*kt08upliketag_ovr_ntrksLR);
		h08dntrks->Fill(*kt08dwnliketag_ovr_ntrksLR);
	}
	//loop over pure tree
	//while( pureLRread.Next()){
		
		//std::cout<<*puremcqqLR<<" ";
		//hmcWqq->Fill((*puremcqqLR));

	//	if( *puretagCosPsiSumLR < mctagcut ) continue;
		
		//	hpureWqq->Fill((*puremctWqqLR));

	//}


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


////////plots for jet min tracks
	TFile* Z = TFile::Open("../../2f_Z_had_LR.root");
	TFile* WWh = TFile::Open("../../4f_WW_had_LR.root");
	TFile* ZZ = TFile::Open("../../4f_ZZ_semi_LR.root");
	double weightZ = 1.06611;
	double weightWWh = 1.06676;
	double weightZZ = 0.05433;	
	double weightWWsLR = 0.784017;

	TTreeReader LRread("eekttree", fLR);
	TTreeReader Zread("eekttree",Z);
	TTreeReader WWhread("eekttree",WWh);
	TTreeReader ZZread("eekttree",ZZ);

	TTreeReaderValue<int> leasttrkLR(LRread,"eektjetLeastNTrks");
	TTreeReaderValue<int> leasttrkZ(Zread,"eektjetLeastNTrks");
	TTreeReaderValue<int> leasttrkWWh(WWhread,"eektjetLeastNTrks");
	TTreeReaderValue<int> leasttrkZZ(ZZread,"eektjetLeastNTrks");

	TH1D* LRtrk = new TH1D("wwqqlnuLeastTrk","Events Min Tracks > 0;N Tracks",25,-0.5,24.5);
	TH1D* Ztrk = new TH1D("zqqLeastTrk","Jet with Minimum Tracks > 0;N Tracks",25,-0.5,24.5);
	TH1D* WWhtrk = new TH1D("wwqqqqLeastTrk","Events Min Tracks > 0;N Tracks",25,-0.5,24.5);
	TH1D* ZZtrk = new TH1D("zzLeastTrk","Events Min Tracks > 0;N Tracks",25,-0.5,24.5);
	while( LRread.Next()){
		LRtrk->Fill(*leasttrkLR,weightWWsLR);
	}
	while( Zread.Next()){
		Ztrk->Fill(*leasttrkZ,weightZ);
	}
	while( WWhread.Next()){
		WWhtrk->Fill(*leasttrkWWh, weightWWh);
	}
	while( ZZread.Next()){
		ZZtrk->Fill(*leasttrkZZ, weightZZ);
	}

TCanvas *c5 = new TCanvas("c5","multipads",800,600);
    Ztrk->SetStats(false);
	LRtrk->SetLineColor(kBlack);
	Ztrk->SetLineColor(kRed);
	WWhtrk->SetLineColor(kBlue);
	ZZtrk->SetLineColor(kGreen);
	Ztrk->Draw();
	LRtrk->Draw("same");
	
	WWhtrk->Draw("same");
	ZZtrk->Draw("same");

	TLegend* leg = new TLegend(xlmin,ylmin,xlmin+dx,ylmin+dy);
//leg->SetHeader("#sqrt{s} = 500 GeV: e^{-}_{L} e^{+}_{R} #rightarrow W^{-} W^{+} #rightarrow q q l #nu","C");
leg->AddEntry(Ztrk,"ee #rightarrow qq","l");
leg->AddEntry(WWhtrk,"WW #rightarrow qqqq","l");
leg->AddEntry(ZZtrk,"ZZ #rightarrow qqll","l");
leg->AddEntry(LRtrk,"WW #rightarrow qql #nu","l");

leg->SetBorderSize(1);                          // Include border
leg->Draw();

/// kt15 overlay
	//energy fraction per jet flavor, eektS
TCanvas *c6 = new TCanvas("c6","multipads",800,600);
		
		h15lEfrac->SetLineColor(kGreen);
		h15uEfrac->SetLineColor(kRed);
		h15dEfrac->SetLineColor(kBlue);
		//hlEfrac->SetStats(false);
		h15dEfrac->Draw();		
		h15lEfrac->Draw("sames");
		h15uEfrac->Draw("sames");
		

		
	TLegend* leg4 = new TLegend(xlmin,ylmin,xlmin+dx,ylmin+dy);
leg4->SetHeader("#sqrt{s} = 500 GeV: e^{-}_{L} e^{+}_{R} #rightarrow W^{-} W^{+} #rightarrow q q l #nu","C");
leg4->AddEntry(h15lEfrac,"lepton","l");
leg4->AddEntry(h15uEfrac,"u-like q","l");
leg4->AddEntry(h15dEfrac,"d-like q","l");


leg4->SetBorderSize(1);                          // Include border
leg4->Draw();


//number of overlay tracks per jet flavor eekt
TCanvas *c7 = new TCanvas("c7","multipads",800,600);
		
		h15lntrks->SetLineColor(kGreen);
		h15untrks->SetLineColor(kRed);
		h15dntrks->SetLineColor(kBlue);
		//hlntrks->SetStats(false);
		h15lntrks->Draw();
		h15untrks->Draw("sames");
		h15dntrks->Draw("sames");		
		
		
	TLegend* leg5 = new TLegend(xlmin,ylmin,xlmin+dx,ylmin+dy);
leg5->SetHeader("#sqrt{s} = 500 GeV: e^{-}_{L} e^{+}_{R} #rightarrow W^{-} W^{+} #rightarrow q q l #nu","C");
leg5->AddEntry(h15lntrks,"lepton","l");
leg5->AddEntry(h15untrks,"u-like q","l");
leg5->AddEntry(h15dntrks,"d-like q","l");


leg5->SetBorderSize(1);                          // Include border
leg5->Draw();


//kt08 overlay
TCanvas *c8 = new TCanvas("c8","multipads",800,600);
		
		h08lEfrac->SetLineColor(kGreen);
		h08uEfrac->SetLineColor(kRed);
		h08dEfrac->SetLineColor(kBlue);
		//hlEfrac->SetStats(false);
		h08dEfrac->Draw();		
		h08lEfrac->Draw("sames");
		h08uEfrac->Draw("sames");
		

		
	TLegend* leg6 = new TLegend(xlmin,ylmin,xlmin+dx,ylmin+dy);
leg6->SetHeader("#sqrt{s} = 500 GeV: e^{-}_{L} e^{+}_{R} #rightarrow W^{-} W^{+} #rightarrow q q l #nu","C");
leg6->AddEntry(h08lEfrac,"lepton","l");
leg6->AddEntry(h08uEfrac,"u-like q","l");
leg6->AddEntry(h08dEfrac,"d-like q","l");


leg6->SetBorderSize(1);                          // Include border
leg6->Draw();


//number of overlay tracks per jet flavor eekt
TCanvas *c9 = new TCanvas("c9","multipads",800,600);
		
		h08lntrks->SetLineColor(kGreen);
		h08untrks->SetLineColor(kRed);
		h08dntrks->SetLineColor(kBlue);
		//hlntrks->SetStats(false);
		h08lntrks->Draw();
		h08untrks->Draw("sames");
		h08dntrks->Draw("sames");		
		
		
	TLegend* leg7 = new TLegend(xlmin,ylmin,xlmin+dx,ylmin+dy);
leg7->SetHeader("#sqrt{s} = 500 GeV: e^{-}_{L} e^{+}_{R} #rightarrow W^{-} W^{+} #rightarrow q q l #nu","C");
leg7->AddEntry(h08lntrks,"lepton","l");
leg7->AddEntry(h08untrks,"u-like q","l");
leg7->AddEntry(h08dntrks,"d-like q","l");


leg7->SetBorderSize(1);                          // Include border
leg7->Draw();



}

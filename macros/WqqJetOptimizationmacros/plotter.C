
#include "plotTools.C"
#include <vector>
#include "TFile.h"


void plotter(){



	//path to opt files
	std::string path = "/afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/WqqJetOptFiles/OptimizationOutputFiles/";
	std::string filename = "optfile";
	int fileNo = 0; 


//	std::vector<TFile*> filevec(8);
//	for(unsigned int i=0; i<filevec.size(); i++){
//		filevec.at(i) = TFile::Open( (path+filename+std::to_string(fileNo)+".root").c_str() );
//		fileNo++;
//	}
	TFile* f0 = TFile::Open("/afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/WqqJetOptFiles/OptimizationOutputFiles/optfile0.root");
	TFile* f5 = TFile::Open("/afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/WqqJetOptFiles/OptimizationOutputFiles/optfile5.root");
	TFile* f7 = TFile::Open("/afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/WqqJetOptFiles/OptimizationOutputFiles/optfile7.root");
							//afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/WqqJetOptFiles/OptimizationOutputFiles
	//example code
	/*TFile *f = TFile::Open("../jpsi20gev_cal/MassConstraint_calibrated.root");
	TFile *f2 = TFile::Open("../pi010gev_cal/MassConstraint_calibrated.root");
	TFile *f3 = TFile::Open("../eta20gev_cal/MassConstraint_calibrated.root");
	TFile *f4 = TFile::Open("../etapi020gev_1C_cal/MassConstraint1C_calibrated.root");
	TFile *f5 = TFile::Open("../etapi020gev_2C_cal/MassConstraint2C_calibrated.root");
	

	f->GetObject("tree", jpsitree);
	f2->GetObject("tree", pi0tree);
	f3->GetObject("tree", etatree);
	f4->GetObject("tree", etapi0tree);
	f5->GetObject("tree", etapi02ctree);
	
	TFile *fout = new TFile("formattedplots.root","RECREATE");
	*/

	TFile *fout = new TFile("./plots/optPlots.root","RECREATE");

	TH1D* optDiff;
	TH1D* lowDiff;
	TH1D* hiDiff;
	
	f0->GetObject("cut0_4_11", lowDiff);
	f5->GetObject("cut5_4_11", optDiff);
	f7->GetObject("cut7_4_11", hiDiff);

//	plot(optDiff,"test","",1);
//	plot(lowDiff,"test2","",1);
//	plot(hiDiff,"test3","",1);

	std::vector<TH1D*> hdiffvec{ optDiff, lowDiff, hiDiff };
	std::vector<int> col{1,2,3};
	std::vector<int> lin{1,1,1};
	std::vector<std::string> legdesc{"YCut 5e-5","YCut 1e-3","YCut 5e-6"}; 
	plotsuper( hdiffvec, col, lin, legdesc, "WW#rightarrow qq #mu #nu eLpR", "SupDiff","", 1);
	

	//no cut diff
	TH1D* nocutDiff;
	f0->GetObject("cut0_0_0", nocutDiff);
	plot( nocutDiff, "nocutDiff","",1);



	//mass distributions
	TH1D* nocutMass;
	TH1D* optMass;
	f0->GetObject("masscut0_0_0", nocutMass);
	f5->GetObject("masscut5_4_11", optMass);
	std::vector<TH1D*> hmassvec{ optMass, nocutMass};
	std::vector<int> col2{1,2};
	std::vector<int> lin2{1,1};
	std::vector<std::string> legdesc2{"YCut 5e-5, Pt>2GeV","YCut 1e-3, No Cuts"};
	plotsuper( hmassvec, col2, lin2, legdesc2,"WW#rightarrow qq #mu #nu eLpR","SupMass","",1);


	//TGraphs
	TGraph* FWHM_pt;
	TGraph* Mode_pt;
	TGraph* ModeEnt_pt;
	TGraph* FWHM_cost;
	TGraph* Mode_cost;
	TGraph* ModeEnt_cost;


	TGraph* FWHM_ptLO;
	TGraph* Mode_ptLO;
	TGraph* ModeEnt_ptLO;
	TGraph* FWHM_costLO;
	TGraph* Mode_costLO;
	TGraph* ModeEnt_costLO;

	TGraph* FWHM_ptHI;
	TGraph* Mode_ptHI;
	TGraph* ModeEnt_ptHI;
	TGraph* FWHM_costHI;
	TGraph* Mode_costHI;
	TGraph* ModeEnt_costHI;



	f5->GetObject("fwhm_pt5", FWHM_pt);
	f5->GetObject("mode_pt5", Mode_pt);
	f5->GetObject("modeEnt_pt5", ModeEnt_pt);
	FWHM_pt->SetName("YCut 5e-5");
	Mode_pt->SetName("YCut 5e-5");
	ModeEnt_pt->SetName("YCut 5e-5");

	f5->GetObject("fwhm_cost5", FWHM_cost);
	f5->GetObject("mode_cost5", Mode_cost);
	f5->GetObject("modeEnt_cost5", ModeEnt_cost);
	FWHM_cost->SetName("YCcut 5e-5");
	Mode_cost->SetName("YCut 5e-5");
	ModeEnt_cost->SetName("YCut 5e-5");

	f0->GetObject("fwhm_pt0", FWHM_ptLO);
	f0->GetObject("mode_pt0", Mode_ptLO);
	f0->GetObject("modeEnt_pt0", ModeEnt_ptLO);
	FWHM_ptLO->SetName("YCut 1e-3");
	Mode_ptLO->SetName("YCut 1e-3");
	ModeEnt_ptLO->SetName("YCut 1e-3");

	f0->GetObject("fwhm_cost0", FWHM_costLO);
	f0->GetObject("mode_cost0", Mode_costLO);
	f0->GetObject("modeEnt_cost0", ModeEnt_costLO);
	FWHM_costLO->SetName("YCut 1e-3");
	Mode_costLO->SetName("YCut 1e-3");
	ModeEnt_costLO->SetName("YCut 1e-3");

	f7->GetObject("fwhm_pt7", FWHM_ptHI);
	f7->GetObject("mode_pt7", Mode_ptHI);
	f7->GetObject("modeEnt_pt7", ModeEnt_ptHI);
	FWHM_ptHI->SetName("YCut 5e-6");
	Mode_ptHI->SetName("YCut 5e-6");
	ModeEnt_ptHI->SetName("YCut 5e-6");

	f7->GetObject("fwhm_cost7", FWHM_costHI);
	f7->GetObject("mode_cost7", Mode_costHI);
	f7->GetObject("modeEnt_cost7", ModeEnt_costHI);
	FWHM_costHI->SetName("YCut 5e-6");
	Mode_costHI->SetName("YCut 5e-6");
	ModeEnt_costHI->SetName("YCut 5e-6");

//	gr1->SetMarkerColor(kBlue);
//    gr1->SetMarkerStyle(21);

	FWHM_pt->SetMarkerColor(kBlue);
	Mode_pt->SetMarkerColor(kBlue);
	ModeEnt_pt->SetMarkerColor(kBlue);
	FWHM_cost->SetMarkerColor(kBlue);
	Mode_cost->SetMarkerColor(kBlue);
	ModeEnt_cost->SetMarkerColor(kBlue);
	FWHM_pt->SetMarkerStyle(21);
	Mode_pt->SetMarkerStyle(21);
	ModeEnt_pt->SetMarkerStyle(21);
	FWHM_cost->SetMarkerStyle(21);
	Mode_cost->SetMarkerStyle(21);
	ModeEnt_cost->SetMarkerStyle(21);

	FWHM_ptLO->SetMarkerColor(kRed);
	Mode_ptLO->SetMarkerColor(kRed);
	ModeEnt_ptLO->SetMarkerColor(kRed);
	FWHM_costLO->SetMarkerColor(kRed);
	Mode_costLO->SetMarkerColor(kRed);
	ModeEnt_costLO->SetMarkerColor(kRed);
	FWHM_ptLO->SetMarkerStyle(22);
	Mode_ptLO->SetMarkerStyle(22);
	ModeEnt_ptLO->SetMarkerStyle(22);
	FWHM_costLO->SetMarkerStyle(22);
	Mode_costLO->SetMarkerStyle(22);
	ModeEnt_costLO->SetMarkerStyle(22);

	FWHM_ptHI->SetMarkerColor(kGreen);
	Mode_ptHI->SetMarkerColor(kGreen);
	ModeEnt_ptHI->SetMarkerColor(kGreen);
	FWHM_costHI->SetMarkerColor(kGreen);
	Mode_costHI->SetMarkerColor(kGreen);
	ModeEnt_costHI->SetMarkerColor(kGreen);
	FWHM_ptHI->SetMarkerStyle(23);
	Mode_ptHI->SetMarkerStyle(23);
	ModeEnt_ptHI->SetMarkerStyle(23);
	FWHM_costHI->SetMarkerStyle(23);
	Mode_costHI->SetMarkerStyle(23);
	ModeEnt_costHI->SetMarkerStyle(23);

	//test
	//plot( FWHM_pt, "testg","","",1);

	

	TMultiGraph *mgfwhmPT = new TMultiGraph();
	mgfwhmPT->Add(FWHM_pt);
	mgfwhmPT->Add(FWHM_ptLO);
	mgfwhmPT->Add(FWHM_ptHI);
//	mgfwhmPT->GetXaxis()->SetTitle("Pt Cut [GeV]");
//	mgfwhmPT->GetYaxis()->SetTitle("Full Width Half Maximum [GeV]");
	plot(mgfwhmPT, "mgfwhmPt", "ALP","", "Pt Cut [GeV]", "Full Width Half Maximum [GeV]", 1);
	
	TMultiGraph *mgmodePT = new TMultiGraph();
	mgmodePT->Add(Mode_pt);
	mgmodePT->Add(Mode_ptLO);
	mgmodePT->Add(Mode_ptHI);
	plot(mgmodePT, "mgmodePt", "ALP","","Pt Cut [GeV]", "Mode [GeV]", 1);

	TMultiGraph *mgmodeEntPT = new TMultiGraph();
	mgmodeEntPT->Add(ModeEnt_pt);
	mgmodeEntPT->Add(ModeEnt_ptLO);
	mgmodeEntPT->Add(ModeEnt_ptHI);
	plot(mgmodeEntPT, "mgmodeEntPt", "alp","","Pt Cut [GeV]", "Mode Entries", 1);
/// cost next

	TMultiGraph *mgfwhmCOST = new TMultiGraph();
	mgfwhmCOST->Add(FWHM_cost);
	mgfwhmCOST->Add(FWHM_costLO);
	mgfwhmCOST->Add(FWHM_costHI);
	plot(mgfwhmCOST, "mgfwhmCost", "ALP","","Cos#theta Cut ", "Full Width Half Maximum [GeV]", 1);

	TMultiGraph *mgmodeCOST = new TMultiGraph();
	mgmodeCOST->Add(Mode_cost);
	mgmodeCOST->Add(Mode_costLO);
	mgmodeCOST->Add(Mode_costHI);
	plot(mgmodeCOST, "mgmodeCost", "ALP","","Cos#theta Cut ", "Mode [GeV]", 1);

	TMultiGraph *mgmodeEntCOST = new TMultiGraph();
	mgmodeEntCOST->Add(ModeEnt_cost);
	mgmodeEntCOST->Add(ModeEnt_costLO);
	mgmodeEntCOST->Add(ModeEnt_costHI);
	plot(mgmodeEntCOST, "mgmodeEntCost", "ALP","","Cos#theta Cut ", "Mode Entries", 1);
	

}

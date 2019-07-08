
#include "plotTools.C"
#include <vector>
#include "TFile.h"


void plotter(){



	//path to opt files
	std::string path = "/afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/WqqJetOptFiles/OptimizationOutputFiles/";
	std::string filename = "optfile";
	int fileNo = 0; 


	std::vector<TFile*> filevec(8);
	for(unsigned int i=0; i<filevec.size(); i++){
		filevec.at(i) = TFile::Open( (path+filename+std::to_string(fileNo)+".root").c_str() );
	}

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
	
	filevec.at(0)->GetObject("cut5_4_11", lowDiff);
	filevec.at(5)->GetObject("cut5_4_11", optDiff);
	filevec.at(7)->GetObject("cut5_4_11", hiDiff);

	std::vector<TH1D*> hdiffvec{ optDiff, lowDiff, hiDiff };
	std::vector<int> col{1,2,3};
	std::vector<int> lin{1,1,1};
	std::vector<std::string> legdesc{"ycut1","ycut2","ycut3"}; 
	plotsuper( hdiffvec, col, lin, legdesc, "", "SupDiff","./plots/", 1);
	

	//no cut diff
	TH1D* nocutDiff;
	filevec.at(0)->GetObject("cut0_0_0", nocutDiff);
	plot( nocutDiff, "nocutDiff","./plots/",1);



	//mass distributions
	TH1D* nocutMass;
	TH1D* optMass;
	filevec.at(0)->GetObject("masscut0_0_0", nocutMass);
	filevec.at(5)->GetObject("masscut5_4_11", optMass);
	std::vector<TH1D*> hmassvec{ optMass, nocutMass};
	std::vector<int> col2{1,2};
	std::vector<int> lin2{1,1};
	std::vector<std::string> legdesc2{"nocutmass","cutoptmass"};
	plotsuper( hmassvec, col2, lin2, legdesc2,"","SupMass","./plots/",1);


	//TGraphs
	TGraph* FWHM_pt;
	TGraph* Mode_pt;
	TGraph* ModeEnt_pt;
	TGraph* FWHM_cost;
	TGraph* Mode_cost;
	TGraph* ModeEnt_cost;

	



	

}

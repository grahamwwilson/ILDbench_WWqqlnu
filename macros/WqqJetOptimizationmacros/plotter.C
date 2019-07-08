


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

}

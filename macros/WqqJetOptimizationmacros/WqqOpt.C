#include "Wqqtree.C"
#include "plotTools.C"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

	ofstream logfile;
	std::string path1= "/afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/WqqJetOptFiles/OptimizationOutputLogs/";



//GLOBAL VECS to store data over each file
	//extract info from each plot
	std::vector<double> FWHM;
	std::vector<double> MODEENTRIES;
	std::vector<double> MODE;
	std::vector<double> RMS;
	std::vector<double> MEAN;
	std::vector<double> YCUT;

	std::vector<double> ptcutPerHist{};
	std::vector<double> costcutPerHist{};
	std::vector<double> ptcutID{};
	std::vector<double> costcutID{};
	std::vector<double> ycutID{};

//require pt higher than pt cut and require particles more central than cost cut
void Loop(Wqqtree& mclass, std::vector<double> ptcutPerHist, std::vector<double> costcutPerHist, std::vector<TH1D*> cuthists , std::vector<TH1D*> masshists, double& y)
{

   if (mclass.fChain == 0) return;

   Long64_t nentries = mclass.fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = mclass.LoadTree(jentry);
      if (ientry < 0) break;
      nb = mclass.fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	if(jentry == 0 ){
		y = mclass.ycut;
	}

	std::vector<TLorentzVector> Ws{};
	for(unsigned int i=0; i< cuthists.size(); i++){
		TLorentzVector Wqq;
		Ws.push_back(Wqq);
	}

	//loop over all the cuts
	for(unsigned int i=0; i< cuthists.size(); i++){
			//loop over the jets for each cut hist, and add together 4vecs that pass the cuts
			for(unsigned int j=0; j< mclass.RemainJetsJets->size(); j++){
				if( (ptcutPerHist.at(i) == -1) || ( mclass.RemainJetsJets->at(j).Pt() > ptcutPerHist.at(i)) ){
					if( (costcutPerHist.at(i) == -1) || (mclass.RemainJetsJets->at(j).CosTheta() < costcutPerHist.at(i)) ) {
							Ws.at(i) += mclass.RemainJetsJets->at(j);
					}
				}
			}

		cuthists.at(i)->Fill(  Ws.at(i).M()- mclass.mcqq->M() );
		masshists.at(i)->Fill( Ws.at(i).M() );
	}
	
   }

}
void print(std::vector<double> v){
	for(unsigned int i=0; i< v.size(); i++){
		logfile<<v.at(i)<<" ";
	}
	logfile<<std::endl;
}
double getRMS( TH1D* h){
	return h->GetRMS();
}
double getMean( TH1D* h){
	return h->GetMean();
}
double getModeEntries( TH1D* h){
	//mode entries is sum of max bin and nearest neighbors
	double ModeEntries = h->GetBinContent(h->GetMaximumBin());
	ModeEntries += h->GetBinContent(h->GetMaximumBin()-1);
	ModeEntries += h->GetBinContent(h->GetMaximumBin()+1);
	return ModeEntries;
}
double getMode(TH1D* h){
	
	double CenterEntries = h->GetBinContent(h->GetMaximumBin());
	double LeftEntries = h->GetBinContent(h->GetMaximumBin()-1);
	double RightEntries = h->GetBinContent(h->GetMaximumBin()+1);
	double TotalEntries = LeftEntries + CenterEntries + RightEntries;
	//define weights
	double wl,wc,wr;
	wl = LeftEntries/TotalEntries;
	wc = CenterEntries/TotalEntries;
	wr = RightEntries/TotalEntries;
	double xl,xc,xr;
	xl = h->GetXaxis()->GetBinCenter(h->GetMaximumBin()-1);
	xc = h->GetXaxis()->GetBinCenter(h->GetMaximumBin());
	xr = h->GetXaxis()->GetBinCenter(h->GetMaximumBin()+1);

	double Mode = wl*xl + wc*xc + wr*xr;
	
	return Mode;

}
double getFWHM( TH1D* h){
		
	int binmax = h->GetMaximumBin();
	//double mode = h->GetXaxis()->GetBinCenter(binmax);
	double CenterEntries = h->GetBinContent(binmax);
	double LeftEntries = h->GetBinContent(binmax);
	double RightEntries = h->GetBinContent(binmax);	
	
	double AverageEntries = (LeftEntries + CenterEntries + RightEntries)/3.;


	//step left and right of the mode
	double halfMax = AverageEntries/2.;
	double NBinsX = h->GetNbinsX();
	double x0_l=-1;
	double x0_r=-1;
	double xa,xb;
	double Na,Nb,Ntot;
	double wa,wb;

//check to the right //peform the simplest case (no expanding bin window for cases with increasing or equal bins to the right)
	for(int ibin=binmax; ibin<NBinsX-1; ibin++){
		if( h->GetBinContent(ibin) <= halfMax ){
			Nb = halfMax - h->GetBinContent(ibin);
			Na = h->GetBinContent(ibin-1) - halfMax;
			xb = h->GetXaxis()->GetBinCenter(ibin);
			xa = h->GetXaxis()->GetBinCenter(ibin-1);
			Ntot = Na+Nb;
			wa = 1 - (Na/Ntot);
			wb = 1 - (Nb/Ntot);
			x0_r = wa*xa + wb*xb;
			break;
		}	
	}

	for(int ibin=binmax; ibin>0; ibin--){
		if( h->GetBinContent(ibin) <= halfMax){
			Nb= halfMax - h->GetBinContent(ibin);
			Na= h->GetBinContent(ibin+1) - halfMax;
			xb = h->GetXaxis()->GetBinCenter(ibin);
			xa = h->GetXaxis()->GetBinCenter(ibin-1);
			Ntot = Na+Nb;
			wa = 1 - (Na/Ntot);
			wb = 1 - (Nb/Ntot);
			x0_l = wa*xa + wb*xb;
			break;
		}
	}

	if( (x0_l ==-1) || (x0_r==-1)){
		return -1; //cant find FWHM
	}

	return x0_r - x0_l;
	
} 

void AnalyzeFile(std::string filename, std::string treename, int ycutNo){
	//read in list of files


	//instantiate make files
	Wqqtree tree(filename, treename);
	std::string path2 = "/afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/WqqJetOptFiles/OptimizationOutputFiles/";
	TFile* f = new TFile((path2+"optfile"+std::to_string(ycutNo)+".root").c_str(),"RECREATE");
	
	
	//get the yvalue for this this file
	double ycut;
	


	std::vector<double> ptcuts;
	ptcuts.push_back(-1);
	
	double ptstep = 0.5;
	double ptstart = ptstep;
	double ptend = 5+ptstep;
	while(ptstart< ptend){
		ptcuts.push_back(ptstart);
		ptstart+=ptstep;
	}
	print(ptcuts);

	std::vector<double> costcuts;
	costcuts.push_back(-1);
	
	double coststep = 0.01;
	double coststart = 0.9;
	double costend = 1.0+coststep;
	while(coststart<costend){
		costcuts.push_back(coststart);
		coststart+=coststep;
	}
	print(costcuts);

	std::vector<TH1D*> cuthists{};
	std::vector<TH1D*> masshists{};
	//std::vector<double> ptcutPerHist{};
	//std::vector<double> costcutPerHist{};
	//std::vector<double> ycutPerHist{};

	//for all combinations of cuts loop and produce plots
	for(unsigned int i=0; i< ptcuts.size(); i++){
		for(unsigned int j=0; j< costcuts.size(); j++){

				
			//do loops over the trees
			TH1D* hist = initTH1D( "cut"+std::to_string(ycutNo)+"_"+std::to_string(i)+"_"+std::to_string(j), "Generator Mass Difference;  M_{qq}^{meas} - M_{qq}^{gen}; Events Per 0.5 GeV Bin", 400, -100, 100);
			TH1D* qqmass = initTH1D( "masscut"+std::to_string(ycutNo)+"_"+std::to_string(i)+"_"+std::to_string(j)," W #rightarrow qq Mass; Mass [GeV]; Events Per 0.5 GeV Bin", 200, 30., 130. );
			cuthists.push_back(hist);	
			masshists.push_back(qqmass);
			ptcutPerHist.push_back(ptcuts.at(i));
			costcutPerHist.push_back(costcuts.at(j));
			ptcutID.push_back(i);
			costcutID.push_back(j);
			//ycutPerHist.push_back(ycut);

		
		}
	}
	//	print(ptcutPerHist);
	//	print(costcutPerHist);
			Loop( tree, ptcutPerHist, costcutPerHist , cuthists, masshists, ycut);

	int itr= FWHM.size();
	int j;

	//init 2d plots
	double* ptcutx = new double[ptcuts.size()];
	double* costcutx = new double[costcuts.size()-1];
	int ind=0;
	for(unsigned int i =0; i< ptcuts.size(); i++){
		if(ptcuts.at(i) == -1){
			ptcutx[ind] = 0;
			ind++;
			continue;
		}
		ptcutx[ind] = ptcuts.at(i);
		ind++;
	}
	ind =0;
	for(unsigned int i=0; i< costcuts.size(); i++){
		if(costcuts.at(i) == -1) continue;
		costcutx[ind] = costcuts.at(i);
		ind++;
	}
	
	
	double* fwhm_pt = new double[ptcuts.size()];
	double* fwhm_cost = new double[costcuts.size()-1];
	double* mode_pt = new double[ptcuts.size()];
	double* mode_cost = new double[costcuts.size()-1];
	double* modeEnt_pt = new double[ptcuts.size()];
	double* modeEnt_cost = new double[costcuts.size()-1];
	
	///test plots
	for(unsigned int i=0; i<cuthists.size(); i++){
		//cuthists.at(i)->Fit("gaus");
		FWHM.push_back( getFWHM(cuthists.at(i)) );
		MODEENTRIES.push_back( getModeEntries( cuthists.at(i)) );
		MODE.push_back( getMode( cuthists.at(i)) );
		RMS.push_back( getRMS( cuthists.at(i)) );
		MEAN.push_back( getMean( cuthists.at(i)) );
		YCUT.push_back( ycut );
		ycutID.push_back(ycutNo);


		j = i+itr;
		plot(cuthists.at(i), std::to_string(ycutNo)+"cut"+std::to_string(i),"",0);
		logfile<<" ycut: "<<ycut<<" ("<<std::to_string(ycutNo)<<")"<<" ptcut: "<<ptcutPerHist.at(j)<<" ("<<ptcutID.at(j)<<")"<<" costcut: "<<costcutPerHist.at(j)<<" ("<<costcutID.at(j)<<")"<<" FWHM: "<< FWHM.at(j) <<" RMS: "<<RMS.at(j)<<" Mode: "<<MODE.at(j)<<" mean: "<<MEAN.at(j)<<" modeEnt: "<<MODEENTRIES.at(j)<<std::endl;

	}

		//create profiles for cuts as a fn of statistic
	int costitr = 0;
	int ptitr = 0;
	for(unsigned int i=0; i<cuthists.size(); i++){
		j = i+itr;
		if(ptcutPerHist.at(i)== -1 && costcutPerHist.at(i) == -1){
			fwhm_pt[ptitr]=FWHM.at(j);
			mode_pt[ptitr] = MODE.at(j);
			modeEnt_pt[ptitr] = MODEENTRIES.at(j);
			ptitr++;
			continue;
		} 		

		if(ptcutPerHist.at(i) == -1 ){
			//fill cost cut only
			fwhm_cost[costitr]= FWHM.at(j);
			mode_cost[costitr]= MODE.at(j);
			modeEnt_cost[costitr]= MODEENTRIES.at(j);
			costitr++;
		}
		if(costcutPerHist.at(i) == -1){
			//fill pt cut only
			fwhm_pt[ptitr]= FWHM.at(j);
			mode_pt[ptitr]= MODE.at(j);
			modeEnt_pt[ptitr] = MODEENTRIES.at(j);
			ptitr++;
		}
	} 
 
	
	//when arrays are filled make the plots tag with the ycutNo
	TGraph* g = initTGraph("fwhm_pt"+std::to_string(ycutNo), "", ptcuts.size(), ptcutx, fwhm_pt  );
	g->Write();
	g = initTGraph("fwhm_cost"+std::to_string(ycutNo),"",costcuts.size()-1,costcutx,fwhm_cost);
	g->Write();
	g =initTGraph("mode_pt"+std::to_string(ycutNo),"", ptcuts.size(),ptcutx,mode_pt);
	g->Write();
	g= initTGraph("mode_cost"+std::to_string(ycutNo),"", costcuts.size()-1,costcutx,mode_cost);
	g->Write();
	g =initTGraph("modeEnt_pt"+std::to_string(ycutNo),"", ptcuts.size(),ptcutx,modeEnt_pt);
	g->Write();
	g= initTGraph("modeEnt_cost"+std::to_string(ycutNo),"", costcuts.size()-1,costcutx,modeEnt_cost);
	g->Write();



	f->Write();
	f->Close();
	
}
void printOptimal(){
	double minFWHM = 9999.;
	double maxModeEntries = -1;
	double optInd;	

	logfile<<"OPTIMAL WORKING POINT:"<<std::endl;
	for(unsigned int i=0; i<FWHM.size(); i++){
		if( (FWHM.at(i) <= minFWHM) && (MODEENTRIES.at(i) >= maxModeEntries) && fabs(MEAN.at(i))<10 ){
			minFWHM = FWHM.at(i);
			maxModeEntries = MODEENTRIES.at(i);
			optInd = i;
		}
	}

		logfile<<" ycut: "<<YCUT.at(optInd)<<" ("<<ycutID.at(optInd)<<")"<<" ptcut: "<<ptcutPerHist.at(optInd)<<" ("<<ptcutID.at(optInd)<<")"<<" costcut: "<<costcutPerHist.at(optInd)<<" ("<<costcutID.at(optInd)<<")"<<" FWHM: "<< FWHM.at(optInd) <<" RMS: "<<RMS.at(optInd)<<" Mode: "<<MODE.at(optInd)<<" mean: "<<MEAN.at(optInd)<<" modeEnt: "<<MODEENTRIES.at(optInd)<<std::endl;
	

}
void WqqOpt(){

	  	logfile.open (path1+"optlog.log");

	std::vector<std::string> files{ "WqqOptycut1S1file.root" , "WqqOptycut2S1file.root" , "WqqOptycut3S1file.root" , "WqqOptycut4S1file.root" , "WqqOptycut5S1file.root" , "WqqOptycut6S1file.root", "WqqOptycut7S1file.root", "WqqOptycut8S1file.root"};
//	TFile* f = new TFile("test.root","RECREATE");
//	int ycutNo = 0;
	std::string path = "/afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/WqqJetOptFiles/RootFiles/";
	for( int ycutNo = 0; ycutNo< files.size(); ycutNo++){
		std::cout<<"running file no. "<<ycutNo<<std::endl;
		AnalyzeFile(path+files.at(ycutNo),"TauJets", ycutNo);
	}
	
//	AnalyzeFile("/home/bears/work/research/WWbenchmark/qqMass_opt/optJets/test/WqqOptycut4S1file.root", "TauJets",ycutNo);



	printOptimal();
	logfile.close();
}


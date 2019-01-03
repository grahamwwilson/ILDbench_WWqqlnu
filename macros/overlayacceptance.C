#include "TCanvas.h"
#include "TH1D.h"
#include <vector>
#include "TFile.h"
#include <iostream>

void overlayacceptance(){
			std::cout<<"debug"<<std::endl;
		TCanvas *c1 = new TCanvas("c1","multipads",800,600);
	
	//	const char* file = "4f_WW_semi_LR.root";
		int ncuts = 8;
		//we need to know the cuts defined in code
		std::vector<double> cuts{0.2, 0.4, 0.6, 0.8, 0.91, 0.95, 0.99,1};
		//make efficiency plot
		TFile *f = TFile::Open("4f_WW_semi_LR.root");
	
		TH1D* eff1 = new TH1D("eff1","efficiency with cuts with overlay removal",20,0,1);
		eff1->Sumw2(true);
		TH1D* eff2 = new TH1D("eff2","efficiency with cuts without overlay removal",20,0,1);
		eff2->Sumw2(true);
		
		std::vector<TH1D*> withoverlay(ncuts);
		std::vector<TH1D*> nooverlay(ncuts);

		TH1D* temp;
	std::cout<<"debug"<<std::endl;
		for(int i=0; i<ncuts; i++){
				char cuts[100];
         	sprintf(cuts, "_%d", i);
         	std::string cutnum(cuts);
			
				withoverlay.at(i)=temp;
				f->GetObject(("maxcostheta_cut_"+cutnum).c_str(), nooverlay.at(i));



				f->GetObject(("maxcostheta_cut_ovr_"+cutnum).c_str(), temp);
				withoverlay.at(i)=temp;
		}
		

		std::cout<<"debug"<<std::endl;
		double weight;
		weight = 1/(withoverlay.at(ncuts-1)->GetEntries());

			std::cout<<"debug"<<std::endl;
		int nentries;
		for(unsigned int i=0; i < withoverlay.size(); i++){
			nentries = withoverlay.at(i)->GetEntries();
		
			for(int i=0; i<nentries; i++){
				eff2->Fill( cuts.at(i), weight );		
			}
			

		}
		

		eff2->Draw();


		
}

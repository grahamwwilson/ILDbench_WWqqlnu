#ifndef HISTS
#define HISTS


#include "TH1D.h"
#include "TH2D.h"
#include "ROOT/TThreadedObject.hxx"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "myselector.C"
#include "TFile.h"
#include "TClass.h"
#include "TKey.h"
#include "TH1.h"
#include <string>
#include "TLorentzVector.h"
//#include "TIter.h"
class histset{
	
	public:
	   histset(TFile* f, std::string tag);	
	   void init(); 

	  //lumi stuff
	  double _iLumi;
	  double _Pem;
	  double _Pep;

	  int _nLL;
	  int _nLR;
	  int _nRL;
	  int _nRR;

	void setWeightParams(double iLumi, double Pem, double Pep, int nLL, int nLR, int nRL, int nRR );

	   void AnalyzeEntry(myselector& s); 
	 //  void AnalyzeEntry(mytreevalues& s);

	   //bookeeping enumeration: (if we do this we dont need to worry about hist ptr copies and merging)
	   enum th1d_index{ind_EvisHist, numTH1Hist};
	   enum th2d_index{ numTH2Hist};
	
	std::string _tag{};
	   // make a big vector and load enumerated histograms onto the vector
	 std::vector<ROOT::TThreadedObject<TH1D>* >  TH1Manager{};
	 std::vector<ROOT::TThreadedObject<TH2D>* >  TH2Manager{};
	//std::vector<TH1D> TH1Manager{};
	//st
	TH1D* EvisHist{};//{(_tag+"EvisHist").c_str(),"Visible Energy;GeV; Entries per 10 GeV bin", 70, 0 , 700};
	TH1D* PtvisHist{};
	TH1D* nLepHist{};
	TH1D* mwlepHist{};
	TH1D* mwhadHist{};
	TH1D* EcomHist{};
	TH1D* nRemHist{};
	  //locate the histogram and perform ptr copying 
	  void FillTH1(int index, double x, double w);
	  void FillTH2(int index, double x, double y);
	
	  void WriteHist(std::string outputfilename, std::string TFileOption);

	//Tag for compiling multiple datasets into same file which share the same plots
	//std::string _tag{}; 
	//this tag will automatically appended to the variable name in each histogram on write
	
	//cut flow stuff
	bool orderCuts = true;
	std::vector<std::string> _cutsequence{"nocut", "lepton", "ntracks", "esum","roots","mwlep", "mwhad", "costwl", "costwq"};
	std::vector<int> _nLLpass{};
	std::vector<int> _nLRpass{};
	std::vector<int> _nRLpass{};
	std::vector<int> _nRRpass{};
	std::vector<int> _nTotpass{};	
	
	std::vector<int>& getPassPol(int pol1, int pol2);

	void printtables();

	//cut descriptions
	// lepton = ntau0 > 0
	// ntracks = total track multiplicity > 10
	// esum = total visible energy < 500 GeV
	// roots = center of mass energy (rest frame mass) > 100 GeV
	// mwlep = 40 < leptonic w mass < 120
	// mwhad = 40 < hadronic w mass < 120
	// costw = cos thetaW  > -0.95
	
	
};

histset::histset(TFile* f, std::string tag = ""){
	_tag = tag; 


   //f1 = TFile::Open("hsimple.root");
  /* TIter keyList(f->GetListOfKeys());
   TKey *key;
   //TCanvas c1;
  // c1.Print("hsimple.ps[");
   while ((key = (TKey*)keyList())) {
      TClass *cl = gROOT->GetClass(key->GetClassName());
      if (!cl->InheritsFrom("TH1")) continue;
      TH1 *h = (TH1*)key->ReadObj();
	std::string name = std::string(h->GetName());
	std::string tagname = tag+name;
	h->SetName(tagname.c_str());	
   }*/

	
//	 std::vector<ROOT::TThreadedObject<TH1D>*>  Manager1(numTH1Hist);
//	TH1Manager=Manager1;

//	 std::vector<ROOT::TThreadedObject<TH2D>*>  Manager2(numTH2Hist);
//	TH2Manager=Manager2;

	init();

}
void histset::setWeightParams(double iLumi, double Pem, double Pep, int nLL, int nLR, int nRL, int nRR ){
 	_iLumi = iLumi;
	_Pem = Pem;
	_Pep = Pep;
	_nLL = nLL;
	_nLR = nLR;
	_nRL = nRL;
	_nRR = nRR;

	std::cout<<"Running with "<<iLumi<<" "<<Pem<<" "<<Pep<<" "<<" "<<nLL<<" "<<nLR<<" "<<nRL<<" "<<nRR<<std::endl;
	//init evt cut counters
	std::vector<int> LL(_cutsequence.size());
	std::vector<int> LR(_cutsequence.size());
	std::vector<int> RL(_cutsequence.size());
	std::vector<int> RR(_cutsequence.size());	
	std::vector<int> TOT(_cutsequence.size());
	LL[0] = _nLL;
	LR[0] = _nLR;
	RL[0] = _nRL;
	RR[0] = _nRR;

	TOT[0] = _nLL + _nLR + _nRL + _nRR;

	for(unsigned int i=1; i<_cutsequence.size(); i++){
		LL[i] = 0;
		LR[i] = 0;
		RL[i] = 0;
		RR[i] = 0;
		TOT[i] = 0;
	}
	_nLLpass = LL;
	_nLRpass = LR;
	_nRLpass = RL;
	_nRRpass = RR;
	_nTotpass = TOT;

	
}
template <class type>
void printvec(std::vector<type> vec){
	for(unsigned int i=0; i< vec.size(); i++){
	std::cout<<vec[i]<<" ";
	}
	std::cout<<std::endl;
} 
void histset::printtables(){
	//sum tot
	for(unsigned int i=0; i< _nTotpass.size(); i++){
		_nTotpass.at(i) = _nLLpass[i] + _nLRpass[i] + _nRLpass[i] + _nRRpass[i];
	}	
	std::cout<<" cut "<<" ";
	printvec( _cutsequence );
	std::cout<<" LL "<<" ";
	printvec( _nLLpass );
	std::cout<<" LR " << " ";
	printvec( _nLRpass );
	std::cout<<" RL " << " ";
	printvec( _nRLpass );
	std::cout<<" RR " << " ";
	printvec( _nRRpass );
	std::cout<<" tot " << " ";
	printvec( _nTotpass );
	
}
void histset::init(){
	EvisHist = new TH1D((_tag+"EvisHist").c_str(),"Visible Energy;GeV; Entries per 10 GeV bin", 70, 0 , 700 );
	PtvisHist = new TH1D((_tag+"PtvisHist").c_str(),"Visible Pt; GeV; Entries per 10 GeV bin",50,0,500);
	nLepHist = new TH1D((_tag+"nLepHist").c_str(),"Number of Reconstructed Leptons; n #l jets; Entries Per Lepton",11,-0.5,10.5);
	mwlepHist = new TH1D((_tag+"mwlepHist").c_str(),"W #rightarrow #l #nu Reconstructed Mass; Mass GeV; Entries Per 5 GeV Bin", 50,0,250);
	mwhadHist = new TH1D((_tag+"mwhadHist").c_str(),"W #rightarrow qq Reconstructed Mass;Mass GeV; Entries Per 5 GeV Bin", 50,0,250);
	EcomHist = new TH1D((_tag+"EcomHist").c_str(),"#sqrt{s};GeV; Entries per 10 GeV bin", 70,0, 700);
	nRemHist = new TH1D((_tag+"nRemHist").c_str(), "Number of Jet Fragments;N Jets",21,-0.5,20.5);
//init TH1D
	//TH1Manager.at(ind_EvisHist) = new ROOT::TThreadedObject<TH1D>("EvisHist", "Visble Energy;GeV;Entries per 10 GeV bin", 70, 0, 700);
// init TH2D
	//TH2Manager.at(ind_cat0PtcmPtisrDphiCMIHist) = new ROOT::TThreadedObject<TH2D>("cat0PtcmPtisrDphiCMIHist", "cat0: PTCM/PTISR vs dphiCMI ;dphiCMI;PTCM/PTISR", 50, 0, 3.2, 50, 0,2);
	//TH2Manager.at(ind_cat1PtcmPtisrDphiCMIHist) = new ROOT::TThreadedObject<TH2D>("cat1PtcmPtisrDphiCMIHist", "cat1: PTCM/PTISR vs dphiCMI;dphiCMI;PTCM/PTSIR", 50, 0, 3.2,50, 0,2);

}
void histset::FillTH1(int index, double x, double w=1){
	//we must make ptr copies for performance reasons when trying to fill a histogram
	auto myhist = TH1Manager.at(index)->Get();
	myhist->Fill(x,w);
}
void histset::FillTH2(int index, double x, double y){
	auto myhist = TH2Manager.at(index)->Get();
	myhist->Fill(x,y);
}
void histset::WriteHist(std::string outputfilename, std::string TFileOption){

	TFile* outfile = new TFile(outputfilename.c_str(),TFileOption.c_str());


	for(int i=0; i<numTH1Hist; i++){
		//do a check for entries, merge isnt safe on 0 entry histograms
		auto hptr = TH1Manager.at(i)->Get();		
		if(hptr->GetEntries() > 0){
			auto histmerged = TH1Manager.at(i)->Merge();
			TH1D* h = (TH1D*) histmerged->Clone();
			std::string hname(h->GetName());
			outfile->WriteObject(h, (_tag+hname).c_str() );
		}
		else{
			auto h = TH1Manager.at(i)->Get()->Clone();
			std::string hname(h->GetName());
			outfile->WriteObject(h, (_tag+hname).c_str() );
		}
	}

	for(int i=0; i<numTH2Hist; i++){
		auto hptr = TH2Manager.at(i)->Get();
		if(hptr->GetEntries() > 0){
			auto histmerged = TH2Manager.at(i)->Merge();
			TH2D* h = (TH2D*) histmerged->Clone();
			std::string hname(h->GetName());
			outfile->WriteObject(h,(_tag+hname).c_str() );
		}
		else{
			auto h = TH2Manager.at(i)->Get()->Clone();
			std:;string hname(h->GetName());
			outfile->WriteObject(h, (_tag+hname).c_str() );
		}
	}	

}
bool leptoncut(int& count, int ntau){
	if(ntau > 0){ 
		count++;
		return true;
	}
	return false;
}
bool ntrackscut(int& count, int ntrks){
	if(ntrks > 10){
		count++;
		return true;
	}
	return false;
}
bool esumcut(int& count, double evis){
	if( evis < 500){
		count++;
		return true;
	}
	return false;
}
bool rootscut(int& count, double ecom){
	if( ecom > 100){
		count++;
		return true;
	}
	return false;
}
bool mwlepcut(int& count, double wlmass){
	if( wlmass > 40 && wlmass < 120 ){
		count++;
		return true;
	}
	return false;
}
bool mwhadcut(int& count, double wqmass){
	if( wqmass > 40 && wqmass < 120){
		count++;
		return true;
	}
	return false;
}
bool costwcut(int& count, double costw){
	if( costw > -0.95 ){
		count++;
		return true;
	}
	return false;
}
std::vector<int>& histset::getPassPol(int pol1, int pol2){
	if(pol1 == -1 && pol2 == -1) return _nLLpass;
	if(pol1 == -1 && pol2 == 1) return _nLRpass;
	if(pol1 == 1 && pol2 == -1) return _nRLpass;
	if(pol1 == 1 && pol2 == 1) return _nRRpass;
}
void histset::AnalyzeEntry(myselector& s){
   	
	//always make a local copy, if its a value dereference.. if you dont do this scope/dereferencing will get really weird, clunky, and unmanageable
	//have to auto& or myreader will try to register copy of the readerarray ptr
	//auto MET = *(s.MET);
	//polarization stuff
//	 Pem = -0.8;
//	 Pep = 0.3;

	double fRm = 0.5*(1+_Pem);
	double fLm = 1-fRm;

	double fRp = 0.5*(1+_Pep);
	double fLp = 1-fRp;

	double wpolLR = fLm*fRp;
	double wpolRL = fRm*fLp;
	double wpolLL = fLm*fLp;
	double wpolRR = fRm*fRp;

	double xsec_new;
	double nev;
	auto pol1 = *(s.polarization1);
	auto pol2 = *(s.polarization2);
	auto xsec = *(s.xsec);

	if( pol1 == -1 && pol2 == -1){
		xsec_new = wpolLL*xsec;
		nev = _nLL;
	}
	if(pol1 == -1 && pol2 == 1){
		xsec_new = wpolLR*xsec;
		nev = _nLR;
	}
	if(pol1 == 1 && pol2 == 1){
		xsec_new = wpolRR*xsec;
		nev = _nRR;
	}
	if(pol1 ==1 && pol2 == -1){
		xsec_new = wpolRL*xsec;
		nev = _nRL;
	}

	double evtw = 1;	
	double thisLumi = ((double)nev)/xsec_new;
	evtw = _iLumi/thisLumi;	

	auto candE0 = *(s.candE0);	
	auto& remE0_preclean = s.remE0;
	auto& remPx0_preclean = s.remPx0;
	auto& remPy0_preclean = s.remPy0;
	auto candPx0 = *(s.candPx0);
	auto candPy0 = *(s.candPy0);
	auto nlep = *(s.ntau0);
	auto candPz0 = *(s.candPz0);
	auto& remPz0_preclean = s.remPz0;
	auto njets0_preclean = *(s.njets0);

	auto nPandoraTrks = *(s.nPandoraTrks);

	nLepHist->Fill(nlep, evtw);
//	nRemHist->Fill(njets0, evtw);
	if(nlep ==0) return;

	//jet preprocessing////////////////////////////////////
	//make std 4vecs to house jets after preselection cuts (pt>2Gev)	
	std::vector<double> remPx0{};
	std::vector<double> remPy0{};
	std::vector<double> remPz0{};
	std::vector<double> remE0{};

	for(unsigned int i = 0; i< remE0_preclean.GetSize(); i++){
		double pt = sqrt(remPx0_preclean[i]*remPx0_preclean[i] + remPy0_preclean[i]*remPy0_preclean[i]);
		if(pt > 2){
			remPx0.push_back( remPx0_preclean[i]);
			remPy0.push_back( remPy0_preclean[i]);
			remPz0.push_back( remPz0_preclean[i]);
			remE0.push_back( remE0_preclean[i]);

		} 	

	}
	int njets0 = remE0.size();
	//////////////////////////////////////////////////////
	 nRemHist->Fill(njets0, evtw);

//	double Emiss;
	double Ejets=0.;
	double Pxjets=0.;
	double Pyjets=0.;
	double Pzjets=0.;
	for(int i=0; i<remE0.size(); i++){
		Ejets = Ejets + remE0[i]; 
		Pxjets = Pxjets + remPx0[i];
		Pyjets = Pyjets + remPy0[i]; 
		Pzjets = Pzjets + remPz0[i];
	}

	double Ptjets= sqrt(Pxjets*Pxjets + Pyjets*Pyjets);
	double Ptcand = sqrt(candPx0*candPx0 + candPy0*candPy0);
	double Evis = candE0 + Ejets;
	//FillTH1(ind_EvisHist, Evis);
	EvisHist->Fill(Evis, evtw);
	PtvisHist->Fill(Ptjets+Ptcand, evtw);

//	nLepHist->Fill(nlep, evtw);
//	nRemHist->Fill(njets0, evtw);
		
   //calculate mwlep //neutrino mass approx 0
   	double Pxmiss, Pymiss, Pzmiss;
	Pxmiss = candPx0;
	Pymiss = candPy0;
	Pzmiss = candPz0;
	for(int i=0; i<remE0.size(); i++){
		Pxmiss += remPx0[i];
		Pymiss += remPy0[i];
		Pzmiss += remPz0[i];
	
	}
	Pxmiss = -Pxmiss;
	Pymiss = -Pymiss;
	Pzmiss = -Pzmiss;

	double Pmiss = sqrt(Pxmiss*Pxmiss + Pymiss*Pymiss + Pzmiss*Pzmiss);

	//lep mass is 4vec lep + miss
	//
	TLorentzVector lep0(candPx0,candPy0, candPz0, candE0 );
	TLorentzVector nu0(Pxmiss, Pymiss, Pzmiss, Pmiss );

	TLorentzVector Wlep0 = lep0+nu0;
	mwlepHist->Fill(Wlep0.M(), evtw);

	//get had mass
	TLorentzVector Wqq0(Pxjets, Pyjets, Pzjets, Ejets);
	mwhadHist->Fill(Wqq0.M(), evtw);
	
	//boost to CM
	TLorentzVector Tot = Wlep0+Wqq0;
	TVector3 cmboost =  Tot.BoostVector();
	Tot.Boost(-cmboost);	
	EcomHist->Fill(Tot.E(), evtw);

// apply cuts
//
//
//_cutsequence{"nocut", "lepton", "ntracks", "esum","roots","mwlep", "mwhad", "costw"};
	bool pass;
	for(unsigned int i=0; i<_cutsequence.size(); i++){
		std::string cut = _cutsequence.at(i);
		if( cut.compare("lepton")==0){ //do lepton cut
		 	pass = leptoncut(getPassPol(pol1,pol2)[i], nlep);
			 if(!pass && orderCuts) break;
		}
		if( cut.compare("ntracks")==0){// track multiplicity
			pass = ntrackscut(getPassPol(pol1,pol2)[i], nPandoraTrks);
			if(!pass & orderCuts) break;
		}
		if( cut.compare("esum")==0){ //visible energy sum
			pass = esumcut(getPassPol(pol1,pol2)[i], Evis);
			if(!pass & orderCuts) break;
		}
		if( cut.compare("roots")==0){ //rest energy 
			pass = rootscut(getPassPol(pol1,pol2)[i], Tot.E());
			if(!pass & orderCuts) break;
		}
		if( cut.compare("mwlep")==0){// leptonic w mass cut
			pass = mwlepcut(getPassPol(pol1,pol2)[i], Wlep0.M());
			if(!pass & orderCuts) break;
		}
		if( cut.compare("mwhad")==0){// hadronic w mass cut
			pass = mwhadcut(getPassPol(pol1,pol2)[i], Wqq0.M());
			if(!pass & orderCuts) break;
		}
		if( cut.compare("costwl")==0){// cos thetaW cut
			pass = costwcut(getPassPol(pol1,pol2)[i], Wlep0.CosTheta());
			if(!pass & orderCuts) break;
		}
		if( cut.compare("costwq")==0){
			pass = costwcut(getPassPol(pol1,pol2)[i], Wqq0.CosTheta());
			if(!pass & orderCuts) break;
		}

	}

}
#endif

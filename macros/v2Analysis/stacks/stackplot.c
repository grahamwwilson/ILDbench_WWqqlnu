//#include "plotTools.C"

void gethists(std::vector<TH1D*>& hists, std::vector<std::string> taglist, std::string histname, TFile* f){
        for(int i=0; i<taglist.size(); i++){
                std::string hname = taglist.at(i)+histname;
                hists.at(i) = (TH1D*) f->Get(hname.c_str());
        }
}



//make stack plots

//void stack(std::string histname ){
//void stackplot(){
void stackplot(std::string histname ){
	TFile* f1 = TFile::Open("../Analysis/eventSel.root");
//	TFile* f1s = TFile::Open("../AnalysisSignal/eventSelS.root");
//	TFile* f2 = TFile::Open("../Analysis/eventSelTau.root");
//	TFile* f2s = TFile::Open("../AnalysisSignal/eventSelSTau.root");
//std::string histname = "EvisHist";
	TCanvas* c = new TCanvas();
	//2f from f1
	//collect BG
	std::vector<std::string> _2f{"BHAg", "ZHAD", "ZL", "WL"};  // "WS", "WWS"};
	std::vector<std::string> _4f{"ZEEL","ZEES","ZNUL", "ZNUS","ZWML","WWHAD", "WWL", "ZZHAD", "ZZL", "ZZS","ZZWWH","ZZWWL"};
	std::vector<std::string> _6f{"EEWW","LLWW","TTB","VVWW","XXWW","XXZ","YYZ"};
	std::vector<std::string> _H{"EEH", "MUH", "TAUH", "QQH", "NNH"};

	//get special 
	std::vector<std::string> _S1{"WWS"};
	std::vector<std::string> _S2{"WS1"};
	std::vector<std::string> _BG{"WSBG"};
	std::vector<std::string> _S2Full{"WS"};


	//get tight hists
	std::vector<TH1D*> _2ftight(_2f.size());
	std::vector<TH1D*> _4ftight(_4f.size());
	std::vector<TH1D*> _6ftight(_6f.size());
	std::vector<TH1D*> _Htight(_H.size());
//	std::vector<TH1D*> _4fspectight(_BG.size());

	//signal tight
	std::vector<TH1D*> _wwstight(_S1.size());
	std::vector<TH1D*> _wstight(_S2.size());

	//get loos hists
	std::vector<TH1D*> _2floose(_2f.size());
        std::vector<TH1D*> _4floose(_4f.size());
        std::vector<TH1D*> _6floose(_6f.size());
        std::vector<TH1D*> _Hloose(_H.size());
        std::vector<TH1D*> _4fspecloose(_BG.size());

        //signal tight
        std::vector<TH1D*> _wwsloose(_S1.size());
        std::vector<TH1D*> _wsloose(_S2.size());
	

	//populatehists
	//bg tight
	gethists(_2ftight, _2f, histname, f1);
	gethists(_4ftight, _4f, histname, f1);
	gethists(_6ftight, _6f, histname, f1);
	gethists(_Htight, _H, histname, f1);
//	gethists(_4fspectight, _BG,histname, f1s);

	gethists(_wwstight, _S1, histname, f1);
	gethists(_wstight, _S2Full, histname, f1);

/*	gethists(_2floose, _2f, histname, f2);
        gethists(_4floose, _4f, histname, f2);
        gethists(_6floose, _6f, histname, f2);
        gethists(_Hloose, _H, histname, f2);
        gethists(_4fspecloose, _BG,histname, f2s);

        gethists(_wwsloose, _S1, histname, f1);
        gethists(_wsloose, _S2, histname, f1);
*/
	auto xaxis = _2ftight[0]->GetXaxis()->GetTitle();
	auto yaxis = _2ftight[0]->GetYaxis()->GetTitle();
	//add together appropriate histograms
	TH1D* _2ftot = _2ftight[0];
//	_2ftot->Add(_2floose[0]);
	for(int i =1; i< _2ftight.size(); i++){
		
		_2ftot->Add(_2ftight[i]);
//		_2ftot->Add(_2floose[i]);	
	}
	_2ftot->SetFillColor(39);
//check
//	std::cout<< _2ftot->Integral()<<std::endl;
	TH1D* _4ftot = _4ftight[0];
  //      _4ftot->Add(_4floose[0]);
        for(int i =1; i< _4ftight.size(); i++){

                _4ftot->Add(_4ftight[i]);
             //   _4ftot->Add(_4floose[i]);
        }
//	_4ftot->Add(_4fspectight[0]);
//	_4ftot->Add(_4fspecloose[0]);
	_4ftot->SetFillColor(29);

	TH1D* _6ftot = _6ftight[0];
//        _6ftot->Add(_6floose[0]);
		std::cout<<_6ftight[0]->GetEntries()<<std::endl;
        for(int i =1; i< _6ftight.size(); i++){
			std::cout<<_6ftight[i]->GetEntries()<<std::endl;
                _6ftot->Add(_6ftight[i]);
  //              _6ftot->Add(_6floose[i]);
        }
	_6ftot->SetFillColor(kBlue);

	TH1D* _Htot = _Htight[0];
//        _Htot->Add(_Hloose[0]);
        for(int i =1; i< _Htight.size(); i++){

                _Htot->Add(_Htight[i]);
  //              _Htot->Add(_Hloose[i]);
        }
	_Htot->SetFillColor(kBlack);
	//do signal
	TH1D* _Stight = _wwstight[0];
	_Stight->Add( _wstight[0] );
	_Stight->SetFillColor(kRed);

//	TH1D* _Sloose = _wwsloose[0];
//	_Sloose->Add(_wsloose[0]);
//	_Sloose->SetFillColor(kGreen);

	THStack *hs = new THStack("hs","");
	hs->SetTitle((std::string(_Stight->GetTitle())+";"+std::string(xaxis)+";"+std::string(yaxis)).c_str());
	std::cout<<xaxis;
	//hs->GetXaxis()->SetTitle(xaxis);
	//hs->GetYaxis()->SetTitle(yaxis);
	hs->Add(_Htot);
	hs->Add(_6ftot);
	hs->Add(_4ftot);
	hs->Add(_2ftot);
	hs->Add(_Stight);
	//hs->Add(_Sloose);
	//c->SetLogy();
	hs->Draw("hist");
	float ymax=800.0; float xlmin=0.7; float ylmin=0.7;//was 35 58
        const float dx=0.28;
        const float dy=0.26;
        TLegend* leg = new TLegend(xlmin,ylmin,xlmin+dx,ylmin+dy);
       // TLegend* leg = new TLegend(0.1,0.7,0.48,0.9);
    //    leg->SetHeader(" ","C");

	leg->AddEntry(_Stight, "Tight Signal", "f");
	//leg->AddEntry(_Sloose, "Loose Signal", "f");
	leg->AddEntry(_2ftot, "2 ferm" ,"f");
	leg->AddEntry(_4ftot, "4 ferm" ,"f");
	leg->AddEntry(_6ftot, "6 ferm" ,"f");
	leg->AddEntry(_Htot, "SM Higgs" ,"f");
        /*for(unsigned int i=0; i< hlegdesc.size(); i++){
                leg->AddEntry( hvec.at(i), hlegdesc.at(i).c_str(), "lp");
        }*/

        leg->SetBorderSize(1);                          // Include border
        leg->Draw();

	c->Print((histname+".pdf").c_str());


	//gen diff plots
	//

	TFile* f1s = TFile::Open("../AnalysisSignal/eventSelS.root");
	std::vector<std::string> _WWSignals{"WWS1", "WWS2","WS1", "WSBG", "WWS1BG","WWS2BG"};
	std::vector<TH1D*> massdiffs(_WWSignals.size());
	std::vector<TH1D*> costdiffs(_WWSignals.size());
	gethists(massdiffs,_WWSignals , "mqqdiffHist", f1s);	
	gethists(costdiffs,_WWSignals, "qcostdiffHist", f1s);

	TH1D* mdiff = massdiffs[0];
	TH1D* cdiff = costdiffs[0];
	for(int i=1;i<_WWSignals.size();i++){
		mdiff->Add(massdiffs[i]);
		cdiff->Add(costdiffs[i]);
	}
	TCanvas* cmass = new TCanvas();
	mdiff->Draw("hist:e");
	cmass->Print("mqqdiffHist.pdf");

	TCanvas* ccost = new TCanvas();
	cdiff->Draw("hist:e");
	ccost->Print("qcostdiffHist.pdf");
	

//_2ftot->Draw();

/*
	       // std::string leghead = " ";
       // std::string cname = path+"evis";
        gethists(hists, taglist, "EvisHist", f);
        plotsuper(hists,colors,line,taglist,leghead,cname,"", 1);


         cname = path+"ptvis";
        gethists(hists, taglist, "PtvisHist", f);
        plotsuper(hists,colors,line,taglist,leghead
	ccost->Print(("qcostdiffHist.pdf").c_str());,cname,"", 1);
         cname = path+"nlep";
        gethists(hists, taglist, "nLepHist", f);
        plotsuper(hists,colors,line,taglist,leghead,cname,"", 1);
         cname = path+"mwlep";
        gethists(hists, taglist, "mwlepHist", f);
        plotsuper(hists,colors,line,taglist,leghead,cname,"", 1);
         cname = path+"mwhad";
        gethists(hists, taglist, "mwhadHist", f);
        plotsuper(hists,colors,line,taglist,leghead,cname,"", 1);
         cname = path+"ecom";
        gethists(hists, taglist, "EcomHist", f);
        plotsuper(hists,colors,line,taglist,leghead,cname,"", 1);

         cname = path+"njet";
        gethists(hists, taglist, "nRemHist", f);
        plotsuper(hists,colors,line,taglist,leghead,cname,"", 1);

        cname = path+"ntracks";
        gethists(hists,taglist,"ntracksHist",f);
        plotsuper(hists,colors,line,taglist,leghead,cname,"",1);
        cname = path+"vrecoil";
        gethists(hists,taglist,"vrecoilHist",f);
        plotsuper(hists,colors,line,taglist,leghead,cname,"",1);
        cname = path+"wlrecoil";
        gethists(hists,taglist,"wlrecoilHist",f);
        plotsuper(hists,colors,line,taglist,leghead,cname,"",1);
        cname = path+"costwl";
        gethists(hists,taglist,"costwlHist",f);
        plotsuper(hists,colors,line,taglist,leghead,cname,"",1);
        cname = path+"costwq";
        gethists(hists,taglist,"costwqHist",f);
        plotsuper(hists,colors,line,taglist,leghead,cname,"",1);
        cname = path+"qcost";
        gethists(hists,taglist,"qcostHist",f);
        plotsuper(hists,colors,line,taglist,leghead,cname,"",1);
*/
}

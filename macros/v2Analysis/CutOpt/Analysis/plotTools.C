

TH1D* initTH1D( std::string varname, std::string name, int bins, double xlow, double xup){
	return new TH1D( varname.c_str(), name.c_str(), bins, xlow, xup);
}
TH2D* initTH2D( std::string varname, std::string name, int xbins, double xlow, double xup, int ybins, double ylow, double yup){
	return new TH2D( varname.c_str(), name.c_str(),xbins,xlow,xup,ybins,ylow,yup); 
}
void plot( TH1D* h , std::string cname , std::string tag, bool save){
	TCanvas *c = new TCanvas(cname.c_str(),"m",800,600);
	h->Draw();
	if(!save) return;
	c->Print((tag+cname+".pdf").c_str());
}
void plot( TH2D* h, std::string cname, std::string opt, std::string tag, bool save){
	TCanvas *c = new TCanvas(cname.c_str(), "m",800,600);
	h->Draw(opt.c_str());
    if(!save) return;
	c->Print((tag+cname+".pdf").c_str());
}
void plotsuper( std::vector<TH1D*> hvec, std::vector<int> colors, std::vector<int> linestyles, std::vector<std::string> hlegdesc,std::string legheader, std::string cname, std::string tag, bool save){
// do some sorting so plots arent ugly
//
	int maxHistInd=-1;
	int maxval=-1;
	int thismax;
	for(unsigned int i=0; i<hvec.size(); i++){
		thismax = hvec.at(i)->GetMaximum();
		if(thismax>maxval){
			maxval = thismax;	
			maxHistInd = i;
		}
	}
	//swap the max to first position on the vec
	TH1D* temp = hvec[0];
	int tempcol = colors[0];
	int templin = linestyles[0];
	std::string tempdesc = hlegdesc[0];
	hvec[0]=hvec[maxHistInd];
	hvec[maxHistInd] = temp;
	colors[0] = colors[maxHistInd];
	colors[maxHistInd] = tempcol;
	linestyles[0] = linestyles[maxHistInd];
	linestyles[maxHistInd] = templin;
	hlegdesc[0] = hlegdesc[maxHistInd];
	hlegdesc[maxHistInd] = tempdesc;

	TCanvas* c = new TCanvas((tag+cname).c_str(),"m",800,600);
	//c->SetLogy();
	int color =1;
	for(unsigned int i=0; i< colors.size(); i++){
		hvec.at(i)->SetLineColor(colors.at(i));
	}	
	for(unsigned int i=0; i< linestyles.size(); i++){
		hvec.at(i)->SetMarkerStyle(linestyles.at(i));
		hvec.at(i)->SetMarkerColor(colors.at(i));
		hvec.at(i)->SetLineWidth(2);
	}
	hvec.at(0)->Draw();
	for(unsigned int i=0; i< hvec.size(); i++){
		//if(i==2) hvec.at(i)->SetLineStyle(10);
		//if(i==2) hvec.at(i)->SetLineWidth(3);
		hvec.at(i)->Draw("SAMES");
	}
	float ymax=800.0; float xlmin=0.7; float ylmin=0.7;//was 35 58
	const float dx=0.28;
	const float dy=0.26;
	TLegend* leg = new TLegend(xlmin,ylmin,xlmin+dx,ylmin+dy);
	leg->SetHeader(legheader.c_str(),"C");

	for(unsigned int i=0; i< hlegdesc.size(); i++){
		leg->AddEntry( hvec.at(i), hlegdesc.at(i).c_str(), "lp");
	}

	leg->SetBorderSize(1);                          // Include border
	leg->Draw();
    if(!save) return;
    c->Print((tag+cname+".pdf").c_str());
}

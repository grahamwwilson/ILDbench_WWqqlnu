#include "plotTools.C"

void gethists(std::vector<TH1D*>& hists, std::vector<std::string> taglist, std::string histname, TFile* f){
	for(int i=0; i<taglist.size(); i++){
		std::string hname = taglist.at(i)+histname;
		hists.at(i) = (TH1D*) f->Get(hname.c_str());
	}
}
void scaleToUnity(std::vector<TH1D*>& hists){
	for(unsigned int i=0; i< hists.size(); i++){
		hists.at(i)->Scale(1/hists.at(i)->Integral());
	}
}
void combine(int num){
	TFile *f = TFile::Open("eventSel.root");
std::string path;
std::vector<std::string> taglist;
std::vector<int> colors;
std::vector<int> line;
if(num ==1){
	std::string p = "./plots/2f";
	std::vector<std::string> t{"BHAg", "ZHAD", "ZL", "WL", "WS", "WWS"};
	std::vector<int> c{1,49,29,4, 2, 3};
	std::vector<int> l{1,1,1,1,29,29};
	taglist = t;
	colors = c;
	line = l;
	path =p;
}
if(num==2){
	std::string p = "./plots/4f1";
	std::vector<std::string> t{"ZEEL","ZEES","ZNUL", "ZNUS","ZWML", "WS", "WWS"};
	std::vector<int> c{1,49,29,4,6,2,3};
	std::vector<int> l {1,1,1,1,1,29,29};
	taglist = t;
	colors = c;
	line = l;
	path = p;
}
if(num==3){
	std::string p = "./plots/4f2";
	std::vector<std::string> t{"WWHAD", "WWL", "ZZHAD", "ZZL", "ZZS","ZZWWH","ZZWWL", "WS", "WWS"};
	std::vector<int> c{1,49,29,4,6,37,28,2,3};
	std::vector<int> l{1,1,1,1,1,1,1,29,29};
	taglist = t;
	colors = c;
	line = l;
	path =p;
}
if(num==4){
	std::string p = "./plots/H";
	std::vector<std::string> t{"EEH", "MUH", "TAUH", "QQH", "NNH", "WS", "WWS"};
	std::vector<int> c{1,49,29,4,6,2,3};
	std::vector<int> l{1,1,1,1,1,29,29};
	taglist = t;
	colors = c;
	line = l;
	path=p;
}
if(num ==5){
	std::string p = "./plots/6f";
	std::vector<std::string> t{"EEWW","LLWW","TTB","VVWW","XXWW","XXZ","YYZ", "WS","WWS"};
	std::vector<int> c{1,49,29,4,6,37,28,2,3};
	std::vector<int> l{1,1,1,1,1,1,1,29,29};
	taglist = t;
	colors = c;
	line =l;
	path = p;
	}
	//std::vector<std::string> taglist{"BHAg","ZHAD","ZL", "WL", "WS", "ZEEL","ZEES", "ZNUL", "ZNUS", "WWHAD", "WWL", "WWS", "ZZHAD", "ZZL", "ZZS", "EEH", "MUH", "TAUH", "QQH", "NNH" };

	std::vector<TH1D*> hists(taglist.size());


//	std::vector<int> colors = {1,2,3,4,49,6,7,1,2,3,4,49,6,7,1,2,3,4,49,6};
//	std::vector<int> line = {1,1,1,1,1,1,1,20,21,22,23,24,25,26,27,28,29,30,31,32};
	std::string leghead = " ";
	std::string cname = path+"evis";
	gethists(hists, taglist, "EvisHist", f);
	plotsuper(hists,colors,line,taglist,leghead,cname,"", 1);


	 cname = path+"ptvis";
	gethists(hists, taglist, "PtvisHist", f);
	plotsuper(hists,colors,line,taglist,leghead,cname,"", 1);
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


	//plot rescaled to area 
	cname = path+"evisUnity";
	gethists(hists, taglist, "EvisHist", f);
	scaleToUnity(hists);
	plotsuper(hists,colors,line,taglist,leghead,cname,"", 1);
	 cname = path+"ptvisUnity";
	gethists(hists, taglist, "PtvisHist", f);
	scaleToUnity(hists);
	plotsuper(hists,colors,line,taglist,leghead,cname,"", 1);
	 cname = path+"nlepUnity";
	gethists(hists, taglist, "nLepHist", f);
	scaleToUnity(hists);
	plotsuper(hists,colors,line,taglist,leghead,cname,"", 1);
	 cname = path+"mwlepUnity";
	gethists(hists, taglist, "mwlepHist", f);
	scaleToUnity(hists);
	plotsuper(hists,colors,line,taglist,leghead,cname,"", 1);
	 cname = path+"mwhadUnity";
	gethists(hists, taglist, "mwhadHist", f);
	scaleToUnity(hists);
	plotsuper(hists,colors,line,taglist,leghead,cname,"", 1);
	 cname = path+"ecomUnity";
	gethists(hists, taglist, "EcomHist", f);
	scaleToUnity(hists);
	plotsuper(hists,colors,line,taglist,leghead,cname,"", 1);
	
	 cname = path+"njetUnity";
	gethists(hists, taglist, "nRemHist", f);
	scaleToUnity(hists);
	plotsuper(hists,colors,line,taglist,leghead,cname,"", 1);


	cname = path+"ntracksUnity";
	gethists(hists,taglist,"ntracksHist",f);
	scaleToUnity(hists);
	plotsuper(hists,colors,line,taglist,leghead,cname,"",1);
	cname = path+"vrecoilUnity";
	gethists(hists,taglist,"vrecoilHist",f);
	scaleToUnity(hists);
	plotsuper(hists,colors,line,taglist,leghead,cname,"",1);
	cname = path+"wlrecoilUnity";
	gethists(hists,taglist,"wlrecoilHist",f);
	scaleToUnity(hists);
	plotsuper(hists,colors,line,taglist,leghead,cname,"",1);
	cname = path+"costwlUnity";
	gethists(hists,taglist,"costwlHist",f);
	scaleToUnity(hists);
	plotsuper(hists,colors,line,taglist,leghead,cname,"",1);
	cname = path+"costwqUnity";
	gethists(hists,taglist,"costwqHist",f);
	scaleToUnity(hists);
	plotsuper(hists,colors,line,taglist,leghead,cname,"",1);
	cname = path+"qcostUnity";
	scaleToUnity(hists);
        gethists(hists,taglist,"qcostHist",f);
        plotsuper(hists,colors,line,taglist,leghead,cname,"",1);


}


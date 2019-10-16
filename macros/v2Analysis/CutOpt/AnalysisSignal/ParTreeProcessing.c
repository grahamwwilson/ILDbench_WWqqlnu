//#include "TROOT.h"
//
#ifndef PARTREE
#define PARTREE

#include "TH1D.h"
#include "TH2D.h"
#include "ROOT/TThreadedObject.hxx"
//#include "ROOT/Math/GenVector/LorentzVector.h"
#include "Math/GenVector/LorentzVector.h"

//#include "ROOT/TTreeProcessorMT.hxx"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include <vector>
#include "TFile.h"
#include "histset.c"
#include "myselector.C"

#include <iostream>
#ifdef __MAKECINT__
#pragma link C++ class std::string+;
#endif
int main(int argc, char *argv[])
{

   //set nthreads from first input argument
   int nthreads = std::atoi (argv[1]);

  //set treename to read from second input argument
  std::string treename(argv[2]);

  //set the data tag from 3rd input argument
  //always need a tag, if you dont want this "" should work
  std::string tag(argv[3]);

  //set outputfilename in 4th input argument
  std::string ofilename(argv[4]);

  //set outputfileOption in 5th argument .. either recreate or udpate
  std::string ofileoption(argv[5]);

  //argv6 pem --- argv7 pep --- argv8 ilumi
  double pem = std::stod(std::string(argv[6]));
  double pep = std::stod(std::string(argv[7]));
  double ilumi = std::stod(std::string(argv[8]));

   // First enable implicit multi-threading globally, so that the implicit parallelisation is on.
   // The parameter of the call specifies the number of threads to use.
//   ROOT::EnableImplicitMT(nthreads);


   //load up the list of files to be processed
   //all the remaining input arguments are files to be added to the TChain
   //
   TChain *tc = new TChain("tree");
   std::vector<std::string_view> ifilelist{};
   for(int i=9; i<argc; i++){
	ifilelist.push_back(std::string_view(argv[i]));
	tc->Add(std::string(argv[i]).c_str());

	
   }
 //extract number of events for each pol 
 TFile* ofile = new TFile( ofilename.c_str(), ofileoption.c_str());	
   //Create our ThreadedHistograms and Analysis Class
   histset h( ofile,ofilename, tag);
  
  //make our parallel tree processor
  // ROOT::TTreeProcessorMT tp(ifilelist,treename.c_str());
   // Define the function that will process a subrange of the tree.
   // The function must receive only one parameter, a TTreeReader,
   // and it must be thread safe. To enforce the latter requirement,
   // TThreadedObject histograms will be used.
   //
 //  auto myFunction = [&](TTreeReader &myReader) {
	TTreeReader myReader(tc);
		


	int nLL,nLR,nRL,nRR;
	int entries = myReader.GetEntries(true);
//	myReader.SetEntry(entries);
	std::cout<<"entries" <<entries<<std::endl;


	//create our values to be read
	myselector s;
	
	//copy the tree onto the selector
	s.Init(myReader.GetTree());


	s.fReader.SetEntry(entries-1);
	//extra n values
	nLL = *(s.nLL);
	nLR = *(s.nLR);
	nRL = *(s.nRL);
	nRR = *(s.nRR);
	h.setWeightParams(ilumi, pem, pep, nLL, nLR, nRL, nRR);

      while (myReader.Next()) {
	//synchronize the threaded readed with private selector set of variables
	s.fReader.SetEntry(myReader.GetCurrentEntry());
	//analyze the current set of variables with hist set  class
	h.AnalyzeEntry(s); 
	
      }
//	h.printtables();
	h.normtables();
	h.printtables();
  // };
   // Launch the parallel processing of the tree

  // tp.Process(myFunction);
	
  //automatically do all merging and writing
//  h.WriteHist(ofilename, ofileoption);
	ofile->Write();	
   return 0;
}
#endif


//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Sep 25 03:13:55 2019 by ROOT version 6.08/06
// from TTree tree/Tree
// found on file: /afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/v2files/2f_Z_bhabhag/2f_Z_bhabhagfile.root
//////////////////////////////////////////////////////////

#ifndef myselector_h
#define myselector_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include <vector>
using namespace std;


class myselector : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Float_t> xsec = {fReader, "xsec"};
   TTreeReaderValue<Float_t> xsecerr = {fReader, "xsecerr"};
   TTreeReaderValue<Int_t> beampart1 = {fReader, "beampart1"};
   TTreeReaderValue<Int_t> beampart2 = {fReader, "beampart2"};
   TTreeReaderValue<Int_t> polarization1 = {fReader, "polarization1"};
   TTreeReaderValue<Int_t> polarization2 = {fReader, "polarization2"};
   TTreeReaderValue<Int_t> nLL = {fReader, "nLL"};
   TTreeReaderValue<Int_t> nRR = {fReader, "nRR"};
   TTreeReaderValue<Int_t> nLR = {fReader, "nLR"};
   TTreeReaderValue<Int_t> nRL = {fReader, "nRL"};
   TTreeReaderValue<Int_t> nevt = {fReader, "nevt"};
   TTreeReaderValue<Double_t> ycut = {fReader, "ycut"};
   TTreeReaderValue<Int_t> nPandoraTrks = {fReader, "nPandoraTrks"};
   TTreeReaderValue<Int_t> nPandoraPfos = {fReader, "nPandoraPfos"};
/*   TTreeReaderValue<Int_t> isMuon = {fReader, "genMuon"};
   TTreeReaderValue<Int_t> isTau = {fReader, "genTau"};
   TTreeReaderValue<Int_t> isElectron = {fReader, "genElectron"};
   TTreeReaderValue<Int_t> tauType = {fReader, "genTauType"};
   TTreeReaderArray<int> MCf_PDG = {fReader, "MCf_PDG"};
   TTreeReaderArray<double> MCf_Px = {fReader, "MCf_Px"};
   TTreeReaderArray<double> MCf_Py = {fReader, "MCf_Py"};
   TTreeReaderArray<double> MCf_Pz = {fReader, "MCf_Pz"};
   TTreeReaderArray<double> MCf_E = {fReader, "MCf_E"};
   TTreeReaderArray<double> MCfprodVtxX = {fReader, "MCfprodVtxX"};
   TTreeReaderArray<double> MCfprodVtxY = {fReader, "MCfprodVtxY"};
   TTreeReaderArray<double> MCfprodVtxZ = {fReader, "MCfprodVtxZ"};
   TTreeReaderArray<double> MCfendVtxX = {fReader, "MCfendVtxX"};
   TTreeReaderArray<double> MCfendVtxY = {fReader, "MCfendVtxY"};
   TTreeReaderArray<double> MCfendVtxZ = {fReader, "MCfendVtxZ"};
   TTreeReaderArray<int> genTauVisPDG = {fReader, "genTauVisPDG"};
   TTreeReaderArray<double> genTauVisPx = {fReader, "genTauVisPx"};
   TTreeReaderArray<double> genTauVisPy = {fReader, "genTauVisPy"};
   TTreeReaderArray<double> genTauVisPz = {fReader, "genTauVisPz"};
   TTreeReaderArray<double> genTauVisE = {fReader, "genTauVisE"};
   TTreeReaderValue<vector<bool>> genTauVisVtxisNOTParentEnd = {fReader, "genTauVisVtxisNOTParentEnd"};
   TTreeReaderArray<double> genTauVisX = {fReader, "genTauVisX"};
   TTreeReaderArray<double> genTauVisY = {fReader, "genTauVisY"};
   TTreeReaderArray<double> genTauVisZ = {fReader, "genTauVisZ"};
   TTreeReaderArray<int> genTauIPDG = {fReader, "genTauIPDG"};
   TTreeReaderArray<double> genTauIPx = {fReader, "genTauIPx"};
   TTreeReaderArray<double> genTauIPy = {fReader, "genTauIPy"};
   TTreeReaderArray<double> genTauIPz = {fReader, "genTauIPz"};  */
   TTreeReaderValue<Int_t> ntau0 = {fReader, "ntau0"};
   TTreeReaderArray<double> tauPx0 = {fReader, "tauPx0"};
   TTreeReaderArray<double> tauPy0 = {fReader, "tauPy0"};
   TTreeReaderArray<double> tauPz0 = {fReader, "tauPz0"};
   TTreeReaderArray<double> tauE0 = {fReader, "tauE0"};
   TTreeReaderArray<int> tauNTrks0 = {fReader, "tauNTrks0"};
   TTreeReaderArray<int> tauNPfos0 = {fReader, "tauNPfos0"};
   TTreeReaderValue<Double_t> candPx0 = {fReader, "candPx0"};
   TTreeReaderValue<Double_t> candPy0 = {fReader, "candPy0"};
   TTreeReaderValue<Double_t> candPz0 = {fReader, "candPz0"};
   TTreeReaderValue<Double_t> candE0 = {fReader, "candE0"};
   TTreeReaderValue<Int_t> candNTrks0 = {fReader, "candNTrks0"};
   TTreeReaderValue<Int_t> candNPfos0 = {fReader, "candNPfos0"};
   TTreeReaderArray<double> candNeuPx0 = {fReader, "candNeuPx0"};
   TTreeReaderArray<double> candNeuPy0 = {fReader, "candNeuPy0"};
   TTreeReaderArray<double> candNeuPz0 = {fReader, "candNeuPz0"};
   TTreeReaderArray<double> candNeuE0 = {fReader, "candNeuE0"};
   TTreeReaderArray<double> candTrkd00 = {fReader, "candTrkd00"};
   TTreeReaderArray<double> candTrkPhi0 = {fReader, "candTrkPhi0"};
   TTreeReaderArray<double> candTrkOm0 = {fReader, "candTrkOm0"};
   TTreeReaderArray<double> candTrkz00 = {fReader, "candTrkz00"};
   TTreeReaderArray<double> candTrktlam0 = {fReader, "candTrktlam0"};
   TTreeReaderArray<vector<float>> candTrkCov0 = {fReader, "candTrkCov0"};
   TTreeReaderValue<Int_t> njets0 = {fReader, "njets0"};
   TTreeReaderArray<int> remNtrk0 = {fReader, "remNtrk0"};
   TTreeReaderArray<int> remNpfo0 = {fReader, "remNpfo0"};
   TTreeReaderArray<double> remPx0 = {fReader, "remPx0"};
   TTreeReaderArray<double> remPy0 = {fReader, "remPy0"};
   TTreeReaderArray<double> remPz0 = {fReader, "remPz0"};
   TTreeReaderArray<double> remE0 = {fReader, "remE0"};
   TTreeReaderValue<Int_t> ntau1 = {fReader, "ntau1"};
   TTreeReaderArray<double> tauPx1 = {fReader, "tauPx1"};
   TTreeReaderArray<double> tauPy1 = {fReader, "tauPy1"};
   TTreeReaderArray<double> tauPz1 = {fReader, "tauPz1"};
   TTreeReaderArray<double> tauE1 = {fReader, "tauE1"};
   TTreeReaderArray<int> tauNTrks1 = {fReader, "tauNTrks1"};
   TTreeReaderArray<int> tauNPfos1 = {fReader, "tauNPfos1"};
   TTreeReaderValue<Double_t> candPx1 = {fReader, "candPx1"};
   TTreeReaderValue<Double_t> candPy1 = {fReader, "candPy1"};
   TTreeReaderValue<Double_t> candPz1 = {fReader, "candPz1"};
   TTreeReaderValue<Double_t> candE1 = {fReader, "candE1"};
   TTreeReaderValue<Int_t> candNTrks1 = {fReader, "candNTrks1"};
   TTreeReaderValue<Int_t> candNPfos1 = {fReader, "candNPfos1"};
   TTreeReaderArray<double> candNeuPx1 = {fReader, "candNeuPx1"};
   TTreeReaderArray<double> candNeuPy1 = {fReader, "candNeuPy1"};
   TTreeReaderArray<double> candNeuPz1 = {fReader, "candNeuPz1"};
   TTreeReaderArray<double> candNeuE1 = {fReader, "candNeuE1"};
   TTreeReaderArray<double> candTrkd01 = {fReader, "candTrkd01"};
   TTreeReaderArray<double> candTrkPhi1 = {fReader, "candTrkPhi1"};
   TTreeReaderArray<double> candTrkOm1 = {fReader, "candTrkOm1"};
   TTreeReaderArray<double> candTrkz01 = {fReader, "candTrkz01"};
   TTreeReaderArray<double> candTrktlam1 = {fReader, "candTrktlam1"};
   TTreeReaderArray<vector<float>> candTrkCov1 = {fReader, "candTrkCov1"};
   TTreeReaderValue<Int_t> njets1 = {fReader, "njets1"};
   TTreeReaderArray<int> remNtrk1 = {fReader, "remNtrk1"};
   TTreeReaderArray<int> remNpfo1 = {fReader, "remNpfo1"};
   TTreeReaderArray<double> remPx1 = {fReader, "remPx1"};
   TTreeReaderArray<double> remPy1 = {fReader, "remPy1"};
   TTreeReaderArray<double> remPz1 = {fReader, "remPz1"};
   TTreeReaderArray<double> remE1 = {fReader, "remE1"};
   TTreeReaderValue<Int_t> ntau2 = {fReader, "ntau2"};
   TTreeReaderArray<double> tauPx2 = {fReader, "tauPx2"};
   TTreeReaderArray<double> tauPy2 = {fReader, "tauPy2"};
   TTreeReaderArray<double> tauPz2 = {fReader, "tauPz2"};
   TTreeReaderArray<double> tauE2 = {fReader, "tauE2"};
   TTreeReaderArray<int> tauNTrks2 = {fReader, "tauNTrks2"};
   TTreeReaderArray<int> tauNPfos2 = {fReader, "tauNPfos2"};
   TTreeReaderValue<Double_t> candPx2 = {fReader, "candPx2"};
   TTreeReaderValue<Double_t> candPy2 = {fReader, "candPy2"};
   TTreeReaderValue<Double_t> candPz2 = {fReader, "candPz2"};
   TTreeReaderValue<Double_t> candE2 = {fReader, "candE2"};
   TTreeReaderValue<Int_t> candNTrks2 = {fReader, "candNTrks2"};
   TTreeReaderValue<Int_t> candNPfos2 = {fReader, "candNPfos2"};
   TTreeReaderArray<double> candNeuPx2 = {fReader, "candNeuPx2"};
   TTreeReaderArray<double> candNeuPy2 = {fReader, "candNeuPy2"};
   TTreeReaderArray<double> candNeuPz2 = {fReader, "candNeuPz2"};
   TTreeReaderArray<double> candNeuE2 = {fReader, "candNeuE2"};
   TTreeReaderArray<double> candTrkd02 = {fReader, "candTrkd02"};
   TTreeReaderArray<double> candTrkPhi2 = {fReader, "candTrkPhi2"};
   TTreeReaderArray<double> candTrkOm2 = {fReader, "candTrkOm2"};
   TTreeReaderArray<double> candTrkz02 = {fReader, "candTrkz02"};
   TTreeReaderArray<double> candTrktlam2 = {fReader, "candTrktlam2"};
   TTreeReaderArray<vector<float>> candTrkCov2 = {fReader, "candTrkCov2"};
   TTreeReaderValue<Int_t> njets2 = {fReader, "njets2"};
   TTreeReaderArray<int> remNtrk2 = {fReader, "remNtrk2"};
   TTreeReaderArray<int> remNpfo2 = {fReader, "remNpfo2"};
   TTreeReaderArray<double> remPx2 = {fReader, "remPx2"};
   TTreeReaderArray<double> remPy2 = {fReader, "remPy2"};
   TTreeReaderArray<double> remPz2 = {fReader, "remPz2"};
   TTreeReaderArray<double> remE2 = {fReader, "remE2"};
   TTreeReaderValue<Int_t> ntau3 = {fReader, "ntau3"};
   TTreeReaderArray<double> tauPx3 = {fReader, "tauPx3"};
   TTreeReaderArray<double> tauPy3 = {fReader, "tauPy3"};
   TTreeReaderArray<double> tauPz3 = {fReader, "tauPz3"};
   TTreeReaderArray<double> tauE3 = {fReader, "tauE3"};
   TTreeReaderArray<int> tauNTrks3 = {fReader, "tauNTrks3"};
   TTreeReaderArray<int> tauNPfos3 = {fReader, "tauNPfos3"};
   TTreeReaderValue<Double_t> candPx3 = {fReader, "candPx3"};
   TTreeReaderValue<Double_t> candPy3 = {fReader, "candPy3"};
   TTreeReaderValue<Double_t> candPz3 = {fReader, "candPz3"};
   TTreeReaderValue<Double_t> candE3 = {fReader, "candE3"};
   TTreeReaderValue<Int_t> candNTrks3 = {fReader, "candNTrks3"};
   TTreeReaderValue<Int_t> candNPfos3 = {fReader, "candNPfos3"};
   TTreeReaderArray<double> candNeuPx3 = {fReader, "candNeuPx3"};
   TTreeReaderArray<double> candNeuPy3 = {fReader, "candNeuPy3"};
   TTreeReaderArray<double> candNeuPz3 = {fReader, "candNeuPz3"};
   TTreeReaderArray<double> candNeuE3 = {fReader, "candNeuE3"};
   TTreeReaderArray<double> candTrkd03 = {fReader, "candTrkd03"};
   TTreeReaderArray<double> candTrkPhi3 = {fReader, "candTrkPhi3"};
   TTreeReaderArray<double> candTrkOm3 = {fReader, "candTrkOm3"};
   TTreeReaderArray<double> candTrkz03 = {fReader, "candTrkz03"};
   TTreeReaderArray<double> candTrktlam3 = {fReader, "candTrktlam3"};
   TTreeReaderArray<vector<float>> candTrkCov3 = {fReader, "candTrkCov3"};
   TTreeReaderValue<Int_t> njets3 = {fReader, "njets3"};
   TTreeReaderArray<int> remNtrk3 = {fReader, "remNtrk3"};
   TTreeReaderArray<int> remNpfo3 = {fReader, "remNpfo3"};
   TTreeReaderArray<double> remPx3 = {fReader, "remPx3"};
   TTreeReaderArray<double> remPy3 = {fReader, "remPy3"};
   TTreeReaderArray<double> remPz3 = {fReader, "remPz3"};
   TTreeReaderArray<double> remE3 = {fReader, "remE3"};
   TTreeReaderValue<Int_t> ntau4 = {fReader, "ntau4"};
   TTreeReaderArray<double> tauPx4 = {fReader, "tauPx4"};
   TTreeReaderArray<double> tauPy4 = {fReader, "tauPy4"};
   TTreeReaderArray<double> tauPz4 = {fReader, "tauPz4"};
   TTreeReaderArray<double> tauE4 = {fReader, "tauE4"};
   TTreeReaderArray<int> tauNTrks4 = {fReader, "tauNTrks4"};
   TTreeReaderArray<int> tauNPfos4 = {fReader, "tauNPfos4"};
   TTreeReaderValue<Double_t> candPx4 = {fReader, "candPx4"};
   TTreeReaderValue<Double_t> candPy4 = {fReader, "candPy4"};
   TTreeReaderValue<Double_t> candPz4 = {fReader, "candPz4"};
   TTreeReaderValue<Double_t> candE4 = {fReader, "candE4"};
   TTreeReaderValue<Int_t> candNTrks4 = {fReader, "candNTrks4"};
   TTreeReaderValue<Int_t> candNPfos4 = {fReader, "candNPfos4"};
   TTreeReaderArray<double> candNeuPx4 = {fReader, "candNeuPx4"};
   TTreeReaderArray<double> candNeuPy4 = {fReader, "candNeuPy4"};
   TTreeReaderArray<double> candNeuPz4 = {fReader, "candNeuPz4"};
   TTreeReaderArray<double> candNeuE4 = {fReader, "candNeuE4"};
   TTreeReaderArray<double> candTrkd04 = {fReader, "candTrkd04"};
   TTreeReaderArray<double> candTrkPhi4 = {fReader, "candTrkPhi4"};
   TTreeReaderArray<double> candTrkOm4 = {fReader, "candTrkOm4"};
   TTreeReaderArray<double> candTrkz04 = {fReader, "candTrkz04"};
   TTreeReaderArray<double> candTrktlam4 = {fReader, "candTrktlam4"};
   TTreeReaderArray<vector<float>> candTrkCov4 = {fReader, "candTrkCov4"};
   TTreeReaderValue<Int_t> njets4 = {fReader, "njets4"};
   TTreeReaderArray<int> remNtrk4 = {fReader, "remNtrk4"};
   TTreeReaderArray<int> remNpfo4 = {fReader, "remNpfo4"};
   TTreeReaderArray<double> remPx4 = {fReader, "remPx4"};
   TTreeReaderArray<double> remPy4 = {fReader, "remPy4"};
   TTreeReaderArray<double> remPz4 = {fReader, "remPz4"};
   TTreeReaderArray<double> remE4 = {fReader, "remE4"};


   myselector(TTree * /*tree*/ =0) { }
   virtual ~myselector() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

  // ClassDef(myselector,0);

};

#endif

#ifdef myselector_cxx
void myselector::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t myselector::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef myselector_cxx

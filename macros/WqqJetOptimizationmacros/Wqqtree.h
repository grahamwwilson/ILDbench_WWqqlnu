//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jun 27 18:56:22 2019 by ROOT version 5.34/38
// from TTree TauJets/TauJets
// found on file: WqqOptycut8S1file.root
//////////////////////////////////////////////////////////

#ifndef Wqqtree_h
#define Wqqtree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TLorentzVector.h>
#include <vector>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class Wqqtree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Double_t        xsec;
   Double_t        xsecerr;
   Int_t           nevt;
   Double_t        ycut;
   TLorentzVector  *TauJetsmcTau;
   vector<TLorentzVector> *TauJetstauTLV;
   Int_t           TauJetsnTaus;
   vector<int>     *TauJetstauTrkMult;
   vector<int>     *TauJetstauPfoMult;
   vector<double>  *TauJetstauCharge;
   vector<int>     *TauJetstauNOLTrks;
   vector<int>     *TauJetstauNOLPfos;
   vector<double>  *TauJetstauOLEFrac;
   vector<double>  *TauJetstauOLMFrac;
   vector<double>  *TauJetstauTrueFrac;
   vector<double>  *TauJetstauPsi;
   Double_t        TauJetsminTauPsi;
   Int_t           TauJetsindexOfMinTauPsi;
   Bool_t          TauJetsisMuon;
   Bool_t          TauJetsisTau;
   Bool_t          TauJetsisElectron;
   Int_t           TauJetstauType;
   Int_t           TauJetsmclepCharge;
   Int_t           TauJetsmclepTrkMult;
   Int_t           TauJetsmclepPfoMult;
   TLorentzVector  *TauJetsMCf0;
   Int_t           TauJetsMCf0_PDG;
   TLorentzVector  *TauJetsMCf1;
   Int_t           TauJetsMCf1_PDG;
   TLorentzVector  *TauJetsMCf2;
   Int_t           TauJetsMCf2_PDG;
   TLorentzVector  *TauJetsMCf3;
   Int_t           TauJetsMCf3_PDG;
   vector<TLorentzVector> *TauJetsMCTauVisibleDaughters;
   vector<int>     *TauJetsMCTauVisibleDaughters_pdg;
   vector<double>  *TauJetsMCTauVisibleDaughters_charge;
   vector<TLorentzVector> *TauJetsMCTauInvisibleDaughters;
   vector<int>     *TauJetsMCTauInvisibleDaughters_pdg;
   TLorentzVector  *mcl;
   TLorentzVector  *mcqq;
   vector<TLorentzVector> *RemainPFOsmcselremainpfos;
   vector<TLorentzVector> *RemainPFOseselremainpfos;
   Double_t        RemainPFOseselmatchmcsel;
   vector<vector<TLorentzVector> > *RemainPFOsJetOLtlv;
   Double_t        RemainJetsyMinus;
   Double_t        RemainJetsyPlus;
   vector<TLorentzVector> *RemainJetsJets;
   vector<vector<TLorentzVector> > *RemainJetsJetOLtlv;

   // List of branches
   TBranch        *b_xsec;   //!
   TBranch        *b_xsecerr;   //!
   TBranch        *b_nevt;   //!
   TBranch        *b_ycut;   //!
   TBranch        *b_TauJetsmcTau;   //!
   TBranch        *b_TauJetstauTLV;   //!
   TBranch        *b_TauJetsnTaus;   //!
   TBranch        *b_TauJetstauTrkMult;   //!
   TBranch        *b_TauJetstauPfoMult;   //!
   TBranch        *b_TauJetstauCharge;   //!
   TBranch        *b_TauJetstauNOLTrks;   //!
   TBranch        *b_TauJetstauNOLPfos;   //!
   TBranch        *b_TauJetstauOLEFrac;   //!
   TBranch        *b_TauJetstauOLMFrac;   //!
   TBranch        *b_TauJetstauTrueFrac;   //!
   TBranch        *b_TauJetstauPsi;   //!
   TBranch        *b_TauJetsminTauPsi;   //!
   TBranch        *b_TauJetsindexOfMinTauPsi;   //!
   TBranch        *b_TauJetsisMuon;   //!
   TBranch        *b_TauJetsisTau;   //!
   TBranch        *b_TauJetsisElectron;   //!
   TBranch        *b_TauJetstauType;   //!
   TBranch        *b_TauJetsmclepCharge;   //!
   TBranch        *b_TauJetsmclepTrkMult;   //!
   TBranch        *b_TauJetsmclepProMult;   //!
   TBranch        *b_TauJetsMCf0;   //!
   TBranch        *b_TauJetsMCf0_PDG;   //!
   TBranch        *b_TauJetsMCf1;   //!
   TBranch        *b_TauJetsMCf1_PDG;   //!
   TBranch        *b_TauJetsMCf2;   //!
   TBranch        *b_TauJetsMCf2_PDG;   //!
   TBranch        *b_TauJetsMCf3;   //!
   TBranch        *b_TauJetsMCf3_PDG;   //!
   TBranch        *b_TauJetsMCTauVisibleDaughters;   //!
   TBranch        *b_TauJetsMCTauVisibleDaughters_pdg;   //!
   TBranch        *b_TauJetsMCTauVisibleDaughters_charge;   //!
   TBranch        *b_TauJetsMCTauInvisibleDaughters;   //!
   TBranch        *b_TauJetsMCTauInvisibleDaughters_pdg;   //!
   TBranch        *b_mcl;   //!
   TBranch        *b_mcqq;   //!
   TBranch        *b_RemainPFOsmcselremainpfos;   //!
   TBranch        *b_RemainPFOseselremainpfos;   //!
   TBranch        *b_RemainPFOseselmatchmcsel;   //!
   TBranch        *b_RemainPFOsJetOLtlv;   //!
   TBranch        *b_RemainJetsyMinus;   //!
   TBranch        *b_RemainJetsyPlus;   //!
   TBranch        *b_RemainJetsJets;   //!
   TBranch        *b_RemainJetsJetOLtlv;   //!

   Wqqtree(std::string filename, std::string treename, TTree *tree=0);
   virtual ~Wqqtree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Wqqtree_cxx
Wqqtree::Wqqtree(std::string filename, std::string treename, TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(filename.c_str());
      if (!f || !f->IsOpen()) {
         f = new TFile(filename.c_str());
      }
      f->GetObject(treename.c_str(),tree);

   }
   Init(tree);
}

Wqqtree::~Wqqtree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Wqqtree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Wqqtree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Wqqtree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   TauJetsmcTau = 0;
   TauJetstauTLV = 0;
   TauJetstauTrkMult = 0;
   TauJetstauPfoMult = 0;
   TauJetstauCharge = 0;
   TauJetstauNOLTrks = 0;
   TauJetstauNOLPfos = 0;
   TauJetstauOLEFrac = 0;
   TauJetstauOLMFrac = 0;
   TauJetstauTrueFrac = 0;
   TauJetstauPsi = 0;
   TauJetsMCf0 = 0;
   TauJetsMCf1 = 0;
   TauJetsMCf2 = 0;
   TauJetsMCf3 = 0;
   TauJetsMCTauVisibleDaughters = 0;
   TauJetsMCTauVisibleDaughters_pdg = 0;
   TauJetsMCTauVisibleDaughters_charge = 0;
   TauJetsMCTauInvisibleDaughters = 0;
   TauJetsMCTauInvisibleDaughters_pdg = 0;
   mcl = 0;
   mcqq = 0;
   RemainPFOsmcselremainpfos = 0;
   RemainPFOseselremainpfos = 0;
   RemainPFOsJetOLtlv = 0;
   RemainJetsJets = 0;
   RemainJetsJetOLtlv = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("xsec", &xsec, &b_xsec);
   fChain->SetBranchAddress("xsecerr", &xsecerr, &b_xsecerr);
   fChain->SetBranchAddress("nevt", &nevt, &b_nevt);
   fChain->SetBranchAddress("ycut", &ycut, &b_ycut);
   fChain->SetBranchAddress("TauJetsmcTau", &TauJetsmcTau, &b_TauJetsmcTau);
   fChain->SetBranchAddress("TauJetstauTLV", &TauJetstauTLV, &b_TauJetstauTLV);
   fChain->SetBranchAddress("TauJetsnTaus", &TauJetsnTaus, &b_TauJetsnTaus);
   fChain->SetBranchAddress("TauJetstauTrkMult", &TauJetstauTrkMult, &b_TauJetstauTrkMult);
   fChain->SetBranchAddress("TauJetstauPfoMult", &TauJetstauPfoMult, &b_TauJetstauPfoMult);
   fChain->SetBranchAddress("TauJetstauCharge", &TauJetstauCharge, &b_TauJetstauCharge);
   fChain->SetBranchAddress("TauJetstauNOLTrks", &TauJetstauNOLTrks, &b_TauJetstauNOLTrks);
   fChain->SetBranchAddress("TauJetstauNOLPfos", &TauJetstauNOLPfos, &b_TauJetstauNOLPfos);
   fChain->SetBranchAddress("TauJetstauOLEFrac", &TauJetstauOLEFrac, &b_TauJetstauOLEFrac);
   fChain->SetBranchAddress("TauJetstauOLMFrac", &TauJetstauOLMFrac, &b_TauJetstauOLMFrac);
   fChain->SetBranchAddress("TauJetstauTrueFrac", &TauJetstauTrueFrac, &b_TauJetstauTrueFrac);
   fChain->SetBranchAddress("TauJetstauPsi", &TauJetstauPsi, &b_TauJetstauPsi);
   fChain->SetBranchAddress("TauJetsminTauPsi", &TauJetsminTauPsi, &b_TauJetsminTauPsi);
   fChain->SetBranchAddress("TauJetsindexOfMinTauPsi", &TauJetsindexOfMinTauPsi, &b_TauJetsindexOfMinTauPsi);
   fChain->SetBranchAddress("TauJetsisMuon", &TauJetsisMuon, &b_TauJetsisMuon);
   fChain->SetBranchAddress("TauJetsisTau", &TauJetsisTau, &b_TauJetsisTau);
   fChain->SetBranchAddress("TauJetsisElectron", &TauJetsisElectron, &b_TauJetsisElectron);
   fChain->SetBranchAddress("TauJetstauType", &TauJetstauType, &b_TauJetstauType);
   fChain->SetBranchAddress("TauJetsmclepCharge", &TauJetsmclepCharge, &b_TauJetsmclepCharge);
   fChain->SetBranchAddress("TauJetsmclepTrkMult", &TauJetsmclepTrkMult, &b_TauJetsmclepTrkMult);
   fChain->SetBranchAddress("TauJetsmclepPfoMult", &TauJetsmclepPfoMult, &b_TauJetsmclepProMult);
   fChain->SetBranchAddress("TauJetsMCf0", &TauJetsMCf0, &b_TauJetsMCf0);
   fChain->SetBranchAddress("TauJetsMCf0_PDG", &TauJetsMCf0_PDG, &b_TauJetsMCf0_PDG);
   fChain->SetBranchAddress("TauJetsMCf1", &TauJetsMCf1, &b_TauJetsMCf1);
   fChain->SetBranchAddress("TauJetsMCf1_PDG", &TauJetsMCf1_PDG, &b_TauJetsMCf1_PDG);
   fChain->SetBranchAddress("TauJetsMCf2", &TauJetsMCf2, &b_TauJetsMCf2);
   fChain->SetBranchAddress("TauJetsMCf2_PDG", &TauJetsMCf2_PDG, &b_TauJetsMCf2_PDG);
   fChain->SetBranchAddress("TauJetsMCf3", &TauJetsMCf3, &b_TauJetsMCf3);
   fChain->SetBranchAddress("TauJetsMCf3_PDG", &TauJetsMCf3_PDG, &b_TauJetsMCf3_PDG);
   fChain->SetBranchAddress("TauJetsMCTauVisibleDaughters", &TauJetsMCTauVisibleDaughters, &b_TauJetsMCTauVisibleDaughters);
   fChain->SetBranchAddress("TauJetsMCTauVisibleDaughters_pdg", &TauJetsMCTauVisibleDaughters_pdg, &b_TauJetsMCTauVisibleDaughters_pdg);
   fChain->SetBranchAddress("TauJetsMCTauVisibleDaughters_charge", &TauJetsMCTauVisibleDaughters_charge, &b_TauJetsMCTauVisibleDaughters_charge);
   fChain->SetBranchAddress("TauJetsMCTauInvisibleDaughters", &TauJetsMCTauInvisibleDaughters, &b_TauJetsMCTauInvisibleDaughters);
   fChain->SetBranchAddress("TauJetsMCTauInvisibleDaughters_pdg", &TauJetsMCTauInvisibleDaughters_pdg, &b_TauJetsMCTauInvisibleDaughters_pdg);
   fChain->SetBranchAddress("mcl", &mcl, &b_mcl);
   fChain->SetBranchAddress("mcqq", &mcqq, &b_mcqq);
   fChain->SetBranchAddress("RemainPFOsmcselremainpfos", &RemainPFOsmcselremainpfos, &b_RemainPFOsmcselremainpfos);
   fChain->SetBranchAddress("RemainPFOseselremainpfos", &RemainPFOseselremainpfos, &b_RemainPFOseselremainpfos);
   fChain->SetBranchAddress("RemainPFOseselmatchmcsel", &RemainPFOseselmatchmcsel, &b_RemainPFOseselmatchmcsel);
   fChain->SetBranchAddress("RemainPFOsJetOLtlv", &RemainPFOsJetOLtlv, &b_RemainPFOsJetOLtlv);
   fChain->SetBranchAddress("RemainJetsyMinus", &RemainJetsyMinus, &b_RemainJetsyMinus);
   fChain->SetBranchAddress("RemainJetsyPlus", &RemainJetsyPlus, &b_RemainJetsyPlus);
   fChain->SetBranchAddress("RemainJetsJets", &RemainJetsJets, &b_RemainJetsJets);
   fChain->SetBranchAddress("RemainJetsJetOLtlv", &RemainJetsJetOLtlv, &b_RemainJetsJetOLtlv);
   Notify();
}

Bool_t Wqqtree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Wqqtree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Wqqtree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Wqqtree_cxx

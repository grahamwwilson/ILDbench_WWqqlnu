//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Oct 15 13:10:54 2019 by ROOT version 6.18/04
// from TTree tree/Tree
// found on file: 4f_WW_V5.root
//////////////////////////////////////////////////////////

#ifndef MyClass_h
#define MyClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"

class MyClass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         xsec;
   Float_t         xsecerr;
   Int_t           beampart1;
   Int_t           beampart2;
   Int_t           polarization1;
   Int_t           polarization2;
   Int_t           nLL;
   Int_t           nRR;
   Int_t           nLR;
   Int_t           nRL;
   Int_t           nevt;
   Double_t        ycut;
   Int_t           nPandoraTrks;
   Int_t           nPandoraPfos;
   vector<int>     *wwlike;
   Int_t           isMuon;
   Int_t           isTau;
   Int_t           isElectron;
   Int_t           TauType;
   vector<int>     *MCf_PDG;
   vector<double>  *MCf_Px;
   vector<double>  *MCf_Py;
   vector<double>  *MCf_Pz;
   vector<double>  *MCf_E;
   vector<double>  *MCfprodVtxX;
   vector<double>  *MCfprodVtxY;
   vector<double>  *MCfprodVtxZ;
   vector<double>  *MCfendVtxX;
   vector<double>  *MCfendVtxY;
   vector<double>  *MCfendVtxZ;
   vector<int>     *genTauVisPDG;
   vector<double>  *genTauVisPx;
   vector<double>  *genTauVisPy;
   vector<double>  *genTauVisPz;
   vector<double>  *genTauVisE;
   vector<bool>    *genTauVisVtxisNOTParentEnd;
   vector<double>  *genTauVisX;
   vector<double>  *genTauVisY;
   vector<double>  *genTauVisZ;
   vector<int>     *genTauIPDG;
   vector<double>  *genTauIPx;
   vector<double>  *genTauIPy;
   vector<double>  *genTauIPz;
   Int_t           ntau0;
   vector<double>  *tauPx0;
   vector<double>  *tauPy0;
   vector<double>  *tauPz0;
   vector<double>  *tauE0;
   vector<int>     *tauNTrks0;
   vector<int>     *tauNPfos0;
   Double_t        candPx0;
   Double_t        candPy0;
   Double_t        candPz0;
   Double_t        candE0;
   Int_t           candNTrks0;
   Int_t           candNPfos0;
   vector<double>  *candNeuPx0;
   vector<double>  *candNeuPy0;
   vector<double>  *candNeuPz0;
   vector<double>  *candNeuE0;
   vector<double>  *candTrkd00;
   vector<double>  *candTrkPhi0;
   vector<double>  *candTrkOm0;
   vector<double>  *candTrkz00;
   vector<double>  *candTrktlam0;
   vector<vector<float> > *candTrkCov0;
   Int_t           njets0;
   vector<int>     *remNtrk0;
   vector<int>     *remNpfo0;
   vector<double>  *remPx0;
   vector<double>  *remPy0;
   vector<double>  *remPz0;
   vector<double>  *remE0;
   vector<double>  *qqPx0;
   vector<double>  *qqPy0;
   vector<double>  *qqPz0;
   vector<double>  *qqE0;
   vector<double>  *lPx0;
   vector<double>  *lPy0;
   vector<double>  *lPz0;
   vector<double>  *lE0;
   vector<double>  *lq0;
   Double_t        nuPzISR0;
   Double_t        gEISR0;
   Double_t        nuPx0;
   Double_t        nuPy0;
   Double_t        nuPz0;
   Double_t        nuE0;
   Double_t        gPx0;
   Double_t        gPy0;
   Double_t        gPz0;
   Double_t        gE0;
   Double_t        qqfitMass0;
   Double_t        lnufitMass0;
   Double_t        fitprob0;
   Double_t        chi20;
   Int_t           ntau1;
   vector<double>  *tauPx1;
   vector<double>  *tauPy1;
   vector<double>  *tauPz1;
   vector<double>  *tauE1;
   vector<int>     *tauNTrks1;
   vector<int>     *tauNPfos1;
   Double_t        candPx1;
   Double_t        candPy1;
   Double_t        candPz1;
   Double_t        candE1;
   Int_t           candNTrks1;
   Int_t           candNPfos1;
   vector<double>  *candNeuPx1;
   vector<double>  *candNeuPy1;
   vector<double>  *candNeuPz1;
   vector<double>  *candNeuE1;
   vector<double>  *candTrkd01;
   vector<double>  *candTrkPhi1;
   vector<double>  *candTrkOm1;
   vector<double>  *candTrkz01;
   vector<double>  *candTrktlam1;
   vector<vector<float> > *candTrkCov1;
   Int_t           njets1;
   vector<int>     *remNtrk1;
   vector<int>     *remNpfo1;
   vector<double>  *remPx1;
   vector<double>  *remPy1;
   vector<double>  *remPz1;
   vector<double>  *remE1;
   vector<double>  *qqPx1;
   vector<double>  *qqPy1;
   vector<double>  *qqPz1;
   vector<double>  *qqE1;
   vector<double>  *lPx1;
   vector<double>  *lPy1;
   vector<double>  *lPz1;
   vector<double>  *lE1;
   vector<double>  *lq1;
   Double_t        nuPzISR1;
   Double_t        gEISR1;
   Double_t        nuPx1;
   Double_t        nuPy1;
   Double_t        nuPz1;
   Double_t        nuE1;
   Double_t        gPx1;
   Double_t        gPy1;
   Double_t        gPz1;
   Double_t        gE1;
   Double_t        qqfitMass1;
   Double_t        lnufitMass1;
   Double_t        fitprob1;
   Double_t        chi21;
   Int_t           ntau2;
   vector<double>  *tauPx2;
   vector<double>  *tauPy2;
   vector<double>  *tauPz2;
   vector<double>  *tauE2;
   vector<int>     *tauNTrks2;
   vector<int>     *tauNPfos2;
   Double_t        candPx2;
   Double_t        candPy2;
   Double_t        candPz2;
   Double_t        candE2;
   Int_t           candNTrks2;
   Int_t           candNPfos2;
   vector<double>  *candNeuPx2;
   vector<double>  *candNeuPy2;
   vector<double>  *candNeuPz2;
   vector<double>  *candNeuE2;
   vector<double>  *candTrkd02;
   vector<double>  *candTrkPhi2;
   vector<double>  *candTrkOm2;
   vector<double>  *candTrkz02;
   vector<double>  *candTrktlam2;
   vector<vector<float> > *candTrkCov2;
   Int_t           njets2;
   vector<int>     *remNtrk2;
   vector<int>     *remNpfo2;
   vector<double>  *remPx2;
   vector<double>  *remPy2;
   vector<double>  *remPz2;
   vector<double>  *remE2;
   vector<double>  *qqPx2;
   vector<double>  *qqPy2;
   vector<double>  *qqPz2;
   vector<double>  *qqE2;
   vector<double>  *lPx2;
   vector<double>  *lPy2;
   vector<double>  *lPz2;
   vector<double>  *lE2;
   vector<double>  *lq2;
   Double_t        nuPzISR2;
   Double_t        gEISR2;
   Double_t        nuPx2;
   Double_t        nuPy2;
   Double_t        nuPz2;
   Double_t        nuE2;
   Double_t        gPx2;
   Double_t        gPy2;
   Double_t        gPz2;
   Double_t        gE2;
   Double_t        qqfitMass2;
   Double_t        lnufitMass2;
   Double_t        fitprob2;
   Double_t        chi22;
   Int_t           ntau3;
   vector<double>  *tauPx3;
   vector<double>  *tauPy3;
   vector<double>  *tauPz3;
   vector<double>  *tauE3;
   vector<int>     *tauNTrks3;
   vector<int>     *tauNPfos3;
   Double_t        candPx3;
   Double_t        candPy3;
   Double_t        candPz3;
   Double_t        candE3;
   Int_t           candNTrks3;
   Int_t           candNPfos3;
   vector<double>  *candNeuPx3;
   vector<double>  *candNeuPy3;
   vector<double>  *candNeuPz3;
   vector<double>  *candNeuE3;
   vector<double>  *candTrkd03;
   vector<double>  *candTrkPhi3;
   vector<double>  *candTrkOm3;
   vector<double>  *candTrkz03;
   vector<double>  *candTrktlam3;
   vector<vector<float> > *candTrkCov3;
   Int_t           njets3;
   vector<int>     *remNtrk3;
   vector<int>     *remNpfo3;
   vector<double>  *remPx3;
   vector<double>  *remPy3;
   vector<double>  *remPz3;
   vector<double>  *remE3;
   vector<double>  *qqPx3;
   vector<double>  *qqPy3;
   vector<double>  *qqPz3;
   vector<double>  *qqE3;
   vector<double>  *lPx3;
   vector<double>  *lPy3;
   vector<double>  *lPz3;
   vector<double>  *lE3;
   vector<double>  *lq3;
   Double_t        nuPzISR3;
   Double_t        gEISR3;
   Double_t        nuPx3;
   Double_t        nuPy3;
   Double_t        nuPz3;
   Double_t        nuE3;
   Double_t        gPx3;
   Double_t        gPy3;
   Double_t        gPz3;
   Double_t        gE3;
   Double_t        qqfitMass3;
   Double_t        lnufitMass3;
   Double_t        fitprob3;
   Double_t        chi23;
   Int_t           ntau4;
   vector<double>  *tauPx4;
   vector<double>  *tauPy4;
   vector<double>  *tauPz4;
   vector<double>  *tauE4;
   vector<int>     *tauNTrks4;
   vector<int>     *tauNPfos4;
   Double_t        candPx4;
   Double_t        candPy4;
   Double_t        candPz4;
   Double_t        candE4;
   Int_t           candNTrks4;
   Int_t           candNPfos4;
   vector<double>  *candNeuPx4;
   vector<double>  *candNeuPy4;
   vector<double>  *candNeuPz4;
   vector<double>  *candNeuE4;
   vector<double>  *candTrkd04;
   vector<double>  *candTrkPhi4;
   vector<double>  *candTrkOm4;
   vector<double>  *candTrkz04;
   vector<double>  *candTrktlam4;
   vector<vector<float> > *candTrkCov4;
   Int_t           njets4;
   vector<int>     *remNtrk4;
   vector<int>     *remNpfo4;
   vector<double>  *remPx4;
   vector<double>  *remPy4;
   vector<double>  *remPz4;
   vector<double>  *remE4;
   vector<double>  *qqPx4;
   vector<double>  *qqPy4;
   vector<double>  *qqPz4;
   vector<double>  *qqE4;
   vector<double>  *lPx4;
   vector<double>  *lPy4;
   vector<double>  *lPz4;
   vector<double>  *lE4;
   vector<double>  *lq4;
   Double_t        nuPzISR4;
   Double_t        gEISR4;
   Double_t        nuPx4;
   Double_t        nuPy4;
   Double_t        nuPz4;
   Double_t        nuE4;
   Double_t        gPx4;
   Double_t        gPy4;
   Double_t        gPz4;
   Double_t        gE4;
   Double_t        qqfitMass4;
   Double_t        lnufitMass4;
   Double_t        fitprob4;
   Double_t        chi24;

   // List of branches
   TBranch        *b_xsec;   //!
   TBranch        *b_xsecerr;   //!
   TBranch        *b_beampart1;   //!
   TBranch        *b_beampart2;   //!
   TBranch        *b_polarization1;   //!
   TBranch        *b_polarization2;   //!
   TBranch        *b_nLL;   //!
   TBranch        *b_nRR;   //!
   TBranch        *b_nLR;   //!
   TBranch        *b_nRL;   //!
   TBranch        *b_nevt;   //!
   TBranch        *b_ycut;   //!
   TBranch        *b_nPandoraTrks;   //!
   TBranch        *b_nPandoraPfos;   //!
   TBranch        *b_wwlike;   //!
   TBranch        *b_isMuon;   //!
   TBranch        *b_isTau;   //!
   TBranch        *b_isElectron;   //!
   TBranch        *b_TauType;   //!
   TBranch        *b_MCf_PDG;   //!
   TBranch        *b_MCf_Px;   //!
   TBranch        *b_MCf_Py;   //!
   TBranch        *b_MCf_Pz;   //!
   TBranch        *b_MCf_E;   //!
   TBranch        *b_MCfprodVtxX;   //!
   TBranch        *b_MCfprodVtxY;   //!
   TBranch        *b_MCfprodVtxZ;   //!
   TBranch        *b_MCfendVtxX;   //!
   TBranch        *b_MCfendVtxY;   //!
   TBranch        *b_MCfendVtxZ;   //!
   TBranch        *b_genTauVisPDG;   //!
   TBranch        *b_genTauVisPx;   //!
   TBranch        *b_genTauVisPy;   //!
   TBranch        *b_genTauVisPz;   //!
   TBranch        *b_genTauVisE;   //!
   TBranch        *b_genTauVisVtxisNOTParentEnd;   //!
   TBranch        *b_genTauVisX;   //!
   TBranch        *b_genTauVisY;   //!
   TBranch        *b_genTauVisZ;   //!
   TBranch        *b_genTauIPDG;   //!
   TBranch        *b_genTauIPx;   //!
   TBranch        *b_genTauIPy;   //!
   TBranch        *b_genTauIPz;   //!
   TBranch        *b_ntau0;   //!
   TBranch        *b_tauPx0;   //!
   TBranch        *b_tauPy0;   //!
   TBranch        *b_tauPz0;   //!
   TBranch        *b_tauE0;   //!
   TBranch        *b_tauNTrks0;   //!
   TBranch        *b_tauNPfos0;   //!
   TBranch        *b_candPx0;   //!
   TBranch        *b_candPy0;   //!
   TBranch        *b_candPz0;   //!
   TBranch        *b_candE0;   //!
   TBranch        *b_candNTrks0;   //!
   TBranch        *b_candNPfos0;   //!
   TBranch        *b_candNeuPx0;   //!
   TBranch        *b_candNeuPy0;   //!
   TBranch        *b_candNeuPz0;   //!
   TBranch        *b_candNeuE0;   //!
   TBranch        *b_candTrkd00;   //!
   TBranch        *b_candTrkPhi0;   //!
   TBranch        *b_candTrkOm0;   //!
   TBranch        *b_candTrkz00;   //!
   TBranch        *b_candTrktlam0;   //!
   TBranch        *b_candTrkCov0;   //!
   TBranch        *b_njets0;   //!
   TBranch        *b_remNtrk0;   //!
   TBranch        *b_remNpfo0;   //!
   TBranch        *b_remPx0;   //!
   TBranch        *b_remPy0;   //!
   TBranch        *b_remPz0;   //!
   TBranch        *b_remE0;   //!
   TBranch        *b_qqPx0;   //!
   TBranch        *b_qqPy0;   //!
   TBranch        *b_qqPz0;   //!
   TBranch        *b_qqE0;   //!
   TBranch        *b_lPx0;   //!
   TBranch        *b_lPy0;   //!
   TBranch        *b_lPz0;   //!
   TBranch        *b_lE0;   //!
   TBranch        *b_lq0;   //!
   TBranch        *b_nuPzISR0;   //!
   TBranch        *b_gEISR0;   //!
   TBranch        *b_nuPx0;   //!
   TBranch        *b_nuPy0;   //!
   TBranch        *b_nuPz0;   //!
   TBranch        *b_nuE0;   //!
   TBranch        *b_gPx0;   //!
   TBranch        *b_gPy0;   //!
   TBranch        *b_gPz0;   //!
   TBranch        *b_gE0;   //!
   TBranch        *b_qqfitMass0;   //!
   TBranch        *b_lnufitMass0;   //!
   TBranch        *b_fitprob0;   //!
   TBranch        *b_chi20;   //!
   TBranch        *b_ntau1;   //!
   TBranch        *b_tauPx1;   //!
   TBranch        *b_tauPy1;   //!
   TBranch        *b_tauPz1;   //!
   TBranch        *b_tauE1;   //!
   TBranch        *b_tauNTrks1;   //!
   TBranch        *b_tauNPfos1;   //!
   TBranch        *b_candPx1;   //!
   TBranch        *b_candPy1;   //!
   TBranch        *b_candPz1;   //!
   TBranch        *b_candE1;   //!
   TBranch        *b_candNTrks1;   //!
   TBranch        *b_candNPfos1;   //!
   TBranch        *b_candNeuPx1;   //!
   TBranch        *b_candNeuPy1;   //!
   TBranch        *b_candNeuPz1;   //!
   TBranch        *b_candNeuE1;   //!
   TBranch        *b_candTrkd01;   //!
   TBranch        *b_candTrkPhi1;   //!
   TBranch        *b_candTrkOm1;   //!
   TBranch        *b_candTrkz01;   //!
   TBranch        *b_candTrktlam1;   //!
   TBranch        *b_candTrkCov1;   //!
   TBranch        *b_njets1;   //!
   TBranch        *b_remNtrk1;   //!
   TBranch        *b_remNpfo1;   //!
   TBranch        *b_remPx1;   //!
   TBranch        *b_remPy1;   //!
   TBranch        *b_remPz1;   //!
   TBranch        *b_remE1;   //!
   TBranch        *b_qqPx1;   //!
   TBranch        *b_qqPy1;   //!
   TBranch        *b_qqPz1;   //!
   TBranch        *b_qqE1;   //!
   TBranch        *b_lPx1;   //!
   TBranch        *b_lPy1;   //!
   TBranch        *b_lPz1;   //!
   TBranch        *b_lE1;   //!
   TBranch        *b_lq1;   //!
   TBranch        *b_nuPzISR1;   //!
   TBranch        *b_gEISR1;   //!
   TBranch        *b_nuPx1;   //!
   TBranch        *b_nuPy1;   //!
   TBranch        *b_nuPz1;   //!
   TBranch        *b_nuE1;   //!
   TBranch        *b_gPx1;   //!
   TBranch        *b_gPy1;   //!
   TBranch        *b_gPz1;   //!
   TBranch        *b_gE1;   //!
   TBranch        *b_qqfitMass1;   //!
   TBranch        *b_lnufitMass1;   //!
   TBranch        *b_fitprob1;   //!
   TBranch        *b_chi21;   //!
   TBranch        *b_ntau2;   //!
   TBranch        *b_tauPx2;   //!
   TBranch        *b_tauPy2;   //!
   TBranch        *b_tauPz2;   //!
   TBranch        *b_tauE2;   //!
   TBranch        *b_tauNTrks2;   //!
   TBranch        *b_tauNPfos2;   //!
   TBranch        *b_candPx2;   //!
   TBranch        *b_candPy2;   //!
   TBranch        *b_candPz2;   //!
   TBranch        *b_candE2;   //!
   TBranch        *b_candNTrks2;   //!
   TBranch        *b_candNPfos2;   //!
   TBranch        *b_candNeuPx2;   //!
   TBranch        *b_candNeuPy2;   //!
   TBranch        *b_candNeuPz2;   //!
   TBranch        *b_candNeuE2;   //!
   TBranch        *b_candTrkd02;   //!
   TBranch        *b_candTrkPhi2;   //!
   TBranch        *b_candTrkOm2;   //!
   TBranch        *b_candTrkz02;   //!
   TBranch        *b_candTrktlam2;   //!
   TBranch        *b_candTrkCov2;   //!
   TBranch        *b_njets2;   //!
   TBranch        *b_remNtrk2;   //!
   TBranch        *b_remNpfo2;   //!
   TBranch        *b_remPx2;   //!
   TBranch        *b_remPy2;   //!
   TBranch        *b_remPz2;   //!
   TBranch        *b_remE2;   //!
   TBranch        *b_qqPx2;   //!
   TBranch        *b_qqPy2;   //!
   TBranch        *b_qqPz2;   //!
   TBranch        *b_qqE2;   //!
   TBranch        *b_lPx2;   //!
   TBranch        *b_lPy2;   //!
   TBranch        *b_lPz2;   //!
   TBranch        *b_lE2;   //!
   TBranch        *b_lq2;   //!
   TBranch        *b_nuPzISR2;   //!
   TBranch        *b_gEISR2;   //!
   TBranch        *b_nuPx2;   //!
   TBranch        *b_nuPy2;   //!
   TBranch        *b_nuPz2;   //!
   TBranch        *b_nuE2;   //!
   TBranch        *b_gPx2;   //!
   TBranch        *b_gPy2;   //!
   TBranch        *b_gPz2;   //!
   TBranch        *b_gE2;   //!
   TBranch        *b_qqfitMass2;   //!
   TBranch        *b_lnufitMass2;   //!
   TBranch        *b_fitprob2;   //!
   TBranch        *b_chi22;   //!
   TBranch        *b_ntau3;   //!
   TBranch        *b_tauPx3;   //!
   TBranch        *b_tauPy3;   //!
   TBranch        *b_tauPz3;   //!
   TBranch        *b_tauE3;   //!
   TBranch        *b_tauNTrks3;   //!
   TBranch        *b_tauNPfos3;   //!
   TBranch        *b_candPx3;   //!
   TBranch        *b_candPy3;   //!
   TBranch        *b_candPz3;   //!
   TBranch        *b_candE3;   //!
   TBranch        *b_candNTrks3;   //!
   TBranch        *b_candNPfos3;   //!
   TBranch        *b_candNeuPx3;   //!
   TBranch        *b_candNeuPy3;   //!
   TBranch        *b_candNeuPz3;   //!
   TBranch        *b_candNeuE3;   //!
   TBranch        *b_candTrkd03;   //!
   TBranch        *b_candTrkPhi3;   //!
   TBranch        *b_candTrkOm3;   //!
   TBranch        *b_candTrkz03;   //!
   TBranch        *b_candTrktlam3;   //!
   TBranch        *b_candTrkCov3;   //!
   TBranch        *b_njets3;   //!
   TBranch        *b_remNtrk3;   //!
   TBranch        *b_remNpfo3;   //!
   TBranch        *b_remPx3;   //!
   TBranch        *b_remPy3;   //!
   TBranch        *b_remPz3;   //!
   TBranch        *b_remE3;   //!
   TBranch        *b_qqPx3;   //!
   TBranch        *b_qqPy3;   //!
   TBranch        *b_qqPz3;   //!
   TBranch        *b_qqE3;   //!
   TBranch        *b_lPx3;   //!
   TBranch        *b_lPy3;   //!
   TBranch        *b_lPz3;   //!
   TBranch        *b_lE3;   //!
   TBranch        *b_lq3;   //!
   TBranch        *b_nuPzISR3;   //!
   TBranch        *b_gEISR3;   //!
   TBranch        *b_nuPx3;   //!
   TBranch        *b_nuPy3;   //!
   TBranch        *b_nuPz3;   //!
   TBranch        *b_nuE3;   //!
   TBranch        *b_gPx3;   //!
   TBranch        *b_gPy3;   //!
   TBranch        *b_gPz3;   //!
   TBranch        *b_gE3;   //!
   TBranch        *b_qqfitMass3;   //!
   TBranch        *b_lnufitMass3;   //!
   TBranch        *b_fitprob3;   //!
   TBranch        *b_chi23;   //!
   TBranch        *b_ntau4;   //!
   TBranch        *b_tauPx4;   //!
   TBranch        *b_tauPy4;   //!
   TBranch        *b_tauPz4;   //!
   TBranch        *b_tauE4;   //!
   TBranch        *b_tauNTrks4;   //!
   TBranch        *b_tauNPfos4;   //!
   TBranch        *b_candPx4;   //!
   TBranch        *b_candPy4;   //!
   TBranch        *b_candPz4;   //!
   TBranch        *b_candE4;   //!
   TBranch        *b_candNTrks4;   //!
   TBranch        *b_candNPfos4;   //!
   TBranch        *b_candNeuPx4;   //!
   TBranch        *b_candNeuPy4;   //!
   TBranch        *b_candNeuPz4;   //!
   TBranch        *b_candNeuE4;   //!
   TBranch        *b_candTrkd04;   //!
   TBranch        *b_candTrkPhi4;   //!
   TBranch        *b_candTrkOm4;   //!
   TBranch        *b_candTrkz04;   //!
   TBranch        *b_candTrktlam4;   //!
   TBranch        *b_candTrkCov4;   //!
   TBranch        *b_njets4;   //!
   TBranch        *b_remNtrk4;   //!
   TBranch        *b_remNpfo4;   //!
   TBranch        *b_remPx4;   //!
   TBranch        *b_remPy4;   //!
   TBranch        *b_remPz4;   //!
   TBranch        *b_remE4;   //!
   TBranch        *b_qqPx4;   //!
   TBranch        *b_qqPy4;   //!
   TBranch        *b_qqPz4;   //!
   TBranch        *b_qqE4;   //!
   TBranch        *b_lPx4;   //!
   TBranch        *b_lPy4;   //!
   TBranch        *b_lPz4;   //!
   TBranch        *b_lE4;   //!
   TBranch        *b_lq4;   //!
   TBranch        *b_nuPzISR4;   //!
   TBranch        *b_gEISR4;   //!
   TBranch        *b_nuPx4;   //!
   TBranch        *b_nuPy4;   //!
   TBranch        *b_nuPz4;   //!
   TBranch        *b_nuE4;   //!
   TBranch        *b_gPx4;   //!
   TBranch        *b_gPy4;   //!
   TBranch        *b_gPz4;   //!
   TBranch        *b_gE4;   //!
   TBranch        *b_qqfitMass4;   //!
   TBranch        *b_lnufitMass4;   //!
   TBranch        *b_fitprob4;   //!
   TBranch        *b_chi24;   //!

   MyClass(TTree *tree=0);
   virtual ~MyClass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MyClass_cxx
MyClass::MyClass(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("4f_WW_V5.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("4f_WW_V5.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

MyClass::~MyClass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MyClass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MyClass::LoadTree(Long64_t entry)
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

void MyClass::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   wwlike = 0;
   MCf_PDG = 0;
   MCf_Px = 0;
   MCf_Py = 0;
   MCf_Pz = 0;
   MCf_E = 0;
   MCfprodVtxX = 0;
   MCfprodVtxY = 0;
   MCfprodVtxZ = 0;
   MCfendVtxX = 0;
   MCfendVtxY = 0;
   MCfendVtxZ = 0;
   genTauVisPDG = 0;
   genTauVisPx = 0;
   genTauVisPy = 0;
   genTauVisPz = 0;
   genTauVisE = 0;
   genTauVisVtxisNOTParentEnd = 0;
   genTauVisX = 0;
   genTauVisY = 0;
   genTauVisZ = 0;
   genTauIPDG = 0;
   genTauIPx = 0;
   genTauIPy = 0;
   genTauIPz = 0;
   tauPx0 = 0;
   tauPy0 = 0;
   tauPz0 = 0;
   tauE0 = 0;
   tauNTrks0 = 0;
   tauNPfos0 = 0;
   candNeuPx0 = 0;
   candNeuPy0 = 0;
   candNeuPz0 = 0;
   candNeuE0 = 0;
   candTrkd00 = 0;
   candTrkPhi0 = 0;
   candTrkOm0 = 0;
   candTrkz00 = 0;
   candTrktlam0 = 0;
   candTrkCov0 = 0;
   remNtrk0 = 0;
   remNpfo0 = 0;
   remPx0 = 0;
   remPy0 = 0;
   remPz0 = 0;
   remE0 = 0;
   qqPx0 = 0;
   qqPy0 = 0;
   qqPz0 = 0;
   qqE0 = 0;
   lPx0 = 0;
   lPy0 = 0;
   lPz0 = 0;
   lE0 = 0;
   lq0 = 0;
   tauPx1 = 0;
   tauPy1 = 0;
   tauPz1 = 0;
   tauE1 = 0;
   tauNTrks1 = 0;
   tauNPfos1 = 0;
   candNeuPx1 = 0;
   candNeuPy1 = 0;
   candNeuPz1 = 0;
   candNeuE1 = 0;
   candTrkd01 = 0;
   candTrkPhi1 = 0;
   candTrkOm1 = 0;
   candTrkz01 = 0;
   candTrktlam1 = 0;
   candTrkCov1 = 0;
   remNtrk1 = 0;
   remNpfo1 = 0;
   remPx1 = 0;
   remPy1 = 0;
   remPz1 = 0;
   remE1 = 0;
   qqPx1 = 0;
   qqPy1 = 0;
   qqPz1 = 0;
   qqE1 = 0;
   lPx1 = 0;
   lPy1 = 0;
   lPz1 = 0;
   lE1 = 0;
   lq1 = 0;
   tauPx2 = 0;
   tauPy2 = 0;
   tauPz2 = 0;
   tauE2 = 0;
   tauNTrks2 = 0;
   tauNPfos2 = 0;
   candNeuPx2 = 0;
   candNeuPy2 = 0;
   candNeuPz2 = 0;
   candNeuE2 = 0;
   candTrkd02 = 0;
   candTrkPhi2 = 0;
   candTrkOm2 = 0;
   candTrkz02 = 0;
   candTrktlam2 = 0;
   candTrkCov2 = 0;
   remNtrk2 = 0;
   remNpfo2 = 0;
   remPx2 = 0;
   remPy2 = 0;
   remPz2 = 0;
   remE2 = 0;
   qqPx2 = 0;
   qqPy2 = 0;
   qqPz2 = 0;
   qqE2 = 0;
   lPx2 = 0;
   lPy2 = 0;
   lPz2 = 0;
   lE2 = 0;
   lq2 = 0;
   tauPx3 = 0;
   tauPy3 = 0;
   tauPz3 = 0;
   tauE3 = 0;
   tauNTrks3 = 0;
   tauNPfos3 = 0;
   candNeuPx3 = 0;
   candNeuPy3 = 0;
   candNeuPz3 = 0;
   candNeuE3 = 0;
   candTrkd03 = 0;
   candTrkPhi3 = 0;
   candTrkOm3 = 0;
   candTrkz03 = 0;
   candTrktlam3 = 0;
   candTrkCov3 = 0;
   remNtrk3 = 0;
   remNpfo3 = 0;
   remPx3 = 0;
   remPy3 = 0;
   remPz3 = 0;
   remE3 = 0;
   qqPx3 = 0;
   qqPy3 = 0;
   qqPz3 = 0;
   qqE3 = 0;
   lPx3 = 0;
   lPy3 = 0;
   lPz3 = 0;
   lE3 = 0;
   lq3 = 0;
   tauPx4 = 0;
   tauPy4 = 0;
   tauPz4 = 0;
   tauE4 = 0;
   tauNTrks4 = 0;
   tauNPfos4 = 0;
   candNeuPx4 = 0;
   candNeuPy4 = 0;
   candNeuPz4 = 0;
   candNeuE4 = 0;
   candTrkd04 = 0;
   candTrkPhi4 = 0;
   candTrkOm4 = 0;
   candTrkz04 = 0;
   candTrktlam4 = 0;
   candTrkCov4 = 0;
   remNtrk4 = 0;
   remNpfo4 = 0;
   remPx4 = 0;
   remPy4 = 0;
   remPz4 = 0;
   remE4 = 0;
   qqPx4 = 0;
   qqPy4 = 0;
   qqPz4 = 0;
   qqE4 = 0;
   lPx4 = 0;
   lPy4 = 0;
   lPz4 = 0;
   lE4 = 0;
   lq4 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("xsec", &xsec, &b_xsec);
   fChain->SetBranchAddress("xsecerr", &xsecerr, &b_xsecerr);
   fChain->SetBranchAddress("beampart1", &beampart1, &b_beampart1);
   fChain->SetBranchAddress("beampart2", &beampart2, &b_beampart2);
   fChain->SetBranchAddress("polarization1", &polarization1, &b_polarization1);
   fChain->SetBranchAddress("polarization2", &polarization2, &b_polarization2);
   fChain->SetBranchAddress("nLL", &nLL, &b_nLL);
   fChain->SetBranchAddress("nRR", &nRR, &b_nRR);
   fChain->SetBranchAddress("nLR", &nLR, &b_nLR);
   fChain->SetBranchAddress("nRL", &nRL, &b_nRL);
   fChain->SetBranchAddress("nevt", &nevt, &b_nevt);
   fChain->SetBranchAddress("ycut", &ycut, &b_ycut);
   fChain->SetBranchAddress("nPandoraTrks", &nPandoraTrks, &b_nPandoraTrks);
   fChain->SetBranchAddress("nPandoraPfos", &nPandoraPfos, &b_nPandoraPfos);
   fChain->SetBranchAddress("wwlike", &wwlike, &b_wwlike);
   fChain->SetBranchAddress("isMuon", &isMuon, &b_isMuon);
   fChain->SetBranchAddress("isTau", &isTau, &b_isTau);
   fChain->SetBranchAddress("isElectron", &isElectron, &b_isElectron);
   fChain->SetBranchAddress("TauType", &TauType, &b_TauType);
   fChain->SetBranchAddress("MCf_PDG", &MCf_PDG, &b_MCf_PDG);
   fChain->SetBranchAddress("MCf_Px", &MCf_Px, &b_MCf_Px);
   fChain->SetBranchAddress("MCf_Py", &MCf_Py, &b_MCf_Py);
   fChain->SetBranchAddress("MCf_Pz", &MCf_Pz, &b_MCf_Pz);
   fChain->SetBranchAddress("MCf_E", &MCf_E, &b_MCf_E);
   fChain->SetBranchAddress("MCfprodVtxX", &MCfprodVtxX, &b_MCfprodVtxX);
   fChain->SetBranchAddress("MCfprodVtxY", &MCfprodVtxY, &b_MCfprodVtxY);
   fChain->SetBranchAddress("MCfprodVtxZ", &MCfprodVtxZ, &b_MCfprodVtxZ);
   fChain->SetBranchAddress("MCfendVtxX", &MCfendVtxX, &b_MCfendVtxX);
   fChain->SetBranchAddress("MCfendVtxY", &MCfendVtxY, &b_MCfendVtxY);
   fChain->SetBranchAddress("MCfendVtxZ", &MCfendVtxZ, &b_MCfendVtxZ);
   fChain->SetBranchAddress("genTauVisPDG", &genTauVisPDG, &b_genTauVisPDG);
   fChain->SetBranchAddress("genTauVisPx", &genTauVisPx, &b_genTauVisPx);
   fChain->SetBranchAddress("genTauVisPy", &genTauVisPy, &b_genTauVisPy);
   fChain->SetBranchAddress("genTauVisPz", &genTauVisPz, &b_genTauVisPz);
   fChain->SetBranchAddress("genTauVisE", &genTauVisE, &b_genTauVisE);
   fChain->SetBranchAddress("genTauVisVtxisNOTParentEnd", &genTauVisVtxisNOTParentEnd, &b_genTauVisVtxisNOTParentEnd);
   fChain->SetBranchAddress("genTauVisX", &genTauVisX, &b_genTauVisX);
   fChain->SetBranchAddress("genTauVisY", &genTauVisY, &b_genTauVisY);
   fChain->SetBranchAddress("genTauVisZ", &genTauVisZ, &b_genTauVisZ);
   fChain->SetBranchAddress("genTauIPDG", &genTauIPDG, &b_genTauIPDG);
   fChain->SetBranchAddress("genTauIPx", &genTauIPx, &b_genTauIPx);
   fChain->SetBranchAddress("genTauIPy", &genTauIPy, &b_genTauIPy);
   fChain->SetBranchAddress("genTauIPz", &genTauIPz, &b_genTauIPz);
   fChain->SetBranchAddress("ntau0", &ntau0, &b_ntau0);
   fChain->SetBranchAddress("tauPx0", &tauPx0, &b_tauPx0);
   fChain->SetBranchAddress("tauPy0", &tauPy0, &b_tauPy0);
   fChain->SetBranchAddress("tauPz0", &tauPz0, &b_tauPz0);
   fChain->SetBranchAddress("tauE0", &tauE0, &b_tauE0);
   fChain->SetBranchAddress("tauNTrks0", &tauNTrks0, &b_tauNTrks0);
   fChain->SetBranchAddress("tauNPfos0", &tauNPfos0, &b_tauNPfos0);
   fChain->SetBranchAddress("candPx0", &candPx0, &b_candPx0);
   fChain->SetBranchAddress("candPy0", &candPy0, &b_candPy0);
   fChain->SetBranchAddress("candPz0", &candPz0, &b_candPz0);
   fChain->SetBranchAddress("candE0", &candE0, &b_candE0);
   fChain->SetBranchAddress("candNTrks0", &candNTrks0, &b_candNTrks0);
   fChain->SetBranchAddress("candNPfos0", &candNPfos0, &b_candNPfos0);
   fChain->SetBranchAddress("candNeuPx0", &candNeuPx0, &b_candNeuPx0);
   fChain->SetBranchAddress("candNeuPy0", &candNeuPy0, &b_candNeuPy0);
   fChain->SetBranchAddress("candNeuPz0", &candNeuPz0, &b_candNeuPz0);
   fChain->SetBranchAddress("candNeuE0", &candNeuE0, &b_candNeuE0);
   fChain->SetBranchAddress("candTrkd00", &candTrkd00, &b_candTrkd00);
   fChain->SetBranchAddress("candTrkPhi0", &candTrkPhi0, &b_candTrkPhi0);
   fChain->SetBranchAddress("candTrkOm0", &candTrkOm0, &b_candTrkOm0);
   fChain->SetBranchAddress("candTrkz00", &candTrkz00, &b_candTrkz00);
   fChain->SetBranchAddress("candTrktlam0", &candTrktlam0, &b_candTrktlam0);
   fChain->SetBranchAddress("candTrkCov0", &candTrkCov0, &b_candTrkCov0);
   fChain->SetBranchAddress("njets0", &njets0, &b_njets0);
   fChain->SetBranchAddress("remNtrk0", &remNtrk0, &b_remNtrk0);
   fChain->SetBranchAddress("remNpfo0", &remNpfo0, &b_remNpfo0);
   fChain->SetBranchAddress("remPx0", &remPx0, &b_remPx0);
   fChain->SetBranchAddress("remPy0", &remPy0, &b_remPy0);
   fChain->SetBranchAddress("remPz0", &remPz0, &b_remPz0);
   fChain->SetBranchAddress("remE0", &remE0, &b_remE0);
   fChain->SetBranchAddress("qqPx0", &qqPx0, &b_qqPx0);
   fChain->SetBranchAddress("qqPy0", &qqPy0, &b_qqPy0);
   fChain->SetBranchAddress("qqPz0", &qqPz0, &b_qqPz0);
   fChain->SetBranchAddress("qqE0", &qqE0, &b_qqE0);
   fChain->SetBranchAddress("lPx0", &lPx0, &b_lPx0);
   fChain->SetBranchAddress("lPy0", &lPy0, &b_lPy0);
   fChain->SetBranchAddress("lPz0", &lPz0, &b_lPz0);
   fChain->SetBranchAddress("lE0", &lE0, &b_lE0);
   fChain->SetBranchAddress("lq0", &lq0, &b_lq0);
   fChain->SetBranchAddress("nuPzISR0", &nuPzISR0, &b_nuPzISR0);
   fChain->SetBranchAddress("gEISR0", &gEISR0, &b_gEISR0);
   fChain->SetBranchAddress("nuPx0", &nuPx0, &b_nuPx0);
   fChain->SetBranchAddress("nuPy0", &nuPy0, &b_nuPy0);
   fChain->SetBranchAddress("nuPz0", &nuPz0, &b_nuPz0);
   fChain->SetBranchAddress("nuE0", &nuE0, &b_nuE0);
   fChain->SetBranchAddress("gPx0", &gPx0, &b_gPx0);
   fChain->SetBranchAddress("gPy0", &gPy0, &b_gPy0);
   fChain->SetBranchAddress("gPz0", &gPz0, &b_gPz0);
   fChain->SetBranchAddress("gE0", &gE0, &b_gE0);
   fChain->SetBranchAddress("qqfitMass0", &qqfitMass0, &b_qqfitMass0);
   fChain->SetBranchAddress("lnufitMass0", &lnufitMass0, &b_lnufitMass0);
   fChain->SetBranchAddress("fitprob0", &fitprob0, &b_fitprob0);
   fChain->SetBranchAddress("chi20", &chi20, &b_chi20);
   fChain->SetBranchAddress("ntau1", &ntau1, &b_ntau1);
   fChain->SetBranchAddress("tauPx1", &tauPx1, &b_tauPx1);
   fChain->SetBranchAddress("tauPy1", &tauPy1, &b_tauPy1);
   fChain->SetBranchAddress("tauPz1", &tauPz1, &b_tauPz1);
   fChain->SetBranchAddress("tauE1", &tauE1, &b_tauE1);
   fChain->SetBranchAddress("tauNTrks1", &tauNTrks1, &b_tauNTrks1);
   fChain->SetBranchAddress("tauNPfos1", &tauNPfos1, &b_tauNPfos1);
   fChain->SetBranchAddress("candPx1", &candPx1, &b_candPx1);
   fChain->SetBranchAddress("candPy1", &candPy1, &b_candPy1);
   fChain->SetBranchAddress("candPz1", &candPz1, &b_candPz1);
   fChain->SetBranchAddress("candE1", &candE1, &b_candE1);
   fChain->SetBranchAddress("candNTrks1", &candNTrks1, &b_candNTrks1);
   fChain->SetBranchAddress("candNPfos1", &candNPfos1, &b_candNPfos1);
   fChain->SetBranchAddress("candNeuPx1", &candNeuPx1, &b_candNeuPx1);
   fChain->SetBranchAddress("candNeuPy1", &candNeuPy1, &b_candNeuPy1);
   fChain->SetBranchAddress("candNeuPz1", &candNeuPz1, &b_candNeuPz1);
   fChain->SetBranchAddress("candNeuE1", &candNeuE1, &b_candNeuE1);
   fChain->SetBranchAddress("candTrkd01", &candTrkd01, &b_candTrkd01);
   fChain->SetBranchAddress("candTrkPhi1", &candTrkPhi1, &b_candTrkPhi1);
   fChain->SetBranchAddress("candTrkOm1", &candTrkOm1, &b_candTrkOm1);
   fChain->SetBranchAddress("candTrkz01", &candTrkz01, &b_candTrkz01);
   fChain->SetBranchAddress("candTrktlam1", &candTrktlam1, &b_candTrktlam1);
   fChain->SetBranchAddress("candTrkCov1", &candTrkCov1, &b_candTrkCov1);
   fChain->SetBranchAddress("njets1", &njets1, &b_njets1);
   fChain->SetBranchAddress("remNtrk1", &remNtrk1, &b_remNtrk1);
   fChain->SetBranchAddress("remNpfo1", &remNpfo1, &b_remNpfo1);
   fChain->SetBranchAddress("remPx1", &remPx1, &b_remPx1);
   fChain->SetBranchAddress("remPy1", &remPy1, &b_remPy1);
   fChain->SetBranchAddress("remPz1", &remPz1, &b_remPz1);
   fChain->SetBranchAddress("remE1", &remE1, &b_remE1);
   fChain->SetBranchAddress("qqPx1", &qqPx1, &b_qqPx1);
   fChain->SetBranchAddress("qqPy1", &qqPy1, &b_qqPy1);
   fChain->SetBranchAddress("qqPz1", &qqPz1, &b_qqPz1);
   fChain->SetBranchAddress("qqE1", &qqE1, &b_qqE1);
   fChain->SetBranchAddress("lPx1", &lPx1, &b_lPx1);
   fChain->SetBranchAddress("lPy1", &lPy1, &b_lPy1);
   fChain->SetBranchAddress("lPz1", &lPz1, &b_lPz1);
   fChain->SetBranchAddress("lE1", &lE1, &b_lE1);
   fChain->SetBranchAddress("lq1", &lq1, &b_lq1);
   fChain->SetBranchAddress("nuPzISR1", &nuPzISR1, &b_nuPzISR1);
   fChain->SetBranchAddress("gEISR1", &gEISR1, &b_gEISR1);
   fChain->SetBranchAddress("nuPx1", &nuPx1, &b_nuPx1);
   fChain->SetBranchAddress("nuPy1", &nuPy1, &b_nuPy1);
   fChain->SetBranchAddress("nuPz1", &nuPz1, &b_nuPz1);
   fChain->SetBranchAddress("nuE1", &nuE1, &b_nuE1);
   fChain->SetBranchAddress("gPx1", &gPx1, &b_gPx1);
   fChain->SetBranchAddress("gPy1", &gPy1, &b_gPy1);
   fChain->SetBranchAddress("gPz1", &gPz1, &b_gPz1);
   fChain->SetBranchAddress("gE1", &gE1, &b_gE1);
   fChain->SetBranchAddress("qqfitMass1", &qqfitMass1, &b_qqfitMass1);
   fChain->SetBranchAddress("lnufitMass1", &lnufitMass1, &b_lnufitMass1);
   fChain->SetBranchAddress("fitprob1", &fitprob1, &b_fitprob1);
   fChain->SetBranchAddress("chi21", &chi21, &b_chi21);
   fChain->SetBranchAddress("ntau2", &ntau2, &b_ntau2);
   fChain->SetBranchAddress("tauPx2", &tauPx2, &b_tauPx2);
   fChain->SetBranchAddress("tauPy2", &tauPy2, &b_tauPy2);
   fChain->SetBranchAddress("tauPz2", &tauPz2, &b_tauPz2);
   fChain->SetBranchAddress("tauE2", &tauE2, &b_tauE2);
   fChain->SetBranchAddress("tauNTrks2", &tauNTrks2, &b_tauNTrks2);
   fChain->SetBranchAddress("tauNPfos2", &tauNPfos2, &b_tauNPfos2);
   fChain->SetBranchAddress("candPx2", &candPx2, &b_candPx2);
   fChain->SetBranchAddress("candPy2", &candPy2, &b_candPy2);
   fChain->SetBranchAddress("candPz2", &candPz2, &b_candPz2);
   fChain->SetBranchAddress("candE2", &candE2, &b_candE2);
   fChain->SetBranchAddress("candNTrks2", &candNTrks2, &b_candNTrks2);
   fChain->SetBranchAddress("candNPfos2", &candNPfos2, &b_candNPfos2);
   fChain->SetBranchAddress("candNeuPx2", &candNeuPx2, &b_candNeuPx2);
   fChain->SetBranchAddress("candNeuPy2", &candNeuPy2, &b_candNeuPy2);
   fChain->SetBranchAddress("candNeuPz2", &candNeuPz2, &b_candNeuPz2);
   fChain->SetBranchAddress("candNeuE2", &candNeuE2, &b_candNeuE2);
   fChain->SetBranchAddress("candTrkd02", &candTrkd02, &b_candTrkd02);
   fChain->SetBranchAddress("candTrkPhi2", &candTrkPhi2, &b_candTrkPhi2);
   fChain->SetBranchAddress("candTrkOm2", &candTrkOm2, &b_candTrkOm2);
   fChain->SetBranchAddress("candTrkz02", &candTrkz02, &b_candTrkz02);
   fChain->SetBranchAddress("candTrktlam2", &candTrktlam2, &b_candTrktlam2);
   fChain->SetBranchAddress("candTrkCov2", &candTrkCov2, &b_candTrkCov2);
   fChain->SetBranchAddress("njets2", &njets2, &b_njets2);
   fChain->SetBranchAddress("remNtrk2", &remNtrk2, &b_remNtrk2);
   fChain->SetBranchAddress("remNpfo2", &remNpfo2, &b_remNpfo2);
   fChain->SetBranchAddress("remPx2", &remPx2, &b_remPx2);
   fChain->SetBranchAddress("remPy2", &remPy2, &b_remPy2);
   fChain->SetBranchAddress("remPz2", &remPz2, &b_remPz2);
   fChain->SetBranchAddress("remE2", &remE2, &b_remE2);
   fChain->SetBranchAddress("qqPx2", &qqPx2, &b_qqPx2);
   fChain->SetBranchAddress("qqPy2", &qqPy2, &b_qqPy2);
   fChain->SetBranchAddress("qqPz2", &qqPz2, &b_qqPz2);
   fChain->SetBranchAddress("qqE2", &qqE2, &b_qqE2);
   fChain->SetBranchAddress("lPx2", &lPx2, &b_lPx2);
   fChain->SetBranchAddress("lPy2", &lPy2, &b_lPy2);
   fChain->SetBranchAddress("lPz2", &lPz2, &b_lPz2);
   fChain->SetBranchAddress("lE2", &lE2, &b_lE2);
   fChain->SetBranchAddress("lq2", &lq2, &b_lq2);
   fChain->SetBranchAddress("nuPzISR2", &nuPzISR2, &b_nuPzISR2);
   fChain->SetBranchAddress("gEISR2", &gEISR2, &b_gEISR2);
   fChain->SetBranchAddress("nuPx2", &nuPx2, &b_nuPx2);
   fChain->SetBranchAddress("nuPy2", &nuPy2, &b_nuPy2);
   fChain->SetBranchAddress("nuPz2", &nuPz2, &b_nuPz2);
   fChain->SetBranchAddress("nuE2", &nuE2, &b_nuE2);
   fChain->SetBranchAddress("gPx2", &gPx2, &b_gPx2);
   fChain->SetBranchAddress("gPy2", &gPy2, &b_gPy2);
   fChain->SetBranchAddress("gPz2", &gPz2, &b_gPz2);
   fChain->SetBranchAddress("gE2", &gE2, &b_gE2);
   fChain->SetBranchAddress("qqfitMass2", &qqfitMass2, &b_qqfitMass2);
   fChain->SetBranchAddress("lnufitMass2", &lnufitMass2, &b_lnufitMass2);
   fChain->SetBranchAddress("fitprob2", &fitprob2, &b_fitprob2);
   fChain->SetBranchAddress("chi22", &chi22, &b_chi22);
   fChain->SetBranchAddress("ntau3", &ntau3, &b_ntau3);
   fChain->SetBranchAddress("tauPx3", &tauPx3, &b_tauPx3);
   fChain->SetBranchAddress("tauPy3", &tauPy3, &b_tauPy3);
   fChain->SetBranchAddress("tauPz3", &tauPz3, &b_tauPz3);
   fChain->SetBranchAddress("tauE3", &tauE3, &b_tauE3);
   fChain->SetBranchAddress("tauNTrks3", &tauNTrks3, &b_tauNTrks3);
   fChain->SetBranchAddress("tauNPfos3", &tauNPfos3, &b_tauNPfos3);
   fChain->SetBranchAddress("candPx3", &candPx3, &b_candPx3);
   fChain->SetBranchAddress("candPy3", &candPy3, &b_candPy3);
   fChain->SetBranchAddress("candPz3", &candPz3, &b_candPz3);
   fChain->SetBranchAddress("candE3", &candE3, &b_candE3);
   fChain->SetBranchAddress("candNTrks3", &candNTrks3, &b_candNTrks3);
   fChain->SetBranchAddress("candNPfos3", &candNPfos3, &b_candNPfos3);
   fChain->SetBranchAddress("candNeuPx3", &candNeuPx3, &b_candNeuPx3);
   fChain->SetBranchAddress("candNeuPy3", &candNeuPy3, &b_candNeuPy3);
   fChain->SetBranchAddress("candNeuPz3", &candNeuPz3, &b_candNeuPz3);
   fChain->SetBranchAddress("candNeuE3", &candNeuE3, &b_candNeuE3);
   fChain->SetBranchAddress("candTrkd03", &candTrkd03, &b_candTrkd03);
   fChain->SetBranchAddress("candTrkPhi3", &candTrkPhi3, &b_candTrkPhi3);
   fChain->SetBranchAddress("candTrkOm3", &candTrkOm3, &b_candTrkOm3);
   fChain->SetBranchAddress("candTrkz03", &candTrkz03, &b_candTrkz03);
   fChain->SetBranchAddress("candTrktlam3", &candTrktlam3, &b_candTrktlam3);
   fChain->SetBranchAddress("candTrkCov3", &candTrkCov3, &b_candTrkCov3);
   fChain->SetBranchAddress("njets3", &njets3, &b_njets3);
   fChain->SetBranchAddress("remNtrk3", &remNtrk3, &b_remNtrk3);
   fChain->SetBranchAddress("remNpfo3", &remNpfo3, &b_remNpfo3);
   fChain->SetBranchAddress("remPx3", &remPx3, &b_remPx3);
   fChain->SetBranchAddress("remPy3", &remPy3, &b_remPy3);
   fChain->SetBranchAddress("remPz3", &remPz3, &b_remPz3);
   fChain->SetBranchAddress("remE3", &remE3, &b_remE3);
   fChain->SetBranchAddress("qqPx3", &qqPx3, &b_qqPx3);
   fChain->SetBranchAddress("qqPy3", &qqPy3, &b_qqPy3);
   fChain->SetBranchAddress("qqPz3", &qqPz3, &b_qqPz3);
   fChain->SetBranchAddress("qqE3", &qqE3, &b_qqE3);
   fChain->SetBranchAddress("lPx3", &lPx3, &b_lPx3);
   fChain->SetBranchAddress("lPy3", &lPy3, &b_lPy3);
   fChain->SetBranchAddress("lPz3", &lPz3, &b_lPz3);
   fChain->SetBranchAddress("lE3", &lE3, &b_lE3);
   fChain->SetBranchAddress("lq3", &lq3, &b_lq3);
   fChain->SetBranchAddress("nuPzISR3", &nuPzISR3, &b_nuPzISR3);
   fChain->SetBranchAddress("gEISR3", &gEISR3, &b_gEISR3);
   fChain->SetBranchAddress("nuPx3", &nuPx3, &b_nuPx3);
   fChain->SetBranchAddress("nuPy3", &nuPy3, &b_nuPy3);
   fChain->SetBranchAddress("nuPz3", &nuPz3, &b_nuPz3);
   fChain->SetBranchAddress("nuE3", &nuE3, &b_nuE3);
   fChain->SetBranchAddress("gPx3", &gPx3, &b_gPx3);
   fChain->SetBranchAddress("gPy3", &gPy3, &b_gPy3);
   fChain->SetBranchAddress("gPz3", &gPz3, &b_gPz3);
   fChain->SetBranchAddress("gE3", &gE3, &b_gE3);
   fChain->SetBranchAddress("qqfitMass3", &qqfitMass3, &b_qqfitMass3);
   fChain->SetBranchAddress("lnufitMass3", &lnufitMass3, &b_lnufitMass3);
   fChain->SetBranchAddress("fitprob3", &fitprob3, &b_fitprob3);
   fChain->SetBranchAddress("chi23", &chi23, &b_chi23);
   fChain->SetBranchAddress("ntau4", &ntau4, &b_ntau4);
   fChain->SetBranchAddress("tauPx4", &tauPx4, &b_tauPx4);
   fChain->SetBranchAddress("tauPy4", &tauPy4, &b_tauPy4);
   fChain->SetBranchAddress("tauPz4", &tauPz4, &b_tauPz4);
   fChain->SetBranchAddress("tauE4", &tauE4, &b_tauE4);
   fChain->SetBranchAddress("tauNTrks4", &tauNTrks4, &b_tauNTrks4);
   fChain->SetBranchAddress("tauNPfos4", &tauNPfos4, &b_tauNPfos4);
   fChain->SetBranchAddress("candPx4", &candPx4, &b_candPx4);
   fChain->SetBranchAddress("candPy4", &candPy4, &b_candPy4);
   fChain->SetBranchAddress("candPz4", &candPz4, &b_candPz4);
   fChain->SetBranchAddress("candE4", &candE4, &b_candE4);
   fChain->SetBranchAddress("candNTrks4", &candNTrks4, &b_candNTrks4);
   fChain->SetBranchAddress("candNPfos4", &candNPfos4, &b_candNPfos4);
   fChain->SetBranchAddress("candNeuPx4", &candNeuPx4, &b_candNeuPx4);
   fChain->SetBranchAddress("candNeuPy4", &candNeuPy4, &b_candNeuPy4);
   fChain->SetBranchAddress("candNeuPz4", &candNeuPz4, &b_candNeuPz4);
   fChain->SetBranchAddress("candNeuE4", &candNeuE4, &b_candNeuE4);
   fChain->SetBranchAddress("candTrkd04", &candTrkd04, &b_candTrkd04);
   fChain->SetBranchAddress("candTrkPhi4", &candTrkPhi4, &b_candTrkPhi4);
   fChain->SetBranchAddress("candTrkOm4", &candTrkOm4, &b_candTrkOm4);
   fChain->SetBranchAddress("candTrkz04", &candTrkz04, &b_candTrkz04);
   fChain->SetBranchAddress("candTrktlam4", &candTrktlam4, &b_candTrktlam4);
   fChain->SetBranchAddress("candTrkCov4", &candTrkCov4, &b_candTrkCov4);
   fChain->SetBranchAddress("njets4", &njets4, &b_njets4);
   fChain->SetBranchAddress("remNtrk4", &remNtrk4, &b_remNtrk4);
   fChain->SetBranchAddress("remNpfo4", &remNpfo4, &b_remNpfo4);
   fChain->SetBranchAddress("remPx4", &remPx4, &b_remPx4);
   fChain->SetBranchAddress("remPy4", &remPy4, &b_remPy4);
   fChain->SetBranchAddress("remPz4", &remPz4, &b_remPz4);
   fChain->SetBranchAddress("remE4", &remE4, &b_remE4);
   fChain->SetBranchAddress("qqPx4", &qqPx4, &b_qqPx4);
   fChain->SetBranchAddress("qqPy4", &qqPy4, &b_qqPy4);
   fChain->SetBranchAddress("qqPz4", &qqPz4, &b_qqPz4);
   fChain->SetBranchAddress("qqE4", &qqE4, &b_qqE4);
   fChain->SetBranchAddress("lPx4", &lPx4, &b_lPx4);
   fChain->SetBranchAddress("lPy4", &lPy4, &b_lPy4);
   fChain->SetBranchAddress("lPz4", &lPz4, &b_lPz4);
   fChain->SetBranchAddress("lE4", &lE4, &b_lE4);
   fChain->SetBranchAddress("lq4", &lq4, &b_lq4);
   fChain->SetBranchAddress("nuPzISR4", &nuPzISR4, &b_nuPzISR4);
   fChain->SetBranchAddress("gEISR4", &gEISR4, &b_gEISR4);
   fChain->SetBranchAddress("nuPx4", &nuPx4, &b_nuPx4);
   fChain->SetBranchAddress("nuPy4", &nuPy4, &b_nuPy4);
   fChain->SetBranchAddress("nuPz4", &nuPz4, &b_nuPz4);
   fChain->SetBranchAddress("nuE4", &nuE4, &b_nuE4);
   fChain->SetBranchAddress("gPx4", &gPx4, &b_gPx4);
   fChain->SetBranchAddress("gPy4", &gPy4, &b_gPy4);
   fChain->SetBranchAddress("gPz4", &gPz4, &b_gPz4);
   fChain->SetBranchAddress("gE4", &gE4, &b_gE4);
   fChain->SetBranchAddress("qqfitMass4", &qqfitMass4, &b_qqfitMass4);
   fChain->SetBranchAddress("lnufitMass4", &lnufitMass4, &b_lnufitMass4);
   fChain->SetBranchAddress("fitprob4", &fitprob4, &b_fitprob4);
   fChain->SetBranchAddress("chi24", &chi24, &b_chi24);
   Notify();
}

Bool_t MyClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MyClass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MyClass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MyClass_cxx

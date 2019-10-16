#include "marlin/Processor.h"
#include "EVENT/MCParticle.h"
#include "EVENT/ReconstructedParticle.h"
#include "EVENT/LCRelation.h"
#include "IMPL/LCCollectionVec.h"
#include "IMPL/MCParticleImpl.h"
#include "IMPL/ReconstructedParticleImpl.h"
#include <marlin/Global.h>
#include "gear/BField.h"
#include "lcio.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TString.h"
#include <vector>
#include <algorithm>
#include "TLorentzVector.h"
#include "TVector3.h"
#include "classifyTau.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include "EVENT/LCParameters.h"
#include "TROOT.h"
#include <string> 

#include "eventVariables.h"
#include "jetVariables.h"
#include "PandoraPfoVariables.h"
#include "anaVariables.h"
#include "overlayVariables.h"
#include "HistoManager.h"
#include "tauFinderVariables.h"
//#include "mcVariables.h"
#include "mcVars.h"
#include "tauJet.h"
#include "tauCand.h"
#include "remainjet.h"
#include "fitJet.h"
#include "remainPfos.h"
#include "jetOverlay.h"
#include "JetFitObject.h"
#include "NeutrinoFitObject.h"
#include "LeptonFitObject.h"
#include "ISRPhotonFitObject.h"
#include "MomentumConstraint.h"
#include "OPALFitterGSL.h"
#include "MassConstraint.h"
#ifdef __MAKECINT__
#pragma link C++ class vector< vector<float> >+;
#endif


//#define ncuts 7
//if we change nferm we need to recompile and also change _nfermion and _nleptons in xml
//#define nferm 4

using namespace lcio;
using namespace marlin;
	/** WWAnalysis:<br>
 *
 * 
 * @author Justin Anguiano, University of Kansas
 * 
 */

 class WWAnalysis2 : public marlin::Processor {

 public:

 virtual marlin::Processor*  newProcessor() { return new WWAnalysis2 ; }

  WWAnalysis2(const WWAnalysis2&) = delete ;
  WWAnalysis2& operator=(const WWAnalysis2&) = delete ;

  WWAnalysis2() ;

  /** Called at the beginning of the job before anything is read.
   *  Use to initialize the proscessor, e.g. book histograms.
   */
  virtual void init() ;
  /** Called for every run.
   */
  virtual void processRunHeader( LCRunHeader* run ) ;

  /** Called for every event - the working horse.
   */
  virtual void processEvent( LCEvent * evt ) ;


  /** Called after data processing for clean up.
   */
  virtual void end() ;

 //collection gathering
  bool FindMCParticles( LCEvent* evt );
  bool FindPFOCollection( LCEvent* evt, std::string PfoCollectionName, std::vector<ReconstructedParticle*>& localVec );
  bool FindTracks( LCEvent* evt );
  bool FindRecoToMCRelation( LCEvent* evt );
 void dofit(int coneNumber );
	
 //  void processOverlayVariables(overlayVariables*& oVar, std::vector<ReconstructedParticle*> jets, std::vector<MCParticle*> mcpartvec , std::vector<LCRelation*> pfo2mc);




	 


  //jet analysis helpers
 
 	//TODO reimplement in other class
//	MCParticle* classifyEvent2fermion( std::vector<TLorentzVector*>& _MCf, std::vector<int>& _MCfpdg );



	//for the extra overlay analysis jets
 // void populateJetsWithOverlayTLVs(std::vector<ReconstructedParticle*> j);

  //helper function to get production angle of W-
 // double getCosThetaW();

  

  protected:

//output file
  TFile* file{};


 //std::vector<TTree*> _trees{};
	TTree* _tree{}; //only one tree

//Tau optimization////
 //int _tauoptmode{};
// void initTauFinderOptimization();
	void inittree();
 void SetTauOptimizationVariables(LCEvent* evt);
 //void initEmptyTau(tauFinderVariables*& t, MCParticle* tau);
 //void initTauWithNoMCLepton(tauFinderVariables*& t);
 //std::vector<tauFinderVariables*> _tf{};
 //std::vector<mcVariables*> _mcv{};
 //std::vector<remainPfos*> _rp{};
 //std::vector<jetOverlay*> _ol1j{};
 //std::vector<jetVariables*> _js{};//2d because we can have mulitple jet collection for one parameter set
 //std::vector<jetOverlay*> _rjOL{};

 mcVars* _mcv{};
 std::vector<tauJet*> _tauJets{};
 std::vector<tauCand*> _tauCands{}; //energy selected
 std::vector<remainjet*> _remJets{};
 std::vector<fitJet*> _fitJets{}; 
 
void FillNtuple(LCEvent* evt);

 
//TTree* _tree{};//single run tree
//non tau optimization


  //event info
  int _nRun{};
  int _nEvt{};
  float _xsec{}; 
  float _xsecerr{};
  double _remainYcut{};
  int _beampart1{};
  int _beampart2{};
  int _polarization1{};
  int _polarization2{};

  int _nPandoraTrks{};
  int _nPandoraPfos{};

  int _nLL{};
  int _nRR{};
  int _nLR{};
  int _nRL{};


//fitt variables
 std::vector<int> _wwlike{0,0,0,0,0};
// double _fitprob{};
// double _chi2{};

std::string _outpath;


//the total number of unique cuts applied (for histogram indexing)

	int ncuts = 7;

  
  //vector to hold the particles for the event
   std::vector<MCParticle*> _mcpartvec{};

    std::vector<Track*> _trackvec{};
//  std::vector<ReconstructedParticle*> _pfovec{};
//  std::vector<ReconstructedParticle*> _purePFOs{};
//  std::vector<LCRelation*> _reco2mcvec{};
 

 
 
 
	//jet y variabls //log jet variables
  //int _nJets{};
  //int _nJetCollections = 5;


	//EVENT SELECTION WEIGHT
//	double weight{};//defined in xml


	int   _printing{};

	//running mode
//	int _runSignalMode{};

//input background//number of fermions or leptons
	int _nfermions{};
	int _nleptons{};

  //input collections
  std::string _inputMcParticleCollectionName{};
  std::string _inputTrackCollectionName{};
//  std::string _inputRecoRelationCollectionName{}; 
  std::vector<ReconstructedParticle*> _pandoraPFOs{}; 


  //std::vector<std::vector<ReconstructedParticle*> > _particleCollections{};
  //std::vector<std::vector<ReconstructedParticle*> > _remainCollections{};
  //std::vector<std::vector<ReconstructedParticle*> > _remainJetCollections{};
  
  std::vector<std::vector<ReconstructedParticle*> > _tauJetCollections{};
  std::vector<std::vector<ReconstructedParticle*> > _tauCandCollections{};
  std::vector<std::vector<ReconstructedParticle*> > _remJetCollections{};
//  std::vector<std::vector<Reconstructedparticle*> > _remPFOCollections{};
 // std::vector<std::vector<ReconstructedParticle*> > _inputJetCollections{}

 // std::vector<std::string> _inputJetCollectionsNames{};
 // std::vector<std::string> _inputRemainCollectionsNames{};
 // std::vector<std::string> _inputRemainJetsCollNames{};
 std::vector<std::string> _tauJetCollectionsNames{};
 std::vector<std::string> _tauCandCollectionsNames{};
 std::vector<std::string> _remJetCollectionsNames{};
 //std::vector<std::string> _remPFOCollectionsNames{};

	






};

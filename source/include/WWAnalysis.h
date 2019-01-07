#include "marlin/Processor.h"
#include "EVENT/MCParticle.h"
#include "EVENT/ReconstructedParticle.h"
#include "EVENT/LCRelation.h"
#include "IMPL/LCCollectionVec.h"
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

#include "eventVariables.h"
#include "jetVariables.h"
#include "PandoraPfoVariables.h"
#include "anaVariables.h"
#include "overlayVariables.h"
#include "HistoManager.h"



//#define ncuts 7
//if we change nferm we need to recompile and also change _nfermion and _nleptons in xml
//#define nferm 4

using namespace lcio;

	/** WWAnalysis:<br>
 *
 * 
 * @author Justin Anguiano, University of Kansas
 * 
 */

 class WWAnalysis : public marlin::Processor {

 public:

 virtual marlin::Processor*  newProcessor() { return new WWAnalysis ; }

  WWAnalysis(const WWAnalysis&) = delete ;
  WWAnalysis& operator=(const WWAnalysis&) = delete ;

  WWAnalysis() ;

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
 // bool FindJets( LCEvent* evt ) ;
  bool FindPFOs( LCEvent* evt ) ;
  bool FindTracks( LCEvent* evt );
  bool FindRecoToMCRelation( LCEvent* evt );
 // bool FindJetsWithOverlay( LCEvent* evt );
  bool FindJetCollection( LCEvent* evt, std::string JetCollectionName, std::vector<ReconstructedParticle*>& localVec );

	void processSignalVariableSet(LCEvent* evt, std::vector<LCRelation*> pfo2mc, eventVariables*& evtVar, jetVariables*& jetVar, PandoraPfoVariables*& ppfoVar, anaVariables*& anaVar, overlayVariables*& oVar, std::vector<ReconstructedParticle*> jets);
	void printSignalVariableSet( eventVariables*& evtVar, jetVariables*& jetVar, PandoraPfoVariables*& ppfoVar, anaVariables*& anaVar, overlayVariables*& oVar );



	//overlay analysis
	//TODO redo in separate class
	void AnalyzeOverlay(LCEvent* evt );
	void FindMCOverlay( MCParticle* p , std::vector<MCParticle*>& FSP);
	void AnalyzeOverlayAcceptance(std::vector<TLorentzVector*> _jetswithoverlay, std::vector<TLorentzVector*> _jetsremovedoverlay );
	void initOverlayEff();

  //jet analysis helpers
 
 	//TODO reimplement in other class
	MCParticle* classifyEvent2fermion( std::vector<TLorentzVector*>& _MCf, std::vector<int>& _MCfpdg );



	//for the extra overlay analysis jets
  void populateJetsWithOverlayTLVs(std::vector<ReconstructedParticle*> j);

  //helper function to get production angle of W-
  double getCosThetaW();

  

  protected:

 //variable helper classes
 eventVariables* ev_eekt{};
 jetVariables* jv_eekt{};
 anaVariables* ana_eekt{};
 overlayVariables* ov_eekt{};
 overlayVariables* ppfo_ovr{};

	eventVariables* ev_kt15{};
 jetVariables* jv_kt15{};
 anaVariables* ana_kt15{};

	eventVariables* ev_kt08{};
 jetVariables* jv_kt08{};
 anaVariables* ana_kt08{};

//overlay removed from eekt variables set
 eventVariables* ev_eekt_no_overlay{};
 jetVariables* jv_eekt_no_overlay{};
 anaVariables* ana_eekt_no_overlay{};

 PandoraPfoVariables* ppfov{};
 HistoManager* h1{};
//TTree
  TFile* file{};
  TTree* _tree{};
  int _nRun{};
  int _nEvt{};

//event number
  int nEvt{};



 //the number of overlay events present in the event
	int OverlaynTotalEvents=-1;
	int OverlayPairBgOverlaynEvents=-1;
	//overlay rejected particle variables separated by flavour
	//these vectors need to be cleared for each event
	std::vector<double> uplike_rejects_costheta{};
	std::vector<double> downlike_rejects_costheta{};
	std::vector<double> lepton_rejects_costheta{};

	std::vector<double> uplike_rejects_pt{}; 
	std::vector<double> downlike_rejects_pt{};
	std::vector<double> lepton_rejects_pt{};
	
	std::vector<double> uplike_rejects_P{};
	std::vector<double> downlike_rejects_P{};
	std::vector<double> lepton_rejects_P{};

//the total number of unique cuts applied (for histogram indexing)

	int ncuts = 7;

  
  //vector to hold the particles for the event
  std::vector<MCParticle*> _mcpartvec{};
 // std::vector<ReconstructedParticle*> _jets{};
  std::vector<Track*> _trackvec{};
  std::vector<ReconstructedParticle*> _pfovec{};
  std::vector<LCRelation*> _reco2mcvec{};
 // std::vector<ReconstructedParticle*> _jetswithoverlay{};
  
 
	//testing
//  std::vector< std::vector<ReconstructedParticle*> > _jetCollections{};
 
 std::vector<ReconstructedParticle*> _eektJets{};
  std::vector<ReconstructedParticle*> _kt08Jets{};
//  std::vector<ReconstructedParticle*> _kt10Jets{};
//  std::vector<ReconstructedParticle*> _kt12Jets{};
  std::vector<ReconstructedParticle*> _kt15Jets{};
 
 
	//jet y variabls //log jet variables
  int _nJets{};
  int _nJetCollections = 5;


	//EVENT SELECTION WEIGHT
	double weight{};//defined in xml


	int   _printing{};

//input background//number of fermions or leptons
	int _nfermions{};
	int _nleptons{};

  //input collections
  std::string _inputMcParticleCollectionName{};
  std::string _inputJetCollectionName{};
  std::string _inputJetWithOverlayCollectionName{};
  std::string _inputParticleCollectionName{};
  std::string _inputTrackCollectionName{};
  std::string _inputRecoRelationCollectionName{};

 // std::< std::vector<std::string> > jetCollectionNames{};

  std::string _JetCollName_eekt = "eektJets";
  std::string _JetCollName_kt15 = "kt15Jets";
  std::string _JetCollName_kt08 = "kt08Jets";



	/* special set of histograms for dealing with overlay and forward acceptance */
	/* each hist in the array is a cut on costheta */
	/* the cuts are 0.99, 0.95, 0.91, 0.8, 0.6, 0.4, 0.2 */
	//total of 7 different cuts
	int overlaycuts = 8;
	std::vector<double> maxcosthetacuts{ 0.2, 0.4, 0.6, 0.8, 0.91, 0.95, 0.99,99};
	std::vector<TH1D*> maxcostheta_cut{};
	//no overlay removal in this plot
	std::vector<TH1D*> maxcostheta_cut_ovr{};

	//generator level
	std::vector<TH1D*> maxcostheta_cut_mc{};
	//mctag mqq - mc mqq
	std::vector<TH1D*> mctag_mc_dM_ovr{};
	std::vector<TH1D*> mctag_mc_dM{};
	

	/* end acceptance */

};

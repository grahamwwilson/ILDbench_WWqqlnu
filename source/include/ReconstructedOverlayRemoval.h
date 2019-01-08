#include "marlin/Processor.h"
#include "EVENT/MCParticle.h"
#include "EVENT/ReconstructedParticle.h"
#include "IMPL/LCCollectionVec.h"
#include "EVENT/LCRelation.h"
#include "lcio.h"
#include "TFile.h"
#include <vector>

#include "TLorentzVector.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace lcio;

	/** ReconstructedOverlayRemoval:<br>
 *
 * 
 * @author Justin Anguiano, University of Kansas
 * 
 */

 class ReconstructedOverlayRemoval : public marlin::Processor {

 public:

 virtual marlin::Processor*  newProcessor() { return new ReconstructedOverlayRemoval ; }

  ReconstructedOverlayRemoval(const ReconstructedOverlayRemoval&) = delete ;
  ReconstructedOverlayRemoval& operator=(const ReconstructedOverlayRemoval&) = delete ;

  ReconstructedOverlayRemoval() ;

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

  bool FindPFOs(LCEvent* evt);
  bool FindMCParticles( LCEvent* evt );
  bool FindRecoToMCRelation( LCEvent* evt );

  void printReconstructedParticle(ReconstructedParticle* p);
  bool particleIsOverlay(int id);
  void classifyReconstructedParticles( LCCollectionVec*& overlayCollection, LCCollectionVec*& purgedCollection);
  void extractMCOverlay( std::vector<MCParticle*>& mcpartvec, LCCollectionVec*& mcCollection );
  protected:
  int nEvt{};
  
  //vector to hold the tracks for the event
  std::vector<ReconstructedParticle*> _pfovec{};
  std::vector<MCParticle*> _mcpartvec{};

  std::vector<LCRelation*> _reco2mcvec{};

 
//xml parameters

  std::string _outputParticleCollectionName{};
  std::string _inputParticleCollectionName{};
  
  std::string _outputMCCollectionName{};
  std::string _inputMcParticleCollectionName{};

  std::string _inputRecoRelationCollectionName{};

  std::string _outputOverlayCollectionName{};

  int _MCOFilter{};
  int _printing{};
};

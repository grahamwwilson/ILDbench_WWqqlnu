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

	/** TauSelector:<br>
 *
 * 
 * @author Justin Anguiano, University of Kansas
 * 
 */

 class TauSelector : public marlin::Processor {

 public:

 virtual marlin::Processor*  newProcessor() { return new TauSelector ; }

  TauSelector(const TauSelector&) = delete ;
  TauSelector& operator=(const TauSelector&) = delete ;

  TauSelector() ;

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

  bool FindPFOs(LCEvent* evt, std::string _inputParticleCollectionName, std::vector<ReconstructedParticle*>& _pfovec);

  void printReconstructedParticle(ReconstructedParticle* p);

  protected:
  int nEvt{};
  
  //vector to hold the tracks for the event
  std::vector<ReconstructedParticle*> _Remainpfovec{};
  std::vector<ReconstructedParticle*> _TauJetpfovec{};

 
//xml parameters

  std::string _inputRemainCollectionName{};
  std::string _inputTauJetCollectionName{};

  std::string _outputRemainCollectionName{};
  std::string _outputTauJetCollectionName{};


};

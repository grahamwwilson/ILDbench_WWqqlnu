

# This is a list of all the variables used in the analysis along with a simple definition

---WWAnalysis.h---

#std::vector<TLorentzVector*> _MCf; 
An array that stores the four vectors of the generator level fermions of the event, e.g. qq, qqqq, qqlnu 

#std::vector<int> _MCfpdg;
An array that stores the pdg value of the generator level fermions of the event, the index of particles are consistent between _MCf and _MCfpdg

#bool isTau;
A flag that is used to distinguish signal events from the generator level, if the generator lepton is a tau then this variable is true

#bool isMuon;
The same as isTau but true for muon events

#int trueq;
The charge of the generator lepton in a signal event

#int tauDecayMode;
a numbered generator decay mode for tau from daniels code, based on this enumeration
{decayChPi=0, decayRho, decayA1_1p, decayA1_3p , decayEl, decayMu , decayW , decayK , decayMultiprong , decayOthersingleprong, decayUnrecognised}
  
#int taudaughters;
the number of stable generator daughters from daniels algorithm
  
#int tauChargedDaughters;
the number of tracks from a generator tau from daniels algorithm
  
#int tauNeutrals;
the number of neutral particles from a generator tau from daniels algoritm

#int lq;
the assigned charge of the reconstructed jet that is tagged as a lepton

#int OverlaynTotalEvents;
the total number of overlay events for a particular event, name follows the parameter name from dumpevent
	
#int OverlayPairBgOverlaynEvents;
the total number of pair background overlay events, there is always at least 1

# std::vector<TLorentzVector*> jets{};
four vector version of the reconstructed particle jets

#TLorentzVector* Wl;
The four vector of the reconstructed leptonic W, made from the inferred neutrino four momentum and the four momentum of the jet tagged as a lepton

#TLorentzVector* Wqq;
The four vector of the reconstructed hadronic W, made from the two jets that are tagged as quarks

#TLorentzVector* nu;
A four vector of the inferred neutrino, with assumed mass=0

#std::vector<TLorentzVector*> CMJets{};
The four vectors of the visible reconstructed jets boosted into their W rest frame

#TLorentzVector* CMnu;
The four vector of the inferred neutrino boosted into its leptonic W rest frame

#int lpdg;
the generator pdg code for the mc lepton in a signal event
  
#int lnparts;
the number of particles in a lepton tagged reconstructed jet
  
#int lntracks; 
the number of tracks in a lepton tagged reconstructed jet
  
#int lnmcparts; //true n daughters of lepton
the number of particles from the generator tau in a signal event , includes tracks, neutrals, FSR (primary visbile things but not conversions) based on my lepton algorithm
 
#int lnmctracks;
the number of tracks produced in the generator tau decay in a signal event, based on my lepton algorithm
  
#std::vector<int> jetNparts;
a vector that tracks the number of reconstructed particles in each reconstructed jet. The i'th element is the number of reconstructed particles in the i'th jet product of fast jet
  
#std::vector<int> jetNtracks; 
the same as jetNparts except this exclusived holds the number fast jet tracks

#double leadingptljet; 
the transverse momentum of the highest momentum track of the reconstructed jet that is tagged as a lepton  

#double leadingd0ljet; //d0 of the leading track in the lepton jet
the r-phi impact parameter d0 of the highest momentum track in the reconstructed jet tagged as a lepton
  
#double leadingd0relerrljet;
(name should change) the significance of leadingd0ljet d0/sigma_d0

#int trueljetntracks; 
the number of tracks in the reconstructed jet that has been tagged from the mc lepton
  
#int jetleastntracks; 
the number of tracks in the reconstructed jet that has the fewest tracks

#double mcqqmass;
the mass from the sum of the two generator quarks four momentum in a signal event

#double mcqqE;
the energy of the generator diquark
	
#double mcqqcostheta;
cosine of the polar angle of the generator diquark

#double mcqqphi;
azimuthal angle of the generator diquark

#double leadingptqjet; //pt of the leading track in a quark jet
the transverse momentum of the highest momentum track of one of the jets tagged as a quark jet 

#double leadingd0qjet; //d0 of the leading track in a quark jet
the r-phi impact parameter d0 of the highest momentum track in one of the jets tagged as a quark jet
 
#double leadingd0relerrqjet;
the significance of leadingd0qjet   d0/sigma_d0

//jet y variabls //log jet variables
#int _nJets;
number of jets produced from fast jet eekt

#float _yMinus;
the fast jet variable from eekt for y-, the value stored is log(y-)

#float _yPlus;
same as _yMinus but the + version, also log(y+)

#double psi_mcl_ljet;
the opening angle between the generator lepton and the reconstructed jet that is tagged as a lepton

  //opening angle between mc lepton and closest jet
#double true_psi_mcl_ljet;
the opening angle between the generator lepton and the reconstructed jet that was tagged by the mc lepton

#int totaltracks{};
The total number of charged particles in the event, populated directly from PandoraPFOs

#double total_Pt{};
The transverse momentum from the four vector that is the sum of all PandoraPFO four vectors	

#double total_E{};
the same as total_Pt but the total Energy
	
#double total_M{};
the same as total_Pt but the total Mass
  



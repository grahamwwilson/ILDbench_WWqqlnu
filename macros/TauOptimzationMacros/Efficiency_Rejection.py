

from ROOT import TCanvas, TFile, TH1D, TH2D, TProfile, TLegend, TGraph, TTree, gDirectory
import subprocess

def bash( bashCommand ):
	process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
	#process = subprocess.Popen(bashCommand.split())
	output, error = process.communicate()
	return output ,error
def GetKeyNames( self, dir = "" ):
        self.cd(dir)
        return [key.GetName() for key in gDirectory.GetListOfKeys()]
TFile.GetKeyNames = GetKeyNames

#run over 3 subsets S1, S2, B1

#on run define what subset
SUBSET = ['S1', 'S2', 'B1']
PARTICLETYPE = ['MUON', 'ELECTRON', 'TAU0', 'TAU1', 'TAU2', 'TAU3', 'TAU4', 'BG1']

#CHOOSE SUBSET/PTYPE INDICES
SUBSET = SUBSET[0]
PARTICLETYPE = PARTICLETYPE[0]


#Since i didnt store it, figure out the parameters for each tree and store them with the eff
searchConeAngleMin = 0.
searchConeAngleMax = 0.16
searchConeAngleStep = 0.01 #10mrad step

isoAngleMin = 0.
isoAngleMax = 0.11
isoAngleStep = 0.01 #10mrad step

isoEnergyMin = 0.
isoEnergyMax = 11.
isoEnergyStep = 1. #1gev step

#number of trees per file
#nTreesPerFile = 50


#create the parameter sets
coneValues = np.arange(searchConeAngleMin, searchConeAngleMax, searchConeAngleStep)
isoAngleValues = np.arange(isoAngleMin, isoAngleMax, isoAngleStep)
isoEnergyValues = np.arange(isoEnergyMin, isoEnergyMax, isoEnergyStep)

#make a little sublist of [tree number, cone angle, iso angle, iso energy]
treedetails = []
treenum = 1
for c in coneValues:
	for iA in isoAngleValues:
		for iE in isoEnergyValues:
			treedetails.append( [ treenum, c, iA, iE ])
			treenum = treenum + 1

print treedetails

LS = bash('ls /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RootFiles/file.root /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RootFiles/')
LS = LS[0].split('\n')

#collect the files of chosen subset
FILESUBSET = [f for f in LS if SUBSET in f]

print FILESUBSET

#loop over the list of files and collect all the trees
for filename in FILESUBSET:
	currentFile = TFile.Open(filename)
	treeNames = currentFile.GetKeyNames('./')
	#extract each tree
	for tn in treeNames:
		tree = t.currentFile.Get(tn)
		#loop over the tree
		for nevents in tree:

			if PARTICLETYPE == 'MUON':
				if nevent.isMuon:
					
			if PARTICLETYPE == 'ELECTRON':

			if PARTICLETYPE == 'TAU0':

			if PARTICLETYPE == 'TAU1':

			if PARTICLETYPE == 'TAU2':

			if PARTICLETYPE == 'TAU3':
	
			if PARTICLETYPE == 'TAU4':



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

LS = bash('ls /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RootFiles/file.root /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RootFiles/')
LS = LS[0].split('\n')

#collect the files of chosen subset
FILESUBSET = [f for f in LS if SUBSET in f]

print FILESUBSET

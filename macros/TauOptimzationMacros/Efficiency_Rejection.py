

from ROOT import TCanvas, TFile, TH1D, TH2D, TProfile, TLegend, TGraph, TTree, gDirectory
import subprocess
from array import array


def bash( bashCommand ):
	process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
	#process = subprocess.Popen(bashCommand.split())
	output, error = process.communicate()
	return output ,error
def GetKeyNames( self, dir = "" ):
        self.cd(dir)
        return [key.GetName() for key in gDirectory.GetListOfKeys()]
TFile.GetKeyNames = GetKeyNames

def GetTreeObject(tree, branchName ,value):
	branchesObj = tree.GetListOfBranches()
	branches = []
	for b in branchesObj:
		branches.append( b.GetName() )
		
	print "got branches"
	print branches
	branch = [b for b in branches if branchName in b]
	print "got branch"
	print branch
	print "done"
	tree.SetBranchAddress(branch[0],value)
	#return branch.GetEntries()
	#ranch.GetLeafEntry
	#leafs = tree.GetListOfLeaves()
	#print leafs

def makearray(mini,Maxi,step):
	#start = mini
	arr = []
	while mini < Maxi :
		arr.append(mini)
		mini = mini + step
		mini = round(mini, 4)
	return arr
#run over 3 subsets S1, S2, B1

#on run define what subset
SUBSET = ['S1', 'S2', 'B1']
PARTICLETYPE = ['MUON', 'ELECTRON', 'TAU0', 'TAU1', 'TAU2', 'TAU3', 'TAU4', 'BG1']

#CHOOSE SUBSET/PTYPE INDICES
BGSUBSET = SUBSET[2]
BGPARTICLETYPE = PARTICLETYPE[7]
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
coneValues = makearray(searchConeAngleMin, searchConeAngleMax, searchConeAngleStep)
isoAngleValues = makearray(isoAngleMin, isoAngleMax, isoAngleStep)
isoEnergyValues = makearray(isoEnergyMin, isoEnergyMax, isoEnergyStep)

#make a little sublist of [tree number, cone angle, iso angle, iso energy]
treedetails = []
treenum = 1
for c in coneValues:
	for iA in isoAngleValues:
		for iE in isoEnergyValues:
			treedetails.append( [ treenum, c, iA, iE ])
			treenum = treenum + 1

#print treedetails

LS = bash('ls /nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RootFiles/')
LS = LS[0].split('\n')

#collect the files of chosen subset
FILESUBSET = [f for f in LS if SUBSET in f]
BGFILESUBSET = [f for f in LS if BGSUBSET in f]

#print FILESUBSET
#print BGFILESUBSET

#we need to write all this stuff to a tree in a rootfile
outputFile = TFile.Open('/nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/EffRootFiles/'+SUBSET+PARTICLETYPE+'.root','RECREATE')
outputTree = TTree(SUBSET+PARTICLETYPE, SUBSET+PARTICLETYPE)
eff_s, eff_b, RR, treeN, searchCone, isoCone, isoE, p, effp, N_s, N_b, Total_s, Total_b = array( 'f', [ 0. ] ),array( 'f', [ 0. ]) ,array( 'f', [ 0. ]) ,array( 'f', [ 0. ]) ,array( 'f', [ 0. ]) ,array( 'f', [ 0. ]) ,array( 'f', [ 0. ]) ,array( 'f', [ 0. ]) ,array( 'f', [ 0. ]) ,array( 'f', [ 0. ]) ,array( 'f', [ 0. ]) ,array( 'f', [ 0. ]) ,array( 'f', [ 0. ]) 
eff_sL, eff_bL, RRL, treeNL, searchConeL, isoConeL, isoEL, pL, effpL, N_sL, N_bL, Total_sL, Total_bL = [], [], [], [], [], [], [], [], [], [], [], [], []
#set branches
outputTree.Branch("eff_s",eff_s,"eff_s/F")
outputTree.Branch("eff_b",eff_b,"eff_b/F")
outputTree.Branch("RR",RR,"RR/F")
outputTree.Branch("treeN",treeN,"treeN/F")
outputTree.Branch("searchCone",searchCone,"searchCone/F")
outputTree.Branch("isoCone",isoCone,"isoCone/F")
outputTree.Branch("isoE",isoE,"isoE/F")
outputTree.Branch("p",p,"p/F")
outputTree.Branch("effp",effp,"effp/F")
outputTree.Branch("N_s",N_s,"N_s/F")
outputTree.Branch("N_b",N_b,"N_b/F")
outputTree.Branch("Total_s", Total_s,"Total_s/F")
outputTree.Branch("Total_b", Total_b,"Total_b/F")

#iterator for tree details
treedetails_itr = 0;
#combine FILESUBSETS
FILESUPERSET = []
for f1 in FILESUBSET:
	FILESUPERSET.append(f1)
for b1 in BGFILESUBSET:
	FILESUPERSET.append(b1)

FILESUBSET = FILESUPERSET
#tree loop vars
isMuon = array('i',[0])
nTaus = array('i',[0])
#loop over the list of files and collect all the trees
for filename in FILESUBSET:
	currentFile = TFile.Open('/nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RootFiles/'+filename)

	keyList = currentFile.GetKeyNames('./')
	print "\nKeys in file:", keyList
	treeNames = currentFile.GetKeyNames('./')
	#extract each tree
	for tn in treeNames:
		tree = currentFile.Get(tn)

		GetTreeObject(tree, 'isMuon', isMuon )
		GetTreeObject(tree, 'nTaus', nTaus )
		for entry in tree:
			if isMuon[0] && PARTICLETYPE == 'MUON'::
				Total_s[0] = Total_s[0]+1.
				round(Total_s[0])
				if nTaus == 1:
					N_s[0] = N_s[0] + 1.
					round(N_s[0])

		print N_s[0], Total_s[0]
		tree.Fill()
		break
	break
		#loop over the tree
		#for nevents in tree:

		#	GetTreeObject(tree, 'isMuon' )
		#	break
	#		if PARTICLETYPE == 'MUON':
	#			#if nevent.(tn+'isMuon'):
	#			if 0:
	#				Total_s = Total_s+ 1.
	#			#	if nevent.(tn+'nTaus') == 1:
	#			if 0:
	#					N_s = N_s + 1.
	#				
	#		if PARTICLETYPE == 'ELECTRON':
	#			True
#
#			if PARTICLETYPE == 'TAU0':
#				True
#
#			if PARTICLETYPE == 'TAU1':
#				True
##			if PARTICLETYPE == 'TAU2':
#				True
#
#			if PARTICLETYPE == 'TAU3':
#				True
#	
#			if PARTICLETYPE == 'TAU4':
#				True

		#populate variables according to the current tree and fill our output tree
#		eff_sL.append(N_s/Total_s)
#		treeNL.append(treedetails[treedetails_itr][0])
#		searchConeL.append(treedetails[treedetails_itr][1])
#		isoConeL.append(treedetails[treedetails_itr][2])
#		isoEL.append(treedetails[treedetails_itr][3])
		#tree.Fill()

#we have to loop over the bg file separate
#for filename in BGFILESUBSET:
#	currentFile = TFile.Open(filename)
#	treeNames = currentFile.GetKeyNames('./')
	#extract each tree
#	for tn in treeNames:
#		tree = currentFile.Get(tn)
		#loop over the tree
#		for nevents in tree:
#			Total_b = Total_b + 1.
		#if nevent.(tn+'nTaus') :
#		if 0:
#				N_b = N_b + 1.
#
#		eff_bL.append(N_b/Total_b)
#		RRL.append(1. - eff_b)
#		pL.append(N_s / (N_s + N_b))
#		effPL.append(1.)
		
#loop over everything
#for A,B,C,D,E,F,G,H,I,J,K,L,M in zip(eff_sL, eff_bL, RRL, treeNL, searchConeL, isoConeL, isoEL, pL, effpL, N_sL, N_bL, Total_sL, Total_bL):
#	eff_s, eff_b, RR, treeN, searchCone, isoCone, isoE, p, effp, N_s, N_b, Total_s, Total_b = A,B,C,D,E,F,G,H,I,J,K,L,M
#	effp = eff_s * p
#	outputTree.Fill()
	

outputFile.Write()
		





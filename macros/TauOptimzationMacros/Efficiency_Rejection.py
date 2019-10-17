

from ROOT import TCanvas, TFile, TH1D, TH2D, TProfile, TLegend, TGraph, TTree, gDirectory, TLorentzVector
import ROOT as rt
import subprocess
from array import array
import math
import ctypes
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
		
#	print "got branches"
	#print branches
	branch = [b for b in branches if branchName in b]
#	print "got branch"
#	print branch
	#print "done" 
#	if(not tlv):
	tree.SetBranchAddress(branch[0],value)
#	if( tlv ):
#		tree.SetBranchAddress(branch[0]+'.E' ,value)
	#return branch.GetEntries()
	#ranch.GetLeafEntry
	#leafs = tree.GetListOfLeaves()
	#print leafs
def GetBranchName(tree, branchName):
	branchesObj = tree.GetListOfBranches()
	branches = []
	for b in branchesObj:
		branches.append(b.GetName() )
	branch = [b for b in branches if branchName in b]
	return branch[0]

def makearray(mini,Maxi,step):
	#start = mini
	arr = []
	while mini < Maxi :
		arr.append(mini)
		mini = mini + step
		mini = round(mini, 4)
	return arr

def getmaxenergy( ntaus, vec4):
	if ntaus == 0:
		return 0.
	maxE = 0.
	for v in vec4:
		if v.E() > maxE:
			maxE = v.E()

	return maxE

def passAcceptance( flist, fpdglist):
	passes = True
	for mcf, pdg in zip(flist, fpdglist):
		if abs(pdg[0]) != 12 and abs(pdg[0]) != 14 and abs(pdg[0]) != 16:
			#no neutrinos allowed
			if abs( abs(mcf[0]) > 0.995 ):
				passes = False
	return passes 

#run over 3 subsets S1, S2, B1

#def tilv( branchname ):
#	getattr(t,'my4vec.').E()
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
#eff_sL, eff_bL, RRL, treeNL, searchConeL, isoConeL, isoEL, pL, effpL, N_sL, N_bL, Total_sL, Total_bL = [], [], [], [], [], [], [], [], [], [], [], [], []
Emax_s, Emax_b = array( 'f', [0.] ), array( 'f', [0.] )
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
#outputTree.Branch("Emax_s", Emax_s,"Emax_s/F") #the higheest energy tau reconstucted
#outputTree.Branch("Emax_b", Emax_b,"Emax_b/F")

#iterator for tree details
treedetails_itr = 0;
#combine FILESUBSETS
#FILESUPERSET = []
#for f1 in FILESUBSET:#
#	FILESUPERSET.append(f1)
#for b1 in BGFILESUBSET:
#	FILESUPERSET.append(b1)

#FILESUBSET = FILESUPERSET
#tree loop vars
isMuon = array('i',[0])
isTau = array('i',[0])
isElectron = array('i',[0])
tauType = array('i',[0])
nTaus = array('i',[0])
nTausBG = array('i',[0])
#tauTLV = rt.vector('TLorentzVector')()
#tauTLVBG = rt.vector('TLorentzVector')()

#look at acceptance
#currently we only look at 4f events
#mcf0 = TLorentzVector()
mcf0 = array('d',[0])
mcf1 = array('d',[0])
mcf2 = array('d',[0])
mcf3 = array('d',[0])
mcf0_pdg = array('i',[0])
mcf1_pdg = array('i',[0])
mcf2_pdg = array('i',[0])
mcf3_pdg = array('i',[0])
mcf0bg = array('d',[0])
mcf1bg = array('d',[0])
mcf2bg = array('d',[0])
mcf3bg = array('d',[0])
mcf0_pdgbg = array('i',[0])
mcf1_pdgbg = array('i',[0])
mcf2_pdgbg = array('i',[0])
mcf3_pdgbg = array('i',[0])





print FILESUBSET
print BGFILESUBSET
#loop over the list of files and collect all the trees
for filename, filenameBG in zip(FILESUBSET, BGFILESUBSET):
	currentFile = TFile.Open('/nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RootFiles/'+filename)
	currentBGFile = TFile.Open('/nfs/dust/ilc/user/anguiano/WWBenchmark/WWFiles/TauOptimizationFiles/RootFiles/'+filenameBG)	

	keyList = currentFile.GetKeyNames('./')
	print "\nKeys in file:", keyList
	treeNames = currentFile.GetKeyNames('./')
	treeNamesBG = currentBGFile.GetKeyNames('./')
	#extract each tree
	for tn,tnbg in zip(treeNames, treeNamesBG):
		tree = currentFile.Get(tn)
		treebg = currentBGFile.Get(tnbg)

		GetTreeObject(tree, 'isMuon', isMuon )
		GetTreeObject(tree, 'nTaus', nTaus )
		GetTreeObject(tree, 'isTau', isTau)
		GetTreeObject(tree, 'isElectron', isElectron)
		GetTreeObject(tree, 'tauType', tauType)
		GetTreeObject(treebg, 'nTaus', nTausBG)
	#	GetTreeObject(tree, 'tauTLV', tauTLV)
	#	GetTreeObject(treebg, 'tauTLV', tauTLVBG) 
##		GetTreeObject(tree, 'MCf0', mcf0, 1)
	#	GetTreeObject(tree, 'MCf1', mcf1)
	#	GetTreeObject(tree, 'MCf2', mcf2)
	#	GetTreeObject(tree, 'MCf3', mcf3)
		GetTreeObject(tree, 'MCf0_PDG', mcf0_pdg)
		GetTreeObject(tree, 'MCf1_PDG', mcf1_pdg)
		GetTreeObject(tree, 'MCf2_PDG', mcf2_pdg)
		GetTreeObject(tree, 'MCf3_PDG', mcf3_pdg)
#		GetTreeObject(treebg, 'MCf0', mcf0bg)
#		GetTreeObject(treebg, 'MCf1', mcf1bg)
#		GetTreeObject(treebg, 'MCf2', mcf2bg)
#		GetTreeObject(treebg, 'MCf3', mcf3bg)
	#	
		GetTreeObject(treebg, 'MCf0_PDG', mcf0_pdgbg)
		GetTreeObject(treebg, 'MCf1_PDG', mcf1_pdgbg)
		GetTreeObject(treebg, 'MCf2_PDG', mcf2_pdgbg)
		GetTreeObject(treebg, 'MCf3_PDG', mcf3_pdgbg)
		
		#for entry, entryBG in zip(tree, treebg):
		for entry in tree:
			#mcflist = [ mcf0, mcf1, mcf2, mcf3 ]
			mcf0[0] = getattr(entry,GetBranchName(tree,'MCf0')).CosTheta()	
			mcf1[0] = getattr(entry,GetBranchName(tree,'MCf1')).CosTheta()
			mcf2[0] = getattr(entry,GetBranchName(tree,'MCf2')).CosTheta()
			mcf3[0] = getattr(entry,GetBranchName(tree,'MCf3')).CosTheta()
			#print mcf0[0]
			mcflist= [mcf0,mcf1,mcf2,mcf3]
			mcfpdglist = [mcf0_pdg, mcf1_pdg, mcf2_pdg, mcf3_pdg ]
			#print mcflist
			#print mcfpdglist
			#print passAcceptance(mcflist, mcfpdglist)
			if passAcceptance(mcflist, mcfpdglist) == False:
				continue
		
			#does entry pass mc acceptance
			if isMuon[0] and PARTICLETYPE == 'MUON':
				Total_s[0] = Total_s[0]+1.
				round(Total_s[0])
				#print nTaus
				if nTaus[0] == 1:
					N_s[0] = N_s[0] + 1.
					round(N_s[0])

		#print N_s[0], Total_s[0]
			if isTau[0] and PARTICLETYPE == 'TAU0' and tauType[0] == 0:
				Total_s[0] = Total_s[0]+1.
				round(Total_s[0])
				if nTaus[0] == 1:
					N_s[0] = N_s[0] + 1.
					round(N_s[0])

			if isTau[0] and PARTICLETYPE == 'TAU1' and tauType[0] == 1:
				Total_s[0] = Total_s[0]+1.
				round(Total_s[0])
				if nTaus[0] == 1:
					N_s[0] = N_s[0] + 1.
					round(N_s[0])

			if isTau[0] and PARTICLETYPE == 'TAU2' and tauType[0] == 2:
				Total_s[0] = Total_s[0]+1.
				round(Total_s[0])
				if nTaus[0] == 1:
					N_s[0] = N_s[0] + 1.
					round(N_s[0])

			if isTau[0] and PARTICLETYPE == 'TAU3' and tauType[0] == 3:
				Total_s[0] = Total_s[0]+1.
				round(Total_s[0])
				if nTaus[0] == 1:
					N_s[0] = N_s[0] + 1.
					round(N_s[0])

			if isTau[0] and PARTICLETYPE == 'TAU4' and tauType[0] == 4:
				Total_s[0] = Total_s[0]+1.
				round(Total_s[0])
				if nTaus[0] == 1:
					N_s[0] = N_s[0] + 1.
					round(N_s[0])

			if isElectron[0] and PARTICLETYPE == 'ELECTRON':
				Total_s[0] = Total_s[0]+1.
				round(Total_s[0])
				if nTaus[0] == 1:
					N_s[0] = N_s[0] + 1.
					round(N_s[0])

		for entry in treebg:
			mcf0bg[0] = getattr(entry,GetBranchName(treebg,'MCf0')).CosTheta()
                        mcf1bg[0] = getattr(entry,GetBranchName(treebg,'MCf1')).CosTheta()
                        mcf2bg[0] = getattr(entry,GetBranchName(treebg,'MCf2')).CosTheta()
                        mcf3bg[0] = getattr(entry,GetBranchName(treebg,'MCf3')).CosTheta()

			mcfbglist = [ mcf0bg, mcf1bg, mcf2bg, mcf3bg ]
			mcfpdgbglist = [mcf0_pdgbg, mcf1_pdgbg, mcf2_pdgbg, mcf3_pdgbg ]
			#print mcfbglist
			#print mcfpdgbglist
			#print passAcceptance(mcfbglist, mcfpdgbglist)
			if passAcceptance(mcfbglist, mcfpdgbglist) == False:
				continue

			if True: #this is background
				Total_b[0] = Total_b[0]+1.
				round(Total_b[0])
				#print nTausBG[0]
				if nTausBG[0] >= 1:
					N_b[0] = N_b[0] + 1.
					round(N_b[0])

#		break
		
		eff_s[0] = (N_s[0]/Total_s[0])
		treeN[0] =(treedetails[treedetails_itr][0])
		searchCone[0] = (treedetails[treedetails_itr][1])
		isoCone[0] = (treedetails[treedetails_itr][2])
		isoE[0] =(treedetails[treedetails_itr][3])			
		eff_b[0] =(N_b[0]/Total_b[0])
		RR[0] = (1. - eff_b[0])
		p[0] = (N_s[0] / (N_s[0] + N_b[0]))
		effp[0] = eff_s[0] * p[0]
	#	Emax_s[0] =getmaxenergy( nTaus[0], tauTLV)
	#	Emax_b[0] =getmaxenergy( nTausBG[0], tauTLVBG)
		print eff_s[0], eff_b[0], RR[0], treeN[0], searchCone[0], isoCone[0], isoE[0], p[0], effp[0], N_s[0], N_b[0], Total_s[0], Total_b[0] #, Emax_s[0], Emax_b[0]
		outputTree.Fill()
		treedetails_itr += 1
		
	
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
		





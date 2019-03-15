


#SUBSET = ['S1', 'S2', 'B1']
#PARTICLETYPE = ['MUON', 'ELECTRON', 'TAU0', 'TAU1', 'TAU2', 'TAU3', 'TAU4', 'BG1']


SUBSET="S1"
PTYPE="MUON"
BTYPE="B1"
nfiles=39
ntrees=50

root -l
.x Efficiency_Rejection.C(${SUBSET},${PTYPE},${BTYPE},${nfiles},${ntrees})
.q


SUBSET="S1"
PTYPE="TAU0"
root -l
.x Efficiency_Rejection.C(${SUBSET},${PTYPE},${BTYPE},${nfiles},${ntrees})
.q

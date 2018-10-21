#!/bin/sh
#
# Run RobustResolution tests
#
date
# Might as well recompile it here too
g++ -g -o example example.cpp `root-config --cflags --glibs`

# Run five standard configurations. Three ToyMC and the two PandoraPFO based data-sets.
# Using all 14 metrics (the pair-wise ones are not fast).
#
# For serious work you will likely need more like 10,000 toy experiments (rather than 100 as here)
#
#
./example 0 100 500 54321 > SimpleGaussianToyMC-100.output
./example 1 100 500 54322 > DoubleGaussianToyMC91-100.output
./example 2 100 500 54323 > DoubleGaussianToyMC500-100.output
./example -1 1 1 54324 > Reco_uds91GeV.output
./example -2 1 1 54324 > Reco_uds500GeV.output

date

exit

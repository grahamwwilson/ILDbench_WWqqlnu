

import os


DATASET = '4f_WW_semi_LR'


command = os.popen('ls ./steeringMacros/TauFinderSteeringS1LR/' ).read()

print command


command = os.popen('echo YES')

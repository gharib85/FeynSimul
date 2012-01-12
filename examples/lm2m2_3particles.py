# Does a run with the lm2m2 potential for 3 particles.

import os
import sys
import math
import numpy as np
from datetime import datetime
from time import time
from time import sleep
import csv

sys.path.append(sys.path[0] + "/../src/")
from run_params import *
from host import *
from pimc_utils import *

sys.path.append(sys.path[0] + "/../src/physical_systems/")
from lm2m2_3part import *

experimentName="lm2m2_3part/"

RP = RunParams()
RP.nbrOfWalkers = 64
RP.N = 1024 * 64
RP.getOperator = True
RP.enablePathShift = False
RP.enableBisection = True
RP.enableSingleNodeMove = False
RP.enableGlobalPath = True
RP.enableGlobalOldPath = True
RP.enableParallelizePath = True
RP.returnBinCounts = False
RP.beta = 1000
RP.nbrOfWalkersPerWorkGroup = 4


# Time to run simul
endTime = 60 * 60 * 24 * 14

# How often to save paths.
savePathsInterval = 3000
systemClass = Lm2m2_3part()
RP.operators=(systemClass.energyOp,systemClass.meanSquaredRadiusOp,systemClass.meanRadiusOp)


def opRunsFormula(N, S):
    return max(2 ** 10 / 2 ** S, 1)

def mStepsPerOPRun(N, S):
    return 10

def runsPerN(N, S):
    return max(RP.N / 8, 10)


# Run the simulation function
modN(RP, savePathsInterval, systemClass, endTime, "lm2m2_3part", opRunsFormula
     , mStepsPerOPRun, runsPerN)
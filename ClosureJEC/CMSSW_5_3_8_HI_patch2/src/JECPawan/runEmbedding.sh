#!/bin/sh
root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeV.C++(15,"ppb", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeV.C++(30,"ppb", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeV.C++(50,"ppb", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeV.C++(80,"ppb", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeV.C++(120,"ppb", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeV.C++(170, "ppb", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeV.C++(220,"ppb", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeV.C++(280,"ppb",0);
.q
EOF
#root -l -b<<EOF
#gSystem->Load("../HiForest_V3/hiForest_h.so")
#.x IndResponse5TeV.C++(370,"ppb",0);
#.q
#EOF

rm -f /net/hidsk0001/d00/scratch/maoyx/pPb/ClosureJEC/CMSSW_5_3_8_HI_patch2/src/JECPawan/Output/pPbResponse_ppb_HP04_KurtForest_JECv8_merged.root
hadd /net/hidsk0001/d00/scratch/maoyx/pPb/ClosureJEC/CMSSW_5_3_8_HI_patch2/src/JECPawan/Output/pPbResponse_pPb_HP04_KurtForest_JECv8_merged.root /net/hidsk0001/d00/scratch/maoyx/pPb/ClosureJEC/CMSSW_5_3_8_HI_patch2/src/JECPawan/Output/Response_ppb_HP04_KurtForest_JECv8_pT*.root

#!/bin/sh
root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeV.C++(15,"pbp", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeV.C++(30,"pbp", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeV.C++(50,"pbp", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeV.C++(80,"pbp", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeV.C++(120,"pbp", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeV.C++(170, "pbp", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeV.C++(220,"pbp", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeV.C++(280,"pbp",0);
.q
EOF
root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeV.C++(370,"pbp",0);
.q
EOF

rm -f /net/hidsk0001/d00/scratch/maoyx/pPb/ClosureJEC/CMSSW_5_3_8_HI_patch2/src/JECPawan/Output/PbpResponse_HIJINGPYTHIA_merged.root
hadd /net/hidsk0001/d00/scratch/maoyx/pPb/ClosureJEC/CMSSW_5_3_8_HI_patch2/src/JECPawan/Output/PbpResponse_HIJINGPYTHIA_merged.root /net/hidsk0001/d00/scratch/maoyx/pPb/ClosureJEC/CMSSW_5_3_8_HI_patch2/src/JECPawan/Output/Response_pbp_pT*.root

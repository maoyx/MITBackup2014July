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
.x IndResponse5TeV.C++(170,"pbp", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeV.C++(220,"pbp", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeV.C++(280,"pbp", 0);
.q
EOF

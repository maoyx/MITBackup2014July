#!/bin/sh
root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeVOnFlyForest.C++(15,"pbp", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeVOnFlyForest.C++(30,"pbp", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeVOnFlyForest.C++(50,"pbp", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeVOnFlyForest.C++(80,"pbp", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeVOnFlyForest.C++(120,"pbp", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeVOnFlyForest.C++(170,"pbp", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeVOnFlyForest.C++(220,"pbp", 0);
.q
EOF

root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse5TeVOnFlyForest.C++(280,"pbp", 0);
.q
EOF

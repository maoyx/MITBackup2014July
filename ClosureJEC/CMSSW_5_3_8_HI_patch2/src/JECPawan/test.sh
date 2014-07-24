#!/bin/sh
root -l -b<<EOF
gSystem->Load("../HiForest_V3/hiForest_h.so")
.x IndResponse.C++(120,"pp", 0);
.q
EOF


#!/bin/bash

# runScript.sh
# 
#
export PTHAT=$1
export PTMAX=$2

echo "Processing..."
echo "root -l -b -q anaGenJetJS.C+"

#Do the analysis
root -b > run.log <<EOF
.L anaGenJetJS.C+
anaGenJetJS()
.q
EOF

echo "Done!"

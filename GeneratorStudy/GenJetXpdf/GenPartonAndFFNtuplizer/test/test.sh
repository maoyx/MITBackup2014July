cd /net/hidsk0001/d00/scratch/maoyx/GeneratorStudy/PYTHIA/CMSSW_5_3_8_HI_patch2/src
#cmsenv
eval `scramv1 runtime -sh`

cd /net/hidsk0001/d00/scratch/maoyx/GeneratorStudy/PYTHIA/CMSSW_5_3_8_HI_patch2/src/GenJetXpdf/GenPartonAndFFNtuplizer/test

export PTMIN=30
export PTMAX=50

echo "Processing..."
echo "root -l -b -q Ntuplizer_JetsPYTHIA_Z2.C+"

root -b > runjob.log <<EOF
.L Ntuplizer_JetsPYTHIA_Z2.C+
Ntuplizer_JetsPYTHIA_Z2()
.q
EOF

 echo "Done! for pthat =${PTMIN}"

export PTMIN=50
export PTMAX=80

echo "Processing..."
echo "root -l -b -q Ntuplizer_JetsPYTHIA_Z2.C+"

root -b > runjob.log <<EOF
.L Ntuplizer_JetsPYTHIA_Z2.C+
Ntuplizer_JetsPYTHIA_Z2()
.q
EOF
 echo "Done! for pthat =${PTMIN}"
export PTMIN=80
export PTMAX=120

echo "Processing..."
echo "root -l -b -q Ntuplizer_JetsPYTHIA_Z2.C+"

root -b > runjob.log <<EOF
.L Ntuplizer_JetsPYTHIA_Z2.C+
Ntuplizer_JetsPYTHIA_Z2()
.q
EOF

 echo "Done! for pthat =${PTMIN}"

export PTMIN=120
export PTMAX=170

echo "Processing..."
echo "root -l -b -q Ntuplizer_JetsPYTHIA_Z2.C+"

root -b > runjob.log <<EOF
.L Ntuplizer_JetsPYTHIA_Z2.C+
Ntuplizer_JetsPYTHIA_Z2()
.q
EOF

export PTMIN=170
export PTMAX=230

echo "Processing..."
echo "root -l -b -q Ntuplizer_JetsPYTHIA_Z2.C+"

root -b > runjob.log <<EOF
.L Ntuplizer_JetsPYTHIA_Z2.C+
Ntuplizer_JetsPYTHIA_Z2()
.q
EOF

 echo "Done! for pthat =${PTMIN}"

export PTMIN=230
export PTMAX=300

echo "Processing..."
echo "root -l -b -q Ntuplizer_JetsPYTHIA_Z2.C+"

root -b > runjob.log <<EOF
.L Ntuplizer_JetsPYTHIA_Z2.C+
Ntuplizer_JetsPYTHIA_Z2()
.q
EOF

 echo "Done! for pthat =${PTMIN}"

export PTMIN=300
export PTMAX=380

echo "Processing..."
echo "root -l -b -q Ntuplizer_JetsPYTHIA_Z2.C+"

root -b > runjob.log <<EOF
.L Ntuplizer_JetsPYTHIA_Z2.C+
Ntuplizer_JetsPYTHIA_Z2()
.q
EOF


 echo "Done! for pthat =${PTMIN}"

export PTMIN=380
export PTMAX=-1

echo "Processing..."
echo "root -l -b -q Ntuplizer_JetsPYTHIA_Z2.C+"

root -b > runjob.log <<EOF
.L Ntuplizer_JetsPYTHIA_Z2.C+
Ntuplizer_JetsPYTHIA_Z2()
.q
EOF


 echo "Done! for pthat =${PTMIN}"

echo "Done all jobs!"

#echo "Copying output files to " $destination

cd /net/hidsk0001/d00/scratch/maoyx/GeneratorStudy/CMSSW_5_3_8_HI_patch2/src
#cmsenv
eval `scramv1 runtime -sh`

cd /net/hidsk0001/d00/scratch/maoyx/GeneratorStudy/CMSSW_5_3_8_HI_patch2/src/GenJetXpdf/GenPartonAndFFNtuplizer/test

export PTMIN=$1
export PTMAX=$2

echo "Processing..."
echo "root -l -b -q Ntuplizer_JetsPYTHIA_Z2.C+"

#Do the analysis
root -b > job.log <<EOF
.L Ntuplizer_JetsPYTHIA_Z2.C+
Ntuplizer_JetsPYTHIA_Z2()
.q
EOF


echo "Done!"


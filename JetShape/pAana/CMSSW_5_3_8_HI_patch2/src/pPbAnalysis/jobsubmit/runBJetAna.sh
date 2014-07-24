
source /osg/app/cmssoft/cms/cmsset_default.sh

cd /net/hidsk0001/d00/scratch/maoyx/JetShape/pAana/CMSSW_5_3_8_HI_patch2/src 
#cmsenv
eval `scramv1 runtime -sh`

cd /net/hidsk0001/d00/scratch/maoyx/JetShape/pAana/CMSSW_5_3_8_HI_patch2/src/pPbAnalysis

export PTHAT=$1
export PTMAX=$2

echo "Processing..."
echo "root -l -b -q anaBJet.C+"

#Do the analysis
root -b > runjob.log <<EOF
.L anaBJet.C+
anaBJet()
.q
EOF


echo "Done!"

#echo "Copying output files to " $destination

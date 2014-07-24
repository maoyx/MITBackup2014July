
source /osg/app/cmssoft/cms/cmsset_default.sh

cd /net/hidsk0001/d00/scratch/maoyx/JetShape/pAana/CMSSW_5_3_8_HI_patch2/src
eval `scramv1 runtime -sh`
cd /net/hidsk0001/d00/scratch/maoyx/trkeff/trkcorr
#cd /net/hidsk0001/d00/scratch/maoyx/trkeff/pPbEff
#cd /net/hidsk0001/d00/scratch/maoyx/trkeff/VertexWeightEff2013

export PTHAT=$1

echo "Processing..."
echo "root -l -b -q analyzeTrackingCorrection.C+"

#Do the analysis
root -b > runjob.log <<EOF
.L analyzeTrackingCorrection.C+
analyzeTrackingCorrection()
.q
EOF


echo "Done!"

#echo "Copying output files to " $destination

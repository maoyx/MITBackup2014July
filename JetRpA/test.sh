
source /osg/app/cmssoft/cms/cmsset_default.sh

cd /net/hidsk0001/d00/scratch/maoyx/JetShape/pAana/CMSSW_5_3_8_HI_patch2/src 
#cmsenv
eval `scramv1 runtime -sh`

cd /net/hidsk0001/d00/scratch/maoyx/pPb/12-017 

export TRIG=""



export PTHAT=220
export PTMAX=280

echo "Processing..."
echo "root -l -b -q anaDijetMassRpA.C+"

root -b > runjob.log <<EOF
.L anaDijetMassRpA.C+
anaDijetMassRpA()
.q
EOF
echo "Done for ${PTHAT}"

export PTHAT=280
export PTMAX=9999

echo "Processing..."
echo "root -l -b -q anaDijetMassRpA.C+"

root -b > runjob.log <<EOF
.L anaDijetMassRpA.C+
anaDijetMassRpA()
.q
EOF
echo "Done for ${PTHAT}"

echo "Done for all!"

#echo "Copying output files to " $destination

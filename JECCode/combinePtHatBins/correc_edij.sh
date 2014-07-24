: <<'END'
root -l -b <<EOF 
.L loadfwlite.C 
.x load_JEC.C 
.x weight_PtHatBins_DijetsV2.C+("/net/hisrv0001/home/icali/hadoop/Pythia/Z2/ppDijet_merged/pp276Dijet15_merged.root","/net/hidsk0001/d00/scratch/jrobles/dijet/dijet_pA2013pp/ppCorrected/pp15.root",30,2.03e-1,true)
.q
EOF
END
root -l -b <<EOF 
.L loadfwlite.C 
.x load_JEC.C 
.x weight_PtHatBins_DijetsV2.C+("/net/hisrv0001/home/icali/hadoop/Pythia/Z2/ppDijet_merged/pp276Dijet30_merged.root","/net/hidsk0001/d00/scratch/jrobles/dijet/dijet_pA2013pp/ppCorrected/pp30.root",50,1.079e-02,true)
.q
EOF
root -l -b <<EOF 
.L loadfwlite.C 
.x load_JEC.C 
.x weight_PtHatBins_DijetsV2.C+("/net/hisrv0001/home/icali/hadoop/Pythia/Z2/ppDijet_merged/pp276Dijet50_merged.root","/net/hidsk0001/d00/scratch/jrobles/dijet/dijet_pA2013pp/ppCorrected/pp50.root",80,1.021e-03,true)
.q
EOF
root -l -b <<EOF 
.L loadfwlite.C 
.x load_JEC.C 
.x weight_PtHatBins_DijetsV2.C+("/net/hisrv0001/home/icali/hadoop/Pythia/Z2/ppDijet_merged/pp276Dijet80_merged.root","/net/hidsk0001/d00/scratch/jrobles/dijet/dijet_pA2013pp/ppCorrected/pp80.root",120,6.4e-04,true)
.q
EOF
root -l -b <<EOF 
.L loadfwlite.C 
.x load_JEC.C 
.x weight_PtHatBins_DijetsV2.C+("/net/hisrv0001/home/icali/hadoop/Pythia/Z2/ppDijet_merged/pp276Dijet120_merged.root","/net/hidsk0001/d00/scratch/jrobles/dijet/dijet_pA2013pp/ppCorrected/pp120.root",170,9.913e-05,true)
.q
EOF
root -l -b <<EOF 
.L loadfwlite.C 
.x load_JEC.C 
.x weight_PtHatBins_DijetsV2.C+("/net/hisrv0001/home/icali/hadoop/Pythia/Z2/ppDijet_merged/pp276Dijet170_merged.root","/net/hidsk0001/d00/scratch/jrobles/dijet/dijet_pA2013pp/ppCorrected/pp170.root",200,1.128e-5,true)
.q
EOF
root -l -b <<EOF 
.L loadfwlite.C 
.x load_JEC.C 
.x weight_PtHatBins_DijetsV2.C+("/net/hisrv0001/home/icali/hadoop/Pythia/Z2/ppDijet_merged/pp276Dijet200_merged.root","/net/hidsk0001/d00/scratch/jrobles/dijet/dijet_pA2013pp/ppCorrected/pp200.root",99999,1.47e-06,true)
.q
EOF
rm -f /net/hidsk0001/d00/scratch/jrobles/dijet/dijet_pA2013pp/ppCorrected/dijet_pp_mergedpthatbins_2012MC.root
hadd /net/hidsk0001/d00/scratch/jrobles/dijet/dijet_pA2013pp/ppCorrected/dijet_pp_mergedpthatbins_2012MC.root /net/hidsk0001/d00/scratch/jrobles/dijet/dijet_pA2013pp/ppCorrected/pp*.root

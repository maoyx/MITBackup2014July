<<END
root -l -b <<EOF
.L loadfwlite.C
.x load.C 
.x weight_PtHatBins_DijetsV2.C+("/mnt/hadoop/cms/store/user/dgulhan/pPb_A03/Signal_Pythia15/HiForest2_v01_mergedv01/merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/pp15.root",30,2.03e-1,false)
.q
EOF
END
root -l -b <<EOF
.L loadfwlite.C
.x load.C 
.x weight_PtHatBins_DijetsV2.C+("/mnt/hadoop/cms/store/user/dgulhan/pPb_A03/Signal_Pythia30/HiForest2_v01_mergedv01/merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/pp30.root",50,1.079e-02,false)
.q
EOF
root -l -b <<EOF
.L loadfwlite.C
.x load.C 
.x weight_PtHatBins_DijetsV2.C+("/mnt/hadoop/cms/store/user/dgulhan/pPb_A03/Signal_Pythia50/HiForest2_v01_mergedv01/merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/pp50.root",80,1.021e-03,false)
.q
EOF
root -l -b <<EOF
.L loadfwlite.C
.x load.C 
#.x weight_PtHatBins_DijetsV2.C+("/net/hisrv0001/home/icali/hadoop/Pythia/Z2/ppDijet_merged/pp276Dijet80_merged.root","/net/hidsk0001/d00/scratch/jrobles/dijet_pA2013pp/pp80.root",120,9.913e-05,false)
.q
EOF
root -l -b <<EOF
.L loadfwlite.C
.x load.C 
#.x weight_PtHatBins_DijetsV2.C+("/net/hisrv0001/home/icali/hadoop/Pythia/Z2/ppDijet_merged/pp276Dijet120_merged.root","/net/hidsk0001/d00/scratch/jrobles/dijet_pA2013pp/pp120.root",170,1.128e-5,false)
.q
EOF
root -l -b <<EOF
.L loadfwlite.C
.x load.C 
#.x weight_PtHatBins_DijetsV2.C+("/net/hisrv0001/home/icali/hadoop/Pythia/Z2/ppDijet_merged/pp276Dijet170_merged.root","/net/hidsk0001/d00/scratch/jrobles/dijet_pA2013pp/pp170.root",200,1.47e-06,false)
.q
EOF
root -l -b <<EOF
.L loadfwlite.C
.x load.C 
#.x weight_PtHatBins_DijetsV2.C+("/net/hisrv0001/home/icali/hadoop/Pythia/Z2/ppDijet_merged/pp276Dijet200_merged.root","/net/hidsk0001/d00/scratch/jrobles/dijet_pA2013pp/pp200.root",9999,5.31e-07,false)
.q
EOF
rm -f /net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/JEC/dijet_pp_mergedpthatbins_2012MC.root
hadd /net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/JEC/dijet_pp_mergedpthatbins_2012MC.root /net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/pp*.root
cd ../JEC
ln -sf /net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/dijet_pp_mergedpthatbins_2012MC.root dijet_pp_mergedpthatbins_2012MC.root

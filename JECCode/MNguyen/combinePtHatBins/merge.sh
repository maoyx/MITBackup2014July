root -l -b <<EOF
.L loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_DijetsV2.C+("/mnt/hadoop/cms/store/user/dgulhan/pPb/HP02/prod08/Hijing_Pythia_pt30/HiForest2_v02_merged01/merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/pp30.root",50,1.079e-02,false)
.q
EOF
root -l -b <<EOF
.L loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_DijetsV2.C+("/mnt/hadoop/cms/store/user/dgulhan/pPb/HP02/prod08/Hijing_Pythia_pt50/HiForest2_v02_merged01/merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/pp50.root",80,1.021e-03,false)
.q
EOF
root -l -b <<EOF
.L loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_DijetsV2.C+("/mnt/hadoop/cms/store/user/dgulhan/pPb/HP02/prod08/Hijing_Pythia_pt80/HiForest2_v02_merged01/merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/pp80.root",120, 9.913e-05,false)
.q
EOF
root -l -b <<EOF
.L loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_DijetsV2.C+("/mnt/hadoop/cms/store/user/dgulhan/pPb/HP02/prod08/Hijing_Pythia_pt120/HiForest2_v02_merged01/merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/pp120.root",170,1.128e-5,false)
.q
EOF
root -l -b <<EOF
.L loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_DijetsV2.C+("/mnt/hadoop/cms/store/user/dgulhan/pPb/HP02/prod08/Hijing_Pythia_pt170/HiForest2_v02_merged01/merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/pp170.root",9999,1.47e-06,false)
.q
EOF

hadd /net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/dijet_pp_mergedpthatbins_2012MC.root /net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/pp*.root

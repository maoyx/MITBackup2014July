root -l -b <<EOF
.x loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_DijetsV2.C+("/mnt/hadoop/cms/store/user/dgulhan/pPb_A03/Signal_Pythia15/JEC_merged02/merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/pp15.root",30,2.03e-1,false)
.q
EOF
root -l -b <<EOF
.x loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_DijetsV2.C+("/mnt/hadoop/cms/store/user/dgulhan/pPb_A03/Signal_Pythia30/JEC_merged02/merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/pp30.root", 9999,1.079e-02,false)
.q
EOF
root -l -b <<EOF
.L loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_DijetsV2.C+("/mnt/hadoop/cms/store/user/dgulhan/pPb_A03/Signal_Pythia50/JEC_merged02/merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/pp50.root",80,1.021e-03,false)
.q
EOF
root -l -b <<EOF
.L loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_DijetsV2.C+("/mnt/hadoop/cms/store/user/dgulhan/pPb_A03/Signal_Pythia80/JEC_merged02/merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/pp80.root",120, 9.913e-05,false)
.q
EOF
rm -f /net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/JEC/dijet_pp_mergedpthatbins_2012MC.root
hadd /net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/JEC/dijet_pp_mergedpthatbins_2012MC.root /net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/pp*.root

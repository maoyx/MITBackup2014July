root -l -b <<EOF
.L loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_JetsR3_5.C+("/mnt/hadoop/cms/store/user/dgulhan/HIJING_GEN-SIM_revrese_betap/Hijing_reverse_Dijet15_5p02TeV_FOREST_v1_merged2/pt15_HIJING_GEN-SIM_revrese_betap_merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/corrPbpJet15.root",30,5.335E-01,true)
.q
EOF
root -l -b <<EOF
.L loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_JetsR3_5.C+("/mnt/hadoop/cms/store/user/dgulhan/HIJING_GEN-SIM_revrese_betap/Hijing_reverse_Dijet30_5p02TeV_FOREST_v1_merged2/pt30_HIJING_GEN-SIM_revrese_betap_merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/corrPbpJet30.root",50,3.378E-02,true)
.q
EOF
root -l -b <<EOF
.L loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_JetsR3_5.C+("/mnt/hadoop/cms/store/user/dgulhan/HIJING_GEN-SIM_revrese_betap/Hijing_reverse_Dijet50_5p02TeV_FOREST_v1_merged2/pt50_HIJING_GEN-SIM_revrese_betap_merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/corrPbpJet50.root",80,3.778E-03,true)
.q
EOF
root -l -b <<EOF
.L loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_JetsR3_5.C+("/mnt/hadoop/cms/store/user/dgulhan/HIJING_GEN-SIM_revrese_betap/Hijing_reverse_Dijet80_5p02TeV_FOREST_v1_merged2/pt80_HIJING_GEN-SIM_revrese_betap_merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/corrPbpJet80.root",120, 4.412E-04,true)
.q
EOF
root -l -b <<EOF
.L loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_JetsR3_5.C+("/mnt/hadoop/cms/store/user/dgulhan/HIJING_GEN-SIM_revrese_betap/Hijing_reverse_Dijet120_5p02TeV_FOREST_v1_merged2/pt120_HIJING_GEN-SIM_revrese_betap_merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/corrPbpJet120.root",170,6.147E-05,true)
.q
EOF
root -l -b <<EOF
.L loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_JetsR3_5.C+("/mnt/hadoop/cms/store/user/dgulhan/HIJING_GEN-SIM_revrese_betap/Hijing_reverse_Dijet170_5p02TeV_FOREST_v1_merged2/pt170_HIJING_GEN-SIM_revrese_betap_merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/corrPbpJet170.root",220,1.018E-05,true)
.q
EOF
root -l -b <<EOF
.L loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_JetsR3_5.C+("/mnt/hadoop/cms/store/user/dgulhan/HIJING_GEN-SIM_revrese_betap/Hijing_reverse_Dijet220_5p02TeV_FOREST_v1_merged2/pt220_HIJING_GEN-SIM_revrese_betap_merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/corrPbpJet220.root",280,2.477E-06,true)
.q
EOF
root -l -b <<EOF
.L loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_JetsR3_5.C+("/mnt/hadoop/cms/store/user/dgulhan/HIJING_GEN-SIM_revrese_betap/Hijing_reverse_Dijet280_5p02TeV_FOREST_v1_merged2/pt280_HIJING_GEN-SIM_revrese_betap_merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/corrPbpJet280.root",370,6.160E-07,true)
.q
EOF
root -l -b <<EOF
.L loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_JetsR3_5.C+("/mnt/hadoop/cms/store/user/dgulhan/HIJING_GEN-SIM_revrese_betap/Hijing_reverse_Dijet370_5p02TeV_FOREST_v1_merged2/pt370_HIJING_GEN-SIM_revrese_betap_merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/corrPbpJet370.root",9999,1.088E-07,true)
.q
EOF

rm -f /net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/jet_CorrPbp502_mergedpthatbins_YueShiJECv16.root
hadd /net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/jet_CorrPbp502_mergedpthatbins_YueShiJECv16.root /net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/corrPbpJet*.root




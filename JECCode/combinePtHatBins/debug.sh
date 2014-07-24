root -l -b <<EOF
.L loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_AllJet.C+("/mnt/hadoop/cms/store/user/dgulhan/HIJING_GEN-SIM_revrese_betap/Hijing_reverse_Dijet15_5p02TeV_FOREST_v1_merged2/pt15_HIJING_GEN-SIM_revrese_betap_merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/corrPbpJet15.root",30,5.335E-01,true)
.q
EOF

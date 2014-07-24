root -l -b <<EOF
.L loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_JetsR3_5.C+("/mnt/hadoop/cms/store/user/kjung/Pbp_ForestProdApr14_v3_Merged/Pbp_ForestProdApr14_pthat15_v3output0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/PbpJet15v2.root",30,5.335E-01,false)
.q
EOF

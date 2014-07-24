root -l -b <<EOF
.L loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_DijetsV2.C+("/mnt/hadoop/cms/store/user/dgulhan/pPb_A03/Signal_Pythia170/JEC_merged02/merged_forest_0.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/pp50.root",9999,1.47e-06,false)
.q
EOF


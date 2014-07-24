root -l -b <<EOF
.L loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_IncJet.C+("/mnt/hadoop/cms/store/user/maoyx/hiForest/PP2013_HiForest_PromptReco_JsonPP_Jet80_PPReco_forestv82.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/276CorrppData.root",300,2.034E-01,true)
.q
EOF


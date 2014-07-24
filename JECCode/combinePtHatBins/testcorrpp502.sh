root -l -b <<EOF
.L loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_IncJet.C+("/mnt/hadoop/cms/store/user/kjung/pPbForest/Signal_Pythia_pt30/merged/pt30_HP04_prod16_v77_merged_forest_Sum.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/TestCorrppJet30.root",9999,3.378E-02,true)

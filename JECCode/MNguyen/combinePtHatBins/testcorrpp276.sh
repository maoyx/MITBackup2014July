root -l -b <<EOF
.L loadfwlite.C
.x load_JEC.C 
.x weight_PtHatBins_IncJet.C+("/mnt/hadoop/cms/store/user/dgulhan/pp2013/P01/prod22/Signal_Pythia_pt30/HiForest_v81/hiforestv81_QCD-pthat30_2p76TeV_pythia6_RECO_10_1_kR3.root","/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/combinePtHatBins/TestCorrppJet30.root",9999,1.075E-02,true)

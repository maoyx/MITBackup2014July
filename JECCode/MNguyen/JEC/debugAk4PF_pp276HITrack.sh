#! /bin/sh -f
echo "Running for non-PU jet........... "
# Generate the response
jet_response_analyzer_x  largeEta_binning_ptRebin.config -input jet_pp276HITrack_mergedpthatbins_2013MC.root -useweight true -algs ak4PFJetAnalyzer -drmax 0.4 -output jra_hiF_ak4PF_dijet.root

# Get the l3 corrections
jet_l3_correction_x -input jra_hiF_ak4PF_dijet.root -era JEC_dijet  -batch true -formats pdf -algs ak4PFJetAnalyzer -output jra_hiF_ak4PF_l3_dijet.root
# use the l3 output and response output to get l2 corrections
jet_l2_correction_x -input jra_hiF_ak4PF_dijet.root -l3input jra_hiF_ak4PF_l3_dijet.root -era JEC_dijet -batch true -formats pdf -algs ak4PFJetAnalyzer -output jra_hiF_ak4PF_l2_dijet.root
#draw l2 corrections
jet_draw_l2_correction_x -alg ak4PFJetAnalyzer -filename jra_hiF_ak4PF_l2_dijet.root -outputDir /net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/JEC/testCorrections/ -outputFormat .pdf

# draw l2l3 corrections
jet_draw_corrections_x -algs ak4pf -path "" -outputDir /net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/JEC/testCorrections/ -era JEC_dijet -useL2Cor true -useL3Cor true -outputFormat .pdf

# draw pt closure
jet_draw_closure_pt_x -algs ak4pf -path "" -outputDir /net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/MNguyen/JEC/testCorrections/ -era JEC_dijet -outputFormat .pdf




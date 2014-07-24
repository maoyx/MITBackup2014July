#! /bin/sh -f
echo "Running for dijet........... "
# Generate the response
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2013MC.root -useweight true -algs ak2PFJetAnalyzer -drmax 0.2 -output jra_hiF_ak2PF_dijet.root
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2013MC.root -useweight true -algs ak3PFJetAnalyzer -drmax 0.3 -output jra_hiF_ak3PF_dijet.root
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2013MC.root -useweight true -algs ak4PFJetAnalyzer -drmax 0.4 -output jra_hiF_ak4PF_dijet.root
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2013MC.root -useweight true -algs ak5PFJetAnalyzer -drmax 0.5 -output jra_hiF_ak5PF_dijet.root
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2013MC.root -useweight true -algs ak6PFJetAnalyzer -drmax 0.6 -output jra_hiF_ak6PF_dijet.root
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2013MC.root -useweight true -algs ak1CaloJetAnalyzer -drmax 0.1 -output jra_hiF_ak1Calo_dijet.root
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2013MC.root -useweight true -algs ak2CaloJetAnalyzer -drmax 0.2 -output jra_hiF_ak2Calo_dijet.root
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2013MC.root -useweight true -algs ak3CaloJetAnalyzer -drmax 0.3 -output jra_hiF_ak3Calo_dijet.root
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2013MC.root -useweight true -algs ak4CaloJetAnalyzer -drmax 0.4 -output jra_hiF_ak4Calo_dijet.root
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2013MC.root -useweight true -algs ak5CaloJetAnalyzer -drmax 0.5 -output jra_hiF_ak5Calo_dijet.root
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2013MC.root -useweight true -algs ak6CaloJetAnalyzer -drmax 0.6 -output jra_hiF_ak6Calo_dijet.root
# Get the l3 corrections
jet_l3_correction_x -input jra_hiF_ak2PF_dijet.root -era JEC_ak2PF_dijet  -batch true -formats pdf -algs ak2PFJetAnalyzer -output jra_hiF_ak2PF_l3_dijet.root
jet_l3_correction_x -input jra_hiF_ak3PF_dijet.root -era JEC_ak3PF_dijet  -batch true -formats pdf -algs ak3PFJetAnalyzer -output jra_hiF_ak3PF_l3_dijet.root
jet_l3_correction_x -input jra_hiF_ak4PF_dijet.root -era JEC_ak4PF_dijet  -batch true -formats pdf -algs ak4PFJetAnalyzer -output jra_hiF_ak4PF_l3_dijet.root
jet_l3_correction_x -input jra_hiF_ak5PF_dijet.root -era JEC_ak5PF_dijet  -batch true -formats pdf -algs ak5PFJetAnalyzer -output jra_hiF_ak5PF_l3_dijet.root
jet_l3_correction_x -input jra_hiF_ak6PF_dijet.root -era JEC_ak6PF_dijet  -batch true -formats pdf -algs ak6PFJetAnalyzer -output jra_hiF_ak6PF_l3_dijet.root
jet_l3_correction_x -input jra_hiF_ak1Calo_dijet.root -era JEC_ak1Calo_dijet -batch true -formats pdf -algs ak1CaloJetAnalyzer -output jra_hiF_ak1Calo_l3_dijet.root
jet_l3_correction_x -input jra_hiF_ak2Calo_dijet.root -era JEC_ak2Calo_dijet -batch true -formats pdf -algs ak2CaloJetAnalyzer -output jra_hiF_ak2Calo_l3_dijet.root
jet_l3_correction_x -input jra_hiF_ak3Calo_dijet.root -era JEC_ak3Calo_dijet -batch true -formats pdf -algs ak3CaloJetAnalyzer -output jra_hiF_ak3Calo_l3_dijet.root
jet_l3_correction_x -input jra_hiF_ak4Calo_dijet.root -era JEC_ak4Calo_dijet -batch true -formats pdf -algs ak4CaloJetAnalyzer -output jra_hiF_ak4Calo_l3_dijet.root
jet_l3_correction_x -input jra_hiF_ak5Calo_dijet.root -era JEC_ak5Calo_dijet -batch true -formats pdf -algs ak5CaloJetAnalyzer -output jra_hiF_ak5Calo_l3_dijet.root
jet_l3_correction_x -input jra_hiF_ak6Calo_dijet.root -era JEC_ak6Calo_dijet -batch true -formats pdf -algs ak6CaloJetAnalyzer -output jra_hiF_ak6Calo_l3_dijet.root

# use the l3 output and response output to get l2 corrections
jet_l2_correction_x -input jra_hiF_ak2PF_dijet.root -l3input jra_hiF_ak2PF_l3_dijet.root -era JEC_ak2PF_dijet -batch true -formats pdf -algs ak2PFJetAnalyzer -output jra_hiF_ak2PF_l2_dijet.root
jet_l2_correction_x -input jra_hiF_ak3PF_dijet.root -l3input jra_hiF_ak3PF_l3_dijet.root -era JEC_ak3PF_dijet -batch true -formats pdf -algs ak3PFJetAnalyzer -output jra_hiF_ak3PF_l2_dijet.root
jet_l2_correction_x -input jra_hiF_ak4PF_dijet.root -l3input jra_hiF_ak4PF_l3_dijet.root -era JEC_ak4PF_dijet -batch true -formats pdf -algs ak4PFJetAnalyzer -output jra_hiF_ak4PF_l2_dijet.root
jet_l2_correction_x -input jra_hiF_ak5PF_dijet.root -l3input jra_hiF_ak5PF_l3_dijet.root -era JEC_ak5PF_dijet -batch true -formats pdf -algs ak5PFJetAnalyzer -output jra_hiF_ak5PF_l2_dijet.root
jet_l2_correction_x -input jra_hiF_ak6PF_dijet.root -l3input jra_hiF_ak6PF_l3_dijet.root -era JEC_ak6PF_dijet -batch true -formats pdf -algs ak6PFJetAnalyzer -output jra_hiF_ak6PF_l2_dijet.root
jet_l2_correction_x -input jra_hiF_ak1Calo_dijet.root -l3input jra_hiF_ak1Calo_l3_dijet.root -era JEC_ak1Calo_dijet -batch true -formats pdf -algs ak1CaloJetAnalyzer -output jra_hiF_ak1Calo_l2_dijet.root
jet_l2_correction_x -input jra_hiF_ak2Calo_dijet.root -l3input jra_hiF_ak2Calo_l3_dijet.root -era JEC_ak2Calo_dijet -batch true -formats pdf -algs ak2CaloJetAnalyzer -output jra_hiF_ak2Calo_l2_dijet.root
jet_l2_correction_x -input jra_hiF_ak3Calo_dijet.root -l3input jra_hiF_ak3Calo_l3_dijet.root -era JEC_ak3Calo_dijet -batch true -formats pdf -algs ak3CaloJetAnalyzer -output jra_hiF_ak3Calo_l2_dijet.root
jet_l2_correction_x -input jra_hiF_ak4Calo_dijet.root -l3input jra_hiF_ak4Calo_l3_dijet.root -era JEC_ak4Calo_dijet -batch true -formats pdf -algs ak4CaloJetAnalyzer -output jra_hiF_ak4Calo_l2_dijet.root
jet_l2_correction_x -input jra_hiF_ak5Calo_dijet.root -l3input jra_hiF_ak5Calo_l3_dijet.root -era JEC_ak5Calo_dijet -batch true -formats pdf -algs ak5CaloJetAnalyzer -output jra_hiF_ak5Calo_l2_dijet.root
jet_l2_correction_x -input jra_hiF_ak6Calo_dijet.root -l3input jra_hiF_ak6Calo_l3_dijet.root -era JEC_ak6Calo_dijet -batch true -formats pdf -algs ak6CaloJetAnalyzer -output jra_hiF_ak6Calo_l2_dijet.root

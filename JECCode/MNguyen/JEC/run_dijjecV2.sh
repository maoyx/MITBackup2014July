#! /bin/sh -f
echo "Running for dijet........... "
# Generate the response
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2012MC.root -useweight true -algs ak1PFJetAnalyzer -output jra_hiF_ak1PF_dijet.root
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2012MC.root -useweight true -algs ak2PFJetAnalyzer -output jra_hiF_ak2PF_dijet.root
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2012MC.root -useweight true -algs ak3PFJetAnalyzer -output jra_hiF_ak3PF_dijet.root
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2012MC.root -useweight true -algs ak4PFJetAnalyzer -output jra_hiF_ak4PF_dijet.root
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2012MC.root -useweight true -algs ak5PFJetAnalyzer -output jra_hiF_ak5PF_dijet.root
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2012MC.root -useweight true -algs ak6PFJetAnalyzer -output jra_hiF_ak6PF_dijet.root
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2012MC.root -useweight true -algs ak1CaloJetAnalyzer -output jra_hiF_ak1Calo_dijet.root
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2012MC.root -useweight true -algs ak2CaloJetAnalyzer -output jra_hiF_ak2Calo_dijet.root 
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2012MC.root -useweight true -algs ak3CaloJetAnalyzer -output jra_hiF_ak3Calo_dijet.root
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2012MC.root -useweight true -algs ak4CaloJetAnalyzer -output jra_hiF_ak4Calo_dijet.root
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2012MC.root -useweight true -algs ak5CaloJetAnalyzer -output jra_hiF_ak5Calo_dijet.root
jet_response_analyzer_x  fine_binning_ptRebin_noHF_noLowPt.config -input dijet_pp_mergedpthatbins_2012MC.root -useweight true -algs ak6CaloJetAnalyzer -output jra_hiF_ak6Calo_dijet.root
jet_response_analyzer_x  fine_binning_ptRebin.config -input dijet_pp_mergedpthatbins_2012MC.root -useweight true -algs icPu5JetAnalyzer -output jra_hiF_icPu5_dijet.root

# Get the l3 corrections
jet_l3_correction_x -input jra_hiF_ak1PF_dijet.root -era JEC_ak1PF_dijet  -batch true -formats pdf -algs ak1PFJetAnalyzer -output jra_hiF_ak1PF_l3_dijet.root
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
jet_l3_correction_x -input jra_hiF_icPu5_dijet.root -era JEC_icPu5_dijet -batch true -formats pdf -algs icPu5JetAnalyzer -output jra_hiF_icPu5_l3_dijet.root

# use the l3 output and response output to get l2 corrections
jet_l2_correction_x -input jra_hiF_ak1PF_dijet.root -l3input jra_hiF_ak1PF_l3_dijet.root -era JEC_ak1PF_dijet -batch true -formats pdf -algs ak1PFJetAnalyzer -output jra_hiF_ak1PF_l2_dijet.root
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
jet_l2_correction_x -input jra_hiF_icPu5_dijet.root -l3input jra_hiF_icPu5_l3_dijet.root -era JEC_icPu5_dijet -batch true -formats pdf -algs icPu5JetAnalyzer -output jra_hiF_icPu5_l2_dijet.root


/bin/mv -f *.txt jra*.root dijet/.
/bin/mv -f L3*.pdf pdffiles/dijet/L3Corrections/.

# reads the txt files                                                                                                                                                                                                    
jet_draw_corrections_x -algs ak1PF -era JEC_ak1PF_dijet -useL2Cor true -useL3Cor true -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputFormat .pdf -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/Corrections/
jet_draw_corrections_x -algs ak2PF -era JEC_ak2PF_dijet -useL2Cor true -useL3Cor true -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputFormat .pdf -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/Corrections/
jet_draw_corrections_x -algs ak3PF -era JEC_ak3PF_dijet -useL2Cor true -useL3Cor true -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputFormat .pdf -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/Corrections/
jet_draw_corrections_x -algs ak4PF -era JEC_ak4PF_dijet -useL2Cor true -useL3Cor true -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputFormat .pdf -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/Corrections/
jet_draw_corrections_x -algs ak5PF -era JEC_ak5PF_dijet -useL2Cor true -useL3Cor true -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputFormat .pdf -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/Corrections/
jet_draw_corrections_x -algs ak6PF -era JEC_ak6PF_dijet -useL2Cor true -useL3Cor true -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputFormat .pdf -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/Corrections/
jet_draw_corrections_x -algs ak1Calo -era JEC_ak1Calo_dijet -useL2Cor true -useL3Cor true -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputFormat .pdf -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/Corrections/
jet_draw_corrections_x -algs ak2Calo -era JEC_ak2Calo_dijet -useL2Cor true -useL3Cor true -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputFormat .pdf -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/Corrections/
jet_draw_corrections_x -algs ak3Calo -era JEC_ak3Calo_dijet -useL2Cor true -useL3Cor true -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputFormat .pdf -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/Corrections/
jet_draw_corrections_x -algs ak4Calo -era JEC_ak4Calo_dijet -useL2Cor true -useL3Cor true -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputFormat .pdf -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/Corrections/
jet_draw_corrections_x -algs ak5Calo -era JEC_ak5Calo_dijet -useL2Cor true -useL3Cor true -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputFormat .pdf -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/Corrections/
jet_draw_corrections_x -algs ak6Calo -era JEC_ak6Calo_dijet -useL2Cor true -useL3Cor true -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputFormat .pdf -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/Corrections/
jet_draw_corrections_x -algs icPu5  -era JEC_icPu5_dijet -useL2Cor true -useL3Cor true -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputFormat .pdf -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/Corrections/

# l2 corrections
jet_draw_l2_correction_x -filename jra_hiF_ak1PF_l2_dijet.root -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/L2Corrections/ -alg ak1PFJetAnalyzer  -outputFormat .pdf
jet_draw_l2_correction_x -filename jra_hiF_ak2PF_l2_dijet.root -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/L2Corrections/ -alg ak2PFJetAnalyzer  -outputFormat .pdf
jet_draw_l2_correction_x -filename jra_hiF_ak3PF_l2_dijet.root -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/L2Corrections/ -alg ak3PFJetAnalyzer  -outputFormat .pdf
jet_draw_l2_correction_x -filename jra_hiF_ak4PF_l2_dijet.root -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/L2Corrections/ -alg ak4PFJetAnalyzer  -outputFormat .pdf
jet_draw_l2_correction_x -filename jra_hiF_ak5PF_l2_dijet.root -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/L2Corrections/ -alg ak5PFJetAnalyzer  -outputFormat .pdf
jet_draw_l2_correction_x -filename jra_hiF_ak6PF_l2_dijet.root -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/L2Corrections/ -alg ak6PFJetAnalyzer  -outputFormat .pdf
jet_draw_l2_correction_x -filename jra_hiF_ak1Calo_l2_dijet.root -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/L2Corrections/ -alg ak1CaloJetAnalyzer  -outputFormat .pdf
jet_draw_l2_correction_x -filename jra_hiF_ak2Calo_l2_dijet.root -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/L2Corrections/ -alg ak2CaloJetAnalyzer  -outputFormat .pdf
jet_draw_l2_correction_x -filename jra_hiF_ak3Calo_l2_dijet.root -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/L2Corrections/ -alg ak3CaloJetAnalyzer  -outputFormat .pdf
jet_draw_l2_correction_x -filename jra_hiF_ak4Calo_l2_dijet.root -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/L2Corrections/ -alg ak4CaloJetAnalyzer  -outputFormat .pdf
jet_draw_l2_correction_x -filename jra_hiF_ak5Calo_l2_dijet.root -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/L2Corrections/ -alg ak5CaloJetAnalyzer  -outputFormat .pdf
jet_draw_l2_correction_x -filename jra_hiF_ak6Calo_l2_dijet.root -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/L2Corrections/ -alg ak6CaloJetAnalyzer  -outputFormat .pdf
jet_draw_l2_correction_x -filename jra_hiF_icPu5_l2_dijet.root -path $CMSSW_BASE/src/UserCode/MNguyen/JEC/dijet/ -outputDir $CMSSW_BASE/src/UserCode/MNguyen/JEC/pdffiles/dijet/L2Corrections/ -alg icPu5JetAnalyzer -outputFormat .pdf

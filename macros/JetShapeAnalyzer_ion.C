	// reco PbPb
	#include <iostream>
	#include "TFile.h"
	#include "TTree.h"
	#include "TH1F.h"
	#include "TProfile.h"
	#include "class_def/JetAna.h"
	#include "class_def/Tracks.h"
	#include "class_def/HiTree.h"
	#include "class_def/Skim.h"
	#include "class_def/HLT.h"
	#include <TF1.h>
	
	#include "assert.h"
	#include <fstream>
	#include "TMath.h"
	#include "TVector3.h"
	
	
	#define nCBins 4
	//#define nCBins 2
	#define nPtBins_sub 10
	//#define nPtBins 17
	//#include "TrackingCorrections2012.h"
	
	#define nPtBins 1
	
	
	#include "TrackingCorrectionsv6.h"
	#include "TrackingParam.h"
	
	bool doTrackCorrections = true;
	vector<TrackingCorrections*> trackCorrections;
	TrackingParam *trackCorrFromParam;

        double getTrackCorrectionPara(int j);
        double getTrackCorrection(int j);
    
    
    	
	
	float trkPtCut=1.;
	
	bool is_data = false;
	bool test_it = false;
	bool is_selected = true;
	
	enum enum_dataset_types {e_Data2011,e_HydJet30,e_HydJet50,e_HydJet80, e_HydJet100, e_HydJet120,e_HydJet170,e_HydJet200,e_HydJet250, e_HydJet300, e_n_dataset_types};
	TString dataset_type_strs[e_n_dataset_types] = { "Data2011","HydJet30","HydJet50","HydJet80", "HydJet100", "HydJet120","HydJet170","HydJet200","HydJet250","HydJet300" };
	int dataset_type_code = -999;
	
	//float CBins[nCBins+1] = {0, 12, 40};
	//TString CBin_strs[nCBins+1] = {"Cent0", "Cent30", "Cent100"};
	
	float CBins[nCBins+1] = {0, 4, 12, 20,40};
	TString CBin_strs[nCBins+1] = {"Cent0", "Cent10", "Cent30","Cent50", "Cent100"};
	
	//float CBins[nCBins+1] = {0, 2, 4, 12, 20, 28, 36};
	//TString CBin_strs[nCBins+1] = {"Cent0", "Cent5", "Cent10", "Cent30","Cent50", "Cent70", "Cent90"};
	
	
	
	//float PtBins[nPtBins+1] = {30, 50, 70, 90, 110, 130,150, 170, 190, 210, 230, 250, 270, 290, 300, 340, 400, 440};
	//TString PtBin_strs[nPtBins+1] = {"Pt30", "Pt50", "Pt70","Pt90","Pt110", "Pt130" ,"Pt150" ,"Pt170", "Pt190", "Pt210", "Pt230","Pt250", "Pt270","Pt290","Pt300","Pt340","Pt400","Pt440"};
	
	
	
	
	//float PtBins[nPtBins+1] = {30, 50, 70, 90, 120, 160, 200, 240, 280, 340, 400, 500};
	//TString PtBin_strs[nPtBins+1] = {"Pt30", "Pt50", "Pt70","Pt90","Pt120", "Pt160" ,"Pt200" ,"Pt240", "Pt280", "Pt340", "Pt400","Pt500"};
	
	float PtBins[nPtBins+1] = {100, 500};
	TString PtBin_strs[nPtBins+1] = {"Pt100", "Pt300"};
	
	
	//float PtBins[nPtBins+1] = {100, 120, 140, 160, 180, 200,220, 240, 260, 280, 300, 320, 340, 360, 380, 400, 500};
	//TString PtBin_strs[nPtBins+1] = {"Pt100", "Pt120", "Pt140","Pt160","Pt180", "Pt200" ,"Pt220" ,"Pt240", "Pt260", "Pt280", "Pt300", "Pt320","Pt340","Pt360","Pt380", "Pt400","Pt500"};
	
	
	//float PtBins[nPtBins+1] = {100, 110, 120, 130, 140, 150, 160, 200, 300, 500};
	//TString PtBin_strs[nPtBins+1] = {"Pt100", "Pt110", "Pt120","Pt130","Pt140" , "Pt150", "Pt160", "Pt200","Pt300", "Pt500"};
	Double_t x_Bins_mc[12] = {30,50,70,90,120,160,200,240,280,340,400};
	


const int nPtBintrk = 27;
Double_t ptBintrk[nPtBintrk+1] = {0, 0.5, 1, 1.203915, 1.449412, 1.74497, 2.100796, 2.529181, 3.04492, 3.665826, 4.413344, 5.313293, 6.396755, 7.701152, 9.271536, 11.16214, 13.43828, 16.17855, 19.47761, 23.44939, 28.23108, 33.98783, 40.91848, 49.26238, 59.30774, 71.40151, 85.96137, 103.4902};




	
	float PtBins_sub[nPtBins_sub+1] = {50, 60, 70, 80, 100, 120, 140, 160, 200, 300, 500};
	TString PtBin_sub_strs[nPtBins_sub+1] = {"Pt50", "Pt60", "Pt70", "Pt80",  "Pt100", "Pt120", "Pt140","Pt160", "Pt200" , "Pt300", "Pt500"};
	
	
	class hist_class {
	public:
	hist_class(TString the_desc, bool is_it_data);
	void Delete();
	void NormalizeByCounts();
	void Write();
	void AddHists(hist_class *more_hists, float wt);
	bool is_data;
	// bool is_selected;
	TString desc;
	int n_evt_raw ;
	TH1F* NEvents;
	TH1F* NEvents_test;
	TH1F* NEvents_after_noise;
	TH1F* NEvents_after_spike;
	TH1F* NEvents_after_dphi;
	TH1F* NEvents_before_dphi;
	TH1F* NEvents_dijets;
	TH1F* NEvents_after_trigger;
	
	
	TH1F* AllJetPt_raw_hist;
	TH1F* AllJetPhi_hist;
	TH1F* AllJetEta_hist;
	TH1F* AllJetPt_hist;
	TH1F* First_AllJetPhi_hist;
	TH1F* First_AllJetEta_hist;
	TH1F* First_AllJetPt_hist;
	TH1F* Sub_AllJetPhi_hist;
	TH1F* Sub_AllJetEta_hist;
	TH1F* Sub_AllJetPt_hist;
	TH1F* JetPt_fraction;
	TH1F* Centrality;
	TH1F* track_vz;
	TH1F* track_vz_weighted;
	
	TH1F* jet_pT_hist[nCBins];
	TH1F* jet_phi_hist[nCBins];
	TH1F* jet_eta_hist[nCBins];
	TH1F* jet_corrpT_hist[nCBins];
	TH1F* LeadingJetPt_hist[nCBins];
	TH1F* LeadingJetPhi_hist[nCBins];
	TH1F* LeadingJetEta_hist[nCBins];
	TH1F* SubJetPt_hist[nCBins];
	TH1F* SubJetPhi_hist[nCBins];
	TH1F* SubJetEta_hist[nCBins];
	
	//TH1F* ThirdJetPt_hist[nCBins][nPtBins];
	TH1F* ThirdJetPhi_hist[nCBins][nPtBins];
	TH1F* ThirdJetEta_hist[nCBins][nPtBins];
	TH1F* all_cand_pT_hist[nCBins][nPtBins];
	TH1F* all_cand_phi_hist[nCBins][nPtBins];
	TH1F* all_cand_eta_hist[nCBins][nPtBins];
	
	TH1F* track_cand_pT_hist[nCBins][nPtBins];
	TH1F* track_cand_phi_hist[nCBins][nPtBins];
	TH1F* track_cand_eta_hist[nCBins][nPtBins];
	TH1F* track_cand_pT_hist_subleadingjet[nCBins][nPtBins];
	
	
	TH1F* dPhi_hist[nCBins][nPtBins];
	TH1F* dPhi_after_hist[nCBins][nPtBins];
	TH1F* dPhi_leadingjet_hist[nCBins];
	TH1F* dPhi_subleadingjet_hist[nCBins];
	
	TH1F* all_jets_corrpT[nCBins][nPtBins];
	TH1F* all_jets_phi[nCBins][nPtBins];
	TH1F* all_jets_eta[nCBins][nPtBins];
	TH1F* only_leadingjets_corrpT[nCBins][nPtBins];
	TH1F* only_leadingjets_phi[nCBins][nPtBins];
	TH1F* only_leadingjets_eta[nCBins][nPtBins];
	TH1F* only_subleadingjets_corrpT[nCBins][nPtBins];
	TH1F* only_subleadingjets_phi[nCBins][nPtBins];
	TH1F* only_subleadingjets_eta[nCBins][nPtBins];
	TH1F* neutral_cand_pT_hist[nCBins][nPtBins];
	TH1F* neutral_cand_phi_hist[nCBins][nPtBins];
	TH1F* neutral_cand_eta_hist[nCBins][nPtBins];
	TH1F* photons_cand_pT_hist[nCBins][nPtBins];
	TH1F* photons_cand_phi_hist[nCBins][nPtBins];
	TH1F* photons_cand_eta_hist[nCBins][nPtBins];
	
	TH1F* NumNeutral[nCBins][nPtBins];
	TH1F* NumPhotons[nCBins][nPtBins];
	TH1F* NumAll[nCBins][nPtBins];
	TH1F* NumCharged[nCBins][nPtBins];
	
	TH1F* NumAll_bkg[nCBins][nPtBins];
	TH1F* NumNeutral_bkg[nCBins][nPtBins];
	TH1F* NumPhotons_bkg[nCBins][nPtBins];
	TH1F* NumChargedHadrons_bkg[nCBins][nPtBins];
	TH1F* NumChargedParticles_bkg[nCBins][nPtBins];
	TH1F* NumElectrons_bkg[nCBins][nPtBins];
	TH1F* NumMuons_bkg[nCBins][nPtBins];
	
	        TH1F* radius_hist[nCBins][nPtBins];
		TH1F* radius_hist_mine[nCBins][nPtBins];
	
	TH1F* SumJetPtFraction_hist[nCBins][nPtBins];
	
	//TProfile *JetShapeIntegratedParticles[nCBins][nPtBins];
	// TProfile *JetShapeDiffParticles[nCBins][nPtBins];
	
	TH1F* JetShapeIntegratedParticles[nCBins][nPtBins];
	TH1F* JetShapeDiffParticles[nCBins][nPtBins];
	
	
	
	TProfile *JetShapeIntegratedParticles_bkgsub[nCBins][nPtBins];
	TProfile *JetShapeDiffParticles_bkgsub[nCBins][nPtBins];
	TProfile *JetShapeIntegratedParticles_bkg[nCBins][nPtBins];
	TProfile *JetShapeDiffParticles_bkg[nCBins][nPtBins];
	
	TH1F *JetShapeDiffParticles_bkg_1D[nCBins][nPtBins];
	TH1F *JetShapeDiffParticles_1D[nCBins][nPtBins];
	TH1F *JetShapeIntegratedParticles_bkg_1D[nCBins][nPtBins];
	TH1F *JetShapeIntegratedParticles_1D[nCBins][nPtBins];
	TH1F *JetShapeDiffParticlesGen_bkg_1D[nCBins][nPtBins];
	TH1F *JetShapeDiffParticlesGen_1D[nCBins][nPtBins];
	
	TH1F* NumNeutral_subleadingjet[nCBins][nPtBins];
	TH1F* NumPhotons_subleadingjet[nCBins][nPtBins];
	TH1F* NumAll_subleadingjet[nCBins][nPtBins];
	TH1F* NumChargedHadrons_subleadingjet[nCBins][nPtBins];
	
	
	
	TH1F* SumJetPtFraction_hist_subleadingjet[nCBins][nPtBins];
	TH1F* SumJetPtFraction_hist_subleadingjet_photons[nCBins][nPtBins];
	TH1F* SumJetPtFraction_hist_subleadingjet_neutrals[nCBins][nPtBins];
	TH1F* SumJetPtFraction_hist_subleadingjet_chargedhadrons[nCBins][nPtBins];
	
	TH1F* SumJetPtFraction_hist_leadingjet_photons[nCBins][nPtBins];
	TH1F* SumJetPtFraction_hist_leadingjet_neutrals[nCBins][nPtBins];
	TH1F* SumJetPtFraction_hist_leadingjet_charged[nCBins][nPtBins];
	
	TH1F* all_cand_pT_hist_subleadingjet[nCBins][nPtBins];
	TH1F* all_cand_phi_hist_subleadingjet[nCBins][nPtBins];
	TH1F* all_cand_eta_hist_subleadingjet[nCBins][nPtBins];
	TH1F* radius_hist_subleadingjet[nCBins][nPtBins];
	
	TH1F* Centrality_hist[nCBins][nPtBins];
	TH1F* Aj[nCBins][nPtBins];
	
	
	TH1F* neutral_cand_pT_hist_subleadingjet[nCBins][nPtBins];
	TH1F* neutral_cand_phi_hist_subleadingjet[nCBins][nPtBins];
	TH1F* neutral_cand_eta_hist_subleadingjet[nCBins][nPtBins];
	
	TH1F* photons_cand_pT_hist_subleadingjet[nCBins][nPtBins];
	TH1F* photons_cand_phi_hist_subleadingjet[nCBins][nPtBins];
	TH1F* photons_cand_eta_hist_subleadingjet[nCBins][nPtBins];
	
	
	TH1F* SumJetPtFraction_hist_leadingjet_chargedhadrons[nCBins][nPtBins];
	TH1F* SumJetPtFraction_hist_leadingjet_chargedparticles[nCBins][nPtBins];
	TH1F* SumJetPtFraction_hist_leadingjet_electrons[nCBins][nPtBins];
	TH1F* SumJetPtFraction_hist_leadingjet_muons[nCBins][nPtBins];
	
	TH1F* NumChargedHadrons[nCBins][nPtBins];
	TH1F* NumChargedParticles[nCBins][nPtBins];
	TH1F* NumElectrons[nCBins][nPtBins];
	TH1F* NumMuons[nCBins][nPtBins];
	
	TH1F* chargedhadrons_cand_pT_hist[nCBins][nPtBins];
	TH1F* chargedhadrons_cand_phi_hist[nCBins][nPtBins];
	TH1F* chargedhadrons_cand_eta_hist[nCBins][nPtBins];
	
	TH1F* chargedparticles_cand_pT_hist[nCBins][nPtBins];
	TH1F* chargedparticles_cand_phi_hist[nCBins][nPtBins];
	TH1F* chargedparticles_cand_eta_hist[nCBins][nPtBins];
	
	TH1F* electrons_cand_pT_hist[nCBins][nPtBins];
	TH1F* electrons_cand_phi_hist[nCBins][nPtBins];
	TH1F* electrons_cand_eta_hist[nCBins][nPtBins];
	
	TH1F* muons_cand_pT_hist[nCBins][nPtBins];
	TH1F* muons_cand_phi_hist[nCBins][nPtBins];
	TH1F* muons_cand_eta_hist[nCBins][nPtBins];
	
	
	
	TH1F* chargedhadrons_cand_pT_hist_bkg[nCBins][nPtBins];
	TH1F* chargedparticles_cand_pT_hist_bkg[nCBins][nPtBins];
	TH1F* electrons_cand_pT_hist_bkg[nCBins][nPtBins];
	TH1F* muons_cand_pT_hist_bkg[nCBins][nPtBins];
	TH1F* neutral_cand_pT_hist_bkg[nCBins][nPtBins];
	TH1F* photons_cand_pT_hist_bkg[nCBins][nPtBins];
	
	
	
	TH1F* dN_tracks[nCBins][nPtBins];
	TH1F* dN_chargedhadrons[nCBins][nPtBins];
	TH1F* dN_chargedparticles[nCBins][nPtBins];
	TH1F* dN_electrons[nCBins][nPtBins];
	TH1F* dN_muons[nCBins][nPtBins];
	TH1F* dN_neutrals[nCBins][nPtBins];
	TH1F* dN_photons[nCBins][nPtBins];
	
	TH1F* SumJetPtFraction_hist_leadingjet_photons_bkg[nCBins][nPtBins];
	TH1F* SumJetPtFraction_hist_leadingjet_neutrals_bkg[nCBins][nPtBins];
	TH1F* SumJetPtFraction_hist_leadingjet_chargedhadrons_bkg[nCBins][nPtBins];
	TH1F* SumJetPtFraction_hist_leadingjet_chargedparticles_bkg[nCBins][nPtBins];
	TH1F* SumJetPtFraction_hist_leadingjet_electrons_bkg[nCBins][nPtBins];
	TH1F* SumJetPtFraction_hist_leadingjet_muons_bkg[nCBins][nPtBins];
	
	
	
	/// subleading jet
	TH1F* chargedhadrons_cand_pT_hist_subleadingjet[nCBins][nPtBins];
	TH1F* chargedhadrons_cand_phi_hist_subleadingjet[nCBins][nPtBins];
	TH1F* chargedhadrons_cand_eta_hist_subleadingjet[nCBins][nPtBins];
	
	TH1F* chargedhadrons_cand_pT_hist_subleadingjet_bkg[nCBins][nPtBins];
	TH1F* neutral_cand_pT_hist_subleadingjet_bkg[nCBins][nPtBins];
	TH1F* photons_cand_pT_hist_subleadingjet_bkg[nCBins][nPtBins];
	
	TH1F* SumJetPtFraction_hist_subleadingjet_photons_bkg[nCBins][nPtBins];
	TH1F* SumJetPtFraction_hist_subleadingjet_neutrals_bkg[nCBins][nPtBins];
	TH1F* SumJetPtFraction_hist_subleadingjet_chargedhadrons_bkg[nCBins][nPtBins];
	TH1F* SumJetPtFraction_hist_subleadingjet_chargedparticles_bkg[nCBins][nPtBins];
	TH1F* SumJetPtFraction_hist_subleadingjet_electrons_bkg[nCBins][nPtBins];
	TH1F* SumJetPtFraction_hist_subleadingjet_muons_bkg[nCBins][nPtBins];
	
	TH1F* NumAll_subleadingjet_bkg[nCBins][nPtBins];
	TH1F* NumNeutral_subleadingjet_bkg[nCBins][nPtBins];
	TH1F* NumPhotons_subleadingjet_bkg[nCBins][nPtBins];
	TH1F* NumChargedHadrons_subleadingjet_bkg[nCBins][nPtBins];
	
	TH1F* JetPt_fraction_hist[nCBins][nPtBins];
	TH1F* dPhi_jet_track[nCBins][nPtBins];
	TH1F* dPhi_jet_track_ptweight[nCBins][nPtBins];
	
	
	TH1F* JetShapeDiffParticles_bkg_1D_total[nCBins];
	TH1F* JetShapeIntegratedParticles_bkg_1D_total[nCBins];
	
	TH1F* track_cand_pT_hist_weighted[nCBins][nPtBins];
	TH1F* SumPt_only[nCBins][nPtBins];
        TH1F* track_gen_pT_hist[nCBins][nPtBins];
    	
	
	TH1F* JetEnergy_resolution[nCBins][nPtBins];
	TH1F* JetEnergy_ratio[nCBins][nPtBins];
	
	TH1F* JetShapeDiffParticles_subleadingjet_bkg_1DEtaRef[nCBins][nPtBins_sub];
	TH1F* JetShapeIntegratedParticles_subleadingjet_1D[nCBins][nPtBins_sub];
	TH1F* JetShapeDiffParticles_subleadingjet_bkg_1D[nCBins][nPtBins_sub];
	TH1F* JetShapeDiffParticles_subleadingjet_1D[nCBins][nPtBins_sub];
	
	double sig_count[nCBins][nPtBins];
	double bkg_count[nCBins][nPtBins];
	double sig_count_sub[nCBins][nPtBins_sub];
	double bkg_count_sub[nCBins][nPtBins_sub];
	
	TH1F* JetEnergy_ratio_new[nCBins][nPtBins];
	TH2F* JetEnergy_gen_vs_rec[nCBins];
	TH1F* fullrecjet_aftercuts[nPtBins];
	TH1F* fullrefjet_aftercuts[nPtBins];
	};
	
	hist_class::hist_class(TString the_desc, bool is_it_data) {
	n_evt_raw = 0;
	desc = the_desc;
	is_data = is_it_data;
	
	//  JetEnergy_gen_vs_rec = new TH2F((TString) (desc + "_JetEnergy_gen_vs_rec"), "", 500, 0, 1000, 500, 0, 1000);     JetEnergy_gen_vs_rec->Sumw2();
	
	
	NEvents = new TH1F((TString) (desc + "_Nevents"), "", 100, 0., 100.);     NEvents->Sumw2();
	NEvents_test = new TH1F((TString) (desc + "_Nevents_test"), "", 100, 0., 100.);     NEvents_test->Sumw2();
	NEvents_after_noise = new TH1F((TString) (desc + "_Nevents_after_noise"), "", 100, 0., 100.);     NEvents_after_noise->Sumw2();
	NEvents_after_spike = new TH1F((TString) (desc + "_Nevents_after_spike"), "", 100, 0., 100.);     NEvents_after_spike->Sumw2();
	
	NEvents_dijets = new TH1F((TString) (desc + "_Nevents_dijets"), "", 100, 0., 100.);     NEvents_dijets->Sumw2();
	NEvents_after_dphi = new TH1F((TString) (desc + "_Nevents_after_dphi"), "", 100, 0., 100.);     NEvents_after_dphi->Sumw2();
	NEvents_before_dphi = new TH1F((TString) (desc + "_Nevents_before_dphi"), "", 100, 0., 100.);     NEvents_before_dphi->Sumw2();
	NEvents_after_trigger = new TH1F((TString) (desc + "_Nevents_after_trigger"), "", 100, 0., 100.);     NEvents_after_trigger->Sumw2();
	
	
	AllJetPt_raw_hist = new TH1F((TString) (desc + "_AllJetPt_raw_hist"), "", 100, 0., 500.);     AllJetPt_raw_hist->Sumw2();
	AllJetPt_hist = new TH1F((TString) (desc + "_AllJetPt_hist"), "", 100, 0., 500.);     AllJetPt_hist->Sumw2();
	AllJetPhi_hist = new TH1F((TString) (desc + "_AllJetPhi_hist"), "", 36, 0.,TMath::Pi());     AllJetPhi_hist->Sumw2();
	AllJetEta_hist = new TH1F((TString) (desc + "_AllJetEta_hist"), "", 50, -5., 5.);     AllJetEta_hist->Sumw2();
	
	First_AllJetPt_hist = new TH1F((TString) (desc + "_First_AllJetPt_hist"), "", 100, 0., 500.);     First_AllJetPt_hist->Sumw2();
	First_AllJetPhi_hist = new TH1F((TString) (desc + "_First_AllJetPhi_hist"), "", 36, 0.,TMath::Pi());     First_AllJetPhi_hist->Sumw2();
	First_AllJetEta_hist = new TH1F((TString) (desc + "_First_AllJetEta_hist"), "", 50, -5., 5.);     First_AllJetEta_hist->Sumw2();
	
	Sub_AllJetPt_hist = new TH1F((TString) (desc + "_Sub_AllJetPt_hist"), "", 100, 0., 500.);     Sub_AllJetPt_hist->Sumw2();
	Sub_AllJetPhi_hist = new TH1F((TString) (desc + "_Sub_AllJetPhi_hist"), "", 36, 0.,TMath::Pi());     Sub_AllJetPhi_hist->Sumw2();
	Sub_AllJetEta_hist = new TH1F((TString) (desc + "_Sub_AllJetEta_hist"), "", 50, -5., 5.);     Sub_AllJetEta_hist->Sumw2();
	JetPt_fraction = new TH1F((TString) (desc + "_JetPt_fraction"), "", 100,0.,5);     JetPt_fraction->Sumw2();
	
	Centrality = new TH1F((TString) (desc + "_Centrality"), "", 40,0.,40);     Centrality->Sumw2();
	
	track_vz = new TH1F((TString) (desc + "_track_vz"), "", 80, -20., 20.);
	track_vz_weighted = new TH1F((TString) (desc + "_track_vz_weighted"), "", 80, -20., 20.);
	
	
	for (int ibin2=0;ibin2<nPtBins;ibin2++){
	fullrecjet_aftercuts[ibin2] = new TH1F((TString) (desc + "_fullrecjet_aftercuts" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 10, x_Bins_mc);    fullrecjet_aftercuts[ibin2]->Sumw2();
	
		fullrefjet_aftercuts[ibin2] = new TH1F((TString) (desc + "_fullrefjet_aftercuts" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 10, x_Bins_mc);    fullrefjet_aftercuts[ibin2]->Sumw2();
	
	
	
	}
	
	
	for (int ibin=0;ibin<nCBins;ibin++){
	
	
	jet_pT_hist[ibin] = new TH1F((TString) (desc + "_jet_pT_hist_" + CBin_strs[ibin] + "_" + CBin_strs[ibin+1]), "", 25, 0., 500.); jet_pT_hist[ibin]->Sumw2();
	jet_phi_hist[ibin] = new TH1F((TString) (desc + "_jet_phi_hist_" + CBin_strs[ibin] + "_" + CBin_strs[ibin+1] ), "", 36, 0.,TMath::Pi());
	jet_phi_hist[ibin]->Sumw2();
	jet_eta_hist[ibin] = new TH1F((TString) (desc + "_jet_eta_hist_" + CBin_strs[ibin] + "_" + CBin_strs[ibin+1] ), "", 50, -5., 5.);     jet_eta_hist[ibin]->Sumw2();
	jet_corrpT_hist[ibin] = new TH1F((TString) (desc + "_jet_corrpT_hist_" + CBin_strs[ibin] + "_" + CBin_strs[ibin+1]), "", 25, 0., 500.);     jet_corrpT_hist[ibin]->Sumw2();
	LeadingJetPt_hist[ibin] = new TH1F((TString) (desc + "_LeadingJetPt_hist_" + CBin_strs[ibin] + "_" + CBin_strs[ibin+1] ), "", 25, 0., 500.);     LeadingJetPt_hist[ibin]->Sumw2();
	LeadingJetPhi_hist[ibin] = new TH1F((TString) (desc + "_LeadingJetPhi_hist_" + CBin_strs[ibin] + "_" + CBin_strs[ibin+1]), "", 36, 0.,TMath::Pi());     LeadingJetPhi_hist[ibin]->Sumw2();
	LeadingJetEta_hist[ibin] = new TH1F((TString) (desc + "_LeadingJetEta_hist_" + CBin_strs[ibin] + "_" + CBin_strs[ibin+1]), "", 50, -5., 5.);     LeadingJetEta_hist[ibin]->Sumw2();
	SubJetPt_hist[ibin] = new TH1F((TString) (desc + "_SubJetPt_hist_" + CBin_strs[ibin] + "_" + CBin_strs[ibin+1]), "", 25, 0., 500.);     SubJetPt_hist[ibin]->Sumw2();
	SubJetPhi_hist[ibin] = new TH1F((TString) (desc + "_SubJetPhi_hist_" + CBin_strs[ibin] + "_" + CBin_strs[ibin+1]), "", 36, 0.,TMath::Pi());     SubJetPhi_hist[ibin]->Sumw2();
	SubJetEta_hist[ibin] = new TH1F((TString) (desc + "_SubJetEta_hist_" + CBin_strs[ibin] + "_" + CBin_strs[ibin+1]), "", 50, -5., 5.);     SubJetEta_hist[ibin]->Sumw2();
	
	dPhi_leadingjet_hist[ibin] = new TH1F((TString) (desc + "_dPhi_leadingjet_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1]), "", 30,0,3.14159);     dPhi_leadingjet_hist[ibin]->Sumw2();
	dPhi_subleadingjet_hist[ibin] = new TH1F((TString) (desc + "_dPhi_subleadingjet_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1]), "", 30,0,3.14159);     dPhi_subleadingjet_hist[ibin]->Sumw2();
	
	
	JetShapeDiffParticles_bkg_1D_total[ibin] = new TH1F((TString) (desc + "_JetShapeDiffParticles_bkg_1D_total"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1]), "", 6,0.0,0.3);     JetShapeDiffParticles_bkg_1D_total[ibin]->Sumw2();     
	
	
	JetShapeIntegratedParticles_bkg_1D_total[ibin] = new TH1F((TString) (desc + "_JetShapeIntegratedParticles_bkg_1D_total"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] ), "", 6,0.05,0.35);     JetShapeIntegratedParticles_bkg_1D_total[ibin]->Sumw2();
	
	
	JetEnergy_gen_vs_rec[ibin] = new TH2F((TString) (desc + "_JetEnergy_gen_vs_rec"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1]), "", 500, 0, 1000, 500, 0, 1000);     JetEnergy_gen_vs_rec[ibin]->Sumw2();
	
	
	for (int ibin2=0;ibin2<nPtBins;ibin2++){ 
	//ThirdJetPt_histgibin]gibin2] = new TH1F((TString) (desc + "_ThirdJetPt_hist_" + CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     ThirdJetPt_hist[ibin][ibin2]->Sumw2();
	ThirdJetPhi_hist[ibin][ibin2] = new TH1F((TString) (desc + "_ThirdJetPhi_hist_" + CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 36, 0.,TMath::Pi());     ThirdJetPhi_hist[ibin][ibin2]->Sumw2();
	ThirdJetEta_hist[ibin][ibin2] = new TH1F((TString) (desc + "_ThirdJetEta_hist_" + CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50, -5., 5.);     ThirdJetEta_hist[ibin][ibin2]->Sumw2();
	dPhi_hist[ibin][ibin2] = new TH1F((TString) (desc + "_dPhi_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 30,0,3.14159);     dPhi_hist[ibin][ibin2]->Sumw2();
	dPhi_after_hist[ibin][ibin2] = new TH1F((TString) (desc + "_dPhi_after_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 30,0,3.14159);     dPhi_after_hist[ibin][ibin2]->Sumw2();
	
	dPhi_jet_track[ibin][ibin2] = new TH1F((TString) (desc + "_dPhi_jet_track"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 30,0,3.14159);     dPhi_jet_track[ibin][ibin2]->Sumw2();
	
	
	dPhi_jet_track_ptweight[ibin][ibin2] = new TH1F((TString) (desc + "_dPhi_jet_track_ptweight"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 30,0,3.14159);     dPhi_jet_track_ptweight[ibin][ibin2]->Sumw2();
	
	
	
	
	
	// dPhi_hist[ibin][ibin2] = new TH1F((TString) (desc + "_dPhi_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 6);     // dPhi_hist[ibin][ibin2]->Sumw2();
	//dPhi_after_hist[ibin][ibin2] = new TH1F((TString) (desc + "_dPhi_after_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 6);     //dPhi_after_hist[ibin][ibin2]->Sumw2();
	
	
	all_jets_corrpT[ibin][ibin2] = new TH1F((TString) (desc + "_all_jets_corrpT"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50, 0., 500.);     all_jets_corrpT[ibin][ibin2]->Sumw2();
	all_jets_phi[ibin][ibin2] = new TH1F((TString) (desc + "_all_jets_phi"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 36, 0.,TMath::Pi());     all_jets_phi[ibin][ibin2]->Sumw2();
	all_jets_eta[ibin][ibin2] = new TH1F((TString) (desc + "_all_jets_eta"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50, -5., 5.);     all_jets_eta[ibin][ibin2]->Sumw2();
	
	//// leading jet histograms
	only_leadingjets_corrpT[ibin][ibin2] = new TH1F((TString) (desc + "_only_leadingjets_corrpT"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     only_leadingjets_corrpT[ibin][ibin2]->Sumw2();
	only_leadingjets_phi[ibin][ibin2] = new TH1F((TString) (desc + "_only_leadingjets_phi"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 36, 0.,TMath::Pi());     only_leadingjets_phi[ibin][ibin2]->Sumw2();
	only_leadingjets_eta[ibin][ibin2] = new TH1F((TString) (desc + "_only_leadingjets_eta"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50, -5., 5.);     only_leadingjets_eta[ibin][ibin2]->Sumw2();
	all_cand_pT_hist[ibin][ibin2] = new TH1F((TString) (desc + "_all_cand_pT_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     all_cand_pT_hist[ibin][ibin2]->Sumw2();
	all_cand_phi_hist[ibin][ibin2] = new TH1F((TString) (desc + "_all_cand_phi_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 36, 0.,TMath::Pi());     all_cand_phi_hist[ibin][ibin2]->Sumw2();
	all_cand_eta_hist[ibin][ibin2] = new TH1F((TString) (desc + "_all_cand_eta_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50, -5., 5.);     all_cand_eta_hist[ibin][ibin2]->Sumw2();
	
	track_cand_pT_hist[ibin][ibin2] = new TH1F((TString) (desc + "_track_cand_pT_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", nPtBintrk,ptBintrk);     track_cand_pT_hist[ibin][ibin2]->Sumw2();
	track_cand_phi_hist[ibin][ibin2] = new TH1F((TString) (desc + "_track_cand_phi_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 36, 0.,TMath::Pi());     track_cand_phi_hist[ibin][ibin2]->Sumw2();
	track_cand_eta_hist[ibin][ibin2] = new TH1F((TString) (desc + "_track_cand_eta_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50, -5., 5.);     track_cand_eta_hist[ibin][ibin2]->Sumw2();
	track_cand_pT_hist_subleadingjet[ibin][ibin2] = new TH1F((TString) (desc + "_track_cand_pT_hist_subleadingjet"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     track_cand_pT_hist_subleadingjet[ibin][ibin2]->Sumw2();
	
	
	NumNeutral[ibin][ibin2] = new TH1F((TString) (desc + "_NumNeutral"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumNeutral[ibin][ibin2]->Sumw2();
	NumPhotons[ibin][ibin2] = new TH1F((TString) (desc + "_NumPhotons"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumPhotons[ibin][ibin2]->Sumw2();
	NumAll[ibin][ibin2] = new TH1F((TString) (desc + "_NumAll"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumAll[ibin][ibin2]->Sumw2();
	NumCharged[ibin][ibin2] = new TH1F((TString) (desc + "_NumCharged"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumCharged[ibin][ibin2]->Sumw2();
	NumChargedHadrons[ibin][ibin2] = new TH1F((TString) (desc + "_NumChargedHadrons"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumChargedHadrons[ibin][ibin2]->Sumw2();
	NumChargedParticles[ibin][ibin2] = new TH1F((TString) (desc + "_NumChargedParticles"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumChargedParticles[ibin][ibin2]->Sumw2();
	NumElectrons[ibin][ibin2] = new TH1F((TString) (desc + "_NumElectrons"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumElectrons[ibin][ibin2]->Sumw2();
	NumMuons[ibin][ibin2] = new TH1F((TString) (desc + "_NumMuons"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumMuons[ibin][ibin2]->Sumw2();
	
	
	
	
	
	
	NumNeutral_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_NumNeutral_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumNeutral_bkg[ibin][ibin2]->Sumw2();
	NumPhotons_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_NumPhotons_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumPhotons_bkg[ibin][ibin2]->Sumw2();
	NumAll_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_NumAll_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumAll_bkg[ibin][ibin2]->Sumw2();
	NumChargedHadrons_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_NumChargedHadrons_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumChargedHadrons_bkg[ibin][ibin2]->Sumw2();
	NumChargedParticles_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_NumChargedParticles_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumChargedParticles_bkg[ibin][ibin2]->Sumw2();
	NumElectrons_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_NumElectrons_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumElectrons_bkg[ibin][ibin2]->Sumw2();
	NumMuons_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_NumMuons_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumMuons_bkg[ibin][ibin2]->Sumw2();
	
	
	
	NumNeutral_subleadingjet_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_NumNeutral_subleadingjet_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumNeutral_subleadingjet_bkg[ibin][ibin2]->Sumw2();
	NumPhotons_subleadingjet_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_NumPhotons_subleadingjet_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumPhotons_subleadingjet_bkg[ibin][ibin2]->Sumw2();
	NumAll_subleadingjet_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_NumAll_subleadingjet_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumAll_subleadingjet_bkg[ibin][ibin2]->Sumw2();
	NumChargedHadrons_subleadingjet_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_NumChargedHadrons_subleadingjet_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumChargedHadrons_subleadingjet_bkg[ibin][ibin2]->Sumw2();
	
	
	
	
	
	///===================////////======================//////////////===================//////////=================//////==========
	
	chargedhadrons_cand_pT_hist[ibin][ibin2] = new TH1F((TString) (desc + "_chargedhadrons_cand_pT_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     chargedhadrons_cand_pT_hist[ibin][ibin2]->Sumw2();
	chargedhadrons_cand_phi_hist[ibin][ibin2] = new TH1F((TString) (desc + "_chargedhadrons_cand_phi_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 36, 0.,TMath::Pi());     chargedhadrons_cand_phi_hist[ibin][ibin2]->Sumw2();
	chargedhadrons_cand_eta_hist[ibin][ibin2] = new TH1F((TString) (desc + "_chargedhadrons_cand_eta_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50, -5., 5.);     chargedhadrons_cand_eta_hist[ibin][ibin2]->Sumw2();
	
	chargedparticles_cand_pT_hist[ibin][ibin2] = new TH1F((TString) (desc + "_chargedparticles_cand_pT_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     chargedparticles_cand_pT_hist[ibin][ibin2]->Sumw2();
	chargedparticles_cand_phi_hist[ibin][ibin2] = new TH1F((TString) (desc + "_chargedparticles_cand_phi_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 36, 0.,TMath::Pi());     chargedparticles_cand_phi_hist[ibin][ibin2]->Sumw2();
	chargedparticles_cand_eta_hist[ibin][ibin2] = new TH1F((TString) (desc + "_chargedparticles_cand_eta_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50, -5., 5.);     chargedparticles_cand_eta_hist[ibin][ibin2]->Sumw2();
	
	electrons_cand_pT_hist[ibin][ibin2] = new TH1F((TString) (desc + "_electrons_cand_pT_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     electrons_cand_pT_hist[ibin][ibin2]->Sumw2();
	electrons_cand_phi_hist[ibin][ibin2] = new TH1F((TString) (desc + "_electrons_cand_phi_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 36, 0.,TMath::Pi());     electrons_cand_phi_hist[ibin][ibin2]->Sumw2();
	electrons_cand_eta_hist[ibin][ibin2] = new TH1F((TString) (desc + "_electrons_cand_eta_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50, -5., 5.);     electrons_cand_eta_hist[ibin][ibin2]->Sumw2();
	
	muons_cand_pT_hist[ibin][ibin2] = new TH1F((TString) (desc + "_muons_cand_pT_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     muons_cand_pT_hist[ibin][ibin2]->Sumw2();
	muons_cand_phi_hist[ibin][ibin2] = new TH1F((TString) (desc + "_muons_cand_phi_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 36, 0.,TMath::Pi());     muons_cand_phi_hist[ibin][ibin2]->Sumw2();
	muons_cand_eta_hist[ibin][ibin2] = new TH1F((TString) (desc + "_muons_cand_eta_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50, -5., 5.);     muons_cand_eta_hist[ibin][ibin2]->Sumw2();
	
	neutral_cand_pT_hist[ibin][ibin2] = new TH1F((TString) (desc + "_neutral_cand_pT_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     neutral_cand_pT_hist[ibin][ibin2]->Sumw2();
	neutral_cand_phi_hist[ibin][ibin2] = new TH1F((TString) (desc + "_neutral_cand_phi_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 36, 0.,TMath::Pi());     neutral_cand_phi_hist[ibin][ibin2]->Sumw2();
	neutral_cand_eta_hist[ibin][ibin2] = new TH1F((TString) (desc + "_neutral_cand_eta_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50, -5., 5.);     neutral_cand_eta_hist[ibin][ibin2]->Sumw2();
	
	photons_cand_pT_hist[ibin][ibin2] = new TH1F((TString) (desc + "_photons_cand_pT_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     photons_cand_pT_hist[ibin][ibin2]->Sumw2();
	photons_cand_phi_hist[ibin][ibin2] = new TH1F((TString) (desc + "_photons_cand_phi_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 36, 0.,TMath::Pi());     photons_cand_phi_hist[ibin][ibin2]->Sumw2();
	photons_cand_eta_hist[ibin][ibin2] = new TH1F((TString) (desc + "_photons_cand_eta_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50, -5., 5.);     photons_cand_eta_hist[ibin][ibin2]->Sumw2();
	
	///===================////////======================//////////////===================//////////=================//////==========
	///===================////////======================//////////////===================//////////=================//////==========
	///===================////////======================//////////////===================//////////=================//////==========
	
	
	
	chargedhadrons_cand_pT_hist_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_chargedhadrons_cand_pT_hist_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     chargedhadrons_cand_pT_hist_bkg[ibin][ibin2]->Sumw2();
	
	chargedparticles_cand_pT_hist_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_chargedparticles_cand_pT_hist_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     chargedparticles_cand_pT_hist_bkg[ibin][ibin2]->Sumw2();
	
	electrons_cand_pT_hist_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_electrons_cand_pT_hist_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     electrons_cand_pT_hist_bkg[ibin][ibin2]->Sumw2();
	
	muons_cand_pT_hist_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_muons_cand_pT_hist_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     muons_cand_pT_hist_bkg[ibin][ibin2]->Sumw2();
	
	neutral_cand_pT_hist_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_neutral_cand_pT_hist_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     neutral_cand_pT_hist_bkg[ibin][ibin2]->Sumw2();
	
	photons_cand_pT_hist_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_photons_cand_pT_hist_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     photons_cand_pT_hist_bkg[ibin][ibin2]->Sumw2();
	
	
	/// subleading jet
	
	chargedhadrons_cand_pT_hist_subleadingjet_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_chargedhadrons_cand_pT_hist_subleadingjet_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     chargedhadrons_cand_pT_hist_subleadingjet_bkg[ibin][ibin2]->Sumw2();
	neutral_cand_pT_hist_subleadingjet_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_neutral_cand_pT_hist_subleadingjet_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     neutral_cand_pT_hist_subleadingjet_bkg[ibin][ibin2]->Sumw2();
	photons_cand_pT_hist_subleadingjet_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_photons_cand_pT_hist_subleadingjet_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     photons_cand_pT_hist_subleadingjet_bkg[ibin][ibin2]->Sumw2();
	
	///===================////////======================//////////////===================//////////=================//////==========
	
	
	
	//SumJetPtFraction_hist[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     //SumJetPtFraction_hist[ibin][ibin2]->Sumw2();
	
	
	SumJetPtFraction_hist[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100,0.,500);     SumJetPtFraction_hist[ibin][ibin2]->Sumw2();
	
	
	//  JetShapeIntegratedParticles[ibin][ibin2] = new TProfile((TString) (desc + "_JetShapeIntegratedParticles"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 6,0.05,0.35,0.,2.);     JetShapeIntegratedParticles[ibin][ibin2]->Sumw2();
	
	
	
	JetShapeIntegratedParticles[ibin][ibin2] = new TH1F((TString) (desc + "_JetShapeIntegratedParticles"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 6,0.05,0.35);     JetShapeIntegratedParticles[ibin][ibin2]->Sumw2();
	
	
	
	//JetShapeDiffParticles[ibin][ibin2] = new TProfile((TString) (desc + "_JetShapeDiffParticles"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 6,0.0,0.3,0.,100.);     JetShapeDiffParticles[ibin][ibin2]->Sumw2();
	
	
	JetShapeDiffParticles[ibin][ibin2] = new TH1F((TString) (desc + "_JetShapeDiffParticles"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 6,0.0,0.3);     JetShapeDiffParticles[ibin][ibin2]->Sumw2();
	
	
	
	
	JetShapeIntegratedParticles_bkgsub[ibin][ibin2] = new TProfile((TString) (desc + "_JetShapeIntegratedParticles_bkgsub"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 6,0.05,0.35,0.,2.);     JetShapeIntegratedParticles_bkgsub[ibin][ibin2]->Sumw2();
	JetShapeDiffParticles_bkgsub[ibin][ibin2] = new TProfile((TString) (desc + "_JetShapeDiffParticles_bkgsub"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 6,0.0,0.3,0.,100.);     JetShapeDiffParticles_bkgsub[ibin][ibin2]->Sumw2();
	
	JetShapeIntegratedParticles_bkg[ibin][ibin2] = new TProfile((TString) (desc + "_JetShapeIntegratedParticles_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 6,0.05,0.35,0.,2.);     JetShapeIntegratedParticles_bkg[ibin][ibin2]->Sumw2();
	JetShapeDiffParticles_bkg[ibin][ibin2] = new TProfile((TString) (desc + "_JetShapeDiffParticles_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 6,0.0,0.3,0.,100.);     JetShapeDiffParticles_bkg[ibin][ibin2]->Sumw2();
	
	
	radius_hist[ibin][ibin2] = new TH1F((TString) (desc + "_radius_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50, 0., 5.);     radius_hist[ibin][ibin2]->Sumw2();


        radius_hist_mine[ibin][ibin2] = new TH1F((TString) (desc + "_radius_hist_mine"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50, 0., 5.);     radius_hist_mine[ibin][ibin2]->Sumw2();


	
	/*   J(tShapeDiffParticles_bkg_1D[ibin][ibin2] = new TH1F((TString) (desc + "_JetShapeDiffParticles_bkg_1D"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 6,0.0,0.3);     JetShapeDiffParticles_bkg_1D[ibin][ibin2]->Sumw2();     
	JetShapeDiffParticles_1D[ibin][ibin2] = new TH1F((TString) (desc + "_JetShapeDiffParticles_1D"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 6,0.0,0.3);     JetShapeDiffParticles_1D[ibin][ibin2]->Sumw2();
	
	
	JetShapeIntegratedParticles_bkg_1D[ibin][ibin2] = new TH1F((TString) (desc + "_JetShapeIntegratedParticles_bkg_1D"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 6,0.05,0.35);     JetShapeIntegratedParticles_bkg_1D[ibin][ibin2]->Sumw2();
	JetShapeIntegratedParticles_1D[ibin][ibin2] = new TH1F((TString) (desc + "_JetShapeIntegratedParticles_1D"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 6,0.05,0.35);     JetShapeIntegratedParticles_1D[ibin][ibin2]->Sumw2();
	
	*/
	
	JetShapeDiffParticles_bkg_1D[ibin][ibin2] = new TH1F((TString) (desc + "_JetShapeDiffParticles_bkg_1D"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 6,0.0,0.3);     JetShapeDiffParticles_bkg_1D[ibin][ibin2]->Sumw2();     
	JetShapeDiffParticles_1D[ibin][ibin2] = new TH1F((TString) (desc + "_JetShapeDiffParticles_1D"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 6,0.0,0.3);     JetShapeDiffParticles_1D[ibin][ibin2]->Sumw2();
	
	
	JetShapeIntegratedParticles_bkg_1D[ibin][ibin2] = new TH1F((TString) (desc + "_JetShapeIntegratedParticles_bkg_1D"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 6,0.05,0.35);     JetShapeIntegratedParticles_bkg_1D[ibin][ibin2]->Sumw2();
	JetShapeIntegratedParticles_1D[ibin][ibin2] = new TH1F((TString) (desc + "_JetShapeIntegratedParticles_1D"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 6,0.05,0.35);     JetShapeIntegratedParticles_1D[ibin][ibin2]->Sumw2();
	
		JetShapeDiffParticlesGen_1D[ibin][ibin2] = new TH1F((TString) (desc + "_JetShapeDiffParticlesGen_1D"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 6,0.0,0.3);     JetShapeDiffParticlesGen_1D[ibin][ibin2]->Sumw2();
		
		JetShapeDiffParticlesGen_bkg_1D[ibin][ibin2] = new TH1F((TString) (desc + "_JetShapeDiffParticlesGen_bkg_1D"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 6,0.0,0.3);    
		JetShapeDiffParticlesGen_bkg_1D[ibin][ibin2]->Sumw2();
	
	//// subleading jet histograms
	only_subleadingjets_corrpT[ibin][ibin2] = new TH1F((TString) (desc + "_only_subleadingjets_corrpT"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     only_subleadingjets_corrpT[ibin][ibin2]->Sumw2();
	only_subleadingjets_phi[ibin][ibin2] = new TH1F((TString) (desc + "_only_subleadingjets_phi"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 36, 0.,TMath::Pi());     only_subleadingjets_phi[ibin][ibin2]->Sumw2();
	only_subleadingjets_eta[ibin][ibin2] = new TH1F((TString) (desc + "_only_subleadingjets_eta"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50, -5., 5.);     only_subleadingjets_eta[ibin][ibin2]->Sumw2();
	all_cand_pT_hist_subleadingjet[ibin][ibin2] = new TH1F((TString) (desc + "_all_cand_pT_hist_subleadingjet"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     all_cand_pT_hist_subleadingjet[ibin][ibin2]->Sumw2();
	all_cand_phi_hist_subleadingjet[ibin][ibin2] = new TH1F((TString) (desc + "_all_cand_phi_hist_subleadingjet"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 36, 0.,TMath::Pi());     all_cand_phi_hist_subleadingjet[ibin][ibin2]->Sumw2();
	all_cand_eta_hist_subleadingjet[ibin][ibin2] = new TH1F((TString) (desc + "_all_cand_eta_hist_subleadingjet"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50, -5., 5.);     all_cand_eta_hist_subleadingjet[ibin][ibin2]->Sumw2();
	neutral_cand_pT_hist_subleadingjet[ibin][ibin2] = new TH1F((TString) (desc + "_neutral_cand_pT_hist_subleadingjet"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     neutral_cand_pT_hist_subleadingjet[ibin][ibin2]->Sumw2();
	neutral_cand_phi_hist_subleadingjet[ibin][ibin2] = new TH1F((TString) (desc + "_neutral_cand_phi_hist_subleadingjet"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 36, 0.,TMath::Pi());     neutral_cand_phi_hist_subleadingjet[ibin][ibin2]->Sumw2();
	neutral_cand_eta_hist_subleadingjet[ibin][ibin2] = new TH1F((TString) (desc + "_neutral_cand_eta_hist_subleadingjet"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50, -5., 5.);     neutral_cand_eta_hist_subleadingjet[ibin][ibin2]->Sumw2();
	photons_cand_pT_hist_subleadingjet[ibin][ibin2] = new TH1F((TString) (desc + "_photons_cand_pT_hist_subleadingjet"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     photons_cand_pT_hist_subleadingjet[ibin][ibin2]->Sumw2();
	photons_cand_phi_hist_subleadingjet[ibin][ibin2] = new TH1F((TString) (desc + "_photons_cand_phi_hist_subleadingjet"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 36, 0.,TMath::Pi());     photons_cand_phi_hist_subleadingjet[ibin][ibin2]->Sumw2();
	photons_cand_eta_hist_subleadingjet[ibin][ibin2] = new TH1F((TString) (desc + "_photons_cand_eta_hist_subleadingjet"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50, -5., 5.);     photons_cand_eta_hist_subleadingjet[ibin][ibin2]->Sumw2();
	
	chargedhadrons_cand_pT_hist_subleadingjet[ibin][ibin2] = new TH1F((TString) (desc + "_chargedhadrons_cand_pT_hist_subleadingjet"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 500.);     chargedhadrons_cand_pT_hist_subleadingjet[ibin][ibin2]->Sumw2();
	chargedhadrons_cand_phi_hist_subleadingjet[ibin][ibin2] = new TH1F((TString) (desc + "_chargedhadrons_cand_phi_hist_subleadingjet"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 36, 0.,TMath::Pi());     chargedhadrons_cand_phi_hist_subleadingjet[ibin][ibin2]->Sumw2();
	chargedhadrons_cand_eta_hist_subleadingjet[ibin][ibin2] = new TH1F((TString) (desc + "_chargedhadrons_cand_eta_hist_subleadingjet"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50, -5., 5.);     chargedhadrons_cand_eta_hist_subleadingjet[ibin][ibin2]->Sumw2();
	
	
	NumNeutral_subleadingjet[ibin][ibin2] = new TH1F((TString) (desc + "_NumNeutral_subleadingjet"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumNeutral_subleadingjet[ibin][ibin2]->Sumw2();
	NumPhotons_subleadingjet[ibin][ibin2] = new TH1F((TString) (desc + "_NumPhotons_subleadingjet"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumPhotons_subleadingjet[ibin][ibin2]->Sumw2();
	NumAll_subleadingjet[ibin][ibin2] = new TH1F((TString) (desc + "_NumAll_subleadingjet"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumAll_subleadingjet[ibin][ibin2]->Sumw2();
	
	NumChargedHadrons_subleadingjet[ibin][ibin2] = new TH1F((TString) (desc + "_NumChargedHadrons_subleadingjet"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100, 0., 100.);     NumChargedHadrons_subleadingjet[ibin][ibin2]->Sumw2();
	
	
	
	//SumJetPtFraction_hist_subleadingjet[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_subleadingjet"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100,0.,300);     //SumJetPtFraction_hist_subleadingjet[ibin][ibin2]->Sumw2();
	
	
	SumJetPtFraction_hist_subleadingjet[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_subleadingjet"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_subleadingjet[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_subleadingjet_photons[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_subleadingjet_photons"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_subleadingjet_photons[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_subleadingjet_neutrals[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_subleadingjet_neutrals"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_subleadingjet_neutrals[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_subleadingjet_chargedhadrons[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_subleadingjet_chargedhadrons"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_subleadingjet_chargedhadrons[ibin][ibin2]->Sumw2();
	
	SumJetPtFraction_hist_leadingjet_photons[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_leadingjet_photons"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_leadingjet_photons[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_neutrals[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_leadingjet_neutrals"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_leadingjet_neutrals[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_charged[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_leadingjet_charged"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_leadingjet_charged[ibin][ibin2]->Sumw2();
	
	SumJetPtFraction_hist_leadingjet_chargedhadrons[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_leadingjet_chargedhadrons"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_leadingjet_chargedhadrons[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_chargedparticles[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_leadingjet_chargedparticles"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_leadingjet_chargedparticles[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_electrons[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_leadingjet_electrons"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_leadingjet_electrons[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_muons[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_leadingjet_muons"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_leadingjet_muons[ibin][ibin2]->Sumw2();
	
	
	
	
	/// bkg -- sumpt fraction plots 
	
	SumJetPtFraction_hist_leadingjet_photons_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_leadingjet_photons_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_leadingjet_photons_bkg[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_neutrals_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_leadingjet_neutrals_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_leadingjet_neutrals_bkg[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_chargedhadrons_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_leadingjet_chargedhadrons_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_leadingjet_chargedhadrons_bkg[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_chargedparticles_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_leadingjet_chargedparticles_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_leadingjet_chargedparticles_bkg[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_electrons_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_leadingjet_electrons_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_leadingjet_electrons_bkg[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_muons_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_leadingjet_muons_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_leadingjet_muons_bkg[ibin][ibin2]->Sumw2();
	
	
	
	SumJetPtFraction_hist_subleadingjet_photons_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_subleadingjet_photons_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_subleadingjet_photons_bkg[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_subleadingjet_neutrals_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_subleadingjet_neutrals_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_subleadingjet_neutrals_bkg[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_subleadingjet_chargedhadrons_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_subleadingjet_chargedhadrons_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_subleadingjet_chargedhadrons_bkg[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_subleadingjet_chargedparticles_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_subleadingjet_chargedparticles_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_subleadingjet_chargedparticles_bkg[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_subleadingjet_electrons_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_subleadingjet_electrons_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_subleadingjet_electrons_bkg[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_subleadingjet_muons_bkg[ibin][ibin2] = new TH1F((TString) (desc + "_SumJetPtFraction_hist_subleadingjet_muons_bkg"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50,0.,1.2);     SumJetPtFraction_hist_subleadingjet_muons_bkg[ibin][ibin2]->Sumw2();
	
	
	radius_hist_subleadingjet[ibin][ibin2] = new TH1F((TString) (desc + "_radius_hist_subleadingjet"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50, 0., 5.);     radius_hist_subleadingjet[ibin][ibin2]->Sumw2();
	Centrality_hist[ibin][ibin2] = new TH1F((TString) (desc + "_Centrality_hist_"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 200, 0., 200.);     Centrality_hist[ibin][ibin2]->Sumw2();
	Aj[ibin][ibin2] = new TH1F((TString) (desc + "_Aj"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 25,0.,1.25);     Aj[ibin][ibin2]->Sumw2();
	
	dN_tracks[ibin][ibin2] = new TH1F((TString) (desc + "_dN_tracks"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 300,0.,10.);     dN_tracks[ibin][ibin2]->Sumw2();
	dN_chargedhadrons[ibin][ibin2] = new TH1F((TString) (desc + "_dN_chargedhadrons"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 300,0.,10.);     dN_chargedhadrons[ibin][ibin2]->Sumw2();
	dN_chargedparticles[ibin][ibin2] = new TH1F((TString) (desc + "_dN_chargedparticles"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 300,0.,10.);     dN_chargedparticles[ibin][ibin2]->Sumw2();
	dN_electrons[ibin][ibin2] = new TH1F((TString) (desc + "_dN_electrons"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 300,0.,10.);     dN_electrons[ibin][ibin2]->Sumw2();
	dN_muons[ibin][ibin2] = new TH1F((TString) (desc + "_dN_muons"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 300,0.,10.);     dN_muons[ibin][ibin2]->Sumw2();
	dN_neutrals[ibin][ibin2] = new TH1F((TString) (desc + "_dN_neutrals"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 300,0.,10.);     dN_neutrals[ibin][ibin2]->Sumw2();
	dN_photons[ibin][ibin2] = new TH1F((TString) (desc + "_dN_photons"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 300,0.,10.);     dN_photons[ibin][ibin2]->Sumw2();
	
	JetPt_fraction_hist[ibin][ibin2] = new TH1F((TString) (desc + "_JetPt_fraction_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 100,0.,5);     JetPt_fraction_hist[ibin][ibin2]->Sumw2();
	
	
	
	track_cand_pT_hist_weighted[ibin][ibin2] = new TH1F((TString) (desc + "_track_cand_pT_hist_weighted"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", nPtBintrk,ptBintrk);     track_cand_pT_hist_weighted[ibin][ibin2]->Sumw2();

  track_gen_pT_hist[ibin][ibin2] = new TH1F((TString) (desc + "_track_gen_pT_hist"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", nPtBintrk,ptBintrk);   track_gen_pT_hist[ibin][ibin2]->Sumw2();



	
	SumPt_only[ibin][ibin2] = new TH1F((TString) (desc + "_SumPt_only"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 500, 0., 10.);     SumPt_only[ibin][ibin2]->Sumw2();
	
	
	
	JetEnergy_resolution[ibin][ibin2] = new TH1F((TString) (desc + "_JetEnergy_resolution"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 50, -2., 2.);     JetEnergy_resolution[ibin][ibin2]->Sumw2();
	
	JetEnergy_ratio[ibin][ibin2] = new TH1F((TString) (desc + "_JetEnergy_ratio"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 75, 0., 5.);     JetEnergy_ratio[ibin][ibin2]->Sumw2();
	
	JetEnergy_ratio_new[ibin][ibin2] = new TH1F((TString) (desc + "_JetEnergy_ratio_new"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_strs[ibin2] + "_" + PtBin_strs[ibin2+1]), "", 75, 0., 5.);     JetEnergy_ratio_new[ibin][ibin2]->Sumw2();
	
	
	
	} // pt bin loop
	
	
	for (int ibin3=0;ibin3<nPtBins_sub;ibin3++){  /// pti3 subjet plots
	
	JetShapeDiffParticles_subleadingjet_bkg_1DEtaRef[ibin][ibin3] = new TH1F((TString) (desc + "_JetShapeDiffParticles_subleadingjet_bkg_1DEtaRef"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_sub_strs[ibin3] + "_" + PtBin_sub_strs[ibin3+1]), "", 6,0.0,0.3);     JetShapeDiffParticles_subleadingjet_bkg_1DEtaRef[ibin][ibin3]->Sumw2();     
	
	JetShapeIntegratedParticles_subleadingjet_1D[ibin][ibin3] = new TH1F((TString) (desc + "_JetShapeIntegratedParticles_subleadingjet_1D"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_sub_strs[ibin3] + "_" + PtBin_sub_strs[ibin3+1]), "", 6,0.05,0.35);     JetShapeIntegratedParticles_subleadingjet_1D[ibin][ibin3]->Sumw2();
	
	JetShapeDiffParticles_subleadingjet_bkg_1D[ibin][ibin3] = new TH1F((TString) (desc + "_JetShapeDiffParticles_subleadingjet_bkg_1D"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_sub_strs[ibin3] + "_" + PtBin_sub_strs[ibin3+1]), "", 6,0.0,0.3);     JetShapeDiffParticles_subleadingjet_bkg_1D[ibin][ibin3]->Sumw2();    
	
	JetShapeDiffParticles_subleadingjet_1D[ibin][ibin3] = new TH1F((TString) (desc + "_JetShapeDiffParticles_subleadingjet_1D"+ CBin_strs[ibin] + "_" + CBin_strs[ibin+1] + "_" + PtBin_sub_strs[ibin3] + "_" + PtBin_sub_strs[ibin3+1]), "", 6,0.0,0.3);     JetShapeDiffParticles_subleadingjet_1D[ibin][ibin3]->Sumw2();   
	}
	
	
	} // centrality bin loop
	} // hist class loop
	
	void hist_class::NormalizeByCounts()
	{
	for(int centi = 0; centi < nCBins; centi++) {
	for(int pti = 0; pti < nPtBins; pti++) {
	
	if( sig_count[centi][pti] < 0.5e-18 ) continue;
	JetShapeDiffParticles_1D[centi][pti]->Scale(1. / sig_count[centi][pti]);
	JetShapeDiffParticlesGen_1D[centi][pti]->Scale(1. / sig_count[centi][pti]);
	
	if( bkg_count[centi][pti] < 0.5e-18  ) continue;
	JetShapeDiffParticles_bkg_1D[centi][pti]->Scale(1. / bkg_count[centi][pti]);
	JetShapeDiffParticlesGen_bkg_1D[centi][pti]->Scale(1. / bkg_count[centi][pti]);
	
	}
	
	for(int pti_sub = 0; pti_sub < nPtBins_sub; pti_sub++) {
	
	if( sig_count_sub[centi][pti_sub] < 0.5e-18 ) continue;
	JetShapeDiffParticles_subleadingjet_1D[centi][pti_sub]->Scale(1. / sig_count_sub[centi][pti_sub]);
	
	if( bkg_count_sub[centi][pti_sub] < 0.5e-18  ) continue;
	JetShapeDiffParticles_subleadingjet_bkg_1D[centi][pti_sub]->Scale(1. / bkg_count_sub[centi][pti_sub]);
	
	}
	
	
	}
	
	
	}
	
	
	
	
	
	void hist_class::AddHists(hist_class *more_hists, float wt)
	{
	
	
	std::cout << "AddHists" << std::endl;
	for(int centi = 0; centi < nCBins; centi++) {
	for(int pti = 0; pti < nPtBins; pti++) {
	std::cout << "centi: " << centi << ", ptio : " << pti << ", wt: " << wt << ", add signal: " << more_hists->sig_count[centi][pti] << ", bkg: " << more_hists->bkg_count[centi][pti] << ", result signal: " << sig_count[centi][pti] << ", result_bkg: " << bkg_count[centi][pti] << "\n";
	sig_count[centi][pti] += more_hists->sig_count[centi][pti]*wt;
	bkg_count[centi][pti] += more_hists->bkg_count[centi][pti]*wt;
	
	}
	
	for(int pti_sub = 0; pti_sub < nPtBins_sub; pti_sub++) {
	std::cout << "centi: " << centi << ", ptio_sub : " << pti_sub << ", wt: " << wt << ", add signal: " << more_hists->sig_count_sub[centi][pti_sub] << ", bkg: " << more_hists->bkg_count_sub[centi][pti_sub] << ", result signal: " << sig_count_sub[centi][pti_sub] << ", result_bkg: " << bkg_count[centi][pti_sub] << "\n";
	
	sig_count_sub[centi][pti_sub] += more_hists->sig_count_sub[centi][pti_sub]*wt;
	bkg_count_sub[centi][pti_sub] += more_hists->bkg_count_sub[centi][pti_sub]*wt;
	
	}
	
	
	}
	
	
	//    JetEnergy_gen_vs_rec->Sumw2();   more_hists->JetEnergy_gen_vs_rec->Sumw2();
	//      JetEnergy_gen_vs_rec->Add(more_hists->JetEnergy_gen_vs_rec, wt);
	
	
	NEvents->Sumw2();   more_hists->NEvents->Sumw2();
	NEvents->Add(more_hists->NEvents, wt);
	
	NEvents_test->Sumw2();   more_hists->NEvents_test->Sumw2();
	NEvents_test->Add(more_hists->NEvents_test, wt);
	
	NEvents_after_noise->Add(more_hists->NEvents_after_noise, wt);
	NEvents_after_spike->Add(more_hists->NEvents_after_spike, wt);
	
	NEvents_after_dphi->Sumw2();   more_hists->NEvents_after_dphi->Sumw2();
	NEvents_after_dphi->Add(more_hists->NEvents_after_dphi, wt);
	
	NEvents_before_dphi->Sumw2();   more_hists->NEvents_before_dphi->Sumw2();
	NEvents_before_dphi->Add(more_hists->NEvents_before_dphi, wt);
	
	NEvents_dijets->Sumw2();   more_hists->NEvents_dijets->Sumw2();
	NEvents_dijets->Add(more_hists->NEvents_dijets, wt);
	
	NEvents_after_trigger->Sumw2();   more_hists->NEvents_after_trigger->Sumw2();
	NEvents_after_trigger->Add(more_hists->NEvents_after_trigger, wt);
	
	AllJetPt_raw_hist->Sumw2();   more_hists->AllJetPt_raw_hist->Sumw2();
	AllJetPt_raw_hist->Add(more_hists->AllJetPt_raw_hist, wt);
	AllJetPt_hist->Sumw2();   more_hists->AllJetPt_hist->Sumw2();
	AllJetPt_hist->Add(more_hists->AllJetPt_hist, wt);
	AllJetPhi_hist->Sumw2();   more_hists->AllJetPhi_hist->Sumw2();
	AllJetPhi_hist->Add(more_hists->AllJetPhi_hist, wt);
	AllJetEta_hist->Sumw2();   more_hists->AllJetEta_hist->Sumw2();
	AllJetEta_hist->Add(more_hists->AllJetEta_hist, wt);
	
	First_AllJetPt_hist->Sumw2();   more_hists->First_AllJetPt_hist->Sumw2();
	First_AllJetPt_hist->Add(more_hists->First_AllJetPt_hist, wt);
	
	First_AllJetPhi_hist->Sumw2();   more_hists->First_AllJetPhi_hist->Sumw2();
	First_AllJetPhi_hist->Add(more_hists->First_AllJetPhi_hist, wt);
	
	First_AllJetEta_hist->Sumw2();   more_hists->First_AllJetEta_hist->Sumw2();
	First_AllJetEta_hist->Add(more_hists->First_AllJetEta_hist, wt);
	
	Sub_AllJetPt_hist->Sumw2();   more_hists->Sub_AllJetPt_hist->Sumw2();
	Sub_AllJetPt_hist->Add(more_hists->Sub_AllJetPt_hist, wt);
	
	Sub_AllJetPhi_hist->Sumw2();   more_hists->Sub_AllJetPhi_hist->Sumw2();
	Sub_AllJetPhi_hist->Add(more_hists->Sub_AllJetPhi_hist, wt);
	
	Sub_AllJetEta_hist->Sumw2();   more_hists->Sub_AllJetEta_hist->Sumw2();
	Sub_AllJetEta_hist->Add(more_hists->Sub_AllJetEta_hist, wt);
	
	JetPt_fraction->Sumw2();   more_hists->JetPt_fraction->Sumw2();
	JetPt_fraction->Add(more_hists->JetPt_fraction, wt);
	
	
	Centrality->Sumw2();   more_hists->Centrality->Sumw2();
	Centrality->Add(more_hists->Centrality, wt);
	
	track_vz->Sumw2();   more_hists->track_vz->Sumw2();
	track_vz->Add(more_hists->track_vz, wt);
	
	track_vz_weighted->Sumw2();   more_hists->track_vz_weighted->Sumw2();
	track_vz_weighted->Add(more_hists->track_vz_weighted, wt);
	
	for (int ibin2=0;ibin2<nPtBins;ibin2++){
	fullrecjet_aftercuts[ibin2]->Sumw2();   more_hists->fullrecjet_aftercuts[ibin2]->Sumw2();
	fullrecjet_aftercuts[ibin2]->Add(more_hists->fullrecjet_aftercuts[ibin2], wt);
	
	fullrefjet_aftercuts[ibin2]->Sumw2();   more_hists->fullrefjet_aftercuts[ibin2]->Sumw2();
	fullrefjet_aftercuts[ibin2]->Add(more_hists->fullrefjet_aftercuts[ibin2], wt);
	
	
	}
	
	for (int ibin=0;ibin<nCBins;ibin++){
	
	jet_pT_hist[ibin]->Sumw2();   more_hists->jet_pT_hist[ibin]->Sumw2();
	jet_pT_hist[ibin]->Add(more_hists->jet_pT_hist[ibin], wt);
	jet_phi_hist[ibin]->Sumw2();   more_hists->jet_phi_hist[ibin]->Sumw2();
	jet_phi_hist[ibin]->Add(more_hists->jet_phi_hist[ibin], wt);
	jet_eta_hist[ibin]->Sumw2();   more_hists->jet_eta_hist[ibin]->Sumw2();
	jet_eta_hist[ibin]->Add(more_hists->jet_eta_hist[ibin], wt);
	jet_corrpT_hist[ibin]->Sumw2();   more_hists->jet_corrpT_hist[ibin]->Sumw2();
	jet_corrpT_hist[ibin]->Add(more_hists->jet_corrpT_hist[ibin], wt);
	LeadingJetPt_hist[ibin]->Sumw2();   more_hists->LeadingJetPt_hist[ibin]->Sumw2();
	LeadingJetPt_hist[ibin]->Add(more_hists->LeadingJetPt_hist[ibin], wt);
	LeadingJetPhi_hist[ibin]->Sumw2();   more_hists->LeadingJetPhi_hist[ibin]->Sumw2();
	LeadingJetPhi_hist[ibin]->Add(more_hists->LeadingJetPhi_hist[ibin], wt);
	LeadingJetEta_hist[ibin]->Sumw2();   more_hists->LeadingJetEta_hist[ibin]->Sumw2();
	LeadingJetEta_hist[ibin]->Add(more_hists->LeadingJetEta_hist[ibin], wt);
	SubJetPt_hist[ibin]->Sumw2();   more_hists->SubJetPt_hist[ibin]->Sumw2();
	SubJetPt_hist[ibin]->Add(more_hists->SubJetPt_hist[ibin], wt);
	SubJetPhi_hist[ibin]->Sumw2();   more_hists->SubJetPhi_hist[ibin]->Sumw2();
	SubJetPhi_hist[ibin]->Add(more_hists->SubJetPhi_hist[ibin], wt);
	SubJetEta_hist[ibin]->Sumw2();   more_hists->SubJetEta_hist[ibin]->Sumw2();
	SubJetEta_hist[ibin]->Add(more_hists->SubJetEta_hist[ibin], wt);
	
	dPhi_leadingjet_hist[ibin]->Sumw2();   more_hists->dPhi_leadingjet_hist[ibin]->Sumw2();
	dPhi_leadingjet_hist[ibin]->Add(more_hists->dPhi_leadingjet_hist[ibin], wt);
	dPhi_subleadingjet_hist[ibin]->Sumw2();   more_hists->dPhi_subleadingjet_hist[ibin]->Sumw2();
	dPhi_subleadingjet_hist[ibin]->Add(more_hists->dPhi_subleadingjet_hist[ibin], wt);
	
	JetShapeDiffParticles_bkg_1D_total[ibin]->Sumw2();   more_hists->JetShapeDiffParticles_bkg_1D_total[ibin]->Sumw2();
	JetShapeDiffParticles_bkg_1D_total[ibin]->Add(more_hists->JetShapeDiffParticles_bkg_1D_total[ibin], wt);
	
	JetShapeIntegratedParticles_bkg_1D_total[ibin]->Sumw2();   more_hists->JetShapeIntegratedParticles_bkg_1D_total[ibin]->Sumw2();
	JetShapeIntegratedParticles_bkg_1D_total[ibin]->Add(more_hists->JetShapeIntegratedParticles_bkg_1D_total[ibin], wt);
	
	
	JetEnergy_gen_vs_rec[ibin]->Sumw2();   more_hists->JetEnergy_gen_vs_rec[ibin]->Sumw2();
	JetEnergy_gen_vs_rec[ibin]->Add(more_hists->JetEnergy_gen_vs_rec[ibin], wt);
	
	
	
	for (int ibin2=0;ibin2<nPtBins;ibin2++){ 
	// ThirdJetPt_histgibin][ibin2]->Sumw2();   more_hists->ThirdJetPt_hist[ibin][ibin2]->Sumw2();
	//ThirdJetPt_hist[ibin][ibin2]->Add(more_hists->ThirdJetPt_hist[ibin][ibin2], wt);
	ThirdJetPhi_hist[ibin][ibin2]->Sumw2();   more_hists->ThirdJetPhi_hist[ibin][ibin2]->Sumw2();
	ThirdJetPhi_hist[ibin][ibin2]->Add(more_hists->ThirdJetPhi_hist[ibin][ibin2], wt);
	ThirdJetEta_hist[ibin][ibin2]->Sumw2();   more_hists->ThirdJetEta_hist[ibin][ibin2]->Sumw2();
	ThirdJetEta_hist[ibin][ibin2]->Add(more_hists->ThirdJetEta_hist[ibin][ibin2], wt);
	dPhi_hist[ibin][ibin2]->Sumw2();   more_hists->dPhi_hist[ibin][ibin2]->Sumw2();
	dPhi_hist[ibin][ibin2]->Add(more_hists->dPhi_hist[ibin][ibin2], wt);
	dPhi_after_hist[ibin][ibin2]->Sumw2();   more_hists->dPhi_after_hist[ibin][ibin2]->Sumw2();
	dPhi_after_hist[ibin][ibin2]->Add(more_hists->dPhi_after_hist[ibin][ibin2], wt);
	
	
	
	all_jets_corrpT[ibin][ibin2]->Sumw2();   more_hists->all_jets_corrpT[ibin][ibin2]->Sumw2();
	all_jets_corrpT[ibin][ibin2]->Add(more_hists->all_jets_corrpT[ibin][ibin2], wt);
	all_jets_phi[ibin][ibin2]->Sumw2();   more_hists->all_jets_phi[ibin][ibin2]->Sumw2();
	all_jets_phi[ibin][ibin2]->Add(more_hists->all_jets_phi[ibin][ibin2], wt);
	all_jets_eta[ibin][ibin2]->Sumw2();   more_hists->all_jets_eta[ibin][ibin2]->Sumw2();
	all_jets_eta[ibin][ibin2]->Add(more_hists->all_jets_eta[ibin][ibin2], wt);
	
	//// leading jet histograms
	only_leadingjets_corrpT[ibin][ibin2]->Sumw2();   more_hists->only_leadingjets_corrpT[ibin][ibin2]->Sumw2();
	only_leadingjets_corrpT[ibin][ibin2]->Add(more_hists->only_leadingjets_corrpT[ibin][ibin2], wt);
	only_leadingjets_phi[ibin][ibin2]->Sumw2();   more_hists->only_leadingjets_phi[ibin][ibin2]->Sumw2();
	only_leadingjets_phi[ibin][ibin2]->Add(more_hists->only_leadingjets_phi[ibin][ibin2], wt);
	only_leadingjets_eta[ibin][ibin2]->Sumw2();   more_hists->only_leadingjets_eta[ibin][ibin2]->Sumw2();
	only_leadingjets_eta[ibin][ibin2]->Add(more_hists->only_leadingjets_eta[ibin][ibin2], wt);
	all_cand_pT_hist[ibin][ibin2]->Sumw2();   more_hists->all_cand_pT_hist[ibin][ibin2]->Sumw2();
	all_cand_pT_hist[ibin][ibin2]->Add(more_hists->all_cand_pT_hist[ibin][ibin2], wt);
	all_cand_phi_hist[ibin][ibin2]->Sumw2();   more_hists->all_cand_phi_hist[ibin][ibin2]->Sumw2();
	all_cand_phi_hist[ibin][ibin2]->Add(more_hists->all_cand_phi_hist[ibin][ibin2], wt);
	all_cand_eta_hist[ibin][ibin2]->Sumw2();   more_hists->all_cand_eta_hist[ibin][ibin2]->Sumw2();
	all_cand_eta_hist[ibin][ibin2]->Add(more_hists->all_cand_eta_hist[ibin][ibin2], wt);
	
	track_cand_pT_hist[ibin][ibin2]->Sumw2();   more_hists->track_cand_pT_hist[ibin][ibin2]->Sumw2();
	track_cand_pT_hist[ibin][ibin2]->Add(more_hists->track_cand_pT_hist[ibin][ibin2], wt);
	track_cand_phi_hist[ibin][ibin2]->Sumw2();   more_hists->track_cand_phi_hist[ibin][ibin2]->Sumw2();
	track_cand_phi_hist[ibin][ibin2]->Add(more_hists->track_cand_phi_hist[ibin][ibin2], wt);
	track_cand_eta_hist[ibin][ibin2]->Sumw2();   more_hists->track_cand_eta_hist[ibin][ibin2]->Sumw2();
	track_cand_eta_hist[ibin][ibin2]->Add(more_hists->track_cand_eta_hist[ibin][ibin2], wt);
	
	
	track_cand_pT_hist_subleadingjet[ibin][ibin2]->Sumw2();   more_hists->track_cand_pT_hist_subleadingjet[ibin][ibin2]->Sumw2();
	track_cand_pT_hist_subleadingjet[ibin][ibin2]->Add(more_hists->track_cand_pT_hist_subleadingjet[ibin][ibin2], wt);
	
	neutral_cand_pT_hist[ibin][ibin2]->Sumw2();   more_hists->neutral_cand_pT_hist[ibin][ibin2]->Sumw2();
	neutral_cand_pT_hist[ibin][ibin2]->Add(more_hists->neutral_cand_pT_hist[ibin][ibin2], wt);
	neutral_cand_phi_hist[ibin][ibin2]->Sumw2();   more_hists->neutral_cand_phi_hist[ibin][ibin2]->Sumw2();
	neutral_cand_phi_hist[ibin][ibin2]->Add(more_hists->neutral_cand_phi_hist[ibin][ibin2], wt);
	neutral_cand_eta_hist[ibin][ibin2]->Sumw2();   more_hists->neutral_cand_eta_hist[ibin][ibin2]->Sumw2();
	neutral_cand_eta_hist[ibin][ibin2]->Add(more_hists->neutral_cand_eta_hist[ibin][ibin2], wt);
	photons_cand_pT_hist[ibin][ibin2]->Sumw2();   more_hists->photons_cand_pT_hist[ibin][ibin2]->Sumw2();
	photons_cand_pT_hist[ibin][ibin2]->Add(more_hists->photons_cand_pT_hist[ibin][ibin2], wt);
	photons_cand_phi_hist[ibin][ibin2]->Sumw2();   more_hists->photons_cand_phi_hist[ibin][ibin2]->Sumw2();
	photons_cand_phi_hist[ibin][ibin2]->Add(more_hists->photons_cand_phi_hist[ibin][ibin2], wt);
	photons_cand_eta_hist[ibin][ibin2]->Sumw2();   more_hists->photons_cand_eta_hist[ibin][ibin2]->Sumw2();
	photons_cand_eta_hist[ibin][ibin2]->Add(more_hists->photons_cand_eta_hist[ibin][ibin2], wt);
	
	
	NumNeutral[ibin][ibin2]->Sumw2();   more_hists->NumNeutral[ibin][ibin2]->Sumw2();
	NumNeutral[ibin][ibin2]->Add(more_hists->NumNeutral[ibin][ibin2], wt);
	NumPhotons[ibin][ibin2]->Sumw2();   more_hists->NumPhotons[ibin][ibin2]->Sumw2();
	NumPhotons[ibin][ibin2]->Add(more_hists->NumPhotons[ibin][ibin2], wt);
	NumAll[ibin][ibin2]->Sumw2();   more_hists->NumAll[ibin][ibin2]->Sumw2();
	NumAll[ibin][ibin2]->Add(more_hists->NumAll[ibin][ibin2], wt);
	NumCharged[ibin][ibin2]->Sumw2();   more_hists->NumCharged[ibin][ibin2]->Sumw2();
	NumCharged[ibin][ibin2]->Add(more_hists->NumCharged[ibin][ibin2], wt);
	NumChargedHadrons[ibin][ibin2]->Sumw2();   more_hists->NumChargedHadrons[ibin][ibin2]->Sumw2();
	NumChargedHadrons[ibin][ibin2]->Add(more_hists->NumChargedHadrons[ibin][ibin2], wt);
	NumChargedParticles[ibin][ibin2]->Sumw2();   more_hists->NumChargedParticles[ibin][ibin2]->Sumw2();
	NumChargedParticles[ibin][ibin2]->Add(more_hists->NumChargedParticles[ibin][ibin2], wt);
	NumElectrons[ibin][ibin2]->Sumw2();   more_hists->NumElectrons[ibin][ibin2]->Sumw2();
	NumElectrons[ibin][ibin2]->Add(more_hists->NumElectrons[ibin][ibin2], wt);
	NumMuons[ibin][ibin2]->Sumw2();   more_hists->NumMuons[ibin][ibin2]->Sumw2();
	NumMuons[ibin][ibin2]->Add(more_hists->NumMuons[ibin][ibin2], wt);
	
	
	NumNeutral_bkg[ibin][ibin2]->Sumw2();   more_hists->NumNeutral_bkg[ibin][ibin2]->Sumw2();
	NumNeutral_bkg[ibin][ibin2]->Add(more_hists->NumNeutral_bkg[ibin][ibin2], wt);
	NumPhotons_bkg[ibin][ibin2]->Sumw2();   more_hists->NumPhotons_bkg[ibin][ibin2]->Sumw2();
	NumPhotons_bkg[ibin][ibin2]->Add(more_hists->NumPhotons_bkg[ibin][ibin2], wt);
	NumAll_bkg[ibin][ibin2]->Sumw2();   more_hists->NumAll_bkg[ibin][ibin2]->Sumw2();
	NumAll_bkg[ibin][ibin2]->Add(more_hists->NumAll_bkg[ibin][ibin2], wt);
	NumChargedHadrons_bkg[ibin][ibin2]->Sumw2();   more_hists->NumChargedHadrons_bkg[ibin][ibin2]->Sumw2();
	NumChargedHadrons_bkg[ibin][ibin2]->Add(more_hists->NumChargedHadrons_bkg[ibin][ibin2], wt);
	NumChargedParticles_bkg[ibin][ibin2]->Sumw2();   more_hists->NumChargedParticles_bkg[ibin][ibin2]->Sumw2();
	NumChargedParticles_bkg[ibin][ibin2]->Add(more_hists->NumChargedParticles_bkg[ibin][ibin2], wt);
	NumElectrons_bkg[ibin][ibin2]->Sumw2();   more_hists->NumElectrons_bkg[ibin][ibin2]->Sumw2();
	NumElectrons_bkg[ibin][ibin2]->Add(more_hists->NumElectrons_bkg[ibin][ibin2], wt);
	NumMuons_bkg[ibin][ibin2]->Sumw2();   more_hists->NumMuons_bkg[ibin][ibin2]->Sumw2();
	NumMuons_bkg[ibin][ibin2]->Add(more_hists->NumMuons_bkg[ibin][ibin2], wt);
	
	
	chargedhadrons_cand_pT_hist[ibin][ibin2]->Sumw2();   more_hists->chargedhadrons_cand_pT_hist[ibin][ibin2]->Sumw2();
	chargedhadrons_cand_pT_hist[ibin][ibin2]->Add(more_hists->chargedhadrons_cand_pT_hist[ibin][ibin2], wt);
	chargedhadrons_cand_phi_hist[ibin][ibin2]->Sumw2();   more_hists->chargedhadrons_cand_phi_hist[ibin][ibin2]->Sumw2();
	chargedhadrons_cand_phi_hist[ibin][ibin2]->Add(more_hists->chargedhadrons_cand_phi_hist[ibin][ibin2], wt);
	chargedhadrons_cand_eta_hist[ibin][ibin2]->Sumw2();   more_hists->chargedhadrons_cand_eta_hist[ibin][ibin2]->Sumw2();
	chargedhadrons_cand_eta_hist[ibin][ibin2]->Add(more_hists->chargedhadrons_cand_eta_hist[ibin][ibin2], wt);
	
	chargedparticles_cand_pT_hist[ibin][ibin2]->Sumw2();   more_hists->chargedparticles_cand_pT_hist[ibin][ibin2]->Sumw2();
	chargedparticles_cand_pT_hist[ibin][ibin2]->Add(more_hists->chargedparticles_cand_pT_hist[ibin][ibin2], wt);
	chargedparticles_cand_phi_hist[ibin][ibin2]->Sumw2();   more_hists->chargedparticles_cand_phi_hist[ibin][ibin2]->Sumw2();
	chargedparticles_cand_phi_hist[ibin][ibin2]->Add(more_hists->chargedparticles_cand_phi_hist[ibin][ibin2], wt);
	chargedparticles_cand_eta_hist[ibin][ibin2]->Sumw2();   more_hists->chargedparticles_cand_eta_hist[ibin][ibin2]->Sumw2();
	chargedparticles_cand_eta_hist[ibin][ibin2]->Add(more_hists->chargedparticles_cand_eta_hist[ibin][ibin2], wt);
	
	electrons_cand_pT_hist[ibin][ibin2]->Sumw2();   more_hists->electrons_cand_pT_hist[ibin][ibin2]->Sumw2();
	electrons_cand_pT_hist[ibin][ibin2]->Add(more_hists->electrons_cand_pT_hist[ibin][ibin2], wt);
	electrons_cand_phi_hist[ibin][ibin2]->Sumw2();   more_hists->electrons_cand_phi_hist[ibin][ibin2]->Sumw2();
	electrons_cand_phi_hist[ibin][ibin2]->Add(more_hists->electrons_cand_phi_hist[ibin][ibin2], wt);
	electrons_cand_eta_hist[ibin][ibin2]->Sumw2();   more_hists->electrons_cand_eta_hist[ibin][ibin2]->Sumw2();
	electrons_cand_eta_hist[ibin][ibin2]->Add(more_hists->electrons_cand_eta_hist[ibin][ibin2], wt);
	
	muons_cand_pT_hist[ibin][ibin2]->Sumw2();   more_hists->muons_cand_pT_hist[ibin][ibin2]->Sumw2();
	muons_cand_pT_hist[ibin][ibin2]->Add(more_hists->muons_cand_pT_hist[ibin][ibin2], wt);
	muons_cand_phi_hist[ibin][ibin2]->Sumw2();   more_hists->muons_cand_phi_hist[ibin][ibin2]->Sumw2();
	muons_cand_phi_hist[ibin][ibin2]->Add(more_hists->muons_cand_phi_hist[ibin][ibin2], wt);
	muons_cand_eta_hist[ibin][ibin2]->Sumw2();   more_hists->muons_cand_eta_hist[ibin][ibin2]->Sumw2();
	muons_cand_eta_hist[ibin][ibin2]->Add(more_hists->muons_cand_eta_hist[ibin][ibin2], wt);
	/////
	
	
	muons_cand_pT_hist_bkg[ibin][ibin2]->Sumw2();   more_hists->muons_cand_pT_hist_bkg[ibin][ibin2]->Sumw2();
	muons_cand_pT_hist_bkg[ibin][ibin2]->Add(more_hists->muons_cand_pT_hist_bkg[ibin][ibin2], wt);
	electrons_cand_pT_hist_bkg[ibin][ibin2]->Sumw2();   more_hists->electrons_cand_pT_hist_bkg[ibin][ibin2]->Sumw2();
	electrons_cand_pT_hist_bkg[ibin][ibin2]->Add(more_hists->electrons_cand_pT_hist_bkg[ibin][ibin2], wt);
	chargedparticles_cand_pT_hist_bkg[ibin][ibin2]->Sumw2();   more_hists->chargedparticles_cand_pT_hist_bkg[ibin][ibin2]->Sumw2();
	chargedparticles_cand_pT_hist_bkg[ibin][ibin2]->Add(more_hists->chargedparticles_cand_pT_hist_bkg[ibin][ibin2], wt);
	chargedhadrons_cand_pT_hist_bkg[ibin][ibin2]->Sumw2();   more_hists->chargedhadrons_cand_pT_hist_bkg[ibin][ibin2]->Sumw2();
	chargedhadrons_cand_pT_hist_bkg[ibin][ibin2]->Add(more_hists->chargedhadrons_cand_pT_hist_bkg[ibin][ibin2], wt);
	neutral_cand_pT_hist_bkg[ibin][ibin2]->Sumw2();   more_hists->neutral_cand_pT_hist_bkg[ibin][ibin2]->Sumw2();
	neutral_cand_pT_hist_bkg[ibin][ibin2]->Add(more_hists->neutral_cand_pT_hist_bkg[ibin][ibin2], wt);
	photons_cand_pT_hist_bkg[ibin][ibin2]->Sumw2();   more_hists->photons_cand_pT_hist_bkg[ibin][ibin2]->Sumw2();
	photons_cand_pT_hist_bkg[ibin][ibin2]->Add(more_hists->photons_cand_pT_hist_bkg[ibin][ibin2], wt);
	
	
	SumJetPtFraction_hist[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist[ibin][ibin2], wt);
	
	JetShapeIntegratedParticles[ibin][ibin2]->Sumw2();   more_hists->JetShapeIntegratedParticles[ibin][ibin2]->Sumw2();
	JetShapeIntegratedParticles[ibin][ibin2]->Add(more_hists->JetShapeIntegratedParticles[ibin][ibin2], wt);
	JetShapeDiffParticles[ibin][ibin2]->Sumw2();   more_hists->JetShapeDiffParticles[ibin][ibin2]->Sumw2();
	JetShapeDiffParticles[ibin][ibin2]->Add(more_hists->JetShapeDiffParticles[ibin][ibin2], wt);
	
	JetShapeIntegratedParticles_bkgsub[ibin][ibin2]->Sumw2();   more_hists->JetShapeIntegratedParticles_bkgsub[ibin][ibin2]->Sumw2();
	JetShapeIntegratedParticles_bkgsub[ibin][ibin2]->Add(more_hists->JetShapeIntegratedParticles_bkgsub[ibin][ibin2], wt);
	
	JetShapeDiffParticles_bkgsub[ibin][ibin2]->Sumw2();   more_hists->JetShapeDiffParticles_bkgsub[ibin][ibin2]->Sumw2();
	JetShapeDiffParticles_bkgsub[ibin][ibin2]->Add(more_hists->JetShapeDiffParticles_bkgsub[ibin][ibin2], wt);
	
	
	JetShapeIntegratedParticles_bkg[ibin][ibin2]->Sumw2();   more_hists->JetShapeIntegratedParticles_bkg[ibin][ibin2]->Sumw2();
	JetShapeIntegratedParticles_bkg[ibin][ibin2]->Add(more_hists->JetShapeIntegratedParticles_bkg[ibin][ibin2], wt);
	
	JetShapeDiffParticles_bkg[ibin][ibin2]->Sumw2();   more_hists->JetShapeDiffParticles_bkg[ibin][ibin2]->Sumw2();
	JetShapeDiffParticles_bkg[ibin][ibin2]->Add(more_hists->JetShapeDiffParticles_bkg[ibin][ibin2], wt);
	
	
	JetShapeIntegratedParticles_bkg_1D[ibin][ibin2]->Sumw2();   more_hists->JetShapeIntegratedParticles_bkg_1D[ibin][ibin2]->Sumw2();
	JetShapeIntegratedParticles_bkg_1D[ibin][ibin2]->Add(more_hists->JetShapeIntegratedParticles_bkg_1D[ibin][ibin2], wt);
	JetShapeDiffParticles_bkg_1D[ibin][ibin2]->Sumw2();   more_hists->JetShapeDiffParticles_bkg_1D[ibin][ibin2]->Sumw2();
	JetShapeDiffParticles_bkg_1D[ibin][ibin2]->Add(more_hists->JetShapeDiffParticles_bkg_1D[ibin][ibin2], wt);
	
	JetShapeIntegratedParticles_1D[ibin][ibin2]->Sumw2();   more_hists->JetShapeIntegratedParticles_1D[ibin][ibin2]->Sumw2();
	JetShapeIntegratedParticles_1D[ibin][ibin2]->Add(more_hists->JetShapeIntegratedParticles_1D[ibin][ibin2], wt);
	JetShapeDiffParticles_1D[ibin][ibin2]->Sumw2();   more_hists->JetShapeDiffParticles_1D[ibin][ibin2]->Sumw2();
	JetShapeDiffParticles_1D[ibin][ibin2]->Add(more_hists->JetShapeDiffParticles_1D[ibin][ibin2], wt);
	
	
	JetShapeDiffParticlesGen_1D[ibin][ibin2]->Sumw2();   more_hists->JetShapeDiffParticlesGen_1D[ibin][ibin2]->Sumw2();
	JetShapeDiffParticlesGen_1D[ibin][ibin2]->Add(more_hists->JetShapeDiffParticlesGen_1D[ibin][ibin2], wt);
	
	JetShapeDiffParticlesGen_bkg_1D[ibin][ibin2]->Sumw2();   more_hists->JetShapeDiffParticlesGen_bkg_1D[ibin][ibin2]->Sumw2();
	JetShapeDiffParticlesGen_bkg_1D[ibin][ibin2]->Add(more_hists->JetShapeDiffParticlesGen_bkg_1D[ibin][ibin2], wt);
		
	
	
	radius_hist[ibin][ibin2]->Sumw2();   more_hists->radius_hist[ibin][ibin2]->Sumw2();
	radius_hist[ibin][ibin2]->Add(more_hists->radius_hist[ibin][ibin2], wt);

        radius_hist_mine[ibin][ibin2]->Sumw2();   more_hists->radius_hist_mine[ibin][ibin2]->Sumw2();
	radius_hist_mine[ibin][ibin2]->Add(more_hists->radius_hist_mine[ibin][ibin2], wt);



	
	//// subleading jet histograms
	only_subleadingjets_corrpT[ibin][ibin2]->Sumw2();   more_hists->only_subleadingjets_corrpT[ibin][ibin2]->Sumw2();
	only_subleadingjets_corrpT[ibin][ibin2]->Add(more_hists->only_subleadingjets_corrpT[ibin][ibin2], wt);
	only_subleadingjets_phi[ibin][ibin2]->Sumw2();   more_hists->only_subleadingjets_phi[ibin][ibin2]->Sumw2();
	only_subleadingjets_phi[ibin][ibin2]->Add(more_hists->only_subleadingjets_phi[ibin][ibin2], wt);
	only_subleadingjets_eta[ibin][ibin2]->Sumw2();   more_hists->only_subleadingjets_eta[ibin][ibin2]->Sumw2();
	only_subleadingjets_eta[ibin][ibin2]->Add(more_hists->only_subleadingjets_eta[ibin][ibin2], wt);
	all_cand_pT_hist_subleadingjet[ibin][ibin2]->Sumw2();   more_hists->all_cand_pT_hist_subleadingjet[ibin][ibin2]->Sumw2();
	all_cand_pT_hist_subleadingjet[ibin][ibin2]->Add(more_hists->all_cand_pT_hist_subleadingjet[ibin][ibin2], wt);
	all_cand_phi_hist_subleadingjet[ibin][ibin2]->Sumw2();   more_hists->all_cand_phi_hist_subleadingjet[ibin][ibin2]->Sumw2();
	all_cand_phi_hist_subleadingjet[ibin][ibin2]->Add(more_hists->all_cand_phi_hist_subleadingjet[ibin][ibin2], wt);
	all_cand_eta_hist_subleadingjet[ibin][ibin2]->Sumw2();   more_hists->all_cand_eta_hist_subleadingjet[ibin][ibin2]->Sumw2();
	all_cand_eta_hist_subleadingjet[ibin][ibin2]->Add(more_hists->all_cand_eta_hist_subleadingjet[ibin][ibin2], wt);
	neutral_cand_pT_hist_subleadingjet[ibin][ibin2]->Sumw2();   more_hists->neutral_cand_pT_hist_subleadingjet[ibin][ibin2]->Sumw2();
	neutral_cand_pT_hist_subleadingjet[ibin][ibin2]->Add(more_hists->neutral_cand_pT_hist_subleadingjet[ibin][ibin2], wt);
	neutral_cand_phi_hist_subleadingjet[ibin][ibin2]->Sumw2();   more_hists->neutral_cand_phi_hist_subleadingjet[ibin][ibin2]->Sumw2();
	neutral_cand_phi_hist_subleadingjet[ibin][ibin2]->Add(more_hists->neutral_cand_phi_hist_subleadingjet[ibin][ibin2], wt);
	neutral_cand_eta_hist_subleadingjet[ibin][ibin2]->Sumw2();   more_hists->neutral_cand_eta_hist_subleadingjet[ibin][ibin2]->Sumw2();
	neutral_cand_eta_hist_subleadingjet[ibin][ibin2]->Add(more_hists->neutral_cand_eta_hist_subleadingjet[ibin][ibin2], wt);
	
	
	photons_cand_pT_hist_subleadingjet[ibin][ibin2]->Sumw2();   more_hists->photons_cand_pT_hist_subleadingjet[ibin][ibin2]->Sumw2();
	photons_cand_pT_hist_subleadingjet[ibin][ibin2]->Add(more_hists->photons_cand_pT_hist_subleadingjet[ibin][ibin2], wt);
	photons_cand_phi_hist_subleadingjet[ibin][ibin2]->Sumw2();   more_hists->photons_cand_phi_hist_subleadingjet[ibin][ibin2]->Sumw2();
	photons_cand_phi_hist_subleadingjet[ibin][ibin2]->Add(more_hists->photons_cand_phi_hist_subleadingjet[ibin][ibin2], wt);
	photons_cand_eta_hist_subleadingjet[ibin][ibin2]->Sumw2();   more_hists->photons_cand_eta_hist_subleadingjet[ibin][ibin2]->Sumw2();
	photons_cand_eta_hist_subleadingjet[ibin][ibin2]->Add(more_hists->photons_cand_eta_hist_subleadingjet[ibin][ibin2], wt);
	
	chargedhadrons_cand_pT_hist_subleadingjet[ibin][ibin2]->Sumw2();   more_hists->chargedhadrons_cand_pT_hist_subleadingjet[ibin][ibin2]->Sumw2();
	chargedhadrons_cand_pT_hist_subleadingjet[ibin][ibin2]->Add(more_hists->chargedhadrons_cand_pT_hist_subleadingjet[ibin][ibin2], wt);
	chargedhadrons_cand_phi_hist_subleadingjet[ibin][ibin2]->Sumw2();   more_hists->chargedhadrons_cand_phi_hist_subleadingjet[ibin][ibin2]->Sumw2();
	chargedhadrons_cand_phi_hist_subleadingjet[ibin][ibin2]->Add(more_hists->chargedhadrons_cand_phi_hist_subleadingjet[ibin][ibin2], wt);
	chargedhadrons_cand_eta_hist_subleadingjet[ibin][ibin2]->Sumw2();   more_hists->chargedhadrons_cand_eta_hist_subleadingjet[ibin][ibin2]->Sumw2();
	chargedhadrons_cand_eta_hist_subleadingjet[ibin][ibin2]->Add(more_hists->chargedhadrons_cand_eta_hist_subleadingjet[ibin][ibin2], wt);
	
	
	chargedhadrons_cand_pT_hist_subleadingjet_bkg[ibin][ibin2]->Sumw2();   more_hists->chargedhadrons_cand_pT_hist_subleadingjet_bkg[ibin][ibin2]->Sumw2();
	chargedhadrons_cand_pT_hist_subleadingjet_bkg[ibin][ibin2]->Add(more_hists->chargedhadrons_cand_pT_hist_subleadingjet_bkg[ibin][ibin2], wt);
	
	neutral_cand_pT_hist_subleadingjet_bkg[ibin][ibin2]->Sumw2();   more_hists->neutral_cand_pT_hist_subleadingjet_bkg[ibin][ibin2]->Sumw2();
	neutral_cand_pT_hist_subleadingjet_bkg[ibin][ibin2]->Add(more_hists->neutral_cand_pT_hist_subleadingjet_bkg[ibin][ibin2], wt);
	
	photons_cand_pT_hist_subleadingjet_bkg[ibin][ibin2]->Sumw2();   more_hists->photons_cand_pT_hist_subleadingjet_bkg[ibin][ibin2]->Sumw2();
	photons_cand_pT_hist_subleadingjet_bkg[ibin][ibin2]->Add(more_hists->photons_cand_pT_hist_subleadingjet_bkg[ibin][ibin2], wt);
	
	NumNeutral_subleadingjet[ibin][ibin2]->Sumw2();   more_hists->NumNeutral_subleadingjet[ibin][ibin2]->Sumw2();
	NumNeutral_subleadingjet[ibin][ibin2]->Add(more_hists->NumNeutral_subleadingjet[ibin][ibin2], wt);
	NumPhotons_subleadingjet[ibin][ibin2]->Sumw2();   more_hists->NumPhotons_subleadingjet[ibin][ibin2]->Sumw2();
	NumPhotons_subleadingjet[ibin][ibin2]->Add(more_hists->NumPhotons_subleadingjet[ibin][ibin2], wt);
	NumAll_subleadingjet[ibin][ibin2]->Sumw2();   more_hists->NumAll_subleadingjet[ibin][ibin2]->Sumw2();
	NumAll_subleadingjet[ibin][ibin2]->Add(more_hists->NumAll_subleadingjet[ibin][ibin2], wt);
	NumChargedHadrons_subleadingjet[ibin][ibin2]->Sumw2();   more_hists->NumChargedHadrons_subleadingjet[ibin][ibin2]->Sumw2();
	NumChargedHadrons_subleadingjet[ibin][ibin2]->Add(more_hists->NumChargedHadrons_subleadingjet[ibin][ibin2], wt);
	
	NumNeutral_subleadingjet_bkg[ibin][ibin2]->Sumw2();   more_hists->NumNeutral_subleadingjet_bkg[ibin][ibin2]->Sumw2();
	NumNeutral_subleadingjet_bkg[ibin][ibin2]->Add(more_hists->NumNeutral_subleadingjet_bkg[ibin][ibin2], wt);
	NumPhotons_subleadingjet_bkg[ibin][ibin2]->Sumw2();   more_hists->NumPhotons_subleadingjet_bkg[ibin][ibin2]->Sumw2();
	NumPhotons_subleadingjet_bkg[ibin][ibin2]->Add(more_hists->NumPhotons_subleadingjet_bkg[ibin][ibin2], wt);
	NumAll_subleadingjet_bkg[ibin][ibin2]->Sumw2();   more_hists->NumAll_subleadingjet_bkg[ibin][ibin2]->Sumw2();
	NumAll_subleadingjet_bkg[ibin][ibin2]->Add(more_hists->NumAll_subleadingjet_bkg[ibin][ibin2], wt);
	NumChargedHadrons_subleadingjet_bkg[ibin][ibin2]->Sumw2();   more_hists->NumChargedHadrons_subleadingjet_bkg[ibin][ibin2]->Sumw2();
	NumChargedHadrons_subleadingjet_bkg[ibin][ibin2]->Add(more_hists->NumChargedHadrons_subleadingjet_bkg[ibin][ibin2], wt);
	
	
	
	
	SumJetPtFraction_hist_subleadingjet[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist_subleadingjet[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_subleadingjet[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_subleadingjet[ibin][ibin2], wt);
	
	SumJetPtFraction_hist_subleadingjet_photons[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist_subleadingjet_photons[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_subleadingjet_photons[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_subleadingjet_photons[ibin][ibin2], wt);
	
	SumJetPtFraction_hist_subleadingjet_chargedhadrons[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist_subleadingjet_chargedhadrons[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_subleadingjet_chargedhadrons[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_subleadingjet_chargedhadrons[ibin][ibin2], wt);
	
	SumJetPtFraction_hist_subleadingjet_neutrals[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist_subleadingjet_neutrals[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_subleadingjet_neutrals[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_subleadingjet_neutrals[ibin][ibin2], wt);
	
	
	
	/// bkg..
	SumJetPtFraction_hist_subleadingjet_photons_bkg[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist_subleadingjet_photons_bkg[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_subleadingjet_photons_bkg[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_subleadingjet_photons_bkg[ibin][ibin2], wt);
	
	SumJetPtFraction_hist_subleadingjet_chargedhadrons_bkg[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist_subleadingjet_chargedhadrons_bkg[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_subleadingjet_chargedhadrons_bkg[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_subleadingjet_chargedhadrons_bkg[ibin][ibin2], wt);
	
	SumJetPtFraction_hist_subleadingjet_neutrals_bkg[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist_subleadingjet_neutrals_bkg[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_subleadingjet_neutrals_bkg[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_subleadingjet_neutrals_bkg[ibin][ibin2], wt);
	
	SumJetPtFraction_hist_subleadingjet_chargedparticles_bkg[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist_subleadingjet_chargedparticles_bkg[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_subleadingjet_chargedparticles_bkg[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_subleadingjet_chargedparticles_bkg[ibin][ibin2], wt);
	
	
	SumJetPtFraction_hist_subleadingjet_electrons_bkg[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist_subleadingjet_electrons_bkg[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_subleadingjet_electrons_bkg[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_subleadingjet_electrons_bkg[ibin][ibin2], wt);
	
	SumJetPtFraction_hist_subleadingjet_muons_bkg[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist_subleadingjet_muons_bkg[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_subleadingjet_muons_bkg[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_subleadingjet_muons_bkg[ibin][ibin2], wt);
	
	
	SumJetPtFraction_hist_leadingjet_photons[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist_leadingjet_photons[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_photons[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_leadingjet_photons[ibin][ibin2], wt);
	SumJetPtFraction_hist_leadingjet_neutrals[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist_leadingjet_neutrals[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_neutrals[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_leadingjet_neutrals[ibin][ibin2], wt);
	
	SumJetPtFraction_hist_leadingjet_charged[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist_leadingjet_charged[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_charged[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_leadingjet_charged[ibin][ibin2], wt);
	
	///
	
	SumJetPtFraction_hist_leadingjet_chargedhadrons[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist_leadingjet_chargedhadrons[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_chargedhadrons[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_leadingjet_chargedhadrons[ibin][ibin2], wt);
	
	SumJetPtFraction_hist_leadingjet_chargedparticles[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist_leadingjet_chargedparticles[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_chargedparticles[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_leadingjet_chargedparticles[ibin][ibin2], wt);
	
	SumJetPtFraction_hist_leadingjet_electrons[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist_leadingjet_electrons[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_electrons[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_leadingjet_electrons[ibin][ibin2], wt);
	
	SumJetPtFraction_hist_leadingjet_muons[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist_leadingjet_muons[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_muons[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_leadingjet_muons[ibin][ibin2], wt);
	////
	
	/// starts -- bkg sumpt fraction plots
	SumJetPtFraction_hist_leadingjet_photons_bkg[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist_leadingjet_photons_bkg[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_photons_bkg[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_leadingjet_photons_bkg[ibin][ibin2], wt);
	
	SumJetPtFraction_hist_leadingjet_neutrals_bkg[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist_leadingjet_neutrals_bkg[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_neutrals_bkg[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_leadingjet_neutrals_bkg[ibin][ibin2], wt);
	
	SumJetPtFraction_hist_leadingjet_chargedhadrons_bkg[ibin][ibin2]->Sumw2();more_hists->SumJetPtFraction_hist_leadingjet_chargedhadrons_bkg[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_chargedhadrons_bkg[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_leadingjet_chargedhadrons_bkg[ibin][ibin2], wt);
	
	SumJetPtFraction_hist_leadingjet_chargedparticles_bkg[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist_leadingjet_chargedparticles_bkg[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_chargedparticles_bkg[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_leadingjet_chargedparticles_bkg[ibin][ibin2], wt);
	
	SumJetPtFraction_hist_leadingjet_electrons_bkg[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist_leadingjet_electrons_bkg[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_electrons_bkg[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_leadingjet_electrons_bkg[ibin][ibin2], wt);
	
	SumJetPtFraction_hist_leadingjet_muons_bkg[ibin][ibin2]->Sumw2();   more_hists->SumJetPtFraction_hist_leadingjet_muons_bkg[ibin][ibin2]->Sumw2();
	SumJetPtFraction_hist_leadingjet_muons_bkg[ibin][ibin2]->Add(more_hists->SumJetPtFraction_hist_leadingjet_muons_bkg[ibin][ibin2], wt);
	/// end -- bkg sumpt fraction plots
	
	
	
	
	radius_hist_subleadingjet[ibin][ibin2]->Sumw2();   more_hists->radius_hist_subleadingjet[ibin][ibin2]->Sumw2();
	radius_hist_subleadingjet[ibin][ibin2]->Add(more_hists->radius_hist_subleadingjet[ibin][ibin2], wt);
	Centrality_hist[ibin][ibin2]->Sumw2();   more_hists->Centrality_hist[ibin][ibin2]->Sumw2();
	Centrality_hist[ibin][ibin2]->Add(more_hists->Centrality_hist[ibin][ibin2], wt);
	
	
	Aj[ibin][ibin2]->Sumw2();   more_hists->Aj[ibin][ibin2]->Sumw2();
	Aj[ibin][ibin2]->Add(more_hists->Aj[ibin][ibin2], wt);
	
	
	dN_tracks[ibin][ibin2]->Sumw2();   more_hists->dN_tracks[ibin][ibin2]->Sumw2();
	dN_tracks[ibin][ibin2]->Add(more_hists->dN_tracks[ibin][ibin2], wt);
	dN_chargedhadrons[ibin][ibin2]->Sumw2();   more_hists->dN_chargedhadrons[ibin][ibin2]->Sumw2();
	dN_chargedhadrons[ibin][ibin2]->Add(more_hists->dN_chargedhadrons[ibin][ibin2], wt);
	dN_chargedparticles[ibin][ibin2]->Sumw2();   more_hists->dN_chargedparticles[ibin][ibin2]->Sumw2();
	dN_chargedparticles[ibin][ibin2]->Add(more_hists->dN_chargedparticles[ibin][ibin2], wt);
	dN_electrons[ibin][ibin2]->Sumw2();   more_hists->dN_electrons[ibin][ibin2]->Sumw2();
	dN_electrons[ibin][ibin2]->Add(more_hists->dN_electrons[ibin][ibin2], wt);
	dN_muons[ibin][ibin2]->Sumw2();   more_hists->dN_muons[ibin][ibin2]->Sumw2();
	dN_muons[ibin][ibin2]->Add(more_hists->dN_muons[ibin][ibin2], wt);
	dN_neutrals[ibin][ibin2]->Sumw2();   more_hists->dN_neutrals[ibin][ibin2]->Sumw2();
	dN_neutrals[ibin][ibin2]->Add(more_hists->dN_neutrals[ibin][ibin2], wt);
	dN_photons[ibin][ibin2]->Sumw2();   more_hists->dN_photons[ibin][ibin2]->Sumw2();
	dN_photons[ibin][ibin2]->Add(more_hists->dN_photons[ibin][ibin2], wt);
	
	JetPt_fraction_hist[ibin][ibin2]->Sumw2();   more_hists->JetPt_fraction_hist[ibin][ibin2]->Sumw2();
	JetPt_fraction_hist[ibin][ibin2]->Add(more_hists->JetPt_fraction_hist[ibin][ibin2], wt);
	
	dPhi_jet_track[ibin][ibin2]->Sumw2();   more_hists->dPhi_jet_track[ibin][ibin2]->Sumw2();
	dPhi_jet_track[ibin][ibin2]->Add(more_hists->dPhi_jet_track[ibin][ibin2], wt);
	
	dPhi_jet_track_ptweight[ibin][ibin2]->Sumw2();   more_hists->dPhi_jet_track_ptweight[ibin][ibin2]->Sumw2();
	dPhi_jet_track_ptweight[ibin][ibin2]->Add(more_hists->dPhi_jet_track_ptweight[ibin][ibin2], wt);
	
	
	track_cand_pT_hist_weighted[ibin][ibin2]->Sumw2();   more_hists->track_cand_pT_hist_weighted[ibin][ibin2]->Sumw2();
	track_cand_pT_hist_weighted[ibin][ibin2]->Add(more_hists->track_cand_pT_hist_weighted[ibin][ibin2], wt);
	
	SumPt_only[ibin][ibin2]->Sumw2();   more_hists->SumPt_only[ibin][ibin2]->Sumw2();
	SumPt_only[ibin][ibin2]->Add(more_hists->SumPt_only[ibin][ibin2], wt);
	
	JetEnergy_resolution[ibin][ibin2]->Sumw2();   more_hists->JetEnergy_resolution[ibin][ibin2]->Sumw2();
	JetEnergy_resolution[ibin][ibin2]->Add(more_hists->JetEnergy_resolution[ibin][ibin2], wt);
	
	JetEnergy_ratio[ibin][ibin2]->Sumw2();   more_hists->JetEnergy_ratio[ibin][ibin2]->Sumw2();
	JetEnergy_ratio[ibin][ibin2]->Add(more_hists->JetEnergy_ratio[ibin][ibin2], wt);
	
	
	JetEnergy_ratio_new[ibin][ibin2]->Sumw2();   more_hists->JetEnergy_ratio_new[ibin][ibin2]->Sumw2();
		JetEnergy_ratio_new[ibin][ibin2]->Add(more_hists->JetEnergy_ratio_new[ibin][ibin2], wt);
	

         track_gen_pT_hist[ibin][ibin2]->Sumw2();   more_hists->track_gen_pT_hist[ibin][ibin2]->Sumw2();
        track_gen_pT_hist[ibin][ibin2]->Add(more_hists->track_gen_pT_hist[ibin][ibin2], wt);
	
		
	}
	
	
	
	for (int ibin3=0;ibin3<nPtBins_sub;ibin3++){  /// pti3 subjet plots
	
	JetShapeDiffParticles_subleadingjet_bkg_1DEtaRef[ibin][ibin3]->Sumw2();   more_hists->JetShapeDiffParticles_subleadingjet_bkg_1DEtaRef[ibin][ibin3]->Sumw2();
	JetShapeDiffParticles_subleadingjet_bkg_1DEtaRef[ibin][ibin3]->Add(more_hists->JetShapeDiffParticles_subleadingjet_bkg_1DEtaRef[ibin][ibin3], wt);
	
	JetShapeIntegratedParticles_subleadingjet_1D[ibin][ibin3]->Sumw2();   more_hists->JetShapeIntegratedParticles_subleadingjet_1D[ibin][ibin3]->Sumw2();
	JetShapeIntegratedParticles_subleadingjet_1D[ibin][ibin3]->Add(more_hists->JetShapeIntegratedParticles_subleadingjet_1D[ibin][ibin3], wt);
	
	JetShapeDiffParticles_subleadingjet_bkg_1D[ibin][ibin3]->Sumw2();   more_hists->JetShapeDiffParticles_subleadingjet_bkg_1D[ibin][ibin3]->Sumw2();
	JetShapeDiffParticles_subleadingjet_bkg_1D[ibin][ibin3]->Add(more_hists->JetShapeDiffParticles_subleadingjet_bkg_1D[ibin][ibin3], wt);
	
	JetShapeDiffParticles_subleadingjet_1D[ibin][ibin3]->Sumw2();   more_hists->JetShapeDiffParticles_subleadingjet_1D[ibin][ibin3]->Sumw2();
	JetShapeDiffParticles_subleadingjet_1D[ibin][ibin3]->Add(more_hists->JetShapeDiffParticles_subleadingjet_1D[ibin][ibin3], wt);
	
	}
	
	
	
	}
	}
	
	
	void hist_class::Delete()
	{
	
	//  delete JetEnergy_gen_vs_rec;
	
	delete NEvents;
	delete NEvents_test;
	delete NEvents_after_noise;
	delete NEvents_after_spike;
	delete NEvents_after_dphi;
	delete NEvents_before_dphi;
	delete NEvents_dijets;
	delete NEvents_after_trigger;
	
	delete AllJetPt_raw_hist;
	delete AllJetPhi_hist;
	delete AllJetEta_hist;
	delete AllJetPt_hist;
	delete First_AllJetPhi_hist;
	delete First_AllJetEta_hist;
	delete First_AllJetPt_hist;
	delete Sub_AllJetPhi_hist;
	delete Sub_AllJetEta_hist;
	delete Sub_AllJetPt_hist;
	delete JetPt_fraction;
	delete Centrality;
	
	delete track_vz;
	delete track_vz_weighted;
	
	for (int ibin2=0;ibin2<nPtBins;ibin2++){
	delete fullrecjet_aftercuts[ibin2];
	delete fullrefjet_aftercuts[ibin2];
	}
	
	
	
	for (int ibin=0;ibin<nCBins;ibin++){
	
	delete jet_pT_hist[ibin];
	delete jet_phi_hist[ibin];
	delete jet_eta_hist[ibin];
	delete jet_corrpT_hist[ibin];
	delete LeadingJetPt_hist[ibin];
	delete LeadingJetPhi_hist[ibin];
	delete LeadingJetEta_hist[ibin];
	delete SubJetPt_hist[ibin];
	delete SubJetPhi_hist[ibin];
	delete SubJetEta_hist[ibin];
	
	delete dPhi_leadingjet_hist[ibin];
	delete dPhi_subleadingjet_hist[ibin];
	
	
	
	
	delete JetShapeDiffParticles_bkg_1D_total[ibin];
	delete JetShapeIntegratedParticles_bkg_1D_total[ibin];
	
	delete JetEnergy_gen_vs_rec[ibin];
	
	for (int ibin2=0;ibin2<nPtBins;ibin2++){
	
	
	// delete ThirdJetPt_hist[ibin][ibin2];
	delete ThirdJetPhi_hist[ibin][ibin2];
	delete ThirdJetEta_hist[ibin][ibin2];
	delete dPhi_hist[ibin][ibin2];
	delete dPhi_after_hist[ibin][ibin2];
	
	
	
	
	delete all_jets_corrpT[ibin][ibin2];
	delete all_jets_phi[ibin][ibin2];
	delete all_jets_eta[ibin][ibin2];
	
	delete only_leadingjets_corrpT[ibin][ibin2];
	delete only_leadingjets_phi[ibin][ibin2];
	delete only_leadingjets_eta[ibin][ibin2];
	delete neutral_cand_pT_hist[ibin][ibin2];
	delete neutral_cand_phi_hist[ibin][ibin2];
	delete neutral_cand_eta_hist[ibin][ibin2];
	delete photons_cand_pT_hist[ibin][ibin2];
	delete photons_cand_phi_hist[ibin][ibin2];
	delete photons_cand_eta_hist[ibin][ibin2];
	delete NumNeutral[ibin][ibin2];
	delete NumPhotons[ibin][ibin2];
	delete NumAll[ibin][ibin2];
	delete NumCharged[ibin][ibin2];
	
	delete NumAll_bkg[ibin][ibin2];
	delete NumNeutral_bkg[ibin][ibin2];
	delete NumPhotons_bkg[ibin][ibin2];
	delete NumChargedHadrons_bkg[ibin][ibin2];
	delete NumChargedParticles_bkg[ibin][ibin2];
	delete NumElectrons_bkg[ibin][ibin2];
	delete NumMuons_bkg[ibin][ibin2];
	
	delete radius_hist[ibin][ibin2];
	delete radius_hist_mine[ibin][ibin2];

	delete JetShapeIntegratedParticles[ibin][ibin2];
	delete JetShapeDiffParticles[ibin][ibin2];
	delete JetShapeIntegratedParticles_bkgsub[ibin][ibin2];
	delete JetShapeDiffParticles_bkgsub[ibin][ibin2];
	delete JetShapeIntegratedParticles_bkg[ibin][ibin2];
	delete JetShapeDiffParticles_bkg[ibin][ibin2];
	
	
	
	delete SumJetPtFraction_hist[ibin][ibin2];
	delete all_cand_pT_hist[ibin][ibin2];
	delete all_cand_phi_hist[ibin][ibin2];
	delete all_cand_eta_hist[ibin][ibin2];
	
	delete track_cand_pT_hist[ibin][ibin2];
	delete track_cand_phi_hist[ibin][ibin2];
	delete track_cand_eta_hist[ibin][ibin2];
	delete track_cand_pT_hist_subleadingjet[ibin][ibin2];
	
	delete only_subleadingjets_corrpT[ibin][ibin2];
	delete only_subleadingjets_phi[ibin][ibin2];
	delete only_subleadingjets_eta[ibin][ibin2];
	delete neutral_cand_pT_hist_subleadingjet[ibin][ibin2];
	delete neutral_cand_phi_hist_subleadingjet[ibin][ibin2];
	delete neutral_cand_eta_hist_subleadingjet[ibin][ibin2];
	delete photons_cand_pT_hist_subleadingjet[ibin][ibin2];
	delete photons_cand_phi_hist_subleadingjet[ibin][ibin2];
	delete photons_cand_eta_hist_subleadingjet[ibin][ibin2];
	delete NumNeutral_subleadingjet[ibin][ibin2];
	delete NumPhotons_subleadingjet[ibin][ibin2];
	delete NumAll_subleadingjet[ibin][ibin2];
	delete NumChargedHadrons_subleadingjet[ibin][ibin2];
	
	
	
	delete JetShapeDiffParticles_bkg_1D[ibin][ibin2];
	delete JetShapeDiffParticles_1D[ibin][ibin2];
	delete JetShapeIntegratedParticles_bkg_1D[ibin][ibin2];
	delete JetShapeIntegratedParticles_1D[ibin][ibin2];
	
	delete JetShapeDiffParticlesGen_bkg_1D[ibin][ibin2];
	delete JetShapeDiffParticlesGen_1D[ibin][ibin2];
	
	
	
	delete SumJetPtFraction_hist_subleadingjet[ibin][ibin2];
	delete SumJetPtFraction_hist_subleadingjet_photons[ibin][ibin2];
	delete SumJetPtFraction_hist_subleadingjet_neutrals[ibin][ibin2];
	delete SumJetPtFraction_hist_subleadingjet_chargedhadrons[ibin][ibin2];
	
	delete SumJetPtFraction_hist_leadingjet_photons[ibin][ibin2];
	delete SumJetPtFraction_hist_leadingjet_neutrals[ibin][ibin2];
	delete SumJetPtFraction_hist_leadingjet_charged[ibin][ibin2];
	
	
	delete all_cand_pT_hist_subleadingjet[ibin][ibin2];
	delete all_cand_phi_hist_subleadingjet[ibin][ibin2];
	delete all_cand_eta_hist_subleadingjet[ibin][ibin2];
	delete radius_hist_subleadingjet[ibin][ibin2];
	delete Centrality_hist[ibin][ibin2];
	delete Aj[ibin][ibin2];
	
	delete SumJetPtFraction_hist_leadingjet_chargedhadrons[ibin][ibin2];
	delete SumJetPtFraction_hist_leadingjet_chargedparticles[ibin][ibin2];
	delete SumJetPtFraction_hist_leadingjet_electrons[ibin][ibin2];
	delete SumJetPtFraction_hist_leadingjet_muons[ibin][ibin2];
	
	delete NumChargedHadrons[ibin][ibin2];
	delete NumChargedParticles[ibin][ibin2];
	delete NumElectrons[ibin][ibin2];
	delete NumMuons[ibin][ibin2];
	
	delete chargedhadrons_cand_pT_hist[ibin][ibin2];
	delete chargedhadrons_cand_phi_hist[ibin][ibin2];
	delete chargedhadrons_cand_eta_hist[ibin][ibin2];
	
	delete chargedparticles_cand_pT_hist[ibin][ibin2];
	delete chargedparticles_cand_phi_hist[ibin][ibin2];
	delete chargedparticles_cand_eta_hist[ibin][ibin2];
	
	delete electrons_cand_pT_hist[ibin][ibin2];
	delete electrons_cand_phi_hist[ibin][ibin2];
	delete electrons_cand_eta_hist[ibin][ibin2];
	
	delete muons_cand_pT_hist[ibin][ibin2];
	delete muons_cand_phi_hist[ibin][ibin2];
	delete muons_cand_eta_hist[ibin][ibin2];
	
	delete dN_tracks[ibin][ibin2];
	delete dN_chargedhadrons[ibin][ibin2];
	delete dN_chargedparticles[ibin][ibin2];
	delete dN_electrons[ibin][ibin2];
	delete dN_muons[ibin][ibin2];
	delete dN_neutrals[ibin][ibin2];
	delete dN_photons[ibin][ibin2];
	
	delete chargedhadrons_cand_pT_hist_bkg[ibin][ibin2];
	delete chargedparticles_cand_pT_hist_bkg[ibin][ibin2];
	delete electrons_cand_pT_hist_bkg[ibin][ibin2];
	delete muons_cand_pT_hist_bkg[ibin][ibin2];
	delete neutral_cand_pT_hist_bkg[ibin][ibin2];
	delete photons_cand_pT_hist_bkg[ibin][ibin2];
	
	delete SumJetPtFraction_hist_leadingjet_photons_bkg[ibin][ibin2];
	delete SumJetPtFraction_hist_leadingjet_neutrals_bkg[ibin][ibin2];
	delete SumJetPtFraction_hist_leadingjet_chargedhadrons_bkg[ibin][ibin2];
	delete SumJetPtFraction_hist_leadingjet_chargedparticles_bkg[ibin][ibin2];
	delete SumJetPtFraction_hist_leadingjet_electrons_bkg[ibin][ibin2];
	delete SumJetPtFraction_hist_leadingjet_muons_bkg[ibin][ibin2];
	
	
	/// subleading jet
	delete chargedhadrons_cand_pT_hist_subleadingjet[ibin][ibin2];
	delete chargedhadrons_cand_phi_hist_subleadingjet[ibin][ibin2];
	delete chargedhadrons_cand_eta_hist_subleadingjet[ibin][ibin2];
	
	delete chargedhadrons_cand_pT_hist_subleadingjet_bkg[ibin][ibin2];
	delete neutral_cand_pT_hist_subleadingjet_bkg[ibin][ibin2];
	delete photons_cand_pT_hist_subleadingjet_bkg[ibin][ibin2];
	
	
	delete SumJetPtFraction_hist_subleadingjet_photons_bkg[ibin][ibin2];
	delete SumJetPtFraction_hist_subleadingjet_neutrals_bkg[ibin][ibin2];
	delete SumJetPtFraction_hist_subleadingjet_chargedhadrons_bkg[ibin][ibin2];
	delete SumJetPtFraction_hist_subleadingjet_chargedparticles_bkg[ibin][ibin2];
	delete SumJetPtFraction_hist_subleadingjet_electrons_bkg[ibin][ibin2];
	delete SumJetPtFraction_hist_subleadingjet_muons_bkg[ibin][ibin2];
	
	
	delete NumAll_subleadingjet_bkg[ibin][ibin2];
	delete NumNeutral_subleadingjet_bkg[ibin][ibin2];
	delete NumPhotons_subleadingjet_bkg[ibin][ibin2];
	delete NumChargedHadrons_subleadingjet_bkg[ibin][ibin2];
	
	delete JetPt_fraction_hist[ibin][ibin2];
	delete dPhi_jet_track[ibin][ibin2];
	delete dPhi_jet_track_ptweight[ibin][ibin2];
	delete track_cand_pT_hist_weighted[ibin][ibin2];
	delete track_gen_pT_hist[ibin][ibin2];

	delete SumPt_only[ibin][ibin2];
	
	delete JetEnergy_resolution[ibin][ibin2];
	delete JetEnergy_ratio[ibin][ibin2];
	
	delete JetEnergy_ratio_new[ibin][ibin2];
	
	}
	
	for (int ibin3=0;ibin3<nPtBins_sub;ibin3++){  /// pti3 subjet plots
	delete JetShapeIntegratedParticles_subleadingjet_1D[ibin][ibin3];
	delete JetShapeDiffParticles_subleadingjet_bkg_1DEtaRef[ibin][ibin3];
	delete JetShapeDiffParticles_subleadingjet_bkg_1D[ibin][ibin3];
	delete JetShapeDiffParticles_subleadingjet_1D[ibin][ibin3];
	}
	
	
	}
	}
	
	void hist_class::Write()
	{
	
	
	
	TString pT_str = "";
	if( trkPtCut >= 0.5 && trkPtCut < 1.5 ) pT_str = "trkPtCut1";
	else if( trkPtCut >= 1.5 && trkPtCut < 2.5 ) pT_str = "trkPtCut2";
	else if( trkPtCut >= 2.5 && trkPtCut < 3.5 ) pT_str = "trkPtCut3";
	else if( trkPtCut >= 3.5 && trkPtCut < 4.5 ) pT_str = "trkPtCut4";
	else assert(0);  
	TString out_name = (TString) ("root_output/" + dataset_type_strs[dataset_type_code] + "_" + pT_str + ".root");
	if( test_it ) out_name = (TString) ("root_output/" + dataset_type_strs[dataset_type_code] + "_" + pT_str + "_test.root");
	TFile *out_file = new TFile(out_name, "RECREATE");
	
	
	//     JetEnergy_gen_vs_rec->Write();
	
	
	NEvents->Write();
	NEvents_test->Write();
	NEvents_after_noise->Write();
	NEvents_after_spike->Write();
	NEvents_after_trigger->Write();
	NEvents_after_dphi->Write();
	NEvents_before_dphi->Write();
	NEvents_dijets->Write();
	
	AllJetPt_raw_hist->Write();
	AllJetPhi_hist->Write();
	AllJetEta_hist->Write();
	AllJetPt_hist->Write();
	
	First_AllJetPhi_hist->Write();
	First_AllJetEta_hist->Write();
	First_AllJetPt_hist->Write();
	
	Sub_AllJetPhi_hist->Write();
	Sub_AllJetEta_hist->Write();
	Sub_AllJetPt_hist->Write();
	JetPt_fraction->Write();
	Centrality->Write();
	
	track_vz->Write();
	track_vz_weighted->Write();
	
	for (int ibin2=0;ibin2<nPtBins;ibin2++){
	fullrecjet_aftercuts[ibin2]->Write();
		fullrefjet_aftercuts[ibin2]->Write();
	}
	
	
	for (int ibin=0;ibin<nCBins;ibin++){
	
	jet_pT_hist[ibin]->Write();
	jet_phi_hist[ibin]->Write();
	jet_eta_hist[ibin]->Write();
	jet_corrpT_hist[ibin]->Write();
	LeadingJetPt_hist[ibin]->Write();
	LeadingJetPhi_hist[ibin]->Write();
	LeadingJetEta_hist[ibin]->Write();
	SubJetPt_hist[ibin]->Write();
	SubJetPhi_hist[ibin]->Write();
	SubJetEta_hist[ibin]->Write();
	dPhi_leadingjet_hist[ibin]->Write();
	dPhi_subleadingjet_hist[ibin]->Write();
	
	JetShapeDiffParticles_bkg_1D_total[ibin]->Write();
	JetShapeIntegratedParticles_bkg_1D_total[ibin]->Write();
	JetEnergy_gen_vs_rec[ibin]->Write();
	
	for (int ibin2=0;ibin2<nPtBins;ibin2++){
	
	
	
	//  ThirdJetPt_hist[ibin][ibin2]->Write();
	ThirdJetPhi_hist[ibin][ibin2]->Write();
	ThirdJetEta_hist[ibin][ibin2]->Write();
	
	radius_hist[ibin][ibin2]->Write();
	radius_hist_mine[ibin][ibin2]->Write();

	dPhi_hist[ibin][ibin2]->Write();
	dPhi_after_hist[ibin][ibin2]->Write();
	
	
	all_jets_corrpT[ibin][ibin2]->Write();
	all_jets_phi[ibin][ibin2]->Write();
	all_jets_eta[ibin][ibin2]->Write();
	only_leadingjets_corrpT[ibin][ibin2]->Write();
	only_leadingjets_phi[ibin][ibin2]->Write();
	only_leadingjets_eta[ibin][ibin2]->Write();
	only_subleadingjets_corrpT[ibin][ibin2]->Write();
	only_subleadingjets_phi[ibin][ibin2]->Write();
	only_subleadingjets_eta[ibin][ibin2]->Write();
	
	
	neutral_cand_pT_hist[ibin][ibin2]->Write();
	neutral_cand_phi_hist[ibin][ibin2]->Write();
	neutral_cand_eta_hist[ibin][ibin2]->Write();
	photons_cand_pT_hist[ibin][ibin2]->Write();
	photons_cand_phi_hist[ibin][ibin2]->Write();
	photons_cand_eta_hist[ibin][ibin2]->Write();
	NumNeutral[ibin][ibin2]->Write();
	NumPhotons[ibin][ibin2]->Write();
	NumAll[ibin][ibin2]->Write();
	NumCharged[ibin][ibin2]->Write();
	
	NumAll_bkg[ibin][ibin2]->Write();
	NumNeutral_bkg[ibin][ibin2]->Write();
	NumPhotons_bkg[ibin][ibin2]->Write();
	NumChargedHadrons_bkg[ibin][ibin2]->Write();
	NumChargedParticles_bkg[ibin][ibin2]->Write();
	NumElectrons_bkg[ibin][ibin2]->Write();
	NumMuons_bkg[ibin][ibin2]->Write();
	
	JetShapeIntegratedParticles[ibin][ibin2]->Write();
	JetShapeDiffParticles[ibin][ibin2]->Write();
	JetShapeIntegratedParticles_bkgsub[ibin][ibin2]->Write();
	JetShapeDiffParticles_bkgsub[ibin][ibin2]->Write();
	JetShapeIntegratedParticles_bkg[ibin][ibin2]->Write();
	JetShapeDiffParticles_bkg[ibin][ibin2]->Write();
	
	
	JetShapeDiffParticles_bkg_1D[ibin][ibin2]->Write();
	JetShapeDiffParticles_1D[ibin][ibin2]->Write();
	JetShapeIntegratedParticles_bkg_1D[ibin][ibin2]->Write();
	JetShapeIntegratedParticles_1D[ibin][ibin2]->Write();
	
	JetShapeDiffParticlesGen_bkg_1D[ibin][ibin2]->Write();
	JetShapeDiffParticlesGen_1D[ibin][ibin2]->Write();
	
	SumJetPtFraction_hist[ibin][ibin2]->Write();
	all_cand_pT_hist[ibin][ibin2]->Write();
	all_cand_phi_hist[ibin][ibin2]->Write();
	all_cand_eta_hist[ibin][ibin2]->Write();
	
	track_cand_pT_hist[ibin][ibin2]->Write();
	track_cand_phi_hist[ibin][ibin2]->Write();
	track_cand_eta_hist[ibin][ibin2]->Write();
	track_cand_pT_hist_subleadingjet[ibin][ibin2]->Write();
	
	neutral_cand_pT_hist_subleadingjet[ibin][ibin2]->Write();
	neutral_cand_phi_hist_subleadingjet[ibin][ibin2]->Write();
	neutral_cand_eta_hist_subleadingjet[ibin][ibin2]->Write();
	photons_cand_pT_hist_subleadingjet[ibin][ibin2]->Write();
	photons_cand_phi_hist_subleadingjet[ibin][ibin2]->Write();
	photons_cand_eta_hist_subleadingjet[ibin][ibin2]->Write();
	NumNeutral_subleadingjet[ibin][ibin2]->Write();
	NumPhotons_subleadingjet[ibin][ibin2]->Write();
	NumAll_subleadingjet[ibin][ibin2]->Write();
	NumChargedHadrons_subleadingjet[ibin][ibin2]->Write();
	
	
	
	SumJetPtFraction_hist_subleadingjet[ibin][ibin2]->Write();
	SumJetPtFraction_hist_subleadingjet_photons[ibin][ibin2]->Write();
	SumJetPtFraction_hist_subleadingjet_neutrals[ibin][ibin2]->Write();
	SumJetPtFraction_hist_subleadingjet_chargedhadrons[ibin][ibin2]->Write();
	
	SumJetPtFraction_hist_leadingjet_photons[ibin][ibin2]->Write();
	SumJetPtFraction_hist_leadingjet_neutrals[ibin][ibin2]->Write();
	SumJetPtFraction_hist_leadingjet_charged[ibin][ibin2]->Write();
	
	SumJetPtFraction_hist_leadingjet_chargedhadrons[ibin][ibin2]->Write();
	SumJetPtFraction_hist_leadingjet_chargedparticles[ibin][ibin2]->Write();
	SumJetPtFraction_hist_leadingjet_electrons[ibin][ibin2]->Write();
	SumJetPtFraction_hist_leadingjet_muons[ibin][ibin2]->Write();
	
	NumChargedHadrons[ibin][ibin2]->Write();
	NumChargedParticles[ibin][ibin2]->Write();
	NumElectrons[ibin][ibin2]->Write();
	NumMuons[ibin][ibin2]->Write();
	
	chargedhadrons_cand_pT_hist[ibin][ibin2]->Write();
	chargedhadrons_cand_phi_hist[ibin][ibin2]->Write();
	chargedhadrons_cand_eta_hist[ibin][ibin2]->Write();
	
	chargedparticles_cand_pT_hist[ibin][ibin2]->Write();
	chargedparticles_cand_phi_hist[ibin][ibin2]->Write();
	chargedparticles_cand_eta_hist[ibin][ibin2]->Write();
	
	electrons_cand_pT_hist[ibin][ibin2]->Write();
	electrons_cand_phi_hist[ibin][ibin2]->Write();
	electrons_cand_eta_hist[ibin][ibin2]->Write();
	
	muons_cand_pT_hist[ibin][ibin2]->Write();
	muons_cand_phi_hist[ibin][ibin2]->Write();
	muons_cand_eta_hist[ibin][ibin2]->Write();
	
	
	all_cand_pT_hist_subleadingjet[ibin][ibin2]->Write();
	all_cand_phi_hist_subleadingjet[ibin][ibin2]->Write();
	all_cand_eta_hist_subleadingjet[ibin][ibin2]->Write();
	radius_hist_subleadingjet[ibin][ibin2]->Write();
	Centrality_hist[ibin][ibin2]->Write();
	Aj[ibin][ibin2]->Write();
	
	
	dN_tracks[ibin][ibin2]->Write();
	dN_chargedhadrons[ibin][ibin2]->Write();
	dN_chargedparticles[ibin][ibin2]->Write();
	dN_electrons[ibin][ibin2]->Write();
	dN_muons[ibin][ibin2]->Write();
	dN_neutrals[ibin][ibin2]->Write();
	dN_photons[ibin][ibin2]->Write();
	
	chargedhadrons_cand_pT_hist_bkg[ibin][ibin2]->Write();
	chargedparticles_cand_pT_hist_bkg[ibin][ibin2]->Write();
	electrons_cand_pT_hist_bkg[ibin][ibin2]->Write();
	muons_cand_pT_hist_bkg[ibin][ibin2]->Write();
	neutral_cand_pT_hist_bkg[ibin][ibin2]->Write();
	photons_cand_pT_hist_bkg[ibin][ibin2]->Write();
	
	SumJetPtFraction_hist_leadingjet_photons_bkg[ibin][ibin2]->Write();
	SumJetPtFraction_hist_leadingjet_neutrals_bkg[ibin][ibin2]->Write();
	SumJetPtFraction_hist_leadingjet_chargedhadrons_bkg[ibin][ibin2]->Write();
	SumJetPtFraction_hist_leadingjet_chargedparticles_bkg[ibin][ibin2]->Write();
	SumJetPtFraction_hist_leadingjet_electrons_bkg[ibin][ibin2]->Write();
	SumJetPtFraction_hist_leadingjet_muons_bkg[ibin][ibin2]->Write();
	
	
	/// subleading jet plots
	chargedhadrons_cand_pT_hist_subleadingjet[ibin][ibin2]->Write();
	chargedhadrons_cand_phi_hist_subleadingjet[ibin][ibin2]->Write();
	chargedhadrons_cand_eta_hist_subleadingjet[ibin][ibin2]->Write();
	
	chargedhadrons_cand_pT_hist_subleadingjet_bkg[ibin][ibin2]->Write();
	neutral_cand_pT_hist_subleadingjet_bkg[ibin][ibin2]->Write();
	photons_cand_pT_hist_subleadingjet_bkg[ibin][ibin2]->Write();
	
	
	SumJetPtFraction_hist_subleadingjet_photons_bkg[ibin][ibin2]->Write();
	SumJetPtFraction_hist_subleadingjet_neutrals_bkg[ibin][ibin2]->Write();
	SumJetPtFraction_hist_subleadingjet_chargedhadrons_bkg[ibin][ibin2]->Write();
	SumJetPtFraction_hist_subleadingjet_chargedparticles_bkg[ibin][ibin2]->Write();
	SumJetPtFraction_hist_subleadingjet_electrons_bkg[ibin][ibin2]->Write();
	SumJetPtFraction_hist_subleadingjet_muons_bkg[ibin][ibin2]->Write();
	
	
	NumAll_subleadingjet_bkg[ibin][ibin2]->Write();
	NumNeutral_subleadingjet_bkg[ibin][ibin2]->Write();
	NumPhotons_subleadingjet_bkg[ibin][ibin2]->Write();
	NumChargedHadrons_subleadingjet_bkg[ibin][ibin2]->Write();
	
	JetPt_fraction_hist[ibin][ibin2]->Write();
	dPhi_jet_track[ibin][ibin2]->Write();
	dPhi_jet_track_ptweight[ibin][ibin2]->Write();
	track_cand_pT_hist_weighted[ibin][ibin2]->Write();
        track_gen_pT_hist[ibin][ibin2]->Write();
  	
	SumPt_only[ibin][ibin2]->Write();
	
	JetEnergy_resolution[ibin][ibin2]->Write();
	JetEnergy_ratio[ibin][ibin2]->Write();
	JetEnergy_ratio_new[ibin][ibin2]->Write();
	
	
	} /// ptbin
	
	
	for (int ibin3=0;ibin3<nPtBins_sub;ibin3++){  /// pti3 subjet plots
	JetShapeIntegratedParticles_subleadingjet_1D[ibin][ibin3]->Write();
	JetShapeDiffParticles_subleadingjet_bkg_1DEtaRef[ibin][ibin3]->Write();
	JetShapeDiffParticles_subleadingjet_bkg_1D[ibin][ibin3]->Write();
	JetShapeDiffParticles_subleadingjet_1D[ibin][ibin3]->Write();
	}
	
	}  //centralitybin
	out_file->Close();
	}
	
	
	
	double deltaR(double eta1, double phi1, double eta2, double phi2);
	double deltaR(double eta1, double phi1, double eta2, double phi2){
			double deltaEta = fabs(eta1-eta2);
			double deltaPhi = fabs(phi1-phi2);
			if (deltaPhi>TMath::TwoPi())   std::cout << "deltaR calculation. Why is deltaPhi larger than 2pi?" << std::endl;
			else if (deltaPhi>TMath::Pi()) deltaPhi = TMath::TwoPi()-deltaPhi;
			return pow(deltaEta*deltaEta+deltaPhi*deltaPhi,0.5);
	}
	
	
	void StudyFiles(std::vector<TString> file_names, int foi, hist_class *my_hists);
	//void GetFilesOfFileNames(std::vector<TString> &files_of_file_names, std::vector<float> &Xsections); ////getting the data/simulation based on whatever dataset you pick (arg)
	
	void GetFilesOfFileNames(std::vector<TString> &files_of_file_names, std::vector<float> &Xsections, std::vector<double> &assumed_n_evt); ////getting the data/simulation based on whatever dataset you pick (arg);
	
	void ReadFileList(std::vector<TString> &my_file_names, TString file_of_names, bool debug=false);
	float GetDatasetWeight(double n_evt_raw, double Xsection);//
	//void GetBkgShape(TVector3 highest_jet_vec, TVector3 second_highest_jet_vec, std::vector<TVector3>& bkg_particles);  
	//double GetBkgShape(TVector3 highest_jet_vec, TVector3 second_highest_jet_vec, std::vector<TVector3>& bkg_particles);  
	void GetBkgShape(TVector3 highest_jet_vec, TVector3 second_highest_jet_vec, TVector3& bkg_dir, TVector3& bkg_dir2);
	
	int main(int argc, char *argv[])
	{
	
	
	if(doTrackCorrections){
	
	trackCorrFromParam = new TrackingParam();
	
	//trackCorrections.push_back(new TrackingCorrections("Forest2STAv12","Forest2_MergedGeneral"));
	// trackCorrections.push_back(new TrackingCorrections("Forest2STAv12","Forest2_MergedGeneral_j1"));
	// trackCorrections.push_back(new TrackingCorrections("Forest2STAv12","Forest2_MergedGeneral_j2"));
	
		trackCorrections.push_back(new TrackingCorrections("Forest2STAv14","Forest2_MergedGeneral_jetfine"));
	
	
	for(int i = 0; i < trackCorrections.size(); ++i){
	
	
	//trackCorrections[i]->AddSample("../trkcorr/TrkCorrtest_hy18dj50_akPu3PF_100_-1_-1000_genJetMode0.root",50);
	trackCorrections[i]->AddSample("../trkcorr/TrkCorrtest_hy18dj80_akPu3PF_100_-1_-1000_genJetMode0.root",80);
	trackCorrections[i]->AddSample("../trkcorr/TrkCorrtest_hy18dj100_akPu3PF_100_-1_-1000_genJetMode0.root",100);
	trackCorrections[i]->AddSample("../trkcorr/TrkCorrtest_hy18dj120_akPu3PF_100_-1_-1000_genJetMode0.root",120);
	trackCorrections[i]->AddSample("../trkcorr/TrkCorrtest_hy18dj170_akPu3PF_100_-1_-1000_genJetMode0.root",170);
	trackCorrections[i]->AddSample("../trkcorr/TrkCorrtest_hy18dj200_akPu3PF_100_-1_-1000_genJetMode0.root",200);
	trackCorrections[i]->AddSample("../trkcorr/TrkCorrtest_hy18dj250_akPu3PF_100_-1_-1000_genJetMode0.root",250);
	trackCorrections[i]->AddSample("../trkcorr/TrkCorrtest_hy18dj300_akPu3PF_100_-1_-1000_genJetMode0.root",300);
	
	
	
		trackCorrections[i]->weightSamples_ = true;
		trackCorrections[i]->smoothLevel_ = 0;
		trackCorrections[i]->trkPhiMode_ = false;
		trackCorrections[i]->Init();
	}
	
	}
	
	
	
	assert(argc == 3);
	dataset_type_code = atoi(argv[1]);    //// pick datasets you want to run over
	
	trkPtCut = atof(argv[2]);
	assert(trkPtCut > 0. && trkPtCut < 5.);
	std::cout << "Running with trkPtCut " << trkPtCut << std::endl;
	
	if(dataset_type_code == e_Data2011 ) is_data = true;
	
	else if( dataset_type_code == e_HydJet30 || dataset_type_code == e_HydJet50 || dataset_type_code == e_HydJet80|| dataset_type_code == e_HydJet100|| dataset_type_code == e_HydJet120|| dataset_type_code == e_HydJet170|| dataset_type_code == e_HydJet200 || dataset_type_code == e_HydJet250 || dataset_type_code == e_HydJet300) is_data =false;
	else assert(0);
	
	std::vector<TString> files_of_file_names;   files_of_file_names.clear();
	std::vector<float> Xsections;   Xsections.clear();
	std::vector<double> assumed_n_evt;   assumed_n_evt.clear();
	
	////// Get list of files for each dataset ... where do I look for the dataset
	std::cout << "GetFilesOf" << std::endl;
	//  GetFilesOfFileNames(files_of_file_names, Xsections);
	GetFilesOfFileNames(files_of_file_names, Xsections, assumed_n_evt);
	
	//// Total histograms, will add to this for each dataset
	hist_class *hists = new hist_class((TString) ("hists"), is_data);
	//// Loop over each dataset (dataset = collection of similar files of event types)
	for(int foi = 0; foi < (int) files_of_file_names.size(); foi++) {
	TString dataset_str = "sim_dataset_";   dataset_str += foi;
	hist_class *these_hists = new hist_class((TString) ("hists_" + dataset_str), is_data);
	std::cout << "Got hist class for foi " << foi << std::endl;
	std::vector<TString> file_names;   file_names.clear();
	
	////// Collect the file names for this dataset
	ReadFileList( file_names, files_of_file_names.at(foi), true);
	
	////// Pass these files to StudyFiles function to fill histograms
	StudyFiles(file_names, foi, these_hists);
	
	
	float dataset_scale_val = 1.;
	if( !is_data ) {    ////// determine the proper weighting for this dataset (how much you've simulated and likelihood of event)
	assert(foi < (int) Xsections.size() );
	////////////////////      dataset_scale_val = GetDatasetWeight(these_hists->n_evt_raw, Xsections.at(foi));
	
	//dataset_scale_val = GetDatasetWeight(assumed_n_evt.at(foi), Xsections.at(foi));
	
	
	//std::cout << "foi: " << foi << ", xsec: " << Xsections.at(foi) << ", n_evt_raw: " << these_hists->n_evt_raw << ", scale: " << dataset_scale_val << "\n";
	}
	/////// Add the histograms for this dataset to the full histogram class that you care about
	std::cout << "Addhists" << std::endl;
	hists->AddHists(these_hists, dataset_scale_val);
	std::cout << "Delete" << std::endl;
	these_hists->Delete();
	std::cout << "Delete" << std::endl;
	delete these_hists;
	}
	hists->NormalizeByCounts();
	hists->Write();
	}
	
	
	
	void StudyFiles(std::vector<TString> file_names, int foi, hist_class *my_hists)
	{
	
	
	double weight=1.;
	
	
	
	//////////###### PTHAT SAMPLES ###########///////////////
	
	
		int pthat =30;
		int pthatmax =50;
	
		if( dataset_type_code == e_HydJet50 ) {
		pthat = 50;
		pthatmax=80;
	
		}
		if( dataset_type_code == e_HydJet80 ) {
		pthat = 80;
		pthatmax=100;
	
		}
		if( dataset_type_code == e_HydJet100 ) {
		pthat = 100;
		pthatmax=120;
	
		}
		if( dataset_type_code == e_HydJet120 ) {
		pthat = 120;
		pthatmax=170;
	
		}
		if( dataset_type_code == e_HydJet170 ) {
		pthat = 170;
		pthatmax=200;
	
		}
		if( dataset_type_code == e_HydJet200 ) {
		pthat = 200;
		pthatmax=250;
				
		}
		if( dataset_type_code == e_HydJet250 ) {
		pthat = 250;
		pthatmax=300;
	
		}
		if( dataset_type_code == e_HydJet300 ) {
		pthat = 300;
		pthatmax=400;
		}
	
	std::cout << "I am working\n";
	
	
	TTree *inp_tree;
	TTree *inp_tree2;
	TTree *inp_tree3;
	TTree *inp_tree4;
	TTree *inp_tree5;
	TTree *inp_tree6;
	
	
	for(int fi = 0; fi < (int) file_names.size(); fi++) {
	TFile *my_file = TFile::Open(file_names.at(fi));
	std::cout << "file it" << ", file_name: " << file_names.at(fi) << ", number " << fi << " of " << file_names.size() << std::endl;
	if(my_file->IsZombie()) {
	std::cout << "Is zombie" << std::endl;
	}
	
	inp_tree = (TTree*)  my_file->Get("akPu3PFJetAnalyzer/t");
	inp_tree3 = (TTree*) my_file->Get("hiEvtAnalyzer/HiTree");
	inp_tree4 = (TTree*) my_file->Get("skimanalysis/HltTree");
	inp_tree5 = (TTree*) my_file->Get("anaTrack/trackTree");
	inp_tree6 = (TTree*) my_file->Get("hltanalysis/HltTree");
	
	std::cout << "Got tree" << std::endl;
	
	JetAna *my_ct = new JetAna(inp_tree);
	HiTree *my_ct3 = new HiTree(inp_tree3);
	Skim *my_ct4   = new Skim(inp_tree4);
	Tracks *my_ct5 = new Tracks(inp_tree5);
	HLT *my_ct6 = new HLT(inp_tree6);
	
	
	std::cout << "Got CT" << std::endl;
	int n_evt = my_ct->fChain->GetEntriesFast();
	
	
	TF1 *fcen = new TF1("fcen","[0]*exp([1]+[2]*x+[3]*x*x+[4]*x*x*x)",0,40);
	TF1 * fVz = new TF1("fVx","[0]+[1]*x+[2]*TMath::Power(x,2)+[3]*TMath::Power(x,3)+[4]*TMath::Power(x,4)", -15., 15.);
	
	
	///==========================   Event Loop starts ===================================
	///==========================   Event Loop starts ===================================
	
	for(int evi = 0; evi < n_evt; evi++) {
//        for(int evi = 0; evi < 100; evi++) {
	  
	  	
	if (evi%100==0) std::cout << " I am running on file " << fi << " of " << ((int) file_names.size()) << ", evi: " << evi << " of " << n_evt << std::endl;
	my_ct->fChain->GetEntry(evi);
	my_hists->NEvents->Fill(my_ct->fChain->GetEntry(evi));
	
	//  my_ct2->fChain->GetEntry(evi);
	my_ct3->fChain->GetEntry(evi);
	my_ct4->fChain->GetEntry(evi);
	my_ct5->fChain->GetEntry(evi);
	my_ct6->fChain->GetEntry(evi);
	//----------------------------------------------------------------------------


	//! Centrality reweighting function
	fcen->SetParameters(1.98261e-02,5.55963e+00,-1.34951e-01,1.70895e-03,-9.28386e-05);
	//! vertex z reqeighting
	fVz->SetParameters(7.62788e-01,-1.13228e-02,5.85199e-03,-3.04550e-04,4.43440e-05);
	
        int hiBin = my_ct3->hiBin;
        float vz  = my_ct3->vz;

	if(fabs(vz) > 15.)continue;
	double wvz=1;
	double wcen=1;

	my_hists->track_vz->Fill(vz);
		
	
	if(is_data) { 
	  int noise_event_selection = my_ct4->pHBHENoiseFilter; 
	  if(noise_event_selection==0) continue;
	  my_hists->NEvents_after_noise->Fill(1.0);
	
	  int event_selection = my_ct4->pcollisionEventSelection;
	  if(event_selection==0) continue;
	  my_hists->NEvents_test->Fill(1.0);
	
	  if (my_ct6->HLT_HIJet80_v1==0) continue;
	
	  wvz=1;
	  wcen=1;
	
	}else{
	
	wvz=fVz->Eval(vz);
	wcen = fcen->Eval(hiBin);
	my_hists->track_vz_weighted->Fill(vz, wvz*wcen);

	}

	TVector3 jet_vec;
	TVector3 track_vec;
	jet_vec.SetPtEtaPhi(0, 0, 0);
	track_vec.SetPtEtaPhi(0, 0, 0);



	//// loop over ak3PUPFjets for inclusive jets
	for(int j4i = 0; j4i < my_ct->nref ; j4i++) {
	
	if( fabs(my_ct->jteta[j4i]) > 2 ) continue;
	if(my_ct->trackMax[j4i]/my_ct->jtpt[j4i] <=0.01) continue ;            
	if( my_ct->jtpt[j4i] <100 ) continue;
	if( my_ct->jtpt[j4i] >300 ) continue;
	
	if( !is_data ) {
		double pthat_new = my_ct->pthat;
		if (pthat_new > pthatmax) continue;
        }
			
		int ibin = 0;      int ibin2 = 0;  int ibin3=0;
		for (int centi=0;centi<nCBins;centi++){
		if (my_ct3->hiBin >=CBins[centi] && my_ct3->hiBin <CBins[centi+1])  ibin = centi;
		}
	
		for(int pti = 0; pti < nPtBins; pti++) {
		if (my_ct->jtpt[j4i] >=PtBins[pti] && my_ct->jtpt[j4i] < PtBins[pti+1])  ibin2 = pti ;
		}
	
			my_hists->LeadingJetPt_hist[ibin2]->Fill(my_ct->jtpt[j4i], wvz*wcen);
			my_hists->LeadingJetPhi_hist[ibin2]->Fill(my_ct->jtphi[j4i], wvz*wcen);
			my_hists->LeadingJetEta_hist[ibin2]->Fill(my_ct->jteta[j4i], wvz*wcen);
			my_hists->Centrality_hist[ibin][ibin2]->Fill(my_ct3->hiBin, wvz*wcen);
	
		if ( fabs(my_ct->jteta[j4i]) < 0.3 ) continue;  /// eta cut
	
			my_hists->all_jets_corrpT[ibin][ibin2]->Fill(my_ct->jtpt[j4i], wvz*wcen);
			my_hists->all_jets_phi[ibin][ibin2]->Fill(my_ct->jtphi[j4i], wvz*wcen);
			my_hists->all_jets_eta[ibin][ibin2]->Fill(my_ct->jteta[j4i], wvz*wcen);
	
	
		///=================================================================================================
		///------------------------------------- GenChgParticle Starts--------------------------------------
		///=================================================================================================
	
			/// GenParticles:  Denominator for signal

			int gen_multiplicity =0;
			const int NRBIN_gen=6;
			std::vector<double> SumPtRBinGen(NRBIN_gen);
			for(int vi = 0; vi < (int) SumPtRBinGen.size(); vi++) {
			SumPtRBinGen.at(vi) = 0.;
			}
			const float RBIN_gen[NRBIN_gen+1]={0.0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3};
			std::vector<double> SumPtRBinEtaRefGen(NRBIN_gen);
			for(int vi = 0; vi < (int) SumPtRBinEtaRefGen.size(); vi++) {
			SumPtRBinEtaRefGen.at(vi) = 0.;
			}



	if( !is_data ) {
			float SumPtGenJet = 0; 
			for(int ipart = 0 ; ipart < my_ct5->nParticle ; ipart++){ //sim track loop 
				double gen_pt = my_ct5->pPt[ipart];
				double gen_phi = my_ct5->pPhi[ipart];
				double gen_eta = my_ct5->pEta[ipart];  
				if(gen_pt<trkPtCut)continue ;
				if(TMath::Abs(gen_eta)>2.4)continue ;
				double gendr = deltaR(my_ct->jteta[j4i],my_ct->jtphi[j4i], gen_eta,gen_phi);

            double dr =TMath::Sqrt((gen_phi-my_ct->jtphi[j4i])*(gen_phi-my_ct->jtphi[j4i])+(gen_eta-my_ct->jteta[j4i])*(gen_eta-my_ct->jteta[j4i]));

//	                       std::cout << " gendr : " << gendr << "   " << dr << std::endl;



				if(my_ct5->pNRec[ipart]>0&&(my_ct5->mtrkAlgo[ipart]<4||(my_ct5->mtrkQual[ipart]))){
				if(gendr<=0.3){
				my_hists->track_gen_pT_hist[ibin][ibin2]->Fill(gen_pt, wvz*wcen);
				SumPtGenJet += gen_pt;
				} 
				} 
			}  
	
	
			/// GenParticles:  Numerator for signal
	

			for(int ipart = 0 ; ipart < my_ct5->nParticle ; ipart++){ //sim track loop 
				double gen_pt = my_ct5->pPt[ipart];
				double gen_phi = my_ct5->pPhi[ipart];
				double gen_eta = my_ct5->pEta[ipart];  
				if(gen_pt<trkPtCut)continue ;
				if(TMath::Abs(gen_eta)>2.4)continue ;
				double rr = deltaR(my_ct->jteta[j4i],my_ct->jtphi[j4i], gen_eta,gen_phi);
				if(my_ct5->pNRec[ipart]>0&&(my_ct5->mtrkAlgo[ipart]<4||(my_ct5->mtrkQual[ipart]))){
				if(rr<=0.3){
				gen_multiplicity++;
				for(int ir=0;ir<NRBIN_gen;ir++){
				if(RBIN_gen[ir]<rr && rr <= RBIN_gen[ir+1]){
				SumPtRBinGen[ir]+=gen_pt;
				continue;						 
				}
				}
				} 
				} 
			}  
	
			/// GenParticles: Numerator for eta reflection 
	

			if( fabs(my_ct->jteta[j4i]) > 0.3 ){
			for(int ipart = 0 ; ipart < my_ct5->nParticle ; ipart++){ //sim track loop 
				double gen_pt = my_ct5->pPt[ipart];
				double gen_phi = my_ct5->pPhi[ipart];
				double gen_eta = my_ct5->pEta[ipart];  
				if(gen_pt<trkPtCut)continue ;
				if(TMath::Abs(gen_eta)>2.4)continue ;
				double rr = deltaR(-(my_ct->jteta[j4i]),my_ct->jtphi[j4i], gen_eta,gen_phi);
				if(my_ct5->pNRec[ipart]>0&&(my_ct5->mtrkAlgo[ipart]<4||(my_ct5->mtrkQual[ipart]))){
				for(int ir=0;ir<NRBIN_gen;ir++){
				if(RBIN_gen[ir]<rr && rr <= RBIN_gen[ir+1]){
				SumPtRBinEtaRefGen[ir]+=gen_pt;
				continue;						 
				}
				}
			} 
			}  
			} 
	
       }
		///=================================================================================================
		///------------------------------------- GenChgParticle Ends----------------------------------------
		///=================================================================================================
	
	
		
		///=================================================================================================
		///------------------------ RecTracks and tracking efficiency corrections Starts--------------------
		///=================================================================================================
	
	
		double correctionFactors[4] = {0,0,0,0};
		float trkweight = 1.;
		float trkweight_bkg_num = 1.;
		float trkweight_bkg_er = 1.;
	
		float SumpTLeadJet = 0.;      float SumpTSubLeadJet = 0.;
		float SumPtJet = 0; 
	
		/// Denominator for signal
		for(int tracks =0; tracks < my_ct5->nTrk; tracks++){
                   if(fabs(my_ct5->trkEta[tracks])>2.4) continue;


//                   std::cout << " highPurity : " << my_ct5->highPurity[tracks] << std::endl;
                 // std::cout << " highPurity : " << my_ct5->highPurity[tracks] << std::endl;

		   if (my_ct5->trkAlgo[tracks]<4 || my_ct5->highPurity[tracks]==1) {

                  // std::cout << " highPurity : " << my_ct5->highPurity[tracks] << std::endl;



	//	    if(fabs(my_ct5->trkEta[tracks])>2.4) continue;
		      if(my_ct5->trkPt[tracks]>trkPtCut) {
//      TVector3 jet_vec;
  //    TVector3 track_vec;
   //   jet_vec.SetPtEtaPhi(0, 0, 0);
     // track_vec.SetPtEtaPhi(0, 0, 0);
      jet_vec.SetPtEtaPhi(my_ct->jtpt[j4i], my_ct->jteta[j4i], my_ct->jtphi[j4i]);
      track_vec.SetPtEtaPhi(my_ct5->trkPt[tracks], my_ct5->trkEta[tracks], my_ct5->trkPhi[tracks]);
      double delr = jet_vec.DeltaR(track_vec);
	
	
	             double my_rr = deltaR(my_ct->jteta[j4i],my_ct->jtphi[j4i], my_ct5->trkEta[tracks],my_ct5->trkPhi[tracks]);
                     double rr =TMath::Sqrt((my_ct5->trkPhi[tracks]-my_ct->jtphi[j4i])*(my_ct5->trkPhi[tracks]-my_ct->jtphi[j4i])+(my_ct5->trkEta[tracks]-my_ct->jteta[j4i])*(my_ct5->trkEta[tracks]-my_ct->jteta[j4i]));

               // std::cout << " deltaR mine " << rr << " TVector3:  " << delr << "  yaxian's :  " <<  dr << std::endl;
      //          std::cout << " jetEta " <<  my_ct->jteta[j4i] << "  jet phi: " <<  my_ct->jtphi[j4i] << " trkEta : " << my_ct5->trkEta[tracks]  << " trkPhi: " << my_ct5->trkPhi[tracks] <<   "   TVector3:  " << delr << "  yaxian's :  " <<  dr << std::endl;


			double ptParticle=my_ct5->trkPt[tracks];
			float dphi_jet_track = my_ct->jtphi[j4i] - my_ct5->trkPhi[tracks];
			my_hists->dPhi_jet_track[ibin][ibin2]->Fill(fabs(dphi_jet_track), wvz*wcen);
	
	       	
		       if(my_rr<0.3){
		       
		       my_hists->radius_hist_mine[ibin][ibin2]->Fill(my_rr, wvz*wcen);
	               my_hists->track_cand_pT_hist[ibin][ibin2]->Fill(my_ct5->trkPt[tracks], wvz*wcen);
								       
		       }
		
		
		       if (rr<0.3){ 
                       
		       my_hists->radius_hist[ibin][ibin2]->Fill(rr, wvz*wcen);

		        
//	                std::cout << " jetEta " <<  my_ct->jteta[j4i] << "  jet phi: " <<  my_ct->jtphi[j4i] << " trkEta : " << my_ct5->trkEta[tracks]  << " trkPhi: " << my_ct5->trkPhi[tracks] <<   "   TVector3:  " << delr << "  yaxian's :  " <<  dr << std::endl;


	
	
	//		my_hists->track_cand_pT_hist[ibin][ibin2]->Fill(my_ct5->trkPt[tracks], wvz*wcen);
						        
        //if (evi%1==0) std::cout << ", evi: " << evi << " of " << n_evt << "jet index : " << j4i << my_ct->jtpt[j4i] << " jet eta : "  << my_ct->jteta[j4i] <<  "   jetphi :  " << my_ct->jtphi[j4i] <<    "   trkId : " << tracks <<  "   trkpt : " << my_ct5->trkPt[tracks] << "  trkEta: " << my_ct5->trkEta[tracks] << "   trkPhi : " <<  my_ct5->trkPhi[tracks] << "    deltaR " << rr  <<  std::endl;


		if( doTrackCorrections ) trkweight = trackCorrections[0]->GetCorr(my_ct5->trkPt[tracks],my_ct5->trkEta[tracks],my_ct->jtpt[j4i],my_ct3->hiBin);
		//	my_hists->track_cand_pT_hist_weighted[ibin][ibin2]->Fill(my_ct5->trkPt[tracks], trkweight*wvz*wcen);

                        my_hists->track_cand_pT_hist_weighted[ibin][ibin2]->Fill(my_ct5->trkPt[tracks], wvz*wcen);



                        ///my_hists->track_cand_pT_hist[ibin][ibin2]->Fill(my_ct5->trkPt[tracks], wvz*wcen);



			//std::cout << " trk weight " << trkweight << "  jetpt: " << my_ct->jtpt[j4i] << "  trkPt : " << my_ct5->trkPt[tracks]  <<   std::endl;
			 SumPtJet += ptParticle*trkweight;
			 SumpTLeadJet  += ptParticle*trkweight;
			} //deltaR03 loop
		     }   //pt cut
		   } ///track loop ends
		}
	
	
		///   Numerator for signal
		const int NRBIN=6;
		std::vector<double> SumPtRBin(NRBIN);
		for(int vi = 0; vi < (int) SumPtRBin.size(); vi++) {
		SumPtRBin.at(vi) = 0.;
		}
		const float RBIN[NRBIN+1]={0.0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3};
		double ptParticle=0;
		for(int tracks =0; tracks < my_ct5->nTrk; tracks++){
		   if (my_ct5->trkAlgo[tracks]<4 || my_ct5->highPurity[tracks]==1) {
		    if(fabs(my_ct5->trkEta[tracks])>2.4) continue;
		     if(my_ct5->trkPt[tracks]>trkPtCut) {
			double rr = deltaR(my_ct->jteta[j4i],my_ct->jtphi[j4i], my_ct5->trkEta[tracks],my_ct5->trkPhi[tracks]);
			ptParticle=my_ct5->trkPt[tracks];
			for(int ir=0;ir<NRBIN;ir++){
			  if(RBIN[ir]<rr && rr <= RBIN[ir+1]){
			   if( doTrackCorrections ) trkweight_bkg_num = trackCorrections[0]->GetCorr(my_ct5->trkPt[tracks],my_ct5->trkEta[tracks],my_ct->jtpt[j4i],my_ct3->hiBin);
			   SumPtRBin[ir]+=ptParticle*trkweight_bkg_num;
			   continue;						 
			  }
			}
		      } 
		   }
		}
	
	
		///   Numerator for eta reflection 
		std::vector<double> SumPtRBinEtaRef(NRBIN);
		for(int vi = 0; vi < (int) SumPtRBinEtaRef.size(); vi++) {
		SumPtRBinEtaRef.at(vi) = 0.;
		}
		double ptParticle_er=0;
		if( fabs(my_ct->jteta[j4i]) > 0.3 ){
		    for(int tracks =0; tracks < my_ct5->nTrk; tracks++){
		     if (my_ct5->trkAlgo[tracks]<4 || my_ct5->highPurity[tracks]==1) {
		       if(fabs(my_ct5->trkEta[tracks])>2.4) continue;
			 if(my_ct5->trkPt[tracks]>trkPtCut) {
			 double rr = deltaR(-(my_ct->jteta[j4i]),my_ct->jtphi[j4i], my_ct5->trkEta[tracks],my_ct5->trkPhi[tracks]);
			 ptParticle_er=my_ct5->trkPt[tracks];
			 for(int ir=0;ir<NRBIN;ir++){
			  if(RBIN[ir]<rr && rr <= RBIN[ir+1]){
			   if( doTrackCorrections ) trkweight_bkg_er = trackCorrections[0]->GetCorr(my_ct5->trkPt[tracks],my_ct5->trkEta[tracks],my_ct->jtpt[j4i],my_ct3->hiBin);
			    SumPtRBinEtaRef[ir]+=ptParticle_er*trkweight_bkg_er;
		            continue;						 
			   }
			 }
			} 
		     }  
		   }  
		}
	
		///=================================================================================================
		///------------------------ RecTracks and tracking efficiency corrections Ends----------------------
		///=================================================================================================
	
	
		///=================================================================================================
		///------------------------ Filling Shapes histograms  ---------------------------------------------
		///=================================================================================================
	
	
		std::vector<double> DifferentialPt(NRBIN);
		std::vector<double> DifferentialPtEtaRef(NRBIN);
		std::vector<double> DifferentialPt_sub(NRBIN);
		std::vector<double> DifferentialPtEtaRef_sub(NRBIN);
			std::vector<double> DifferentialPtGen(NRBIN);
			std::vector<double> DifferentialPtEtaRefGen(NRBIN);
	
		for(int ir=0;ir<NRBIN;ir++){
			if(my_ct->jtpt[j4i]>0.0001){
			DifferentialPt[ir] =SumPtRBin[ir]/(my_ct->jtpt[j4i]);
                if( !is_data ) {
			DifferentialPtGen[ir] =SumPtRBinGen[ir]/(my_ct->jtpt[j4i]);
	        }
			}
	
			if( fabs(my_ct->jteta[j4i]) > 0.3 ){
			if(my_ct->jtpt[j4i]>0.0001){
			DifferentialPtEtaRef[ir] =SumPtRBinEtaRef[ir]/(my_ct->jtpt[j4i]);
                if( !is_data ) {
			DifferentialPtEtaRefGen[ir] =SumPtRBinEtaRefGen[ir]/(my_ct->jtpt[j4i]);
	        }
			}
			}
		}
	
		if(my_ct->jtpt[j4i]>0.0001){
		my_hists->sig_count[ibin][ibin2] += wvz*wcen;
			if( fabs(my_ct->jteta[j4i]) > 0.3 ) {
			my_hists->bkg_count[ibin][ibin2] += wvz*wcen;
			}
	
		if( ibin == 1 && ibin2 == 1 ) std::cout << "bkg_count: " << my_hists->bkg_count[ibin][ibin2] << ", s+b count: " << my_hists->sig_count[ibin][ibin2] << "\n";
		}
		
	
	
	
		for(int ir=0;ir<NRBIN;ir++){
			float fill_val = 0.05*(ir+1)-0.025;
			if(my_ct->jtpt[j4i]>0.0001){
			my_hists->JetShapeDiffParticles_1D[ibin][ibin2]->Fill(fill_val,DifferentialPt[ir]*wvz*wcen);
                if( !is_data ) {
			my_hists->JetShapeDiffParticlesGen_1D[ibin][ibin2]->Fill(fill_val,DifferentialPtGen[ir]*wvz*wcen);
	        }
			}
			if( fabs(my_ct->jteta[j4i]) > 0.3 ) {
			if(my_ct->jtpt[j4i]>0.0001){
			my_hists->JetShapeDiffParticles_bkg_1D[ibin][ibin2]->Fill(fill_val,DifferentialPtEtaRef[ir]*wvz*wcen);
                if( !is_data ) {
			my_hists->JetShapeDiffParticlesGen_bkg_1D[ibin][ibin2]->Fill(fill_val,DifferentialPtEtaRefGen[ir]*wvz*wcen);
                }
			}
			}
			
		
		}
	
		std::vector<double> tot_sumpt_rbin(NRBIN);
		for(int irad=0;irad<NRBIN;irad++){
		for(int ir=0;ir<=irad;ir++){
			tot_sumpt_rbin[irad] +=SumPtRBin[ir];
		}
		}
	
		for(int ir=0;ir<NRBIN;ir++){
		float fill_val = 0.05*(ir+1);
			if(my_ct->jtpt[j4i]>0.0001){
			my_hists->JetShapeIntegratedParticles_1D[ibin][ibin2]->Fill(fill_val,(tot_sumpt_rbin[ir]/my_ct->jtpt[j4i])*wvz*wcen);
			}
			
		}
	
	
	
	
	
	
		} /// main jet loop
	if( evi % 500 == 0 ) my_hists->Write();
	
	
		///====================================== Code ends ==============================================================
		///====================================== Code ends ==============================================================
		///====================================== Code ends ==============================================================
	
	}  ///event loop
	
	///==========================   Event Loop ends ==================================================
	///==========================   Event Loop ends ==================================================
	///==========================   Event Loop ends ==================================================
	
	
	std::cout << "done with file " << fi << std::endl;
	
	}  /// file loop
	
	}
	
	
	
	
	///========================= background subtruction ============================================================
	///========================= background subtruction ============================================================
	///========================= background subtruction ============================================================
	
	
	void GetBkgShape(TVector3 highest_jet_vec, TVector3 second_highest_jet_vec, TVector3& bkg_dir, TVector3& bkg_dir2) { 
	
	
	//TVector3 bkg_dir = highest_jet_vec.Cross(second_highest_jet_vec);
	
	bkg_dir = highest_jet_vec;
	bkg_dir2 = second_highest_jet_vec;
	
	float bkg_dir_Eta = -bkg_dir.Eta();
	float bkg_dir_Phi = bkg_dir.Phi();
	float bkg_dir_Pt = bkg_dir.Pt();
	
	float bkg_dir_Eta2 = -bkg_dir2.Eta();
	float bkg_dir_Phi2 = bkg_dir2.Phi();
	float bkg_dir_Pt2 = bkg_dir2.Pt();
	
	bkg_dir.SetPtEtaPhi(bkg_dir_Pt, bkg_dir_Eta, bkg_dir_Phi);
	bkg_dir2.SetPtEtaPhi(bkg_dir_Pt2, bkg_dir_Eta2, bkg_dir_Phi2);
	
	}
	
	void ReadFileList(std::vector<TString> &my_file_names, TString file_of_names, bool debug)
	{
	ifstream file_stream(file_of_names);
	std::string line;
	my_file_names.clear();
	if( debug ) std::cout << "Open file " << file_of_names << " to extract files to run over" << std::endl;
	if( file_stream.is_open() ) {
	if( debug ) std::cout << "Opened " << file_of_names << " for reading" << std::endl;
	int line_num = 0;
	while( !file_stream.eof() ) {
	getline(file_stream, line);
	if( debug ) std::cout << line_num << ": " << line << std::endl;
	TString tstring_line(line);
	if( tstring_line.CompareTo("", TString::kExact) != 0 ) my_file_names.push_back(tstring_line);
	line_num++;
	}
	} else {
	std::cout << "Error, could not open " << file_of_names << " for reading" << std::endl;
	assert(0);
	}
	}
	
	
	
	
	//void GetFilesOfFileNames(std::vector<TString> &files_of_file_names, std::vector<float> &Xsections) ////getting the data/simulation based on whatever dataset you pick (arg)
	void GetFilesOfFileNames(std::vector<TString> &files_of_file_names, std::vector<float> &Xsections, std::vector<double> &assumed_n_evt) ////getting the data/simulation based on whatever dataset you pick (arg)
	
	
	{
	files_of_file_names.clear();   Xsections.clear();
	
	if( dataset_type_code == e_HydJet30 ) {
	files_of_file_names.push_back("Hydjet_Pt30.txt");
	Xsections.push_back(1.079e-02);
	assumed_n_evt.push_back(109918);
	
	}else if( dataset_type_code == e_HydJet50 ) {
	files_of_file_names.push_back("Hydjet_Pt50.txt");
	Xsections.push_back(1.021e-03 - 9.913E-05);
	assumed_n_evt.push_back(112166);
	
	}else if( dataset_type_code == e_HydJet80 ) {
	files_of_file_names.push_back("Hydjet_Pt80.txt");
	Xsections.push_back(9.913E-05 - 3.069E-05);
	assumed_n_evt.push_back(146162);
	
	}else if( dataset_type_code == e_HydJet100 ) {
	files_of_file_names.push_back("Hydjet_Pt100.txt");
	Xsections.push_back(3.069E-05 - 1.128E-05);
	assumed_n_evt.push_back(593463);
	
	}else if( dataset_type_code == e_HydJet120 ) {
	files_of_file_names.push_back("Hydjet_Pt120.txt");
	Xsections.push_back(1.128E-05 - 1.470E-06);
	assumed_n_evt.push_back(141263);
	
	}else if( dataset_type_code == e_HydJet170 ) {
	files_of_file_names.push_back("Hydjet_Pt170.txt");
	Xsections.push_back(1.470E-06 - 5.310E-07);
	assumed_n_evt.push_back(62944);
	
	}else if( dataset_type_code == e_HydJet200 ) {
	files_of_file_names.push_back("Hydjet_Pt200.txt");
	Xsections.push_back(5.310E-07 - 1.192E-07);
	assumed_n_evt.push_back(54952);
	
	}else if( dataset_type_code == e_HydJet250 ) {
	files_of_file_names.push_back("Hydjet_Pt250.txt");
	Xsections.push_back(1.192E-07 - 3.176E-08);
	assumed_n_evt.push_back(37856);
	
	}else if( dataset_type_code == e_HydJet300 ) {
	files_of_file_names.push_back("Hydjet_Pt300.txt");
	Xsections.push_back(3.176E-08);
	assumed_n_evt.push_back(53009);
	
	}else if( dataset_type_code == e_Data2011 ) {
	files_of_file_names.push_back("Data2011.txt"); 
	}else {
	std::cout << "I don't understand the fileset" << std::endl;
	assert(0);
	}
	}
	
	
	
	float GetDatasetWeight(double n_evt_raw, double Xsection)
	{
	assert( n_evt_raw > 0.5 );
	//  double wt  = (Xsection / (n_evt_raw/100000.)); /// data luminosity is 150 mikrob^-1
	//  double wt  = (Xsection / n_evt_raw*150); /// data luminosity is 150 mikrob^-1
	double wt  = (Xsection / n_evt_raw);
	
	return wt;
	}
	

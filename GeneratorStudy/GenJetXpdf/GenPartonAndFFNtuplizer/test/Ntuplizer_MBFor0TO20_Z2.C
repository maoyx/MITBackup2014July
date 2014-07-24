//We only need ~Ed3sigma/dp3, nothing else; we compute dsigma/dpT instead

#include <iostream>

#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TNtuple.h"
#include "TMath.h"
#include "TString.h"
#include "TClonesArray.h"
#include "TTree.h"
#include "TSystem.h"
#include "TRandom2.h"

#include "GenParticleInfo.h"
#include "SpectraStudyTreeClass.h"

// Histograms 
TH1F *dPtHat;
TH1F *dNevtMinPtHat;
TH1F *dNJetdPt;

TH2F *dNAllTrkdPtdPtHat;
TH2F *dNAllTrkdPtdPtHat_ForCorrelation;
TH2F *dNAllTrkdPtdPtHat_adjustedBinning;
TH2F *dNAllTrkdPtdPhi;

TH2F *dNAllTrkdPtdPtHat_eta0308;
TH2F *dNAllTrkdPtdPtHat_eta0813;
TH2F *dNAllTrkdPtdPtHat_eta1318;

// Variables
vector<double> ptBins, ptHatBins, ptHatBins_adjusted;
vector<double> jptBins;
vector<double> dphiBins;

//------------------------------------
void prepareHist();
void saveHistRoot();
//------------------------------------

void Ntuplizer_MBFor0TO20_Z2(bool save=true){

//   TString infdir = "/net/hidsk0001/d00/scratch/krajczar/ppRef/RelativePlacement/5020GeV";
//   TString infile = "spectAnaGEN_March20";
   TString infdir = "/net/hidsk0001/d00/scratch/maoyx/GeneratorStudy/ppRef/Z2_5020GeV";
   TString infile = "AnaGEN_Oct6_Z2_MB_Pt0to20_numEvent640000";
   TString outdir = "/net/hidsk0001/d00/scratch/maoyx/GeneratorStudy/CMSSW_5_3_8_HI_patch2/src/GenJetXpdf/GenPartonAndFFNtuplizer/test" ;
   TString outfile;
   outfile.Append(Form("TEST_%s",infile.Data()));

   cout<<"Check Parameters = "<<outfile.Data()<<endl;

   TFile *f1 = TFile::Open(Form("%s/%s.root",infdir.Data(),infile.Data()));

   if(!f1) {
      Error("<Input File Reading>","File is NULL");
      return;
   }

   f1->cd("genSpectAna");
   TTree *nt = (TTree*) f1->FindObjectAny("SpectraStudyTree");
   if(!nt) {
      Error("<Input Tree Reading>","Tree is NULL");
      return;
   }

   gSystem->Load("/net/hidsk0001/d00/scratch/maoyx/GeneratorStudy/CMSSW_5_3_8_HI_patch2/lib/slc5_amd64_gcc462/pluginGenJetXpdfGenPartonAndFFNtuplizer.so");

   SpectraStudyTreeClass stree;

   TClonesArray *alltrk = new TClonesArray("GenParticleInfo");
   TClonesArray *AllParticles_test = new TClonesArray("GenParticleInfo");
   TClonesArray *AssParticles_test = new TClonesArray("GenParticleInfo");

   nt->SetBranchAddress("fPthat",&stree.fPthat);
   nt->SetBranchAddress("fCrossx",&stree.fCrossx);
   nt->SetBranchAddress("isMinPtHat",&stree.isMinPtHat);
   nt->SetBranchAddress("nNumEvt",&stree.nNumEvt);

   nt->SetBranchAddress("AllParticles",&alltrk);
   nt->SetBranchAddress("AssParticles",&AssParticles_test);   

   nt->SetBranchAddress("nJets",&stree.nJets);
   nt->SetBranchAddress("fJPt",stree.fJPt);
   nt->SetBranchAddress("fJEt",stree.fJEt);
   nt->SetBranchAddress("fJEta",stree.fJEta);
   nt->SetBranchAddress("fJPhi",stree.fJPhi);

   prepareHist();

   int totN = 0;
   int totN_My = 0;

//CHECK NUMBER OF EVENTS - STARTS - 
   for (int i=0;i<nt->GetEntries();i++){

      nt->GetEntry(i);
      if(stree.isMinPtHat==1)
         totN_My++;
   }
   std::cerr<<" Number of events in the lowest pThat bin: " << totN_My << std::endl;
//CHECK NUMBER OF EVENTS - ENDS -

   std::cerr<<" Number of entries in the tree: " << nt->GetEntries() << std::endl;
   for (int i=0;i<nt->GetEntries();i++){

      nt->GetEntry(i);

////////////////test -start-      
//ALWAYS ZERO ENTRIES
//      std::cerr<<"==== STARTING THE CROSS CHECK ====" << std::endl;
//      std::cerr<<"   entries, AssParticles_test: " << AssParticles_test->GetEntriesFast() << std::endl;
//      std::cerr<<"   entries, alltrk           : " << alltrk->GetEntriesFast() << std::endl;
//      for (int l=0; l<AssParticles_test->GetEntriesFast(); ++l) {
//	 GenParticleInfo *particle = (GenParticleInfo*)AssParticles_test->At(l);
//
//	 float hoppa  = particle->fPt;
//
//         std::cerr<<"hoppa pt: " << hoppa << std::endl;
//      }
////////////////test -end-      

      float nevt = (float) stree.nNumEvt;
      //Put in the correct number of events for the first bin  //important, maybe ask Yue Shi
      if(stree.isMinPtHat==1)
         nevt = totN_My;

      if (i%20000==0) {
	 cout<<"Cross-section of the sub-sample: "<<stree.fCrossx<<" pTHat of the collision: "<<stree.fPthat << endl;
//	     <<" number of events = "<<nevt
//	     <<" number of jets = "<<stree.nJets<<" number of saved gen particle = "<<alltrk->GetEntriesFast()<<endl;
      }

      dPtHat->Fill(stree.fPthat);

      // Fill leading jets for |eta|<1.5 : ak5GenJets + |eta|<1 for charged particles
      double leadingJetPt = 0.;
      for (int j=0; j<stree.nJets; ++j) {

         float jpt  = stree.fJPt[j];
         float jeta = stree.fJEta[j];
         float jphi = stree.fJPhi[j];

         if(fabs(jeta)>1.5) continue;

         if(jpt > leadingJetPt) leadingJetPt = jpt;
      }
      dNJetdPt->Fill(leadingJetPt,stree.fCrossx);

      
      // 1. All Charged Tracks ----------------------------------------
      for (int l=0; l<alltrk->GetEntriesFast(); ++l) {
	 GenParticleInfo *AllParticles = (GenParticleInfo*)alltrk->At(l);

	 float alltrkpt  = AllParticles->fPt;
	 float alltrketa = AllParticles->fEta;
	 float alltrkphi = AllParticles->fPhi;

//         std::cerr<<"------------------" << std::endl;
//         std::cerr<<" phi: " << alltrkphi << std::endl;
//         std::cerr<<" eta: " << alltrketa << std::endl;
//         std::cerr<<" pt : " << alltrkpt << std::endl;

	 // HIST FILLING
//	 if(fabs(alltrketa)>1.0) continue; // eta cut     

	 if(fabs(alltrketa)<=1.0) {
            dNAllTrkdPtdPtHat->Fill(alltrkpt,stree.fPthat,stree.fCrossx/nevt);
            dNAllTrkdPtdPtHat_ForCorrelation->Fill(alltrkpt,stree.fPthat,stree.fCrossx/nevt);
	    dNAllTrkdPtdPtHat_adjustedBinning->Fill(alltrkpt,stree.fPthat,stree.fCrossx/nevt);
            dNAllTrkdPtdPhi->Fill(alltrkpt,alltrkphi,stree.fCrossx/nevt);
         }

	 if(fabs(alltrketa)>0.3 && fabs(alltrketa)<=0.8)
            dNAllTrkdPtdPtHat_eta0308->Fill(alltrkpt,stree.fPthat,stree.fCrossx/nevt);
	 if(fabs(alltrketa)>0.8 && fabs(alltrketa)<=1.3)
            dNAllTrkdPtdPtHat_eta0813->Fill(alltrkpt,stree.fPthat,stree.fCrossx/nevt);
	 if(fabs(alltrketa)>1.3 && fabs(alltrketa)<=1.8)
            dNAllTrkdPtdPtHat_eta1318->Fill(alltrkpt,stree.fPthat,stree.fCrossx/nevt);
      }

      if(stree.isMinPtHat==1) dNevtMinPtHat->Fill(1.1);
      totN++;

   } // end of all entries

   cout<<"Number of events = "<<totN<<endl;

   // Save histograms in a root file
   if(save){
      cout<<"Output file = "<<Form("%s/%s.root",outdir.Data(),outfile.Data())<<endl;
      TFile *outputFile = new TFile(Form("%s/%s.root",outdir.Data(),outfile.Data()),"recreate");
      saveHistRoot();
   }

}


void prepareHist(){

   TH1::SetDefaultSumw2();
   TH2::SetDefaultSumw2();
   TH3::SetDefaultSumw2();

   const double small = 1e-3;

   // ptHat bins
   double pthb;
   for(pthb = 0; pthb < 3600-small; pthb += 5) ptHatBins.push_back(pthb);
   ptHatBins.push_back(3600);

   double pthb_adjusted;
   for(pthb_adjusted = 0; pthb_adjusted < 100-small; pthb_adjusted += 5) ptHatBins_adjusted.push_back(pthb_adjusted);
   for(pthb_adjusted = 100; pthb_adjusted < 400-small; pthb_adjusted += 10) ptHatBins_adjusted.push_back(pthb_adjusted);
   for(pthb_adjusted = 400; pthb_adjusted < 800-small; pthb_adjusted += 20) ptHatBins_adjusted.push_back(pthb_adjusted);
   for(pthb_adjusted = 800; pthb_adjusted < 1600-small; pthb_adjusted += 40) ptHatBins_adjusted.push_back(pthb_adjusted);
   for(pthb_adjusted = 1600; pthb_adjusted < 3200-small; pthb_adjusted += 80) ptHatBins_adjusted.push_back(pthb_adjusted);
   ptHatBins_adjusted.push_back(3200);

   // pt bins
   double ptb;
   for(ptb =   0  ; ptb <   1.2-small; ptb +=  0.2 ) ptBins.push_back(ptb);
   for(ptb =   1.2; ptb <   2.4-small; ptb +=  0.4 ) ptBins.push_back(ptb);
   for(ptb =   2.4; ptb <   26.4-small; ptb +=  0.8 ) ptBins.push_back(ptb);
   for(ptb =   26.4; ptb <   119.2-small; ptb +=  1.6 ) ptBins.push_back(ptb);
   ptBins.push_back(119.2);
//   for(ptb =   7.2; ptb <  13.2-small; ptb +=  2. ) ptBins.push_back(ptb);
//   for(ptb =  13.2; ptb <  25.2-small; ptb +=  4. ) ptBins.push_back(ptb); 
//   for(ptb =  25.2; ptb <  61.2-small; ptb +=  12. ) ptBins.push_back(ptb);
//   for(ptb =  61.2; ptb <  121.2-small; ptb +=  20. ) ptBins.push_back(ptb);
//   for(ptb = 121.2; ptb < 361.2-small; ptb +=  40. ) ptBins.push_back(ptb);
//   for(ptb = 361.2; ptb < 396.0-small; ptb +=  34.8) ptBins.push_back(ptb);  
//   for(ptb = 396.0; ptb <1221.6-small; ptb +=  34.4) ptBins.push_back(ptb);
//   for(ptb = 1221.6; ptb <2882.8-small; ptb +=  68.8) ptBins.push_back(ptb);
//   for(ptb = 2882.8; ptb <3708.4-small; ptb +=  137.6) ptBins.push_back(ptb);
//   ptBins.push_back(3708.4);


   Int_t NumOfPtBins_part = 40;

   double ptBins_adjusted[] = {0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 3.2, 4.0, 4.8, 5.6, 6.4, 7.2, 9.6, 12.0, 14.4, 19.2, 24.0, 28.8, 35.2, 41.6, 48.0, 60.8, 73.6, 86.4, 103.6, 120.8, 138., 155.2, 172.4, 189.6, 206.8};

   // phi bins
   double dphib;

   for(dphib = -3.2; dphib < 3.2-small; dphib += 0.05) dphiBins.push_back(dphib);
   dphiBins.push_back(3.2);

   // jpt bins
   double djpt;
   for(djpt = 0.; djpt < 100-small; djpt += 2.) jptBins.push_back(djpt);
   for(djpt = 100.; djpt < 200-small; djpt += 4.) jptBins.push_back(djpt);
   for(djpt = 200.; djpt < 400-small; djpt += 8.) jptBins.push_back(djpt);
   for(djpt = 400.; djpt < 800-small; djpt += 16.) jptBins.push_back(djpt);
   for(djpt = 800.; djpt < 1600-small; djpt += 32.) jptBins.push_back(djpt);
   jptBins.push_back(1600.);


   // 1D      
   dPtHat = new TH1F("dPtHat","#hat{q} with no weight", ptHatBins.size()-1, &ptHatBins[0]);   
   dNevtMinPtHat = new TH1F("dNevtMinPtHat","Number of processed events in the min pt_hat sample",10,0.0,10.0); 
   dNJetdPt = new TH1F("dNJetdPt","Jet pt",jptBins.size()-1, &jptBins[0]);

   // 2D
   dNAllTrkdPtdPtHat = new TH2F("dNAllTrkdPtdPtHat","Charged particle p_{T} vs #hat{q}; p_{T} (GeV/c); #hat{q} (GeV)",
				ptBins.size()-1, &ptBins[0], ptHatBins.size()-1, &ptHatBins[0]);

   dNAllTrkdPtdPtHat_ForCorrelation = new TH2F("dNAllTrkdPtdPtHat_ForCorrelation","Charged particle p_{T} vs #hat{q}; p_{T} (GeV/c); #hat{q} (GeV)",
				ptBins.size()-1, &ptBins[0], ptHatBins_adjusted.size()-1, &ptHatBins_adjusted[0]);

   dNAllTrkdPtdPtHat_adjustedBinning = new TH2F("dNAllTrkdPtdPtHat_adjustedBinning","Charged particle p_{T} vs #hat{q}; p_{T} (GeV/c); #hat{q} (GeV)",
				NumOfPtBins_part-1, &ptBins_adjusted[0], ptHatBins.size()-1, &ptHatBins[0]);

   dNAllTrkdPtdPtHat_eta0308 = new TH2F("dNAllTrkdPtdPtHat_eta0308","Charged particle p_{T} vs #hat{q}; p_{T} (GeV/c); #hat{q} (GeV)",
				ptBins.size()-1, &ptBins[0], ptHatBins.size()-1, &ptHatBins[0]);
   dNAllTrkdPtdPtHat_eta0813 = new TH2F("dNAllTrkdPtdPtHat_eta0813","Charged particle p_{T} vs #hat{q}; p_{T} (GeV/c); #hat{q} (GeV)",
				ptBins.size()-1, &ptBins[0], ptHatBins.size()-1, &ptHatBins[0]);
   dNAllTrkdPtdPtHat_eta1318 = new TH2F("dNAllTrkdPtdPtHat_eta1318","Charged particle p_{T} vs #hat{q}; p_{T} (GeV/c); #hat{q} (GeV)",
				ptBins.size()-1, &ptBins[0], ptHatBins.size()-1, &ptHatBins[0]);
   
   dNAllTrkdPtdPhi = new TH2F("dNAllTrkdPtdPhi","p_{T} vs #Delta#phi; p_{T} (GeV/c); #Delta#phi (rad)",
			      ptBins.size()-1, &ptBins[0], dphiBins.size()-1, &dphiBins[0]);
}


void saveHistRoot(){

   dPtHat->Write();
   dNevtMinPtHat->Write();
   dNJetdPt->Write();

   dNAllTrkdPtdPtHat->Write();
   dNAllTrkdPtdPtHat_eta0308->Write();
   dNAllTrkdPtdPtHat_eta0813->Write();
   dNAllTrkdPtdPtHat_eta1318->Write();
   dNAllTrkdPtdPtHat_ForCorrelation->Write();
   dNAllTrkdPtdPtHat_adjustedBinning->Write();
   dNAllTrkdPtdPhi->Write();
}


//We only need ~Ed3sigma/dp3, nothing else; we compute dsigma/dpT instead

#include <iostream>

#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TNtuple.h"
#include "TVector3.h"
#include "TMath.h"
#include "TString.h"
#include "TClonesArray.h"
#include "TTree.h"
#include "TProfile.h"
#include "TSystem.h"
#include "TRandom2.h"

#include "GenParticleInfo.h"
#include "SpectraStudyTreeClass.h"
using namespace std;

const int netabin = 7 ;
//const double deta[]={-2.2, -1.2, -0.7, -0.3, 0.3, 0.7,1.2,2.2} ;
const double deta[]={-2.0, -1.5, -1.0, -0.5, 0.5, 1.0,1.5,2.0} ;
const double dtrketa[]={-1.8, -1.3, -0.8, -0.3, 0.3, 0.8,1.3,1.8} ;
const double dphicut = 2*TMath::Pi()/3. ;
const double leadingjetcut = 120. ;
const double subleadjetcut = 30. ;
const double conesize = 0.3 ;

// Histograms 
TH1F *dPtHat;
TH1F *dNevtMinPtHat;
TH1F *dNJetdPt;

TProfile *hPartonX1X2;
TProfile *hPartonXQ2;
TProfile *hPartonXQ2Pt1to4;
TProfile *hPartonXQ2Pt4to10;
TProfile *hPartonXQ2PtAbove10;
TProfile *hJetPtPartonX;
TProfile *hJetPtM1P1PartonX;
TProfile *hJetEtaPartonX;
TProfile *hTrkPtPartonX;
TProfile *hTrkPtM1P1PartonX;
TProfile *hTrkPtM1P1Q2;
TProfile *hJetPtM1P1Q2;
TProfile *hJetPtEtaBinPartonX[netabin];
TProfile *hTrkPtEtaBinPartonX[netabin];
TProfile *hTrkPtEtaBinQ2[netabin];
TProfile *hTrkEtaPartonX;
TH1F *hJetPtEtaBin[netabin];
TH1F *hTrkPtEtaBin[netabin];


TH1F *hAllJetdPt;
TH1F *hJetPtM1P1;
TH1F *hTrkPtM1P1;
TH1F *hNeutralPtM1P1;
TH1F *hJetTrkPtM1P1;
TH1F *hAllTrkdPt;
TH1F *hPosTrkdPt;
TH1F *hNegTrkdPt;

//dijet histograms
TProfile *hLeadingJetPtPartonX;
TH2F *hDijetPtRatio;
TH2F *hDijetPtDphi;
TH2F *hDijetPtDeta;
TH2F *hDijetEta;
TH2F *hDijetEtaSum;
TProfile *hEtaDijetPartonX;
TProfile *hDijetPartonXQ2;
TH1F *hJetMassM1P1;
TH1F *hJetMassEtaBin[netabin];
TProfile *hJetMassM1P1PartonX;
TProfile *hJetMassEtaBinPartonX[netabin];


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
vector<double> q2Bins;
vector<double> xBins;
vector<double> dphiBins;

int ptmin ;
int ptmax ;
//------------------------------------
void prepareHist();
void saveHistRoot();
TH1 * normalizeByBinWidth(TH1 *histo);
Double_t func(Double_t *x, Double_t *par);

//------------------------------------

void Ntuplizer_JetsPYTHIA_Z2(bool save=true){
//   TString infdir = "/net/hidsk0001/d00/scratch/krajczar/ppRef/RelativePlacement/5020GeV";
//   TString infile = "spectAnaGEN_March20";
//   TString infdir = "/net/hidsk0001/d00/scratch/maoyx/GeneratorStudy/ppRef/Z2_5020GeV";
//   TString infdir = "/net/hidsk0001/d00/scratch/maoyx/GeneratorStudy/ppRef/ProQ20_5020GeV";
   TString filename ;
   TString tune ="Z2_5020GeV";
   if(tune=="Z2_5020GeV") filename="Jan27_Z2";
   else if(tune=="D6T_5020GeV") filename="Feb6_D6T";
   else if(tune=="ProQ20_5020GeV") filename="Jan30_ProQ20";
   else if(tune=="AMBT1_5020GeV") filename="Feb4_AMBT1";
   else filename="Feb02_Z2Star";
   TString infdir = Form("/net/hidsk0001/d00/scratch/maoyx/GeneratorStudy/ppRef/%s",tune.Data());
   TString infile ;
     ptmin=atoi(getenv("PTMIN")) ;
     ptmax=atoi(getenv("PTMAX")) ;
     std::cerr <<"ptmin =" <<ptmin << "  ptmax =" <<ptmax <<endl ;
/*   if(ptmin==0) infile = Form("AnaGENJetR3_Jan27_Z2_MB_Pt%dto%d_numEvent640000", ptmin, ptmax);
   else if(ptmin==380) infile = Form("AnaGENJetR3_Jan27_Z2_Pt%dtoinf_numEvent640000", ptmin);
   else infile = Form("AnaGENJetR3_Jan27_Z2_Pt%dto%d_numEvent640000", ptmin, ptmax);
*/
   if(ptmin==380) infile = Form("AnaGENJetR3_%s_Pt%dtoinf_numEvent640000", filename.Data(),ptmin);
   else infile = Form("AnaGENJetR3_%s_Pt%dto%d_numEvent640000", filename.Data(), ptmin, ptmax);
   TString outdir = "." ;
   TString outfile;
 //  outfile.Append(Form("DiJetMass_nPDF%s",infile.Data()));
   outfile.Append(Form("nPDFWeight_GenAna_%s",infile.Data()));

   std::cerr<<"Check Parameters = "<<infile.Data()<<endl;

   TFile *f1 = TFile::Open(Form("%s/%s.root",infdir.Data(),infile.Data()));

   if(!f1) {
      Error("<Input File Reading>","File is NULL");
      return;
   }

//   f1->cd("genSpectAna");
   TTree *nt = (TTree*) f1->Get("genSpectAna/SpectraStudyTree");
   TTree *tJets = (TTree*) f1->Get("genJetPDF/hi");
   nt->AddFriend(tJets);

  if(!nt || !tJets) {
      Error("<Input Tree Reading>","Tree is NULL");
      return;
   }

   gSystem->Load("/net/hidsk0001/d00/scratch/maoyx/GeneratorStudy/PYTHIA/CMSSW_5_3_8_HI_patch2/lib/slc5_amd64_gcc462/pluginGenJetXpdfGenPartonAndFFNtuplizer.so");

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
   tJets->SetBranchAddress("x1",&stree.fPdfx1);
   tJets->SetBranchAddress("x2",&stree.fPdfx2);

   prepareHist();

   int totN = 0;
   int totN_My = 0;
   // JV the nPDF 
//    TF1 * fpdf = new TF1("fpdf","pol8",0,1);
//    Double_t paramset[9] = {0.905354, 27.0304, -491.564, 3771.39, -15606.1, 37242.3, -51143, 37432, -11268.1};
   
//   TF1 * fpdf = new TF1("fpdf","pol9",0.,1.);
//   Double_t paramset[] = {0.885878, 12.3164, -232.156, 2108.86, -10804.9, 33013.3, -61320.6, 67869.2, -41148.8, 10524.3};
//   fpdf->SetParameters(paramset);

   TF1 * fpdf = new TF1("fpdf", func, 0.00001,0.98,6);
  // Double_t paramset[] = {0.46, 0.02, 1.6, 0.3, 0.55, 1.33}; // order (y0, xa, ya, xe, ye, b)
 //  Double_t paramset[] = {0.7, 0.04, 1.4, 0.5, 0.6, 1.33}; // order (y0, xa, ya, xe, ye, b)
 //  Double_t paramset[] = {0.8, 0.01, 1.8, 0.3, 0.55, 1.33}; // order (y0, xa, ya, xe, ye, b)
 //  Double_t paramset[] = {0.4, 0.01, 1.8, 0.2, 0.55, 1.33}; // order (y0, xa, ya, xe, ye, b)
 //  Double_t paramset[] = {0.45, 0.01, 1.8, 0.5, 0.7, 1.33}; // order (y0, xa, ya, xe, ye, b)
//   Double_t paramset[] = {0.9, 0.03, 5.8, 0.5, 0.5, 1.33}; // order (y0, xa, ya, xe, ye, b)
   Double_t paramset[] = {0.8, 0.05, 1.3, 0.5, 0.7, 1.33}; // order (y0, xa, ya, xe, ye, b)
   fpdf->SetParameters(paramset);
  
   float w=1;


//CHECK NUMBER OF EVENTS - STARTS - 
   for (int i=0;i<nt->GetEntries();i++){

      nt->GetEntry(i);
      tJets->GetEntry(i);
      if(stree.isMinPtHat==1)
         totN_My++;
   }
   std::cerr<<" Number of events in the lowest pThat bin: " << totN_My << std::endl;
//CHECK NUMBER OF EVENTS - ENDS -

   std::cerr<<" Number of entries in the tree: " << nt->GetEntries() << std::endl;

   float nevt = nt->GetEntries() ;
   float cs = stree.fCrossx ;

   std::cerr<<"pthat =" <<ptmin << " Cross-section of the sub-sample: "<<cs<<" Nevent = : "<<nevt << endl; 
       TVector3 jet1_vec;
       TVector3 jet2_vec;
       TVector3 jet_vec;
       TVector3 trk_vec;
   for (int i=0;i<nt->GetEntries();i++){
     
     nt->GetEntry(i);
     tJets->GetEntry(i);
     ////////////////test -start-      
//ALWAYS ZERO ENTRIES
/*      std::cerr<<"==== STARTING THE CROSS CHECK ====" << std::endl;
      std::cerr<<"   entries, AssParticles_test: " << AssParticles_test->GetEntriesFast() << std::endl;
      std::cerr<<"   entries, alltrk           : " << alltrk->GetEntriesFast() << std::endl;
      for (int l=0; l<AssParticles_test->GetEntriesFast(); ++l) {
	 GenParticleInfo *particle = (GenParticleInfo*)AssParticles_test->At(l);

	 float hoppa  = particle->fPt;

         std::cerr<<"hoppa pt: " << hoppa << std::endl;
      }
////////////////test -end-      
*/
      float x1 = (float) stree.fPdfx1;
      float x2 = (float) stree.fPdfx2;
      float pthat = (float) stree.fPthat ;
  //    if(x1==1) x1 = 1.e-4 ;
  //    if(x2==1) x2 = 1.e-4 ;
       if(x1==1 || x2==1) continue ;
         w = fpdf->Eval(x1); // getting the weight from a function
      //   if(x1>0.83) w = 1.6; 
      // here we use a step function 
   //   w = 1 ;


      //Put in the correct number of events for the first bin  //important, maybe ask Yue Shi
      if(stree.isMinPtHat==1)
         nevt = totN_My;
      if (i%20000==0) {
	 cout<<"Cross-section of the sub-sample: "<<stree.fCrossx<<" pTHat of the collision: "<<pthat << endl;
//	     <<" number of events = "<<nevt
//	     <<" number of jets = "<<stree.nJets<<" number of saved gen particle = "<<alltrk->GetEntriesFast()<<endl;
      }

 //  cout <<"x1 =" <<x1<<endl ;
      dPtHat->Fill(pthat, stree.fCrossx/nevt);
      hPartonX1X2->Fill(x1, x2, stree.fCrossx/nevt);
      hPartonXQ2->Fill(x1, pthat*pthat, (stree.fCrossx/nevt));

  //    dPtHat->Fill(pthat);
  //    hPartonX1X2->Fill(x1, x2);
      // Fill leading jets for |eta|<1.5 : ak5GenJets + |eta|<1 for charged particles
      double leadingJetPt = -999.;
      double leadingJetEta = -999.;
      double leadingJetPhi = -999.;
      int leadingIndex = -1;
      double subleadingJetPt = -999.;
      double subleadingJetEta = -999.;
      double subleadingJetPhi = -999.;
      int subleadingIndex = -1;
      int jEtaBin = -1 ;
      float etashift = 0.465 ;
      jet1_vec.SetPtEtaPhi(0, 0, 0);
      jet2_vec.SetPtEtaPhi(0, 0, 0);
      for (int j=0; j<stree.nJets; j++) {
	
	float jpt  = stree.fJPt[j];
	float jeta = stree.fJEta[j];
	float jphi = stree.fJPhi[j];

         if(jpt<30.) continue ;
	if(fabs(jeta)<1.0)hJetPtM1P1Q2->Fill(jpt,pthat*pthat, w*(stree.fCrossx/nevt));
         if(fabs(jeta)>3.0) continue;
	 hJetPtPartonX->Fill(jpt,x2, w*stree.fCrossx/nevt); 
	 //  hJetPtPartonX->Fill(x1, jpt); 
	 if(jpt>50.)hJetEtaPartonX->Fill(x2, jeta, w*stree.fCrossx/nevt); 
	 //  if(jpt>50.)hJetEtaPartonX->Fill(x1, jeta); 
	 if(fabs(jeta)<1.0)hJetPtM1P1PartonX->Fill(jpt, x2, w*stree.fCrossx/nevt); 
	 if(fabs(jeta)<1.0)hJetPtM1P1->Fill(jpt, w*stree.fCrossx/nevt); 
         // if(fabs(jeta)<1.0)hJetPtM1P1PartonX->Fill(x1, jpt); 
	 hAllJetdPt->Fill(jpt, w*stree.fCrossx/nevt);
         //  hAllJetdPt->Fill(jpt);
	 
         for(int ieta = 0 ; ieta < netabin ; ieta++){
          if(jeta >= deta[ieta] && jeta <deta[ieta+1]) jEtaBin = ieta ;
         }
         if(jEtaBin!=-1)  hJetPtEtaBinPartonX[jEtaBin]->Fill(jpt,x2, w*stree.fCrossx/nevt);
         if(jEtaBin!=-1)  hJetPtEtaBin[jEtaBin]->Fill(jpt, w*stree.fCrossx/nevt);
         if(jpt > leadingJetPt) {
          leadingJetPt = jpt;
          leadingJetPhi = jphi;
          leadingJetEta = jeta;
          leadingIndex = j ;
         }
      }
      dNJetdPt->Fill(leadingJetPt,w*stree.fCrossx/nevt);
      jet1_vec.SetPtEtaPhi(leadingJetPt, leadingJetEta, leadingJetPhi); 
      if(fabs(leadingJetEta)<1.0) hLeadingJetPtPartonX->Fill(leadingJetPt,x2,  w*stree.fCrossx/nevt);
    //    std::cerr <<"dijets :" << "pt =" <<leadingJetPt  << endl ;
           //search for subleading jets
           for (int j=0; j<stree.nJets; j++) {
            if(leadingIndex<0. || j == leadingIndex) continue ;
              if(leadingJetPhi<-5.) continue ;
          //   std:cerr <<"start to look for subleading!!!" <<endl ;
               float jpt  = stree.fJPt[j];
               float jeta = stree.fJEta[j];
               float jphi = stree.fJPhi[j];
                 jet2_vec.SetPtEtaPhi(jpt, jeta, jphi);
               if(fabs(jeta)>3.0) continue;
               if(jpt>leadingJetPt) continue ;
                if(TMath::Abs(jet2_vec.DeltaPhi(jet1_vec))<dphicut) continue ;
             //  float dphi = jphi-leadingJetPhi ;
      // if(TMath::Abs(dphi)>TMath::Pi()) std::cerr <<"dijets :" << "pt =" <<leadingJetPt <<" dphi =" <<dphi << endl ;
           //    if(TMath::Abs(dphi)>TMath::Pi()) dphi-=2*TMath::Pi();
           //    if(TMath::Abs(dphi)<0.5*TMath::Pi()) continue ;
               if(jpt > subleadingJetPt) {
                   subleadingJetPt = jpt;
                   subleadingJetPhi = jphi;
                   subleadingJetEta = jeta;
                   subleadingIndex = j ;
               }
          } //! end of subleading search

      if(subleadingIndex >=0 && leadingIndex >= 0. && leadingJetPt>=subleadingJetPt && subleadingJetPt >subleadjetcut){
        double dijeteta = (subleadingJetEta+leadingJetEta)/2. ;
        double dijetM = TMath::Sqrt(2*leadingJetPt*subleadingJetPt*(TMath::CosH(leadingJetEta-subleadingJetEta)-TMath::Cos(leadingJetPhi-subleadingJetPhi)));
        jet2_vec.SetPtEtaPhi(subleadingJetPt, subleadingJetEta, subleadingJetPhi);
        Int_t jjEtaBin = -1 ;
       //  std::cerr <<"find dijets :" << "pt =" <<leadingJetPt <<" subpt =" <<subleadingJetPt << endl ;
       hDijetPtRatio->Fill(leadingJetPt, subleadingJetPt/leadingJetPt, w*stree.fCrossx/nevt);
       hDijetPtDphi->Fill(leadingJetPt, TMath::Abs(jet2_vec.DeltaPhi(jet1_vec)), w*stree.fCrossx/nevt);
         hDijetPtDeta->Fill(leadingJetPt, subleadingJetEta-leadingJetEta, w*stree.fCrossx/nevt);
    //  if(leadingJetPt>120. && subleadingJetPt>30. && TMath::Abs(subleadingJetPhi-leadingJetPhi)>2*TMath::Pi()/3.) 
        hDijetEta->Fill(leadingJetEta, subleadingJetEta, w*stree.fCrossx/nevt);
       hDijetEtaSum->Fill(leadingJetEta, (subleadingJetEta+leadingJetEta)/2., w*stree.fCrossx/nevt);
     //  if(leadingJetPt>120. && subleadingJetPt>30. && TMath::Abs(subleadingJetPhi-leadingJetPhi)>2*TMath::Pi()/3.)
        hEtaDijetPartonX->Fill(x2, (subleadingJetEta+leadingJetEta)/2., w*stree.fCrossx/nevt);
     //  if(leadingJetPt>120. && subleadingJetPt>30. && TMath::Abs(subleadingJetPhi-leadingJetPhi)>2*TMath::Pi()/3.)
        hDijetPartonXQ2->Fill(x2, pthat*pthat, w*stree.fCrossx/nevt);
         if(fabs(dijeteta)<1.0)hJetMassM1P1PartonX->Fill(dijetM, x2, w*stree.fCrossx/nevt);
          if(fabs(dijeteta)<1.0)hJetMassM1P1->Fill(dijetM, w*stree.fCrossx/nevt);
         for(int ieta = 0 ; ieta < netabin ; ieta++){
          if(dijeteta >= deta[ieta] && dijeteta <deta[ieta+1]) jjEtaBin = ieta ;
          }
         if(jjEtaBin!=-1)  hJetMassEtaBinPartonX[jjEtaBin]->Fill( dijetM, x2, w*stree.fCrossx/nevt);
         if(jjEtaBin!=-1)  hJetMassEtaBin[jjEtaBin]->Fill(dijetM, w*stree.fCrossx/nevt);
     }

      // 1. All Charged Tracks ----------------------------------------
      Int_t trkEtaBin = -1 ;
      for (int l=0; l<alltrk->GetEntriesFast(); l++) {
	GenParticleInfo *AllParticles = (GenParticleInfo*)alltrk->At(l);
	
	float alltrkpt  = AllParticles->fPt;
	float alltrketa = AllParticles->fEta;
	float alltrkphi = AllParticles->fPhi;
	int charge = AllParticles->iCharge;
	int status = AllParticles->iStatus;


	if(fabs(alltrketa)>2.4) continue ;
        if(status!=1) continue ;
      if(charge==0){ 
	if(fabs(alltrketa)<1.0)hNeutralPtM1P1->Fill(alltrkpt, w*stree.fCrossx/nevt);
      }
     else{ 
	hAllTrkdPt->Fill(alltrkpt, w*stree.fCrossx/nevt);
	if(charge>0)hPosTrkdPt->Fill(alltrkpt, w*stree.fCrossx/nevt);
	else hNegTrkdPt->Fill(alltrkpt, w*stree.fCrossx/nevt);
	//         std::cerr<<"------------------" << std::endl;
	//         std::cerr<<" phi: " << alltrkphi << std::endl;
	//         std::cerr<<" eta: " << alltrketa << std::endl;
	//         std::cerr<<" pt : " << alltrkpt << std::endl;

	// HIST FILLING
	//	 if(fabs(alltrketa)>1.0) continue; // eta cut
	
	
	hTrkPtPartonX->Fill(alltrkpt, x2, w*stree.fCrossx/nevt);
	hTrkEtaPartonX->Fill(x2, alltrketa, w*stree.fCrossx/nevt);
        if(alltrkpt>1 && alltrkpt<=4) hPartonXQ2Pt1to4->Fill(x2, pthat*pthat, (stree.fCrossx/nevt));
        if(alltrkpt>4 && alltrkpt<=10) hPartonXQ2Pt4to10->Fill(x2, pthat*pthat, (stree.fCrossx/nevt));
        if(alltrkpt>10) hPartonXQ2PtAbove10->Fill(x2, pthat*pthat, (stree.fCrossx/nevt));
	if(fabs(alltrketa)<1.0)hTrkPtM1P1PartonX->Fill(alltrkpt, x2, w*stree.fCrossx/nevt);
	if(fabs(alltrketa)<1.0)hTrkPtM1P1Q2->Fill(alltrkpt,pthat*pthat, w*(stree.fCrossx/nevt));
	if(fabs(alltrketa)<1.0)hTrkPtM1P1->Fill(alltrkpt, w*stree.fCrossx/nevt);
	    
	for(int ieta = 0 ; ieta < netabin ; ieta++){
	  if(alltrketa >= dtrketa[ieta] && alltrketa <dtrketa[ieta+1]) trkEtaBin = ieta ;
	}
	    if(trkEtaBin!=-1)  hTrkPtEtaBinPartonX[trkEtaBin]->Fill(alltrkpt, x2, w*stree.fCrossx/nevt);
	    if(trkEtaBin!=-1)  hTrkPtEtaBinQ2[trkEtaBin]->Fill(alltrkpt,pthat*pthat, w*(stree.fCrossx/nevt));
	    if(trkEtaBin!=-1)  hTrkPtEtaBin[trkEtaBin]->Fill(alltrkpt, w*stree.fCrossx/nevt);
	    
        }
      }
      
      if(stree.isMinPtHat==1) dNevtMinPtHat->Fill(1.1);
      totN++;

    //! for jet associated track analysis
      jet_vec.SetPtEtaPhi(0, 0, 0);
      trk_vec.SetPtEtaPhi(0, 0, 0);
      for (int j=0; j<stree.nJets; j++) {

        float jpt  = stree.fJPt[j];
        float jeta = stree.fJEta[j];
        float jphi = stree.fJPhi[j];

         if(jpt<30.) continue ;
       if(TMath::Abs(jeta)<3){
            jet_vec.SetPtEtaPhi(jpt, jeta, jphi);
     //    for (int l=0; l<AssParticles_test->GetEntriesFast(); l++) {
         for (int l=0; l<alltrk->GetEntriesFast(); l++) {
       //    GenParticleInfo *particle = (GenParticleInfo*)AssParticles_test->At(l);
           GenParticleInfo *particle = (GenParticleInfo*)alltrk->At(l);

           float asstrkpt  = particle->fPt;
           float asstrketa = particle->fEta;
           float asstrkphi = particle->fPhi;
           int charge = particle->iCharge;
           int status = particle->iStatus;
           if(status!=1) continue ;
           if(charge==0) continue ;
           if(fabs(asstrketa)>2.4) continue ;
            trk_vec.SetPtEtaPhi(asstrkpt, asstrketa, asstrkphi);
          // cout <<"trk pt =" <<asstrkpt <<" delta r =" << jet_vec.DeltaR(trk_vec)<< endl ; 
             if(jet_vec.DeltaR(trk_vec)<conesize){
                hJetTrkPtM1P1->Fill(asstrkpt, w*stree.fCrossx/nevt);         
             } //jet-track cone size requirement 
          }  //track look
      } //jet eta cut
     } //jet loop
   } // end of all entries


   cout<<"Number of events = "<<totN<<endl;

   // Save histograms in a root file
   if(save){
/*   normalizeByBinWidth(hAllTrkdPt);
   normalizeByBinWidth(hPosTrkdPt);
   normalizeByBinWidth(hNegTrkdPt);
   normalizeByBinWidth(hTrkPtM1P1);
   for(int ieta = 0 ; ieta <netabin ; ieta++){
     normalizeByBinWidth(hTrkPtEtaBin[ieta]);
   }
*/
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
 //  for(djpt = 0.; djpt < 500-small; djpt += 10.) jptBins.push_back(djpt);
 //   jptBins.push_back(500.);
 /*  for(djpt = 0.; djpt < 100-small; djpt += 2.) jptBins.push_back(djpt);
   for(djpt = 100.; djpt < 200-small; djpt += 4.) jptBins.push_back(djpt);
   for(djpt = 200.; djpt < 400-small; djpt += 8.) jptBins.push_back(djpt);
   for(djpt = 400.; djpt < 800-small; djpt += 16.) jptBins.push_back(djpt);
   for(djpt = 800.; djpt < 1600-small; djpt += 32.) jptBins.push_back(djpt);
   jptBins.push_back(1600.);

  const  Double_t jetPtBin[]={3, 4, 5, 7, 9, 12, 15, 18, 22, 27, 33, 39, 47, 55, 64,74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 429, 692, 1000};
  const int nJetPtBin = sizeof(jetPtBin)/sizeof(Double_t)-1 ; 
  jptBins.size() = nJetPtBin +1 ;
*/
   for(djpt = 3.; djpt < 5-small; djpt += 1.) jptBins.push_back(djpt);
   for(djpt = 5.; djpt < 9-small; djpt += 2.) jptBins.push_back(djpt);
   for(djpt = 9.; djpt < 24-small; djpt += 3.) jptBins.push_back(djpt);
   for(djpt = 24.; djpt < 32-small; djpt += 4.) jptBins.push_back(djpt);
   for(djpt = 32.; djpt < 37-small; djpt += 5.) jptBins.push_back(djpt);
   for(djpt = 37.; djpt < 49-small; djpt += 6.) jptBins.push_back(djpt);
   for(djpt = 49.; djpt < 56-small; djpt += 7.) jptBins.push_back(djpt);
   for(djpt = 56.; djpt < 64-small; djpt += 8.) jptBins.push_back(djpt);
   for(djpt = 64.; djpt < 84-small; djpt += 10.) jptBins.push_back(djpt);
   for(djpt = 84.; djpt < 97-small; djpt += 13.) jptBins.push_back(djpt);
   for(djpt = 97.; djpt < 114-small; djpt += 17.) jptBins.push_back(djpt);
   for(djpt = 114.; djpt < 133-small; djpt += 19.) jptBins.push_back(djpt);
   for(djpt = 133.; djpt < 153-small; djpt += 20.) jptBins.push_back(djpt);
   for(djpt = 153.; djpt < 174-small; djpt += 21.) jptBins.push_back(djpt);
   for(djpt = 174.; djpt < 196-small; djpt += 22.) jptBins.push_back(djpt);
   for(djpt = 196.; djpt < 220-small; djpt += 24.) jptBins.push_back(djpt);
   for(djpt = 220.; djpt < 245-small; djpt += 25.) jptBins.push_back(djpt);
   for(djpt = 245.; djpt < 272-small; djpt += 27.) jptBins.push_back(djpt);
   for(djpt = 272.; djpt < 300-small; djpt += 28.) jptBins.push_back(djpt);
   for(djpt = 300.; djpt < 330-small; djpt += 30.) jptBins.push_back(djpt);
   for(djpt = 330.; djpt < 362-small; djpt += 32.) jptBins.push_back(djpt);
   for(djpt = 362.; djpt < 395-small; djpt += 33.) jptBins.push_back(djpt);
   for(djpt = 395.; djpt < 430-small; djpt += 35.) jptBins.push_back(djpt);
   for(djpt = 430.; djpt < 468-small; djpt += 38.) jptBins.push_back(djpt);
   for(djpt = 468.; djpt < 509-small; djpt += 39.) jptBins.push_back(djpt);
   for(djpt = 507.; djpt < 548-small; djpt += 41.) jptBins.push_back(djpt);
   for(djpt = 548.; djpt < 592-small; djpt += 44.) jptBins.push_back(djpt);
   for(djpt = 592.; djpt < 638-small; djpt += 46.) jptBins.push_back(djpt);
   for(djpt = 638.; djpt < 686-small; djpt += 48.) jptBins.push_back(djpt);
   for(djpt = 686.; djpt < 1000-small; djpt += 314.) jptBins.push_back(djpt);
   jptBins.push_back(1000.);

 // Q2 bins
   double q2;
   for(q2 = 1.; q2 < 10-small; q2 += 1.) q2Bins.push_back(q2);
   for(q2 = 10.; q2 < 100-small; q2 += 10.) q2Bins.push_back(q2);
   for(q2 = 100.; q2 < 1000-small; q2 += 100.) q2Bins.push_back(q2);
   for(q2 = 1000.; q2 < 10000-small; q2 += 1000.) q2Bins.push_back(q2);
   for(q2 = 10000.; q2 < 100000-small; q2 += 10000.) q2Bins.push_back(q2);
   for(q2 = 100000.; q2 < 1000000-small; q2 += 100000.) q2Bins.push_back(q2);
   q2Bins.push_back(1.e6);

 // partonx bins
   double partonx;
   for(partonx = 1.e-4; partonx < 1.e-3-small; partonx += 1.e-4) xBins.push_back(partonx);
   for(partonx = 1.e-3; partonx < 0.01-small; partonx += 1.e-3) xBins.push_back(partonx);
   for(partonx = 0.01; partonx < 0.1-small; partonx += 0.01) xBins.push_back(partonx);
   for(partonx = 0.1; partonx < 1-small; partonx += 0.1) xBins.push_back(partonx);
   xBins.push_back(1.1);

   // 1D      
   dPtHat = new TH1F("dPtHat","#hat{q} with no weight", ptHatBins.size()-1, &ptHatBins[0]);   
   dNevtMinPtHat = new TH1F("dNevtMinPtHat","Number of processed events in the min pt_hat sample",10,0.0,10.0); 
   dNJetdPt = new TH1F("dNJetdPt","Jet pt",jptBins.size()-1, &jptBins[0]);
    hAllJetdPt = new TH1F("hAllJetdPt","Inclusive Jet pt",jptBins.size()-1, &jptBins[0]);
    hAllTrkdPt = new TH1F("hAllTrkdPt","Inclusive Track pt",NumOfPtBins_part-1, &ptBins_adjusted[0]);
    hPosTrkdPt = new TH1F("hPosTrkdPt","Postive charge Track pt",NumOfPtBins_part-1, &ptBins_adjusted[0]);
    hNegTrkdPt = new TH1F("hNegTrkdPt","Negative charge Track pt",NumOfPtBins_part-1, &ptBins_adjusted[0]);
    hJetPtM1P1 = new TH1F("hJetPtEtaM1P1","Jet pt in |#eta|<1",jptBins.size()-1, &jptBins[0]);
    hTrkPtM1P1 = new TH1F("hTrkPtEtaM1P1","Track pt in |#eta|<1",NumOfPtBins_part-1, &ptBins_adjusted[0]);
    hNeutralPtM1P1 = new TH1F("hNeutralPtEtaM1P1","Neutral pt in |#eta|<1",NumOfPtBins_part-1, &ptBins_adjusted[0]);
    hJetTrkPtM1P1 = new TH1F("hJetTrkPtEtaM1P1","JetTrack pt in |#eta|<1",NumOfPtBins_part-1, &ptBins_adjusted[0]);

   // 2D
   hPartonX1X2 = new TProfile("hPartonX1X2","PartonX1X2",xBins.size()-1, &xBins[0], 0., 1.) ; //xBins.size()-1, &xBins[0]);
   hPartonXQ2 = new TProfile("hPartonXQ2","PartonXQ2",xBins.size()-1, &xBins[0], 1., 1.e5);
   hPartonXQ2Pt1to4 = new TProfile("hPartonXQ2Pt1to4","PartonXQ2Pt1to4",xBins.size()-1, &xBins[0], 1., 1.e5);
   hPartonXQ2Pt4to10 = new TProfile("hPartonXQ2Pt4to10","PartonXQ2Pt4to10",xBins.size()-1, &xBins[0], 1., 1.e5);
   hPartonXQ2PtAbove10 = new TProfile("hPartonXQ2PtAbove10","PartonXQ2PtAbove10",xBins.size()-1, &xBins[0], 1., 1.e5);
   hJetPtPartonX = new TProfile("hJetPtPartonX","Jet pt vs Partonx",jptBins.size()-1, &jptBins[0]); //xBins.size()-1, &xBins[0], 10., 1000.) ; //jptBins.size()-1, &jptBins[0]);
   hJetPtM1P1PartonX = new TProfile("hJetPtPartonXEtaM1P1","Jet pt vs Partonx in |#eta|<1",jptBins.size()-1, &jptBins[0]);; //xBins.size()-1, &xBins[0], 10., 1000.) ; //jptBins.size()-1, &jptBins[0]);
   hJetEtaPartonX = new TProfile("hJetEtaPartonX","Jet eta vs Partonx",xBins.size()-1, &xBins[0]) ; //, 100, -5., 5.);
   hTrkPtPartonX = new TProfile("hTrkPtPartonX","Track pt vs Partonx",NumOfPtBins_part-1, &ptBins_adjusted[0]); //xBins.size()-1, &xBins[0]); //,50,2,100);
   hTrkPtM1P1PartonX = new TProfile("hTrkPtPartonXEtaM1P1","Track pt vs Partonx in |#eta|<1",NumOfPtBins_part-1, &ptBins_adjusted[0]); //xBins.size()-1, &xBins[0]); //,50,2,100);
   hTrkPtM1P1Q2 = new TProfile("hTrkPtQ2EtaM1P1","Track pt vs Q2 in |#eta|<1",NumOfPtBins_part-1, &ptBins_adjusted[0], 1., 1.e5);
   hJetPtM1P1Q2 = new TProfile("hJetPtQ2EtaM1P1","Jet pt vs Q2 in |#eta|<1",jptBins.size()-1, &jptBins[0], 1., 1.e5);
   //   hTrkPtM1P1PartonX = new TH2F("hTrkPtPartonXEtaM1P1","Track pt vs Partonx in |#eta|<1",5000, 1.e-5, 1.1, ptBins.size()-1, &ptBins[0]);
   // hTrkPtM1P1PartonX = new TH2F("hTrkPtPartonXEtaM1P1","Track pt vs Partonx in |#eta|<1",5000, 1.e-5, 1.1, 50,2,100);
   hTrkEtaPartonX = new TProfile("hTrkEtaPartonX","Track eta vs Partonx",xBins.size()-1, &xBins[0]); //, 100, -5., 5.);

 //dijet histograms
 //  hLeadingJetPtPartonX = new TH2F("hLeadingJetPtPartonX","Leading Jet pt vs Partonx",5000, 1.e-5, 1.1, jptBins.size()-1, &jptBins[0]);
   hLeadingJetPtPartonX = new TProfile("hLeadingJetPtPartonX","Leading Jet pt vs Partonx",jptBins.size()-1, &jptBins[0]); //xBins.size()-1, &xBins[0]); //, jptBins.size()-1, &jptBins[0]);
   hDijetPtRatio = new TH2F("hDijetPtRatio","dijet pt ratio vs leading jet pt",jptBins.size()-1, &jptBins[0], 100, 0., 1.);
   hDijetPtDphi = new TH2F("hDijetPtDphi","dijet dphi vs leading jet pt",jptBins.size()-1, &jptBins[0], dphiBins.size()-1, &dphiBins[0]);
   hDijetPtDeta = new TH2F("hDijetPtDeta","dijet deta vs leading jet pt",jptBins.size()-1, &jptBins[0], 500, -5., 5.);
   hDijetEta = new TH2F("hDijetEta","subleading jet eta vs leading jet eta",500, -5., 5., 500, -5., 5.);
   hDijetEtaSum = new TH2F("hDijetEtaSum","dijet eta vs leading jet eta",500, -5., 5., 500, -5., 5.);
   hEtaDijetPartonX = new TProfile("hEtaDijetPartonx","dijet #eta vs parton x",xBins.size()-1, &xBins[0]); //, 100, -5., 5.);
   hDijetPartonXQ2 = new TProfile("hDijetPartonxQ2","dijet Q^{2} vs parton x",xBins.size()-1, &xBins[0]); //, q2Bins.size()-1, &q2Bins[0]);
    hJetMassM1P1 = new TH1F("hJetMassEtaM1P1","Jet Mass in |#eta|<1",jptBins.size()-1, &jptBins[0]);
   hJetMassM1P1PartonX = new TProfile("hJetMassPartonXEtaM1P1","DiJet Mass vs Partonx in |#eta|<1", jptBins.size()-1, &jptBins[0]); //xBins.size()-1, &xBins[0], 10., 1000. ) ; //jptBins.size()-1, &jptBins[0]);
 
  for(int ieta = 0 ; ieta <netabin ; ieta++){
      hJetPtEtaBinPartonX[ieta] = new TProfile(Form("hJetPtPartonXEtaBin%.f_%.f", deta[ieta]*10, deta[ieta+1]*10),Form("hJetPtPartonXEtaBin%.f_%.f", deta[ieta]*10, deta[ieta+1]*10),jptBins.size()-1, &jptBins[0]); //xBins.size()-1, &xBins[0], 10., 1000. ) ; //jptBins.size()-1, &jptBins[0]);
      hJetPtEtaBin[ieta] = new TH1F(Form("hJetPtEtaBin%.f_%.f", deta[ieta]*10, deta[ieta+1]*10),Form("hJetPtEtaBin%.f_%.f", deta[ieta]*10, deta[ieta+1]*10),jptBins.size()-1, &jptBins[0]);
      hJetMassEtaBin[ieta] = new TH1F(Form("hJetMassEtaBin%.f_%.f", deta[ieta]*10, deta[ieta+1]*10),Form("hJetMassEtaBin%.f_%.f", deta[ieta]*10, deta[ieta+1]*10),jptBins.size()-1, &jptBins[0]);
      hJetMassEtaBinPartonX[ieta] = new TProfile(Form("hJetMassPartonXEtaBin%.f_%.f", deta[ieta]*10, deta[ieta+1]*10),Form("hJetMassPartonXEtaBin%.f_%.f", deta[ieta]*10, deta[ieta+1]*10),jptBins.size()-1, &jptBins[0]); //xBins.size()-1, &xBins[0], 10., 1000.) ; //5000, 1.e-5, 1.1, jptBins.size()-1, &jptBins[0]);
      hTrkPtEtaBinPartonX[ieta] = new TProfile(Form("hTrkPtPartonXEtaBin%.f_%.f", dtrketa[ieta]*10, dtrketa[ieta+1]*10),Form("hTrkPtPartonXEtaBin%.f_%.f", dtrketa[ieta]*10, dtrketa[ieta+1]*10),NumOfPtBins_part-1, &ptBins_adjusted[0]) ; //xBins.size()-1, &xBins[0],0., 500.); // 5000, 1.e-5, 1.1, ptBins.size()-1, &ptBins[0]);
      hTrkPtEtaBinQ2[ieta] = new TProfile(Form("hTrkPtQ2EtaBin%.f_%.f", dtrketa[ieta]*10, dtrketa[ieta+1]*10),Form("hTrkPtQ2EtaBin%.f_%.f", dtrketa[ieta]*10, dtrketa[ieta+1]*10),NumOfPtBins_part-1, &ptBins_adjusted[0], 1., 1.e5);
	    // hTrkPtEtaBinPartonX[ieta] = new TH2F(Form("hTrkPtPartonXEtaBin%.f_%.f", dtrketa[ieta]*10, dtrketa[ieta+1]*10),Form("hTrkPtPartonXEtaBin%.f_%.f", dtrketa[ieta]*10, dtrketa[ieta+1]*10),5000, 1.e-5, 1.1, 50,2,100);
      
      hTrkPtEtaBin[ieta] = new TH1F(Form("hTrkPtEtaBin%.f_%.f", dtrketa[ieta]*10, dtrketa[ieta+1]*10),Form("hTrkPtEtaBin%.f_%.f", dtrketa[ieta]*10, dtrketa[ieta+1]*10),NumOfPtBins_part-1, &ptBins_adjusted[0]);
      //      hTrkPtEtaBin[ieta] = new TH1F(Form("hTrkPtEtaBin%.f_%.f", dtrketa[ieta]*10, dtrketa[ieta+1]*10),Form("hTrkPtEtaBin%.f_%.f", dtrketa[ieta]*10, dtrketa[ieta+1]*10),ptBins.size()-1, &ptBins[0]);
      //hTrkPtEtaBin[ieta] = new TH1F(Form("hTrkPtEtaBin%.f_%.f", dtrketa[ieta]*10, dtrketa[ieta+1]*10),Form("hTrkPtEtaBin%.f_%.f", dtrketa[ieta]*10, dtrketa[ieta+1]*10),50,2,100);
  }


}


void saveHistRoot(){
/*normalizeByBinWidth()
normalizeByBinWidth()
normalizeByBinWidth()
normalizeByBinWidth()
normalizeByBinWidth()
   dPtHat->Scale(cs/nevt);
   dNevtMinPtHat->Scale(cs/nevt);
   dNJetdPt->Scale(cs/nevt);
   hAllJetdPt->Scale(cs/nevt);
   hPartonX1X2->Scale(cs/nevt);
   hJetPtPartonX->Scale(cs/nevt);
   hJetPtM1P1PartonX->Scale(cs/nevt);
   hJetEtaPartonX->Scale(cs/nevt);
   hTrkPtPartonX->Scale(cs/nevt);
   hTrkPtM1P1PartonX->Scale(cs/nevt);
   hTrkEtaPartonX->Scale(cs/nevt);
   for(int ieta = 0 ; ieta <netabin ; ieta++){
   hJetPtEtaBin[ieta]->Scale(cs/nevt);
   hTrkPtEtaBin[ieta]->Scale(cs/nevt);
   hJetPtEtaBinPartonX[ieta]->Scale(cs/nevt);
   hTrkPtEtaBinPartonX[ieta]->Scale(cs/nevt);
  }
   dNAllTrkdPtdPtHat->Scale(cs/nevt);
   dNAllTrkdPtdPtHat_eta0308->Scale(cs/nevt);
   dNAllTrkdPtdPtHat_eta0813->Scale(cs/nevt);
   dNAllTrkdPtdPtHat_eta1318->Scale(cs/nevt);
   dNAllTrkdPtdPtHat_ForCorrelation->Scale(cs/nevt);
   dNAllTrkdPtdPtHat_adjustedBinning->Scale(cs/nevt);
   dNAllTrkdPtdPhi->Scale(cs/nevt);
*/
   dPtHat->Write();
   dNevtMinPtHat->Write();
   dNJetdPt->Write();
   hAllJetdPt->Write();



   hAllTrkdPt->Write();
   hPosTrkdPt->Write();
   hNegTrkdPt->Write();
   hJetPtM1P1->Write();
   hTrkPtM1P1->Write();
   hNeutralPtM1P1->Write();
   hJetTrkPtM1P1->Write();
 
   hPartonX1X2->Write();
   hPartonXQ2->Write();
   hPartonXQ2Pt1to4->Write();
   hPartonXQ2Pt4to10->Write();
   hPartonXQ2PtAbove10->Write();
   hJetPtPartonX->Write();
   hJetPtM1P1PartonX->Write();
   hJetEtaPartonX->Write();
   hTrkPtPartonX->Write();
   hTrkPtM1P1PartonX->Write();
   hTrkPtM1P1Q2->Write();
   hJetPtM1P1Q2->Write();
   hTrkEtaPartonX->Write();

  //dijets histograms
   hLeadingJetPtPartonX->Write();
   hDijetPtRatio->Write();
   hDijetPtDphi->Write();
   hDijetPtDeta->Write();
   hDijetEta->Write();
   hDijetEtaSum->Write();
   hEtaDijetPartonX->Write();
   hDijetPartonXQ2->Write();
   hJetMassM1P1->Write();
   hJetMassM1P1PartonX->Write();

   for(int ieta = 0 ; ieta <netabin ; ieta++){
     //   normalizeByBinWidth(hTrkPtEtaBin[ieta]);
     hJetPtEtaBin[ieta]->Write();
     hTrkPtEtaBin[ieta]->Write();
     hJetPtEtaBinPartonX[ieta]->Write();
     hTrkPtEtaBinPartonX[ieta]->Write();
     hJetMassEtaBin[ieta]->Write();
     hJetMassEtaBinPartonX[ieta]->Write();
     hTrkPtEtaBinQ2[ieta]->Write();
   }
}

TH1 * normalizeByBinWidth(TH1 *histo) {
    for(int i = 1; i <= histo->GetNbinsX(); i++) {
        float content = histo->GetBinContent(i);
        float error = histo->GetBinError(i);
        histo->SetBinContent(i,content/histo->GetBinWidth(i));
        histo->SetBinError(i,error/histo->GetBinWidth(i));
    }
    return histo ;




}

Double_t func(Double_t *x, Double_t *par){

double y0=par[0];
double xa=par[1];
double ya=par[2];
double xe=par[3];
double ye=par[4];
double b=par[5];

double a0=ya;
double a1 = (y0-ya)/(1-exp(-xa));
double a2 = -1.0/xa*(y0-ya)/(1-exp(-xa));

//double b0 = ya+3.0*xa*xa*(ya-ye)*(xa+xe)/(xa-xe)/(xa-xe)/(xa-xe);
//double b1 = -6.0*xa*xe*(ya-ye)/(xa-xe)/(xa-xe)/(xa-xe);
//double b2 = 3.0*(ya-ye)*(xa+xe)/(xa-xe)/(xa-xe)/(xa-xe);
double b3 = -2.0*(ya-ye)/(xa-xe)/(xa-xe)/(xa-xe);
double b0=ya-1.0/2*b3*xa*xa*(3*xe-xa);
double b1 = 3.0*xa*xe*b3;
double b2 = -3.0/2*b3*(xa+xe);

double c0= 2.0*ye;
double c1 = -ye*(b*xe-xe+1)*pow(1-xe,b-1);
double c2 = -b*ye*pow(1-xe,b-1);

if (x[0]<=xa) return (a0+(a1+a2*x[0])*(exp(-x[0])-exp(-xa)));
else if (x[0]>xa && x[0]<=xe) return (b0+b1*x[0]+b2*x[0]*x[0]+b3*x[0]*x[0]*x[0]);
else return (c0+(c1-c2*x[0])*pow(1-x[0],-b));

}



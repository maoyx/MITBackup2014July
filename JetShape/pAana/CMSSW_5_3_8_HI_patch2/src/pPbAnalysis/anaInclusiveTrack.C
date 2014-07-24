#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TVector3.h"
#include "TMath.h"
#include "TF1.h"
#include <TH1D.h>
#include <TNtuple.h>
#include "TChain.h"
#include <iostream>
#include <TString.h>
#include <TCut.h>
#include "../SmearingFactors.h"
#include "hiForest.h"
#include "commonSetup.h"
#include "../TrackCorrector.C"

using namespace std;

//define the kinematics cuts for the analysis
const double conesize = 0.3 ;
const double deltacone = 0.05 ;

//const double radius = 0.025;

//const int nrbin = 10 ;
//double rbin[nrbin+1]={0.0,0.05,0.10, 0.15, 0.20,0.25,0.30,0.35,0.40,0.45,0.50};

const int nrbin = 6 ;
double rbin[nrbin+1]={0.0,0.05,0.10, 0.15, 0.20,0.25,0.30};

const double etacut = 2.0 ;
//const double dphicut = TMath::TwoPi()/3. ;
const double dphicut = 7*TMath::Pi()/8. ;
const double leadingjetcut = 50. ;
const double trackcut = 1.;
const double tracketacut = 2.4; //make sure the tracks around jet cone inside eta range

////for etalimit = 0.3, to remove the possible overlap region by ER method 
const double etalimit = 0.3 ; 

int pthat ; //= 120 ; //=300 ; //30 and 80 for pp; 30,50,80,120,170,200 for PbPb MC 
int ptmax ; //= 170 ;
TString coll = "PPb";
TString para ="Full" ; //PYQUEN parameters setting: Wide or Full
const bool DoGenAna=kFALSE ; //should be only be true for MC sample

//do tracking corrections
const bool doTrackCorrections = kTRUE; //for tracking efficiency correction
TString corrMet = "Hist" ; //Hist table from Frank, or Para from Krisztian
TrackingParam *trackCorrFromParam;

vector<TrackingCorrections*> trackCorrections;

//for jet pt smearing and reweight
const bool DoSmear = kFALSE ;
const bool DoJetPtWeight = kFALSE ; //!only be true when DoSmear TRUE 

const bool DoSumPtNorm = kFALSE ;
//weight factor from vertex and centrality
double weight =1. ;

TString intputFile ;

//TString dataPath="/Users/ymao/group/CMS/hiForest";
TString dataPath ;

//if it is pp, no centrality bins, only one
const int nbin = 1 ;
const int centr[] ={0,100};
////for HI centrality bin
//const int nbin = 4 ;
//const int centr[] ={0,10,30,50,100};
//const int nbin = 6 ;
//const int centr[] ={0,5, 10, 30,50, 70, 90};

//const double pt[]={100., 120., 140., 160., 200., 300., 500.};
const int nptbin = 1 ;
const double pt[]={50., 500.};
//const int ntrkptbin = 6 ;
//const double trkpt[]={1., 2., 4., 8., 16., 32., 500.};

const int ntrkptbin = 4 ;
const double trkpt[]={1.,4., 16., 64., 500.};

const Double_t jetPtBin[] = {30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,400};
//const Double_t jetPtBin[] = {100, 110, 120, 130, 140, 150, 160, 170, 180, 200, 240, 300};
//const Double_t jetPtBin[] = {100, 110, 120, 130, 140, 150, 160, 180, 200, 240, 300, 500};
const int nJetPtBin = sizeof(jetPtBin)/sizeof(Double_t)-1 ;

//const int nPtBin = 27;
//double TrkBin[nPtBin+1] = {0, 0.5, 1, 1.203915, 1.449412, 1.74497, 2.100796, 2.529181, 3.04492, 3.665826, 4.413344, 5.313293, 6.396755, 7.701152, 9.271536, 11.16214, 13.43828, 16.17855, 19.47761, 23.44939, 28.23108, 33.98783, 40.91848, 49.26238, 59.30774, 71.40151, 85.96137, 103.4902}; 

//const Double_t TrkBin[]={0, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0, 1.05, 1.1, 1.15, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.5, 3.0, 4., 5., 6., 8.,10.,12.,15.,20.,25.,30.,45.,60.,80.,100., 120.,150., 180.,300.,500.};
//const Double_t TrkBin[]={0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 3.2, 4.0, 4.8, 5.6, 6.4, 7.2, 9.6, 12.0, 14.4, 19.2, 24.0, 28.8, 35.2, 41.6, 48.0, 60.8, 73.6, 86.4, 103.6, 120.8, 138., 155.2, 172.4, 189.6, 206.8};
const Double_t TrkBin[]={0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6, 130}; 
const int nPtBin = sizeof(TrkBin)/sizeof(Double_t)-1 ;

//const int netabin = 10 ;
//const double deta[]={-2.5, -2.0, -1.5, -1.0, -0.5, 0.0,0.5,1.0,1.5,2.0, 2.5} ;
const int netabin = 7 ;
const double deta[]={-1.8, -1.3, -0.8, -0.3, 0.3, 0.8,1.3,1.8} ;

const int ntrketabin = 7 ;
const double dtrketa[]={-1.8, -1.3, -0.8, -0.3, 0.3, 0.8,1.3,1.8} ;

class hist_class {
public:
    hist_class(TString the_desc);
    void Delete();
    void Write();
    
    TString desc;
    bool IsMC ;
    
    TH1F * Ntrack[nbin];
    TH1D * NEvents[nbin];
    TH1D * NevtCounter[nbin];

    TH1F * jetpt[nbin];    
    TH2F * trackpt[nbin];
    TH1F * trackrawpt[nbin];
    TH2F * trackphi[nbin];
    TH2F * tracketa[nbin];
    TH2F * trackpteff[nbin];
    

    TH1D * CenBin;
    TH1D * CenBinWt;
    TH1F * Vertex ;
    TH1F * VertexWt ;

    //For inclusive track analysis, outside jet loop
    TH1F * inctrkpt[nbin];
    TH1F * inctrkptM1P1[nbin];
    TH1F * incgenpartpt[nbin];
    TH1F * incgenmatchpt[nbin];



    TH2F * trackPtEtaBin[nbin][netabin]; //jet FF hist. in eta bins
    TH1F * inctrkptEtaBin[nbin][ntrketabin];
    TH1F * NtrkEtaBin[nbin][ntrketabin];
    TH1F * jetptEtaBin[nbin][netabin];
    TH1F * NjetsEtaBin[nbin][netabin];

    TH2F * genpartpt[nbin] ;
    TH2F * genpartphi[nbin] ;
    TH2F * genparteta[nbin] ;
    TH2F * bkgpartpt[nbin];
    


    
};

hist_class::hist_class(TString the_desc)
{
    
    desc = the_desc;
    IsMC =kFALSE ;
    for(int ibin = 0 ; ibin <nbin; ibin++){
        NEvents[ibin] = new TH1D(Form("Nevents_%d-%d%%",centr[ibin],centr[ibin+1]), Form("Nevents_%d-%d%%",centr[ibin],centr[ibin+1]), 100, 0, 2.);
        NEvents[ibin]->Sumw2();
        NevtCounter[ibin] = new TH1D(Form("NeventsCounter_%d-%d%%",centr[ibin],centr[ibin+1]), Form("NeventsCounter_%d-%d%%",centr[ibin],centr[ibin+1]), 1, 0, 1);
        NevtCounter[ibin]->Sumw2();
        Ntrack[ibin] = new TH1F(Form("Ntracks_%d-%d%%",centr[ibin],centr[ibin+1]), Form("Ntracks_%d-%d%%",centr[ibin],centr[ibin+1]), 800, -1., 799);
        jetpt[ibin] = new TH1F(Form("jetpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jetpt_%d-%d%%",centr[ibin],centr[ibin+1]), 50, 0., 500.);
       jetpt[ibin]->Sumw2();
     //   trackpt[ibin] = new TH2F(Form("trackpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("trackpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 200, 0., 200); 
        trackpt[ibin] = new TH2F(Form("trackpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("trackpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, nPtBin, TrkBin); 
        trackpt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        trackpt[ibin]->GetYaxis()->SetTitle("p_{T}^{trk} (GeV/c)");   
        trackpt[ibin]->Sumw2();
        trackrawpt[ibin] = new TH1F(Form("trackrawpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("trackrawpt_%d-%d%%",centr[ibin],centr[ibin+1]), nPtBin, TrkBin);
        trackrawpt[ibin]->GetXaxis()->SetTitle("p_{T}^{trkRAW} (GeV/c)");
        trackrawpt[ibin]->Sumw2();
        trackphi[ibin] = new TH2F(Form("trackphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("trackphi_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, -5.05, 4.95); 
        trackphi[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        trackphi[ibin]->GetYaxis()->SetTitle("#phi^{trk}");   
        trackphi[ibin]->Sumw2();
        tracketa[ibin] = new TH2F(Form("tracketa_%d-%d%%",centr[ibin],centr[ibin+1]), Form("tracketa_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, -5.05, 4.95); 
        tracketa[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        tracketa[ibin]->GetYaxis()->SetTitle("#eta^{trk}");   
        tracketa[ibin]->Sumw2();

        for(Int_t ieta = 0 ; ieta < netabin ; ieta++){
        jetptEtaBin[ibin][ieta] = new TH1F(Form("jetptEtaBin%.f_%.f_Cen%d-%d%%",deta[ieta]*10,deta[ieta+1]*10, centr[ibin],centr[ibin+1]), Form("jetptEtaBin%.f_%.f_Cen%d-%d%%",deta[ieta]*10,deta[ieta+1]*10, centr[ibin],centr[ibin+1]), 50, 0., 500.);
   //   else   jetpt[ibin] = new TH1F(Form("jetpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jetpt_%d-%d%%",centr[ibin],centr[ibin+1]), nJetPtBin, jetPtBin);
        jetptEtaBin[ibin][ieta]->Sumw2();

        NjetsEtaBin[ibin][ieta] = new TH1F(Form("NjetsEtaBin%.f_%.f_Cen%d-%d%%",deta[ieta]*10,deta[ieta+1]*10, centr[ibin],centr[ibin+1]), Form("NjetsEtaBin%.f_%.f_Cen%d-%d%%",deta[ieta]*10,deta[ieta+1]*10, centr[ibin],centr[ibin+1]), 800, -1., 799);
       NjetsEtaBin[ibin][ieta]->Sumw2();

        trackPtEtaBin[ibin][ieta] = new TH2F(Form("trackptInJetEta%.f_%.f_Cen%d-%d%%",  deta[ieta]*10,deta[ieta+1]*10, centr[ibin],centr[ibin+1]), Form("trackptInJetEta%.f_%.f_Cen%d-%d%%",deta[ieta]*10,deta[ieta+1]*10, centr[ibin],centr[ibin+1]), 500, 0., 500, nPtBin, TrkBin);
        trackPtEtaBin[ibin][ieta]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        trackPtEtaBin[ibin][ieta]->GetYaxis()->SetTitle("p_{T}^{trk} (GeV/c)");
        trackPtEtaBin[ibin][ieta]->Sumw2();
        }

        trackpteff[ibin] = new TH2F(Form("jettrackpteff_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jettrackpteff_%d-%d%%",centr[ibin],centr[ibin+1]), nPtBin, TrkBin, 200, 0., 2.);
        trackpteff[ibin]->GetXaxis()->SetTitle("p_{T}^{trk} (GeV/c)");
        trackpteff[ibin]->Sumw2();


        //for inclusive track histgram
        inctrkpt[ibin] = new TH1F(Form("inclusivetrackpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("inclusivetrackpt_%d-%d%%",centr[ibin],centr[ibin+1]), nPtBin, TrkBin);
        inctrkpt[ibin]->GetXaxis()->SetTitle("p_{T}^{trk} (GeV/c)");
        inctrkpt[ibin]->Sumw2();
        inctrkptM1P1[ibin] = new TH1F(Form("inclusivetrackptInEtaM1P1_%d-%d%%",centr[ibin],centr[ibin+1]), Form("inclusivetrackptM1P1_%d-%d%%",centr[ibin],centr[ibin+1]), nPtBin, TrkBin);
        inctrkptM1P1[ibin]->GetXaxis()->SetTitle("p_{T}^{trk} (GeV/c)");
        inctrkptM1P1[ibin]->Sumw2();
         for(Int_t ieta = 0 ; ieta < ntrketabin ; ieta++){
         inctrkptEtaBin[ibin][ieta] = new TH1F(Form("IncTrkEtaBin%.f_%.f_Cen%d-%d%%",dtrketa[ieta]*10,dtrketa[ieta+1]*10, centr[ibin],centr[ibin+1]), Form("IncTrkEtaBin%.f_%.f_Cen%d-%d%%",dtrketa[ieta]*10,dtrketa[ieta+1]*10, centr[ibin],centr[ibin+1]), nPtBin, TrkBin);
        inctrkptEtaBin[ibin][ieta]->GetXaxis()->SetTitle("p_{T}^{trk} (GeV/c)");
        inctrkptEtaBin[ibin][ieta]->Sumw2();
 
        NtrkEtaBin[ibin][ieta] = new TH1F(Form("NtracksEtaBin%.f_%.f_Cen%d-%d%%",dtrketa[ieta]*10,dtrketa[ieta+1]*10, centr[ibin],centr[ibin+1]), Form("NtracksEtaBin%.f_%.f_Cen%d-%d%%",dtrketa[ieta]*10,dtrketa[ieta+1]*10, centr[ibin],centr[ibin+1]), 800, -1., 799);
       NtrkEtaBin[ibin][ieta]->Sumw2();
       }
        if(IsMC){
          if(DoGenAna){
          //  genpartpt[ibin] = new TH2F(Form("genpartpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genpartpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 200, 0., 200);
            genpartpt[ibin] = new TH2F(Form("genpartpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genpartpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500., nPtBin, TrkBin);
            genpartpt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            genpartpt[ibin]->GetYaxis()->SetTitle("p_{T}^{part} (GeV/c)");   
            genpartpt[ibin]->Sumw2();
            genpartphi[ibin] = new TH2F(Form("genpartphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genpartphi_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 100, -5.05, 4.95);
            genpartphi[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            genpartphi[ibin]->GetYaxis()->SetTitle("#phi^{part}");   
            genpartphi[ibin]->Sumw2();
            genparteta[ibin] = new TH2F(Form("genparteta_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genparteta_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 100, -5.05, 4.95);
            genparteta[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            genparteta[ibin]->GetYaxis()->SetTitle("#eta^{part} ");   
            genparteta[ibin]->Sumw2();
          //  bkgpartpt[ibin] = new TH2F(Form("bkgpartpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("bkgpartpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 200, 0., 200); 
          
        //for inclusive track histgram
        incgenpartpt[ibin] = new TH1F(Form("inclusivegenpartpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("inclusivegenpartpt_%d-%d%%",centr[ibin],centr[ibin+1]), nPtBin, TrkBin);
        incgenpartpt[ibin]->GetXaxis()->SetTitle("p_{T}^{gen} (GeV/c)");
        incgenpartpt[ibin]->Sumw2();
        incgenmatchpt[ibin] = new TH1F(Form("inclusivegenmatchpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("inclusivegenmatchpt_%d-%d%%",centr[ibin],centr[ibin+1]), nPtBin, TrkBin);   
       incgenmatchpt[ibin]->GetXaxis()->SetTitle("p_{T}^{gen} (GeV/c)");
        incgenmatchpt[ibin]->Sumw2();

          } //generator level charge particles histogram
        } //MC histogram

        }  //centrality bins loop
        
    //    for(int i = 0 ; i < 6 ; i++){
    //     ptbin[i] = new TH1F(Form("ptbin_%.f-%.f",pt[i], pt[i+1]), Form("ptbin_%.f-%.f",pt[i], pt[i+1]), 500, 0., 500.);
    //    }
    // if(!deltaR)
    CenBin = new TH1D((TString) (desc + "_Cent"), "", 100, 0, 100);
    CenBin->Sumw2();
    CenBinWt = new TH1D((TString) (desc + "_CentWeighted"), "", 100, 0, 100);
    CenBinWt->Sumw2();
    Vertex = new TH1F((TString) (desc + "_Vz"), "", 400, -20., 20.);
    Vertex->Sumw2();
    VertexWt = new TH1F((TString) (desc + "_VzWeighted"), "", 400, -20., 20.);
    VertexWt->Sumw2();
    
}

void hist_class::Delete()
{
    for(int ibin = 0 ; ibin <nbin; ibin++){
        delete NEvents[ibin];
        delete NevtCounter[ibin];
        //        delete TwoTrackTwoJet[ibin];
        //        delete TwoTrackThreeJet[ibin];
        //        delete OneTrackTwoJet[ibin];
        //        delete OneTrackThreeJet[ibin];
        //        delete SumPtFraction[ibin];
        delete Ntrack[ibin];  
        delete jetpt[ibin];
        delete trackpt[ibin];
        delete trackrawpt[ibin];
        delete trackphi[ibin];
        delete tracketa[ibin];
       
        delete inctrkpt[ibin] ; 
        delete inctrkptM1P1[ibin] ; 
        delete trackpteff[ibin];
        for(Int_t ieta = 0 ; ieta < netabin ; ieta++){
        delete trackPtEtaBin[ibin][ieta]; 
        delete jetptEtaBin[ibin][ieta]; 
        delete NjetsEtaBin[ibin][ieta]; 
        }
       
        for(Int_t ieta = 0 ; ieta < ntrketabin ; ieta++)  {
           delete inctrkptEtaBin[ibin][ieta] ;
           delete NtrkEtaBin[ibin][ieta];  
            }
        if(IsMC){
          if(DoGenAna){
            delete genpartpt[ibin];
            delete genpartphi[ibin];
            delete genparteta[ibin];
            delete incgenpartpt[ibin];
            delete incgenmatchpt[ibin];
         }
        }
        
    } //centrality loop
    //   for(int i=0; i<6;i++) delete ptbin[i];
    delete CenBin;
    delete CenBinWt;
    delete Vertex;
    delete VertexWt;

}

void hist_class::Write()
{
    TString out_name ;
    TString dataType ; 
    if(IsMC) dataType="MC" ;
    else dataType="DATA";
    TString met ;
    if(etalimit==etacut) met = "RC";
    else met = "ER";
    TString level ;
    if(DoJetPtWeight) level = "wt";
    else level = "";
    TString Norm ;
    if(DoSumPtNorm)Norm="NormSum";
    else Norm ="NormJet";
   TString anagen ;
    if(DoGenAna) anagen="GenCharge";
    else anagen="";
    if(doTrackCorrections){
          out_name=Form("%s%s_AkPu3PFJet%s2013%sIterTrkCorrtest%.fEtaCut%.fpthat%d_%s",dataType.Data(),coll.Data(),anagen.Data(), corrMet.Data(), trackcut,tracketacut*10, pthat, intputFile.Data());
      }
       else {
          out_name=Form("%s%s_AkPu3PFJet%sTrk%.fEtaCut%.fpthat%d_%s",dataType.Data(),coll.Data(),anagen.Data(),  trackcut,tracketacut*10, pthat, intputFile.Data());
    }
     
       TFile *out_file = new TFile(Form("/net/hidsk0001/d00/scratch/maoyx/JetShape/pAana/CMSSW_5_3_8_HI_patch2/src/pPbAnalysis/%s",out_name.Data()), "RECREATE");
    for(int ibin = 0 ; ibin <nbin; ibin++){
        NEvents[ibin]->Write();
        NevtCounter[ibin]->Write();
        Ntrack[ibin]->Write();
        jetpt[ibin]->Write();
         trackpt[ibin]->Write();
         trackrawpt[ibin]->Write();
        trackphi[ibin]->Write();
        tracketa[ibin]->Write();
        inctrkpt[ibin]->Write();
        inctrkptM1P1[ibin]->Write();
        trackpteff[ibin]->Write();
        for(Int_t ieta = 0 ; ieta < netabin ; ieta++){
         trackPtEtaBin[ibin][ieta]->Write();
         jetptEtaBin[ibin][ieta]->Write();
         NjetsEtaBin[ibin][ieta]->Write();
        }
       for(Int_t ieta = 0 ; ieta < ntrketabin ; ieta++)  {
          inctrkptEtaBin[ibin][ieta]->Write();
          NtrkEtaBin[ibin][ieta]->Write();
        }
        if(IsMC){
         if(DoGenAna){ 
           genpartpt[ibin]->Write();
            genpartphi[ibin]->Write();
            genparteta[ibin]->Write();
            incgenpartpt[ibin]->Write();
            incgenmatchpt[ibin]->Write();
          }    
        }
        } //centrality bins
    
    //  for(int i=0; i<6;i++) ptbin[i]->Write();
    CenBin->Write();
    CenBinWt->Write();
    Vertex->Write();
    VertexWt->Write();

    out_file->Close();
    cout <<"Output file: " <<Form("%s",out_name.Data()) <<endl ;
    
}


void anaInclusiveTrack()
{
//  pthat=atoi(getenv("PTHAT")) ;
//  ptmax=atoi(getenv("PTMAX")) ;
// cout <<"pthat = " <<pthat <<"  pthatmax =" <<ptmax <<endl ;
   // gROOT->ForceStyle(0);
    //for centrality reweight parameterization
    TF1 *fcen = new TF1("fcen","[0]*exp([1]+[2]*x+[3]*x*x+[4]*x*x*x)",0,40);
   // fcen->SetParameters(2.10653e-02,5.61607,-1.41493e-01,1.00586e-03,-1.32625e-04); //from Pawn/Pelin
    fcen->SetParameters(1.98261e-02,5.55963e+00,-1.34951e-01,1.70895e-03,-9.28386e-05); //fit by myself
   
  //  TF1 * fcen = new TF1("fcen","[0]+[1]*x+[2]*x*x+[3]*TMath::Power(x,3)", 0, 40);
  //  fcen->SetParameters(3.55169, -0.246077, 0.00541725,-3.64594e-05);
  //  fcen->SetParErrors(0.143397, 0.0166513, 0.000639065,7.94585e-06);
    //for vertex reweight parameterization
    TF1 * fVz = new TF1("fVx","[0]+[1]*x+[2]*TMath::Power(x,2)+[3]*TMath::Power(x,3)+[4]*TMath::Power(x,4)", -15., 15.);
    if(coll=="HI")
      //  fVz->SetParameters(0.803816, -0.0179222, 0.00716733, -0.000165785, 7.30741e-05); //PbPb vertex reweighting
        fVz->SetParameters(7.62788e-01,-1.13228e-02,5.85199e-03,-3.04550e-04,4.43440e-05); 
     else if(coll=="PPb")
        fVz->SetParameters(1.60182e+00,1.08425e-03,-1.29156e-02,-7.24899e-06,2.80750e-05); 
     else if(coll=="PbP")
        fVz->SetParameters(1.64354e+00,-3.63562e-03,-1.42033e-02,1.70149e-05,3.30168e-05); 
    else if(coll=="PP2011") 
    //    fVz->SetParameters(0.86946, -0.0353677, 0.00497902, -0.00016535, 4.53564e-05); //p vertex reweighting
      fVz->SetParameters(8.41684e-01,-2.58609e-02,4.86550e-03,-3.10581e-04,2.07918e-05); 
     else 
       fVz->SetParameters(1.28206e+00, 1.34215e-02, -5.85163e-03, -3.54998e-05, 7.35499e-06); //! data/MC without data shift
    //   fVz->SetParameters(1.26536e+00, 2.77455e-02, -5.47913e-03, -7.76245e-05, 6.25962e-06);//! data shift to vz+0.4847   
 //   fVz->SetParErrors(0.0218623, 0.00619651,  0.00144498,0.000105209, 1.3927e-05); //for PbPb vertext reweight parameters error
//   fVz->SetParErrors( 0.0280385, 0.00792399,  0.00173743,0.000122401, 1.59032e-05); //for PbPb vertext reweight parameters error
     
   
    TFile* fcrel3 = TFile::Open("/net/hidsk0001/d00/scratch/maoyx/JetShape/pAana/CMSSW_5_3_8_HI_patch2/src/Casym_pPb_Jul17_hcalbins.root", "readonly");//eta3,pPb hcalbins
    TH1D * C_rel=(TH1D*)fcrel3->Get("C_asym");
  //  fcrel3->Close();

   //this function is to correct for UE subtraction (we are using akPu3PF algorithm)
    TF1 *fUE = new TF1("fUE","[0]/pow(x,[1])");
    fUE->SetParameters(0.937820,-0.0111559);

    hist_class *my_hists = new hist_class("pfjet");
    cout <<my_hists->IsMC<<endl ;
    if(my_hists->IsMC==kTRUE){
      pthat=atoi(getenv("PTHAT")) ;
      ptmax=atoi(getenv("PTMAX")) ;
       cout <<"pthat = " <<pthat <<"  pthatmax =" <<ptmax <<endl ;
     }

    //! Edited by Pawan
    //! Load the Smearing factors
   // if(coll=="PP"&& DoSmear)
        LoadParameters();
    
//for pt jet reweight after smearing
    TH1F * ptwt[nbin];
    TFile * ptwtfile ;    
    if(DoJetPtWeight && DoSmear && (coll=="PP"||coll=="PP2011")){
     //     TFile * ptwtfile = TFile::Open("/Users/ymao/group/CMS/macros/DataJetPtReweight.root", "readonly");
  //      TFile * ptwtfile = TFile::Open("/home/group/CMS/WorkSpace/analysis/PFjet/DataJetPtReweight.root", "readonly");
        //  TFile * ptwtfile = TFile::Open("/afs/cern.ch/user/y/ymao/scratch0/JetShape/DataSubjetPtReweight.root", "readonly");     
     //   TFile * ptwtfile = TFile::Open("/net/hidsk0001/d00/scratch/maoyx/JetShape/CMSSW_4_4_2_patch5/src/DataJetPtReweight.root", "readonly");
        if(my_hists->IsMC==kTRUE)  
            ptwtfile = TFile::Open("/net/hidsk0001/d00/scratch/maoyx/JetShape/CMSSW_4_4_2_patch5/src/MCJetPtReweightRebin.root", "readonly");
         //   ptwtfile = TFile::Open("/net/hidsk0001/d00/scratch/maoyx/JetShape/CMSSW_4_4_2_patch5/src/2013MCHITrackingAk3PFJetPtReweightRebin.root", "readonly");
        else  
        //   ptwtfile = TFile::Open("/net/hidsk0001/d00/scratch/maoyx/JetShape/CMSSW_4_4_2_patch5/src/DataJetPtReweightRebin.root", "readonly");
       //    ptwtfile = TFile::Open("/net/hidsk0001/d00/scratch/maoyx/JetShape/CMSSW_4_4_2_patch5/src/DataJetPtReweight.root", "readonly");
         //   ptwtfile = TFile::Open("/net/hidsk0001/d00/scratch/maoyx/JetShape/CMSSW_4_4_2_patch5/src/DataAk3PFJetPtReweightRebin.root", "readonly");
        //    ptwtfile = TFile::Open("/net/hidsk0001/d00/scratch/maoyx/JetShape/CMSSW_4_4_2_patch5/src/DataAk3PFJetPtReweightRebin.root", "readonly");
            ptwtfile = TFile::Open("/net/hidsk0001/d00/scratch/maoyx/JetShape/CMSSW_4_4_2_patch5/src/2013DataHITrackingAk3PFJetPtReweightRebin.root", "readonly");

       //     ptwtfile = TFile::Open("/net/hidsk0001/d00/scratch/maoyx/JetShape/CMSSW_4_4_2_patch5/src/DataAk3PFJetPtReweightRebin.root", "readonly");
        for(int ibin = 0 ; ibin <nbin; ibin++){
          //  ptwt[ibin] = (TH1F*)ptwtfile->Get(Form("WeightFactor_JetPtCen%d-%d%%", centr[ibin],centr[ibin+1]));
            ptwt[ibin] = (TH1F*)ptwtfile->Get(Form("SmearedRatioJetPtCen%d-%d%%", centr[ibin],centr[ibin+1]));

        }
           ptwtfile->Close();
    }

    std::cout << "start working\n";
    if(my_hists->IsMC!=kTRUE){ 
      //    dataPath="/Users/ymao/group/CMS/hiForest";
   //  dataPath="/home/group/CMS/WorkSpace/data/HI2011/forest" ; //lxplus data path
      if(coll=="HI")
        //  dataPath="/net/hisrv0001/home/yenjie/slocal/merge/pbpb" ; //mit PbPb data for QM analysis
      //    dataPath="/net/hisrv0001/home/yenjie/slocal/merge/pbpbDijet" ; //mit PbPb data full dataset
        dataPath="/net/hidsk0001/d00/scratch/yjlee/merge/pbpbDijet_v20" ;//mit PbPb data path
 //  else  if(coll=="PP2011")
   //      dataPath="/net/hisrv0001/home/yenjie/scratch/hiForest/prod/productionPP/CMSSW_4_4_2_patch6/test/ppForest2";
  //  else    dataPath="/mnt/hadoop/cms/store/user/maoyx/hiForest";  //2013 data 
    else    dataPath="/mnt/hadoop/cms/store/user/ymao/hiForest/PA2013";  //2013 pPb MB data 
    }
    else { //MC analysis
    //         dataPath= "/Users/ymao/group/CMS/hiForest"; //local analysis
        if(coll=="HI") {
        //  dataPath= Form("/net/hisrv0001/home/yenjie/slocal/merge/v28/pthat%d",pthat); //lxplus MC normial
          if(pthat==50||pthat==80||pthat==100||pthat==170)
             dataPath= Form("/mnt/hadoop/cms/store/user/yenjie/HiForest_v27/"); //MIT MC normial
           else 
                dataPath= Form("/mnt/hadoop/cms/store/user/yenjie/HiForest_v28/"); //MIT MC normial
        //  dataPath= Form("/net/hisrv0001/home/yenjie/slocal/merge/pyquen/pyquen%s%d",para.Data(), pthat); //lxplus MC pquen
       }
       else if(coll=="PPb")
        dataPath=Form("/mnt/hadoop/cms/store/user/dgulhan/pPb/HP04/prod16/Hijing_Pythia_pt%d/HiForest_v77_merged01", pthat);
       else if(coll=="PbP")
        dataPath=Form("/mnt/hadoop/cms/store/user/dgulhan/Pbp/HP05/prod24/Hijing_Pythia_pt%d/HiForest_v84_merged02", pthat);
        else if(coll=="PP2011")
         dataPath= Form("/net/hisrv0001/home/zhukova/scratch/HIHighPt/forest/pthat%d", pthat); //lxplus path for pp
       //  dataPath= Form("/mnt/hadoop/cms/store/user/icali/Pythia/Z2/ppDijet_merged"); //lxplus path for pp
       else {       
       //  dataPath= Form("/mnt/hadoop/cms/store/user/dgulhan/ppHiIterativeTrack/P01/prod24/Signal_Pythia_pt%d/HiForest_v84_merged01", pthat); //2013 pp HI tracking
      //  dataPath= Form("/mnt/hadoop/cms/store/user/dgulhan/pp2013/P01/prod22/Signal_Pythia_pt%d/HiForest_v81_merged01", pthat); //2013 pp tracking for 2.76TeV
     //  dataPath= Form("/mnt/hadoop/cms/store/user/kjung/pp_Fix_MergedForest", pthat); //2013 pp tracking for B-tagging at 2.76TeV
       if(pthat==220)
         dataPath= Form("/mnt/hadoop/cms/store/user/dgulhan/pPb/HP04/prod16/Signal_Pythia_pt%d/HiForest_v77_v2_merged02", pthat); //2013 pp tracking for 5.02TeV
      else 
       dataPath= Form("/mnt/hadoop/cms/store/user/dgulhan/pPb/HP04/prod16/Signal_Pythia_pt%d/HiForest_v77_v2_merged01", pthat); //2013 pp tracking for 5.02TeV
        }
    }
    if(my_hists->IsMC!=kTRUE){  //real data analysis
        if(coll=="HI")             
          //  intputFile="mergedFile.root" ;  //QM analysis results
            intputFile="promptskim-hihighpt-hltjet80-pt90-v20.root" ; //full dataset
         //  intputFile="castor_frank_PbPb_dijetforest2_HiForest-promptskim-hihighpt-hltjet80-pt90-v2_v3_part2.root";
	    //  intputFile="HiForest-promptskim-hihighpt-hltjet80-pt90-v3_part2.root";
       // intputFile="promptskim-hihighpt-hltjet80-pt90-v3-forest-v2.root";
      //  else { 
	else if(coll=="PP2011")  
             intputFile="hiForest2_pp_ppreco_415_90percent.root";  //! 2011 pp data rereco
         //	      intputFile="pp_merged_full.root";   // ! 2011 pp data
        else if(coll=="PbPb")
           intputFile="PbPHiForest2_PbPbPAHighPtJet80_cent50-100_pprereco.root"; 	
        else if(coll=="PPb")
     //    intputFile="PA2013_HiForest_PromptReco_JSonPPb_forestv77.root";
         intputFile="PA2013_HiForest_PromptReco_KrisztianMB_JSonPPb_forestv84.root" ;
        else if(coll=="PbP")
         intputFile="PA2013_HiForest_PromptReco_JSonPbp_JECdb_forestv84.root" ;
        else 
         //  intputFile="PP2013_HiForest_PromptReco_JsonPP_Jet80_HIReco_forestv84_v2.root";  //! 2013 pp data with HI tracking
           intputFile="PP2013_HiForest_PromptReco_JsonPP_Jet80_PPReco_forestv82.root";  //! 2013 pp data with pp tracking
       //    intputFile=Form("pt%d_HP04_prod16_v77_merged_forest_Sum.root",pthat);  //! 2013 MC for 5.02TeV with pp tracking
    //    }
    }
    else { //MC sample
        if(coll=="HI"){             
	  //  intputFile=Form("pyquen%s%d_HYDJET.root", para.Data(), pthat);
          if(pthat==50||pthat==80||pthat==100||pthat==170)
              intputFile=Form("Dijet%d_HydjetDrum_v27_mergedV1.root", pthat);
         else 
              intputFile=Form("Dijet%d_HydjetDrum_v28_mergedV1.root", pthat);
	  /*	        if(pthat==80) 
              //  intputFile=Form("Pythia%d_HydjetDrum_mix01_HiForest2_v22_simTrack05.root", pthat);
                intputFile=Form("Pythia%d_HydjetDrum_mix01_HiForest2_v20.root", pthat);
            else if(pthat==30||pthat==50 ||pthat==170)
                intputFile=Form("Pythia%d_HydjetDrum_mix01_HiForest2_v19.root", pthat);  
            else 
                intputFile=Form("Pythia%d_HydjetDrum_mix01_HiForest2_v21_ivan.root", pthat);
            //  intputFile="merged_HydjetDrum.root";
	    */  
   }
      else if(coll=="PPb")
        intputFile=Form("pt%d_HP04_prod16_v77_merged_forest_0.root", pthat);
      else if(coll=="PbP")
        intputFile=Form("pt%d_HP05_prod24_v84_merged_forest_0.root", pthat);
      else if(coll=="PP2011")
          intputFile=Form("mergedFile.root");  // 2011 pp MC
        else 
       //   intputFile=Form("pp276Dijet%d_merged.root",pthat);  
        //  intputFile=Form("pt%d_JEC_ppHiIterativeTrack_P01_prod24_v84_merged_forest_0.root", pthat); // ! 2013 pp@2.76TeV MC with HI tracking 
      //    intputFile=Form("pt%d_pp2013_P01_prod22_v81_merged_forest_0.root", pthat); // ! 2013 pp@2.76TeV MC with pp tracking 
         intputFile=Form("pt%d_HP04_hiforest77_hiSignal.root", pthat); // ! 2013 pp 5.02TeV MC with pp tracking 
    //      intputFile=Form("pp_Fix_MCBForest%doutput.root", pthat); // ! 2013 pp 2.76TeV MC with pp tracking for b-tagging 
    }
    
    TString inname=Form("%s/%s", dataPath.Data(),intputFile.Data());
    // Define the input file and HiForest
  //  bool isPP =false ;
   HiForest * c ; 
   if(coll=="PP" || coll=="PP2011")
        c = new HiForest(inname,"forest",cPP);
     else if(coll=="PPb" || coll=="PbP")
        c = new HiForest(inname,"forest",cPPb);
     else 
        c = new HiForest(inname,"forest",cPbPb);
  //  HiForest * c = new HiForest(inname,"forest",isPP);
   // HiForest *c = new HiForest(inname);
  //  if(doTrackCorrections)
  //       c->doTrackCorrections = 1;
  //  else 
       c->doTrackCorrections = false;
    c->doTrackingSeparateLeadingSubleading = false;
    c->InitTree();
  //  cout << "start working222222\n";
  //  TFile *my_file=TFile::Open(Form("%s/%s", dataPath.Data(),intputFile.Data()));
    cout <<"Input file" << inname<<endl ;
    
    TrackCorrector corr("trkcorr/trackCorrections_HIN12017v4_HijingCombined.root");
   if(doTrackCorrections){
   corr.load("trkCorr_HIN12017");
   corr.setOption1(true);
   corr.setOption2(true);
  }

//    if(my_file->IsZombie()) {
//    }
    
    // evt tree
//    TTree *evt_tree = (TTree*) c->inf->Get("hiEvtAnalyzer/HiTree");
//    Evts offSel;
//    if (evt_tree) {
//        c->CheckTree(evt_tree,"HiTree");
//        setupEvtTree(evt_tree,offSel,1);
//    }
    Evts * offSel = &(c->evt); 

    //skim tree
//    TTree *skim_tree = (TTree*) c->inf->Get("skimanalysis/HltTree");
//    Skims my_skim;
//    if (skim_tree) {
//        c->CheckTree(skim_tree,"HltTree");
//        setupSkimTree(skim_tree,my_skim,1);
//    }
    Skims * my_skim = &(c->skim); 

    //hlt tree
//    TTree *hlt_tree = (TTree*) c->inf->Get("hltanalysis/HltTree");
//     Hlts trigSel;
//    if (hlt_tree) {
//        c->CheckTree(hlt_tree,"HltTree");
//        setupHltTree(hlt_tree,trigSel,1);
//    }
    Hlts * trigSel = &(c->hlt); 
    //jet tree
//    TTree *inp_tree = (TTree*) c->inf->Get("akPu3PFJetAnalyzer/t");
//    Jets my_ct;
//    if (inp_tree) {
//        c->CheckTree(inp_tree,"t");
//        SetupJetTree(inp_tree,my_ct,1);
//    }
    
//    if(coll=="HI") 
        Jets * my_ct = &(c->akPu3PF); 
 //   else 
  //   Jets * my_ct = &(c->ak3PF);
    //  Jets * jetthres =  &(c->icPu5); 
   //track tree

//    TTree *tr_tree = (TTree*) c->inf->Get("mergedTrack/trackTree");
////    TTree *tr_tree = (TTree*) c->inf->Get("anaTrack/trackTree");
//    Tracks my_tr;
//    if (tr_tree) {
//        c->CheckTree(tr_tree,"trackTree");
//        SetupTrackTree(tr_tree,my_tr,1);
//    }
    Tracks * my_tr = &(c->track);
    
    //GenParticle tree
//    TTree *GenPart_tree = (TTree*) c->inf->Get("HiGenParticleAna/hi");
//    GenParticles my_GenPart;
//    if (GenPart_tree) {
//        c->CheckTree(GenPart_tree,"hi");
//        SetupGenParticleTree(GenPart_tree,my_GenPart,1);
//    }
    GenParticles * my_GenPart = &(c->genparticle);

    int curr_bin = nbin-1 ;
    int Nevents = 0 ;
    cout <<"Number of events ="<<c->GetEntries()<<endl ;
    for(int evi = 0; evi < c->GetEntries(); evi++) {
    //            for(int evi = 0; evi < 50; evi++) {
        c->GetEntry(evi);
      //  if(evi%2==1) continue ; 
      //  if(evi%2==0) continue ; 
       //cout <<"evt = "<<evi <<endl ; 
        int noise_evt = my_skim->pHBHENoiseFilter ;
        //        int ecal_noise = my_skim->phiEcalRecHitSpikeFilter ;
        //        if(ecal_noise==0) continue ;
        
        double vz = offSel->vz ;
        int hiBin = offSel->hiBin ;
        weight = 1. ;      
 
         int pileup_Gplus ;
 //  if(coll=="HI") {
       if(my_hists->IsMC!=kTRUE){
            int evt_sel ;
            pileup_Gplus = my_skim->pVertexFilterCutGplus ;
           if(coll=="PbPb"|| coll=="HI"|| coll=="PP2011")  evt_sel = my_skim->pcollisionEventSelection ;
            else  evt_sel = my_skim->pPAcollisionEventSelectionPA;
            if(evt_sel==0) continue ;
        }
        if(my_hists->IsMC!=kTRUE){
            if(noise_evt==0) continue ;
             int jetTr2 ;
              if(coll=="HI"|| coll=="PbPb")
               jetTr2 = trigSel->HLT_HIJet80_v1 ;
                else if (coll=="PP2011")
                 jetTr2 = trigSel->HLT_Jet60_v1 ;
               else
               //  jetTr2 = trigSel->HLT_PAJet80_NoJetID_v1 ;
                 jetTr2 = trigSel->HLT_PAZeroBiasPixel_SingleTrack_v1 ;
     //         if(coll=="HI"){
     //	      int jetTr2 = trigSel->HLT_HIJet80_v1 ;
            //    else 
            //            int jetTr1 = trigSel->HLT_Jet40_v1 ;
	           	  //    int jetTr2 = trigSel->HLT_Jet60_v1 ;
            //                
            if(jetTr2==0) continue ;
            int run=offSel->run ;
            if(coll=="PPb"){
             if( my_skim->phfPosFilter1==0 || my_skim->phfNegFilter1==0 ||my_skim->pBeamScrapingFilter==0 || my_skim->pprimaryvertexFilter==0) continue ;
             if(pileup_Gplus==0) continue ;
             if(run>211256) continue ;
            // if(run<=210658) continue ;  //remove the runs with old alignment
             if(run<210676) continue ;  //remove the runs with old alignment
            }
           if(coll=="PbP"){
             if(pileup_Gplus==0) continue ;
            if(run<=211256) continue ;
           }
   //	}
        }
                
        //if there is no jets or no PF candidates, skip the event
        if(my_ct->nref==0) continue ;
        //put the higher pthat cut
        if(my_hists->IsMC==kTRUE && my_ct->pthat>ptmax) continue ;
         if(my_ct->pthat>ptmax) cout <<"pthat =" <<my_ct->pthat <<endl ;
       if(coll=="HI"|| coll=="PP2011") 
        my_hists->CenBin->Fill(hiBin*2.5);
      else my_hists->CenBin->Fill(hiBin);

        my_hists->Vertex->Fill(vz);

        //   cout <<"vz =" <<vz <<endl ;
        if(TMath::Abs(vz)>15.) continue ;
        if(my_hists->IsMC==kTRUE) weight*=fVz->Eval(vz);
        else weight=1. ;
        
         if(coll=="HI"){
            if(my_hists->IsMC==kTRUE) 
                // weight = wt[hiBin]; 
                weight*=fcen->Eval(hiBin);
            // weight = 1.;
            else 
                weight = 1. ;
            double centrality = hiBin*2.5 ;
            //   my_hists->CenBin->Fill(offSel->hiBin);
            
            for(int ibin = 0 ; ibin <nbin; ibin++){
                if(centrality >=centr[ibin] && centrality<centr[ibin+1]) curr_bin = ibin ;
            }
        }
        else {
            curr_bin=nbin-1 ;
             weight = 1. ;
        }
       //   weight = 1. ;

       //    cout << "  cent_bin:" <<curr_bin <<endl ;
        if(evi%10000==1)cout <<" coll = " <<coll <<" weight = " <<weight <<" evt = " <<evi <<endl ;
        
      //  my_hists->Ntrack[curr_bin]->Fill(1, weight);
        //cout <<my_hists->NEvents[curr_bin]->GetName() <<endl;
        //cout << "start working222222\n";
        
        
        //  cout << "still working222222\n";
        if(my_hists->IsMC==kFALSE)my_hists->VertexWt->Fill(vz+0.4847, weight);
        else  my_hists->VertexWt->Fill(vz, weight);
         if(coll=="HI"|| coll=="PP2011")     
           my_hists->CenBinWt->Fill(offSel->hiBin*2.5,weight);
        else
         my_hists->CenBinWt->Fill(offSel->hiBin,weight);


   // for inclusive jet analysis
   for(int j4i = 0; j4i < my_ct->nref ; j4i++) {
    double jetweight = 1; 
    double jet_pt= my_ct->jtpt[j4i];
    double jet_eta = my_ct->jteta[j4i];
    int dEtaBin = -1. ;
     //for jet kinematcis cuts
     if(jet_pt>100. && TMath::Abs(jet_eta)<3.){
        jetweight = (fUE->Eval(jet_pt))*C_rel->GetBinContent(C_rel->FindBin(jet_eta));
        my_hists->jetpt[curr_bin]->Fill(jet_pt*jetweight, weight);
         for(Int_t ieta = 0 ; ieta <netabin; ieta++){
            if(coll=="PPb"){
               if((jet_eta+0.465)>deta[ieta]&&(jet_eta+0.465)<=deta[ieta+1]) dEtaBin = ieta ;
             }
            else if(coll=="PbP"){
              if((jet_eta-0.465)>deta[ieta]&&(jet_eta-0.465)<=deta[ieta+1]) dEtaBin = ieta ;
             }
           else {
             if((jet_eta)>deta[ieta]&&(jet_eta)<=deta[ieta+1]) dEtaBin = ieta ;
            } 
         } //assign the eta bin for jets
      if(dEtaBin!=-1){
        my_hists->jetptEtaBin[curr_bin][dEtaBin]->Fill(jet_pt*jetweight, weight);   
        my_hists->NjetsEtaBin[curr_bin][dEtaBin]->Fill(1);
     } 
    }// for jet kinematics cuts
   } //! jet loop

        //Leading Jets seach, for tracking efficiency
      double leadingJetPt = -1. ;
      Int_t leadingJetIndex = -1 ;
     for(int j = 0; j < my_ct->nref ; j++) {
         if (fabs(my_ct->jteta[j])>2.5) continue;
         if (my_ct->rawpt[j]<15) continue;
         if (my_ct->jtpt[j]>leadingJetPt) {
            leadingJetPt = my_ct->jtpt[j];
            leadingJetIndex = j;
         }
      }
      if(leadingJetPt==-1) //for corrections
            leadingJetPt=10.;

      //Tracks for event weights; eta-pt cut removed
      int trackMult = 0;
      for(int j=0;j<my_tr->nTrk;j++) {
         if(!((my_tr->highPurity[j])
             && (fabs(my_tr->trkDz1[j]/my_tr->trkDzError1[j])<3)
             && (fabs(my_tr->trkDxy1[j]/my_tr->trkDxyError1[j])<3)
             && (my_tr->trkPtError[j]/my_tr->trkPt[j]<0.1)
            ))
            continue;
         trackMult++;
      }
      // Don't analyze 0 multiplicity events; correction added later
      if(trackMult==0)
         continue;
      double evtWeight = 1.;
      evtWeight = corr.getEventWeight(trackMult);

     //for inclusive track analysis, without jet selection and requirement
       for(int itr = 0 ; itr < my_tr->nTrk ; itr++){
                            double tr_pt = my_tr->trkPt[itr];
                            double tr_phi = my_tr->trkPhi[itr];
                            double tr_eta = my_tr->trkEta[itr];
                            if(TMath::Abs(tr_eta)>2.4) continue ;
         //                    if(my_tr->trkPtError[itr]/my_tr->trkPt[itr]>=0.1 || TMath::Abs(my_tr->trkDz1[itr]/my_tr->trkDzError1[itr])>=3.0 ||TMath::Abs(my_tr->trkDxy1[itr]/my_tr->trkDxyError1[itr])>=3.0) continue ; //ridge cut for tracks                           
         if(!((my_tr->highPurity[itr])
             && (fabs(my_tr->trkDz1[itr]/my_tr->trkDzError1[itr])<3)
             && (fabs(my_tr->trkDxy1[itr]/my_tr->trkDxyError1[itr])<3)
             && (my_tr->trkPtError[itr]/my_tr->trkPt[itr]<0.1)
            ))
            continue;
                            Int_t TrkEtaBin = -1 ;
                       for(Int_t ieta = 0 ; ieta <ntrketabin; ieta++){
                        if(coll=="PPb"){             
                           if((tr_eta+0.465)>dtrketa[ieta]&&(tr_eta+0.465)<=dtrketa[ieta+1]) TrkEtaBin = ieta ;
                           }
                        else if(coll=="PbP"){
                            if((tr_eta-0.465)>dtrketa[ieta]&&(tr_eta-0.465)<=dtrketa[ieta+1]) TrkEtaBin = ieta ;
                           }
                        else  
                      if((tr_eta)>dtrketa[ieta]&&(tr_eta)<=dtrketa[ieta+1]) TrkEtaBin = ieta ; 
                     } 
                            if((my_tr->highPurity[itr])){
                                if(tr_pt<trackcut) continue ;
                            double trkweight=1. ;
                            if(doTrackCorrections){
                             //   if(corrMet=="Hist")trkweight = c->getTrackCorrection(itr);
                             //   else trkweight = c->getTrackCorrectionPara(itr);
                             trkweight = corr.getWeight(tr_pt,tr_eta,leadingJetPt);
                            }
                        my_hists->inctrkpt[curr_bin]->Fill(tr_pt, weight*trkweight);
                        if(TMath::Abs(tr_eta)<=1)
                          my_hists->inctrkptM1P1[curr_bin]->Fill(tr_pt, weight*trkweight);
                        my_hists->Ntrack[curr_bin]->Fill(1);
                        if(TrkEtaBin!=-1) my_hists->inctrkptEtaBin[curr_bin][TrkEtaBin]->Fill(tr_pt, weight*trkweight);
                        if(TrkEtaBin!=-1) my_hists->NtrkEtaBin[curr_bin][TrkEtaBin]->Fill(1);
                      } //! high purity track cuts
              }  //! inclusive track loop
       Nevents++;
       my_hists->NEvents[curr_bin]->Fill(1, weight);
            if(my_hists->IsMC==kTRUE&&DoGenAna){
                          //using the sim track to calculate the tracking efficiency 
                    for(int ipart = 0 ; ipart < my_tr->nParticle ; ipart++){ //sim track loop 
                        double gen_pt = my_tr->pPt[ipart];
                        double gen_phi = my_tr->pPhi[ipart];
                        double gen_eta = my_tr->pEta[ipart];
                        if(gen_pt<trackcut)continue ;
                        if(TMath::Abs(gen_eta)>2.4)continue ;
                              if(my_tr->pNRec[ipart]>0&&((my_tr->mtrkQual[ipart]))) {
                                 if((my_tr->mtrkPtError[ipart]/my_tr->mtrkPt[ipart]<0.1 && TMath::Abs(my_tr->mtrkDz1[ipart]/my_tr->mtrkDzError1[ipart])<3.0 && TMath::Abs(my_tr->mtrkDxy1[ipart]/my_tr->mtrkDxyError1[ipart])<3.0)){
                                my_hists->incgenmatchpt[curr_bin]->Fill(gen_pt, weight);
                                 } //tracking cut
                              } // matching hist
                             my_hists->incgenpartpt[curr_bin]->Fill(gen_pt,weight);
                       } //! sim track loop
      } //only runs on MC
    }  ///event loop
    
       my_hists->NevtCounter[curr_bin]->SetBinContent(1, Nevents);
    my_hists->Write();
    //   my_hists->Delete();
    //  delete my_hists;
    std::cout << "working done\n";
}





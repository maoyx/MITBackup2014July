#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"
#include "class_def/skim.h"
#include "class_def/Evt.h"
#include "class_def/HIHLT.h"
#include "class_def/track.h"
#include "class_def/akPu3PFJet.h"
#include "class_def/pfTree.h"
#include "TMath.h"
#include <iostream>
using namespace std;

//define the kinematics cuts for the analysis
const double conesize = 0.3 ;
const double deltacone = 0.05 ;

//const double radius = 0.025;

//const int nrbin = 10 ;
//double rbin[nrbin+1]={0.0,0.05,0.10, 0.15, 0.20,0.25,0.30,0.35,0.40,0.45,0.50};

const int nrbin = 6 ;
double rbin[nrbin+1]={0.0,0.05,0.10, 0.15, 0.20,0.25,0.30};

//const double radius = atoi(gSystem->Getenv("RADIUS"))  ;

const double etacut = 1.0 ;
const double dphicut = TMath::TwoPi()/3. ;
const double leadingjetcut = 80. ;
const double subleadjetcut = 40. ;
const double trackcut = 4.;
const double tracketacut = 3.; //make sure the tracks around jet cone inside eta range

//for background cut
const double bkgetacut = 0.0 ; //bkg eta range: [0., 0.5, 1.0, 1.5]
const double bkgphicut = TMath::PiOver2()/2. ; //bkg phi[0., 1/3.,1/2.] 

//for HI centrality bin
const int nbin = 6 ;
const double centr[] ={0,10,20,30,50,70,100};

bool IsMC = kTRUE ;
const int pthat =200 ; //30 and 80 for pp; 30,50,80,120,170,200 for PbPb MC 

TString coll = "HI";
TString intputFile ;

//TString dataPath="/Users/ymao/group/CMS/hiForest";
TString dataPath ;

// //if it is pp, no centrality bins, only one
// const int nbin = 1 ;
// const double centr[] ={0,100};

class hist_class {
public:
    hist_class(TString the_desc);
    void Delete();
    void Write();
    
    TString desc;
    
    TH1F * NEvents[nbin];
    TH1F * NJets[nbin];
    TH1F * Ntrack[nbin];
    TH1F * jetpt[nbin];
    TH1F * subjetpt[nbin];
    TH1F * dijet[nbin];
    TH1F * Rjj[nbin];
    TH2F * dihadron[nbin];
    TH1F * Ajj[nbin] ;
    TH1F * trackpt[nbin];
    TH2F * NeutralPt[nbin];
    TH2F * PhotonPt[nbin];
    TH2F * ChargePt[nbin];
    TH2F * SumNePt[nbin];
    TH2F * SumPhPt[nbin];
    TH2F * SumChPt[nbin];
    TH2F * NeutralMult[nbin];
    TH2F * PhotonMult[nbin];
    TH2F * ChargeMult[nbin];   
    TH2F * jetfrag[nbin] ;
    TH2F * subjetfrag[nbin] ;
    TH1F * deltaR;
    TH1F * leadingFrac;
    
    //for jet shape variables
    TH2F * DiffJS[nbin][nrbin]; //differential jet shapes (pho(r)) hist.
    TH2F * IntJS[nbin][nrbin]; //Integrated jet shapes (psi(r)) hist.
    TH2F * dphiJS[nbin]; //phi diviration from jet phi 
    TH2F * detaJS[nbin] ; //eta diviration from jet eta 
    TH2F * subDiffJS[nbin][nrbin]; //differential sub-jet shapes (pho(r)) hist.
    TH2F * subIntJS[nbin][nrbin]; //Integrated sub-jet shapes (psi(r)) hist.
    
    //for jet shape backgroun study
    TH2F * bkgNeutralPt[nbin];
    TH2F * bkgPhotonPt[nbin];
    TH2F * bkgChargePt[nbin];
    TH2F * bkgSumNePt[nbin];
    TH2F * bkgSumPhPt[nbin];
    TH2F * bkgSumChPt[nbin];
    TH2F * bkgNeutralMult[nbin];
    TH2F * bkgPhotonMult[nbin];
    TH2F * bkgChargeMult[nbin];   
    TH2F * bkgDiffJS[nbin][nrbin]; //differential jet shapes (pho(r)) hist.
    TH2F * bkgIntJS[nbin][nrbin]; //Integrated jet shapes (psi(r)) hist.
    TH2F * bkgsubDiffJS[nbin][nrbin]; //differential sub-jet shapes (pho(r)) hist.
    TH2F * bkgsubIntJS[nbin][nrbin]; //Integrated sub-jet shapes (psi(r)) hist.    
};

hist_class::hist_class(TString the_desc)
{
    
    desc = the_desc;
    for(int ibin = 0 ; ibin <nbin; ibin++){
        NEvents[ibin] = new TH1F(Form("Nevents_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("Nevents_%.f-%.f%%",centr[ibin],centr[ibin+1]), 100, 0., 100.);
        NJets[ibin] = new TH1F(Form("NJets_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("NJets_%.f-%.f%%",centr[ibin],centr[ibin+1]), 100, 0., 100.);
        Ntrack[ibin] = new TH1F(Form("Ntracks_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("Ntracks_%.f-%.f%%",centr[ibin],centr[ibin+1]), 100, 0., 1000.);
        jetpt[ibin] = new TH1F(Form("jetpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("jetpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0., 500.);
        subjetpt[ibin] = new TH1F(Form("subjetpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("subjetpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0., 500.);
        dijet[ibin] = new TH1F(Form("dphi_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("dphi_%.f-%.f%%",centr[ibin],centr[ibin+1]), 120, -4., 8.);
        Rjj[ibin] = new TH1F(Form("Rjj_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("Rjj_%.f-%.f%%",centr[ibin],centr[ibin+1]), 100, 0., 2.);        
        dihadron[ibin] = new TH2F(Form("dihadron_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("dihadron_%.f-%.f%%",centr[ibin],centr[ibin+1]), 120, -4., 8.,100, -5.,5.);
        Ajj[ibin] = new TH1F(Form("Aj_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("Aj_%.f-%.f%%",centr[ibin],centr[ibin+1]), 100, 0., 1.);
        trackpt[ibin] = new TH1F(Form("trackpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("trackpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0., 500.);
        NeutralPt[ibin] = new TH2F(Form("neutralpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("neutralpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 500, 0., 500.);
        NeutralPt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        NeutralPt[ibin]->GetYaxis()->SetTitle("p_{T} (GeV/c)");
        PhotonPt[ibin] = new TH2F(Form("photonpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("photonpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 500, 0., 500.);
        PhotonPt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        PhotonPt[ibin]->GetYaxis()->SetTitle("p_{T} (GeV/c)");
        ChargePt[ibin] = new TH2F(Form("chargept_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("chargept_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 500, 0., 500.);
        ChargePt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        ChargePt[ibin]->GetYaxis()->SetTitle("p_{T} (GeV/c)");
        SumNePt[ibin] = new TH2F(Form("sumneutralpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("sumneutralpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 100, 0., 1.);
        SumNePt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        SumNePt[ibin]->GetYaxis()->SetTitle("#Sigma p_{T}^{h^{0}}/p_{T}^{jet}");   
        SumPhPt[ibin] = new TH2F(Form("sumphotonpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("sumphotonpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 100, 0., 1.);
        SumPhPt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        SumPhPt[ibin]->GetYaxis()->SetTitle("#Sigma p_{T}^{#gamma}/p_{T}^{jet}"); 
        SumChPt[ibin] = new TH2F(Form("sumchpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("sumchargept_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 100, 0., 1.);
        SumChPt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        SumChPt[ibin]->GetYaxis()->SetTitle("#Sigma p_{T}^{h^{#pm}}/p_{T}^{jet}");
        NeutralMult[ibin] = new TH2F(Form("NeMult_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("NeMult_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 100, 0., 100.);
        NeutralMult[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        NeutralMult[ibin]->GetYaxis()->SetTitle("# of Neutral");    
        PhotonMult[ibin] = new TH2F(Form("PhMult_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("PhMult_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 100, 0., 100.);
        PhotonMult[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        PhotonMult[ibin]->GetYaxis()->SetTitle("# of Charge");    
        ChargeMult[ibin] = new TH2F(Form("ChMult_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("ChMult_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 100, 0., 100.);
        ChargeMult[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        ChargeMult[ibin]->GetYaxis()->SetTitle("# of Charge");    
        
        jetfrag[ibin] = new TH2F(Form("FFleading_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("FFleading_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 100, 0., 5.);
        jetfrag[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        jetfrag[ibin]->GetYaxis()->SetTitle("#xi = ln(p_{T}^{jet}/p_{T}^{h})");
        subjetfrag[ibin] = new TH2F(Form("FFsubleading_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("FFsubleading_%.f-%.f%%",centr[ibin],centr[ibin+1]), 100, 0., 5.,100, 0., 5.);
        subjetfrag[ibin]->GetXaxis()->SetTitle("#xi = ln(p_{T}^{jet1}/p_{T}^{h})");
        subjetfrag[ibin]->GetYaxis()->SetTitle("#xi = ln(p_{T}^{jet2}/p_{T}^{h})");
        
        //for bkg histos.
        bkgNeutralPt[ibin] = new TH2F(Form("bkgneutralpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("bkgneutralpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 500, 0., 500.);
        bkgNeutralPt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        bkgNeutralPt[ibin]->GetYaxis()->SetTitle("p_{T} (GeV/c)");
        bkgPhotonPt[ibin] = new TH2F(Form("bkgphotonpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("bkgphotonpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 500, 0., 500.);
        bkgPhotonPt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        bkgPhotonPt[ibin]->GetYaxis()->SetTitle("p_{T} (GeV/c)");    
        bkgChargePt[ibin] = new TH2F(Form("bkgchargept_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("bkgchargept_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 500, 0., 500.);
        bkgChargePt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        bkgChargePt[ibin]->GetYaxis()->SetTitle("p_{T} (GeV/c)");
        bkgSumNePt[ibin] = new TH2F(Form("bkgsumneutralpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("bkgsumneutralpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 100, 0., 1.);
        bkgSumNePt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        bkgSumNePt[ibin]->GetYaxis()->SetTitle("#Sigma p_{T}^{h^{0}}/p_{T}^{jet}");   
        bkgSumPhPt[ibin] = new TH2F(Form("bkgsumphotonpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("bkgsumphotonpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 100, 0., 1.);
        bkgSumPhPt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        bkgSumPhPt[ibin]->GetYaxis()->SetTitle("#Sigma p_{T}^{#gamma}/p_{T}^{jet}");   
        bkgSumChPt[ibin] = new TH2F(Form("bkgsumchpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("bkgsumchargept_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 100, 0., 1.);
        bkgSumChPt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        bkgSumChPt[ibin]->GetYaxis()->SetTitle("#Sigma p_{T}^{h^{#pm}}/p_{T}^{jet}");    
        bkgNeutralMult[ibin] = new TH2F(Form("bkgNeMult_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("bkgNeMult_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 100, 0., 100.);
        bkgNeutralMult[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        bkgNeutralMult[ibin]->GetYaxis()->SetTitle("# of Neutral");    
        bkgPhotonMult[ibin] = new TH2F(Form("bkgPhMult_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("bkgPhMult_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 100, 0., 100.);
        bkgPhotonMult[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        bkgPhotonMult[ibin]->GetYaxis()->SetTitle("# of Charge");    
        bkgChargeMult[ibin] = new TH2F(Form("bkgChMult_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("bkgChMult_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 100, 0., 100.);
        bkgChargeMult[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        bkgChargeMult[ibin]->GetYaxis()->SetTitle("# of Charge");
        for(int ir = 0 ; ir <nrbin; ir++){
            DiffJS[ibin][ir] = new TH2F(Form("differentialJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("differentialJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500., 150, 0., 1.5);
            DiffJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            DiffJS[ibin][ir]->GetYaxis()->SetTitle("#rho (r)");
            IntJS[ibin][ir] = new TH2F(Form("IntegratedJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("IntegratedJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500., 150, 0., 1.5);
            IntJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            IntJS[ibin][ir]->GetYaxis()->SetTitle(Form("#psi(r=%1.2f)",deltacone*(ir+1)));
            
            subDiffJS[ibin][ir] = new TH2F(Form("subjetdifferentialJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("subjetdifferentialJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500., 150, 0., 1.5);
            subDiffJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            subDiffJS[ibin][ir]->GetYaxis()->SetTitle("#rho (r)");
            subIntJS[ibin][ir] = new TH2F(Form("subjetIntegratedJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("subjetIntegratedJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500., 150, 0., 1.5);
            subIntJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            subIntJS[ibin][ir]->GetYaxis()->SetTitle(Form("#psi(r=%1.2f)",deltacone*(ir+1)));
            
            bkgDiffJS[ibin][ir] = new TH2F(Form("bkgdifferentialJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("bkgdifferentialJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500., 150, 0., 1.5);
            bkgDiffJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            bkgDiffJS[ibin][ir]->GetYaxis()->SetTitle("#rho (r)");
            bkgIntJS[ibin][ir] = new TH2F(Form("bkgIntegratedJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("bkgIntegratedJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500., 150, 0., 1.5);
            bkgIntJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            bkgIntJS[ibin][ir]->GetYaxis()->SetTitle(Form("#psi(r=%1.2f)",deltacone*(ir+1)));
            bkgsubDiffJS[ibin][ir] = new TH2F(Form("bkgsubjetdifferentialJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("bkgsubjetdifferentialJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500., 150, 0., 1.5);
            bkgsubDiffJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            bkgsubDiffJS[ibin][ir]->GetYaxis()->SetTitle("#rho (r)");
            bkgsubIntJS[ibin][ir] = new TH2F(Form("bkgsubjetIntegratedJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("bkgsubjetIntegratedJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500., 150, 0., 1.5);
            bkgsubIntJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            bkgsubIntJS[ibin][ir]->GetYaxis()->SetTitle(Form("#psi(r=%1.2f)",deltacone*(ir+1)));          
        }
        
    }
    
    // if(!deltaR)
    deltaR = new TH1F((TString) (desc + "_deltaR"), "", 100, 0., 10.);
    // if(!leadingFrac)
    leadingFrac = new TH1F((TString) (desc + "_leadingFrac"), "", 100, 0., 2.);
    
    
    
}

void hist_class::Delete()
{
    for(int ibin = 0 ; ibin <nbin; ibin++){
        delete NEvents[ibin];
        delete NJets[ibin];
        delete Ntrack[ibin];  
        delete jetpt[ibin];
        delete subjetpt[ibin];
        delete dijet[ibin];
        delete Rjj[ibin] ;  
        delete dihadron[ibin];
        delete Ajj[ibin];
        delete trackpt[ibin];
        delete NeutralPt[ibin];
        delete PhotonPt[ibin];
        delete ChargePt[ibin];
        delete SumNePt[ibin];
        delete SumPhPt[ibin];
        delete SumChPt[ibin];
        delete NeutralMult[ibin];
        delete PhotonMult[ibin];
        delete ChargeMult[ibin];
        delete bkgNeutralPt[ibin];
        delete bkgPhotonPt[ibin];
        delete bkgChargePt[ibin];
        
        delete jetfrag[ibin];
        delete subjetfrag[ibin];
        
        delete bkgNeutralPt[ibin];
        delete bkgPhotonPt[ibin];
        delete bkgChargePt[ibin];      
        delete bkgSumNePt[ibin];
        delete bkgSumPhPt[ibin];
        delete bkgSumChPt[ibin];
        delete bkgNeutralMult[ibin];
        delete bkgPhotonMult[ibin];
        delete bkgChargeMult[ibin];
        
        for(int ir = 0 ; ir <nrbin; ir++){
            delete DiffJS[ibin][ir];
            delete IntJS[ibin][ir];
            delete subDiffJS[ibin][ir];
            delete subIntJS[ibin][ir];
            delete bkgDiffJS[ibin][ir];
            delete bkgIntJS[ibin][ir];
            delete bkgsubDiffJS[ibin][ir];
            delete bkgsubIntJS[ibin][ir];
        }
    }
    
    delete deltaR;
    delete leadingFrac;
}

void hist_class::Write()
{
    TString out_name ;
    TString dataType ; 
    if(IsMC) dataType="MC" ;
    else dataType="DATA";
    if(bkgphicut==0.) {
      if(IsMC)
        out_name=Form("%s%s_JetPt%.f_%.fTrk%.f_BkgEta%.fPhi%.f_CenBin%d_Nrbin%d_Pthat%d%s",dataType.Data(),coll.Data(),leadingjetcut,subleadjetcut,trackcut, bkgetacut*10,bkgphicut,nbin,nrbin,pthat, intputFile.Data());
      else
        out_name=Form("%s%s_JetPt%.f_%.fTrk%.f_BkgEta%.fPhi%.f_CenBin%d_Nrbin%d_%s",dataType.Data(),coll.Data(),leadingjetcut,subleadjetcut,trackcut, bkgetacut*10,bkgphicut,nbin,nrbin, intputFile.Data());
    }
    else {
      if(IsMC)
        out_name=Form("%s%s_JetPt%.f_%.fTrk%.f_BkgEta%.fPhi%.f_CenBin%d_Nrbin%d_Pthat%d%s",dataType.Data(),coll.Data(),leadingjetcut,subleadjetcut,trackcut, bkgetacut*10,TMath::Pi()/bkgphicut,nbin,nrbin,pthat, intputFile.Data());
      else 
        out_name=Form("%s%s_JetPt%.f_%.fTrk%.f_BkgEta%.fPhi%.f_CenBin%d_Nrbin%d_%s",dataType.Data(),coll.Data(),leadingjetcut,subleadjetcut,trackcut, bkgetacut*10,TMath::Pi()/bkgphicut,nbin,nrbin, intputFile.Data());
    }
    //sprintf(out_name,Form("%s_ptCut%3f_%2f_CenBin%d_%s",dataType,leadingjetcut,subleadjetcut,nbin,intputFile));
    TFile *out_file = new TFile(Form("/net/hidsk0001/d00/scratch/maoyx/JetShape//%s",out_name.Data()), "RECREATE");
    for(int ibin = 0 ; ibin <nbin; ibin++){
        NEvents[ibin]->Write();
        NJets[ibin]->Write();
        Ntrack[ibin]->Write();
        jetpt[ibin]->Write();
        subjetpt[ibin]->Write();
        dijet[ibin]->Write();
        Rjj[ibin]->Write();  
        dihadron[ibin]->Write();
        Ajj[ibin]->Write();
        trackpt[ibin]->Write();
        NeutralPt[ibin]->Write();
        PhotonPt[ibin]->Write();
        ChargePt[ibin]->Write();    
        SumNePt[ibin]->Write();
        SumPhPt[ibin]->Write();
        SumChPt[ibin]->Write(); 
        NeutralMult[ibin]->Write();
        PhotonMult[ibin]->Write();
        ChargeMult[ibin]->Write();    
        jetfrag[ibin]->Write();
        subjetfrag[ibin]->Write();
        bkgNeutralPt[ibin]->Write();
        bkgPhotonPt[ibin]->Write();
        bkgChargePt[ibin]->Write();    
        bkgSumNePt[ibin]->Write();
        bkgSumPhPt[ibin]->Write();
        bkgSumChPt[ibin]->Write(); 
        bkgNeutralMult[ibin]->Write();
        bkgPhotonMult[ibin]->Write();
        bkgChargeMult[ibin]->Write();   
        
        for(int ir = 0 ; ir <nrbin; ir++){
            DiffJS[ibin][ir]->Write();
            IntJS[ibin][ir]->Write();
            subDiffJS[ibin][ir]->Write();
            subIntJS[ibin][ir]->Write();
            bkgDiffJS[ibin][ir]->Write();
            bkgIntJS[ibin][ir]->Write();
            bkgsubDiffJS[ibin][ir]->Write();
            bkgsubIntJS[ibin][ir]->Write();
        }
    }
    
    deltaR->Write();
    leadingFrac->Write();
    out_file->Close();
    cout <<"Output file: " <<Form("%s",out_name.Data()) <<endl ;
    
}


int main()
{
    // gROOT->ForceStyle(0);
    
    std::cout << "start working\n";
    if(!IsMC) 
      //    dataPath="/Volumes/WORKDISK/backup/pc93/2012-01-26/WorkSpace/data/HI2011/forest";
    dataPath="/mnt/hadoop/cms/store/user/pelin/ppdijet" ; //mit pp data path
    else 
      //  dataPath= "/Users/ymao/group/CMS/hiForest"; //local analysis
   dataPath= Form("/mnt/hadoop/cms/store/user/mnguyen/MC_Production/Pythia%d_HydjetDrum_mix01",pthat); //mit path for HI
    //    dataPath= Form("/mnt/hadoop/cms/store/user/mnguyen/MC_Production/pythia%d",pthat); //mit path for pp
    if(!IsMC){  //real data analysis
        if(coll=="HI")             
            intputFile="HiForestData2011_FullStat_JSON_Dijet_v7.root";
        else 
            intputFile="merged_pp2760_AllPhysics_Part_Prod03.root";
        //intputFile="mit_pelin_dijet_hiforest_pp_276TeV_data.root";
    }
    else { //MC sample
        if(coll=="HI")             
	  //    intputFile=Form("mit_pawan_PbPb2760_Dijet_Hydrum_dijet%d.root", pthat);
         intputFile="merged_HydjetDrum.root";
        else 
            intputFile="merged_hiForest.root";
       //  intputFile="mit_mnguyen_pp2760_pythia80_dijet80.root";
       // intputFile=Form("mit_mnguyen_pp2760_pythia_dijet%d.root",pthat);  
    }
    TFile *my_file=TFile::Open(Form("%s/%s", dataPath.Data(),intputFile.Data()));
    cout <<"Input file" << Form("%s/%s", dataPath.Data(),intputFile.Data())<<endl ;
    
    hist_class *my_hists = new hist_class("pfjet");
    
    if(my_file->IsZombie()) {
    }
    
    TTree *evt_tree = (TTree*) my_file->Get("hiEvtAnalyzer/HiTree");
    Evt * offSel = new Evt(evt_tree);
    
    TTree *skim_tree = (TTree*) my_file->Get("skimanalysis/HltTree");
    skim * my_skim = new skim(skim_tree);
    
    
    TTree *hlt_tree = (TTree*) my_file->Get("hltanalysis/HltTree");
    //    if(coll=="HI") 
    HIHLT * trigSel = new HIHLT(hlt_tree);
    //    else 
    //        HLT * trigSel = new HLT(hlt_tree);
    
    TTree *inp_tree = (TTree*) my_file->Get("akPu3PFJetAnalyzer/t");
    akPu3PFJet * my_ct = new akPu3PFJet(inp_tree);
    
    TTree *pf_tree = (TTree*) my_file->Get("pfcandAnalyzer/pfTree");
    pfTree * pfpart = new pfTree(pf_tree);
    
    TTree *tr_tree = (TTree*) my_file->Get("anaTrack/trackTree");
    track * my_tr = new track(tr_tree);
    
    int n_evt = my_ct->fChain->GetEntriesFast();
    int curr_bin = nbin-1 ;
    cout <<"Number of events =" <<n_evt <<endl ;
    for(int evi = 0; evi < n_evt; evi++) {
        my_skim->fChain->GetEntry(evi); 
        trigSel->fChain->GetEntry(evi);
        
        int noise_evt = my_skim->pHBHENoiseFilter ;
        int ecal_noise = my_skim->phiEcalRecHitSpikeFilter ;
        if(ecal_noise==0) continue ;
        if(coll=="HI") {
            int evt_sel = my_skim->pcollisionEventSelection ;
            if(evt_sel==0) continue ;
        }
        if(!IsMC){
            if(noise_evt==0) continue ;
            //if(coll=="HI")
            int jetTr1 = trigSel->HLT_HIJet65_v1 ;
            int jetTr2 = trigSel->HLT_HIJet80_v1 ;
            // else 
	    //   int jetTr1 = trigSel->HLT_Jet40_v1 ;
	    //  int jetTr2 = trigSel->HLT_Jet60_v1 ;
            //                
            if(jetTr1==0 || jetTr2==0) continue ;
        }
        
        my_ct->fChain->GetEntry(evi);
        my_tr->fChain->GetEntry(evi);
        pfpart->fChain->GetEntry(evi);
        // std::cout <<"!!!!!!!!!!!!!!still working\n";
        
        //if there is no jets or no PF candidates, skip the event
        if(my_ct->nref==0) continue ;
        if(pfpart->nPFpart==0) continue ;
        
        if(coll=="HI"){
            offSel->fChain->GetEntry(evi); 
            int centrality = offSel->hiBin*2.5 ;
            
            for(int ibin = 0 ; ibin <nbin; ibin++){
                if(centrality >=centr[ibin] && centrality<centr[ibin+1]) curr_bin = ibin ;
            }
        }
        else curr_bin=nbin-1 ;
        //   cout << "  cent_bin:" <<curr_bin <<endl ;
        
        if(evi%10000==1)cout <<" coll = " <<coll <<" MC = " <<IsMC <<" evt = " <<evi <<endl ;
        
        my_hists->Ntrack[curr_bin]->Fill(my_tr->fChain->GetEntry(evi));
        //cout <<my_hists->NEvents[curr_bin]->GetName() <<endl;
        my_hists->NEvents[curr_bin]->Fill(my_ct->fChain->GetEntry(evi));
        //cout << "start working222222\n";
        
        
        ///--------------------------------------------------------------------
        /// ---- JETS  ----- ///////////////////////////////////////////
        ///--------------------------------------------------------------------
        
        //define the variables used
        double lead_pt=0. ;
        int lead_index=-1 ;
        double sublead_pt=0. ;
        int sublead_index=-1 ;      
        double lead_tr=0.;
        int tr_index = -1 ;
        int njets = 0 ;
        double subjet_phi = 0. ;
        double subjet_eta = 0. ;
        double bkg_subphi = 0. ;
        double bkg_subeta = 0. ; 
        for(int j4i = 0; j4i < my_ct->nref ; j4i++) {
            
            double jet_pt= my_ct->jtpt[j4i];
            if(TMath::Abs(my_ct->jteta[j4i])>etacut) continue ;
            if(jet_pt<leadingjetcut) continue ;
            if(jet_pt >lead_pt){
                lead_pt=jet_pt;
                lead_index=j4i;
            }
        } //search for leading jet loop
        if(lead_index!=-1){ //if leading jet found
            double jet_phi =my_ct->jtphi[lead_index];
            double jet_eta = my_ct->jteta[lead_index];
            double bkg_phi = jet_phi+bkgphicut;
            double bkg_eta = jet_eta+bkgetacut;
            my_hists->jetpt[curr_bin]->Fill(lead_pt);
            
            //search for subleading jet
            for(int ijet = 0 ; ijet <my_ct->nref; ijet++){
                if(ijet==lead_index) continue ;
                if(TMath::Abs(my_ct->jteta[ijet])>etacut) continue ;
                double deltaphi = my_ct->jtphi[ijet]-jet_phi ;
                if(deltaphi>=TMath::Pi()) deltaphi-=TMath::TwoPi();
                if(deltaphi<-TMath::Pi()) deltaphi+=TMath::TwoPi();
                if(TMath::Abs(deltaphi)<dphicut) continue ;

                if(my_ct->jtpt[ijet]<subleadjetcut) continue ;            
                
                if(my_ct->jtpt[ijet] >sublead_pt){
                    sublead_pt=my_ct->jtpt[ijet];
                    sublead_index=ijet;
                }
            }  //end of subleading jet search
            
            if(sublead_index!=-1){ //subleading jet found
                subjet_phi =my_ct->jtphi[sublead_index];
                subjet_eta = my_ct->jteta[sublead_index];
                bkg_subphi = subjet_phi+bkgphicut;
                bkg_subeta = subjet_eta+bkgetacut;  
                double dphi = my_ct->jtphi[sublead_index]-jet_phi;
                if(dphi <-TMath::PiOver2())dphi+=TMath::TwoPi();
                //if(dphi >=TMath::TwoPi()/2.)dphi-=TMath::TwoPi(); 
                double Aj = TMath::Abs((lead_pt-sublead_pt)/(lead_pt+sublead_pt)) ;
                my_hists->subjetpt[curr_bin]->Fill(sublead_pt);
                my_hists->dijet[curr_bin]->Fill(dphi);
                my_hists->Ajj[curr_bin]->Fill(Aj);
                my_hists->Rjj[curr_bin]->Fill(sublead_pt/lead_pt); 
                if(TMath::Sqrt((bkg_phi-jet_phi)*(bkg_phi-jet_phi)+(bkg_eta-jet_eta)*(bkg_eta-jet_eta))<conesize){
                    printf ("jet bkg inside leading jet cone \n");
                    continue ;
                }
                if(TMath::Sqrt((bkg_subphi-subjet_phi)*(bkg_subphi-subjet_phi)+(bkg_subeta-subjet_eta)*(bkg_subeta-subjet_eta))<conesize){
                    printf ("subjet bkg inside subleading jet cone \n");
                    continue ;
                }
                if(TMath::Sqrt((bkg_subphi-jet_phi)*(bkg_subphi-jet_phi)+(bkg_subeta-jet_eta)*(bkg_subeta-jet_eta))<conesize){
                    printf ("subjet bkg inside leading jet cone \n");
                    continue ;
                }
                if(TMath::Sqrt((bkg_phi-subjet_phi)*(bkg_phi-subjet_phi)+(bkg_eta-subjet_eta)*(bkg_eta-subjet_eta))<conesize){
                    printf ("jet bkg inside subleading jet cone \n");
                    continue ;
                }
            }
            //for PF analysis
            int neutral = 0 ;
            int photon = 0 ;
            int charge = 0 ;
            double sumchpt =0. ;
            double sumphpt =0. ;
            double sumnept =0. ;
            double rho[nrbin] ;
            double psi[nrbin] ;
            double subrho[nrbin] ;
            double subpsi[nrbin] ;
            double dR = 0. ;
            double sumpt = 0. ;
            double sumsubpt = 0. ;
            double meanphi = 0.;
            double meaneta = 0. ;
            int bkgneutral = 0 ;
            int bkgphoton = 0 ;
            int bkgcharge = 0 ;
            double bkgsumchpt =0. ;
            double bkgsumphpt =0. ;
            double bkgsumnept =0. ;
            double bkg_dr = 0. ;
            double bkgrho[nrbin];
            double bkgpsi[nrbin] ;
            double bkgsubrho[nrbin] ;
            double bkgsubpsi[nrbin] ;
            double bkgsumpt = 0. ;
            double bkgsumsubpt = 0. ;
            for(int ir = 0 ; ir <nrbin ; ir++){
                rho[ir]=0. ;
                psi[ir]= 0.;
                subrho[ir]=0.;
                subpsi[ir]=0.;
                bkgrho[ir]=0.;
                bkgpsi[ir]=0. ;
                bkgsubrho[ir]=0.;
                bkgsubpsi[ir]=0.;
            }
            for(int ipart = 0 ; ipart < pfpart->nPFpart ; ipart++){
                double pf_pt = pfpart->pfPt[ipart];
                double pf_phi = pfpart->pfPhi[ipart];
                double pf_eta = pfpart->pfEta[ipart];
                int partid = pfpart->pfId[ipart];  
                if(partid==1 || partid==3) continue ;
                //   cout <<"eta" <<pfeta <<endl;
              //  if(TMath::Abs(pf_eta)>tracketacut) continue ;
                if(pf_pt<trackcut) continue ;
                dR =TMath::Sqrt((pf_phi-jet_phi)*(pf_phi-jet_phi)+(pf_eta-jet_eta)*(pf_eta-jet_eta));
                my_hists->deltaR->Fill(dR);
                // cout << "R =" <<dR <<endl ;
                if(dR<=conesize){
                    sumpt+=pf_pt;
                    meaneta+=pf_pt*pf_eta;
                    meanphi+=pf_pt*pf_phi;
                    my_hists->jetfrag[curr_bin]->Fill(lead_pt, TMath::Log(lead_pt/pf_pt));
                    if(partid==5) {
                        my_hists->NeutralPt[curr_bin]->Fill(lead_pt, pf_pt);
                        sumnept+=pf_pt ;
                        neutral++ ;
                    }
                    if(partid==4) {
                        my_hists->PhotonPt[curr_bin]->Fill(lead_pt, pf_pt);
                        sumphpt+=pf_pt ;
                        photon++ ;
                    }
                    
                    for(int ir = 0 ; ir <nrbin; ir++){
                        if(dR>rbin[ir]&&dR<=rbin[ir+1])
                            rho[ir]+=pf_pt ;
                        if(dR<=rbin[ir+1]) psi[ir]+=pf_pt ;
                    }
                } //pf particle inside the leading jet
                else {  //for PF particle outside leading jet
                    if(sublead_index!=-1) {
                        double dR2 =TMath::Sqrt((pf_phi-subjet_phi)*(pf_phi-subjet_phi)+(pf_eta-subjet_eta)*(pf_eta-subjet_eta));
                        if(dR2<=conesize){
                            sumsubpt+=pf_pt;
                            my_hists->subjetfrag[curr_bin]->Fill(TMath::Log(lead_pt/pf_pt), TMath::Log(sublead_pt/pf_pt));
                            for(int ir = 0 ; ir <nrbin; ir++){
                                if(dR2<=rbin[ir+1]) subpsi[ir]+=pf_pt ;
                                if(dR2>rbin[ir]&&dR2<=rbin[ir+1])
                                    subrho[ir]+=pf_pt ;
                            }
                            
                        } //pf particles inside sub jet 
                        else { //PF outside both jets
                            double bkgsub_dr = TMath::Sqrt((pf_phi-bkg_subphi)*(pf_phi-bkg_subphi)+(pf_eta-bkg_subeta)*(pf_eta-bkg_subeta));
                            if(bkgsub_dr<=conesize){
                                bkgsumsubpt+=pf_pt;
                            } //tracks inside bkg cone
                            for(int ir = 0 ; ir <nrbin; ir++){
                                if(bkgsub_dr>rbin[ir]&&bkgsub_dr<=rbin[ir+1])
                                    bkgsubrho[ir]+=pf_pt ;
                                if(bkgsub_dr<=rbin[ir+1]) bkgsubpsi[ir]+=pf_pt ;
                             //   if(ir==9) cout <<"psi ="<<bkgsubpsi[ir]<<" sum" <<sumsubpt<<endl ;
                            }
                            
                        } //outside both jet cone
                    } //sub leading jet found
                    
                    bkg_dr = TMath::Sqrt((pf_phi-bkg_phi)*(pf_phi-bkg_phi)+(pf_eta-bkg_eta)*(pf_eta-bkg_eta));
                    if(bkg_dr<=conesize){
                        bkgsumpt+=pf_pt;
                        if(partid==5) { //neutral particles
                            my_hists->bkgNeutralPt[curr_bin]->Fill(lead_pt, pf_pt);
                            bkgsumnept+=pf_pt ;
                            bkgneutral++ ;
                        }
                        if(partid==4) { //photon
                            my_hists->bkgPhotonPt[curr_bin]->Fill(lead_pt, pf_pt);
                            bkgsumphpt+=pf_pt ;
                            bkgphoton++ ;
                        } 
                        for(int ir = 0 ; ir <nrbin; ir++){
                            if(bkg_dr>rbin[ir]&&bkg_dr<=rbin[ir+1])
                                bkgrho[ir]+=pf_pt ;
                            if(bkg_dr<=rbin[ir+1]) bkgpsi[ir]+=pf_pt ;
                        }
                    }  //bkg cone
                    
                } //PF outside jet cone
            } //PF analysis 
            //    cout <<"sum of Ne+Ch+Ph: " <<sumnept+sumphpt+sumchpt<<endl;
            
            sumnept/=lead_pt ;
            sumphpt/=lead_pt ;
            //            sumchpt/=lead_pt ;
            my_hists->NeutralMult[curr_bin]->Fill(lead_pt, neutral);
            my_hists->PhotonMult[curr_bin]->Fill(lead_pt, photon);
            //          my_hists->ChargeMult[curr_bin]->Fill(charge);
            my_hists->SumNePt[curr_bin]->Fill(lead_pt, sumnept);
            my_hists->SumPhPt[curr_bin]->Fill(lead_pt, sumphpt);
            bkgsumnept/=lead_pt ;
            bkgsumphpt/=lead_pt ;
            //            sumchpt/=lead_pt ;
            my_hists->bkgNeutralMult[curr_bin]->Fill(lead_pt, bkgneutral);
            my_hists->bkgPhotonMult[curr_bin]->Fill(lead_pt, bkgphoton);
            //          my_hists->ChargeMult[curr_bin]->Fill(charge);
            my_hists->bkgSumNePt[curr_bin]->Fill(lead_pt, bkgsumnept);
            my_hists->bkgSumPhPt[curr_bin]->Fill(lead_pt, bkgsumphpt);
            
            //for track analysis
            double sumtrk = 0. ;
            for(int itr = 0 ; itr < my_tr->nTrk ; itr++){
                double tr_pt = my_tr->trkPt[itr];
                double tr_phi = my_tr->trkPhi[itr];
                double tr_eta = my_tr->trkEta[itr];
               // if(TMath::Abs(tr_eta)>tracketacut) continue ;
                if(tr_pt<trackcut) continue ;
                double dr =TMath::Sqrt((tr_phi-jet_phi)*(tr_phi-jet_phi)+(tr_eta-jet_eta)*(tr_eta-jet_eta));
                my_hists->deltaR->Fill(dr);         
                if(dr <=conesize){
                    sumtrk+=tr_pt ;
                    sumpt+=tr_pt ;
                    meaneta+=tr_pt*tr_eta;
                    meanphi+=tr_pt*tr_phi;
                    my_hists->jetfrag[curr_bin]->Fill(lead_pt, TMath::Log(lead_pt/tr_pt));
                    my_hists->trackpt[curr_bin]->Fill(tr_pt);
                    my_hists->ChargePt[curr_bin]->Fill(lead_pt, tr_pt);
                    sumchpt+=tr_pt ;
                    charge++ ;
                    
                    //                my_hists->dihadron[curr_bin]->Fill(tr_phi-jet_phi, 0.5);
                    //                my_hists->dihadron[curr_bin]->Fill(TMath::Abs(tr_phi-my_ct->jtphi[sublead_index]), 0.5);
                    if(tr_pt >lead_tr) {
                        lead_tr = tr_pt ;
                        tr_index = itr ;
                    }
                    for(int ir = 0 ; ir <nrbin; ir++){
                        if(dr>rbin[ir]&&dr<=rbin[ir+1])
                            rho[ir]+=tr_pt ;
                        if(dr<=rbin[ir+1]) psi[ir]+=tr_pt ;
                    }
                    
                    
                } //tracks inside for jet
                else { //treck outside jetcone 
                    if(sublead_index!=-1) {
                        double dr2 =TMath::Sqrt((tr_phi-subjet_phi)*(tr_phi-subjet_phi)+(tr_eta-subjet_eta)*(tr_eta-subjet_eta));
                        if(dr<conesize && dr2<conesize) {
                            cout <<"!!!! two jets are overlap with track: "<<itr <<"eta: " <<tr_eta <<" phi:" <<tr_phi << endl;
                            continue ;
                        }        
                        if(dr2<=conesize) {
                            sumsubpt+=tr_pt;
                            my_hists->subjetfrag[curr_bin]->Fill(TMath::Log(lead_pt/tr_pt), TMath::Log(sublead_pt/tr_pt));
                            for(int ir = 0 ; ir <nrbin; ir++){
                                if(dr2<=rbin[ir+1]) subpsi[ir]+=tr_pt ;
                                if(dr2>rbin[ir]&&dr2<=rbin[ir+1])
                                    subrho[ir]+=tr_pt ;

                            }
                            
                        } //track inside the second jet
                        else if(dr2>conesize&&dr>conesize){ //PF outside both jet
                            double bkgsub_dr = TMath::Sqrt((tr_phi-bkg_subphi)*(tr_phi-bkg_subphi)+(tr_eta-bkg_subeta)*(tr_eta-bkg_subeta));
                            if(bkgsub_dr<=conesize) {
                                bkgsumsubpt+=tr_pt;
                                for(int ir = 0 ; ir <nrbin; ir++){
                                    if(bkgsub_dr>rbin[ir]&&bkgsub_dr<=rbin[ir+1])
                                        bkgsubrho[ir]+=tr_pt ;
                                    if(bkgsub_dr<=rbin[ir+1]) bkgsubpsi[ir]+=tr_pt ;
                                }
                                
                            } //track inside subject background cone
                        } //outside both jet cone
                    } //subjet found
                    
                    bkg_dr = TMath::Sqrt((tr_phi-bkg_phi)*(tr_phi-bkg_phi)+(tr_eta-bkg_eta)*(tr_eta-bkg_eta));            
                    if(bkg_dr<=conesize){
                        my_hists->bkgChargePt[curr_bin]->Fill(lead_pt, tr_pt);
                        bkgsumchpt+=tr_pt ;
                        bkgcharge++ ;  
                        bkgsumpt+=tr_pt ;
                        for(int ir = 0 ; ir <nrbin; ir++){
                            if(bkg_dr>rbin[ir]&&bkg_dr<=rbin[ir+1])
                                bkgrho[ir]+=tr_pt ;
                            if(bkg_dr<=rbin[ir+1]) bkgpsi[ir]+=tr_pt ;
                        }
                    }  //bkg cone                
                } //track outside jet cone
            } //track loop
            sumchpt/=lead_pt ;
            my_hists->ChargeMult[curr_bin]->Fill(lead_pt, charge);
            my_hists->SumChPt[curr_bin]->Fill(lead_pt, sumchpt); 
            bkgsumchpt/=lead_pt ;
            my_hists->bkgChargeMult[curr_bin]->Fill(lead_pt, bkgcharge);
            my_hists->bkgSumChPt[curr_bin]->Fill(lead_pt, bkgsumchpt); 
            
            meanphi/=sumpt;
            meaneta/=sumpt;
            // rho/=deltacone ;
            for(int ir = 0 ; ir <nrbin; ir++){
                psi[ir]/=sumpt;
                rho[ir]/=sumpt;
                subpsi[ir]/=sumsubpt;
                subrho[ir]/=sumsubpt;
                bkgpsi[ir]/=sumpt;
                bkgrho[ir]/=sumpt;
                bkgsubpsi[ir]/=sumsubpt;
                bkgsubrho[ir]/=sumsubpt;
                my_hists->DiffJS[curr_bin][ir]->Fill(lead_pt, rho[ir]);
                my_hists->IntJS[curr_bin][ir]->Fill(lead_pt, psi[ir]);
                my_hists->subDiffJS[curr_bin][ir]->Fill(sublead_pt, subrho[ir]);
                my_hists->subIntJS[curr_bin][ir]->Fill(sublead_pt, subpsi[ir]);
                // rho/=deltacone ;
                my_hists->bkgDiffJS[curr_bin][ir]->Fill(lead_pt, bkgrho[ir]);
                //   my_hists->IntJS[curr_bin]->Fill(lead_pt, 1-psi);
                my_hists->bkgIntJS[curr_bin][ir]->Fill(lead_pt, bkgpsi[ir]);
                my_hists->bkgsubDiffJS[curr_bin][ir]->Fill(sublead_pt, bkgsubrho[ir]);
                my_hists->bkgsubIntJS[curr_bin][ir]->Fill(sublead_pt, bkgsubpsi[ir]);        
            }
            //  cout <<"jet : " <<lead_pt << " sum track:" <<sumtrk<<endl ;
            
            if(tr_index!=-1){ //doing leading track-hadron correlations
                double leading_phi =my_tr->trkPhi[tr_index];
                double leading_eta = my_tr->trkEta[tr_index];
                for(int itr = 0 ; itr < my_tr->nTrk ; itr++){
                    if(itr==tr_index) continue ;
                    if(TMath::Abs(my_tr->trkEta[itr])>tracketacut) continue ;
                    if(my_tr->trkPt[itr]<trackcut) continue ;
                    double lhdphi = leading_phi-my_tr->trkPhi[itr];
                    if(lhdphi <-TMath::PiOver2())lhdphi+=TMath::TwoPi();
                    double lhdeta = leading_eta-my_tr->trkEta[itr];
                    
                    my_hists->dihadron[curr_bin]->Fill(lhdphi, lhdeta);
                }                
            }
            njets++ ;
        }//leading jet found
        if(lead_tr!=0 && lead_pt!=0)my_hists->leadingFrac->Fill(lead_tr/lead_pt);
        if(njets)my_hists->NJets[curr_bin]->Fill(njets);
    }  ///event loop
    
    my_hists->Write();
    // my_hists->Delete();
    delete my_hists;
    std::cout << "working done\n";
}





#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"
#include "class_def/skim.h"
#include "class_def/Evt.h"
#include "class_def/HLT.h"
#include "class_def/track.h"
#include "class_def/akPu3PFJet.h"
#include "class_def/pfTree.h"
#include "class_def/GenParticle.h"
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

const double etacut = 2.0 ;
const double dphicut = TMath::TwoPi()/3. ;
const double leadingjetcut = 80. ;
const double subleadjetcut = 40. ;
const double trackcut = 2.;
const double tracketacut = 3.; //make sure the tracks around jet cone inside eta range

//for background cut
//const Int_t kSignEta = 1 ;
//const Int_t kSignPhi = 1 ;
//const double bkgetacut = kSignEta*0.5 ; //bkg eta range: [0., 0.5, 1.0, 1.5]
//const double bkgphicut = kSignPhi*TMath::PiOver2() ; //bkg phi[0., 1/3.,1/2.]

////for eta <= 0.5, using random cone bkg, eta reflected method for bkg
const double etalimit = 0.5 ; 

////for HI centrality bin
//const int nbin = 6 ;
//const double centr[] ={0,10,20,30,50,70,100};

const int pthat =30 ; //30 and 80 for pp; 30,50,80,120,170,200 for PbPb MC 
TString coll = "PP";

//const bool IsMC=kTRUE ;

double weight ;
TString intputFile ;

//TString dataPath="/Users/ymao/group/CMS/hiForest";
TString dataPath ;

//if it is pp, no centrality bins, only one
const int nbin = 1 ;
const double centr[] ={0,100};

class hist_class {
public:
    hist_class(TString the_desc);
    void Delete();
    void Write();
    
    TString desc;
    bool IsMC ;
    
    TH1F * NEvents[nbin];
    TH1F * NJets[nbin];
    TH1F * Ntrack[nbin];
    TH1F * jetpt[nbin];
    TH1F * subjetpt[nbin];
    TH2F * dijet[nbin];
    TH1F * Rjj[nbin];
    TH1F * Ajj[nbin] ;
    TH1F * trackpt[nbin];
    
    TH2F * jetfrag[nbin] ;
    TH2F * subjetfrag[nbin] ;
    TH1F * deltaR;
    TH1D * CenBin;
    
    //for jet shape variables
    TH2F * ChargePt[nbin][nrbin];
    TH2F * SumChPt[nbin][nrbin];
    TH2F * ChargeMult[nbin][nrbin];   
    TH2F * DiffJS[nbin][nrbin]; //differential jet shapes (pho(r)) hist.
    TH2F * IntJS[nbin][nrbin]; //Integrated jet shapes (psi(r)) hist.
    //  TH2F * dphiJS[nbin]; //phi diviration from jet phi 
    //   TH2F * detaJS[nbin] ; //eta diviration from jet eta 
    TH2F * subDiffJS[nbin][nrbin]; //differential sub-jet shapes (pho(r)) hist.
    TH2F * subIntJS[nbin][nrbin]; //Integrated sub-jet shapes (psi(r)) hist.
    
    //for jet shape backgroun study
    TH2F * bkgChargePt[nbin][nrbin];
    TH2F * bkgSumChPt[nbin][nrbin];
    TH2F * bkgChargeMult[nbin][nrbin];   
    TH2F * bkgDiffJS[nbin][nrbin]; //differential jet shapes (pho(r)) hist.
    TH2F * bkgIntJS[nbin][nrbin]; //Integrated jet shapes (psi(r)) hist.
    TH2F * bkgsubDiffJS[nbin][nrbin]; //differential sub-jet shapes (pho(r)) hist.
    TH2F * bkgsubIntJS[nbin][nrbin]; //Integrated sub-jet shapes (psi(r)) hist. 
    
};

hist_class::hist_class(TString the_desc)
{
    
    desc = the_desc;
    IsMC =kTRUE ;
    for(int ibin = 0 ; ibin <nbin; ibin++){
        NEvents[ibin] = new TH1F(Form("Nevents_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("Nevents_%.f-%.f%%",centr[ibin],centr[ibin+1]), 100, 0.5, 100.5);
        NJets[ibin] = new TH1F(Form("NJets_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("NJets_%.f-%.f%%",centr[ibin],centr[ibin+1]), 100, 0.5, 100.5);
        Ntrack[ibin] = new TH1F(Form("Ntracks_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("Ntracks_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 1., 1001);
        jetpt[ibin] = new TH1F(Form("jetpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("jetpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0.5, 500.5);
        subjetpt[ibin] = new TH1F(Form("subjetpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("subjetpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0.5, 500.5);
        dijet[ibin] = new TH2F(Form("dphi_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("dphi_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0.5, 500.5,120, -4.05, 8.05);
        //        dijet[ibin] = new TH2F(Form("dphi_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("dphi_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0.5, 500.5,30, 0.,TMath::Pi());
        dijet[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        dijet[ibin]->GetYaxis()->SetTitle("#Delta#phi");
        Rjj[ibin] = new TH1F(Form("Rjj_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("Rjj_%.f-%.f%%",centr[ibin],centr[ibin+1]), 100, 0.01, 2.01);        
        Ajj[ibin] = new TH1F(Form("Aj_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("Aj_%.f-%.f%%",centr[ibin],centr[ibin+1]), 100, 0.005, 1.005);
        trackpt[ibin] = new TH1F(Form("trackpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("trackpt_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0.5, 500.5); 
        
        jetfrag[ibin] = new TH2F(Form("FFleading_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("FFleading_%.f-%.f%%",centr[ibin],centr[ibin+1]), 500, 0.5, 500.5, 100, 0.05, 10.05);
        jetfrag[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        jetfrag[ibin]->GetYaxis()->SetTitle("#xi = ln(p_{T}^{jet}/p_{T}^{h})");
        subjetfrag[ibin] = new TH2F(Form("FFsubleading_%.f-%.f%%",centr[ibin],centr[ibin+1]), Form("FFsubleading_%.f-%.f%%",centr[ibin],centr[ibin+1]), 100, 0.05, 10.05,100, 0.05, 10.05);
        subjetfrag[ibin]->GetXaxis()->SetTitle("#xi = ln(p_{T}^{jet1}/p_{T}^{h})");
        subjetfrag[ibin]->GetYaxis()->SetTitle("#xi = ln(p_{T}^{jet2}/p_{T}^{h})");
        
        for(int ir = 0 ; ir <nrbin; ir++){
            ChargePt[ibin][ir] = new TH2F(Form("chargeptdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("chargeptdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0.5, 500.5, 500, 0.5, 500.5);
            ChargePt[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            ChargePt[ibin][ir]->GetYaxis()->SetTitle("p_{T} (GeV/c)");
            SumChPt[ibin][ir] = new TH2F(Form("sumchptdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("sumchargeptdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0.5, 500.5, 100, 0.005, 1.005);
            SumChPt[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            SumChPt[ibin][ir]->GetYaxis()->SetTitle("#Sigma p_{T}^{h^{#pm}}/p_{T}^{jet}");  
            ChargeMult[ibin][ir] = new TH2F(Form("ChMultdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("ChMultdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0.5, 500.5, 100, 0.5, 100.5);
            ChargeMult[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            ChargeMult[ibin][ir]->GetYaxis()->SetTitle("# of Charge");   
            DiffJS[ibin][ir] = new TH2F(Form("differentialJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("differentialJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0.5, 500.5, 150, 0.005, 1.505);
            DiffJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            DiffJS[ibin][ir]->GetYaxis()->SetTitle("#rho (r)");
            IntJS[ibin][ir] = new TH2F(Form("IntegratedJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("IntegratedJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0.5, 500.5, 150, 0.005, 1.505);
            IntJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            IntJS[ibin][ir]->GetYaxis()->SetTitle(Form("#psi(r=%1.2f)",deltacone*(ir+1)));
            
            subDiffJS[ibin][ir] = new TH2F(Form("subjetdifferentialJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("subjetdifferentialJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0.5, 500.5, 150, 0.005, 1.505);
            subDiffJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            subDiffJS[ibin][ir]->GetYaxis()->SetTitle("#rho (r)");
            subIntJS[ibin][ir] = new TH2F(Form("subjetIntegratedJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("subjetIntegratedJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0.5, 500.5, 150, 0.005, 1.505);
            subIntJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            subIntJS[ibin][ir]->GetYaxis()->SetTitle(Form("#psi(r=%1.2f)",deltacone*(ir+1)));
            
            //for bkg histos.
            bkgChargePt[ibin][ir] = new TH2F(Form("bkgchargeptdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("bkgchargeptdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0.5, 500.5, 500, 0.5, 500.5);
            bkgChargePt[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            bkgChargePt[ibin][ir]->GetYaxis()->SetTitle("p_{T} (GeV/c)");
            bkgSumChPt[ibin][ir] = new TH2F(Form("bkgsumchptdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("bkgsumchargeptdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0.5, 500.5, 100, 0.005, 1.005);
            bkgSumChPt[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            bkgSumChPt[ibin][ir]->GetYaxis()->SetTitle("#Sigma p_{T}^{h^{#pm}}/p_{T}^{jet}");    
            bkgChargeMult[ibin][ir] = new TH2F(Form("bkgChMultdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("bkgChMultdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0.5, 500.5, 100, 0.5, 100.5);
            bkgChargeMult[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            bkgChargeMult[ibin][ir]->GetYaxis()->SetTitle("# of Charge");
            
            bkgDiffJS[ibin][ir] = new TH2F(Form("bkgdifferentialJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("bkgdifferentialJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0.5, 500.5, 150, 0.005, 1.505);
            bkgDiffJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            bkgDiffJS[ibin][ir]->GetYaxis()->SetTitle("#rho (r)");
            bkgIntJS[ibin][ir] = new TH2F(Form("bkgIntegratedJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("bkgIntegratedJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0.5, 500.5, 150, 0.005, 1.505);
            bkgIntJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            bkgIntJS[ibin][ir]->GetYaxis()->SetTitle(Form("#psi(r=%1.2f)",deltacone*(ir+1)));
            bkgsubDiffJS[ibin][ir] = new TH2F(Form("bkgsubjetdifferentialJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("bkgsubjetdifferentialJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0.5, 500.5, 150, 0.005, 1.505);
            bkgsubDiffJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            bkgsubDiffJS[ibin][ir]->GetYaxis()->SetTitle("#rho (r)");
            bkgsubIntJS[ibin][ir] = new TH2F(Form("bkgsubjetIntegratedJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("bkgsubjetIntegratedJSdR%.f_%.f_Cen%.f-%.f%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0.5, 500.5, 150, 0.005, 1.505);
            bkgsubIntJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            bkgsubIntJS[ibin][ir]->GetYaxis()->SetTitle(Form("#psi(r=%1.2f)",deltacone*(ir+1)));    
            
        }
        
    }
    
    // if(!deltaR)
    deltaR = new TH1F((TString) (desc + "_deltaR"), "", 100, 0., 10.);
    CenBin = new TH1D((TString) (desc + "_Cent"), "", 40, 0, 40);
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
        delete Ajj[ibin];
        delete trackpt[ibin];
        
        delete jetfrag[ibin];
        delete subjetfrag[ibin];
        
        for(int ir = 0 ; ir <nrbin; ir++){
            delete ChargePt[ibin][ir];
            delete SumChPt[ibin][ir];
            delete ChargeMult[ibin][ir];
            delete DiffJS[ibin][ir];
            delete IntJS[ibin][ir];
            delete subDiffJS[ibin][ir];
            delete subIntJS[ibin][ir];
            delete bkgChargePt[ibin][ir];      
            delete bkgSumChPt[ibin][ir];
            delete bkgChargeMult[ibin][ir];
            delete bkgDiffJS[ibin][ir];
            delete bkgIntJS[ibin][ir];
            delete bkgsubDiffJS[ibin][ir];
            delete bkgsubIntJS[ibin][ir];
        }
    }
    
    delete deltaR;
    delete CenBin;
}

void hist_class::Write()
{
    TString out_name ;
    TString dataType ; 
    if(IsMC) dataType="MC" ;
    else dataType="DATA";
        out_name=Form("%s%s_GenJetPt%.f_%.fTrk%.fEta%.f_BkgEtaBound%.f_CenBin%d_Nrbin%d_Pthat%d%s",dataType.Data(),coll.Data(),leadingjetcut,subleadjetcut,trackcut, etacut,etalimit*10, nbin,nrbin,pthat, intputFile.Data());
    //sprintf(out_name,Form("%s_ptCut%3f_%2f_CenBin%d_%s",dataType,leadingjetcut,subleadjetcut,nbin,intputFile));
   // TFile *out_file = new TFile(Form("/Users/ymao/group/CMS/anaOutputs/%s",out_name.Data()), "RECREATE");
         TFile *out_file = new TFile(Form("/net/hidsk0001/d00/scratch/maoyx/JetShape/%s",out_name.Data()), "RECREATE");
    for(int ibin = 0 ; ibin <nbin; ibin++){
        NEvents[ibin]->Write();
        NJets[ibin]->Write();
        Ntrack[ibin]->Write();
        jetpt[ibin]->Write();
        subjetpt[ibin]->Write();
        dijet[ibin]->Write();
        Rjj[ibin]->Write();  
        Ajj[ibin]->Write();
        trackpt[ibin]->Write();
        
        jetfrag[ibin]->Write();
        subjetfrag[ibin]->Write();
        for(int ir = 0 ; ir <nrbin; ir++){
            ChargePt[ibin][ir]->Write();    
            SumChPt[ibin][ir]->Write(); 
            ChargeMult[ibin][ir]->Write();    
            DiffJS[ibin][ir]->Write();
            IntJS[ibin][ir]->Write();
            subDiffJS[ibin][ir]->Write();
            subIntJS[ibin][ir]->Write();
            bkgChargePt[ibin][ir]->Write();    
            bkgSumChPt[ibin][ir]->Write(); 
            bkgChargeMult[ibin][ir]->Write();   
            bkgDiffJS[ibin][ir]->Write();
            bkgIntJS[ibin][ir]->Write();
            bkgsubDiffJS[ibin][ir]->Write();
            bkgsubIntJS[ibin][ir]->Write();
        }
    }
    
    deltaR->Write();
    CenBin->Write();
    out_file->Close();
    cout <<"Output file: " <<Form("%s",out_name.Data()) <<endl ;
    
}


int main()
{
    // gROOT->ForceStyle(0);
    
    hist_class *my_hists = new hist_class("pfjet");
    cout <<my_hists->IsMC<<endl ;
    double wt[40];
    if(my_hists->IsMC==kTRUE && coll=="HI"){
    //    TFile * wtfile = TFile::Open("/Users/ymao/group/CMS/PFjet/McCentralityReweight.root", "readonly");
           TFile * wtfile = TFile::Open("/net/hidsk0001/d00/scratch/maoyx/JetShape/McCentralityReweight.root", "readonly");
        TH1D * hReWt = (TH1D*)wtfile->Get("CentWeight");
        for(int ibin = 0 ; ibin < hReWt->GetNbinsX() ; ibin++){
            if(hReWt->GetBinContent(ibin)==0)
                wt[ibin]=1.;
            else       
                wt[ibin]=hReWt->GetBinContent(ibin);
        }
        wtfile->Close();
    }
    else {
        for(int ibin = 0 ; ibin < 40 ; ibin++) wt[ibin]=1. ; 
    }
    std::cout << "start working\n";
      //  dataPath= "/Users/ymao/group/CMS/hiForest"; //local analysis
           if(coll=="HI") 
                    dataPath= Form("/mnt/hadoop/cms/store/user/mnguyen/MC_Production/Pythia%d_HydjetDrum_mix01",pthat); //mit path for HI
                else    
        //        //        dataPath= Form("/mnt/hadoop/cms/store/user/mnguyen/MC_Production/pythia%d",pthat); //mit path for pp
                    dataPath= Form("/net/hisrv0001/home/icali/hadoop/Pythia/Z2/ppDijet_merged"); //mit path for pp
      
    //MC sample
        if(coll=="HI")             
        //    intputFile=Form("mit_pawan_PbPb2760_Dijet_Hydrum_dijet%d.root", pthat);
          intputFile="merged_HydjetDrum.root";
        else 
            //     intputFile="merged_hiForest.root";
            //  intputFile="mit_mnguyen_pp2760_pythia80_dijet80.root";
            intputFile=Form("pp276Dijet%d_merged.root",pthat);  
    
    TFile *my_file=TFile::Open(Form("%s/%s", dataPath.Data(),intputFile.Data()));
    cout <<"Input file" << Form("%s/%s", dataPath.Data(),intputFile.Data())<<endl ;
    
    if(my_file->IsZombie()) {
    }
    
    TTree *evt_tree = (TTree*) my_file->Get("hiEvtAnalyzer/HiTree");
    Evt * offSel = new Evt(evt_tree);
    
    TTree *skim_tree = (TTree*) my_file->Get("skimanalysis/HltTree");
    skim * my_skim = new skim(skim_tree);
    
    
    TTree *hlt_tree = (TTree*) my_file->Get("hltanalysis/HltTree");
    //    if(coll=="HI") 
    //  HIHLT * trigSel = new HIHLT(hlt_tree);
    //    else 
    HLT * trigSel = new HLT(hlt_tree);
    
    TTree *inp_tree = (TTree*) my_file->Get("akPu3PFJetAnalyzer/t");
    akPu3PFJet * my_ct = new akPu3PFJet(inp_tree);
    
    TTree *pf_tree = (TTree*) my_file->Get("pfcandAnalyzer/pfTree");
    pfTree * pfpart = new pfTree(pf_tree);
    
    TTree *tr_tree = (TTree*) my_file->Get("anaTrack/trackTree");
    track * my_tr = new track(tr_tree);
    
    //   if(my_hists->IsMC==kTRUE){
    TTree *GenPart_tree = (TTree*) my_file->Get("HiGenParticleAna/hi");
    GenParticle * my_GenPart = new GenParticle(GenPart_tree);      
    //   }
    
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
        if(my_hists->IsMC!=kTRUE){
            if(noise_evt==0) continue ;
            //if(coll=="HI")
            //            int jetTr1 = trigSel->HLT_HIJet65_v1 ;
            //            int jetTr2 = trigSel->HLT_HIJet80_v1 ;
            // else 
            int jetTr1 = trigSel->HLT_Jet40_v1 ;
            int jetTr2 = trigSel->HLT_Jet60_v1 ;
            //                
            if(jetTr1==0 || jetTr2==0) continue ;
        }
        
        my_ct->fChain->GetEntry(evi);
        my_tr->fChain->GetEntry(evi);
        pfpart->fChain->GetEntry(evi);
        if(my_hists->IsMC==kTRUE)my_GenPart->fChain->GetEntry(evi);
        // std::cout <<"!!!!!!!!!!!!!!still working\n";
        
        //if there is no jets or no PF candidates, skip the event
        if(my_ct->nref==0) continue ;
        
        if(coll=="HI"){
            offSel->fChain->GetEntry(evi);
            int hiBin = offSel->hiBin ;
            if(my_hists->IsMC==kTRUE) weight = wt[hiBin]; 
            else weight = 1. ;
            double centrality = offSel->hiBin*2.5 ;
            //   my_hists->CenBin->Fill(offSel->hiBin);
            
            for(int ibin = 0 ; ibin <nbin; ibin++){
                if(centrality >=centr[ibin] && centrality<centr[ibin+1]) curr_bin = ibin ;
            }
        }
        else {
            curr_bin=nbin-1 ;
            weight = 1. ;
        }
        //   cout << "  cent_bin:" <<curr_bin <<endl ;
        
        if(evi%10000==1)cout <<" coll = " <<coll <<" weight = " <<weight <<" evt = " <<evi <<endl ;
        
        my_hists->Ntrack[curr_bin]->Fill(my_tr->fChain->GetEntry(evi), weight);
        //cout <<my_hists->NEvents[curr_bin]->GetName() <<endl;
        //cout << "start working222222\n";
        
        
        ///--------------------------------------------------------------------
        /// ---- JETS  ----- ///////////////////////////////////////////
        ///--------------------------------------------------------------------
        
        //define the variables used
        double lead_pt=0. ;
        int lead_index=-1 ;
        double sublead_pt=0. ;
        int sublead_index=-1 ;      
        double jet_phi = -999.;
        double jet_eta = -999. ;
        double bkg_phi = -999.;
        double bkg_eta = -999.;
        
        int njets = 0 ;
        double subjet_phi = -999. ;
        double subjet_eta = -999. ;
        double bkg_subphi = -999. ;
        double bkg_subeta = -999. ; 
        
        double bkgphicut = 0. ;
        double bkgetacut = 0. ;
        
        for(int j4i = 0; j4i < my_ct->ngen ; j4i++) {
            
            double jet_pt= my_ct->genpt[j4i];
            if(TMath::Abs(my_ct->geneta[j4i])>etacut) continue ;
            if(jet_pt<leadingjetcut) continue ;
            //remove flucluation with too large pt from small MC pthat sample
            if(my_hists->IsMC==kTRUE && jet_pt>3*pthat) continue ; 
            if(jet_pt >lead_pt){
                lead_pt=jet_pt;
                lead_index=j4i;
            }
        } //search for leading jet loop
        if(lead_index<0) continue ; //no leading found
        
        //   if(lead_index!=-1){ //if leading jet found
        jet_phi =my_ct->genphi[lead_index];
        jet_eta = my_ct->geneta[lead_index];
        my_hists->jetpt[curr_bin]->Fill(lead_pt, weight);
        
        //search for subleading jet
        for(int ijet = 0 ; ijet <my_ct->ngen; ijet++){
            if(ijet==lead_index) continue ;
            if(TMath::Abs(my_ct->geneta[ijet])>etacut) continue ;
            //remove flucluation with too large pt from small MC pthat sample
            if(my_hists->IsMC==kTRUE && my_ct->genpt[ijet]>3*pthat) continue ;
            
            //                double deltaphi = my_ct->genphi[ijet]-jet_phi ;
            //                if(deltaphi>=TMath::Pi()) deltaphi-=TMath::TwoPi();
            //                if(deltaphi<-TMath::Pi()) deltaphi+=TMath::TwoPi();
            //                if(TMath::Abs(deltaphi)<dphicut) continue ;
            
            if(my_ct->genpt[ijet]<subleadjetcut) continue ;            
            
            if(my_ct->genpt[ijet] >sublead_pt){
                sublead_pt=my_ct->genpt[ijet];
                sublead_index=ijet;
            }
        }  //end of subleading jet search
        if(sublead_index<0) continue ; //no subjet found
        
        //    if(sublead_index!=-1){ //subleading jet found
        subjet_phi =my_ct->genphi[sublead_index];
        subjet_eta = my_ct->geneta[sublead_index];
        double dphi = my_ct->genphi[sublead_index]-jet_phi;
        if(dphi>=TMath::Pi()) dphi-=TMath::TwoPi();
        if(dphi<-TMath::Pi()) dphi+=TMath::TwoPi();
        my_hists->dijet[curr_bin]->Fill(lead_pt, dphi, weight);
        
        //first search for highest two jets, to remove 4 jets events if the highest two jets are at the same side
        if(TMath::Abs(dphi)<dphicut) continue ;
        
        //if(dphi >=TMath::TwoPi()/2.)dphi-=TMath::TwoPi(); 
        //if(dphi <-TMath::PiOver2())dphi+=TMath::TwoPi();
        double Aj = TMath::Abs((lead_pt-sublead_pt)/(lead_pt+sublead_pt)) ;
        my_hists->subjetpt[curr_bin]->Fill(sublead_pt, weight);
        //                //in order to compare Pelin's delta phi (werid bins)
        //                if(dphi>TMath::Pi())dphi-=TMath::TwoPi();
        //                my_hists->dijet[curr_bin]->Fill(lead_pt, TMath::Abs(dphi));
        my_hists->Ajj[curr_bin]->Fill(Aj, weight);
        my_hists->Rjj[curr_bin]->Fill(sublead_pt/lead_pt, weight);
        njets++ ;        
        my_hists->NEvents[curr_bin]->Fill(my_ct->fChain->GetEntry(evi), weight);
        
        //set background cone 
        bkgphicut = TMath::Abs(jet_phi-subjet_phi)/2. ;
        bkgetacut = TMath::Abs(jet_eta-subjet_eta)/2. ;
        
        //   cout <<"rotation eta ="<<bkgetacut <<"  phi ="<<bkgphicut<<endl;
        if(jet_eta<=etalimit) {
            if(bkgetacut<=(etacut-etalimit)||jet_eta<0.){
                //    bkg_phi = jet_phi+bkgphicut;
                bkg_eta = jet_eta+bkgetacut;
            }
            else {
                //    bkg_phi = jet_phi+bkgphicut;
                // bkg_eta = jet_eta+TMath::Max((etacut-etalimit)/2.,bkgetacut/2.); 
                bkg_eta = jet_eta-bkgetacut;
            }
            if(jet_phi<0.)bkg_phi = jet_phi+bkgphicut;
            else bkg_phi = jet_phi-bkgphicut;
        }
        else {
            bkg_phi = jet_phi;
            bkg_eta = -jet_eta;
            
        }
        
        if(subjet_eta<=etalimit) {
            if(bkgetacut<=(etacut-etalimit)||subjet_eta<0.){
                //    bkg_subphi = subjet_phi+bkgphicut;
                bkg_subeta = subjet_eta+bkgetacut;
            }
            else{
                //   bkg_subphi = subjet_phi+bkgphicut;
                bkg_subeta = subjet_eta-bkgetacut;
                //          bkg_subeta = subjet_eta+TMath::Max((etacut-etalimit)/2.,bkgetacut/2.); 
            }
            if(subjet_phi<0.)bkg_subphi = subjet_phi+bkgphicut;
            else bkg_subphi = subjet_phi-bkgphicut;
        }
        else {
            bkg_subphi = subjet_phi ;
            bkg_subeta = -subjet_eta ;
        }
        if(TMath::Abs(bkg_eta)>2.) cout <<"jet_eta =" <<jet_eta<<" bkg =" <<bkg_eta<<endl ;
        if(TMath::Abs(bkg_subeta)>2.) cout <<"subjet_eta =" <<subjet_eta<<" bkg =" <<bkg_subeta<<endl ;
        if(TMath::Abs(bkg_eta)>2.) continue ;   
        if(TMath::Abs(bkg_subeta)>2.) continue ;   
        
        if(TMath::Sqrt((bkg_phi-jet_phi)*(bkg_phi-jet_phi)+(bkg_eta-jet_eta)*(bkg_eta-jet_eta))<=conesize){
            printf ("jet bkg inside leading jet cone \n");
            continue ;
        }
        if(TMath::Sqrt((bkg_subphi-subjet_phi)*(bkg_subphi-subjet_phi)+(bkg_subeta-subjet_eta)*(bkg_subeta-subjet_eta))<=conesize){
            printf ("subjet bkg inside subleading jet cone \n");
            continue ;
        }
        if(TMath::Sqrt((bkg_subphi-jet_phi)*(bkg_subphi-jet_phi)+(bkg_subeta-jet_eta)*(bkg_subeta-jet_eta))<=conesize){
            printf ("subjet bkg inside leading jet cone \n");
            continue ;
        }
        if(TMath::Sqrt((bkg_phi-subjet_phi)*(bkg_phi-subjet_phi)+(bkg_eta-subjet_eta)*(bkg_eta-subjet_eta))<=conesize){
            printf ("jet bkg inside subleading jet cone \n");
            continue ;
        }
        
        //      }
        //for track analysis
        int charge[nrbin] ;
        double sumchpt[nrbin];
        double rho[nrbin] ;
        double psi[nrbin] ;
        double subrho[nrbin] ;
        double subpsi[nrbin] ;
        double sumpt = 0. ;
        double sumsubpt = 0. ;
        double meanphi = 0.;
        double meaneta = 0. ;
        int bkgcharge[nrbin] ;
        double bkgsumchpt[nrbin]  ;
        double bkgrho[nrbin];
        double bkgpsi[nrbin] ;
        double bkgsubrho[nrbin] ;
        double bkgsubpsi[nrbin] ;
        double bkgsumpt = 0. ;
        double bkgsumsubpt = 0. ;
        for(int ir = 0 ; ir <nrbin ; ir++){
            charge[ir]=0 ;
            sumchpt[ir]=0. ;
            rho[ir]=0. ;
            psi[ir]= 0.;
            subrho[ir]=0.;
            subpsi[ir]=0.;
            bkgcharge[ir]=0 ;
            bkgsumchpt[ir]=0. ;
            bkgrho[ir]=0.;
            bkgpsi[ir]=0. ;
            bkgsubrho[ir]=0.;
            bkgsubpsi[ir]=0.;
        }
        for(int ipart = 0 ; ipart < my_GenPart->mult ; ipart++){
            double gen_pt = my_GenPart->pt[ipart];
            double gen_phi = my_GenPart->phi[ipart];
            double gen_eta = my_GenPart->eta[ipart];
            // if(TMath::Abs(gen_eta)>tracketacut) continue ;
            if(gen_pt<trackcut) continue ;
            double dr =TMath::Sqrt((gen_phi-jet_phi)*(gen_phi-jet_phi)+(gen_eta-jet_eta)*(gen_eta-jet_eta));
            my_hists->deltaR->Fill(dr, weight);         
            double dr2 =TMath::Sqrt((gen_phi-subjet_phi)*(gen_phi-subjet_phi)+(gen_eta-subjet_eta)*(gen_eta-subjet_eta));
            if(dr<conesize && dr2<conesize) {
                cout <<"!!!! two jets are overlap with gen particle: "<<ipart <<"eta: " <<gen_eta <<" phi:" <<gen_phi << endl;
                continue ;
            }       
            else if(dr <=conesize){
                sumpt+=gen_pt ;
                my_hists->jetfrag[curr_bin]->Fill(lead_pt, TMath::Log(lead_pt/gen_pt), weight);
                my_hists->trackpt[curr_bin]->Fill(gen_pt, weight);
                for(int ir = 0 ; ir <nrbin; ir++){
                    if(dr>rbin[ir]&&dr<=rbin[ir+1]){
                        rho[ir]+=gen_pt ;
                        my_hists->ChargePt[curr_bin][ir]->Fill(lead_pt, gen_pt, weight);
                        sumchpt[ir]+=gen_pt ;
                        charge[ir]++ ;
                    }
                    if(dr<=rbin[ir+1]) {
                        psi[ir]+=gen_pt ; 
//                        my_hists->ChargePt[curr_bin][ir]->Fill(lead_pt, gen_pt, weight);
//                        sumchpt[ir]+=gen_pt ;
//                        charge[ir]++ ;
                    }
                }
            } //tracks inside for jet
            else if(dr2<=conesize) {
                sumsubpt+=gen_pt;
                my_hists->subjetfrag[curr_bin]->Fill(TMath::Log(lead_pt/gen_pt), TMath::Log(sublead_pt/gen_pt), weight);
                for(int ir = 0 ; ir <nrbin; ir++){
                    if(dr2<=rbin[ir+1]) subpsi[ir]+=gen_pt ;
                    if(dr2>rbin[ir]&&dr2<=rbin[ir+1]){
                        subrho[ir]+=gen_pt ;
                    }
                    
                }
                
            } //track inside the second jet
            else { //track outside jetcone 
                double bkg_dr = TMath::Sqrt((gen_phi-bkg_phi)*(gen_phi-bkg_phi)+(gen_eta-bkg_eta)*(gen_eta-bkg_eta));  
                double bkgsub_dr = TMath::Sqrt((gen_phi-bkg_subphi)*(gen_phi-bkg_subphi)+(gen_eta-bkg_subeta)*(gen_eta-bkg_subeta));
                //                if(bkg_dr<=conesize && bkgsub_dr<conesize) {
                //                    cout <<"!!!! two bkg cones are overlap with gen part: "<<ipart <<"eta: " <<gen_eta <<" phi:" <<gen_phi << endl;
                //                    continue ;
                //                }       
                
                if(bkg_dr<=conesize){
                    bkgsumpt+=gen_pt ;
                    for(int ir = 0 ; ir <nrbin; ir++){
                        if(bkg_dr>rbin[ir]&&bkg_dr<=rbin[ir+1]){
                            bkgrho[ir]+=gen_pt ;
                            my_hists->bkgChargePt[curr_bin][ir]->Fill(lead_pt, gen_pt, weight);
                            bkgsumchpt[ir]+=gen_pt ;
                            bkgcharge[ir]++ ;  
                        }
                        if(bkg_dr<=rbin[ir+1]) {
                            bkgpsi[ir]+=gen_pt ;
                        }
                    }
                }  //bkg cone   
                if(bkgsub_dr<=conesize) {
                    bkgsumsubpt+=gen_pt;
                    for(int ir = 0 ; ir <nrbin; ir++){
                        if(bkgsub_dr>rbin[ir]&&bkgsub_dr<=rbin[ir+1])
                            bkgsubrho[ir]+=gen_pt ;
                        if(bkgsub_dr<=rbin[ir+1]) {
                            bkgsubpsi[ir]+=gen_pt ;
                        }
                    }
                    
                } //track inside subject background cone
            } //outside both jet cone
            
            
            
        } //gen particle loop     
        
        if(sumpt==0 || sumsubpt==0) continue ;
        if(bkgsumpt>=sumpt || bkgsumsubpt>=sumsubpt) continue ;
        meanphi/=sumpt;
        meaneta/=sumpt;
        // rho/=deltacone ;
        for(int ir = 0 ; ir <nrbin; ir++){
          //  if(ir==nrbin-1)cout<<"psi="<<psi[ir]<<"sum ="<<sumpt<<endl;
        //    if(rho[ir]==sumpt&&ir>0) cout<<"evt ="<<evi<<" ir="<<ir<<"sum ="<<sumpt<<"psi ="<<psi[ir-1] <<" rho ="<<rho[ir-1]<<endl;
            psi[ir]/=sumpt;
            rho[ir]/=sumpt;
            subpsi[ir]/=sumsubpt;
            subrho[ir]/=sumsubpt;
            bkgpsi[ir]/=sumpt;
            bkgrho[ir]/=sumpt;
            bkgsubpsi[ir]/=sumsubpt;
            bkgsubrho[ir]/=sumsubpt;
            sumchpt[ir]/=sumpt ;
            bkgsumchpt[ir]/=sumpt ;

            my_hists->ChargeMult[curr_bin][ir]->Fill(lead_pt, charge[ir], weight);
            my_hists->SumChPt[curr_bin][ir]->Fill(lead_pt, sumchpt[ir],weight); 
            my_hists->bkgChargeMult[curr_bin][ir]->Fill(lead_pt, bkgcharge[ir],weight);
            my_hists->bkgSumChPt[curr_bin][ir]->Fill(lead_pt, bkgsumchpt[ir],weight); 
            my_hists->DiffJS[curr_bin][ir]->Fill(lead_pt, rho[ir],weight);
            my_hists->IntJS[curr_bin][ir]->Fill(lead_pt, psi[ir],weight);
            my_hists->subDiffJS[curr_bin][ir]->Fill(sublead_pt, subrho[ir],weight);
            my_hists->subIntJS[curr_bin][ir]->Fill(sublead_pt, subpsi[ir],weight);
            // rho/=deltacone ;
            my_hists->bkgDiffJS[curr_bin][ir]->Fill(lead_pt, bkgrho[ir],weight);
            //   my_hists->IntJS[curr_bin]->Fill(lead_pt, 1-psi);
            my_hists->bkgIntJS[curr_bin][ir]->Fill(lead_pt, bkgpsi[ir],weight);
            my_hists->bkgsubDiffJS[curr_bin][ir]->Fill(sublead_pt, bkgsubrho[ir],weight);
            my_hists->bkgsubIntJS[curr_bin][ir]->Fill(sublead_pt, bkgsubpsi[ir],weight);   
        }
        if(njets)my_hists->NJets[curr_bin]->Fill(my_ct->fChain->GetEntry(evi),weight);
        
        if(coll=="HI"){
            offSel->fChain->GetEntry(evi); 
            my_hists->CenBin->Fill(offSel->hiBin,weight);
        }
                
    }  ///event loop
    
    my_hists->Write();
    // my_hists->Delete();
    delete my_hists;
    std::cout << "working done\n";
}





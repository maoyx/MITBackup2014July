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
#include "hiForest.h"
#include "commonSetup.h"

using namespace std;

const double etacut = 2.0 ;
const double trackcut = 0.5;
const double tracketacut = 2.4; //make sure the tracks around jet cone inside eta range

////for etalimit = 0.3, to remove the possible overlap region by ER method 
const double etalimit = 0.3 ; 

const int pthat =80 ; //30 and 80 for pp; 30,50,80,120,170,200 for PbPb MC 
TString coll = "PP";
const bool DoGenAna=kTRUE ; //should be only be true for MC sample

TString intputFile ;

//TString dataPath="/Users/ymao/group/CMS/hiForest";
TString dataPath ;

//if it is pp, no centrality bins, only one
const int nbin = 1 ;
const int centr[] ={0,100};
//////for HI centrality bin
//const int nbin = 4 ;
//const int centr[] ={0,10,30,50,100};
//const int nbin = 2 ;
//const int centr[] ={0,30,100};

const int ntrkptbin = 6 ;
const double trkpt[]={1., 2., 4., 8., 16., 32., 500.};

class hist_class {
public:
    hist_class(TString the_desc);
    void Delete();
    void Write();
    
    TString desc;
    bool IsMC ;
    
    TH1F * NEvents[nbin];
    TH1F * Ntrack[nbin];
     TH1F * trackpt[nbin];
    TH2F * trackphi[nbin];
    TH2F * tracketa[nbin];
    TH1F * postrackpt[nbin];
    TH1F * negtrackpt[nbin];

    TH1F * Vertex ;
    //   if(IsMC){
    TH1F * genpartpt[nbin] ;
    TH1F * genpospartpt[nbin] ;
    TH1F * gennegpartpt[nbin] ;
    TH2F * genpartphi[nbin] ;
    TH2F * genparteta[nbin] ;
};

hist_class::hist_class(TString the_desc)
{
    
    desc = the_desc;
    IsMC =kTRUE ;
    for(int ibin = 0 ; ibin <nbin; ibin++){
        NEvents[ibin] = new TH1F(Form("Nevents_%d-%d%%",centr[ibin],centr[ibin+1]), Form("Nevents_%d-%d%%",centr[ibin],centr[ibin+1]), 800, 0, 800.);
        Ntrack[ibin] = new TH1F(Form("Ntracks_%d-%d%%",centr[ibin],centr[ibin+1]), Form("Ntracks_%d-%d%%",centr[ibin],centr[ibin+1]), 800, 0, 800.);
        trackpt[ibin] = new TH1F(Form("trackpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("trackpt_%d-%d%%",centr[ibin],centr[ibin+1]),200, 0., 200); 
        trackpt[ibin]->GetXaxis()->SetTitle("p_{T}^{trk} (GeV/c)");   
        trackpt[ibin]->Sumw2();
        postrackpt[ibin] = new TH1F(Form("postrackpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("postrackpt_%d-%d%%",centr[ibin],centr[ibin+1]),200, 0., 200); 
        postrackpt[ibin]->GetXaxis()->SetTitle("p_{T}^{trk} (GeV/c)");   
        postrackpt[ibin]->Sumw2();
        negtrackpt[ibin] = new TH1F(Form("negtrackpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("negtrackpt_%d-%d%%",centr[ibin],centr[ibin+1]),200, 0., 200); 
        negtrackpt[ibin]->GetXaxis()->SetTitle("p_{T}^{trk} (GeV/c)");   
        negtrackpt[ibin]->Sumw2();
        trackphi[ibin] = new TH2F(Form("trackphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("trackphi_%d-%d%%",centr[ibin],centr[ibin+1]), 200, 0., 200, 100, -5.05, 4.95); 
        trackphi[ibin]->GetXaxis()->SetTitle("p_{T}^{trk} (GeV/c)");
        trackphi[ibin]->GetYaxis()->SetTitle("#phi^{trk}");   
        trackphi[ibin]->Sumw2();
        tracketa[ibin] = new TH2F(Form("tracketa_%d-%d%%",centr[ibin],centr[ibin+1]), Form("tracketa_%d-%d%%",centr[ibin],centr[ibin+1]), 200, 0., 200, 100, -5.05, 4.95); 
        tracketa[ibin]->GetXaxis()->SetTitle("p_{T}^{trk} (GeV/c)");
        tracketa[ibin]->GetYaxis()->SetTitle("#eta^{trk}");   
        tracketa[ibin]->Sumw2();

        if(IsMC&&DoGenAna){
            genpartpt[ibin] = new TH1F(Form("genpartpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genpartpt_%d-%d%%",centr[ibin],centr[ibin+1]), 200, 0., 200);
            genpartpt[ibin]->GetXaxis()->SetTitle("p_{T}^{part} (GeV/c)");   
            genpartpt[ibin]->Sumw2();
            genpospartpt[ibin] = new TH1F(Form("genpospartpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genpospartpt_%d-%d%%",centr[ibin],centr[ibin+1]), 200, 0., 200);
            genpospartpt[ibin]->GetXaxis()->SetTitle("p_{T}^{part} (GeV/c)");   
            genpospartpt[ibin]->Sumw2();    
            gennegpartpt[ibin] = new TH1F(Form("gennegpartpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("gennegpartpt_%d-%d%%",centr[ibin],centr[ibin+1]), 200, 0., 200);
            gennegpartpt[ibin]->GetXaxis()->SetTitle("p_{T}^{part} (GeV/c)");   
            gennegpartpt[ibin]->Sumw2();
            genpartphi[ibin] = new TH2F(Form("genpartphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genpartphi_%d-%d%%",centr[ibin],centr[ibin+1]), 200, 0., 200, 100, -5.05, 4.95);
            genpartphi[ibin]->GetXaxis()->SetTitle("p_{T}^{gen} (GeV/c)");
            genpartphi[ibin]->GetYaxis()->SetTitle("#phi^{part}");   
            genpartphi[ibin]->Sumw2();
            genparteta[ibin] = new TH2F(Form("genparteta_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genparteta_%d-%d%%",centr[ibin],centr[ibin+1]), 200, 0., 200, 100, -5.05, 4.95);
            genparteta[ibin]->GetXaxis()->SetTitle("p_{T}^{gen} (GeV/c)");
            genparteta[ibin]->GetYaxis()->SetTitle("#eta^{part} ");   
            genparteta[ibin]->Sumw2();
        }
 //for MC histograms
        }  //centrality bins loop
    Vertex = new TH1F((TString) (desc + "_Vz"), "", 400, -20., 20.);
    Vertex->Sumw2();
}

void hist_class::Delete()
{
    for(int ibin = 0 ; ibin <nbin; ibin++){
        delete NEvents[ibin];
        delete Ntrack[ibin];  
        delete trackpt[ibin];
        delete postrackpt[ibin];
        delete negtrackpt[ibin];
        delete trackphi[ibin];
        delete tracketa[ibin];
        
        if(IsMC&&DoGenAna){
            delete genpartpt[ibin];
            delete genpospartpt[ibin];
            delete gennegpartpt[ibin];
            delete genpartphi[ibin];
            delete genparteta[ibin];
        }
        
    } //centrality loop
    delete Vertex;
}

void hist_class::Write()
{
    TString out_name ;
    TString dataType ; 
    if(IsMC) dataType="MC" ;
    else dataType="DATA";
            out_name=Form("%s%s_TrackCut%.fDist_%s",dataType.Data(),coll.Data(),trackcut, intputFile.Data());       
 
       TFile *out_file = new TFile(Form("/net/hidsk0001/d00/scratch/maoyx/pAExercise/CMSSW_5_3_3/src/%s",out_name.Data()), "RECREATE");
    for(int ibin = 0 ; ibin <nbin; ibin++){
        NEvents[ibin]->Write();
        Ntrack[ibin]->Write();
        trackpt[ibin]->Write();
        postrackpt[ibin]->Write();
         negtrackpt[ibin]->Write();
        trackphi[ibin]->Write();
        tracketa[ibin]->Write();
        if(IsMC&&DoGenAna){
            genpartpt[ibin]->Write();
            genpospartpt[ibin]->Write();
            gennegpartpt[ibin]->Write();
            genpartphi[ibin]->Write();
            genparteta[ibin]->Write();
        }
        } //centrality bins
    
    Vertex->Write();
    out_file->Close();
    cout <<"Output file: " <<Form("%s",out_name.Data()) <<endl ;
    
}


void drawTrackCharge()
{
    hist_class *my_hists = new hist_class("track");
    cout <<my_hists->IsMC<<endl ;

    std::cout << "start working\n";
    if(my_hists->IsMC!=kTRUE){ 
      //    dataPath="/Users/ymao/group/CMS/hiForest";
   //  dataPath="/home/group/CMS/WorkSpace/data/HI2011/forest" ; //lxplus data path
      if(coll=="pA")
          dataPath="/net/hisrv0001/home/yenjie/slocal/merge/pbpb" ; //mit PbPb data
      //  dataPath="/mnt/hadoop/cms/store/user/yenjie/HiForest_data_v28" ;//mit PbPb data path
   else 
        dataPath="/net/hisrv0001/home/yenjie/scratch/hiForest/prod/productionPP/CMSSW_4_4_2_patch6/test/ppForest2";
    }
    else {
        if(coll=="pA") 
          dataPath= Form("/mnt/hadoop/cms/store/user/tuos/pPb/HiForest/5_3_3_patch3"); //lxplus MC normial
       //   dataPath= Form("/net/hisrv0001/home/yenjie/slocal/merge/pyquen/pyquen%s%d",para.Data(), pthat); //lxplus MC pquen
        else    
         dataPath= Form("/net/hisrv0001/home/zhukova/scratch/HIHighPt/forest/pthat%d", pthat); //lxplus path for pp
       //  dataPath= Form("/mnt/hadoop/cms/store/user/yetkin/MC_Production/HydjetDrum03"); //lxplus path for Hydjet MB
    }
    if(my_hists->IsMC!=kTRUE){  //real data analysis
        if(coll=="pA")             
            intputFile="mergedFile.root" ;
         //  intputFile="castor_frank_PbPb_dijetforest2_HiForest-promptskim-hihighpt-hltjet80-pt90-v2_v3_part2.root";
	    //  intputFile="HiForest-promptskim-hihighpt-hltjet80-pt90-v3_part2.root";
       // intputFile="promptskim-hihighpt-hltjet80-pt90-v3-forest-v2.root";
        else 
	      intputFile="pp_merged_full.root";
     //    intputFile="forest2_2760GeV_ppJet_full_July14.root";
	  //   intputFile="castor_frank_forest2_HiForest-ppskim-hihighpt-pt90-v1_v3_part.root";
    }
    else { //MC sample
        if(coll=="pA"){             
	   intputFile=Form("pPbAMPT_Evening_5_3_3_v0_HiForest2_v07.root");
         //  intputFile=Form("pPbHijing_5_3_3_v0_HiForest2_v07.root");
   }
        else 
         //   intputFile=Form("HydjetDrum03_HiForest_v05_merged_test02.root");  
          intputFile=Form("mergedFile.root");  
    }
    
    TString inname=Form("%s/%s", dataPath.Data(),intputFile.Data());
    // Define the input file and HiForest
    bool isPP =false ;
    if(coll=="PP") isPP =true ;
    HiForest * c = new HiForest(inname,"forest",isPP);
   // HiForest *c = new HiForest(inname);
    c->InitTree();
    cout <<"Input file" << inname<<endl ;
    
    Evts * offSel = &(c->evt); 

    //skim tree
    Skims * my_skim = &(c->skim); 

    //hlt tree
    Hlts * trigSel = &(c->hlt); 
    
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
    cout <<"Number of events ="<<c->GetEntries()<<endl ;
    for(int evi = 0; evi < c->GetEntries(); evi++) {
        //          for(int evi = 0; evi < 10; evi++) {
        c->GetEntry(evi);
       //cout <<"evt = "<<evi <<endl ; 
        int noise_evt = my_skim->pHBHENoiseFilter ;
        //        int ecal_noise = my_skim->phiEcalRecHitSpikeFilter ;
        //        if(ecal_noise==0) continue ;
        
        double vz = offSel->vz ;
        int hiBin = offSel->hiBin ;
        
        //   cout <<"vz =" <<vz <<endl ;
        if(TMath::Abs(vz)>15.) continue ;

       //    cout << "  cent_bin:" <<curr_bin <<endl ;
        if(evi%10000==1)cout <<" coll = " <<coll <<" evt = " <<evi <<endl ;
        
        //cout <<my_hists->NEvents[curr_bin]->GetName() <<endl;
        //cout << "start working222222\n";
        my_hists->Ntrack[curr_bin]->Fill(my_tr->nTrk);

                if(my_hists->IsMC==kTRUE&&DoGenAna){
                    for(int ipart = 0 ; ipart < my_GenPart->mult ; ipart++){//gen particle loop
                        double gen_pt = my_GenPart->pt[ipart];
                        double gen_phi = my_GenPart->phi[ipart];
                        double gen_eta = my_GenPart->eta[ipart];
                        int chg = my_GenPart->chg[ipart];
                        if(chg==0) continue ;
                        if(TMath::Abs(gen_eta)>2.4) continue ;
                        my_hists->genpartpt[curr_bin]->Fill(gen_pt);
                        if(chg==1)my_hists->genpospartpt[curr_bin]->Fill(gen_pt);
                        if(chg==-1)my_hists->gennegpartpt[curr_bin]->Fill(gen_pt);
                        my_hists->genpartphi[curr_bin]->Fill(gen_pt,gen_phi);
                        my_hists->genparteta[curr_bin]->Fill(gen_pt,gen_eta);
                    }

//            //using the sim track to calculate the tracking efficiency 
//            for(int ipart = 0 ; ipart < my_tr->nParticle ; ipart++){ //sim track loop 
//                double gen_pt = my_tr->pPt[ipart];
//                double gen_phi = my_tr->pPhi[ipart];
//                double gen_eta = my_tr->pEta[ipart];  
//                if(gen_pt<trackcut)continue ;
//                if(TMath::Abs(gen_eta)>2.4)continue ;
//                if(my_tr->pNRec[ipart]>0&&(my_tr->mtrkAlgo[ipart]<4||(my_tr->mtrkQual[ipart]))){
//                    //   if(my_tr->pNRec[ipart]>0){  //no quality cuts                  
//                       my_hists->genpartpt[curr_bin]->Fill(gen_pt);
//                        my_hists->genpartphi[curr_bin]->Fill(gen_pt,gen_phi);
//                       my_hists->genparteta[curr_bin]->Fill(gen_pt,gen_eta);
//                } //gen matched track selection
//            }  //sim track loop
                    
        }//MC sim track loop for efficiency study  
        
        
        for(int itr = 0 ; itr < my_tr->nTrk ; itr++){
            double tr_pt = my_tr->trkPt[itr];
            double tr_phi = my_tr->trkPhi[itr];
            double tr_eta = my_tr->trkEta[itr];
            if(TMath::Abs(tr_eta)>2.4) continue ;
            
            if(my_tr->trkAlgo[itr]<4 ||(my_tr->highPurity[itr])){
                if(tr_pt<trackcut) continue ;
                my_hists->trackpt[curr_bin]->Fill(tr_pt);
                my_hists->trackphi[curr_bin]->Fill(tr_pt, tr_phi);
                my_hists->tracketa[curr_bin]->Fill(tr_pt, tr_eta);
            } //track selection  
        } //track loop

        my_hists->Ntrack[curr_bin]->Fill(1);        
        my_hists->Vertex->Fill(offSel->vz);

    }  ///event loop
    
    my_hists->Write();
    //   my_hists->Delete();
    //  delete my_hists;
    std::cout << "working done\n";
}





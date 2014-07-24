#include <stdio.h>
#include <iostream>
#include "TCanvas.h"
#include "TError.h"
#include "TPad.h"
#include "TString.h"
#include "TRandom.h"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH1.h"
#include "TLine.h"
#include <TF1.h>
#include <TMath.h>
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TString.h"
#include "TCut.h"
#include <TMath.h>
#include <TSystem.h>
#include "THStack.h"
#include <iostream>
using namespace std;

void AddHist(){
    const int Nfile = 10 ;
    TFile * f[Nfile] ;
    TString name[Nfile] ;
    TList * list[Nfile] ;
    const Int_t pthat[]={0, 20, 30, 50, 80, 120, 170, 230, 300, 380, -1};
    const int npthatbin = sizeof(pthat)/sizeof(Double_t)-1 ;
    const char * kDir = "/net/hidsk0001/d00/scratch/maoyx/GeneratorStudy/PYTHIA/CMSSW_5_3_8_HI_patch2/src/GenJetXpdf/GenPartonAndFFNtuplizer/test" ;
    int N ;
  //  TString filename ="Feb02_Z2Star"; 
 //   TString filename ="Jan30_ProQ20"; 
    TString filename ="Jan27_Z2"; 
  //  TString filename ="Feb4_AMBT1"; 
 //   TString filename ="Feb6_D6T"; 
    for(int ifile=0; ifile<Nfile; ifile++){ 
    if(ifile==Nfile-1) name[ifile]=Form("nPDFWeight_GenAna_AnaGENJetR3_%s_Pt%dtoinf_numEvent640000.root", filename.Data(), pthat[ifile]);
    else name[ifile]=Form("nPDFWeight_GenAna_AnaGENJetR3_%s_Pt%dto%d_numEvent640000.root",filename.Data(),  pthat[ifile], pthat[ifile+1]);

   f[ifile] = TFile::Open(Form("%s/%s", kDir, name[ifile].Data()), "readonly");

      list[ifile] =(TList*)f[ifile]->GetListOfKeys();
      if(ifile==0){
        N = list[ifile]->GetEntries();
      }
  }

      const int Nhist = N ;
      TH1 * h[Nfile][Nhist];
      TH1 * htot[Nhist];
    for(int ifile=0; ifile<Nfile; ifile++){ 
      for(int ihist = 0 ; ihist < Nhist ; ihist++){
      h[ifile][ihist] = (TH1*)f[ifile]->Get(list[ifile]->At(ihist)->GetName()) ;
      }
    }
    TString outname=Form("nPDFWeight_GenAna_AnaGENJetR3_%s_PYTHIACombined.root", filename.Data()) ;
   TFile * fmerge = new TFile(Form("%s/%s", kDir,outname.Data()), "RECREATE");
       for(int ihist = 0 ; ihist < Nhist ; ihist++){

            for(int ifile=0; ifile<Nfile; ifile++){ 
                if(ifile==0)
                    htot[ihist] = (TH1*)h[ifile][ihist]->Clone(Form("%s",list[ifile]->At(ihist)->GetName()));
                else 
                    htot[ihist]->Add(h[ifile][ihist]);
                
            }
        
        if(htot[ihist]->GetEntries()>0){
            htot[ihist]->Write();
        }

    }
    fmerge->Close() ;
    

}

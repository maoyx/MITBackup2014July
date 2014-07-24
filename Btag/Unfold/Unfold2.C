#include <iostream>
#include <stdio.h>

#include <TRandom2.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>

#include "utilities.h"
#include "bayesianUnfold.h"
#include "prior.h"

using namespace std;


//==============================================================================
// Unfolding Ying Lu 08 07 11
// Update Yen-Jie Lee 06.22.12
//==============================================================================

void Unfold2(int algo= 3,bool useSpectraFromFile=0, bool useMatrixFromFile=0, int doToy = 0, int isMC = 0,char *spectraFileName = (char*)"pbpb_spectra_akPu3PF.root",double recoJetPtCut = 60,double trackMaxPtCut = 0, int nBayesianIter = 4, int doBjets=0) // algo 2 =akpu2 ; 3 =akpu3 ; 4 =akpu4 ;1 = icpu5
{
  
  gStyle->SetErrorX(0.5);
  gStyle->SetPaintTextFormat("3.2f");
  gStyle->SetOptLogz(1);
  gStyle->SetPadRightMargin(0.13);	
  gStyle->SetOptTitle(0);

	const float pplumi=5.3e9;
        const bool SavePlot=kTRUE;

  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  
  // input files
  char *fileNamePP_data = (char*)"/net/hidsk0001/d00/scratch/maoyx/pPb/Btag/CodeMatt/NewFormatV4_bFractionMCTemplate_pppp1_SSVHEat2.0FixCL0_bin_0_40_eta_0_2.root";
  char *fileNamePbPb_data = (char*)"/net/hidsk0001/d00/scratch/maoyx/pPb/Btag/CodeMatt/AltBinningV6_bFractionMCTemplate_ppPbPb1_SSVHEat2.0FixCL0_bin_0_40_eta_0_2.root";
  char *fileNamePP_mc = NULL;
  if(doBjets) fileNamePP_mc = (char*)"/net/hidsk0001/d00/scratch/kjung/histos/ppMC_ppReco_ak3PF_BjetTrig_noIPupperCut.root";
  else fileNamePP_mc = (char*)"/net/hidsk0001/d00/scratch/kjung/histos//ppMC_ppReco_ak3PF_QCDjetTrig_noIPupperCut.root";
  char *fileNamePbPb_mc = NULL;
  if(doBjets)fileNamePbPb_mc = (char*) "/net/hisrv0001/home/mnguyen/scratch/bTaggingOutput/ntuples/PbPbBMC_pt30by3_ipHICalibCentWeight_noTrig.root";
  else fileNamePbPb_mc = (char*) "/net/hisrv0001/home/mnguyen/scratch/bTaggingOutput/ntuples/PbPbQCDMC_pt30by3_ipHICalibCentWeight_noTrig.root";

  // grab ntuples
  TFile *infPbPb_mc = new TFile(fileNamePbPb_mc);
  TFile *infPP_mc = new TFile(fileNamePP_mc);


  // Output file
  TFile *pbpb_Unfo;
  if (isMC) pbpb_Unfo = new TFile(Form("pbpb_Unfo_%s_MC.root",algoName[algo]),"RECREATE");
  else pbpb_Unfo  = new TFile(Form("pbpb_Unfo_%s_jtpt%.0f_trk%.0f.root",algoName[algo],recoJetPtCut,trackMaxPtCut),"RECREATE");
  // Histograms used by RooUnfold
  UnfoldingHistos *uhist[nbins_cent+1];
		
  // Initialize Histograms   
	
  for (int i=0;i<=nbins_cent;i++) uhist[i] = new UnfoldingHistos(i);
	
  // Initialize reweighting functions
  
  TCut dataSelection;
  TCut dataSelectionPP;
  TCut TriggerSelectionPP;
  TCut TriggerSelectionPbPb80;

  if(doBjets)dataSelection = "weight*(abs(refparton_flavorForB)==5&&abs(jteta)<2)";
  else dataSelection = "weight*(abs(jteta)<2)";
  

  if (isMC) cout<<"This is a MC closure test"<<endl;
  else cout<< "This is a data analysis"<<endl;    		     
	     	
  // Setup jet data branches, basically the jet tree branches are assigned to this object when we loop over the events
	
  JetDataPbPb *dataPbPb   = new JetDataPbPb(fileNamePbPb_mc,(char*)"nt"); // PbPb data	
  JetDataPP *dataPP = new JetDataPP(fileNamePP_mc,(char*)"nt");	// pp data
	
  TFile *fSpectra(0);		
  if (useSpectraFromFile||useMatrixFromFile){
    fSpectra = new TFile(spectraFileName,"read");
  }
  
  // Come back to the output file dir
  pbpb_Unfo->cd();

  // Get Jet spectra from data file
  cout <<"Reading data..."<<endl;

  // This doesn't seem to be relevant for the moment -Matt
  /*	

  TTree *tPbPbJet = (TTree*)infPbPb_mc->Get("nt");
  TTree *tPPJet  = (TTree*)infPP_mc->Get("nt");


  TCanvas * cInput = new TCanvas("cInput","Input",800,400);
  cInput->Divide(2,1);
		
  cout <<"Spectra..."<<endl;	
	
  for (int i=0;i<=nbins_cent;i++){
    cout <<nbins_cent<<endl;
    TCut centCut = Form("bin<%.0f&&bin>=%.0f",boundaries_cent[i+1],boundaries_cent[i]);
    if (useSpectraFromFile) {
      uhist[i]->hMeas = (TH1F*)fSpectra->Get(Form("hMeas_cent%d",i));
    } else {
      if (!isMC) {
	tPbPbJet->Project(Form("hMeas_cent%d",i),"jtptB", dataSelection&&centCut&&TriggerSelectionPbPb80);
      }   
    }
		
    if (useMatrixFromFile) {
      cout <<"Matrix"<<endl;
      uhist[i]->hMatrixFit = (TH2F*) fSpectra->Get(Form("hMatrixFit_cent%d",i));
      uhist[i]->hMeasMatch = (TH1F*)((TH2F*) fSpectra->Get(Form("hMatrixFit_cent%d",i)))->ProjectionY();
      uhist[i]->hMeasMatch->Divide(uhist[i]->hMeas);
    } else {
      uhist[i]->hMeasMatch = 0;
    }
    uhist[i]->hMeas->Draw();
  }

  if (!isMC) tPPJet->Project(Form("hMeas_cent%d",nbins_cent),"jtpt",dataSelectionPP&&TriggerSelectionPP);
  */
  cout <<"MC..."<<endl;	
  
  TH1F *hCent = new TH1F("hCent","",nbins_cent,boundaries_cent);
 
		
  // Fill PbPb MC   
  if (!useMatrixFromFile) {
    for (Long64_t jentry2=0; jentry2<dataPbPb->tJet->GetEntries();jentry2++) {
      dataPbPb->tJet->GetEntry(jentry2);
      
      // change when we switch to centrality binning
      int cBin = 0;
      
      //int cBin = hCent->FindBin(dataPbPb->bin)-1;
      /*
	if (cBin>=nbins_cent) continue;
	if (cBin==-1) continue;
      */
      
      if ( dataPbPb->refpt  < 0. ) continue;
      if ( dataPbPb->jteta  > 2. || dataPbPb->jteta < -2. ) continue;
      if ( dataPbPb->refpt<0) dataPbPb->refpt=0;
      if (doBjets && fabs(dataPbPb->refparton_flavorForB)!=5) continue;
      if (doBjets&& dataPbPb->discr_ssvHighEff<2) continue;
      if (doBjets && dataPbPb->jtptB < recoJetPtCut) continue;
      if (!doBjets && dataPbPb->jtptA < recoJetPtCut) continue;
      //if ( dataPbPb->isTrig <1) continue;
      
      if(!doBjets)if(dataPbPb->refpt < 50 && dataPbPb->jtptA>120) continue;
      if(doBjets)if(dataPbPb->refpt < 50 && dataPbPb->jtptB>120) continue;

      if (!isMC||jentry2 % 2 == 1) {
	if(doBjets)uhist[cBin]-> hMatrix->Fill(dataPbPb->refpt,dataPbPb->jtptB,dataPbPb->weight);
	else uhist[cBin]-> hMatrix->Fill(dataPbPb->refpt,dataPbPb->jtptA,dataPbPb->weight);
      }	  
      if (jentry2 % 2 == 0) {
	uhist[cBin]-> hGen->Fill(dataPbPb->refpt,dataPbPb->weight);   
	if(doBjets)uhist[cBin]-> hMeas->Fill(dataPbPb->jtptB,dataPbPb->weight);  	 
	else uhist[cBin]-> hMeas->Fill(dataPbPb->jtptA,dataPbPb->weight);  	 
	//uhist[cBin]-> hMeasJECSys->Fill(dataPbPb->jtpt*(1.+0.02/nbins_cent*(nbins_cent-i)),dataPbPb->weight); 
	// FIXME!!!!!!  i is supposed to be a loop over centrality !!!!
	if(doBjets)uhist[cBin]-> hMeasJECSys->Fill(dataPbPb->jtptB*(1.+0.02/nbins_cent*(nbins_cent-0)),dataPbPb->weight); 
	else uhist[cBin]-> hMeasJECSys->Fill(dataPbPb->jtptA*(1.+0.02/nbins_cent*(nbins_cent-0)),dataPbPb->weight); 
      }
    }

    //pp will just fill the last index of the centrality array

    // fill pp MC
    for (Long64_t jentry2=0; jentry2<dataPP->tJet->GetEntries();jentry2++) {
      dataPP->tJet->GetEntry(jentry2);
      
      if ( dataPP->refpt<0) continue;
      if ( dataPP->jteta  > 2. || dataPP->jteta < -2. ) continue;
      if ( dataPP->refpt<0) dataPP->refpt=0;
      if ( doBjets && fabs(dataPP->refparton_flavorForB)!=5) continue;
      if ( doBjets && dataPP->discr_ssvHighEff<2) continue;
      if ( dataPP->jtpt < recoJetPtCut) continue;
      
      if (!isMC||jentry2 % 2 == 1) {
	uhist[nbins_cent]-> hMatrix->Fill(dataPP->refpt,dataPP->jtpt,dataPP->weight);
      }	  
      if (jentry2 % 2 == 0) {
	uhist[nbins_cent]-> hGen->Fill(dataPP->refpt,dataPP->weight);   
	uhist[nbins_cent]-> hMeas->Fill(dataPP->jtpt,dataPP->weight); 
      }           
    }
  }

	

  cout <<"Response Matrix..."<<endl;
	
  TCanvas * cMatrix = new TCanvas("cMatrix","Matrix",800,400);
  cMatrix->Divide(2,1);

  for (int i=0;i<=nbins_cent;i++){
    cMatrix->cd(i+1);
    if (!useMatrixFromFile) {
      TF1 *f = new TF1("f","[0]*pow(x+[2],[1])");
      f->SetParameters(1e10,-8.8,40);
      for (int y=1;y<=uhist[i]->hMatrix->GetNbinsY();y++) {
	double sum=0;
	for (int x=1;x<=uhist[i]->hMatrix->GetNbinsX();x++) {
	  if (uhist[i]->hMatrix->GetBinContent(x,y)<=1*uhist[i]->hMatrix->GetBinError(x,y)) {
	    uhist[i]->hMatrix->SetBinContent(x,y,0);
	    uhist[i]->hMatrix->SetBinError(x,y,0);
	  }
	  sum+=uhist[i]->hMatrix->GetBinContent(x,y);
	}
				
	for (int x=1;x<=uhist[i]->hMatrix->GetNbinsX();x++) {	   
	  double ratio = 1;
	  uhist[i]->hMatrix->SetBinContent(x,y,uhist[i]->hMatrix->GetBinContent(x,y)*ratio);
	  uhist[i]->hMatrix->SetBinError(x,y,uhist[i]->hMatrix->GetBinError(x,y)*ratio);
	}
      }
    }
    uhist[i]->hResponse = (TH2F*)uhist[i]->hMatrix->Clone(Form("hResponse_cent%d",i));
    for (int y=1;y<=uhist[i]->hResponse->GetNbinsY();y++) {
      double sum=0;
      for (int x=1;x<=uhist[i]->hResponse->GetNbinsX();x++) {
	if (uhist[i]->hResponse->GetBinContent(x,y)<=0*uhist[i]->hResponse->GetBinError(x,y)) {
	  uhist[i]->hResponse->SetBinContent(x,y,0);
	  uhist[i]->hResponse->SetBinError(x,y,0);
	}
	sum+=uhist[i]->hResponse->GetBinContent(x,y);
      }
			
      for (int x=1;x<=uhist[i]->hResponse->GetNbinsX();x++) {  	
	if (sum==0) continue;
	double ratio = uhist[i]->hMeas->GetBinContent(y)/sum;
	if (uhist[i]->hMeas->GetBinContent(y)==0) ratio = 1e-100/sum;
      }
    }
		
    uhist[i]->hResponseNorm = (TH2F*)uhist[i]->hMatrix->Clone(Form("hResponseNorm_cent%d",i));
    for (int x=1;x<=uhist[i]->hResponseNorm->GetNbinsX();x++) {
      double sum=0;
      for (int y=1;y<=uhist[i]->hResponseNorm->GetNbinsY();y++) {
	if (uhist[i]->hResponseNorm->GetBinContent(x,y)<=0*uhist[i]->hResponseNorm->GetBinError(x,y)) {
	  uhist[i]->hResponseNorm->SetBinContent(x,y,0);
	  uhist[i]->hResponseNorm->SetBinError(x,y,0);
	}
	sum+=uhist[i]->hResponseNorm->GetBinContent(x,y);
      }
			
      for (int y=1;y<=uhist[i]->hResponseNorm->GetNbinsY();y++) {  	
	if (sum==0) continue;
	double ratio = 1./sum;
	uhist[i]->hResponseNorm->SetBinContent(x,y,uhist[i]->hResponseNorm->GetBinContent(x,y)*ratio);
	uhist[i]->hResponseNorm->SetBinError(x,y,uhist[i]->hResponseNorm->GetBinError(x,y)*ratio);
      }
    }
		
    uhist[i]->hResponse->Draw("col");
		
    if (!useMatrixFromFile) uhist[i]->hMatrixFit = uhist[i]->hMatrix;
    uhist[i]->hMatrixFit->SetName(Form("hMatrixFit_cent%d",i));
  }

   cMatrix->Update();
  if (isMC==0) {
    // Use measured histogram from Matt & Kurt's file
	   
    // PbPb file:

    TFile *infMatt = new TFile(fileNamePbPb_data);
    TH1F *hMattPbPb = NULL;
    if(doBjets) hMattPbPb = (TH1F*) infMatt->Get("hRawBData");
    else hMattPbPb = (TH1F*) infMatt->Get("hIncJetsData");
    divideBinWidth(hMattPbPb);
           
    // Need to match the binning carefully, please double check whenever you change the binning
    for (int i=1;i<=hMattPbPb->GetNbinsX();i++)
      {
	uhist[0]->hMeas->SetBinContent(i+uhist[0]->hMeas->FindBin(61)-1,hMattPbPb->GetBinContent(i));  
	uhist[0]->hMeas->SetBinError(i+uhist[0]->hMeas->FindBin(61)-1,hMattPbPb->GetBinError(i));  
      }

    // pp file:
    // The file name needs to be updated!!!!!
    TFile *infMattPP = new TFile(fileNamePP_data);
    TH1F *hMattPP = NULL;
    if(doBjets)hMattPP = (TH1F*) infMattPP->Get("hRawBData");
    else hMattPP = (TH1F*) infMattPP->Get("hIncJetsData");
    divideBinWidth(hMattPP);
	   
    // Need to match the binning carefully, please double check whenever you change the binning
    for (int i=1;i<=hMattPP->GetNbinsX();i++)
      {
	uhist[nbins_cent]->hMeas->SetBinContent(i+uhist[nbins_cent]->hMeas->FindBin(61)-1,hMattPP->GetBinContent(i));  
	uhist[nbins_cent]->hMeas->SetBinError(i+uhist[nbins_cent]->hMeas->FindBin(61)-1,hMattPP->GetBinError(i));  
      }

  }

 
  pbpb_Unfo->cd();
	
  cout << "==================================== UNFOLD ===================================" << endl;
	
  //char chmet[100]; 
	
  // ======================= Reconstructed pp and PbPb spectra =========================================================
  TCanvas * cPbPb = new TCanvas("cPbPb","Comparison",1200,600);
  cPbPb->Divide(2,1); 
  cPbPb->cd(1);
	
	
  for (int i=0;i<=nbins_cent;i++) {
    cPbPb->cd(i+1)->SetLogy();   
    // Do Bin-by-bin
    TH1F *hBinByBinCorRaw = (TH1F*)uhist[i]->hResponse->ProjectionY(); 
    TH1F *hMCGen           = (TH1F*)uhist[i]->hResponse->ProjectionX(); // gen
    hBinByBinCorRaw->Divide(hMCGen);
    TF1 *f = new TF1("f","[0]+[1]*x");
    hBinByBinCorRaw->Fit("f","LL ","",90,300);
    TH1F* hBinByBinCor = (TH1F*)hBinByBinCorRaw->Clone();//functionHist(f,hBinByBinCorRaw,Form("hBinByBinCor_cent%d",i));
    delete hBinByBinCorRaw;
    delete hMCGen;
    uhist[i]->hRecoBinByBin = (TH1F*) uhist[i]->hMeas->Clone(Form("hRecoBinByBin_cent%d",i));
    uhist[i]->hRecoBinByBin->Divide(hBinByBinCor);
		
    // Do unfolding
    //if (isMC) uhist[i]->hMeas = (TH1F*)uhist[i]->hMatrix->ProjectionY()->Clone(Form("hMeas_cent%d",i));
    prior myPrior(uhist[i]->hMatrixFit,uhist[i]->hMeas,0);
  //  myPrior.unfold(uhist[i]->hMeas,1);
    myPrior.unfold(uhist[i]->hMeas,nBayesianIter);
    TH1F *hPrior;//=(TH1F*) functionHist(fPow,uhist[i]->hMeas,Form("hPrior_cent%d",i));
    hPrior = (TH1F*)uhist[i]->hGen->Clone("hPrior");//(TH1F*)uhist[i]->hMeas->Clone(Form("hPrior_cent%d",i));
    removeZero(hPrior);
		
    bayesianUnfold myUnfoldingJECSys(uhist[i]->hMatrixFit,hPrior,0);
    myUnfoldingJECSys.unfold(uhist[i]->hMeasJECSys,nBayesianIter);
    bayesianUnfold myUnfoldingSmearSys(uhist[i]->hMatrixFit,hPrior,0);
    myUnfoldingSmearSys.unfold(uhist[i]->hMeasSmearSys,nBayesianIter);
    bayesianUnfold myUnfolding(uhist[i]->hMatrixFit,myPrior.hPrior,0);
    myUnfolding.unfold(uhist[i]->hMeas,nBayesianIter);
    cout <<"Unfolding bin "<<i<<endl;

    // Iteration Systematics
    for (int j=2;j<=40;j++)
      {
	bayesianUnfold myUnfoldingSys(uhist[i]->hMatrixFit,hPrior,0);
	myUnfoldingSys.unfold(uhist[i]->hMeas,j);
	uhist[i]->hRecoIterSys[j]  = (TH1F*) myUnfoldingSys.hPrior->Clone(Form("hRecoRAA_IterSys%d_cent%d",j,i));
      }
		
		
    uhist[i]->hReco         = (TH1F*) uhist[i]->hRecoIterSys[nBayesianIter]->Clone(Form("Unfolded_cent%i",i));
    uhist[i]->hRecoJECSys   = (TH1F*) myUnfoldingJECSys.hPrior->Clone(Form("UnfoldedJeCSys_cent%i",i));
    uhist[i]->hRecoSmearSys   = (TH1F*) myUnfoldingSmearSys.hPrior->Clone(Form("UnfoldedSmearSys_cent%i",i));
    uhist[i]->hRecoBinByBin->SetName(Form("UnfoldedBinByBin_cent%i",i));
		
    if (doToy) {
      TCanvas *cToy = new TCanvas("cToy","toy",600,600);
      cToy->cd();
      int nExp=1000;
      TH1F *hTmp[nbins_truth+1];
      TH1F *hTmp2[nbins_truth+1];
      for (int j=1;j<=nbins_truth;j++) {
	hTmp[j] = new TH1F(Form("hTmp%d",j),"",200,0,10.+uhist[i]->hReco->GetBinContent(j)*2);
	hTmp2[j] = new TH1F(Form("hTmp2%d",j),"",200,0,10.+uhist[i]->hRecoBinByBin->GetBinContent(j)*2);
      }
      for (int exp =0; exp<nExp; exp++) {
	TH1F *hToy = (TH1F*)uhist[i]->hMeas->Clone();   
	TH2F *hMatrixToy = (TH2F*)uhist[i]->hMatrixFit->Clone();
	hToy->SetName("hToy");
	if (exp%100==0) cout <<"Pseudo-experiment "<<exp<<endl;
	for (int j=1;j<=hToy->GetNbinsX();j++) {
	  double value = gRandom->Poisson(uhist[i]->hMeas->GetBinContent(j));
	  hToy->SetBinContent(j,value);
	}
				
	for (int j=1;j<=hMatrixToy->GetNbinsX();j++) {
	  for (int k=1;k<=hMatrixToy->GetNbinsY();k++) {
	    double value = gRandom->Gaus(uhist[i]->hMatrixFit->GetBinContent(j,k),uhist[i]->hMatrixFit->GetBinError(j,k));
	    hMatrixToy->SetBinContent(j,k,value);
	  }
	}

	prior myPriorToy(hMatrixToy,hToy,0.0);
	myPriorToy.unfold(hToy,1);
	bayesianUnfold myUnfoldingToy(hMatrixToy,myPriorToy.hPrior,0.0);
	myUnfoldingToy.unfold(hToy,nBayesianIter);
	TH1F *hRecoTmp = (TH1F*) myUnfoldingToy.hPrior->Clone();
				
	for (int j=1;j<=hRecoTmp->GetNbinsX();j++) {
	  hTmp[j]->Fill(hRecoTmp->GetBinContent(j));
	}
	delete hToy;
	delete hRecoTmp;
	delete hMatrixToy;
      }
      TF1 *fGaus = new TF1("fGaus","[0]*TMath::Gaus(x,[1],[2])");
      for (int j=1;j<=nbins_truth;j++)
	{
	  f->SetParameters(hTmp[j]->GetMaximum(),hTmp[j]->GetMean(),hTmp[j]->GetRMS());
				
	  if (hTmp[j]->GetMean()>0) {
	    hTmp[j]->Fit(fGaus,"LL Q ");
	    hTmp[j]->Fit(fGaus,"LL Q ");
	    uhist[i]->hReco->SetBinError(j,f->GetParameter(2));
	  }	       
	  f->SetParameters(hTmp2[j]->GetMaximum(),hTmp2[j]->GetMean(),hTmp2[j]->GetRMS());
	  if (hTmp2[j]->GetMean()>0) {
	    hTmp2[j]->Fit(fGaus,"LL Q ");
	    hTmp2[j]->Fit(fGaus,"LL Q ");
	    uhist[i]->hRecoBinByBin->SetBinError(j,f->GetParameter(2));
	  }	       
	  delete hTmp[j];
	  delete hTmp2[j];
	}
      cPbPb->cd(i+1);
    }

    uhist[i]->hMeas->SetMarkerStyle(20);
    uhist[i]->hMeas->SetMarkerColor(1);
    uhist[i]->hReco->SetMarkerStyle(24);
    uhist[i]->hReco->SetMarkerColor(2);
    uhist[i]->hReco->SetLineColor(2);
    uhist[i]->hReco->SetName(Form("hReco_cent%d",i));
    uhist[i]->hReco->Draw("");    
    makeHistTitle(uhist[i]->hReco,"","Jet p_{T} (GeV/c)","dN_{jets} / dp_{T}");
    uhist[i]->hReco->GetYaxis()->SetTitleOffset(1.3);
    uhist[i]->hReco->GetXaxis()->SetTitleOffset(1.2);
    uhist[i]->hGen->SetLineWidth(1);
    uhist[i]->hGen->SetLineColor(1);
    if(isMC)uhist[i]->hGen->Draw("hist same");
    uhist[i]->hReco->Draw("same");    
    uhist[i]->hRecoBinByBin->SetMarkerStyle(28);
    uhist[i]->hRecoBinByBin->SetMarkerColor(4);
    uhist[i]->hRecoBinByBin->SetLineColor(4);
    uhist[i]->hRecoBinByBin->Draw("same");    
    uhist[i]->hReco->SetAxisRange(60,300);
    TH1F *hReproduced = (TH1F*)myUnfolding.hReproduced->Clone(Form("hReproduced_cent%d",i));
    hReproduced->SetMarkerColor(4);
    hReproduced->SetMarkerStyle(24);
    uhist[i]->hMeas->Draw("same");    
		
    TLegend *leg = new TLegend(0.5,0.5,0.9,0.9);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->AddEntry(uhist[i]->hMeas,"Measured","pl");
    leg->AddEntry(uhist[i]->hReco,"Bayesian unfolded","pl");
    leg->AddEntry(uhist[i]->hRecoBinByBin,"Bin-by-bin unfolded","pl");
    if(isMC)leg->AddEntry(uhist[i]->hGen,"Generator level truth","l");
    leg->Draw();
  }	     
  
  cPbPb->Update();

 // ======================= Unfolding closure in MC =========================================================
  TCanvas * cRatio = new TCanvas("cRatio","Ratio",1200,600);
    TH1F * hReco[nbins_cent+1];
    TH1F * hRecoBinByBin[nbins_cent+1];
    TH1F * hMeas[nbins_cent+1];
    TH1F * hGen[nbins_cent+1];
    TLegend *leg[nbins_cent+1];
  TLine *line = new TLine(60,1,250,1);
	line->SetLineStyle(2);
	line->SetLineWidth(2);
 
    for (int i=0;i<=nbins_cent;i++) {
        hReco[i]          = (TH1F*)uhist[i]->hReco->Clone(Form("hReco_Cen%d", i));
        hRecoBinByBin[i]          = (TH1F*)uhist[i]->hRecoBinByBin->Clone(Form("hRecoBinByBin_Cen%d", i));
        hMeas[i]          = (TH1F*)uhist[i]->hMeas->Clone(Form("hMeas_Cen%d", i));
        if(isMC) hGen[i]          = (TH1F*)uhist[i]->hGen->Clone(Form("hGen_Cen%d", i));
    }
    
  if(isMC){
    cRatio->Divide(2,1);
      for (int i=0;i<=nbins_cent;i++) {
          
          hMeas[i]->Divide(hGen[i]);
          hRecoBinByBin[i]->Divide(hGen[i]);
          hReco[i]->Divide(hGen[i]);
          cRatio->cd(i+1);

		//hRecoPP->SetAxisRange(90,300,"X");
		hReco[i]->SetAxisRange(0,2,"Y");
		hReco[i]->SetMarkerStyle(24);
		hReco[i] ->SetLineColor(2);
		hReco[i] ->SetMarkerColor(2);
		hMeas[i]->SetMarkerStyle(20);
		hMeas[i]->SetLineColor(1);
		hMeas[i]->SetMarkerColor(1);
		hRecoBinByBin[i]->SetMarkerStyle(28);
		hRecoBinByBin[i]->SetLineColor(4);
		hRecoBinByBin[i]->SetMarkerColor(4);
		
		makeHistTitle(hReco[i],"","Jet p_{T} (GeV/c)","Reco / Truth");
		hReco[i]->GetYaxis()->SetTitleOffset(1.4);
		hReco[i]->GetXaxis()->SetTitleOffset(1.2);
		hReco[i]->Draw("");
		hRecoBinByBin[i]->Draw("same");
		hMeas[i]->Draw("same");
		line->Draw();
		
		leg[i] = myLegend(0.52,0.65,0.85,0.9);
		leg[i]->AddEntry(hReco[i],"Bayesian","pl");
		leg[i]->AddEntry(hRecoBinByBin[i],"Bin-by-bin","pl");
		leg[i]->AddEntry(hMeas[i],"no unfolding","pl");
		leg[i]->Draw();
		putCMSPrel(0.2,0.83,0.06);
		drawText("Anti-k_{T} Particle Flow Jets   R = 0.3",0.2,0.23,20);
		drawText("CMS Simulation",0.6,0.4,22);
		drawText("| #eta | <2 ",0.6,0.31,22);
      }
  }
  else {
      hMeas[nbins_cent]->Scale(1./CorFac[6]/5.3e9);
      hRecoBinByBin[nbins_cent]->Scale(1./CorFac[6]/5.3e9);
      hReco[nbins_cent]->Scale(1./CorFac[6]/5.3e9);
      cRatio->cd(1);
      
      for (int i=0;i<nbins_cent;i++) {
          hMeas[i]            ->Scale(1./CorFac[i]/1.0908e9/TAA[i]);
          hRecoBinByBin[i]            ->Scale(1./CorFac[i]/1.0908e9/TAA[i]);
          hReco[i]            ->Scale(1./CorFac[i]/1.0908e9/TAA[i]);
          
          hMeas[i]->Divide(hMeas[nbins_cent]);
          hRecoBinByBin[i]->Divide(hRecoBinByBin[nbins_cent]);
          hReco[i]->Divide(hReco[nbins_cent]);
          
          hReco[i]->SetAxisRange(0,2,"Y");
          hReco[i]->SetMarkerStyle(24);
          hReco[i] ->SetLineColor(2);
          hReco[i] ->SetMarkerColor(2);
          hMeas[i]->SetMarkerStyle(20);
          hMeas[i]->SetLineColor(1);
          hMeas[i]->SetMarkerColor(1);
          hRecoBinByBin[i]->SetMarkerStyle(28);
          hRecoBinByBin[i]->SetLineColor(4);
          hRecoBinByBin[i]->SetMarkerColor(4);
         // if(i==0){
          makeHistTitle(hReco[i],"","Jet p_{T} (GeV/c)","Spectra Ratio");
          hReco[i]->GetYaxis()->SetTitleOffset(1.4);
          hReco[i]->GetXaxis()->SetTitleOffset(1.2);
          hReco[i]->Draw("");
              leg[i] = myLegend(0.52,0.65,0.85,0.9);
              leg[i]->AddEntry(hReco[i],"Bayesian","pl");
              leg[i]->AddEntry(hRecoBinByBin[i],"Bin-by-bin","pl");
              leg[i]->AddEntry(hMeas[i],"no unfolding","pl");
              leg[i]->Draw();

       //   }
       //   else {
          hReco[i]->Draw("same");
          hRecoBinByBin[i]->Draw("same");
          hMeas[i]->Draw("same");
      //    }
       } 
         line->Draw();
          
          putCMSPrel(0.2,0.83,0.06);
          drawText(Form("#intL dt = %.f #mub^{-1}",150.),0.2,0.78,22);
          drawText("Anti-k_{T} Particle Flow Jets   R = 0.3",0.2,0.73,20);
          drawText("| #eta | <2 ",0.6,0.69,22);
  
  }
    cRatio->Update();

  pbpb_Unfo->Write();

  SysData systematics;

  // Iteration systematics
  TCanvas *cIterSys = new TCanvas("cIterSys","IterSys",1200,600);
  cIterSys->Divide(2,1);
  cIterSys->cd(2);
  TH1F *hRecoIterSysPP[100];
  TH1F *hRebinPP_tmp         = rebin(uhist[nbins_cent]->hReco, (char*)"hRebinPP_tmp");
  TLegend *legBayesianIterPP = myLegend(0.4,0.7,0.9,0.9);
  legBayesianIterPP->AddEntry("","PP","");
         
  for (int j=2;j<7;j++) {
    hRecoIterSysPP[j] = rebin(uhist[nbins_cent]->hRecoIterSys[j],Form("hRecoIterSysPP_IterSys%d",j));
    hRecoIterSysPP[j]->SetLineColor(colorCode[j-2]);
    hRecoIterSysPP[j]->SetMarkerColor(colorCode[j-2]);
    hRecoIterSysPP[j]->Divide(hRebinPP_tmp);
    if (j==2){
    //  makeHistTitle(hRecoIterSysPP[j],(char*)"",(char*)"Jet p_{T} (GeV/c)",(char*)"Ratio (Unfolded / Nominal)");
      makeHistTitle(hRecoIterSysPP[j],"","Jet p_{T} (GeV/c)","Ratio (Unfolded / Nominal)");
      hRecoIterSysPP[j]->SetTitleOffset(1.3,"Y");
      hRecoIterSysPP[j]->SetTitleOffset(1.2,"X");
      hRecoIterSysPP[j]->SetAxisRange(0,2,"Y");
      hRecoIterSysPP[j]->Draw(); 
    } else {
      hRecoIterSysPP[j]->Draw("same");
    }
         
    checkMaximumSys(systematics.hSysIter[nbins_cent],hRecoIterSysPP[j],0,1.1);
    legBayesianIterPP->AddEntry(hRecoIterSysPP[j],Form("Iteration %d",j),"pl");     
  }
      
  legBayesianIterPP->Draw();
  line->Draw();
  drawEnvelope(systematics.hSysIter[nbins_cent],(char*)"hist same");


  cIterSys->cd(1);
  TH1F *hRecoIterSysPbPb[100];
  TH1F *hRebinPbPb_tmp         = rebin(uhist[0]->hReco, (char*)"hRebinPbPb_tmp");
  TLegend *legBayesianIterPbPb = myLegend(0.4,0.7,0.9,0.9);
  legBayesianIterPbPb->AddEntry("","PbPb","");
  for (int j=2;j<7;j++) {
    hRecoIterSysPbPb[j] = rebin(uhist[0]->hRecoIterSys[j],Form("hRecoIterSysPbPb_IterSys%d",j));
    hRecoIterSysPbPb[j]->SetLineColor(colorCode[j-2]);
    hRecoIterSysPbPb[j]->SetMarkerColor(colorCode[j-2]);
    hRecoIterSysPbPb[j]->Divide(hRebinPbPb_tmp);
    if (j==2){
    //  makeHistTitle(hRecoIterSysPbPb[j],(char*)"",(char*)"Jet p_{T} (GeV/c)",(char*)"Ratio (Unfolded / Nominal)");
      makeHistTitle(hRecoIterSysPbPb[j],"","Jet p_{T} (GeV/c)","Ratio (Unfolded / Nominal)");
      hRecoIterSysPbPb[j]->SetTitleOffset(1.3,"Y");
      hRecoIterSysPbPb[j]->SetTitleOffset(1.2,"X");
      hRecoIterSysPbPb[j]->SetAxisRange(0,2,"Y");
      hRecoIterSysPbPb[j]->Draw(); 
    } else {
      hRecoIterSysPbPb[j]->Draw("same");
    }
         
    checkMaximumSys(systematics.hSysIter[0],hRecoIterSysPbPb[j],0,1.1);
    legBayesianIterPbPb->AddEntry(hRecoIterSysPbPb[j],Form("Iteration %d",j),"pl");     
  }
  legBayesianIterPbPb->Draw();
  line->Draw();
  drawEnvelope(systematics.hSysIter[0],(char*)"hist same");
  
  cIterSys->Update();
  
  TString data ;
  if(isMC) data="MC";
  else data="Data";
 TString anaType ;
  if(doBjets) anaType="Bjet";
  else anaType="Inclusive";
  
  if(SavePlot){
    cMatrix->SaveAs(Form("plots/%s%s%sResponseMatrix.gif", data.Data(), anaType.Data(), algoName[algo]));
    cPbPb->SaveAs(Form("plots/%s%s%sJetSpectra.gif",  data.Data(), anaType.Data(), algoName[algo]));
    cRatio->SaveAs(Form("plots/%s%s%sJetRatio.gif",  data.Data(), anaType.Data(), algoName[algo]));
    cIterSys->SaveAs(Form("plots/%s%s%sIterationSys.gif",  data.Data(), anaType.Data(), algoName[algo]));
}
}






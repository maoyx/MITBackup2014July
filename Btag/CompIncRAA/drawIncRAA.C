void drawIncRAA(int writeRaw=1, int grabUnfolded=0){

  gStyle->SetErrorX(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gROOT->ForceStyle(1);
  
  TFile *fPbPb, *fpp, *fUnfolded;
  TTree *tPbPb, *tpp;
  TH1F *hPbPb, *hpp;

  if(!grabUnfolded){

    fpp = new TFile("/net/hisrv0001/home/yenjie/scratch/hiForest/prod/productionPP/CMSSW_4_4_2_patch6/test/ppForest2/pp_merged_full.root") ; 
   // fpp = new TFile("/mnt/hadoop/cms/store/user/maoyx/hiForest/ppdata_ppReco_ak3PF_jetTrig_noIPupperCut.root");
  //  fPbPb = new TFile("/net/hisrv0001/home/mnguyen/scratch/bTaggingOutput/ntuples/PbPbdata_pt30by3_jpHICalibRepass_jet6580.root");
   // fPbPb = new TFile("/net/hisrv0001/home/mnguyen/scratch/bTaggingOutput/ntuples/PbPbdata_pt30by3_jpHICalibRepass_withDup_PU.root");
    fPbPb = new TFile("/net/hisrv0001/home/mnguyen/scratch/bTaggingOutput/ntuples/PbPbdata_pt30by3_jpHICalibRepass_withDup_PU_jet80_all.root");
    
    tPbPb = (TTree *)fPbPb->Get("nt");
 //   tpp = (TTree *)fpp->Get("nt");
    tpp = (TTree *)fpp->Get("ak3PFJetAnalyzer/t");
    tpp->AddFriend("hltanalysis/HltTree");
    tpp->AddFriend("skimanalysis/HltTree");
    tpp->AddFriend("hiEvtAnalyzer/HiTree");

    //const int nBins = 6;
    //double ptBin[nBins+1] = {60,70,85,105,130,170,250};
    const Double_t ptBin[] = {0,5,10,15,20,25,30,35,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260, 270, 280, 290, 300, 320, 350, 400, 500};
  //  const Double_t ptBin[] = {30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 200, 240, 300};
    const int nBins = sizeof(ptBin)/sizeof(Double_t)-1;
    
    hPbPb = new TH1F("hPbPb","PbPb Spectrum; p_{T} (GeV/c); d#sigma/dp_{T} [mb (GeV/c)];",nBins,ptBin);
    hpp = new TH1F("hpp","pp Spectrum; p_{T} [GeV/c]; Counts",nBins,ptBin);
    hPbPb->Sumw2();
    hpp->Sumw2();
    
    tPbPb->Draw("jtpt>>hPbPb","weight*(jet80==1)");
    //tPbPb->Draw("jtptA>>hPbPb","weight*(bin<2)");
    //tPbPb->Draw("jtptA>>hPbPb","weight*(bin>=28&&bin<36)");
   // tpp->Draw("jtpt>>hpp","weight","same");
 //   tpp->Draw("jtpt>>hpp","weight*(HLT_Jet80_noJetID_v1==1)","same");
    tpp->Draw("jtpt>>hpp","abs(vz)<15.&&pcollisionEventSelection==1&&pHBHENoiseFilter==1&&abs(jteta)<2&&HLT_Jet60_v1==1","same");
  }    
  else{

    //TFile *fUnfolded = new TFile("~/Work/bTagging/bJetRAA/pbpb_Unfo_akPu3PF_jtpt60_Inc.root");
    TFile *fUnfolded = new TFile("~/Work/bTagging/bJetRAA/pbpb_Unfo_akPu3PF_jtpt60_bJets.root");
    //hPbPb = (TH1F*)fUnfolded->Get("hReco_cent0");
    //hpp = (TH1F*)fUnfolded->Get("hReco_cent1");        
    hPbPb = (TH1F*)fUnfolded->Get("UnfoldedBinByBin_cent0");
    hpp = (TH1F*)fUnfolded->Get("UnfoldedBinByBin_cent1");        
  }
  
 if(writeRaw&&!grabUnfolded){
    TFile *fOut=new TFile("rawIncSpectra2011pp_MB.root","recreate");
    hPbPb->Write();
    hpp->Write();
    return;
  }
  

  
  hPbPb->SetLineColor(2);
  
  
  hPbPb->GetXaxis()->SetNdivisions(505);
  
  hPbPb->SetMarkerStyle(8);
  hpp->SetMarkerStyle(8);
  hpp->SetMarkerColor(2);
  
  
  
  
  TCanvas *c1=new TCanvas("c1","c1",600,600);
  
 
  
  hPbPb->Scale(1./5.67);  // taa
  //hPbPb->Scale(1./25.9);  // taa
  //hPbPb->Scale(1./0.17);  // taa
  float nMB = 1.09079385600000000e+09;
  //float nMB = 1.09079385600000000e+09*0.05;
  //float nMB = 1.09079385600000000e+09*0.2;
  hPbPb->Scale(1./nMB); //nMB
  hpp->Scale(1./5.33e9);  // luminosity

  

  TF1 *fpow = new TF1("fpow","[0]*pow(x,[1])",70,200);
  fpow->SetLineWidth(1);
  
  // divide out the bin-width                                                                                                                                 
  if(!grabUnfolded){    
    for(int i=0;i<hPbPb->GetNbinsX();i++){
      float val =     hPbPb->GetBinContent(i+1);
      float err =     hPbPb->GetBinError(i+1);
      float width =   hPbPb->GetBinWidth(i+1);
      hPbPb->SetBinContent(i+1,val/width);
      hPbPb->SetBinError(i+1,err/width);
    }
  
    for(int i=0;i<hpp->GetNbinsX();i++){
      float val =     hpp->GetBinContent(i+1);
      float err =     hpp->GetBinError(i+1);
      float width =   hpp->GetBinWidth(i+1);
      hpp->SetBinContent(i+1,val/width);
      hpp->SetBinError(i+1,err/width);
    }
  }


  // bin shift correction

  TH1F *hPbPbOrig=hPbPb->Clone("hPbPbOrig");

  for(int iter=0;iter<4;iter++){
    
    cout<<" iteration # "<<iter<<endl;
    hPbPb->Fit(fpow,"","N",70,250);
    for(int i=0;i<hPbPb->GetNbinsX();i++){
      float meanVal = fpow->Integral(hPbPb->GetBinLowEdge(i+1),hPbPb->GetBinLowEdge(i+1)+hPbPb->GetBinWidth(i+1))/hPbPb->GetBinWidth(i+1);
      float centVal = fpow->Eval(hPbPb->GetBinCenter(i+1));
      float binShiftCorr = centVal/meanVal;
      cout<<" i "<<i<<" corr "<<binShiftCorr<<endl;

      float val =     hPbPbOrig->GetBinContent(i+1);
      float err =     hPbPbOrig->GetBinError(i+1);

      hPbPb->SetBinContent(i+1,val*binShiftCorr);
      hPbPb->SetBinError(i+1,err*binShiftCorr);

    }
  }

  TH1F *hppOrig=hpp->Clone("hppOrig");
  
  for(int iter=0;iter<4;iter++){
    
    cout<<" iteration # "<<iter<<endl;
    hpp->Fit(fpow,"","N",70,250);
    for(int i=0;i<hpp->GetNbinsX();i++){
      float meanVal = fpow->Integral(hpp->GetBinLowEdge(i+1),hpp->GetBinLowEdge(i+1)+hpp->GetBinWidth(i+1))/hpp->GetBinWidth(i+1);
      float centVal = fpow->Eval(hpp->GetBinCenter(i+1));
      float binShiftCorr = centVal/meanVal;
      cout<<" i "<<i<<" corr "<<binShiftCorr<<endl;

      float val =     hppOrig->GetBinContent(i+1);
      float err =     hppOrig->GetBinError(i+1);

      hpp->SetBinContent(i+1,val*binShiftCorr);
      hpp->SetBinError(i+1,err*binShiftCorr);

    }
  }


  
  delete fpow;

  hPbPb->Draw();
  hpp->Draw("same");
  

  TLegend *leg=new TLegend(0.6,0.6,0.9,0.9);
  leg->AddEntry(hPbPb,"PbPb * T_{AA}","p");
  leg->AddEntry(hpp,"pp","p");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->Draw();


  TCanvas *c2=new TCanvas("c2","c2",600,600);
  TH1F *hRatio = hPbPb->Clone("hPbPb");
  hRatio->Reset();
  hRatio->SetYTitle("R_{AA}");
  //hRatio->Divide(hPbPb,hpp,1.,1.,"B");
  hRatio->Divide(hPbPb,hpp);

  hRatio->GetYaxis()->SetRangeUser(0.,1.);
 
  hRatio->GetXaxis()->SetRangeUser(50,250);
  hRatio->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hRatio->Draw();

  cout<<" numerator error "<<hPbPb->GetBinError(17)<<"/"<<hPbPb->GetBinContent(17)<<" = "<<hPbPb->GetBinError(17)/hPbPb->GetBinContent(17)<<endl;
  cout<<" denominator error "<<hpp->GetBinError(17)<<"/"<<hpp->GetBinContent(17)<<" = "<<hpp->GetBinError(17)/hpp->GetBinContent(17)<<endl;
  cout<<" ratio error "<<hRatio->GetBinError(17)<<"/"<<hRatio->GetBinContent(17)<<" = "<<hRatio->GetBinError(17)/hRatio->GetBinContent(17)<<endl;


}

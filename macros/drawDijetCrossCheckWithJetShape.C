#include "CutAndBinCollection2011.h"
#include <TRandom3.h>
#include <time.h>


void drawDijetCrossCheckWithJetShape() {
  
  TFile* inf1 = new TFile("fromYaxian/dijetFF_output_histograms_trkPtProjectOnJetAxis_trackPtCut2_finerBin.root");
  
  // jet
  TH1D* lpt1[5];
  TH1F* lpt2[5];
  TH1D* slpt1[5];
  TH1F* slpt2[5];
  
  // track
  TH1D* ltpt1[5];
  TH1F* ltpt2[5];
  TH1D* sltpt1[5];
  TH1F* sltpt2[5];

  for ( int icent=1; icent<=4 ; icent++) {
    lpt1[icent] = (TH1D*)inf1->Get(Form("hLjetPt_hidata_icent%d_irj999_fragMode1_closure100",icent));
    slpt1[icent] = (TH1D*)inf1->Get(Form("hSljetPt_hidata_icent%d_irj999_fragMode1_closure100",icent));
    ltpt1[icent] = (TH1D*)inf1->Get(Form("hpt_lJet_sigTrk_hidata_icent%d_irj999_fragMode1_closure100",icent));
    sltpt1[icent] = (TH1D*)inf1->Get(Form("hpt_slJet_sigTrk_hidata_icent%d_irj999_fragMode1_closure100",icent));
    ltpt1[icent]->Scale(lpt1[icent]->GetEntries());
    sltpt1[icent]->Scale(slpt1[icent]->GetEntries());
  }
  //  TFile* inf2 = new TFile("fromYaxian/forYongsun.root");
  TFile* inf2 = new TFile("fromYaxian/HIDataJetPtTrackPt.root");

  lpt2[1] = (TH1F*)inf2->Get("jetpt_0-10%");
  lpt2[2] = (TH1F*)inf2->Get("jetpt_10-30%");
  lpt2[3] = (TH1F*)inf2->Get("jetpt_30-50%");
  lpt2[4] = (TH1F*)inf2->Get("jetpt_50-100%");
  slpt2[1] = (TH1F*)inf2->Get("subjetpt_0-10%");
  slpt2[2] = (TH1F*)inf2->Get("subjetpt_10-30%");
  slpt2[3] = (TH1F*)inf2->Get("subjetpt_30-50%");
  slpt2[4] = (TH1F*)inf2->Get("subjetpt_50-100%");

  ltpt2[1] = (TH1F*)inf2->Get("leadingjettrackpt_0-10%");
  ltpt2[2] = (TH1F*)inf2->Get("leadingjettrackpt_10-30%");
  ltpt2[3] = (TH1F*)inf2->Get("leadingjettrackpt_30-50%");
  ltpt2[4] = (TH1F*)inf2->Get("leadingjettrackpt_50-100%");
  sltpt2[1] = (TH1F*)inf2->Get("subleadingjettrackpt_0-10%");
  sltpt2[2] = (TH1F*)inf2->Get("subleadingjettrackpt_10-30%");
  sltpt2[3] = (TH1F*)inf2->Get("subleadingjettrackpt_30-50%");
  sltpt2[4] = (TH1F*)inf2->Get("subleadingjettrackpt_50-100%");
  /*
    lpt2[1] = (TH1F*)inf2->Get("LeadingJetPt_Cent0_Cent10");
    lpt2[2] = (TH1F*)inf2->Get("LeadingJetPt_Cent10_Cent30");
    lpt2[3] = (TH1F*)inf2->Get("LeadingJetPt_Cent30_Cent50");
    lpt2[4] = (TH1F*)inf2->Get("LeadingJetPt_Cent50_Cent100");
    slpt2[1] = (TH1F*)inf2->Get("SubJetPt_Cent0_Cent10");
    slpt2[2] = (TH1F*)inf2->Get("SubJetPt_Cent10_Cent30");
    slpt2[3] = (TH1F*)inf2->Get("SubJetPt_Cent30_Cent50");
    slpt2[4] = (TH1F*)inf2->Get("SubJetPt_Cent30_Cent50");
  */
  
  TCanvas* c1 =new TCanvas("c1","",1200,700);
  makeMultiPanelCanvas(c1,4,2,0.0,0.0,0.2,0.15,0.02);
  
  TLegend* l2  =  new TLegend(0.03183659,0.5963235,0.7209577,0.8718487,NULL,"brNDC");
  for ( int icent=1; icent<=4 ; icent++) {
    c1->cd(icent);
    //  scaleInt(lff1[icent]);
    //  scaleInt(lff2[icent]);
    lpt1[icent]->Rebin(20);
    lpt2[icent]->Rebin(20);

    handsomeTH1(lpt1[icent],1);
    handsomeTH1(lpt2[icent],2);
    handsomeTH1(slpt1[icent],1);
    handsomeTH1(slpt2[icent],2);
    //    lpt1[icent]->SetAxisRange(0.00001,3,"Y");
    // lpt1[icent]->SetAxisRange(0,4.5,"X");
    //   lpt1[icent]->SetYTitle("PbPb/pp");
    cout << "lpt1[icent]->Integral() = " << lpt1[icent]->Integral()<<endl;
     cout << "lpt2[icent]->Integral() = " << lpt2[icent]->Integral()<<endl;
     lpt1[icent]->DrawCopy();
     lpt2[icent]->DrawCopy("same hist");
     gPad->SetLogy();
     c1->cd(icent+4);
    lpt1[icent]->Divide(lpt2[icent]);
    lpt1[icent]->SetAxisRange(0,2,"Y");
    lpt1[icent]->DrawCopy();
    jumSun(0,1,500,1);
    
  }
  
  TCanvas* c2 =new TCanvas("c2","",1200,700);
  makeMultiPanelCanvas(c2,4,2,0.0,0.0,0.2,0.15,0.02);
  
  for ( int icent=1; icent<=4 ; icent++) {
    cout << "slpt1[icent]->Integral() = " << slpt1[icent]->Integral()<<endl;
    cout << "slpt2[icent]->Integral() = " << slpt2[icent]->Integral()<<endl;    c2->cd(icent);
    //  scaleInt(lff1[icent]);
    //  scaleInt(lff2[icent]);
    slpt1[icent]->Rebin(20);
    slpt2[icent]->Rebin(20);

    //    slpt1[icent]->SetAxisRange(0.00001,3,"Y");
    // slpt1[icent]->SetAxisRange(0,4.5,"X");
    //   slpt1[icent]->SetYTitle("PbPb/pp");
    slpt1[icent]->DrawCopy();
    slpt2[icent]->DrawCopy("same hist");
    gPad->SetLogy();
    c2->cd(icent+4);
    slpt1[icent]->Divide(slpt2[icent]);
    slpt1[icent]->SetAxisRange(0,2,"Y");
    slpt1[icent]->DrawCopy();
    jumSun(0,1,500,1);
  }
  

  TCanvas* c3 =new TCanvas("c3","",1200,700);
  makeMultiPanelCanvas(c3,4,2,0.0,0.0,0.2,0.15,0.02);
  
  for ( int icent=1; icent<=4 ; icent++) {
    c3->cd(icent);
    //  scaleInt(lff1[icent]);
    //  scaleInt(lff2[icent]);

    handsomeTH1(ltpt1[icent],1);
    handsomeTH1(ltpt2[icent],2);
    handsomeTH1(sltpt1[icent],1);
    handsomeTH1(sltpt2[icent],2);
    //    ltpt1[icent]->SetAxisRange(0.00001,3,"Y");
    // ltpt1[icent]->SetAxisRange(0,4.5,"X");
    //   ltpt1[icent]->SetYTitle("PbPb/pp");
    ltpt1[icent]->DrawCopy();
    ltpt2[icent]->DrawCopy("same hist");
    gPad->SetLogy();
    c3->cd(icent+4);
    ltpt1[icent]->Divide(ltpt2[icent]);
    ltpt1[icent]->SetAxisRange(0,2,"Y");
    ltpt1[icent]->DrawCopy();
    jumSun(0,1,500,1);
  }


  TCanvas* c4 =new TCanvas("c4","",1200,700);
  makeMultiPanelCanvas(c4,4,2,0.0,0.0,0.2,0.15,0.02);
  
  for ( int icent=1; icent<=4 ; icent++) {
    c4->cd(icent);
    //  scalein(lff1[icent]);
    //  scaleInt(lff2[icent]);

    //    sltpt1[icent]->SetAxisRange(0.00001,3,"Y");
    // sltpt1[icent]->SetAxisRange(0,4.5,"X");
    //   sltpt1[icent]->SetYTitle("PbPb/pp");
    sltpt1[icent]->DrawCopy();
    sltpt2[icent]->DrawCopy("same hist");
    gPad->SetLogy();
    c4->cd(icent+4);
    cout << " here 1 : " << sltpt1[icent]->GetNbinsX() << endl;
    cout << " here 2 : " << sltpt2[icent]->GetNbinsX() << endl;
    sltpt1[icent]->Divide(sltpt2[icent]);
    sltpt1[icent]->SetAxisRange(0,2,"Y");
    sltpt1[icent]->DrawCopy();
    jumSun(0,1,500,1);
  }

  
}
/*
  lff2[icent]->DrawCopy("same");
  if ( icent == 1) drawText("Leading jet",0.3,0.65,1);
  drawText(Form("%.2f < A_{j} < %.2f", float(ajBin1[icent-1]), float(ajBin1[icent])), 0.3,0.89);
    jumSun(0,1,6.5,1);
    if ( icent == 2) {
    easyLeg(l2,"PbPb/pp");
    l2->AddEntry(lff2[icent],"2010 (HIN-11-004)");
    l2->AddEntry(lff1[icent],"2011");
    l2->Draw();
    }
  }
  
  for ( int icent=1; icent<=4 ; icent++) {
  c1->cd(icent+4);
  // scaleInt(sff1[icent]);
  //  scaleInt(sff2[icent]);
    handsomeTH1(sff1[icent],1);
    handsomeTH1(sff2[icent],2);
    sff1[icent]->SetAxisRange(0.00001,3,"Y");
    sff1[icent]->SetXTitle("#xi = ln(1/z)");
    sff1[icent]->SetAxisRange(0,4.5,"X");
    sff1[icent]->DrawCopy();
    sff2[icent]->DrawCopy("same");
    if ( icent == 1 ) drawText("Subleading jet",0.3,0.65,1);
    jumSun(0,1,6.5,1);
    }
    for ( int icent=1; icent<=4 ; icent++) {
    c1->cd(icent+12);
    sff1[icent]->Divide(sff2[icent]);
    sff1[icent]->SetAxisRange(0.,2,"Y");
    sff1[icentyyyyyyyyy]->Draw();
    jumSun(0,1,7,1);
    }
    c1->SaveAs("plotsOfDijetFF//jetFF_comparison2011_2010_raw.pdf");
*/

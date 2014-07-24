#include <TROOT.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <TVector3.h> 
#include <stdio.h>
#include <string.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TCut.h>

#define PI 3.14159;
void makeMultiPanelCanvas(TCanvas*& canv, const Int_t columns, 
			  const Int_t rows, const Float_t leftOffset=0.,
                          const Float_t bottomOffset=0., 
			  const Float_t leftMargin=0.2, 
			  const Float_t bottomMargin=0.2,
                          const Float_t edge=0.05);

void  JetResponseMacro_TheDeadlyEagle_Eta(){

  gROOT->ProcessLine(".x rootlogon.C");
  gROOT->ProcessLine(".L format1Dhisto.C");
  gROOT->ProcessLine(".L formatTGraph.C");
  gROOT->ProcessLine(".x betterColors.C");

TFile *FileA = TFile::Open(Form("../JEC/Corrected_dijet_pp_mergedpthatbins_2013MCV2.root"));
  //TFile *FileA = TFile::Open(Form("~/rootFiles/JEC/Files/20120521/Correcteddijet_pp_mergedpthatbins_2012MC.root"));
  TString outname = "JetResponse_Plots.root"; 
  TFile* outf = new TFile(outname,"recreate");

  const char* AlgoNames[] = {"ak1PF","ak2PF","ak3PF","ak4PF","ak5PF","ak6PF","ak1Calo","ak2Calo","ak3Calo","ak4Calo","ak5Calo","ak6Calo","icPu5"};
  
  TCanvas *c1 = new TCanvas("c1","c1",1100,700);
  makeMultiPanelCanvas(c1,3,2,0.0,0.0,0.2,0.15,0.07);
  TCanvas *c1B = new TCanvas("c1B","c1B",1100,700);
  makeMultiPanelCanvas(c1B,3,2,0.0,0.0,0.2,0.15,0.07);
  TCanvas *c1C = new TCanvas("c1C","c1C",1100,700);
  makeMultiPanelCanvas(c1C,3,2,0.0,0.0,0.2,0.15,0.07);
  const int cCanDiv = 13;
  int nCanvDiv = cCanDiv;
  const int CnXbins = 30;
  int nXbins = CnXbins;

  TH2D* iHistoCorrEta[cCanDiv];
  TH2D* iHistoRefEta[cCanDiv];
  TH2D* iHistoJtEta[cCanDiv];
  TH2D* iHistoRawEta[cCanDiv];
  TH1D* h1[cCanDiv][CnXbins];
  TF1* Gauss6[cCanDiv][CnXbins];
  double mean[cCanDiv][CnXbins];
  double sigma[cCanDiv][CnXbins];
  double meanErr[cCanDiv][CnXbins];
  double sigmaErr[cCanDiv][CnXbins];
  double xPoint[cCanDiv][CnXbins];
  double xPointErr[cCanDiv][CnXbins];
  TLegend*  leg[cCanDiv];

  for(int i =0; i<nCanvDiv; i++)
    {
if(i==0 || i==6) continue;//skip the ak1 algos
if(i==12) continue;//skip the icpU5 algos
    if(i<=5)c1->cd(i+1);
    if(i>5 && i<12)c1B->cd(i-5);
    if(i>=12)c1C->cd(i-12);
    if(i==0)  TTree* t      = (TTree*)FileA->Get("ak1PFJetAnalyzer/t");
    if(i==1)  TTree* t      = (TTree*)FileA->Get("ak2PFJetAnalyzer/t");
    if(i==2)  TTree* t      = (TTree*)FileA->Get("ak3PFJetAnalyzer/t");
    if(i==3)  TTree* t      = (TTree*)FileA->Get("ak4PFJetAnalyzer/t");
    if(i==4)  TTree* t      = (TTree*)FileA->Get("ak5PFJetAnalyzer/t");
    if(i==5)  TTree* t      = (TTree*)FileA->Get("ak6PFJetAnalyzer/t");
    if(i==6)  TTree* t      = (TTree*)FileA->Get("ak1CaloJetAnalyzer/t");
    if(i==7)  TTree* t      = (TTree*)FileA->Get("ak2CaloJetAnalyzer/t");
    if(i==8)  TTree* t      = (TTree*)FileA->Get("ak3CaloJetAnalyzer/t");
    if(i==9)  TTree* t      = (TTree*)FileA->Get("ak4CaloJetAnalyzer/t");
    if(i==10) TTree* t      = (TTree*)FileA->Get("ak5CaloJetAnalyzer/t");
    if(i==11) TTree* t      = (TTree*)FileA->Get("ak6CaloJetAnalyzer/t");
    if(i==12) TTree* t      = (TTree*)FileA->Get("icPu5JetAnalyzer/t");
      
      leg[i]= new TLegend(0.22,0.63,0.45,0.90);//top right
      leg[i]->SetFillColor(0);
      leg[i]->SetTextSize(0.05);
      leg[i]->SetBorderSize(0);
      
      iHistoCorrEta[i] = new TH2D(Form("%s_CorrEta",AlgoNames[i]),Form("%s_CorrEta",AlgoNames[i]),nXbins,-2,2,500,0,5);
      //t->Draw(Form("corrpt/refpt:jteta>>%s_CorrEta",AlgoNames[i]),Form("corrpt>0 && fabs(jteta)<2.0"),"goff");
      t->Draw(Form("corrpt/refpt:jteta>>%s_CorrEta",AlgoNames[i]),Form("corrpt>5 && refpt>5 && fabs(jteta)<2.0"),"goff");
      iHistoCorrEta[i]->Draw("colz");
      leg[i]->AddEntry(iHistoCorrEta[i],Form("%s |#eta|<2.0",AlgoNames[i]),"");
      leg[i]->AddEntry(iHistoCorrEta[i],Form("Corrected / ref p_{T}"),"");
      format1Dhisto(*iHistoCorrEta[i],250,-1,2,20,2,1,"Jet #eta","Corrected p_{T}/ ref p_{T}");//Red      
      leg[i]->Draw();
      for(int iX=iHistoCorrEta[i]->GetXaxis()->GetFirst(); iX<iHistoCorrEta[i]->GetXaxis()->GetLast(); iX++ )
	{
	  //cout<<"bin ( "<<iX<<" ) --limits ["<<iHistoCorrEta[i]->GetXaxis()->GetBinLowEdge(iX)<<" , "<<iHistoCorrEta[i]->GetXaxis()->GetBinUpEdge(iX)<<" ] "<<endl;
	  h1[i][iX] = new TH1D(Form("h1_%d_%d_py",i,iX),Form("h1_%d_%d_py",i,iX),500,0,5);
	  h1[i][iX] =(TH1D*)iHistoCorrEta[i]->ProjectionY(Form("h1_%d_%d_py",i,iX),iX,iX,"e");
	  Gauss6[i][iX] = new TF1(Form("F6_c%d_d%d",i,iX),"gaus",0,5);
	  Gauss6[i][iX]->SetParLimits(1,0.7,1.5);
	  h1[i][iX]->Fit(Form("F6_c%d_d%d",i,iX),"0Q");
	  mean[i][iX] = Gauss6[i][iX]->GetParameter(1);
	  sigma[i][iX] = Gauss6[i][iX]->GetParameter(2);
	  meanErr[i][iX] = Gauss6[i][iX]->GetParError(1);
	  sigmaErr[i][iX] = Gauss6[i][iX]->GetParError(2);
	  xPoint[i][iX] =iHistoCorrEta[i]->GetXaxis()->GetBinCenter(iX);
	  xPointErr[i][iX] = 0;
	  
	  if(i==0 && iX==1)//Just to test 
	    {
	      TCanvas *c11 = new TCanvas("c11","c11",500,400);
	      c11->cd();	    
	      h1[i][iX]->Draw();
	      Gauss6[i][iX]->Draw("same");
	    }	  
	}

      
    }
  


  TLegend*  leg2B[cCanDiv];
  TLegend*  leg2A[cCanDiv];
  TGraphErrors *CorrEta_Mean[cCanDiv];
  TCanvas *c2 = new TCanvas("c2","c2",1100,700);
  makeMultiPanelCanvas(c2,3,2,0.0,0.0,0.2,0.15,0.07);
  TCanvas *c2B = new TCanvas("c2B","c2B",1100,700);
  makeMultiPanelCanvas(c2B,3,2,0.0,0.0,0.2,0.15,0.07);
  TCanvas *c2C = new TCanvas("c2C","c2C",1100,700);
  makeMultiPanelCanvas(c2C,3,2,0.0,0.0,0.2,0.15,0.07);

  TGraphErrors *CorrEta_Sigma[cCanDiv];
  TCanvas *c3 = new TCanvas("c3","c3",1100,700);
  makeMultiPanelCanvas(c3,3,2,0.0,0.0,0.2,0.15,0.07);
  TCanvas *c3B = new TCanvas("c3B","c3B",1100,700);
  makeMultiPanelCanvas(c3B,3,2,0.0,0.0,0.2,0.15,0.07);
  TCanvas *c3C = new TCanvas("c3C","c3C",1100,700);
  makeMultiPanelCanvas(c3C,3,2,0.0,0.0,0.2,0.15,0.07);

  for(int i2 =0; i2<nCanvDiv; i2++)
    {
      leg2A[i2]= new TLegend(0.22,0.18,0.45,0.35);//top right
      leg2A[i2]->SetFillColor(0);
      leg2A[i2]->SetTextSize(0.05);
      leg2A[i2]->SetBorderSize(0);
      
      leg2B[i2]= new TLegend(0.22,0.18,0.45,0.35);//top right
      leg2B[i2]->SetFillColor(0);
      leg2B[i2]->SetTextSize(0.05);
      leg2B[i2]->SetBorderSize(0);

      double xLoc[CnXbins];
      double y2Loc[CnXbins];
      double y3Loc[CnXbins];
      double xLocErr[CnXbins];
      double y2LocErr[CnXbins];
      double y3LocErr[CnXbins];
      for(int iBin=0; iBin<nXbins; iBin++)
	{	  
	  xLoc[iBin] = xPoint[i2][iBin];
	  xLocErr[iBin] = xPointErr[i2][iBin];
	  y2Loc[iBin] = mean[i2][iBin];
	  y2LocErr[iBin] = meanErr[i2][iBin];
	  y3Loc[iBin] = sigma[i2][iBin];
	  y3LocErr[iBin] = sigmaErr[i2][iBin];
	}


    
    if(i2<=5)c2->cd(i2+1);
    if(i2>5 && i2<12)c2B->cd(i2-5);
    if(i2>=12)c2C->cd(i2-12);
      CorrEta_Mean[i2] = new TGraphErrors(nXbins,xLoc,y2Loc,xLocErr,y2LocErr);
      formatTGraph(*CorrEta_Mean[i2],250,-1,1,20,1,1,"Jet #eta","#mu ");
      leg2A[i2]->AddEntry(CorrEta_Mean[i2],Form("%s |#eta|<2.0",AlgoNames[i2]),"");
      leg2A[i2]->AddEntry(CorrEta_Mean[i2],Form("Corrected p_{T}/ ref p_{T}"),"lp");
      CorrEta_Mean[i2]->SetMaximum(1.15);
      CorrEta_Mean[i2]->SetMinimum(0.90);
      CorrEta_Mean[i2]->Draw("AP");
      leg2A[i2]->Draw();

    if(i2<=5)c3->cd(i2+1);
    if(i2>5 && i2<12)c3B->cd(i2-5);
    if(i2>=12)c3C->cd(i2-12);
      CorrEta_Sigma[i2] = new TGraphErrors(nXbins,xLoc,y3Loc,xLocErr,y3LocErr);
      formatTGraph(*CorrEta_Sigma[i2],250,-1,1,20,1,1,"Jet #eta","#sigma ");
      leg2B[i2]->AddEntry(CorrEta_Sigma[i2],Form("%s |#eta|<2.0",AlgoNames[i2]),"");
      leg2B[i2]->AddEntry(CorrEta_Sigma[i2],Form("Corrected p_{T}/ ref p_{T}"),"lp");
      CorrEta_Sigma[i2]->SetMaximum(0.6);
      CorrEta_Sigma[i2]->SetMinimum(-0.2);
      CorrEta_Sigma[i2]->Draw("AP");
      leg2B[i2]->Draw();

    }
  
  c1->Print("plots/pPb2013_0126/EtaCorrection2D_AKPF.pdf");
  c1B->Print("plots/pPb2013_0126/EtaCorrection2D_AKCalo.pdf");
  c1C->Print("plots/pPb2013_0126/EtaCorrection2D_IC.pdf");
  c2->Print("plots/pPb2013_0126/EtaCorrection1DMean_AKPF.pdf");
  c2B->Print("plots/pPb2013_0126/EtaCorrection1DMean_AKCalo.pdf");
  c2C->Print("plots/pPb2013_0126/EtaCorrection1DMean_IC.pdf");
  c3->Print("plots/pPb2013_0126/EtaCorrection1DSigma_AKPF.pdf");
  c3B->Print("plots/pPb2013_0126/EtaCorrection1DSigma_AKCalo.pdf");
  c3C->Print("plots/pPb2013_0126/EtaCorrection1DSigma_IC.pdf");


}




///////////////////////////////////////////////////////////////////////
//         TOOL BOX
//////////////////////////////////////////////////////////////////////
void makeMultiPanelCanvas(TCanvas*& canv,
                          const Int_t columns,
                          const Int_t rows,
                          const Float_t leftOffset,
                          const Float_t bottomOffset,
                          const Float_t leftMargin,
                          const Float_t bottomMargin,
                          const Float_t edge) {
   if (canv==0) {
      Error("makeMultiPanelCanvas","Got null canvas.");
      return;
   }
   canv->Clear();

   TPad* pad[columns][rows];
   Float_t Xlow[columns];
   Float_t Xup[columns];
   Float_t Ylow[rows];
   Float_t Yup[rows];
   Float_t PadWidth =
   (1.0-leftOffset)/((1.0/(1.0-leftMargin)) +
   (1.0/(1.0-edge))+(Float_t)columns-2.0);
   Float_t PadHeight =
   (1.0-bottomOffset)/((1.0/(1.0-bottomMargin)) +
   (1.0/(1.0-edge))+(Float_t)rows-2.0);
   Xlow[0] = leftOffset;
   Xup[0] = leftOffset + PadWidth/(1.0-leftMargin);
   Xup[columns-1] = 1;
   Xlow[columns-1] = 1.0-PadWidth/(1.0-edge);

   Yup[0] = 1;
   Ylow[0] = 1.0-PadHeight/(1.0-edge);
   Ylow[rows-1] = bottomOffset;
   Yup[rows-1] = bottomOffset + PadHeight/(1.0-bottomMargin);

   for(Int_t i=1;i<columns-1;i++) {
      Xlow[i] = Xup[0] + (i-1)*PadWidth;
      Xup[i] = Xup[0] + (i)*PadWidth;
   }
   Int_t ct = 0;
   for(Int_t i=rows-2;i>0;i--) {
      Ylow[i] = Yup[rows-1] + ct*PadHeight;
      Yup[i] = Yup[rows-1] + (ct+1)*PadHeight;
      ct++;
   }
   TString padName;
   for(Int_t i=0;i<columns;i++) {
      for(Int_t j=0;j<rows;j++) {
         canv->cd();
         padName = Form("p_%d_%d",i,j);
         pad[i][j] = new TPad(padName.Data(),padName.Data(),
            Xlow[i],Ylow[j],Xup[i],Yup[j]);
         if(i==0) pad[i][j]->SetLeftMargin(leftMargin);
         else pad[i][j]->SetLeftMargin(0);

         if(i==(columns-1)) pad[i][j]->SetRightMargin(edge);
         else pad[i][j]->SetRightMargin(0);

         if(j==0) pad[i][j]->SetTopMargin(edge);
         else pad[i][j]->SetTopMargin(0);

         if(j==(rows-1)) pad[i][j]->SetBottomMargin(bottomMargin);
         else pad[i][j]->SetBottomMargin(0);

         pad[i][j]->Draw();
         pad[i][j]->cd();
         pad[i][j]->SetNumber(columns*j+i+1);
      }
   }
}
void drawText(const char *text, float xp, float yp){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(63);
  tex->SetTextSize(17);
  //tex->SetTextSize(0.05);
  tex->SetTextColor(kBlack);
  tex->SetLineWidth(1);
  tex->SetNDC();
  tex->Draw();
}

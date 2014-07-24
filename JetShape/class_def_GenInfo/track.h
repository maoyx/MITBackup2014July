//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May  2 10:14:40 2012 by ROOT version 5.27/06b
// from TTree trackTree/v1
// found on file: /home/maoy/working/Dijet80_merged.root
//////////////////////////////////////////////////////////

#ifndef track_h
#define track_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class track {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           nEv;
   Int_t           nLumi;
   Int_t           nBX;
   Int_t           nRun;
   Int_t           nv;
   Float_t         vx[2];   //[nv]
   Float_t         vy[2];   //[nv]
   Float_t         vz[2];   //[nv]
   Int_t           nTrk;
   Float_t         trkPt[1203];   //[nTrk]
   Float_t         trkPtError[1203];   //[nTrk]
   Int_t           trkNHit[1203];   //[nTrk]
   Int_t           trkNlayer[1203];   //[nTrk]
   Int_t           trkNlayer3D[1203];   //[nTrk]
   Float_t         trkEta[1203];   //[nTrk]
   Float_t         trkPhi[1203];   //[nTrk]
   Int_t           trkQual[1203];   //[nTrk]
   Float_t         trkChi2[1203];   //[nTrk]
   Float_t         trkChi2hit1D[1203];   //[nTrk]
   Float_t         trkNdof[1203];   //[nTrk]
   Float_t         trkDz[1203];   //[nTrk]
   Float_t         trkDzError[1203];   //[nTrk]
   Float_t         trkDzError1[1203];   //[nTrk]
   Float_t         trkDzError2[1203];   //[nTrk]
   Float_t         trkDxy[1203];   //[nTrk]
   Float_t         trkDxyBS[1203];   //[nTrk]
   Float_t         trkDxy1[1203];   //[nTrk]
   Float_t         trkDxy2[1203];   //[nTrk]
   Float_t         trkDxyError[1203];   //[nTrk]
   Float_t         trkDxyErrorBS[1203];   //[nTrk]
   Float_t         trkDxyError1[1203];   //[nTrk]
   Float_t         trkDxyError2[1203];   //[nTrk]
   Float_t         trkDz1[1203];   //[nTrk]
   Float_t         trkDz2[1203];   //[nTrk]
   Float_t         trkVx[1203];   //[nTrk]
   Float_t         trkVy[1203];   //[nTrk]
   Float_t         trkVz[1203];   //[nTrk]
   Bool_t          trkFake[1203];   //[nTrk]
   Float_t         trkAlgo[1203];   //[nTrk]
   Int_t           pfType[1203];   //[nTrk]
   Float_t         pfCandPt[1203];   //[nTrk]
   Float_t         pfSumEcal[1203];   //[nTrk]
   Float_t         pfSumHcal[1203];   //[nTrk]
   Int_t           nParticle;
   Float_t         pStatus[487];   //[nParticle]
   Float_t         pPId[487];   //[nParticle]
   Float_t         pEta[487];   //[nParticle]
   Float_t         pPhi[487];   //[nParticle]
   Float_t         pPt[487];   //[nParticle]
   Float_t         pAcc[487];   //[nParticle]
   Float_t         pNRec[487];   //[nParticle]
   Int_t           pNHit[487];   //[nParticle]
   Float_t         mtrkPt[487];   //[nParticle]
   Float_t         mtrkPtError[487];   //[nParticle]
   Int_t           mtrkNHit[487];   //[nParticle]
   Int_t           mtrkNlayer[487];   //[nParticle]
   Int_t           mtrkNlayer3D[487];   //[nParticle]
   Int_t           mtrkQual[487];   //[nParticle]
   Float_t         mtrkChi2[487];   //[nParticle]
   Float_t         mtrkNdof[487];   //[nParticle]
   Float_t         mtrkDz1[487];   //[nParticle]
   Float_t         mtrkDzError1[487];   //[nParticle]
   Float_t         mtrkDxy1[487];   //[nParticle]
   Float_t         mtrkDxyError1[487];   //[nParticle]
   Float_t         mtrkAlgo[487];   //[nParticle]
   Int_t           mtrkPfType[487];   //[nParticle]
   Float_t         mtrkPfCandPt[487];   //[nParticle]
   Float_t         mtrkPfSumEcal[487];   //[nParticle]
   Float_t         mtrkPfSumHcal[487];   //[nParticle]

   // List of branches
   TBranch        *b_nEv;   //!
   TBranch        *b_nLumi;   //!
   TBranch        *b_nBX;   //!
   TBranch        *b_nRun;   //!
   TBranch        *b_nv;   //!
   TBranch        *b_vx;   //!
   TBranch        *b_vy;   //!
   TBranch        *b_vz;   //!
   TBranch        *b_nTrk;   //!
   TBranch        *b_trkPt;   //!
   TBranch        *b_trkPtError;   //!
   TBranch        *b_trkNHit;   //!
   TBranch        *b_trkNlayer;   //!
   TBranch        *b_trkNlayer3D;   //!
   TBranch        *b_trkEta;   //!
   TBranch        *b_trkPhi;   //!
   TBranch        *b_trkQual;   //!
   TBranch        *b_trkChi2;   //!
   TBranch        *b_trkChi2hit1D;   //!
   TBranch        *b_trkNdof;   //!
   TBranch        *b_trkDz;   //!
   TBranch        *b_trkDzError;   //!
   TBranch        *b_trkDzError1;   //!
   TBranch        *b_trkDzError2;   //!
   TBranch        *b_trkDxy;   //!
   TBranch        *b_trkDxyBS;   //!
   TBranch        *b_trkDxy1;   //!
   TBranch        *b_trkDxy2;   //!
   TBranch        *b_trkDxyError;   //!
   TBranch        *b_trkDxyErrorBS;   //!
   TBranch        *b_trkDxyError1;   //!
   TBranch        *b_trkDxyError2;   //!
   TBranch        *b_trkDz1;   //!
   TBranch        *b_trkDz2;   //!
   TBranch        *b_trkVx;   //!
   TBranch        *b_trkVy;   //!
   TBranch        *b_trkVz;   //!
   TBranch        *b_trkFake;   //!
   TBranch        *b_trkAlgo;   //!
   TBranch        *b_pfType;   //!
   TBranch        *b_pfCandPt;   //!
   TBranch        *b_pfSumEcal;   //!
   TBranch        *b_pfSumHcal;   //!
   TBranch        *b_nParticle;   //!
   TBranch        *b_pStatus;   //!
   TBranch        *b_pPId;   //!
   TBranch        *b_pEta;   //!
   TBranch        *b_pPhi;   //!
   TBranch        *b_pPt;   //!
   TBranch        *b_pAcc;   //!
   TBranch        *b_pNRec;   //!
   TBranch        *b_pNHit;   //!
   TBranch        *b_mtrkPt;   //!
   TBranch        *b_mtrkPtError;   //!
   TBranch        *b_mtrkNHit;   //!
   TBranch        *b_mtrkNlayer;   //!
   TBranch        *b_mtrkNlayer3D;   //!
   TBranch        *b_mtrkQual;   //!
   TBranch        *b_mtrkChi2;   //!
   TBranch        *b_mtrkNdof;   //!
   TBranch        *b_mtrkDz1;   //!
   TBranch        *b_mtrkDzError1;   //!
   TBranch        *b_mtrkDxy1;   //!
   TBranch        *b_mtrkDxyError1;   //!
   TBranch        *b_mtrkAlgo;   //!
   TBranch        *b_mtrkPfType;   //!
   TBranch        *b_mtrkPfCandPt;   //!
   TBranch        *b_mtrkPfSumEcal;   //!
   TBranch        *b_mtrkPfSumHcal;   //!

   track(TTree *tree=0);
   virtual ~track();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef track_cxx
track::track(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
/*   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/maoy/working/Dijet80_merged.root");
      if (!f) {
         f = new TFile("/home/maoy/working/Dijet80_merged.root");
      }
      tree = (TTree*)gDirectory->Get("trackTree");

   }*/
   Init(tree);
}

track::~track()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t track::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t track::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void track::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nEv", &nEv, &b_nEv);
   fChain->SetBranchAddress("nLumi", &nLumi, &b_nLumi);
   fChain->SetBranchAddress("nBX", &nBX, &b_nBX);
   fChain->SetBranchAddress("nRun", &nRun, &b_nRun);
   fChain->SetBranchAddress("nv", &nv, &b_nv);
   fChain->SetBranchAddress("vx", vx, &b_vx);
   fChain->SetBranchAddress("vy", vy, &b_vy);
   fChain->SetBranchAddress("vz", vz, &b_vz);
   fChain->SetBranchAddress("nTrk", &nTrk, &b_nTrk);
   fChain->SetBranchAddress("trkPt", trkPt, &b_trkPt);
   fChain->SetBranchAddress("trkPtError", trkPtError, &b_trkPtError);
   fChain->SetBranchAddress("trkNHit", trkNHit, &b_trkNHit);
   fChain->SetBranchAddress("trkNlayer", trkNlayer, &b_trkNlayer);
   fChain->SetBranchAddress("trkNlayer3D", trkNlayer3D, &b_trkNlayer3D);
   fChain->SetBranchAddress("trkEta", trkEta, &b_trkEta);
   fChain->SetBranchAddress("trkPhi", trkPhi, &b_trkPhi);
   fChain->SetBranchAddress("trkQual", trkQual, &b_trkQual);
   fChain->SetBranchAddress("trkChi2", trkChi2, &b_trkChi2);
   fChain->SetBranchAddress("trkChi2hit1D", trkChi2hit1D, &b_trkChi2hit1D);
   fChain->SetBranchAddress("trkNdof", trkNdof, &b_trkNdof);
   fChain->SetBranchAddress("trkDz", trkDz, &b_trkDz);
   fChain->SetBranchAddress("trkDzError", trkDzError, &b_trkDzError);
   fChain->SetBranchAddress("trkDzError1", trkDzError1, &b_trkDzError1);
   fChain->SetBranchAddress("trkDzError2", trkDzError2, &b_trkDzError2);
   fChain->SetBranchAddress("trkDxy", trkDxy, &b_trkDxy);
   fChain->SetBranchAddress("trkDxyBS", trkDxyBS, &b_trkDxyBS);
   fChain->SetBranchAddress("trkDxy1", trkDxy1, &b_trkDxy1);
   fChain->SetBranchAddress("trkDxy2", trkDxy2, &b_trkDxy2);
   fChain->SetBranchAddress("trkDxyError", trkDxyError, &b_trkDxyError);
   fChain->SetBranchAddress("trkDxyErrorBS", trkDxyErrorBS, &b_trkDxyErrorBS);
   fChain->SetBranchAddress("trkDxyError1", trkDxyError1, &b_trkDxyError1);
   fChain->SetBranchAddress("trkDxyError2", trkDxyError2, &b_trkDxyError2);
   fChain->SetBranchAddress("trkDz1", trkDz1, &b_trkDz1);
   fChain->SetBranchAddress("trkDz2", trkDz2, &b_trkDz2);
   fChain->SetBranchAddress("trkVx", trkVx, &b_trkVx);
   fChain->SetBranchAddress("trkVy", trkVy, &b_trkVy);
   fChain->SetBranchAddress("trkVz", trkVz, &b_trkVz);
   fChain->SetBranchAddress("trkFake", trkFake, &b_trkFake);
   fChain->SetBranchAddress("trkAlgo", trkAlgo, &b_trkAlgo);
   fChain->SetBranchAddress("pfType", pfType, &b_pfType);
   fChain->SetBranchAddress("pfCandPt", pfCandPt, &b_pfCandPt);
   fChain->SetBranchAddress("pfSumEcal", pfSumEcal, &b_pfSumEcal);
   fChain->SetBranchAddress("pfSumHcal", pfSumHcal, &b_pfSumHcal);
   fChain->SetBranchAddress("nParticle", &nParticle, &b_nParticle);
   fChain->SetBranchAddress("pStatus", pStatus, &b_pStatus);
   fChain->SetBranchAddress("pPId", pPId, &b_pPId);
   fChain->SetBranchAddress("pEta", pEta, &b_pEta);
   fChain->SetBranchAddress("pPhi", pPhi, &b_pPhi);
   fChain->SetBranchAddress("pPt", pPt, &b_pPt);
   fChain->SetBranchAddress("pAcc", pAcc, &b_pAcc);
   fChain->SetBranchAddress("pNRec", pNRec, &b_pNRec);
   fChain->SetBranchAddress("pNHit", pNHit, &b_pNHit);
   fChain->SetBranchAddress("mtrkPt", mtrkPt, &b_mtrkPt);
   fChain->SetBranchAddress("mtrkPtError", mtrkPtError, &b_mtrkPtError);
   fChain->SetBranchAddress("mtrkNHit", mtrkNHit, &b_mtrkNHit);
   fChain->SetBranchAddress("mtrkNlayer", mtrkNlayer, &b_mtrkNlayer);
   fChain->SetBranchAddress("mtrkNlayer3D", mtrkNlayer3D, &b_mtrkNlayer3D);
   fChain->SetBranchAddress("mtrkQual", mtrkQual, &b_mtrkQual);
   fChain->SetBranchAddress("mtrkChi2", mtrkChi2, &b_mtrkChi2);
   fChain->SetBranchAddress("mtrkNdof", mtrkNdof, &b_mtrkNdof);
   fChain->SetBranchAddress("mtrkDz1", mtrkDz1, &b_mtrkDz1);
   fChain->SetBranchAddress("mtrkDzError1", mtrkDzError1, &b_mtrkDzError1);
   fChain->SetBranchAddress("mtrkDxy1", mtrkDxy1, &b_mtrkDxy1);
   fChain->SetBranchAddress("mtrkDxyError1", mtrkDxyError1, &b_mtrkDxyError1);
   fChain->SetBranchAddress("mtrkAlgo", mtrkAlgo, &b_mtrkAlgo);
   fChain->SetBranchAddress("mtrkPfType", mtrkPfType, &b_mtrkPfType);
   fChain->SetBranchAddress("mtrkPfCandPt", mtrkPfCandPt, &b_mtrkPfCandPt);
   fChain->SetBranchAddress("mtrkPfSumEcal", mtrkPfSumEcal, &b_mtrkPfSumEcal);
   fChain->SetBranchAddress("mtrkPfSumHcal", mtrkPfSumHcal, &b_mtrkPfSumHcal);
   Notify();
}

Bool_t track::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void track::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t track::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef track_cxx

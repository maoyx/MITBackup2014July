#ifndef SpectraStudyTreeClass_h
#define SpectraStudyTreeClass_h

// Convinient Output Classes

class SpectraStudyTreeClass {
public :
   SpectraStudyTreeClass() : 
   fPthat(-999), fCrossx(-999), isMinPtHat(0), nNumEvt(0), nJets(0), fPdfx1(-999), fPdfx2(-999)
   {
   }

   // Declaration of leaf types
   float fPthat, fCrossx;
   int isMinPtHat;
   int nNumEvt;
   int   nJets;
   float fPdfx1;
   float fPdfx2 ;
   int   nTrks[1000];  //[nJets]
   float fJPt[1000];   //[nJets]
   float fJEt[1000];   //[nJets]
   float fJEta[1000];   //[nJets]
   float fJY[1000];     //[nJets]
   float fJPhi[1000];   //[nJets]

   void clear() {
      fPthat = -999; fCrossx = -999; isMinPtHat = 0; nNumEvt = 0; nJets = 0; fPdfx1 = -999 ; fPdfx2 = -999 ;
   }
};

#endif


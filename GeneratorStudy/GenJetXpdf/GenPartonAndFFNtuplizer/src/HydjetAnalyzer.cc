// -*- C++ -*-
//
// Package:    HydjetAnalyzer
// Class:      HydjetAnalyzer
// 
/**\class HydjetAnalyzer HydjetAnalyzer.cc yetkin/HydjetAnalyzer/src/HydjetAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yetkin Yilmaz
//         Created:  Tue Dec 18 09:44:41 EST 2007
// $Id: HydjetAnalyzer.cc,v 1.24 2011/01/21 15:45:18 yilmaz Exp $
//
//


// system include files
#include <memory>
#include <iostream>
#include <string>
#include <fstream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ServiceRegistry/interface/Service.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"
#include "SimDataFormats/HiGenData/interface/GenHIEvent.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "RecoJets/JetAlgorithms/interface/JetAlgoHelper.h" //for sorting 
#include "GenJetXpdf/GenPartonAndFFNtuplizer/interface/GenParticleInfo.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "HepMC/GenEvent.h"
#include "HepMC/HeavyIon.h"

#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"

// root include file
#include "TFile.h"
#include "TNtuple.h"

using namespace std;

static const int MAXPARTICLES = 5000000;
static const int MAXVTX = 1000;
static const int ETABINS = 3; // Fix also in branch string

//
// class decleration
//

struct HydjetEvent{

   int event;
   float b;
   float npart;
   float ncoll;
   float nhard;
   float phi0;
  float scale;

   int n[ETABINS];
   float ptav[ETABINS];

   int mult;
   float pt[MAXPARTICLES];
   float pz[MAXPARTICLES];
   float eta[MAXPARTICLES];
   float phi[MAXPARTICLES];
   int pdg[MAXPARTICLES];
   int chg[MAXPARTICLES];

   float vx;
   float vy;
   float vz;
   float vr;
   float scalePDF;
   float x1;
   float x2;
   
};

class HydjetAnalyzer : public edm::EDAnalyzer {
   public:
      explicit HydjetAnalyzer(const edm::ParameterSet&);
      ~HydjetAnalyzer();


   private:
      virtual void beginRun(const edm::Run&, const edm::EventSetup&) ;
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------

   std::ofstream out_b;
   std::string fBFileName;

   std::ofstream out_n;
   std::string fNFileName;

   std::ofstream out_m;
   std::string fMFileName;

  
   TTree* hydjetTree_;
   HydjetEvent hev_;

   TNtuple *nt;

   std::string output;           // Output filename
 
   bool doAnalysis_;
   bool printLists_;
   bool doCF_;
   bool doVertex_;
  bool useHepMCProduct_;
  bool doHI_;
  bool doParticles_;

   double etaMax_;
   double ptMin_;
  edm::InputTag src_;
  edm::InputTag genParticleSrc_;
  edm::InputTag genHIsrc_;
  edm::InputTag gjsrc_;

   edm::ESHandle < ParticleDataTable > pdt;
   edm::Service<TFileService> f;

   double pthatCut_;
   double crossX_; // cross-section in mb
   int32_t numEvt_; // number of events generated

   static const int MAXJETS = 50000;

   float fPthat;
   float fCrossx;
   int   nNumEvt;
   int   isMinPtHat;

   struct PJ{
      int   nJets;
      int   nTrks[MAXJETS];
      float fJPt[MAXJETS];
      float fJEt[MAXJETS];
      float fJEta[MAXJETS];
      float fJY[MAXJETS];
      float fJPhi[MAXJETS];
   };

   PJ jets_;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
HydjetAnalyzer::HydjetAnalyzer(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   fBFileName = iConfig.getUntrackedParameter<std::string>("output_b", "b_values.txt");
   fNFileName = iConfig.getUntrackedParameter<std::string>("output_n", "n_values.txt");
   fMFileName = iConfig.getUntrackedParameter<std::string>("output_m", "m_values.txt");
   doAnalysis_ = iConfig.getUntrackedParameter<bool>("doAnalysis", true);
   useHepMCProduct_ = iConfig.getUntrackedParameter<bool>("useHepMCProduct", true);
   printLists_ = iConfig.getUntrackedParameter<bool>("printLists", false);
   doCF_ = iConfig.getUntrackedParameter<bool>("doMixed", false);
   doVertex_ = iConfig.getUntrackedParameter<bool>("doVertex", false);
   etaMax_ = iConfig.getUntrackedParameter<double>("etaMax", 2);
   ptMin_ = iConfig.getUntrackedParameter<double>("ptMin", 0);
   src_ = iConfig.getUntrackedParameter<edm::InputTag>("src",edm::InputTag("generator"));
   genParticleSrc_ = iConfig.getUntrackedParameter<edm::InputTag>("src",edm::InputTag("hiGenParticles"));
   genHIsrc_ = iConfig.getUntrackedParameter<edm::InputTag>("src",edm::InputTag("heavyIon"));
   doParticles_ = iConfig.getUntrackedParameter<bool>("doParticles", true);

   gjsrc_ = iConfig.getUntrackedParameter<edm::InputTag>("gjsrc",edm::InputTag("ak3HiGenJets"));
   pthatCut_ = iConfig.getUntrackedParameter<double>("pthatCut", 0.0);
   crossX_ = iConfig.getUntrackedParameter<double>("crossX", 50.0);
   numEvt_ = iConfig.getUntrackedParameter<int>("numEvt",100);
}


HydjetAnalyzer::~HydjetAnalyzer()
{
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
HydjetAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace HepMC;
   using namespace reco;

   // Event Info
   edm::Handle<GenEventInfoProduct> genEvtInfo;
   iEvent.getByLabel("generator", genEvtInfo);
   fPthat = genEvtInfo->qScale();

   fCrossx = crossX_; // cross section needs to be by hands
   nNumEvt = numEvt_; // number of event generated (but can be different from accepted)

   if((int)pthatCut_!=0) isMinPtHat = 1;
   else isMinPtHat = 0;

   // this is needed for generation with min pt_hat = 0
   // because it automatically sets the max pt_hat = infinity
   if((int)pthatCut_!=0 && fPthat>pthatCut_) return;
  
   hev_.event = iEvent.id().event();
   for(int ieta = 0; ieta < ETABINS; ++ieta){
      hev_.n[ieta] = 0;
      hev_.ptav[ieta] = 0;
   }
   hev_.mult = 0;
      
   double phi0 = 0;
   double b = -1;
   double scale = -1;
   int npart = -1;
   int ncoll = -1;
   int nhard = -1;
   double vx = -99;
   double vy = -99;
   double vz = -99;
   double vr = -99;
   const GenEvent* evt;
  
   int nmix = -1;
   int np = 0;
   int sig = -1;
   int src = -1;

  //  cout <<"pdf ==========="  <<endl ;  
   if(useHepMCProduct_){
   if(doCF_){
     Handle<CrossingFrame<HepMCProduct> > cf;
     iEvent.getByLabel(InputTag("mix","source"),cf);
     MixCollection<HepMCProduct> mix(cf.product());
     nmix = mix.size();
     cout<<"Mix Collection Size: "<<mix<<endl;

     MixCollection<HepMCProduct>::iterator mbegin = mix.begin();
     MixCollection<HepMCProduct>::iterator mend = mix.end();
     
     for(MixCollection<HepMCProduct>::iterator mixit = mbegin; mixit != mend; ++mixit){
       const GenEvent* subevt = (*mixit).GetEvent();
       int all = subevt->particles_size();
       np += all;
       HepMC::GenEvent::particle_const_iterator begin = subevt->particles_begin();
       HepMC::GenEvent::particle_const_iterator end = subevt->particles_end();
       for(HepMC::GenEvent::particle_const_iterator it = begin; it != end; ++it){
	 if((*it)->status() == 1){
	   int pdg_id = (*it)->pdg_id();
	   float eta = (*it)->momentum().eta();
	   float phi = (*it)->momentum().phi();
	   float pt = (*it)->momentum().perp();
	   const ParticleData * part = pdt->particle(pdg_id );
	   int charge = static_cast<int>(part->charge());

	   hev_.pt[hev_.mult] = pt;
	   hev_.eta[hev_.mult] = eta;
	   hev_.phi[hev_.mult] = phi;
	   hev_.pdg[hev_.mult] = pdg_id;
	   hev_.chg[hev_.mult] = charge;

	   eta = fabs(eta);
	   int etabin = 0;
	   if(eta > 0.5) etabin = 1;
	   if(eta > 1.) etabin = 2;
	   if(eta < 2.){
	     hev_.ptav[etabin] += pt;
	     ++(hev_.n[etabin]);
	   }
	   ++(hev_.mult);
	   }
       }
     }
   }else{
   
   Handle<HepMCProduct> mc;
   iEvent.getByLabel(src_,mc);
   evt = mc->GetEvent();
   scale = evt->event_scale();
   const HepMC::PdfInfo *pdf = mc->GetEvent()->pdf_info();    
   if(pdf){
      hev_.scalePDF= pdf->scalePDF();
      hev_.x1= pdf->x1();
      hev_.x2= pdf->x2();
//      bjorken = ((pdf->x1())/((pdf->x1())+(pdf->x2())));
   }
   else { cout <<"no pdf found!!!" <<endl ; }
   const HeavyIon* hi = evt->heavy_ion();
   if(hi){
      b = hi->impact_parameter();
      npart = hi->Npart_proj()+hi->Npart_targ();
      ncoll = hi->Ncoll();
      nhard = hi->Ncoll_hard();
      phi0 = hi->event_plane_angle();
      
      if(printLists_){
	 out_b<<b<<endl;
	 out_n<<npart<<endl;
      }
   }
   
   src = evt->particles_size();
   
   HepMC::GenEvent::particle_const_iterator begin = evt->particles_begin();
   HepMC::GenEvent::particle_const_iterator end = evt->particles_end();
   for(HepMC::GenEvent::particle_const_iterator it = begin; it != end; ++it){
     if((*it)->status() == 1){
       int pdg_id = (*it)->pdg_id();
       float eta = (*it)->momentum().eta();
       float phi = (*it)->momentum().phi();
       float pt = (*it)->momentum().perp();
       float pz = (*it)->momentum().pz();
       const ParticleData * part = pdt->particle(pdg_id );
       int charge = static_cast<int>(part->charge());
       
       hev_.pt[hev_.mult] = pt;
       hev_.pz[hev_.mult] = pz;
       hev_.eta[hev_.mult] = eta;
       hev_.phi[hev_.mult] = phi;
       hev_.pdg[hev_.mult] = pdg_id;
       hev_.chg[hev_.mult] = charge;
       
       eta = fabs(eta);
       int etabin = 0;
       if(eta > 0.5) etabin = 1; 
       if(eta > 1.) etabin = 2;
       if(eta < 2.){
	 hev_.ptav[etabin] += pt;
	 ++(hev_.n[etabin]);
	 }
       ++(hev_.mult);
     }
   }  // end of partile loop

   // Get "GenParton"/"GenJet"
   Handle<vector<GenJet> > genjets;
   iEvent.getByLabel(gjsrc_,genjets);
  int totJet = genjets->size();
   jets_.nJets = 0;   // jets that pass cuts and saved

   vector<const GenJet *> sortedJets;

   for(int j = 0; j < totJet; ++j){
      const GenJet* jet = &((*genjets)[j]);
      sortedJets.push_back( & *jet);
   }

   sortByEtRef (&sortedJets);
   for(int ij = 0; ij < totJet; ij++){

      jets_.fJEt[jets_.nJets]   = sortedJets[ij]->et();
      jets_.fJPt[jets_.nJets]   = sortedJets[ij]->pt();
      jets_.fJPhi[jets_.nJets]  = sortedJets[ij]->phi();
      jets_.fJEta[jets_.nJets]  = sortedJets[ij]->eta();
      jets_.fJY[jets_.nJets]  = sortedJets[ij]->rapidity();
      jets_.nJets++;
   } //end of jet loop

   }
   }else{
     edm::Handle<reco::GenParticleCollection> parts;
     iEvent.getByLabel(genParticleSrc_,parts);
     for(unsigned int i = 0; i < parts->size(); ++i){
       const reco::GenParticle& p = (*parts)[i];
       hev_.pt[hev_.mult] = p.pt();
       hev_.eta[hev_.mult] = p.eta();
       hev_.phi[hev_.mult] = p.phi();
       hev_.pdg[hev_.mult] = p.pdgId();
       hev_.chg[hev_.mult] = p.charge();
       double eta = fabs(p.eta());

       int etabin = 0;
       if(eta > 0.5) etabin = 1;
       if(eta > 1.) etabin = 2;
       if(eta < 2.){
         hev_.ptav[etabin] += p.pt();
         ++(hev_.n[etabin]);
       }
       ++(hev_.mult);
     }
     if(doHI_){
       edm::Handle<GenHIEvent> higen;
       iEvent.getByLabel(genHIsrc_,higen);
     }
   }

   if(doVertex_){
      edm::Handle<edm::SimVertexContainer> simVertices;
      iEvent.getByType<edm::SimVertexContainer>(simVertices);
      
      if (! simVertices.isValid() ) throw cms::Exception("FatalError") << "No vertices found\n";
      int inum = 0;
      
      edm::SimVertexContainer::const_iterator it=simVertices->begin();
      SimVertex vertex = (*it);
      cout<<" Vertex position "<< inum <<" " << vertex.position().rho()<<" "<<vertex.position().z()<<endl;
      vx = vertex.position().x();
      vy = vertex.position().y();
      vz = vertex.position().z();
      vr = vertex.position().rho();
   }
   
   for(int i = 0; i<3; ++i){
      hev_.ptav[i] = hev_.ptav[i]/hev_.n[i];
   }
   
   hev_.b = b;
   hev_.scale = scale;
   hev_.npart = npart;
   hev_.ncoll = ncoll;
   hev_.nhard = nhard;
   hev_.phi0 = phi0;
   hev_.vx = vx;
   hev_.vy = vy;
   hev_.vz = vz;
   hev_.vr = vr;

   nt->Fill(nmix,np,src,sig);

   hydjetTree_->Fill();

}


// ------------ method called once each job just before starting event loop  ------------
void
HydjetAnalyzer::beginRun(const edm::Run&, const edm::EventSetup& iSetup) 
{
   iSetup.getData(pdt);
}

void 
HydjetAnalyzer::beginJob()
{

   if(printLists_){
      out_b.open(fBFileName.c_str());
      if(out_b.good() == false)
	 throw cms::Exception("BadFile") << "Can\'t open file " << fBFileName;
      out_n.open(fNFileName.c_str());
      if(out_n.good() == false)
	 throw cms::Exception("BadFile") << "Can\'t open file " << fNFileName;
      out_m.open(fMFileName.c_str());
      if(out_m.good() == false)
	 throw cms::Exception("BadFile") << "Can\'t open file " << fMFileName;
   }   
   
   if(doAnalysis_){
      nt = f->make<TNtuple>("nt","Mixing Analysis","mix:np:src:sig");

      hydjetTree_ = f->make<TTree>("hi","Tree of Hydjet Events");
      hydjetTree_->Branch("event",&hev_.event,"event/I");
      hydjetTree_->Branch("b",&hev_.b,"b/F");
      hydjetTree_->Branch("npart",&hev_.npart,"npart/F");
      hydjetTree_->Branch("ncoll",&hev_.ncoll,"ncoll/F");
      hydjetTree_->Branch("nhard",&hev_.nhard,"nhard/F");
      hydjetTree_->Branch("phi0",&hev_.phi0,"phi0/F");
      hydjetTree_->Branch("scale",&hev_.scale,"scale/F");

      hydjetTree_->Branch("n",hev_.n,"n[3]/I");
      hydjetTree_->Branch("ptav",hev_.ptav,"ptav[3]/F");

      if(doParticles_){
	
	hydjetTree_->Branch("mult",&hev_.mult,"mult/I");
	hydjetTree_->Branch("pt",hev_.pt,"pt[mult]/F");
	hydjetTree_->Branch("pz",hev_.pz,"pz[mult]/F");
	hydjetTree_->Branch("eta",hev_.eta,"eta[mult]/F");
	hydjetTree_->Branch("phi",hev_.phi,"phi[mult]/F");
	hydjetTree_->Branch("pdg",hev_.pdg,"pdg[mult]/I");
	hydjetTree_->Branch("chg",hev_.chg,"chg[mult]/I");
	
	hydjetTree_->Branch("scalePDF",&hev_.scalePDF,"scalePDF/F");
	hydjetTree_->Branch("x1",&hev_.x1,"x1/F");
	hydjetTree_->Branch("x2",&hev_.x2,"x2/F");
	hydjetTree_->Branch("vx",&hev_.vx,"vx/F");
	hydjetTree_->Branch("vy",&hev_.vy,"vy/F");
	hydjetTree_->Branch("vz",&hev_.vz,"vz/F");
	hydjetTree_->Branch("vr",&hev_.vr,"vr/F");

   hydjetTree_->Branch("fPthat",&fPthat,"fPthat/F");
   hydjetTree_->Branch("fCrossx",&fCrossx,"fCrossx/F");
   hydjetTree_->Branch("isMinPtHat",&isMinPtHat,"isMinPtHat/I");
   hydjetTree_->Branch("nNumEvt",&nNumEvt,"nNumEvt/I");
   hydjetTree_->Branch("nJets",&jets_.nJets,"nJets/I");
   hydjetTree_->Branch("fJPt",jets_.fJPt,"fJPt[nJets]/F");
   hydjetTree_->Branch("fJEt",jets_.fJEt,"fJEt[nJets]/F");
   hydjetTree_->Branch("fJEta",jets_.fJEta,"fJEta[nJets]/F");
   hydjetTree_->Branch("fJY",jets_.fJY,"fJY[nJets]/F");
   hydjetTree_->Branch("fJPhi",jets_.fJPhi,"fJPhi[nJets]/F");
      }
   }
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HydjetAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(HydjetAnalyzer);

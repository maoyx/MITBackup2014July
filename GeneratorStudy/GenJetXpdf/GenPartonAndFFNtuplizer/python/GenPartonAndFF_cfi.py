import FWCore.ParameterSet.Config as cms

genJetPDF = cms.EDAnalyzer('HydjetAnalyzer',
              gjsrc = cms.untracked.InputTag("ak3GenJets"),
              pthatCut = cms.untracked.double(0.0),
              crossX = cms.untracked.double(0.0), # cross section in mb
              numEvt = cms.untracked.int32(100) # number of events      
             )

genSpectAna = cms.EDAnalyzer('GenPartonAndFFNtuplizer',
              gsrc = cms.untracked.InputTag("genParticles"),
              gjsrc = cms.untracked.InputTag("ak3GenJets"),
              pthatCut = cms.untracked.double(0.0),
              crossX = cms.untracked.double(0.0), # cross section in mb
              numEvt = cms.untracked.int32(100) # number of events                             
)

genSpectAnaForTOP = cms.EDAnalyzer('GenPartonAndFFNtuplizerForTOP',
              gsrc = cms.untracked.InputTag("genParticles"),
              gjsrc = cms.untracked.InputTag("ak3GenJets"),
              pthatCut = cms.untracked.double(0.0),
              crossX = cms.untracked.double(0.0), # cross section in mb
              numEvt = cms.untracked.int32(100) # number of events                             
)

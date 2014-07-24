version="538"
tracks="generalTracks"
sample="PythiaZ2_5TeV"

import FWCore.ParameterSet.Config as cms
process = cms.Process('jecdb')
process.load('CondCore.DBCommon.CondDBCommon_cfi')
process.CondDBCommon.connect = 'sqlite_file:JEC_PA5TEV_PUalgos_CMSSW538_2013.db'
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1))
process.source = cms.Source('EmptySource')
process.PoolDBOutputService = cms.Service('PoolDBOutputService',
                                          process.CondDBCommon,
                                          toPut = cms.VPSet(


    cms.PSet(
    record = cms.string('AKPu2PF'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_'+tracks+'_'+sample+'_'+version+'_AKPu2PF'),
    label  = cms.string('AKPu2PF')
    ),
    cms.PSet(
    record = cms.string('AKPu3PF'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_'+tracks+'_'+sample+'_'+version+'_AKPu3PF'),
    label  = cms.string('AKPu3PF')
    ),
    cms.PSet(
    record = cms.string('AKPu4PF'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_'+tracks+'_'+sample+'_'+version+'_AKPu4PF'),
    label  = cms.string('AKPu4PF')
    ),
    cms.PSet(
    record = cms.string('AKPu5PF'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_'+tracks+'_'+sample+'_'+version+'_AKPu5PF'),
    label  = cms.string('AKPu5PF')
    ),
    cms.PSet(
    record = cms.string('AKPu6PF'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_'+tracks+'_'+sample+'_'+version+'_AKPu6PF'),
    label  = cms.string('AKPu6PF')
    ),
                                          cms.PSet(
    record = cms.string('AKPu2Calo'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_'+sample+'_'+version+'_AKPu2Calo'),
    label  = cms.string('AKPu2Calo')
    ),
                                          cms.PSet(
    record = cms.string('AKPu3Calo'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_'+sample+'_'+version+'_AKPu3Calo'),
    label  = cms.string('AKPu3Calo')
    ),
                                          cms.PSet(
    record = cms.string('AKPu4Calo'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_'+sample+'_'+version+'_AKPu4Calo'),
    label  = cms.string('AKPu4Calo')
    ),
                                          cms.PSet(
    record = cms.string('AKPu5Calo'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_'+sample+'_'+version+'_AKPu5Calo'),
    label  = cms.string('AKPu5Calo')
    ),
                                          cms.PSet(
    record = cms.string('AKPu6Calo'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_'+sample+'_'+version+'_AKPu6Calo'),
    label  = cms.string('AKPu6Calo')
    ),


                                          )
)
process.dbWriterAKPu2PFTowers = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('JEC_dijet'),
                                       algo   = cms.untracked.string('AKPu2PF')
                                       )
process.dbWriterAKPu3PFTowers = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('JEC_dijet'),
                                       algo   = cms.untracked.string('AKPu3PF')
                                       )
process.dbWriterAKPu4PFTowers = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('JEC_dijet'),
                                       algo   = cms.untracked.string('AKPu4PF')
                                       )
process.dbWriterAKPu5PFTowers = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('JEC_dijet'),
                                       algo   = cms.untracked.string('AKPu5PF')
                                       )
process.dbWriterAKPu6PFTowers = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('JEC_dijet'),
                                       algo   = cms.untracked.string('AKPu6PF')
                                       )

process.dbWriterAKPu2Calo = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('JEC_dijet'),
                                       algo   = cms.untracked.string('AKPu2Calo')
                                       )
process.dbWriterAKPu3Calo = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('JEC_dijet'),
                                       algo   = cms.untracked.string('AKPu3Calo')
                                       )
process.dbWriterAKPu4Calo = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('JEC_dijet'),
                                       algo   = cms.untracked.string('AKPu4Calo')
                                       )
process.dbWriterAKPu5Calo = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('JEC_dijet'),
                                       algo   = cms.untracked.string('AKPu5Calo')
                                       )
process.dbWriterAKPu6Calo = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('JEC_dijet'),
                                       algo   = cms.untracked.string('AKPu6Calo')
                                       )

process.p = cms.Path(

process.dbWriterAKPu3PFTowers +
process.dbWriterAKPu4PFTowers +
process.dbWriterAKPu5PFTowers +
process.dbWriterAKPu3Calo +
process.dbWriterAKPu4Calo +
process.dbWriterAKPu5Calo 

)
'''
process.p = cms.Path(

process.dbWriterAKPu1PFTowers +
process.dbWriterAKPu2PFTowers +
process.dbWriterAKPu3PFTowers +
process.dbWriterAKPu4PFTowers +
process.dbWriterAKPu5PFTowers +
process.dbWriterAKPu6PFTowers +
process.dbWriterAKPu2Calo +
process.dbWriterAKPu3Calo +
process.dbWriterAKPu4Calo +
process.dbWriterAKPu5Calo +
process.dbWriterAKPu6Calo 

) 
'''

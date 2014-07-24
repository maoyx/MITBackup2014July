import FWCore.ParameterSet.Config as cms
process = cms.Process('jecdb')
process.load('CondCore.DBCommon.CondDBCommon_cfi')
process.CondDBCommon.connect = 'sqlite_file:JEC_HI2760_CMSSW501_2012.db'
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1))
process.source = cms.Source('EmptySource')
process.PoolDBOutputService = cms.Service('PoolDBOutputService',
                                          process.CondDBCommon,
                                          toPut = cms.VPSet(


    cms.PSet(				  
    record = cms.string('AK1PF'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_hiGoodTightTracks_PythiaZ2_442p5_AK1PF'),
    label  = cms.string('AK1PF')
    ),
    cms.PSet(
    record = cms.string('AK2PF'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_hiGoodTightTracks_PythiaZ2_442p5_AK2PF'),
    label  = cms.string('AK2PF')
    ),
    cms.PSet(
    record = cms.string('AK3PF'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_hiGoodTightTracks_PythiaZ2_442p5_AK3PF'),
    label  = cms.string('AK3PF')
    ),
    cms.PSet(
    record = cms.string('AK4PF'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_hiGoodTightTracks_PythiaZ2_442p5_AK4PF'),
    label  = cms.string('AK4PF')
    ),
    cms.PSet(
    record = cms.string('AK5PF'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_hiGoodTightTracks_PythiaZ2_442p5_AK5PF'),
    label  = cms.string('AK5PF')
    ),
    cms.PSet(
    record = cms.string('AK6PF'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_hiGoodTightTracks_PythiaZ2_442p5_AK6PF'),
    label  = cms.string('AK6PF')
    ),
                                          cms.PSet(
    record = cms.string('AK1Calo'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_hiGoodTightTracks_PythiaZ2_442p5_AK1Calo'),
    label  = cms.string('AK1Calo')
    ),
                                          cms.PSet(
    record = cms.string('AK2Calo'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_hiGoodTightTracks_PythiaZ2_442p5_AK2Calo'),
    label  = cms.string('AK2Calo')
    ),
                                          cms.PSet(
    record = cms.string('AK3Calo'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_hiGoodTightTracks_PythiaZ2_442p5_AK3Calo'),
    label  = cms.string('AK3Calo')
    ),
                                          cms.PSet(
    record = cms.string('AK4Calo'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_hiGoodTightTracks_PythiaZ2_442p5_AK4Calo'),
    label  = cms.string('AK4Calo')
    ),
                                          cms.PSet(
    record = cms.string('AK5Calo'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_hiGoodTightTracks_PythiaZ2_442p5_AK5Calo'),
    label  = cms.string('AK5Calo')
    ),
                                          cms.PSet(
    record = cms.string('AK6Calo'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_hiGoodTightTracks_PythiaZ2_442p5_AK6Calo'),
    label  = cms.string('AK6Calo')
    ),
                                          cms.PSet(
    record = cms.string('IC5Calo'),
    tag    = cms.string('JetCorrectorParametersCollection_HI_Calo_hiGoodTightTracks_D6T_413_IC5Calo'),
    label  = cms.string('IC5Calo')
    ),


                                          )
)
process.dbWriterAK1PFTowers = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('JEC_dijet'),
                                       algo   = cms.untracked.string('AK1PF')
                                       )
process.dbWriterAK2PFTowers = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('JEC_dijet'),
                                       algo   = cms.untracked.string('AK2PF')
                                       )
process.dbWriterAK3PFTowers = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('JEC_dijet'),
                                       algo   = cms.untracked.string('AK3PF')
                                       )
process.dbWriterAK4PFTowers = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('JEC_dijet'),
                                       algo   = cms.untracked.string('AK4PF')
                                       )
process.dbWriterAK5PFTowers = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('JEC_dijet'),
                                       algo   = cms.untracked.string('AK5PF')
                                       )
process.dbWriterAK6PFTowers = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('JEC_dijet'),
                                       algo   = cms.untracked.string('AK6PF')
                                       )

process.dbWriterAK1Calo = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('JEC_dijet'),
                                       algo   = cms.untracked.string('AK1Calo')
                                       )
process.dbWriterAK2Calo = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('JEC_dijet'),
                                       algo   = cms.untracked.string('AK2Calo')
                                       )
process.dbWriterAK3Calo = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('JEC_dijet'),
                                       algo   = cms.untracked.string('AK3Calo')
                                       )
process.dbWriterAK4Calo = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('JEC_dijet'),
                                       algo   = cms.untracked.string('AK4Calo')
                                       )
process.dbWriterAK5Calo = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('JEC_dijet'),
                                       algo   = cms.untracked.string('AK5Calo')
                                       )
process.dbWriterAK6Calo = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('JEC_dijet'),
                                       algo   = cms.untracked.string('AK6Calo')
                                       )
process.dbWriterIC5Calo = cms.EDAnalyzer('JetCorrectorDBWriter',
                                       era    = cms.untracked.string('HI_Calo_hiGoodTightTracks_D6T_413'),
                                       algo   = cms.untracked.string('IC5Calo')
                                       )

process.p = cms.Path(

process.dbWriterAK1PFTowers +
process.dbWriterAK2PFTowers +
process.dbWriterAK3PFTowers +
process.dbWriterAK4PFTowers +
process.dbWriterAK5PFTowers +
process.dbWriterAK6PFTowers +
process.dbWriterAK1Calo +
process.dbWriterAK2Calo +
process.dbWriterAK3Calo +
process.dbWriterAK4Calo +
process.dbWriterAK5Calo +
process.dbWriterAK6Calo +
process.dbWriterIC5Calo 

)
'''
process.p = cms.Path(

process.dbWriterAK1PFTowers +
process.dbWriterAK2PFTowers +
process.dbWriterAK3PFTowers +
process.dbWriterAK4PFTowers +
process.dbWriterAK5PFTowers +
process.dbWriterAK6PFTowers +
process.dbWriterIC5Calo +
process.dbWriterAK1Calo +
process.dbWriterAK2Calo +
process.dbWriterAK3Calo +
process.dbWriterAK4Calo +
process.dbWriterAK5Calo +
process.dbWriterAK6Calo 

) 
'''

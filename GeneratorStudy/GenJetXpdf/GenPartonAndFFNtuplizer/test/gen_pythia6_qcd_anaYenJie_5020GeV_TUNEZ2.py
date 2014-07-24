import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import os

# Example) CFG.py output="spectAnaGEN.root" maxEvents=1000 processType="NSD_0_to_5"

# Available processType
# NSD_0_to_5, NSD_5_to_10, NSD_10_to_20, NSD_20_to_30, NSD_30_to_50, NSD_50_to_80, NSD_80_to_120
# NSD_120_to_170, NSD_170_to_230, NSD_230_to_300, and so on

# ============= Pythia pre-setting ============================
# setup 'standard'  options
options = VarParsing.VarParsing ('standard')

options.output = 'spectAnaGEN_fromTFileService.root'
options.maxEvents = 1000

# my own variable
# available processType in customiseGEN_cfi
options.register('processType',
#                 "NSD_230_to_300",
                 "NSD_50_to_80",
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 "Pythia process type with pT_hat range")

options.register('sqrtS',
                 5020.0,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.float,
                 "Center-of-mass energy")

options.register('processType7TeVXSec',
                 "Z2_5TeV_NSD_50_to_80",
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 "Pythia XSection")

# get and parse the command line arguments
options.parseArguments()

# =============== Actual cfg ==================================
process = cms.Process('GEN')

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.load('Configuration/StandardSequences/EndOfProcess_cff')
process.load('Configuration/EventContent/EventContent_cff')
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("PhysicsTools.HepMCCandAlgos.genParticles_cfi")

process.load("Configuration.StandardSequences.Services_cff")
process.load("GeneratorInterface.HydjetInterface.hydjetDefault_cfi")

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.5 $'),
    annotation = cms.untracked.string('100'),
    name = cms.untracked.string('PyReleaseValidation')
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)
process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound')
)
# Input source
process.source = cms.Source("EmptySource")

# ============= Pythia setting  ================================
from Configuration.Generator.PythiaUEZ2Settings_cfi import *

process.generator = cms.EDFilter("Pythia6GeneratorFilter",
    pythiaPylistVerbosity = cms.untracked.int32(0),
    filterEfficiency = cms.untracked.double(1.0),
    pythiaHepMCVerbosity = cms.untracked.bool(True),
    comEnergy = cms.double(5020.0),
    maxEventsToPrint = cms.untracked.int32(0),
    PythiaParameters = cms.PSet(
         pythiaUESettingsBlock,
         processParameters = cms.vstring(
                 'MSEL=1         ! High Pt QCD',
                 'CKIN(3)=50     ! Pt hat lower cut',
                 'CKIN(4)=80     ! Pt hat upper cut'
                 ),
         parameterSets = cms.vstring('pythiaUESettings',
                                     'processParameters')
         )
)

process.gen_step = cms.Path(process.generator
                            *process.genParticles)

# update the process parameters and c.o.m energy
from MCGeneration.PPSpectraPythiaTunes.customiseGEN_cfi import *
updatePy6ProcParameters(process.generator,options.processType,options.sqrtS)

# ============= Gen jet ================================
# Re-make genjets for 35x reprocessing of 31x MC
process.load("RecoJets.Configuration.GenJetParticles_cff")
process.load("RecoJets.Configuration.RecoGenJets_cff")

process.genjet_step = cms.Path(process.genJetParticles *
                               process.ak5GenJets *
                               process.ak7GenJets *
                               process.iterativeCone5GenJets)


# =============== spectra ana ==========================
from GenJetXpdf.GenPartonAndFFNtuplizer.customise_cfi import *

process.load("GenJetXpdf.GenPartonAndFFNtuplizer.GenPartonAndFF_cfi")
process.ana_step = cms.Path(process.genSpectAna)
process.ana_step2 = cms.Path(process.genJetPDF)
process.genSpectAna.crossX = getPy6ProcXsection(options.processType7TeVXSec)
process.genSpectAna.numEvt = options.maxEvents
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string(options.output)
                                   )
process = enableMinPtHatCut(process,options.processType) 

# =============== Output ================================
process.output = cms.OutputModule("PoolOutputModule",
   outputCommands = cms.untracked.vstring(
    'keep *_genParticles_*_*',
    'keep *_iterativeCone5GenJets_*_*'
    ),
   fileName = cms.untracked.string('test_fromOutputModule.root'),
   dataset = cms.untracked.PSet(
    dataTier = cms.untracked.string('GEN'),
    filterName = cms.untracked.string('')
    ),
   SelectEvents = cms.untracked.PSet(
    SelectEvents = cms.vstring('generation_step2')
    )
)


# =============== Schedule =====================

process.schedule = cms.Schedule(process.gen_step,
                                process.genjet_step,
                                process.ana_step2,
                                process.ana_step)

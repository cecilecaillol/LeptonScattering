import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1000) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(100)

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '106X_dataRun2_v35', '')

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(

        '/store/user/wangjian/mpmp_SFGen/RunIISummer20UL18MiniAODv2_v3/240408_075851/0000/aammmm_RunIISummer20UL18MiniAODv2_tm_1.root'

    ),
    duplicateCheckMode = cms.untracked.string('noDuplicateCheck')

)

process.load( "PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff" )
process.load( "PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff" )

from EgammaUser.EgammaPostRecoTools.EgammaPostRecoTools import setupEgammaPostRecoSeq

setupEgammaPostRecoSeq(process,era='2017-UL',
                                     eleIDModules=['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V2_cff',
                                     'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV70_cff',
                                     'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_iso_V2_cff',
                                     'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_noIso_V2_cff'],
                                     phoIDModules=['RecoEgamma.PhotonIdentification.Identification.mvaPhotonID_Fall17_94X_V2_cff',
                                     'RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Fall17_94X_V2_cff']
)  

process.demo = cms.EDAnalyzer("FRAnlzr",
    MC = cms.bool(False), #False
    year = cms.int32(2017),
    vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    muons = cms.InputTag("slimmedMuons"),
    mcmapmuons = cms.InputTag("muonsMCMatchForTable"),
    electrons = cms.InputTag("slimmedElectrons"),
    mcmapelectrons = cms.InputTag("electronsMCMatchForTable"),
    pfCands = cms.InputTag("packedPFCandidates"),
    packedgens = cms.InputTag("packedGenParticles"),
    pruned = cms.InputTag("prunedGenParticles"),
    beamSpotHandle = cms.InputTag("offlineBeamSpot"),
    triggerBitsH = cms.InputTag("TriggerResults", "", "HLT"),
    metfilterBitsH = cms.InputTag("TriggerResults", "", "PAT"),
    generatorLabel       = cms.InputTag("generator"),
    pileupInfo=cms.InputTag('slimmedAddPileupInfo'),
    mets = cms.InputTag("slimmedMETsPuppi"),
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('tree_fr.root'))

process.p = cms.Path(process.egammaPostRecoSeq+process.demo)

import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(500) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(100)

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '106X_dataRun2_v35', '')

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(

        #'/store/mc/RunIISummer20UL18MiniAODv2/WpWpJJ_EWK_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v2/2560000/2A06992B-5F8E-D84A-98AE-5AEEF65D4499.root'
        #'/store/data/Run2018A/DoubleMuon/MINIAOD/UL2018_MiniAODv2_GT36-v1/2430000/00267D27-22E1-C143-A50C-5FC81AE13C86.root'
 	'/store/data/Run2018B/MuonEG/MINIAOD/UL2018_MiniAODv2_GT36-v1/40000/0196B339-F1B2-6A43-A3A2-00E59A673AED.root'
        #'/store/user/wangjian/mpmp_SFGen/RunIISummer20UL18MiniAODv2_v3/240408_075851/0000/aammmm_RunIISummer20UL18MiniAODv2_tm_1.root'

        #'/store/mc/RunIISummer20UL18MiniAODv2/WWTo2L2Nu_TuneCP5_DoubleScattering_13TeV-pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v2/50000/0C401F27-2F8F-5D41-B6E2-4FB7FFAD6E3F.root',
        #'/store/mc/RunIISummer20UL18MiniAODv2/WWTo2L2Nu_TuneCP5_DoubleScattering_13TeV-pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v2/50000/0C5EFFB0-1A20-9647-84C7-13E8E8EF9FD3.root',
        #'/store/mc/RunIISummer20UL18MiniAODv2/WWTo2L2Nu_TuneCP5_DoubleScattering_13TeV-pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v2/50000/0DBA32FF-37A4-5C4C-87E7-55F868048DCD.root',
        #'/store/mc/RunIISummer20UL18MiniAODv2/WWTo2L2Nu_TuneCP5_DoubleScattering_13TeV-pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v2/50000/1124D71A-A516-3D4C-97EE-A1942FF43574.root',
        #'/store/mc/RunIISummer20UL18MiniAODv2/WWTo2L2Nu_TuneCP5_DoubleScattering_13TeV-pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v2/50000/184EC2D0-1B8D-8F48-B7C3-1D309AC4E11D.root',
        #'/store/mc/RunIISummer20UL18MiniAODv2/WWTo2L2Nu_TuneCP5_DoubleScattering_13TeV-pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v2/50000/19D8B24C-CA5A-D248-9F36-9152B9CF8D69.root',
        #'/store/mc/RunIISummer20UL18MiniAODv2/WWTo2L2Nu_TuneCP5_DoubleScattering_13TeV-pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v2/50000/1F5653C3-9AFD-ED45-B388-324FE40594D9.root',
        #'/store/mc/RunIISummer20UL18MiniAODv2/WWTo2L2Nu_TuneCP5_DoubleScattering_13TeV-pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v2/50000/25A4A9ED-0050-AD41-BB27-76ADC4025967.root',
        #'/store/mc/RunIISummer20UL18MiniAODv2/WWTo2L2Nu_TuneCP5_DoubleScattering_13TeV-pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v2/50000/35934CBE-3470-9741-AA43-EECC651DADE7.root',
        #'/store/mc/RunIISummer20UL18MiniAODv2/WWTo2L2Nu_TuneCP5_DoubleScattering_13TeV-pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v2/50000/472F5AEF-456E-9C48-AFCF-40A6A03A80B1.root'

    ),
    duplicateCheckMode = cms.untracked.string('noDuplicateCheck')

)

process.load( "PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff" )
process.load( "PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff" )

from EgammaUser.EgammaPostRecoTools.EgammaPostRecoTools import setupEgammaPostRecoSeq

setupEgammaPostRecoSeq(process,era='2018-UL',
                                     eleIDModules=['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V2_cff',
                                     'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV70_cff',
                                     'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_iso_V2_cff',
                                     'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_noIso_V2_cff'],
                                     phoIDModules=['RecoEgamma.PhotonIdentification.Identification.mvaPhotonID_Fall17_94X_V2_cff',
                                     'RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Fall17_94X_V2_cff']
)  

process.demo = cms.EDAnalyzer("SSEMAnlzr",
    MC = cms.bool(False), #False
    year = cms.int32(2018),
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
    lheInfo = cms.VInputTag(cms.InputTag("externalLHEProducer"), cms.InputTag("source"))
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('tree_ssem.root'))

process.p = cms.Path(process.egammaPostRecoSeq+process.demo)

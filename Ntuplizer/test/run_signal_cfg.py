import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(500) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(100)

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '102X_upgrade2018_realistic_v18')
process.GlobalTag = GlobalTag(process.GlobalTag, '106X_upgrade2018_realistic_v16_L1v1', '')

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(

        #'/store/mc/RunIISummer20UL18MiniAODv2/WpWpJJ_EWK_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v2/2560000/2A06992B-5F8E-D84A-98AE-5AEEF65D4499.root'
        #'/store/data/Run2018A/DoubleMuon/MINIAOD/UL2018_MiniAODv2_GT36-v1/2430000/00267D27-22E1-C143-A50C-5FC81AE13C86.root'
        #'/store/user/wangjian/mpmp_SFGen/RunIISummer20UL18MiniAODv2_v3/240408_075851/0000/aammmm_RunIISummer20UL18MiniAODv2_tm_1.root'
	#'/store/user/wangjian/llscat_POWHEG_trigger/RunIISummer20UL18MiniAODv2_PrivateMC/231207_205550/0000/aammmm_RunIISummer20UL18MiniAODv2_tm_1.root'

	'/store/user/wangjian/llscat_powheg_ptl8/RunIISummer20UL18MiniAODv2_v3/240620_084124/0000/aammmm_RunIISummer20UL18MiniAODv2_tm_1.root',
        '/store/user/wangjian/llscat_powheg_ptl8/RunIISummer20UL18MiniAODv2_v3/240620_084124/0000/aammmm_RunIISummer20UL18MiniAODv2_tm_2.root',
        '/store/user/wangjian/llscat_powheg_ptl8/RunIISummer20UL18MiniAODv2_v3/240620_084124/0000/aammmm_RunIISummer20UL18MiniAODv2_tm_3.root',
        '/store/user/wangjian/llscat_powheg_ptl8/RunIISummer20UL18MiniAODv2_v3/240620_084124/0000/aammmm_RunIISummer20UL18MiniAODv2_tm_4.root',
        '/store/user/wangjian/llscat_powheg_ptl8/RunIISummer20UL18MiniAODv2_v3/240620_084124/0000/aammmm_RunIISummer20UL18MiniAODv2_tm_5.root',
        '/store/user/wangjian/llscat_powheg_ptl8/RunIISummer20UL18MiniAODv2_v3/240620_084124/0000/aammmm_RunIISummer20UL18MiniAODv2_tm_6.root',
        '/store/user/wangjian/llscat_powheg_ptl8/RunIISummer20UL18MiniAODv2_v3/240620_084124/0000/aammmm_RunIISummer20UL18MiniAODv2_tm_7.root',
        '/store/user/wangjian/llscat_powheg_ptl8/RunIISummer20UL18MiniAODv2_v3/240620_084124/0000/aammmm_RunIISummer20UL18MiniAODv2_tm_8.root',

	#'/store/mc/RunIISummer20UL18MiniAODv2/DYJetsToTauTau_TauToMuEle_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v1/230000/00B899C8-3D94-4349-9219-47D2BDDFE4CF.root',

    ),
    duplicateCheckMode = cms.untracked.string('noDuplicateCheck')

)

process.load( "PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff" )
process.load( "PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff" )

#from EgammaUser.EgammaPostRecoTools.EgammaPostRecoTools import setupEgammaPostRecoSeq

#setupEgammaPostRecoSeq(process,era='2018-UL',
#                                     eleIDModules=['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V2_cff',
#                                     'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV70_cff',
#                                     'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_iso_V2_cff',
#                                     'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_noIso_V2_cff'],
#                                     phoIDModules=['RecoEgamma.PhotonIdentification.Identification.mvaPhotonID_Fall17_94X_V2_cff',
#                                     'RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Fall17_94X_V2_cff']
#)  

process.demo = cms.EDAnalyzer("GenAnlzr",
    MC = cms.bool(True), 
    pruned = cms.InputTag("prunedGenParticles"),
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('tree_ssem.root'))

process.p = cms.Path(process.demo)

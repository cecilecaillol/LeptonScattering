import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
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
        '/store/user/wangjian/llscat_powheg_ptl8/RunIISummer20UL18MiniAODv2_v3/240620_084124/0000/aammmm_RunIISummer20UL18MiniAODv2_tm_4.root',
        '/store/user/wangjian/llscat_powheg_ptl8/RunIISummer20UL18MiniAODv2_v3/240620_084124/0000/aammmm_RunIISummer20UL18MiniAODv2_tm_5.root',
        '/store/user/wangjian/llscat_powheg_ptl8/RunIISummer20UL18MiniAODv2_v3/240620_084124/0000/aammmm_RunIISummer20UL18MiniAODv2_tm_6.root',
        '/store/user/wangjian/llscat_powheg_ptl8/RunIISummer20UL18MiniAODv2_v3/240620_084124/0000/aammmm_RunIISummer20UL18MiniAODv2_tm_7.root',
        '/store/user/wangjian/llscat_powheg_ptl8/RunIISummer20UL18MiniAODv2_v3/240620_084124/0000/aammmm_RunIISummer20UL18MiniAODv2_tm_8.root',

	#'/store/mc/RunIISummer20UL18MiniAODv2/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v2/100000/4E295BA9-D9F7-6643-B993-57789E70C0CB.root',
	#'/store/mc/RunIISummer20UL18MiniAODv2/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v1/00000/0FB611DB-DE9A-0E4D-9A91-A1CBFD85AE6B.root'

	#'/store/group/cmst3/group/taug2/PublishedMiniAOD/GGToTauTau_Ctb20_RunIISummer20UL18/crab_GGToTauTau_Ctb20_RunIISummer20UL18_januarysamples/240109_103259/0000/step1_GEN_PUB_321.root'

	#'/store/mc/RunIISummer20UL18MiniAODv2/DYJetsToTauTau_TauToMuEle_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v1/230000/00B899C8-3D94-4349-9219-47D2BDDFE4CF.root',
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

process.finalGenParticles = cms.EDProducer("GenParticlePruner",
    src = cms.InputTag("prunedGenParticles"),
    select = cms.vstring(
	"drop *",
        "keep++ abs(pdgId) == 15 & (pt > 15 ||  isPromptDecayed() )",#  keep full tau decay chain for some taus
	#"drop status==1 & pt < 1", #drop soft stable particle in tau decay
        "keep+ abs(pdgId) == 15 ",  #  keep first gen decay product for all tau
        "+keep pdgId == 22 && status == 1 && (pt > 10 || isPromptFinalState())", # keep gamma above 10 GeV (or all prompt) and its first parent
	"+keep abs(pdgId) == 11 || abs(pdgId) == 13 || abs(pdgId) == 15", #keep leptons, with at most one mother back in the history
	"drop abs(pdgId)= 2212 && abs(pz) > 1000", #drop LHC protons accidentally added by previous keeps
        "keep (400 < abs(pdgId) < 600) || (4000 < abs(pdgId) < 6000)", #keep all B and C hadrons
        "keep abs(pdgId) == 12 || abs(pdgId) == 14 || abs(pdgId) == 16",   # keep neutrinos
	"keep status == 3 || (status > 20 && status < 30)", #keep matrix element summary
        "keep isHardProcess() ||  fromHardProcessDecayed()  || fromHardProcessFinalState() || (statusFlags().fromHardProcess() && statusFlags().isLastCopy())",  #keep event summary based on status flags
	"keep  (status > 70 && status < 80 && pt > 15) ", # keep high pt partons right before hadronization
        "keep abs(pdgId) == 23 || abs(pdgId) == 24 || abs(pdgId) == 25 || abs(pdgId) == 37 ",   # keep VIP(articles)s
        #"keep abs(pdgId) == 310 && abs(eta) < 2.5 && pt > 1 ",                                                     # keep K0
        "keep (1000001 <= abs(pdgId) <= 1000039 ) || ( 2000001 <= abs(pdgId) <= 2000015)", #keep SUSY fiction particles
 		
   )
)

process.electronsMCMatchForTable = cms.EDProducer("MCMatcher",  # cut on deltaR, deltaPt/Pt; pick best by deltaR
    src         = cms.InputTag("slimmedElectrons"),                 # final reco collection
    matched     = cms.InputTag("finalGenParticles"), # final mc-truth particle collection
    mcPdgId     = cms.vint32(11,22),                 # one or more PDG ID (11 = el, 22 = pho); absolute values (see below)
    checkCharge = cms.bool(False),              # True = require RECO and MC objects to have the same charge
    mcStatus    = cms.vint32(1),                # PYTHIA status code (1 = stable, 2 = shower, 3 = hard scattering)
    maxDeltaR   = cms.double(0.3),              # Minimum deltaR for the match
    maxDPtRel   = cms.double(0.5),              # Minimum deltaPt/Pt for the match
    resolveAmbiguities    = cms.bool(True),     # Forbid two RECO objects to match to the same GEN object
    resolveByMatchQuality = cms.bool(True),    # False = just match input in order; True = pick lowest deltaR pair first
)

process.muonsMCMatchForTable = cms.EDProducer("MCMatcher",       # cut on deltaR, deltaPt/Pt; pick best by deltaR
    src         = cms.InputTag("slimmedMuons"),                         # final reco collection
    matched     = cms.InputTag("finalGenParticles"),     # final mc-truth particle collection
    mcPdgId     = cms.vint32(13),               # one or more PDG ID (13 = mu); absolute values (see below)
    checkCharge = cms.bool(False),              # True = require RECO and MC objects to have the same charge
    mcStatus    = cms.vint32(1),                # PYTHIA status code (1 = stable, 2 = shower, 3 = hard scattering)
    maxDeltaR   = cms.double(0.3),              # Minimum deltaR for the match
    maxDPtRel   = cms.double(0.5),              # Minimum deltaPt/Pt for the match
    resolveAmbiguities    = cms.bool(True),     # Forbid two RECO objects to match to the same GEN object
    resolveByMatchQuality = cms.bool(True),    # False = just match input in order; True = pick lowest deltaR pair first
)

process.demo = cms.EDAnalyzer("SSEMAnlzr",
    MC = cms.bool(True), 
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

process.p = cms.Path(process.egammaPostRecoSeq+process.finalGenParticles+process.electronsMCMatchForTable+process.muonsMCMatchForTable+process.demo)

from CRABClient.UserUtilities import config
config = config()

#config.General.requestName = 'MuonEG_2017B'
#config.General.requestName = 'MuonEG_2017C'
#config.General.requestName = 'MuonEG_2017D'
#config.General.requestName = 'MuonEG_2017E'
#config.General.requestName = 'MuonEG_2017F'
#config.General.requestName = 'SingleMuon_2017B'
#config.General.requestName = 'SingleMuon_2017C'
#config.General.requestName = 'SingleMuon_2017D'
config.General.requestName = 'SingleMuon_2017E'
#config.General.requestName = 'SingleMuon_2017F'
#config.General.requestName = 'DoubleMuon_2017B'
#config.General.requestName = 'DoubleMuon_2017C'
#config.General.requestName = 'DoubleMuon_2017D'
#config.General.requestName = 'DoubleMuon_2017E'
#config.General.requestName = 'DoubleMuon_2017F'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'run_ssem_2017data_cfg.py'
config.JobType.allowUndistributedCMSSW = True

#config.Data.inputDataset = "/MuonEG/Run2017B-UL2017_MiniAODv2-v1/MINIAOD"
#config.Data.inputDataset = "/MuonEG/Run2017C-UL2017_MiniAODv2-v1/MINIAOD"
#config.Data.inputDataset = "/MuonEG/Run2017D-UL2017_MiniAODv2-v1/MINIAOD"
#config.Data.inputDataset = "/MuonEG/Run2017E-UL2017_MiniAODv2-v1/MINIAOD"
#config.Data.inputDataset = "/MuonEG/Run2017F-UL2017_MiniAODv2-v1/MINIAOD"
#config.Data.inputDataset = "/SingleMuon/Run2017B-UL2017_MiniAODv2_GT36-v2/MINIAOD"
#config.Data.inputDataset = "/SingleMuon/Run2017C-UL2017_MiniAODv2_GT36-v2/MINIAOD"
#config.Data.inputDataset = "/SingleMuon/Run2017D-UL2017_MiniAODv2_GT36-v2/MINIAOD"
config.Data.inputDataset = "/SingleMuon/Run2017E-UL2017_MiniAODv2_GT36-v2/MINIAOD"
#config.Data.inputDataset = "/SingleMuon/Run2017F-UL2017_MiniAODv2_GT36-v2/MINIAOD"
#config.Data.inputDataset = "/DoubleMuon/Run2017B-UL2017_MiniAODv2-v1/MINIAOD"
#config.Data.inputDataset = "/DoubleMuon/Run2017C-UL2017_MiniAODv2-v1/MINIAOD"
#config.Data.inputDataset = "/DoubleMuon/Run2017D-UL2017_MiniAODv2-v1/MINIAOD"
#config.Data.inputDataset = "/DoubleMuon/Run2017E-UL2017_MiniAODv2-v2/MINIAOD"
#config.Data.inputDataset = "/DoubleMuon/Run2017F-UL2017_MiniAODv2-v1/MINIAOD"

config.Data.inputDBS = "global"
config.Data.splitting = 'Automatic'
config.Data.lumiMask = 'https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions17/13TeV/Legacy_2017/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt'
config.Data.outLFNDirBase = '/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/'
config.Data.publication = False
config.Site.storageSite = 'T2_CH_CERN'

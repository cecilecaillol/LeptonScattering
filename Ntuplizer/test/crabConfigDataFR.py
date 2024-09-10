from CRABClient.UserUtilities import config
config = config()

#config.General.requestName = 'SingleMuon_2018A'
#config.General.requestName = 'SingleMuon_2018B'
#config.General.requestName = 'SingleMuon_2018C'
#config.General.requestName = 'SingleMuon_2018D'
#config.General.requestName = 'DoubleMuon_2018A'
#config.General.requestName = 'DoubleMuon_2018B'
#config.General.requestName = 'DoubleMuon_2018C'
config.General.requestName = 'DoubleMuon_2018D'
config.General.workArea = 'crab_projectsFR'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'run_fr_2018data_cfg.py'
config.JobType.allowUndistributedCMSSW = True

#config.Data.inputDataset = "/SingleMuon/Run2018A-UL2018_MiniAODv2_GT36-v2/MINIAOD"
#config.Data.inputDataset = "/SingleMuon/Run2018B-UL2018_MiniAODv2_GT36-v2/MINIAOD"
#config.Data.inputDataset = "/SingleMuon/Run2018C-UL2018_MiniAODv2_GT36-v3/MINIAOD"
#config.Data.inputDataset = "/SingleMuon/Run2018D-UL2018_MiniAODv2_GT36-v2/MINIAOD"
#config.Data.inputDataset = "/DoubleMuon/Run2018A-UL2018_MiniAODv2_GT36-v1/MINIAOD"
#config.Data.inputDataset = "/DoubleMuon/Run2018B-UL2018_MiniAODv2_GT36-v1/MINIAOD"
#config.Data.inputDataset = "/DoubleMuon/Run2018C-UL2018_MiniAODv2_GT36-v1/MINIAOD"
config.Data.inputDataset = "/DoubleMuon/Run2018D-UL2018_MiniAODv2_GT36-v1/MINIAOD"
config.Data.inputDBS = "global"
config.Data.splitting = 'Automatic'
config.Data.unitsPerJob = 500
config.Data.lumiMask = 'https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions18/13TeV/Legacy_2018/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt'
config.Data.outLFNDirBase = '/store/group/cmst3/user/ccaillol/LeptonScattering/FR/'
config.Data.publication = False
config.Site.storageSite = 'T2_CH_CERN'

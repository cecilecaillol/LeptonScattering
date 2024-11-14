from CRABClient.UserUtilities import config
config = config()

#config.General.requestName = "SingleElectron_2017B"
#config.General.requestName = "SingleElectron_2017C"
#config.General.requestName = "SingleElectron_2017D"
#config.General.requestName = "SingleElectron_2017E"
config.General.requestName = "SingleElectron_2017F"

config.General.workArea = 'crab_projectsChargeMisid'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'run_chargemisid_2017data_cfg.py'
config.JobType.allowUndistributedCMSSW = True

#config.Data.inputDataset = "/SingleElectron/Run2017B-UL2017_MiniAODv2-v1/MINIAOD"
#config.Data.inputDataset = "/SingleElectron/Run2017C-UL2017_MiniAODv2-v1/MINIAOD"
#config.Data.inputDataset = "/SingleElectron/Run2017D-UL2017_MiniAODv2-v1/MINIAOD"
#config.Data.inputDataset = "/SingleElectron/Run2017E-UL2017_MiniAODv2-v1/MINIAOD"
config.Data.inputDataset = "/SingleElectron/Run2017F-UL2017_MiniAODv2-v1/MINIAOD"

config.Data.inputDBS = "global"
config.Data.splitting = 'Automatic'
config.Data.lumiMask = 'https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions17/13TeV/Legacy_2017/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt'
config.Data.outLFNDirBase = '/store/group/cmst3/user/ccaillol/LeptonScattering/ChargeMisid2017/'
config.Data.publication = False
config.Site.storageSite = 'T2_CH_CERN'

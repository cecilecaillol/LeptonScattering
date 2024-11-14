from CRABClient.UserUtilities import config
config = config()

#config.General.requestName = 'SingleElectron_2016postF'
#config.General.requestName = 'SingleElectron_2016postG'
config.General.requestName = 'SingleElectron_2016postH'
config.General.workArea = 'crab_projectsChargeMisid'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'run_chargemisid_2016postdata_cfg.py'
config.JobType.allowUndistributedCMSSW = True

#config.Data.inputDataset = "/SingleElectron/Run2016F-UL2016_MiniAODv2-v2/MINIAOD"
#config.Data.inputDataset = "/SingleElectron/Run2016G-UL2016_MiniAODv2-v2/MINIAOD"
config.Data.inputDataset = "/SingleElectron/Run2016H-UL2016_MiniAODv2-v2/MINIAOD"

config.Data.inputDBS = "global"
config.Data.splitting = 'Automatic'
config.Data.lumiMask = 'https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions16/13TeV/Legacy_2016/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt'
config.Data.outLFNDirBase = '/store/group/cmst3/user/ccaillol/LeptonScattering/ChargeMisid2016post/'
config.Data.publication = False
config.Site.storageSite = 'T2_CH_CERN'

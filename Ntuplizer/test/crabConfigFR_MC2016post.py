from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'ZZ4L_2016post'
#config.General.requestName = 'WZ3LNu_2016post'
config.General.workArea = 'crab_projectsFR'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'run_fr_2016postmc_cfg.py'
config.JobType.allowUndistributedCMSSW = True

config.Data.inputDataset = '/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM'
#config.Data.inputDataset = '/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM'

config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.splitting = 'Automatic'
config.Data.outLFNDirBase = '/store/group/cmst3/user/ccaillol/LeptonScattering/FR2016post/'
config.Data.publication = False
config.Site.storageSite = 'T2_CH_CERN'

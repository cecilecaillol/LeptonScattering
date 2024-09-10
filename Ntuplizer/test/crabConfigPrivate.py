from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'GGTT_Ctb20_2018'
#config.General.requestName = 'GGWW_2018'
#config.General.requestName = 'GGMM_2018'
#config.General.requestName = 'GGEE_2018'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'run_ssem_2018mc_cfg.py'
config.JobType.allowUndistributedCMSSW = True


config.Data.inputDataset = "/GGToTauTau_Ctb20_RunIISummer20UL18/cmst3-crab_GGToTauTau_Ctb20_RunIISummer20UL18_januarysamples-c15273f0b6812ff053a850f456209388/USER"
#config.Data.inputDataset = "/GGToWW_RunIISummer20UL18/cmst3-crab_GGToWW_RunIISummer20UL18_januarysamples-c15273f0b6812ff053a850f456209388/USER"
#config.Data.inputDataset = "/GGToMuMu_RunIISummer20UL18/cmst3-crab_GGToMuMu_RunIISummer20UL18_januarysamples-c15273f0b6812ff053a850f456209388/USER"
#config.Data.inputDataset = "/GGToElEl_RunIISummer20UL18/cmst3-crab_GGToElEl_RunIISummer20UL18_januarysamples-c15273f0b6812ff053a850f456209388/USER"
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'Automatic'
config.Data.outLFNDirBase = '/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/'
config.Data.publication = False
config.Site.storageSite = 'T2_CH_CERN'

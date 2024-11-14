from CRABClient.UserUtilities import config
config = config()

#config.General.requestName = 'MuonEG_2016preBv1'
#config.General.requestName = 'MuonEG_2016preBv2'
#config.General.requestName = 'MuonEG_2016preC'
#config.General.requestName = 'MuonEG_2016preD'
#config.General.requestName = 'MuonEG_2016preE'
#config.General.requestName = 'MuonEG_2016preF'
#config.General.requestName = 'SingleMuon_2016preBv1'
#config.General.requestName = 'SingleMuon_2016preBv2'
#config.General.requestName = 'SingleMuon_2016preC'
#config.General.requestName = 'SingleMuon_2016preD'
#config.General.requestName = 'SingleMuon_2016preE'
#config.General.requestName = 'SingleMuon_2016preF'
#config.General.requestName = 'DoubleMuon_2016preBv1'
#config.General.requestName = 'DoubleMuon_2016preBv2'
#config.General.requestName = 'DoubleMuon_2016preC'
#config.General.requestName = 'DoubleMuon_2016preD'
#config.General.requestName = 'DoubleMuon_2016preE'
config.General.requestName = 'DoubleMuon_2016preF'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'run_ssem_2016predata_cfg.py'
config.JobType.allowUndistributedCMSSW = True

#config.Data.inputDataset = "/MuonEG/Run2016B-ver1_HIPM_UL2016_MiniAODv2-v2/MINIAOD"
#config.Data.inputDataset = "/MuonEG/Run2016B-ver2_HIPM_UL2016_MiniAODv2-v2/MINIAOD"
#config.Data.inputDataset = "/MuonEG/Run2016C-HIPM_UL2016_MiniAODv2-v2/MINIAOD"
#config.Data.inputDataset = "/MuonEG/Run2016D-HIPM_UL2016_MiniAODv2-v2/MINIAOD"
#config.Data.inputDataset = "/MuonEG/Run2016E-HIPM_UL2016_MiniAODv2-v2/MINIAOD"
#config.Data.inputDataset = "/MuonEG/Run2016F-HIPM_UL2016_MiniAODv2-v2/MINIAOD"
#config.Data.inputDataset = "/SingleMuon/Run2016B-ver1_HIPM_UL2016_MiniAODv2-v2/MINIAOD"
#config.Data.inputDataset = "/SingleMuon/Run2016B-ver2_HIPM_UL2016_MiniAODv2-v2/MINIAOD"
#config.Data.inputDataset = "/SingleMuon/Run2016C-HIPM_UL2016_MiniAODv2-v2/MINIAOD"
#config.Data.inputDataset = "/SingleMuon/Run2016D-HIPM_UL2016_MiniAODv2-v2/MINIAOD"
#config.Data.inputDataset = "/SingleMuon/Run2016E-HIPM_UL2016_MiniAODv2-v2/MINIAOD"
#config.Data.inputDataset = "/SingleMuon/Run2016F-HIPM_UL2016_MiniAODv2-v2/MINIAOD"
#config.Data.inputDataset = "/DoubleMuon/Run2016B-ver1_HIPM_UL2016_MiniAODv2-v1/MINIAOD"
#config.Data.inputDataset = "/DoubleMuon/Run2016B-ver2_HIPM_UL2016_MiniAODv2-v1/MINIAOD"
#config.Data.inputDataset = "/DoubleMuon/Run2016C-HIPM_UL2016_MiniAODv2-v1/MINIAOD"
#config.Data.inputDataset = "/DoubleMuon/Run2016D-HIPM_UL2016_MiniAODv2-v1/MINIAOD"
#config.Data.inputDataset = "/DoubleMuon/Run2016E-HIPM_UL2016_MiniAODv2-v1/MINIAOD"
config.Data.inputDataset = "/DoubleMuon/Run2016F-HIPM_UL2016_MiniAODv2-v1/MINIAOD"

config.Data.inputDBS = "global"
config.Data.splitting = 'Automatic'
config.Data.lumiMask = 'https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions16/13TeV/Legacy_2016/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt'
config.Data.outLFNDirBase = '/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/'
config.Data.publication = False
config.Site.storageSite = 'T2_CH_CERN'

from CRABClient.UserUtilities import config
config = config()

#config.General.requestName = 'WZ3LNu_2018'
#config.General.requestName = 'ZZ4L_2018'
#config.General.requestName = 'WWDPS_2018'
#config.General.requestName = 'DY_2018'
#config.General.requestName = 'DYemu_2018'
#config.General.requestName = 'ZG_2018'
config.General.requestName = 'ZGv2_2018'
#config.General.requestName = 'WG_2018'
#config.General.requestName = 'TTW_2018'
#config.General.requestName = 'TTZ_2018'
#config.General.requestName = 'TG_2018'
#config.General.requestName = 'WWW_2018'
#config.General.requestName = 'WWG_2018'
#config.General.requestName = 'W_2018'
#config.General.requestName = 'W1_2018'
#config.General.requestName = 'W2_2018'
#config.General.requestName = 'TTG_2018'

config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'run_ssem_2018mc_cfg.py'
config.JobType.allowUndistributedCMSSW = True

#config.Data.inputDataset = '/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM'
#config.Data.inputDataset = '/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM'
#config.Data.inputDataset = '/WWTo2L2Nu_TuneCP5_DoubleScattering_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM'
#config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM'
#config.Data.inputDataset = '/DYJetsToTauTau_TauToMuEle_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM'
#config.Data.inputDataset = '/ZGToLLG_01J_5f_lowMLL_lowGPt_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM'
config.Data.inputDataset = '/ZGToLLG_01J_5f_lowMLL_lowGPt_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1_ext1-v2/MINIAODSIM'
#config.Data.inputDataset = '/WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM'
#config.Data.inputDataset = '/ttWJets_TuneCP5_13TeV_madgraphMLM_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM'
#config.Data.inputDataset = '/ttZJets_TuneCP5_13TeV_madgraphMLM_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM'
#config.Data.inputDataset = '/TGJets_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM'
#config.Data.inputDataset = '/WWW_Inclusive_dim6_LO_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM'
#config.Data.inputDataset = '/WWG_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM'
#config.Data.inputDataset = '/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM'
#config.Data.inputDataset = '/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM'
#config.Data.inputDataset = '/W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM'
#config.Data.inputDataset = '/TTGamma_Dilept_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM'

config.Data.inputDBS = 'global'
config.Data.splitting = 'Automatic'
config.Data.outLFNDirBase = '/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/'
config.Data.publication = False
config.Site.storageSite = 'T2_CH_CERN'

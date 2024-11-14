./Make.sh FinalSelection_3lep.cc
./FinalSelection_3lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/MuonEG.root output_3lep_2018/MuonEG.root MuonEG data_obs
./FinalSelection_3lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/SingleMuon.root output_3lep_2018/SingleMuon.root SingleMuon data_obs
./FinalSelection_3lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/DoubleMuon.root output_3lep_2018/DoubleMuon.root DoubleMuon data_obs
hadd -f output_3lep_2018/Data.root output_3lep_2018/MuonEG.root output_3lep_2018/SingleMuon.root output_3lep_2018/DoubleMuon.root
./FinalSelection_3lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/ZZ4L.root output_3lep_2018/ZZ4L.root ZZ4L ZZ4L
./FinalSelection_3lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/WZ3LNu.root output_3lep_2018/WZ3LNu.root WZ3LNu WZ3LNu
./FinalSelection_3lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/TTW.root output_3lep_2018/TTW.root TTW TTV
./FinalSelection_3lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/TTZ.root output_3lep_2018/TTZ.root TTZ TTV
./FinalSelection_3lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/WWW.root output_3lep_2018/WWW.root WWW VVV
./FinalSelection_3lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/ZG.root output_3lep_2018/ZG.root ZG VG
#./FinalSelection_3lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/WG.root output_3lep_2018/WG.root WG VG
#./FinalSelection_3lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/TG.root output_3lep_2018/TG.root TG VG
./FinalSelection_3lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/TTG.root output_3lep_2018/TTG.root TTG VG
./FinalSelection_3lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/WWG.root output_3lep_2018/WWG.root WWG VG
hadd -f output_3lep_2018/XG.root output_3lep_2018/ZG.root output_3lep_2018/TTG.root output_3lep_2018/WWG.root
./FinalSelection_3lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/signal_ptl8.root output_3lep_2018/signal_ptl8.root llscat_ptl8 llscat
python Create_fake_3lep.py --year=2018
hadd -f datacard_3lep_2018.root output_3lep_2018/nonprompt.root output_3lep_2018/Data.root output_3lep_2018/ZZ4L.root output_3lep_2018/WZ3LNu.root output_3lep_2018/XG.root output_3lep_2018/TTW.root output_3lep_2018/TTZ.root output_3lep_2018/WWW.root output_3lep_2018/signal_ptl8.root

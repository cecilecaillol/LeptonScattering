./Make.sh FinalSelection_3lep.cc
./FinalSelection_3lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/MuonEG.root output_3lep_2017/MuonEG.root MuonEG data_obs
./FinalSelection_3lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/SingleMuon.root output_3lep_2017/SingleMuon.root SingleMuon data_obs
./FinalSelection_3lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/DoubleMuon.root output_3lep_2017/DoubleMuon.root DoubleMuon data_obs
hadd -f output_3lep_2017/Data.root output_3lep_2017/MuonEG.root output_3lep_2017/SingleMuon.root output_3lep_2017/DoubleMuon.root
./FinalSelection_3lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/ZZ4L.root output_3lep_2017/ZZ4L.root ZZ4L ZZ4L
./FinalSelection_3lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/WZ3LNu.root output_3lep_2017/WZ3LNu.root WZ3LNu WZ3LNu
#./FinalSelection_3lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/WW2L2Nu.root output_3lep_2017/WW2L2Nu.root WW2L2Nu WW2LNu
#./FinalSelection_3lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/WZmin0p1.root output_3lep_2017/WZmin0p1.root WZmin0p1 WZ3LNu
./FinalSelection_3lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/TTW.root output_3lep_2017/TTW.root TTW TTV
./FinalSelection_3lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/TTZ.root output_3lep_2017/TTZ.root TTZ TTV
./FinalSelection_3lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/WWW.root output_3lep_2017/WWW.root WWW VVV
./FinalSelection_3lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/ZG.root output_3lep_2017/ZG.root ZG VG
./FinalSelection_3lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/WG.root output_3lep_2017/WG.root WG VG
./FinalSelection_3lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/TG.root output_3lep_2017/TG.root TG VG
./FinalSelection_3lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/WWG.root output_3lep_2017/WWG.root WWG VG
./FinalSelection_3lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/DYemu.root output_3lep_2017/DYemu.root DYemu DY
./FinalSelection_3lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/DY.root output_3lep_2017/DY.root DY DY
python Relax_shape_3lep.py --year=2017 --process=DY
python Relax_shape_3lep.py --year=2017 --process=DYemu
#./FinalSelection_3lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/signal_ptl8.root output_3lep_2017/signal_ptl8.root llscat_ptl8 llscat
python Create_fake_3lep.py --year=2017
hadd -f datacard_3lep_2017.root output_3lep_2017/DYemu_relaxed.root output_3lep_2017/DY_relaxed.root output_3lep_2017/nonprompt.root output_3lep_2017/Data.root output_3lep_2017/ZZ4L.root output_3lep_2017/WZ3LNu.root output_3lep_2017/ZG.root output_3lep_2017/WG.root output_3lep_2017/TG.root output_3lep_2017/WWG.root output_3lep_2017/TTW.root output_3lep_2017/TTZ.root output_3lep_2017/WWW.root #output_3lep_2017/DYemu.root output_3lep_2017/DY.root #output_3lep_2017/signal_ptl8.root 

./Make.sh FinalSelection_3lep.cc
./FinalSelection_3lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/MuonEG.root output_3lep_2016pre/MuonEG.root MuonEG data_obs
./FinalSelection_3lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/SingleMuon.root output_3lep_2016pre/SingleMuon.root SingleMuon data_obs
./FinalSelection_3lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/DoubleMuon.root output_3lep_2016pre/DoubleMuon.root DoubleMuon data_obs
hadd -f output_3lep_2016pre/Data.root output_3lep_2016pre/MuonEG.root output_3lep_2016pre/SingleMuon.root output_3lep_2016pre/DoubleMuon.root
./FinalSelection_3lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/ZZ4L.root output_3lep_2016pre/ZZ4L.root ZZ4L ZZ4L
./FinalSelection_3lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/WZ3LNu.root output_3lep_2016pre/WZ3LNu.root WZ3LNu WZ3LNu
#./FinalSelection_3lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/WW2L2Nu.root output_3lep_2016pre/WW2L2Nu.root WW2L2Nu WW2LNu
#./FinalSelection_3lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/WZmin0p1.root output_3lep_2016pre/WZmin0p1.root WZmin0p1 WZ3LNu
./FinalSelection_3lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/TTW.root output_3lep_2016pre/TTW.root TTW TTV
./FinalSelection_3lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/TTZ.root output_3lep_2016pre/TTZ.root TTZ TTV
./FinalSelection_3lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/WWW.root output_3lep_2016pre/WWW.root WWW VVV
./FinalSelection_3lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/ZG.root output_3lep_2016pre/ZG.root ZG VG
./FinalSelection_3lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/WG.root output_3lep_2016pre/WG.root WG VG
./FinalSelection_3lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/TG.root output_3lep_2016pre/TG.root TG VG
./FinalSelection_3lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/WWG.root output_3lep_2016pre/WWG.root WWG VG
./FinalSelection_3lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/DYemu.root output_3lep_2016pre/DYemu.root DYemu DY
./FinalSelection_3lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/DY.root output_3lep_2016pre/DY.root DY DY
python Relax_shape_3lep.py --year=2016pre --process=DY
python Relax_shape_3lep.py --year=2016pre --process=DYemu
#./FinalSelection_3lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/signal_ptl8.root output_3lep_2016pre/signal_ptl8.root llscat_ptl8 llscat
python Create_fake_3lep.py --year=2016pre
hadd -f datacard_3lep_2016pre.root output_3lep_2016pre/DYemu_relaxed.root output_3lep_2016pre/DY_relaxed.root output_3lep_2016pre/nonprompt.root output_3lep_2016pre/Data.root output_3lep_2016pre/ZZ4L.root output_3lep_2016pre/WZ3LNu.root output_3lep_2016pre/ZG.root output_3lep_2016pre/WG.root output_3lep_2016pre/TG.root output_3lep_2016pre/WWG.root output_3lep_2016pre/TTW.root output_3lep_2016pre/TTZ.root output_3lep_2016pre/WWW.root #output_3lep_2016pre/DYemu.root output_3lep_2016pre/DY.root #output_3lep_2016pre/signal_ptl8.root 

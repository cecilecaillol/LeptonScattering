./Make.sh FinalSelection_2lep.cc
./FinalSelection_2lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/MuonEG.root output_2lep_2018/MuonEG.root MuonEG data_obs
./FinalSelection_2lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/SingleMuon.root output_2lep_2018/SingleMuon.root SingleMuon data_obs
hadd -f output_2lep_2018/Data.root output_2lep_2018/MuonEG.root output_2lep_2018/SingleMuon.root 
./FinalSelection_2lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/ZZ4L.root output_2lep_2018/ZZ4L.root ZZ4L ZZ4L
./FinalSelection_2lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/WZ3LNu.root output_2lep_2018/WZ3LNu.root WZ3LNu WZ3LNu
#./FinalSelection_2lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/WZmin0p1.root output_2lep_2018/WZmin0p1.root WZmin0p1 WZ3LNu
./FinalSelection_2lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/TTW.root output_2lep_2018/TTW.root TTW TTV
./FinalSelection_2lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/TTZ.root output_2lep_2018/TTZ.root TTZ TTV
./FinalSelection_2lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/WWW.root output_2lep_2018/WWW.root WWW VVV
./FinalSelection_2lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/ZG.root output_2lep_2018/ZG.root ZG VG
./FinalSelection_2lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/WG.root output_2lep_2018/WG.root WG VG
./FinalSelection_2lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/TG.root output_2lep_2018/TG.root TG VG
./FinalSelection_2lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/DYemu.root output_2lep_2018/DYemu.root DYemu DY
./FinalSelection_2lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/DY.root output_2lep_2018/DY.root DY DY
python Relax_shape_2lep.py --year=2018 --process=DY
python Relax_shape_2lep.py --year=2018 --process=DYemu
./FinalSelection_2lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/WWDPS.root output_2lep_2018/WWDPS.root WWDPS WWDPS
./FinalSelection_2lep.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/signal_ptl8.root output_2lep_2018/signal_ptl8.root llscat_ptl8 llscat
python Create_fake_2lep.py --year=2018
hadd -f datacard_2lep_2018.root output_2lep_2018/DYemu_relaxed.root output_2lep_2018/DY_relaxed.root output_2lep_2018/nonprompt.root output_2lep_2018/Data.root output_2lep_2018/ZZ4L.root output_2lep_2018/WZ3LNu.root output_2lep_2018/ZG.root output_2lep_2018/WG.root output_2lep_2018/TG.root output_2lep_2018/TTW.root output_2lep_2018/TTZ.root output_2lep_2018/WWW.root output_2lep_2018/WWDPS.root output_2lep_2018/signal_ptl8.root 

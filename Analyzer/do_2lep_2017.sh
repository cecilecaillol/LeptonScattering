./Make.sh FinalSelection_2lep.cc
./FinalSelection_2lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/MuonEG.root output_2lep_2017/MuonEG.root MuonEG data_obs
./FinalSelection_2lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/SingleMuon.root output_2lep_2017/SingleMuon.root SingleMuon data_obs
hadd -f output_2lep_2017/Data.root output_2lep_2017/MuonEG.root output_2lep_2017/SingleMuon.root 
./FinalSelection_2lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/ZZ4L.root output_2lep_2017/ZZ4L.root ZZ4L ZZ4L
./FinalSelection_2lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/WZ3LNu.root output_2lep_2017/WZ3LNu.root WZ3LNu WZ3LNu
./FinalSelection_2lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/TTW.root output_2lep_2017/TTW.root TTW TTV
./FinalSelection_2lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/TTZ.root output_2lep_2017/TTZ.root TTZ TTV
./FinalSelection_2lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/WWW.root output_2lep_2017/WWW.root WWW VVV
./FinalSelection_2lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/ZG.root output_2lep_2017/ZG.root ZG VG
./FinalSelection_2lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/WG.root output_2lep_2017/WG.root WG VG
./FinalSelection_2lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/TG.root output_2lep_2017/TG.root TG VG
./FinalSelection_2lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/DYemu.root output_2lep_2017/DYemu.root DYemu DY
./FinalSelection_2lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/DY.root output_2lep_2017/DY.root DY DY
python Relax_shape_2lep.py --year=2017 --process=DY
python Relax_shape_2lep.py --year=2017 --process=DYemu
./FinalSelection_2lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/WWDPS.root output_2lep_2017/WWDPS.root WWDPS WWDPS
#./FinalSelection_2lep.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2017/signal_ptl8.root output_2lep_2017/signal_ptl8.root llscat_ptl8 llscat
python Create_fake_2lep.py --year=2017
hadd -f datacard_2lep_2017.root output_2lep_2017/DYemu_relaxed.root output_2lep_2017/DY_relaxed.root output_2lep_2017/nonprompt.root output_2lep_2017/Data.root output_2lep_2017/ZZ4L.root output_2lep_2017/WZ3LNu.root output_2lep_2017/ZG.root output_2lep_2017/WG.root output_2lep_2017/TG.root output_2lep_2017/TTW.root output_2lep_2017/TTZ.root output_2lep_2017/WWW.root output_2lep_2017/WWDPS.root #output_2lep_2017/signal_ptl8.root 

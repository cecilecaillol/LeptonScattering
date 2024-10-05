./Make.sh FinalSelection_2lep.cc
./FinalSelection_2lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/MuonEG.root output_2lep_2016pre/MuonEG.root MuonEG data_obs
./FinalSelection_2lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/SingleMuon.root output_2lep_2016pre/SingleMuon.root SingleMuon data_obs
hadd -f output_2lep_2016pre/Data.root output_2lep_2016pre/MuonEG.root output_2lep_2016pre/SingleMuon.root 
./FinalSelection_2lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/ZZ4L.root output_2lep_2016pre/ZZ4L.root ZZ4L ZZ4L
./FinalSelection_2lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/WZ3LNu.root output_2lep_2016pre/WZ3LNu.root WZ3LNu WZ3LNu
./FinalSelection_2lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/TTW.root output_2lep_2016pre/TTW.root TTW TTV
./FinalSelection_2lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/TTZ.root output_2lep_2016pre/TTZ.root TTZ TTV
./FinalSelection_2lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/WWW.root output_2lep_2016pre/WWW.root WWW VVV
./FinalSelection_2lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/ZG.root output_2lep_2016pre/ZG.root ZG VG
./FinalSelection_2lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/WG.root output_2lep_2016pre/WG.root WG VG
./FinalSelection_2lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/TG.root output_2lep_2016pre/TG.root TG VG
./FinalSelection_2lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/DYemu.root output_2lep_2016pre/DYemu.root DYemu DY
./FinalSelection_2lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/DY.root output_2lep_2016pre/DY.root DY DY
python Relax_shape_2lep.py --year=2016pre --process=DY
python Relax_shape_2lep.py --year=2016pre --process=DYemu
./FinalSelection_2lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/WWDPS.root output_2lep_2016pre/WWDPS.root WWDPS WWDPS
#./FinalSelection_2lep.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016pre/signal_ptl8.root output_2lep_2016pre/signal_ptl8.root llscat_ptl8 llscat
python Create_fake_2lep.py --year=2016pre
hadd -f datacard_2lep_2016pre.root output_2lep_2016pre/DYemu_relaxed.root output_2lep_2016pre/DY_relaxed.root output_2lep_2016pre/nonprompt.root output_2lep_2016pre/Data.root output_2lep_2016pre/ZZ4L.root output_2lep_2016pre/WZ3LNu.root output_2lep_2016pre/ZG.root output_2lep_2016pre/WG.root output_2lep_2016pre/TG.root output_2lep_2016pre/TTW.root output_2lep_2016pre/TTZ.root output_2lep_2016pre/WWW.root output_2lep_2016pre/WWDPS.root #output_2lep_2016pre/signal_ptl8.root 

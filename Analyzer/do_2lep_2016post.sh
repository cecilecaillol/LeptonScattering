./Make.sh FinalSelection_2lep.cc
./FinalSelection_2lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/MuonEG.root output_2lep_2016post/MuonEG.root MuonEG data_obs
./FinalSelection_2lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/SingleMuon.root output_2lep_2016post/SingleMuon.root SingleMuon data_obs
hadd -f output_2lep_2016post/Data.root output_2lep_2016post/MuonEG.root output_2lep_2016post/SingleMuon.root 
./FinalSelection_2lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/ZZ4L.root output_2lep_2016post/ZZ4L.root ZZ4L ZZ4L
./FinalSelection_2lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/WZ3LNu.root output_2lep_2016post/WZ3LNu.root WZ3LNu WZ3LNu
./FinalSelection_2lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/TTW.root output_2lep_2016post/TTW.root TTW TTV
./FinalSelection_2lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/TTZ.root output_2lep_2016post/TTZ.root TTZ TTV
./FinalSelection_2lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/WWW.root output_2lep_2016post/WWW.root WWW VVV
./FinalSelection_2lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/ZG.root output_2lep_2016post/ZG.root ZG VG
./FinalSelection_2lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/WG.root output_2lep_2016post/WG.root WG VG
./FinalSelection_2lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/TG.root output_2lep_2016post/TG.root TG VG
./FinalSelection_2lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/DYemu.root output_2lep_2016post/DYemu.root DYemu DY
./FinalSelection_2lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/DY.root output_2lep_2016post/DY.root DY DY
python Relax_shape_2lep.py --year=2016post --process=DY
python Relax_shape_2lep.py --year=2016post --process=DYemu
./FinalSelection_2lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/WWDPS.root output_2lep_2016post/WWDPS.root WWDPS WWDPS
#./FinalSelection_2lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/signal_ptl8.root output_2lep_2016post/signal_ptl8.root llscat_ptl8 llscat
python Create_fake_2lep.py --year=2016post
hadd -f datacard_2lep_2016post.root output_2lep_2016post/DYemu_relaxed.root output_2lep_2016post/DY_relaxed.root output_2lep_2016post/nonprompt.root output_2lep_2016post/Data.root output_2lep_2016post/ZZ4L.root output_2lep_2016post/WZ3LNu.root output_2lep_2016post/ZG.root output_2lep_2016post/WG.root output_2lep_2016post/TG.root output_2lep_2016post/TTW.root output_2lep_2016post/TTZ.root output_2lep_2016post/WWW.root output_2lep_2016post/WWDPS.root #output_2lep_2016post/signal_ptl8.root 

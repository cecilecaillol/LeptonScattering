./Make.sh FinalSelection_3lep.cc
./FinalSelection_3lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/MuonEG.root output_3lep_2016post/MuonEG.root MuonEG data_obs
./FinalSelection_3lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/SingleMuon.root output_3lep_2016post/SingleMuon.root SingleMuon data_obs
./FinalSelection_3lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/DoubleMuon.root output_3lep_2016post/DoubleMuon.root DoubleMuon data_obs
hadd -f output_3lep_2016post/Data.root output_3lep_2016post/MuonEG.root output_3lep_2016post/SingleMuon.root output_3lep_2016post/DoubleMuon.root
./FinalSelection_3lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/ZZ4L.root output_3lep_2016post/ZZ4L.root ZZ4L ZZ4L
./FinalSelection_3lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/WZ3LNu.root output_3lep_2016post/WZ3LNu.root WZ3LNu WZ3LNu
#./FinalSelection_3lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/WW2L2Nu.root output_3lep_2016post/WW2L2Nu.root WW2L2Nu WW2LNu
#./FinalSelection_3lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/WZmin0p1.root output_3lep_2016post/WZmin0p1.root WZmin0p1 WZ3LNu
./FinalSelection_3lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/TTW.root output_3lep_2016post/TTW.root TTW TTV
./FinalSelection_3lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/TTZ.root output_3lep_2016post/TTZ.root TTZ TTV
./FinalSelection_3lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/WWW.root output_3lep_2016post/WWW.root WWW VVV
./FinalSelection_3lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/ZG.root output_3lep_2016post/ZG.root ZG VG
./FinalSelection_3lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/WG.root output_3lep_2016post/WG.root WG VG
./FinalSelection_3lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/TG.root output_3lep_2016post/TG.root TG VG
./FinalSelection_3lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/WWG.root output_3lep_2016post/WWG.root WWG VG
./FinalSelection_3lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/DYemu.root output_3lep_2016post/DYemu.root DYemu DY
./FinalSelection_3lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/DY.root output_3lep_2016post/DY.root DY DY
python Relax_shape_3lep.py --year=2016post --process=DY
python Relax_shape_3lep.py --year=2016post --process=DYemu
#./FinalSelection_3lep.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM2016post/signal_ptl8.root output_3lep_2016post/signal_ptl8.root llscat_ptl8 llscat
python Create_fake_3lep.py --year=2016post
hadd -f datacard_3lep_2016post.root output_3lep_2016post/DYemu_relaxed.root output_3lep_2016post/DY_relaxed.root output_3lep_2016post/nonprompt.root output_3lep_2016post/Data.root output_3lep_2016post/ZZ4L.root output_3lep_2016post/WZ3LNu.root output_3lep_2016post/ZG.root output_3lep_2016post/WG.root output_3lep_2016post/TG.root output_3lep_2016post/WWG.root output_3lep_2016post/TTW.root output_3lep_2016post/TTZ.root output_3lep_2016post/WWW.root #output_3lep_2016post/DYemu.root output_3lep_2016post/DY.root #output_3lep_2016post/signal_ptl8.root 

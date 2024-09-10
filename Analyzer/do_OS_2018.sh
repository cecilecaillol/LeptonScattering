./Make.sh FinalSelection_OS.cc
./FinalSelection_OS.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/MuonEG.root output_OS_2018/MuonEG.root MuonEG data_obs
./FinalSelection_OS.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/SingleMuon.root output_OS_2018/SingleMuon.root SingleMuon data_obs
hadd -f output_OS_2018/Data.root output_OS_2018/MuonEG.root output_OS_2018/SingleMuon.root 
./FinalSelection_OS.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/ZZ4L.root output_OS_2018/ZZ4L.root ZZ4L ZZ4L
./FinalSelection_OS.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/WZ3LNu.root output_OS_2018/WZ3LNu.root WZ3LNu WZ3LNu
#./FinalSelection_OS.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/WW2L2Nu.root output_OS_2018/WW2L2Nu.root WW2L2Nu WW2LNu
#./FinalSelection_OS.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/WZmin0p1.root output_OS_2018/WZmin0p1.root WZmin0p1 WZ3LNu
./FinalSelection_OS.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/TTW.root output_OS_2018/TTW.root TTW TTV
./FinalSelection_OS.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/TTZ.root output_OS_2018/TTZ.root TTZ TTV
./FinalSelection_OS.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/WWW.root output_OS_2018/WWW.root WWW VVV
./FinalSelection_OS.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/ZGlow.root output_OS_2018/ZG.root ZG VG
./FinalSelection_OS.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/DYemu.root output_OS_2018/DYemu.root DYemu DY
./FinalSelection_OS.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/DY.root output_OS_2018/DY.root DY DY
./FinalSelection_OS.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/signal_ptl8.root output_OS_2018/signal_ptl8.root llscat_ptl8 llscat
python Create_fake_OS.py --year=2018
hadd -f datacard_OS_2018.root output_OS_2018/nonprompt.root output_OS_2018/Data.root output_OS_2018/ZZ4L.root output_OS_2018/WZ3LNu.root output_OS_2018/ZG.root output_OS_2018/TTW.root output_OS_2018/TTZ.root output_OS_2018/WWW.root output_OS_2018/DYemu.root output_OS_2018/DY.root output_OS_2018/signal_ptl8.root 

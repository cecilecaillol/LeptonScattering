./Make.sh FinalSelection_emu.cc
./FinalSelection_emu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/MuonEG.root output_emu_2018/MuonEG.root data_obs data_obs
./FinalSelection_emu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/ZZ4L.root output_emu_2018/ZZ4L.root ZZ4L ZZ4L
./FinalSelection_emu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/WZ3LNu.root output_emu_2018/WZ3LNu.root WZ3LNu WZ3LNu
./FinalSelection_emu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/TTTo2L2Nu.root output_emu_2018/TTTo2L2Nu.root TTTo2L2Nu TTTo2L2Nu
./FinalSelection_emu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/VV2L2Nu.root output_emu_2018/VV2L2Nu.root VV2L2Nu VV2L2Nu
./FinalSelection_emu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/DY.root output_emu_2018/DY.root DY DY
./FinalSelection_emu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/DYemu.root output_emu_2018/DYemu.root DYemu DY
hadd -f output_emu_2018/DYall.root output_emu_2018/DY.root output_emu_2018/DYemu.root
./FinalSelection_emu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/TTW.root output_emu_2018/TTW.root TTW TTV
./FinalSelection_emu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/TTZ.root output_emu_2018/TTZ.root TTZ TTV
./FinalSelection_emu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/TTG.root output_emu_2018/TTG.root TTG TT
./FinalSelection_emu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/ZG.root output_emu_2018/ZG.root ZG ZG
./FinalSelection_emu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/WG.root output_emu_2018/WG.root WG WG
./FinalSelection_emu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/WWG.root output_emu_2018/WWG.root WWG WWG
./FinalSelection_emu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/WWW.root output_emu_2018/WWW.root WWW WWW
./FinalSelection_emu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/GGWW.root output_emu_2018/GGWW.root GGWW GGWW
./FinalSelection_emu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/GGTT_Ctb20.root output_emu_2018/GGTT_Ctb20.root GGTT_Ctb20 GGTT
./FinalSelection_emu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/GGEE.root output_emu_2018/GGEE.root GGEE GGEE
./FinalSelection_emu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/GGMM.root output_emu_2018/GGMM.root GGMM GGMM
#./FinalSelection_emu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/signal.root output_emu_2018/signal.root llscat llscat
./FinalSelection_emu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/signal_ptl8.root output_emu_2018/signal_ptl8.root llscat_ptl8 llscat
python Create_fake_emu.py --year=2018
python Create_chargemisid_emu.py --year=2018
hadd -f datacard_emu_2018.root output_emu_2018/chargemisid.root output_emu_2018/nonprompt.root output_emu_2018/MuonEG.root output_emu_2018/ZZ4L.root output_emu_2018/WZ3LNu.root output_emu_2018/TTTo2L2Nu.root output_emu_2018/VV2L2Nu.root output_emu_2018/DYall.root output_emu_2018/GGWW.root output_emu_2018/GGEE.root output_emu_2018/GGMM.root output_emu_2018/GGTT_Ctb20.root output_emu_2018/TTW.root output_emu_2018/TTZ.root output_emu_2018/TTG.root output_emu_2018/ZG.root output_emu_2018/signal_ptl8.root

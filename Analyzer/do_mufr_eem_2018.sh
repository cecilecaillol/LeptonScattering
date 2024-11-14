./Make.sh FinalSelection_mufr.cc
./FinalSelection_mufr.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FRmu/SingleMuon.root output_mufr_eem_2018/SingleMuon.root SingleMuon data_obs
./FinalSelection_mufr.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FRmu/MuonEG.root output_mufr_eem_2018/MuonEG.root MuonEG data_obs
./FinalSelection_mufr.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FRmu/EGamma.root output_mufr_eem_2018/EGamma.root EGamma data_obs
hadd -f output_mufr_eem_2018/Data.root output_mufr_eem_2018/SingleMuon.root output_mufr_eem_2018/MuonEG.root output_mufr_eem_2018/EGamma.root
./FinalSelection_mufr.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FRmu/ZZ4L.root output_mufr_eem_2018/ZZ4L.root ZZ4L ZZ4L
./FinalSelection_mufr.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FRmu/WZ3LNu.root output_mufr_eem_2018/WZ3LNu.root WZ3LNu WZ3LNu
python Measure_mufr_eem.py --year=2018
#hadd -f datacard_mufr_2018.root output_mufr_eem_2018/SingleMuon.root output_mufr_eem_2018/ZZ4L.root output_mufr_eem_2018/WZ3LNu.root 

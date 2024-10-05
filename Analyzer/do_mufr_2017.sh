./Make.sh FinalSelection_mufr_from3mu.cc
./FinalSelection_mufr_from3mu.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR2017/SingleMuon.root output_mufr_2017/SingleMuon.root data_obs data_obs
./FinalSelection_mufr_from3mu.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR2017/ZZ4L.root output_mufr_2017/ZZ4L.root ZZ4L ZZ4L
./FinalSelection_mufr_from3mu.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR2017/WZ3LNu.root output_mufr_2017/WZ3LNu.root WZ3LNu WZ3LNu
python Measure_mufr.py --year=2017
#hadd -f datacard_mufr_2017.root output_mufr_2017/SingleMuon.root output_mufr_2017/ZZ4L.root output_mufr_2017/WZ3LNu.root 

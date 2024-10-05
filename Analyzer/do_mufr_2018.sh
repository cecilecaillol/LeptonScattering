./Make.sh FinalSelection_mufr_from3mu.cc
./FinalSelection_mufr_from3mu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR/SingleMuon.root output_mufr_2018/SingleMuon.root data_obs data_obs
./FinalSelection_mufr_from3mu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR/ZZ4L.root output_mufr_2018/ZZ4L.root ZZ4L ZZ4L
./FinalSelection_mufr_from3mu.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR/WZ3LNu.root output_mufr_2018/WZ3LNu.root WZ3LNu WZ3LNu
python Measure_mufr.py --year=2018
#hadd -f datacard_mufr_2018.root output_mufr_2018/SingleMuon.root output_mufr_2018/ZZ4L.root output_mufr_2018/WZ3LNu.root 

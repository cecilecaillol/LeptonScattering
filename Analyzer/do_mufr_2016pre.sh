./Make.sh FinalSelection_mufr_from3mu.cc
./FinalSelection_mufr_from3mu.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR2016pre/SingleMuon.root output_mufr_2016pre/SingleMuon.root data_obs data_obs
./FinalSelection_mufr_from3mu.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR2016pre/ZZ4L.root output_mufr_2016pre/ZZ4L.root ZZ4L ZZ4L
./FinalSelection_mufr_from3mu.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR2016pre/WZ3LNu.root output_mufr_2016pre/WZ3LNu.root WZ3LNu WZ3LNu
python Measure_mufr.py --year=2016pre
#hadd -f datacard_mufr_2016pre.root output_mufr_2016pre/SingleMuon.root output_mufr_2016pre/ZZ4L.root output_mufr_2016pre/WZ3LNu.root 

./Make.sh FinalSelection_efr.cc
./FinalSelection_efr.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR2017/SingleMuon.root output_efr_2017/Data.root data_obs data_obs
#./FinalSelection_efr.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR2017/DoubleMuon.root output_efr_2017/Data.root data_obs data_obs
./FinalSelection_efr.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR2017/ZZ4L.root output_efr_2017/ZZ4L.root ZZ4L ZZ4L
./FinalSelection_efr.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR2017/WZ3LNu.root output_efr_2017/WZ3LNu.root WZ3LNu WZ3LNu
python Measure_efr.py --year=2017
#hadd -f datacard_efr_2017.root output_efr_2017/SingleMuon.root output_efr_2017/ZZ4L.root output_efr_2017/WZ3LNu.root 

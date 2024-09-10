./Make.sh FinalSelection_efr.cc
#./FinalSelection_efr.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR/SingleMuon.root output_efr_2018/Data.root data_obs data_obs
./FinalSelection_efr.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR/DoubleMuon.root output_efr_2018/Data.root data_obs data_obs
./FinalSelection_efr.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR/ZZ4L.root output_efr_2018/ZZ4L.root ZZ4L ZZ4L
./FinalSelection_efr.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR/WZ3LNu.root output_efr_2018/WZ3LNu.root WZ3LNu WZ3LNu
python Measure_efr.py --year=2018
#hadd -f datacard_efr_2018.root output_efr_2018/SingleMuon.root output_efr_2018/ZZ4L.root output_efr_2018/WZ3LNu.root 

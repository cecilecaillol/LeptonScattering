./Make.sh FinalSelection_efr.cc
./FinalSelection_efr.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR2016pre/SingleMuon.root output_efr_2016pre/Data.root data_obs data_obs
#./FinalSelection_efr.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR2016pre/DoubleMuon.root output_efr_2016pre/Data.root data_obs data_obs
./FinalSelection_efr.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR2016pre/ZZ4L.root output_efr_2016pre/ZZ4L.root ZZ4L ZZ4L
./FinalSelection_efr.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR2016pre/WZ3LNu.root output_efr_2016pre/WZ3LNu.root WZ3LNu WZ3LNu
python Measure_efr.py --year=2016pre
#hadd -f datacard_efr_2016pre.root output_efr_2016pre/SingleMuon.root output_efr_2016pre/ZZ4L.root output_efr_2016pre/WZ3LNu.root 

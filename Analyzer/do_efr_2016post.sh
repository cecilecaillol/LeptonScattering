./Make.sh FinalSelection_efr.cc
./FinalSelection_efr.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR2016post/SingleMuon.root output_efr_2016post/Data.root data_obs data_obs
#./FinalSelection_efr.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR2016post/DoubleMuon.root output_efr_2016post/Data.root data_obs data_obs
./FinalSelection_efr.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR2016post/ZZ4L.root output_efr_2016post/ZZ4L.root ZZ4L ZZ4L
./FinalSelection_efr.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR2016post/WZ3LNu.root output_efr_2016post/WZ3LNu.root WZ3LNu WZ3LNu
python Measure_efr.py --year=2016post
#hadd -f datacard_efr_2016post.root output_efr_2016post/SingleMuon.root output_efr_2016post/ZZ4L.root output_efr_2016post/WZ3LNu.root 

./Make.sh FinalSelection_mufr_from3mu.cc
./FinalSelection_mufr_from3mu.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR2016post/SingleMuon.root output_mufr_2016post/SingleMuon.root data_obs data_obs
./FinalSelection_mufr_from3mu.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR2016post/ZZ4L.root output_mufr_2016post/ZZ4L.root ZZ4L ZZ4L
./FinalSelection_mufr_from3mu.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR2016post/WZ3LNu.root output_mufr_2016post/WZ3LNu.root WZ3LNu WZ3LNu
python Measure_mufr.py --year=2016post
#hadd -f datacard_mufr_2016post.root output_mufr_2016post/SingleMuon.root output_mufr_2016post/ZZ4L.root output_mufr_2016post/WZ3LNu.root 

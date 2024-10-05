./Make.sh FinalSelection_WZ2mu1eCR.cc
./FinalSelection_WZ2mu1eCR.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/SingleMuon.root output_WZ2mu1eCR_2018/Data.root data_obs data_obs
./FinalSelection_WZ2mu1eCR.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/ZZ4L.root output_WZ2mu1eCR_2018/ZZ4L.root ZZ4L ZZ4L
./FinalSelection_WZ2mu1eCR.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/SSEM/WZ3LNu.root output_WZ2mu1eCR_2018/WZ3LNu.root WZ3LNu WZ3LNu
python Create_fake_WZCR.py --year="2018" --channel="2mu1e"
hadd -f datacard_WZ2mu1eCR_2018.root output_WZ2mu1eCR_2018/nonprompt.root output_WZ2mu1eCR_2018/ZZ4L.root output_WZ2mu1eCR_2018/WZ3LNu.root output_WZ2mu1eCR_2018/Data.root 

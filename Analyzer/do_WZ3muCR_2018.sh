./Make.sh FinalSelection_WZ3muCR.cc
./FinalSelection_WZ3muCR.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR/SingleMuon.root output_WZ3muCR_2018/Data.root data_obs data_obs
./FinalSelection_WZ3muCR.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR/ZZ4L.root output_WZ3muCR_2018/ZZ4L.root ZZ4L ZZ4L
./FinalSelection_WZ3muCR.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/FR/WZ3LNu.root output_WZ3muCR_2018/WZ3LNu.root WZ3LNu WZ3LNu
python Create_fake_WZCR.py --year="2018" --channel="3mu"
hadd -f datacard_WZ3muCR_2018.root output_WZ3muCR_2018/nonprompt.root output_WZ3muCR_2018/ZZ4L.root output_WZ3muCR_2018/WZ3LNu.root output_WZ3muCR_2018/Data.root 

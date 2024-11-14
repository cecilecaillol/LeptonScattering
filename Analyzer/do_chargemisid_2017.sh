./Make.sh FinalSelection_echargemisid.cc
./FinalSelection_echargemisid.exe 2017 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/ChargeMisid2017/SingleElectron.root output_chargemisid/Data2017.root data_obs data_obs
./Make.sh Fit_el_CMSShape.cc 
./Fit_el_CMSShape.exe 2017  output_chargemisid/Data2017.root chargemisid_2017_data.root Data

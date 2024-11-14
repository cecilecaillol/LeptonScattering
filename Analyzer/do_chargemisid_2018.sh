./Make.sh FinalSelection_echargemisid.cc
./FinalSelection_echargemisid.exe 2018 /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/ChargeMisid2018/EGamma.root output_chargemisid/Data2018.root data_obs data_obs
./Make.sh Fit_el_CMSShape.cc 
./Fit_el_CMSShape.exe 2018  output_chargemisid/Data2018.root chargemisid_2018_data.root Data

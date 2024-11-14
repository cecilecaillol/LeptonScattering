./Make.sh FinalSelection_echargemisid.cc
./FinalSelection_echargemisid.exe 2016pre /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/ChargeMisid2016pre/SingleElectron.root output_chargemisid/Data2016pre.root data_obs data_obs
./Make.sh Fit_el_CMSShape.cc 
./Fit_el_CMSShape.exe 2016pre  output_chargemisid/Data2016pre.root chargemisid_2016pre_data.root Data

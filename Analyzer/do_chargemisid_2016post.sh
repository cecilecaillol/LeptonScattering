./Make.sh FinalSelection_echargemisid.cc
./FinalSelection_echargemisid.exe 2016post /eos/cms/store/group/cmst3/user/ccaillol/LeptonScattering/ChargeMisid2016post/SingleElectron.root output_chargemisid/Data2016post.root data_obs data_obs
./Make.sh Fit_el_CMSShape.cc 
./Fit_el_CMSShape.exe 2016post  output_chargemisid/Data2016post.root chargemisid_2016post_data.root Data

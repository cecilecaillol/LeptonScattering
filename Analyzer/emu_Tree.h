      int n_mu, n_el, n_pv, pv_ntrk2, pv_ntrk3, hlt_isomu24, hlt_mu17_mu8, hlt_mu17_mu8_mass3p8, hlt_mu8_el23, hlt_mu23_el12, hlt_el23_el12, hlt_el25_el25, hlt_mu12_el23, hlt_mu9_mu9_el9, hlt_el32, pv_nmu,
             ntrk_prompt, ntrk_nonprompt, is_DYtauetaumu, is_ZG,
             hlt_isomu27, hlt_mu23_el12_DZ, hlt_mu8_el23_DZ, hlt_mu17_mu8_DZ_mass3p8, hlt_mu17_mu8_DZ_mass8, hlt_isotkmu24,
hlt_mu17_mu8_DZ, hlt_mu17_tkmu8, hlt_mu17_tkmu8_DZ, hlt_tkmu17_tkmu8, hlt_tkmu17_tkmu8_DZ;
      int el_conversionveto[5], mu_trigger23[5], mu_trigger8[5],mu_frompv[5], mu_charge[5], mu_tight[5],el_charge[5], el_frompv[5], el_trigger[5], el_chargeconsistent[5], el_genPart[5], el_losthits[5];
      int el_CBIDLoose[5],el_CBIDMedium[5],el_CBIDTight[5],el_CBIDVeto[5],el_MVAIDisoWP80[5],el_MVAIDisoWP90[5],el_MVAIDisoWPHZZ[5],el_MVAIDisoWPLoose[5],el_MVAIDnoisoWP80[5],el_MVAIDnoisoWP90[5],el_MVAIDnoisoWPLoose[5], mu_pfiso[5], mu_genPart[5];
      double mu_pt[5], mu_eta[5], mu_phi[5], mu_dz[5], mu_dxy[5], mu_rawiso[5], mu_sip2d[5], 
             el_pt[5], el_eta[5], el_phi[5], el_pfiso[5], el_dxy[5], el_dz[5], el_rawiso[5], el_sip2d[5], 
             pv_d0, pv_dz, pv_ndof, pv_chi2,
         pt_2mu, pt_3mu_s, pt_3mu_v, mass_2mu, dphi_2mu, pv_charge, pt_vector, pt_scalar;

   	float gentop_pt, genantitop_pt, gentop_eta, genantitop_eta, gentop_phi, genantitop_phi, genWeight, Pileup_trueNumInteractions;

   Float_t         PuppiMET_pt;
   Float_t         PuppiMET_phi;
   Float_t         taug2weight;
   Int_t           ntrk_HS;
   Int_t           ntrk_signal;
   Int_t           ntrk_all;
   Int_t           ntrk_PU;
   Int_t           ntrk0p02_HS;
   Int_t           ntrk0p02_signal;
   Int_t           ntrk0p02_all;
   Int_t           ntrk0p02_PU;
   Int_t           ntrk0p03_HS;
   Int_t           ntrk0p03_signal;
   Int_t           ntrk0p03_all;
   Int_t           ntrk0p03_PU;

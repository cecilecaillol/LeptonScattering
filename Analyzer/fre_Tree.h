      int n_mu, n_el, hlt_isomu24, hlt_mu17_mu8, hlt_isomu27, hlt_isotkmu24,
             hlt_mu23_el12, hlt_mu23_el12_DZ, hlt_mu8_el23, hlt_mu8_el23_DZ, hlt_mu17_mu8_DZ, hlt_mu17_tkmu8, 
             hlt_mu17_tkmu8_DZ, hlt_tkmu17_tkmu8, hlt_tkmu17_tkmu8_DZ, hlt_mu17_mu8_DZ_mass3p8, hlt_mu17_mu8_DZ_mass8,
             ntrk_prompt, ntrk_nonprompt, ntrk_all;
      int mu_trigger[5], mu_charge[5], mu_tight[5], mu_pfiso[5], mu_genPart[5];
      float mu_pt[5], mu_eta[5], mu_phi[5], mu_dz[5], mu_dxy[5], mu_rawiso[5], mu_sip2d[5];
   	float gentop_pt, genantitop_pt, genWeight;

      int el_conversionveto[5],el_charge[5], el_chargeconsistent[5], el_genPart[5], el_losthits[5];
      int el_CBIDLoose[5],el_CBIDMedium[5],el_CBIDTight[5],el_CBIDVeto[5],el_MVAIDisoWP80[5],el_MVAIDisoWP90[5],el_MVAIDisoWPHZZ[5],el_MVAIDisoWPLoose[5],el_MVAIDnoisoWP80[5],el_MVAIDnoisoWP90[5],el_MVAIDnoisoWPLoose[5];
      float el_pt[5], el_eta[5], el_phi[5], el_pfiso[5], el_dxy[5], el_dz[5], el_sip2d[5];
      float Pileup_trueNumInteractions;
      float PuppiMET_pt, PuppiMET_phi;

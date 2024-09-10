#include <TH2.h>
#include <TH2F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include "TMultiGraph.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <stdio.h>
#include <TF1.h>
#include <TDirectoryFile.h>
#include <TRandom3.h>
#include "TLorentzVector.h"
#include "TString.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TKey.h"
#include "THashList.h"
#include "THStack.h"
#include "TPaveLabel.h"
#include "TFile.h"
#include "TTree.h"
#include "frmu_Tree.h"
#include "myHelper.h"
#include "LumiReweightingStandAlone.h"

using namespace std;

int main(int argc, char** argv) {

    int is_control=0;

    std::string year = *(argv + 1);
    std::string input = *(argv + 2);
    std::string output = *(argv + 3);
    std::string sample = *(argv + 4);
    std::string name = *(argv + 5);

    TFile *f_Double = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    TTree *arbre = (TTree*) f_Double->Get("demo/data");

    //TTree *arbre2 = (TTree*) f_Double->Get("Runs");
    float ngen=0;
    float ngenu=0;
    if (name!="data_obs") {
        TH1F *h_step = (TH1F*) f_Double->Get("demo/step");
	ngen=h_step->GetBinContent(2);
    }
    /*if (name!="data_obs") {
       Int_t nentries_wtn2 = (Int_t) arbre2->GetEntries();
       arbre2->SetBranchAddress("genEventSumw", &genEventSumw);
       arbre2->SetBranchAddress("genEventCount", &genEventCount);
       for (Int_t i = 0; i < nentries_wtn2; i++) {
         arbre2->GetEntry(i);
         ngen+=genEventSumw;
	 ngenu+=genEventCount;
       }
    }
    cout<<"weighted events: "<<ngen<<endl;
    cout<<"unweighted events: "<<ngenu<<endl;*/

    float xs=1.0; float weight=1.0; float luminosity=59830.0;
    if (year=="2017") luminosity=41480.0;
    if (year=="2016pre") luminosity=19520.0;
    if (year=="2016post") luminosity=16810.0;
    if (sample=="Z" or sample=="DY" or sample=="ZL" or sample=="ZTT" or sample=="ZJ" or sample=="ZLL"){ xs=6077.2; weight=luminosity*xs/ngen;}
    else if (sample=="DYemu"){ xs=2025.7*(0.178+0.174)*(0.178+0.174); weight=luminosity*xs/ngen;}
    else if (sample=="W_Pt100to250"){ xs=689.75; weight=luminosity*xs/ngen;}
    else if (sample=="W_Pt250to400"){ xs=24.51; weight=luminosity*xs/ngen;}
    else if (sample=="W_Pt400to600"){xs=3.110; weight=luminosity*xs/ngen;}
    else if (sample=="W_Pt600toInf"){ xs=0.4683; weight=luminosity*xs/ngen;}
    else if (sample=="W"){ xs=61527.5; weight=luminosity*xs/ngen;}
    else if (sample=="DY_Pt50to100"){ xs=387.13; weight=luminosity*xs/ngen;}
    else if (sample=="DY_Pt100to250"){ xs=89.39; weight=luminosity*xs/ngen;}
    else if (sample=="DY_Pt250to400"){ xs=3.43; weight=luminosity*xs/ngen;}
    else if (sample=="DY_Pt400to650"){ xs=0.464; weight=luminosity*xs/ngen;}
    else if (sample=="DY_Pt650toInf"){ xs=0.0436; weight=luminosity*xs/ngen;}
    else if (sample=="TTTo2L2Nu"){ xs=833.0*0.1061; weight=luminosity*xs/ngen;}
    else if (sample=="TTToSemiLeptonic"){ xs=791*0.4392; weight=luminosity*xs/ngen;}
    else if (sample=="TTToHadronic"){ xs=791*0.4544; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ4L"){ xs=1.21; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2L2Q"){ xs=3.22; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2Q2L"){ xs=3.22; weight=luminosity*xs/ngen;}
    else if (sample=="WZ3LNu"){ xs=4.71; weight=luminosity*xs/ngen;}
    else if (sample=="VV2L2Nu"){ xs=11.09+0.9738; weight=luminosity*xs/ngen;}
    else if (sample=="WW2L2Nu"){ xs=11.09; weight=luminosity*xs/ngen;}
    else if (sample=="WZ2L2Q"){ xs=6.419; weight=luminosity*xs/ngen;}
    else if (sample=="WZ2Q2L"){ xs=6.419; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2L2Nu"){ xs=0.9738; weight=luminosity*xs/ngen;}
    else if (sample=="WZ"){ xs=47.13; weight=luminosity*xs/ngen;}
    else if (sample=="WW"){ xs=118.7; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_top"){ xs=39.65; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_antitop"){ xs=39.65; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_top"){ xs=134.2; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_antitop"){ xs=80.0; weight=luminosity*xs/ngen;}
    else if (sample=="GGTT"){ xs=1.161*0.008735; weight=luminosity*xs/ngen;}
    else if (sample=="GGWW"){ xs=0.00656; weight=luminosity*xs/ngen;} // new 1/137
    else if (name=="data_obs"){ weight=1.0;}
    else if (name=="test") { xs=1.0; weight=luminosity*xs/ngen;}
    else if (sample=="GGTT_Ctb20"){ xs=1.048*0.0403; weight=luminosity*xs/ngen;} // new 1/137
    else if (sample=="GGHTT"){ xs=48.30*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="GGHWW") {xs=48.30*0.2203*0.3258*0.3258; weight=luminosity*xs/ngen;}

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(10);

    arbre->SetBranchAddress("n_mu", &n_mu);
    arbre->SetBranchAddress("hlt_isomu24", &hlt_isomu24);
    arbre->SetBranchAddress("hlt_mu17_mu8", &hlt_mu17_mu8);
    arbre->SetBranchAddress("ntrk_prompt", &ntrk_prompt);
    arbre->SetBranchAddress("ntrk_nonprompt", &ntrk_nonprompt);
    arbre->SetBranchAddress("mu_trigger", &mu_trigger);
    arbre->SetBranchAddress("mu_charge", &mu_charge);
    arbre->SetBranchAddress("mu_genPart", &mu_genPart);
    arbre->SetBranchAddress("mu_rawiso", &mu_rawiso);
   arbre->SetBranchAddress("mu_pt", &mu_pt);
   arbre->SetBranchAddress("mu_eta", &mu_eta);
   arbre->SetBranchAddress("mu_phi", &mu_phi);
   arbre->SetBranchAddress("mu_pfiso", &mu_pfiso);
   arbre->SetBranchAddress("mu_dz", &mu_dz);
   arbre->SetBranchAddress("mu_dxy", &mu_dxy);
   arbre->SetBranchAddress("genWeight", &genWeight);
   arbre->SetBranchAddress("gentop_pt", &gentop_pt);
   arbre->SetBranchAddress("genantitop_pt", &genantitop_pt);
   arbre->SetBranchAddress("Pileup_trueNumInteractions", &Pileup_trueNumInteractions);

   arbre->SetBranchAddress("el_conversionveto", &el_conversionveto);
   arbre->SetBranchAddress("el_charge", &el_charge);
   arbre->SetBranchAddress("el_genPart", &el_genPart);
   arbre->SetBranchAddress("el_chargeconsistent", &el_chargeconsistent);
   arbre->SetBranchAddress("el_CBIDLoose", &el_CBIDLoose);
   arbre->SetBranchAddress("el_CBIDMedium", &el_CBIDMedium);
   arbre->SetBranchAddress("el_CBIDTight", &el_CBIDTight);
   arbre->SetBranchAddress("el_CBIDVeto", &el_CBIDVeto);
   arbre->SetBranchAddress("el_MVAIDisoWP80", &el_MVAIDisoWP80);
   arbre->SetBranchAddress("el_MVAIDisoWP90", &el_MVAIDisoWP90);
   arbre->SetBranchAddress("el_MVAIDisoWPHZZ", &el_MVAIDisoWPHZZ);
   arbre->SetBranchAddress("el_MVAIDisoWPLoose", &el_MVAIDisoWPLoose);
   arbre->SetBranchAddress("el_MVAIDnoisoWP80", &el_MVAIDnoisoWP80);
   arbre->SetBranchAddress("el_MVAIDnoisoWP90", &el_MVAIDnoisoWP90);
   arbre->SetBranchAddress("el_MVAIDnoisoWPLoose", &el_MVAIDnoisoWPLoose);
   arbre->SetBranchAddress("el_pt", &el_pt);
   arbre->SetBranchAddress("el_eta", &el_eta);
   arbre->SetBranchAddress("el_phi", &el_phi);
   arbre->SetBranchAddress("el_dxy", &el_dxy);
   arbre->SetBranchAddress("el_dz", &el_dz);
   arbre->SetBranchAddress("n_el", &n_el);


   TFile* f_eleIDSF=new TFile("scalefactors/egammaEffi.txt_Ele_wp80iso_EGM2D.root","read");
   TH2F* h_eleIDSF= (TH2F*) f_eleIDSF->Get("EGamma_SF2D");
   TFile* f_eleRecoSF=new TFile("scalefactors/egammaEffi_ptAbove20.txt_EGM2D_UL2018.root","read");
   TH2F* h_eleRecoSF= (TH2F*) f_eleRecoSF->Get("EGamma_SF2D");
   TFile* f_eleRecoBelowSF=new TFile("scalefactors/egammaEffi_ptBelow20.txt_EGM2D_UL2018.root","read");
   TH2F* h_eleRecoBelowSF= (TH2F*) f_eleRecoBelowSF->Get("EGamma_SF2D");

   if (year=="2017"){
      TFile* f_eleIDSF=new TFile("scalefactors/egammaEffi.txt_EGM2D_MVA80iso_UL17.root","read");
      h_eleIDSF= (TH2F*) f_eleIDSF->Get("EGamma_SF2D");
      TFile* f_eleRecoSF=new TFile("scalefactors/egammaEffi_ptAbove20.txt_EGM2D_UL2017.root","read");
      h_eleRecoSF= (TH2F*) f_eleRecoSF->Get("EGamma_SF2D");
      TFile* f_eleRecoBelowSF=new TFile("scalefactors/egammaEffi_ptBelow20.txt_EGM2D_UL2017.root","read");
      h_eleRecoBelowSF= (TH2F*) f_eleRecoBelowSF->Get("EGamma_SF2D");
   }
   else if (year=="2016post"){
      TFile* f_eleIDSF=new TFile("scalefactors/egammaEffi.txt_Ele_wp80iso_postVFP_EGM2D.root","read");
      h_eleIDSF= (TH2F*) f_eleIDSF->Get("EGamma_SF2D");
      TFile* f_eleRecoSF=new TFile("scalefactors/egammaEffi_ptAbove20.txt_EGM2D_UL2016postVFP.root","read");
      h_eleRecoSF= (TH2F*) f_eleRecoSF->Get("EGamma_SF2D");
      TFile* f_eleRecoBelowSF=new TFile("scalefactors/egammaEffi_ptBelow20.txt_EGM2D_UL2016postVFP.root","read");
      h_eleRecoBelowSF= (TH2F*) f_eleRecoBelowSF->Get("EGamma_SF2D");
   }
   else if (year=="2016pre"){
      TFile* f_eleIDSF=new TFile("scalefactors/egammaEffi.txt_Ele_wp80iso_preVFP_EGM2D.root","read");
      h_eleIDSF= (TH2F*) f_eleIDSF->Get("EGamma_SF2D");
      TFile* f_eleRecoSF=new TFile("scalefactors/egammaEffi_ptAbove20.txt_EGM2D_UL2016preVFP.root","read");
      h_eleRecoSF= (TH2F*) f_eleRecoSF->Get("EGamma_SF2D");
      TFile* f_eleRecoBelowSF=new TFile("scalefactors/egammaEffi_ptBelow20.txt_EGM2D_UL2016preVFP.root","read");
      h_eleRecoBelowSF= (TH2F*) f_eleRecoBelowSF->Get("EGamma_SF2D");
   }

   TFile* f_muonID=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2018_UL_ID.root","read");
   TFile* f_muonIso=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2018_UL_ISO.root","read");
   TH2F* h_muonIsoSF= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt");
   TH2F* h_muonIDSF= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt");
   TH2F* h_muonIsoSF_stat= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt_stat");
   TH2F* h_muonIDSF_stat= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt_stat");
   TH2F* h_muonIsoSF_syst= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt_syst");
   TH2F* h_muonIDSF_syst= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt_syst");

   if (year=="2016pre"){
      TFile* f_muonID=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2016_UL_HIPM_ID.root","read");
      TFile* f_muonIso=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2016_UL_HIPM_ISO.root","read");
      h_muonIsoSF= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt");
      h_muonIDSF= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt");
      h_muonIsoSF_stat= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt_stat");
      h_muonIDSF_stat= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt_stat");
      h_muonIsoSF_syst= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt_syst");
      h_muonIDSF_syst= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt_syst");
   }
   if (year=="2016post"){
      TFile* f_muonID=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2016_UL_ID.root","read");
      TFile* f_muonIso=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2016_UL_ISO.root","read");
      h_muonIsoSF= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt");
      h_muonIDSF= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt");
      h_muonIsoSF_stat= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt_stat");
      h_muonIDSF_stat= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt_stat");
      h_muonIsoSF_syst= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt_syst");
      h_muonIDSF_syst= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt_syst");
   }
   if (year=="2017"){
      TFile* f_muonID=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2017_UL_ID.root","read");
      TFile* f_muonIso=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2017_UL_ISO.root","read");
      h_muonIsoSF= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt");
      h_muonIDSF= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt");
      h_muonIsoSF_stat= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt_stat");
      h_muonIDSF_stat= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt_stat");
      h_muonIsoSF_syst= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt_syst");
      h_muonIDSF_syst= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt_syst");
   }

   reweight::LumiReWeighting* LumiWeights_12;
   LumiWeights_12 = new reweight::LumiReWeighting("mcPileupUL2018.root", "PileupHistogram-UL2018-100bins_withVar.root", "pu_mc", "pileup");

   //float bins0[]
   float bins0[] = {8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100};
   //float bins0[]={5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,25,30,35,40,50,75,100};
   int  binnum0 = sizeof(bins0)/sizeof(Float_t) - 1;

   TH1F*  h_ptB_anti = new TH1F("h_ptB_anti","h_ptB_anti",binnum0,bins0); h_ptB_anti->Sumw2();
   TH1F*  h_ptB_iso = new TH1F("h_ptB_iso","h_ptB_iso",binnum0,bins0); h_ptB_iso->Sumw2();
   TH1F*  h_ptE_iso = new TH1F("h_ptE_iso","h_ptE_iso",binnum0,bins0); h_ptE_iso->Sumw2();
   TH1F*  h_ptE_anti = new TH1F("h_ptE_anti","h_ptE_anti",binnum0,bins0); h_ptE_anti->Sumw2();

   TH1F*  h_mumumass = new TH1F("h_mumumass","h_mumumass",20,70,110); h_mumumass->Sumw2();

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();

   for (Int_t i = 0; i < nentries_wtn; i++) {
	arbre->LoadTree(i);
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	int idx1=-1; int idx2=-1; float best_Zmass=15.000001;
	for (int j=0; j<n_el-1; ++j){
	   TLorentzVector tmp1;
           tmp1.SetPtEtaPhiM(el_pt[j], el_eta[j], el_phi[j], 0.105);
	   for (int k=j+1; k<n_el; ++k){
	      TLorentzVector tmp2;
	      tmp2.SetPtEtaPhiM(el_pt[k], el_eta[k], el_phi[k], 0.105);
	      if (fabs(el_dz[j])<0.1 and fabs(el_dz[k])<0.1 and el_dxy[j]<0.05 and el_dxy[k]<0.05 and el_charge[j]*el_charge[k]<0 and fabs((tmp1+tmp2).M()-90)<best_Zmass and tmp1.DeltaR(tmp2)>0.3 and el_MVAIDisoWP80[j] and el_MVAIDisoWP80[k] and (el_pt[j]>33 or el_pt[k]>33)){ idx1=j; idx2=k; best_Zmass= fabs((tmp1+tmp2).M()-90);}
	   }
	}
	if (idx1==-1 or idx2==-1) continue;
        TLorentzVector my_el1;
         my_el1.SetPtEtaPhiM(el_pt[idx1], el_eta[idx1], el_phi[idx1], 0.105);
        TLorentzVector my_el2;
         my_el2.SetPtEtaPhiM(el_pt[idx2], el_eta[idx2], el_phi[idx2], 0.105);
        h_mumumass->Fill((my_el1+my_el2).M());

	int idx3=-1;
        for (int l=0; l<n_mu; ++l){
           TLorentzVector tmp3;
           tmp3.SetPtEtaPhiM(mu_pt[l], mu_eta[l], mu_phi[l], 0.);
           if (mu_pt[l]>8 and tmp3.DeltaR(my_el1)>0.3 and tmp3.DeltaR(my_el2)>0.3 and mu_dz[l]<0.1 and mu_dxy[l]<0.05 and idx3<0) idx3=l;
	}
	if (idx3==-1) continue;


        if (name!="data_obs"){
	    if (mu_genPart[idx3]==0) continue;
	}

        //h_mumumass->Fill((my_el1+my_el2).M());


	//if (!hlt_isomu24) continue;
	if (!hlt_mu17_mu8) continue;

        // Block weights
        float aweight=1.0;
        if (name!="data_obs"){
           //aweight=aweight*L1PreFiringWeight_Nom;
           aweight*=LumiWeights_12->weight(Pileup_trueNumInteractions);
           aweight=aweight*genWeight;

	   //FIXME add trigger 

           float ept1=my_el1.Pt();
           if (ept1>120) ept1=119;
           float elidsf1_nom = h_eleIDSF->GetBinContent(h_eleIDSF->GetXaxis()->FindBin(my_el1.Eta()),h_eleIDSF->GetYaxis()->FindBin(ept1));
           float elRecoSF1 = 1.0;
           if (ept1<20) elRecoSF1 = h_eleRecoBelowSF->GetBinContent(h_eleRecoBelowSF->GetXaxis()->FindBin(my_el1.Eta()),h_eleRecoBelowSF->GetYaxis()->FindBin(ept1));
           else elRecoSF1 = h_eleRecoSF->GetBinContent(h_eleRecoSF->GetXaxis()->FindBin(my_el1.Eta()),h_eleRecoSF->GetYaxis()->FindBin(ept1));
           aweight=aweight*elidsf1_nom*elRecoSF1;

           float ept2=my_el2.Pt();
           if (ept2>120) ept2=119;
           float elidsf2_nom = h_eleIDSF->GetBinContent(h_eleIDSF->GetXaxis()->FindBin(my_el2.Eta()),h_eleIDSF->GetYaxis()->FindBin(ept2));
           float elRecoSF2 = 1.0;
           if (ept2<20) elRecoSF2 = h_eleRecoBelowSF->GetBinContent(h_eleRecoBelowSF->GetXaxis()->FindBin(my_el2.Eta()),h_eleRecoBelowSF->GetYaxis()->FindBin(ept2));
           else elRecoSF2 = h_eleRecoSF->GetBinContent(h_eleRecoSF->GetXaxis()->FindBin(my_el2.Eta()),h_eleRecoSF->GetYaxis()->FindBin(ept2));
           aweight=aweight*elidsf2_nom*elRecoSF2;

	   // FIXME add 3rd mu SF iso

           if (sample=="TTTo2L2Nu" or sample=="TTToSemiLeptonic" or sample=="TTToHadronic") {float toppt_reweighting=pow((TMath::Exp(0.0615-0.0005*gentop_pt)*TMath::Exp(0.0615-0.0005*genantitop_pt)),0.5); aweight*=toppt_reweighting; }

	   aweight*=0.95;// trigger and 3rd lepton //FIXME
        }

	if (mu_rawiso[idx3]>1.0) continue;
	bool is_isolated=mu_pfiso[idx3]>0.5;

	if (!is_isolated and fabs(mu_eta[idx3])<1.2) h_ptB_anti->Fill(mu_pt[idx3],weight*aweight);
        if (is_isolated and fabs(mu_eta[idx3])<1.2) h_ptB_iso->Fill(mu_pt[idx3],weight*aweight);
        if (!is_isolated and fabs(mu_eta[idx3])>1.2) h_ptE_anti->Fill(mu_pt[idx3],weight*aweight);
        if (is_isolated and fabs(mu_eta[idx3])>1.2) h_ptE_iso->Fill(mu_pt[idx3],weight*aweight);

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

cout<<h_mumumass->GetEntries()<<endl;

    h_ptB_anti->SetName("pt_antimu_barrel");
    h_ptB_anti->Write();
    h_ptB_iso->SetName("pt_isomu_barrel");
    h_ptB_iso->Write();
    h_mumumass->Write();

    h_ptE_anti->SetName("pt_antimu_endcaps");
    h_ptE_anti->Write();
    h_ptE_iso->SetName("pt_isomu_endcaps");
    h_ptE_iso->Write();

    fout->Close();
} 



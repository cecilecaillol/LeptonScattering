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
#include "fre_Tree.h"
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
    TTree *arbre = (TTree*) f_Double->Get("demo/tree_fr");

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
    arbre->SetBranchAddress("mu_rawiso", &mu_rawiso);
    arbre->SetBranchAddress("mu_genPart", &mu_genPart);
   arbre->SetBranchAddress("mu_pt", &mu_pt);
   arbre->SetBranchAddress("mu_eta", &mu_eta);
   arbre->SetBranchAddress("mu_phi", &mu_phi);
   arbre->SetBranchAddress("mu_pfiso", &mu_pfiso);
   arbre->SetBranchAddress("mu_dz", &mu_dz);
   arbre->SetBranchAddress("mu_dxy", &mu_dxy);
   arbre->SetBranchAddress("genWeight", &genWeight);
   arbre->SetBranchAddress("gentop_pt", &gentop_pt);
   arbre->SetBranchAddress("genantitop_pt", &genantitop_pt);

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

   arbre->SetBranchAddress("Pileup_trueNumInteractions", &Pileup_trueNumInteractions);

   arbre->SetBranchAddress("PuppiMET_pt", &PuppiMET_pt);
   arbre->SetBranchAddress("PuppiMET_phi", &PuppiMET_phi);


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

   float bins0[] = {5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,25,30,35,40,50,75,100};
   //float bins0[] = {0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.2};
   int  binnum0 = sizeof(bins0)/sizeof(Float_t) - 1;

   float bins1[] = {-1,0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100};
//1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,25,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80};
   int  binnum1 = sizeof(bins1)/sizeof(Float_t) - 1;

   TH1F*  h_ptB_anti = new TH1F("h_ptB_anti","h_ptB_anti",binnum0,bins0); h_ptB_anti->Sumw2();
   TH1F*  h_ptB_iso = new TH1F("h_ptB_iso","h_ptB_iso",binnum0,bins0); h_ptB_iso->Sumw2();
   TH1F*  h_ptE_iso = new TH1F("h_ptE_iso","h_ptE_iso",binnum0,bins0); h_ptE_iso->Sumw2();
   TH1F*  h_ptE_anti = new TH1F("h_ptE_anti","h_ptE_anti",binnum0,bins0); h_ptE_anti->Sumw2();

   TH1F*  h_ntracks_anti = new TH1F("h_ntracks_anti","h_ntracks_anti",binnum1,bins1); h_ntracks_anti->Sumw2();
   TH1F*  h_ntracks_iso = new TH1F("h_ntracks_iso","h_ntracks_iso",binnum1,bins1); h_ntracks_iso->Sumw2();

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();

   for (Int_t i = 0; i < nentries_wtn; i++) {
	arbre->LoadTree(i);
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	if (n_mu<2) continue;
        if (n_el<1) continue;
	if (n_mu+n_el>3) continue;

	int idx1=-1; int idx2=-1; float best_Zmass=15.000001;
	for (int j=0; j<n_mu-1; ++j){
	   TLorentzVector tmp1;
           tmp1.SetPtEtaPhiM(mu_pt[j], mu_eta[j], mu_phi[j], 0.105);
	   for (int k=j+1; k<n_mu; ++k){
	      TLorentzVector tmp2;
	      tmp2.SetPtEtaPhiM(mu_pt[k], mu_eta[k], mu_phi[k], 0.105);
	      if ((mu_trigger[j] or mu_trigger[k]) and fabs(mu_dz[j])<0.1 and fabs(mu_dz[k])<0.1 and mu_dxy[j]<0.05 and mu_dxy[k]<0.05 and mu_charge[j]*mu_charge[k]<0 and fabs((tmp1+tmp2).M()-91.1876)<best_Zmass and tmp1.DeltaR(tmp2)>0.5 and mu_rawiso[j]<0.25 and mu_rawiso[k]<0.25 and (mu_pt[j]>20 or mu_pt[k]>20) and mu_pt[j]>10 and mu_pt[k]>10){ idx1=j; idx2=k; best_Zmass= fabs((tmp1+tmp2).M()-91.1876);}
	   }
	}
	if (idx1==-1 or idx2==-1) continue;
	TLorentzVector my_mu1;
         my_mu1.SetPtEtaPhiM(mu_pt[idx1], mu_eta[idx1], mu_phi[idx1], 0.105);
        TLorentzVector my_mu2;
         my_mu2.SetPtEtaPhiM(mu_pt[idx2], mu_eta[idx2], mu_phi[idx2], 0.105);

	int idx3=-1;
        for (int l=0; l<n_el; ++l){
           TLorentzVector tmp3;
           tmp3.SetPtEtaPhiM(el_pt[l], el_eta[l], el_phi[l], 0.);
	   if (tmp3.DeltaR(my_mu1)>0.3 and tmp3.DeltaR(my_mu2)>0.3 and fabs(el_dz[l])<0.1 and el_dxy[l]<0.05 and idx3<0 and el_chargeconsistent[l] and el_conversionveto[l] and el_MVAIDisoWPLoose[l] and fabs(el_eta[l])<2.5) idx3=l;
        }
	if (idx3==-1) continue;

        TLorentzVector el;
        el.SetPtEtaPhiM(el_pt[idx3], el_eta[idx3], el_phi[idx3], 0.1);

	//if (!hlt_isomu24) continue;
	if (!hlt_mu17_mu8) continue;

	if (name!="data_obs"){
	   if (el_genPart[idx3]==0) continue;
	}

        // Block weights
        float aweight=1.0;
        if (name!="data_obs"){
           //aweight=aweight*L1PreFiringWeight_Nom;
           //aweight=aweight*puWeight;
           aweight*=LumiWeights_12->weight(Pileup_trueNumInteractions);
           aweight=aweight*genWeight;

           float mu1pt=mu_pt[idx1];
           if (mu1pt>120) mu1pt=119;
           if (mu1pt<15) mu1pt=16;
           float muidsf_nom1 = h_muonIDSF->GetBinContent(h_muonIDSF->GetXaxis()->FindBin(fabs(mu_eta[idx1])),h_muonIDSF->GetYaxis()->FindBin(mu1pt));
           float muisosf_nom1 = h_muonIsoSF->GetBinContent(h_muonIsoSF->GetXaxis()->FindBin(fabs(mu_eta[idx1])),h_muonIsoSF->GetYaxis()->FindBin(mu1pt));
           float mu2pt=mu_pt[idx2];
           if (mu2pt>120) mu2pt=119;
           if (mu2pt<15) mu2pt=16;
           float muidsf_nom2 = h_muonIDSF->GetBinContent(h_muonIDSF->GetXaxis()->FindBin(fabs(mu_eta[idx2])),h_muonIDSF->GetYaxis()->FindBin(mu2pt));
           float muisosf_nom2 = h_muonIsoSF->GetBinContent(h_muonIsoSF->GetXaxis()->FindBin(fabs(mu_eta[idx2])),h_muonIsoSF->GetYaxis()->FindBin(mu2pt));
           aweight=aweight*muidsf_nom1*muisosf_nom2*muidsf_nom1*muisosf_nom2;//*GetMuRecoSF(year,my_mu.Eta());

           if (sample=="TTTo2L2Nu" or sample=="TTToSemiLeptonic" or sample=="TTToHadronic") {float toppt_reweighting=pow((TMath::Exp(0.0615-0.0005*gentop_pt)*TMath::Exp(0.0615-0.0005*genantitop_pt)),0.5); aweight*=toppt_reweighting; }

           aweight*=0.95;// trigger and 3rd lepton //FIXME
        }

	bool is_isolated=el_MVAIDisoWP80[idx3];
	TLorentzVector my_met;
        my_met.SetPtEtaPhiM(PuppiMET_pt,0,PuppiMET_phi,0);
        float mt = TMass_F(el.Pt(), el.Px(), el.Py(), PuppiMET_pt, PuppiMET_phi);
        float var=el.Pt();
        if (mt>50) continue;
	//if (el.Pt()<30) continue; //FIXME
        //var=fabs(el.DeltaPhi(my_met));//FIXME

	if (!is_isolated and fabs(el_eta[idx3])<1.5) h_ptB_anti->Fill(var,weight*aweight);
        if (is_isolated and fabs(el_eta[idx3])<1.5) h_ptB_iso->Fill(var,weight*aweight);
        if (!is_isolated and fabs(el_eta[idx3])>1.5) h_ptE_anti->Fill(var,weight*aweight);
        if (is_isolated and fabs(el_eta[idx3])>1.5) h_ptE_iso->Fill(var,weight*aweight);

	if (is_isolated) {h_ntracks_iso->Fill(ntrk_prompt+ntrk_nonprompt,weight*aweight); h_ntracks_iso->Fill(-1,weight*aweight);}
        if (!is_isolated) {h_ntracks_anti->Fill(ntrk_prompt+ntrk_nonprompt,weight*aweight); h_ntracks_anti->Fill(-1,weight*aweight);}

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    h_ntracks_iso->Write();
    h_ntracks_anti->Write();

    h_ptB_anti->SetName("pt_antiel_barrel");
    h_ptB_anti->Write();
    h_ptB_iso->SetName("pt_isoel_barrel");
    h_ptB_iso->Write();

    h_ptE_anti->SetName("pt_antiel_endcaps");
    h_ptE_anti->Write();
    h_ptE_iso->SetName("pt_isoel_endcaps");
    h_ptE_iso->Write();

    fout->Close();
} 



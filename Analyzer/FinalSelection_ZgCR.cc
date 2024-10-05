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

    std::string year = *(argv + 1);
    std::string input = *(argv + 2);
    std::string output = *(argv + 3);
    std::string sample = *(argv + 4);
    std::string name = *(argv + 5);

    TFile *f_Double = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    TTree *arbre = (TTree*) f_Double->Get("demo/tree_fr");

    float ngen=0;
    float ngenu=0;
    if (name!="data_obs") {
        TH1F *h_step = (TH1F*) f_Double->Get("demo/step");
	ngen=h_step->GetBinContent(2);
    }

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
    else if (sample=="ZZ4L"){ xs=1.325; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2L2Q"){ xs=3.22; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2Q2L"){ xs=3.22; weight=luminosity*xs/ngen;}
    else if (sample=="WZ3LNu"){ xs=5.213; weight=luminosity*xs/ngen;}
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
    arbre->SetBranchAddress("n_el", &n_el);
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
   arbre->SetBranchAddress("PuppiMET_pt", &PuppiMET_pt);
   arbre->SetBranchAddress("PuppiMET_phi", &PuppiMET_phi);
   arbre->SetBranchAddress("el_conversionveto", &el_conversionveto);
   arbre->SetBranchAddress("el_charge", &el_charge);
   arbre->SetBranchAddress("el_genPart", &el_genPart);
   arbre->SetBranchAddress("el_chargeconsistent", &el_chargeconsistent);
   arbre->SetBranchAddress("el_MVAIDisoWP80", &el_MVAIDisoWP80);
   arbre->SetBranchAddress("el_MVAIDisoWPLoose", &el_MVAIDisoWPLoose);
   arbre->SetBranchAddress("el_pt", &el_pt);
   arbre->SetBranchAddress("el_eta", &el_eta);
   arbre->SetBranchAddress("el_phi", &el_phi);
   arbre->SetBranchAddress("el_dxy", &el_dxy);
   arbre->SetBranchAddress("el_dz", &el_dz);


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

   TFile* f_eleIDSF=new TFile("scalefactors/egammaEffi.txt_Ele_wp80iso_EGM2D.root","read");
   TH2F* h_eleIDSF= (TH2F*) f_eleIDSF->Get("EGamma_SF2D");
   TFile* f_eleRecoSF=new TFile("scalefactors/egammaEffi_ptAbove20.txt_EGM2D_UL2018.root","read");
   TH2F* h_eleRecoSF= (TH2F*) f_eleRecoSF->Get("EGamma_SF2D");
   TFile* f_eleRecoBelowSF=new TFile("scalefactors/egammaEffi_ptBelow20.txt_EGM2D_UL2018.root","read");
   TH2F* h_eleRecoBelowSF= (TH2F*) f_eleRecoBelowSF->Get("EGamma_SF2D");
   // FIXME add other years

   reweight::LumiReWeighting* LumiWeights_12;
   LumiWeights_12 = new reweight::LumiReWeighting("mcPileupUL2018.root", "PileupHistogram-UL2018-100bins_withVar.root", "pu_mc", "pileup");

   TFile *f_mufr=new TFile("output_mufr_2018/mufr.root","read");
   TFile *f_efr=new TFile("output_efr_2018/efr.root","read");
   TH1F* h_mufrB = (TH1F*) f_mufr->Get("mufr_barrel");
   TH1F* h_mufrE = (TH1F*) f_mufr->Get("mufr_endcaps");
   TF1* fit_mufrB = (TF1*) f_mufr->Get("fit_mufr_barrel");
   TF1* fit_mufrE = (TF1*) f_mufr->Get("fit_mufr_endcaps");
   TF1* fit_mufrnt = (TF1*) f_mufr->Get("fit_frnt");
   TH1F* h_efrB = (TH1F*) f_efr->Get("efr_barrel");
   TH1F* h_efrE = (TH1F*) f_efr->Get("efr_endcaps");
   TF1* fit_efrB = (TF1*) f_efr->Get("fit_efr_barrel");
   TF1* fit_efrE = (TF1*) f_efr->Get("fit_efr_endcaps");
   TF1* fit_efrnt = (TF1*) f_efr->Get("fit_frnt");

   TString uncertainties[1]={""};

   std::vector<TH1F*> h0;
   std::vector<TH1F*> h0_anti;
   std::vector<TH1F*> h1;
   std::vector<TH1F*> h1_anti;
   std::vector<TH1F*> h2;
   std::vector<TH1F*> h2_anti;
   std::vector<TH1F*> h3;
   std::vector<TH1F*> h3_anti;
   std::vector<TH1F*> h4;
   std::vector<TH1F*> h4_anti;
   std::vector<TH1F*> h5;
   std::vector<TH1F*> h5_anti;
   std::vector<TH1F*> h6;
   std::vector<TH1F*> h6_anti;
   std::vector<TH1F*> h7;
   std::vector<TH1F*> h7_anti;
   std::vector<TH1F*> h8;
   std::vector<TH1F*> h8_anti;

   int nbhist=1;

   float bins0[] = {0,1,2,3,4,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100};
   float bins1[] = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,85,90,95,100,105,110,115,120};
   float bins2[] = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,85,90,95,100,105,110,115,120};
   float bins3[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};
   float bins4[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};
   float bins5[] = {0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3.0,3.1,3.2,3.3,3.4,3.5,3.6,3.7,3.8,3.9,4.0,4.1,4.2,4.3,4.4,4.5,4.6,4.7,4.8,4.9,5.0};
   float bins6[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100};
   float bins7[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
   float bins8[] = {0,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0};

   int  binnum0 = sizeof(bins0)/sizeof(Float_t) - 1;
   int  binnum1 = sizeof(bins1)/sizeof(Float_t) - 1;
   int  binnum2 = sizeof(bins2)/sizeof(Float_t) - 1;
   int  binnum3 = sizeof(bins3)/sizeof(Float_t) - 1;
   int  binnum4 = sizeof(bins4)/sizeof(Float_t) - 1;
   int  binnum5 = sizeof(bins5)/sizeof(Float_t) - 1;
   int  binnum6 = sizeof(bins6)/sizeof(Float_t) - 1;
   int  binnum7 = sizeof(bins7)/sizeof(Float_t) - 1;
   int  binnum8 = sizeof(bins8)/sizeof(Float_t) - 1;
   for (int k=0; k<nbhist; ++k){
        ostringstream HN0; HN0 << "h0" << k;
        h0.push_back(new TH1F (HN0.str().c_str(),"InvMa",binnum0,bins0)); h0[k]->Sumw2();
        ostringstream HN1; HN1 << "h1" << k;
        h1.push_back(new TH1F (HN1.str().c_str(),"InvMa",binnum1,bins1)); h1[k]->Sumw2();
        ostringstream HN2; HN2 << "h2" << k;
        h2.push_back(new TH1F (HN2.str().c_str(),"InvMa",binnum2,bins2)); h2[k]->Sumw2();
        ostringstream HN3; HN3 << "h3" << k;
        h3.push_back(new TH1F (HN3.str().c_str(),"InvMa",binnum3,bins3)); h3[k]->Sumw2();
        ostringstream HN4; HN4 << "h4" << k;
        h4.push_back(new TH1F (HN4.str().c_str(),"InvMa",binnum4,bins4)); h4[k]->Sumw2();
        ostringstream HN5; HN5 << "h5" << k;
        h5.push_back(new TH1F (HN5.str().c_str(),"InvMa",binnum5,bins5)); h5[k]->Sumw2();
        ostringstream HN6; HN6 << "h6" << k;
        h6.push_back(new TH1F (HN6.str().c_str(),"InvMa",binnum6,bins6)); h6[k]->Sumw2();
        ostringstream HN7; HN7 << "h7" << k;
        h7.push_back(new TH1F (HN7.str().c_str(),"InvMa",binnum7,bins7)); h7[k]->Sumw2();
        ostringstream HN8; HN8 << "h8" << k;
        h8.push_back(new TH1F (HN8.str().c_str(),"InvMa",binnum8,bins8)); h8[k]->Sumw2();

        ostringstream HN0A; HN0A << "h0_anti" << k;
        h0_anti.push_back(new TH1F (HN0A.str().c_str(),"InvMa",binnum0,bins0)); h0_anti[k]->Sumw2();
        ostringstream HN1A; HN1A << "h1_anti" << k;
        h1_anti.push_back(new TH1F (HN1A.str().c_str(),"InvMa",binnum1,bins1)); h1_anti[k]->Sumw2();
        ostringstream HN2A; HN2A << "h2_anti" << k;
        h2_anti.push_back(new TH1F (HN2A.str().c_str(),"InvMa",binnum2,bins2)); h2_anti[k]->Sumw2();
        ostringstream HN3A; HN3A << "h3_anti" << k;
        h3_anti.push_back(new TH1F (HN3A.str().c_str(),"InvMa",binnum3,bins3)); h3_anti[k]->Sumw2();
        ostringstream HN4A; HN4A << "h4_anti" << k;
        h4_anti.push_back(new TH1F (HN4A.str().c_str(),"InvMa",binnum4,bins4)); h4_anti[k]->Sumw2();
        ostringstream HN5A; HN5A << "h5_anti" << k;
        h5_anti.push_back(new TH1F (HN5A.str().c_str(),"InvMa",binnum5,bins5)); h5_anti[k]->Sumw2();
        ostringstream HN6A; HN6A << "h6_anti" << k;
        h6_anti.push_back(new TH1F (HN6A.str().c_str(),"InvMa",binnum6,bins6)); h6_anti[k]->Sumw2();
        ostringstream HN7A; HN7A << "h7_anti" << k;
        h7_anti.push_back(new TH1F (HN7A.str().c_str(),"InvMa",binnum7,bins7)); h7_anti[k]->Sumw2();
        ostringstream HN8A; HN8A << "h8_anti" << k;
        h8_anti.push_back(new TH1F (HN8A.str().c_str(),"InvMa",binnum8,bins8)); h8_anti[k]->Sumw2();
   }

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();

   for (Int_t i = 0; i < nentries_wtn; i++) {
	arbre->LoadTree(i);
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	if (n_mu!=2) continue;
	if (n_el!=1) continue;

	int idx1=-1; int idx2=-1; float best_Zmass=15.000001;
	for (int j=0; j<n_mu-1; ++j){
	   TLorentzVector tmp1;
           tmp1.SetPtEtaPhiM(mu_pt[j], mu_eta[j], mu_phi[j], 0.105);
	   for (int k=j+1; k<n_mu; ++k){
	      TLorentzVector tmp2;
	      tmp2.SetPtEtaPhiM(mu_pt[k], mu_eta[k], mu_phi[k], 0.105);
	      if ((mu_trigger[j] or mu_trigger[k]) and fabs(mu_dz[j])<0.1 and fabs(mu_dz[k])<0.1 and mu_dxy[j]<0.05 and mu_dxy[k]<0.05 and mu_charge[j]*mu_charge[k]<0 and fabs((tmp1+tmp2).M()-91.1876)<best_Zmass and tmp1.DeltaR(tmp2)>0.5 and mu_rawiso[j]<0.25 and mu_rawiso[k]<0.25 and (mu_pt[j]>26 or mu_pt[k]>26) and mu_pt[j]>10 and mu_pt[k]>10){ idx1=j; idx2=k; best_Zmass= fabs((tmp1+tmp2).M()-91.1876);}
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
           if (el_pt[l]>10 and tmp3.DeltaR(my_mu1)>0.3 and tmp3.DeltaR(my_mu2)>0.3 and fabs(el_dz[l])<0.1 and el_dxy[l]<0.05 and idx3<0) idx3=l;
	}
	if (idx3==-1) continue;

        /*if (name!="data_obs"){
	    if (mu_genPart[idx3]==0) continue;
	}*/

	if (!hlt_isomu24) continue;
	//if (!hlt_mu17_mu8) continue;

        // Block weights
        float aweight=1.0;
        if (name!="data_obs"){
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

           aweight=aweight*muidsf_nom1*muisosf_nom2*muidsf_nom1*muisosf_nom2;

           float ept=el_pt[idx3];
           if (ept>120) ept=119;
           float elidsf_nom = h_eleIDSF->GetBinContent(h_eleIDSF->GetXaxis()->FindBin(el_eta[idx3]),h_eleIDSF->GetYaxis()->FindBin(ept));
           float elRecoSF = 1.0;
           if (ept<20) elRecoSF = h_eleRecoBelowSF->GetBinContent(h_eleRecoBelowSF->GetXaxis()->FindBin(el_eta[idx3]),h_eleRecoBelowSF->GetYaxis()->FindBin(ept));
           else elRecoSF = h_eleRecoSF->GetBinContent(h_eleRecoSF->GetXaxis()->FindBin(el_eta[idx3]),h_eleRecoSF->GetYaxis()->FindBin(ept));
           aweight=aweight*elidsf_nom*elRecoSF;


           if (sample=="TTTo2L2Nu" or sample=="TTToSemiLeptonic" or sample=="TTToHadronic") {float toppt_reweighting=pow((TMath::Exp(0.0615-0.0005*gentop_pt)*TMath::Exp(0.0615-0.0005*genantitop_pt)),0.5); aweight*=toppt_reweighting; }
        }

	if (!el_MVAIDisoWPLoose[idx3]) continue;//FIXME
	bool is_isolated=el_MVAIDisoWP80[idx3];

	TLorentzVector mu1; mu1.SetPtEtaPhiM(mu_pt[idx1],mu_eta[idx1],mu_phi[idx1], 0.105);
        TLorentzVector mu2; mu2.SetPtEtaPhiM(mu_pt[idx2],mu_eta[idx2],mu_phi[idx2], 0.105);
        TLorentzVector el1; el1.SetPtEtaPhiM(el_pt[idx3],el_eta[idx3],el_phi[idx3], 0.);

        for (int k=0; k<nbhist; ++k){

           float mt = TMass_F(el1.Pt(), el1.Px(), el1.Py(), PuppiMET_pt, PuppiMET_phi);
           if (mt<60) continue;
	   float mvis=(mu1+el1).M();

           bool is_cat0=(mvis>12);
           bool is_cat1=(mvis>12);
           bool is_cat2=(mvis>12);
           bool is_cat3=(mvis>12);
           bool is_cat4=(mvis>12);
           bool is_cat5=(mvis>12);
           bool is_cat6=(mvis>12);
           bool is_cat7=(mvis>12);
           bool is_cat8=(mvis>12);

           float var0 = ntrk_prompt+ntrk_nonprompt;
           float var1 = mu1.Pt();
           float var2 = el1.Pt();
           float var3 = mu1.Eta();
           float var4 = el1.Eta();
           float var5 = mu1.DeltaR(el1);
           float var6 = PuppiMET_pt;
           float var7 = mt;
           float var8 = 1-fabs(mu1.DeltaPhi(el1))/3.14159;

           if (is_isolated) {
	      if (is_cat0) h0[k]->Fill(var0,weight*aweight);
              if (is_cat1) h1[k]->Fill(var1,weight*aweight);
              if (is_cat2) h2[k]->Fill(var2,weight*aweight);
              if (is_cat3) h3[k]->Fill(var3,weight*aweight);
              if (is_cat4) h4[k]->Fill(var4,weight*aweight);
              if (is_cat5) h5[k]->Fill(var5,weight*aweight);
              if (is_cat6) h6[k]->Fill(var6,weight*aweight);
              if (is_cat7) h7[k]->Fill(var7,weight*aweight);
              if (is_cat8) h8[k]->Fill(var8,weight*aweight);
           }

	   float wfr=1.0;
           float efr=0.0;
           int ntracks=ntrk_prompt+ntrk_nonprompt;
           if (ntracks>80) ntracks=80;
           if (fabs(el1.Eta())<1.5) efr=h_efrB->GetBinContent(h_efrB->GetXaxis()->FindBin(el1.Pt()));
           else efr=h_efrE->GetBinContent(h_efrE->GetXaxis()->FindBin(el1.Pt()));
           efr*=fit_efrnt->Eval(ntracks);
           wfr=efr;


           if (!is_isolated) {
              if (is_cat0) h0_anti[k]->Fill(var0,weight*aweight*wfr);
              if (is_cat1) h1_anti[k]->Fill(var1,weight*aweight*wfr);
              if (is_cat2) h2_anti[k]->Fill(var2,weight*aweight*wfr);
              if (is_cat3) h3_anti[k]->Fill(var3,weight*aweight*wfr);
              if (is_cat4) h4_anti[k]->Fill(var4,weight*aweight*wfr);
              if (is_cat5) h5_anti[k]->Fill(var5,weight*aweight*wfr);
              if (is_cat6) h6_anti[k]->Fill(var6,weight*aweight*wfr);
              if (is_cat7) h7_anti[k]->Fill(var7,weight*aweight*wfr);
              if (is_cat8) h8_anti[k]->Fill(var8,weight*aweight*wfr);
           }
	} // end of nbhist loop over k
    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    bool isMC=(name!="data_obs");
    WriteHistToFileWZCR(fout, h0, name, "wz2mu1ecr_0", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileWZCR(fout, h1, name, "wz2mu1ecr_1", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileWZCR(fout, h2, name, "wz2mu1ecr_2", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileWZCR(fout, h3, name, "wz2mu1ecr_3", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileWZCR(fout, h4, name, "wz2mu1ecr_4", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileWZCR(fout, h5, name, "wz2mu1ecr_5", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileWZCR(fout, h6, name, "wz2mu1ecr_6", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileWZCR(fout, h7, name, "wz2mu1ecr_7", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileWZCR(fout, h8, name, "wz2mu1ecr_8", uncertainties, isMC, nbhist, isMC);

    WriteHistToFileWZCR(fout, h0_anti, name, "wz2mu1ecr_0_anti", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileWZCR(fout, h1_anti, name, "wz2mu1ecr_1_anti", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileWZCR(fout, h2_anti, name, "wz2mu1ecr_2_anti", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileWZCR(fout, h3_anti, name, "wz2mu1ecr_3_anti", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileWZCR(fout, h4_anti, name, "wz2mu1ecr_4_anti", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileWZCR(fout, h5_anti, name, "wz2mu1ecr_5_anti", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileWZCR(fout, h6_anti, name, "wz2mu1ecr_6_anti", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileWZCR(fout, h7_anti, name, "wz2mu1ecr_7_anti", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileWZCR(fout, h8_anti, name, "wz2mu1ecr_8_anti", uncertainties, isMC, nbhist, isMC);

    fout->Close();
} 



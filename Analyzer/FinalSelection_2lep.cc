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
#include "emu_Tree.h"
#include "myHelper.h"
#include "LumiReweightingStandAlone.h"

using namespace std;

int main(int argc, char** argv) {

    int is_control=1;

    std::string year = *(argv + 1);
    std::string input = *(argv + 2);
    std::string output = *(argv + 3);
    std::string sample = *(argv + 4);
    std::string name = *(argv + 5);

    TFile *f_Double = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    TTree *arbre = (TTree*) f_Double->Get("demo/tree_em");

    float ngen=0;
    float ngenu=0;
    if (name!="data_obs") {
        TH1F *h_step = (TH1F*) f_Double->Get("demo/step");
	ngen=h_step->GetBinContent(2);
    }
    if (name=="llscat") {
        TH1F *h_step = (TH1F*) f_Double->Get("demo/step");
        ngen=h_step->GetBinContent(1);
    }

    float xs=1.0; float weight=1.0; float luminosity=59830.0;
    if (year=="2017") luminosity=41480.0;
    if (year=="2016pre") luminosity=19520.0;
    if (year=="2016post") luminosity=16810.0;
    if (sample=="Z" or sample=="DY" or sample=="ZL" or sample=="ZTT" or sample=="ZJ" or sample=="ZLL"){ xs=6077.2; weight=luminosity*xs/ngen;}
    else if (sample=="DYemu"){ xs=0.95*2025.7*(0.178+0.174)*(0.178+0.174); weight=luminosity*xs/ngen;}//FIXME
    else if (sample=="TTTo2L2Nu"){ xs=833.0*0.1061; weight=luminosity*xs/ngen;}
    else if (sample=="TTToSemiLeptonic"){ xs=791*0.4392; weight=luminosity*xs/ngen;}
    else if (sample=="TTToHadronic"){ xs=791*0.4544; weight=luminosity*xs/ngen;}
    else if (sample=="W"){ xs=61527.5; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ4L"){ xs=1.325; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2L2Q"){ xs=3.22; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2Q2L"){ xs=3.22; weight=luminosity*xs/ngen;}
    else if (sample=="WZ3LNu"){ xs=5.056; weight=luminosity*xs/ngen;}
    else if (sample=="VV2L2Nu"){ xs=11.09+0.9738; weight=luminosity*xs/ngen;}
    else if (sample=="WW2L2Nu"){ xs=10.48; weight=luminosity*xs/ngen;}
    else if (sample=="WZ2L2Q"){ xs=6.419; weight=luminosity*xs/ngen;}
    else if (sample=="WZ2Q2L"){ xs=6.419; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2L2Nu"){ xs=0.9738; weight=luminosity*xs/ngen;}
    else if (sample=="WZ"){ xs=47.13; weight=luminosity*xs/ngen;}
    else if (sample=="WZmin0p1"){ xs=58.59; weight=luminosity*xs/ngen;}
    else if (sample=="WW"){ xs=118.7; weight=luminosity*xs/ngen;}
    else if (sample=="TTW"){ xs=0.6105; weight=luminosity*xs/ngen;}
    else if (sample=="TTZ"){ xs=0.77; weight=luminosity*xs/ngen;}
    else if (sample=="TTG"){ xs=3.8; weight=luminosity*xs/ngen;}
    else if (sample=="TG"){ xs=1.018; weight=luminosity*xs/ngen;}
    else if (sample=="WG"){ xs=191.2; weight=luminosity*xs/ngen;}
    else if (sample=="WWG"){ xs=0.2147; weight=luminosity*xs/ngen;}
    else if (sample=="WWW"){ xs=0.2086; weight=luminosity*xs/ngen;}
    else if (sample=="WWDPS"){ xs=0.1729; weight=luminosity*xs/ngen;}
    else if (sample=="ZG"){ xs=173.9; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_top"){ xs=39.65; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_antitop"){ xs=39.65; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_top"){ xs=134.2; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_antitop"){ xs=80.0; weight=luminosity*xs/ngen;}
    else if (sample=="GGTT"){ xs=1.161*0.008735; weight=luminosity*xs/ngen;}
    else if (sample=="GGWW"){ xs=0.00656; weight=luminosity*xs/ngen;} // new 1/137
    else if (sample=="GGEE"){ xs=0.303; weight=luminosity*xs/ngen;}
    else if (sample=="GGMM"){ xs=0.303; weight=luminosity*xs/ngen;}
    else if (name=="data_obs"){ weight=1.0;}
    else if (sample=="GGTT_Ctb20"){ xs=1.048*0.0403; weight=luminosity*xs/ngen;} // new 1/137
    else if (sample=="llscat"){ xs=0.017; weight=luminosity*xs/ngen;}
    else if (sample=="llscat_ptl8"){ xs=0.006; weight=luminosity*xs/ngen;}

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(10);

    arbre->SetBranchAddress("n_mu", &n_mu);
    arbre->SetBranchAddress("n_el", &n_el);
    arbre->SetBranchAddress("hlt_mu8_el23", &hlt_mu8_el23);
    arbre->SetBranchAddress("hlt_mu23_el12", &hlt_mu23_el12);
    arbre->SetBranchAddress("hlt_isomu24", &hlt_isomu24);
    arbre->SetBranchAddress("hlt_mu8_el23_DZ", &hlt_mu8_el23_DZ);
    arbre->SetBranchAddress("hlt_mu23_el12_DZ", &hlt_mu23_el12_DZ);
    arbre->SetBranchAddress("hlt_isotkmu24", &hlt_isotkmu24);
    arbre->SetBranchAddress("hlt_isomu27", &hlt_isomu27);
    arbre->SetBranchAddress("ntrk_prompt", &ntrk_prompt);
    arbre->SetBranchAddress("ntrk_nonprompt", &ntrk_nonprompt);
    arbre->SetBranchAddress("PuppiMET_pt", &PuppiMET_pt);
    arbre->SetBranchAddress("PuppiMET_phi", &PuppiMET_phi);
    arbre->SetBranchAddress("taug2weight", &taug2weight);
    arbre->SetBranchAddress("ntrk_HS", &ntrk_HS);
    arbre->SetBranchAddress("ntrk_signal", &ntrk_signal);
    arbre->SetBranchAddress("ntrk_all", &ntrk_all);
    arbre->SetBranchAddress("ntrk_PU", &ntrk_PU);
    arbre->SetBranchAddress("ntrk0p02_HS", &ntrk0p02_HS);
    arbre->SetBranchAddress("ntrk0p02_signal", &ntrk0p02_signal);
    arbre->SetBranchAddress("ntrk0p02_all", &ntrk0p02_all);
    arbre->SetBranchAddress("ntrk0p02_PU", &ntrk0p02_PU);
    arbre->SetBranchAddress("ntrk0p03_HS", &ntrk0p03_HS);
    arbre->SetBranchAddress("ntrk0p03_signal", &ntrk0p03_signal);
    arbre->SetBranchAddress("ntrk0p03_all", &ntrk0p03_all);
    arbre->SetBranchAddress("ntrk0p03_PU", &ntrk0p03_PU);
    arbre->SetBranchAddress("pv_dz", &pv_dz);

    arbre->SetBranchAddress("el_conversionveto", &el_conversionveto);
    arbre->SetBranchAddress("el_losthits", &el_losthits);
    arbre->SetBranchAddress("mu_trigger23", &mu_trigger23);
    arbre->SetBranchAddress("mu_trigger8", &mu_trigger8);
    arbre->SetBranchAddress("mu_frompv", &mu_frompv);
    arbre->SetBranchAddress("mu_charge", &mu_charge);
    arbre->SetBranchAddress("mu_tight", &mu_tight);
    arbre->SetBranchAddress("mu_genPart", &mu_genPart);
    arbre->SetBranchAddress("mu_rawiso", &mu_rawiso);
    arbre->SetBranchAddress("mu_sip2d", &mu_sip2d);
   arbre->SetBranchAddress("el_charge", &el_charge);
   arbre->SetBranchAddress("el_frompv", &el_frompv);
   arbre->SetBranchAddress("el_genPart", &el_genPart);
   arbre->SetBranchAddress("el_trigger", &el_trigger);
   arbre->SetBranchAddress("el_chargeconsistent", &el_chargeconsistent);
   arbre->SetBranchAddress("el_MVAIDisoWP80", &el_MVAIDisoWP80);
   arbre->SetBranchAddress("el_MVAIDisoWP90", &el_MVAIDisoWP90);
   arbre->SetBranchAddress("el_MVAIDisoWPHZZ", &el_MVAIDisoWPHZZ);
   arbre->SetBranchAddress("el_MVAIDisoWPLoose", &el_MVAIDisoWPLoose);
   arbre->SetBranchAddress("mu_pt", &mu_pt);
   arbre->SetBranchAddress("mu_eta", &mu_eta);
   arbre->SetBranchAddress("mu_phi", &mu_phi);
   arbre->SetBranchAddress("mu_pfiso", &mu_pfiso);
   arbre->SetBranchAddress("mu_dz", &mu_dz);
   arbre->SetBranchAddress("mu_dxy", &mu_dxy);
   arbre->SetBranchAddress("el_pt", &el_pt);
   arbre->SetBranchAddress("el_eta", &el_eta);
   arbre->SetBranchAddress("el_phi", &el_phi);
   arbre->SetBranchAddress("el_dxy", &el_dxy);
   arbre->SetBranchAddress("el_dz", &el_dz);
   arbre->SetBranchAddress("genWeight", &genWeight);
   arbre->SetBranchAddress("gentop_pt", &gentop_pt);
   arbre->SetBranchAddress("genantitop_pt", &genantitop_pt);
   arbre->SetBranchAddress("gentop_eta", &gentop_eta);
   arbre->SetBranchAddress("genantitop_eta", &genantitop_eta);
   arbre->SetBranchAddress("gentop_phi", &gentop_phi);
   arbre->SetBranchAddress("genantitop_phi", &genantitop_phi);
   arbre->SetBranchAddress("Pileup_trueNumInteractions", &Pileup_trueNumInteractions);
   arbre->SetBranchAddress("is_DYtauetaumu", &is_DYtauetaumu);
   arbre->SetBranchAddress("is_ZG", &is_ZG);

   int nbhist=1;

   std::vector<TH1F*> h0;
   std::vector<TH1F*> h0_anti0;
   std::vector<TH1F*> h0_anti1;
   std::vector<TH1F*> h0_anti2;
   std::vector<TH1F*> h1;
   std::vector<TH1F*> h1_anti0;
   std::vector<TH1F*> h1_anti1;
   std::vector<TH1F*> h1_anti2;
   std::vector<TH1F*> h2;
   std::vector<TH1F*> h2_anti0;
   std::vector<TH1F*> h2_anti1;
   std::vector<TH1F*> h2_anti2;
   std::vector<TH1F*> h3;
   std::vector<TH1F*> h3_anti0;
   std::vector<TH1F*> h3_anti1;
   std::vector<TH1F*> h3_anti2;
   std::vector<TH1F*> h4;
   std::vector<TH1F*> h4_anti0;
   std::vector<TH1F*> h4_anti1;
   std::vector<TH1F*> h4_anti2;
   std::vector<TH1F*> h5;
   std::vector<TH1F*> h5_anti0;
   std::vector<TH1F*> h5_anti1;
   std::vector<TH1F*> h5_anti2;
   std::vector<TH1F*> h6;
   std::vector<TH1F*> h6_anti0;
   std::vector<TH1F*> h6_anti1;
   std::vector<TH1F*> h6_anti2;
   std::vector<TH1F*> h7;
   std::vector<TH1F*> h7_anti0;
   std::vector<TH1F*> h7_anti1;
   std::vector<TH1F*> h7_anti2;
   std::vector<TH1F*> h8;
   std::vector<TH1F*> h8_anti0;
   std::vector<TH1F*> h8_anti1;
   std::vector<TH1F*> h8_anti2;

   std::vector<TH1F*> h0R;
   std::vector<TH1F*> h0R_anti0;
   std::vector<TH1F*> h0R_anti1;
   std::vector<TH1F*> h0R_anti2;
   std::vector<TH1F*> h1R;
   std::vector<TH1F*> h1R_anti0;
   std::vector<TH1F*> h1R_anti1;
   std::vector<TH1F*> h1R_anti2;
   std::vector<TH1F*> h2R;
   std::vector<TH1F*> h2R_anti0;
   std::vector<TH1F*> h2R_anti1;
   std::vector<TH1F*> h2R_anti2;
   std::vector<TH1F*> h3R;
   std::vector<TH1F*> h3R_anti0;
   std::vector<TH1F*> h3R_anti1;
   std::vector<TH1F*> h3R_anti2;
   std::vector<TH1F*> h4R;
   std::vector<TH1F*> h4R_anti0;
   std::vector<TH1F*> h4R_anti1;
   std::vector<TH1F*> h4R_anti2;
   std::vector<TH1F*> h5R;
   std::vector<TH1F*> h5R_anti0;
   std::vector<TH1F*> h5R_anti1;
   std::vector<TH1F*> h5R_anti2;
   std::vector<TH1F*> h6R;
   std::vector<TH1F*> h6R_anti0;
   std::vector<TH1F*> h6R_anti1;
   std::vector<TH1F*> h6R_anti2;
   std::vector<TH1F*> h7R;
   std::vector<TH1F*> h7R_anti0;
   std::vector<TH1F*> h7R_anti1;
   std::vector<TH1F*> h7R_anti2;
   std::vector<TH1F*> h8R;
   std::vector<TH1F*> h8R_anti0;
   std::vector<TH1F*> h8R_anti1;
   std::vector<TH1F*> h8R_anti2;

   std::vector<TH1F*> h0OS;
   std::vector<TH1F*> h1OS;
   std::vector<TH1F*> h2OS;
   std::vector<TH1F*> h3OS;
   std::vector<TH1F*> h4OS;
   std::vector<TH1F*> h5OS;
   std::vector<TH1F*> h6OS;
   std::vector<TH1F*> h7OS;
   std::vector<TH1F*> h8OS;

   // Control 0
   /*float bins0[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80};
   float bins1[] = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,85,90,95,100,105,110,115,120};
   float bins2[] = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,85,90,95,100,105,110,115,120};
   float bins3[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};
   float bins4[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};
   float bins5[] = {0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3.0,3.1,3.2,3.3,3.4,3.5,3.6,3.7,3.8,3.9,4.0,4.1,4.2,4.3,4.4,4.5,4.6,4.7,4.8,4.9,5.0};
   float bins6[] = {0,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0};
   float bins7[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
   float bins8[] = {0,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0};*/


   // Control 1
   float bins0[] = {0,0.1,0.20,0.4,0.6,0.8,1.0};
   float bins1[] = {0,0.1,0.20,0.4,0.6,0.8,1.0};
   float bins2[] = {0,0.1,0.20,0.4,0.6,0.8,1.0};
   float bins3[] = {0,0.1,0.20,0.4,0.6,0.8,1.0};
   float bins4[] = {0,1,2,3,4,5,6,7,8,9,10};
   float bins5[] = {0,1,2,3,4,5,6,7,8,9,10};
   float bins6[] = {0,0.1,0.20,0.4,0.6,0.8,1.0};
   float bins7[] = {0,0.1,0.20,0.4,0.6,0.8,1.0};
   float bins8[] = {0,0.1,0.20,0.4,0.6,0.8,1.0};

   
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

        ostringstream HN0OS; HN0OS << "h0OS" << k;
        h0OS.push_back(new TH1F (HN0OS.str().c_str(),"InvMa",binnum0,bins0)); h0OS[k]->Sumw2();
        ostringstream HN1OS; HN1OS << "h1OS" << k;
        h1OS.push_back(new TH1F (HN1OS.str().c_str(),"InvMa",binnum1,bins1)); h1OS[k]->Sumw2();
        ostringstream HN2OS; HN2OS << "h2OS" << k;
        h2OS.push_back(new TH1F (HN2OS.str().c_str(),"InvMa",binnum2,bins2)); h2OS[k]->Sumw2();
        ostringstream HN3OS; HN3OS << "h3OS" << k;
        h3OS.push_back(new TH1F (HN3OS.str().c_str(),"InvMa",binnum3,bins3)); h3OS[k]->Sumw2();
        ostringstream HN4OS; HN4OS << "h4OS" << k;
        h4OS.push_back(new TH1F (HN4OS.str().c_str(),"InvMa",binnum4,bins4)); h4OS[k]->Sumw2();
        ostringstream HN5OS; HN5OS << "h5OS" << k;
        h5OS.push_back(new TH1F (HN5OS.str().c_str(),"InvMa",binnum5,bins5)); h5OS[k]->Sumw2();
        ostringstream HN6OS; HN6OS << "h6OS" << k;
        h6OS.push_back(new TH1F (HN6OS.str().c_str(),"InvMa",binnum6,bins6)); h6OS[k]->Sumw2();
        ostringstream HN7OS; HN7OS << "h7OS" << k;
        h7OS.push_back(new TH1F (HN7OS.str().c_str(),"InvMa",binnum7,bins7)); h7OS[k]->Sumw2();
        ostringstream HN8OS; HN8OS << "h8OS" << k;
        h8OS.push_back(new TH1F (HN8OS.str().c_str(),"InvMa",binnum8,bins8)); h8OS[k]->Sumw2();

        ostringstream HN0R; HN0R << "h0R" << k;
        h0R.push_back(new TH1F (HN0R.str().c_str(),"InvMa",binnum0,bins0)); h0R[k]->Sumw2();
        ostringstream HN1R; HN1R << "h1R" << k;
        h1R.push_back(new TH1F (HN1R.str().c_str(),"InvMa",binnum1,bins1)); h1R[k]->Sumw2();
        ostringstream HN2R; HN2R << "h2R" << k;
        h2R.push_back(new TH1F (HN2R.str().c_str(),"InvMa",binnum2,bins2)); h2R[k]->Sumw2();
        ostringstream HN3R; HN3R << "h3R" << k;
        h3R.push_back(new TH1F (HN3R.str().c_str(),"InvMa",binnum3,bins3)); h3R[k]->Sumw2();
        ostringstream HN4R; HN4R << "h4R" << k;
        h4R.push_back(new TH1F (HN4R.str().c_str(),"InvMa",binnum4,bins4)); h4R[k]->Sumw2();
        ostringstream HN5R; HN5R << "h5R" << k;
        h5R.push_back(new TH1F (HN5R.str().c_str(),"InvMa",binnum5,bins5)); h5R[k]->Sumw2();
        ostringstream HN6R; HN6R << "h6R" << k;
        h6R.push_back(new TH1F (HN6R.str().c_str(),"InvMa",binnum6,bins6)); h6R[k]->Sumw2();
        ostringstream HN7R; HN7R << "h7R" << k;
        h7R.push_back(new TH1F (HN7R.str().c_str(),"InvMa",binnum7,bins7)); h7R[k]->Sumw2();
        ostringstream HN8R; HN8R << "h8R" << k;
        h8R.push_back(new TH1F (HN8R.str().c_str(),"InvMa",binnum8,bins8)); h8R[k]->Sumw2();

        ostringstream HN0_anti0; HN0_anti0 << "h0_anti0" << k;
        h0_anti0.push_back(new TH1F (HN0_anti0.str().c_str(),"InvMa",binnum0,bins0)); h0_anti0[k]->Sumw2();
        ostringstream HN1_anti0; HN1_anti0 << "h1_anti0" << k;
        h1_anti0.push_back(new TH1F (HN1_anti0.str().c_str(),"InvMa",binnum1,bins1)); h1_anti0[k]->Sumw2();
        ostringstream HN2_anti0; HN2_anti0 << "h2_anti0" << k;
        h2_anti0.push_back(new TH1F (HN2_anti0.str().c_str(),"InvMa",binnum2,bins2)); h2_anti0[k]->Sumw2();
        ostringstream HN3_anti0; HN3_anti0 << "h3_anti0" << k;
        h3_anti0.push_back(new TH1F (HN3_anti0.str().c_str(),"InvMa",binnum3,bins3)); h3_anti0[k]->Sumw2();
        ostringstream HN4_anti0; HN4_anti0 << "h4_anti0" << k;
        h4_anti0.push_back(new TH1F (HN4_anti0.str().c_str(),"InvMa",binnum4,bins4)); h4_anti0[k]->Sumw2();
        ostringstream HN5_anti0; HN5_anti0 << "h5_anti0" << k;
        h5_anti0.push_back(new TH1F (HN5_anti0.str().c_str(),"InvMa",binnum5,bins5)); h5_anti0[k]->Sumw2();
        ostringstream HN6_anti0; HN6_anti0 << "h6_anti0" << k;
        h6_anti0.push_back(new TH1F (HN6_anti0.str().c_str(),"InvMa",binnum6,bins6)); h6_anti0[k]->Sumw2();
        ostringstream HN7_anti0; HN7_anti0 << "h7_anti0" << k;
        h7_anti0.push_back(new TH1F (HN7_anti0.str().c_str(),"InvMa",binnum7,bins7)); h7_anti0[k]->Sumw2();
        ostringstream HN8_anti0; HN8_anti0 << "h8_anti0" << k;
        h8_anti0.push_back(new TH1F (HN8_anti0.str().c_str(),"InvMa",binnum8,bins8)); h8_anti0[k]->Sumw2();

        ostringstream HN0R_anti0; HN0R_anti0 << "h0R_anti0" << k;
        h0R_anti0.push_back(new TH1F (HN0R_anti0.str().c_str(),"InvMa",binnum0,bins0)); h0R_anti0[k]->Sumw2();
        ostringstream HN1R_anti0; HN1R_anti0 << "h1R_anti0" << k;
        h1R_anti0.push_back(new TH1F (HN1R_anti0.str().c_str(),"InvMa",binnum1,bins1)); h1R_anti0[k]->Sumw2();
        ostringstream HN2R_anti0; HN2R_anti0 << "h2R_anti0" << k;
        h2R_anti0.push_back(new TH1F (HN2R_anti0.str().c_str(),"InvMa",binnum2,bins2)); h2R_anti0[k]->Sumw2();
        ostringstream HN3R_anti0; HN3R_anti0 << "h3R_anti0" << k;
        h3R_anti0.push_back(new TH1F (HN3R_anti0.str().c_str(),"InvMa",binnum3,bins3)); h3R_anti0[k]->Sumw2();
        ostringstream HN4R_anti0; HN4R_anti0 << "h4R_anti0" << k;
        h4R_anti0.push_back(new TH1F (HN4R_anti0.str().c_str(),"InvMa",binnum4,bins4)); h4R_anti0[k]->Sumw2();
        ostringstream HN5R_anti0; HN5R_anti0 << "h5R_anti0" << k;
        h5R_anti0.push_back(new TH1F (HN5R_anti0.str().c_str(),"InvMa",binnum5,bins5)); h5R_anti0[k]->Sumw2();
        ostringstream HN6R_anti0; HN6R_anti0 << "h6R_anti0" << k;
        h6R_anti0.push_back(new TH1F (HN6R_anti0.str().c_str(),"InvMa",binnum6,bins6)); h6R_anti0[k]->Sumw2();
        ostringstream HN7R_anti0; HN7R_anti0 << "h7R_anti0" << k;
        h7R_anti0.push_back(new TH1F (HN7R_anti0.str().c_str(),"InvMa",binnum7,bins7)); h7R_anti0[k]->Sumw2();
        ostringstream HN8R_anti0; HN8R_anti0 << "h8R_anti0" << k;
        h8R_anti0.push_back(new TH1F (HN8R_anti0.str().c_str(),"InvMa",binnum8,bins8)); h8R_anti0[k]->Sumw2();

        ostringstream HN0_anti1; HN0_anti1 << "h0_anti1" << k;
        h0_anti1.push_back(new TH1F (HN0_anti1.str().c_str(),"InvMa",binnum0,bins0)); h0_anti1[k]->Sumw2();
        ostringstream HN1_anti1; HN1_anti1 << "h1_anti1" << k;
        h1_anti1.push_back(new TH1F (HN1_anti1.str().c_str(),"InvMa",binnum1,bins1)); h1_anti1[k]->Sumw2();
        ostringstream HN2_anti1; HN2_anti1 << "h2_anti1" << k;
        h2_anti1.push_back(new TH1F (HN2_anti1.str().c_str(),"InvMa",binnum2,bins2)); h2_anti1[k]->Sumw2();
        ostringstream HN3_anti1; HN3_anti1 << "h3_anti1" << k;
        h3_anti1.push_back(new TH1F (HN3_anti1.str().c_str(),"InvMa",binnum3,bins3)); h3_anti1[k]->Sumw2();
        ostringstream HN4_anti1; HN4_anti1 << "h4_anti1" << k;
        h4_anti1.push_back(new TH1F (HN4_anti1.str().c_str(),"InvMa",binnum4,bins4)); h4_anti1[k]->Sumw2();
        ostringstream HN5_anti1; HN5_anti1 << "h5_anti1" << k;
        h5_anti1.push_back(new TH1F (HN5_anti1.str().c_str(),"InvMa",binnum5,bins5)); h5_anti1[k]->Sumw2();
        ostringstream HN6_anti1; HN6_anti1 << "h6_anti1" << k;
        h6_anti1.push_back(new TH1F (HN6_anti1.str().c_str(),"InvMa",binnum6,bins6)); h6_anti1[k]->Sumw2();
        ostringstream HN7_anti1; HN7_anti1 << "h7_anti1" << k;
        h7_anti1.push_back(new TH1F (HN7_anti1.str().c_str(),"InvMa",binnum7,bins7)); h7_anti1[k]->Sumw2();
        ostringstream HN8_anti1; HN8_anti1 << "h8_anti1" << k;
        h8_anti1.push_back(new TH1F (HN8_anti1.str().c_str(),"InvMa",binnum8,bins8)); h8_anti1[k]->Sumw2();

        ostringstream HN0R_anti1; HN0R_anti1 << "h0R_anti1" << k;
        h0R_anti1.push_back(new TH1F (HN0R_anti1.str().c_str(),"InvMa",binnum0,bins0)); h0R_anti1[k]->Sumw2();
        ostringstream HN1R_anti1; HN1R_anti1 << "h1R_anti1" << k;
        h1R_anti1.push_back(new TH1F (HN1R_anti1.str().c_str(),"InvMa",binnum1,bins1)); h1R_anti1[k]->Sumw2();
        ostringstream HN2R_anti1; HN2R_anti1 << "h2R_anti1" << k;
        h2R_anti1.push_back(new TH1F (HN2R_anti1.str().c_str(),"InvMa",binnum2,bins2)); h2R_anti1[k]->Sumw2();
        ostringstream HN3R_anti1; HN3R_anti1 << "h3R_anti1" << k;
        h3R_anti1.push_back(new TH1F (HN3R_anti1.str().c_str(),"InvMa",binnum3,bins3)); h3R_anti1[k]->Sumw2();
        ostringstream HN4R_anti1; HN4R_anti1 << "h4R_anti1" << k;
        h4R_anti1.push_back(new TH1F (HN4R_anti1.str().c_str(),"InvMa",binnum4,bins4)); h4R_anti1[k]->Sumw2();
        ostringstream HN5R_anti1; HN5R_anti1 << "h5R_anti1" << k;
        h5R_anti1.push_back(new TH1F (HN5R_anti1.str().c_str(),"InvMa",binnum5,bins5)); h5R_anti1[k]->Sumw2();
        ostringstream HN6R_anti1; HN6R_anti1 << "h6R_anti1" << k;
        h6R_anti1.push_back(new TH1F (HN6R_anti1.str().c_str(),"InvMa",binnum6,bins6)); h6R_anti1[k]->Sumw2();
        ostringstream HN7R_anti1; HN7R_anti1 << "h7R_anti1" << k;
        h7R_anti1.push_back(new TH1F (HN7R_anti1.str().c_str(),"InvMa",binnum7,bins7)); h7R_anti1[k]->Sumw2();
        ostringstream HN8R_anti1; HN8R_anti1 << "h8R_anti1" << k;
        h8R_anti1.push_back(new TH1F (HN8R_anti1.str().c_str(),"InvMa",binnum8,bins8)); h8R_anti1[k]->Sumw2();

        ostringstream HN0_anti2; HN0_anti2 << "h0_anti2" << k;
        h0_anti2.push_back(new TH1F (HN0_anti2.str().c_str(),"InvMa",binnum0,bins0)); h0_anti2[k]->Sumw2();
        ostringstream HN1_anti2; HN1_anti2 << "h1_anti2" << k;
        h1_anti2.push_back(new TH1F (HN1_anti2.str().c_str(),"InvMa",binnum1,bins1)); h1_anti2[k]->Sumw2();
        ostringstream HN2_anti2; HN2_anti2 << "h2_anti2" << k;
        h2_anti2.push_back(new TH1F (HN2_anti2.str().c_str(),"InvMa",binnum2,bins2)); h2_anti2[k]->Sumw2();
        ostringstream HN3_anti2; HN3_anti2 << "h3_anti2" << k;
        h3_anti2.push_back(new TH1F (HN3_anti2.str().c_str(),"InvMa",binnum3,bins3)); h3_anti2[k]->Sumw2();
        ostringstream HN4_anti2; HN4_anti2 << "h4_anti2" << k;
        h4_anti2.push_back(new TH1F (HN4_anti2.str().c_str(),"InvMa",binnum4,bins4)); h4_anti2[k]->Sumw2();
        ostringstream HN5_anti2; HN5_anti2 << "h5_anti2" << k;
        h5_anti2.push_back(new TH1F (HN5_anti2.str().c_str(),"InvMa",binnum5,bins5)); h5_anti2[k]->Sumw2();
        ostringstream HN6_anti2; HN6_anti2 << "h6_anti2" << k;
        h6_anti2.push_back(new TH1F (HN6_anti2.str().c_str(),"InvMa",binnum6,bins6)); h6_anti2[k]->Sumw2();
        ostringstream HN7_anti2; HN7_anti2 << "h7_anti2" << k;
        h7_anti2.push_back(new TH1F (HN7_anti2.str().c_str(),"InvMa",binnum7,bins7)); h7_anti2[k]->Sumw2();
        ostringstream HN8_anti2; HN8_anti2 << "h8_anti2" << k;
        h8_anti2.push_back(new TH1F (HN8_anti2.str().c_str(),"InvMa",binnum8,bins8)); h8_anti2[k]->Sumw2();

        ostringstream HN0R_anti2; HN0R_anti2 << "h0R_anti2" << k;
        h0R_anti2.push_back(new TH1F (HN0R_anti2.str().c_str(),"InvMa",binnum0,bins0)); h0R_anti2[k]->Sumw2();
        ostringstream HN1R_anti2; HN1R_anti2 << "h1R_anti2" << k;
        h1R_anti2.push_back(new TH1F (HN1R_anti2.str().c_str(),"InvMa",binnum1,bins1)); h1R_anti2[k]->Sumw2();
        ostringstream HN2R_anti2; HN2R_anti2 << "h2R_anti2" << k;
        h2R_anti2.push_back(new TH1F (HN2R_anti2.str().c_str(),"InvMa",binnum2,bins2)); h2R_anti2[k]->Sumw2();
        ostringstream HN3R_anti2; HN3R_anti2 << "h3R_anti2" << k;
        h3R_anti2.push_back(new TH1F (HN3R_anti2.str().c_str(),"InvMa",binnum3,bins3)); h3R_anti2[k]->Sumw2();
        ostringstream HN4R_anti2; HN4R_anti2 << "h4R_anti2" << k;
        h4R_anti2.push_back(new TH1F (HN4R_anti2.str().c_str(),"InvMa",binnum4,bins4)); h4R_anti2[k]->Sumw2();
        ostringstream HN5R_anti2; HN5R_anti2 << "h5R_anti2" << k;
        h5R_anti2.push_back(new TH1F (HN5R_anti2.str().c_str(),"InvMa",binnum5,bins5)); h5R_anti2[k]->Sumw2();
        ostringstream HN6R_anti2; HN6R_anti2 << "h6R_anti2" << k;
        h6R_anti2.push_back(new TH1F (HN6R_anti2.str().c_str(),"InvMa",binnum6,bins6)); h6R_anti2[k]->Sumw2();
        ostringstream HN7R_anti2; HN7R_anti2 << "h7R_anti2" << k;
        h7R_anti2.push_back(new TH1F (HN7R_anti2.str().c_str(),"InvMa",binnum7,bins7)); h7R_anti2[k]->Sumw2();
        ostringstream HN8R_anti2; HN8R_anti2 << "h8R_anti2" << k;
        h8R_anti2.push_back(new TH1F (HN8R_anti2.str().c_str(),"InvMa",binnum8,bins8)); h8R_anti2[k]->Sumw2();

   }

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
   TFile* f_muonTrg=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2018_UL_SingleMuonTriggers.root","read");
   TH2F* h_muonTrgSF= (TH2F*) f_muonTrg->Get("NUM_IsoMu24_DEN_CutBasedIdMedium_and_PFIsoMedium_abseta_pt");

   if (year=="2016pre"){
      TFile* f_muonID=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2016_UL_HIPM_ID.root","read");
      TFile* f_muonIso=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2016_UL_HIPM_ISO.root","read");
      h_muonIsoSF= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt");
      h_muonIDSF= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt");
      h_muonIsoSF_stat= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt_stat");
      h_muonIDSF_stat= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt_stat");
      h_muonIsoSF_syst= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt_syst");
      h_muonIDSF_syst= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt_syst");
      TFile* f_muonTrg=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2016_UL_HIPM_SingleMuonTriggers.root","read");
      h_muonTrgSF= (TH2F*) f_muonTrg->Get("NUM_IsoMu24_or_IsoTkMu24_DEN_CutBasedIdMedium_and_PFIsoMedium_abseta_pt");
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
      TFile* f_muonTrg=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2016_UL_SingleMuonTriggers.root","read");
      h_muonTrgSF= (TH2F*) f_muonTrg->Get("NUM_IsoMu24_or_IsoTkMu24_DEN_CutBasedIdMedium_and_PFIsoMedium_abseta_pt");
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
      TFile* f_muonTrg=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2017_UL_SingleMuonTriggers.root","read");
      h_muonTrgSF= (TH2F*) f_muonTrg->Get("NUM_IsoMu27_DEN_CutBasedIdMedium_and_PFIsoMedium_abseta_pt");
   }

   TFile* f_e_trg24_c=new TFile("scalefactors/sf_el_2018_HLTMu8Ele23.root","read");
   TFile* f_e_trg12_c=new TFile("scalefactors/sf_el_2018_HLTMu23Ele12.root","read");
   TFile* f_mu_trg24_c=new TFile("scalefactors/sf_mu_2018_HLTMu23Ele12.root","read");
   TFile* f_mu_trg8_c=new TFile("scalefactors/sf_mu_2018_HLTMu8Ele23.root","read");
   TH2F* h_mu_trg24_data_c= (TH2F*) f_mu_trg24_c->Get("eff_data");
   TH2F* h_mu_trg24_zll_c= (TH2F*) f_mu_trg24_c->Get("eff_mc");
   TH2F* h_mu_trg8_data_c= (TH2F*) f_mu_trg8_c->Get("eff_data");
   TH2F* h_mu_trg8_zll_c= (TH2F*) f_mu_trg8_c->Get("eff_mc");
   TH2F* h_e_trg24_data_c= (TH2F*) f_e_trg24_c->Get("eff_data");
   TH2F* h_e_trg24_zll_c= (TH2F*) f_e_trg24_c->Get("eff_mc");
   TH2F* h_e_trg12_data_c= (TH2F*) f_e_trg12_c->Get("eff_data");
   TH2F* h_e_trg12_zll_c= (TH2F*) f_e_trg12_c->Get("eff_mc");
   if (year=="2017"){
      TFile* f_e_trg24_c=new TFile("scalefactors/sf_el_2017_HLTMu8Ele23.root","read");
      TFile* f_e_trg12_c=new TFile("scalefactors/sf_el_2017_HLTMu23Ele12.root","read");
      TFile* f_mu_trg24_c=new TFile("scalefactors/sf_mu_2017_HLTMu23Ele12.root","read");
      TFile* f_mu_trg8_c=new TFile("scalefactors/sf_mu_2017_HLTMu8Ele23.root","read");
      h_mu_trg24_data_c= (TH2F*) f_mu_trg24_c->Get("eff_data");
      h_mu_trg24_zll_c= (TH2F*) f_mu_trg24_c->Get("eff_mc");
      h_mu_trg8_data_c= (TH2F*) f_mu_trg8_c->Get("eff_data");
      h_mu_trg8_zll_c= (TH2F*) f_mu_trg8_c->Get("eff_mc");
      h_e_trg24_data_c= (TH2F*) f_e_trg24_c->Get("eff_data");
      h_e_trg24_zll_c= (TH2F*) f_e_trg24_c->Get("eff_mc");
      h_e_trg12_data_c= (TH2F*) f_e_trg12_c->Get("eff_data");
      h_e_trg12_zll_c= (TH2F*) f_e_trg12_c->Get("eff_mc");
   }
   else if (year=="2016post"){
      TFile* f_e_trg24_c=new TFile("scalefactors/sf_el_2016post_HLTMu8Ele23.root","read");
      TFile* f_e_trg12_c=new TFile("scalefactors/sf_el_2016post_HLTMu23Ele12.root","read");
      TFile* f_mu_trg24_c=new TFile("scalefactors/sf_mu_2016post_HLTMu23Ele12.root","read");
      TFile* f_mu_trg8_c=new TFile("scalefactors/sf_mu_2016post_HLTMu8Ele23.root","read");
      h_mu_trg24_data_c= (TH2F*) f_mu_trg24_c->Get("eff_data");
      h_mu_trg24_zll_c= (TH2F*) f_mu_trg24_c->Get("eff_mc");
      h_mu_trg8_data_c= (TH2F*) f_mu_trg8_c->Get("eff_data");
      h_mu_trg8_zll_c= (TH2F*) f_mu_trg8_c->Get("eff_mc");
      h_e_trg24_data_c= (TH2F*) f_e_trg24_c->Get("eff_data");
      h_e_trg24_zll_c= (TH2F*) f_e_trg24_c->Get("eff_mc");
      h_e_trg12_data_c= (TH2F*) f_e_trg12_c->Get("eff_data");
      h_e_trg12_zll_c= (TH2F*) f_e_trg12_c->Get("eff_mc");
   }
   else if (year=="2016pre"){
      TFile* f_e_trg24_c=new TFile("scalefactors/sf_el_2016pre_HLTMu8Ele23.root","read");
      TFile* f_e_trg12_c=new TFile("scalefactors/sf_el_2016pre_HLTMu23Ele12.root","read");
      TFile* f_mu_trg24_c=new TFile("scalefactors/sf_mu_2016pre_HLTMu23Ele12.root","read");
      TFile* f_mu_trg8_c=new TFile("scalefactors/sf_mu_2016pre_HLTMu8Ele23.root","read");
      h_mu_trg24_data_c= (TH2F*) f_mu_trg24_c->Get("eff_data");
      h_mu_trg24_zll_c= (TH2F*) f_mu_trg24_c->Get("eff_mc");
      h_mu_trg8_data_c= (TH2F*) f_mu_trg8_c->Get("eff_data");
      h_mu_trg8_zll_c= (TH2F*) f_mu_trg8_c->Get("eff_mc");
      h_e_trg24_data_c= (TH2F*) f_e_trg24_c->Get("eff_data");
      h_e_trg24_zll_c= (TH2F*) f_e_trg24_c->Get("eff_mc");
      h_e_trg12_data_c= (TH2F*) f_e_trg12_c->Get("eff_data");
      h_e_trg12_zll_c= (TH2F*) f_e_trg12_c->Get("eff_mc");
   }

   reweight::LumiReWeighting* LumiWeights_12;
   LumiWeights_12 = new reweight::LumiReWeighting("mcPileupUL2018.root", "PileupHistogram-UL2018-100bins_withVar.root", "pu_mc", "pileup");
   if (year=="2017"){
      LumiWeights_12 = new reweight::LumiReWeighting("mcPileupUL2017.root", "PileupHistogram-UL2017-100bins_withVar.root", "pu_mc", "pileup");
   }
   else if (year=="2016pre" or year=="2016post"){
      LumiWeights_12 = new reweight::LumiReWeighting("mcPileupUL2016.root", "PileupHistogram-UL2016-100bins_withVar.root", "pu_mc", "pileup");
   }

   //TFile *f_mufr=new TFile("output_mufr_2018/mufr.root","read");
   TFile *f_mufr=new TFile("output_mufr_eem_2018/mufr_eem.root","read");
   TFile *f_efr=new TFile("output_efr_2018/efr_emm.root","read");
   TH1F* h_mufrB = (TH1F*) f_mufr->Get("mufr_barrel");
   TH1F* h_mufrE = (TH1F*) f_mufr->Get("mufr_endcaps");
   TF1* fit_mufrB = (TF1*) f_mufr->Get("fit_pt_isomu_emutrg_barrel");
   TF1* fit_mufrE = (TF1*) f_mufr->Get("fit_pt_isomu_emutrg_endcaps");
   //TF1* fit_mufrB = (TF1*) f_mufr->Get("fit_mufr_barrel");
   //TF1* fit_mufrE = (TF1*) f_mufr->Get("fit_mufr_endcaps");
   //TF1* fit_mufrB = (TF1*) f_mufr->Get("fit_mufr2_barrel");
   //TF1* fit_mufrE = (TF1*) f_mufr->Get("fit_mufr2_endcaps");
   TF1* fit_mufrnt = (TF1*) f_mufr->Get("fit_frnt");
   TH1F* h_efrB = (TH1F*) f_efr->Get("efr_barrel");
   TH1F* h_efrE = (TH1F*) f_efr->Get("efr_endcaps");
   //TF1* fit_efrB = (TF1*) f_efr->Get("fit_efr_barrel");
   //TF1* fit_efrE = (TF1*) f_efr->Get("fit_efr_endcaps");
   TF1* fit_efrB = (TF1*) f_efr->Get("fit_pt_isoel_singlemutrg_barrel");
   TF1* fit_efrE = (TF1*) f_efr->Get("fit_pt_isoel_singlemutrg_endcaps");
   TF1* fit_efrB_notrg = (TF1*) f_efr->Get("fit_pt_isoel_singlemutrg_barrel");
   TF1* fit_efrE_notrg = (TF1*) f_efr->Get("fit_pt_isoel_singlemutrg_endcaps");
   TF1* fit_efrB_emutrg = (TF1*) f_efr->Get("fit_pt_isoel_emutrg_barrel");
   TF1* fit_efrE_emutrg = (TF1*) f_efr->Get("fit_pt_isoel_emutrg_endcaps");
   TF1* fit_efrnt = (TF1*) f_efr->Get("fit_frnt");

   if (year=="2016pre"){
      TFile *f_mufr=new TFile("output_mufr_2016pre/mufr.root","read");
      TFile *f_efr=new TFile("output_efr_2016pre/efr.root","read");
      h_mufrB = (TH1F*) f_mufr->Get("mufr_barrel");
      h_mufrE = (TH1F*) f_mufr->Get("mufr_endcaps");
      fit_mufrB = (TF1*) f_mufr->Get("fit_mufr_barrel");
      fit_mufrE = (TF1*) f_mufr->Get("fit_mufr_endcaps");
      fit_mufrnt = (TF1*) f_mufr->Get("fit_frnt");
      h_efrB = (TH1F*) f_efr->Get("efr_barrel");
      h_efrE = (TH1F*) f_efr->Get("efr_endcaps");
      fit_efrB = (TF1*) f_efr->Get("fit_efr_barrel");
      fit_efrE = (TF1*) f_efr->Get("fit_efr_endcaps");
      fit_efrnt = (TF1*) f_efr->Get("fit_frnt");
   }
   if (year=="2016post"){
      TFile *f_mufr=new TFile("output_mufr_2016post/mufr.root","read");
      TFile *f_efr=new TFile("output_efr_2016post/efr.root","read");
      h_mufrB = (TH1F*) f_mufr->Get("mufr_barrel");
      h_mufrE = (TH1F*) f_mufr->Get("mufr_endcaps");
      fit_mufrB = (TF1*) f_mufr->Get("fit_mufr_barrel");
      fit_mufrE = (TF1*) f_mufr->Get("fit_mufr_endcaps");
      fit_mufrnt = (TF1*) f_mufr->Get("fit_frnt");
      h_efrB = (TH1F*) f_efr->Get("efr_barrel");
      h_efrE = (TH1F*) f_efr->Get("efr_endcaps");
      fit_efrB = (TF1*) f_efr->Get("fit_efr_barrel");
      fit_efrE = (TF1*) f_efr->Get("fit_efr_endcaps");
      fit_efrnt = (TF1*) f_efr->Get("fit_frnt");
   }
   if (year=="2017"){
      TFile *f_mufr=new TFile("output_mufr_2017/mufr.root","read");
      TFile *f_efr=new TFile("output_efr_2017/efr.root","read");
      h_mufrB = (TH1F*) f_mufr->Get("mufr_barrel");
      h_mufrE = (TH1F*) f_mufr->Get("mufr_endcaps");
      fit_mufrB = (TF1*) f_mufr->Get("fit_mufr_barrel");
      fit_mufrE = (TF1*) f_mufr->Get("fit_mufr_endcaps");
      fit_mufrnt = (TF1*) f_mufr->Get("fit_frnt");
      h_efrB = (TH1F*) f_efr->Get("efr_barrel");
      h_efrE = (TH1F*) f_efr->Get("efr_endcaps");
      fit_efrB = (TF1*) f_efr->Get("fit_efr_barrel");
      fit_efrE = (TF1*) f_efr->Get("fit_efr_endcaps");
      fit_efrnt = (TF1*) f_efr->Get("fit_frnt");
   }


   TFile* f_ptbalance=new TFile("correction_ptbalance_2018.root","read");
   TF1* fit_ptbalance = (TF1*) f_ptbalance->Get("fit_ptbalance");

   TFile *f_punt=new TFile("corrs_ntracks_pu_UL2018.root");
   TH2F* correction_map=(TH2F*) f_punt->Get("corr_raw");
   if (year=="2017"){
     TFile *f_punt=new TFile("corrs_ntracks_pu_UL2017.root");
     correction_map=(TH2F*) f_punt->Get("corr_raw");
   }
   else if (year=="2016post"){
     TFile *f_punt=new TFile("corrs_ntracks_pu_UL2016_postVFP.root");
     correction_map=(TH2F*) f_punt->Get("corr_raw");
   }
   else if (year=="2016pre"){
     TFile *f_punt=new TFile("corrs_ntracks_pu_UL2016_preVFP.root");
     correction_map=(TH2F*) f_punt->Get("corr_raw");
   }

   TFile *f_hsnt=new TFile("corrs_ntracks_hs_UL2018.root");
   TH2F* correction_mapHS=(TH2F*) f_hsnt->Get("correction_map");
   if (year=="2017"){
      TFile *f_hsnt=new TFile("corrs_ntracks_hs_UL2017.root");
      correction_mapHS=(TH2F*) f_hsnt->Get("correction_map");
   }
   else if (year=="2016post"){
      TFile *f_hsnt=new TFile("corrs_ntracks_hs_UL2016_postVFP.root");
      correction_mapHS=(TH2F*) f_hsnt->Get("correction_map");
   }
   else if (year=="2016pre"){
      TFile *f_hsnt=new TFile("corrs_ntracks_hs_UL2016_preVFP.root");
      correction_mapHS=(TH2F*) f_hsnt->Get("correction_map");
   }

   TFile *f_chargemisid=new TFile("measured_ele_chargemisid_2018.root");
   TH2F* h_chargemisid=(TH2F*) f_chargemisid->Get("e_chargemisid");
   if (year=="2017"){
      TFile *f_chargemisid=new TFile("measured_ele_chargemisid_2017.root");
      h_chargemisid=(TH2F*) f_chargemisid->Get("e_chargemisid");
   }
   else if (year=="2016post"){
      TFile *f_chargemisid=new TFile("measured_ele_chargemisid_2016post.root");
      h_chargemisid=(TH2F*) f_chargemisid->Get("e_chargemisid");
   }
   else if (year=="2016pre"){
      TFile *f_chargemisid=new TFile("measured_ele_chargemisid_2016pre.root");
      h_chargemisid=(TH2F*) f_chargemisid->Get("e_chargemisid");
   }



   TString uncertainties[1]={""};

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();

   for (Int_t i = 0; i < nentries_wtn; i++) {
	arbre->LoadTree(i);
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

        int charge_el=0;
        int charge_mu=0;
	TLorentzVector my_mu;
	my_mu.SetPtEtaPhiM(mu_pt[0], mu_eta[0], mu_phi[0], 0.105);
	charge_mu=mu_charge[0];
        TLorentzVector my_ele;
        my_ele.SetPtEtaPhiM(el_pt[0], el_eta[0], el_phi[0], 0.);
	charge_el=el_charge[0];
	if (fabs(my_mu.Eta())>2.4) continue; 
        if (fabs(my_ele.Eta())>1.4442 and fabs(my_ele.Eta())<1.5660) continue;
        if (fabs(my_ele.Eta())>2.5) continue; 
	if (my_mu.DeltaR(my_ele)<1.0) continue;
	//if (fabs(mu_dz[0]-el_dz[0])>0.1) continue;
	if (fabs(mu_dz[0]-el_dz[0])>0.03) continue;
	//if (mu_dxy[0]>0.05 or el_dxy[0]>0.05) continue;
	if (mu_sip2d[0]>4 or el_dxy[0]>0.05) continue;

        float simple_ditau_z=0.5*(2*pv_dz+el_dz[0]+mu_dz[0]);

	// Trigger block
	bool is_mu8ele23=false;
	bool is_mu23ele12=false;
 	bool is_isomu=false;
	is_mu8ele23=(hlt_mu8_el23_DZ and my_ele.Pt()>24 and my_mu.Pt()>10 and my_mu.Pt()<26);
	is_mu23ele12=(hlt_mu23_el12_DZ and my_ele.Pt()>13 and my_mu.Pt()>24 and my_mu.Pt()<26);
	is_isomu=(hlt_isomu24 and my_mu.Pt()>26);

	if (year=="2017"){
           is_mu8ele23=false;
           is_mu23ele12=false;
           is_isomu=false;
           is_mu8ele23=(hlt_mu8_el23_DZ and my_ele.Pt()>23 and my_mu.Pt()>8);
           is_mu23ele12=(hlt_mu23_el12_DZ and my_ele.Pt()>12 and my_mu.Pt()>24 and my_mu.Pt()<29);
           is_isomu=(hlt_isomu27 and my_mu.Pt()>29);
	}
        else if (year=="2016post" and name=="data_obs"){
           is_mu8ele23=false;
           is_mu23ele12=false;
           is_isomu=false;
           is_mu8ele23=(hlt_mu8_el23_DZ and my_ele.Pt()>23 and my_mu.Pt()>8);
           is_mu23ele12=(hlt_mu23_el12_DZ and my_ele.Pt()>12 and my_mu.Pt()>24 and my_mu.Pt()<26);
           is_isomu=((hlt_isomu24 or hlt_isotkmu24) and my_mu.Pt()>26);
        }
        if (year=="2016pre" or (year=="2016post" and name!="data_obs")){
           is_mu8ele23=false;
           is_mu23ele12=false;
           is_isomu=false;
           is_mu8ele23=(hlt_mu8_el23 and my_ele.Pt()>23 and my_mu.Pt()>8);
           is_mu23ele12=(hlt_mu23_el12 and my_ele.Pt()>12 and my_mu.Pt()>24 and my_mu.Pt()<26);
           is_isomu=((hlt_isomu24 or hlt_isotkmu24) and my_mu.Pt()>26);
        }

	if (!is_mu8ele23 and !is_mu23ele12 and !is_isomu) continue;
	if (sample=="MuonEG" and is_isomu) continue;
        if (sample=="SingleMuon" and !is_isomu) continue;

	// Block ID/iso/charge
	if (!el_MVAIDisoWPLoose[0]) continue;
	if (mu_rawiso[0]>1.0) continue;
	bool is_ele_isolated=(el_losthits[0]==0 and el_MVAIDisoWP80[0]);
	bool is_mu_isolated=(mu_pfiso[0]>0.50);
	bool is_SS = (mu_charge[0]*el_charge[0]>0);
	if (!el_conversionveto[0] or !el_chargeconsistent[0]) continue;
        if (name!="data_obs" and name!="W"){
	  if (!(el_genPart[0]==1 or el_genPart[0]==22 or el_genPart[0]==15)) continue;
          if (!(mu_genPart[0]==1 or mu_genPart[0]==15)) continue;
	}

	bool has_extralepton=false;
        for (int ii=1; ii<n_mu; ++ii){
           TLorentzVector tmp_mu; tmp_mu.SetPtEtaPhiM(mu_pt[ii], mu_eta[ii], mu_phi[ii], 0.105);
           if (mu_rawiso[ii]<0.4 and mu_charge[ii]*charge_mu<0 and my_mu.DeltaR(tmp_mu)>0.3 and my_ele.DeltaR(tmp_mu)>0.3 and fabs(mu_dz[0]-mu_dz[ii])<0.1 and mu_dxy[ii]<0.05 and mu_pt[ii]>5 and fabs(mu_eta[ii])<2.4){ 
		has_extralepton=true;
           }
        }
        for (int ii=1; ii<n_el; ++ii){
           TLorentzVector tmp_el; tmp_el.SetPtEtaPhiM(el_pt[ii], el_eta[ii], el_phi[ii], 0.0);
           if (el_MVAIDisoWPLoose[ii] and el_charge[ii]*charge_el<0 and my_ele.DeltaR(tmp_el)>0.3 and my_mu.DeltaR(tmp_el)>0.3 and fabs(el_dz[0]-el_dz[ii])<0.1 and el_dxy[ii]<0.05 and el_pt[ii]>7 and fabs(el_eta[ii])<2.5){ 
	      has_extralepton=true;
	   }
        }
	if (has_extralepton) continue; 


        // Block weights
        float aweight=1.0;
        if (name!="data_obs"){
           //aweight=aweight*L1PreFiringWeight_Nom;
           aweight*=LumiWeights_12->weight(Pileup_trueNumInteractions);
           if (name!="llscat") aweight=aweight*genWeight;
           float ept=my_ele.Pt();
           if (ept>120) ept=119;
           float elidsf_nom = h_eleIDSF->GetBinContent(h_eleIDSF->GetXaxis()->FindBin(my_ele.Eta()),h_eleIDSF->GetYaxis()->FindBin(ept));
           float elRecoSF = 1.0;
           if (ept<20) elRecoSF = h_eleRecoBelowSF->GetBinContent(h_eleRecoBelowSF->GetXaxis()->FindBin(my_ele.Eta()),h_eleRecoBelowSF->GetYaxis()->FindBin(ept));
           else elRecoSF = h_eleRecoSF->GetBinContent(h_eleRecoSF->GetXaxis()->FindBin(my_ele.Eta()),h_eleRecoSF->GetYaxis()->FindBin(ept));
           aweight=aweight*elidsf_nom*elRecoSF;


           float mu1pt=my_mu.Pt();
           if (mu1pt>120) mu1pt=119;
           if (mu1pt<15) mu1pt=16;
           float muidsf_nom = h_muonIDSF->GetBinContent(h_muonIDSF->GetXaxis()->FindBin(fabs(my_mu.Eta())),h_muonIDSF->GetYaxis()->FindBin(mu1pt));
           float muisosf_nom = h_muonIsoSF->GetBinContent(h_muonIsoSF->GetXaxis()->FindBin(fabs(my_mu.Eta())),h_muonIsoSF->GetYaxis()->FindBin(mu1pt));
           aweight=aweight*muidsf_nom*muisosf_nom;//*GetMuRecoSF(year,my_mu.Eta());


           float ept2=my_ele.Pt();
           if (ept2>200) ept2=199;
           float mupt2=my_mu.Pt();
           if (mupt2>200) mupt2=199;
           if (ept2<15) ept2=15;
           if (mupt2<15) mupt2=15;
           float eff_e_trg24_data=h_e_trg24_data_c->GetBinContent(h_e_trg24_data_c->GetXaxis()->FindBin(ept2),h_e_trg24_data_c->GetYaxis()->FindBin(fabs(my_ele.Eta())));
           float eff_e_trg12_data=h_e_trg12_data_c->GetBinContent(h_e_trg12_data_c->GetXaxis()->FindBin(ept2),h_e_trg12_data_c->GetYaxis()->FindBin(fabs(my_ele.Eta())));
           float eff_mu_trg24_data=h_mu_trg24_data_c->GetBinContent(h_mu_trg24_data_c->GetXaxis()->FindBin(mupt2),h_mu_trg24_data_c->GetYaxis()->FindBin(fabs(my_mu.Eta())));
           float eff_mu_trg8_data=h_mu_trg8_data_c->GetBinContent(h_mu_trg8_data_c->GetXaxis()->FindBin(mupt2),h_mu_trg8_data_c->GetYaxis()->FindBin(fabs(my_mu.Eta())));
           float eff_e_trg24_zll=h_e_trg24_zll_c->GetBinContent(h_e_trg24_zll_c->GetXaxis()->FindBin(ept2),h_e_trg24_zll_c->GetYaxis()->FindBin(fabs(my_ele.Eta())));
           float eff_e_trg12_zll=h_e_trg12_zll_c->GetBinContent(h_e_trg12_zll_c->GetXaxis()->FindBin(ept2),h_e_trg12_zll_c->GetYaxis()->FindBin(fabs(my_ele.Eta())));
           float eff_mu_trg24_zll=h_mu_trg24_zll_c->GetBinContent(h_mu_trg24_zll_c->GetXaxis()->FindBin(mupt2),h_mu_trg24_zll_c->GetYaxis()->FindBin(fabs(my_mu.Eta())));
           float eff_mu_trg8_zll=h_mu_trg8_zll_c->GetBinContent(h_mu_trg8_zll_c->GetXaxis()->FindBin(mupt2),h_mu_trg8_zll_c->GetYaxis()->FindBin(fabs(my_mu.Eta())));

           float probData =eff_e_trg24_data*eff_mu_trg8_data*int(is_mu8ele23)+eff_mu_trg24_data*eff_e_trg12_data*int(is_mu23ele12)-eff_e_trg24_data*eff_mu_trg24_data*int(is_mu8ele23 && is_mu23ele12);
           float probMC =eff_e_trg24_zll*eff_mu_trg8_zll*int(is_mu8ele23)+eff_mu_trg24_zll*eff_e_trg12_zll*int(is_mu23ele12)-eff_e_trg24_zll*eff_mu_trg24_zll*int(is_mu8ele23 && is_mu23ele12);

           float sf_trg=probData/probMC;
           if (probMC==0) sf_trg=1;
           float trgsf1 = h_muonTrgSF->GetBinContent(h_muonTrgSF->GetXaxis()->FindBin(fabs(my_mu.Eta())),h_muonTrgSF->GetYaxis()->FindBin(mu1pt));
           if (!is_isomu) aweight=aweight*sf_trg;
	   else aweight*=trgsf1;


	   if ((sample=="DYemu" or sample=="DY") and gentop_eta<10 and genantitop_eta<10){
	      TLorentzVector my_gentau; my_gentau.SetPtEtaPhiM(gentop_pt, gentop_eta, gentop_phi, 0.);
              TLorentzVector my_genantitau; my_gentau.SetPtEtaPhiM(genantitop_pt, genantitop_eta, genantitop_phi, 0.);
	      aweight*=fit_ptbalance->Eval((my_gentau+my_genantitau).Pt()/(my_gentau.Pt()+my_genantitau.Pt()));
	   }
        }

	if (sample=="DY" and is_DYtauetaumu) continue;
        if ((sample=="DY" or sample=="DYemu") and is_ZG) continue;

	// Ntracks corrections
        float zpos=simple_ditau_z;
        if (zpos<-10) zpos=-9.99;
        else if (zpos>10) zpos=9.99;
        //int ntpu=ntrk_PU;
        int ntpu=ntrk0p03_PU;
        if (ntpu>49) ntpu=49;
        if (name!="data_obs") {
                aweight*=correction_map->GetBinContent(correction_map->GetXaxis()->FindBin(ntpu),correction_map->GetYaxis()->FindBin(zpos));
        } 

        float gen_aco = (1.0 -fabs(my_mu.DeltaPhi(my_ele))/3.14159); //FIXME
        if (sample=="DYemu" or sample=="DY" or sample=="WZ3LNu" or sample=="ZZ4L"){ aweight*=correction_mapHS->GetBinContent(correction_mapHS->GetXaxis()->FindBin(TMath::Min(30,ntrk_HS)),correction_mapHS->GetYaxis()->FindBin(gen_aco)); }

	if (sample=="GGTT_Ctb20") aweight*=taug2weight;
	if (sample=="GGTT_Ctb20" or sample=="GGTT" or sample=="GGWW" or sample=="GGEE" or sample=="GGMM") aweight*=5.0; //elastic rescaling

	// Starting loop over uncertainties
	TLorentzVector save_mu=my_mu;
        TLorentzVector save_ele=my_ele;

        for (int k=0; k<nbhist; ++k){
           my_mu=save_mu;
	   my_ele=save_ele;
	   float weight2=1.0;

	   if (my_ele.Pt()<20) continue; //FIXME was 20
           if (my_mu.Pt()<20) continue; //FIXME was 20
           if (my_ele.Pt()<24 and my_mu.Pt()<24) continue;
	   //if (is_mu8ele23 and !is_mu23ele12 and my_ele.Pt()<24) continue;
           //if (!is_mu8ele23 and is_mu23ele12 and my_mu.Pt()<24) continue;
           //is_mu8ele23=(hlt_mu8_el23 and my_ele.Pt()>24 and my_mu.Pt()>10 and mu_trigger8[0]);
           //is_mu23ele12=(hlt_mu23_el12 and my_ele.Pt()>13 and my_mu.Pt()>24 and mu_trigger23[0]);
           //is_isomu24=(hlt_isomu24 and my_mu.Pt()>26);
           //if (!is_mu8ele23 and !is_mu23ele12 and !is_isomu24) continue;
	   float mvis=(my_ele+my_mu).M();
	   //if (mvis<40) continue;
	   if (mvis<4) continue;
           float mt = TMass_F(my_mu.Pt(), my_mu.Px(), my_mu.Py(), PuppiMET_pt, PuppiMET_phi);

           int ntrk=ntrk_prompt+ntrk_nonprompt;
	   //if (name=="llscat") ntrk=ntrk_PU+ntrk_signal;
	   //else if (name=="data_obs") ntrk=ntrk_all;
	   //else ntrk=ntrk_HS+ntrk_PU;

           if (name=="llscat") ntrk=ntrk0p03_PU+ntrk0p03_signal;
           else if (name=="data_obs") ntrk=ntrk0p03_all;
           else ntrk=ntrk0p03_HS+ntrk0p03_PU;

	   float ptbalance=(my_ele+my_mu).Pt()/(my_ele.Pt()+my_mu.Pt());

	   //if (ptbalance<0.05) cout<<ptbalance<<" "<<my_ele.Pt()<<" "<<my_mu.Pt()<<" "<<my_ele.DeltaR(my_mu)<<" "<<my_ele.DeltaPhi(my_mu)<<endl;

           bool is_cat0=(mvis>0);
           bool is_cat1=(mvis>0);
           bool is_cat2=(mvis>0);
           bool is_cat3=(mvis>0);
           bool is_cat4=(mvis>0);
           bool is_cat5=(mvis>0);
           bool is_cat6=(mvis>0);
           bool is_cat7=(mvis>0);
           bool is_cat8=(mvis>0);

           bool is_cat0R=(mvis>0);
           bool is_cat1R=(mvis>0);
           bool is_cat2R=(mvis>0);
           bool is_cat3R=(mvis>0);
           bool is_cat4R=(mvis>0);
           bool is_cat5R=(mvis>0);
           bool is_cat6R=(mvis>0);
           bool is_cat7R=(mvis>0);
           bool is_cat8R=(mvis>0);

	   float var0 = ntrk;
           float var1 = my_ele.Pt();
           float var2 = my_mu.Pt();
           float var3 = my_ele.Eta();
           float var4 = my_mu.Eta();
           float var5 = my_ele.DeltaR(my_mu);
           float var6 = (my_ele+my_mu).Pt()/(my_ele.Pt()+my_mu.Pt());
           float var7 = mt;//PuppiMET_pt;//mvis; //FIXME
           float var8 = 1-fabs(my_ele.DeltaPhi(my_mu))/3.14159;

	   if (is_control==1){
	      is_cat0=(ntrk==0);
              is_cat1=(ntrk==1);
              is_cat2=(ntrk==2);
              is_cat3=(ntrk>=3);
              is_cat4=(ptbalance<0.1);
              is_cat5=(ptbalance>0.1);
              is_cat6=(ntrk==6);
              is_cat7=(ntrk==7);
              is_cat8=(ntrk>=8);

              is_cat0R=(ntrk<10);
              is_cat1R=(ntrk<10);
              is_cat2R=(ntrk<10);
              is_cat3R=(ntrk>=3);
              is_cat4R=(ptbalance<0.3);
              is_cat5R=(ptbalance>0.1);
              is_cat6R=(ntrk<10);
              is_cat7R=(ntrk<10);
              is_cat8R=(ntrk>=8);

              var0=ptbalance;
	      var1=ptbalance;
              var2=ptbalance;
              var3=ptbalance;
              var4=ntrk;
              var5=ntrk;
              var6=ptbalance;
              var7=ptbalance;
              var8=ptbalance;
	   }

	   if (is_SS and is_ele_isolated and is_mu_isolated ){
	     if (is_cat0) h0[k]->Fill(var0,weight*aweight*weight2);
             if (is_cat1) h1[k]->Fill(var1,weight*aweight*weight2);
             if (is_cat2) h2[k]->Fill(var2,weight*aweight*weight2);
             if (is_cat3) h3[k]->Fill(var3,weight*aweight*weight2);
             if (is_cat4) h4[k]->Fill(var4,weight*aweight*weight2);
             if (is_cat5) h5[k]->Fill(var5,weight*aweight*weight2);
             if (is_cat6) h6[k]->Fill(var6,weight*aweight*weight2);
             if (is_cat7) h7[k]->Fill(var7,weight*aweight*weight2);
             if (is_cat8) h8[k]->Fill(var8,weight*aweight*weight2);

             if (is_cat0R) h0R[k]->Fill(var0,weight*aweight*weight2);
             if (is_cat1R) h1R[k]->Fill(var1,weight*aweight*weight2);
             if (is_cat2R) h2R[k]->Fill(var2,weight*aweight*weight2);
             if (is_cat3R) h3R[k]->Fill(var3,weight*aweight*weight2);
             if (is_cat4R) h4R[k]->Fill(var4,weight*aweight*weight2);
             if (is_cat5R) h5R[k]->Fill(var5,weight*aweight*weight2);
             if (is_cat6R) h6R[k]->Fill(var6,weight*aweight*weight2);
             if (is_cat7R) h7R[k]->Fill(var7,weight*aweight*weight2);
             if (is_cat8R) h8R[k]->Fill(var8,weight*aweight*weight2);
	   }

	   float ptmax=my_ele.Pt();
	   if (ptmax>60) ptmax=59;
	   float chargemisid=h_chargemisid->GetBinContent(h_chargemisid->GetXaxis()->FindBin(ptmax),h_chargemisid->GetYaxis()->FindBin(fabs(my_ele.Eta())));
	   float f_misid=chargemisid/(1-chargemisid);
           if (!is_SS and is_ele_isolated and is_mu_isolated){
             if (is_cat0) h0OS[k]->Fill(var0,weight*aweight*weight2*f_misid);
             if (is_cat1) h1OS[k]->Fill(var1,weight*aweight*weight2*f_misid);
             if (is_cat2) h2OS[k]->Fill(var2,weight*aweight*weight2*f_misid);
             if (is_cat3) h3OS[k]->Fill(var3,weight*aweight*weight2*f_misid);
             if (is_cat4) h4OS[k]->Fill(var4,weight*aweight*weight2*f_misid);
             if (is_cat5) h5OS[k]->Fill(var5,weight*aweight*weight2*f_misid);
             if (is_cat6) h6OS[k]->Fill(var6,weight*aweight*weight2*f_misid);
             if (is_cat7) h7OS[k]->Fill(var7,weight*aweight*weight2*f_misid);
             if (is_cat8) h8OS[k]->Fill(var8,weight*aweight*weight2*f_misid);
           }

	   float mufr=0.0;
           float mupt=my_mu.Pt();
           if (mupt<5) mupt=5;
           if (mupt>99) mupt=99;//FIXME
           if (fabs(my_mu.Eta())<1.2) mufr=fit_mufrB->Eval(mupt);
           else mufr=fit_mufrE->Eval(mupt);
	   int ntracks=ntrk_prompt+ntrk_nonprompt;
	   if (ntracks>80) ntracks=80;
	   mufr*=fit_mufrnt->Eval(ntracks);

           float efr=0.0;
	   float ept=my_ele.Pt();
           if (ept<10) ept=10;
           if (ept>60) ept=60;//FIXME
	   //if (fabs(my_ele.Eta())<1.5) efr=fit_efrB_notrg->Eval(ept);
           //else efr=fit_efrE_notrg->Eval(ept);
	   if (my_mu.Pt()>26){
              if (fabs(my_ele.Eta())<1.5) efr=fit_efrB_notrg->Eval(ept);
              else efr=fit_efrE_notrg->Eval(ept);
	   }
	   else{
              if (fabs(my_ele.Eta())<1.5) efr=fit_efrB_emutrg->Eval(ept);
              else efr=fit_efrE_emutrg->Eval(ept);
           }

           efr*=fit_efrnt->Eval(ntracks);

	   if (is_SS and is_ele_isolated and !is_mu_isolated ){
             if (is_cat0) h0_anti1[k]->Fill(var0,weight*aweight*weight2*mufr);
             if (is_cat1) h1_anti1[k]->Fill(var1,weight*aweight*weight2*mufr);
             if (is_cat2) h2_anti1[k]->Fill(var2,weight*aweight*weight2*mufr);
             if (is_cat3) h3_anti1[k]->Fill(var3,weight*aweight*weight2*mufr);
             if (is_cat4) h4_anti1[k]->Fill(var4,weight*aweight*weight2*mufr);
             if (is_cat5) h5_anti1[k]->Fill(var5,weight*aweight*weight2*mufr);
             if (is_cat6) h6_anti1[k]->Fill(var6,weight*aweight*weight2*mufr);
             if (is_cat7) h7_anti1[k]->Fill(var7,weight*aweight*weight2*mufr);
             if (is_cat8) h8_anti1[k]->Fill(var8,weight*aweight*weight2*mufr);

             if (is_cat0R) h0R_anti1[k]->Fill(var0,weight*aweight*weight2*mufr);
             if (is_cat1R) h1R_anti1[k]->Fill(var1,weight*aweight*weight2*mufr);
             if (is_cat2R) h2R_anti1[k]->Fill(var2,weight*aweight*weight2*mufr);
             if (is_cat3R) h3R_anti1[k]->Fill(var3,weight*aweight*weight2*mufr);
             if (is_cat4R) h4R_anti1[k]->Fill(var4,weight*aweight*weight2*mufr);
             if (is_cat5R) h5R_anti1[k]->Fill(var5,weight*aweight*weight2*mufr);
             if (is_cat6R) h6R_anti1[k]->Fill(var6,weight*aweight*weight2*mufr);
             if (is_cat7R) h7R_anti1[k]->Fill(var7,weight*aweight*weight2*mufr);
             if (is_cat8R) h8R_anti1[k]->Fill(var8,weight*aweight*weight2*mufr);
	   }

           if (is_SS and !is_ele_isolated and is_mu_isolated ){
             if (is_cat0) h0_anti2[k]->Fill(var0,weight*aweight*weight2*efr);
             if (is_cat1) h1_anti2[k]->Fill(var1,weight*aweight*weight2*efr);
             if (is_cat2) h2_anti2[k]->Fill(var2,weight*aweight*weight2*efr);
             if (is_cat3) h3_anti2[k]->Fill(var3,weight*aweight*weight2*efr);
             if (is_cat4) h4_anti2[k]->Fill(var4,weight*aweight*weight2*efr);
             if (is_cat5) h5_anti2[k]->Fill(var5,weight*aweight*weight2*efr);
             if (is_cat6) h6_anti2[k]->Fill(var6,weight*aweight*weight2*efr);
             if (is_cat7) h7_anti2[k]->Fill(var7,weight*aweight*weight2*efr);
             if (is_cat8) h8_anti2[k]->Fill(var8,weight*aweight*weight2*efr);

             if (is_cat0R) h0R_anti2[k]->Fill(var0,weight*aweight*weight2*efr);
             if (is_cat1R) h1R_anti2[k]->Fill(var1,weight*aweight*weight2*efr);
             if (is_cat2R) h2R_anti2[k]->Fill(var2,weight*aweight*weight2*efr);
             if (is_cat3R) h3R_anti2[k]->Fill(var3,weight*aweight*weight2*efr);
             if (is_cat4R) h4R_anti2[k]->Fill(var4,weight*aweight*weight2*efr);
             if (is_cat5R) h5R_anti2[k]->Fill(var5,weight*aweight*weight2*efr);
             if (is_cat6R) h6R_anti2[k]->Fill(var6,weight*aweight*weight2*efr);
             if (is_cat7R) h7R_anti2[k]->Fill(var7,weight*aweight*weight2*efr);
             if (is_cat8R) h8R_anti2[k]->Fill(var8,weight*aweight*weight2*efr);
	   }

           if (is_SS and !is_ele_isolated and !is_mu_isolated ){
             if (is_cat0) h0_anti0[k]->Fill(var0,weight*aweight*weight2*efr*mufr);
             if (is_cat1) h1_anti0[k]->Fill(var1,weight*aweight*weight2*efr*mufr);
             if (is_cat2) h2_anti0[k]->Fill(var2,weight*aweight*weight2*efr*mufr);
             if (is_cat3) h3_anti0[k]->Fill(var3,weight*aweight*weight2*efr*mufr);
             if (is_cat4) h4_anti0[k]->Fill(var4,weight*aweight*weight2*efr*mufr);
             if (is_cat5) h5_anti0[k]->Fill(var5,weight*aweight*weight2*efr*mufr);
             if (is_cat6) h6_anti0[k]->Fill(var6,weight*aweight*weight2*efr*mufr);
             if (is_cat7) h7_anti0[k]->Fill(var7,weight*aweight*weight2*efr*mufr);
             if (is_cat8) h8_anti0[k]->Fill(var8,weight*aweight*weight2*efr*mufr);

             if (is_cat0R) h0R_anti0[k]->Fill(var0,weight*aweight*weight2*efr*mufr);
             if (is_cat1R) h1R_anti0[k]->Fill(var1,weight*aweight*weight2*efr*mufr);
             if (is_cat2R) h2R_anti0[k]->Fill(var2,weight*aweight*weight2*efr*mufr);
             if (is_cat3R) h3R_anti0[k]->Fill(var3,weight*aweight*weight2*efr*mufr);
             if (is_cat4R) h4R_anti0[k]->Fill(var4,weight*aweight*weight2*efr*mufr);
             if (is_cat5R) h5R_anti0[k]->Fill(var5,weight*aweight*weight2*efr*mufr);
             if (is_cat6R) h6R_anti0[k]->Fill(var6,weight*aweight*weight2*efr*mufr);
             if (is_cat7R) h7R_anti0[k]->Fill(var7,weight*aweight*weight2*efr*mufr);
             if (is_cat8R) h8R_anti0[k]->Fill(var8,weight*aweight*weight2*efr*mufr);
	   }

	}

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    cout<<h0[0]->Integral()<<" "<<h1[0]->Integral()<<endl;

    bool isMC=(name!="data_obs");
    WriteHistToFileEMu(fout, h0, name, "em2l_0", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h0_anti0, name, "em2l_0_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h0_anti1, name, "em2l_0_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h0_anti2, name, "em2l_0_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h1, name, "em2l_1", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h1_anti0, name, "em2l_1_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h1_anti1, name, "em2l_1_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h1_anti2, name, "em2l_1_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h2, name, "em2l_2", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h2_anti0, name, "em2l_2_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h2_anti1, name, "em2l_2_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h2_anti2, name, "em2l_2_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h3, name, "em2l_3", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h3_anti0, name, "em2l_3_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h3_anti1, name, "em2l_3_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h3_anti2, name, "em2l_3_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h4, name, "em2l_4", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h4_anti0, name, "em2l_4_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h4_anti1, name, "em2l_4_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h4_anti2, name, "em2l_4_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h5, name, "em2l_5", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h5_anti0, name, "em2l_5_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h5_anti1, name, "em2l_5_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h5_anti2, name, "em2l_5_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h6, name, "em2l_6", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h6_anti0, name, "em2l_6_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h6_anti1, name, "em2l_6_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h6_anti2, name, "em2l_6_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h7, name, "em2l_7", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h7_anti0, name, "em2l_7_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h7_anti1, name, "em2l_7_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h7_anti2, name, "em2l_7_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h8, name, "em2l_8", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h8_anti0, name, "em2l_8_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h8_anti1, name, "em2l_8_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h8_anti2, name, "em2l_8_anti2", uncertainties, isMC, nbhist, true);

    WriteHistToFileEMu(fout, h0R, name, "em2lR_0", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h0R_anti0, name, "em2lR_0_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h0R_anti1, name, "em2lR_0_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h0R_anti2, name, "em2lR_0_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h1R, name, "em2lR_1", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h1R_anti0, name, "em2lR_1_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h1R_anti1, name, "em2lR_1_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h1R_anti2, name, "em2lR_1_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h2R, name, "em2lR_2", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h2R_anti0, name, "em2lR_2_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h2R_anti1, name, "em2lR_2_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h2R_anti2, name, "em2lR_2_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h3R, name, "em2lR_3", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h3R_anti0, name, "em2lR_3_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h3R_anti1, name, "em2lR_3_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h3R_anti2, name, "em2lR_3_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h4R, name, "em2lR_4", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h4R_anti0, name, "em2lR_4_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h4R_anti1, name, "em2lR_4_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h4R_anti2, name, "em2lR_4_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h5R, name, "em2lR_5", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h5R_anti0, name, "em2lR_5_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h5R_anti1, name, "em2lR_5_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h5R_anti2, name, "em2lR_5_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h6R, name, "em2lR_6", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h6R_anti0, name, "em2lR_6_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h6R_anti1, name, "em2lR_6_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h6R_anti2, name, "em2lR_6_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h7R, name, "em2lR_7", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h7R_anti0, name, "em2lR_7_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h7R_anti1, name, "em2lR_7_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h7R_anti2, name, "em2lR_7_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h8R, name, "em2lR_8", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h8R_anti0, name, "em2lR_8_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h8R_anti1, name, "em2lR_8_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h8R_anti2, name, "em2lR_8_anti2", uncertainties, isMC, nbhist, true);

    WriteHistToFileEMu(fout, h0OS, name, "em2lOS_0", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h1OS, name, "em2lOS_1", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h2OS, name, "em2lOS_2", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h3OS, name, "em2lOS_3", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h4OS, name, "em2lOS_4", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h5OS, name, "em2lOS_5", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h6OS, name, "em2lOS_6", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h7OS, name, "em2lOS_7", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h8OS, name, "em2lOS_8", uncertainties, isMC, nbhist, isMC);

    fout->Close();
} 

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

    //TTree *arbre2 = (TTree*) f_Double->Get("Runs");
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
    else if (sample=="DYemu"){ xs=0.95*2025.7*(0.178+0.174)*(0.178+0.174); weight=luminosity*xs/ngen;}//FIXME
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
    else if (sample=="TTW"){ xs=0.4611; weight=luminosity*xs/ngen;}
    else if (sample=="TTZ"){ xs=0.5407; weight=luminosity*xs/ngen;}
    else if (sample=="TTG"){ xs=3.8; weight=luminosity*xs/ngen;}
    else if (sample=="WG"){ xs=411.2; weight=luminosity*xs/ngen;}
    else if (sample=="WWG"){ xs=0.3369; weight=luminosity*xs/ngen;}
    else if (sample=="WWW"){ xs=0.3895; weight=luminosity*xs/ngen;}
    else if (sample=="ZG"){ xs=55.48; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_top"){ xs=39.65; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_antitop"){ xs=39.65; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_top"){ xs=134.2; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_antitop"){ xs=80.0; weight=luminosity*xs/ngen;}
    else if (sample=="GGTT"){ xs=1.161*0.008735; weight=luminosity*xs/ngen;}
    else if (sample=="GGWW"){ xs=0.00656; weight=luminosity*xs/ngen;} // new 1/137
    else if (sample=="GGEE"){ xs=0.303; weight=luminosity*xs/ngen;}
    else if (sample=="GGMM"){ xs=0.303; weight=luminosity*xs/ngen;}
    else if (name=="data_obs"){ weight=1.0;}
    else if (name=="test") { xs=1.0; weight=luminosity*xs/ngen;}
    else if (sample=="GGTT_Ctb20"){ xs=1.048*0.0403; weight=luminosity*xs/ngen;} // new 1/137
    else if (sample=="GGHTT"){ xs=48.30*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="GGHWW") {xs=48.30*0.2203*0.3258*0.3258; weight=luminosity*xs/ngen;}
    else if (sample=="llscat"){ xs=0.017; weight=luminosity*xs/ngen;}
    else if (sample=="llscat_ptl8"){ xs=0.006; weight=luminosity*xs/ngen;}

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(10);

    arbre->SetBranchAddress("n_mu", &n_mu);
    arbre->SetBranchAddress("n_el", &n_el);
    arbre->SetBranchAddress("n_pv", &n_pv);
    arbre->SetBranchAddress("pv_ntrk2", &pv_ntrk2);
    arbre->SetBranchAddress("pv_ntrk3", &pv_ntrk3);
    arbre->SetBranchAddress("hlt_mu8_el23", &hlt_mu8_el23);
    arbre->SetBranchAddress("hlt_mu23_el12", &hlt_mu23_el12);
    arbre->SetBranchAddress("pv_nmu", &pv_nmu);
    arbre->SetBranchAddress("ntrk_prompt", &ntrk_prompt);
    arbre->SetBranchAddress("ntrk_nonprompt", &ntrk_nonprompt);
    arbre->SetBranchAddress("PuppiMET_pt", &PuppiMET_pt);
    arbre->SetBranchAddress("PuppiMET_phi", &PuppiMET_phi);
    arbre->SetBranchAddress("taug2weight", &taug2weight);
    arbre->SetBranchAddress("ntrk_HS", &ntrk_HS);
    arbre->SetBranchAddress("ntrk_signal", &ntrk_signal);
    arbre->SetBranchAddress("ntrk_all", &ntrk_all);
    arbre->SetBranchAddress("ntrk_PU", &ntrk_PU);
    arbre->SetBranchAddress("pv_dz", &pv_dz);

    arbre->SetBranchAddress("el_conversionveto", &el_conversionveto);
    arbre->SetBranchAddress("mu_trigger23", &mu_trigger23);
    arbre->SetBranchAddress("mu_trigger8", &mu_trigger8);
    arbre->SetBranchAddress("mu_frompv", &mu_frompv);
    arbre->SetBranchAddress("mu_charge", &mu_charge);
    arbre->SetBranchAddress("mu_tight", &mu_tight);
    arbre->SetBranchAddress("mu_genPart", &mu_genPart);
    arbre->SetBranchAddress("mu_rawiso", &mu_rawiso);
   arbre->SetBranchAddress("el_charge", &el_charge);
   arbre->SetBranchAddress("el_frompv", &el_frompv);
   arbre->SetBranchAddress("el_genPart", &el_genPart);
   arbre->SetBranchAddress("el_trigger", &el_trigger);
   arbre->SetBranchAddress("el_chargeconsistent", &el_chargeconsistent);
   arbre->SetBranchAddress("el_CBIDLoose", &el_CBIDLoose);
   arbre->SetBranchAddress("el_CBIDMedium", &el_CBIDMedium);
   arbre->SetBranchAddress("el_CBIDTight", &el_CBIDTight);
   arbre->SetBranchAddress("el_CBIDVeto", &el_CBIDVeto);
   arbre->SetBranchAddress("el_MVAIDisoWP80", &el_MVAIDisoWP80);
   arbre->SetBranchAddress("el_MVAIDisoWP90", &el_MVAIDisoWP90);
   arbre->SetBranchAddress("el_MVAIDisoWPHZZ", &el_MVAIDisoWPHZZ);
   arbre->SetBranchAddress("el_MVAIDisoWPLoose", &el_MVAIDisoWPLoose);
   arbre->SetBranchAddress("el_MVAIDnoisoWPLoose", &el_MVAIDnoisoWPLoose);
   arbre->SetBranchAddress("el_MVAIDnoisoWP90", &el_MVAIDnoisoWP90);
   arbre->SetBranchAddress("el_MVAIDnoisoWP80", &el_MVAIDnoisoWP80);
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

   std::vector<TH1F*> hOS0;
   std::vector<TH1F*> hOS0_anti0;
   std::vector<TH1F*> hOS0_anti1;
   std::vector<TH1F*> hOS0_anti2;
   std::vector<TH1F*> hOS1;
   std::vector<TH1F*> hOS1_anti0;
   std::vector<TH1F*> hOS1_anti1;
   std::vector<TH1F*> hOS1_anti2;
   std::vector<TH1F*> hOS2;
   std::vector<TH1F*> hOS2_anti0;
   std::vector<TH1F*> hOS2_anti1;
   std::vector<TH1F*> hOS2_anti2;
   std::vector<TH1F*> hOS3;
   std::vector<TH1F*> hOS3_anti0;
   std::vector<TH1F*> hOS3_anti1;
   std::vector<TH1F*> hOS3_anti2;
   std::vector<TH1F*> hOS4;
   std::vector<TH1F*> hOS4_anti0;
   std::vector<TH1F*> hOS4_anti1;
   std::vector<TH1F*> hOS4_anti2;
   std::vector<TH1F*> hOS5;
   std::vector<TH1F*> hOS5_anti0;
   std::vector<TH1F*> hOS5_anti1;
   std::vector<TH1F*> hOS5_anti2;
   std::vector<TH1F*> hOS6;
   std::vector<TH1F*> hOS6_anti0;
   std::vector<TH1F*> hOS6_anti1;
   std::vector<TH1F*> hOS6_anti2;
   std::vector<TH1F*> hOS7;
   std::vector<TH1F*> hOS7_anti0;
   std::vector<TH1F*> hOS7_anti1;
   std::vector<TH1F*> hOS7_anti2;
   std::vector<TH1F*> hOS8;
   std::vector<TH1F*> hOS8_anti0;
   std::vector<TH1F*> hOS8_anti1;
   std::vector<TH1F*> hOS8_anti2;

   std::vector<TH1F*> h0_relaxanti0;
   std::vector<TH1F*> h3_relaxanti0;
   std::vector<TH1F*> h6_relaxanti0;
   std::vector<TH1F*> hOS0_relaxanti0;
   std::vector<TH1F*> hOS3_relaxanti0;
   std::vector<TH1F*> hOS6_relaxanti0;
   std::vector<TH1F*> h0_relaxanti1;
   std::vector<TH1F*> h3_relaxanti1;
   std::vector<TH1F*> h6_relaxanti1;
   std::vector<TH1F*> hOS0_relaxanti1;
   std::vector<TH1F*> hOS3_relaxanti1;
   std::vector<TH1F*> hOS6_relaxanti1;
   std::vector<TH1F*> h0_relaxanti2;
   std::vector<TH1F*> h3_relaxanti2;
   std::vector<TH1F*> h6_relaxanti2;
   std::vector<TH1F*> hOS0_relaxanti2;
   std::vector<TH1F*> hOS3_relaxanti2;
   std::vector<TH1F*> hOS6_relaxanti2;


   // Control 1
   float bins0[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80};
   float bins1[] = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80};
   float bins2[] = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80};
   float bins3[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};
   float bins4[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};
   float bins5[] = {0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3.0,3.1,3.2,3.3,3.4,3.4,3.5,3.6,3.7,3.8,3.9,4.0,4.1,4.2,4.3,4.4,4.5,4.6,4.7,4.8,4.9,5.0};
   float bins6[] = {0,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0};
   float bins7[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
   float bins8[] = {0,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0};
   
   // Control 2
   /*float bins0[] = {0,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0};
   float bins1[] = {0,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0};
   float bins2[] = {0,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0};
   float bins3[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80};
   float bins4[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80};
   float bins5[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80};
   float bins6[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
   float bins7[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
   float bins8[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};*/

   // Control 3
   /*float bins0[] = {0,0.05,0.1,0.15,0.20,0.4,0.6,0.8,1.0};
   float bins1[] = {0,0.05,0.1,0.15,0.20,0.4,0.6,0.8,1.0};
   float bins2[] = {0,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0};
   float bins3[] = {0,0.1,0.5,1.0};
   float bins4[] = {0,0.1,0.5,1.0};
   float bins5[] = {0,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0};
   float bins6[] = {0,0.05,0.1,0.5,1.0};
   float bins7[] = {0,0.05,0.1,0.5,1.0};
   float bins8[] = {0,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0};*/

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

        ostringstream HOSN0; HOSN0 << "hOS0" << k;
        hOS0.push_back(new TH1F (HOSN0.str().c_str(),"InvMa",binnum0,bins0)); hOS0[k]->Sumw2();
        ostringstream HOSN1; HOSN1 << "hOS1" << k;
        hOS1.push_back(new TH1F (HOSN1.str().c_str(),"InvMa",binnum1,bins1)); hOS1[k]->Sumw2();
        ostringstream HOSN2; HOSN2 << "hOS2" << k;
        hOS2.push_back(new TH1F (HOSN2.str().c_str(),"InvMa",binnum2,bins2)); hOS2[k]->Sumw2();
        ostringstream HOSN3; HOSN3 << "hOS3" << k;
        hOS3.push_back(new TH1F (HOSN3.str().c_str(),"InvMa",binnum3,bins3)); hOS3[k]->Sumw2();
        ostringstream HOSN4; HOSN4 << "hOS4" << k;
        hOS4.push_back(new TH1F (HOSN4.str().c_str(),"InvMa",binnum4,bins4)); hOS4[k]->Sumw2();
        ostringstream HOSN5; HOSN5 << "hOS5" << k;
        hOS5.push_back(new TH1F (HOSN5.str().c_str(),"InvMa",binnum5,bins5)); hOS5[k]->Sumw2();
        ostringstream HOSN6; HOSN6 << "hOS6" << k;
        hOS6.push_back(new TH1F (HOSN6.str().c_str(),"InvMa",binnum6,bins6)); hOS6[k]->Sumw2();
        ostringstream HOSN7; HOSN7 << "hOS7" << k;
        hOS7.push_back(new TH1F (HOSN7.str().c_str(),"InvMa",binnum7,bins7)); hOS7[k]->Sumw2();
        ostringstream HOSN8; HOSN8 << "hOS8" << k;
        hOS8.push_back(new TH1F (HOSN8.str().c_str(),"InvMa",binnum8,bins8)); hOS8[k]->Sumw2();



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

        ostringstream HOSN0_anti0; HOSN0_anti0 << "hOS0_anti0" << k;
        hOS0_anti0.push_back(new TH1F (HOSN0_anti0.str().c_str(),"InvMa",binnum0,bins0)); hOS0_anti0[k]->Sumw2();
        ostringstream HOSN1_anti0; HOSN1_anti0 << "hOS1_anti0" << k;
        hOS1_anti0.push_back(new TH1F (HOSN1_anti0.str().c_str(),"InvMa",binnum1,bins1)); hOS1_anti0[k]->Sumw2();
        ostringstream HOSN2_anti0; HOSN2_anti0 << "hOS2_anti0" << k;
        hOS2_anti0.push_back(new TH1F (HOSN2_anti0.str().c_str(),"InvMa",binnum2,bins2)); hOS2_anti0[k]->Sumw2();
        ostringstream HOSN3_anti0; HOSN3_anti0 << "hOS3_anti0" << k;
        hOS3_anti0.push_back(new TH1F (HOSN3_anti0.str().c_str(),"InvMa",binnum3,bins3)); hOS3_anti0[k]->Sumw2();
        ostringstream HOSN4_anti0; HOSN4_anti0 << "hOS4_anti0" << k;
        hOS4_anti0.push_back(new TH1F (HOSN4_anti0.str().c_str(),"InvMa",binnum4,bins4)); hOS4_anti0[k]->Sumw2();
        ostringstream HOSN5_anti0; HOSN5_anti0 << "hOS5_anti0" << k;
        hOS5_anti0.push_back(new TH1F (HOSN5_anti0.str().c_str(),"InvMa",binnum5,bins5)); hOS5_anti0[k]->Sumw2();
        ostringstream HOSN6_anti0; HOSN6_anti0 << "hOS6_anti0" << k;
        hOS6_anti0.push_back(new TH1F (HOSN6_anti0.str().c_str(),"InvMa",binnum6,bins6)); hOS6_anti0[k]->Sumw2();
        ostringstream HOSN7_anti0; HOSN7_anti0 << "hOS7_anti0" << k;
        hOS7_anti0.push_back(new TH1F (HOSN7_anti0.str().c_str(),"InvMa",binnum7,bins7)); hOS7_anti0[k]->Sumw2();
        ostringstream HOSN8_anti0; HOSN8_anti0 << "hOS8_anti0" << k;
        hOS8_anti0.push_back(new TH1F (HOSN8_anti0.str().c_str(),"InvMa",binnum8,bins8)); hOS8_anti0[k]->Sumw2();

        ostringstream HOSN0_anti1; HOSN0_anti1 << "hOS0_anti1" << k;
        hOS0_anti1.push_back(new TH1F (HOSN0_anti1.str().c_str(),"InvMa",binnum0,bins0)); hOS0_anti1[k]->Sumw2();
        ostringstream HOSN1_anti1; HOSN1_anti1 << "hOS1_anti1" << k;
        hOS1_anti1.push_back(new TH1F (HOSN1_anti1.str().c_str(),"InvMa",binnum1,bins1)); hOS1_anti1[k]->Sumw2();
        ostringstream HOSN2_anti1; HOSN2_anti1 << "hOS2_anti1" << k;
        hOS2_anti1.push_back(new TH1F (HOSN2_anti1.str().c_str(),"InvMa",binnum2,bins2)); hOS2_anti1[k]->Sumw2();
        ostringstream HOSN3_anti1; HOSN3_anti1 << "hOS3_anti1" << k;
        hOS3_anti1.push_back(new TH1F (HOSN3_anti1.str().c_str(),"InvMa",binnum3,bins3)); hOS3_anti1[k]->Sumw2();
        ostringstream HOSN4_anti1; HOSN4_anti1 << "hOS4_anti1" << k;
        hOS4_anti1.push_back(new TH1F (HOSN4_anti1.str().c_str(),"InvMa",binnum4,bins4)); hOS4_anti1[k]->Sumw2();
        ostringstream HOSN5_anti1; HOSN5_anti1 << "hOS5_anti1" << k;
        hOS5_anti1.push_back(new TH1F (HOSN5_anti1.str().c_str(),"InvMa",binnum5,bins5)); hOS5_anti1[k]->Sumw2();
        ostringstream HOSN6_anti1; HOSN6_anti1 << "hOS6_anti1" << k;
        hOS6_anti1.push_back(new TH1F (HOSN6_anti1.str().c_str(),"InvMa",binnum6,bins6)); hOS6_anti1[k]->Sumw2();
        ostringstream HOSN7_anti1; HOSN7_anti1 << "hOS7_anti1" << k;
        hOS7_anti1.push_back(new TH1F (HOSN7_anti1.str().c_str(),"InvMa",binnum7,bins7)); hOS7_anti1[k]->Sumw2();
        ostringstream HOSN8_anti1; HOSN8_anti1 << "hOS8_anti1" << k;
        hOS8_anti1.push_back(new TH1F (HOSN8_anti1.str().c_str(),"InvMa",binnum8,bins8)); hOS8_anti1[k]->Sumw2();

        ostringstream HOSN0_anti2; HOSN0_anti2 << "hOS0_anti2" << k;
        hOS0_anti2.push_back(new TH1F (HOSN0_anti2.str().c_str(),"InvMa",binnum0,bins0)); hOS0_anti2[k]->Sumw2();
        ostringstream HOSN1_anti2; HOSN1_anti2 << "hOS1_anti2" << k;
        hOS1_anti2.push_back(new TH1F (HOSN1_anti2.str().c_str(),"InvMa",binnum1,bins1)); hOS1_anti2[k]->Sumw2();
        ostringstream HOSN2_anti2; HOSN2_anti2 << "hOS2_anti2" << k;
        hOS2_anti2.push_back(new TH1F (HOSN2_anti2.str().c_str(),"InvMa",binnum2,bins2)); hOS2_anti2[k]->Sumw2();
        ostringstream HOSN3_anti2; HOSN3_anti2 << "hOS3_anti2" << k;
        hOS3_anti2.push_back(new TH1F (HOSN3_anti2.str().c_str(),"InvMa",binnum3,bins3)); hOS3_anti2[k]->Sumw2();
        ostringstream HOSN4_anti2; HOSN4_anti2 << "hOS4_anti2" << k;
        hOS4_anti2.push_back(new TH1F (HOSN4_anti2.str().c_str(),"InvMa",binnum4,bins4)); hOS4_anti2[k]->Sumw2();
        ostringstream HOSN5_anti2; HOSN5_anti2 << "hOS5_anti2" << k;
        hOS5_anti2.push_back(new TH1F (HOSN5_anti2.str().c_str(),"InvMa",binnum5,bins5)); hOS5_anti2[k]->Sumw2();
        ostringstream HOSN6_anti2; HOSN6_anti2 << "hOS6_anti2" << k;
        hOS6_anti2.push_back(new TH1F (HOSN6_anti2.str().c_str(),"InvMa",binnum6,bins6)); hOS6_anti2[k]->Sumw2();
        ostringstream HOSN7_anti2; HOSN7_anti2 << "hOS7_anti2" << k;
        hOS7_anti2.push_back(new TH1F (HOSN7_anti2.str().c_str(),"InvMa",binnum7,bins7)); hOS7_anti2[k]->Sumw2();
        ostringstream HOSN8_anti2; HOSN8_anti2 << "hOS8_anti2" << k;
        hOS8_anti2.push_back(new TH1F (HOSN8_anti2.str().c_str(),"InvMa",binnum8,bins8)); hOS8_anti2[k]->Sumw2();


	// Relax track selection
        ostringstream HN0R0; HN0R0 << "h0_relaxanti0" << k;
        h0_relaxanti0.push_back(new TH1F (HN0R0.str().c_str(),"InvMa",binnum0,bins0)); h0_relaxanti0[k]->Sumw2();
        ostringstream HN3R0; HN3R0 << "h3_relaxanti0" << k;
        h3_relaxanti0.push_back(new TH1F (HN3R0.str().c_str(),"InvMa",binnum3,bins3)); h3_relaxanti0[k]->Sumw2();
        ostringstream HN6R0; HN6R0 << "h6_relaxanti0" << k;
        h6_relaxanti0.push_back(new TH1F (HN6R0.str().c_str(),"InvMa",binnum6,bins6)); h6_relaxanti0[k]->Sumw2();
        ostringstream HN0R1; HN0R1 << "h0_relaxanti1" << k;
        h0_relaxanti1.push_back(new TH1F (HN0R1.str().c_str(),"InvMa",binnum0,bins0)); h0_relaxanti1[k]->Sumw2();
        ostringstream HN3R1; HN3R1 << "h3_relaxanti1" << k;
        h3_relaxanti1.push_back(new TH1F (HN3R1.str().c_str(),"InvMa",binnum3,bins3)); h3_relaxanti1[k]->Sumw2();
        ostringstream HN6R1; HN6R1 << "h6_relaxanti1" << k;
        h6_relaxanti1.push_back(new TH1F (HN6R1.str().c_str(),"InvMa",binnum6,bins6)); h6_relaxanti1[k]->Sumw2();
        ostringstream HN0R2; HN0R2 << "h0_relaxanti2" << k;
        h0_relaxanti2.push_back(new TH1F (HN0R2.str().c_str(),"InvMa",binnum0,bins0)); h0_relaxanti2[k]->Sumw2();
        ostringstream HN3R2; HN3R2 << "h3_relaxanti2" << k;
        h3_relaxanti2.push_back(new TH1F (HN3R2.str().c_str(),"InvMa",binnum3,bins3)); h3_relaxanti2[k]->Sumw2();
        ostringstream HN6R2; HN6R2 << "h6_relaxanti2" << k;
        h6_relaxanti2.push_back(new TH1F (HN6R2.str().c_str(),"InvMa",binnum6,bins6)); h6_relaxanti2[k]->Sumw2();

        ostringstream HOSN0R0; HOSN0R0 << "hOS0_relaxanti0" << k;
        hOS0_relaxanti0.push_back(new TH1F (HOSN0R0.str().c_str(),"InvMa",binnum0,bins0)); hOS0_relaxanti0[k]->Sumw2();
        ostringstream HOSN3R0; HOSN3R0 << "hOS3_relaxanti0" << k;
        hOS3_relaxanti0.push_back(new TH1F (HOSN3R0.str().c_str(),"InvMa",binnum3,bins3)); hOS3_relaxanti0[k]->Sumw2();
        ostringstream HOSN6R0; HOSN6R0 << "hOS6_relaxanti0" << k;
        hOS6_relaxanti0.push_back(new TH1F (HOSN6R0.str().c_str(),"InvMa",binnum6,bins6)); hOS6_relaxanti0[k]->Sumw2();
        ostringstream HOSN0R1; HOSN0R1 << "hOS0_relaxanti1" << k;
        hOS0_relaxanti1.push_back(new TH1F (HOSN0R1.str().c_str(),"InvMa",binnum0,bins0)); hOS0_relaxanti1[k]->Sumw2();
        ostringstream HOSN3R1; HOSN3R1 << "hOS3_relaxanti1" << k;
        hOS3_relaxanti1.push_back(new TH1F (HOSN3R1.str().c_str(),"InvMa",binnum3,bins3)); hOS3_relaxanti1[k]->Sumw2();
        ostringstream HOSN6R1; HOSN6R1 << "hOS6_relaxanti1" << k;
        hOS6_relaxanti1.push_back(new TH1F (HOSN6R1.str().c_str(),"InvMa",binnum6,bins6)); hOS6_relaxanti1[k]->Sumw2();
        ostringstream HOSN0R2; HOSN0R2 << "hOS0_relaxanti2" << k;
        hOS0_relaxanti2.push_back(new TH1F (HOSN0R2.str().c_str(),"InvMa",binnum0,bins0)); hOS0_relaxanti2[k]->Sumw2();
        ostringstream HOSN3R2; HOSN3R2 << "hOS3_relaxanti2" << k;
        hOS3_relaxanti2.push_back(new TH1F (HOSN3R2.str().c_str(),"InvMa",binnum3,bins3)); hOS3_relaxanti2[k]->Sumw2();
        ostringstream HOSN6R2; HOSN6R2 << "hOS6_relaxanti2" << k;
        hOS6_relaxanti2.push_back(new TH1F (HOSN6R2.str().c_str(),"InvMa",binnum6,bins6)); hOS6_relaxanti2[k]->Sumw2();

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

   TFile* f_ptbalance=new TFile("correction_ptbalance_2018.root","read");
   TF1* fit_ptbalance = (TF1*) f_ptbalance->Get("fit_ptbalance");

   TFile *f_punt=new TFile("corrs_ntracks_pu_UL2018.root");
   TH2F* correction_map=(TH2F*) f_punt->Get("corr");

   TFile *f_hsnt=new TFile("corrs_ntracks_hs_UL2018.root");
   TH2F* correction_mapHS=(TH2F*) f_hsnt->Get("correction_map");

   TH1F* h_ptbalance_all=new TH1F("h_ptbalance_all","h_ptbalance_all",20,0,1); h_ptbalance_all->Sumw2();
   TH1F* h_ptbalance_two=new TH1F("h_ptbalance_two","h_ptbalance_two",20,0,1); h_ptbalance_two->Sumw2();
   TH1F* h_ptbalance_extramu=new TH1F("h_ptbalance_extramu","h_ptbalance_extramu",20,0,1); h_ptbalance_extramu->Sumw2();
   TH1F* h_ptbalance_extrael=new TH1F("h_ptbalance_extrael","h_ptbalance_extrael",20,0,1); h_ptbalance_extrael->Sumw2();

   TString uncertainties[1]={""};

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();

   for (Int_t i = 0; i < nentries_wtn; i++) {
	arbre->LoadTree(i);
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	int charge_mu=0;
        int charge_extramu=0;
        int charge_el=0;
        int charge_extrael=0;
	TLorentzVector my_mu;
	my_mu.SetPtEtaPhiM(mu_pt[0], mu_eta[0], mu_phi[0], 0.105);
	charge_mu=mu_charge[0];
        TLorentzVector my_ele;
        my_ele.SetPtEtaPhiM(el_pt[0], el_eta[0], el_phi[0], 0.);
	charge_el=el_charge[0];
	if (fabs(my_mu.Eta())>2.4) continue;
        if (fabs(my_ele.Eta())>2.5) continue;
	if (my_mu.DeltaR(my_ele)<0.5) continue;
	if (fabs(mu_dz[0]-el_dz[0])>0.1) continue;
	if (mu_dxy[0]>0.05 or el_dxy[0]>0.05) continue;

        float simple_ditau_z=0.5*(2*pv_dz+el_dz[0]+mu_dz[0]);

	/*TLorentzVector my_extramu; my_extramu.SetPtEtaPhiM(0,0,0,0);
	if (n_mu>1 and mu_pfiso[1]) {my_extramu.SetPtEtaPhiM(mu_pt[1], mu_eta[1], mu_phi[1], 0.105); charge_extramu=mu_charge[1];}
        TLorentzVector my_extrael; my_extrael.SetPtEtaPhiM(0,0,0,0);
        if (n_el>1 and el_MVAIDisoWP80[1]) {my_extrael.SetPtEtaPhiM(el_pt[1], el_eta[1], el_phi[1], 0.); charge_extrael=el_charge[1];}*/

        TLorentzVector my_extramu; my_extramu.SetPtEtaPhiM(0,0,0,0);
        TLorentzVector my_extrael; my_extrael.SetPtEtaPhiM(0,0,0,0);
	bool is_extramu_isolated=0;
	int extramu_gen=0;
	for (int ii=1; ii<n_mu; ++ii){
	   TLorentzVector tmp_mu; tmp_mu.SetPtEtaPhiM(mu_pt[ii], mu_eta[ii], mu_phi[ii], 0.105);
	   //if (my_extramu.Pt()<1 and mu_rawiso[ii]<1.0 and mu_charge[ii]*charge_mu<0 and my_mu.DeltaR(tmp_mu)>0.5 and my_ele.DeltaR(tmp_mu)>0.5 and fabs((tmp_mu+my_mu).M()-91)>15) {my_extramu=tmp_mu; charge_extramu=mu_charge[ii]; is_extramu_isolated = mu_pfiso[ii]>0.5; extramu_gen=mu_genPart[ii];}  
	   if (my_extramu.Pt()<1 and mu_rawiso[ii]<0.5 and mu_charge[ii]*charge_mu<0 and my_mu.DeltaR(tmp_mu)>0.5 and my_ele.DeltaR(tmp_mu)>0.5) {my_extramu=tmp_mu; charge_extramu=mu_charge[ii]; is_extramu_isolated = mu_pfiso[ii]>0.5; extramu_gen=mu_genPart[ii];} //FIXME 
	}

        bool is_extrael_isolated=0;
	int extrael_gen=0;
        for (int ii=1; ii<n_el; ++ii){
           TLorentzVector tmp_el; tmp_el.SetPtEtaPhiM(el_pt[ii], el_eta[ii], el_phi[ii], 0.105);
           //if (my_extrael.Pt()<1 and el_MVAIDisoWPLoose[ii] and el_charge[ii]*charge_el<0 and my_mu.DeltaR(tmp_el)>0.5 and my_ele.DeltaR(tmp_el)>0.5 and fabs((tmp_el+my_ele).M()-91)>15) {my_extrael=tmp_el; charge_extrael=el_charge[ii]; is_extrael_isolated=el_MVAIDisoWP80[ii]; extrael_gen=el_genPart[ii];}
           if (my_extrael.Pt()<1 and el_MVAIDisoWPLoose[ii] and el_charge[ii]*charge_el<0 and my_mu.DeltaR(tmp_el)>0.5 and my_ele.DeltaR(tmp_el)>0.5) {my_extrael=tmp_el; charge_extrael=el_charge[ii]; is_extrael_isolated=el_MVAIDisoWP80[ii]; extrael_gen=el_genPart[ii];} //FIXME
        }

	//TLorentzVector my_gentau; my_gentau.SetPtEtaPhiM(0,0,0,0);
        //TLorentzVector my_genantitau; my_genantitau.SetPtEtaPhiM(0,0,0,0);

//cout<<"n_el, n_mu: "<<n_el<<", "<<n_mu<<endl;
//if (n_mu>1) cout<<"mu (pt, gen): "<<mu_pt[1]<<", "<<mu_genPart[1]<<" "<<mu_pfiso[1]<<endl;
//if (n_el>1) cout<<"el (pt, gen): "<<el_pt[1]<<", "<<el_genPart[1]<<" "<<el_MVAIDisoWP80[1]<<endl;

	// Trigger block
	bool is_mu8ele23=false;
	bool is_mu23ele12=false;
	is_mu8ele23=(hlt_mu8_el23 and my_ele.Pt()>23 and my_mu.Pt()>8 and mu_trigger8[0]);
	is_mu23ele12=(hlt_mu23_el12 and my_ele.Pt()>12 and my_mu.Pt()>23 and mu_trigger23[0]);
	if (!is_mu8ele23 and !is_mu23ele12) continue;

	// Block ID/iso/charge
	if (!el_MVAIDisoWPLoose[0]) continue;
	if (mu_rawiso[0]>0.5) continue;
	bool is_ele_isolated=el_MVAIDisoWP80[0];
	bool is_mu_isolated=(mu_pfiso[0]>0.50);
	bool is_SS = (mu_charge[0]*el_charge[0]>0);
	if (!el_conversionveto[0] or !el_chargeconsistent[0]) continue;
        /*if (name!="data_obs"){
	  if (!(el_genPart[0]==1 or el_genPart[0]==22 or el_genPart[0]==15)) continue;
          if (!(mu_genPart[0]==1 or mu_genPart[0]==15)) continue;
	}*/

	bool pass_gen_emu=true;
	bool pass_gen_extrael=true;
        bool pass_gen_extramu=true;
        if (name!="data_obs"){
          if (!(el_genPart[0]==1 or el_genPart[0]==22 or el_genPart[0]==15)) pass_gen_emu=false;
          if (!(mu_genPart[0]==1 or mu_genPart[0]==15)) pass_gen_emu=false;

          if (!(mu_genPart[0]==1 or mu_genPart[0]==15)) pass_gen_extrael=false;
          if (!(extrael_gen==1 or extrael_gen==22 or extrael_gen==15)) pass_gen_extrael=false;

          if (!(el_genPart[0]==1 or el_genPart[0]==22 or el_genPart[0]==15)) pass_gen_extramu=false;
          if (!(extramu_gen==1 or extramu_gen==15)) pass_gen_extramu=false;
        }


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

	   if (my_extrael.Pt()>10){
              float ept2=my_extrael.Pt();
              if (ept2>120) ept2=119;
              float elidsf2_nom = h_eleIDSF->GetBinContent(h_eleIDSF->GetXaxis()->FindBin(my_extrael.Eta()),h_eleIDSF->GetYaxis()->FindBin(ept2));
              float elRecoSF2 = 1.0;
              if (ept<20) elRecoSF2 = h_eleRecoBelowSF->GetBinContent(h_eleRecoBelowSF->GetXaxis()->FindBin(my_extrael.Eta()),h_eleRecoBelowSF->GetYaxis()->FindBin(ept2));
              else elRecoSF2 = h_eleRecoSF->GetBinContent(h_eleRecoSF->GetXaxis()->FindBin(my_extrael.Eta()),h_eleRecoSF->GetYaxis()->FindBin(ept2));
              aweight=aweight*elidsf2_nom*elRecoSF2;
	   }

           float mu1pt=my_mu.Pt();
           if (mu1pt>120) mu1pt=119;
           if (mu1pt<15) mu1pt=16;
           float muidsf_nom = h_muonIDSF->GetBinContent(h_muonIDSF->GetXaxis()->FindBin(fabs(my_mu.Eta())),h_muonIDSF->GetYaxis()->FindBin(mu1pt));
           float muisosf_nom = h_muonIsoSF->GetBinContent(h_muonIsoSF->GetXaxis()->FindBin(fabs(my_mu.Eta())),h_muonIsoSF->GetYaxis()->FindBin(mu1pt));
           aweight=aweight*muidsf_nom*muisosf_nom;//*GetMuRecoSF(year,my_mu.Eta());

	   if (my_extramu.Pt()>5){
              float mu2pt=my_mu.Pt();
              if (mu2pt>120) mu2pt=119;
              if (mu2pt<15) mu2pt=16; //FIXME add low pt
              float muidsf2_nom = h_muonIDSF->GetBinContent(h_muonIDSF->GetXaxis()->FindBin(fabs(my_extramu.Eta())),h_muonIDSF->GetYaxis()->FindBin(mu2pt));
              float muisosf2_nom = h_muonIsoSF->GetBinContent(h_muonIsoSF->GetXaxis()->FindBin(fabs(my_extramu.Eta())),h_muonIsoSF->GetYaxis()->FindBin(mu2pt));
              aweight=aweight*muidsf2_nom*muisosf2_nom;//*GetMuRecoSF(year,my_mu.Eta());
	   }

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
           aweight=aweight*sf_trg;
           if (sample=="TTTo2L2Nu" or sample=="TTToSemiLeptonic" or sample=="TTToHadronic") {float toppt_reweighting=pow((TMath::Exp(0.0615-0.0005*gentop_pt)*TMath::Exp(0.0615-0.0005*genantitop_pt)),0.5); aweight*=toppt_reweighting; }
	   if ((sample=="DYemu" or sample=="DY") and gentop_eta<10 and genantitop_eta<10){
	      TLorentzVector my_gentau; my_gentau.SetPtEtaPhiM(gentop_pt, gentop_eta, gentop_phi, 0.);
              TLorentzVector my_genantitau; my_gentau.SetPtEtaPhiM(genantitop_pt, genantitop_eta, genantitop_phi, 0.);
	      aweight*=fit_ptbalance->Eval((my_gentau+my_genantitau).Pt()/(my_gentau.Pt()+my_genantitau.Pt()));
	   }
        }

	if (sample=="DY" and gentop_phi<5 and genantitop_phi<5) continue;// remove tautau from inclusive sample 

	// Ntracks corrections
        float zpos=simple_ditau_z;
        if (zpos<-10) zpos=-9.99;
        else if (zpos>10) zpos=9.99;
        int ntpu=ntrk_PU;
        if (ntpu>49) ntpu=49;
        if (sample!="data_obs") {
                aweight*=correction_map->GetBinContent(correction_map->GetXaxis()->FindBin(ntpu),correction_map->GetYaxis()->FindBin(zpos));
        } 

        float gen_aco = (1.0 -fabs(my_mu.DeltaPhi(my_ele))/3.14159); //FIXME
        //if (sample=="DYemu" or sample=="DY" or sample=="VV2L2Nu" or sample=="WZ3LNu" or sample=="ZZ4L"){ aweight*=correction_mapHS->GetBinContent(correction_mapHS->GetXaxis()->FindBin(TMath::Min(30,ntrk_HS)),correction_mapHS->GetYaxis()->FindBin(gen_aco)); }
        //if (sample=="DYemu" or sample=="DY" or sample=="VV2L2Nu"){ aweight*=correction_mapHS->GetBinContent(correction_mapHS->GetXaxis()->FindBin(TMath::Min(30,ntrk_HS)),correction_mapHS->GetYaxis()->FindBin(gen_aco)); }
        if (sample=="DYemu" or sample=="DY"){ aweight*=correction_mapHS->GetBinContent(correction_mapHS->GetXaxis()->FindBin(TMath::Min(30,ntrk_HS)),correction_mapHS->GetYaxis()->FindBin(gen_aco)); }

	if (sample=="GGTT_Ctb20") aweight*=taug2weight;
	if (sample=="GGTT_Ctb20" or sample=="GGTT" or sample=="GGWW" or sample=="GGEE" or sample=="GGMM") aweight*=5.0; //elastic rescaling

	// Starting loop over uncertainties
	TLorentzVector save_mu=my_mu;
        TLorentzVector save_ele=my_ele;

        for (int k=0; k<nbhist; ++k){
           my_mu=save_mu;
	   my_ele=save_ele;
	   float weight2=1.0;

	   if (my_ele.Pt()<20) continue; //FIXME
           if (my_mu.Pt()<20) continue; //FIXME
           if (my_ele.Pt()<24 and my_mu.Pt()<24) continue;
	   if (is_mu8ele23 and !is_mu23ele12 and my_ele.Pt()<24) continue;
           if (!is_mu8ele23 and is_mu23ele12 and my_mu.Pt()<24) continue;
	   float mvis=(my_ele+my_mu).M();
	   if (mvis<12) continue;

           int ntrk=ntrk_prompt+ntrk_nonprompt;
	   if (name=="llscat") ntrk=ntrk_PU+ntrk_signal;
	   else if (name=="data_obs") ntrk=ntrk_all;
	   else ntrk=ntrk_HS+ntrk_PU;

           bool is_cat0=(mvis>0);
           bool is_cat1=(mvis>0);
           bool is_cat2=(mvis>0);
           bool is_cat3=(mvis>0);
           bool is_cat4=(mvis>0);
           bool is_cat5=(mvis>0);
           bool is_cat6=(mvis>0);
           bool is_cat7=(mvis>0);
           bool is_cat8=(mvis>0);

           bool is_cat0_relax=(mvis>0);
           bool is_cat1_relax=(mvis>0);
           bool is_cat2_relax=(mvis>0);
           bool is_cat3_relax=(mvis>0);
           bool is_cat4_relax=(mvis>0);
           bool is_cat5_relax=(mvis>0);
           bool is_cat6_relax=(mvis>0);
           bool is_cat7_relax=(mvis>0);
           bool is_cat8_relax=(mvis>0);

	   float var0 = ntrk;
           float var1 = my_ele.Pt();
           float var2 = my_mu.Pt();
           float var3 = my_ele.Eta();
           float var4 = my_mu.Eta();
           float var5 = my_ele.DeltaR(my_mu);
           float var6 = (my_ele+my_mu).Pt()/(my_ele.Pt()+my_mu.Pt());
           float var7 = mvis;
           float var8 = 1-fabs(my_ele.DeltaPhi(my_mu))/3.14159;

	   bool is_two=(my_extramu.Pt()<5 and my_extrael.Pt()<5);
	   bool is_extrael=(my_extramu.Pt()<5 and my_extrael.Pt()>5);
	   bool is_extramu=(my_extrael.Pt()<5 and my_extramu.Pt()>5);

           if (is_extramu and fabs((my_mu+my_extramu+my_ele).M()-91)<5 or fabs((my_mu+my_extramu).M()-91)<10) continue;
           if (is_extrael and fabs((my_ele+my_extrael).M()-91)<10) continue;

           int corr_ntrk=ntrk;
           if (is_extramu or is_extrael) corr_ntrk=ntrk-1;
           if (corr_ntrk<0) corr_ntrk=0;

	   if (is_control==2){
              is_cat0=(is_two);
              is_cat1=(is_extrael);
              is_cat2=(is_extramu);
              is_cat3=(is_two);
              is_cat4=(is_extrael);
              is_cat5=(is_extramu);
              is_cat6=(is_two);
              is_cat7=(is_extrael);
              is_cat8=(is_extramu);

              is_cat0_relax=(is_two);
              is_cat1_relax=(is_extrael);
              is_cat2_relax=(is_extramu);
              is_cat3_relax=(is_two);
              is_cat4_relax=(is_extrael);
              is_cat5_relax=(is_extramu);
              is_cat6_relax=(is_two);
              is_cat7_relax=(is_extrael);
              is_cat8_relax=(is_extramu);

              var0 = (my_ele+my_mu).Pt()/(my_ele.Pt()+my_mu.Pt());
              var1 = (my_ele+my_mu+my_extrael).Pt()/(my_ele.Pt()+my_mu.Pt()+my_extrael.Pt());
              var2 = (my_ele+my_mu+my_extramu).Pt()/(my_ele.Pt()+my_mu.Pt()+my_extramu.Pt());
              var3 = ntrk;
              var4 = ntrk;
              var5 = ntrk;
              var6 = mvis;
              var7 = mvis;
              var8 = mvis;
	   }
	
           if (is_control==3){
              /*is_cat0=(is_two and ntrk==0);
              is_cat1=(is_two and ntrk==1);
              is_cat2=(is_two and ntrk>1);*/
 	      is_cat0=(corr_ntrk==0);
              is_cat1=(corr_ntrk==1);
              is_cat2=(corr_ntrk>1);

              is_cat3=(is_extrael and ntrk<=1);
              is_cat4=(is_extrael and ntrk==2);
              is_cat5=(is_extrael and ntrk>2);
              is_cat6=(is_extramu and ntrk<=1);
              is_cat7=(is_extramu and ntrk==2);
              is_cat8=(is_extramu and ntrk>2);

              /*is_cat0_relax=(is_two and ntrk<10);
              is_cat1_relax=(is_two and ntrk<10);
              is_cat2_relax=(is_two and ntrk>1);*/
	      is_cat0_relax=(ntrk<10);
              is_cat1_relax=(ntrk<10);
              is_cat2_relax=(ntrk>1);

              is_cat3_relax=(is_extrael and ntrk<10);
              is_cat4_relax=(is_extrael and ntrk<10);
              is_cat5_relax=(is_extrael and ntrk>2);
              is_cat6_relax=(is_extramu and ntrk<10);
              is_cat7_relax=(is_extramu and ntrk<10);
              is_cat8_relax=(is_extramu and ntrk>2);

	      float ptbalance=(my_ele+my_mu).Pt()/(my_ele.Pt()+my_mu.Pt());
	      if (is_extramu) ptbalance=(my_ele+my_mu+my_extramu).Pt()/(my_ele.Pt()+my_mu.Pt()+my_extramu.Pt());
	      if (is_extrael) ptbalance=(my_ele+my_mu+my_extrael).Pt()/(my_ele.Pt()+my_mu.Pt()+my_extrael.Pt());

              var0 = ptbalance;
              var1 = ptbalance;
              var2 = ptbalance;
              var3 = ptbalance;
              var4 = ptbalance;
              var5 = ptbalance;
              var6 = ptbalance;
              var7 = ptbalance;
              var8 = ptbalance;
           }

           bool is_1_isolated = is_ele_isolated;
           bool is_2_isolated = is_mu_isolated;

	   if (is_SS and is_1_isolated and is_2_isolated and pass_gen_emu){
	     h_ptbalance_all->Fill((my_ele+my_mu).Pt()/(my_ele.Pt()+my_mu.Pt()),weight*aweight*weight2);
	     if (my_extramu.Pt()<5 and my_extrael.Pt()<5) h_ptbalance_two->Fill((my_ele+my_mu).Pt()/(my_ele.Pt()+my_mu.Pt()),weight*aweight*weight2);
             else if (my_extramu.Pt()>5 and my_extrael.Pt()<5) h_ptbalance_extramu->Fill((my_ele+my_mu+my_extramu).Pt()/(my_ele.Pt()+my_mu.Pt()+my_extramu.Pt()),weight*aweight*weight2);
             else if (my_extramu.Pt()<5 and my_extrael.Pt()>5) h_ptbalance_extrael->Fill((my_ele+my_mu+my_extrael).Pt()/(my_ele.Pt()+my_mu.Pt()+my_extrael.Pt()),weight*aweight*weight2);
	     if (is_cat0) h0[k]->Fill(var0,weight*aweight*weight2);
             if (is_cat1) h1[k]->Fill(var1,weight*aweight*weight2);
             if (is_cat2) h2[k]->Fill(var2,weight*aweight*weight2);
	   //}
           //if (is_SS and is_1_isolated and is_2_isolated and is_extrael_isolated and pass_gen_emu){
             if (is_cat3) h3[k]->Fill(var3,weight*aweight*weight2);
             if (is_cat4) h4[k]->Fill(var4,weight*aweight*weight2);
             if (is_cat5) h5[k]->Fill(var5,weight*aweight*weight2);
	   //}
           //if (is_SS and is_1_isolated and is_2_isolated and is_extramu_isolated and pass_gen_emu){
             if (is_cat6) h6[k]->Fill(var6,weight*aweight*weight2);
             if (is_cat7) h7[k]->Fill(var7,weight*aweight*weight2);
             if (is_cat8) h8[k]->Fill(var8,weight*aweight*weight2);
	   }

	   float mufr=0.0;
           float mupt=my_mu.Pt();
           if (mupt<5) mupt=5;
           if (mupt>39) mupt=39;//FIXME
	   if (fabs(my_mu.Eta())<1.2) mufr=h_mufrB->GetBinContent(h_mufrB->GetXaxis()->FindBin(mupt));
           else mufr=h_mufrE->GetBinContent(h_mufrE->GetXaxis()->FindBin(mupt));
           //if (mupt<5) mupt=5;
           //if (mupt>80) mupt=80;
           //if (fabs(my_mu.Eta())<1.2) mufr=fit_mufrB->Eval(mupt);
           //else mufr=fit_mufrE->Eval(mupt);
	   int ntracks=ntrk_prompt+ntrk_nonprompt;
	   if (ntracks>80) ntracks=80;
	   mufr*=fit_mufrnt->Eval(ntracks);

           float efr=0.0;
	   float ept=my_ele.Pt();
           if (ept<10) ept=10;
           if (ept>80) ept=39;//FIXME
           if (fabs(my_ele.Eta())<1.5) efr=h_efrB->GetBinContent(h_efrB->GetXaxis()->FindBin(ept));
           else efr=h_efrE->GetBinContent(h_efrE->GetXaxis()->FindBin(ept));
           //if (ept<10) ept=10;
	   //if (ept>80) ept=80;
           //if (fabs(my_ele.Eta())<1.5) efr=fit_efrB->Eval(ept);
           //else efr=fit_efrE->Eval(ept);
           efr*=fit_efrnt->Eval(ntracks);

	   float extramufr=0.0;
           float extramupt=my_extramu.Pt();
	   if (extramupt<8) extramupt=8; //FIXME
           if (fabs(my_extramu.Eta())<1.2) extramufr=h_mufrB->GetBinContent(h_mufrB->GetXaxis()->FindBin(extramupt));
           else extramufr=h_mufrE->GetBinContent(h_mufrE->GetXaxis()->FindBin(extramupt));
           extramufr*=fit_mufrnt->Eval(ntracks);

           float extraelfr=0.0;
           float extraelpt=my_extrael.Pt();
           if (fabs(my_extrael.Eta())<1.5) extraelfr=h_efrB->GetBinContent(h_efrB->GetXaxis()->FindBin(extraelpt));
           else extraelfr=h_efrE->GetBinContent(h_efrE->GetXaxis()->FindBin(extraelpt));
           extraelfr*=fit_efrnt->Eval(ntracks);

	   if (is_SS and is_1_isolated and !is_2_isolated and pass_gen_emu){
             if (is_cat0) h0_anti1[k]->Fill(var0,weight*aweight*weight2*mufr);
             if (is_cat1) h1_anti1[k]->Fill(var1,weight*aweight*weight2*mufr);
             if (is_cat2) h2_anti1[k]->Fill(var2,weight*aweight*weight2*mufr);
             if (is_cat0_relax) h0_relaxanti1[k]->Fill(var0,weight*aweight*weight2*mufr);
	   //}
           //if (is_SS and is_1_isolated and !is_2_isolated and is_extrael_isolated and pass_gen_emu){
             if (is_cat3) h3_anti1[k]->Fill(var3,weight*aweight*weight2*mufr);
             if (is_cat4) h4_anti1[k]->Fill(var4,weight*aweight*weight2*mufr);
             if (is_cat5) h5_anti1[k]->Fill(var5,weight*aweight*weight2*mufr);
             if (is_cat3_relax) h3_relaxanti1[k]->Fill(var3,weight*aweight*weight2*mufr);
	   //}
           //if (is_SS and is_1_isolated and !is_2_isolated and is_extramu_isolated and pass_gen_emu){
             if (is_cat6) h6_anti1[k]->Fill(var6,weight*aweight*weight2*mufr);
             if (is_cat7) h7_anti1[k]->Fill(var7,weight*aweight*weight2*mufr);
             if (is_cat8) h8_anti1[k]->Fill(var8,weight*aweight*weight2*mufr);
             if (is_cat6_relax) h6_relaxanti1[k]->Fill(var6,weight*aweight*weight2*mufr);
	   }


           if (is_SS and !is_1_isolated and is_2_isolated and pass_gen_emu){
             if (is_cat0) h0_anti2[k]->Fill(var0,weight*aweight*weight2*efr);
             if (is_cat1) h1_anti2[k]->Fill(var1,weight*aweight*weight2*efr);
             if (is_cat2) h2_anti2[k]->Fill(var2,weight*aweight*weight2*efr);
             if (is_cat0_relax) h0_relaxanti2[k]->Fill(var0,weight*aweight*weight2*efr);
	   //}
           //if (is_SS and !is_1_isolated and is_2_isolated and is_extrael_isolated and pass_gen_emu){
             if (is_cat3) h3_anti2[k]->Fill(var3,weight*aweight*weight2*efr);
             if (is_cat4) h4_anti2[k]->Fill(var4,weight*aweight*weight2*efr);
             if (is_cat5) h5_anti2[k]->Fill(var5,weight*aweight*weight2*efr);
             if (is_cat3_relax) h3_relaxanti2[k]->Fill(var3,weight*aweight*weight2*efr);
	   //}
           //if (is_SS and !is_1_isolated and is_2_isolated and is_extramu_isolated and pass_gen_emu){
             if (is_cat6) h6_anti2[k]->Fill(var6,weight*aweight*weight2*efr);
             if (is_cat7) h7_anti2[k]->Fill(var7,weight*aweight*weight2*efr);
             if (is_cat8) h8_anti2[k]->Fill(var8,weight*aweight*weight2*efr);
             if (is_cat6_relax) h6_relaxanti2[k]->Fill(var6,weight*aweight*weight2*efr);
	   }






           if (is_SS and !is_1_isolated and !is_2_isolated and pass_gen_emu){
             if (is_cat0) h0_anti0[k]->Fill(var0,weight*aweight*weight2*efr*mufr);
             if (is_cat1) h1_anti0[k]->Fill(var1,weight*aweight*weight2*efr*mufr);
             if (is_cat2) h2_anti0[k]->Fill(var2,weight*aweight*weight2*efr*mufr);
             if (is_cat0_relax) h0_relaxanti0[k]->Fill(var0,weight*aweight*weight2*efr*mufr);
	   //}
           //if (is_SS and !is_1_isolated and !is_2_isolated and is_extrael_isolated and pass_gen_emu){
             if (is_cat3) h3_anti0[k]->Fill(var3,weight*aweight*weight2*efr*mufr);
             if (is_cat4) h4_anti0[k]->Fill(var4,weight*aweight*weight2*efr*mufr);
             if (is_cat5) h5_anti0[k]->Fill(var5,weight*aweight*weight2*efr*mufr);
             if (is_cat3_relax) h3_relaxanti0[k]->Fill(var3,weight*aweight*weight2*efr*mufr);
	   //}
           //if (is_SS and !is_1_isolated and !is_2_isolated and is_extramu_isolated and pass_gen_emu){
             if (is_cat6) h6_anti0[k]->Fill(var6,weight*aweight*weight2*efr*mufr);
             if (is_cat7) h7_anti0[k]->Fill(var7,weight*aweight*weight2*efr*mufr);
             if (is_cat8) h8_anti0[k]->Fill(var8,weight*aweight*weight2*efr*mufr);
             if (is_cat6_relax) h6_relaxanti0[k]->Fill(var6,weight*aweight*weight2*efr*mufr);
	   }

	   //###########################################
	   //############## Start OS ###################
	   //###########################################


           if (!is_SS and is_1_isolated and is_2_isolated and pass_gen_emu){
             if (is_cat0) hOS0[k]->Fill(var0,weight*aweight*weight2);
             if (is_cat1) hOS1[k]->Fill(var1,weight*aweight*weight2);
             if (is_cat2) hOS2[k]->Fill(var2,weight*aweight*weight2);
	   //}
           //if (!is_SS and is_1_isolated and is_2_isolated and is_extrael_isolated and pass_gen_extrael){
             if (is_cat3) hOS3[k]->Fill(var3,weight*aweight*weight2);
             if (is_cat4) hOS4[k]->Fill(var4,weight*aweight*weight2);
             if (is_cat5) hOS5[k]->Fill(var5,weight*aweight*weight2);
	   //}
           //if (!is_SS and is_1_isolated and is_2_isolated and is_extramu_isolated and pass_gen_extramu){
             if (is_cat6) hOS6[k]->Fill(var6,weight*aweight*weight2);
//if (is_cat6 or is_cat7) cout<<var6<<" "<<(my_mu+my_extramu).M()<<" "<<(my_ele+my_mu+my_extramu).M()<<endl;
             if (is_cat7) hOS7[k]->Fill(var7,weight*aweight*weight2);
             if (is_cat8) hOS8[k]->Fill(var8,weight*aweight*weight2);
           }




           if (!is_SS and is_1_isolated and !is_2_isolated and pass_gen_emu){
             if (is_cat0) hOS0_anti1[k]->Fill(var0,weight*aweight*weight2*mufr);
             if (is_cat1) hOS1_anti1[k]->Fill(var1,weight*aweight*weight2*mufr);
             if (is_cat2) hOS2_anti1[k]->Fill(var2,weight*aweight*weight2*mufr);
             if (is_cat0_relax) hOS0_relaxanti1[k]->Fill(var0,weight*aweight*weight2*mufr);
	   }
           /*if (!is_SS and is_1_isolated and is_2_isolated and !is_extrael_isolated and pass_gen_extrael){
             if (is_cat3) hOS3_anti1[k]->Fill(var3,weight*aweight*weight2*extraelfr);
             if (is_cat4) hOS4_anti1[k]->Fill(var4,weight*aweight*weight2*extraelfr);
             if (is_cat5) hOS5_anti1[k]->Fill(var5,weight*aweight*weight2*extraelfr);
             if (is_cat3_relax) hOS3_relaxanti1[k]->Fill(var3,weight*aweight*weight2*extraelfr);
	   }
           if (!is_SS and is_1_isolated and is_2_isolated and !is_extramu_isolated and pass_gen_extramu){
             if (is_cat6) hOS6_anti1[k]->Fill(var6,weight*aweight*weight2*extramufr);
             if (is_cat7) hOS7_anti1[k]->Fill(var7,weight*aweight*weight2*extramufr);
             if (is_cat8) hOS8_anti1[k]->Fill(var8,weight*aweight*weight2*extramufr);
             if (is_cat6_relax) hOS6_relaxanti1[k]->Fill(var6,weight*aweight*weight2*extramufr);
	   }*/
           if (!is_SS and is_1_isolated and !is_2_isolated and pass_gen_emu){
             if (is_cat3) hOS3_anti1[k]->Fill(var3,weight*aweight*weight2*mufr);
             if (is_cat4) hOS4_anti1[k]->Fill(var4,weight*aweight*weight2*mufr);
             if (is_cat5) hOS5_anti1[k]->Fill(var5,weight*aweight*weight2*mufr);
             if (is_cat3_relax) hOS3_relaxanti1[k]->Fill(var5,weight*aweight*weight2*mufr);
             if (is_cat6) hOS6_anti1[k]->Fill(var6,weight*aweight*weight2*mufr);
             if (is_cat7) hOS7_anti1[k]->Fill(var7,weight*aweight*weight2*mufr);
             if (is_cat8) hOS8_anti1[k]->Fill(var8,weight*aweight*weight2*mufr);
             if (is_cat6_relax) hOS6_relaxanti1[k]->Fill(var6,weight*aweight*weight2*mufr);
           }




           if (!is_SS and !is_1_isolated and is_2_isolated and pass_gen_emu){
             if (is_cat0) hOS0_anti2[k]->Fill(var0,weight*aweight*weight2*efr);
             if (is_cat1) hOS1_anti2[k]->Fill(var1,weight*aweight*weight2*efr);
             if (is_cat2) hOS2_anti2[k]->Fill(var2,weight*aweight*weight2*efr);
             if (is_cat0_relax) hOS0_relaxanti2[k]->Fill(var0,weight*aweight*weight2*efr);
 	   }
           /*if (!is_SS and is_1_isolated and !is_2_isolated and is_extrael_isolated and pass_gen_extrael){
             if (is_cat3) hOS3_anti2[k]->Fill(var3,weight*aweight*weight2*mufr);
             if (is_cat4) hOS4_anti2[k]->Fill(var4,weight*aweight*weight2*mufr);
             if (is_cat5) hOS5_anti2[k]->Fill(var5,weight*aweight*weight2*mufr);
             if (is_cat3_relax) hOS3_relaxanti2[k]->Fill(var3,weight*aweight*weight2*mufr);
	   }
           if (!is_SS and !is_1_isolated and is_2_isolated and is_extramu_isolated and pass_gen_extramu){
             if (is_cat6) hOS6_anti2[k]->Fill(var6,weight*aweight*weight2*efr);
             if (is_cat7) hOS7_anti2[k]->Fill(var7,weight*aweight*weight2*efr);
             if (is_cat8) hOS8_anti2[k]->Fill(var8,weight*aweight*weight2*efr);
             if (is_cat6_relax) hOS6_relaxanti2[k]->Fill(var6,weight*aweight*weight2*efr);
	   }*/

           if (!is_SS and !is_1_isolated and is_2_isolated and pass_gen_emu){
             if (is_cat3) hOS3_anti2[k]->Fill(var3,weight*aweight*weight2*efr);
             if (is_cat4) hOS4_anti2[k]->Fill(var4,weight*aweight*weight2*efr);
             if (is_cat5) hOS5_anti2[k]->Fill(var5,weight*aweight*weight2*efr);
             if (is_cat3_relax) hOS3_relaxanti2[k]->Fill(var3,weight*aweight*weight2*efr);
             if (is_cat6) hOS6_anti2[k]->Fill(var6,weight*aweight*weight2*efr);
             if (is_cat7) hOS7_anti2[k]->Fill(var7,weight*aweight*weight2*efr);
             if (is_cat8) hOS8_anti2[k]->Fill(var8,weight*aweight*weight2*efr);
             if (is_cat6_relax) hOS6_relaxanti2[k]->Fill(var6,weight*aweight*weight2*efr);
           }





           if (!is_SS and !is_1_isolated and !is_2_isolated and pass_gen_emu){
             if (is_cat0) hOS0_anti0[k]->Fill(var0,weight*aweight*weight2*efr*mufr);
             if (is_cat1) hOS1_anti0[k]->Fill(var1,weight*aweight*weight2*efr*mufr);
             if (is_cat2) hOS2_anti0[k]->Fill(var2,weight*aweight*weight2*efr*mufr);
             if (is_cat0_relax) hOS0_relaxanti0[k]->Fill(var0,weight*aweight*weight2*efr*mufr);
	   }
           /*if (!is_SS and is_1_isolated and !is_2_isolated and !is_extrael_isolated and pass_gen_extrael){
             if (is_cat3) hOS3_anti0[k]->Fill(var3,weight*aweight*weight2*mufr*extraelfr);
             if (is_cat4) hOS4_anti0[k]->Fill(var4,weight*aweight*weight2*mufr*extraelfr);
             if (is_cat5) hOS5_anti0[k]->Fill(var5,weight*aweight*weight2*mufr*extraelfr);
             if (is_cat3_relax) hOS3_relaxanti0[k]->Fill(var3,weight*aweight*weight2*mufr*extraelfr);
	   }
           if (!is_SS and !is_1_isolated and is_2_isolated and !is_extramu_isolated and pass_gen_extramu){
             if (is_cat6) hOS6_anti0[k]->Fill(var6,weight*aweight*weight2*efr*extramufr);
             if (is_cat7) hOS7_anti0[k]->Fill(var7,weight*aweight*weight2*efr*extramufr);
             if (is_cat8) hOS8_anti0[k]->Fill(var8,weight*aweight*weight2*efr*extramufr);
             if (is_cat6_relax) hOS6_relaxanti0[k]->Fill(var6,weight*aweight*weight2*efr*extramufr);
	   }*/
           if (!is_SS and !is_1_isolated and !is_2_isolated and pass_gen_emu){
             if (is_cat3) hOS3_anti0[k]->Fill(var3,weight*aweight*weight2*efr*mufr);
             if (is_cat4) hOS4_anti0[k]->Fill(var4,weight*aweight*weight2*efr*mufr);
             if (is_cat5) hOS5_anti0[k]->Fill(var5,weight*aweight*weight2*efr*mufr);
             if (is_cat3_relax) hOS3_relaxanti0[k]->Fill(var3,weight*aweight*weight2*efr*mufr);
             if (is_cat6) hOS6_anti0[k]->Fill(var6,weight*aweight*weight2*efr*mufr);
             if (is_cat7) hOS7_anti0[k]->Fill(var7,weight*aweight*weight2*efr*mufr);
             if (is_cat8) hOS8_anti0[k]->Fill(var8,weight*aweight*weight2*efr*mufr);
             if (is_cat6_relax) hOS6_relaxanti0[k]->Fill(var6,weight*aweight*weight2*efr*mufr);
           }



	}

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    cout<<h0[0]->Integral()<<" "<<h1[0]->Integral()<<endl;

    h_ptbalance_all->Write();
    h_ptbalance_two->Write();
    h_ptbalance_extramu->Write();
    h_ptbalance_extrael->Write();

    bool isMC=(name!="data_obs");
    WriteHistToFileEMu(fout, h0, name, "em_0", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h0_anti0, name, "em_0_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h0_anti1, name, "em_0_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h0_anti2, name, "em_0_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h0_relaxanti0, name, "em_0_relaxanti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h0_relaxanti1, name, "em_0_relaxanti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h0_relaxanti2, name, "em_0_relaxanti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h1, name, "em_1", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h1_anti0, name, "em_1_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h1_anti1, name, "em_1_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h1_anti2, name, "em_1_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h2, name, "em_2", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h2_anti0, name, "em_2_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h2_anti1, name, "em_2_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h2_anti2, name, "em_2_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h3, name, "em_3", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h3_anti0, name, "em_3_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h3_anti1, name, "em_3_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h3_anti2, name, "em_3_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h3_relaxanti0, name, "em_3_relaxanti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h3_relaxanti1, name, "em_3_relaxanti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h3_relaxanti2, name, "em_3_relaxanti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h4, name, "em_4", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h4_anti0, name, "em_4_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h4_anti1, name, "em_4_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h4_anti2, name, "em_4_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h5, name, "em_5", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h5_anti0, name, "em_5_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h5_anti1, name, "em_5_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h5_anti2, name, "em_5_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h6, name, "em_6", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h6_anti0, name, "em_6_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h6_anti1, name, "em_6_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h6_anti2, name, "em_6_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h6_relaxanti0, name, "em_6_relaxanti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h6_relaxanti1, name, "em_6_relaxanti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h6_relaxanti2, name, "em_6_relaxanti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h7, name, "em_7", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h7_anti0, name, "em_7_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h7_anti1, name, "em_7_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h7_anti2, name, "em_7_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h8, name, "em_8", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, h8_anti0, name, "em_8_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h8_anti1, name, "em_8_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, h8_anti2, name, "em_8_anti2", uncertainties, isMC, nbhist, true);

    WriteHistToFileEMu(fout, hOS0, name, "em_0_OS", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, hOS0_anti0, name, "em_0_OS_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS0_anti1, name, "em_0_OS_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS0_anti2, name, "em_0_OS_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS0_relaxanti0, name, "em_0_OS_relaxanti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS0_relaxanti1, name, "em_0_OS_relaxanti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS0_relaxanti2, name, "em_0_OS_relaxanti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS1, name, "em_1_OS", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, hOS1_anti0, name, "em_1_OS_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS1_anti1, name, "em_1_OS_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS1_anti2, name, "em_1_OS_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS2, name, "em_2_OS", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, hOS2_anti0, name, "em_2_OS_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS2_anti1, name, "em_2_OS_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS2_anti2, name, "em_2_OS_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS3, name, "em_3_OS", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, hOS3_anti0, name, "em_3_OS_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS3_anti1, name, "em_3_OS_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS3_anti2, name, "em_3_OS_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS3_relaxanti0, name, "em_3_OS_relaxanti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS3_relaxanti1, name, "em_3_OS_relaxanti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS3_relaxanti2, name, "em_3_OS_relaxanti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS4, name, "em_4_OS", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, hOS4_anti0, name, "em_4_OS_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS4_anti1, name, "em_4_OS_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS4_anti2, name, "em_4_OS_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS5, name, "em_5_OS", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, hOS5_anti0, name, "em_5_OS_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS5_anti1, name, "em_5_OS_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS5_anti2, name, "em_5_OS_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS6, name, "em_6_OS", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, hOS6_anti0, name, "em_6_OS_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS6_anti1, name, "em_6_OS_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS6_anti2, name, "em_6_OS_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS6_relaxanti0, name, "em_6_OS_relaxanti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS6_relaxanti1, name, "em_6_OS_relaxanti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS6_relaxanti2, name, "em_6_OS_relaxanti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS7, name, "em_7_OS", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, hOS7_anti0, name, "em_7_OS_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS7_anti1, name, "em_7_OS_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS7_anti2, name, "em_7_OS_anti2", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS8, name, "em_8_OS", uncertainties, isMC, nbhist, isMC);
    WriteHistToFileEMu(fout, hOS8_anti0, name, "em_8_OS_anti0", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS8_anti1, name, "em_8_OS_anti1", uncertainties, isMC, nbhist, true);
    WriteHistToFileEMu(fout, hOS8_anti2, name, "em_8_OS_anti2", uncertainties, isMC, nbhist, true);


    fout->Close();
} 



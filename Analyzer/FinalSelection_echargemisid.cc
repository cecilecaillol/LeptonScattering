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
#include "chargemisid_Tree.h"
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
    TTree *arbre = (TTree*) f_Double->Get("demo/tree_misid");

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(10);

   arbre->SetBranchAddress("genWeight", &genWeight);

   arbre->SetBranchAddress("el_conversionveto", &el_conversionveto);
   arbre->SetBranchAddress("el_charge", &el_charge);
   arbre->SetBranchAddress("el_genPart", &el_genPart);
   arbre->SetBranchAddress("el_chargeconsistent", &el_chargeconsistent);
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
   arbre->SetBranchAddress("el_sip2d", &el_sip2d);

   arbre->SetBranchAddress("Pileup_trueNumInteractions", &Pileup_trueNumInteractions);


   float bins0[] = {5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,25,30,35,40,50,75,100};
   int  binnum0 = sizeof(bins0)/sizeof(Float_t) - 1;

    TH1F* h_OS_EH_EH=new TH1F("h_OS_EH_EH","h_OS_EH_EH",60,60,120); h_OS_EH_EH->Sumw2();
    TH1F* h_OS_EH_BH=new TH1F("h_OS_EH_BH","h_OS_EH_BH",60,60,120); h_OS_EH_BH->Sumw2();
    TH1F* h_OS_EH_EM=new TH1F("h_OS_EH_EM","h_OS_EH_EM",60,60,120); h_OS_EH_EM->Sumw2();
    TH1F* h_OS_EH_BM=new TH1F("h_OS_EH_BM","h_OS_EH_BM",60,60,120); h_OS_EH_BM->Sumw2();
    TH1F* h_OS_EH_EL=new TH1F("h_OS_EH_EL","h_OS_EH_EL",60,60,120); h_OS_EH_EL->Sumw2();
    TH1F* h_OS_EH_BL=new TH1F("h_OS_EH_BL","h_OS_EH_BL",60,60,120); h_OS_EH_BL->Sumw2();
    TH1F* h_OS_BH_BH=new TH1F("h_OS_BH_BH","h_OS_BH_BH",60,60,120); h_OS_BH_BH->Sumw2();
    TH1F* h_OS_BH_EM=new TH1F("h_OS_BH_EM","h_OS_BH_EM",60,60,120); h_OS_BH_EM->Sumw2();
    TH1F* h_OS_BH_BM=new TH1F("h_OS_BH_BM","h_OS_BH_BM",60,60,120); h_OS_BH_BM->Sumw2();
    TH1F* h_OS_BH_EL=new TH1F("h_OS_BH_EL","h_OS_BH_EL",60,60,120); h_OS_BH_EL->Sumw2();
    TH1F* h_OS_BH_BL=new TH1F("h_OS_BH_BL","h_OS_BH_BL",60,60,120); h_OS_BH_BL->Sumw2();
    TH1F* h_OS_EM_EM=new TH1F("h_OS_EM_EM","h_OS_EM_EM",60,60,120); h_OS_EM_EM->Sumw2();
    TH1F* h_OS_EM_BM=new TH1F("h_OS_EM_BM","h_OS_EM_BM",60,60,120); h_OS_EM_BM->Sumw2();
    TH1F* h_OS_EM_EL=new TH1F("h_OS_EM_EL","h_OS_EM_EL",60,60,120); h_OS_EM_EL->Sumw2();
    TH1F* h_OS_EM_BL=new TH1F("h_OS_EM_BL","h_OS_EM_BL",60,60,120); h_OS_EM_BL->Sumw2();
    TH1F* h_OS_BM_BM=new TH1F("h_OS_BM_BM","h_OS_BM_BM",60,60,120); h_OS_BM_BM->Sumw2();
    TH1F* h_OS_BM_EL=new TH1F("h_OS_BM_EL","h_OS_BM_EL",60,60,120); h_OS_BM_EL->Sumw2();
    TH1F* h_OS_BM_BL=new TH1F("h_OS_BM_BL","h_OS_BM_BL",60,60,120); h_OS_BM_BL->Sumw2();
    TH1F* h_OS_EL_EL=new TH1F("h_OS_EL_EL","h_OS_EL_EL",60,60,120); h_OS_EL_EL->Sumw2();
    TH1F* h_OS_EL_BL=new TH1F("h_OS_EL_BL","h_OS_EL_BL",60,60,120); h_OS_EL_BL->Sumw2();
    TH1F* h_OS_BL_BL=new TH1F("h_OS_BL_BL","h_OS_BL_BL",60,60,120); h_OS_BL_BL->Sumw2();

    TH1F* h_SS_EH_EH=new TH1F("h_SS_EH_EH","h_SS_EH_EH",60,60,120); h_SS_EH_EH->Sumw2();
    TH1F* h_SS_EH_BH=new TH1F("h_SS_EH_BH","h_SS_EH_BH",60,60,120); h_SS_EH_BH->Sumw2();
    TH1F* h_SS_EH_EM=new TH1F("h_SS_EH_EM","h_SS_EH_EM",60,60,120); h_SS_EH_EM->Sumw2();
    TH1F* h_SS_EH_BM=new TH1F("h_SS_EH_BM","h_SS_EH_BM",60,60,120); h_SS_EH_BM->Sumw2();
    TH1F* h_SS_EH_EL=new TH1F("h_SS_EH_EL","h_SS_EH_EL",60,60,120); h_SS_EH_EL->Sumw2();
    TH1F* h_SS_EH_BL=new TH1F("h_SS_EH_BL","h_SS_EH_BL",60,60,120); h_SS_EH_BL->Sumw2();
    TH1F* h_SS_BH_BH=new TH1F("h_SS_BH_BH","h_SS_BH_BH",60,60,120); h_SS_BH_BH->Sumw2();
    TH1F* h_SS_BH_EM=new TH1F("h_SS_BH_EM","h_SS_BH_EM",60,60,120); h_SS_BH_EM->Sumw2();
    TH1F* h_SS_BH_BM=new TH1F("h_SS_BH_BM","h_SS_BH_BM",60,60,120); h_SS_BH_BM->Sumw2();
    TH1F* h_SS_BH_EL=new TH1F("h_SS_BH_EL","h_SS_BH_EL",60,60,120); h_SS_BH_EL->Sumw2();
    TH1F* h_SS_BH_BL=new TH1F("h_SS_BH_BL","h_SS_BH_BL",60,60,120); h_SS_BH_BL->Sumw2();
    TH1F* h_SS_EM_EM=new TH1F("h_SS_EM_EM","h_SS_EM_EM",60,60,120); h_SS_EM_EM->Sumw2();
    TH1F* h_SS_EM_BM=new TH1F("h_SS_EM_BM","h_SS_EM_BM",60,60,120); h_SS_EM_BM->Sumw2();
    TH1F* h_SS_EM_EL=new TH1F("h_SS_EM_EL","h_SS_EM_EL",60,60,120); h_SS_EM_EL->Sumw2();
    TH1F* h_SS_EM_BL=new TH1F("h_SS_EM_BL","h_SS_EM_BL",60,60,120); h_SS_EM_BL->Sumw2();
    TH1F* h_SS_BM_BM=new TH1F("h_SS_BM_BM","h_SS_BM_BM",60,60,120); h_SS_BM_BM->Sumw2();
    TH1F* h_SS_BM_EL=new TH1F("h_SS_BM_EL","h_SS_BM_EL",60,60,120); h_SS_BM_EL->Sumw2();
    TH1F* h_SS_BM_BL=new TH1F("h_SS_BM_BL","h_SS_BM_BL",60,60,120); h_SS_BM_BL->Sumw2();
    TH1F* h_SS_EL_EL=new TH1F("h_SS_EL_EL","h_SS_EL_EL",60,60,120); h_SS_EL_EL->Sumw2();
    TH1F* h_SS_EL_BL=new TH1F("h_SS_EL_BL","h_SS_EL_BL",60,60,120); h_SS_EL_BL->Sumw2();
    TH1F* h_SS_BL_BL=new TH1F("h_SS_BL_BL","h_SS_BL_BL",60,60,120); h_SS_BL_BL->Sumw2();

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();

   for (Int_t i = 0; i < nentries_wtn; i++) {
	arbre->LoadTree(i);
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	TLorentzVector my_el1;
	my_el1.SetPtEtaPhiM(el_pt[0], el_eta[0], el_phi[0], 0.0);
        TLorentzVector my_el2;
        my_el2.SetPtEtaPhiM(el_pt[1], el_eta[1], el_phi[1], 0.0);

	if (!el_MVAIDisoWP80[0] or fabs(el_eta[0])>2.5 or !el_conversionveto[0] or fabs(el_dz[0])>0.1 or !el_chargeconsistent[0]) continue; //add sip2d
        if (!el_MVAIDisoWP80[0] or fabs(el_eta[0])>2.5 or !el_conversionveto[0] or fabs(el_dz[0])>0.1 or !el_chargeconsistent[1]) continue;
	if (my_el1.DeltaR(my_el2)<0.3) continue;
	if ((my_el1+my_el2).M()<60 or (my_el1+my_el2).M()>120) continue;
	if (year=="2018" and my_el1.Pt()<33 and my_el2.Pt()<33) continue;
        if (year=="2018" and my_el1.Pt()<33 and my_el2.Pt()<33) continue;
        if ((year=="2016pre" or year=="2016post") and my_el1.Pt()<26 and my_el2.Pt()<26) continue;

	bool is_BL_1 = false;
	bool is_EL_1 = false;
	bool is_BM_1 = false;
	bool is_EM_1 = false;
	bool is_BH_1 = false;
	bool is_EH_1 = false;
        bool is_BL_2 = false;
        bool is_EL_2 = false;
        bool is_BM_2 = false;
        bool is_EM_2 = false;
        bool is_BH_2 = false;
        bool is_EH_2 = false;

	if (my_el1.Pt()<25){
	   if (fabs(my_el1.Eta())<1.479) is_BL_1=true;
	   else is_EL_1=true;
	}
	else if (my_el1.Pt()<40){
           if (fabs(my_el1.Eta())<1.479) is_BM_1=true;
           else is_EM_1=true;
        }
	else{
           if (fabs(my_el1.Eta())<1.479) is_BH_1=true;
           else is_EH_1=true;
        }

        if (my_el2.Pt()<25){
           if (fabs(my_el2.Eta())<1.479) is_BL_2=true;
           else is_EL_2=true;
        }
        else if (my_el2.Pt()<40){
           if (fabs(my_el2.Eta())<1.479) is_BM_2=true;
           else is_EM_2=true;
        }
        else{
           if (fabs(my_el2.Eta())<1.479) is_BH_2=true;
           else is_EH_2=true;
        }

	float mee=(my_el1+my_el2).M();
	bool is_OS=(el_charge[0]*el_charge[1]<0);

	if (is_EH_1 and is_EH_2){
	   if (is_OS) h_OS_EH_EH->Fill(mee);
	   if (!is_OS) h_SS_EH_EH->Fill(mee);
	}
	if ((is_EH_1 and is_BH_2) or (is_EH_2 and is_BH_1)){
           if (is_OS) h_OS_EH_BH->Fill(mee);
           if (!is_OS) h_SS_EH_BH->Fill(mee);
        }
        if ((is_EH_1 and is_EM_2) or (is_EH_2 and is_EM_1)){
           if (is_OS) h_OS_EH_EM->Fill(mee);
           if (!is_OS) h_SS_EH_EM->Fill(mee);
        }
        if ((is_EH_1 and is_BM_2) or (is_EH_2 and is_BM_1)){
           if (is_OS) h_OS_EH_BM->Fill(mee);
           if (!is_OS) h_SS_EH_BM->Fill(mee);
        }
        if ((is_EH_1 and is_EL_2) or (is_EH_2 and is_EL_1)){
           if (is_OS) h_OS_EH_EL->Fill(mee);
           if (!is_OS) h_SS_EH_EL->Fill(mee);
        }
        if ((is_EH_1 and is_BL_2) or (is_EH_2 and is_BL_1)){
           if (is_OS) h_OS_EH_BL->Fill(mee);
           if (!is_OS) h_SS_EH_BL->Fill(mee);
        }

        if ((is_BH_1 and is_BH_2) or (is_BH_2 and is_BH_1)){
           if (is_OS) h_OS_BH_BH->Fill(mee);
           if (!is_OS)h_SS_BH_BH->Fill(mee);
        }
        if ((is_BH_1 and is_EM_2) or (is_BH_2 and is_EM_1)){
           if (is_OS) h_OS_BH_EM->Fill(mee);
           if (!is_OS) h_SS_BH_EM->Fill(mee);
        }
        if ((is_BH_1 and is_BM_2) or (is_BH_2 and is_BM_1)){
           if (is_OS) h_OS_BH_BM->Fill(mee);
           if (!is_OS) h_SS_BH_BM->Fill(mee);
        }
        if ((is_BH_1 and is_EL_2) or (is_BH_2 and is_EL_1)){
           if (is_OS) h_OS_BH_EL->Fill(mee);
           if (!is_OS) h_SS_BH_EL->Fill(mee);
        }
        if ((is_BH_1 and is_BL_2) or (is_BH_2 and is_BL_1)){
           if (is_OS) h_OS_BH_BL->Fill(mee);
           if (!is_OS) h_SS_BH_BL->Fill(mee);
        }

        if ((is_EM_1 and is_EM_2) or (is_EM_2 and is_EM_1)){
           if (is_OS) h_OS_EM_EM->Fill(mee);
           if (!is_OS) h_SS_EM_EM->Fill(mee);
        }
        if ((is_EM_1 and is_BM_2) or (is_EM_2 and is_BM_1)){
           if (is_OS) h_OS_EM_BM->Fill(mee);
           if (!is_OS) h_SS_EM_BM->Fill(mee);
        }
        if ((is_EM_1 and is_EL_2) or (is_EM_2 and is_EL_1)){
           if (is_OS) h_OS_EM_EL->Fill(mee);
           if (!is_OS) h_SS_EM_EL->Fill(mee);
        }
        if ((is_EM_1 and is_BL_2) or (is_EM_2 and is_BL_1)){
           if (is_OS) h_OS_EM_BL->Fill(mee);
           if (!is_OS) h_SS_EM_BL->Fill(mee);
        }

        if ((is_BM_1 and is_BM_2) or (is_BM_2 and is_BM_1)){
           if (is_OS) h_OS_BM_BM->Fill(mee);
           if (!is_OS) h_SS_BM_BM->Fill(mee);
        }
        if ((is_BM_1 and is_EL_2) or (is_BM_2 and is_EL_1)){
           if (is_OS) h_OS_BM_EL->Fill(mee);
           if (!is_OS) h_SS_BM_EL->Fill(mee);
        }
        if ((is_BM_1 and is_BL_2) or (is_BM_2 and is_BL_1)){
           if (is_OS) h_OS_BM_BL->Fill(mee);
           if (!is_OS) h_SS_BM_BL->Fill(mee);
        }

        if ((is_EL_1 and is_EL_2) or (is_EL_2 and is_EL_1)){
           if (is_OS) h_OS_EL_EL->Fill(mee);
           if (!is_OS) h_SS_EL_EL->Fill(mee);
        }
        if ((is_EL_1 and is_BL_2) or (is_EL_2 and is_BL_1)){
           if (is_OS) h_OS_EL_BL->Fill(mee);
           if (!is_OS) h_SS_EL_BL->Fill(mee);
        }

        if ((is_BL_1 and is_BL_2) or (is_BL_2 and is_BL_1)){
           if (is_OS) h_OS_BL_BL->Fill(mee);
           if (!is_OS) h_SS_BL_BL->Fill(mee);
        }


    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    h_OS_EH_EH->Write();
    h_OS_EH_BH->Write();
    h_OS_EH_EM->Write();
    h_OS_EH_BM->Write();
    h_OS_EH_EL->Write();
    h_OS_EH_BL->Write();
    h_OS_BH_BH->Write();
    h_OS_BH_EM->Write();
    h_OS_BH_BM->Write();
    h_OS_BH_EL->Write();
    h_OS_BH_BL->Write();
    h_OS_EM_EM->Write();
    h_OS_EM_BM->Write();
    h_OS_EM_EL->Write();
    h_OS_EM_BL->Write();
    h_OS_BM_BM->Write();
    h_OS_BM_EL->Write();
    h_OS_BM_BL->Write();
    h_OS_EL_EL->Write();
    h_OS_EL_BL->Write();
    h_OS_BL_BL->Write();

    h_SS_EH_EH->Write();
    h_SS_EH_BH->Write();
    h_SS_EH_EM->Write();
    h_SS_EH_BM->Write();
    h_SS_EH_EL->Write();
    h_SS_EH_BL->Write();
    h_SS_BH_BH->Write();
    h_SS_BH_EM->Write();
    h_SS_BH_BM->Write();
    h_SS_BH_EL->Write();
    h_SS_BH_BL->Write();
    h_SS_EM_EM->Write();
    h_SS_EM_BM->Write();
    h_SS_EM_EL->Write();
    h_SS_EM_BL->Write();
    h_SS_BM_BM->Write();
    h_SS_BM_EL->Write();
    h_SS_BM_BL->Write();
    h_SS_EL_EL->Write();
    h_SS_EL_BL->Write();
    h_SS_BL_BL->Write();

    fout->Close();
} 



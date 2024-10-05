#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <map>
#include <string>
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TSystem.h"
#include "TMath.h" //M_PI is in TMath
#include "TRandom3.h"
#include <TLorentzVector.h>

float norm_F(float x, float y){
    return sqrt(x*x+y*y);
}

float TMass_F(float pt3lep, float px3lep, float py3lep, float met, float metPhi) {
    return sqrt(pow(pt3lep + met, 2) - pow(px3lep + met * cos(metPhi), 2) - pow(py3lep + met * sin(metPhi), 2));
}


void WriteHistToFileEMu(TFile* myfile, std::vector<TH1F*> hist, std::string name, TString dir_name, TString uncertainties[1], bool isMC, int nbhist, bool write_uncertainties){
    TString postfix="";
    TDirectory *dir =myfile->mkdir(dir_name);
    dir->cd();
    if (!write_uncertainties) nbhist=1;
    for (int k=0; k<nbhist; ++k){
       for (int j=0; j<hist[k]->GetSize()-1; ++j){
         if (hist[k]->GetBinContent(j)<0) hist[k]->SetBinContent(j,0);
       }
       //include overflow in last bin
       hist[k]->SetBinContent(hist[k]->GetSize()-2,hist[k]->GetBinContent(hist[k]->GetSize()-2)+hist[k]->GetBinContent(hist[k]->GetSize()-1));
       hist[k]->SetBinError(hist[k]->GetSize()-2,pow(hist[k]->GetBinError(hist[k]->GetSize()-2)*hist[k]->GetBinError(hist[k]->GetSize()-2)+hist[k]->GetBinError(hist[k]->GetSize()-1)*hist[k]->GetBinError(hist[k]->GetSize()-1),0.5));
       hist[k]->SetBinContent(hist[k]->GetSize()-1,0);
       hist[k]->SetBinError(hist[k]->GetSize()-1,0);

       postfix=uncertainties[k];
       hist[k]->SetName(name.c_str()+postfix);
       hist[k]->Write();
    }
}

void WriteHistToFileWZCR(TFile* myfile, std::vector<TH1F*> hist, std::string name, TString dir_name, TString uncertainties[1], bool isMC, int nbhist, bool write_uncertainties){
    TString postfix="";
    TDirectory *dir =myfile->mkdir(dir_name);
    dir->cd();
    if (!write_uncertainties) nbhist=1;
    for (int k=0; k<nbhist; ++k){
       for (int j=0; j<hist[k]->GetSize()-1; ++j){
         if (hist[k]->GetBinContent(j)<0) hist[k]->SetBinContent(j,0);
       }
       //include overflow in last bin
       hist[k]->SetBinContent(hist[k]->GetSize()-2,hist[k]->GetBinContent(hist[k]->GetSize()-2)+hist[k]->GetBinContent(hist[k]->GetSize()-1));
       hist[k]->SetBinError(hist[k]->GetSize()-2,pow(hist[k]->GetBinError(hist[k]->GetSize()-2)*hist[k]->GetBinError(hist[k]->GetSize()-2)+hist[k]->GetBinError(hist[k]->GetSize()-1)*hist[k]->GetBinError(hist[k]->GetSize()-1),0.5));
       hist[k]->SetBinContent(hist[k]->GetSize()-1,0);
       hist[k]->SetBinError(hist[k]->GetSize()-1,0);

       postfix=uncertainties[k];
       hist[k]->SetName(name.c_str()+postfix);
       hist[k]->Write();
    }
}


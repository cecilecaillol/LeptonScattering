#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <stdio.h>
#include <TDirectoryFile.h>
#include <TRandom3.h>
#include "TLorentzVector.h"
#include "TString.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TFile.h"

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooVoigtian.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TRandom.h"
#include "RooCMSShape.h"

using namespace RooFit;

using namespace std;

int main(int argc, char** argv) {


    std::string year = *(argv + 1);
    std::string input = *(argv + 2);
    std::string output = *(argv + 3);
    std::string sample = *(argv + 4);

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(10);

    TFile *fin = TFile::Open(input.c_str(), "READ");

    TH1F* eff = new TH1F("eff","eff",21,0,21);

    //TString sbins[21]={"BL_BL","BM_BL","BM_BM","BH_BL","BH_BM","BH_BH","EL_EL","EM_EL","EM_EM","EH_EL","EH_EM","EH_BH","EL_BL","BM_EL","EM_BL","EM_BM","BH_EL","EH_BL","BH_EM","EH_BM","EH_EH"};
    TString sbins[14]={"BH_BH","BH_BL","BH_BM","BH_EL","BH_EM","BM_BL","BM_BM","BM_EL","EH_BH","EH_BL","EH_BM","EH_EM","EM_BL","EM_BM"};
    int nbins=14;

    for (int j=0; j<nbins; ++j){
       TH1F *h_pass = (TH1F*) fin->Get("h_SS_"+sbins[j]);
       TH1F *h_fail = (TH1F*) fin->Get("h_OS_"+sbins[j]);

       RooRealVar Mee("Mee", "Mee", 65, 115);
       RooDataHist dh_pass("dh_pass", "dh_pass", Mee, Import(*h_pass));
       RooDataHist dh_fail("dh_fail", "dh_fail", Mee, Import(*h_fail));

       RooPlot *frame = Mee.frame(Title("Pass"));
       dh_pass.plotOn(frame);
       RooRealVar mean1P("mean1P", "mean1P", 90, 85, 95);
       RooRealVar mean2P("mean2P", "mean2P", 90, 85, 95);
       RooRealVar width("width", "width", 2.495,2.495,2.495);
       RooRealVar sigma1P("sigma1P", "sigma1P", 2,0,5);
       float max_sigma2P=6;
       if (sbins[j]=="BH_BM"){ max_sigma2P=10;}
       if (year!="2018" and sbins[j]=="BM_BL"){ max_sigma2P=4;}
       RooRealVar sigma2P("sigma2P", "sigma2P", 4,2,max_sigma2P);
       RooVoigtian voigt1P("voigt1P","voigt1P", Mee, mean1P, width, sigma1P);
       RooVoigtian voigt2P("voigt2P","voigt2P", Mee, mean2P, width, sigma2P);
       RooRealVar fracSP("fracSP", "fracSP", 0.5,0.0,1.0);
       RooAddPdf signalP("signalP","signalP", {voigt1P,voigt2P}, fracSP);

       RooRealVar normSP("normSP", "normSP", 100000. ,0.0,100000000.0);
       float max3P=1000000.0;
       //if (bins_pt[j]>=75 and bins_pt[j]<5000){ max3P=1000.;}
       RooRealVar frac3P("frac3P", "frac3P", 0. ,0.0,max3P);

       /*if (bins_pt[j]>=10 and bins_pt[j]<5000){
          RooRealVar lpP("lpP", "lpP", 0.0, -1, 1.1);
          RooExponential expP("expP","expP",Mee,lpP);
          RooAddPdf modelP("sigmodelP","sigmodelP", {signalP,expP}, {normSP,frac3P});
          modelP.fitTo(dh_pass);
          modelP.plotOn(frame);
          modelP.plotOn(frame,Components("expP"), LineStyle(kDashed));
       }*/
       //else{
          float initial_alphaP=50.0; float initial_betaP=0.01; float initial_gammaP=0.0; float initial_frac3P=1000.0;float max_alphaP=160.0;
          //if (bins_pt[j]==50){ initial_alphaP=90; initial_betaP=0.091; initial_gammaP=0.10; max_alphaP=95.0;}
          //if (bins_pt[j]>=20 and bins_pt[j]<30){ initial_alphaP=80; initial_betaP=0.1; initial_gammaP=0.30;}
          //if (bins_pt[j]>=20 and bins_pt[j]<30){ initial_frac3P=0;}
          if (sbins[j]=="BH_EL"){ initial_alphaP=90; initial_betaP=0.091; initial_gammaP=0.10; max_alphaP=95.0;}
          if (sbins[j]=="BM_BM" and year!="2018"){ initial_alphaP=90; initial_betaP=0.091; initial_gammaP=0.10; max_alphaP=95.0;}
          if (sbins[j]=="BH_EM"){ initial_alphaP=160; initial_frac3P=0;}
          if (sbins[j]=="EH_BM"){ initial_alphaP=160; initial_frac3P=0;}
          if (sbins[j]=="EM_BM"){ initial_alphaP=160; initial_frac3P=0;}
          if (sbins[j]=="EM_BL" and year!="2018"){ initial_alphaP=60; initial_betaP=0.091; initial_gammaP=0.10; max_alphaP=95.0;}
          if (sbins[j]=="EM_BL" and year=="2016post"){ initial_alphaP=70; initial_betaP=0.02; initial_gammaP=0.00; max_alphaP=195.0;}
          if (sbins[j]=="BH_BM" and year!="2018"){ initial_alphaP=80; initial_betaP=0.091; initial_gammaP=0.10; initial_frac3P=0.5;}
          if (sbins[j]=="EH_BM" and year!="2018"){ initial_alphaP=60; initial_betaP=0.091; initial_gammaP=0.10; initial_frac3P=0.5;}
          if (sbins[j]=="EH_BH" and year!="2018"){ initial_alphaP=60; initial_betaP=0.091; initial_gammaP=0.10; initial_frac3P=0.5;}
          if (sbins[j]=="BH_BH" and year=="2016post"){ initial_alphaP=90; initial_betaP=0.091; initial_gammaP=0.10; max_alphaP=95.0;}
          if (sbins[j]=="EM_BM" and year=="2016post"){ initial_alphaP=90; initial_betaP=0.091; initial_gammaP=0.10; max_alphaP=95.0;}
          if (sbins[j]=="EM_BM" and year=="2017"){ initial_alphaP=90; initial_betaP=0.091; initial_gammaP=0.10; max_alphaP=95.0;}
          if (sbins[j]=="BH_BM" and year=="2017"){ initial_alphaP=70; initial_betaP=0.091; initial_gammaP=0.10; max_alphaP=95.0;}
          if (sbins[j]=="BH_BH" and year=="2017"){ initial_alphaP=100; initial_betaP=0.02; initial_gammaP=0.02; max_alphaP=135.0;}
          if (sbins[j]=="EH_BM" and year=="2017"){ initial_alphaP=70; initial_betaP=0.091; initial_gammaP=0.10; max_alphaP=95.0;}
          if (sbins[j]=="BM_BM" and year=="2017"){ initial_alphaP=70; initial_betaP=0.091; initial_gammaP=0.10; max_alphaP=95.0;}
          if (sbins[j]=="EM_BL" and year=="2017"){ initial_alphaP=70; initial_betaP=0.091; initial_gammaP=0.10; max_alphaP=95.0;}
          RooRealVar alphaP("alphaP", "alphaP", initial_alphaP, 60.0, max_alphaP);
          RooRealVar betaP("betaP", "betaP", initial_betaP, 0.05, 0.2);
          RooRealVar gammaP("gammaP", "gammaP", initial_gammaP,-1,  2);
          RooRealVar peakP("peakP", "peakP", 90,90,90);
          RooCMSShape expP("expP", "expP", Mee, alphaP, betaP, gammaP, peakP);
          RooAddPdf modelP("sigmodelP","sigmodelP", {signalP,expP}, {normSP,frac3P});
          modelP.fitTo(dh_pass);
          modelP.plotOn(frame);
          modelP.plotOn(frame,Components("expP"), LineStyle(kDashed));
       //}*/

       RooPlot *frame2 = Mee.frame(Title("Fail"));
       dh_fail.plotOn(frame2);
       float minmean=80;
       float maxmean=105;
       float nommean1=90;
       float nommean2=90;
       //if (bins_pt[j]==25 and bins_pt[j+1]==35){ minmean=85; }
       //if (bins_pt[j]==100) { minmean=88; maxmean=92;}
       //if (bins_pt[j]==50) { nommean1=89; nommean2=100; minmean=85; maxmean=105;}
       RooRealVar mean1F("mean1F", "mean1F", nommean1, minmean, maxmean);
       RooRealVar mean2F("mean2F", "mean2F", nommean2, minmean, maxmean);
       RooRealVar sigma1F("sigma1F", "sigma1F", 1.0,0,5);
       RooRealVar sigma2F("sigma2F", "sigma2F", 3.5,2,10);
       RooVoigtian voigt1F("voigt1F","voigt1F", Mee, mean1F, width, sigma1F);
       RooVoigtian voigt2F("voigt2F","voigt2F", Mee, mean2F, width, sigma2F);
       RooRealVar fracSF("fracSF", "fracSF", 0.5,0.0,1.0);
       RooAddPdf signalF("signalF","signalF", {voigt1F,voigt2F}, fracSF);

       float nom_norm=100000.;
       //if (bins_pt[j]==100) { nom_norm=100.0;}
       RooRealVar normSF("normSF", "normSF", nom_norm ,0.0,100000000.0);
       RooRealVar frac3F("frac3F", "frac3F", 0. ,0.0,1000000.0);
       float minalpha=50;
       float maxalpha=160;
       float nomalpha=100;
       float nomgamma=0.01;
       float maxgamma=1.0;
       float nombeta=0.1;
       float maxbeta=0.2;
       if (sbins[j]=="BM_BL" and year!="2018"){ nomalpha=90; nombeta=0.091; nomgamma=0.10; maxalpha=95.0;}
       if (sbins[j]=="BM_BM" and year=="2017"){ nomalpha=90; nombeta=0.091; nomgamma=0.10; maxalpha=95.0;}
       if (sbins[j]=="EM_BL" and year=="2017"){ nomalpha=90; nombeta=0.091; nomgamma=0.10; maxalpha=95.0;}
       /*if (bins_pt[j]>=50 and bins_pt[j]<100){minalpha=60; maxalpha=110; nomalpha=80;}
       if (bins_pt[j]==25 and bins_pt[j+1]==35){minalpha=60; maxalpha=160; nomalpha=120; nomgamma=0.8;}
       if (bins_pt[j]==50){ nomalpha=90; maxalpha=95.0;}
       if (bins_pt[j]==100){ minalpha=110; nomalpha=125; maxalpha=160.0; nomgamma=1.4; maxgamma=2.0; nombeta=0.3, maxbeta=1.0;}*/

       if (sbins[j]!="BM_BM" and sbins[j]!="BH_BL" and sbins[j]!="BM_BL" and sbins[j]!="EH_BH"){
          RooRealVar lpF("lpF", "lpF", -0.1, -1, 1.1);
          RooExponential expF("expF","expF",Mee,lpF);
          RooAddPdf modelF("sigmodelF","sigmodelF", {signalF,expF}, {normSF,frac3F});
          modelF.fitTo(dh_fail);
          modelF.plotOn(frame2);
          modelF.plotOn(frame2,Components("expF"), LineStyle(kDashed));
       }
       else{
          RooRealVar alphaF("alphaF", "alphaF", nomalpha, minalpha, maxalpha);
          RooRealVar betaF("betaF", "betaF", nombeta, 0.05, maxbeta);
          RooRealVar gammaF("gammaF", "gammaF", nomgamma, -2, maxgamma);
          RooRealVar peakF("peakF", "peakF", 90,90,90);
          RooCMSShape expF("expF", "expF", Mee, alphaF, betaF, gammaF, peakF);
          RooAddPdf modelF("sigmodelF","sigmodelF", {signalF,expF}, {normSF,frac3F});
          modelF.fitTo(dh_fail);
          modelF.plotOn(frame2);
          modelF.plotOn(frame2,Components("expF"), LineStyle(kDashed));
       }

       TCanvas *c = new TCanvas("rf102_dataimport", "rf102_dataimport", 1000, 800);
       c->Divide(2,1);
       c->cd(1);
       gPad->SetLeftMargin(0.15);
       frame->GetYaxis()->SetTitleOffset(1.4);
       frame->Draw();
       c->cd(2);
       gPad->SetLeftMargin(0.15);
       frame2->GetYaxis()->SetTitleOffset(1.4);
       frame2->Draw();

       cout<<"signal pass: "<<normSP.getVal()<<endl;
       cout<<"signal fail: "<<normSF.getVal()<<endl;
       float efficiency=(normSP.getVal())/(normSP.getVal()+normSF.getVal());
       cout<<"efficiency: "<<efficiency<<endl;
       float err_efficiency=efficiency*(normSP.getError())/(normSP.getVal());
       cout<<"err efficiency: "<<err_efficiency<<endl;

       TPaveText categ  = TPaveText(0.05, 0.84+0.013, 0.95, 0.84+0.155, "NDC");
       categ.SetBorderSize(   0 );
       categ.SetFillStyle(    0 );
       categ.SetTextAlign(   12 );
       categ.SetTextSize ( 0.035 );
       categ.SetTextColor(    1 );
       categ.SetTextFont (   42 );
       categ.AddText(sbins[j]);
       c->cd();
       categ.Draw("same");
       //categ.AddText("eff = "+to_string(efficiency));
       //categ.Draw("same");

       c->SaveAs("plots_chargemisid_"+year+"/fits_"+sample+"_"+sbins[j]+".png");

       eff->SetBinContent(j+1,efficiency);
       eff->SetBinError(j+1,err_efficiency);
    }

    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();
    eff->Write();
    fout->Close();
} 

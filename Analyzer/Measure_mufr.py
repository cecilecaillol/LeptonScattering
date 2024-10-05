def add_lumi(year):
    lowX=0.55
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.055)
    lumi.SetTextFont (   42 )
    if (year=="2018"): lumi.AddText("2018, 60 fb^{-1} (13 TeV)")
    if (year=="2017"): lumi.AddText("2017, 41 fb^{-1} (13 TeV)")
    if (year=="2016"): lumi.AddText("2016, 36 fb^{-1} (13 TeV)")
    if (year=="2016pre"): lumi.AddText("2016 preVFP, 20 fb^{-1} (13 TeV)")
    if (year=="2016post"): lumi.AddText("2016 postVFP, 16 fb^{-1} (13 TeV)")
    return lumi

def add_CMS():
    lowX=0.16
    lowY=0.835
    lumi  = ROOT.TPaveText(0.1, lowY+0.06, 0.2, lowY+0.16, "NDC")
    lumi.SetTextFont(61)
    lumi.SetTextSize(0.065)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("CMS")
    return lumi

def add_Supplementary():
    lowX=0.32
    lowY=0.825
    lumi  = ROOT.TPaveText(0.2, lowY+0.06, 0.45, lowY+0.16, "NDC")
    lumi.SetTextFont(42)
    lumi.SetTextSize(0.05)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("Work in progress")
    return lumi

def make_legend():
        output = ROOT.TLegend(0.4, 0.5, 0.92, 0.86, "", "brNDC")
        output.SetNColumns(2)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        return output


if __name__ == "__main__":

    import ROOT
    import argparse

    ROOT.gStyle.SetOptStat(0)

    is_control=1

    parser = argparse.ArgumentParser()
    parser.add_argument('--year')
    options = parser.parse_args()

    fZZ=ROOT.TFile("output_mufr_"+options.year+"/ZZ4L.root","r")
    fWZ=ROOT.TFile("output_mufr_"+options.year+"/WZ3LNu.root","r")
    fData=ROOT.TFile("output_mufr_"+options.year+"/SingleMuon.root","r")
    fout=ROOT.TFile("output_mufr_"+options.year+"/mufr.root","recreate")

    hBanti=fData.Get("pt_antimu_barrel").Clone()
    hBanti.Add(fWZ.Get("pt_antimu_barrel"),-1)
    hBanti.Add(fZZ.Get("pt_antimu_barrel"),-1)

    hBiso=fData.Get("pt_isomu_barrel").Clone()
    hBiso.Add(fWZ.Get("pt_isomu_barrel"),-1)
    hBiso.Add(fZZ.Get("pt_isomu_barrel"),-1)

    hBiso.Divide(hBanti)

    c=ROOT.TCanvas("canvas","",0,0,800,600)
    c.cd()
    hBiso.SetMaximum(1.5)
    hBiso.SetMinimum(0.0)
    hBiso.Draw("e")
    hBiso.SetTitle("")
    hBiso.GetXaxis().SetTitle("#mu p_{T} (GeV)")
    hBiso.GetYaxis().SetTitle("f_#mu")
    total1 = ROOT.TF1( 'total1', 'expo(0)+pol1(2)', 5, 100 )
    total1.SetLineColor( ROOT.kMagenta )
    hBiso.Fit(total1,'R')
    total1.SetName("fit_mufr_barrel")
    lumi=add_lumi(options.year)
    lumi.Draw("same")
    cms=add_CMS()
    cms.Draw("same")
    sup=add_Supplementary()
    sup.Draw("same")
    c.SaveAs("mufr_barrel_"+options.year+".png")




    hEanti=fData.Get("pt_antimu_endcaps").Clone()
    hEanti.Add(fWZ.Get("pt_antimu_endcaps"),-1)
    hEanti.Add(fZZ.Get("pt_antimu_endcaps"),-1)

    hEiso=fData.Get("pt_isomu_endcaps").Clone()
    hEiso.Add(fWZ.Get("pt_isomu_endcaps"),-1)
    hEiso.Add(fZZ.Get("pt_isomu_endcaps"),-1)

    hEiso.Divide(hEanti)

    c=ROOT.TCanvas("canvas","",0,0,800,600)
    c.cd()
    hEiso.SetMaximum(1.5)
    hEiso.SetMinimum(0.0)
    hEiso.Draw("e")
    hEiso.SetTitle("")
    hEiso.GetXaxis().SetTitle("#mu p_{T} (GeV)")
    hEiso.GetYaxis().SetTitle("f_{#mu}")
    total2 = ROOT.TF1( 'total2', 'expo(0)+pol1(2)', 5, 100 )
    total2.SetLineColor( ROOT.kMagenta )
    hEiso.Fit(total2,'R')
    total2.SetName("fit_mufr_endcaps")
    lumi=add_lumi(options.year)
    lumi.Draw("same")
    cms=add_CMS()
    cms.Draw("same")
    sup=add_Supplementary()
    sup.Draw("same")
    c.SaveAs("mufr_endcaps_"+options.year+".png")


    fout.cd()
    hBiso.SetName("mufr_barrel")
    hBiso.Write()
    total1.Write()

    hEiso.SetName("mufr_endcaps")
    hEiso.Write()
    total2.Write()

    h1anti=fData.Get("h_ntracks_anti").Clone()
    h1anti.Sumw2()
    h1anti.Add(fWZ.Get("h_ntracks_anti"),-1)
    h1anti.Add(fZZ.Get("h_ntracks_anti"),-1)

    h1iso=fData.Get("h_ntracks_iso").Clone()
    h1iso.Sumw2()
    h1iso.Add(fWZ.Get("h_ntracks_iso"),-1)
    h1iso.Add(fZZ.Get("h_ntracks_iso"),-1)

    h1iso.Divide(h1anti)
    average=h1iso.GetBinContent(1)
    for k in range(1,h1iso.GetSize()):
       h1iso.SetBinContent(k,h1iso.GetBinContent(k)/average)
       h1iso.SetBinError(k,h1iso.GetBinError(k)/average)
    fout.cd()
    h1iso.SetName("FRNT")
    h1iso.Write()

    c1=ROOT.TCanvas("canvas","",0,0,800,600)
    c1.cd()
    h1iso.SetTitle("")
    h1iso.SetMarkerStyle(20)
    h1iso.SetMarkerColor(1)
    h1iso.SetLineColor(1)
    h1iso.GetXaxis().SetTitle("N_{#lower[-0.25]{tracks}}")
    h1iso.GetYaxis().SetTitle("f_{#mu} correction ")
    h1iso.GetXaxis().SetTitleSize(0.06)
    h1iso.GetYaxis().SetTitleSize(0.06)
    h1iso.GetXaxis().SetLabelSize(0.04)
    h1iso.GetYaxis().SetLabelSize(0.04)
    h1iso.GetYaxis().SetTitleOffset(0.8)
    h1iso.GetXaxis().SetTitleOffset(0.7)
    h1iso.Draw("e0p")
    h1iso.GetXaxis().SetRangeUser(0,100)
    h1iso.SetMinimum(0.5)
    lumi=add_lumi(options.year)
    lumi.Draw("same")
    cms=add_CMS()
    cms.Draw("same")
    sup=add_Supplementary()
    sup.Draw("same")
    total = ROOT.TF1( 'total', 'pol5', 0, 100 )
    total.SetLineColor( ROOT.kMagenta )
    h1iso.Fit(total,'R')
    total.SetName("fit_frnt")

    hint = ROOT.TH1D("hint","Fitted Gaussian with .68 conf.band", 100, 0, 100);
    (ROOT.TVirtualFitter.GetFitter()).GetConfidenceIntervals(hint,0.68);
    hint.SetStats(False);
    hint.SetFillColor(ROOT.kCyan);
    hint.SetFillStyle(3001);
    hint.Draw("e3 same");
    print hint.GetBinError(1)/hint.GetBinContent(1);

    total.Draw("SAME")
    h1iso.Draw("PSAME")

    leg  = ROOT.TLegend(0.13, 0.15, 0.8, 0.3, "", "brNDC");
    leg.SetNColumns(2);
    leg.SetLineWidth(0);
    leg.SetLineStyle(0);
    leg.SetFillStyle(0);
    leg.SetBorderSize(0);
    leg.SetTextFont(42);
    leg.AddEntry(total, "Polynomial fit", "l");
    leg.AddEntry(hint, "Fit uncertainty", "f");
    leg.Draw("same");
    fout.cd()
    total.Write()
    c1.cd()
    c1.Modified()
    c1.SaveAs("mufr_nt_"+options.year+".png")

    names=["pt_antimu_endcaps","pt_isomu_endcaps","pt_antimu_barrel","pt_isomu_barrel"]
    for k in range(0,len(names)):
       c=ROOT.TCanvas("canvas","",0,0,800,600)
       c.cd()
       #c.SetLogy()
       data=fData.Get(names[k])
       wz=fWZ.Get(names[k])
       zz=fZZ.Get(names[k])
       data.SetMarkerStyle(20)
       wz.SetFillColor(ROOT.TColor.GetColor("#5790fc"))
       zz.SetFillColor(ROOT.TColor.GetColor("#7a21dd"))
       stack=ROOT.THStack("stack","stack")
       stack.Add(wz)
       stack.Add(zz)
       #data.SetMinimum(1.0)
       data.SetTitle("")
       data.GetXaxis().SetTitle("#mu p_{T} (GeV)")
       data.GetYaxis().SetTitle("Events")
       c.SetLogy()

       data.SetMinimum(1.0)
       data.Draw("e")
       stack.Draw("histsame")

       legende=make_legend()
       legende.AddEntry(data,"Observed","elp")
       legende.AddEntry(wz,"WZ","f")
       legende.AddEntry(zz,"ZZ","f")
       legende.Draw()

       lumi=add_lumi(options.year)
       lumi.Draw("same")
       cms=add_CMS()
       cms.Draw("same")
       sup=add_Supplementary()
       sup.Draw("same")

       c.SaveAs("mufr_"+names[k]+"_"+options.year+".png")



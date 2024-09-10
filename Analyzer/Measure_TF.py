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


if __name__ == "__main__":

    import ROOT
    import argparse

    is_control=1

    parser = argparse.ArgumentParser()
    parser.add_argument('--year')
    options = parser.parse_args()

    year4=options.year
    if options.year=="2016pre": year4="2016preVFP"
    if options.year=="2016post": year4="2016postVFP"

    postfixName=[""]

    nbhist=1 

    fZZ=ROOT.TFile("output_emu_"+options.year+"/ZZ4L.root","r")
    fWZ=ROOT.TFile("output_emu_"+options.year+"/WZ3LNu.root","r")
    fData=ROOT.TFile("output_emu_"+options.year+"/MuonEG.root","r")
    fout=ROOT.TFile("tf.root","recreate")

    hBanti=fData.Get("h_CR_anti")
    hBanti.Add(fWZ.Get("h_CR_anti"),-1)
    hBanti.Add(fZZ.Get("h_CR_anti"),-1)

    hBiso=fData.Get("h_CR_iso")
    hBiso.Add(fWZ.Get("h_CR_iso"),-1)
    hBiso.Add(fZZ.Get("h_CR_iso"),-1)

    hBiso.Divide(hBanti)

    c=ROOT.TCanvas("canvas","",0,0,800,600)
    c.cd()
    hBiso.SetMinimum(0.0)
    #hBiso.SetMaximum(0.5)
    hBiso.Draw("colz")
    hBiso.SetName("tf")
    c.SaveAs("tf.png")

    fout.cd()
    hBiso.Write()


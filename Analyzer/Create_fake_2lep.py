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

    fZZ=ROOT.TFile("output_2lep_"+options.year+"/ZZ4L.root","r")
    fWZ=ROOT.TFile("output_2lep_"+options.year+"/WZ3LNu.root","r")
    fZG=ROOT.TFile("output_2lep_"+options.year+"/ZG.root","r")
    fTTZ=ROOT.TFile("output_2lep_"+options.year+"/TTZ.root","r")
    fTTW=ROOT.TFile("output_2lep_"+options.year+"/TTW.root","r")
    fWWW=ROOT.TFile("output_2lep_"+options.year+"/WWW.root","r")
    fData=ROOT.TFile("output_2lep_"+options.year+"/Data.root","r")
    fout=ROOT.TFile("output_2lep_"+options.year+"/nonprompt.root","recreate")

    ncat=9
    if is_control==0: 
	ncat=9
        nbhist=1

    for j in range(0,ncat):
       dir0=fout.mkdir("em2l_"+str(j))

       for k in range(0,nbhist):
          postfix=postfixName[k]

	  hPF=fData.Get("em2l_"+str(j)+"_anti1/data_obs"+postfix).Clone()
          hPF.Add(fWZ.Get("em2l_"+str(j)+"_anti1/WZ3LNu"),-1)
          hPF.Add(fZZ.Get("em2l_"+str(j)+"_anti1/ZZ4L"),-1)
          hPF.Add(fZG.Get("em2l_"+str(j)+"_anti1/VG"),-1)
          hPF.Add(fWWW.Get("em2l_"+str(j)+"_anti1/VVV"),-1)
          hPF.Add(fTTZ.Get("em2l_"+str(j)+"_anti1/TTV"),-1)
          hPF.Add(fTTW.Get("em2l_"+str(j)+"_anti1/TTV"),-1)

          hFP=fData.Get("em2l_"+str(j)+"_anti2/data_obs"+postfix).Clone()
          hFP.Add(fWZ.Get("em2l_"+str(j)+"_anti2/WZ3LNu"),-1)
          hFP.Add(fZZ.Get("em2l_"+str(j)+"_anti2/ZZ4L"),-1)
          hFP.Add(fZG.Get("em2l_"+str(j)+"_anti2/VG"),-1)
          hFP.Add(fWWW.Get("em2l_"+str(j)+"_anti2/VVV"),-1)
          hFP.Add(fTTZ.Get("em2l_"+str(j)+"_anti2/TTV"),-1)
          hFP.Add(fTTW.Get("em2l_"+str(j)+"_anti2/TTV"),-1)

          hFF=fData.Get("em2l_"+str(j)+"_anti0/data_obs"+postfix).Clone()
          hFF.Add(fWZ.Get("em2l_"+str(j)+"_anti0/WZ3LNu"),-1)
          hFF.Add(fZZ.Get("em2l_"+str(j)+"_anti0/ZZ4L"),-1)
          hFF.Add(fZG.Get("em2l_"+str(j)+"_anti0/VG"),-1)
          hFF.Add(fWWW.Get("em2l_"+str(j)+"_anti0/VVV"),-1)
          hFF.Add(fTTZ.Get("em2l_"+str(j)+"_anti0/TTV"),-1)
          hFF.Add(fTTW.Get("em2l_"+str(j)+"_anti0/TTV"),-1)

          h0=hPF.Clone()
          h0.Add(hFP)
          h0.Add(hFF,-1)


          hPFR=fData.Get("em2lR_"+str(j)+"_anti1/data_obs"+postfix).Clone()
          hPFR.Add(fWZ.Get("em2lR_"+str(j)+"_anti1/WZ3LNu"),-1)
          hPFR.Add(fZZ.Get("em2lR_"+str(j)+"_anti1/ZZ4L"),-1)
          hPFR.Add(fZG.Get("em2lR_"+str(j)+"_anti1/VG"),-1)
          hPFR.Add(fWWW.Get("em2lR_"+str(j)+"_anti1/VVV"),-1)
          hPFR.Add(fTTZ.Get("em2lR_"+str(j)+"_anti1/TTV"),-1)
          hPFR.Add(fTTW.Get("em2lR_"+str(j)+"_anti1/TTV"),-1)

          hFPR=fData.Get("em2lR_"+str(j)+"_anti2/data_obs"+postfix).Clone()
          hFPR.Add(fWZ.Get("em2lR_"+str(j)+"_anti2/WZ3LNu"),-1)
          hFPR.Add(fZZ.Get("em2lR_"+str(j)+"_anti2/ZZ4L"),-1)
          hFPR.Add(fZG.Get("em2lR_"+str(j)+"_anti2/VG"),-1)
          hFPR.Add(fWWW.Get("em2lR_"+str(j)+"_anti2/VVV"),-1)
          hFPR.Add(fTTZ.Get("em2lR_"+str(j)+"_anti2/TTV"),-1)
          hFPR.Add(fTTW.Get("em2lR_"+str(j)+"_anti2/TTV"),-1)

          hFFR=fData.Get("em2lR_"+str(j)+"_anti0/data_obs"+postfix).Clone()
          hFFR.Add(fWZ.Get("em2lR_"+str(j)+"_anti0/WZ3LNu"),-1)
          hFFR.Add(fZZ.Get("em2lR_"+str(j)+"_anti0/ZZ4L"),-1)
          hFFR.Add(fZG.Get("em2lR_"+str(j)+"_anti0/VG"),-1)
          hFFR.Add(fWWW.Get("em2lR_"+str(j)+"_anti0/VVV"),-1)
          hFFR.Add(fTTZ.Get("em2lR_"+str(j)+"_anti0/TTV"),-1)
          hFFR.Add(fTTW.Get("em2lR_"+str(j)+"_anti0/TTV"),-1)

          h0R=hPFR.Clone()
          h0R.Add(hFPR)
          h0R.Add(hFFR,-1)
   
	  #for k in range(1,hPF.GetSize()):
	  #   if hPF.GetBinContent(k)+hFP.GetBinContent(k)<hFF.GetBinContent(k): h0.SetBinContent(k,hFF.GetBinContent(k))

          fout.cd()
          dir0.cd()
          h0R.SetName("nonprompt"+postfix)
          h0R.Scale(h0.Integral()/h0R.Integral())
          h0R.Write()



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

    fZZ=ROOT.TFile("output_OS_"+options.year+"/ZZ4L.root","r")
    fWZ=ROOT.TFile("output_OS_"+options.year+"/WZ3LNu.root","r")
    fTTZ=ROOT.TFile("output_OS_"+options.year+"/TTZ.root","r")
    fTTW=ROOT.TFile("output_OS_"+options.year+"/TTW.root","r")
    fWWW=ROOT.TFile("output_OS_"+options.year+"/WWW.root","r")
    fData=ROOT.TFile("output_OS_"+options.year+"/Data.root","r")
    fout=ROOT.TFile("output_OS_"+options.year+"/nonprompt.root","recreate")

    ncat=9
    if is_control==0: 
	ncat=9
        nbhist=1

    for j in range(0,ncat):
       dir0=fout.mkdir("em_"+str(j))

       for k in range(0,nbhist):
          postfix=postfixName[k]

	  hPF=fData.Get("em_"+str(j)+"_anti1/data_obs"+postfix).Clone()
          hPF.Add(fWZ.Get("em_"+str(j)+"_anti1/WZ3LNu"),-1)
          hPF.Add(fZZ.Get("em_"+str(j)+"_anti1/ZZ4L"),-1)
          hPF.Add(fWWW.Get("em_"+str(j)+"_anti1/VVV"),-1)
          hPF.Add(fTTZ.Get("em_"+str(j)+"_anti1/TTV"),-1)
          hPF.Add(fTTW.Get("em_"+str(j)+"_anti1/TTV"),-1)

          h0=hPF.Clone()

          hPFR=fData.Get("emR_"+str(j)+"_anti1/data_obs"+postfix).Clone()
          hPFR.Add(fWZ.Get("emR_"+str(j)+"_anti1/WZ3LNu"),-1)
          hPFR.Add(fZZ.Get("emR_"+str(j)+"_anti1/ZZ4L"),-1)
          hPFR.Add(fWWW.Get("emR_"+str(j)+"_anti1/VVV"),-1)
          hPFR.Add(fTTZ.Get("emR_"+str(j)+"_anti1/TTV"),-1)
          hPFR.Add(fTTW.Get("emR_"+str(j)+"_anti1/TTV"),-1)

          fout.cd()
          dir0.cd()
          hPFR.SetName("nonprompt"+postfix)
          hPFR.Scale(h0.Integral()/hPFR.Integral())
          hPFR.Write()


